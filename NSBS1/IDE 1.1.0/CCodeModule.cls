VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CCodeModule"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public path As String
Public fileName As String
Public Name As String
Public pgm_script As String
Public obj_code As String
Public obj_code_len As Long
Public m_bSaved As Boolean

Public offset As Integer
Private m_nIdNo As Integer

'2300 marks beginning of CCodeModule string table entries
Private Const kResStrings As Integer = 2300
Private Const kTotalProps As Integer = 3
Private Const kErrStrings As Integer = 2350
Private Const kVersion As Integer = 2

Private Sub class_initialize()
   IdNo = 0
   Name = "Module.cod"
   pgm_script = ""
   path = ""
   fileName = Name
   offset = 0
   m_bSaved = False
End Sub

Public Sub PrcOut()
   'none
End Sub

Public Sub Save()
   Write #1, "mod"
   Write #1, str(kVersion)
   Write #1, IdNo
   Write #1, GetRelativePath(gTarget.pathname, path)
   Write #1, Name
End Sub

Public Sub Restore()
Dim strTemp As String
Dim PathOrVersion

   Input #1, PathOrVersion 'code that can open old version without Version# field
   If Val(PathOrVersion) > 0 Then
      Input #1, m_nIdNo
      Input #1, path
   Else
      path = PathOrVersion
   End If
   
   SetFileName
   Input #1, strTemp
   OpenModule
End Sub

Public Sub OpenModule()
Dim res As Boolean

   'On Error GoTo fileNotFound
   'Open path For Input As #2
   'On Error GoTo 0
   'Input #2, pgm_script
   'Close #2
   res = ReadFile(path, pgm_script)
   If res Then
      pgm_script = Mid$(pgm_script, 2, Len(pgm_script) - 4)  'trim off quotes from each end
      ProcessScript pgm_script, FromDisk
      m_bSaved = True
   Else
      'fileNotFound: On Error GoTo 0
      MsgBox gStringTable(3252) + path '"Module not found."
      path = ""
   End If
End Sub

Public Sub SetFileName(Optional newPath As String = "")
   If Len(path) = 0 And Len(newPath) <> 0 Then
      path = newPath
   End If
   fileName = Mid(path, InStrRev(path, "\") + 1)
   Name = fileName
End Sub

Public Property Let IdNo(nIdNo As Integer)
   m_nIdNo = nIdNo
   If m_nIdNo Then Name = "Module" & IdNo
End Property

Public Property Get IdNo() As Integer
   IdNo = m_nIdNo
End Property

Public Sub GetProperty()
Static nProp As Integer

   If nProp = kTotalProps Then
      gPropInfo.Name = ""
      nProp = 0
      Exit Sub
   End If

   gPropInfo.Val = ""
   'Use pgReadOnly as default, it is most common
   gPropInfo.Type = pgReadOnly

   Select Case nProp
   Case 0: gPropInfo.Name = "Name"
   Case 1: gPropInfo.Name = "ID"
   Case 2: gPropInfo.Name = "Module Path"
   End Select
   gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "Name": GetPropertyVal = Name
   Case "ID": GetPropertyVal = IdNo
   Case "Module Path": GetPropertyVal = path
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim cMod As CCodeModule

   ValidateProperty = True
'   Select Case strProp
'   Case "Name"
'   Case "ID"
'   Case "Module Path"
'   End Select
End Function

Public Property Get GlobalID() As String
Attribute GlobalID.VB_UserMemId = 0
   GlobalID = "module|" + Me.path
End Property

Public Function GetScript(strScript As String, Optional bForceCreate As Boolean = True) As String
   GetScript = pgm_script
End Function

Public Function PutScript(ByVal strText As String, ByVal strScript As String) As Boolean
Dim strGID As String
Dim bDirty As Boolean

   bDirty = (pgm_script <> strText)
   If Not bDirty And Not m_bSaved And Len(strText) = 0 Then
      MsgBox gStringTable(3373) '"Project cannot contain an empty module"
      'ProjectRemoveModule Me
      strText = "'" & gStringTable(3373)
      PutScript = True
      Exit Function
   End If
   If Not m_bSaved Then
      bDirty = True
      frmMain.dlgCommonDialog.DialogTitle = "Save Module"
      frmMain.dlgCommonDialog.Filter = "Modules(*.cod)|*.cod"
      frmMain.dlgCommonDialog.DefaultExt = "cod"
      frmMain.dlgCommonDialog.fileName = path
      frmMain.dlgCommonDialog.flags = cdlOFNLongNames + cdlOFNNoReadOnlyReturn + cdlOFNOverwritePrompt
      frmMain.dlgCommonDialog.CancelError = True
      On Error GoTo gotCancel
      frmMain.dlgCommonDialog.ShowSave
      On Error GoTo 0
      If frmMain.dlgCommonDialog.fileName = "" Then
         Beep
         Exit Function
      End If
      strGID = GlobalID
      path = frmMain.dlgCommonDialog.fileName
      SetFileName
      If gbProjectExplorer Then gfProjectExplorer.UpdateObjectNode Me, strGID
   Else
      If Len(strText) = 0 Then
         MsgBox gStringTable(3373) '"Project cannot contain an empty module"
         'ProjectRemoveModule Me
         strText = "'" & gStringTable(3373)
         PutScript = True
         Exit Function
      End If
   End If
  
   If bDirty Then
      pgm_script = strText
      strGID = GlobalID
      
      ProcessScript strText, ToDisk
      On Error GoTo readonly
      Open path For Output As #2
      On Error GoTo 0
      Write #2, strText
      Close #2
      m_bSaved = True
      gfProjectExplorer.UpdateObjectNode Me, strGID
   End If
   PutScript = True
gotCancel:
   On Error GoTo 0
   Exit Function
readonly:
   MsgBox gStringTable(3413) 'Code module is read only. Changes not saved.
   Exit Function
End Function
