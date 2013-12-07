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

enum { OperandBase  = 0x00004000UL };
enum { RegisterBase = 0x00010000UL };

typedef enum OperandType_t
{
	MaskModRM = 0x2000,
	Reg = OperandBase | 0xFF, /* operand is register (explicitly specified) */
	Imm = OperandBase | 0xFE, /* operand is immediate (explicitly specified) */
	Mem = OperandBase | 0xFD, /* operand is memory */
	I = 0x0100, /* immediate data */
	J = 0x0200, /* relative offset */
	O = 0x0300, /* instruction has no ModR/M byte, offset of operand is coded as word or double-word depending on operand-size attribute */
	X = 0x0400, /* Memory addressed by the DS:rSI register pair */
	Y = 0x0500, /* Memory addressed by the ES:rDI register pair */
	F = 0x0600, /* FLAGS/EFLAGS/RFLAGS */
	A = 0x0700, /* instruction has no ModR/M byte, direct address */
	E = 0x0800 | MaskModRM, /* instruction has ModR/M byte, general-purpose register operand is defined in R/M field */
	G = 0x0900 | MaskModRM, /* instruction has ModR/M byte, general-purpose register operand is defined in Reg field */
	M = 0x0A00 | MaskModRM, /* instruction has ModR/M byte, but it may refer to memory only */
	S = 0x0B00 | MaskModRM, /* instruction has ModR/M byte, segment register operand is defined in Reg field */
	R = 0x0C00 | MaskModRM, /* instruction has ModR/M byte, R/M field may refer only to general register */
	D = 0x0D00 | MaskModRM, /* instruction has ModR/M byte, debug register operand is defined in Reg field */
	C = 0x0E00 | MaskModRM, /* instruction has ModR/M byte, control register operand is defined in Reg field */
	U = 0x0F00 | MaskModRM, /* instruction has ModR/M byte, 128-bit XMM or 256-bit YMM operand is defined in R/M field */
	V = 0x1000 | MaskModRM, /* instruction has ModR/M byte, 128-bit XMM or 256-bit YMM operand is defined in Reg field */
	W = 0x1100 | MaskModRM, /* instruction has ModR/M byte, 128-bit XMM or 256-bit YMM operand is defined in R/M field */
	P = 0x1200 | MaskModRM, /* instruction has ModR/M byte, MMX operand is defined in Reg field */
	Q = 0x1300 | MaskModRM, /* instruction has ModR/M byte, MMX operand is defined in R/M field */
	N = 0x1400 | MaskModRM, /* instruction has ModR/M byte, MMX operand is defined in R/M field (packed quadword) */

    _  = 0x00, /* no type */
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
	pb = 0x0D, /* quadword MMX register (vector composed of 8-bit integers) */
    pk = 0x0E, /* quadword MMX register (vector composed of 8-bit integers) */
	pi = 0x0F, /* quadword MMX register (vector composed of 16-bit integers) */
	pw = 0x10, /* quadword MMX register (vector composed of 16-bit integers) */
	pj = 0x11, /* quadword MMX register (vector composed of 32-bit integers) */
	pq = 0x12, /* quadword MMX register (vector composed of 64-bit integers) */
	a  = 0x13, /* two one-word operands in memory or two double-word operands in memory, depending on operand-size attribute (used only by the BOUND instruction) */
	y  = 0x14, /* double-word or quad-word, depending on operand-size attribute */
	oq = 0x15, /* operand is either the upper or lower half of 128-bit value */

#define DEFINE_TYPE(T) \
	T##b  = OperandBase | T | b, \
	T##v  = OperandBase | T | v, \
	T##z  = OperandBase | T | z, \
	T##p  = OperandBase | T | p, \
	T##w  = OperandBase | T | w, \
	T##q  = OperandBase | T | q, \
	T##d  = OperandBase | T | d, \
	T##o  = OperandBase | T | o, \
	T##ps = OperandBase | T | ps, \
	T##ss = OperandBase | T | ss, \
	T##pd = OperandBase | T | pd, \
	T##sd = OperandBase | T | sd, \
	T##pb = OperandBase | T | pb, \
	T##pk = OperandBase | T | pk, \
	T##pi = OperandBase | T | pi, \
	T##pw = OperandBase | T | pw, \
	T##pj = OperandBase | T | pj, \
	T##pq = OperandBase | T | pq, \
	T##a  = OperandBase | T | a, \
	T##_  = OperandBase | T | _, \
	T##y  = OperandBase | T | y, \
	T##oq = OperandBase | T | oq, \

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
	DEFINE_TYPE(N)
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

/* explicit register - range RegisterBase and higher */
#define EXTRACT_REG(x) (((x) >= RegisterBase) ? (x) : 0)
/* explicit immediate - range 00h - OperandBase */
#define EXTRACT_IMM(x) ((0 < (x) && (x) < OperandBase) ? (x) : 0)

/* other type */
#define EXTRACT_TYPE(x) (EXTRACT_REG(x) ? Reg : (EXTRACT_IMM(x) ? Imm : (x)))
#define PACK_TYPE(x) (OperandType)((EXTRACT_TYPE(x) > OperandBase) ? (EXTRACT_TYPE(x)) : 0)

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

#define LOTYPE(x) (OperandType)((x - OperandBase) & 0x00FF)
#define HITYPE(x) (OperandType)((x - OperandBase) & 0xFF00)

#define HASMODRM(x) (0 != (x & MaskModRM))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPERANDTYPE_H__938CCA62_C5BE_43C5_8A74_6C9E8E580418__ */
