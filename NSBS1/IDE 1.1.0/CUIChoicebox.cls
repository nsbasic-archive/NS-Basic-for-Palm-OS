VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIChoicebox"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Member0" ,"Repeater"
Option Explicit

Public obj As New CUIObject
Private m_bAnchorLeft As Boolean
Private m_nGroupID As Integer
Private m_bSelected As Boolean

Private Const kVersion As Integer = 1
'2700 marks beginning of CUIChoicebox/CUICheckbox string table entries
Private Const kResStrings As Integer = 2700
Private Const kUserProps As Integer = 3
Private Const kTotalProps As Integer = 13

Private Sub class_initialize()
   obj.Parent = Me
   obj.Name = "Choicebox"
   obj.Kind = "cho"
   obj.Width = 36
   obj.Label = obj.Name
   m_nGroupID = 0
   m_bSelected = False
   m_bAnchorLeft = True
End Sub

Public Sub PrcOut()
Dim c As Byte
Dim cho As ctlOut
Dim templen As Integer

   BuildControlPrc cho, obj
   cho.style.s = &H1
   If AnchorLeft = True Then cho.attr = cho.attr Or &H8
   cho.group = m_nGroupID
   If Selected = True Then cho.attr = cho.attr Or &H10
   
   c = &H1
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)
   
   Put #9, , cho
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
      MsgBox "Error: Invalid Choicebox Version (" & version & ")"
      End
   End If

   Input #1, m_bSelected, m_nGroupID, m_bAnchorLeft
   obj.Restore
End Sub

Public Sub Save()
   Write #1, obj.Kind
   Write #1, kVersion
   Write #1, Selected, GroupId, AnchorLeft
   obj.Save
End Sub

Public Function Copy() As String
Dim temp As String

   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   temp = Join(Array(BoolStr(Selected), GroupId, BoolStr(AnchorLeft)), ",")
   Copy = Copy + temp + vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "cho" Then
      MsgBox "Invalid paste: Choicebox Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox "Invalid paste: Choicebox Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   Selected = UnBoolStr(tokens(0))
   GroupId = tokens(1)
   AnchorLeft = UnBoolStr(tokens(2))

   'Remove used code and paste inherited object
   For i = 4 To UBound(strLines)
      strLines(i - 3) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 3)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw False

   'Control specific drawing/text here
   If Selected Then
      obj.Control.BackColor = vbBlack
      obj.Control.ForeColor = vbWhite
   Else
      obj.Control.BackColor = vbWhite
      obj.Control.ForeColor = vbBlack
      'Draw border
      obj.Control.Line (0, 0)-(obj.Control.Width - 1, obj.Control.Height - 1), vbBlack, B
   End If

   obj.Control.CurrentX = (obj.Control.Width - obj.Control.TextWidth(obj.Label)) \ 2
   obj.Control.CurrentY = (obj.Control.Height - obj.Control.TextHeight(obj.Label)) \ 2
   obj.Control.Print obj.Label
   obj.DrawSelected
End Sub

Public Property Let GroupId(ByVal vData As Integer)
   m_nGroupID = vData
End Property

Public Property Get GroupId() As Integer
   GroupId = m_nGroupID
End Property

Public Property Let Selected(ByVal vData As Boolean)
   m_bSelected = vData
End Property

Public Property Get Selected() As Boolean
   Selected = m_bSelected
End Property

Public Property Let AnchorLeft(ByVal vData As Boolean)
   m_bAnchorLeft = vData
End Property

Public Property Get AnchorLeft() As Boolean
   AnchorLeft = m_bAnchorLeft
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
   Select Case nProp
   Case 0: gPropInfo.Name = "Anchor Left"
   Case 1
      gPropInfo.Name = "Group ID"
      gPropInfo.Type = pgString
   Case 2: gPropInfo.Name = "Selected"
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
   End Select
   If nProp < kUserProps Then gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Anchor Left": GetPropertyVal = AnchorLeft
   Case "Group ID": GetPropertyVal = GroupId
   Case "Selected": GetPropertyVal = Selected
   Case Else: GetPropertyVal = obj.GetPropertyVal(strProp)
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim o As Object

   ValidateProperty = True
   Select Case strProp
   Case "Anchor Left": AnchorLeft = strVal
   Case "Group ID"
      If Selected Then
         For Each o In obj.Form.ObjectCollection
            If Not o Is Me Then
               If StrComp(o.obj.Kind, obj.Kind) = 0 Then
                  If o.GroupId = strVal And o.Selected Then
                     Select Case MsgBox(LoadResString(kResStrings), vbYesNoCancel)
                     Case vbYes
                        o.Selected = False
                        GroupId = strVal
                     Case vbNo
                        Selected = False
                        GroupId = strVal
                     Case vbCancel
                        ValidateProperty = False
                     End Select
                  End If
               End If
            End If
         Next
      Else
         GroupId = strVal
      End If
   Case "Selected"
      Selected = strVal Like g_strTrue
      If strVal Like g_strTrue Then
         For Each o In obj.Form.ObjectCollection
            If Not o Is Me Then
               If StrComp(o.obj.Kind, obj.Kind) = 0 Then
                  If o.GroupId = strVal And o.Selected Then
                     Select Case MsgBox(LoadResString(kResStrings), vbYesNoCancel)
                     Case vbYes
                        o.Selected = False
                     Case vbNo
                        Selected = False
                     Case vbCancel
                        Selected = False
                        ValidateProperty = False
                     End Select
                  End If
               End If
            End If
         Next
      End If
   Case Else: ValidateProperty = obj.ValidateProperty(strProp, strVal)
   End Select
End Function
