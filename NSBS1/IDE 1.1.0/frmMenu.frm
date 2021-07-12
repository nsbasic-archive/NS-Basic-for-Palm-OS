VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.MDIForm frmMain 
   BackColor       =   &H8000000C&
   Caption         =   "Project1"
   ClientHeight    =   3225
   ClientLeft      =   60
   ClientTop       =   600
   ClientWidth     =   5640
   LinkTopic       =   "MDIForm1"
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.Toolbar tbToolBar 
      Align           =   1  'Align Top
      Height          =   1080
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   5640
      _ExtentX        =   9948
      _ExtentY        =   1905
      ButtonWidth     =   609
      Appearance      =   1
      ImageList       =   "imlToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   24
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "New"
            Object.ToolTipText     =   "1087"
            ImageKey        =   "New"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Open"
            Object.ToolTipText     =   "1088"
            ImageKey        =   "Open"
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Save"
            Object.ToolTipText     =   "1089"
            ImageKey        =   "Save"
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Print"
            Object.ToolTipText     =   "1090"
            ImageKey        =   "Print"
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Undo"
            Object.ToolTipText     =   "1091"
            ImageKey        =   "Undo"
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Redo"
            Object.ToolTipText     =   "1092"
            ImageKey        =   "Redo"
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Cut"
            Object.ToolTipText     =   "1093"
            ImageKey        =   "Cut"
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Copy"
            Object.ToolTipText     =   "1094"
            ImageKey        =   "Copy"
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Paste"
            Object.ToolTipText     =   "1095"
            ImageKey        =   "Paste"
         EndProperty
         BeginProperty Button13 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Delete"
            Object.ToolTipText     =   "1096"
            ImageKey        =   "Delete"
         EndProperty
         BeginProperty Button14 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button15 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Find"
            Object.ToolTipText     =   "1097"
            ImageKey        =   "Find"
         EndProperty
         BeginProperty Button16 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button17 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Add Form"
            Object.ToolTipText     =   "1098"
            ImageKey        =   "form1"
         EndProperty
         BeginProperty Button18 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Add Bitmap"
            Object.ToolTipText     =   "1099"
            ImageKey        =   "Bitmap"
         EndProperty
         BeginProperty Button19 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Add Module"
            Object.ToolTipText     =   "1100"
            ImageKey        =   "code"
         EndProperty
         BeginProperty Button20 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button21 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Make"
            Object.ToolTipText     =   "1101"
            ImageKey        =   "Macro"
         EndProperty
         BeginProperty Button22 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button23 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Properties"
            Object.ToolTipText     =   "1102"
            ImageKey        =   "Properties"
         EndProperty
         BeginProperty Button24 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Menu Editor"
            Object.ToolTipText     =   "1103"
            ImageKey        =   "MenuEditor"
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog dlgCommonDialog 
      Left            =   1740
      Top             =   1365
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   0
      Top             =   2955
      Width           =   5640
      _ExtentX        =   9948
      _ExtentY        =   476
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   4471
            Text            =   "Status"
            TextSave        =   "Status"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            AutoSize        =   2
            TextSave        =   "3/7/2001"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "5:32 AM"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Left            =   1740
      Top             =   1365
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   17
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0000
            Key             =   "New"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0112
            Key             =   "Open"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0224
            Key             =   "Save"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0336
            Key             =   "Print"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0448
            Key             =   "Undo"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":055A
            Key             =   "Redo"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":066C
            Key             =   "Cut"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":077E
            Key             =   "Copy"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0890
            Key             =   "Paste"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":09A2
            Key             =   "Delete"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0AB4
            Key             =   "Find"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0BC6
            Key             =   "form1"
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":0F18
            Key             =   "Bitmap"
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":11D2
            Key             =   "code"
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":1724
            Key             =   "Macro"
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":1836
            Key             =   "Properties"
         EndProperty
         BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMenu.frx":1948
            Key             =   "MenuEditor"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "1000"
      Begin VB.Menu mnuFileNewProject 
         Caption         =   "1001"
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFileOpenProject 
         Caption         =   "1002"
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileSaveProject 
         Caption         =   "1003"
      End
      Begin VB.Menu mnuFileSaveProjectAs 
         Caption         =   "1004"
      End
      Begin VB.Menu mnuFileBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "1005"
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "1006"
      End
      Begin VB.Menu mnuFileSaveAll 
         Caption         =   "1007"
      End
      Begin VB.Menu mnuFileBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFilePageSetup 
         Caption         =   "1008"
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "1009"
      End
      Begin VB.Menu mnuFileBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   1
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   2
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   3
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   4
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileBar4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "1010"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "1011"
      Begin VB.Menu mnuEditUndo 
         Caption         =   "1012"
         Shortcut        =   ^Z
      End
      Begin VB.Menu mnuEditRedo 
         Caption         =   "1013"
      End
      Begin VB.Menu mnuEditBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditCut 
         Caption         =   "1014"
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "1015"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuEditPaste 
         Caption         =   "1016"
         Shortcut        =   ^V
      End
      Begin VB.Menu mnuEditDelete 
         Caption         =   "1017"
      End
      Begin VB.Menu mnuEditSelectAll 
         Caption         =   "1018"
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuEditBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditFind 
         Caption         =   "1019"
         Shortcut        =   ^F
      End
      Begin VB.Menu mnuEditFindNext 
         Caption         =   "1020"
         Shortcut        =   ^G
      End
      Begin VB.Menu mnuEditReplace 
         Caption         =   "1021"
         Shortcut        =   ^H
      End
      Begin VB.Menu mnuEditGoTo 
         Caption         =   "1022"
         Shortcut        =   ^T
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "1023"
      Begin VB.Menu mnuViewToolbar 
         Caption         =   "1024"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewStatusBar 
         Caption         =   "1025"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewRefresh 
         Caption         =   "1026"
      End
   End
   Begin VB.Menu mnuProject 
      Caption         =   "1027"
      Begin VB.Menu mnuProjectAddForm 
         Caption         =   "1028"
      End
      Begin VB.Menu mnuProjectAddBitmap 
         Caption         =   "1029"
      End
      Begin VB.Menu mnuProjectAddModule 
         Caption         =   "1030"
      End
      Begin VB.Menu mnuProjectBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuProjectStartupCode 
         Caption         =   "1031"
      End
      Begin VB.Menu mnuProjectTerminationCode 
         Caption         =   "1032"
      End
      Begin VB.Menu mnuProjectHelpCode 
         Caption         =   "1033"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuProjectBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuProjectMake 
         Caption         =   "1034"
      End
      Begin VB.Menu mnuProjectBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuProjectDownloadProject 
         Caption         =   "1035"
      End
      Begin VB.Menu mnuProjectDownloadRuntime 
         Caption         =   "1036"
      End
      Begin VB.Menu mnuProjectDownloadMathlib 
         Caption         =   "1037"
      End
      Begin VB.Menu mnuProjectBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuProjectProperties 
         Caption         =   "1038"
      End
      Begin VB.Menu mnuProjectBar4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuProjectSetDefault 
         Caption         =   "1039"
      End
   End
   Begin VB.Menu mnuFormat 
      Caption         =   "1040"
      Begin VB.Menu mnuFormatAlign 
         Caption         =   "1041"
         Begin VB.Menu mnuFormatAlignLefts 
            Caption         =   "1042"
         End
         Begin VB.Menu mnuFormatAlignCenters 
            Caption         =   "1043"
         End
         Begin VB.Menu mnuFormatAlignRights 
            Caption         =   "1044"
         End
         Begin VB.Menu mnuFormatAlignBar0 
            Caption         =   "-"
         End
         Begin VB.Menu mnuFormatAlignTops 
            Caption         =   "1045"
         End
         Begin VB.Menu mnuFormatAlignMiddles 
            Caption         =   "1046"
         End
         Begin VB.Menu mnuFormatAlignBottoms 
            Caption         =   "1047"
         End
         Begin VB.Menu mnuFormatAlignBar1 
            Caption         =   "-"
         End
         Begin VB.Menu mnuFormatAlignToGrid 
            Caption         =   "1048"
         End
      End
      Begin VB.Menu mnuFormatMakeSameSize 
         Caption         =   "1049"
         Begin VB.Menu mnuFormatMakeSameSizeWidth 
            Caption         =   "1050"
         End
         Begin VB.Menu mnuFormatMakeSameSizeHeight 
            Caption         =   "1051"
         End
         Begin VB.Menu mnuFormatMakeSameSizeBoth 
            Caption         =   "1052"
         End
      End
      Begin VB.Menu mnuFormatBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormatSizeToGrid 
         Caption         =   "1053"
      End
      Begin VB.Menu mnumnuFormatBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormatHorizontalSpacing 
         Caption         =   "1054"
         Begin VB.Menu mnuFormatHorizontalSpacingEqual 
            Caption         =   "1055"
         End
         Begin VB.Menu mnuFormatHorizontalSpacingIncrease 
            Caption         =   "1056"
         End
         Begin VB.Menu mnuFormatHorizontalSpacingDecrease 
            Caption         =   "1057"
         End
         Begin VB.Menu mnuFormatHorizontalSpacingRemove 
            Caption         =   "1058"
         End
      End
      Begin VB.Menu mnuFormatVerticalSpacing 
         Caption         =   "1059"
         Begin VB.Menu mnuFormatVerticalSpacingEqual 
            Caption         =   "1060"
         End
         Begin VB.Menu mnuFormatVerticalSpacingIncrease 
            Caption         =   "1061"
         End
         Begin VB.Menu mnuFormatVerticalSpacingDecrease 
            Caption         =   "1062"
         End
         Begin VB.Menu mnuFormatVerticalSpacingRemove 
            Caption         =   "1063"
         End
      End
      Begin VB.Menu mnumnuFormatBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormatCenter 
         Caption         =   "1064"
         Begin VB.Menu mnuFormatCenterHorizontally 
            Caption         =   "1065"
         End
         Begin VB.Menu mnuFormatCenterVertically 
            Caption         =   "1066"
         End
      End
      Begin VB.Menu mnuFormatBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormatOrder 
         Caption         =   "1067"
         Begin VB.Menu mnuFormatOrderFront 
            Caption         =   "1068"
         End
         Begin VB.Menu mnuFormatOrderForward 
            Caption         =   "1069"
         End
         Begin VB.Menu mnuFormatOrderBackward 
            Caption         =   "1070"
         End
         Begin VB.Menu mnuFormatOrderBack 
            Caption         =   "1071"
         End
      End
   End
   Begin VB.Menu mnuTools 
      Caption         =   "1072"
      Begin VB.Menu mnuToolsMenuEditor 
         Caption         =   "1073"
      End
      Begin VB.Menu mnuToolsBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolsOptions 
         Caption         =   "1074"
      End
   End
   Begin VB.Menu mnuWindow 
      Caption         =   "1075"
      WindowList      =   -1  'True
      Begin VB.Menu mnuWindowToolPalette 
         Caption         =   "1076"
      End
      Begin VB.Menu mnuWindowProperties 
         Caption         =   "1077"
         Shortcut        =   {F4}
      End
      Begin VB.Menu mnuWindowBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuWindowCascade 
         Caption         =   "1078"
      End
      Begin VB.Menu mnuWindowTileHorizontal 
         Caption         =   "1079"
      End
      Begin VB.Menu mnuWindowTileVertical 
         Caption         =   "1080"
      End
      Begin VB.Menu mnuWindowBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuWindowWindows 
         Caption         =   "1081"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "1082"
      Begin VB.Menu mnuHelpRegister 
         Caption         =   "1083"
      End
      Begin VB.Menu mnuHelpTopics 
         Caption         =   "1084"
      End
      Begin VB.Menu mnuHelpWWW 
         Caption         =   "1085"
      End
      Begin VB.Menu mnuHelpBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "1086"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function SendMessage Lib "User32" Alias "SendMessageA" (ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Any) As Long
Const EM_UNDO = &HC7

Private Sub MDIForm_Load()
   LoadResStrings Me
   Me.Left = GetSetting(App.Title, "Settings", "MainLeft", 1000)
   Me.Top = GetSetting(App.Title, "Settings", "MainTop", 1000)
   Me.Width = GetSetting(App.Title, "Settings", "MainWidth", 6500)
   Me.Height = GetSetting(App.Title, "Settings", "MainHeight", 6500)
   LoadNewDoc
End Sub


Private Sub LoadNewDoc()
   Static lDocumentCount As Long
   Dim frmD As frmDocument
   lDocumentCount = lDocumentCount + 1
   Set frmD = New frmDocument
   frmD.Caption = "Document " & lDocumentCount
   frmD.Show
End Sub


Private Sub MDIForm_Unload(Cancel As Integer)
   If Me.WindowState <> vbMinimized Then
      SaveSetting App.Title, "Settings", "MainLeft", Me.Left
      SaveSetting App.Title, "Settings", "MainTop", Me.Top
      SaveSetting App.Title, "Settings", "MainWidth", Me.Width
      SaveSetting App.Title, "Settings", "MainHeight", Me.Height
   End If
End Sub

Private Sub tbToolBar_ButtonClick(ByVal Button As MSComCtlLib.Button)
   On Error Resume Next
   Select Case Button.Key
      Case "New"
         LoadNewDoc
      Case "Open"
         mnuFileOpen_Click
      Case "Save"
         mnuFileSave_Click
      Case "Print"
         mnuFilePrint_Click
      Case "Undo"
         'ToDo: Add 'Undo' button code.
         MsgBox "Add 'Undo' button code."
      Case "Redo"
         'ToDo: Add 'Redo' button code.
         MsgBox "Add 'Redo' button code."
      Case "Cut"
         mnuEditCut_Click
      Case "Copy"
         mnuEditCopy_Click
      Case "Paste"
         mnuEditPaste_Click
      Case "Delete"
         'ToDo: Add 'Delete' button code.
         MsgBox "Add 'Delete' button code."
      Case "Find"
         'ToDo: Add 'Find' button code.
         MsgBox "Add 'Find' button code."
      Case "Add Form"
         'ToDo: Add 'Add Form' button code.
         MsgBox "Add 'Add Form' button code."
      Case "Add Bitmap"
         'ToDo: Add 'Add Bitmap' button code.
         MsgBox "Add 'Add Bitmap' button code."
      Case "Add Module"
         'ToDo: Add 'Add Module' button code.
         MsgBox "Add 'Add Module' button code."
      Case "Make"
         'ToDo: Add 'Make' button code.
         MsgBox "Add 'Make' button code."
      Case "Properties"
         'ToDo: Add 'Properties' button code.
         MsgBox "Add 'Properties' button code."
      Case "Menu Editor"
         'ToDo: Add 'Menu Editor' button code.
         MsgBox "Add 'Menu Editor' button code."
   End Select
End Sub

Private Sub mnuHelpmnuHelpAbout_Click()
   'ToDo: Add 'mnuHelpmnuHelpAbout_Click' code.
   MsgBox "Add 'mnuHelpmnuHelpAbout_Click' code."
End Sub

Private Sub mnuHelpmnuHelpWWW_Click()
   'ToDo: Add 'mnuHelpmnuHelpWWW_Click' code.
   MsgBox "Add 'mnuHelpmnuHelpWWW_Click' code."
End Sub

Private Sub mnuHelpmnuHelpHelp_Click()
   'ToDo: Add 'mnuHelpmnuHelpHelp_Click' code.
   MsgBox "Add 'mnuHelpmnuHelpHelp_Click' code."
End Sub

Private Sub mnuHelpmnuHelpRegister_Click()
   'ToDo: Add 'mnuHelpmnuHelpRegister_Click' code.
   MsgBox "Add 'mnuHelpmnuHelpRegister_Click' code."
End Sub

Private Sub mnuWindowmnuWindowWindows_Click()
   'ToDo: Add 'mnuWindowmnuWindowWindows_Click' code.
   MsgBox "Add 'mnuWindowmnuWindowWindows_Click' code."
End Sub

Private Sub mnuWindowTileVertical_Click()
   Me.Arrange vbTileVertical
End Sub

Private Sub mnuWindowTileHorizontal_Click()
   Me.Arrange vbTileHorizontal
End Sub

Private Sub mnuWindowCascade_Click()
   Me.Arrange vbCascade
End Sub

Private Sub mnuWindowmnuWindowProperties_Click()
   'ToDo: Add 'mnuWindowmnuWindowProperties_Click' code.
   MsgBox "Add 'mnuWindowmnuWindowProperties_Click' code."
End Sub

Private Sub mnuWindowmnuWindowToolPalette_Click()
   'ToDo: Add 'mnuWindowmnuWindowToolPalette_Click' code.
   MsgBox "Add 'mnuWindowmnuWindowToolPalette_Click' code."
End Sub

Private Sub mnuToolsOptions_Click()
   'ToDo: Add 'mnuToolsOptions_Click' code.
   MsgBox "Add 'mnuToolsOptions_Click' code."
End Sub

Private Sub mnuToolsmnuToolsMenuEditor_Click()
   'ToDo: Add 'mnuToolsmnuToolsMenuEditor_Click' code.
   MsgBox "Add 'mnuToolsmnuToolsMenuEditor_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatOrderBack_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatOrderBack_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatOrderBack_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatOrderBackward_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatOrderBackward_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatOrderBackward_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatOrderForward_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatOrderForward_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatOrderForward_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatOrderFront_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatOrderFront_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatOrderFront_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatOrder_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatOrder_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatOrder_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatCenterVertically_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatCenterVertically_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatCenterVertically_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatCenterHorizontally_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatCenterHorizontally_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatCenterHorizontally_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatCenter_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatCenter_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatCenter_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatVerticalSpacingRemove_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatVerticalSpacingRemove_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatVerticalSpacingRemove_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatVerticalSpacingDecrease_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatVerticalSpacingDecrease_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatVerticalSpacingDecrease_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatVerticalSpacingIncrease_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatVerticalSpacingIncrease_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatVerticalSpacingIncrease_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatVerticalSpacingEqual_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatVerticalSpacingEqual_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatVerticalSpacingEqual_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatVerticalSpacing_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatVerticalSpacing_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatVerticalSpacing_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatHorizontalSpacingRemove_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatHorizontalSpacingRemove_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatHorizontalSpacingRemove_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatHorizontalSpacingDecrease_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatHorizontalSpacingDecrease_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatHorizontalSpacingDecrease_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatHorizontalSpacingIncrease_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatHorizontalSpacingIncrease_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatHorizontalSpacingIncrease_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatHorizontalSpacingEqual_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatHorizontalSpacingEqual_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatHorizontalSpacingEqual_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatHorizontalSpacing_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatHorizontalSpacing_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatHorizontalSpacing_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatSizeToGrid_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatSizeToGrid_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatSizeToGrid_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatMakeSameSizeBoth_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatMakeSameSizeBoth_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatMakeSameSizeBoth_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatMakeSameSizeHeight_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatMakeSameSizeHeight_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatMakeSameSizeHeight_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatMakeSameSizeWidth_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatMakeSameSizeWidth_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatMakeSameSizeWidth_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatMakeSameSize_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatMakeSameSize_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatMakeSameSize_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatAlignToGrid_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatAlignToGrid_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatAlignToGrid_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatAlignBottoms_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatAlignBottoms_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatAlignBottoms_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatAlignMiddles_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatAlignMiddles_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatAlignMiddles_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatAlignTops_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatAlignTops_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatAlignTops_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatAlignRights_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatAlignRights_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatAlignRights_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatAlignCenters_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatAlignCenters_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatAlignCenters_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatAlignLefts_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatAlignLefts_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatAlignLefts_Click' code."
End Sub

Private Sub mnumnuFormatmnuFormatAlign_Click()
   'ToDo: Add 'mnumnuFormatmnuFormatAlign_Click' code.
   MsgBox "Add 'mnumnuFormatmnuFormatAlign_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectSetDefault_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectSetDefault_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectSetDefault_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectProperties_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectProperties_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectProperties_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectDownloadMathlib_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectDownloadMathlib_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectDownloadMathlib_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectDownloadRuntime_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectDownloadRuntime_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectDownloadRuntime_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectDownloadProject_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectDownloadProject_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectDownloadProject_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectMake_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectMake_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectMake_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectHelpCode_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectHelpCode_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectHelpCode_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectTerminationCode_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectTerminationCode_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectTerminationCode_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectStartupCode_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectStartupCode_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectStartupCode_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectAddModule_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectAddModule_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectAddModule_Click' code."
End Sub

Private Sub mnumnuProjectmnuEditAddBitmap_Click()
   'ToDo: Add 'mnumnuProjectmnuEditAddBitmap_Click' code.
   MsgBox "Add 'mnumnuProjectmnuEditAddBitmap_Click' code."
End Sub

Private Sub mnumnuProjectmnuProjectAddForm_Click()
   'ToDo: Add 'mnumnuProjectmnuProjectAddForm_Click' code.
   MsgBox "Add 'mnumnuProjectmnuProjectAddForm_Click' code."
End Sub

Private Sub mnuViewRefresh_Click()
   'ToDo: Add 'mnuViewRefresh_Click' code.
   MsgBox "Add 'mnuViewRefresh_Click' code."
End Sub

Private Sub mnuViewStatusBar_Click()
   mnuViewStatusBar.Checked = Not mnuViewStatusBar.Checked
   sbStatusBar.Visible = mnuViewStatusBar.Checked
End Sub

Private Sub mnuViewToolbar_Click()
   mnuViewToolbar.Checked = Not mnuViewToolbar.Checked
   tbToolBar.Visible = mnuViewToolbar.Checked
End Sub

Private Sub mnuEditmnuEditGoTo_Click()
   'ToDo: Add 'mnuEditmnuEditGoTo_Click' code.
   MsgBox "Add 'mnuEditmnuEditGoTo_Click' code."
End Sub

Private Sub mnuEditmnuEditReplace_Click()
   'ToDo: Add 'mnuEditmnuEditReplace_Click' code.
   MsgBox "Add 'mnuEditmnuEditReplace_Click' code."
End Sub

Private Sub mnuEditmnuEditFindNext_Click()
   'ToDo: Add 'mnuEditmnuEditFindNext_Click' code.
   MsgBox "Add 'mnuEditmnuEditFindNext_Click' code."
End Sub

Private Sub mnuEditmnuEditFind_Click()
   'ToDo: Add 'mnuEditmnuEditFind_Click' code.
   MsgBox "Add 'mnuEditmnuEditFind_Click' code."
End Sub

Private Sub mnuEditmnuEditSelectAll_Click()
   'ToDo: Add 'mnuEditmnuEditSelectAll_Click' code.
   MsgBox "Add 'mnuEditmnuEditSelectAll_Click' code."
End Sub

Private Sub mnuEditmnuEditDelete_Click()
   'ToDo: Add 'mnuEditmnuEditDelete_Click' code.
   MsgBox "Add 'mnuEditmnuEditDelete_Click' code."
End Sub

Private Sub mnuEditPaste_Click()
   On Error Resume Next
   ActiveForm.rtfText.SelRTF = Clipboard.GetText

End Sub

Private Sub mnuEditCopy_Click()
   On Error Resume Next
   Clipboard.SetText ActiveForm.rtfText.SelRTF

End Sub

Private Sub mnuEditCut_Click()
   On Error Resume Next
   Clipboard.SetText ActiveForm.rtfText.SelRTF
   ActiveForm.rtfText.SelText = vbNullString

End Sub

Private Sub mnuEditmnuEditRedo_Click()
   'ToDo: Add 'mnuEditmnuEditRedo_Click' code.
   MsgBox "Add 'mnuEditmnuEditRedo_Click' code."
End Sub

Private Sub mnuEditUndo_Click()
   'ToDo: Add 'mnuEditUndo_Click' code.
   MsgBox "Add 'mnuEditUndo_Click' code."
End Sub


Private Sub mnuFileExit_Click()
   'unload the form
   Unload Me

End Sub

Private Sub mnuFilePrint_Click()
   On Error Resume Next
   If ActiveForm Is Nothing Then Exit Sub
   

   With dlgCommonDialog
      .DialogTitle = "Print"
      .CancelError = True
      .Flags = cdlPDReturnDC + cdlPDNoPageNums
      If ActiveForm.rtfText.SelLength = 0 Then
         .Flags = .Flags + cdlPDAllPages
      Else
         .Flags = .Flags + cdlPDSelection
      End If
      .ShowPrinter
      If Err <> MSComDlg.cdlCancel Then
         ActiveForm.rtfText.SelPrint .hDC
      End If
   End With

End Sub

Private Sub mnuFilePageSetup_Click()
   On Error Resume Next
   With dlgCommonDialog
      .DialogTitle = "Page Setup"
      .CancelError = True
      .ShowPrinter
   End With

End Sub

Private Sub mnuFileSaveAll_Click()
   'ToDo: Add 'mnuFileSaveAll_Click' code.
   MsgBox "Add 'mnuFileSaveAll_Click' code."
End Sub

Private Sub mnuFileSaveAs_Click()
   Dim sFile As String
   

   If ActiveForm Is Nothing Then Exit Sub
   

   With dlgCommonDialog
      .DialogTitle = "Save As"
      .CancelError = False
      'ToDo: set the flags and attributes of the common dialog control
      .Filter = "All Files (*.*)|*.*"
      .ShowSave
      If Len(.FileName) = 0 Then
         Exit Sub
      End If
      sFile = .FileName
   End With
   ActiveForm.Caption = sFile
   ActiveForm.rtfText.SaveFile sFile

End Sub

Private Sub mnuFileSave_Click()
   Dim sFile As String
   If Left$(ActiveForm.Caption, 8) = "Document" Then
      With dlgCommonDialog
         .DialogTitle = "Save"
         .CancelError = False
         'ToDo: set the flags and attributes of the common dialog control
         .Filter = "All Files (*.*)|*.*"
         .ShowSave
         If Len(.FileName) = 0 Then
            Exit Sub
         End If
         sFile = .FileName
      End With
      ActiveForm.rtfText.SaveFile sFile
   Else
      sFile = ActiveForm.Caption
      ActiveForm.rtfText.SaveFile sFile
   End If

End Sub

Private Sub mnuFilemnuFileSaveProjectAs_Click()
   'ToDo: Add 'mnuFilemnuFileSaveProjectAs_Click' code.
   MsgBox "Add 'mnuFilemnuFileSaveProjectAs_Click' code."
End Sub

Private Sub mnuFilemnuFileSaveProject_Click()
   'ToDo: Add 'mnuFilemnuFileSaveProject_Click' code.
   MsgBox "Add 'mnuFilemnuFileSaveProject_Click' code."
End Sub

Private Sub mnuFileOpen_Click()
   Dim sFile As String


   If ActiveForm Is Nothing Then LoadNewDoc
   

   With dlgCommonDialog
      .DialogTitle = "Open"
      .CancelError = False
      'ToDo: set the flags and attributes of the common dialog control
      .Filter = "All Files (*.*)|*.*"
      .ShowOpen
      If Len(.FileName) = 0 Then
         Exit Sub
      End If
      sFile = .FileName
   End With
   ActiveForm.rtfText.LoadFile sFile
   ActiveForm.Caption = sFile

End Sub

Private Sub mnuFileNew_Click()
   LoadNewDoc
End Sub

