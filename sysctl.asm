;****************************************************************
; File: sysctl.asm
; Description:
;   Device declaration and control porcedure
; Author:  Lyadvinsky M.V.
; Date:    3.02.2000
;****************************************************************

.386p
include vmm.inc
include drp.inc
include ilb.inc


extrn _OnAsyncRequest: near

;****************************************************************
;
; DRP structure
;
;****************************************************************
VXD_IDATA_SEG
 public _portDRP
 _portDRP DRP <EyeCatcher, \
   DRP_VSD_9, \
   offset32 _OnAsyncRequest, \
   offset32 _portILB, \
   'Low I/O VSD', \
   0, 0, 0>
VXD_IDATA_ENDS



;****************************************************************
;
; ILB structure
;
;****************************************************************
VXD_LOCKED_DATA_SEG
 public _portILB
 _portILB ILB <>  ;IO Subsystem linkage block
VXD_LOCKED_DATA_ENDS


;****************************************************************
;
; Processing CPP initializers
;
;****************************************************************
VxD_LOCKED_DATA_SEG
didinit  dd    0
VxD_LOCKED_DATA_ENDS

initcode segment dword public flat 'code'
beginit  dd    0
initcode ends

initend  segment dword public flat 'code'
endinit  dd    0
initend  ends

_bss	 segment dword public flat 'lcode'
startbss dd    0
_bss	 ends

_ebss	 segment dword public flat 'lcode'
endbss	 dd    0
_ebss ends


;****************************************************************
;
; Declare device
;
;****************************************************************
Declare_Virtual_Device \
  LOWIO, \
  1, 0, \
  LOWIO_Control, \
  Undefined_Device_ID, \
  Undefined_Init_Order,,, \
  _portDRP


;****************************************************************
;
; Control dispatch
;
;****************************************************************
VxD_LOCKED_CODE_SEG
Begin_Control_Dispatch LOWIO
  bts  didinit, 0		       ; been here before?
  jc   skipinit 		       ; if yes, skip initialization
  pushad                       ; save all registers
  ;    The linker won't necessarily generate zero data for the BSS section,
  ;    which is where the compiler places uninitialized static data. Zero
  ;    this area by hand, therefore.
  cld                          ; force forward direction
  mov  edi, offset32 startbss  ; point to start of BSS area
  mov  ecx, offset32 endbss    ; compute length
  sub  ecx, edi
  shr  ecx, 2			       ; convert to dwords
  xor  eax, eax                ; get const zero
  rep  stosd			       ; zero-fill BSS area
  ;    Execute static initialization code
  mov  esi, offset32 beginit+4 ; point to 1st initializer ptr
@@:
  cmp  esi, offset32 endinit   ; reached end of initializers?
  jae  @F	                   ; if yes, leave the loop
  call dword ptr [esi]         ; call static initializer
  add  esi, 4			       ; process all of them
  jmp  @B	                   ;   ..
@@:
  popad	                       ; restore registers
skipinit:
  Control_Dispatch Sys_Dynamic_Device_Init, _OnSysDynamicDeviceInit, cCall
  Control_Dispatch Sys_Dynamic_Device_Exit, _OnSysDynamicDeviceExit, cCall
  Control_Dispatch W32_DEVICEIOCONTROL,     _SysDispatch, cCall, <ecx, ebx, edx, esi>
End_Control_Dispatch   LOWIO
VxD_LOCKED_CODE_ENDS

END
