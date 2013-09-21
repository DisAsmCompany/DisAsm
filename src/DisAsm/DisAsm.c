/*
* Filename: DisAsm.c
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: DisAsm API implementation
*              
*              
*
*/

#include "DisAsm"
#include "OpCodeTable.h"

int DisAsmInstructionDecode(unsigned char * buffer, InstructionInfo * info)
{
	OpCodeTableElement * element = 0;
	int length = 0;
	info->opcode = buffer[length];
	++length;

	if (0x0F == info->opcode)
	{
		/* secondary opcode table */
		info->opcode = (info->opcode << 8) | buffer[length];
		++length;
		element = &SecondaryOpcodeTable[info->opcode & 0xFF];
	}
	else
	{
		element = &PrimaryOpcodeTable[info->opcode];
	}
	
	info->hasModRM = 0;

	if (DB == element->mnemonic)
	{
		__asm int 3;
		info->length = 0;
	}

	info->hasDisp = 0;
	info->hasImm  = 0;

	if (element->operands > 0)
	{
		info->hasModRM = element->operand1type & MaskModRM;
		if (element->operand1type & (I | J))
		{
			info->hasImm = 1;
			if (element->operand1type & b)
			{
				info->sizeImm = 1;
			}
			if (element->operand1type & v)
			{
				info->sizeImm = 4;
			}
			if (element->operand1type & z)
			{
				info->sizeImm = 4;
			}
		}
		info->operand1.type = element->operand1type;
		if (element->operand1type == Reg)
		{
			info->operand1.value.reg = element->reg1;
		}

		if (element->operands > 1)
		{
			info->hasModRM = element->operand2type & MaskModRM;
			if (element->operand2type & I)
			{
				info->hasImm = 1;
				if (element->operand2type & v)
				{
					info->sizeImm = 4;
				}
			}
			info->operand2.type = element->operand2type;
			if (element->operand2type == Reg)
			{
				info->operand2.value.reg = element->reg2;
			}

			if (element->operands > 2)
			{
				info->hasModRM = element->operand3type & MaskModRM;
				if (element->operand3type & I)
				{
					info->hasImm = 1;
					if (element->operand3type & v)
					{
						info->sizeImm = 4;
					}
				}
				if (element->operand3type == Reg)
				{
					info->operand3.value.reg = element->reg3;
				}
			}
		}
	}
	if (info->hasModRM)
	{
		info->ModRM.value = buffer[length];
		++length;
		info->hasSIB = (info->ModRM.fields.Mod != 3) && (info->ModRM.fields.RM == 4);
		switch (info->ModRM.fields.Mod)
		{
		case 1:
			info->hasDisp = 1;
			info->sizeDisp = 1;
			break;
		case 2:
			info->hasDisp = 1;
			info->sizeDisp = 4;
			break;
		}

		if (info->hasSIB)
		{
			info->SIB = buffer[length];
			++length;
		}
		if (element->operands > 0)
		{
			if (element->operand1type & E)
			{
				info->operand1.type = Reg;
				info->operand1.value.reg = info->ModRM.fields.RM;
				if (element->operand1type & v)
				{
					info->operand1.value.reg |= Reg32;
				}
			}
			if (element->operand1type & G)
			{
				info->operand1.type = Reg;
				info->operand1.value.reg = info->ModRM.fields.Reg;
				if (element->operand1type & v)
				{
					info->operand1.value.reg |= Reg32;
				}
			}
			if (element->operands > 1)
			{
				if (element->operand2type & E)
				{
					info->operand2.type = Reg;
					info->operand2.value.reg = info->ModRM.fields.RM;
					if (element->operand2type & v)
					{
						info->operand2.value.reg |= Reg32;
					}
				}
				if (element->operand2type & G)
				{
					info->operand2.type = Reg;
					info->operand2.value.reg = info->ModRM.fields.Reg;
					if (element->operand2type & v)
					{
						info->operand2.value.reg |= Reg32;
					}
				}
			}
		}
	}
	if (info->hasDisp)
	{
		switch (info->sizeDisp)
		{
		case 1:
			info->disp = buffer[length];
			++length;
			break;
		case 2:
			info->disp = (buffer[length + 1] << 8) | buffer[length];
			length += 2;
			break;
		case 4:
			info->disp = (buffer[length + 3] << 24) | (buffer[length + 2] << 16) | (buffer[length + 1] << 8) | buffer[length];
			length += 4;
			break;
		default:
			break;
		}
	}
	if (info->hasImm)
	{
		switch (info->sizeImm)
		{
		case 1:
			info->imm = buffer[length];
			++length;
			break;
		case 2:
			info->imm = (buffer[length + 1] << 8) | buffer[length];
			length += 2;
			break;
		case 4:
			info->imm = (buffer[length + 3] << 24) | (buffer[length + 2] << 16) | (buffer[length + 1] << 8) | buffer[length];
			length += 4;
			break;
		default:
			break;
		}
	}
	info->length = length;
	info->mnemonic = element->mnemonic;
	info->operands = element->operands;
	return info->length;
}
