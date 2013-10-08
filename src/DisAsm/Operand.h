/*
* Filename: Operand.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: instruction operand declaration
*              
*              
*
*/

#pragma once
#ifndef __OPERAND_H__
#define __OPERAND_H__

typedef union uOperand_t
{
	Register reg;
	uint8_t imm;
}
uOperand;

typedef struct Operand_t
{
	OperandType type;
	uOperand value;
	uint8_t memory;
	uint8_t scale;
	uint8_t hasBase;
	uint8_t hasIndex;
	Register base;
	Register index;
}
Operand;

#endif /* __OPERAND_H__ */
