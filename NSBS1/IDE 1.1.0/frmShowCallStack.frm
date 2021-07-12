VERSION 5.00
Begin VB.Form frmShowCallStack 
   Caption         =   "3436[Debugger Call Stack]"
   ClientHeight    =   4710
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8445
   LinkTopic       =   "Form1"
   ScaleHeight     =   4710
   ScaleWidth      =   8445
   StartUpPosition =   3  'Windows Default
   Tag             =   "3436"
   Begin VB.TextBox txtCallStack 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   4335
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Text            =   "frmShowCallStack.frx":0000
      Top             =   120
      Width           =   7935
   End
End
Attribute VB_Name = "frmShowCallStack"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
   LoadResStrings Me
End Sub

Private Sub Form_Resize()
'MMD: Yeah, this is broken again... ha ha ha
   If Me.WindowState = vbMinimized Then Exit Sub  '02/11/2001 MMD

   If Me.Height >= 360 Then
      With txtCallStack
         .Left = 0
         .Top = 0
         .Width = Me.ScaleWidth
         .Height = Me.ScaleHeight
      End With
   End If
End Sub
