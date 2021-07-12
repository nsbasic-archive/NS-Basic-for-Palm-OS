Attribute VB_Name = "MNSBCodeMax"
Option Explicit

'This module does all the CodeMax stuff

Global Const CM_NSB_EDITSELECTALL = 4400
Global Const CM_NSB_EDITFIND = 4401
Global cmGlobals As CodeMax4Ctl.Globals
Global cmLanguage As New CodeMax4Ctl.Language

Const kKeywords = " Let If Then Else ElseIf EndIf Do Loop Exit For Next GoTo" & _
" GoSub Return NextScreen NextForm Select Case Stop Where" & _
" Sub Function End Call" & _
" CreateWindow DestroyWindow DrawBitmap DrawChars DrawLine" & _
" DrawRectangle EraseWindow FillRectangle SetCurrentWindow Redraw" & _
" Beep Chain Cursor Id Define Delay Display MsgBox" & _
" MenuDraw MenuErase MenuReset SetEventHandled Sound PlaySound" & _
" Global Dim as Type Byte Database Date Double Float Integer Short" & _
" Single String SysTrapSub SysTrapFunc Time Variant Creator With Keyed" & _
" nsbOn nsbOff nsbChecked nsbUnchecked nsbNormal nsbCustom" & _
" nsbInverted nsbGrey nsbGray True False" & _
" nsbKeyOrButton nsbPenDown nsbPenUp nsbWait nsbNoWait nsbSerialIn nsbHandEraJog" & _
" nsbYes nsbNo"

Const kOperators = "^  -  *  /  \  +  =  <>  <  >  <=  >=  Mod  Is  Like  And  Eqv  Imp  Not  Or  Xor"
Const kIntrinsics = "bmp but chk fld gad shf grd lbl lst pop cho rpt scr sel sli"

Sub CreateLanguage()
Dim trace As Boolean
trace = True
   If trace Then MsgBox "CreateLanguage " & 1
   '--------------------------------------
   ' create A new language
   'Dim l As New CodeMax4Ctl.Language
   #If NSBSymbian Then
      cmLanguage.Name = "NS Basic/Symbian OS"
   #Else
      cmLanguage.Name = "NS Basic/Palm"
   #End If
   ' Basic allows parameter blocks to start with whitespace
   cmLanguage.WhitespaceAsParamBlock = True
   cmLanguage.WordChars = "[\w]"

   '--------------------------------------
   ' create a 'Whitespace' scope tokenset.
   ' this is necessary so we can support
   ' parameter blocks that start with whitespace
   ' instead of '('
   Dim Whitespace As New CodeMax4Ctl.TokenSet
   Whitespace.Name = "Whitespace"
   Whitespace.id = cmTsIdWhitespace
   ' Whitespace can exist at the global scope
   Call Whitespace.ValidScopes.Add(Nothing)
   ' define the whitespace token
   Call Whitespace.tokens.Add("\s+", True)
   ' add 'Whitespace' to the language
   Call cmLanguage.TokenSets.Add(Whitespace)
   If trace Then MsgBox "CreateLanguage " & 2
    
    '--------------------------------------
    ' create a 'Scope Keywords' scope tokenset
    Dim ScopeKeywords As New CodeMax4Ctl.TokenSet
    ScopeKeywords.id = cmTsIdScopeKeywords
    ScopeKeywords.Type = CodeMax4Ctl.cmTokenSetType.cmTsTypeScope
    ScopeKeywords.Name = "Scope Keywords"
    ScopeKeywords.CaseSensitive = False
    ScopeKeywords.NormalizeCase = True
    ' Scopes keywords can be nested or exist at the global scope
    Call ScopeKeywords.ValidScopes.Add(ScopeKeywords)
    Call ScopeKeywords.ValidScopes.Add(Nothing)
    ScopeKeywords.ForeColor = RGB(0, 0, 255) ' blue
    ' scopes can autoindent
    ScopeKeywords.AutoIndent = True
    ScopeKeywords.tokens.Add ("{")
    ScopeKeywords.Tokens2.Add ("}")
    ScopeKeywords.tokens.Add ("[")
    ScopeKeywords.Tokens2.Add ("]")
    ScopeKeywords.tokens.Add ("For")
    ScopeKeywords.Tokens2.Add ("Next")
    ScopeKeywords.tokens.Add ("Do")
    ScopeKeywords.Tokens2.Add ("Loop")
    ScopeKeywords.tokens.Add ("With")
    ScopeKeywords.Tokens2.Add ("End With")
    ScopeKeywords.tokens.Add ("Function")
    ScopeKeywords.Tokens2.Add ("End Function")
    ScopeKeywords.tokens.Add ("Class")
    ScopeKeywords.Tokens2.Add ("End Class")
    ScopeKeywords.tokens.Add ("Sub")
    ScopeKeywords.Tokens2.Add ("End Sub")
    ScopeKeywords.tokens.Add ("If")
    ScopeKeywords.Tokens2.Add ("End If")
    ' add 'Scope Keywords' to the language
    Call cmLanguage.TokenSets.Add(ScopeKeywords)
    Call Whitespace.ValidScopes.Add(ScopeKeywords)
    If trace Then MsgBox "CreateLanguage " & 3

    '--------------------------------------
    ' create an empty 'Text' tokenset as a catch-all
    ' for text in all scopes
    ' Note: this is added later to the language
    ' definition because it has the lowest precedence.
    ' we create it now so it can be referenced by
    ' other tokensets
    Dim Text As New CodeMax4Ctl.TokenSet
    Text.Name = "Text"
    Text.id = cmTsIdText
    Call Text.ValidScopes.Add(ScopeKeywords)
    Call Text.ValidScopes.Add(Nothing)
   If trace Then MsgBox "CreateLanguage " & 4

    '--------------------------------------------
    ' create a 'Parameter Block' scope tokenset.
    ' This is necessary for CodeMax to automatically
    ' support Parameter Info toolTips.
    '--------------------------------------------
    Dim ParamBlock As New CodeMax4Ctl.TokenSet
    ParamBlock.Name = "Parameter Block"
    ParamBlock.id = cmTsIdParameterBlocks
    ParamBlock.Type = cmTsTypeScope
    
    ' Parameter block keywords are valid within 'Scope Keywords',
    ' other parameter blocks, and the global scope
    Call ParamBlock.ValidScopes.Add(ScopeKeywords)
    Call ParamBlock.ValidScopes.Add(ParamBlock)
    Call ParamBlock.ValidScopes.Add(Nothing)
    ParamBlock.Hidden = True    'this tokenset is hidden -- the user should be able to change its properties
    ParamBlock.InheritFrom = Text 'inherit color settings from 'Text'
    Dim t As CodeMax4Ctl.IToken
    If trace Then MsgBox "CreateLanguage " & 5
   
    Set t = ParamBlock.tokens.Add("(")
    t.Action = cmCmdParameterInfo   'invoke parameter help when starting a parameter block
    Set t = ParamBlock.Tokens2.Add(")")
    t.Action = cmCmdCommitMember   'commit the selected member in a popup when closing a parameter block
    ' add this scope to the language
    Call cmLanguage.TokenSets.Add(ParamBlock)

    '--------------------------------------
    ' create a 'Comments' scope tokenset
    Dim Comments As New CodeMax4Ctl.TokenSet
    Comments.Name = "Comments"
    Comments.id = cmTsIdLineComments
    Comments.Type = CodeMax4Ctl.cmTokenSetType.cmTsTypeScope
    'Comments.FontStyle = cmFontItalic
    
    ' comments can be nested within scope keywords
    ' or exist at the global scope
    Call Comments.ValidScopes.Add(ScopeKeywords)
    Call Comments.ValidScopes.Add(Nothing)
    Comments.ForeColor = RGB(0, 128, 0) ' green
    Comments.tokens.Add ("'")
    Comments.tokens.Add ("Rem")
    ' add 'Comments' to the language
    Call cmLanguage.TokenSets.Add(Comments)
   If trace Then MsgBox "CreateLanguage " & 6

   '----------------------------------------------------------------------
    ' create a 'Escape Sequences' tokenset for embedded quotes in strings
    Dim EscSequence As New CodeMax4Ctl.TokenSet
    EscSequence.Name = "Escape Sequences"
    EscSequence.id = cmTsIdEscapeSeqs
    EscSequence.ForeColor = RGB(0, 128, 0) ' green
    EscSequence.tokens.Add (Chr$(34) + Chr$(34))
    ' add 'EscSequence' to the language
    Call cmLanguage.TokenSets.Add(EscSequence)

    '--------------------------------------
    ' create a 'Strings' scope tokenset
    Dim Strings As New CodeMax4Ctl.TokenSet
    Strings.Name = "Strings"
    Strings.id = cmTsIdStrings
    Strings.Type = CodeMax4Ctl.cmTokenSetType.cmTsTypeScope
    Strings.CaseSensitive = False
    Strings.NormalizeCase = True
    ' Strings can be nested within scope keywords
    ' or exist at the global scope
    Call Strings.ValidScopes.Add(ScopeKeywords)
    Call Strings.ValidScopes.Add(ParamBlock)
    Call Strings.ValidScopes.Add(Nothing)
    Strings.ForeColor = vbRed 'vbMagenta 'RGB(0, 255, 0) ' green
    Call Strings.tokens.Add(Chr(34))   ' double quotes (")
    Call Strings.Tokens2.Add(Chr(34))   ' double quotes (")
    ' add 'Strings' to the language
    Call cmLanguage.TokenSets.Add(Strings)
   If trace Then MsgBox "CreateLanguage " & 7

    ' EscSequence can be nested within strings
    Call EscSequence.ValidScopes.Add(Strings)

    '--------------------------------------
    ' create a 'Keywords' list tokenset
    Dim Keywords As New CodeMax4Ctl.TokenSet
    Dim keywordList() As String, d As String, i As Integer
    Keywords.Name = "Keywords"
    Keywords.id = cmTsIdKeywords
    Keywords.CaseSensitive = False
    Keywords.NormalizeCase = True
    ' keywords are valid within 'Scope Keywords'
    ' and the global scope
    Call Keywords.ValidScopes.Add(ScopeKeywords)
    Call Keywords.ValidScopes.Add(Nothing)
    Keywords.ForeColor = RGB(0, 0, 255)    ' blue
    'Keywords.FontStyle = CodeMax4CtcmLanguagecmFontStyle.cmFontBold
    keywordList = Split(kKeywords)
    For i = 1 To UBound(keywordList)
      Call Keywords.tokens.Add(keywordList(i))
    Next
    ' add 'Keywords' to the language
    Call cmLanguage.TokenSets.Add(Keywords)
    
    '--------------------------------------
    ' create a 'Variables' list tokenset
    Dim Variables As New CodeMax4Ctl.TokenSet
    Dim VariablesList() As String
    Variables.Name = "Variables"
    Variables.id = cmTsIdVariables
    Variables.CaseSensitive = False
    Variables.NormalizeCase = True
    ' variables are valid within 'Scope Keywords'
    ' and the global scope
    Call Variables.ValidScopes.Add(ScopeKeywords)
    Call Variables.ValidScopes.Add(Nothing)
    Keywords.ForeColor = RGB(0, 0, 255)    ' blue
    'Keywords.FontStyle = CodeMax4CtcmLanguagecmFontStyle.cmFontBold
    VariablesList = Split("my George hENNE")
    For i = 1 To UBound(VariablesList)
      Call Variables.tokens.Add(VariablesList(i))
    Next
    ' add 'Variables' to the language
    Call cmLanguage.TokenSets.Add(Variables)
    
    '--------------------------------------
    ' create an 'Operators' list tokenset
    Dim Operators As New CodeMax4Ctl.TokenSet
    Dim operatorList() As String
    Operators.Name = "Operators"
    Operators.id = cmTsIdOperators
    Operators.CaseSensitive = False
    Operators.NormalizeCase = True
    ' Operators are valid within 'Scope Keywords', 'parameter blocks' and the global scope
    Call Operators.ValidScopes.Add(ScopeKeywords)
    Call Operators.ValidScopes.Add(ParamBlock)
    Call Operators.ValidScopes.Add(Nothing)
    Dim tok As CodeMax4Ctl.IToken
    Set tok = Operators.tokens.Add(".")
    tok.Action = cmCmdListMembers 'invoke a memberlist when '.' is typed
    Set tok = Operators.tokens.Add("=")
    tok.Action = cmCmdCommitMember 'commit the selected member in a popup when finishing a parameter
    operatorList = Split(kOperators)
    For i = 1 To UBound(operatorList)
      Call Operators.tokens.Add(operatorList(i))
    Next
    ' add 'Operators' to the language
    Call cmLanguage.TokenSets.Add(Operators)
   If trace Then MsgBox "CreateLanguage " & 8

    '--------------------------------------------
    ' create a 'Argument Separater' scope tokenset.
    ' This is necessary for CodeMax to support bolding
    ' of the current parameter in a Parameter Info
    ' tooltip.
    '--------------------------------------------
    Dim ArgSep As New CodeMax4Ctl.TokenSet
    ArgSep.Name = "Argument Separators"
    ArgSep.id = cmTsIdArgSeparators
    ArgSep.CaseSensitive = False
    ArgSep.NormalizeCase = True
    
    ' argument separators are only valid within parameter blocks
    Call ArgSep.ValidScopes.Add(Nothing)
    Call ArgSep.ValidScopes.Add(ParamBlock)
    Call ArgSep.ValidScopes.Add(ScopeKeywords)
    ArgSep.Hidden = True    'this tokenset is hidden -- the user should be able to change its properties
    ArgSep.InheritFrom = Text 'inherit color settings from 'Text'
    Set t = ArgSep.tokens.Add(",")
    t.Action = cmCmdCommitMember   'commit the selected member in a popup when finishing a parameter
    ' add this scope to the language
    Call cmLanguage.TokenSets.Add(ArgSep)

    ' add the 'text' tokenset as the last tokenset
    ' in the language so it will have the lowest
    ' precedence and therefore not override all
    ' other tokensets
    Call cmLanguage.TokenSets.Add(Text)
   If trace Then MsgBox "CreateLanguage " & 9

    '--------------------------------------
    ' make the language available to the user
    Call cmLanguage.Register
   If trace Then MsgBox "CreateLanguage " & 10

   '--------------------------------------
   ' create a memberlist for the Err global
   ' variable so we can hand it to CodeMax
   ' at a later time in OnQueryMemberList().
   ' We could create this memberlist on the fly
   ' every time OnQueryMemberList() is called, but
   ' since this memberlist is static and won't change,
   ' we might as well construct it now for the best
   ' performance later.
   Dim ErrMethods As New CodeMax4Ctl.MemberList
   Dim mem As CodeMax4Ctl.IMember
   
   ErrMethods.Name = "Err Methods"
   ErrMethods.Language = cmLanguage
   ErrMethods.CaseSensitive = False
    
   Set mem = ErrMethods.Add("Clear", "", cmImgMethod)
      mem.HelpString = "Clear the error information"
   Set mem = ErrMethods.Add("Description", "", cmImgProperty)
      mem.HelpString = "Textual description of the error"
   Set mem = ErrMethods.Add("Source", "", cmImgProperty)
      mem.HelpString = "error source"
   Set mem = ErrMethods.Add("Number", "", cmImgProperty)
      mem.HelpString = "The error code number"
   Set mem = ErrMethods.Add("Raise", "Raise(Number, [Source[, Description[, HelpFile[, HelpDescription]]]])", cmImgMethod)
      mem.HelpString = "force an error"
   Call ErrMethods.Register
   If trace Then MsgBox "CreateLanguage " & 11
    
   '--------------------------------------
   ' create a memberlist for global functions.
   Dim GblMethods As New CodeMax4Ctl.MemberList
   Dim s As String
   Dim strKey As String
   Dim p As Integer
   Dim comment As String
   
   GblMethods.Language = cmLanguage
   GblMethods.Name = "Global Methods"
   GblMethods.CaseSensitive = False
   For i = 100 To 299
      s = gStringTable(i)
      If Left(s, 13) = "String Table:" Then Exit For
      comment = ""
      p = InStr(s, "'")
      If p Then
         comment = Mid(s, p + 1)
         s = Left(s, p - 2)
      End If
      
      strKey = Split(Split(Split(s, " ")(0), "[")(0), "(")(0)
      Set mem = GblMethods.Add(strKey, s, cmImgMethod)
      mem.HelpString = comment
   Next
   Call GblMethods.Register
   If trace Then MsgBox "CreateLanguage " & 12

   '------------------------------------------
   ' create member lists for intrinsic objects
   Dim intrinMems As CodeMax4Ctl.MemberList
   Dim strsIntrinsics() As String, strTrinsic As String
   Dim strsMems() As String
   Dim objSic As Object
   Dim j As Integer
   
   strsIntrinsics = Split(kIntrinsics & " frm", " ")
   For i = 0 To UBound(strsIntrinsics) - 1
      If trace Then MsgBox "CreateLanguage 12 " & strsIntrinsics(i) & " 1"

      Set objSic = CreateObjectEx(strsIntrinsics(i))
      If trace Then MsgBox "CreateLanguage 12 " & strsIntrinsics(i) & " 1.1"
      Set intrinMems = New CodeMax4Ctl.MemberList
      If trace Then MsgBox "CreateLanguage 12 " & strsIntrinsics(i) & " 2"
      intrinMems.Language = cmLanguage
      intrinMems.Name = strsIntrinsics(i)
      intrinMems.CaseSensitive = False
      strsMems = objSic.PropertyList
      If trace Then MsgBox "CreateLanguage 12 " & strsIntrinsics(i) & " 3"
      For j = 0 To UBound(strsMems)
         Set mem = intrinMems.Add(strsMems(j), "", cmImgProperty)
         'mem.helpstring = foo
         Set mem = Nothing
      Next
      If trace Then MsgBox "CreateLanguage 12 " & strsIntrinsics(i) & " 4"
      intrinMems.Add "Left", "", cmImgProperty
      intrinMems.Add "Top", "", cmImgProperty
      intrinMems.Add "Width", "", cmImgProperty
      intrinMems.Add "Height", "", cmImgProperty
      strsMems = objSic.MethodList
      If trace Then MsgBox "CreateLanguage 12 " & strsIntrinsics(i) & " 5"
      For j = 0 To UBound(strsMems)
         Set mem = intrinMems.Add(strsMems(j), "", cmImgMethod)
         'mem.helpstring = foo
         Set mem = Nothing
      Next
      If trace Then MsgBox "CreateLanguage 12 " & strsIntrinsics(i) & " 6"
      Call intrinMems.Register
      Set objSic = Nothing
      Set intrinMems = Nothing
      If trace Then MsgBox "CreateLanguage 12 " & strsIntrinsics(i) & " 7"
   Next
   If trace Then MsgBox "CreateLanguage " & 13

End Sub

'Let's set CodeMax and Code Window stuffs here... once
Sub MNSBCodeMax_Initialize()
Dim hotKey As New CodeMax4Ctl.hotKey
Dim trace As Boolean
trace = True
   
   If trace Then MsgBox "MNSBCodeMax_Initialize " & 1
   If Not cmGlobals Is Nothing Then
      MsgBox "MNSBCodeMax_Initialize recall"
      Exit Sub
   End If
   Set cmGlobals = New CodeMax4Ctl.Globals

   'Unregister some built-in CodeMax shortcuts
   hotKey.Modifiers1 = 2
   'Ctrl+F Find...
   hotKey.VirtKey1 = "F"
   hotKey.Unbind
   'Ctrl+H Replace...
   hotKey.VirtKey1 = "H"
   hotKey.Unbind
   'Ctrl+V Paste
   hotKey.VirtKey1 = "V"
   hotKey.Unbind
   'Ctrl+X Cut
   hotKey.VirtKey1 = "X"
   hotKey.Unbind
   'Ctrl+Z Undo
   hotKey.VirtKey1 = "Z"
   hotKey.Unbind

   'Ctrl+A Edit->Select All
   'Call cmGlobals.RegisterCommand(CM_NSB_EDITSELECTALL, "Select All", "Selects all text in the active pane.")
   hotKey.VirtKey1 = "A"
   'Call cmGlobals.RegisterHotKey(hotKey, CM_NSB_EDITSELECTALL)

   'Register Find, Find Next, Replace
'   Call CMGlobals.RegisterCommand(cmCmdFind, "NS Basic Find", "Help out NS Basic Find")
'   Call CMGlobals.UnregisterCommand(cmCmdFind)
   If trace Then MsgBox "MNSBCodeMax_Initialize " & 2
   
   MNSBCodeMax_CreateNSBasicLanguage
   If trace Then MsgBox "MNSBCodeMax_Initialize " & 3

End Sub

Sub MNSBCodeMax_CreateNSBasicLanguage()
   Dim d As String
   Dim nsbLang As CodeMax4Ctl.Language

CreateLanguage
Exit Sub

   Set nsbLang = New CodeMax4Ctl.Language
   nsbLang.CaseSensitive = True

   'Create KeyWords list
   '05.A Arithmetic Commands
   d = "Let"
   '05.B Control and Logic Commands
   d = d & " If Then Else ElseIf EndIf Do Loop Exit For Next GoTo"
   d = d & " GoSub Return NextScreen NextForm Select Case Stop Where"
   '05.C Module Definition and Control Commands
   d = d & " Sub Function End Call"
   '05.D Screen Graphics Commands
   d = d & " CreateWindow DestroyWindow DrawBitmap DrawChars DrawLine"
   d = d & " DrawRectangle EraseWindow FillRectangle SetCurrentWindow Redraw"
   '05.E Miscellaneous Commands
   d = d & " Beep Chain Cursor Id Define Delay Display MsgBox"
   d = d & " MenuDraw MenuErase MenuReset SetEventHandled Sound playsound"
   'Data types
   d = d & " Global Dim as Type Byte Database Date Double Float Integer Short"
   d = d & " Single String Time Variant Creator With Keyed"
   'NSB Constants
   d = d & " nsbOn nsbOff nsbChecked nsbUnchecked nsbNormal nsbcustom"
   d = d & " nsbInverted nsbGrey nsbGray True False"
   d = d & " nsbKeyOrButton nsbPenDown nsbPenUp nsbWait nsbNoWait nsbSerialIn nsbHandEraJog"
   d = d & " nsbYes nsbNo"
   'Assign KeyWords list
   nsbLang.Keywords = d

   'Create Scope Keywords list
'   nsbLang.ScopeKeywords1 = Replace("Sub-Function", "-", nSep)
'   nsbLang.ScopeKeywords2 = Replace("End Sub-End Function", "-", nSep)

   'Create Operators list
   d = "/ * + - = ! % # $ & And Or Not"
'   For Each prop In gCodeProps
'     d$ = d$ & nSep$ & CStr(prop)
'   Next
   'Assign Operators list
   nsbLang.Operators = d

'**** Misc
   nsbLang.SingleLineComments = Chr(39) ' "'"
   nsbLang.MultiLineComments1 = Chr(19)
   nsbLang.MultiLineComments2 = Chr(20)
   nsbLang.ScopeKeywords1 = "" '{ in C style
   nsbLang.ScopeKeywords2 = "" '} in C style
   nsbLang.StringDelims = Chr$(34) ' """
   nsbLang.EscapeChar = ""
   nsbLang.TerminatorChar = ""

'**** Register the language into the globals props using the Language class "nsbLang"
   cmGlobals.UnregisterAllLanguages
   Call cmGlobals.RegisterLanguage("NSBasic", nsbLang)
End Sub

'Sub MNSBCodeMax_SavePrefs(Control As codeMax4Ctl.CodeMax)
'   Dim oldhKey As Long
'   Dim oldSubKey As String
'
'   oldhKey = MWinReg.hKey
'   MWinReg.hKey = HKEY_CURRENT_USER
'   oldSubKey = MWinReg.SubKey
'   MWinReg.SubKey = "Software\NSBasic\Palm\Editor"
'   With Control
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "ColorSyntax", .ColorSyntax
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "EnableHSplitter", .EnableHSplitter
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "EnableVSplitter", .EnableVSplitter
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "HScrollVisible", .HScrollVisible
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "VScrollVisible", .VScrollVisible
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "AutoIndentMode", .AutoIndentMode
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "SmoothScrolling", .SmoothScrolling
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "LineToolTips", .LineToolTips
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "DisplayLeftMargin", .DisplayLeftMargin
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "EnableColumnSel", .EnableColumnSel
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "EnableDragDrop", .EnableDragDrop
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "ExpandTabs", .ExpandTabs
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "TabSize", .TabSize
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "SetColor", .GetColor(cmClrHighlightedLine)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "FontName", .font.Name
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "FontCharset", .font.Charset
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "FontSize", .font.Size
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "SelBounds", .SelBounds
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "SetFontStyle", .GetFontStyle(cmStyText)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "SetCommentStyle", .GetFontStyle(cmStyComment)
'      'SetRegValue MWinReg.hKey, MWinReg.SubKey, "SetAllBookmarks", .SetAllBookmarks
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "SetLineNumbering", .LineNumbering
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "SetLineNumberStart", .LineNumberStart
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "SetLineNumberStyle", .LineNumberStyle
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "HideSel", .HideSel
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "NormalizeCase", .NormalizeCase
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "OvertypeCaret", .OvertypeCaret
'      'Syntax colors
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrText, .GetColor(cmClrText)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrTextBk, .GetColor(cmClrTextBk)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrComment, .GetColor(cmClrComment)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrCommentBk, .GetColor(cmClrCommentBk)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrKeyword, .GetColor(cmClrKeyword)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrKeywordBk, .GetColor(cmClrKeywordBk)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrNumber, .GetColor(cmClrNumber)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrNumberBk, .GetColor(cmClrNumberBk)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrOperator, .GetColor(cmClrOperator)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrOperatorBk, .GetColor(cmClrOperatorBk)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrString, .GetColor(cmClrString)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrStringBk, .GetColor(cmClrStringBk)
'      SetRegValue MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrWindow, .GetColor(cmClrWindow)
'   End With
'   MWinReg.hKey = oldhKey
'   MWinReg.SubKey = oldSubKey
'End Sub

Sub MNSBCodeMax_SetLanguage(ByRef scriptObj As CodeMax4Ctl.CodeMax)
'**** Apply the language to our control instance
'   script.Language = ""
'   MNSBCodeMax_CreateNSBasicLanguage
   scriptObj.Language = cmLanguage
'   script.SetColor cmClrBookmark, vbWhite
'   script.SetColor cmClrBookmarkBk, &H80&
'   scriptObj.SetColor cmClrNumber, scriptObj.GetColor(cmClrString)
'   scriptObj.SetFontStyle cmStyKeyword, cmFontNormal
'   script.SetColor cmClrScopeKeyword, vbYellow
'   script.SetColor cmClrWindow, vbBlack
'   script.SetColor cmClrText, vbWhite
End Sub

Sub MNSBCodeMax_SavePrefs(scriptObj As CodeMax4Ctl.CodeMax)
Dim key As String
   #If NSBSymbian Then
      key = "HKCU\Software\NSBasic\Symbian\Editor"
   #Else
      key = "HKCU\Software\NSBasic\Palm\Editor"
   #End If
   cmGlobals.SaveSettingsToRegistry (key)
   scriptObj.SaveSettingsToRegistry (key)
   'MsgBox "settings saved"
End Sub

Sub MNSBCodeMax_SetScriptPrefs(ByRef scriptObj As CodeMax4Ctl.CodeMax)
Dim key As String
'Dim oldhKey As Long
'Dim oldSubKey As String

   #If NSBSymbian Then
      key = "HKCU\Software\NSBasic\Symbian\Editor"
   #Else
      key = "HKCU\Software\NSBasic\Palm\Editor"
   #End If
   cmGlobals.LoadSettingsFromRegistry (key)
   scriptObj.LoadSettingsFromRegistry (key)
   
'   oldhKey = MWinReg.hKey
'   MWinReg.hKey = HKEY_CURRENT_USER
'   oldSubKey = MWinReg.SubKey
'   MWinReg.SubKey = "Software\NSBasic\Palm\Editor"
'
'   With scriptObj
'      .ColorSyntax = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "ColorSyntax", g_strTrue) Like g_strTrue)
'      .EnableHSplitter = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "EnableHSplitter", g_strTrue) Like g_strTrue)
'      .EnableVSplitter = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "EnableVSplitter", g_strTrue) Like g_strTrue)
'      .HScrollVisible = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "HScrollVisible", g_strTrue) Like g_strTrue)
'      .VScrollVisible = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "VScrollVisible", g_strTrue) Like g_strTrue)
'      .AutoIndentMode = GetRegValue(MWinReg.hKey, MWinReg.SubKey, "AutoIndentMode", 2)
'      .SmoothScrolling = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SmoothScrolling", g_strFalse) Like g_strTrue)
'      .LineToolTips = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "LineToolTips", g_strTrue) Like g_strTrue)
'      .DisplayLeftMargin = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "DisplayLeftMargin", g_strFalse) Like g_strTrue)
'      .EnableColumnSel = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "EnableColumnSel", g_strTrue) Like g_strTrue)
'      .EnableDragDrop = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "EnableDragDrop", g_strTrue) Like g_strTrue)
'      .ExpandTabs = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "ExpandTabs", g_strTrue) Like g_strTrue)
'      .TabSize = GetRegValue(MWinReg.hKey, MWinReg.SubKey, "TabSize", 4)
'      .SetColor cmClrHighlightedLine, GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SetColor", 65535)
'      .SetFontStyle cmStyText, GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SetFontStyle", 0)
'      .SetFontStyle cmStyComment, GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SetCommentStyle", 2)
'
'      .font.Name = GetRegValue(MWinReg.hKey, MWinReg.SubKey, "FontName", "Courier New")
'      .font.Charset = gLabelCharset '0
'      .font.Size = GetRegValue(MWinReg.hKey, MWinReg.SubKey, "FontSize", 10) '03/22/01 GH
'      .SelBounds = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SelBounds", g_strTrue) Like g_strTrue)
'      '.SetAllBookmarks = ((GetRegValue(MWinReg.hKey, MWinReg.SubKey,"SetAllBookmarks" )
'      .LineNumbering = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SetLineNumbering", g_strFalse) Like g_strTrue)
'      .LineNumberStart = GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SetLineNumberStart", 1)
'      .LineNumberStyle = GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SetLineNumberStyle", cmDecimal)
'      .HideSel = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "HideSel", g_strFalse) Like g_strTrue)
'      .NormalizeCase = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "NormalizeCase", g_strTrue) Like g_strTrue)
'      .OvertypeCaret = (GetRegValue(MWinReg.hKey, MWinReg.SubKey, "OvertypeCaret", g_strTrue) Like g_strTrue)
'      'Syntax colors
'      .SetColor cmClrText, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrText, .GetColor(cmClrText)))
'      .SetColor cmClrTextBk, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrTextBk, .GetColor(cmClrTextBk)))
'      .SetColor cmClrComment, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrComment, .GetColor(cmClrComment)))
'      .SetColor cmClrCommentBk, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrCommentBk, .GetColor(cmClrCommentBk)))
'      .SetColor cmClrKeyword, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrKeyword, .GetColor(cmClrKeyword)))
'      .SetColor cmClrKeywordBk, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrKeywordBk, .GetColor(cmClrKeywordBk)))
'      .SetColor cmClrNumber, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrNumber, .GetColor(cmClrNumber)))
'      .SetColor cmClrNumberBk, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrNumberBk, .GetColor(cmClrNumberBk)))
'      .SetColor cmClrOperator, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrOperator, .GetColor(cmClrOperator)))
'      .SetColor cmClrOperatorBk, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrOperatorBk, .GetColor(cmClrOperatorBk)))
'      .SetColor cmClrString, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrString, .GetColor(cmClrString)))
'      .SetColor cmClrStringBk, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrStringBk, .GetColor(cmClrStringBk)))
'      .SetColor cmClrWindow, Val(GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Color" & cmClrWindow, .GetColor(cmClrWindow)))
'   End With
'
'   MWinReg.hKey = oldhKey
'   MWinReg.SubKey = oldSubKey
End Sub
