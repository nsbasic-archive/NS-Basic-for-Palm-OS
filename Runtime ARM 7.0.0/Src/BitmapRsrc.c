/***********************************************************************
 *
 Sample Code Disclaimer

 Copyright © 2002 PalmSource, Inc. or its subsidiaries.  All
 rights reserved.

 You may incorporate this sample code (the "Code") into your applications
 for Palm OS(R) platform products and may use the Code to develop
 such applications without restriction.  The Code is provided to you on
 an "AS IS" basis and the responsibility for its operation is 100% yours.
 PALMSOURCE, INC. AND ITS SUBSIDIARIES (COLLECTIVELY, "PALMSOURCE") DISCLAIM
 ALL WARRANTIES, TERMS AND CONDITIONS WITH RESPECT TO THE CODE, EXPRESS,
 IMPLIED, STATUTORY OR OTHERWISE, INCLUDING WARRANTIES, TERMS OR
 CONDITIONS OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 NONINFRINGEMENT AND SATISFACTORY QUALITY.  You are not permitted to
 redistribute the Code on a stand-alone basis and you may only
 redistribute the Code in object code form as incorporated into your
 applications.  TO THE FULL EXTENT ALLOWED BY LAW, PALMSOURCE ALSO EXCLUDES ANY
 LIABILITY, WHETHER BASED IN CONTRACT OR TORT (INCLUDING NEGLIGENCE), FOR
 INCIDENTAL, CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OF ANY
 KIND, OR FOR LOSS OF REVENUE OR PROFITS, LOSS OF BUSINESS, LOSS OF
 INFORMATION OR DATA, OR OTHER FINANCIAL LOSS ARISING OUT OF OR IN
 CONNECTION WITH THE USE OR PERFORMANCE OF THE CODE.  The Code is subject
 to Restricted Rights for U.S. government users and export regulations.
  
 SAMPLE NAME:		Bitmap Resource

 FILE:			BitmapRsrc.c

 DATE:			6/15/2002

 DESCRIPTION:		Source Code 
 
 Requires Palm OS 5 SDK (DR12) or later
 *
 *
 *****************************************************************************/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */



#include <PalmOS.h>
#include "BitmapRsrc.h"


// Just before deleting a bitmap, fill it with this byte.
// Then, if used later and error checking is on, this code 
// can detect the use of a deleted bitmap.
#define DEAD_FILL_BYTE 0xFE

#if 0
#pragma mark -
#pragma mark === Error Checking Level ===
#endif // 0


// ErrIf_() gives a fatal error on debug builds and just
// goes to the "cleanup" for non-debug builds.
#if ERROR_CHECK_LEVEL == ERROR_CHECK_FULL
#define ErrIf_(test, message) ErrFatalDisplayIf(test,message)
#define SimpleVerify_(bmp) VerifyBitmap(bmp)
#else
#define ErrIf_(test, message) if (test) goto cleanup
#define SimpleVerify_(bmp) while(false) { ; }
#endif



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static Boolean VerifyBitmap(const BmpRsrcType * bmp)
{
	// Do some basic checking.  Nothing special... just something
	// fast that will catch some of the common mistakes.

	ErrIf_(bmp==NULL, "Bitmap is NULL");
	ErrIf_(((UInt16)(bmp->v0.width) == ((DEAD_FILL_BYTE<<8) | DEAD_FILL_BYTE)),
		"Bitmap used after being deleted");
	ErrIf_(bmp->v2.version!=0 && bmp->v2.version != 1
			&& bmp->v2.version!=2 && bmp->v2.version!=3,
		"Bitmap has invalid version;  possibly corrupt bitmap or ARM-native bitmap");


	return true;

cleanup:
	return false;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if 0
#pragma mark -
#pragma mark === Private Utilities ===
#endif // 0
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline Int32 CalcRowBytes(Int16 width, Int16 pixelSize)
{
	// The number of bits is the width in pixels * the number of
	// bits used per pixel.
	Int32 numberOfBits = (Int32)width * pixelSize;


	// rowBytes is the # of bytes but must be rounded UP to an even
	// number of bytes.  By adding 15 to the number of bits,
	// dividing by 16, and then 
	// multiplying by 2 we arrive at the correct answer.
	// Instead of the painful multiply and divide sequence,
	// we can shift right by 4 and then shift left by 1
	// to achieve the same result.
	Int16 rowBytes = (numberOfBits+15) >> 4 << 1;

	

	return rowBytes;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline UInt32 romVersion()
{
	// Determin the ROM version.
	UInt32 romVersion;
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	return romVersion;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
//04022003static inline Boolean HasHighDensityAPIs()
Boolean HasHighDensityAPIs()    //added 04022003
{
	// Determins if a device has the high-density APIs.  Note that
	// some devices might have the APIs but their screens could be
	// standard (low) density.  In this, high-density offscreens
	// can still be created although their use is somewhat limited.
	//04022003return SysGetTrapAddress(sysTrapSysHighDensitySelector) != 
	//04022003		SysGetTrapAddress(sysTrapSysUnimplemented);
	return seeIfHighDensityDisplay();
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline Int32 CalcColorTableSize(const ColorTableType * ct)
{
	// Equivalent to BmpColortableSize() except this code operates
	// directly on a colortable instead of on a colortable embedded in
	// a bitmap.
	if (ct == NULL) return 0;
	else return sizeof(ColorTableType) + sizeof(RGBColorType)*ct->numEntries;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static const BitmapDirectInfoType * FindDirectInfo(const BmpRsrcV2Type * v2)
{
	// On V2 16bit bitmaps this routine finds the "directInfo" structure.
	Int32 offset = sizeof(BmpRsrcV2Type);
	if (v2->flags.indirectColorTable) offset += sizeof(void*);
	else offset += CalcColorTableSize(BmpRsrcGetColorTable((BmpRsrcType*)v2));
	return (const BitmapDirectInfoType *)(((const UInt8 *)v2) + offset);
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static Boolean IsDummyBitmap(const BmpRsrcType * bmp)
{
	// Determins if a resource bitmap is the "fake" bitmap that separates
	// the standard density bitmaps from the high density bitmaps in
	// a bitmap family.
	return (bmp != NULL
			&& BmpRsrcGetVersion(bmp) == 1
			&& (BmpRsrcGetPixelSize(bmp) == 0xFF));
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

SysAppInfoPtr 	SysGetAppInfo(SysAppInfoPtr *uiAppPP, SysAppInfoPtr *actionCodeAppPP)
							SYS_TRAP(sysTrapSysGetAppInfo);
#define memNewChunkFlagAllowLarge			0x1000	// allow >64K allocations


static void * BigMemoryAlloc(Int32 size)
{
	// Allocate a chunk of memory where the size of the memory might exceed
	// 64k.  There are a few potential problems here:
	//  (a) the memory cannot be saved to a database
	//  (b) if you forget to free the large chunk before
	//      you application quits, you will cause a MEMORY LEAK on
	//      Palm OS 5 and 5.1 .
	
	
	void * p;   //05282003
	if (size > 65500)
	{
		SysAppInfoPtr unusedAppInfoP;
		UInt16 currentOwnerID = SysGetAppInfo(&unusedAppInfoP, &unusedAppInfoP)->memOwnerID;
		return MemChunkNew(0, size, currentOwnerID | memNewChunkFlagNonMovable | memNewChunkFlagAllowLarge);
	}
	//05282003 else return MemPtrNew(size);
	p=MemPtrNew(size);           //05282003
	if(p==0) OutOfMemory(6030);  //05282003
	return(p);                   //05282003
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void BigMemoryFree(void * ptr)
{
	// Memory allocated with MemChunkNew() and MemPtrNew() can both be
	// freed with MemPtrFree().  There is never a need to call MemChunkFree().

	ErrIf_(!ptr, "Invalid memory free");
	MemPtrFree(ptr);

cleanup:
	;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if 0
#pragma mark -
#pragma mark === Create / Delete ===
#endif // 0
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
BmpRsrcType * BmpRsrcV0Create(Int16 width, Int16 height)
{
	// Pixel depth is always 1-bit (black and white).
	// No color table, transparent color is implied white.
	
	Int16 rowBytes;
	Int32 pixelDataSize, totalSize;
	BmpRsrcV0Type * bmp = NULL;

	ErrIf_(width<=0 || width>4096 || height<=0 || height>4096,
		"Improper bitmap dimensions");

	rowBytes = CalcRowBytes(width,1);
	pixelDataSize = (Int32)rowBytes * height;
	totalSize = sizeof(BmpRsrcV0Type) + pixelDataSize;


	bmp = BigMemoryAlloc(totalSize);
	ErrNonFatalDisplayIf(bmp==NULL, "Out of memory");
	if (bmp == NULL) goto cleanup;

	// This clears out everything.  The important thing is that
	// it sets all the flags to 0 (false), sets the reserved
	// bytes to 0, and sets the pixel data to zero (white).
	MemSet(bmp, totalSize, 0);

	bmp->width = width;
	bmp->height = height;
	bmp->rowBytes = rowBytes;
	
	

cleanup:
	return (BmpRsrcType*)bmp;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
BmpRsrcType * BmpRsrcV2Create(Int16 width, Int16 height,
								Int16 pixelSize,
								const ColorTableType * ct,
								const UInt8 * bits)
{
	// If bits is NULL, the bitmap will be created with one
	// chunk of memory.  Otherwise, an indirect bitmap is created and
	// the bits are allocated by the caller and DELETED after the
	// bitmap is deleted (if the bits is part of a resource, then
	// you don't delete, but the resource must be locked while the
	// bitmap is in use).
	
	// On devices with double-density support, it is preferable that
	// bitmaps be created without color tables (pass NULL for ct).
	// On older devices, bitmaps used as a destination by
	// calling WinCreateBitmapWindow() should contain a color table
	// if the pixel size of the offscreen is different than the pixel size
	// of the screen.
	

	Int16 rowBytes;
	Int32 pixelDataSize, totalSize, colorTableSize;
	BmpRsrcV2Type * bmp = NULL;
	UInt8 * ptr;

	ErrIf_(width<=0 || width>4096 || height<=0 || height>4096,
		"Improper bitmap dimensions");
	ErrIf_(pixelSize!=1 && pixelSize!=2 && pixelSize!=4
			&& pixelSize!=8 && pixelSize!=16,
			"Unsupported pixel size");


	// 16-bit bitmaps may include (surprisingly) a 256-entry colortable.
	// 1, 2, 4, and 8-bit bitmaps may include a colortable that
	// has many colors as the pixelSize can allow.
	ErrIf_(ct!=NULL && ((pixelSize==16&&ct->numEntries!=256)
			|| (pixelSize<=8 && ct->numEntries != 1<<pixelSize)),
		"Invalid colortable");


	// Note that Palm OS 3.5 doesn't support 16 bbp.  In theory,
	// you could still use the BitmapRsrc code.  You just can't use
	// the native graphics of the Palm OS to work on a 16 bbp bitmap.
	ErrIf_(romVersion() < sysMakeROMVersion(3,5,0,sysROMStageRelease,0),
		"Palm OS higher than 3.5 required for 16 bit");

	rowBytes = CalcRowBytes(width,pixelSize);
	if (bits == NULL) pixelDataSize = (Int32)rowBytes * height;
	else pixelDataSize = 4;
	totalSize = sizeof(BmpRsrcV2Type) + pixelDataSize;
	
		
	// If we have a user color table, make room for it in the
	// bitmap.
	if (ct != NULL)
	{
		colorTableSize = CalcColorTableSize(ct);
		totalSize += colorTableSize;
	}

	// If the pixelSize is 16, make room for the BitmapDirectInfoType.
	if (pixelSize == 16) totalSize += sizeof(BitmapDirectInfoType);


	bmp = BigMemoryAlloc(totalSize);
	ErrNonFatalDisplayIf(bmp==NULL, "Out of memory");
	if (bmp == NULL) goto cleanup;

	// This clears out everything in the V2 structure.
	// The important thing is that
	// it sets all the flags to 0 (false), the nextDepthOffset to
	// 0 (this isn't a "bitmap family"), the transparentIndex to
	// 0 (transparent color is white), compressionType to 0
	// (no compression) and the reserved field to 0.
	MemSet(bmp, sizeof(BmpRsrcV2Type), 0);


	bmp->width = width;
	bmp->height = height;
	bmp->rowBytes = rowBytes;
	bmp->pixelSize = pixelSize;
	bmp->version = 2;
	
	// Point ptr right after the structure.  Then,
	// as we handle color table and 16-bit structure below we
	// can increment ptr beyond those pieces.  In the end,
	// ptr will point to where the pixels go and we can clear
	// that area of memory.
	ptr = (UInt8*)(bmp+1);
	
	if (ct)
	{
		// Place the color table into the bitmap following the
		// structure.
		MemMove(ptr, ct, colorTableSize);
		ptr += colorTableSize;
		bmp->flags.hasColorTable = 1;
	}
	
	if (pixelSize == 16)
	{
		static const BitmapDirectInfoType defaultDirect
			= { 5,6,5, 0, {0,255,255,255} };
		BitmapDirectInfoType * direct = (BitmapDirectInfoType*)ptr;
		ptr += sizeof(BitmapDirectInfoType);
		*direct = defaultDirect;
		bmp->flags.directColor = 1;
	}

	
	if (bits == NULL)
	{
		// Now clear the bitmap's pixels to white.  Note that
		// white is 0xFFFF for 16-bit bitmaps but 0 for all
		// other bitmaps.
		MemSet(ptr, pixelDataSize, pixelSize==16?0xFF:0);
	}
	else
	{
		*(const UInt8**)ptr = bits;
		bmp->flags.indirect = true;
	}
	

cleanup:
	return (BmpRsrcType*)bmp;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
BmpRsrcType * BmpRsrcV3Create(Int16 width, Int16 height,
							Int16 pixelSize, const ColorTableType * ct,
							const UInt8 * bits,
							Int16 density, PixelFormatType pixelFormat
						)
{
	// If bits is NULL, the bitmap will be created with one
	// chunk of memory.  Otherwise, an indirect bitmap is created and
	// the bits is allocated by the caller and DELETED after the
	// bitmap is deleted (if the bits is part of a resource, then
	// you don't delete, but the resource must be locked while the
	// bitmap is in use).

	// On devices with double-density support, it is preferable that
	// bitmaps be created without color tables (pass NULL for ct).
	// On older devices, bitmaps used as a destination by
	// calling WinCreateBitmapWindow() should contain a color table
	// if the pixel size of the offscreen is different than the pixel size
	// of the screen.
	

	Int16 rowBytes;
	Int32 pixelDataSize, totalSize, colorTableSize;
	BmpRsrcV3Type * bmp = NULL;
	UInt8 * ptr;

	ErrIf_(width<=0 || width>4096 || height<=0 || height>4096,
		"Improper bitmap dimensions");
	ErrIf_(pixelSize!=1 && pixelSize!=2 && pixelSize!=4
			&& pixelSize!=8 && pixelSize!=16,
			"Unsupported pixel size");
	ErrIf_(density!=kDensityLow && density!=kDensityDouble, "Unsupported density");
	ErrIf_(pixelFormat<pixelFormatIndexed || pixelFormat>pixelFormatIndexedLE,
			"Unsupported pixel format");

	// 16-bit bitmaps may include (surprisingly) a 256-entry colortable.
	// 1, 2, 4, and 8-bit bitmaps may include a colortable that
	// has many colors as the pixelSize can allow.
	ErrIf_(ct!=NULL && ((pixelSize==16&&ct->numEntries!=256)
			|| (pixelSize<=8 && ct->numEntries != 1<<pixelSize)),
		"Invalid colortable");

	// If little-pixel-endian is requested, make sure the OS supports it.
	// In theory, you could still use the BitmapRsrc code.  You just can't use
	// the native graphics of the Palm OS on he bitmap.
	ErrIf_((pixelFormat==pixelFormatIndexedLE || pixelFormat==pixelFormat565LE)
			&&  romVersion() < sysMakeROMVersion(5,0,0,sysROMStageRelease,0)
			&& HasHighDensityAPIs() == false,
		"OS doesn't support little-pixel-endian btmaps");


	// See if the OS supports V3 bitmaps.  If the OS does not, you
	// could still use BitmapRsrc code to work with V3 bitmaps;  you just
	// can't use the native graphics of the Palm OS on V3 bitmaps.
	ErrIf_(HasHighDensityAPIs() == false, "OS doesn't support V3 bitmaps");


	// We'll be nice to the caller about the pixelFormat.
	// The caller can pass either of the big-pixel-endian values to
	// specify big-pixel-endian or either of the little-pixel-endian
	// values to specify little-pixel-endian.  We'll figure out
	// indexed or 565 here based on the pixelSize;
	if (pixelFormat==pixelFormatIndexed || pixelFormat==pixelFormat565)
	{
		pixelFormat = (pixelSize == 16 ? pixelFormat565 : pixelFormatIndexed);
	}
	else
	{
		if (pixelSize == 16) pixelFormat = pixelFormat565LE;
		else if (pixelSize == 8) pixelFormat = pixelFormatIndexed;  // not LE
		else pixelFormat = pixelFormatIndexedLE;
	}


	rowBytes = CalcRowBytes(width,pixelSize);
	if (bits == NULL) pixelDataSize = (Int32)rowBytes * height;
	else pixelDataSize = 4;
	totalSize = sizeof(BmpRsrcV3Type) + pixelDataSize;


	// If we have a user color table, make room for it in the bitmap.
	if (ct != NULL)
	{
		colorTableSize = CalcColorTableSize(ct);
		totalSize += colorTableSize;
	}


	bmp = BigMemoryAlloc(totalSize);
	ErrNonFatalDisplayIf(bmp==NULL, "Out of memory");
	if (bmp == NULL) goto cleanup;

	// This clears out everything in the V3 structure.
	// The important thing is that
	// it sets all the flags to 0 (false), the nextDepthOffset to
	// 0 (this isn't a "bitmap family"), the transparentIndex to
	// 0 (transparent color is white), compressionType to 0
	// (no compression) and the reserved field to 0.
	MemSet(bmp, sizeof(BmpRsrcV3Type), 0);


	bmp->width = width;
	bmp->height = height;
	bmp->rowBytes = rowBytes;
	bmp->pixelSize = pixelSize;
	bmp->version = 3;
	bmp->size = sizeof(BmpRsrcV3Type);
	bmp->pixelFormat = pixelFormat;
	bmp->density = density;
	
	
	// Point ptr right after the structure.  Then,
	// as we handle color table  we
	// can increment ptr beyond those pieces.  In the end,
	// ptr will point to where the pixels go and we can clear
	// that area of memory.
	ptr = (UInt8*)(bmp+1);
	
	if (ct)
	{
		// Place the color table into the bitmap following the
		// structure.
		MemMove(ptr, ct, colorTableSize);
		ptr += colorTableSize;
		bmp->flags.hasColorTable = 1;
	}
	
	if (pixelSize == 16)
	{
		bmp->flags.directColor = 1;  // might not need to set this for V3
	}

	if (bits == NULL)
	{
		// Now clear the bitmap's pixels to white.  Note that
		// white is 0xFFFF for 16-bit bitmaps but 0 for all
		// other bitmaps.
		MemSet(ptr, pixelDataSize, pixelSize==16?0xFF:0);
	}
	else
	{
		*(const UInt8**)ptr = bits;
		bmp->flags.indirect = true;
	}
		

cleanup:
	return (BmpRsrcType*)bmp;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
BmpRsrcType * BmpRsrcCreate(Int16 width, Int16 height,
								Int16 pixelSize, const ColorTableType * ct,
								Int16 density, PixelFormatType pixelFormat)
{
	// Create the lowest version bitmap that the input parameters will allow.
	
	// Note that if density is 72 or 144 (kDensityLow or kDensityDouble)
	// the lowest version is V3.  If
	// you pass 0 for density, then a V2 or V0 bitmap can be created.


	// By default, a NULL ct matches the screen's colortable.
	// So, just leave the colortable alone.

	// If caller specified -1 for pixelSize, then use the pixelSize of
	// the current draw window.  (Game developers might like this code.)
	if (pixelSize == -1)
	{
		pixelSize = BmpGetBitDepth(WinGetBitmap(WinGetDrawWindow()));
	}

	// If density is -1, then use the density of the current draw window.
	if (density == -1)
	{
		if (HasHighDensityAPIs())
			density = BmpGetDensity(WinGetBitmap(WinGetDrawWindow()));
		else
			density = 0;
	}
	
	// If pixelFormat is -1, use the pixelformat of the screen.
	// Note that pixelFormatIndexed and pixelFormat565 always work,
	// they just might require extra work with drawing the bitmap
	// to the screen.
	if ((Int8)pixelFormat == (Int8)-1)
	{
		if (HasHighDensityAPIs())
		{
			// Unfortunately, there is no BmpGetDensity() API.
			// The best we can do is to query the screen's
			// format and hope for the best.
			UInt32 attr;
			(void) WinScreenGetAttribute(winScreenPixelFormat, &attr);
			pixelFormat = attr;
		}
		else pixelFormat = 0;
	}



	if (density != 0 || pixelFormat == pixelFormatIndexedLE
		|| pixelFormat == pixelFormat565LE)
	{
		return BmpRsrcV3Create(width,height,pixelSize,
							ct, NULL,density,pixelFormat);
	}
	else if (pixelSize > 1 || ct != NULL)
	{
		return BmpRsrcV2Create(width,height,pixelSize,ct, NULL);
	}
	else
	{
		// Might be better to return a V2 so that you could later change
		// the transparent value.  Oh well.  If you are reading this
		// comment, then you obviously have the source code so can make
		// the change yourself...
		//     return BmpRsrcV2Create(width,height,1,NULL,NULL);
		return BmpRsrcV0Create(width,height);
	}
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void BmpRsrcDelete(BmpRsrcType * bmp)
{
	SimpleVerify_(bmp);


#if ERROR_CHECK_LEVEL == ERROR_CHECK_FULL
	// ### zero out memory for stronger error checking
	MemSet(bmp, BmpRsrcGetTotalSize(bmp), DEAD_FILL_BYTE);
#endif

	BigMemoryFree(bmp);

cleanup:
	return;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if 0
#pragma mark -
#pragma mark === Utilities ===
#endif // 0
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
Int32 BmpRsrcGetTotalSize(const BmpRsrcType * bmp)
{
	// Computes the size of the structure.  If the bitmap contains
	// "indirect" bits or "indirect" color table, then only sizeof(void*)
	// is added to the total size.  "indirect" means that the bits or
	// the colortable are pointed to by a void* in the main structure
	// instead of being in-line in the main structure.

	Int32 size = 0;

	SimpleVerify_(bmp);


	switch (BmpRsrcGetVersion(bmp))
	{
		case 0:
			size = sizeof(BmpRsrcV0Type);
			break;
		case 1:
			size = sizeof(BmpRsrcV1Type);
			break;
		case 2:
			size = sizeof(BmpRsrcV2Type);
			if (bmp->v2.flags.directColor) size += sizeof(BitmapDirectInfoType);
			break;
		case 3:
			size = bmp->v3.size;
			break;
		
		default:
			goto cleanup;
	}


	if (bmp->v0.flags.hasColorTable)
	{
		// If the colortable is just a pointer, increase size by 4.
		// Otherwise the colortable is in line with the strucure
		//  and the structure's size must be increased by the
		//  size of the entire colortable.
		if (bmp->v0.flags.indirectColorTable) size += sizeof(void*);
		else size += CalcColorTableSize(BmpRsrcGetColorTable(bmp));
	}



	// When the bits are "indirect" then the bitmap structure
	// just has a pointer to those bits.  So the total size of
	// that is just 4.
	if (bmp->v2.flags.indirect) size += sizeof(void*);
	else
	{
		if (bmp->v0.flags.compressed)
		{
			// For compressed bitmaps of type 3, the
			// first LONGWORD is the size.  For older bitmaps,
			// the size is stored only as a 16-bit entry.
			void * ptr = BmpRsrcGetBits(bmp);
			if (bmp->v2.version == 3) size += *(UInt32*)ptr;
			else size += *(UInt16*)ptr;
		}
		else
		{
			// Uncompressed bitmap.  Compute the size of the bits.
			size += (Int32)(bmp->v0.rowBytes) * bmp->v0.height;
		}
	}


cleanup:
	return size;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
UInt8 * BmpRsrcGetBits(const BmpRsrcType * bmp)
{
	// Same as BmpGetBits();

	UInt8 * ptr = NULL;
	Int32 size = 0;

	SimpleVerify_(bmp);

	switch (BmpRsrcGetVersion(bmp))
	{
		case 0:
			size = sizeof(BmpRsrcV0Type);
			break;
		case 1:
		case 2:
			size = sizeof(BmpRsrcV2Type);
			if (bmp->v2.flags.directColor) size += sizeof(BitmapDirectInfoType);
			break;
		case 3:
			size = bmp->v3.size;
			break;
		
		default:
			goto cleanup;
	}

	if (bmp->v0.flags.hasColorTable)
	{
		if (bmp->v0.flags.indirectColorTable) size += sizeof(void*);
		else size += CalcColorTableSize(BmpRsrcGetColorTable(bmp));
	}
	

	ptr = ((UInt8*)bmp) + size;
	
	if (bmp->v0.flags.indirect) ptr = *(UInt8**)ptr;

cleanup:
	return ptr;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
UInt32 BmpRsrcGetTransparentValue(const BmpRsrcType * bmp)
{
	// Same as BmpGetTransparentValue().
	
	UInt32 val = 0;

	SimpleVerify_(bmp);

	// Use a 32-bit return here to make room for 24-bit bitmaps in the future.
	switch (BmpRsrcGetVersion(bmp))
	{
		case 0:
		case 1:
			// default value of 0 is already set
			break;
		case 2:
			if (bmp->v2.pixelSize <= 8) val = bmp->v2.transparentIndex;
			else
			{
				// Find the direct info and convert the 24-bit RGB value
				// stored there into 565.
				const BitmapDirectInfoType * direct = FindDirectInfo(&bmp->v2);
				val = (direct->transparentColor.r & 0x000000F8L) << 8;
				val |= (direct->transparentColor.g & 0x000000FCL) << 3;
				val |= (direct->transparentColor.b & 0x000000F8L) >> 3;				
			}
			break;
		case 3:
			val = bmp->v3.transparentValue;
			break;
		default:
			goto cleanup;
	}

cleanup:
	return val;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
ColorTableType * BmpRsrcGetColorTable(const BmpRsrcType * bmp)
{
	// Same as BmpGetColortable().
	Int32 offset = 0;

	SimpleVerify_(bmp);
	

	switch (BmpRsrcGetVersion(bmp))
	{
		case 0:
			// no color table
			break;
		case 1:
			if (bmp->v1.flags.hasColorTable)
				offset = sizeof(BmpRsrcV1Type);
			break;
		case 2:
			if (bmp->v2.flags.hasColorTable)
				offset = sizeof(BmpRsrcV2Type);
			break;
		case 3:
			if (bmp->v3.flags.hasColorTable)
				offset = bmp->v3.size;
			break;
		
		default:
			goto cleanup;
	}


cleanup:
	if (offset)
	{
		const UInt8 * ptr = ((const UInt8 *)bmp) + offset;
		
		if (bmp->v0.flags.indirectColorTable == 0) return (ColorTableType*)ptr;
		else return *(ColorTableType**)ptr;
	}
	else return NULL;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
PixelFormatType BmpRsrcGetPixelFormat(const BmpRsrcType * bmp)
{
	PixelFormatType format = pixelFormatIndexed;

	SimpleVerify_(bmp);


	switch (BmpRsrcGetVersion(bmp))
	{
		case 0:
		case 1:
			break;
		case 2:
			if (bmp->v2.pixelSize == 16) format = pixelFormat565;
			break;
		case 3:
			format = bmp->v3.pixelFormat;
			break;
	}

cleanup:
	return format;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void BmpRsrcSetFlag(BmpRsrcType * bmp, BmpRsrcFlagEnum which, Boolean value)
{
	// Only set the flag if the bitmap format allows that flag to be set.

	// ### not allowing compressed bitmaps in this sample code
	
	// hasColorTable, indrect, forScreen, directColor, indirectColorTable
	// cannot be changed on an existing bitmap.

	SimpleVerify_(bmp);


	switch (BmpRsrcGetVersion(bmp))
	{
		case 0:
			ErrIf_(which!=kNoDitherFlag, "Invalid flag for type 0 bitmap");
			break;
		case 1:
			ErrIf_(which != kNoDitherFlag,
					"Invalid flag for type 1 bitmap");
			break;
		case 2:
			ErrIf_(which != kHasTransparencyFlag
					&& which != kNoDitherFlag,
					"Invalid flag for type 2 bitmap");
			break;
		case 3:
			ErrIf_(which != kHasTransparencyFlag
					&& which != kNoDitherFlag,
					"Invalid flag for type 3 bitmap");
			break;
	}
	
	if (value) *(UInt16*)&bmp->v0.flags |= (0x8000 >> which);
	else *(UInt16*)&bmp->v0.flags &= ~(0x8000 >> which);
	
	
cleanup:
	return;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void BmpRsrcSetTransparentValue(BmpRsrcType * bmp, UInt32 value)
{
	// Similar to BmpSetTransparentValue() except that this routine
	// does NOT set the hasTransparecy flag.  This is useful
	// when using the winOverlay, winMask, winErase modes of the
	// double-density Window Manager & blitter.  To simulate
	// the effect of BmpSetTransparentValue() you may also
	// want to issue a BmpRsrcSetFlag() to turn on the hasTransparency bit.
	
	
	SimpleVerify_(bmp);

	ErrIf_(value >= ((UInt32)1 << BmpRsrcGetPixelSize(bmp)),
		"Transparent value out of range for bitmap's pixel size");

	switch (BmpRsrcGetVersion(bmp))
	{
		case 0:
		case 1:
			// default value of 0 is already set
			ErrIf_(true, "Bitmap type1 0 and 1 don't support transparent value");
			break;
		case 2:
			if (bmp->v2.pixelSize <= 8) bmp->v2.transparentIndex = value;
			else
			{
				UInt8 r = (value >> 11) /* & 0x001F */;
				UInt8 g = (value >> 5) & 0x003F;
				UInt8 b = (value /* >> 0 */) & 0x001F;

				BitmapDirectInfoType * direct;
				direct = (BitmapDirectInfoType*)FindDirectInfo(&bmp->v2);
				
				direct->transparentColor.r = (r<<3) | (r>>2);
				direct->transparentColor.g = (g<<2) | (g>>4);
				direct->transparentColor.b = (b<<3) | (b>>2);


				// No need to set the transparentIndex.
			}
			break;
		case 3:
			bmp->v3.transparentValue = value;
			break;
		default:
			goto cleanup;
	}

cleanup:
	return;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void BmpRsrcSetDensity(BmpRsrcType * bmp, Int16 density)
{
	// Normally you wouldn't change the density of a bitmap on-the-fly.
	// It could lead to some interesting effects though....
	// Suppose you created a low-density bitmap,  used WinCreateBitmapWindow()
	// to attach a window to that offscreen bitmap, drew some text into
	// that offscreen using WinDrawChars() (this would be low-density text,
	// as the bitmap is low density),  set density of the bitmap to
	// kDensityDouble, and then WinDrawBitmap() that bitmap to the real
	// screen.  Voila!  You have just succeeded in drawing a low density
	// font to a high density display;  better get a magnifying glass to read
	// that text!

	SimpleVerify_(bmp);

	ErrIf_(BmpRsrcGetVersion(bmp) != 3,
		"Must have V3 bitmap to set density.");
	
	ErrIf_(density!=kDensityLow && density !=kDensityDouble,
		"Unsupported bitmap density.");
		
	bmp->v3.density = density;

cleanup:
	return;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if 0
#pragma mark -
#pragma mark === Drawing Utilities ===
#endif // 0
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
UInt32 BmpRsrcGetPixel(const BmpRsrcType * bmp, Int16 x, Int16 y)
{
	// Return value is 32-bit for future 24-bbp formats.
	// This code is very slow, as it handles a single pixel with lots of
	// computation overhead.  Use this code as a starting point to
	// understand how the pixels of a bitmap are ordered and how to
	// write your own high-speed code.
	
	const UInt8 * rowPtr;
	UInt32 value = -1;	// returns -1 if an error occurrs.
	Int16 pixelSize;
	
	SimpleVerify_(bmp);

	ErrIf_(x<0 || y<0 || x>=bmp->v0.width || y>=bmp->v0.height,
			"Coordinate out of range");
	ErrIf_(BmpRsrcGetFlag(bmp, kCompressedFlag),
			"can't operate on compressed bitmaps");

	// Figure out on which row the pixel lives.
	rowPtr = BmpRsrcGetBits(bmp) + (Int32)BmpRsrcGetRowBytes(bmp) * y;
	
	pixelSize = BmpRsrcGetPixelSize(bmp);
	switch (pixelSize)
	{
		case 1:
		case 2:
		case 4:
			// Convert x from pixels into bits.  Then pick the
			// correct byte.
			x *= pixelSize;
			value = rowPtr[x>>3];
			
			// Now figure out which bits within that byte we need.
			if (BmpRsrcGetPixelFormat(bmp) == pixelFormatIndexed)
			{
				x = 8 - (x & 7);
				x -= pixelSize;
			}
			else // pixelFormatIndexedLE
			{
				x = (x & 7);
			}

			// Extract the bits.
			value >>= x;
			value &= ((1<<pixelSize)-1);
			break;
		case 8:
			value = rowPtr[x];
			break;
		case 16:
			value = ((const UInt16*)rowPtr)[x];
			if (BmpRsrcGetPixelFormat(bmp) == pixelFormat565LE)
				value = ((value >> 8) | (value << 8)) & 0x0000FFFF;
			break;
	}
	
	
	

cleanup:
	return value;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void BmpRsrcSetPixel(BmpRsrcType * bmp, Int16 x, Int16 y, UInt32 value)
{
	// This code is very slow, as it handles a single pixel with lots of
	// computation overhead.  Use this code as a starting point to
	// understand how the pixels of a bitmap are ordered and how to
	// write your own high-speed code.

	// value is 32-bit for future 24-bbp formats.
	
	UInt8 * rowPtr;
	Int16 pixelSize = BmpRsrcGetPixelSize(bmp);
	
	SimpleVerify_(bmp);

	ErrIf_(x<0 || y<0 || x>=bmp->v0.width || y>=bmp->v0.height,
			"Coordinate out of range");

	ErrIf_(BmpRsrcGetFlag(bmp, kCompressedFlag),
			"can't operate on compressed bitmaps");

	ErrIf_(value >= (1L<<pixelSize), "Pixel value too large for pixelSize");

	// Figure out on which row the pixel lives.
	rowPtr = BmpRsrcGetBits(bmp) + (Int32)BmpRsrcGetRowBytes(bmp) * y;
	

	switch (pixelSize)
	{
		case 1:
		case 2:
		case 4:
			// Convert x from pixels into bits.  Then pick the
			// correct byte.
			x *= pixelSize;
			rowPtr += (x >> 3);
			
			// Now figure out which bits within that byte we need.
			if (BmpRsrcGetPixelFormat(bmp) == pixelFormatIndexed)
			{
				x = 8 - (x & 7);
				x -= pixelSize;
			}
			else // pixelFormatIndexedLE
			{
				x = (x & 7);
			}

			// Mask off the bits in the destination.
			*rowPtr &= ~(((1<<pixelSize)-1) << x);

			// Write the bits to the destination.
			*rowPtr |= (value << x);

			break;
		case 8:
			rowPtr[x] = value;
			break;
		case 16:
			if (BmpRsrcGetPixelFormat(bmp) == pixelFormat565LE)
				value = ((value >> 8) | (value << 8)) & 0x0000FFFF;
			((UInt16*)rowPtr)[x] = value;
			break;
	}
	
	
	

cleanup:
	return;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
UInt32 BmpRsrcBlackPixelValue(const BmpRsrcType * bmp)
{
	// Give a bitmap, returns the value that will result in a black pixel.
	// Assumes that colortable (if any) has the standard values.

	UInt32 value = 0;  // on error, return this value
	Int16 pixelSize = BmpRsrcGetPixelSize(bmp);
	
	SimpleVerify_(bmp);

	if (pixelSize == 16) value = 0;
	else value = (1<<pixelSize) - 1;
	
cleanup:
	return value;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
UInt32 BmpRsrcWhitePixelValue(const BmpRsrcType * bmp)
{
	// Give a bitmap, returns the value that will result in a white pixel.
	// Assumes that colortable (if any) has the standard values.

	UInt32 value = 0;  // on error, return this value
	Int16 pixelSize = BmpRsrcGetPixelSize(bmp);
	
	SimpleVerify_(bmp);

	if (pixelSize == 16) value = 0x0000FFFF;
	else value = 0;
	
cleanup:
	return value;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
IndexedColorType BmpRsrcBlackPixelIndex(const BmpRsrcType * bmp)
{
	// Suitable for use with WinSetForeColor()

	IndexedColorType value = 0;  // on error, return this value
	Int16 pixelSize = BmpRsrcGetPixelSize(bmp);

	SimpleVerify_(bmp);


	if (pixelSize == 16) value = 255;
	else value = (1<<pixelSize) - 1;
	
cleanup:
	return value;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
IndexedColorType BmpRsrcWhitePixelIndex(const BmpRsrcType * bmp)
{
	// Suitable for use with WinSetForeColor()

	SimpleVerify_(bmp);


cleanup:
	return 0;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if 0
#pragma mark -
#pragma mark === Resource Bitmap Family ===
#endif // 0
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
const BmpRsrcType * BmpRsrcGetNextMemberFromFamily(const BmpRsrcType * bmp)
{
	// Iterates through a bitmap family.
	
	const BmpRsrcType * next = NULL;
	

	SimpleVerify_(bmp);

	if (IsDummyBitmap(bmp))
	{
		next = (const BmpRsrcType *)(((const BmpRsrcV1Type *)bmp) + 1);
		
	}
	else
	{
		switch (BmpRsrcGetVersion(bmp))
		{
			case 0:
				break;
			case 1:
			case 2:
				if (bmp->v2.nextDepthOffset != 0)
					next = (const BmpRsrcType *)((UInt32*)bmp + bmp->v2.nextDepthOffset);
				break;
			case 3:
				if (bmp->v3.nextBitmapOffset != 0)
					next = (const BmpRsrcType *)((UInt8*)bmp + bmp->v3.nextBitmapOffset);
				break;
		}
	}

cleanup:
	return next;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
BmpRsrcType * BmpRsrcCreateIndirectCopy(const BmpRsrcType * bmpRsrc)
{
	
	// Create an in-memory structure that points to the pixels (and
	// optional colortable) of the resource bitmap.

	// Note well that the resouce bitmap must remain locked for the duration
	// of the created in-memory bitmap, as the in-memory bitmap
	// indirectly references the pixels (bits) of the resource bitmap
	// and the (optional) resource colortable.


	UInt8 * bits = BmpRsrcGetBits(bmpRsrc);
	Int16 density = BmpRsrcGetDensity(bmpRsrc);
	PixelFormatType pixelFormat = BmpRsrcGetPixelFormat(bmpRsrc);
	BmpRsrcType * bmp = NULL;
	UInt32 transparentValue = 0;
	Int16 width = BmpRsrcGetWidth(bmpRsrc);
	Int16 height = BmpRsrcGetHeight(bmpRsrc);
	const ColorTableType * ct = BmpRsrcGetColorTable(bmpRsrc);
	Int16 pixelSize = BmpRsrcGetPixelSize(bmpRsrc);
	int compressed = BmpRsrcGetFlag(bmpRsrc, kCompressedFlag);
	
	// Create a V2 bitmap if source bitmap is V2 or less.
	// If source bitmap is V3, then creates a V3.
	// You can change this logic here if you want to ALWAYS
	// have a V3.  Just set the createVersion variable to 3 below.
	int createVersion = (BmpRsrcGetVersion(bmpRsrc) <= 2) ? 2 : 3;
	
	
	// If the source is a compressed bitmap, deal with possible
	// mix-match between V2 and V3.  A V2 bitmap stores a SHORT
	// before the compressed data to hold the compressed data size.
	// A V3 bitmap stores a LONG betfore the compressed data to hold
	// the compressed data size.
	// We handle the situation by finding the start of the compressed data
	// and then backing up by 2 or 4 bytes to find the pointer we need
	// to send in as the start of the data including the size short or long.
	// There is a potential bug here, though.  If the new value for
	// "bits" is different from the unchanged value, then there will be
	// either a truncation of the field or the field will have garbage
	// in the top short.  Fortunately, the blitter ignores this field
	// altogether.
	if (compressed)
	{
		// Make bits skip the compression size and point to the data.
		// This is dependent on the original bitmap's version.
		if (BmpRsrcGetVersion(bmpRsrc) <= 2) bits += 2;
		else bits += 4;
		
		// Now back up bits enough for the NEW bitmap.
		// This is dependent on the NEW bitmap's version.
		if (createVersion <= 2) bits -= 2;
		else bits -= 4;
	}
	
	
	// The new bitmap will indirectly point back to the pixels (bits) of the
	// original.  This "indirect" feature is only available in v2 and v3
	// bitmaps.  Accordingly, if the version of the original is less than 2
	// then we create a V2.  This also gives the added benefit of
	// allowing you to set the transparency even if the original was 
	// v1 or v0.  You might opt to always create a v3, then you could
	// alter the density as well.
	if (createVersion <= 2)
		bmp = BmpRsrcV2Create(width,height, pixelSize, ct, bits);
	else
		bmp = BmpRsrcV3Create(width, height, pixelSize,
									ct, bits, density, pixelFormat);



	// Set the appropriate flags.
	if (compressed)
	{
		bmp->v3.flags.compressed = 1;

		// Find the compression type and then set the compression type.
		// This is done in two stages so that the versions of the original
		// and created bitmaps can be different.
		compressed = bmpRsrc->v2.version == 2
			? bmpRsrc->v2.compressionType : bmpRsrc->v3.compressionType;
		if (bmp->v2.version == 2)
			bmp->v2.compressionType = compressed;
		else
			bmp->v3.compressionType = compressed;
	}
	BmpRsrcSetFlag(bmp, kHasTransparencyFlag, BmpRsrcGetFlag(bmpRsrc, kHasTransparencyFlag));
	BmpRsrcSetFlag(bmp, kNoDitherFlag, BmpRsrcGetFlag(bmpRsrc, kNoDitherFlag));
	
	

	if (BmpRsrcGetVersion(bmpRsrc) >= 2)
		BmpRsrcSetTransparentValue(bmp, BmpRsrcGetTransparentValue(bmpRsrc));



cleanup:
	return bmp;
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static const BmpRsrcType * SelectBitmapFromFamily(const BmpRsrcType * bmp)
{
	// This is a tricky function.  It looks through a bitmap family
	// and selects the "best" one from the family for drawing to the
	// current draw window.  This function attempts to mimic the selection
	// behavior of WinDrawBitmap().  However, this code attempts to handle
	// even more than just 2 different densities even though the Window Manager's
	// code at this time only handles 2.  Accordingly, there may be differences.
	
	// One danger is that you call this routine to see what will be
	// drawn with WinDrawBitmap() but for some future OS, the algorithms
	// differ and a different bitmap family member actually gets drawn.
	// An easy way around this is
	// to use  BmpRsrcBestMemberFromFamily() instead to
	// make an in-memory copy of the best bitmap from the family.
	// Then call WinDrawBitmap() on the in-memory copy.  This will force
	// WinDrawBitmap() to use exactly the bitmap selected with this code,
	// since that bitmap will be separated out from the family.
	
	// If you have other ideas as to the "best" bitmap for a given situation,
	// modify this function.  If you modify this function, you should 
	// definitly use BmpRsrcBestMemberFromFamily(). (see previous paragraph)
	
	const BitmapType * drawBitmap;
	WinHandle drawWindow;
	Int16 drawDepth, drawDensity;
	const BmpRsrcType * bmp2;

	drawWindow = WinGetDrawWindow();
	ErrIf_(drawWindow==NULL, "no draw window");
	drawBitmap = WinGetBitmap(drawWindow);
	
	drawDepth = BmpGetBitDepth(drawBitmap);
	
	if (HasHighDensityAPIs())
		drawDensity = BmpGetDensity(drawBitmap);
	else
		drawDensity = kDensityLow;

	
	

	// Version 0 bitmaps don't have families, so just return the input bitmap.
	if (BmpRsrcGetVersion(bmp) == 0) goto cleanup;
	
	// check for dummy bitmap, and skip over it
	if (IsDummyBitmap(bmp)) bmp = BmpRsrcGetNextMemberFromFamily(bmp);
	ErrIf_(bmp==NULL, "empty bitmap family");
	
	// if there is only one bitmap, just return it
	if (BmpRsrcGetNextMemberFromFamily(bmp) == NULL) goto cleanup;



	if (HasHighDensityAPIs())
	{
		Int16 bestScore = -20000;
		// On machines that can handle high-density, we use this algorithm:
		// 1:  avoid at all cost choosing a bitmap of higher density
		//	   than the draw window's density.
		// 2:  choose color if the draw window is color;  choose grayscale
		//	   if the draw window is grayscale
		// 3:  if exact density is not available, try standard density
		// 4:  if neither exact density nor standard density are available,
		//	   choose any density
		// 5:  within color or grayscale,
		//	   select the highest depth not exceeding the draw window depth
		//	   or the lowest depth higher than the draw window depth if
		//	   lower is not available

		for (bmp2=bmp; bmp2!=NULL; bmp2=BmpRsrcGetNextMemberFromFamily(bmp2))
		{
			Int16 density, depth;
			Int16 score;
			if (IsDummyBitmap(bmp2)) continue;
			
			density = BmpRsrcGetDensity(bmp2);
			depth = BmpRsrcGetPixelSize(bmp2);
			
			score = 0;
			
			
			if (density > drawDensity)
			{
				// Rule 1:  avoid any sort of down-sampling by giving
				// downsampling such a negative score that it will
				// only be chosen as a last resort.
				score += -10000;
			}
			else if (density == drawDensity)
			{
				// Rule 3:  exact density is good
				score += 100;
			}
			else if (density == kDensityLow)
			{
				// Rule 3:  low-density is next-best behind exact density
				score += 50;
			}
			else
			{
				// Rule 4:  we're neutral to any other density
				score += 0;
			}
			
			
			
			if ((depth>=8 && drawDepth>=8) || (depth<8 && drawDepth<8))
			{
				// Rule 2:  try to match color with color and gray with gray.
				// 			Note that this scoring trumps rule 3, so
				//			we favor color / gray matching over density.
				score += 1000;
			}
			
			if (depth <= drawDepth)
			{
				// Rule 5:  extra weight to get depths within color/gray
				//			to be chosen correctly.
				score += (depth - drawDepth);
			}
			else if (depth > drawDepth)
			{
				// Rule 5 again.  We don't need to adjust the weight 
				// negatively, since bitmaps are ordered by bit depth;
				// thus the first high-depth bitmap will be selected and
				// not replaced by even-higher-depth bitmaps with other
				// equal features.	
			}
			
			if (bestScore < score)
			{
				bestScore = score;
				bmp = bmp2;
			}
		}
		

	}
	else
	{
		// The machine we're running on doesn't support
		// the high-density APIs (NOT the same as having high-density
		// API's but a low-density screen, by the way).
		// Accordingly, we only choose from standard-density bitmaps.
		// Note that standard-density  bitmaps appear first in the list.
		if (BmpRsrcGetDensity(bmp) != kDensityLow)
		{
			bmp = NULL;
			goto cleanup;
		}
		
		// The algorithm is pretty simple:  choose the highest depth
		// less than or equal to the the draw window's depth if possible.
		// If all bitmaps are higher depth than draw window, then choose
		// the lowest of those.
		// Note that bitmaps are ordered lowest-to-highest pixel size;
		// this simplifies searching.
		
		
		bmp2 = bmp;
		while (bmp2!=NULL && !IsDummyBitmap(bmp2)
				&& BmpRsrcGetPixelSize(bmp2) <= drawDepth)
		{
			bmp = bmp2;
			bmp2 = BmpRsrcGetNextMemberFromFamily(bmp2);
		}
	}


cleanup:
	return bmp;

	
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
BmpRsrcType * BmpRsrcBestMemberFromFamily(const BmpRsrcType * bmpFamily)
{
	// Iterate through bitmap family and find most appropriate bitmap to
	// draw into the current draw window.  Then create an in-memory bitmap
	// from that bitmap.
	
	// This could be useful if you wanted to know what bitmap WinDrawBitmap()
	// will draw when handed a bitmap family.  Please also see comments
	// with SelectBitmapFromFamily() routine above.
	
	// Note well that the bitmap family must remain locked for the duration
	// of the created in-memory bitmap.
	
	// Please remember to BmpRsrcDelete() the resource when you are done!
	
	// This routine isn't as inefficient as it sounds, since
	// the in-memory bitmap that is returned has indirect pointers back
	// to the color table and pixels (bits) of the original bitmap
	// from which it was cloned. Thus the colortable and the pixels
	// don't get duplicated.


	const BmpRsrcType * best = SelectBitmapFromFamily(bmpFamily);
	if (best == NULL) return NULL;

	return BmpRsrcCreateIndirectCopy(best);
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
