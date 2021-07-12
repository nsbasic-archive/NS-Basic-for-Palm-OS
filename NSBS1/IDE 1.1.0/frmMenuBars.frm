VERSION 5.00
Begin VB.Form frmMenuBars 
   Caption         =   "Menu Editor -- Edit the Menubar Choices"
   ClientHeight    =   6225
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7305
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   6225
   ScaleWidth      =   7305
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton butEdit 
      Caption         =   "&Edit Choices..."
      Height          =   375
      Left            =   5880
      TabIndex        =   6
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CommandButton butAdd 
      Caption         =   "&Add"
      Height          =   375
      Left            =   5880
      TabIndex        =   4
      Top             =   1320
      Width           =   1215
   End
   Begin VB.ListBox outlMenu 
      CausesValidation=   0   'False
      Height          =   2595
      Left            =   240
      TabIndex        =   3
      Top             =   1320
      Width           =   5415
   End
   Begin VB.CommandButton butClose 
      Cancel          =   -1  'True
      Caption         =   "C&lose"
      Default         =   -1  'True
      Height          =   375
      Left            =   5880
      TabIndex        =   12
      Top             =   5640
      Width           =   1215
   End
   Begin VB.CommandButton butApply 
      Caption         =   "A&pply"
      Height          =   375
      Left            =   4440
      TabIndex        =   11
      Top             =   4740
      Width           =   975
   End
   Begin VB.CommandButton butInsert 
      Caption         =   "&Insert"
      Height          =   375
      Left            =   5880
      TabIndex        =   5
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CommandButton butDelete 
      Caption         =   "&Delete"
      Height          =   375
      Left            =   5880
      TabIndex        =   7
      Top             =   2760
      Width           =   1215
   End
   Begin VB.TextBox fldCaption 
      CausesValidation=   0   'False
      Height          =   285
      Left            =   480
      TabIndex        =   10
      Top             =   4800
      Width           =   3735
   End
   Begin VB.TextBox fldMenuName 
      Height          =   285
      Left            =   1800
      TabIndex        =   1
      Top             =   120
      Width           =   3855
   End
   Begin VB.Line Line1 
      X1              =   0
      X2              =   7320
      Y1              =   840
      Y2              =   840
   End
   Begin VB.Shape Shape1 
      DrawMode        =   1  'Blackness
      Height          =   1095
      Left            =   240
      Top             =   4320
      Width           =   5415
   End
   Begin VB.Label Label5 
      Caption         =   "Edit Selected Menubar Item"
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   4080
      Width           =   2175
   End
   Begin VB.Label Label3 
      Caption         =   "Menubar I&tems:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   960
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Menubar &Caption:"
      Height          =   255
      Left            =   480
      TabIndex        =   9
      Top             =   4440
      Width           =   1455
   End
   Begin VB.Label Label4 
      Caption         =   "&Menu Name: "
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   165
      Width           =   1455
   End
End
Attribute VB_Name = "frmMenuBars"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_Menu As CMenu
Private m_Project As CProject
Private m_nIndex As Integer

Public Property Let Project(prj As CProject)
   Set m_Project = prj
End Property

Public Property Let Menu(mnu As CMenu)
   Set m_Menu = mnu
End Property

Private Sub butEdit_click()
Dim fMenuDef As New frmMenuDef

   If outlMenu.ListIndex < 0 Then
      MsgBox "must select a menu bar first"
      Exit Sub
   End If
   fMenuDef.Project = m_Project
   fMenuDef.Menu = m_Menu
   fMenuDef.MenuBar = m_Menu.MenuBars(outlMenu.ListIndex + 1)
   fMenuDef.Show vbModal
End Sub

Private Sub butApply_Click()
Dim strCaption As String

   If outlMenu.ListIndex = -1 Then
      strCaption = fldCaption.Text
      InsertMenubar
      fldCaption = strCaption
   End If

   If (outlMenu.ListIndex + 1) > m_Menu.MenuBars.count Then
      MsgBox "Use insert to insert a new item first"
      Exit Sub
   End If

   m_Menu.MenuBars(outlMenu.ListIndex + 1).caption = ReplaceQuotes(fldCaption.Text)
   Refresh
End Sub

Private Sub butDelete_Click()
Dim i As Integer

   If outlMenu.ListIndex < 0 Then
      MsgBox "Nothing is selected"
      Exit Sub
   End If

   'MMD: How is this clause even possible??
   If outlMenu.ListIndex + 1 > m_Menu.MenuBars.count Then
      MsgBox "Can't delete"
      Exit Sub
   End If
  
   m_Project.Dirty = True
   m_Menu.MenuBars.Remove outlMenu.ListIndex + 1
   m_nIndex = m_nIndex - 1
'  If outlMenu.ListIndex + 1 > m_Menu.MenuBars.count Then
'     outlMenu.ListIndex = m_Menu.MenuBars.count - 1
'  End If
'  mnubarCurItem = outlMenu.ListIndex
   Refresh
End Sub

Private Sub butClose_Click()
   If m_Menu.Name = "" Then m_Menu.Name = "<untitled>"

   'cant leave it empty
   If m_Menu.MenuBars.count = 0 Then InsertMenubar

   If m_Menu.MenuBars.count = 1 _
         And (m_Menu.MenuBars(1).caption = "") _
         Or (m_Menu.MenuBars(1).caption = " ") Then
      m_Menu.MenuBars(1).caption = "<untitled>"
   End If

   Unload Me
End Sub

Private Sub butInsert_Click()
   InsertMenubar
End Sub

Private Sub InsertMenubar()
Dim mBar As New CMenuBar

   'Create MenuBar, add to project and menu
   mBar.IdNo = m_Project.GetNextSeqNo
   mBar.SetGlobalID m_Menu.GlobalID
   m_Project.Dirty = True
   If m_Menu.MenuBars.count = 0 Then
      m_Menu.MenuBars.Add mBar, str(mBar.IdNo)
   Else
      m_Menu.MenuBars.Add mBar, str(mBar.IdNo), outlMenu.ListIndex + 1
   End If

   'Now add to list and select if not selected
   Refresh
   If outlMenu.ListCount = 1 Then outlMenu.ListIndex = 0
End Sub

Private Sub butAdd_Click()
Dim mBar As New CMenuBar

   m_Project.Dirty = True
   mBar.IdNo = m_Project.GetNextSeqNo
   mBar.SetGlobalID m_Menu.GlobalID
   If m_Menu.MenuBars.count = 0 Then
      m_Menu.MenuBars.Add mBar, str(mBar.IdNo)
   Else
      m_Menu.MenuBars.Add mBar, str(mBar.IdNo), , outlMenu.ListIndex + 1
   End If
   m_nIndex = outlMenu.ListIndex + 1
   Refresh
End Sub

Private Sub fldMenuName_Change()
   m_Project.Dirty = True
   m_Menu.Name = fldMenuName.Text
End Sub

Private Sub Form_Load()
'   Unload frmMenuDef
   m_nIndex = -1
End Sub

Private Sub Form_Paint()
Dim m As Integer
Dim i As Integer
Dim work As String
Dim mBar As CMenuBar
  
   outlMenu.fontName = gLabelFontName
   fldCaption.fontName = gLabelFontName
   outlMenu.Clear
   fldMenuName.Text = m_Menu.Name

   'MMD: You're serious about this??
'   m = 0
'   For Each mBar In m_Menu.MenuBars
'      m = m + 1
'      work = mBar.caption
'      Do While Len(work) < 40
'         work = work + " "
'      Loop
'      outlMenu.AddItem work
'   Next

   For Each mBar In m_Menu.MenuBars
      outlMenu.AddItem mBar.caption
   Next

  'now set flds of cur item
   If m_nIndex = -1 And m_Menu.MenuBars.count > 0 Then
      m_nIndex = 0
   End If
   outlMenu.ListIndex = m_nIndex
   If m_Menu.MenuBars.count = 0 Then
      fldCaption = ""
      butDelete.Enabled = False
      butEdit.Enabled = False
   Else
'      Set mnuBar = m_Menu.MenuBars(outlMenu.ListIndex + 1)
      fldCaption = m_Menu.MenuBars(m_nIndex + 1).caption
      butDelete.Enabled = True
      butEdit.Enabled = True
   End If
End Sub

Private Sub outlMenu_Click()
   m_nIndex = outlMenu.ListIndex

'   If outlMenu.ListIndex = -1 Then
'      Set mnuBar = Nothing
'      mnubarCurItem = 0
'   Else
''      Set menuSave = Menu
'      Set mnuBar = m_Menu.MenuBars(outlMenu.ListIndex + 1)
'      mnubarCurItem = outlMenu.ListIndex
'   End If
End Sub

Private Sub outlMenu_DblClick()
   butEdit_click
End Sub
