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
#ifndef __OPERAND_H__A660D542_5B99_4A1D_8607_2D239E8B8888__
#define __OPERAND_H__A660D542_5B99_4A1D_8607_2D239E8B8888__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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
	Register index;
}
Operand;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPERAND_H__A660D542_5B99_4A1D_8607_2D239E8B8888__ */
