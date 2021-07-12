VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmProjectExplorer 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Project Explorer"
   ClientHeight    =   2460
   ClientLeft      =   45
   ClientTop       =   285
   ClientWidth     =   4335
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   164
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   289
   ShowInTaskbar   =   0   'False
   Tag             =   "1174"
   Visible         =   0   'False
   Begin MSComctlLib.ImageList imlProjectExplorer 
      Left            =   120
      Top             =   1800
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      UseMaskColor    =   0   'False
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   10
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":0000
            Key             =   "NSBasic"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":059A
            Key             =   "FolderClosed"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":08EC
            Key             =   "FolderOpen"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":0C3E
            Key             =   "Form"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":0F90
            Key             =   "UIObject"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":12E2
            Key             =   "Menu"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":1634
            Key             =   "MenuBar"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":1986
            Key             =   "MenuElem"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":1CD8
            Key             =   "Bitmap"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmProjectExplorer.frx":202A
            Key             =   "Module"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TreeView expl 
      Height          =   1695
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4335
      _ExtentX        =   7646
      _ExtentY        =   2990
      _Version        =   393217
      HideSelection   =   0   'False
      Indentation     =   556
      LabelEdit       =   1
      Style           =   7
      ImageList       =   "imlProjectExplorer"
      Appearance      =   1
   End
End
Attribute VB_Name = "frmProjectExplorer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private IconMenu As New cIconMenu

Private m_nFormIndex As Long
Private m_nBitmapIndex As Long
Private m_nModuleIndex As Long
Private m_strSelection As String

Public Sub DockWindow()
'On Error Resume Next
Dim lRet As Long

   Me.Visible = False

   'Make sure we keep the ToolWindow style
   lRet = SetWindowLong(Me.hWnd, GWL_EXSTYLE, CLng(WS_EX_TOOLBOXWINDOW))

   'Set parent and resize the panel
   SetParent Me.hWnd, frmMain.picProjectExplorer.hWnd
   frmMain.picProjectExplorer_Resize
   frmMain.picPanel_Resize

   frmMain.picPanel.Refresh
   frmMain.picPanel.Visible = True
   DoEvents
   Me.Visible = True
   SendMessage Me.hWnd, WM_NCACTIVATE, 1, 0
   frmMain.mnuViewProjectExplorer.Checked = gbProjectExplorer
End Sub

Public Sub DisplayExplorer()
Dim i As Integer
Dim wk, wk2 As String
Dim tempString As String
Dim proj As CProject
Dim frm As CForm
Dim ob As Object
Dim Module As CCodeModule
Dim Bitmap As CBitmapFile
Dim resource As CResourceFile
Dim nProject As Integer
Dim nForm As Integer

repeat:
   If expl.Nodes.count <> 0 Then
      expl.Nodes.Clear
   End If
   For Each proj In gProjects
      expl.Nodes.Add , , , ""
      nProject = expl.Nodes.count
      FillProjectNode nProject, proj
      expl.Nodes(nProject).Expanded = True
'      If expl.Nodes(nProject).Image = Empty Then
      expl.Nodes(nProject).Image = "NSBasic"
'      End If

      'Add Forms folder
      expl.Nodes.Add nProject, tvwChild, , "Forms"
      i = expl.Nodes.count
      expl.Nodes(i).Tag = "Forms|" & proj.GlobalID
      expl.Nodes(i).Expanded = True
      expl.Nodes(i).Image = "FolderClosed"
      expl.Nodes(i).ExpandedImage = "FolderOpen"

      'Add each form
      For Each frm In proj.FormCollection
         expl.Nodes.Add i, tvwChild, , ""
         nForm = expl.Nodes.count
         FillFormNode nForm, frm, proj
         expl.Nodes(nForm).Image = "Form"
         'Open form folder if this is the active form
         If aView Is frm Then expl.Nodes(nForm).Expanded = True

         'Add objects from form
         For Each ob In frm.ObjectCollection
            expl.Nodes.Add nForm, tvwChild, , ""
            FillObjectNode expl.Nodes.count, ob, frm, proj
            expl.Nodes(expl.Nodes.count).Image = "UIObject"
         Next
      Next

      'Add Menus folder
      expl.Nodes.Add nProject, tvwChild, , "Menus"
      i = expl.Nodes.count
      expl.Nodes(i).Tag = "Menus|" & proj.GlobalID
      expl.Nodes(i).Image = "FolderClosed"
      expl.Nodes(i).ExpandedImage = "FolderOpen"

      DisplayProjectMenus proj, i

      'Add Bitmaps folder
      expl.Nodes.Add nProject, tvwChild, , "Bitmaps"
      i = expl.Nodes.count
      expl.Nodes(i).Tag = "Bitmaps|" & proj.GlobalID
      expl.Nodes(i).Image = "FolderClosed"
      expl.Nodes(i).ExpandedImage = "FolderOpen"

      'Add each bitmap
      For Each bmp In proj.BitmapCollection
         expl.Nodes.Add i, tvwChild, , ""
         FillBitmapNode expl.Nodes.count, bmp, proj
         expl.Nodes(expl.Nodes.count).Image = "Bitmap"
      Next
      
      'Add Modules folder
      expl.Nodes.Add nProject, tvwChild, , "Modules"
      i = expl.Nodes.count
      expl.Nodes(i).Tag = "Modules|" & proj.GlobalID
      expl.Nodes(i).Image = "FolderClosed"
      expl.Nodes(i).ExpandedImage = "FolderOpen"

      'Add each module
      For Each cod2 In proj.CodeCollection
         expl.Nodes.Add i, tvwChild, , ""
         FillModuleNode expl.Nodes.count, cod2 ', proj
         expl.Nodes(expl.Nodes.count).Image = "Module"
      Next
      
      'Add Resources folder
      expl.Nodes.Add nProject, tvwChild, , "Resources"
      i = expl.Nodes.count
      expl.Nodes(i).Tag = "Resources|" & proj.GlobalID
      expl.Nodes(i).Image = "FolderClosed"
      expl.Nodes(i).ExpandedImage = "FolderOpen"

      'Add each resource
      For Each res In proj.ResourceCollection
         expl.Nodes.Add i, tvwChild, , ""
         FillResourceNode expl.Nodes.count, res, proj
         expl.Nodes(expl.Nodes.count).Image = "Module"
      Next
      
   Next

   'Open Forms folder
'   expl.Nodes(m_nFormIndex).Expanded = True
   expl.Refresh
End Sub

Private Sub FillProjectNode(nProject As Integer, ByVal proj As CProject)
Dim wk As String

   wk = ""
   If proj.pgm_script <> "" Then wk = wk + "Startup"
   If proj.pgm_script <> "" And proj.termination_script <> "" Then wk = wk + ", "
   If proj.termination_script <> "" Then wk = wk + "Termination"
   If wk <> "" Then
      wk = "(" + wk + ")"
   End If
   wk = proj.Name + wk
   If StrComp(proj.Name, gTarget.Name) = 0 Then
      expl.Nodes(nProject).Bold = True
   Else
      expl.Nodes(nProject).Bold = False
   End If
   expl.Nodes(nProject).Text = wk
   expl.Nodes(nProject).Tag = proj.GlobalID
End Sub

Private Sub FillFormNode(nForm As Integer, ByVal frm As CForm, ByVal proj As CProject)
Dim wk As String

   wk = ""
   If frm.pgm_script <> "" Then wk = wk + "Before"
   If frm.pgm_script <> "" And (frm.event_script <> "" Or frm.pgm_script_after <> "") Then wk = wk + ", "
   If frm.event_script <> "" Then wk = wk + "Event"
   If frm.pgm_script_after <> "" And frm.event_script <> "" Then wk = wk + ", "
   If frm.pgm_script_after <> "" Then wk = wk + "After"
   If wk <> "" Then
      wk = "(" + wk + ")"
   End If
   wk = frm.Name + "/" + frm.Title + wk
   expl.Nodes(nForm).Text = wk
   expl.Nodes(nForm).Tag = frm.GlobalID
End Sub

Private Sub FillObjectNode(nOb As Integer, ByVal ob As Object, ByVal frm As CForm, ByVal proj As CProject)
   Dim wk As String

   wk = ob.obj.Name + "/" + ob.obj.Label
   If ob.obj.ScriptLen > 0 Then wk = wk + "(Click)"
   expl.Nodes(nOb).Text = wk
   expl.Nodes(nOb).Tag = ob.obj.GlobalID
End Sub

Private Sub FillMenuNode(nMenu As Integer, ByVal mnu As CMenu)
   expl.Nodes(nMenu).Text = mnu.Name
   expl.Nodes(nMenu).Tag = mnu.GlobalID
End Sub

Private Sub FillMenuBarNode(nMenuBar As Integer, ByVal mBar As CMenuBar)
   expl.Nodes(nMenuBar).Text = mBar.caption
   expl.Nodes(nMenuBar).Tag = mBar.GlobalID
End Sub

Private Sub FillMenuElemNode(nMenuElem As Integer, ByVal mElem As CMenuElem)
Dim wk As String

   wk = mElem.caption
   If mElem.command <> "" Then wk = wk & "[/" & mElem.command & "]"
   If mElem.menu_script <> "" Then wk = wk & "(Click)"
   expl.Nodes(nMenuElem).Text = wk
   expl.Nodes(nMenuElem).Tag = mElem.GlobalID
End Sub

Private Sub FillBitmapNode(nBmp As Integer, ByVal bmp As CBitmapFile, ByVal proj As CProject)
   Dim filename As String
   filename = bmp.PathName1
   If filename = "" Then filename = bmp.PathName2
   If filename = "" Then filename = bmp.PathName4
   If filename = "" Then filename = bmp.PathName8
   If filename = "" Then filename = bmp.PathName16
   If filename = "" Then filename = bmp.PathName1h
   If filename = "" Then filename = bmp.PathName2h
   If filename = "" Then filename = bmp.PathName4h
   If filename = "" Then filename = bmp.PathName8h
   If filename = "" Then filename = bmp.PathName16h
   
   expl.Nodes(nBmp).Text = bmp.IdNo & "/" & bmp.Name & " " & Mid(filename, InStrRev(filename, "\") + 1)
   expl.Nodes(nBmp).Tag = bmp.GlobalID
End Sub
Private Sub FillResourceNode(nRes As Integer, ByVal res As CResourceFile, ByVal proj As CProject)
   expl.Nodes(nRes).Text = res.IdNo & "/" & res.Name & " " & Mid(res.ResourcePath, InStrRev(res.ResourcePath, "\") + 1)
   expl.Nodes(nRes).Tag = res.GlobalID
End Sub

Private Sub FillModuleNode(nModule As Integer, ByVal cMod As CCodeModule) ', byval proj As CProject)
   expl.Nodes(nModule).Text = cMod.filename
   expl.Nodes(nModule).Tag = cMod.GlobalID 'Join(Array("module", cmod.IdNo, proj.Name), "|")
End Sub

Private Sub Expl_DblClick()
Dim index As Integer
Dim arrNode() As String
Dim obj As Object
Dim frm As Form
Dim proj As CProject
Dim fMenuEditor As New frmMenuEditor

   Set obj = LocateObject(expl.SelectedItem.Tag)
   Select Case typename(obj)
   Case "CProject"
      'Covers Projects, and Project Folders (Forms,Bitmaps,Modules,Resources)
      'Open project code, when it's all one thing
   Case "CForm"
      frmMain.ViewObject expl.SelectedItem.Tag
   Case "CBitmapFile"
      'Open a file dialog here that allows a bitmap to be chosen
   Case "CResourceFile"
      'Open a file dialog here that allows a resource to be chosen
   Case "CCodeModule"
      frmMain.ViewCode expl.SelectedItem.Tag, "code"
   Case "CMenu"
      Set proj = LocateProject(expl.SelectedItem.Tag)
      fMenuEditor.Project = proj
      fMenuEditor.Menu = LocateObject(expl.SelectedItem.Tag)
      fMenuEditor.Show vbModal, frmMain
      UpdateProjectMenus proj
   Case "CMenuBar"
   Case "CMenuElem"
      frmMain.ViewCode expl.SelectedItem.Tag, "code"
   Case Else
      'This is some object...
      '1. Show the form
      '2. Hilite the object
      '3. Open the code
'      Set o2 = LocateObject(expl.SelectedItem.Tag)
'      frmMain.ViewObject expl.SelectedItem.Tag
      frmMain.ViewObject obj.obj.GlobalID
      obj.obj.Control.Parent.ClearSelection
      frmMain.ViewCode obj.obj.GlobalID, "code"
   End Select
End Sub

Private Sub expl_KeyUp(KeyCode As Integer, Shift As Integer)
   If KeyCode = 93 Then expl_MouseUp 2, 0, -expl.Left, -expl.Top
End Sub

Private Sub expl_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim o2 As Object
Dim v2 As Object
Dim tempIndex As Integer
Dim arrTag() As String

   'Mouse coordinates are sent in as negative from KeyUp-Key=93
   'The is the Windows "Menu" key.
   'If menu key is used, the negative coordinates are the origin
   'of the expl object.  This makes the menu popup show at the top
   'left of expl when the key is pressed, otherwise at mouse location
   'when right-click occurs
   '  if x < 0 and y < 0 then
   '     PopupMenu mnuMenu, , -x, -y
   '  else
   '     PopupMenu mnuMenu
   '  end if
   If expl.SelectedItem Is Nothing Then Exit Sub
   Set o2 = LocateObject(expl.SelectedItem.Tag)
   Select Case Left(expl.SelectedItem.Tag, InStr(expl.SelectedItem.Tag, "|") - 1)
'   Case "project"
'      If gbProperties Then gfProperties.Object = o2
   Case "form"
      If gbProperties Then gfProperties.Object = o2
      Set v2 = frmMain.GetMDIChild(o2.GlobalID)
      If Not v2 Is Nothing Then v2.ClearSelection
   Case "object"
      If Not o2.obj.Control Is Nothing Then
         o2.obj.Control.Parent.SetSelection o2
      End If
'   Case "bitmap"
'      If gbProperties Then gfProperties.Object = o2
'   Case "module"
'      If gbProperties Then gfProperties.Object = o2
'   Case "resource"
'      If gbProperties Then gfProperties.Object = o2
   Case Else
      If gbProperties Then gfProperties.Object = o2
   End Select

   If Button <> vbRightButton Then Exit Sub
   frmMain.RightClickMenu 0, expl.SelectedItem.Tag
End Sub  'expl_MouseUp

Private Sub Form_Load()
   LoadResStrings Me
   Me.Left = -(Me.Width + 1)
   gbProjectExplorer = True
   If gbPlainText Then
      expl.font.Name = gLabelFontName
      expl.font.Charset = gLabelCharset
      Me.fontname = gLabelFontName
      Me.font.Charset = gLabelCharset
   End If
'   DisplayExplorer
   
   If menusOn = True Then
      With IconMenu
         .Attach Me.hWnd
         .ImageList = imlIcons
      End With
   End If
'   DockWindow
End Sub

Private Sub Form_Resize()
   If Me.WindowState = vbMinimized Then Exit Sub
   Me.ScaleMode = 3
   With expl
      .Width = IIf(Me.Width \ Screen.TwipsPerPixelX - 8 < 10, 10, Me.Width \ Screen.TwipsPerPixelX - 8)
      .Height = IIf(Me.Height \ Screen.TwipsPerPixelY - (.Top + 25) < 10, 10, Me.Height \ Screen.TwipsPerPixelY - (.Top + 25))
   End With
   'MsgBox "Resize" & vbCrLf & "Explorer: " & Me.Width & "," & Me.Height & vbCrLf & "expl: " & expl.Width & "," & expl.Height
   'MsgBox "Screen.TwipsPerPixelX: " & Screen.TwipsPerPixelX
End Sub

Private Sub Form_Unload(Cancel As Integer)
   gbProjectExplorer = False
   frmMain.picPanel_Resize
   frmMain.mnuViewProjectExplorer.Checked = gbProjectExplorer
End Sub

Public Function GetNode(ByVal strTag As String) As MSComctlLib.Node
Dim i As Integer

   For i = 1 To expl.Nodes.count
      If expl.Nodes(i).Tag = strTag Then
         Set GetNode = expl.Nodes(i)
         Exit Function
      End If
   Next
End Function

Public Sub RemoveNode(ByVal strID As String)
Dim nod As MSComctlLib.Node

   Set nod = GetNode(strID).Parent
   expl.Nodes.Remove GetNode(strID).index
   If nod Is Nothing Then Exit Sub
   If nod.Children < 1 Then nod.Expanded = False
End Sub

Public Sub AddNewForm(ByRef frm As CForm, ByRef proj As CProject)
Dim nod As MSComctlLib.Node

   Set nod = GetNode("Forms|" & proj.GlobalID)   'Forms folder
   Set nod = expl.Nodes.Add(nod.index, tvwChild, , "")
   FillFormNode nod.index, frm, proj
   nod.Image = "Form"
   Set expl.SelectedItem = nod
   nod.EnsureVisible
End Sub

Public Sub AddNewControl(ByVal obj As Object, ByVal frm As CForm)
Dim nod As MSComctlLib.Node

   Set nod = GetNode(frm.GlobalID)  'Parent Form
   nod.Expanded = True
   Set nod = expl.Nodes.Add(nod.index, tvwChild, , "")
   FillObjectNode nod.index, obj, frm, frm.Project
   nod.Image = "UIObject"
   Set expl.SelectedItem = nod
   nod.EnsureVisible
End Sub

Public Sub AddNewMenu(ByRef mnu As CMenu, ByRef proj As CProject)
Dim nod As MSComctlLib.Node

   Set nod = GetNode("Menus|" & proj.GlobalID)  'Menus Folder
   nod.Expanded = True
   Set nod = expl.Nodes.Add(nod.index, tvwChild, , "")
   FillMenuNode nod.index, mnu
   nod.Image = "Menu"
   Set expl.SelectedItem = nod
   nod.EnsureVisible
End Sub

Public Sub AddNewMenuBar(ByRef mBar As CMenuBar, ByRef mnu As CMenu)
Dim nod As MSComctlLib.Node

   Set nod = GetNode(mnu.GlobalID)  'Parent Menu
   nod.Expanded = True
   Set nod = expl.Nodes.Add(nod.index, tvwChild, , "")
   FillMenuBarNode nod.index, mBar
   nod.Image = "MenuBar"
   Set expl.SelectedItem = nod
   nod.EnsureVisible
End Sub

Public Sub AddNewMenuElem(ByRef mElem As CMenuElem, ByRef mBar As CMenuBar)
Dim nod As MSComctlLib.Node

   Set nod = GetNode(mBar.GlobalID) 'Parent MenuBar
   nod.Expanded = True
   Set nod = expl.Nodes.Add(nod.index, tvwChild, , "")
   FillMenuElemNode nod.index, mElem
   nod.Image = "MenuElem"
   Set expl.SelectedItem = nod
   nod.EnsureVisible
End Sub

Public Sub AddNewBitmap(ByRef bmp As CBitmapFile, ByRef proj As CProject)
Dim nod As MSComctlLib.Node

   Set nod = GetNode("Bitmaps|" & proj.GlobalID)   'Bitmaps folder
   nod.Expanded = True
   Set nod = expl.Nodes.Add(nod.index, tvwChild, , "")
   FillBitmapNode nod.index, bmp, proj
   nod.Image = "Bitmap"
   Set expl.SelectedItem = nod
   nod.EnsureVisible
End Sub

Public Sub AddNewResource(ByRef bmp As CResourceFile, ByRef proj As CProject)
Dim nod As MSComctlLib.Node

   Set nod = GetNode("Resources|" & proj.GlobalID)   'Resources folder
   nod.Expanded = True
   Set nod = expl.Nodes.Add(nod.index, tvwChild, , "")
   FillResourceNode nod.index, bmp, proj
   nod.Image = "Module"
   Set expl.SelectedItem = nod
   nod.EnsureVisible
End Sub

Public Sub AddNewModule(ByRef cMod As CCodeModule, ByRef proj As CProject)
Dim nod As MSComctlLib.Node

   Set nod = GetNode("Modules|" + proj.GlobalID) 'Modules folder
   nod.Expanded = True
   Set nod = expl.Nodes.Add(nod.index, tvwChild, , "")
   FillModuleNode nod.index, cMod ', proj
   nod.Image = "Module"
   Set expl.SelectedItem = nod
   nod.EnsureVisible
End Sub

Public Sub UpdateTarget()
Dim i As Integer

   For i = 1 To gProjects.count
      FillProjectNode GetNode(gProjects(i).GlobalID).index, gProjects(i)
   Next
   SetCaption
End Sub

Public Sub SetCaption()
   Me.caption = gStringTable(1301)
   If gTarget Is Nothing Then Exit Sub

   Me.caption = Me.caption & " - " & gTarget.Name
End Sub

Public Sub ShowActive(Optional obj As Object)

   If obj Is Nothing Then
      Set expl.SelectedItem = Nothing
      Exit Sub
   End If
   On Error GoTo ShowActiveErr1
   Set expl.SelectedItem = GetNode(obj.GlobalID)
   If gbProperties Then gfProperties.Object = LocateObject(obj.GlobalID)
   Exit Sub

ShowActiveErr1:
   Set expl.SelectedItem = GetNode(obj.obj.GlobalID)
   If gbProperties Then gfProperties.Object = LocateObject(obj.obj.GlobalID)
End Sub

Public Sub UpdateObjectNode(ByVal obj As Object, ByVal strGlobalID As String)
Dim nod As MSComctlLib.Node

   Set nod = GetNode(strGlobalID)
   If nod Is Nothing Then Exit Sub
   Select Case Left(strGlobalID, InStr(strGlobalID, "|") - 1)
   Case "project": FillProjectNode nod.index, obj
   Case "form": FillFormNode nod.index, obj, obj.Project
   Case "bitmap": FillBitmapNode nod.index, obj, obj.Project
   Case "resource": FillResourceNode nod.index, obj, obj.Project
   Case "menu": FillMenuNode nod.index, obj
   Case "menubar": FillMenuBarNode nod.index, obj
   Case "menuelem": FillMenuElemNode nod.index, obj
   Case "module": FillModuleNode nod.index, obj
   Case "object": FillObjectNode nod.index, obj, obj.obj.Form, obj.obj.Form.Project
   End Select
End Sub

Public Sub UpdateProjectMenus(ByVal proj As CProject)
Dim nod As MSComctlLib.Node
Dim i As Integer

   Set nod = GetNode("Menus|" & proj.GlobalID)
   Set nod = nod.Child
   Do While Not nod Is Nothing
      i = nod.index
      Set nod = nod.Next
      expl.Nodes.Remove i
   Loop
   DisplayProjectMenus proj, GetNode("Menus|" & proj.GlobalID).index
End Sub

Public Sub DisplayProjectMenus(ByVal proj As CProject, nMenusFolder As Integer)
Dim nod As MSComctlLib.Node
Dim nMenu As Integer
Dim nMenuBar As Integer
Dim mnu As CMenu
Dim mBar As CMenuBar
Dim mElem As CMenuElem

   'Add Each menu
   For Each mnu In proj.MenuCollection
      Set nod = expl.Nodes.Add(nMenusFolder, tvwChild, , "")
      nMenu = nod.index
      FillMenuNode nMenu, mnu
'expl.Nodes(nMenu).Text = expl.Nodes(nMenu).Text & " " & mnu.GlobalID
      expl.Nodes(nMenu).Image = "Menu"
      'Open Menus folder if this project has menus
      expl.Nodes(nMenusFolder).Expanded = True

      'Add objects from form
      For Each mBar In mnu.MenuBars
         Set nod = expl.Nodes.Add(nMenu, tvwChild, , "")
         nMenuBar = nod.index
         FillMenuBarNode nMenuBar, mBar
'expl.Nodes(nMenuBar).Text = expl.Nodes(nMenuBar).Text & " " & mBar.GlobalID
         expl.Nodes(nMenuBar).Image = "MenuBar"
         For Each mElem In mBar.MenuElems
            Set nod = expl.Nodes.Add(nMenuBar, tvwChild, , "")
            FillMenuElemNode nod.index, mElem
'expl.Nodes(expl.Nodes.count).Text = expl.Nodes(expl.Nodes.count).Text & " " & mElem.GlobalID
            expl.Nodes(nod.index).Image = "MenuElem"
         Next
      Next
   Next
End Sub
