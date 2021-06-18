VERSION 5.00
Object = "{EFC9CC66-188E-11D5-9892-0000CB222337}#1.0#0"; "EmuLink.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   7455
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4755
   LinkTopic       =   "Form1"
   ScaleHeight     =   7455
   ScaleWidth      =   4755
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command7 
      Caption         =   "Check Presence"
      Height          =   495
      Left            =   360
      TabIndex        =   16
      Top             =   6840
      Width           =   2655
   End
   Begin VB.CommandButton Command6 
      Caption         =   "Soft Reset"
      Height          =   495
      Left            =   360
      TabIndex        =   15
      Top             =   6240
      Width           =   2775
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Test"
      Height          =   495
      Left            =   1440
      TabIndex        =   14
      Top             =   5640
      Width           =   1815
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Start application"
      Height          =   375
      Left            =   1440
      TabIndex        =   11
      Top             =   5040
      Width           =   1815
   End
   Begin VB.TextBox Text4 
      Height          =   375
      Left            =   240
      TabIndex        =   9
      Text            =   "AA"
      Top             =   4560
      Width           =   2895
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Stop application"
      Height          =   375
      Left            =   1320
      TabIndex        =   8
      Top             =   3840
      Width           =   1935
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Export"
      Height          =   375
      Left            =   1320
      TabIndex        =   7
      Top             =   3240
      Width           =   1935
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Text            =   "Network"
      Top             =   2640
      Width           =   3015
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   240
      TabIndex        =   3
      Text            =   "c:\network.prc"
      Top             =   1920
      Width           =   3015
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Import"
      Height          =   375
      Left            =   1320
      TabIndex        =   2
      Top             =   1200
      Width           =   1935
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Text            =   "c:\aa.prc"
      Top             =   720
      Width           =   3015
   End
   Begin VB.Label Result 
      Height          =   255
      Left            =   960
      TabIndex        =   13
      Top             =   120
      Width           =   1935
   End
   Begin VB.Label Label5 
      Caption         =   "Result"
      Height          =   255
      Left            =   240
      TabIndex        =   12
      Top             =   120
      Width           =   735
   End
   Begin VB.Label Label4 
      Caption         =   "Application database name"
      Height          =   255
      Left            =   240
      TabIndex        =   10
      Top             =   4320
      Width           =   2295
   End
   Begin VB.Label Label3 
      Caption         =   "Database name"
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Top             =   2400
      Width           =   2055
   End
   Begin VB.Label Label2 
      Caption         =   "Full path"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   1560
      Width           =   1815
   End
   Begin VB.Label Label1 
      Caption         =   "Full path"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   360
      Width           =   1935
   End
   Begin EMULINKLib.EmuLink EmuLink1 
      Left            =   3600
      Top             =   120
      _Version        =   65536
      _ExtentX        =   1508
      _ExtentY        =   1085
      _StockProps     =   0
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Result = "Start"
Result = EmuLink1.ImportFile(Text1)
End Sub

Private Sub Command2_Click()
Result = "Start"
Result = EmuLink1.ExportFile(Text2, Text3)
End Sub

Private Sub Command3_Click()
Result = "Start"
Result = EmuLink1.AppStop()
End Sub

Private Sub Command4_Click()
Result = "Start"
Result = EmuLink1.NormalUIAppSwitch(Text4)
End Sub

Private Sub Command5_Click()

Result = "Start"

If EmuLink1.CheckCurApp(Text4) = True Then EmuLink1.NormalUIAppSwitch ("Preferences")
 
 Result = EmuLink1.ImportFile(Text1)
 Result1 = EmuLink1.AppStop()
 Do
  Result1 = EmuLink1.CheckCurApp("Launcher")
 Loop Until Result1 = True

EmuLink1.NormalUIAppSwitch (Text4)

End Sub

Private Sub Command6_Click()
   Result = "Start"
   Result = EmuLink1.SysSoftReset()
End Sub

Private Sub Command7_Click()
   Result = "Start"
   Result = EmuLink1.CheckPresence()
End Sub
