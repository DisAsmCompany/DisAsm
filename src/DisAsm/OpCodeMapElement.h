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
	OperandType type[4];
	Register reg[4];
}
OpCodeMapElement;

#endif /* __OPCODEMAPELEMENT_H__ */
