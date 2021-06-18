VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Listen"
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
   Begin VB.CommandButton cmdClear 
      Caption         =   "Clear"
      Height          =   495
      Left            =   3600
      TabIndex        =   2
      Top             =   2880
      Width           =   915
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
      Index           =   0
      Left            =   120
      Top             =   2820
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
      LocalPort       =   1010
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdClear_Click()
    lbStatus.Clear
End Sub

Private Sub Form_Load()
    Load wsServer(1)
    wsServer(0).Listen
    lbStatus.AddItem "Local IP is " & wsServer(0).LocalIP & " Port is " & wsServer(0).LocalPort
    lbStatus.AddItem "Listening..."
End Sub

Private Sub wsServer_Close(Index As Integer)
    lbStatus.AddItem ("Closed at " + Str(Time))
    wsServer(Index).Close
End Sub

Private Sub wsServer_ConnectionRequest(Index As Integer, ByVal requestID As Long)
    On Error GoTo Errorlbl
    If Index = 0 Then
        wsServer(1).LocalPort = 0
        wsServer(1).Accept requestID
        lbStatus.AddItem "Connected " + wsServer(1).RemoteHostIP + " at " + Str(Time)
    End If
    Exit Sub
Errorlbl:
    lbStatus.AddItem "Error in ConnectionRequest"
    Beep
End Sub

Private Sub wsServer_DataArrival(Index As Integer, ByVal bytesTotal As Long)
    Dim strData As String
    
    wsServer(Index).GetData strData
    lbStatus.AddItem "Received: " + strData
    wsServer(Index).SendData strData

End Sub

Private Sub wsServer_Error(Index As Integer, ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    On Error Resume Next
    lbStatus.AddItem "WinSock error: " & Number & " " & Description + " at " + Str(Time)
    wsServer(1).Close
End Sub
