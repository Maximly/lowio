/////////////////////////////////////////////////////////////////
// File: vxdext.h
// Description:
//   VxD Helpers
// Author:  Lyadvinsky M.V.
// Date:    30.12.1999
/////////////////////////////////////////////////////////////////
#ifndef _vxdext_h
#define _vxdext_h

// VMM Services
HEVENT VXDINLINE
Call_VM_Event(HVM hVM, void (__cdecl *pfnEvent)(), ULONG ulRefData)
{
 HEVENT hEvent;
 _asm  mov ebx, [hVM]
 _asm  mov edx, [ulRefData]
 _asm  mov esi, [pfnEvent]
 VMMCall(Call_VM_Event)
 _asm  mov [hEvent], esi
 return(hEvent);
}

// System VM
HEVENT VXDINLINE
CallInSystemVM(void (__cdecl *pfnEvent)(), ULONG ulRefData)
{
 return Call_VM_Event(Get_Sys_VM_Handle(), pfnEvent, ulRefData);
}

// VWIN32 Services
int VXDINLINE NAKED
CloseVxDHandle(HANDLE hEvent) 
{
 VxDJmp(_VWIN32_CloseVxDHandle)
}


int
VXDINLINE
WaitForSingleObject(HANDLE hEvent, DWORD dwTimeOut, BOOL bAlertable)
{
 _asm  mov ebx, [hEvent]
 _asm  mov edx, [dwTimeOut]
 _asm  mov eax, [bAlertable]
 VxDCall(_VWIN32_WaitSingleObject)
}

HANDLE
VXDINLINE
CreateThread(PVOID ThreadProc, DWORD dwParam)
{
 _asm  mov ecx, 4096
 _asm  mov edx, [dwParam]
 _asm  mov ebx, [ThreadProc]
 _asm  mov esi, 0
 VxDCall(_VWIN32_CreateRing0Thread)
}

void
VXDINLINE
TerminateThread(HANDLE hThread)
{
 _asm  mov edi, [hThread]
 VMMCall(VMMTerminateThread)
}

#endif