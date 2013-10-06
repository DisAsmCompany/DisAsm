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

#define SHIFT3(x) (0x0200UL + (x) * 8)

_ENUM_START(Register)

#define rRegister  SHIFT3(0x01UL) /* mask */
#define eRegister  SHIFT3(0x02UL) /* mask */
/* 8-bit  general purpose register (AL/CL/DL/BL/SPL/BPL/SIL/DIL) */
#define Reg8       SHIFT3(0x03UL)
/* 16-bit general purpose register (AX/CX/DX/BX/SP/BP/SI/DI) */
#define Reg16      SHIFT3(0x04UL)
/* 32-bit general purpose register (EAX/ECX/EDX/EBX/ESP/EBP/ESI/EDI) */
#define Reg32      SHIFT3(0x05UL)
/* MMX register (MM0/MM1/MM2/MM3/MM4/MM5/MM6/MM7) */
#define RegMMX     SHIFT3(0x06UL)
/* SSE register (XMM0/XMM1/XMM2/XMM3/XMM4/XMM5/XMM6/XMM7) */
#define RegSSE     SHIFT3(0x07UL)
/* AVX register (YMM0/YMM1/YMM2/YMM3/YMM4/YMM5/YMM6/YMM7) */
#define RegAVX     SHIFT3(0x08UL)
/* 16-bit segment register (ES/CS/SS/DS/FS/GS/--/--) */
#define RegSeg     SHIFT3(0x09UL)
/* x87 FPU register (ST0/ST1/ST2/ST3/ST4/ST5/ST6/ST7) */
#define Regx87     SHIFT3(0x0AUL)
/* control register (CR0/CR1/CR2/CR3/CR4/CR5/CR6/CR7) */
#define RegControl SHIFT3(0x0BUL)
/* debug register (DR0/DR1/DR2/DR3/DR4/DR5/DR6/DR7) */
#define RegDebug   SHIFT3(0x0CUL)

_ENUM_ELEMENT_VALUE(r0, 0x00UL)
_ENUM_ELEMENT_VALUE(r1, 0x01UL)
_ENUM_ELEMENT_VALUE(r2, 0x02UL)
_ENUM_ELEMENT_VALUE(r3, 0x03UL)
_ENUM_ELEMENT_VALUE(r4, 0x04UL)
_ENUM_ELEMENT_VALUE(r5, 0x05UL)
_ENUM_ELEMENT_VALUE(r6, 0x06UL)
_ENUM_ELEMENT_VALUE(r7, 0x07UL)

_ENUM_ELEMENT_VALUE(rAX, rRegister | r0)
_ENUM_ELEMENT_VALUE(rCX, rRegister | r1)
_ENUM_ELEMENT_VALUE(rDX, rRegister | r2)
_ENUM_ELEMENT_VALUE(rBX, rRegister | r3)
_ENUM_ELEMENT_VALUE(rSP, rRegister | r4)
_ENUM_ELEMENT_VALUE(rBP, rRegister | r5)
_ENUM_ELEMENT_VALUE(rSI, rRegister | r6)
_ENUM_ELEMENT_VALUE(rDI, rRegister | r7)

_ENUM_ELEMENT_VALUE(eAX, eRegister | r0)
_ENUM_ELEMENT_VALUE(eCX, eRegister | r1)
_ENUM_ELEMENT_VALUE(eDX, eRegister | r2)
_ENUM_ELEMENT_VALUE(eBX, eRegister | r3)
_ENUM_ELEMENT_VALUE(eSP, eRegister | r4)
_ENUM_ELEMENT_VALUE(eBP, eRegister | r5)
_ENUM_ELEMENT_VALUE(eSI, eRegister | r6)
_ENUM_ELEMENT_VALUE(eDI, eRegister | r7)

_ENUM_ELEMENT_VALUE(AL,  Reg8    | r0)
_ENUM_ELEMENT_VALUE(CL,  Reg8    | r1)
_ENUM_ELEMENT_VALUE(DL,  Reg8    | r2)
_ENUM_ELEMENT_VALUE(BL,  Reg8    | r3)
_ENUM_ELEMENT_VALUE(AH,  Reg8    | r4)
_ENUM_ELEMENT_VALUE(CH,  Reg8    | r5)
_ENUM_ELEMENT_VALUE(DH,  Reg8    | r6)
_ENUM_ELEMENT_VALUE(BH,  Reg8    | r7)

_ENUM_ELEMENT_VALUE(AX,  Reg16   | r0)
_ENUM_ELEMENT_VALUE(CX,  Reg16   | r1)
_ENUM_ELEMENT_VALUE(DX,  Reg16   | r2)
_ENUM_ELEMENT_VALUE(BX,  Reg16   | r3)
_ENUM_ELEMENT_VALUE(SP,  Reg16   | r4)
_ENUM_ELEMENT_VALUE(BP,  Reg16   | r5)
_ENUM_ELEMENT_VALUE(SI,  Reg16   | r6)
_ENUM_ELEMENT_VALUE(DI,  Reg16   | r7)

_ENUM_ELEMENT_VALUE(EAX, Reg32   | r0)
_ENUM_ELEMENT_VALUE(ECX, Reg32   | r1)
_ENUM_ELEMENT_VALUE(EDX, Reg32   | r2)
_ENUM_ELEMENT_VALUE(EBX, Reg32   | r3)
_ENUM_ELEMENT_VALUE(ESP, Reg32   | r4)
_ENUM_ELEMENT_VALUE(EBP, Reg32   | r5)
_ENUM_ELEMENT_VALUE(ESI, Reg32   | r6)
_ENUM_ELEMENT_VALUE(EDI, Reg32   | r7)

_ENUM_ELEMENT_VALUE(MM0, RegMMX  | r0)
_ENUM_ELEMENT_VALUE(MM1, RegMMX  | r1)
_ENUM_ELEMENT_VALUE(MM2, RegMMX  | r2)
_ENUM_ELEMENT_VALUE(MM3, RegMMX  | r3)
_ENUM_ELEMENT_VALUE(MM4, RegMMX  | r4)
_ENUM_ELEMENT_VALUE(MM5, RegMMX  | r5)
_ENUM_ELEMENT_VALUE(MM6, RegMMX  | r6)
_ENUM_ELEMENT_VALUE(MM7, RegMMX  | r7)

_ENUM_ELEMENT_VALUE(XMM0, RegSSE | r0)
_ENUM_ELEMENT_VALUE(XMM1, RegSSE | r1)
_ENUM_ELEMENT_VALUE(XMM2, RegSSE | r2)
_ENUM_ELEMENT_VALUE(XMM3, RegSSE | r3)
_ENUM_ELEMENT_VALUE(XMM4, RegSSE | r4)
_ENUM_ELEMENT_VALUE(XMM5, RegSSE | r5)
_ENUM_ELEMENT_VALUE(XMM6, RegSSE | r6)
_ENUM_ELEMENT_VALUE(XMM7, RegSSE | r7)

_ENUM_ELEMENT_VALUE(YMM0, RegAVX | r0)
_ENUM_ELEMENT_VALUE(YMM1, RegAVX | r1)
_ENUM_ELEMENT_VALUE(YMM2, RegAVX | r2)
_ENUM_ELEMENT_VALUE(YMM3, RegAVX | r3)
_ENUM_ELEMENT_VALUE(YMM4, RegAVX | r4)
_ENUM_ELEMENT_VALUE(YMM5, RegAVX | r5)
_ENUM_ELEMENT_VALUE(YMM6, RegAVX | r6)
_ENUM_ELEMENT_VALUE(YMM7, RegAVX | r7)

_ENUM_ELEMENT_VALUE(ES,   RegSeg | r0)
_ENUM_ELEMENT_VALUE(CS,   RegSeg | r1)
_ENUM_ELEMENT_VALUE(SS,   RegSeg | r2)
_ENUM_ELEMENT_VALUE(DS,   RegSeg | r3)
_ENUM_ELEMENT_VALUE(FS,   RegSeg | r4)
_ENUM_ELEMENT_VALUE(GS,   RegSeg | r5)

_ENUM_ELEMENT_VALUE(ST0,  Regx87 | r0)
_ENUM_ELEMENT_VALUE(ST1,  Regx87 | r1)
_ENUM_ELEMENT_VALUE(ST2,  Regx87 | r2)
_ENUM_ELEMENT_VALUE(ST3,  Regx87 | r3)
_ENUM_ELEMENT_VALUE(ST4,  Regx87 | r4)
_ENUM_ELEMENT_VALUE(ST5,  Regx87 | r5)
_ENUM_ELEMENT_VALUE(ST6,  Regx87 | r6)
_ENUM_ELEMENT_VALUE(ST7,  Regx87 | r7)

_ENUM_ELEMENT_VALUE(CR0,  RegControl | r0)
_ENUM_ELEMENT_VALUE(CR1,  RegControl | r1)
_ENUM_ELEMENT_VALUE(CR2,  RegControl | r2)
_ENUM_ELEMENT_VALUE(CR3,  RegControl | r3)
_ENUM_ELEMENT_VALUE(CR4,  RegControl | r4)
_ENUM_ELEMENT_VALUE(CR5,  RegControl | r5)
_ENUM_ELEMENT_VALUE(CR6,  RegControl | r6)
_ENUM_ELEMENT_VALUE(CR7,  RegControl | r7)

_ENUM_ELEMENT_VALUE(DR0,  RegDebug | r0)
_ENUM_ELEMENT_VALUE(DR1,  RegDebug | r1)
_ENUM_ELEMENT_VALUE(DR2,  RegDebug | r2)
_ENUM_ELEMENT_VALUE(DR3,  RegDebug | r3)
_ENUM_ELEMENT_VALUE(DR4,  RegDebug | r4)
_ENUM_ELEMENT_VALUE(DR5,  RegDebug | r5)
_ENUM_ELEMENT_VALUE(DR6,  RegDebug | r6)
_ENUM_ELEMENT_VALUE(DR7,  RegDebug | r7)

_ENUM_STOP(Register)

#endif /* __REGISTER_H__ */
