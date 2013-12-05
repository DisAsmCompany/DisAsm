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

/* no "pragma once" - header is tricky and supposed to be included twice by design */
#ifndef __REGISTER_H__8C8FA516_AFA4_402d_B1A2_8040D9312A78__
#define __REGISTER_H__8C8FA516_AFA4_402d_B1A2_8040D9312A78__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
for each group we have 8 registers : 0 1 2 3 4 5 6 7
that could be represented by 3 bits
so each groups should be shifted by 3

another trick is that registers should begin with value 0200h
in order to allow coding of Operand Type / Register in single word field
(see also OperandType.h for details on coding)
*/

#define SHIFT4(x) (RegisterBase + ((x) << 4))

#ifndef DefineRegisters
#define DefineRegisters(name0, name1, name2, name3, name4, name5, name6, name7, name8, name9, name10, name11, name12, name13, name14, name15, value, base) \
_ENUM_ELEMENT_VALUE_SKIP(value, SHIFT4(base)) \
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
#endif /* DefineRegisters */

#ifndef DefineRegisters16
#define DefineRegisters16(name, value, base) \
_ENUM_ELEMENT_VALUE_SKIP(value, SHIFT4(base)) \
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
#endif /* DefineRegisters16 */

_ENUM_START(Register, RegisterBase)
DefineRegisters(rAX, rCX, rDX, rBX, rSP, rBP, rSI, rDI, r8,  r9,  r10,  r11,  r12,  r13,  r14,  r15,  rRegister, 0x00)
DefineRegisters(eAX, eCX, eDX, eBX, eSP, eBP, eSI, eDI, e8,  e9,  e10,  e11,  e12,  e13,  e14,  e15,  eRegister, 0x01)
DefineRegisters(AL,  CL,  DL,  BL,  AH,  CH,  DH,  BH,  R8B, R9B, R10B, R11B, R12B, R13B, R14B, R15B, Reg8,  0x02)
DefineRegisters(AX,  CX,  DX,  BX,  SP,  BP,  SI,  DI,  R8W, R9W, R10W, R11W, R12W, R13W, R14W, R15W, Reg16, 0x03)
DefineRegisters(EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, R8D, R9D, R10D, R11D, R12D, R13D, R14D, R15D, Reg32, 0x04)
DefineRegisters(RAX, RCX, RDX, RBX, RSP, RBP, RSI, RDI, R8,  R9,  R10,  R11,  R12,  R13,  R14,  R15,  Reg64, 0x05)
DefineRegisters(ES, CS, SS, DS, FS, GS, Seg6, Seg7, Seg8, Seg9, Seg10, Seg11, Seg12, Seg13, Seg14, Seg15, RegSeg, 0x06)
DefineRegisters16(CR,  RegControl, 0x07)
DefineRegisters16(DR,  RegDebug, 0x08)
DefineRegisters16(ST,  RegX87, 0x09)
DefineRegisters16(MM,  RegMMX, 0x0A)
DefineRegisters16(XMM, RegSSE, 0x0B)
DefineRegisters16(YMM, RegAVX, 0x0C)
DefineRegisters16(ZMM, RegAVX512, 0x0D)

_ENUM_STOP(Register, RegisterBase)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __REGISTER_H__8C8FA516_AFA4_402d_B1A2_8040D9312A78__ */
