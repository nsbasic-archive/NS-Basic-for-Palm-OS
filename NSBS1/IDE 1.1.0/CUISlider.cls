VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUISlider"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
'added this entire module 04012005
Public obj As New CUIObject
Private mvarAnchorLeft As Boolean
Private mvarFrame As Boolean
Private mvarNonBoldFrame As Boolean
Public vertical As Boolean
Public minimum As Integer
Public maximum As Integer
Public m_nPageSize
Public m_nValue As Integer
Public thumbBitmapID As Integer
Public backgroundBitmapID As Integer

Private Const kVersion As Integer = 1
Private Const kResStrings As Integer = 3000
Private Const kErrStrings As Integer = 3050
Private Const kUserProps As Integer = 4
Private Const kTotalProps As Integer = 15
Private Const kProperties As String = "Min-Max-Value-PageSize"
Private Const kMethods As String = "Hide-Show-Redraw"

Private Sub class_initialize()
   obj.Parent = Me
   obj.name = "Slider" '+ Trim(str(obj.IdNo))
   obj.Width = 75
   'if (obj.OrigLeft+obj.width)*  magnific >
   obj.Label = obj.name
   obj.Kind = "sli"
   mvarAnchorLeft = False
   mvarFrame = False
   mvarNonBoldFrame = False
   vertical = False
   minimum = 0
   maximum = 100
   PageSize = 10
   Value = 0
   thumbBitmapID = 0
   backgroundBitmapID = 0
End Sub

Public Sub PrcOut()
Dim slider As SliderOut
Dim c As Byte
Dim templen As Integer
   
   slider.id.w = cvtWord(obj.IdNo)
   slider.bounds.topleft.x = cvtWord(obj.OrigLeft)
   slider.bounds.topleft.y = cvtWord(obj.OrigTop)
   slider.bounds.extent.x = cvtWord(obj.Width)
   slider.bounds.extent.y = cvtWord(obj.Height)
   slider.thumbID.w = cvtWord(thumbBitmapID)
   slider.backgroundID.w = cvtWord(backgroundBitmapID)
   slider.attribute1 = &H40   'usable enabled
   If obj.Usable = True Then slider.attribute1 = slider.attribute1 Or &H80

   slider.attribute1 = slider.attribute1 Or &H20 'visible = True
   slider.attribute2 = &H40
   If vertical = True Then slider.attribute2 = slider.attribute2 Or &H20
   slider.style = 6   'without feedback events
   'slider.style = 7    'with feedback events
   
   If mvarFrame = True Then
      If mvarNonBoldFrame = True Then
         slider.attribute1 = slider.attribute1 Or &H1
      Else
         slider.attribute1 = slider.attribute1 Or &H2
      End If
   End If
   
   slider.minimum.w = cvtWord(minimum)
   slider.maximum.w = cvtWord(maximum)
   slider.PageSize.w = cvtWord(PageSize)
   slider.Value.w = cvtWord(Value)
   slider.Reserved = &H0
   slider.activeSliderPtr.c = 0
   c = &HE
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   Put #9, , slider
   'templen = Len(obj.Label)
   'Put #6, , templen
   'Put #9, , obj.Label
   'c = &H0
   'Put #9, , c
End Sub

Public Sub Restore()
Dim version As Integer
  
   Input #1, version
   If version = 1 Then
      Input #1, _
               mvarAnchorLeft, _
               mvarFrame, _
               mvarNonBoldFrame, _
               vertical, _
               minimum, _
               maximum, _
               m_nPageSize, _
               m_nValue, _
               thumbBitmapID, _
               backgroundBitmapID
      obj.Restore
   Else
      MsgBox gStringTable(3416) + str(version) '"Error: Invalid Slider Version " & version & ")"
      End
   End If
End Sub

Public Sub Save()
Dim version As Integer
  
   version = 1
   Write #1, obj.Kind
   Write #1, version
   Write #1, _
            mvarAnchorLeft, _
            mvarFrame, _
            mvarNonBoldFrame, _
            vertical, _
            minimum, _
            maximum, _
            m_nPageSize, _
            m_nValue, _
            thumbBitmapID, _
            backgroundBitmapID
   obj.Save
End Sub

Public Function Copy() As String
Dim temp As String

   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   temp = Join(Array(mvarAnchorLeft, _
                                    mvarFrame, _
                                    mvarNonBoldFrame, _
                                    vertical, _
                                    minimum, _
                                    maximum, _
                                    m_nPageSize, _
                                    m_nValue, _
                                    thumbBitmapID, _
                                    backgroundBitmapID), ",")
   Copy = Copy + temp + vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "sli" Then
      MsgBox gStringTable(3418) '"Invalid paste: Slider Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3419) '"Invalid paste: Slider Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   mvarAnchorLeft = tokens(0)
   mvarFrame = tokens(1)
   mvarNonBoldFrame = tokens(2)
   vertical = tokens(3)
   minimum = tokens(4)
   maximum = tokens(5)
   m_nPageSize = tokens(6)
   m_nValue = tokens(7)
   thumbBitmapID = tokens(8)
   backgroundBitmapID = tokens(9)
   
   'Remove used code and paste inherited object
   For i = 4 To UBound(strLines)
      strLines(i - 3) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 3)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
Dim i As Integer
Dim h As Integer
Dim w As Integer
Dim wk As String
Dim rad As Integer

   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw False
   obj.Control.BackColor = getUIColorTable(1)
   obj.Control.ForeColor = getUIColorTable(2)
   'George: Make this MagFactor-savvy

   If obj.Width < obj.Height Then
      rad = obj.Width / 4
   Else
      rad = obj.Height / 4
   End If
   If mvarNonBoldFrame Then
      obj.Control.DrawWidth = 1
   Else
      obj.Control.DrawWidth = 2
   End If
   
   w = obj.Control.Width
   h = obj.Control.Height
   
   'horizontal lines
   obj.Control.Line (2, h / 2 - 4)-(w - 3, h / 2 - 4), getUIColorTable(0)
   obj.Control.Line (2, h / 2 - 0)-(w - 3, h / 2 - 0), getUIColorTable(0)
   obj.Control.Line (2, h / 2 + 4)-(w - 3, h / 2 + 4), getUIColorTable(0)
   
   'ends
   obj.Control.Line (1, h / 2 - 3)-(1, h / 2 + 3), getUIColorTable(0)
   obj.Control.Line (w, h / 2 - 3)-(w - 2, h / 2 + 3), getUIColorTable(0)
      
   'draw the carat
   obj.Control.Line (w / 3 + 0, h / 2 - 8)-(w / 3 + 0, h / 2 + 8), getUIColorTable(0) 'left vert
   obj.Control.Line (w / 3 + 8, h / 2 - 8)-(w / 3 + 8, h / 2 + 8), getUIColorTable(0) 'right vert
   obj.Control.Line (w / 3 + 1, h / 2 + 9)-(w / 3 + 7, h / 2 + 9), getUIColorTable(0) 'bottom
   obj.Control.Line (w / 3 + 1, h / 2 - 9)-(w / 3 + 7, h / 2 - 9), getUIColorTable(0) 'top
   
   'draw the gradiations
   For i = 0 To 10
      obj.Control.Line (1 + i * (w - 2) / 10, (h / 2) + 6)-(1 + i * (w - 2) / 10, (h / 2) + 8), getUIColorTable(0)
   Next
   
   obj.DrawSelected
End Sub

Public Property Let MinValue(ByVal vData As Integer)
    minimum = vData
End Property
Public Property Get MinValue() As Integer
    MinValue = minimum
End Property

Public Property Let MaxValue(ByVal vData As Integer)
    maximum = vData
End Property
Public Property Get MaxValue() As Integer
    MaxValue = maximum
End Property

Public Property Let Value(ByVal vData As Integer)
   m_nValue = vData
End Property
Public Property Get Value() As Integer
   Value = m_nValue
End Property

Public Property Let PageSize(ByVal vData As Integer)
   m_nPageSize = vData
End Property
Public Property Get PageSize() As Integer
   PageSize = m_nPageSize
End Property

Public Sub GetProperty()
Static nProp As Integer

   If nProp = kTotalProps Then
      gPropInfo.name = ""
      nProp = 0
      Exit Sub
   End If

   If nProp < kUserProps Then gPropInfo.Type = pgString
   Select Case nProp
   Case 0
      gPropInfo.name = "Minimum"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
      gPropInfo.Type = pgString
   Case 1
      gPropInfo.name = "Maximum"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
      gPropInfo.Type = pgString
   Case 2
      gPropInfo.name = "Page Size"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
      gPropInfo.Type = pgString
   Case 3
      gPropInfo.name = "Value"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
      gPropInfo.Type = pgString
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
   Case "Minimum": GetPropertyVal = minimum
   Case "Maximum": GetPropertyVal = maximum
   Case "Page Size": GetPropertyVal = PageSize
   Case "Value": GetPropertyVal = Value
   Case Else: GetPropertyVal = obj.GetPropertyVal(strProp)
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim n As Integer
Dim bmp As CBitmapFile
Dim frm As CForm
Dim o As Object

   ValidateProperty = True
   Select Case strProp
   'MMD: These numeric properties need some additional validation, especially Page Size
   Case "Maximum"
      n = Val(strVal)
      If MinValue > n Then
         MsgBox gStringTable(kErrStrings), vbCritical + vbOKOnly
         ValidateProperty = False
         Exit Function
      End If
      MaxValue = n
   Case "Minimum"
      n = Val(strVal)
      If MaxValue < n Then
         MsgBox gStringTable(kErrStrings), vbCritical + vbOKOnly
         ValidateProperty = False
         Exit Function
      End If
      MinValue = n
   Case "Page Size"
      n = Val(strVal)
      PageSize = n
   Case "Value"
      n = Val(strVal)
      If n < MinValue Or n > MaxValue Then
         MsgBox gStringTable(kErrStrings + 1), vbCritical + vbOKOnly
         ValidateProperty = False
         Exit Function
      End If
      Value = n
   Case Else: ValidateProperty = obj.ValidateProperty(strProp, strVal)
   End Select
   If ValidateProperty Then obj.Form.Project.Dirty = True
End Function

Public Function PropertyList() As String()
   PropertyList = Split(kProperties, "-")
End Function

Public Function MethodList() As String()
   MethodList = Split(kMethods, "-")
End Function

