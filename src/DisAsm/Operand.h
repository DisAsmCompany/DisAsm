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

typedef struct Operand_t
{
	OperandType type;
	Register reg;
	uint8_t scale;
	uint8_t hasBase;
	uint8_t hasIndex;
	Register index;
	uint8_t size;
}
Operand;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPERAND_H__A660D542_5B99_4A1D_8607_2D239E8B8888__ */
