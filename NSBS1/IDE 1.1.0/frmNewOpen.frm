VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomctl.ocx"
Begin VB.Form frmNewOpen 
   Caption         =   "Open"
   ClientHeight    =   5550
   ClientLeft      =   2325
   ClientTop       =   1695
   ClientWidth     =   6495
   ClipControls    =   0   'False
   Icon            =   "frmNewOpen.frx":0000
   LinkTopic       =   "Form2"
   ScaleHeight     =   5550
   ScaleWidth      =   6495
   Begin VB.Timer tmrUnload 
      Enabled         =   0   'False
      Interval        =   50
      Left            =   5520
      Top             =   5040
   End
   Begin VB.PictureBox m_Controls 
      BorderStyle     =   0  'None
      Height          =   5370
      Left            =   60
      ScaleHeight     =   5370
      ScaleWidth      =   6375
      TabIndex        =   0
      Top             =   120
      Visible         =   0   'False
      Width           =   6375
      Begin VB.PictureBox imgSplash 
         Enabled         =   0   'False
         Height          =   825
         Left            =   0
         Picture         =   "frmNewOpen.frx":014A
         ScaleHeight     =   765
         ScaleWidth      =   6375
         TabIndex        =   7
         TabStop         =   0   'False
         Top             =   0
         Width           =   6435
         Begin VB.Label lblSplash 
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
            TabIndex        =   8
            Tag             =   "1401"
            Top             =   105
            Width           =   3345
         End
      End
      Begin MSComctlLib.ListView lvwNew 
         Height          =   2520
         Left            =   120
         TabIndex        =   5
         Top             =   1440
         Width           =   6150
         _ExtentX        =   10848
         _ExtentY        =   4445
         LabelEdit       =   1
         LabelWrap       =   -1  'True
         HideSelection   =   0   'False
         _Version        =   393217
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         NumItems        =   0
      End
      Begin MSComctlLib.ListView lvwRecent 
         Height          =   2520
         Left            =   120
         TabIndex        =   4
         Top             =   1320
         Visible         =   0   'False
         Width           =   6150
         _ExtentX        =   10848
         _ExtentY        =   4445
         View            =   3
         Arrange         =   2
         LabelEdit       =   1
         LabelWrap       =   -1  'True
         HideSelection   =   0   'False
         _Version        =   393217
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         NumItems        =   2
         BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            Text            =   "File"
            Object.Width           =   3598
         EndProperty
         BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            SubItemIndex    =   1
            Text            =   "Folder"
            Object.Width           =   6879
         EndProperty
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
         Left            =   60
         TabIndex        =   3
         Tag             =   "1144"
         Top             =   5100
         Width           =   5055
      End
      Begin VB.CommandButton cmdNewOpen 
         Caption         =   "&Open"
         Default         =   -1  'True
         Height          =   345
         Left            =   5040
         TabIndex        =   2
         Tag             =   "1145"
         Top             =   4020
         Width           =   1125
      End
      Begin VB.CommandButton CmdNewCancel 
         Caption         =   "&Cancel"
         Height          =   345
         Left            =   5030
         TabIndex        =   1
         Tag             =   "1146"
         Top             =   4425
         Width           =   1125
      End
      Begin MSComctlLib.TabStrip tabMain 
         Height          =   3990
         Left            =   0
         TabIndex        =   6
         Top             =   900
         Width           =   6375
         _ExtentX        =   11245
         _ExtentY        =   7038
         _Version        =   393216
         BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
            NumTabs         =   3
            BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
               Caption         =   "New"
               Object.Tag             =   "1141"
               ImageVarType    =   2
            EndProperty
            BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
               Caption         =   "Existing"
               Object.Tag             =   "1142"
               ImageVarType    =   2
            EndProperty
            BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
               Caption         =   "Recent"
               Object.Tag             =   "1143"
               ImageVarType    =   2
            EndProperty
         EndProperty
      End
   End
End
Attribute VB_Name = "frmNewOpen"
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

Private m_bShowNew As Boolean
Private m_bIsNew As Boolean

Private m_ilsNew As MSComctlLib.ImageList
Private m_ilsExist As MSComctlLib.ImageList
Private m_sNewName() As String
Private m_vNewIcon() As Variant
Private m_iNewCount As Long
Private m_sExistName() As String
Private m_sExistFolder() As String
Private m_dExistDate() As Date
Private m_vExistIcon() As Variant
Private m_iExistCOunt As Long

Public Function SetBackwardFocus() As Long
Dim CurHnd As Long
Dim NewHnd As Long

   CurHnd = GetFocusAPI()
        
   If tabMain.SelectedItem = gStringTable(1141) Then 'new
  
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
  
   ElseIf tabMain.SelectedItem = gStringTable(1143) Then 'recent
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
   Else
 
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
      CmdNewCancel.Move wLp.x * Screen.TwipsPerPixelX - m_Controls.Left - 300, wLp.y * Screen.TwipsPerPixelY - m_Controls.Top, 300 + (tdr.Right - tdr.Left) * Screen.TwipsPerPixelX, (tdr.Bottom - tdr.Top) * Screen.TwipsPerPixelY
   ElseIf lID = fdlgIDOK Then
      ' Position VB OK:
      cmdNewOpen.Move wLp.x * Screen.TwipsPerPixelX - m_Controls.Left - 300, wLp.y * Screen.TwipsPerPixelY - m_Controls.Top, 300 + (tdr.Right - tdr.Left) * Screen.TwipsPerPixelX, (tdr.Bottom - tdr.Top) * Screen.TwipsPerPixelY
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
 
   If tabMain.SelectedItem = gStringTable(1141) Then 'new
  
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
  
   ElseIf tabMain.SelectedItem = gStringTable(1143) Then 'recent
  
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
  
   Else
 
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
   If m_bShowNew Then
      lH = (m_Controls.Top + tabMain.Top + tabMain.Height + chkDont.Height + Me.Height - Me.ScaleHeight) \ Screen.TwipsPerPixelY + 2
      chkDont.Move chkDont.Left, tabMain.Height + tabMain.Top + 4 * Screen.TwipsPerPixelY
   Else
      lH = (m_Controls.Top + tabMain.Top + tabMain.Height + Me.Height - Me.ScaleHeight) \ Screen.TwipsPerPixelY
   End If
   MoveWindow m_hwnd, 0&, 0&, lW + 4, lH + 8, 0
   'Center it
   cD.CentreDialog hDlg, Screen
   m_Controls.Width = lW * Screen.TwipsPerPixelX - (Me.Width - Me.ScaleWidth)
   tabMain.Width = m_Controls.Width
   imgSplash.Width = tabMain.Width
   lblSplash.Left = (imgSplash.Width - lblSplash.Width) \ 2

   'move our controls container to dialog
   SetParent m_Controls.hwnd, m_hwnd

   InstallHook
End Sub

Private Sub chkDont_Click()
   m_bShowNew = Not m_bShowNew
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "ShowSplash", m_bShowNew
End Sub

Private Sub CmdNewCancel_Click()
   Form_QueryUnload 0, 0
End Sub

Private Sub cmdNewOpen_Click()
   If lvwNew.SelectedItem Is Nothing Then Exit Sub

   m_sFileName = lvwNew.SelectedItem.Text
   m_bCancel = False
   Form_QueryUnload 0, 0
End Sub

Private Sub Form_Load()
Dim itmX As ListItem
Dim i As Long
   LoadResStrings Me
   'Signal default of cancelled:
   m_bCancel = True

   'Form initialisation:
   If Not (m_ilsNew Is Nothing) Then
      lvwNew.Icons = m_ilsNew
   End If

   If m_bShowNew Then
      tabMain.Top = imgSplash.Top + imgSplash.Height + 4 * Screen.TwipsPerPixelY
   Else
      tabMain.Top = imgSplash.Top
   End If
   lvwNew.Top = tabMain.ClientTop + 2 * Screen.TwipsPerPixelY
   lvwRecent.Top = tabMain.ClientTop + 2 * Screen.TwipsPerPixelY

   If m_bShowNew Then
      For i = 1 To m_iNewCount
         Set itmX = lvwNew.ListItems.Add(, , m_sNewName(i), m_vNewIcon(i))
         If (i = 1) Then
            itmX.Selected = True
            m_sFileName = lvwNew.SelectedItem.Text
         End If
      Next i
   End If

   If Not (m_ilsExist Is Nothing) Then
      lvwRecent.SmallIcons = m_ilsExist
   End If

   For i = 1 To m_iExistCOunt
      Set itmX = lvwRecent.ListItems.Add(, , m_sExistName(i), , m_vExistIcon(i))
      itmX.SubItems(1) = m_sExistFolder(i)
'      itmX.SubItems(2) = m_dExistDate(i)
      If (i = 1) Then
         itmX.Selected = True
      End If
   Next i

   If m_bShowNew Then
      imgSplash.Visible = True
      lblSplash.Visible = True
      m_bIsNew = True
      lvwNew.Visible = True
      cmdNewOpen.Visible = True
      CmdNewCancel.Visible = True
      chkDont.Visible = True
   Else
      imgSplash.Visible = False
      lblSplash.Visible = False
      tabMain.Tabs.Remove 1
      lvwNew.Visible = False
      cmdNewOpen.Visible = False
      CmdNewCancel.Visible = False
      chkDont.Visible = False
   End If
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
   If (m_hwnd <> 0) And (m_hDlg <> 0) Then
      'Cancel Common Dialog box if loaded:
      
      'Put m_Controls back on Me
      SetParent m_Controls.hwnd, Me.hwnd
      
      'Send Close command to the dialog:
      SendMessageLong m_hwnd, WM_COMMAND, fdlgIDCANCEL, 1
      SendMessageLong m_hDlg, WM_CLOSE, 0, 0
      SendMessageLong m_hwnd, WM_CLOSE, 0, 0
      m_hwnd = 0: m_hDlg = 0
   End If

   RemoveHook
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
   'Recent item:
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

   'Show the relevant picture box for the
   'selected tab:
   iTab = tabMain.SelectedItem.caption
   If iTab = LastTabFocus Then Exit Sub

   Select Case LastTabFocus
   Case gStringTable(1141) 'New
      m_bIsNew = False
      ShowWindow lvwNew.hwnd, 0&

      cmdNewOpen.Visible = False
      CmdNewCancel.Visible = False
   Case gStringTable(1142) '"Existing"
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
   Case gStringTable(1143) '"Recent"
      ShowWindow lvwRecent.hwnd, 0&
   End Select

   Select Case iTab
   Case gStringTable(1141) '"New"
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
   Case gStringTable(1142) '"Existing"
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
   Case gStringTable(1143) '"Recent"
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

Public Sub AddNewType(ByVal sName As String, Optional ByVal vIcon As Variant)
   m_iNewCount = m_iNewCount + 1
   ReDim Preserve m_sNewName(1 To m_iNewCount) As String
   ReDim Preserve m_vNewIcon(1 To m_iNewCount) As Variant
   m_sNewName(m_iNewCount) = sName
   m_vNewIcon(m_iNewCount) = vIcon
End Sub

'Public Sub AddExistItem(ByVal sName As String, ByVal sFOlder As String, ByVal dDate As Date, Optional ByVal vIcon As Variant)
Public Sub AddExistItem(ByVal sName As String, ByVal sFOlder As String, Optional ByVal vIcon As Variant)
   m_iExistCOunt = m_iExistCOunt + 1
   ReDim Preserve m_sExistName(1 To m_iExistCOunt) As String
   ReDim Preserve m_sExistFolder(1 To m_iExistCOunt) As String
'   ReDim Preserve m_dExistDate(1 To m_iExistCOunt) As Date
   ReDim Preserve m_vExistIcon(1 To m_iExistCOunt) As Variant
   m_sExistName(m_iExistCOunt) = sName
   m_sExistFolder(m_iExistCOunt) = sFOlder
'   m_dExistDate(m_iExistCOunt) = dDate
   m_vExistIcon(m_iExistCOunt) = vIcon
End Sub

Public Property Let NewImageList(ByRef ilsThis As ImageList)
   Set m_ilsNew = ilsThis
End Property

Public Property Let ExistingImageList(ByRef ilsThis As ImageList)
   Set m_ilsExist = ilsThis
End Property

Public Property Let ShowNew(ByVal bShow As Boolean)
   m_bShowNew = bShow
End Property

Public Property Get Cancelled() As Boolean
   Cancelled = m_bCancel
End Property

Public Property Get fileName() As String
   'Property to allow the caller to retrieve the
   'selected file name:
   fileName = m_sFileName
End Property

Private Sub tmrUnload_Timer()
   Unload Me
End Sub
