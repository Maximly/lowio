/////////////////////////////////////////////////////////////////
// File: lowio.h
// Description:
//   LOWIO driver definitiions
// Author:  Lyadvinsky M.V.
// Date:    03.02.2000
/////////////////////////////////////////////////////////////////
#ifndef _lowio_h
#define _lowio_h

#define LOWIO_LGN_MASK   DRP_MISC_PD
#define LOWIO_LGN_ORD    DRP_MISC_PD_BIT

#ifdef DEBUG
#define DbgPrint Debug_Printf
#else
#define DbgPrint
#endif

extern "C" ILB portILB;

#endif