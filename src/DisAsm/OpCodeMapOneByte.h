/*
* Filename: OpCodeMapOneByte.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: One-Byte Opcode Map (OpCodes 00h - FFh)
*              
*              
*
*/

#ifndef __OPCODEMAPONEBYTE_H__
#define __OPCODEMAPONEBYTE_H__

/* One-Byte Opcode Map (OpCodes 00h - FFh) */

/* 
  0 1 2 3 4 5 6 7   8 9 A B C D E F
0 X X X X X X X X 0 X X X X X X X + 0
1 X X X X X X X X 1 X X X X X X X X 1
2 X X X X X X P X 2 X X X X X X P X 2
3 X X X X X X P X 3 X X X X X X P X 3
4 X X X X X X X X 4 X X X X X X X X 4
5 X X X X X X X X 5 X X X X X X X X 5
6 X X     P P P P 6 X X X X X X X X 6
7 X X X X X X X X 7 X X X X X X X X 7
  0 1 2 3 4 5 6 7   8 9 A B C D E F
8 X X X X X X X X 8 X X X X X X X X 8
9 X X X X X X X X 9 X X   X X X X X 9
A X X X X X X X X A X X X X X X X X A
B X X X X X X X X B X X X X X X X X B
C X X X X     X X C X X X X X X X X C
D X X X X X X X X D + + + + + + + + D
E X X X X X X X X E X X   X X X X X E
F P X P P X X X X F X X X X X X X X F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

OpCodeMapElement OpCodeMapOneByte[] =
{
	/* 00h - 07h */
	{ADD, OP2(Eb, Gb)}, {ADD, OP2(Ev, Gv)}, {ADD, OP2(Gb, Eb)}, {ADD, OP2(Gv, Ev)}, {ADD, OP2(Reg, Ib), AL}, {ADD, OP2(Reg, Iz), rAX}, {PUSH, OP1(Reg), ES}, {POP, OP1(Reg), ES},
	/* 08h - 0Fh */
	{OR , OP2(Eb, Gb)}, {OR , OP2(Ev, Gv)}, {OR , OP2(Gb, Eb)}, {OR , OP2(Gv, Ev)}, {OR , OP2(Reg, Ib), AL}, {OR , OP2(Reg, Iz), rAX}, {PUSH, OP1(Reg), CS}, {ESCAPE},
	/* 10h - 17h */
	{ADC, OP2(Eb, Gb)}, {ADC, OP2(Ev, Gv)}, {ADC, OP2(Gb, Eb)}, {ADC, OP2(Gv, Ev)}, {ADC, OP2(Reg, Ib), AL}, {ADC, OP2(Reg, Iz), rAX}, {PUSH, OP1(Reg), SS}, {POP, OP1(Reg), SS},
	/* 17h - 1Fh */
	{SBB, OP2(Eb, Gb)}, {SBB, OP2(Ev, Gv)}, {SBB, OP2(Gb, Eb)}, {SBB, OP2(Gv, Ev)}, {SBB, OP2(Reg, Ib), AL}, {SBB, OP2(Reg, Iz), rAX}, {PUSH, OP1(Reg), DS}, {POP, OP1(Reg), DS},
	/* 20h - 27h */
	{AND, OP2(Eb, Gb)}, {AND, OP2(Ev, Gv)}, {AND, OP2(Gb, Eb)}, {AND, OP2(Gv, Ev)}, {AND, OP2(Reg, Ib), AL}, {AND, OP2(Reg, Iz), rAX}, {PrefixES}, {DAA},
	/* 28h - 2Fh */
	{SUB, OP2(Eb, Gb)}, {SUB, OP2(Ev, Gv)}, {SUB, OP2(Gb, Eb)}, {SUB, OP2(Gv, Ev)}, {SUB, OP2(Reg, Ib), AL}, {SUB, OP2(Reg, Iz), rAX}, {PrefixCS}, {DAS},
	/* 30h - 37h */
	{XOR, OP2(Eb, Gb)}, {XOR, OP2(Ev, Gv)}, {XOR, OP2(Gb, Eb)}, {XOR, OP2(Gv, Ev)}, {XOR, OP2(Reg, Ib), AL}, {XOR, OP2(Reg, Iz), rAX}, {PrefixSS}, {AAA},
	/* 38h - 3Fh */
	{CMP, OP2(Eb, Gb)}, {CMP, OP2(Ev, Gv)}, {CMP, OP2(Gb, Eb)}, {CMP, OP2(Gv, Ev)}, {CMP, OP2(Reg, Ib), AL}, {CMP, OP2(Reg, Iz), rAX}, {PrefixDS}, {AAS},
	/* 40h - 47h */
	{INC, OP1(Reg), eAX}, {INC, OP1(Reg), eCX}, {INC, OP1(Reg), eDX}, {INC, OP1(Reg), eBX}, {INC, OP1(Reg), eSP}, {INC, OP1(Reg), eBP}, {INC, OP1(Reg), eSI}, {INC, OP1(Reg), eDI},
	/* 48h - 4Fh */
	{DEC, OP1(Reg), eAX}, {DEC, OP1(Reg), eCX}, {DEC, OP1(Reg), eDX}, {DEC, OP1(Reg), eBX}, {DEC, OP1(Reg), eSP}, {DEC, OP1(Reg), eBP}, {DEC, OP1(Reg), eSI}, {DEC, OP1(Reg), eDI},
	/* 50h - 57h */
	{PUSH, OP1(Reg), rAX}, {PUSH, OP1(Reg), rCX}, {PUSH, OP1(Reg), rBX}, {PUSH, OP1(Reg), rDX}, {PUSH, OP1(Reg), rSP}, {PUSH, OP1(Reg), rBP}, {PUSH, OP1(Reg), rSI}, {PUSH, OP1(Reg), rDI},
	/* 57h - 5Fh */
	{POP , OP1(Reg), rAX}, {POP , OP1(Reg), rCX}, {POP , OP1(Reg), rBX}, {POP , OP1(Reg), rDX}, {POP , OP1(Reg), rSP}, {POP , OP1(Reg), rBP}, {POP , OP1(Reg), rSI}, {POP , OP1(Reg), rDI},
	/* 60h - 67h */
	{PUSHA}, {POPA}, {DB}, {DB}, {PrefixFS}, {PrefixGS}, {OperandSize}, {AddressSize},
	/* 68h - 6Fh */
	{PUSH, OP1(Iz)}, {IMUL, OP3(Gv, Ev, Iz)}, {PUSH, OP1(Ib)}, {IMUL, OP3(Gv, Ev, Ib)}, {INS, OP2(Yb, Reg), 0, DX}, {INS, OP2(Yz, Reg), 0, DX}, {OUTS, OP2(Reg, Xb), DX}, {OUTS, OP2(Reg, Xz), DX},
	/* 70h - 77h */
	{JO, OP1(Jb)}, {JNO, OP1(Jb)}, {JB, OP1(Jb)}, {JAE, OP1(Jb)}, {JE, OP1(Jb)}, {JNE, OP1(Jb)}, {JBE, OP1(Jb)}, {JA, OP1(Jb)},
	/* 78h - 7Fh */
	{JS, OP1(Jb)}, {JNS, OP1(Jb)}, {JP, OP1(Jb)}, {JNP, OP1(Jb)}, {JL, OP1(Jb)}, {JNL, OP1(Jb)}, {JLE, OP1(Jb)}, {JNLE, OP1(Jb)},
	/* 80h - 87h */
	{GROUP1, OP2(Eb, Ib)}, {GROUP1, OP2(Ev, Iz)}, {GROUP1, OP2(Eb, Ib)}, {GROUP1, OP2(Ev, Ib)}, {TEST, OP2(Eb, Gb)}, {TEST, OP2(Ev, Gv)}, {XCHG, OP2(Eb, Gb)}, {XCHG, OP2(Ev, Gv)},
	/* 88h - 8Fh */
	{MOV, OP2(Eb, Gb)}, {MOV, OP2(Ev, Gv)}, {MOV, OP2(Gb, Eb)}, {MOV, OP2(Gv, Ev)}, {MOV, OP2(Ev, Sw)}, {LEA, OP2(Gv, M)}, {MOV, OP2(Sw, Ev)}, {GROUP1A, OP1(Ev)},
	/* 90h - 97h */
	{NOP}, {XCHG, OP2(Reg, Reg), rCX, rAX}, {XCHG, OP2(Reg, Reg), rDX, rAX}, {XCHG, OP2(Reg, Reg), rBX, rAX}, {XCHG, OP2(Reg, Reg), rSP, rAX}, {XCHG, OP2(Reg, Reg), rBP, rAX}, {XCHG, OP2(Reg, Reg), rSI, rAX}, {XCHG, OP2(Reg, Reg), rDI, rAX},
	/* 98h - 9Fh */
	{CBW}, {CWD}, {DB}, {WAIT}, {PUSHF, OP1(Fv)}, {POPF, OP1(Fv)}, {SAHF}, {LAHF},
	/* A0h - A7h */
	{MOV, OP2(Reg, Ob), AL}, {MOV, OP2(Reg, Ov), rAX}, {MOV, OP2(Reg, Ob), AL}, {MOV, OP2(Ov, Reg), 0, rAX}, {MOVS, OP2(Yb, Xb)}, {MOVS, OP2(Yv, Xv)}, {CMPS, OP2(Yb, Xb)}, {CMPS, OP2(Yv, Xv)},
	/* A8h - AFh */
	{TEST, OP2(Reg, Ib), AL}, {TEST, OP2(Reg, Iz), rAX}, {STOS, OP2(Yb, Reg), 0, AL}, {STOS, OP2(Yv, Reg), 0, rAX}, {LODS, OP2(Reg, Xb), AL}, {LODS, OP2(Reg, Xv), rAX}, {SCAS, OP2(Reg, Yb), AL}, {SCAS, OP2(Reg, Yv), rAX},
	/* B0h - B7h */
	{MOV, OP2(Reg, Ib), AL}, {MOV, OP2(Reg, Ib), CL}, {MOV, OP2(Reg, Ib), DL}, {MOV, OP2(Reg, Ib), BL}, {MOV, OP2(Reg, Ib), AH}, {MOV, OP2(Reg, Ib), CH}, {MOV, OP2(Reg, Ib), DH}, {MOV, OP2(Reg, Ib), BH},
	/* B8h - BFh */
	{MOV, OP2(Reg, Iv), rAX}, {MOV, OP2(Reg, Iv), rCX}, {MOV, OP2(Reg, Iv), rBX}, {MOV, OP2(Reg, Iv), rDX}, {MOV, OP2(Reg, Iv), rSP}, {MOV, OP2(Reg, Iv), rBP}, {MOV, OP2(Reg, Iv), rSI}, {MOV, OP2(Reg, Iv), rDI},
	/* C0h - C7h */
	{GROUP2, OP2(Eb, Ib)}, {GROUP2, OP2(Ev, Ib)}, {RET, OP1(Iw)}, {RET}, {DB}, {DB}, {GROUP11, OP2(Eb, Ib)}, {GROUP11, OP2(Ev, Iv)},
	/* C8h - CFh */
	{ENTER, OP2(Iw, Ib)}, {LEAVE}, {RET, OP1(Iw)}, {RET}, {_INT, OP1(Imm), 3}, {_INT, OP1(Ib)}, {INTO}, {IRET},
	/* D0h - D7h */
	{GROUP2, OP2(Eb, Imm), 0, 1}, {GROUP2, OP2(Ev, Imm), 0, 1}, {GROUP2, OP2(Eb, Reg), 0, CL}, {GROUP2, OP2(Ev, Reg), 0, CL}, {AAM, OP1(Ib)}, {AAD, OP1(Ib)}, {SACL}, {XLAT},
	/* D8h - DFh */
	{ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87},
	/* E0h - E7h */
	{LOOPNE, OP1(Jb)}, {LOOPE, OP1(Jb)}, {LOOP, OP1(Jb)}, {JCXZ, OP1(Jb)}, {_IN, OP2(Reg, Ib), AL}, {_IN, OP2(Reg, Ib), eAX}, {_OUT, OP2(Ib, Reg), 0, AL}, {_OUT, OP2(Ib, Reg), eAX},
	/* E8h - EFh */
	{CALL, OP1(Jz)}, {JMP, OP1(Jz)}, {DB}, {JMP, OP1(Jb)}, {_IN, OP2(Reg, Reg), AL, DX}, {_IN, OP2(Reg, Reg), eAX, DX}, {_OUT, OP2(Reg, Reg), DL, AL}, {_OUT, OP2(Reg, Reg), DX, eAX},
	/* F0h - F7h */
	{LOCK}, {_INT, OP1(Imm), 1}, {REPNE}, {REP}, {HLT}, {CMC}, {GROUP3, OP1(Eb)}, {GROUP3, OP1(Ev)},
	/* F8h - FFh */
	{CLC}, {STC}, {CLI}, {STI}, {CLD}, {STD}, {GROUP4}, {GROUP5},
};

#endif /* __OPCODEMAPONEBYTE_H__ */
