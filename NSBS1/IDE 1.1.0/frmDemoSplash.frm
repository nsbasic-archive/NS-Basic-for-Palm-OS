VERSION 5.00
Begin VB.Form frmDemoSplash 
   Caption         =   "1124[Demo Version]"
   ClientHeight    =   6150
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7995
   LinkTopic       =   "Form1"
   ScaleHeight     =   6150
   ScaleWidth      =   7995
   StartUpPosition =   3  'Windows Default
   Tag             =   "1124"
   Begin VB.TextBox txtNotes 
      Height          =   2655
      Left            =   1320
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   6
      Top             =   2640
      Width           =   5655
   End
   Begin VB.CommandButton btnBuy 
      Caption         =   "1123[Buy]"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Tag             =   "1123"
      Top             =   5640
      Width           =   1335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "1404[OK]"
      Height          =   375
      Left            =   6600
      TabIndex        =   1
      Tag             =   "1404"
      Top             =   5640
      Width           =   1215
   End
   Begin VB.PictureBox Picture1 
      BorderStyle     =   0  'None
      Height          =   1695
      Left            =   240
      Picture         =   "frmDemoSplash.frx":0000
      ScaleHeight     =   1695
      ScaleWidth      =   1455
      TabIndex        =   0
      Top             =   240
      Width           =   1455
   End
   Begin VB.Label timeleft 
      Appearance      =   0  'Flat
      BackColor       =   &H8000000A&
      Caption         =   "Days Remaining"
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   2880
      TabIndex        =   7
      Top             =   5640
      Width           =   1815
   End
   Begin VB.Label Label3 
      Caption         =   "1122"
      Height          =   495
      Left            =   240
      TabIndex        =   5
      Tag             =   "1122"
      Top             =   2040
      Width           =   7455
   End
   Begin VB.Label Label2 
      Caption         =   "1121"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   17.25
         Charset         =   238
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1800
      TabIndex        =   4
      Tag             =   "1121"
      Top             =   1200
      Width           =   6135
   End
   Begin VB.Label Label1 
      Caption         =   "1120"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   24
         Charset         =   238
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   1800
      TabIndex        =   3
      Tag             =   "1120"
      Top             =   240
      Width           =   6015
   End
End
Attribute VB_Name = "frmDemoSplash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private daysRemaining As Long
Private Sub btnBuy_Click()
   #If NSBSymbian Then
      openWebPage "www.nsbasic.com/order.shtml"
   #Else
      openWebPage "www.nsbasic.com/order.shtml"
   #End If
End Sub

Private Sub Command1_Click()
  Me.Hide
  Unload Me
  If daysRemaining < 0 Then End
End Sub

Private Sub Form_Load()
Dim checksum As String
Dim x, y As Double
Dim trace As Boolean
   trace = True
   If trace Then MsgBox "demoSpash " & 1
   LoadResStrings Me
   If trace Then MsgBox "demoSpash " & 2
   txtNotes = gStringTable(3312) & vbCrLf & vbCrLf 'Welcome to NS Basic/Palm's Demonstration Edition!
   txtNotes = txtNotes & gStringTable(3313) & vbCrLf & vbCrLf 'Click the Buy button for more information or to get the latest version of NS Basic/Palm with full support and 140 page Handbook.
   txtNotes = txtNotes & gStringTable(3314) & vbCrLf 'This is the full version of NS Basic/Palm, with some restrictions:
   txtNotes = txtNotes & gStringTable(3315) & vbCrLf '1. Apps you create will only run for 5 days.
   txtNotes = txtNotes & gStringTable(3316) & vbCrLf '2. Apps created do not need a runtime.
   If Not bookEdition Then txtNotes = txtNotes & gStringTable(3317) & vbCrLf '3. This demo copy will only run for 30 days.
   txtNotes = txtNotes & gStringTable(3318) & vbCrLf & vbCrLf '4. Shared libraries are not included.
   txtNotes = txtNotes & gStringTable(3319) 'Be sure to read the release notes for full information on getting started.
   If trace Then MsgBox "demoSpash " & 3

   'check if timed out
   MWinReg.hKey = HKEY_CURRENT_USER
   #If NSBSymbian Then
      MWinReg.SubKey = "Software\NSBasic\Symbian"
   #Else
      MWinReg.SubKey = "Software\NSBasic\Palm"
   #End If
   If trace Then MsgBox "demoSpash 3.0"
   checksum = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "checksum", "0")
   If trace Then MsgBox "demoSpash " & 3.1 & " Date " & Date & " datediff " & DateDiff("d", "5/23/54", Date)
   y = DateDiff("d", "5/23/1954", Date)
   If trace Then MsgBox "demoSpash " & 3.2
   If checksum = "0" Then 'start for first time
      checksum = str(y)
      MWinReg.SetRegValue MWinReg.hKey, MWinReg.SubKey, "checksum", checksum
   End If 'check if expired
   If trace Then MsgBox "demoSpash " & 3.3
   x = Val(checksum)
   If trace Then MsgBox "demoSpash " & 3.4
   daysRemaining = 30 - (y - x)
   If trace Then MsgBox "demoSpash " & 3.5
   If bookEdition Then daysRemaining = 4
   If trace Then MsgBox "demoSpash " & 3.6
   If Not bookEdition Then timeleft.caption = gStringTable(3311) & " " & daysRemaining ' "Days Remaining: "
   If trace Then MsgBox "demoSpash " & 3.7
   If daysRemaining < 0 Then
      MsgBox gStringTable(3310) '"NS Basic/Palm Demonstration Edition has timed out. It is time to get your real copy!"
   End If
   If trace Then MsgBox "demoSpash " & 4
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Me.Hide
  Unload Me
  If daysRemaining < 0 Then End
End Sub

