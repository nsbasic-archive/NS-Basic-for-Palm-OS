VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CResourceFile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'resource object
Option Explicit

Public Name As String     'ResourcefileIDNO

'MMD: Don't know what use this property is anymore, baggage for now...
Public filename As String 'only at runtime, extracted from fileName

Private m_nIdNo As Integer    'set when a resource is added to a project
Private m_Project As CProject
Private m_ResourceType As String
Private m_ResourcePath As String

Private Const kVersion As Integer = 1
Private Const kTotalProps As Integer = 4
Private Const kResStrings As Integer = 2201

Public Sub class_initialize()
Dim i As Integer

   Name = "Resource"
   filename = ""
   ResourceType = "DBIM"
   ResourcePath = ""
   m_nIdNo = 0
End Sub

Public Sub Save()
   Write #1, "resfile"
   Write #1, kVersion
   Write #1, Name
   Write #1, IdNo
   Write #1, ResourceType
   Write #1, GetRelativePath(gTarget.pathname, ResourcePath)
End Sub

Public Sub Restore()
Dim version As Integer
Dim nID As Integer

   Input #1, version
   If version <> kVersion Then
      MsgBox gStringTable(3307) + version '"Error: Invalid resource File Version (" & version & ")"
      End
   End If

   Input #1, Name
   Input #1, m_nIdNo
   Input #1, m_ResourceType
   Input #1, m_ResourcePath
   SetFileName ""
End Sub

Public Sub SetFileName(newPath As String)
   If Len(ResourcePath) = 0 And Len(newPath) <> 0 Then
      ResourcePath = newPath
   End If
   filename = Mid(ResourcePath, InStrRev(ResourcePath, "\") + 1)
End Sub

Public Property Let IdNo(ByVal nIdNo As Integer)
   m_nIdNo = nIdNo
   If m_nIdNo Then Name = "Resource" & m_nIdNo
End Property

Public Property Get IdNo() As Integer
   IdNo = m_nIdNo
End Property

Public Property Get Project() As CProject
   Set Project = m_Project
End Property

Public Property Let Project(prj As CProject)
   Set m_Project = prj
End Property

Public Property Get ResourceType() As String
   ResourceType = m_ResourceType
End Property

Public Property Let ResourceType(p As String)
   m_ResourceType = p
End Property

Public Property Get ResourcePath() As String
   ResourcePath = m_ResourcePath
End Property

Public Property Let ResourcePath(p As String)
   m_ResourcePath = p
End Property


Public Sub GetProperty()
Static nProp As Integer
Dim nIndex As Integer

   If nProp = kTotalProps Then
      gPropInfo.Name = ""
      nProp = 0
      Exit Sub
   End If

   Select Case nProp
   Case 0 'Name
      gPropInfo.Name = "(Name)"
      gPropInfo.Type = pgString
   Case 1 'ID
      gPropInfo.Name = "ID"
      'gPropInfo.Type = pgReadOnly
   Case 2 'Resource Type
      gPropInfo.Name = "Resource Type"
      gPropInfo.Type = pgString
   Case 3 'resource Path
      gPropInfo.Name = "Resource Path"
      gPropInfo.Type = pgOther
      gPropInfo.data = gStringTable(kResStrings) + ">" + m_ResourcePath
   End Select
   gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "(Name)": GetPropertyVal = Name
   Case "ID": GetPropertyVal = IdNo
   Case "Resource Type": GetPropertyVal = ResourceType
   Case "Resource Path": GetPropertyVal = ResourcePath
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim bmp As CResourceFile
Dim x As Integer

   ValidateProperty = True
   Select Case strProp
   Case "(Name)"
      'Make sure name is unique within the project

      If Not LegalObjectName(strVal) Then
         ValidateProperty = False
         Exit Function
      End If

      Name = strVal
   Case "ID"
      x = Val(strVal)
      If x < 0 Or x > 32767 Then InvalidProperty
      IdNo = x
   Case "Resource Type"
      strVal = Left(strVal & "....", 4)
      ResourceType = strVal
   Case "resource Path"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         ResourcePath = strVal
      End If
   End Select
   If ValidateProperty Then LocateProject(GlobalID).Dirty = True
End Function

Public Property Get GlobalID() As String
   GlobalID = Join(Array("resource", IdNo, m_Project.GlobalID), "|")
End Property
Public Sub GuessName()
Dim nameSoFar As String
Dim k As Integer
Dim bite As Byte

    On Error GoTo fileNotFound
    
    Open m_ResourcePath For Binary As #10
    On Error GoTo giveUp
    
    bite = 1    ' Just in case file is empty
    k = 0
    nameSoFar = ""
    Do While (Not EOF(10)) And (k < 32)
        Get #10, , bite
        If (bite >= 32) And (bite <= 127) Then   ' ASCII character
            nameSoFar = nameSoFar + Chr(bite)
        Else
            Exit Do
        End If
    Loop
    
    If (0 = bite) Then Name = nameSoFar
    
giveUp:
    Close #10
    
fileNotFound:
End Sub
Public Sub PrcOut(pathname)
Dim bite As Byte
Dim k As Integer
Dim nRecords As Integer
Dim localChunkID As Long
Dim correctID As Long
Dim foo As String
Dim i As Integer
Dim typ As String

'#If NSBSymbian Then
'   Exit Sub 'On Symbian, resources are installed as files, not embedded in .prc
'#End If

    ' EMP modified to extract libr resources
   correctID = -1

   'make sure file exists
   On Error GoTo fileNotFound
   Open GetAbsolutePath(pathname, "") For Input As #10
   On Error GoTo 0
   Close #10

   Open pathname For Binary As #10
   #If NSBSymbian Then
      If LOF(10) > 65520 Then
         Close #10
         Exit Sub
      End If
   #End If
   
   If m_ResourceType = "libr" Then
     ' Skip header
     For k = 1 To 76
        Get #10, , bite
     Next
     nRecords = 0
     Get #10, , bite
     nRecords = bite
     Get #10, , bite
     nRecords = nRecords * 256 + bite
     
     If (nRecords < 1) Then
         MsgBox gStringTable(3360) + pathname
     Else
         For i = 1 To nRecords
         
            'Find and read the resource
            typ = ""
            
            For k = 1 To 4
              Get #10, , bite
              typ = typ + Chr(bite)
            Next k
         
            For k = 1 To 2 ' Skip type and id
              Get #10, , bite
            Next k
            
            localChunkID = 0
            Get #10, , bite
            localChunkID = localChunkID * 256 + bite
            Get #10, , bite
            localChunkID = localChunkID * 256 + bite
            Get #10, , bite
            localChunkID = localChunkID * 256 + bite
            Get #10, , bite
            localChunkID = localChunkID * 256 + bite
            
            If typ = "libr" Then correctID = localChunkID
         Next i
         
         If (correctID >= 0) Then
         
             Close #10
             Open pathname For Binary As #10
             For k = 1 To correctID
                Get #10, , bite
             Next
             
             'Assume everything after this is the resource
            Do While Not EOF(10)
               Get #10, , bite
               Put #3, , bite
            Loop
        Else
           MsgBox gStringTable(3360) + pathname '"Error: Resource not found: " & PathName
        End If
        
     End If
   Else
    ' Plain binary file
   Do While Not EOF(10)
      Get #10, , bite
      Put #3, , bite
   Loop
   End If
allDone:
   Close #10
   Exit Sub

fileNotFound: On Error GoTo 0
   MsgBox gStringTable(3360) + pathname '"Error: Resource not found: " & PathName
End Sub


