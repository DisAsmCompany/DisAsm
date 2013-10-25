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
	Reg = 0x01FF, /* operand is register (explicitly specified) */
	Imm = 0x01FE, /* operand is immediate (explicitly specified) */
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
	T##b = 0x0100 | T | b, \
	T##v = 0x0100 | T | v, \
	T##z = 0x0100 | T | z, \
	T##p = 0x0100 | T | p, \
	T##w = 0x0100 | T | w, \
	T##q = 0x0100 | T | q, \
	T##d = 0x0100 | T | d, \

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
}
OperandType;

/*
how does it work?
there are several cases :
1. no operand - just pass zero (0)
operand type will be set to zero
2. explicit immediate operand - instructions like INT 03h (OpCode CCh)
in that case operand type has value in range 01h - FFh (this range is reserved)
operand type will be set to Imm
3. explicit register operand - instructions like PUSH rAX (OpCode 50h)
registers has its values in range 0200h and upper
operand type will be set to Reg
4. operand type definition - e.g. ADD Eb, Gb (OpCode 00h)
operand type is defined in range 0100h - 01FFh

calculate operands count : how many non-zero bytes are in packed type definition
*/

/* explicit register - range 0200h and higher */
#define EXTRACT_REG(x) (((x) >= 0x0200) ? (x) : 0)
/* explicit immediate - range 00h - 0FFh */
#define EXTRACT_IMM(x) ((0 < (x) && (x) < 0x0100) ? (x) : 0)

/* other type */
#define EXTRACT_TYPE(x) (EXTRACT_REG(x) ? Reg : (EXTRACT_IMM(x) ? Imm : (x)))
#define PACK_TYPE(x) ((EXTRACT_TYPE(x) > 0x0100) ? (EXTRACT_TYPE(x) - 0x0100) : 0)

#define OP4(x, y, z, w) \
	(PACK_TYPE(x) << ShiftOperand0) | \
	(PACK_TYPE(y) << ShiftOperand1) | \
	(PACK_TYPE(z) << ShiftOperand2) | \
	(PACK_TYPE(w) << ShiftOperand3), \
	(Register)(x), (Register)(y), (Register)(z), (Register)(w)

#define OP3(x, y, z) OP4(x, y, z, 0)
#define OP2(x, y)    OP4(x, y, 0, 0)
#define OP1(x)       OP4(x, 0, 0, 0)
#define OP0          OP4(0, 0, 0, 0)

#define _OP1GET(x) (0xFF & ((x) >> ShiftOperand0))
#define _OP2GET(x) (0xFF & ((x) >> ShiftOperand1))
#define _OP3GET(x) (0xFF & ((x) >> ShiftOperand2))
#define _OP4GET(x) (0xFF & ((x) >> ShiftOperand3))

#define OP1GET(x) (0x0100 | _OP1GET(x))
#define OP2GET(x) (0x0100 | _OP2GET(x))
#define OP3GET(x) (0x0100 | _OP3GET(x))
#define OP4GET(x) (0x0100 | _OP4GET(x))

#define OPCOUNT(x) (!!_OP1GET(x) + !!_OP2GET(x) + !!_OP3GET(x) + !!_OP4GET(x))

#define LOTYPE(x) ((x - 0x0100) & 0x0F)
#define HITYPE(x) ((x - 0x0100) & 0xF0)

#define HASMODRM(x) (\
	(HITYPE(x) == E) || \
	(HITYPE(x) == G) || \
	(HITYPE(x) == M) || \
	(HITYPE(x) == C) || \
	(HITYPE(x) == D) || \
	(HITYPE(x) == R) || \
	(HITYPE(x) == S))

#endif /* __OPERANDTYPE_H__ */
