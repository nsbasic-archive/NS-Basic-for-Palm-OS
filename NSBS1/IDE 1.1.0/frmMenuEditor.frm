VERSION 5.00
Begin VB.Form frmMenuEditor 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Menu Editor"
   ClientHeight    =   7425
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   7125
   Icon            =   "frmMenuEditor.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7425
   ScaleWidth      =   7125
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Tag             =   "1600"
   Begin VB.CommandButton butMove 
      Caption         =   "&Next"
      Default         =   -1  'True
      Height          =   495
      Index           =   2
      Left            =   240
      TabIndex        =   10
      Tag             =   "1618"
      ToolTipText     =   "1609"
      Top             =   2640
      Width           =   855
   End
   Begin VB.ComboBox cmbMenu 
      Height          =   315
      Left            =   2520
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   120
      Width           =   3255
   End
   Begin VB.TextBox txtCaption 
      Height          =   375
      Left            =   2520
      TabIndex        =   3
      Top             =   520
      Width           =   3255
   End
   Begin VB.TextBox txtProcName 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   375
      Left            =   2520
      TabIndex        =   5
      Top             =   980
      Width           =   3255
   End
   Begin VB.ComboBox cmbCommand 
      Height          =   315
      Left            =   2520
      Style           =   2  'Dropdown List
      TabIndex        =   7
      Top             =   1440
      Width           =   3255
   End
   Begin VB.CommandButton butMove 
      Height          =   375
      Index           =   0
      Left            =   240
      Picture         =   "frmMenuEditor.frx":038A
      Style           =   1  'Graphical
      TabIndex        =   8
      ToolTipText     =   "1608"
      Top             =   2040
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton butMove 
      Height          =   375
      Index           =   1
      Left            =   720
      Picture         =   "frmMenuEditor.frx":06CC
      Style           =   1  'Graphical
      TabIndex        =   9
      ToolTipText     =   "1609"
      Top             =   2040
      UseMaskColor    =   -1  'True
      Width           =   375
   End
   Begin VB.CommandButton butAction 
      Caption         =   "Insert &MenuBar"
      Height          =   495
      Index           =   0
      Left            =   1320
      TabIndex        =   11
      Tag             =   "1603"
      Top             =   2040
      Width           =   2175
   End
   Begin VB.CommandButton butAction 
      Caption         =   "Add Menu&Bar"
      Height          =   495
      Index           =   1
      Left            =   1320
      TabIndex        =   12
      Tag             =   "1604"
      Top             =   2640
      Width           =   2175
   End
   Begin VB.CommandButton butAction 
      Caption         =   "Insert D&ropdown"
      Height          =   495
      Index           =   2
      Left            =   3600
      TabIndex        =   13
      Tag             =   "1605"
      Top             =   2040
      Width           =   2175
   End
   Begin VB.CommandButton butAction 
      Caption         =   "Add Dro&pdown"
      Height          =   495
      Index           =   3
      Left            =   3600
      TabIndex        =   14
      Tag             =   "1606"
      Top             =   2640
      Width           =   2175
   End
   Begin VB.CommandButton butAction 
      Caption         =   "&Delete"
      Height          =   495
      Index           =   4
      Left            =   5880
      TabIndex        =   15
      Tag             =   "1017"
      Top             =   2040
      Width           =   1095
   End
   Begin VB.ListBox lstMenu 
      Height          =   3570
      ItemData        =   "frmMenuEditor.frx":0A0E
      Left            =   120
      List            =   "frmMenuEditor.frx":0A10
      TabIndex        =   17
      Top             =   3600
      Width           =   6855
   End
   Begin VB.CommandButton butOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   5880
      TabIndex        =   18
      Tag             =   "1619"
      Top             =   120
      Width           =   1095
   End
   Begin VB.Line Line1 
      X1              =   120
      X2              =   7080
      Y1              =   1920
      Y2              =   1920
   End
   Begin VB.Label Label4 
      Caption         =   "M&enu:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Tag             =   "1610"
      Top             =   150
      Width           =   2295
   End
   Begin VB.Label Label1 
      Caption         =   "&Caption:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Tag             =   "1611"
      Top             =   600
      Width           =   2295
   End
   Begin VB.Label Label2 
      Caption         =   "Proc Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Tag             =   "1612"
      Top             =   1080
      Width           =   2295
   End
   Begin VB.Label Label3 
      Caption         =   "Co&mmand:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Tag             =   "1613"
      Top             =   1470
      Width           =   2295
   End
   Begin VB.Label Label5 
      Caption         =   "Menu &Layout:"
      Height          =   255
      Left            =   240
      TabIndex        =   16
      Tag             =   "1614"
      Top             =   3360
      Width           =   3015
   End
   Begin VB.Menu mnuRight 
      Caption         =   "Right-Click"
      Visible         =   0   'False
      Begin VB.Menu mnuRightMove 
         Caption         =   "1601"
         Index           =   0
      End
      Begin VB.Menu mnuRightMove 
         Caption         =   "1602"
         Index           =   1
      End
      Begin VB.Menu mnuRightBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuRightAdd 
         Caption         =   "1603"
         Index           =   0
      End
      Begin VB.Menu mnuRightAdd 
         Caption         =   "1604"
         Index           =   1
      End
      Begin VB.Menu mnuRightAdd 
         Caption         =   "-"
         Index           =   2
      End
      Begin VB.Menu mnuRightAdd 
         Caption         =   "1605"
         Index           =   3
      End
      Begin VB.Menu mnuRightAdd 
         Caption         =   "1606"
         Index           =   4
      End
      Begin VB.Menu mnuRightAdd 
         Caption         =   "-"
         Index           =   5
      End
      Begin VB.Menu mnuRightAdd 
         Caption         =   "1017"
         Index           =   6
      End
   End
End
Attribute VB_Name = "frmMenuEditor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_Project As CProject
Private m_Menu As CMenu
Private m_bMenuBar As Boolean
Private m_Target As Object
Private m_bProgramSet As Boolean
Private Const kMenuBar As Long = 100000
Private Const kMenuElem As Long = 200000
Private Const kEditMenuName As Integer = -1
Private Const kDeleteMenu As Integer = -2
Private Const kAddNewMenu As Integer = -3

Public Property Let Project(ByVal proj As CProject)
   Set m_Project = proj
End Property

Public Property Let Menu(ByVal mnu As CMenu)
   Set m_Menu = mnu
End Property

Private Sub butAction_Click(index As Integer)
Dim mBarNew As New CMenuBar
Dim mElemNew As New CMenuElem
Dim mBar As CMenuBar
Dim mElem As CMenuElem
Dim nIndex As Integer

   m_Project.Dirty = True
   Select Case index
   Case 0 'Insert MenuBar
      'Locate current MenuBar, and insert new MenuBar
      mBarNew.IdNo = m_Project.GetNextSeqNo
      mBarNew.SetGlobalID m_Menu.GlobalID
      If lstMenu.ListIndex < 0 Then
         m_Menu.MenuBars.Add mBarNew, str(mBarNew.IdNo)
         nIndex = 0
      Else
         Set mBar = LocateMenuBar(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar)
         m_Menu.MenuBars.Add mBarNew, str(mBarNew.IdNo), MenuBarIndex(mBar.IdNo)
         nIndex = GetListIndex(mBar.IdNo)
      End If
      lstMenu.AddItem mBarNew.caption, nIndex
      lstMenu.ItemData(nIndex) = kMenuBar + mBarNew.IdNo
      lstMenu.ListIndex = nIndex
   Case 1 'Add MenuBar
      'Locate current MenuBar, and insert new MenuBar
      mBarNew.IdNo = m_Project.GetNextSeqNo
      mBarNew.SetGlobalID m_Menu.GlobalID
      If lstMenu.ListCount < 1 Then
         m_Menu.MenuBars.Add mBarNew, str(mBarNew.IdNo)
         nIndex = 0
      Else
         Set mBar = LocateMenuBar(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar)
         m_Menu.MenuBars.Add mBarNew, str(mBarNew.IdNo), , MenuBarIndex(mBar.IdNo)
         If mBar.MenuElems.count > 0 Then
            nIndex = GetListIndex(mBar.MenuElems(mBar.MenuElems.count).IdNo) + 1
         Else
            nIndex = lstMenu.ListIndex + 1
         End If
      End If
      lstMenu.AddItem mBarNew.caption, nIndex
      lstMenu.ItemData(nIndex) = kMenuBar + mBarNew.IdNo
      lstMenu.ListIndex = nIndex
   Case 2 'Insert MenuElem
      'Locate current MenuElem, and insert new MenuElem
      Set mBar = LocateMenuBar(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar)
      mElemNew.IdNo = m_Project.GetNextSeqNo
      mElemNew.SetGlobalID mBar.GlobalID
      If m_bMenuBar Then
         If mBar.MenuElems.count = 0 Then
            mBar.MenuElems.Add mElemNew, Trim(str(mElemNew.IdNo))
         Else
            mBar.MenuElems.Add mElemNew, Trim(str(mElemNew.IdNo)), 1
         End If
         nIndex = GetListIndex(mBar.IdNo) + 1
      Else
         Set mElem = LocateMenuElem(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar)
         mBar.MenuElems.Add mElemNew, Trim(str(mElemNew.IdNo)), MenuElemIndex(mBar.IdNo, mElem.IdNo)
         nIndex = GetListIndex(mElem.IdNo)
      End If
      lstMenu.AddItem "..." & mElemNew.caption, nIndex
      lstMenu.ItemData(nIndex) = kMenuElem + mElemNew.IdNo
      lstMenu.ListIndex = nIndex
   Case 3 'Add MenuElem
      Set mBar = LocateMenuBar(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar)
      mElemNew.IdNo = m_Project.GetNextSeqNo
      mElemNew.SetGlobalID mBar.GlobalID
      If m_bMenuBar Then
         If mBar.MenuElems.count = 0 Then
            mBar.MenuElems.Add mElemNew, Trim(str(mElemNew.IdNo))
         Else
            mBar.MenuElems.Add mElemNew, Trim(str(mElemNew.IdNo)), , mBar.MenuElems.count
         End If
         If mBar.MenuElems.count > 1 Then
            nIndex = GetListIndex(mBar.MenuElems(mBar.MenuElems.count - 1).IdNo) + 1
         Else
            nIndex = GetListIndex(mBar.IdNo) + 1
         End If
      Else
         Set mElem = LocateMenuElem(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar)
         mBar.MenuElems.Add mElemNew, Trim(str(mElemNew.IdNo)), , MenuElemIndex(mBar.IdNo, mElem.IdNo)
         nIndex = GetListIndex(mElem.IdNo) + 1
      End If
      lstMenu.AddItem "..." & mElemNew.caption, nIndex
      lstMenu.ItemData(nIndex) = kMenuElem + mElemNew.IdNo
      lstMenu.ListIndex = nIndex
   Case 4 'Delete
      If lstMenu.ListIndex <> -1 Then
         Set mBar = LocateMenuBar(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar)
         nIndex = lstMenu.ListIndex 'GetListIndex(mBar.IdNo)
         If m_bMenuBar Then
            m_Menu.MenuBars.Remove MenuBarIndex(mBar.IdNo)
            lstMenu.RemoveItem nIndex
            Do While nIndex < lstMenu.ListCount
               If lstMenu.ItemData(nIndex) > kMenuElem Then
                  lstMenu.RemoveItem nIndex
               Else
                  Exit Do
               End If
            Loop
         Else
            mBar.MenuElems.Remove Trim(str(lstMenu.ItemData(nIndex) Mod kMenuBar))
            lstMenu.RemoveItem nIndex
         End If
         Set m_Target = Nothing
         If nIndex >= lstMenu.ListCount Then nIndex = lstMenu.ListCount - 1
      End If
   End Select
   UpdateDialog
   lstMenu.ListIndex = nIndex
End Sub

Private Sub butMove_Click(index As Integer)
Dim nIndex As Integer
Dim nItemData As Long

   Select Case index
   Case 0 'Move Up
      If lstMenu.ListIndex >= 0 Then
         nItemData = lstMenu.ItemData(lstMenu.ListIndex)
         If lstMenu.ItemData(lstMenu.ListIndex) > kMenuElem Then
            'Move a menu element
            m_Menu.MoveElement LocateMenuElem(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar), vbKeyUp
         Else
            'Move a menu bar
            m_Menu.MoveBar LocateMenuBar(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar), vbKeyUp
         End If
         SetMenu
         For nIndex = 0 To lstMenu.ListCount - 1
            If lstMenu.ItemData(nIndex) = nItemData Then
               lstMenu.ListIndex = nIndex
               Exit For
            End If
         Next
      End If
   Case 1 'Move Down
      If lstMenu.ListIndex >= 0 Then
         nItemData = lstMenu.ItemData(lstMenu.ListIndex)
         If lstMenu.ItemData(lstMenu.ListIndex) > kMenuElem Then
            'Move a menu element
            m_Menu.MoveElement LocateMenuElem(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar), vbKeyDown
         Else
            'Move a menu bar
            m_Menu.MoveBar LocateMenuBar(lstMenu.ItemData(lstMenu.ListIndex) Mod kMenuBar), vbKeyDown
         End If
         SetMenu
         For nIndex = 0 To lstMenu.ListCount - 1
            If lstMenu.ItemData(nIndex) = nItemData Then
               lstMenu.ListIndex = nIndex
               Exit For
            End If
         Next
      End If
   Case 2 'Next
      nIndex = lstMenu.ListIndex + 1
      If nIndex >= lstMenu.ListCount Then
         'Add something
         If lstMenu.ListCount = 0 Then
            butAction_Click 1
         Else
            If lstMenu.ItemData(lstMenu.ListCount - 1) > kMenuElem Then
               butAction_Click 3
            Else
               butAction_Click 1
            End If
         End If
      Else
         'Select next item in list
         lstMenu.ListIndex = nIndex
         UpdateDialog
         lstMenu.ListIndex = nIndex
      End If
   End Select
End Sub

Private Sub butOK_Click()
   Unload Me
End Sub

Private Sub InitMenuCombobox()
Dim i As Integer

   'Initialize Menu Combobox
   cmbMenu.Clear
   For i = 1 To m_Project.MenuCollection.count
      cmbMenu.AddItem m_Project.MenuCollection(i).Name
      cmbMenu.ItemData(i - 1) = i
      If m_Project.MenuCollection(i) Is m_Menu Then
         cmbMenu.Tag = -1
         cmbMenu.ListIndex = i - 1
      End If
   Next
   If cmbMenu.ListCount > 0 Then
      cmbMenu.AddItem "----------"
      cmbMenu.ItemData(i - 1) = 0
      cmbMenu.AddItem gStringTable(1621)
      cmbMenu.ItemData(i) = kEditMenuName
      cmbMenu.AddItem gStringTable(1626)
      cmbMenu.ItemData(i + 1) = kDeleteMenu
      cmbMenu.AddItem gStringTable(1622)
      cmbMenu.ItemData(i + 2) = kAddNewMenu
   Else
      cmbMenu.AddItem gStringTable(1622)
      cmbMenu.ItemData(0) = kAddNewMenu
   End If
End Sub

Private Sub cmbCommand_Click()
   If m_Target Is Nothing Then Exit Sub
   If Not typename(m_Target) = "CMenuElem" Then Exit Sub

   If cmbCommand.ListIndex = 0 Then
      m_Target.command = ""
   ElseIf cmbCommand.ListIndex <= 10 Then
      m_Target.command = cmbCommand.ListIndex - 1
   Else
      m_Target.command = Chr(cmbCommand.ItemData(cmbCommand.ListIndex))
   End If
   txtCaption_Change
End Sub

Private Sub cmbMenu_Click()
Dim nIndex As Integer
Dim strname As String

   If cmbMenu.Tag < 0 Then
      cmbMenu.Tag = cmbMenu.ListIndex
   Else
      Select Case cmbMenu.ItemData(cmbMenu.ListIndex)
      Case kEditMenuName
         If gLanguage <> "Nippon" Then
            strname = InputBox(gStringTable(1623), gStringTable(1621), m_Menu.Name)
         Else
            strname = InputBox(gStringTable(1623) + " " + gStringTable(1621), "", m_Menu.Name)
         End If
         If strname <> "" Then
            m_Menu.Name = strname
            cmbMenu.List(cmbMenu.Tag) = m_Menu.Name
         End If
         GoTo ResetIndex
      Case kDeleteMenu
         If MsgBox(gStringTable(1627), vbYesNo + vbQuestion, gStringTable(1626)) = vbYes Then
            m_Project.MenuCollection.Remove MenuIndex(m_Menu.IdNo)
            Set m_Menu = Nothing
            InitMenuCombobox
            SetMenu
            If m_Project.MenuCollection.count = 0 Then
               If AddNewMenu Then
                  InitMenuCombobox
                  SetMenu
               Else
               End If
            Else
               Set m_Menu = m_Project.MenuCollection(1)
               InitMenuCombobox
               SetMenu
            End If
         End If
         GoTo ResetIndex
      Case kAddNewMenu
         If AddNewMenu Then
            InitMenuCombobox
            SetMenu
         End If
      Case 0 'Do nothing
         GoTo ResetIndex
      Case Else 'Select a new menu
         Set m_Menu = m_Project.MenuCollection(cmbMenu.ItemData(cmbMenu.ListIndex))
         cmbMenu.Tag = cmbMenu.ListIndex
         SetMenu
      End Select
   End If
   Exit Sub

ResetIndex:
   nIndex = cmbMenu.Tag
   cmbMenu.Tag = -1
   cmbMenu.ListIndex = nIndex
End Sub

Private Sub Form_Load()
Dim i As Integer
Dim strname As String
   LoadResStrings Me

   If m_Menu Is Nothing Then Set m_Menu = m_Project.MenuCollection(1)
   'If gbPlainText Then
    '  txtCaption.fontName = gLabelFontName
   '   lstMenu.fontName = gLabelFontName
   'End If
   'txtCaption.font.Charset = gLabelCharset
   'lstMenu.font.Charset = gLabelCharset
   InitMenuCombobox

   'Initialize Command Combobox
   cmbCommand.Clear
   cmbCommand.AddItem "(None)"
   For i = 0 To 9
      cmbCommand.AddItem i
      cmbCommand.ItemData(i + 1) = i + 1
   Next
   For i = Asc("A") To Asc("Z")
      cmbCommand.AddItem Chr(i)
      cmbCommand.ItemData(i - Asc("A") + 11) = i
   Next
   SetMenu
End Sub

Private Sub SetMenu()
Dim mBar As CMenuBar
Dim mElem As CMenuElem

   lstMenu.Clear
   If Not m_Menu Is Nothing Then
      For Each mBar In m_Menu.MenuBars
         lstMenu.AddItem mBar.caption
         lstMenu.ItemData(lstMenu.ListCount - 1) = kMenuBar + mBar.IdNo
         For Each mElem In mBar.MenuElems
            If mElem.command <> "" Then
               lstMenu.AddItem "..." & mElem.caption & "[/" & mElem.command & "]"
            Else
               lstMenu.AddItem "..." & mElem.caption
            End If
            lstMenu.ItemData(lstMenu.ListCount - 1) = kMenuElem + mElem.IdNo
         Next
      Next
      If lstMenu.ListCount > 0 Then lstMenu.ListIndex = 0
   End If
   UpdateDialog
End Sub

Private Sub UpdateDialog()
   If lstMenu.ListIndex < 0 Then
      SetTxtCaption ""
      txtProcName.Text = ""
'      txtProcName.Enabled = False
'      txtProcName.BackColor = &H8000000F
      cmbCommand.ListIndex = -1
      cmbCommand.Enabled = False
      butAction(2).Enabled = False
      butAction(3).Enabled = False
      butAction(4).Enabled = False
      Set m_Target = Nothing
   Else
      If lstMenu.ItemData(lstMenu.ListIndex) < kMenuElem Then
         m_bMenuBar = True
         Set m_Target = LocateMenuBar(lstMenu.ItemData(lstMenu.ListIndex) - kMenuBar)
         SetTxtCaption m_Target.caption
         txtProcName.Text = ""
'         txtProcName.Enabled = False
'         txtProcName.BackColor = &H8000000F
         cmbCommand.ListIndex = -1
         cmbCommand.Enabled = False
      Else
         m_bMenuBar = False
         Set m_Target = LocateMenuElem(lstMenu.ItemData(lstMenu.ListIndex) - kMenuElem)
         SetTxtCaption m_Target.caption
         txtProcName.Text = m_Target.ProcName
'         txtProcName.Enabled = True
'         txtProcName.BackColor = &H80000005
         If m_Target.command = "" Then
            cmbCommand.ListIndex = 0
         Else
            If m_Target.command >= 0 And m_Target.command <= 9 Then
               cmbCommand.ListIndex = m_Target.command + 1
            Else
               cmbCommand.ListIndex = Asc(m_Target.command) - Asc("A") + 11
            End If
         End If
         cmbCommand.Enabled = True
      End If
      butAction(2).Enabled = True
      butAction(3).Enabled = True
      butAction(4).Enabled = True
   End If
End Sub

Private Function LocateMenuBar(nIdNo As Integer) As CMenuBar
Dim mBar As CMenuBar
Dim mElem As CMenuElem

   For Each mBar In m_Menu.MenuBars
      If mBar.IdNo = nIdNo Then
         Set LocateMenuBar = mBar
         Exit Function
      End If
      For Each mElem In mBar.MenuElems
         If mElem.IdNo = nIdNo Then
            Set LocateMenuBar = mBar
            Exit Function
         End If
      Next
   Next
End Function

Private Function LocateMenuElem(nIdNo As Integer) As CMenuElem
Dim mBar As CMenuBar
Dim mElem As CMenuElem

   If m_bMenuBar Then Exit Function
   For Each mBar In m_Menu.MenuBars
      For Each mElem In mBar.MenuElems
         If mElem.IdNo = nIdNo Then
            Set LocateMenuElem = mElem
            Exit Function
         End If
      Next
   Next
End Function

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
Dim i As Integer

   For i = 0 To lstMenu.ListCount - 1
      If lstMenu.ItemData(i) < kMenuElem Then
         If lstMenu.List(i) = "" Then
            lstMenu.ListIndex = i
            MsgBox gStringTable(1620), vbCritical + vbOKOnly
            Exit Sub
         End If
      Else
         If lstMenu.List(i) = "..." Then
            lstMenu.ListIndex = i
            MsgBox gStringTable(1620), vbCritical + vbOKOnly
            Exit Sub
         End If
      End If
   Next
End Sub

Private Sub lstMenu_Click()
   UpdateDialog
End Sub

Private Sub lstMenu_KeyUp(KeyCode As Integer, Shift As Integer)
   If KeyCode = 93 Then PopupMenu mnuRight
End Sub

Private Sub lstMenu_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
   If Button = vbRightButton Then PopupMenu mnuRight
End Sub

Private Sub mnuRightAdd_Click(index As Integer)
   Select Case index
   Case 0, 1: butAction_Click index
   Case 3, 4: butAction_Click index - 1
   Case 6: butAction_Click -2
   End Select
End Sub

Private Sub mnuRightMove_Click(index As Integer)
   butMove_Click index
End Sub

Private Function MenuIndex(nIdNo As Integer) As Integer
   For MenuIndex = 1 To m_Project.MenuCollection.count
      If m_Project.MenuCollection(MenuIndex).IdNo = nIdNo Then Exit Function
   Next
End Function

Private Function MenuBarIndex(nIdNo As Integer) As Integer
   For MenuBarIndex = 1 To m_Menu.MenuBars.count
      If m_Menu.MenuBars(MenuBarIndex).IdNo = nIdNo Then Exit Function
   Next
End Function

Private Function MenuElemIndex(nBarIdNo As Integer, nElemIdNo As Integer) As Integer
Dim i As Integer

   For i = 1 To m_Menu.MenuBars.count
      If m_Menu.MenuBars(i).IdNo = nBarIdNo Then
         For MenuElemIndex = 1 To m_Menu.MenuBars(i).MenuElems.count
            If m_Menu.MenuBars(i).MenuElems(MenuElemIndex).IdNo = nElemIdNo Then Exit Function
         Next
      End If
   Next
End Function

Public Function GetListIndex(nIdNo As Integer) As Integer
   For GetListIndex = 0 To lstMenu.ListCount - 1
      If lstMenu.ItemData(GetListIndex) Mod kMenuBar = nIdNo Then Exit Function
   Next
End Function

Private Sub SetTxtCaption(ByVal strCaption As String)
   m_bProgramSet = True
   txtCaption.Text = strCaption
   m_bProgramSet = False
End Sub

Private Sub txtCaption_Change()
Dim strTemp As String

   If m_bProgramSet Then Exit Sub
   If m_Target Is Nothing Then
      strTemp = txtCaption.Text
      butAction(1).Value = True
      txtCaption.Text = strTemp
      txtCaption_Change
      txtCaption.SelStart = Len(txtCaption.Text)
      Exit Sub
   End If
   m_Target.caption = txtCaption.Text
   If m_bMenuBar Then
      lstMenu.List(lstMenu.ListIndex) = m_Target.caption
   Else
      strTemp = "..." & m_Target.caption
      If m_Target.command <> "" Then strTemp = strTemp & "[/" & m_Target.command & "]"
      lstMenu.List(lstMenu.ListIndex) = strTemp
   End If
End Sub

Private Function AddNewMenu() As Boolean
Dim mnu As New CMenu

   If gLanguage <> "Nippon" Then
      mnu.Name = InputBox(gStringTable(1623), gStringTable(1624))
   Else
      mnu.Name = InputBox(gStringTable(1623) + " " + gStringTable(1624))
   End If
   If mnu.Name = "" Then Exit Function
   m_Project.AddMenu mnu
   Set m_Menu = mnu
   AddNewMenu = True
End Function
