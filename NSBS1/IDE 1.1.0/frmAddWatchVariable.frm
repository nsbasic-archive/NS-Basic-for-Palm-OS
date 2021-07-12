VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmAddWatchVariable 
   Caption         =   "Add a Watch Variable"
   ClientHeight    =   6510
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   5745
   LinkTopic       =   "Form1"
   ScaleHeight     =   6510
   ScaleWidth      =   5745
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.TreeView Tree 
      Height          =   5655
      Left            =   240
      TabIndex        =   1
      Top             =   720
      Width           =   5295
      _ExtentX        =   9340
      _ExtentY        =   9975
      _Version        =   393217
      Style           =   7
      ImageList       =   "ImageList1"
      Appearance      =   1
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   4680
      Top             =   120
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   13
      ImageHeight     =   13
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   3
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmAddWatchVariable.frx":0000
            Key             =   "nonsubscriptedVariable"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmAddWatchVariable.frx":00FA
            Key             =   "subscriptedVariableClosed"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmAddWatchVariable.frx":01F4
            Key             =   "subscriptedVariableOpen"
         EndProperty
      EndProperty
   End
   Begin VB.Label Label1 
      Caption         =   "Pick a variable to add to the watch list......"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4335
   End
End
Attribute VB_Name = "frmAddWatchVariable"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'entire form is new 04012005

Dim startIndex As Integer
Private Sub Form_Resize()
'MMD: Yeah, this is broken again... ha ha ha
   If Me.WindowState = vbMinimized Then Exit Sub  '02/11/2001 MMD

   If Me.Height >= 360 Then
      With Tree
         .Left = 0
         .Top = 0
         .Width = Me.ScaleWidth
         .Height = Me.ScaleHeight
      End With
   End If
End Sub
Private Sub addIt()
    'this routine has just a few changes 06112005 and they are marked individually
    Dim s1 As Integer
    Dim s2 As Integer
    Dim s3 As Integer
    
    Dim d As CDataElement
    Dim n As Integer
    Dim i As Integer  'added 06112005
    Dim lim1 As Integer
    Dim lim2 As Integer
    Dim lim3 As Integer
    Dim startIndex As Integer
    
    'startIndex = kStringWorkDEMax + kArithWorkDEMax + gTotalNSBvars + 1
    '06112005 startIndex = kStringWorkDEMax + kArithWorkDEMax + 1
     
    n = 0
    If Tree.SelectedItem.Tag > 0 Then    'modified 06112005
        'start additions 06112005
        'make sure selected var not already in list of watch variables
        For i = 1 To frmWatchVariables.Tree.Nodes.count
            If frmWatchVariables.Tree.Nodes(i).Tag = Tree.SelectedItem.Tag Then
                MsgBox gStringTable(3423) '"The selected variable is already in the watch variable list to be viewed."
                Exit Sub
            End If
        Next
        'endadditions 06112005
        needToRefreshWatchVars = True
        s1 = 1
        s2 = 1
        s3 = 1
        
       Set d = gTarget.DataCollection(Tree.SelectedItem.Tag)   'modified 06112005
       lim1 = d.max_no_values1
       If lim1 = 0 Then lim1 = 1
       lim2 = d.max_no_values2
       If lim2 = 0 Then lim2 = 1
       lim3 = d.max_no_values3
       If lim3 = 0 Then lim3 = 1
       
       For s1 = 1 To lim1
         For s2 = 1 To lim2
           For s3 = 1 To lim3
                If lim1 > 1 Then
                    strs1 = str(s1)
                Else
                    strs1 = ""
                End If
                If lim2 > 1 Then
                    strs2 = str(s2)
                    strs1 = strs1 + ","
                Else
                    strs2 = ""
                End If
                If lim3 > 1 Then
                    strs3 = str(s3)
                    strs2 = strs2 + ","
                Else
                    strs3 = ""
                End If
        
                If s1 <= 1 And s2 <= 1 And s3 <= 1 Then
          
                    If lim1 > 1 Or lim2 > 1 Or lim3 > 1 Then
                        Set debuggerLastVariableNode = frmWatchVariables.Tree.Nodes.Add(, tvwLast, , frmMain.formatTree(d.LocalSource, d.Name, "(Subscripted array)"), "subscriptedVariableClosed", "subscriptedVariableOpen")
                        debuggerLastVariableNode.Tag = 0
                        
                        Set debuggerLastSubscriptNode = frmWatchVariables.Tree.Nodes.Add(debuggerLastVariableNode, tvwChild, , frmMain.formatTree(d.LocalSource, d.Name + "(" + strs1 + strs2 + strs3 + ") ", "(Value)"), "nonsubscriptedVariable", "nonsubscriptedVariable")
                        debuggerLastSubscriptNode.Tag = d.tbl_no
                        n = n + 1
                    Else
                        Set debuggerLastVariableNode = frmWatchVariables.Tree.Nodes.Add(, tvwLast, , frmMain.formatTree(d.LocalSource, d.Name, "(Value)"), "nonsubscriptedVariable", "nonsubscriptedVariable")
                        debuggerLastVariableNode.Tag = d.tbl_no

                        n = n + 1
                    End If
                Else
                    Set debuggerLastSubscriptNode = frmWatchVariables.Tree.Nodes.Add(debuggerLastSubscriptNode, tvwLast, , frmMain.formatTree(d.LocalSource, d.Name + "(" + strs1 + strs2 + strs3 + ")", "(Value)"), "nonsubscriptedVariable", "nonsubscriptedVariable")
                    debuggerLastSubscriptNode.Tag = d.tbl_no
                    n = n + 1
                  
                End If
                 
          Next
        Next
      Next
    End If
        
End Sub

Private Sub Form_Load()
 
    'this routine changed drastically 06112005
    
    'Note to George -06112005 -- previously, this form had a listbox to display variables to choose from.
    '                            now, it has a tree (see form designer)
Dim s As String
Dim i As Integer
Dim n As Integer
Dim d As CDataElement
Dim highestN As Integer
 
Dim tempLocalID As String
Dim tempVarName As String
Dim tempDataElemNo As Integer

Dim lastModuleNode As Node
Dim debuggerLastSubscriptNode As Node

Dim s1 As Integer
Dim s2 As Integer
Dim s3 As Integer

Dim strs1 As String
Dim strs2 As String
Dim strs3 As String

 Dim lst As ListImage
     
     debuggerlastvariableid = 1
Set debuggerLastSubscriptNode = Nothing
Set debuggerLastVariableNode = Nothing

  Tree.Nodes.Clear

 
'format the showVariables tree grid prior to asking for the values
'also chg the tree to sort global vars plus include a node for each module's work vars

'first--build arrays that can be sorted
i = gTarget.DataCollection.count - (kStringWorkDEMax + kArithWorkDEMax)
ReDim svLocalIDs(i)
ReDim svVarNames(i)
ReDim svDataElemNos(i)
n = 0
For i = (kStringWorkDEMax + kArithWorkDEMax) + 1 To gTarget.DataCollection.count
    Set d = gTarget.DataCollection(i)
    
    If Left(d.Name, 1) = "+" _
    Or Left(d.Name, 1) = "." _
    Or Left(d.Name, 3) = "swb" And d.isConstant = True _
    Or Left(d.Name, 3) = "nsb" And d.isConstant = True _
    Or Mid(d.Name, 1, 2) = ">>" Then
       GoTo ContinueLoop    'ignore numeric & alpha literals and typeDefs
    End If
    n = n + 1
    If d.LocalOrGlobal = "g" Then
        svLocalIDs(n) = ""
        svVarNames(n) = d.Name
        svDataElemNos(n) = i
    Else
        svLocalIDs(n) = d.LocalSource
        svVarNames(n) = d.Name
        svDataElemNos(n) = i
    End If
ContinueLoop:
 Next
 highestN = n
'now, sort the vars to moduleName,varname
 n = 1
 For i = 1 To highestN - 1
    For n = i + 1 To highestN
       If svLocalIDs(n) < svLocalIDs(i) _
       Or (svLocalIDs(n) = svLocalIDs(i)) And (svVarNames(n) < svVarNames(i)) Then
           'switch entries
           tempLocalID = svLocalIDs(i)
           tempVarName = svVarNames(i)
           tempDataElemNo = svDataElemNos(i)
           
           svLocalIDs(i) = svLocalIDs(n)
           svVarNames(i) = svVarNames(n)
           svDataElemNos(i) = svDataElemNos(n)
           
           svLocalIDs(n) = tempLocalID
           svVarNames(n) = tempVarName
           svDataElemNos(n) = tempDataElemNo
           
        End If
    Next
 Next
 'now, actually build the tree (except for subscript entries)
 For i = 1 To highestN
    Set d = gTarget.DataCollection(svDataElemNos(i))
 
    If i = 1 Or svLocalIDs(i) <> svLocalIDs(i - 1) Then
        'make new module name node
        Set lastModuleNode = Tree.Nodes.Add( _
                            , tvwLast, , frmMain.formatTree(d.LocalSource, "", _
                            "(Subr/Func Name)"), "nonsubscriptedVariable", "nonsubscriptedVariable")
        lastModuleNode.Tag = 0
    End If
             
    Set debuggerLastVariableNode = Tree.Nodes.Add( _
                            lastModuleNode, tvwChild, , formatWatchNames(d.LocalSource, d.Name), _
                            "nonsubscriptedVariable", "nonsubscriptedVariable")
    debuggerLastVariableNode.Tag = svDataElemNos(i)
             
Next
End Sub
Function formatWatchNames(source As String, varname As String)
   srcWidth = frmWatchVariables.Tree.Width / 4
   varNameWidth = frmWatchVariables.Tree.Width / 2
   s = source
   If source = "" Then source = "Global"
   frmWatchVariables.font = frmWatchVariables.Tree.font
       
   Do While frmWatchVariables.TextWidth(s) < srcWidth
      s = s + "."
   Loop
    
   s = s + varname
   formatWatchNames = s
End Function
Private Sub lstVars_Click()
    addIt
End Sub
'06112005 Private Sub lstVars_Click()
'06112005    addIt
'06112005End Sub
 
'this routine added 06112005
Private Sub Tree_Click()
    addIt
End Sub
