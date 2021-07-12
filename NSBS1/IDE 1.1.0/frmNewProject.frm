VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmNewProject 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "New Project"
   ClientHeight    =   3255
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6030
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3255
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   Tag             =   "1149"
   Begin MSComctlLib.ImageList imlTemplates 
      Left            =   5040
      Top             =   1320
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   1
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmNewProject.frx":0000
            Key             =   "NSBasic"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ListView lstTemplates 
      Height          =   3015
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   4455
      _ExtentX        =   7858
      _ExtentY        =   5318
      Arrange         =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      Icons           =   "imlTemplates"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      Tag             =   "1146"
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   4680
      TabIndex        =   0
      Tag             =   "1106"
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "frmNewProject"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_strTemplate As String

Public Property Get ProjectTemplate() As String
   ProjectTemplate = m_strTemplate
End Property

Private Sub CancelButton_Click()
   Unload Me
End Sub

Private Sub Form_Load()
   lstTemplates.ListItems.Add , , "Project File", "NSBasic"
   LoadResStrings Me
End Sub

Private Sub lstTemplates_DblClick()
   OKButton_Click
End Sub

Private Sub OKButton_Click()
   m_strTemplate = "Project File"
   Unload Me
End Sub

