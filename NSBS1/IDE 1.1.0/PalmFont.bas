Attribute VB_Name = "PalmFont"
Private FontMask(8) As Byte

Type PalmFontInfoType
   BytesWide As Integer
   ColsWide(258) As Integer
   RowsHigh As Integer
   Offsets(258) As Integer
   StartChar As Integer
   EndChar As Integer
   StartOffset As Integer
   LeadingPixels As Integer
End Type

Global PalmFontInfo(8) As PalmFontInfoType
Private FontsInitialized As Boolean

Sub PalmFont_Initialize()
   If FontsInitialized Then Exit Sub
   FontsInitialized = True
   FontMask(0) = &H80
   FontMask(1) = &H40
   FontMask(2) = &H20
   FontMask(3) = &H10
   FontMask(4) = &H8
   FontMask(5) = &H4
   FontMask(6) = &H2
   FontMask(7) = &H1

   Open InstallationDirectory + "\fonts.dat" For Binary As 13

   FontRetrieve 0, &H90
   FontRetrieve 1, &HAD4
   FontRetrieve 2, &H1636
   FontRetrieve 3, &H23D4
   FontRetrieve 4, &H2522
   FontRetrieve 5, &H25B0
   FontRetrieve 6, &H2622
   FontRetrieve 7, &H27AC
End Sub

Private Function GetInt() As Integer
   Dim l As Byte
   Dim r As Byte
   
   Get #13, , l
   Get #13, , r
   If l > 127 Then l = l - 128
   GetInt = l * 256 + r
   'MsgBox str(Loc(13)) + " getint=" + str(getint) + " " + str(l) + " " + str(r)
End Function
Private Sub FontRetrieve(theFont As Integer, p As Long)
   Dim i, j As Integer

   p = p + 1
   Seek 13, p
'MsgBox "loc(" + str(font) + ")=" + str(p)
'   i = GetInt() 'font type
   GetInt
'   FontStartChar(font) = getint()
   PalmFontInfo(theFont).StartChar = GetInt()
'   FontEndChar(font) = getint()
   PalmFontInfo(theFont).EndChar = GetInt()
'MsgBox "end char =" + str(FontEndChar(font))
'   i = GetInt() 'maxwidth
   GetInt
'   i = GetInt() 'kernmax
   GetInt
'   i = GetInt() 'nDescent
   GetInt
'   i = GetInt() 'fRecWidth
   GetInt
'   FontRowsHigh(font) = getint()
   PalmFontInfo(theFont).RowsHigh = GetInt()
'MsgBox "rowshIGH=" + str(FontRowsHigh(font))
'   i = GetInt() 'offset to o/w
   GetInt
'   i = GetInt() 'ascent
   GetInt
'   i = GetInt() 'descent
   GetInt
'   i = GetInt() 'leading
   GetInt
'   FontBytesWide(font) = getint() * 2
   PalmFontInfo(theFont).BytesWide = GetInt() * 2
'MsgBox "wide=" + str(FontBytesWide(font))
'   FontStartOffset(font) = Loc(13)
   PalmFontInfo(theFont).StartOffset = Loc(13)
   Seek 13, Loc(13) + PalmFontInfo(theFont).BytesWide * PalmFontInfo(theFont).RowsHigh + 1

   For i = 0 To UBound(PalmFontInfo(theFont).ColsWide)
      PalmFontInfo(theFont).ColsWide(i) = -1
   Next
'MsgBox "start=" + str(FontStartChar(font)) + " end=" + str(FontEndChar(font))
   For i = PalmFontInfo(theFont).StartChar To PalmFontInfo(theFont).EndChar + 2
      PalmFontInfo(theFont).Offsets(i) = GetInt()
'MsgBox "start offset (" + Str(font) + "," + Str(i) + ")=" + Str(FontOffsets(font, i))
   Next
   For i = PalmFontInfo(theFont).StartChar To PalmFontInfo(theFont).EndChar + 1
 '     PalmFontInfo(theFont).ColsWide(i) = GetInt()
      j = GetInt()
      If j > 256 Then j = j Mod 256
      PalmFontInfo(theFont).ColsWide(i) = j

'      PalmFontInfo(theFont).ColsWide(i) = GetInt()
'      Do While PalmFontInfo(theFont).ColsWide(i) > 256
'         PalmFontInfo(theFont).ColsWide(i) = PalmFontInfo(theFont).ColsWide(i) - 256
'      Loop
'MsgBox "cols wide (" + Str(font) + "," + Str(i) + ")=" + Str(FontColsWide(font, i))
   Next
End Sub

Private Function FontLeading(theFont As Integer) As Integer
   FontLeading = PalmFontInfo(theFont).LeadingPixels
End Function

Private Function FontCharIndex(theFont As Integer, char As String) As Integer
   FontCharIndex = Asc(char) - PalmFontInfo(theFont).StartChar
End Function

Private Function FontRows(theFont As Integer, char As String) As Integer
   If FontCharIndex(theFont, char) >= 0 Then
      FontRows = PalmFontInfo(theFont).RowsHigh
   Else
      FontRows = 0
   End If
End Function

Private Function FontCols(theFont As Integer, char As String) As Integer
   If FontCharIndex(theFont, char) >= 0 Then
      FontCols = PalmFontInfo(theFont).ColsWide(Asc(char))
   Else
      FontCols = 0
   End If
End Function

Private Function FontPixel(theFont As Integer, char As String, row As Integer, col As Integer) As Boolean
'   Dim z As String
   Dim pint As Integer
   Dim p As Long
   Dim i As Integer
'   Dim xx As Integer
   Dim zInt As Integer
   Dim zDouble As Double
   Dim charVal As Integer

   FontPixel = False
   charVal = Asc(char)
   If FontCharIndex(theFont, Mid(char, 1, 1)) < 0 Then Exit Function
   If PalmFontInfo(theFont).ColsWide(charVal) < 0 Then Exit Function
   p = PalmFontInfo(theFont).StartOffset + PalmFontInfo(theFont).BytesWide * row + 1

   pint = Int((PalmFontInfo(theFont).Offsets(charVal) + col) / 8)
   p = p + pint
   Seek #13, p
   'z = " "
   'Get #13, , z '0401
   Get #13, , zInt
   zDouble = zInt
   If zDouble < 0 Then zDouble = zDouble + 65536
   zDouble = zDouble Mod 256
   'Debug.Print Asc(z) & " " & zDouble

   i = (PalmFontInfo(theFont).Offsets(charVal) + col) Mod 8
   'xx = Asc(z) And FontMask(i)
   FontPixel = zDouble And FontMask(i)

'   If xx = 0 Then
'      FontPixel = False
'   Else
'      FontPixel = True
'   End If
End Function

'George: This function is only used in CForm.PrcOut
'George: Now that we use the Palm fonts, can we do without it?
Function FontTextHeight(theForm As Form, theString As String, theFont As Integer) As Integer
   If Not bPlainText Then
'MMD: Deleted Mag nific
'      FontTextHeight = PalmFontInfo(theFont).RowsHigh * mag nific
      FontTextHeight = PalmFontInfo(theFont).RowsHigh * 2
   Else
      FontTextHeight = theForm.TextHeight(theString)
   End If
End Function

'George: This function is only used in CForm.PrcOut
'George: Now that we use the Palm fonts, can we do without it?
Function FontTextWidth(theForm As Form, theString As String, theFont As Integer) As Integer
   Dim i As Integer

   If Not bPlainText Then
      FontTextWidth = 0
      For i = 1 To Len(theString)
'MMD: Deleted Mag nific
'         FontTextWidth = FontTextWidth _
               + (PalmFontInfo(theFont).ColsWide(Asc(Mid$(theString, i, 1))) _
               + PalmFontInfo(theFont).LeadingPixels) * mag nific
         FontTextWidth = FontTextWidth _
               + (PalmFontInfo(theFont).ColsWide(Asc(Mid$(theString, i, 1))) _
               + PalmFontInfo(theFont).LeadingPixels) * 2
      Next
   Else
      FontTextWidth = theForm.TextWidth(theString)
   End If
End Function

Function FontCheckAvail(theFont As Integer) As Boolean
   If Not FontsInitialized Then PalmFont_Initialize

   If PalmFontInfo(theFont).StartOffset = 0 Then
      MsgBox "Font " & theFont & " is not available."
      FontCheckAvail = False
   Else
      FontCheckAvail = True
   End If
End Function
