VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CUILabel"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
Attribute VB_Ext_KEY = "Member0" ,"UIList"
Option Explicit

Public obj As New CUIObject

Private Const kVersion As Integer = 1
Private Const kUserProps As Integer = 0
Private Const kTotalProps As Integer = 8
Private Const kProperties As String = "Text"
Private Const kMethods As String = "Hide-Show-Redraw-Left-Top-Width-Height"

Private Sub class_initialize()
   obj.Parent = Me
   obj.name = "Label"
   obj.Kind = "lbl"
   obj.Label = obj.name
End Sub

Public Sub PrcOut()
Dim lab As labelOut
Dim c As Byte
Dim templen As Integer

   lab.id.w = cvtWord(obj.IdNo)
   If obj.Usable Then
      lab.Usable.w = cvtWord(&H8000)
   Else
      lab.Usable.w = 0
   End If
   lab.pos.x = cvtWord(obj.OrigLeft)
   lab.pos.y = cvtWord(obj.OrigTop)
   lab.font = obj.FontID
   lab.Text.c = 0
   c = &H8
   Put #8, , c
   c = &H0
   Put #8, , c
   wordBound (9)
   outLong 8, Loc(9)
   
   Put #9, , lab
   If obj.Label = "" Or obj.Label = " " Then obj.Label = "*"
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
      MsgBox gStringTable(3288) + version '"Error: Invalid Label Version (" & version & ")"
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
   If LCase(UnQuote(strLines(1))) <> "lbl" Then
      MsgBox gStringTable(3289) '"Invalid paste: Label Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3290) '"Invalid paste: Label Version"
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
   If obj.Control Is Nothing Then Exit Sub

   obj.ScreenDraw False
   obj.Control.BackColor = getUIColorTable(1)
   obj.Control.ForeColor = getUIColorTable(2)

   'This tricky one likes to control its own Width and Height
   If gbWinNT2000 Or gbPlainText Then
      obj.Width = obj.Control.TextWidth(obj.Label) \ obj.Control.Parent.MagFactor
      obj.Height = obj.Control.TextHeight(obj.Label) \ obj.Control.Parent.MagFactor
   Else
      obj.Width = obj.Control.TextWidth(obj.Label)
      obj.Height = obj.Control.TextHeight(obj.Label)
   End If

   obj.ScreenDraw False

   'Control specific drawing/text here
   obj.Control.CurrentX = 0
   obj.Control.CurrentY = 0
   obj.Control.Print obj.Label
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
   Case kUserProps + 5: obj.GetProperty "Visible"
   Case kUserProps + 6: obj.GetProperty "Font ID"
   Case kUserProps + 7: obj.GetProperty "Label"
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

