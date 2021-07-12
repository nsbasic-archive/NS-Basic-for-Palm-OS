VERSION 5.00
Begin VB.Form frmPalmScreen 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "<Project> - Form [<FormName> - <FormTitle>]"
   ClientHeight    =   6870
   ClientLeft      =   45
   ClientTop       =   300
   ClientWidth     =   5070
   Icon            =   "frmPalmScreen.frx":0000
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   458
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   338
   Begin VB.PictureBox picSS 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   1815
      Left            =   120
      Picture         =   "frmPalmScreen.frx":038A
      ScaleHeight     =   119
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   319
      TabIndex        =   2
      Top             =   4920
      Width           =   4815
   End
   Begin VB.PictureBox pbPalmScreen 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   4815
      Left            =   120
      ScaleHeight     =   319
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   319
      TabIndex        =   0
      Top             =   120
      Width           =   4815
      Begin VB.PictureBox pbTitle 
         Appearance      =   0  'Flat
         BackColor       =   &H00000000&
         BorderStyle     =   0  'None
         BeginProperty Font 
            Name            =   "Wingdings"
            Size            =   8.25
            Charset         =   2
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   375
         Left            =   0
         ScaleHeight     =   25
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   113
         TabIndex        =   1
         Top             =   0
         Width           =   1695
      End
   End
End
Attribute VB_Name = "frmPalmScreen"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const kScreenLeft = 5
Const kScreenTop = 5
'Const kScreenWidth = 160  'Now a global, based on gbDana
Const kScreenHeight = 160
Const kTitleHeight = 13
Const kTitleLineHeight = 2

Public Selection As New Collection
Private m_nMagFactor As Integer
Private m_bNewObject As Boolean
Private m_Form As CForm

Private Sub Form_Activate()
   frmMain.ActiveFormChange 1
End Sub

Private Sub Form_Click()
Dim ob As Object

   If Not gbWinNT2000 Then Exit Sub
   #If NSBSymbian = 0 Then
   m_nMagFactor = (m_nMagFactor * 2) Mod 3
   #End If
   With pbPalmScreen
      .Visible = False
      .Width = (m_Form.Width * m_nMagFactor) + 2
      .Height = (m_Form.Height * m_nMagFactor) + 2
      .Left = kScreenLeft + (m_Form.OriginLeft * m_nMagFactor)
      .Top = kScreenTop + (m_Form.OriginTop * m_nMagFactor)
      .fontSize = 8 * m_nMagFactor
      .Visible = True
   End With

   SetPicSS
   pbTitle.fontSize = 8 * m_nMagFactor
   pbTitle.Refresh
   For Each ob In m_Form.ObjectCollection
      ob.ScreenDraw
   Next
End Sub

Private Sub Form_Load()
   'Move offscreen
   Me.Left = -(Me.Width + 1)
   
   m_nMagFactor = 2
   With pbPalmScreen
      .Width = (kScreenWidth * m_nMagFactor) + 2
      .Height = (kScreenHeight * m_nMagFactor) + 2
      .Left = kScreenLeft
      .Top = kScreenTop
      If gbWinNT2000 Or gbPlainText Then
         .fontSize = 8 * m_nMagFactor
      Else
         .fontSize = 8
      End If
      .BackColor = getUIColorTable(22) 'UIFormFill
      .Visible = True
   End With
   
   SetPicSS
   With Me
      .Width = (2 * kScreenLeft + kScreenWidth * m_nMagFactor + 8) * Screen.TwipsPerPixelX
      .Height = (2 * kScreenTop + kScreenHeight * m_nMagFactor + picSS.Height + 34) * Screen.TwipsPerPixelY
   End With

   If gbPlainText Then
      pbTitle.font.Name = gLabelFontName
   Else
      pbTitle.font.Name = gstrPalmFonts(1)
   End If
   pbTitle.font.Charset = gLabelCharset
   pbTitle.BackColor = getUIColorTable(21)
   pbTitle.ForeColor = getUIColorTable(22)
   
   If gbWinNT2000 Or gbPlainText Then
      pbTitle.fontSize = 8 * m_nMagFactor
   Else
      pbTitle.fontSize = 8
   End If

   Me.fontname = gLabelFontName
   Me.fontSize = gLabelFontSize
   Me.font.Charset = gLabelCharset
   
End Sub

Public Property Let Object(theForm As CForm)
Dim obj As Object
   
   Set m_Form = theForm
   SetCaption
   Me.Tag = m_Form.GlobalID
   For Each obj In m_Form.ObjectCollection
      AddUIObject obj
   Next
End Property

Public Property Get Object() As CForm
   Set Object = m_Form
End Property

Function OrigX() As Integer
   OrigX = kScreenLeft
End Function

Function OrigY() As Integer
   OrigY = kScreenTop
End Function

Private Sub Form_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
   If frmMain.ActiveForm Is Me And Selection.count <> 1 Then ShowCoordinates -44, -44
End Sub

Private Sub Form_Resize()
   If WindowState = vbNormal Then
      If Me.Width <> (2 * kScreenLeft + picSS.Width + 8) * Screen.TwipsPerPixelX Then SetPicSS
   End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
Dim obj As Object
   If m_Form Is Nothing Then Exit Sub
   
   ClearSelection
   For Each obj In m_Form.ObjectCollection
      obj.obj.Control = Nothing
   Next
'MMD: I don't like this code
   frmMain.RemoveMDIChild Me.Tag
   frmMain.ActiveFormChange 0
End Sub

Public Function GlobalID() As String
   GlobalID = m_Form.GlobalID
End Function

Private Sub pbPalmScreen_Click()
   If m_bNewObject Then
      m_bNewObject = False
   Else
      If gnToolboxTool = 1 Then ClearSelection
   End If
End Sub

Private Sub pbPalmScreen_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
   If gnToolboxTool <> 1 Then
      pbPalmScreen.MousePointer = vbCrosshair
   Else
      pbPalmScreen.MousePointer = vbDefault
   End If
   If frmMain.ActiveForm Is Me And Selection.count = 0 Then ShowCoordinates x \ m_nMagFactor, y \ m_nMagFactor
End Sub

Private Sub pbPalmScreen_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim ob As Object

   'Do nothing if shift key down, no tool selected, or outside screen bounds
   If Shift <> 0 Then Exit Sub
   If Button = vbRightButton Then
      frmMain.RightClickMenu 1, m_Form.GlobalID
      Exit Sub
   End If

   If gnToolboxTool = 1 Then Exit Sub
   If x < 0 Or y < 0 Or x > pbPalmScreen.Width Or y > pbPalmScreen.Height Then Exit Sub

   'Create the proper object, and add it to the form and screen
   Select Case gnToolboxTool
   Case 2: Set ob = New CUIButton
   Case 3: Set ob = New CUIList
   Case 4: Set ob = New CUILabel
   Case 5: Set ob = New CUIField
   Case 6: Set ob = New CUIPushbutton
   Case 7: Set ob = New CUICheckbox
   Case 8: Set ob = New CUIPopup
   Case 9: Set ob = New CUISelector
   Case 10: Set ob = New CUIBitmap
   Case 11: Set ob = New CUIGadget
   Case 12: Set ob = New CUIRepeater
   Case 13: Set ob = New CUIScrollbar
   Case 14: Set ob = New CUIGraffitiShiftIndicator
   Case 15: Set ob = New CUIGrid
   Case 16: Set ob = New CUISlider
   End Select
   ob.obj.OrigLeft = x \ m_nMagFactor
   ob.obj.OrigTop = y \ m_nMagFactor
   ob.obj.Selected = True
   m_Form.AddNewObject ob
   AddUIObject ob

   'Add the object to project explorer and display in properties window
   If gbProjectExplorer Then gfProjectExplorer.AddNewControl ob, m_Form

   'Reset the toolbox tool
   gfToolbox.ToolboxSelect 1
   pbPalmScreen.MousePointer = vbDefault

   'Select the object
   DoEvents
   SetSelection ob
   m_bNewObject = True
End Sub

Private Sub pbPalmScreen_Paint()
Dim row As Integer
Dim col As Integer
Dim ob As Object

   If m_Form Is Nothing Then Exit Sub
   gsCurrentFormGlobalID = m_Form.GlobalID
   'First do the screen size
   With pbPalmScreen
      .Width = (m_Form.Width * m_nMagFactor) + 2
      .Height = (m_Form.Height * m_nMagFactor) + 2
      .Left = kScreenLeft + (m_Form.OriginLeft * m_nMagFactor)
      .Top = kScreenTop + (m_Form.OriginTop * m_nMagFactor)
      .BackColor = getUIColorTable(22) 'UIFormFill
   End With
   SetPicSS
   
   'First do the title
   If m_Form.OptTitle Then
      With pbTitle
         .Left = 0
         .Top = 0
         '.Width = pbTitle.TextWidth(m_Form.Title)
         .Height = kTitleHeight * m_nMagFactor
         .BackColor = getUIColorTable(21)
         .ForeColor = getUIColorTable(22)
         .Visible = True
         .Refresh
      End With
      'Draw the separator line
      pbPalmScreen.Line (0, kTitleHeight * m_nMagFactor)-(m_Form.Width * m_nMagFactor, (kTitleHeight + kTitleLineHeight) * m_nMagFactor), getUIColorTable(21), BF
   Else
      pbTitle.Visible = False
   End If

   'Now paint the grid
   If gbWantGrid Then
      With pbPalmScreen
         .DrawMode = vbCopyPen
         .DrawStyle = vbSolid
         .DrawWidth = 1

         For row = 0 To m_Form.Height * m_nMagFactor Step gnGridIncr * m_nMagFactor
            For col = 0 To m_Form.Width * m_nMagFactor Step gnGridIncr * m_nMagFactor
               pbPalmScreen.PSet (col, row), vbGrayText
            Next
         Next
      End With
   End If
   
   For Each ob In m_Form.ObjectCollection
      ob.ScreenDraw
   Next

End Sub

Private Sub pbTitle_Click()
   If gnToolboxTool = 1 Then ClearSelection
   DisplaySelection
End Sub

Private Sub pbTitle_DblClick()
Dim strTitle As String

   strTitle = InputBox(gStringTable(3262), , m_Form.Title) '"Enter new form title"
   If Len(strTitle) = 0 Then
      If MsgBox(gStringTable(3261), vbYesNo) = vbYes Then '"Do you want to hide the TitleBar?"
         m_Form.OptTitle = False
         pbPalmScreen.Refresh
         If gbProjectExplorer Then gfProjectExplorer.UpdateObjectNode m_Form, m_Form.GlobalID
         If gbProperties Then gfProperties.Object = Nothing
         DisplaySelection
'         MsgBox "This doesn't update the Properties Window"
         Exit Sub
      End If
      Exit Sub
   End If
   If m_Form.ValidateProperty("Title", strTitle) Then pbTitle.Refresh
   If gbProjectExplorer Then gfProjectExplorer.UpdateObjectNode m_Form, m_Form.GlobalID
   If gbProperties Then gfProperties.Object = Nothing
   DisplaySelection
End Sub

Private Sub pbTitle_Paint()
   If m_Form Is Nothing Then Exit Sub
   pbTitle.Cls
   If gbWinNT2000 Or gbPlainText Then
      pbTitle.Width = pbTitle.TextWidth(m_Form.Title) + 2 * m_nMagFactor
   Else
      pbTitle.Width = (pbTitle.TextWidth(m_Form.Title) + 2) * m_nMagFactor
   End If
   pbTitle.CurrentX = m_nMagFactor
   pbTitle.CurrentY = (pbTitle.Height - pbTitle.TextHeight(m_Form.Title)) \ 2
   pbTitle.Print m_Form.Title
End Sub

Public Sub AddUIObject(ByVal obj As Object)
   obj.obj.Control = Me.Controls.Add("VB.PictureBox", obj.obj.Name)
   If obj.obj.Kind = "bmp" Then
      addImageToBitmap (obj.obj)
      obj.obj.Control.Tag = "|||||||||"
   End If
   obj.obj.Control.Appearance = 0
   obj.obj.Control.BorderStyle = 0
   obj.obj.Control.ScaleMode = vbPixels
   obj.obj.Control.BackColor = vbWhite
   obj.obj.Control.Visible = True
   Set obj.obj.Control.Container = pbPalmScreen
End Sub

Public Sub RemoveUIObject(ByVal obj As Object)
Dim i As Integer

   For i = 0 To Me.Controls.count - 1
      If Me.Controls(i) Is obj.obj.Control Then
         RemoveSelectionItem obj
         Me.Controls.Remove i
         obj.obj.Control = Nothing
         Exit Sub
      End If
   Next
End Sub

Public Property Get MagFactor() As Integer
   MagFactor = m_nMagFactor
End Property

Public Property Let MagFactor(nMagFactor As Integer)
   m_nMagFactor = nMagFactor
   pbPalmScreen.Refresh
End Property

Public Sub ClearSelection(Optional bDisplaySelection As Boolean = True)
Dim fileName As String
Dim dirName As String

   While Selection.count > 0
      Selection(1).obj.Selected = False
      Selection(1).ScreenDraw
      
      If Selection(1).obj.Kind = "bmp" Then
         If Selection(1).ResourceId = Selection(1).obj.IdNo Then
            Set Selection(1).obj.Control.Picture = CaptureWindow(Selection(1).obj.Control.hWnd, True, 0, 0, Selection(1).obj.Control.Width, Selection(1).obj.Control.Height)
            dirName = fileDirectory & "\bitmaps\" & gTarget.Name
            If Dir(dirName, vbDirectory) = "" Then MkDir (dirName)
            fileName = dirName & "\" & Selection(1).obj.IdNo & ".bmp"
            SavePicture Selection(1).obj.Control.Picture, fileName
            'Debug.Print filename & " saved."
         End If
      End If
      
      Selection.Remove 1
   Wend
   
   If bDisplaySelection Then DisplaySelection
   ShowCoordinates -44, -44
   ShowDimensions -44, -44
      
End Sub

Public Sub AddSelectionItem(ByVal obj As Object)
   obj.obj.Selected = True
   obj.ScreenDraw
   Selection.Add obj, obj.obj.GlobalID
   DisplaySelection
End Sub

Public Sub SetSelection(ByVal obj As Object)
   ClearSelection False
   AddSelectionItem obj
End Sub

Public Sub RemoveSelectionItem(ByVal obj As Object)
   obj.obj.Selected = False
   obj.ScreenDraw
   Selection.Remove obj.obj.GlobalID
   DisplaySelection
End Sub

Public Sub DisplaySelection()
   Select Case Selection.count
   Case 0
      If gbProjectExplorer Then gfProjectExplorer.ShowActive m_Form
      If gbProperties Then gfProperties.Object = m_Form
      ShowCoordinates -44, -44
      ShowDimensions -44, -44
   Case 1
      If gbProjectExplorer Then gfProjectExplorer.ShowActive Selection(1)
      If gbProperties Then gfProperties.Object = Selection(1)
      ShowCoordinates Selection(1).obj.OrigLeft, Selection(1).obj.OrigTop
      ShowDimensions Selection(1).obj.Width, Selection(1).obj.Height
   Case Else
      If gbProjectExplorer Then gfProjectExplorer.ShowActive m_Form
      If gbProperties Then gfProperties.Object = Nothing
      ShowCoordinates -44, -44
      ShowDimensions -44, -44
   End Select
End Sub

Public Sub MouseMoveSelection(ByRef x As Integer, ByRef y As Integer, nLeft As Integer, nTop As Integer, Optional ByVal obj As Object = Nothing, Optional nForceGrid As Integer = 0)
Dim baseX As Integer, baseY As Integer
Dim bGridPref As Boolean

   'bGridPref allows temporary suspension/enforcement of grid
   bGridPref = gbWantGrid
   Select Case nForceGrid
   Case vbShiftMask: gbWantGrid = True
   Case vbCtrlMask: gbWantGrid = False
   End Select

   'Coordinate + delta gives proposed new coordinate
   'SnapToGrid finds nearest grid coordinate (GC) to proposed new coordinate
   'Subtracting current position from nearest GC determines how much we should move
   x = SnapToGrid(nLeft + x) - nLeft
   y = SnapToGrid(nTop + y) - nTop

   If obj Is Nothing Then
      For Each obj In Selection
         obj.obj.OrigLeft = obj.obj.OrigLeft + x
         obj.obj.OrigTop = obj.obj.OrigTop + y
         obj.ScreenDraw
      Next
   Else
      obj.obj.OrigLeft = obj.obj.OrigLeft + x
      obj.obj.OrigTop = obj.obj.OrigTop + y
   End If
   gbWantGrid = bGridPref
End Sub

Public Sub ResizeSelectionToGrid(Optional ByVal obj As Object = Nothing, Optional nForceGrid As Integer = 0)
Dim bGridPref As Boolean

   'bGridPref allows temporary suspension/enforcement of grid
   bGridPref = gbWantGrid
   Select Case nForceGrid
   Case vbShiftMask: gbWantGrid = True
   Case vbCtrlMask: gbWantGrid = False
   End Select

   If obj Is Nothing Then
      For Each obj In Selection
         MouseMoveSelection 0, 0, obj.obj.OrigLeft, obj.obj.OrigTop, obj
         obj.obj.Width = SnapToGrid(obj.obj.Width)
         obj.obj.Height = SnapToGrid(obj.obj.Height)
         obj.ScreenDraw
      Next
   Else
      MouseMoveSelection 0, 0, obj.obj.OrigLeft, obj.obj.OrigTop, obj
      obj.obj.Width = SnapToGrid(obj.obj.Width)
      obj.obj.Height = SnapToGrid(obj.obj.Height)
   End If
   gbWantGrid = bGridPref
End Sub

Public Sub Format(nType As Integer, nStyle As Integer)
Dim obj As Object
Dim i As Integer
Dim nMax As Integer, nMin As Integer, nSpc As Integer, nOff As Integer

   Select Case nType
   Case 0 'Align
      For Each obj In Selection
         Select Case nStyle
         Case 0 'Lefts
            obj.obj.OrigLeft = Selection(1).obj.OrigLeft
         Case 1 'Centers
            obj.obj.OrigLeft = Selection(1).obj.OrigLeft + (Selection(1).obj.Width - obj.obj.Width) \ 2
         Case 2 'Rights
            obj.obj.OrigLeft = (Selection(1).obj.OrigLeft + Selection(1).obj.Width) - obj.obj.Width
         Case 4 'Tops
            obj.obj.OrigTop = Selection(1).obj.OrigTop
         Case 5 'Middles
            obj.obj.OrigTop = Selection(1).obj.OrigTop + (Selection(1).obj.Height - obj.obj.Height) \ 2
         Case 6 'Bottoms
            obj.obj.OrigTop = (Selection(1).obj.OrigTop + Selection(1).obj.Height) - obj.obj.Height
         Case 8 'To Grid
            MouseMoveSelection 0, 0, obj.obj.OrigLeft, obj.obj.OrigTop, obj, vbShiftMask
         End Select
         obj.ScreenDraw
      Next
   Case 1 'Same Size
      For Each obj In Selection
         Select Case nStyle
         Case 0 'Width
            obj.obj.Width = Selection(1).obj.Width
         Case 1 'Height
            obj.obj.Height = Selection(1).obj.Height
         Case 2 'Both
            obj.obj.Width = Selection(1).obj.Width
            obj.obj.Height = Selection(1).obj.Height
         End Select
         obj.ScreenDraw
      Next
   Case 2 'Size To Grid
      For Each obj In Selection
         ResizeSelectionToGrid obj, vbShiftMask
         obj.ScreenDraw
      Next
   Case 3 'Horizontal Spacing
      'Only need to do this stuff for equal spacing
      If nStyle = 0 Then
         If Selection.count < 3 Then Exit Sub
   
         'Initialize Min/Max, and make first pass to determine values
         nMax = 0: nMin = Object.Width
         For Each obj In Selection
            If obj.obj.OrigLeft < nMin Then nMin = obj.obj.OrigLeft
            If obj.obj.OrigLeft > nMax Then nMax = obj.obj.OrigLeft
         Next
         nSpc = (nMax - nMin) \ (Selection.count - 1)
      End If

      'Cycle through selection and move objects accordingly
      For i = 1 To Selection.count
         Select Case nStyle
         Case 0 'Equal
            Selection(i).obj.OrigLeft = nMin + (i - 1) * nSpc
         Case 1 'Increase
            Selection(i).obj.OrigLeft = Selection(i).obj.OrigLeft + (i - 1) * (gnGridIncr \ 2)
         Case 2 'Decrease
            Selection(i).obj.OrigLeft = Selection(i).obj.OrigLeft - (i - 1) * (gnGridIncr \ 2)
         Case 3 'Remove
            If i > 1 Then Selection(i).obj.OrigLeft = Selection(i - 1).obj.OrigLeft + Selection(i - 1).obj.Width
         End Select
         Selection(i).ScreenDraw
      Next
   Case 4 'Vertical Spacing
      'Only need to do this stuff for equal spacing
      If nStyle = 0 Then
         If Selection.count < 3 Then Exit Sub
   
         'Initialize Min/Max, and make first pass to determine values
         nMax = 0: nMin = Object.Height
         For Each obj In Selection
            If obj.obj.OrigTop < nMin Then nMin = obj.obj.OrigTop
            If obj.obj.OrigTop > nMax Then nMax = obj.obj.OrigTop
         Next
         nSpc = (nMax - nMin) \ (Selection.count - 1)
      End If

      'Cycle through selection and move objects accordingly
      For i = 1 To Selection.count
         Select Case nStyle
         Case 0 'Equal
            Selection(i).obj.OrigTop = nMin + (i - 1) * nSpc
         Case 1 'Increase
            Selection(i).obj.OrigTop = Selection(i).obj.OrigTop + (i - 1) * (gnGridIncr \ 2)
         Case 2 'Decrease
            Selection(i).obj.OrigTop = Selection(i).obj.OrigTop - (i - 1) * (gnGridIncr \ 2)
         Case 3 'Remove
            If i > 1 Then Selection(i).obj.OrigTop = Selection(i - 1).obj.OrigTop + Selection(i - 1).obj.Height
         End Select
         Selection(i).ScreenDraw
      Next
   Case 5 'Center
      Select Case nStyle
      Case 0 'Horizontally
         'Initialize Min/Max, and make first pass to determine values
         nMax = 0: nMin = Object.Width
         For Each obj In Selection
            If obj.obj.OrigLeft < nMin Then nMin = obj.obj.OrigLeft
            If (obj.obj.OrigLeft + obj.obj.Width) > nMax Then nMax = (obj.obj.OrigLeft + obj.obj.Width)
         Next
         nOff = (Object.Width - (nMax - nMin)) \ 2

         For Each obj In Selection
            obj.obj.OrigLeft = (obj.obj.OrigLeft - nMin) + nOff
            obj.ScreenDraw
         Next
      Case 1 'Vertically
         'Initialize Min/Max, and make first pass to determine values
         nMax = 0: nMin = Object.Height
         For Each obj In Selection
            If obj.obj.OrigTop < nMin Then nMin = obj.obj.OrigTop
            If (obj.obj.OrigTop + obj.obj.Height) > nMax Then nMax = (obj.obj.OrigTop + obj.obj.Height)
         Next
         nOff = (Object.Height - (nMax - nMin)) \ 2

         For Each obj In Selection
            obj.obj.OrigTop = (obj.obj.OrigTop - nMin) + nOff
            obj.ScreenDraw
         Next
      End Select
   Case 6 'Order
      Select Case nStyle
      Case 0 'Front
      Case 1 'Forward
      Case 2 'Backward
      Case 3 'Back
      End Select
   End Select
   If gbProperties Then
      gfProperties.Object = Nothing
      DisplaySelection
   End If
End Sub

Private Sub picss_Paint()
   '1 pixel border on all sides accounts for factor of 2 below
   picSS.PaintPicture picSS.Picture, 0, 0, picSS.Width - 2, picSS.Height - 2
End Sub

Private Sub picSS_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
   If Button = vbLeftButton And Shift = 0 Then
      If x > (2 * m_nMagFactor) And x < (24 * m_nMagFactor) And y > (35 * m_nMagFactor) And y < (58 * m_nMagFactor) Then MenuEditor
   End If
End Sub

Public Sub SetCaption()
   Me.caption = m_Form.Project.Name & " - Form (" & m_Form.Name & ")"
End Sub

Public Sub UpdateScreen()
   pbPalmScreen.Refresh
   SetCaption
End Sub

Public Function SnapToGrid(nVal As Integer) As Integer
   If gbWantGrid Then
      SnapToGrid = ((nVal + gnGridIncr \ 2) \ gnGridIncr) * gnGridIncr
   Else
      SnapToGrid = nVal
   End If
End Function

Public Sub Save()
Dim frm As Form
Dim obj As Object

   'Save any open code windows that belong to this form
   Set frm = frmMain.GetMDIChild(m_Form.GlobalID & "|before")
   If Not frm Is Nothing Then frm.Save
   Set frm = frmMain.GetMDIChild(m_Form.GlobalID & "|after")
   If Not frm Is Nothing Then frm.Save
   Set frm = frmMain.GetMDIChild(m_Form.GlobalID & "|event")
   If Not frm Is Nothing Then frm.Save

   'Save any open code windows of objects from this form
   For Each obj In m_Form.ObjectCollection
      Set frm = frmMain.GetMDIChild(obj.obj.GlobalID & "|code")
      If Not frm Is Nothing Then frm.Save
   Next
End Sub

Public Sub Cut()
Dim obj As Object

   If Selection.count = 0 Then Exit Sub
   Copy
   Delete
End Sub

Public Sub Copy()
Dim strClip As String
Dim obj As Object

   If Selection.count = 0 Then
      strClip = m_Form.Copy
   Else
      For Each obj In Selection
         strClip = strClip & obj.Copy
      Next
   End If
   Clipboard.SetText kClipboardHeader & vbCrLf & strClip
End Sub

Public Function ValidPaste() As Boolean
   ValidPaste = (ValidClipboard = kClipboardObject)
End Function

Public Sub Paste()
Dim strLines() As String

   If ValidClipboard <> kClipboardObject Then Exit Sub
   strLines = Split(Clipboard.GetText, vbCrLf)
   m_Form.PasteObject strLines, False
End Sub

Public Sub Delete()
Dim obj As Object

   If Selection.count = 0 Then Exit Sub
   For Each obj In Selection
      FormRemoveObject m_Form, obj
   Next
End Sub

Public Sub SelectAll()
Dim obj As Object

   ClearSelection
   For Each obj In m_Form.ObjectCollection
      AddSelectionItem obj
   Next
End Sub

Public Property Get Dirty() As Boolean
   Dirty = False
End Property

Private Sub SetPicSS()
#If NSBSymbian Then
   picSS.Height = 0
   pbPalmScreen.Height = pbPalmScreen.Width
   picSS.Visible = False
#Else
   picSS.Left = kScreenLeft + ((m_Form.Width - 160) \ 2) * m_nMagFactor
   If m_Form.Height > kScreenHeight Then
      picSS.Top = kScreenLeft + m_Form.Height * m_nMagFactor + 1
   Else
      picSS.Top = kScreenTop + kScreenHeight * m_nMagFactor + 1
   End If
   picSS.Width = 160 * m_nMagFactor + 2
   picSS.Height = 59 * m_nMagFactor + 2
   picSS.Refresh
#End If
End Sub

Public Sub addImageToBitmap(obj)
   Dim fileName As String
   Dim HiRes As Boolean
   Dim res As CBitmapFile
   
   HiRes = False
   obj.Control.AutoSize = True
  
   'Get the resource for the bitmap object
   For Each res In gTarget.BitmapCollection
      If Val(obj.Label) = res.IdNo Then Exit For
   Next
   If res Is Nothing Then Exit Sub
   If Val(obj.Label) <> res.IdNo Then Exit Sub
   
   'Determine which image to use: choose highest res available
   fileName = res.PathName1
   If res.PathName2 <> "" Then fileName = res.PathName2
   If res.PathName4 <> "" Then fileName = res.PathName4
   If res.PathName8 <> "" Then fileName = res.PathName8
   If res.PathName16 <> "" Then fileName = res.PathName16
   If res.PathName1h <> "" Then
      fileName = res.PathName1h
      HiRes = True
   End If
   If res.PathName2h <> "" Then
      fileName = res.PathName2h
      HiRes = True
   End If
   If res.PathName4h <> "" Then
      fileName = res.PathName4h
      HiRes = True
   End If
   If res.PathName8h <> "" Then
      fileName = res.PathName8h
      HiRes = True
   End If
   If res.PathName16h <> "" Then
      fileName = res.PathName16h
      HiRes = True
   End If
   If LCase(Right(fileName, 3)) <> "bmp" Then Exit Sub
   obj.Control.AutoSize = True
   obj.Control.Picture = LoadPicture(GetAbsolutePath(fileName, ""))
   obj.Height = obj.Control.Height
   obj.Width = obj.Control.Width
   If HiRes = False Then 'this code does not do anything. It should blow up the image to the full size of the control.
      obj.Control.AutoRedraw = True
      obj.Control.AutoSize = False
      obj.Control.Picture = LoadPicture(GetAbsolutePath(fileName, ""))
      obj.Control.PaintPicture obj.Control.Picture, 0, 0, obj.Control.Width, obj.Control.Height
      obj.Control.Picture = obj.Control.Image
      obj.Control.AutoRedraw = False
   End If
End Sub
