VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "msflxgrd.ocx"
Begin VB.Form frmThemeEditor 
   Caption         =   "Theme Editor"
   ClientHeight    =   6435
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   10620
   LinkTopic       =   "Form1"
   ScaleHeight     =   6435
   ScaleWidth      =   10620
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton btnImportColors 
      Caption         =   "Import Colors"
      Height          =   255
      Left            =   8160
      TabIndex        =   7
      Top             =   120
      Visible         =   0   'False
      Width           =   1335
   End
   Begin VB.CommandButton btnOpen 
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
      Height          =   285
      Left            =   4080
      TabIndex        =   6
      Top             =   120
      Width           =   285
   End
   Begin VB.TextBox txtName 
      Height          =   285
      Left            =   1440
      TabIndex        =   5
      Top             =   120
      Width           =   2535
   End
   Begin VB.CommandButton btnSaveAs 
      Caption         =   "Save As...1006"
      Height          =   375
      Left            =   6960
      TabIndex        =   3
      Tag             =   "1006"
      Top             =   5160
      Width           =   1335
   End
   Begin VB.CommandButton btnNew 
      Caption         =   "New1087"
      Height          =   375
      Left            =   5280
      TabIndex        =   2
      Tag             =   "1087"
      Top             =   5160
      Width           =   1335
   End
   Begin VB.CommandButton btnSave 
      Caption         =   "Save1106"
      Height          =   375
      Left            =   8520
      TabIndex        =   1
      Tag             =   "1106"
      Top             =   5160
      Width           =   1335
   End
   Begin MSFlexGridLib.MSFlexGrid gridThemes 
      Height          =   4455
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   10335
      _ExtentX        =   18230
      _ExtentY        =   7858
      _Version        =   393216
      Rows            =   30
      Cols            =   4
      ScrollBars      =   2
   End
   Begin VB.Label lblName 
      Caption         =   "ThemeName3453"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Tag             =   "3453"
      Top             =   120
      Width           =   1095
   End
End
Attribute VB_Name = "frmThemeEditor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private themeColors() As Long
Private Rows As Integer
Private openName As String

Private Const Classic = "01010101,01FFFFFF,01010101,01330199,01FFFFFF,01010101,01FFFFFF,01010101,01330199,01FFFFFF,01FFFFFF,01010101,01999999,01010101,01FFFF01,01010101,01010101,01FFFFFF,01010101,0101FFFF,01330199,01330199,01FFFFFF,01330199,01FFFFFF,01330199,01FFFFFF,0101CC01,01FFCC01,01FF0101,01330199,Classic"

Private Sub btnOpen_Click()
   
   frmMain.dlgCommonDialog.DialogTitle = gStringTable(2207)
   frmMain.dlgCommonDialog.InitDir = fileDirectory + "\themes"
   frmMain.dlgCommonDialog.Filter = "Theme Files(*.pdb)|*.pdb"
   frmMain.dlgCommonDialog.DefaultExt = ".pdb"
   frmMain.dlgCommonDialog.flags = cdlOFNNoChangeDir
   frmMain.dlgCommonDialog.CancelError = True
   frmMain.dlgCommonDialog.filename = ""
   On Error GoTo gotCancel
   frmMain.dlgCommonDialog.ShowOpen
   On Error GoTo 0
   loadTheme frmMain.dlgCommonDialog.filename
   
gotCancel:
End Sub
  
Sub loadTheme(filename)
   Dim i As Integer
   
   themeColors = getThemeColors(filename)
   
   txtName.Text = Mid(filename, InStrRev(filename, "\") + 1)
   txtName.Text = Left(txtName.Text, Len(txtName.Text) - 4)
   gridThemes.col = 3
   For i = 1 To Rows - 1
     'gridThemes.TextMatrix(i, 3) = "  " & i - 1 & " " & Hex(themeColors(gridThemes.RowData(i)))
     gridThemes.row = i
     gridThemes.CellBackColor = swapRGB(themeColors(gridThemes.RowData(i)))
   Next
   
   openName = filename
   
End Sub

Private Sub btnSave_Click()
   Dim i As Integer
   Dim filename As String
   Dim themeResource(127) As Byte  '4*31 elements
   Dim s As String
   Dim b1 As Integer
   Dim b2 As Integer
   Dim b3 As Integer
   Dim frm As Form
   Dim FileNumber As Integer
   FileNumber = FreeFile
  
   'does file exist already?
   On Error GoTo fileNotFound
   Open filename For Random As #FileNumber
   On Error GoTo 0
   Close #FileNumber
   
   If LCase(openName) <> LCase(filename) Then
      i = MsgBox(gStringTable(3455) & txtName.Text & "?", vbOKCancel)
      If i <> 1 Then Exit Sub
      openName = filename
   End If

fileNotFound:
   On Error GoTo 0
      
   'number of colors in theme
   themeResource(0) = 30
   themeResource(1) = 1
   themeResource(2) = 1
   themeResource(3) = 1
   
   For i = 0 To 30 'add each color to themeResource
      s = Hex(&H1000000 + themeColors(i))
      b1 = Val("&h" & Mid(s, 2, 2))
      b2 = Val("&h" & Mid(s, 4, 2))
      b3 = Val("&h" & Mid(s, 6, 2))
      If b1 = 0 Then b1 = 1
      If b2 = 0 Then b2 = 1
      If b3 = 0 Then b3 = 1
      themeResource(i * 4 + 4) = 1
      themeResource(i * 4 + 5) = b1
      themeResource(i * 4 + 6) = b2
      themeResource(i * 4 + 7) = b3
   Next
   
   SaveThemeFile txtName.Text, themeResource
   Unload Me
   DoEvents
   
   Set frm = frmMain.GetMDIChild(gsCurrentFormGlobalID)
   If frm Is Nothing Then
      'frmMain.ViewObject gsCurrentFormGlobalID
   Else
      frm.UpdateScreen
   End If
End Sub


Private Sub SaveThemeFile(Name As String, themeResource() As Byte)
   Dim filename As String
   Dim data(212) As Byte
   Dim FileNumber As Integer
   Dim i As Integer
   FileNumber = FreeFile
   Dim s As String
   
   For i = 0 To 212
      data(i) = 0
   Next
   
   For i = 0 To Len(Name) - 1
      data(i) = Asc(Mid(Name, i + 1, 1))
   Next
   
   For i = 0 To 1 'creation and modification date - arbitrary
      data(36 + i * 4) = &HC5
      data(37 + i * 4) = &H4B
      data(38 + i * 4) = &H1F
      data(39 + i * 4) = &H16
   Next
   
   s = "dataNSBa" 'type and creator
    For i = 0 To Len(s) - 1
      data(60 + i) = Asc(Mid(s, i + 1, 1))
   Next
   
   data(77) = 1     'number of records
   data(81) = &H58  'position themeResource starts
   
   For i = 0 To 123
      data(88 + i) = themeResource(i)
   Next
   
   filename = fileDirectory & "\themes\" & Name & ".pdb"
   Open filename For Binary Access Write As #FileNumber
   Put #FileNumber, , data
   Close #FileNumber
End Sub

Function hexString2string(s As String) As String
   hexString2string = hexChar2char(Mid(s, 1, 2)) & hexChar2char(Mid(s, 3, 2)) & hexChar2char(Mid(s, 5, 2)) & hexChar2char(Mid(s, 7, 2))
End Function
Function hexChar2char(s)
   hexChar2char = Chr(Val("&h" & s))
   If hexChar2char = Chr(0) Then hexChar2char = Chr(1) 'zero not allowed in Palm OS string
End Function

Private Sub btnNew_Click()
   Dim i As Integer
   Dim s() As String
   
   s = Split(Classic, ",")
   
   txtName.Text = ""
   For i = 0 To 30
      themeColors(i) = Val("&h" & Mid(s(i), 3))
   Next
   gridThemes.col = 3
   For i = 1 To Rows - 1
      gridThemes.row = i
      gridThemes.CellBackColor = swapRGB(themeColors(gridThemes.RowData(i)))
   Next
   openName = txtName.Text
End Sub

Private Sub btnSaveAs_Click()
Dim filename As String

   frmMain.dlgCommonDialog.DialogTitle = gStringTable(2207)
   frmMain.dlgCommonDialog.InitDir = fileDirectory + "\themes"
   frmMain.dlgCommonDialog.Filter = "Theme Files(*.pdb)|*.pdb"
   frmMain.dlgCommonDialog.DefaultExt = ".pdb"
   frmMain.dlgCommonDialog.flags = cdlOFNNoChangeDir
   frmMain.dlgCommonDialog.CancelError = True
   frmMain.dlgCommonDialog.filename = txtName.Text
   On Error GoTo gotCancel
   frmMain.dlgCommonDialog.ShowSave
   On Error GoTo 0
   filename = frmMain.dlgCommonDialog.filename
   txtName.Text = Mid(filename, InStrRev(filename, "\") + 1) 'trim left
   txtName.Text = Left(txtName.Text, Len(txtName.Text) - 4) 'trim right
   
   btnSave_Click
   
gotCancel:
End Sub

Private Sub Form_Load()
   Dim data() As String
   Dim i As Integer
   Dim Form As CForm
   Dim filename As String
   
   LoadResStrings Me
   
   btnOpen.font = "Arial"
   btnOpen.FontBold = True
    
   Form_Resize
   
   With gridThemes
      Rows = 1
      For i = 0 To 29 'section in stringTable with data
         data = Split(gStringTable(i + 3500), "|")
         If data(0) <> "(not used)" Then
            .TextMatrix(Rows, 1) = data(0)
            .TextMatrix(Rows, 2) = data(1)
            .RowData(Rows) = i
             Rows = Rows + 1
         End If
      Next
      .Rows = Rows
   End With
   
   filename = GetAbsolutePath(gTarget.theme, "")
   loadTheme filename
   
End Sub

Private Sub Form_Resize()
   With gridThemes
      .Top = 500
      .Height = 30 * 15 * 12 - 30   'lines * twips * pixels/line - 2 pixels
      .RowHeight(0) = 0
      .Width = Me.Width - 300
      .ColWidth(0) = 0
      .ColWidth(1) = 2250
      .ColWidth(3) = 1500
      .ColWidth(2) = .Width - 3750
   End With
   lblName.Top = 150
   txtName.Top = 150
   btnNew.Top = Me.Height - 600 - btnNew.Height
   btnNew.Left = Me.Width - 4 * 300 - btnNew.Width * 3
   btnSaveAs.Top = Me.Height - 600 - btnNew.Height
   btnSaveAs.Left = Me.Width - 3 * 300 - btnNew.Width * 2
   btnSave.Top = Me.Height - 600 - btnNew.Height
   btnSave.Left = Me.Width - 2 * 300 - btnNew.Width * 1
   'Me.Height = btnSave.Top + btnSave.Height + 150
End Sub

Sub gridThemes_click() 'bring up the color picker when grid clicked on
   If gridThemes.col <> 3 Then Exit Sub
   Dim oleNewColor As OLE_COLOR
   oleNewColor = ShowColorDialog(Me.hWnd, True, swapRGB(themeColors(gridThemes.RowData(gridThemes.row))))
   If oleNewColor <> -1 Then
      'MsgBox "oleNewColor " & Hex(oleNewColor)
      gridThemes.CellBackColor = oleNewColor
      themeColors(gridThemes.RowData(gridThemes.row)) = swapRGB(oleNewColor)
   End If
End Sub


#If 1 = 0 Then 'dead code.
Private Sub btnImportColors_Click()
'Import data from Memopad. The colors app put the themes there.
'just used once, to create the initial entries in \Themes
   Dim PalmDB
   Dim i As Integer
   Dim s As String
   Dim chan As Integer
   Dim recs(1000) As String
   Dim rec As String
   Dim themeResource As String
   Dim Name As String
   Dim theme As Integer
   Dim b1 As String
   Dim b2 As String
   Dim b3 As String
   
   chan = 98
   Open "e:\nsbs1\files\colors.txt" For Input As #chan
   Do Until EOF(chan)
      Line Input #chan, recs(i)
      i = i + 1
   Loop
   Close #chan
       
   Set PalmDB = New PalmDBLib.Database
   For theme = 0 To 29 'number of themes in txt file
      Name = Mid(recs(theme * 32), 10)
      themeResource = Chr(30) & Chr(1) & Chr(1) & Chr(1) 'number of colors in theme
      For i = 1 To 30 'add each color to theme
         rec = recs(theme * 32 + i) 'get a color record
         s = Mid(rec, InStrRev(rec, "=") + 1) 'get the color
         b1 = Val("&h" & Mid(s, 1, 2))
         b2 = Val("&h" & Mid(s, 3, 2))
         b3 = Val("&h" & Mid(s, 5, 2))
         If b1 = 0 Then b1 = 1
         If b2 = 0 Then b2 = 1
         If b3 = 0 Then b3 = 1
         themeResource = themeResource & Chr(1) & Chr(b1) & Chr(b2) & Chr(b3)
      Next
      
      SaveThemeFile Name, themeResource
   
   Next
   Set PalmDB = Nothing

End Sub
#End If

