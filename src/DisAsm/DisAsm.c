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

#include <stdio.h>
#include <stdlib.h>

#include "DisAsm"
#include "OpCodeMap.h"
#include "DisAsmContext.h"
#include "GroupDecode.h"

HDISASM DisAsmCreate()
{
	DisAsmContext * pContext = malloc(sizeof(DisAsmContext));
	pContext->buffer = NULL;
	pContext->length = 0;
	pContext->size = 4;
	return (HDISASM) pContext;
}

void DisAsmDestroy(HDISASM hDisAsm)
{
	free(hDisAsm);
}

uint8_t Fetch1(DisAsmContext * pContext)
{
	uint8_t result = pContext->buffer[pContext->length];
	++pContext->length;
	return result;
}

uint16_t Fetch2(DisAsmContext * pContext)
{
	uint16_t result = 
		(pContext->buffer[pContext->length + 1] << 8) | 
		(pContext->buffer[pContext->length]);
	pContext->length += 2;
	return result;
}

uint32_t Fetch4(DisAsmContext * pContext)
{
	uint32_t result = 
		(pContext->buffer[pContext->length + 3] << 24) | 
		(pContext->buffer[pContext->length + 2] << 16) | 
		(pContext->buffer[pContext->length + 1] << 8) | 
		(pContext->buffer[pContext->length]);
	pContext->length += 4;
	return result;
}

uint32_t FetchN(DisAsmContext * pContext, uint8_t N)
{
	uint32_t result = 0;
	switch (N)
	{
	case 1: result = Fetch1(pContext); break;
	case 2: result = Fetch2(pContext); break;
	case 4: result = Fetch4(pContext); break;
	}
	return result;
}

OpCodeMapElement * ChooseOpCode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	OpCodeMapElement * element = NULL;

	OpCode opcode = Fetch1(pContext);

	switch (opcode)
	{
	case 0x0F:
		opcode = (opcode << 8) | Fetch1(pContext);
		switch (opcode)
		{
		case 0x0F38:
			opcode = (opcode << 8) | Fetch1(pContext);
			if (1 == pInfo->nPrefixes && 0x66 == pInfo->prefixes[0].opcode)
			{
				/* Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh), Prefix 66h */
				element = &OpCodeMapThreeByte0F38Prefix66[opcode & 0xFF];
			}
			else if (1 == pInfo->nPrefixes && 0xF2 == pInfo->prefixes[0].opcode)
			{
				/* Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh), Prefix F2h */
				element = &OpCodeMapThreeByte0F38PrefixF2[opcode & 0xFF];
			}
			else if (1 == pInfo->nPrefixes && 0xF3 == pInfo->prefixes[0].opcode)
			{
				/* Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh), Prefix F3h */
				element = &OpCodeMapThreeByte0F38PrefixF3[opcode & 0xFF];
			}
			else
			{
				/* Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh) */
				element = &OpCodeMapThreeByte0F38[opcode & 0xFF];
			}
			break;
		case 0x0F3A:
			opcode = (opcode << 8) | Fetch1(pContext);
			if (1 == pInfo->nPrefixes && 0x66 == pInfo->prefixes[0].opcode)
			{
				/* Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh), Prefix 66h */
				element = &OpCodeMapThreeByte0F3APrefix66[opcode & 0xFF];
			}
			else if (1 == pInfo->nPrefixes && 0xF2 == pInfo->prefixes[0].opcode)
			{
				/* Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh), Prefix F2h */
				element = &OpCodeMapThreeByte0F3APrefixF2[opcode & 0xFF];
			}
			else if (1 == pInfo->nPrefixes && 0xF3 == pInfo->prefixes[0].opcode)
			{
				/* Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh), Prefix F3h */
				element = &OpCodeMapThreeByte0F3APrefixF3[opcode & 0xFF];
			}
			else
			{
				/* Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh) */
				element = &OpCodeMapThreeByte0F3A[opcode & 0xFF];
			}
			break;
		default:
			if (1 == pInfo->nPrefixes && 0x66 == pInfo->prefixes[0].opcode)
			{
				/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh), Prefix 66h */
				element = &OpCodeMapTwoByte0FPrefix66[opcode & 0xFF];
			}
			else if (1 == pInfo->nPrefixes && 0xF2 == pInfo->prefixes[0].opcode)
			{
				/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh), Prefix F2h */
				element = &OpCodeMapTwoByte0FPrefixF2[opcode & 0xFF];
			}
			else if (1 == pInfo->nPrefixes && 0xF3 == pInfo->prefixes[0].opcode)
			{
				/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh), Prefix F3h */
				element = &OpCodeMapTwoByte0FPrefixF3[opcode & 0xFF];
			}
			else
			{
				/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh) */
				element = &OpCodeMapTwoByte0F[opcode & 0xFF];
			}
			break;
		}
		break;
	default:
		/* One-Byte Opcode Map (OpCodes 00h - FFh) */
		element = &OpCodeMapOneByte[opcode & 0xFF];
		/* handle prefixes */
		switch (element->mnemonic)
		{
		case LOCK:
		case REPNE:
		case REP:
		case PrefixCS:
		case PrefixSS:
		case PrefixDS:
		case PrefixES:
		case PrefixFS:
		case PrefixGS:
		case OperandSize:
		case AddressSize:
			if (pInfo->nPrefixes < MAX_PREFIXES)
			{
				if (OperandSize == element->mnemonic)
				{
					pContext->size = 2;
				}
				pInfo->prefixes[pInfo->nPrefixes].opcode = opcode;
				pInfo->prefixes[pInfo->nPrefixes].mnemonic = element->mnemonic;
				++pInfo->nPrefixes;
				return ChooseOpCode(pContext, pInfo);
			}
			else
			{
				__asm int 3;
				return NULL;
			}
		}
		break;
	}
	pInfo->opcode = opcode;
	return element;
}

void OperandDecode(DisAsmContext *pContext, InstructionInfo * pInfo, Operand * pOperand)
{
	OperandType HiType = HITYPE(pOperand->type);
	OperandType LoType = LOTYPE(pOperand->type);
	switch (HiType)
	{
	case Reg:
		pOperand->memory = 0;
		if (pOperand->value.reg & rRegister)
		{
			pOperand->value.reg = (pOperand->value.reg & ~rRegister) | Reg32;
		}
		if (pOperand->value.reg & eRegister)
		{
			pOperand->value.reg = (pOperand->value.reg & ~eRegister) | Reg32;
		}
		break;
	case S:
		pOperand->type = Reg;
		pOperand->memory = 0;
		pOperand->value.reg = pInfo->ModRM.fields.Reg | RegSeg;
		break;
	case E:
		pOperand->type = Reg;
		pOperand->memory = pInfo->ModRM.fields.Mod != 3;
		pOperand->scale = 0;
		pOperand->hasBase = 0;
		if (pInfo->hasSIB)
		{
			pOperand->hasBase = 1;
			pOperand->scale = 1 << pInfo->SIB.fields.Scale;
			pOperand->value.reg = pInfo->SIB.fields.Index;
			if (5 == (pOperand->base = pInfo->SIB.fields.Base))
			{
				switch (pInfo->ModRM.fields.Mod)
				{
				case 0: pInfo->hasDisp = 1; pInfo->sizeDisp = 4; pOperand->hasBase = 0; break;
				case 1: pInfo->hasDisp = 1; pInfo->sizeDisp = 1; break;
				case 2: pInfo->hasDisp = 1; pInfo->sizeDisp = 4; break;
				default:
					break;
				}
			}
		}
		else
		{
			pOperand->value.reg = pInfo->ModRM.fields.RM;
		}
		if (LoType == v)
		{
			pOperand->value.reg |= Reg32;
			pOperand->base |= Reg32;
		}
		else if (LoType == w)
		{
			pOperand->value.reg |= Reg16;
			pOperand->base |= Reg16;
		}
		else if (LoType == b)
		{
			pOperand->value.reg |= Reg8;
			pOperand->base |= Reg8;
		}
		else
		{
			__asm int 3;
		}
		break;
	case G:
		pOperand->memory = 0;
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.Reg;
		if (LoType == v)
		{
			pOperand->value.reg |= Reg32;
		}
		else if (LoType == w)
		{
			pOperand->value.reg |= Reg16;
		}
		else if (LoType == b)
		{
			pOperand->value.reg |= Reg8;
		}
		else
		{
			__asm int 3;
		}
		break;
	case I:
	case J:
	case O:
		pInfo->hasImm = 1;
		if (Jb == pOperand->type)
		{
			pInfo->sizeImm = 1;
		}
		if (Ib == pOperand->type)
		{
			pInfo->sizeImm = 1;
		}
		if (Ob == pOperand->type)
		{
			pInfo->sizeImm = 4;
		}
		if (LoType == v)
		{
			pInfo->sizeImm = (4 == pContext->size) ? 4 : 2;
		}
		if (LoType == z)
		{
			pInfo->sizeImm = (4 == pContext->size) ? 4 : 2;
		}
		if (LoType == w)
		{
			pInfo->sizeImm = 2;
		}
		break;
	default:
		break;
	}
}

uint8_t DisAsmInstructionDecode(HDISASM hDisAsm, uint8_t * buffer, InstructionInfo * pInfo)
{
	DisAsmContext * pContext = (DisAsmContext*) hDisAsm;
	OpCodeMapElement * pElement = 0;
	uint8_t i = 0;

	pContext->buffer = buffer;
	pContext->length = 0;
	pContext->size = 4;

	pInfo->nPrefixes = 0;

	pElement = ChooseOpCode(pContext, pInfo);
	if (NULL == pElement || DB == pElement->mnemonic)
	{
		//__asm int 3;
		return 0;
	}
	pInfo->mnemonic = pElement->mnemonic;
	pInfo->hasModRM = 0;
	if (GROUP1 <= pInfo->mnemonic && pInfo->mnemonic <= GROUPP)
	{
		pInfo->hasModRM = 1;
	}
	pInfo->hasDisp = 0;
	pInfo->hasImm  = 0;

	pInfo->nOperands = OPCOUNT(pElement->type);
	pInfo->operands[0].type = OP1GET(pElement->type);
	pInfo->operands[1].type = OP2GET(pElement->type);
	pInfo->operands[2].type = OP3GET(pElement->type);
	pInfo->operands[3].type = OP4GET(pElement->type);
	pInfo->operands[0].value.reg = pElement->reg1;
	pInfo->operands[1].value.reg = pElement->reg2;
	pInfo->operands[2].value.reg = pElement->reg3;
	pInfo->operands[3].value.reg = pElement->reg4;
	pInfo->hasModRM |= HASMODRM(pInfo->operands[0].type);
	pInfo->hasModRM |= HASMODRM(pInfo->operands[1].type);
	pInfo->hasModRM |= HASMODRM(pInfo->operands[2].type);
	pInfo->hasModRM |= HASMODRM(pInfo->operands[3].type);

	if (pInfo->hasModRM)
	{
		pInfo->ModRM.value = Fetch1(pContext);
		pInfo->hasSIB = (pInfo->ModRM.fields.Mod != 3) && (pInfo->ModRM.fields.RM == 4);

		GroupDecode(pContext, pInfo);

		switch (pInfo->ModRM.fields.Mod)
		{
		case 0:
			if (pInfo->ModRM.fields.RM == 5)
			{
				pInfo->hasDisp = 1;
				pInfo->sizeDisp = 4;
			}
			break;
		case 1:
			pInfo->hasDisp = 1;
			pInfo->sizeDisp = 1;
			break;
		case 2:
			pInfo->hasDisp = 1;
			pInfo->sizeDisp = 4;
			break;
		}

		if (pInfo->hasSIB)
		{
			pInfo->SIB.value = Fetch1(pContext);
		}
	}
	for (i = 0; i < pInfo->nOperands; ++i)
	{
		OperandDecode(pContext, pInfo, &pInfo->operands[i]);
	}
	pInfo->disp = pInfo->hasDisp ? FetchN(pContext, pInfo->sizeDisp) : 0;
	pInfo->imm  = pInfo->hasImm  ? FetchN(pContext, pInfo->sizeImm)  : 0;
	return pInfo->length = pContext->length;
}

/* for tests */

OpCode _ChooseOpCode(uint8_t * buffer)
{
	HDISASM hDisAsm = DisAsmCreate();
	InstructionInfo info = {0};
	DisAsmContext * pContext = (DisAsmContext*) hDisAsm;
	pContext->buffer = buffer;
	pContext->length = 0;
	ChooseOpCode(pContext, &info);
	DisAsmDestroy(hDisAsm);
	return info.opcode;
}
