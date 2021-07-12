VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIGrid"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
'this entire class module new on 09042003
Public obj As New CUIObject
Public m_nVisibleRows As Integer
Public m_nCols As Integer
Public m_bHasScrollbar As Boolean
'private colwidth(101) As Integer

Private Const kVersion As Integer = 2
Private Const kUserProps As Integer = 3
Private Const kTotalProps As Integer = 13
Private Const kProperties As String = "Left-Top-Width-Height-Col-Cols-ColWidth-Row-RowData-Rows-Text-Value-TopRow"
Private Const kMethods As String = "Add-Clear-Hide-Redraw-Remove-Show-" _
   & "ColType-TextMatrix-ValueMatrix-FontMatrix-ShowGridLines-HideGridLines-BindToDatabase"

Private Sub class_initialize()
    Dim i As Integer
     obj.Parent = Me
     obj.name = "Grid" '+ Trim(str(obj.IdNo))
     obj.Kind = "grd"
     m_bHasScrollbar = False
     'For i = 0 To 100
     '   ColumnWidth(i) = 10
     'Next
     m_nVisibleRows = 2
     obj.Height = m_nVisibleRows * 12
     
     m_nCols = 2
     obj.Width = m_nCols * 25
End Sub
Public Sub PrcOut()
'several mods to this code 09242003
   Dim tbl As tableOut
   Dim c As Byte
   Dim ccc As tableColAttr
   Dim rrr As tableRowAttr
   Dim i As Integer
   Dim totwidth As Integer
   Dim templen As Integer
   Dim scr As scrollbarOut
   
    c = &H3
    Put #8, , c
    c = &H0
    Put #8, , c
    wordBound (9)
    outLong 8, Loc(9)
   tbl.id.w = cvtWord(obj.IdNo)
   tbl.bounds.topleft.x = cvtWord(obj.OrigLeft)
   tbl.bounds.topleft.y = cvtWord(obj.OrigTop)
   tbl.bounds.extent.x = cvtWord(obj.Width)
   tbl.bounds.extent.y = cvtWord(obj.Height)
   tbl.attr = &H44  'editable and usable
   If m_bHasScrollbar = True Then tbl.attr = tbl.attr Or &H8
   tbl.filler1 = &H0
   tbl.numColumns.w = cvtWord(m_nCols)
   tbl.numRows.w = cvtWord(m_nVisibleRows)
   tbl.currentRow.w = 0
   tbl.currentColumn.w = 0
   tbl.topRow.w = 0
   tbl.colAttrs.c = 0
   tbl.rowAttrs.c = 0
   tbl.Items.c = 0
   tbl.currentField.c = 0
   
   Put #9, , tbl
   c = &H0
   For i = 1 To 36
     Put #9, , c
   Next
   totwidth = 0
   If m_nCols = 0 Then
       m_nCols = 1
   End If
   ccc.Width.w = cvtWord((obj.Width - 1 * m_nCols) / m_nCols)
   ccc.flag1 = &H1
   ccc.flag2 = &H0
   ccc.spacing.w = cvtWord(1)
   ccc.drawCallback.c = 0
   ccc.loadData.c = 0
   ccc.saveData.c = 0
   
   'output column attrs
   For i = 1 To m_nCols
      If i <> m_nCols Then
           totwidth = totwidth + (obj.Width - 1 * m_nCols) / m_nCols
      Else
          ccc.Width.w = cvtWord(obj.Width - totwidth - 1 * m_nCols)
      End If
      Put #9, , ccc
   Next
   
   'output row attr's
   rrr.id.w = 0
   rrr.Height.w = cvtWord(11)
   rrr.data.d = 0
   rrr.flag1 = &H1
   rrr.flag2 = &H1
   rrr.Reserved.w = 0
   For i = 1 To m_nVisibleRows
       Put #9, , rrr
   Next
   
   c = &H0
   For i = 1 To m_nVisibleRows * m_nCols * 8
      Put #9, , c
   Next
   
   'write length of all addt'l data
   templen = 36 + m_nCols * 18 + m_nVisibleRows * 12 + m_nVisibleRows * m_nCols * 8
   Put #6, , templen
   
   If m_bHasScrollbar = True Then
      'put out a scrollbar too with one higher idno
      scr.id.w = cvtWord(obj.IdNo + 1)
      scr.bounds.topleft.x = cvtWord(obj.OrigLeft + obj.Width + 3)
      scr.bounds.topleft.y = cvtWord(obj.OrigTop)
      scr.bounds.extent.x = cvtWord(7)
      scr.bounds.extent.y = cvtWord(obj.Height)
      scr.attr = &H80
      'If mvarVisible = True Then scr.attr = scr.attr Or &H40
      scr.attr = scr.attr Or &H40 '4.25.2000
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
Public Property Let HasScrollbar(ByVal vData As Boolean)
    m_bHasScrollbar = vData
End Property
Public Property Get HasScrollbar() As Boolean
    HasScrollbar = m_bHasScrollbar
End Property
Public Property Let Cols(ByVal vData As Integer)
   m_nCols = vData
End Property
Public Property Get Cols() As Integer
   Cols = m_nCols
End Property
Public Property Let VisibleRows(ByVal vData As Integer)
   m_nVisibleRows = vData
End Property
Public Property Get VisibleRows() As Integer
   VisibleRows = m_nVisibleRows
End Property
Public Sub Restore()
  Dim i As Integer
  
  Dim version As Integer
  Input #1, version
  
   If version <> kVersion Then
      MsgBox gStringTable(3392) + str(version) '"Error: Invalid Grid Version " & version & ")"
      End
   End If
   
   Input #1, m_nVisibleRows, m_nCols, m_bHasScrollbar
     
     'For i = 1 To mvarColumns
     '   Input #1, mvarColumnWidth(i)
     'Next
   obj.Restore
End Sub
Public Sub Save()
  Dim version As Integer
  Dim i As Integer
  version = 2
  Write #1, obj.Kind
  Write #1, version
  Write #1, m_nVisibleRows, m_nCols, m_bHasScrollbar
      
  'For i = 1 To m_nCols
  '   Write #1, colwidth(i)
  'Next
  obj.Save
End Sub


Public Sub ScreenDraw()
Dim x As Integer, y As Integer
Dim w As Integer, h As Integer
   
   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw True
   obj.Control.BackColor = getUIColorTable(1)
   obj.Control.ForeColor = getUIColorTable(2)

   'Control specific drawing/text here
   obj.Control.DrawWidth = 1
   
   'draw row bounds
   h = obj.Control.Height \ m_nVisibleRows
   For y = 1 To m_nVisibleRows - 1
      obj.Control.Line (0, y * h)-(obj.Control.Width, y * h), vbGrayText, BF
   Next
   
   'draw col bounds
   w = obj.Control.Width \ m_nCols
   For x = 1 To m_nCols - 1
      obj.Control.Line (x * w, 0)-(x * w, obj.Control.Height), vbGrayText, BF
   Next

   obj.DrawSelected
End Sub
Public Sub GetProperty()
Static nProp As Integer

   If nProp = kTotalProps Then
      gPropInfo.name = ""
      nProp = 0
      Exit Sub
   End If

   gPropInfo.Val = ""
   If nProp < kUserProps Then gPropInfo.Type = pgBoolean
'Must be readonly to uncheck leftjustified
   Select Case nProp
   Case 0:
      gPropInfo.name = "Cols"
      gPropInfo.Type = pgString
   Case 1: gPropInfo.name = "Has Scrollbar"
   Case 2:
      gPropInfo.name = "Visible Rows"
      gPropInfo.Type = pgString
   Case kUserProps + 0: obj.GetProperty "(Name)"
   Case kUserProps + 1: obj.GetProperty "Type"
   Case kUserProps + 2: obj.GetProperty "ID"
   Case kUserProps + 3: obj.GetProperty "Left"
   Case kUserProps + 4: obj.GetProperty "Top"
   Case kUserProps + 5: obj.GetProperty "Width"
   Case kUserProps + 6: obj.GetProperty "Height"
   'Case kUserProps + 7: obj.GetProperty "Visible"
   'Case kUserProps + 8: obj.GetProperty "Font ID"
   Case kUserProps + 7: obj.GetProperty "Nav Flags"
   Case kUserProps + 8: obj.GetProperty "Nav Above ID"
   Case kUserProps + 9: obj.GetProperty "Nav Below ID"
   End Select
   If nProp < kUserProps Then gPropInfo.Val = GetPropertyVal(gPropInfo.name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Cols": GetPropertyVal = Cols
   Case "Has Scrollbar": GetPropertyVal = HasScrollbar
   Case "Visible Rows": GetPropertyVal = VisibleRows
   Case Else: GetPropertyVal = obj.GetPropertyVal(strProp)
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim n As Double

   ValidateProperty = True
   Select Case strProp
   Case "Has Scrollbar": HasScrollbar = strVal
   Case "Cols"
      n = Val(strVal)
      If n < 1 Or n > 32767 Then
         MsgBox gStringTable(3392), vbCritical + vbOKOnly 'Maximum VisibleRows/cols must be between 1 and 32767
         ValidateProperty = False
         n = 4
      End If
      Cols = n
   Case "Visible Rows"
      n = Val(strVal)
      If n <= 0 Or n > 32767 Then
         MsgBox gStringTable(3392), vbCritical + vbOKOnly 'Maximum VisibleRows/cols must be between 1 and 32767
         ValidateProperty = False
         n = 4
      End If
      VisibleRows = n
      obj.Parent = Me
      obj.Height = n * 12
   Case Else: ValidateProperty = obj.ValidateProperty(strProp, strVal)
   End Select
End Function
Public Function Copy() As String
Dim temp As String

   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   temp = Join(Array(str(Cols), BoolStr(HasScrollbar), str(VisibleRows)), ",")
   Copy = Copy + temp + vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "grd" Then
      MsgBox gStringTable(3393) '"Invalid paste: Grid Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3394) '"Invalid paste: Grid Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   Cols = Val(tokens(0))
   HasScrollbar = UnBoolStr(tokens(1))
   VisibleRows = Val(tokens(2))

   'Remove used code and paste inherited object
   For i = 4 To UBound(strLines)
      strLines(i - 3) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 3)
   obj.Paste strLines
End Sub
 
Public Function PropertyList() As String()
   PropertyList = Split(kProperties, "-")
End Function

Public Function MethodList() As String()
   MethodList = Split(kMethods, "-")
End Function

