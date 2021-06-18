VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Talk"
   ClientHeight    =   3555
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4830
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3555
   ScaleWidth      =   4830
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command3 
      Caption         =   "Send Data"
      Height          =   495
      Left            =   1320
      TabIndex        =   5
      Top             =   2880
      Width           =   975
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Close Connect"
      Height          =   495
      Left            =   2880
      TabIndex        =   4
      Top             =   2880
      Width           =   855
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Connect"
      Height          =   495
      Left            =   120
      TabIndex        =   3
      Top             =   2880
      Width           =   975
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "Clear"
      Height          =   495
      Left            =   3960
      TabIndex        =   2
      Top             =   2880
      Width           =   555
   End
   Begin VB.Frame Frame2 
      Caption         =   "Connection Status"
      Height          =   2595
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4455
      Begin VB.ListBox lbStatus 
         Height          =   2205
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   4215
      End
   End
   Begin MSWinsockLib.Winsock wsServer 
      Left            =   0
      Top             =   2640
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim connectStatus As Integer

Private Sub cmdClear_Click()
    lbStatus.Clear
End Sub

Private Sub Command1_Click()
   lbStatus.AddItem "Local IP is " & wsServer.LocalIP & " Port is " & wsServer.LocalPort
   wsServer.Connect wsServer.LocalHostName, 1010
End Sub

Private Sub Command2_Click()
   wsServer.Close
   connectStatus = 0 'not connected
End Sub

Private Sub Command3_Click()
   If connectStatus = 1 Then
      wsServer.SendData "Listen up, buddy"
   Else
      MsgBox "not connected"
   End If
End Sub

Private Sub Form_Load()
    connectStatus = 0 'not connected
End Sub

Private Sub wsServer_Close() 'this will be called if Listen exits
    lbStatus.AddItem ("Closed at " + Str(Time))
    wsServer.Close
    connectStatus = 0 'not connected
End Sub

Private Sub wsServer_DataArrival(ByVal bytesTotal As Long)
    Dim strData As String
    wsServer.GetData strData
    lbStatus.AddItem "Received: " + strData
End Sub

Private Sub wsServer_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    On Error Resume Next
    lbStatus.AddItem "WinSock error: " & Number & " " & Description + " at " + Str(Time)
    wsServer.Close
End Sub
Private Sub wsServer_connect()
   lbStatus.AddItem "Connection established at " + Str(Time)
   connectStatus = 1 ' connected
End Sub

