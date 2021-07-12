VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "Comdlg32.ocx"
Begin VB.Form frmCompileOptions 
   Caption         =   "Compile Options"
   ClientHeight    =   4935
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7155
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   4935
   ScaleWidth      =   7155
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkHiRes 
      Caption         =   "Set High Res for HandEra 330"
      Height          =   255
      Left            =   3600
      TabIndex        =   15
      Top             =   240
      Width           =   2895
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Browse"
      Height          =   255
      Left            =   6000
      TabIndex        =   6
      Top             =   3840
      Width           =   735
   End
   Begin VB.TextBox txtGlobalPath 
      Height          =   285
      Left            =   1560
      TabIndex        =   4
      Text            =   "Text2"
      Top             =   3840
      Width           =   4335
   End
   Begin MSComDlg.CommonDialog ComDlg 
      Left            =   120
      Top             =   4320
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CheckBox chkAutosave 
      Caption         =   "&Save before Compile"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   2010
   End
   Begin VB.CheckBox chkFat 
      Caption         =   "&Compile into Fat App"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   600
      Width           =   2010
   End
   Begin VB.CommandButton butCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5880
      TabIndex        =   3
      Top             =   4440
      Width           =   1095
   End
   Begin VB.CommandButton butDone 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4560
      TabIndex        =   2
      Top             =   4440
      Width           =   1095
   End
   Begin VB.Frame frame1 
      Caption         =   "What to do after Compile"
      Height          =   2055
      Left            =   120
      TabIndex        =   7
      Top             =   1320
      Width           =   6855
      Begin VB.CommandButton Command1 
         Caption         =   "Browse"
         Height          =   255
         Left            =   5880
         TabIndex        =   14
         Top             =   960
         Width           =   735
      End
      Begin VB.TextBox txtPOSEpath 
         Height          =   285
         Left            =   1440
         TabIndex        =   13
         Text            =   "Text1"
         Top             =   960
         Width           =   4335
      End
      Begin VB.CheckBox chkPOSErun 
         Caption         =   "Run app immediately"
         Height          =   375
         Left            =   360
         TabIndex        =   11
         Top             =   600
         Width           =   3615
      End
      Begin VB.OptionButton optDownload 
         Caption         =   "Do not do anything"
         Height          =   375
         Index           =   3
         Left            =   120
         TabIndex        =   10
         Top             =   1560
         Width           =   3855
      End
      Begin VB.OptionButton optDownload 
         Caption         =   "Hotsync to device"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   9
         Top             =   1320
         Width           =   3975
      End
      Begin VB.OptionButton optDownload 
         Caption         =   "Send to Palm OS Emulator (POSE)"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Width           =   4095
      End
      Begin VB.Label Label2 
         Caption         =   "Path to POSE"
         Height          =   255
         Left            =   360
         TabIndex        =   12
         Top             =   960
         Width           =   1215
      End
   End
   Begin VB.Label Label1 
      Caption         =   "Global Path"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   3840
      Width           =   1335
   End
End
Attribute VB_Name = "frmCompileOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub butCancel_Click()
   Me.Hide
   Unload Me
   frmMain.Show
End Sub

Private Sub butDone_Click()
Dim oldPath As String
Dim res As Boolean
Dim FatBoolean As String
Dim strAutoKey As String
Dim strPOSErun As String
Dim strHiRes As String
   
   oldPath = GlobalPath
   GlobalPath = txtGlobalPath
   MakeGlobalDirectories
   res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "InstallDir1", GlobalPath)
                   
   If chkFat.Value = 0 Then
      FatBoolean = "False"
      gbBuildFat = False
   Else
      FatBoolean = "True"
      gbBuildFat = True
   End If
   res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "Fat", FatBoolean)
                   
   If chkAutosave.Value = 0 Then
      gbAutoSave = False
      strAutoKey = "False"
   Else
      gbAutoSave = True
      strAutoKey = "True"
   End If
   res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "AutoSave", strAutoKey)
      
   If chkHiRes.Value = 0 Then
      gbHiRes = False
      strHiRes = "False"
   Else
      gbHiRes = True
      strHiRes = "True"
   End If
   res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "HiRes", strHiRes)
      
   If chkPOSErun.Value = 0 Then
      gbPOSErun = False
      strPOSErun = "False"
   Else
      gbPOSErun = True
      strPOSErun = "True"
   End If
   res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "POSErun", strPOSErun)

   If Len(txtPOSEpath) > 0 Then
      gstrPOSEPath = txtPOSEpath
      res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "POSEpath", gstrPOSEPath)
   End If
   
   If optDownload(1) = True Then
      DownloadOption = "POSE"
   ElseIf optDownload(2) = True Then
      DownloadOption = "Hotsync"
   Else
      DownloadOption = "none"
   End If
   res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "DownloadOption", DownloadOption)

   projectDirty = True
   Me.Hide
   Unload Me
   frmMain.Show
End Sub

Private Sub Command1_Click()
   comdlg.DialogTitle = "Path to POSE"
   comdlg.InitDir = GlobalPath + "\tools"
   comdlg.fileName = ""
   comdlg.Filter = "POSE Sessions (*.psf)|*.psf|(Emulator.exe)|Emulator.exe"
   comdlg.DefaultExt = "psf"
   comdlg.CancelError = False
   comdlg.ShowOpen
   txtPOSEpath = comdlg.fileName
   gstrPOSEPath = txtPOSEpath
   txtPOSEpath.Refresh
End Sub

Private Sub Command2_Click()
   comdlg.DialogTitle = "Global Path"
   comdlg.InitDir = GlobalPath
   comdlg.fileName = ""
   comdlg.Filter = "Directory (.)|."
   comdlg.DefaultExt = ""
   comdlg.CancelError = False
   comdlg.ShowOpen
   txtGlobalPath.Text = comdlg.fileName
   txtGlobalPath.Refresh
End Sub

Private Sub Form_Load()
   txtGlobalPath = GlobalPath
   txtPOSEpath = gstrPOSEPath
   
   If gbBuildFat = False Then
      chkFat = 0
   Else
      chkFat = 1
   End If
   
   If gbAutoSave = False Then
      chkAutosave = 0
   Else
      chkAutosave = 1
   End If
   
   If gbHiRes = False Then
      chkHiRes = 0
   Else
      chkHiRes = 1
   End If
   
   If DownloadOption = "POSE" Then
      optDownload(1) = True
   ElseIf DownloadOption = "Hotsync" Then
      optDownload(2) = True
   Else
      optDownload(3) = True
   End If
   
   If gbPOSErun Then
      chkPOSErun.Value = 1
   Else
      chkPOSErun.Value = 0
   End If
   
   With Me
      .Left = frmMain.Left + (frmMain.Width - .Width) / 2
      .Top = frmMain.Top + (frmMain.Height - .Height) / 2
   End With
End Sub

Private Sub optDownload_Click(index As Integer)
   If index = 1 Then
      chkPOSErun.Enabled = True
      Label2.Enabled = True
      txtPOSEpath.Enabled = True
      Command1.Enabled = True
      DownloadOption = "POSE"
   ElseIf index = 2 Then
      chkPOSErun.Enabled = False
      Label2.Enabled = False
      txtPOSEpath.Enabled = False
      Command1.Enabled = False
      DownloadOption = "Hotsync"
   Else
      chkPOSErun.Enabled = False
      Label2.Enabled = False
      txtPOSEpath.Enabled = False
      Command1.Enabled = False
      DownloadOption = "None"
   End If
End Sub
