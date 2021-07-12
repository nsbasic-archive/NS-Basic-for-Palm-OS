VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "UITable"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Option Explicit

Public obj As UIObject
Private mvarRows As Integer
Private mvarColumns As Integer
Private mvarColumnWidth(26) As Integer
Private Sub class_initialize()
   'create the mUILabel object when the UIShiftIndic class is created
   Dim i As Integer

   Set obj = New UIObject
   obj.name = "Tbl" + Trim(str(obj.idno))
   obj.Label = obj.name
   obj.Kind = "tbl"
   For i = 0 To 25
      mvarColumnWidth(i) = 10
   Next
End Sub
Public Sub PrcOut()
   Dim tbl As tableOut
   Dim c As Byte

   '??set fields
   c = &H3
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   Put #9, , tbl
End Sub
Public Sub restore()
   Dim i As Integer
   Dim version As Integer

   Input #1, version
   If version = 1 Then
      Input #1, mvarRows, mvarColumns
      For i = 1 To mvarColumns
         Input #1, mvarColumnWidth(i)
      Next
      obj.restore
   Else
      MsgBox "error -- version " & version & " is invalid for 'UITable'"
      End
   End If
End Sub
Public Sub save()
   Dim version As Integer
   Dim i As Integer

   version = 1
   Write #1, obj.Kind
   Write #1, version
   Write #1, Rows, Columns
   For i = 1 To Columns
      Write #1, GetColumnWidth(i)
   Next
   obj.save
End Sub
Public Function Copy() As String
   Dim version As Integer
   Dim i As Integer

   version = 1
   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & version & vbCrLf
   Copy = Copy + Join(Array(Rows, Columns), ",") + vbCrLf
   For i = 1 To Columns
      Copy = Copy & GetColumnWidth(i) & vbCrLf
   Next
   Copy = Copy + obj.Copy()
End Function
Public Sub Paste(ByRef strLines() As String)
   Dim tokens() As String
   Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "tbl" Then
      MsgBox "Invalid paste: table type"
      End
   End If
   If strLines(2) <> 1 Then
      MsgBox "Invalid paste: table version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   Rows = tokens(0)
   Columns = tokens(1)
   For i = 1 To Columns
      SetColumnWidth i, strLines(3 + i)
   Next

   'Remove used code and paste inherited object
   For i = (4 + Columns) To UBound(strLines)
      strLines(i - (3 + Columns)) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - (3 + Columns))
   obj.Paste strLines
End Sub

Public Sub ScreenDraw(theForm As Form)
   Dim xul, xll, xur, xlr As Integer
   Dim yul, yll, yur, ylr As Integer
   
   theForm.DrawWidth = 1
   xul = theForm.OrigX + obj.OrigLeft * Magnific
   yul = theForm.OrigY + obj.OrigTop * Magnific
   xur = theForm.OrigX + (obj.OrigLeft + obj.Width) * Magnific
   yur = theForm.OrigY + obj.OrigTop * Magnific
   xll = xul
   yll = yul + obj.Height * Magnific
   xlr = xur
   ylr = yur + obj.Height * Magnific
   theForm.Line (xul, yul)-(xlr, ylr), theForm.BackColor, BF
   theForm.Line (xul, yul)-(xlr, ylr), vbBlack, B
End Sub

Public Property Let Columns(ByVal vData As Integer)
'Syntax: X.Columns = 5
   mvarColumns = vData
End Property
Public Property Get Columns() As Integer
   Columns = mvarColumns
End Property
Public Property Let Rows(ByVal vData As Integer)
   mvarRows = vData
End Property
Public Property Get Rows() As Integer
   Rows = mvarRows
End Property
Public Sub SetColumnWidth(iData As Integer, ByVal vData As Integer)
   mvarColumnWidth(iData) = vData
End Sub
Public Function GetColumnWidth(iData As Integer) As Integer
   GetColumnWidth = mvarColumnWidth(iData)
End Function
