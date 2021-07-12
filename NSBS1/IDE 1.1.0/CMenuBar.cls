VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CMenuBar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public workXoffset As Integer
Public caption As String
Public command As String
Public MenuElems As New Collection
Public IdNo As Integer
Private m_strGlobalID As String

Private Const kVersion As Integer = 1
Private Const kTotalProps = 2

Public Sub class_initialize()
   caption = "untitled"
   command = ""
'   gtarget.HighestSeqNo = gtarget.HighestSeqNo + 1
'   idno = gtarget.HighestSeqNo
End Sub

Public Sub save()
Dim mElem As CMenuElem

   Write #1, "menu"
   Write #1, kVersion
   Write #1, caption, command, IdNo
   Write #1, MenuElems.count
   For Each mElem In MenuElems
      mElem.save
   Next
End Sub

Public Function Copy() As String
Dim mElem As CMenuElem

   Copy = Quote("menubar") & vbCrLf
   Copy = Copy & kVersion & vbCrLf
   Copy = Copy & Join(Array(Quote(caption), Quote(command), IdNo), ",") & vbCrLf
   Copy = Copy & MenuElems.count & vbCrLf
   For Each mElem In MenuElems
      Copy = Copy & mElem.Copy
   Next
End Function

Public Sub Paste(ByRef strLines() As String, ByVal proj As CProject)
Dim tokens() As String
Dim i As Integer, nCount As Integer
Dim oldIdNo As Integer
Dim mElem As CMenuElem

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) = "menuelem" Then
      nCount = 1
      GoTo PasteMenuElem
   End If
   If LCase(UnQuote(strLines(1))) <> "menubar" Then
      MsgBox gStringTable(3242) '"Invalid paste: MenuBar Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3243) '"Invalid paste: MenuBar Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   caption = UnQuote(tokens(0))
   oldIdNo = tokens(2)
   nCount = strLines(4)
   
   'Remove used code then paste any menuelems
   For i = 5 To UBound(strLines)
      strLines(i - 4) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 4)
   For i = 1 To nCount
PasteMenuElem:
      Set mElem = New CMenuElem
      mElem.IdNo = proj.GetNextSeqNo
      mElem.SetGlobalID GlobalID
      mElem.Paste strLines
      MenuElems.Add mElem, Trim(str(mElem.IdNo))
   Next
End Sub

Public Sub restore()
Dim ignore As String
Dim version As Integer
Dim i As Integer
Dim cnt As Integer
Dim mElem As CMenuElem

   Input #1, ignore 'menu
   Input #1, version
   If version <> kVersion Then
      MsgBox gStringTable(3244) + version '"Error: Invalid MenuBar Version (" & version & ")"
      End
   End If

   Input #1, caption, command, IdNo
   Input #1, cnt
   SetGlobalID ""
'   If cnt > 0 Then
   For i = 1 To cnt
      Set mElem = New CMenuElem
      mElem.restore
      MenuElems.Add mElem, Trim(str(mElem.IdNo))
      mElem.SetGlobalID GlobalID
   Next
'   End If
End Sub

Public Property Get GlobalID() As String
Attribute GlobalID.VB_UserMemId = 0
   GlobalID = m_strGlobalID
End Property

Public Sub SetGlobalID(ByVal strMenuGlobalID As String)
   If IdNo = 0 Then
      m_strGlobalID = "|" & strMenuGlobalID
   Else
      If m_strGlobalID = "" Then
         m_strGlobalID = "menubar|" & IdNo & "|" & strMenuGlobalID
      Else
         m_strGlobalID = "menubar|" & IdNo & m_strGlobalID
      End If
   End If
End Sub

Public Sub GetProperty()
Static nProp As Integer

   If nProp = kTotalProps Then
      gPropInfo.Name = ""
      nProp = 0
      Exit Sub
   End If

   gPropInfo.Val = ""
   Select Case nProp
   Case 0
      gPropInfo.Name = "Caption"
      gPropInfo.Type = pgString
   Case 1
      gPropInfo.Name = "ID"
      gPropInfo.Type = pgReadOnly
   End Select
   If nProp < kTotalProps Then gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Caption": GetPropertyVal = caption
   Case "ID": GetPropertyVal = IdNo
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
   ValidateProperty = True
   Select Case strProp
   Case "Caption"
      If Len(strVal) = 0 Then
         ValidateProperty = False
         Exit Function
      End If
      caption = strVal
   End Select
   If ValidateProperty Then LocateProject(GlobalID).Dirty = True
End Function

Public Property Get Name() As String
   Name = "Menu Bar"
End Property
