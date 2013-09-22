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
}
uOperand;

typedef struct Operand_t
{
	OperandType type;
	uOperand value;
}
Operand;

#endif /* __OPERAND_H__ */
