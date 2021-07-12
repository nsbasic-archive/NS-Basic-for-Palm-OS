VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{F9980F03-3DB6-11D2-B398-444553540000}#1.0#0"; "palmcntl.ocx"
Begin VB.Form frmHotsync 
   Caption         =   "Install Form"
   ClientHeight    =   2910
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3870
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   2910
   ScaleWidth      =   3870
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   2
      Top             =   0
      Width           =   3870
      _ExtentX        =   6826
      _ExtentY        =   741
      ButtonWidth     =   635
      ButtonHeight    =   582
      Appearance      =   1
      _Version        =   393216
      Begin PALMCNTLLib.UserManager UserManager1 
         Left            =   3720
         Top             =   360
         _Version        =   65536
         _ExtentX        =   1000
         _ExtentY        =   1000
         _StockProps     =   0
      End
   End
   Begin VB.CommandButton butCancel 
      Caption         =   "1139[&Cancel]"
      Height          =   375
      Left            =   2040
      TabIndex        =   3
      Tag             =   "1139"
      Top             =   2280
      Width           =   1575
   End
   Begin VB.CommandButton butInstall 
      Caption         =   "1138[&Install]"
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Tag             =   "1138"
      Top             =   2280
      Width           =   1695
   End
   Begin VB.ListBox userlist 
      Height          =   1425
      Left            =   240
      TabIndex        =   1
      Top             =   600
      Width           =   3375
   End
   Begin PALMCNTLLib.UserData UserData1 
      Left            =   3720
      Top             =   1560
      _Version        =   65536
      _ExtentX        =   1000
      _ExtentY        =   1000
      _StockProps     =   0
   End
End
Attribute VB_Name = "frmHotsync"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private mvarInstall As String
#If NSBSymbian=0 Then

Private Sub butCancel_Click()
   Me.Hide
   Unload Me
   'frmMain.Show
End Sub

Public Sub butInstall_Click()
   If userlist.ListIndex = -1 Or userlist.ListIndex > userlist.ListCount - 1 Then
      MsgBox gStringTable(3322) '"Please select a username."
      Exit Sub
   End If
   UserData1.AssignUserID UserManager1.GetUserID(userlist.ListIndex)
   If mvarInstall = "" Then
      UserData1.AddInstallFile (DownloadPath + gTarget.Name + ".prc")
      UserData1.AddInstallFile (DownloadPath + gTarget.Name + ".pdb")
   Else
      UserData1.AddInstallFile (mvarInstall)
   End If
   MsgBox gStringTable(3323) '"Program will install on Palm device on next HotSync."

   Me.Hide
   Unload Me
   'frmMain.Show
End Sub

Private Sub Form_Load()
   Dim count As Long
   Dim index As Integer
   Dim userID As Long
   Dim username As String
   Dim itemIndex As Integer

   LoadResStrings Me, False
   mvarInstall = ""
   count = UserManager1.GetUserCount
   If count < 0 Then
      count = 0
   End If
   index = 0
   userlist.Clear
   Do While index < count
      userID = UserManager1.GetUserID(index)
      If (userID <> 0) Then
         UserData1.AssignUserID userID
         username = UserData1.username
         If (UserData1.IsProfileUser) Then
            username = username + " - Profile"
         End If
         userlist.AddItem username, index
         userlist.ItemData(index) = userID
      End If
      If (index = 0) Then
         userlist.Text = username
      End If
      index = index + 1
   Loop

   If count = 0 Then
      MsgBox gStringTable(3324) '"Can't find any Usernames to install programs for.  Installation cancelled."
      installType = "none"
   ElseIf count = 1 Then
      userlist.ListIndex = 0
      installType = "one"
   Else
      userlist.ListIndex = 0
      installType = "many"
   End If
   With Me
      .Left = frmMain.Left + (frmMain.Width - .Width) / 2
      .Top = frmMain.Top + (frmMain.Height - .Height) / 2
   End With
End Sub

Public Sub DoInstall(strInstall As String)
   mvarInstall = strInstall
   If installType = "many" Then
      Me.Show 1
   ElseIf installType = "one" Then
      butInstall_Click
      Unload Me
   Else
      Unload Me
   End If
End Sub

Public Property Let install(strInstall As String)
   mvarInstall = strInstall
End Property

Public Property Get install() As String
   install = mvarInstall
End Property
#End If
