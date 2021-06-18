PRCExplorer 1.0.19.1
--------------------

This application is FREEWARE.

You are allowed to freely distribute it but only as the original package with all the original files. 
You are NOT allowed to sell it or make money with it in any way.
It is provided AS-IS without any warranty of any kind. Even if you use for professional purposes. You use it at your own risk.
It is NOT officially supported neither by me nor by Palm. However feel free to send questions/comments/feedback to Regis.Nicolas@PalmSource.com
The original distribution can be found at www.palmgear.com

Send any question to: <mailto:Regis.Nicolas@PalmSource.com>

What's new in 1.0.9:
--------------------
- New Zooming functionality: works for Bitmaps, Icons, Forms, Alerts, Fonts
- Improved Font viewer showing each char bitmap individually (with zoom)
- Code viewer displaying Assembly language (with trap names) in applications and extensions
- An helper DLL supporting Fonts, Palettes and Data dump has been created for viewer developers and is used.
- It's now possible to display Talt using the Form Viewer (Hold down 'Alt' while opening the Talt)
- Drawing lines when zooming beyond a value (8)
- Save/Copy bitmaps
- Dynamic sizing of viewers + support for viewers developers

What's new in 1.0.10:
---------------------
- Renamed to PRCExplorer (abandoned the idea of dumping PDB files)
- Bug fix when dropping several files
- Bug fix when a form uses Application defined font
- List resources in their type alphabetical order
- Added support for 16bit uncompressed bitmaps
- F5: refresh, Shift F5: refresh in dump mode
- Added support for 'ovly' resources
- Added binary display of database headers (plus additional fields)
- It's now possible to save a displayed PRC. That opens the door to modifying them.
- It's now possible to remove resources from a database.

What's new in 1.0.11:
---------------------
- Corrected a bug in displaying Tbsb resources (and added CRC validation)
- Fixed a bug when moving the split bar: resize of the right pane was not happening
- Improved bitmaps and forms plugin zoom
- Added staticData to plugins and changed the plugin entry point to return the plugin version which is checked.
- Added support for PackBits bitmap (de)compression
- Added support for Japanese fonts. However since MBAR viewer uses native Windows Menu, Japanese fonts do not work for them.
- Added support for graphical buttons
- Added version field in database viewer
- Moved standard Palm viewers to Palm68KViewers.dll and changed loading order

What's new in 1.0.12:
---------------------
- Added PackBits support for 16 bits bitmaps
- Fixed a bug in PackBits decompressor (4 bpp)
- Added support for High Density bitmaps and icons
- Limited the minimum size of the main window
- Fixed a bug where the scroller did not appear when switching to a bigger bitmap

What's new in 1.0.13:
---------------------
- Help Icon now shows up in the Controls list so it's possible to know which text will be displayed
- Disassembly is not limited anymore on NT, 2000, XP, ...
- Default buttons now show up with a gray background
- Clicking on a graphical button toggles the bitmap between normal and selected mode
- Sliders display their frame if bitmaps are not found in the same prc
- Form viewer improved to display form attributes and other information
- Added support for High Density fonts
- Improved Font viewer: zoom/density persistence when switching fonts
- Removed unused toolbar icons and menus

- 1.0.13 is the first PUBLIC release of PRCExplorer...


What's new in 1.0.14:
---------------------
- Added "File/Save Source" feature: It is now possible to save the rcp generated from the prc
- Added a new "Source" tab in the form viewer
- Added color support in form viewer
- Clicking on a resource while holding down 'Alt' key displays a dialog allowing to choose the viewer to use. 
  This allows to use a different viewer than the registered one for this resource or to use a viewer when none is registered.
- Improved font viewer to display the missing char

- Reorganized form viewer a little bit
- Form viewer now remembers the current tab when changing forms (useful for source)
- PRC is now the default extension in Open File dialogs
- Associated the 'libr' resource type (which are code) with the code viewer
- Displaying graphical control bounds when no bitmap is associated

- BUGFIX: Eliminated one assert when refreshing (F5)
- BUGFIX: Removed a couple of memory leaks
- BUGFIX: '\n' are not displayed as a missing char anymore
- BUGFIX: Last PRC name removed from title when closed
- BUGFIX: Lists display was showing junk
- BUGFIX: Menu viewer was displaying junk if item was finishing with '...'


What's new in 1.0.15:
---------------------
- Added support for ScanLine compressed 16 bpp bitmaps (Packbits was already supported. RLE is not).

- BUGFIX: In some case when using Drag'n'drop, the explorer was not setting the current dir as I thought it would.
  This was leading PRCExplorer not to find the viewers. Now the application directory is explicitly searched.
- BUGFIX: Fixed crash when Saving/Copying bitmaps on Win98.
- BUGFIX: Pressing Esc while on Default Res or PRC viewers was hiding them...


What's new in 1.0.16:
---------------------
- FEATURE: PRCExplorer now comes with a mini-SDK which allows you to implement your own viewers!!!
  There is no documentation yet but a Sample Viewer with it. Feel free to copy/paste :-)

- FEATURE: Save source now saves bitmaps using PilRC2.9p5 (BITMAP|ICON)FAMILYEX new keyword.
- FEATURE: It's now possible to invoke PRCExplorer from the command line to perform PRC->RCP operation.
  The syntax is: PRCExplorer filename.prc -o source.rcp [-q]
  You can convert only one file at a time. 
  -q is used so PRCExplorer does not popup an error dialog if the conversion fails.
  ERRORLEVEL is set to:
    - 0 if everything went OK, 
	- 1 if the command line parameters are invalid or misused,
	- 2 if loading or parsing the prc generated an error,
	- 3 if it was not possible to save the rcp file
- FEATURE: User defined fonts are now supported in the Form viewer for fonts defined in the same PRC
- FEATURE: Added a "Bitmap Size" field in the bitmap viewer for the currently displayed bitmap
- FEATURE: Added 'pref' and 'xprf' viewers

- BUGFIX: Fixed several problems with v3 bitmaps (especially HiRes)
- BUGFIX: Saved 16bpp bitmaps were causing some external apps to crash or hang. Fixed.
- BUGFIX: Ctrl+A, Ctrl+C now works in edit fields


What's new in 1.0.17:
---------------------
- FEATURE: Density added in the bitmap list of a bitmap family.
- FEATURE: Reload (F6): reloads the same PRC from disk and updates the display.
- FEATURE: Added support for color tables in 1, 2, 4 and 8 bpp bitmaps.
- FEATURE: Save source now saves fonts.

- BUGFIX: 16 bpp bitmaps display and transparency fixed.
- BUGFIX: The form viewer was sometimes displaying the HiRes version of some embedded bitmaps.
- BUGFIX: The bitmap viewer was displaying junk below and on the right of the image when scrolling in zoomed mode.
- BUGFIX: When switching between bitmaps families, it remembers the previously displayed bpp. Now, it also remembers the density.

What's new in 1.0.18:
---------------------
- FEATURE: It's now possible to display controls borders in the Form viewers to get their exact positions.
- FEATURE: Tables rows and columns are shown in the form viewer
- FEATURE: Controls whose text is too big to fit into what their width allows are displayed in RED
- FEATURE: Preparation work for OS5.x types (abmp, aalt, afrm, ...)

- BUGFIX: Updated my email address :-)
- BUGFIX: GDI objects leaked when drawing bitmaps

What's new in 1.0.18.5:
-----------------------
- No new features from 1.0.18 but the MFC and CRT support libraries are linked statically instead of using the DLL counterparts. 
  Nobody should still see the missing DLL error when starting PRCExplorer.
  The problem comes from msvcr70.dll and mfc70.dll being far less distributed than the 60 versions used up into version 1.0.17.
  I will eventually revert to using the DLLs but later when many more people will have them.
  I do NOT want to distribute these 2 dlls with PRCExplorer neither BTW.

What's new in 1.0.18.6:
-----------------------
- Internal release

What's new in 1.0.19:
---------------------
- FEATURE: Added support in "Save Source" for other BITMAP/ICON densities than 1 (72) and 2 (144) in particular for 1.5 (108)
- FEATURE: Added support for 1.5x fonts
- FEATURE: Added support for Font families in "Save Source" to save 'nfnt' fonts in source format
- FEATURE: Added support for sliders in "Source Tab" in the form viewer.
- FEATURE: Added context menu to Database TreeView
- FEATURE: Added support for Navigation resources ('fnav')
- FEATURE: Added support for Navigation in the Form viewer
- FEATURE: Displaying the Tip string (in addition to its ID) when clicking the 'i' button in form titles
- FEATURE: Added mouse coordinates in form viewer
- FEATURE: Added a view displaying all bitmaps in a family in the tBMP viewer
- FEATURE: Changed the viewer structure to add a callback to the host (front end). This will be extended later but already gives the possibility of fetching a resource in other loaded PRC (for resources in overlays or base)

- BUGFIX: Save source: Empty Lists in forms were missing an empty string ""
- BUGFIX: Form Bitmaps were discarded when bitmaps were not found in the same PRC. A rectangle will be displayed instead and the correct FORMBITMAP line will appear in the source.
- BUGFIX: Disassembly of MOVEM was displaying a wrong register list when from registers to memory
- BUGFIX: Reverted the change in 1.0.18.5 to link statically with MFC and CRT. This causes some memory allocation issues.

What's new in 1.0.19.1:
-----------------------
- FEATURE: Added support for bigger than 160x160 forms (up to 480x480). These form sizes can exist for DIA-aware applications

- BUGFIX: Better handling of incorrect 'fnav' resources with ID on non-existing controls - not crashing anymore
- BUGFIX: I broke -o command line option (to generate .rcp file directly without running the UI) in 1.0.19. Fixed now.
- BUGFIX: 1.0.20 version was reported incorrectly as 1.0.18.9.

TO DO:
------
-FEATURE: Find
-FEATURE: Find Resource
-FEATURE: Save source: XRD format
-FEATURE: True MBAR viewer
-FEATURE: Support densities in Forms (1x, 1.5x, 2x). Is that really needed ?
