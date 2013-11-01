/*
* Filename: OpCodeMapElement.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: element of OpCode Maps
*              
*              
*
*/

#pragma once
#ifndef __OPCODEMAPELEMENT_H__
#define __OPCODEMAPELEMENT_H__

typedef struct OpCodeMapElement_t
{
	Mnemonic mnemonic;
	OperandType type1;
	OperandType type2;
	OperandType type3;
	OperandType type4;
	Register reg1;
	Register reg2;
	Register reg3;
	Register reg4;
}
OpCodeMapElement;

#endif /* __OPCODEMAPELEMENT_H__ */
