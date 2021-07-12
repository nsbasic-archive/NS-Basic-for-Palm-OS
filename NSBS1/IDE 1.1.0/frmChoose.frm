VERSION 5.00
Begin VB.Form frmChoose 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "List to Choose From"
   ClientHeight    =   4455
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4335
   Icon            =   "frmChoose.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4455
   ScaleWidth      =   4335
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton butCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   75
      TabIndex        =   0
      Top             =   3915
      Width           =   975
   End
   Begin VB.ListBox lst 
      Height          =   3765
      Left            =   15
      TabIndex        =   1
      Top             =   15
      Width           =   4290
   End
End
Attribute VB_Name = "frmChoose"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub butCancel_Click()
  'Me.Hide   '1114
  frmCode.Show 1  '1114
End Sub

Private Sub Form_Paint()
  Dim v As DataElement
  Dim s As view
  lst.Clear
  If chooseType = "v" Then
    For Each v In model.DataCollection
      lst.AddItem v.name
    Next
  Else
    For Each s In model.ViewCollection
      lst.AddItem s.name
    Next
  End If
  
End Sub

Private Sub lst_Click()
  'If lst.ListIndex < 0 Or lst.ListIndex > lst.ListCount - 1 Then Exit Sub
  'frmCode.Script.text = left(frmCode.Script.text, _
   '                   frmCode.Script.SelStart) _
   '                   + lst.text _
   '                   + right(frmCode.Script.text, _
   '                   Len(frmCode.Script) - frmCode.Script.SelStart)
  'Me.Hide  1114
  'frmCode.Show 1  '1114
End Sub
