/*
* Filename: OperandType.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: possible argument types for 
*              x86/x64 instructions
*              
*
*/

#pragma once
#ifndef __OPERANDTYPE_H__
#define __OPERANDTYPE_H__

/*

operand type for single operand is coded in one byte (uint8_t)
lowest 4 bits describe operand size, and highest 4 bits describe operand nature
in instruction table, operand types are really coded in double word (uint32_t)
that means single value describes operand types for all operands (up to 4 operands)
each byte describes single operand, if some operand is not present, its type set to zero (0)
[op4][op3][op2][op1]

*/

typedef enum OperandType_t
{
	Reg = 0xFF, /* operand is register (explicitly specified) */
	Imm = 0xFE, /* operand is immediate (explicitly specified) */
	E = 0x10, /* instruction has ModR/M byte, general-purpose register operand is defined in R/M field */
	G = 0x20, /* instruction has ModR/M byte, general-purpose register operand is defined in Reg field */
	I = 0x30, /* immediate data */
	J = 0x40, /* relative offset */
	M = 0x50, /* instruction has ModR/M byte, but it may refer to memory only */
	O = 0x60, /* instruction has no ModR/M byte, offset of operand is coded as word or double-word depending on operand-size attribute */
	X = 0x70, /* Memory addressed by the DS:rSI register pair */
	Y = 0x90, /* Memory addressed by the ES:rDI register pair */
	S = 0xA0, /* instruction has ModR/M byte, segment register operand is defined in Reg field */
	F = 0xB0, /* FLAGS/EFLAGS/RFLAGS */
	R = 0xC0, /* instruction has ModR/M byte, R/M field may refer only to general register */
	D = 0xD0, /* instruction has ModR/M byte, debug register operand is defined in Reg field */
	C = 0xE0, /* instruction has ModR/M byte, control register operand is defined in Reg field */

	b = 0x01, /* byte, regardless of operand size attribute*/
	v = 0x02, /* word, double-word or quad-word, depending on operand-size attribute */
	z = 0x03, /* word for 16-bit operand size, double-word for 32-bit or 64-bit operand-size */
	p = 0x04, /* 32-bit, 48-bit, 80-bit pointer depending on operand-size attribute */
	w = 0x05, /* word, regardless of operand size attribute*/ 
	q = 0x06, /* quad-word, regardless of operand size attribute*/ 
	d = 0x07, /* double-word, regardless of operand size attribute */

#define DEFINE_TYPE(T) \
	T##b = T | b, \
	T##v = T | v, \
	T##z = T | z, \
	T##p = T | p, \
	T##w = T | w, \
	T##q = T | q, \
	T##d = T | d, \

	DEFINE_TYPE(E)
	DEFINE_TYPE(G)
	DEFINE_TYPE(I)
	DEFINE_TYPE(J)
	DEFINE_TYPE(M)
	DEFINE_TYPE(O)
	DEFINE_TYPE(X)
	DEFINE_TYPE(Y)
	DEFINE_TYPE(S)
	DEFINE_TYPE(F)
	DEFINE_TYPE(R)
	DEFINE_TYPE(C)
	DEFINE_TYPE(D)

	ShiftOperand0 = 0,
	ShiftOperand1 = 8,
	ShiftOperand2 = 16,
	ShiftOperand3 = 24,

	MaskOperand1 = 0x000000FFUL,
	MaskOperand2 = 0x0000FF00UL,
	MaskOperand3 = 0x00FF0000UL,
	MaskOperand4 = 0xFF000000UL,
}
OperandType;

#define OP0             (0)
#define OP1(x)          (((x) << ShiftOperand0) | OP0)
#define OP2(x, y)       (((y) << ShiftOperand1) | OP1(x))
#define OP3(x, y, z)    (((z) << ShiftOperand2) | OP2(x, y))
#define OP4(x, y, z, w) (((w) << ShiftOperand3) | OP3(x, y, z))

#define OP1GET(x) (((x) & MaskOperand1) >> ShiftOperand0)
#define OP2GET(x) (((x) & MaskOperand2) >> ShiftOperand1)
#define OP3GET(x) (((x) & MaskOperand3) >> ShiftOperand2)
#define OP4GET(x) (((x) & MaskOperand4) >> ShiftOperand3)

#define OPCOUNT(x) (!!OP1GET(x) + !!OP2GET(x) + !!OP3GET(x) + !!OP4GET(x))

#define LOTYPE(x) ((x) & 0x0F)
#define HITYPE(x) ((x) & 0xF0)

#define HASMODRM(x) (\
	(HITYPE(x) == E) || \
	(HITYPE(x) == G) || \
	(HITYPE(x) == M) || \
	(HITYPE(x) == C) || \
	(HITYPE(x) == D) || \
	(HITYPE(x) == R) || \
	(HITYPE(x) == S))

#endif /* __OPERANDTYPE_H__ */
