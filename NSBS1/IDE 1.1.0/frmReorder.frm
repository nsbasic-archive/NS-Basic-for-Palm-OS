VERSION 5.00
Begin VB.Form frmReorder 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Reorder Dialog"
   ClientHeight    =   3195
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6030
   Icon            =   "frmReorder.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   Begin VB.ListBox lstObjects 
      Height          =   2985
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   4455
   End
   Begin VB.CommandButton cmdDown 
      Enabled         =   0   'False
      Height          =   495
      Left            =   4680
      Picture         =   "frmReorder.frx":000C
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CommandButton cmdUp 
      Enabled         =   0   'False
      Height          =   495
      Left            =   4680
      Picture         =   "frmReorder.frx":044E
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   4680
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "frmReorder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public gForm As CForm
Public gProj As CProject
Private gObjs() As Object

Private Sub CancelButton_Click()
   Set gProj = Nothing
   Me.Hide
End Sub

Private Sub cmdDown_Click()
Dim strTemp As String
Dim ob As Object
Dim li As Integer

   li = lstObjects.ListIndex
   strTemp = lstObjects.List(li)
   lstObjects.RemoveItem li
   Set ob = gObjs(li)
   Set gObjs(li) = gObjs(li + 1)
   Set gObjs(li + 1) = ob
   li = li + 1
   lstObjects.AddItem strTemp, li
   lstObjects.ListIndex = li
End Sub

Private Sub cmdUp_Click()
Dim strTemp As String
Dim ob As Object
Dim li As Integer

   li = lstObjects.ListIndex
   strTemp = lstObjects.List(li)
   lstObjects.RemoveItem li
   Set ob = gObjs(li)
   Set gObjs(li) = gObjs(li - 1)
   Set gObjs(li - 1) = ob
   li = li - 1
   lstObjects.AddItem strTemp, li
   lstObjects.ListIndex = li
End Sub

Private Sub Form_Load()
Dim obj As Object
Dim i As Integer

   If Not gForm Is Nothing Then
      If gForm.ObjectCollection.count = 0 Then Exit Sub
'      If gForm.Controls.count = 0 Then Exit Sub
      ReDim gObjs(gForm.ObjectCollection.count - 1)
'      ReDim gObjs(gForm.Controls.count - 1)
      For i = 1 To gForm.ObjectCollection.count
'      For i = 1 To gForm.Controls.count
         lstObjects.AddItem gForm.ObjectCollection(i).obj.Name
         Set gObjs(i - 1) = gForm.ObjectCollection(i)
      Next
      'RES
      caption = "Tab Order - " & gForm.Name
   Else
      If gProj.FormCollection.count = 0 Then Exit Sub
'      If gProj.Forms.count = 0 Then Exit Sub
      ReDim gObjs(gProj.FormCollection.count - 1)
'      ReDim gObjs(gProj.Forms.count - 1)
      For i = 1 To gProj.FormCollection.count
'      For i = 1 To gProj.Forms.count
         lstObjects.AddItem gProj.FormCollection(i).Title
         Set gObjs(i - 1) = gProj.FormCollection(i)
      Next
      'RES
      caption = "Form Order - " & gProj.Name
   End If
   If lstObjects.ListCount <> 0 Then lstObjects.ListIndex = 0
End Sub

Private Sub lstObjects_Click()
   If lstObjects.ListIndex < 0 Then
      cmdUp.Enabled = False
      cmdDown.Enabled = False
   Else
      cmdUp.Enabled = True
      cmdDown.Enabled = True
      If lstObjects.ListIndex = 0 Then cmdUp.Enabled = False
      If lstObjects.ListIndex = lstObjects.ListCount - 1 Then cmdDown.Enabled = False
   End If
End Sub

Private Sub OKButton_Click()
Dim coll As New Collection
Dim i As Integer

   If Not gForm Is Nothing Then
      For i = 0 To UBound(gObjs)
         coll.Add gObjs(i)
      Next
      Set gForm.ObjectCollection = Nothing
      Set gForm.ObjectCollection = coll
   Else
      For i = 0 To UBound(gObjs)
         coll.Add gObjs(i)
      Next
      Set gProj.FormCollection = Nothing
      Set gProj.FormCollection = coll
   End If
   If gbProjectExplorer Then gfProjectExplorer.DisplayExplorer
   Set gForm = Nothing
   Set gProj = Nothing
   Me.Hide
End Sub
