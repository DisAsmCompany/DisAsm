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
0 X X X X         0 X X X X         0
1 X X X X         1 X X X X         1
2 X X X X     X X 2 X X X X     X X 2
3 X X X X     X X 3 X X X X     X X 3
4 X X X X X X X X 4 X X X X X X X X 4
5 X X X X X X X X 5 X X X X X X X X 5
6         X X X X 6                 6
7 X X X X X X X X 7 X X X X X X X X 7
  0 1 2 3 4 5 6 7   8 9 A B C D E F
8         X X X X 8 X X X X         8
9 X               9                 9
A X X             A                 A
B                 B X X X X X X X X B
C     X           C                 C
D                 D                 D
E                 E                 E
F X   X X         F               X F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

OpCodeMapElement OpCodeMapOneByte[] =
{
	/* 00h - 07h */
	{ADD, 2, Eb, 0, Gb, 0}, {ADD, 2, Ev, 0, Gv, 0}, {ADD, 2, Gb, 0, Eb, 0}, {ADD, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {DB},
	/* 08h - 0Fh */
	{OR , 2, Eb, 0, Gb, 0}, {OR , 2, Ev, 0, Gv, 0}, {OR , 2, Gb, 0, Eb, 0}, {OR , 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {DB},
	/* 10h - 17h */
	{ADC, 2, Eb, 0, Gb, 0}, {ADC, 2, Ev, 0, Gv, 0}, {ADC, 2, Gb, 0, Eb, 0}, {ADC, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {DB},
	/* 17h - 1Fh */
	{SBB, 2, Eb, 0, Gb, 0}, {SBB, 2, Ev, 0, Gv, 0}, {SBB, 2, Gb, 0, Eb, 0}, {SBB, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {DB},
	/* 20h - 27h */
	{AND, 2, Eb, 0, Gb, 0}, {AND, 2, Ev, 0, Gv, 0}, {AND, 2, Gb, 0, Eb, 0}, {AND, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {ES}, {DAA},
	/* 28h - 2Fh */
	{SUB, 2, Eb, 0, Gb, 0}, {SUB, 2, Ev, 0, Gv, 0}, {SUB, 2, Gb, 0, Eb, 0}, {SUB, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {CS}, {DAS},
	/* 30h - 37h */
	{XOR, 2, Eb, 0, Gb, 0}, {XOR, 2, Ev, 0, Gv, 0}, {XOR, 2, Gb, 0, Eb, 0}, {XOR, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {AAA},
	/* 38h - 3Fh */
	{CMP, 2, Eb, 0, Gb, 0}, {CMP, 2, Ev, 0, Gv, 0}, {CMP, 2, Gb, 0, Eb, 0}, {CMP, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {SS}, {AAS},
	/* 40h - 47h */
	{INC, 1, Reg, eAX}, {INC, 1, Reg, eCX}, {INC, 1, Reg, eDX}, {INC, 1, Reg, eBX}, {INC, 1, Reg, eSP}, {INC, 1, Reg, eBP}, {INC, 1, Reg, eSI}, {INC, 1, Reg, eDI},
	/* 48h - 4Fh */
	{DEC, 1, Reg, eAX}, {DEC, 1, Reg, eCX}, {DEC, 1, Reg, eDX}, {DEC, 1, Reg, eBX}, {DEC, 1, Reg, eSP}, {DEC, 1, Reg, eBP}, {DEC, 1, Reg, eSI}, {DEC, 1, Reg, eDI},
	/* 50h - 57h */
	{PUSH, 1, Reg, rAX}, {PUSH, 1, Reg, rCX}, {PUSH, 1, Reg, rBX}, {PUSH, 1, Reg, rDX}, {PUSH, 1, Reg, rSP}, {PUSH, 1, Reg, rBP}, {PUSH, 1, Reg, rSI}, {PUSH, 1, Reg, rDI},
	/* 57h - 5Fh */
	{POP , 1, Reg, rAX}, {POP , 1, Reg, rCX}, {POP , 1, Reg, rBX}, {POP , 1, Reg, rDX}, {POP , 1, Reg, rSP}, {POP , 1, Reg, rBP}, {POP , 1, Reg, rSI}, {POP , 1, Reg, rDI},
	/* 60h - 67h */
	{DB}, {DB}, {DB}, {DB}, {FS}, {GS}, {OperandSize}, {AddressSize},
	/* 68h - 6Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 70h - 77h */
	{JO, 1, Jb}, {JNO, 1, Jb}, {JB, 1, Jb}, {JAE, 1, Jb}, {JE, 1, Jb}, {JNE, 1, Jb}, {JBE, 1, Jb}, {JA, 1, Jb},
	/* 78h - 7Fh */
	{JS, 1, Jb}, {JNS, 1, Jb}, {JP, 1, Jb}, {JNP, 1, Jb}, {JL, 1, Jb}, {JNL, 1, Jb}, {JLE, 1, Jb}, {JNLE, 1, Jb},
	/* 80h - 87h */
	{DB}, {DB}, {DB}, {DB}, {TEST, 2, Eb, 0, Gb, 0}, {TEST, 2, Ev, 0, Gv, 0}, {XCHG, 2, Eb, 0, Gb, 0}, {XCHG, 2, Ev, 0, Gv, 0},
	/* 88h - 8Fh */
	{MOV, 2, Eb, 0, Gb, 0}, {MOV, 2, Ev, 0, Gv, 0}, {MOV, 2, Gb, 0, Eb, 0}, {MOV, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {DB},
	/* 90h - 97h */
	{NOP}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 98h - 9Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* A0h - A7h */
	{MOV, 2, Reg, AL, Ob, 0}, {DB}, {MOV, 2, Ob, 0, Reg, AL}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* A8h - AFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* B0h - B7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* B8h - BFh */
	{MOV, 2, Reg, rAX, Iv, 0}, {MOV, 2, Reg, rCX, Iv, 0}, {MOV, 2, Reg, rBX, Iv, 0}, {MOV, 2, Reg, rDX, Iv, 0}, {MOV, 2, Reg, rSP, Iv, 0}, {MOV, 2, Reg, rBP, Iv, 0}, {MOV, 2, Reg, rSI, Iv, 0}, {MOV, 2, Reg, rDI, Iv, 0},
	/* C0h - C7h */
	{DB}, {DB}, {RET, 1, Iw, 0}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* C8h - CFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* D0h - D7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* D8h - DFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* E0h - E7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* E8h - EFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* F0h - F7h */
	{LOCK}, {DB}, {REPNE}, {REP}, {HLT}, {CMC}, {DB}, {DB},
	/* F8h - FFh */
	{CLC}, {STC}, {CLI}, {STI}, {CLD}, {STD}, {DB}, {GROUP5},
};

#endif /* __OPCODEMAPONEBYTE_H__ */
