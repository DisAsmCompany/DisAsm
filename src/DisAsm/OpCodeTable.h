/*
* Filename: OpCodeTable.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: table of x86 opcodes :
*              opcode <-> info
*              (mnemonic, etc)
*
*/

#pragma once
#ifndef __OPCODETABLE_H__
#define __OPCODETABLE_H__

typedef struct OpCodeTableElement_t
{
	Mnemonic mnemonic;
	int operands;
	OperandType operand1type;
	Register reg1;
	OperandType operand2type;
	Register reg2;
	OperandType operand3type;
	Register reg3;
}
OpCodeTableElement;

/* Primary Opcode Table (OpCodes 00h - FFh) */

/* 
  0 1 2 3 4 5 6 7   8 9 A B C D E F
0 X X X X         0 X X X X         0
1 X X X X         1 X X X X         1
2 X X X X       X 2 X X X X       X 2
3 X X X X       X 3 X X X X       X 3
4                 4                 4
5 X X X X X X X X 5 X X X X X X X X 5
6                 6                 6
7 X X X X X X X X 7 X X X X X X X X 7
  0 1 2 3 4 5 6 7   8 9 A B C D E F
8                 8 X X X X         8
9 X               9                 9
A                 A                 A
B                 B X X X X X X X X B
C                 C                 C
D                 D                 D
E                 E                 E
F                 F                 F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

OpCodeTableElement PrimaryOpcodeTable[] =
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
	{AND, 2, Eb, 0, Gb, 0}, {AND, 2, Ev, 0, Gv, 0}, {AND, 2, Gb, 0, Eb, 0}, {AND, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {DAA},
	/* 28h - 2Fh */
	{SUB, 2, Eb, 0, Gb, 0}, {SUB, 2, Ev, 0, Gv, 0}, {SUB, 2, Gb, 0, Eb, 0}, {SUB, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {DAS},
	/* 30h - 37h */
	{XOR, 2, Eb, 0, Gb, 0}, {XOR, 2, Ev, 0, Gv, 0}, {XOR, 2, Gb, 0, Eb, 0}, {XOR, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {AAA},
	/* 38h - 3Fh */
	{CMP, 2, Eb, 0, Gb, 0}, {CMP, 2, Ev, 0, Gv, 0}, {CMP, 2, Gb, 0, Eb, 0}, {CMP, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {AAS},
	/* 40h - 47h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 48h - 4Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 50h - 57h */
	{PUSH, 1, Reg, rAX}, {PUSH, 1, Reg, rCX}, {PUSH, 1, Reg, rBX}, {PUSH, 1, Reg, rDX}, {PUSH, 1, Reg, rSP}, {PUSH, 1, Reg, rBP}, {PUSH, 1, Reg, rSI}, {PUSH, 1, Reg, rDI},
	/* 57h - 5Fh */
	{POP , 1, Reg, rAX}, {POP , 1, Reg, rCX}, {POP , 1, Reg, rBX}, {POP , 1, Reg, rDX}, {POP , 1, Reg, rSP}, {POP , 1, Reg, rBP}, {POP , 1, Reg, rSI}, {POP , 1, Reg, rDI},
	/* 60h - 67h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 68h - 6Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 70h - 77h */
	{JO, 1, Jb}, {JNO, 1, Jb}, {JB, 1, Jb}, {JAE, 1, Jb}, {JE, 1, Jb}, {JNE, 1, Jb}, {JBE, 1, Jb}, {JA, 1, Jb},
	/* 78h - 7Fh */
	{JS, 1, Jb}, {JNS, 1, Jb}, {JP, 1, Jb}, {JNP, 1, Jb}, {JL, 1, Jb}, {JNL, 1, Jb}, {JLE, 1, Jb}, {JNLE, 1, Jb},
	/* 80h - 87h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 88h - 8Fh */
	{MOV, 2, Eb, 0, Gb, 0}, {MOV, 2, Ev, 0, Gv, 0}, {MOV, 2, Gb, 0, Eb, 0}, {MOV, 2, Gv, 0, Ev, 0}, {DB}, {DB}, {DB}, {DB},
	/* 90h - 97h */
	{NOP}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 98h - 9Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* A0h - A7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* A8h - AFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* B0h - B7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* B8h - BFh */
	{MOV, 2, Reg, rAX, Iv, 0}, {MOV, 2, Reg, rCX, Iv, 0}, {MOV, 2, Reg, rBX, Iv, 0}, {MOV, 2, Reg, rDX, Iv, 0}, {MOV, 2, Reg, rSP, Iv, 0}, {MOV, 2, Reg, rBP, Iv, 0}, {MOV, 2, Reg, rSI, Iv, 0}, {MOV, 2, Reg, rDI, Iv, 0},
	/* C0h - C7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
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
	{DB}, {DB}, {DB}, {DB}, {HLT}, {CMC}, {DB}, {DB},
	/* F8h - FFh */
	{CLC}, {STC}, {CLI}, {STI}, {CLD}, {STD}, {DB}, {DB},
};

/* Secondary Opcode Table (OpCodes 0F00h - 0FFFh) */

/* 
  0 1 2 3 4 5 6 7   8 9 A B C D E F
0                 0                 0
1                 1                 1
2                 2                 2
3                 3                 3
4 X X X X X X X X 4 X X X X X X X X 4
5                 5                 5
6                 6                 6
7                 7                 7
  0 1 2 3 4 5 6 7   8 9 A B C D E F
8 X X X X X X X X 8 X X X X X X X X 8
9 X X X X X X X X 9 X X X X X X X X 9
A     X           A                 A
B                 B                 B
C                 C                 C
D                 D                 D
E                 E                 E
F                 F                 F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

OpCodeTableElement SecondaryOpcodeTable[] =
{
	/* 0F00h - 0F07h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F08h - 0F0Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F10h - 0F17h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F17h - 0F1Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F20h - 0F27h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F28h - 0F2Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F30h - 0F37h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38h - 0F3Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F40h - 0F47h */
	{CMOVO, 2, Gv, 0, Ev, 0}, {CMOVNO, 2, Gv, 0, Ev, 0}, {CMOVB, 2, Gv, 0, Ev, 0}, {CMOVAE, 2, Gv, 0, Ev, 0}, {CMOVE, 2, Gv, 0, Ev, 0}, {CMOVNE, 2, Gv, 0, Ev, 0}, {CMOVBE, 2, Gv, 0, Ev, 0}, {CMOVA, 2, Gv, 0, Ev, 0},
	/* 0F48h - 0F4Fh */
	{CMOVS, 2, Gv, 0, Ev, 0}, {CMOVNS, 2, Gv, 0, Ev, 0}, {CMOVP, 2, Gv, 0, Ev, 0}, {CMOVNP, 2, Gv, 0, Ev, 0}, {CMOVL, 2, Gv, 0, Ev, 0}, {CMOVNL, 2, Gv, 0, Ev, 0}, {CMOVLE, 2, Gv, 0, Ev, 0}, {CMOVNLE, 2, Gv, 0, Ev, 0},
	/* 0F50h - 0F57h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F57h - 0F5Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F60h - 0F67h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F68h - 0F6Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F70h - 0F77h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F78h - 0F7Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F80h - 0F87h */
	{JO, 1, Jz}, {JNO, 1, Jz}, {JB, 1, Jz}, {JAE, 1, Jz}, {JE, 1, Jz}, {JNE, 1, Jz}, {JBE, 1, Jz}, {JA, 1, Jz},
	/* 0F88h - 0F8Fh */
	{JS, 1, Jz}, {JNS, 1, Jz}, {JP, 1, Jz}, {JNP, 1, Jz}, {JL, 1, Jz}, {JNL, 1, Jz}, {JLE, 1, Jz}, {JNLE, 1, Jz},
	/* 0F90h - 0F97h */
	{SETO, 1, Jz}, {SETNO, 1, Jz}, {SETB, 1, Jz}, {SETAE, 1, Jz}, {SETE, 1, Jz}, {SETNE, 1, Jz}, {SETBE, 1, Jz}, {SETA, 1, Jz},
	/* 0F98h - 0F9Fh */
	{SETS, 1, Jz}, {SETNS, 1, Jz}, {SETP, 1, Jz}, {SETNP, 1, Jz}, {SETL, 1, Jz}, {SETNL, 1, Jz}, {SETLE, 1, Jz}, {SETNLE, 1, Jz},
	/* 0FA0h - 0FA7h */
	{DB}, {DB}, {CPUID}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FA8h - 0FAFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FB0h - 0FB7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FB8h - 0FBFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FC0h - 0FC7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FC8h - 0FCFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FD0h - 0FD7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FD8h - 0FDFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FE0h - 0FE7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FE8h - 0FEFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FF0h - 0FF7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FF8h - 0FFFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
};

#endif // __OPCODETABLE_H__
