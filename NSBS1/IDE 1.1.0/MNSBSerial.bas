Attribute VB_Name = "MNSBSerial"
Option Explicit

#If NSBSymbian Then
Public Function isPro() As Boolean
   If CheckSerial(glSerialNumber, 4) \ 2 = CheckSerial(glSerialNumber, 4) / 2 Then
      isPro = True
   Else
      isPro = False
   End If
End Function
#End If

Public Function CheckSerial(ByVal astrSerial As String, ByRef anProduct As Integer) As Long
Dim nProduct As Integer
Dim nMod As Integer
Dim nCustNum As Long
Dim nPad1 As Integer, nPad2 As Integer
Dim nCheck As Integer
'MsgBox "1: " & astrSerial & " " & anProduct
   ' Prod | Dig4 | Dig3 | Pad1 | Dig0 | Pad2 | Dig2 | Dig1 | Chk
   'Product Code: a-f = Prod #1, g-l = Prod #2, m-r = Prod #3, s-x = Prod #4
   'ModVal:       1-6 = Prod #1, 1-6 = Prod #2, 1-6 = Prod #3, 1-6 = Prod #4
   'Customer # = Dig0Dig1Dig2Dig3Dig4
   '(Pad1 + Dig2Dig1) mod 7 = ModVal
   '(Pad2 + Dig4Dig3) mod 7 = ModVal
   astrSerial = Replace(astrSerial, "-", "")
   If Len(astrSerial) <> 9 Then
      CheckSerial = 0
      Exit Function
   End If
'MsgBox "2: " & astrSerial
   CheckSerial = -1
   nProduct = (Asc(UCase(Left(astrSerial, 1))) - Asc("A"))
'MsgBox "3: " & nProduct
   'Skip check for generic test
   If anProduct = 0 Then
      anProduct = (nProduct \ 6) + 1
   Else
      If (nProduct \ 6) + 1 <> anProduct Then Exit Function
   End If
'MsgBox "4: " & anProduct
   nMod = (nProduct Mod 6) + 1
   nCustNum = Val(Mid(astrSerial, 5, 1) & StrReverse(Mid(astrSerial, 2, 2) & Mid(astrSerial, 7, 2)))
'MsgBox "5: " & nCustNum
   nCheck = (Asc(UCase(Right(astrSerial, 1))) - Asc("A"))
   If nCustNum Mod 23 <> nCheck Then Exit Function
'MsgBox "6: " & nCheck
   nPad1 = Val(Mid(astrSerial, 4, 1))
'MsgBox "7: " & (nPad1 + Val(Mid(astrSerial, 7, 2)))
   If (nPad1 + Val(Mid(astrSerial, 7, 2))) Mod 7 <> nMod Then Exit Function
   nPad2 = Val(Mid(astrSerial, 6, 1))
'MsgBox "8: " & (nPad2 + Val(Mid(astrSerial, 2, 2)))
   If (nPad2 + Val(Mid(astrSerial, 2, 2))) Mod 7 <> nMod Then Exit Function
   CheckSerial = nCustNum
'MsgBox "9: " & CheckSerial
End Function

'anProduct: A number between 1 and 4 that denotes which product (1 = CE, 2 = Palm, ...)
'anCustNum: A number between 1 and 99999 that denotes the user number
   ' Prod | Dig4 | Dig3 | Pad1 | Dig0 | Pad2 | Dig2 | Dig1 | Chk
   'Product Code: a-f = Prod #1, g-l = Prod #2, m-r = Prod #3, s-x = Prod #4
   'ModVal:       1-6 = Prod #1, 1-6 = Prod #2, 1-6 = Prod #3, 1-6 = Prod #4
   'Customer # = Dig0Dig1Dig2Dig3Dig4
   '(Pad1 + Dig2Dig1) mod 7 = ModVal
   '(Pad2 + Dig4Dig3) mod 7 = ModVal
Public Function GenSerial(ByVal anProduct As Integer, ByVal anCustNum As Long) As String
Dim nProduct As Integer
Dim nMod As Integer
Dim strCustNum As String
Dim nPad1 As Integer
Dim nPad2 As Integer

   If anProduct < 1 Or anProduct > 4 Then Exit Function
   nProduct = (anProduct - 1) * 6 + Int(Rnd() * 6)
   nMod = (nProduct Mod 6) + 1
   GenSerial = Chr(Asc("A") + nProduct)
   strCustNum = StrReverse(Right("00000" & CStr(anCustNum), 5))
   GenSerial = GenSerial & Left(strCustNum, 2)
   If Val(Mid(strCustNum, 3, 2)) Mod 7 <= nMod Then
      nPad1 = nMod - Val(Mid(strCustNum, 3, 2)) Mod 7
   Else
      nPad1 = 7 + nMod - Val(Mid(strCustNum, 3, 2)) Mod 7
   End If
   nPad1 = IIf(nPad1 > 2, nPad1, nPad1 + Int(Rnd() * 2) * 7)
   GenSerial = GenSerial & "-" & CStr(nPad1) & Right(strCustNum, 1)
   If Val(Left(strCustNum, 2)) Mod 7 <= nMod Then
      nPad2 = nMod - Val(Left(strCustNum, 2)) Mod 7
   Else
      nPad2 = 7 + nMod - Val(Left(strCustNum, 2)) Mod 7
   End If
   nPad2 = IIf(nPad2 > 2, nPad2, nPad2 + Int(Rnd() * 2) * 7)
   GenSerial = GenSerial & CStr(nPad2) & "-"
   GenSerial = GenSerial & Mid(strCustNum, 3, 2)
   GenSerial = GenSerial & Chr(Asc("A") + anCustNum Mod 23)
End Function
