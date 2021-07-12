VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUISelector"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Member0" ,"UITable"
Option Explicit

Public obj As New CUIObject
Private m_bAnchorLeft As Boolean

Private Const kVersion As Integer = 1
'2600 marks beginning of CUIButton/CUISelector string table entries
Private Const kResStrings As Integer = 2600
Private Const kUserProps As Integer = 1
Private Const kTotalProps As Integer = 14
Private Const kProperties = "Text-Left-Top-Width-Height"
Private Const kMethods = "Hide-Show-Redraw"

Private Sub class_initialize()
   obj.Parent = Me
   obj.name = "Selector"
   obj.Kind = "sel"
   obj.Width = 45
   obj.Label = obj.name
End Sub

Public Sub PrcOut()
Dim c As Byte
Dim sel As ctlOut
Dim templen As Integer

   BuildControlPrc sel, obj
   sel.style.s = &H4
   If AnchorLeft = True Then sel.attr = sel.attr Or &H8

   c = &H1
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)
   Put #9, , sel
   templen = Len(obj.Label)
   Put #6, , templen
   Put #9, , obj.Label
   c = &H0
   Put #9, , c
End Sub

Public Sub Restore()
Dim version As Integer

   Input #1, version
   If version <> kVersion Then
      MsgBox gStringTable(3303) + version '"Error: Invalid Selector Version (" & version & ")"
      End
   End If

   Input #1, m_bAnchorLeft
   obj.Restore
End Sub

Public Sub Save()
   Write #1, obj.Kind
   Write #1, kVersion
   Write #1, AnchorLeft
   obj.Save
End Sub

Public Function Copy() As String
   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   Copy = Copy + BoolStr(AnchorLeft) + vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "sel" Then
      MsgBox gStringTable(3304) '"Invalid paste: Selector Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3305) '"Invalid paste: Selector Version"
      End
   End If

   'Restore properties
   AnchorLeft = UnBoolStr(strLines(3))

   'Remove used code and paste inherited object
   For i = 4 To UBound(strLines)
      strLines(i - 3) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 3)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw True
   obj.Control.BackColor = getUIColorTable(1)
   obj.Control.ForeColor = getUIColorTable(2)

   'Control specific drawing/text here
'George: This doesn't actually go here, it should be managed in ValidateProperty
'George: when all the Palm font stuff is resolved
'   If gbWinNT2000 Or gbPlainText Then
'      obj.Width = obj.Control.TextWidth(obj.Label) \ obj.Control.Parent.MagFactor + 2
'   Else
'      obj.Width = obj.Control.TextWidth(obj.Label) + 2
'   End If

   obj.Control.CurrentX = 2
   obj.Control.CurrentY = (obj.Control.Height - obj.Control.TextHeight(obj.Label)) \ 2
   obj.Control.Print obj.Label
   obj.DrawSelected
End Sub

Public Property Let AnchorLeft(ByVal vData As Boolean)
   m_bAnchorLeft = vData
End Property

Public Property Get AnchorLeft() As Boolean
   AnchorLeft = m_bAnchorLeft
End Property

Private Sub Class_Terminate()
   Set obj = Nothing
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
   Select Case nProp
   Case 0: gPropInfo.name = "Anchor Left"
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
   If nProp < kUserProps Then gPropInfo.Val = GetPropertyVal(gPropInfo.name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Anchor Left": GetPropertyVal = AnchorLeft
   Case Else: GetPropertyVal = obj.GetPropertyVal(strProp)
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
   ValidateProperty = True
   Select Case strProp
   Case "Anchor Left": AnchorLeft = strVal
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

