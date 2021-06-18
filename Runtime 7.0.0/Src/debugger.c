 
#include <PalmOS.h>
#include <FloatMgr.h>
#include <PalmTypes.h>
#include <PalmCompatibility.h>
#include <Field.h>
#include <NetMgr.h>
#include "copy.h"

FieldType * inFieldPtr;
FieldType * outFieldPtr;

UInt16 netlibRefnum;

 NetSocketRef socket;
UInt16 newPortID;
 

char inBufr[2048];
/*********************************************************************
 * Internal Functions
 *********************************************************************/
void verb_netIO_getHostByAddr(char* ipAddress, char* result);
Err subrtn_getAddressByName(char *name,UInt32*address32,char *addressDot) ;
void verb_netIO_getHostByName(char* name, char *result);
 void debuggerSend(char * msg);
 void debuggerGetReturnMessage(char* outputMsg);

void debuggerClose()
{
	Err err;
	NetLibSocketShutdown(netlibRefnum,   socket, 
			netSocketDirBoth, 1000*SysTicksPerSecond(), &err);
			
	 
	
	
						 
//07052005 SysFatalAlert("closing socket");
	NetLibSocketClose(netlibRefnum,socket,1000*SysTicksPerSecond(),&err);
//07052005 SysFatalAlert("closing netlib");
    NetLibClose (netlibRefnum,1);
}

//////////////////////////////////////////
//
void verb_netIO_getHostByAddr(char* ipAddress, char* result)
{
  NetHostInfoType     *infoTypePtr;  //pointer to the portion of the info buffer that contains results of the lookup
  NetHostInfoBufType  infoBuf;       //buffer to contain host info
  NetIPAddr addrToLookup;
  char wk[64];
  char wk2[64];
  Err err; 
  NetSocketAddrINType ad;
                         //error indicator
   
                                         //IP address to look up as xxx.xxx.xxx.xxx
  addrToLookup=NetLibAddrAToIN(netlibRefnum,  //NetLib library address
                              ipAddress);           //convert dot notation addr to 32-bit address
                                    
  ad.family=netSocketAddrINET;
  ad.port=0;
  ad.addr=addrToLookup;


  //ad.addr=NetNToHL(ad.addr); 

//StrPrintF(debug,"addr to lookup=%lu",addrToLookup);
//dbug(debug);

          infoTypePtr=NetLibGetHostByAddr(
                     netlibRefnum,  //NetLib library address
                      (unsigned char*)&ad.addr,               //IP address
                      sizeof(ad.addr),       //length of ip address
                      //(unsigned char *)arg3_val,
                      //StrLen(arg3_val),
                      //(Byte*)&addrToLookup,
                      //4,
                      //netSocketAddrRaw,
                      netSocketAddrINET,     //the type of address
                      &infoBuf,               //where to store the host name on return
                      30*sysTicksPerSecond,  //timeout value
                      &err);                 //where to return error code
  if(infoTypePtr==0)   //an error occurred
  {
      switch(err)
      {
         case netErrTimeout:              StrCopy(wk,"Timeout");break;
         case netErrNotOpen:              StrCopy(wk,"NotOpen");break;
         case netErrDNSNameTooLong:       StrCopy(wk,"DNSNameTooLong");break;  
         case netErrDNSBadName:           StrCopy(wk,"DNSBadName");break;      
         case netErrDNSLabelTooLong:      StrCopy(wk,"DNSLabelTooLong");break;    
         case netErrDNSAllocationFailure: StrCopy(wk,"DNSAllocationFailure");break;    
         case netErrDNSTimeout:           StrCopy(wk,"DNSTimeout");break;    
         case netErrDNSUnreachable:       StrCopy(wk,"DNSUnreachable");break;    
         case netErrDNSFormat:            StrCopy(wk,"DNSFormat");break;    
         case netErrDNSServerFailure:     StrCopy(wk,"DNSServerFailure");break;    
         case netErrDNSNonexistantName:   StrCopy(wk,"DNSNonExistantName");break;    
         case netErrDNSNIY:               StrCopy(wk,"DNSNIY");break;    
         case netErrDNSRefused:           StrCopy(wk,"DNSRefused");break;
         case netErrDNSImpossible:        StrCopy(wk,"DNSImpossible");break;    
         case netErrDNSNoRRS:             StrCopy(wk,"DNSNoRSS");break;    
         case netErrDNSAborted:           StrCopy(wk,"DNSAborted");break;    
         case netErrDNSBadProtocol:       StrCopy(wk,"DNSBadProtocol");break;    
         case netErrDNSTruncated:         StrCopy(wk,"DNSTruncated");break;    
         case netErrDNSNoRecursion:       StrCopy(wk,"DNSNoRecursion");break;    
         case netErrDNSIrrelevant:        StrCopy(wk,"DNSIrrelevant");break;    
         case netErrDNSNotInLocalCache:   StrCopy(wk,"DNSNotInLocalCache");break;    
         case netErrDNSNoPort:            StrCopy(wk,"DNSNoPort");break;
         case netErrNoDNSServers:         StrCopy(wk,"No DNS Servers");break;
         default:                         StrCopy(wk,"UndeterminedError");break;               
      }
      StrCopy(wk2,"netErr");      //put "netErr" on the front of any err message   
      StrCat(wk2,wk);
      MemMove(result, wk2,StrLen(wk2)+1);          //return the error message as the result
      return;     
  }                    
  //no error -- have a host name
 MemMove(result,infoTypePtr->nameP,StrLen(infoTypePtr->nameP)+1);            //store the host ip name in the result               
                       
}
//**************************************************************************
//
//**************************************************************************
Err subrtn_getAddressByName(char *name,UInt32*address32,char *addressDot)  //subroutine to retrieve an ip address given a name
{
  NetHostInfoType     *infoTypePtr;  //pointer to the portion of the info buffer that contains results of the lookup
  NetHostInfoBufType  infoBuf;       //buffer to contain host info
  char wk[64];
  int x2;
  void* ptr;
  Err err;                       //error indicator
   
//StrPrintF(debug,"getaddrByName of name=%s",name);
//dbug(debug);  
  infoTypePtr=NetLibGetHostByName(netlibRefnum,  //NetLib library address
                      name,                   //name to lookup
                      &infoBuf,               //where to store the host name on return
                      30*sysTicksPerSecond,    //timeout value
                      &err);                  //where to return error code
//dbug("after addrbyName");
  if(infoTypePtr==0)   //an error occurred
  {
//StrPrintF(debug,"error %d",err);
//dbug(debug);
      switch(err)
      {
         case netErrTimeout:              StrCopy(wk,"Timeout");break;
         case netErrNotOpen:              StrCopy(wk,"NotOpen");break;
         case netErrDNSNameTooLong:       StrCopy(wk,"DNSNameTooLong");break;  
         case netErrDNSBadName:           StrCopy(wk,"DNSBadName");break;      
         case netErrDNSLabelTooLong:      StrCopy(wk,"DNSLabelTooLong");break;    
         case netErrDNSAllocationFailure: StrCopy(wk,"DNSAllocationFailure");break;    
         case netErrDNSTimeout:           StrCopy(wk,"DNSTimeout");break;    
         case netErrDNSUnreachable:       StrCopy(wk,"DNSUnreachable");break;    
         case netErrDNSFormat:            StrCopy(wk,"DNSFormat");break;    
         case netErrDNSServerFailure:     StrCopy(wk,"DNSServerFailure");break;    
         case netErrDNSNonexistantName:   StrCopy(wk,"DNSNonExistantName");break;    
         case netErrDNSNIY:               StrCopy(wk,"DNSNIY");break;    
         case netErrDNSRefused:           StrCopy(wk,"DNSRefused");break;
         case netErrDNSImpossible:        StrCopy(wk,"DNSImpossible");break;    
         case netErrDNSNoRRS:             StrCopy(wk,"DNSNoRSS");break;    
         case netErrDNSAborted:           StrCopy(wk,"DNSAborted");break;    
         case netErrDNSBadProtocol:       StrCopy(wk,"DNSBadProtocol");break;    
         case netErrDNSTruncated:         StrCopy(wk,"DNSTruncated");break;    
         case netErrDNSNoRecursion:       StrCopy(wk,"DNSNoRecursion");break;    
         case netErrDNSIrrelevant:        StrCopy(wk,"DNSIrrelevant");break;    
         case netErrDNSNotInLocalCache:   StrCopy(wk,"DNSNotInLocalCache");break;    
         case netErrDNSNoPort:            StrCopy(wk,"DNSNoPort");break;
         case netErrNoDNSServers:         StrCopy(wk,"No DNS Servers");break;
         default:                         StrCopy(wk,"UndeterminedRError");break;               
      }
 
      StrCopy(addressDot,"netErr");      //put "netErr" on the front of any err message   
       StrCat(addressDot,wk);
      
      return(err);   //indicate an error     
  }                    
  //no error -- have anIP address
  
  
//dbug("no error");
  
  
  
 //StrPrintF(debug,"ptrs  -infoBuf %lu ",&infoBuf);
 //dbug(debug);
 //StrPrintF(debug,"ptrs  -infoTypePtr %lu ",infoTypePtr);
 //dbug(debug);
 //StrPrintF(debug,"ptrs  -infotype addrlist %lu ",infoTypePtr->addrListP);
 //dbug(debug);
for(x2=0;infoTypePtr->addrListP[x2];++x2)
{
   ptr=(infoTypePtr->addrListP[x2]);  //get the ptr to the first address

   *address32=*((NetIPAddr*)ptr);
//StrPrintF(debug,"found address=%lu",*address32);
//SysFatalAlert(debug);
   if(*address32!=0)
   {
      NetLibAddrINToA(netlibRefnum,    //network library reference number
                      *address32,  //network IP address 32-bit number
                      addressDot); //output address in dot notation   
      break;
   }    
//dbug(addressDot);                  
} 
 
  //ptr=*(NetIPAddr**)(infoTypePtr->addrListP);  //get the ptr to the first address

  //*address32=*((NetIPAddr*)ptr);
//StrPrintF(debug,"got ip address (long)=%lu",((long)(*address32)));
//dbug(debug);
  //NetLibAddrINToA(netIO_libRefNum,    //network library reference number
  //                *address32,  //network IP address 32-bit number
  //                addressDot); //output address in dot notation   
//StrPrintF(debug,"leaving subrtn--dot addr=%s",addressDot);
//dbug(debug);
  return(0);            
  
}
//**************************************************************************
//
//**************************************************************************
void verb_netIO_getHostByName(char* name, char *result)
{
  Err err;
  NetIPAddr netAddr32;   //32-bit network address
  char      addressDot[100];  //address in dot notation 
  //find_arg_3();  //name to look up 
  if(StrLen(name)==0)  //dont allow null address name
  {
      err=netErrParamErr;
  }
  else
  {
      err=subrtn_getAddressByName(name, &netAddr32, addressDot);
  }
  if(err!=0) 
  {
    StrPrintF(addressDot,"**error - %d",err);
  }  
  
  MemMove(result,addressDot,StrLen(addressDot)+1);            //store the host ip name (or error message)in the result               
  
}
//**************************************************************************
//
//**************************************************************************

void debuggerConnect()
{
  //connect
	Boolean handled = false;
	FormType * frmP;
	
	FieldType * field;
	MemHandle outH;
	char* outP;
	UInt16 count;
	 Int16 res;
	Int16 len;
	 char * fldContents;
	 
	 char addressDot[100];
	 char msg[100];
	
	 Err err;
	 
     NetSocketAddrINType socketAddr;   //structure to hold address info          
	 
	 NetSocketAddrType toAddress;
	 NetSocketAddrType fromAddress;
	 
	 UInt16 lengthToAddress;
	 UInt16 lengthFromAddress;
	 
	 UInt16 errCount;
	  
	  	  
			   // NetSocketAddrType  socketAddress;  
			   
			  //open up the netlib library
			   err= SysLibFind ("Net.lib",&netlibRefnum);
			   
			   if( err != 0)
			   {
			        StrPrintF(debug,"On netlib Find got error = %d",err);
			        SysFatalAlert(debug);
			        
			                          SysFatalAlert("System will now reset.");   //07052005
			                          SysReset();                               //07052005
			   }
			   //
			   //open up a new socket to commun over
			   //
			    socket =   NetLibSocketOpen (netlibRefnum,
                         netSocketAddrINET ,
                         netSocketTypeStream,
                          netSocketProtoIPTCP,  //protocol ignored
                          1000*SysTicksPerSecond(), 
                          &err);
//SysFatalAlert("socket open");
			    if( err != 0)
			    {
			       StrPrintF(debug,"OnSocketOpen got error = %d",err);
			       SysFatalAlert(debug);
                      debuggerClose();                           //07052005
                      SysFatalAlert("System will now reset.");   //07052005
                      SysReset();                               //07052005
			    }
			    
			       
               
                //  set socket address params & socketLength
                 socketAddr.family=netSocketAddrINET; 
   				 socketAddr.port=1000;   //set the port//
//SysFatalAlert("calling in connect");
   
   
 
   					//MemMove(&socketAddr.addr, "127.0.0.1",10);
  					//verb_netIO_getHostByName("localhost", char *result)
  					subrtn_getAddressByName("localhost",&socketAddr.addr , addressDot ); 
//SysFatalAlert(addressDot);  					
  					//ldm
  					len=sizeof(NetSocketAddrINType);
//StrPrintF(debug,"socket# = %d",socket);
//SysFatalAlert(debug);   
   
   					//
   					// and connect to the IDE via tcpip
   					//
resetRetry:
                    errCount = 0;
retryConnect:
   					res = NetLibSocketConnect (netlibRefnum,
                       socket,
                      (NetSocketAddrType*) &socketAddr,
                       len,
                       50000*SysTicksPerSecond(),
                       &err);
		                if( (res == -1) && (err==4626))
		                {
		                    ++errCount;
		                    if (errCount < 20)
		                    {
//SysFatalAlert("retrying connect");
		                    	 goto retryConnect;
		                	}
		                	StrPrintF(debug,"Having trouble connecting to the IDE for debugging.  Start the debug process from the IDE menu.");
		                    SysFatalAlert(debug);
					        goto resetRetry;	
		                }
		                if( res == -1)
		                {
		                      StrPrintF(debug,"OnSocketConnect got error = %d",err);
					          SysFatalAlert(debug);
					                  debuggerClose();                           //07052005
			                          SysFatalAlert("System will now reset.");   //07052005
			                          SysReset();                               //07052005 debuggerClose();                           //07052005
			                           
					          goto resetRetry;
		                }
//07052005 SysFatalAlert("Connection made");
                  
                 
                        msgCount=0;
                        debuggerSend("connect");
 retry:
                        debuggerGetReturnMessage(msg);
				        if(MemCmp(msg,"quit",4)==0)
				        {
				            if (msgCount == 0)
				            {
//07052005 SysFatalAlert("retrying after 'quit'");
				               ++msgCount;
				               goto retry;
				            }
				            SysFatalAlert("The program was stopped from the debugging menu");
							debuggerClose();
							verb_stop();
							return;
				        }
				        if(MemCmp(msg,"connect",7) != 0)
				        {
				           StrPrintF(debug,"Illegal msg from IDE=%s",msg);
				           SysFatalAlert(debug);
				            debuggerClose();                           //07052005
				            SysFatalAlert("System will now reset.");   //modified 07062005
			                SysReset();                               //07052005
				           return;
				        }
//07052005 SysFatalAlert("Connected");
				         
				        
				 
 }
//**************************************************************************
//
//**************************************************************************

 void debuggerSend(char * msg)
 {
  //send
		 
		 UInt16 count;
	     Int16 res;
	 	 Err err;   
			      
			     
						count = NetLibSend (netlibRefnum,
                                   socket,
                                   msg,StrLen(msg),
                                  0,  //flags, 
                                  0,  //toaddr
                                   0, //toaddr length
                                   1000*SysTicksPerSecond(),
                                   &err);
                          if( count ==0 ) 
                          {
                              //07262005 StrPrintF(debug,"OnSocketSend -- host shutdown socket");
			                  //07262005 SysFatalAlert(debug);
			                   debuggerClose();                           //07052005
			                   //07262005 SysFatalAlert("System will now reset.");   //07052005
			                  SysReset();                               //07052005
                          }
                          else
                          {
                          		if( count == -1)
                          		{
                          		     StrPrintF(debug,"OnSocketSend got error = %d",err);
			                         SysFatalAlert(debug);
			                          debuggerClose();                           //07052005
			                          SysFatalAlert("System will now reset.");   //07052005
			                          SysReset();                               //07052005
                          		}
                          		else
                          		{
                          			//SysFatalAlert("Send over -- going to retry read");
                          			
                          		}
                          	
                          }              
}
//**************************************************************************
//
//**************************************************************************

void debuggerGetReturnMessage(char* outputMsg)
{
	 UInt16 count;
	     Int16 res;
	 	 Err err;   
	 	    		//now, receive the rebounding msg
reissueRead:
			 count =  NetLibReceive (netlibRefnum,
                           socket,
                           &inBufr,2048,
                           0,  //UInt16 flags,
                           0, //fromAddr 
                            0, //&lengthFromAddress,
                            1000*SysTicksPerSecond(),
                            &err);
                 if( count == -1)
                 {
                      if (err == netErrTimeout)
	                  {
	                     goto reissueRead;
	                  }	
	               
                      StrPrintF(debug,"OnSocketReceive got error = %d",err);
			          SysFatalAlert(debug);
			           debuggerClose();                           //07052005
			           SysFatalAlert("System will now reset.");  //07052005
			          SysReset();                              //07052005 
                 }
                 else
                 {
                       if (count == 0)
                       {
                       		StrPrintF(debug,"OnSocketReceive -- host shutdown socket");
			                SysFatalAlert(debug);
			                 debuggerClose();                           //07052005
			                 SysFatalAlert("System will now reset.");   //07052005
			                SysReset();                               //07052005
                       }
                       else
                       {
            
				            MemMove(outputMsg,inBufr, count);
				            outputMsg[count]=0x00;
//07052005 Trace(outputMsg);				            
                       }
                  }     
}
//**************************************************************************
//
//**************************************************************************

unsigned long debuggerFindInteger(char*s , int length)
{
		int i;
		char work[50];
		MemMove(work,s,length);
		work[length]=0x00;
		//position past leading zeroes
		for(i=0;i<length;++i)
		{
			if( work[i] != ' ') break;
			
		}
		if(i==length) return(0);
		return(StrAToI(&work[i]));
		
}