extern Err NSBLifeDriveLibOpen(UInt16 refNum   			)
				SAMPLE_LIB_TRAP(sysLibTrapOpen);
extern Err NSBLifeDriveLibClose(UInt16 refNum  			)
				SAMPLE_LIB_TRAP(sysLibTrapClose);
extern Err NSBLifeDriveLibSleep(UInt16 refNum  			)
				SAMPLE_LIB_TRAP(sysLibTrapSleep);
extern Err NSBLifeDriveLibWake(UInt16 refNum   			)
				SAMPLE_LIB_TRAP(sysLibTrapWake);
extern Err BrowserPresent(UInt16 refNum, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 0);
extern Err BrowserOpenDialog(UInt16 refNum, UInt16 *volume, char *path, char *extensions, char *title, UInt16 *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 1);
extern Err BrowserSaveDialog(UInt16 refNum, UInt16 *volume, char *path, char *extensions, char *title, UInt16 *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 2);
extern Err PhotoPresent(UInt16 refNum, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 3);
extern Err PhotoAlbumCount(UInt16 refNum, UInt16 vRefNum, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 4);
extern Err PhotoAlbumID(UInt16 refNum, UInt16 vRefNum, UInt16 index, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 5);
extern Err PhotoAlbumName(UInt16 refNum, UInt16 albumID, char *name)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 6);
extern Err PhotoNewAlbum(UInt16 refNum, UInt16 vRefNum, char *name, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 7);
extern Err PhotoRenameAlbum(UInt16 refNum, UInt16 albumID, char *name, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 8);
extern Err PhotoDeleteAlbum(UInt16 refNum, UInt16 albumID, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 9);
extern Err PhotoDeleteAlbumAndContents(UInt16 refNum, UInt16 albumID, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 10);
extern Err PhotoImageCount(UInt16 refNum, UInt16 albumID, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 11);
extern Err PhotoSelectFromAlbum(UInt16 refNum, UInt16 albumID, UInt16 start, UInt16 number)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 12);
extern Err PhotoSelectImage(UInt16 refNum)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 13);
extern Err PhotoSelectImages(UInt16 refNum)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 14);
extern Err PhotoSelectVideo(UInt16 refNum)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 15);
extern Err PhotoSelectVideos(UInt16 refNum)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 16);
extern Err PhotoSelectNone(UInt16 refNum)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 17);
extern Err PhotoSelectionCount(UInt16 refNum, UInt16 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 18);
extern Err PhotoSelectedImage(UInt16 refNum, UInt16 which, UInt32 *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 19);
extern Err PhotoDisplayImage(UInt16 refNum, UInt32 imageH, UInt16 left, UInt16 top, UInt16 width, UInt16 height)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 20);
extern Err PhotoImageName(UInt16 refNum, UInt32 imageH, char *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 21);
