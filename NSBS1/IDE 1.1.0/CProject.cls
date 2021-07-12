VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CProject"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'Collections
Public TypeDefCollection As New Collection
Public CodeCollection As New Collection
Public DataCollection As New Collection
Public ParagCollection As New Collection
Public FormCollection As New Collection
Public MenuCollection As New Collection
Public DatabaseCollection As New Collection
Public LinkCollection As New Collection
Public LibraryCollection As New Collection
Public BitmapCollection As New Collection
Public ResourceCollection As New Collection
Public SelectCollection As New Collection

'User variables
Public Name As String
'Use property access to ensure 4 char length
Private m_strApplType As String * 4
Private m_strCreatorID As String * 4
Public pgm_script As String
Public termination_script As String
'LoRes Icons
Public SIF1 As String
Public SIF2 As String
Public SIF4 As String
Public SIF8 As String
Public SIF16 As String
Public LIF1 As String
Public LIF2 As String
Public LIF4 As String
Public LIF8 As String
Public LIF16 As String
'HiRes Icons
Public SIF1h As String
Public SIF2h As String
Public SIF4h As String
Public SIF8h As String
Public SIF16h As String
Public LIF1h As String
Public LIF2h As String
Public LIF4h As String
Public LIF8h As String
Public LIF16h As String
Public launcherName As String
Public LaunchVersion As String
Public IdNo As Integer
Public pathname As String
Public Saved As Boolean
Private m_nLargeIconID As Integer
Private m_nSmallIconID As Integer
Public theme As String
#If NSBSymbian Then
Public installFolder As String
Public Company As String
Public LauncherIconS60 As String
Public LauncherIconUIQ As String
Public UID3 As String
Public License As String
#End If

Public HighestSeqNo As Integer
Public obj_code As String
Public obj_code_len As Long
Public termin_obj_code As String
Public termin_obj_code_len As Long
'Dim formTOCLoc3 As Long
Dim TOCLoc3 As Long
'Dim TOCLoc4 As Long

'IDE variables
Public Dirty As Boolean
Private m_strGlobalID As String

'2000 marks beginning of CProject string table entries
#If NSBSymbian Then
   Private Const kTotalProps As Integer = 12
   Private Const kVersion As Integer = 9
#Else
   Private Const kTotalProps As Integer = 9
   Private Const kVersion As Integer = 9
#End If
Private Const kResStrings As Integer = 2000
Private Const kResStrings2200 As Integer = 2200
Private Const kErrStrings As Integer = 2050

Private Sub class_initialize()
Dim i As Integer
Dim sv As CDataElement
Dim av As CDataElement

'   Set model = Me

'What the Hell is dummyObject??  03/07/2001 MMD
'   Set dummyObject = New UIPushbutton
'   dummyObject.obj.Name = "..dummy***"
'   Set Nil = dummyObject

   Name = "Project1"
   ApplType = "appl"
#If NSBSymbian Then
   Company = ""
   installFolder = ""
   LauncherIconS60 = ""
   LauncherIconUIQ = ""
   LaunchVersion = "1,0,0"
   installFolder = "Installat."
   License = ""
   UID3 = gstrNextUID3
   gstrNextUID3 = Hex(CLng("&h" & gstrNextUID3) + 3)
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "NextUID3", gstrNextUID3
   theme = fileDirectory & "\themes\Symbian.pdb"
#Else
   LaunchVersion = ""
   theme = fileDirectory & "\themes\Classic.pdb"
#End If
   CreatorID = "Test"
   pgm_script = ""
   termination_script = ""
   SIF1 = ""
   LIF1 = ""
   launcherName = ""
   HighestSeqNo = 1000
   IdNo = GetNextSeqNo
   pathname = fileDirectory & "\Projects\" & Name & ".prj"
   Saved = False
   gsTheme = theme
   
'sgBox "init strings"
   For i = 1 To kStringWorkDEMax
      Set sv = New CDataElement
      sv.Kind = "s"
      sv.Length = 256
      sv.Name = "string_work"
      AddDataElement sv
      If i = 1 Then first_string_work = sv.tbl_no
   Next
   For i = 1 To kArithWorkDEMax
      Set av = New CDataElement
      av.Kind = "n"
      av.Name = "arith_work"
      AddDataElement av
      If i = 1 Then first_arith_work = av.tbl_no
   Next

   Dirty = False
'sgBox "after model init decnt=" + str(DataCollection.Count)
End Sub

Public Function PrcOut() As Long
Dim db As cDatabase     'added 09242003
Dim colNo As Integer  'added 09242003
Dim saveHighestSeqNo As Long
Dim eno As Integer
Dim lvl As Integer
Dim mnuBar As CMenuBar
Dim mnuBar2 As CMenuBar
Dim mnu As CMenuElem
Dim mnu2 As CMenuElem
'   Dim firstFormTOC As Long
Dim c As Byte
Dim cod As New CCodeModule
Dim view2 As CForm
Dim para As New CParaTbl
Dim t1 As Byte
Dim t2 As Byte
Dim t3 As Byte
Dim t4 As Byte
Dim id1 As Byte
Dim id2 As Byte
Dim offset As Long
Dim bmp As CBitmapFile
Dim res As CResourceFile
Dim tmploc As Long
Dim firstTocLocRecord3 As Long
'Dim firstTocLocRecord4 As Long
Dim prcHdr As prcHeader
Dim pdbHdr As prcHeader
Dim i As Integer
Dim j As Integer
Dim o As Object
Dim typerec As Byte
Dim Dummy As Byte
Dim dummy2 As Long
Dim ident As Integer
Dim noItems As Integer
Dim ctl As ctlOut
Dim fld As FieldOut

Dim slider As SliderOut
Dim gad As gadgetOut
Dim si As shiftIndicOut
Dim lab As labelOut
Dim lst As listOut
Dim scr As scrollbarOut
Dim tbl As tableOut
Dim titl As titleOut
Dim popup As popupOut
Dim wkstr As String
Dim frm As formOut
Dim vv As CForm
Dim wk As String
Dim bite As Byte
Dim byte1 As Byte
Dim byte2 As Byte
Dim byte3 As Byte
Dim byte4 As Byte
Dim de As CDataElement
Dim work As String
Dim one_num As Double
Dim q As Integer
Dim zeroTerm As Byte
Dim n As Integer
Dim x As Integer
Dim haveMenu(21) As Boolean
Dim menu2 As CMenu
Dim bmpform As bitmapOut
Dim randNo As Integer
Dim theByte As Byte
Dim jjj As Integer
Dim ii, ij As Integer
Dim icb As Byte
Dim icx As Byte
Dim icy As Byte
Dim byt As Byte
Dim nnn As Integer
Dim secByte As Byte
Dim intwk As Long
Dim iwk As Integer
Dim tocRecords As Byte '10/12/00 GH
Dim tocRec As Integer '10/12/00 GH
Dim oldWord As Long '10/12/00 GH
Dim newWord As Long '10/12/00 GH
Dim tocLoc As Integer '10/12/00 GH
Dim tocRecord(9) As Byte  '10/12/00 GH
Dim tocName As String '10/12/00 GH
Dim largeIconAddr As Long '10/12/00 GH
Dim iconRec As Integer '10/12/00 GH
Dim workLen As Integer '01/15/00 GH
Dim objCnt As Integer     'added 09092002
Dim navArray() As Integer 'added 10.13.06 GH

   saveHighestSeqNo = HighestSeqNo
   formCount = 0
   If glSerialNumber = "Unregistered Demo" And DemoSw = "n" Then Exit Function '02/28/01 GH defeat crack

   If FormCollection.count < 1 Then
      MsgBox gStringTable(1412), vbCritical 'Project will not compile without at least one form
      Exit Function
   End If

   zeroTerm = &H0
   openOutput
   outFile = 3
   Get #5, , prcHdr  'read hdr from template
   'write header
   For i = 0 To 31
      prcHdr.NameFld(i) = &H0
   Next
   wk = Name
   For i = 0 To 30
      If i > Len(wk) - 1 Then
         Exit For
      End If
      If Asc(Mid(wk, i + 1, 1)) > 255 Or Asc(Mid(wk, i + 1, 1)) < 1 And compileOkSw Then  '07/19/01 gh
         MsgBox gStringTable(3253) '"Project name cannot contain double byte characters"                      '07/19/01 gh
         Mid(wk, i + 1, 1) = "X"                                                          '07/19/01 gh
         compileOkSw = False                                                              '07/19/01 gh
         Exit For                                                                         '07/19/01 gh
      End If                                                                              '07/19/01 gh

      prcHdr.NameFld(i) = Asc(Mid(wk, i + 1, 1))
   Next
   
   If gbCopyProtect Then
      prcHdr.flags.w = prcHdr.flags.w + 16384 'set copy protect bit
   End If
   
'   prcHdr.type4 = Asc("l")  '10/12/00 GH
   'ApplType should always be "appl"
   prcHdr.type1 = Asc(Mid(ApplType, 1, 1)) '031301 MMD
   prcHdr.type2 = Asc(Mid(ApplType, 2, 1)) '031301 MMD
   prcHdr.type3 = Asc(Mid(ApplType, 3, 1)) '031301 MMD
   prcHdr.type4 = Asc(Mid(ApplType, 4, 1)) '031301 MMD

   prcHdr.id1 = Asc(Mid(CreatorID, 1, 1))
   prcHdr.id2 = Asc(Mid(CreatorID, 2, 1))
   prcHdr.id3 = Asc(Mid(CreatorID, 3, 1))
   prcHdr.id4 = Asc(Mid(CreatorID, 4, 1))

   randNo = 0
   PalmDatesTwo randNo, prcHdr.createTime(0), prcHdr.createTime(1), prcHdr.createTime(2), _
      prcHdr.createTime(3), prcHdr.modTime(0), prcHdr.modTime(1), prcHdr.modTime(2), _
      prcHdr.modTime(3)
   prcHdr.modTime(0) = prcHdr.createTime(0)
   prcHdr.modTime(1) = prcHdr.createTime(1)
   prcHdr.modTime(2) = prcHdr.createTime(2)
   prcHdr.modTime(3) = prcHdr.createTime(3)

   prcHdr.numRecords.w = 0 'fill in later
   Put #3, , prcHdr

   Seek #5, 78  '10/12/00 GH get number of contents records in template
   Get #5, , tocRecords  '10/12/00 GH

   'Copy TOC records; zap names of duplicate resources
   For i = 1 To tocRecords '10/12/00 GH
      Get #5, , tocRecord '10/12/00 GH
      tocName = Chr(tocRecord(0)) & Chr(tocRecord(1)) & Chr(tocRecord(2)) & Chr(tocRecord(3)) '10/12/00 GH
      If tocName = "tAIN" Then tocRecord(0) = Asc("X") 'template name '10/12/00 GH
      If tocName = "tver" Then tocRecord(0) = Asc("X") 'template version '10/12/00 GH
      If tocName = "tAIB" Then iconRec = i '10/12/00 GH
      Put #3, , tocRecord '10/12/00 GH
      'sgBox i & " " & tocName & " " & tocRecord(4) & " " & tocRecord(5) & " " & tocRecord(6) & " " & tocRecord(7) & " " & tocRecord(8) & " " & tocRecord(9)
   Next '10/12/00 GH

   '1023
   GoTo skipHdr
   'build pdb hdr
   For i = 0 To 31
      pdbHdr.NameFld(i) = &H0
   Next
   wk = Name + "-bsc"
   For i = 0 To 30
      If i > Len(wk) - 1 Then
         Exit For
      End If
      pdbHdr.NameFld(i) = Asc(Mid(wk, i + 1, 1))
   Next
   pdbHdr.flags.w = cvtWord(1)
   pdbHdr.version.w = cvtWord(0)  'pdb

   'if demo make diff 2 otherwise make rand # 0-9 but not 2
   If DemoSw = "n" Then
      Do
         randNo = Rnd() * 10
         If (Not randNo = 2) And (Not randNo = 0) Then
            Exit Do
         End If
      Loop
   Else
      randNo = 2
   End If
   PalmDatesTwo randNo, pdbHdr.createTime(0), pdbHdr.createTime(1), pdbHdr.createTime(2), _
      pdbHdr.createTime(3), pdbHdr.modTime(0), pdbHdr.modTime(1), pdbHdr.modTime(2), _
      pdbHdr.modTime(3)
   pdbHdr.modTime(0) = pdbHdr.createTime(0)
   pdbHdr.modTime(1) = pdbHdr.createTime(1)
   pdbHdr.modTime(2) = pdbHdr.createTime(2)
   pdbHdr.modTime(3) = pdbHdr.createTime(3)
   pdbHdr.backupTime(0) = 0
   pdbHdr.backupTime(1) = 0
   pdbHdr.backupTime(2) = 0
   pdbHdr.backupTime(3) = 0
   pdbHdr.modNum = 0
   pdbHdr.appInfo = 0
   pdbHdr.sortInfo = 0
   pdbHdr.type1 = Asc("D")
   pdbHdr.type2 = Asc("A")
   pdbHdr.type3 = Asc("T")
   pdbHdr.type4 = Asc("A")
   pdbHdr.id1 = Asc(Mid(CreatorID, 1, 1))
   pdbHdr.id2 = Asc(Mid(CreatorID, 2, 1))
   pdbHdr.id3 = Asc(Mid(CreatorID, 3, 1))
   pdbHdr.id4 = Asc(Mid(CreatorID, 4, 1))
   pdbHdr.uniqIdSeed = 0
   pdbHdr.nextRecordList = 0
   pdbHdr.numRecords.w = 0 'fill in later
   Put #3, , pdbHdr

skipHdr:
   firstTocLocRecord3 = Loc(3) + 1
  
   If m_nSmallIconID <> 0 Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   End If
   If Not launcherName = "" Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   End If
   If Not LaunchVersion = "" Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   End If
   If gbHiRes Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   End If
   If gbDana Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   End If

   'name record
   For i = 1 To 10
      c = &H0
      Put #3, , c
   Next
   'write empty program base rec
   For i = 1 To 10
      c = &H0
      Put #3, , c
   Next
   'write (model id#) empty  TOC record for pgm code
   If Not obj_code_len = 0 Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   End If
   'write termin code toc rec
   If Not termin_obj_code_len = 0 Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   End If
   'write out aView list toc
   For i = 1 To 10
      c = &H0
      Put #3, , c
   Next
   'write obj for data elems
   If DataCollection.count > (kStringWorkDEMax + kArithWorkDEMax) Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
      For i = 1 To 10  'and one for data init rec
         c = &H0
         Put #3, , c
      Next
   End If
   'write obj for parags
   If LinkCollection.count > 0 Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   End If

   'write rec for indep for code modules list
   If CodeCollection.count > 0 Then
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
      For Each cod In CodeCollection
         For i = 1 To 10
            c = &H0
            Put #3, , c
         Next
      Next
   End If

   For Each view2 In FormCollection
      'write form TOC record
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   Next
   For Each view2 In FormCollection
       If Not view2.Tips = "" Then
         'write (pref 6code rec for Tips
         For i = 1 To 10
            c = &H0
            Put #3, , c
         Next
      End If
      
      
      'Navigation resource (fnav) 'added 10.13.2006 GH
      For i = 1 To 10
        c = &H0
        Put #3, , c
      Next
      
      If Not view2.obj_code_len = 0 Then
         'write code TOC record
         For i = 1 To 10
            c = &H0
            Put #3, , c
         Next
      End If
      If Not view2.obj_code_len_after = 0 Then
         'write code TOC record
         For i = 1 To 10
            c = &H0
            Put #3, , c
         Next
      End If
      If Not view2.event_obj_code_len = 0 Then
         'write code TOC record
         For i = 1 To 10
            c = &H0
            Put #3, , c
         Next
      End If
     '06102002 start additions
        'write toc record for list of control names for a form
      For i = 1 To 10
          c = &H0
          Put #3, , c
      Next
     '06102002 end of additions
      For Each o In view2.ObjectCollection
'sgBox "obj has code of length=" + str(o.obj.obj_code_len)
         If Not o.obj.obj_code_len = 0 Then
            'write code TOC  record
'sgBox "writing toc rec for obj at " + str(Loc(4) + 1)
            For i = 1 To 10
               c = &H0
               Put #3, , c
            Next
         End If
      Next
   Next

   'menu def TOC entries
   For Each menu2 In MenuCollection
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   Next
   For Each menu2 In MenuCollection
      For Each mnuBar In menu2.MenuBars
         For Each mnu In mnuBar.MenuElems
            If Not mnu.obj_code_len = 0 Then
               For i = 1 To 10
                  c = &H0
                  Put #3, , c
               Next
            End If
         Next
      Next
   Next

   'write toc for bitmaps
   For Each bmp In BitmapCollection
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   Next

  'additions 09242003
  For Each db In gTarget.DatabaseCollection
      'only write out database fields rec if record layout was defined
      If db.formatRecord <> 0 Then
         For i = 1 To 10
                c = &H0
                Put #3, , c
         Next
      End If
      
  Next
  'end of additions 09242003

   'write toc for resources
   For Each res In ResourceCollection
      For i = 1 To 10
         c = &H0
         Put #3, , c
      Next
   Next

   'now, copy existing records from prc template
   Do While Not EOF(5)
      Get #5, , bite
      Put #3, , bite
   Loop

   TOCLoc3 = firstTocLocRecord3
   'TOCLoc4 = firstTocLocRecord4

'   If Not SIF1 = "" Then
   If m_nSmallIconID <> 0 Then
      'small icon
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      'write TOC rec with offset
      writeTOCRecord3 3, "tAIB", 1001, tmploc - 1
      Seek #3, tmploc
      TOCLoc3 = TOCLoc3 + 10
   End If

   If Not launcherName = "" Then
      'small icon
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      'write TOC rec with offset
      writeTOCRecord3 3, "tAIN", 1000, tmploc - 1
      Seek #3, tmploc
      TOCLoc3 = TOCLoc3 + 10
      writeOutString 3, launcherName
   End If

   If Not LaunchVersion = "" Then
      'small icon
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      'write TOC rec with offset
      writeTOCRecord3 3, "tver", 1000, tmploc - 1
      Seek #3, tmploc
      TOCLoc3 = TOCLoc3 + 10
      writeOutString 3, LaunchVersion
   End If

   If gbHiRes Then
      'High Res for HandEra
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      'write TOC rec with offset
      writeTOCRecord3 3, "sKst", 1000, tmploc - 1
      Seek #3, tmploc
      TOCLoc3 = TOCLoc3 + 10
      writeOutString 3, LaunchVersion
   End If

   If gbDana Then
      'WideScreen for AlphaSmart Dana
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      'write TOC rec with offset
      writeTOCRecord3 3, "wTap", 1000, tmploc - 1
      Seek #3, tmploc
      TOCLoc3 = TOCLoc3 + 10
      writeOutLong 3, 1
   End If

   wordBound 3
   tmploc = Loc(3) + 1
   Seek #3, TOCLoc3
   TOCLoc3 = TOCLoc3 + 10
   'write dev name rec w offset
   writeTOCRecord4 3, "nsba", 9904, tmploc - 1
   Seek #3, tmploc
   'Put #3, , SerialNumber                            '10.25.00 GH
   For i = 1 To Len(glSerialNumber)
      byte1 = Asc(Mid(glSerialNumber, i, 1))
      byte1 = byte1 + i + 65
      Put #3, , byte1
   Next i

   wordBound 3
   tmploc = Loc(3) + 1

   Seek #3, TOCLoc3
   TOCLoc3 = TOCLoc3 + 10
   'write TOC lst rec w offset
   writeTOCRecord4 3, "nsba", 9905, tmploc - 1

   Seek #3, tmploc
   'write base record
   For Each vv In FormCollection
      If vv.IsDefaultForm Then
         GoTo gotIt
      End If
   Next
   Set vv = New CForm
   Set vv = FormCollection(1)

gotIt:
   Put #3, , cvtWord(vv.IdNo)

'sgBox "decnt=" + str(DataCollection.Count) + " strmax=" + str(kStringWorkDEMax) + " wkmax=" + str(kArithWorkDEMax)
   writeOutInteger 3, DataCollection.count - (kStringWorkDEMax + kArithWorkDEMax)
   writeOutInteger 3, LinkCollection.count
   writeOutInteger 3, CodeCollection.count
   writeOutInteger 3, FormCollection.count
   
   writeOutInteger 3, first_string_work
   writeOutInteger 3, kStringWorkDEMax
   writeOutInteger 3, first_arith_work
   writeOutInteger 3, kArithWorkDEMax
   writeOutInteger 3, DatabaseCollection.count
   writeOutInteger 3, VersionInteg
   writeOutInteger 3, VersionFrac
   If LitePro = "l" Then
      writeOutInteger 3, 0
   ElseIf LitePro = "m" Then
      writeOutInteger 3, 1
   Else
      writeOutInteger 3, 2  'pro   "p"
   End If
   For nnn = 0 To 5
      If Not prcHdr.createTime(3) Mod 6 = nnn Then
         secByte = Rnd() * 255
      Else
         intwk = prcHdr.createTime(3)
         If DemoSw = "n" Then
            intwk = ((intwk + 123) * 98765)
         Else
            intwk = ((intwk + 913) * 11314)
         End If
         secByte = intwk Mod 255
      End If
      Put #3, , secByte
   Next

   If DemoSw = "n" Then
      iwk = intwk Mod 128
   Else
      iwk = intwk Mod 128 + 128
   End If
   secByte = iwk
   Put #3, , secByte
   secByte = 255 - iwk
   Put #3, , secByte
   'now put out creation date
   Put #3, , prcHdr.createTime(0)
   Put #3, , prcHdr.createTime(1)
   Put #3, , prcHdr.createTime(2)
   Put #3, , prcHdr.createTime(3)
''dbug "setting def screen to " + str(vv.idNo)

   If Not obj_code_len = 0 Then
      wordBound 3
      tmploc = Loc(3) + 1

      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'wrte TOC lst rec w offset
      writeTOCRecord4 3, "nsba", 9906, tmploc - 1
      Seek #3, tmploc
      'write model code record
      'dbug "before write loc=" + str(Loc(3))
      writeOutCode 3, obj_code, obj_code_len
      'dbug "*" + obj_code + "*" + "  at offset=" + str(Loc(3))
      'dbug "wrote model code len=" + str(obj_code_len)
   End If

   If Not termin_obj_code_len = 0 Then
      wordBound 3
      tmploc = Loc(3) + 1

      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'wrte TOC lst rec w offset
      writeTOCRecord4 3, "nsba", 9915, tmploc - 1
      Seek #3, tmploc
      'write model termination code record
      'dbug "before write loc=" + str(Loc(4)) '0401
      writeOutCode 3, termin_obj_code, termin_obj_code_len
      'dbug "*" + obj_code + "*" + "  at offset=" + str(Loc(4))
      'dbug "wrote model code len=" + str(obj_code_len)
   End If

   wordBound 3
   tmploc = Loc(3) + 1

   Seek #3, TOCLoc3
   TOCLoc3 = TOCLoc3 + 10 'wrte TOC rec for aView list w offset
   writeTOCRecord4 3, "nsba", 9907, tmploc - 1
   Seek #3, tmploc

'dbug "next output at loc=" + str(loc(3))
   'write aView list recor
   For Each view2 In FormCollection
      writeOutInteger 3, view2.IdNo
      writeOutString 3, view2.Name      'added 06102002 need names for NextScreen varname
   Next

skipview:
   If DataCollection.count > (kStringWorkDEMax + kArithWorkDEMax) Then
      wordBound 3
      tmploc = Loc(3) + 1

      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'wrte TOC rec for data elems w offset
      writeTOCRecord4 3, "nsba", 9908, tmploc - 1
      Seek #3, tmploc
      Dim varCount As Integer
      varCount = 0

      For Each de In DataCollection
         If de.tbl_no <= (kStringWorkDEMax + kArithWorkDEMax) Then
            GoTo dontWriteData
         End If
         varCount = varCount + 1
         writeOutInteger 3, de.tbl_no
         writeOutInteger 3, de.Length
         writeOutInteger 3, de.Dgt_Bef
         writeOutInteger 3, de.Dgt_Aft
         writeOutInteger 3, de.max_no_values1
         writeOutInteger 3, de.max_no_values2
         writeOutInteger 3, de.max_no_values3
         writeOutByte 3, Asc(Mid$(de.Kind, 1, 1))
         'Put #3, , de.kind
         Put #3, , de.ByteFlag              '821 added *******************
         If de.isConstant = True Then       '821 added *******************
            writeOutByte 3, &H1             '821 added *******************
         Else                               '821 added *******************
            writeOutByte 3, &H0             '821 added *******************
         End If                             '821 added *******************
         wordBound 3
         'Put #3, , &H0

dontWriteData:
      Next
      If varCount > 3600 Then MsgBox (gStringTable(3351)) & " " & varCount 'Variable table overflow. Reduce number of variables and literals.
      'MsgBox "Size of Data Element record =" & Loc(3) - tmploc & " for " & varCount & " records."
      wordBound 3
      tmploc = Loc(3) + 1
    
      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'wrte TOC rec for initial data values
      writeTOCRecord4 3, "nsba", 9909, tmploc - 1
      Seek #3, tmploc
      'write data init record
      For Each de In DataCollection
         If de.tbl_no < (kStringWorkDEMax + kArithWorkDEMax) Then
            GoTo dontWriteInit
         End If
         If Mid(de.Name, 1, 1) = "." Then 'have alpha literal
            writeOutInteger 3, de.tbl_no
            work = de.single_value
            workLen = getWriteOutStringLen(work)        '04/25/01 GH
            writeOutInteger 3, workLen + 1              '01/15/00 GH
            writeOutString 3, work
         ElseIf Mid(de.Name, 1, 1) = "+" Then 'have numeric literal
            one_num = de.single_value
            writeOutInteger 3, de.tbl_no
            work = str(one_num)
            Do
               If Left(work, 1) = " " Then
                  work = Right$(work, Len(work) - 1)
               Else
                  Exit Do
               End If
            Loop
            writeOutInteger 3, Len(work) + 1
            writeOutString 3, work
         ElseIf Left(de.Name, 3) = "nsb" Or de.Name = "true" Then
            one_num = de.single_value
            writeOutInteger 3, de.tbl_no
            work = str(one_num)
            Do
               If Left(work, 1) = " " Then
                  work = Right$(work, Len(work) - 1)
               Else
                  Exit Do
               End If
            Loop
            writeOutInteger 3, Len(work) + 1
            writeOutString 3, work
         End If
dontWriteInit:
      Next
      writeOutInteger 3, 0  'trailing 0 for id indics end
      If Loc(3) - tmploc > 65535 Then MsgBox (gStringTable(3366)) & " " & Loc(3) - tmploc 'Literal table overflow (65535 max). Reduce the number of string and numeric literals in your code.
   End If

   If LinkCollection.count > 0 Then
      wordBound 3
      tmploc = Loc(3) + 1
    
      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'wrte TOC rec for parags w offset
      writeTOCRecord4 3, "nsba", 9910, tmploc - 1
      Seek #3, tmploc
      'write pqarags record
      For Each para In LinkCollection
         writeOutInteger 3, para.moduleId
         writeOutUnsignedInteger 3, para.offset + 4  '***revised 3/13/2001 ***
      Next
   End If

   If CodeCollection.count > 0 Then
      wordBound 3
      tmploc = Loc(3) + 1

      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'wrte TOC rec for code modules w offset
      writeTOCRecord4 3, "nsba", 9912, tmploc - 1
      Seek #3, tmploc
      'write pqarags record
      For Each cod In CodeCollection
         writeOutInteger 3, cod.IdNo
         writeOutInteger 3, cod.offset
      Next
      For Each cod In CodeCollection
         wordBound 3
         tmploc = Loc(3) + 1

         Seek #3, TOCLoc3
         TOCLoc3 = TOCLoc3 + 10
         'wrte TOC rec for code modules w offset
         writeTOCRecord4 3, "nsba", cod.IdNo, tmploc - 1
         Seek #3, tmploc
         'write code module code record
         writeOutCode 3, cod.obj_code, cod.obj_code_len
      Next
   End If
   'TOCLoc3 = TOCLoc3 - 10

   For Each view2 In FormCollection
'dbug "processing view=" + view2.title
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'write TOC rec with offset
      writeTOCRecord3 3, "tFRM", view2.IdNo, tmploc - 1
'dbug "wrote the toc rec"
      Seek #3, tmploc
'dbug "going to aView.prc.out"
      view2.PrcOut
'dbug "before form out -- offset=" + str(Loc(3))
      Open DownloadPath + "__temp7.__7" For Binary As #7
      Get #7, , frm
      Put #3, , frm
      Close 7
'dbug "wrote 'frm' and closed 7 -- offset=" + str(Loc(3))
      'put form TOC recs out
      Open DownloadPath + "__temp8.__8" For Binary As #8
      wordBound 3
'      firstFormTOC = Loc(3) + 1

      Do While Not EOF(8)
         If EOF(8) Then
            Exit Do
         End If
         Get #8, , typerec

         If EOF(8) Then
            Exit Do
         End If
        '04012005  commented out  put #3, , typerec
        'start additions 04012005
        If typerec = &HE Then
           byt = &H1
           Put #3, , byt  'slider is type of control
        Else
           Put #3, , typerec
        End If
        'end additions 04012005

         Get #8, , Dummy
         Put #3, , Dummy
         Get #8, , byte1
         Get #8, , byte2
         Get #8, , byte3
         Get #8, , byte4
         offset = byte4 + byte3 * 256& + byte2 * 65536 + byte1 * 65536 * 256
'sgBox "found #8 typerec=" + str(typerec) + " offset=" + str(offset)
         offset = offset + LOF(8) + 68
         writeOutLong 3, offset
         'Get #8, , ident
         'Put #3, , ident
'dbug "found #8 rec --obj type=" + str(typerec) + " dummy=" + str(dummy) + "offset=" + str(offset)
      Loop
      Close 8
'dbug "before output -- offset=" + str(Loc(3))
      Open DownloadPath + "__temp6.__6" For Binary As #6
      Open DownloadPath + "__temp8.__8" For Binary As #8
      Open DownloadPath + "__temp9.__9" For Binary As #9
      'formTOCLoc3 = firstFormTOC + 2
      Do While Not EOF(8)
         Get #8, , typerec
         If EOF(8) Then
            Exit Do
         End If
         Get #8, , Dummy
         Get #8, , dummy2
         'Get #8, , ident
'dbug "processing typerec=" + str(typerec)
         'tmploc = Loc(3) + 1
         'Seek #3, formTOCLoc3
         'outLong 3, tmploc - 1
         'formTOCLoc3 = formTOCLoc3 + 6
         'Seek #3, tmploc
         inputWordBound 9
'sgBox "reading from 9 at loc=" + str(Loc(9))
         wordBound 3

         Select Case typerec
         Case &H0
            Get #9, , fld
            Put #3, , fld
         Case &H1
            Get #9, , ctl
            Put #3, , ctl
            Get #6, , q
            wkstr = Space(q)
            Get #9, , wkstr
'sgBox "found ctl len=" + str(q) + " string=" + wkstr + "  of length=" + str(Len(wkstr)) + "  len s/b=" + str(q)
            Get #9, , Dummy
'sgBox "ctl dummy is " + str(dummy)
            Put #3, , wkstr
            Put #3, , zeroTerm
         Case &H2
            Get #9, , lst
            Put #3, , lst
            Get #6, , noItems
            For j = 1 To noItems
               For jjj = 1 To 4
                  Get #9, , theByte
                  Put #3, , theByte
               Next
            Next
            
            For j = 1 To noItems
               Get #6, , q
               wkstr = Space(q)
               Get #9, , wkstr
'sgBox "found len=" + str(q) + "  string=" + wkstr + "  of length=" + str(Len(wkstr)) + "  len s/b=" + str(q)
               Get #9, , Dummy
'sgBox "found dummy=" + str(dummy)
               Put #3, , wkstr
               Put #3, , zeroTerm
            Next j
         Case &H3
            Get #9, , tbl
            Put #3, , tbl
            'additions 09242003
            Get #6, , q
            wkstr = Space(q)
            Get #9, , wkstr
            Put #3, , wkstr
            'end additions 09242003
         Case &H4
            Get #9, , bmpform
            Put #3, , bmpform
         Case &H8
            Get #9, , lab
            Put #3, , lab
            Get #6, , q
''dbug "found string of length in label=" + str(q)
            wkstr = Space(q)
            Get #9, , wkstr
            Get #9, , Dummy
            Put #3, , wkstr
            Put #3, , zeroTerm
         Case &H9
            Get #9, , titl
            Put #3, , titl
            Get #6, , q
''dbug "found string of length in label=" + str(q)
            wkstr = Space(q)
            Get #9, , wkstr
            Get #9, , Dummy
            Put #3, , wkstr
            Put #3, , zeroTerm
         Case &HA
            Get #9, , popup
            Put #3, , popup
         Case &HB
            Get #9, , si
            Put #3, , si
         Case &HC
            Get #9, , gad
            Put #3, , gad
         Case &HD
            Get #9, , scr
            Put #3, , scr
          'additions 04012005
          Case &HE
            Get #9, , slider
            Put #3, , slider
          'end additions 04012005
         Case Else
            MsgBox gStringTable(3254) + str(typerec) '"error--can't recognize frm subobject " + str(typerec)
         End Select
'dbug "after output -- offset=" + str(Loc(3))
      Loop

      Close 6
      Close 8
      Close 9
   Next

   For Each view2 In FormCollection
      'write Tips
      If Not view2.Tips = "" Then
         wordBound 3
         tmploc = Loc(3) + 1
         Seek #3, TOCLoc3
         TOCLoc3 = TOCLoc3 + 10
         'write TOC with offset
         writeTOCRecord4 3, "tSTR", view2.TipsIdNo, tmploc - 1
         Seek #3, tmploc
         Put #3, , Replace(view2.Tips, vbCrLf, vbLf)
         c = &H0
         Put #3, , c
      End If
      
      'Navigation resource (fnav) 'added 10.13.2006 GH
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'write TOC with offset
      writeTOCRecord4 3, "fnav", view2.IdNo, tmploc - 1
      Seek #3, tmploc
      navArray = BuildNavArray(view2)
      For i = 0 To UBound(navArray) - 1
        writeOutInteger 3, navArray(i)
      Next
      c = &H0
      Put #3, , c
      
      If Not view2.obj_code_len = 0 Then
         wordBound 3
         tmploc = Loc(3) + 1
         Seek #3, TOCLoc3
         TOCLoc3 = TOCLoc3 + 10
         'write TOC with offset
         writeTOCRecord4 3, "nsba", view2.obj_code_id, tmploc - 1
         Seek #3, tmploc
         'write aView code  record
         writeOutCode 3, view2.obj_code, view2.obj_code_len
      End If

      If Not view2.obj_code_len_after = 0 Then
         wordBound 3
         tmploc = Loc(3) + 1
         Seek #3, TOCLoc3
         TOCLoc3 = TOCLoc3 + 10
         'write TOC with offset
         writeTOCRecord4 3, "nsba", view2.IdNo, tmploc - 1
         Seek #3, tmploc
         'write aView code  record
         writeOutCode 3, view2.obj_code_after, view2.obj_code_len_after
      End If

      If Not view2.event_obj_code_len = 0 Then
         wordBound 3
         tmploc = Loc(3) + 1
         Seek #3, TOCLoc3
         TOCLoc3 = TOCLoc3 + 10
         'write TOC with offset
         writeTOCRecord4 3, "nsba", 10800 - view2.IdNo, tmploc - 1
         Seek #3, tmploc
         'write aView code  record
         writeOutCode 3, view2.event_obj_code, view2.event_obj_code_len
      End If
      '06102002 start additions
      'write out record for list of control names for the form
        wordBound 3

        tmploc = Loc(3) + 1

         Seek #3, TOCLoc3
        TOCLoc3 = TOCLoc3 + 10
        'write TOC with offset

        writeTOCRecord4 3, "olst", view2.IdNo, tmploc - 1
        Seek #3, tmploc
        'write view code  record
        objCnt = 0                            'added 09092002
        For Each o In view2.ObjectCollection  'added 09092002
            If o.obj.Kind = "pop" Then        'added 09092002
               objCnt = objCnt + 3            'added 09092002
            Else                              'added 09092002
               objCnt = objCnt + 1            'added 09092002
            End If                            'added 09092002
        Next                                  'added 09092002
        writeOutInteger 3, objCnt             'added 09092002
        '09092002 writeOutInteger 3, view2.ObjectCollection.count
        For Each o In view2.ObjectCollection
           writeOutString 3, o.obj.Name
           If o.obj.Kind = "pop" Then          'added 09092002
             writeOutString 3, o.obj.Name      'added 09092002
             writeOutString 3, o.obj.Name      'added 09092002
            End If                             'added 09092002
        Next
      '06102002 end of additions

      For Each o In view2.ObjectCollection
         If Not o.obj.obj_code_len = 0 Then
            wordBound 3
            tmploc = Loc(3) + 1
'sgBox "updating toc at " + str(tocloc3) + " to point to " + str(tmploc)
            Seek #3, TOCLoc3
            TOCLoc3 = TOCLoc3 + 10
            'write TOC with offset
            If o.obj.Kind = "bmp" Then
               writeTOCRecord4 3, "nsba", o.ResourceId, tmploc - 1
            ElseIf o.obj.Kind = "pop" Then
               'use id of list that is part of popup
               writeTOCRecord4 3, "nsba", o.obj.IdNo, tmploc - 1
            Else
               writeTOCRecord4 3, "nsba", o.obj.IdNo, tmploc - 1
            End If
            Seek #3, tmploc
            'write an object's code  record
            writeOutCode 3, o.obj.obj_code, o.obj.obj_code_len
         End If
      Next
   Next

  'menu entries
   For Each menu2 In MenuCollection
      GenMenuTBAR menu2, 1
   Next
   For Each menu2 In MenuCollection
      For Each mnuBar In menu2.MenuBars
         For Each mnu In mnuBar.MenuElems
            If Not mnu.obj_code_len = 0 Then
               wordBound 3
               tmploc = Loc(3) + 1
               Seek #3, TOCLoc3
               TOCLoc3 = TOCLoc3 + 10
               'write TOC with offset
               writeTOCRecord4 3, "nsba", mnu.IdNo, tmploc - 1
               Seek #3, tmploc
               'write an object's code  record
               writeOutCode 3, mnu.obj_code, mnu.obj_code_len
            End If
         Next
      Next
   Next

   'additions 09242003
   ' ouptut FILE RECORD LAYOUTS
   nnn = 0
   For Each db In gTarget.DatabaseCollection
      'only write out database fields rec if record layout was defined
      nnn = nnn + 1  'bump dbase id #
      If db.formatRecord <> 0 Then
          wordBound 3
          tmploc = Loc(3) + 1
          Seek #3, TOCLoc3
          TOCLoc3 = TOCLoc3 + 10
          'write TOC rec with offset
          writeTOCRecord3 3, "Fldd", nnn, tmploc - 1
    'dbug "wrote the toc rec"
          Seek #3, tmploc
          colNo = 0
          
          writeOutString 3, db.deviceFilename
          writeOutString 3, db.creator
          Put #3, , cvtWord(db.keyFieldTblNo)           'added 02042004
          'Put #3, , cvtWord(db.lastDbFldNo - db.firstDbFldNo + 1) 'no of fields defined
          'start insertions 02042004
          If db.keyFieldTblNo <> 0 Then
              Put #3, , cvtWord(db.lastDbFldNo - db.firstDbFldNo + 2) 'no of fields defined +1 for keyfield
              'put out key field as db fld
              Set data = find_de_by_no(db.keyFieldTblNo)
              Put #3, , cvtWord(db.keyFieldTblNo)      'tblNo of keyfield data element
              Put #3, , cvtWord(colNo)  'seq column no
              colNo = colNo + 1
              If data.Kind = "i" Then
                 If data.ByteFlag = &H80 Then
                    Put #3, , cvtWord(1)  'long int
                     
                 Else
                    Put #3, , cvtWord(5)  'short int
                 End If
              ElseIf data.Kind = "s" Then
                 If data.ByteFlag = &H80 Then
                    Put #3, , cvtWord(7) 'byte
                 Else
                    Put #3, , cvtWord(0)   'string
                 End If
              ElseIf data.Kind = "n" Then
                 If data.ByteFlag = &H40 Then
                    Put #3, , cvtWord(2)      'double
                 ElseIf data.ByteFlag = &H20 Then
                     Put #3, , cvtWord(6) 'single
                 End If
                 
                 
              ElseIf data.Kind = "t" Then
                 Put #3, , cvtWord(4)   'time
              ElseIf data.Kind = "d" Then
                 Put #3, , cvtWord(3)   'date
              End If
              
              writeOutString 3, data.Name
              writeOutByte 3, &H1   'keyfield
          Else
             'don't count keyfield in fld count
             Put #3, , cvtWord(db.lastDbFldNo - db.firstDbFldNo + 1) 'no of fields defined
          
          End If
          'end insertions 02042004
          For i = db.firstDbFldNo To db.lastDbFldNo
              Set data = find_de_by_no(i)
              Put #3, , cvtWord(i)      'tblNo of data element
              Put #3, , cvtWord(colNo)  'seq column no
              colNo = colNo + 1
              If data.Kind = "i" Then
                 If data.ByteFlag = &H80 Then
                    Put #3, , cvtWord(1)  'long int
                     
                 Else
                    Put #3, , cvtWord(5)  'short int
                 End If
              ElseIf data.Kind = "s" Then
                 If data.ByteFlag = &H80 Then
                    Put #3, , cvtWord(7) 'byte
                 Else
                    Put #3, , cvtWord(0)   'string
                 End If
              ElseIf data.Kind = "n" Then
                 If data.ByteFlag = &H40 Then
                    Put #3, , cvtWord(2)      'double
                 ElseIf data.ByteFlag = &H20 Then
                     Put #3, , cvtWord(6) 'single
                 End If
                 
                 
              ElseIf data.Kind = "t" Then
                 Put #3, , cvtWord(4)   'time
              ElseIf data.Kind = "d" Then
                 Put #3, , cvtWord(3)   'date
              End If
              
              writeOutString 3, data.Name
              
              '02042004If db.noKeyFields And colNo = 1 Then   'keyflag
              '02042004   writeOutByte 3, &H1
              '02042004Else
                  
                  writeOutByte 3, &H0  'not a key field
              
              '02042004 End If
          Next
      End If
   Next
   'end additions 09242003

   'write resource entries
   For Each res In ResourceCollection
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'write TOC rec with offset
      writeTOCRecord3 3, res.ResourceType, res.IdNo, tmploc - 1
      Seek #3, tmploc
      'write out resource entry and bits
      res.PrcOut (res.ResourcePath)
   Next

   'write bitmap entries -- this should be last
   For Each bmp In BitmapCollection
      wordBound 3
      tmploc = Loc(3) + 1
      Seek #3, TOCLoc3
      TOCLoc3 = TOCLoc3 + 10
      'write TOC rec with offset
      writeTOCRecord3 3, "Tbmp", bmp.IdNo, tmploc - 1
   Next
      
   wordBound 3
'   If Not LIF1 = "" Then
   If m_nLargeIconID <> 0 Then
      tmploc = Loc(3) + 1
      Seek #3, 76 + 10 * iconRec '10/12/00 GH
      Get #3, , byte1  '10/12/00 GH
      Get #3, , byte2 '10/12/00 GH
      Get #3, , byte3 '10/12/00 GH
      oldWord = byte1 * 65536# + byte2 * 256# + byte3 '10/12/00 GH
      newWord = oldWord + (TOCLoc3 - firstTocLocRecord3) + 1 '10/12/00 GH
      Seek #3, newWord '10/12/00 GH

   End If
   
   i = (TOCLoc3 - firstTocLocRecord3) / 10 + tocRecords '10/12/00 GH
   Seek #3, 77 'num rec slot
   Put #3, , cvtWord(i)
   TOCLoc3 = TOCLoc3 - 10

   'Fix up pointers in TOC to allow for extra TOC records that were added GH 10/12/00
   For tocRec = 0 To tocRecords - 1
      tocLoc = 85 + tocRec * 10 '02.16.01 GH
      Seek #3, tocLoc
      Get #3, , byte1
      Get #3, , byte2
      Get #3, , byte3      '02.16.01 GH
      Get #3, , byte4      '02.16.01 gh
      oldWord = byte1 * 16777216# + byte2 * 65536# + byte3 * 256# + byte4 '02.16.01 gh
      newWord = oldWord + (TOCLoc3 - firstTocLocRecord3) + 10
      'If newWord > 32767 Then newWord = newWord - 65535 '02.16.01 gh
      Seek #3, tocLoc
      Call writeOutLong(3, newWord) '02.16.01 gh
   Next

   Close 5
   Close 3
   'note ....if compileOkSw is false, the generation had errors
   wkstr = Dir(DownloadPath + "__temp*.*")
   'sgBox "wkstr=" + wkstr
   Do While Not wkstr = ""
      Kill DownloadPath & wkstr
      wkstr = Dir
   Loop
   HighestSeqNo = saveHighestSeqNo
   
   WriteOutBitmaps
   
   wk = DownloadPath + gTarget.Name + ".prc"
   Open wk For Binary As #3
   PrcOut = LOF(3)
   Close 3

End Function

Public Sub Restore()
Dim i As Long
Dim version As Integer
Dim oldversion As Integer
Dim oldFrac As Integer
Dim iconList As String
Dim Dummy As String
Dim s() As String

   Input #1, version
   If version > kVersion Then
      MsgBox gStringTable(3255) & version '"Error: Invalid Project Version (" & version & ")"
      End
   End If

   Input #1, Name, m_strApplType, m_strCreatorID, HighestSeqNo
   If m_strApplType = "Test" Then ApplType = "appl"

   If version > 4 Then Input #1, oldversion, oldFrac

   Input #1, pgm_script
   ProcessScript pgm_script, FromDisk

   If version > 1 Then
      RestoreImages SIF1, SIF2, SIF4, SIF8, SIF16, SIF1h, SIF2h, SIF4h, SIF8h, SIF16h
      RestoreImages LIF1, LIF2, LIF4, LIF8, LIF16, LIF1h, LIF2h, LIF4h, LIF8h, LIF16h
   End If
   If version > 2 Then Input #1, launcherName
   If version > 3 Then Input #1, LaunchVersion
#If NSBSymbian Then
   If version > 7 Then
      Input #1, Company
      Input #1, installFolder
      If installFolder = "" Then installFolder = "Installat."
      Input #1, iconList
      Input #1, UID3
      If UID3 = "" Then
         UID3 = gstrNextUID3
         gstrNextUID3 = Hex(CLng("&h" & gstrNextUID3) + 3)
         MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "NextUID3", gstrNextUID3
      End If
      s = Split(iconList, ",")
      If UBound(s) = -1 Then
         LauncherIconS60 = ""
         LauncherIconUIQ = ""
         License = ""
      ElseIf UBound(s) = 0 Then
         If Right(s(0), 3) = "svg" Then LauncherIconS60 = s(0)
         If Right(s(0), 3) = "bmp" Then LauncherIconUIQ = s(0)
         License = ""
      ElseIf UBound(s) = 1 Then
         If Right(s(0), 3) = "svg" Then LauncherIconS60 = s(0)
         If Right(s(1), 3) = "bmp" Then LauncherIconUIQ = s(1)
         License = ""
      ElseIf UBound(s) = 2 Then
         If Right(s(0), 3) = "svg" Then LauncherIconS60 = s(0)
         If Right(s(1), 3) = "bmp" Then LauncherIconUIQ = s(1)
         License = s(2)
      End If
      If LaunchVersion = "" Then LaunchVersion = "1,0,0"
    Else
      Company = ""
      installFolder = ""
      LauncherIconS60 = ""
      LauncherIconUIQ = ""
      License = ""
      LaunchVersion = "1,0,0"
      installFolder = "Installat."
      UID3 = gstrNextUID3
      gstrNextUID3 = Hex(CLng("&h" & gstrNextUID3) + 3)
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "NextUID3", gstrNextUID3
      theme = GetRelativePath(CurDir, fileDirectory & "\themes\Classic.pdb")
   End If
#Else
   If version > 7 Then
      Input #1, Dummy
      Input #1, Dummy
      Input #1, Dummy
      Input #1, Dummy
   End If
#End If
   If version > 8 Then
      Input #1, theme
   End If
   gsTheme = theme

   If version > 5 Then
      Input #1, termination_script
      ProcessScript termination_script, FromDisk
   End If
   If version > 6 Then
      m_nLargeIconID = Val(SIF1)
      m_nSmallIconID = Val(LIF1)
   End If
   Saved = True
End Sub

Public Sub Save()
Dim i As Integer
Dim strTemp As String
Dim obj As Object, o2 As Object
Dim frm As frmCode

   On Error GoTo SaveError
   Open Me.pathname For Output As #1

   Write #1, "mdl"
   Write #1, kVersion
   Write #1, Name, ApplType, CreatorID, HighestSeqNo, VersionInteg, VersionFrac

   Set frm = frmMain.GetMDIChild(GlobalID & "|startup")
   If Not frm Is Nothing Then frm.Save
   strTemp = pgm_script
   ProcessScript strTemp, ToDisk
   Write #1, strTemp

'   SaveImages SIF1, SIF2, SIF4, SIF8
'   SaveImages LIF1, LIF2, LIF4, LIF8
   Write #1, m_nLargeIconID
   Write #1, m_nSmallIconID
   Write #1, launcherName
   Write #1, LaunchVersion
#If NSBSymbian Then
   Write #1, Company
   Write #1, installFolder
   Write #1, Join(Array(GetRelativePath(gTarget.pathname, LauncherIconS60), _
                        GetRelativePath(gTarget.pathname, LauncherIconUIQ), _
                        GetRelativePath(gTarget.pathname, License)), ",")
   Write #1, UID3
#Else
   Write #1, ""
   Write #1, ""
   Write #1, ""
   Write #1, ""
#End If
   Write #1, GetRelativePath(gTarget.pathname, theme)

   Set frm = frmMain.GetMDIChild(GlobalID & "|termination")
   If Not frm Is Nothing Then frm.Save
   strTemp = termination_script
   ProcessScript strTemp, ToDisk
   Write #1, strTemp

   For Each obj In BitmapCollection
      obj.Save
   Next
   For Each obj In ResourceCollection
      obj.Save
   Next
   For Each obj In MenuCollection
      obj.Save
   Next
   For Each obj In CodeCollection
      obj.Save
   Next
   For Each obj In FormCollection
      obj.Save
   Next
   Write #1, "end"
   Close #1
   Saved = True
   Exit Sub

SaveError:
   MsgBox gStringTable(3256) & vbCrLf & err.Description '"Unable to save project"
End Sub

Public Sub Paste(ByRef strLines() As String)
Dim frm As CForm
Dim mnu As New CMenu
Dim obj As Object

   If strLines(0) <> kClipboardHeader Then Exit Sub
   Select Case LCase(UnQuote(strLines(1)))
   Case "vew"
      Set frm = AddNewForm
      frm.Paste strLines
      gfProjectExplorer.AddNewForm frm, Me
      For Each obj In frm.ObjectCollection
         gfProjectExplorer.AddNewControl obj, frm
      Next
   Case "mnu"
      mnu.IdNo = GetNextSeqNo
      mnu.SetGlobalID GlobalID
      mnu.Paste strLines, Me
      AddMenu mnu
      gfProjectExplorer.UpdateProjectMenus Me
   End Select
End Sub

Public Function AddNewForm() As CForm
Dim frm As New CForm
Dim tempForm As CForm
Dim i As Integer
Dim strTitle As String

   frm.obj_code_id = GetNextSeqNo
   frm.IdNo = GetNextSeqNo

   i = 0
   strTitle = ""
   Do While Len(strTitle) = 0
      i = i + 1
      strTitle = "Form" & i
      For Each tempForm In FormCollection
         If StrComp(tempForm.Title, strTitle, vbTextCompare) = 0 Then
            strTitle = ""
         End If
      Next
   Loop
   frm.Title = strTitle

   FormCollection.Add frm
   frm.Project = Me
   Set AddNewForm = frm
   Dirty = True
End Function

Public Sub RemoveForm(ByVal strGlobalID As String)
Dim i As Integer

   For i = 1 To FormCollection.count
      If FormCollection(i).GlobalID = strGlobalID Then
         FormCollection.Remove i
         Exit For
      End If
   Next
   Dirty = True
   If FormCollection.count < 1 Then MsgBox gStringTable(1412), vbCritical 'Project will not compile without at least one form
   
End Sub

Public Function AddNewBitmap(ByRef strFilename As String) As CBitmapFile
Dim bmp As New CBitmapFile

   bmp.IdNo = GetNextSeqNo
   bmp.SetFileName strFilename
   BitmapCollection.Add bmp
   bmp.Project = Me
   Set AddNewBitmap = bmp
   Dirty = True
End Function

Public Sub RemoveBitmap(ByVal strGlobalID As String)
Dim i As Integer

   For i = 1 To BitmapCollection.count
      If BitmapCollection(i).GlobalID = strGlobalID Then
         BitmapCollection.Remove i
         Exit For
      End If
   Next
   Dirty = True
End Sub
Public Function AddNewResource(ByRef strFilename As String) As CResourceFile
Dim bmp As New CResourceFile

   bmp.IdNo = GetNextSeqNo
   bmp.SetFileName strFilename
   ResourceCollection.Add bmp
   bmp.Project = Me
   Set AddNewResource = bmp
   Dirty = True
End Function

Public Sub RemoveResource(ByVal strGlobalID As String)
Dim i As Integer

   For i = 1 To ResourceCollection.count
      If ResourceCollection(i).GlobalID = strGlobalID Then
         ResourceCollection.Remove i
         Exit For
      End If
   Next
   Dirty = True
End Sub

Public Function AddModule(Optional ByRef strFilename As String = "") As CCodeModule
Dim cMod As New CCodeModule
Dim cmod2 As CCodeModule
Dim strModule As String
Dim i As Integer

   If Len(strFilename) <> 0 Then
      If Dir(strFilename, vbNormal) = "" Then
         MsgBox gStringTable(3257) + strFilename '"Unable to find Module '" & strFilename & "'"
         Exit Function
      End If
   End If

   cMod.IdNo = GetNextSeqNo
   If Len(strFilename) = 0 Then
      For i = Asc("a") To Asc("z")
         strModule = Left(Me.pathname, InStrRev(Me.pathname, ".") - 1) & Chr(i) & ".cod"
         For Each cmod2 In CodeCollection
            If cmod2.path = strModule Then GoTo AddModule_FindNext
         Next
         cMod.SetFileName strModule
         GoTo AddModule_FoundNext
AddModule_FindNext:
      Next
'      cmod.SetFileName Left(Me.pathname, InStrRev(Me.pathname, ".") - 1) & ".cod"
   Else
      cMod.SetFileName strFilename
      cMod.OpenModule
   End If

AddModule_FoundNext:
   CodeCollection.Add cMod
   Set AddModule = cMod
   Dirty = True
End Function

Public Sub RemoveModule(ByVal strGlobalID As String)
Dim i As Integer

   For i = 1 To CodeCollection.count
      If CodeCollection(i).GlobalID = strGlobalID Then
         CodeCollection.Remove i
         Exit For
      End If
   Next
   Dirty = True
End Sub

Public Sub AddBitmap(ByVal bm As CBitmapFile, Optional nID As Integer = 0)
   BitmapCollection.Add bm
   If nID = 0 Then bm.IdNo = GetNextSeqNo
   Dirty = True
End Sub
Public Sub AddResource(ByVal resource As CResourceFile, Optional nID As Integer = 0)
   ResourceCollection.Add resource
   If nID = 0 Then resource.IdNo = GetNextSeqNo
   Dirty = True
End Sub

Public Sub AddDataElement(ByVal de As CDataElement)
   DataCollection.Add de
   de.tbl_no = DataCollection.count
End Sub

Public Function AddMenu(Optional ByVal mnu As CMenu = Nothing) As Boolean
   If mnu Is Nothing Then
      Set mnu = New CMenu
      If gLanguage <> "Nippon" Then
         mnu.Name = InputBox(gStringTable(1623), gStringTable(1624))
      Else
         mnu.Name = InputBox(gStringTable(1623) + " " + gStringTable(1624))
      End If
      If mnu.Name = "" Then Exit Function
   End If
   If mnu.IdNo = 0 Then
      mnu.IdNo = GetNextSeqNo
      If GlobalID <> "" Then mnu.SetGlobalID GlobalID
   End If
   MenuCollection.Add mnu, str(mnu.IdNo)
   AddMenu = True
   Dirty = True
End Function

Private Sub GenMenuTBAR(mn As CMenu, eno As Integer)
Dim mBar As PPmenuBar
Dim pull As menuPulldown
Dim itm As menuItem
Dim mnu As CMenuElem
Dim mnu2 As CMenuElem
Dim temp As Long
Dim p As Long
Dim i As Long
Dim startPull As Long
Dim startItem As Long
Dim startStrings As Long
Dim startMBAR As Long
Dim icnt As Integer
Dim pcnt As Integer
Dim n As Integer
Dim knt As Integer
Dim m As Integer
Dim titleOffset As Integer
Dim maxlen As Integer
Dim drop As Integer
Dim byte00 As Byte

   byte00 = &H0
   wordBound 3
   temp = Loc(3) + 1
   Seek #3, TOCLoc3
   TOCLoc3 = TOCLoc3 + 10
   'write TOC rec with offset
   writeTOCRecord3 3, "MBAR", mn.IdNo, temp - 1
   Seek #3, temp
   startMBAR = temp
   mBar.barWin.h = 0
   mBar.bitsBehind.h = 0
   mBar.savedActiveWin.h = 0
   mBar.bitsBehindStatus.h = 0
   mBar.attr.w = &H0
   mBar.curMenu.w = 0
   mBar.curItem.w = -1
   mBar.cmdTick = 0
   mBar.numMenus.w = cvtWord(0)  'til later
   mBar.menuPulldownPtr = 0
   Put #3, , mBar

   startPull = Loc(3) + 1
   titleOffset = 4
   For Each mnuBar In mn.MenuBars
'sgBox "generating pulldown for item=" + mnu.caption + " item#=" + str(n)
      pull.menuWin.h = 0
      pull.bounds.topleft.x = 0
      pull.bounds.topleft.y = 0
      pull.bounds.extent.x = 0
      pull.bounds.extent.y = 0
      pull.bitsBehind.h = 0
      pull.titleBounds.topleft.x = cvtWord(titleOffset)
      mnuBar.workXoffset = titleOffset
      pull.titleBounds.topleft.y = cvtWord(0)
'      pull.titleBounds.extent.x = cvtWord(0.8 * frmPalmScreen.TextWidth(mnuBar.caption))
      pull.titleBounds.extent.x = cvtWord(GetTextWidth(mnuBar.caption, 1) + 8)
      pull.titleBounds.extent.y = cvtWord(12)
      pull.Title = 0
      pull.numItems.w = 0
      pull.menuItemTypeOffset = 0
      Put #3, , pull
'      titleOffset = titleOffset + 0.8 * frmMain.picBox.TextWidth(mnuBar.caption)
      titleOffset = titleOffset + GetTextWidth(mnuBar.caption, 1) + 8
   Next
   startItem = Loc(3) + 1
   p = startPull

   For Each mnuBar In mn.MenuBars
      temp = Loc(3) + 1
      Seek #3, p + 32
      Put #3, , cvtWord(temp - startMBAR)
      Seek #3, temp
      p = p + 34
      For Each mnu In mnuBar.MenuElems
'sgBox "putting out item id=" + str(mnu.idno)
         itm.id.w = cvtWord(mnu.IdNo)
         If Len(mnu.command) > 0 And mnu.caption <> "-" Then
            itm.command = Asc(mnu.command)
         Else
            itm.command = 0
         End If
         itm.unused = &H0
         itm.itemStr = 0
         Put #3, , itm
      Next
   Next
   startStrings = Loc(3) + 1
   p = startPull
   i = startItem
   pcnt = 0
   icnt = 0

   For Each mnuBar In mn.MenuBars
      'its a pulldown
      'first --look ahead and count items
      temp = Loc(3) + 1
      maxlen = 0
'      knt = 0
      Dim cntSeparators As Integer                      '2012001 added *********
      cntSeparators = 0                                 '2012001 added *********
      For Each mnu2 In mnuBar.MenuElems
'sgBox "subtitle=" + mnu2.caption + "   txtlen=" + str(frmPalmScreen.textwidth(mnu2.caption)) / Mag nific)
'         knt = knt + 1
         'Not sure how well this works, but errors are gone
'         If mnu2.MenuWidth > maxlen Then
'            maxlen = mnu2.MenuWidth
'            If maxlen > 159 Then maxlen = 159
'         End If
'         MsgBox "Commented these 4 lines out because magnific was removed", vbOKOnly, "MMD"
'         If (1.4 * frmPalmScreen.TextWidth(mnu2.caption) / magnific) > maxlen Then '2012001  modified******
'            maxlen = 1.4 * frmPalmScreen.TextWidth(mnu2.caption) / magnific        '2012001  modified******
'            If maxlen > 159 Then maxlen = 159                               '2012001   added********
'         End If
         If mnu2.command <> "" Then
            If GetTextWidth(mnu2.caption & vbTab & Chr(&H9D) & Left(mnu2.command, 1), 1) + 8 > maxlen Then
               maxlen = GetTextWidth(mnu2.caption & vbTab & Chr(&H9D) & Left(mnu2.command, 1), 1) + 8
               If maxlen > 159 Then maxlen = 159
            End If
         Else
            If GetTextWidth(mnu2.caption, 1) + 8 > maxlen Then    '05282001  modified******
               maxlen = GetTextWidth(mnu2.caption, 1) + 8         '05282001  modified******
               If maxlen > 159 Then maxlen = 159                               '2012001   added********
            End If
         End If
         If mnu2.caption = "-" Then                                         '2012001 added ********* is it a separator
            cntSeparators = cntSeparators + 1                               '2012001 added *********
         End If                                                             '2012001 added *********
      Next
'      If knt <> mnuBar.MenuElems.count Then MsgBox "Not equal"
      Seek #3, p + 4 'topleft-x
      If mnuBar.workXoffset + maxlen > 160 Then
         Put #3, , cvtWord(160 - maxlen)
      Else
         Put #3, , cvtWord(mnuBar.workXoffset)
      End If
      Seek #3, p + 6 'topleft y
      Put #3, , cvtWord(14)
      Seek #3, p + 8 'x-extent
      Put #3, , cvtWord(maxlen)
      Seek #3, p + 10 'y-extent

'      Put #3, , cvtWord(11 * knt - 6 * cntSeparators)   '2001-07-27 MMD
      Put #3, , cvtWord(11 * mnuBar.MenuElems.count - 6 * cntSeparators)   '2001-07-27 MMD
      Seek #3, p + 28
'      Put #3, , cvtWord(knt) 'cnt of items in pulldown
      Put #3, , cvtWord(mnuBar.MenuElems.count)  'cnt of items in pulldown
      Seek #3, temp
      temp = Loc(3) + 1
      Seek #3, p + 26  'title offset
      Put #3, , cvtWord(temp - startMBAR)
      Seek #3, temp
      pcnt = pcnt + 1
      p = p + 34
      Put #3, , mnuBar.caption
      Put #3, , byte00
      For Each mnu In mnuBar.MenuElems
         'its a lower lvl item
         temp = Loc(3) + 1
         Seek #3, i + 6
         Put #3, , cvtWord(temp - startMBAR)
         Seek #3, temp
         icnt = icnt + 1
         i = i + 8
         Put #3, , mnu.caption
         Put #3, , byte00
      Next

nextMenu:
   Next
   temp = Loc(3) + 1

   Seek #3, startMBAR + 26
   Put #3, , cvtWord(pcnt)
   Seek #3, temp
End Sub

Public Function GetNextSeqNo() As Integer
   If HighestSeqNo > 9990 Then MsgBox gStringTable(3443) 'Maximum number of resources in a project is 9999
   HighestSeqNo = HighestSeqNo + 1
   GetNextSeqNo = HighestSeqNo
End Function

Public Function OpenProject(ByVal strPath As String) As Boolean
Dim o As Object
Dim bmp As CBitmapFile
Dim Kind As String
Dim saveHighSeqNo As Integer
Dim frm As CForm
Dim projectDir As String

'MMD   stage = "l"
   OpenProject = False
   On Error GoTo gotCancel
   Open strPath For Input As #1
   
   'Change the current directory to the project file directory
   projectDir = Left(strPath, InStrRev(strPath, "\"))
   If Mid(projectDir, 2, 1) = ":" Then ChDrive Left(projectDir, 2) 'ignore network drives
   ChDir projectDir
   
   Do
      Input #1, Kind
      Select Case Kind
      Case "mdl", "proj"
         Restore
'         saveHighSeqNo = o.HighestSeqNo
'         o.HighestSeqNo = 0
      Case "bmpfile"
         Set o = New CBitmapFile
         o.Restore
         o.Project = Me
         AddBitmap o, o.IdNo
      Case "resfile"
         Set o = New CResourceFile
         o.Restore
         o.Project = Me
         AddResource o, o.IdNo
      Case "mnu"
         Set o = New CMenu
'         Set menu = o
         o.SetGlobalID GlobalID
         o.Restore
'         MenuCollection.Add o
         AddMenu o
      Case "mod"
         Set o = New CCodeModule
'         Set cod = o
         'o.IdNo = GetNextSeqNo     '12.04.06 GH
         o.Restore
         If Len(o.path) = 0 Then
'            Set cod = Nothing
            Set o = Nothing
         Else
            CodeCollection.Add o
         End If
      Case "vew", "form"
         Set frm = New CForm
         frm.Restore
         frm.Project = Me
         FormCollection.Add frm
      Case "bmp", "bitmap"
         Set o = New CUIBitmap
         RestoreUIObject frm, o
      Case "but", "button"
         Set o = New CUIButton
         RestoreUIObject frm, o
      Case "chk", "checkbox"
         Set o = New CUICheckbox
         RestoreUIObject frm, o
      Case "cho", "choicebox", "pus", "pushbutton"
         Set o = New CUIPushbutton
         RestoreUIObject frm, o
      Case "fld", "field"
         Set o = New CUIField
         RestoreUIObject frm, o
      Case "gad", "gadget"
         Set o = New CUIGadget
         RestoreUIObject frm, o
      Case "lbl", "label"
         Set o = New CUILabel
         RestoreUIObject frm, o
      Case "lst", "list"
         Set o = New CUIList
         RestoreUIObject frm, o
      Case "pop", "popup"
         Set o = New CUIPopup
         RestoreUIObject frm, o
      Case "rpt", "repeater"
         Set o = New CUIRepeater
         RestoreUIObject frm, o
      Case "scr", "scrollbar"
         Set o = New CUIScrollbar
         RestoreUIObject frm, o
      Case "sel", "selector"
         Set o = New CUISelector
         RestoreUIObject frm, o
      Case "shf", "gsi"
         Set o = New CUIGraffitiShiftIndicator
         RestoreUIObject frm, o
      Case "sli", "slider"
         Set o = New CUISlider
         RestoreUIObject frm, o
      Case "grd", "grid"
         Set o = New CUIGrid
         RestoreUIObject frm, o
      Case "end"
         Exit Do
      Case "data"
         Set o = New CDataElement
         o.Restore
         AddDataElement o
      Case Else
         MsgBox gStringTable(3258) + Kind '"Error: Illegal Object Type (" + Kind + ")"
         End
      End Select
   Loop
   
   Close #1
   On Error GoTo 0
   pathname = strPath
   OpenProject = True
   Saved = True
   Dirty = False
   Exit Function
gotCancel:
   MsgBox gStringTable(3259) + strPath '"Error Loading Project '" + strPath + "'"
   End
End Function

Private Sub RestoreUIObject(ByVal frm As CForm, ByVal obj As Object)
   obj.Restore
   frm.ObjectCollection.Add obj
   obj.obj.Form = frm
End Sub

Public Property Let ApplType(ByVal strname As String)
   m_strApplType = Left(strname, 4)
End Property

Public Property Get ApplType() As String
   ApplType = m_strApplType
End Property

Public Property Let CreatorID(ByVal strCode As String)
   m_strCreatorID = Left(strCode, 4)
End Property

Public Property Get CreatorID() As String
   CreatorID = m_strCreatorID
End Property

Public Sub GetProperty()
Static nProp As Integer

   If nProp = kTotalProps Then
      gPropInfo.Name = ""
      nProp = 0
      Exit Sub
   End If

   gPropInfo.Val = ""
   'Use pgString as default, it is most common
   gPropInfo.Type = pgString

   Select Case nProp
   Case 0 'Name
      gPropInfo.Name = "(Name)"
   Case 1 'Type
      gPropInfo.Name = "Type"
      'gPropInfo.Type = pgReadOnly
   Case 2 'Path
      gPropInfo.Name = "Project Path"
      gPropInfo.Type = pgReadOnly
   Case 3 'Launcher Name
      gPropInfo.Name = "Launcher Name"
   Case 4 'Version
      gPropInfo.Name = "Version"
   Case 5 'Theme
      gPropInfo.Name = "Theme"
      gPropInfo.Type = pgOther
      gPropInfo.data = gStringTable(2206) + ">"
#If NSBSymbian Then
   Case 6 'Company Name
      gPropInfo.Name = "Company"
      gPropInfo.Type = pgString
   Case 7 'Install Folder
      gPropInfo.Name = "Install Folder"
      gPropInfo.Type = pgString
   Case 8 'Symbian Launcher Icon
      gPropInfo.Name = "Launcher Icon UIQ"
      gPropInfo.Type = pgOther
      gPropInfo.data = gStringTable(kResStrings2200 + 4) + ">"
   Case 9 'Symbian Launcher Icon
      gPropInfo.Name = "Launcher Icon S60"
      gPropInfo.Type = pgOther
      gPropInfo.data = gStringTable(kResStrings2200 + 3) + ">"
   Case 10 'License
      gPropInfo.Name = "License"
      gPropInfo.Type = pgOther
      gPropInfo.data = gStringTable(kResStrings2200 + 5) + ">"
   Case 11 'Symbian UID3
      gPropInfo.Name = "UID3"
      gPropInfo.Type = pgString
#Else
   Case 6 'Large Icon
      gPropInfo.Name = "ID, Large Icon"
      If m_nLargeIconID = 0 Then
         gPropInfo.Val = gStringTable(kResStrings + 0) '(None)
      Else
         gPropInfo.Val = m_nLargeIconID
      End If
      gPropInfo.Type = pgString
   Case 7 'Small Icon
      gPropInfo.Name = "ID, Small Icon"
      If m_nSmallIconID = 0 Then
         gPropInfo.Val = gStringTable(kResStrings + 0) '(None)
      Else
         gPropInfo.Val = m_nSmallIconID
      End If
      gPropInfo.Type = pgString
   Case 8 'Creator ID
      gPropInfo.Name = "Creator ID"
      gPropInfo.Type = pgString
#End If
   End Select
   If gPropInfo.Val = "" Then gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "(Name)": GetPropertyVal = Name
   Case "Type": GetPropertyVal = ApplType
   Case "Creator ID": GetPropertyVal = CreatorID
   Case "Project Path": GetPropertyVal = pathname
   Case "ID, Large Icon": GetPropertyVal = m_nLargeIconID
   Case "ID, Small Icon": GetPropertyVal = m_nSmallIconID
   Case "Launcher Name": GetPropertyVal = launcherName
   Case "Version": GetPropertyVal = LaunchVersion
   Case "Theme": GetPropertyVal = theme
#If NSBSymbian Then
   Case "Company": GetPropertyVal = Company
   Case "Install Folder": GetPropertyVal = installFolder
   Case "Launcher Icon S60": GetPropertyVal = LauncherIconS60
   Case "Launcher Icon UIQ": GetPropertyVal = LauncherIconUIQ
   Case "License": GetPropertyVal = License
   Case "UID3": GetPropertyVal = UID3
#End If
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim strWork As String
Dim proj As CProject
Dim n As Integer
Dim frm As Form

   ValidateProperty = True
   Select Case strProp
   Case "(Name)"
      For Each proj In gProjects
         If StrComp(proj.Name, strVal, vbTextCompare) = 0 Then
            'Project named X already open
            MsgBox gStringTable(kErrStrings), vbOKOnly
            ValidateProperty = False
            Exit Function
         End If
      Next

      If Not Saved Then
         If ValidFileName(strVal) Then
'            strWork = filedirectory + "\Projects\" + strVal + ".prj"
'            If Dir(strWork, vbNormal) <> "" Then
'               'Overwrite existing file?
'               If MsgBox(gStringTable(kErrStrings + 1), vbYesNo) = vbNo Then
'                  ValidateProperty = False
'                  Exit Function
'               End If
'            End If
            Name = strVal
         Else
            ValidateProperty = False
            Exit Function
         End If
      Else
         Name = strVal
      End If
      frmMain.SetCaptions
   Case "Type"
      If Len(strVal) <> 4 Then
         ValidateProperty = False
      Else
         ApplType = strVal
      End If
   Case "Creator ID"
      strVal = Left(strVal & "....", 4)
      If LCase(strVal) = strVal Then
         For n = 1 To 4
            'Allow Creator ID w/ any non-alpha chars
            If InStr(1, "abcdefghijklmnopqrstuvwxyz", Mid(strVal, n, 1), vbBinaryCompare) = 0 Then
               CreatorID = strVal
               Exit Function
            End If
         Next
         MsgBox gStringTable(kErrStrings + 2), vbCritical + vbOKOnly
         ValidateProperty = False
         Exit Function
      Else
         CreatorID = strVal
      End If
   Case "ID, Large Icon"
      n = 0
      If Val(strVal) <> 0 Then
         For Each bmp In BitmapCollection
            If bmp.IdNo = Val(strVal) Then
               n = bmp.IdNo
               Exit For
            End If
         Next
         If n = 0 Then
            MsgBox gStringTable(kResStrings + 2), vbCritical + vbOKOnly
            DoEvents
            gfProjectExplorer.ShowActive Me
            ValidateProperty = False
            Exit Function
         End If
      End If
      m_nLargeIconID = n
   Case "ID, Small Icon"
      n = 0
      If Val(strVal) <> 0 Then
         For Each bmp In BitmapCollection
            If bmp.IdNo = Val(strVal) Then
               n = bmp.IdNo
               Exit For
            End If
         Next
         If n = 0 Then
            MsgBox gStringTable(kResStrings + 2), vbCritical + vbOKOnly
            DoEvents
            gfProjectExplorer.ShowActive Me
            ValidateProperty = False
            Exit Function
         End If
      End If
      m_nSmallIconID = n
#If NSBSymbian = 1 Then
   Case "Company"
      strVal = Replace(strVal, """", "*")
      Company = strVal
   Case "Install Folder"
      strVal = Replace(strVal, """", "*")
      installFolder = strVal
   Case "Launcher Icon S60"
      strVal = Replace(strVal, """", "*")
      LauncherIconS60 = strVal
   Case "Launcher Icon UIQ"
      strVal = Replace(strVal, """", "*")
      LauncherIconUIQ = strVal
   Case "License"
      strVal = Replace(strVal, """", "*")
      License = strVal
   Case "UID3"
      strVal = Replace(strVal, """", "*")
      UID3 = strVal
      If UID3 = "" Then 'if UID3 is blank, then give it the next number.
         UID3 = gstrNextUID3
         gstrNextUID3 = Hex(CLng("&h" & gstrNextUID3) + 3)
         MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "NextUID3", gstrNextUID3
      End If
 #End If
   Case "Launcher Name"
      strVal = Replace(strVal, """", "*")
      launcherName = strVal
   Case "Version"
      #If NSBSymbian Then
         'format must be #,#,#,#
         Dim v() As String
         Dim i As Integer
         v = Split(strVal, ",")
         If UBound(v) <> 2 Then
            MsgBox gStringTable(3449) 'Version must be in format #,#,#
            ValidateProperty = False
            Exit Function
         End If
         For i = 0 To 2
            If Not IsNumeric(v(i)) Then
               MsgBox gStringTable(3449) 'Version must be in format #,#,#
               ValidateProperty = False
               Exit Function
            End If
         Next
      #End If
      LaunchVersion = strVal
   Case "Theme"
      strVal = Replace(strVal, """", "*")
      theme = strVal
      addThemeToResources
      gsTheme = theme
      Set frm = frmMain.GetMDIChild(gsCurrentFormGlobalID)
      If frm Is Nothing Then
         'frmMain.ViewObject gsCurrentFormGlobalID
      Else
         frm.UpdateScreen
      End If
   End Select
   Dirty = True
End Function

Public Property Get Form(nID As Integer) As CForm
Dim frm As CForm

   For Each frm In FormCollection
      If frm.IdNo = nID Then
         Set Form = frm
         Exit Property
      End If
   Next
End Property

Public Property Get Bitmap(nID As Integer) As CBitmapFile
Dim bmp As CBitmapFile

   For Each bmp In BitmapCollection
      If bmp.IdNo = nID Then
         Set Bitmap = bmp
         Exit Property
      End If
   Next
End Property
Public Property Get resource(nID As Integer) As CResourceFile
Dim bmp As CResourceFile

   For Each bmp In ResourceCollection
      If bmp.IdNo = nID Then
         Set resource = bmp
         Exit Property
      End If
   Next
End Property

Public Property Get Module(nID As Integer) As CCodeModule
Dim cm As CCodeModule

   For Each cm In CodeCollection
      If cm.IdNo = nID Then
         Set Module = cm
         Exit Property
      End If
   Next
End Property

Public Property Get GlobalID() As String
Attribute GlobalID.VB_UserMemId = 0
   GlobalID = m_strGlobalID
End Property

Public Property Let GlobalID(strID As String)
   m_strGlobalID = "project|" & strID
End Property

Public Function GetScript(strScript As String, Optional bForceCreate As Boolean = True) As String
   Select Case strScript
   Case "startup"
      If pgm_script <> "" Or Not bForceCreate Then
         GetScript = pgm_script
      Else
         GetScript = "Sub Project_Startup()" & vbCrLf & vbCrLf & "End Sub"
      End If
   Case "termination"
      If termination_script <> "" Or Not bForceCreate Then
         GetScript = termination_script
      Else
         GetScript = "Sub Project_Termination()" & vbCrLf & vbCrLf & "End Sub"
      End If
   End Select
End Function

Public Sub PutScript(ByVal strText As String, ByVal strScript As String)
   Select Case strScript
   Case "startup": pgm_script = strText
   Case "termination": termination_script = strText
   End Select
   Dirty = True
End Sub

Public Sub WriteOutBitmaps()
Dim bmp As CBitmapFile
Dim frm As Object
Dim obj As Object
Dim filename As String
Dim res As Double

   For Each bmp In BitmapCollection
      If CheckBitmap(bmp.PathName1) And CheckBitmap(bmp.PathName2) And CheckBitmap(bmp.PathName4) And CheckBitmap(bmp.PathName8) And CheckBitmap(bmp.PathName16) And _
         CheckBitmap(bmp.PathName1h) And CheckBitmap(bmp.PathName2h) And CheckBitmap(bmp.PathName4h) And CheckBitmap(bmp.PathName8h) And CheckBitmap(bmp.PathName16h) Then '07/18/01 GH
         ResIn bmp.IdNo, bmp.PathName1, bmp.PathName2, bmp.PathName4, bmp.PathName8, bmp.PathName16, bmp.PathName1h, bmp.PathName2h, bmp.PathName4h, bmp.PathName8h, bmp.PathName16h
         If bmp.IdNo = m_nLargeIconID Then _
            ResIn 1000, bmp.PathName1, bmp.PathName2, bmp.PathName4, bmp.PathName8, bmp.PathName16, bmp.PathName1h, bmp.PathName2h, bmp.PathName4h, bmp.PathName8h, bmp.PathName16h
         If bmp.IdNo = m_nSmallIconID Then _
            ResIn 1001, bmp.PathName1, bmp.PathName2, bmp.PathName4, bmp.PathName8, bmp.PathName16, bmp.PathName1h, bmp.PathName2h, bmp.PathName4h, bmp.PathName8h, bmp.PathName16h
      End If
   Next
   
   For Each frm In gTarget.FormCollection
      For Each obj In frm.ObjectCollection
         If obj.obj.Kind = "bmp" Then
            If obj.ResourceId = obj.obj.IdNo Then
              filename = fileDirectory & "\bitmaps\" & gTarget.Name & "\" & obj.obj.IdNo & ".bmp"
              If Dir(filename) = "" Then
                 frmMain.ViewObject obj.obj.GlobalID
                 obj.obj.Control.Parent.ClearSelection 'this creates the file for that object
              End If
              res = ResIn(obj.obj.IdNo, "", "", "", filename, "", "", "", "", "", filename)
              If res > 0 Then
                 MsgBox gStringTable(3534) & res & " " & filename 'Image must be less than 64K
              End If
            End If
         End If
      Next
   Next

End Sub
Public Sub WriteOutResources()
Dim resource As CResourceFile
   For Each resource In ResourceCollection
         'ResIn resource.IdNo
   Next
End Sub
Public Function CheckBitmap(pathname As String) '07/18/01 GH
'see if bitmap exists
   CheckBitmap = True
   If pathname = "" Then Exit Function
   
   On Error GoTo notFound
   Open pathname For Input As #3
   Close #3
   Exit Function
   
notFound:
   MsgBox gStringTable(3260) + pathname '"Bitmap not found: " & pathname
   CheckBitmap = False
   compileOkSw = False
End Function

Public Function BuildMap() As String()
Dim strMap As String
Dim frm As CForm
Dim mnu As CMenu
Dim mBar As CMenuBar
Dim mElem As CMenuElem
Dim cMod As CCodeModule
Const kSep As String = ">"

   strMap = Join(Array(GlobalID & "|startup", GlobalID & "|termination"), kSep)
   For Each frm In FormCollection
      strMap = strMap & kSep & Join(frm.BuildMap, kSep)
   Next
   For Each mnu In MenuCollection
      For Each mBar In mnu.MenuBars
         For Each mElem In mBar.MenuElems
            strMap = strMap & kSep & mElem.GlobalID & "|click"
         Next
      Next
   Next
   For Each cMod In CodeCollection
      strMap = strMap & kSep & cMod.GlobalID & "|code"
   Next
   BuildMap = Split(strMap, kSep)
'   MsgBox Join(BuildMap, vbCrLf)
'   Clipboard.SetText Join(BuildMap, vbCrLf)
End Function

Public Function GetObjectType(astrName As String) As String
Dim frm As CForm

   For Each frm In FormCollection
      GetObjectType = frm.GetObjectType(astrName)
      If GetObjectType <> "" Then Exit Function
   Next
End Function
Public Function BuildNavArray(view As CForm) As Integer() 'added 10.13.06 GH
    Dim navArray() As Integer
    ReDim navArray(10 + view.ObjectCollection.count * 4)
    Dim count As Integer
    Dim o As Object
    Dim i As Integer
    Dim flags As Long
    count = 0
    
    navArray(0) = 1                              'Version
    navArray(1) = view.ObjectCollection.count    'number of objects on the form
    navArray(2) = 20                             'header size in bytes - always 20
    navArray(3) = 8                              'element size in bytes - always 8
    navArray(4) = 0                              'navFlags part 1 - does not seem to be used
    flags = view.NavFlags                        'need to do some magic if value 8000 hex.
    
    'Avoid a crash if there are more than 18 forms.
    If flags <> 2 Then formCount = formCount + 1 'only count forms that have nav on them
    If formCount > 18 Then flags = 2             'turn off nav on forms after 18
    
    If flags > 32768 Then
      i = flags \ 32768
      If i > 1 Then flags = 0
      flags = flags Mod 32768
      flags = -32767 + flags
    End If
    navArray(5) = flags                          'navFlags part 2

    navArray(6) = view.NavFirstID                'initialObjectIDHint
    navArray(7) = view.NavJumpToID               'JumpObjectID
    navArray(8) = view.NavBottomLeftID           'BottomLeftObjectID
    navArray(9) = 0                              'filler
    
    'now, do the elements
    i = 10
    For Each o In view.ObjectCollection
      If o.obj.Kind <> "shf" And o.obj.Kind <> "bmp" Then
      'If o.obj.ScriptLen > 0 Then                'collect all objects that have a script
        navArray(i + 0) = o.obj.IdNo
        flags = o.obj.NavFlags                   'need to do some magic if value 8000 hex.
        If flags > 32768 Then
           i = flags \ 32768
           If i > 1 Then flags = 0
           flags = flags Mod 32768
           flags = -32767 + flags
        End If

        navArray(i + 1) = flags                    'object flags
        If o.obj.Kind = "lbl" Or o.obj.Kind = "scr" Then navArray(i + 1) = 1 'force skip
        navArray(i + 2) = o.obj.NavAboveID         'aboveObjectID
        navArray(i + 3) = o.obj.NavBelowID         'belowObjectID
        If navArray(6) = 0 Then navArray(6) = o.obj.IdNo 'set initialObjectIDHint to first object
        If navArray(7) = 0 Then navArray(7) = o.obj.IdNo
        If navArray(8) = 0 Then navArray(8) = o.obj.IdNo 'set bottomLeftObjectID to last object
        i = i + 4
        count = count + 1
      End If
    Next
    navArray(1) = count                           'number of objects on the form
    ReDim Preserve navArray(10 + count * 4 - 1)
    BuildNavArray = navArray
End Function
