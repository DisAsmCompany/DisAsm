/*
* Filename: Register.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: possible x86/x64 register values
*              
*              
*
*/

#ifndef __REGISTER_H__
#define __REGISTER_H__

/*
for each group we have 8 registers : 0 1 2 3 4 5 6 7
that could be represented by 3 bits
so each groups should be shifted by 3

another trick is that registers should begin with value 0200h
in order to allow coding of Operand Type / Register in single word field
(see also OperandType.h for details on coding)
*/

#define REGISTERBASE 0x00010000UL

#define SHIFT4(x) (REGISTERBASE + (x) * 16)

#define DefineRegisters(name0, name1, name2, name3, name4, name5, name6, name7, name8, name9, name10, name11, name12, name13, name14, name15, value) \
_ENUM_ELEMENT_VALUE(name0,  value | 0) \
_ENUM_ELEMENT_VALUE(name1,  value | 1) \
_ENUM_ELEMENT_VALUE(name2,  value | 2) \
_ENUM_ELEMENT_VALUE(name3,  value | 3) \
_ENUM_ELEMENT_VALUE(name4,  value | 4) \
_ENUM_ELEMENT_VALUE(name5,  value | 5) \
_ENUM_ELEMENT_VALUE(name6,  value | 6) \
_ENUM_ELEMENT_VALUE(name7,  value | 7) \
_ENUM_ELEMENT_VALUE(name8,  value | 8) \
_ENUM_ELEMENT_VALUE(name9,  value | 9) \
_ENUM_ELEMENT_VALUE(name10, value | 10) \
_ENUM_ELEMENT_VALUE(name11, value | 11) \
_ENUM_ELEMENT_VALUE(name12, value | 12) \
_ENUM_ELEMENT_VALUE(name13, value | 13) \
_ENUM_ELEMENT_VALUE(name14, value | 14) \
_ENUM_ELEMENT_VALUE(name15, value | 15)

#define DefineRegisters16(name, value) \
_ENUM_ELEMENT_VALUE(name##0,  value | 0) \
_ENUM_ELEMENT_VALUE(name##1,  value | 1) \
_ENUM_ELEMENT_VALUE(name##2,  value | 2) \
_ENUM_ELEMENT_VALUE(name##3,  value | 3) \
_ENUM_ELEMENT_VALUE(name##4,  value | 4) \
_ENUM_ELEMENT_VALUE(name##5,  value | 5) \
_ENUM_ELEMENT_VALUE(name##6,  value | 6) \
_ENUM_ELEMENT_VALUE(name##7,  value | 7) \
_ENUM_ELEMENT_VALUE(name##8,  value | 8) \
_ENUM_ELEMENT_VALUE(name##9,  value | 9) \
_ENUM_ELEMENT_VALUE(name##10, value | 10) \
_ENUM_ELEMENT_VALUE(name##11, value | 11) \
_ENUM_ELEMENT_VALUE(name##12, value | 12) \
_ENUM_ELEMENT_VALUE(name##13, value | 13) \
_ENUM_ELEMENT_VALUE(name##14, value | 14) \
_ENUM_ELEMENT_VALUE(name##15, value | 15)

#define rRegister  SHIFT4(0x00UL) /* mask */
#define eRegister  SHIFT4(0x01UL) /* mask */
/* 8-bit  general purpose register (AL/CL/DL/BL/SPL/BPL/SIL/DIL) */
#define Reg8       SHIFT4(0x02UL)
/* 16-bit general purpose register (AX/CX/DX/BX/SP/BP/SI/DI/R8W/R9W/R10W/R11W/R12W/R13W/R14W/R15W) */
#define Reg16      SHIFT4(0x03UL)
/* 32-bit general purpose register (EAX/ECX/EDX/EBX/ESP/EBP/ESI/EDI/R8D/R9D/R10D/R11D/R12D/R13D/R14D/R15D) */
#define Reg32      SHIFT4(0x04UL)
/* 64-bit general purpose register (RAX/RCX/RDX/RBX/RSP/RBP/RSI/RDI/R8/R9/R10/R11/R12/R13/R14/R15) */
#define Reg64      SHIFT4(0x05UL)
/* MMX register (MM0/MM1/MM2/MM3/MM4/MM5/MM6/MM7) */
#define RegMMX     SHIFT4(0x06UL)
/* SSE register (XMM0/XMM1/XMM2/XMM3/XMM4/XMM5/XMM6/XMM7) */
#define RegSSE     SHIFT4(0x07UL)
/* AVX register (YMM0/YMM1/YMM2/YMM3/YMM4/YMM5/YMM6/YMM7) */
#define RegAVX     SHIFT4(0x08UL)
/* 16-bit segment register (ES/CS/SS/DS/FS/GS/--/--) */
#define RegSeg     SHIFT4(0x09UL)
/* x87 FPU register (ST0/ST1/ST2/ST3/ST4/ST5/ST6/ST7) */
#define RegX87     SHIFT4(0x0AUL)
/* control register (CR0/CR1/CR2/CR3/CR4/CR5/CR6/CR7) */
#define RegControl SHIFT4(0x0BUL)
/* debug register (DR0/DR1/DR2/DR3/DR4/DR5/DR6/DR7) */
#define RegDebug   SHIFT4(0x0CUL)
/* AVX-512 (ZMM) register (ZMM0/ZMM1/ZMM2/ZMM3/ZMM4/ZMM5/ZMM6/ZMM7/ZMM8/ZMM9/ZMM10/ZMM11/ZMM12/ZMM13/ZMM14/ZMM15) */
#define RegAVX512  SHIFT4(0x0DUL)

_ENUM_START(Register, REGISTERBASE)

DefineRegisters(rAX, rCX, rDX, rBX, rSP, rBP, rSI, rDI, r8,  r9,  r10,  r11,  r12,  r13,  r14,  r15,  rRegister)
DefineRegisters(eAX, eCX, eDX, eBX, eSP, eBP, eSI, eDI, e8,  e9,  e10,  e11,  e12,  e13,  e14,  e15,  eRegister)
DefineRegisters(AL,  CL,  DL,  BL,  AH,  CH,  DH,  BH,  R8B, R9B, R10B, R11B, R12B, R13B, R14B, R15B, Reg8)
DefineRegisters(AX,  CX,  DX,  BX,  SP,  BP,  SI,  DI,  R8W, R9W, R10W, R11W, R12W, R13W, R14W, R15W, Reg16)
DefineRegisters(EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, R8D, R9D, R10D, R11D, R12D, R13D, R14D, R15D, Reg32)
DefineRegisters(RAX, RCX, RDX, RBX, RSP, RBP, RSI, RDI, R8,  R9,  R10,  R11,  R12,  R13,  R14,  R15,  Reg64)
DefineRegisters16(MM,  RegMMX)
DefineRegisters16(XMM, RegSSE)
DefineRegisters16(YMM, RegAVX)
DefineRegisters(ES, CS, SS, DS, FS, GS, Seg6, Seg7, Seg8, Seg9, Seg10, Seg11, Seg12, Seg13, Seg14, Seg15, RegSeg)
DefineRegisters16(ST,  RegX87)
DefineRegisters16(CR,  RegControl)
DefineRegisters16(DR,  RegDebug)
DefineRegisters16(ZMM, RegAVX512)

_ENUM_STOP(Register, REGISTERBASE)

#endif /* __REGISTER_H__ */
