VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIBitmap"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Member0" ,"UIGadget"
Option Explicit

Public obj As New CUIObject
Private m_nResourceID As Integer
Private m_nGradientColor1 As Long
Private m_nGradientColor2 As Long
Private m_nGradientStyle As Integer  '1=top to bottom, 0=left to right
Private m_sCaption As String
Private m_nAlignment As Integer      '0=Left, 1=Right, 2=Center
Private m_nAppearance As Integer     '0=Flat, 1=3D
Private m_nBorderStyle As Integer    '0-none, 1=single
Private m_bFontBold As Boolean
Private m_bFontItalic As Boolean
Private m_sFontName As String
Private m_nFontSize As Single
Private m_bFontStrikethru As Boolean
Private m_bFontUnderline As Boolean
Private m_nForeColor As Long
Private m_sPicture As String
Private m_bStretch As Boolean

Private Const kVersion As Integer = 2
'2500 marks beginning of CUIBitmap string table entries
Private Const kResStrings As Integer = 2500
Private Const kErrStrings As Integer = 2550
Private Const kUserProps As Integer = 17
Private Const kTotalProps As Integer = 28
Private Const kProperties As String = "Left-Top"
Private Const kMethods As String = "Hide-Show"

Private Sub class_initialize()
Dim trace As Boolean
trace = True

   If trace Then MsgBox "CUIBitmap:class_initialize 1"
   obj.Parent = Me
   obj.Name = "Bitmap"
   obj.Kind = "bmp"
   If trace Then MsgBox "CUIBitmap:class_initialize 2"
   m_nResourceID = obj.IdNo
   If trace Then MsgBox "CUIBitmap:class_initialize 2.1"
   m_nGradientColor1 = getUIColorTable(1)
   m_nGradientColor2 = getUIColorTable(1)
   If trace Then MsgBox "CUIBitmap:class_initialize 3"
   m_nGradientStyle = 1    '1=top to bottom
   m_sCaption = ""
   m_nAlignment = 2        '2=Center
   m_nBorderStyle = 0      '0=none
   m_nAppearance = 0       '0=Flat
   If trace Then MsgBox "CUIBitmap:class_initialize 4"
   m_bFontBold = False
   m_bFontItalic = False
   m_sFontName = "Arial"
   m_nFontSize = 10
   If trace Then MsgBox "CUIBitmap:class_initialize 5"
   m_bFontStrikethru = False
   m_bFontUnderline = False
   m_nForeColor = getUIColorTable(2)
   m_sPicture = ""
   m_bStretch = False
   If trace Then MsgBox "CUIBitmap:class_initialize 6"
End Sub

Public Sub PrcOut()
Dim c As Byte
Dim i As Integer
Dim vw As CForm
Dim ob As Object
Dim bmp As bitmapOut
Dim bfl As CBitmapFile
Dim bValid As Boolean
Dim bBitmapOk As Boolean

   If obj.Usable Then
      bmp.Usable = &H80
   Else
      bmp.Usable = 0
   End If
   bmp.unused = &H0
   bmp.pos.x = cvtWord(obj.OrigLeft)
   bmp.pos.y = cvtWord(obj.OrigTop)
   
   If m_nResourceID > 0 And m_nResourceID <> obj.IdNo Then
      'check if bitmap exists
      For Each bfl In gTarget.BitmapCollection
         If bfl.IdNo = m_nResourceID Then bBitmapOk = True
      Next
      If bBitmapOk = False Then
         MsgBox gStringTable(3347) & ": " & m_nResourceID '"Bitmap object has invalid Resource ID"
         compileOkSw = False
      End If
      bmp.rscId.w = cvtWord(m_nResourceID)
   Else
      bmp.rscId.w = cvtWord(obj.IdNo)
   End If
   

   c = &H4
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   Put #9, , bmp
End Sub

Public Sub Restore()
Dim version As Integer
Dim properties As String
Dim proplist() As String
Dim i As Integer

   Input #1, version
   If version > kVersion Then
      MsgBox gStringTable(3267) + version '"Error: Invalid bitmap version (" & version & ")"
      End
   End If

   Input #1, m_nResourceID
   If version > 1 Then
      Input #1, properties
   End If
   obj.Restore
   If m_nResourceID = 0 Then m_nResourceID = obj.IdNo
   
   If version > 1 Then
      proplist = Split(properties, ",")
      For i = 0 To UBound(proplist) - 1
         setPropertyVal (proplist(i))
      Next
   End If
End Sub

Public Sub Save()
   Write #1, obj.Kind
   Write #1, kVersion
   Write #1, m_nResourceID
   Write #1, getAllProperties
   obj.Save
End Sub

Public Function Copy() As String
   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   Copy = Copy & ResourceId & vbCrLf
   Copy = Copy & getAllProperties & vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim proplist() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "bmp" Then
      MsgBox gStringTable(3268) '"Invalid paste: Bitmap Type"
      End
   End If
   If strLines(2) > kVersion Then
      MsgBox gStringTable(3269) '"Invalid paste: Bitmap Version"
      End
   End If

   'Restore properties
   ResourceId = strLines(3)
   proplist = Split(strLines(4), ",")

   'Remove used code and paste inherited object
   For i = 5 To UBound(strLines)
      strLines(i - 4) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 4)
   obj.Paste strLines
   
   For i = 0 To UBound(proplist) - 1
      setPropertyVal (proplist(i))
   Next
   If Not ValidateProperty("Bitmap ID", ResourceId) Then ResourceId = 0
   
End Sub

Public Sub ScreenDraw()
Dim filename As String
Dim w As Integer
Dim h As Integer
Dim properties() As String
   Const cCaption = 0
   Const cAlignment = 1
   Const cGradientColor1 = 2
   Const cGradientColor2 = 3
   Const cGradientStyle = 4
   Const cWidth = 5
   Const cHeight = 6
   Const cPicture = 7
   Const cStretch = 8

   If obj.Control Is Nothing Then Exit Sub
   If gbUIBitmapScreenDrawHappening Then Exit Sub
   gbUIBitmapScreenDrawHappening = True 'stop recursive calls to this sub
   properties = Split(obj.Control.Tag, "|")
   If properties(cStretch) = "" Then properties(cStretch) = "False"
   
   obj.ScreenDraw False
   
   If ResourceId = obj.IdNo Then

      If obj.Control.Appearance <> Appearance Then
         obj.Control.Appearance = Appearance
      End If
      If obj.Control.BorderStyle <> BorderStyle Then
         obj.Control.BorderStyle = BorderStyle
      End If
      If obj.Control.FontBold <> FontBold Then
         obj.Control.FontBold = FontBold
         FontBold = obj.Control.FontBold 'set to legal value
      End If
      If obj.Control.FontItalic <> FontItalic Then
         obj.Control.FontItalic = FontItalic
         FontItalic = obj.Control.FontItalic 'set to legal value
      End If
      If obj.Control.fontname <> fontname Then
         obj.Control.fontname = fontname
      End If
      If obj.Control.fontSize <> fontSize Then
         obj.Control.fontSize = fontSize
         fontSize = obj.Control.fontSize 'reset fontsize to legal value
      End If
      If obj.Control.FontStrikethru <> FontStrikethru Then
         obj.Control.FontStrikethru = FontStrikethru
      End If
      If obj.Control.FontUnderline <> FontUnderline Then
         obj.Control.FontUnderline = FontUnderline
      End If
      If obj.Control.ForeColor <> ForeColor Then
         obj.Control.ForeColor = ForeColor
      End If
              
      If Picture <> "" Then 'Picture Style Bitmap
        If properties(cPicture) <> Picture Or properties(cStretch) <> str(Stretch) Or _
           Abs(Val(properties(cWidth)) - obj.Control.Width) > 1 Or _
           Abs(Val(properties(cHeight)) - obj.Control.Height) > 1 Then

           If Stretch Then 'size image to current bitmap object size
               obj.Control.AutoRedraw = True
               obj.Control.AutoSize = False
               On Error GoTo pictureNotFound
               obj.Control.Picture = LoadPicture(Picture)
               On Error GoTo 0
               obj.Control.PaintPicture obj.Control.Picture, 0, 0, obj.Control.Width, obj.Control.Height
               obj.Control.Picture = obj.Control.Image
               obj.Control.AutoRedraw = False
           Else 'size bitmap object to image size
               obj.Control.AutoSize = True
               obj.Control.AutoRedraw = False
               On Error GoTo pictureNotFound
               obj.Control.Picture = LoadPicture(Picture)
               On Error GoTo 0
               obj.Width = obj.Control.Width / obj.Control.Parent.MagFactor
               obj.Height = obj.Control.Height / obj.Control.Parent.MagFactor
           End If
           properties(cPicture) = Picture
           properties(cStretch) = Stretch
           properties(cWidth) = obj.Control.Width
           properties(cHeight) = obj.Control.Height
        End If
      Else  'Text and Gradient style bitmap
       'Gradient is cleared by .cls, so it needs to be redrawn each time
        If Val(properties(cGradientColor1)) <> GradientColor1 Or _
           Val(properties(cGradientColor2)) <> GradientColor2 Or _
           Val(properties(cGradientStyle)) <> GradientStyle Then
           properties(cGradientColor1) = str(GradientColor1)
           properties(cGradientColor2) = str(GradientColor2)
           properties(cGradientStyle) = str(GradientStyle)
        End If
        DrawGradient obj.Control.hDC, obj.Control.Width, obj.Control.Height, GradientColor1, GradientColor2, GradientStyle
        
        'Caption is cleared by .cls, so it needs to be redrawn each time
        If properties(cCaption) <> caption Or _
           Val(properties(cAlignment)) <> Alignment Then 'but only saved if it actually changed
           properties(cCaption) = caption
           properties(cAlignment) = str(Alignment)
        End If
        w = obj.Control.TextWidth(caption)
        h = obj.Control.TextHeight(caption)
        obj.Control.CurrentY = (obj.Control.Height / 2) - (h / 2)
        If Alignment = 0 Then obj.Control.CurrentX = 5
        If Alignment = 1 Then obj.Control.CurrentX = obj.Control.Width - 5 - w
        If Alignment = 2 Then obj.Control.CurrentX = (obj.Control.Width / 2) - (w / 2)
        obj.Control.Print caption
      End If
           
   End If
   
pictureNotFound:

   obj.Control.Tag = Join(properties, "|")
   obj.DrawSelected
   gbUIBitmapScreenDrawHappening = False
   frmMain.sbStatusBar.Panels(1).Text = "Image Size:" & (obj.Control.Width / obj.Control.Parent.MagFactor) _
     * (obj.Control.Height / obj.Control.Parent.MagFactor) * 8
End Sub

Public Property Let ResourceId(ByVal vData As Integer)
   m_nResourceID = vData
   If m_nResourceID = 0 Then
      obj.Label = ""
   Else
      obj.Label = m_nResourceID
   End If
End Property
Public Property Get ResourceId() As Integer
   If m_nResourceID = 0 Then m_nResourceID = obj.IdNo
   ResourceId = m_nResourceID
End Property

Public Property Let FontBold(ByVal vData As Boolean)
   m_bFontBold = vData
End Property
Public Property Get FontBold() As Boolean
   FontBold = m_bFontBold
End Property

Public Property Let FontItalic(ByVal vData As Boolean)
   m_bFontItalic = vData
End Property
Public Property Get FontItalic() As Boolean
   FontItalic = m_bFontItalic
End Property

Public Property Let FontStrikethru(ByVal vData As Boolean)
   m_bFontStrikethru = vData
End Property
Public Property Get FontStrikethru() As Boolean
   FontStrikethru = m_bFontStrikethru
End Property

Public Property Let FontUnderline(ByVal vData As Boolean)
   m_bFontUnderline = vData
End Property
Public Property Get FontUnderline() As Boolean
   FontUnderline = m_bFontUnderline
End Property

Public Property Let Stretch(ByVal vData As Boolean)
   m_bStretch = vData
End Property
Public Property Get Stretch() As Boolean
   Stretch = m_bStretch
End Property

Public Property Let GradientColor1(ByVal vData As Long)
   m_nGradientColor1 = vData
End Property
Public Property Get GradientColor1() As Long
   GradientColor1 = m_nGradientColor1
End Property

Public Property Let GradientColor2(ByVal vData As Long)
   m_nGradientColor2 = vData
End Property
Public Property Get GradientColor2() As Long
   GradientColor2 = m_nGradientColor2
End Property

Public Property Let Alignment(ByVal vData As Integer)
   m_nAlignment = vData
End Property
Public Property Get Alignment() As Integer
   Alignment = m_nAlignment
End Property

Public Property Let Appearance(ByVal vData As Integer)
   m_nAppearance = vData
End Property
Public Property Get Appearance() As Integer
   Appearance = m_nAppearance
End Property

Public Property Let BorderStyle(ByVal vData As Integer)
   m_nBorderStyle = vData
End Property
Public Property Get BorderStyle() As Integer
   BorderStyle = m_nBorderStyle
End Property

Public Property Let fontSize(ByVal vData As Single)
   m_nFontSize = vData
End Property
Public Property Get fontSize() As Single
   fontSize = m_nFontSize
End Property

Public Property Let ForeColor(ByVal vData As Long)
   m_nForeColor = vData
End Property
Public Property Get ForeColor() As Long
   ForeColor = m_nForeColor
End Property

Public Property Let GradientStyle(ByVal vData As Integer)
   m_nGradientStyle = vData
End Property
Public Property Get GradientStyle() As Integer
   GradientStyle = m_nGradientStyle
End Property

Public Property Let caption(ByVal vData As String)
   m_sCaption = vData
End Property
Public Property Get caption() As String
   caption = m_sCaption
End Property

Public Property Let fontname(ByVal vData As String)
   m_sFontName = vData
End Property
Public Property Get fontname() As String
   fontname = m_sFontName
End Property

Public Property Let Picture(ByVal vData As String)
   m_sPicture = vData
End Property
Public Property Get Picture() As String
   Picture = m_sPicture
End Property

Public Sub GetProperty()
Static nProp As Integer

   If nProp = kTotalProps Then
      gPropInfo.Name = ""
      nProp = 0
      Exit Sub
   End If

   gPropInfo.Val = ""
   Select Case nProp
   Case 0
      gPropInfo.Name = "Bitmap ID"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgString
   Case 1
      gPropInfo.Name = "Gradient Color 1"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgColor
      gPropInfo.data = "Color>" & gPropInfo.Val
   Case 2
      gPropInfo.Name = "Gradient Color 2"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgColor
      gPropInfo.data = "Color>" & gPropInfo.Val
   Case 3
      gPropInfo.Name = "Gradient Style"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgNumlist
      gPropInfo.data = gStringTable(3532) '0 - Left to Right>1 - Top to Bottom
   Case 4
      gPropInfo.Name = "Caption"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgString
   Case 5
      gPropInfo.Name = "Alignment"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgNumlist
      gPropInfo.data = gStringTable(3530) '0 - Left>1 - Right>2 - Center
   Case 6
      gPropInfo.Name = "Appearance"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgNumlist
      gPropInfo.data = gStringTable(3531) '0 - Flat>1 - 3D
   Case 7
      gPropInfo.Name = "FontBold"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgBoolean
   Case 8
      gPropInfo.Name = "FontItalic"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgBoolean
   Case 9
      gPropInfo.Name = "Font Name"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgFont
      gPropInfo.data = "Font>Choose Font for Caption"
   Case 10
      gPropInfo.Name = "FontSize"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgString
   Case 11
      gPropInfo.Name = "FontStrikethru"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgBoolean
   Case 12
      gPropInfo.Name = "FontUnderline"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgBoolean
   Case 13
      gPropInfo.Name = "Caption Color"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgColor
      gPropInfo.data = "Color>" & gPropInfo.Val
   Case 14
      gPropInfo.Name = "Picture"
      gPropInfo.Type = pgOther
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.data = gStringTable(2200) + ">" 'all image files
   Case 15
      gPropInfo.Name = "BorderStyle"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgNumlist
      gPropInfo.data = gStringTable(3533) '0 - none>1 - single
   Case 16
      gPropInfo.Name = "Stretch"
      gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
      gPropInfo.Type = pgBoolean

   Case kUserProps + 0: obj.GetProperty "(Name)"
   Case kUserProps + 1: obj.GetProperty "Type"
   Case kUserProps + 2: obj.GetProperty "ID"
   Case kUserProps + 3: obj.GetProperty "Left"
   Case kUserProps + 4: obj.GetProperty "Top"
   Case kUserProps + 5: obj.GetProperty "Width"
   Case kUserProps + 6: obj.GetProperty "Height"
   Case kUserProps + 7: obj.GetProperty "Visible"
   Case kUserProps + 8: obj.GetProperty "Nav Flags"
   Case kUserProps + 9: obj.GetProperty "Nav Above ID"
   Case kUserProps + 10: obj.GetProperty "Nav Below ID"
   End Select
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Bitmap ID": GetPropertyVal = ResourceId
   Case "Gradient Color 1": GetPropertyVal = Hex(GradientColor1)
   Case "Gradient Color 2": GetPropertyVal = Hex(GradientColor2)
   Case "Gradient Style": GetPropertyVal = GradientStyle
   Case "Caption": GetPropertyVal = caption
   Case "Alignment": GetPropertyVal = Alignment
   Case "Appearance": GetPropertyVal = Appearance
   Case "BorderStyle": GetPropertyVal = BorderStyle
   Case "FontBold": GetPropertyVal = FontBold
   Case "FontItalic": GetPropertyVal = FontItalic
   Case "Font Name": GetPropertyVal = fontname
   Case "FontSize": GetPropertyVal = fontSize
   Case "FontStrikethru": GetPropertyVal = FontStrikethru
   Case "FontUnderline": GetPropertyVal = FontUnderline
   Case "Caption Color": GetPropertyVal = Hex(ForeColor)
   Case "Picture": GetPropertyVal = Picture
   Case "Stretch": GetPropertyVal = Stretch
   
   Case Else: GetPropertyVal = obj.GetPropertyVal(strProp)
   End Select
End Function
Public Function setPropertyVal(ByVal strProp As String) As String
   Dim data() As String
   data = Split(strProp, "=")

   Select Case data(0)
   Case "Bitmap ID": ResourceId = Val(data(1))
   Case "Gradient Color 1": GradientColor1 = CLng("&h" & data(1))
   Case "Gradient Color 2": GradientColor2 = CLng("&h" & data(1))
   Case "Gradient Style": GradientStyle = Val(data(1))
   Case "Caption": caption = data(1)
   Case "Alignment": Alignment = Val(data(1))
   Case "Appearance": Appearance = Val(data(1))
   Case "BorderStyle": BorderStyle = Val(data(1))
   Case "FontBold": FontBold = (data(1) = "True")
   Case "FontItalic": FontItalic = (data(1) = "True")
   Case "Font Name": fontname = data(1)
   Case "FontSize": fontSize = Val(data(1))
   Case "FontStrikethru": FontStrikethru = (data(1) = "True")
   Case "FontUnderline": FontUnderline = (data(1) = "True")
   Case "Caption Color": ForeColor = CLng("&h" & data(1))
   Case "Picture": Picture = data(1)
   Case "Stretch": Stretch = (data(1) = "True")
   
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim nResID As Integer
Dim bmp As CBitmapFile
Dim frm As CForm
Dim o As Object
Dim i As Long

   ValidateProperty = True
   Select Case strProp
   Case "Bitmap ID"
      If Val(strVal) = 0 Or Val(strVal) = obj.IdNo Then
         ResourceId = obj.IdNo
      Else
         'Check to see that bitmap with that resource exists
         For Each bmp In obj.Form.Project.BitmapCollection
            If bmp.IdNo = Val(strVal) Then
               nResID = bmp.IdNo
               Exit For
            Else
               nResID = 0
            End If
         Next
         If nResID = 0 And Val(strVal) = obj.IdNo Then nResID = obj.IdNo
         If nResID = 0 Then
            MsgBox gStringTable(kErrStrings), vbCritical + vbOKOnly
            ValidateProperty = False
            Exit Function
         End If
   
         'Now check to make sure that no other object is using it
         For Each frm In obj.Form.Project.FormCollection
            For Each o In frm.ObjectCollection
               If Not o Is Me Then
                  If StrComp(o.obj.Kind, obj.Kind, vbTextCompare) = 0 Then
                     If ResourceId = nResID Then
                        MsgBox gStringTable(kErrStrings + 1), vbCritical + vbOKOnly
                        ValidateProperty = False
                        Exit Function
                     End If
                  End If
               End If
            Next
         Next
         ResourceId = nResID
      End If
   Case "Gradient Color 1"
      i = Val(strVal)
      If i >= 0 Then GradientColor1 = i
   Case "Gradient Color 2"
      i = Val(strVal)
      If i >= 0 Then GradientColor2 = i
   Case "Gradient Style"
      GradientStyle = Val(strVal)
   Case "Caption"
      caption = strVal
   Case "Alignment"
      Alignment = Val(strVal)
   Case "Appearance"
      Appearance = Val(strVal)
   Case "BorderStyle"
      BorderStyle = Val(strVal)
   Case "FontBold"
      FontBold = strVal Like g_strTrue
      obj.Control.FontBold = FontBold
      FontBold = obj.Control.FontBold 'reset FontBold to legal value
   Case "FontItalic"
      FontItalic = strVal Like g_strTrue
      obj.Control.FontItalic = FontItalic
      FontItalic = obj.Control.FontItalic 'reset FontItalic to legal value
   Case "Font Name"
      fontname = strVal
      FontItalic = obj.Control.FontItalic 'reset FontItalic to legal value
      FontBold = obj.Control.FontBold 'reset FontBold to legal value
   Case "FontSize"
      fontSize = Val(strVal)
      obj.Control.fontSize = fontSize
      fontSize = obj.Control.fontSize 'reset fontsize to legal value
   Case "FontStrikethru"
      FontStrikethru = strVal Like g_strTrue
   Case "FontUnderline"
      FontUnderline = strVal Like g_strTrue
   Case "Caption Color"
      i = Val(strVal)
      If i >= 0 Then ForeColor = i
   Case "Picture"
      Picture = strVal
   Case "Stretch"
      Stretch = strVal Like g_strTrue

   Case Else: ValidateProperty = obj.ValidateProperty(strProp, strVal)
   End Select
   If ValidateProperty Then gTarget.Dirty = ValidateProperty
End Function

Public Function PropertyList() As String()
   PropertyList = Split(kProperties, "-")
End Function

Public Function MethodList() As String()
   MethodList = Split(kMethods, "-")
End Function

Private Function getAllProperties() As String
   Static nProp As Integer
   Dim i As Integer
   
   nProp = 0
   For i = 1 To kTotalProps 'kUserProps
      GetProperty
      If i <= kUserProps Then
         If gPropInfo.Name = "Bitmap ID" And ResourceId = obj.IdNo Then gPropInfo.Val = 0
         If gPropInfo.Name = "Picture" Then
           getAllProperties = getAllProperties & gPropInfo.Name & "=" & GetRelativePath(gTarget.pathname, gPropInfo.Val) & ","
         Else
            getAllProperties = getAllProperties & gPropInfo.Name & "=" & gPropInfo.Val & ","
         End If
      End If
   Next
   
End Function
