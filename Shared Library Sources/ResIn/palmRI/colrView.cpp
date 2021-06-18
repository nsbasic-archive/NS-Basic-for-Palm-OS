// colrView.cpp : implementation of the CColrView class
//



#include "stdafx.h"
#include "colr.h"
#include <afxctl.h>


#include "colrDoc.h"
#include "colrView.h"
//#include "palmBitmap.h" //included in colrview.h

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColrView

IMPLEMENT_DYNCREATE(CColrView, CView)

BEGIN_MESSAGE_MAP(CColrView, CView)
	//{{AFX_MSG_MAP(CColrView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColrView construction/destruction
#define HIMETRIC_INCH	2540



unsigned char CColrView::prcData[]=
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x09,0x00,0x00,0x3A,0x91,0xAB,0xB1, 0x3A,0x91,0xAC,0x0B,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x52,0x73,0x72,0x63,
	0x50,0x4D,0x52,0x49,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

CColrView::CColrView()
{
m_plp=NULL;
First_Time_in_Draw=true;
}

CColrView::~CColrView()
{
	if (m_plp!=NULL) HeapFree(GetProcessHeap (), 0,m_plp);
}

BOOL CColrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CColrView drawing

void CColrView::OnDraw(CDC* pDC)
{

	if(First_Time_in_Draw) 
		First_Time_in_Draw=false;
	else return;


	CColrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);



	LPCTSTR outputFileName = pDoc->ofilename;
	LPCTSTR resType = pDoc->resType;
	int resID = pDoc->resID;


	BitmapPtrV2 palmBitmap[numLayer];
	int totalSize[20];
	int pIdx,dpIdx=1;

	for(pIdx=0;pIdx<pDoc->picCount;pIdx++) palmBitmap[pIdx]=NULL; // max picCount will be 4

	for(pIdx=0;pIdx<pDoc->picCount;pIdx++) // here, we'll have to loop through ALL pictures
		{

		// select the next existing image of 1,2,4,8, or 16
		while(!pDoc->deep[dpIdx]) dpIdx++; 
		int dp=dpIdx;dpIdx++;
		LPPICTURE gpPicture=pDoc->gpPicture[dp];
		int bpp=pDC->GetDeviceCaps(BITSPIXEL);
		if (gpPicture)
			{
			unsigned int nWidth=picWidth[dp];
			unsigned int nHeight=picHeight[dp];
			RECT rc;
			
			createPCPalette(pDC,dp%halfNumLayer);
			createPalmCT(dp%halfNumLayer);

			GetClientRect(&rc);

/*
			CDC * dcMem=new CDC();
			dcMem->CreateCompatibleDC(pDC);
			CBitmap * bitm=new CBitmap();
			bitm->CreateCompatibleBitmap(dcMem,nWidth, nHeight);
			dcMem->SelectObject(bitm);
			gpPicture->Render(dcMem->m_hDC,0, 0, nWidth, nHeight, 0, pichmHeight[dp], pichmWidth[dp], -pichmHeight[dp], &rc);
			char temp[256];
			bitm->GetBitmapBits(256,&temp[0]);
*/

			// display picture using IPicture::Render
			gpPicture->Render(pDC->m_hDC,0, 0, nWidth, nHeight, 0, pichmHeight[dp], pichmWidth[dp], -pichmHeight[dp], &rc);

			int tblSiz=0;
			if((dp%halfNumLayer)!=16)
				tblSiz=1<<(dp%halfNumLayer);



			// here is where we depart from the index table form of bitmap creation if the depth is 16 
			//  that's because 16 bit entries use direct pxiel data - i.e. each pixel is represented by 16 bits
			//  made up of bit values of the form 'rrrr rggg gggb bbbb' i.e. 5:6:5 technique
/*
			if(dp==16)
				{
				AfxMessageBox("ERROR- 16 bit bitmaps not supported yet");
				exit(1);
				}
*/


			UInt16 rowBytes=((nWidth*(dp%halfNumLayer)+15 )/16)*2;
			//int outside=(int) (rowBytes+1-((float)dp*nWidth+1)/8.); 
		
			int outsideBits=8*rowBytes-(dp%halfNumLayer)*nWidth;		// number of bits of junk at the end of a row
			int outside = (outsideBits + 7) / 8;		// number of bytes, including a possible partial
			if (outsideBits % 8) {			// if there is a partial byte, skip it
				outside--;
			}
		



		char * idx = (char *) calloc(nHeight*rowBytes,1);
		int noOfPixels=0;
		unsigned long * buf=(unsigned long *)malloc(nWidth*nHeight*sizeof(unsigned long));
		int k=0;

		//***GETTING THE PIXELS FROM THE DISPLAYED IMAGE ON THE PC SCREEN
		//***	
//---
		int rdp = dp%halfNumLayer;
		for(unsigned int ui=0;ui<nHeight;ui++)
			for(unsigned int j=0;j<nWidth;j++)
				buf[k++]=pDC->GetPixel(j,ui);
		noOfPixels=k;

			UInt16 *idx16 =(UInt16 *)idx; //idx16 is therefore 16 bit ref to idx
			unsigned long b;
			UInt16 b16;
			if(rdp==16)
				{
				//***16 bit direct is NEW and handled differently from 1,2,4,8
				//*** store each pixel in 16 bits: 'rrrr rggg gggb bbbb'
				for(int i=0;i<noOfPixels;i++)
					{
					b=buf[i];
					//each buf[i] goes into idx16[i];
					b16= (UInt16) ( ((b & 0x000000F8) <<8)  |  (( b &0x0000FC00) >> 5)  |  ((b & 0x00F80000) >> 19) ); 
					idx16[i]= (b16 >> 8) | ((b16 & 0x00FF) << 8);
					}
				}
			else
				{
				//***GENERATION OF THE INDEXES OF THE PIXELS INTO THE PALM COLOR TABLE
				//***PACK THE DATA ACCORDING TO THE NUMBER OF BITS PER PIXEL AND THEREFORE PIXELS INEXES PER BYTE
				//***	
				int noOfBits=(rdp==8) ? 8 : 0; // so 8 deep always comes this branch
				noOfPixels=0;
				int j4=0,ii;
				int extra=-1;
				for(unsigned int j=0;j<nHeight;j++)
					{
				 for(unsigned int j2=0;j2<nWidth;j2++)
					{
					boolean notInList=true;
					for(int i=0;i<=(tblSiz+extra);i++)
						{
						if((table[i]& 0x00FFFFFF)==(buf[j4] & 0x00FFFFFF))
							{
							ii=(i<tblSiz) ? i : ((table[i]>>24)& 0x000000FF); 
							if(noOfBits==8)
								{
								if(rdp==8)
									{
									if(0x00000000==(buf[j4] & 0x00FFFFFF)) ii=255; // black is always LAST entry
									idx[noOfPixels++]=ii;
									}
								else
									{
									noOfPixels++;
									idx[noOfPixels]=ii;
									noOfBits=rdp;
									}
								}
							else
								{
								idx[noOfPixels]=(idx[noOfPixels]<<rdp) | ii;
								noOfBits+=rdp;
								}
							notInList=false;
							break;
							}
						}
					if(notInList) 
						{
						COLORREF crf=pDC->GetNearestColor( buf[j4] ) ;  // just for testing


						// see if we can compute the closest color in the table
						long lb=(long) buf[j4];
						int closestIndex;


						long rb=(lb>>16) & 0x000000FF;
						long gb=(lb>>8)  & 0x000000FF;
						long bb=lb  & 0x000000FF;
						long diff=255*255+255*255+255*255+1;
						for(int i=0;i<tblSiz;i++)
							{
							long lt=table[i];
							long rt=(lt>>16) & 0x000000FF;
							long gt=(lt>>8)  & 0x000000FF;
							long bt=lt  & 0x000000FF;
							long num=(rb-rt)*(rb-rt)+(gb-gt)*(gb-gt)+(bb-bt)*(bb-bt);
							if(num<diff)
								{
								diff=num;
								closestIndex=i;
								}
							}
							i=closestIndex;
							if(noOfBits==8)
								{
								if(rdp==8)
									idx[noOfPixels++]=i;
								else
									{
									noOfPixels++;
									idx[noOfPixels]=i;
									noOfBits=rdp;
									}
								}
							else
								{
								idx[noOfPixels]=(idx[noOfPixels]<<rdp) | i;
								noOfBits+=rdp;
								}
						/*
						if(extra==512)
							{
							AfxMessageBox("ERROR- Too many colors in color table");
							exit(1);
							}
						table[tblSiz+(++extra)]=(closestIndex<<24) | (lb & 0x00FFFFFF);
						*/
						}
					j4++;
					 } // end inner for loop
				if((rdp!=8) &&(noOfBits!=0)) {
						idx[noOfPixels] <<= (8 - noOfBits);
						noOfPixels++;
					}
					noOfPixels=noOfPixels+outside; 
					noOfBits=(rdp==8) ? 8 : 0;
					} //end outer for loop
			  } // end else on 16 bit dp
///-----
		bool isV2 = dp<halfNumLayer;
		int BitmapTypeSize = isV2? sizeof(BitmapTypeV2):sizeof(BitmapTypeV3);
		unsigned long noOfBytes= rowBytes*nHeight;

		totalSize[pIdx]=BitmapTypeSize+noOfBytes; //each is a dword multiplier, so totalsize is dword multiple
		if (totalSize[pIdx] % 4) totalSize[pIdx] += 2;

		palmBitmap[pIdx]=	(BitmapPtrV2) malloc(totalSize[pIdx]);

		BitmapPtrV2 bitmapPtr=palmBitmap[pIdx];
		BitmapPtrV2 bitmapPtrC = (BitmapPtrV2)bitmapPtr; 
		BitmapPtrV2 bitmapPtrV2 = (BitmapPtrV2)bitmapPtr; 
		BitmapPtrV3 bitmapPtrV3 = (BitmapPtrV3)bitmapPtr; 


		/*Int16*/   write68kWord((UInt16 *)(&(bitmapPtrC->width)),nWidth); //palmBitmap[pIdx]->width = nWidth; 
		/*Int16*/   write68kWord((UInt16 *)&(bitmapPtrC->height),nHeight); //palmBitmap[pIdx]->height= nHeight;

		/*UInt16*/  write68kWord(&bitmapPtrC->rowBytes,rowBytes);// palmBitmap[pIdx]->rowBytes = rowBytes;

		// can't do the following - it must be done as shown below the cooments
		//			FOR: palmBitmap[pIdx]->flags
		/*
							palmBitmap[pIdx]->flags.compressed=0;
							palmBitmap[pIdx]->flags.forScreen=0;
							palmBitmap[pIdx]->flags.hasColorTable=0;
							palmBitmap[pIdx]->flags.hasTransparency=0;
							palmBitmap[pIdx]->flags.indirect=0;
							palmBitmap[pIdx]->flags.reserved=0;
		*/
		/* PalmOS5
		typedef struct BitmapFlagsType
		{
			UInt16 	compressed:1;  				// Data format:  0=raw; 1=compressed
			UInt16 	hasColorTable:1;				// if true, color table stored before bits[]
			UInt16 	hasTransparency:1;			// true if transparency is used
			UInt16 	indirect:1;						// true if bits are stored indirectly
			UInt16 	forScreen:1;					// system use only
			UInt16	directColor:1;					// direct color bitmap
			UInt16	indirectColorTable:1;		// if true, color table pointer follows BitmapType structure
			UInt16	noDither:1;						// if true, blitter does not dither
			UInt16 	reserved:8;
		}BitmapFlagsType;
		*/
		char compressed=0;
		char hasColorTable=0;
		char hasTransparency=0;
		char indirect=0;
		char forScreen=0;
		char directColor=(dp==16+halfNumLayer)?1:0;
		char indirectColorTable=0;
		char noDither=0;
		char reserved=0;

		UInt16 flags=	(compressed<<15) | 
						(hasColorTable<<14) | 
						(hasTransparency<<13) | 
						(indirect<<12) |  
						(forScreen<<11) | 
						(directColor<<10) | 
						(indirectColorTable<<9) | 
						(noDither<<8) | 
						(reserved<<0);

		write68kWord(   (UInt16 *) (&bitmapPtrC->flags),flags);
		/*UInt8*/	bitmapPtrC->pixelSize=dp%halfNumLayer;				// bits/pixel

		if (isV2)
		{
		/*UInt8*/	bitmapPtrV2->version=2;				// version of bitmap. This is vers 2
		/*UInt16*/	bitmapPtrV2->nextDepthOffset=0;		// # of DWords to next BitmapType <<<CHANGES WHEN WE HAVE MULTIPLES
														//  from beginnning of this one
		/*UInt8*/	bitmapPtrV2->transparentIndex=0;		// v2 only, if flags.hasTransparency is true,
														// index number of transparent color
		/*UInt8*/	bitmapPtrV2->compressionType=BitmapCompressionTypeNone;
											 			// v2 only, if flags.compressed is true, this is
														// the type, see BitmapCompressionType
		/*UInt16*/	bitmapPtrV2->reserved=0;				// for future use, must be zero!
		}else 
		{
		/*UInt8*/	bitmapPtrV3->version=3;				// version of bitmap. This is vers 3
		/*UInt8*/	bitmapPtrV3->size=0x18;				// size of this structure in bytes (0x16)
		/*UInt8*/	bitmapPtrV3->pixelFormat=((dp%halfNumLayer)==16)?1:0;			// format of the pixel data, see pixelFormatType(pixelFormatIndexed=0)
		/*UInt8*/	bitmapPtrV3->unused=0;
		/*UInt8*/	bitmapPtrV3->compressionType=BitmapCompressionTypeNone; // see BitmapCompressionType
		/*UInt16*/	write68kWord((UInt16 *)&bitmapPtrV3->density,144); // used by the blitter to scale bitmaps 72-one 144-double
		/*UInt32*/	bitmapPtrV3->transparentValue=0;		// the index or RGB value of the transparent color
		/*UInt32*/	bitmapPtrV3->nextBitmapOffset=0;		// byte offset to next bitmap in bitmap family
		}

		// move noOfBytes from idex to BitmapPtr+sizeof(BitmapType) 

		char * to=((char *) palmBitmap[pIdx])+BitmapTypeSize;
		char * from=(char *) idx;


		memmove( to, from, noOfBytes );

		free(buf);
		free(idx);

		}
	else
		{
		AfxMessageBox("ERROR- a picture was not valid");
		exit(1);
		}


	}

	//
	for(pIdx=0;pIdx<pDoc->picCount-1;pIdx++) 
	{if (((BitmapPtrV2)palmBitmap[pIdx])->version == 2)
			 write68kWord((UInt16 *) &((BitmapPtrV2)palmBitmap[pIdx])->nextDepthOffset,totalSize[pIdx]/sizeof(DWord));
	else write68kDWord((DWord *) &((BitmapPtrV3)palmBitmap[pIdx])->nextBitmapOffset,totalSize[pIdx]);}


	int newResourceSize=0;
	for(int i=0;i<pDoc->picCount;i++) newResourceSize+=totalSize[i];

	if (newResourceSize>=65535)
	{
		AfxMessageBox("ERROR-  resource >64k");
		exit(newResourceSize);
	}

	addResourceToPalm(pDoc->picCount,totalSize,palmBitmap,outputFileName,resID,resType);
	for(pIdx=0;pIdx<pDoc->picCount;pIdx++) if(palmBitmap[pIdx]!=NULL) free(palmBitmap[pIdx]);
	if (m_plp!=NULL) HeapFree(GetProcessHeap (), 0,m_plp);

	exit(0);

}

/////////////////////////////////////////////////////////////////////////////
// CColrView printing

BOOL CColrView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CColrView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CColrView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CColrView diagnostics

#ifdef _DEBUG
void CColrView::AssertValid() const
{
	CView::AssertValid();
}

void CColrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColrDoc* CColrView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColrDoc)));
	return (CColrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColrView message handlers

void CColrView::write68kDWord(DWord *to, DWord value)
{
    char *p = (char *)to;
    p[0] = (char)(value >> 24);
    p[1] = (char)(value >> 16);
    p[2] = (char)(value >> 8);
    p[3] = (char)(value);
}

void CColrView::write68kWord(Word *to, Word value)
{
    char *p = (char *)to;
    p[0] = (char)(value >> 8);
    p[1] = (char)(value);
}

int CColrView::read68kWord(Word *from)
{
    unsigned char *p = (unsigned char *)from;
    int value = (p[0] << 8) | p[1];
    return value;
}

int CColrView::read68kDWord(DWord *from)
{
    unsigned char *p = (unsigned char *)from;
    int value = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
    return value;
}

void CColrView::addResourceToPalm(int picCount,int totalSize[numLayer],BitmapPtrV2 palmBitmap[numLayer],LPCTSTR oFileName,int refID,LPCTSTR resType)
{
//	AfxMessageBox("aaa");
    FILE *iFile=NULL, *oFile  ;//, *dFile;
    long oldSize, dataSize;
    int i, oldCount;
    DatabaseHdrType iHdr;
    RsrcEntryType e;
    long remainder;
    char *inBuf;
	DWord newResourceSize=0;
	for(i=0;i<picCount;i++) newResourceSize+=totalSize[i];
    
    remove("tmp.prc");
    rename(oFileName, "tmp.prc");
    
    iFile = fopen("tmp.prc", "rb");
	if(iFile==NULL) 
		{
		//AfxMessageBox("ERROR- could not open prc file");
		//exit(1);

		// This SHOULD work, if we didn't have a prc file, and we copied prc data to it to make one.
		oFile = fopen(oFileName, "wb");
		int fileNameLength = strlen(oFileName);
		if (fileNameLength > 31) fileNameLength = 31;
		CString tempCS(oFileName,fileNameLength);
		if ( tempCS.Right( 4 ).CompareNoCase(".prc") ==0) fileNameLength-=4;
		fwrite(oFileName, 1, fileNameLength, oFile); // file name into prc file;
		fwrite((prcData + fileNameLength), 1, (80 - fileNameLength), oFile);
		fclose(oFile);
		rename(oFileName, "tmp.prc");
		iFile = fopen("tmp.prc", "rb");
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
	
	//DWord theResType=(DWord) (  ((*resType)<<24) + ((*(resType+1))<<16) + ((*(resType+2))<<8) +(*(resType+3)) );
    long startOfResourceMap = ftell(iFile);
    long startOfReplacedResourceContents;
	unsigned char* cp = (unsigned char *)resType;
	DWord theResType=(DWord) (  ((*cp)<<24) + ((*(cp+1))<<16) + ((*(cp+2))<<8) +(*(cp+3)) );
	DWord invResType;
	write68kDWord(&invResType, theResType); 
    Word theResID;
    write68kWord(&theResID, refID);  
    DWord oldResourceSize;
    int replaceIndex = -1;
    for (i = 0; i < oldCount; i++) {				// read and write all the previous resource entries 
        fread(&e, sizeof(RsrcEntryType), 1, iFile);
	int curOffset = read68kDWord(&e.localChunkID);
        if ((e.type == invResType) && (e.id == theResID)) {
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
    
    fseek(iFile, 0, SEEK_SET);
    fread(&iHdr, sizeof(DatabaseHdrType) - sizeof(Word), 1, iFile);		// read the DB header
	if (replaceIndex == -1)
		write68kWord(&iHdr.recordList.numRecords, (Word)(oldCount + 1));	// we're adding one more
    fwrite(&iHdr, sizeof(DatabaseHdrType) - sizeof(Word), 1, oFile);	// the header has a bogus Word at the end

    if (replaceIndex != -1) {
        for (i = 0; i <= replaceIndex; i++) {		// these resource entries remain unchanged
            fread(&e, sizeof(RsrcEntryType), 1, iFile);
            fwrite(&e, sizeof(RsrcEntryType), 1, oFile);
        }
        for (i = replaceIndex + 1; i < oldCount; i++) {
            fread(&e, sizeof(RsrcEntryType), 1, iFile);
            int curOffset = read68kDWord(&e.localChunkID);
        
            write68kDWord(&e.localChunkID, (DWord)(curOffset + newResourceSize - oldResourceSize));
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
//	fwrite((char *)palmBitmap[0], 1, 1, oFile);	
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
        curOffset = read68kDWord(&e.localChunkID);		// all the embedded offset values need to be incremented by
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

	for(i=0;i<picCount;i++)
	  fwrite( (char *)palmBitmap[i], 1, totalSize[i], oFile);	
	}
    fclose(oFile);
    fclose(iFile);

}



void CColrView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CColrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int x=pDoc->picCount;
	CPaintDC dc(this);
	CDC *pDC=&dc;
	maxHeight=0;
	maxWidth=0;

	int dpIdx=1;
	for(int pIdx=0;pIdx<pDoc->picCount;pIdx++) // here, we'll have to loop through ALL pictures
		{
		while(!pDoc->deep[dpIdx]) dpIdx++;
		int dp=dpIdx;dpIdx++;

		LPPICTURE gpPicture=pDoc->gpPicture[dp];
		int bpp=pDC->GetDeviceCaps(BITSPIXEL);
		if (gpPicture)
			{


			// get width and height of picture
			long hmWidth;
			long hmHeight;
			gpPicture->get_Width(&hmWidth);
			gpPicture->get_Height(&hmHeight);
			pichmWidth[dp]=hmWidth;
			pichmHeight[dp]=hmHeight;
			// convert himetric to pixels
			picWidth[dp]= MulDiv(hmWidth, pDC->GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
			picHeight[dp]= MulDiv(hmHeight, pDC->GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
			if(picWidth[dp]>maxWidth) maxWidth=picWidth[dp];
			if(picHeight[dp]>maxHeight) maxHeight=picHeight[dp];
			}
		}
	

	CColrApp * app = (CColrApp *) AfxGetApp( );
// NSB update 12.26.01

//		(app->m_pMainWnd)->MoveWindow(0,0,maxWidth+12,maxHeight+92-42);
/*
	(app->m_pMainWnd)->MoveWindow(0,0,
		maxWidth+GetSystemMetrics(SM_CXSIZEFRAME)*2 + GetSystemMetrics(SM_CXEDGE)*2,
		maxHeight+GetSystemMetrics(SM_CYSIZEFRAME)*2 + GetSystemMetrics(SM_CYEDGE)*2 + 
		GetSystemMetrics(SM_CYMENU) + GetSystemMetrics(SM_CYCAPTION));
*/
	CWnd *w = app->m_pMainWnd;
	int fx = 200;
	int fy = 200;
	w->MoveWindow(0,0,fx,fy);
	CRect cr;
	w->GetClientRect(cr);
	int sx = fx - cr.Width();
	int sy = fy - cr.Height();
	
	//insurance
	sx+=16;
	sy+=16;
	
	w->MoveWindow(0,0,sx+maxWidth,sy+maxHeight);

// end update

}
 

void CColrView::createWebPalette()
	{
    UINT nColors=216+40; // 6x6x6 web safe colors
	DWORD dwSize = sizeof (LOGPALETTE) + ((nColors - 1) * sizeof (PALETTEENTRY));
	if (m_plp!=NULL) {m_palette.DeleteObject();HeapFree(GetProcessHeap (), 0,m_plp);}
    m_plp = (LOGPALETTE*) HeapAlloc (GetProcessHeap (), 0,dwSize);
    m_plp->palVersion = 0x300; // ?
    m_plp->palNumEntries = (WORD) nColors;

	int c[]={0xff,0xcc,0x99,0x66,0x33,0x00};
    int i=0;
    for (int b=5;b>=0;b--)
        for(int r=0;r<6;r++)
            for(int g=5;g>=0;g--)

		{
			m_plp->palPalEntry[i].peRed		= c[r];
			m_plp->palPalEntry[i].peGreen	= c[g];
			m_plp->palPalEntry[i].peBlue	= c[b];
			m_plp->palPalEntry[i++].peFlags = 0;
		}

	for(int ii=0;ii<40;ii++)
		{
			m_plp->palPalEntry[i].peRed		= 0;
			m_plp->palPalEntry[i].peGreen	= 0;
			m_plp->palPalEntry[i].peBlue	= 0;
			m_plp->palPalEntry[i++].peFlags = 0;
		}



	m_palette.CreatePalette(m_plp);
	}



 void CColrView::createGrayPalette()
	{
    UINT nColors=16; // 16 gray scale colors
	DWORD dwSize = sizeof (LOGPALETTE) + ((nColors - 1) * sizeof (PALETTEENTRY));
	if (m_plp!=NULL) {m_palette.DeleteObject();HeapFree(GetProcessHeap (), 0,m_plp);}
    m_plp = (LOGPALETTE*) HeapAlloc (GetProcessHeap (), 0,dwSize);
    m_plp->palVersion = 0x300; // ?
    m_plp->palNumEntries = (WORD) nColors;
 	int c[]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
    for (unsigned int i = 0; i < nColors; i++)
      {
        m_plp->palPalEntry[i].peRed   = (BYTE) c[i];
        m_plp->palPalEntry[i].peGreen = (BYTE) c[i];
        m_plp->palPalEntry[i].peBlue  = (BYTE) c[i];
        m_plp->palPalEntry[i].peFlags = 0;
		}

	m_palette.CreatePalette(m_plp);
	}


void CColrView::create4ShadePalette()
{
    UINT nColors=4; // 4 gray scale colors
	DWORD dwSize = sizeof (LOGPALETTE) + ((nColors - 1) * sizeof (PALETTEENTRY));
	if (m_plp!=NULL) {m_palette.DeleteObject();HeapFree(GetProcessHeap (), 0,m_plp);}
    m_plp = (LOGPALETTE*) HeapAlloc (GetProcessHeap (), 0,dwSize);
    m_plp->palVersion = 0x300; // ?
    m_plp->palNumEntries = (WORD) nColors;
 	int c[]={0x00,0x55,0xaa,0xff};
    for (unsigned int i = 0; i < nColors; i++)
      {
        m_plp->palPalEntry[i].peRed   = (BYTE) c[i];
        m_plp->palPalEntry[i].peGreen = (BYTE) c[i];
        m_plp->palPalEntry[i].peBlue  = (BYTE) c[i];
        m_plp->palPalEntry[i].peFlags = 0;
		}

	m_palette.CreatePalette(m_plp);
}


void CColrView::createBWPalette()
{
    UINT nColors=2; // 2 gray scale colors
	DWORD dwSize = sizeof (LOGPALETTE) + ((nColors - 1) * sizeof (PALETTEENTRY));
	if (m_plp!=NULL) {m_palette.DeleteObject();HeapFree(GetProcessHeap (), 0,m_plp);}
    m_plp = (LOGPALETTE*) HeapAlloc (GetProcessHeap (), 0,dwSize);
    m_plp->palVersion = 0x300; // ?
    m_plp->palNumEntries = (WORD) nColors;
  	int c[]={0x00,0xff};
    for (unsigned int i = 0; i < nColors; i++)
      {
        m_plp->palPalEntry[i].peRed   = (BYTE) c[i];
        m_plp->palPalEntry[i].peGreen = (BYTE) c[i];
        m_plp->palPalEntry[i].peBlue  = (BYTE) c[i];
        m_plp->palPalEntry[i].peFlags = 0;
		}
	
	m_palette.CreatePalette(m_plp);
}
      

void CColrView::createWebPalmCT()
{

//***GENERATION OF THE 256 ELEMENT COLOR TABLE FOR THE PALM
//***	
int c[]={0x00,0x33,0x66,0x99,0xcc,0xff};
int k=0;
for (int r=5;r>=0;r--)
	for(int b=5;b>=3;b--)
		for(int g=5;g>=0;g--)
			table[k++]=((((c[b]<<8) | c[g]) <<8) | c[r]);
for (r=5;r>=0;r--)
	for(int b=2;b>=0;b--)
		for(int g=5;g>=0;g--)
			table[k++]=((((c[b]<<8) | c[g]) <<8) | c[r]);

int c2[]={0x11,0x22,0x44,0x55,0x77,0x88,0xaa,0xbb,0xdd,0xee};

k--; //(zero goes elsewhere)
for (int i=0;i<10;i++)
			table[k++]=((((c2[i]<<8) | c2[i]) <<8) | c2[i]);

unsigned long leftOvers[]={0x00c0c0c0,0x00800000,0x00800080,0x00008000,0x00008080};
for(i=0;i<5;i++)
			table[k++]=leftOvers[i];
for(i=0;i<26;i++)
			table[k++]=0;
}


void CColrView::createGrayPalmCT()
{
    UINT nColors=16; // 16 gray scale colors
 	int c[]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
     int ii=0;for (int i= nColors-1 ; i >=0; i--)
		table[ii++]=((((c[i]<<8) | c[i]) <<8) | c[i]);
}


void CColrView::create4ShadePalmCT()
{
    UINT nColors=4; // 4 gray scale colors
 	int c[]={0x00,0x55,0xaa,0xff};
     int ii=0;for (int i= nColors-1 ; i >=0; i--)
		table[ii++]=((((c[i]<<8) | c[i]) <<8) | c[i]);
}


void CColrView::createBWPalmCT()
{
    UINT nColors=2; // 2 gray scale colors
  	int c[]={0x00,0xff};
     int ii=0;for (int i= nColors-1 ; i >=0; i--)
		table[ii++]=((((c[i]<<8) | c[i]) <<8) | c[i]);
}
      


void CColrView::createPCPalette(CDC* pDC,int dp)
{
	 switch (dp)
	 {

	 case 16: break; // i.e. need no palette for 16 bit (direct table)

	 case 8:createWebPalette();break;
	 case 4:createGrayPalette();break;
	 case 2:create4ShadePalette();break;
	 case 1:createBWPalette();break;


	 }
	pDC->SelectPalette(&m_palette,FALSE);
    pDC->RealizePalette();
}

void CColrView::createPalmCT(int dp)
{
 	 switch (dp)
	 {
	 case 16: break; // i.e. need no palette for 16 bit (direct table)

	 case 8:createWebPalmCT();break;
	 case 4:createGrayPalmCT();break;
	 case 2:create4ShadePalmCT();break;
	 case 1:createBWPalmCT();break;

	 }

}





///////////////
/**
 * Compress a Bitmap (Tbmp or tAIB) resource.
 * 
 * @param rcbmp      a reference to the Palm Computing resource data.
 * @param compress   compression style?
 * @param colortable does a color table need to be generated?
 * @param directColor is the bitmap > 8bpp? (direct color mode)
 */
/*
static void
BMP_CompressBitmap(BitmapType * rcbmp,
                   int compress,
                   BOOL colortable,
                   BOOL directColor)
{
  unsigned char *bits;
  int size, msize, i, j, k, flag;

  // determine how much memory is required for compression (hopefully
  // less)
  size = 2;
  if (colortable)
    size += COLOR_TABLE_SIZE;
  if (directColor)
    size += 8;
  msize = size + ((rcbmp->cbRow + ((rcbmp->cbRow + 7) / 8)) * rcbmp->cy);

  // allocat memory and clear
  bits = (unsigned char *)malloc(msize * sizeof(unsigned char));
  memset(bits, 0, msize * sizeof(unsigned char));

  // prevent transparency data from being compressed in 16bpp
  if (directColor) 
    rcbmp->pbBits += 8;  

  // do the compression (at least, attempt it)
  for (i = 0; i < rcbmp->cy; i++)
  {
    flag = 0;
    for (j = 0; j < rcbmp->cbRow; j++)
    {
      if ((i == 0) ||
          (rcbmp->pbBits[(i * rcbmp->cbRow) + j] !=
           rcbmp->pbBits[((i - 1) * rcbmp->cbRow) + j]))
      {
        flag |= (0x80 >> (j & 7));
      }
      if (((j & 7) == 7) || (j == (rcbmp->cbRow - 1)))
      {
        bits[size++] = (unsigned char)flag;
        for (k = (j & ~7); k <= j; ++k)
        {
          if (((flag <<= 1) & 0x100) != 0)
            bits[size++] = rcbmp->pbBits[i * rcbmp->cbRow + k];
        }
        flag = 0;
      }
    }
  }

  // fix pointer back for 16bpp (we offset it previously)
  if (directColor) 
    rcbmp->pbBits -= 8;  

  // if we must compress, or if it was worth it, save!
  if (compress == rwForceCompress || size < rcbmp->cbDst)
  {

    // do we have a color table?
    if ((colortable) && (!directColor))
    {

      int i;

      // copy the color table (dont forget it!)
      for (i = 0; i < COLOR_TABLE_SIZE; i++)
        bits[i] = rcbmp->pbBits[i];

      bits[COLOR_TABLE_SIZE] = (unsigned char)(size >> 8);
      bits[COLOR_TABLE_SIZE + 1] = (unsigned char)size;
    }
    // direct color info?
    if (directColor)
    {

      int i;

      // copy the direct color info (dont forget it!)
      for (i = 0; i < 8; i++)
        bits[i] = rcbmp->pbBits[i];

      bits[8] = (unsigned char)(size >> 8);
      bits[9] = (unsigned char)size;
    }

    else
    {
      bits[0] = (unsigned char)((size & 0xff00) >> 8);
      bits[1] = (unsigned char)(size & 0x00ff);
    }

    // change the data chunk to the newly compressed data
    free(rcbmp->pbBits);

    // rcbmp->ff |= 0x8000;
    rcbmp->flags.compressed = fTrue;

    rcbmp->pbBits = bits;
    rcbmp->cbDst = size;
  }
  else
    free(bits);
} 



*/