/*
* Filename: OpCodeMapTwoByte0F.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh)
*              
*              
*
*/

#ifndef __OPCODEMAPTWOBYTE0F_H__
#define __OPCODEMAPTWOBYTE0F_H__

/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh) */

/* 
  0 1 2 3 4 5 6 7   8 9 A B C D E F
0                 0       X         0
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

OpCodeMapElement OpCodeMapTwoByte0F[] =
{
	/* 0F00h - 0F07h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F08h - 0F0Fh */
	{DB}, {DB}, {DB}, {UD2}, {DB}, {DB}, {DB}, {DB},
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

#endif /* __OPCODEMAPTWOBYTE0F_H__ */
