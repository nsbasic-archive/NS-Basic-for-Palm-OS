Attribute VB_Name = "MNSBasicCompile"
Option Explicit

Public Const menusOn = False 'do not show menu icons during debugging.
Public Const allowRegistration = True
Public Const bookEdition = False 'special build for inclusion in book
Public Const defaultLanguage = "English"  'normally English

'additions 06112005
'Dim svModules(2) As Integer    'will be reDIM'd later to larger size
Global svLocalIDs() As String    'will be reDIM'd later to larger size
Global svVarNames() As String     'will be reDIM'd later to larger size
Global svDataElemNos() As Integer  'will be reDIM'd later to larger size
Global lastVarNodeAskedFor As Integer 'the node number of the last node asked for
'end additions 06112005

Global saveTerm1013 As String        'added 1013200
Global saveTermType1013 As Integer   'added 10132002
Global itsAVarname As Boolean         'added 08222002
Global saveTblNo As Integer           'added 08222002
Global saveObjName As String          'added 08222002

Global gDimIsDatabase As Boolean                        'added 09242003
Global gnToolboxTool As Integer
Global gfToolbox As New frmToolbox
Global gbToolbox As Boolean
Global gfProjectExplorer As New frmProjectExplorer
Global gbProjectExplorer As Boolean
Global gfProperties As New frmProperties
Global gbProperties As Boolean
Global gProjects As New Collection
'Global gstr Target As String
Global gTarget As CProject
Global gSelected As Object
Global gDefineStmts As String
Global gFirstSubName As String
Global gCorrection As Long
Global gsCurrentFormGlobalID As String

Dim bracket_mode As Boolean
Global LastSubFuncParsed As String   '06102002 added
Global startingParagCount As Integer  'added 4/07/2001  ****
Global allowArrayNames As Boolean     'added 805 ************
Global projectDirty As Boolean
Global gbUIBitmapScreenDrawHappening As Boolean
Global gLabelFontName As String
Global gLabelFontSize As Integer
Global gLabelCharset As Integer
Global gLanguage As String
Global gStringTable(4000) As String
Global gCommandLineProject As String
Global gCommandLineOptions As String

Global typ As CTypeDef
Global loadType As String
Global LocalID As String
Global DemoSw As String * 1
Global installType As String
Global compileOkSw As Boolean
Global fileDirectory As String
Global DownloadOption As String  '04/03/01 GH
Global gbPOSErun As Boolean        '04/03/01 GH
Global gbSimulatorRun As Boolean   '11/07/03 GH
Global gstrPOSEPath As String        '04/03/01 GH
Global gstrSimulatorPath As String   '11/07/03 GH
Global gbBuildFat As Boolean       '10.22.00 GH
Global gbIncludeArmNative As Boolean '12/30/03 GH
Global gbAutoSave As Boolean      '01/10/01 MMD
Global gbPlainText As Boolean     '01/17/01 MMD
Global gbLaunchPOSE As Boolean
Global gbLaunchSimulator As Boolean '11/07/03 GH
Global gbHiRes As Boolean         '05/10/01 GH
Global gbDana As Boolean          '05/14/07 GH
Global gNextCompileResourceID As Integer '12/08/08 GH
#If NSBSymbian Then
Global gbCreateS60 As Boolean     '05/15/08 GH
Global gbCreateUIQ As Boolean     '05/15/08 GH
Global gbRunImmediately As Boolean '05/15/08 GH
Global gstrNextUID3 As String      '07/04/08 GH
#End If
Global kScreenWidth As Integer    '05/14/07 GH
Global gbCopyProtect As Boolean   '09/06/01 GH
Global ghDebugMode As Boolean     '06/10/05 GH
Global listOrPopup As String
Global compiler_debug As Boolean
Global thisTermStart As Long
Global curCompilePos As Long
Global curCompileLine As Long
Global curCompileLen As Long           '***revised 3/13/2001 *****
Global stmt_start_instr As Long        '***revised 3/13/2001 ******
Global controlId As Integer
Global controlObj As Object
Global currentTypename As String
Global Menu As CMenu
Global mnuBar As CMenuBar
Global mnu As CMenuElem
Global chooseType As String
Global last_para  As Integer
Global file_null_ptr As CFileEntry
Global file_ptr As CFileEntry
Global log_work_var_no As Integer
Global arith_work_de_no As Integer
Global string_work_de_no As Integer
Global paren_cnt As Integer
Global paren_is_delim_sw As Integer
Global term As String
Global para_endif_ptr(2000) As Integer
Global parse_type As String
Global NeedInitialization As Integer
Global parse_desc  As String
Global mode As String
Global compileInProcess

Global subOrFunc As String
Global compile_no_good  As Integer
'Global model As CProject
Global aView As CForm
Global aView_null_ptr As New CForm
Global object_null_ptr As New CUIObject
Global d1 As CDataElement
Global arg_1 As Integer
Global arg1_occ1 As Integer
Global arg1_occ2 As Integer
Global arg1_occ3 As Integer


Global d2 As CDataElement
Global arg_2 As Integer
Global arg2_occ1 As Integer
Global arg2_occ2 As Integer
Global arg2_occ3 As Integer

Global first_string_work As Integer
Global Const kStringWorkDEMax As Integer = 100
Global logic_stat  As Integer
Global oper_se As CSynElem
Global subj_se As CSynElem
Global first_log_work As Integer
Global Const log_work_var_max As Integer = 100
Global repeat_sw As Integer
Global d3 As CDataElement
Global arg_3 As Integer
Global arg3_occ1 As Integer
Global arg3_occ2 As Integer
Global arg3_occ3 As Integer

Global gTotalNSBvars As Integer
Global first_arith_work As Integer
Global Const kArithWorkDEMax As Integer = 100
Global d4 As CDataElement
Global arg_4 As Integer
Global arg4_occ1 As Integer
Global arg4_occ2 As Integer
Global arg4_occ3 As Integer

Global arith_work_integ_sw(2000)
Global d5 As CDataElement
Global arg_5 As Integer
Global arg5_occ1 As Integer
Global arg5_occ2 As Integer
Global arg5_occ3 As Integer

Global thisModuleId As Integer
Global dataelem_null_ptr As CDataElement
Global code_buffer As String
Global code_buff_max As Long
Global proc_offset As Long
Global p As CParaTbl
Global para_null_ptr As New CParaTbl
Global para_false_ptr(256) As Integer
Global if_was_elseif(256) As Integer
Global ArgListCollection As Collection
Global parag_tbl_no As Integer
Global link_tbl_no As Integer
Global term_sub_present As Integer
Global the_highest_parag As Integer
Global compile_err  As Integer
Global if_level As Integer
Global al As New CArgList
Global Const term_len_max As Integer = 256
Global look_ahead_char As String
Global quote_con As String
Global end_line As String
Global line_feed As String
Global tabChar As String
Global err_code As Integer
Global term_tbl_no As Integer
Global data As CDataElement

Global paren_done_yet As Integer
Global theTermSe As CSynElem
Global theTermDe_no As Integer
Global theTermMaj As String
Global theTermSub1 As Integer
Global theTermSub2 As Integer
Global theTermSub3 As Integer

Global se_null_ptr As CSynElem
Global arith_stat As Integer
Global arith_se As CSynElem
Global paren_sw As Integer
Global termType As Integer
Global term_used As Integer
Global dbdef As cDatabase
Global dbNumber As Integer
Global Const FUNCTYPE As Integer = 10
'11/30/2000 MD
Global Const gcTYPE_VERB As Integer = 2
Global Const gcTYPE_RESERVED As Integer = 3
Global Const gcTYPE_DATA_PARA As Integer = 4
Global Const gcTYPE_ALPHALIT As Integer = 5
Global Const gcTYPE_CONSTANT As Integer = 6
Global Const gcTYPE_OTHER As Integer = 7
Global Const gcTYPE_FUNC As Integer = 10
Global Const gcTYPE_DBNAME As Integer = 13
'11/30/2000 MD
Global func_type As Integer
Global while_level As Integer
Global while_endwhile_ptr(2000) As Integer
Global while_false_ptr(2000) As Integer
Global Const max_if_lvls As Integer = 256
Global para_true_ptr(2000) As Integer
Global Const max_while_lvls As Integer = 256
Global while_true_ptr(2000) As Integer

Global for_level As Integer
Global for_endwhile_ptr(200) As Integer
Global for_false_ptr(200) As Integer
Global Const max_for_lvls As Integer = 10
Global for_true_ptr(200) As Integer


Global Const win_kybd_tab As Byte = &H9
Global Const funcName As String = "f"
Global Const func_token As Byte = &HDE
Global termin As String
Global end_input As Boolean

Global look_i As Integer
Global look_ahead_buf As String
Global Const null_string As String = ""
Global term_area As Integer
Global term_len As Integer
Global in_buf As String
Global in_ptr As Long           '02/20/01 GH
Global alpha_con_seq_no As Integer
Global num_con_seq_no As Integer
Global termin_prev As String
Global quote_mode As Integer
Global got_period As Integer
Global one_char As String
Global s1_tbl_no As Integer
Global s2_tbl_no As Integer
Global s3_tbl_no As Integer

Global cur_char As String
Global se As CSynElem
Global first_se As CSynElem
Global formCount As Integer '11.20.06 GH counter of number of forms with nav

Enum ProcessScriptEnum
   ToDisk
   FromDisk
End Enum

Public Type PropertyInfo
   Name As String
   Val As String
   Type As Integer
   data As String
End Type
Global gPropInfo As PropertyInfo

Type controlProportions
   widthProportions As Single
   heightProportions As Single
   topProportions As Single
   leftProportions As Single
End Type

Type Word
   w As Integer
End Type

Type Dword
   d As Long
End Type

Type PointType
   x As Integer
   y As Integer
End Type
   
Type RectangleType
   topleft As PointType
   extent As PointType
End Type
   
Type AbsRectType
   Left As Integer
   Top As Integer
   Right As Integer
   Bottom As Integer
End Type
   
Type CharPtr
   c As Long
End Type
   
Type Handle
   h As Long
End Type
    
Type ControlStyleType
   s As Byte
End Type
    
Type ctlOut
   id As Word
   bounds As RectangleType
   Text As CharPtr
   attr As Byte
      '&h80 usable:1
      '&h40 enabled:1
      '&h20 visible:1
      '&h10 onflag:1
      '&h08 leftAnchor:1
      '&h07 Frame:3
   unused As Byte
   style As ControlStyleType
   font As Byte
   group As Byte
   unused3 As Byte
End Type

Type LineInfoType
   start As Word
   Length As Word
End Type

Type LineInfoPtr
   l As Long
End Type
  
Type FieldOut
   id As Word
   RECT As RectangleType
   attr1 As Byte
   attr2 As Byte
      '&h8000 usable:1
      '&h4000 visible:1
      '&h2000 editable:1
      '&h1000 singleLine:1
      '&h0800 hasFocus:1
      '&h0400 dynamicSize:1
      '&h0200 insPtVisible:1
      '&h0100 dirty:1
      '&h00C0 underlined:2
      '&h0030 justification:2
      '&h0008 autoShift:1
      '&h0004 hasScrollBar:1
      '&h0002 numeric:1
      '&h0001 unused:1
   Text As CharPtr
   textHandle As Handle
   lines As LineInfoPtr
   textLen As Word
   textBlockSize As Word
   MaxCharacters As Word
   selFirstPos As Word
   selLastPos As Word
   insPtXPos As Word
   insPtYPos As Word
   font As Byte
   unused As Byte
End Type

Type titleOut
   RECT As RectangleType
   Text As CharPtr
End Type

Type labelOut
   id As Word
   pos As PointType
   Usable As Word
   font As Byte
   unused As Byte
   Text As CharPtr
End Type
 
'added 04012005   !!!new slider control!!!!!
Type SliderOut
   id As Word
   bounds As RectangleType
   thumbID As Word
   backgroundID As Word
   attribute1 As Byte      '0hc040  0hc060 if vertical
   attribute2 As Byte
   style As Byte          'h06 if slider  h07 if feedback
   Reserved As Byte
   minimum As Word
   maximum As Word
   PageSize As Word
   Value As Word
   activeSliderPtr As CharPtr
End Type
'end additions 04012005
 
Type gadgetOut
   id As Word
   Usable As Word
   RECT As RectangleType
   data As CharPtr
End Type
 
Type bitmapOut
   Usable As Byte
      ':1 set if part of UI
   unused As Byte
   pos As PointType
   rscId As Word
End Type
 
Type popupOut
   ctlId As Word
   ListId As Word
End Type

Type listOut
   id As Word
   bounds As RectangleType
   attr As Byte
      '&h80 usable:1
      '&h40 enabled:1
      '&h20 visible:1
      '&h10 poppedUp:1
      '&h08 hasScrollbar:1
      '&h04 search:1
      '&h03 reserved:2
   unused As Byte
   itemsText As CharPtr
   numItems As Word
   currentItem As Word
   topItem As Word
   font As Byte
   unused2 As Byte
   popupWin As Handle
   callback As CharPtr
End Type
  
Type scrollbarOut
   bounds As RectangleType
   id As Word
   attr As Byte
      '&h80 usable:1
      '&h40 visible:1
      '&h20 hilighted:1
      '&h10 shown:1
      '&h0F activeRegion:4
   unused As Byte
   Value As Integer
   MinValue As Integer
   MaxValue As Integer
   PageSize As Integer
   penPosInCar As Integer
   savePos As Integer
End Type
  
Type shiftIndicOut
   pos As PointType
End Type
  
  Type tableOut
     id As Word
     bounds As RectangleType
     attr As Byte
       'visible &h80
       'editable &h40
       'editing &h20
       'selected &h10
       'hasScrollbar &h08
       'usable &04
     filler1 As Byte
     numColumns As Word
     numRows As Word
     currentRow As Word
     currentColumn As Word
     topRow As Word
     colAttrs As CharPtr
     rowAttrs As CharPtr
     Items As CharPtr
     currentField As CharPtr
   End Type
   
   Type tableRowAttr
     id As Word
     Height As Word
     data As Dword
     flag1 As Byte
       'reserved 7 bits
       'usable   &h01
     flag2 As Byte
     'reserved 5 bits
       'invalid  &h04
       'staticHeight '&h02
       'selectable   '&h01
     Reserved As Word
   End Type
   
   Type tableColAttr
     Width As Word
     flag1 As Byte
       'unused - 6 bits
       'editIndicator &h02
       'usable        &h01
     flag2 As Byte
     spacing As Word
     drawCallback As CharPtr
     loadData     As CharPtr
     saveData As CharPtr
   End Type

   
Type formOut
   dispWidth As Word
   dispHeight As Word
   displayAddr As CharPtr
   flags As Word
      '&h8000 format:1
      '&h4000 offscreen:1
      '&h2000 modal:1
      '&h1000 focusable:1
      '&h0800 enabled:1
      '&h0400 visible:1
      '&h0200 dialog:1
      '&h0100 compressed:1
      '&h00FF reserved:8
   bounds As RectangleType
   clipBounds As AbsRectType
   origin As PointType
   cornerDiam As Byte
   frameBits As Byte
      '&hF0 reserved:4
      '&h0C shadow width:2
      '&h03 frame width:2
   statePtr As CharPtr
   nextWindow As CharPtr
   '-----------------end of window type structure----------
   id As Word
   attr As Byte
      '&h80 usable:1
      '&h40 enabled:1
      '&h20 visible:1
      '&h10 dirty:1
      '&h08 saveBehind:1
      '&h04 grafShift:1
      '&h03 reserved:2
   unused As Byte
   unused2 As Byte
   unused3 As Byte
   bitsBehindForm As Handle
   handler As CharPtr
   focus As Word
   defButton As Word
   helpRscId As Word
   menuRscId As Word
   numObjects As Word
   objPtr As CharPtr
End Type
  
Type prcHeader
   NameFld(31) As Byte
   flags As Word
   version As Word
   createTime(3) As Byte
   modTime(3) As Byte
   backupTime(3)  As Byte
   modNum As Long
   appInfo As Long
   sortInfo As Long
   type1 As Byte
   type2 As Byte
   type3 As Byte
   type4 As Byte
   id1 As Byte
   id2 As Byte
   id3 As Byte
   id4 As Byte
   uniqIdSeed As Long
   nextRecordList As Long
   numRecords As Word
End Type
  
Type menuItem
   id As Word
   command As Byte
   unused As Byte
   itemStr As Long
End Type
  
Type menuPulldown
   menuWin As Handle
   bounds As RectangleType
   bitsBehind As Handle
   titleBounds As RectangleType
   Title As Long
   numItems As Word
   menuItemTypeOffset As Long
End Type

Type PPmenuBar
   barWin As Handle
   bitsBehind As Handle
   savedActiveWin As Handle
   bitsBehindStatus As Handle
   attr As Word
      '&h8000 visible:1
      '&h4000 cmd pending:1
      '&h2000 insPtEnabled:1
      '&h1FFF reserved:13
   curMenu As Word
   curItem As Word
   cmdTick As Long
   numMenus As Word
   menuPulldownPtr As Long
End Type
    
'separate bitmap entry in prc file
Type bmpType
   Width As Word
   Height As Word
   rowBytes As Word
   flags As Word
   resv1 As Word
   resv2 As Word
   resv3 As Word
   resv4 As Word
End Type

Global stage As String
Global newProjSw As Boolean
Global LitePro As String
Global glSerialNumber As String
Global gsTheme As String
Global Const VersionInteg = 505
Global Const VersionFrac = 0
Global SnapSw As Boolean
Global outFile As Integer
Global o As Object
Global explScreenIndex As Integer
Global explBitmapIndex As Integer
Global explCodeIndex As Integer
Global cod As CCodeModule
Global bmp As CBitmapFile
Global selectedTop As Integer
Global selectedLeft As Integer
Global selectedWidth As Integer
Global selectedHeight As Integer
Global editorSource As String
Global ProjectName As String
Global ProjectPath As String
Global LastX As Integer
Global LastY As Integer
Global LastButton As Integer
Global objectSelected As Boolean
Global formSelected As Boolean
Global resizeInProcess As Boolean
Global alignInProcess As Boolean
Global alignType As String
Global alignSpace As Boolean
Global alignStartX As Integer
Global alignStartY As Integer
Global alignLastX As Integer
Global alignLastY As Integer
Global MouseSelectBorder As Boolean
Global saveMouseSelectObject As Object
Global PalmScreenOrigX As Integer
Global PalmScreenOrigY As Integer
Global firstObject As Object
Global MouseX As Integer
Global MouseY As Integer
Global gbWantGrid As Boolean
Global gnGridIncr As Integer
Global resetProjectPath As String
Global resetProjectName As String
Global resetModel As CProject
Global resetView As CForm
Global moveInprocess As Boolean
Public Const objButton As Integer = 1
Public Const objPushbutton As Integer = 2
Public Const objCheckbox As Integer = 3
Public Const objShiftIndic As Integer = 4
Public Const objGrid As Integer = 5
Public Const objSelector As Integer = 6
Public Const objScrollbar As Integer = 7
Public Const objRepeater As Integer = 8
Public Const objPopup As Integer = 9
Public Const objList As Integer = 10
Public Const objLabel As Integer = 11
Public Const objGadget As Integer = 12
Public Const objField As Integer = 13
Public Const objBitmap As Integer = 14
Public Const objSlider As Integer = 15   'added 04012005

Global currentStatementNumber As Integer  'added 04012005
Global gbDebugMode As Boolean             'added 04012005
Global gbAtBreakPoint As Boolean          'added 07012005
Global debuggerModuleId As Integer        'added 04012005
Global debuggerStatementNumber As Integer 'added 04012005
Global endOfLastLine As Long              'added 04012005
Global lastModuleIdOutput As Integer      'added 04012005
Global lastStmtNumberOutput As Integer    'added 04012005
Global debuggerlastvariableid  As Long    'added 04012005
Global debuggerLastSubscriptNode As Node  'added 04012005
Global debuggerLastVariableNode As Node   'added 04012005
Global debuggerlaststackid As Integer     'added 04012005
Global ignoreBreakpoints As Boolean       'added 04012005
Global debuggerlastnodeno As Integer      'added 04012005
Global needToRefreshWatchVars As Boolean  'added 04012005

Global OnOneLine As Integer
Global dummyObject As Object

Global DownloadPath As String
Global Nil As Object
Global ToolboxInProcess As Boolean
Global ToolboxOrigX As Integer
Global ToolboxOrigY As Integer
Global ToolboxType As Integer
Global ToolboxSelected As Boolean
Global mnuCurItem As Integer
Global ProgramsDirectory As String
Global mnubarCurItem As Integer

Global RecentProjs(20) As String
Global verb_had_paren As Boolean
Global RegistrationCode As String
Global RegistrationCrc As Long
Declare Function WinHelp Lib "USER32" Alias "WinHelpA" _
      (ByVal hWnd As Long, ByVal lpHelpFile As String, _
       ByVal wCommand As Long, ByVal dwData As Long) As Long

Public Const HELP_CONTEXT = &H1
Public Const HELP_QUIT = &H2
Public Const HELP_INDEX = &H3
Public Const HELP_HELPONHELP = &H4
Public Const HELP_SETINDEX = &H5
Public Const HELP_KEY = &H101
Public Const HELP_MULTIKEY = &H201
'Global lastSearch As String
Global lastSearchLocat As Long
Global searchNotFoundSw As Integer

Global firstSearchModule As Object
Global searchInProgress As Boolean
Global searchText As String
Global searchOrigPos As Long
Global searchModule As Object
Global lastSearchModule As Object
Global searchCmd As String
Global selectCount As Integer
Global resizeType As Integer

Global g_strTrue As String
Global g_strFalse As String

 
Function chk_proc_verbs() As Integer
    If term_is("_end-line") Then
'dbug    "chk_proc_verbs got _end-line"
      'dont need to do anything
      GoTo foundVerb
    End If
    If subOrFunc = " " Then
      If (term_is("sub")) Then
         parse_sub
         GoTo foundVerb
      ElseIf term_is("function") Then
         parse_function
         GoTo foundVerb
      ElseIf term_is("global") Then
         parse_global
         GoTo foundVerb
      ElseIf term_is("type") Then
         parse_typeStmt
         GoTo foundVerb
      Else
        chk_proc_verbs = 0
        Exit Function
      End If
    End If
    
    If subOrFunc = " " Then
       print_err gStringTable(3104) '"Missing SUB or FUNCTION header"
    End If
    If gTarget.SelectCollection.count > 0 Then
       If gTarget.SelectCollection.Item(gTarget.SelectCollection.count).stat = 0 Then
          If Not term_is("case") Then print_err gStringTable(3105) '"the only statement that can follow a SELECT CASE is the CASE statement"
       End If
    End If
    
    'If (term_is("alter")) Then
    '      parse_alter
    
    '  Else: If (term_is("browse")) Then parse_browse
    '  Else: If (term_is("buffer")) Then parse_buffer
    If (term_is("let")) Then
          parse_let
   '   Else: If (term_is("comm")) Then com1_parse
    ElseIf term_is("beep") Then
         parse_beep
    ElseIf term_is("bitmap") Then
         parse_bitmap
    ElseIf (term_is("call")) Then
          parse_call
    ElseIf (term_is("case")) Then
          parse_case
    ElseIf (term_is("clear")) Then  '08022002 changed(was clearfields)
          parse_clearfields               '06102002 added
    ElseIf (term_is("compilerdebugon")) Then
             compiler_debug = True
    ElseIf (term_is("debugon")) Then
           out_one_char &HFD
    ElseIf (term_is("debugoff")) Then
           out_one_char &HFE
    ElseIf (term_is("compilerdisp")) Then
           get_term
           MsgBox "progress=" + term
    ElseIf (term_is("compilerdebugoff")) Then
          compiler_debug = False
    ElseIf (term_is("controlsetlabel")) _
        Or (term_is("controlsettext")) Then
          parse_ControlSetLabel
    '08222002ElseIf (term_is("controlssettext")) Then   'added 06102002
    '08222002      parse_controlssettext                'added 06102002
    ElseIf (term_is("controlsetstatus")) Then
          parse_ControlSetStatus
    ElseIf (term_is("controlhide")) Then
          parse_ControlHide
    ElseIf (term_is("controlshow")) Then
          parse_ControlShow
    ElseIf (term_is("createwindow")) Then
          parse_createwindow
    ElseIf (term_is("setcurrentwindow")) Then
          parse_setcurwindow
    ElseIf (term_is("cursor")) Then
          parse_cursor
    ElseIf (term_is("define")) Then
          parse_define
    '  Else: If (term_is("dbfields")) Then qry_dbfields
    '  Else: If (term_is("dbtables")) Then qry_dbtables
    ElseIf (term_is("delay")) Then
       parse_delay
    '  Else: If (term_is("delete")) Then GoTo gotDelete
    ElseIf (term_is("destroywindow")) Then
          parse_destroywindow
    'ElseIf (term_is("directory")) Then
    '   parse_directory
    ElseIf (term_is("dim")) Then
       parse_dim
    ElseIf (term_is("display")) Then
       parse_display
    ElseIf (term_is("do")) Then
       parse_do
    ElseIf (term_is("drawchars")) Then
          parse_drawchars
    ElseIf (term_is("drawline")) Then
          parse_drawline
    ElseIf (term_is("drawbitmap")) Then
          parse_drawbitmap
    ElseIf (term_is("drawrectangle")) Then
          parse_drawrectangle
    ElseIf (term_is("edit")) Then
       parse_edit
    ElseIf (term_is("else")) Then
       parse_else
     ElseIf (term_is("elseif")) Then
       parse_elseif
    '   Else: If (term_is("email")) Then ccmail1_verb
    ElseIf (term_is("endif")) Then
       parse_endif
    ElseIf term_is("end") Then
         parse_end
         GoTo foundVerb
   
    '   Else: If (term_is("execdos")) Then parse_execdos
    ElseIf (term_is("erasewindow")) Then
          parse_erasewindow
    'ElseIf (term_is("exec")) Then
    '   parse_exec
    ElseIf (term_is("exit")) Then
       parse_exit
    '   Else: If (term_is("execmodel")) Then parse_execmodel
    '   Else: If (term_is("execprogram")) Then parse_execprogram
    ElseIf (term_is("export")) Then
       parse_export
    ElseIf (term_is("fieldsettext")) Then
          parse_fieldSetText
    ElseIf (term_is("fieldsetmaxchars")) Then
          parse_fieldSetMaxChars
    
    ElseIf (term_is("fillrectangle")) Then
          parse_fillrectangle
    ElseIf (term_is("for")) Then
       parse_for
    ElseIf (term_is("setgeneralproperty")) Then
       parse_setgeneralproperty
    ElseIf (term_is("generalverb")) Then    'added 08222002
       parse_generalVerb                    'changed 09092002
    ElseIf (term_is("getpen")) Then
       parse_getpen
    ElseIf (term_is("global")) Then
       parse_global
    ElseIf (term_is("go")) Then
       parse_go
    ElseIf (term_is("gosub")) Then
       parse_gosub
    ElseIf (term_is("goto")) Then
       parse_goto
    ElseIf (term_is("if")) Then
       parse_if
    ElseIf (term_is("import")) Then
       parse_import
    '   Else: If (term_is("insert")) Then GoTo gotInsert
         
    ElseIf (term_is("input")) Then
       parse_input
    'ElseIf (term_is("label")) Then
    '    parse_label
    ElseIf (term_is("chain")) Then
        parse_transfertoprogram
    ElseIf (term_is("launchprogram")) Then
        parse_launchprogram
    ElseIf (term_is("transfertoprogram")) Then
        parse_transfertoprogram
    ElseIf (term_is("listadditem")) Then
          parse_listAddItem
    ElseIf (term_is("listclear")) Then
       parse_listclear
    ElseIf (term_is("listdeleteitem")) Then
          parse_listDeleteItem
    ElseIf (term_is("listsetselected")) Then
          parse_listSetSelected
    'ElseIf (term_is("load")) Then
    '    parse_load
    'ElseIf (term_is("lookup")) Then
    '    parse_lookup
    ElseIf (term_is("loop")) Then
       parse_loop
    'ElseIf (term_is("newmodel")) Then
    '    parse_newmodel
    'ElseIf (term_is("memdebug")) Then
    '    parse_mem_debug
    ElseIf (term_is("menuerase")) Then
        parse_menuerase
    ElseIf (term_is("menudraw")) Then
        parse_menudraw
    ElseIf (term_is("menureset")) Then
        parse_menureset
    ElseIf (term_is("msgbox")) Then
       parse_msgbox
    ElseIf (term_is("next")) Then
       parse_next
    ElseIf (term_is("nextscreen")) Or (term_is("nextform")) Then
       parse_nextscreen
       
    ElseIf (term_is("popupadditem")) Then
       parse_popupAddItem
    ElseIf (term_is("popupclear")) Then
       parse_popupClear
    ElseIf (term_is("popupdeleteitem")) Then
       parse_popupDeleteItem
    ElseIf (term_is("popupsetselected")) Then
       parse_popupSetSelected
    ElseIf (term_is("popupsettext")) Then
       parse_PopupSetText
    ElseIf (term_is("print")) Then
       parse_msgbox 'was parse_print, but there is no print
    'ElseIf (term_is("receive")) Then
    '   parse_receive
    ElseIf (term_is("redraw")) Then
       parse_redraw
    '   Else: If (term_is("report")) Then rpt_parse_report
    '   Else: If (term_is("resave")) Then parse_resave
    ElseIf (term_is("return")) Then
       parse_return
    'ElseIf (term_is("run")) Then
    '   parse_run
    '   Else: If (term_is("runmodel")) Then parse_runmodel
    '   Else: If (term_is("runprogram")) Then parse_runprogram
    '   Else: If (term_is("screenprint")) Then parse_screenprint
    '   Else: If (term_is("select")) Then GoTo gotSelect
    
    ElseIf (term_is("scrollbarsetcurrent")) Then
          parse_scrollbarsetcurrent
    ElseIf (term_is("scrollbarsetmin")) Then
          parse_scrollbarsetmin
    ElseIf (term_is("scrollbarsetmax")) Then
          parse_scrollbarsetmax
    ElseIf (term_is("scrollbarsetpagesize")) Then
          parse_scrollbarsetpagesize
    ElseIf (term_is("select")) Then
          parse_select
   ElseIf (term_is("seteventhandled")) Then
          parse_seteventhandled
    ElseIf (term_is("setheapvariablecount")) Then  '06102002 added
          parse_setheapvariablecount               '06102002 added
    'ElseIf (term_is("send")) Then
    '   parse_send
    ElseIf (term_is("startsignaturecapture")) Then   '*** added 4/30/2001 ***********
       parse_signaturestartcapture                   '*** added 4/30/2001 ***********
    ElseIf (term_is("displaysignature")) Then        '*** added 4/30/2001 ***********
       parse_signaturedisplay                        '*** added 4/30/2001 ***********
    ElseIf (term_is("erasesignature")) Then          '*** added 4/30/2001 ***********
       parse_signatureerase                          '*** added 4/30/2001 ***********
    'ElseIf (term_is("sort")) Then
    '   parse_sort
    ElseIf (term_is("sound")) Then
       parse_sound
    ElseIf (term_is("playsound")) Then
       parse_playsound
    ElseIf (term_is("stop")) Then
       parse_stop
    ElseIf (term_is("type")) Then
       parse_typeStmt
    'ElseIf (term_is("while")) Then
    '   parse_while
    '   Else: If (term_is("update")) Then GoTo gotUpdate
    ElseIf (Mid$(term, 1, 1) = "'") Then
       parse_comment
    ElseIf (term_is("loadlibrary")) Then     '11/30/2000 MD
       parse_loadLibrary                     '11/30/2000 MD
    ElseIf (term_is("externalsub")) Then     '12/26/2000 MD
      parse_externalSub                      '12/26/2000 MD
    ElseIf (term_is("systrapsub")) Then      '12/26/2000 MD
      parse_sysTrapSub                       '12/26/2000 MD
    Else
         chk_proc_verbs = 0
         Exit Function
    End If
foundVerb:
    chk_proc_verbs = 1
    Exit Function

End Function

Function chk_func_name() As Integer

     If (term_is("abs")) Then
       chk_func_name = 1
     ElseIf (term_is("alert")) Then
       chk_func_name = 200
     ElseIf (term_is("int")) Then
       chk_func_name = 2
     ElseIf (term_is("mod")) Then
       chk_func_name = 3
     ElseIf (term_is("rand")) Then
       chk_func_name = 4
     ElseIf (term_is("round")) Then
       chk_func_name = 5
     ElseIf (term_is("setlocale")) Then
       chk_func_name = 6
     ElseIf (term_is("power10")) Then
       chk_func_name = 7
     ElseIf (term_is("chr")) Then
       chk_func_name = 8
     ElseIf (term_is("format")) Then
       chk_func_name = 9
     ElseIf (term_is("formatnl")) Then
       chk_func_name = 10
     ElseIf (term_is("instr")) Then
       chk_func_name = 11
     ElseIf (term_is("nooccurs")) Then
       chk_func_name = 12
     ElseIf (term_is("asc")) Then
       chk_func_name = 14
     ElseIf (term_is("left")) Then
       chk_func_name = 15
     ElseIf (term_is("right")) Then
       chk_func_name = 16
     ElseIf (term_is("len")) Then
       chk_func_name = 17
     ElseIf (term_is("lcase")) Then
       chk_func_name = 18
     ElseIf (term_is("mid")) Then
       chk_func_name = 19
     ElseIf (term_is("testnum")) Then
       chk_func_name = 20
     ElseIf (term_is("str")) Then
       chk_func_name = 21
     ElseIf (term_is("proper")) Then
       chk_func_name = 22
     ElseIf (term_is("ucase")) Then
       chk_func_name = 23
     ElseIf (term_is("val")) Then
       chk_func_name = 24
     ElseIf (term_is("todate")) Then
       chk_func_name = 25
     ElseIf (term_is("totime")) Then
       chk_func_name = 26
     ElseIf (term_is("dateval")) Then
       chk_func_name = 27
     ElseIf (term_is("mmddyytodate")) Then
       chk_func_name = 28
     ElseIf (term_is("timeval")) Then
       chk_func_name = 29
     'ElseIf (term_is("timevalue")) Then
     '  chk_func_name = 30
     ElseIf (term_is("day")) Then
       chk_func_name = 31
     ElseIf (term_is("hour")) Then
       chk_func_name = 32
     ElseIf (term_is("minute")) Then
       chk_func_name = 33
     ElseIf (term_is("second")) Then
       chk_func_name = 34
     ElseIf (term_is("month")) Then
       chk_func_name = 35
     ElseIf (term_is("year")) Then
       chk_func_name = 36
     ElseIf (term_is("dayofweek")) Then
       chk_func_name = 37
     ElseIf (term_is("dayofyear")) Then
       chk_func_name = 38
     'ElseIf (term_is("avg")) Then
     '  chk_func_name = 39
     'ElseIf (term_is("count")) Then
     '  chk_func_name = 40
     'ElseIf (term_is("max")) Then
     '  chk_func_name = 41
     'ElseIf (term_is("min")) Then
     '  chk_func_name = 42
     'ElseIf (term_is("sum")) Then
     '  chk_func_name = 43
     ElseIf (term_is("getgeneralpropertynumeric")) Then     'added 08222002
       chk_func_name = 42                                   'added 08222002
     ElseIf (term_is("getgeneralpropertystring")) Then      'added 08222002
       chk_func_name = 43                                   'added 08222002
     ElseIf (term_is("ceiling")) Then
       chk_func_name = 44
     ElseIf (term_is("floor")) Then
       chk_func_name = 45
     'ElseIf (term_is("currency")) Then
     '  chk_func_name = 46
     ElseIf (term_is("sign")) Then
       chk_func_name = 47
     ElseIf (term_is("trunc")) Then
       chk_func_name = 48
     ElseIf (term_is("leftpad")) Then
       chk_func_name = 49
     ElseIf (term_is("rightpad")) Then
       chk_func_name = 50
     ElseIf (term_is("adddays")) Then
       chk_func_name = 51
     ElseIf (term_is("addmonths")) Then
       chk_func_name = 52
     ElseIf (term_is("addyears")) Then
       chk_func_name = 53
     ElseIf (term_is("firstofmonth")) Then
       chk_func_name = 54
     ElseIf (term_is("lastofmonth")) Then
       chk_func_name = 55
     ElseIf (term_is("today")) Then
       chk_func_name = 56
     ElseIf (term_is("now")) Then
       chk_func_name = 57
     ElseIf (term_is("datediff")) Then  '06102002 added ***
       chk_func_name = 58              '06102002 added ***
     ElseIf (term_is("timediff")) Then  '06102002 added ***
       chk_func_name = 59               '06102002 added ***
     ElseIf (term_is("yearmonth")) Then
       chk_func_name = 60
     ElseIf (term_is("monthday")) Then
       chk_func_name = 61
     ElseIf (term_is("hourmin")) Then
       chk_func_name = 62
     ElseIf (term_is("hourminampm")) Then
       chk_func_name = 63
     ElseIf (term_is("datemmddyy")) Then
       chk_func_name = 64
     ElseIf (term_is("subtractdays")) Then
       chk_func_name = 65
     ElseIf (term_is("subtractmonths")) Then
       chk_func_name = 66
     ElseIf (term_is("subtractyears")) Then
       chk_func_name = 67
     ElseIf (term_is("popupdate")) Then
       chk_func_name = 68
     ElseIf (term_is("popuptime")) Then
       chk_func_name = 69
     ElseIf (term_is("degtoradians")) Then
       chk_func_name = 70
     ElseIf (term_is("radtodegrees")) Then
       chk_func_name = 71
     '08222002ElseIf (term_is("controlsgettext")) Then   'added 06102002
     '08222002  chk_func_name = 72                       'added 06102002
     '08222002ElseIf (term_is("controlsgettype")) Then   'added 06102002
     '08222002  chk_func_name = 73                       'added 06102002
     '08222002ElseIf (term_is("controlsgetposition")) Then   'added 06102002
     '08222002  chk_func_name = 74                       'added 06102002
     ElseIf (term_is("controlscount")) Then   'added 06102002
       chk_func_name = 75                       'added 06102002
     'ElseIf (term_is("maxlength")) Then
     '  chk_func_name = 68
     'ElseIf (term_is("varnumdecs")) Then
     '  chk_func_name = 69
     'ElseIf (term_is("vartype")) Then
     '  chk_func_name = 70
     'ElseIf (term_is("varlength")) Then
     '  chk_func_name = 71
     
     
     ElseIf (term_is("rtrim")) Then
       chk_func_name = 80
     ElseIf (term_is("ltrim")) Then
       chk_func_name = 81
     ElseIf (term_is("trim")) Then
       chk_func_name = 82
     ElseIf term_is("syseventavailable") Then
       chk_func_name = 83
     ElseIf (term_is("getkey")) Then
       chk_func_name = 84
     
     ElseIf (term_is("geteventtype")) Then
       chk_func_name = 86
     ElseIf (term_is("sysinfo")) Then
       chk_func_name = 87
     ElseIf (term_is("endsignaturecapture")) Then            '*** added 4/30/2001  *********
       chk_func_name = 418                                   'revised 5/8/2001
     ElseIf term_is("dbcreatedatabasefromresource") Then
       chk_func_name = 88
     ElseIf term_is("getversion") Then
       chk_func_name = 89
     ElseIf (term_is("serialopen")) Then
       chk_func_name = 100
     ElseIf (term_is("serialclose")) Then
       chk_func_name = 101
     ElseIf (term_is("serialreceive")) Then
       chk_func_name = 102
     ElseIf (term_is("serialsend")) Then
       chk_func_name = 103
     ElseIf (term_is("serialset") Or term_is("sysinfoset")) Then
       chk_func_name = 104
     ElseIf (term_is("serialdial")) Then
       chk_func_name = 105
     ElseIf (term_is("serialhangup")) Then
       chk_func_name = 106
     ElseIf (term_is("serialreceivewithevent")) Then     'added 02.26.02 GH
       chk_func_name = 107
     ElseIf term_is("dbfind") Then
       chk_func_name = 300
      ElseIf term_is("dbread") Then
       chk_func_name = 301
     ElseIf term_is("dbupdate") Then
       chk_func_name = 302
      ElseIf term_is("dbdelete") Then
       chk_func_name = 303
     ElseIf term_is("dbinsert") Then
       chk_func_name = 304
      ElseIf term_is("dbreadnext") Then
       chk_func_name = 305
     ElseIf term_is("dberase") Then
       chk_func_name = 306
      ElseIf term_is("dbcreate") Then
       chk_func_name = 307
     ElseIf term_is("dbopen") Then
       chk_func_name = 308
     ElseIf term_is("dbclose") Then
       chk_func_name = 309
      ElseIf term_is("dbget") Then
       chk_func_name = 310
      ElseIf term_is("dbput") Then
       chk_func_name = 311
      ElseIf term_is("dbposition") Then
       chk_func_name = 312
      ElseIf term_is("dbreset") Then
        chk_func_name = 313
      ElseIf term_is("dbgetnorecs") Then
       chk_func_name = 314
      ElseIf term_is("dbreadprev") Then
       chk_func_name = 315
      ElseIf term_is("controlgetstatus") Then
       chk_func_name = 400
      ElseIf term_is("fieldgettext") Then
       chk_func_name = 401
      ElseIf term_is("listgetnoitems") Then
       chk_func_name = 402
      ElseIf term_is("listgetselecteditemno") Then
       chk_func_name = 403
      ElseIf term_is("listgetitemtext") Then
       chk_func_name = 404
      ElseIf term_is("controlgetid") Then
       chk_func_name = 409
      ElseIf term_is("popupgetnoitems") Then
       chk_func_name = 412
      ElseIf term_is("popupgetselecteditemno") _
          Or term_is("popupgetselected") Then
       chk_func_name = 413
      ElseIf term_is("popupgetitemtext") Then
       chk_func_name = 414
      ElseIf term_is("scrollbargetcurrent") Then
       chk_func_name = 415
       ElseIf term_is("popupgettext") Then
       chk_func_name = 416
      ElseIf term_is("controlgettext") Then
       chk_func_name = 417
       
      ElseIf term_is("acos") Then
       chk_func_name = 500
      ElseIf term_is("asin") Then
       chk_func_name = 501
      ElseIf term_is("atan") Then
       chk_func_name = 502
      ElseIf term_is("atan2") Then
       chk_func_name = 503
      ElseIf term_is("cos") Then
       chk_func_name = 504
      ElseIf term_is("sin") Then
       chk_func_name = 505
      ElseIf term_is("tan") Then
       chk_func_name = 506
      
      ElseIf term_is("cosh") Then
       chk_func_name = 508
      ElseIf term_is("sinh") Then
       chk_func_name = 509
      ElseIf term_is("tanh") Then
       chk_func_name = 510
      ElseIf term_is("acosh") Then
       chk_func_name = 511
      ElseIf term_is("asinh") Then
       chk_func_name = 512
      ElseIf term_is("atanh") Then
       chk_func_name = 513
      ElseIf term_is("exp") Then
       chk_func_name = 514
      ElseIf term_is("log") Then
       chk_func_name = 515
      ElseIf term_is("log10") Then
       chk_func_name = 516
      ElseIf term_is("cbrt") Then
       chk_func_name = 517
      ElseIf term_is("rem") Then
       chk_func_name = 518
      ElseIf (term_is("pow")) Then
       chk_func_name = 519
      ElseIf (term_is("sqrt")) Then
       chk_func_name = 520
      ElseIf (term_is("systrapfunc")) Then   '12/06/2000 MD
         chk_func_name = 598                 '12/06/2000 MD
      ElseIf (term_is("externalfunc")) Then  '11/30/2000 MD
         chk_func_name = 599                 '11/30/2000 MD
      ElseIf (term_is("applaunch")) Then        '01/29/2001 MMD
       chk_func_name = 650                      '01/29/2001 MMD
    Else
       chk_func_name = 0
     End If
End Function
Function chk_verb() As Integer              '/*-------check if term is a cobol verb---*/
    If (Mid$(term, 1, 1) = " ") Then GoTo isVerb
    'If (term_is("alter")) Then GoTo isVerb
    
    
    If (term_is("let")) Then GoTo isVerb
    If (term_is("beep")) Then GoTo isVerb
    If (term_is("bitmap")) Then GoTo isVerb
    If (term_is("call")) Then GoTo isVerb
    If (term_is("case")) Then GoTo isVerb
    If (term_is("chain")) Then GoTo isVerb
    If (term_is("clear")) Then GoTo isVerb  '08022002 changed(was clearfields)
    If (term_is("compilerdebugon")) Then GoTo isVerb  '06102002 added
    If (term_is("compilerdebugoff")) Then GoTo isVerb
    If term_is("compilerdisp") Then GoTo isVerb
    If term_is("controlhide") Then GoTo isVerb
    If (term_is("controlsetlabel")) Then GoTo isVerb
    If (term_is("controlsettext")) Then GoTo isVerb
    If (term_is("controlssettext")) Then GoTo isVerb     'added 06102002
    If (term_is("controlsetstatus")) Then GoTo isVerb
    If term_is("controlshow") Then GoTo isVerb
    If (term_is("createwindow")) Then GoTo isVerb
    If (term_is("setcurrentwindow")) Then GoTo isVerb
    If (term_is("cursor")) Then GoTo isVerb
    If (term_is("define")) Then GoTo isVerb
    If (term_is("delay")) Then GoTo isVerb
    If term_is("debugon") Then GoTo isVerb
    If term_is("debugoff") Then GoTo isVerb
    If (term_is("destroywindow")) Then GoTo isVerb
    If (term_is("dim")) Then GoTo isVerb
    'If (term_is("directory")) Then GoTo isVerb
    If (term_is("display")) Then GoTo isVerb
    If (term_is("do")) Then GoTo isVerb
    If (term_is("drawchars")) Then GoTo isVerb
    If (term_is("drawbitmap")) Then GoTo isVerb
    If (term_is("drawline")) Then GoTo isVerb
    If (term_is("drawrectangle")) Then GoTo isVerb
    'If (term_is("edit")) Then GoTo isVerb
    If (term_is("else")) Then GoTo isVerb
    If (term_is("elseif")) Then GoTo isVerb
    'If (term_is("email")) Then GoTo isVerb
    If (term_is("endif")) Then GoTo isVerb
    'If (term_is("wend")) Then GoTo isVerb
    If (term_is("end")) Then GoTo isVerb
    If (term_is("erasewindow")) Then GoTo isVerb
    'If (term_is("exec")) Then GoTo isVerb
    
    If (term_is("exit")) Then GoTo isVerb
    'If (term_is("export")) Then GoTo isVerb
    If (term_is("fieldsettext")) Then GoTo isVerb
    If (term_is("fieldsetmaxchars")) Then GoTo isVerb
    If (term_is("fillrectangle")) Then GoTo isVerb
    If (term_is("for")) Then GoTo isVerb
    If (term_is("function")) Then GoTo isVerb
    If (term_is("setgeneralproperty")) Then GoTo isVerb   'added 08222002
    If (term_is("generalverb")) Then GoTo isVerb           'added 08222002
    If (term_is("getpen")) Then GoTo isVerb
    If (term_is("global")) Then GoTo isVerb
    If (term_is("go")) Then GoTo isVerb
    If (term_is("gosub")) Then GoTo isVerb
    If (term_is("goto")) Then GoTo isVerb
    If (term_is("if")) Then GoTo isVerb
    'If (term_is("import")) Then GoTo isVerb
    'If (term_is("input")) Then GoTo isVerb
    If (term_is("launchprogram")) Then GoTo isVerb
    If (term_is("listadditem")) Then GoTo isVerb
    If (term_is("listclear")) Then GoTo isVerb
    If (term_is("listdeleteitem")) Then GoTo isVerb
    If (term_is("listsetselected")) Then GoTo isVerb
    'If (term_is("load")) Then GoTo isVerb
    If (term_is("loadlibrary")) Then GoTo isVerb   '11/30/2000 MD
    If (term_is("externalsub")) Then GoTo isVerb   '12/26/2000 MD
    If (term_is("systrapsub")) Then GoTo isVerb    '12/26/2000 MD
    'If (term_is("lookup")) Then GoTo isVerb
    If (term_is("loop")) Then GoTo isVerb
    'If (term_is("memdebug")) Then GoTo isVerb
    If (term_is("menudraw")) Then GoTo isVerb
    If (term_is("menuerase")) Then GoTo isVerb
    If (term_is("menureset")) Then GoTo isVerb
    If (term_is("msgbox")) Then GoTo isVerb
    'If (term_is("newmodel")) Then GoTo isVerb
    If (term_is("next")) Then GoTo isVerb
    If (term_is("nextscreen")) Then GoTo isVerb
    If (term_is("nextform")) Then GoTo isVerb
    'If (term_is("print")) Then GoTo isVerb
    If (term_is("popupclear")) Then GoTo isVerb
    If term_is("popupadditem") Then GoTo isVerb
    If term_is("popupdeleteitem") Then GoTo isVerb
    If term_is("popupsetselected") Then GoTo isVerb
    If term_is("popupsettext") Then GoTo isVerb
    If term_is("print") Then GoTo isVerb
    If (term_is("return")) Then GoTo isVerb
    'If (term_is("recalc")) Then GoTo isVerb
    'If (term_is("receive")) Then GoTo isVerb
    If (term_is("redraw")) Then GoTo isVerb
    'If (term_is("report")) Then GoTo isVerb
    'If (term_is("resave")) Then GoTo isVerb
    'If (term_is("screenprint")) Then GoTo isVerb
    'If (term_is("send")) Then GoTo isVerb
    'If (term_is("sort")) Then GoTo isVerb
    If term_is("scrollbarsetcurrent") Then GoTo isVerb
    If term_is("scrollbarsetmin") Then GoTo isVerb
    If term_is("scrollbarsetmax") Then GoTo isVerb
    If term_is("scrollbarsetpagesize") Then GoTo isVerb
    If (term_is("select")) Then GoTo isVerb
    'If (term_is("seteventtype")) Then GoTo isVerb
    If (term_is("setheapvariablecount")) Then GoTo isVerb
    If (term_is("startsignaturecapture")) Then GoTo isVerb     '*** added 4/30/2001 ***********
    If (term_is("erasesignature")) Then GoTo isVerb            '*** added 4/30/2001 ***********
    If (term_is("displaysignature")) Then GoTo isVerb          '*** added 4/30/2001 ***********
    If (term_is("sound")) Then GoTo isVerb
    If (term_is("playsound")) Then GoTo isVerb
    If (term_is("stop")) Then GoTo isVerb
    If (term_is("sub")) Then GoTo isVerb
    If (term_is("tablesetitemtext")) Then GoTo isVerb
    If (term_is("tableinsertrow")) Then GoTo isVerb
    If (term_is("tabledeleterow")) Then GoTo isVerb
    If (term_is("tablesetrowselectable")) Then GoTo isVerb
    'If (term_is("tablesetcolselectable")) Then GoTo isVerb
    If (term_is("tablesetselected")) Then GoTo isVerb
    If (term_is("transfertoprogram")) Then GoTo isVerb
    'If (term_is("update")) Then GoTo isVerb
    'If (term_is("while")) Then GoTo isVerb
    chk_verb = 0
    Exit Function
isVerb:
    chk_verb = 1
    Exit Function
End Function

Function chk_reserved() As Integer
    Dim i As Integer
    Dim ad1 As String
    Dim res As Integer
    
    If term = "cursor" Then GoTo isReserved
    If term = "to" Then GoTo isReserved
    If term = "step" Then GoTo isReserved
    If term = "then" Then GoTo isReserved
    chk_reserved = 0
    Exit Function
isReserved:
   chk_reserved = 1
   Exit Function

End Function

'MMD: This is less efficient version of standard StrComp(a,b,vbTextCompare)
'10.22.06 GH: No longer used
Function stricmp(a As String, b As String) As Integer
   Dim aa As String
   Dim bb As String
   aa = LCase$(a)
   bb = LCase$(b)
   If aa = bb Then
      stricmp = 0
   Else
      If aa > bb Then
         stricmp = 1
      Else
         stricmp = -1
      End If
   End If
End Function

Function chk_num_con() As Integer
    Dim i As Integer
    got_period = 0
    i = -1
    Do
      i = i + 1
      If Mid$(term, i + 1, 1) = "" Then
        Exit Do
      End If
      one_char = Mid$(term, i + 1, 1)
      If (one_char = "+") And (i = 0) Then GoTo continue
      If ((one_char = "-") And (i = 0)) Then GoTo continue
      
      If ((one_char = ".") And (got_period = 0)) Then
        got_period = 1
        GoTo continue
      End If
      If ((one_char < "0") Or (one_char > "9")) Then
         chk_num_con = 0
         Exit Function
      End If
continue:
   Loop          '/*terminates the while from above*/

    If (i = 0) Then
       chk_num_con = 0
       Exit Function
    End If
    If (i = 1) Then
      If ((one_char = "+") Or _
        (one_char = "-") Or _
        (one_char = ".")) Then
            chk_num_con = 0
            Exit Function
      End If
    End If
    chk_num_con = 1
End Function
Sub get_term()
    Dim tempSe As CSynElem

   If term_used = 0 Then
'dbug "returning old term=" + term
      term_used = 1 '/*term not used last time*/
      GoTo exit_get_term
   End If

   Set se = first_se
   If se Is se_null_ptr Then
      term = "_end-line"
      termType = 2 'verb
      termin = ""
'dbug "returning _end-line"
      GoTo exit_get_term
   End If

'dbug "se pts to " + se.term
   curCompilePos = se.posInInput
   curCompileLen = Len(se.term)
   term = LCase$(se.term)
   termType = se.termType
   termin = se.termin

   s1_tbl_no = se.sub1
   s2_tbl_no = se.sub2
   s3_tbl_no = se.sub3

'dbug "going to delete_syn_elem"
   Set theTermSe = se.Nxt
   theTermDe_no = se.de_no
   theTermMaj = se.maj
   theTermSub1 = se.sub1
   theTermSub2 = se.sub2
   theTermSub3 = se.sub3

   delete_syn_elem se
   Set se = theTermSe

exit_get_term:
   If compiler_debug Then
      dbug "returning term=" + term + " termin=" + termin + " type=" + str$(termType)
   End If
End Sub
Sub get_stmt_elem()
    Dim c As String * 1
    Dim i As Integer
    Dim j As Integer
    Dim newTerm As String
     
    ' get next term
    If term_used = 0 Then

If compiler_debug Then
dbug "stmt elem -returning old term=" + term
End If
        term_used = 1 '/*term not used last time*/
        Exit Sub
    End If
get_term_repeat:
    If (termin = "") And (end_input) Then
'dbug "found end of script"
       term = "_end-line"
       termType = 2
       termin = " "
       Exit Sub
    End If
    If (termin = "(") Or termin = ")" Or termin = "=" Then
    
       thisTermStart = thisTermStart + Len(term)
       term = " "
       curCompilePos = thisTermStart
       curCompileLen = Len(term)
       Mid$(term, 1, 1) = termin   '/*use last terminator as new term*/
'dbug "returning termin=" + termin
       termin = " "        'dont use next time*/
       term_area = 2
       termType = 7
       term_len = 1
       term_used = 1
       
       Exit Sub
    End If
   
    If termin = end_line Or termin = line_feed Then
'sgBox "got to end-of-line"
       thisTermStart = thisTermStart + Len(term)
       term = "_end-line"
       termType = 2 'verb
       termin = ""
       GoTo type_done
    End If
get_term_agn:
'dbug "at get_term_agin"
    term = ""
    term_len = 0
    termin_prev = termin
    quote_mode = 0
    term_used = 1
    get_string
    If term_is(null_string) And (Not end_input) And (quote_mode = 0) Then GoTo get_term_repeat
    If (term_is(null_string)) And (quote_mode = 0) Then
'dbug "returning null_string"
        term = ""
        termType = 2
        term_len = 3
        Exit Sub
    End If
    'If term_is("_") Then                     '*** commented out 10.10.2000
    If term_is("_") And quote_mode = 0 Then   '*** added 10.10.2000
       Do
         If termin = end_line Or termin = line_feed Then
            '07052005 get_string
            Exit Do
         End If
         get_string                           '**** added 10.10.2000 ******************
       Loop
       GoTo get_term_agn
    End If
    'If Instr$(1, term, ".") Then
       
    
    If (quote_mode) Then
        termType = 5  'alpha literal */
        GoTo type_done
    End If
    If Left$(term, 1) = "&" Then 'hex constant
      'Lets convert to integer string
      If Not LCase$(Mid$(term, 2, 1)) = "h" Then SYNTAX 1
'      If right$(term, 1) <> "&" Then term = term + "&"
'      term = trim$(str$(val(term)))
      If Len(term) Mod 2 = 1 Then  'need to insert a 0
         term = "&h0" + Mid$(term, 3)
      End If
      newTerm = ""
      For i = 3 To Len(term) Step 2
          c = Mid$(term, i, 1)
          If c >= "0" And c <= "9" Then
             j = (Asc(c) - Asc("0")) * 16
          ElseIf LCase$(c) >= "a" And LCase$(c) <= "f" Then
             j = ((Asc(LCase$(c)) - Asc("a")) + 10) * 16
          Else: SYNTAX 2
          End If
          c = Mid$(term, i + 1, 1)
          If c >= "0" And c <= "9" Then
             j = j + (Asc(c) - Asc("0"))
          ElseIf LCase$(c) >= "a" And LCase$(c) <= "f" Then
             j = j + (Asc(LCase$(c)) - Asc("a")) + 10
          Else: SYNTAX 3
          End If
          newTerm = newTerm + Chr$(j)
''sgBox "hex=" + str$(j)
       Next
       term = newTerm
       termType = 5
       term_len = Len(newTerm)
'       term_len = Len(term)
 'sgBox "returning hex of len " + str$(Len(term))
       GoTo type_done
    End If
    term = LCase$(term)              '***added 11/20/2000
    If chk_num_con() Then
'dbug "got num-const"
      termType = 6     ' num const */
    Else
         func_type = chk_func_name()
         If Not func_type = 0 Then
            termType = FUNCTYPE 'function*/
         
         Else
            If chk_verb() Then
                termType = 2       'verb    */
            Else
               If chk_reserved() Then
                  termType = 3
                  GoTo type_done
               End If
               dbNumber = chk_dbname()
               If dbNumber > 0 Then
'sgBox "setting dbname type"
                  termType = 13
                  GoTo type_done
               End If
               If (chk_data_para()) Then
                   removeBrackets
                   termType = 4     ' data/para name */
                   GoTo type_done
               End If
               termType = 7        ' other */
           End If
         End If
    End If
type_done:
     curCompilePos = thisTermStart
     curCompileLen = Len(term)
'dbug "stmtelem=" + term
   
End Sub
Sub removeBrackets()
  Dim i As Integer
  Dim j As Integer
  Dim c As String
'sgBox "in remove brackets"

retry:
  j = InStr(1, term, ".")
  For i = 1 To Len(term)
    c = Mid$(term, i, 1)
    If c = "[" Then
       If j = 0 Then SYNTAX 4
       If Not Mid$(term, j - 1, 1) = "]" Then SYNTAX 5
       term = Mid$(term, 2, j - 3) + Mid$(term, j, Len(term) - j + 1)
'sgBox "redo as " + term
       GoTo retry
    End If
    If c = "]" And Not i = 1 Then SYNTAX 6
    If c = "]" Then SYNTAX 7
  Next
End Sub
Sub parse_seteventhandled()
   out_one_char (&H7)
   
End Sub

Function chk_dbname()
  Dim i As Integer
  
   i = 0
   For Each dbdef In gTarget.DatabaseCollection
      i = i + 1
    '04042004 the following IF made into a 2-line stmt
    If LCase$(dbdef.Name) = LCase$(term) _
    And (dbdef.LocalOrGlobal = "l" And LocalID = dbdef.LocalSource) Then
         chk_dbname = i
'sgBox "is dbname #" + str$(i)
         Exit Function
      End If
   Next
   
  i = 0                                                                    'added 04042004
  For Each dbdef In gTarget.DatabaseCollection                               'added 04042004
    i = i + 1                                                              'added 04042004
                                                                           'added 04042004
    If LCase$(dbdef.Name) = LCase$(term) And dbdef.LocalOrGlobal = "g" Then  'added 04042004
       chk_dbname = i                                                      'added 04042004
       Exit Function                                                       'added 04042004
    End If                                                                 'added 04042004
  Next                                                                     'added 04042004

   chk_dbname = 0
'sgBox "not dbname= " + term + "  #dbs=" + str$(model1.DatabaseCollection.count)
End Function

Function term_is(chk_term As String) As Boolean
    'check if "term" = parameter------*/
    'If LCase$(term) = LCase$(chk_term) Then term_is = True _
    'Else: term_is = False                   'not =
    
    term_is = (StrComp(term, chk_term) = 0)
End Function

'MMD: Unused function
'Sub strcpy(too As String, from As String)
'   too = from
'End Sub

Function initialize_valu()
    Dim Dummy As Boolean
     Dim one_num As Double
    one_num = 0
    
    data.Length = 11
    'DATA.dgt_bef = 7
    'DATA.dgt_aft = 2
    data.Dgt_Bef = 0
    data.Dgt_Aft = 0
    data.Kind = "n"
    data.max_no_values1 = 1
    data.max_no_values2 = 0
    data.max_no_values3 = 0
    data.Cur_No_Values = 1
    data.single_value = one_num
    
End Function

Function new_term_not(chk_term As String) As Boolean    'get new term & chk against param--*/
    get_term
'sgBox "at new-term-not--looking for=" + chk_term + " got=" + term
    If term = chk_term Then
        new_term_not = False ' ==
    Else
        new_term_not = True 'not =
    End If
End Function

Function term_not(chk_term As String) As Boolean
   ' check if "term" not = parameter

    If Not term = chk_term Then
        term_not = True 'not =*/
    Else
        term_not = False '*===*/
    End If
End Function

Function locate_data_tbl() As Integer  'locate data elem by name
Dim lvl As Integer
Dim save_term As String
Dim i As Integer
Dim j As Integer
Dim k As Integer
Dim c As Integer
Dim cnt As Integer
Dim have_period As Integer
Dim Dgt_Bef As Integer
Dim nnn As Double
'aView  * view2=null_ptr
Dim one_num As Double
Dim one_string As String
'sgBox "at locate_data term=" + term + "   type=" + str$(termType)

   If (termType = 4) Then GoTo loc_data_name
   If (termType = 5) Then GoTo loc_data_alpha
   If (termType = 6) Then GoTo loc_data_numer
   term_tbl_no = 0
   locate_data_tbl = 0
   Exit Function

loc_data_numer:
   c = 1
   cnt = 0
   have_period = 0
   Do While c <= Len(term)
      If ((Mid$(term, c, 1) = "+") Or (Mid$(term, c, 1) = "-")) Then
         If (Not c = 1) Then
            SYNTAX 8
            locate_data_tbl = 0
            Exit Function
         End If
      Else
         If (Mid$(term, c, 1) = ".") Then
            If (have_period = 1) Then
               SYNTAX 9
               locate_data_tbl = 0
               Exit Function
            Else
               have_period = 1
               Dgt_Bef = cnt
               cnt = 0
            End If
         Else
            If ((Mid$(term, c, 1) < "0") Or (Mid$(term, c, 1) > "9")) Then
               SYNTAX 10
               locate_data_tbl = 0
               Exit Function
            Else
               cnt = cnt + 1
            End If
         End If
      End If
      c = c + 1
   Loop

   nnn = Val(term)
   For Each data In gTarget.DataCollection
      If (Mid$(data.Name, 1, 1) = "+") Then
         one_num = data.single_value
         If (one_num = nnn) Then
            term_tbl_no = data.tbl_no
            locate_data_tbl = 1
            Exit Function '/*found matching const--use it */
         End If
      End If
   Next

   'no matching const
   num_con_seq_no = num_con_seq_no + 1
   save_term = term

   term = "+" & Trim$(str$(num_con_seq_no))
   add_data_name_to_tbl ("global")
   data.isConstant = True
   term_tbl_no = data.tbl_no
   data.single_value = nnn
   If (have_period = 0) Then
      data.ByteFlag = &H80
      data.Dgt_Bef = cnt
      data.Dgt_Aft = 0
   Else
      data.ByteFlag = &H40
      data.Dgt_Bef = Dgt_Bef
      data.Dgt_Aft = cnt
   End If
   data.Length = data.Dgt_Bef + data.Dgt_Aft + 2
   If (data.Dgt_Aft = 0) Then
      data.Kind = "i"
   Else
      data.Kind = "n"
   End If
   data.max_no_values1 = 1
   data.max_no_values2 = 0
   data.max_no_values3 = 0
   data.Cur_No_Values = 1
   locate_data_tbl = 1
   Exit Function

loc_data_all_lit:
loc_data_alpha:
   For Each data In gTarget.DataCollection
      If (Mid$(data.Name, 1, 1) = ".") Then
         one_string = data.single_value
         If (one_string = term) Then
            term_tbl_no = data.tbl_no
            locate_data_tbl = 1
            Exit Function
         End If
      End If
   Next

   'no match
   alpha_con_seq_no = alpha_con_seq_no + 1
   save_term = term

   term = "." & Trim$(str$(alpha_con_seq_no))
   add_data_name_to_tbl ("global")
   data.isConstant = True         'added 821 *********************
   term_tbl_no = data.tbl_no
   data.Dgt_Bef = Len(save_term)
   data.Length = data.Dgt_Bef
   data.single_value = save_term
   data.Dgt_Aft = 0
   data.Kind = "s"
   locate_data_tbl = 1
   Exit Function

loc_data_name:
   For Each data In gTarget.DataCollection
'If compiler_debug = True And Not DATA.name = "string_work" And Not DATA.name = "arith_work" Then
'sgBox "comparing " + DATA.name + " to " + term
'End If
      If (StrComp(data.Name, term) = 0) _
            And (data.LocalOrGlobal = "l" And LocalID = data.LocalSource) Then
         GoTo loc_name_found_match
      End If
   Next
   For Each data In gTarget.DataCollection
      If (StrComp(data.Name, term) = 0) And data.LocalOrGlobal = "g" Then
            GoTo loc_name_found_match
      End If
   Next
   GoTo loc_name_no_match

loc_name_found_match:
'If compiler_debug = True Then
'dbug "got match" + term
'End If
   term_tbl_no = data.tbl_no

loc_skip_used:
'sgBox "MATCH term=" + term
   locate_data_tbl = 1
   Exit Function

loc_name_no_match:
'If compiler_debug = True Then
'dbug "no-MATCH term=" + term
'End If
   term_tbl_no = 0
   locate_data_tbl = 0
End Function

Function locateDataByName(Name As String) As CDataElement
  Dim d As CDataElement

   For Each d In gTarget.DataCollection
'If compiler_debug = True And Not DATA.name = "string_work" And Not DATA.name = "arith_work" Then
'sgBox "comparing " + DATA.name + " to " + term
'End If
      If (StrComp(d.Name, Name) = 0) _
            And (d.LocalOrGlobal = "l" And LocalID = d.LocalSource) Then
         GoTo loc_name_found_match
      End If
   Next
   For Each d In gTarget.DataCollection
'If compiler_debug = True And Not DATA.name = "string_work" And Not DATA.name = "arith_work" Then
'sgBox "comparing " + DATA.name + " to " + term
'End If
      If (StrComp(d.Name, Name) = 0) _
            And d.LocalOrGlobal = "g" Then
         GoTo loc_name_found_match
      End If
   Next
   GoTo loc_name_no_match

loc_name_found_match:
'If compiler_debug = True Then
'dbug "got match" + term
'End If
   Set locateDataByName = d
   Exit Function

loc_name_no_match:
   Set locateDataByName = Nothing
End Function

Function find_de_by_no(de_no As Integer) As CDataElement                '/*uses d.e. # to locate d.e. tbl entry*/
   If de_no = 0 Then
     Set find_de_by_no = Nothing
   Else
     Set find_de_by_no = gTarget.DataCollection.Item(de_no)
   End If
End Function

Sub print_err(ByVal Msg As String)
   compile_no_good = 9999
   MsgBox gStringTable(3103) + Msg '+ "'."   'Error...
'sgBox "err#=" + str$(temp)
'MsgBox "err#=" + str$(temp)
err.Raise 1000
  
End Sub
'added routine 08222002
Sub get_term_left_paren()
   get_term
   If se.maj = "p" And se.sub1 = 0 Then Exit Sub
   SYNTAX 11
End Sub
'added routine 08222002
Sub get_term_right_paren()
   get_term
   If se.maj = "p" And se.sub1 = 1 Then Exit Sub
   SYNTAX 12
End Sub

'MMD: Redundant sub
'Sub get_dataname()
'    get_data_name
'End Sub

Sub get_dataname_num()  '/*find dataname--must be dataname & numeric type*/
   get_dataname
   If (err_code = 0) Then
      If (termType = 6) Then Exit Sub '/*num lit*/
      If (termType = 4) Then
         If (Not data.Kind = "s") Then Exit Sub '/*num data variable*/
      End If
   End If
   print_err gStringTable(3106) '"Expecting a numeric variable or numeric constant."
End Sub

Sub get_dataname_string()  '/*find dataname--must be dataname & string type*/
   get_dataname
'sgBox "error kind =" + DATA.kind + "errcode=" + str$(err_code) + " termType=" + str$(termType)
   If (err_code = 0) Then
      If (termType = 5) Then Exit Sub '/*alpha lit*/
      If (termType = 4) Then
         If data.Kind = "s" Then Exit Sub  '/*alpha data variable*/
      End If
   End If
   print_err gStringTable(3107) + term + " " + str$(termType) '"Expecting a variable of type STRING or a string literal surrounded by quote marks. Term and type: "
End Sub

Sub get_dataname()  '/*--- find next data name--------------*/
Dim save_data As New CDataElement
    
   get_dataname_nosubs
   If (err_code = 0) Then
      s1_tbl_no = theTermSub1
      s2_tbl_no = theTermSub2
      s3_tbl_no = theTermSub3

      If allowArrayNames = False Then  'added 805 *************************************
         If (data.max_no_values1 > 1 And s1_tbl_no = 0) _
               Or (data.max_no_values2 > 1 And s2_tbl_no = 0) _
               Or (data.max_no_values3 > 1 And s3_tbl_no = 0) Then
            print_err gStringTable(3108) '"Missing required levels of subscripting."
         End If
      End If                            'added 805 ***********************************
   End If
End Sub

'MMD: Redundant sub name
'Sub get_dataname_nosubs()
'    get_dataname_nosubs
'End Sub

Sub get_dataname_nosubs()  '/*get data name w/o subscripts--------*/
   err_code = 0
   get_term
   If term = "_end-line" Then
      err_code = 4
      GoTo exitIt
   End If

'sgBox "at nosubs found term=" + term + " maj=" + theTermMaj
   If theTermMaj = "d" Then
'sgBox "assigning by no=" + str$(theTermDe_no)
      err_code = 0
      Set data = find_de_by_no(theTermDe_no)
      term_tbl_no = data.tbl_no
   Else
'sgBox "gdn didn't get dataname=" + term
      If locate_data_tbl() = 0 Then
         err_code = 4    '/*err if not in tbl*/
      End If
   End If

exitIt:
'sgBox "leaving get_dataname_nosubs --err_code=" + str$(err_code)
   s1_tbl_no = 0
   s2_tbl_no = 0
   s3_tbl_no = 0
End Sub

Sub process_a_char() ' /*-----process one single char from input-*/
    Dim Val As Long
    Dim save_cur As String
'dbug "at process_a_char=" + cur_char
    If (end_input) Then
      termin = ""
      cur_char = ""
      Exit Sub
    End If
    If (quote_mode) Then
        If ((cur_char = end_line) Or (cur_char = line_feed)) Then
          get_next_char
          Exit Sub
        Else
           If (cur_char = quote_con) Then
              look_ahead_a_char
              If (look_ahead_char = quote_con) Then
                 get_next_char
                 insert_char
                 get_next_char
                 Exit Sub
               Else
                  termin = cur_char  '/ not spec char*/
                  Exit Sub
               End If
           Else
               insert_char
               get_next_char
               Exit Sub
           End If
        End If
    End If
    If (bracket_mode) Then
        If ((cur_char = end_line) Or (cur_char = line_feed)) Then
          termin = cur_char
          Exit Sub
        Else
               If cur_char = "]" Then bracket_mode = False
               insert_char
               get_next_char
               Exit Sub
        End If
    End If
''dbug "at process select -- cur_char=" + cur_char
reselect_case:
    Select Case cur_char
      'Case "_"
      '   termin = cur_char
      '   Exit Sub
      '04012005 Case end_line, line_feed
      Case end_line            'added 04012005
           'termin = cur_char
           '04012005  termin = end_line
              look_ahead_a_char                         'added 07062005
              If (look_ahead_char = line_feed) Then     'added 07062005
                 get_next_char       'added 04012005
                 Exit Sub            'added 040120005
              Else                                      'added 07062005
                  'treat car-ret w/o line-feed as if crlf             'added 07062005
                  currentStatementNumber = currentStatementNumber + 1 'added 07062005
                  termin = end_line                                   'added 07062005
                  endOfLastLine = in_ptr                              'added 07062005
                  Exit Sub                                            'added 07062005
              End If                                 'added 07062005
       Case line_feed                                          'added 04012005
           currentStatementNumber = currentStatementNumber + 1 'added 04012005
           termin = end_line                                   'added 04012005
           endOfLastLine = in_ptr                              'added 04012005
           Exit Sub                                            'added 04012005
      
      Case "'"  'comment
           If quote_mode Then
             GoTo its_in_quotes
           End If
           Do
             get_next_char
           Loop Until cur_char = end_line Or end_input   '***revised 3/13/2001 *************
           If end_input Then       'added 3/13/2001 **************
              termin = ""          'added 3/13/2001 **************
              cur_char = ""        'added 3/13/2001 **************
              Exit Sub             'added 3/13/2001 **************
           End If                  'added 3/13/2001 **************
           GoTo reselect_case
      Case quote_con
'dbug "setting quote mode"
           quote_mode = 1
           get_next_char
           Exit Sub
      Case " ", "", ",", "=", ":"
           termin = cur_char
           Exit Sub
      Case "["
           bracket_mode = True
           GoTo UseIt
      Case "*", "/", "+", "-", "^", ">", "<"
      
'dbug "got blank terminator"
           termin = cur_char
           Exit Sub
      'insertions 04012005
      Case "@"
           If in_ptr = endOfLastLine + 1 Then
               'its a breakpoint char -- ignore
               get_next_char
               GoTo reselect_case:
           End If
      'end of insertions 04012005
      'start insertion 12252005
      Case "&"
          look_ahead_a_char
          If (look_ahead_char = " ") Then
             termin = "+"    'treat ampersand like a plus sign
             cur_char = "+"
             Exit Sub
          End If
          GoTo UseIt
      'end insertions 12252005
      Case Else
its_in_quotes:
           If ((Not quote_mode) And ((cur_char = "(") Or (cur_char = ")"))) Then
              If (paren_is_delim_sw = 1) Then
                  termin = cur_char
                  Exit Sub
               End If
           End If
UseIt:
           insert_char
           get_next_char
           Exit Sub
     End Select
End Sub
Sub get_next_char()         '/*----get char from in buffer_*/
    Dim i As Integer
    If (look_i = 0) Then
       get_next_char_absol
    Else
        '/*return a char from look ahead bufr */
        look_i = look_i - 1
        cur_char = Mid$(look_ahead_buf, 1, 1)
        If cur_char = vbTab Then cur_char = " "
        i = 0
        Do While (i <= look_i)
          Mid$(look_ahead_buf, i + 1, 1) = Mid$(look_ahead_buf, i + 2, 1)
          i = i + 1
        Loop
    End If
    
End Sub
Sub term_err_stop(str As String)
   MsgBox (str)
   MsgBox gStringTable(3227) '"Compile will continue, but is not successful."
   'End
End Sub
Sub get_next_char_absol()
   '10.22.06 GH code optimized
   If (end_input) Then
     cur_char = ""
     termin = ""
     Exit Sub
   End If
   
   in_ptr = in_ptr + 1
   cur_char = Mid(in_buf, in_ptr + 1, 1)
   If LenB(cur_char) > 0 Then
     Select Case Asc(cur_char)
        Case 13: curCompileLine = curCompileLine + 1 'CR
        Case 9:  cur_char = " " 'tab
     End Select
   Else
     end_input = 1
     cur_char = ""
     termin = ""
   End If
End Sub

Sub build_look_ahead_buf()        '/*--build up look ahead bufr---*/
    get_next_char_absol
    If (end_input) Then
      cur_char = ""
      Mid$(look_ahead_buf, look_i + 1, 1) = ""
      Exit Sub
    End If
    Mid$(look_ahead_buf, look_i + 1, 1) = cur_char
    look_i = look_i + 1
    Mid$(look_ahead_buf, look_i + 1, 1) = ""
End Sub
Sub look_ahead_a_char()        '/*---peek ahead one char to see what it is*/
    If (Not look_i = 0) Then
      look_ahead_char = Mid$(look_ahead_buf, 1, 1)
      Exit Sub
    End If
    If (end_input) Then
      look_ahead_char = ""
      Exit Sub
    End If
    look_ahead_char = Mid$(in_buf, in_ptr + 2, 1)
End Sub
Sub remove_lead_blanks()   '/*----skip by all leading blank chars---*/
    If (end_input) Then Exit Sub
    Do
       get_next_char
       
    Loop While ((cur_char = " ") Or (cur_char = "@"))  'modified 04012005
End Sub
Sub insert_char()
    '/*---add cur char to term string building*/
    If (term_len = (term_len_max - 1)) Then
       print_err gStringTable(3109) + term_len_max 'Found a term longer than limit of
       Exit Sub
    End If
    term = term + cur_char
    term_len = term_len + 1
End Sub

Function chk_data_para() As Integer '/*------chk if term is data or parag name--*/
    Dim i As Integer
    Dim periodSw As Boolean
    Dim brackSw As Boolean
    brackSw = False
    
    periodSw = False
 If compiler_debug = True Then
 MsgBox "checking datapara for " + term
 End If
    i = 0
    Do
     i = i + 1
     If i > Len(term) Then
        Exit Do
     End If
     
     one_char = Mid$(term, i, 1)
     If (one_char = "_") Then GoTo continue
     If one_char = "[" And i = 1 Then
        brackSw = True
        GoTo continue
     End If
     If one_char = "]" And brackSw Then
        brackSw = False
        GoTo continue
     End If
     If brackSw Then GoTo continue
     
     one_char = LCase$(one_char)
     
     If one_char = "." And i > 1 And i < Len(term) Then
       periodSw = True
       GoTo continue
     End If
     If ((one_char >= "a") And (one_char <= "z")) Then GoTo continue
     If ((one_char < "0") Or (one_char > "9")) Then
not_data:
         chk_data_para = 0
         Exit Function
     End If
     If i = 1 Then GoTo not_data
continue:
    Loop
'dbug "setting chk_data_para=1"
    chk_data_para = 1
End Function

Sub graph_change_cursor(too As String)
    If too = "n" Then
       Screen.MousePointer = vbDefault
    Else
       Screen.MousePointer = vbHourglass
    End If
End Sub

'041601 MMD NULL function
'Sub graph_blink_cursor()
'
'End Sub

Sub chk_for_subscripts()
''no longer used
    Dim test As String
    Dim save_term As String
    Dim save_area As Integer
    Dim save_tbl_no As Integer
    Dim save_type As Integer
    Dim save_len As Integer
    Dim dt As New CDataElement
    
    Dim s1_save As Integer
    Dim s2_save As Integer
    Dim s3_save As Integer
    
    Set dt = data
    save_term = term
    save_tbl_no = term_tbl_no
    save_area = term_area
    save_type = termType
    save_len = term_len
    s1_tbl_no = 0
    s2_tbl_no = 0
    s3_tbl_no = 0
   
    If (termin = " ") Then
      Do
        look_ahead_a_char
        If (look_ahead_char = " ") Then skip_over_input_space
      Loop While (look_ahead_char = " ")
    
    Else
       look_ahead_char = termin
    End If

'sprintf(debug,"look-ahead-char is %c",look_ahead_char)
    If (Not look_ahead_char = "(") Then GoTo chk_subs_return
    If (new_term_not("(")) Then
        term_used = 0
        GoTo chk_subs_return
    End If

    get_dataname_nosubs
    If (Not err_code = 0) Then GoTo subs_not_defined
    If (Not termType = 6) Then
       If (Not termType = 4) Then GoTo chk_subs_syntax
    End If
    If (Not data.Kind = "i") Then GoTo subs_not_numer
    s1_tbl_no = term_tbl_no
'sgBox "set sub1 to " + str$(s1_tbl_no)
      
    get_term
    If (term_is(")")) Then GoTo chk_subs_return
    term_used = 0
    get_dataname_nosubs
    If (Not err_code = 0) Then GoTo subs_not_defined
    If (Not termType = 6) Then
       If (Not termType = 4) Then GoTo chk_subs_syntax
    End If
    If (Not data.Kind = "i") Then GoTo subs_not_numer
    s2_tbl_no = term_tbl_no
'sgBox "set sub2 to " + str$(s2_tbl_no)

    get_term
    If (term_is(")")) Then GoTo chk_subs_return
    term_used = 0
    get_dataname_nosubs
    If (Not err_code = 0) Then GoTo subs_not_defined
    If (Not termType = 6) Then
       If (Not termType = 4) Then GoTo chk_subs_syntax
    End If
    If (Not data.Kind = "i") Then GoTo subs_not_numer
    s3_tbl_no = term_tbl_no
'sgBox "set sub3 to " + str$(s3_tbl_no)
    get_term
    If (term_is(")")) Then GoTo chk_subs_return
    term_used = 0
    GoTo chk_subs_syntax
chk_subs_return:
    If ((dt.max_no_values1 > 1) And (s1_tbl_no = 0)) Then
       term_sub_present = "n"
       term = "-999"
       termType = 6
       term_len = 1
       locate_data_tbl
       s1_tbl_no = data.tbl_no
'sprintf(test,"assigned subscript=%s (%ul)",term,s1_tbl_no)
    ElseIf ((dt.max_no_values1 > 1) And (s1_tbl_no > 0)) _
       And ((dt.max_no_values2 > 1) And (s2_tbl_no > 0)) _
       And ((dt.max_no_values3 > 1) And (s3_tbl_no > 0)) Then
       term_sub_present = "y"
    Else
       GoTo chk_subs_syntax
    End If
    term_len = save_len
    termType = save_type
    term_area = save_area
    term_tbl_no = save_tbl_no
    term = save_term
    Exit Sub
chk_subs_syntax:
    SYNTAX 13
    GoTo chk_subs_return
subs_not_numer:
    print_err gStringTable(3110) '"Subscripts must be numeric constants or variables.")
    GoTo chk_subs_return
subs_not_defined:
    
    print_err gStringTable(3111) '"Name used as a subscript is not defined elsewhere.")
    GoTo chk_subs_return
End Sub
Sub skip_over_input_space()   '/*--skip space in input stmt---*/
    get_next_char
    Exit Sub
End Sub
Sub add_to_para_tbl()    '/*----add to para tbl----------*/
   
    Set p = New CParaTbl
    parag_tbl_no = parag_tbl_no + 1
    p.tbl_no = parag_tbl_no
    p.name_ptr = term
    'gtarget.ParagCollection.Add p, p.name_ptr  'commented out 4/07/2001 ***
    gTarget.ParagCollection.Add p               'added 4/07/2001  ***
'sprintf(debug,"created para=%p first=%p last=%p",p,first_para_tbl_ptr,last_para_tbl_ptr)
End Sub
Sub add_to_link_tbl()    '/*----add to para tbl----------*/
    
    Set p = New CParaTbl
    link_tbl_no = link_tbl_no + 1
    p.tbl_no = link_tbl_no
    p.name_ptr = term
    gTarget.LinkCollection.Add p, p.name_ptr
'sprintf(debug,"created para=%p first=%p last=%p",p,first_para_tbl_ptr,last_para_tbl_ptr)
End Sub

Sub chk_outstand_ifs()   '/*----chk outstanding ifs-------*/
    '??not used
    Dim i As Integer
    Dim p As CParaTbl
    If (Not if_level = 0) Then
      i = 1
      Do While i <= if_level
        p = loc_para_ptr(para_false_ptr(i))
        If (p = para_null_ptr) Then
           term_err_stop gStringTable(3228) '"Bad IF logic in the internals of the program.")
        End If
        p.defined = 1
        p.offset = proc_offset
        para_false_ptr(i) = 0
        i = i + 1
      Loop
      if_level = 0
    End If
End Sub
Sub get_para_name()  '/*------get para name---------*/
    Dim result As Integer
    get_term
    err_code = 0
    If (Not termType = 4) Then
       err_code = 10
'dbug "termType=" + str$(termType) + "  term=" + term + " len=" + str$(Len(term))
       print_err gStringTable(3112) '"Expecting a valid LABEL name.")
       Exit Sub
    End If
    result = locate_para_tbl
    If (result = 0) Then add_to_para_tbl
    term_tbl_no = p.tbl_no
    Exit Sub
End Sub
Sub get_link_name()  '/*------get para name---------*/
    Dim result As Integer
    get_term
    err_code = 0
    If (Not termType = 4) Then
       err_code = 10
'dbug "termType=" + str$(termType) + "  term=" + term + " len=" + str$(Len(term))
       print_err gStringTable(3113) '"Expecting a valid subroutine/function name.")
       Exit Sub
    End If
    result = locate_link_tbl
    If (result = 0) Then add_to_link_tbl '???
    term_tbl_no = p.tbl_no
    Exit Sub
End Sub
Sub out_file_ptr(file_ptr As CFileEntry)
    out_the_string (file_ptr.Name)
End Sub
Sub out_one_char(the_byte As Byte)    'out one char as two bytes to avoid unicode problems
    If (proc_offset = code_buff_max) Then
       abort_too_big
    End If
    code_buffer = code_buffer & Chr$(Int(the_byte / 64) + 1) & Chr$((the_byte Mod 64) + 1)
    proc_offset = proc_offset + 1
End Sub
Sub out_one_char_of_string(the_char As String)
  If the_char = "" Then
    out_one_char (0)
  Else
    out_one_char (Asc(the_char))
  End If
End Sub
Sub OLD_out_one_char_of_string(the_char As String)
   If (proc_offset = code_buff_max) Then
     abort_too_big
    End If
    If the_char = "" Then
       code_buffer = code_buffer + Chr$(255) + Chr$(1)
    ElseIf Asc(Mid$(the_char, 1, 1)) = &HFF Then
       code_buffer = code_buffer + Chr$(255) + Chr$(2)
    Else
       code_buffer = code_buffer + the_char
    End If
    proc_offset = proc_offset + 1
End Sub

Sub OLD_out_one_char(the_char As Byte)    '/*------out one character-----------*/
    If (proc_offset = code_buff_max) Then
       abort_too_big
    End If
    If the_char = &H0 Then
       code_buffer = code_buffer + Chr$(255) + Chr$(1)
    ElseIf the_char = &HFF Then
       code_buffer = code_buffer + Chr$(255) + Chr$(2)
    Else
         code_buffer = code_buffer & Chr$(the_char)
    End If
    If Len(code_buffer) = 6 Then
      MsgBox "it's 6 " + str$(the_char) + str$(Asc(Mid$(code_buffer, 6, 1))) '0401
    End If
    proc_offset = proc_offset + 1
End Sub
Sub out_one_integ(i As Integer)  '/*------output one integer----------*/
    Dim l As Byte
    Dim m As Byte
    Dim sw As String
    sw = "+"
    If i < 0 Then
       sw = "-"
       i = Abs(i) - 1
    End If
    l = Int(i / 256)
    m = Int(i - l * 256)
       
    If sw = "-" Then
      l = 255 - l
      m = 255 - m
    End If
    out_one_char l
    out_one_char m
End Sub
Sub out_one_unsignedInteg(i As Long)  '5/7/1
   Dim m1 As Byte
   Dim m2 As Byte
   Dim wk As Long
   
   If i > CLng(65536) Then print_err gStringTable(3114) '"Module has exceeded size limit."
   m1 = Int(i / 256)
   wk = m1
   wk = wk * 256
   m2 = Int(i - wk)
   
   out_one_char m1
   out_one_char m2
End Sub


Sub out_the_string(str As String)
    Dim i As Integer
    If ((proc_offset + Len(str)) >= code_buff_max) Then abort_too_big

    
    For i = 1 To Len(str)
      out_one_char_of_string (Mid$(str, i, 1))
    Next
    
    out_one_char (&H0)
End Sub
Sub out_tok_1arg(the_token As Byte)       '  /*---output token + 1 argument---*/
    out_one_char (the_token)
    out_1arg
End Sub
Sub out_tok_2arg(the_token As Byte)       '  /*---output token + 2 argument---*/
    out_one_char (the_token)
    out_2arg
End Sub
Sub out_tok_3arg(the_token As Byte)       '  /*---output token + 3 argument---*/
    out_one_char (the_token)
    out_3arg
End Sub
Sub out_tok_4arg(the_token As Byte)       '  /*---output token + 3 argument---*/
    out_one_char (the_token)
    out_4arg
End Sub
Sub out_tok_5arg(the_token As Byte)       '  /*---output token + 3 argument---*/
    out_one_char (the_token)
    out_5arg
End Sub
Sub out_1arg()     '/*------output 1 argument---------*/
    out_the_1st_arg
End Sub
Sub out_2arg()          '/*------output 2 arguments--------*/
    out_the_1st_arg
    out_the_2cnd_arg
End Sub
Sub out_3arg()         '/*------output 3 arguments--------*/
    out_the_1st_arg
    out_the_2cnd_arg
    out_the_3rd_arg
End Sub
Sub out_4arg()         '/*------output 3 arguments--------*/
    out_the_1st_arg
    out_the_2cnd_arg
    out_the_3rd_arg
    out_the_4th_arg
End Sub
Sub out_5arg()         '/*------output 3 arguments--------*/
    out_the_1st_arg
    out_the_2cnd_arg
    out_the_3rd_arg
    out_the_4th_arg
    out_the_5th_arg
End Sub
Sub out_an_arg(arg As Integer, Sub_1 As Integer, Sub_2 As Integer, Sub_3 As Integer)
    Dim d As CDataElement
    
    out_one_integ (arg)
    If arg = 0 Then Exit Sub
    Set d = find_de_by_no(arg)
   
    
    '805 comment out If d.max_no_values1 > 1 And (sub_1 > 0) Then  '***************************
    If d.max_no_values1 > 1 Then   '805 added *************************************************
         out_one_integ (Sub_1)
         '805 commented out If d.max_no_values2 > 1 And (sub_2 > 0) Then  '************************
         If d.max_no_values2 > 1 Then     '805 added **********************************************
            out_one_integ (Sub_2)
            '805 commented out If d.max_no_values3 > 1 And (sub_3 > 0) Then  '***************************
            If d.max_no_values3 > 1 Then  '805 added ****************************************************
               out_one_integ (Sub_3)
            End If
         End If
     End If
End Sub
Sub out_the_1st_arg()             '/*----put out arg 1------------------*/
    out_an_arg arg_1, arg1_occ1, arg1_occ2, arg1_occ3
End Sub
Sub out_the_2cnd_arg()            ' /*----put out arg 2------------------*/
    out_an_arg arg_2, arg2_occ1, arg2_occ2, arg2_occ3
End Sub
Sub out_the_3rd_arg()            ' /*----put out arg 3------------------*/
    out_an_arg arg_3, arg3_occ1, arg3_occ2, arg3_occ3
End Sub
Sub out_the_4th_arg()            ' /*----put out arg 3------------------*/
    out_an_arg arg_4, arg4_occ1, arg4_occ2, arg4_occ3
End Sub
Sub out_the_5th_arg()             '/*----put out arg 3------------------*/
    out_an_arg arg_5, arg5_occ1, arg5_occ2, arg5_occ3
End Sub
Function locate_para_tbl() As Integer '   /*--locate paragraph tbl-----*/
  Dim i As Integer                     'added 4/07/2001 ***
  i = 0                                'added 4/07/2001 ***
  For Each p In gTarget.ParagCollection
    i = i + 1                          'added 4/07/2001 ***
'sgBox "start=" + str$(startingParagCount)
   If i > startingParagCount Then    'added 4/07/2001 ***
      If p.name_ptr = term Then
         locate_para_tbl = p.tbl_no
         Exit Function
      End If
    End If                             'added 4/07/2001 ***
  Next
  
  locate_para_tbl = 0
  Set p = para_null_ptr
End Function

Function locate_link_tbl() As Integer '   /*--locate paragraph tbl-----*/
'If compiler_debug Then
'dbug "in locate-link"
'End If
  Dim temp As String

   temp = LCase$(term)
   For Each p In gTarget.LinkCollection
'If compiler_debug Then
'sgBox "link comparing =" + p.name_ptr + " to term=" + term
'End If
      If p.name_ptr = temp Then
         locate_link_tbl = p.tbl_no
         Exit Function
      End If
   Next

   locate_link_tbl = 0
   Set p = para_null_ptr
End Function

Function loc_para_ptr(parag_no As Integer) As CParaTbl '/*-locate paragraph ptr---*/
   For Each p In gTarget.ParagCollection
     If p.tbl_no = parag_no Then
        Set loc_para_ptr = p
        Exit Function
     End If
   Next
   Set loc_para_ptr = para_null_ptr
   Exit Function
End Function
Function loc_link_ptr(parag_no As Integer) As CParaTbl '/*-locate paragraph ptr---*/
   For Each p In gTarget.LinkCollection
     If p.tbl_no = parag_no Then
        Set loc_link_ptr = p
        Exit Function
     End If
   Next
   Set loc_link_ptr = para_null_ptr
   Exit Function
End Function

Sub reset_args()                   '/*---reset args to nulls------------*/
   arg_1 = 0
   arg_2 = 0
   arg_3 = 0
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
   arg2_occ1 = 0
   arg2_occ2 = 0
   arg2_occ3 = 0
   arg3_occ1 = 0
   arg3_occ2 = 0
   arg3_occ3 = 0

   Set d1 = dataelem_null_ptr
   Set d2 = dataelem_null_ptr
   Set d3 = dataelem_null_ptr
End Sub

Sub set_arg_1()                  ' /*--------set argument 1------------*/
    Set d1 = data
    arg_1 = term_tbl_no
    arg1_occ1 = s1_tbl_no
    arg1_occ2 = s2_tbl_no
    arg1_occ3 = s3_tbl_no
End Sub
Sub set_arg_2()                 '  /*--------set argument 2------------*/
    Set d2 = data
    arg_2 = term_tbl_no
    arg2_occ1 = s1_tbl_no
    arg2_occ2 = s2_tbl_no
    arg2_occ3 = s3_tbl_no
End Sub
Sub set_arg_3()                  ' /*--------set argument 3------------*/
    Set d3 = data
    arg_3 = term_tbl_no
    arg3_occ1 = s1_tbl_no
    arg3_occ2 = s2_tbl_no
    arg3_occ3 = s3_tbl_no
End Sub
Sub set_arg_4()                  ' /*--------set argument 4------------*/
    Set d4 = data
    arg_4 = term_tbl_no
    arg4_occ1 = s1_tbl_no
    arg4_occ2 = s2_tbl_no
    arg4_occ3 = s3_tbl_no
   
End Sub
Sub set_arg_5()                  ' /*--------set argument 5------------*/
    Set d5 = data
    arg_5 = term_tbl_no
    arg5_occ1 = s1_tbl_no
    arg5_occ2 = s2_tbl_no
    arg5_occ3 = s3_tbl_no
End Sub
Sub abort_too_big()
   term_err_stop gStringTable(3116) '"Compiled code exceeds internal code buffer size.")
End Sub
Function load_alloc_data() As CDataElement
   Set load_alloc_data = New CDataElement
End Function

Function add_data_name_to_tbl(LocOrGlob As String)
   'put data name into data elem tbl
   Set data = load_alloc_data
   initialize_valu
   data.Name = term
   If LocOrGlob = "local" Then
      data.LocalOrGlobal = "l"
      data.LocalSource = LocalID
   Else
      data.LocalOrGlobal = "g"
      data.LocalSource = ""
   End If
   gTarget.AddDataElement data
End Function

Function new_is(chk_term As String) As Boolean
    If new_not(chk_term) Then
       new_is = False
    Else
       new_is = True
    End If
End Function

Sub get_string()             '/*-----get parsed string of char---------*/

 'dbug "at get_string"
    If (end_input) Then
      term = ""
      termin = " "
      term_len = 4
      termType = 2
      Exit Sub
    End If
    If termin = "*" Or termin = "/" Or termin = "+" Or termin = "-" Or termin = "^" _
                    Or termin = "<" Or termin = ">" Then
       term = termin
       termin = " "
       term_len = 1
       
       Exit Sub
    End If
    remove_lead_blanks
'dbug "returned from remove lead blanks"
    thisTermStart = in_ptr
    termin = "~"
    bracket_mode = False
    Do
       process_a_char
    Loop While (termin = "~")
    termin = cur_char
    term_area = 2
'dbug "***got string =" + term
End Sub
Function new_not(chk_term As String) As Boolean
    get_term
    If term = chk_term Then
        new_not = False
    Else
        new_not = True
    End If
End Function
Function new_term_is(chk_term As String) As Boolean   '/*------get new term & chk against param--*/
    get_term
    If term = chk_term Then
       new_term_is = True ' == */
    Else
       new_term_is = False ' not = */
    End If
End Function

'/*--------------------------------------------*/
Function compile_all() As Integer
Dim saveHighestSeqNo As Long
   saveHighestSeqNo = gTarget.HighestSeqNo
   ''above must be before 'New' declarations
Dim wkstr As String
Dim ii As Integer
Dim status As Long                '*****revised 3/13/2001 **************

Dim para As CParaTbl
Dim temp As New CDataElement
   Set temp = dataelem_null_ptr
Dim aView_save As New CForm
Dim view2 As New CForm
   Set view2 = aView_null_ptr
Dim Data2  As New CDataElement
   Set Data2 = dataelem_null_ptr
Dim o As Object
   Set o = object_null_ptr
   'QRYNAV *n=null_ptr
Dim old_aView As CForm
Dim view3 As CForm      'added 12182002 *******
   Set old_aView = aView
Dim i As Integer
Dim codeIn As String
Dim projectDir

'sgBox "at compile all"
   compiler_debug = False
   'make sure we are in the right directory
   projectDir = Left(gTarget.pathname, InStrRev(gTarget.pathname, "\"))
   If Mid(projectDir, 2, 1) = ":" Then ChDrive Left(projectDir, 2) 'ignore network drives
   ChDir projectDir

   ''???temp
   On Error GoTo compileFailed     'intercept errors '0401
   Set aView_save = aView '/*switch to first aView of model*/
   Set aView = gTarget.FormCollection(1)
   Set old_aView = aView

   graph_change_cursor "w"

   currentTypename = ""
   code_buffer = ""
   gDimIsDatabase = False
   num_con_seq_no = 0
   alpha_con_seq_no = 0
   compile_no_good = 0
   for_level = 0
   gNextCompileResourceID = gTarget.HighestSeqNo
'sgBox "clearing parags"
   Do While gTarget.TypeDefCollection.count > 0
      gTarget.TypeDefCollection.Remove 1
   Loop
   Do While gTarget.LinkCollection.count > 0
      gTarget.LinkCollection.Remove 1
   Loop
   Do While gTarget.DataCollection.count > (kArithWorkDEMax + kStringWorkDEMax)
      gTarget.DataCollection.Remove gTarget.DataCollection.count
   Loop
'sgBox "there are " + str$(model1.DataCollection.count) + "   dataelems"
   Do While gTarget.DatabaseCollection.count > 0
      gTarget.DatabaseCollection.Remove 1
   Loop
   Do While gTarget.LibraryCollection.count > 0    '11/30/2000 MD
      gTarget.LibraryCollection.Remove 1           '11/30/2000 MD
   Loop                                            '11/30/2000 MD
   
    'additions 12182002 *********************
    Do While gTarget.SelectCollection.count > 0
       gTarget.SelectCollection.Remove 1
    Loop
    for_level = 0
    if_level = 0
    
    For Each view2 In gTarget.FormCollection
        For Each o In view2.ObjectCollection
            For Each view3 In gTarget.FormCollection
                If LCase$(o.obj.Name) = LCase$(view3.Name) Then
                   print_err gStringTable(3372) & o.obj.Name '"A screen object has the same name as a form: "
                End If
            Next
        Next
    Next
    'end of additions 12182002 ***************************

   AddNSBNames
   link_tbl_no = 0
   'graph_blink_cursor '041601 MMD

'---------------
   gTarget.obj_code = ""
   gTarget.obj_code_len = 0
   
   '09.30.2002 GWH Following code block modified to auto define functions
   CollectFuncs
   codeIn = gTarget.pgm_script
   gCorrection = Len(codeIn)
   codeIn = DefineFuncsInStartupCode(codeIn) & vbCrLf & DefineSetThemeFunction()
   gCorrection = Len(codeIn) - gCorrection 'how many bytes did we insert?
   
   If codeIn <> "" Then
      editorSource = gTarget.GlobalID & "|startup"
      thisModuleId = 9906  'pgm-code is always 9906
      status = compile_one_script(codeIn)
      gTarget.obj_code = code_buffer

'dbug "set model obj code len to " + str$(status)
      If (status = -1) Then
         GoTo compile_over
      Else
         gTarget.obj_code_len = Len(code_buffer)
      End If
   End If
   gCorrection = 0

'----------------
   gTarget.termin_obj_code = ""
   gTarget.termin_obj_code_len = 0
'sgBox "model-script=" + model1.pgm_script
   If gTarget.termination_script <> "" Then
'MMD  editor Source = "w"
'MMD  frmCode.Text = model1.termination_script
      editorSource = gTarget.GlobalID & "|termination"
      thisModuleId = 9915  'term-code is always 9915
      status = compile_one_script(gTarget.termination_script)
      gTarget.termin_obj_code = code_buffer
'dbug "set model obj code len to " + str$(status)
      If (status = -1) Then
         GoTo compile_over
      Else
         gTarget.termin_obj_code_len = Len(code_buffer)
      End If
   End If

'----------------
   For Each cod In gTarget.CodeCollection
      cod.obj_code = ""
      cod.obj_code_len = 0
      If cod.pgm_script <> "" Then
'MMD     editor Source = "m"
'MMD     frmCode.Text = cod.pgm_script
         editorSource = cod.GlobalID & "|code"
         thisModuleId = cod.IdNo
         status = compile_one_script(cod.pgm_script)
         cod.obj_code = code_buffer

         If (status = -1) Then
            GoTo compile_over
         Else
            cod.obj_code_len = Len(code_buffer)
         End If
      End If
   Next

'----------------
   For Each Menu In gTarget.MenuCollection
      For Each mnuBar In Menu.MenuBars
         For Each mnu In mnuBar.MenuElems
            mnu.obj_code = ""
            mnu.obj_code_len = 0

            If mnu.menu_script <> "" Then
'MMD           editor Source = "menu"
'MMD           frmCode.Text = mnu.menu_script
               editorSource = mnu.GlobalID & "|code"
               thisModuleId = mnu.IdNo
               status = compile_one_script(mnu.menu_script)
               mnu.obj_code = code_buffer
               If (status = -1) Then
                  GoTo compile_over
               Else
                  mnu.obj_code_len = Len(code_buffer)
               End If
            End If
         Next
      Next
   Next

'----------------
   For Each view2 In gTarget.FormCollection
      Set old_aView = view2
      'graph_blink_cursor '041601 MMD
      view2.obj_code = ""
      view2.obj_code_len = 0
      If view2.pgm_script <> "" Then
         Set aView = view2
         editorSource = aView.GlobalID & "|before"
         thisModuleId = view2.IdNo - 1
         status = compile_one_script(view2.pgm_script)
         view2.obj_code = code_buffer
         If (status = -1) Then
            GoTo compile_over
         Else
            view2.obj_code_len = Len(code_buffer)
         End If
      End If

      view2.obj_code_after = ""
      view2.obj_code_len_after = 0
      If view2.pgm_script_after <> "" Then
         Set aView = view2
         editorSource = aView.GlobalID & "|after"
         thisModuleId = view2.IdNo
         status = compile_one_script(view2.pgm_script_after)
         view2.obj_code_after = code_buffer
         If (status = -1) Then
            GoTo compile_over
         Else
            view2.obj_code_len_after = Len(code_buffer)
         End If
      End If

      view2.event_obj_code = ""
      view2.event_obj_code_len = 0
      If view2.event_script <> "" Then
         Set aView = view2
'MMD     editor Source = "e"
'MMD     frmCode.Text = aView.event_script
         editorSource = aView.GlobalID & "|event"
         thisModuleId = 10800 - view2.IdNo
         status = compile_one_script(view2.event_script)
         view2.event_obj_code = code_buffer
         If (status = -1) Then
            GoTo compile_over
         Else
            view2.event_obj_code_len = Len(code_buffer)
         End If
      End If

      For Each o In view2.ObjectCollection
         o.obj.obj_code = ""
         o.obj.obj_code_len = 0
         If Not o.obj.script = "" Then
            Set saveMouseSelectObject = o
'MMD        editor Source = "o"
'MMD        frmCode.Text = saveMouseSelectObject.obj.script
            editorSource = o.obj.GlobalID & "|code"
            thisModuleId = o.obj.IdNo
            status = compile_one_script(o.obj.script)
            o.obj.obj_code = code_buffer
 'sgBox "obj compile done --status=" + str$(status) + " objCodeLength=" + str$(Len(o.obj.obj_code))
            If (status = -1) Then
               GoTo compile_over
            Else
               o.obj.obj_code_len = Len(o.obj.obj_code)
            End If
         End If
      Next
   Next

   Set aView = aView_save
   editorSource = ""
   ShowStatus gStringTable(3230), True   '"Compiling...",

   'check for undefined subs/funcs
   For Each p In gTarget.LinkCollection
      If (p.defined = 0) Then
         print_err gStringTable(3117) + p.name_ptr '"SUB or FUNCTION not defined:"
      End If
   Next

compile_over: '/*"Compile done"*/
   code_buffer = ""
   graph_change_cursor "n"
   compile_all = (compile_no_good)
   gTarget.HighestSeqNo = saveHighestSeqNo
   wkstr = Dir(DownloadPath + "__temp*.*")
   Do While Not wkstr = ""
      Kill DownloadPath & wkstr
      wkstr = Dir
   Loop
   Exit Function

compileFailed:
   'On Error GoTo 0
   If Not err.Number = 1000 And Not err.Number = 0 Then
      MsgBox gStringTable(3235) + str$(err.Number) + ": " + err.Description 'compile error
   End If
   On Error GoTo 0
   compile_no_good = 1
   GoTo compile_over
End Function

Sub AddNSBNames()
   'adds all of nsb's predefined constants to the project
   'constants must start with nsb or you'll need to fix code in PrcOut
   gTotalNSBvars = 0
   AddNSB "nsbOff", 0
   AddNSB "nsbOn", 1
   AddNSB "nsbUnchecked", 0
   AddNSB "nsbChecked", 1
   AddNSB "nsbDbOk", 0
   
   AddNSB "nsbPenNormal", 0
   AddNSB "nsbPenInverted", 1
   AddNSB "nsbGrey", 2
   AddNSB "nsbGray", 2
   AddNSB "nsbPenGrey", 2
   AddNSB "nsbPenGray", 2
   AddNSB "nsbCustom", 3
   AddNSB "nsbKeyOrButton", 1
   AddNSB "nsbPenUp", 3
   AddNSB "nsbPenDown", 2
   AddNSB "nsbWait", 0
   AddNSB "nsbNoWait", 1
   AddNSB "nsbNo", 0
   AddNSB "nsbYes", 1
   AddNSB "nsbFalse", 0
   AddNSB "nsbTrue", 1
   AddNSB "True", 1
   AddNSB "False", 0
   AddNSB "nsbJogDial", 4    '2012001  added********************************************
   AddNSB "nsbHandEraJog", 5
   AddNSB "nsbSerialIn", 6
   AddNSB "nsbPalm5Way", 7   '2003.01.03 GWH Added
   AddNSB "nsb5Way", 7       '2008.03.31 GWH Added
   AddNSB "nsbFormUpdate", 8
   AddNSB "nsbFormClose", 9
   AddNSB "nsbTimer", 10
   AddNSB "nsbIrCOMM", 1769104237
   AddNSB "nsbRFCOMM", 1919312749 'Bluetooth Virtual Port
   AddNSB "nsbBTCM", 1651794800 'Bluetooth Connection Manager
   AddNSB "nsbSIR", 32769 'SIR
End Sub

Sub AddNSB(Name As String, Value As Variant)
   Dim av As New CDataElement

   For Each data In gTarget.DataCollection
      If StrComp(data.Name, Name) = 0 And data.LocalOrGlobal = "g" Then
         Exit Sub
      End If
   Next

   av.Cur_No_Values = 0
   av.Kind = "i"
   av.Length = 0
   av.max_no_values1 = 1
   av.max_no_values2 = 0
   av.max_no_values3 = 0
   av.LocalOrGlobal = "g"
   av.LocalSource = ""
   av.Name = LCase$(Name)
   av.single_value = Value
   av.isConstant = True
   gTarget.AddDataElement av  '041801 MMD
   gTotalNSBvars = gTotalNSBvars + 1
End Sub

Function compile_one_script(script As String) As Long    '***revised 3/13/2001**************
Dim ii As Integer
Dim work As String
Dim err As Integer
Dim Msg As String
Dim jmpval As Integer
Dim final_para As CParaTbl
Dim p As CParaTbl
Dim scriptTitle As String

'George: The next line is kind of evil.  Script procedures can use parens optionally
'Sub HelloWorld will throw, but Sub HelloWorld() will not, because this ShowStatus
'setup is looking for a ( where there doesn't necessarily need to be one.
'Fix this, or document that optional parens are no longer allowed.
scriptTitle = Left$(script, InStr(script, "(") - 1)
ShowStatus gStringTable(3230) & scriptTitle, True 'compiling

'sgBox "at compile one script=" + Script
   subOrFunc = " "
   in_buf = script
   '/**/
   code_buffer = ""
   currentStatementNumber = 1   'added 04012005
   parse_desc = "DRILLDOWN script"
   parse_type = "d" '/*compiling a drilldown script*/
   err = parseTheScript
'dbug "after parse ---proc_offset=" + str$(proc_offset)
   If err = 0 Then
      For Each p In gTarget.ParagCollection
         If (p.defined = 0) And Not Left$(p.name_ptr, 1) = "=" Then
            print_err gStringTable(3118) + p.name_ptr '"Label not defined."
            err = -1
            GoTo FoundErr
         End If
      Next
      compile_one_script = proc_offset
   Else
FoundErr:                                                               'added 813 ********************
      ShowStatus
      compile_one_script = (err)
   End If
   If Not subOrFunc = " " Then
      print_err gStringTable(3119) '"Missing END SUB or END FUNCTION statement"
   End If
End Function

Sub gen_a_dummy_goto()
    out_one_char &H1E
    out_one_integ para_endif_ptr(if_level)
End Sub

'Sub strcpy(tostr As String, from As String)
'   tostr = from
'End Sub
Sub dbug(Msg As String)
  MsgBox Msg
End Sub

'Copyright 2002 by NS BASIC Corporation.  All rights reserved.
'MMD: This will get moved to MNSBasic when relative paths are introduced
Sub MakeGlobalDirectories()
    '??
    If Dir(fileDirectory, vbDirectory) = "" Then
       MkDir (fileDirectory)
    End If
    
    If Dir(fileDirectory + "\Download", vbDirectory) = "" Then
       MkDir (fileDirectory + "\Download")
    End If
    If Dir(fileDirectory + "\Projects", vbDirectory) = "" Then
       MkDir (fileDirectory + "\Projects")
    End If
    'If Dir(filedirectory + "\codemods", vbDirectory) = "" Then
    '   MkDir (filedirectory + "\codemods")
    'End If
    If Dir(fileDirectory + "\Bitmaps", vbDirectory) = "" Then
       MkDir (fileDirectory + "\Bitmaps")
    End If
   If Dir(fileDirectory + "\Lib", vbDirectory) = "" Then    '11/30/2000 MD
      MkDir (fileDirectory + "\Lib")                        '11/30/2000 MD
   End If                                                '11/30/2000 MD
    DownloadPath = fileDirectory + "\Download\"
End Sub

Sub Main()
Dim index As Integer
Dim userID As Long
Dim username As String
Dim itemIndex As Integer
Dim reg As String
Dim i As Integer
Dim count As Long
Dim randNo As Long
Dim strSN As String
Dim trace As Boolean
trace = True
   
'   projectDirty = False
   g_strTrue = True
   g_strFalse = False

   Randomize
   If trace Then MsgBox "Sub Main " & 1
   'Registry key we want to use
   MWinReg.hKey = HKEY_CURRENT_USER
   #If NSBSymbian Then
      MWinReg.SubKey = "Software\NSBasic\Symbian"
      ProgramsDirectory = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "ProgramsDirectory", "c:\Program Files\nsbasic\Symbian")
      fileDirectory = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "FilesDirectory", "c:\nsbasic_symbian")
   #Else
      MWinReg.SubKey = "Software\NSBasic\Palm"
      ProgramsDirectory = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "ProgramsDirectory", "c:\Program Files\nsbasic\Palm")
      fileDirectory = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "FilesDirectory", "c:\nsbasic")
   #End If
   If trace Then MsgBox "Sub Main " & 2
   MakeGlobalDirectories
   If trace Then MsgBox "Sub Main " & 3
   
   gLanguage = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Language", defaultLanguage)
   LoadStringTable
   If trace Then MsgBox "Sub Main " & 4

   glSerialNumber = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SerialNumber", "Unregistered Demo")
   gnGridIncr = Val(MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "GridIncr", "4"))
   gbWantGrid = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "WantGrid", True)
   gbBuildFat = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Fat", True)
   gbIncludeArmNative = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "IncludeArmNative", False)
   gbAutoSave = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "AutoSave", False)
   gbHiRes = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "HiRes", False)
   gbDana = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "Dana", False)
   If gbDana Then kScreenWidth = 560 Else kScreenWidth = 160
   gbCopyProtect = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "CopyProtect", False)
   gbDebugMode = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "DebugMode", False)
   gbPlainText = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "PlainText", False)
   gLabelFontName = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "IDEFontName", gStringTable(3348)) 'MS Sans Serif
   gLabelCharset = Val(MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "IDEFontCharset", gStringTable(3350))) '0
   gLabelFontSize = Val(MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "IDEFontSize", gStringTable(3349))) '01/19/00 GH
   DownloadOption = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "DownloadOption", "POSE") '04/04/01 GH
   
   gbPOSErun = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "POSErun", True)
   gstrPOSEPath = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "POSEPath", fileDirectory & "\Tools\Emulator.exe") '04/04/01 GH
   gbLaunchPOSE = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "LaunchPOSE", False)
   
   gbSimulatorRun = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SimulatorRun", True)
   gstrSimulatorPath = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "SimulatorPath", fileDirectory & "\Tools\Simulator\PalmSim.exe") '04/04/01 GH
   gbLaunchSimulator = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "LaunchSimulator", False)
   
   'If Not allowRegistration Then gbBuildFat = True
    If trace Then MsgBox "Sub Main " & 5

 #If NSBSymbian Then
   gbCreateS60 = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "CreateS60", True)
   gbCreateUIQ = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "CreateUIQ", False)
   gbRunImmediately = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "RunImmediately", False)
   gstrNextUID3 = MWinReg.GetRegValue(MWinReg.hKey, MWinReg.SubKey, "NextUID3", "E1100001") '07/04/08 GH
   gbPOSErun = False
   gbSimulatorRun = False
#End If
  
   MNSBCodeMax_Initialize
   If trace Then MsgBox "Sub Main " & 6
   
   CheckSerialNumber
   If trace Then MsgBox "Sub Main " & 7
'   frmRegister.CheckSerialNumber
'   Unload frmRegister

   NeedInitialization = 0

   frmMain.Show
'   Load frmMain
'   Load frmSelProj
'   frmSelProj.Show 1
   If compileOkSw And InStr(gCommandLineOptions, "-compile") Then End
End Sub

Sub wordBound(n As Integer)
   Dim j As Long
   Dim c As Byte

   c = &H0
   j = Loc(n)
   If j Mod 2 = 1 Then
      Put n, , c
   End If
End Sub
Sub inputWordBound(n As Integer)
  Dim j As Long
  Dim c As Byte

  c = &H0
  
     j = Loc(n)
     If j Mod 2 = 0 Then

     Else
       Get n, , c

     End If
End Sub
Sub writeTOCRecord3(f As Integer, typ As String, id As Integer, position As Long)
   Dim i As Integer
   Dim c As Byte
   c = &H0
     For i = 1 To 4
       If i > Len(typ) Then
          Put f, , c
       Else
          Put f, , Mid$(typ, i, 1)
       End If
     Next
     writeOutInteger f, id
     writeOutLong f, position
End Sub
Sub writeTOCRecord4(f As Integer, typ As String, id As Integer, position As Long)
   Dim i As Integer
   Dim c As Byte
   c = &H0
     For i = 1 To 4
       If i > Len(typ) Then
          Put f, , c
       Else
          Put f, , Mid$(typ, i, 1)
       End If
     Next
     writeOutInteger f, id
     writeOutLong f, position
End Sub
Function cvtWord(j As Integer) As Integer
    Dim i As Long
    Dim l As Long
    Dim m As Long
    Dim n As Long
    If j = 0 Then
       cvtWord = 0
       Exit Function
    End If

    i = j

    l = i \ 256
    m = i - l * 256

    n = m * 256 + l

    If n > 32767 Then
       cvtWord = n - 65536

    Else
       cvtWord = n

    End If
End Function
Sub writeOutInteger(f As Integer, q As Integer)
    'r=file@, q=value
    Dim i As Integer
    Dim l As Byte
    Dim m As Byte
    Dim sn As Integer
    i = Abs(q)
    l = i \ 256
    m = i - l * 256
    If Sgn(q) = -1 Then
       If m = 0 Then
          sn = 1
       Else
          m = &HFF - m
          sn = 0
       End If
       If l = 0 And sn = 1 Then
       Else
         l = &HFF - l + sn
       End If
    End If
    writeOutByte f, l
    writeOutByte f, m
    
End Sub
Sub outLong(f As Integer, l As Long)
   writeOutLong f, l
End Sub
Sub writeOutLong(f As Integer, q As Long)
    Dim i As Long
    Dim j As Byte
    Dim k As Byte
    Dim l As Byte
    Dim m As Byte
    Dim i2 As Long
    Dim i3 As Integer
    Dim sn As Integer
    i = Abs(q)
    i2 = i \ 256
    m = i - i2 * 256
    i3 = i2 \ 256
    l = i2 - i3 * 256
    j = i3 \ 256
    k = i3 - j * 256
    If Sgn(q) = -1 Then
       If m = 0 Then
          sn = 1
       Else
          m = &HFF - m
          sn = 0
       End If
       If l = 0 And sn = 1 Then
          sn = 1
       Else
          l = &HFF - l + sn
          sn = 0
       End If
       If k = 0 And sn = 1 Then
          sn = 1
       Else
          If k = 0 And sn = 1 Then
            sn = 1
          Else
            k = &HFF - k + sn
            sn = 0
          End If
       End If
       If j = 0 And sn = 1 Then
       Else
          j = &HFF - j + sn
       End If
    End If
    writeOutByte f, j
    writeOutByte f, k
    writeOutByte f, l
    writeOutByte f, m
End Sub
Sub openOutput()
Dim wk As String

   wk = DownloadPath + gTarget.Name + ".prc"
   If Not Dir(wk) = "" Then
      Kill wk
   End If
   Open wk For Binary As #3
   'wk = DownloadPath + model1.name + ".pdb"
   'If Not Dir(wk) = "" Then
   '   Kill wk
   'End If
   'Open wk For Binary As #4
  If gbBuildFat = False Then  '10.22.00 GH
    Open ProgramsDirectory & "\BuildTools\template.prc" For Binary As #5
  Else      '10.22.00 GH
    If gbIncludeArmNative = False Then
      If gbDebugMode = False Then
         Open ProgramsDirectory & "\BuildTools\NSBRuntime.prc" For Binary As #5 '10.22.00 GH
      Else
         Open ProgramsDirectory & "\BuildTools\NSBRuntimeDebug.prc" For Binary As #5 '10.22.00 GH
      End If
    Else
      Open ProgramsDirectory & "\BuildTools\NSBRuntimeArm68K.prc" For Binary As #5 '10.22.00 GH
    End If
  End If                    '10.22.00 GH
End Sub
Sub writeOutByte(f As Integer, b As Byte)
   Put f, , b
End Sub
Sub writeOutString(f As Integer, str1 As String)
  Dim i As Integer
  'Dim b As Byte
  Dim k1 As Byte
  Dim k2 As Byte

  'For i = 1 To Len(str1)  '01/16/00 old non-unicode
    'b = Asc(mid$(str1, i, 1))
    'If Asc(b) = 34 Then b = chr$(39) 'cvt double quotes to single
    'Put f, , b
  'Next

  For i = 1 To Len(str1)  '01/16/00 GH modified to output unicode
        'hicode
        If Asc(Mid$(str1, i, 1)) < 0 Then
            k1 = (Asc(Mid$(str1, i, 1)) + &H10000) \ &H100
        Else
            k1 = Asc(Mid$(str1, i, 1)) \ &H100
        End If
        'locode
        k2 = Asc(Mid$(str1, i, 1)) And &HFF
    
        If k1 > 0 Then
            If k1 = 34 Then k1 = 39 'cvt double quotes to single
            Put f, , k1
        End If
        If k2 > 0 Then
            Put f, , k2
        End If
  Next
  
  k1 = &H0
  Put f, , k1
End Sub
Function getWriteOutStringLen(str1 As String) As Integer '04/25/1 GH
  Dim i As Integer
  Dim k1 As Byte
  Dim k2 As Byte

  For i = 1 To Len(str1)
        'hicode
        If Asc(Mid$(str1, i, 1)) < 0 Then
            k1 = (Asc(Mid$(str1, i, 1)) + &H10000) \ &H100
        Else
            k1 = Asc(Mid$(str1, i, 1)) \ &H100
        End If
        'locode
        k2 = Asc(Mid$(str1, i, 1)) And &HFF
    
        If k1 > 0 Then
            getWriteOutStringLen = getWriteOutStringLen + 1
        End If
        If k2 > 0 Then
            getWriteOutStringLen = getWriteOutStringLen + 1
        End If
  Next
End Function

Sub writeOutCode(f As Integer, code As String, codeLen As Long)
   Dim i As Long
   Dim c As Byte
   For i = 1 To codeLen Step 2
    c = (Asc(Mid$(code, i, 1)) - 1) * 64 + Asc(Mid$(code, i + 1, 1)) - 1
    Put f, , c
   Next
End Sub

Sub OLD_writeOutCode(f As Integer, code As String, codeLen As Long)
   Dim i As Long
   Dim c As Byte
   Dim x As Integer
   x = codeLen

   For i = 1 To codeLen
     If Asc(Mid$(code, i, 1)) = &HFF Then
        i = i + 1
        If Asc(Mid$(code, i, 1)) = &H1 Then
           c = &H0
           Put f, , c
        Else
           c = &HFF
           Put f, , c
        End If
     Else
        Put f, , Mid$(code, i, 1)
     End If
  Next
End Sub

'MMD: This belongs inside CUIObject
Sub BuildControlPrc(but As ctlOut, obj As CUIObject)
   but.id.w = cvtWord(obj.IdNo)
   but.bounds.topleft.x = cvtWord(obj.OrigLeft)
   but.bounds.topleft.y = cvtWord(obj.OrigTop)
   but.bounds.extent.x = cvtWord(obj.Width)
   but.bounds.extent.y = cvtWord(obj.Height)
   but.Text.c = 0
   but.attr = &H1  'std frame
   If obj.Usable = True Then but.attr = but.attr Or &H80
   but.attr = but.attr Or &H40 'enabled = true
   but.attr = but.attr Or &H20 'visible = True
   
   but.style.s = 0
   but.font = obj.FontID
   but.group = 0
End Sub
Sub PalmDatesTwo(diffSecs As Integer, b1 As Byte, b2 As Byte, b3 As Byte, b4 As Byte, _
                                   c1 As Byte, c2 As Byte, c3 As Byte, c4 As Byte)
    Dim x As Date
    x = Now
    PalmDate x, 0, b1, b2, b3, b4
    PalmDate x, diffSecs, c1, c2, c3, c4
  
End Sub
Sub PalmDate(startDate As Date, diffSecs As Integer, b1 As Byte, b2 As Byte, b3 As Byte, b4 As Byte)
  Dim a As Date
  Dim b As Date
  Dim c As Date
  Dim x As Double
  
  Dim x1 As Double
  Dim xold As Double
  'adds diff seconds to today's date & time
  a = startDate
  b = "1/1/1904"
  
  
  x = DateDiff("s", b, a)
  x = x - 2147483648# + diffSecs
  
  
  x1 = 1073741824#
  xold = x
  
  b1 = 128 + 64 * chk(x, x1) + 32 * chk(x, x1 / 2) _
  + 16 * chk(x, x1 / 4) + 8 * chk(x, x1 / 8) _
  + 4 * chk(x, x1 / 16) + 2 * chk(x, x1 / 32) _
  + chk(x, x1 / 64)
  
  x1 = 4194304#
    
  b2 = 128 * chk(x, x1 * 2) + 64 * chk(x, x1) + 32 * chk(x, x1 / 2) _
  + 16 * chk(x, x1 / 4) + 8 * chk(x, x1 / 8) _
  + 4 * chk(x, x1 / 16) + 2 * chk(x, x1 / 32) _
  + chk(x, x1 / 64)
  
  x1 = 16384#
   
  b3 = 128 * chk(x, x1 * 2) + 64 * chk(x, x1) + 32 * chk(x, x1 / 2) _
  + 16 * chk(x, x1 / 4) + 8 * chk(x, x1 / 8) _
  + 4 * chk(x, x1 / 16) + 2 * chk(x, x1 / 32) _
  + chk(x, x1 / 64)
  
  x1 = 64#
  
  
  b4 = 128 * chk(x, x1 * 2) + 64 * chk(x, x1) + 32 * chk(x, x1 / 2) _
  + 16 * chk(x, x1 / 4) + 8 * chk(x, x1 / 8) _
  + 4 * chk(x, x1 / 16) + 2 * chk(x, x1 / 32) _
  + chk(x, x1 / 64)
  
  'sgBox "x=" + str$(xold) + "  xb=" + str$(b1) + " b2=" + str$(b2) + " b3=" + str$(b3) + " b4=" + str$(b4)
End Sub
Function chk(x As Double, y As Double) As Integer
  If x >= y Then
    x = x - y
    chk = 1
  Else
    chk = 0
  End If
End Function
Public Sub displayHelp(x As Form)
End Sub
Sub arith_exp_gen()
If compiler_debug Then
MsgBox "arith exp gen"
dbugDump
End If
   arith_scan_all
   Set se = first_se
End Sub
Sub dbugDump()
  Dim tempSe As CSynElem
  Set tempSe = se
 If compiler_debug Then
  Set se = first_se
  Do
    dbug "dump term=" + se.term + " maj=" + se.maj + " termin=" + se.termin + " type=" + str$(se.termType) + " deno=" + str$(se.de_no) + "  sub1=" + str$(se.sub1)
    Set se = se.Nxt
  Loop While (Not se Is se_null_ptr)
 End If
 Set se = tempSe
End Sub
Sub arith_scan_all() '/*scan entire syn elem list */
  If first_se Is se_null_ptr Then
    Exit Sub
  End If
restart_arith_scan:
    arith_stat = 1
                       '1= unary + or -
                       '2=exponen
                       '3=* or /
                       '4= + or -
'Set se = first_se
'Do While Not se Is se_null_ptr
'   MsgBox "se maj=" + se.maj + " sub1=" + str$(se.sub1) + " name=" + se.term
'
'   Set se = se.nxt
'Loop

arith_scan_again:
'dbug "rescan --arith_stat=" + str$(arith_stat)
    paren_cnt = 0
    Set se = first_se
    Do
        arith_scan_for_exp
    Loop While (Not se Is se_null_ptr)

    If (arith_stat = 99) Then GoTo restart_arith_scan
    If (arith_stat < 4) Then
       arith_stat = arith_stat + 1
       GoTo arith_scan_again
    End If

'dbug "after arith_scan"
If compiler_debug Then
MsgBox "after arith_scan_all"
dbugDump
End If
End Sub
Sub arith_scan_for_exp()  '/* scans from se to begin expression */
    Dim wkde As CDataElement   '*** added 10.10.2000
    Dim argcnt As Integer
    Dim temp As CSynElem
    Set temp = se_null_ptr
    Dim temp2 As CSynElem
    Dim temp3 As CSynElem
    Set temp2 = se_null_ptr
    Dim typ As New CTypeDef
    Dim t As New CTypeElem
    Dim wk As String
'If compiler_debug Then
'sgBox "arith scan se=" + se.maj + " deno=" + str$(se.de_no) + "  sub1=" + str$(se.sub1) + " arith_stat=" + str$(arith_stat)
'End If
    
    If ((se.maj = "p") And (se.sub1 = 0)) Then '/*left paren*/
      paren_cnt = paren_cnt + 1
      Set se = se.Nxt
      Exit Sub
    End If
    If ((se.maj = "p") And (se.sub1 = 1)) Then
      '/*rt paren*/
      If (paren_cnt = 0) Then
          print_err gStringTable(3120) '"Right parenthesis found without an open left parenthesis"
         Exit Sub
      End If
      paren_cnt = paren_cnt - 1
      '/* to remove parens */
      If (Not se.Prev Is se_null_ptr) Then
        Set temp = se.Prev
        If (temp.maj = "d") Then
          If (Not temp.Prev Is se_null_ptr) Then
            Set temp = temp.Prev
            If ((temp.maj = "p") And (temp.sub1 = 0) _
            And (Not LCase$(first_se.term) = "dim") _
            And (Not LCase$(first_se.term) = "global")) _
            Then  '/* ( */
              Set temp2 = temp.Prev
              If ((temp2 Is se_null_ptr) _
              Or ((Not temp2.maj = funcName) And (Not temp2.maj = "y") And (Not temp2.maj = "u"))) Then  '***3/13/2001 *** revised
                delete_syn_elem temp
                Set temp = se
                Set se = temp.Prev

                delete_syn_elem temp
                arith_stat = 99
                Set se = se_null_ptr
                Exit Sub
              ElseIf temp2.maj = "y" Then
                Set temp3 = se.Prev
                '*** additions 10.10.2000 starting here ******************
                If temp3.sub1 > 1 Then                                            '***added 10.10.2000******
                  'subscript is itself subscripted, so must assign it to work var '***added 10.10.2000******
                  gen_alloc_arith_work                                            '***added 10.10.2000******
                  arg_1 = arith_work_de_no                                        '***added 10.10.2000******
                  arg1_occ1 = 0                                                   '***added 10.10.2000******
                  arg1_occ2 = 0                                                   '***added 10.10.2000******
                  arg1_occ3 = 0                                                   '***added 10.10.2000******
                  out_one_char &H59                                               '***added 10.10.2000******
                  arg_2 = temp3.de_no                                             '***added 10.10.2000******
                  arg2_occ1 = temp3.sub1                                          '***added 10.10.2000******
                  arg2_occ2 = temp3.sub2                                          '***added 10.10.2000******
                  arg2_occ3 = temp3.sub3                                          '***added 10.10.2000******
                  out_the_2cnd_arg                                                '***added 10.10.2000******
                  out_the_1st_arg                                                 '***added 10.10.2000******
                  out_one_char &H0                                                '***added 10.10.2000******
                  temp3.de_no = arith_work_de_no                                  '***added 10.10.2000******
                  temp3.sub1 = 0                                                  '***added 10.10.2000******
                  temp3.sub2 = 0                                                  '***added 10.10.2000******
                  temp3.sub3 = 0                                                  '***added 10.10.2000******
                End If                                                            '***added 10.10.2000******
                '*** additions end here 10.10.2000 ******************************
                
                temp2.sub1 = temp3.de_no
                temp2.maj = "d"
                delete_syn_elem se
                Set se = temp3.Prev
                delete_syn_elem temp3
                delete_syn_elem se
                arith_stat = 99
                Set se = se_null_ptr
                Exit Sub
              End If
            ElseIf (Not LCase$(first_se.term) = "dim") And (Not LCase$(first_se.term) = "global") Then
              'chk for multiple subscripts
              Do
                 If (temp.maj = "d") And Not (temp.Prev Is se_null_ptr) Then
                     Set temp = temp.Prev
                 Else
                     Exit Do
                 End If
              Loop
              If ((temp.maj = "p") And (temp.sub1 = 0) _
              And (Not temp.Prev Is se_null_ptr) _
              And (Not LCase$(first_se.term) = "dim") _
              And (Not LCase$(first_se.term) = "global") _
              ) Then '/* ( */
                Set temp2 = temp.Prev
                If temp2.maj = "y" Then
                  Set temp3 = temp.Nxt
                  delete_syn_elem temp
                  temp2.sub1 = temp3.de_no
                  If (Not temp3.Nxt Is se_null_ptr) And (temp3.Nxt.maj = "d") Then
                    Set se = temp3
                    Set temp3 = temp3.Nxt
                    delete_syn_elem se
                    temp2.sub2 = temp3.de_no
                    If (Not temp3.Nxt Is se_null_ptr) And (temp3.Nxt.maj = "d") Then
                      Set se = temp3
                      Set temp3 = temp3.Nxt
                      delete_syn_elem se
                      temp2.sub3 = temp3.de_no
                    End If
                  End If
                
                  Set se = temp3.Nxt
                  temp2.maj = "d"
                  delete_syn_elem temp3 'last subscript
                  delete_syn_elem se  'rt paren
                  arith_stat = 99
                 
                  Set se = se_null_ptr
                  Exit Sub
                End If
              End If
            End If
          End If
        End If
      End If
      Set se = se.Nxt
      Exit Sub
    End If

    If (se.maj = "a") Then
      If ((se.sub1 = 1) Or (se.sub1 = 2)) Then
        If (Not se.Prev Is se_null_ptr) Then
          Set temp = se.Prev
          If (((temp.maj = "p") And (temp.sub1 = 0)) Or _
             temp.maj = "@" Or _
             temp.termType = 2 Or _
             temp.termin = "," Or _
             (temp.maj = "a") Or (temp.maj = "r")) Then
             If (Not se.Nxt Is se_null_ptr) Then
               Set temp = se.Nxt
               If (temp.maj = "d") Then
                 If (se.sub1 = 1) Then '/*unary +*/
                   delete_syn_elem se
                   Set se = temp
                   Exit Sub
                 Else          '/* unary - */
                   gen_unary_minus
                   Exit Sub
                 End If
               End If
             End If
          End If
        Else
           Set temp = se.Nxt
           If (Not temp Is se_null_ptr) Then
             If (temp.maj = "d") Then
               If (se.sub1 = 1) Then '/*unary +*/
                 delete_syn_elem se
                 Set se = temp
                 Exit Sub
               Else   '/* unary - */
                 gen_unary_minus
                 Exit Sub
               End If
             End If
           End If
        End If
      End If
    End If

arith_retry:
    If (se.maj = "u") Then 'user func
      argcnt = 0
      Set temp = se.Nxt
      If ((Not temp.maj = "p") Or (Not temp.sub1 = 0)) Then '/*left paren*/
        print_err gStringTable(3121) '"Left parenthesis missing after function name."
        Exit Sub
      End If
      Do While (1)
        argcnt = argcnt + 1
        Set temp = temp.Nxt
        If (temp Is se_null_ptr) Then
          print_err gStringTable(3122) '"Missing right parenthesis at end of function call"
          Exit Sub
        End If

        If ((temp.maj = "p") And (temp.sub1 = 1)) Then '/*rt paren*/
           Set p = loc_link_ptr(se.de_no)
           
           'gen code for user func
'sgBox "user func at offset=" + str$(proc_offset)
     out_one_char (&H13) 'tok for user func
           out_one_integ (p.tbl_no) 'func tbl no
           
           Set temp = se.Nxt
           delete_syn_elem temp 'left paren
           Set temp = se.Nxt
           Do While (1)
               If Not ((temp.maj = "p") And (temp.sub1 = 1)) Then 'rt paren
                 Set data = find_de_by_no(temp.de_no)
                 If (data Is Nothing) Then
'sgBox "dataelem =" + temp.term + "    is null"
                      SYNTAX 14
                 End If
'sgBox "user func arg=" + DATA.name
                 If data.typedefFlag = True Then
                      Set typ = locate_type_def(data.typedefName)
                      For Each t In typ.Elements
                          PutOutTypeDefArgs t, data, temp.sub1, temp.sub2, temp.sub3, argcnt  'added 805************************
                          'commented out 805 argcnt = argcnt + 1
                          'commented out 805 wk = right$(DATA.name, Len(DATA.name) - 2) + "." _
                          'commented out 805      + right$(t.name, Len(t.name) - Instr$(1, t.name, ".", 0))
                          'commented out 805 Set d2 = locateDataByName(wk)
                          'commented out 805 arg_2 = d2.tbl_no
                          'commented out 805 arg2_occ1 = temp.sub1 'use subscripts of DATA
                          'commented out 805 arg2_occ2 = temp.sub2
                          'commented out 805 arg2_occ3 = temp.sub3
                          'commented out 805 out_the_2cnd_arg
                      Next
                 Else
                    If temp.maj = "*" Then SYNTAX 15
                    arg_2 = temp.de_no
                    arg2_occ1 = temp.sub1
                    arg2_occ2 = temp.sub2
                    arg2_occ3 = temp.sub3
                 
                    out_the_2cnd_arg
                    argcnt = argcnt + 1
                 End If
                 delete_syn_elem temp
                 Set temp = se.Nxt
               Else
                 delete_syn_elem temp 'deletes the rt paren
                 out_one_integ (0) 'mark end of args
                 se.term = ""
                 se.maj = "d"
                 se.termType = 4
                 se.de_no = p.func_de_no
                 'Set se = se.nxt  ***commented out 10.10.2000  ***************
                 out_one_integ p.func_de_no 'to store result in(??may not be used??)
                 
                 '*****additions 10.10.2000 start here ************************
                 'may use same function twice in same statement, so must move value to work var '***added 10.10.2000 ***
                 arg_1 = se.de_no                                                               '***added 10.10.2000 ***
                 arg2_occ1 = 0                                                                  '***added 10.10.2000 ***
                 arg2_occ2 = 0                                                                  '***added 10.10.2000 ***
                 arg2_occ3 = 0                                                                  '***added 10.10.2000 ***
                 Set wkde = find_de_by_no(p.func_de_no)                                         '***added 10.10.2000 ***
                 If wkde.Kind = "s" Then                                                        '***added 10.10.2000 ***
                   gen_alloc_string_work                                                        '***added 10.10.2000 ***
                   arg_2 = string_work_de_no                                                    '***added 10.10.2000 ***
                   se.de_no = string_work_de_no                                                 '***added 10.10.2000 ***
                 Else                                                                           '***added 10.10.2000 ***
                   gen_alloc_arith_work                                                         '***added 10.10.2000 ***
                   arg_2 = arith_work_de_no                                                     '***added 10.10.2000 ***
                   se.de_no = arith_work_de_no                                                  '***added 10.10.2000 ***
                 End If                                                                         '***added 10.10.2000 ***
                 arg2_occ1 = 0                                                                  '***added 10.10.2000 ***
                 arg2_occ2 = 0                                                                  '***added 10.10.2000 ***
                 arg2_occ3 = 0                                                                  '***added 10.10.2000 ***
                 out_one_char &H59                                                              '***added 10.10.2000 ***
                 out_the_1st_arg                                                                '***added 10.10.2000 ***
                 out_the_2cnd_arg                                                               '***added 10.10.2000 ***
                 out_one_char &H0                                                               '***added 10.10.2000 ***
                                                                                                '***added 10.10.2000 ***
                 Set se = se.Nxt                                                                '***added 10.10.2000 ***
                 '****additions 10.10.2000 end here ***************************
                 
                 Exit Sub
               End If
           Loop
           If Not argcnt = p.argCount Then
              If p.argCount = -1 Then
                 p.argCount = argcnt  'hasn't been defined yet so use cur cnt
              Else
                print_err gStringTable(3123) + p.name_ptr _
                    + gStringTable(3124) + str$(p.argCount) + gStringTable(3125) + str$(argcnt) '"Wrong number of arguments supplied for user function "
              End If
           End If
        End If
        If (Not temp.maj = "*") And (Not temp.maj = "d") And (Not temp.maj = "y") And (Not temp.maj = "&") Then 'some inner expres
           Set se = se.Nxt
           Exit Sub
        End If
      Loop 'never falls thru
      
    End If
    If (se.maj = "d") Then      '/* variable */
      Set temp = se.Nxt
      If (temp Is se_null_ptr) Then
        Set se = se.Nxt
        Exit Sub
      End If
      If (temp.maj = "a") Then '/*arith oper */
        If (((temp.sub1 = 1) And (arith_stat = 4)) _
        Or ((temp.sub1 = 2) And (arith_stat = 4)) _
        Or ((temp.sub1 = 3) And (arith_stat = 3)) _
        Or ((temp.sub1 = 4) And (arith_stat = 3)) _
        Or ((temp.sub1 = 5) And (arith_stat = 2))) Then
take_out_3_terms:
          Set arith_se = temp
          Set temp = temp.Nxt
          If (temp Is se_null_ptr) Then
            Set se = se.Nxt
            Exit Sub
          End If
          If (temp.maj = "d") Then
            If (Not temp.Nxt Is se_null_ptr) Then
              Set temp = temp.Nxt
              If ((arith_se.sub1 = 1) _
              Or (arith_se.sub1 = 2)) Then '/*only add/minus*/
                If (((temp.maj = "a") And (temp.sub1 = 1)) _
                Or ((temp.maj = "a") And (temp.sub1 = 2)) _
                Or (temp.maj = "r") Or (temp.maj = "l") _
                Or (temp.maj = "*") _
                Or (temp.maj = "@") _
                Or (temp.maj = "d") _
                Or ((temp.maj = "p") And (temp.sub1 = 1))) Then
                Else
                  Set se = se.Nxt
                  Exit Sub
                End If
              End If
              'start of additions 12182002 ******************
              If (arith_se.sub1 = 3) _
              Or (arith_se.sub1 = 4) Then    'on mult or divide
                  If (temp.maj = "a") And (temp.sub1 = 5) Then
                     'cant do mult/divide because next oper is expon
                     Set se = se.Nxt
                     Exit Sub
                  End If
              End If
              'end of additions 12182002 ****************
              
            End If
            If (Not se.Prev Is se_null_ptr) Then
              If ((arith_se.sub1 = 1) _
              Or (arith_se.sub1 = 2)) Then '/*only add/minus*/
                Set temp = se.Prev
                If (((temp.maj = "a") And (temp.sub1 = 1)) _
                Or ((temp.maj = "a") And (temp.sub1 = 2)) _
                Or temp.maj = "@" _
                Or temp.maj = "z" _
                Or temp.maj = "d" Or temp.maj = "y" Or temp.maj = "&" _
                Or (temp.maj = "r") Or (temp.maj = "l") _
                Or ((temp.maj = "p") And (temp.sub1 = 0))) Then
               Else
                  Set se = se.Nxt
                  Exit Sub
                End If
              '****start inserts 9/22/2001 ************************
              Else
                If arith_se.sub1 = 3 Then   'if multiply
                   Set temp = se.Prev
                   If temp.maj = "a" And temp.sub1 = 4 Then 'prev was divide (probably preceded by rt paren)
                      Set se = se.Nxt
                      Exit Sub
                   End If
                End If
              '****end of inserts 9/22/2001 ************************

              End If
            End If
            
            gen_three_term_arith
If compiler_debug Then
dbug ("three term")
dbugDump
End If

             arith_stat = 99
            Set se = se_null_ptr
            Exit Sub
            'GoTo arith_retry
          Else
            Set se = se.Nxt
            Exit Sub
          End If
        End If
      End If
    End If

    If (se.maj = funcName) Then
'sgBox "at funcname"
'If compiler_debug Then
'sgBox "found funcname" + se.term
'End If
      Set temp = se.Nxt
      If ((Not temp.maj = "p") Or (Not temp.sub1 = 0)) Then '/*left paren*/
'If compiler_debug Then
'sgBox "no left paren"
'End If
        print_err gStringTable(3125) '"missing left parenthesis after function name"
        Exit Sub
      End If
      Do While (1)
        Set temp = temp.Nxt
        If (temp Is se_null_ptr) Then
          print_err gStringTable(3126) '"Missing right parenthesis at end of function call"
          Exit Sub
        End If
        'If Not (temp.maj = "P" And temp.sub1 = 1) And Not temp.maj = "d" And Not temp.maj = "y" Then
        '   ???
        'End If
'If compiler_debug Then
'sgBox "temp-maj=" + temp.maj + " deno=" + str$(temp.de_no) + "  sub1=" + str$(temp.sub1)
'End If
       If ((temp.maj = "p") And (temp.sub1 = 1)) Then '/*rt paren*/
'sgBox "selecting func =" + str$(se.sub1)
          Select Case (se.sub1)
            Case 75               'added 06102002
              func_controlsCount  'added 06102002
            Case 42                           'added 08222002
              func_getGeneralPropertyNumeric  'added 08222002
            Case 43                           'added 08222002
              func_getGeneralPropertyString   'added 08222002
            Case 400
              func_controlgetstatus
            Case 401
              func_fieldgettext
            Case 402
              func_listgetnoitems
            Case 403
              func_listgetselecteditemno
            Case 404
              func_listgetitemtext
            Case 405
              func_tablegetitemtext
            Case 406
              func_tablegetselectedrow
            Case 407
              func_getselectedcol
            Case 408
              func_getnorows
            Case 409
              func_controlgetid
              
            Case 412
              func_popupgetnoitems
            Case 413
              func_popupgetselecteditemno
            Case 414
              func_popupgetitemtext
            Case 415
              func_scrollbargetcurrent
            Case 416
              func_popupgettext
            Case 417
              func_controlgettext
            Case 418                  'added 5/8/2001
              func_gadEndCapture      'added 5/8/2001
            Case 598                '12/06/2000 MD
               func_sysTrapFunc     '12/06/2000 MD
            Case 599                '11/30/2000 MD
               func_externalFunc    '11/30/2000 MD
              
            Case 200 'alertbox
              func_alert
            Case 300
              func_dbfind
            Case 301
              func_dbread
            Case 302
              func_dbupdate
            Case 303
              func_dbdelete
            Case 304
              func_dbinsert
            Case 305
              func_dbreadnext
            Case 306
              func_dberase
            Case 307
'sgBox "found 307"
               func_dbcreate
            Case 308
'sgBox "found 308"
               func_dbopen
            Case 309
              func_dbclose
            Case 310
              func_dbget
            Case 311
              func_dbput
            Case 312
              func_dbposition
            Case 313
              func_dbreset
            Case 314
              func_dbgetnorecs
            Case 315
              func_dbreadprev
            Case 1, 2, 6, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41, _
                 44, 45, 47, 54, 55, 70, 71, 73, 87, 108, _
                 129, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, _
                 500, 501, 502, 504, 505, 506, 508, 509, 510, _
                 511, 512, 513, 514, 515, 516, 517, 520
              func_1arg "n", "n"

          '06102002 Case 21, 46, 60, 61, 62, 63, 64, 159
          Case 21, 46, 60, 61, 62, 63, 64, 159   'changed 08222002
               func_1arg "s", "n"
          Case 156, 157
               func_1arg "s", "s"
          Case 3, 5, 7, 48, 51, 52, 53, 58, 59, 65, 66, 67, 100, 503, 518, 519 '06102002 revised
          
               func_2arg "n", "n", "n"
          'commment out 813 Case 4, 56, 57, 58, 59, 83, 86, 101, 106, 160
          '06102002 revised Case 4, 56, 57, 58,59, 83, 86, 101, 106, 160  'added 813    '*** modified 4/30/2001 *********************
                  Case 4, 56, 57, 83, 86, 101, 106, 107, 160   'revised 06102002
               func_0arg "n"
'sgBox "after return from func_0arg    se.maj=" + se.maj
             
          Case 84                                                 '*** modified 5/8/2001 *********************
               func_0arg "s"
          Case 8
              func_1arg "s", "n"
          '06102002 Case 14, 17, 24, 25, 26, 28, 71, 141
          Case 14, 17, 24, 25, 26, 28, 71, 74, 141  'changed 06102002
              func_1arg "n", "s"

          '06102002 Case 18, 22, 23, 70, 72, 80, 81, 82
          Case 18, 22, 23, 70, 80, 81, 82, 89    'EMP added GetVersion
              func_1arg "s", "s"
          Case 12
              func_2arg "n", "a", "n"
          
          Case 15, 16, 49, 50
              func_2arg "s", "s", "n"
          Case 9, 10, 162
              func_2arg "s", "n", "s"
          Case 68
              func_2arg "n", "n", "s"
          Case 88, 103, 104
              func_2arg "n", "s", "n"
          Case 105
              func_2arg "n", "s", "s"
          Case 69
              func_3arg "n", "n", "n", "s"
              
          Case 102
              func_3arg "n", "s", "n", "n"
              
          Case 40, 161
              func_1arg "n", "a"
          Case 19
              func_3arg "s", "s", "n", "n"
          Case 27, 29
              func_3arg "n", "n", "n", "n"
          Case 11
              func_4arg "n", "n", "s", "s", "n"
          Case 20
              func_4arg "n", "s", "s", "n", "n"
         Case 650 'applaunch                                         '01/29/2001 MMD
            'val = AppLaunch(cardNo, pgmName, launchCmd, data)       '01/29/2001 MMD
            'val = AppLaunch(0, "PalmPrint", 32768, "Hello, World!") '01/29/2001 MMD
            func_4arg "n", "n", "s", "n", "a"                        '01/29/2001 MMD
          Case Else
            term_err_stop gStringTable(3229) + str$(se.sub1) '"Internal compiler error--found function code " +
          End Select
         
          arith_stat = 99
          Set se = se_null_ptr
          Exit Sub
        End If
        If (Not temp.maj = "d") And (Not temp.maj = "y") _
        And (Not temp.maj = "&") Then
'If compiler_debug Then
'sgBox "exiting do at se="+se.maj
'End If
            Exit Do
        End If
      Loop
    End If
    Set se = se.Nxt
End Sub
'inserted entire routine 08222002
Sub func_getGeneralPropertyString()     'entire routine added 08222002
  Dim byt As Byte
'compiler_debug = True
'dbugDump
'MsgBox "se.term=" + se.term
  Dim a As CSynElem
  Dim b As CSynElem
  Dim c As CSynElem
  Dim d As CSynElem
  Dim e As CSynElem
  Dim f As CSynElem
  
  Dim hadParen As Boolean
  
  hadParen = False
  
  Set a = se
  Set b = a.Nxt
  
  out_one_char (&H8B)
  set_result_string
  
  If b.maj = "p" And b.sub1 = 0 Then
     delete_syn_elem b
     Set b = a.Nxt
     hadParen = True
  End If
  term = b.term    '1st param is how ctl is identified
                                ' 'i'=by its id
                                ' 'v'=name in a var
                                ' 'p' by its positon on the form
  byt = Asc(Left$(term, 1))
  out_one_char byt
  Set c = b.Nxt
  Select Case term
    Case "i"
      out_one_integ (Val(c.term))  'id#
    Case "v"
      arg_2 = c.de_no    'varname containg ctl name
      arg2_occ1 = c.sub1
      arg2_occ2 = c.sub2
      arg2_occ3 = c.sub3
      out_the_2cnd_arg
    Case "p"
      arg_2 = c.de_no     'var containing index # of ctl on form
      arg2_occ1 = c.sub1
      arg2_occ2 = c.sub2
      arg2_occ3 = c.sub3
      out_the_2cnd_arg
  End Select
  
      Set d = c.Nxt          'number of property
      out_one_integ (Val(d.term))
      
  Select Case Val(d.term)
    Case 0  'text
       'no additional params
    Case 11  'itemtext
       '09092002 if d.nxt Is se_null_ptr Then SYNTAX
       '09092002 Set e = d.nxt
       '09092002 If e.maj <> "p" Or e.sub1 <> 0 Then SYNTAX
       '09092002 delete_syn_elem e
       If d.Nxt Is se_null_ptr Then
         SYNTAX 16
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing index # of element in list
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
       
       '09092002 If d.nxt Is se_null_ptr Then SYNTAX
       '09092002 Set e = d.nxt
       '09092002 If e.maj <> "p" Or e.sub1 <> 1 Then SYNTAX
       '09092002 delete_syn_elem e
     Case 12  'signatureEndCapture (signature)
       'no additional parameters
       
     'additions 09242003
     Case 50
'MsgBox "in getGeneralProperty String"
       If d.Nxt Is se_null_ptr Then
         SYNTAX 17
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing col # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
     Case 54, 55, 59  'textmatrix,valuematrix,fontmatrix   'modified 04012005
'MsgBox "54 function"
'dbugDump
       If d.Nxt Is se_null_ptr Then
         SYNTAX 18
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing row # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
       
       If d.Nxt Is se_null_ptr Then
         SYNTAX 19
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing col # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
     Case 57
        If d.Nxt Is se_null_ptr Then
         SYNTAX 20
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing row # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
     'end of additions 09242003
    End Select
    If hadParen Then
       If d.Nxt Is se_null_ptr Then SYNTAX 21
       If d.Nxt.maj <> "p" Or d.Nxt.sub1 <> 1 Then SYNTAX 22
       delete_syn_elem d.Nxt
       
    End If
    delete_syn_elem b
    delete_syn_elem c
    delete_syn_elem d
End Sub

'inserted entire routine 08222002
Sub func_getGeneralPropertyNumeric()     'entire routine added 08222002
  Dim byt As Byte
'compiler_debug = True
'dbugDump
'MsgBox "se.term=" + se.term
  Dim a As CSynElem
  Dim b As CSynElem
  Dim c As CSynElem
  Dim d As CSynElem
  Dim e As CSynElem
  Dim f As CSynElem
  Dim hadParen As Boolean
  
  hadParen = False
  
  Set a = se
  Set b = a.Nxt
  
  out_one_char (&H8A)
  db_set_result
  
  If b.maj = "p" And b.sub1 = 0 Then
     delete_syn_elem b
     Set b = a.Nxt
     hadParen = True
  End If
  term = b.term    '1st param is how ctl is identified
                                ' 'i'=by its id
                                ' 'v'=name in a var
                                ' 'p' by its positon on the form
  byt = Asc(Left$(term, 1))
  out_one_char byt
  Set c = b.Nxt
  Select Case term
    Case "i"
      out_one_integ (Val(c.term))  'id#
    Case "v"
      arg_2 = c.de_no    'varname containg ctl name
      arg2_occ1 = c.sub1
      arg2_occ2 = c.sub2
      arg2_occ3 = c.sub3
      out_the_2cnd_arg
    Case "p"
      arg_2 = c.de_no     'var containing index # of ctl on form
      arg2_occ1 = c.sub1
      arg2_occ2 = c.sub2
      arg2_occ3 = c.sub3
      out_the_2cnd_arg
  End Select
  
      Set d = c.Nxt          'number of property
      out_one_integ (Val(d.term))
      
      Select Case Val(d.term)
    Case 1  'status
       'no additional params
    Case 2  'selected
        'no additional params
    Case 5  'current
        'no additional params
    Case 9 'noitems
        'no additional params
    Case 13 'type
        'no additional params
    Case 14  'index(position)
        'no additional params
    Case 15  'id(position)        'added 09302002
        'no additional params      'added 09302002
        
     'start additions 09242003
     Case 50  'colwidth (grid)
'MsgBox "in getGeneralProp Num"
       If d.Nxt Is se_null_ptr Then
         SYNTAX 23
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing row # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
     Case 55  'valuematrix (grid)
'MsgBox "55 function "
'dbugDump
       If d.Nxt Is se_null_ptr Then
         SYNTAX 24
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing row # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
       
       If d.Nxt Is se_null_ptr Then
         SYNTAX 25
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing col # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
     Case 57  'valuematrix (grid)
        If d.Nxt Is se_null_ptr Then
         SYNTAX 26
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing row # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
       
        
     'end additions 09242003    End Select
     'start additions 04012005
     Case 59  'fontmatrix (grid)
 
'dbugDump
       If d.Nxt Is se_null_ptr Then
         SYNTAX
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing row # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
       
       If d.Nxt Is se_null_ptr Then
         SYNTAX
       Else
          Set e = d.Nxt
       End If
       
       arg_2 = e.de_no     'var containing col # of cell
       arg2_occ1 = e.sub1
       arg2_occ2 = e.sub2
       arg2_occ3 = e.sub3
       out_the_2cnd_arg
       delete_syn_elem e
     'end additions 04012005
    End Select
    If hadParen Then
       If d.Nxt Is se_null_ptr Then SYNTAX 27
       If d.Nxt.maj <> "p" Or d.Nxt.sub1 <> 1 Then SYNTAX 28
       delete_syn_elem d.Nxt
       
    End If
    delete_syn_elem b
    delete_syn_elem c
    delete_syn_elem d
    
End Sub

'06102002  added entire routine
Sub func_controlsCount()

   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem

    Dim view2 As CForm
    Set view2 = aView_null_ptr
    Dim work As String
    Dim argum1 As CDataElement
    Dim argum2 As CDataElement

   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'form name
   Set z = c.Nxt  'right paren
   'get_term   'to skip func name
'MsgBox "a.term=" + a.term + "  b.term=" + b.term

'compiler_debug = True
'dbugDump
 
   If b.maj <> "p" Or b.sub1 <> 0 Then SYNTAX 29
   If z.maj <> "p" Or z.sub1 <> 1 Then SYNTAX 30
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        print_err gStringTable(3364) '"Screen name must be in quotes.")
        Exit Sub
    End If

   If Not Mid$(valu1.Name, 1, 1) = "." Then '/*if alpha literal*/
          print_err gStringTable(3364) '"Must use the name of a screen in quotes"
   Else
      work = valu1.single_value
      For Each view2 In gTarget.FormCollection
        If (LCase$(view2.Name) = LCase$(work)) Then
            gen_alloc_arith_work
            arg_1 = arith_work_de_no
            arg1_occ1 = 0
            arg1_occ2 = 0
            arg1_occ3 = 0
            
            out_one_char (func_token)
            out_one_integ (se.sub1)
            out_one_integ (0) '/*no args*/
            
            out_the_1st_arg
            out_one_integ (view2.IdNo)
            delete_syn_elem a
            delete_syn_elem b
            delete_syn_elem c
            'Set z = se
'MsgBox "z.term=" + z.term
            z.de_no = arg_1
            z.maj = "d"
            z.term = ""
            z.termType = 4
            z.sub1 = 0
            z.sub2 = 0
            z.sub3 = 0
            
            Set se = z
           Exit Sub
        End If
      Next
      print_err ("References an unknown screen name." + data.single_value)
   End If         '06102002
End Sub
'06102002 end of additions
Sub func_tableCommon()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim d As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   
   a = se   'func name
   b = se.Nxt 'left paren
   c = b.Nxt  'table id
   d = c.Nxt 'row
   z = d.Nxt 'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        print_err gStringTable(3127) '"Invalid table object name"
        Exit Sub
    End If
   
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
    arg_2 = d.de_no 'row
    arg2_occ1 = d.sub1
    arg2_occ2 = d.sub2
    arg2_occ3 = d.sub3
   out_one_char (func_token)
   out_one_integ (se.sub1)
   out_one_integ (0) '/*no args*/
   out_the_2cnd_arg
   out_the_1st_arg
   
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 31
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 32
   End If
   func_findctlname c
   out_one_integ (controlId)
    
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    delete_syn_elem d
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
   
End Sub

Sub func_findctlname(a As CSynElem)
   Dim view2 As CForm
   Dim d As CDataElement
   Set d = find_de_by_no(a.de_no)
  
  For Each view2 In gTarget.FormCollection
    For Each o In view2.ObjectCollection
      If LCase$(o.obj.Name) = LCase$(d.single_value) Then
         controlId = o.obj.IdNo
         Set controlObj = o
         Exit Sub
       End If
     Next
   Next
   print_err gStringTable(3128) + d.single_value '"Can't locate a control that matches name="
End Sub
Sub func_scrollbargetcurrent()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        print_err gStringTable(3129) '"Invalid object name"
        Exit Sub
    End If
   
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0

    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
   
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 33
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 34
   End If
   func_findctlname c
   out_one_integ (controlId)
    
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_controlgetstatus()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0

    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
   
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 35
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 36
   End If
   func_findctlname c
   out_one_integ (controlId)
    
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.term = ""
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_controlgetid()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0

    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
   
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 37
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 38
   End If
   func_findctlname c
   out_one_integ (controlId)
    
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.term = ""
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_controlgettext()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_string_work
   arg_1 = string_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0

    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
   
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 39
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 40
   End If
   func_findctlname c
   out_one_integ (controlId)
    
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.term = ""
    z.termType = 4
    z.maj = "d"
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_fieldgettext()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_string_work
   arg_1 = string_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
   
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
     func_findctlname c
     out_one_integ (controlId)

   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 41
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 42
   End If
   
   
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    z.term = "" '1121
    
  
    Set se = z
End Sub
Sub func_listgetnoitems()
  listOrPopup = "l"
  GetNoItemsCommon
End Sub
Sub func_popupgetnoitems()
  listOrPopup = "p"
  GetNoItemsCommon
End Sub
Sub GetNoItemsCommon()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
     func_findctlname c
     If listOrPopup = "l" Then
        out_one_integ (controlId)
     Else
       out_one_integ (controlId + 1)
     End If
   If b.maj = "p" And b.sub1 = 0 Then
   Else
       Set se = b
       SYNTAX 43
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
         Set se = z
         SYNTAX 44
   End If
   
   
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_listgetselecteditemno()
  listOrPopup = "l"
  getSelectedItemNoCommon
End Sub
Sub func_popupgetselecteditemno()
  listOrPopup = "p"
  getSelectedItemNoCommon
End Sub
Sub getSelectedItemNoCommon()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
   
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
     func_findctlname c
     If listOrPopup = "l" Then
       out_one_integ (controlId)
     Else
       out_one_integ (controlId + 1)
     End If
   If b.maj = "p" And b.sub1 = 0 Then
   Else
       Set se = b
       SYNTAX 45
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
       Set se = z
       SYNTAX 46
   End If
   
   
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    'z.rel = " "
    'z.relno = 0
    Set se = z
End Sub
Sub func_listgetitemtext()
   listOrPopup = "l"
   getItemTextCommon
End Sub
Sub func_popupgetitemtext()
   listOrPopup = "p"
   getItemTextCommon
End Sub
Sub getItemTextCommon()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim d As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem

   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set d = c.Nxt 'item no to get
   Set z = d.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
      Set se = c
      arith_syntax_err
      Exit Sub
   End If
   gen_alloc_string_work
   arg_1 = string_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
   arg_2 = d.de_no 'msg
   arg2_occ1 = d.sub1
   arg2_occ2 = d.sub2
   arg2_occ3 = d.sub3

   out_one_char (func_token)
   out_one_integ (se.sub1)
   out_one_integ (1) '/*no args*/
   out_the_2cnd_arg
   out_the_1st_arg
   func_findctlname c
   If listOrPopup = "l" Then
      out_one_integ (controlId)
   Else
      out_one_integ (controlId + 1)
   End If
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 47
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
      Set se = z
      SYNTAX 49
   End If

   delete_syn_elem a
   delete_syn_elem b
   delete_syn_elem c
   delete_syn_elem d
   z.de_no = arg_1
   z.maj = "d"
   z.termType = 4
   z.sub1 = 0
   z.sub2 = 0
   z.sub3 = 0
   Set se = z
End Sub
Sub func_popupgettext()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim d As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_string_work
   arg_1 = string_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
       
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
    func_findctlname c
     
    out_one_integ (controlId)
     
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 50
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
         Set se = z
         SYNTAX 51
   End If

   
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_tablegetitemtext()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim d As CSynElem
   Dim e As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set d = c.Nxt 'row #
   Set e = d.Nxt 'col #
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   
   
   gen_alloc_string_work
   arg_1 = string_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
    arg_2 = d.de_no 'msg
    arg2_occ1 = d.sub1
    arg2_occ2 = d.sub2
    arg2_occ3 = d.sub3
    
    arg_3 = e.de_no 'msg
    arg3_occ1 = e.sub1
    arg3_occ2 = e.sub2
    arg3_occ3 = e.sub3
    
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (2) '/*no args*/
    out_the_2cnd_arg
    out_the_3rd_arg
    out_the_1st_arg
     func_findctlname c
     out_one_integ (controlId)
   
   If b.maj = "p" And b.sub1 = 0 Then
   Else
       Set se = b
       SYNTAX 52
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 53
   End If
   
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    delete_syn_elem d
    delete_syn_elem e
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_tablegetselectedrow()
Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
     func_findctlname c
     out_one_integ (controlId)
   
   If b.maj = "p" And b.sub1 = 0 Then
   Else
        Set se = b
        SYNTAX 54
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 55
   End If
   
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_getselectedcol()
Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
     func_findctlname c
     out_one_integ (controlId)

   If b.maj = "p" And b.sub1 = 0 Then
   Else
       Set se = b
       SYNTAX 56
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
         Set se = z
         SYNTAX 57
   End If
   
   
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Sub func_getnorows()
Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
   out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
     func_findctlname c
     out_one_integ (controlId)
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 58
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
      Set se = z
      SYNTAX 59
   End If
   
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.maj = "d"
    z.termType = 4
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
                
Sub func_alert()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim d As CSynElem
   Dim e As CSynElem
   Dim f As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Dim temp2 As CSynElem
   Set a = se     'alert verb
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'title
   Set d = c.Nxt  'msg
   Set e = d.Nxt  'type
   Set f = e.Nxt 'button1
  
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   Set valu1 = find_de_by_no(d.de_no)
   If Not d.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = d
        arith_syntax_err
        Exit Sub
    End If
   Set valu1 = find_de_by_no(e.de_no)
   If Not e.maj = "d" Then      'Or Not valu1.kind = "s" Then
        Set se = e
        arith_syntax_err
        Exit Sub
    End If
    Set valu1 = find_de_by_no(f.de_no)
   If Not f.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = f
        arith_syntax_err
        Exit Sub
    End If
    
    gen_alloc_arith_work
   arg_1 = arith_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
    out_tok_1arg (&HC1) 'token
    arg_2 = c.de_no 'tit
    arg2_occ1 = c.sub1
    arg2_occ2 = c.sub2
    arg2_occ3 = c.sub3
    
    out_the_2cnd_arg
    arg_2 = d.de_no 'msg
    arg2_occ1 = d.sub1
    arg2_occ2 = d.sub2
    arg2_occ3 = d.sub3
    
    out_the_2cnd_arg
     arg_2 = e.de_no 'type
    arg2_occ1 = e.sub1
    arg2_occ2 = e.sub2
    arg2_occ3 = e.sub3
    
    out_the_2cnd_arg
     arg_2 = f.de_no 'but1
    arg2_occ1 = f.sub1
    arg2_occ2 = f.sub2
    arg2_occ3 = f.sub3
    
    
    out_the_2cnd_arg
    Set temp = f.Nxt
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    delete_syn_elem d
    delete_syn_elem e
    delete_syn_elem f
    Do
      If temp.maj = "p" And temp.sub1 = 1 Then
         Exit Do
      End If
      If Not temp.maj = "d" Then
         Set se = temp
         arith_syntax_err
      End If
      Set valu1 = find_de_by_no(temp.de_no)
      If Not temp.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = temp
        arith_syntax_err
        Exit Sub
      End If
      arg_2 = temp.de_no 'button
      arg2_occ1 = temp.sub1
      arg2_occ2 = temp.sub2
      arg2_occ3 = temp.sub3
      
      
      out_the_2cnd_arg
      Set temp2 = temp
      Set temp = temp.Nxt
      delete_syn_elem temp2
    Loop
    out_one_integ (0)
    temp.de_no = arg_1
    temp.maj = "d"
    temp.termType = 4
    temp.sub1 = 0
    temp.sub2 = 0
    temp.sub3 = 0
    
    Set se = temp
End Sub
 Sub func_dbfind()
   out_one_char (&H23)
   db_set_result
   find_dbname
   find_dbkey
   dbelim_paren
 End Sub
Sub func_dbread()
   out_one_char (&H24)
   db_set_result
   find_dbname
   find_dbkey
   find_dbvars
   dbelim_paren
End Sub
Sub func_dbupdate()
   out_one_char (&H25)
   db_set_result
   find_dbname
   find_dbkey
   find_dbvars
   dbelim_paren
End Sub
Sub func_dbdelete()
   out_one_char (&H26)
   db_set_result
   find_dbname
   find_dbkey
   dbelim_paren
   
End Sub
Sub func_dbinsert()
   out_one_char (&H27)
   db_set_result
   find_dbname
   find_dbkey
   find_dbvars
   dbelim_paren
End Sub
Sub func_dbreadnext()
   out_one_char (&H28)
   db_set_result
   find_dbname
   find_dbkey
   find_dbvars
   dbelim_paren
End Sub
Sub func_dbreadprev()
   out_one_char (&H49)
   db_set_result
   find_dbname
   find_dbkey
   find_dbvars
   dbelim_paren
End Sub
Sub func_dberase()
   out_one_char (&H29)
   db_set_result
   find_dbname
   dbelim_paren
End Sub
Sub func_dbcreate()
   out_one_char (&H2A)

   db_set_result

   find_dbname

   find_dbliteral

   find_dbcardno
   find_dbcreator
   
   dbelim_paren
End Sub
Sub func_dbopen()
'sgBox "at dbopen"
   Dim d As CDataElement
   out_one_char (&H2B)
   db_set_result
   find_dbname
   If se.termType = 5 Then
    Set d = find_de_by_no(se.de_no)
    If LCase$(d.single_value) = LCase$(projNameOnly(ProjectName)) Then
         print_err gStringTable(3130) '"Database name cannot be the same as the project name."
    End If
   End If
   find_dbliteral
   find_dbcardno
   dbelim_paren
End Sub

Function projNameOnly(projname As String) As String
   Dim i As Integer
   For i = Len(projname) To 1 Step -1
     If Mid$(projname, i, 1) = "\" Then
        projNameOnly = Mid$(projname, i + 1, Len(projname) - i - 4)
        Exit Function
     End If
   Next
End Function
Sub func_dbreset()
   
    
   out_one_char (&HDC)
   db_set_result
   find_dbname
   
   dbelim_paren
End Sub
Sub func_dbclose()
   out_one_char (&H2C)
   db_set_result
   find_dbname
   dbelim_paren
End Sub
Sub func_dbget()
   '1/9/2001 out_one_char (&H2D)
   out_one_char (&H87)  '1/9/2001 to use new put in runtime
   db_set_result
   find_dbname
   '1/9/2001 find_dbsinglevar
   find_dbvars    'added 1/9/2001
   dbelim_paren
End Sub

Sub func_dbgetnorecs()
   out_one_char (&H1F)
   db_set_result
   find_dbname
   dbelim_paren
   End Sub
Sub func_dbput()
   '1/9/2001out_one_char (&H2E)
   out_one_char (&H86)  'added 1/9/2001  to use new put in runtime
   db_set_result
   find_dbname
   '1/9/2001find_dbsinglevar
   find_dbvars   'added 1/9/2001
   dbelim_paren
End Sub

Sub func_dbposition()
   out_one_char (&H2F)
   db_set_result
   find_dbname
   find_dbwhere
   find_dboffset
   dbelim_paren
End Sub
Sub dbelim_paren()
  Dim temp As CSynElem
  If Not se.maj = "p" Then
     SYNTAX 60
  End If
  Set temp = se
  Set se = se.Prev
  delete_syn_elem temp
End Sub

Sub find_dbname()
  Dim temp As CSynElem

  Set se = se.Nxt 'skip over result
  Set temp = se
  Set se = se.Nxt
  delete_syn_elem temp 'delete parenthesis
  If Not se.maj = "&" Then
     print_err gStringTable(3131) '"Expecting a database name variable"
  End If
'sgBox "located the dbname =" + str$(se.de_no)
  out_one_integ (se.de_no)
  Set temp = se
  Set se = se.Nxt
  delete_syn_elem temp
End Sub

Sub find_dbvars()
  Dim temp As CSynElem
  Dim wk As String
  Dim typ As CTypeDef
  Dim t As CTypeElem
  Dim d1 As CDataElement
  Dim tname As String
  Dim seSave As CSynElem
  
  allowArrayNames = True              '***added 4/30/2001 **********************
  Do
     
     If se.maj = "p" Then
        Exit Do
     End If
'sgBox "dbvar arg = " + se.term
     Set d1 = find_de_by_no(se.de_no)
     If d1.typedefFlag = True Then
       For Each typ In gTarget.TypeDefCollection
         If Not d1.typedefName = typ.Name Then GoTo notThisOne '****added 912**********
substituteTypedef:
     
'sgBox "found dbvar for typedef=" + typ.name
        Set seSave = se
        tname = se.term
        For Each t In typ.Elements
          
          wk = tname + "." _
          + Right$(t.Name, Len(t.Name) - InStr(1, t.Name, ".", 0))
'sgBox "call searching for x=" + wk
          Set d1 = locateDataByName(wk)

'sgBox "dbarg CTypeDef-- adding arg=" + wk + "/" + d1.name + "  kind=" +d1.kind
          Set temp = New CSynElem
          temp.term = wk
          temp.termType = 4
          temp.maj = "d"
          temp.de_no = d1.tbl_no
          temp.sub1 = se.sub1
          temp.sub2 = se.sub2
          temp.sub3 = se.sub3
          temp.posInInput = se.posInInput
          If Not se.Nxt Is se_null_ptr Then
             Set se.Nxt.Prev = temp
          End If
          Set temp.Nxt = se.Nxt
          Set temp.Prev = se
          Set se.Nxt = temp
          Set se = se.Nxt
        Next
        Set se = seSave
        GoTo elimSe '***************added912****************************
notThisOne: '******************************added912****************************
       Next
       print_err gStringTable(3132) '"Invalid TYPE name"   '*******added 912
       'goto elimSe    '***********************commented out 912**********************************
     End If
     arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3
     out_the_1st_arg
     GoTo elimSe

elimSe:
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp
   Loop
   out_one_integ (0)
   allowArrayNames = False        '***added 4/30/2001 **********************
End Sub
Sub find_dbkey()
  Dim valu1 As CDataElement
  Dim temp As CSynElem
    If Not se.maj = "d" Then
       SYNTAX 61
    End If
     Set valu1 = find_de_by_no(se.de_no)
     If valu1.typedefFlag = True Then
       print_err gStringTable(3133) '"TYPE structures cannot be used as database keys."
     End If
     arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3
    
     out_the_1st_arg
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp
End Sub
Sub find_dbliteral()
  Dim temp As CSynElem
   If Not se.maj = "d" Then
       SYNTAX 62
    End If
     arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3
     
     out_the_1st_arg
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp
End Sub
Sub find_dbcardno()
  Dim temp As CSynElem
If Not se.maj = "d" Then
       SYNTAX 63
    End If
     arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3
     
     
     out_the_1st_arg
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp
End Sub
Sub find_dbcreator()
  Dim temp As CSynElem
  If Not se.maj = "d" Then
       SYNTAX 64
    End If
     arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3
     
     out_the_1st_arg
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp
End Sub
Sub find_dbsinglevar()
  Dim temp As CSynElem
  If Not se.maj = "d" Then
       SYNTAX 65
    End If
     arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3
     
     out_the_1st_arg
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp
End Sub
Sub find_dboptlength()
  Dim temp As CSynElem
  If Not se.maj = "d" Then
     If Not se.maj = "p" Then
        SYNTAX 66
     End If
     out_one_integ (0) 'no length
  Else
     arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3
     
     out_the_1st_arg
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp
  End If
End Sub
Sub find_dbwhere()
  Dim temp As CSynElem
    arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3
     
     out_the_1st_arg
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp
End Sub
Sub find_dboffset()
  Dim temp As CSynElem
     arg_1 = se.de_no
     arg1_occ1 = se.sub1
     arg1_occ2 = se.sub2
     arg1_occ3 = se.sub3

     
     out_the_1st_arg
     Set temp = se
     Set se = se.Nxt
     delete_syn_elem temp

End Sub
Sub db_set_result()
  Dim temp As CSynElem
   gen_alloc_arith_work
   arg_3 = arith_work_de_no
   arg3_occ1 = 0
   arg3_occ2 = 0
   arg3_occ3 = 0
   out_the_3rd_arg
   se.de_no = arg_3
   se.maj = "d"
   se.termType = 4
   se.term = ""
   se.termin = ""
   se.sub1 = 0
   se.sub2 = 0
   se.sub3 = 0
End Sub
Sub func_externalFunc()
   ' EMP overhauled
   Dim i As Integer, numSE As Integer
   Dim Value As CDataElement
   Dim numArgs As Integer
   Dim startArgs As Integer
   Dim runner As CSynElem
   Dim libraryID As Integer
   Dim procedureOrdinal As Integer
   Dim retType As Integer
   Dim retSize As Integer
   Dim delTemp As CSynElem
   Dim wantsContext As Boolean
   
   retType = 0
   retSize = 0
   
   ' Put pointers to syntax elements into a local array for convenience
   Set runner = se

   ' Advance
   Set runner = runner.Nxt
   If runner Is Nothing Then
      arith_syntax_err
   End If

   ' Check for parens
   If ((runner.maj <> "p") Or (runner.sub1 <> 0)) Then
      Set se = runner
      arith_syntax_err
      Exit Sub
   End If

   ' Advance
   Set runner = runner.Nxt
   If runner Is Nothing Then
      arith_syntax_err
   End If
   
   ' Library ID specified
   libraryID = runner.sub1
   
   wantsContext = Not (runner.sub2 = 0)
   
   ' Advance
   Set runner = runner.Nxt
   If runner Is Nothing Then
      arith_syntax_err
   End If
   
   ' Procedure ID and return type specified
   procedureOrdinal = runner.sub1
   retType = runner.sub2
   retSize = runner.sub3
   
   ' Advance
   Set runner = runner.Nxt
   If runner Is Nothing Then
      arith_syntax_err
   End If
   
   ' Number of args specified
   numArgs = runner.sub1
   
   ' Out the proc particulars
   If (retType = 0) Then
      out_one_char (&H71)
   Else
      If (wantsContext) Then
          out_one_char (&H7C)
      Else
          out_one_char (&H79)
      End If
   End If
   out_one_integ libraryID
   out_one_integ procedureOrdinal
   out_one_integ numArgs
   
   If (Not retType = 0) Then
     out_one_char (retType) 'Type of return value
     out_one_char (retSize) 'Size of return value
   
      ' Eat the argument types and spit them out
      For i = 1 To numArgs
        ' Advance
        Set runner = runner.Nxt
        If runner Is Nothing Then
         arith_syntax_err
        End If
        
        out_one_char (runner.sub2)
        out_one_char (runner.sub3)
      Next i
   End If
   
   ' Loop through function arguments and out them
   ' First four SE are part of the call, SE #5 is the first argument (if any)
   For i = 1 To numArgs
      ' Advance
      Set runner = runner.Nxt  ' Now on open paren or not
      If runner Is Nothing Then
         arith_syntax_err
      End If
      
      Set Value = find_de_by_no(runner.de_no)
      arg_2 = runner.de_no
      arg2_occ1 = runner.sub1
      arg2_occ2 = runner.sub2
      arg2_occ3 = runner.sub3
      out_the_2cnd_arg
   Next

   ' Now, out the return value
'   Set value = find_de_by_no(first_se.de_no)
'   If (value.kind = "n") Or (value.kind = "i") Then
'      gen_alloc_arith_work
'      arg_3 = arith_work_de_no
'   Else
'      gen_alloc_string_work
'      arg_3 = string_work_de_no
'   End If
   arg_3 = first_se.de_no
   arg3_occ1 = 0
   arg3_occ2 = 0
   arg3_occ3 = 0
   out_the_3rd_arg

   ' Advance
   Set runner = runner.Nxt  ' Now on open paren or not
   If runner Is Nothing Then
      arith_syntax_err
   End If
   
   ' Check for closing parenthesis
   If ((runner.maj <> "p") Or (runner.sub1 <> 1)) Then
      Set se = runner
      arith_syntax_err
      Exit Sub
   End If
   
   ' Finally, delete all but the last SE, and set the last to hold return value
   While (Not se Is runner)
      Set delTemp = se
      Set se = se.Nxt
      delete_syn_elem delTemp
   Wend
   
   se.de_no = arg_3
   se.maj = "d"
   se.sub1 = 0
   se.sub2 = 0
   se.sub3 = 0
   se.term = ""
   se.termType = 4
   
End Sub  'func_externalFunc
Sub old_func_externalFunc()
   Dim aSynElem(60) As CSynElem
   Dim i As Integer, numSE As Integer
   Dim Value As CDataElement
   Dim numArgs As Integer
   Dim startArgs As Integer
   
   ' Put pointers to syntax elements into a local array for convenience
   Set aSynElem(0) = se
   For i = 0 To 59
      If (aSynElem(i) Is se_null_ptr) Then
         Exit For
      Else
         Set aSynElem(i + 1) = aSynElem(i).Nxt
      End If
   Next
   numSE = i

   ' Check for parens
   If ((aSynElem(1).maj <> "p") Or (aSynElem(1).sub1 <> 0)) Then
      Set se = aSynElem(1)
      arith_syntax_err
      Exit Sub
   End If
   If ((aSynElem(numSE - 1).maj <> "p") Or (aSynElem(numSE - 1).sub1 <> 1)) Then
      Set se = aSynElem(i)
      arith_syntax_err
      Exit Sub
   End If

   ' Out the proc particulars
   If (aSynElem(3).sub2 = 0) Then
      out_one_char (&H71)
   Else
      out_one_char (&H79)
   End If
   out_one_integ aSynElem(2).sub1    'Library ID number
   out_one_integ aSynElem(3).sub1    'Procedure ordinal
   numArgs = aSynElem(4).sub1
   out_one_integ numArgs             'Number of parameters
   
   If (Not aSynElem(3).sub2 = 0) Then
     out_one_char (aSynElem(3).sub2) 'Type of return value
     out_one_char (aSynElem(3).sub3) 'Size of return value
   End If
      
   startArgs = 5

   ' Loop through function arguments and out them
   ' First four SE are part of the call, SE #5 is the first argument (if any)
   For i = startArgs To (4 + numArgs)
      Set Value = find_de_by_no(aSynElem(i).de_no)
      arg_2 = aSynElem(i).de_no
      arg2_occ1 = aSynElem(i).sub1
      arg2_occ2 = aSynElem(i).sub2
      arg2_occ3 = aSynElem(i).sub3
      out_the_2cnd_arg
   Next

   ' Now, out the return value
'   Set value = find_de_by_no(first_se.de_no)
'   If (value.kind = "n") Or (value.kind = "i") Then
'      gen_alloc_arith_work
'      arg_3 = arith_work_de_no
'   Else
'      gen_alloc_string_work
'      arg_3 = string_work_de_no
'   End If
   arg_3 = first_se.de_no
   arg3_occ1 = 0
   arg3_occ2 = 0
   arg3_occ3 = 0
   out_the_3rd_arg

   ' Finally, delete all but the last SE, and set the last to hold return value
   For i = 0 To (numSE - 2)
      delete_syn_elem aSynElem(i)
   Next
   Set se = aSynElem(numSE - 1)
   se.de_no = arg_3
   se.maj = "d"
   se.sub1 = 0
   se.sub2 = 0
   se.sub3 = 0
   se.term = ""
   se.termType = 4
End Sub  'func_externalFunc
Sub func_sysTrapFunc()
   Dim aSynElem(10) As CSynElem
   Dim i As Integer, numSE As Integer
'   Dim el As CExternalLibrary
'   Dim elm As CExternalLibraryMethod
   Dim Value As CDataElement
   Dim numArgs As Integer

   ' Put pointers to syntax elements into a local array for convenience
   Set aSynElem(0) = se
   For i = 0 To 9
      If aSynElem(i) Is se_null_ptr Then
         Exit For
      Else
         Set aSynElem(i + 1) = aSynElem(i).Nxt
      End If
   Next
   numSE = i

   ' Check for parens
   If ((aSynElem(1).maj <> "p") Or (aSynElem(1).sub1 <> 0)) Then
      Set se = aSynElem(1)
      arith_syntax_err
      Exit Sub
   End If
   If ((aSynElem(numSE - 1).maj <> "p") Or (aSynElem(numSE - 1).sub1 <> 1)) Then
      Set se = aSynElem(i)
      arith_syntax_err
      Exit Sub
   End If

   ' Out the proc particulars
   out_one_char (&H74)  'OS Trap Bytecode
   Set Value = find_de_by_no(aSynElem(2).de_no)
   out_one_integ Value.single_value    'Trap Number
   Set Value = find_de_by_no(aSynElem(3).de_no)
   numArgs = Value.single_value
   out_one_integ numArgs               'Number of arguments

   ' Loop through function arguments and out them
   ' First four SE are part of the call, SE #5 is the first argument (if any)
   For i = 4 To (3 + numArgs)
      Set Value = find_de_by_no(aSynElem(i).de_no)
      arg_2 = aSynElem(i).de_no
      arg2_occ1 = aSynElem(i).sub1
      arg2_occ2 = aSynElem(i).sub2
      arg2_occ3 = aSynElem(i).sub3
      out_the_2cnd_arg
   Next

   ' Now, out the return value
'   Set value = find_de_by_no(first_se.de_no)
'   If (value.kind = "n") Or (value.kind = "i") Then
'      gen_alloc_arith_work
'      arg_3 = arith_work_de_no
'   Else
'      gen_alloc_string_work
'      arg_3 = string_work_de_no
'   End If
   arg_3 = first_se.de_no
   arg3_occ1 = 0
   arg3_occ2 = 0
   arg3_occ3 = 0
   out_the_3rd_arg

   ' Finally, delete all but the last SE, and set the last to hold return value
   For i = 0 To (numSE - 2)
      delete_syn_elem aSynElem(i)
   Next
   Set se = aSynElem(numSE - 1)
   se.de_no = arg_3
   se.maj = "d"
   se.sub1 = 0
   se.sub2 = 0
   se.sub3 = 0
   se.term = ""
   se.termType = 4
End Sub  'func_sysTrapFunc
Sub set_result_string()

  Dim temp As CSynElem
   gen_alloc_string_work
   arg_3 = string_work_de_no
   arg3_occ1 = 0
   arg3_occ2 = 0
   arg3_occ3 = 0
   out_the_3rd_arg
   se.de_no = arg_3
   se.maj = "d"
   se.termType = 4
   se.term = ""
   se.termin = ""
   
    se.sub1 = 0
    se.sub2 = 0
    se.sub3 = 0
    
End Sub

Sub func_0arg(the_type As String)
    Dim a As CSynElem
    Dim b As CSynElem
    Dim c As CSynElem
    Set a = se
 'sgBox "at func_0arg   se.maj=" + se.maj
    If se.Nxt Is se_null_ptr Then MissingArg Else Set b = se.Nxt
    If b.Nxt Is se_null_ptr Then MissingArg Else Set c = b.Nxt

    If ((Not b.maj = "p") Or (Not b.sub1 = 0)) Then
       Set se = b
       arith_syntax_err
        Exit Sub
    End If
    If ((Not c.maj = "p") Or (Not c.sub1 = 1)) Then
       Set se = c
       arith_syntax_err
        Exit Sub
    End If
    If (the_type = "s") Then
      gen_alloc_string_work
      arg_3 = string_work_de_no
    Else
      gen_alloc_arith_work
      arg_3 = arith_work_de_no
    End If
    arg3_occ1 = 0
    arg3_occ2 = 0
    arg3_occ3 = 0
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_3rd_arg

    delete_syn_elem a
    delete_syn_elem b
    
    c.de_no = arg_3
    c.maj = "d"
    c.termType = 4
    c.sub1 = 0
    c.sub2 = 0
    c.sub3 = 0
    
    Set se = c
'sgBox "at end of func_0arg    se.maj=" + se.maj
   
End Sub
Sub func_1arg(the_type As String, type1 As String)

    Dim valu1 As CDataElement
    Set valu1 = dataelem_null_ptr
    Dim a As CSynElem
    Dim b As CSynElem
    Dim c As CSynElem
    Dim d As CSynElem
    Set a = se
    If a.Nxt Is se_null_ptr Then MissingArg Else Set b = se.Nxt
    If b.Nxt Is se_null_ptr Then MissingArg Else Set c = b.Nxt
    If c.Nxt Is se_null_ptr Then MissingArg Else Set d = c.Nxt

    If ((Not b.maj = "p") Or (Not b.sub1 = 0)) Then
        Set se = b
        arith_syntax_err
        Exit Sub
    End If
    If ((Not d.maj = "p") Or (Not d.sub1 = 1)) Then
        Set se = d
        arith_syntax_err
        Exit Sub
    End If
    If (the_type = "s") Then
      gen_alloc_string_work
      arg_3 = string_work_de_no
    Else
      gen_alloc_arith_work
      arg_3 = arith_work_de_no
    End If
    arg3_occ1 = 0
    arg3_occ2 = 0
    arg3_occ3 = 0
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (1) '/*no args*/
    If Not (c.termType = 4 Or c.termType = 5 Or c.termType = 6) Then    'added 5.20.2000
       print_err gStringTable(3134) '"Argument is not a valid variable name or literal."  'added 5.20.2000
    End If                            'added 5.20.2000
    Set valu1 = find_de_by_no(c.de_no)
                          
    If (((valu1.Kind = "s") And (type1 = "n")) _
     Or ((Not valu1.Kind = "s") And (type1 = "s"))) Then
        Set se = c
        print_err gStringTable(3135) + valu1.Name '"Incorrect type of variable used
        Set se = se_null_ptr
        Exit Sub
    End If

    arg_2 = c.de_no
    arg2_occ1 = c.sub1
    arg2_occ2 = c.sub2
    arg2_occ3 = c.sub3
    
    out_the_2cnd_arg
    out_the_3rd_arg

    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    d.de_no = arg_3
    d.maj = "d"
    d.sub1 = 0
    d.sub2 = 0
    d.sub3 = 0
    d.term = "" '1121
    If (the_type = "s") Then
      d.termType = 5
    Else
      d.termType = 6  '??  don't know what to set
      
    End If
    Set se = d
    Exit Sub
End Sub
Sub func_2arg(the_type As String, type1 As String, type2 As String)
    Dim valu1 As CDataElement
    Set valu1 = dataelem_null_ptr
    Dim a As CSynElem
    Dim b As CSynElem
    Dim c As CSynElem
    Dim d As CSynElem
    Dim e As CSynElem
    Set a = se
    If a.Nxt Is se_null_ptr Then MissingArg Else Set b = se.Nxt
    If b.Nxt Is se_null_ptr Then MissingArg Else Set c = b.Nxt
    If c.Nxt Is se_null_ptr Then MissingArg Else Set d = c.Nxt
    If d.Nxt Is se_null_ptr Then MissingArg Else Set e = d.Nxt

    If ((Not b.maj = "p") Or (Not b.sub1 = 0)) Then
        Set se = b
        arith_syntax_err
        Exit Sub
    End If
    If ((Not e.maj = "p") Or (Not e.sub1 = 1)) Then
        Set se = e
        arith_syntax_err
        Exit Sub
    End If
    If (the_type = "s") Then
      gen_alloc_string_work
      arg_3 = string_work_de_no
    Else
      gen_alloc_arith_work
      arg_3 = arith_work_de_no
    End If
    arg3_occ1 = 0
    arg3_occ2 = 0
    arg3_occ3 = 0
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (2) '/*no args*/
    If Not (c.termType = 4 Or c.termType = 5 Or c.termType = 6) _
    Or Not (d.termType = 4 Or d.termType = 5 Or d.termType = 6) Then 'added .20.2000
       print_err gStringTable(3136) '"Argument is not a valid variable name or literal." 'added .20.2000
    End If                            'added 5.20.2000
    Set valu1 = find_de_by_no(c.de_no)
    If (((valu1.Kind = "s") And (type1 = "n")) _
     Or ((Not valu1.Kind = "s") And (type1 = "s"))) Then
       If se.sub1 <> 103 Then  '103 is serialSend which can have any type  'added 4/07/2001 ***
        Set se = c
        print_err gStringTable(3137) + valu1.Name '"Incorrect type of variable used:
        Set se = se_null_ptr
        Exit Sub
      End If                                                             'added 4/07/2001 ***
    End If

    arg_2 = c.de_no
    arg2_occ1 = c.sub1
    arg2_occ2 = c.sub2
    arg2_occ3 = c.sub3
    
    out_the_2cnd_arg
    Set valu1 = find_de_by_no(d.de_no)
    If (((valu1.Kind = "s") And (type2 = "n")) _
     Or ((Not valu1.Kind = "s") And (type2 = "s"))) Then
        Set se = d
        print_err gStringTable(3138) + valu1.Name '"Incorrect type of variable used :
        Set se = se_null_ptr
        Exit Sub
    End If

    arg_2 = d.de_no
    arg2_occ1 = d.sub1
    arg2_occ2 = d.sub2
    arg2_occ3 = d.sub3
    
    out_the_2cnd_arg
    out_the_3rd_arg

    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    delete_syn_elem d
    e.de_no = arg_3
    e.maj = "d"
    e.sub1 = 0
    e.sub2 = 0
    e.sub3 = 0
    If (the_type = "s") Then
      e.termType = 5
    Else
      e.termType = 6 '??don't know what to set
      
    End If
    Set se = e
    Exit Sub
End Sub
Sub func_3arg(the_type As String, type1 As String, type2 As String, type3 As String)
    Dim valu1 As CDataElement
    Set valu1 = dataelem_null_ptr
    
    Dim a As CSynElem
    Dim b As CSynElem
    Dim c As CSynElem
    Dim d As CSynElem
    Dim e As CSynElem
    Dim f As CSynElem
    
    Set a = se
    If a.Nxt Is se_null_ptr Then MissingArg Else Set b = a.Nxt
    If b.Nxt Is se_null_ptr Then MissingArg Else Set c = b.Nxt
    If c.Nxt Is se_null_ptr Then MissingArg Else Set d = c.Nxt
    If d.Nxt Is se_null_ptr Then MissingArg Else Set e = d.Nxt
    If e.Nxt Is se_null_ptr Then MissingArg Else Set f = e.Nxt
    
    If ((Not b.maj = "p") Or (Not b.sub1 = 0)) Then
        Set se = b
        arith_syntax_err
        Exit Sub
    End If
    If ((Not f.maj = "p") Or (Not f.sub1 = 1)) Then
        Set se = f
        arith_syntax_err
        Exit Sub
    End If
    If (the_type = "s") Then
      gen_alloc_string_work
      arg_3 = string_work_de_no
    Else
      gen_alloc_arith_work
      arg_3 = arith_work_de_no
    End If
    arg3_occ1 = 0
    arg3_occ2 = 0
    arg3_occ3 = 0
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (3) '/*no args*/
    If Not (c.termType = 4 Or c.termType = 5 Or c.termType = 6) _
    Or Not (d.termType = 4 Or d.termType = 5 Or d.termType = 6) _
    Or Not (e.termType = 4 Or e.termType = 5 Or e.termType = 6) Then 'added 5.20.2000
       print_err gStringTable(3139) '"Argument is not a valid variable name or literal." 'added 5.20.2000
    End If                            'added 5.20.2000
    Set valu1 = find_de_by_no(c.de_no)
    If (((valu1.Kind = "s") And (type1 = "n")) _
     Or ((Not valu1.Kind = "s") And (type1 = "s"))) Then
       If se.sub1 <> 102 Then  '102 is serialReceive and can have either type  'added 4/07/2001 ***
        Set se = c
        print_err gStringTable(3140) + valu1.Name '"Incorrect type of variable used (" +  + ")."
        Set se = se_null_ptr
        Exit Sub
       End If                                                                  'added 4/07/2001 ***
    End If

    arg_2 = c.de_no
    arg2_occ1 = c.sub1
    arg2_occ2 = c.sub2
    arg2_occ3 = c.sub3
    
    
    out_the_2cnd_arg
    Set valu1 = find_de_by_no(d.de_no)
    If (((valu1.Kind = "s") And (type2 = "n")) _
     Or ((Not valu1.Kind = "s") And (type2 = "s"))) Then
        Set se = d
        print_err gStringTable(3141) + valu1.Name '"Incorrect type of variable used
        Set se = se_null_ptr
        Exit Sub
    End If

    arg_2 = d.de_no
    arg2_occ1 = d.sub1
    arg2_occ2 = d.sub2
    arg2_occ3 = d.sub3
    
   
    out_the_2cnd_arg

    Set valu1 = find_de_by_no(e.de_no)
    If (((valu1.Kind = "s") And (type3 = "n")) _
     Or ((Not valu1.Kind = "s") And (type3 = "s"))) Then
        Set se = e
        print_err gStringTable(3142) + valu1.Name '"Incorrect type of variable used
        Set se = se_null_ptr
        Exit Sub
    End If

    arg_2 = e.de_no
    arg2_occ1 = e.sub1
    arg2_occ2 = e.sub2
    arg2_occ3 = e.sub3
    
    
    out_the_2cnd_arg

    out_the_3rd_arg

    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    delete_syn_elem d
    delete_syn_elem e
    f.de_no = arg_3
    f.maj = "d"
    f.sub1 = 0
    f.sub2 = 0
    f.sub3 = 0
    If (the_type = "s") Then
      f.termType = 5
    Else
      f.termType = 6 '??don't know what to set
      
    End If
    Set se = f
    Exit Sub
End Sub
Sub func_4arg(the_type As String, type1 As String, type2 As String, _
                                  type3 As String, type4 As String)
    Dim valu1 As CDataElement
    Set valu1 = dataelem_null_ptr
    
    Dim a As CSynElem
    Dim b As CSynElem
    Dim c As CSynElem
    Dim d As CSynElem
    Dim e As CSynElem
    Dim f As CSynElem
    Dim G As CSynElem
    
    Set a = se
    If a.Nxt Is se_null_ptr Then MissingArg Else Set b = a.Nxt
    If b.Nxt Is se_null_ptr Then MissingArg Else Set c = b.Nxt
    If c.Nxt Is se_null_ptr Then MissingArg Else Set d = c.Nxt
    If d.Nxt Is se_null_ptr Then MissingArg Else Set e = d.Nxt
    If e.Nxt Is se_null_ptr Then MissingArg Else Set f = e.Nxt
    If f.Nxt Is se_null_ptr Then MissingArg Else Set G = f.Nxt
    If ((Not b.maj = "p") Or (Not b.sub1 = 0)) Then
        Set se = b
        arith_syntax_err
        Exit Sub
    End If
    If ((Not G.maj = "p") Or (Not G.sub1 = 1)) Then
        Set se = G
        arith_syntax_err
        Exit Sub
    End If
    If (the_type = "s") Then
      gen_alloc_string_work
      arg_3 = string_work_de_no
    Else
      gen_alloc_arith_work
      arg_3 = arith_work_de_no
    End If
    arg3_occ1 = 0
    arg3_occ2 = 0
    arg3_occ3 = 0
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (4) '/*no args*/
    If Not (c.termType = 4 Or c.termType = 5 Or c.termType = 6) _
    Or Not (d.termType = 4 Or d.termType = 5 Or d.termType = 6) _
    Or Not (e.termType = 4 Or e.termType = 5 Or e.termType = 6) _
    Or Not (f.termType = 4 Or f.termType = 5 Or f.termType = 6) Then 'added 5.20.2000
       print_err gStringTable(3143) '"Argument is not a valid variable name or literal." 'added 5.20.2000
    End If                                                        'added 5.20.2000
    Set valu1 = find_de_by_no(c.de_no)
    If (((valu1.Kind = "s") And (type1 = "n")) _
     Or ((Not valu1.Kind = "s") And (type1 = "s"))) Then
        Set se = c
        print_err gStringTable(3144) + valu1.Name '"Incorrect type of variable used
        Set se = se_null_ptr
        Exit Sub
    End If

    arg_2 = c.de_no
    arg2_occ1 = c.sub1
    arg2_occ2 = c.sub2
    arg2_occ3 = c.sub3
    
    
    out_the_2cnd_arg
    Set valu1 = find_de_by_no(d.de_no)
    If (((valu1.Kind = "s") And (type2 = "n")) _
     Or ((Not valu1.Kind = "s") And (type2 = "s"))) Then
        Set se = d
        print_err gStringTable(3145) + valu1.Name '"Incorrect type of variable used
        Set se = se_null_ptr
        Exit Sub
    End If

    arg_2 = d.de_no
    arg2_occ1 = d.sub1
    arg2_occ2 = d.sub2
    arg2_occ3 = d.sub3
    
    
    out_the_2cnd_arg

    Set valu1 = find_de_by_no(e.de_no)
    If (((valu1.Kind = "s") And (type3 = "n")) _
     Or ((Not valu1.Kind = "s") And (type3 = "s"))) Then
        Set se = e
        print_err gStringTable(3146) + valu1.Name '"Incorrect type of variable used
        Set se = se_null_ptr
        Exit Sub
    End If

    arg_2 = e.de_no
    arg2_occ1 = e.sub1
    arg2_occ2 = e.sub2
    arg2_occ3 = e.sub3
    
    
    out_the_2cnd_arg

    Set valu1 = find_de_by_no(f.de_no)
    If (((valu1.Kind = "s") And (type4 = "n")) _
     Or ((Not valu1.Kind = "s") And (type4 = "s"))) Then
        Set se = f
        print_err gStringTable(3147) + valu1.Name '"Incorrect type of variable used
        Set se = se_null_ptr
        Exit Sub
    End If
    
    arg_2 = f.de_no
    arg2_occ1 = f.sub1
    arg2_occ2 = f.sub2
    arg2_occ3 = f.sub3
    
    
    out_the_2cnd_arg
    
    out_the_3rd_arg

    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    delete_syn_elem d
    delete_syn_elem e
    delete_syn_elem f
    G.de_no = arg_3
    G.maj = "d"
    G.sub1 = 0
    G.sub2 = 0
    G.sub3 = 0
    If (the_type = "s") Then
      G.termType = 5
    Else
       G.termType = 6 '??don't know what to set
      
    End If
    Set se = G
  
End Sub
Sub arith_syntax_err()         '/* syntax err */
    SYNTAX 68
    Set se = se_null_ptr
    Exit Sub
End Sub
Sub gen_unary_minus()           '/* unary - */
    Dim temp As CSynElem
    Set temp = se_null_ptr
    
    Set temp = se.Nxt
    arg_1 = temp.de_no
    arg1_occ1 = temp.sub1
    arg1_occ2 = temp.sub2
    arg1_occ3 = temp.sub3
    
    
    gen_alloc_arith_work
    arg_2 = arith_work_de_no
    arg2_occ1 = 0
    arg2_occ2 = 0
    arg2_occ3 = 0
    out_tok_2arg (&H1B)    '/*negate --unary minus*/
    delete_syn_elem se
    Set se = temp
    temp.de_no = arith_work_de_no
    temp.sub1 = 0
    temp.sub2 = 0
    temp.sub3 = 0
    
    Exit Sub
End Sub
Sub MissingArg()
   print_err gStringTable(3148) '"Incorrect number of function arguments"
End Sub

Sub gen_three_term_arith()
    Dim a As CSynElem
    Dim b As CSynElem
    Dim c As CSynElem
    Dim d As CSynElem
    Dim e As CSynElem
    Dim f As CSynElem
    
    Dim valu1 As CDataElement
    Set valu1 = dataelem_null_ptr
    Dim valu2 As CDataElement
    Set valu2 = dataelem_null_ptr
    Dim tok As String

    Dim integ_sw As Integer
    Set a = se
    Set b = se.Nxt
    Set c = b.Nxt
    Set valu1 = find_de_by_no(a.de_no)
    Set valu2 = find_de_by_no(c.de_no)
    If (valu1.Kind = "s") Then
      If (Not valu2.Kind = "s") Then
        Set se = a
        SYNTAX 69
        Set se = se_null_ptr
        Exit Sub
      End If
      arg_1 = a.de_no
      arg1_occ1 = a.sub1
      arg1_occ2 = a.sub2
      arg1_occ3 = a.sub3
      
      
      arg_2 = c.de_no
      arg2_occ1 = c.sub1
      arg2_occ2 = c.sub2
      arg2_occ3 = c.sub3
      
      
      gen_alloc_string_work
      arg_3 = string_work_de_no
      arg3_occ1 = 0
      arg3_occ2 = 0
      arg3_occ3 = 0
      out_tok_3arg (&H90)
      delete_syn_elem a
      delete_syn_elem b
      c.de_no = string_work_de_no
      c.sub1 = 0
      c.sub2 = 0
      c.sub3 = 0
      c.term = "stringwk" + str$(string_work_de_no)
      c.termType = 4  '//
      Set se = c
      Exit Sub
    End If
    If (valu2.Kind = "s") Then
       Set se = c
       SYNTAX 70
       Set se = se_null_ptr
       Exit Sub
    End If

    Select Case (b.sub1)
    Case 1
        tok = &H4
         '/* + */"
    Case 2
        tok = &H1A
        '/* - */"
    Case 3
        tok = &HE
    Case 4
        tok = &HA
    Case 5
        tok = &H50
    End Select
    gen_alloc_arith_work
    arg_3 = arith_work_de_no
    arg3_occ1 = 0
    arg3_occ2 = 0
    arg3_occ3 = 0
    If ((b.sub1 = 2) Or (b.sub1 = 4)) Then
      arg_1 = c.de_no
      arg1_occ1 = c.sub1
      arg1_occ2 = c.sub2
      arg1_occ3 = c.sub3
      
      arg_2 = a.de_no
      arg2_occ1 = a.sub1
      arg2_occ2 = a.sub2
      arg2_occ3 = a.sub3
      
    Else
      arg_1 = a.de_no
      arg1_occ1 = a.sub1
      arg1_occ2 = a.sub2
      arg1_occ3 = a.sub3
      
      arg_2 = c.de_no
      arg2_occ1 = c.sub1
      arg2_occ2 = c.sub2
      arg2_occ3 = c.sub3
      
    End If
    out_tok_3arg (tok)
    out_one_char (&H0)
    If (b.sub1 = 4) Then  '/*on divide--need remainder */
      arg_3 = 0
      arg3_occ1 = 0
      arg3_occ2 = 0
      arg3_occ3 = 0
      ' out_the_3rd_arg
      out_one_integ (0)
    End If

'/*check if both arguments were integers */

'/*changed 12/23/91 to not cvt result of integ intmed calcs to int*/
    GoTo skip_integer_calcs

'/*!!!!!code skipped!!!!!*/
    integ_sw = 0

    If (chk_if_work_var(a.de_no)) Then
      integ_sw = integ_sw + arith_work_integ_sw(a.de_no - first_arith_work)
    Else
      Set valu1 = find_de_by_no(a.de_no)
      If (valu1.Dgt_Aft = 0) Then integ_sw = integ_sw + 1
    End If

    If (Not integ_sw = 0) Then
      If (chk_if_work_var(c.de_no)) Then
        integ_sw = integ_sw + arith_work_integ_sw(c.de_no - first_arith_work)
      Else
        Set valu1 = find_de_by_no(c.de_no)
        If (valu1.Dgt_Aft = 0) Then integ_sw = integ_sw + 1
      End If
    End If

    If (integ_sw = 2) Then
              '/*yes--both were integer, put out code */
              '/*to force result to be an integer     */
      out_one_char (&H5B)
      arg_3 = arith_work_de_no
      arg3_occ1 = 0
      arg3_occ2 = 0
      arg3_occ3 = 0
      out_the_3rd_arg
      arith_work_integ_sw(arith_work_de_no - first_arith_work) = 1
    Else
      arith_work_integ_sw(arith_work_de_no - first_arith_work) = 0
    End If
skip_integer_calcs:
If compiler_debug Then
dbug "before three term"
dbugDump
End If
    delete_syn_elem a
    delete_syn_elem b

    c.de_no = arith_work_de_no
    c.maj = "d"
    c.sub1 = 0
    c.sub2 = 0
    c.sub3 = 0
    c.term = "arithwk" + str$(arith_work_de_no)
    c.termType = 4  '//
    Set se = c
If compiler_debug Then
dbug "after three term"
dbugDump
End If
     Exit Sub
End Sub
Sub gen_alloc_arith_work()       '/* assign arith work variable */

    If (arith_work_de_no < first_arith_work) Then
        arith_work_de_no = first_arith_work
    End If

    If ((arith_work_de_no - first_arith_work) < kArithWorkDEMax) Then
        arith_work_de_no = arith_work_de_no + 1
        Exit Sub
    End If
    term_err_stop gStringTable(3224) '"Not enough arith work variables.")   '/* all used up */
    Exit Sub
End Sub
Sub gen_alloc_string_work()       '/* assign string work variable */

    If (string_work_de_no < first_string_work) Then
      string_work_de_no = first_string_work - 1
    End If
    string_work_de_no = string_work_de_no + 1
    If ((string_work_de_no - first_string_work) < kStringWorkDEMax) Then
          Exit Sub
    End If
    '/**/
    term_err_stop gStringTable(3225) '"Not enough string work variables.")   '/* all used up */
    Exit Sub
End Sub

Public Sub build_syn_elem()
   If Not OnOneLine = 2 Then term_used = 1
   arith_work_de_no = 0
   log_work_var_no = 0
   Set se = se_null_ptr
   Set first_se = se_null_ptr
   repeat_sw = 1
    Do While (repeat_sw)
      build_next_se
      If (repeat_sw And se.term = "then") Or (repeat_sw And se.term = "else") Then  'modified 4/07/2001 ***
      'If (repeat_sw And se.term = "then") Then
         repeat_sw = 0
      End If
    Loop
   eliminateNegConstants
   substituteForObjNotation
    'convertUndefFuncs
'    If (first_se Is se_null_ptr) Then
'        Exit Sub
'    End If
'    Exit Sub
End Sub

Sub eliminateNegConstants()
Dim Prev As CSynElem
Dim temp As CSynElem
Dim saveTerm As String
Dim saveTermtype As Integer
Dim res As Integer

   If first_se Is se_null_ptr Then Exit Sub
   Set se = first_se
   Do While Not se Is se_null_ptr
      'If Not se.term = "-" Then GoTo notPossible '02062006 GWH changed to agree with Larry's source, though it seemed to work OK.
      If Not se.term = "-" Or se.termType = 5 Then GoTo notPossible
      If se.Nxt Is se_null_ptr Then GoTo notPossible
      If Not se.Nxt.termType = 6 Then GoTo notPossible 'not num lit

      If se.Prev Is se_null_ptr Then Exit Sub
      If se.Prev.term = "=" Then GoTo possible
      If se.Prev.maj = "a" Then GoTo possible 'arith oper
      If se.Prev.maj = "p" And se.Prev.sub1 = 0 Then GoTo possible 'left paren
      If se.Prev.termType = 2 Then GoTo possible 'verb
      If se.Prev.termType = 3 Then GoTo possible 'reserved
      GoTo notPossible

possible:
      Set temp = se.Nxt.Nxt
      If temp Is se_null_ptr Then GoTo elim
      If temp.maj = "a" Then GoTo elim 'arith oper
      If temp.maj = "p" And temp.sub1 = 1 Then GoTo elim 'right paren
      If temp.termType = 3 Then GoTo elim 'reserved word
      GoTo notPossible

elim:
      saveTerm = term
      saveTermtype = termType
      term = "-" + se.Nxt.term
      termType = 6
      res = locate_data_tbl()
      Set Prev = se.Prev
      Set se = se.Nxt
      se.term = term
      se.de_no = data.tbl_no
      Set Prev.Nxt = se
      Set se.Prev = Prev

      term = saveTerm
      termType = saveTermtype

notPossible:
      Set se = se.Nxt
   Loop
End Sub

Sub convertUndefFuncs()
   '??code not now in use
   Set se = first_se
   Do While Not se Is Nothing And Not se Is se_null_ptr
      If Not se.maj = "*" Then GoTo ContinueLoop
      If se Is first_se Then GoTo ContinueLoop
      If se.Nxt.maj = "p" And se.Nxt.sub1 = 0 Then 'its a right paren
MsgBox "looking at " + se.term
      If se.Prev.term = "sub" Or se.Prev.term = "function" Or se.Prev.term = "dim" _
         Or se.Prev.term = "global" Or se.Prev.term = "type" _
            Then GoTo ContinueLoop
         
         'looks like an undef function
MsgBox "converting " + se.term
         se.maj = "u"
         term = se.term
         add_to_link_tbl
         se.de_no = p.tbl_no
      End If
      
ContinueLoop:
      Set se = se.Nxt
   Loop
End Sub
Sub substituteForObjNotation()
'this changes syn-elems to substitute for
'       obj.property = .....
'       x= obj.property
'       obj.method params
Dim Name As Variant
Dim objname As String
Dim methodProp As String
Dim pos As Integer
Dim view2 As CForm
Dim t As CTypeElem
Dim wk As String
Dim temp As CSynElem
Dim seSave As CSynElem  'added 06102002
Dim cnt As Integer      'added 06102002
Dim oTemp As Object
Dim nProc As Integer
Dim nArgs As Integer
Dim generalVerb As Boolean        'added 08222002
Dim generalVerbSE As CSynElem      'added 08222002
Dim x As CSynElem

   Set se = first_se
   
   'added starting here 9/22/2001
   If se.term = "let" Then           'eliminate leading LET  **added 9/22/2001
      If Not se.Nxt Is se_null_ptr Then      '**added 9/22/2001
         Set se = se.Nxt                     '**added 9/22/2001
         Set se.Prev = se_null_ptr           '**added 9/22/2001
         Set first_se = se                   '**added 9/22/2001
      End If                                 '**added 9/22/2001
   End If                                    '**added 9/22/2001
   'end of Additions 9/22/2001

   Do While Not se Is Nothing And Not se Is se_null_ptr
      'delete 06102002 If Not se.termType = 4 Then GoTo continueLoop
      If Not se.termType = 4 And Not se.termType = 7 Then GoTo ContinueLoop 'added 06102002
      pos = InStr(1, se.term, ".")
      If pos = 0 Then
         'For Each typ In model1.TypeDefCollection
'sgBox "Comparing typ.name=" + typ.name + " to " + se.term
         '    If lcase$(typ.name) = se.term Then GoTo substituteTypedef 'its a CTypeDef
         'Next
         
         GoTo ContinueLoop
      End If
         'it has xxx.yyy format
      'start section of additions  06102002
      Set seSave = se                       'added 08222002
      If pos = 1 Then
         'it's   .yyyy   controls(n).yyyyy
         objname = ""
         'substitutes for the format controls(position).method
        '   note that in this case the elements controls, leftparen, position, and right paren
        '        are all separate elements preceding the current term which was of the form
        '        .method.  At this point objname = null string and methodProp is the method
        '        Need to back up in the syn element chain to land on the variable name
        '
        'now, position back past the subscripts (however complicated) to find varname
        '     do this by locating the left paren that corresponds to the current right paren
        
        '08222002Set seSave = se
        cnt = 0  'count of open parentheses
'MsgBox "looking for prev term"
'compiler_debug = True
'dbugDump
        Do
           If se.Prev Is Nothing Then print_err "Can't locate the subscripted variable name."
           Set se = se.Prev
           If se.maj = "p" And se.sub1 = 1 Then
              cnt = cnt + 1  'another right paren, so up the count
           Else
              If se.maj = "p" And se.sub1 = 0 Then
                 cnt = cnt - 1   'left paren, so decrement the count
                 If cnt = 0 Then
                    If se.Prev Is Nothing Then print_err "Can't locate the subscripted variable name."
                    Set se = se.Prev 'now sitting on the 'controls' element
                    Exit Do
                 End If
              End If
           End If
        Loop
        
        If Not se.term = "controls" Then
'MsgBox "no controls" + se.term
           SYNTAX 71
        End If
'****** 08222002 replace everything until ending marker line that says "'controls' routine ends here")
        'Set seForControls = se
        'following stmt modified 09092002
        If seSave.term <> ".text" _
        And seSave.term <> ".index" _
        And seSave.term <> ".setfocus" _
        And seSave.term <> ".cursor" _
        And seSave.term <> ".redraw" _
        And seSave.term <> ".refresh" _
        And seSave.term <> ".status" _
        And seSave.term <> ".maxchars" _
        And seSave.term <> ".selected" _
        And seSave.term <> ".noitems" _
        And seSave.term <> ".itemtext" Then
        
           '09092002 had to break above stmt into 2 IFs because too many continuations
           If seSave.term <> ".current" _
            And seSave.term <> ".min" _
            And seSave.term <> ".max" _
            And seSave.term <> ".pagesize" _
            And seSave.term <> ".endsignaturecapture" _
            And seSave.term <> ".show" _
            And seSave.term <> ".hide" _
            And seSave.term <> ".add" _
            And seSave.term <> ".clear" _
            And seSave.term <> ".delete" _
            And seSave.term <> ".remove" _
            And seSave.term <> ".startsignaturecapture" _
            And seSave.term <> ".erasesignature" _
            And seSave.term <> ".displaysignature" _
            And seSave.term <> ".type" Then
'MsgBox "no .text " + seSave.term
                 '12182002 revised this IF stmt
                 If seSave.term <> ".id" _
                     And seSave.term <> ".label" Then
                     'revised this IF stmt 08152004 to add 'hideGridLines' and 'showGridLines'
                     If seSave.term <> ".col" _
                     And seSave.term <> ".cols" _
                     And seSave.term <> ".colwidth" _
                     And seSave.term <> ".toprow" _
                     And seSave.term <> ".row" _
                     And seSave.term <> ".rows" _
                     And seSave.term <> ".visiblerows" _
                     And seSave.term <> ".textmatrix" _
                     And seSave.term <> ".valuematrix" _
                     And seSave.term <> ".value" _
                     And seSave.term <> ".rowdata" _
                     And seSave.term <> ".add" _
                     And seSave.term <> ".delete" _
                     And seSave.term <> ".coltype" _
                     And seSave.term <> ".addrow" _
                     And seSave.term <> ".hidegridlines" _
                     And seSave.term <> ".showgridlines" _
                     And seSave.term <> ".bindtodatabase" _
                     And seSave.term <> ".left" _
                     And seSave.term <> ".top" _
                     And seSave.term <> ".width" _
                     And seSave.term <> ".height" _
                     And seSave.term <> ".fontmatrix" Then
                         'end insertions 04012005
                        SYNTAX 72
                     End If
                 End If
           End If                                         '09092002
        End If
        If se Is first_se Then
           'trying to set the property  (or verb like .show/.hide etc)//changed 08222002
            Set generalVerbSE = se
            generalVerb = False
            se.termType = 2 'verb
            'deleted 08222002 If seSave.term <> ".text" Then SYNTAX  'added 07152002
            'deleted 08222002 se.term = "controlssettext"
            se.term = "setGeneralProperty" 'may override later to be general verb
            se.termin = " "
            se.maj = "z"
            se.sub1 = 0
          
          
            If se.Nxt.maj = "p" And se.Nxt.sub1 = 0 Then
               se.Nxt.term = "p"    'indic that its by position
               se.Nxt.termType = 5  'alpha lit
               se.Nxt.maj = "d"
            Else
               SYNTAX 73
            End If
            Set se = seSave
            If se.Prev.maj = "p" And se.Prev.sub1 = 1 Then
            Else
'MsgBox "no right paren " + se.term
               SYNTAX 74
            End If
            Set se.Prev = se.Prev.Prev  'elim rt paren
            Set se.Prev.Nxt = se
            
            se.maj = "d"
            se.termType = 6 'set property number as numeric lit
            Select Case seSave.term
                Case ".text", ".label"    'revised 12182002
                     se.term = "0"
                Case ".status"
                     se.term = "1"
                Case ".selected"
                     se.term = "2"
                Case ".maxchars"
                     se.term = "3"
                Case ".current"
                     se.term = "4"
                Case ".min"
                     se.term = "5"
                Case ".max"
                     se.term = "6"
                Case ".pagesize"
                     se.term = "7"
                'additions 09242003
                Case ".col"
                     se.term = "48"
                Case ".cols"
                     se.term = "49"
                Case ".colwidth"
                     se.term = "50"
                Case ".row"
                     se.term = "51"
                Case ".rows"
                     se.term = "52"
                Case ".visiblerows"
                     se.term = "53"
                Case ".textmatrix"
                     se.term = "54"
                Case ".valuematrix"
                     se.term = "55"
                Case ".value"
                     se.term = "56"
                Case ".rowdata"
                     se.term = "57"
                Case ".toprow"             'inserted 02062004
                     se.term = "58"        'inserted 02062004
                Case ".fontmatrix"         'added 04012005
                     se.term = "59"        'added 04012005
                Case ".hide"
                     se.term = "0"
                     generalVerb = True
                 Case ".show"
                     se.term = "1"
                     generalVerb = True
                 Case ".add"
                     se.term = "2"
                     generalVerb = True
                 Case ".clear"
                     se.term = "3"
                     generalVerb = True
                 Case ".delete", ".remove"
                     se.term = "4"
                     generalVerb = True
                 Case ".startsignaturecapture"   '09092002
                     se.term = "5"
                     generalVerb = True
                 Case ".erasesignature"          '09092002
                     se.term = "6"
                     generalVerb = True
                 Case ".displaysignature"         '09092002
                     se.term = "7"
                     generalVerb = True
                 Case ".redraw", ".refresh"        '09092002
                     se.term = "8"                 '09092002
                     generalVerb = True            '09092002
                 Case ".setfocus", ".cursor"        '09092002
                     se.term = "9"                 '09092002
                     generalVerb = True            '09092002
                 'start of additions 09242003
                 Case ".addrow"
                     se.term = "70"
                     generalVerb = True
                 Case ".remove"
                     se.term = "71"
                     generalVerb = True
                 Case ".coltype"
                     se.term = "72"
                     generalVerb = True
                 Case ".bindtodatabase"
                     se.term = "73"
                     generalVerb = True
                 Case ".hidegridlines"            '08152004
                     se.term = "75"               '08152004
                     generalVerb = True           '08152004
                 Case ".showgridlines"            '08152004
                     se.term = "76"               '08152004
                     generalVerb = True           '08152004
                 'end of additions 09242003
                 'start additions 04012005
                Case "left"
                   '07052005 replace entire section                     '07052005
                   If se Is first_se Then                               '07052005
                      If o.obj.Kind <> "bmp" Then                       '07052005
                         substSetGeneralProperty controlId, 80, "n"     '07052005
                      Else                                              '07052005
                          substSetGeneralProperty o.ResourceId, 80, "n" '07052005
                      End If                                            '07052005
                   Else                                                 '07052005
                      If o.obj.Kind <> "bmp" Then                       '07052005
                          substGetGeneralProperty controlId, 80, "n"    '07052005
                      Else                                              '07052005
                          substGetGeneralProperty o.ResourceId, 80, "n" '07052005
                      End If                                            '07052005
                   End If                                               '07052005
                Case "top"
                   '07052005 replace entire section                     '07052005
                   If se Is first_se Then                               '07052005
                      If o.obj.Kind <> "bmp" Then                       '07052005
                         substSetGeneralProperty controlId, 81, "n"     '07052005
                      Else                                              '07052005
                          substSetGeneralProperty o.ResourceId, 81, "n" '07052005
                      End If                                            '07052005
                   Else                                                 '07052005
                      If o.obj.Kind <> "bmp" Then                       '07052005
                          substGetGeneralProperty controlId, 81, "n"    '07052005
                      Else                                              '07052005
                          substGetGeneralProperty o.ResourceId, 81, "n" '07052005
                      End If                                            '07052005
                   End If                                               '07052005
                Case "width"
                   '07052005 replace entire section                     '07052005
                   If se Is first_se Then                               '07052005
                      If o.obj.Kind <> "bmp" Then                       '07052005
                         substSetGeneralProperty controlId, 82, "n"     '07052005
                      Else                                              '07052005
                          substSetGeneralProperty o.ResourceId, 82, "n" '07052005
                      End If                                            '07052005
                   Else                                                 '07052005
                      If o.obj.Kind <> "bmp" Then                       '07052005
                          substGetGeneralProperty controlId, 82, "n"    '07052005
                      Else                                              '07052005
                          substGetGeneralProperty o.ResourceId, 82, "n" '07052005
                      End If                                            '07052005
                   End If                                               '07052005
                Case "height"
                   '07052005 replace entire section                     '07052005
                   If se Is first_se Then                               '07052005
                      If o.obj.Kind <> "bmp" Then                       '07052005
                         substSetGeneralProperty controlId, 83, "n"     '07052005
                      Else                                              '07052005
                          substSetGeneralProperty o.ResourceId, 83, "n" '07052005
                      End If                                            '07052005
                   Else                                                 '07052005
                      If o.obj.Kind <> "bmp" Then                       '07052005
                          substGetGeneralProperty controlId, 83, "n"    '07052005
                      Else                                              '07052005
                          substGetGeneralProperty o.ResourceId, 83, "n" '07052005
                      End If                                            '07052005
                   End If                                               '07052005
       'end additions 04012005
            End Select
            saveTerm1013 = term               'added 10132002
            saveTermType1013 = termType       'added 10132002
            term = se.term                    'added 10132002
            termType = 6                      'added 10132002
            locate_data_tbl                   'added 10132002
            se.de_no = term_tbl_no            'added 10132002
            term = saveTerm1013               'added 10132002
            termType = saveTermType1013       'added 10132002
            If generalVerb Then
                generalVerbSE.term = "generalverb"
            Else
              'additions 09242003
              If se.term = "50" Or se.term = "54" Or se.term = "55" Or se.term = "57" Or se.term = "59" Then  'modified 04012005
                  'these formats must have "(" + params + ")"
                  If se.Nxt Is Nothing Then SYNTAX 75
                  If se.Nxt.maj <> "p" And se.Nxt.sub1 <> 0 Then SYNTAX 76
                   
                  Do
                    If se.Nxt Is Nothing Then SYNTAX 77
                    Set se = se.Nxt
                    If se.maj = "p" And se.sub1 = 1 Then Exit Do
                    If se.maj = "r" And se.sub1 = 3 Then SYNTAX 78
                     
                  Loop
              End If
              'end of additions 09242003
              Set temp = se
              If se.Nxt Is Nothing Then SYNTAX 79   'added 09242003
              Set se = se.Nxt  'should be = sign
              If se.maj <> "r" Or se.sub1 <> 3 Then
'MsgBox "no = sign " + se.term + "  maj=" + se.maj
                  SYNTAX 80  '= sign
              End If
              'Set se = se.nxt   'elim = sign
              'Set se.prev = temp
              'Set se.prev.nxt = se
              'Set se = se.prev
            End If
        Else
           'trying to get the property
           Set seSave.Prev.Nxt = seSave.Nxt  'elim .text element
           If Not seSave.Nxt Is se_null_ptr Then Set seSave.Nxt.Prev = seSave.Prev
            
            'now, change the controls to controlsgettext
            se.termType = FUNCTYPE 'function
            '07152002 se.term = "controlsgettext"
            'following stmt modified 12182002  added test for ".label"
            'following statement modified 09242003 to add several grid properties
            If seSave.term = ".text" _
            Or seSave.term = ".label" _
            Or seSave.term = ".itemtext" _
            Or seSave.term = ".endsignaturecapture" _
            Or seSave.term = ".textmatrix" Then
                se.term = "getgeneralpropertystring" 'added 07152002
                se.sub1 = 43
            ElseIf seSave.term = ".status" _
                Or seSave.term = ".selected" _
                Or seSave.term = ".current" _
                Or seSave.term = ".type" _
                Or seSave.term = ".id" _
                Or seSave.term = ".noitems" _
                Or seSave.term = ".col" _
                Or seSave.term = ".cols" _
                Or seSave.term = ".colwidth" _
                Or seSave.term = ".row" _
                Or seSave.term = ".rows" _
                Or seSave.term = ".visiblerows" _
                Or seSave.term = ".valuematrix" _
                Or seSave.term = ".value" _
                Or seSave.term = ".rowdata" _
                Or seSave.term = ".left" _
                Or seSave.term = ".top" _
                Or seSave.term = ".width" _
                Or seSave.term = ".height" _
                Or seSave.term = ".fontmatrix" Then
                se.term = "getgeneralpropertynumeric" 'added 07152002
                se.sub1 = 42
            Else                            'added 07152002
                SYNTAX 81
            End If                          'added 07152002
            se.termin = " "
            se.maj = funcName
'compiler_debug = True
'dbugDump
            '07152002 se.sub1 = 72
            '08222002If seSave.term = ".text" Then   'added 07152002
            '    se.sub1 = 72                'added 07152002
            'Else                            'added 07152002
            '   If seSave.term = ".type" Then se.sub1 = 73 'added 07152002
            'End If                          'added 07152002
            
            Set se = se.Nxt
'MsgBox "maj=" + se.nxt.maj + "  sub1=" + str$(se.nxt.sub1)
            If se.maj = "p" And se.sub1 = 0 Then
            Else
              SYNTAX 82
            End If
            Set x = New CSynElem
            addSynElemAfterSE x
            Set se = se.Nxt
            se.maj = "d"
            se.termType = 5
            se.term = "p"      'indic its by position
            
            saveTerm1013 = term               'added 10132002
            saveTermType1013 = termType       'added 10132002
            term = se.term                    'added 10132002
            termType = 5                      'added 10132002
            locate_data_tbl                   'added 10132002
            se.de_no = term_tbl_no            'added 10132002
            term = saveTerm1013               'added 10132002
            termType = saveTermType1013       'added 10132002
            Set se = se.Nxt    'varname with positiion index
            
            If se.Nxt.maj = "p" And se.Nxt.sub1 = 1 Then    'modified 08222002
            Else
              SYNTAX 83
            End If
            Set x = New CSynElem
            addSynElemAfterSE x
            Set se = se.Nxt
            se.maj = "d"
            se.termType = 6
            Select Case seSave.term
           Case ".text", ".label"     'revised 12182002 to add ,".label"
                se.term = "0"
                'if followed by left paren--assume it's itemtext  'added 10052002
                If (Not seSave.Nxt Is se_null_ptr) Then               'added 10052002
                  If seSave.Nxt.maj = "p" And seSave.Nxt.sub1 = 0 Then    'added 10052002
                     se.term = "11"                               'added 10052002
                  Else                                 '***added 10132002
                     se.term = "0"                      '***added 10132002
                  End If                                          'added 10052002
                Else                                 '***added 10132002
                     se.term = "0"                      '***added 10132002
                End If                                            'added 10052002
              
              Case ".itemtext"
                se.term = "11"
              Case ".endsignaturecapture"    '09092002
                se.term = "12"
              Case ".status"
                se.term = "1"
              Case ".selected"
                se.term = "2"
              Case ".current"
                se.term = "5"
              Case ".noitems"
                se.term = "99"   'modified 07062005
              Case ".type"
                se.term = "13"
              Case ".index"
                se.term = "14"
              Case ".id"         'added 09302002
                se.term = "15"    'added 09302002
               Case ".col"
                     se.term = "48"
               Case ".cols"
                     se.term = "49"
               'start of additions 09242003
               Case ".colwidth"
                     se.term = "50"
               Case ".row"
                     se.term = "51"
               Case ".rows"
                     se.term = "52"
               Case ".visiblerows"
                     se.term = "53"
               Case ".textmatrix"
                     se.term = "54"
               Case ".valuematrix"
                     se.term = "55"
               Case ".value"
                     se.term = "56"
               Case ".rowdata"
                     se.term = "57"
               Case ".toprow"            'inserted 02062004
                     se.term = "58"       'inserted 02062004
               'end of additions 09242003
               Case ".fontmatrix"             'added 04012005
                     se.term = "59"           'added 04012005
               Case ".left"
                     se.term = "80"
               Case ".top"
                     se.term = "81"
               Case ".width"
                     se.term = "82"
               Case ".height"
                     se.term = "83"
               'end insertions 04012005
              End Select
              saveTerm1013 = term               'added 10132002
              saveTermType1013 = termType       'added 10132002
              term = se.term                    'added 10132002
              termType = 6                      'added 10132002
              locate_data_tbl                   'added 10132002
              se.de_no = term_tbl_no            'added 10132002
              term = saveTerm1013               'added 10132002
              termType = saveTermType1013       'added 10132002
              '09242003 If se.term = "11" Then                        'added 09092002
 'MsgBox "se.term=" + se.term
              If se.term = "11" Or se.term = "50" Or se.term = "54" Or se.term = "55" Or se.term = "57" Or se.term = "59" Then 'modified 04012005
                  'itemtext is followed by (itemNo),        'added 09092002
                  '  so must elim leadingparen              'added 09092002
                  If (se.Nxt Is se_null_ptr) Then SYNTAX 84   'added 09092002
                  If se.Nxt.maj <> "p" Or se.Nxt.sub1 <> 1 Then SYNTAX 86 'added 09092002
                  delete_syn_elem se.Nxt                    'added 09092002
                  'now--skip left paren following .itemtext 'added 09092002
                  If (se.Nxt Is se_null_ptr) Then SYNTAX 85   'added 09092002
                  If se.Nxt.maj <> "p" Or se.Nxt.sub1 <> 0 Then SYNTAX 87 'added 09092002
                  delete_syn_elem se.Nxt                    'added 09092002
              End If                                        'added 09092002
              If se.term = "12" Then                        'added 09092002
                  'ENDSIGNATURECAPTURE may be followed by (),          'added 09092002
                  '  so must elim parens                               'added 09092002
                  If (se.Nxt Is se_null_ptr) Then SYNTAX 88               'added 09092002
                  If se.Nxt.maj <> "p" Or se.Nxt.sub1 <> 1 Then SYNTAX 89 'added 09092002
                  
                  Set se = se.Nxt  'rt paren                           'added 09092002
                  If Not se.Nxt Is se_null_ptr Then                    'added 09092002
                      If se.Nxt.maj = "p" And se.Nxt.sub1 = 0 Then     'added 09092002
                          delete_syn_elem se.Nxt                       'added 09092002
                          If (se.Nxt Is se_null_ptr) Then SYNTAX 90      'added 09092002
                          If se.Nxt.maj <> "p" Or se.Nxt.sub1 <> 0 Then SYNTAX 91 'added 09092002
                          delete_syn_elem se.Nxt                       'added 09092002
                      End If                                          'added 09092002
                  End If                                               'added 09092002
               End If                                       'added 09092002
noParens:                                                   'added 09092002
              
              
              'added 09092002
              
              Set se = seSave.Prev
        End If
'******* 08222002 'controls' routine ends here  -- replace above on 08222002 ******************************
        
        GoTo ContinueLoop
      End If
      'end of additions  06102002
         
      'its xxx.yyy format
         objname = LCase$(Left$(se.term, pos - 1))
         If Left$(objname, 1) = "[" Then
            objname = Left$(objname, Len(objname) - 1)
            If Not Left$(objname, 1) = "[" Then
               SYNTAX 92
            End If
            objname = Right$(objname, Len(objname) - 1)
         End If
         methodProp = LCase$(Right$(se.term, Len(se.term) - pos))
         For Each typ In gTarget.TypeDefCollection
'sgBox "Comparing typ.name=" + typ.name + " to " + objname
            If LCase$(typ.Name) = LCase$(objname) Then GoTo ContinueLoop 'its a CTypeDef
         Next
         controlId = 0
'sgBox "searching for ctlname=" + objname + "  pos=" + str$(pos) + " se.term=" + se.term
          '06102002 start new inserted statements
          For Each view2 In gTarget.FormCollection
              If LCase$(view2.Name) = objname Then
                 Select Case methodProp
                   Case "clear"                       'changed 08022002
                     substituteverb "clear", objname  'changed 08022002
                   Case "redraw"
                     substituteverb "redraw", objname
                   Case "count"        'changed 07152002
                     substituteFunc "controlscount", objname, 75
                   
                   Case Else
                     GoTo notSupported
                 End Select
                 
              End If
          Next
          '06102002 end of inserted statemenmts
         For Each view2 In gTarget.FormCollection
            For Each o In view2.ObjectCollection
               If LCase$(o.obj.Name) = objname Then
                  controlId = o.obj.IdNo
                  Set controlObj = o
                  itsAVarname = False     'added 08222002
                  GoTo gotIt
               End If
            Next
         Next

'11/30/2000 MD
'sgBox "searching for libname=" + objname + "  pos=" + str$(pos) + " se.term=" + se.term
'07/10/2003 EMP
'changed to support new shared libraries
      If (objname = "systrap") Then
      Else
         On Error Resume Next
         Set oTemp = gTarget.LibraryCollection(objname)
         'If (err <> 0) Then GoTo notSupported
         If (err <> 0) Then GoTo tryObjectProperty
         On Error GoTo 0
         nProc = oTemp.GetProcNum(methodProp)
         nArgs = oTemp.GetNumProcArgs(methodProp)
         If nProc >= 0 Then
            substituteExternal oTemp.IdNo, nProc, nArgs, oTemp.GetArgTypes(methodProp)
         Else
            GoTo tryObjectProperty
         End If
      End If
'11/30/2000 MD
tryObjectProperty:
'start of additions 08222002 -- added all statements down to '***end of additions 08222002 ***
          'now, see if used a variable name   varname.propname
          term = objname
          termType = se.termType
          If locate_data_tbl() = 0 Then GoTo ContinueLoop
          'assume varname is a control name
          saveTblNo = term_tbl_no
          saveObjName = objname
          itsAVarname = True
          Set controlObj = Nothing
          controlId = 0
          GoTo gotIt
          
         
'***end of additions 08222002 ***
           '08222002GoTo continueLoop
'got a screen variable    objname.propname  (or varname.propname) 'added 08222002

gotIt:
          If methodProp = "index" Then  'added 07152002
              If se Is first_se Then    'added 07152002
                GoTo notSupported       'added 07152002
             Else                       'added 07152002
                '08222002 substituteFunc "controlsgetposition", objname, 74   'added 07152002
                substGetGeneralProperty controlId, 14, "n"    'added 08222002
             End If                     'added 07152002
          End If
          If methodProp = "id" Then     'added 09302002
              If se Is first_se Then    'added 09302002
                GoTo notSupported       'added 09302002
             Else                       'added 09302002
                substGetGeneralProperty controlId, 15, "n"    'added 09302002
             End If                     'added 09302002
          End If                        'added 09302002
          
          
          '0822002If o.obj.kind = "scr" Then
             Select Case methodProp
               Case "max"                                  'modified 08222002
                 If itsAVarname = False Then                       'added 08222002
                   If o.obj.Kind <> "scr" And o.obj.Kind <> "sli" Then GoTo notSupported 'modified 04012005
                 End If                                            'added 08222002
                 If se Is first_se Then                     'added 08222002
                     substSetGeneralProperty controlId, 6, "n"  'added 08222002
                 Else                                       'added 08222002
                      'start modification 04012005
                      If o.obj.Kind = "sli" Then
                          substGetGeneralProperty controlId, 6, "n"
                      Else
                         GoTo notSupported
                      End If
                      'end modifications  04012005
                 End If                                     'added 08222002
               Case "min"                                   'added 08222002
                 If itsAVarname = False Then                       'added 08222002
                   If o.obj.Kind <> "scr" And o.obj.Kind <> "sli" Then GoTo notSupported 'modified 04012005
                 End If                                            'added 08222002
                 If se Is first_se Then                     'added 08222002
                     substSetGeneralProperty controlId, 5, "n"  'added 08222002
                 Else                                       'added 08222002
                      'start modification 04012005
                      If o.obj.Kind = "sli" Then
                          substGetGeneralProperty controlId, 5, "n"
                      Else
                         GoTo notSupported
                      End If
                      'end modifications  04012005
                 End If                                     'added 08222002
               Case "pagesize"                              'added 08222002
                 If itsAVarname = False Then                       'added 08222002
                   If o.obj.Kind <> "scr" And o.obj.Kind <> "sli" Then GoTo notSupported 'modified 04012005
                 End If                                            'added 08222002
                 If se Is first_se Then                     'added 08222002
                      substSetGeneralProperty controlId, 7, "n"  'added 08222002
                 Else                                       'added 08222002
                      'start modification 04012005
                      If o.obj.Kind = "sli" Then
                          substGetGeneralProperty controlId, 7, "n"
                      Else
                         GoTo notSupported
                      End If
                      'end modifications  04012005
                 End If                                     'added 08222002
                 
               Case "current"                               'added 08222002
                 If itsAVarname = False Then                       'added 08222002
                   '07122005 If o.obj.kind <> "scr" And o.obj.kind <> "sli" Then GoTo notSupported 'modified 04012005
                   If o.obj.Kind <> "scr" Then GoTo notSupported   'added 07122005
                 End If                                            'added 08222002
                 If se Is first_se Then
                   '08222002substitute2for2 "scrollbarset" + methodProp, objname
                   '02062006substSetGeneralProperty controlId, 4, "n"  'added 08222002 GWH: now same as "Value"
                   substSetGeneralProperty controlId, 56, "n"  'added 08222002
                 Else
                   '08222002 If methodProp = "current" Then
                   '08222002 substituteFunc "scrollbargetcurrent", objname, 415
                   '02062006 substSetGeneralProperty controlId, 4, "n"  'added 08222002 GWH: Now same as "Value"
                   substGetGeneralProperty controlId, 56, "n"  'added 08222002
                   '08222002Else
                   '08222002   GoTo notSupported
                   '08222002End If
                 End If
               '08222002Case Default
               '08222002  GoTo tryothers
             '08222002End Select
          '08222002End If
'08222002tryothers:
          
'MsgBox "trying method/prop=" + methodProp + "  kind=" + o.obj.kind
          '08222002Select Case methodProp
          
            Case "type"                  'added 08222002
               If se Is first_se Then    'added 08222002
                     GoTo notSupported   'added 08222002
               Else                      'added 08222002
                     substGetGeneralProperty controlId, 13, "n"  'added 08222002
               End If                    'added 08222002
            Case "refresh", "redraw"
               If Not se Is first_se Then GoTo notSupported
               '08222002substitute2for1 "redraw", objname
               substGeneralVerb controlId, 8   '08222002  added
               'Set se = se.nxt 'position on 'redraw'
               '09092002 substituteInsert "id"
            Case "setfocus", "cursor"
               If itsAVarname = False Then                         'added 08222002
                   If o.obj.Kind <> "fld" Then GoTo notSupported   'added 08222002
               End If                                              'added 08222002
               If Not se Is first_se Then GoTo notSupported
               '08222002substitute2for1 "cursor", objname
               substGeneralVerb controlId, 9   '08222002  added
               'Set se = se.nxt 'position on 'redraw'
               '08222002substituteInsert "id"
            Case "startsignaturecapture"         '09092002
               If itsAVarname = False Then                         'added 08222002
                  If Not o.obj.Kind = "gad" Then GoTo notSupported
               End If                                              'added 08222002
               If se Is first_se Then
                  '08222002 substitute2for1 "signaturestartcapture", objname
                  substGeneralVerb controlId, 5   '08222002  added
               Else
                 GoTo notSupported
               End If
            
            Case "displaysignature"              '09092002
               If itsAVarname = False Then                       'added 08222002
                 If Not o.obj.Kind = "gad" Then GoTo notSupported
               End If                                             'added 08222002
               If se Is first_se Then
                  '08222002 substitute2for1 "signaturedisplay", objname
                  substGeneralVerb controlId, 7   '08222002  added
               Else
                 GoTo notSupported
               End If
            Case "erasesignature"                  '09092002
               If itsAVarname = False Then                       'added 08222002
                 If Not o.obj.Kind = "gad" Then GoTo notSupported
               End If                                            'added 08222002
               If se Is first_se Then
                  '08222002 substitute2for1 "signatureerase", objname
                  substGeneralVerb controlId, 6   '08222002  added
               Else
                 GoTo notSupported
               End If
            Case "endsignaturecapture"               '09092002
               If itsAVarname = False Then                       'added 08222002
                 If Not o.obj.Kind = "gad" Then GoTo notSupported
               End If                                             'added 08222002
               If se Is first_se Then
                  GoTo notSupported
                                       
               Else
                  '08222002 substituteFunc "signatureendcapture", objname, 418
                  substGetGeneralProperty controlId, 12, "s"   'added 08222002
'MsgBox "substituting"
               End If
               
               
            Case "itemtext"
itsItemText:                                                              'added 10052002
              '08222002Select Case o.obj.kind
              '08222002  Case "lst"
              If itsAVarname = False Then                         'added 08222002
                   'following stmt modified 09242003
                   If o.obj.Kind <> "lst" And o.obj.Kind <> "pop" And o.obj.Kind <> "grd" _
                        Then GoTo notSupported   '09242003
               End If                                              'added 08222002
               
               If se Is first_se Then
                     'If o.obj.Kind <> "grd" Then    'added 09242003
                         GoTo notSupported          'added 09242003
                     'End If                         'added 09242003
                     
                     'additions 09242003
 
                     
                     'end of additions 09242003
                     'substitute2for2 "listsettext", objname
                  Else
                     '08222002 substituteFunc "listgetitemtext", objname, 404
                     substGetGeneralProperty controlId, 11, "s"  'added 08222002
                  End If
                '08222002Case "pop"
                '08222002  If se Is first_se Then
                '08222002    'substitute2for2 "popupsettext", objname
                '08222002    GoTo notSupported
                '08222002  Else
                '08222002     substituteFunc "popupgetitemtext", objname, 414
                '08222002   End If
              '08222002End Select
            Case "text", "label"
              
                '08222002Select Case o.obj.kind
                '08222002  Case "but", "lbl", "chk", "cho", "rpt", "sel"
               If itsAVarname = False Then                         'added 08222002
                   'stmt modified 09242003
                   If o.obj.Kind <> "but" And o.obj.Kind <> "lbl" And o.obj.Kind <> "chk" _
                   And o.obj.Kind <> "cho" And o.obj.Kind <> "rpt" And o.obj.Kind <> "sel" _
                   And o.obj.Kind <> "pop" And o.obj.Kind <> "fld" And o.obj.Kind <> "lst" _
                   And o.obj.Kind <> "grd" Then GoTo notSupported
               
               End If                                              'added 08222002
               
              If se Is first_se Then
                       '0822002substitute2for2 "controlsettext", objname
                       If Not se.Nxt Is se_null_ptr Then                   'added 10052002
                          If se.Nxt.maj = "p" And se.Nxt.sub1 = 0 Then     'added 10052002
                             SYNTAX 93                                       'added 10052002
                          End If                                           'added 10052002
                       End If                                              'added10052002
                       substSetGeneralProperty controlId, 0, "s"  'added 08222002
               Else
                      '08222002 substituteFunc "controlgettext", objname, 417
                       If Not se.Nxt Is se_null_ptr Then                   'added 10052002
                          If se.Nxt.maj = "p" And se.Nxt.sub1 = 0 Then     'added 10052002
                             'assume itemtext                              'added 10052002
                             GoTo itsItemText                               'added 10052002
                          End If                                           'added 10052002
                        End If                                              'added 10052002
                        substGetGeneralProperty controlId, 0, "s"  'added 08222002
               End If
                  '08222002Case "pop"
                  '08222002  If se Is first_se Then
                  '08222002    substitute2for2 "popupsettext", objname
                  '08222002  Else
                  '08222002     substituteFunc "popupgettext", objname, 416
                  '08222002  End If
                  '08222002Case "fld"
                  '08222002  If se Is first_se Then
                  '08222002      substitute2for2 "fieldsettext", objname
                  '08222002  Else
                  '08222002      substituteFunc "fieldgettext", objname, 401
                  '08222002  End If
                  '08222002Case "tbl"
                  '08222002  If se Is first_se Then
                  '08222002    substitute2for2 "tablesetitemtext", objname
                  '08222002  Else
                  '08222002    substituteFunc "tablegetitemtext", objname, 405
                  '08222002
                  '08222002  End If
                  '08222002Case "lst"
                  '08222002  If se Is first_se Then GoTo notSupported
                  '08222002 substituteFunc "listgetitemtext", objname, 404
                  '08222002   Case Default
                  
'08222002notSupported:
'08222002                print_err "Object(" + o.obj.kind + ") does not support that method or property(" + methodProp + ")"
              '08222002  End Select
           Case "show"
              If Not se Is first_se Then GoTo notSupported
              '08222002substitute2for1 "controlshow", objname
              If itsAVarname = False Then                'added 10082002
                   If o.obj.Kind = "bmp" Then           'added 10082002
                      substGeneralVerb o.ResourceId, 1  'added 10082002
                      GoTo ContinueLoop                 'added 10082002
                   End If                               'added 10082002
               End If                                   'added 10082002
               substGeneralVerb controlId, 1   '08222002  added
            Case "hide"
              If Not se Is first_se Then GoTo notSupported
              '08222002 substitute2for1 "controlhide", objname
              If itsAVarname = False Then                'added 10082002
                   If o.obj.Kind = "bmp" Then           'added 10082002
                      substGeneralVerb o.ResourceId, 0  'added 10082002
                      GoTo ContinueLoop                 'added 10082002
                   End If                               'added 10082002
               End If                                   'added 10082002
              substGeneralVerb controlId, 0   '08222002  added
            Case "clear"
              '08222002Select Case o.obj.kind
              '08222002  Case "pop"
              If itsAVarname = False Then                         'added 08222002
                   'following stmt modified 09242003
                   If o.obj.Kind <> "pop" And o.obj.Kind <> "lst" And o.obj.Kind <> "grd" Then GoTo notSupported
               End If                                              'added 08222002
               
               If Not se Is first_se Then GoTo notSupported
                  '08222002 substitute2for1 "popupclear", objname
                  substGeneralVerb controlId, 3   '08222002  added
                '08222002Case "lst"
                '08222002  If Not se Is first_se Then GoTo notSupported
                '08222002  substitute2for1 "listclear", objname
                '08222002Case Default
                '08222002  GoTo notSupported
              '08222002End Select
            Case "status"
              
               '08222002Select Case o.obj.kind
              '08222002  Case "chk", "cho"
              If itsAVarname = False Then                         'added 08222002
                   If o.obj.Kind <> "chk" And o.obj.Kind <> "cho" Then GoTo notSupported   'added 08222002
               End If                                              'added 08222002
               
               If se Is first_se Then
                    '08222002substitute2for2 "controlsetstatus", objname
                    substSetGeneralProperty controlId, 1, "n"  'added 08222002
                  Else
                    '08222002 substituteFunc "controlgetstatus", objname, 400
                    substGetGeneralProperty controlId, 1, "n"  'added 08222002
                  End If
                '08222002Case "default"
                '08222002  GoTo notSupported
              '08222002End Select
            Case "addrow"
                If itsAVarname = False Then
                   If o.obj.Kind <> "grd" Then GoTo notSupported
                End If
               
               If Not se Is first_se Then GoTo notSupported
             
               If itsAVarname = False Then
                    
                    substGeneralVerb controlId, 70
               Else
                    substGeneralVerb controlId, 2
                End If
            'end of additions for addrow 06072004
            Case "add"
              If itsAVarname = False Then                         'added 08222002
                   If o.obj.Kind <> "pop" And o.obj.Kind <> "lst" And o.obj.Kind <> "grd" Then GoTo notSupported  'added 08222002
               End If                                              'added 08222002
               
              If Not se Is first_se Then GoTo notSupported
                  '08222002 substitute2for1 "listadditem", objname
               If itsAVarname = False Then    'added 06072004
                   If o.obj.Kind = "grd" Then   'added 06072004
                        substGeneralVerb controlId, 70
                        GoTo skipOverGridTest              'added 06072004
                   End If                                  'added 06072004
               End If                                      'added 060702004
               'commented out 06072004 Else
                    substGeneralVerb controlId, 2  '08222002  added
               'commented out 06072004 End If
skipOverGridTest:   'added 06072004

             Case "remove", "delete"
               If itsAVarname = False Then                         'added 08222002
                   If o.obj.Kind <> "pop" And o.obj.Kind <> "lst" And o.obj.Kind <> "grd" Then GoTo notSupported   'added 08222002
               End If                                              'added 08222002
               '08222002 substitute2for1 "listdeleteitem", objname
               '02022004  changes below
               
               
               If itsAVarname = False Then         'added 06072004
                  If o.obj.Kind = "grd" Then
                     substGeneralVerb controlId, 71
                     GoTo skipOverGridTest2        'added 06072004
                  End If                           'added 06072004
               End If                              'added 06072004
               '06072004 Else
                   substGeneralVerb controlId, 4    '08222002  added
              '06072004End If
              '08222002  Case "pop"
              '08222002     substitute2for1 "popupdeleteitem", objname
              '08222002       Case Default
              '08222002    GoTo notSupported
             '08222002End Select
skipOverGridTest2:                   'added 06072004

             Case "maxchars"
               If itsAVarname = False Then   'added 08222002
                 If o.obj.Kind <> "fld" Then GoTo notSupported  'modified 08222002
               End If                                           'added 08222002
               If Not se Is first_se Then GoTo notSupported
                   '08222002substitute2for2 "fieldsetmaxchars", objname
                   substSetGeneralProperty controlId, 3, "n"  'added 08222002
               '08222002Else
               '08222002  GoTo notSupported
               '08222002End If
               '08222002End If                                         'added 08222002
             Case "selected"
               '08222002Select Case o.obj.kind
               '08222002  Case "lst"
               If itsAVarname = False Then                         'added 08222002
                   If o.obj.Kind <> "pop" And o.obj.Kind <> "lst" Then GoTo notSupported   'added 08222002
               End If                                              'added 08222002
               
               If se Is first_se Then
                     '08222002substitute2for2 "listsetselected", objname
                     substSetGeneralProperty controlId, 2, "n"  'added 08222002
                   Else
                     '08222002 substituteFunc "listgetselecteditemno", objname, 403
                     substGetGeneralProperty controlId, 2, "n"  'added 08222002
                   End If
               '08222002  Case "pop"
               '08222002      If se Is first_se Then
               '08222002         substitute2for2 "popupsetselected", objname
               '08222002      Else
               '08222002         substituteFunc "popupgetselecteditemno", objname, 413
               '08222002      End If
               '08222002   Case "tbl"
               '08222002      substitute2for1 "tablesetselected", objname
               '08222002    Case Default
               '08222002     GoTo notSupported
               '08222002   End Select
      Case "noitems"
                '08222002  Select Case o.obj.kind
                '08222002    Case "tbl"
                '08222002      substituteFunc "tablegetnorows", objname, 408
                '08222002    Case "lst"
                '08222002 substituteFunc "listgetnoitems", objname, 402
                '08222002    Case "pop"
                '08222002       substituteFunc "popupgetnoitems", objname, 412
               If itsAVarname = False Then                         'added 08222002
                   If o.obj.Kind <> "pop" And o.obj.Kind <> "lst" Then GoTo notSupported   'added 08222002
               End If                                              'added 08222002
               
               If se Is first_se Then GoTo notSupported    'added 08222002
                    substGetGeneralProperty controlId, 9, "n"  'added 08222002
                '08222002  Case Default
                '08222002      GoTo notSupported
                '08222002  End Select
              
              'start of additions 09242003
              Case "col"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 48, "n"
                   Else
                      substGetGeneralProperty controlId, 48, "n"
                   End If
              Case "cols"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      'substSetGeneralProperty controlId, 49, "n"
                      GoTo notSupported
                   Else
                      substGetGeneralProperty controlId, 49, "n"
                   End If
               Case "row"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 51, "n"
                   Else
                      substGetGeneralProperty controlId, 51, "n"
                   End If
               Case "rows"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 52, "n"
                   Else
                      substGetGeneralProperty controlId, 52, "n"
                   End If
               Case "visiblerows"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      'substSetGeneralProperty controlId, 53, "n"
                      GoTo notSupported
                   Else
                      substGetGeneralProperty controlId, 53, "n"
                   End If
               'start deletions 02062004
               'george--this was the duplicate Case "cols" that you told me about
               'Case "col"
               '    If itsAVarname = False Then
               '       If o.obj.kind <> "grid" Then GoTo notSupported
               '    End If
               '    If se Is first_se Then
               '       substSetGeneralProperty controlId, 48, "n"
               '    Else
               '       substGetGeneralProperty controlId, 48, "n"
               '    End If
               'end of deletions 02062004
               Case "value"
                   If itsAVarname = False Then
                      '07122005 If o.obj.kind <> "grid" Then GoTo notSupported
                      If o.obj.Kind <> "grd" And o.obj.Kind <> "sli" And o.obj.Kind <> "scr" Then GoTo notSupported   '07122005
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 56, "n"
                   Else
                      substGetGeneralProperty controlId, 56, "n"
                   End If
                Case "colwidth"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 50, "n"
                   Else
                      substGetGeneralProperty controlId, 50, "n"
                   End If
                Case "textmatrix"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 54, "s"
                   Else
                      substGetGeneralProperty controlId, 54, "s"
                   End If
                Case "valuematrix"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 55, "n"
                   Else
                      substGetGeneralProperty controlId, 55, "n"
                   End If
                'start additions 04012005
                Case "fontmatrix"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 59, "n"
                   Else
                      substGetGeneralProperty controlId, 59, "n"
                   End If
                'end additions 04012005
                Case "rowdata"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 57, "n"
                   Else
                      substGetGeneralProperty controlId, 57, "n"
                   End If
               'start additions 02062004
                Case "toprow"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 58, "n"
                   Else
                      substGetGeneralProperty controlId, 58, "n"
                   End If
                'end additions 02062004
                Case "coltype"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   substGeneralVerb controlId, 72
                Case "bindtodatabase"
                   If itsAVarname = False Then
                      If o.obj.Kind <> "grd" Then GoTo notSupported
                   End If
                   substGeneralVerb controlId, 73
       
                Case "hidegridlines"                                   '08152004
                   If itsAVarname = False Then                         '08152004
                      If o.obj.Kind <> "grd" Then GoTo notSupported   '08152004
                   End If                                              '08152004
                   substGeneralVerb controlId, 75                      '08152004
                Case "showgridlines"                                   '08152004
                   If itsAVarname = False Then                         '08152004
                      If o.obj.Kind <> "grd" Then GoTo notSupported   '08152004
                   End If                                              '08152004
                   substGeneralVerb controlId, 76                      '08152004

      'end of additions 09242003
       'start additions 04012005
                Case "left"
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 80, "n"
                   Else
                      substGetGeneralProperty controlId, 80, "n"
                   End If
                Case "top"
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 81, "n"
                   Else
                      substGetGeneralProperty controlId, 81, "n"
                   End If
                Case "width"
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 82, "n"
                   Else
                      substGetGeneralProperty controlId, 82, "n"
                   End If
                Case "height"
                   If se Is first_se Then
                      substSetGeneralProperty controlId, 83, "n"
                   Else
                      substGetGeneralProperty controlId, 83, "n"
                   End If
       'end additions 04012005

      End Select

substituteTypedef:
ContinueLoop:
      Set se = se.Nxt
   Loop
   Exit Sub    'added 08222002
notSupported:   'added 08222002
                print_err "Object(" + o.obj.Kind + ") does not support that method or property(" + methodProp + ")"  'added 08222002
   
End Sub
'entire routine added 08222002
Sub substGetGeneralProperty(controlId As Integer, propId As Integer, retType As String)
  Dim x As CSynElem
  
  se.termType = FUNCTYPE
  se.maj = funcName
  If retType = "s" Then
     se.term = "getGeneralPropertyString"
     se.sub1 = 43
  Else
     se.term = "getGeneralPropertyNumeric"
     se.sub1 = 42
  End If
  
  Set x = New CSynElem  'add left paren
  addSynElemAfterSE x
  Set se = se.Nxt
  se.termType = 7
  se.maj = "p"
  se.sub1 = 0
  
  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  se.termType = 5
  se.maj = "d"
  If itsAVarname = False Then
       se.term = "i"  'indic its by control id
  Else
       se.term = "v"   'indic its by varname
  End If
  
    saveTerm1013 = term               'added 10132002
    saveTermType1013 = termType       'added 10132002
    term = se.term                    'added 10132002
    termType = 5                      'added 10132002
    locate_data_tbl                   'added 10132002
    se.de_no = term_tbl_no            'added 10132002
    term = saveTerm1013               'added 10132002
    termType = saveTermType1013       'added 10132002

  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  If itsAVarname = False Then
    se.termType = 6
    se.maj = "d"
    se.term = str$(controlId)
    saveTerm1013 = term               'added 10132002
    saveTermType1013 = termType       'added 10132002
    term = se.term                    'added 10132002
    termType = 6                      'added 10132002
    strip_and_locate_data_tbl                   'added 10132002
    se.de_no = term_tbl_no            'added 10132002
    term = saveTerm1013               'added 10132002
    termType = saveTermType1013       'added 10132002
  Else
    se.termType = 4
    se.maj = "d"
    se.term = saveObjName
    se.de_no = saveTblNo
    se.sub1 = 0
    se.sub2 = 0
    se.sub3 = 0
  End If
  
  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  se.termType = 6
  se.maj = "d"
  se.term = str$(propId)
  saveTerm1013 = term               'added 10132002
  saveTermType1013 = termType       'added 10132002
  term = se.term                    'added 10132002
  termType = 6                      'added 10132002
  strip_and_locate_data_tbl                   'added 10132002
  se.de_no = term_tbl_no            'added 10132002
  term = saveTerm1013               'added 10132002
  termType = saveTermType1013       'added 10132002
  
 Select Case propId                             'added 09092002
  Case 11                                   'added 09092002
        If se.Nxt Is se_null_ptr Then SYNTAX 94              'added 09092002
        Set x = se.Nxt                                     'added 09092002
        If x.maj <> "p" Or x.sub1 <> 0 Then SYNTAX 95        'added 09092002
        delete_syn_elem x                                  'added 09092002
    Case 12                                                'added 09092002
        If se.Nxt Is se_null_ptr Then GoTo addRightParen              'added 09092002
        Set x = se.Nxt                                     'added 09092002
        If x.maj <> "p" Or x.sub1 <> 0 Then SYNTAX 96        'added 09092002
        delete_syn_elem x                                  'added 09092002
    'start additions 09242003
    Case 50, 54, 55, 57, 59   'modified 04012005
        If se.Nxt Is se_null_ptr Then SYNTAX 97
        Set x = se.Nxt
        If x.maj <> "p" Or x.sub1 <> 0 Then SYNTAX 98
        delete_syn_elem x
    'end of additions 09242003
      
    Case Else                                             'added 09092002
addRightParen:                                              'added 09092002
        Set x = New CSynElem  'add rtparen    'indented 09092002
        addSynElemAfterSE x                 'indented 09092002
        Set se = se.Nxt                     'indented 09092002
        se.termType = 7                     'indented 09092002
        se.maj = "p"                        'indented 09092002
        se.sub1 = 1                         'indented 09092002
  
  End Select                                   'added 09092002
  
End Sub
'entire routine added 08222002
Sub substSetGeneralProperty(controlId As Integer, propId As Integer, retType As String)
  Dim x As CSynElem
  
  se.termType = 2
  se.maj = "z"
  'If retType = "s" Then
  '   se.term = "getGeneralPropertyString"
  '   se.sub1 = 43
  'Else
  '   se.term = "getGeneralPropertyNumeric"
  '   se.sub1 = 42
  'End If
  se.term = "setgeneralproperty"
  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  se.termType = 5
  se.maj = "d"
  If itsAVarname = False Then
       se.term = "i"  'indic its by control id
  Else
       se.term = "v"   'indic its by varname
  End If
            saveTerm1013 = term               'added 10132002
            saveTermType1013 = termType       'added 10132002
            term = se.term                    'added 10132002
            termType = 5                      'added 10132002
            locate_data_tbl                   'added 10132002
            se.de_no = term_tbl_no            'added 10132002
            term = saveTerm1013               'added 10132002
            termType = saveTermType1013       'added 10132002

  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  If itsAVarname = False Then
    se.termType = 6
    se.maj = "d"
    se.term = str$(controlId)
    saveTerm1013 = term               'added 10132002
    saveTermType1013 = termType       'added 10132002
    term = se.term                    'added 10132002
    termType = 6                      'added 10132002
    strip_and_locate_data_tbl                  'added 10132002
    se.de_no = term_tbl_no            'added 10132002
    term = saveTerm1013               'added 10132002
    termType = saveTermType1013       'added 10132002
  Else
    se.termType = 4
    se.maj = "d"
    se.term = saveObjName
    se.de_no = saveTblNo
    se.sub1 = 0
    se.sub2 = 0
    se.sub3 = 0
  End If
  
  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  se.termType = 6
  se.maj = "d"
  se.term = str$(propId)
  saveTerm1013 = term               'added 10132002
  saveTermType1013 = termType       'added 10132002
  term = se.term                    'added 10132002
  termType = 6                      'added 10132002
  strip_and_locate_data_tbl                   'added 10132002
  se.de_no = term_tbl_no            'added 10132002
  term = saveTerm1013               'added 10132002
  termType = saveTermType1013       'added 10132002
End Sub
'entire routine added 08222002
Sub substGeneralVerb(controlId, verbId As Integer)
   Dim x As CSynElem
   Dim saveSe As CSynElem          'added 09092002
   
   Set saveSe = se                'added 09092002
  se.termType = 2                 'changed 09092002
  se.maj = "z"
  se.term = "generalverb"
  se.sub1 = 0
 
  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  se.termType = 5
  se.maj = "d"
  If itsAVarname = False Then
       se.term = "i"  'indic its by control id
  Else
       se.term = "v"   'indic its by varname
  End If
  
            saveTerm1013 = term               'added 10132002
            saveTermType1013 = termType       'added 10132002
            term = se.term                    'added 10132002
            termType = 5                      'added 10132002
            locate_data_tbl                   'added 10132002
            se.de_no = term_tbl_no            'added 10132002
            term = saveTerm1013               'added 10132002
            termType = saveTermType1013       'added 10132002
  
  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  If itsAVarname = False Then
    se.termType = 6
    se.maj = "d"
    se.term = str$(controlId)
    saveTerm1013 = term               'added 10132002
    saveTermType1013 = termType       'added 10132002
    term = se.term                    'added 10132002
    termType = 6                      'added 10132002
    strip_and_locate_data_tbl                   'added 10132002
    se.de_no = term_tbl_no            'added 10132002
    term = saveTerm1013               'added 10132002
    termType = saveTermType1013       'added 10132002
  Else
    se.termType = 4
    se.maj = "d"
    se.term = saveObjName
    se.de_no = saveTblNo
    se.sub1 = 0
    se.sub2 = 0
    se.sub3 = 0
  End If
  
  Set x = New CSynElem
  addSynElemAfterSE x
  Set se = se.Nxt
  se.termType = 6
  se.maj = "d"
  se.term = str$(verbId)
  saveTerm1013 = term               'added 10132002
  saveTermType1013 = termType       'added 10132002
  term = se.term                    'added 10132002
  termType = 6                      'added 10132002
  strip_and_locate_data_tbl                   'added 10132002
  se.de_no = term_tbl_no            'added 10132002
  term = saveTerm1013               'added 10132002
  termType = saveTermType1013       'added 10132002
  
  '09092002 Set se = saveSe               'added 09092002
  
''compiler_debug = True 'temporary
''dbugDump             'temporary
End Sub
'08222002 added entire routine
Sub addSynElemAfterSE(x As CSynElem)
  Set x.Prev = se
  Set x.Nxt = se.Nxt
  If Not se.Nxt Is se_null_ptr Then
    Set se.Nxt.Prev = x
  End If
  Set se.Nxt = x
 End Sub

'06102002 inserted entire subroutine
Sub substituteverb(verb As String, method As String)

  Dim temp2 As New CSynElem
  Dim temp3 As New CSynElem
  Dim temp4 As New CSynElem
  
   se.termType = 2 'verb
   se.term = verb
   se.termin = " "
   se.maj = "z"
   se.sub1 = 0
   
   If Not se.Nxt Is se_null_ptr Then
     If se.Nxt.maj = "p" And se.Nxt.sub1 = 0 Then
        GoTo parenAlready
     End If
   End If
   'put in paren,objname,and paren
   
   temp2.maj = "p"
   temp2.sub1 = 0 'left paren
   temp2.posInInput = se.posInInput

   temp3.term = method
   temp3.termType = 5
   term = temp3.term
   termType = 5 'alphalit
   locate_data_tbl
 
   temp3.de_no = data.tbl_no
   temp3.maj = "d"
   
   temp3.sub1 = 0
   temp3.sub2 = 0
   temp3.sub3 = 0
   temp3.posInInput = se.posInInput
   
   
   temp4.maj = "p"
   temp4.sub1 = 1 'right paren
   temp4.posInInput = se.posInInput

   If Not se.Nxt Is Nothing Then

       Set se.Nxt.Prev = temp4
   End If

   Set temp4.Nxt = se.Nxt
   Set temp4.Prev = temp3
   Set temp3.Nxt = temp4
   Set temp3.Prev = temp2
   Set temp2.Nxt = temp3
   Set temp2.Prev = se
   
   Set se.Nxt = temp2

   Exit Sub
parenAlready:
   Set se = se.Nxt
   
   temp3.term = method
   temp3.termType = 5
   term = temp3.term
   termType = 5 'alphalit
   locate_data_tbl
   temp3.de_no = data.tbl_no
   temp3.maj = "d"
   temp3.sub1 = 0
   temp3.sub2 = 0
   temp3.sub3 = 0
   
   If Not se.Nxt Is Nothing Then
      Set se.Nxt.Prev = temp3
   End If
   Set temp3.Nxt = se.Nxt
   Set temp3.Prev = se
   Set se.Nxt = temp3
End Sub

'06102002 end of inserted statements
Sub substituteInsert(verb As String)
   Dim temp As New CSynElem
   
      
   temp.term = verb
   temp.termType = 7
   
   
   temp.maj = "z"
   temp.de_no = 0
   temp.sub1 = 0
   temp.sub2 = 0
   temp.sub3 = 0
   temp.posInInput = se.posInInput
   If Not se.Nxt Is Nothing Then
      Set se.Nxt.Prev = temp
   End If
   Set temp.Nxt = se.Nxt
   Set temp.Prev = se
   Set se.Nxt = temp
   

End Sub
Sub substitute2for2(verb As String, obj As String)
  
   'entry was of the form obj.prop = value
   se.termType = 2 'verb
   se.term = verb
   se.termin = " "
   
   se.Nxt.term = obj
   se.Nxt.termType = 5
   term = se.Nxt.term
   termType = 5 'alphalit
   locate_data_tbl
   se.Nxt.maj = "d"
   se.Nxt.termType = 5
   se.Nxt.de_no = term_tbl_no
   se.Nxt.sub1 = 0
   se.Nxt.sub2 = 0
   se.Nxt.sub3 = 0
   
End Sub
Sub substitute2for1(verb As String, obj As String)
   Dim temp As New CSynElem
   
   se.termType = 2 'verb
   se.term = verb
   se.termin = " "
   
   temp.term = obj
   temp.termType = 5
   term = temp.term
   termType = 5 'alphalit
   locate_data_tbl
   temp.maj = "d"
   temp.de_no = term_tbl_no
   temp.sub1 = 0
   temp.sub2 = 0
   temp.sub3 = 0
   temp.posInInput = se.posInInput
   If Not se.Nxt Is se_null_ptr Then
     Set se.Nxt.Prev = temp
   End If
   Set temp.Nxt = se.Nxt
   Set temp.Prev = se
   Set se.Nxt = temp
End Sub
Sub substituteExternal(libID As Integer, procid As Integer, numArgs As Integer, retType As String)
' EMP overhauled
' DIKEO eliminate array if possible
'Sub substituteExternal(libname As String, libid As Integer, procname As String, _
'                       procid As Integer)

   Dim seTemp(60) As New CSynElem
   Dim curSE As Integer
   Dim maxSE As Integer
   Dim bIsProc As Boolean
   Dim oTemp As Object
   Dim arg As Integer
   Dim parenAlready As Boolean
   Dim argStart As Integer
   Dim wantsContext As Boolean
      
   If se Is first_se Then
      se.term = "ExternalSub"
      se.termType = gcTYPE_VERB
      se.maj = "z"
      bIsProc = True
      argStart = 0
   Else
      se.term = "ExternalFunc"
      se.termType = gcTYPE_FUNC
      se.maj = funcName '?? = "f"
      se.sub1 = 599
      bIsProc = False
      argStart = 2
   End If
   se.termin = " "
      
   maxSE = 0
   
   parenAlready = False
   If Not se.Nxt Is Nothing Then
     If se.Nxt.maj = "p" And se.Nxt.sub1 = 0 Then
        parenAlready = True
        Set se = se.Nxt 'past the parenthesis
     End If
   End If
   
   If (Not parenAlready) Then
     ' Open paren
     maxSE = maxSE + 1
     seTemp(maxSE).term = "("
     seTemp(maxSE).maj = "p"
     seTemp(maxSE).sub1 = 0 'left paren
     seTemp(maxSE).posInInput = se.posInInput
   End If
   
   wantsContext = False
   
   If (retType <> "") Then
     If Mid$(retType, 1, 2) = "xx" Then
        wantsContext = True
        retType = Mid$(retType, 3)
     End If
   End If
   
   
   ' Library ID
   maxSE = maxSE + 1
   seTemp(maxSE).term = Trim$(str$(libID))
   seTemp(maxSE).termType = gcTYPE_CONSTANT
   seTemp(maxSE).maj = "d"
   seTemp(maxSE).sub1 = libID
   If (wantsContext) Then
     seTemp(maxSE).sub2 = 1
   Else
     seTemp(maxSE).sub2 = 0
   End If
   seTemp(maxSE).sub3 = 0
   seTemp(maxSE).posInInput = se.posInInput

   ' Procedure ID
   maxSE = maxSE + 1
   seTemp(maxSE).term = Trim$(str$(procid))
   seTemp(maxSE).termType = gcTYPE_CONSTANT
   seTemp(maxSE).maj = "d"
   seTemp(maxSE).sub1 = procid
   If (retType = "") Then
      seTemp(maxSE).sub2 = 0
      seTemp(maxSE).sub3 = 0
   Else
     If (Mid$(retType, 1, 2) = "  ") Then
       seTemp(maxSE).sub2 = 0
       seTemp(maxSE).sub3 = 0
     Else
        If (bIsProc) Then
            If (retType = "") Then
                ' It's an old-style proc, or a proc without arguments, just the same
                seTemp(maxSE).sub2 = 0
                seTemp(maxSE).sub3 = 0
            Else
                ' A new style proc, put anything in there but zero for the parser
                seTemp(maxSE).sub2 = Asc("X")
                seTemp(maxSE).sub3 = 4
            End If
        Else
            seTemp(maxSE).sub2 = Asc(Mid$(retType, 1, 1))
            seTemp(maxSE).sub3 = Asc(Mid$(retType, 2, 1)) - Asc("0")
        End If
     End If
   End If
   seTemp(maxSE).posInInput = se.posInInput  '??

   ' Number of args
   maxSE = maxSE + 1
   seTemp(maxSE).term = Trim$(str$(numArgs))
   seTemp(maxSE).termType = gcTYPE_CONSTANT
   seTemp(maxSE).maj = "d"
   seTemp(maxSE).sub1 = numArgs
   seTemp(maxSE).sub2 = 0
   seTemp(maxSE).sub3 = 0
   seTemp(maxSE).posInInput = se.posInInput
   
   If ((Not (retType = "")) And numArgs > 0) Then
     ' Emit a token for the type and size of each arg
     For arg = 1 To numArgs
       maxSE = maxSE + 1
       seTemp(maxSE).term = "arg" + Trim$(str$(numArgs))
       seTemp(maxSE).termType = gcTYPE_CONSTANT
       seTemp(maxSE).maj = "d"
       seTemp(maxSE).sub1 = 0 'What's with this?
       seTemp(maxSE).sub2 = Asc(Mid$(retType, arg * 2 + argStart - 1, 1))
       seTemp(maxSE).sub3 = Asc(Mid$(retType, arg * 2 + argStart, 1)) - Asc("0")
       seTemp(maxSE).posInInput = se.posInInput
     Next arg
     
   End If
   
   If (Not parenAlready) Then
   ' Close parenthesis
   maxSE = maxSE + 1
   seTemp(maxSE).term = "("
   seTemp(maxSE).maj = "p"
   seTemp(maxSE).sub1 = 1 'right paren
   seTemp(maxSE).posInInput = se.posInInput
   End If

   ' Link them together
    curSE = 1
    If Not se.Nxt Is Nothing Then Set se.Nxt.Prev = seTemp(curSE)
    Set seTemp(curSE).Nxt = se.Nxt
    Set seTemp(curSE).Prev = se
    Set se.Nxt = seTemp(curSE)
    
    For curSE = 2 To maxSE
      If Not seTemp(curSE - 1).Nxt Is Nothing Then Set seTemp(curSE - 1).Nxt.Prev = seTemp(curSE)
      Set seTemp(curSE).Nxt = seTemp(curSE - 1).Nxt
      Set seTemp(curSE).Prev = seTemp(curSE - 1)
      Set seTemp(curSE - 1).Nxt = seTemp(curSE)
    Next curSE

End Sub
Sub substituteFunc(verb As String, obj As String, funcNo As Integer)

  Dim temp2 As New CSynElem
  Dim temp3 As New CSynElem
  Dim temp4 As New CSynElem
  
   se.termType = FUNCTYPE 'function
   se.term = verb
   se.termin = " "
   se.maj = funcName
   se.sub1 = funcNo
   
   If Not se.Nxt Is Nothing Then
     If se.Nxt.maj = "p" And se.Nxt.sub1 = 0 Then
        GoTo parenAlready
     End If
   End If
   'put in paren,objname,and paren
   'temp2.termType = 7
   temp2.maj = "p"
   temp2.sub1 = 0 'left paren
   temp2.posInInput = se.posInInput

   temp3.term = obj
   temp3.termType = 5
   term = temp3.term
   termType = 5 'alphalit
   locate_data_tbl
 
   temp3.maj = "d"
   temp3.de_no = term_tbl_no
   temp3.sub1 = 0
   temp3.sub2 = 0
   temp3.sub3 = 0
   temp3.posInInput = se.posInInput
   
   'temp4.termType = 7
   temp4.maj = "p"
   temp4.sub1 = 1 'right paren
   temp4.posInInput = se.posInInput
   
   If Not se.Nxt Is Nothing Then
     Set se.Nxt.Prev = temp4
   End If
   Set temp4.Nxt = se.Nxt
   Set temp4.Prev = temp3
   Set temp3.Nxt = temp4
   Set temp3.Prev = temp2
   Set temp2.Nxt = temp3
   Set temp2.Prev = se
   
   Set se.Nxt = temp2
   Exit Sub
parenAlready:
   Set se = se.Nxt
   
   temp3.term = obj
   temp3.termType = 5
   term = temp3.term
   termType = 5 'alphalit
   locate_data_tbl
   temp3.maj = "d"
   temp3.de_no = term_tbl_no
   temp3.sub1 = 0
   temp3.sub2 = 0
   temp3.sub3 = 0
   
   If Not se.Nxt Is Nothing Then
      Set se.Nxt.Prev = temp3
   End If
   Set temp3.Nxt = se.Nxt
   Set temp3.Prev = se
   Set se.Nxt = temp3
End Sub
Sub build_next_se()        '/*------bld a single syn elem entry-----*/
    Dim pno As Integer
    Dim temp As CSynElem
    Set temp = New CSynElem
   
    If (se Is se_null_ptr) Then
        Set first_se = temp
        Set temp.Prev = se_null_ptr
    Else
        Set se.Nxt = temp
        Set temp.Prev = se
    End If
    Set temp.Nxt = se_null_ptr
    Set se = temp
    get_stmt_elem
If compiler_debug Then
   dbug "got stmt elem=" + term + " termType=" + str$(termType)
End If
    se.posInInput = thisTermStart
    se.term = term
    se.termType = termType
    se.termin = termin
    If termin = "(" Or termin = ")" Then se.termin = " "
    
    If term = "_end-line" Then
       bld_at_end
    ElseIf ((termType = 5) Or (termType = 1) Or (termType = 6)) Then
        bld_const
    ElseIf termType = 13 Then
        bld_dbname
    ElseIf (termType = FUNCTYPE) Then
        bld_function
    ElseIf (termType = 2) Then
        bld_verb
    ElseIf (term_is("(")) Then
       bld_left_paren
    ElseIf (term_is(")")) Then
       bld_right_paren
    ElseIf (term_is("+")) Then
       bld_plus
    ElseIf (term_is("-")) Then
       bld_minus
    ElseIf (term_is("*")) Then
       bld_mult
    ElseIf (term_is("/")) Then
       bld_div
    ElseIf (term_is("^")) Then
       bld_expon
    ElseIf (term_is("<")) Then
       bld_less
    ElseIf ((term_is("<=")) Or (term_is("=<"))) Then
      bld_less_equal
    ElseIf (term_is(">")) Then
      bld_greater
    ElseIf ((term_is(">=")) Or (term_is("=>"))) Then
      bld_greater_equal
    ElseIf ((term_is("<>")) Or (term_is("><"))) Then 'this never happens - GH
      bld_unequal
    ElseIf (term_is("=")) Then
      bld_equal
    ElseIf (term_is("or")) Then
      bld_or
    ElseIf (term_is("and")) Then
      bld_and
    ElseIf (term_is("not")) Then
      bld_not
    ElseIf ((term_is("on")) Or (term_is("while")) _
       Or (Mid$(term, 1, 1) = " ")) Then
       bld_verb
       Exit Sub
    
    ElseIf (term_is(",")) Then
      bld_comma
    ElseIf (termType = 4) Or termType = 5 Or termType = 6 Then
      bld_dname
    ElseIf (termType = 3) Or termType = 7 Then  '06102002 changed
       bld_reserved
    Else
'dbug "err in build_syn_elem ---" + term
      print_err gStringTable(3363) + "'" + term + "'" 'Can't recognize term:   'changed 06102002
      repeat_sw = 0
    End If
End Sub
Sub bld_reserved()
  se.maj = "@"
  se.de_no = 0
  se.sub1 = 0
End Sub
Sub bld_dbname()
'sgBox "at bld_dbname"
  se.maj = "&"
  se.de_no = dbNumber
End Sub
Sub bld_function()
    se.maj = funcName
    se.sub1 = func_type
    Exit Sub
End Sub
Sub bld_left_paren()
    se.maj = "p"
    se.sub1 = 0
    Exit Sub
End Sub

Sub bld_right_paren()
    se.maj = "p"
    se.sub1 = 1
    Exit Sub
End Sub
Sub bld_plus()
    se.maj = "a"
    se.sub1 = 1
    Exit Sub
End Sub
Sub bld_minus()
    se.maj = "a"
    se.sub1 = 2
    Exit Sub
End Sub
Sub bld_mult()
    se.maj = "a"
    se.sub1 = 3
    Exit Sub
End Sub
Sub bld_div()
    se.maj = "a"
    se.sub1 = 4
    Exit Sub
End Sub
Sub bld_expon()
    se.maj = "a"
    se.sub1 = 5
    Exit Sub
End Sub
Sub bld_less()
    Dim temp As CSynElem
    If Not se.Prev Is se_null_ptr Then
      Set temp = se.Prev
      If temp.maj = "r" And temp.sub1 = 3 Then 'make <=
         temp.sub1 = 5
         release_syn_elem
         Exit Sub
      End If
      If temp.maj = "r" And temp.sub1 = 2 Then 'make ><
         temp.sub1 = 6
         release_syn_elem
         Exit Sub
      End If
    End If
    se.maj = "r"
    se.sub1 = 1
    Exit Sub
End Sub
Sub bld_less_equal()
    se.maj = "r"
    se.sub1 = 5   '/*same as NOT >  */
    Exit Sub
End Sub
Sub bld_greater()
    Dim temp As CSynElem
    If Not se.Prev Is se_null_ptr Then
      Set temp = se.Prev
      If temp.maj = "r" And temp.sub1 = 3 Then 'make >=
         temp.sub1 = 4
         release_syn_elem
         Exit Sub
      End If
      If temp.maj = "r" And temp.sub1 = 1 Then 'make <>
         temp.sub1 = 6
         release_syn_elem
         Exit Sub
      End If
    End If
    se.maj = "r"
    se.sub1 = 2
    Exit Sub
End Sub
Sub bld_greater_equal()
    
    se.maj = "r"
    se.sub1 = 4 '/*same as NOT < */
    Exit Sub
End Sub
Sub bld_exceeds()
    se.maj = "r"
    se.sub1 = 2
    Exit Sub
End Sub
Sub bld_equal()
    Dim temp As CSynElem
    If Not se.Prev Is se_null_ptr Then
      Set temp = se.Prev
      If temp.maj = "r" And temp.sub1 = 1 Then 'make <=
         temp.sub1 = 5
         release_syn_elem
         Exit Sub
      End If
      If temp.maj = "r" And temp.sub1 = 2 Then 'make >=
         temp.sub1 = 4
         release_syn_elem
         Exit Sub
      End If
    End If
    se.maj = "r"
    se.sub1 = 3
    Exit Sub
End Sub
Sub bld_unequal() 'I don't think this is used. GH
    se.maj = "r"
    se.sub1 = 6
    'get_term
    '/*"to"*/
    ' If (term_is("to")) Then
    'Else
      'term_used = 0
    'End If
    Exit Sub
End Sub
Sub bld_less_than()
    get_term
    '/*"than"*/
    If (term_not("than")) Then term_used = 0
    bld_less
    Exit Sub
End Sub
Sub bld_greater_than()
    get_term
    '/*"than"*/
    If (term_not("than")) Then term_used = 0
    bld_greater
    Exit Sub
End Sub
Sub bld_is()
    get_term
    If ((term_is("less")) Or _
    (term_is("greater")) Or _
    (term_is("not")) Or _
    (term_is("positive")) Or _
    (term_is("negative")) Or _
    (term_is("unequal")) Or _
    (term_is("zero")) Or _
    (term_is(">")) Or _
    (term_is("<")) Or _
    (term_is("=")) Or _
    (term_is("equal")) Or _
    (term_is("numeric")) Or _
    (term_is("alphabetic"))) Then
      term_used = 0
      release_syn_elem
      Exit Sub
    End If
    SYNTAX 99
    repeat_sw = 0
    Exit Sub
End Sub
Sub bld_comma()
    release_syn_elem
    Exit Sub
End Sub
Sub bld_or()
    se.maj = "l"
    se.sub1 = 1
    Exit Sub
End Sub
Sub bld_and()
    se.maj = "l"
    se.sub1 = 2
    Exit Sub
End Sub
Sub bld_not()
    se.maj = "l"
    se.sub1 = 3
    Exit Sub
End Sub

Sub bld_zero()
    Dim temp As CSynElem

    '/* if "zero" not preceeded by "=" ">" "<"      then bld it */
    Set temp = se.Prev
    If (Not temp Is se_null_ptr) Then
        If (Not temp.maj = "r") Then
          se.maj = "r"   '/*put in an = operator */
          se.sub1 = 3
          term_used = 0   '/*will reget "zero" */
          Exit Sub
        End If
    End If


    bld_const    '/* now put zero in as a constant */
    Exit Sub
End Sub
Sub bld_equal_to()
    get_term
    '/*"to"*/
    If (term_not("to")) Then term_used = 0
    bld_equal
    Exit Sub
End Sub
Sub bld_dname()
    Dim pno As Integer
   
    pno = locate_link_tbl
    If Not pno = 0 Then
         If Not p.ptype = "f" Then
            'subrtn name
            se.maj = "?"
            se.de_no = pno
            se.sub1 = 0
            se.sub2 = 0
            se.sub3 = 0
            'se.rel = 0
            'se.relno = 0
            Exit Sub
         Else
            
            '06102002 If se.prev Is se_null_ptr Then
            '06102002       get_stmt_elem
            '06102002       If Not term_is("(") Then
            '06102002           term_used = 0
            '06102002           GoTo notFunc
            '06102002       Else
            '06102002           print_err "Must assign a function result to a variable name."
            '06102002       End If
            '06102002 End If
            If p.name_ptr = LastSubFuncParsed Then     'added 06102002
               If Not termin = "(" Then GoTo notFunc    'added 06102002
            End If                                      'added 06102002
userFunc:
            'user_func
            se.maj = "u"
            se.de_no = pno
            se.sub1 = 0
            se.sub2 = 0
            se.sub3 = 0
            'se.rel = 0
            'se.relno = 0
            Exit Sub
         End If
    End If
    
notFunc:
    If (locate_data_tbl()) = 1 Then
itsDataelem:
      If data.max_no_values1 > 1 Then
        se.maj = "y"  'needs subscripts
      Else
        se.maj = "d"
      End If
      se.de_no = term_tbl_no
      se.sub1 = 0  '!!
      se.sub2 = 0
      se.sub3 = 0
      
    Else
'sgBox "setting * for se.term=" + se.term
       Set data = locateDataByName(">>" + term)
       If Not data Is Nothing Then
         term_tbl_no = data.tbl_no
         GoTo itsDataelem
       Else
         se.maj = "*"
         se.sub1 = 0
         se.sub2 = 0
         se.sub3 = 0
       End If
     End If
End Sub
Sub bld_const()
    
    locate_data_tbl
    se.maj = "d"
    se.de_no = term_tbl_no
    se.sub1 = 0
    se.sub2 = 0
    se.sub3 = 0
    
End Sub

Sub bld_verb()
    se.maj = "z"
    se.sub1 = 0
    se.sub2 = 0
    se.sub3 = 0
 End Sub
 Sub bld_at_end()
    release_syn_elem
    repeat_sw = 0
    Exit Sub
End Sub
Sub release_syn_elem()
    Dim temp As CSynElem
    Dim Nxt As CSynElem
    
    Set temp = se.Prev
    Set Nxt = se.Nxt
    
    
    If (temp Is se_null_ptr) Then
      Set first_se = se_null_ptr
      Set se = se_null_ptr
    Else
      Set se = temp
      Set se.Nxt = Nxt
    End If
    If (Nxt Is se_null_ptr) Then
    Else: Set Nxt.Prev = temp
    End If
    
    
End Sub
Sub delete_syn_elem(temp As CSynElem)       '/*----delete an elem in list------*/
    Dim bak As CSynElem
    Dim fwd As CSynElem
'dbug "deleting synelem=" + temp.term
'dbug "deleting se=" + temp.term + " first=" + first_se.term _
'+ " prev=" + temp.prev.term + " nxt=" + temp.nxt.term
    Set bak = temp.Prev
    Set fwd = temp.Nxt
    If (Not bak Is se_null_ptr) Then Set bak.Nxt = temp.Nxt
    If (Not fwd Is se_null_ptr) Then Set fwd.Prev = temp.Prev
    
    If (bak Is se_null_ptr) Then
      If (fwd Is se_null_ptr) Then
        Set first_se = se_null_ptr
      Else
        Set first_se = fwd
      End If
    End If
'dbug "after deleting first_se=" + first_se.term + " se=" + se.term _
'+ " prev=" + se.prev.term + " nxt=" + se.nxt.term

End Sub


Sub insert_syn_elem_before() '/*put new elem before current one*/
    Dim temp As CSynElem
    Set temp = New CSynElem
    If (se Is first_se) Then
      Set first_se = temp
      Set temp.Prev = se_null_ptr
    Else
      Set se.Prev.Nxt = temp
      Set temp.Prev = se.Prev
    End If
    Set temp.Nxt = se
    Set se.Prev = temp
    Set se = temp
    Exit Sub
End Sub
Sub insert_syn_elem_after() '/*put new elem after  current one*/
    Dim temp As CSynElem
    Set temp = New CSynElem
    If (se.Nxt Is se_null_ptr) Then
    Else
      Set se.Nxt.Prev = temp
    End If
    Set temp.Nxt = se.Nxt
    Set temp.Prev = se
    Set se.Nxt = temp
    Set se = temp
    Exit Sub
End Sub

Public Sub logic_exp_gen()
    Set se = first_se
    If se.Nxt Is se_null_ptr Then SYNTAX 100
 If compiler_debug Then
 dbugDump
 End If
    If se.term = "if" Then se = se.Nxt 'sitting on
    If se.Nxt Is se_null_ptr Then SYNTAX 101
    If se.Nxt.term = "then" Then SYNTAX 102
    arith_scan_all        '/* first gen code for arith expres */
    logic_compress_expand   '/*elim nots & implied opers */if se.maj
    logic_scan_all          '/* then gen logic code */
    Set se = first_se
    
End Sub
Sub logic_scan_all()        '/* scan entire syn elem list */
restart_logic_scan:
    logic_stat = 1
logic_scan_again:
    Set se = first_se
    paren_cnt = 0
    Do
      logic_scan_for_exp
    Loop While (Not se Is se_null_ptr)
    If (logic_stat = 99) Then GoTo restart_logic_scan
    If (logic_stat < 8) Then
       logic_stat = logic_stat + 1
       GoTo logic_scan_again
    End If
    Exit Sub
End Sub
Sub logic_scan_for_exp()  '/* scan from se to begin expres */
    Dim temp As CSynElem
    Set temp = se_null_ptr
'sgBox "at scan maj=" + se.maj
    If ((se.maj = "p") And (se.sub1 = 0)) Then '/*left paren */
      paren_cnt = paren_cnt + 1
      Set se = se.Nxt
      Exit Sub
    End If
    If ((se.maj = "p") And (se.sub1 = 1)) Then '/*rt paren */
      If (paren_cnt = 0) Then
        logic_syntax_err
      End If
      paren_cnt = paren_cnt + 1
    '/**/
      If (Not se.Prev Is se_null_ptr) Then        '/*remove parens*/
        Set temp = se.Prev
        If (temp.maj = "v") Then
          If (Not temp.Prev Is se_null_ptr) Then
            Set temp = temp.Prev
            If ((temp.maj = "p") And (temp.sub1 = 0)) Then
              delete_syn_elem temp
              Set temp = se
              Set se = temp.Prev
              delete_syn_elem temp
              logic_stat = 99
              Set se = se_null_ptr
              Exit Sub
            End If
          End If
        End If
      End If
      Set se = se.Nxt
      Exit Sub
    End If
    If ((se.maj = "l") And (se.sub1 = 3)) Then '/*not*/
      If (logic_stat = 6) Then
        If (Not se.Nxt Is se_null_ptr) Then
          Set temp = se.Nxt
          If (temp.maj = "v") Then
            gen_not_logic
            Exit Sub
          End If
        End If
      End If
    End If

    If (se.maj = "d") Then   '/* data name */
      If (logic_stat = 1) Then
        If (Not se.Nxt Is se_null_ptr) Then
          Set temp = se.Nxt
          If (temp.maj = "r") Then '/*relat operator*/
            If (Not temp.Nxt Is se_null_ptr) Then
              Set temp = temp.Nxt
              If (temp.maj = "d") Then
                gen_relational_logic
                Exit Sub
              End If
            End If
          End If
        End If
      End If
    End If
    If (se.maj = "d") Then
      If (logic_stat = 2) Then
        If (Not se.Nxt Is se_null_ptr) Then
          Set temp = se.Nxt
          If (temp.maj = "c") Then '/*class tests*/
            gen_logic_class_tests
            Exit Sub
          End If
        End If
      End If
    End If
    'test for and
    If (((se.maj = "l") And (se.sub1 = 2) And (logic_stat = 7)) _
    Or ((se.maj = "l") And (se.sub1 = 1) And (logic_stat = 8))) Then
      If (Not se.Prev Is se_null_ptr) Then
        Set temp = se.Prev
        If (temp.maj = "v") Then
          If (Not se.Nxt Is se_null_ptr) Then
            Set temp = se.Nxt
            If (temp.maj = "v") Then
              gen_logic_and_or
              Exit Sub
            End If
          End If
        End If
      End If
    End If
    
    Set se = se.Nxt
End Sub
Sub logic_insert_subj_oper()     '/*insert implied subj+oper */
    logic_insert_subject
    logic_insert_an_elem (oper_se)
    Exit Sub
End Sub
Sub logic_insert_subject()        '/*insert implied relat subject */
    logic_insert_an_elem (subj_se)
    Exit Sub
End Sub
Sub logic_insert_an_elem(copy_se As CSynElem)  '/*insert a copy of elem into list */
    Dim temp As CSynElem
    Set temp = New CSynElem
    If (se Is first_se) Then
      Set first_se = temp
    Else:
      Set se.Prev.Nxt = temp
    End If
    Set temp.Prev = se.Prev
    Set temp.Nxt = se
    temp.maj = copy_se.maj
    temp.de_no = copy_se.de_no
    temp.sub1 = copy_se.sub1
    temp.sub2 = copy_se.sub2
    temp.sub3 = copy_se.sub3
    
    Set se.Prev = temp
    Exit Sub
End Sub
Sub logic_syntax_err()
    SYNTAX 103
    Set se = se_null_ptr
    Exit Sub
End Sub
'/*         this rtn 1.combines "not" in form not =,not <,not>    */
'/*                                 to become one operator.        */
'/*                  2.fills in implied vars & opers               */
'/**/
Sub logic_compress_expand()
    Dim temp As CSynElem
    Set temp = se_null_ptr
    Set se = first_se
    Do While (Not se Is se_null_ptr)
       '/*first elim not"s */
      If ((se.maj = "l") And (se.sub1 = 3)) Then '/*not*/
        If (Not se.Nxt Is se_null_ptr) Then
          Set temp = se.Nxt
          If (temp.maj = "r") Then
            If ((temp.sub1 > 0) And (temp.sub1 < 4)) Then
              temp.sub1 = temp.sub1 + 3
              delete_syn_elem se
              Set se = temp
            End If
          Else
            If (temp.maj = "c") Then
              If ((temp.sub1 > 0) And (temp.sub1 < 6)) Then
                temp.sub1 = temp.sub1 + 5
                delete_syn_elem se
                Set se = temp
              End If
            End If
          End If
        End If
      End If
      Set se = se.Nxt
    Loop
    Set se = first_se
    Do While (Not se Is se_null_ptr)     '/*elim implied opers */
      Set subj_se = se
      If (se.maj = "d") Then
        If (Not se.Nxt Is se_null_ptr) Then
          Set se = se.Nxt
          If (se.maj = "r") Then
            Set oper_se = se
            If (Not se.Nxt Is se_null_ptr) Then
              Set se = se.Nxt
              If (se.maj = "d") Then
                If (Not se.Nxt Is se_null_ptr) Then
                  Set se = se.Nxt
                  If (se.maj = "l") Then
                    If ((se.sub1 = 1) Or (se.sub1 = 2)) Then
                      If (Not se.Nxt Is se_null_ptr) Then
                        Set se = se.Nxt
                        If (se.maj = "r") Then
                          logic_insert_subject
                          GoTo backup_1_se
                        Else
                          If (se.maj = "d") Then
                            If (se.Nxt Is se_null_ptr) Then
                              logic_insert_subj_oper
                              GoTo backup_2_se
                            Else
                              Set temp = se.Nxt
                              If ((temp.maj = "p") Or _
                                (temp.maj = "l")) Then
                                 logic_insert_subj_oper
                                 GoTo backup_2_se
                              End If
                            End If
                          Else
                            If ((se.maj = "l") And _
                            (se.sub1 = 3)) Then
                              If (Not se.Nxt Is se_null_ptr) Then
                                Set se = se.Nxt
                                If (se.maj = "d") Then
                                  If (se.Nxt Is se_null_ptr) Then
                                    logic_insert_subj_oper
                                    GoTo backup_2_se
                                  Else
                                    Set temp = se.Nxt
                                    If ((temp.maj = "p") Or _
                                    (temp.maj = "l")) Then
                                      logic_insert_subj_oper
                                      GoTo backup_2_se
                                     End If
                                   End If
                                 End If
                               End If
                             End If
                           End If
                         End If
                       End If
                     End If
                    
                   End If
                 End If
               End If
             End If
           End If
         End If
       End If
      Set se = subj_se.Nxt
      GoTo repeat_again
backup_2_se:
      Set se = se.Prev
backup_1_se:
      Set se = se.Prev
repeat_again:
    Loop
    Exit Sub
End Sub
Sub gen_not_logic()            '/* not condition */
    Dim temp As CSynElem
    Set temp = se.Nxt
    arg_1 = temp.de_no
    arg1_occ1 = 0
    arg1_occ2 = 0
    arg1_occ3 = 0
    gen_alloc_log_work
    out_one_char (&H51)
    out_one_integ (arg_1)  '/*will be a log var #*/
    out_one_integ (log_work_var_no)
    delete_syn_elem se
    Set se = temp
    se.maj = "v"
    se.de_no = log_work_var_no
    Exit Sub
End Sub
Sub gen_relational_logic()     '/*relational logic tests */
    Dim wk_s As String
    Dim b As CSynElem
    Dim c As CSynElem
    Set b = se.Nxt
    Set c = b.Nxt
    arg_1 = se.de_no
    arg1_occ1 = se.sub1
    arg1_occ2 = se.sub2
    arg1_occ3 = se.sub3
    
    
    arg_2 = c.de_no
    arg2_occ1 = c.sub1
    arg2_occ2 = c.sub2
    arg2_occ3 = c.sub3
    
   
    Select Case (b.sub1)
    Case 1
      arg_3 = 2
    Case 2
      arg_3 = 1
    Case 3
      arg_3 = 0
    Case 4
      arg_3 = 5
    Case 5
      arg_3 = 4
    Case 6
      arg_3 = 3
    End Select
    out_tok_2arg (&H52)
    out_one_integ (arg_3)
    gen_alloc_log_work
    out_one_integ (log_work_var_no)
    delete_syn_elem se
    delete_syn_elem b
    Set se = c
    se.maj = "v"
    se.de_no = log_work_var_no
    Exit Sub
End Sub
Sub gen_logic_class_tests()
    Dim the_byte As Byte
    Dim b As CSynElem
    Set b = se.Nxt
    arg_1 = se.de_no
    arg1_occ1 = se.sub1
    arg1_occ2 = se.sub2
    arg1_occ3 = se.sub3
    
    
    Select Case (b.sub1)
    Case 1
    arg_2 = 14
    Case 2
    arg_2 = 16
    Case 3
    arg_2 = 18
    Case 4
    arg_2 = 12
    Case 5
    arg_2 = 10
     '/* alphab*/"
    Case 6
    arg_2 = 15
     '/* not pos */"
    Case 7
    arg_2 = 17
     '/* not neg */"
    Case 8
    arg_2 = 19
     '/* not zero*/"
    Case 9
    arg_2 = 13
     '/* not numer */"
    Case 10
    arg_2 = 11
     '/* not alphab*/"
    End Select
    out_tok_1arg (&H53)
    the_byte = arg_2
    out_one_char (the_byte)
    gen_alloc_log_work
    out_one_integ (log_work_var_no)
    delete_syn_elem se
    Set se = b
    se.maj = "v"
    se.de_no = log_work_var_no
    Exit Sub
End Sub
Sub gen_logic_and_or()
    Dim a As CSynElem
    Dim c As CSynElem
    Set a = se.Prev
    Set c = se.Nxt
    If (se.sub1 = 1) Then
       out_one_char (&H55) '/* or  */
    Else:
       out_one_char (&H54)
    End If '/* and */
    out_one_integ (a.de_no)
    out_one_integ (c.de_no)
    gen_alloc_log_work
    out_one_integ (log_work_var_no)
    delete_syn_elem a
    delete_syn_elem se
    Set se = c
    se.de_no = log_work_var_no
    Exit Sub
End Sub
Sub gen_alloc_log_work()  '/*assign a logical work variable */
    If (log_work_var_no < log_work_var_max) Then
      log_work_var_no = log_work_var_no + 1
      Exit Sub
    End If
    '/**/
    term_err_stop gStringTable(3226) '"Not enough logical work variables.")
    Exit Sub
End Sub



Function chk_if_work_var(de_no As Integer) As Integer    '/*exit subs 1 if de_no is an arith wk variable*/
   If ((de_no >= first_arith_work) And _
    (de_no < (first_arith_work + kArithWorkDEMax))) Then
         chk_if_work_var = 1
         Exit Function
    Else
         chk_if_work_var = 0
         Exit Function
    End If
End Function

Public Function parseTheScript() As Integer
Dim save_proc_offset As Long
Dim pp As CParaTbl
Dim i As Integer
Dim p As CParaTbl
Dim tempBuffer As String

'dbug "at parse"
   quote_mode = 0
   
   look_i = 0
   end_input = 0
   proc_offset = 0
   if_level = 0
   OnOneLine = 0
   Do While gTarget.SelectCollection.count > 0
      gTarget.SelectCollection.Remove (1)
   Loop
   termin = ""
   term_used = 1
   If NeedInitialization = 0 Then
      Set file_null_ptr = New CFileEntry
      file_null_ptr.Name = "__file_null"
      Set aView_null_ptr = New CForm
      aView_null_ptr.Title = "__aView_null"
      Set object_null_ptr = New CUIObject
      object_null_ptr.Name = "__object_null"
      Set dataelem_null_ptr = New CDataElement
      dataelem_null_ptr.Name = "__dataelem_null"
      Set para_null_ptr = New CParaTbl
      para_null_ptr.name_ptr = "__para_null"
      Set se_null_ptr = New CSynElem
      se_null_ptr.term = "null"
      quote_con = Chr$(34)
      end_line = Chr$(13)
      line_feed = Chr$(10)
      tabChar = Chr$(9)
      code_buff_max = 1000000
      NeedInitialization = 1
   End If
    
   For Each p In gTarget.ParagCollection
      gTarget.ParagCollection.Remove 1
   Next
   parag_tbl_no = 0
   the_highest_parag = gTarget.ParagCollection.count

   in_ptr = -1
   endOfLastLine = -1     'added 04012005
   compile_err = 0
   Set first_se = se_null_ptr
   parse_it
   If (compile_err) Then
      compile_no_good = 1
      code_buffer = &HFFFF '/*mark as no good*/
      proc_offset = 2
      parseTheScript = -1
   Else
      'put out stop code
      out_one_char (&HFF)
      If proc_offset Mod 2 = 1 Then
         out_one_char (&H0)
      End If
'dbug "at parse offset=" + str$(proc_offset)
      'now add parag tbl offsets to end of code_buffer
      tempBuffer = code_buffer
      code_buffer = ""
      save_proc_offset = proc_offset
      proc_offset = 0
      'put # parags and offset on front of code
      out_one_integ (gTarget.ParagCollection.count)
      out_unsigned_integ (save_proc_offset + 4)         '***revised 3/13/2001 *******
      code_buffer = code_buffer + tempBuffer
'dbug "codelength=" + str$(Len(code_buffer))
'now add paras to end
      proc_offset = save_proc_offset + 4

      For Each p In gTarget.ParagCollection
         'out_one_integ (p.offset + 4)
         out_one_unsignedInteg (p.offset + 4)  '5/7/1 fix overflow
'dbug "putting out para offset for " + str$(p.tbl_no) + " offset=" + str$(p.offset)
      Next
      parseTheScript = 0
   End If
End Function

Sub parse_comment()
   'skip till end of line
   Do While (1)
      get_term
      If term_is("_end-line") Then Exit Do
   Loop
End Sub

Sub parse_it()
Dim work As String
Dim tempSe As CSynElem
Dim res As Integer

proc_loop:
   If Not first_se Is se_null_ptr Then
'dbug "1st"
      SYNTAX 104
   End If
   cur_char = ""
   log_work_var_no = 0
   arith_work_de_no = -9999
   string_work_de_no = -9999
   paren_cnt = 0
   paren_is_delim_sw = 1

   reset_args
   stmt_start_instr = proc_offset
    
    'start additions 04012005
    If gbDebugMode = True Then
        'only output once
        If thisModuleId <> lastModuleIdOutput Or currentStatementNumber <> lastStmtNumberOutput Then
            'put out  start of statement op-code
            out_one_char (&HF1)
            out_one_integ (thisModuleId)
            out_one_integ (currentStatementNumber)
            lastModuleIdOutput = thisModuleId
            lastStmtNumberOutput = currentStatementNumber
        End If
        
    End If
    'end additions 04012005
'dbug "going to build syn elem"
   build_syn_elem
'dbug "back from build_syn_elem"
continueSameStmt:                    '***added 11/20/2000 ****************
   If end_input And (first_se Is se_null_ptr) Then
      Exit Sub
   End If
   If first_se Is se_null_ptr Then
'sgBox "xxx found end of stmt"
      If OnOneLine = 2 Or OnOneLine = 3 Or OnOneLine = 4 Then '***added 12/1/2000 *******
         parse_endif   'simulate endif                         '***added 12/1/2000 *******
      End If                                                  '***added 12/1/2000 *******
      OnOneLine = 0                                           '***added 12/1/2000 *******
      GoTo proc_loop
   End If
'dbug "going to arith_exp_gen"
   If currentTypename = "" Then
      first_se.term = LCase$(first_se.term)        '***added 10.10.2000
'sgBox "in parse_it looking at first_se.term=" + first_se.term
      '06102002 Added lcase to the terms of this statement:
      If LCase$(first_se.term) = "do" _
         Or LCase$(first_se.term) = "sub" _
         Or LCase$(first_se.term) = "define" _
         Or LCase$(first_se.term) = "else" _
         Or LCase$(first_se.term) = "elseif" _
         Or LCase$(first_se.term) = "function" Then
'sgBox "skipping do"
           'dont gen for 'do'  because goofs up logic chk
      Else
         arith_exp_gen
      End If
   End If

'dbug "returning from arith_exp_gen"
chk_verb_again:
   get_term
'dbug "in parse_it ---got term=" + term + " len=" + str$(Len(term)) + " end_input=" + str$(end_input) + "  onOneline=" + str$(OnOneLine)
   If ((end_input) And (term_is(""))) Then
      If (Not if_level = 0) Or (Not gTarget.SelectCollection.count = 0) Then
         print_err gStringTable(3151) '"Error. All IF's or SELECT CASE statements are not matched with an ENDIF or END SELECT.")
      End If
      Exit Sub
   End If
   If Not currentTypename = "" Then
      term_used = 0
'dbug "doit"
      parse_typeElement
      GoTo proc_loop
   End If

   If (chk_proc_verbs()) Then
'sgBox "after chk verb--term=" + term + " OnOneLine=" + str$(OnOneLine)

DoneWithCmd:
      If OnOneLine = 0 Then GoTo chk_further
      If OnOneLine = 1 Then                   '***added 12/1/2000*****
         OnOneLine = 2                        '***added 12/1/2000*****
         GoTo proc_loop                       '***added 12/1/2000*****
      End If                                  '***added 12/1/2000*****
      If OnOneLine = 1 Or OnOneLine = 2 Then  '***changed 11/20/2000 *******
         OnOneLine = 2
         'GoTo proc_loop             '***commented out 11/20/2000 ********
'sgBox "going to continueSameStmt1"
         GoTo continueSameStmt       '***added 11/20/2000         ********
      End If

chk_further:
      If first_se Is se_null_ptr Then
'sgBox "first se is null ptr after donewith cmd   OnOneLine=" + str$(OnOneLine)
         If OnOneLine = 0 Then
           GoTo proc_loop
         End If
         If OnOneLine = 9 Then                 'added 4/07/2001 ***
'sgBox "going to chk_verb because 9"
            OnOneLine = 3                      'added 4/07/2001
            GoTo proc_loop                     'added 4/07/2001
         End If                                'added 4/07/2001
         
         If OnOneLine = 2 Or OnOneLine = 3 Or OnOneLine = 4 Then '***changed 11/20/2000 *******
              '1=after then but before else
              '2=after else but before endif
'sgBox "adding endif 2" + "  offset=" + str$(proc_offset)


             parse_endif   'simulate endif
         End If
         OnOneLine = 0
         GoTo chk_verb_again
      Else  'may have lingering left paren
'dbug "look for left paren 'had paren'=" + str$(verb_had_paren)
         If verb_had_paren = True Then
'dbug "looking for left paren"
            Do
               get_term
            Loop While term_is(" ")
            If term_not(")") Then
'dbug "no left paren"
               print_err gStringTable(3152) + term '"Missing right parenthesis:
            End If
'dbug "got left paren"
         End If
      End If
      GoTo chk_verb_again
   End If
'sgBox "not a verb=" + term + "  and term-type=" + str$(termType)
    '*******added 06102002 to let func calls be used w/o storing the result****
    If se Is se_null_ptr And theTermMaj = "d" _
    And theTermDe_no <= kStringWorkDEMax + kArithWorkDEMax Then
'MsgBox "found func w/o vaer"
        'looks like a func without wanting to store the result
        Set first_se = se_null_ptr
        GoTo proc_loop
    End If
    '********end-of-additions 06102002******
   If Not termType = 4 Then
      print_err gStringTable(3153) + termType '"Unidentified command =" + term
   End If
'sgBox "got nonverb=" + term + "  termin=" + termin
   If termin = ":" Then
'sgBox "found colon after term " + term + " -- proc as label"
      term_used = 0
      parse_label
      GoTo proc_loop
   End If
'If compiler_debug Then
'sgBox "process term=" + term + "   nxt=" + se.nxt.term
'End If

   If termin = "=" Then GoTo assignment
'sgBox "chking term=" + se.term
   If Not se Is se_null_ptr Then
      If se.term = "=" Then GoTo assignment
   End If
   res = locate_link_tbl
   If Not res = 0 Then
      term_used = 0
'sgBox "generating call to " + term
'compiler_debug = True
'dbugDump
'compiler_debug = False
      parse_call
      GoTo proc_loop
   End If

assignment:
   term_used = 0
   parse_let
   If OnOneLine = 0 Then GoTo chk_more
   If first_se Is se_null_ptr Then
      parse_endif   'simulate endif
      OnOneLine = 0
      GoTo chk_verb_again
   End If

   If OnOneLine = 1 Or OnOneLine = 2 Then
      OnOneLine = 2
'sgBox "going to continueStmt2"
      GoTo continueSameStmt
   End If

chk_more:
   If first_se Is se_null_ptr Then
'sgBox "first se is null ptr   OnOneLine=" + str$(OnOneLine)
      If OnOneLine = 0 Then
         GoTo proc_loop
      End If
      If OnOneLine = 2 Or OnOneLine = 3 Or OnOneLine = 4 Then
         '2=after then but before else
         '3=after else but before endif
         '4=after last stmt
'sgBox "simulating endif"
         parse_endif   'simulate endif
      End If
      OnOneLine = 0
      GoTo chk_verb_again
   End If
'sgBox "firstse=" + first_se.term
   GoTo proc_loop
End Sub

Sub SYNTAX(Optional err As Integer)
   print_err gStringTable(3115) & " " & err '"Syntax error.
End Sub

Sub parse_let()
'Dim save_rel_1 As String
'Dim save_rel_tbl_1 As Integer
'sgBox "at parse_let"
Dim round As Integer
Dim save_a, save_1, save_2, save_3 As Integer
Dim saveTerm As String
Dim saveTermtype As Integer
Dim wkde1 As CDataElement
Dim wkde2 As CDataElement
Dim de1 As CDataElement
Dim de2 As CDataElement
Dim Data1 As CDataElement
Dim Data2 As CDataElement
Dim saveData As CDataElement
Dim typ As New CTypeDef
Dim t As New CTypeElem
Dim wk As String
Dim data2occ1 As Integer
Dim data2occ2 As Integer
Dim data2occ3 As Integer
Dim data1occ1 As Integer
Dim data1occ2 As Integer
Dim data1occ3 As Integer
Dim Shift As Integer
Dim ii As Integer
Dim jj As Integer
Dim kk As Integer

'sgBox "aT PARSE_LET"
   get_dataname
'dbug "let dataname=" + term + " -- errcode=" + str$(err_code)
   If Not err_code = 0 Then SYNTAX 105
   If (data.isConstant = True) Then                                     'added 821 ****************
      print_err gStringTable(3154) '"Can't use a constant on the left side of an = sign."    'added 821 ****************
   End If                                                               'added 821 ****************
   If (Not termType = 4) Then SYNTAX 106
   set_arg_2
   Set Data2 = data
   round = 0
   get_term
    
   If term_is("rounded") Then
      round = 1
      get_term
   End If
   If Not term_is("=") Then SYNTAX 107
    
'sgBox "in 'let' getting dataname"
   get_dataname   'may be work var from arith_exp
   Set Data1 = data
   saveTerm = term
   saveTermtype = termType
'sgBox "in 'let' err-code=" + str$(err_code)
   If Not err_code = 0 Then SYNTAX 108
    
    
    If Data1.typedefFlag = True Then
'sgBox "CTypeDef s1_tbl_no=" + str$(s1_tbl_no)
'its a CTypeDef so must generate one assign of each member of type
        If Data2.typedefFlag = False Then print_err gStringTable(3155) 'Can only assign a CTypeDef to another CTypeDef"
        If Not Data2.typedefName = Data1.typedefName Then print_err gStringTable(3156) '"Can only assign CTypeDef variables to the same kind of CTypeDef variable."
        
        Set typ = locate_type_def(Data1.typedefName)
'sgBox "sub --searching for typedef=" + DATA.typedefName
'sgBox "assigning typedefs"
        For Each t In typ.Elements
          Set saveData = data
          wk = Right$(Data1.Name, Len(Data1.Name) - 2) + "." _
               + Right$(t.Name, Len(t.Name) - InStr(1, t.Name, ".", 0))

          'Set de = locateDataByName(wk)
          Set data = locateDataByName(wk)
          term_tbl_no = data.tbl_no
          Set de1 = data

          set_arg_1
'sgBox wk + " subs=" + str$(arg1_occ1) + " " + str$(arg1_occ2) + " " + str$(arg1_occ3) + " " + DATA.name
          wk = Right$(Data2.Name, Len(Data2.Name) - 2) + "." _
               + Right$(t.Name, Len(t.Name) - InStr(1, t.Name, ".", 0))

          Set data = locateDataByName(wk)
          arg_2 = data.tbl_no
          Set de2 = data
          Set data = saveData
          'now see if the element has addt'l subscripts
          data2occ1 = arg2_occ1
          data2occ2 = arg2_occ2
          data2occ3 = arg2_occ3
          data1occ1 = arg1_occ1
          data1occ2 = arg1_occ2
          data1occ3 = arg1_occ3
'sgBox "data1=" + data1.name + " " + str$(data1.max_no_values1) + " " + str$(data1.max_no_values2) + " " + str$(data1.max_no_values3) _
'+ "de1=" + de1.name + " " + str$(de1.max_no_values1) + " " + str$(de1.max_no_values2) + " " + str$(de1.max_no_values3)

          If de1.max_no_values3 > 1 Then    'element level has 3 levels of subs
             If Data1.max_no_values1 > 1 Or Data2.max_no_values1 > 1 Then print_err gStringTable(3157) '"Too many levels of subscripting."
             For ii = 1 To de1.max_no_values1
               For jj = 1 To de1.max_no_values2
                 For kk = 1 To de1.max_no_values3
                     term = str$(kk)
                     termType = 6
                     strip_and_locate_data_tbl
                     arg1_occ3 = term_tbl_no
                     arg2_occ3 = term_tbl_no
                     term = str$(jj)
                     termType = 6
                     strip_and_locate_data_tbl
                     arg1_occ2 = term_tbl_no
                     arg2_occ2 = term_tbl_no
                     term = str$(ii)
                     termType = 6
                     strip_and_locate_data_tbl
                     arg1_occ1 = term_tbl_no
                     arg2_occ1 = term_tbl_no
                     out_tok_2arg (&H59) '/*gen final move of result */
                     If (round) Then
                        out_one_char (&HFE)
                     Else
                       out_one_char (&H0)
                      End If
                  Next
                Next
              Next
          Else
            If de1.max_no_values2 > 1 Then       'element level has two levels of subscripts
               For ii = 1 To de1.max_no_values1
                 For jj = 1 To de1.max_no_values2
                   If Data1.max_no_values1 < 2 Then
                     term = str$(jj)
                     termType = 6
                     strip_and_locate_data_tbl
                     arg1_occ2 = term_tbl_no
                     term = str$(ii)
                     termType = 6
                     strip_and_locate_data_tbl
                     arg1_occ1 = term_tbl_no
                   Else
                     If Data1.max_no_values2 < 2 Then
                        term = str$(jj)
                        termType = 6
                        strip_and_locate_data_tbl
                        arg1_occ3 = term_tbl_no
                        term = str$(ii)
                        termType = 6
                        strip_and_locate_data_tbl
                        arg1_occ2 = term_tbl_no
                     Else
                        print_err gStringTable(3158) '"Too many levels of subscripting."
                     End If
                    End If
                    If Data2.max_no_values1 < 2 Then
                     term = str$(jj)
                     termType = 6
                     strip_and_locate_data_tbl
                     arg2_occ2 = term_tbl_no
                     term = str$(ii)
                     termType = 6
                     strip_and_locate_data_tbl
                     arg2_occ1 = term_tbl_no
                   Else
                     If Data2.max_no_values2 < 2 Then
                        term = str$(jj)
                        termType = 6
                        strip_and_locate_data_tbl
                        arg2_occ3 = term_tbl_no
                        term = str$(ii)
                        termType = 6
                        strip_and_locate_data_tbl
                        arg2_occ2 = term_tbl_no
                     Else
                        print_err gStringTable(3159) '"Too many levels of subscripting."
                     End If
                    End If
                     out_tok_2arg (&H59) '/*gen final move of result */
                     If (round) Then
                        out_one_char (&HFE)
                     Else
                       out_one_char (&H0)
                      End If
                 Next
               Next
            Else
              If de1.max_no_values1 > 1 Then   'element level has 1 level of subs
'sgBox "1 level"
                 For ii = 1 To de1.max_no_values1
                   If Data1.max_no_values1 < 2 Then
                     term = str$(ii)
                     termType = 6
'sgBox "aaa"
                     strip_and_locate_data_tbl
'sgBox "bbb"
                     arg1_occ1 = term_tbl_no
                   Else
                     If Data1.max_no_values2 < 2 Then
                        term = str$(ii)
                        termType = 6
'sgBox "ccc=*" + term + "*"
                        strip_and_locate_data_tbl
'sgBox "ddd"
                        arg1_occ2 = term_tbl_no
                     Else
                        If Data1.max_no_values3 < 2 Then
                          term = str$(ii)
                          termType = 6
                          strip_and_locate_data_tbl
                          arg1_occ3 = term_tbl_no
                        Else
                          print_err gStringTable(3160) '"Too many levels of subscripting."
                        End If
                     End If
                   End If
                   If Data2.max_no_values1 < 2 Then
                     term = str$(ii)
                     termType = 6
                     strip_and_locate_data_tbl
                     arg2_occ1 = term_tbl_no
                   Else
                     If Data2.max_no_values2 < 2 Then
                        term = str$(ii)
                        termType = 6
                        strip_and_locate_data_tbl
                        arg2_occ2 = term_tbl_no
                     Else
                        If Data2.max_no_values3 < 2 Then
                          term = str$(ii)
                          termType = 6
                          strip_and_locate_data_tbl
                          arg2_occ3 = term_tbl_no
                        Else
                          print_err gStringTable(3161) '"Too many levels of subscripting."
                        End If
                     End If
                   End If
'sgBox "zzz"
                   out_tok_2arg (&H59) '/*gen final move of result */
                   If (round) Then
                        out_one_char (&HFE)
                   Else
                       out_one_char (&H0)
                   End If
                 Next
              Else   'element level has no levels of sub
                  out_tok_2arg (&H59) '/*gen final move of result */
                  If (round) Then
                     out_one_char (&HFE)
                  Else
                     out_one_char (&H0)
                  End If
              End If
            End If
          End If
            
            
'sgBox "past the subs process for 1 element"

'sgBox "sub def adding arg=" + wk + "/" + de.name + "kind=" + de.kind
          'restore orig subs
           arg2_occ1 = data2occ1
           arg2_occ2 = data2occ2
           arg2_occ3 = data2occ3
           arg1_occ1 = data1occ1
           arg1_occ2 = data1occ2
           arg1_occ3 = data1occ3
          
        Next   'next element in CTypeDef
'sgBox "CTypeDef completed"
      Else
         'not a type def arg
         set_arg_1
    
         Set wkde1 = find_de_by_no(arg_1)
         Set wkde2 = find_de_by_no(arg_2)

'12/27/2000 MMD
         If (((wkde1.Kind = "s") And (Not wkde2.Kind = "s")) _
         Or ((wkde2.Kind = "s") And (Not wkde1.Kind = "s"))) Then
'         If (Not wkde1.kind = wkde2.kind) Then
             print_err gStringTable(3162) '"Right and left side of = sign must be matching data types.")
         End If
          If wkde1.Kind = "s" And wkde1.max_no_values1 > 1 And wkde1.tbl_no = wkde2.tbl_no Then                  '*** added  10.10.2000
            'it is an assignment of one element of a string array to another element of the same array          '*** added  10.10.2000
            'this can cause memory problems in the runtime, so first assign the right side to a work string var '*** added  10.10.2000
            'and then assign the work var to the left hand side variable                                        '*** added  10.10.2000
            gen_alloc_string_work            '*** added  10.10.2000
            arg_3 = string_work_de_no        '*** added  10.10.2000
            arg3_occ1 = 0                    '*** added  10.10.2000
            arg3_occ2 = 0                    '*** added  10.10.2000
            arg3_occ3 = 0                    '*** added  10.10.2000
            out_one_char &H59                '*** added  10.10.2000
            out_the_1st_arg                  '*** added  10.10.2000
            out_the_3rd_arg                  '*** added  10.10.2000
            out_one_char &H0                 '*** added  10.10.2000
            'now assign wk var to result     '*** added  10.10.2000
            out_one_char &H59                '*** added  10.10.2000
            out_the_3rd_arg                  '*** added  10.10.2000
            out_the_2cnd_arg                 '*** added  10.10.2000
            out_one_char &H0                 '*** added  10.10.2000
         Else                                '*** added  10.10.2000
            out_tok_2arg (&H59) '/*gen final move of result */
            If (round) Then
              out_one_char (&HFE)
            Else
              out_one_char (&H0)
            End If
         End If                             '*** added  10.10.2000
       End If
   term = saveTerm
   termType = saveTermtype
End Sub
Sub parse_cursor()

    parse_opt_paren
    get_term
    '/**/
    If (term_is("id")) Then '/*using CURSOR ID n to set mouse on object n*/
        'get_dataname  '??type
        'If (err_code) Then SYNTAX
        'set_arg_1
        'out_tok_1arg (&H84)
        get_controlName ""
        out_one_char (&H84)
        out_one_integ (controlId)
        
        Exit Sub
    End If
   
    term_used = 0
    get_dataname_num
    set_arg_1   'x
    get_dataname_num
    set_arg_2   'y
    out_tok_2arg (&HD2)
End Sub
'Sub parse_directory()
'    arg_1 = 0
'    arg_2 = 0
'    arg_3 = 0
'    arg_4 = 0
'    arg_5 = 0
'    get_term
'    If (term_is("current-working")) Then
'       get_dataname
'       If (err_code) Then SYNTAX
'       If (Not DATA.kind = "s") Then SYNTAX
'       set_arg_1
'       out_tok_1arg (&H9F)
'        Exit Sub
'    End If
'    term_used = 0
'
'    get_dataname
'    If (err_code) Then SYNTAX
'    set_arg_1
'    Do While (1)
'       get_term
'       If (term_is("name")) Then
'          get_dataname_nosubs
'          If (err_code) Then SYNTAX
'          set_arg_2
'          GoTo continue
'       End If
'       If (term_is("date")) Then
'          get_dataname_nosubs
'          If (err_code) Then SYNTAX
'          set_arg_3
'          GoTo continue
'       End If
'       If (term_is("time")) Then
'                    get_dataname_nosubs
'                    If (err_code) Then SYNTAX
'                    set_arg_4
'                    GoTo continue
'       End If
'       If (term_is("size")) Then
'                        get_dataname_nosubs
'                        If (err_code) Then SYNTAX
'                        set_arg_5
'                        GoTo continue
'        End If
'        term_used = 0
'        Exit Do
'continue:
'    Loop
'     out_one_char (&H95)
'     out_the_1st_arg
'     out_the_2cnd_arg
'     out_the_3rd_arg
'     out_the_4th_arg
'     out_the_5th_arg
'End Sub
Sub parse_display()
    parse_opt_paren
    out_one_char (&H9)
    get_term
    If (term_is("color")) Then
        out_one_char (&H1)
        get_dataname
        If (err_code) Then SYNTAX 109
        If (data.Kind = "s") Then SYNTAX 110
        set_arg_1
        out_1arg
    Else
        out_one_char (&H0)
        term_used = 0
    End If
    get_term
    '/**/
    If (term_is("background")) Then
       out_one_char (&H1)
       get_dataname
       If Not err_code = 0 Then SYNTAX 111
       If (data.Kind = "s") Then SYNTAX 112
       set_arg_1
       out_1arg
    Else
       out_one_char (&H0)
       term_used = 0
    End If
    Do While (1)
       get_dataname
'sgBox "got dataname--errcode=" + str$(err_code)
       If Not err_code = 0 Then
           term_used = 0
'sgBox "exitinfg do"
           Exit Do
        End If
'sgBox "gotdataname=" + term
        out_one_char (&H1)
        set_arg_1
        out_1arg
     Loop
'sgBox "out of loop"
     out_one_char (&H0)
     Exit Sub
End Sub
Sub parse_edit()
    'not used
    parse_opt_paren
    get_dataname
    If Not err_code = 0 Then SYNTAX 113
    set_arg_1
    out_tok_1arg (&H96)
    get_term
    '/**/
    If (term_is("title")) Then
       get_dataname
       If Not err_code = 0 Then SYNTAX 114
       set_arg_1
       out_1arg
    Else
       out_one_char (&H0)
    End If
End Sub

Sub parse_else()
    
'sgBox "parsing else" + "  offset=" + str$(proc_offset)

    If termin = end_line Or termin = line_feed Then
'sgBox "a"
       parse_common_else
       arith_exp_gen
    Else
       get_term
       If term = "if" Then
'sgBox "b"
            parse_elseif
       Else
'sgBox "c"
           term_used = 0
           parse_common_else
           'arith_exp_gen          'commented out 4/07/2001 ***
       End If
    End If
End Sub
Sub parse_common_else()
    If ((if_level < 1) Or (para_false_ptr(if_level) = 0)) Then SYNTAX 115

    gen_a_dummy_goto

    Set p = loc_para_ptr(para_false_ptr(if_level))
    p.offset = proc_offset
    p.defined = 1
    para_false_ptr(if_level) = 0
    If OnOneLine = 2 Then OnOneLine = 9  'modified 4/07/2001 ***
End Sub

Sub parse_elseif()
    parse_common_else
    'if_level = if_level - 1
    arith_exp_gen
    parse_if
    if_was_elseif(if_level - 1) = 1
End Sub

Sub parse_endif()

    If (if_level = 0) Then
       '/**/
       print_err gStringTable(3163) '"ENDIF found but no IF
       Exit Sub
    End If
again:
    Set p = loc_para_ptr(para_endif_ptr(if_level))
    p.offset = proc_offset
    p.defined = 1
    If (Not para_false_ptr(if_level) = 0) Then
'sgBox "setting false ptr in endif"
       Set p = loc_para_ptr(para_false_ptr(if_level))
       p.offset = proc_offset
       p.defined = 1
    End If
'sgBox "in endif"
    if_level = if_level - 1
    If if_was_elseif(if_level) = 1 Then GoTo again
    If Not OnOneLine = 0 Then OnOneLine = 4    '****changed 11/20/2000 *****
End Sub
Sub parse_loop()
    If (while_level = 0) Then
       '/**/
       print_err gStringTable(3164) '"ENDWHILE found but no WHILE outstanding.")
       Exit Sub
    End If
    out_one_char (&HAA)
    
    out_one_integ (while_endwhile_ptr(while_level))

       Set p = loc_para_ptr(while_false_ptr(while_level))
       p.offset = proc_offset
       p.defined = 1
    while_level = while_level - 1
    Exit Sub
End Sub
Sub parse_exit()
'dbug "at exit sub"
  get_term
  If term_is("sub") Then
      If Not subOrFunc = "s" Then
         print_err gStringTable(3165) '"Found EXIT SUB within a function"
      End If
      out_one_char (&HF8)
      out_one_char (&HFF)
       
  ElseIf term_is("function") Then
      If Not subOrFunc = "f" Then
         print_err gStringTable(3166) '"Found EXIT function within a subroutine"
      End If
      out_one_char (&HF9)
      out_one_char (&HFF)
     
  ElseIf term_is("do") Then
       out_one_char (&HAB)
      out_one_integ (while_false_ptr(while_level))
      Exit Sub
  ElseIf term_is("for") Then
       out_one_char (&HAC)
      out_one_integ (for_false_ptr(for_level))
      Exit Sub
  Else
    SYNTAX 116
  End If
End Sub
Sub parse_end()
'dbug "at end sub"
  get_term
  If term_is("sub") Then
      If Not subOrFunc = "s" Then
         print_err gStringTable(3167) '"Found EXIT SUB within a function"
      End If
      
      If for_level <> 0 Then print_err gStringTable(3371) '"Missing 'Next' statement"   'added 12182002
      If gTarget.SelectCollection.count <> 0 Then print_err gStringTable(3370) '"Missing 'End Select' statement"   'added 12182002
      
      If if_level <> 0 Then                           '***added 3/13/2001
         print_err gStringTable(3168) '"IF does not have matching ENDIF"  '***added 3/13/2001
      End If                                          '***added 3/13/2001
      out_one_char (&HF8)
      out_one_char (&HFF)
      subOrFunc = " "
  ElseIf term_is("function") Then
      If Not subOrFunc = "f" Then
         print_err gStringTable(3169) '"Found EXIT function within a subroutine"
      End If
      
      If for_level <> 0 Then print_err gStringTable(3371) '"Missing 'Next' statement"   'added 12182002
      If gTarget.SelectCollection.count <> 0 Then print_err gStringTable(3370) '"Missing 'End Select' statement"   'added 12182002
      If if_level <> 0 Then                           '***added 3/13/2001
         print_err gStringTable(3170) '"IF does not have matching ENDIF"  '***added 3/13/2001
      End If                                          '***added 3/13/2001
      out_one_char (&HF9)
      out_one_char (&HFF)
      subOrFunc = " "
  ElseIf term_is("select") Then
      parse_end_select
  ElseIf term_is("type") Then
      If currentTypename = "" Then
          SYNTAX 117
      End If
      currentTypename = ""
  ElseIf term_is("if") Then   '4.20.2000 gh
      parse_endif             '4.20.2000 gh
      currentTypename = ""
  Else
    SYNTAX 118
  End If
End Sub


Sub parse_global()
  'start additions 02062004
  Dim t As CTypeElem
  Dim typ  As CTypeDef
  Dim wk As String
  Dim d2 As CDataElement
  
  gDimIsDatabase = False
    Dim db As cDatabase
dimAgain:
    'end additions 02062004
    get_dataname_nosubs
'dbug "got dname --name=" + term + " errcode=" + str$(err_code)
   If err_code = 0 Then
      If data.LocalOrGlobal = "g" Then
        print_err gStringTable(3171) '"Variable already defined"
      End If
   End If
   'start additions 02062004
   For Each db In gTarget.DatabaseCollection
     '04042004 If lcase$(db.name) = lcase$(term) Then
     If LCase$(db.Name) = LCase$(term) And db.LocalOrGlobal = "g" Then   'added 04042004
       print_err gStringTable(3414) 'Database name already defined elsewhere.
       Exit Sub
     End If
   Next
   'end additions 02042006
   add_data_name_to_tbl ("global")
   ParseDimOrGlobal "global"
   
   'start additions 02062004

    'now put out code to initialize the variable's value
   If data.typedefFlag = True Then
      'must put out init code for every member of typedef
'MsgBox "found typedef in dim"
      Set typ = locate_typedef(data.typedefName)
      For Each t In typ.Elements
          wk = Right$(data.Name, Len(data.Name) - 2) + "." _
               + Right$(t.Name, Len(t.Name) - InStr(1, t.Name, ".", 0))
'MsgBox "init vars typedef =" + wk
          Set d2 = locateDataByName(wk)
          arg_2 = d2.tbl_no
          arg2_occ1 = 0
          arg2_occ2 = 0
          arg2_occ3 = 0
          out_one_char &H19
          out_the_2cnd_arg
       Next
   Else
          out_one_char &H19
          arg_2 = data.tbl_no
          arg2_occ1 = 0
          arg2_occ2 = 0
          arg2_occ3 = 0
                 
          out_the_2cnd_arg
          
   End If
   get_term
   term_used = 0
   
   If termType = 4 Then GoTo dimAgain
   '04042004 If dimIsDatabase Then                                          'added 09242003
   '04042004   print_err "Must provide a database record layout name"      'added 09242003
   '04042004 End If
   'end additions 02062004
                                                            
End Sub
Function locate_typedef(who As String) As CTypeDef

   Dim t As CTypeDef
   For Each t In gTarget.TypeDefCollection
 'MsgBox "locatetypedef comparing=" + t.name + " to=" + who
     If LCase$(t.Name) = LCase$(who) Then
        Set locate_typedef = t
        Exit Function
     End If
   Next
   Set locate_typedef = Nothing
   
End Function
Sub parse_typeStmt()
Dim typename As String
 
   get_term
   If locate_data_tbl() = 1 Then
      print_err gStringTable(3172) '"TYPE name already defined as variable."
   End If
   If Not locate_type_def(term) Is Nothing Then
      print_err gStringTable(3173) '"Type name already defined."
   End If
'dbug "got dname --name=" + term + " errcode=" + str$(err_code)
   'If err_code = 0 Then
   '   If DATA.LocalOrGlobal = "g" Then
   '     print_err "Variable already defined"
   '   End If
   'End If
   Set typ = New CTypeDef
   currentTypename = term
   typ.Name = term
   gTarget.TypeDefCollection.Add typ

   get_term

   If term_is("_end-line") Then
      term_used = 0
   Else
      SYNTAX 119
   End If
End Sub

Sub parse_typeElement()
  Dim typelem As CTypeElem
  Dim saveTerm As String
  get_term
'sgBox "1st term is =" + term
   saveTerm = term
   If term_is("end") Then
     parse_end
  Else
    term_used = 0
    get_dataname_nosubs
'dbug "got dname --name=" + term + " errcode=" + str$(err_code)
   'If err_code = 0 Then
      'If DATA.LocalOrGlobal = "g" Then
      '  print_err "Variable already defined"
      'End If
   'End If
   
   term = ">>" + currentTypename + "." + saveTerm 'dont want to be able to use as reg data elem
   saveTerm = term
'sgBox "adding =" + term
   add_data_name_to_tbl ("global")
'sgBox "parsetypeelem added dataname=" + DATA.name
   ParseDimOrGlobal "global"
   For Each typelem In typ.Elements
     If typelem.Name = saveTerm Then print_err gStringTable(3174) '"Element of TYPE structure is duplicated."
   Next
   If data.typedefFlag = True Then
      print_err gStringTable(3175) '"TYPE definitions cannot nest other TYPE variables"
   End If
   Set typelem = New CTypeElem
   typelem.Name = saveTerm
   Set typelem.de = data
   typ.Elements.Add typelem
   
   'If DATA.max_no_values1 > 1 Then
   '   print_err "Type elements cannot be individual arrays."
   'End If
   
   
 End If
End Sub
Sub parse_loadLibrary()
   ' Load library is a language statement that can be called with 1 or 2 parameters
   ' The first parameter is a string that defines the name that the library will be
   ' referred to.  The second parameter is the local .inf library declaration file name
   ' (from the <install dir>\lib directory).  The second parameter is optional, because
   ' it will be created by adding ".inf" to the first parameter by default
   '
   ' LoadLibrary "mathlib"
   ' LoadLibrary "mathlib.inf", "math2"
   '
   '
   ' EMP additions
   ' Generate code for inline library if it is in the resource collection
   '
   Dim strInfPath As String
   Dim strLibObj As String
   Dim bLibDe As Boolean
   Dim lib As CExternalLibrary
   Dim res As CResourceFile
   Dim resID As Integer

   resID = -1   ' Default not found

   ' Get first arg
   ' It may be both the library .inf name and variable name
   ' It may or may not end with .inf
   get_term
   If (StrComp(Right$(term, 4), ".inf", vbTextCompare) = 0) Then
      strLibObj = Left$(term, Len(term) - 4)
      strInfPath = term
   Else
      strLibObj = term
      strInfPath = term + ".inf"
   End If
   term_used = 1
   
#If NSBSymbian = 0 Then
   For Each res In gTarget.ResourceCollection
      If (res.ResourceType = "libr") Then
          If LCase$(res.Name) = LCase$(strLibObj) Then
              resID = res.IdNo
          End If
      End If
   Next
#End If

   ' Look for optional second parameter
   ' If used it is the variable name that refers to the library
   get_term
   If Not (term_is("_end-line")) Then
      strLibObj = term
      term_used = 1
      get_term
      If Not (term_is("_end-line")) Then
         SYNTAX 120
      End If
      term_used = 1
   End If

   ' With all parameters accounted for, check to see that a library is
   ' not being added with a duplicate name
   On Error Resume Next
   Set lib = gTarget.LibraryCollection(strLibObj)
   If (err = 0) Then print_err gStringTable(3176) + strLibObj '("Duplicate library object name " + strLibObj)
   On Error GoTo 0

   ' Now, attempt to load the .inf file
   ' EMP changed for new library
   Set lib = New CExternalLibrary
   If (Not lib.LoadNewLibrary(strInfPath, strLibObj)) Then
      print_err gStringTable(3177) + strInfPath '"Unable to read library declaration file " & strInfPath)
   Else
      gTarget.LibraryCollection.Add lib, strLibObj
      lib.IdNo = gTarget.LibraryCollection.count - 1
   End If

'   If err_code <> 0 Then SYNTAX
'   set_arg_1

'   strLibObj = term
'   bLibDe = False
   
'   get_dataname
'   If (err_code = 0) Then
'      If (termType = gcTYPE_ALPHALIT) Then
'         strLibObj = term
'         bLibDe = True
'      ElseIf ((termType = 4) And (DATA.kind = "s")) Then
'         strLibObj = term
'         bLibDe = True
'      Else
'         SYNTAX
'      End If
'   Else
'      If Not (term_is("_end-line")) Then
'         SYNTAX
'      End If
'   End If

'   ' Ensure libname has proper extension, then try to load the declaration file
'   If ((Len(strLibObj) < 4) Or StrComp(right$(strLibObj, 4), ".inf", vbTextCompare) <> 0) Then
'      strLibObj = strLibObj & ".inf"
'   End If

   term = lib.PrcName
   termType = gcTYPE_ALPHALIT
   locate_data_tbl
   arg_2 = term_tbl_no
   s1_tbl_no = 0
   s2_tbl_no = 0
   s3_tbl_no = 0
   set_arg_2
'   out_tok_2arg (&H72)
   If resID < 0 Then
       out_one_char (&H72)
   Else
       out_one_char (&H7A)
   End If
   out_one_integ lib.IdNo
   out_the_2cnd_arg
   If resID >= 0 Then
       out_one_integ resID
   End If
'MsgBox "Parsed LoadLibrary"
End Sub  'parse_loadLibrary
Sub parse_dim()
  Dim t As CTypeElem
  Dim typ  As CTypeDef
  Dim wk As String
  Dim d2 As CDataElement
  gDimIsDatabase = False
dimAgain:
   parse_dim_single
    'now put out code to initialize the variable's value
   If data.typedefFlag = True Then
      'must put out init code for every member of CTypeDef
'sgBox "found CTypeDef in dim"
      Set typ = locate_type_def(data.typedefName)
      For Each t In typ.Elements
          wk = Right$(data.Name, Len(data.Name) - 2) + "." _
               + Right$(t.Name, Len(t.Name) - InStr(1, t.Name, ".", 0))
'sgBox "init vars CTypeDef =" + wk
          Set d2 = locateDataByName(wk)
          arg_2 = d2.tbl_no
          arg2_occ1 = 0
          arg2_occ2 = 0
          arg2_occ3 = 0
          out_one_char &H19
          out_the_2cnd_arg
       Next
   Else
          out_one_char &H19
          arg_2 = data.tbl_no
          arg2_occ1 = 0
          arg2_occ2 = 0
          arg2_occ3 = 0
                 
          out_the_2cnd_arg
          
   End If
   get_term
   term_used = 0
   If termType = 4 Then GoTo dimAgain
   '04042004 If dimIsDatabase Then                                          'added 09242003
   '04042004   print_err "Must provide a database record layout name"      'added 09242003
   '04042004 End If                                                         'added 09242003
End Sub

Sub parse_dim_single()
   Dim db As cDatabase    'inserted 02062004
   get_dataname_nosubs

   If err_code = 0 Then
     If data.LocalOrGlobal = "l" Then
       print_err gStringTable(3178) '"Variable already defined"
     End If
   End If
   'start additions 02062004
   For Each db In gTarget.DatabaseCollection
       '04042004 If lcase$(db.name) = lcase$(term) then
       If (LCase$(db.Name) = LCase$(term)) And (db.LocalOrGlobal = "l") And (LocalID = db.LocalSource) Then    'added 04042004
       print_err gStringTable(3414) '"Database name already defined elsewhere."
       Exit Sub
     End If
   Next
   'end additions 02062004
   add_data_name_to_tbl ("local")
   ParseDimOrGlobal "local"
   
End Sub
Sub ParseDimOrGlobal(locGlob As String)
  
  
'sgBox "at dim-or-glob term=" + term
   get_term
'sgBox "ten got term=" + term
   If term_is("(") Then
     If gDimIsDatabase Then                                   'added 09242003
        print_err gStringTable(3396) '"Database record name cannot be an array"  'added 09242003
     End If                                                  'added 09242003
     get_term
'sgBox "got subsc=" + term
    data.max_no_values1 = Val(term)
     get_term
     If Not term = ")" Then
        data.max_no_values2 = Val(term)
        get_term
        If Not term = ")" Then
           data.max_no_values3 = Val(term)
           get_term
        End If
     End If
     If Not term = ")" Then SYNTAX 121
     get_term
  End If
  If term_is("as") Then
     parse_the_as_clause locGlob    'modified 04042004
   Else
     SYNTAX 122
  End If
End Sub
Sub parse_the_as_clause(what As String)
   Dim t As CTypeDef
   Dim d As CDataElement
   Dim e As CTypeElem
   Dim parentDe As CDataElement
   Dim x1, x2, x3 As Integer
  
  Dim dbRecordName  As CDataElement      'inserted 04042004
  
   get_term
'dbug "looking for datatype -- got " + term
     
   Select Case term
   Case "variant"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      data.Kind = "v"
      data.ByteFlag = &H0
      ' ByteFlag2 == 0x40
      ' 0x00 = NULL
      data.ByteFlag2 = &H40
      ' 0x00 = i
      ' 0x01 = s
      ' 0x02 = n
      ' 0x04 = d
      ' 0x08 = t
      ' 0x10 = & (database)
      ' 0x20 = user
      ' 0x40 = object/pointer
      ' 0x80 = "Reserved"
   Case "integer"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      data.Kind = "i"
      data.Dgt_Aft = 0
      data.ByteFlag = &H80
   Case "string"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      data.Kind = "s"
      data.Dgt_Bef = 0 'allows to be resized
      data.Length = 32767
      data.ByteFlag = &H0
   Case "float", "double"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      data.Kind = "n"
      data.ByteFlag = &H40
   Case "single"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      data.Kind = "n"
      data.ByteFlag = &H20
   'Case "long"
      'DATA.kind = "n"
      'DATA.byteFlag = &H10
   Case "short"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      data.Kind = "i"
      data.Dgt_Aft = 0
      data.ByteFlag = &H10
   'Case "currency"
      'DATA.kind = "c"
   'Case "boolean"
      'DATA.kind = "f"
   Case "date"
       'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
     data.Kind = "d"
      data.ByteFlag = &H40    'added 5.20.2000
   Case "time"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      data.Kind = "t"
      data.ByteFlag = &H40    'added 5.20.2000
   Case "byte"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      data.Kind = "s" 'treat as one-byte string
      data.Dgt_Bef = 1
      data.Length = 1
      data.ByteFlag = &H80
   Case "database"
      'If gDimIsDatabase Then GoTo errorDatabase  'added 09242003
      Set dbdef = New cDatabase
      dbdef.Name = data.Name
      dbdef.IdNo = gTarget.DatabaseCollection.count + 1
      dbdef.LocalOrGlobal = Left$(what, 1)                     'added 04042004
      If dbdef.LocalOrGlobal = "l" Then                          'added 04042004
         dbdef.LocalSource = LocalID                    'added 04042004
      Else                                              'added 04042004
         dbdef.LocalSource = ""                         'added 04042004
      End If                                            'added 04042004
 
      gTarget.DatabaseCollection.Add dbdef
      data.Kind = "&"
      data.Name = ">_>_>_" 'chg name so no dataname match
         
         ' start of additions 09242003
         get_term
         If term_is("_end-line") Then Exit Sub
         If termType <> 5 Then
'MsgBox "termType=" & termType
                print_err gStringTable(3397) '"Must supply database name in quotes."
         End If
         Set d = find_de_by_no(theTermDe_no)
         dbdef.deviceFilename = d.single_value
'MsgBox "assigning device filename=" + dbdef.deviceFilename
'04042004 get_term
'04042004 If term <> "creator" Then
'04042004 creatorErr:
'04042004      print_err "Filename must be followed by 'CREATOR ""cccc"" "
'04042004 End If
'04042004 get_term
'04042004 If termType <> 5 Then GoTo creatorErr
'04042004 Set d = find_de_by_no(theTermDe_no)
'04042004 dbdef.creator = d.single_value
         
'MsgBox "Assigning creator=" + dbdef.creator + "  d.singleValue=" & d.single_value
 
'04042004 get_term
'04042004 If term_is("keyed") Then
'04042004   dbdef.noKeyFields = 1
'04042004   get_term
'04042004 End If
'04042004 If term = "with" Then
'04042004   'parsing database record format clauses
'04042004   If new_term_not("record") Then
'04042004        print_err ("Database format syntax is incorrect--expecting WITH RECORD") 'modified 02042004
'04042004   End If

            get_term
            If termType <> 4 Then
               print_err gStringTable(3407) 'Database format syntax is incorrect--expecting record name")
            End If
            
            'start additions 04/27/2004
            Set data = locateDataByName(">>" + term)
            If Not data Is Nothing Then
                print_err gStringTable(3414) 'Database name already defined elsewhere.
            End If
            'end additions 04/27/2004

            add_data_name_to_tbl ("global")               'inserted 04042004
            Set dbRecordName = data                       'inserted 04042004
            
            'read the record's type name
            get_term                                        'inserted 04042004
            If termType <> 4 Then                           'inserted 04042004
               print_err ("Database format syntax is incorrect--expecting record Type Definition name") 'inserted 04042004
            End If                                          'inserted 04042004
            dbdef.formatTypeName = term                     'inserted 04042004
            
            'see if has key field specified                 'inserted 04042004
            get_term                                       'inserted 04042004
            If termType = 4 Then                           'inserted 04042004
                dbdef.noKeyFields = 1                      'inserted 04042004
                
                
                'first field should be keyFieldName
                Set d = find_de_by_no(theTermDe_no)
                If d Is Nothing Then
                   print_err gStringTable(3408) '"database record's keyField is not defined by DIM statement"
                End If
                If d.typedefFlag Then
                   print_err gStringTable(3409) '"the database keyField cannot be a TYPE name, must be single variable"
                End If
                If d.max_no_values1 > 1 Then
                   print_err gStringTable(3410) '"the database keyField cannot be subscripted."
                End If
                dbdef.keyFieldTblNo = d.tbl_no
                get_term
                '04042004 If termType <> 4 Then
                '04042004    print_err ("Database format syntax is incorrect--expecting record layout name") 'modified 02042004
                '04042004 End If
                
            End If
            term_used = 0                 'inserted 04042004
            'end insertions 02042004
            gDimIsDatabase = True
         '04042004 Else                    'added 02042004
         '04042004   print_err "Must supply the database keyField and/or record layout name"  'added 02042004
         '04042004 End If
         '04042004 term_used = 0
         'end of additions 09242003
         '04042004 Exit Sub
         
         Set data = dbRecordName                 'inserted 04042004
         term = dbdef.formatTypeName             'inserted 04042004
         GoTo testForTypeDef                     'inserted 04042004
   Case Else
testForTypeDef:                                  'inserted 04042004
      For Each t In gTarget.TypeDefCollection
         If LCase$(term) = LCase$(t.Name) Then
            'CTypeDef
             If what = "f" Or what = "def" Then    '9/22/2001 added
                print_err gStringTable(3400) 'Functions cannot return a user defined TYPE result"  '9/22/2001 added
             End If                                '9/22/2001 added
            Set parentDe = data
            parentDe.typedefFlag = True
            parentDe.typedefName = LCase$(term)
            'Set t.de = DATA
             
            For Each e In t.Elements
               Set d = New CDataElement
               d.tbl_no = gTarget.DataCollection.count
               d.Name = LCase$(parentDe.Name) + "." + Mid$(e.de.Name, InStr(1, e.de.Name, ".") + 1, _
                                       Len(e.de.Name) - InStr(1, e.de.Name, "."))
               'additions 09242003
               'record 1st and last fields of record layout
               If gDimIsDatabase Then
                  If dbdef.firstDbFldNo = 0 Then
                       dbdef.firstDbFldNo = d.tbl_no + 1
                  End If
                 dbdef.lastDbFldNo = d.tbl_no + 1
               End If
               'end of additions 09242003

               d.Length = e.de.Length
               d.Dgt_Bef = e.de.Dgt_Bef
               d.Dgt_Aft = e.de.Dgt_Aft
               d.Kind = e.de.Kind
 'sgBox "in dim --setting name=" + d.name + "  to kind =" + d.kind
               d.Cur_No_Values = e.de.Cur_No_Values
               x1 = e.de.max_no_values1
               x2 = e.de.max_no_values2
               x3 = e.de.max_no_values3
               d.max_no_values1 = parentDe.max_no_values1 'subs come from var being defined
               d.max_no_values2 = parentDe.max_no_values2
               d.max_no_values3 = parentDe.max_no_values3
               If x1 > 1 Then
                  If d.max_no_values1 < 2 Then
                     d.max_no_values1 = x1
                  ElseIf d.max_no_values2 < 2 Then
                     d.max_no_values2 = x1
                  ElseIf d.max_no_values3 < 2 Then
                     d.max_no_values3 = x1
                  Else
                     print_err gStringTable(3179) '"Too many levels of subscripting."
                  End If
                  If x2 > 1 Then
                     If d.max_no_values2 < 2 Then
                        d.max_no_values2 = x2
                     ElseIf d.max_no_values3 < 2 Then
                        d.max_no_values3 = x2
                     Else
                        print_err gStringTable(3179) '"Too many levels of subscripting."
                     End If
                     If x3 > 1 Then
                        If d.max_no_values3 < 2 Then
                           d.max_no_values3 = x3
                        Else
                           print_err gStringTable(3179) '"Too many levels of subscripting."
                        End If
                     End If
                  End If
               End If
               'd.LocalOrGlobal = left$(locGlob, 1)
               d.LocalOrGlobal = parentDe.LocalOrGlobal
               d.LocalSource = parentDe.LocalSource
               'If locGlob = "local" Then
               '    d.LocalSource = LocalID
               'Else
               '    d.LocalSource = ""
               'End If
               d.ByteFlag = e.de.ByteFlag
               
               gTarget.AddDataElement d
'sgBox "added elem=" + d.name + "  from " + e.de.name
            Next
             parentDe.Name = ">>" + parentDe.Name 'change name so cant use as var
             If gDimIsDatabase Then                     'added 09242003
                 dbdef.formatRecord = parentDe.tbl_no   'added 09242003
                 dbdef.formatTypeName = parentDe.Name   'added 09242003
                 gDimIsDatabase = False                 'added 09242003
             End If                                     'added 09242003
            Exit Sub
         End If
      Next
      If gDimIsDatabase Then GoTo errorDatabase     'inserted 04042004
      SYNTAX 123
      Exit Sub                    'added 09242003
errorDatabase:                       'added 09242003
      print_err gStringTable(3401) 'Database record must be a TYPE name."  'added 09242003
      Exit Sub                                          'added 09242003
       
   End Select
   If termin = "*" Then
      If data.Kind = "s" Then print_err gStringTable(3180) '"Can only use DIM statement modifiers on numeric variables."
      get_term  'this gets the *
      get_term  'this gets length

      data.Length = Val(term)
      data.Dgt_Bef = data.Length
      If termin = "," Then
         If data.Kind = "s" Then SYNTAX 124
         get_term
'sgBox "term2 is '" + term + "' termin=" + termin
         data.Dgt_Aft = Val(term)
         If data.Length < data.Dgt_Aft + 2 Then print_err gStringTable(3362) '"Digits to right must be at least 2 less than length."
         data.Dgt_Bef = data.Length - data.Dgt_Aft - 2
'sgBox "setting dgtaft to " + str$(DATA.dgt_aft)
      Else
         data.Dgt_Aft = 0
         If Not data.Kind = "s" Then data.Dgt_Bef = data.Length - 1 'for sign
      End If
   End If
End Sub
Sub parse_externalSub()
    ' EMP rewritten
   Dim aSynElem(60) As CSynElem
   Dim i As Integer, numSE As Integer
   Dim strLibObjName As String, strMethodName As String
   Dim el As CExternalLibrary
   ' Dim elm As CExternalLibraryMethod
   Dim Value As CDataElement
   Dim libID As Integer, procNum As Integer, numArgs As Integer
   Dim IsNew As Boolean
   Dim wantsContext As Boolean

   parse_opt_paren
   ' Get lib
   get_term
   If (term_is("_end-line")) Then SYNTAX 125
   libID = Val(term)
   
   wantsContext = Not (s2_tbl_no = 0)
   
   ' Get proc
   get_term
   If (term_is("_end-line")) Then SYNTAX 126
   procNum = Val(term)
   
   IsNew = Not (s2_tbl_no = 0)

   ' Get numArgs
   get_term
   If (term_is("_end-line")) Then SYNTAX 127
   numArgs = Val(term)
   
   ' Out the proc particulars
   If (IsNew) Then
       If (wantsContext) Then
          out_one_char (&H7B)
       Else
          out_one_char (&H78)
       End If
   Else
       out_one_char (&H70)
   End If
   
   out_one_integ (libID)
   out_one_integ (procNum)
   out_one_integ (numArgs)

   If (IsNew) Then
       ' Output the argument type info
       For i = 1 To numArgs
           get_term
           out_one_char (s2_tbl_no)
           out_one_char (s3_tbl_no)
       Next i
   End If

   ' Get args, if any
   If Not se Is se_null_ptr Then
      Set aSynElem(0) = se
      For i = 0 To 50
         If (aSynElem(i) Is se_null_ptr) Then
            Exit For
         Else
            Set aSynElem(i + 1) = aSynElem(i).Nxt
         End If
      Next
      numSE = i
      If (aSynElem(numSE - 1).term = ")") Then
         If (numSE - 1 <> numArgs) Then
             MissingArg
         End If
      Else
         If (numSE - 1 <> numArgs) Then
             MissingArg
         End If
      End If
   End If
   

   ' Loop through proc arguments and out them
   Set se = se_null_ptr
   For i = 0 To (numSE - 1)
      If (aSynElem(i).maj <> "p") Then
         Set Value = find_de_by_no(aSynElem(i).de_no)
         arg_2 = aSynElem(i).de_no
         arg2_occ1 = aSynElem(i).sub1
         arg2_occ2 = aSynElem(i).sub2
         arg2_occ3 = aSynElem(i).sub3
         out_the_2cnd_arg
      End If
      delete_syn_elem aSynElem(i)
   Next
End Sub  'parse_externalSub
Sub oldParse_externalSub()
   Dim aSynElem(10) As CSynElem
   Dim i As Integer, numSE As Integer
   Dim strLibObjName As String, strMethodName As String
   Dim el As CExternalLibrary
   ' Dim elm As CExternalLibraryMethod
   Dim Value As CDataElement
   Dim libID As Integer, procNum As Integer, numArgs As Integer

   parse_opt_paren
   ' Get lib
   get_term
   If (term_is("_end-line")) Then SYNTAX 128
   libID = Val(term)

   ' Get proc
   get_term
   If (term_is("_end-line")) Then SYNTAX 129
   procNum = Val(term)

   ' Get numArgs
   get_term
   If (term_is("_end-line")) Then SYNTAX 130
   numArgs = Val(term)
   
   ' For now, just pass over the argument info
   For i = 1 To numArgs
       get_term
   Next i

   ' Get args, if any
   If Not se Is se_null_ptr Then
      Set aSynElem(0) = se
      For i = 0 To 9
         If (aSynElem(i) Is se_null_ptr) Then
            Exit For
         Else
            Set aSynElem(i + 1) = aSynElem(i).Nxt
         End If
      Next
      numSE = i
      If (aSynElem(numSE - 1).term = ")") Then
         If ((numSE - 1) <> numArgs) Then
             MissingArg
         End If
      Else
         If (numSE <> numArgs) Then
             MissingArg
         End If
      End If
   End If
   
   ' Out the proc particulars
   out_one_char (&H70)
   out_one_integ (libID)
   out_one_integ (procNum)
   out_one_integ (numArgs)

   ' Loop through proc arguments and out them
   Set se = se_null_ptr
   For i = 0 To (numSE - 1)
      If (aSynElem(i).maj <> "p") Then
         Set Value = find_de_by_no(aSynElem(i).de_no)
         arg_2 = aSynElem(i).de_no
         arg2_occ1 = aSynElem(i).sub1
         arg2_occ2 = aSynElem(i).sub2
         arg2_occ3 = aSynElem(i).sub3
         out_the_2cnd_arg
      End If
      delete_syn_elem aSynElem(i)
   Next
End Sub  'old parse_externalSub
Sub parse_sysTrapSub()
   Dim aSynElem(10) As CSynElem
   Dim i As Integer, numSE As Integer
   Dim strLibObjName As String, strMethodName As String
'   Dim el As CExternalLibrary
'   Dim elm As CExternalLibraryMethod
   Dim Value As CDataElement
   Dim trapNum As Integer, numArgs As Integer

   parse_opt_paren
   ' Get lib
'   get_term
'   If (term_is("_end-line")) Then SYNTAX 131
'   On Error Resume Next
'   Set el = model1.LibraryCollection(term)
'   If (err <> 0) Then print_err ("Invalid Library Object name: " + term)
'   On Error GoTo 0
'   set_arg_1

   ' Get proc
   get_term
'sgBox term, vbOKOnly, "parse_sysTrapSub: term 1"
   If (term_is("_end-line")) Then SYNTAX 132
   On Error Resume Next
   trapNum = CInt(Val(term))
'sgBox trapNum, vbOKOnly, "parse_sysTrapSub: trapNum"
   If (err = 0) Then
      get_term
'sgBox term, vbOKOnly, "parse_sysTrapSub: term 2"
      If (term_is("_end-line")) Then SYNTAX 133
      numArgs = CInt(Val(term))
'sgBox numArgs, vbOKOnly, "parse_sysTrapSub: numArgs"
   Else
      'Do something here to convert trap names as strings to OS trap numbers
'   Set elm = el.m_arrGlobalMethods(term)
'   If (err <> 0) Then print_err ("Procedure(" + DATA.single_value + ") not a member of Library")
   End If
   On Error GoTo 0
'   set_arg_2

   ' Get args from call, if any
   Set aSynElem(0) = se
   For i = 0 To 9
      If (aSynElem(i) Is se_null_ptr) Then
         Exit For
      Else
         Set aSynElem(i + 1) = aSynElem(i).Nxt
      End If
   Next
   numSE = i
   ' Compare number of args in call to prescribed number of args
   If (aSynElem(i).term = ")") Then
      If ((numSE - 1) <> numArgs) Then MissingArg
   Else
      If (numSE <> numArgs) Then MissingArg
   End If

   ' Out the proc particulars
   out_one_char (&H73)
   out_one_integ (trapNum)
   out_one_integ (numArgs)

   ' Loop through any proc arguments and out them
   Set se = se_null_ptr
   For i = 0 To (numSE - 1)
'sgBox "outing an arg"
      If (aSynElem(i).maj <> "p") Then
         Set Value = find_de_by_no(aSynElem(i).de_no)
         arg_2 = aSynElem(i).de_no
         arg2_occ1 = aSynElem(i).sub1
         arg2_occ2 = aSynElem(i).sub2
         arg2_occ3 = aSynElem(i).sub3
         out_the_2cnd_arg
      End If
      delete_syn_elem aSynElem(i)
   Next
End Sub  'parse_sysTrapSub
Sub ClearLocalVariables()
  Dim d As CDataElement

   For Each d In gTarget.DataCollection
      If d.LocalOrGlobal = "l" Then
         d.LocalOrGlobal = "x"
      End If
   Next
End Sub
Sub parse_define()
   'skip define statements - they are obsolete
   
   get_link_name
   If p.ptype = "" Then
      p.ptype = "f"
      p.defBy = "d"
   ElseIf Not p.ptype = "f" Then
      print_err gStringTable(3181) '"Function name same as subroutine or function name."
   End If
   If p.defBy = "f" Then print_err gStringTable(3182) '"DEFINE not needed and may conflict with function definition.")
   
   If new_term_not("as") Then
      print_err gStringTable(3183) '"function type must be defined with AS clause
   End If
   If p.defined = 0 Then
      p.defined = 1
      term = p.name_ptr
'sgBox "adding func name as d.e. = " + term
      'create a dataname for the function
      add_data_name_to_tbl ("global")
      p.func_de_no = data.tbl_no
   Else
      'print_err "Function name defined in two places"
      parse_comment
      Exit Sub
   End If
   
   parse_the_as_clause "def"
   
End Sub
Sub parse_function() 'func definition
  Dim typ As New CTypeDef
  Dim t As New CTypeElem
  Dim de As CDataElement
  Dim wk As String
  

   Dim result As Integer
   Dim cnt As Integer
   If Not subOrFunc = " " Then
     print_err gStringTable(3184) '"Previous sub or function not terminated by EXIT statement"
   End If
   startingParagCount = gTarget.ParagCollection.count    'added 4/07/2001 ***
   subOrFunc = "f"
   ClearLocalVariables
   get_link_name
   
   LocalID = p.name_ptr 'func name
   LastSubFuncParsed = p.name_ptr      '06102002  added
   p.moduleId = thisModuleId 'may override where define set it to
   If p.ptype = "" Then
      p.ptype = "f"
      p.defBy = "f"
   ElseIf Not p.ptype = "f" Then
      print_err gStringTable(3185) '"Function name same as paragraph or function name."
   End If
   
   
   If gbDebugMode Then       'added 04012005
       out_one_char (&HF2)   'added 04012005
       p.offset = proc_offset - 6  'added 04012005 to acct for F1/mod/stmt/F2
   Else                            'added 04012005
       p.offset = proc_offset
   End If                          'added 04012005
   
   out_one_char (&HC2) 'tok
   
   If new_term_not("(") Then SYNTAX 134
   cnt = 0
LoopOnArg:
   get_term
   If Not term = ")" Then
      term_used = 0
'sgBox "going to parse_dim with term=" + term
      '805 commented out parse_dim            *************************************************************
      parse_dim_single                        '805 added ***************************************************
      If data.typedefFlag = True Then
        Set typ = locate_type_def(data.typedefName)
        For Each t In typ.Elements
          cnt = cnt + 1
          'Set de = locateDataByName(DATA.name + "." + t.name)
          wk = Right$(data.Name, Len(data.Name) - 2) + "." _
               + Right$(t.Name, Len(t.Name) - InStr(1, t.Name, ".", 0))
          Set de = locateDataByName(wk)
          out_one_integ (de.tbl_no)
          If de.max_no_values1 > 1 Then out_one_integ (0)  '805 added ****************************************
          If de.max_no_values2 > 1 Then out_one_integ (0)  '805 added ****************************************
          If de.max_no_values3 > 1 Then out_one_integ (0)  '805 added ****************************************
         Next
         GoTo LoopOnArg
     Else
'sgBox "adding parameter " + DATA.name + "  type=" + DATA.kind
        out_one_integ (data.tbl_no)
        If data.max_no_values1 > 1 Then out_one_integ (0) '805 added ****************************************
        If data.max_no_values2 > 1 Then out_one_integ (0) '805 added ****************************************
        If data.max_no_values3 > 1 Then out_one_integ (0) '805 added ****************************************
         
        cnt = cnt + 1
        GoTo LoopOnArg
     End If
   End If
   If p.argCount = -1 Then
'sgBox "setting # args to " + str$(cnt)
      p.argCount = cnt
   Else
        If Not p.argCount = cnt Then
           print_err gStringTable(3186) + str$(p.argCount) + " " + str$(cnt)
           '"Wrong # of arguments - needs=" + str$(p.argCount) + " found=" + str$(cnt)
        End If
   End If
   out_one_integ (0)  'mark end of arg list
   If new_term_not("as") Then
      print_err gStringTable(3187) '"function type must be defined using 'AS type'")
   End If
   If p.defined = 0 Then
      p.defined = 1
      term = p.name_ptr
'sgBox "adding func name as d.e. = " + term
      add_data_name_to_tbl ("global")
      p.func_de_no = data.tbl_no
   Else
      If p.defBy = "d" Then
         p.defBy = "f"
      Else
        print_err gStringTable(3188) '"Function name defined in two places"
      End If
      Set data = find_de_by_no(p.func_de_no) 'added 5.20.2000
   End If   'create a dataname for the function

   out_one_integ data.tbl_no 'put out daname for func result
   parse_the_as_clause "f"
   'get_term
'sgBox "at select term=" + term
   'Select Case lcase$(term)
   '    Case "integer"
   '      DATA.kind = "i"
'sgBox "got case integer"
   '    Case "string"
   '      DATA.kind = "s"
   '      DATA.dgt_bef = 0 'make resizable string
   '   Case "date"
   '      DATA.kind = "d"
   '    Case Else
'sgBox "got case else --term=" + term
   '      SYNTAX
   'End Select
'sgBox "past select"
   'If termin = "*" Then
'sgBox "termin was *"
   '      get_term
   '      get_term
   '      DATA.length = val(term)
   '      If termin = "," Then
   '         get_term
   '         DATA.dgt_aft = val(term)
   '      Else
   '         DATA.dgt_aft = 0
   '      End If
   'End If
   
'sgBox "leaving parse_func"
End Sub
Sub parse_sub()
   'puts out one element of typedef as a sub or func arg
   '...may put out several if the element is subscripted
   Dim result As Integer
   Dim cnt As Integer
   Dim typ As New CTypeDef
   Dim t As New CTypeElem
   Dim de As New CDataElement
   Dim wk As String
   
   If Not subOrFunc = " " Then
     print_err gStringTable(3189) '"Previous sub or function not terminated by EXIT statement"
   End If
   startingParagCount = gTarget.ParagCollection.count  'added 4/07/2001 ***
   subOrFunc = "s"
   ClearLocalVariables
   get_link_name
   LastSubFuncParsed = p.name_ptr 'added 06102002
   LocalID = p.name_ptr 'func name
   p.moduleId = thisModuleId 'may override where define set it to
   If p.ptype = "" Then
      p.ptype = "s"
   ElseIf Not p.ptype = "s" Then
      print_err gStringTable(3190) '"Subroutine name same as paragraph or function name."
   End If
   If p.defined = 0 Then
      p.defined = 1
   Else
      print_err gStringTable(3191) '"Subroutine name defined in two places"
   End If
   If gbDebugMode Then            'added 04012005
       out_one_char (&HF2)         'added 04012005
       p.offset = proc_offset - 6  'added 04012005 to acct for F1/mod/stmt/F2
   Else                            'added 04012005
       p.offset = proc_offset
   End If                          'added 04012005
                   
   out_one_char (&H12) 'tok
   
   If new_term_not("(") Then SYNTAX 135
   cnt = 0
LoopOnArg:
   get_term
   If term = ")" Then
'dbug "parse sub got )"
      If p.argCount = -1 Then
        p.argCount = cnt
      Else
        If Not p.argCount = cnt Then
           print_err gStringTable(3192) '"Wrong # of arguments"
        End If
      End If
      out_one_integ (0)
'dbug "finished with parse_sub"
      Exit Sub
   Else
'dbug "parse sub got arg"
      term_used = 0
      '805 commented out parse_dim          ****************************************************************
      parse_dim_single                      '805 added *****************************************************
      If data.typedefFlag = True Then
        Set typ = locate_type_def(data.typedefName)
'sgBox "sub --searching for typedef=" + DATA.typedefName
        For Each t In typ.Elements
          cnt = cnt + 1
          wk = Right$(data.Name, Len(data.Name) - 2) + "." _
               + Right$(t.Name, Len(t.Name) - InStr(1, t.Name, ".", 0))
          Set de = locateDataByName(wk)
'sgBox "sub def adding arg=" + wk + "/" + de.name + "kind=" + de.kind
          out_one_integ (de.tbl_no)
          If de.max_no_values1 > 1 Then out_one_integ (0)  '805 added ****************************************
          If de.max_no_values2 > 1 Then out_one_integ (0)  '805 added ****************************************
          If de.max_no_values3 > 1 Then out_one_integ (0)  '805 added ****************************************
         Next
      Else
'sgBox "sub adding reg arg name=" + DATA.name + "  kind=" + DATA.kind
         out_one_integ (data.tbl_no)
         If data.max_no_values1 > 1 Then out_one_integ (0) '805 added ****************************************
         If data.max_no_values2 > 1 Then out_one_integ (0) '805 added ****************************************
         If data.max_no_values3 > 1 Then out_one_integ (0) '805 added ****************************************
         
         cnt = cnt + 1
      End If
      GoTo LoopOnArg
   End If

End Sub
Sub parse_beep()
   out_one_char &H5
End Sub
'06102002 added entire subroutine
Sub parse_clearfields()
    Dim view2 As CForm
    Set view2 = aView_null_ptr
    Dim work As String
    Dim argum1 As CDataElement
    Dim argum2 As CDataElement

    parse_opt_paren
    get_dataname
    If Not err_code = 0 Then SYNTAX 136
    If (Not data.Kind = "s") Then
       '/**/
       print_err gStringTable(3364) '"Screen name must be in quotes.")
    End If
    Set argum1 = data
    set_arg_1
   
   If Not Mid$(argum1.Name, 1, 1) = "." Then '/*if alpha literal*/
          print_err gStringTable(3364) '"Must use the name of a screen in quotes"
   Else        '06102002
      work = data.single_value
      For Each view2 In gTarget.FormCollection
        If (LCase$(view2.Name) = LCase$(work)) Then
           out_one_char (&H81)
           out_one_integ (view2.IdNo)
           Exit Sub
        End If
      Next
      print_err gStringTable(3365) '"NEXTFORM references an unknown screen name.")
   End If         '06102002
End Sub
'06102002 added entire subroutine ****
Sub parse_setheapvariablecount()
  get_dataname_num
  If Not err_code = 0 Then SYNTAX 137
  set_arg_1
  out_tok_1arg (&HC0)
End Sub

Sub parse_bitmap()
  'no longer used??
  parse_opt_paren
  get_controlName "bmp"
  get_dataname  '??type num or string
  
  If Not err_code = 0 Then SYNTAX 139
  set_arg_1
  out_one_char (&H3D)
  out_one_integ (controlId)
  out_the_1st_arg
End Sub
Sub parse_call()
   Dim result As Integer
   Dim cnt As Integer
   Dim typ As New CTypeDef
   Dim t As New CTypeElem
   Dim wk As String
   
   If Not OnOneLine = 0 Then print_err gStringTable(3193) '"Can't use CALL in same line as IF"
   get_link_name
   If p.ptype = "" Then
      p.ptype = "s"
   ElseIf Not p.ptype = "s" Then
      print_err gStringTable(3194) '"Subroutine name same as paragraph name or function name."
   End If
   out_one_char (&H11) 'tok
   out_one_integ (term_tbl_no) 'link parag#
'sgBox "a"
   If (new_term_not("(")) Then term_used = 0
   allowArrayNames = True     'added 805 ***************************************
   cnt = 0
LoopOnArgs:
   get_dataname
   If Not err_code = 0 Then
      Set data = locateDataByName(">>" + term)
      If Not data Is Nothing Then
         
         GoTo dataOrTypeDef
      End If
'sgBox "didnt find CTypeDef for term=" + term
       If term_is(")") Then
gotEnd:
         If p.argCount = -1 Then
           p.argCount = cnt
         Else
           If Not p.argCount = cnt Then
              print_err gStringTable(3195) '"Wrong # of arguments"
           End If
         End If
         out_one_integ (0) 'end marker
         allowArrayNames = False   'added 805 ********************************
         Exit Sub
      ElseIf term_is("_end-line") Then
         
         GoTo gotEnd
      Else
        't = locate_type_def(term)
        'If t Is Nothing Then SYNTAX
        SYNTAX 140
      End If
   Else
     'If DATA.typedefFlag = True Then print_err "Can't use user TYPE as call argument"
dataOrTypeDef:
      If data.typedefFlag = True Then
        Set typ = locate_type_def(data.typedefName)
'sgBox "call searching for typedef=" + DATA.typedefName
         For Each t In typ.Elements
          '805 ELIMINATED SEVERAL STMTS HERE AND ADDED THE NEXT STMT          ********************************
          PutOutTypeDefArgs t, data, s1_tbl_no, s2_tbl_no, s3_tbl_no, cnt  'added 805*************************
        Next
    Else
 'sgBox "call adding reg argmt name=" + DATA.name + "  kind=" + DATA.kind
         cnt = cnt + 1
         set_arg_1
         out_1arg
    End If
    GoTo LoopOnArgs
   End If
   
End Sub
Sub parse_createwindow()
  parse_opt_paren
  get_dataname_string
  set_arg_1 'name of window
  
  get_dataname_num
  If Not err_code = 0 Then SYNTAX 141
  set_arg_2  'x-start
  get_dataname_num
  If Not err_code = 0 Then SYNTAX 142
  set_arg_3  'y-start
  get_dataname_num
  If Not err_code = 0 Then SYNTAX 143
  set_arg_4  'width
  get_dataname_num
  If Not err_code = 0 Then SYNTAX 144
  set_arg_5  'height
  out_tok_5arg (&H40)
End Sub
Sub parse_destroywindow()
  parse_opt_paren
  get_dataname_string
  set_arg_1 'name of window
  out_tok_1arg (&H41)
End Sub
Sub parse_setcurwindow()
  parse_opt_paren
  get_dataname_string
  set_arg_1 'name of window
  out_tok_1arg (&H47)
End Sub
Sub parse_erasewindow()
  parse_opt_paren
  out_one_char (&H42)
  
  get_term                       '***added 11272000 ***********
  If term = "_end-line" Then     '***added 11272000 ***********
  Else                           '***added 11272000 ***********
    print_err gStringTable(3196) '"Extra information supplied on the end of the statement" '***added 11272000 ***********
  End If                         '***added 11272000 ***********
End Sub

Sub parse_drawchars()
  
  parse_opt_paren
  get_dataname_string
  set_arg_1  'chars
  get_dataname_num
  set_arg_2  'x-start
  get_dataname_num
  set_arg_3  'y-start
  
  out_tok_3arg (&H43)
  parse_getpentype
End Sub
Sub parse_drawbitmap()
  parse_opt_paren
  get_dataname_num
  set_arg_1  'bitmapid
  get_dataname_num
  set_arg_2  'x-start
  get_dataname_num
  set_arg_3  'y-start
  
  out_tok_3arg (&H48)

End Sub
Sub parse_drawline()
  
  parse_opt_paren
  get_dataname_num
  set_arg_1  'x-start
  get_dataname_num
  set_arg_2  'y-start
  get_dataname_num
  set_arg_3  'x-end
  get_dataname_num
  set_arg_4  'y-end
  out_tok_4arg (&H44)
  parse_getpentype
End Sub
Sub parse_drawrectangle()
  parse_opt_paren
  get_dataname_num
  set_arg_1  'x-start
  get_dataname_num
  set_arg_2  'y-start
  get_dataname_num
  set_arg_3  'width
  get_dataname_num
  set_arg_4  'height
 
  get_dataname_num
  set_arg_5  'corner diam
  out_tok_5arg (&H45)
  
  parse_getpentype
End Sub
Sub parse_fillrectangle()
  parse_opt_paren
  get_dataname_num
  set_arg_1  'x-start
  get_dataname_num
  set_arg_2  'y-start
  get_dataname_num
  set_arg_3  'width
  get_dataname_num
  set_arg_4  'height
  get_dataname_num
  set_arg_5  'corner diam
   out_tok_5arg (&H46)
  parse_getpentype
End Sub
Sub parse_getpentype()
  get_term
  If term_is("normal") Or term_is("nsbnormal") Or term_is("_end-line") Then
     out_one_char (&H0)
  Else
    If term_is("inverted") Or term_is("nsbinverted") Then
       out_one_char (&H1)
    Else
      If term_is("gray") Or term_is("grey") Or term_is("nsbgrey") Or term_is("nsbgray") Then
         out_one_char (&H2)
      Else
         If term_is("nsbcustom") Then
            out_one_char (&H3)
         Else
            SYNTAX 145
         End If
      End If
    End If
  End If
End Sub

Sub parse_menuerase()
  parse_opt_paren
  out_one_char (&H20)
End Sub
Sub parse_menudraw()
   parse_opt_paren
   get_term
   For Each Menu In gTarget.MenuCollection
'sgBox "comparing " + menu.name + " to " + term
     If LCase$(Menu.Name) = LCase$(term) Then
        GoTo found_it
     End If
   Next
   print_err gStringTable(3197) '"the name given is not a valid menu name."
   Exit Sub
found_it:
   out_one_char (&H21)
   out_one_integ Menu.IdNo
End Sub
Sub parse_menureset()
   parse_opt_paren
   out_one_char (&H22)
End Sub
Sub parse_msgbox()
    parse_opt_paren
    get_dataname_string
'dbug "in parse errmsg --err_code=" + str$(err_code)
    set_arg_1
    out_tok_1arg (&HD3)
End Sub
Sub parse_for()
  Dim save_term As String
  'Dim saveSE as csynelem
  'Dim workSe as csynelem
  
    'Set workSe = first_se
    'Do
    '  If workSe Is se_null_ptr Then
    '     Set saveSE = workSe
    '     Exit Do
    '   End If
    '   If workSe.term = "to" Then
    '     Set saveSE = workSe
    '     Set workSe.prv.nxt = se_null_ptr 'chop off the do command before the 'to'
    '     Exit Do
    '   End If
    '   Set workSe = workSe.nxt
    'Loop
    'arith_exp_gen
    
    If (for_level = max_for_lvls) Then
    '/**/
      print_err gStringTable(3198)  '"Statement too complex.")
      Exit Sub
    End If
    for_level = for_level + 1
    
    get_dataname_num
    set_arg_1   'ctl-variable
    
    If new_term_not("=") Then SYNTAX 146
    get_dataname_num
    set_arg_2  'initial value
    
    'Set first_se = saveTerm
    'setse.prv = se_null_ptr
    If new_term_not("to") Then SYNTAX 147

    get_dataname_num
    set_arg_3

    get_term
    If term_is("step") Then
       get_dataname_num
'sgBox "in parse_for  tblno=" + str$(term_tbl_no) + "  name=" + term
       set_arg_4
    Else
      save_term = term
      term = "1"
      termType = 6
      locate_data_tbl
      arg_4 = term_tbl_no 'step variable
      s1_tbl_no = 0
      s2_tbl_no = 0
      s3_tbl_no = 0
      'rel_1 = 0
      'rel_tbl_1 = 0
      set_arg_4
      term = save_term
      term_used = 0
    End If
    out_tok_4arg (&HA1) 'tok for-start
    out_one_integ for_level
    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    for_true_ptr(for_level) = p.tbl_no
    

    
    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    for_endwhile_ptr(for_level) = p.tbl_no
    
    
    p.offset = proc_offset
    p.defined = 1
     
    out_one_char (&HA2)  'tok for-continue
    out_the_1st_arg  'ctl-variable
    'out_the_3rd_arg   'end value
    'out_the_4th_arg   'step val
    out_one_integ for_level
   
    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    for_false_ptr(for_level) = p.tbl_no
    out_one_integ (p.tbl_no)

    Set p = loc_para_ptr(for_true_ptr(for_level))
    p.offset = proc_offset
    p.defined = 1
    

    
End Sub
Sub parse_next()
    If for_level = 0 Then
       print_err gStringTable(3199) '"Found 'NEXT' without a matching 'FOR' statement.")
      Exit Sub
    End If
    out_one_char (&HA3) 'tok next
    out_one_integ (for_endwhile_ptr(for_level))
    
    
    Set p = loc_para_ptr(for_false_ptr(for_level))
    p.offset = proc_offset
    p.defined = 1
    for_level = for_level - 1
End Sub
Sub parse_go()
    If (new_term_not("to")) Then SYNTAX 148
    parse_goto
End Sub
Sub parse_getpen()
    parse_opt_paren
    get_dataname_num
   set_arg_1  'current x
   get_dataname_num
   set_arg_2  'current y
   get_dataname_num
   set_arg_3  'pen up=3 pen down=2
   out_tok_3arg (&H4C)
End Sub
Sub parse_gosub()
    arg_2 = 0
    get_para_name
    If (err_code) Then SYNTAX 149
    arg_1 = p.tbl_no
    out_one_char (&H10)
    out_one_integ (arg_1)
End Sub
Sub parse_goto()
    get_para_name
    If (err_code) Then SYNTAX 150
    'arg_1 = p.tbl_no        '***commented out 11/20/2000
    'out_tok_1arg (&H1E)     '***commented out 11/20/2000
    out_one_char (&H1E)      '***added 11/20/2000
    out_one_integ (p.tbl_no) '***added 11/20/2000
End Sub

Sub parse_return()
    out_one_char (&H1D)
End Sub

Sub parse_select()
Dim cs As New CSelectObj

   get_term
'sgBox "in select     term=" + term
   If Not term_is("case") Then SYNTAX 151
'sgBox "getting dataname"
   get_dataname
   If (err_code) Then SYNTAX 152
'sgBox "found dataname"
   set_arg_1
   cs.arg = arg_1
   cs.occ1 = arg1_occ1
   cs.occ2 = arg1_occ2
   cs.occ3 = arg1_occ3
   cs.stat = 0
   term = "=" + Trim$(str$(parag_tbl_no + 1))
   add_to_para_tbl
   cs.end_select_ptr = p.tbl_no
   gTarget.SelectCollection.Add cs
End Sub

Sub parse_case()
Dim save_term As String
Dim cs As CSelectObj
Dim n As CSynElem
Dim e As CSynElem
Dim z As CSynElem

   If gTarget.SelectCollection.count = 0 Then
      print_err gStringTable(3200) '"CASE without SELECT CASE preceeding"
   End If
   Set cs = gTarget.SelectCollection.Item(gTarget.SelectCollection.count)
   cs.stat = cs.stat + 1
   If cs.stat > 1 Then
      'parse_endif
      out_one_char &H1E 'goto
      out_one_integ cs.end_select_ptr
      Set p = loc_para_ptr(para_false_ptr(if_level))
      p.offset = proc_offset
      p.defined = 1
      para_false_ptr(if_level) = 0
      if_level = if_level - 1
   End If
    
    'If Not first_se.term = "else" Then           '***commented out 10.10.2000
    If Not LCase$(first_se.term) = "else" Then     '*** added 10.10.2000
      If cs.stat >= 999 Then
         print_err gStringTable(3201) 'CASE with value cannot follow CASE ELSE"
      End If
      If Not first_se.maj = "d" Then                      '*** added 10.10.2000 ***
         print_err gStringTable(3202) '"CASE not followed by valid dataname." '*** added 10.10.2000 ***
      End If                                              '*** added 10.10.2000 ***
      
    'added 02202002 larry
    If first_se.de_no <= (kStringWorkDEMax + kArithWorkDEMax) Then 'can't use computed values
        print_err gStringTable(3354) '"CASE must be followed by a string or numeric literal or a simple variable name.Calculated values or functions are not allowed."
    End If
    'end of additions 02202002
      
      'insert select var
      Set n = New CSynElem
      n.de_no = cs.arg
      n.maj = "d"
      n.termType = 4
      n.term = "selectdataname"
      n.termin = " "
      n.posInInput = first_se.posInInput
      n.sub1 = cs.occ1
      n.sub2 = cs.occ2
      n.sub3 = cs.occ3
      
      Set e = New CSynElem
      e.maj = "r"
      e.sub1 = 3
      e.term = "="
      e.termin = " "
      
      
      Set n.Prev = se_null_ptr
      Set n.Nxt = e
      Set e.Prev = n
      Set e.Nxt = first_se
      Set first_se.Prev = e
      Set first_se = n
      
      logic_exp_gen
      out_one_char (&HC) 'tok for if
      save_term = term
    
      term = "=" + Trim$(str$(parag_tbl_no + 1))
      add_to_para_tbl
      If (if_level = max_if_lvls) Then
    '/**/
        print_err gStringTable(3203) '"Statement too compex
        Exit Sub
      End If
      if_level = if_level + 1
      if_was_elseif(if_level) = 0   'added 4/07/2001  *******
      para_false_ptr(if_level) = p.tbl_no
      out_one_integ (p.tbl_no)
    
      term = "=" + Trim$(str$(parag_tbl_no + 1))
      add_to_para_tbl
      para_true_ptr(if_level) = p.tbl_no
      out_one_integ (p.tbl_no)
      
      term = "=" + Trim$(str$(parag_tbl_no + 1))
      add_to_para_tbl
      para_endif_ptr(if_level) = p.tbl_no
      out_one_integ (p.tbl_no)

      term = save_term
      out_one_integ (log_work_var_no) '/*var to test*/
      get_term  'skip the resulting logic var
      

      Set p = loc_para_ptr(para_true_ptr(if_level))
      p.offset = proc_offset
      p.defined = 1
      OnOneLine = 0
    Else
      get_term  'skip else
      cs.stat = 999 'have case else
    End If
End Sub
Sub parse_end_select()
    Dim cs As CSelectObj
    If gTarget.SelectCollection.count = 0 Then print_err gStringTable(3204) '"END SELECT without SELECT CASE"
    If gTarget.SelectCollection.Item(gTarget.SelectCollection.count).stat = 0 Then
       print_err gStringTable(3205) '"SELECT CASE has no CASE statements"
    End If
    Set cs = gTarget.SelectCollection.Item(gTarget.SelectCollection.count)
    If cs.stat < 999 Then parse_endif 'dont need if last was case else
    Set p = loc_para_ptr(cs.end_select_ptr)
    p.offset = proc_offset
    p.defined = 1
    gTarget.SelectCollection.Remove gTarget.SelectCollection.count
    
End Sub
Sub parse_if()
    Dim save_term As String
  
    If Not OnOneLine = 0 Then
       print_err gStringTable(3206) '"Can't stack 'if' stmts on the same line"
    End If
    logic_exp_gen    '/*generate logic */
    out_one_char (&HC)   '/*token for if */
    save_term = term
    
    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    If (if_level = max_if_lvls) Then
   
      print_err gStringTable(3207) '"Statement too complicated to interpret--please simplify.")
      Exit Sub
    End If
    if_level = if_level + 1
    if_was_elseif(if_level) = 0
    para_false_ptr(if_level) = p.tbl_no
    out_one_integ (p.tbl_no)
    
    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    para_true_ptr(if_level) = p.tbl_no
    out_one_integ (p.tbl_no)
    
    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    para_endif_ptr(if_level) = p.tbl_no
    out_one_integ (p.tbl_no)

    term = save_term
    out_one_integ (log_work_var_no) '/*var to test*/
    get_term  'skip the resulting logic var
    get_term
    If (term_is("then")) Then
    Else
'sgBox "in if found  " + term
       term_used = 0
    End If

    Set p = loc_para_ptr(para_true_ptr(if_level))
    p.offset = proc_offset
    p.defined = 1
    
    'see if stmts follow 'then'
    get_stmt_elem
'dbug "at then term is " + term
    If Not term = "_end-line" Then
       OnOneLine = 1
       term_used = 0
'compiler_debug = True
    Else
       OnOneLine = 0
    End If
    
End Sub
Sub parse_do()
    get_term
    If term_is("while") Then
       parse_while
       
    ElseIf term_is("until") Then
       parse_until
    Else
      term_used = 0
      parse_while_or_until (&HA7)
    End If
End Sub
Sub parse_while()
  parse_while_or_until (&HA9)
End Sub
Sub parse_until()
  parse_while_or_until (&HA8)
End Sub
Sub parse_while_or_until(tok As String)
    Dim save_term As String
'sgBox "in do while"
    save_term = term
    If (while_level = max_while_lvls) Then
    '/**/
      print_err gStringTable(3208) '"Statement too complicated to interpret--please simplify.")
      Exit Sub
    End If
    while_level = while_level + 1
    '/**/
    'sprintf(term, "=p%lu\0",parag_tbl_no+1)
    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    while_endwhile_ptr(while_level) = p.tbl_no
    p.offset = proc_offset
    p.defined = 1

    term = save_term
    If Not tok = &HA7 Then
        arith_exp_gen
        logic_exp_gen    '/*generate logic */
    End If
    out_one_char (tok)  '/*token for while */

    save_term = term
    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    while_false_ptr(while_level) = p.tbl_no
    out_one_integ (p.tbl_no)

    term = "=" + Trim$(str$(parag_tbl_no + 1))
    add_to_para_tbl
    while_true_ptr(while_level) = p.tbl_no
    out_one_integ (p.tbl_no)
    out_one_integ (while_endwhile_ptr(while_level))

    term = save_term
    out_one_integ (log_work_var_no) '/*var to test*/

    Set p = loc_para_ptr(while_true_ptr(while_level))
    p.offset = proc_offset
    p.defined = 1
    If Not tok = &HA7 Then
        get_term 'skip the resulting logic var
    End If
End Sub
Public Function ALPHALIT() As Boolean
   If termType = 5 Then
     ALPHALIT = True
   Else
     ALPHALIT = False
   End If
   Exit Function
End Function
Public Function NUMLIT() As Boolean
   If termType = 6 Then
     NUMLIT = True
   Else
     NUMLIT = False
   End If
   Exit Function
End Function
Public Function DATATYPE() As Boolean
   If termType = 4 Then
     DATATYPE = True
   Else
     DATATYPE = False
   End If
   Exit Function
End Function
Public Function NOTDATA() As Boolean
   If Not termType = 4 Then
     NOTDATA = True
   Else
     NOTDATA = False
   End If
   Exit Function
End Function
Public Function OTHER() As Boolean
   If termType = 7 Then
     OTHER = True
   Else
     OTHER = False
   End If
   Exit Function
End Function
Public Function Reserved() As Boolean
   If termType = 3 Then
     Reserved = True
   Else
     Reserved = False
   End If
   Exit Function
End Function
Public Function verb() As Boolean
   If termType = 2 Then
     verb = True
   Else
     verb = False
   End If
   Exit Function
End Function
Sub parse_input()
    parse_opt_paren
    get_dataname
    If (err_code) Then SYNTAX 153
    If (ALPHALIT Or NUMLIT) Then SYNTAX 153
    set_arg_1
    out_tok_1arg (&H1)
    Exit Sub
End Sub
Sub parse_label()
    Dim save_term As String
    Dim result As Integer
    get_term
    result = locate_para_tbl
check_para_exists:
    If (Not result = 0) Then
      If (p.defined = 1) Then
        print_err gStringTable(3209) '"Duplicate label name used.")
        Exit Sub
      End If
    End If
    If (result = 0) Then
       add_to_para_tbl
    End If
    p.defined = 1
    p.offset = proc_offset
    
    last_para = p.tbl_no
    Exit Sub
End Sub
Sub parse_newmodel()
    'not used
    get_dataname
    If (err_code) Then SYNTAX 154
    set_arg_1
    out_tok_1arg (&H98)
    Exit Sub
End Sub
Sub parse_nextscreen()
   Dim view2 As CForm
   Set view2 = aView_null_ptr
   Dim work As String
   Dim argum1 As CDataElement
   Dim argum2 As CDataElement
   
   parse_opt_paren
   get_dataname
   If Not err_code = 0 Then SYNTAX 155
   If (Not data.Kind = "s") Then
      print_err gStringTable(3210) '"NEXTFORM name must be in quotes or a string variable.")
   End If
   Set argum1 = data
   set_arg_1
   If Not Mid$(argum1.Name, 1, 1) = "." Then '/*if alpha literal*/
         '06102002 print_err "Must use the name of a screen in quotes"
        out_tok_1arg (&H83)     '06102002
         
         get_term                     '***added 08222002
         If term_is("clear") Then   '***changed 09092002
           out_one_integ (1)          '***added 08222002
         Else                         '***added 08222002
            term_used = 0             '***added 08222002
           out_one_integ (0)          '***changed 09092002
         End If                       '***added 08222002
    
   Else        '06102002
   work = data.single_value
   For Each view2 In gTarget.FormCollection
      If LCase$(view2.Name) = LCase$(work) Then
         out_one_char (&H80)
         out_one_integ (view2.IdNo)
         
         get_term                     '***added 08222002
         If term_is("clear") Then     '***changed 09092002
           out_one_integ (1)          '***added 08222002
         Else                         '***added 08222002
            term_used = 0             '***added 08222002
            out_one_integ (0)          '***changed 09092002
         End If                       '***added 08222002
         
         If subOrFunc = "f" Then                      '***added 10.10.2000
            out_one_char &HF9  'terminate the function'***added 10.10.2000
            out_one_char &HFF                         '***added 10.10.2000
         Else                                         '***added 10.10.2000
            out_one_char &HF8   'terminate the sub    '***added 10.10.2000
            out_one_char &HFF                         '***added 10.10.2000
         End If                                       '***added 10.10.2000
         Exit Sub
      End If
   Next
   print_err gStringTable(3212) + work '"NEXTFORM references an unknown form name:" & work)
   End If
End Sub
Sub parse_print()
'code not used
    parse_opt_paren
    out_one_char (&HD5)
    Do While (1)
      get_dataname
      If (err_code) Then
         term_used = 0
         Exit Do
      End If
      out_one_char (&H1)
      set_arg_1
      out_1arg
    Loop
    out_one_char (&H0)
    Exit Sub
End Sub

Sub parse_redraw()
'sgBox "at redraw"
    parse_opt_paren
    get_term
'sgBox "got term=" + term
   If (term_is("id")) Then
      '/*using form REDRAW ID n to just redraw one object*/
'sgBox "id"
      get_controlName ""
'sgBox "ctlid=" + str$(controlID) + "  kind=" + o.obj.kind
      out_one_char (&H85)
      If o.obj.Kind = "pop" Then
          out_one_integ (controlId)
          out_one_char_of_string "p"
      Else
        out_one_integ (controlId)
        If testIfRealControl(o.obj) = 1 Then
           out_one_char_of_string "c"
        Else
           If o.obj.Kind = "lst" Then
              out_one_char_of_string "l"
           Else
              If o.obj.Kind = "fld" Then
                 out_one_char_of_string "f"
              Else
                 If o.obj.Kind = "grd" Then
                    out_one_char_of_string "t"
                 Else
                    If o.obj.Kind = "lbl" Then
                       out_one_char_of_string "z"
                    Else
                      If o.obj.Kind = "gad" Then   'added 812**************
                       out_one_char_of_string "g"  'added 812**************
                      Else                         'added 812***************
                        print_err gStringTable(3213) 'Can't redraw this kind of object"
                      End If 'added 812***************
                    End If
                  End If
              End If
           End If
        End If
      End If
'sgBox "leaving"
      Exit Sub
    End If
    
    term_used = 0
    out_one_char (&H82)
    out_one_char (&H0)  '4 zero's = 2 end-of-arg nulls for screen codeexecution
    out_one_char (&H0)
    out_one_char (&H0)
    out_one_char (&H0)
'sgBox "leaving redraw"
    Exit Sub
End Sub

Function testIfRealControl(obj As CUIObject) As Integer
   Select Case obj.Kind
   Case "but", "chk", "cho", "pop", "rpt", "sel", "pus": testIfRealControl = 1
   Case Else: testIfRealControl = 0
   End Select
End Function

Sub parse_sound()
  parse_opt_paren
  get_dataname_num
  set_arg_1  'frequency
  get_dataname_num
  set_arg_2  'duration
  get_dataname_num
  set_arg_3  'amplitude
  
  out_tok_3arg (&H4B)
  get_term
  If term_is("wait") Or term_is("nsbwait") Then
    out_one_char (&H0)
  Else
    If term_is("nowait") Or term_is("nsbnowait") Then
      out_one_char (&H1)
    Else
      term_used = 0
      out_one_char (&H1)
    End If
  End If
End Sub
'Sub parse_sort()
'    out_one_char (&HD4)
'    Do While (1)
'      get_term
'      If (VERB) Then Exit Do
'      term_used = 0
'      get_dataname
'      If ((err_code) Or NOTDATA) Then SYNTAX
'      set_arg_1
'      get_term
'      '/*"asc"*/
'      If (term_is("asc")) Then
'          out_one_char (&H1)
'      ElseIf (term_is("desc")) Then
'           out_one_char (&H2)
'      ElseIf (term_is("synch")) Then
'           out_one_char (&H3)
'      Else
'        term_used = 0
'        out_one_char (&H1)
'      End If
'      out_1arg
'    Loop
'    out_one_char (&H0)      '/*end of list*/
'    term_used = 0
'
'    Exit Sub
'End Sub

Sub parse_playsound()
  parse_opt_paren
  get_dataname_num
  set_arg_1  'sound id
  get_dataname_num
  set_arg_2  'ampScale
  get_dataname_num
  set_arg_3  'flags
  
  out_tok_3arg (&H4E)

End Sub

Sub parse_stop()
    out_one_char (&H18)
    out_one_char (&H0)
    Exit Sub
End Sub
Sub parse_table()
    get_term
     '/**/
     If (term_is("transfer")) Then
        parse_table_transfer
    ElseIf (term_is("empty")) Then
       parse_table_empty
    ElseIf (term_is("shift")) Then
       parse_table_shift
    ElseIf (term_is("delete")) Then
       parse_table_delete
    ElseIf (term_is("export")) Then
       parse_table_export
    Else: SYNTAX 156
    End If
    Exit Sub
End Sub
Sub parse_table_export()
    'not used
    get_dataname_nosubs
    If (err_code) Then SYNTAX 157
    set_arg_1
    out_tok_1arg (&H35)
    get_term
    If (term_not("to")) Then SYNTAX 158
    get_term
    '/**/
    If (term_is("subscript")) Then
      out_one_char (&H1)
      get_dataname
      If (err_code) Then SYNTAX 159
      set_arg_1
      out_1arg
    Else
      term_used = 0
      out_one_char (&H0)  '/*no subscript*/
    End If
    get_term
    '/**/
    If (term_not("tables")) Then SYNTAX 160
    Do While (1)
      get_term
      If (verb Or Reserved) Then
        term_used = 0
        Exit Do
      End If
      term_used = 0
      get_dataname_nosubs
      If (err_code) Then SYNTAX 161
      out_one_char (&H1)
      set_arg_1
      out_1arg
    Loop
    out_one_char (&H0)
    Exit Sub
End Sub
Sub parse_table_shift()
    'not used
    get_term
    If (term_not("down")) Then SYNTAX 162
    get_dataname
    If (err_code) Then SYNTAX 163
    set_arg_1
    get_term
    If (term_not("at")) Then SYNTAX 164
    get_dataname
    If (err_code) Then SYNTAX 165
    If (data.Kind = "s") Then
       print_err gStringTable(3214) '"Table subscript must be numeric.")
    End If
    set_arg_2
    out_tok_2arg (&H32)
    Exit Sub
End Sub
Sub parse_table_delete()
    'not used
    get_dataname
    If (err_code) Then SYNTAX 166
    set_arg_1
    get_term
    If (term_not("at")) Then SYNTAX 167
    get_dataname
    If (err_code) Then SYNTAX 168
    If (data.Kind = "s") Then
       '/**/
       print_err gStringTable(3214) '("Table subscript must be numeric.")
    End If
    set_arg_2
    out_tok_2arg (&H33)
    Exit Sub
End Sub

Sub parse_table_transfer()
    'not used
    Dim argum1 As CDataElement
    Dim argum2 As CDataElement

    get_dataname
    If (err_code) Then SYNTAX 169
    Set argum1 = data
    set_arg_1
    get_term
    If (term_not("to")) Then SYNTAX 170
    get_dataname
    If (err_code) Then SYNTAX 171
    Set argum2 = data
    set_arg_2
    If (Not argum1.Kind = argum2.Kind) Then
       print_err gStringTable(3215) '"Transfer tables must be of same kind of data.")
    End If
    out_tok_2arg (&H30)
    Exit Sub
End Sub
Sub parse_table_empty()
    'not used
    get_dataname
    If (err_code) Then SYNTAX 172
    set_arg_1
    out_tok_1arg (&H31)
    Exit Sub
End Sub

Sub parse_import()
   'not used
   Dim start_row, start_col As Integer
   Dim end_row As Integer
   Dim end_col As Integer
   
   Dim delim As String
   delim = " "

   parse_opt_paren
   get_term
   '/*/
   If (term_not("lotus")) Then GoTo check_flatfile
   get_dataname   '/*pathname*/
   If (err_code) Then SYNTAX 173
   set_arg_1
   out_tok_1arg (&H9A)
repeat_range_or_cells:
   get_term
   If (term_not("by")) Then term_used = 0
   get_term
   If (term_is("range")) Then GoTo range
   If (term_is("cell") Or term_is("cells")) Then GoTo cell
   SYNTAX 174
range:
   get_dataname
   If Not err_code = 0 Then SYNTAX 175
   set_arg_1  '/*range name*/
   out_tok_1arg (&H0)
   get_term
   If (term_is("to") Or term_is("by")) Then
   Else: term_used = 0
   End If
   get_term
   If (term_is("row") Or term_is("rows")) Then GoTo Rows
  
   If (term_is("col") Or term_is("cols")) Then GoTo Columns
   SYNTAX 176
Rows:
   out_one_char (&H0)
   GoTo row_column_common
Columns:
   out_one_char (&H1)
row_column_common:
   Do While (1)
      get_term
      If (verb Or Reserved) Then Exit Do
      term_used = 0
      get_dataname_nosubs
      If Not err_code = 0 Then SYNTAX 177
      set_arg_1
      out_1arg
   Loop
   out_one_integ (0)
   GoTo see_if_repeat
cell:
   out_one_char (&H1)
   Do While (1)
   
      get_term

      If (verb Or Reserved) Then Exit Do
      term_used = 0

      get_dataname
      If (err_code) Then SYNTAX 178

      '/*--parse_cvt_cell(data,&start_row,&start_col) ----*/
      set_arg_2
      get_dataname
      If (err_code) Then SYNTAX 179
      '/*----parse_cvt_cell(data,&end_row,&end_col) ----*/
      set_arg_3
      get_dataname_nosubs
      If (err_code) Then SYNTAX 180
      set_arg_1
      out_3arg


   Loop
   out_one_integ (0)
   term_used = 0
see_if_repeat:
   
   If (term_is("by") Or term_is("range") _
   Or term_is("cell") Or term_is("cells")) Then
    out_one_char (&H1)  '/*repeat*/
    GoTo repeat_range_or_cells
   End If
   out_one_char (&H0)
   term_used = 0
   Exit Sub
check_flatfile:
   '/**/
   If (term_not("flatfile")) Then SYNTAX 181
   get_dataname   '/*pathname*/
   If (err_code) Then SYNTAX 182
   set_arg_1
   out_tok_1arg (&H9C)
   delim = " "
   Do While (1)
       get_term
       If (term_is("space-delimited")) Then
       ElseIf (term_is("comma-delimited")) Then
         delim = ","
       ElseIf (term_is("tab-delimited")) Then
         delim = win_kybd_tab
       ElseIf (term_is("into")) Then
         term_used = 0
       Else: SYNTAX 183
       End If
       Exit Do
   Loop
   get_term
   If (term_not("into")) Then SYNTAX 184
   out_one_char_of_string (delim)
   Do While (1)
    get_dataname_nosubs
    If (err_code) Then
      term_used = 0
      Exit Do
    End If
    out_one_char (&H1)
    set_arg_1
    out_1arg
   Loop
    out_one_char (&H0)
   Exit Sub
End Sub
Sub parse_export()
   'not used
   Dim delim As String
   delim = " "
   parse_opt_paren
   get_term
   '/**/
   If (term_not("flatfile")) Then SYNTAX 185
   get_dataname   '/*pathname*/
   If (err_code) Then SYNTAX 186
   set_arg_1
   out_tok_1arg (&HA2)
   delim = " "
   Do While (1)
       get_term
       '/**/
       If (term_is("space-delimited")) Then
       ElseIf (term_is("comma-delimited")) Then
         delim = ","
       ElseIf (term_is("tab-delimited")) Then
         delim = win_kybd_tab
       ElseIf (term_is("into")) Then
         term_used = 0
       Else: SYNTAX 187
       End If
       Exit Do
   Loop
   get_term
   If (term_not("from")) Then SYNTAX 188
   out_one_char_of_string (delim)
   Do While (1)
    get_dataname
    If (err_code) Then
       term_used = 0
       Exit Do
    End If
    out_one_char (&H1)
    set_arg_1
    out_1arg
   Loop
    out_one_char (&H0)
   Exit Sub
End Sub

'Sub parse_run()
'   get_term
'    If (term_is("program")) Then
'      parse_runprogram
   'ElseIf (term_is("model")) Then
   '  parse_runmodel
'   Else: SYNTAX
'   End If
'   Exit Sub
'End Sub
'Sub parse_runprogram()
'   get_dataname
'   If (err_code) Then SYNTAX '/*program to run*/
'   set_arg_1
'   get_dataname
'   If (err_code) Then SYNTAX '/*parameter string*/
'   set_arg_2
'   out_tok_2arg (&HB1)
'   Exit Sub
'End Sub
Sub parse_launchprogram()
   parse_opt_paren
   get_dataname_num
   set_arg_2  'cardno
   get_dataname_string '/*program to run*/
   set_arg_1
   
   out_tok_2arg (&HB2)
   Exit Sub
End Sub
Sub parse_transfertoprogram()
   parse_opt_paren
   get_dataname_num
   set_arg_1  'cardno
   get_dataname_string '/*program to run*/
   set_arg_2
   
   out_tok_2arg (&HB3)
End Sub

'Sub parse_runmodel()
'    get_dataname
'    If (err_code) Then SYNTAX
'    set_arg_1
'    out_tok_1arg (&HB3)
'   Exit Sub
'End Sub
'Sub parse_execmodel()
'    get_dataname
'    If (err_code) Then SYNTAX
'    set_arg_1
'    out_tok_1arg (&HB4)
'   Exit Sub
'End Sub
Sub parse_exec()
   get_term
    '/**/
    If (term_is("program")) Then
      parse_launchprogram
   'ElseIf (term_is("model")) Then
   '  parse_execmodel
   Else: SYNTAX 189
   End If
   Exit Sub
End Sub
'Sub parse_execdos()
'    get_dataname
'    If (err_code) Then SYNTAX
'    set_arg_1
'    out_tok_1arg (&H97)
'    Exit Sub
'End Sub
Sub parse_send()
   'not used
   parse_opt_paren
   out_one_char (&HB5)
   Do While (1)
      get_dataname_nosubs
      If (err_code) Then
        term_used = 0
        Exit Do
      End If
      out_one_char (&H1)
      set_arg_1
      out_1arg
   Loop
   out_one_char (&H0)
   Exit Sub
End Sub
Sub parse_receive()
   'not used
   parse_opt_paren
   out_one_char (&HB6)
   Do While (1)
      get_dataname_nosubs
      If (err_code) Then
        term_used = 0
        Exit Do
      End If
      out_one_char (&H1)
      set_arg_1
      out_1arg
   Loop
   out_one_char (&H0)
   Exit Sub
End Sub

Sub parse_delay()
   parse_opt_paren
   get_dataname_num
   set_arg_1
   out_tok_1arg (&H4A)
   Exit Sub
End Sub
'Sub parse_alter()
'   Dim code As Byte
'   code = &H0
'   get_term
'   '/**/
'   If (term_not("id")) Then SYNTAX
'   get_dataname_num
'  set_arg_1   '/*id # of object to alter*/
'   out_tok_1arg (&H4B)
'   Do While (1)
'     get_term
      '/**/
'      If (term_is("xorigin")) Then code = &H1
'     If (term_is("yorigin")) Then code = &H2
 '    If (term_is("width")) Then code = &H3
 '    If (term_is("height")) Then code = &H4
 '    If (term_is("color")) Then code = &H5
 '    If (term_is("background")) Then code = &H6
 '    If (term_is("xoffset")) Then code = &H7
 '    If (term_is("yoffset")) Then code = &H8
 '    If (term_is("offset")) Then code = &H9
 '    If (term_is("xscale")) Then code = &HA
 '    If (term_is("yscale")) Then code = &HB
 '    If (term_is("filename")) Then code = &HC
 '    If code = &H0 Then
 '         Exit Do
 '    End If
 '    If (Not code = &HC) Then
 '      get_dataname_num
 '    Else
 '       get_dataname
 '       If Not err_code = 0 Then SYNTAX
 '    End If
 '    set_arg_1
 '    out_one_char (code)
 '    out_1arg
 '  Loop
 '  term_used = 0
 '  out_one_char (&H0)
 '  Exit Sub
'End Sub
'Sub parse_mem_debug()
'   out_one_char (&H2)
'   get_term
'   If (term_is("on")) Then
'     out_one_char (&H1)
'   ElseIf (term_is("off")) Then
'     out_one_char (&H0)
'   Else:  SYNTAX
'   End If
'   Exit Sub
'End Sub
Sub parse_ControlSetStatus()
  Dim res As Integer
  parse_opt_paren
  get_controlName ""
  get_term
  If term_is("checked") Then
    res = 1
  ElseIf term_is("unchecked") Then
    res = 0
  ElseIf term_is("on") Then
    res = 1
  ElseIf term_is("off") Then
    res = 0
  ElseIf term_is("0") Then
    res = 0
  ElseIf term_is("1") Then
    res = 1
  ElseIf term_is("nsbno") Then
    res = 0
  ElseIf term_is("nsbyes") Then
    res = 1
  ElseIf term_is("nsboff") Then
    res = 0
  ElseIf term_is("nsbon") Then
    res = 1
  ElseIf term_is("nsbunchecked") Then
    res = 0
  ElseIf term_is("nsbchecked") Then
    res = 1
  Else
      '*************************code added 2012001 **********
      'maybe its a varname
      term_used = 0
      get_dataname_num
      set_arg_1
      out_one_char (&H3B)   'use diff opcode
      out_one_integ (controlId)
      out_the_1st_arg
      Exit Sub
      '**************************end of code added 2012001****************
  End If
  out_one_char (&H30)
  out_one_integ (controlId)
  out_one_integ (res)
End Sub


'08222002 routine no longer needed
'added entire routine 06102002
'08222002Sub parse_controlssettext()
'08222002   'two args are control position # and text to set
'08222002  get_dataname_num
'08222002  set_arg_1
'08222002  get_dataname_string
'08222002  set_arg_2
'08222002  out_tok_2arg &H37
'08222002
'08222002End Sub


Sub parse_ControlSetLabel()
'   If editorSource = "p" Or editorSource = "w" Or editorSource = "v" Then
   Select Case Mid$(editorSource, InStrRev(editorSource, "|") + 1)
   Case "startup", "termination", "before"
      print_err gStringTable(3216) '"The ControlSetLabel command cannot be used before" & vbCrLf _
            & "the control is displayed on a form.
   End Select

   parse_opt_paren
   get_controlName ""
   get_dataname_string
   set_arg_1
   out_one_char (&H3E)
   out_one_integ (controlId)
   out_the_1st_arg
   If o.obj.Kind = "lbl" Then      'new
      out_one_char_of_string ("l")   'new
   Else                              'new
      out_one_char_of_string (" ")   'new
   End If                            'new
End Sub


Sub parse_PopupSetText()
  parse_opt_paren
  get_controlName "pop"
  get_dataname_string
  set_arg_1
  out_one_char (&H3E)
  out_one_integ (controlId)
  out_the_1st_arg
  out_one_char_of_string (" ")
End Sub

Sub parse_ControlHide()
   parse_opt_paren
   get_controlName ""

   'If testIfRealControl(o.obj) = 0 Then
   '   print_err "Can't hide/show this kind of object"
   'End If
   out_one_char (&H31)
   If controlObj.obj.Kind = "bmp" Then
      out_one_integ (controlObj.ResourceId) 'on bitmap controls, put out the bitmap id no instead
   Else
      If controlObj.obj.Kind = "shf" Then                    '815 new stmt**********
         print_err gStringTable(3217) '"Can't hide the Graffiti Shift Indicator" '815 new stmt**********
      Else                                                   '815 new stmt**********
         out_one_integ (controlId)
      End If                                                 '815 new stmt**********
   End If
   out_one_char (&H0)
   If controlObj.obj.Kind = "fld" Or controlObj.obj.Kind = "grd" Then '815 added **********
      If controlObj.HasScrollbar = True Then                  '815 added **********
         out_one_char (&H31)                                      '815 added **********
         out_one_integ (controlId + 1) 'and also hide the scrollbar '815 added **********
         out_one_char (&H0)                                       '815 added **********
      End If                                                      '815 added **********
   End If                                                         '815 added **********
End Sub
Sub parse_ControlShow()
  parse_opt_paren
  get_controlName ""
   'If testIfRealControl(o.obj) = 0 Then
   '  print_err "Can't hide/show this kind of object"
   'End If
  out_one_char (&H31) 'use same as hideControl
  If controlObj.obj.Kind = "bmp" Then
    out_one_integ (controlObj.ResourceId) 'on bitmap controls, put out the bitmap id no instead
  Else
    If controlObj.obj.Kind = "shf" Then                    '815 new stmt**********
      print_err gStringTable(3217) '"Can't hide the Graffiti Shift Indicator"  '815 new stmt**********
    Else                                                   '815 new stmt**********
       out_one_integ (controlId)
    End If                                                 '815 new stmt**********
  End If
  out_one_char (&H1)
  
End Sub

Sub parse_fieldSetText()
'   If editorSource = "p" Or editorSource = "w" Or editorSource = "v" Then
   Select Case Mid$(editorSource, InStrRev(editorSource, "|") + 1)
   Case "startup", "termination", "before"
      print_err gStringTable(3218) '"The FieldSetText command cannot be used before" & vbCrLf _
            & "the control is displayed on a form. Place this" & vbCrLf _
            & "command in the form after script or later."
   End Select

  Dim res As Integer
  parse_opt_paren
  get_controlName "fld"
'dbug "get dn2"
  get_dataname_string
'dbug "got dn2 err code=" + str$(err_code)
  set_arg_1
  
  out_one_char (&H32)
  out_one_integ (controlId)
  out_the_1st_arg
'dbug "leaving parse_fieldsettext"
'out_one_integ (res)
End Sub
Sub parse_fieldSetMaxChars()
  parse_opt_paren
  get_controlName "fld"
  get_dataname_num
  set_arg_1
  out_one_char (&H33)
  out_one_integ (controlId)
  out_the_1st_arg
  
End Sub
Sub parse_listAddItem()
  parse_opt_paren
  get_controlName "lst"
  addItemCommon
End Sub
Sub parse_popupAddItem()
  parse_opt_paren
  get_controlName "pop"
  controlId = controlId + 1
  addItemCommon
End Sub
'entire routine added 08222002
Sub parse_setgeneralproperty()
  Dim parenSw As Boolean
  Dim b As Byte
  Dim propId As Integer
  out_one_char (&H89)
  
  parse_opt_paren
  get_term       '1st param is how ctl is identified
                           ' 'p' by its positon on the form
  b = Asc(Left$(term, 1))
  out_one_char (b)
  Select Case term
    Case "i"
      get_term                 'id#
      out_one_integ (Val(term))
    Case "v"
      get_dataname_string      'vae containing name
      set_arg_1
      out_the_1st_arg
    Case "p"
      get_dataname_num         'var containing position
      set_arg_1
      out_the_1st_arg
  End Select
  get_term                     'number of property
  out_one_integ (Val(term))
  propId = Val(term)
  get_term                      '= sign or left paren or maybe reduction to single var
  'additions 09242003
'MsgBox "propid=" & propId & "    term=" + term
  Select Case propId
    Case 50                    'colwidth(i)
'MsgBox "parse_colwidth "
'compiler_debug = True
'dbugDump
        If term <> "(" Then
           parenSw = False
           term_used = 0
        Else
           parenSw = True
        End If
         get_dataname_num     'col#
         set_arg_1
         out_the_1st_arg
         
         get_term
         If parenSw = True Then
           If term <> ")" Then SYNTAX 189
           get_term            '= sign
         End If
    Case 54                    'textmatrix(i,j)
         If term <> "(" Then
           parenSw = False
           term_used = 0
        Else
           parenSw = True
        End If
         
         get_dataname_num     'row#
         set_arg_1
         out_the_1st_arg
         
         get_dataname_num     'col#
         set_arg_1
         out_the_1st_arg
         
         get_term
         If parenSw = True Then
           If term <> ")" Then SYNTAX 190
           get_term            '= sign
         End If
          
          
'MsgBox "got left paren"
          
    Case 55                    'valuematrix(i,j)
         If term <> "(" Then
           parenSw = False
           term_used = 0
        Else
           parenSw = True
        End If
         
         get_dataname_num     'row#
         set_arg_1
         out_the_1st_arg
         
         get_dataname_num     'col#
         set_arg_1
         out_the_1st_arg
         
         get_term
         If parenSw = True Then
           If term <> ")" Then SYNTAX 191
           get_term            '= sign
         End If
          
          
    Case 57                    'rowdata(row)
         If term <> "(" Then
           parenSw = False
           term_used = 0
        Else
           parenSw = True
        End If
         
         get_dataname_num     'row#
         set_arg_1
         out_the_1st_arg
         get_term
          If parenSw = True Then
           If term <> ")" Then SYNTAX 192
           get_term            '= sign
         End If
         
     'start additions 04012005
     Case 59                    'fontmatrix(i,j)
         If term <> "(" Then
           parenSw = False
           term_used = 0
        Else
           parenSw = True
        End If
         
         get_dataname_num     'row#
         set_arg_1
         out_the_1st_arg
         
         get_dataname_num     'col#
         set_arg_1
         out_the_1st_arg
         
         get_term
         If parenSw = True Then
           If term <> ")" Then SYNTAX
           get_term            '= sign
         End If
     'end additions 04012005
         
    End Select
  'end of additions 09242003
 If Not term = "=" Then SYNTAX 193
  Select Case propId
    Case 0 'text
         get_dataname_string
         set_arg_1
         out_the_1st_arg
    Case 1 'status
         get_dataname_num
         set_arg_1
         out_the_1st_arg
    Case 2 'selected
         get_dataname_num
         set_arg_1
         out_the_1st_arg
    Case 3 'maxChars
         get_dataname_num
         set_arg_1
         out_the_1st_arg
    Case 4 'current
         get_dataname_num
         set_arg_1
         out_the_1st_arg
    Case 5 'min
         get_dataname_num
         set_arg_1
         out_the_1st_arg
    Case 6 'max
         get_dataname_num
         set_arg_1
         out_the_1st_arg
    Case 7 'pageSize
         get_dataname_num
         set_arg_1
         out_the_1st_arg
    'additions 09242003
    Case 48, 50, 51, 52, 55, 56, 57, 58, 59, 80, 81, 82, 83 'modified 04012005    'col,colwidth,row,rows, valuematrix,value,rowdata,toprow,fontmatrix
         get_dataname_num
         set_arg_1
         out_the_1st_arg
    Case 54                       'textmatrix
         get_dataname_string
         set_arg_1
         out_the_1st_arg
    
    
    'end of additions 09242003
  End Select
    
End Sub

'entire routine added 08222002
Sub parse_generalVerb()
  Dim b As Byte
  Dim d2 As CDataElement    '***added 09302002***
  Dim parentName As String
  Dim fieldName As String
  Dim n As Integer
  Dim typ As CTypeDef
  Dim t As CTypeElem
  Dim parenSw As Boolean
  Dim i As Integer
  out_one_char (&H88)
  
  parse_opt_paren
  get_term       '1st param is how ctl is identified
                           ' 'p' by its positon on the form
  b = Asc(Left$(term, 1))     'chamged 09092002
  out_one_char b
  Select Case term
    Case "i"
      get_term                 'id#
      out_one_integ (Val(term))
    Case "v"
      get_dataname_string      'vae containing name
      set_arg_1
      out_the_1st_arg
    Case "p"
      get_dataname_num         'var containing position
      set_arg_1
      out_the_1st_arg
  End Select
  get_term                     'number of property
  out_one_integ (Val(term))
  
  Select Case Val(term)
    Case 0 'hide
         'no addt'l params
    Case 1 'show
         'no addt'l params
    Case 2 'additem (except cannot use for "grid" -- see "70" addrow  06072004
         get_dataname_string  'text to set
         set_arg_1
         out_the_1st_arg
         
         '09302002 get_dataname_num    'index # in list
         '09302002 set_arg_1
         '09302002 out_the_1st_arg
         '******added 09302002 *** down to ending marker---
            get_term
            If term = "_end-line" Or term = "nodisplay" Then
               term_used = 0
               Set d2 = dataelem_null_ptr
              arg_2 = 0
              arg2_occ1 = 0
              arg2_occ2 = 0
              arg2_occ3 = 0
            Else
               term_used = 0
               get_dataname_num  'index wherte to insert
               set_arg_2
            End If
            
            
            out_the_2cnd_arg   '//
            If new_term_is("nodisplay") Then
               out_one_char (&H0)
            Else
               term_used = 0
               out_one_char (&H1)
            End If
         '***09302002 END-OF-ADDITIONS ****************************************
    Case 3 'clear
         'no addt'l params
    Case 4 'delete item
         get_dataname_num   'index # of item to clear
         set_arg_1
         out_the_1st_arg
    Case 5 'start capture
         'no addt'l params
    Case 6 'erase
         'no addt'l params
    Case 7 'display Sig
         get_dataname_string  'signature bitmap string   '09092002
         set_arg_1                                       '09092002
         out_the_1st_arg                                 '09092002
    Case 8 'redraw
         'no addt'l parameters
    Case 9  'setfocus,cursor
         'no addt'l parameters
    'additions 09242003
    Case 70     'grid add
         ',o addtl params
         parse_opt_paren   'inserted 03042004
    Case 71 'delete item (grid)
         get_dataname_num   'index # of item to clear
         set_arg_1
         out_the_1st_arg
    Case 72    'coltype
          parse_opt_paren       'inserted 02062004
'get_term
'MsgBox "term=" + term + " type=" & termType & "   hadParen=" & verb_had_paren
'term_used = 0
         get_dataname_num   'column #
'MsgBox "term=" + term
         set_arg_1
         out_the_1st_arg
         
         get_dataname_string   'column type
'MsgBox "term=" + term
         set_arg_1
         out_the_1st_arg
         
         get_dataname_string   'format string
'MsgBox "term=" + term
         set_arg_1
         out_the_1st_arg
         
          
         If verb_had_paren = True Then
           get_term
           If term <> ")" Then SYNTAX 194
         End If
         
    Case 75                       '08152004   'hideGridLines'
         'no additional args      '08152004   'hideGridLines'
    Case 76                       '08152004   'showGridLines'
         'no additional args      '08152004   'showGridLines'

    Case 73   'bind to database
         
 
          
         '02062004 paren_sw = False
         '02062004 get_term
         '02062004 If term = "(" Then
         '02062004
         '02062004    paren_sw = True
         '02062004 Else
         '02062004 MsgBox "term=" + term
         '02062004  End If
         
         
         parse_opt_paren                'inserted 02062004
         get_term
         If term = "_end-line" Then SYNTAX
         If termType <> 13 Then print_err gStringTable(3402) '"Expecting a database name"
         out_one_integ theTermDe_no    'put out database number
         
            i = 1
            For Each dbdef In gTarget.DatabaseCollection
                
                If i = theTermDe_no Then
                   GoTo foundDbName
                End If
                i = i + 1
            Next
            MsgBox gStringTable(3403) '"Internal error -- can't find database from number"
            
foundDbName:
         Do While (1)
            get_term
            '02062004 If term = "_end-line" Then Syntax
            If (term = "_end-line" Or term = "where") And verb_had_paren = False Then 'inserted 02062004
               term_used = 0                             'inserted 02062004
               Exit Do                                   'inserted 02062004
            End If                                       'inserted 02062004
            If term = ")" And verb_had_paren = True Then Exit Do 'modified 02062004
             
            If theTermMaj <> "d" Then print_err gStringTable(3404) '"Expecting a database field"
            'n = Instr$(1, se.term, ".")
            'If n = 0 Then print_err ("Expecting field of database (must use format recname.fieldName)")
            'parentName = mid$(se.term, 1, n - 1)
            'fieldName = mid$(se.term, n + 1, Len(se.term) - n)
      
            'Set typ = locate_typedef(parentName)
            'If typ Is Nothing Then print_err "dbFieldName has an incorrect database record prefix"
            'For Each t In typ.elements
            '    If t.name = fieldName Then GoTo foundIt
            'Next
            'print_err "dbFieldName is not a member of db record definition"
foundIt:

'MsgBox "dbdef.firstFldNo=" & dbdef.firstDbFldNo & "  thisFldNo=" & theTermDe_no
            
            '02042004 out_one_integ (theTermDe_no - dbdef.firstDbFldNo) 'put out rel# of fld in rec layout
            'start insertions 02042004
            'want to put out the fld no within db definition, but because keyField is outside the
            'record layout, the logic gets messy
            If dbdef.keyFieldTblNo = 0 Then
               out_one_integ (theTermDe_no - dbdef.firstDbFldNo) 'put out rel# of fld in rec layout
            Else
               'db is keyed, so must take diff paths if binding to keyField or not.
               'even if not, colNo is one > normal because keyfld must be counted too
               If theTermDe_no = dbdef.keyFieldTblNo Then
                  out_one_integ (0) 'keyfield is fld# 0
               Else
                  out_one_integ (theTermDe_no - dbdef.firstDbFldNo) + 1 'put out rel# of fld in rec layout plus 1 for keyfield
               End If
            End If
            'end insertions 02042004
         Loop
         out_one_integ (1000)    'end of list of db fields
         get_term
         If term = "_end-line" Then GoTo allDone
         If Not term = "where" Then SYNTAX
         
         out_one_char (&H5C) 'put out opCode for where clause
     
          
         term = "=" + Trim$(str$(parag_tbl_no + 1))
         add_to_para_tbl
         If (if_level = max_if_lvls) Then
             print_err gStringTable(3405) '"Statement too complicated -- please simplify.")
             Exit Sub
         End If
         
         if_level = if_level + 1
         para_false_ptr(if_level) = p.tbl_no
         
         if_was_elseif(if_level) = 0
         out_one_integ (p.tbl_no)
              
         logic_exp_gen     'parse the conditional clause
         out_one_char (&H5D) 'opcode for end of where clause
         out_one_integ (log_work_var_no) 'result log var of conditional expr
     
         get_term  'get past the log var
                 
         Set p = loc_para_ptr(para_false_ptr(if_level))
         p.offset = proc_offset
         p.defined = 1
         if_level = if_level - 1
allDone:
'dbugDump
    'end of additions 09242003
         'If paren_sw Then
         '      get_term
         '      If term <> ")" Then Syntax
         'End If
  End Select
    
End Sub

Sub parse_popupClear()
  parse_opt_paren
  get_controlName "pop"
  controlId = controlId + 1
  out_one_char (&H6)
  out_one_integ (controlId)
End Sub
Sub parse_listclear()
  'If editor Source = "p" Or editor Source = "w" Or editor Source = "v" Then  'removed 6.6.2000 GH
  '   print_err "The ListClear command cannot be used in" + chr$(10) + chr$(13) + "a form before script. Place this command in the after script."
  'End If

  parse_opt_paren
  get_controlName "lst"
  controlId = controlId
  out_one_char (&H4D)
  out_one_integ (controlId)
End Sub
Sub addItemCommon()
  get_dataname_string  'the item text
  set_arg_1
  get_term
  If term = "_end-line" Or term = "nodisplay" Then
     term_used = 0
     Set d2 = dataelem_null_ptr
    arg_2 = 0
    arg2_occ1 = 0
    arg2_occ2 = 0
    arg2_occ3 = 0
  Else
     term_used = 0
     get_dataname_num  'index where to insert
     set_arg_2
  End If
  out_one_char (&H34)
  out_one_integ (controlId)
  out_2arg
  If new_term_is("nodisplay") Then
     out_one_char (&H0)
  Else
     term_used = 0
     out_one_char (&H1)
  End If
  
End Sub
Sub parse_listDeleteItem()
  parse_opt_paren
  get_controlName "lst"
  controlId = controlId
  deleteItemCommon
End Sub
Sub parse_popupDeleteItem()
  parse_opt_paren
  get_controlName "pop"
  controlId = controlId + 1
  
  deleteItemCommon
End Sub
Sub deleteItemCommon()
  get_dataname_num  'index where to delete
  set_arg_2
  out_one_char (&H35)
  out_one_integ (controlId)
  out_the_2cnd_arg
End Sub
Sub parse_listSetSelected()
  parse_opt_paren
  get_controlName "lst"
  setSelectedCommon
End Sub
Sub parse_popupSetSelected()
  parse_opt_paren
  get_controlName "pop"
  controlId = controlId + 1
  setSelectedCommon
End Sub
Sub setSelectedCommon()
  get_dataname_num  'index to select
  set_arg_2
  out_one_char (&H36)
  out_one_integ (controlId)
  out_the_2cnd_arg
End Sub
Sub parse_scrollbarsetcurrent()
  parse_opt_paren
  
  get_controlName "scr"
  get_dataname_num  'index to select
  set_arg_2
  out_one_char (&H3F)
  out_one_char (&H1)
  out_one_integ (controlId)
  out_the_2cnd_arg
End Sub
Sub parse_scrollbarsetmin()
  parse_opt_paren
  get_controlName "scr"
  get_dataname_num  'index to select
  set_arg_2
  out_one_char (&H3F)
  out_one_char (&H2)
  out_one_integ (controlId)
  out_the_2cnd_arg
End Sub
Sub parse_scrollbarsetmax()
  parse_opt_paren
  get_controlName "scr"
  get_dataname_num  'index to select
  set_arg_2
  out_one_char (&H3F)
  out_one_char (&H3)
  out_one_integ (controlId)
  out_the_2cnd_arg
End Sub
Sub parse_scrollbarsetpagesize()
  parse_opt_paren
  get_controlName "scr"
  get_dataname_num  'index to select
  set_arg_2
  out_one_char (&H3F)
  out_one_char (&H4)
  out_one_integ (controlId)
  out_the_2cnd_arg
End Sub



Sub get_controlName(t As String)
  
  
  get_term
'sgBox "at ctlname term=" + term + "  type=" + str$(termType)
  SearchControlName t
End Sub
Sub SearchControlName(t As String)
Dim view2 As CForm

   If Not ALPHALIT Then SYNTAX 199
   For Each view2 In gTarget.FormCollection
      For Each o In view2.ObjectCollection
         If LCase$(o.obj.Name) = LCase$(term) Then
            controlId = o.obj.IdNo
            Set controlObj = o
            If Not t = "" Then
               If Not t = o.obj.Kind Then
                  print_err gStringTable(3219) '"Object type does not support this action."
               End If
            End If
            Exit Sub
         End If
      Next
   Next
   print_err gStringTable(3220) '"Can't locate a control that matches name"
End Sub

Sub parse_opt_paren()
   get_term
   If term_is("(") Then
      verb_had_paren = True
   Else
      term_used = 0
      verb_had_paren = False
   End If
End Sub

Public Function ReplaceQuotes(txt As String) As String
   Dim i As Integer
   Dim wk As String

   wk = txt
   For i = 1 To Len(txt)
      If Asc(Mid$(wk, i, 1)) = 34 Then Mid$(wk, i, i) = Chr$(39)
   Next
   ReplaceQuotes = wk
End Function

Function locate_type_def(who As String) As CTypeDef
   Dim t As CTypeDef

   For Each t In gTarget.TypeDefCollection
 'sgBox "locatetypedef comparing=" + t.name + " to=" + who
     If LCase$(t.Name) = LCase$(who) Then
        Set locate_type_def = t
        Exit Function
     End If
   Next
   Set locate_type_def = Nothing
End Function

Sub strip_and_locate_data_tbl()
   term = Right$(term, Len(term) - 1)
   locate_data_tbl
End Sub

Sub PutOutTypeDefArgs(t As CTypeElem, data As CDataElement, s1_tbl_no As Integer, s2_tbl_no As Integer, s3_tbl_no As Integer, cnt As Integer)
   'new 805  all of this sub
   Dim wk As String
   
          
          wk = Right$(data.Name, Len(data.Name) - 2) + "." _
          + Right$(t.Name, Len(t.Name) - InStr(1, t.Name, ".", 0))
'sgBox "call searching for x=" + wk
          Set d1 = locateDataByName(wk)
'sgBox "call -- adding arg=" + wk + "/" + d1.name + "  kind=" + d1.kind
          'If d1.max_no_values1 < 2 Then 'no element subs
            If (d1.max_no_values1 > 1 And s3_tbl_no > 0) _
            Or (d1.max_no_values2 > 1 And s2_tbl_no > 0) _
            Or (d1.max_no_values3 > 1 And s1_tbl_no > 0) Then
               print_err gStringTable(3221) '"Too many levels of subscripting with CTypeDef."
            End If
            arg_1 = d1.tbl_no
            arg1_occ1 = s1_tbl_no 'use subscripts of DATA
            arg1_occ2 = s2_tbl_no
            arg1_occ3 = s3_tbl_no
            out_1arg
            cnt = cnt + 1
End Sub

Public Sub CheckSerialNumber()
Dim serNo As Long
#If NSBSymbian Then
   serNo = CheckSerial(glSerialNumber, 4)
   If serNo = 64 Then serNo = 0 'stolen card - zorro08@gmail.com
   If serNo = 79 Then serNo = 0 'duplicate order Klaus Erfurth
   If serNo = 113 Then serNo = 0 'stolen card - flashcheck1@gmail.com
#Else
   serNo = CheckSerial(glSerialNumber, 1)
   If serNo = 7683 Then serNo = 0 'pirated number - Boris Belfer
   If serNo = 9138 Then serNo = 0 'believed to be pirate - Jimmy Canoly
   If serNo = 9353 Then serNo = 0 'stolen card. japplegate@merseymail.com
   If serNo = 9311 Then serNo = 0 'stolen card. yuliya86@yahoo.com
   If serNo = 3311 Then serNo = 0 'believed to be pirated by s.kani
#End If
If serNo > 0 Then
   'MsgBox "checkSerialNumber() serno>0"
   LitePro = "p"
   DemoSw = "n"
Else
   'MsgBox "checkSerialNumber() serno=0"
   LitePro = "l"
   DemoSw = "y"
   glSerialNumber = "Unregistered Demo"
End If
End Sub

'***added this subroutine 3/13/2001 **************************************
Sub out_unsigned_integ(i As Long)
   'outputs up to 65k as two-byte unsigned int
   Dim m1 As Byte
   Dim m2 As Byte
   Dim wk As Long
   
   If i > CLng(65536) Then print_err gStringTable(3221) '"Program has exceeded size limitations "
   m1 = Int(i / 256)
   wk = m1
   wk = wk * 256
   m2 = Int(i - wk)
   
   out_one_char m1
   out_one_char m2
End Sub                '***end of code additions 3/13/2001

'***this entire routine new 3/13/2001***
Sub writeOutUnsignedInteger(f As Integer, i As Long)
   Dim m1 As Byte
   Dim m2 As Byte
   Dim wk As Long
   
   If i > CLng(65536) Then print_err gStringTable(3221) '"Program has exceeded size limitations "
   m1 = Int(i / 256)
   wk = m1
   wk = wk * 256
   m2 = Int(i - wk)
   
   writeOutByte f, m1
   writeOutByte f, m2
End Sub                '***end of additions 3/13/2001
Sub parse_signaturestartcapture()   '*** routine added 4/30/2001 *************
  parse_opt_paren
  get_controlName "gad"
  out_one_char (&H76)
  out_one_integ (controlId)
End Sub
Sub parse_signatureerase()          '*** routine added 4/30/2001 *************
  parse_opt_paren
  get_controlName "gad"
  out_one_char (&H75)
  out_one_integ (controlId)
End Sub
Sub parse_signaturedisplay()        '*** routine added 4/30/2001 *************
  parse_opt_paren
  get_controlName "gad"
  out_one_char (&H77)
  out_one_integ (controlId)
  
  get_dataname_string
  set_arg_1
  out_the_1st_arg
End Sub
Sub func_gadEndCapture()
   Dim a As CSynElem
   Dim b As CSynElem
   Dim c As CSynElem
   Dim z As CSynElem
   Dim valu1 As CDataElement
   Dim temp As CSynElem
   Set a = se     'func name
   Set b = se.Nxt 'leftparen
   Set c = b.Nxt  'control name
   Set z = c.Nxt  'right paren
   Set valu1 = find_de_by_no(c.de_no)
   If Not c.maj = "d" Or Not valu1.Kind = "s" Then
        Set se = c
        arith_syntax_err
        Exit Sub
    End If
   gen_alloc_string_work
   arg_1 = string_work_de_no
   arg1_occ1 = 0
   arg1_occ2 = 0
   arg1_occ3 = 0
'sgBox "in end capture 418"
    out_one_char (func_token)
    out_one_integ (se.sub1)
    out_one_integ (0) '/*no args*/
    out_the_1st_arg
   
   If b.maj = "p" And b.sub1 = 0 Then
   Else
      Set se = b
      SYNTAX 200
   End If
   If z.maj = "p" And z.sub1 = 1 Then
   Else
        Set se = z
        SYNTAX 201
   End If
   func_findctlname c
   out_one_integ (controlId)
    
    delete_syn_elem a
    delete_syn_elem b
    delete_syn_elem c
    z.de_no = arg_1
    z.term = ""
    z.termType = 4
    z.maj = "d"
    z.sub1 = 0
    z.sub2 = 0
    z.sub3 = 0
    
    Set se = z
End Sub
Public Sub CollectFuncs()
'this collects all functions and returns DEFINE statements for them
Dim cMod As CCodeModule
Dim frm As CForm
Dim ob As Object
gDefineStmts = "define settheme as integer" & vbCrLf
gFirstSubName = ""
ShowStatus "Collecting Function Definitions"
   
   If gTarget.pgm_script <> "" Then
      CollectFuncsInCode gTarget.pgm_script, True
   End If
   If gFirstSubName = "" Then gFirstSubName = "No Startup Code"
   
   If gTarget.termination_script <> "" Then
      CollectFuncsInCode gTarget.termination_script, False
   End If
   For Each cMod In gTarget.CodeCollection
      If cMod.pgm_script <> "" Then CollectFuncsInCode cMod.pgm_script, False
   Next
   For Each frm In gTarget.FormCollection
      If frm.pgm_script <> "" Then CollectFuncsInCode frm.pgm_script, False
      If frm.pgm_script_after <> "" Then CollectFuncsInCode frm.pgm_script_after, False
      If frm.event_script <> "" Then CollectFuncsInCode frm.event_script, False
      
      For Each ob In frm.ObjectCollection
         If ob.obj.script <> "" Then CollectFuncsInCode ob.obj.script, False
      Next
   Next
   'For Each cMod In gTarget.CodeCollection  '07.05.2005 GWH - duplicates code above
   '   If cMod.pgm_script <> "" Then CollectFuncsInCode cMod.pgm_script, False
   'Next
   'MsgBox gDefineStmts
End Sub
Private Sub CollectFuncsInCode(script As String, startupScript As Boolean)
   Dim i As Long
   Dim j As Long
   Dim stmt As String
   
   i = 1
   Do While i < Len(script)
      j = InStr(i, script, Chr$(10))
      If Not j = 0 Then
         CollectFuncsOnList Trim$(Mid$(script, i, j - i)), startupScript
           i = j + 1
      Else
         CollectFuncsOnList Trim$(Mid$(script, i, Len(script) - i + 1)), startupScript
        Exit Do
      End If
   Loop
End Sub
Private Sub CollectFuncsOnList(stmt As String, startupScript As Boolean)
Dim p1 As Long
Dim p2 As Long

   stmt = Trim$(LCase$(stmt))
   If gFirstSubName = "" And startupScript Then 'get name of first subroutine - it's the startup code
      If Left$(stmt, 4) = "sub " Then
         p1 = InStr(1, stmt, "(")
         gFirstSubName = Trim$(Mid$(stmt, 5, p1 - 5))
      End If
   End If
   
   If Left$(stmt, 9) <> "function " Then Exit Sub
   'If gFirstSubName = "" Then gFirstSubName = "No Startup Code"
   stmt = "define" & Mid$(stmt, 9)
   p1 = InStr(1, stmt, "(")
   For p2 = Len(stmt) To 1 Step -1
      If Mid$(stmt, p2, 1) = ")" Then Exit For
   Next
   If p1 <= 2 Or p2 <= 2 Then Exit Sub
   
   stmt = Left$(stmt, p1 - 1) & Mid$(stmt, p2 + 1)
   If InStr(1, stmt, " as ") = 0 Then Exit Sub  'missing AS clause
   If InStr(1, stmt, " datediff ") Then print_err gStringTable(3367)  'DateDiff is a reserved word and cannot be used as a function name.
   If InStr(1, stmt, " timediff ") Then print_err gStringTable(3368)  'TimeDiff is a reserved word and cannot be used as a function name.
   
   gDefineStmts = gDefineStmts & stmt
End Sub
Private Function DefineFuncsInStartupCode(codeIn As String) As String
Dim i As Long
Dim themeCode As String
Dim p As Integer
Dim theme As String

   theme = gTarget.theme
   p = InStrRev(theme, "\")
   If p > 0 Then theme = Mid(theme, p + 1) 'trim to get just theme name
   theme = Left(theme, Len(theme) - 4)
   themeCode = "SetTheme(" & Chr(34) & theme & Chr(34) & ")" & vbCrLf
   
   'add Define statements in the project startup code automatically
   If gFirstSubName = "No Startup Code" Then 'startup code is blank
      codeIn = "Sub Project_startup()" & vbCr & gDefineStmts & themeCode & "End Sub" & vbCr & codeIn
   Else
      'name of sub is first line that starts with sub
      i = InStr(1, LCase$(codeIn), "sub " & gFirstSubName & "()")
      If i = 0 Then 'startup code has no Sub Project_Startup
         print_err gStringTable(3369) '"Startup SUB statement not formatted properly."
      Else
         i = InStr(i, codeIn, Chr$(10))
         codeIn = Left$(codeIn, i) & gDefineStmts & themeCode & Mid$(codeIn, i)
      End If
   End If
   DefineFuncsInStartupCode = codeIn
End Function
Private Function DefineSetThemeFunction() As String
Dim s As String
 s = "Function SetTheme(filename as string) as Integer" & vbCrLf
 s = s & "Dim ResTypeInt as Integer" & vbCrLf
 s = s & "Dim ResID as Short" & vbCrLf
 s = s & "Dim ResSize as Integer" & vbCrLf
 s = s & "Dim resH as Variant" & vbCrLf
 s = s & "Dim PrefsDB as Variant" & vbCrLf
 s = s & "Dim dstP as Variant" & vbCrLf
 s = s & "Dim theme as String" & vbCrLf
 s = s & "Dim saved as Short" & vbCrLf
 s = s & "Dim i as Short" & vbCrLf
 s = s & "Dim which as Short" & vbCrLf
 s = s & "Dim color as String" & vbCrLf
 #If NSBSymbian = 0 Then
 s = s & "If sysinfo(6)<35 Then Exit Function" & vbCrLf
 #End If
 s = s & "ResID = 25" & vbCrLf
 s = s & "ResSize = 124" & vbCrLf
 s = s & "saved = 256 'boolean True" & vbCrLf
 s = s & "ResTypeInt=1886615923 'psys" & vbCrLf
 s = s & "Dim db as Database" & vbCrLf
 #If NSBSymbian = 0 Then
 s = s & dbCreateDatases
 #End If
 s = s & "SetTheme=dbopen(db, filename, 0)" & vbCrLf
 s = s & "If SetTheme<>0 then Exit Function" & vbCrLf
 s = s & "SetTheme=dbposition(db,1,0)" & vbCrLf
 s = s & "SetTheme=dbget(db, theme)" & vbCrLf
 s = s & "If SetTheme<>0 Then MsgBox str(2000+SetTheme) & "" dbRead Theme""" & vbCrLf
 s = s & "dbclose(db)" & vbCrLf
 #If NSBSymbian = 1 Then 'only need to do this while running StyleTap
 s = s & "PrefsDB  = SysTrapFunc(736,1, saved)         'PrefOpenPreferenceDB" & vbCrLf
 s = s & "resH = SysTrapFunc(95, 2, ResTypeInt, ResID) 'DmGetResource" & vbCrLf
 s = s & "If resH=0 Then resH = SysTrapFunc(108,4, PrefsDB, ResTypeInt, ResID, ResSize) 'DmNewResource" & vbCrLf
 s = s & "dstP = SysTrapFunc(33,1,ResH)                'MemHandleLock" & vbCrLf
 s = s & "SysTrapSub 118, 4, dstP, 0, theme, ResSize   'DMWrite" & vbCrLf
 s = s & "SetTheme = SysTrapFunc(34,1,resH)            'MemHandleUnlock " & vbCrLf
 s = s & "SetTheme = SysTrapFunc(97,1,resH)            'DmReleaseResource" & vbCrLf
 s = s & "SetTheme = systrapfunc(74,1,PrefsDB)         'DmCloseDatabase" & vbCrLf
 #End If
 s = s & "For i=0 to 29" & vbCrLf '0 to 29
 s = s & "  which=i*256" & vbCrLf
 s = s & "  color=mid(theme, i*4+5, 4)" & vbCrLf
 's = s & "  msgbox str(i) & str(asc(mid(color,1,1))) & str(asc(mid(color,2,1))) & str(asc(mid(color,3,1))) & str(asc(mid(color,4,1)))" & vbCrLf
 s = s & "  setTheme = sysTrapFunc(934, 2, which, color) 'UIColorSetTableEntry   " & vbCrLf
 s = s & "Next" & vbCrLf
 s = s & "End Function" & vbCrLf
 
DefineSetThemeFunction = s
'MsgBox s
End Function
Private Function dbCreateDatases() As String
Dim s As String
Dim res As CResourceFile

   'Palm does not automatically extract theme files, so it has to be done here.
   For Each res In gTarget.ResourceCollection
      If res.ResourceType = "DBIM" Then
         s = s & "SetTheme=dbCreateDatabaseFromResource(""" & res.ResourceType & """," & res.IdNo & ")" & vbCrLf
      End If
   Next
   dbCreateDatases = s
End Function

Public Sub addThemeToResources()
   Dim path As String
   Dim Name As String
   Dim filename As String
   Dim res As CResourceFile
   Dim newOne As Boolean
   Dim s As String
   
   path = gTarget.theme
   filename = Mid(path, InStrRev(path, "\") + 1) 'trim left
   Name = Left(filename, Len(filename) - 4) 'trim right
   newOne = True
   'is the theme already a resource?
   For Each res In gTarget.ResourceCollection
      If res.Name = Name Then newOne = False
   Next
   If newOne Then
      Set res = createNewResource(Name, filename, "DBIM", path)
      gfProjectExplorer.AddNewResource res, gTarget
      DoEvents
   End If
End Sub
Public Function createNewResource(Name As String, filename As String, resType As String, path As String) As CResourceFile
   Dim resource As CResourceFile
   
   'Is this resource already in the project?
   For Each resource In gTarget.ResourceCollection
      If LCase(resource.filename) = LCase(filename) Then Exit Function
   Next
   
   Set resource = New CResourceFile
   
   resource.filename = filename
   resource.ResourceType = resType
   resource.ResourcePath = path
   resource.IdNo = gTarget.GetNextSeqNo
   resource.Name = Name
   gTarget.ResourceCollection.Add resource
   resource.Project = gTarget
   If gbProjectExplorer Then gfProjectExplorer.UpdateObjectNode resource, resource.GlobalID
   Set createNewResource = resource
End Function
