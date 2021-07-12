VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUIGraffitiShiftIndicator"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Member0" ,"UILabel"
Option Explicit

Public obj As New CUIObject

Private Const kVersion As Integer = 1
Private Const kUserProps As Integer = 0
Private Const kTotalProps As Integer = 5
Private Const kProperties As String = "Index-Left-Top-Width-Height"
Private Const kMethods As String = "Hide-Show"

Private Sub class_initialize()
   obj.Parent = Me
   obj.name = "GSI"
   obj.Kind = "shf"
   obj.Width = 8
   obj.Height = 8
End Sub

Sub PrcOut()
Dim c As Byte
Dim si As shiftIndicOut

   si.pos.x = cvtWord(obj.OrigLeft)
   si.pos.y = cvtWord(obj.OrigTop)

   c = &HB
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)
   Put #9, , si
End Sub

Public Sub Restore()
Dim version As Integer

   Input #1, version
   If version <> kVersion Then
      MsgBox gStringTable(3285) + version '"Error: Invalid Graffiti Shift Indicator Version (" & version & ")"
      End
   End If

   obj.Restore
End Sub

Public Sub Save()
   Write #1, obj.Kind
   Write #1, kVersion
   obj.Save
End Sub

Public Function Copy() As String
   Copy = Quote(obj.Kind) + vbCrLf
   Copy = Copy & kVersion & vbCrLf
   Copy = Copy + obj.Copy()
End Function
Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "shf" Then
      MsgBox gStringTable(3286) '"Invalid paste: Graffiti Shift Indicator Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3287) '"Invalid paste: Graffiti Shift Indicator version"
      End
   End If

   'Restore properties

   'Remove used code and paste inherited object
   For i = 3 To UBound(strLines)
      strLines(i - 2) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 2)
   obj.Paste strLines
End Sub

Public Sub ScreenDraw()
Dim i As Integer, h As Integer, w As Integer

   If obj.Control Is Nothing Then Exit Sub

   obj.Width = 8
   obj.Height = 8
   obj.ScreenDraw False

   'Control specific drawing/text here
'George: Make this MagFactor-savvy
   'draw upper triangle
   w = 16
   h = 18
   For i = 1 To w / 2
      obj.Control.Line (w / 2 - i, i)-(w / 2 + i, i)
   Next
   'draw bar
   obj.Control.Line (4, w / 2)-(11, h), getUIColorTable(0), BF
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
   Select Case nProp
   Case kUserProps + 0: obj.GetProperty "(Name)"
   Case kUserProps + 1: obj.GetProperty "Type"
   Case kUserProps + 2: obj.GetProperty "ID"
   Case kUserProps + 3: obj.GetProperty "Left"
   Case kUserProps + 4: obj.GetProperty "Top"
   End Select
   gPropInfo.Val = GetPropertyVal(gPropInfo.name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   GetPropertyVal = obj.GetPropertyVal(strProp)
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
   ValidateProperty = obj.ValidateProperty(strProp, strVal)
End Function

Public Function PropertyList() As String()
   PropertyList = Split(kProperties, "-")
End Function

Public Function MethodList() As String()
   MethodList = Split(kMethods, "-")
End Function

