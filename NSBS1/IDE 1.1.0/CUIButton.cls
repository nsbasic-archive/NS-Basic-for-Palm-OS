VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIButton"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

Public obj As New CUIObject
Private m_bAnchorLeft As Boolean
Private m_bFrame As Boolean
Private m_bNonBoldFrame As Boolean

Private Const kVersion As Integer = 1
'2600 marks beginning of CUIButton string table entries
Private Const kResStrings As Integer = 2600
Private Const kUserProps As Integer = 3
Private Const kTotalProps As Integer = 16
Private Const kProperties As String = "Text-Index-ID-Left-Top-Width-Height"
Private Const kMethods As String = "Hide-Show-Redraw"

Private Sub class_initialize()
   obj.Parent = Me
   obj.name = "Button"
   obj.Kind = "but"
   obj.Width = 36
   obj.Label = "OK"
   m_bAnchorLeft = True
   m_bFrame = True
   m_bNonBoldFrame = True
End Sub

Public Sub PrcOut()
Dim but As ctlOut
Dim c As Byte
Dim templen As Integer

   BuildControlPrc but, obj
   but.style.s = &H0
   but.attr = but.attr And &HF8
   If Frame = True Then
      If NonBoldFrame = True Then
         but.attr = but.attr Or &H1
      Else
         but.attr = but.attr Or &H2
      End If
   End If
   If AnchorLeft = True Then but.attr = but.attr Or &H8
   c = &H1
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)

   Put #9, , but
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
      MsgBox gStringTable(3270) + version '"Error: Invalid button version (" & version & ")"
      End
   End If

   Input #1, m_bAnchorLeft, m_bFrame, m_bNonBoldFrame
   obj.Restore
End Sub

Public Sub Save()
   Write #1, obj.Kind
   Write #1, kVersion
   Write #1, m_bAnchorLeft, m_bFrame, m_bNonBoldFrame
   obj.Save
End Sub

Public Function Copy() As String
Dim version As Integer
Dim temp As String

   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   temp = Join(Array(BoolStr(AnchorLeft), BoolStr(Frame), BoolStr(NonBoldFrame)), ",")
   Copy = Copy + temp + vbCrLf
   Copy = Copy + obj.Copy()
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "but" Then
      MsgBox gStringTable(3271) '"Invalid paste: Button Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3272) '"Invalid paste: Button Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   AnchorLeft = UnBoolStr(tokens(0))
   Frame = UnBoolStr(tokens(1))
   NonBoldFrame = UnBoolStr(tokens(2))

   'Remove used code and paste inherited object
   For i = 4 To UBound(strLines)
      strLines(i - 3) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 3)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
Dim rad As Integer
Dim w As Integer, h As Integer, dw As Integer
Const PI = 3.14159265

   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw False
   obj.Control.BackColor = getUIColorTable(1)
   obj.Control.ForeColor = getUIColorTable(2)

   'Control specific drawing/text here
   obj.Control.CurrentX = (obj.Control.Width - obj.Control.TextWidth(obj.Label)) \ 2
   obj.Control.CurrentY = (obj.Control.Height - obj.Control.TextHeight(obj.Label)) \ 2
   obj.Control.Print obj.Label
   w = obj.Control.Width - 1
   h = obj.Control.Height - 1

   If m_bFrame Then
      #If NSBSymbian Then
      rad = 0 * obj.Control.Parent.MagFactor 'Symbian has square corners
      #Else
      rad = 3 * obj.Control.Parent.MagFactor
      #End If
      obj.Control.DrawWidth = 1
      If Not m_bNonBoldFrame Then obj.Control.DrawWidth = 2
      dw = obj.Control.DrawWidth
      
      obj.Control.Line (rad, 0)-(w - rad, dw - 1), getUIColorTable(0), BF 'top
      obj.Control.Line (rad, h)-(w - rad, h), getUIColorTable(0) 'bottom
      obj.Control.Line (0, rad)-(dw - 1, h - rad), getUIColorTable(0), BF 'left
      obj.Control.Line (w, rad)-(w, h - rad), getUIColorTable(0) 'right
      obj.Control.Circle (rad, rad), rad, getUIColorTable(0), PI * 0.5, PI 'TL
      obj.Control.Circle (rad, h - rad), rad, getUIColorTable(0), PI, PI * 1.55 'BL
      obj.Control.Circle (w - rad, rad), rad, getUIColorTable(0), 0, PI * 0.5 'TR
      obj.Control.Circle (w - rad, h - rad), rad, getUIColorTable(0), PI * 1.5, 2 * PI 'BR
   End If
   obj.DrawSelected
End Sub

Public Property Let NonBoldFrame(ByVal vData As Boolean)
   m_bNonBoldFrame = vData
End Property

Public Property Get NonBoldFrame() As Boolean
   NonBoldFrame = m_bNonBoldFrame
End Property

Public Property Let Frame(ByVal vData As Boolean)
   m_bFrame = vData
End Property

Public Property Get Frame() As Boolean
   Frame = m_bFrame
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
      gPropInfo.name = ""
      nProp = 0
      Exit Sub
   End If

   gPropInfo.Val = ""
   If nProp < kUserProps Then gPropInfo.Type = pgBoolean
   Select Case nProp
   Case 0: gPropInfo.name = "Anchor Left"
   Case 1: gPropInfo.name = "Frame"
   Case 2: gPropInfo.name = "Non-bold Frame"
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
   Case "Frame": GetPropertyVal = Frame
   Case "Non-bold Frame": GetPropertyVal = NonBoldFrame
   Case Else: GetPropertyVal = obj.GetPropertyVal(strProp)
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
   ValidateProperty = True
   Select Case strProp
   Case "Anchor Left": AnchorLeft = strVal
   Case "Frame": Frame = strVal
   Case "Non-bold Frame": NonBoldFrame = strVal
   Case Else: ValidateProperty = obj.ValidateProperty(strProp, strVal)
   End Select
End Function

Public Function PropertyList() As String()
   PropertyList = Split(kProperties, "-")
End Function

Public Function MethodList() As String()
   MethodList = Split(kMethods, "-")
End Function
