/////////////////////////////////////////////////////////////////
// File: aep.cpp
// Description:
//   Asynchronous Event Procedure
// Author:  Lyadvinsky M.V.
// Date:    03.02.2000
/////////////////////////////////////////////////////////////////
#include "stdvxd.h"

#include "lowio.h"

#pragma VxD_LOCKED_CODE_SEG
#pragma VxD_LOCKED_DATA_SEG
#undef CURSEG
#define CURSEG() LCODE

USHORT OnInitialize(PAEP_bi_init);
USHORT OnBootComplete(PAEP_boot_done);
USHORT OnUninitialize(PAEP_bi_uninit);

typedef USHORT (*PEF)(PAEP);

static PEF EvProcs[AEP_MAX_FUNC + 1] =
{
 (PEF)OnInitialize,      // 00 AEP_INITIALIZE
 NULL,                   // 01 AEP_SYSTEM_CRIT_SHUTDOWN
 (PEF)OnBootComplete,    // 02 AEP_BOOT_COMPLETE
 NULL,                   // 03 AEP_CONFIG_DCB
 NULL,                   // 04 AEP_UNCONFIG_DCB
 NULL,                   // 05 AEP_IOP_TIMEOUT
 NULL,                   // 06 AEP_DEVICE_INQUIRY
 NULL,                   // 07 AEP_HALF_SEC
 NULL,                   // 08 AEP_1_SEC
 NULL,                   // 09 AEP_2_SECS
 NULL,                   // 0A AEP_4_SECS
 NULL,                   // 0B AEP_DBG_DOT_CMD
 NULL,                   // 0C AEP_ASSOCIATE_DCB
 NULL,                   // 0D AEP_REAL_MODE_HANDOFF
 NULL,                   // 0E AEP_SYSTEM_SHUTDOWN
 (PEF)OnUninitialize,    // 0F AEP_UNINITIALIZE
 NULL,                   // 10 AEP_DCB_LOCK
 NULL,                   // 11 AEP_MOUNT_NOTIFY
 NULL,                   // 12 AEP_CREATE_VRP
 NULL,                   // 13 AEP_DESTROY_VRP
 NULL,                   // 14 AEP_REFRESH_DRIVE
 NULL,                   // 15 AEP_PEND_UNCONFIG_DCB
 NULL,                   // 16 AEP_1E_VEC_UPDATE
 NULL                    // 17 AEP_CHANGE_RPM
};

SYSCTL
VOID
OnAsyncRequest(PAEP pAep)
{
 PEF pProc;
 if (pAep->AEP_func <= AEP_MAX_FUNC &&
     (pProc = EvProcs[pAep->AEP_func]) != NULL)
 {
  pAep->AEP_result = pProc(pAep);
 }
 else
 {
  pAep->AEP_result = AEP_FAILURE;
 }
 DbgPrint("LOWIO: AEP function 0x%X, result: 0x%X\n",
   pAep->AEP_func, pAep->AEP_result);
}

#pragma VxD_PAGEABLE_CODE_SEG

USHORT
OnInitialize(PAEP_bi_init pAep)
{
 USHORT uErr = AEP_SUCCESS;
 return uErr;
}


USHORT
OnBootComplete(PAEP_boot_done pAep)
{
 return AEP_SUCCESS;
}


USHORT
OnUninitialize(PAEP_bi_uninit pAep)
{
 return AEP_SUCCESS;
}
