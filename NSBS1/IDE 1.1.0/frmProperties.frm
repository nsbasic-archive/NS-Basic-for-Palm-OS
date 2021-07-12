VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "msflxgrd.ocx"
Begin VB.Form frmProperties 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Properties"
   ClientHeight    =   6015
   ClientLeft      =   32805
   ClientTop       =   285
   ClientWidth     =   5895
   LinkTopic       =   "Properties"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   6015
   ScaleWidth      =   5895
   ShowInTaskbar   =   0   'False
   Tag             =   "1175"
   Visible         =   0   'False
   Begin VB.CommandButton btnEllipsis 
      Caption         =   "..."
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4680
      TabIndex        =   6
      Top             =   480
      Width           =   255
   End
   Begin VB.TextBox txtList 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   3360
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   5
      Top             =   480
      Visible         =   0   'False
      Width           =   1020
   End
   Begin VB.CheckBox Button 
      BeginProperty Font 
         Name            =   "Wingdings"
         Size            =   8.25
         Charset         =   2
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   4440
      Picture         =   "frmProperties.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   480
      UseMaskColor    =   -1  'True
      Width           =   240
   End
   Begin VB.ListBox lstProps 
      Appearance      =   0  'Flat
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   225
      Left            =   3360
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   720
      Width           =   1275
   End
   Begin VB.TextBox txtEdit 
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   345
      Left            =   3360
      TabIndex        =   2
      Top             =   120
      Visible         =   0   'False
      Width           =   1725
   End
   Begin MSFlexGridLib.MSFlexGrid grdProperties 
      Height          =   4275
      Left            =   0
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   0
      Width           =   3195
      _ExtentX        =   5636
      _ExtentY        =   7541
      _Version        =   393216
      Rows            =   1
      Cols            =   4
      FixedRows       =   0
      FixedCols       =   0
      BackColorBkg    =   16777215
      GridColorFixed  =   12632256
      AllowBigSelection=   0   'False
      FocusRect       =   0
      ScrollBars      =   2
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Label lblMask 
      BackColor       =   &H80000003&
      Height          =   495
      Left            =   3240
      TabIndex        =   1
      Top             =   0
      Width           =   1815
   End
End
Attribute VB_Name = "frmProperties"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim m_PropGrid As New CPropertiesGrid
Dim m_obj As Object

Private Sub Form_Load()
   gbProperties = True
   m_PropGrid.Init grdProperties, lblMask, txtEdit, txtList, Button, lstProps, btnEllipsis, Me
   Me.Left = -(Me.Width + 1)
End Sub

Private Sub Form_Resize()
   m_PropGrid.Resize
End Sub

Public Sub DockWindow()
'On Error Resume Next
Dim lRet As Long

   Me.Visible = False

   'Make sure we keep the ToolWindow style
   lRet = SetWindowLong(Me.hwnd, GWL_EXSTYLE, CLng(WS_EX_TOOLBOXWINDOW))

   'Set parent and resize the panel
   SetParent Me.hwnd, frmMain.picProperties.hwnd
   frmMain.picProperties_Resize
   frmMain.picPanel_Resize

   frmMain.picPanel.Refresh
   frmMain.picPanel.Visible = True
   DoEvents
   Me.Visible = True
   SendMessage Me.hwnd, WM_NCACTIVATE, 1, 0
   frmMain.mnuViewProperties.Checked = gbProperties

   ShowObject
End Sub

Private Sub Form_Unload(Cancel As Integer)
   gbProperties = False
   frmMain.picPanel_Resize
   frmMain.mnuViewProperties.Checked = gbProperties
End Sub

Public Property Let Object(ByRef obj As Object)
   If obj Is m_obj Then Exit Property
   m_PropGrid.HideEditors
   Set m_obj = obj
   ShowObject
End Property

Private Sub ShowObject()
   m_PropGrid.Clear
   If Not m_obj Is Nothing Then
      m_obj.GetProperty
      Do While gPropInfo.Name <> ""
         m_PropGrid.AddItem gPropInfo.Type, gPropInfo.Name, gPropInfo.Val, gPropInfo.data
         m_obj.GetProperty
      Loop
   End If
   SetCaption
End Sub

Public Property Get Object() As Object
   Set Object = m_obj
End Property

Public Sub SetCaption()
   Me.caption = gStringTable(1302)
   If m_obj Is Nothing Then Exit Sub

   On Error GoTo UIObject
   Me.caption = Me.caption & " - " & m_obj.Name
   Exit Sub

UIObject:
   Me.caption = Me.caption & " - " & m_obj.obj.Name
End Sub

