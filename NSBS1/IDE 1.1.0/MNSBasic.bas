Attribute VB_Name = "MNSBasic"
Option Explicit

Public Const knInvalidChars As Integer = 1406 'Resource ID
Public Const kClipboardHeader = "NS Basic Clipboard"
Public Const kClipboardForm = 1
Public Const kClipboardObject = 2
Public Const kClipboardMenu = 3
Public Const kClipboardMenuBar = 4
Public Const kClipboardMenuElem = 5

Public Const kFindCase As Integer = &H1
Public Const kFindWord As Integer = &H2
Public Const kFindModule As Integer = &H10
Public Const kFindProject As Integer = &H20
Public Const kFindSelected As Integer = &H40

Public gstrFind As String
Public gstrReplace As String
Public gbNewFind As Boolean
Public gbFindAny As Boolean
Public gbFindOne As Boolean
Public gbFindAbort As Boolean
Public gbReplaceAll As Boolean
Public garrSearchMap() As String
Public gnSearchStart As Integer
Public gnSearchLoc As Integer
Public gnFindFlags As Integer
Public gnReplaceCount As Integer
Public gSearchSel As CodeMax4Ctl.range
Public gbReplaceChange As Boolean

Public gbWinNT2000 As Boolean
Public gstrPalmFonts(7) As String
Public gnPalmFontSize(7) As Integer

'Public Function TraverseProject(Optional strGID As String = "") As String
'Dim arrGID() As String
'Static s_strGIDStart As String
'Static s_strGIDCurrent As String
'Dim strStartBase As String
'Dim strCurBase As String
'Dim strCurLoc As String
'
'   If Len(strGID) <> 0 Then
'      s_strGIDStart = strGID
'      s_strGIDCurrent = s_strGIDStart
'   End If
'
'   strStartBase = Left(s_strGIDStart, InStr(1, s_strGIDStart, "|") - 1)
'   strCurBase = Left(s_strGIDCurrent, InStr(1, s_strGIDCurrent, "|") - 1)
'   strCurLoc = Mid(s_strGIDCurrent, InStrRev(s_strGIDCurrent, "|") + 1)
'
'   arrGID = Split(s_strGIDCurrent, "|")
'   Select Case strCurBase
'   Case "project"
'      If UBound(arrGID) = 1 Then
'         'Go to startup
'         ReDim Preserve arrGID(2)
'         arrGID(2) = "startup"
'      Else
'         If strCurLoc = "startup" Then
'            'Go to termination
'            arrGID(2) = "termination"
'         ElseIf strCurLoc = "termination" Then
'            'Go to form
'            'Go to menu
'            'Go to module
'         End If
'      End If
'   Case "form"
'      If UBound(arrGID) = 3 Then
'         'Go to before
'         ReDim Preserve arrGID(4)
'         arrGID(4) = "before"
'      Else
'         Select Case strCurLoc
'         Case "before"
'            arrGID(4) = "event"
'         Case "event"
'            arrGID(4) = "after"
'         Case "after"
''            arrGID(4) = "help"
'            'Go to objects
'         End Select
'      End If
'   Case "object"
'
'   End Select
'
'   s_strGIDCurrent = Join(arrGID, "|")
'   TraverseProject = s_strGIDCurrent
'End Function

Public Sub CMaxPrepFindReplace(ByVal cMax As CodeMax4Ctl.CodeMax)
   cMax.ExecuteCmd cmCmdSetFindText, gstrFind
   cMax.ExecuteCmd cmCmdSetReplaceText, gstrReplace
   'Case sensitivity
   If gnFindFlags And kFindCase Then
      cMax.ExecuteCmd cmCmdCaseSensitiveOn
   Else
      cMax.ExecuteCmd cmCmdCaseSensitiveOff
   End If

   'Whole word
   If gnFindFlags And kFindWord Then
      cMax.ExecuteCmd cmCmdWholeWordOn
   Else
      cMax.ExecuteCmd cmCmdWholeWordOff
   End If
End Sub

Public Function CMaxFindNext(ByVal cMax As CodeMax4Ctl.CodeMax) As Boolean
Dim range1 As CodeMax4Ctl.range
Dim range2 As CodeMax4Ctl.range

   CMaxPrepFindReplace cMax

   'Selected Text
   Set range1 = cMax.GetSel(True)
'   If gnFindFlags And kFindSelected Then
'      range.EndColNo = range.StartColNo
'      range.EndLineNo = range.StartLineNo
'   Else
'      range.StartColNo = range.EndColNo
'      range.StartLineNo = range.EndLineNo
'   End If
'   cMax.SetSel range, True

   cMax.ExecuteCmd cmCmdFindNext, 0
   If StrComp(cMax.SelText, gstrFind, vbTextCompare) = 0 Then
      Set range2 = cMax.GetSel(True)
      If range2.StartLineNo > range1.StartLineNo _
            Or ((range2.StartLineNo = range1.StartLineNo) And (range2.EndColNo > range1.EndColNo)) Then
         CMaxFindNext = True
      Else
         range1.StartColNo = range1.EndColNo
         range1.StartLineNo = range1.EndLineNo
         cMax.SetSel range1, True
         If gnFindFlags And kFindModule Then
            If MsgBox(gStringTable(3306), vbYesNo + vbQuestion) = vbYes Then
               '"End of search area reached, do you want to start from the beginning?
               range1.StartColNo = 0
               range1.EndColNo = 0
               range1.StartLineNo = 0
               range1.EndLineNo = 0
               cMax.SetSel range1, True
               CMaxFindNext = CMaxFindNext(cMax)
            End If
         End If
      End If
   End If
End Function

Public Function FindNext() As Boolean
Dim frm As frmCode
Dim sel As range

   CMaxPrepFindReplace frmMain.cmaxFind
   frmMain.cmaxFind.Text = GetScript(garrSearchMap(gnSearchLoc))
   If gnFindFlags = kFindSelected Then
      frmMain.cmaxFind.SetSel gSearchSel, True
   End If

lblFindNextFailed:
   While frmMain.cmaxFind.TextLength = 0 And gnSearchLoc >= 0
      gnSearchLoc = (gnSearchLoc + 1) Mod (UBound(garrSearchMap) + 1)
      If gnSearchLoc = gnSearchStart Then
         gnSearchLoc = -1
      Else
         frmMain.cmaxFind.Text = GetScript(garrSearchMap(gnSearchLoc))
      End If
   Wend
   If frmMain.cmaxFind.TextLength = 0 Then Exit Function

   'Set selection to match current code window, if one is open
   Set frm = frmMain.GetMDIChild(garrSearchMap(gnSearchLoc))
   If Not frm Is Nothing Then
      'Do something tricky here to set selection
      Set sel = frm.GetSel
      If Not sel.IsEmpty Then
         If gnFindFlags And kFindSelected Then
            frmMain.cmaxFind.Text = frm.SelText
         Else
            'Move to end of selection and begin searching from there
            sel.Empty
            frmMain.cmaxFind.SetSel sel, True
         End If
      End If
   End If

   'Do the find
   gbFindOne = False
   frmMain.cmaxFind.ExecuteCmd cmCmdFindNext, 0
   gbNewFind = False
   If gbFindOne Then
      FindNext = True
      Set frm = frmMain.ViewCode(garrSearchMap(gnSearchLoc))
      Set sel = frmMain.cmaxFind.GetSel(True)
      frm.SetSel sel
   Else
'      gnSearchLoc = (gnSearchLoc + 1) Mod (UBound(garrSearchMap) + 1)
      frmMain.cmaxFind.Text = ""
      GoTo lblFindNextFailed
   End If
End Function

Sub ShowStatus(Optional ByVal strStatus As String = "", Optional bAutoClear As Boolean = False)
   frmMain.sbStatusBar.Panels(1).Text = strStatus
   frmMain.tmrStatus.Enabled = False
   If bAutoClear Then frmMain.tmrStatus.Enabled = True
End Sub

Sub ShowCursor(l As Integer, c As Integer)
   frmMain.sbStatusBar.Panels(2).Text = "Line: " & l & "   Col: " & c
End Sub

Sub ShowCoordinates(x As Integer, y As Integer) ', Optional bAutoClear As Boolean = False)
   If x = -44 And y = -44 Then
      frmMain.sbStatusBar.Panels(2).Text = ""
   Else
      frmMain.sbStatusBar.Panels(2).Text = "X: " & x & "   Y: " & y
   End If
'   frmMain.tmrStatus.Enabled = False
'   If bAutoClear Then frmMain.tmrStatus.Enabled = True
End Sub

Sub ShowDimensions(w As Integer, h As Integer) ', Optional bAutoClear As Boolean = False)
   If w = -44 And h = -44 Then
      frmMain.sbStatusBar.Panels(3).Text = ""
   Else
      frmMain.sbStatusBar.Panels(3).Text = "W: " & w & "   H: " & h
   End If
'   frmMain.tmrStatus.Enabled = False
'   If bAutoClear Then frmMain.tmrStatus.Enabled = True
End Sub

Function LocateProject(ByVal strGID As String) As CProject
Dim arrGID() As String
Dim proj As CProject
Dim cMod As CCodeModule

   arrGID = Split(strGID, "|")
   Select Case arrGID(0)
   Case "project": Set LocateProject = frmMain.Project(arrGID(1))
   Case "form", "bitmap", "resource": Set LocateProject = frmMain.Project(arrGID(3))
   Case "object": Set LocateProject = frmMain.Project(arrGID(5))
   Case "menu": Set LocateProject = frmMain.Project(arrGID(3))
   Case "menubar": Set LocateProject = frmMain.Project(arrGID(5))
   Case "menuelem": Set LocateProject = frmMain.Project(arrGID(7))
   Case "module" ': MsgBox "You locate a Module's project"
      For Each proj In gProjects
         For Each cMod In proj.CodeCollection
            If cMod.GlobalID = arrGID(0) & "|" & arrGID(1) Then
               Set LocateProject = proj
               Exit Function
            End If
         Next
      Next
   Case "Forms", "Bitmaps", "Modules", "Resources": Set LocateProject = frmMain.Project(arrGID(2))
   End Select
End Function

Function LocateObject(ByVal strGID As String) As Object
Dim arrGID() As String
Dim proj As CProject
Dim obj As Object, o2 As Object, o3 As Object

   arrGID = Split(strGID, "|")
   Select Case arrGID(0)
   Case "project" 'project|IDE Serial#
      Set LocateObject = frmMain.Project(arrGID(1))
   Case "form" 'form|Form Resource ID|project|IDE Serial #
      Set proj = frmMain.Project(arrGID(3))
      Set LocateObject = proj.Form(Val(arrGID(1)))
   Case "menu" 'menu|Menu Resource ID|project|IDE Serial #
      Set proj = frmMain.Project(arrGID(3))
      For Each obj In proj.MenuCollection
         If obj.IdNo = arrGID(1) Then
            Set LocateObject = obj
            Exit Function
         End If
      Next
   Case "menubar" 'menubar|MenuBar Resource ID|menu|Menu Resource ID|project|IDE Serial #
      Set proj = frmMain.Project(arrGID(5))
      For Each obj In proj.MenuCollection
         If obj.IdNo = arrGID(3) Then
            For Each o2 In obj.MenuBars
               If o2.IdNo = arrGID(1) Then
                  Set LocateObject = o2
                  Exit Function
               End If
            Next
         End If
      Next
   Case "menuelem" 'menuelem|MenuElem Resource ID|menubar|MenuBar Resource ID|menu|Menu Resource ID|project|IDE Serial #
      Set proj = frmMain.Project(arrGID(7))
      For Each obj In proj.MenuCollection
         If obj.IdNo = arrGID(5) Then
            For Each o2 In obj.MenuBars
               If o2.IdNo = arrGID(3) Then
                  For Each o3 In o2.MenuElems
                     If o3.IdNo = arrGID(1) Then
                        Set LocateObject = o3
                        Exit Function
                     End If
                  Next
               End If
            Next
         End If
      Next
   Case "bitmap" 'bitmap|Bitmap Resource ID|project|IDE Serial#
      Set proj = frmMain.Project(arrGID(3))
      Set LocateObject = proj.Bitmap(Val(arrGID(1)))
   Case "resource" 'resource|Resource Resource ID|project|IDE Serial#
      Set proj = frmMain.Project(arrGID(3))
      Set LocateObject = proj.resource(Val(arrGID(1)))
   Case "module" 'module|Module Path
      'Modules can be so unclean...
      For Each obj In gTarget.CodeCollection
         If StrComp(obj.GlobalID, arrGID(0) & "|" & arrGID(1), vbTextCompare) = 0 Then
            Set LocateObject = obj
            Exit Function
         End If
      Next
'      Set LocateObject = proj.Module(Val(arrGID(2)))
   Case "object" 'object|Object Resource ID|form|Form Resource ID|project|IDE Serial#
      Set proj = frmMain.Project(arrGID(5))
      Set LocateObject = proj.Form(Val(arrGID(3))).Object(Val(arrGID(1)))
   Case "Forms", "Menus", "Bitmaps", "Modules", "Resources" '[Forms|Menus|Bitmaps|Modules]|project|IDE Serial#
      'Same as project... for now
      Set LocateObject = frmMain.Project(arrGID(2))
   End Select
End Function

Sub ProjectAddForm(Optional ByVal proj As CProject = Nothing)
Dim frm As CForm
Dim fPalmScreen As New frmPalmScreen

   If proj Is Nothing Then Set proj = gTarget
   Set frm = proj.AddNewForm
   If gbProjectExplorer Then gfProjectExplorer.AddNewForm frm, proj
   frmMain.ViewObject frm.GlobalID
'   fPalmScreen.Object = frm
'   fPalmScreen.Show
'   frmMain.AddMDIChild fPalmScreen
End Sub

Sub ProjectRemoveForm(ByVal frm As CForm, Optional ByVal proj As CProject)
Dim f As Form
Dim ob As Object
If MsgBox(gStringTable(3442) & frm.Title & "?", vbYesNo) = vbYes Then

   'First close the Palm Screen displaying the form and any of its code windows
   Set f = frmMain.RemoveMDIChild(frm.GlobalID)
   If Not f Is Nothing Then Unload f
   Set f = frmMain.RemoveMDIChild(frm.GlobalID & "|before")
   If Not f Is Nothing Then Unload f
   Set f = frmMain.RemoveMDIChild(frm.GlobalID & "|after")
   If Not f Is Nothing Then Unload f
   Set f = frmMain.RemoveMDIChild(frm.GlobalID & "|event")
   If Not f Is Nothing Then Unload f
   For Each ob In frm.ObjectCollection
      Set f = frmMain.RemoveMDIChild(ob.obj.GlobalID & "|code")
      If Not f Is Nothing Then Unload f
   Next
   proj.RemoveForm frm.GlobalID
   gfProjectExplorer.RemoveNode frm.GlobalID
   If gbProperties Then gfProperties.Object = Nothing
End If
End Sub

Sub ProjectAddMenu(Optional ByVal proj As CProject = Nothing)
Dim fMenuEditor As New frmMenuEditor

   If proj Is Nothing Then Set proj = gTarget
   If Not proj.AddMenu Then Exit Sub
   fMenuEditor.Project = proj
   fMenuEditor.Menu = proj.MenuCollection(proj.MenuCollection.count)
   fMenuEditor.Show vbModal, frmMain
   gfProjectExplorer.UpdateProjectMenus proj
End Sub

Sub ProjectRemoveMenu(ByVal mnu As CMenu, Optional ByVal proj As CProject = Nothing)
   If proj Is Nothing Then Set proj = gTarget
   proj.MenuCollection.Remove str(mnu.IdNo)
   gfProjectExplorer.RemoveNode mnu.GlobalID
   If gbProperties Then gfProperties.Object = Nothing
End Sub

Sub ProjectAddMenuBar(ByVal mnu As CMenu, Optional ByVal proj As CProject = Nothing)
Dim mBar As New CMenuBar

   If proj Is Nothing Then Set proj = gTarget
   If gLanguage <> "nippon" Then
      mBar.caption = InputBox(gStringTable(1625), gStringTable(1629), mBar.caption)
   Else
      mBar.caption = InputBox(gStringTable(1625) + " " + gStringTable(1629), , mBar.caption)
   End If
   If mBar.caption = "" Then Exit Sub
   proj.Dirty = True
   mBar.IdNo = proj.GetNextSeqNo
   mBar.SetGlobalID mnu.GlobalID
   mnu.MenuBars.Add mBar, str(mBar.IdNo)
   gfProjectExplorer.AddNewMenuBar mBar, mnu
End Sub

Sub ProjectRemoveMenuBar(ByVal mBar As CMenuBar, Optional ByVal proj As CProject = Nothing)
Dim mnu As CMenu
Dim mBar2 As CMenuBar

   On Error Resume Next
   If proj Is Nothing Then Set proj = gTarget
   For Each mnu In proj.MenuCollection
      Set mBar2 = mnu.MenuBars(str(mBar.IdNo))
      If Not mBar2 Is Nothing Then
         mnu.MenuBars.Remove str(mBar.IdNo)
         gfProjectExplorer.RemoveNode mBar.GlobalID
         If gbProperties Then gfProperties.Object = Nothing
         Exit Sub
      End If
   Next
End Sub

Sub ProjectAddMenuElem(ByVal mBar As CMenuBar, Optional ByVal proj As CProject = Nothing)
Dim mElem As New CMenuElem

   If proj Is Nothing Then Set proj = gTarget
   If gLanguage <> "Nippon" Then
      mElem.caption = InputBox(gStringTable(1628), gStringTable(1630), mElem.caption)
   Else
      mElem.caption = InputBox(gStringTable(1628) + " " + gStringTable(1630), , mElem.caption)
   End If
   If mElem.caption = "" Then Exit Sub
   proj.Dirty = True
   mElem.IdNo = proj.GetNextSeqNo
   mElem.SetGlobalID mBar.GlobalID
   mBar.MenuElems.Add mElem, Trim(str(mElem.IdNo))
   gfProjectExplorer.AddNewMenuElem mElem, mBar
End Sub

Sub ProjectRemoveMenuElem(ByVal mElem As CMenuElem, Optional ByVal proj As CProject = Nothing)
Dim mnu As CMenu
Dim mBar As CMenuBar
Dim mElem2 As CMenuElem

   On Error Resume Next
   If proj Is Nothing Then Set proj = gTarget
   For Each mnu In proj.MenuCollection
      For Each mBar In mnu.MenuBars
         Set mElem2 = mBar.MenuElems(Trim(str(mElem.IdNo)))
         If Not mElem2 Is Nothing Then
            mBar.MenuElems.Remove Trim(str(mElem.IdNo))
            gfProjectExplorer.RemoveNode mElem.GlobalID
            If gbProperties Then gfProperties.Object = Nothing
            Exit Sub
         End If
      Next
   Next
End Sub

Sub ProjectAddBitmap(Optional ByVal proj As CProject = Nothing)
Dim bmp As CBitmapFile
Dim filename As String
Dim names() As String
Dim Name As Variant
Dim i As Integer
Dim j As Integer

   On Error GoTo gotCancel
   frmMain.dlgCommonDialog.CancelError = True
   frmMain.dlgCommonDialog.DialogTitle = gStringTable(2202) '"Add Bitmap"
   frmMain.dlgCommonDialog.InitDir = fileDirectory + "\bitmaps"
   frmMain.dlgCommonDialog.DefaultExt = "bmp"
   frmMain.dlgCommonDialog.Filter = gStringTable(2200) '"Image Files (*.gif;*.jpg;*.bmp;*.ico;*.emf;*.wmf)|*.gif;*.jpg;*.bmp;*.ico;*.emf;*.wmf|All Files|*.*"  '7/19/1 GH
   frmMain.dlgCommonDialog.filename = ""
   frmMain.dlgCommonDialog.flags = cdlOFNNoChangeDir 'cdlOFNLongNames + cdlOFNAllowMultiselect '7/19/1 gh
   frmMain.dlgCommonDialog.ShowOpen
   On Error GoTo 0

   If frmMain.dlgCommonDialog.filename = "" Then
      Beep
      Exit Sub
   End If
   If proj Is Nothing Then Set proj = gTarget

   Set bmp = proj.AddNewBitmap(frmMain.dlgCommonDialog.filename)
   gfProjectExplorer.AddNewBitmap bmp, proj
   DoEvents
   gfProjectExplorer.ShowActive bmp
   
gotCancel:
End Sub

Sub ProjectAddResource(Optional ByVal proj As CProject = Nothing)
Dim res As CResourceFile
Dim filename As String
Dim names() As String
Dim Name As Variant
Dim i As Integer
Dim j As Integer

   On Error GoTo gotCancel
   frmMain.dlgCommonDialog.CancelError = True
   frmMain.dlgCommonDialog.DialogTitle = gStringTable(3357) '"Add resource"
   frmMain.dlgCommonDialog.InitDir = fileDirectory + "\Lib"
   frmMain.dlgCommonDialog.DefaultExt = "prc"
   frmMain.dlgCommonDialog.Filter = "Resource Files (*.prc;*.pdb)|*.prc;*.pdb|All Files|*.*" '7/19/1 gh
   frmMain.dlgCommonDialog.filename = ""
   frmMain.dlgCommonDialog.flags = cdlOFNLongNames + cdlOFNNoChangeDir
   frmMain.dlgCommonDialog.ShowOpen
   On Error GoTo 0

   If frmMain.dlgCommonDialog.filename = "" Then
      Beep
      Exit Sub
   End If
   If proj Is Nothing Then Set proj = gTarget

   Set res = proj.AddNewResource(frmMain.dlgCommonDialog.filename)
   
   ' EMP
   ' Guess resource name to make shared libs easier
   res.GuessName
   
   gfProjectExplorer.AddNewResource res, proj
   
   
   DoEvents
   gfProjectExplorer.ShowActive res
   
gotCancel:
End Sub

Sub ProjectAddModuleNew(Optional ByVal proj As CProject = Nothing)
Dim cMod As CCodeModule

   If proj Is Nothing Then Set proj = gTarget
   Set cMod = proj.AddModule
   frmMain.ViewCode cMod.GlobalID, "code"
   gfProjectExplorer.AddNewModule cMod, proj
End Sub

Sub ProjectAddModuleExisting(Optional ByVal proj As CProject = Nothing)
Dim cMod As CCodeModule

   On Error GoTo gotCancel
   frmMain.dlgCommonDialog.CancelError = True
   frmMain.dlgCommonDialog.DialogTitle = "Add Module"
   frmMain.dlgCommonDialog.InitDir = fileDirectory + "\Projects"
   frmMain.dlgCommonDialog.DefaultExt = "cod"
   frmMain.dlgCommonDialog.Filter = "Modules (*.cod)|*.cod"
   frmMain.dlgCommonDialog.flags = cdlOFNLongNames + cdlOFNNoChangeDir
   frmMain.dlgCommonDialog.filename = ""
   frmMain.dlgCommonDialog.ShowOpen
   On Error GoTo 0

   If frmMain.dlgCommonDialog.filename = "" Then
      Beep
      Exit Sub
   End If
'   bmp.pathName = frmSave.comdlg.fileName
'   bmp.SetFileName gComDlg.FileName
    
   If proj Is Nothing Then Set proj = gTarget
   Set cMod = proj.AddModule(frmMain.dlgCommonDialog.filename)
   gfProjectExplorer.AddNewModule cMod, proj
'   model1.BitmapCollection.Add bmp
gotCancel:
End Sub

Sub ProjectRemoveModule(ByVal cMod As CCodeModule, Optional ByVal proj As CProject)
Dim f As Form

   'Make sure we have a project
   If proj Is Nothing Then Set proj = gTarget

   'First close the code window displaying the module
   Set f = frmMain.RemoveMDIChild(cMod.GlobalID & "|code")
   If Not f Is Nothing Then Unload f
   proj.RemoveModule cMod.GlobalID
   gfProjectExplorer.RemoveNode cMod.GlobalID
   If gbProperties Then gfProperties.Object = Nothing
End Sub

Sub FormRemoveObject(ByVal frm As CForm, ByVal obj As Object)
Dim f As Form

   'First close the object's code window
   Set f = frmMain.RemoveMDIChild(obj.obj.GlobalID & "|code")
   If Not f Is Nothing Then Unload f
   'Now remove control from Palm Screen
   Set f = frmMain.GetMDIChild(frm.GlobalID)
   If Not f Is Nothing Then f.RemoveUIObject obj
   frm.RemoveObject obj
   If gbProjectExplorer Then gfProjectExplorer.RemoveNode obj.obj.GlobalID
   If gbProperties Then gfProperties.Object = Nothing
End Sub

Sub ProcessScript(ByRef strScript As String, lDirection As Long)
   Dim i As Long

   If lDirection = ToDisk Then
      For i = 1 To Len(strScript)
         If Mid(strScript, i, 1) = "~" Then
            Mid(strScript, i, 1) = Chr$(6)
         End If
         If Mid(strScript, i, 1) = Chr$(34) Then
            Mid(strScript, i, 1) = "~"
         End If
      Next
   Else
      For i = 1 To Len(strScript)
         If Mid(strScript, i, 1) = "~" Then
            Mid(strScript, i, 1) = Chr$(34)
         End If
         If Mid(strScript, i, 1) = Chr$(6) Then
            Mid(strScript, i, 1) = "~"
         End If
      Next
   End If
End Sub

Function Quote(strVal As String) As String
   Quote = Chr(34) + strVal + Chr(34)
End Function

Function UnQuote(strVal As String) As String
   If Left(strVal, 1) = ("" & Chr(34)) And Right(strVal, 1) = ("" & Chr(34)) Then
      UnQuote = Mid(strVal, 2, Len(strVal) - 2)
   Else
      UnQuote = strVal
   End If
End Function

Function BoolStr(bVal As Boolean) As String
   If bVal Then BoolStr = "#TRUE#" Else BoolStr = "#FALSE#"
End Function

Function UnBoolStr(strVal As String) As Boolean
   If strVal = "#TRUE#" Then UnBoolStr = True Else UnBoolStr = False
End Function

Public Function ValidClipboard() As Integer
Dim strClip As String

   ValidClipboard = 0
   If Clipboard.GetFormat(vbCFText) Then
      If (Left(Clipboard.GetText, Len(kClipboardHeader)) = kClipboardHeader) Then
         strClip = Mid(Clipboard.GetText, Len(kClipboardHeader & vbCrLf) + 2)
         Select Case Left(strClip, InStr(strClip, Chr(34)) - 1)
         Case "vew": ValidClipboard = kClipboardForm
         Case "mnu": ValidClipboard = kClipboardMenu
         Case "menubar": ValidClipboard = kClipboardMenuBar
         Case "menuelem": ValidClipboard = kClipboardMenuElem
         Case Else: ValidClipboard = kClipboardObject
         End Select
      End If
   End If
End Function

'Sub PasteForm(ByRef strLines() As String, ByVal proj As CProject)
'Dim frm As CForm
'
'   If strLines(0) <> kClipboardHeader Then Exit Sub
'   Select Case LCase(UnQuote(strLines(1)))
'   Case "vew", "form"
'      Set frm = proj.AddNewForm
'      frm.Paste strLines
''      gtarget.formcollection.Add View
''      projectDirty = True
''      RebuildProjectExplorer
''      Refresh
'      If UBound(strLines) > 1 Then PasteObject strLines, frm
'   End Select
'   gfProjectExplorer.AddNewForm frm, proj
'End Sub
'
'Function PasteObject(ByRef strLines() As String, ByRef frm As CForm) As Object
'Dim pasteObj As Object
'Dim fPalmScreen As frmPalmScreen
'
'   Select Case LCase(UnQuote(strLines(1)))
'   Case "bmp": Set pasteObj = New CUIBitmap
'   Case "but": Set pasteObj = New CUIButton
'   Case "chk": Set pasteObj = New CUICheckbox
'   Case "cho": Set pasteObj = New CUIPushbutton
'   Case "fld": Set pasteObj = New CUIField
'   Case "gad": Set pasteObj = New CUIGadget
'   Case "lbl": Set pasteObj = New CUILabel
'   Case "lst": Set pasteObj = New CUIList
'   Case "pop": Set pasteObj = New CUIPopup
'   Case "rpt": Set pasteObj = New CUIRepeater
'   Case "scr": Set pasteObj = New CUIScrollbar
'   Case "sel": Set pasteObj = New CUISelector
'   Case "shf": Set pasteObj = New CUIGraffitiShiftIndicator
''   Case "tbl": Set pasteObj = New cUITable
'   End Select
'   frm.AddNewObject pasteObj
'   pasteObj.Paste strLines
'   gfProjectExplorer.AddNewControl pasteObj, frm
'   Set fPalmScreen = frmMain.GetMDIChild(frm.GlobalID)
'   If Not fPalmScreen Is Nothing Then
'      fPalmScreen.AddUIObject pasteObj
'   End If
''   pasteObj.drawDesignLayout
''   frm.ObjectCollection.Add pasteObj
'   If UBound(strLines) > 1 Then
'      PasteObject strLines, frm
'   Else
''      RebuildProjectExplorer
'      Set PasteObject = pasteObj
'   End If
'End Function

Public Function ImgNum(iml As ImageList, strKey As String) As Long
   ImgNum = iml.ListImages(strKey).index - 1
End Function

Function trimWhiteSpace(ByVal s As String, Optional direction As Integer = 2) As String
   Dim ws As String

   'When trimming off whitespace...
   ' Direction = 0 for left only
   ' Direction = 1 for right only
   ' Direction = 2 for left and right
   ws = " " & vbCr & vbLf & vbTab
   If direction = 0 Or direction = 2 Then
      'Trim leading whitespace
      Do While InStr(1, ws, Left(s, 1)) > 0 And Len(s) > 0
         s = Mid(s, 2)
      Loop
   End If
   
   If direction = 1 Or direction = 2 Then
      'Trim trailing whitespace
      Do While InStr(1, ws, Right(s, 1)) > 0 And Len(s) > 0
         s = Left(s, Len(s) - 1)
      Loop
   End If
   trimWhiteSpace = s
End Function

Public Sub SaveImages(p1 As String, p2 As String, p3 As String, p4 As String, p5 As String, p1h As String, p2h As String, p3h As String, p4h As String, p5h As String)
Dim paths(9) As String
   
   If (p2 = "") And (p3 = "") And (p4 = "") And (p5 = "") And (p1h = "") And (p2h = "") And (p3h = "") And (p4h = "") And (p5h = "") Then
      Write #1, GetRelativePath(gTarget.pathname, p1)
   Else
      paths(0) = GetRelativePath(gTarget.pathname, p1)
      paths(1) = GetRelativePath(gTarget.pathname, p2)
      paths(2) = GetRelativePath(gTarget.pathname, p3)
      paths(3) = GetRelativePath(gTarget.pathname, p4)
      paths(4) = GetRelativePath(gTarget.pathname, p5)
      paths(5) = GetRelativePath(gTarget.pathname, p1h)
      paths(6) = GetRelativePath(gTarget.pathname, p2h)
      paths(7) = GetRelativePath(gTarget.pathname, p3h)
      paths(8) = GetRelativePath(gTarget.pathname, p4h)
      paths(9) = GetRelativePath(gTarget.pathname, p5h)
      Write #1, Join(paths, ",")
   End If
End Sub

Public Sub RestoreImages(ByRef p1 As String, ByRef p2 As String, ByRef p3 As String, ByRef p4 As String, ByRef p5 As String, ByRef p1h As String, ByRef p2h As String, ByRef p3h As String, ByRef p4h As String, ByRef p5h As String)
Dim paths() As String
Dim s As String

   Input #1, s
   paths = Split(s, ",")
   If UBound(paths) = 0 Then p1 = paths(0) Else p1 = ""
   If UBound(paths) > 0 Then  '07/19/01 gh
      p1 = paths(0)           '07/19/01 gh
      p2 = paths(1)           '07/19/01 gh
   Else                       '07/19/01 gh
      p2 = ""                 '07/19/01 gh
   End If                     '07/19/01 gh
   If UBound(paths) > 1 Then p3 = paths(2) Else p3 = ""
   If UBound(paths) > 2 Then p4 = paths(3) Else p4 = ""
   If UBound(paths) > 3 Then p5 = paths(4) Else p5 = ""
   
   If UBound(paths) > 4 Then p1h = paths(5) Else p1h = ""
   If UBound(paths) > 5 Then p2h = paths(6) Else p2h = ""
   If UBound(paths) > 6 Then p3h = paths(7) Else p3h = ""
   If UBound(paths) > 7 Then p4h = paths(8) Else p4h = ""
   If UBound(paths) > 8 Then p5h = paths(9) Else p5h = ""
End Sub

Public Function ValidFileName(ByVal strText As String) As Boolean
Dim arrChar() As String
Dim i As Integer

   arrChar = Split(gStringTable(knInvalidChars))
   For i = 0 To UBound(arrChar)
      If InStr(strText, arrChar(i)) > 0 Then
         MsgBox gStringTable(knInvalidChars + 1), vbCritical + vbOKOnly
         ValidFileName = False
         Exit Function
      End If
   Next
   ValidFileName = True
End Function

Public Function LegalObjectName(ByVal strText As String) As Boolean
Dim arrChar() As String
Dim str1 As String
Dim i As Integer

   arrChar = Split(gStringTable(1409), "a")
   For i = 0 To UBound(arrChar)
      If InStr(strText, arrChar(i)) > 0 Then
         MsgBox gStringTable(1410) & "'" & strText & "'", vbCritical + vbOKOnly
         LegalObjectName = False
         Exit Function
      End If
   Next
   str1 = Left(strText, 1)
   If str1 >= "a" And str1 <= "z" Or str1 >= "A" And str1 <= "Z" Then
      LegalObjectName = True
   Else
      MsgBox gStringTable(1410) & "'" & strText & "'", vbCritical + vbOKOnly
      LegalObjectName = False
   End If
End Function

Public Sub InvalidProperty()
   MsgBox gStringTable(1407), vbOKOnly + vbCritical
End Sub

Public Sub MenuEditor()
Dim fMenuEditor As New frmMenuEditor
Dim proj As CProject
Dim mnu As CMenu

   Set proj = ActiveProject
   If proj Is Nothing Then Exit Sub

   If proj.MenuCollection.count = 0 Then
      If Not proj.AddMenu Then Exit Sub
   End If

   fMenuEditor.Project = proj
   fMenuEditor.Show vbModal, frmMain
   gfProjectExplorer.UpdateProjectMenus proj
End Sub
Public Sub ThemeEditor()
Dim fThemeEditor As New frmThemeEditor

   fThemeEditor.Show vbModal, frmMain
 End Sub

Public Function ActiveProject() As CProject
   If Not frmMain.ActiveForm Is Nothing Then Set ActiveProject = LocateProject(frmMain.ActiveForm.GlobalID)
   If ActiveProject Is Nothing Then Set ActiveProject = gTarget
End Function

Public Function GetTextWidth(ByVal strText As String, Optional nFontIndex As Integer = 0, Optional nMagFactor As Integer = 1) As Integer
Dim factor As Double

   frmMain.picBox.fontname = gstrPalmFonts(nFontIndex)
   frmMain.picBox.fontSize = gnPalmFontSize(nFontIndex)
   factor = gnPalmFontSize(nFontIndex) / frmMain.picBox.fontSize
'   GetTextWidth = (frmMain.picBox.TextWidth(strText) \ 15) * nMagFactor
   GetTextWidth = (frmMain.picBox.TextWidth(strText) \ 15) * factor * nMagFactor
'   MsgBox "Text: '" & strText & "'" & vbCrLf _
'         & "Font Index: " & nFontIndex & vbCrLf _
'         & "Font: " & frmMain.picBox.fontSize & "-pt " & frmMain.picBox.fontName & vbCrLf _
'         & "Text Width: " & GetTextWidth
End Function

Public Function GetTextHeight(ByVal strText As String, Optional nFontIndex As Integer = 0, Optional nMagFactor As Integer = 1) As Integer
Dim factor As Double

   On Error GoTo err_GetTextHeight

   frmMain.picBox.fontname = gstrPalmFonts(nFontIndex)
   frmMain.picBox.fontSize = gnPalmFontSize(nFontIndex)
   factor = gnPalmFontSize(nFontIndex) / frmMain.picBox.fontSize
   GetTextHeight = (frmMain.picBox.TextHeight(strText) \ 15) * factor * nMagFactor
   Exit Function
   
err_GetTextHeight:
   GetTextHeight = 11
End Function

Public Function GetScript(ByVal strMixed As String, Optional ByVal strScript As String) As String
Dim obj As Object

   If strScript = "" Then strScript = Mid(strMixed, InStrRev(strMixed, "|") + 1)
   Set obj = LocateObject(strMixed)
   If Left(strMixed, Len("object")) = "object" Then
      GetScript = obj.obj.GetScript(strScript, False)
   Else
      GetScript = obj.GetScript(strScript, False)
   End If
End Function

Public Sub PutScript(ByVal strCode As String, ByVal strGID As String)
Dim obj As Object

   Set obj = LocateObject(strGID)
   If obj Is Nothing Then Exit Sub
   If Left(strGID, Len("object")) = "object" Then
      obj.obj.PutScript strCode, Mid(strGID, InStrRev(strGID, "|") + 1)
   Else
      obj.PutScript strCode, Mid(strGID, InStrRev(strGID, "|") + 1)
   End If
End Sub

'Const kIntrinsics = "Bitmap Button CheckBox Field Gadget GraffitiShiftIndicator Grid Label List Popup PushButton Repeater Scrollbar Selector"
Public Function CreateObjectEx(ByRef astrType As String) As Object
Dim locobj As Object

   Select Case astrType
   Case "bmp": Set CreateObjectEx = New CUIBitmap
   Case "but": Set CreateObjectEx = New CUIButton
   Case "chk": Set CreateObjectEx = New CUICheckbox
   Case "fld": Set CreateObjectEx = New CUIField
   Case "gad": Set CreateObjectEx = New CUIGadget
   Case "shf": Set CreateObjectEx = New CUIGraffitiShiftIndicator
   Case "grd": Set CreateObjectEx = New CUIGrid
   Case "lbl": Set CreateObjectEx = New CUILabel
   Case "lst": Set CreateObjectEx = New CUIList
   Case "pop": Set CreateObjectEx = New CUIPopup
   Case "cho": Set CreateObjectEx = New CUIPushbutton
   Case "rpt": Set CreateObjectEx = New CUIRepeater
   Case "scr": Set CreateObjectEx = New CUIScrollbar
   Case "sel": Set CreateObjectEx = New CUISelector
   Case "sli": Set CreateObjectEx = New CUISlider
   Case "frm": Set CreateObjectEx = New CForm
   End Select
End Function

Public Function GetObjectType(astrName As String) As String
   GetObjectType = gTarget.GetObjectType(astrName)
End Function

Function ElapsedTime(tStart As Variant, tStop As Variant) As _
String
' **************************************************************
' Function Name : ElapsedTime          *
' Created By    : Herry Hariry Amin    *
' Email         : h2arr@cbn.net.id     *
' Language      : VB4, VB5, VB6        *
' Example       : sYourVariable = ElapsedTime _
                  (tStartTime,tStopTime)
'Notes:         : Times passed to this function should be
'               : in valid format (e.g., hh:mm.ss).  Otherwise,
'               : function will return 0:00:00
                
' ****************************************************************
On Error GoTo END_ELAPSEDTIME

Dim dtr, dtl, jml As Long

dtl = (Hour(tStart) * 3600) + (Minute(tStart) * 60) + (Second(tStart))
dtr = (Hour(tStop) * 3600) + (Minute(tStop) * 60) + (Second(tStop))

    If tStop < tStart Then
       jml = 86400
    Else
       jml = 0
    End If
    jml = jml + (dtr - dtl)
    
ElapsedTime = Format(str(Int((Int((jml / 3600)) Mod 24))), "00") + ":" + Format(str(Int((Int((jml / 60)) Mod 60))), "00") + ":" + Format(str(Int((jml Mod 60))), "00")

END_ELAPSEDTIME:
     
End Function
Public Function swapRGB(color As Long) As Long
   'Palm is BGR, Windows is RGB. Need to swap B and R. (Big Endian vs. Little Endian)
   Dim s As String
   s = Hex(&H1000000 + color)
   swapRGB = CLng("&h" & Mid(s, 6, 2) & Mid(s, 4, 2) & Mid(s, 2, 2))
End Function
Public Function getUIColorTable(x) As Long
   Dim themeColors() As Long

   themeColors = getThemeColors(gsTheme)
   getUIColorTable = swapRGB(themeColors(x))
   
End Function
Public Function getThemeColors(filename) As Long()
   Dim themeColors(31) As Long
   Dim i As Integer
   Dim b1 As String
   Dim b2 As String
   Dim b3 As String
   Dim err As Integer
   Dim themeResource(213) As Byte
   Dim FileNumber As Integer
   Dim trace As Boolean
   trace = True
   
   If trace Then MsgBox "getThemeColors 1" & filename
   FileNumber = FreeFile
   If filename = "" Then GoTo themeNotFound
   
   If trace Then MsgBox "getThemeColors 2" & GetAbsolutePath(filename, "")
   If trace Then MsgBox "getThemeColors filedirectory=" & fileDirectory
   On Error GoTo themeNotFound
   Open GetAbsolutePath(filename, "") For Input As #FileNumber
   On Error GoTo 0
   Close #FileNumber
   
   Open GetAbsolutePath(filename, "") For Binary Access Read As #FileNumber
   Get #FileNumber, 89, themeResource
   Close #FileNumber
   
   If trace Then MsgBox "getThemeColors 3" & filename
   For i = 1 To 30
      b1 = themeResource(i * 4 + 1)
      b2 = themeResource(i * 4 + 2)
      b3 = themeResource(i * 4 + 3)
      If b1 = 0 Then b1 = 1
      If b2 = 0 Then b2 = 1
      If b3 = 0 Then b3 = 1
      themeColors(i - 1) = RGB(b3, b2, b1)
   Next
   getThemeColors = themeColors
   Exit Function
themeNotFound:
   If trace Then MsgBox "getThemeColors 4" & filename
   #If NSBSymbian = 1 Then
      getThemeColors = getThemeColors(fileDirectory & "\themes\Symbian.pdb")
   #Else
      getThemeColors = getThemeColors(fileDirectory & "\themes\Classic.pdb")
   #End If
End Function
Public Function ResIn(IdNo As Integer, p1 As String, p2 As String, p4 As String, p8 As String, p16 As String, p1h As String, p2h As String, p4h As String, p8h As String, p16h As String) As Double
Dim resource As String
Dim command As String
Dim files As String
Dim q As String
Dim res As Double
   
   q = Chr(34)
   files = ""
   If p1 <> "" Then files = files & q & GetAbsolutePath(p1, "") & ":1" & q & " "
   If p2 <> "" Then files = files & q & GetAbsolutePath(p2, "") & ":2" & q & " "
   If p4 <> "" Then files = files & q & GetAbsolutePath(p4, "") & ":4" & q & " "
   If p8 <> "" Then files = files & q & GetAbsolutePath(p8, "") & ":8" & q & " "
   If p16 <> "" Then files = files & q & GetAbsolutePath(p16, "") & ":16" & q & " "
   If p1h <> "" Then files = files & q & GetAbsolutePath(p1h, "") & ":1d" & q & " "
   If p2h <> "" Then files = files & q & GetAbsolutePath(p2h, "") & ":2d" & q & " "
   If p4h <> "" Then files = files & q & GetAbsolutePath(p4h, "") & ":4d" & q & " "
   If p8h <> "" Then files = files & q & GetAbsolutePath(p8h, "") & ":8d" & q & " "
   If p16h <> "" Then files = files & q & GetAbsolutePath(p16h, "") & ":16d" & q & " "
   If files = "" Then Exit Function

   command = q & fileDirectory & "\tools\resin.exe" & q & " " & files
   If IdNo = 1000 Then
      resource = "tAIB 1000"
   ElseIf IdNo = 1001 Then
      resource = "tAIB 1001"
   Else
      resource = "Tbmp " & str(IdNo)
   End If
   command = command & " " & q & DownloadPath & gTarget.Name & ".prc" & q & " " & resource
   ResIn = ExecCmd(command)
End Function
