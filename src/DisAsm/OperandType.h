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
#ifndef __OPERANDTYPE_H__938CCA62_C5BE_43C5_8A74_6C9E8E580418__
#define __OPERANDTYPE_H__938CCA62_C5BE_43C5_8A74_6C9E8E580418__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum OperandType_t
{
	MaskModRM = 0x0800,
	Reg = 0x10FF, /* operand is register (explicitly specified) */
	Imm = 0x10FE, /* operand is immediate (explicitly specified) */
	Mem = 0x10FD, /* operand is memory */
	I = 0x0010, /* immediate data */
	J = 0x0020, /* relative offset */
	O = 0x0030, /* instruction has no ModR/M byte, offset of operand is coded as word or double-word depending on operand-size attribute */
	X = 0x0040, /* Memory addressed by the DS:rSI register pair */
	Y = 0x0050, /* Memory addressed by the ES:rDI register pair */
	F = 0x0060, /* FLAGS/EFLAGS/RFLAGS */
	A = 0x0070, /* instruction has no ModR/M byte, direct address */
	E = 0x0080 | MaskModRM, /* instruction has ModR/M byte, general-purpose register operand is defined in R/M field */
	G = 0x0090 | MaskModRM, /* instruction has ModR/M byte, general-purpose register operand is defined in Reg field */
	M = 0x00A0 | MaskModRM, /* instruction has ModR/M byte, but it may refer to memory only */
	S = 0x00B0 | MaskModRM, /* instruction has ModR/M byte, segment register operand is defined in Reg field */
	R = 0x00C0 | MaskModRM, /* instruction has ModR/M byte, R/M field may refer only to general register */
	D = 0x00D0 | MaskModRM, /* instruction has ModR/M byte, debug register operand is defined in Reg field */
	C = 0x00E0 | MaskModRM, /* instruction has ModR/M byte, control register operand is defined in Reg field */
	U = 0x00F0 | MaskModRM, /* instruction has ModR/M byte, 128-bit XMM or 256-bit YMM operand is defined in R/M field */
	V = 0x0100 | MaskModRM, /* instruction has ModR/M byte, 128-bit XMM or 256-bit YMM operand is defined in Reg field */
	W = 0x0110 | MaskModRM, /* instruction has ModR/M byte, 128-bit XMM or 256-bit YMM operand is defined in R/M field */
	P = 0x0120 | MaskModRM, /* instruction has ModR/M byte, MMX operand is defined in Reg field */
	Q = 0x0130 | MaskModRM, /* instruction has ModR/M byte, MMX operand is defined in R/M field */

	b  = 0x01, /* byte, regardless of operand size attribute*/
	v  = 0x02, /* word, double-word or quad-word, depending on operand-size attribute */
	z  = 0x03, /* word for 16-bit operand size, double-word for 32-bit or 64-bit operand-size */
	p  = 0x04, /* 32-bit, 48-bit, 80-bit pointer depending on operand-size attribute */
	w  = 0x05, /* word, regardless of operand size attribute*/ 
	q  = 0x06, /* quad-word, regardless of operand size attribute*/ 
	d  = 0x07, /* double-word, regardless of operand size attribute */
	o  = 0x08, /* oct-word, regardless of operand size attribute */
	ps = 0x09, /* 128-bit or 256-bit packed single-precision floating-point data */
	ss = 0x0A, /* 128-bit or 256-bit scalar single-precision floating-point data */
	pd = 0x0B, /* 128-bit or 256-bit packed double-precision floating-point data */
	sd = 0x0C, /* 128-bit or 256-bit scalar double-precision floating-point data */
	a  = 0x0D, /* two one-word operands in memory or two double-word operands in memory, depending on operand-size attribute (used only by the BOUND instruction) */
	_  = 0x0E, /* no type */
	y  = 0x0F, /* double-word or quad-word, depending on operand-size attribute */

#define DEFINE_TYPE(T) \
	T##b  = 0x1000 | T | b, \
	T##v  = 0x1000 | T | v, \
	T##z  = 0x1000 | T | z, \
	T##p  = 0x1000 | T | p, \
	T##w  = 0x1000 | T | w, \
	T##q  = 0x1000 | T | q, \
	T##d  = 0x1000 | T | d, \
	T##o  = 0x1000 | T | o, \
	T##ps = 0x1000 | T | ps, \
	T##ss = 0x1000 | T | ss, \
	T##pd = 0x1000 | T | pd, \
	T##sd = 0x1000 | T | sd, \
	T##a  = 0x1000 | T | a, \
	T##_  = 0x1000 | T | _, \
	T##y  = 0x1000 | T | y, \

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
	DEFINE_TYPE(U)
	DEFINE_TYPE(V)
	DEFINE_TYPE(W)
	DEFINE_TYPE(P)
	DEFINE_TYPE(Q)
	DEFINE_TYPE(A)
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

/* explicit register - range REGISTERBASE and higher */
#define EXTRACT_REG(x) (((x) >= REGISTERBASE) ? (x) : 0)
/* explicit immediate - range 00h - 0FFh */
#define EXTRACT_IMM(x) ((0 < (x) && (x) < 0x1000) ? (x) : 0)

/* other type */
#define EXTRACT_TYPE(x) (EXTRACT_REG(x) ? Reg : (EXTRACT_IMM(x) ? Imm : (x)))
#define PACK_TYPE(x) (OperandType)((EXTRACT_TYPE(x) > 0x1000) ? (EXTRACT_TYPE(x)) : 0)

#define OP4(x, y, z, w) \
	{(PACK_TYPE(x)), \
	 (PACK_TYPE(y)), \
	 (PACK_TYPE(z)), \
	 (PACK_TYPE(w))}, \
{(Register)(x), (Register)(y), (Register)(z), (Register)(w)}

#define OP3(x, y, z) OP4(x, y, z, 0)
#define OP2(x, y)    OP4(x, y, 0, 0)
#define OP1(x)       OP4(x, 0, 0, 0)
#define OP0          OP4(0, 0, 0, 0)

#define OPCOUNT(x) (!!(x)[0] + !!(x)[1] + !!(x)[2] + !!(x)[3])

#define LOTYPE(x) (OperandType)((x - 0x1000) & 0x000F)
#define HITYPE(x) (OperandType)((x - 0x1000) & 0x0FF0)

#define HASMODRM(x) (0 != (x & MaskModRM))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPERANDTYPE_H__938CCA62_C5BE_43C5_8A74_6C9E8E580418__ */
