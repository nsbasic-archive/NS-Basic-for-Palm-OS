



/***********************************************************************
*
Sample Code Disclaimer


Copyright © 1999 3Com Corporation or its subsidiaries.  All
rights reserved.

You may incorporate this sample code (the "Code") into your applications
for Palm Computing(R) platform products and may use the Code to develop
such applications without restriction.  The Code is provided to you on
an "AS IS" basis and the responsibility for its operation is 100% yours.
3COM CORPORATION AND ITS SUBSIDIARIES (COLLECTIVELY, "3COM") DISCLAIM
ALL WARRANTIES, TERMS AND CONDITIONS WITH RESPECT TO THE CODE, EXPRESS,
IMPLIED, STATUTORY OR OTHERWISE, INCLUDING WARRANTIES, TERMS OR
CONDITIONS OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
NONINFRINGEMENT AND SATISFACTORY QUALITY.  You are not permitted to
redistribute the Code on a stand-alone basis and you may only
redistribute the Code in object code form as incorporated into your
applications.  TO THE FULL EXTENT ALLOWED BY LAW, 3COM ALSO EXCLUDES ANY
LIABILITY, WHETHER BASED IN CONTRACT OR TORT (INCLUDING NEGLIGENCE), FOR
INCIDENTAL, CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OF ANY
KIND, OR FOR LOSS OF REVENUE OR PROFITS, LOSS OF BUSINESS, LOSS OF
INFORMATION OR DATA, OR OTHER FINANCIAL LOSS ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THE CODE.  The Code is subject
to Restricted Rights for U.S. government users and export regulations.

SAMPLE NAME:        Signature++

FILE:                 Signature.c

DESCRIPTION:        Implementation file for the signature++ sample
*
**********************************************************************/
//#define DO_NOT_ALLOW_ACCESS_TO_INTERNALS_OF_STRUCTS
#include <PalmOS.h>                // all the system toolbox headers
#include <PalmCompatibility.h>
#include <SysEvtMgr.h>            //    Needed for search for EvtSysEventAvail
#include <FeatureMgr.h>            //    Needed to get the ROM version
#include <MemoryMgr.h>
#include <ErrorMgr.h>
#include <BmpGlue.h>
#include <Bitmap.h>
#include "BitmapRsrc.h"
#include <ErrorBase.h>                   //05212003

#include "NSBPNOShared.h"               //EMP
#include  "copy.h"


/***********************************************************************
* Global defines for this module
**********************************************************************/
#define version20    0x02000000    // Palm OS 2.0 version number
#define version32    0x03200000    // Palm OS 3.2 version number
#define version35   0x03500000  // Palm OS 3.5 version number 
#define version50   0x05000000  // Palm OS 5.0 version number   //inserted 02222003
#define version40   0x04000000  // Palm OS 4.0
//added 04022003
typedef struct oldBitmapFlagsType
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
}
oldBitmapFlagsType;
//end of adds 
//09232002---
typedef struct oldBitmapType
//#ifdef ALLOW_ACCESS_TO_INTERNALS_OF_BITMAPS	// These fields will not be available in the next OS release!
{
	Int16  				width;
	Int16  				height;
	UInt16  				rowBytes;
	oldBitmapFlagsType	flags;   //changed 04022003
	 
	UInt8					pixelSize;			// bits/pixel
	UInt8					version;				// version of bitmap. This is vers 2
	UInt16	 			nextDepthOffset;	// # of DWords to next BitmapType
													//  from beginnning of this one
	UInt8					transparentIndex;	// v2 only, if flags.hasTransparency is true,
													// index number of transparent color
	UInt8					compressionType;	// v2 only, if flags.compressed is true, this is
													// the type, see BitmapCompressionType
														
	UInt16	 			reserved;			// for future use, must be zero!
	
	// if (flags.hasColorTable)
	//	  ColorTableType	colorTable		// NOTE: Could have 0 entries (2 bytes long)
	//
	// if (flags.directColor)
	//	  BitmapDirectInfoType	directInfo;
	// 
	// if (flags.indirect)
	//	  void*	  bitsP;						// pointer to actual bits
	// else
	//    UInt8	  bits[];					// or actual bits
	//
}
//#endif
oldBitmapType;

struct oldBitmapType* oldBitmapPtr;
//09232002 end-of-additions----
/***********************************************************************
* Global variables for this module
**********************************************************************/
  struct oldBitmapType*    gBitmapPtr = NULL;    // This will point to our signature bitmap



/***********************************************************************
* Prototypes for internal functions
**********************************************************************/

extern void misc_stostr(struct dataelem **d,
        UInt16 sub1,UInt16 sub2,UInt16 sub3, char *result);

static VoidPtr         GetObjectPtr(Int objectID);    
static FieldPtr     GetFocusObjectPtr(void);
static BitmapPtr     GetSignatureBitmap( RectangleType* theBoundsPtr );
void GetSignatureGadgetBounds( RectangleType* theBoundsPtr );
void         CaptureSignature();


static void     saveSignature();
static void     getSignature(UShort srecToGet);
static void     clearSignature();
static void     drawSignature();

Boolean find_ctlid(Boolean abort);
//static void drawSignature(BitmapPtr gBitmapPtr)
//{
//    RectangleType    theBounds;
//    
//    GetSignatureGadgetBounds( &theBounds );
//    
//    // Draw a frame around our gadget so that users know where to sign
//    WinDrawRectangleFrame( simpleFrame, &theBounds );
//    
//    // Draw the signature bitmap if it exists (it would have been setup
//    // by StartApplication)
//    if (gBitmapPtr)
//        WinDrawBitmap( gBitmapPtr, theBounds.topLeft.x, theBounds.topLeft.y );
//
//  return;
//}

static void clearSignature()
{
    SWord                x, y;
//    Boolean            penDown;
    RectangleType    theGadgetBounds;

  // Grab the gadget's bounds
    GetSignatureGadgetBounds( &theGadgetBounds );
                
    // Erase the rectangle
    WinEraseRectangle( &theGadgetBounds, 0 );
                    
    // Draw a frame around our gadget so that users know where to sign
    WinDrawRectangleFrame( simpleFrame, &theGadgetBounds );                
    
    
    return;
}




/***********************************************************************
*
* FUNCTION:    GetObjectPtr
*
* DESCRIPTION: P10. This routine returns a pointer to an object in the active form.
*
* PARAMETERS:  objectID - id of the object
*
* RETURNED:    pointer to the object's data structure
*
***********************************************************************/
static VoidPtr GetObjectPtr(Int objectID)
{
    FormPtr frm;
    
    frm = FrmGetActiveForm();
    return(FrmGetObjectPtr(frm, FrmGetObjectIndex(frm, objectID)));
}




/***********************************************************************
*
* FUNCTION:        GetSignatureBitmap
*
* DESCRIPTION:     This routine converts the screen drawing into a bitmap
*                    WARNING:  THIS CODE IS NOT SUPPORTED CODE AND MAY NOT WORK 
*                    ON DEVICES WHOSE OS VERSION IS OTHER THAN 2.X, 3.0, 
*                    3.1, OR 3.2.
*
* PARAMETERS:      theBoundsPtr - the bounds of the gadget
*
* RETURNED:        A pointer to the bitmap
*
***********************************************************************/
BitmapPtr GetSignatureBitmap( RectangleType* theBoundsPtr )
{
   //this whole routine redone 03102003
    Boolean seeIfHighDensityDisplay();
    extern BitmapPtr CaptureSignaturePriorToVersion35(RectangleType* theBoundsPtr );

    UInt32 winMgrVersion;
    UInt32 width;
    UInt32 height;
    UInt32 depth;
    UInt16 version;
    UInt32 pixelFormat;
    Boolean enableColor;
    BmpRsrcType * bmpV3;
    BmpRsrcType * bmpV2;
    BitmapPtr ptr;
    WinHandle wnd;
    WinHandle wnd2;
    Err err;
    UInt16 zeroWord=0;
    
    
    
    struct oldBitmapTypeV1Layout
	//ifdef ALLOW_ACCESS_TO_INTERNALS_OF_BITMAPS	// These fields will not be available in the next OS release!
	{
		// BitmapType
	 	Int16  				width;
		Int16  				height;
		UInt16  				rowBytes;
		oldBitmapFlagsType	flags;				//changed 04022003	// (compressed, hasColorTable)
		UInt8					pixelSize;
		UInt8					version;					
		
		// version 1 fields
		UInt16	 			nextDepthOffset;		// offset in longwords
		UInt16				reserved[2];	
	}  ;
	struct oldBitmapTypeV1Layout oldBitmapTypeV1;
    UInt32 lenBits;
	UInt32 lenHdr;
 
    err = FtrGet(sysFtrCreator, sysFtrNumWinVersion, &winMgrVersion);
    if(PNO(romVersion)<version35)    return(CaptureSignaturePriorToVersion35( theBoundsPtr ));  //prior to version 35 
    else
    {
 
        WinScreenMode(winScreenModeGet,&width,&height,&depth,&enableColor);
        
		
		
        //low density
//dbug("low density");
 
            bmpV2= BmpRsrcV2Create(theBoundsPtr->extent.x, theBoundsPtr->extent.y,
							depth, NULL, NULL);
            wnd=WinCreateBitmapWindow((struct BitmapType*)bmpV2,&err);   //create a new bitmap window 
			if( err!= errNone)  MiscFatalAlert("Out of Memory."); 
	        WinCopyRectangle(WinGetDrawWindow(), wnd ,theBoundsPtr,0,0,winPaint);
		
		if (seeIfHighDensityDisplay()==true)
        {
 //dbug("high density");   
             //high density
             WinScreenGetAttribute(winScreenPixelFormat, &pixelFormat);
             ((struct BmpRsrcV2Type*)(bmpV2))->nextDepthOffset=MemPtrSize(bmpV2)/4;
             bmpV3= BmpRsrcV3Create(theBoundsPtr->extent.x*2, theBoundsPtr->extent.y*2,
							depth, NULL, NULL,
							kDensityDouble,   pixelFormat);
         
        
	        wnd2=WinCreateBitmapWindow((struct BitmapType*)bmpV3,&err);   //create a new bitmap window 
			if( err!= errNone)  MiscFatalAlert("Out of Memory."); 
	        WinCopyRectangle(WinGetDrawWindow(), wnd2,theBoundsPtr,0,0,winPaint);
	    }    
        else
        {
 
            return ( (BitmapPtr) bmpV2); 
        }
//WinSetCoordinateSystem(kDensityDouble);
//WinDrawBitmap((BitmapPtr) bmpV3, 0,30);
       
         
 	 
		//build a required dummy type 1 bitmap after v2 bitmap
        oldBitmapTypeV1.width=0;
		oldBitmapTypeV1.height=0;
		oldBitmapTypeV1.rowBytes=0;

		MemMove(&oldBitmapTypeV1.flags,&zeroWord,zeroWord);					// (compressed, hasColorTable)
		oldBitmapTypeV1.pixelSize=255;    //0xff
		oldBitmapTypeV1.version=BitmapVersionOne;					
		
		oldBitmapTypeV1.nextDepthOffset=0;		// offset in longwords
		
		oldBitmapTypeV1.reserved[0]=0x00;
		oldBitmapTypeV1.reserved[1]=0x00;
	 
		
		 
		//put dummy v1 bitmap on front
		//put v3 bitmap on end		
//StrPrintF(debug,"sizeV2=%lu  sizeV1=%lu sizeV3=%lu ",MemPtrSize(bmpV2),sizeof(struct oldBitmapTypeV1Layout),MemPtrSize(bmpV3));
//dbug(debug); 
		/* 04072003
		ptr=MemPtrNew( MemPtrSize(bmpV2) + sizeof(struct oldBitmapTypeV1Layout) + MemPtrSize(bmpV3));
		if(ptr==0) OutOfMemory(6025);  //05282003
		MemMove((char*)ptr,bmpV2,MemPtrSize(bmpV2));
		MemMove((char*)ptr+MemPtrSize(bmpV2),&oldBitmapTypeV1,sizeof(struct oldBitmapTypeV1Layout));
		MemMove((char*)ptr+MemPtrSize(bmpV2)+sizeof(struct oldBitmapTypeV1Layout),bmpV3,MemPtrSize(bmpV3));
 		
		*/
		 
		
		if(PNO(romVersion)<version40)
		{
		        lenBits=MemPtrSize(bmpV3);
		}
		else    BmpGetSizes ((BitmapPtr)bmpV3,&lenBits, &lenHdr);
 		if(lenBits>63000) 
		{
		    SysFatalAlert("Signature area too large.");
		    ErrThrow(-1);                  //inserted 05212003
		    //05212003 return(MemPtrNew(1));
		}
 		ptr=MemPtrNew( sizeof(struct oldBitmapTypeV1Layout) + MemPtrSize(bmpV3));
		if(ptr==0) 
		{
		    SysFatalAlert("Out of memory formatting bitmap");
		    ErrThrow(-1);                  //inserted 05212003
		    //05212003return(MemPtrNew(1));
		}
		//MemMove((char*)ptr,bmpV2,MemPtrSize(bmpV2));
 		MemMove((char*)ptr ,&oldBitmapTypeV1,sizeof(struct oldBitmapTypeV1Layout));
 		MemMove((char*)ptr +sizeof(struct oldBitmapTypeV1Layout),bmpV3,MemPtrSize(bmpV3));
 		BmpRsrcDelete(bmpV2);
 		BmpRsrcDelete(bmpV3);
 		return ( (BitmapPtr) ptr);                            
    
    }
}
 

//*****************************************************************************************
BitmapPtr CaptureSignaturePriorToVersion35(RectangleType* theBoundsPtr )
{
//----
//#ifndef DO_NOT_ALLOW_ACCESS_TO_INTERNALS_OF_STRUCTS
//NOTE:  The structures RGBColorType, ColorTableType, FGraphicsStateType, oldGDeviceType, and oldWindowType
//     are from PalmOS prior to version 3.5

  // This is the structure of a color table. It maps pixel values into
//  RGB colors. Each element in the table corresponds to the next
//  index, starting at 0. A pointer to this table is stored in
//  the WindowExtType structure and a pointer to the WindowExtType is
//  stored in the WindowType. 
typedef struct RGBColorType {
    Byte    unused;                                    // unused, must be 0
    Byte    r;                                            // amount of red, 0->255
    Byte    g;                                            // amount of green, 0->255
    Byte    b;                                            // amount of blue, 0->255
    } RGBColorType;
    
typedef struct ColorTableType {
    Word                            numEntries;        // number of entries in table
    RGBColorType                entry[1];        // array 0->numEntries-1 of colors
    } ColorTableType;
typedef ColorTableType*     ColorTablePtr;

typedef struct {
    ScrOperation        grafMode;
    Boolean                patternMode;
    PatternType            pattern;
    CustomPatternType    customPtn;
    FontID                fontId;
    Byte                    padding1;
    FontPtr           font;
    UnderlineModeType    underlineMode;
    RGBColorType        foreColor;
    RGBColorType        backColor;
} GraphicStateType;

typedef GraphicStateType * GraphicStatePtr;
typedef struct GDeviceType {
    VoidPtr                        baseAddr;        // base address
    Word                            width;            // width in pixels
    Word                            height;            // height in pixels
    Word                            rowBytes;        // rowBytes of display
    Byte                            pixelSize;        // bits/pixel
    Byte                            version;            // version of GDeviceType
                                                        //  - this is version 0
    // Flags -----
    Word                            forDriver:1;    // true if this is the GDeviceType structure
                                                        //  used by the screen driver.
    Word                            dynamic:1;        // true if this structure was allocated
                                                        //  using MemPtrNew and needs to be freed.
    Word                            compressed:1;    // true if pixels are compressed.
    Word                            flags:13;        // unused flags - all 0 for now

    // Color Table ----
    ColorTablePtr                cTableP;            // color table. If nil, then
                                                        //  a default color table will be used. 
    } oldGDeviceType;
typedef oldGDeviceType* oldGDevicePtr;

// The Window structure.
typedef struct oldWinTypeStruct {
  Word                            displayWidthV20;        // use WinGetDisplayExtent instead
  Word                            displayHeightV20;        // use WinGetDisplayExtent instead
  VoidPtr                        displayAddrV20;        // use the drawing functions instead
  UInt16               windowFlags;     //changed 04022003
  RectangleType                windowBounds;
  AbsRectType                    clippingBounds;
  oldGDevicePtr                    gDeviceP;
  FrameBitsType               frameType;
  GraphicStatePtr                gstate;
  struct WinTypeStruct *    nextWindow;
} oldWindowType;

typedef oldWindowType * oldWinPtr;
typedef oldWinPtr           oldWinHandle;
  


//----
    WinHandle    theWindowHandle;
    Word        theError;
    BitmapPtr    theBitmapPtr = NULL;
    Word        theRowBytes, theHeight;
    
            
    // Create an offscreen window to copy the bits bounded by the gadget into.
    // This will make converting the window into a bitmap a little easier for us
    // You could just copy the screen bits directly into the bitmap, but that
    // would require more pointer arithmetic and POSE complains when you read
    // directly from the screen.
    theWindowHandle = WinCreateOffscreenWindow( theBoundsPtr->extent.x, 
                            theBoundsPtr->extent.y, screenFormat, &theError );
    
    if (!theError)
    {
        // Now, copy the gadgets screen rectangle into the new window.  This will offset
        // the screen bits to (0, 0) in the offscreen window.
        WinCopyRectangle( NULL, theWindowHandle, theBoundsPtr, 0, 0, scrCopy );
        
        // Now, this is the tricky part.  There is no API for getting the bits on the screen
        // into a bitmap, so this code is unsupported and will only work on Palm OS 2.x, 3.0, 
        // 3.1, and 3.2 devices.  This is why we limit this sample to only those versions in
        // the RomVersionCompatible function.  This code will also only work on a device with
        // a screen depth of 1.
        // WARNING:  THIS CODE IS NOT SUPPORTED CODE AND MAY NOT WORK ON DEVICES
        // WHOSE OS VERSION IS OTHER THAN 2.X, 3.0, 3.1, OR 3.2
        
        // Cache a couple of important bits of information
        theRowBytes = ((oldWinHandle)theWindowHandle)->gDeviceP->rowBytes;
        theHeight = ((oldWinHandle)theWindowHandle)->gDeviceP->height;
        
        // Now, allocate our bitmap and set all the important bits of information.
        oldBitmapPtr = MiscPtrNew( sizeof(oldBitmapType) + (theRowBytes*theHeight) ,"newBmp");
        if (oldBitmapPtr)
        {
            MemSet( oldBitmapPtr, sizeof(oldBitmapType) + (theRowBytes*theHeight), 0 );
            
            oldBitmapPtr->width = ((oldWinHandle)theWindowHandle)->gDeviceP->width;
            oldBitmapPtr->height = ((oldWinHandle)theWindowHandle)->gDeviceP->height;
            oldBitmapPtr->rowBytes = ((oldWinHandle)theWindowHandle)->gDeviceP->rowBytes;
            oldBitmapPtr->pixelSize = ((oldWinHandle)theWindowHandle)->gDeviceP->pixelSize;
            oldBitmapPtr->nextDepthOffset = NULL;
            
            // CreateOffscreenWindow does not, by default, create a compressed window
            oldBitmapPtr->flags.compressed = ((oldWinHandle)theWindowHandle)->gDeviceP->compressed;
            
            // All bitmaps are version 1 bitmaps without a color table.
            oldBitmapPtr->version = 1;
            oldBitmapPtr->flags.hasColorTable = 0;
            
            // Move the offscreen bits into our bitmap.  The baseAddr field
            // contains the bit array of our bitmap for 1-bit, uncompressed bitmaps.
            MemMove( (Ptr)((ULong)(oldBitmapPtr) + sizeof(oldBitmapType)), 
                        ((oldWinHandle)theWindowHandle)->gDeviceP->baseAddr, theRowBytes * theHeight );
        }
        
        // Delete the window that we created with WinCreateOffscreenWindow
        WinDeleteWindow( theWindowHandle, false );
    }
    
    // Finally, return our bitmap 
    return (BitmapPtr)oldBitmapPtr;
//#endif
}


/***********************************************************************
*
* FUNCTION:        GetSignatureGadgetBounds
*
* DESCRIPTION:     This routine grabs the bounds of the signature gadget
*
* PARAMETERS:      theBoundsPtr - the bounds of the gadget
*
* RETURNED:        nothing
*
***********************************************************************/
void GetSignatureGadgetBounds( RectangleType* theBoundsPtr )
{
    FormPtr            theFormPtr;
    FormGadgetType*    theGadgetPtr;
    
    theFormPtr = FrmGetActiveForm();
    theGadgetPtr = GetObjectPtr( sigCaptureCtlId );
    
    FrmGetObjectBounds( theFormPtr, 
            FrmGetObjectIndex(theFormPtr, sigCaptureCtlId), theBoundsPtr );
}

/***********************************************************************
*
* FUNCTION:        CaptureSignature
*
* DESCRIPTION:     This routine captures the signature and draws it on the 
*                        screen
*
* PARAMETERS:      None
*
* RETURNED:        nothing
*
***********************************************************************/
void CaptureSignature()
{
    SWord                x, y, prevX, prevY;
    Boolean                penDown;
    RectangleType        theClipRectangle;
    RectangleType        theGadgetBounds;
    
    // Grab the gadget's bounds
    GetSignatureGadgetBounds( &theGadgetBounds );
    
    // Grab the coordinates of the pen
    EvtGetPen( &prevX, &prevY, &penDown );
        
    // Save off the current clip rectangle and set the new clipping
    // rectangle to be the bounds of the signature gadget.
    WinGetClip( &theClipRectangle );
    WinSetClip( &theGadgetBounds );
    
    // Track the pen
    do
    {
        EvtGetPen(&x, &y, &penDown);
        
        // Don't bother to do anything if the user hasn't moved
        // the pen!
        if ((x != prevX || y != prevY))
        {
            WinDrawLine( prevX, prevY, x, y );
        
            prevX = x;
            prevY = y;
        }
    } while (penDown);

        
    // Restore the old clipping rectangle
    WinSetClip( &theClipRectangle );
}
/***********************************************************************
*
* FUNCTION:        DrawSignature
*
* DESCRIPTION:     This routine draws the signature from its bitmap
*                        
* PARAMETERS:      Bitmap to draw
*
* RETURNED:        nothing
*
***********************************************************************/
void DrawSignature(VoidHand *bitmapHand, struct oldBitmapType* gBitmapPtr, RectangleType theBounds)
{

//---
//#ifndef DO_NOT_ALLOW_ACCESS_TO_INTERNALS_OF_STRUCTS
//NOTE:  The structures RGBColorType, ColorTableType, FGraphicsStateType, oldGDeviceType, and oldWindowType
//     are from PalmOS prior to version 3.5

  // This is the structure of a color table. It maps pixel values into
//  RGB colors. Each element in the table corresponds to the next
//  index, starting at 0. A pointer to this table is stored in
//  the WindowExtType structure and a pointer to the WindowExtType is
//  stored in the WindowType. 
typedef struct RGBColorType {
    Byte    unused;                                    // unused, must be 0
    Byte    r;                                            // amount of red, 0->255
    Byte    g;                                            // amount of green, 0->255
    Byte    b;                                            // amount of blue, 0->255
    } RGBColorType;
    
typedef struct ColorTableType {
    Word                            numEntries;        // number of entries in table
    RGBColorType                entry[1];        // array 0->numEntries-1 of colors
    } ColorTableType;
typedef ColorTableType*     ColorTablePtr;

typedef struct {
    ScrOperation        grafMode;
    Boolean                patternMode;
    PatternType            pattern;
    CustomPatternType    customPtn;
    FontID                fontId;
    Byte                    padding1;
    FontPtr           font;
    UnderlineModeType    underlineMode;
    RGBColorType        foreColor;
    RGBColorType        backColor;
} GraphicStateType;

typedef GraphicStateType * GraphicStatePtr;
typedef struct GDeviceType {
    VoidPtr                        baseAddr;        // base address
    Word                            width;            // width in pixels
    Word                            height;            // height in pixels
    Word                            rowBytes;        // rowBytes of display
    Byte                            pixelSize;        // bits/pixel
    Byte                            version;            // version of GDeviceType
                                                        //  - this is version 0
    // Flags -----
    Word                            forDriver:1;    // true if this is the GDeviceType structure
                                                        //  used by the screen driver.
    Word                            dynamic:1;        // true if this structure was allocated
                                                        //  using MemPtrNew and needs to be freed.
    Word                            compressed:1;    // true if pixels are compressed.
    Word                            flags:13;        // unused flags - all 0 for now

    // Color Table ----
    ColorTablePtr                cTableP;            // color table. If nil, then
                                                        //  a default color table will be used. 
    } oldGDeviceType;
typedef oldGDeviceType* oldGDevicePtr;

// The Window structure.
typedef struct oldWinTypeStruct {
  Word                            displayWidthV20;        // use WinGetDisplayExtent instead
  Word                            displayHeightV20;        // use WinGetDisplayExtent instead
  VoidPtr                        displayAddrV20;        // use the drawing functions instead
  UInt16                windowFlags;       //changed 04022003
  RectangleType                windowBounds;
  AbsRectType                    clippingBounds;
  oldGDevicePtr                    gDeviceP;
  FrameBitsType               frameType;
  GraphicStatePtr                gstate;
  struct WinTypeStruct *    nextWindow;
} oldWindowType;

typedef oldWindowType * oldWinPtr;
typedef oldWinPtr           oldWinHandle;
//#endif  
//09232002---
typedef struct oldBitmapType
//#ifdef ALLOW_ACCESS_TO_INTERNALS_OF_BITMAPS	// These fields will not be available in the next OS release!
{
	Int16  				width;
	Int16  				height;
	UInt16  				rowBytes;
	oldBitmapFlagsType	flags;
	UInt8					pixelSize;			// bits/pixel
	UInt8					version;				// version of bitmap. This is vers 2
	UInt16	 			nextDepthOffset;	// # of DWords to next BitmapType
													//  from beginnning of this one
	UInt8					transparentIndex;	// v2 only, if flags.hasTransparency is true,
													// index number of transparent color
	UInt8					compressionType;	// v2 only, if flags.compressed is true, this is
													// the type, see BitmapCompressionType
														
	UInt16	 			reserved;			// for future use, must be zero!
	
	// if (flags.hasColorTable)
	//	  ColorTableType	colorTable		// NOTE: Could have 0 entries (2 bytes long)
	//
	// if (flags.directColor)
	//	  BitmapDirectInfoType	directInfo;
	// 
	// if (flags.indirect)
	//	  void*	  bitsP;						// pointer to actual bits
	// else
	//    UInt8	  bits[];					// or actual bits
	//
}
//#endif
oldBitmapType;

typedef oldBitmapType* oldBitmapPtr;
//09232002 end-of-additions----
//---
char bitFlags[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
    oldBitmapPtr newBitmapPtr;
    char * oldptr;
    char * oldp;
    char * newptr;
    char * newp;
    int    oldbit;
    int    newbit;
    //09232002 int    depth;
    int    pix;
    int    row;
    int i;
    Coord width;
    Coord height;
    UInt16 rowBytes;
    unsigned long ul1;
    UInt8 depth;   //09232002
   
   
   
    // Draw a frame around our gadget so that users know where to sign
    WinDrawRectangleFrame( simpleFrame, &theBounds );
     
    // Draw the signature bitmap if it exists 
    
    if (gBitmapPtr==0) return;
    BmpGlueGetDimensions ((struct BitmapType*)gBitmapPtr,&width,&height,&rowBytes);    //09232002
//StrPrintF(debug,"draw  w=%d h=%d rowBytes=%c",width,height,rowBytes);
//dbug(debug);
    depth=BmpGlueGetBitDepth ((struct BitmapType*)gBitmapPtr);
 
    if (PNO(romVersion)<version35)
    {
//#ifndef DO_NOT_ALLOW_ACCESS_TO_INTERNALS_OF_STRUCTS
    	//09232002if (gBitmapPtr->pixelSize>1)

    	if (depth>1)     //09232002
        {
//dbug("its in color");
           //its a color bitmap to display on a pre-3.5 OS -- need to convert bitmap to b&W
           *bitmapHand=MiscHandleNew(MemPtrSize(gBitmapPtr),"bitm");
           newBitmapPtr=(oldBitmapType*)MiscHandleLock(*bitmapHand);
           
           MemSet(newBitmapPtr,MemPtrSize(newBitmapPtr),0x00);   //initialize it to all bits off
           MemMove(newBitmapPtr,gBitmapPtr,16);   //copy the header info
           newBitmapPtr->pixelSize=1;    //change to a B&W image
           
           newBitmapPtr->rowBytes=(newBitmapPtr->width+7)/8;  //compute new # bytes to hold one row of bits
           i=newBitmapPtr->rowBytes/2;
           if( 2*i != newBitmapPtr->rowBytes) ++newBitmapPtr->rowBytes;  //round to even number of bytes

           oldptr=(char*)gBitmapPtr+16-gBitmapPtr->rowBytes;      //position by the header info
           newptr=(char*)newBitmapPtr+16-newBitmapPtr->rowBytes;         //position by header
           for(row=0;row<gBitmapPtr->height;++row)
           {
               oldptr=oldptr+gBitmapPtr->rowBytes;             //position forward one row of bits
               oldbit=0;
               oldp=oldptr;
               newptr=newptr+newBitmapPtr->rowBytes;
               newp=newptr;                                   
               newbit=0;
             
               for(pix=0;pix<gBitmapPtr->width;++pix)
               {
                 //repeats for each depth of the color image

                 for( depth=0;depth<gBitmapPtr->pixelSize;++depth)
                 {
                   if(depth!=7)
                   {
                      if(*oldp & bitFlags[oldbit])
                      {
                        //the pixels on, so modify the new bitmap
                        *newp=*newp | bitFlags[newbit];
                      }
                   }
                   if(oldbit==7) {oldbit=0; ++oldp;}   //bump to next byte of old bitmap
                   else          ++oldbit;             //or just to the next bit of old bitmap
                    
                 }
                 if(newbit==7) {newbit=0; ++newp;}   //same for new bitmap
                 else          ++newbit;  
               } 
           }
        
           if(MemPtrResize(newBitmapPtr,16+newBitmapPtr->rowBytes*newBitmapPtr->height) !=0) OutOfMemory(6024); //05282003;
           WinDrawBitmap( (struct BitmapType*)newBitmapPtr, theBounds.topLeft.x, theBounds.topLeft.y );
           MemPtrFree(gBitmapPtr);
       
           (struct BitmapType*)gBitmapPtr=(struct BitmapType*)newBitmapPtr;
       }
       else
       {
           //B&W
//dbug("its B&W");
           goto drawNoConversion;
       }
//#endif  
    }
    else 
    {
//dbug("drawing new style");
drawNoConversion:
       WinDrawBitmap( (struct BitmapType*)gBitmapPtr, theBounds.topLeft.x, theBounds.topLeft.y );
    }
  return;
}

//*****************************************************************************************
VoidPtr CompressBitmap( VoidPtr bmp )
{

    long len; 
    char * temp;
    char* adtemp;
    char *adbmp;
    long newlen=0;
    char theChar;
    UInt8 cnt; 
    Err err;
    VoidHand hand;
    long offset;
    UInt32 theLen;

    len=MemPtrSize(bmp); 
    
   
//StrPrintF(debug,"abc2  len=%lu",len);
//dbug(debug);
    if(len>(long)(64l*2l/3l*1024l))
    {
       theLen=63l*1024l;
//StrPrintF(debug,"abc3  len=%lu",theLen);
//dbug(debug);
       hand=MemHandleNew(theLen);  //04072003 to keep from exceeding 64k
    }
    else
    {
       theLen=len*3l/2l;
//StrPrintF(debug,"abc4  len=%lu",theLen);
//dbug(debug);
       hand=MemHandleNew(theLen);  //04072003   
    } 
    if(hand==0)
    {
        misc_text_abort("Out of memory trying to compress bitmap.");
    }
    temp=MemHandleLock(hand);
    if(temp==0)
    {
        misc_text_abort("Out of memory trying to compress bitmap.");
    }

    adtemp=temp;
    adbmp=(char*)bmp;
//StrPrintF(debug,"compress len=%lu bmp=%lu temp=%lu", len,adbmp,adtemp);
//dbug(debug);

   while(1)
    {
       if (adbmp>= ((char*)bmp+len)) break;
       cnt=1;
       theChar=*adbmp++; //OS5: Error, read from BitmapType
       
       while(  (adbmp< ((char*)bmp+len)) && (*adbmp==theChar) )
       {
           ++adbmp;
           ++cnt;
           if(cnt==255) break;
       }
       if( (adtemp-temp)>  (MemPtrSize(temp)-10))
       {
          offset=adtemp-temp;
          MemPtrUnlock(temp);
//dbug("resizing");
          if(MemHandleResize(hand,MemHandleSize(hand)+1000) !=0) OutOfMemory(6020); //05282003
          temp=MemHandleLock(hand);
          adtemp=temp+offset;
       }
       
       
       *(adtemp++)=cnt;
       
       if(theChar==0x00)  //cant let oxoo in stream or it terminates string
       {
           *(adtemp++)=0x01;
           *(adtemp++)=0x02;
       }
       else
       {
          if(theChar==0x01)
          {
             *(adtemp++)=0x01;
             *(adtemp++)=0x01;
          }
          else *(adtemp++)=theChar;
       }
       
    }
    *adtemp=0x00;  //put on ending null to terminate string
//StrPrintF(debug,"after compress len=%u char1=%c",StrLen(temp),*((char*)temp));
//dbug(debug);
    if(MemPtrResize(temp, (adtemp-temp+1)) !=0) OutOfMemory(6021);  //05282003
    return (VoidPtr)temp;
}
//*****************************************************************************************
BitmapPtr  unCompress( char * string)
{
   char* adtemp;
   char * bmp;
   char* adbmp;
   int i;
   unsigned char cnt;
   int tempcnt;
   char theChar;
   long offset;
   Err err;
   UInt32 newsize;
   VoidHand hand;
   UInt32 len;
   long wklong;
   
   adtemp=string;
//StrPrintF(debug,"uncompress len=%u char1=%c string=%lu adtemp=%lu", StrLen(string),*string,string,adtemp);
//dbug(debug);   
   
   hand=MemHandleNew((StrLen(string)));
   //05282003 bmp=MemHandleLock(hand);
   if(hand==0)     //mod 05282003
   {
//dbug("out of mem at point a");
      misc_text_abort("Out of memory");
   }
   bmp=MemHandleLock(hand);     //05282003
   adbmp=(char*)bmp;
//StrPrintF(debug,"uncompress cnt=%d",StrLen(string));
//dbug(debug);   
   while(*adtemp!=0x00)
   {
       
       cnt=*adtemp++;
//wklong=cnt;

       if( (MemPtrSize(bmp)-(adbmp-bmp)) <  (cnt+5))
       {
          newsize=MemPtrSize(bmp)+1000+cnt;
//StrPrintF(debug, "Resizing  bmp=%lu adbmp=%lu adtemp=%lu to len=%lu ", (char*)bmp,adbmp,adtemp,newsize);
//dbug(debug);
          offset=adbmp-(char*)bmp;
          
          hand=MemPtrRecoverHandle(bmp);
//StrPrintF(debug,"before resize handLen=%lu",MemHandleSize(hand));
//dbug(debug);
          MemHandleUnlock(hand);
          err=MemHandleResize(hand, newsize);
          if(err!=0)  OutOfMemory(6022);   //05282003
//StrPrintF(debug,"after resize handLen=%lu",MemHandleSize(hand));
//dbug(debug);          
          bmp=MemHandleLock(hand);
          
//StrPrintF(debug, "err=%lu outofspace=%lu  chunkLocked=%lu invalParm=%lu",err,memErrNotEnoughSpace,memErrChunkLocked,memErrInvalidParam);
//dbug(debug);          
          if((bmp==0)||(err!=0)) misc_text_abort("Out of memory");
          (char*)adbmp=(char*)bmp+offset;
//wklong=adbmp-bmp;
//StrPrintF(debug,"offset=%lu adbmp=%lu bmp=%lu  recalc=%lu",offset,&adbmp,&bmp,wklong);
//dbug(debug);
      }  
        if(*adtemp == 0x01) 
        {
           ++adtemp;
       
           if(*adtemp==0x02) theChar=0x00;
           else              theChar=0x01;
        }
        else                 theChar=*adtemp;
           
       ++adtemp;
//tempcnt=cnt;
//StrPrintF(debug,"inserting char=%x cnt=%d",theChar,tempcnt);
//dbug(debug);
       for(i=0;i<cnt;++i) *(adbmp++)=theChar;
   }
   len=(char*)adbmp-(char*)bmp;
//StrPrintF(debug,"resize at end uncompress   len=%lu  bmp=%lu adbmp=%lu",len,&bmp,&adbmp);
//dbug(debug);
   if(MemPtrResize( bmp, len) !=0)  OutOfMemory(6023);  //05282003
//dbug("returning from uncompress");
   return( (BitmapPtr)bmp);
} 
//*****************************************************************************************
void commonErase(FormPtr frmPtr, int controlid)
{
   sigCaptureCtlId=controlid;
   sigCaptureFormId=FrmGetFormId(frmPtr);
   clearSignature();   
}  
//*****************************************************************************************
void verb_signatureErase()
{
   FormPtr frmPtr;
   find_ctlid(true);      //gadget control
   frmPtr=FrmGetActiveForm();
   commonErase(frmPtr,PNO(controlid));
}  
//*****************************************************************************************
void commonStartCapture(FormPtr frmPtr, int controlid)
{
   RectangleType r;
   sigCaptureCtlId=controlid;
   sigCaptureFormId=FrmGetFormId(frmPtr);
   sigCaptureSw=true;
   GetSignatureGadgetBounds( &r );
   WinDrawRectangleFrame( simpleFrame, &r );  
}

//*****************************************************************************************
void verb_signatureStartCapture()
{
   FormPtr frmPtr;
   
   find_ctlid(true);      //gadget control 
   frmPtr=FrmGetActiveForm();
   commonStartCapture(frmPtr, PNO(controlid));  
}

//*****************************************************************************************
void commonEndCapture(FormPtr frmPtr, struct dataelem **de, Int16 occ1,
	Int16 occ2, Int16 occ3, Int16 controlid)
{
   RectangleType r;
   BitmapPtr bmp;
   VoidPtr compressed;

   sigCaptureSw=false;
//SysFatalAlert("going to bounds");
   GetSignatureGadgetBounds( &r );
   
//SysFatalAlert("going to get bitmap");
   bmp=GetSignatureBitmap( &r );
//SysFatalAlert("going to compress");
   compressed=CompressBitmap( bmp );
//SysFatalAlert("after compress");

#if 0
   misc_stostr4(compressed);   //return the bitmap as a string
#else
	misc_stostr(de, occ1, occ2, occ3, compressed);	// Changed to make PNO friendly
#endif
//SysFatalAlert("after store string");
   MemPtrFree(bmp);
//SysFatalAlert("after bmp free");
   MemPtrFree(compressed);
//SysFatalAlert("after free compressed");
}
//*****************************************************************************************
void verb_func_signatureEndCapture()  //careful--this is a function
{
   FormPtr frmPtr;
   frmPtr=FrmGetActiveForm();
   commonEndCapture(frmPtr, &arg4,arg4_occ1,arg4_occ2,arg4_occ3, PNO(controlid));
}
//*****************************************************************************************
void commonSignatureDisplay(FormPtr frmPtr, char *argx_val, int controlid)
{
  VoidHand bmpHand;
    unsigned long len;
    RectangleType r;
    BitmapPtr bmp;
    //len=StrLen(arg1_val);
//StrPrintF(debug,"display len=%lu",len);
//dbug(debug);    
    bmp=unCompress( argx_val);
//dbug("uncompressed");
    sigCaptureCtlId=controlid;
    sigCaptureFormId=FrmGetFormId(frmPtr);
    sigCaptureSw=false;
    GetSignatureGadgetBounds( &r );
//dbug("have bounds");
    bmpHand=MemPtrRecoverHandle(bmp);
//dbug("going to drawThesignature");
    DrawSignature(&bmpHand,(struct oldBitmapType*)bmp,r);
//dbug("back from draw");
    MemPtrUnlock(bmp);
    MemHandleFree(bmpHand);
   
}

//*****************************************************************************************
void verb_signatureDisplay()
{
    FormPtr frmPtr;
    find_ctlid(true);      //gadget control
    find_arg_1();      //text string of image to display
    frmPtr=FrmGetActiveForm();
    commonSignatureDisplay(frmPtr, arg1_val, PNO(controlid));
}






//added 03102003
Boolean seeIfHighDensityDisplay()
{
       
	UInt32 winVersion;
	Err error;
	UInt32 density;
	 
	error = FtrGet(sysFtrCreator, sysFtrNumWinVersion,	&winVersion);
	// If winVersion is >= 4, the high-density feature set
	// is present. Check what type of display we are on
	// and load the appropriate font resource.
	if (!error && (winVersion >= 4))  
	{
    	error = WinScreenGetAttribute(winScreenDensity, &density);
	    if (!error && (density != kDensityLow)) 
	    {
            return(true);  //high-density
        }
    }    
    return(false);

}