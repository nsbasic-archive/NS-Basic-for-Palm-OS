#ifndef __cEncDec
#define __cEncDec

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************
 **                      d e c r y p t D a t a
 ***************************************************************************/
#ifdef ED_COMPILE_DLL
#ifdef ED_DLL_LIB
__declspec (dllexport)
#else
__declspec (dllimport)
#endif 
#endif
int decryptData(char *keyStr, char *encryptedData, char *decryptedData);


/***************************************************************************
 **                      e n c r y p t D a t a
 ***************************************************************************/
#ifdef ED_COMPILE_DLL
#ifdef ED_DLL_LIB
__declspec (dllexport)
#else
__declspec (dllimport)
#endif 
#endif
int encryptData(char *keyStr, char *decryptedData, char *encryptedData);

#ifdef __cplusplus
}
#endif

#endif