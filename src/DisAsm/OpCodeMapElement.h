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
	uint8_t operands;
	OperandType operand1type;
	Register reg1;
	OperandType operand2type;
	Register reg2;
	OperandType operand3type;
	Register reg3;
}
OpCodeMapElement;

#endif /* __OPCODEMAPELEMENT_H__ */
