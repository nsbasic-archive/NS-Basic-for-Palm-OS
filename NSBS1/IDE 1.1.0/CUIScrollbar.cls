VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIScrollbar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Member0" ,"Selector"
Option Explicit

Public obj As New CUIObject
Private m_nValue As Integer
Private m_nMinValue As Integer
Private m_nMaxValue As Integer
Private m_nPageSize As Integer

'Version 2 differs from V1 by removing the unused
'Visible and Hilighted
Private Const kVersion As Integer = 2
'3000 marks beginning of CUIScrollbar string table entries
Private Const kResStrings As Integer = 3000
Private Const kErrStrings As Integer = 3050
Private Const kUserProps As Integer = 4
Private Const kTotalProps As Integer = 12
Private Const kProperties As String = "Value-Min-Max-PageSize-Left-Top-Width-Height"
Private Const kMethods As String = "Hide-Show-Redraw"

Private Sub class_initialize()
   obj.Parent = Me
   obj.name = "Scrollbar"
   obj.Kind = "scr"
   obj.Width = 7
   obj.Height = 100
   m_nValue = 0
   m_nMinValue = 0
   m_nMaxValue = 1
   m_nPageSize = 1
End Sub

Public Sub PrcOut()
Dim c As Byte
Dim scr As scrollbarOut

   scr.id.w = cvtWord(obj.IdNo)
   scr.bounds.topleft.x = cvtWord(obj.OrigLeft)
   scr.bounds.topleft.y = cvtWord(obj.OrigTop)
   scr.bounds.extent.x = cvtWord(obj.Width)
   scr.bounds.extent.y = cvtWord(obj.Height)
   If obj.Usable Then
      scr.attr = &H80
   Else
      scr.attr = 0
   End If
   scr.Value = cvtWord(m_nValue)
   scr.MinValue = cvtWord(m_nMinValue)
   scr.MaxValue = cvtWord(m_nMaxValue)
   scr.PageSize = cvtWord(m_nPageSize)
   scr.penPosInCar = 0
   scr.savePos = 0
  
   c = &HD
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   Put #9, , scr
End Sub

Public Sub Restore()
Dim version As Integer
Dim bOld1 As Boolean, bOld2 As Boolean

   Input #1, version
   If version > kVersion Then
      MsgBox gStringTable(3300) + version '"Error: Invalid Scrollbar Version (" & version & ")"
      End
   End If

   Select Case version
   Case 1
      Input #1, m_nValue, m_nMinValue, m_nMaxValue, m_nPageSize, bOld1, bOld2
   Case kVersion
      Input #1, m_nValue, m_nMinValue, m_nMaxValue, m_nPageSize
   End Select
   obj.Restore
End Sub

Public Sub Save()
   Write #1, obj.Kind
   Write #1, kVersion
   Write #1, Value, MinValue, MaxValue, PageSize
   obj.Save
End Sub

Public Function Copy() As String
Dim temp As String

   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   temp = Join(Array(Value, MinValue, MaxValue, PageSize), ",")
   Copy = Copy + temp + vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "scr" Then
      MsgBox gStringTable(3301) '"Invalid paste: Scrollbar Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3302) '"Invalid paste: Scrollbar Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   Value = tokens(0)
   MinValue = tokens(1)
   MaxValue = tokens(2)
   PageSize = tokens(3)

   'Remove used code and paste inherited object
   For i = 4 To UBound(strLines)
      strLines(i - 3) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 3)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
Dim i As Integer, h As Integer, w As Integer

   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw False
   obj.Control.BackColor = getUIColorTable(1)
   obj.Control.ForeColor = getUIColorTable(2)

   'Control specific drawing/text here
'George: Make this MagFactor-savvy
   'draw upper triangle
   w = obj.Control.Width
   If w Mod 2 = 0 Then w = w - 1
   h = obj.Control.Height
   For i = 1 To w / 2
      obj.Control.Line (w / 2 - i, i)-(w / 2 + i, i)
   Next
   'draw bar
   obj.Control.Line (w \ 4, w \ 2 + 2)-(3 * w / 4, h - w / 2), getUIColorTable(0), BF
   'draw bottom triangle
   For i = 0 To (w / 2) - 1
      obj.Control.Line (w / 2 - i, h - i)-(w / 2 + i, h - i)
   Next
   obj.DrawSelected
End Sub

Public Property Let PageSize(ByVal vData As Integer)
   m_nPageSize = vData
End Property

Public Property Get PageSize() As Integer
   PageSize = m_nPageSize
End Property

Public Property Let MaxValue(ByVal vData As Integer)
   m_nMaxValue = vData
End Property

Public Property Get MaxValue() As Integer
   MaxValue = m_nMaxValue
End Property

Public Property Let MinValue(ByVal vData As Integer)
   m_nMinValue = vData
End Property

Public Property Get MinValue() As Integer
   MinValue = m_nMinValue
End Property

Public Property Let Value(ByVal vData As Integer)
   m_nValue = vData
End Property

Public Property Get Value() As Integer
   Value = m_nValue
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
      gPropInfo.name = "Maximum"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
   Case 1
      gPropInfo.name = "Minimum"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
   Case 2
      gPropInfo.name = "Page Size"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
   Case 3
      gPropInfo.name = "Value"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
   Case kUserProps + 0: obj.GetProperty "(Name)"
   Case kUserProps + 1: obj.GetProperty "Type"
   Case kUserProps + 2: obj.GetProperty "ID"
   Case kUserProps + 3: obj.GetProperty "Left"
   Case kUserProps + 4: obj.GetProperty "Top"
   Case kUserProps + 5: obj.GetProperty "Width"
   Case kUserProps + 6: obj.GetProperty "Height"
   Case kUserProps + 7: obj.GetProperty "Visible"
   End Select
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Maximum": GetPropertyVal = MaxValue
   Case "Minumum": GetPropertyVal = MinValue
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
   Case "Minumum"
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

