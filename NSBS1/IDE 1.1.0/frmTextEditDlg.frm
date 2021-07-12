VERSION 5.00
Begin VB.Form frmTextEditDlg 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   4215
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   4215
   Icon            =   "frmTextEditDlg.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4215
   ScaleWidth      =   4215
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton CancelButton 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   840
      TabIndex        =   2
      Top             =   3720
      Width           =   1575
   End
   Begin VB.TextBox txtEdit 
      Height          =   3495
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   120
      Width           =   3975
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "&OK"
      Height          =   375
      Left            =   2520
      TabIndex        =   1
      Top             =   3720
      Width           =   1575
   End
End
Attribute VB_Name = "frmTextEditDlg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_strText As String
Public Cancelled As Boolean

Public Property Get Text() As String
   Text = m_strText
End Property

Public Property Let Text(ByVal strText As String)
   m_strText = strText
   txtEdit.Text = m_strText
End Property

Private Sub Form_GotFocus()
   txtEdit.SetFocus
End Sub

Private Sub Form_Load()
   LoadResStrings Me ', False

   'If gbPlainText Then
   '   txtEdit.font.Name = gLabelFontName
   '   txtEdit.font.Charset = gLabelCharset
   'End If
   Cancelled = False
End Sub

Public Sub OKButton_Click()
   m_strText = txtEdit.Text
   Unload Me
End Sub

Public Sub CancelButton_Click()
   Cancelled = True
   Unload Me
End Sub

Private Sub txtEdit_KeyUp(KeyCode As Integer, Shift As Integer)
   If (Shift And vbCtrlMask) And KeyCode = Asc("A") Then
      txtEdit.SelStart = 0
      txtEdit.SelLength = Len(txtEdit.Text)
   End If
End Sub
