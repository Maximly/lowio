// StdVxd.h -- Standard declarations for C-language VxDs
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#ifndef STDVXD_H
#define STDVXD_H

#ifdef __cplusplus
	extern "C" {
	#ifndef SETINITSEG
		#define SETINITSEG
		#pragma warning(disable:4075) // nonstandard init seg
		#pragma warning(default:4075)
	#endif // SETINITSEG
	#define SYSCTL extern "C"
#else // not __cplusplus
	#define SYSCTL
#endif // not __cplusplus

#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif

#define WANTVXDWRAPS
#include <basedef.h>
#undef NULL
#define NULL 0
#include <vmm.h>
#include <vwin32.h>
#include <scsi.h>
#include <debug.h>
#pragma warning(disable:4229)
#include <shell.h>
#pragma warning(default:4229)
#include "VMMREG.h"

// Virtual Communications Driver:

#include <vxdwraps.h>

#include <stdarg.h>
#include <configmg.h>
#include <winerror.h>

#ifdef __cplusplus
} // extern "C"
#endif
		
#include "iosdcls.h"
#include "ifsmgr.h"

///////////////////////////////////////////////////////////////////////////////
// Useful general-purpose definitions

//#include <string.h>
extern "C" void* memcpy(void *dest, const void *src, size_t count);
extern "C" void* memset(void *dest, int c, size_t count);
extern "C" char* strcpy(char *strDestination, const char *strSource);
extern "C" char* strcat(char *strDestination, const char *strSource);
extern "C" char* strncpy(char *strDest, const char *strSource, size_t count);
extern "C" int   strlen(const char *string);
#pragma function(memcpy, memset, strcat, strcpy, strlen)
#define sprintf _Sprintf

#ifndef ASSERT
#ifdef DEBUG
	#define ASSERT(e) if(!(e)){Debug_Printf("Assertion failure in " __FILE__ ", line %d: " #e "\r\n", __LINE__);\
		_asm int 1\
		}
#else
	#define ASSERT(e)
#endif
#endif

#ifndef MAKELONG
	#define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))
#endif

#ifndef FIELDOFFSET
	#define FIELDOFFSET(type, field) ((DWORD)(&((type *)0)->field))
#endif

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

#ifndef NAKED
	#define NAKED __declspec(NAKED)
#endif

#ifndef min
	#define min(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef max
	#define max(a,b) ((a) > (b) ? (b) : (a))
#endif

typedef DIOCPARAMETERS *LPDIOC;

#define ULONGLONG unsigned __int64

#include "vxdext.h"

#endif // STDVXD_H
