VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmToolbox 
   BorderStyle     =   4  'Fixed ToolWindow
   ClientHeight    =   6930
   ClientLeft      =   45
   ClientTop       =   285
   ClientWidth     =   345
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   6930
   ScaleWidth      =   345
   ShowInTaskbar   =   0   'False
   Begin MSComctlLib.Toolbar tbToolbox 
      Height          =   5280
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   375
      _ExtentX        =   661
      _ExtentY        =   9313
      ButtonWidth     =   609
      ButtonHeight    =   582
      Style           =   1
      ImageList       =   "imlToolbox"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   16
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Cursor"
            ImageIndex      =   1
            Style           =   1
            Value           =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Button"
            Object.ToolTipText     =   "1202"
            ImageIndex      =   2
            Style           =   1
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "List"
            Object.ToolTipText     =   "1203"
            ImageIndex      =   3
            Style           =   1
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Label"
            Object.ToolTipText     =   "1204"
            ImageIndex      =   4
            Style           =   1
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Field"
            Object.ToolTipText     =   "1205"
            ImageIndex      =   5
            Style           =   1
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "PushButton"
            Object.ToolTipText     =   "1206"
            ImageIndex      =   6
            Style           =   1
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Checkbox"
            Object.ToolTipText     =   "1207"
            ImageIndex      =   7
            Style           =   1
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "PopupTrigger"
            Object.ToolTipText     =   "1208"
            ImageIndex      =   8
            Style           =   1
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Selector"
            Object.ToolTipText     =   "1209"
            ImageIndex      =   9
            Style           =   1
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Bitmap"
            Object.ToolTipText     =   "1210"
            ImageIndex      =   10
            Style           =   1
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Gadget"
            Object.ToolTipText     =   "1211"
            ImageIndex      =   11
            Style           =   1
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Repeater"
            Object.ToolTipText     =   "1212"
            ImageIndex      =   12
            Style           =   1
         EndProperty
         BeginProperty Button13 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Scrollbar"
            Object.ToolTipText     =   "1213"
            ImageIndex      =   13
            Style           =   1
         EndProperty
         BeginProperty Button14 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "GraffitiShiftIndicator"
            Object.ToolTipText     =   "1214"
            ImageIndex      =   14
            Style           =   1
         EndProperty
         BeginProperty Button15 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Data Aware Grid"
            Object.ToolTipText     =   "3406"
            ImageIndex      =   15
            Style           =   1
         EndProperty
         BeginProperty Button16 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Slider"
            Object.ToolTipText     =   "3415"
            ImageIndex      =   16
            Style           =   1
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList imlToolbox 
      Left            =   0
      Top             =   5880
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   16777215
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   16
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":0000
            Key             =   "Cursor"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":0352
            Key             =   "Button"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":06A4
            Key             =   "List"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":09F6
            Key             =   "Label"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":0D48
            Key             =   "Field"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":109A
            Key             =   "PushButton"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":13EC
            Key             =   "Checkbox"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":173E
            Key             =   "PopupTrigger"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":1A90
            Key             =   "Selector"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":1DE2
            Key             =   "Bitmap"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":2134
            Key             =   "Gadget"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":2486
            Key             =   "Repeater"
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":27D8
            Key             =   "Scrollbar"
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":2B2A
            Key             =   "ShiftIndicator"
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":2E7C
            Key             =   "Grid"
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmToolbox.frx":30CE
            Key             =   "Slider"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmToolbox"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public Sub DockWindow()
'On Error Resume Next
Dim lRet As Long

   'Hide first
   Me.Visible = False

   'Make sure we keep the ToolWindow style
   lRet = SetWindowLong(Me.hwnd, GWL_EXSTYLE, CLng(WS_EX_TOOLBOXWINDOW))

   'Set parent window and its size
   SetParent Me.hwnd, frmMain.picToolbox.hwnd
   frmMain.picToolbox.Width = Me.Width
   frmMain.picToolbox_Resize
'   Me.Move 0, 0

   'Show everything
   frmMain.picToolbox.Visible = True
   DoEvents
   Me.Visible = True
   SendMessage Me.hwnd, WM_NCACTIVATE, 1, 0

   'Keep track of some info
   frmMain.mnuViewToolbox.Checked = True
End Sub

Private Sub Form_Load()
   gbToolbox = True
   gnToolboxTool = 1
   Me.Width = tbToolbox.Width
   LoadResStrings Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
   gbToolbox = False
   frmMain.picToolbox.Visible = False
   frmMain.mnuViewToolbox.Checked = False
End Sub

Private Sub tbToolbox_ButtonClick(ByVal Button As MSComctlLib.Button)
   ToolboxSelect Button.index
End Sub

Public Sub ToolboxSelect(nTool As Integer)
Dim nIndex As Integer

   If nTool = gnToolboxTool And nTool <> 1 Then
      nIndex = 1
   Else
      nIndex = nTool
   End If
   tbToolbox.Buttons(gnToolboxTool).Value = tbrUnpressed
   gnToolboxTool = nIndex
   tbToolbox.Buttons(gnToolboxTool).Value = tbrPressed
End Sub

