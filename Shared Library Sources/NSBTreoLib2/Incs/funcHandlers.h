extern Err NSBTreoLibOpen(UInt16 refNum   			)
				SAMPLE_LIB_TRAP(sysLibTrapOpen);
extern Err NSBTreoLibClose(UInt16 refNum  			)
				SAMPLE_LIB_TRAP(sysLibTrapClose);
extern Err NSBTreoLibSleep(UInt16 refNum  			)
				SAMPLE_LIB_TRAP(sysLibTrapSleep);
extern Err NSBTreoLibWake(UInt16 refNum   			)
				SAMPLE_LIB_TRAP(sysLibTrapWake);
extern Err PhoneOn(UInt16 refNum, long *ret 		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 0);
extern Err SignalQuality(UInt16 refNum, long *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 1);
extern Err PhoneType(UInt16 refNum, char *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 2);
extern Err PhoneReady(UInt16 refNum, long *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 3);
extern Err MainNumber(UInt16 refNum, char *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 4);
extern Err NetworkAvailable(UInt16 refNum, long *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 5);
extern Err CallWaiting(UInt16 refNum, long *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 6);
extern Err CallWaitingSet(UInt16 refNum, long whether	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 7);
extern Err OperatorCurName(UInt16 refNum, char *ret		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 8);
extern Err OperatorCurID(UInt16 refNum, char *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 9);
extern Err Provider(UInt16 refNum, char *ret		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 10);
extern Err OperatorCount(UInt16 refNum, long *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 11);
extern Err OperatorName(UInt16 refNum, long which, char *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 12);
extern Err Operator(UInt16 refNum, long which, long type	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 13);
extern Err BookCount(UInt16 refNum, long *ret		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 14);
extern Err BookFirstName(UInt16 refNum, long which, char *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 15);
extern Err BookLastName(UInt16 refNum, long which, char *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 16);
extern Err BookPhoneNumber(UInt16 refNum, long which, char *ret)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 17);
extern Err DialPhone(UInt16 refNum, char *number						)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 18);
extern Err SendSMSMessage(UInt16 refNum, char *nbr, char *name, char *msg)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 19);
extern Err SendEMail(UInt16 refNum, char *addr, char *cc, char *subj, char *msg )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 20);
extern Err Browse(UInt16 refNum, char *msg				)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 21);
extern Err BookReload(UInt16 refNum						)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 22);
extern Err PhoneTurnOn(UInt16 refNum						)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 23);
extern Err TCPIPDropConnection(UInt16 refNum				)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 24);
extern Err Vibrate(UInt16 refNum, long *count				)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 25);
extern Err Blink(UInt16 refNum, long *count				)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 26);
extern Err Roaming(UInt16 refNum, long *count		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 27);
extern Err Software(UInt16 refNum, char *count		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 28);
extern Err Hardware(UInt16 refNum, char *count		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 29);
extern Err ProductName(UInt16 refNum, char *count	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 30);
extern Err SerialNumber(UInt16 refNum, char *count	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 31);
extern Err CarrierID(UInt16 refNum, char *count		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 32);
extern Err ProductRevision(UInt16 refNum, char *count)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 33);
extern Err ROM(UInt16 refNum, char *count			)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 34);
extern Err Firmware(UInt16 refNum, char *count		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 35);
extern Err HTTPOpen(UInt16 refNum, long *result		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 36);
extern Err HTTPClose(UInt16 refNum						)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 37);
extern Err HTTPSendRequest(UInt16 refNum, char *url, long timeInMs, long *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 38);
extern Err KeyboardLocked(UInt16 refNum, long *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 39);
extern Err KeyboardLock(UInt16 refNum, long whether		)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 40);
extern Err HTTPGetHeader(UInt16 refNum, long timeInMs, char *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 41);
extern Err HTTPRead(UInt16 refNum, long size, long timeInMs, char *ret  )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 42);
extern Err HTTPSendPostRequest(UInt16 refNum, char *url, char *postData, long timeInMs, long *ret	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 43);
extern Err HTTPEnd(UInt16 refNum							)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 44);
extern Err GetRingProfile(UInt16 refNum, UInt16 profile, Int16 *vol, Int16 *vib, Int16 *result   )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 45);
extern Err SetRingProfile(UInt16 refNum, UInt16 profile, Int16 vol, Int16 vib, Int16 *result     )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 46);
extern Err GetRoamWarnings(UInt16 refNum, Int16 *result	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 47);
extern Err SetRoamWarnings(UInt16 refNum, UInt16 warnings, Int16 *result	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 48);
extern Err PhonePower(UInt16 refNum, char *offOn, Int16 *result )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 49);
extern Err GetLibRefNum(UInt16 refNum, UInt16 *result	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 50);
extern Err GetRoamMode(UInt16 refNum, Int16 *result 	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 51);
extern Err SetRoamMode(UInt16 refNum, Int16 mode, Int16 *result	)
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 52);
