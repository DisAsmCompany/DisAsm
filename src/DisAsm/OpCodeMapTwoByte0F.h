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
0     X X   X X X 0 X X   X   X X + 0
1                 1 X X X X X X X X 1
2                 2                 2
3 X X X X X X     3 +   +           3
4 X X X X X X X X 4 X X X X X X X X 4
5                 5                 5
6                 6                 6
7                 7                 7
  0 1 2 3 4 5 6 7   8 9 A B C D E F
8 X X X X X X X X 8 X X X X X X X X 8
9 X X X X X X X X 9 X X X X X X X X 9
A X X X   X X     A X X X   X X X X A
B X X         X X B   X         X X B
C X X             C X X X X X X X X C
D                 D                 D
E                 E                 E
F                 F               X F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

OpCodeMapElement OpCodeMapTwoByte0F[] =
{
	/* 0F00h - 0F07h */
	{DB}, {DB}, {LAR, OP2(Gv, Ew)}, {LSL, OP2(Gv, Ew)}, {DB}, {SYSCALL}, {CLTS}, {SYSRET},
	/* 0F08h - 0F0Fh */
	{INVD}, {WBINVD}, {DB}, {UD2}, {DB}, {GROUPP}, {FEMMS}, {ESCAPE3DNOW},
	/* 0F10h - 0F17h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F18h - 0F1Fh */
	{GROUP16}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)},
	/* 0F20h - 0F27h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F28h - 0F2Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F30h - 0F37h */
	{WRMSR}, {RDTSC}, {RDMSR}, {RDPMC}, {SYSENTER}, {SYSEXIT}, {DB}, {DB},
	/* 0F38h - 0F3Fh */
	{ESCAPE}, {DB}, {ESCAPE}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F40h - 0F47h */
	{CMOVO, OP2(Gv, Ev)}, {CMOVNO, OP2(Gv, Ev)}, {CMOVB, OP2(Gv, Ev)}, {CMOVAE, OP2(Gv, Ev)}, {CMOVE, OP2(Gv, Ev)}, {CMOVNE, OP2(Gv, Ev)}, {CMOVBE, OP2(Gv, Ev)}, {CMOVA, OP2(Gv, Ev)},
	/* 0F48h - 0F4Fh */
	{CMOVS, OP2(Gv, Ev)}, {CMOVNS, OP2(Gv, Ev)}, {CMOVP, OP2(Gv, Ev)}, {CMOVNP, OP2(Gv, Ev)}, {CMOVL, OP2(Gv, Ev)}, {CMOVNL, OP2(Gv, Ev)}, {CMOVLE, OP2(Gv, Ev)}, {CMOVNLE, OP2(Gv, Ev)},
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
	{JO, OP1(Jz)}, {JNO, OP1(Jz)}, {JB, OP1(Jz)}, {JAE, OP1(Jz)}, {JE, OP1(Jz)}, {JNE, OP1(Jz)}, {JBE, OP1(Jz)}, {JA, OP1(Jz)},
	/* 0F88h - 0F8Fh */
	{JS, OP1(Jz)}, {JNS, OP1(Jz)}, {JP, OP1(Jz)}, {JNP, OP1(Jz)}, {JL, OP1(Jz)}, {JNL, OP1(Jz)}, {JLE, OP1(Jz)}, {JNLE, OP1(Jz)},
	/* 0F90h - 0F97h */
	{SETO, OP1(Eb)}, {SETNO, OP1(Eb)}, {SETB, OP1(Eb)}, {SETAE, OP1(Eb)}, {SETE, OP1(Eb)}, {SETNE, OP1(Eb)}, {SETBE, OP1(Eb)}, {SETA, OP1(Eb)},
	/* 0F98h - 0F9Fh */
	{SETS, OP1(Eb)}, {SETNS, OP1(Eb)}, {SETP, OP1(Eb)}, {SETNP, OP1(Eb)}, {SETL, OP1(Eb)}, {SETNL, OP1(Eb)}, {SETLE, OP1(Eb)}, {SETNLE, OP1(Eb)},
	/* 0FA0h - 0FA7h */
	{PUSH, OP1(Reg), FS}, {POP, OP1(Reg), FS}, {CPUID}, {DB}, {SHLD, OP3(Ev, Gv, Ib)}, {SHLD, OP3(Ev, Gv, Reg), 0, 0, CL}, {DB}, {DB},
	/* 0FA8h - 0FAFh */
	{PUSH, OP1(Reg), GS}, {POP, OP1(Reg), GS}, {RSM}, {DB}, {SHRD, OP3(Ev, Gv, Ib)}, {SHRD, OP3(Ev, Gv, Reg), 0, 0, CL}, {GROUP15}, {IMUL, OP2(Gv, Ev)},
	/* 0FB0h - 0FB7h */
	{CMPXCHG, OP2(Eb, Gb)}, {CMPXCHG, OP2(Ev, Gv)}, {DB}, {DB}, {DB}, {DB}, {MOVZX, OP2(Gv, Eb)}, {MOVZX, OP2(Gv, Ew)},
	/* 0FB8h - 0FBFh */
	{DB}, {GROUP10}, {DB}, {DB}, {DB}, {DB}, {MOVSX, OP2(Gv, Eb)}, {MOVSX, OP2(Gv, Ev)},
	/* 0FC0h - 0FC7h */
	{XADD, OP2(Eb, Gb)}, {XADD, OP2(Ev, Gv)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FC8h - 0FCFh */
	{BSWAP, OP1(Reg), rAX}, {BSWAP, OP1(Reg), rCX}, {BSWAP, OP1(Reg), rDX}, {BSWAP, OP1(Reg), rBX}, {BSWAP, OP1(Reg), rSP}, {BSWAP, OP1(Reg), rBP}, {BSWAP, OP1(Reg), rSI}, {BSWAP, OP1(Reg), rDI},
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
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {UD0},
};

#endif /* __OPCODEMAPTWOBYTE0F_H__ */
