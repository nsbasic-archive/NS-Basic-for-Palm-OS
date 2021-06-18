Treo Lib
June 18, 2004

This contains the current version of the Treo lib.  It has all the functions implemented
that I think prudent for the first release.  The HTTP functions are still flaky, and 
I'll be working on those in the next couple of days.

The directory contains everything needed to compile the Treo lib, except for the Treo
SDK, which is installed in the CodeWarrior tree.  Just double-click on the project 
and go.

Assuming that the root directory is NSBTreo, the files are as follows:

Distributable Files:

NSBTreo\ref.html is the technote.  Rename to TN30.html before distributing.
NSBTreo\Incs\NSBTreoLib.inf is the info file.  Copy to \NSBasic\Lib
NSBTreo\Obj\NSBTreoLib.prc is the shared library.
NSBTreo\TreoTest is the test program.  Copy to \NSBasic\Projects

Other Sources and compilation steps:

NSBTreo\Obj\doit.bat adds the tver to the compiled shared library.

NSBTreo\ref.txt is the source file for the documentation.
NSBTreo\md.pl compiles the documentation into ref.html.  Type perl md.pl ref.txt

NSBTreo\Incs\libdef.txt is the source file for the library description.  Edit this
and type perl snip.pl to recreate the jump tables, prototypes, and .inf file.  After
a change, remove object code from the project and recompile.