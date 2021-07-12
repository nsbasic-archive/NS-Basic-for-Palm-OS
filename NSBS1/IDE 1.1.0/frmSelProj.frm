VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomctl.ocx"
Begin VB.Form frmSelProj 
   Caption         =   "NS Basic/Palm: Easy development for Palm OS devices!"
   ClientHeight    =   7620
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8430
   LinkTopic       =   "Form1"
   ScaleHeight     =   7620
   ScaleWidth      =   8430
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ImageList ilsIcons16 
      Left            =   720
      Top             =   5640
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   16776960
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   2
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSelProj.frx":0000
            Key             =   "PRJ"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSelProj.frx":0352
            Key             =   "TEXT"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList ilsIcons32 
      Left            =   120
      Top             =   5640
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   16776960
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   2
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSelProj.frx":06A4
            Key             =   "PRJ"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmSelProj.frx":12F6
            Key             =   "TEXT"
         EndProperty
      EndProperty
   End
   Begin VB.Timer tmrUnload 
      Enabled         =   0   'False
      Interval        =   50
      Left            =   1320
      Top             =   5640
   End
   Begin VB.PictureBox m_Controls 
      BorderStyle     =   0  'None
      Height          =   5580
      Left            =   0
      ScaleHeight     =   5580
      ScaleWidth      =   7350
      TabIndex        =   0
      Top             =   0
      Visible         =   0   'False
      Width           =   7350
      Begin MSComctlLib.ListView lvwRecent 
         Height          =   2550
         Left            =   120
         TabIndex        =   2
         Top             =   1395
         Visible         =   0   'False
         Width           =   6270
         _ExtentX        =   11060
         _ExtentY        =   4498
         View            =   3
         Arrange         =   2
         LabelEdit       =   1
         LabelWrap       =   -1  'True
         HideSelection   =   0   'False
         _Version        =   393217
         Icons           =   "ilsIcons32"
         SmallIcons      =   "ilsIcons16"
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   2
         BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            Text            =   "File"
            Object.Width           =   4480
         EndProperty
         BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            SubItemIndex    =   1
            Text            =   "Folder"
            Object.Width           =   4480
         EndProperty
      End
      Begin MSComctlLib.ListView lvwNew 
         Height          =   2550
         Left            =   120
         TabIndex        =   1
         Top             =   1485
         Visible         =   0   'False
         Width           =   6270
         _ExtentX        =   11060
         _ExtentY        =   4498
         LabelEdit       =   1
         LabelWrap       =   -1  'True
         HideSelection   =   0   'False
         _Version        =   393217
         Icons           =   "ilsIcons32"
         SmallIcons      =   "ilsIcons16"
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   0
      End
      Begin VB.CheckBox chkDont 
         Caption         =   "Don't show this dialog in the f&uture"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   195
         Left            =   75
         TabIndex        =   7
         Top             =   5160
         Width           =   5055
      End
      Begin VB.CommandButton CmdNewCancel 
         Caption         =   "&Cancel"
         Height          =   345
         Left            =   5220
         TabIndex        =   5
         Top             =   4515
         Width           =   1125
      End
      Begin VB.CommandButton cmdNewOpen 
         Caption         =   "&Open"
         Default         =   -1  'True
         Height          =   345
         Left            =   5205
         TabIndex        =   4
         Top             =   4080
         Width           =   1125
      End
      Begin VB.PictureBox imgSplash 
         Enabled         =   0   'False
         Height          =   825
         Left            =   60
         Picture         =   "frmSelProj.frx":1F48
         ScaleHeight     =   765
         ScaleWidth      =   6375
         TabIndex        =   3
         TabStop         =   0   'False
         Top             =   75
         Width           =   6435
         Begin VB.Label Label1 
            AutoSize        =   -1  'True
            BackStyle       =   0  'Transparent
            Caption         =   "NS Basic/Palm"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   24
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   555
            Left            =   0
            TabIndex        =   6
            Top             =   105
            Width           =   3345
         End
      End
      Begin MSComctlLib.TabStrip tabMain 
         Height          =   3990
         Left            =   45
         TabIndex        =   8
         Top             =   990
         Width           =   6855
         _ExtentX        =   12091
         _ExtentY        =   7038
         _Version        =   393216
         BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
            NumTabs         =   3
            BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
               Caption         =   "New"
               Key             =   "New"
               Object.ToolTipText     =   "Create a new Project"
               ImageVarType    =   2
            EndProperty
            BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
               Caption         =   "Existing"
               Key             =   "Existing"
               Object.ToolTipText     =   "Open an existing Project"
               ImageVarType    =   2
            EndProperty
            BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
               Caption         =   "Recent"
               Key             =   "Recent"
               Object.ToolTipText     =   "Open a recently edited Project"
               ImageVarType    =   2
            EndProperty
         EndProperty
      End
   End
End
Attribute VB_Name = "frmSelProj"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public WithEvents cD As cCommonDialog
Attribute cD.VB_VarHelpID = -1


Private ShiftDlgX As Long
Private ShiftDlgY As Long

'Holds Dlg Toolbarhwnd
Private Tbhwnd  As Long
'Tmp String for when we change tabs and then return to existing tab
Private TmpFileTxt      As String * 256
'Tab to clean up before showing new tab
Private LastTabFocus    As String

Private m_hwnd As Long
Private m_hDlg As Long
Private m_bCancel As Boolean
Private m_sFileName As String

Private m_bShowNew As Boolean       'Show "New" tab
Private m_bIsNew As Boolean         '"New" tab is visible
Private m_bMainLoading As Boolean   'Main form is loading

Private m_ilsNew As ImageList
Private m_ilsExist As ImageList
Private m_sNewName() As String
Private m_vNewIcon() As Variant
Private m_iNewCount As Long
Private m_sExistName() As String
Private m_sExistFolder() As String
Private m_vExistIcon() As Variant
Private m_iExistCount As Long

Private Sub Form_Load()
   Dim itmX As Object
   Dim i As Long
   Dim strRecent As String, strRecentPath As String, strRecentFile As String

   ' Signal default of cancelled:
   m_bCancel = True
    
   ' Form initialisation:
'   If Not (m_ilsNew Is Nothing) Then
'   End If

   If m_bShowNew Then
      Me.AddNewType "Project File", "PRJ"
      tabMain.Top = imgSplash.Top + imgSplash.Height + 4 * Screen.TwipsPerPixelY
   Else
      tabMain.Top = imgSplash.Top
   End If
   lvwNew.Top = tabMain.ClientTop + 2 * Screen.TwipsPerPixelY
   lvwRecent.Top = lvwNew.Top

   If m_bShowNew Then
      For i = 1 To m_iNewCount
         Set itmX = lvwNew.ListItems.Add(, , m_sNewName(i), m_vNewIcon(i))
         If (i = 1) Then
            itmX.Selected = True
            m_sFileName = lvwNew.SelectedItem.Text
         End If
      Next i
   End If

   If Dir(GlobalPath + "\recent.dat", vbNormal) <> "" Then
      Open GlobalPath + "\recent.dat" For Input As #1
      For i = 1 To 20
         Input #1, strRecent
         If strRecent <> "" Then
            strRecentFile = Mid(strRecent, InStrRev(strRecent, "\") + 1)
            strRecentPath = Left(strRecent, Len(strRecent) - Len(strRecentFile))
'            Set itmX = lvwRecent.ListItems.Add(, , m_sExistName(i), , m_vExistIcon(i))
            Set itmX = lvwRecent.ListItems.Add(, , strRecentFile, , "PRJ")
'            itmX.SubItems(1) = m_sExistFolder(i)
            itmX.SubItems(1) = strRecentPath
            If (i = 1) Then
               itmX.Selected = True
            End If
         End If
      Next
      Close #1
   End If

   imgSplash.Visible = m_bShowNew
   If Not (m_bShowNew) Then
      tabMain.Tabs.Remove 1
   Else
      m_bIsNew = True
   End If
   lvwNew.Visible = m_bShowNew
   cmdNewOpen.Visible = m_bShowNew
   CmdNewCancel.Visible = m_bShowNew
   Me.Visible = False
   ShowDialog
End Sub

Public Function SetBackwardFocus() As Long
   Dim CurHnd As Long
   Dim NewHnd As Long

   CurHnd = GetFocusAPI()

   If tabMain.SelectedItem = "New" Then
      Select Case CurHnd
      Case tabMain.hwnd
         SetFocusAPI CmdNewCancel.hwnd
      Case lvwNew.hwnd
         SetFocusAPI tabMain.hwnd
      Case cmdNewOpen.hwnd
         SetFocusAPI lvwNew.hwnd
      Case CmdNewCancel.hwnd
          SetFocusAPI cmdNewOpen.hwnd
      Case Else
         SetFocusAPI tabMain.hwnd
      End Select
  
      NewHnd = 1
   ElseIf tabMain.SelectedItem = "Recent" Then
      Select Case CurHnd
      Case tabMain.hwnd
         Exit Function
      Case GetDlgItem(m_hwnd, fdlgIDCANCEL)
         Exit Function
      Case GetDlgItem(m_hwnd, fdlgIDOK)
         SetFocusAPI lvwRecent.hwnd
      Case lvwRecent.hwnd
         SetFocusAPI tabMain.hwnd
      Case Else
         SetFocusAPI tabMain.hwnd
      End Select
      
      NewHnd = 1
   End If

   If NewHnd <> 0 Then
      SetBackwardFocus = 1
   Else
      SetBackwardFocus = 0
   End If
End Function

Private Sub SetControlPos(ByVal hd As Long, ByVal SFlags As Long, Optional ByVal lID As Long = -1)
   Dim tdr As RECT
   Dim wLp As POINTAPI
   Dim lShiftX As Long
   Dim lShiftY As Long
 
   GetWindowRect hd, tdr
   ScreenToClient m_hwnd, wLp
      
   lShiftX = tabMain.ClientLeft \ Screen.TwipsPerPixelX
   lShiftY = tabMain.ClientTop \ Screen.TwipsPerPixelY + 2
   wLp.x = wLp.x + tdr.Left + lShiftX
   wLp.y = wLp.y + tdr.Top + lShiftY
   
   SetWindowPos hd, 0, wLp.x, wLp.y, 0, 0, SFlags
   
   If lID = fdlgIDCANCEL Then
      ' Position VB Cancel:
      CmdNewCancel.Move wLp.x * Screen.TwipsPerPixelX - m_Controls.Left, wLp.y * Screen.TwipsPerPixelY - m_Controls.Top, (tdr.Right - tdr.Left) * Screen.TwipsPerPixelX, (tdr.Bottom - tdr.Top) * Screen.TwipsPerPixelY
   ElseIf lID = fdlgIDOK Then
      ' Position VB OK:
      cmdNewOpen.Move wLp.x * Screen.TwipsPerPixelX - m_Controls.Left, wLp.y * Screen.TwipsPerPixelY - m_Controls.Top, (tdr.Right - tdr.Left) * Screen.TwipsPerPixelX, (tdr.Bottom - tdr.Top) * Screen.TwipsPerPixelY
      ' Position ListViews:
      lvwRecent.Move lvwRecent.Left, lvwRecent.Top, _
         cmdNewOpen.Left + cmdNewOpen.Width - lvwRecent.Left, _
         cmdNewOpen.Top - lvwRecent.Top - 4 * Screen.TwipsPerPixelY
      lvwNew.Move lvwRecent.Left, lvwRecent.Top, lvwRecent.Width, lvwRecent.Height
   End If
    
End Sub

Public Function SetForwardFocus() As Long
   Dim CurHnd As Long
   Dim NewHnd As Long
    
   CurHnd = GetFocusAPI()
 
   If tabMain.SelectedItem = "New" Then
      Select Case CurHnd
      Case tabMain.hwnd
         SetFocusAPI cmdNewOpen.hwnd
         If lvwNew.ListItems.count > 0 Then
            SetFocusAPI lvwNew.hwnd
         End If
      Case lvwNew.hwnd
         SetFocusAPI cmdNewOpen.hwnd
      Case cmdNewOpen.hwnd
         SetFocusAPI CmdNewCancel.hwnd
      Case CmdNewCancel.hwnd
         SetFocusAPI tabMain.hwnd
      Case Else
         SetFocusAPI tabMain.hwnd
      End Select
      
      NewHnd = 1
   ElseIf tabMain.SelectedItem = "Recent" Then
      Select Case CurHnd
      Case tabMain.hwnd
         If lvwRecent.ListItems.count > 0 Then
            SetFocusAPI lvwRecent.hwnd
         Else
            SetFocusAPI GetDlgItem(m_hwnd, fdlgIDCANCEL)
            Exit Function
         End If
      Case lvwRecent.hwnd
         If lvwRecent.ListItems.count > 0 Then
            SetFocusAPI GetDlgItem(m_hwnd, fdlgIDOK)
         Else
            SetFocusAPI GetDlgItem(m_hwnd, fdlgIDCANCEL)
            Exit Function
         End If
      Case GetDlgItem(m_hwnd, fdlgIDOK)
         Exit Function
      Case GetDlgItem(m_hwnd, fdlgIDCANCEL)
         Exit Function
      Case Else
         SetFocusAPI tabMain.hwnd
      End Select
  
      NewHnd = 1
   End If

   If NewHnd <> 0 Then
      SetForwardFocus = 1
   Else
      SetForwardFocus = 0
   End If
End Function

Private Sub cD_DialogOK(bCancel As Boolean)
   bCancel = True
   m_bCancel = False
   m_sFileName = GetCDlgFileName(m_hDlg)
   tmrUnload.Enabled = True
End Sub

Private Sub cD_FolderChange(ByVal hDlg As Long)
   Static DoOnce As Boolean
   Dim hd As Long
 
   If Not DoOnce Then
      'We do this because the file listvw was not_
      'created till after dialog intialize
 
      If m_bShowNew Then
         hd = GetDlgItem(m_hwnd, fdlgLVLstFiles)
         SetControlPos hd, SWP_MOVEHIDE Or SWP_NOMOVE Or SWP_NOZORDER
      Else
         SetFocusAPI m_Controls.hwnd
      End If
      
      m_Controls.Visible = True
      m_Controls.ZOrder 1
      DoOnce = True
   End If
End Sub

Private Sub cD_InitDialog(ByVal hDlg As Long)
   Dim hd As Long
   Dim tR As RECT, tTR As RECT
   Dim lW As Long, lH As Long
    
   m_hDlg = hDlg
   ' For Open/Save dialog we need the parent of the supplied dialog handle:
   m_hwnd = GetParent(hDlg)
   GetWindowRect m_hwnd, tTR
        
   If m_bShowNew Then
      
      '// Cancel Button
      hd = GetDlgItem(m_hwnd, fdlgIDCANCEL)
      SetControlPos hd, SWP_MOVEHIDE, fdlgIDCANCEL
      GetWindowRect hd, tR
        
      '// Open Button
      hd = GetDlgItem(m_hwnd, fdlgIDOK)
      SetControlPos hd, SWP_MOVEHIDE, fdlgIDOK
        
      '// Read-Only CheckBox
      hd = GetDlgItem(m_hwnd, fdlgChxReadOnly)
      SetControlPos hd, SWP_MOVEHIDE
      EnableWindow hd, False
  
      '// FileType TextBox
      hd = GetDlgItem(m_hwnd, fdlgcmbSaveAsType)
      SetControlPos hd, SWP_MOVEHIDE
        
      '// FileType Label
      hd = GetDlgItem(m_hwnd, fdlgStcSaveAsType)
      SetControlPos hd, SWP_MOVEHIDE
        
      '// FileName TxtBox
      hd = GetDlgItem(m_hwnd, fdlgEdtFileName)
      SetControlPos hd, SWP_MOVEHIDE
        
      '// FileName Label
      hd = GetDlgItem(m_hwnd, fdlgStcFileName)
      SetControlPos hd, SWP_MOVEHIDE
          
      '// ListBoxLb
      hd = GetDlgItem(m_hwnd, fdlgLBLstFiles)
      SetControlPos hd, SWP_MOVEHIDE
      EnableWindow hd, True
      
      '// Find ComboBox:
      hd = GetDlgItem(m_hwnd, fdlgCmbSaveInFindIn)
      SetControlPos hd, SWP_MOVEHIDE
          
      '// Find In Label:
      hd = GetDlgItem(m_hwnd, fdlgStcSaveInFindIn)
      SetControlPos hd, SWP_MOVEHIDE
          
      '// Tool Bar
      Tbhwnd = FindWindowEx(m_hwnd, 0&, "ToolbarWindow32", vbNullString)
      SetControlPos Tbhwnd, SWP_MOVEHIDE Or SWP_NOZORDER
   Else
      '// Cancel Button
      hd = GetDlgItem(m_hwnd, fdlgIDCANCEL)
      SetControlPos hd, SWP_NOSIZE
      GetWindowRect hd, tR
          
      '// Open Button
      hd = GetDlgItem(m_hwnd, fdlgIDOK)
      SetControlPos hd, SWP_NOSIZE
          
      '// Read-Only CheckBox
      hd = GetDlgItem(m_hwnd, fdlgChxReadOnly)
      SetControlPos hd, SWP_MOVEHIDE
      EnableWindow hd, False
      
      '// FileType TextBox
      hd = GetDlgItem(m_hwnd, fdlgcmbSaveAsType)
      SetControlPos hd, SWP_NOSIZE
          
      '// FileType Label
      hd = GetDlgItem(m_hwnd, fdlgStcSaveAsType)
      SetControlPos hd, SWP_NOSIZE
          
      '// FileName TxtBox
      hd = GetDlgItem(m_hwnd, fdlgEdtFileName)
      SetControlPos hd, SWP_NOSIZE
          
      '// FileName Label
      hd = GetDlgItem(m_hwnd, fdlgStcFileName)
      SetControlPos hd, SWP_NOSIZE
          
      '// ListBoxLb
      hd = GetDlgItem(m_hwnd, fdlgLBLstFiles)
      SetControlPos hd, SWP_NOSIZE
      EnableWindow hd, True
      
      '// Find ComboBox:
      hd = GetDlgItem(m_hwnd, fdlgCmbSaveInFindIn)
      SetControlPos hd, SWP_NOSIZE
          
      '// Find In Label:
      hd = GetDlgItem(m_hwnd, fdlgStcSaveInFindIn)
      SetControlPos hd, SWP_NOSIZE
          
      '// Tool Bar
      Tbhwnd = FindWindowEx(m_hwnd, 0&, "ToolbarWindow32", vbNullString)
      SetControlPos Tbhwnd, SWP_NOSIZE Or SWP_NOZORDER
    
   End If
  
   'Resize dialog to [me.height & me.width] then center
   lW = tR.Right - tTR.Left + (tabMain.ClientLeft * 2 + Me.Width - Me.ScaleWidth) \ Screen.TwipsPerPixelX
   lH = (m_Controls.Top + tabMain.Top + tabMain.Height + chkDont.Height + Me.Height - Me.ScaleHeight) \ Screen.TwipsPerPixelY + 8
   chkDont.Move chkDont.Left, tabMain.Height + tabMain.Top + 4 * Screen.TwipsPerPixelY
   MoveWindow m_hwnd, 0&, 0&, lW + 4, lH + 8, 0
   'Center it
   cD.CentreDialog hDlg, Screen
   m_Controls.Width = lW * Screen.TwipsPerPixelX - (Me.Width - Me.ScaleWidth)
   tabMain.Width = m_Controls.Width - 2 * tabMain.Left
   lvwNew.Width = tabMain.ClientWidth - 2 * (lvwNew.Left - tabMain.ClientLeft)
   lvwRecent.Width = lvwNew.Width
   lvwRecent.ColumnHeaders(1).Width = lvwRecent.Width \ 3
   lvwRecent.ColumnHeaders(2).Width = lvwRecent.Width - lvwRecent.ColumnHeaders(1).Width - 795
   imgSplash.Width = tabMain.Width
   Label1.Left = (imgSplash.Width - Label1.Width) \ 2
   
   'move our controls container to dialog
   SetParent m_Controls.hwnd, m_hwnd
      
   InstallHook

End Sub

Private Sub chkDont_Click()
   m_bShowNew = Not m_bShowNew
End Sub

Private Sub CmdNewCancel_Click()
   m_sFileName = ""
   Form_QueryUnload 0, 0
End Sub

Private Sub cmdNewOpen_Click()
   If lvwNew.SelectedItem Is Nothing Then Exit Sub
   
   m_sFileName = lvwNew.SelectedItem.Text
   m_bCancel = False
   Form_QueryUnload 0, 0
   
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
   If (m_hwnd <> 0) And (m_hDlg <> 0) Then
      ' Cancel Common Dialog box if loaded:
      
      'Put m_Controls back on Me
      SetParent m_Controls.hwnd, Me.hwnd
      
      ' Send Close command to the dialog:
      SendMessageLong m_hwnd, WM_COMMAND, fdlgIDCANCEL, 1
      SendMessageLong m_hDlg, WM_CLOSE, 0, 0
      SendMessageLong m_hwnd, WM_CLOSE, 0, 0
      m_hwnd = 0: m_hDlg = 0
   End If
   RemoveHook
End Sub

Private Sub Form_Resize()
   Debug.Print
End Sub

Private Sub lvwNew_DblClick()
   If Not (lvwNew.SelectedItem Is Nothing) And Not (lvwNew.DropHighlight Is Nothing) Then
      cmdNewOpen.Value = True
   End If
End Sub

Private Sub lvwNew_ItemClick(ByVal Item As MSComctlLib.ListItem)
   m_sFileName = Item.Text
End Sub

Private Sub lvwNew_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
   If Button = vbLeftButton Then
      lvwNew.DropHighlight = lvwNew.HitTest(x, y)
   End If
End Sub

Private Sub lvwRecent_DblClick()
   If Not (lvwRecent.SelectedItem Is Nothing) And Not (lvwRecent.DropHighlight Is Nothing) Then
      m_sFileName = lvwRecent.SelectedItem.Text
      SendMessageLong m_hwnd, WM_COMMAND, fdlgIDOK, 1
   End If
End Sub

Private Sub lvwRecent_ItemClick(ByVal Item As MSComctlLib.ListItem)
   ' Recent item:
   m_sFileName = Item.SubItems(1)
   If (Right$(m_sFileName, 1) <> "\") Then m_sFileName = m_sFileName & "\"
   m_sFileName = m_sFileName & Item.Text
   SetDlgItemText m_hwnd, fdlgEdtFileName, m_sFileName
End Sub

Private Sub lvwRecent_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
   If Button = vbLeftButton Then
      lvwRecent.DropHighlight = lvwRecent.HitTest(x, y)
   End If
End Sub

Private Sub m_Controls_GotFocus()
   If GetFocusAPI <> tabMain.hwnd Then
      If tabMain.SelectedItem.caption = "New" Then
         'We do this to make cmdnewopen the show as default else it won't
         SetFocusAPI cmdNewOpen.hwnd
      End If
      SetFocusAPI tabMain.hwnd
   End If
End Sub

Private Sub tabMain_BeforeClick(Cancel As Integer)
   LastTabFocus = tabMain.SelectedItem.caption
End Sub

Private Sub tabMain_Click()
   Dim iTab As String
   Dim hd  As Long
   
   ' Show the relevant picture box for the
   ' selected tab:
   iTab = tabMain.SelectedItem.caption
   If iTab = LastTabFocus Then Exit Sub
      
   Select Case LastTabFocus
   Case "New"
      m_bIsNew = False
      ShowWindow lvwNew.hwnd, 0&
      
      cmdNewOpen.Visible = False
      CmdNewCancel.Visible = False
      
   Case "Existing"
      
      Call GetDlgItemText(m_hwnd, fdlgEdtFileName, TmpFileTxt, 128)
      
      hd = GetDlgItem(m_hwnd, fdlgLVLstFiles)
      ShowWindow hd, 0&
      
      hd = GetDlgItem(m_hwnd, fdlgStcSaveInFindIn)
      ShowWindow hd, 0&
   
      hd = GetDlgItem(m_hwnd, fdlgCmbSaveInFindIn)
      ShowWindow hd, 0&
      EnableWindow hd, 0&
   
      ShowWindow Tbhwnd, 0&
                
      hd = GetDlgItem(m_hwnd, fdlgStcFileName)
      ShowWindow hd, 0&
                
      hd = GetDlgItem(m_hwnd, fdlgEdtFileName)
      ShowWindow hd, 0&
                
      hd = GetDlgItem(m_hwnd, fdlgStcSaveAsType)
      ShowWindow hd, 0&
   
      hd = GetDlgItem(m_hwnd, fdlgcmbSaveAsType)
      ShowWindow hd, 0&
     
   Case "Recent"
      ShowWindow lvwRecent.hwnd, 0&
      
   End Select
    
   Select Case iTab
   Case "New"
      m_bIsNew = True
      ShowWindow lvwNew.hwnd, 1&
      SetFocusAPI tabMain.hwnd
      
      hd = GetDlgItem(m_hwnd, fdlgIDCANCEL)
      ShowWindow hd, 0&
  
      hd = GetDlgItem(m_hwnd, fdlgIDOK)
      ShowWindow hd, 0&
      
      cmdNewOpen.Visible = True
      CmdNewCancel.Visible = True
      
      If Not (lvwNew.SelectedItem Is Nothing) Then
         m_sFileName = lvwNew.SelectedItem.Text
         lvwNew.SelectedItem.Selected = True
      Else
         m_sFileName = ""
      End If
      
      SetFocusAPI tabMain.hwnd
      
   Case "Existing"
      hd = GetDlgItem(m_hwnd, fdlgIDCANCEL)
      ShowWindow hd, 1&
            
      hd = GetDlgItem(m_hwnd, fdlgIDOK)
      ShowWindow hd, 1&
      EnableWindow hd, 1&
      
      hd = GetDlgItem(m_hwnd, fdlgcmbSaveAsType)
      ShowWindow hd, 1&
                     
      hd = GetDlgItem(m_hwnd, fdlgStcSaveAsType)
      ShowWindow hd, 1&
   
      hd = GetDlgItem(m_hwnd, fdlgEdtFileName)
      ShowWindow hd, 1&
    
      hd = GetDlgItem(m_hwnd, fdlgStcFileName)
      ShowWindow hd, 1&
               
      hd = GetDlgItem(m_hwnd, fdlgLVLstFiles)
      ShowWindow hd, 1&
      
      hd = GetDlgItem(m_hwnd, fdlgCmbSaveInFindIn)
      ShowWindow hd, 1&
      EnableWindow hd, True
    
      hd = GetDlgItem(m_hwnd, fdlgStcSaveInFindIn)
      ShowWindow hd, 1&
  
      ShowWindow Tbhwnd, 1
                
      m_sFileName = TmpFileTxt
    
      SetFocusAPI tabMain.hwnd
      SetDlgItemText m_hwnd, fdlgEdtFileName, TmpFileTxt
      
   Case "Recent"
            
      hd = GetDlgItem(m_hwnd, fdlgIDCANCEL)
      ShowWindow hd, 1&
            
      hd = GetDlgItem(m_hwnd, fdlgIDOK)
      ShowWindow hd, 1&
      
      ShowWindow lvwRecent.hwnd, 1&
      SetFocusAPI tabMain.hwnd
      
      If lvwRecent.ListItems.count = 0 Then
         hd = GetDlgItem(m_hwnd, fdlgIDOK)
         EnableWindow hd, 0&
         ShowWindow hd, 0&
         m_sFileName = ""
      Else
         If Not (lvwRecent.SelectedItem Is Nothing) Then
            m_sFileName = lvwRecent.SelectedItem.SubItems(1)
            If (Right$(m_sFileName, 1) <> "\") Then m_sFileName = m_sFileName & "\"
            m_sFileName = m_sFileName & lvwRecent.SelectedItem.Text
         Else
            m_sFileName = ""
         End If
      End If
      
      If Not (lvwRecent.SelectedItem Is Nothing) Then
         lvwRecent.SelectedItem.Selected = True
      End If
   
      SetDlgItemText m_hwnd, fdlgEdtFileName, m_sFileName
   End Select
    
    
End Sub

Public Property Get ShowNew() As Boolean
    ShowNew = m_bShowNew
End Property

Public Property Get IsNew() As Boolean
    IsNew = m_bIsNew
End Property

Public Sub AddNewType(ByVal sName As String, ByVal vIcon As Variant)
   m_iNewCount = m_iNewCount + 1
   ReDim Preserve m_sNewName(1 To m_iNewCount) As String
   ReDim Preserve m_vNewIcon(1 To m_iNewCount) As Variant
   m_sNewName(m_iNewCount) = sName
   m_vNewIcon(m_iNewCount) = vIcon
End Sub

Public Sub AddExistItem(ByVal sName As String, ByVal sFolder As String, Optional ByVal vIcon As Variant)
    m_iExistCount = m_iExistCount + 1
    ReDim Preserve m_sExistName(1 To m_iExistCount) As String
    ReDim Preserve m_sExistFolder(1 To m_iExistCount) As String
    ReDim Preserve m_vExistIcon(1 To m_iExistCount) As Variant
    m_sExistName(m_iExistCount) = sName
    m_sExistFolder(m_iExistCount) = sFolder
    m_vExistIcon(m_iExistCount) = vIcon
End Sub

Public Property Let NewImageList(ByRef ilsThis As Variant)
   Set m_ilsNew = ilsThis
End Property

Public Property Let ExistingImageList(ByRef ilsThis As Variant)
    Set m_ilsExist = ilsThis
End Property

Public Property Let ShowNew(ByVal bShow As Boolean)
    m_bShowNew = bShow
End Property

Public Property Get Cancelled() As Boolean
    Cancelled = m_bCancel
End Property

Public Property Get fileName() As String
    ' Property to allow the caller to retrieve the
    ' selected file name:
    fileName = m_sFileName
End Property

Private Sub tmrUnload_Timer()
   Unload Me
End Sub

Public Sub ShowDialog()
   'If chkToggleView.value = Unchecked Then
   '   me.ShowNew = 0
   'Else
   '   Me.ShowNew = 1
   'End If

   If Me.ShowNew Then
   End If
    
   'Me.AddExistItem "Readme2.Txt", App.path & "\", "9/21/98", "TEXT"
   'Me.AddExistItem "Deletedfile.Txt", App.path & "\", "9/23/98", "HTML"
   'Me.AddExistItem "ccnews.Htm", App.path & "\", "9/25/98", "HTML"
'   Me.ExistingImageList = ilsIcons16
    
   Set Me.cD = New cCommonDialog
   Me.cD.DialogTitle = "Open Project"
   Me.cD.InitDir = winreg.GetRegValue(winreg.hKey, winreg.SubKey, "RecentPath", GlobalPath + "\Projects")
   Me.cD.Filter = "Project Files (*.PRJ)|*.PRJ|All Files (*.*)|*.*"
   Me.cD.flags = OFN_FILEMUSTEXIST Or OFN_PATHMUSTEXIST
   Me.cD.FilterIndex = 1
   Me.cD.DefaultExt = "prj"
   Me.cD.HookDialog = True

   'Make Dialog owner Me
   Me.cD.hwnd = Me.hwnd
'   Load Me

   Me.cD.ShowOpen
    
   If Not Me.Cancelled Then
      'lblFile.caption = "New:" & Me.FileName
      'If Me.IsNew Then
      '   If Me.FileName = "HTML File" Then
      '      txtFile.text = "<HTML>" & vbCrLf & vbCrLf & "<HEADER" & vbCrLf & "</HEADER>" & vbCrLf & vbCrLf & "<BODY>" & vbCrLf & "</BODY>" & vbCrLf & vbCrLf & "</HTML>"
      '   Else
      '      txtFile.text = ""
      '   End If
      'Else
      '   txtFile.text = GetFileText(Me.FileName)
      'End If
   End If

'   If me.ShowNew Then
'      chkToggleView.value = 1
'   Else
'      chkToggleView.value = 0
'   End If
End Sub
