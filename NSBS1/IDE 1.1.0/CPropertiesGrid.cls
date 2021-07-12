VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CPropertiesGrid"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private WithEvents mGrid As MSFlexGrid
Attribute mGrid.VB_VarHelpID = -1
Private WithEvents mMask As VB.Label
Attribute mMask.VB_VarHelpID = -1
Private WithEvents mEdit As VB.TextBox
Attribute mEdit.VB_VarHelpID = -1
Private WithEvents mList As VB.TextBox
Attribute mList.VB_VarHelpID = -1
Private WithEvents mButton As VB.CheckBox
Attribute mButton.VB_VarHelpID = -1
Private WithEvents mListProp As VB.ListBox
Attribute mListProp.VB_VarHelpID = -1
Private WithEvents mEllipsis As VB.CommandButton
Attribute mEllipsis.VB_VarHelpID = -1
Private mForm As frmProperties

Private Declare Function GetWindowLong Lib "USER32" Alias "GetWindowLongW" (ByVal hWnd As Long, ByVal nIndex As Long) As Long
Private Declare Function GetSystemMetrics Lib "USER32" (ByVal nIndex As Long) As Long
Private Const SM_CXVSCROLL = 2
Private Const WS_VSCROLL = &H200000

Private Enum enCols
   enProp = 0
   enVal
   enType
   enData
End Enum

Public Enum enPropType
   pgReadOnly = 0
   pgString
   pgBoolean
   pgList
   pgNumlist
   pgOther
   pgStringList
   pgColor
   pgFont
End Enum

Private m_nRows As Integer
Private curRow As Integer
Private bLockCol As Boolean
Private sTrue As String, sFalse As String
Private m_bList As Boolean

Public Sub Init(objGrid As MSFlexGrid, objMask As VB.Label, objEdit As VB.TextBox, _
      objList As VB.TextBox, objButton As VB.CheckBox, objListProp As VB.ListBox, _
      objEllipsis As VB.CommandButton, objForm As Object)
Dim bool As Boolean

   sTrue = True
   sFalse = False
   m_nRows = 0
   curRow = m_nRows - 1

   Set mGrid = objGrid
   Set mMask = objMask
   Set mEdit = objEdit
   Set mList = objList
   Set mButton = objButton
   Set mListProp = objListProp
   Set mEllipsis = objEllipsis
   Set mForm = objForm

   'Init grid object
   With mGrid
      .ColAlignment(enProp) = 0
      .ColAlignment(enVal) = 0
      .ColWidth(enType) = 0
      .ColWidth(enData) = 0
      .RowHeight(0) = 0
   End With

   'Label font
   If gbPlainText Then mEdit.fontname = gLabelFontName
   mEdit.font.Charset = gLabelCharset

   HideEditors
End Sub

Public Sub Resize()
   With mGrid
      .Left = 0
      .Top = 0
      .Width = IIf(mForm.Width - 100 < 200, 200, mForm.Width - 100)
      .Height = IIf(mForm.Height - 400 < 200, 200, mForm.Height - 400)
      If .Width > 2600 Then
         .ColWidth(enProp) = 1300
         .ColWidth(enVal) = .Width - 1300
      Else
         .ColWidth(enProp) = .Width \ 2
         .ColWidth(enVal) = .ColWidth(enProp)
      End If
   End With
   If mEdit.Visible Then SetEdit
   If m_bList Then SetList
'   mGrid_Click
End Sub

Public Sub HideEditors()
'   mGrid.SetFocus
   mMask.Visible = False
   mEdit_LostFocus
   mEdit.Visible = False
   mList.Visible = False
   mButton.Visible = False
   mButton.Value = 0
   mListProp.Visible = False
   mEllipsis.Visible = False
   m_bList = False
   mEdit.Tag = ""
End Sub

Private Sub LocateEdit()
   If mGrid.row = 0 Or mGrid.col = 0 Then Exit Sub
   With mMask
      .Width = mGrid.CellWidth - ScrollBarWidth - 75 - 15
      .Height = mGrid.CellHeight
      .Top = mGrid.CellTop + mGrid.Top ' + 280         '+ 10
      .Left = mGrid.CellLeft + mGrid.Left ' + 45
   End With
   With mEdit
      .Width = mMask.Width - 45
      .Height = mMask.Height - 15
      .Left = mMask.Left + 45
      .Top = mMask.Top + 15
      .Enabled = True
   End With
End Sub

Public Sub SetEdit()
   bLockCol = True
   mGrid.col = 1
   HideEditors
   LocateEdit
   mForm.Refresh

   With mMask
      .Visible = True
      .ZOrder
   End With
   With mEdit
      .Text = mGrid.Text
      .SelStart = Len(.Text)
      .SelLength = Len(.Text)
      .Tag = mGrid.row
      .Visible = True
      .ZOrder
   End With

'   curRow = mGrid.Row
   mGrid.col = 0
   bLockCol = False
End Sub

Public Sub SetList()
Dim strItems() As String, strItem As Variant

   HideEditors
   SetEdit
   If GetType <> pgList Then mEdit.Visible = False

   With mButton
      .Left = mGrid.Left + mGrid.Width - ScrollBarWidth - mGrid.CellHeight - 45
      .Top = mEdit.Top - 15
      .Width = mGrid.CellHeight
      .Height = mGrid.CellHeight
      .Tag = mGrid.row
      .Visible = True
      .ZOrder
   End With

   mListProp.Clear
   mListProp.Height = 0
   strItems = Split(GetData, ">")
   For Each strItem In strItems
      mListProp.AddItem strItem
   Next
   mListProp.Tag = GetType
   m_bList = True
End Sub

Public Sub SetEllipsis()
   HideEditors
   SetEdit
   'Hide edit when user can't type directly into field
'   mEdit.Visible = False

   With mEllipsis
      .Width = 300
      .Left = mGrid.Left + mGrid.Width - ScrollBarWidth - .Width - 45
      .Top = mEdit.Top - 15
      .Height = mGrid.CellHeight
      .Visible = True
      .ZOrder
      .Tag = GetData
   End With
End Sub

Private Sub mButton_Click()
'   If mButton.Value = 1 Then mButton.Value = 0
   If mButton.Value = 0 Then
      mListProp.Visible = False
      mEdit.Visible = False
      Exit Sub
   End If
   bLockCol = True
   mGrid.col = 1
'  If iShowProp = 0 Then 'Show Color
'     mfraColor.Top = mGrid.Top + mGrid.CellTop + mGrid.CellHeight
'     mfraColor.Left = (mGrid.Width + mGrid.Left) - mfraColor.Width - ScrollBarWidth
'     mfraColor.Visible = True
'  ElseIf iShowProp = 1 Then 'Show List
'
   With mListProp
      .Move mGrid.CellLeft + mGrid.Left, _
         mGrid.Top + mGrid.CellTop + mGrid.CellHeight, _
         mGrid.CellWidth - ScrollBarWidth - 90, _
         0
      .Height = (.fontSize * 30) * .ListCount
      If .Top + .Height > mGrid.Height Then
         .Height = mGrid.Height - .Top
      End If
      .Visible = True
      .ZOrder
      .SetFocus
   End With
   bLockCol = False
   mGrid.col = 0
   
'  End If
End Sub

'Private Sub mEdit_Change()
'   If mGrid.row > -1 Then
'      mGrid.TextMatrix(mGrid.row, 1) = mEdit.Text
'   End If
''Static bSet As Boolean
''If bSet Then Exit Sub
''bSet = True
''      UpdateValue medit.tag, mEdit.Text
''      If mEdit.Text <> GetVal Then
''         mEdit.Text = GetVal
''         mEdit.selStart = 0
''         mEdit.ZOrder
''         mEdit.SetFocus
''      End If
''bSet = False
'End Sub

Private Sub mEdit_Click()
   mButton.Visible = False
End Sub

Private Sub mEdit_KeyPress(KeyAscii As Integer)
   'If enter is pressed, update.
   If KeyAscii = 13 Then
      UpdateValue mEdit.Tag, mEdit.Text
      mEdit.Text = GetVal
   End If
End Sub

Private Sub mEdit_KeyDown(KeyCode As Integer, Shift As Integer)
    Dim prevValue As String
    If KeyCode = vbKeyReturn Then
      On Error Resume Next
      mButton.Visible = False
      If mEdit.Visible = True Then
         prevValue = Trim(mGrid.Text)
         mGrid.SetFocus
      End If
    End If
    mButton.Visible = False
End Sub

Private Sub mEdit_LostFocus()
Dim prevValue As String
    
   mButton.Visible = False
   If Not mEdit.Enabled Then Exit Sub
   
   If mEdit.Tag = "" Then Exit Sub
   UpdateValue mEdit.Tag, mEdit.Text
   mEdit.Text = GetVal(mEdit.Tag)
       
End Sub

Private Sub mEllipsis_Click()
Dim strData() As String
Dim filename As String
Dim fontname As String
Dim oleNewColor As OLE_COLOR
Dim obj As Object
Dim fTextEditDlg As New frmTextEditDlg
Dim sFile() As String
Dim trace As Boolean
sFile = Split(gStringTable(2200), ">") 'get "File"
trace = True

   If mEllipsis.Tag = "" Then mEllipsis.Tag = "Resource" 'this is definitely the wrong fix for the bug
   strData = Split(mEllipsis.Tag, ">")
   If trace Then MsgBox "mEllipsis_Click 1 " & strData(0)
   Select Case strData(0)
   Case sFile(0), "File" 'File
      If trace Then MsgBox "mEllipsis_Click 2"
      frmMain.dlgCommonDialog.DialogTitle = strData(1)
      If InStr(strData(1), "Theme") Then
         frmMain.dlgCommonDialog.InitDir = fileDirectory + "\themes"
         frmPalmScreen.ClearSelection (False) 'works together with "Perhaps inelegant" below.
      If trace Then MsgBox "mEllipsis_Click 3" & fileDirectory + "\themes"
      End If
      If InStr(strData(1), "Load Image") Then
         frmMain.dlgCommonDialog.InitDir = fileDirectory + "\bitmaps"
      End If
      If InStr(strData(1), "License") Then
         frmMain.dlgCommonDialog.InitDir = fileDirectory
      End If
      frmMain.dlgCommonDialog.Filter = strData(2)
      frmMain.dlgCommonDialog.DefaultExt = strData(3)
      frmMain.dlgCommonDialog.flags = cdlOFNNoChangeDir
      frmMain.dlgCommonDialog.CancelError = True
      frmMain.dlgCommonDialog.filename = strData(4)
      If trace Then MsgBox "mEllipsis_Click 4"
      On Error GoTo gotCancel
      frmMain.dlgCommonDialog.ShowOpen
      On Error GoTo 0
      If trace Then MsgBox "mEllipsis_Click 5"
      filename = frmMain.dlgCommonDialog.filename
      mEdit.Text = filename
      'This next line allows the display refresh properly. Perhaps inelegant...
      'If InStr(strData(1), "Theme") Then MsgBox gStringTable(3535) & filename 'Theme changed to
      UpdateValue mEdit.Tag, filename
   Case "bitmap"
      mEllipsisBitmapAction
   Case "Resource"
      mEllipsisResourceAction
   Case "List Items"
      fTextEditDlg.caption = strData(0)
      fTextEditDlg.Text = Mid(mEllipsis.Tag, Len(strData(0)) + 2)
      fTextEditDlg.Show vbModal, frmMain
      If Not fTextEditDlg.Cancelled Then
         UpdateValue mEdit.Tag, fTextEditDlg.Text
         mEdit.Text = GetVal(mEdit.Tag)
         mEllipsis.Tag = mForm.Object.GetStringList
      End If
   Case "Modal Tips"
      fTextEditDlg.caption = strData(0)
      fTextEditDlg.Text = Mid(mEllipsis.Tag, Len(strData(0)) + 2)
      fTextEditDlg.Show vbModal, frmMain
      If Not fTextEditDlg.Cancelled Then
         UpdateValue mEdit.Tag, fTextEditDlg.Text
         mEdit.Text = GetVal(mEdit.Tag)
         mEllipsis.Tag = mForm.Object.GetStringList
      End If
   Case "Color"
      oleNewColor = ShowColorDialog(frmProperties.hWnd, True, Val("&h" & strData(1)))
      If oleNewColor >= 0 Then
         mEdit.Text = Hex(oleNewColor)
         UpdateValue mEdit.Tag, str(oleNewColor)
      End If
   Case "Font"
      frmMain.dlgCommonDialog.DialogTitle = strData(1)
      frmMain.dlgCommonDialog.CancelError = True
      frmMain.dlgCommonDialog.flags = cdlCFScreenFonts
      frmMain.dlgCommonDialog.fontname = GetVal(mEdit.Tag)
      On Error GoTo gotCancel
      frmMain.dlgCommonDialog.ShowFont
      On Error GoTo 0
      fontname = frmMain.dlgCommonDialog.fontname
      mEdit.Text = fontname
      UpdateValue mEdit.Tag, fontname
   Case Else
   End Select

gotCancel:
   If trace Then MsgBox "mEllipsis_Click 6"
   Set obj = mForm.Object
   DoEvents
   mForm.Object = obj
End Sub

Private Sub mGrid_Click()
Dim lStyle As Long
Dim ScrollWidth As Long

   If mGrid.row = curRow Then
      If mGrid.ColSel <> mGrid.col Then mGrid.ColSel = mGrid.col
      Exit Sub
   End If
   curRow = mGrid.row
'sgBox curRow
'   mGrid.SetFocus
   If mEdit.Visible Then mEdit_LostFocus
   mEdit.Visible = False
'   mForm.SetFocus

   If mGrid.row = -1 Or m_nRows < 1 Then Exit Sub
'   curRow = mGrid.Row
'   Call mForm.ShowDescription(ti.GetDescription(mGrid.TextMatrix(curRow, 0)))
'   If ShowColor Then
'      curRow = mGrid.Row
'      mEdit.Visible = False
'      Exit Sub
'   End If

   'SetEdit also sets mGrid.Col = 0, so check first
   Select Case GetType
   Case pgString
      SetEdit
   Case pgBoolean, pgList, pgNumlist
      SetList
   Case pgReadOnly
      HideEditors
   Case pgOther
      SetEllipsis
   Case pgStringList
      SetEllipsis
      mEdit.Enabled = False
   Case pgColor
      SetEllipsis
   Case pgFont
      SetEllipsis
   End Select
End Sub

Private Sub mGrid_DblClick()
   If m_nRows < 1 Then Exit Sub
   If GetType = pgReadOnly Then Exit Sub
'   With mEdit
'      .selStart = 0
'      .selLength = Len(mEdit.Text)
'      .SetFocus
'   End With
End Sub

Private Sub mGrid_EnterCell()
   If curRow <> mGrid.row Then
      mGrid_Click
   End If
   If Not bLockCol And mGrid.col <> 0 Then mGrid.col = 0
End Sub

Private Sub mGrid_KeyDown(KeyCode As Integer, Shift As Integer)
   If KeyCode = vbKeyReturn Then
      Call mGrid_DblClick
   End If
'   If KeyCode = vbKeyDelete Then
'      mGrid.Text = ""
'   End If
End Sub

Public Function ScrollBarWidth() As Long
Dim lStyle As Long

   'Check if scrollbar is showing
   lStyle = GetWindowLong(mGrid.hWnd, (-16))
   If (lStyle And WS_VSCROLL) > 0 Then
      ScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL) * Screen.TwipsPerPixelX
   Else
      ScrollBarWidth = 0
   End If
   'sgBox "lStyle: " & lStyle & vbCrLf _
         & "ScrollBarWidth: " & ScrollBarWidth & vbCrLf _
         & "SM_CXVSCROLL: " & SM_CXVSCROLL & vbCrLf _
         & "Screen.TwipsPerPixelX: " & Screen.TwipsPerPixelX
End Function

'This would be the function to manage scrolling, but things are acting funny
Private Sub mGrid_Scroll2()
   If mEdit.Visible Then SetEdit
   If m_bList Then SetList
End Sub







Private Sub mListProp_click()
   mListProp.Visible = False
   mButton.Value = 0
   If mListProp.ListIndex < 0 Then Exit Sub
   If GetType = pgNumlist Then
      UpdateValue mButton.Tag, Val(mListProp.List(mListProp.ListIndex))
      mEdit.Text = GetVal(mEdit.Tag)
'      mEdit.Text = Val(mListProp.List(mListProp.ListIndex))       '07/17/01 GH
   Else
      UpdateValue mButton.Tag, mListProp.List(mListProp.ListIndex)
      mEdit.Text = GetVal(mEdit.Tag)
'      mEdit.Text = mListProp.List(mListProp.ListIndex)            '07/17/01 GH
   End If
   SetList
End Sub

Public Sub AddItem(nType As Integer, ByVal strProp As String, ByVal strVal As String, Optional ByVal strData As String)
Static nCol1 As Integer

   If m_nRows = 0 Then nCol1 = 0
   mForm.font = mGrid.font
   If nType = pgBoolean Then strData = sTrue & ">" & sFalse
   If nType = pgReadOnly Then strProp = "[" & strProp & "]"
   'Add some space for padding
   If mForm.TextWidth(strProp & "  ") > nCol1 Then nCol1 = mForm.TextWidth(strProp & "  ")
   If nCol1 < mGrid.Width \ 2 Then
      mGrid.ColWidth(enProp) = nCol1
   Else
      mGrid.ColWidth(enProp) = mGrid.Width \ 2
   End If
   mGrid.ColWidth(enVal) = mGrid.Width - mGrid.ColWidth(enProp)
   mGrid.AddItem (strProp & vbTab & strVal & vbTab & nType & vbTab & strData), 1
   If gbPlainText Then
      mGrid.row = 1
      'Set column to lock so .col will stick
      bLockCol = True
      mGrid.col = enVal
      mGrid.CellFontName = gLabelFontName
      'Unlock column
      bLockCol = False
      mGrid.col = 0
   End If
   m_nRows = m_nRows + 1
   mGrid.Sort = flexSortGenericAscending
   HideEditors
End Sub

Private Function GetProp(Optional nRow As Integer = -1) As String
   If nRow < 0 Then nRow = mGrid.row
   GetProp = mGrid.TextMatrix(nRow, enProp)
   'Strip [] envelope for read-only properties
   If GetType(nRow) = pgReadOnly Then
      GetProp = Mid(GetProp, 2, Len(GetProp) - 2)
   End If
End Function

Private Function GetVal(Optional nRow As Integer = -1) As String
   If nRow < 0 Then nRow = mGrid.row
   GetVal = mGrid.TextMatrix(nRow, enVal)
End Function

Private Function GetType(Optional nRow As Integer = -1) As Integer
   If m_nRows < 1 Then Exit Function
   If nRow < 0 Then nRow = mGrid.row
   GetType = Val(mGrid.TextMatrix(nRow, enType))
End Function

Private Function GetData(Optional nRow As Integer = -1) As String
   If nRow < 0 Then nRow = mGrid.row
   GetData = mGrid.TextMatrix(nRow, enData)
End Function

Private Sub LetVal(ByVal strVal As String, Optional nRow As Integer = -1)
   If nRow < 0 Then nRow = mGrid.row
   mGrid.TextMatrix(nRow, enVal) = strVal
End Sub

Private Sub mEllipsisBitmapAction()
'Dim filedirectory As String 'temp
Dim filename As String

'   filedirectory = "c:\nsbasic" 'temp
   On Error GoTo gotCancel
   frmMain.dlgCommonDialog.DialogTitle = "Bitmap File to Add"
   frmMain.dlgCommonDialog.InitDir = fileDirectory + "\bitmaps"
   frmMain.dlgCommonDialog.DefaultExt = "bmp"
   frmMain.dlgCommonDialog.Filter = "Image Files (*.gif;*.jpg;*.bmp;*.ico;*.emf;*.wmf)|*.gif;*.jpg;*.bmp;*.ico;*.emf;*.wmf|All Files|*.*" '7/19/1 gh
   frmMain.dlgCommonDialog.filename = mGrid.TextMatrix(mGrid.row, enVal)
   If frmMain.dlgCommonDialog.filename = "(none)" Then frmMain.dlgCommonDialog.filename = ""
   frmMain.dlgCommonDialog.ShowOpen
   On Error GoTo 0
SetBitmapName:
   filename = frmMain.dlgCommonDialog.filename
   mGrid.TextMatrix(mGrid.row, enVal) = filename
   If filename = "" Then mGrid.TextMatrix(mGrid.row, enVal) = "(none)"
'   filedirectory = Left(fileName, InStrRev(fileName, "\"))
   
gotCancel:
   If frmMain.dlgCommonDialog.filename = "" Then
      If MsgBox(gStringTable(3266), vbYesNo + vbQuestion) = vbNo Then Exit Sub 'Do you want to remove this item?"
      GoTo SetBitmapName
   End If
End Sub
Private Sub mEllipsisResourceAction()
'Dim filedirectory As String 'temp
Dim filename As String

'   filedirectory = "c:\nsbasic" 'temp
   On Error GoTo gotCancel
   frmMain.dlgCommonDialog.DialogTitle = "Resource File to Add"
   frmMain.dlgCommonDialog.InitDir = fileDirectory + "\lib"
   frmMain.dlgCommonDialog.DefaultExt = "prc"
   frmMain.dlgCommonDialog.Filter = "Resource Files (*.prc;*.pdb)|*.prc;*.pdb|All Files|*.*" '7/19/1 gh
   frmMain.dlgCommonDialog.filename = mGrid.TextMatrix(mGrid.row, enVal)
   If frmMain.dlgCommonDialog.filename = "(none)" Then frmMain.dlgCommonDialog.filename = ""
   frmMain.dlgCommonDialog.ShowOpen
   On Error GoTo 0
SetResourceName:
   filename = frmMain.dlgCommonDialog.filename
   mGrid.TextMatrix(mGrid.row, enVal) = filename
   If filename = "" Then mGrid.TextMatrix(mGrid.row, enVal) = "(none)"
'   filedirectory = Left(fileName, InStrRev(fileName, "\"))
   
gotCancel:
   If frmMain.dlgCommonDialog.filename = "" Then
      If MsgBox(gStringTable(3266), vbYesNo + vbQuestion) = vbNo Then Exit Sub 'Do you want to remove this item?"
      GoTo SetResourceName
   End If
End Sub

Public Sub Clear()
   HideEditors
   mGrid.Rows = 1
   m_nRows = 0
   curRow = 0
End Sub

Private Sub UpdateValue(nRow As Integer, strVal As String)
Dim strOrig As String
Dim frm As Form

   strOrig = GetVal(nRow)
   If strOrig = strVal Then Exit Sub
   If mForm.Object.ValidateProperty(GetProp(nRow), strVal) Then
      LetVal mForm.Object.GetPropertyVal(GetProp(nRow)), nRow
      Select Case typename(mForm.Object)
      Case "CProject"
      Case "CForm"
         Set frm = frmMain.GetMDIChild(mForm.Object.GlobalID)
         If Not frm Is Nothing Then frm.UpdateScreen
         gfProjectExplorer.UpdateObjectNode mForm.Object, mForm.Object.GlobalID
      Case "CBitmapFile"
      Case "CResourceFile"
      Case "CCodeModule"
      Case "CMenu", "CMenuBar", "CMenuElem"
         gfProjectExplorer.UpdateObjectNode mForm.Object, mForm.Object.GlobalID
      Case Else
         mForm.Object.ScreenDraw
         gfProjectExplorer.UpdateObjectNode mForm.Object, mForm.Object.obj.GlobalID
      End Select
   End If
   UpdateAllValues
End Sub

Private Sub UpdateAllValues()
Dim i As Integer

   For i = 1 To m_nRows
      LetVal mForm.Object.GetPropertyVal(GetProp(i)), i
   Next
End Sub
