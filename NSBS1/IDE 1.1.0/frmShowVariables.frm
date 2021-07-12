VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmShowVariables 
   Caption         =   "3435[Variables]"
   ClientHeight    =   8190
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11985
   BeginProperty Font 
      Name            =   "Comic Sans MS"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   8190
   ScaleWidth      =   11985
   StartUpPosition =   3  'Windows Default
   Tag             =   "3435"
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   11040
      Top             =   0
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
            Picture         =   "frmShowVariables.frx":0000
            Key             =   "nonsubscriptedVariable"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmShowVariables.frx":00FA
            Key             =   "subscriptedVariableClosed"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmShowVariables.frx":01F4
            Key             =   "subscriptedVariableOpen"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TreeView Tree 
      Height          =   6375
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   10815
      _ExtentX        =   19076
      _ExtentY        =   11245
      _Version        =   393217
      Style           =   7
      ImageList       =   "ImageList1"
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Courier New"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
End
Attribute VB_Name = "frmShowVariables"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'this entire form is new 04012005

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

