VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CMenu"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public MenuBars As New Collection
Public Name As String
Public IdNo As Integer
Private m_strGlobalID As String

Private Const kVersion As Integer = 2
Private Const kTotalProps = 2

Private Sub class_initialize()
   Name = ""
   IdNo = 0
End Sub

Public Sub Restore()
Dim version As Integer
Dim i As Integer
Dim cnt As Integer
Dim mBar As CMenuBar

   Input #1, version
   If version > kVersion Then
      MsgBox gStringTable(3239) + version '"Error: Invalid Menu Version
      End
   End If

   Input #1, Name

   If version > 1 Then Input #1, IdNo

   SetGlobalID ""
   Input #1, cnt
   For i = 1 To cnt
      Set mBar = New CMenuBar
      mBar.SetGlobalID GlobalID
      mBar.Restore
      MenuBars.Add mBar, str(mBar.IdNo)
   Next
End Sub

Public Sub Save()
Dim mBar As CMenuBar

   Write #1, "mnu"
   Write #1, kVersion, Name
   Write #1, IdNo
   Write #1, MenuBars.count
   For Each mBar In MenuBars
      mBar.Save
   Next
End Sub

Public Function Copy() As String
Dim mBar As CMenuBar

   Copy = Quote("mnu") & vbCrLf
   Copy = Copy & kVersion & "," & Quote(Name) & vbCrLf
   Copy = Copy & IdNo & vbCrLf
   Copy = Copy & MenuBars.count & vbCrLf
   For Each mBar In MenuBars
      Copy = Copy & mBar.Copy
   Next
End Function

Public Sub Paste(ByRef strLines() As String, ByVal proj As CProject)
Dim tokens() As String
Dim i As Integer, nCount As Integer
Dim oldIdNo As Integer
Dim mBar As CMenuBar

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) = "menubar" Then
      nCount = 1
      GoTo PasteMenuBar
   End If
   If LCase(UnQuote(strLines(1))) <> "mnu" Then
      MsgBox gStringTable(3240) '"Invalid paste: Menu Type"
      End
   End If
   tokens = Split(strLines(2), ",")
   If tokens(0) <> kVersion Then
      MsgBox gStringTable(3241) '"Invalid paste: Menu Version"
      End
   End If

   'Restore properties
   Name = UnQuote(tokens(1))
   oldIdNo = strLines(3)
   nCount = strLines(4)
   
   'Remove used code then paste any menubars
   For i = 5 To UBound(strLines)
      strLines(i - 4) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - 4)
   For i = 1 To nCount
PasteMenuBar:
      Set mBar = New CMenuBar
      mBar.IdNo = proj.GetNextSeqNo
      mBar.SetGlobalID GlobalID
      MenuBars.Add mBar, str(mBar.IdNo)
      mBar.Paste strLines, proj
   Next
End Sub

Public Property Get GlobalID() As String
Attribute GlobalID.VB_UserMemId = 0
   GlobalID = m_strGlobalID
End Property

Public Sub SetGlobalID(ByRef strProjGlobalID As String)
   If IdNo = 0 Then
      m_strGlobalID = "|" & strProjGlobalID
   Else
      If m_strGlobalID = "" Then
         m_strGlobalID = "menu|" & IdNo & "|" & strProjGlobalID
      Else
         m_strGlobalID = "menu|" & IdNo & m_strGlobalID
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
      gPropInfo.Name = "Name"
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
   Case "Name": GetPropertyVal = Name
   Case "ID": GetPropertyVal = IdNo
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
   ValidateProperty = True
   Select Case strProp
   Case "Name"
      If Len(strVal) = 0 Then
         ValidateProperty = False
         Exit Function
      End If
      Name = strVal
'   Case "Frame": Frame = strVal
'   Case "Non-bold Frame": NonBoldFrame = strVal
'   Case Else: ValidateProperty = obj.ValidateProperty(strProp, strVal)
   End Select
   If ValidateProperty Then LocateProject(GlobalID).Dirty = True
End Function

Public Sub MoveElement(ByVal Elem As CMenuElem, moveDir As Long)
Dim mBar As CMenuBar
Dim mElem As CMenuElem
Dim i As Integer
Dim j As Integer

   'Locate which Menu Bar contains the element
   For i = 1 To MenuBars.count
      Set mBar = MenuBars(i)
      For j = 1 To mBar.MenuElems.count
         If mBar.MenuElems(j) Is Elem Then GoTo lbl_MoveElement
      Next
   Next

lbl_MoveElement:
   If moveDir = vbKeyUp Then
      If j = 1 Then
         'Already the first element in this bar
         Beep
         Exit Sub
      End If
      mBar.MenuElems.Remove j
      mBar.MenuElems.Add Elem, Trim(str(Elem.IdNo)), j - 1
   Else 'moveDir = vbKeyDown
      If j = mBar.MenuElems.count Then
         'Already the last element in this bar
         Beep
         Exit Sub
      End If
      mBar.MenuElems.Remove j
      mBar.MenuElems.Add Elem, Trim(str(Elem.IdNo)), , j
   End If
   LocateProject(GlobalID).Dirty = True
End Sub

Public Sub MoveBar(ByVal bar As CMenuBar, moveDir As Long)
Dim mBar As CMenuBar
Dim i As Integer

   'Locate the Menu Bar
   For i = 1 To MenuBars.count
      If MenuBars(i) Is bar Then Exit For
   Next

   If moveDir = vbKeyUp Then
      If i = 1 Then
         'Already the first bar in this menu
         Beep
         Exit Sub
      End If
      MenuBars.Remove i
      MenuBars.Add bar, , i - 1
   Else
      If i = MenuBars.count Then
         'Already the last bar in this menu
         Beep
         Exit Sub
      End If
      MenuBars.Remove i
      MenuBars.Add bar, , , i
   End If
   LocateProject(GlobalID).Dirty = True
End Sub
