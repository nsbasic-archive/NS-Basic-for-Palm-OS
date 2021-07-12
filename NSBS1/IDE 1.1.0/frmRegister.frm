VERSION 5.00
Begin VB.Form frmRegister 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "NS Basic/Palm Registration"
   ClientHeight    =   3090
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5730
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3090
   ScaleWidth      =   5730
   StartUpPosition =   3  'Windows Default
   Tag             =   "1176"
   Begin VB.CommandButton butCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4200
      TabIndex        =   5
      Tag             =   "1146"
      Top             =   2640
      Width           =   1455
   End
   Begin VB.CommandButton butDone 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   2640
      TabIndex        =   0
      Tag             =   "1106"
      Top             =   2640
      Width           =   1455
   End
   Begin VB.TextBox fldSerialNumber 
      Height          =   285
      Left            =   2400
      TabIndex        =   2
      Text            =   "Unregistered Demo"
      Top             =   1080
      Width           =   3255
   End
   Begin VB.Label Label3 
      Caption         =   $"frmRegister.frx":0000
      Height          =   855
      Left            =   120
      TabIndex        =   4
      Tag             =   "1180"
      Top             =   1560
      Width           =   5535
   End
   Begin VB.Label Label2 
      Caption         =   "&Serial Number:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Tag             =   "1178"
      Top             =   1125
      Width           =   2055
   End
   Begin VB.Label Label1 
      Caption         =   $"frmRegister.frx":00DD
      Height          =   855
      Left            =   120
      TabIndex        =   1
      Tag             =   "1177"
      Top             =   120
      Width           =   5535
      WordWrap        =   -1  'True
   End
End
Attribute VB_Name = "frmRegister"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub butDone_Click()
Dim oldDemoSW As String
   'MsgBox "butDone_Click() " & DemoSw & allowRegistration

   If allowRegistration = True Then
      oldDemoSW = DemoSw
      glSerialNumber = fldSerialNumber.Text
      CheckSerialNumber
      'MsgBox "butDone_Click() demosw=" & DemoSw
      If DemoSw = "n" Then 'save the serial number
         res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "SerialNumber", glSerialNumber)
      End If
      If oldDemoSW = "y" And DemoSw = "n" Then MsgBox gStringTable(3263) '"Congratulations!  You now have a full licenced version."
      If oldDemoSW = "n" And DemoSw = "y" Then
         MsgBox gStringTable(3264) '"Reverting to Unregistered Demo.  Please reenter your Serial Number."
         glSerialNumber = "Unregistered Demo"
         res = MWinReg.SetRegValue(MWinReg.hKey, MWinReg.SubKey, "SerialNumber", glSerialNumber)
         Exit Sub
      End If
   Else
      MsgBox gStringTable(3265) '"This is a Demo copy - it cannot be registered.  Please contact NS Basic Corporation to obtain a full copy with all the latest features."
   End If
   Unload Me
End Sub

Private Sub butCancel_Click()
  Unload Me
End Sub


Private Sub Form_Load()
   LoadResStrings Me
   If Not allowRegistration Then
      Label2.Enabled = False
      fldSerialNumber.Enabled = False
      glSerialNumber = "0"
   End If
      
   If glSerialNumber <> "0" Then
      fldSerialNumber.Text = glSerialNumber
   Else
      fldSerialNumber.Text = "Unregistered Demo"
   End If
End Sub
