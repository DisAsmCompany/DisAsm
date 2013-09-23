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

typedef enum OperandType_t
{
	Reg = 0x00, /* operand is register */
	E = 0x01, /* instruction has ModR/M byte, general-purpose register operand is defined in R/M field */
	G = 0x02, /* instruction has ModR/M byte, general-purpose register operand is defined in Reg field */
	I = 0x04, /* immediate data */
	J = 0x08, /* relative offset */
	M = 0x10, /* instruction has ModR/M byte, but it may refer to memory only */
	O = 0x20, /* instruction has no ModR/M byte, offset of operand is coded as word or double-word depending on operand-size attribute */
	X = 0x40, /* Memory addressed by the DS:rSI register pair */
	Y = 0x80, /* Memory addressed by the ES:rDI register pair */

	b = 0x0100, /* byte, regardless of operand size attribute*/
	v = 0x0200, /* word, double-word or quad-word, depending on operand-size attribute */
	z = 0x0400, /* word for 16-bit operand size, double-word for 32-bit or 64-bit operand-size */
	p = 0x0800, /* 32-bit, 48-bit, 80-bit pointer depending on operand-size attribute */
	w = 0x1000, /* word, regardless of operand size attribute*/ 

	Eb = E | b,
	Ev = E | v,
	Ez = E | z,
	Ep = E | p,
	Ew = E | w,

	Gb = G | b,
	Gv = G | v,
	Gz = G | z,
	Gp = G | p,
	Gw = G | w,

	Ib = I | b,
	Iv = I | v,
	Iz = I | z,
	Ip = I | p,
	Iw = I | w,

	Jb = J | b,
	Jv = J | v,
	Jz = J | z,
	Jp = J | p,
	Jw = J | w,

	Mb = M | b,
	Mv = M | v,
	Mz = M | z,
	Mp = M | p,
	Mw = M | w,

	Ob = O | b,
	Ov = O | v,
	Oz = O | z,
	Op = O | p,
	Ow = O | w,

	Xb = X | b,
	Xv = X | v,
	Xz = X | z,
	Xp = X | p,
	Xw = X | w,

	Yb = Y | b,
	Yv = Y | v,
	Yz = Y | z,
	Yp = Y | p,
	Yw = Y | w,

	MaskModRM = E | G,
	MaskImmediate = I | J | O,
}
OperandType;

#endif /* __OPERANDTYPE_H__ */
