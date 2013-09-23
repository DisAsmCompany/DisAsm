/*
* Filename: StrAsm.c
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: StrAsm API implementation
*              
*              
*
*/

#include <stdio.h>
#include <stdlib.h>

#include "../DisAsm/DisAsm"
#define _STR_ENUM
#undef  __MNEMONIC_H__
#undef  __REGISTER_H__
#include "../DisAsm/DisAsm"
#include "StrAsm"

void PrintOperand(InstructionInfo * info, Operand * operand)
{
	if (operand->type == Reg)
	{
		char * reg = RegisterToString(operand->value.reg);
		printf("%s", reg);
	}
	if (HITYPE(operand->type) == I || HITYPE(operand->type) == J)
	{
		printf("%X%Xh", info->imm >> 4, info->imm & 0x0F);
	}
}

void StrAsmPrintInstruction(InstructionInfo * info)
{
	 char * mnemonic = MnemonicToString(info->mnemonic);
	 printf("%s", mnemonic);

	 if (info->nOperands > 0)
	 {
		 printf(" ");
		 PrintOperand(info, &info->operands[0]);
		 
		 if (info->nOperands > 1)
		 {
			 printf(", ");
			 PrintOperand(info, &info->operands[1]);
			 if (info->nOperands > 2)
			 {
				 printf(", ");
				 PrintOperand(info, &info->operands[2]);
			 }
		 }
	 }
	 printf("\n");
}
