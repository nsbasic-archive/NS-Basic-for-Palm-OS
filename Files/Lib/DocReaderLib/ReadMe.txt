ReadMe for DocReaderLib
------ --- ------------

Version 1.4 (Jan 31, 2004) -- See release notes at end of file

DocReaderLib is a shared library for integrating the reading of "DOC"
style databases from within a Palm OS based application.  It can be
implemented in NSB/Palm v4 projects with literally only two or three
lines of code.

DOC style databases are the de facto standard for simple text-based
documents under Palm OS.  Not to be confused with Microsoft Office
Word documents (*.doc), the DOC standard was specifically designed
for the limited resource constraints of common Palm OS devices.

Numerous commercial, shareware, and even freeware DOC readers are
available but all of them operate as stand-alone applications.  For
some purposes that is fine (e.g. when you're reading a novel), but
in other cases it is advantageous to have text based reference aids
available from *within* your own application.

For example, applications may want to provide easy access to medical
references, building codes, sales literature, policy manuals, or any
number of other text based references.  Now you can not only easily
provide access to the documents, but you can even link to specific
locations within a document if the context of your program permits
you to predict where within the document the user would prefer to
start reading.

Another example is an application help file.  You can not only
supply a full user guide and tutorial, but you can use "bookmarks"
within the help file named to match the form titles in your own
application.  This permits a single line of code in a menu item or
form button to link to the associated section of the document.  The
result is a context-sensitive help file, yet the user can peruse other
sections of the help file as well.  All using a single line of code.

A more comprehensive guide to the features of DocReaderLib and
instructions for using it is contained in the DocReadLib Guied which
is supplied in both *.txt file and a DOC compatible *.pdb format for
reading on the Palm OS device itself.

In addition, a sample NSB/Palm v4 application is provided in both
source and compiled (*.prc) form so you may experiment with the
various options DocReaderLib supports, and see for yourself the code
used to add the reader support to the project.

The files contained in this distribution include:

  DocReader.prj			Sample NSB project source
  DocReaderLib Guide.txt	Text file containing usage info
  DocReaderLib Guide.pdb	DOC style version of above text
  DocReaderLib.inf		Used by NSB/Palm v4 compiler
  DocReaderLib.prc		Shared library
  ReadMe.txt			You're reading it

Please refer to the DocReaderLib Guide for more information.  You 
may either read the *.txt version, or install the compiled sample
NSB project and read the guide directly on a device.  It is not
necessary to install either the DocReadLib.prc library or the 
DocReaderLib Guide.pdb to the device, only the DocReader.prc 
sample itself.

Questions or comments should be directed to:

  Douglas Handy
  dhandy1@bellsouth.net		or
  http://groups.yahoo.com/group/nsbasic-palm

The latest version can be obtained from:

  http://groups.yahoo.com/group/nsbasic-palm/files


Version Notes
------- -----

v1.4	Jan 31, 2004
	Corrected problem when displaying a document which is
	shorted than one full screen.  circumvent some problems
	with dynamically generated forms under OS3.x though the
	following issues remain (in OS 3.x only):
	  - POSE reports a series of low memory access.  Up to 15
	    occurences, depending on options set.  There is one
	    report per object on the form.  This appears to be a
	    bug in OS 3.x, and does not affect the device.
	  - Corrected error until OS 3.x when No Title requested.
	  - Memory leak of 7 bytes per time a doc is displayed,
	    but only if the option is set to NOT allow a jump by
	    percentage within the document or show the current
	    location as a percentage of the document.  It also
	    only affects OS 3.x, and the memory will be reclaimed
	    when the application terminates.

