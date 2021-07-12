VERSION 5.00
Begin VB.Form frmBrowseFolder 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Browse Folder"
   ClientHeight    =   4545
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   5055
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4545
   ScaleWidth      =   5055
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.DirListBox lstDir 
      Height          =   2790
      Left            =   240
      TabIndex        =   3
      Top             =   480
      Width           =   4575
   End
   Begin VB.DriveListBox cmbDrive 
      Height          =   315
      Left            =   240
      TabIndex        =   2
      Top             =   120
      Width           =   4575
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3600
      TabIndex        =   1
      Top             =   3960
      Width           =   1215
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   2160
      TabIndex        =   0
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label lblPath 
      BorderStyle     =   1  'Fixed Single
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   3360
      Width           =   4575
   End
End
Attribute VB_Name = "frmBrowseFolder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public path As String

Private Sub cmbdrive_Change()
Dim strDrive As String

   strDrive = Left(lstDir.path, 2)
   On Error GoTo BadDrive
   lstDir.path = cmbDrive.Drive
   Exit Sub

BadDrive:
   cmbDrive.Drive = strDrive
End Sub

Private Sub cmdCancel_Click()
   Unload Me
End Sub

Private Sub cmdOK_Click()
   path = lstDir.path
   Unload Me
End Sub

Private Sub Form_Load()
   If Mid(path, 2, 1) = ":" Then
      cmbDrive = Left(path, 2)
   Else
      cmbDrive = "C:"
   End If
   
   lstDir.path = path
   lblPath.caption = path
End Sub

Private Sub lstDir_Change()
   lblPath.caption = lstDir.path
End Sub
