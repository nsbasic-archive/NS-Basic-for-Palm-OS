VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIPopup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Member0" ,"UIChoicebox"
Option Explicit

Public obj As New CUIObject
Private m_bAnchorLeft As Boolean
Private m_nResourceID As Integer
Private m_nListID As Integer  'assoc popup list
Private m_nVisibleItems As Integer 'for assoc list obj
Private m_strList As String

Private Const kVersion As Integer = 2
'3100 marks beginning of CUIPopup string table entries
Private Const kResStrings As Integer = 3100
Private Const kErrStrings As Integer = 2950
Private Const kUserProps As Integer = 3
Private Const kTotalProps As Integer = 16
Private Const kProperties As String = "Selected-Text-Text(number)-Index-NoItems-ItemText-Left-Top-Width-Height"
Private Const kMethods As String = "Hide-Show-Redraw-Clear-Add-Delete"

Private Sub class_initialize()
   obj.Parent = Me
   obj.name = "Popup"
   obj.Kind = "pop"
   obj.Width = 45
   obj.Label = obj.name
   m_bAnchorLeft = True
   m_nResourceID = 0
   m_nListID = 0
   m_nVisibleItems = 4
   m_strList = ""
   'reserve id for list
End Sub

Public Sub PrcOut()
Dim c As Byte
Dim pop As ctlOut
Dim popup As popupOut
Dim templen As Integer

   BuildControlPrc pop, obj
   pop.style.s = &H3
   
   If AnchorLeft = True Then pop.attr = pop.attr Or &H8
   'pop.attr = pop.attr And &HDF 'turn off visible
   pop.group = cvtWord(m_nResourceID) '??is this right
   c = &H1
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   Put #9, , pop
   templen = Len(obj.Label)
   Put #6, , templen
   Put #9, , obj.Label
   c = &H0
   Put #9, , c

   ' other popup output
   PutOutListElem

   'now, put out a popup form elem
   c = &HA
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   popup.ctlId.w = cvtWord(obj.IdNo)
   popup.ListId.w = cvtWord(obj.IdNo + 1)
   Put #9, , popup
End Sub

Sub PutOutListElem()
Dim cnt As Integer
Dim c As Byte
Dim lst As listOut
Dim s As Variant
Dim ss As String
Dim templen As Integer
Dim Items As New Collection
Dim i As Integer
Dim listHeight As Integer
Dim strTemp As String
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

   lst.id.w = cvtWord(obj.IdNo + 1)
   lst.bounds.topleft.x = cvtWord(obj.OrigLeft + 13)
   lst.bounds.topleft.y = cvtWord(obj.OrigTop)
   lst.bounds.extent.x = cvtWord(obj.Width - 13)
'   charHeight = 11
'   lst.bounds.extent.y = cvtWord(VisibleItems * charHeight)
   listHeight = GetTextHeight("?", obj.FontID) * m_nVisibleItems
   lst.bounds.extent.y = cvtWord(listHeight)
'   If (obj.OrigTop + VisibleItems * charHeight) > 159 Then
'      If VisibleItems * charHeight > 159 Then
'         lst.bounds.topleft.y = 0
'      Else
'         lst.bounds.topleft.y = 159 - VisibleItems * charHeight
'      End If
'   End If
   If (obj.OrigTop + listHeight) > 159 Then
      If listHeight > 159 Then
         lst.bounds.topleft.y = 0
      Else
         lst.bounds.topleft.y = 159 - listHeight
      End If
   End If

   lst.attr = &H0
   lst.itemsText.c = 0
'   lst.numItems.w = cvtWord(VisibleItems)
   lst.numItems.w = cvtWord(UBound(arrList) + 1)
   lst.currentItem.w = -1   '10/30
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

'   For Each s In Items
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

'   cnt = Items.count
   cnt = UBound(arrList) + 1
   Put #6, , cnt

'   For Each s In Items
'      ss = s
'      templen = Len(ss)
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
      MsgBox gStringTable(3294) + version '"Error: Invalid Popup Trigger Version (" & version & ")"
      End
   End If

   Input #1, m_bAnchorLeft, m_nResourceID, m_nVisibleItems
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
   Write #1, AnchorLeft, ResourceId, VisibleItems
   s = m_strList
   ProcessScript s, ToDisk
   Write #1, s
   obj.Save
End Sub

Public Function Copy() As String
   Copy = Quote(obj.Kind) & vbCrLf
   Copy = Copy & kVersion & vbCrLf
   Copy = Copy & Join(Array(BoolStr(AnchorLeft), ResourceId, VisibleItems), ",") & vbCrLf
   Copy = Copy & m_strList & vbCrLf
   Copy = Copy & obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "pop" Then
      MsgBox gStringTable(3295) '"Invalid paste: Popup Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3296) '"Invalid paste: Popup Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   AnchorLeft = UnBoolStr(tokens(0))
   ResourceId = tokens(1)
   VisibleItems = tokens(2)
   m_strList = strLines(4)

   'Remove used code and paste inherited object
   For i = 5 To UBound(strLines)
      strLines(i - 4) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 4)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
Dim i As Integer
Const kDropArrowWidth = 8
Const kDropArrowSpace = 2

   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw False
   obj.Control.BackColor = getUIColorTable(1)
   obj.Control.ForeColor = getUIColorTable(2)

   'Control specific drawing/text here
   obj.Control.CurrentX = kDropArrowWidth * obj.Control.Parent.MagFactor + 1
   obj.Control.CurrentY = 0
   obj.Control.Print obj.Label
   For i = 0 To 7
      obj.Control.Line (i, i + (kDropArrowSpace * obj.Control.Parent.MagFactor)) _
      -((kDropArrowWidth * obj.Control.Parent.MagFactor) - i, i + (kDropArrowSpace * obj.Control.Parent.MagFactor))
   Next
   obj.DrawSelected
End Sub

Public Property Let ResourceId(ByVal vData As Integer)
   m_nResourceID = vData
End Property

Public Property Get ResourceId() As Integer
   ResourceId = m_nResourceID
End Property

Public Property Let AnchorLeft(ByVal vData As Boolean)
   m_bAnchorLeft = vData
End Property

Public Property Get AnchorLeft() As Boolean
   AnchorLeft = m_bAnchorLeft
End Property

Public Property Let ListId(ByVal vData As Integer)
   m_nListID = vData
End Property

Public Property Get ListId() As Integer
   ListId = m_nListID
End Property

Public Property Let VisibleItems(ByVal vData As Integer)
   m_nVisibleItems = vData
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
      gPropInfo.name = "Anchor Left"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
      gPropInfo.Type = pgBoolean
'   Case 1 'List ID
'      gPropInfo.Name = "List ID"
'      gPropInfo.Val = GetPropertyVal("List ID")
'      gPropInfo.Type = pgString
   Case 1 'Visible Rows
      gPropInfo.name = "Visible Rows"
      gPropInfo.Val = GetPropertyVal(gPropInfo.name)
      gPropInfo.Type = pgString
   Case 2
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
   Case kUserProps + 6: obj.GetProperty "Height"
   Case kUserProps + 7: obj.GetProperty "Visible"
   Case kUserProps + 8: obj.GetProperty "Font ID"
   Case kUserProps + 9: obj.GetProperty "Label"
   Case kUserProps + 10: obj.GetProperty "Nav Flags"
   Case kUserProps + 11: obj.GetProperty "Nav Above ID"
   Case kUserProps + 12: obj.GetProperty "Nav Below ID"
   End Select
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Anchor Left": GetPropertyVal = AnchorLeft
'   Case "List ID": GetPropertyVal = ListId
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
Dim nResID As Integer
Dim bmp As CBitmapFile
Dim frm As CForm
Dim o As Object
Dim n As Integer
Dim arrList() As String
Dim i As Integer
Dim j As Integer
Dim arrItems() As String

   ValidateProperty = True
   Select Case strProp
   Case "Anchor Left": AnchorLeft = strVal Like g_strTrue
'   Case "List ID"
'      ListId = 0
'      MsgBox gStringTable(kResStrings), vbOKOnly
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

