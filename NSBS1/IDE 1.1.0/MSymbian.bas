Attribute VB_Name = "MSymbian"
Option Explicit

#If NSBSymbian Then
Global logFile As String
Global errLogFile As String
Global pkgFile As String
Global exeFile As String
Global shortExeFile As String
Global cmdFile As String
Global sisFile As String
Global sisxFile As String
Global sisFileS60us As String
Global sisFileUIQus As String
Global sisFileS60ss As String
Global sisFileUIQss As String
Global mifFile As String
Global mbmFile As String
Global shortMifFile As String
Global shortMbmFile As String
Global tmpFile As String
Global toolsDir As String
Global outputDir As String
Global convertIconBatFile As String
Global createInstallerBatFile As String
Global exeBatFile As String
Global uidcrcTmpFile As String
Global fontconvBatFile As String
Global executableName As String
Global platform As String
Global trace As Boolean

Sub compileSymbian()
   Dim FileNumber As Integer
   Dim fileLen As Integer
   Dim res
   trace = True
   FileNumber = FreeFile
   deleteWorkFiles
   
   If gbCreateS60 Then
      initFileNames ("S60")
      On Error Resume Next
      Kill logFile
      Kill errLogFile
      Kill sisxFile
      Kill sisFile
      Kill sisFileS60us
      Kill sisFileS60ss
      On Error GoTo 0
      modifyPKGfile ("S60")
      compileResourceFile ("")
      compileResourceFile ("_reg")
      modifyEXEfile shortExeFile, gTarget.UID3
      modifyEXEfile "StyleTap.dll", uid3plus(2)
      modifyEXEfile "StyleTapSymbianS60.dll", uid3plus(1)
      makeCMDfile
      convertIconS60
      createInstaller ("S60")
   End If
   
   If gbCreateUIQ Then
      initFileNames ("UIQ")
      On Error Resume Next
      Kill logFile
      Kill errLogFile
      Kill sisFile
      Kill sisFileUIQus
      Kill sisFileUIQss
      On Error GoTo 0
      modifyPKGfile ("UIQ")
      compileResourceFile ("")
      compileResourceFile ("_reg")
      compileResourceFile ("_loc")
      modifyEXEfile shortExeFile, gTarget.UID3
      modifyEXEfile "StyleTap.dll", uid3plus(2)
      modifyEXEfile "StyleTapSymbianUIQ.dll", uid3plus(1)
      makeCMDfile
      convertIconUIQ
      createInstaller ("UIQ")
   End If
   
   If Not trace Then deleteWorkFiles 'comment out this statement to leave the workfiles around
   If errLogFile <> "" Then
      Open errLogFile For Binary Access Read As #FileNumber
      fileLen = LOF(FileNumber)
      Close #FileNumber
      
      If fileLen = 795 Or fileLen = 1065 Then
         Kill errLogFile
      ElseIf fileLen > 0 Then
         MsgBox gStringTable(3451)
      End If
   End If

   If gbRunImmediately Then
      runImmediately
   End If
End Sub
Sub initFileNames(pform As String)
   platform = pform
   executableName = "StyleTapLauncher" & platform
   
   toolsDir = ProgramsDirectory & "\BuildTools\"
   outputDir = fileDirectory & "\Download\"
   logFile = outputDir & "compile.log"
   errLogFile = outputDir & "error.log"
   pkgFile = outputDir & gTarget.Name & ".pkg"
   exeFile = outputDir & executableName & ".exe"
   shortExeFile = executableName & ".exe"
   mifFile = outputDir & executableName & ".mif"
   shortMifFile = executableName
   mbmFile = outputDir & executableName & ".mbm"
   shortMbmFile = executableName
   sisFile = outputDir & gTarget.Name & ".sis"
   sisxFile = outputDir & gTarget.Name & ".sisx"
   sisFileS60us = outputDir & gTarget.Name & "_S60_unsigned.sis"
   sisFileUIQus = outputDir & gTarget.Name & "_UIQ_unsigned.sis"
   sisFileS60ss = outputDir & gTarget.Name & "_S60_selfsigned.sisx"
   sisFileUIQss = outputDir & gTarget.Name & "_UIQ_selfsigned.sis"
   fontconvBatFile = outputDir & "fontconvbat.bat"
   cmdFile = outputDir & "cmd.txt"
   tmpFile = outputDir & "crc32.tmp"
   convertIconBatFile = outputDir & "convertIcon.bat"
   createInstallerBatFile = outputDir & "createInstaller.bat"
   exeBatFile = outputDir & "exe.bat"
   uidcrcTmpFile = outputDir & "uidcrc.tmp"
End Sub
Sub deleteWorkFiles()

   On Error Resume Next
   Kill pkgFile
   Kill outputDir & "StyleTapLauncherS60.exe"
   Kill outputDir & "StyleTapLauncherUIQ.exe"
   Kill outputDir & "StyleTapLauncherS60.mif"
   Kill outputDir & "StyleTapLauncherUIQ.mif"
   Kill fontconvBatFile
   Kill cmdFile
   Kill tmpFile
   Kill convertIconBatFile
   Kill exeBatFile
   Kill uidcrcTmpFile
   Kill createInstallerBatFile
   Kill "StyleTap.dll"
   Kill "StyleTapSymbianS60.dll"
   Kill "StyleTapSymbianUIQ.dll"
   Kill "StyleTapLauncherS60.exe"
   Kill "StyleTapLauncherUIQ.exe"
   Kill outputDir & "selfsigned.cer"
   Kill outputDir & "selfsigned.key"
   Kill outputDir & "StyleTap.dll"
   Kill outputDir & "StyleTapSymbianS60.dll"
   Kill outputDir & "StyleTapSymbianUIQ.dll"
   Kill outputDir & "StyleTapLauncherS60.exe"
   Kill outputDir & "StyleTapLauncherUIQ.exe"
   Kill outputDir & "rcompS60.bat"
   Kill outputDir & "rcompS60_reg.bat"
   Kill outputDir & "rcompUIQ.bat"
   Kill outputDir & "rcompUIQ_reg.bat"
   Kill outputDir & "rcompUIQ_loc.bat"
   Kill outputDir & "StyleTapLauncherS60.rpp"
   Kill outputDir & "StyleTapLauncherS60_reg.rpp"
   Kill outputDir & "StyleTapLauncherUIQ.rpp"
   Kill outputDir & "StyleTapLauncherUIQ_reg.rpp"
   Kill outputDir & "StyleTapLauncherUIQ_loc.rpp"
   Kill GetTemporaryPath() & "StyleTapLauncherS60.rsc"
   Kill GetTemporaryPath() & "StyleTapLauncherS60_reg.rsc"
   Kill GetTemporaryPath() & "StyleTapLauncherUIQ.rsc"
   Kill GetTemporaryPath() & "StyleTapLauncherUIQ_reg.rsc"
   Kill GetTemporaryPath() & "StyleTapLauncherUIQ_loc.rsc"
   Kill outputDir & "StyleTapLauncherUIQ.mbm"
   Kill "rcomp.exe"
   Kill "uidcrc.exe"
   
   If Not isPro Or allowRegistration = False Or glSerialNumber = "Unregistered Demo" Then
      'if not Pro Edition, get rid of the files that could be used to make a signed version
      Kill sisFileS60us
      Kill sisFileUIQus
   End If
   On Error GoTo 0
    
End Sub
Sub modifyPKGfile(platform As String)
'The pkg file contains general information about the project and which files are to be installed.
'It is used by the makesis utility to create the installer.
'This code takes a template.pkg file from the BuildTools folder and modifies it for this project.
'Placeholders, marked by *** before and after, in the template are replaced.

   Dim FileNumber As Integer
   Dim data As String
   Dim s As String
   Dim p As Integer
   Dim targetPath As String
   Dim source As String
   Dim launcherName As String
   Dim infile As String
   Dim res
   Dim theme As String
   Dim Quote As String
   Quote = Chr(34)
   
   ShowStatus "Modifying PKG File", True
   infile = toolsDir & "template.pkg"
   FileNumber = FreeFile
   Open infile For Binary Access Read As #FileNumber
   data = String$(LOF(FileNumber), 32) 'fill buffer before reading
   Get #FileNumber, , data
   Close #FileNumber
   
   'get the UID3
   targetPath = "- " & Quote & "!:\private\" & gTarget.UID3 & "\install\db\"
   data = Replace(data, "***uid3***", gTarget.UID3)
   
   data = Replace(data, "***uid3+1***", uid3plus(1))
   data = Replace(data, "***uid3+2***", uid3plus(2))
   
   'Apply the fixups
   If gTarget.launcherName = "" Then
      launcherName = gTarget.Name
   Else
      launcherName = gTarget.launcherName
   End If
   data = Replace(data, "***LauncherName***", launcherName)
   
   s = checkLaunchVersion()
   data = Replace(data, "***version***", s)
   
   If gTarget.License = "" Then
      s = toolsDir & "license.txt"
   Else
      s = GetAbsolutePath(gTarget.License, "")
   End If
   data = Replace(data, "***license***", s)
   
   If gTarget.Company = "" Then
      s = launcherName
   Else
      s = gTarget.Company
   End If
   data = Replace(data, "***company***", s)
  
   data = Replace(data, "***name***", launcherName)
   data = Replace(data, "***filename***", gTarget.Name)
      
   s = fileDirectory & "\Download"
   data = Replace(data, "***prcdir***", s)
   
   s = ProgramsDirectory & "\BuildTools"
   data = Replace(data, "***buildtoolsdir***", s)
   
   s = GetTemporaryPath()
   data = Replace(data, "***tempdir***", s)
   
   'comment out lines not needed
   If platform = "S60" Then
      data = Replace(data, "***s60comment***", "")
   Else
      data = Replace(data, "***s60comment***", ";")
   End If
   
   If platform = "UIQ" Then
      data = Replace(data, "***uiqcomment***", "")
   Else
      data = Replace(data, "***uiqcomment***", ";")
   End If
   
   'Write out shared libs and resources
   s = q(fileDirectory & "\lib\mathlib.prc") & " " & targetPath & "mathlib.prc" & Quote & vbCrLf
   For Each res In gTarget.ResourceCollection
      source = GetAbsolutePath(res.ResourcePath, "")
      s = s & q(source) & " " & targetPath & res.filename & Quote & vbCrLf
   Next
   data = Replace(data, "***Resources***", s)
   
   'write out the new file
   Open pkgFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
End Sub

Sub compileResourceFile(rppname As String)
'The resource files (*.rsc) contain general information about the executable.
'The parameters are stored in the related .rpp file.
'The first part of the .rpp file contains definitions for the data types and names in the actual
'parameters. If you need to add definitions, look at the .rpp file that is output by a build
'using Symbian's tools.
'The parameters appear at the end in plain text. The file can be modified in NotePad.
'The template is take from the BuildTools folder, modified and written out to \download.
'The rcomp utility is used to compile the rsc file from the rpp file.
'The modified rsc file will be installed on the device.
'Warning: the output file from rcomp (*.rss) has to go to a pathname without spaces.

   Dim FileNumber As Integer
   Dim data As String
   Dim launcherName As String
   Dim installFolder As String
   Dim infile As String
   Dim res
      
   ShowStatus "Compiling Resource " & rppname, True
   infile = toolsDir & "template" & platform & rppname & ".rpp"
   FileNumber = FreeFile
   Open infile For Binary Access Read As #FileNumber
   data = String$(LOF(FileNumber), 32) 'fill buffer before reading
   Get #FileNumber, , data
   Close #FileNumber
   
   'Apply the fixups
   If gTarget.installFolder = "" Then
      installFolder = "Installat."
   Else
      installFolder = gTarget.installFolder
   End If
   If gTarget.launcherName = "" Then
      launcherName = gTarget.Name
   Else
      launcherName = gTarget.launcherName
   End If
   data = Replace(data, "***name***", launcherName)
   data = Replace(data, "***installFolder***", installFolder)
   data = Replace(data, "***uid3***", gTarget.UID3)
   data = Replace(data, "***mifFile***", shortMifFile)
   data = Replace(data, "***mbmFile***", shortMbmFile)
            
   'write out the new file
   Open outputDir & executableName & rppname & ".rpp" For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
   'now compile it
      
   data = "copy " & q(toolsDir & "rcomp.exe") & " ." & vbCrLf
   data = data & "copy " & q(toolsDir & "uidcrc.exe") & " ." & vbCrLf
   data = data & "rcomp" & " -u"  'add -v for verbose
   data = data & " -o" & q(GetTemporaryPath() & executableName & rppname & ".rsc")
   data = data & " -s" & q(outputDir & executableName & rppname & ".rpp") & vbCrLf
      
   Open outputDir & "rcomp" & platform & rppname & ".bat" For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber

   data = q(outputDir & "rcomp" & platform & rppname & ".bat") & " 1>> " & q(logFile) & " 2>> " & q(errLogFile)
   res = ExecCmd(data)
   
End Sub

Sub modifyEXEfile(filename As String, UID3 As String)
'The exe file is the one that is actually launched by the Symbian Launcher.
'It is just a pretty face. It displays a name and an icon (both defined in the rsc files),
'and its only task is to get the name of the NS Basic program to run (it's in cmd.txt),
'and start the StyleTap runtime engine, passing the program name.

'There are two checksums to be calculated. The first checksum is based on bytes 1-12 of the file,
'which are made up of the type (DLL or EXE), a constant, and the UID3. It is calculated by the
'uidcrc utility.

'Once the uid3 is known, it can be passed to the crc32 utility to actually update the file.

'This sub also does sets up the uids and checksums for the dll files.
'It also updates the list of declared capabilities, called iS.Caps.iCaps. For self signing,
'only certain capabilities are allowed. The ones used by an executable are put into bytes 88-8E by
'the Carbide compiler. By overriding the bytes, the checking is defeated. Of course, you still cannot
'use the advanced capabilities: The OS will give some kind of protection fault.

'fontconv is originally named crc32; found on the net. It calculates the crc32 and fixes the exe file.

   ShowStatus "Modifying EXE File:" & filename, True
   Dim FileNumber As Integer
   Dim tmpFile As String
   Dim data As String
   Dim i As Integer
   Dim res As Integer
   Dim launcherName As String
   Dim uidBytes(16) As Byte
   Dim infile As String
   Dim uid1 As String
   Dim uid2 As String
   Dim resBytes() As Byte
   FileNumber = FreeFile
   
   'create fontconv.exe
   resBytes = LoadResData(101, "custom")
   Open "fontconv.exe" For Binary As #FileNumber
   Put #FileNumber, , resBytes
   Close #FileNumber

   If LCase(Right(filename, 4)) = ".exe" Then
      uid1 = "0x1000007A" 'KExecutableImageUid
      uid2 = "0x100039CE" 'KUidApp
   Else
      uid1 = "0x10000079" 'KDynamicLibraryUid
      uid2 = "0x1000008D" 'KSharedLibraryUid
   End If
   
   'calculate CRC for bytes 13 to 16 using uidcrc.exe
   data = q(toolsDir & "uidcrc.exe") & " " & uid1 & " " & uid2 & " 0x" & UID3 & " " & q(uidcrcTmpFile)
   res = ExecCmd(data)
   
   res = readInputFile(uidcrcTmpFile, uidBytes)
   If res <> 15 Then
      MsgBox "Error in uidcrc calculation: " & res
      Exit Sub
   End If
   
   'copy the file to the current directory so it can be worked on
   data = "copy " & q(toolsDir & filename) & " ."
   On Error Resume Next
   Kill fontconvBatFile
   On Error GoTo 0
   
   Open fontconvBatFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   data = q(fontconvBatFile) & " 1>> " & q(logFile) & " 2>> " & q(errLogFile)
   res = ExecCmd(data)
   
   'Zap the declared capabilities so they are just the basic ones
   Open filename For Binary Access Write As #FileNumber
   Put #FileNumber, &H89, CByte(0)
   Put #FileNumber, &H8A, CByte(&HE0)
   Put #FileNumber, &H8B, CByte(1)
   Put #FileNumber, &H8C, CByte(0)
   Put #FileNumber, &H8D, CByte(0)
   Put #FileNumber, &H8E, CByte(0)
   Close #FileNumber
   
   data = "fontconv" & " -u 0x" & UID3
   data = data & " -c 0x" & Right(Hex(uidBytes(15) + &H100), 2)
   data = data & Right(Hex(uidBytes(14) + &H100), 2)
   data = data & Right(Hex(uidBytes(13) + &H100), 2)
   data = data & Right(Hex(uidBytes(12) + &H100), 2)
   data = data & " -f" & q(filename) & vbCrLf
   data = data & "copy " & q("0x" & UID3 & "_" & filename) & " " & q(outputDir & filename) & vbCrLf
   data = data & "del " & q("0x" & UID3 & "_" & filename) & vbCrLf
   data = data & "del fontconv.exe" & vbCrLf

   On Error Resume Next
   Kill fontconvBatFile
   On Error GoTo 0
   
   Open fontconvBatFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
   If trace Then
    data = q(fontconvBatFile) & " 1>> " & q(logFile) & " 2>> " & q(errLogFile)
   Else
    data = q(fontconvBatFile) '& " 1>> " & q(logFile) & " 2>> " & q(errLogFile)
   End If
   res = ExecCmd(data)
   
End Sub

Sub makeCMDfile()
'This file contains the name of the NS Basic app that StyleTap will launch

   Dim FileNumber As Integer
   Dim data As String
   
   ShowStatus "Modifying CMD File", True
   FileNumber = FreeFile
   
   data = "StyleTapSymbian_" & uid3plus(1) & ".dll StyleTap_" & uid3plus(2) & ".dll /launch " & q(gTarget.Name)
      
   Open cmdFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
End Sub
Sub convertIconS60()
'This creates the icon file in MIF form (Multi Image Format).
'It takes an svgt file (Scalar Vector Graphics - Tiny) file and feeds it to the mifconv utility
'to produce the .mif file.
'The mif file is included in the installer.
'The rsc file contains the path to the mif file so the Symbian Launcher can find it.

   ShowStatus "Converting S60 Icon", True
   Dim data As String
   Dim res As Integer
   Dim icon As String
   Dim FileNumber As Integer
   Dim cmdFile As String
   
   icon = GetAbsolutePath(gTarget.LauncherIconS60, "")
   If Len(icon) < 4 Then icon = toolsDir & "LauncherIcon.svg" 'default icon
   'input file must be in SVGT (tiny) format.
   data = q(toolsDir & "Nokia_files\mifconv.exe") & " "
   data = data & q(mifFile)
   data = data & " /T" & q(Left(outputDir, Len(outputDir) - 1))
   data = data & " /S" & q(Left(toolsDir, Len(toolsDir) - 1))
   data = data & " /B" & q(Left(toolsDir, Len(toolsDir) - 1))
   data = data & " /X /c32 " & q(icon)
   
   FileNumber = FreeFile
   Open convertIconBatFile For Output As #FileNumber
   Print #FileNumber, data
   Close #FileNumber

   data = q(convertIconBatFile) & " 1>> " & q(logFile) & " 2>> " & q(errLogFile)
   res = ExecCmd(data)
 
End Sub
Sub convertIconUIQ()

   ShowStatus "Converting UIQ Icon", True
   Dim data As String
   Dim res As Integer
   Dim icon As String
   Dim FileNumber As Integer
   Dim cmdFile As String
   Dim s As String
   
   icon = GetAbsolutePath(gTarget.LauncherIconUIQ, "")
   If Len(icon) < 4 Then icon = toolsDir & "LauncherIcon.bmp" 'default icon
   s = Left(icon, Len(icon) - 4)
   data = q(toolsDir & "bmconv.exe") & " " & q(mbmFile)
   data = data & " /c8" & q(s & "64.bmp") & " /c8" & q(toolsDir & "64.bmp")
   data = data & " /c8" & q(s & "40.bmp") & " /c8" & q(toolsDir & "40.bmp")
   data = data & " /c8" & q(s & "18.bmp") & " /c8" & q(toolsDir & "18.bmp")
   
   FileNumber = FreeFile
   Open convertIconBatFile For Output As #FileNumber
   Print #FileNumber, data
   Close #FileNumber

   data = q(convertIconBatFile) & " 1>> " & q(logFile) & " 2>> " & q(errLogFile)
   res = ExecCmd(data)
 
End Sub
Sub createInstaller(platform As String)
'This creates a batch file to call the makesis utility.
'Makesis uses the information in the .pkg file (see ModifyPkgFile) to do its stuff.
'The resulting file is a desktop executable that calls the Nokia Suite to do the installation.
'It's the only file that matters after the installer is created.

   Dim cmdFile As String
   Dim FileNumber As Integer
   Dim data As String
   Dim res As Integer
   Dim expDays As String
   
   ShowStatus "Creating SIS File", True

   If allowRegistration = False Or glSerialNumber = "Unregistered Demo" Then
      expDays = "30"
   Else
      expDays = "365"
   End If

   data = q(toolsDir & "makesis") & " " & q(pkgFile) & vbCrLf
   
   data = data & q(toolsDir & "makekeys") & " -cert -expdays " & expDays & " -password DefaultPassword -len 1024 -dname "
   data = data & q("CN=Support CO=CA OU=Development OR=NS Basic Corporation EM=support@nsbasic.com") & " "
   data = data & q(outputDir & "selfsigned.key") & " "
   data = data & q(outputDir & "selfsigned.cer") & vbCrLf
      
   data = data & q(toolsDir & "signsis") & " -s " & q(sisFile) & " "
   data = data & q(sisxFile & platform) & " "
   data = data & q(outputDir & "selfsigned.cer") & " "
   data = data & q(outputDir & "selfsigned.key") & " "
   data = data & "DefaultPassword" & vbCrLf
   
   If platform = "S60" Then
      data = data & "move " & q(sisFile) & " " & q(sisFileS60us) & vbCrLf                'unsigned
      data = data & "move " & q(sisxFile & platform) & " " & q(sisFileS60ss) & vbCrLf               'signed
   Else
      data = data & "move " & q(sisFile) & " " & q(sisFileUIQus) & vbCrLf                'unsigned
      data = data & "move " & q(sisxFile & platform) & " " & q(sisFileUIQss) & vbCrLf               'signed
   End If

   FileNumber = FreeFile
   Open createInstallerBatFile For Output As #FileNumber
   Print #FileNumber, data
   Close #FileNumber

   data = q(createInstallerBatFile) & " 1>> " & q(logFile) & " 2>> " & q(errLogFile)
   res = ExecCmd(data)

End Sub

Sub runImmediately()
   Dim command As String
   Dim res As Integer
   If gbCreateS60 Then
      ShowStatus "Run SISX File", True
      command = q(sisFileS60ss)
      ShellExecute frmMain.hWnd, "open", command, 0, 0, SW_SHOWNORMAL
   End If
   If gbCreateUIQ Then
      ShowStatus "Run SIS File", True
      command = q(sisFileUIQss)
      ShellExecute frmMain.hWnd, "open", command, 0, 0, SW_SHOWNORMAL
   End If
End Sub

Function readInputFile(inputfile As String, s() As Byte) As Long
   Dim i As Long
   Dim FileNumber As Integer
   FileNumber = FreeFile
   i = -1
   Open inputfile For Binary As #FileNumber
   While EOF(FileNumber) = False
      i = i + 1
      Get #FileNumber, , s(i)
   Wend
   Close #FileNumber
   readInputFile = i - 1
End Function
Sub copyBytes(s() As Byte, fromByte As Long, toByte As Long, FileNumber As Integer)
   Dim i As Long
   For i = fromByte To toByte
      Put #FileNumber, , CByte(s(i))
   Next
End Sub
Sub writeString(outString As String, leadBytes As Integer, FileNumber As Integer)
   Dim i As Integer
   If leadBytes >= 1 Then Put #FileNumber, , CByte(Len(outString))
   If leadBytes = 2 Then Put #FileNumber, , CByte(Len(outString))
   For i = 1 To Len(outString)
      Put #FileNumber, , CByte(Asc(Mid(outString, i, 1)))
   Next
End Sub

Function CRC32(buffer() As Byte, bufLen)
'not used. Symbian uses some other algorithm.
Dim crc32Table() As Long
Dim crc32Result As Long
Dim iLookup As Integer
Dim b As Byte

Dim dwPolynomial As Long
dwPolynomial = &HEDB88320 'found this magic number on the web. Seems to be commonly used.
dwPolynomial = 0
Dim i As Integer, j As Integer

ReDim crc32Table(256)
Dim dwCrc As Long

For i = 0 To 255
    dwCrc = i
    For j = 8 To 1 Step -1
        If (dwCrc And 1) Then
            dwCrc = ((dwCrc And &HFFFFFFFE) \ 2&) And &H7FFFFFFF
            dwCrc = dwCrc Xor dwPolynomial
        Else
            dwCrc = ((dwCrc And &HFFFFFFFE) \ 2&) And &H7FFFFFFF
        End If
    Next j
    crc32Table(i) = dwCrc
Next i

crc32Result = &HFFFFFFFF
      
For i = 0 To bufLen - 1
   iLookup = (crc32Result And &HFF) Xor buffer(i)
   crc32Result = ((crc32Result And &HFFFFFF00) \ &H100) And 16777215 ' nasty shr 8 with vb :/
   crc32Result = crc32Result Xor crc32Table(iLookup)
Next

CRC32 = Not (crc32Result)
End Function

Function q(s As String) As String
   'this function returns s as "s"
   q = Chr(34) & s & Chr(34)
End Function

Function checkLaunchVersion() As String
Dim s1() As String
Dim i As Long

'LaunchVersion must be in the format x,y,z
s1 = Split(gTarget.LaunchVersion, ",")
If UBound(s1) = 2 Then
   For i = 0 To 2
      If Not IsNumeric(s1(i)) Then s1(i) = "0"
   Next
   gTarget.LaunchVersion = Join(s1, ",")
Else
   gTarget.LaunchVersion = "1,0,0"
End If
checkLaunchVersion = gTarget.LaunchVersion
End Function

Function uid3plus(plus) As String
   uid3plus = Hex(plus + Val("&h" & gTarget.UID3))
End Function

#End If 'NSBSymbian

