Attribute VB_Name = "modAPI"
Option Explicit

Type RECT
    Left As Long
    Top As Long
    Right As Long
    Bottom As Long
End Type

Type POINTAPI
    x As Long
    y As Long
End Type

Type Msg
   hwnd As Long
   message As Long
   wParam As Long
   lParam As Long
   Time As Long
   pt As POINTAPI
End Type

Type NMHDR
   hwndFrom As Long
   idfrom As Long
   code As Long
End Type

Type ToolTipText
   hdr As NMHDR
   lpszText As Long
   szText As String * 80
   hInst As Long
   uFlags As Long
End Type

Public Type MINMAXINFO
   ptReserved As POINTAPI
   ptMaxSize As POINTAPI
   ptMaxPosition As POINTAPI
   ptMinTrackSize As POINTAPI
   ptMaxTrackSize As POINTAPI
End Type

Public gHWndToolTip As Long

Public Type TOOLINFO
   cbSize As Long
   uFlags As Long
   hwnd As Long
   uId As Long
   rct As RECT
   hInst As Long
   lpszText As Long
End Type

Public Declare Function GetParent Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function SetParent Lib "user32" (ByVal hWndChild As Long, ByVal hWndNewParent As Long) As Long
Public Declare Function GetWindowRect Lib "user32" (ByVal hwnd As Long, lpRect As RECT) As Long
Public Declare Function ScreenToClient Lib "user32" (ByVal hwnd As Long, lpPoint As POINTAPI) As Long
Public Declare Sub GetCursorPos Lib "user32" (lpPoint As POINTAPI)

Public Declare Function MoveWindow Lib "user32" (ByVal hwnd As Long, ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal bRepaint As Long) As Long
Public Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Public Declare Function SendMessageLong Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Public Declare Function SendMessageString Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As String) As Long
Public Declare Function GetWindow Lib "user32" (ByVal hwnd As Long, ByVal wCmd As Long) As Long
Public Declare Function UpdateWindow Lib "user32" (ByVal hwnd As Long) As Long
#If UNICODE Then
Public Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongW" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Any) As Long
Public Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongW" (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Public Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcW" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
#Else
Public Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Any) As Long
Public Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Public Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
#End If
Public Declare Function GetSystemMetrics Lib "user32" (ByVal nIndex As Long) As Long
Public Const SM_CXVSCROLL = 2


Declare Function FindWindowEx Lib "user32" Alias "FindWindowExA" (ByVal hWnd1 As Long, ByVal hWnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long


   
'Declare constants used by GetWindow.
Public Const GW_CHILD = 5
Public Const GW_HWNDFIRST = 0
Public Const GW_HWNDLAST = 1
Public Const GW_HWNDNEXT = 2
Public Const GW_HWNDPREV = 3
Public Const GW_OWNER = 4

'Dialog Internal Controls
Public Const fdlgChxReadOnly = &H410
Public Const fdlgcmbSaveAsType = &H470
Public Const fdlgCmbSaveInFindIn = &H471
Public Const fdlgEdtFileName = &H480
Public Const fdlgIDCANCEL = 2
Public Const fdlgIDOK = 1
Public Const fdlgLBLstFiles = &H460
Public Const fdlgLVLstFiles = &H461
Public Const fdlgPshHelp = &H40E
Public Const fdlgStcFileName = &H442
Public Const fdlgStcSaveAsType = &H441
Public Const fdlgStcSaveInFindIn = &H443

Public Const SWP_NOSIZE = &H1
Public Const SWP_NOMOVE = &H2
Public Const SWP_NOZORDER = &H4
Public Const SWP_NOREDRAW = &H8
Public Const SWP_NOACTIVATE = &H10
Public Const SWP_FRAMECHANGED = &H20
Public Const SWP_SHOWWINDOW = &H40
Public Const SWP_HIDEWINDOW = &H80
Public Const SWP_NOCOPYBITS = &H100
Public Const SWP_NOOWNERZORDER = &H200
Public Const SWP_DRAWFRAME = SWP_FRAMECHANGED
Public Const SWP_NOREPOSITION = SWP_NOOWNERZORDER

Public Const SWP_MOVEHIDE = SWP_NOSIZE Or SWP_HIDEWINDOW

'Key Const
Public Const VK_TAB = &H9
Public Const VK_SHIFT = &H10
Public Const VK_CONTROL = &H11

'Traps Alter Key
Public Const KBH_MASK = &H20000000

'Hook Const
Public Const WH_KEYBOARD = 2

'For Trapping Tab Key on Dialog Box
Declare Function CallNextHookEx Lib "user32" (ByVal hHook As Long, ByVal nCode As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Declare Function UnhookWindowsHookEx Lib "user32" (ByVal hHook As Long) As Long
Declare Function SetWindowsHookEx Lib "user32" Alias "SetWindowsHookExA" (ByVal idHook As Long, ByVal lpfn As Long, ByVal hmod As Long, ByVal dwThreadId As Long) As Long

Declare Function PostMessage Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Declare Function EnableWindow Lib "user32" (ByVal hwnd As Long, ByVal fEnable As Long) As Long
Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal x As Long, ByVal y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long
Declare Function GetKeyState Lib "user32" (ByVal nVirtKey As Long) As Integer
Declare Function GetFocusAPI Lib "user32" Alias "GetFocus" () As Long
Declare Function SetFocusAPI Lib "user32" Alias "SetFocus" (ByVal hwnd As Long) As Long
Declare Function GetDlgItem Lib "user32" (ByVal hDlg As Long, ByVal nIDDlgItem As Long) As Long
Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Integer, ByVal lParam As Integer) As Long
Declare Function SetDlgItemText& Lib "user32" Alias "SetDlgItemTextA" (ByVal hDlg As Long, ByVal nIDDlgItem As Long, ByVal lpString As String)
Declare Function GetDlgItemText& Lib "user32" Alias "GetDlgItemTextA" (ByVal hDlg As Long, ByVal nIDDlgItem As Long, ByVal lpString As String, ByVal nMaxCount As Long)
Declare Function SetDlgItemInt& Lib "user32" (ByVal hDlg As Long, ByVal nIDDlgItem As Long, ByVal wValue As Long, ByVal bSigned As Long)

Public Const WM_CLOSE = &H10&
Public Const WM_COMMAND = &H111&
Public Const WM_USER = &H400&
Public Const HWND_TOPMOST = -1

Public Const CDM_FIRST = (WM_USER + 100)
Public Const CDM_GETFILEPATH = (CDM_FIRST + &H1)

Public Const MAX_PATH = 260

'Extended Window Constants
Public Const WS_EX_TOPMOST = &H8
Public Const WS_EX_TRANSPARENT = &H20
Public Const WS_EX_TOOLWINDOW = &H80
Public Const WS_EX_WINDOWEDGE = &H100
Public Const WS_EX_CLINTEDGE = &H200
Public Const WS_EX_CONTROLPARENT = &H10000
Public Const WS_EX_TOOLBOXWINDOW = (WS_EX_WINDOWEDGE Or WS_EX_TOOLWINDOW Or WS_EX_TOPMOST)
' Public Const WS_EX_TRANSPARENT = &H20&
Public Const WS_EX_NOPARENTNOTIFY = &H4&
'Public Const WS_DLGFRAME = &H400000
Public Const WS_OVERLAPPED = &H0&
Public Const WS_CAPTION = &HC00000
Public Const WS_MAXIMIZEBOX = &H10000
Public Const WS_MINIMIZEBOX = &H20000
Public Const WS_SYSMENU = &H80000
Public Const WS_THICKFRAME = &H40000
Public Const WS_VISIBLE = &H10000000
Public Const WS_OVERLAPPEDWINDOW = (WS_OVERLAPPED Or WS_CAPTION Or WS_SYSMENU Or WS_THICKFRAME Or WS_MINIMIZEBOX Or WS_MAXIMIZEBOX)
Public Const DS_MODALFRAME = &H80
Public Const GWL_EXSTYLE As Long = (-20)
Public Const GWL_WNDPROC As Long = (-4&)
Public Const WS_CLIPCHILDREN = &H2000000
Public Const WS_CLIPSIBLINGS = &H4000000
Public Const WS_VSCROLL = &H200000

Public Const WM_ACTIVATE = &H6
Public Const WM_NCACTIVATE = &H86
Public Const WM_NCHITTEST = &H84
Public Const WM_WINDOWPOSCHANGING = &H46
Public Const WM_KILLFOCUS = &H8
Public Const WM_PAINT = &HF
Public Const WM_NCPAINT = &H85
Public Const WM_GETDLGCODE = &H87
Public Const WM_NCMOUSEMOVE = &HA0
Public Const WM_NCLBUTTONDOWN = &HA1
Public Const WM_NCLBUTTONUP = &HA2
Public Const WM_NCLBUTTONDBLCLK = &HA3
Public Const WM_NCRBUTTONDOWN = &HA4
Public Const WM_NCRBUTTONUP = &HA5
Public Const WM_NCRBUTTONDBLCLK = &HA6
Public Const WM_NCMBUTTONDOWN = &HA7
Public Const WM_NCMBUTTONUP = &HA8
Public Const WM_NCMBUTTONDBLCLK = &HA9
Public Const WM_SYSCOMMAND = &H112
Public Const WM_EXITSIZEMOVE = &H232
Public Const WM_LBUTTONDBLCLK = &H203
Public Const WM_GETMINMAXINFO = &H24
Public Const WM_MOUSEMOVE = &H200
Public Const WM_LBUTTONDOWN = &H201
Public Const WM_LBUTTONUP = &H202
Public Const WM_RBUTTONDOWN = &H204
Public Const WM_RBUTTONUP = &H205
Public Const WM_MBUTTONDOWN = &H207
Public Const WM_MBUTTONUP = &H208
Public Const WM_NOTIFY = &H4E

Public Const TTM_RELAYEVENT = (WM_USER + 7)

'ToolTip Notification
Public Const H_MAX As Long = &HFFFFFFFF + 1
Public Const TTN_FIRST = (H_MAX - 520&)
#If UNICODE Then
  Public Const TTN_NEEDTEXTW = (TTN_FIRST - 10&)
  Public Const TTN_NEEDTEXT = TTN_NEEDTEXTW
#Else
  Public Const TTN_NEEDTEXTA = (TTN_FIRST - 0&)
  Public Const TTN_NEEDTEXT = TTN_NEEDTEXTA
#End If

Private m_hKeyHook  As Long

'Declarations for web access
Private Const SW_SHOW = 5       ' Displays Window in its current size
                                      ' and position
Private Const SW_SHOWNORMAL = 1 ' Restores Window if Minimized or
                                      ' Maximized

Private Declare Function ShellExecute Lib "shell32.dll" Alias _
         "ShellExecuteA" (ByVal hwnd As Long, ByVal lpOperation As _
         String, ByVal lpFile As String, ByVal lpParameters As String, _
         ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long
Private Declare Function FindExecutable Lib "shell32.dll" Alias _
         "FindExecutableA" (ByVal lpFile As String, ByVal lpDirectory As _
         String, ByVal lpResult As String) As Long


Public Sub InstallHook()
   If m_hKeyHook = 0 Then
      m_hKeyHook = SetWindowsHookEx(WH_KEYBOARD, AddressOf TabKeyProc, 0&, App.ThreadID)
   End If
End Sub
Public Sub RemoveHook()
   If m_hKeyHook <> 0 Then
      UnhookWindowsHookEx m_hKeyHook
      m_hKeyHook = 0
   End If
End Sub

Public Property Get GetCDlgFileName(ByVal hDlg As Long) As String
Dim sBuf As String
Dim iPos As Long
Dim hwnd As Long
   hwnd = GetParent(hDlg)
   sBuf = String$(MAX_PATH, 0)
   SendMessageString hwnd, CDM_GETFILEPATH, 260, sBuf
   iPos = InStr(sBuf, vbNullChar)
   If iPos > 0 Then
      GetCDlgFileName = Left$(sBuf, iPos - 1)
   End If
End Property

Public Function TabKeyProc(ByVal nCode As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
  
 If nCode >= 0 And Not (frmSelProj Is Nothing) Then
  If wParam = 9 Then
      
   If (lParam And &HC0000000) = 0 And (lParam And KBH_MASK) <> 0 Then
    'do nothing
   ElseIf GetKeyState(VK_CONTROL) <= 1 Then
    
    If GetKeyState(VK_SHIFT) < 0 And GetKeyState(VK_TAB) < 0 Then
     If lParam = 135200769 Or lParam = 1208942593 Or lParam = 983041 Or 1074724865 Then
      If frmSelProj.SetBackwardFocus Then
       TabKeyProc = 1&: Exit Function
      End If
     End If

    ElseIf GetKeyState(VK_TAB) < 0 Then
     If lParam = 135200769 Or lParam = 1208942593 Or lParam = 983041 Or 1074724865 Then
      If frmSelProj.SetForwardFocus Then
       TabKeyProc = 1&: Exit Function
      End If
     End If
    
    End If
   
   End If
  
  ElseIf wParam = 13 Then
   If frmSelProj.IsNew Then
    If Not (frmSelProj.lvwNew.SelectedItem Is Nothing) Then
     If frmSelProj.lvwNew.SelectedItem.Text <> "" Then
      frmSelProj.cmdNewOpen.Value = True
      TabKeyProc = 1: Exit Function
     End If
    End If
   End If
  End If
 
 End If
         
 TabKeyProc = CallNextHookEx(m_hKeyHook, nCode, wParam, lParam)
         
End Function
Sub openWebPage(pageName As String)
      
      Dim fileName, Dummy As String
      Dim BrowserExec As String * 255
      Dim RetVal As Long
      Dim FileNumber As Integer

      ' First, create a known, temporary HTML file
      BrowserExec = Space(255)
      fileName = "C:\temphtm.HTM"
      FileNumber = FreeFile                    ' Get unused file number
      Open fileName For Output As #FileNumber  ' Create temp HTML file
          Write #FileNumber, "<HTML> <\HTML>"  ' Output text
      Close #FileNumber                        ' Close file
      ' Then find the application associated with it
      RetVal = FindExecutable(fileName, Dummy, BrowserExec)
      BrowserExec = Trim(BrowserExec)
      ' If an application is found, launch it!
      If RetVal <= 32 Or IsEmpty(BrowserExec) Then ' Error
          MsgBox "Could not find associated Browser", vbExclamation, "Browser Not Found"
      Else
          RetVal = ShellExecute(frmMain.hwnd, "open", BrowserExec, pageName, Dummy, SW_SHOWNORMAL)
          If RetVal <= 32 Then        ' Error
              MsgBox "Web Page not Opened", vbExclamation, "URL Failed"
          End If
      End If
      Kill fileName                   ' delete temp HTML file
End Sub

