VERSION 5.00
Begin VB.Form frmMenuDef 
   Caption         =   "Menu Editor -- Edit Dropdown Choices"
   ClientHeight    =   6225
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7305
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   6225
   ScaleWidth      =   7305
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton butAdd 
      Caption         =   "&Add"
      Height          =   375
      Left            =   5880
      TabIndex        =   6
      Top             =   1320
      Width           =   1215
   End
   Begin VB.TextBox menuOption 
      CausesValidation=   0   'False
      Height          =   285
      Left            =   1800
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   480
      Width           =   3855
   End
   Begin VB.ListBox outlMenu 
      CausesValidation=   0   'False
      Height          =   2595
      Left            =   240
      TabIndex        =   5
      Top             =   1320
      Width           =   5415
   End
   Begin VB.TextBox fldMenuName 
      Height          =   285
      Left            =   1800
      TabIndex        =   1
      Top             =   120
      Width           =   3855
   End
   Begin VB.CommandButton butApply 
      Caption         =   "A&pply"
      Height          =   375
      Left            =   4440
      TabIndex        =   13
      Top             =   4740
      Width           =   975
   End
   Begin VB.CommandButton butClose 
      Cancel          =   -1  'True
      Caption         =   "C&lose"
      Default         =   -1  'True
      Height          =   375
      Left            =   5880
      TabIndex        =   14
      Top             =   5640
      Width           =   1215
   End
   Begin VB.TextBox fldCaption 
      CausesValidation=   0   'False
      Height          =   285
      Left            =   480
      TabIndex        =   12
      Top             =   4800
      Width           =   3735
   End
   Begin VB.CommandButton butDelete 
      Caption         =   "&Delete"
      Height          =   375
      Left            =   5880
      TabIndex        =   9
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CommandButton butInsert 
      Caption         =   "&Insert"
      Height          =   375
      Left            =   5880
      TabIndex        =   7
      Top             =   1800
      Width           =   1215
   End
   Begin VB.CommandButton butEdit 
      Caption         =   "&Edit Code..."
      Height          =   375
      Left            =   5880
      TabIndex        =   8
      Top             =   2280
      Width           =   1215
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
   Begin VB.Label Label7 
      Caption         =   "Edit Selected Dropdown Choice"
      Height          =   255
      Left            =   240
      TabIndex        =   10
      Top             =   4080
      Width           =   2535
   End
   Begin VB.Label Label3 
      Caption         =   "D&ropdown Choices:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   960
      Width           =   1455
   End
   Begin VB.Label Label5 
      Caption         =   "Menubar &Option:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   525
      Width           =   1455
   End
   Begin VB.Label Label4 
      Caption         =   "&Menu Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   165
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Menu Dropdown &Caption:"
      Height          =   255
      Left            =   480
      TabIndex        =   11
      Top             =   4440
      Width           =   2055
   End
End
Attribute VB_Name = "frmMenuDef"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private m_Project As CProject
Private m_Menu As CMenu
Private m_MenuBar As CMenuBar
Private m_nIndex As Integer

Public Property Let Project(ByVal proj As CProject)
   Set m_Project = proj
End Property

Public Property Let Menu(ByVal mnu As CMenu)
   Set m_Menu = mnu
End Property

Public Property Let MenuBar(ByVal mBar As CMenuBar)
   Set m_MenuBar = mBar
End Property

Private Sub butEdit_click()
Dim fCode As New frmCode

   If outlMenu.ListIndex < 0 Then
      MsgBox "No item selected."
      Exit Sub
   End If

   If outlMenu.ListIndex + 1 > m_MenuBar.MenuElems.count Then
      MsgBox "Highlight a dropdown menu element, please."
      Exit Sub
   End If

   fCode.Text = m_MenuBar.MenuElems(outlMenu.ListIndex + 1).menu_script
'   editorSource = "menu"
   fCode.Show vbModal
End Sub

Private Sub butApply_Click()
Dim strCaption As String
   
   If outlMenu.ListIndex = -1 Then
      strCaption = fldCaption.Text
      insert_menuelem
      fldCaption.Text = strCaption
   End If

   If outlMenu.ListIndex + 1 > m_MenuBar.MenuElems.count Then
      MsgBox "Use insert to insert a new item first"
      Exit Sub
   End If

   m_MenuBar.MenuElems(outlMenu.ListIndex + 1).caption = ReplaceQuotes(fldCaption.Text)
   Refresh
End Sub

Private Sub butDelete_Click()
Dim i As Integer

   If outlMenu.ListIndex < 0 Then
      MsgBox "No item selected."
      Exit Sub
   End If

   'MMD: How is this clause even possible??
   If outlMenu.ListIndex + 1 > m_MenuBar.MenuElems.count Then
      MsgBox "Can't delete!"
      Exit Sub
   End If

   m_Project.Dirty = True
   m_MenuBar.MenuElems.Remove outlMenu.ListIndex + 1
   m_nIndex = m_nIndex - 1
'
'  'need to change indent of items after item deleted
'  If outlMenu.ListIndex + 1 > mnuBar.MenuElems.count Then
'     outlMenu.ListIndex = mnuBar.MenuElems.count - 1
'  End If
'  mnuCurItem = outlMenu.ListIndex
   Refresh
End Sub

Private Sub butClose_Click()
   Unload Me
End Sub

Private Sub butInsert_Click()
   insert_menuelem
End Sub

Private Sub insert_menuelem()
Dim mnuElem As New CMenuElem

   'Create MenuElem, add to project and MenuBar
   mnuElem.IdNo = m_Project.GetNextSeqNo
   mnuElem.SetGlobalID m_MenuBar.GlobalID
   m_Project.Dirty = True
   If m_MenuBar.MenuElems.count = 0 Then
      m_MenuBar.MenuElems.Add mnuElem
   Else
      m_MenuBar.MenuElems.Add mnuElem, , outlMenu.ListIndex + 1
   End If
  
   'Now add to list and select if not selected
   Refresh
   If outlMenu.ListCount = 1 Then outlMenu.ListIndex = 0
End Sub

Private Sub butAdd_Click()
Dim mnuElem As New CMenuElem

   m_Project.Dirty = True
   mnuElem.IdNo = m_Project.GetNextSeqNo
   mnuElem.SetGlobalID m_MenuBar.GlobalID
   If m_MenuBar.MenuElems.count = 0 Then
      m_MenuBar.MenuElems.Add mnuElem
   Else
      m_MenuBar.MenuElems.Add mnuElem, , , outlMenu.ListIndex + 1
   End If
   m_nIndex = outlMenu.ListIndex + 1
   Refresh
End Sub

Private Sub fldMenuName_Change()
   m_Project.Dirty = True
   m_Menu.Name = fldMenuName.Text
End Sub

Private Sub menuOption_Change()
   m_Project.Dirty = True
   m_MenuBar.caption = menuOption.Text
End Sub

Private Sub Form_Load()
   m_nIndex = -1
End Sub

Private Sub Form_Paint()
'Dim m As Integer
'Dim i As Integer
'Dim work As String
Dim mnuElem As CMenuElem

   outlMenu.fontName = gLabelFontName
   fldCaption.fontName = gLabelFontName
   menuOption.fontName = gLabelFontName
   outlMenu.Clear
   fldMenuName.Text = m_Menu.Name
   menuOption.Text = m_MenuBar.caption

   'MMD: There's more pad here than Hannibal Lechter's cell
'   m = 0
'   For Each mnu In mnuBar.MenuElems
'      m = m + 1
'      work = mnu.caption
'      Do While Len(work) < 40
'        work = work + " "
'      Loop
'      outlMenu.AddItem work
'   Next
   For Each mnuElem In m_MenuBar.MenuElems
      outlMenu.AddItem mnuElem.caption
   Next

   'now set flds of cur item
   If m_nIndex = -1 And m_MenuBar.MenuElems.count > 0 Then
      m_nIndex = 0
   End If
   outlMenu.ListIndex = m_nIndex
   If m_MenuBar.MenuElems.count = 0 Then
      fldCaption = ""
      butDelete.Enabled = False
      butEdit.Enabled = False
   Else
      fldCaption = m_MenuBar.MenuElems(m_nIndex + 1).caption
      butDelete.Enabled = True
      butEdit.Enabled = True
   End If
End Sub

Private Sub outlMenu_Click()
   m_nIndex = outlMenu.ListIndex
'   If outlMenu.ListIndex = -1 Then
'      Set mnu = Nothing
'      mnuCurItem = 0
'   Else
'      Set mnu = mnuBar.MenuElems.Item(outlMenu.ListIndex + 1)
'      mnuCurItem = outlMenu.ListIndex
'   End If
End Sub

Private Sub outlMenu_DblClick()
   butEdit_click
End Sub
