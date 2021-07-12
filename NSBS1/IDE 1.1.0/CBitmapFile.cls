VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CBitmapFile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Name As String
Public Path As String
Public FileName As String
Private m_nIdNo As Integer
Private m_Project As CProject

Private Const kVersion As Integer = 1
'2200 marks beginning of CBitmapFile string table entries
Private Const kResStrings As Integer = 2200

Public Sub Class_Initialize()
'   model.HighestSeqNo = model.HighestSeqNo + 1
'   IdNo = model.HighestSeqNo
   IdNo = 0
   Name = "Bmpfile"
   Path = ""
   FileName = ""
End Sub

Public Sub Save()
   Write #1, "bmpfile"
   Write #1, kVersion
   Write #1, Name
   Write #1, IdNo
   Write #1, Path
End Sub

Public Sub Restore()
Dim version As Integer

   Input #1, version
   If version <> kVersion Then
      MsgBox "Error: Invalid Bitmap File Version (" & version & ")"
      End
   End If
   Input #1, Name
   Input #1, m_nIdNo
   Input #1, Path
   SetFileName
End Sub

Public Sub PrcOut()
Dim bmpOut As bmpType
Dim offsetStop As Long
Dim wid As Long
Dim ht As Long
Dim widshort As Integer
Dim htshort As Integer
Dim b As Byte
Dim i, j, n, k As Integer
Dim o As Byte
Dim noBits As Integer
Dim noInBits As Integer
Dim noOutBits As Integer
Dim offset As Long
Dim filesize As Long
Dim ignorelong As Long
Dim headerSize As Long
Dim ignoreInt As Integer

   'make sure file exists
   On Error GoTo fileNotFound
   Open Path For Input As #10
   On Error GoTo 0
   Close #10

   Open Path For Binary As #10
   For i = Len(Path) To 1 Step -1
      If Mid(Path, i, 1) = "." Then Exit For
   Next
   If Right(Path, Len(Path) - i) = "icn" Then
      Do While Not EOF(10)
         Get #10, , b
         Put #3, , b
      Loop
      GoTo allDone
   End If

   For i = 1 To 2
      Get #10, , b
   Next
   filesize = bmpGetLong(10)
   If filesize = 0 Then
      MsgBox "Error: Bitmap " & Path & " has zero bytes."
      Close #10
      Exit Sub
   End If

'MsgBox "filesize=" + str(filesize)
   ignorelong = bmpGetLong(10)
   headerSize = bmpGetLong(10)
   ignorelong = bmpGetLong(10)
   wid = bmpGetLong(10)
   ht = bmpGetLong(10)
'MsgBox "wid=" + str(wid) + " ht=" + str(ht)
   ignoreInt = bmpGetShort(10)
   noBits = bmpGetShort(10)
   If noBits > 1 Then
      MsgBox "Error: color bitmaps are not supported(" + Path + "). This bitmap will be ignored."
      Close #10
      Exit Sub
   End If

   For i = 1 To 6
      ignorelong = bmpGetLong(10)
   Next
   For i = 54 To headerSize
      b = bmpGetByte(10)
   Next
   noInBits = Int((wid + 31) / 32) * 32
   noOutBits = Int((wid + 15) / 16) * 16
   'write out header info for bitmap
   widshort = wid
   htshort = ht
'MsgBox "wid=" + str(widshort) + " ht=" + str(htshort) + " rowbytes=" + str(noOutBits / 8)
   bmpOut.Width.w = cvtWord(widshort)
   bmpOut.Height.w = cvtWord(htshort)
   bmpOut.rowBytes.w = cvtWord(noOutBits / 8)
   bmpOut.flags.w = &H0
   bmpOut.resv1.w = 0
   bmpOut.resv2.w = 0
   bmpOut.resv3.w = 0
   bmpOut.resv4.w = 0
   Put #3, , bmpOut

   offset = filesize + noInBits / 8
'MsgBox "noInbits=" + str(noInBits) + " noOutbits=" + str(noOutBits)
 
nextLine:
   offset = offset - 2 * noInBits / 8
   offsetStop = offset + noInBits / 8
   If offset < headerSize Then GoTo allDone
'MsgBox "at next line --offset=" + str(offset)
   j = 8
   o = &H0
   k = 0
   For i = 1 To noInBits
      If j = 8 Then
         offset = offset + 1
       
         Seek #10, offset
         b = bmpGetByte(10)
'MsgBox "i=" + str(i) + "read = " + str(b)
         j = 0
      End If

      j = j + 1
      If i > noOutBits Then
         GoTo nobit
      End If
      If i > wid Then
         GoTo zerobit
      End If

'MsgBox "examine b=" + str(b) + " j=" + str(j)
      Select Case j
      Case 1
         If Not (b And &H80) = 0 Then GoTo zerobit
      Case 2
         If Not (b And &H40) = 0 Then GoTo zerobit
      Case 3
         If Not (b And &H20) = 0 Then GoTo zerobit
      Case 4
         If Not (b And &H10) = 0 Then GoTo zerobit
      Case 5
         If Not (b And &H8) = 0 Then GoTo zerobit
      Case 6
         If Not (b And &H4) = 0 Then GoTo zerobit
      Case 7
         If Not (b And &H2) = 0 Then GoTo zerobit
      Case 8
         If Not (b And &H1) = 0 Then GoTo zerobit
      End Select

      'put in a bit
'MsgBox "at put in bit --k=" + str(k)
      k = k + 1
      Select Case k
      Case 1
         o = o Or &H80
      Case 2
         o = o Or &H40
      Case 3
         o = o Or &H20
      Case 4
         o = o Or &H10
      Case 5
         o = o Or &H8
      Case 6
         o = o Or &H4
      Case 7
         o = o Or &H2
      Case 8
         o = o Or &H1
      End Select
      GoTo nobit

zerobit:
      k = k + 1

nobit:
      If k = 8 Then
         Put #3, , o
'MsgBox "writing out " + str(o)
         o = &H0
         k = 0
      End If

skipIt:
   Next

lineDone:
   j = noInBits
'MsgBox "j=" + str(j) + " inbits=" + str(noInBits) + " outbits=" + str(noOutBits) + " k=" + str(k)
   Do
      j = j + 1
      If j > noOutBits Then
         Exit Do
      End If
      k = k + 1
      If k = 8 Then
         Put #3, , o
         o = &H0
         k = 0
      End If
   Loop
   If Not k = 0 Then
      Put #3, , o
'MsgBox "writing out " + str(o)
   End If
   GoTo nextLine
allDone:
   Close #10
   Exit Sub

fileNotFound: On Error GoTo 0
   MsgBox "Error: Bitmap " & Path & " not found. This bitmap will be skipped."
End Sub

Function bmpGetByte(fil As Integer) As Integer  '10.26.00 GH function rewritten
  Dim b As Byte
  Get #fil, , b
  bmpGetByte = b
End Function

Function bmpGetShort(fil As Integer) As Integer  '10.26.00 GH function rewritten
  Dim b1 As Byte
  Dim b2 As Byte
  Dim res As Integer
  Get #fil, , b1
  Get #fil, , b2
  res = b2 * 256# + b1
  bmpGetShort = res
End Function

Function bmpGetLong(fil As Integer) As Long '10.26.00 GH function rewritten
  Dim res As Long
  Dim b1 As Byte
  Dim b2 As Byte
  Dim b3 As Byte
  Dim b4 As Byte
  Get #fil, , b1
  Get #fil, , b2
  Get #fil, , b3
  Get #fil, , b4
  res = b4 * 16777216# + b3 * 65536# + b2 * 256# + b1
  bmpGetLong = res
End Function

Public Sub SetFileName(Optional newPath As String = "")
   If Len(Path) = 0 And Len(newPath) <> 0 Then
      Path = newPath
   End If
   FileName = Mid(Path, InStrRev(Path, "\") + 1)
End Sub

Public Property Let IdNo(ByVal nIdNo As Integer)
   m_nIdNo = nIdNo
   If m_nIdNo Then Name = "BmpFile" & m_nIdNo
End Property

Public Property Get IdNo() As Integer
   IdNo = m_nIdNo
End Property

Public Property Get Project() As CProject
   Set Project = m_Project
End Property

Public Property Let Project(prj As CProject)
   Set m_Project = prj
End Property

Public Sub GetProperty()
Static nProp As Integer

   If nProp = 3 Then
      gPropInfo.Name = ""
      nProp = 0
      Exit Sub
   End If
   gPropInfo.Name = LoadResString(kResStrings + nProp)
   Select Case nProp
   Case 0 'Name
      gPropInfo.Val = Name
      gPropInfo.Type = pgString
   Case 1 'ID
      gPropInfo.Val = IdNo
      gPropInfo.Type = pgReadOnly
   Case 2 'Path
      gPropInfo.Val = Path
      gPropInfo.Type = pgOther
      gPropInfo.Data = LoadResString(kResStrings + 3)
   End Select
   nProp = nProp + 1
End Sub

Public Property Get Tag() As String
   Tag = Join(Array("bitmap", m_Project.Name, IdNo), "|")
End Property
