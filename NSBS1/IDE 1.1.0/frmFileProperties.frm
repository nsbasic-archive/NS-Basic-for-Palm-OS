VERSION 5.00
Begin VB.Form frmFileProperties 
   Caption         =   "<File> Properties"
   ClientHeight    =   1545
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6705
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   1545
   ScaleWidth      =   6705
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton butClose 
      Caption         =   "Close"
      Default         =   -1  'True
      Height          =   375
      Left            =   5520
      TabIndex        =   0
      Top             =   960
      Width           =   975
   End
   Begin VB.TextBox TxtPath 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   285
      Left            =   240
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   405
      Width           =   6255
   End
   Begin VB.Label Label1 
      Caption         =   "Path Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   855
   End
End
Attribute VB_Name = "frmFileProperties"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_Ob As Object

Private Sub butClose_Click()
   Unload Me
End Sub

Private Sub Form_Load()
   TxtPath.Text = m_Ob.Path
End Sub

Public Property Get Object() As Object
   Object = m_Ob
End Property

Public Property Let Object(ByRef ob As Object)
   Set m_Ob = ob
End Property
