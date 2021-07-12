VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CExternalLibrary"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public m_strLibObj As String
'Public m_strInfPath As String
Public m_strPrcName As String
Public m_idno As Integer
Public m_arrGlobalMethods As Collection
Public Sub class_initialize()
   m_strLibObj = ""
'   m_strLocalLib = ""
   m_strPrcName = ""
   m_idno = -1
   Set m_arrGlobalMethods = New Collection
End Sub
Public Function LoadNewLibrary(strInfPath As String, strLibObj As String) As Boolean
   ' Added by EMP to support new format
   Dim WhileState As Integer  '0=Open File, 1=Got PrcName, 2=GlobalMethods 3=PrivateMethods, 4=InfVers
   Dim strLine As Variant
   Dim strFileContents As String
   Dim astrFileContents() As String
   Dim vMethodParams As Variant
   Dim strMethodName As String
   Dim oldLibrary As Boolean
   Dim vers As String

   oldLibrary = False
   LoadNewLibrary = False

   m_strLibObj = strLibObj

   'open the file
   If ReadFile(filedirectory + "\lib\" + strInfPath, strFileContents) Then
      astrFileContents = Split(strFileContents, vbCrLf)
   
      ' Now, try to loop through file, reading
      On Error GoTo ParseError
      WhileState = 0
      
      For Each strLine In astrFileContents
         If ((Left(strLine, 1) <> ";") And (Len(strLine) > 0)) Then
            If StrComp(Left(strLine, 7), "infvers", vbTextCompare) = 0 Then
                vers = Mid(strLine, 9, 1)
            End If
            Select Case WhileState
            Case 0 ' Open File, looking for line beginning with "PrcName"
               If StrComp(Left(strLine, 7), "prcname", vbTextCompare) = 0 Then
                  m_strPrcName = Trim(Mid(strLine, Len("prcname=") + 1))
                  If StrComp(Right(m_strPrcName, 4), ".prc", vbTextCompare) = 0 Then
                     m_strPrcName = Left(m_strPrcName, Len(m_strPrcName) - 4)
                  End If
                  WhileState = 1
               End If
            Case 1 ' Got PrcName, Looking for line beginning with "[GlobalMethods]"
               If StrComp(Left(strLine, 15), "[GlobalMethods]", vbTextCompare) = 0 Then WhileState = 2
            Case 2 ' In Global Methods section, add methods until "[PrivateMethods]"
               If StrComp(Left(strLine, 16), "[PrivateMethods]", vbTextCompare) = 0 Then
                  WhileState = 3
               Else
                  ' Add method
                 If (Not AddNewMethod(strLine)) Then
                      If vers = "2" Then GoTo ParseError
                      oldLibrary = True
                      If (Not AddMethod(strLine)) Then GoTo ParseError
                  End If
               End If
            Case 3 ' In Private Methods section, add methods until next section/EOF
               If (Left(strLine, 1) = "[") Then
                  WhileState = 4
               Else
                  ' Add method
                  If (Not AddNewMethod(strLine)) Then
                      oldLibrary = True
                      If (Not AddMethod(strLine)) Then GoTo ParseError
                  End If
               End If
            End Select
         End If
       Next
      
       LoadNewLibrary = True

   Else
      'print_err gStringTable(3222) + strInfPath '"Unable to open Library Information File " + strInfPath)
      LoadNewLibrary = False
   End If
   Exit Function

ParseError:
   print_err gStringTable(3223) + strInfPath + " " + strLine + " " + strLine
   '"Invalid method declaration in Library Declaration File: "
   Close #1
   LoadNewLibrary = False
End Function  'LoadNewLibrary

Private Function AddMethod(ByVal strLine As String) As Boolean
   Dim vTemp As Variant
   Dim strTemp As String
   Dim meth As New CExternalLibraryMethod
   AddMethod = False

   ' Fill a new method structure, first token is separated by "="
   vTemp = Split(strLine, "=")
   If (UBound(vTemp) < 1) Then Exit Function
   strTemp = LCase(Trim(vTemp(0)))
   strTemp = Replace(strTemp, vbTab, "")
   meth.strname = strTemp

   ' Rebuild any separated comments from Split on =
   vTemp(0) = ""
   strTemp = Mid(Join(vTemp, "="), 2)
   
   ' Remaining tokens are separated by ","
   vTemp = Split(strTemp, ",")
   If (UBound(vTemp) < 2) Then Exit Function
   meth.nProc = Val(vTemp(0))

   ' Proc(Sub) returns no value, Func returns a value
   strTemp = LCase(Trim(vTemp(1)))
   strTemp = Replace(strTemp, vbTab, "")
   If strTemp = "proc" Or strTemp = "sub" Then
      meth.nMethodType = 0
   Else
      meth.nMethodType = 1
   End If
   meth.nParams = Val(vTemp(2))

   ' Now do the optionals
   If (UBound(vTemp) > 2) Then
      meth.strHelp = Trim(vTemp(3))
      If (UBound(vTemp) > 3) Then
         'meth.strArgTypes = vTemp(4)
      End If
   End If

   'Add structure to methods collection
   m_arrGlobalMethods.Add meth, meth.strname
   AddMethod = True
End Function  'AddMethod
Private Function GuessType(inout As String, typ As String)
   ' EMP
   GuessType = ""
   
   Select Case typ
      Case "integer", "int32", "int4", "long", "uint32", "uint4"
          GuessType = "i4"
      Case "string", "char"
          GuessType = "s0"
      Case "double", "flt8", "flt64", "date", "time"
          GuessType = "n8"
      Case "float", "single", "flt4", "flt32", "database"
          GuessType = "n4"
      Case "short", "int16", "int2", "int", "uint16", "uint2"
          GuessType = "i2"
      Case "variant"
          GuessType = "v0"
   End Select
   
   If (inout = "out" Or inout = "inout") Then
       GuessType = UCase(GuessType)
    End If
   
   
End Function
Private Function ParseHelp(meth As CExternalLibraryMethod, isFunc As Boolean) As Boolean
   ' EMP
   Dim help As String
   Dim cut1 As Variant
   Dim cut2 As Variant
   Dim args As Variant
   Dim tokens As Variant
   Dim funcNameAndVar As String
   Dim funcName As String
   Dim k As Integer
   Dim i As Integer
   Dim state As Integer '0: expecting in/out 1: expecting var 2: expecting as 3: expecting type
   Dim inout As String
   Dim var As String
   Dim typ As String
   Dim token As String
   Dim arg As String
   Dim guessedType As String
   Dim firstArg As Integer
   
   ParseHelp = False
   
   meth.strArgTypes = ""
   
   help = meth.strHelp
   
   cut1 = Split(help, "(")
   
   If (UBound(cut1) < 1) Then Exit Function
   
   funcNameAndVar = LCase(Trim(cut1(0)))
   
   cut2 = Split(funcNameAndVar, "=")
   
   If (UBound(cut2) > 0) Then
       funcName = Trim(cut2(UBound(cut2)))
   Else
       funcName = funcNameAndVar
   End If
   
   If (Not (funcName = meth.strname)) Then Exit Function
   
   cut1 = Split(cut1(1), ")")
   
   ' Get the args to test for context
   args = Split(cut1(0), ",")
   
   firstArg = 0
   
   If (UBound(args) > 0) Then
      If (LCase(Trim(args(0)) = "context")) Then
          firstArg = 1
          meth.strArgTypes = meth.strArgTypes + "xx"
      End If
      
   End If
   
   'So far name is OK, check return argument
      
   If isFunc Then
       If (UBound(cut1) <= 0) Then
           Exit Function
       End If
      'It should be a function, if it has an as as the return
   
        tokens = Split(cut1(1), " ")
        
        state = 2
        For k = 0 To UBound(tokens)
           token = LCase(Trim(tokens(k)))
           If (Not token = "") Then
              Select Case state
              Case 0
                 If (token = "in" Or token = "out" Or token = "inout") Then
                     inout = token
                     state = 1
                 Else ' Assume it's in
                    inout = "in"
                    k = k - 1
                    state = 1
                 End If
              Case 1
                 var = token
                 state = 2
              Case 2
                 If (Not token = "as") Then
                     Exit Function
                 End If
                 state = 3
              Case 3
                 typ = token
                 state = 999
              End Select
           End If
        Next k
                
        If (Not state = 999) Then
           Exit Function
        End If
        
        meth.strArgTypes = meth.strArgTypes + GuessType(inout, typ)
   End If
   
   
   ' Now check the args
   For i = firstArg To UBound(args)
      arg = Trim(args(i))
      tokens = Split(arg, " ")
      
      state = 0
      
        For k = 0 To UBound(tokens)
           token = LCase(Trim(tokens(k)))
           If (Not token = "") Then
              Select Case state
              Case 0
                 If (token = "in" Or token = "out" Or token = "inout") Then
                     inout = token
                     state = 1
                 Else ' Assume it's in
                    inout = "in"
                    k = k - 1
                    state = 1
                 End If
              Case 1
                 var = token
                 state = 2
              Case 2
                 If (Not token = "as") Then
                     Exit Function
                 End If
                 state = 3
              Case 3
                 typ = token
                 state = 999
              End Select
           End If
        Next k
                
        If (Not state = 999) Then
           Exit Function
        End If
        
        meth.strArgTypes = meth.strArgTypes + GuessType(inout, typ)
   Next i
   
   ParseHelp = True
End Function
Private Function AddNewMethod(ByVal strLine As String) As Boolean
   Dim vTemp As Variant
   Dim vTemp2 As Variant
   Dim strTemp As String
   Dim meth As New CExternalLibraryMethod
   AddNewMethod = False
   
   ' EMP because comment may contain comma, split on " first
   vTemp2 = Split(strLine, """")
   If (UBound(vTemp2) < 1) Then Exit Function
   
   ' Fill a new method structure, first token is separated by "="
   
   vTemp = Split(vTemp2(0), "=")
   
   If (UBound(vTemp) < 1) Then Exit Function
   strTemp = LCase(Trim(vTemp(0)))
   strTemp = Replace(strTemp, vbTab, "")
   meth.strname = strTemp

   ' Rebuild any separated comments from Split on =
   vTemp(0) = ""
   strTemp = Mid(Join(vTemp, "="), 2)
   
   ' Remaining tokens are separated by ","
   vTemp = Split(strTemp, ",")
   If (UBound(vTemp) < 2) Then Exit Function
   meth.nProc = Val(vTemp(0))

   ' Proc(Sub) returns no value, Func returns a value
   strTemp = LCase(Trim(vTemp(1)))
   strTemp = Replace(strTemp, vbTab, "")
   If strTemp = "proc" Or strTemp = "sub" Then
      meth.nMethodType = 0
   Else
      meth.nMethodType = 1
   End If
   meth.nParams = Val(vTemp(2))

   ' Now do the optionals
   If (UBound(vTemp2) > 1) Then
      meth.strHelp = vTemp2(1)
      
      ' Parse the help comments
      If (Not ParseHelp(meth, meth.nMethodType = 1)) Then Exit Function
   End If

   'Add structure to methods collection
   m_arrGlobalMethods.Add meth, meth.strname
   AddNewMethod = True
End Function  'AddNewMethod
Public Function GetProcNum(strname As String) As Integer
   Dim elm As CExternalLibraryMethod
   GetProcNum = -1

   On Error Resume Next
   Set elm = m_arrGlobalMethods(strname)
   If (err <> 0) Then Exit Function
   GetProcNum = elm.nProc
End Function  'GetProcNum
Public Function GetArgTypes(strname As String) As String
' EMP added
   Dim elm As CExternalLibraryMethod
   GetArgTypes = ""

   On Error Resume Next
   Set elm = m_arrGlobalMethods(strname)
   If (err <> 0) Then Exit Function
   GetArgTypes = elm.strArgTypes
End Function  'GetProcNum
Public Function GetNumProcArgs(strname As String) As Integer
   Dim elm As CExternalLibraryMethod
   GetNumProcArgs = -1

   On Error Resume Next
   Set elm = m_arrGlobalMethods(strname)
   If (err <> 0) Then Exit Function
   GetNumProcArgs = elm.nParams
End Function 'GetNumProcArgs
Public Property Let IdNo(new_idno As Integer)
   m_idno = new_idno
End Property 'SET idno
Public Property Get IdNo() As Integer
   IdNo = m_idno
End Property  'GET idno
Public Property Get PrcName() As String
   PrcName = m_strPrcName
End Property  'GET PrcName
