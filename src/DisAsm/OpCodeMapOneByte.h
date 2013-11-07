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
6 X X   X P P P P 6 X X X X X X X X 6
7 X X X X X X X X 7 X X X X X X X X 7
  0 1 2 3 4 5 6 7   8 9 A B C D E F
8 X X X X X X X X 8 X X X X X X X X 8
9 X X X X X X X X 9 X X   X X X X X 9
A X X X X X X X X A X X X X X X X X A
B X X X X X X X X B X X X X X X X X B
C X X X X     X X C X X X X X X X X C
D X X X X X X X X D + + + + + + + + D
E X X X X X X X X E X X X X X X X X E
F P X P P X X X X F X X X X X X X X F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

OpCodeMapElement OpCodeMapOneByte[] =
{
	/* 00h - 07h */
	{ADD, OP2(Eb, Gb)}, {ADD, OP2(Ev, Gv)}, {ADD, OP2(Gb, Eb)}, {ADD, OP2(Gv, Ev)}, {ADD, OP2(AL, Ib)}, {ADD, OP2(rAX, Iz)}, {PUSH, OP1(ES)}, {POP, OP1(ES)},
	/* 08h - 0Fh */
	{OR , OP2(Eb, Gb)}, {OR , OP2(Ev, Gv)}, {OR , OP2(Gb, Eb)}, {OR , OP2(Gv, Ev)}, {OR , OP2(AL, Ib)}, {OR , OP2(rAX, Iz)}, {PUSH, OP1(CS)}, {ESCAPE},
	/* 10h - 17h */
	{ADC, OP2(Eb, Gb)}, {ADC, OP2(Ev, Gv)}, {ADC, OP2(Gb, Eb)}, {ADC, OP2(Gv, Ev)}, {ADC, OP2(AL, Ib)}, {ADC, OP2(rAX, Iz)}, {PUSH, OP1(SS)}, {POP, OP1(SS)},
	/* 17h - 1Fh */
	{SBB, OP2(Eb, Gb)}, {SBB, OP2(Ev, Gv)}, {SBB, OP2(Gb, Eb)}, {SBB, OP2(Gv, Ev)}, {SBB, OP2(AL, Ib)}, {SBB, OP2(rAX, Iz)}, {PUSH, OP1(DS)}, {POP, OP1(DS)},
	/* 20h - 27h */
	{AND, OP2(Eb, Gb)}, {AND, OP2(Ev, Gv)}, {AND, OP2(Gb, Eb)}, {AND, OP2(Gv, Ev)}, {AND, OP2(AL, Ib)}, {AND, OP2(rAX, Iz)}, {PrefixES}, {DAA},
	/* 28h - 2Fh */
	{SUB, OP2(Eb, Gb)}, {SUB, OP2(Ev, Gv)}, {SUB, OP2(Gb, Eb)}, {SUB, OP2(Gv, Ev)}, {SUB, OP2(AL, Ib)}, {SUB, OP2(rAX, Iz)}, {PrefixCS}, {DAS},
	/* 30h - 37h */
	{XOR, OP2(Eb, Gb)}, {XOR, OP2(Ev, Gv)}, {XOR, OP2(Gb, Eb)}, {XOR, OP2(Gv, Ev)}, {XOR, OP2(AL, Ib)}, {XOR, OP2(rAX, Iz)}, {PrefixSS}, {AAA},
	/* 38h - 3Fh */
	{CMP, OP2(Eb, Gb)}, {CMP, OP2(Ev, Gv)}, {CMP, OP2(Gb, Eb)}, {CMP, OP2(Gv, Ev)}, {CMP, OP2(AL, Ib)}, {CMP, OP2(rAX, Iz)}, {PrefixDS}, {AAS},
	/* 40h - 47h */
	{INC, OP1(eAX)}, {INC, OP1(eCX)}, {INC, OP1(eDX)}, {INC, OP1(eBX)}, {INC, OP1(eSP)}, {INC, OP1(eBP)}, {INC, OP1(eSI)}, {INC, OP1(eDI)},
	/* 48h - 4Fh */
	{DEC, OP1(eAX)}, {DEC, OP1(eCX)}, {DEC, OP1(eDX)}, {DEC, OP1(eBX)}, {DEC, OP1(eSP)}, {DEC, OP1(eBP)}, {DEC, OP1(eSI)}, {DEC, OP1(eDI)},
	/* 50h - 57h */
	{PUSH, OP1(rAX)}, {PUSH, OP1(rCX)}, {PUSH, OP1(rBX)}, {PUSH, OP1(rDX)}, {PUSH, OP1(rSP)}, {PUSH, OP1(rBP)}, {PUSH, OP1(rSI)}, {PUSH, OP1(rDI)},
	/* 57h - 5Fh */
	{POP , OP1(rAX)}, {POP , OP1(rCX)}, {POP , OP1(rBX)}, {POP , OP1(rDX)}, {POP , OP1(rSP)}, {POP , OP1(rBP)}, {POP , OP1(rSI)}, {POP , OP1(rDI)},
	/* 60h - 67h */
	{PUSHA}, {POPA}, {DB}, {ARPL, OP2(Ew, Gw)}, {PrefixFS}, {PrefixGS}, {OperandSize}, {AddressSize},
	/* 68h - 6Fh */
	{PUSH, OP1(Iz)}, {IMUL, OP3(Gv, Ev, Iz)}, {PUSH, OP1(Ib)}, {IMUL, OP3(Gv, Ev, Ib)}, {INS, OP2(Yb, DX)}, {INS, OP2(Yz, DX)}, {OUTS, OP2(DX, Xb)}, {OUTS, OP2(DX, Xz)},
	/* 70h - 77h */
	{JO, OP1(Jb)}, {JNO, OP1(Jb)}, {JB, OP1(Jb)}, {JAE, OP1(Jb)}, {JE, OP1(Jb)}, {JNE, OP1(Jb)}, {JBE, OP1(Jb)}, {JA, OP1(Jb)},
	/* 78h - 7Fh */
	{JS, OP1(Jb)}, {JNS, OP1(Jb)}, {JP, OP1(Jb)}, {JNP, OP1(Jb)}, {JL, OP1(Jb)}, {JNL, OP1(Jb)}, {JLE, OP1(Jb)}, {JNLE, OP1(Jb)},
	/* 80h - 87h */
	{GROUP1, OP2(Eb, Ib)}, {GROUP1, OP2(Ev, Iz)}, {GROUP1, OP2(Eb, Ib)}, {GROUP1, OP2(Ev, Ib)}, {TEST, OP2(Eb, Gb)}, {TEST, OP2(Ev, Gv)}, {XCHG, OP2(Eb, Gb)}, {XCHG, OP2(Ev, Gv)},
	/* 88h - 8Fh */
	{MOV, OP2(Eb, Gb)}, {MOV, OP2(Ev, Gv)}, {MOV, OP2(Gb, Eb)}, {MOV, OP2(Gv, Ev)}, {MOV, OP2(Ev, Sw)}, {LEA, OP2(Gv, M)}, {MOV, OP2(Sw, Ev)}, {GROUP1A, OP1(Ev)},
	/* 90h - 97h */
	{NOP}, {XCHG, OP2(rCX, rAX)}, {XCHG, OP2(rDX, rAX)}, {XCHG, OP2(rBX, rAX)}, {XCHG, OP2(rSP, rAX)}, {XCHG, OP2(rBP, rAX)}, {XCHG, OP2(rSI, rAX)}, {XCHG, OP2(rDI, rAX)},
	/* 98h - 9Fh */
	{CBW}, {CWD}, {DB}, {WAIT}, {PUSHF, OP1(Fv)}, {POPF, OP1(Fv)}, {SAHF}, {LAHF},
	/* A0h - A7h */
	{MOV, OP2(AL, Ob)}, {MOV, OP2(rAX, Ov)}, {MOV, OP2(AL, Ob)}, {MOV, OP2(Ov, rAX)}, {MOVS, OP2(Yb, Xb)}, {MOVS, OP2(Yv, Xv)}, {CMPS, OP2(Yb, Xb)}, {CMPS, OP2(Yv, Xv)},
	/* A8h - AFh */
	{TEST, OP2(AL, Ib)}, {TEST, OP2(rAX, Iz)}, {STOS, OP2(Yb, AL)}, {STOS, OP2(Yv, rAX)}, {LODS, OP2(AL, Xb)}, {LODS, OP2(rAX, Xv)}, {SCAS, OP2(AL, Yb)}, {SCAS, OP2(rAX, Yv)},
	/* B0h - B7h */
	{MOV, OP2(AL, Ib)}, {MOV, OP2(CL, Ib)}, {MOV, OP2(DL, Ib)}, {MOV, OP2(BL, Ib)}, {MOV, OP2(AH, Ib)}, {MOV, OP2(CH, Ib)}, {MOV, OP2(DH, Ib)}, {MOV, OP2(BH, Ib)},
	/* B8h - BFh */
	{MOV, OP2(rAX, Iv)}, {MOV, OP2(rCX, Iv)}, {MOV, OP2(rBX, Iv)}, {MOV, OP2(rDX, Iv)}, {MOV, OP2(rSP, Iv)}, {MOV, OP2(rBP, Iv)}, {MOV, OP2(rSI, Iv)}, {MOV, OP2(rDI, Iv)},
	/* C0h - C7h */
	{GROUP2, OP2(Eb, Ib)}, {GROUP2, OP2(Ev, Ib)}, {RET, OP1(Iw)}, {RET}, {DB}, {DB}, {GROUP11, OP2(Eb, Ib)}, {GROUP11, OP2(Ev, Iv)},
	/* C8h - CFh */
	{ENTER, OP2(Iw, Ib)}, {LEAVE}, {RET, OP1(Iw)}, {RET}, {_INT, OP1(3)}, {_INT, OP1(Ib)}, {INTO}, {IRET},
	/* D0h - D7h */
	{GROUP2, OP2(Eb, 1)}, {GROUP2, OP2(Ev, 1)}, {GROUP2, OP2(Eb, CL)}, {GROUP2, OP2(Ev, CL)}, {AAM, OP1(Ib)}, {AAD, OP1(Ib)}, {SACL}, {XLAT},
	/* D8h - DFh */
	{ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87}, {ESCAPEX87},
	/* E0h - E7h */
	{LOOPNE, OP1(Jb)}, {LOOPE, OP1(Jb)}, {LOOP, OP1(Jb)}, {JCXZ, OP1(Jb)}, {_IN, OP2(AL, Ib)}, {_IN, OP2(eAX, Ib)}, {_OUT, OP2(Ib, AL)}, {_OUT, OP2(Ib, eAX)},
	/* E8h - EFh */
	{CALL, OP1(Jz)}, {JMP, OP1(Jz)}, {JMP, OP1(Ap)}, {JMP, OP1(Jb)}, {_IN, OP2(AL, DX)}, {_IN, OP2(eAX, DX)}, {_OUT, OP2(DL, AL)}, {_OUT, OP2(DX, eAX)},
	/* F0h - F7h */
	{LOCK}, {_INT, OP1(1)}, {REPNE}, {REP}, {HLT}, {CMC}, {GROUP3, OP1(Eb)}, {GROUP3, OP1(Ev)},
	/* F8h - FFh */
	{CLC}, {STC}, {CLI}, {STI}, {CLD}, {STD}, {GROUP4}, {GROUP5},
};

#endif /* __OPCODEMAPONEBYTE_H__ */
