Attribute VB_Name = "mKeyboardHook"
Option Explicit

Type RECT
   Left As Long
   Top As Long
   Right As Long
   Bottom As Long
End Type

Type POINTAPI
   X As Long
   Y As Long
End Type

Public Declare Function GetParent Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function SetParent Lib "user32" (ByVal hWndChild As Long, ByVal hWndNewParent As Long) As Long
Public Declare Function GetWindowRect Lib "user32" (ByVal hwnd As Long, lpRect As RECT) As Long
Public Declare Function ScreenToClient Lib "user32" (ByVal hwnd As Long, lpPoint As POINTAPI) As Long

Public Declare Function MoveWindow Lib "user32" (ByVal hwnd As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal bRepaint As Long) As Long
Public Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Public Declare Function SendMessageLong Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Public Declare Function SendMessageString Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As String) As Long
Public Declare Function GetWindow Lib "user32" (ByVal hwnd As Long, ByVal wCmd As Long) As Long

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
Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal X As Long, ByVal Y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long
Declare Function GetKeyState Lib "user32" (ByVal nVirtKey As Long) As Integer
Declare Function GetFocusAPI Lib "user32" Alias "GetFocus" () As Long
Declare Function SetFocusAPI Lib "user32" Alias "SetFocus" (ByVal hwnd As Long) As Long
Declare Function GetDlgItem Lib "user32" (ByVal hDlg As Long, ByVal nIDDlgItem As Long) As Long
Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Integer, ByVal lParam As Any) As Long
Declare Function SetDlgItemText& Lib "user32" Alias "SetDlgItemTextA" (ByVal hDlg As Long, ByVal nIDDlgItem As Long, ByVal lpString As String)
Declare Function GetDlgItemText& Lib "user32" Alias "GetDlgItemTextA" (ByVal hDlg As Long, ByVal nIDDlgItem As Long, ByVal lpString As String, ByVal nMaxCount As Long)
Declare Function SetDlgItemInt& Lib "user32" (ByVal hDlg As Long, ByVal nIDDlgItem As Long, ByVal wValue As Long, ByVal bSigned As Long)
Public Declare Function UpdateWindow Lib "user32" (ByVal hwnd As Long) As Long

Public Const WM_CLOSE = &H10&
Public Const WM_COMMAND = &H111&
Public Const WM_USER = &H400&

Public Const CDM_FIRST = (WM_USER + 100)
Public Const CDM_GETFILEPATH = (CDM_FIRST + &H1)

Public Const MAX_PATH = 260

Private m_hKeyHook  As Long

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
   If nCode >= 0 And Not (frmNew Is Nothing) Then
      If wParam = 9 Then
         If (lParam And &HC0000000) = 0 And (lParam And KBH_MASK) <> 0 Then
            'do nothing
         ElseIf GetKeyState(VK_CONTROL) <= 1 Then
            If GetKeyState(VK_SHIFT) < 0 And GetKeyState(VK_TAB) < 0 Then
               If lParam = 135200769 Or lParam = 1208942593 Or lParam = 983041 Or 1074724865 Then
                  If frmNew.SetBackwardFocus Then
                     TabKeyProc = 1&
                     Exit Function
                  End If
               End If
            ElseIf GetKeyState(VK_TAB) < 0 Then
               If lParam = 135200769 Or lParam = 1208942593 Or lParam = 983041 Or 1074724865 Then
                  If frmNew.SetForwardFocus Then
                     TabKeyProc = 1&
                     Exit Function
                  End If
               End If
            End If
         End If
      ElseIf wParam = 13 Then
         If frmNew.IsNew Then
            If Not (frmNew.lvwNew.SelectedItem Is Nothing) Then
               If frmNew.lvwNew.SelectedItem.Text <> "" Then
                  frmNew.cmdNewOpen.Value = True
                  TabKeyProc = 1: Exit Function
               End If
            End If
         End If
      End If
   End If
   TabKeyProc = CallNextHookEx(m_hKeyHook, nCode, wParam, lParam)
End Function
