VERSION 5.00
Begin VB.Form frmBitmapProp 
   Caption         =   "Bitmap Properties - ID# ????"
   ClientHeight    =   1395
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6705
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   1395
   ScaleWidth      =   6705
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton butClose 
      Caption         =   "Close"
      Default         =   -1  'True
      Height          =   375
      Left            =   5520
      TabIndex        =   2
      Top             =   840
      Width           =   975
   End
   Begin VB.TextBox TxtPath 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   285
      Left            =   240
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   405
      Width           =   6255
   End
   Begin VB.Label Label1 
      Caption         =   "&Bitmap File Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
End
Attribute VB_Name = "frmBitmapProp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub butClose_Click()
   Me.Hide
   Unload Me
   frmMain.Show
End Sub

Private Sub Form_Load()
   frmBitmapProp.caption = "Bitmap Properties - ID# " + Trim(str(bmp.IdNo))
   TxtPath = bmp.pathName
   With Me
      .Left = frmIDE.Left + (frmIDE.Width - .Width) / 2
      .Top = frmIDE.Top + (frmIDE.Height - .Height) / 2
   End With
End Sub
