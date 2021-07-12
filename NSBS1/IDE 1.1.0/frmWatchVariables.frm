VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmWatchVariables 
   Caption         =   "3431[Watch Variable List]"
   ClientHeight    =   8025
   ClientLeft      =   165
   ClientTop       =   855
   ClientWidth     =   6780
   Icon            =   "frmWatchVariables.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   8025
   ScaleWidth      =   6780
   StartUpPosition =   3  'Windows Default
   Tag             =   "3431"
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   2280
      Top             =   7080
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   13
      ImageHeight     =   13
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   3
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmWatchVariables.frx":08CA
            Key             =   "nonsubscriptedVariable"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmWatchVariables.frx":09C4
            Key             =   "subscriptedVariableClosed"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmWatchVariables.frx":0ABE
            Key             =   "subscriptedVariableOpen"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TreeView Tree 
      Height          =   6615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5535
      _ExtentX        =   9763
      _ExtentY        =   11668
      _Version        =   393217
      Style           =   7
      ImageList       =   "ImageList1"
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Menu mnuWatchAdd 
      Caption         =   "3432"
   End
   Begin VB.Menu mnuWatchDelete 
      Caption         =   "3433"
   End
   Begin VB.Menu mnuWatchDeleteAll 
      Caption         =   "3434"
   End
End
Attribute VB_Name = "frmWatchVariables"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'entire form is new 04012005

Private Sub Form_Load()
   LoadResStrings Me
End Sub

Private Sub Form_Resize()
'MMD: Yeah, this is broken again... ha ha ha
   If Me.WindowState = vbMinimized Then Exit Sub  '02/11/2001 MMD

   If Me.Height >= 360 Then
      With Tree
         .Left = 0
         .Top = 0
         .Width = Me.ScaleWidth
         .Height = Me.ScaleHeight
      End With
   End If
End Sub

Private Sub mnuWatchAdd_Click()
    frmAddWatchVariable.Show 1
    
    needToRefreshWatchVars = True
    'Me.Hide
End Sub

Private Sub mnuWatchDelete_Click()
    Dim index As Integer
    Dim Tag As Long
    
    index = Tree.SelectedItem.index
    Tag = Tree.SelectedItem.Tag
    
    If Tag <> 0 And index > 0 Then
       Do While Tag = Tree.Nodes(index - 1).Tag
          index = index - 1
       Loop
       If Tree.Nodes(index - 1).Tag = 0 Then index = index - 1
    End If
    
    'have the starting point of deletes
    Tag = Tree.Nodes(index).Tag
    If Tag = 0 Then Tag = Tree.Nodes(index + 1).Tag
    
    Tree.Nodes.Remove (index)
    Do While index < Tree.Nodes.count
      If Tree.Nodes(index).Tag <> Tag Then
          Exit Do
       End If
       Tree.Nodes.Remove (index)
    Loop
End Sub

Private Sub mnuWatchDeleteAll_Click()
   Do While frmWatchVariables.Tree.Nodes.count > 0
        frmWatchVariables.Tree.Nodes.Remove (0)
   Loop
End Sub
