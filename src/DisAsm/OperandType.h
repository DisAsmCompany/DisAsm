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
	I = 0x04,
	J = 0x08,

	b = 0x0100, /* byte, regardless of operand size attribute*/
	v = 0x0200, /* word, double-word or quad-word, depending on operand size attribute */
	z = 0x0400,

	Eb = E | b,
	Ev = E | v,

	Gb = G | b,
	Gv = G | v,
	Gz = G | z,

	Ib = I | b,
	Iv = I | v,
	Iz = I | z,

	Jb = J | b,
	Jv = J | v,
	Jz = J | z,

	MaskModRM = E | G,
}
OperandType;

#endif // __OPERANDTYPE_H__
