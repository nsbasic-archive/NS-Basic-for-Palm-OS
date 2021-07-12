VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmBrowser 
   ClientHeight    =   5160
   ClientLeft      =   3060
   ClientTop       =   3315
   ClientWidth     =   6540
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   5160
   ScaleWidth      =   6540
   ShowInTaskbar   =   0   'False
   Begin VB.Timer timTimer 
      Enabled         =   0   'False
      Interval        =   5
      Left            =   6180
      Top             =   1500
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Left            =   2670
      Top             =   2340
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   24
      ImageHeight     =   24
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   6
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrowser.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrowser.frx":0712
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrowser.frx":0E24
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrowser.frx":1536
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrowser.frx":1C48
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrowser.frx":235A
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin SHDocVwCtl.WebBrowser brwWebBrowser 
      Height          =   3734
      Left            =   50
      TabIndex        =   0
      Top             =   50
      Width           =   5393
      ExtentX         =   9513
      ExtentY         =   6586
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   ""
   End
End
Attribute VB_Name = "frmBrowser"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public StartingAddress As String
Dim mbDontNavigateNow As Boolean

Private Sub Form_Load()
   On Error Resume Next
   LoadResStrings Me
   Me.Show
'   tbToolBar.Refresh
   Form_Resize


'   cboAddress.Move 50, lblAddress.Top + lblAddress.Height + 15


   If Len(StartingAddress) > 0 Then
'      cboAddress.Text = StartingAddress
'      cboAddress.AddItem cboAddress.Text
      'try to navigate to the starting address
      timTimer.Enabled = True
      brwWebBrowser.Navigate StartingAddress
   End If


End Sub

Private Sub brwWebBrowser_DownloadComplete()
   On Error Resume Next
   Me.caption = brwWebBrowser.LocationName
End Sub

Private Sub brwWebBrowser_NavigateComplete2(ByVal pDisp As Object, URL As Variant)
   On Error Resume Next
   Dim i As Integer
   Dim bFound As Boolean
   Me.caption = brwWebBrowser.LocationName
'   For i = 0 To cboAddress.ListCount - 1
'      If cboAddress.List(i) = brwWebBrowser.LocationURL Then
'         bFound = True
'         Exit For
'      End If
'   Next i
   mbDontNavigateNow = True
'   If bFound Then
'      cboAddress.RemoveItem i
'   End If
'   cboAddress.AddItem brwWebBrowser.LocationURL, 0
'   cboAddress.ListIndex = 0
   mbDontNavigateNow = False
End Sub

Private Sub Form_Resize()
   On Error Resume Next
'   cboAddress.Width = Me.ScaleWidth - 100
   brwWebBrowser.Width = Me.ScaleWidth - 100
   brwWebBrowser.Height = Me.ScaleHeight - 100
End Sub

Private Sub timTimer_Timer()
   If brwWebBrowser.Busy = False Then
      timTimer.Enabled = False
      Me.caption = "NSBasic.com" 'brwWebBrowser.LocationName
   Else
      Me.caption = "Working..."
   End If
End Sub
