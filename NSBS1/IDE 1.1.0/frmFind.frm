VERSION 5.00
Begin VB.Form frmFind 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Find"
   ClientHeight    =   2505
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7785
   Icon            =   "frmFind.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2505
   ScaleWidth      =   7785
   StartUpPosition =   1  'CenterOwner
   Begin VB.CheckBox chkWholeWord 
      Caption         =   "1132[Find Whole Word &Only]"
      Height          =   255
      Left            =   2280
      TabIndex        =   8
      Tag             =   "1132"
      Top             =   1080
      Width           =   3255
   End
   Begin VB.CheckBox chkMatchCase 
      Caption         =   "1133[Match Ca&se]"
      Height          =   255
      Left            =   2280
      TabIndex        =   9
      Tag             =   "1133"
      Top             =   1440
      Width           =   3255
   End
   Begin VB.CommandButton butReplaceAll 
      Caption         =   "1137[Replace &All]"
      Height          =   375
      Left            =   6000
      TabIndex        =   13
      Tag             =   "1137"
      Top             =   1800
      Width           =   1695
   End
   Begin VB.CommandButton butReplace 
      Caption         =   "1136[&Replace]"
      Height          =   375
      Left            =   6000
      TabIndex        =   12
      Tag             =   "1136"
      Top             =   1320
      Width           =   1695
   End
   Begin VB.CommandButton butCancel 
      Cancel          =   -1  'True
      Caption         =   "1135[Cancel]"
      Height          =   375
      Left            =   6000
      TabIndex        =   11
      Tag             =   "1135"
      Top             =   600
      Width           =   1695
   End
   Begin VB.CommandButton butFindNext 
      Caption         =   "1134[Find &Next]"
      Default         =   -1  'True
      Height          =   375
      Left            =   6000
      TabIndex        =   10
      Tag             =   "1134"
      Top             =   120
      Width           =   1695
   End
   Begin VB.OptionButton optSelected 
      Caption         =   "1131[Selected &Text]"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Tag             =   "1131"
      Top             =   2040
      Width           =   1455
   End
   Begin VB.OptionButton optProject 
      Caption         =   "1130[&Current Project]"
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Tag             =   "1130"
      Top             =   1560
      Width           =   1455
   End
   Begin VB.OptionButton optModule 
      Caption         =   "1129[Current &Module]"
      Height          =   495
      Left            =   240
      TabIndex        =   5
      Tag             =   "1129"
      Top             =   1080
      Width           =   1455
   End
   Begin VB.TextBox txtReplace 
      Height          =   285
      Left            =   2280
      TabIndex        =   3
      Top             =   480
      Width           =   3495
   End
   Begin VB.TextBox txtFind 
      Height          =   285
      Left            =   2280
      TabIndex        =   1
      Top             =   120
      Width           =   3495
   End
   Begin VB.Frame Frame1 
      Caption         =   "1128[Search]"
      Height          =   1575
      Left            =   120
      TabIndex        =   4
      Tag             =   "1128"
      Top             =   840
      Width           =   1815
   End
   Begin VB.Label lblReplace 
      Caption         =   "1127[Replace &With:]"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Tag             =   "1127"
      Top             =   525
      Width           =   2055
   End
   Begin VB.Label lblFind 
      Caption         =   "1126[&Find What:]"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Tag             =   "1126"
      Top             =   165
      Width           =   2055
   End
End
Attribute VB_Name = "frmFind"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim saveCod As CCodeModule
Dim saveModel As CProject
Dim saveMnu As CMenuElem
Dim saveView As CForm
Dim saveObj As Object
Dim origType As String
Dim searchStart As Long
Dim searchLength As Long
Dim searchCnt As Long
Dim searchType As String
Dim searchPos As Long
Dim origComplete As Boolean
Dim m_Form As Form
Private m_strFind As String
Private m_strReplace As String
Private m_idSearchStart As String            'Replacing firstSearchModule
Private m_bSearchFound As Boolean            'Replacing searchNotFoundSw
Private m_rSearchStart As CodeMax4Ctl.range   'Replacing searchStart

Private Sub butCancel_Click()
   Unload Me
'   frmCode.Refresh
End Sub

Private Sub Form_Load()
'   gbNewFind = True
   LoadResStrings Me
   If m_Form Is Nothing Then
      optModule.Enabled = False
      optProject.Value = True
      optSelected.Enabled = False
   Else
      optModule.Enabled = True
      If typename(m_Form) = "frmCode" Then
         If m_Form.GetSel().IsEmpty Then
            'Nothing is selected, so disable selection searches, and set search scope to previously used
            optSelected.Enabled = False
            If gnFindFlags And kFindModule Then
               optModule.Value = True
            Else
               optProject.Value = True
            End If
         Else
            'Something is selected, so default to a selection search
            optSelected.Enabled = True
            optSelected.Value = True
         End If
         txtFind.Text = m_Form.GetFindText
      Else 'typename(m_Form) = "frmPalmScreen"
         'Palm Screen search, so disable selection searches, and set search scope to previously used
         optSelected.Enabled = False
         If gnFindFlags And kFindProject Then
            optProject.Value = True
         Else
            optModule.Value = True
         End If
         txtFind.Text = gstrFind
      End If
   End If
   m_strFind = txtFind.Text
   txtReplace.Text = gstrReplace
   m_strReplace = txtReplace.Text
End Sub

Private Function butCommon_Click(bReplace As Boolean) As Boolean
Dim proj As CProject
Dim nFlags As Integer
Dim i As Integer
Dim strSearchStart As String
Dim arrStr() As String

   'Get find and replace strings, set globals and determine if this is a new search
   gstrFind = txtFind.Text
   If Len(gstrFind) = 0 Then Exit Function
   If bReplace Then
      gstrReplace = txtReplace.Text
      If gstrFind <> m_strFind Or gstrReplace <> m_strReplace Then gbNewFind = True
      m_strReplace = gstrReplace
   Else
      If gstrFind <> m_strFind Then gbNewFind = True
   End If
   m_strFind = gstrFind

   'Get flags, set global and determine if this is a new search
   If optModule Then
      nFlags = kFindModule
   ElseIf optProject Then
      nFlags = kFindProject
   Else
      nFlags = kFindSelected
      Set gSearchSel = m_Form.GetSel
   End If
   If chkMatchCase Then nFlags = nFlags + kFindCase
   If chkWholeWord Then nFlags = nFlags + kFindWord
   If nFlags <> gnFindFlags Then
      gbNewFind = True
      gnFindFlags = nFlags
   End If

   'If this is a new search, set start point, current point, and scope
   If gbNewFind Or gnSearchLoc < 0 Then
      If m_Form Is Nothing Then
         'We're searching the whole project
         Set proj = ActiveProject
         garrSearchMap = proj.BuildMap
      Else
         'Find project, and set scope according to find flags and/or current form type
         If gnFindFlags And kFindProject Then
            Set proj = LocateProject(m_Form.GlobalID)
            If proj Is Nothing Then
               garrSearchMap = Array(m_Form.GlobalID)
            Else
               garrSearchMap = proj.BuildMap
            End If
         Else
            'Since we have a form, the search start is always that form
            If typename(m_Form) = "frmCode" Then
               m_Form.PutTheCodeBack
               garrSearchMap = Split(m_Form.GlobalID, ">")
            Else 'typename(m_Form) = "frmPalmScreen"
               garrSearchMap = m_Form.Object.BuildMap
            End If
         End If
      End If

      'If search scope is project, locate starting index in search map, otherwise use 0
      gnSearchStart = 0
      If (gnFindFlags And kFindProject) And Not (m_Form Is Nothing) Then
         If typename(m_Form) = "frmCode" Then
            strSearchStart = m_Form.GlobalID
         Else 'typename(m_Form) = "frmPalmScreen"
            arrStr = m_Form.Object.BuildMap
            strSearchStart = arrStr(0)
         End If
            
         For i = 0 To UBound(garrSearchMap)
            If garrSearchMap(i) = strSearchStart Then
               gnSearchStart = i
               Exit For
            End If
         Next
      End If
      gnSearchLoc = gnSearchStart
      gnReplaceCount = 0
   End If
   butCommon_Click = True
End Function

Private Sub butFindNext_click()
   If Not butCommon_Click(False) Then
      Beep
      Exit Sub
   End If
   If Not FindNext Then
      If Not gbFindAny Then
         MsgBox gStringTable(3320), vbExclamation '"Search text is not found"
         gbNewFind = True
      Else
         If gnSearchLoc < 0 Then
            MsgBox gStringTable(3321), vbInformation + vbOKOnly ' "End of search reached"
            gbNewFind = True
            Unload Me
         End If
      End If
   Else
      'Only look in selected text for the first occurence
      If gnFindFlags And kFindSelected Then
         optModule = True
         gnFindFlags = gnFindFlags + kFindModule - kFindSelected
      End If
   End If
End Sub

Private Sub butReplace_Click()
Dim frm As frmCode

   If Not butCommon_Click(True) Then
      Beep
      Exit Sub
   End If
   
      CMaxPrepFindReplace frmMain.cmaxFind
      If Not frmMain.ActiveForm Is Nothing Then
         If typename(frmMain.ActiveForm) = "frmCode" Then
            Set frm = frmMain.ActiveForm
            frmMain.cmaxFind.Text = frm.Text
            frmMain.cmaxFind.SetSel frm.GetSel, True
            gbFindOne = False
            frmMain.cmaxFind.ExecuteCmd cmCmdReplace, 0
            If gbFindOne Then
               frm.Text = frmMain.cmaxFind.Text
               frm.SetSel frmMain.cmaxFind.GetSel(True)
               frm.PutTheCodeBack
            End If
         Else
            FindNext
         End If
      Else
         FindNext
      End If
End Sub

Private Sub butReplaceAll_Click()
Dim frm As frmCode
Dim i As Integer
Dim bRepl As Boolean
Dim nIndex As Long
   
   'Screw elegance!

   If Not butCommon_Click(True) Then
      Beep
      Exit Sub
   End If
   
   gbReplaceAll = True
   CMaxPrepFindReplace frmMain.cmaxFind
   If gnFindFlags And kFindSelected Then
      Set frm = frmMain.GetMDIChild(garrSearchMap(0))
      nIndex = frm.Editor.GetTopIndex(frm.Editor.CurrentView)
      frmMain.bCMaxFindFlag = True
      frmMain.cmaxFind.Text = GetScript(garrSearchMap(0))
      frmMain.bCMaxFindFlag = False
      frmMain.cmaxFind.SetSel frm.Editor.GetSel(True), True
'      frmMain.cmaxFind.ExecuteCmd cmCmdFindMarkAll, 0
'      frmMain.cmaxFind.ExecuteCmd cmCmdBookmarkJumpToFirst
'      bRepl = frmMain.cmaxFind.GetBookmark(frmMain.cmaxFind.GetSel(True).StartLineNo)
'      frmMain.cmaxFind.ExecuteCmd cmCmdBookmarkClearAll, 0
'      frmMain.cmaxFind.SetSel frm.Editor.GetSel(True), True
      gbReplaceChange = False
      frmMain.cmaxFind.ExecuteCmd cmCmdReplaceAllInSelection, 0
      If gbReplaceChange Then
         frm.Dirty = True
      frm.Text = frmMain.cmaxFind.Text
      frm.PutTheCodeBack
      End If
      frm.Editor.SetTopIndex frm.Editor.CurrentView, nIndex
   Else
      For i = 0 To UBound(garrSearchMap)
         'First do the replace offscreen
         'MMD!: This looks like it gets code from the object, not ensuring that the
         'MMD!: most recently updated version (the editor) is used.
         frmMain.cmaxFind.Text = GetScript(garrSearchMap(i))
         If Not frmMain.cmaxFind.Text = "" Then
            frmMain.cmaxFind.ExecuteCmd cmCmdReplaceAllInBuffer, 0
            'Now, if the window was open, lets put the new text in there and put the text away
            Set frm = frmMain.GetMDIChild(garrSearchMap(i))
            If Not frm Is Nothing Then
               nIndex = frm.Editor.GetTopIndex(frm.Editor.CurrentView)
               frm.Text = frmMain.cmaxFind.Text
               frm.Dirty = True
               frm.PutTheCodeBack
               frm.Editor.SetTopIndex frm.Editor.CurrentView, nIndex
            Else
               PutScript frmMain.cmaxFind.Text, garrSearchMap(i)
            End If
         End If
      Next
   End If
   gbReplaceAll = False
End Sub

Public Property Let Form(frm As Form)
Dim rng As CodeMax4Ctl.range

   Set m_Form = frm
   If typename(frm) = "frmCode" Then
      Set rng = frm.Editor.GetSel(True)
      ' Put any selected text into find field
      If rng.StartLineNo <> rng.EndLineNo Then
         rng.EndLineNo = rng.StartLineNo
         rng.EndColNo = Len(frm.Editor.GetLine(rng.StartLineNo))
         txtFind.Text = frm.Editor.GetText(rng)
         gbNewFind = True
      ElseIf rng.StartColNo <> rng.EndColNo Then
         txtFind.Text = frm.Editor.GetText(rng)
         optModule = True
         gbNewFind = True
      End If
   End If
End Property

Public Property Let FindReplace(bFindReplace As Boolean)
   lblReplace.Visible = bFindReplace
   txtReplace.Visible = bFindReplace
   butReplace.Visible = bFindReplace
   butReplaceAll.Visible = bFindReplace
   If bFindReplace Then
      Me.caption = gStringTable(1304)
      butFindNext.Enabled = Not optSelected.Value
      butReplace.Enabled = Not optSelected.Value
   Else
      Me.caption = gStringTable(1303)
   End If
End Property

Private Sub optModule_Click()
   'Find next always enabled on Find Dialog
   If Not butReplace.Visible Then Exit Sub
   butFindNext.Enabled = Not optSelected.Value
   butReplace.Enabled = Not optSelected.Value
End Sub

Private Sub optProject_Click()
   'Find next always enabled on Find Dialog
   If Not butReplace.Visible Then Exit Sub
   butFindNext.Enabled = Not optSelected.Value
   butReplace.Enabled = Not optSelected.Value
End Sub

Private Sub optSelected_Click()
   'Find next always enabled on Find Dialog
   If Not butReplace.Visible Then Exit Sub
   butFindNext.Enabled = Not optSelected.Value
   butReplace.Enabled = Not optSelected.Value
End Sub

Private Sub txtFind_GotFocus()
   txtFind.SelStart = 0
   txtFind.SelLength = Len(txtFind.Text)
End Sub

Private Sub txtReplace_GotFocus()
   txtReplace.SelStart = 0
   txtReplace.SelLength = Len(txtReplace.Text)
End Sub
