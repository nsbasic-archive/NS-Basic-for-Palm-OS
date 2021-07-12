VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIObject"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'local variable(s) to hold property value(s)
Public NextObj As Object
Public PrevObj As Object
Private m_strKind As String
Private m_strName As String
Private m_nIdNo As Integer
Private m_nOrigLeft As Integer
Private m_nOrigTop As Integer
Private m_nHeight As Integer
Private m_nWidth As Integer
Private m_bUsable As Boolean
Private m_nFontId As Integer
Private m_strLabel As String
Private m_strScript As String
Private m_strSubName As String
Private m_nNavFlags As Integer     '10.16.06 GH Navigation
Private m_nNavAboveID As Integer   '10.16.06 GH Navigation
Private m_nNavBelowID As Integer  '10.16.06 GH Navigation
Public obj_code As String
Public obj_code_len As Long
Private m_Form As CForm
Private WithEvents m_Control As VB.PictureBox
Attribute m_Control.VB_VarHelpID = -1

Private m_Parent As Object
Public Selected As Boolean
Private m_nMousePointX As Integer
Private m_nMousePointY As Integer
Private m_nMouseHandle As Integer
Private m_bMoving As Boolean
Private m_bResize As Boolean

Private Const kVersion As Integer = 3
'2400 marks beginning of CUIObject string table entries
Private Const kResStrings As Integer = 2400
Private Const kErrStrings As Integer = 2450

Private Const kDragHandleSize As Integer = 3
Private Const kSelectBorderSize As Integer = 2

Private Sub class_initialize()
'   Set NextObj = Nil
'   Set PrevObj = Nil
   OrigLeft = 50
   OrigTop = 0
   Width = 12
   Height = 12
   Usable = True
   FontID = 0
   m_strKind = "obj"
   Name = "object"
   IdNo = 0
   script = ""
   '& IdNo
   m_strSubName = Name
   m_nNavFlags = 0
   m_nNavAboveID = 0
   m_nNavBelowID = 0

   obj_code = ""
   obj_code_len = 0
End Sub

Public Sub Restore()
Dim i As Integer
Dim temp As String
Dim version As Integer
Dim strname As String

   Input #1, temp 'reads 'obj' tag
   If Not temp = "obj" Then
      MsgBox gStringTable(3248) + temp '"Error: Invalid Object Type
   End If

   Input #1, version
   If version > kVersion Then
      MsgBox gStringTable(3249) + version '"Error: Invalid Object Version (" & version & ")"
      End
   End If

   If version >= 2 Then
      Input #1, m_strKind, strname, m_nIdNo, m_nOrigLeft, m_nOrigTop, _
         m_nHeight, m_nWidth, m_bUsable, m_nFontId, m_strLabel
      If version >= 3 Then
         Input #1, m_nNavFlags, m_nNavAboveID, m_nNavBelowID
      End If
      Input #1, m_strScript
      ProcessScript m_strScript, FromDisk
      'Set default name directly
      m_strName = "object" & IdNo
      m_strSubName = m_strName
      'Set actual name property
      Name = strname
   End If
End Sub

Public Sub Save()
Dim strTemp As String

   Write #1, "obj"
   Write #1, kVersion
   Write #1, Kind, Name, IdNo, OrigLeft, OrigTop, Height, Width, Usable, FontID, Label, _
      NavFlags, NavAboveID, NavBelowID
   strTemp = script
   ProcessScript strTemp, ToDisk
   Write #1, strTemp
End Sub

Public Function Copy() As String
Dim strTemp As String

   Copy = Quote("obj") + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   strTemp = Join(Array(Quote(Kind), Quote(Name), IdNo, OrigLeft, OrigTop, _
      Height, Width, BoolStr(Usable), FontID, NavFlags, NavAboveID, NavBelowID, Quote(Label)), ",")
   Copy = Copy & strTemp & vbCrLf
   strTemp = script
   ProcessScript strTemp, ToDisk
   Copy = Copy & Quote(strTemp) & vbCrLf
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i, nScriptEnd As Integer
Dim oldIdNo As Integer

   'Get obj and version
   If LCase(UnQuote(strLines(1))) <> "obj" Then
      MsgBox gStringTable(3250) '"Invalid paste: Object Type"
      End
   End If
   If Val(strLines(2)) <> kVersion Then
      MsgBox gStringTable(3251) '"Invalid paste: Object Version"
      End
   End If

   'Get properties
   tokens = Split(strLines(3), ",")
'   kind = UnQuote(tokens(0))
'   name = UnQuote(tokens(1))
   oldIdNo = tokens(2)
   OrigLeft = tokens(3) ' + (gnGridIncr \ 2)
   OrigTop = tokens(4) ' + (gnGridIncr \ 2)
   Height = tokens(5)
   Width = tokens(6)
   Usable = UnBoolStr(tokens(7))
   FontID = tokens(8)
   If UBound(tokens) > 12 Then '10.16.06 gh: Why this loop? I thought there was only 1 label?
      Label = tokens(12)
      For i = 13 To UBound(tokens)
         Label = Label & "," & tokens(i)
      Next
      Label = UnQuote(Label)
   Else
      Label = UnQuote(tokens(12))
   End If
   NavFlags = tokens(9)
   NavAboveID = tokens(10)
   NavBelowID = tokens(11)
   
   'Find end of script
   For i = 4 To UBound(strLines)
      If Right(strLines(i), 1) = Chr(34) Then
         nScriptEnd = i
         Exit For
      End If
   Next

   'Move script lines into tokens array for joining
   ReDim tokens(nScriptEnd - 4)
   For i = 0 To UBound(tokens)
      tokens(i) = strLines(i + 4)
   Next

   'Reconstitute script
   script = UnQuote(Join(tokens, vbCrLf))
   ProcessScript m_strScript, FromDisk
   script = Replace(m_strScript, "object" & oldIdNo, "object" & IdNo)

   'Remove used code then pass the rest on for pasting if anything remains
'   nScriptEnd = nScriptEnd
   For i = nScriptEnd + 1 To UBound(strLines)
      strLines(i - nScriptEnd) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - nScriptEnd)
End Sub

Public Sub PasteShift()
   OrigLeft = OrigLeft + (gnGridIncr \ 2)
   OrigTop = OrigTop + (gnGridIncr \ 2)
End Sub

Public Property Let Label(ByVal vData As String)
   m_strLabel = vData
End Property

Public Property Get Label() As String
'   If Len(m_strLabel) > 0 Then
      Label = m_strLabel
'   Else
'      Label = m_strName
'   End If
End Property

Public Property Let FontID(ByVal vData As Integer)
   m_nFontId = vData
End Property

Public Property Get FontID() As Integer
   FontID = m_nFontId
End Property

Public Property Let script(ByVal vData As String)
   m_strScript = vData
End Property

Public Property Get script() As String
   script = m_strScript
End Property

Public Property Get ScriptLen() As Long
   ScriptLen = Len(m_strScript)
End Property

Public Property Let Usable(ByVal vData As Boolean)
   m_bUsable = vData
End Property

Public Property Get Usable() As Boolean
   Usable = m_bUsable
End Property

Public Property Let Width(ByVal vData As Integer)
   m_nWidth = vData
   If m_nWidth < 0 Then m_nWidth = 0
End Property

Public Property Get Width() As Integer
   Width = m_nWidth
End Property

Public Property Let Height(ByVal vData As Integer)
   m_nHeight = vData
   If m_nHeight < 0 Then m_nHeight = 0
End Property

Public Property Get Height() As Integer
   Height = m_nHeight
End Property

Public Property Let OrigTop(ByVal vData As Integer)
'   If vData < 0 Then vData = 0
   'Subtract one to account for 160 pixel screen having pixels from 0 to 159
'   If Not m_Form Is Nothing Then
'      If vData + m_nHeight > m_Form.Height - 1 Then vData = m_Form.Height - m_nHeight
'   End If
   m_nOrigTop = vData
End Property

Public Property Get OrigTop() As Integer
   OrigTop = m_nOrigTop
End Property

Public Property Let OrigLeft(ByVal vData As Integer)
'   If vData < 0 Then vData = 0
   'Subtract one to account for 160 pixel screen having pixels from 0 to 159
'   If Not m_Form Is Nothing Then
'      If vData + m_nWidth > m_Form.Width - 1 Then vData = m_Form.Width - m_nWidth
'   End If
   m_nOrigLeft = vData
End Property

Public Property Get OrigLeft() As Integer
   OrigLeft = m_nOrigLeft
End Property

Public Property Let IdNo(ByVal vData As Integer)
   m_nIdNo = vData
   If m_nIdNo Then
      Name = Name & m_nIdNo
   End If
End Property

Public Property Get IdNo() As Integer
   IdNo = m_nIdNo
End Property

Public Property Let NavFlags(ByVal vData As Integer)
   m_nNavFlags = vData
   If m_nNavFlags < 0 Then m_nNavFlags = 0
End Property
Public Property Get NavFlags() As Integer
   NavFlags = m_nNavFlags
End Property

Public Property Let NavAboveID(ByVal vData As Integer)
   m_nNavAboveID = vData
   If m_nNavAboveID < 0 Then m_nNavAboveID = 0
End Property

Public Property Get NavAboveID() As Integer
   NavAboveID = m_nNavAboveID
End Property

Public Property Let NavBelowID(ByVal vData As Integer)
   m_nNavBelowID = vData
   If m_nNavBelowID < 0 Then m_nWidth = 0
End Property

Public Property Get NavBelowID() As Integer
   NavBelowID = m_nNavBelowID
End Property


Public Property Let Name(ByVal vData As String)
Dim strSubName As String

   'Verify name
   If Len(vData) = 0 Then Exit Property
   If InStr(1, vData, " ", vbTextCompare) > 0 Then Exit Property

   'Set name
   m_strName = vData

   'For initialization
'   If Kind = "obj" Then
'      Kind = LCase(m_strName)
'      Label = m_strName
'   End If

'   'Store old sub name to update script and set subname
'   strSubName = m_strSubName
'   m_strSubName = m_strName & "_Click"
'
'   'Update script with new sub name
'   If Len(m_strScript) > 0 Then
'      m_strScript = Replace(m_strScript, strSubName, m_strSubName, , , vbTextCompare)
'      'Next, replace all other occurences in project
'   End If
End Property

Public Property Get Name() As String
   Name = m_strName
End Property

Public Property Get SubName() As String
   SubName = m_strSubName
End Property
   
Public Property Get Kind() As String
   Kind = m_strKind
End Property

Public Property Let Kind(ByVal vData As String)
   m_strKind = vData
End Property

Public Property Get Form() As CForm
   Set Form = m_Form
End Property

Public Property Let Form(frm As CForm)
   Set m_Form = frm
End Property

Public Sub GetProperty(strProp As String)
   gPropInfo.Name = strProp
   'Use pgString as default, it is most common
   gPropInfo.Type = pgString

   Select Case strProp
   Case "(Name)"
   Case "Type": gPropInfo.Type = pgReadOnly
   Case "ID": gPropInfo.Type = pgReadOnly
   Case "Left"
   Case "Top"
   Case "Width"
   Case "Height"
   Case "Visible": gPropInfo.Type = pgBoolean
   Case "Font ID"
      gPropInfo.Type = pgNumlist
      gPropInfo.data = gStringTable(kResStrings)
   Case "Nav Flags"
   Case "Nav Above ID"
   Case "Nav Below ID"
   Case "Label"
   End Select
   gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "(Name)": GetPropertyVal = Name
   Case "Type"
      Select Case Kind
      Case "bmp": GetPropertyVal = "Form Bitmap"
      Case "but": GetPropertyVal = "Button"
      Case "chk": GetPropertyVal = "Checkbox"
      Case "cho", "pus": GetPropertyVal = "Pushbutton"
      Case "fld": GetPropertyVal = "Field"
      Case "gad": GetPropertyVal = "Gadget"
      Case "shf", "gsi": GetPropertyVal = "Graffiti Shift Indicator"
      Case "lbl": GetPropertyVal = "Label"
      Case "lst": GetPropertyVal = "List"
      Case "pop": GetPropertyVal = "Popup"
      Case "rpt": GetPropertyVal = "Repeater"
      Case "scr": GetPropertyVal = "Scrollbar"
      Case "sel": GetPropertyVal = "Selector"
      Case "grd": GetPropertyVal = "Grid"
      End Select
   Case "ID": GetPropertyVal = IdNo
   Case "Left": GetPropertyVal = OrigLeft
   Case "Top": GetPropertyVal = OrigTop
   Case "Width": GetPropertyVal = Width
   Case "Height": GetPropertyVal = Height
   Case "Visible": GetPropertyVal = Usable
   Case "Font ID": GetPropertyVal = FontID
   Case "Label": GetPropertyVal = Label
   Case "Nav Flags": GetPropertyVal = NavFlags
   Case "Nav Above ID": GetPropertyVal = NavAboveID
   Case "Nav Below ID": GetPropertyVal = NavBelowID
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim n As Double
Dim i As Integer
Dim frm As CForm
Dim obj As Object

   ValidateProperty = True
   Select Case strProp
   Case "(Name)"
      'Make sure name is unique within the project
      For Each frm In Form.Project.FormCollection
         For Each obj In frm.ObjectCollection
            If Not obj Is Parent Then
               If StrComp(obj.obj.Name, strVal, vbTextCompare) = 0 Then
                  MsgBox gStringTable(kErrStrings) & "'" & strVal & "'", vbCritical + vbOKOnly
                  ValidateProperty = False
                  Exit Function
               End If
            End If
         Next
      Next

      If Not LegalObjectName(strVal) Then
         ValidateProperty = False
         Exit Function
      End If

      Name = strVal
   Case "Type"
   Case "ID"
   'MMD: These four properties need some additional validation
   Case "Left"
      n = Val(strVal)
      If n < 0 Then n = 0
      If n > 1000 Then n = 1000
      OrigLeft = n
'     OrigLeft = Val(strVal)
   Case "Top"
      n = Val(strVal)
      If n < 0 Then n = 0
      If n > 1000 Then n = 1000
      OrigTop = n
'      OrigTop = Val(strVal)
   Case "Width"
      n = Val(strVal)
      If n < 0 Then n = 0
      If n > 1000 Then n = 1000
      Width = n
'      Width = Val(strVal)
   Case "Height"
      n = Val(strVal)
      If n > 1000 Then n = 1000
      If n < 0 Then n = 0
      Height = n
'      Height = Val(strVal)
   Case "Visible"
      Usable = strVal Like g_strTrue
   Case "Font ID"
      n = Val(strVal)
      If n < 0 Then n = 0
      If n > 1000 Then n = 1000
      FontID = n
   Case "Label"
      Label = ReplaceQuotes(strVal)
   Case "Nav Flags"
      i = Val(strVal)
      If i < 0 Then i = 0
      NavFlags = i
   Case "Nav Above ID"
      i = Val(strVal)
      If i < 0 Then i = 0
      If i > 0 And Object(i) Is Nothing Then i = 0
      NavAboveID = i
   Case "Nav Below ID"
      i = Val(strVal)
      If i < 0 Then i = 0
      If i > 0 And Object(i) Is Nothing Then i = 0
      NavBelowID = i

   End Select
   If ValidateProperty Then Form.Project.Dirty = True
End Function

Public Property Get GlobalID() As String
Attribute GlobalID.VB_UserMemId = 0
   GlobalID = Join(Array("object", IdNo, m_Form.GlobalID), "|")
End Property

Public Function GetScript(strScript As String, Optional bForceCreate As Boolean = True) As String
   If Len(m_strScript) > 0 Or Not bForceCreate Then
      GetScript = m_strScript
   Else
      GetScript = "Sub object" & IdNo & "()" & vbCrLf & vbCrLf & "End Sub"
   End If
End Function

Public Sub PutScript(ByVal strText As String, ByVal strScript As String)
   m_strScript = strText
   m_Form.Project.Dirty = True
End Sub

Public Property Get Control() As VB.PictureBox
   Set Control = m_Control
End Property

Public Property Let Control(ByVal pb As VB.PictureBox)
   Set m_Control = pb
   If Not m_Control Is Nothing Then m_Control.Visible = True
End Property

Public Property Get Parent() As Object
   Set Parent = m_Parent
End Property

Public Property Let Parent(ByVal obj As Object)
   Set m_Parent = obj
End Property

Private Sub m_Control_DblClick()
Dim fCode As New frmCode

   'm_Control.Tag = "1"
   m_Control.Refresh
   m_Control.Parent.ClearSelection
   frmMain.ViewCode GlobalID, "code"
End Sub

Private Function GetHandle(ByVal x As Integer, ByVal y As Integer)
Dim nMid As Integer
      
   nMid = m_Control.Width \ 2 - 2
   If x <= kDragHandleSize Then
      nMid = m_Control.Height \ 2 - 2
      If y <= kDragHandleSize Then 'NW
         GetHandle = 7
      ElseIf y >= nMid And y <= nMid + kDragHandleSize Then 'W
         GetHandle = 4
      ElseIf y >= m_Control.Height - (kDragHandleSize + 1) Then 'SW
         GetHandle = 1
      Else 'None
         GetHandle = 0
      End If
   ElseIf x >= nMid And x <= nMid + kDragHandleSize Then
      If y <= kDragHandleSize Or y >= m_Control.Height - (kDragHandleSize + 1) Then
         If y <= kDragHandleSize Then: GetHandle = 8: Else GetHandle = 2
      Else
         GetHandle = 0
      End If
   ElseIf x >= m_Control.Width - (kDragHandleSize + 1) Then
      nMid = m_Control.Height \ 2 - 2
      If y <= kDragHandleSize Then 'NE
         GetHandle = 9
      ElseIf y >= nMid And y <= nMid + kDragHandleSize Then 'E
         GetHandle = 6
      ElseIf y >= m_Control.Height - (kDragHandleSize + 1) Then 'SE
         GetHandle = 3
      Else 'None
         GetHandle = 0
      End If
   Else
      GetHandle = 0
   End If
End Function

Private Sub SetMousePointer(Optional ByVal nHandle As Integer = 0)
   Select Case nHandle
   Case 0: m_Control.MousePointer = vbDefault
   Case 7, 3: m_Control.MousePointer = vbSizeNWSE
   Case 8, 2: m_Control.MousePointer = vbSizeNS
   Case 9, 1: m_Control.MousePointer = vbSizeNESW
   Case 4, 6: m_Control.MousePointer = vbSizeWE
   End Select
End Sub

Private Sub m_Control_KeyUp(KeyCode As Integer, Shift As Integer)
   If Not Selected Then Exit Sub
   If Shift = 0 And KeyCode = 46 Then FormRemoveObject m_Control.Parent.Object, Me.Parent
End Sub

Private Sub m_Control_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
   If Not m_Control.Parent Is frmMain.ActiveForm Then m_Control.Parent.ZOrder
   If Button <> vbLeftButton Then Exit Sub

   If Shift And vbShiftMask Then
'      If Selected Then
'         m_Control.Parent.RemoveSelectionItem Parent
'      Else
'         m_Control.Parent.AddSelectionItem Parent
'      End If
      m_bMoving = False
      Exit Sub
   End If

   If Selected Then
      m_bMoving = False
   Else
      m_Control.Parent.SetSelection Parent
      m_bMoving = True
   End If
   m_nMousePointX = x
   m_nMousePointY = y
   m_nMouseHandle = GetHandle(x, y)
   SetMousePointer m_nMouseHandle
End Sub

Private Sub m_Control_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim nX As Integer, nY As Integer, n As Integer

   If Button = 0 Then
      m_nMousePointX = x
      m_nMousePointY = y
      If Not Selected Or m_Control.Parent.Selection.count > 1 Then
         SetMousePointer
      Else
         SetMousePointer GetHandle(x, y)
      End If
   ElseIf Button = vbLeftButton Then 'Moving with mouse down, either drag or resize
'      If Shift <> 0 Then Exit Sub
      nX = (x - m_nMousePointX) \ m_Control.Parent.MagFactor
      nY = (y - m_nMousePointY) \ m_Control.Parent.MagFactor
      If nX = 0 And nY = 0 Then Exit Sub
      m_bMoving = True
      If m_Control.Parent.Selection.count > 1 Then m_nMouseHandle = 0
      m_bResize = m_nMouseHandle <> 0
      Select Case m_nMouseHandle
      Case 0 'drag
         m_Control.Parent.MouseMoveSelection nX, nY, OrigLeft, OrigTop, , Shift
      Case 7 'NW Resize
         OrigLeft = OrigLeft + nX
         OrigTop = OrigTop + nY
         Width = Width - nX
         Height = Height - nY
      Case 8 'N Resize
         OrigTop = OrigTop + nY
         Height = Height - nY
      Case 4 'W Resize
         OrigLeft = OrigLeft + nX
         Width = Width - nX
      Case 9 'NE Resize
         OrigTop = OrigTop + nY
         Width = Width + nX
         Height = Height - nY
         m_nMousePointX = x
      Case 1 'SW Resize
         OrigLeft = OrigLeft + nX
         Width = Width - nX
         Height = Height + nY
         m_nMousePointY = y
      Case 6 'E Resize
         Width = Width + nX
         m_nMousePointX = x
      Case 3 'SE Resize
         Width = Width + nX
         Height = Height + nY
         m_nMousePointX = x
         m_nMousePointY = y
      Case 2 'S Resize
         Height = Height + nY
         m_nMousePointY = y
      End Select
      If OrigLeft < 0 Then OrigLeft = 0
      If OrigTop < 0 Then OrigTop = 0
      If OrigLeft + Width > m_Form.Width Then OrigLeft = m_Form.Width - Width
      If OrigTop + Height > m_Form.Height Then OrigTop = m_Form.Height - Height
      
      If m_Control.Parent.Selection.count = 1 Then
         ShowCoordinates OrigLeft, OrigTop
         ShowDimensions Width, Height
      End If
      m_Control.Refresh
      m_Form.Project.Dirty = True
   End If
End Sub

Private Sub m_Control_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
   If Button = vbRightButton Then
      If x < 0 Or y < 0 Or x > m_Control.Width Or y > m_Control.Height Then Exit Sub
'      If Shift <> 0 Then Exit Sub
      If Not Selected Then m_Control.Parent.AddSelectionItem Parent
      If Shift = vbShiftMask Or m_Control.Parent.Selection.count > 1 Then
         frmMain.PopupMenu frmMain.mnuFormat
      ElseIf Shift = 0 Then
         frmMain.RightClickMenu 1, GlobalID
      End If
   Else
      If m_bMoving Then
         If m_bResize Then
            m_Control.Parent.ResizeSelectionToGrid , Shift
         End If
         If gbProperties Then
            gfProperties.Object = Nothing
            m_Control.Parent.DisplaySelection
         End If
      Else
         If Selected Then
            m_Control.Parent.RemoveSelectionItem Parent
            m_Control.Parent.SetFocus
         Else
            If Shift And vbShiftMask Then m_Control.Parent.AddSelectionItem Parent
         End If
      End If
      m_nMousePointX = 0
      m_nMousePointY = 0
   End If
   ShowStatus
End Sub

Private Sub m_Control_Paint()
   'Each different parent type knows how it wants to be ScreenDraw'n
   Parent.ScreenDraw
End Sub

Public Sub ScreenDraw(bDrawBorder As Boolean)
Dim fontname As String
Dim fontSize As Integer
Dim nMag As Integer

   'Choose your font here
   fontname = gstrPalmFonts(m_nFontId)
   fontSize = gnPalmFontSize(m_nFontId)
   If gbPlainText Then fontname = gLabelFontName

   'First clear the object
   Control.Cls

   'Set object properties
   With Control
      nMag = Control.Parent.MagFactor
      .Left = OrigLeft * nMag
      .Top = OrigTop * nMag
      .Width = Width * nMag
      .Height = Height * nMag
      If Kind <> "bmp" Then
         .font.Name = fontname
         If gbWinNT2000 Or gbPlainText Then .fontSize = fontSize * nMag
      End If
      .font.Charset = gLabelCharset
   End With

   'Draw a line around the object if requested
   If bDrawBorder Then
      Control.DrawWidth = 1
      Control.DrawStyle = vbSolid
      Control.Line (0, 0)-(Control.Width - 1, Control.Height - 1), Control.ForeColor, B
   End If
End Sub

Public Sub DrawSelected()
Dim nMid As Integer

   If Not Selected Then Exit Sub
   Control.DrawWidth = 1
   Control.DrawStyle = vbDot
   Control.Line (kSelectBorderSize, kSelectBorderSize)-(Control.Width - (1 + kSelectBorderSize), Control.Height - (1 + kSelectBorderSize)), Control.ForeColor, B
   Control.DrawStyle = vbSolid
   Control.Line (0, 0)-(kDragHandleSize, kDragHandleSize), Control.ForeColor, BF
   Control.Line (0, Control.Height - (kDragHandleSize + 1))-(kDragHandleSize, Control.Height - 1), Control.ForeColor, BF
   Control.Line (Control.Width - (kDragHandleSize + 1), 0)-(Control.Width - 1, kDragHandleSize), Control.ForeColor, BF
   Control.Line (Control.Width - (kDragHandleSize + 1), Control.Height - (kDragHandleSize + 1))-(Control.Width - 1, Control.Height - 1), Control.ForeColor, BF
   nMid = Control.Height \ 2 - 2
   Control.Line (0, nMid)-(kDragHandleSize, nMid + kDragHandleSize), Control.ForeColor, BF
   Control.Line (Control.Width - (kDragHandleSize + 1), nMid)-(Control.Width - 1, nMid + kDragHandleSize), Control.ForeColor, BF
   nMid = Control.Width \ 2 - 2
   Control.Line (nMid, 0)-(nMid + kDragHandleSize, kDragHandleSize), Control.ForeColor, BF
   Control.Line (nMid, Control.Height - (kDragHandleSize + 1))-(nMid + kDragHandleSize, Control.Height - 1), Control.ForeColor, BF
End Sub
Public Property Get Object(nID As Integer) As Object
Dim obj As Object
Dim frm As CForm

For Each frm In Form.Project.FormCollection
   For Each obj In frm.ObjectCollection
      If obj.obj.IdNo = nID Then
         Set Object = obj
         Exit Property
      End If
   Next
Next
End Property
