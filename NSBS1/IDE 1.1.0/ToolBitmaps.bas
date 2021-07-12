Attribute VB_Name = "ToolBitmaps"
Option Explicit
DefLng A-Z

Declare Function LoadBitmap Lib "user32" Alias "LoadBitmapA" (ByVal hInstance As Long, ByVal lpBitmapName As String) As Long
Declare Function OpenClipboard Lib "user32" (ByVal hWnd As Long) As Long
Declare Function CloseClipboard Lib "user32" () As Long
Declare Function EmptyClipboard Lib "user32" () As Long
Declare Function SetClipboardData Lib "user32" (ByVal wFormat As Long, ByVal hMem As Long) As Long
Declare Function LoadImage Lib "user32" Alias "LoadImageA" (ByVal hInst As Long, ByVal lpsz As String, ByVal un1 As Long, ByVal n1 As Long, ByVal n2 As Long, ByVal un2 As Long) As Long

Public Const CF_BITMAP = 2
Public Const LR_LOADMAP3DCOLORS = &H1000
Public Const LR_LOADFROMFILE = &H10
Public Const LR_LOADTRANSPARENT = &H20
Public Const IMAGE_BITMAP = 0

Public Sub MakeFileTrans(ImgPic As Object, ByVal FileName As String)
'You'll need to add an NT 4.0 procedure
Dim BitMapLong As Long
Dim TempLong As Long
Dim hfile As Integer
Dim bytResData() As Byte

   hfile = FreeFile
   bytResData = LoadResData(114, "CUSTOM")
   Open App.Path & "\toolb.bmp" For Binary As hfile
   Put #hfile, , bytResData
   Close #hfile
   FileName = App.Path & "\toolb.bmp"
   TempLong = OpenClipboard(0)
   TempLong = EmptyClipboard()
 
   BitMapLong = LoadImage(0, FileName, IMAGE_BITMAP, 0, 0, _
                   LR_LOADFROMFILE Or LR_LOADMAP3DCOLORS Or LR_LOADTRANSPARENT)
   TempLong = SetClipboardData(CF_BITMAP, BitMapLong)
   TempLong = CloseClipboard()

   Set ImgPic.Picture = Clipboard.GetData(vbCFBitmap)
   Clipboard.SetText ""
End Sub
