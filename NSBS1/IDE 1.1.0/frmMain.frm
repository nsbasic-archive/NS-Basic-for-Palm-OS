VERSION 5.00
Object = "{BCA00000-0F85-414C-A938-5526E9F1E56A}#4.0#0"; "cmax40.dll"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{6FBA474E-43AC-11CE-9A0E-00AA0062BB4C}#1.0#0"; "SYSINFO.OCX"
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Object = "{EFC9CC66-188E-11D5-9892-0000CB222337}#1.0#0"; "emulink.ocx"
Begin VB.MDIForm frmMain 
   BackColor       =   &H8000000C&
   Caption         =   "1401[NS Basic for Palm]"
   ClientHeight    =   7905
   ClientLeft      =   225
   ClientTop       =   855
   ClientWidth     =   11700
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "MDIForm1"
   Picture         =   "frmMain.frx":08CA
   StartUpPosition =   3  'Windows Default
   Tag             =   "1401"
   Begin MSWinsockLib.Winsock tcpServer 
      Left            =   3840
      Top             =   1080
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin SysInfoLib.SysInfo SysInfo 
      Left            =   1560
      Top             =   1080
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
   End
   Begin VB.PictureBox picBox 
      Align           =   1  'Align Top
      Height          =   615
      Left            =   0
      ScaleHeight     =   555
      ScaleWidth      =   11640
      TabIndex        =   8
      Top             =   360
      Visible         =   0   'False
      Width           =   11700
      Begin VB.PictureBox picTmp 
         Height          =   375
         Left            =   0
         ScaleHeight     =   315
         ScaleWidth      =   435
         TabIndex        =   10
         Top             =   0
         Width           =   495
      End
      Begin CodeMax4Ctl.CodeMax cmaxFind 
         Height          =   375
         Left            =   1080
         OleObjectBlob   =   "frmMain.frx":0918
         TabIndex        =   9
         Top             =   120
         Width           =   855
      End
      Begin EMULINKLib.EmuLink EmuLink1 
         Left            =   2400
         Top             =   0
         _Version        =   131072
         _ExtentX        =   873
         _ExtentY        =   873
         _StockProps     =   0
      End
   End
   Begin VB.Timer tmrStatus 
      Enabled         =   0   'False
      Interval        =   3000
      Left            =   3360
      Top             =   1080
   End
   Begin VB.PictureBox picToolbox 
      Align           =   3  'Align Left
      Appearance      =   0  'Flat
      BackColor       =   &H80000004&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   6660
      Left            =   0
      ScaleHeight     =   6660
      ScaleWidth      =   840
      TabIndex        =   7
      Top             =   975
      Width           =   840
   End
   Begin VB.PictureBox picPanel 
      Align           =   4  'Align Right
      Appearance      =   0  'Flat
      BackColor       =   &H80000004&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   6660
      Left            =   8220
      ScaleHeight     =   6660
      ScaleWidth      =   3480
      TabIndex        =   2
      Top             =   975
      Visible         =   0   'False
      Width           =   3480
      Begin VB.PictureBox picProperties 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   855
         Left            =   240
         ScaleHeight     =   855
         ScaleWidth      =   495
         TabIndex        =   6
         Top             =   3120
         Visible         =   0   'False
         Width           =   495
      End
      Begin VB.PictureBox picProjectExplorer 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   855
         Left            =   240
         ScaleHeight     =   855
         ScaleWidth      =   495
         TabIndex        =   5
         Top             =   1920
         Visible         =   0   'False
         Width           =   495
      End
      Begin VB.PictureBox picSplit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000004&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   135
         Left            =   240
         MouseIcon       =   "frmMain.frx":0A08
         MousePointer    =   99  'Custom
         ScaleHeight     =   135
         ScaleWidth      =   495
         TabIndex        =   4
         Top             =   2880
         Visible         =   0   'False
         Width           =   495
      End
      Begin VB.PictureBox picWidth 
         Appearance      =   0  'Flat
         BackColor       =   &H80000004&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   2055
         Left            =   0
         MouseIcon       =   "frmMain.frx":0C1A
         MousePointer    =   99  'Custom
         ScaleHeight     =   2055
         ScaleWidth      =   135
         TabIndex        =   3
         Top             =   1920
         Width           =   135
      End
   End
   Begin MSComDlg.CommonDialog dlgCommonDialog 
      Left            =   2760
      Top             =   1080
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   0
      Top             =   7635
      Width           =   11700
      _ExtentX        =   20638
      _ExtentY        =   476
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   5
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   9843
            Text            =   "Status"
            TextSave        =   "Status"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Coordinates"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Dimensions"
         EndProperty
         BeginProperty Panel4 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            TextSave        =   "12/13/2010"
         EndProperty
         BeginProperty Panel5 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "10:39 PM"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar tbToolBar 
      Align           =   1  'Align Top
      Height          =   360
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   11700
      _ExtentX        =   20638
      _ExtentY        =   635
      ButtonWidth     =   609
      ButtonHeight    =   582
      Appearance      =   1
      Style           =   1
      ImageList       =   "imlToolbarIcons"
      DisabledImageList=   "imlDisabledToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   24
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "New"
            Object.ToolTipText     =   "1087"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Open"
            Object.ToolTipText     =   "1088"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Save"
            Object.ToolTipText     =   "1089"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Print"
            Object.ToolTipText     =   "1090"
            ImageIndex      =   4
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Undo"
            Object.ToolTipText     =   "1091"
            ImageIndex      =   5
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Redo"
            Object.ToolTipText     =   "1092"
            ImageIndex      =   6
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Cut"
            Object.ToolTipText     =   "1093"
            ImageIndex      =   7
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Copy"
            Object.ToolTipText     =   "1094"
            ImageIndex      =   8
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Paste"
            Object.ToolTipText     =   "1095"
            ImageIndex      =   9
         EndProperty
         BeginProperty Button13 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Delete"
            Object.ToolTipText     =   "1096"
            ImageIndex      =   10
         EndProperty
         BeginProperty Button14 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button15 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Find"
            Object.ToolTipText     =   "1097"
            ImageIndex      =   11
         EndProperty
         BeginProperty Button16 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button17 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Add Form"
            Object.ToolTipText     =   "1098"
            ImageIndex      =   12
         EndProperty
         BeginProperty Button18 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Add Bitmap"
            Object.ToolTipText     =   "1099"
            ImageIndex      =   13
         EndProperty
         BeginProperty Button19 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Add Module"
            Object.ToolTipText     =   "1100"
            ImageIndex      =   14
         EndProperty
         BeginProperty Button20 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button21 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Compile"
            Object.ToolTipText     =   "1101"
            ImageIndex      =   15
         EndProperty
         BeginProperty Button22 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button23 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Properties"
            Object.ToolTipText     =   "1102"
            ImageIndex      =   16
         EndProperty
         BeginProperty Button24 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Menu Editor"
            Object.ToolTipText     =   "1103"
            ImageIndex      =   17
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList ilsIcons32 
      Left            =   960
      Top             =   2280
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
            Picture         =   "frmMain.frx":0E2C
            Key             =   "PRJ"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1706
            Key             =   "TEXT"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList ilsIcons16 
      Left            =   960
      Top             =   2880
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
            Picture         =   "frmMain.frx":2358
            Key             =   "PRJ"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":28F2
            Key             =   "TEXT"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Left            =   960
      Top             =   1080
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483633
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   17
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2C44
            Key             =   "New"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2F96
            Key             =   "Open"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":32E8
            Key             =   "Save"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":363A
            Key             =   "Print"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":398C
            Key             =   "Undo"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":3CDE
            Key             =   "Redo"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":4030
            Key             =   "Cut"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":4382
            Key             =   "Copy"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":46D4
            Key             =   "Paste"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":4A26
            Key             =   "Delete"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":4D78
            Key             =   "Find"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":50CA
            Key             =   "Form"
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":541C
            Key             =   "Bitmap"
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":576E
            Key             =   "Module"
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":5AC0
            Key             =   "Compile"
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":5E12
            Key             =   "Properties"
         EndProperty
         BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6164
            Key             =   "MenuEditor"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList imlDisabledToolbarIcons 
      Left            =   960
      Top             =   1680
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483633
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   17
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":64B6
            Key             =   "New"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6808
            Key             =   "Open"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6B5A
            Key             =   "Save"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":6EAC
            Key             =   "Print"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":71FE
            Key             =   "Undo"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7550
            Key             =   "Redo"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":78A2
            Key             =   "Cut"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7BF4
            Key             =   "Copy"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":7F46
            Key             =   "Paste"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8298
            Key             =   "Delete"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":85EA
            Key             =   "Find"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":893C
            Key             =   "Form"
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8C8E
            Key             =   "Bitmap"
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":8FE0
            Key             =   "Module"
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":9332
            Key             =   "Compile"
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":9684
            Key             =   "Properties"
         EndProperty
         BeginProperty ListImage17 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":99D6
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
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFileSaveProjectAs 
         Caption         =   "1004"
      End
      Begin VB.Menu mnuFileBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFilePageSetup 
         Caption         =   "1008"
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "1009"
         Shortcut        =   ^P
      End
      Begin VB.Menu mnuFileBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   1
      End
      Begin VB.Menu mnuFileMRU 
         Caption         =   ""
         Index           =   2
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
         Shortcut        =   ^Y
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
         Shortcut        =   {F3}
         Visible         =   0   'False
      End
      Begin VB.Menu mnuEditReplace 
         Caption         =   "1021"
         Shortcut        =   ^H
      End
      Begin VB.Menu mnuEditGoTo 
         Caption         =   "1022"
         Shortcut        =   ^T
      End
      Begin VB.Menu editSep3 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuEditPreferences 
         Caption         =   "1218"
         Visible         =   0   'False
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "1023"
      Begin VB.Menu mnuViewProjectExplorer 
         Caption         =   "1118"
         Shortcut        =   ^R
      End
      Begin VB.Menu mnuViewProperties 
         Caption         =   "1077"
         Shortcut        =   {F4}
      End
      Begin VB.Menu mnuViewToolbox 
         Caption         =   "1076"
         Shortcut        =   ^B
      End
      Begin VB.Menu mnuViewBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewToolbar 
         Caption         =   "1024"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewStatusBar 
         Caption         =   "1025"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewBar1 
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
      Begin VB.Menu mnuProjectAddMenu 
         Caption         =   "1029"
      End
      Begin VB.Menu mnuProjectAddBitmap 
         Caption         =   "1030"
      End
      Begin VB.Menu mnuProjectAddNewModule 
         Caption         =   "1516"
      End
      Begin VB.Menu mnuProjectAddExistingModule 
         Caption         =   "1517"
      End
      Begin VB.Menu mnuProjectAddResource 
         Caption         =   "3355"
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
         Begin VB.Menu mnuProjectSetTargetList 
            Caption         =   ""
            Index           =   0
         End
      End
   End
   Begin VB.Menu mnuFormat 
      Caption         =   "1040"
      Begin VB.Menu mnuFormatAlign 
         Caption         =   "1041"
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "1042"
            Index           =   0
         End
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "1043"
            Index           =   1
         End
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "1044"
            Index           =   2
         End
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "-"
            Index           =   3
         End
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "1045"
            Index           =   4
         End
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "1046"
            Index           =   5
         End
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "1047"
            Index           =   6
         End
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "-"
            Index           =   7
         End
         Begin VB.Menu mnuFormatAlignItem 
            Caption         =   "1048"
            Index           =   8
         End
      End
      Begin VB.Menu mnuFormatMakeSameSize 
         Caption         =   "1049"
         Begin VB.Menu mnuFormatMakeSameSizeItem 
            Caption         =   "1050"
            Index           =   0
         End
         Begin VB.Menu mnuFormatMakeSameSizeItem 
            Caption         =   "1051"
            Index           =   1
         End
         Begin VB.Menu mnuFormatMakeSameSizeItem 
            Caption         =   "1052"
            Index           =   2
         End
      End
      Begin VB.Menu mnuFormatBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormatSizeToGrid 
         Caption         =   "1053"
      End
      Begin VB.Menu mnuFormatBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormatHorizontalSpacing 
         Caption         =   "1054"
         Begin VB.Menu mnuFormatHorizontalSpacingItem 
            Caption         =   "1055"
            Index           =   0
         End
         Begin VB.Menu mnuFormatHorizontalSpacingItem 
            Caption         =   "1056"
            Index           =   1
         End
         Begin VB.Menu mnuFormatHorizontalSpacingItem 
            Caption         =   "1057"
            Index           =   2
         End
         Begin VB.Menu mnuFormatHorizontalSpacingItem 
            Caption         =   "1058"
            Index           =   3
         End
      End
      Begin VB.Menu mnuFormatVerticalSpacing 
         Caption         =   "1059"
         Begin VB.Menu mnuFormatVerticalSpacingItem 
            Caption         =   "1055"
            Index           =   0
         End
         Begin VB.Menu mnuFormatVerticalSpacingItem 
            Caption         =   "1056"
            Index           =   1
         End
         Begin VB.Menu mnuFormatVerticalSpacingItem 
            Caption         =   "1057"
            Index           =   2
         End
         Begin VB.Menu mnuFormatVerticalSpacingItem 
            Caption         =   "1058"
            Index           =   3
         End
      End
      Begin VB.Menu mnuFormatBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFormatCenter 
         Caption         =   "1064"
         Begin VB.Menu mnuFormatCenterItem 
            Caption         =   "1065"
            Index           =   0
         End
         Begin VB.Menu mnuFormatCenterItem 
            Caption         =   "1066"
            Index           =   1
         End
      End
      Begin VB.Menu mnuFormatBar3 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFormatOrder 
         Caption         =   "1067"
         Visible         =   0   'False
         Begin VB.Menu mnuFormatOrderItem 
            Caption         =   "1068"
            Index           =   0
         End
         Begin VB.Menu mnuFormatOrderItem 
            Caption         =   "1069"
            Index           =   1
         End
         Begin VB.Menu mnuFormatOrderItem 
            Caption         =   "1070"
            Index           =   2
         End
         Begin VB.Menu mnuFormatOrderItem 
            Caption         =   "1071"
            Index           =   3
         End
      End
   End
   Begin VB.Menu mnuRun 
      Caption         =   "1215"
      Begin VB.Menu mnuRunCompile 
         Caption         =   "1101"
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuRunBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRunHotsyncProject 
         Caption         =   "1035"
      End
      Begin VB.Menu mnuRunHotsyncRuntime 
         Caption         =   "1036"
      End
      Begin VB.Menu mnuRunHotsyncLibs 
         Caption         =   "1037"
      End
      Begin VB.Menu mnuRunSep3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRunPOSEstart 
         Caption         =   "1219"
      End
      Begin VB.Menu mnuRunPOSEProject 
         Caption         =   "1223"
      End
      Begin VB.Menu mnuRunPoseRuntime 
         Caption         =   "1217"
      End
      Begin VB.Menu mnuRunPOSELibs 
         Caption         =   "1222"
      End
      Begin VB.Menu mnuRunPOSEstartapp 
         Caption         =   "1220"
      End
      Begin VB.Menu mnuRunPOSEstop 
         Caption         =   "1221"
      End
      Begin VB.Menu mnuRunBar2 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuRunBuildOptions 
         Caption         =   "1216"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuRunBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDebugContinue 
         Caption         =   "3424"
         Shortcut        =   {F8}
      End
      Begin VB.Menu mnuCodeDebugStop 
         Caption         =   "3441"
      End
      Begin VB.Menu mnuCodeDebugWatch 
         Caption         =   "3425"
      End
      Begin VB.Menu mnuCodeDebugVariables 
         Caption         =   "3426"
      End
      Begin VB.Menu mnuCodeDebugCallStack 
         Caption         =   "3427"
      End
      Begin VB.Menu mnuCodeDebugBreakpointsClearThisModule 
         Caption         =   "3428"
      End
      Begin VB.Menu mnuCodeDebugBreakpointsClearAll 
         Caption         =   "3429"
      End
      Begin VB.Menu mnuDebugIgnoreBreakpoints 
         Caption         =   "3430"
      End
      Begin VB.Menu mnuRunRunImmediately 
         Caption         =   "3450"
      End
   End
   Begin VB.Menu mnuTools 
      Caption         =   "1072"
      Begin VB.Menu mnuToolsMenuEditor 
         Caption         =   "1073"
         Shortcut        =   ^E
      End
      Begin VB.Menu mnuToolsThemeEditor 
         Caption         =   "3454"
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   1
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   2
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   3
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   4
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   5
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   6
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   7
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   8
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   9
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   10
      End
      Begin VB.Menu mnuToolsList 
         Caption         =   ""
         Index           =   11
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
      Begin VB.Menu mnuWindowList 
         Caption         =   ""
         Index           =   0
      End
      Begin VB.Menu mnuWindowWindows 
         Caption         =   "1081"
         Visible         =   0   'False
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "1082"
      Begin VB.Menu mnuHelpReadme 
         Caption         =   "3452"
      End
      Begin VB.Menu mnuHelpTopics 
         Caption         =   "1084"
         Shortcut        =   {F1}
      End
      Begin VB.Menu mnuHelpHandbook 
         Caption         =   "3537"
      End
      Begin VB.Menu mnuHelpRegister 
         Caption         =   "1083"
      End
      Begin VB.Menu mnuHelpWWW 
         Caption         =   "1085"
      End
      Begin VB.Menu mnuHelpTutorials 
         Caption         =   "3445"
      End
      Begin VB.Menu mnuHelpTechNotes 
         Caption         =   "3352"
      End
      Begin VB.Menu mnuHelpPalmCreatorID 
         Caption         =   "1119"
      End
      Begin VB.Menu mnuHelpPOSE 
         Caption         =   "1305"
      End
      Begin VB.Menu mnuHelpBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpBook 
         Caption         =   "3536"
      End
      Begin VB.Menu mnuHelpBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "1086"
      End
   End
   Begin VB.Menu mnuRight 
      Caption         =   "Right-Click Menu"
      Visible         =   0   'False
      Begin VB.Menu mnuRightItem 
         Caption         =   "1500"
         Index           =   0
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1501"
         Index           =   1
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "-"
         Index           =   2
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1502"
         Index           =   3
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1503"
         Index           =   4
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "-"
         Index           =   5
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1504"
         Index           =   6
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1505"
         Index           =   7
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1506"
         Index           =   8
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1507"
         Index           =   9
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "-"
         Index           =   10
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1014"
         Index           =   11
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1015"
         Index           =   12
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1016"
         Index           =   13
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1017"
         Index           =   14
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "-"
         Index           =   15
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1508"
         Index           =   16
         Begin VB.Menu mnuRightAddItem 
            Caption         =   "1509"
            Index           =   0
         End
         Begin VB.Menu mnuRightAddItem 
            Caption         =   "1510"
            Index           =   1
         End
         Begin VB.Menu mnuRightAddItem 
            Caption         =   "1511"
            Index           =   2
         End
         Begin VB.Menu mnuRightAddItem 
            Caption         =   "-"
            Index           =   3
         End
         Begin VB.Menu mnuRightAddItem 
            Caption         =   "1512"
            Index           =   4
         End
         Begin VB.Menu mnuRightAddItem 
            Caption         =   "1513"
            Index           =   5
         End
         Begin VB.Menu mnuRightAddItem 
            Caption         =   "3359"
            Index           =   6
         End
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1028"
         Index           =   17
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1029"
         Index           =   18
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1514"
         Index           =   19
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1515"
         Index           =   20
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1030"
         Index           =   21
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "-"
         Index           =   22
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1516"
         Index           =   23
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1517"
         Index           =   24
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "3355"
         Index           =   25
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "-"
         Index           =   26
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1518"
         Index           =   27
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1519"
         Index           =   28
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1520"
         Index           =   29
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "3356"
         Index           =   30
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "-"
         Index           =   31
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "3390"
         Index           =   32
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "-"
         Index           =   33
      End
      Begin VB.Menu mnuRightItem 
         Caption         =   "1038"
         Index           =   34
      End
   End
   Begin VB.Menu mnuRightEditCode 
      Caption         =   "Edit menu for right-click in code window"
      Visible         =   0   'False
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1012"
         Index           =   0
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1013"
         Index           =   1
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "-"
         Index           =   2
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1014"
         Index           =   3
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1015"
         Index           =   4
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1016"
         Index           =   5
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1017"
         Index           =   6
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1018"
         Index           =   7
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "-"
         Index           =   8
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1019"
         Index           =   9
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1021"
         Index           =   10
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1022"
         Index           =   11
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "-"
         Index           =   12
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1181"
         Index           =   13
         Begin VB.Menu mnuRightEditAdvanced 
            Caption         =   "1182"
            Index           =   0
         End
         Begin VB.Menu mnuRightEditAdvanced 
            Caption         =   "1183"
            Index           =   1
         End
         Begin VB.Menu mnuRightEditAdvanced 
            Caption         =   "1184"
            Index           =   2
         End
         Begin VB.Menu mnuRightEditAdvanced 
            Caption         =   "1185"
            Index           =   3
         End
         Begin VB.Menu mnuRightEditAdvanced 
            Caption         =   "1186"
            Index           =   4
         End
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "-"
         Index           =   14
      End
      Begin VB.Menu mnuRightEdit 
         Caption         =   "1102"
         Index           =   15
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function SendMessage Lib "USER32" Alias "SendMessageA" (ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Any) As Long
Private Declare Function OSWinHelp% Lib "USER32" Alias "WinHelpA" (ByVal hWnd&, ByVal helpFile$, ByVal wCommand%, dwData As Any)
Private Declare Function AddFontResource Lib "GDI32" Alias "AddFontResourceA" (ByVal p1 As String) As Long
Private Declare Function RemoveFontResource Lib "GDI32" Alias "RemoveFontResourceA" (ByVal p1 As String) As Long
Const EM_UNDO = &HC7
Const HWND_BROADCAST = &HFFFF
Const WM_FONTCHANGE = 29

Dim gnToolboxTool As Integer
Dim m_bSizing As Boolean
Public Children As New Collection
Public ActiveFormIsCode As Boolean
Private m_nGlobalIDSerial As Integer
Private fCodeDebug As frmCode
Public bCMaxFindFlag As Boolean

Private Sub cmaxFind_Change()
   gbFindOne = True
End Sub

Private Sub cmaxFind_FindWrapped(ByVal lCmd As CodeMax4Ctl.cmCommand, ByVal bForward As Boolean)
   If (UBound(garrSearchMap) <> gnSearchLoc) Or (gnFindFlags And kFindSelected) Then
      cmaxFind.CancelEvent
      gbFindAbort = True
      Exit Sub
   End If
   If gnFindFlags And kFindProject Then
      cmaxFind.CancelEvent
      gbFindAbort = True
      Exit Sub
   Else
   If MsgBox(gStringTable(3444), vbYesNo) <> vbYes Then 'The end of the module was reached, do you want to continue searching from the beginning?
      cmaxFind.CancelEvent
      gbFindAbort = True
'        cmaxFind_FindWrapped = True
      End If
   End If
   If UBound(garrSearchMap) = 0 Then
      'Need to come up with a way to stop infinite looping within a single module
'      cmaxFind_FindWrapped = False
   Else
      'cmaxFind_FindWrapped = True
      cmaxFind.CancelEvent
'      FindWrapped = True
   End If
'   If gbReplaceAll Then Exit Sub
'   If MsgBox("The end of the module was reached, do you want to continue searching from the beginning?", vbYesNo) <> vbYes Then
'      cmaxFind.CancelEvent
'      gbFindAbort = True
'   End If
End Sub

Private Sub cmaxFind_ModifiedChange()
   gbReplaceChange = True
End Sub

Private Sub cmaxFind_SelChange()
'Private Sub cmaxFind_SelChange(ByVal Control As CodeMax4Ctl.CodeMax)
Dim sel As range

   If bCMaxFindFlag Then Exit Sub
   'Please review - MMD
   Set sel = cmaxFind.GetSel(True)
   If Not sel.IsEmpty Then
''      If gnFindFlags And kFindSelected Then
'''         cmaxFind.Text = GetScript(garrSearchMap(gnSearchLoc))
''         If sel.StartLineNo = 0 Then
''            sel.StartColNo = sel.StartColNo + gSearchSel.StartColNo
''            If sel.EndLineNo = 0 Then
''               sel.EndColNo = sel.EndColNo + gSearchSel.StartColNo
''            End If
''         Else
''            sel.StartLineNo = sel.StartLineNo + gSearchSel.StartLineNo
''            sel.EndLineNo = sel.EndLineNo + gSearchSel.StartLineNo
''         End If
''         cmaxFind.SetSel sel, True
'''         sel.StartColNo = gSearchSel.StartColNo + sel.StartColNo
'''         sel.StartLineNo = gSearchSel.StartLineNo + sel.StartLineNo
'''         sel.EndColNo = gSearchSel.EndColNo + sel.EndColNo
'''         sel.EndLineNo = gSearchSel.EndLineNo + sel.EndLineNo
''      End If
      gbFindOne = True
      gbFindAny = True
   End If
End Sub

Private Sub MDIForm_Load()
Dim strProj As String
Dim bShowSplash As Boolean
Dim trace As Boolean
trace = True

If trace Then MsgBox 1
   If Not allowRegistration Then
      Load frmDemoSplash
      frmDemoSplash.Show 1
   End If
   CheckForPalmFonts
If trace Then MsgBox 2

   m_nGlobalIDSerial = 1
If trace Then MsgBox 3

   LoadResStrings Me
If trace Then MsgBox 4
   gnToolboxTool = 1
   Me.Left = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "MainLeft", 450)
   Me.Top = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "MainTop", 450)
   Me.Width = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "MainWidth", 12450)
   Me.Height = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "MainHeight", 9450)
   picPanel.Width = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "MainPanel1", picPanel.Width)
   picSplit.Tag = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "MainPanel2", 50)
   ShowStatus
If trace Then MsgBox 5

   gbWinNT2000 = (SysInfo.OSPlatform = 2)
   gbWinNT2000 = True

   DoEvents
 If trace Then MsgBox 6
   gfToolbox.DockWindow
If trace Then MsgBox 7
   gfProjectExplorer.DockWindow
If trace Then MsgBox 8
  gfProperties.DockWindow
If trace Then MsgBox 9
  
   ParseCommandLine 'Were we started from command line?
   If gCommandLineProject <> "" Then
If trace Then MsgBox 9.1
      OpenProject gCommandLineProject
   Else
If trace Then MsgBox 9.2
      bShowSplash = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "ShowSplash", True)
If trace Then MsgBox 9.3
      If bShowSplash Then
If trace Then MsgBox 9.4
         strProj = ShowNewOpen(True)
         If StrComp(strProj, "Project File", vbTextCompare) = 0 Then
If trace Then MsgBox 9.5
            LoadNewProject
         Else
If trace Then MsgBox 9.6
            If Len(strProj) > 0 And Right(LCase(strProj), 4) = ".prj" Then OpenProject strProj
         End If
      Else
If trace Then MsgBox 9.7
         LoadNewProject
      End If
   End If
If trace Then MsgBox 10
   
   UpdateMRU
If trace Then MsgBox 11
   UpdateTools
If trace Then MsgBox 12
   SetWindowList
   #If NSBSymbian = 0 Then
   If gbLaunchPOSE Or gbLaunchSimulator Then mnuRunPOSEstart_Click
   #End If
   If InStr(gCommandLineOptions, "-compile") Then CompileImmediately
   Set fCodeDebug = New frmCode
   fCodeDebug.Visible = False
If trace Then MsgBox 13
    'Load frmShowVariables   'added 04012005
    'Load frmShowCallStack   'added 04012005
    
#If NSBSymbian = 1 Then
   mnuRunHotsyncProject.Visible = False
   mnuRunHotsyncRuntime.Visible = False
   mnuRunHotsyncLibs.Visible = False
   mnuRunPOSEProject.Visible = False
   mnuRunPOSEstartapp.Visible = False
   mnuRunPOSELibs.Visible = False
   mnuRunPOSEstart.Visible = False
   mnuRunPOSEstop.Visible = False
   mnuRunPoseRuntime.Visible = False
   mnuCodeDebugStop.Visible = False
   mnuDebugContinue.Visible = False
   mnuCodeDebugVariables.Visible = False
   mnuCodeDebugCallStack.Visible = False
   mnuCodeDebugWatch.Visible = False
   mnuCodeDebugBreakpointsClearThisModule.Visible = False
   mnuCodeDebugBreakpointsClearAll.Visible = False
   mnuDebugIgnoreBreakpoints.Visible = False
   mnuRunBar1.Visible = False
   mnuRunBar2.Visible = False
   mnuRunBar3.Visible = False
   mnuRunSep3.Visible = False
   mnuHelpPOSE.Visible = False
   mnuHelpPalmCreatorID.Visible = False
   mnuHelpBar1.Visible = False
   mnuHelpBook.Visible = False
#Else
   mnuRunRunImmediately.Visible = False
#End If

End Sub

Private Sub LoadNewProject()
Dim proj As New CProject
Dim openProj As CProject
Dim i As Integer
Dim strname As String

   'Reset find when a new project is opened
   gbNewFind = True
   'Ensure project has unique name
   i = 0
   strname = ""
   Do While Len(strname) = 0
      i = i + 1
      strname = "Project" & i
      For Each openProj In gProjects
         If StrComp(openProj.Name, strname, vbTextCompare) = 0 Then
            strname = ""
         End If
      Next
   Loop
   'Assign global ID #
   proj.GlobalID = m_nGlobalIDSerial
   m_nGlobalIDSerial = m_nGlobalIDSerial + 1
   proj.Name = strname
   proj.AddNewForm
   AddProject proj
   DoEvents
   If gbProjectExplorer Then gfProjectExplorer.ShowActive proj
End Sub

Private Sub OpenProject(ByVal strProj As String)
Dim strPath As String
Dim proj As New CProject
Dim openProj As CProject

   'Assign global ID #
   proj.GlobalID = m_nGlobalIDSerial
   m_nGlobalIDSerial = m_nGlobalIDSerial + 1
   'Reset find when a project is opened
   gbNewFind = True
   If proj.OpenProject(strProj) Then
      'Ensure project has unique name
      For Each openProj In gProjects
         If StrComp(openProj.Name, proj.Name, vbTextCompare) = 0 Then
            MsgBox gStringTable(3327) + proj.Name '("A project named " + proj.Name + " is already open"
            Set proj = Nothing
            Exit Sub
         End If
      Next

      'Store path from last opened project
      strPath = Left(strProj, InStrRev(strProj, "\") - 1)
      SetRegValue MWinReg.hKey, MWinReg.SubKey, "RecentPath", strPath
   Else
      MsgBox gStringTable(3328) & " " & strProj '"Unable to open project file '" + strProj + "'"
      Set proj = Nothing
      Exit Sub
   End If
   AddProject proj
   DoEvents
   If gbProjectExplorer Then gfProjectExplorer.ShowActive proj
End Sub

Private Sub AddProject(proj As CProject)
Dim frm As CForm, frmX As CForm
Dim fPalmScreen As New frmPalmScreen

'   'Assign global ID #
'   proj.GlobalID = m_nGlobalIDSerial
'   m_nGlobalIDSerial = m_nGlobalIDSerial + 1

   gProjects.Add proj, proj.GlobalID
'   gstr Target = proj.Name
   Set gTarget = proj

   'Pick a form to open, the default form or the first form
   Set frm = proj.FormCollection.Item(1)
   For Each frmX In proj.FormCollection
      If frmX.IsDefaultForm Then
         Set frm = frmX
         Exit For
      End If
   Next

   gfProjectExplorer.DisplayExplorer
   addThemeToResources
   UpdateProjectList
   
   gbUIBitmapScreenDrawHappening = False
   fPalmScreen.Object = frm
   fPalmScreen.Move 0, 0
   fPalmScreen.Show
   AddMDIChild fPalmScreen
   
End Sub

Private Function RemoveProject(ByVal proj As CProject) As Boolean
Dim frm As Form
Dim obj As Object
Dim nAction As Integer
Dim cMod As CCodeModule
Dim fCode As frmCode
Dim bDirty As Boolean

   'If nothing is open, remove is already successful
   If proj Is Nothing Then
      RemoveProject = True
      Exit Function
   End If

   'Find out if project is dirty
   bDirty = proj.Dirty
   If Not bDirty Then
      For Each frm In Children
         If proj Is LocateProject(frm.GlobalID) Then
            If frm.Dirty Then
               bDirty = True
               Exit For
            End If
         End If
      Next
   End If

   If bDirty Then
      nAction = MsgBox(gStringTable(3329) & proj.Name & "?", vbYesNoCancel) 'save
      If nAction = vbCancel Then Exit Function
   End If
   RemoveProject = True

   'Close all project windows
   For Each frm In Children
      If proj Is LocateProject(frm.GlobalID) Then
         Unload frm
      End If
   Next
   For Each cMod In proj.CodeCollection
      Set frm = GetMDIChild(cMod.GlobalID & "|code")
      If Not frm Is Nothing Then Unload frm
   Next
   If nAction = vbYes Then SaveProject proj

   'Remove from Project Explorer
   gfProjectExplorer.RemoveNode proj.GlobalID

   'Clear Properties Window
   If gbProperties Then gfProperties.Object = Nothing

   gProjects.Remove proj.GlobalID
   If gProjects.count > 0 Then
      Set gTarget = gProjects(1)
   Else
      Set gTarget = Nothing
   End If
   UpdateProjectList
End Function



Private Sub MDIForm_QueryUnload(Cancel As Integer, UnloadMode As Integer)
Dim proj As CProject

   For Each proj In gProjects
      If proj.Dirty Then
         Select Case MsgBox(gStringTable(3329) & proj.Name & "?", vbYesNoCancel)
         Case vbYes: SaveProject proj
         Case vbNo
         Case vbCancel
            Cancel = 1
            Exit For
         End Select
      End If
   Next
End Sub

Private Sub MDIForm_Resize()
   'MsgBox "resize " & Me.Height & " " & Me.Width
   If Me.Width < 320 Then Me.Width = 320
   If Me.Height < 320 Then Me.Height = 320
End Sub

Private Sub MDIForm_Unload(Cancel As Integer)
Dim fontDir As String
Dim lParam As Long
Dim i As Integer

'   If Not dlgCommonDialog Is Nothing Then Unload dlgCommonDialog
   If Me.WindowState = vbNormal Then
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "MainLeft", Me.Left
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "MainTop", Me.Top
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "MainWidth", Me.Width
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "MainHeight", Me.Height
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "MainPanel1", picPanel.Width
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "MainPanel2", picSplit.Tag
   End If

   If frmMain.tcpServer.state = sckConnected Then frmMain.tcpServer.SendData "quit"
   frmMain.tcpServer.Close
      
   fontDir = ProgramsDirectory & "\fonts\"
   lParam = 0
   For i = 0 To 7
      RemoveFontResource (fontDir & gstrPalmFonts(i) & ".fon")
   Next
   SendMessage HWND_BROADCAST, WM_FONTCHANGE, 0, lParam
End Sub

Private Sub mnuHelpTechNotes_Click()
   Dim techNotes As String
   techNotes = ProgramsDirectory & "\technotes\index.htm"
   openWebPage techNotes
End Sub

Private Sub mnuEdit_Click()
Dim fCode As frmCode

   If ActiveForm Is Nothing Then
      mnuEditUndo.Enabled = False
      mnuEditRedo.Enabled = False
      mnuEditCut.Enabled = False
      mnuEditCopy.Enabled = False
      mnuEditPaste.Enabled = False
      mnuEditDelete.Enabled = False
      mnuEditSelectAll.Enabled = False
      mnuEditGoTo.Enabled = False
   Else
      Select Case typename(ActiveForm)
      Case "frmPalmScreen"
         mnuEditUndo.Enabled = False
         mnuEditRedo.Enabled = False
         mnuEditCut.Enabled = ActiveForm.Selection.count > 0
         mnuEditCopy.Enabled = True
         mnuEditPaste.Enabled = ActiveForm.ValidPaste
         mnuEditDelete.Enabled = ActiveForm.Selection.count > 0
         mnuEditSelectAll.Enabled = True
         mnuEditGoTo.Enabled = False
      Case "frmCode"
         Set fCode = ActiveForm
         mnuEditUndo.Enabled = fCode.CanUndo
         mnuEditRedo.Enabled = fCode.CanRedo
         mnuEditCut.Enabled = fCode.CanCut
         mnuEditCopy.Enabled = fCode.CanCopy
         mnuEditPaste.Enabled = ActiveForm.ValidPaste
         mnuEditDelete.Enabled = fCode.CanCopy
         mnuEditSelectAll.Enabled = True
         mnuEditGoTo.Enabled = True
      End Select
   End If
   mnuEditFind.Enabled = (Not gTarget Is Nothing)
   mnuEditFindNext.Enabled = (Not gTarget Is Nothing)
   mnuEditReplace.Enabled = (Not gTarget Is Nothing)
End Sub

Private Sub mnuEditDelete_Click()
   If ActiveForm Is Nothing Then Exit Sub
   Select Case typename(ActiveForm)
      Case "frmPalmScreen", "frmCode": ActiveForm.Delete
   End Select
End Sub

Private Sub mnuEditFind_Click()
   PutTheCodeBack
   frmFind.Form = ActiveForm
   frmFind.FindReplace = False
   frmFind.Show vbModal
End Sub

Private Sub mnuEditGoTo_Click()
   If ActiveForm Is Nothing Then Exit Sub
   If typename(ActiveForm) <> "frmCode" Then Exit Sub
   ActiveForm.GoToLine
End Sub

Private Sub mnuEditPreferences_Click()
'Dim fPreferences As New frmPreferences

'   fPreferences.Show vbModal
End Sub

Private Sub mnuEditRedo_Click()
   ActiveForm.Redo
End Sub

Private Sub mnuEditReplace_Click()
   PutTheCodeBack
   frmFind.Form = ActiveForm
   frmFind.FindReplace = True
   frmFind.Show vbModal
End Sub

Private Sub mnuEditSelectAll_Click()
   If ActiveForm Is Nothing Then Exit Sub
   Select Case typename(ActiveForm)
   Case "frmPalmScreen", "frmCode": ActiveForm.SelectAll
   End Select
End Sub

Private Sub mnuFile_Click()
   Me.mnuFileMRU(1) = Me.mnuFormat
End Sub

Private Sub mnuFileMRU_Click(index As Integer)
Dim proj As CProject

   For Each proj In gProjects
      If proj.pathname = mnuFileMRU(index).Tag And proj.Saved Then
         MsgBox gStringTable(3330) '"Project is already open"
         Exit Sub
      End If
   Next
   'This line commented out to prevent multiple projects open at once.
'   OpenProject mnuFileMRU(index).Tag
   If RemoveProject(gTarget) Then OpenProject mnuFileMRU(index).Tag
End Sub

Private Sub mnuFileSaveProject_Click()
Dim proj As CProject

   ShowStatus gStringTable(3231), True '"Saving..."
   'If Not ActiveForm Is Nothing Then Set proj = LocateProject(ActiveForm.GlobalID)
   'If proj Is Nothing Then Set proj = gTarget
   Set proj = gTarget
   If proj Is Nothing Then Exit Sub
   PutTheCodeBack
   SaveProject proj
End Sub

Private Sub SaveProject(ByVal proj As CProject)
Dim i As Integer
Dim k As Integer
Dim strRecent(20) As String

   'Check this flag, sending to Save As if project has never been saved
   If Not proj.Saved Then
      mnuFileSaveProjectAs_Click
      Exit Sub
   End If

   proj.Save

   'Manage recent files list
   strRecent(0) = proj.pathname
   If Dir(fileDirectory + "\recent.dat", vbNormal) = "" Then
      For i = 1 To UBound(strRecent)
         strRecent(i) = ""
      Next
   Else
      Open fileDirectory + "\recent.dat" For Input As #1
      For i = 1 To UBound(strRecent)
         Input #1, strRecent(i)
      Next
      Close #1
   End If
   
   'Ensure no duplicates...
   For i = 1 To UBound(strRecent)
      If StrComp(strRecent(0), strRecent(i), vbTextCompare) = 0 Then strRecent(i) = ""
   Next

   'Now, write out the pathnames
   Open fileDirectory + "\recent.dat" For Output As #1
   k = 0
   For i = 0 To UBound(strRecent)
      If strRecent(i) <> "" Then
         k = k + 1
         Write #1, strRecent(i)
      End If
   Next
   Do While k < UBound(strRecent)
      Write #1, ""
      k = k + 1
   Loop
   Close #1
   UpdateMRU
   proj.Dirty = False
gotCancel:
   On Error GoTo 0
End Sub

Private Sub mnuFileSaveProjectAs_Click()
Dim proj As CProject

   
   If Not ActiveForm Is Nothing And typename(ActiveForm) <> "frmProperties" Then Set proj = LocateProject(ActiveForm.GlobalID)
   If proj Is Nothing Then Set proj = gTarget
   If proj Is Nothing Then Exit Sub

   dlgCommonDialog.DialogTitle = "Save Project As"
   dlgCommonDialog.CancelError = True
   dlgCommonDialog.DefaultExt = "prj"
   dlgCommonDialog.Filter = "Project Files(*.prj)|*.prj"
   dlgCommonDialog.filename = proj.pathname
   dlgCommonDialog.flags = cdlOFNLongNames + cdlOFNNoReadOnlyReturn + cdlOFNOverwritePrompt
   On Error GoTo gotCancel
   dlgCommonDialog.ShowSave

   proj.pathname = dlgCommonDialog.filename
   proj.Saved = True
   'Save As merely sets the Saved flag, then lets Save do all the work
   mnuFileSaveProject_Click
gotCancel:
   Exit Sub
End Sub

Private Sub mnuFormat_Click()
Dim bEnabled As Boolean
Dim i As Integer

   If Not ActiveForm Is Nothing Then
      If typename(ActiveForm) = "frmPalmScreen" Then bEnabled = True
   End If
   For i = 0 To mnuFormatAlignItem.UBound
      If mnuFormatAlignItem(i).caption <> "-" Then mnuFormatAlignItem(i).Enabled = bEnabled
   Next
   For i = 0 To mnuFormatMakeSameSizeItem.UBound
      If mnuFormatMakeSameSizeItem(i).caption <> "-" Then mnuFormatMakeSameSizeItem(i).Enabled = bEnabled
   Next
   mnuFormatSizeToGrid.Enabled = bEnabled
   For i = 0 To mnuFormatCenterItem.UBound
      If mnuFormatCenterItem(i).caption <> "-" Then mnuFormatCenterItem(i).Enabled = bEnabled
   Next
   For i = 0 To mnuFormatHorizontalSpacingItem.UBound
      If mnuFormatHorizontalSpacingItem(i).caption <> "-" Then mnuFormatHorizontalSpacingItem(i).Enabled = bEnabled
   Next
   For i = 0 To mnuFormatVerticalSpacingItem.UBound
      If mnuFormatVerticalSpacingItem(i).caption <> "-" Then mnuFormatVerticalSpacingItem(i).Enabled = bEnabled
   Next
End Sub

Private Sub mnuFormatAlignItem_Click(index As Integer)
   'Lefts, Centers, Rights, -, Tops, Middles, Bottoms, -, Grid
   ActiveForm.Format 0, index
End Sub

Private Sub mnuFormatCenterItem_Click(index As Integer)
   'Horizontally, Vertically
   ActiveForm.Format 5, index
End Sub

Private Sub mnuFormatHorizontalSpacingItem_Click(index As Integer)
   'Equal, Increase, Decrease, Remove
   ActiveForm.Format 3, index
End Sub

Private Sub mnuFormatMakeSameSizeItem_Click(index As Integer)
   'Width, Height, Both
   ActiveForm.Format 1, index
End Sub

Private Sub mnuFormatOrderItem_Click(index As Integer)
   'Front, Forward, Backward, Back
   ActiveForm.Format 6, index
End Sub

Private Sub mnuFormatSizeToGrid_Click()
   'Size To Grid
   ActiveForm.Format 2, 0
End Sub

Private Sub mnuFormatVerticalSpacingItem_Click(index As Integer)
   'Equal, Increase, Decrease, Remove
   ActiveForm.Format 4, index
End Sub

Private Sub mnuHelpPalmCreatorID_Click()
   openWebPage "http://www.accessdevnet.com/index.php/ACCESS-Tools/View-category.html"
End Sub

Private Sub mnuHelpPOSE_Click()
   openWebPage "http://www.accessdevnet.com/index.php/ACCESS-Tools/View-category.html"
End Sub

Private Sub mnuHelpRegister_Click()
   frmRegister.Show vbModal, Me
End Sub

Private Sub mnuHelpTopics_Click()
   Dim helpFile As String
   
   helpFile = ProgramsDirectory & "\Lang\" & gLanguage & ".chm"
   On Error GoTo tryhlp
   Open helpFile For Input As #99
   Close #99
   GoTo getHelp
   
tryhlp:
   Resume tryhlp1
tryhlp1:
   helpFile = ProgramsDirectory & "\Lang\" & gLanguage & ".hlp"
   On Error GoTo useEnglish
   Open helpFile For Input As #99
   Close #99
   GoTo getHelp
   
useEnglish:
   On Error GoTo 0
   helpFile = ProgramsDirectory & "\Lang\English.chm"
   
getHelp:
   On Error GoTo 0
   If Right(helpFile, 3) = "chm" Then
      err = ShellExecute(0, "Open", helpFile, vbNullString, vbNullString, 5)
   Else
      dlgCommonDialog.helpFile = helpFile
      dlgCommonDialog.HelpCommand = cdlHelpContents
      dlgCommonDialog.HelpContext = 0
      dlgCommonDialog.ShowHelp
   End If
End Sub
Private Sub mnuHelpBook_Click()
   Dim filename As String
   filename = ProgramsDirectory & "\nsb4palmosfree.pdf"
   err = ShellExecute(0, "Open", filename, vbNullString, vbNullString, 5)
End Sub
Private Sub mnuHelpHandbook_Click()
   Dim filename As String
   filename = ProgramsDirectory & "\lang\Handbook.pdf"
   err = ShellExecute(0, "Open", filename, vbNullString, vbNullString, 5)
End Sub

Private Sub mnuHelpTutorials_Click()
   Dim tutorials As String
   tutorials = ProgramsDirectory & "\technotes\TT.index.htm"
   openWebPage tutorials
End Sub
Private Sub mnuHelpReadme_Click()
   Dim tutorials As String
   tutorials = ProgramsDirectory & "\Readme.htm"
   openWebPage tutorials
End Sub

Private Sub mnuProject_Click()
   mnuProjectAddForm.Enabled = (Not gTarget Is Nothing)
   mnuProjectAddMenu.Enabled = (Not gTarget Is Nothing)
   mnuProjectAddBitmap.Enabled = (Not gTarget Is Nothing)
   mnuProjectAddNewModule.Enabled = (Not gTarget Is Nothing)
   mnuProjectAddExistingModule.Enabled = (Not gTarget Is Nothing)
   mnuProjectAddResource.Enabled = (Not gTarget Is Nothing)
   mnuProjectStartupCode.Enabled = (Not gTarget Is Nothing)
   mnuProjectTerminationCode.Enabled = (Not gTarget Is Nothing)
   'mnuProjectSetTarget.Enabled = (Not gTarget Is Nothing)
   'If gTarget Is Nothing Then Exit Sub
End Sub

Private Sub mnuProjectAddBitmap_click()
   ProjectAddBitmap
End Sub
Private Sub mnuProjectAddResource_click()
   ProjectAddResource
End Sub

Private Sub mnuProjectAddExistingModule_Click()
   ProjectAddModuleExisting
End Sub

Private Sub mnuProjectAddForm_click()
   ProjectAddForm
End Sub

Private Sub mnuProjectAddMenu_Click()
   ProjectAddMenu
End Sub

Private Sub mnuProjectAddNewModule_Click()
   ProjectAddModuleNew
End Sub

Private Sub mnuProjectSetTargetList_Click(index As Integer)
   'This allows the user to manually change the target project
   Set gTarget = LocateObject(mnuProjectSetTargetList(index).Tag)
   UpdateProjectList
End Sub

Private Sub mnuProjectStartupCode_Click()
   ViewCode gTarget.GlobalID, "startup"
End Sub

Private Sub mnuProjectTerminationCode_Click()
   ViewCode gTarget.GlobalID, "termination"
End Sub

'Translate to mnuRightItem equivalent
Private Sub mnuRightAddItem_Click(index As Integer)
   Select Case index
   Case 0, 1: mnuRightItem_Click index + 17
   Case Else: mnuRightItem_Click index + 19
   End Select
End Sub

Private Sub mnuRightEdit_Click(index As Integer)
   Select Case index
   Case 0: ActiveForm.Undo
   Case 1: ActiveForm.Redo
   'Case 2
   Case 3: ActiveForm.Cut
   Case 4: ActiveForm.Copy
   Case 5: ActiveForm.Paste
   Case 6: ActiveForm.Delete
   Case 7: ActiveForm.SelectAll
   'Case 8
   Case 9: mnuEditFind_Click
   Case 10: mnuEditReplace_Click
   Case 11: mnuEditGoTo_Click
   'Case 12
   Case 13 'Advanced
   'Case 14
   Case 15: 'ActiveForm.Editor.ExecuteCommand
   End Select
End Sub

Private Sub mnuRightEditAdvanced_Click(index As Integer)
   Select Case index
   Case 0: mnuRightEditAdvanced(0).Checked = ActiveForm.ShowWhitespace
   Case 1: ActiveForm.CommentSelection True
   Case 2: ActiveForm.CommentSelection False
   Case 3: ActiveForm.SetRepeatCount
   Case 4: ActiveForm.ExecuteCommand
   End Select
End Sub

Private Sub mnuRightEditCode_Click()
   mnuRightEdit(0).Enabled = ActiveForm.CanUndo
   mnuRightEdit(1).Enabled = ActiveForm.CanRedo
   '-
   mnuRightEdit(3).Enabled = ActiveForm.CanCut
   mnuRightEdit(4).Enabled = ActiveForm.CanCopy
   If ActiveForm.CanPaste Then
      If Left(Clipboard.GetText, Len(kClipboardHeader)) = kClipboardHeader Then
         mnuRightEdit(5).Enabled = False
      Else
         mnuRightEdit(5).Enabled = True
      End If
   End If
   mnuRightEdit(6).Enabled = ActiveForm.CanCut
End Sub

'0  View O&bject              1500
'1  View C&ode                1501
'2  -
'3  View &Startup Code        1502
'4  View &Termination Code    1503
'5  -
'6  View &Before Code         1504
'7  View &After Code          1505
'8  View &Event Code          1506
'9  View &Help Code           1507
'10 -
'11 Cu&t                   1014
'12 &Copy                  1015
'13 &Paste                 1016
'14 &Delete                1017
'15 -
'16 &Add                      1508
'-0  &Form                    1509
'-1  &Menu                    1510
'-2  &Bitmap                  1511
'-3  -
'-4  &New Module              1512
'-5  &Existing Module...      1513
'-6  &Resource                3359
'17 Add &Form              1028
'18 Add &Menu              1029
'19 Add &MenuBar              1514
'20 Add &Dropdown             1515
'21 Add &Bitmap            1030
'22 -
'23 Add &New Module           1516
'24 Add &Existing Module...   1517
'25 Add &Resource             3355
'26 -
'27 &Close Project            1518
'28 Re&move Bitmap            1519
'29 Re&move Module            1520
'30 Re&move Resource          3356
'31 -
'32 Reorder...       3390
'33 -
'34 P&roperties...         1038
Private Sub mnuRightItem_Click(index As Integer)
Dim nClickSource As Integer
Dim strGlobalID As String
Dim obj As Object
Dim proj As CProject
Dim frm As frmCode
Dim mElem As CMenuElem
Dim fPalmScreen As frmPalmScreen
Dim nod As MSComctlLib.Node

'   nClickSource = Left(mnuRight.Tag, 1)
   strGlobalID = Mid(mnuRight.Tag, 2)
   Set obj = LocateObject(strGlobalID)
   Set proj = LocateProject(strGlobalID)

   Select Case index
   Case 0: ViewObject strGlobalID
   Case 1: ViewCode strGlobalID, "code"
   Case 3: ViewCode strGlobalID, "startup"
   Case 4: ViewCode strGlobalID, "termination"
   Case 6 'View Before Code
      Set fPalmScreen = GetMDIChild(strGlobalID)
      If Not fPalmScreen Is Nothing Then fPalmScreen.ClearSelection
      ViewCode strGlobalID, "before"
   Case 7 'View After Code
      Set fPalmScreen = GetMDIChild(strGlobalID)
      If Not fPalmScreen Is Nothing Then fPalmScreen.ClearSelection
      ViewCode strGlobalID, "after"
   Case 8 'View Event Code
      Set fPalmScreen = GetMDIChild(strGlobalID)
      If Not fPalmScreen Is Nothing Then fPalmScreen.ClearSelection
      ViewCode strGlobalID, "event"
   Case 9 'View Help Code
      Set fPalmScreen = GetMDIChild(strGlobalID)
      If Not fPalmScreen Is Nothing Then fPalmScreen.ClearSelection
      ViewCode strGlobalID, "help"
   Case 11, 12, 14 'Cut, Copy, Delete
      If index = 11 Or index = 12 Then Clipboard.SetText kClipboardHeader & vbCrLf & obj.Copy
      If index = 11 Or index = 14 Then
         Select Case typename(obj)
         Case "CForm": ProjectRemoveForm obj, proj
         Case "CMenu": ProjectRemoveMenu obj, proj
         Case "CMenuBar": ProjectRemoveMenuBar obj, proj
         Case "CMenuElem": ProjectRemoveMenuElem obj, proj
         Case Else: FormRemoveObject obj.obj.Form, obj
         End Select
         proj.Dirty = True
      End If
   Case 13 'Paste
      Dim strLines() As String
      strLines = Split(Clipboard.GetText, vbCrLf)
      Select Case typename(obj)
      Case "CProject", "CForm": obj.Paste strLines
      Case "CMenu"
         obj.Paste strLines, proj
         gfProjectExplorer.AddNewMenuBar obj.MenuBars(obj.MenuBars.count), obj
         For Each mElem In obj.MenuBars(obj.MenuBars.count).MenuElems
            gfProjectExplorer.AddNewMenuElem mElem, obj.MenuBars(obj.MenuBars.count)
         Next
      Case "CMenuBar"
         obj.Paste strLines, proj
         gfProjectExplorer.AddNewMenuElem obj.MenuElems(obj.MenuElems.count), obj
      End Select
      proj.Dirty = True
   Case 17: ProjectAddForm proj
   Case 18: ProjectAddMenu proj
   Case 19: ProjectAddMenuBar obj, proj
   Case 20: ProjectAddMenuElem obj, proj
   Case 21: ProjectAddBitmap proj
   Case 23: ProjectAddModuleNew proj
   Case 24: ProjectAddModuleExisting proj
   Case 25: ProjectAddResource proj
   Case 27: RemoveProject proj
   Case 28 'Remove Bitmap
      'Remove it from the project, Project Explorer, and Properties Window
      proj.RemoveBitmap strGlobalID
      gfProjectExplorer.RemoveNode strGlobalID
      If gbProperties Then gfProperties.Object = proj
   Case 29 'Remove Module
      'MMD: This is going to be hacky, maybe the admission will help me feel better about it

      'Make sure the module isn't open in an editor
      Set frm = GetMDIChild(strGlobalID & "|code")
      If Not frm Is Nothing Then
         If frm.Dirty Then
            Select Case MsgBox(gStringTable(3331), vbQuestion + vbYesNoCancel) 'Module has been changed, do you want to save?
            Case vbYes: frm.PutTheCodeBack
            Case vbNo: frm.Dirty = False
            Case vbCancel: Exit Sub
            End Select
         End If
         Unload frm
      End If
      Set proj = LocateObject(gfProjectExplorer.expl.SelectedItem.Parent.Tag)

      'Remove it from the project, Project Explorer, and Properties Window
      proj.RemoveModule strGlobalID
      'MMD: Why all this project explorer code ended up here is a mystery to me, too...
      Set nod = gfProjectExplorer.expl.SelectedItem.Parent
      gfProjectExplorer.expl.Nodes.Remove gfProjectExplorer.expl.SelectedItem.index
      'MMD: One would think that a node that was empty would know better than to be expanded
      If nod.Children = 0 Then nod.Expanded = False
      If gbProperties Then gfProperties.Object = proj
   Case 30 'remove resource
      'Remove it from the project, Project Explorer, and Properties Window
      proj.RemoveResource strGlobalID
      gfProjectExplorer.RemoveNode strGlobalID
   Case 32 'Reorder forms
      Dim fReorder As New frmReorder
      If typename(obj) = "CForm" Then
         Set fReorder.gForm = obj
      Else
         Set fReorder.gProj = proj
      End If
      fReorder.Show vbModal
   Case 34 'Properties
      If Not gbProperties Then gfProperties.DockWindow
      gfProperties.Object = obj
   End Select
End Sub

Private Sub mnuRun_Click()
If gTarget Is Nothing Then
      mnuRunCompile.caption = mnuRunCompile.Tag
      mnuRunCompile.Enabled = False
      mnuRunHotsyncProject.caption = mnuRunHotsyncProject.Tag
      mnuRunHotsyncProject.Enabled = False
      mnuRunPOSEProject.caption = mnuRunPOSEProject.Tag
      mnuRunPOSEProject.Enabled = False
      mnuRunPOSEstartapp.caption = mnuRunPOSEstartapp.Tag
      mnuRunPOSEstartapp.Enabled = False
   Else
      mnuRunCompile.caption = mnuRunCompile.Tag & gTarget.Name ' & "          F5"
      mnuRunCompile.Enabled = True
      mnuRunHotsyncProject.caption = mnuRunHotsyncProject.Tag & gTarget.Name
      mnuRunHotsyncProject.Enabled = True
      mnuRunPOSEProject.caption = mnuRunPOSEProject.Tag & gTarget.Name
      mnuRunPOSEProject.Enabled = True
      mnuRunPOSEstartapp.caption = mnuRunPOSEstartapp.Tag & gTarget.Name
      mnuRunPOSEstartapp.Enabled = True
   End If
   
   If DownloadOption = "POSE" Then
      mnuRunPOSEstart.caption = mnuRunPOSEstart.Tag
      mnuRunPOSEstart.Enabled = True
   ElseIf DownloadOption = "Simulator" Then
      mnuRunPOSEstart.caption = gStringTable(3380)
      mnuRunPOSEstart.Enabled = True
   Else
      mnuRunPOSEstart.Enabled = False
   End If
   
   If gbDebugMode Then
      If gbAtBreakPoint Then
         mnuRunCompile = False
         mnuRunPOSELibs = False
         mnuRunPOSEstart = False
         mnuRunPOSEstop = False
         mnuCodeDebugStop = True
         mnuDebugContinue.Enabled = True
         'mnuCodeDebugSingleStep.Enabled = True
         mnuCodeDebugVariables.Enabled = True
         mnuCodeDebugCallStack.Enabled = True
         mnuDebugIgnoreBreakpoints.Enabled = True
      Else
         mnuRunCompile = True
         mnuRunPOSELibs = True
         mnuRunPOSEstart = True
         mnuRunPOSEstop = True
         mnuCodeDebugStop = False
         mnuDebugContinue.Enabled = False
         'mnuCodeDebugSingleStep.Enabled = False
         mnuCodeDebugVariables.Enabled = False
         mnuCodeDebugCallStack.Enabled = False
         mnuDebugIgnoreBreakpoints.Enabled = False
      End If
      mnuCodeDebugWatch.Enabled = True
      mnuCodeDebugBreakpointsClearThisModule.Enabled = True
      mnuCodeDebugBreakpointsClearAll.Enabled = True
   Else
      mnuCodeDebugStop = False
      mnuDebugContinue.Enabled = False
      mnuCodeDebugVariables.Enabled = False
      mnuCodeDebugCallStack.Enabled = False
      mnuDebugIgnoreBreakpoints.Enabled = False
      mnuCodeDebugWatch.Enabled = False
      mnuCodeDebugBreakpointsClearThisModule.Enabled = False
      mnuCodeDebugBreakpointsClearAll.Enabled = False
   End If

End Sub
Private Sub mnuRunHotsyncLibs_Click()
   dlgCommonDialog.DialogTitle = "Shared Libraries"
   dlgCommonDialog.InitDir = fileDirectory + "\Lib"
   dlgCommonDialog.filename = ""
   dlgCommonDialog.Filter = "Shared Libs (*.prc)|*.prc"
   dlgCommonDialog.DefaultExt = "psf"
   dlgCommonDialog.CancelError = True
   On Error GoTo Cancel
   dlgCommonDialog.ShowOpen
   On Error GoTo 0
   DownloadFile dlgCommonDialog.filename, "Hotsync"
Cancel:
End Sub

Private Sub mnuRunHotsyncProject_Click()
   If Not DownloadFile(DownloadPath + gTarget.Name + ".prc", "Hotsync") Then MsgBox gStringTable(3332) '"Download failed."
End Sub

Private Sub mnuRunHotsyncRuntime_Click()
   Dim runtime As String
   runtime = "NSBRuntime.prc"
   If gbIncludeArmNative = True Then runtime = "NSBRuntimeARM68K.prc"
   DownloadFile ProgramsDirectory & "\BuildTools\" & runtime, "Hotsync"
End Sub
Private Sub mnuRunPOSELibs_Click()
   dlgCommonDialog.DialogTitle = "Shared Libraries"
   dlgCommonDialog.InitDir = fileDirectory + "\Lib"
   dlgCommonDialog.filename = ""
   dlgCommonDialog.Filter = "Shared Libs (*.prc)|*.prc"
   dlgCommonDialog.CancelError = True
   dlgCommonDialog.DefaultExt = "psf"
   On Error GoTo Cancel
   dlgCommonDialog.ShowOpen
   On Error GoTo 0
   DownloadFile dlgCommonDialog.filename, DownloadOption
Cancel:
End Sub

Private Sub mnuRunPOSEProject_Click()
   If Not DownloadFile(DownloadPath + gTarget.Name + ".prc", DownloadOption) Then MsgBox gStringTable(3332) '"Download failed."
End Sub

Private Sub mnuRunPoseRuntime_Click()
   Dim runtime As String
   runtime = "NSBRuntime.prc"
   If gbIncludeArmNative = True Then runtime = "NSBRuntimeARM68K.prc"
   If gbDebugMode = True And DownloadOption = "POSE" Then runtime = "NSBRuntimeDebug.prc"
   DownloadFile ProgramsDirectory & "\BuildTools\" & runtime, DownloadOption
End Sub
#If NSBSymbian = 1 Then
Private Sub mnuRunRunImmediately_Click()
   outputDir = fileDirectory & "\Download\"
   sisFile = outputDir & gTarget.Name & ".sis"
   sisxFile = outputDir & gTarget.Name & ".sisx"
   MSymbian.runImmediately
End Sub
#End If

Private Sub mnuTools_Click()
   mnuToolsMenuEditor.Enabled = (gProjects.count > 0)
   mnuToolsThemeEditor.Enabled = (gProjects.count > 0)
End Sub

Private Sub mnuToolsList_Click(index As Integer)
Dim pathname As String
Dim err As Integer

   pathname = Chr(34) & fileDirectory & "\tools\" & mnuToolsList(index).Tag & Chr(34)
   err = ShellExecute(0, "Open", pathname, vbNullString, vbNullString, 5)
End Sub

Private Sub mnuToolsMenuEditor_Click()
   MenuEditor
End Sub
Private Sub mnuToolsThemeEditor_Click()
   ThemeEditor
End Sub

Private Sub mnuToolsOptions_Click()
Dim fOptions As New frmOptions

   fOptions.Show vbModal, Me
End Sub

Private Sub mnuWindow_Click()
'   If Picture1.Visible Then
'      mnuWindowProjectExplorer.Enabled = True
'   Else
'      mnuWindowProjectExplorer.Enabled = False
'   End If
End Sub

Private Sub mnuWindowList_Click(index As Integer)
   GetMDIChild(mnuWindowList(index).Tag).ZOrder
End Sub

Private Sub mnuViewProjectExplorer_Click()
   If gbProjectExplorer Then
      Unload gfProjectExplorer
   Else
      gfProjectExplorer.DisplayExplorer
      gfProjectExplorer.DockWindow
   End If
End Sub

Private Sub mnuViewProperties_Click()
   If gbProperties Then
      Unload gfProperties
   Else
      gfProperties.DockWindow
   End If
End Sub

Private Sub mnuViewToolbox_Click()
   If gbToolbox Then
      Unload gfToolbox
   Else
      gfToolbox.DockWindow
   End If
End Sub

Private Sub picSplit_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
   m_bSizing = True
   SetParent picSplit.hWnd, frmMain.hWnd
   UpdateWindow picSplit.hWnd
End Sub

Private Sub picSplit_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim pt As POINTAPI

   If m_bSizing Then
      GetCursorPos pt
      ScreenToClient frmMain.hWnd, pt
'      ScreenToClient picPanel.hwnd, pt
      picSplit.Move picPanel.Left + picWidth.Width, pt.y * Screen.TwipsPerPixelY, picSplit.Width, 45
'      picSplit.Move picWidth.Width, pt.Y * Screen.TwipsPerPixelY, picSplit.Width, 45
''      picWidth.BackColor = &H8000000C
      picSplit.BackColor = vbBlack
   End If
End Sub

Private Sub picSplit_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim pt As POINTAPI

   m_bSizing = False
   GetCursorPos pt
   ScreenToClient picPanel.hWnd, pt
   picSplit.BackColor = &H8000000F
''   picWidth.BackColor = &H80000002
   SetParent picSplit.hWnd, picPanel.hWnd
'   picSplit.Tag = round(((-pt.Y * Screen.TwipsPerPixelY) / picPanel.Height) * 100)
   picSplit.Tag = round((picSplit.Top - picPanel.Top) / picPanel.Height * 100)
   picPanel_Resize
   UpdateWindow picSplit.hWnd
End Sub

Public Sub picToolbox_Resize()
''   picToolbox.Width = tbToolbox.Width
Dim l As Long

   l = GetWindow(picToolbox.hWnd, GW_CHILD)
   If l <> 0 Then
      MoveWindow l, -3, -3, picToolbox.Width / Screen.TwipsPerPixelX + 8, picToolbox.Height / Screen.TwipsPerPixelY + 9, True
      UpdateWindow l
   End If
End Sub

Public Sub picPanel_Resize()
'On Error Resume Next
Dim nSplit As Integer

   If Me.WindowState = vbMinimized Then Exit Sub
   If Not gbProjectExplorer And Not gbProperties Then
      picPanel.Visible = False
   Else
      picWidth.Move 0, 0, 90, picPanel.Height
      picSplit.Visible = False
      If gbProjectExplorer And gbProperties Then
         'Need to show picSplit first
         nSplit = ((picPanel.Height - 90) * picSplit.Tag) \ 100
         If nSplit < 0 Then nSplit = 0
         nSplit = IIf(nSplit > picPanel.Height - 110, picPanel.Height - 110, nSplit)
         picSplit.Move picWidth.Width, nSplit, picPanel.Width - picWidth.Width, 90
         picSplit.Visible = True
         'Now show other pics
         picProjectExplorer.Move picWidth.Width, 0, picPanel.Width - picWidth.Width, picSplit.Top
         picProjectExplorer.Visible = True
         picProperties.Move picWidth.Width, picSplit.Top + picSplit.Height, picPanel.Width - picWidth.Width, IIf(picPanel.Height - (picSplit.Top + picSplit.Height) < 0, 0, picPanel.Height - (picSplit.Top + picSplit.Height))
         picProperties.Visible = True
      ElseIf gbProjectExplorer Then
         picProjectExplorer.Move picWidth.Width, 0, picPanel.Width - picWidth.Width, picPanel.Height
         picProjectExplorer.Visible = True
         picProperties.Visible = False
      Else
         picProperties.Move picWidth.Width, 0, picPanel.Width - picWidth.Width, picPanel.Height
         picProperties.Visible = True
         picProjectExplorer.Visible = False
      End If
   End If
End Sub

Public Sub picProjectExplorer_Resize()
Dim l As Long

   l = GetWindow(picProjectExplorer.hWnd, GW_CHILD)
   If l <> 0 Then
      Call MoveWindow(l, -3, -3, picProjectExplorer.Width / Screen.TwipsPerPixelX + 8, picProjectExplorer.Height / Screen.TwipsPerPixelY + 9, True)
      Call UpdateWindow(l)
   End If
End Sub

Public Sub picProperties_Resize()
Dim l As Long

   l = GetWindow(picProperties.hWnd, GW_CHILD)
   If l <> 0 Then
      Call MoveWindow(l, -3, -3, picProperties.Width / Screen.TwipsPerPixelX + 8, picProperties.Height / Screen.TwipsPerPixelY + 9, True)
      Call UpdateWindow(l)
   End If
End Sub

Private Sub picWidth_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
   m_bSizing = True
   SetParent picWidth.hWnd, frmMain.hWnd
   UpdateWindow picWidth.hWnd
End Sub

Private Sub picWidth_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim pt As POINTAPI

   If m_bSizing Then
      GetCursorPos pt
      ScreenToClient frmMain.hWnd, pt
      picWidth.Move pt.x * Screen.TwipsPerPixelX, picPanel.Top, 45, picPanel.Height
''      picWidth.BackColor = &H8000000C
      picWidth.BackColor = vbBlack
   End If
End Sub

Private Sub picWidth_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim pt As POINTAPI
Dim NewWidth As Integer

   If m_bSizing Then
      GetCursorPos pt
      ScreenToClient frmMain.hWnd, pt
      m_bSizing = False
      picWidth.BackColor = &H8000000F
''      picWidth.BackColor = &H80000002
      SetParent picWidth.hWnd, picPanel.hWnd
      NewWidth = Me.Width - picWidth.Left - picWidth.Width
      If NewWidth <= 100 Then NewWidth = 100
      picPanel.Width = NewWidth
      picPanel_Resize
      UpdateWindow picWidth.hWnd
   End If
End Sub

Public Sub UpdateToolbar()
   On Error Resume Next
   tbToolBar.Buttons(7).Enabled = ActiveForm.CanUndo
   tbToolBar.Buttons(8).Enabled = ActiveForm.CanRedo
   tbToolBar.Buttons(10).Enabled = ActiveForm.CanCut
   tbToolBar.Buttons(11).Enabled = ActiveForm.CanCopy
   tbToolBar.Buttons(12).Enabled = ActiveForm.CanPaste
   On Error GoTo 0
End Sub

Private Sub tbToolBar_ButtonClick(ByVal Button As MSComctlLib.Button)
   On Error Resume Next
   Select Case Button.key
   Case "New": mnuFileNewProject_click
   Case "Open": mnuFileOpenProject_click
   Case "Save": mnuFileSaveProject_Click
   Case "Print": mnuFilePrint_Click
   Case "Undo": mnuEditUndo_Click
   Case "Redo": mnuEditRedo_Click
   Case "Cut": mnuEditCut_Click
   Case "Copy": mnuEditCopy_Click
   Case "Paste": mnuEditPaste_Click
   Case "Delete":
      mnuRightItem_Click 14
   Case "Find": mnuEditFind_Click
   Case "Add Form": mnuProjectAddForm_click
   Case "Add Bitmap": mnuProjectAddBitmap_click
   Case "Add Module": mnuProjectAddNewModule_Click
   Case "Add Resource": mnuProjectAddResource_click
   Case "Compile": mnuRunCompile_Click
   Case "Properties": mnuViewProperties_Click
   Case "Menu Editor": mnuToolsMenuEditor_Click
   End Select
End Sub

Private Sub mnuHelpAbout_Click()
   frmAbout.Show vbModal, Me
End Sub

Private Sub mnuHelpSearchForHelpOn_Click()
   Dim nRet As Integer

   'if there is no helpfile for this project display a message to the user
   'you can set the HelpFile for your application in the
   'Project Properties dialog
   If Len(App.helpFile) = 0 Then
      MsgBox gStringTable(3333), vbInformation, Me.caption '"Unable to display Help Contents. There is no Help associated with this project."
   Else
      On Error Resume Next
      nRet = OSWinHelp(Me.hWnd, App.helpFile, 261, 0)
      If err Then
         MsgBox err.Description
      End If
   End If
End Sub

Private Sub mnuHelpContents_Click()
   Dim nRet As Integer

   'if there is no helpfile for this project display a message to the user
   'you can set the HelpFile for your application in the
   'Project Properties dialog
   If Len(App.helpFile) = 0 Then
      MsgBox gStringTable(3333), vbInformation, Me.caption ' "Unable to display Help Contents. There is no Help associated with this project."
   Else
      On Error Resume Next
      nRet = OSWinHelp(Me.hWnd, App.helpFile, 3, 0)
      If err Then
         MsgBox err.Description
      End If
   End If
End Sub

Private Sub mnuWindowArrangeIcons_Click()
   Me.Arrange vbArrangeIcons
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

Private Sub mnuWindowNewWindow_Click()
   LoadNewProject
End Sub

Private Sub mnuHelpWWW_Click()
   #If NSBSymbian Then
   openWebPage "http://www.nsbasic.com/symbian/info/ide.html"
   #Else
   openWebPage "http://www.nsbasic.com/palm/info/ide.html"
   #End If
End Sub

Private Sub mnuViewOptions_Click()
   frmOptions.Show vbModal, Me
End Sub

Private Sub mnuViewRefresh_Click()
Dim frm As Form

   Set frm = ActiveForm
   If frm Is Nothing Then Exit Sub
   frm.Visible = False
   frm.Visible = True
End Sub

Private Sub mnuViewStatusBar_Click()
   mnuViewStatusBar.Checked = Not mnuViewStatusBar.Checked
   sbStatusBar.Visible = mnuViewStatusBar.Checked
End Sub

Private Sub mnuViewToolbar_Click()
   mnuViewToolbar.Checked = Not mnuViewToolbar.Checked
   tbToolBar.Visible = mnuViewToolbar.Checked
End Sub

Private Sub mnuEditPaste_Click()
   If ActiveForm Is Nothing Then Exit Sub
   Select Case typename(ActiveForm)
   Case "frmPalmScreen", "frmCode": ActiveForm.Paste
   End Select
'   On Error Resume Next
'   ActiveForm.rtfText.SelRTF = Clipboard.GetText
End Sub

Private Sub mnuEditCopy_Click()
   If ActiveForm Is Nothing Then Exit Sub
   Select Case typename(ActiveForm)
   Case "frmPalmScreen", "frmCode": ActiveForm.Copy
   End Select
'   On Error Resume Next
'   Clipboard.SetText ActiveForm.rtfText.SelRTF
'
End Sub

Private Sub mnuEditCut_Click()
   If ActiveForm Is Nothing Then Exit Sub
   Select Case typename(ActiveForm)
   Case "frmPalmScreen", "frmCode": ActiveForm.Cut
   End Select
'   On Error Resume Next
'   Clipboard.SetText ActiveForm.rtfText.SelRTF
'   ActiveForm.rtfText.SelText = vbNullString
'
End Sub

Private Sub mnuEditUndo_Click()
   ActiveForm.Undo
End Sub

Private Sub mnuFileExit_click()
   Unload Me
End Sub

Private Sub mnuFileSend_Click()
   'ToDo: Add 'mnuFileSend_Click' code.
   MsgBox "Add 'mnuFileSend_Click' code."
End Sub

Private Sub mnuFilePrint_Click()
Dim strGID As String
Dim currentModule As Boolean

   'currentModule = MsgBox(gStringTable(3353), vbYesNo) 'Print the current module only?
   currentModule = False
   
   On Error Resume Next
   If ActiveForm Is Nothing Then Exit Sub

   With dlgCommonDialog
      .DialogTitle = "Print"
      .CancelError = True
      .flags = cdlPDReturnDC + cdlPDNoPageNums + cdlOFNNoChangeDir
      .ShowPrinter
      If err = MSComDlg.cdlCancel Then Exit Sub
   End With

   If currentModule Then
      strGID = ActiveForm.GlobalID
      If typename(ActiveForm) = "frmCode" Then
         'Put code away to make sure changes get printed
         'Also, beware of empty code modules disappearing
         ActiveForm.PutTheCodeBack
         If ActiveForm Is Nothing Then Exit Sub
         If ActiveForm.GlobalID <> strGID Then Exit Sub
         PrintCode ActiveForm.GlobalID
      Else
         PrintForm ActiveForm.GlobalID
      End If
   Else
      PrintProject
   End If
End Sub

Private Sub mnuFilePrintPreview_Click()
   'ToDo: Add 'mnuFilePrintPreview_Click' code.
   MsgBox "Add 'mnuFilePrintPreview_Click' code."
End Sub

Private Sub mnuFilePageSetup_Click()
   On Error Resume Next
   With dlgCommonDialog
      .DialogTitle = "Page Setup"
      .CancelError = True
      .flags = cdlPDPrintSetup
      .ShowPrinter
   End With

End Sub

Private Sub mnuFileProperties_Click()
   'ToDo: Add 'mnuFileProperties_Click' code.
   MsgBox "Add 'mnuFileProperties_Click' code."
End Sub

Private Sub mnuFileSaveAll_Click()
Dim proj As CProject

   For Each proj In gProjects
      SaveProject proj
   Next
End Sub

Private Sub mnuFileSaveAs_click()
Dim sFile As String

   If ActiveForm Is Nothing Then Exit Sub

   With dlgCommonDialog
      .DialogTitle = "Save As"
      .CancelError = False
      'ToDo: set the flags and attributes of the common dialog control
      .Filter = "All Files (*.*)|*.*"
      .ShowSave
      If Len(.filename) = 0 Then
         Exit Sub
      End If
      sFile = .filename
   End With
   ActiveForm.caption = sFile
   ActiveForm.rtfText.SaveFile sFile
End Sub

Private Sub mnuFileClose_click()
   'ToDo: Add 'mnuFileClose_Click' code.
   MsgBox "Add 'mnuFileClose_Click' code."
End Sub

Private Sub mnuFileOpenProject_click()
Dim strProj As String
'Dim fSelProj As New frmSelProj
'
'   fSelProj.ShowNew = False
'   fSelProj.ShowDialog
'   strProj = fSelProj.fileName
'   Unload fSelProj
   strProj = ShowNewOpen(False)
   If strProj <> "" Then
      If RemoveProject(gTarget) Then OpenProject strProj
   End If
End Sub

Private Sub mnuFileNewProject_click()
Dim fNewProject As New frmNewProject
Dim strNew As String

   If MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "ShowSplash", True) Then
      fNewProject.Show vbModal
      strNew = fNewProject.ProjectTemplate
      'This should open the frmSelProj with only the "New" tab
      '...when templates are added
      If strNew = "Project File" Then
         If RemoveProject(gTarget) Then LoadNewProject
      Else
         'Do some sort of template thing here
      End If
   Else
      LoadNewProject
   End If
End Sub

Private Sub UpdateProjectList()
Dim i As Integer
Dim proj As CProject

   'Update Target
''   For Each proj In gProjects
''      If proj.Name = gstr Target Then
''         Set gTarget = proj
''      End If
''   Next

   'Update Target Menu
   For i = 1 To mnuProjectSetTargetList.UBound
      mnuProjectSetTargetList(i).Visible = False
   Next
   For i = 0 To gProjects.count - 1
      If i > mnuProjectSetTargetList.UBound Then Load mnuProjectSetTargetList(i)
      mnuProjectSetTargetList(i).caption = gProjects(i + 1).Name
      mnuProjectSetTargetList(i).Tag = gProjects(i + 1).GlobalID
      If StrComp(gProjects(i + 1).Name, gTarget.Name) = 0 Then
         mnuProjectSetTargetList(i).Checked = True
      Else
         mnuProjectSetTargetList(i).Checked = False
      End If
      mnuProjectSetTargetList(i).Visible = True
   Next

   'Update Project Explorer
   If gbProjectExplorer Then gfProjectExplorer.UpdateTarget

   mnuRun_Click
End Sub

Public Sub ActiveFormChange(nActivate As Integer)
Dim i As Integer
Dim fCode As frmCode

   If nActivate Then
      'ActiveForm.DisplaySelection              '07.11.2005 GH
      If Not ActiveForm Is Nothing Then
         ActiveForm.DisplaySelection             '07.11.2005 GH
         For i = 0 To mnuWindowList.UBound
            mnuWindowList(i).Checked = False
            If ActiveForm.GlobalID = mnuWindowList(i).Tag Then mnuWindowList(i).Checked = True
         Next
         If typename(ActiveForm) = "frmPalmScreen" Then
            ActiveFormIsCode = False
            mnuFormat.Visible = True
            mnuEditUndo.Enabled = False
            mnuEditRedo.Enabled = False
            tbToolBar.Buttons(7).Enabled = False
            tbToolBar.Buttons(8).Enabled = False
         Else
            Set fCode = ActiveForm
            ActiveFormIsCode = True
            mnuFormat.Visible = False
            mnuEditUndo.Enabled = fCode.CanUndo
            mnuEditRedo.Enabled = fCode.CanRedo
            mnuEditCut.Enabled = fCode.CanCut
            mnuEditCopy.Enabled = fCode.CanCopy
            mnuEditPaste.Enabled = fCode.CanPaste
            UpdateToolbar
         End If
      End If
   Else
   End If
End Sub

Public Property Get Project(ByVal strname As String) As CProject
Dim proj As CProject

   strname = "project|" & strname
   For Each proj In gProjects
      If StrComp(proj.GlobalID, strname) = 0 Then
         Set Project = proj
         Exit Property
      End If
   Next
End Property

Public Sub AddMDIChild(frm As Form)
   Children.Add frm
   SetWindowList
End Sub

Public Function RemoveMDIChild(strGlobalID As String) As Form
Dim i As Integer

   On Error GoTo ErrorRemovingMDIChild
   For i = 1 To Children.count
'Debug.Print Children(i).GlobalID
      If Children(i).GlobalID = strGlobalID Then
         Set RemoveMDIChild = Children(i)
         Children.Remove i
         Exit For
      End If
   Next
   SetWindowList
ErrorRemovingMDIChild:
   On Error GoTo 0
End Function

Public Sub CloseMDIChild(strGlobalID As String)
Dim frm As Form

   Set frm = GetMDIChild(strGlobalID)
   If Not frm Is Nothing Then Unload frm
End Sub

Private Sub SetWindowList()
Dim i As Integer
Dim frm As Form

   'Clear the menu first
   For i = 0 To mnuWindowList.UBound
      mnuWindowList(i).Visible = False
'      mnuWindowList(i).Checked = False
   Next
   mnuWindowBar1.Visible = False

   i = 0
   For Each frm In Children
      If i > mnuWindowList.UBound Then Load mnuWindowList(i)
      If i < 9 Then
         mnuWindowList(i).caption = "&" & (i + 1) & " " & frm.caption
      Else
         mnuWindowList(i).caption = frm.caption
      End If
      mnuWindowList(i).Tag = frm.GlobalID
'      If frm Is ActiveForm Then mnuWindowList(i).Checked = True
      mnuWindowList(i).Visible = True
      i = i + 1
   Next
   If i > 0 Then mnuWindowBar1.Visible = True
End Sub

Public Function GetMDIChild(strGlobalID As String) As Form
   For Each GetMDIChild In Children
      If GetMDIChild.GlobalID = strGlobalID Then Exit Function
   Next
   Set GetMDIChild = Nothing
End Function

Public Function ViewObject(strGlobalID As String) As frmPalmScreen
'Dim frm As Form
Dim obj As Object

   Set ViewObject = GetMDIChild(strGlobalID)
   If ViewObject Is Nothing Then
      Set obj = LocateObject(strGlobalID)
      Select Case typename(obj)
      Case "CForm"
         Set ViewObject = New frmPalmScreen
         ViewObject.Object = obj
         If ViewObject.WindowState = vbNormal Then ViewObject.Move 0, 0
         ViewObject.Show
         AddMDIChild ViewObject
      Case "CBitmapFile"
         'Bitmap viewer, possibly...
      Case "CCodeModule"
         'Locate module and open it...
      Case Else
         'Locate and open an object's form
         Set ViewObject = ViewObject(obj.obj.Form.GlobalID)
         'Select object on form
         ViewObject.SetSelection obj
      End Select
   End If
   ViewObject.ZOrder
   ShowStatus ViewObject.Tag, True
End Function

Public Function ViewCode(ByVal strGlobalID As String, Optional ByVal strScript As String = "", Optional ByVal bDebug As Boolean = False) As frmCode
Dim obj As Object
Dim strCode As String

   'If strScript = "" then the script name is already attached to the GID, separate and continue
   If strScript = "" Then
      strCode = strGlobalID
      strScript = Mid(strGlobalID, InStrRev(strGlobalID, "|") + 1)
   Else
      strCode = strGlobalID & "|" & strScript
   End If

   'For the code windows, we tack on a pipe and the script type
   'ie. form|1003|project|7 -> form|1003|project|7|before
   Set ViewCode = GetMDIChild(strCode)
   If bDebug Then
      If strCode = fCodeDebug.GlobalID Then Set ViewCode = fCodeDebug
   End If
   If ViewCode Is Nothing Then
      Set obj = LocateObject(strGlobalID)
      If bDebug Then
         Set ViewCode = fCodeDebug
      Else
         Set ViewCode = New frmCode
      End If
      ViewCode.Tag = strScript
      If Left(strGlobalID, Len("object")) = "object" Then
         ViewCode.IsUIObject = True
         ViewCode.Text = obj.obj.GetScript(strScript)
         ShowStatus obj.obj.Name & " " & strScript, True
      Else
         ViewCode.IsUIObject = False
         ViewCode.Text = obj.GetScript(strScript)
         ShowStatus obj.Name & " " & strScript, True
      End If
      ViewCode.Object = obj
      If Not bDebug Then
         AddMDIChild ViewCode
      End If
   End If
   If Not bDebug Then
      ViewCode.ZOrder
      ActiveFormChange 1
   End If
End Function

Private Sub tmrStatus_Timer()
   tmrStatus.Enabled = False
   sbStatusBar.Panels(1).Text = ""
End Sub

Private Function DownloadFile(filename As String, mode As String) As Boolean
Dim t As Double
Dim result As Boolean

   If mode = "" Then mode = DownloadOption
   DownloadFile = True
   #If NSBSymbian = 0 Then
   If mode = "Hotsync" Then
      Load frmHotsync
      frmHotsync.DoInstall filename
      DownloadFile = True
   ElseIf mode = "POSE" Or mode = "Simulator" Then
      If Not isPOSERunning Then
         mnuRunPOSEstart_Click
         MsgBox gStringTable(3388) 'POSE must be running. Starting now...
         DownloadFile = False
         Exit Function
      End If
      If mode = "POSE" Then
         If Not EmuLink1.CheckCurApp("Launcher") And Not EmuLink1.CheckCurApp("General") And Not EmuLink1.CheckCurApp("Date & Time") Then
            ShowStatus gStringTable(3232), True '"Downloading... stopping current app..."
            EmuLink1.SysSoftReset
            MsgBox gStringTable(3334) '"Click OK when reset is complete..."
         End If
      End If
      ShowStatus gStringTable(3335) & filename & "...", True  '"Downloading... copying "
      DownloadFile = EmuLink1.ImportFile(filename)
      If Not DownloadFile Then MsgBox gStringTable(3335) '"Download failed."
   Else
      MsgBox gStringTable(3337) '"No download option selected in Compile/Download Options"
   End If
   #End If
End Function

Sub pause(secs)
   secs = 0
   Dim t As Long
   Dim i As Integer
   t = Timer
   Do While Timer - t < secs
      i = 1
   Loop
End Sub

Private Sub mnuRunCompile_Click()
Dim wk As String
Dim nFileSize As Long
Dim fFileSize As Double
Dim frm As Form
Dim startTime As Date

   startTime = Time
   PutTheCodeBack
   If gbAutoSave Then mnuFileSaveProject_Click
   
   If gbAtBreakPoint Then
      sendDataToDeviceDebugger ("quit")
      gbAtBreakPoint = False
   End If
   
   If gbDebugMode Then
      ignoreBreakpoints = False
      gbAtBreakPoint = False
      
      If tcpServer.state = sckError Or tcpServer.state = sckClosing Then
         tcpServer.Close
         MsgBox gStringTable(3440) 'Error starting Debugger
      End If
      
      If (tcpServer.state <> sckConnected) And (tcpServer.state <> sckError) And (tcpServer.state <> sckClosing) And (tcpServer.state <> sckListening) Then
         tcpServer.LocalPort = 1000
         tcpServer.Listen
      End If
   End If

   ShowStatus gStringTable(3230), True 'compiling
   DoEvents
   compileInProcess = True
   compile_all
   compileInProcess = False
   If compile_no_good = 1 And editorSource <> "" Then
      ViewCode Left(editorSource, InStrRev(editorSource, "|") - 1), Mid(editorSource, InStrRev(editorSource, "|") + 1)
      ActiveForm.EditorSel CLng(curCompilePos - gCorrection), CLng(curCompileLen)
      ActiveForm.Editor.SetFocus
   Else
      compileInProcess = True
      'Don't think next line does anything - MMD
      Unload frmCode
      compileOkSw = True
      graph_change_cursor "w"
      #If NSBSymbian Then
         gbBuildFat = True
         gbIncludeArmNative = True 'but it doesn't matter how this flag is set
      #End If
      nFileSize = gTarget.PrcOut
      graph_change_cursor "n"
      compileInProcess = False
      On Error GoTo 0
      If compileOkSw = True Then
         stage = "cc"   'compile complete
         fFileSize = round(nFileSize / 1024, 2)
         wk = gTarget.Name & ".prc size: " & fFileSize & " KB"
         wk = wk & vbCrLf & "Compile Time: " & ElapsedTime(startTime, Time)
         If glSerialNumber = "Unregistered Demo" Then wk = wk + vbCr + gStringTable(3374) 'NS Basic not registered - program will time out after 5 days.
         #If NSBSymbian Then
            compileSymbian
         #Else
         If DownloadOption <> "none" Then
            ShowStatus gStringTable(3233), True 'Downloading...
            If DownloadFile(DownloadPath + gTarget.Name + ".prc", "") And _
                  ((DownloadOption = "POSE" And gbPOSErun) Or _
                   (DownloadOption = "Simulator" And gbSimulatorRun)) Then
               ShowStatus gStringTable(3234), True  '"Starting app..."
               If DownloadOption = "POSE" Then pause (2)
               mnuRunPOSEstartApp_Click
            End If
         End If
         #End If
         ShowStatus wk, True
         If InStr(gCommandLineOptions, "-compile") = 0 Then MsgBox wk
      Else
         MsgBox gStringTable(3338) '"There were errors. Compile is not completed."
         Exit Sub
      End If
   End If
End Sub
#If NSBSymbian = 0 Then
Private Sub mnuRunPOSEstart_Click()
Dim commandLineOptions As String
   If DownloadOption = "POSE" And Not isPOSERunning() Then
       setupEmulatorIni
       On Error GoTo POSEerror
       If gstrPOSEPath = "" Or Dir(gstrPOSEPath) = "" Then
          MsgBox gStringTable(1413) 'please locate emulator.exe
          mnuToolsOptions_Click
       End If
       If gstrPOSEPath <> "" And Dir(gstrPOSEPath) <> "" Then
          Shell (gstrPOSEPath + " -preference ReportMemMgrLeaks=0")
       End If
       
     ElseIf DownloadOption = "Simulator" And Not isPOSERunning() Then
       setupPalmSimIni
       'commandLineOptions = " -skipCalibration -stayOnInCradle"
       On Error GoTo SimulatorError
       If gstrSimulatorPath = "" Or Dir(gstrSimulatorPath) = "" Then
          MsgBox gStringTable(3381) 'please locate PalmSim.exe
          mnuToolsOptions_Click
       End If
       If gstrSimulatorPath <> "" And Dir(gstrSimulatorPath) <> "" Then
          Shell (gstrSimulatorPath & commandLineOptions), vbNormalNoFocus
       End If
       pause 2 'give it a chance to get started
       DoEvents
       'setSimulatorLocalHost
    End If
    Exit Sub
    
POSEerror:
        On Error GoTo 0
        MsgBox gStringTable(3339) '"POSE pathname not valid"
        Exit Sub
SimulatorError:
        On Error GoTo 0
        MsgBox gStringTable(3382) '"Simulator pathname not valid"
        Exit Sub
End Sub
Private Sub setupPalmSimIni()
   Dim iniPath As String
   Dim m As String
   Dim message(400) As String
   Dim chan As Integer
   Dim port As Long
   Dim result As Boolean
   Dim line As Integer
   Dim i As Integer
   
   iniPath = Mid(gstrSimulatorPath, 1, Len(gstrSimulatorPath) - 3) & "ini"
   chan = 98
   On Error GoTo exitSetupPalmSimIni
   Open iniPath For Input As #chan
   On Error GoTo 0
   
   line = 0
   Do Until EOF(chan)
      Line Input #chan, m
      line = line + 1
      message(line) = m
      'fix drive number
      If Left(m, 4) = "ROM=" And Right(m, 41) = ":\NSBasic\Tools\Simulator\NTFull_enUS.rom" Then
         Mid(m, 5) = fileDirectory & "\Tools\Simulator\NTFull_enUS.rom"
       End If
      If Left(m, 20) = "LastStorageSnapshot=" And Right(m, 46) = ":\NSBasic\Tools\Simulator\storage snapshot.ssf" Then
         Mid(m, 21) = fileDirectory & "\Tools\Simulator\storage snapshot.ssf"
      End If
      If Left(m, 20) = "StorageSnapshotFile=" And Right(m, 46) = ":\NSBasic\Tools\Simulator\storage snapshot.ssf" Then
         Mid(m, 21) = fileDirectory & "\Tools\Simulator\storage snapshot.ssf"
      End If
      
      message(line) = m
   Loop
   Close #chan
   
   Open iniPath For Output As #chan
   For i = 1 To line
      Print #chan, message(i)
   Next
   Close #chan
   
exitSetupPalmSimIni:
   ShowStatus ""
End Sub
Private Sub setupEmulatorIni()
   Dim iniPath As String
   Dim systemDirectory As String
   Dim m As String
   Dim message(400) As String
   Dim chan As Integer
   Dim port As Long
   Dim result As Boolean
   Dim line As Integer
   Dim i As Integer
   
   systemDirectory = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SystemDirectory", "")
   
   iniPath = systemDirectory & "\Palm OS Emulator.ini"
   chan = 98
   Open iniPath For Input As #chan
   
   line = 0
   Do Until EOF(chan)
      Line Input #chan, m
      line = line + 1
      message(line) = m
      'fix drive number
      If Left(m, 27) = "LastConfiguration.fROMFile=" And Right(m, 42) = ":\NSBasic\Tools\platform41_3c_Dbg_enUS.rom" Then
         Mid(m, 28) = fileDirectory & "\Tools\platform41_3c_Dbg_enUS.rom"
        End If
      message(line) = m
   Loop
   Close #chan
   
   Open iniPath For Output As #chan
   For i = 1 To line
      Print #chan, message(i)
   Next
   Close #chan
   ShowStatus ""
End Sub

Private Sub mnuRunPOSEstartApp_Click()
   Dim result As Boolean
   If DownloadOption = "POSE" Or DownloadOption = "Simulator" Then
        If Not isPOSERunning Then mnuRunPOSEstart_Click
        DoEvents
        pause 2
        DoEvents
        If Not EmuLink1.NormalUIAppSwitch(gTarget.Name) Then
           MsgBox gStringTable(3340) & gTarget.Name ' "Could not start "
        End If
   End If
   ShowStatus ""
End Sub

Private Sub mnuRunPOSEstop_Click()
   Dim result As Boolean
   If DownloadOption = "POSE" Or DownloadOption = "Simulator" Then
        If isPOSERunning() Then
           pause (2)
           If Not EmuLink1.AppStop() Then MsgBox gStringTable(3341) '"POSE not responding. Is it running?"
        End If
    End If
    ShowStatus ""
End Sub
Private Function isPOSERunning() As Boolean
   If EmuLink1.CheckPresence Then
      isPOSERunning = True
   Else
      isPOSERunning = False
   End If
End Function
#End If

Public Sub PrintCode(strGlobalID As String)
Dim ob As Object
Dim strCode As String

   On Error GoTo err_PrintCode

   Set ob = LocateObject(strGlobalID)
   strCode = Mid(strGlobalID, InStrRev(strGlobalID, "|") + 1)
   If ob.GetCode(strCode) = "" Then Exit Sub
   Select Case typename(ob)
   Case "CProject"
      Select Case strCode
      Case "startup"
         PrintCommon "Program", "Startup Code", ob.GetCode(strCode)
      Case "termination"
         PrintCommon "Program", "Termination Code", ob.GetCode(strCode)
      End Select
   Case "CForm"
      Select Case strCode
      Case "before"
         PrintCommon "Form Code(Before form drawn)", _
               "Form = " + ob.Name + "/" + ob.Title, _
               ob.GetCode(strCode)
      Case "after"
         PrintCommon "Form Code(After form drawn)", _
               "Form = " + ob.Name + "/" + ob.Title, _
               ob.GetCode(strCode)
      Case "event"
         PrintCommon "Form Event Code", _
               "Form = " + ob.Name + "/" + ob.Title, _
               ob.GetCode(strCode)
      End Select
   Case "CCodeModule"
      PrintCommon "Module", ob.Name, ob.GetCode(strCode)
   Case "CMenuElem"
      PrintCommon "Menu", ob.caption, ob.GetCode(strCode)
   Case Else
      PrintCommon "Form Object for form = " + ob.obj.Form.Name _
            + "/" + ob.obj.Form.Title, _
            "Id #" + str(ob.obj.IdNo) + " " + ob.obj.Name + "/" + ob.obj.Label, _
            ob.obj.script
   End Select

'Fall through to this error handler, because it closes our document either way
err_PrintCode:
   Printer.EndDoc
End Sub

Public Sub PrintForm(strGlobalID As String)
Dim frm As CForm
Dim ob As Object

   On Error GoTo err_PrintForm

   Set frm = LocateObject(strGlobalID)
   If frm.pgm_script <> "" Then
      PrintCommon "Form Code(Before form drawn)", _
        "Form = " + frm.Name + "/" + frm.Title, _
        frm.pgm_script
   End If
   If frm.pgm_script_after <> "" Then
      PrintCommon "Form Code(After form drawn)", _
         "Form = " + frm.Name + "/" + frm.Title, _
         frm.pgm_script_after
   End If
   If frm.event_script <> "" Then
      PrintCommon "Form Event Code", _
         "Form = " + frm.Name + "/" + frm.Title, _
         frm.event_script
   End If

   For Each ob In frm.ObjectCollection
      If ob.obj.script <> "" Then
         PrintCommon "Form Object for form = " + frm.Name _
            + "/" + frm.Title, _
            "Id #" + str(ob.obj.IdNo) + " " + ob.obj.Name + "/" + ob.obj.Label, _
            ob.obj.script
      End If
   Next

'Fall through to this error handler, because it closes our document either way
err_PrintForm:
   Printer.EndDoc
End Sub

Public Sub PrintProject()
Dim cMod As CCodeModule
Dim mnu As CMenu
Dim mBar As CMenuBar
Dim mElem As CMenuElem
Dim frm As CForm
   
   On Error GoTo getOut
   'Printer.NewPage
          
   If gTarget.pgm_script <> "" Then
      PrintCommon "Program", "Startup Code", gTarget.pgm_script
   End If
   If gTarget.termination_script <> "" Then
      PrintCommon "Program", "Termination Code", gTarget.termination_script
   End If
   For Each cMod In gTarget.CodeCollection
      If cMod.pgm_script <> "" Then
         PrintCommon "Module", cMod.Name, cMod.pgm_script
      End If
   Next
   For Each mnu In gTarget.MenuCollection
      For Each mBar In mnu.MenuBars
         For Each mElem In mBar.MenuElems
            If mElem.menu_script <> "" Then
               PrintCommon "Menu Element", mElem.caption, mElem.menu_script
            End If
         Next
      Next
   Next
   For Each frm In gTarget.FormCollection
      PrintForm frm.GlobalID
   Next
getOut:
   Printer.EndDoc
   On Error GoTo 0
End Sub

Private Sub PrintCommon(t1 As String, t2 As String, script As String)
   Dim i As Long
   Dim j As Long
   Dim prtLine As String
   On Error Resume Next
   Printer.Orientation = dlgCommonDialog.Orientation
   On Error GoTo 0
   Printer.font.Size = 8
   Printer.font.Bold = True
   #If NSBSymbian Then
   Printer.font.Name = GetRegValue(MWinReg.hKey, "Software\NSBasic\Symbian\Editor", "FontName", "Courier New")
   #Else
   Printer.font.Name = GetRegValue(MWinReg.hKey, "Software\NSBasic\Palm\Editor", "FontName", "Courier New")
   #End If
   Printer.Print vbCrLf

   Printer.Print Tab; "--------------------------------------------------------------------------------" _
   + "--------------------------------------------------------------------------------------"
   Printer.Print Tab; "Project = " + gTarget.Name
   Printer.font.Size = Printer.font.Size + 2
   Printer.Print Tab; t1
   Printer.Print Tab; t2
   Printer.font.Size = Printer.font.Size - 2
   Printer.font.Bold = False
   Printer.Print vbCrLf
   'Printer.Print Script
   i = 1
   Do While i < Len(script)
      j = InStr(i, script, Chr$(10))
'sgBox "i=" + str(i) + "  j=" + str(j)
      If Not j = 0 Then
        If (j - i) > 80 Then
          j = i + 80
          Printer.Print Tab; Mid(script, i, j - i + 1) + " >>"
          i = j + 1
        Else
          Printer.Print Tab; Mid(script, i, j - i);
          i = j + 1
        End If
      Else
        Printer.Print Tab; Mid(script, i, Len(script) - i + 1)
        Exit Do
      End If
   Loop
End Sub

'0  View O&bject              1500
'1  View C&ode                1501
'2  -
'3  View &Startup Code        1502
'4  View &Termination Code    1503
'5  -
'6  View &Before Code         1504
'7  View &After Code          1505
'8  View &Event Code          1506
'9  View &Help Code           1507
'10 -
'11 Cu&t                   1014
'12 &Copy                  1015
'13 &Paste                 1016
'14 &Delete                1017
'15 -
'16 &Add                      1508
'-0  &Form                    1509
'-1  &Menu                    1510
'-2  &Bitmap                  1511
'-3  -
'-4  &New Module              1512
'-5  &Existing Module...      1513
'-6  &Resource                3359
'17 Add &Form              1028
'18 Add &Menu              1029
'19 Add &MenuBar              1514
'20 Add &Dropdown             1515
'21 Add &Bitmap            1030
'22 -
'23 Add &New Module           1516
'24 Add &Existing Module...   1517
'25 Add &Resource             3355
'26 -
'27 &Close Project            1518
'28 Re&move Bitmap            1519
'29 Re&move Module            1520
'30 Re&move Resource          3356
'31 -
'32 Reorder...         3390
'33 -
'34 P&roperties...         1038

'nClickSource = 0: Project Explorer Window
'nClickSource = 1: Palm Screen
Public Sub RightClickMenu(nClickSource As Integer, strGlobalID As String)
Dim i As Integer

   'First hide all menu items
   'Skip last two because separator and "Properties..." is always visible
   mnuRightItem(mnuRightItem.UBound - 1).Visible = True
   mnuRightItem(mnuRightItem.UBound).Visible = True
   For i = 0 To mnuRightItem.UBound - 2
      mnuRightItem(i).Visible = False
   Next

   'Now choose which menu items to show for object type and window source
   Select Case Left(strGlobalID, InStr(1, strGlobalID, "|") - 1)
   Case "project"
      mnuRightItem(3).Visible = True   'Startup
      mnuRightItem(4).Visible = True   'Termination
      mnuRightItem(5).Visible = True   'Separator
      mnuRightItem(13).Visible = True  'Paste
      mnuRightItem(13).Enabled = (ValidClipboard = kClipboardForm Or ValidClipboard = kClipboardMenu)
      mnuRightItem(15).Visible = True  'Separator
      mnuRightItem(16).Visible = True  'Add ->
      mnuRightItem(26).Visible = True  'Separator
      mnuRightItem(27).Visible = True  'Remove Project
   Case "form"
      If nClickSource = 0 Then
         mnuRightItem(0).Visible = True   'View Object
         mnuRightItem(2).Visible = True   'Separator
      End If
      mnuRightItem(6).Visible = True   'View Before Code
      mnuRightItem(7).Visible = True   'View After Code
      mnuRightItem(8).Visible = True   'View Event Code
'      mnuRightItem(9).Visible = True   'View Help Code
      mnuRightItem(10).Visible = True  'Separator
      If nClickSource = 0 Then mnuRightItem(11).Visible = True       'Cut
      mnuRightItem(12).Visible = True                                'Copy
      mnuRightItem(13).Visible = True
      mnuRightItem(13).Enabled = (ValidClipboard = kClipboardObject) 'Paste
      If nClickSource = 0 Then mnuRightItem(14).Visible = True       'Delete
      mnuRightItem(15).Visible = True  'Separator
      mnuRightItem(16).Visible = True  'Add ->
      mnuRightItem(31).Visible = True  'Separator
      mnuRightItem(32).Visible = True  'Reorder...
   Case "object"
      If nClickSource = 0 Then mnuRightItem(0).Visible = True  'View Object
      mnuRightItem(1).Visible = True                           'View Code
      mnuRightItem(2).Visible = True                           'Separator
      mnuRightItem(11).Visible = True                          'Cut
      mnuRightItem(12).Visible = True                          'Copy
      mnuRightItem(14).Visible = True                          'Delete
      mnuRightItem(15).Visible = True                          'Separator
      mnuRightItem(16).Visible = True                          'Add ->
   Case "menu"
      mnuRightItem(11).Visible = True                          'Cut
      mnuRightItem(12).Visible = True                          'Copy
      mnuRightItem(13).Visible = True                          'Paste
      mnuRightItem(13).Enabled = (ValidClipboard = kClipboardMenuBar)
      mnuRightItem(14).Visible = True                          'Delete
      mnuRightItem(15).Visible = True                          'Separator
'      mnuRightItem(16).Visible = True                          'Add ->
      mnuRightItem(19).Visible = True                          'Add MenuBar
   Case "menubar"
      mnuRightItem(11).Visible = True                          'Cut
      mnuRightItem(12).Visible = True                          'Copy
      mnuRightItem(13).Visible = True                          'Paste
      mnuRightItem(13).Enabled = (ValidClipboard = kClipboardMenuElem)
      mnuRightItem(14).Visible = True                          'Delete
      mnuRightItem(15).Visible = True                          'Separator
'      mnuRightItem(16).Visible = True                          'Add ->
      mnuRightItem(20).Visible = True                          'Add Dropdown
   Case "menuelem"
      mnuRightItem(1).Visible = True                           'View Code
      mnuRightItem(2).Visible = True                           'Separator
      mnuRightItem(11).Visible = True                          'Cut
      mnuRightItem(12).Visible = True                          'Copy
      mnuRightItem(14).Visible = True                          'Delete
'      mnuRightItem(15).Visible = True                          'Separator
'      mnuRightItem(16).Visible = True                          'Add ->
   Case "bitmap"
      mnuRightItem(16).Visible = True                          'Add ->
      mnuRightItem(26).Visible = True                          'Separator
      mnuRightItem(28).Visible = True                          'Remove Bitmap
   Case "resource"
      mnuRightItem(16).Visible = True                          'Add ->
      mnuRightItem(26).Visible = True                          'Separator
      mnuRightItem(30).Visible = True                          'Remove Resource
   Case "module"
      mnuRightItem(16).Visible = True                          'Add ->
      mnuRightItem(26).Visible = True                          'Separator
      mnuRightItem(29).Visible = True                          'Remove Module
   Case Else 'Folders
      mnuRightItem(17).Visible = True                          'Add Form
      mnuRightItem(18).Visible = True                          'Add Menu
      mnuRightItem(21).Visible = True                          'Add Bitmap
      mnuRightItem(22).Visible = True                          'Separator
      mnuRightItem(23).Visible = True                          'Add New Module
      mnuRightItem(24).Visible = True                          'Add Existing Module
      mnuRightItem(25).Visible = True                          'Add Resource
      If Left(strGlobalID, 5) = "Forms" Then
         mnuRightItem(31).Visible = True                       'Separator
         mnuRightItem(32).Visible = True                       'Reorder...
      End If
      mnuRightItem(33).Visible = False                         'Hide Separator
      mnuRightItem(34).Visible = False                         'Hide Properties
   End Select
   mnuRight.Tag = nClickSource & strGlobalID
   PopupMenu mnuRight
End Sub

Private Sub UpdateMRU()
Dim i As Integer
Dim strPath As String

   Open fileDirectory + "\recent.dat" For Input As #1
   For i = 1 To mnuFileMRU.UBound
      Input #1, strPath
      If strPath <> "" Then
         mnuFileMRU(i).caption = "&" & i & " " & Mid(strPath, InStrRev(strPath, "\") + 1)
         mnuFileMRU(i).Tag = strPath
         mnuFileMRU(i).Visible = True
      Else
         mnuFileMRU(i).Visible = False
      End If
   Next
   Close #1
   mnuFileBar3.Visible = mnuFileMRU(1).Visible
End Sub
Private Sub UpdateTools()
Dim i As Integer
Dim j As Integer
Dim strPath As String
Dim appName As String
Dim hFile As Long
Dim WFD As WIN32_FIND_DATA
   
   i = 0
   hFile = FindFirstFile(fileDirectory & "\Tools\*.*", WFD)
   If hFile <> INVALID_HANDLE_VALUE Then
      Do
      strPath = Left(WFD.cFileName, InStr(WFD.cFileName, Chr(0)) - 1)
      If (LCase(Right(strPath, 4)) = ".exe" Or LCase(Right(strPath, 4)) = ".bat" Or LCase(Right(strPath, 4)) = ".lnk") And i < mnuToolsList.UBound Then
         appName = Mid(strPath, 1, InStrRev(strPath, ".") - 1)
         If Left(appName, 8) = "Emulator" Or appName = "PalmRI" Or appName = "ResIn" Then GoTo skipitem1
         i = i + 1
         mnuToolsList(i).caption = appName
         mnuToolsList(i).Tag = strPath
         mnuToolsList(i).Visible = True
      End If
skipitem1:
         Loop While FindNextFile(hFile, WFD)
      hFile = FindClose(hFile)
   End If
   
   For j = i + 1 To mnuToolsList.UBound
      mnuToolsList(j).Visible = False
   Next
End Sub

Public Function FindNext(ByVal strText As String) As Boolean
   cmaxFind.Text = strText
   FindNext = CMaxFindNext(cmaxFind)
   cmaxFind.Text = ""
End Function

Public Sub ReplaceAll(ByVal strGID As String)
Dim fCode As frmCode
Dim strScript As String
Dim bObject As Boolean
Dim obj As Object

   strScript = Mid(strGID, InStrRev(strGID, "|") + 1)
   If Left(strGID, Len("object")) = "object" Then bObject = True

   Set fCode = GetMDIChild(strGID)
   If fCode Is Nothing Then
      Set obj = LocateObject(strGID)
      If bObject Then
         cmaxFind.Text = obj.obj.GetScript(strScript, False)
      Else
         cmaxFind.Text = obj.GetScript(strScript, False)
      End If
      If cmaxFind.Text = "" Then Exit Sub
      CMaxPrepFindReplace cmaxFind
      cmaxFind.ExecuteCmd cmCmdReplaceAllInBuffer
      If bObject Then
         obj.obj.PutScript cmaxFind.Text, strScript
      Else
         obj.PutScript cmaxFind.Text, strScript
      End If
      cmaxFind.Text = ""
   Else
      CMaxPrepFindReplace fCode.Editor
      fCode.Editor.ExecuteCmd cmCmdReplaceAllInBuffer
   End If
End Sub

Public Sub CheckForPalmFonts()
Dim tempFontName As String
Dim fontDir As String
Dim lParam As Long
Dim i As Integer
Dim trace As Boolean

   trace = True
   If trace Then MsgBox 1.1
   For i = 0 To 7
      gstrPalmFonts(i) = gStringTable(1450 + i)
      Select Case i
      Case 0, 1, 3, 4: gnPalmFontSize(i) = 8
      Case 2, 7: gnPalmFontSize(i) = 11
      Case 5: gnPalmFontSize(i) = 6
      Case 6: gnPalmFontSize(i) = 14
      End Select
   Next
   If trace Then MsgBox 1.2
   
   On Error GoTo MissingFont1
CheckFonts:
   tempFontName = picBox.fontname
   For i = 0 To 7
      picBox.fontname = gstrPalmFonts(i)
   Next
   picBox.fontname = tempFontName
   If trace Then MsgBox 1.3
   Exit Sub

MissingFont1:
   On Error GoTo 0
   If trace Then MsgBox 1.4
   fontDir = ProgramsDirectory & "\Fonts\"
   lParam = 0
   For i = 0 To 7
      AddFontResource (fontDir & gstrPalmFonts(i) & ".fon")
   Next
   SendMessage HWND_BROADCAST, WM_FONTCHANGE, 0, lParam
   If trace Then MsgBox 1.5
   
   On Error GoTo MissingFont2
   GoTo CheckFonts

MissingFont2:
   MsgBox gStringTable(1411), vbCritical + vbOKOnly
   gbPlainText = True
End Sub
Private Function ParseCommandLine()
   Dim commandLine As String
   Dim p As Integer
   commandLine = Trim(command())
   If commandLine = "" Then
      gCommandLineProject = ""
      gCommandLineOptions = ""
   ElseIf Left(commandLine, 1) = Chr(34) Then  '"programname.prj" option1 option2...
      p = InStr(commandLine, ".prj")
      gCommandLineProject = Mid(commandLine, 2, p + 2)
      gCommandLineOptions = Trim(Mid(commandLine, p + 4))
   Else  'programname.prj option1 option2...
      p = InStr(commandLine, " ")
      If p = 0 Then
         gCommandLineProject = commandLine
         gCommandLineOptions = ""
      Else
         gCommandLineProject = Trim(Left(commandLine, p))
         gCommandLineOptions = Trim(Mid(commandLine, p))
      End If
   End If
   'MsgBox "CommandLine:" & commandLine & "." & vbCr & "Project:" & gCommandLineProject & "." & vbCr & "Options:" & gCommandLineOptions & "."
End Function
Private Function CompileImmediately()
   gbLaunchPOSE = False
   gbAutoSave = False
   DownloadOption = "none"
   
   mnuRunCompile_Click
End Function
Private Function ShowNewOpen(bShowNew As Boolean) As String
Dim strRecent As String
Dim strRecentFile As String
Dim strRecentPath As String
Dim i As Integer
Dim trace As Boolean
trace = True
If trace Then MsgBox "ShowNewOpen" & 1
   frmNewOpen.ShowNew = bShowNew

   If frmNewOpen.ShowNew Then
      frmNewOpen.AddNewType "Project File", "PRJ"
'      frmNewOpen.AddNewType "Text File", "TEXT"
      frmNewOpen.NewImageList = ilsIcons32
   End If
If trace Then MsgBox "ShowNewOpen" & 1

   If Dir(fileDirectory + "\recent.dat", vbNormal) <> "" Then
      Open fileDirectory + "\recent.dat" For Input As #1
      For i = 1 To 20
         Input #1, strRecent
         If strRecent <> "" Then
            strRecentFile = Mid(strRecent, InStrRev(strRecent, "\") + 1)
            strRecentPath = Left(strRecent, Len(strRecent) - Len(strRecentFile))
            frmNewOpen.AddExistItem strRecentFile, strRecentPath, "PRJ"
         End If
      Next
      Close #1
   End If
If trace Then MsgBox "ShowNewOpen" & 3

'   frmNewOpen.AddExistItem "Readme2.Txt", App.Path & "\", "9/21/98", "TEXT"
'   frmNewOpen.AddExistItem "Deletedfile.Txt", App.Path & "\", "9/23/98", "PRJ"
'   frmNewOpen.AddExistItem "ccnews.Htm", App.Path & "\", "9/25/98", "PRJ"
   frmNewOpen.ExistingImageList = ilsIcons16
If trace Then MsgBox "ShowNewOpen" & 4

   Set frmNewOpen.cD = New cCommonDialog
If trace Then MsgBox "ShowNewOpen" & 5

   frmNewOpen.cD.InitDir = fileDirectory & "\Projects"
   frmNewOpen.cD.Filter = "Project Files (*.PRJ)|*.PRJ|All Files (*.*)|*.*"
   frmNewOpen.cD.flags = cdlOFNFileMustExist + cdlOFNPathMustExist
   frmNewOpen.cD.FilterIndex = 1
   frmNewOpen.cD.DefaultExt = "PRJ"
   frmNewOpen.cD.HookDialog = True

   'Make Dialog owner Me
   frmNewOpen.cD.hWnd = Me.hWnd
If trace Then MsgBox "ShowNewOpen" & 6

   Load frmNewOpen
If trace Then MsgBox "ShowNewOpen" & 7

   frmNewOpen.cD.ShowOpen
If trace Then MsgBox "ShowNewOpen" & 8

   If Not frmNewOpen.Cancelled Then
      ShowNewOpen = frmNewOpen.filename
   End If
If trace Then MsgBox "ShowNewOpen" & 9

   Unload frmNewOpen
   Set frmNewOpen = Nothing
End Function

'Private Function GetFileText(ByVal sFile As String) As String
'On Local Error GoTo GetFileTextError
'Dim iFIle As Integer
'Dim sBuf As String
'
'   iFIle = FreeFile
'   Open sFile For Binary Access Read As #iFIle
'   sBuf = String$(LOF(iFIle), 32)
'   Get #iFIle, , sBuf
'   Close #iFIle
'   GetFileText = sBuf
'   Exit Function
'
'GetFileTextError:
'   MsgBox "The file: " & sFile & " could not be loaded." & vbCrLf & vbCrLf & "[" & err.Number & ":" & err.Description & "]", vbExclamation
'   Close #iFIle
'End Function

Public Sub SetCaptions()
Dim frm As Form

   For Each frm In Children
      frm.SetCaption
   Next
   gfProjectExplorer.SetCaption
   gfProjectExplorer.UpdateTarget
   gfProperties.SetCaption
End Sub

Public Sub PutTheCodeBack()
Dim frm As Form

   For Each frm In Children
      If typename(frm) = "frmCode" Then frm.PutTheCodeBack
   Next
End Sub

Private Sub mnuDebugContinue_click()
   sendDataToDeviceDebugger ("cont")
   gbAtBreakPoint = False
   ShowStatus ""
End Sub

Public Sub sendDataToDeviceDebugger(m As String)
      tcpServer.SendData m
End Sub

Private Sub tcpServer_ConnectionRequest(ByVal requestID As Long)
  ' Check if the control's State is closed. If not,
    ' close the connection before accepting the new
    ' connection.
    If tcpServer.state <> sckClosed Then _
    tcpServer.Close
    ' Accept the request with the requestID
    ' parameter.
    tcpServer.Accept requestID
End Sub

Private Sub tcpServer_DataArrival(ByVal bytesTotal As Long)
Dim strData As String
Dim pos As Integer
Dim stmtNo As Integer
'Dim src As String
Dim view2 As CForm
Dim view As CForm

Dim n As Integer
Dim lastN As Integer
Dim newNode As Node

Dim s1 As Long
Dim s2 As Long
Dim s3 As Long

Dim strs1 As String
Dim strs2 As String
Dim strs3 As String
Dim works As String

Dim str1 As String   'added 06112005
Dim str2 As String   'added 06112005
Dim str3 As String  'added 06112005
     
Dim calledID As Integer
Dim calledStmtNo As Integer
Dim callingID As Integer
Dim callingStmtNo As Integer

Dim i As Integer
Dim p As Integer
Dim d  As CDataElement
Dim fCode As frmCode
    
   '
   'process data from the device debugger
   '
   tcpServer.GetData strData
   If gbDebugMode = False Then
      tcpServer.SendData ("quit")
      Exit Sub
   End If
   If (Mid(strData, 1, 7) = "connect") Then
      sendDataToDeviceDebugger ("connect")
      Exit Sub
   End If
   If (Mid(strData, 1, 4) = "stmt") Then
      debuggerModuleId = Val(Mid(strData, 5, 5))
      debuggerStatementNumber = Val(Mid(strData, 10, 5))
         
      If ignoreBreakpoints Then
         sendDataToDeviceDebugger ("cont")
         Exit Sub
      End If
      
      ShowStatus gStringTable(3422) & debuggerModuleId & " at statement " & debuggerStatementNumber '"Debugger in module "
      'MsgBox ("debugger at module " + str(debuggerModuleId) + "/ stmt#=" + str(debuggerStatementNumber))
        
      'locate the source for the module that runtime is executing
      '---------------
      If debuggerModuleId = 9906 Then
         editorSource = "p"
         'frmCode.Editor.Text = gTarget.pgm_script  'Fixup!
         Set fCode = ViewCode(gTarget.GlobalID, "startup", True)
         thisModuleId = 9906  'pgm-code is always 9906
         GoTo foundModule
      Else
         If debuggerModuleId = 9915 Then
            editorSource = "w"
            'frmCode.Editor.Text = gTarget.termination_script  'Fixup!
            Set fCode = ViewCode(gTarget.GlobalID, "termination", True)
            thisModuleId = 9915
            GoTo foundModule
         Else
            For Each cod In gTarget.CodeCollection
               If debuggerModuleId = cod.IdNo Then
                  editorSource = "m"
                  'frmCode.Editor.Text = cod.pgm_script  'Fixup!
                  Set fCode = ViewCode(cod.GlobalID, "module", True)
                  thisModuleId = cod.IdNo
                  GoTo foundModule
               End If
            Next

            For Each Menu In gTarget.MenuCollection
               For Each mnuBar In Menu.MenuBars
                  For Each mnu In mnuBar.MenuElems
                     If debuggerModuleId = mnu.IdNo Then
                        editorSource = "menu"
                        'frmCode.Editor.Text = mnu.menu_script  'Fixup!
                        Set fCode = ViewCode(mnu.GlobalID, "menu", True)
                        thisModuleId = mnu.IdNo
                        GoTo foundModule
                     End If
                  Next
               Next
            Next
 
            For Each view2 In gTarget.FormCollection
               If debuggerModuleId = view2.IdNo - 1 Then
                  Set view = view2
                  editorSource = "v"
                  'frmCode.Editor.Text = view.pgm_script  'Fixup!
                  Set fCode = ViewCode(view2.GlobalID, "before", True)
                  thisModuleId = view2.IdNo - 1
                  GoTo foundModule
               End If
               
               If debuggerModuleId = view2.IdNo Then
                  Set view = view2
                  editorSource = "va"
                  'frmCode.Editor.Text = view.pgm_script_after  'Fixup!
                  Set fCode = ViewCode(view2.GlobalID, "after", True)
                  thisModuleId = view2.IdNo
                  GoTo foundModule
               End If
                     
               If debuggerModuleId = 10800 - view2.IdNo Then
                  Set view = view2
                  editorSource = "e"
                  'frmCode.Editor.Text = view.event_script  'Fixup!
                  Set fCode = ViewCode(view2.GlobalID, "event", True)
                  thisModuleId = 10800 - view2.IdNo
                  GoTo foundModule
               End If
                   
               For Each o In view2.ObjectCollection
                  If debuggerModuleId = o.obj.IdNo Then
                     Set saveMouseSelectObject = o
                     editorSource = "o"
                     'frmCode.Editor.Text = saveMouseSelectObject.obj.script  'Fixup!
                     'Set fCode = ViewCode(o.obj.GlobalID, "object", True)
                     Set fCode = ViewCode(o.obj.GlobalID, "code", True)  '12.02.06 GH
                     thisModuleId = o.obj.IdNo
                     GoTo foundModule
                  End If
               Next
            Next
         End If
      End If
      sendDataToDeviceDebugger ("cont")
      Exit Sub

      'can't find source
      '----------------------------------------------
foundModule:
Dim strLine As String

      strLine = fCode.Editor.GetLine(debuggerStatementNumber - 1)
      If Left(Trim(strLine), 1) = "@" Then
         'Show breakpoint and stop
         Set fCode = ViewCode(fCode.GlobalID)
         fCode.Editor.SelectLine debuggerStatementNumber - 1, True
         gbAtBreakPoint = True
      Else
         sendDataToDeviceDebugger ("cont")
      End If
      Exit Sub
   End If

''' MMD Canned the ''' code in favor of the block directly above 2005-07-10
'''         'see if stmt has breakpoint
'''         pos = 1
'''         stmtNo = 1
'''retryBreakpoint:
'''         If pos > fCode.Editor.TextLength Then 'tell runtime to keep on going
'''            sendDataToDeviceDebugger ("cont")
'''            Exit Sub
'''         End If
'''         'Found a breakpoint
'''         If Mid(fCode.Editor.Text, pos, 1) = "@" Then
'''            If stmtNo = debuggerStatementNumber Then 'need to break at this stmt
'''               'Found the proper breakpoint, stop stuff
'''               ShowStatus "At Breakpoint. Module " & debuggerModuleId & " at statement " & debuggerStatementNumber
'''               fCode.Editor.SelStart = pos - 1
'''               fCode.Editor.SelEnd = pos
'''               gbAtBreakPoint = True
'''               Exit Sub
'''            Else 'no breakpoint at this stmt number, so keep going
'''               'Found a breakpoint before or after the current breakpoint
'''               If stmtNo > debuggerStatementNumber Then
'''               sendDataToDeviceDebugger ("cont")
'''               Exit Sub
'''            End If
'''         End If
'''      End If
'''
'''      'position to beginning of next line
'''      p = InStr(pos, fCode.Editor.Text, line_feed)
'''      If p Then
'''         stmtNo = stmtNo + 1
'''         pos = p + 1
'''         GoTo retryBreakpoint
'''      Else 'end of script reached, continue execution
'''         sendDataToDeviceDebugger ("cont")
'''         Exit Sub
'''      End If
'''   End If
        
    '-------------------------------------------------------le-----------------------------
    If (Mid(strData, 1, 5) = "stack") Then
        'received calling stack entry in response to showStack
        debuggerlaststackid = Val(Mid(strData, 6, 4))
        calledID = Val(Mid(strData, 10, 5))
        calledStmtNo = Val(Mid(strData, 15, 5))
        callingID = Val(Mid(strData, 20, 5))
        callingStmtNo = Val(Mid(strData, 25, 5))
        
        If calledID <> 0 Then
            works = vbCrLf + "Module:          " + getModuleNameByID(calledID)
            works = works + vbCrLf + "Sub/Func called :" + GetSubFuncNameBYStmtNO(calledID, calledStmtNo)
            If callingID = 0 Then
                works = works + vbCrLf + "    Called from module: Runtime Controller"
                
            Else
                works = works + vbCrLf + "    Called from module: " + getModuleNameByID(callingID)
                works = works + vbCrLf + "    At statement # : " + str(callingStmtNo)
            End If
            works = works + vbCrLf + "-------------------------------------------------------------------------------------"
        
            
            frmShowCallStack.txtCallStack.Text = frmShowCallStack.txtCallStack.Text + works
            'ask for next stack
            debuggerlaststackid = debuggerlaststackid + 1
            frmMain.sendDataToDeviceDebugger ("stack" _
                                        + Right("0000" + Mid(str(debuggerlaststackid), 2), 4))

        
                   
         Else
            'end of stack
            frmShowCallStack.Show 1
            Exit Sub
            
         End If
         
    End If
    '----------------------------------------------------------------------------------
    'the following routine changed extensively 06112005
    If (Mid(strData, 1, 3) = "var") Then
        'received variable value in response to showVariables
        debuggerlastvariableid = Val(Mid(strData, 4, 6))
        s1 = Val(Mid(strData, 10, 6))
        s2 = Val(Mid(strData, 16, 6))
        s3 = Val(Mid(strData, 22, 6))
        n = 0
        Set d = gTarget.DataCollection(debuggerlastvariableid)
      
        str1 = frmShowVariables.Tree.Nodes(lastVarNodeAskedFor).Text
        n = InStr(1, str1, "***")
        If n = 0 Then
           MsgBox gStringTable(3421) & str(lastVarNodeAskedFor)  '"program error -- can't update variable list at node# = "
        Else
           str2 = Left(str1, n - 1)
           If Len(str1) > n + 2 Then
               str3 = Mid(str1, n + 3)
            Else
                str3 = ""
            End If
            frmShowVariables.Tree.Nodes(lastVarNodeAskedFor).Text = str2 + Mid(strData, 28) + str3
        End If
       
       
       
       s3 = s3 + 1
       If s3 > d.max_no_values3 Then
          s3 = 1
          s2 = s2 + 1
          If s2 > d.max_no_values2 Then
                s2 = 1
                s1 = s1 + 1
                If s1 > d.max_no_values1 Then
                    s1 = 1
                    lastVarNodeAskedFor = lastVarNodeAskedFor + 1
                    If lastVarNodeAskedFor > frmShowVariables.Tree.Nodes.count Then
                        frmShowVariables.Show (1)
                        Exit Sub
                    End If
                    Do While frmShowVariables.Tree.Nodes(lastVarNodeAskedFor).Tag = 0
                        lastVarNodeAskedFor = lastVarNodeAskedFor + 1
                        If lastVarNodeAskedFor > frmShowVariables.Tree.Nodes.count Then
                        frmShowVariables.Show (1)
                        Exit Sub
                    End If
                    Loop
                     
                    debuggerlastvariableid = frmShowVariables.Tree.Nodes(lastVarNodeAskedFor).Tag
                    GoTo skipToNewVar
                End If
            End If
        End If
        lastVarNodeAskedFor = lastVarNodeAskedFor + 1
 
skipToNewVar:
'ask for next var (or var's subscript)
        frmMain.sendDataToDeviceDebugger ("var" _
                                        + Right("000000" + Mid(str(debuggerlastvariableid), 2), 6) _
                                        + Right("000000" + Mid(str(s1), 2), 6) _
                                        + Right("000000" + Mid(str(s2), 2), 6) _
                                        + Right("000000" + Mid(str(s3), 2), 6))
        Exit Sub
                   
    End If
    If (Mid(strData, 1, 5) = "watch") Then
        'received variable value in response to show watch Variables
        debuggerlastnodeno = Val(Mid(strData, 6, 6))
        debuggerlastvariableid = Val(Mid(strData, 12, 6))
        s1 = Val(Mid(strData, 18, 6))
        s2 = Val(Mid(strData, 24, 6))
        s3 = Val(Mid(strData, 30, 6))
        n = 0
    
     'For i = 1 To gTarget.DataCollection.count
       Set d = gTarget.DataCollection(debuggerlastvariableid)
        
        If d.max_no_values1 > 1 Then
           strs1 = str(s1)
        Else
           strs1 = ""
        End If
        If d.max_no_values2 > 1 Then
           strs2 = str(s2)
           strs1 = strs1 + ","
        Else
           strs2 = ""
        End If
        If d.max_no_values3 > 1 Then
           strs3 = str(s3)
           strs2 = strs2 + ","
        Else
           strs3 = ""
        End If
        
        
       'If s1 = 1 And s2 = 1 And s3 = 1 Then
       '
       '   If d.max_no_values1 > 1 Or d.max_no_values2 > 1 Or d.max_no_values3 > 1 Then
       '       'Set debuggerLastVariableNode = frmShowVariables.Tree.Nodes.Add(debuggerLastVariableNode, tvwLast, , formatTree(d.LocalSource, d.name, "(Subscripted array)"), "subscriptedVariableClosed", "subscriptedVariableOpen")
       '       Set debuggerLastVariableNode = frmShowVariables.Tree.Nodes.Add(, tvwLast, , formatTree(d.LocalSource, d.name, "(Subscripted array)"), "subscriptedVariableClosed", "subscriptedVariableOpen")
       '       Set debuggerLastSubscriptNode = frmShowVariables.Tree.Nodes.Add(debuggerLastVariableNode, tvwChild, , formatTree(d.LocalSource, d.name + "(" + strs1 + strs2 + strs3 + ") ", Mid(strData, 34)), "nonsubscriptedVariable", "nonsubscriptedVariable")
       '
       '       n = n + 1
       '   Else
       '       'If (frmShowVariables.Tree.Nodes.count = 0) Then
       '           Set debuggerLastVariableNode = frmShowVariables.Tree.Nodes.Add(, tvwLast, , formatTree(d.LocalSource, d.name, Mid(strData, 34)), "nonsubscriptedVariable", "nonsubscriptedVariable")
       '       'Else
       '       '  Set debuggerLastVariableNode = frmShowVariables.Tree.Nodes.Add(debuggerLastVariableNode, tvwLast, , formatTree(d.LocalSource, d.name, Mid(strData, 28)), "nonsubscriptedVariable", "nonsubscriptedVariable")
       '       'End If
       '       n = n + 1
       '   End If
       'Else
       '   Set debuggerLastSubscriptNode = frmShowVariables.Tree.Nodes.Add(debuggerLastSubscriptNode, tvwLast, , formatTree(d.LocalSource, d.name + "(" + strs1 + strs2 + strs3 + ")", Mid(strData, 34)), "nonsubscriptedVariable", "nonsubscriptedVariable")
       '   n = n + 1
       '
       '
       'End If
       
       frmWatchVariables.Tree.Nodes(debuggerlastnodeno).Text = _
           Left(frmWatchVariables.Tree.Nodes(debuggerlastnodeno).Text, InStr(1, frmWatchVariables.Tree.Nodes(debuggerlastnodeno).Text, "Value=", vbTextCompare) + 5) _
           + Mid(strData, 36)
       debuggerlastnodeno = debuggerlastnodeno + 1
       s3 = s3 + 1
       If s3 > d.max_no_values3 Then
          s3 = 1
          s2 = s2 + 1
          If s2 > d.max_no_values2 Then
                s2 = 1
                s1 = s1 + 1
                If s1 > d.max_no_values1 Then
                   s1 = 1
                   If debuggerlastnodeno > frmWatchVariables.Tree.Nodes.count Then
                        needToRefreshWatchVars = False
                        frmWatchVariables.Show 1
                        If needToRefreshWatchVars Then
                              needToRefreshWatchVars = False
                              'frmCode.mnuCodeDebugWatch_Click  'Fixup!
                              frmMain.mnuCodeDebugWatch_Click
                        End If
                        Exit Sub
                   End If
                   If frmWatchVariables.Tree.Nodes(debuggerlastnodeno).Tag = 0 Then
                     debuggerlastnodeno = debuggerlastnodeno + 1
                    End If
                    debuggerlastvariableid = frmWatchVariables.Tree.Nodes(debuggerlastnodeno).Tag
                    
                End If
            End If
        End If
        'ask for next var (or var's subscript)
      
      frmMain.sendDataToDeviceDebugger ("watch" _
                                        + Right("000000" + Mid(str(debuggerlastnodeno), 2), 6) _
                                        + Right("000000" + Mid(str(debuggerlastvariableid), 2), 6) _
                                        + Right("000000" + Mid(str(s1), 2), 6) _
                                        + Right("000000" + Mid(str(s2), 2), 6) _
                                        + Right("000000" + Mid(str(s3), 2), 6))
   End If
End Sub
Function formatTree(source As String, varname As String, Value As String) As String
    Dim s As String
    Dim srcWidth As Integer
    Dim varNameWidth As Integer
    
    
    srcWidth = frmShowVariables.Tree.Width / 4
    varNameWidth = frmShowVariables.Tree.Width / 2
    s = source
    If source = "" Then source = "Global"
    frmShowVariables.font = frmShowVariables.Tree.font
    
    Do While frmShowVariables.TextWidth(s) < srcWidth
      s = s + "."
    Loop
    
    s = s + varname
    Do While frmShowVariables.TextWidth(s) < varNameWidth
      s = s + "."
    Loop
    
    s = s + "Value=" + Value
    formatTree = s
 
    
End Function

Function getModuleNameByID(id As Integer) As String
        Dim view2 As CForm
        debuggerModuleId = id
         
         
        
         
        If debuggerModuleId = 9906 Then
                 getModuleNameByID = "Project Startup Script"
                 GoTo foundModule
        Else
            If debuggerModuleId = 9915 Then
                 getModuleNameByID = "Project Termination Script"
                 GoTo foundModule
            Else
                 For Each cod In gTarget.CodeCollection
                     If debuggerModuleId = cod.IdNo Then
                        getModuleNameByID = "Code Module -- " + cod.Name
                        GoTo foundModule
                      End If
                  Next
                  
      
                For Each Menu In gTarget.MenuCollection
                 For Each mnuBar In Menu.MenuBars
                  For Each mnu In mnuBar.MenuElems
                      If debuggerModuleId = mnu.IdNo Then
                          getModuleNameByID = "Menu -- " + mnu.subrtnName
                          GoTo foundModule
                      End If
                    
                  Next
                 Next
                Next
 
                For Each view2 In gTarget.FormCollection
                     If debuggerModuleId = view2.IdNo - 1 Then
                        getModuleNameByID = "Form -- " + view2.Name + " -- Before Draw Script"
                        GoTo foundModule
                     End If
                     If debuggerModuleId = view2.IdNo Then
                          getModuleNameByID = "Form -- " + view2.Name + " -- After Draw Script"
                          GoTo foundModule
                     End If
          
                     If debuggerModuleId = 10800 - view2.IdNo Then
                        getModuleNameByID = "Form -- " + view2.Name + " -- Event Script"
                        GoTo foundModule
                    End If
                   
                    For Each o In view2.ObjectCollection
                        If debuggerModuleId = o.obj.IdNo Then
                            getModuleNameByID = "Form Object -- " + o.obj.Name + "'s Click Code"
                            GoTo foundModule
                        End If
                    Next
                Next
            End If
        End If
        'can't recognize source
        getModuleNameByID = ""
        Exit Function
 
    
    '----------------------------------------------
foundModule:
    Exit Function
End Function
Function GetSubFuncNameBYStmtNO(calledID As Integer, calledStmtNo As Integer)

        Dim view2 As CForm
        Dim pos As Integer
        Dim stmtNo As Integer
        Dim j As Integer
        Dim sdata As String
        Dim slen As Integer

        debuggerModuleId = calledID
        debuggerStatementNumber = calledStmtNo
         
        'MsgBox ("debugger at module " + str(debuggerModuleId) + "/ stmt#=" + str(debuggerStatementNumber))
        
        'locate the source for the module that runtime is executing
        '---------------
        If debuggerModuleId = 9906 Then
                 sdata = gTarget.pgm_script
                 GoTo foundModule
        Else
            If debuggerModuleId = 9915 Then
                 sdata = gTarget.termination_script
                 GoTo foundModule
            Else
                 For Each cod In gTarget.CodeCollection
                     If debuggerModuleId = cod.IdNo Then
                        sdata = cod.pgm_script
                        
                        GoTo foundModule
                      End If
                  Next
                  
      
                For Each Menu In gTarget.MenuCollection
                 For Each mnuBar In Menu.MenuBars
                  For Each mnu In mnuBar.MenuElems
                      If debuggerModuleId = mnu.IdNo Then
                          sdata = mnu.menu_script
                           
                          GoTo foundModule
                      End If
                    
                  Next
                 Next
                Next
 
                For Each view2 In gTarget.FormCollection
                     If debuggerModuleId = view2.IdNo - 1 Then
                        sdata = view2.pgm_script
                         
                        GoTo foundModule
                     End If
                     If debuggerModuleId = view2.IdNo Then
                          sdata = view2.pgm_script_after
                          
                          GoTo foundModule
                     End If
          
                     If debuggerModuleId = 10800 - view2.IdNo Then
                        sdata = view2.event_script
                        
                        GoTo foundModule
                    End If
                   
                    For Each o In view2.ObjectCollection
                        If debuggerModuleId = o.obj.IdNo Then
                            sdata = o.obj.script
                             
                            GoTo foundModule
                        End If
                    Next
                Next
            End If
        End If
        'can't recognize source
        GetSubFuncNameBYStmtNO = ""
        Exit Function
 
    
    '----------------------------------------------
foundModule:
'see if stmt has breakpoint
        pos = 1
        stmtNo = 1
retrySearch:
        If pos > Len(sdata) Then
            GetSubFuncNameBYStmtNO = ""
            Exit Function
        End If
         
         If stmtNo = debuggerStatementNumber Then
            'need to break at this stmt
            'MsgBox ("Reached breakpoint at module " + str(debuggerModuleId) + "/ stmt#=" + str(debuggerStatementNumber))
            j = pos
            slen = Len(sdata)
            Do
               If j > slen - 3 Then
                  GetSubFuncNameBYStmtNO = ""
                  Exit Function
               End If
               If Mid(sdata, j, 1) = "@" Or Mid(sdata, j, 1) = " " Or Mid(sdata, j, 1) = line_feed Then
               Else
                  If LCase(Mid(sdata, j, 3)) = "sub" Then
                     GetSubFuncNameBYStmtNO = extractSubFuncName(Mid(sdata, j + 3))
                     Exit Function
                  Else
                     If LCase(Mid(sdata, j, 8)) = "function" Then
                        GetSubFuncNameBYStmtNO = extractSubFuncName(Mid(sdata, j + 8))
                        Exit Function
                     Else
                        'MsgBox ("sdata=" + Mid(sdata, j, 8))
                        GetSubFuncNameBYStmtNO = ""
                        Exit Function
                     End If
                  End If
               End If
               j = j + 1
            Loop
            
            GetSubFuncNameBYStmtNO = ""
            Exit Function
         Else
            'this is not the statement, so keep going
            If stmtNo > debuggerStatementNumber Then
               GetSubFuncNameBYStmtNO = ""
               Exit Function
            End If
         End If
        
        'position to beginning of next line
retryEndOfLine:
        'If 0 Then 'Mid(frmCode.script.Text, pos, 1) = line_feed Then 'Fixup
        If Mid(sdata, pos, 1) = line_feed Then
            stmtNo = stmtNo + 1
            pos = pos + 1
            'If 0 Then 'pos > Len(frmCode.script.Text) Then 'Fixup
            If pos > Len(sdata) Then
                 GetSubFuncNameBYStmtNO = ""
                 Exit Function
            End If
            GoTo retrySearch
        End If
        pos = pos + 1
        GoTo retryEndOfLine
End Function

Function extractSubFuncName(sInput As String)
    Dim s As String
    Dim result As String
    Dim k As Integer
    s = sInput
    Do While Mid(s, 1, 1) = " "
       If Len(s) > 1 Then
           s = Mid(s, 2)
        Else
           extractSubFuncName = ""
           Exit Function
        End If
        
    Loop
    result = ""
    
    k = 1
    Do
      If k > Len(s) _
      Or Mid(s, k, 1) = " " _
      Or Mid(s, k, 1) = line_feed _
      Or Mid(s, k, 1) = "(" Then
         extractSubFuncName = result
         Exit Function
      End If
      result = result + Mid(s, k, 1)
      k = k + 1
    Loop
       
End Function

Private Sub mnuDebugIgnoreBreakpoints_Click()
    ignoreBreakpoints = True
    mnuDebugContinue_click
End Sub

Private Sub mnuCodeDebugBreakpointsClearAll_Click()
Dim strData As String
Dim pos As Integer
Dim stmtNo As Integer
'Dim src As String
Dim view2 As CForm
    
   gTarget.pgm_script = RemoveBreakpoints(gTarget.pgm_script)
   gTarget.termination_script = RemoveBreakpoints(gTarget.termination_script)
    
   For Each cod In gTarget.CodeCollection
      cod.pgm_script = RemoveBreakpoints(cod.pgm_script)
   Next
    
   For Each Menu In gTarget.MenuCollection
      For Each mnuBar In Menu.MenuBars
         For Each mnu In mnuBar.MenuElems
            mnu.menu_script = RemoveBreakpoints(mnu.menu_script)
         Next
      Next
   Next
   
   For Each view2 In gTarget.FormCollection
      view2.pgm_script = RemoveBreakpoints(view2.pgm_script)
      view2.pgm_script_after = RemoveBreakpoints(view2.pgm_script_after)
      view2.event_script = RemoveBreakpoints(view2.event_script)
      For Each o In view2.ObjectCollection
         o.obj.script = RemoveBreakpoints(o.obj.script)
      Next
   Next
End Sub

Private Sub mnuCodeDebugBreakpointsClearThisModule_Click()
Dim fCode As frmCode

   'script.Text = removeBreakpoints(script.Text)  'Fixup!
   If typename(ActiveForm) = "frmCode" Then
      Set fCode = ActiveForm
      fCode.Editor.Text = RemoveBreakpoints(fCode.Editor.Text)
   End If
End Sub

Function RemoveBreakpoints(astrText As String) As String
   astrText = Replace(astrText, vbLf & "@", vbLf & " ")
   If Left(astrText, 1) = "@" Then
      RemoveBreakpoints = " " & Mid(astrText, 2)
   Else
      RemoveBreakpoints = astrText
   End If
End Function

Private Sub mnuCodeDebugCallStack_Click()
    Dim s As String
    Dim i As Integer
    debuggerlaststackid = 1
    'Set debuggerLastSubscriptNode = Nothing
    'Set debuggerLastVariableNode = Nothing

    frmShowCallStack.txtCallStack.Text = ""
    'i = kStringWorkDEMax + kArithWorkDEMax
    s = "stack" + "0001"
    frmMain.sendDataToDeviceDebugger (s)
End Sub

Private Sub mnuCodeDebugSingleStep_Click()
    frmMain.sendDataToDeviceDebugger ("one")
    'closeDownThisForm
End Sub

Private Sub mnuCodeDebugStop_Click()
 
    sendDataToDeviceDebugger ("quit")
    gbAtBreakPoint = False
    ShowStatus ""
    timeDelay (5)
    tcpServer.Close
    'frmMain.tcpServer.Close
    'frmMain.turnOffDebugging
    'closeDownThisForm
 End Sub

Private Sub mnuCodeDebugVariables_Click()
'this routine changed drastically 06112005
Dim s As String
Dim i As Integer
Dim n As Integer
Dim d As CDataElement
Dim highestN As Integer
 
 Dim tempLocalID As String
 Dim tempVarName As String
  Dim tempDataElemNo As Integer
  
  Dim lastModuleNode As Node
  Dim debuggerLastSubscriptNode As Node
  
  Dim s1 As Integer
  Dim s2 As Integer
  Dim s3 As Integer
  
  Dim strs1 As String
  Dim strs2 As String
  Dim strs3 As String
 
debuggerlastvariableid = 1
Set debuggerLastSubscriptNode = Nothing
Set debuggerLastVariableNode = Nothing

frmShowVariables.Tree.Nodes.Clear

 
'format the showVariables tree grid prior to asking for the values
'also chg the tree to sort global vars plus include a node for each module's work vars

'first--build arrays that can be sorted

i = gTarget.DataCollection.count - (kStringWorkDEMax + kArithWorkDEMax)
ReDim svLocalIDs(i)
ReDim svVarNames(i)
ReDim svDataElemNos(i)
n = 0
For i = (kStringWorkDEMax + kArithWorkDEMax) + 1 To gTarget.DataCollection.count
    Set d = gTarget.DataCollection(i)
    
    If Left(d.Name, 1) = "+" _
    Or Left(d.Name, 1) = "." _
    Or Left(d.Name, 3) = "swb" And d.isConstant = True _
    Or Left(d.Name, 3) = "nsb" And d.isConstant = True _
    Or Mid(d.Name, 1, 2) = ">>" Then
       GoTo ContinueLoop    'ignore numeric & alpha literals and typeDefs
    End If
    n = n + 1
    If d.LocalOrGlobal = "g" Then
        svLocalIDs(n) = ""
        svVarNames(n) = d.Name
        svDataElemNos(n) = i
    Else
        svLocalIDs(n) = d.LocalSource
        svVarNames(n) = d.Name
        svDataElemNos(n) = i
    End If
ContinueLoop:
 Next
 highestN = n
'now, sort the vars to moduleName,varname
 n = 1
 For i = 1 To highestN - 1
    For n = i + 1 To highestN
       If svLocalIDs(n) < svLocalIDs(i) _
       Or (svLocalIDs(n) = svLocalIDs(i)) And (svVarNames(n) < svVarNames(i)) Then
           'switch entries
           tempLocalID = svLocalIDs(i)
           tempVarName = svVarNames(i)
           tempDataElemNo = svDataElemNos(i)
           
           svLocalIDs(i) = svLocalIDs(n)
           svVarNames(i) = svVarNames(n)
           svDataElemNos(i) = svDataElemNos(n)
           
           svLocalIDs(n) = tempLocalID
           svVarNames(n) = tempVarName
           svDataElemNos(n) = tempDataElemNo
           
        End If
    Next
 Next
 'now, actually build the tree (except for subscript entries
 For i = 1 To highestN
    Set d = gTarget.DataCollection(svDataElemNos(i))
 
    If i = 1 Or svLocalIDs(i) <> svLocalIDs(i - 1) Then
        'make new module name node
        Set lastModuleNode = frmShowVariables.Tree.Nodes.Add( _
                            , tvwLast, , frmMain.formatTree(d.LocalSource, "", _
                            "(Subr/Func Name)"), "nonsubscriptedVariable", "nonsubscriptedVariable")
        lastModuleNode.Tag = 0
    End If
    
    s1 = 1
    s2 = 1
    s3 = 1
    Do
        If d.max_no_values1 > 1 Then
             strs1 = str(s1)
        Else
              strs1 = ""
        End If
        If d.max_no_values2 > 1 Then
           strs2 = str(s2)
           strs1 = strs1 + ","
        Else
           strs2 = ""
        End If
        If d.max_no_values3 > 1 Then
           strs3 = str(s3)
           strs2 = strs2 + ","
        Else
           strs3 = ""
        End If
        
        
        If s1 = 1 And s2 = 1 And s3 = 1 Then
       
            If d.max_no_values1 > 1 Or d.max_no_values2 > 1 Or d.max_no_values3 > 1 Then
              
                Set debuggerLastVariableNode = frmShowVariables.Tree.Nodes.Add( _
                            lastModuleNode, tvwChild, , frmMain.formatTree(d.LocalSource, d.Name, _
                            "(Subscripted array)"), "subscriptedVariableClosed", "subscriptedVariableOpen")
                debuggerLastVariableNode.Tag = 0
                
                Set debuggerLastSubscriptNode = frmShowVariables.Tree.Nodes.Add( _
                            debuggerLastVariableNode, tvwChild, , frmMain.formatTree(d.LocalSource, d.Name + "(" + strs1 + strs2 + strs3 + ")", "***"), _
                            "nonsubscriptedVariable", "nonsubscriptedVariable")
                debuggerLastSubscriptNode.Tag = svDataElemNos(i)
            Else
                 
                 Set debuggerLastVariableNode = frmShowVariables.Tree.Nodes.Add( _
                            lastModuleNode, tvwChild, , frmMain.formatTree(d.LocalSource, d.Name, "***"), _
                            "nonsubscriptedVariable", "nonsubscriptedVariable")
                  debuggerLastVariableNode.Tag = svDataElemNos(i)
            End If
            
        
        
        Else
                Set debuggerLastSubscriptNode = frmShowVariables.Tree.Nodes.Add( _
                            debuggerLastVariableNode, tvwChild, , frmMain.formatTree(d.LocalSource, d.Name + "(" + strs1 + strs2 + strs3 + ")", "***"), _
                            "nonsubscriptedVariable", "nonsubscriptedVariable")
                debuggerLastSubscriptNode.Tag = svDataElemNos(i)
        End If
        
              
        
       
       'ldmldm
       
       s3 = s3 + 1
       If s3 > d.max_no_values3 Then
          s3 = 1
          s2 = s2 + 1
          If s2 > d.max_no_values2 Then
                s2 = 1
                s1 = s1 + 1
                If s1 > d.max_no_values1 Then
                   Exit Do
                End If
            End If
        End If
    Loop
Next
 
n = 1
If gTarget.DataCollection.count - (kStringWorkDEMax + kArithWorkDEMax) > 0 Then
    'find the first non-parent node
    Do While frmShowVariables.Tree.Nodes(n).Tag = 0
       n = n + 1
    Loop
    lastVarNodeAskedFor = n
    debuggerlastvariableid = frmShowVariables.Tree.Nodes(n).Tag
     
    s = "var" _
                                        + Right("000000" + Mid(str(debuggerlastvariableid), 2), 6) _
                                        + "000001" _
                                        + "000001" _
                                        + "000001"
    frmMain.sendDataToDeviceDebugger (s)
Else
    MsgBox gStringTable(3420) '"The program does not have any variables defined."
End If
'end changes 061120005
End Sub

Public Sub mnuCodeDebugWatch_Click()
   sendFirstWatchRequest
End Sub

Public Sub sendFirstWatchRequest()
    Dim i As Integer
    Dim s As String
    Dim n As Integer
        
    If frmWatchVariables.Tree.Nodes.count = 0 Then
       frmWatchVariables.Show 1, frmMain
       Exit Sub
    Else
        If frmWatchVariables.Tree.Nodes(1).Tag = 0 Then
            i = frmWatchVariables.Tree.Nodes(2).Tag
            n = 2
        Else
            i = frmWatchVariables.Tree.Nodes(1).Tag
            n = 1
        End If
    End If
    s = "watch" _
                                        + Right("000000" + Mid(str(n), 2), 6) _
                                        + Right("000000" + Mid(str(i), 2), 6) _
                                        + "000001" _
                                        + "000001" _
                                        + "000001"
    frmMain.sendDataToDeviceDebugger (s)
    
End Sub
'end additions 04012005


'start additions 07262005
Public Sub timeDelay(secs As Integer)
    Dim startTime As Date
    Dim endTime As Date
    Dim longStart As Long
    Dim longEnd As Long
    
    startTime = Time
    longStart = Second(startTime) + Minute(startTime) * 60 + Hour(startTime) * 3600
    Do
        endTime = Time
        longEnd = Second(endTime) + Minute(endTime) * 60 + Hour(endTime) * 3600
        If longEnd < longStart Then
           longEnd = 24 * 60 * 60 + longEnd
        End If
        If longEnd - longStart > secs Then Exit Sub
        DoEvents
    Loop
End Sub

'end additions 07262005


