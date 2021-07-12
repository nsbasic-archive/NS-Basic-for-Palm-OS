VERSION 5.00
Object = "{BCA00000-0F85-414C-A938-5526E9F1E56A}#4.0#0"; "cmax40.dll"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmOptions 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Options"
   ClientHeight    =   6000
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   8280
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6000
   ScaleWidth      =   8280
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Tag             =   "1150"
   Begin VB.PictureBox pbTab 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   4695
      Index           =   0
      Left            =   240
      ScaleHeight     =   4695
      ScaleMode       =   0  'User
      ScaleWidth      =   7815
      TabIndex        =   26
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   7815
      Begin VB.OptionButton optShowSplash 
         Caption         =   "Prompt for pr&oject"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   47
         Tag             =   "1156"
         Top             =   3360
         Width           =   3975
      End
      Begin VB.OptionButton optShowSplash 
         Caption         =   "Create d&efault project"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   46
         Tag             =   "1157"
         Top             =   3720
         Width           =   3975
      End
      Begin VB.CommandButton butBrowseSimulator 
         Caption         =   "Bro&wse..."
         Height          =   315
         Left            =   6480
         TabIndex        =   36
         Tag             =   "1172"
         Top             =   1200
         Width           =   1335
      End
      Begin VB.CheckBox chkLaunchSimulator 
         Caption         =   "L&aunch Simulator at start up"
         Height          =   255
         Left            =   1920
         TabIndex        =   35
         Tag             =   "3377"
         Top             =   1560
         Width           =   4455
      End
      Begin VB.TextBox txtSimulatorPath 
         Height          =   315
         Left            =   1920
         TabIndex        =   34
         Text            =   "Text1"
         Top             =   1200
         Width           =   4455
      End
      Begin VB.CheckBox chkLaunchPOSE 
         Caption         =   "&Launch POSE at start up"
         Height          =   255
         Left            =   1920
         TabIndex        =   30
         Tag             =   "1154"
         Top             =   840
         Width           =   4455
      End
      Begin VB.CommandButton butBrowsePOSE 
         Caption         =   "B&rowse..."
         Height          =   315
         Left            =   6480
         TabIndex        =   6
         Tag             =   "1153"
         Top             =   480
         Width           =   1335
      End
      Begin VB.TextBox txtPOSEpath 
         Height          =   315
         Left            =   1920
         TabIndex        =   5
         Text            =   "Text1"
         Top             =   480
         Width           =   4455
      End
      Begin VB.TextBox txtFilesDirectory 
         Enabled         =   0   'False
         Height          =   315
         Left            =   1920
         TabIndex        =   2
         Text            =   "Text2"
         Top             =   120
         Width           =   4455
      End
      Begin VB.CommandButton butBrowseGlobalPath 
         Caption         =   "&Browse..."
         Height          =   315
         Left            =   6480
         TabIndex        =   3
         Tag             =   "1153"
         Top             =   90
         Visible         =   0   'False
         Width           =   1335
      End
      Begin VB.ListBox lstLanguage 
         Height          =   1815
         Left            =   4560
         TabIndex        =   32
         Top             =   2640
         Width           =   3255
      End
      Begin VB.Label Label1 
         Caption         =   "When NS Basic starts"
         Height          =   255
         Left            =   120
         TabIndex        =   48
         Tag             =   "1155"
         Top             =   3000
         Width           =   2895
      End
      Begin VB.Label lblSimulatorPath 
         Caption         =   "Path to &Simulator:"
         Height          =   255
         Left            =   120
         TabIndex        =   33
         Tag             =   "3376"
         Top             =   1200
         Width           =   1695
      End
      Begin VB.Label lblPOSEPath 
         Caption         =   "Path to &POSE:"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Tag             =   "1152"
         Top             =   510
         Width           =   1695
      End
      Begin VB.Label lblGlobalPath 
         Caption         =   "&Global Path:"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Tag             =   "1151"
         Top             =   120
         Width           =   1695
      End
   End
   Begin VB.PictureBox pbTab 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   4695
      Index           =   1
      Left            =   240
      ScaleHeight     =   4695
      ScaleWidth      =   7815
      TabIndex        =   25
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   7815
      Begin VB.CommandButton butEditorPrefs 
         Caption         =   "&Editor Preferences..."
         Height          =   315
         Left            =   120
         TabIndex        =   7
         Tag             =   "1158"
         Top             =   120
         Width           =   3015
      End
   End
   Begin VB.PictureBox pbTab 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   4695
      Index           =   2
      Left            =   240
      ScaleHeight     =   4695
      ScaleWidth      =   7815
      TabIndex        =   27
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   7815
      Begin VB.TextBox txtGridSize 
         Height          =   315
         Left            =   1680
         TabIndex        =   15
         Text            =   "Text1"
         Top             =   2280
         Width           =   1095
      End
      Begin VB.CheckBox chkSnapToGrid 
         Caption         =   "&Snap To Grid"
         Height          =   375
         Left            =   240
         TabIndex        =   13
         Tag             =   "1162"
         Top             =   1920
         Width           =   2775
      End
      Begin VB.CommandButton butFont 
         Caption         =   "&Font..."
         Height          =   315
         Left            =   3840
         TabIndex        =   12
         Tag             =   "1161"
         Top             =   1680
         Width           =   1575
      End
      Begin VB.CheckBox chkPlainText 
         Caption         =   "Draw &Plain Text Objects"
         ForeColor       =   &H00000000&
         Height          =   315
         Left            =   240
         TabIndex        =   11
         Tag             =   "1160"
         Top             =   1650
         Width           =   3375
      End
      Begin VB.Frame fraFontDisplay 
         Caption         =   "Plain Text Font"
         Height          =   1335
         Left            =   120
         TabIndex        =   8
         Tag             =   "1159"
         Top             =   120
         Width           =   5295
         Begin VB.Label lblExample 
            Alignment       =   2  'Center
            BackColor       =   &H80000005&
            Caption         =   "Example"
            Height          =   375
            Left            =   120
            TabIndex        =   10
            Tag             =   "1173"
            Top             =   600
            Width           =   5055
         End
         Begin VB.Label lblFontDisplay 
            Alignment       =   2  'Center
            BackColor       =   &H80000005&
            Height          =   975
            Left            =   120
            TabIndex        =   9
            Top             =   240
            Width           =   5055
         End
      End
      Begin VB.Label lblGridSize 
         Caption         =   "&Grid Size:"
         Height          =   555
         Left            =   510
         TabIndex        =   14
         Tag             =   "1163"
         Top             =   2280
         Width           =   1095
      End
   End
   Begin VB.PictureBox pbTab 
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   4695
      Index           =   3
      Left            =   240
      ScaleHeight     =   4695
      ScaleWidth      =   7815
      TabIndex        =   28
      TabStop         =   0   'False
      Top             =   480
      Visible         =   0   'False
      Width           =   7815
      Begin VB.Frame fraAfterCompiling 
         Caption         =   "After Compiling..."
         Height          =   2415
         Left            =   120
         TabIndex        =   29
         Tag             =   "1167"
         Top             =   1920
         Width           =   7695
         Begin VB.CheckBox chkRunImmediately 
            Caption         =   "Run Immediately"
            Height          =   255
            Left            =   3840
            TabIndex        =   45
            Tag             =   "1169"
            Top             =   1080
            Width           =   2895
         End
         Begin VB.CheckBox chkCreateUIQ 
            Caption         =   "Create UIQ Installer"
            Height          =   255
            Left            =   3840
            TabIndex        =   44
            Top             =   720
            Width           =   3135
         End
         Begin VB.CheckBox chkCreateS60 
            Caption         =   "Create S60 Installer"
            Height          =   255
            Left            =   3840
            TabIndex        =   43
            Top             =   360
            Width           =   2535
         End
         Begin VB.CheckBox chkSimulatorRun 
            Caption         =   "Run Immediately"
            Height          =   255
            Left            =   360
            TabIndex        =   38
            Tag             =   "3379"
            Top             =   1080
            Width           =   2655
         End
         Begin VB.OptionButton optDownload 
            Caption         =   "Send to Simulator"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   37
            Tag             =   "3378"
            Top             =   840
            Width           =   3495
         End
         Begin VB.OptionButton optDownload 
            Caption         =   "Send to Palm OS® &Emulator (POSE)"
            Height          =   255
            Index           =   1
            Left            =   120
            TabIndex        =   19
            Tag             =   "1168"
            Top             =   240
            Width           =   4935
         End
         Begin VB.OptionButton optDownload 
            Caption         =   "&HotSync to Device"
            Height          =   255
            Index           =   2
            Left            =   120
            TabIndex        =   21
            Tag             =   "1170"
            Top             =   1560
            Width           =   2775
         End
         Begin VB.OptionButton optDownload 
            Caption         =   "Do &Nothing"
            Height          =   255
            Index           =   3
            Left            =   120
            TabIndex        =   22
            Tag             =   "1171"
            Top             =   2040
            Width           =   4215
         End
         Begin VB.CheckBox chkPOSErun 
            Caption         =   "Run &Immediately"
            Height          =   255
            Left            =   360
            TabIndex        =   20
            Tag             =   "1169"
            Top             =   480
            Width           =   2535
         End
      End
      Begin VB.CheckBox chkDana 
         Caption         =   "Set WideScreen for AlphaSmart Dana"
         Height          =   255
         Left            =   3480
         TabIndex        =   42
         Top             =   840
         Width           =   3255
      End
      Begin VB.CheckBox chkDebugMode 
         Caption         =   "Debug Mode"
         Height          =   255
         Left            =   3480
         TabIndex        =   40
         Tag             =   "3437"
         Top             =   120
         Width           =   2175
      End
      Begin VB.CheckBox chkIncludeArmNative 
         Caption         =   "Include Arm Native Runtime (OS 5)"
         Height          =   255
         Left            =   120
         TabIndex        =   39
         Tag             =   "3391"
         Top             =   1200
         Width           =   3135
      End
      Begin VB.CheckBox chkCopyProtect 
         Caption         =   "Copy Protect"
         Height          =   255
         Left            =   120
         TabIndex        =   31
         Tag             =   "1224"
         Top             =   480
         Width           =   3255
      End
      Begin VB.CheckBox chkFat 
         Caption         =   "&Compile into Fat App"
         Height          =   255
         Left            =   120
         TabIndex        =   18
         Tag             =   "1165"
         Top             =   840
         Width           =   3210
      End
      Begin VB.CheckBox chkAutosave 
         Caption         =   "&Save before Compile"
         Height          =   255
         Left            =   120
         TabIndex        =   16
         Tag             =   "1164"
         Top             =   120
         Width           =   3210
      End
      Begin VB.CheckBox chkHiRes 
         Caption         =   "Set &High Res for HandEra"
         Height          =   255
         Left            =   3480
         TabIndex        =   17
         Tag             =   "1166"
         Top             =   480
         Width           =   3255
      End
   End
   Begin CodeMax4Ctl.CodeMax cmaxPref 
      Height          =   495
      Left            =   840
      OleObjectBlob   =   "frmOptions.frx":0000
      TabIndex        =   41
      Top             =   5400
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.CommandButton CancelButton 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   6480
      TabIndex        =   23
      Tag             =   "1146"
      Top             =   5400
      Width           =   1695
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4680
      TabIndex        =   24
      Tag             =   "1106"
      Top             =   5400
      Width           =   1695
   End
   Begin MSComDlg.CommonDialog comdlg 
      Left            =   120
      Top             =   5400
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DialogTitle     =   "Plain Text Font"
      FileName        =   "*.prj"
      InitDir         =   "c:\"
   End
   Begin MSComctlLib.TabStrip tabPrefs 
      Height          =   5175
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   8055
      _ExtentX        =   14208
      _ExtentY        =   9128
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   4
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "General"
            Object.Tag             =   "1440"
            Object.ToolTipText     =   "1441"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "Editor"
            Object.Tag             =   "1442"
            Object.ToolTipText     =   "1443"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "Design Screen"
            Object.Tag             =   "1444"
            Object.ToolTipText     =   "1445"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab4 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "Compile"
            Object.Tag             =   "1446"
            Object.ToolTipText     =   "1447"
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_nTab As Integer
Private m_bFontChanged As Boolean

Private Enum enTabs
   tbsNone = -1
   tbsGeneral = 0
   tbsEditor = 1
   tbsPalmScreen = 2
   tbsCompile = 3
End Enum

Private Sub butBrowseGlobalPath_Click()
Dim fBrowseFolder As New frmBrowseFolder

   On Error GoTo err_butBrowsefiledirectory_Click
   fBrowseFolder.path = txtFilesDirectory.Text
   fBrowseFolder.Show vbModal
   txtFilesDirectory.Text = fBrowseFolder.path
'
'   comdlg.DialogTitle = "Global Path"
'   comdlg.InitDir = filedirectory
'   comdlg.fileName = ""
'   comdlg.Filter = "Directory (.)|."
'   comdlg.DefaultExt = ""
'   comdlg.CancelError = True
'   comdlg.ShowOpen
'   txtfiledirectory.Text = comdlg.fileName
   txtFilesDirectory.Refresh
err_butBrowsefiledirectory_Click:
End Sub

Private Sub butBrowsePOSE_Click()
   On Error GoTo err_butBrowsePOSE_Click
   comdlg.DialogTitle = "Path to POSE"
   comdlg.InitDir = fileDirectory + "\tools"
   comdlg.filename = "Emulator.exe"
   comdlg.Filter = "Palm OS Emulator (Emulator*.exe)|Emulator*.exe"
   comdlg.DefaultExt = "exe"
   comdlg.CancelError = True
   comdlg.ShowOpen
   txtPOSEpath = comdlg.filename
   txtPOSEpath.Refresh
err_butBrowsePOSE_Click:
End Sub
Private Sub butBrowseSimulator_Click()
   On Error GoTo err_butBrowseSimulator_Click
   comdlg.DialogTitle = "Path to Simulator"
   comdlg.InitDir = fileDirectory + "\tools"
   comdlg.filename = "PalmSim.exe"
   comdlg.Filter = "Palm Simulator (PalmSim.exe)|PalmSim.exe"
   comdlg.DefaultExt = "exe"
   comdlg.CancelError = True
   comdlg.ShowOpen
   txtSimulatorPath = comdlg.filename
   txtSimulatorPath.Refresh
err_butBrowseSimulator_Click:
End Sub

Private Sub butEditorPrefs_Click()
   MNSBCodeMax_SetLanguage cmaxPref
   MNSBCodeMax_SetScriptPrefs cmaxPref
   cmaxPref.ExecuteCmd cmCmdProperties, 0
   'save values in Registry
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "codeFontName", cmaxPref.font.Name
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "codeFontSize", cmaxPref.font.Size
End Sub

Private Sub butFont_Click()
   'Prepare common dialog
   comdlg.flags = cdlCFBoth
   comdlg.fontname = gLabelFontName
   comdlg.fontSize = gLabelFontSize
   comdlg.CancelError = True

   On Error GoTo fontDlgCancel
   comdlg.ShowFont

   m_bFontChanged = True
   lblExample.FontBold = comdlg.FontBold
   lblExample.FontItalic = comdlg.FontItalic
   lblExample.fontname = comdlg.fontname
   lblExample.fontSize = comdlg.fontSize

fontDlgCancel:
   On Error GoTo 0
End Sub

Private Sub CancelButton_Click()
   Unload Me
End Sub

Private Sub chkPlainText_Click()
   butFont.Enabled = chkPlainText
End Sub

Private Sub Form_Load()
   Dim i As Integer
   LoadResStrings Me ', False

   'Update objects from current options
   'Tab 1
   txtFilesDirectory = fileDirectory
   txtPOSEpath = gstrPOSEPath
   txtSimulatorPath = gstrSimulatorPath
   If MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "ShowSplash", True) Then
      optShowSplash(0).Value = True
   Else
      optShowSplash(1).Value = True
   End If
   getLanguages
   'Tab 2
   MNSBCodeMax_SetScriptPrefs cmaxPref
   'Tab 3
   lblExample.fontname = gLabelFontName
   lblExample.fontSize = gLabelFontSize
   lblExample.font.Charset = gLabelCharset
   If gbPlainText Then
      chkPlainText = 1
   Else
      chkPlainText = 0
   End If
   If gbLaunchPOSE Then
      chkLaunchPOSE = 1
   Else
      chkLaunchPOSE = 0
   End If
   If gbLaunchSimulator Then
      chkLaunchSimulator = 1
   Else
      chkLaunchSimulator = 0
   End If
   butFont.Enabled = chkPlainText
   If gbWantGrid Then
      chkSnapToGrid = 1
   Else
      chkSnapToGrid = 0
   End If
   txtGridSize = gnGridIncr
   
   
   'Tab 4
   If gbAutoSave Then
      chkAutosave = 1
   Else
      chkAutosave = 0
   End If
   If gbBuildFat Then
      chkFat = 1
   Else
      chkFat = 0
   End If
   If gbIncludeArmNative Then
      chkIncludeArmNative = 1
   Else
      chkIncludeArmNative = 0
   End If
   If gbHiRes Then
      chkHiRes = 1
   Else
      chkHiRes = 0
   End If
   If gbDana Then
      chkDana = 1
   Else
      chkDana = 0
   End If
   If gbCopyProtect Then
      chkCopyProtect = 1
   Else
      chkCopyProtect = 0
   End If
   If gbDebugMode Then
      chkDebugMode = 1
   Else
      chkDebugMode = 0
   End If

   If DownloadOption = "POSE" Then
      optDownload(1) = True
   ElseIf DownloadOption = "Hotsync" Then
      optDownload(2) = True
   ElseIf DownloadOption = "Simulator" Then
      optDownload(0) = True
   Else
      optDownload(3) = True
   End If
   If gbPOSErun Then
      chkPOSErun.Value = 1
   Else
      chkPOSErun.Value = 0
   End If
   If gbSimulatorRun Then
      chkSimulatorRun.Value = 1
   Else
      chkSimulatorRun.Value = 0
   End If
#If NSBSymbian Then
   If gbCreateS60 Then
      chkCreateS60 = 1
   Else
      chkCreateS60 = 0
   End If
   If gbCreateUIQ Then
      chkCreateUIQ = 1
   Else
      chkCreateUIQ = 0
   End If
   If gbRunImmediately Then
      chkRunImmediately = 1
   Else
      chkRunImmediately = 0
   End If
#End If
   'Show the first tab
   m_nTab = tbsNone
   ShowTab tbsGeneral
   
'fix up display for Symbian
#If NSBSymbian Then
   'tab 1
   lblPOSEPath.Visible = False
   txtPOSEpath.Visible = False
   chkLaunchPOSE.Visible = False
   butBrowsePOSE.Visible = False
   lblSimulatorPath.Visible = False
   txtSimulatorPath.Visible = False
   chkLaunchSimulator.Visible = False
   butBrowseSimulator.Visible = False
   'tab 4
   chkFat.Visible = False
   chkHiRes.Visible = False
   chkDana.Visible = False
   chkIncludeArmNative.Visible = False
   chkLaunchSimulator.Visible = False
   chkSimulatorRun.Visible = False
   chkDebugMode.Visible = False
   chkCopyProtect.Visible = False
   For i = 0 To 3
      optDownload(i).Visible = False
   Next
   chkPOSErun.Visible = False
   chkSimulatorRun.Visible = False
   chkCreateS60.Left = optDownload(0).Left
   chkCreateUIQ.Left = optDownload(0).Left
   chkRunImmediately.Left = optDownload(0).Left
#Else
   chkCreateS60.Visible = False
   chkCreateUIQ.Visible = False
   chkRunImmediately.Visible = False
#End If
End Sub

Private Sub getLanguages()
Dim s, Name
Dim hFile As Long
Dim WFD As WIN32_FIND_DATA
Dim i As Integer

   i = 0
   hFile = FindFirstFile(ProgramsDirectory & "\Lang\StrTable_*.txt", WFD)
   If hFile <> INVALID_HANDLE_VALUE Then
      Do
         Name = Left(WFD.cFileName, InStr(WFD.cFileName, Chr(0)) - 1)
         lstLanguage.AddItem Mid(Name, 10, Len(Name) - 13)
      Loop While FindNextFile(hFile, WFD)
      hFile = FindClose(hFile)
   End If
   For i = 0 To lstLanguage.ListCount - 1
      If lstLanguage.List(i) = gLanguage Then lstLanguage.Selected(i) = True
   Next
End Sub



Private Sub OKButton_Click()
Dim oldPath As String

   'Tab 1
   If Len(txtFilesDirectory) > 0 Then
      If Dir(txtFilesDirectory, vbDirectory) <> "" Then
         If StrComp(txtFilesDirectory, fileDirectory, vbTextCompare) <> 0 Then
            oldPath = fileDirectory
            fileDirectory = txtFilesDirectory
            MakeGlobalDirectories
            MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "filedirectory", fileDirectory
         End If
      End If
   End If
   If Len(txtPOSEpath) > 0 Then
      If StrComp(txtPOSEpath, gstrPOSEPath, vbTextCompare) <> 0 Then
         gstrPOSEPath = txtPOSEpath
         MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "POSEpath", gstrPOSEPath
      End If
   End If
   If Len(txtSimulatorPath) > 0 Then
      If StrComp(txtSimulatorPath, gstrSimulatorPath, vbTextCompare) <> 0 Then
         gstrSimulatorPath = txtSimulatorPath
         MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "SimulatorPath", gstrSimulatorPath
      End If
   End If
   gbLaunchPOSE = chkLaunchPOSE
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "LaunchPOSE", gbLaunchPOSE
   gbLaunchSimulator = chkLaunchSimulator
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "LaunchSimulator", gbLaunchSimulator
   
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "ShowSplash", optShowSplash(0).Value
   If gLanguage <> lstLanguage.List(lstLanguage.ListIndex) Then
      gLanguage = lstLanguage.List(lstLanguage.ListIndex)
      LoadStringTable
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "Language", gLanguage
      gLabelFontName = gStringTable(3348) 'MS Sans Serif if Western
      gLabelCharset = gStringTable(3350) '0 if western
      If gLabelCharset <> 0 Then chkPlainText = 1
      lblExample.font.Charset = gLabelCharset
      lblExample.font.Name = gLabelFontName
      m_bFontChanged = True
      MsgBox gStringTable(3346) 'Restart NS Basic to see new language setting.
   End If
   'Tab 2
   MNSBCodeMax_SavePrefs cmaxPref
   'Tab 3
   gbPlainText = chkPlainText
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "PlainText", gbPlainText
   If m_bFontChanged Then
      gLabelFontName = lblExample.fontname
      gLabelFontSize = lblExample.fontSize
      gLabelCharset = lblExample.font.Charset
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "IDEFontName", gLabelFontName  '01/19/01 GH
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "IDEFontSize", str(gLabelFontSize)  '01/19/01 GH
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "IDEFontCharset", str(gLabelCharset)  '01/19/01 GH
      #If NSBSymbian Then
      MWinReg.SetRegValue MWinReg.hKey, "Software\NSBasic\Symbian\Editor", "FontName", gLabelFontName '03/26/01 GH
      MWinReg.SetRegValue MWinReg.hKey, "Software\NSBasic\Symbian\Editor", "FontCharSet", str(gLabelCharset) '03/26/01 GH
      #Else
      MWinReg.SetRegValue MWinReg.hKey, "Software\NSBasic\Palm\Editor", "FontName", gLabelFontName '03/26/01 GH
      MWinReg.SetRegValue MWinReg.hKey, "Software\NSBasic\Palm\Editor", "FontCharSet", str(gLabelCharset) '03/26/01 GH
      #End If
   End If
   gbWantGrid = chkSnapToGrid
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "WantGrid", gbWantGrid
   gnGridIncr = Val(txtGridSize)
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "GridIncr", gnGridIncr

   'Tab 4
   gbAutoSave = chkAutosave
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "AutoSave", gbAutoSave
   gbIncludeArmNative = chkIncludeArmNative
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "IncludeArmNative", gbIncludeArmNative
   gbBuildFat = chkFat
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "Fat", gbBuildFat
   gbHiRes = chkHiRes
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "HiRes", gbHiRes
   gbDana = chkDana
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "Dana", gbDana
   If gbDana Then kScreenWidth = 560 Else kScreenWidth = 160
   gbCopyProtect = chkCopyProtect
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "CopyProtect", gbCopyProtect
#If NSBSymbian Then
   gbCreateS60 = chkCreateS60
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "CreateS60", gbCreateS60
   gbCreateUIQ = chkCreateUIQ
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "CreateUIQ", gbCreateUIQ
   gbRunImmediately = chkRunImmediately
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "RunImmediately", gbRunImmediately
#End If
   gbDebugMode = chkDebugMode
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "DebugMode", gbDebugMode
   If gbDebugMode = False Then
      If frmMain.tcpServer.state = sckConnected Then frmMain.tcpServer.SendData "quit"
      frmMain.tcpServer.Close
   End If

   If optDownload(1) = True Then
      DownloadOption = "POSE"
   ElseIf optDownload(0) = True Then
      DownloadOption = "Simulator"
   ElseIf optDownload(2) = True Then
      DownloadOption = "Hotsync"
   Else
      DownloadOption = "none"
   End If
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "DownloadOption", DownloadOption
   gbPOSErun = chkPOSErun
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "POSErun", gbPOSErun
   gbSimulatorRun = chkSimulatorRun
   MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "SimulatorRun", gbSimulatorRun

'   projectDirty = True
   Unload Me
End Sub

Private Sub optDownload_Click(index As Integer)
   chkPOSErun.Enabled = (index = 1)
   chkSimulatorRun.Enabled = (index = 0)
End Sub

Private Sub tabPrefs_Click()
   ShowTab tabPrefs.SelectedItem.index - 1
End Sub

Private Sub ShowTab(nTab As Integer)
   If m_nTab <> tbsNone Then pbTab(m_nTab).Visible = False
   m_nTab = nTab
   pbTab(m_nTab).Visible = True
End Sub
