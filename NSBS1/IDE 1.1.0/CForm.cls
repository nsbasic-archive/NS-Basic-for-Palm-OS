VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

Public ObjectCollection As Collection
Public obj_code As String
Public obj_code_after As String
Public pgm_script As String
Public pgm_script_after As String

Public obj_code_len As Long
Public obj_code_len_after As Long
Public obj_code_id As Integer
Public Title As String
Private m_strName As String
Private m_nIdNo As Integer
Private m_bIsDefaultForm As Boolean
Private m_bModal As Boolean
Private m_bFrame As Boolean
Private m_bSaveBehind As Boolean
Private m_nTipsIdNo As Integer
Private m_sTips As String
Private m_nDefaultButtonId As Integer
Private m_nOriginLeft As Integer
Private m_nOriginTop As Integer
Private m_nWidth As Integer
Private m_nHeight As Integer
Private m_bOptTitle As Boolean
Private m_nNavFlags As Long             '10.16.06 GH
Private m_nNavFirstID As Integer        '10.16.06 GH
Private m_nNavJumpToID As Integer       '10.16.06 GH
Private m_nNavBottomLeftID As Integer   '10.16.06 GH
Public event_script As String
Public event_obj_code As String
Public event_obj_code_len As Long
Private m_Project As CProject

Private Const kVersion As Integer = 4 '10.16.06 GH
'2100 marks beginning of CForm string table entries
Private Const kResStrings As Integer = 2100
Private Const kErrStrings As Integer = 2150
Private Const kProperties As String = ""
Private Const kMethods As String = ""

Private Sub class_initialize()
Dim i As Integer
Dim temp As String

   obj_code = ""
   Set ObjectCollection = New Collection
   
   obj_code = 0
   obj_code_len = 0
'   gtarget.HighestSeqNo = gtarget.HighestSeqNo + 1
'   obj_code_id = gtarget.HighestSeqNo
   obj_code_id = 0
'   gtarget.HighestSeqNo = gtarget.HighestSeqNo + 1
'   IdNo = gtarget.HighestSeqNo
   IdNo = 0
   Title = "Form"
   pgm_script = ""
   pgm_script_after = ""
   event_script = ""
   Name = Title
   IsDefaultForm = False
 
   m_bModal = False
   m_bFrame = True
   m_bSaveBehind = True
   m_nTipsIdNo = 0
   m_sTips = ""
   m_nOriginLeft = 0
   m_nOriginTop = 0
   m_nWidth = 160 'kScreenWidth
   If gbDana Then m_nWidth = 560
   m_nHeight = 160 'kScreenHeight
   m_nNavFlags = 0
   m_nNavFirstID = 0
   m_nNavJumpToID = 0
   m_nNavBottomLeftID = 0
   #If NSBSymbian Then
      OptTitle = False
   #Else
      OptTitle = True 'def is yes
   #End If
End Sub

Public Sub PrcOut()
Dim titl As titleOut
Dim frm As formOut
Dim wkstr As String
Dim c As Byte
Dim templen As Integer
Dim obj As Object, o2 As Object

   On Error GoTo 0
   wkstr = Dir(DownloadPath + "__temp*.*")
   'sgBox "wkstr=" + wkstr
   Do While Not wkstr = ""
      Kill DownloadPath & wkstr
      wkstr = Dir
   Loop
   Open DownloadPath + "__temp6.__6" For Binary As #6
   Open DownloadPath + "__temp7.__7" For Binary As #7
   Open DownloadPath + "__temp8.__8" For Binary As #8
   Open DownloadPath + "__temp9.__9" For Binary As #9

   If OptTitle Then
      c = &H9
      Put #8, , c
      c = &H0
      Put #8, , c
      wordBound (9)
      outLong 8, Loc(9)

      Put #9, , titl
      templen = Len(Title)
      Put #6, , templen
      Put #9, , Title
      c = &H0
      Put #9, , c
   End If

   'FIX: Eventually I want this moved to properties window so the error
   'condition can never exist without instant notification to user
   '03/07/2001 MMD
   For Each obj In ObjectCollection
      If obj.obj.Kind = "cho" Or obj.obj.Kind = "pus" Then
         If Not obj.GroupId = 0 And obj.Selected = True Then
            For Each o2 In ObjectCollection
               If Not o2 Is obj Then
                  If o2.obj.Kind = obj.obj.Kind Then
                     If o2.GroupId = obj.GroupId And o2.Selected = True Then
                        MsgBox gStringTable(3236) + Name '"Form has more than one PushButton assigned the same Group ID and also in 'Selected' status. Only one member of a common Group ID can be in 'selected' status."
                        compileOkSw = False
                     End If
                  End If
               End If
            Next
         End If
      End If
   Next

   For Each obj In ObjectCollection
'dbug "going to an obj.prcout"
      wordBound 9
      obj.PrcOut
'dbug "back from obj.prcout"
   Next
   Close 6
   Close 9
   Close 8

   frm.dispWidth.w = 0
   frm.dispHeight.w = 0
   frm.displayAddr.c = 0
   frm.flags.w = cvtWord(&H1200)
   If Modal Then
      frm.flags.w = frm.flags.w Or cvtWord(&H2200)
   End If
   frm.bounds.topleft.x = cvtWord(OriginLeft)
   frm.bounds.topleft.y = cvtWord(OriginTop)
   frm.bounds.extent.x = cvtWord(Width)
   frm.bounds.extent.y = cvtWord(Height)
   frm.clipBounds.Left = 0
   frm.clipBounds.Top = 0
   frm.clipBounds.Right = 0
   frm.clipBounds.Bottom = 0
   frm.origin.x = 0
   frm.origin.y = 0
   If Modal Then
      frm.cornerDiam = &H3
      frm.frameBits = &H2
   Else
      frm.cornerDiam = 0
      frm.frameBits = 1
   End If

   frm.statePtr.c = 0
   frm.nextWindow.c = 0
   frm.id.w = cvtWord(IdNo)
   frm.attr = &HC0
   If SaveBehind Then
      frm.attr = frm.attr Or &H8
   End If

   frm.unused = 0
   frm.unused2 = 0
   frm.unused3 = 0
   frm.bitsBehindForm.h = 0
   frm.handler.c = 0
   frm.focus.w = 0
   frm.defButton.w = 0
   If Tips <> "" Then
      frm.helpRscId.w = cvtWord(TipsIdNo)
   Else
      frm.helpRscId.w = cvtWord(0)
   End If
'   rscId = 0

   frm.menuRscId.w = cvtWord(0)
   frm.numObjects.w = cvtWord(fileLen(DownloadPath + "__temp8.__8") / 6)
   frm.objPtr.c = 0
'dbug "writing frm to #7"
   Put #7, , frm
   Close 7
End Sub

Public Sub Restore()
Dim theNoItems As Integer
Dim i As Integer
Dim version As Integer
Dim strname As String

   Input #1, version
   If version > kVersion Then
      MsgBox gStringTable(3237) & version '"Error: Invalid Form Version
      End
   End If

   Input #1, m_nIdNo, m_bModal, m_bFrame, m_bSaveBehind, m_nDefaultButtonId, _
         m_nOriginLeft, m_nOriginTop, m_nWidth, m_nHeight, m_nTipsIdNo, _
         m_bIsDefaultForm, m_bOptTitle
   Input #1, Title
   If version > 1 Then
      'To allow property validation
      Input #1, strname
   End If
   
   Input #1, pgm_script
   ProcessScript pgm_script, FromDisk
   Input #1, m_nTipsIdNo 'yes, it's read in twice no. No harm done...

   Input #1, pgm_script_after
   ProcessScript pgm_script_after, FromDisk

   If version > 2 Then
      Input #1, event_script
      ProcessScript event_script, FromDisk
   End If
   
   If Not TipsIdNo = 0 Then
      Input #1, m_sTips
   End If
   obj_code_id = IdNo - 1
   
   If version > 3 Then '10.16.06 GH Navigation info
      Input #1, m_nNavFlags, m_nNavFirstID, m_nNavJumpToID, m_nNavBottomLeftID
   End If
   
   'For property validation and script renaming
   If version > 1 Then
      Name = strname
   Else
      Name = Title
   End If
End Sub

Public Sub Save()
Dim strTemp As String
Dim obj As Object
Dim frm As frmCode

   If Tips <> "" And TipsIdNo = 0 Then
      TipsIdNo = Project.GetNextSeqNo
   End If

   Write #1, "vew"
   Write #1, kVersion, IdNo, Modal, Frame, SaveBehind, DefaultButtonID, _
         OriginLeft, OriginTop, Width, Height, TipsIdNo, _
         IsDefaultForm, OptTitle
   Write #1, Title
   Write #1, Name

   Set frm = frmMain.GetMDIChild(GlobalID & "|before")
   If Not frm Is Nothing Then frm.Save
   strTemp = pgm_script
   ProcessScript strTemp, ToDisk
   Write #1, strTemp
   Write #1, TipsIdNo 'yes, it's written out twice. No real harm...

   Set frm = frmMain.GetMDIChild(GlobalID & "|after")
   If Not frm Is Nothing Then frm.Save
   strTemp = pgm_script_after
   ProcessScript strTemp, ToDisk
   Write #1, strTemp

   Set frm = frmMain.GetMDIChild(GlobalID & "|event")
   If Not frm Is Nothing Then frm.Save
   strTemp = event_script
   ProcessScript strTemp, ToDisk
   Write #1, strTemp
   
   If TipsIdNo > 0 Then
      Write #1, Tips
   End If
   
   '10.16.06 GH Navigation fields
   Write #1, NavFlags, NavFirstID, NavJumpToID, NavBottomLeftID
   
   For Each obj In ObjectCollection
      Set frm = frmMain.GetMDIChild(obj.obj.GlobalID & "|code")
      If Not frm Is Nothing Then frm.Save
      obj.Save
   Next
End Sub

Public Function Copy() As String
Dim temp As String
Dim formObj As Object
Dim strTemp As String

   Copy = Quote("vew") + vbCrLf
   temp = Join(Array(kVersion, IdNo, BoolStr(Modal), BoolStr(Frame), _
      BoolStr(SaveBehind), DefaultButtonID, OriginLeft, OriginTop, Width, Height, _
      TipsIdNo, BoolStr(IsDefaultForm), BoolStr(OptTitle), _
      NavFlags, NavFirstID, NavJumpToID, NavBottomLeftID), ",")
   Copy = Copy + temp + vbCrLf
   Copy = Copy + Quote(Title) + vbCrLf
   Copy = Copy + Quote(Name) + vbCrLf
   strTemp = pgm_script
   ProcessScript strTemp, ToDisk
   Copy = Copy + Quote(strTemp) + vbCrLf
   Copy = Copy & TipsIdNo & vbCrLf
   strTemp = pgm_script_after
   ProcessScript strTemp, ToDisk
   Copy = Copy + Quote(strTemp) + vbCrLf
   strTemp = event_script
   ProcessScript strTemp, ToDisk
   Copy = Copy + Quote(strTemp) + vbCrLf
   If TipsIdNo <> 0 Then
      strTemp = Tips
      ProcessScript strTemp, ToDisk
      Copy = Copy + Quote(strTemp) + vbCrLf
   End If
   For Each formObj In ObjectCollection
      Copy = Copy + formObj.Copy
   Next
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer
Dim nScriptStart, nScriptEnd As Integer
Dim oldIdNo As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "vew" Then
      PasteObject strLines, False
      Exit Sub
   End If
   tokens = Split(strLines(2), ",")
   If tokens(0) <> kVersion Then
      MsgBox gStringTable(3238) '"Invalid paste: Form Version"
      End
   End If

   'Restore properties
   oldIdNo = tokens(1)
   Modal = UnBoolStr(tokens(2))
   Frame = UnBoolStr(tokens(3))
   SaveBehind = UnBoolStr(tokens(4))
   DefaultButtonID = tokens(5)
   OriginLeft = tokens(6)
   OriginTop = tokens(7)
   Width = tokens(8)
   Height = tokens(9)
   TipsIdNo = tokens(10)
   IsDefaultForm = UnBoolStr(tokens(11))
   OptTitle = UnBoolStr(tokens(12))
   NavFlags = tokens(13)
   NavFirstID = tokens(14)
   NavJumpToID = tokens(15)
   NavBottomLeftID = tokens(16)
   Title = UnQuote(strLines(3))
   'name = UnQuote(strLines(4))

   'Get Before Script
   pgm_script = RestoreScript(strLines, 5, nScriptEnd)
   pgm_script = Replace(pgm_script, "Screen" & oldIdNo & "_before", "Form" & IdNo & "_before", , , vbTextCompare)
   pgm_script = Replace(pgm_script, "Form" & oldIdNo & "_before", "Form" & IdNo & "_before", , , vbTextCompare)

   'Get TipsIdNo
   TipsIdNo = strLines(nScriptEnd + 1)
   nScriptEnd = nScriptEnd + 1

   'Get After Script
   pgm_script_after = RestoreScript(strLines, nScriptEnd + 1, nScriptEnd)
   pgm_script_after = Replace(pgm_script_after, "Screen" & oldIdNo & "_after", "Form" & IdNo & "_after", , , vbTextCompare)
   pgm_script_after = Replace(pgm_script_after, "Form" & oldIdNo & "_after", "Form" & IdNo & "_after", , , vbTextCompare)

   'Get Event Script
   event_script = RestoreScript(strLines, nScriptEnd + 1, nScriptEnd)
   event_script = Replace(event_script, "Screen" & oldIdNo & "_event", "Form" & IdNo & "_event", , , vbTextCompare)
   event_script = Replace(event_script, "Form" & oldIdNo & "_event", "Form" & IdNo & "_event", , , vbTextCompare)

   'Get Help Script if TipsIdNo <> 0
   If TipsIdNo <> 0 Then
      Tips = RestoreScript(strLines, nScriptEnd + 1, nScriptEnd)
'      Tips = Replace(Tips, "Form" & oldIdNo & "_event", "Form" & idno & "_event", , , vbTextCompare)
   End If

   'Remove used code then pass the rest on for pasting if anything remains
   For i = nScriptEnd + 1 To UBound(strLines)
      strLines(i - nScriptEnd) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - nScriptEnd)
   If UBound(strLines) > 1 Then PasteObject strLines, True
End Sub

Public Sub PasteObject(ByRef strLines() As String, bPasteForm As Boolean)
Dim obj As Object
Dim fPalmScreen As frmPalmScreen

   Select Case LCase(UnQuote(strLines(1)))
   Case "bmp": Set obj = New CUIBitmap
   Case "but": Set obj = New CUIButton
   Case "chk": Set obj = New CUICheckbox
   Case "cho", "pus": Set obj = New CUIPushbutton
   Case "fld": Set obj = New CUIField
   Case "gad": Set obj = New CUIGadget
   Case "lbl": Set obj = New CUILabel
   Case "lst": Set obj = New CUIList
   Case "pop": Set obj = New CUIPopup
   Case "rpt": Set obj = New CUIRepeater
   Case "scr": Set obj = New CUIScrollbar
   Case "sel": Set obj = New CUISelector
   Case "shf": Set obj = New CUIGraffitiShiftIndicator
   Case "grd": Set obj = New CUIGrid
   Case "sli": Set obj = New CUISlider
   End Select
   
   AddNewObject obj
   obj.Paste strLines
   If Not bPasteForm Then
      obj.obj.PasteShift
      gfProjectExplorer.AddNewControl obj, Me
   End If
   Set fPalmScreen = frmMain.GetMDIChild(GlobalID)
   If Not fPalmScreen Is Nothing Then fPalmScreen.AddUIObject obj
   If UBound(strLines) > 1 Then PasteObject strLines, bPasteForm
End Sub

Public Function RestoreScript(ByRef strLines() As String, ByVal nScriptStart As Integer, _
                              ByRef nScriptEnd As Integer) As String
Dim i As Integer
Dim tokens() As String

   'Find end of script
   For i = nScriptStart To UBound(strLines)
      If Right(strLines(i), 1) = Chr(34) Then
         nScriptEnd = i
         Exit For
      End If
   Next

   'Move script lines into tokens array for joining
   ReDim tokens(nScriptEnd - nScriptStart)
   For i = 0 To UBound(tokens)
      tokens(i) = strLines(i + nScriptStart)
   Next

   'Reconstitute script
   RestoreScript = UnQuote(Join(tokens, vbCrLf))
   ProcessScript RestoreScript, FromDisk
End Function

Public Function JoinFormCode() As String
Dim formObj As Object

   JoinFormCode = ""
   If Len(pgm_script) > 0 Then
      JoinFormCode = pgm_script
   End If
   If Len(event_script) > 0 Then
      If Len(JoinFormCode) > 0 Then JoinFormCode = JoinFormCode & vbCrLf & vbCrLf
      JoinFormCode = JoinFormCode & event_script
   End If
   If Len(pgm_script_after) > 0 Then
      If Len(JoinFormCode) > 0 Then JoinFormCode = JoinFormCode & vbCrLf & vbCrLf
      JoinFormCode = JoinFormCode & pgm_script_after
   End If
   For Each formObj In ObjectCollection
      If formObj.obj.ScriptLen > 0 Then
         If Len(JoinFormCode) > 0 Then JoinFormCode = JoinFormCode & vbCrLf & vbCrLf
         JoinFormCode = JoinFormCode & formObj.obj.script
      End If
   Next
End Function

Public Sub SplitFormCode(strCode As String)
Dim n1, n2, nModuleStart, nModuleEnd, nModule, nNewModule As Integer
Dim strLine, strModule, strSubName, strObjectName As String
Dim bNewObject As Boolean
Dim objTemp, objFormObj, objNewObj As Object

   'nModule:
   '0 = none
   '1 = before
   '2 = event
   '3 = after
   '4 = help
   '5 = object
   nModule = 0

   n1 = 1
   n2 = 1
   nModuleStart = 1
   nNewModule = 0
   While n1 < Len(strCode)
      n2 = InStr(n1, strCode, vbCrLf)
      'For end case with no closing crlf
      If n2 = 0 Then n2 = Len(strCode) + 1
      strLine = LCase(Mid(strCode, n1, n2 - n1))
      If StrComp(Left(strLine, Len("end sub")), "end sub") = 0 _
         Or StrComp(Left(strLine, Len("end function")), "end function") = 0 Then
         nModuleEnd = n2
      End If
      If StrComp(Left(strLine, Len("Sub")), "Sub", vbTextCompare) = 0 Then
         'Get sub name and determine if it begins a module
         strSubName = Mid(strLine, 5, InStr(1, strLine, "(") - 5)
         Select Case strSubName
         Case LCase(Name & "_before")
            nNewModule = 1
         Case LCase(Name & "_event")
            nNewModule = 2
         Case LCase(Name & "_after")
            nNewModule = 3
         Case Else
            If StrComp(Right(strSubName, Len("_click")), "_click") = 0 Then
               'check to make sure it is a valid object first
               strObjectName = Left(strSubName, Len(strSubName) - Len("_click"))
               For Each objTemp In ObjectCollection
                  If StrComp(objTemp.obj.Name, strObjectName, vbTextCompare) = 0 Then
                     Set objNewObj = objTemp
                     If IsEmpty(objFormObj) Then
                        Set objFormObj = objNewObj
                     End If
                     nNewModule = 5
                     bNewObject = True
                     Exit For
                  End If
               Next
            End If
         End Select

         'If module numbers don't match we've got something
         If nModule <> nNewModule Or bNewObject Then
            bNewObject = False
            If nModule <> 0 Then
               strModule = Mid(strCode, nModuleStart, nModuleEnd - nModuleStart)
               strModule = trimWhiteSpace(strModule)
MsgBox strModule
               CheckModuleIn nModule, strModule, objFormObj
               If Not IsEmpty(objNewObj) Then Set objFormObj = objNewObj
               nModuleStart = nModuleEnd + 2
            End If
            nModule = nNewModule
         End If
      End If
      'Go to start of next line, avoiding trailing lf
      n1 = n2 + 2
   Wend
   'Need to put away any remaining code here
   strModule = trimWhiteSpace(Mid(strCode, nModuleStart))
   If Len(strModule) > 0 Then CheckModuleIn nModule, strModule, objFormObj
End Sub

Private Sub CheckModuleIn(ByVal nModule As Integer, ByVal strModule As String, ByVal objFormObj As Object)
   Select Case nModule
   Case 1 'before
      aView.pgm_script = strModule
   Case 2 'event
      aView.event_script = strModule
   Case 3 'after
      aView.pgm_script_after = strModule
   Case 4 'help
   Case 5 'object
      objFormObj.obj.script = strModule
   End Select
End Sub

Public Property Get Modal() As Boolean
   Modal = m_bModal
End Property

Public Property Let Modal(ByVal vData As Boolean)
   m_bModal = vData
End Property

Public Property Get Frame() As Boolean
   Frame = m_bFrame
End Property

Public Property Let Frame(ByVal vData As Boolean)
   m_bFrame = vData
End Property

Public Property Get SaveBehind() As Boolean
   SaveBehind = m_bSaveBehind
End Property

Public Property Let SaveBehind(ByVal vData As Boolean)
   m_bSaveBehind = vData
End Property

Public Property Get IdNo() As Integer
   IdNo = m_nIdNo
End Property

Public Property Let IdNo(ByVal vData As Integer)
   m_nIdNo = vData
   If m_nIdNo Then Name = "Form" & IdNo
End Property

Public Property Get OriginLeft() As Integer
   OriginLeft = m_nOriginLeft
End Property

Public Property Let OriginLeft(ByVal vData As Integer)
   m_nOriginLeft = vData
End Property

Public Property Get OriginTop() As Integer
   OriginTop = m_nOriginTop
End Property

Public Property Let OriginTop(ByVal vData As Integer)
   m_nOriginTop = vData
End Property

Public Property Get Width() As Integer
   Width = m_nWidth
End Property

Public Property Let Width(ByVal vData As Integer)
   m_nWidth = vData
End Property

Public Property Get Height() As Integer
   Height = m_nHeight
End Property

Public Property Let Height(ByVal vData As Integer)
   m_nHeight = vData
End Property

Public Property Get IsDefaultForm() As Boolean
   IsDefaultForm = m_bIsDefaultForm
End Property

Public Property Let IsDefaultForm(ByVal vData As Boolean)
   m_bIsDefaultForm = vData
End Property

Public Property Get OptTitle() As Boolean
   OptTitle = m_bOptTitle
End Property

Public Property Let OptTitle(ByVal vData As Boolean)
   m_bOptTitle = vData
End Property

Public Property Get DefaultButtonID() As Integer
   DefaultButtonID = m_nDefaultButtonId
End Property

Public Property Let DefaultButtonID(ByVal vData As Integer)
   m_nDefaultButtonId = vData
End Property

'10.16.06 GH Start additions

Public Property Get TipsIdNo() As Integer
   TipsIdNo = m_nTipsIdNo
End Property
Public Property Let TipsIdNo(ByVal vData As Integer)
   m_nTipsIdNo = vData
End Property
Public Property Get Tips() As String
   Tips = m_sTips
End Property
Public Property Let Tips(ByVal vData As String)
   m_sTips = vData
End Property

Public Property Let NavFlags(ByVal vData As Long)
   m_nNavFlags = vData
End Property

Public Property Get NavFlags() As Long
   NavFlags = m_nNavFlags
End Property

Public Property Let NavFirstID(ByVal vData As Integer)
   m_nNavFirstID = vData
End Property

Public Property Get NavFirstID() As Integer
   NavFirstID = m_nNavFirstID
End Property

Public Property Let NavJumpToID(ByVal vData As Integer)
   m_nNavJumpToID = vData
End Property

Public Property Get NavJumpToID() As Integer
   NavJumpToID = m_nNavJumpToID
End Property

Public Property Let NavBottomLeftID(ByVal vData As Integer)
   m_nNavBottomLeftID = vData
End Property

Public Property Get NavBottomLeftID() As Integer
   NavBottomLeftID = m_nNavBottomLeftID
End Property
'10.16.06 GH End addtions


Public Property Let Name(ByVal vData As String)
Dim strOldName As String
Dim strProcName As String

   'Verify name
   If Len(vData) = 0 Then Exit Property
'   If InStr(1, vData, " ", vbTextCompare) > 0 Then Exit Property

   'Store old name to update scripts
   strOldName = m_strName
   
   'Set name
   m_strName = vData
   strProcName = Replace(m_strName, " ", "_")

   'Update scripts with new name
   If Len(pgm_script) > 0 Then
      pgm_script = Replace(pgm_script, strOldName & "_before", strProcName & "_before", , , vbTextCompare)
      'Next, replace all other occurences in project
   End If
   If Len(event_script) > 0 Then
      event_script = Replace(event_script, strOldName & "_event", strProcName & "_event", , , vbTextCompare)
      'Next, replace all other occurences in project
   End If
   If Len(pgm_script_after) > 0 Then
      pgm_script_after = Replace(pgm_script_after, strOldName & "_after", strProcName & "_after", , , vbTextCompare)
      'Next, replace all other occurences in project
   End If
End Property

Public Property Get Name() As String
   Name = m_strName
End Property

Public Property Get Project() As CProject
   Set Project = m_Project
End Property

Public Property Let Project(prj As CProject)
   Set m_Project = prj
End Property

Public Property Get Object(nID As Integer) As Object
Dim obj As Object

   For Each obj In ObjectCollection
      If obj.obj.IdNo = nID Then
         Set Object = obj
         Exit Property
      End If
   Next
End Property

Public Sub GetProperty()
Static nProp As Integer

   If nProp = 15 Then
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
   Case 1 'ID
      gPropInfo.Name = "ID"
      gPropInfo.Type = pgReadOnly
   Case 2 'Title
      gPropInfo.Name = "Title"
   Case 3 'Default Form
      gPropInfo.Name = "Default Form"
      gPropInfo.Type = pgBoolean
   Case 4 'Show Titlebar
      gPropInfo.Name = "Show Titlebar"
      gPropInfo.Type = pgBoolean
   Case 5 'Left
      gPropInfo.Name = "Left"
   Case 6 'Top
      gPropInfo.Name = "Top"
   Case 7 'Width
      gPropInfo.Name = "Width"
   Case 8 'Height
      gPropInfo.Name = "Height"
   Case 9 'Modal
      gPropInfo.Name = "Modal Form"
      gPropInfo.Type = pgBoolean
   Case 10
      gPropInfo.Name = "Nav Flags"
   Case 11
      gPropInfo.Name = "Nav First ID"
   Case 12
      gPropInfo.Name = "Nav Jump To ID"
   Case 13
      gPropInfo.Name = "Nav Bottom ID"
   Case 14
      gPropInfo.Name = "Modal Tips"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgStringList
      gPropInfo.data = GetStringList
   End Select
   gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "(Name)": GetPropertyVal = Name
   Case "ID": GetPropertyVal = IdNo
   Case "Title": GetPropertyVal = Title
   Case "Default Form": GetPropertyVal = IsDefaultForm
   Case "Show Titlebar": GetPropertyVal = OptTitle
   Case "Left": GetPropertyVal = OriginLeft
   Case "Top": GetPropertyVal = OriginTop
   Case "Width": GetPropertyVal = Width
   Case "Height": GetPropertyVal = Height
   Case "Modal Form": GetPropertyVal = Modal
   Case "Nav Flags": GetPropertyVal = NavFlags
   Case "Nav First ID": GetPropertyVal = NavFirstID
   Case "Nav Jump To ID": GetPropertyVal = NavJumpToID
   Case "Nav Bottom ID": GetPropertyVal = NavBottomLeftID
   Case "Modal Tips":
      'GetPropertyVal = Tips
      If m_sTips = "" Then
         GetPropertyVal = "(Empty)"
      Else
         GetPropertyVal = "(" & Len(m_sTips) & " Chars)"
      End If
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim strWork As String
Dim frm As CForm
Dim n As Integer
Dim l As Long

   ValidateProperty = True
   Select Case strProp
   Case "(Name)"
      'Make sure form name is unique within the project
      For Each frm In m_Project.FormCollection
         If StrComp(strVal, frm.Name, vbTextCompare) = 0 Then
            MsgBox gStringTable(kErrStrings) & "'" & strVal & "'", vbCritical + vbOKOnly
            ValidateProperty = False
            Exit Function
         End If
      Next

      Name = Trim(strVal)
   Case "ID"
   Case "Title"
      Title = ReplaceQuotes(strVal)
   Case "Default Form"
      If strVal Like g_strTrue Then
         IsDefaultForm = True
         For Each frm In m_Project.FormCollection
            If Not frm Is Me Then
               If frm.IsDefaultForm Then
                  If MsgBox("'" & frm.Name & "'" & gStringTable(kResStrings), vbYesNo) = vbYes Then
                     frm.IsDefaultForm = False
                     IsDefaultForm = True
                  Else
                     IsDefaultForm = False
                  End If
               End If
            End If
         Next
      Else
         IsDefaultForm = False
      End If
   Case "Show Titlebar"
      OptTitle = strVal Like g_strTrue
   Case "Left"
      n = Val(strVal)
      If n < 0 Then n = 0
      OriginLeft = n
   Case "Top"
      n = Val(strVal)
      If n < 0 Then n = 0
      OriginTop = n
   Case "Width"
      n = Val(strVal)
      If n < 0 Then n = 0
      Width = n
   Case "Height"
      n = Val(strVal)
      If n < 0 Then n = 0
      Height = n
   Case "Modal Form"
      Modal = (strVal Like g_strTrue)
   Case "Nav Flags"
      l = Val(strVal)
      If l < 0 Then l = 0
      NavFlags = l
   Case "Nav First ID"
      n = Val(strVal)
      If n < 0 Then n = 0
      If n > 0 And Object(n) Is Nothing Then n = 0
      NavFirstID = n
   Case "Nav Jump To ID"
      n = Val(strVal)
      If n < 0 Then n = 0
      If n > 0 And Object(n) Is Nothing Then n = 0
      NavJumpToID = n
   Case "Nav Bottom ID"
      n = Val(strVal)
      If n < 0 Then n = 0
      If n > 0 And Object(n) Is Nothing Then n = 0
      NavBottomLeftID = n
   Case "Modal Tips"
      Tips = ReplaceQuotes(strVal)
   End Select
   If ValidateProperty Then Project.Dirty = True
End Function

Public Property Get GlobalID() As String
Attribute GlobalID.VB_UserMemId = 0
   GlobalID = Join(Array("form", IdNo, m_Project.GlobalID), "|")
End Property

Public Function GetScript(strScript As String, Optional bForceCreate As Boolean = True) As String
   Select Case strScript
   Case "before"
      If pgm_script <> "" Or Not bForceCreate Then
         GetScript = pgm_script
      Else
         GetScript = "Sub Form" & IdNo & "_Before()" & vbCrLf & vbCrLf & "End Sub"
      End If
   Case "after"
      If pgm_script_after <> "" Or Not bForceCreate Then
         GetScript = pgm_script_after
      Else
         GetScript = "Sub Form" & IdNo & "_After()" & vbCrLf & vbCrLf & "End Sub"
      End If
   Case "event"
      If event_script <> "" Or Not bForceCreate Then
         GetScript = event_script
      Else
         GetScript = "Sub Form" & IdNo & "_Event()" & vbCrLf & vbCrLf & "End Sub"
      End If
   End Select
   PutScript GetScript, strScript
End Function

Public Sub PutScript(ByVal strText As String, ByVal strScript As String)
   Select Case strScript
   Case "before": pgm_script = strText
   Case "after": pgm_script_after = strText
   Case "event": event_script = strText
   End Select
   m_Project.Dirty = True
End Sub

Public Sub AddNewObject(ByVal obj As Object)
   obj.obj.IdNo = Project.GetNextSeqNo
   Select Case obj.obj.Kind
   'These object types require an additional resource ID
   Case "pop", "fld": Project.GetNextSeqNo
   'the grid needs 4 extra numbers
   Case "grd":
      Project.GetNextSeqNo
      Project.GetNextSeqNo
      Project.GetNextSeqNo
      Project.GetNextSeqNo
   End Select
   ObjectCollection.Add obj
   obj.obj.Form = Me
   Project.Dirty = True
End Sub

Public Sub RemoveObject(ByVal obj As Object)
Dim i As Integer

   For i = 1 To ObjectCollection.count
      If ObjectCollection(i).obj.GlobalID = obj.obj.GlobalID Then
         ObjectCollection.Remove i
         Exit For
      End If
   Next
End Sub

Public Function BuildMap() As String()
Dim strMap As String
Dim obj As Object
Const kSep As String = ">"

   strMap = Join(Array(GlobalID & "|before", GlobalID & "|event", GlobalID & "|after"), kSep)
   For Each obj In ObjectCollection
      strMap = strMap & kSep & obj.obj.GlobalID & "|code"
   Next
   BuildMap = Split(strMap, kSep)
End Function

Public Function PropertyList() As String()
   PropertyList = Split(kProperties, "-")
End Function

Public Function MethodList() As String()
   MethodList = Split(kMethods, "-")
End Function

Public Function GetObjectType(astrName As String) As String
Dim obj As Object

   If StrComp(Name, astrName, vbTextCompare) = 0 Then
      GetObjectType = "frm"
   Else
      For Each obj In ObjectCollection
         If StrComp(obj.obj.Name, astrName, vbTextCompare) = 0 Then GetObjectType = obj.obj.Kind
         If GetObjectType <> "" Then Exit Function
      Next
   End If
End Function
Public Function GetStringList() As String
   GetStringList = "Modal Tips>" & m_sTips
End Function
