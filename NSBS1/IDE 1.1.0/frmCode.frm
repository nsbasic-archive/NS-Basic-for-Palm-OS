VERSION 5.00
Object = "{BCA00000-0F85-414C-A938-5526E9F1E56A}#4.0#0"; "cmax40.dll"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmCode 
   Caption         =   "Code Window"
   ClientHeight    =   5775
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   10800
   Icon            =   "frmCode.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   5775
   ScaleMode       =   0  'User
   ScaleWidth      =   10800
   Visible         =   0   'False
   Begin CodeMax4Ctl.CodeMax Editor 
      Height          =   5655
      Left            =   0
      OleObjectBlob   =   "frmCode.frx":038A
      TabIndex        =   0
      Top             =   120
      Width           =   10095
   End
   Begin MSComDlg.CommonDialog dialog 
      Left            =   10200
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DialogTitle     =   "Project Help"
      FileName        =   "*.prj"
      InitDir         =   "c:\"
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   10200
      Top             =   600
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   14
      ImageHeight     =   13
      MaskColor       =   65280
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   3
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmCode.frx":047A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmCode.frx":0574
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmCode.frx":066E
            Key             =   ""
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmCode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private bDirty As Boolean                    '02/02/2001 MMD
Private header As String                     '02/02/2001 MMD
Private subheader As String                  '02/02/2001 MMD
Private CodeIconMenu As New cIconMenu
Private m_object As Object
Private m_proj As CProject
Private rngCurrent As CodeMax4Ctl.range

Public IsUIObject As Boolean


Private Sub Editor_ContextMenu(ByVal x As Long, ByVal y As Long)
   Editor.CancelEvent
   PopupMenu frmMain.mnuRightEditCode
End Sub

Private Sub Editor_PropsChange()
   Editor.CancelEvent
   MNSBCodeMax_SavePrefs Editor
End Sub

Private Sub editor_SelChange()
Dim rng As CodeMax4Ctl.range

   If Editor.LineCount = 0 Then Exit Sub
   
   Set rng = Editor.GetSel(True)
   frmMain.UpdateToolbar
   ShowCursor rng.EndLineNo + 1, rng.EndColNo

   If rng.StartLineNo <> rngCurrent.StartLineNo Then
      On Error Resume Next
      Editor.SetDivider rngCurrent.StartLineNo, False
      On Error GoTo 0
      CloseBlock rngCurrent.StartLineNo
      SetNewDividers rngCurrent.StartLineNo
   End If
   Set rngCurrent = rng
'Debug.Print "SelChange"
End Sub

Private Sub Form_Activate()
   frmMain.ActiveFormChange 1
   SetAllDividers
'   LoadBreakpoints
End Sub


Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
   'Removed check for dirty, because it allows new modules to close without saving
'   If Dirty And typename(m_object) = "CCodeModule" Then
'   Dirty = StoreBreakpoints
   If typename(m_object) = "CCodeModule" Then
      Cancel = Not m_object.PutScript(Text, "code")
   End If
   If gbAtBreakPoint Then
      MsgBox gStringTable(3439) 'You cannot close code window in Debug Mode. Continue execution instead.
      Cancel = True
   End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
   If m_object Is Nothing Then Exit Sub
   If compileInProcess = False Then
      If check_code() = False Then Cancel = True
      PutTheCodeBack
   End If

'MMD:I don't like this code
   frmMain.RemoveMDIChild GlobalID
   frmMain.ActiveFormChange 0
End Sub

Function check_code() As Boolean 'check that there is no code before or after
   'Let's clean up a number of things here...
   ' 1. Clear leading white space
   ' 2. Clear trailing white space
   ' 3. Allow opening comments
   Dim temp, code, lines() As String
   Dim i As Integer

   check_code = False

   'Clean leading and trailing whitespace from code
   Editor.Text = (trimWhiteSpace(Editor.Text, 2))

   check_code = True
End Function

Sub PutTheCodeBack()
'   StoreBreakpoints
   If Not bDirty Then Exit Sub
   bDirty = False

   If IsUIObject Then
      m_object.obj.PutScript Editor.Text, Tag
      gfProjectExplorer.UpdateObjectNode m_object, m_object.obj.GlobalID
   Else
      m_object.PutScript Editor.Text, Tag
      gfProjectExplorer.UpdateObjectNode m_object, m_object.GlobalID
   End If
   SetCaption
   gTarget.Dirty = True

End Sub

Private Sub Form_Load()
'MsgBox "frmCode: Load"
'Dim winState As Integer

   IsUIObject = False
   bDirty = False
  
   'Custom Language
   MNSBCodeMax_SetLanguage Editor
   MNSBCodeMax_SetScriptPrefs Editor

   Set rngCurrent = Editor.GetSel(True)
   
   
End Sub

Sub SetCaption()
'Dim strTitle As String
Dim proj As CProject

   If IsUIObject Then
      Set proj = LocateProject(m_object.obj.GlobalID)
   Else
      Set proj = LocateProject(m_object.GlobalID)
   End If
   Select Case typename(m_object)
   Case "CMenuElem"
'      Me.caption = proj.Name & " - Menu " & Menu.Name & " [" & mnuBar.caption & " (" & mnu.caption & ")]"
      Me.caption = proj.Name & " - Menu Dropdown (" & m_object.caption & ")"
   Case "CProject"
      Select Case Me.Tag
      Case "startup": Me.caption = m_object.Name & " (Startup Code)"
      Case "termination": Me.caption = m_object.Name & " (Termination Code)"
      End Select
   Case "CCodeModule"
      Me.caption = "Module - " & m_object.fileName
   Case "CForm"
      Select Case Me.Tag
      Case "event": Me.caption = proj.Name & " - Form " & m_object.Name & " (Event Code)"
      Case "before": Me.caption = proj.Name & " - Form " & m_object.Name & " (Before Code)"
      Case "after": Me.caption = proj.Name & " - Form " & m_object.Name & " (After Code)"
      Case "help": Me.caption = proj.Name & " - Form " & m_object.Name & " (Help Code)"
      End Select
   Case Else
      Me.caption = proj.Name & " - Form " & m_object.obj.Form.Name & " (" & m_object.obj.Name & ")"
   End Select
'   Me.caption = "NS Basic/Palm - " & strTitle
End Sub

Private Sub Form_Resize()
'MMD: Yeah, this is broken again... ha ha ha
   If Me.WindowState = vbMinimized Then Exit Sub  '02/11/2001 MMD

   If Me.Height >= 360 Then
      Editor.Move 0, 0, Me.ScaleWidth, Me.ScaleHeight
   End If
End Sub

Public Sub SetSel(sel As CodeMax4Ctl.range)
   Editor.SetSel sel, True
End Sub

Public Function GetSel() As CodeMax4Ctl.range
   Set GetSel = Editor.GetSel(True)
End Function

Public Function SelText() As String
   SelText = Editor.SelText
End Function

Public Sub EditorSel(SelStart As Long, SelLength As Long)
Dim line As Integer
Dim p As Long
Dim SelRange As CodeMax4Ctl.range

   'convert character position in buffer to line, col
   Set SelRange = Editor.GetSel(True)
   line = 0
   p = 0
   Do While (p + Editor.GetLineLength(line)) < SelStart
      p = p + Editor.GetLineLength(line) + Len(vbCrLf)
      line = line + 1
      If line > Editor.LineCount Then Exit Sub
   Loop
   SelRange.StartLineNo = line
   SelRange.EndLineNo = line
   SelRange.StartColNo = SelStart - p
   SelRange.EndColNo = SelRange.StartColNo + SelLength
   Editor.SetSel SelRange, True
End Sub

Public Function SelStart()
Dim SelRange As CodeMax4Ctl.range
Dim p As Integer
Dim i As Integer

   Set SelRange = Editor.GetSel(True)
   p = SelRange.StartColNo
   For i = 0 To SelRange.StartLineNo - 1
      p = p + Editor.GetLineLength(i) + 2
   Next
   SelStart = p
End Function

Private Sub editor_Change()
   frmMain.UpdateToolbar
   bDirty = True
   m_proj.Dirty = True
End Sub

Private Sub editor_CmdFailure(ByVal Cmd As CodeMax4Ctl.cmCommand, ByVal lErrCode As CodeMax4Ctl.cmCommandErr)
   If lErrCode = cmErrNotFound Then Editor.CancelEvent
End Sub

Private Sub editor_RegisteredCmd(ByVal lCmd As CodeMax4Ctl.cmCommand)
   If lCmd = CM_NSB_EDITSELECTALL Then Editor.ExecuteCmd cmCmdSelectAll
End Sub

Public Property Let Text(ByRef vData As String)
   Editor.Text = vData
End Property

Public Property Get Text() As String
   Text = Editor.Text
End Property

Public Property Let Dirty(ByVal vData As Boolean)
   bDirty = vData
End Property

Public Property Get Dirty() As Boolean
   Dirty = bDirty
End Property

Public Property Let Object(ByVal obj As Object)
   Set m_object = obj
   If IsUIObject Then
      Set m_proj = LocateProject(obj.obj.GlobalID)
   Else
      Set m_proj = LocateProject(obj.GlobalID)
   End If
   SetCaption
End Property

Public Property Get Object() As Object
   Set Object = m_object
End Property

Public Property Get GlobalID() As String
   If m_object Is Nothing Then
      GlobalID = ""
   Else
      If IsUIObject Then
         GlobalID = m_object.obj.GlobalID & "|" & Me.Tag
      Else
         GlobalID = m_object.GlobalID & "|" & Me.Tag
      End If
   End If
End Property


Public Sub DisplaySelection()
   If gbProjectExplorer Then gfProjectExplorer.ShowActive m_object
   If gbProperties Then gfProperties.Object = m_object
End Sub

Public Sub GoToLine()
   Editor.ExecuteCmd cmCmdGotoLine, -1
End Sub

Public Sub Undo()
   Editor.ExecuteCmd cmCmdUndo, 0
End Sub

Public Sub Redo()
   Editor.ExecuteCmd cmCmdRedo, 0
End Sub

Public Sub Cut()
   Editor.ExecuteCmd cmCmdCut, 0
   SetAllDividers
End Sub

Public Sub Copy()
   Editor.ExecuteCmd cmCmdCopy, 0
End Sub

Public Sub Paste()
   Editor.ExecuteCmd cmCmdPaste, 0
   SetAllDividers
End Sub

Public Function ValidPaste() As Boolean
'   If ValidClipboard <> 0 Then Exit Function
   ValidPaste = Clipboard.GetFormat(vbCFText)
End Function

Public Sub Delete()
   Editor.ExecuteCmd cmCmdDelete, 0
   SetAllDividers
End Sub

Public Sub SelectAll()
   Editor.ExecuteCmd cmCmdSelectAll, 0
End Sub

Public Function ShowWhitespace() As Boolean
   ShowWhitespace = Not Editor.DisplayWhitespace
   Editor.ExecuteCmd IIf(ShowWhitespace, cmCmdWhitespaceDisplayOn, cmCmdWhitespaceDisplayOff), 0
End Function

Public Sub SetRepeatCount()
   Editor.ExecuteCmd cmCmdSetRepeatCount, 0
End Sub

Public Sub CommentSelection(bComment As Boolean)
   Editor.ExecuteCmd IIf(bComment, cmCmdCommentSelection, cmCmdUncommentSelection), 0
End Sub

Public Sub ExecuteCommand()
   Editor.ExecuteCmd cmCmdChooseCmd, 0
End Sub

Public Sub Save()
   PutTheCodeBack
End Sub


Public Function GetFindText() As String
   'If nothing is selected, use the last find string
   'If something is selected, use the selection or first line of what is selected, whichever is shortest
   If Editor.GetSel(True).IsEmpty Then
      GetFindText = gstrFind
   Else
      If InStr(Editor.SelText, vbCrLf) > 0 Then
         GetFindText = gstrFind
      Else
         GetFindText = Editor.SelText
      End If
   End If
End Function

Public Function FindNext() As Boolean
   FindNext = CMaxFindNext(Editor)
End Function

Public Function CanUndo() As Boolean
   CanUndo = Editor.CanUndo
End Function

Public Function CanRedo() As Boolean
   CanRedo = Editor.CanRedo
End Function

Public Function CanCut() As Boolean
   CanCut = Editor.CanCut
End Function

Public Function CanCopy() As Boolean
   CanCopy = Editor.CanCopy
End Function

Public Function CanPaste() As Boolean
   CanPaste = Editor.CanPaste
End Function

' QueryMemberList is called when CodeMax needs a memberlist to display.  The application receiving
' the notification should look at the current selection and set 'List' to a memberlist that is most
' appropriate for the context.  If no memberlist should appear, call CodeMax.CancelEvent() to prevent
' the list from appearing.  If 'List' is not set and CancelEvent() is not called, CodeMax will fall back
' to the value stored in CodeMax.MemberList, then fall back to the current scopes (innermost to outermost)
' memberlist (ITokenSet.MemberList), then fall back to ILanguage.MemberList.
Private Sub editor_QueryMemberList(ByVal Cmd As CodeMax4Ctl.cmCommand, List As CodeMax4Ctl.IMemberList)
Dim p As CodeMax4Ctl.ILineParser
Dim sel As CodeMax4Ctl.range
Dim strType As String
    
   Set p = Editor.CreateParser()
   Set sel = Editor.GetSel(True)
'    If sel.EndLineNo = 0 Then Exit Sub
   p.LineNo = sel.EndLineNo
   p.ColNoAfterToken = sel.EndColNo
    
   ' scan backward a few tokens to see if 'Err' is one of them
   If (p.TokenText = "") Then
      Call p.GetNextToken(cmParseDirBackward)
   End If
   If p.TokenText = "=" Then
      Exit Sub
   End If
   If (p.TokenText <> ".") Then
      Call p.GetNextToken(cmParseDirBackward)
   End If
   If (p.TokenText = "." And sel.EndColNo >= p.TokenEndColNo) Then
      Call p.GetNextToken(cmParseDirBackward)
      Select Case UCase(p.TokenText)
      Case "ERR"
         Set List = cmGlobals.MemberLists("Err Methods")
         Exit Sub
      Case "OUTPUT"
         Set List = cmGlobals.MemberLists("Output")
         Exit Sub
      Case Else
         strType = GetObjectType(p.TokenText)
         If strType <> "" And strType <> "frm" Then Set List = cmGlobals.MemberLists(strType)
         Exit Sub
      End Select
   End If
   
   Set List = cmGlobals.MemberLists("Global Methods")
End Sub

Sub SetAllDividers()
Dim i As Long
Dim nLastDivider As Long
Dim strLine As String

   ClearAllDividers
   For i = 0 To Editor.LineCount - 1
      strLine = LCase(Trim(Editor.GetLine(i)))
      If Left(strLine, 7) = "end sub" Or Left(strLine, 12) = "end function" Then
         Editor.SetDivider i, True
         nLastDivider = i
      End If
   Next
   ClearLastDivider nLastDivider
End Sub

Sub ClearAllDividers()
Dim i As Long

   For i = 0 To Editor.LineCount - 1
      Editor.SetDivider i, False
   Next
End Sub

Sub SetNewDividers(nStartLine As Long)
Dim i As Long
Dim nLastDivider As Long
Dim strLine As String

   For i = nStartLine To 0 Step -1
      strLine = LCase(Trim(Editor.GetLine(i)))
      If Left(strLine, 7) = "end sub" Or Left(strLine, 12) = "end function" Then
         Editor.SetDivider i, True
         nLastDivider = i
         Exit For
      End If
   Next
   For i = nStartLine + 1 To Editor.LineCount - 1
      strLine = LCase(Trim(Editor.GetLine(i)))
      If Left(strLine, 7) = "end sub" Or Left(strLine, 12) = "end function" Then
         Editor.SetDivider i, True
         nLastDivider = i
         Exit For
      End If
   Next
   ClearLastDivider nLastDivider
End Sub

Sub ClearLastDivider(nLastDivider As Long)
Dim i As Long

   i = nLastDivider + 1
   While i < Editor.LineCount
      If Len(Trim(Editor.GetLine(i))) > 0 Then Exit Sub
      i = i + 1
   Wend
   If Editor.LineCount > 0 Then
      Editor.SetDivider nLastDivider, False
   End If
End Sub

Sub CloseBlock(nStartLine As Long)
Dim i As Long
Dim strLine As String
Dim bFound As Boolean
Dim procType As String
Dim pos As New CodeMax4Ctl.position
Static bClosing As Boolean

   If bClosing Then Exit Sub
   bClosing = True
   bFound = False
   strLine = LCase(Trim(Editor.GetLine(nStartLine)))
   If Left(strLine, 4) = "sub " Or Left(strLine, 9) = "function " Then
      procType = Left(strLine, 1)
      For i = nStartLine + 1 To Editor.LineCount - 1
         strLine = LCase(Trim(Editor.GetLine(i)))
         If Left(strLine, 4) = "sub " Or Left(strLine, 9) = "function " Then Exit For
         If Left(strLine, 7) = "end sub" Or Left(strLine, 12) = "end function" Then
            bFound = True
            Exit For
         End If
      Next
      If Not bFound Then
         strLine = IIf(procType = "s", "End Sub", "End Function")
         pos.colNo = Editor.GetSel(True).StartColNo
         pos.LineNo = Editor.GetSel(True).StartLineNo
         Editor.InsertText vbCrLf & strLine & vbCrLf, pos
      End If
   End If
   bClosing = False
End Sub
Public Sub showEditorProperties()
   Editor.ExecuteCmd cmCmdProperties, 0
End Sub
