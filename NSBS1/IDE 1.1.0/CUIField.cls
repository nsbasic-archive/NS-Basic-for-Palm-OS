VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIField"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Attribute VB_Ext_KEY = "Member0" ,"UIBitmap"
Option Explicit

Public obj As New CUIObject
Private m_bEditable As Boolean
Private m_bUnderline As Boolean
Private m_bSingleLine As Boolean
Private m_bDynamicSize As Boolean
Private m_bLeftJustified As Boolean
Private m_nMaxCharacters As Integer
Private m_bAutoShift As Boolean
Private m_bHasScrollbar As Boolean
Private m_bNumeric As Boolean
Private m_nScrollbarID As Integer

Private Const kVersion As Integer = 1
'2800 marks beginning of CUIField string table entries
Private Const kResStrings As Integer = 2800
Private Const kErrStrings As Integer = 2850
Private Const kUserProps As Integer = 9
Private Const kTotalProps As Integer = 21
Private Const kProperties As String = "Text-MaxChars-Left-Top-Width-Height"
Private Const kMethods As String = "Hide-Show-Redraw-SetFocus"

Private Sub class_initialize()
   obj.Parent = Me
   obj.Name = "Field"
   obj.Kind = "fld"
   obj.Width = 50
   m_bEditable = True
   m_bUnderline = True
   m_bSingleLine = True
   m_bDynamicSize = False
   m_bLeftJustified = True
   m_nMaxCharacters = 80
   m_bAutoShift = False
   m_bHasScrollbar = False
   m_bNumeric = False
   m_nScrollbarID = 0
End Sub

Public Sub PrcOut()
Dim c As Byte
Dim fld As FieldOut
Dim scr As scrollbarOut
Dim templen As Integer

   fld.id.w = cvtWord(obj.IdNo)
   fld.RECT.topleft.x = cvtWord(obj.OrigLeft)
   fld.RECT.topleft.y = cvtWord(obj.OrigTop)
   fld.RECT.extent.x = cvtWord(obj.Width)
   fld.RECT.extent.y = cvtWord(obj.Height)

   fld.attr1 = &H42 'visible, insertion pt visible
   If obj.Usable = True Then fld.attr1 = fld.attr1 Or &H80
   If m_bEditable Then fld.attr1 = fld.attr1 Or &H20
   If m_bSingleLine Then fld.attr1 = fld.attr1 Or &H10
   If m_bDynamicSize Then fld.attr1 = fld.attr1 Or &H4

   fld.attr2 = &H0
   If m_bUnderline Then fld.attr2 = fld.attr2 Or &H40
   If Not m_bLeftJustified Then fld.attr2 = fld.attr2 Or &H20
   If m_bAutoShift Then fld.attr2 = fld.attr2 Or &H8
   If m_bHasScrollbar Then fld.attr2 = fld.attr2 Or &H4
   If m_bNumeric Then fld.attr2 = fld.attr2 Or &H2

   fld.Text.c = 0
   fld.textHandle.h = 0
   fld.lines.l = 0
   fld.textLen.w = 0
   fld.textBlockSize.w = 0
   fld.MaxCharacters.w = cvtWord(m_nMaxCharacters)
   fld.selFirstPos.w = 0
   fld.selLastPos.w = 0
   fld.insPtXPos.w = 0
   fld.insPtYPos.w = 0
   fld.font = obj.FontID
   c = &H0
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   Put #9, , fld
   
   If m_bHasScrollbar = True Then
      'put out a scrollbar too with one higher idno
      scr.id.w = cvtWord(obj.IdNo + 1)
      scr.bounds.topleft.x = cvtWord(obj.OrigLeft + obj.Width)
      scr.bounds.topleft.y = cvtWord(obj.OrigTop - 1)
      scr.bounds.extent.x = cvtWord(7)
      scr.bounds.extent.y = cvtWord(obj.Height)
      scr.attr = &H80
      'If mvarVisible = True Then scr.attr = scr.attr Or &H40
      'If mvarHilighted = True Then scr.attr = scr.attr Or &H20
      scr.Value = 0
      scr.MinValue = cvtWord(0)
      scr.MaxValue = cvtWord(10)
      scr.PageSize = cvtWord(1)
      scr.penPosInCar = 0
      scr.savePos = 0

      c = &HD
      Put #8, , c
      c = &H0
      Put #8, , c
      wordBound (9)
      outLong 8, Loc(9)

      Put #9, , scr
   End If
End Sub

Public Sub Restore()
Dim version As Integer
   
   Input #1, version
   If version <> kVersion Then
      MsgBox gStringTable(3279) + version '"Error: Invalid Field Version (" & version & ")"
      End
   End If

   Input #1, m_bEditable, m_bUnderline, m_bSingleLine, m_bDynamicSize, _
      m_bLeftJustified, m_nMaxCharacters, m_bAutoShift, m_bHasScrollbar, m_bNumeric
   obj.Restore
End Sub

Public Sub Save()
   Write #1, obj.Kind
   Write #1, kVersion
   Write #1, Editable, Underline, SingleLine, DynamicSize, LeftJustified, _
      MaxCharacters, AutoShift, HasScrollbar, Numeric
   obj.Save
End Sub

Public Function Copy() As String
Dim temp As String

   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   temp = Join(Array(BoolStr(Editable), BoolStr(Underline), BoolStr(SingleLine), _
      BoolStr(DynamicSize), BoolStr(LeftJustified), MaxCharacters, BoolStr(AutoShift), _
      BoolStr(HasScrollbar), BoolStr(Numeric)), ",")
   Copy = Copy + temp + vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "fld" Then
      MsgBox gStringTable(3280) '"Invalid paste: Field Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3281) '"Invalid paste: Field Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   Editable = UnBoolStr(tokens(0))
   Underline = UnBoolStr(tokens(1))
   SingleLine = UnBoolStr(tokens(2))
   DynamicSize = UnBoolStr(tokens(3))
   LeftJustified = UnBoolStr(tokens(4))
   MaxCharacters = tokens(5)
   AutoShift = UnBoolStr(tokens(6))
   HasScrollbar = UnBoolStr(tokens(7))
   Numeric = UnBoolStr(tokens(8))

   'Remove used code and paste inherited object
   For i = 4 To UBound(strLines)
      strLines(i - 3) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 3)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
Dim i As Integer
Dim nolines As Integer
Dim line As String

   If obj.Control Is Nothing Then Exit Sub
   If Editable Then
      obj.Control.BackColor = getUIColorTable(10)
      obj.Control.ForeColor = getUIColorTable(11)
   Else
      obj.Control.BackColor = getUIColorTable(1)
      obj.Control.ForeColor = getUIColorTable(2)
   End If
   obj.ScreenDraw False

   'Control specific drawing/text here

   If m_bSingleLine Then
      nolines = 1
   Else
      If gbWinNT2000 Or gbPlainText Then
         nolines = obj.Height * obj.Control.Parent.MagFactor / (obj.Control.TextHeight("?") + 2)
      Else
         nolines = obj.Height / (obj.Control.TextHeight("?") + 2)
      End If
   End If

   line = ""
   While obj.Control.TextWidth(line) < obj.Width * obj.Control.Parent.MagFactor
      If m_bUnderline Then line = line + "_" Else line = line + "."
   Wend

   obj.Control.CurrentX = 0
   For i = 0 To nolines - 1
      If gbWinNT2000 Or gbPlainText Then
         obj.Control.CurrentY = i * obj.Control.TextHeight("X")
      Else
         obj.Control.CurrentY = i * obj.Control.TextHeight("X") * obj.Control.Parent.MagFactor
      End If
      obj.Control.Print line, getUIColorTable(12)
   Next
   obj.Control.CurrentX = 2
   obj.Control.CurrentY = 0
   obj.Control.Print "<" & obj.Name & ">"
   obj.DrawSelected
End Sub

Public Property Let HasScrollbar(ByVal vData As Boolean)
   m_bHasScrollbar = vData
End Property

Public Property Get HasScrollbar() As Boolean
   HasScrollbar = m_bHasScrollbar
End Property

Public Property Let AutoShift(ByVal vData As Boolean)
   m_bAutoShift = vData
End Property

Public Property Get AutoShift() As Boolean
   AutoShift = m_bAutoShift
End Property

Public Property Let MaxCharacters(ByVal vData As Integer)
   m_nMaxCharacters = vData
End Property

Public Property Get MaxCharacters() As Integer
   MaxCharacters = m_nMaxCharacters
End Property

Public Property Let LeftJustified(ByVal vData As Boolean)
   m_bLeftJustified = vData
End Property

Public Property Get LeftJustified() As Boolean
   LeftJustified = m_bLeftJustified
End Property

Public Property Let DynamicSize(ByVal vData As Boolean)
   m_bDynamicSize = vData
End Property

Public Property Get DynamicSize() As Boolean
   DynamicSize = m_bDynamicSize
End Property

Public Property Let SingleLine(ByVal vData As Boolean)
   m_bSingleLine = vData
End Property

Public Property Get SingleLine() As Boolean
   SingleLine = m_bSingleLine
End Property

Public Property Let Underline(ByVal vData As Boolean)
   m_bUnderline = vData
End Property

Public Property Get Underline() As Boolean
   Underline = m_bUnderline
End Property

Public Property Let Editable(ByVal vData As Boolean)
   m_bEditable = vData
End Property

Public Property Get Editable() As Boolean
   Editable = m_bEditable
End Property

Public Property Let Numeric(ByVal vData As Boolean)
   m_bNumeric = vData
End Property

Public Property Get Numeric() As Boolean
   Numeric = m_bNumeric
End Property

Public Sub GetProperty()
Static nProp As Integer

   If nProp = kTotalProps Then
      gPropInfo.Name = ""
      nProp = 0
      Exit Sub
   End If

   gPropInfo.Val = ""
   If nProp < kUserProps Then gPropInfo.Type = pgBoolean
'Must be readonly to uncheck leftjustified
   Select Case nProp
   Case 0: gPropInfo.Name = "Auto Shift"
   Case 1: gPropInfo.Name = "Dynamic Size"
   Case 2: gPropInfo.Name = "Editable"
   Case 3: gPropInfo.Name = "Has Scrollbar"
   Case 4: gPropInfo.Name = "Left Justified"
   Case 5 'Max Characters
      gPropInfo.Name = "Max Characters"
      gPropInfo.Type = pgString
   Case 6: gPropInfo.Name = "Numeric"
   Case 7: gPropInfo.Name = "Single Line"
   Case 8: gPropInfo.Name = "Underline"
   Case kUserProps + 0: obj.GetProperty "(Name)"
   Case kUserProps + 1: obj.GetProperty "Type"
   Case kUserProps + 2: obj.GetProperty "ID"
   Case kUserProps + 3: obj.GetProperty "Left"
   Case kUserProps + 4: obj.GetProperty "Top"
   Case kUserProps + 5: obj.GetProperty "Width"
   Case kUserProps + 6: obj.GetProperty "Height"
   Case kUserProps + 7: obj.GetProperty "Visible"
   Case kUserProps + 8: obj.GetProperty "Font ID"
   Case kUserProps + 9: obj.GetProperty "Nav Flags"
   Case kUserProps + 10: obj.GetProperty "Nav Above ID"
   Case kUserProps + 11: obj.GetProperty "Nav Below ID"
   End Select
   If nProp < kUserProps Then gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Auto Shift": GetPropertyVal = AutoShift
   Case "Dynamic Size": GetPropertyVal = DynamicSize
   Case "Editable": GetPropertyVal = Editable
   Case "Has Scrollbar": GetPropertyVal = HasScrollbar
   Case "Left Justified": GetPropertyVal = LeftJustified
   Case "Max Characters": GetPropertyVal = MaxCharacters
   Case "Numeric": GetPropertyVal = Numeric
   Case "Single Line": GetPropertyVal = SingleLine
   Case "Underline": GetPropertyVal = Underline
   Case Else: GetPropertyVal = obj.GetPropertyVal(strProp)
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim n As Double

   ValidateProperty = True
   Select Case strProp
   Case "Auto Shift": AutoShift = strVal
   Case "Dynamic Size"
      If strVal = True Then
         DynamicSize = True   '07/17/01 GH
         If HasScrollbar Then
            'A field cannot be sized dynamically with a scrollbar,
            'do you want to remove the scrollbar?
            If MsgBox(gStringTable(kErrStrings + 1), vbYesNo) = vbYes Then
               HasScrollbar = False
               DynamicSize = True
            Else
               HasScrollbar = True
               DynamicSize = False
            End If
         End If
         
      Else
         DynamicSize = False
      End If
   Case "Editable": Editable = strVal
   Case "Has Scrollbar":
      If strVal = True Then
         HasScrollbar = True    '07/17/01 GH
         If DynamicSize Then
            'A field cannot be sized dynamically with a scrollbar,
            'do you want to remove the scrollbar?
            If MsgBox(gStringTable(kErrStrings + 1), vbYesNo) = vbYes Then
               HasScrollbar = False
               DynamicSize = True
            Else
               HasScrollbar = True
               DynamicSize = False
            End If
         End If
         If SingleLine Then
            'A field must have multiple lines to use a scrollbar,
            'do you want to remove the scrollbar?
            If MsgBox(gStringTable(kErrStrings + 2), vbYesNo) = vbYes Then
               HasScrollbar = False
               SingleLine = True
            Else
               HasScrollbar = True
               SingleLine = False
            End If
         End If
      Else
         HasScrollbar = False
      End If
   Case "Left Justified": LeftJustified = strVal
   Case "Max Characters"
      n = Val(strVal)
      If n <= 0 Or n > 32767 Then
         MsgBox gStringTable(kErrStrings), vbCritical + vbOKOnly
         ValidateProperty = False
         n = 80
      End If
      MaxCharacters = n
   Case "Numeric": Numeric = strVal
   Case "Single Line"
      If strVal = True Then
         SingleLine = True      '07/17/01 GH
         If HasScrollbar Then
            'A field must have multiple lines to use a scrollbar,
            'do you want to remove the scrollbar?
            If MsgBox(gStringTable(kErrStrings + 2), vbYesNo) = vbYes Then
               HasScrollbar = False
               SingleLine = True
            Else
               HasScrollbar = True
               SingleLine = False
            End If
         End If
      Else
         SingleLine = False
      End If
   Case "Underline": Underline = strVal
   Case Else: ValidateProperty = obj.ValidateProperty(strProp, strVal)
   End Select
End Function

Public Function PropertyList() As String()
   PropertyList = Split(kProperties, "-")
End Function

Public Function MethodList() As String()
   MethodList = Split(kMethods, "-")
End Function

