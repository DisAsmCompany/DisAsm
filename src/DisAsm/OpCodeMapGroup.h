/*
* Filename: OpCodeMapGroup.h
* Author:   DisAsmCompany
* Date:     06/10/2013
*
* Description: Opcode Map for GROUP extensions
*              (GROUP1 - GROUPP)
*              
*
*/

#pragma once
#ifndef __OPCODEMAPGROUP_H__72610EBD_86E1_43E0_817F_90F132DAFD69__
#define __OPCODEMAPGROUP_H__72610EBD_86E1_43E0_817F_90F132DAFD69__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

OpCodeMapElement OpCodeMapGroup[] =
{
	/* GROUP1 */
	{ADD, OP0}, {OR, OP0}, {ADC, OP0}, {SBB, OP0}, {AND, OP0}, {SUB, OP0}, {XOR, OP0}, {CMP, OP0},
	/* GROUP1A */
	{POP, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* GROUP2 */
	/*
	Intel doesn't define /6 form
	AMD defines both /4 and /6 as SHL/SAL (that are essentially same instruction)
	*/
	{ROL, OP0}, {ROR, OP0}, {RCL, OP0}, {RCR, OP0}, {SHL, OP0}, {SHR, OP0}, {SAL, OP0}, {SAR, OP0},
	/* GROUP3 (opcode F6) */
	{TEST, OP2(Eb, Ib)}, {TEST, OP2(Eb, Ib)}, {NOT, OP0}, {NEG, OP0}, {MUL, OP0}, {IMUL, OP0}, {DIV, OP0}, {IDIV, OP0},
	/* GROUP3 (opcode F7) */
	{TEST, OP2(Ev, Iz)}, {TEST, OP2(Ev, Iz)}, {NOT, OP0}, {NEG, OP0}, {MUL, OP0}, {IMUL, OP0}, {DIV, OP0}, {IDIV, OP0},
	/* GROUP4 */
	{INC, OP1(Eb)}, {DEC, OP1(Eb)}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* GROUP5 */
	{INC, OP1(Ev)}, {DEC, OP1(Ev)}, {CALL, OP1(Ev)}, {CALL, OP1(Mp)}, {JMP, OP1(Ev)}, {JMP, OP1(Mp)}, {PUSH, OP1(Ev)}, {DB, OP0},
	/* GROUP6 */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* GROUP7 */
	{DB, OP0}, {DB, OP0}, {GROUP7_EXT2, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* GROUP7 (/2) */
	{XGETBV, OP0}, {XSETBV, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* GROUP8 */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {BT, OP0}, {BTS, OP0}, {BTR, OP0}, {BTC, OP0},
	/* GROUP9 */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* GROUP10 */
	/*
	according to AMD manual, all GROUP10 variants are defined as UD1
	according to Intel, it is just unnamed undefined instructions
	*/
	{UD1, OP0}, {UD1, OP0}, {UD1, OP0}, {UD1, OP0}, {UD1, OP0}, {UD1, OP0}, {UD1, OP0}, {UD1, OP0},
	/* GROUP11 */
	{MOV, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* GROUP12 */
	{DB, OP0}, {DB, OP0}, {PSRLW, OP2(Nq, Ib)}, {DB, OP0},             {PSRAW, OP2(Nq, Ib)}, {DB, OP0}, {PSLLW, OP2(Nq, Ib)}, {DB, OP0},
	/* GROUP12 (prefix 0x66) */
	{DB, OP0}, {DB, OP0}, {PSRLW, OP2(Uo, Ib)}, {DB, OP0},             {PSRAW, OP2(Uo, Ib)}, {DB, OP0}, {PSLLW, OP2(Uo, Ib)}, {DB, OP0},
	/* GROUP13 */
	{DB, OP0}, {DB, OP0}, {PSRLD, OP2(Nq, Ib)}, {DB, OP0},             {PSRAD, OP2(Nq, Ib)}, {DB, OP0}, {PSLLD, OP2(Nq, Ib)}, {DB, OP0},
	/* GROUP13 (prefix 0x66) */
	{DB, OP0}, {DB, OP0}, {PSRLD, OP2(Uo, Ib)}, {DB, OP0},             {PSRAD, OP2(Uo, Ib)}, {DB, OP0}, {PSLLD, OP2(Uo, Ib)}, {DB, OP0},
	/* GROUP14 */
	{DB, OP0}, {DB, OP0}, {PSRLQ, OP2(Nq, Ib)}, {DB, OP0},             {DB, OP0},            {DB, OP0}, {PSLLQ, OP2(Nq, Ib)}, {DB, OP0},
	/* GROUP14 (prefix 0x66) */
	{DB, OP0}, {DB, OP0}, {PSRLQ, OP2(Uo, Ib)}, {PSRLDQ, OP2(Uo, Ib)}, {DB, OP0},            {DB, OP0}, {PSLLQ, OP2(Uo, Ib)}, {PSLLDQ, OP2(Uo, Ib)},
	/* GROUP15 */
	{FXSAVE, OP1(M)}, {FXRSTOR, OP1(M)}, {LDMXCSR, OP1(Md)}, {STMXCSR, OP1(Md)}, {DB, OP0}, {LFENCE, OP0}, {MFENCE, OP0}, {SFENCE, OP0},
	/* GROUP16 */
	/*
	according to AMD manual, /4 - /7 forms are defines as valid instructions (NOPs)
	for compatibility with future PREFETCH instructions
	*/
	{PREFETCHNTA, OP0}, {PREFETCHT0, OP0}, {PREFETCHT1, OP0}, {PREFETCHT2, OP0}, {NOP, OP0}, {NOP, OP0}, {NOP, OP0}, {NOP, OP0},
	/* GROUP17 */
	/* SSE4A - appears in AMD manual but not in Intel */
	{EXTRQ, OP3(Voq, Ib, Ib)}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* GROUPP */
	/*
	Intel defines just /0 for PREFETCHW
	AMD defines /0, /1 and /3, others are aliases to /0 for compatibility with future PREFETCH instructions
	*/
	{PREFETCHW, OP0}, {PREFETCHW, OP0}, {PREFETCHW, OP0}, {PREFETCHW, OP0}, {PREFETCHW, OP0}, {PREFETCHW, OP0}, {PREFETCHW, OP0}, {PREFETCHW, OP0},
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPCODEMAPGROUP_H__72610EBD_86E1_43E0_817F_90F132DAFD69__ */
