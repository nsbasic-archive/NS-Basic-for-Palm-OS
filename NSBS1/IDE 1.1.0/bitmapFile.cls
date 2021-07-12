VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CBitmapFile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'bitmap object
Option Explicit

'MMD: Name is almost an irrelevancy, its never referred to...
Public Name As String     'BmpfileIDNO

'MMD: These would be easier to handle as an array with private variables
Private m_arrPaths(9) As String

'MMD: Don't know what use this property is anymore, baggage for now...
Public filename As String 'only at runtime, extracted from fileName

Private m_nIdNo As Integer    'set when a bitmap is added to a project
Private m_Project As CProject

'MMD: Why not bump version to 2, and put all code necessary for this object in here?
Private Const kVersion As Integer = 1
'2200 marks beginning of CBitmapFile string table entries
Private Const kResStrings As Integer = 2200
Private Const kErrStrings As Integer = 2250

#If NSBSymbian Then
Private Const kTotalProps As Integer = 6
#Else
Private Const kTotalProps As Integer = 12
#End If

Public Sub class_initialize()
Dim i As Integer

   Name = "Bitmap"
   For i = 0 To 9
      m_arrPaths(i) = ""
   Next
   filename = ""
   m_nIdNo = 0
End Sub

Public Sub Save()
   Write #1, "bmpfile"
   Write #1, kVersion
   Write #1, Name
   Write #1, IdNo

   SaveImages m_arrPaths(0), m_arrPaths(1), m_arrPaths(2), m_arrPaths(3), m_arrPaths(4), m_arrPaths(5), m_arrPaths(6), m_arrPaths(7), m_arrPaths(8), m_arrPaths(9)
End Sub

Public Sub Restore()
Dim version As Integer
Dim nID As Integer
Dim p1 As String
Dim p2 As String
Dim p3 As String
Dim p4 As String
Dim p5 As String
Dim filename As String

Dim p1h As String
Dim p2h As String
Dim p3h As String
Dim p4h As String
Dim p5h As String
p1 = ""
p2 = ""
p3 = ""
p4 = ""
p5 = ""
p1h = ""
p2h = ""
p3h = ""
p4h = ""
p5h = ""

   Input #1, version
   If version <> kVersion Then
      MsgBox gStringTable(3307) + version '"Error: Invalid Bitmap File Version (" & version & ")"
      End
   End If

   Input #1, Name
   Input #1, m_nIdNo

   RestoreImages p1, p2, p3, p4, p5, p1h, p2h, p3h, p4h, p5h
   PathName1 = p1
   PathName2 = p2
   PathName4 = p3
   PathName8 = p4
   PathName16 = p5
   PathName1h = p1h
   PathName2h = p2h
   PathName4h = p3h
   PathName8h = p4h
   PathName16h = p5h
   
   SetFileName ""
   #If NSBSymbian Then
      'If we load a Palm project into Symbian, we have to deal with the issue that
      'it may have a 1 bit bitmap and no 8 bit one (the minimum for Symbian)
      'If so, copy the best lower bitmap image to 8 bit so it appears properly
      If PathName8 = "" Then
         If PathName1 <> "" Then PathName8 = PathName1
         If PathName2 <> "" Then PathName8 = PathName2
         If PathName4 <> "" Then PathName8 = PathName4
      End If
      If PathName8h = "" Then
         If PathName1h <> "" Then PathName8 = PathName1h
         If PathName2h <> "" Then PathName8 = PathName2h
         If PathName4h <> "" Then PathName8 = PathName4h
      End If
      PathName1 = ""
      PathName2 = ""
      PathName4 = ""
      PathName1h = ""
      PathName2h = ""
      PathName4h = ""
   #End If
   
End Sub

Function bmpGetByte(fil As Integer) As Integer  '10.26.00 GH function rewritten
Dim b As Byte

   Get #fil, , b
   bmpGetByte = b
End Function

Function bmpGetShort(fil As Integer) As Integer  '10.26.00 GH function rewritten
Dim b1 As Byte
Dim b2 As Byte
Dim res As Integer
  
   Get #fil, , b1
   Get #fil, , b2
   res = b2 * 256# + b1
   bmpGetShort = res
End Function

Function bmpGetLong(fil As Integer) As Long '10.26.00 GH function rewritten
Dim res As Long
Dim b1 As Byte
Dim b2 As Byte
Dim b3 As Byte
Dim b4 As Byte

   Get #fil, , b1
   Get #fil, , b2
   Get #fil, , b3
   Get #fil, , b4
   res = b4 * 16777216# + b3 * 65536# + b2 * 256# + b1
   bmpGetLong = res
End Function

Public Sub SetFileName(newPath As String)
'For Palm, default to 1 bit BW, low res
'For Symbian, default to 8bit hi res

#If NSBSymbian Then
   If Len(PathName8h) = 0 And Len(newPath) <> 0 Then
      PathName8h = newPath
   End If
   filename = Mid(PathName8h, InStrRev(PathName8h, "\") + 1)
#Else
   If Len(PathName1) = 0 And Len(newPath) <> 0 Then
      PathName1 = newPath
   End If
   filename = Mid(PathName1, InStrRev(PathName1, "\") + 1)
#End If
End Sub

Public Property Let IdNo(ByVal nIdNo As Integer)
   m_nIdNo = nIdNo
   If m_nIdNo Then Name = "Bitmap" & m_nIdNo
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

Public Property Let PathName1(ByVal strPath As String)
   m_arrPaths(0) = strPath
End Property

Public Property Get PathName1() As String
   PathName1 = m_arrPaths(0)
End Property

Public Property Let PathName2(ByVal strPath As String)
   m_arrPaths(1) = strPath
End Property

Public Property Get PathName2() As String
   PathName2 = m_arrPaths(1)
End Property

Public Property Let PathName4(ByVal strPath As String)
   m_arrPaths(2) = strPath
End Property

Public Property Get PathName4() As String
   PathName4 = m_arrPaths(2)
End Property

Public Property Let PathName8(ByVal strPath As String)
   m_arrPaths(3) = strPath
End Property

Public Property Get PathName8() As String
   PathName8 = m_arrPaths(3)
End Property
Public Property Let PathName16(ByVal strPath As String)
   m_arrPaths(4) = strPath
End Property

Public Property Get PathName16() As String
   PathName16 = m_arrPaths(4)
End Property

'HiRes bitmaps..................................................


Public Property Let PathName1h(ByVal strPath As String)
   m_arrPaths(5) = strPath
End Property

Public Property Get PathName1h() As String
   PathName1h = m_arrPaths(5)
End Property

Public Property Let PathName2h(ByVal strPath As String)
   m_arrPaths(6) = strPath
End Property

Public Property Get PathName2h() As String
   PathName2h = m_arrPaths(6)
End Property

Public Property Let PathName4h(ByVal strPath As String)
   m_arrPaths(7) = strPath
End Property

Public Property Get PathName4h() As String
   PathName4h = m_arrPaths(7)
End Property

Public Property Let PathName8h(ByVal strPath As String)
   m_arrPaths(8) = strPath
End Property

Public Property Get PathName8h() As String
   PathName8h = m_arrPaths(8)
End Property
Public Property Let PathName16h(ByVal strPath As String)
   m_arrPaths(9) = strPath
End Property

Public Property Get PathName16h() As String
   PathName16h = m_arrPaths(9)
End Property

Public Sub GetProperty()
Static nProp As Integer
Dim nIndex As Integer
Dim HiRes As String

   If nProp = kTotalProps Then
      gPropInfo.Name = ""
      nProp = 0
      Exit Sub
   End If

   HiRes = ""
   Select Case nProp
   Case 0 'Name
      gPropInfo.Name = "(Name)"
      gPropInfo.Type = pgString
   Case 1 'ID
      gPropInfo.Name = "ID"
      gPropInfo.Type = pgReadOnly
   #If NSBSymbian = 1 Then
   Case 2: gPropInfo.Name = "Path,  8-bit"
   Case 3: gPropInfo.Name = "Path, 16-bit"
   Case 4: gPropInfo.Name = "Path, HiRes  8-bit"
   Case 5: gPropInfo.Name = "Path, HiRes 16-bit"
   #Else
   Case 2: gPropInfo.Name = "Path,  1-bit"
   Case 3: gPropInfo.Name = "Path,  2-bit"
   Case 4: gPropInfo.Name = "Path,  4-bit"
   Case 5: gPropInfo.Name = "Path,  8-bit"
   Case 6: gPropInfo.Name = "Path, 16-bit"
   Case 7: gPropInfo.Name = "Path, HiRes  1-bit"
   Case 8: gPropInfo.Name = "Path, HiRes  2-bit"
   Case 9: gPropInfo.Name = "Path, HiRes  4-bit"
   Case 10: gPropInfo.Name = "Path, HiRes  8-bit"
   Case 11: gPropInfo.Name = "Path, HiRes 16-bit"
   #End If
   End Select
   
   If nProp >= 2 Then
      gPropInfo.data = gStringTable(kResStrings) + ">" + m_arrPaths(nProp - 2)
      gPropInfo.Type = pgOther
   End If
   gPropInfo.Val = GetPropertyVal(gPropInfo.Name)
   nProp = nProp + 1
End Sub

Public Function GetPropertyVal(ByVal strProp As String) As String
   Select Case strProp
   Case "(Name)": GetPropertyVal = Name
   Case "ID": GetPropertyVal = IdNo
   #If NSBSymbian = 0 Then
   Case "Path,  1-bit": GetPropertyVal = m_arrPaths(0)
   Case "Path,  2-bit": GetPropertyVal = m_arrPaths(1)
   Case "Path,  4-bit": GetPropertyVal = m_arrPaths(2)
   Case "Path,  8-bit": GetPropertyVal = m_arrPaths(3)
   Case "Path, 16-bit": GetPropertyVal = m_arrPaths(4)
   Case "Path, HiRes  1-bit": GetPropertyVal = m_arrPaths(5)
   Case "Path, HiRes  2-bit": GetPropertyVal = m_arrPaths(6)
   Case "Path, HiRes  4-bit": GetPropertyVal = m_arrPaths(7)
   Case "Path, HiRes  8-bit": GetPropertyVal = m_arrPaths(8)
   Case "Path, HiRes 16-bit": GetPropertyVal = m_arrPaths(9)
   #Else
   Case "Path,  8-bit": GetPropertyVal = m_arrPaths(3)
   Case "Path, 16-bit": GetPropertyVal = m_arrPaths(4)
   Case "Path, HiRes  8-bit": GetPropertyVal = m_arrPaths(8)
   Case "Path, HiRes 16-bit": GetPropertyVal = m_arrPaths(9)
   #End If
   End Select
End Function

Public Function ValidateProperty(ByVal strProp As String, ByVal strVal As String) As Boolean
Dim bmp As CBitmapFile

   ValidateProperty = True
   Select Case strProp
   Case "(Name)"
      'Make sure name is unique within the project
      For Each bmp In m_Project.BitmapCollection
         If StrComp(strVal, bmp.Name, vbTextCompare) = 0 Then
            MsgBox gStringTable(kErrStrings) & "'" & strVal & "'", vbCritical + vbOKOnly
            ValidateProperty = False
            Exit Function
         End If
      Next

      If Not LegalObjectName(strVal) Then
         ValidateProperty = False
         Exit Function
      End If

      Name = strVal
   Case "ID"
   Case "Path,  1-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(0) = strVal
      End If
   Case "Path,  2-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(1) = strVal
      End If
   Case "Path,  4-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(2) = strVal
      End If
   Case "Path,  8-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(3) = strVal
      End If
   Case "Path, 16-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(4) = strVal
      End If
   'HiRes
   Case "Path, HiRes  1-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(5) = strVal
      End If
   Case "Path, HiRes  2-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(6) = strVal
      End If
   Case "Path, HiRes  4-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(7) = strVal
      End If
   Case "Path, HiRes  8-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(8) = strVal
      End If
   Case "Path, HiRes 16-bit"
      strVal = UnQuote(strVal)
      If Dir(strVal) = "" Then
         InvalidProperty
         ValidateProperty = False
      Else
         m_arrPaths(9) = strVal
      End If
   End Select
   If ValidateProperty Then LocateProject(GlobalID).Dirty = True
End Function

Public Property Get GlobalID() As String
Attribute GlobalID.VB_UserMemId = 0
   GlobalID = Join(Array("bitmap", IdNo, m_Project.GlobalID), "|")
End Property
