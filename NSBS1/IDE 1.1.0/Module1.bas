Attribute VB_Name = "MStringTables"
Option Explicit

Sub LoadStringTable()
Dim message As String
Dim i As Integer
Dim chan As Integer
   
   chan = 98
   Open ProgramsDirectory & "\Lang\StrTable_English.txt" For Input As #chan
   
   For i = 0 To 4000
    gStringTable(i) = "String Table: " & i
   Next
   
   Do Until EOF(chan)
      Line Input #chan, message
      i = Val(Left(message, 4))
      gStringTable(i) = Mid(message, 6)
   Loop
   Close #chan
   
   If gLanguage <> "English" Then 'override English with other language
      On Error GoTo exitSub
      Open ProgramsDirectory & "\Lang\StrTable_" & gLanguage & ".txt" For Input As #chan
      On Error GoTo 0
      
      Do Until EOF(chan)
         Line Input #chan, message
         On Error GoTo skipIt
         If InStr(message, "//") Then
            message = Left(message, InStr(message, "//") - 1)
         End If
         i = Val(Left(message, 4))
         gStringTable(i) = Mid(message, 6)
skipIt:
      Loop
      Close #chan
   End If
exitSub:

End Sub
Sub LoadResStrings(frm As Form, Optional bLoadFont As Boolean = True)
Dim ctl As Control
Dim obj As Object
Dim fnt As Object
Dim sCtlType As String
Dim nVal As Integer

   On Error Resume Next
   
   'set the form's caption
   frm.caption = gStringTable(CInt(frm.Tag))
   
   'set the controls' captions using the caption
   'property for menu items and the Tag property
   'for all other controls
   For Each ctl In frm.Controls
      'If bLoadFont Then Set ctl.font = fnt
      ctl.fontName = gLabelFontName
      ctl.font.Charset = gLabelCharset
      If ctl.font.Size < gLabelFontSize Then ctl.font.Size = gLabelFontSize
      Select Case typename(ctl)
      Case "Label"
         ctl.caption = gStringTable(CInt(ctl.Tag))
      Case "Menu"
         ctl.caption = gStringTable(CInt(ctl.caption))
         ctl.Tag = ctl.caption
      Case "TabStrip"
         For Each obj In ctl.Tabs
            obj.caption = gStringTable(CInt(obj.Tag))
            obj.ToolTipText = gStringTable(CInt(obj.ToolTipText))
         Next
      Case "Toolbar"
         For Each obj In ctl.Buttons
            obj.ToolTipText = gStringTable(CInt(obj.ToolTipText))
         Next
      Case "ListView"
         For Each obj In ctl.ColumnHeaders
            obj.Text = gStringTable(CInt(obj.Tag))
         Next
      Case "TextBox"
         ctl.Text = gStringTable(CInt(ctl.Tag))
      Case Else
         nVal = 0
         nVal = Val(ctl.Tag)
         If nVal > 0 Then ctl.caption = gStringTable(nVal)
         nVal = 0
         nVal = Val(ctl.ToolTipText)
         If nVal > 0 Then ctl.ToolTipText = gStringTable(nVal)
      End Select
   Next
End Sub
