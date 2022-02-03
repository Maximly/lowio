/////////////////////////////////////////////////////////////////
// File: lowio.cpp
// Description:
//   LOWIO driver
// Author:  Lyadvinsky M.V.
// Date:    03.02.2000
/////////////////////////////////////////////////////////////////
#include "stdvxd.h"
#include "lowio.h"

extern "C" DRP portDRP;

#pragma VxD_INIT_CODE_SEG

SYSCTL
BOOL
OnSysDynamicDeviceInit()
{
 BOOL bRet;
 IOS_Register(&portDRP);
 bRet = portDRP.DRP_reg_result == DRP_REMAIN_RESIDENT ||
        portDRP.DRP_reg_result == DRP_MINIMIZE;
 DbgPrint("LOWIO: Loaded\n");
 return bRet;
}


#pragma VxD_LOCKED_CODE_SEG
#undef CURSEG
#define CURSEG() LCODE

SYSCTL
BOOL
OnSysDynamicDeviceExit()
{
 DbgPrint("LOWIO: Unloaded\n");
 return TRUE;
}


SYSCTL
DWORD 
SysDispatch(
 DWORD  dwService,
 DWORD  dwDDB,
 DWORD  hDevice,
 LPDIOC lpDIOCParms)
{
 DWORD dwError = ERROR_INVALID_PARAMETER;
 switch (lpDIOCParms->dwIoControlCode)
 {
  case DIOC_OPEN:
    dwError = 0;
    break;
  
 }
 
 DbgPrint("LOWIO: IOCTL 0x%X, result: 0x%X\n", 
   lpDIOCParms->dwIoControlCode, dwError);
 return dwError;
}


