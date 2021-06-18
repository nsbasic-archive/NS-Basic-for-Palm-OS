
Declare Function EncryptData Lib "EncDec.dll" _
                                    Alias "_EncryptData@12" _
                                (ByVal KeyStr As String, _
                                 ByVal DecryptedStr as String, _
                                 ByRef EncryptedStr as String) _
                                    As Integer

Declare Function DecryptData Lib "EncDec.dll" _
                                    Alias "_DecryptData@12" _
                                (ByVal KeyStr As String, _
                                 ByVal EncryptedStr as String, _
                                 ByRef DecryptedStr as String) _
                                    As Integer

