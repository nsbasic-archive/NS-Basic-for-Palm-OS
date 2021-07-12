Attribute VB_Name = "MSymbian"

#If NSBSymbian Then
Global logFile As String
Global pkgFile As String
Global rppFile As String
Global reg_rppFile As String
Global rscFile As String
Global reg_rscFile As String
Global exeFile As String
Global shortExeFile As String
Global cmdFile As String
Global sisFile As String
Global sisxFile As String
Global mifFile As String
Global shortMifFile As String
Global tmpFile As String
Global toolsDir As String
Global outputDir As String
Global reg_rscBatFile As String
Global rscBatFile As String
Global convertIconBatFile As String
Global createInstallerBatFile As String
Global exeBatFile As String
Global uidcrcTmpFile As String
Global crc32BatFile As String

Sub compileSymbian()
   initFileNames
   deleteWorkFiles
   On Error Resume Next
   Kill logFile
   On Error GoTo 0
   
   modifyPKGfile
   compileReg_rscFile
   compileRscFile
   'OLDmodifyRSCfile
   'OLDmodifyREG_RSCfile
   OLDmodifyEXEfile
   'modifyEXEfile shortExeFile, gTarget.UID3
   'modifyEXEfile "StyleTap.dll", "E056F3A1"
   'modifyEXEfile "StyleTapSymbianS60.dll", "E056F3A1"
   makeCMDfile
   convertIcon
   If gbCreateS60 Then
      createS60installer
      If gbRunImmediately Then
         runImmediately "S60"
      End If
   End If
   If gbCreateUIQ Then
      createUIQinstaller
      If gbRunImmediately Then
         runImmediately "UIQ"
      End If
   End If
   'deleteWorkFiles 'comment out this statement to leave the workfiles around
End Sub
Sub initFileNames()
   Dim fileName
   fileName = "StyleTapLauncherS60"
   
   toolsDir = ProgramsDirectory & "\BuildTools\"
   outputDir = FilesDirectory & "\Download\"
   logFile = outputDir & "error.log"
   pkgFile = outputDir & fileName & ".pkg"
   rppFile = outputDir & fileName & ".rpp"
   reg_rppFile = outputDir & fileName & "_reg.rpp"
   rscFile = outputDir & fileName & ".rsc"
   reg_rscFile = outputDir & fileName & "_reg.rsc"
   exeFile = outputDir & fileName & ".exe"
   shortExeFile = fileName & ".exe"
   mifFile = outputDir & fileName & ".mif"
   shortMifFile = fileName & ".mif"
   sisFile = Left(pkgFile, Len(pkgFile) - 4) & ".sis"
   sisxFile = outputDir & gTarget.Name & ".sisx"
   crc32BatFile = outputDir & "crc32.bat"
   cmdFile = outputDir & "cmd.txt"
   tmpFile = outputDir & "crc32.tmp"
   reg_rscBatFile = outputDir & "reg_rsc.bat"
   rscBatFile = outputDir & "rsc.bat"
   convertIconBatFile = outputDir & "convertIcon.bat"
   createInstallerBatFile = outputDir & "createInstaller.bat"
   exeBatFile = outputDir & "exe.bat"
   uidcrcTmpFile = outputDir & "uidcrc.tmp"
End Sub
Sub deleteWorkFiles()
   On Error Resume Next
   Kill pkgFile
   Kill rscFile
   Kill reg_rscFile
   Kill rppFile
   Kill reg_rppFile
   Kill exeFile
   Kill mifFile
   Kill sisFile
   Kill crc32BatFile
   Kill cmdFile
   Kill tmpFile
   Kill rscBatFile
   Kill reg_rscBatFile
   Kill convertIconBatFile
   Kill exeBatFile
   Kill uidcrcTmpFile
   Kill createInstallerBatFile
   On Error GoTo 0
End Sub
Sub modifyPKGfile()
   Dim FileNumber As Integer
   Dim data As String
   Dim s As String
   Dim p As Integer
   Dim targetPath As String
   Dim source As String
   Dim launcherName As String
   Dim inFile As String
   Dim res
   Dim Quote As String
   Quote = Chr(34)
   
   ShowStatus "Modifying PKG File", True
   inFile = toolsDir & "template.pkg"
   FileNumber = FreeFile
   Open inFile For Binary Access Read As #FileNumber
   data = String$(LOF(FileNumber), 32) 'fill buffer before reading
   Get #FileNumber, , data
   Close #FileNumber
   
   'get the UID3
   targetPath = "- " & Quote & "!:\private\" & gTarget.UID3 & "\install\db\"
   data = Replace(data, "***uid3***", gTarget.UID3)
   
   'Apply the fixups
   If gTarget.launcherName = "" Then
      launcherName = gTarget.Name
   Else
      launcherName = gTarget.launcherName
   End If
   data = Replace(data, "***LauncherName***", launcherName)
   
   If gTarget.LaunchVersion = "" Then
      s = "1,0,0"
   Else
      s = gTarget.LaunchVersion
   End If
   data = Replace(data, "***version***", s)
   
   If gTarget.Company = "" Then
      s = gTarget.launcherName
   Else
      s = gTarget.Company
   End If
   data = Replace(data, "***company***", s)
  
   'data = Replace(data, "***name***", gTarget.Name)
   data = Replace(data, "***name***", launcherName)
      
   s = FilesDirectory & "\Download"
   data = Replace(data, "***prcdir***", s)
   
   s = ProgramsDirectory & "\BuildTools"
   data = Replace(data, "***buildtoolsdir***", s)
   
   'Write out shared libs and resources
   s = q(FilesDirectory & "\lib\mathlib.prc") & " " & targetPath & "mathlib.prc" & Quote & vbCrLf
   For Each res In gTarget.ResourceCollection
      source = GetAbsolutePath(res.ResourcePath, "")
      source = Left(source, Len(source) - 1)
      s = s & q(source) & " " & targetPath & res.fileName & Quote & vbCrLf
   Next
   data = Replace(data, "***Resources***", s)
   
   'write out the new file
   Open pkgFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
End Sub

Sub compileReg_rscFile()
   Dim FileNumber As Integer
   Dim data As String
   Dim launcherName As String
   Dim installFolder As String
   Dim inFile As String
   Dim res
   
   ShowStatus "Modifying Reg_RSC File", True
   inFile = toolsDir & "template_reg.rpp"
   FileNumber = FreeFile
   Open inFile For Binary Access Read As #FileNumber
   data = String$(LOF(FileNumber), 32) 'fill buffer before reading
   Get #FileNumber, , data
   Close #FileNumber
   
   'Apply the fixups
   If gTarget.installFolder = "" Then
      installFolder = "Installat."
   Else
      installFolder = gTarget.installFolder
   End If
   data = Replace(data, "***installFolder***", installFolder)
   data = Replace(data, "***UID3***", gTarget.UID3)
            
   'write out the new file
   Open reg_rppFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
   'now compile it
   data = q(toolsDir & "rcomp") & " -v -u"
   data = data & " -o" & q(reg_rscFile)
   data = data & " -s" & q(reg_rppFile)
      
   Open reg_rscBatFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
   data = reg_rscBatFile & " 1>> " & logFile
   res = ExecCmd(data)
   
End Sub
Sub compileRscFile()
   Dim FileNumber As Integer
   Dim data As String
   Dim launcherName As String
   Dim inFile As String
   Dim res
   
   ShowStatus "Modifying RSC File", True
   inFile = toolsDir & "template.rpp"
   FileNumber = FreeFile
   Open inFile For Binary Access Read As #FileNumber
   data = String$(LOF(FileNumber), 32) 'fill buffer before reading
   Get #FileNumber, , data
   Close #FileNumber
   
   'get the UID3
   data = Replace(data, "***UID3***", gTarget.UID3)
   
   'Apply the fixups
   If gTarget.launcherName = "" Then
      launcherName = gTarget.Name
   Else
      launcherName = gTarget.launcherName
   End If
   data = Replace(data, "***name***", launcherName)
   data = Replace(data, "***mifFile***", shortMifFile)
   
   'write out the new file
   Open rppFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
   'now compile it
   data = q(toolsDir & "rcomp") & " -v -u"
   data = data & " -o" & q(rscFile)
   data = data & " -s" & q(rppFile)
      
   Open rscBatFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
   data = rscBatFile & " 1>> " & logFile
   res = ExecCmd(data)

End Sub
Sub OLDmodifyRSCfile()
   ShowStatus "Modifying RSC File", True
   Dim s(500) As Byte
   Dim reslen As Integer
   Dim inFile As String
   Dim FileNumber As Integer
   Dim launcherName As String
   FileNumber = FreeFile
   
   If gTarget.launcherName = "" Then
      launcherName = gTarget.Name
   Else
      launcherName = gTarget.launcherName
   End If
   launcherName = Left(launcherName & "                     ", 21)
   
   inFile = toolsDir & "template.rsc"
   reslen = readInputFile(inFile, s)
      
   Open rscFile For Binary As #FileNumber
   copyBytes s, 0, 60, FileNumber
   writeString launcherName, 1, FileNumber
   copyBytes s, 83, 92, FileNumber
   writeString launcherName, 2, FileNumber
   copyBytes s, 116, 124, FileNumber
   writeString launcherName, 2, FileNumber
   copyBytes s, 148, 189, FileNumber
   Put #FileNumber, , gTarget.UID3
   copyBytes s, 198, reslen, FileNumber
   
   Close #FileNumber
End Sub
Sub OLDmodifyREG_RSCfile()
   ShowStatus "Modifying REG.RSC File", True
   Dim s(500) As Byte
   Dim reslen As Integer
   Dim inFile As String
   Dim FileNumber As Integer
   Dim launcherName As String
   FileNumber = FreeFile
      
   inFile = toolsDir & "template_reg.rsc"
   reslen = readInputFile(inFile, s)
      
   Open reg_rscFile For Binary As #FileNumber
   copyBytes s, 0, 7, FileNumber
   Put #FileNumber, , CByte("&h" & Mid(gTarget.UID3, 7, 2))
   Put #FileNumber, , CByte("&h" & Mid(gTarget.UID3, 5, 2))
   Put #FileNumber, , CByte("&h" & Mid(gTarget.UID3, 3, 2))
   Put #FileNumber, , CByte("&h" & Mid(gTarget.UID3, 1, 2))
   copyBytes s, 12, 53, FileNumber
   Put #FileNumber, , gTarget.UID3
   copyBytes s, 62, 105, FileNumber
   Put #FileNumber, , gTarget.UID3
   copyBytes s, 114, reslen, FileNumber
   
   Close #FileNumber
End Sub

Sub modifyEXEfile(fileName As String, UID3 As String)
   ShowStatus "Modifying EXE File:" & fileName, True
   Dim s(999999) As Byte
   Dim FileNumber As Integer
   Dim tmpFile As String
   Dim data As String
   Dim i As Integer
   Dim res As Integer
   Dim launcherName As String
   Dim uidBytes(16) As Byte
   FileNumber = FreeFile
   
   'calculate CRC for bytes 13 to 16 using uidcrc.exe
   data = q(toolsDir & "uidcrc.exe") & " 0x1000007A 0x100039CE 0x" & UID3 & " " & uidcrcTmpFile
   res = ExecCmd(data)
   
   res = readInputFile(uidcrcTmpFile, uidBytes)
   If res <> 15 Then
      MsgBox "Error in uidcrc calculation: " & res
      Exit Sub
   End If
                       
   data = "cd " & q(outputDir) & vbCrLf
   data = data & "copy " & q(toolsDir & fileName) & " ." & vbCrLf
   data = data & q(toolsDir & "crc32") & " -u 0x" & UID3
   data = data & " -c 0x" & Right(Hex(uidBytes(15) + &H100), 2)
   data = data & Right(Hex(uidBytes(14) + &H100), 2)
   data = data & Right(Hex(uidBytes(13) + &H100), 2)
   data = data & Right(Hex(uidBytes(12) + &H100), 2)
   data = data & " -f" & fileName & vbCrLf
   data = data & "copy " & q("0x" & UID3 & "_" & fileName) & " " & q(fileName) & vbCrLf
   data = data & "del  " & q("0x" & UID3 & "_" & fileName)
      
   On Error Resume Next
   Kill crc32BatFile
   On Error GoTo 0
   
   Open crc32BatFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
   data = crc32BatFile & " 1>> " & logFile
   res = ExecCmd(data)
   
End Sub
Sub OLDmodifyEXEfile()
   ShowStatus "Modifying EXE File", True
   Dim s(21000) As Byte
   Dim reslen As Integer
   Dim FileNumber As Integer
   Dim tmpFile As String
   Dim inFile As String
   Dim data As String
   Dim i As Integer
   Dim res As Integer
   Dim launcherName As String
   Dim uidBytes(16) As Byte
   FileNumber = FreeFile
   
   'calculate CRC for bytes 13 to 16 using uidcrc.exe
   data = q(toolsDir & "uidcrc.exe") & " 0x1000007A 0x100039CE 0x" & gTarget.UID3 & " " & uidcrcTmpFile
   res = ExecCmd(data)
   
   res = readInputFile(uidcrcTmpFile, uidBytes)
   If res <> 15 Then
      MsgBox "Error in uidcrc calculation: " & res
      Exit Sub
   End If
      
   inFile = toolsDir & "template.exe"
   reslen = readInputFile(inFile, s)
         
   Open exeFile For Binary As #FileNumber
   copyBytes uidBytes, 0, 15, FileNumber
   copyBytes s, 16, 127, FileNumber
   copyBytes uidBytes, 8, 11, FileNumber
   copyBytes s, 132, reslen, FileNumber
   
   Close #FileNumber
              
   data = "cd " & q(outputDir) & vbCrLf
   data = data & "copy " & q(toolsDir & shortExeFile) & " ." & vbCrLf
   data = data & q(toolsDir & "crc32") & " -u 0x" & gTarget.UID3
   data = data & " -c 0x" & Right(Hex(uidBytes(15) + &H100), 2)
   data = data & Right(Hex(uidBytes(14) + &H100), 2)
   data = data & Right(Hex(uidBytes(13) + &H100), 2)
   data = data & Right(Hex(uidBytes(12) + &H100), 2)
   data = data & " -f" & shortExeFile & vbCrLf
   data = data & "copy " & q("0x" & gTarget.UID3 & "_" & shortExeFile) & " " & q(shortExeFile) & vbCrLf
   data = data & "del  " & q("0x" & gTarget.UID3 & "_" & shortExeFile)
      
   Open crc32BatFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
   data = crc32BatFile & " 1>> " & logFile
   res = ExecCmd(data)
   
End Sub

Sub makeCMDfile()
   Dim FileNumber As Integer
   Dim data As String
   
   ShowStatus "Modifying CMD File", True
   FileNumber = FreeFile
   
   data = "/launch " & gTarget.Name
      
   Open cmdFile For Binary As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
   
End Sub
Sub convertIcon()
   ShowStatus "Converting Icon", True
   Dim data As String
   Dim res As Integer
   Dim icon As String
   Dim FileNumber As Integer
   Dim cmdFile As String
   
   icon = gTarget.LauncherIcon
   If Len(icon) < 4 Then icon = toolsDir & "LauncherIcon.svg" 'default icon
   
   If LCase(Right(icon, 3)) = "svg" Then
      'input file must be in SVGT (tiny) format.
      data = q(toolsDir & "mifconv.exe") & " "
      data = data & q(mifFile)
      data = data & " /X /S" & q(Left(toolsDir, Len(toolsDir) - 1)) & " /c32 " & q(icon)
   End If
   
   If LCase(Right(icon, 3)) = "bmp" Then
      'this doesn't work yet. BMCONV returns "Invalid bitmap mode specified"
      data = q(tools & "mifconv.exe") & " "
      data = data & q(mifFile)
      data = data & " /X /S" & q(Left(toolsDir, Len(toolsDir) - 1))
      data = data & " /B" & q(Left(toolsDir, Len(toolsDir) - 1)) & " /c32 " & q(icon)
   End If
   
   FileNumber = FreeFile
   Open convertIconBatFile For Output As #FileNumber
   Print #FileNumber, data
   Close #FileNumber

   data = convertIconBatFile & " 1>> " & logFile
   res = ExecCmd(data)
 
End Sub
Sub createS60installer()
   Dim cmdFile As String
   Dim FileNumber As Integer
   Dim data As String
   Dim res As Integer
   
   ShowStatus "Creating SISX File", True

   data = q(toolsDir & "makesis") & " " & q(pkgFile) & vbCrLf
   data = data & q(toolsDir & "signsis") & " -s " & q(sisFile) & " "
   data = data & q(sisxFile) & " "
   data = data & q(toolsDir & "cert-gen.cer") & " "
   data = data & q(toolsDir & "key-gen.key") & " "
   'data = data & q(toolsDir & "NSBStub.cer") & " "
   'data = data & q(toolsDir & "NSBStub.key") & " "
   data = data & "DefaultPassword" & vbCrLf
   
   FileNumber = FreeFile
   Open createInstallerBatFile For Output As #FileNumber
   Print #FileNumber, data
   Close #FileNumber

   data = createInstallerBatFile & " 1>> " & logFile
   res = ExecCmd(data)

End Sub
Sub createUIQinstaller()

End Sub
Sub runImmediately(platform As String)
   Dim command As String
   Dim res As Integer
   
   ShowStatus "Run SISX File", True
   command = q(sisxFile)
   ShellExecute frmMain.hwnd, "open", command, 0, 0, SW_SHOWNORMAL
End Sub

Function readInputFile(inputfile As String, s() As Byte) As Integer
   Dim i As Integer
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
Sub copyBytes(s() As Byte, fromByte As Integer, toByte As Integer, FileNumber As Integer)
   Dim i As Integer
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

#End If 'NSBSymbian
