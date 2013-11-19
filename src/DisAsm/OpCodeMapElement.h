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
#ifndef __OPCODEMAPELEMENT_H__21A1E58B_A822_4325_B021_06D4E111347B__
#define __OPCODEMAPELEMENT_H__21A1E58B_A822_4325_B021_06D4E111347B__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct OpCodeMapElement_t
{
	Mnemonic mnemonic;
	OperandType type[4];
	Register reg[4];
}
OpCodeMapElement;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPCODEMAPELEMENT_H__21A1E58B_A822_4325_B021_06D4E111347B__ */
