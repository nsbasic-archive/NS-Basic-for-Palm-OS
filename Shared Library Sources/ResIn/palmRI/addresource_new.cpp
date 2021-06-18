void CColrView::addResourceToPalm(int picCount,int totalSize[20],BitmapPtr palmBitmap[20],LPCTSTR oFileName,int refID,LPCTSTR resType)
{
    FILE *iFile, *oFile  ;//, *dFile;
    long oldSize, dataSize;
    int i, oldCount;
    DatabaseHdrType iHdr;
    RsrcEntryType e;
    long remainder;
    char *inBuf;
    
    remove("tmp.prc");
    rename(oFileName, "tmp.prc");
    
    iFile = fopen("tmp.prc", "rb");
    	if(iFile==NULL) 
		{
		AfxMessageBox("ERROR- could not open prc file");
		exit(1);
		}
	fseek(iFile, 0, SEEK_END);
    oldSize = ftell(iFile);
    fseek(iFile, 0, SEEK_SET);
    
    oFile = fopen(oFileName, "wb");		// this is the file we're going to add a resource into
    
    //dFile = fopen("c:\\active\\systrapnamelist\\systrap.dat", "rb");	// this is where we get the resource from
    //fseek(dFile, 0, SEEK_END);
    //dataSize = ftell(dFile);			// find out how big the new resource is
    //fseek(dFile, 0, SEEK_SET);
	dataSize=totalSize[0];				//******CHANGE THIS
    
    fread(&iHdr, sizeof(DatabaseHdrType) - sizeof(Word), 1, iFile);		// read the DB header
    oldCount = read68kWord(&iHdr.recordList.numRecords);				// get the current # records in it
    write68kWord(&iHdr.recordList.numRecords, (Word)(oldCount + 1));	// we're adding one more
    fwrite(&iHdr, sizeof(DatabaseHdrType) - sizeof(Word), 1, oFile);	// the header has a bogus Word at the end

    //DWord theResType=(DWord) (  ((*resType)<<24) + ((*(resType+1))<<16) + ((*(resType+2))<<8) +(*(resType+3)) );
    long startOfResourceMap = ftell(iFile);
    long startOfReplacedResourceContents;
    theResType = *((DWord *)(resType)); // in big-endian
    Word theResId;
    write68Word(&theResId, refID);      
    int replaceIndex = -1;
    for (i = 0; i < oldCount; i++) {				// read and write all the previous resource entries 
        fread(&e, sizeof(RsrcEntryType), 1, iFile);
	int curOffset = read68kDWord(&e.localChunkID);
        if ((e.type == theResType) && (e.id == theResID)) {
            replaceIndex = i;
            startOfReplacedResourceContents = curOffset;
            if (i == (oldCount - 1)) {
                oldResourceSize = oldSize - curOffset;
            }
            else {
                i++;
                fread(&e, sizeof(RsrcEntryType), 1, iFile);
        	int nextOffset = read68kDWord(&e.localChunkID);
                oldResourceSize = nextOffset - curOffset;
            }
            break;
        }
    }
    
    fseek(iFile, startOfResourceMap, SEEK_SET);
    if (replaceIndex != -1) {
        for (i = 0; i <= replaceIndex; i++) {		// these resource entries remain unchanged
            fread(&e, sizeof(RsrcEntryType), 1, iFile);
            fwrite(&e, sizeof(RsrcEntryType), 1, oFile);
        }
        for (i = replaceIndex + 1; i < oldCount; i++) {
            fread(&e, sizeof(RsrcEntryType), 1, iFile);
            curOffset = read68kDWord(&e.localChunkID);
        
            write68kDWord(&e.localChunkID, (DWord)(newResourceSize + oldResourceSize));
	    fwrite(&e, sizeof(RsrcEntryType), 1, oFile);
        }
        // copy straight through the initial resource contents
        remainder = startOfReplacedResourceContents - (sizeof(DatabaseHdrType) - sizeof(Word)) - oldCount * sizeof(RsrcEntryType);
        inBuf = (char *)malloc(remainder);
        fread(inBuf, 1, remainder, iFile);
        fwrite(inBuf, 1, remainder, oFile);
        free(inBuf);
        
        // copy the new resource for replaceIndex
	for(i=0;i<picCount;i++)
	  fwrite( (char *)palmBitmap[i], 1, totalSize[i], oFile);	
	fwrite((char *)palmBitmap[0], 1, 1, oFile);	
        //
        fseek(iFile, oldResourceSize, SEEK_CUR);    // skip the old resource data
        
        // copy through the remainder resource contents
        remainder = oldSize - (startOfReplacedResourceContents + oldResourceSize);
        inBuf = (char *)malloc(remainder);
        fread(inBuf, 1, remainder, iFile);
        fwrite(inBuf, 1, remainder, oFile);
        free(inBuf);

    }
    else {
        for (i = 0; i < oldCount; i++) {				// read and write all the previous resource entries 
            fread(&e, sizeof(RsrcEntryType), 1, iFile);
	    int curOffset;
            curOffset = read68kDWord(&e.localChunkID);              // all the embedded offset values need to be incremented by
								    // the size of the RsrcEntryType we're adding
            write68kDWord(&e.localChunkID, (DWord)(curOffset + sizeof(RsrcEntryType)));
	    fwrite(&e, sizeof(RsrcEntryType), 1, oFile);
        }

        write68kDWord(&e.type,theResType );					// add the new resource entry at the end
	    // convert resourse ID )passed as a parm) to a 16 bit word
        write68kWord(&e.id, refID);
        write68kDWord(&e.localChunkID, oldSize + sizeof(RsrcEntryType));		// it's offset is the original eof + the extra RsrcEntryType
        fwrite(&e, sizeof(RsrcEntryType), 1, oFile);
    
	    // suck all the resource contents across
        remainder = oldSize - (sizeof(DatabaseHdrType) - sizeof(Word)) - oldCount * sizeof(RsrcEntryType);
        inBuf = (char *)malloc(remainder);
        fread(inBuf, 1, remainder, iFile);
        fwrite(inBuf, 1, remainder, oFile);
        free(inBuf);

	    // and then tack on the new resource contents
    //    inBuf = (char *)malloc(dataSize + 1);
    //    fread(inBuf, 1, dataSize, dFile);
    //    fwrite(inBuf, 1, dataSize + 1, oFile);
    //    free(inBuf);

	    for(i=0;i<picCount;i++)
	      fwrite( (char *)palmBitmap[i], 1, totalSize[i], oFile);	
	    fwrite((char *)palmBitmap[0], 1, 1, oFile);	
    }

    fclose(oFile);
    fclose(iFile);

}
