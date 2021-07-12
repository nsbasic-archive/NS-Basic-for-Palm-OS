VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Member0" ,"UIPopup"
Option Explicit

Public obj As New CUIObject
Private m_nVisibleItems As Integer
Private m_Items As New Collection
Private m_strList As String
Private m_nRndSeed As Single

Private Const kVersion As Integer = 2
'2900 marks beginning of CUIList string table entries
Private Const kResStrings As Integer = 2900
Private Const kErrStrings As Integer = 2950
Private Const kUserProps As Integer = 2
Private Const kTotalProps As Integer = 13
Private Const kProperties As String = "ItemText-NoItems-Selected-Left-Top-Width"
Private Const kMethods As String = "Hide-Show-Redraw-Clear-Add-Remove"

Private Sub class_initialize()
   obj.Parent = Me
   obj.name = "List"
   obj.Kind = "lst"
   obj.Width = 40
   VisibleItems = 4
   m_nRndSeed = Rnd()
   m_strList = ""
End Sub

Public Sub PrcOut()
Dim cnt As Integer
Dim c As Byte
Dim i As Integer
Dim lst As listOut
Dim strTemp As String
Dim templen As Integer
Dim arrList() As String

   'Examine the list and make sure it contains enough items to satisy VisibleItems, padding with
   'a " " item where necessary
   arrList = Split(m_strList, vbTab)
   If UBound(arrList) + 1 < m_nVisibleItems Then
      ReDim Preserve arrList(m_nVisibleItems - 1)
      For i = UBound(arrList) To 0 Step -1
         If arrList(i) = "" Then
            arrList(i) = " "
         Else
            Exit For
         End If
      Next
   End If

   lst.id.w = cvtWord(obj.IdNo)
   lst.bounds.topleft.x = cvtWord(obj.OrigLeft)
   lst.bounds.topleft.y = cvtWord(obj.OrigTop)
   lst.bounds.extent.x = cvtWord(obj.Width)
   lst.bounds.extent.y = cvtWord(obj.Height)
   If obj.Usable Then
      lst.attr = &H80
   Else
      lst.attr = 0
   End If
   lst.itemsText.c = 0
   lst.numItems.w = cvtWord(UBound(arrList) + 1)
   lst.currentItem.w = 0
   lst.topItem.w = 0
   lst.font = obj.FontID  '??need cvtword
   lst.popupWin.h = 0
   lst.callback.c = 0
   c = &H2
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   Put #9, , lst
'   For Each s In Items   '//
'      c = &H0
'      For i = 1 To 4
'         Put #9, , c
'      Next
'   Next
   c = &H0
   For i = 0 To UBound(arrList)
      Put #9, , c
      Put #9, , c
      Put #9, , c
      Put #9, , c
   Next

'   cnt = m_Items.count
   cnt = UBound(arrList) + 1
   Put #6, , cnt
'   For Each s In m_Items
'      ss = s
'      templen = Len(ss)
'
'      Put #6, , templen
'      Put #9, , ss
'      c = &H0
'      Put #9, , c
'   Next
   c = &H0
   For i = 0 To UBound(arrList)
      strTemp = arrList(i)
      templen = Len(strTemp)
      Put #6, , templen
      Put #9, , strTemp
      Put #9, , c
   Next
End Sub

Public Sub Restore()
Dim version As Integer
Dim s As String

   Input #1, version
   If version > kVersion Then
      MsgBox gStringTable(3291) + version '"Error: Invalid List Version (" & version & ")"
      End
   End If

   Input #1, m_nVisibleItems
   If version > 1 Then
      Input #1, s
      ProcessScript s, FromDisk
      m_strList = s
   End If
   obj.Restore
End Sub

Public Sub Save()
Dim s As String
   
   Write #1, obj.Kind
   Write #1, kVersion
   Write #1, VisibleItems
   s = m_strList
   ProcessScript s, ToDisk
   Write #1, s
   obj.Save
End Sub

Public Function Copy() As String
   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   Copy = Copy & VisibleItems & vbCrLf
   Copy = Copy & m_strList & vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "lst" Then
      MsgBox gStringTable(3292) '"Invalid paste: List Type"
      End
   End If
   If strLines(2) > kVersion Then
      MsgBox gStringTable(3293) '"Invalid paste: List Version"
      End
   End If

   'Restore properties
   VisibleItems = strLines(3)
   m_strList = strLines(4)

   'Remove used code and paste inherited object
   For i = 5 To UBound(strLines)
      strLines(i - 4) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 4)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
Dim y As Integer

   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw True
   obj.Control.BackColor = getUIColorTable(1)
   obj.Control.ForeColor = getUIColorTable(2)

'   If gbWinNT2000 Or gbPlainText Then
'      obj.Height = (obj.Control.TextHeight("?") \ obj.Control.Parent.MagFactor) * VisibleItems
'   Else
'      obj.Height = obj.Control.TextHeight("?") * VisibleItems
'   End If
'
'   obj.ScreenDraw True

   'Control specific drawing/text here
   Rnd -1
   Randomize m_nRndSeed
   For y = 2 To obj.Control.Height - 3 Step 4
      obj.Control.Line (3, y)-(3 + Rnd * (obj.Control.Width - 3), y), getUIColorTable(0), B
      obj.Control.Line (3, y + 1)-(3 + Rnd(0) * (obj.Control.Width - 3), y + 1), getUIColorTable(0), B
   Next
   obj.DrawSelected
End Sub

Public Property Set Items(ByVal vData As Object)
   Set m_Items = vData
End Property

Public Property Get Items() As Collection
   Set Items = m_Items
End Property

Public Property Let VisibleItems(ByVal vData As Integer)
'George: VisibleItems dictates object height, via Palm Font stuff
   m_nVisibleItems = vData
   obj.Height = GetTextHeight("?", obj.FontID) * m_nVisibleItems
End Property

Public Property Get VisibleItems() As Integer
   VisibleItems = m_nVisibleItems
End Property

Public Sub GetProperty()
Static nProp As Integer

   If nProp = kTotalProps Then
      gPropInfo.name = ""
      nProp = 0
      Exit Sub
   End If

   gPropInfo.Val = ""
   Select Case nProp
   Case 0
      gPropInfo.name = "Visible Rows"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
      gPropInfo.Type = pgString
   Case 1
      gPropInfo.name = "List"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
      gPropInfo.Type = pgStringList
      gPropInfo.data = GetStringList
   Case kUserProps + 0: obj.GetProperty "(Name)"
   Case kUserProps + 1: obj.GetProperty "Type"
   Case kUserProps + 2: obj.GetProperty "ID"
   Case kUserProps + 3: obj.GetProperty "Left"
   Case kUserProps + 4: obj.GetProperty "Top"
   Case kUserProps + 5: obj.GetProperty "Width"
   Case kUserProps + 6: obj.GetProperty "Visible"
   Case kUserProps + 7: obj.GetProperty "Font ID"
   Case kUserProps + 8: obj.GetProperty "Nav Flags"
   Case kUserProps + 9: obj.GetProperty "Nav Above ID"
   Case kUserProps + 10: obj.GetProperty "Nav Below ID"
   End Select
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
Dim i As Integer
Dim strTemp As String

   Select Case strProp
   Case "Visible Rows": GetPropertyVal = VisibleItems
   Case "List"
      If m_strList = "" Then
         GetPropertyVal = "(Empty)"
      Else
         GetPropertyVal = "(" & (UBound(Split(m_strList, vbTab)) + 1) & " Items)"
      End If
   Case Else: GetPropertyVal = obj.GetPropertyVal(strProp)
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim n As Integer
Dim arrList() As String
Dim i As Integer
Dim j As Integer
Dim arrItems() As String

   ValidateProperty = True
   Select Case strProp
   Case "Visible Rows"
      n = Val(strVal)
      If n <= 0 Then
         MsgBox gStringTable(kErrStrings), vbCritical + vbOKOnly
         ValidateProperty = False
         Exit Function
      End If
      VisibleItems = n
   Case "List"
      If strVal = "" Then
         m_strList = strVal
      Else
         'List comes in as text, lets break it into lines and evaluate them
         arrItems = Split(strVal, vbCrLf)
         ReDim arrList(UBound(arrItems))
         j = 0
         For i = 0 To UBound(arrItems)
            If arrItems(i) <> "" Then
               arrList(j) = arrItems(i)
               j = j + 1
            End If
         Next
         ReDim Preserve arrList(j - 1)
         m_strList = Join(arrList, vbTab)
      End If
   Case Else: ValidateProperty = obj.ValidateProperty(strProp, strVal)
   End Select
   If ValidateProperty Then obj.Form.Project.Dirty = True
End Function

Public Function GetStringList() As String
   GetStringList = "List Items>" & Join(Split(m_strList, vbTab), vbCrLf)
End Function

Public Function PropertyList() As String()
   PropertyList = Split(kProperties, "-")
End Function

Public Function MethodList() As String()
   MethodList = Split(kMethods, "-")
End Function
