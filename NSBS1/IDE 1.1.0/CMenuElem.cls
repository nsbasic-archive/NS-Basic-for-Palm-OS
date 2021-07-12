VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CMenuElem"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public command As String
Public subrtnName As String
Public IdNo As Integer
Public menu_script As String


Public obj_code As String
Public obj_code_len As Long
Private m_strGlobalID As String
Private m_nMenuWidth As Integer
Private m_strCaption As String

Private Const kVersion As Integer = 1
Private Const kTotalProps = 4

Public Sub class_initialize()
'   Caption = ""
   command = ""

   IdNo = 0

   subrtnName = ""
   command = ""
   m_strCaption = "untitled"
   menu_script = ""
   obj_code = ""
   obj_code_len = 0
End Sub

Public Sub Save()
Dim strTemp As String

   Write #1, "menu"
   Write #1, kVersion
   Write #1, caption, command, subrtnName, IdNo
   strTemp = menu_script
   ProcessScript strTemp, ToDisk
   Write #1, strTemp
End Sub

Public Function Copy() As String
Dim strTemp As String

   Copy = Quote("menuelem") & vbCrLf
   Copy = Copy & kVersion & vbCrLf
   Copy = Copy & Join(Array(Quote(caption), Quote(command), Quote(subrtnName), IdNo), ",") & vbCrLf
   strTemp = menu_script
   ProcessScript strTemp, ToDisk
   Copy = Copy & Quote(strTemp) & vbCrLf
End Function

Public Sub Paste(ByRef strLines() As String)
Dim tokens() As String
Dim i As Integer
Dim oldIdNo As Integer
Dim nScriptEnd As Integer

   'Ensure the proper object type and version
   If LCase(UnQuote(strLines(1))) <> "menuelem" Then
      MsgBox gStringTable(3245) '"Invalid paste: Dropdown Type"
      End
   End If
   If strLines(2) <> kVersion Then
      MsgBox gStringTable(3246) '"Invalid paste: Dropdown Version"
      End
   End If

   'Restore properties
   tokens = Split(strLines(3), ",")
   caption = UnQuote(tokens(0))
   command = UnQuote(tokens(1))
   subrtnName = UnQuote(tokens(2))
   oldIdNo = tokens(3)

   'Get Menu Script
   'Find end of script
   For i = 4 To UBound(strLines)
      If Right(strLines(i), 1) = Chr(34) Then
         nScriptEnd = i
         Exit For
      End If
   Next

   'Move script lines into tokens array for joining
   ReDim tokens(nScriptEnd - i)
   For i = 0 To UBound(tokens)
      tokens(i) = strLines(i + 4)
   Next

   'Reconstitute script
   menu_script = UnQuote(Join(tokens, vbCrLf))
   ProcessScript menu_script, FromDisk

   'Rename script, as necessary
   menu_script = Replace(menu_script, "Menu" & oldIdNo & "_click", "Menu" & IdNo & "_click", , , vbTextCompare)

   'Remove used code then pass the rest on for pasting if anything remains
   For i = nScriptEnd + 1 To UBound(strLines)
      strLines(i - nScriptEnd) = strLines(i)
   Next
   ReDim Preserve strLines(UBound(strLines) - nScriptEnd)
End Sub

Public Sub Restore()
Dim ignore As String
Dim version As Integer
Dim strTemp As String

   Input #1, ignore 'menu"
   Input #1, version
   If version <> kVersion Then
      MsgBox gStringTable(3247) + version '"Error: Invalid Dropdown Version (" & version & ")"
      End
   End If

   Input #1, strTemp, command, subrtnName, IdNo
   Input #1, menu_script
   caption = strTemp
   ProcessScript menu_script, FromDisk
End Sub

Public Property Get ProcName() As String
   ProcName = "Menu" & IdNo & "_click"
End Property

Public Property Get GlobalID() As String
Attribute GlobalID.VB_UserMemId = 0
   GlobalID = m_strGlobalID
End Property

Public Sub SetGlobalID(ByVal strMenuBarGlobalID As String)
   m_strGlobalID = "menuelem|" & IdNo & "|" & strMenuBarGlobalID
End Sub

Public Function GetScript(ByVal strScript As String, Optional ByVal bForceCreate As Boolean = True) As String
   If Len(menu_script) > 0 Or Not bForceCreate Then
      GetScript = menu_script
   Else
      GetScript = "Sub " & ProcName & "()" & vbCrLf & vbCrLf & "End Sub"
   End If
End Function

Public Sub PutScript(ByVal strText As String, ByVal strScript As String)
Dim proj As CProject
   menu_script = strText
   Set proj = LocateProject(GlobalID)
   proj.Dirty = True
End Sub

Public Sub GetProperty()
Static nProp As Integer
Dim i As Integer

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
   Case 2
      gPropInfo.Name = "Proc Name"
      gPropInfo.Type = pgReadOnly
   Case 3
      gPropInfo.Name = "Shortcut"
      gPropInfo.Type = pgList
      gPropInfo.Data = "(None)"
      For i = 0 To 9
         gPropInfo.Data = gPropInfo.Data & ">" & i
      Next
      For i = Asc("A") To Asc("Z")
         gPropInfo.Data = gPropInfo.Data & ">" & Chr(i)
      Next
   End Select
   If nProp < kTotalProps Then gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Caption": GetPropertyVal = caption
   Case "ID": GetPropertyVal = IdNo
   Case "Proc Name": GetPropertyVal = ProcName
   Case "Shortcut": GetPropertyVal = command
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim strCommand As String

   ValidateProperty = True
   Select Case strProp
   Case "Caption"
      If Len(strVal) = 0 Then
         ValidateProperty = False
         Exit Function
      End If
      caption = strVal
   Case "Shortcut"
      If strVal = "(None)" Then strVal = ""
      If Len(strVal) > 0 Then
         strCommand = UCase(Left(strVal, 1))
         If (Asc(strCommand) < Asc("A") Or Asc(strCommand) > Asc("Z")) _
               And (strCommand < "0" Or strCommand > "9") Then
            ValidateProperty = False
            Exit Function
         End If
      End If
      command = strCommand
   End Select
   If ValidateProperty Then LocateProject(GlobalID).Dirty = True
End Function

Public Property Get Name() As String
   Name = "Dropdown"
End Property

Public Property Get caption() As String
   caption = m_strCaption
End Property

Public Property Let caption(ByVal strCaption As String)
Dim strFont As String
Dim nFontSize As Integer

   m_strCaption = strCaption
   strFont = frmMain.picBox.fontName
   nFontSize = frmMain.picBox.fontSize
   frmMain.picBox.fontName = gstrPalmFonts(0) 'NPalmText9
   frmMain.picBox.fontSize = 8
   m_nMenuWidth = frmMain.picBox.TextWidth(m_strCaption) \ 15
   frmMain.picBox.fontName = strFont
   frmMain.picBox.fontSize = nFontSize
End Property

Public Property Get MenuWidth() As Integer
   MenuWidth = m_nMenuWidth
End Property
