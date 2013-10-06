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
#include "OpCodeMap.h"
#include "DisAsmContext.h"
#include "GroupDecode.h"

HDISASM DisAsmCreate(uint32_t bitness)
{
	DisAsmContext * pContext = malloc(sizeof(DisAsmContext));
	if (NULL == pContext)
	{
		return NULL;
	}
	pContext->hReader = NULL;
	switch (bitness)
	{
	case 8 : pContext->size = 1; break;
	case 16: pContext->size = 2; break;
	case 32: pContext->size = 4; break;
	case 64: pContext->size = 8; break;
	default: break;
	}
	return (HDISASM) pContext;
}

void DisAsmDestroy(HDISASM hDisAsm)
{
	free(hDisAsm);
}

uint8_t Fetch1(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint8_t result = 0;
	ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 1);
	result = pInfo->bytes[pInfo->length];
	++pInfo->length;
	return result;
}

uint16_t Fetch2(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint16_t result = 0;
	ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 2);
	result = 
		(pInfo->bytes[pInfo->length + 1] << 8) | 
		(pInfo->bytes[pInfo->length]);
	pInfo->length += 2;
	return result;
}

uint32_t Fetch4(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint32_t result = 0;
	ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 4);
	result =
		(pInfo->bytes[pInfo->length + 3] << 24) | 
		(pInfo->bytes[pInfo->length + 2] << 16) | 
		(pInfo->bytes[pInfo->length + 1] << 8) | 
		(pInfo->bytes[pInfo->length]);
	pInfo->length += 4;
	return result;
}

uint32_t FetchN(DisAsmContext * pContext, InstructionInfo * pInfo, uint8_t N)
{
	uint32_t result = 0;
	switch (N)
	{
	case 1: result = Fetch1(pContext, pInfo); break;
	case 2: result = Fetch2(pContext, pInfo); break;
	case 4: result = Fetch4(pContext, pInfo); break;
	}
	return result;
}

OpCodeMapElement * ChooseOpCode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	OpCodeMapElement * element = NULL;

	OpCode opcode = Fetch1(pContext, pInfo);

	switch (opcode)
	{
	case 0x0F:
		opcode = (opcode << 8) | Fetch1(pContext, pInfo);
		switch (opcode)
		{
		case 0x0F38:
			opcode = (opcode << 8) | Fetch1(pContext, pInfo);
#if 0
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
#endif /* 0 */
			{
				/* Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh) */
				element = &OpCodeMapThreeByte0F38[opcode & 0xFF];
			}
			break;
		case 0x0F3A:
			opcode = (opcode << 8) | Fetch1(pContext, pInfo);
#if 0
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
#endif /* 0 */
			{
				/* Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh) */
				element = &OpCodeMapThreeByte0F3A[opcode & 0xFF];
			}
			break;
		default:
#if 0
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
#endif /* 0 */
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
					pContext->currentSize = 2;
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
	if (Reg == pOperand->type)
	{
		pOperand->memory = 0;
		if (rRegister <= pOperand->value.reg && pOperand->value.reg <= rRegister + 7)
		{
			pOperand->value.reg = (pOperand->value.reg - rRegister) | Reg32;
		}
		if (eRegister <= pOperand->value.reg && pOperand->value.reg <= eRegister + 7)
		{
			pOperand->value.reg = (pOperand->value.reg - eRegister) | Reg32;
		}
	}
	switch (HiType)
	{
	case S:
		pOperand->type = Reg;
		pOperand->memory = 0;
		pOperand->value.reg = pInfo->ModRM.fields.Reg | RegSeg;
		break;
	case M:
	case R:
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
		else if (LoType == q)
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
			pOperand->value.reg |= Reg32;
			pOperand->base |= Reg32;
		}
		break;
	case C:
		pOperand->memory = 0;
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.Reg;
		if (LoType == d)
		{
			pOperand->value.reg |= RegControl;
		}
		break;
	case D:
		pOperand->memory = 0;
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.Reg;
		if (LoType == d)
		{
			pOperand->value.reg |= RegDebug;
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
			pOperand->value.reg |= Reg32;
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
			pInfo->sizeImm = (4 == pContext->currentSize) ? 4 : 2;
		}
		if (LoType == v)
		{
			pInfo->sizeImm = (4 == pContext->currentSize) ? 4 : 2;
		}
		if (LoType == z)
		{
			pInfo->sizeImm = (4 == pContext->currentSize) ? 4 : 2;
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

void x87Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	OpCodeMapElement * pElement = NULL;
	uint32_t index = 0;
	if (ESCAPEX87 == pInfo->mnemonic)
	{
		if (pInfo->ModRM.fields.Mod == 3)
		{
			index = pInfo->ModRM.fields.RM + pInfo->ModRM.fields.Reg * 8 + (pInfo->opcode - 0xD7) * 64;
		}
		else
		{
			index = pInfo->ModRM.fields.Reg + (pInfo->opcode - 0xD8) * 8;
		}
		pElement = &OpCodeMapX87[index];
		pInfo->mnemonic = pElement->mnemonic;
		pInfo->nOperands = OPCOUNT(pElement->type);
		pInfo->operands[0].type = OP1GET(pElement->type);
		pInfo->operands[1].type = OP2GET(pElement->type);
		pInfo->operands[2].type = OP3GET(pElement->type);
		pInfo->operands[3].type = OP4GET(pElement->type);
		pInfo->operands[0].value.reg = pElement->reg1;
		pInfo->operands[1].value.reg = pElement->reg2;
		pInfo->operands[2].value.reg = pElement->reg3;
		pInfo->operands[3].value.reg = pElement->reg4;
	}
}

uint8_t DisAsmInstructionDecode(HDISASM hDisAsm, HREADER hReader, InstructionInfo * pInfo)
{
	DisAsmContext * pContext = (DisAsmContext*) hDisAsm;
	OpCodeMapElement * pElement = 0;
	uint8_t i = 0;

	pInfo->length = 0;
	pContext->hReader = hReader;
	pContext->currentSize = pContext->size;

	pInfo->nPrefixes = 0;

	pElement = ChooseOpCode(pContext, pInfo);
	if (NULL == pElement || DB == pElement->mnemonic)
	{
		//__asm int 3;
		return 0;
	}
	pInfo->mnemonic = pElement->mnemonic;
	pInfo->hasModRM = 0;
	pInfo->set = GP;
	if (ESCAPEX87 == pInfo->mnemonic)
	{
		pInfo->hasModRM = 1;
		pInfo->set = x87;
	}
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
		pInfo->ModRM.value = Fetch1(pContext, pInfo);
		pInfo->hasSIB = (pInfo->ModRM.fields.Mod != 3) && (pInfo->ModRM.fields.RM == 4);

		GroupDecode(pContext, pInfo);
		x87Decode(pContext, pInfo);
		if (ESCAPEX87 == pInfo->mnemonic || DB == pInfo->mnemonic || (GROUP1 <= pInfo->mnemonic && pInfo->mnemonic <= GROUPP))
		{
			pInfo->mnemonic = DB;
			return 0;
		}

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
			pInfo->SIB.value = Fetch1(pContext, pInfo);
		}
	}
	for (i = 0; i < pInfo->nOperands; ++i)
	{
		OperandDecode(pContext, pInfo, &pInfo->operands[i]);
	}
	pInfo->disp = pInfo->hasDisp ? FetchN(pContext, pInfo, pInfo->sizeDisp) : 0;
	pInfo->imm  = pInfo->hasImm  ? FetchN(pContext, pInfo, pInfo->sizeImm)  : 0;
	return pInfo->length;
}

/* for tests */

OpCode _ChooseOpCode(uint8_t * buffer)
{
	HDISASM hDisAsm = DisAsmCreate(32);
	InstructionInfo info = {0};
	DisAsmContext * pContext = (DisAsmContext*) hDisAsm;
	ChooseOpCode(pContext, &info);
	DisAsmDestroy(hDisAsm);
	return info.opcode;
}
