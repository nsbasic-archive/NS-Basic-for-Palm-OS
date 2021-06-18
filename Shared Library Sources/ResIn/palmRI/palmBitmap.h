
//-----------------------------------------------
// The Bitmap Structure. - copied from palm bitmap.h library
//-----------------------------------------------

#define UInt32 unsigned int
#define UInt16 unsigned short
#define Int16 short
#define UInt8 unsigned char

// bitmap version numbers
#define BitmapVersionZero	0
#define BitmapVersionOne	1
#define BitmapVersionTwo	2
#define BitmapVersionThree	3

// Compression Types for BitMap BitmapVersionTwo.
typedef enum {
	BitmapCompressionTypeScanLine = 0,
	BitmapCompressionTypeRLE,
	
	BitmapCompressionTypeNone = 0xFF
} BitmapCompressionType;

typedef struct BitmapFlagsType {
	UInt16 compressed:1;  			// Data format:  0=raw; 1=compressed
	UInt16 hasColorTable:1;			// if true, color table stored before bits[]
	UInt16 hasTransparency:1;		// true if transparency is used
	UInt16 indirect:1;				// true if bits are stored indirectly
	UInt16 forScreen:1;				// system use only
	UInt16 reserved:11;
} BitmapFlagsType;

// this definition correspond to the 'Tbmp' and 'tAIB' resource types
/*
typedef struct BitmapType {
	Int16  				width;
	Int16  				height;
	UInt16  				rowBytes;
	BitmapFlagsType	flags;
	UInt8					pixelSize;			// bits/pixel
	UInt8					version;				// version of bitmap. This is vers 2

	//
	union
	{
	struct //V3
	{
	// version 3 fields
	UInt8					size;						// size of this structure in bytes (0x16)
	UInt8					pixelFormat;			// format of the pixel data, see pixelFormatType
	UInt8					unused;
	UInt8					compressionType;		// see BitmapCompressionType
	UInt16					density;					// used by the blitter to scale bitmaps
	UInt32					transparentValue;		// the index or RGB value of the transparent color
	UInt32					nextBitmapOffset;		// byte offset to next bitmap in bitmap family
	};
	//
	struct // V2
	{
	UInt16	 			nextDepthOffset;	// # of DWords to next BitmapType
											//  from beginnning of this one
	UInt8				transparentIndex;	// v2 only, if flags.hasTransparency is true,
											// index number of transparent color
	UInt8				compressionType;	// v2 only, if flags.compressed is true, this is
											// the type, see BitmapCompressionType
	UInt16	 		 	reserved;			// for future use, must be zero!
	};
	};
	// [colorTableType] pixels | pixels*
	                                    // If hasColorTable != 0, we have:
	                                    //   ColorTableType followed by pixels. 
													// If hasColorTable == 0:
	                                    //   this is the start of the pixels
	                                    // if indirect != 0 bits are stored indirectly.
	                                    //	  the address of bits is stored here
	                                    //   In some cases the ColorTableType will
	                                    //   have 0 entries and be 2 bytes long.
} BitmapType;

typedef BitmapType *BitmapPtr;
*/
// VU
// This data structure is the PalmOS 5 version 3 BitmapType.
typedef struct BitmapTypeV3
{
	// BitmapType
	Int16  				width;
	Int16  				height;
	UInt16  				rowBytes;
	BitmapFlagsType	flags;					// see BitmapFlagsType
	UInt8					pixelSize;				// bits per pixel
	UInt8					version;					// data structure version 3
	
	// version 3 fields
	UInt8					size;						// size of this structure in bytes (0x16)
	UInt8					pixelFormat;			// format of the pixel data, see pixelFormatType
	UInt8					unused;
	UInt8					compressionType;		// see BitmapCompressionType
	UInt16					density;					// used by the blitter to scale bitmaps
	UInt32					transparentValue;		// the index or RGB value of the transparent color
	UInt32					nextBitmapOffset;		// byte offset to next bitmap in bitmap family

	// if (flags.hasColorTable)
	//		{
	//		if (flags.indirectColorTable)
	//			ColorTableType* colorTableP;	// pointer to color table
	//		else
	//	  		ColorTableType	colorTable;		// color table, could have 0 entries (2 bytes long)
	//		}
	//
	// if (flags.indirect)
	//	  	void*	  bitsP;							// pointer to actual bits
	// else
	//   	UInt8	  bits[];						// or actual bits
	//
} BitmapTypeV3;
typedef BitmapTypeV3* BitmapPtrV3; 

typedef struct BitmapTypeV2
 	{
	// BitmapType
 	Int16  					width;
	Int16  					height;
	UInt16  				rowBytes;
	BitmapFlagsType	flags;					// (compressed, hasColorTable, hasTransparency, indirect, forScreen, directColor)
	UInt8					pixelSize;
	UInt8					version;					
	
	// version 2 fields
	UInt16	 				nextDepthOffset;		// offset in longwords
	UInt8					transparentIndex;	
	UInt8					compressionType;
	UInt16	 				reserved;
	
	// if (flags.hasColorTable)
	//	  ColorTableType	colorTable			// color table, could have 0 entries (2 bytes long)
	//
	// if (flags.directColor)
	//	  BitmapDirectInfoType	directInfo;
	// 
	// if (flags.indirect)
	//	  void*	  bitsP;							// pointer to actual bits
	// else
	//    UInt8	  bits[];						// or actual bits
	//
}BitmapTypeV2;
typedef BitmapTypeV2* BitmapPtrV2;

//

// This is the structure of a color table. It maps pixel values into
//  RGB colors. Each element in the table corresponds to the next
//  index, starting at 0.

typedef struct RGBColorType {
	UInt8	index;									// index of color or best match to cur CLUT or unused.
	UInt8	r;											// amount of red, 0->255
	UInt8	g;											// amount of green, 0->255
	UInt8	b;											// amount of blue, 0->255
} RGBColorType;


typedef struct ColorTableType {
														// high bits (numEntries > 256) reserved
	UInt16						numEntries;		// number of entries in table
	// RGBColorType			entry[];			// array 0..numEntries-1 of colors
														// starts immediately after numEntries
} ColorTableType;


// get start of color table entries aray given pointer to ColorTableType
#define ColorTableEntries(ctP)	((RGBColorType *)((ColorTableType *)(ctP)+1))
