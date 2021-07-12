VERSION 5.00
Begin VB.Form frmMenuSel 
   Caption         =   "Menu Editor -- Select a Menu to Edit"
   ClientHeight    =   4545
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7305
   ControlBox      =   0   'False
   LinkTopic       =   "Menu Selection"
   ScaleHeight     =   4545
   ScaleWidth      =   7305
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton butDelete 
      Caption         =   "&Delete"
      Height          =   375
      Left            =   5880
      TabIndex        =   4
      Top             =   1440
      Width           =   1215
   End
   Begin VB.CommandButton butClose 
      Cancel          =   -1  'True
      Caption         =   "&Close"
      Default         =   -1  'True
      Height          =   375
      Left            =   5880
      TabIndex        =   5
      Top             =   3960
      Width           =   1215
   End
   Begin VB.CommandButton butNew 
      Caption         =   "&New"
      Height          =   375
      Left            =   5880
      TabIndex        =   2
      Top             =   480
      Width           =   1215
   End
   Begin VB.ListBox listMenus 
      Height          =   3180
      ItemData        =   "frmMenuSel.frx":0000
      Left            =   240
      List            =   "frmMenuSel.frx":0002
      TabIndex        =   1
      Top             =   480
      Width           =   5415
   End
   Begin VB.CommandButton butEdit 
      Caption         =   "&Edit..."
      Height          =   375
      Left            =   5880
      TabIndex        =   3
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "&Menus"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   165
      Width           =   855
   End
End
Attribute VB_Name = "frmMenuSel"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private m_Project As CProject

Public Property Let Project(ByVal proj As CProject)
   Set m_Project = proj
End Property

Public Property Get Project() As CProject
   Set Project = m_Project
End Property

Private Sub butClose_Click()
   Unload Me
End Sub 'butClose_Click

Private Sub butDelete_Click()
   If listMenus.ListIndex < 0 Or listMenus.ListIndex > m_Project.MenuCollection.count - 1 Then
'      MsgBox "Must select a menu to delete"
      Exit Sub
   End If
   m_Project = True
   m_Project.MenuCollection.Remove listMenus.ListIndex + 1
   listMenus.RemoveItem listMenus.ListIndex
End Sub 'butDelete_Click

Private Sub ViewMenu(Menu As CMenu)
Dim fMenuBars As New frmMenuBars

   fMenuBars.Project = m_Project
   fMenuBars.Menu = Menu
   fMenuBars.Show vbModal
End Sub 'ViewMenu

Private Sub butEdit_click()
   If listMenus.ListIndex < 0 Or listMenus.ListIndex > m_Project.MenuCollection.count - 1 Then
'      MsgBox "Must select a menu to edit"
      Exit Sub
   End If
   ViewMenu m_Project.MenuCollection(listMenus.ListIndex + 1)
End Sub 'butEdit_Click

Private Sub butNew_Click()
Dim mnu As New CMenu

   m_Project.AddMenu mnu
   ViewMenu mnu
End Sub 'butNew_Click

Private Sub Form_Paint()
Dim menu2 As CMenu

   listMenus.Clear

   For Each menu2 In m_Project.MenuCollection
      listMenus.AddItem menu2.Name
   Next
   If m_Project.MenuCollection.count > 0 Then
      listMenus.ListIndex = 0
      butDelete.Enabled = True
   Else
      listMenus.ListIndex = -1
      butDelete.Enabled = False
   End If
   If listMenus.ListIndex >= 0 Then
      butEdit.Enabled = True
   Else
      butEdit.Enabled = False
   End If
End Sub

Private Sub listMenus_DblClick()
   butEdit_click
End Sub
