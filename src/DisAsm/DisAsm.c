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

HDISASM DisAsmCreate(uint32_t bitness)
{
	DisAsmContext * pContext = calloc(1, sizeof(DisAsmContext));
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
	pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 1);
	result = pInfo->bytes[pInfo->length];
	++pInfo->length;
	return result;
}

uint16_t Fetch2(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint16_t result = 0;
	pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 2);
	result = 
		(pInfo->bytes[pInfo->length + 1] << 8) | 
		(pInfo->bytes[pInfo->length]);
	pInfo->length += 2;
	return result;
}

uint32_t Fetch4(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint32_t result = 0;
	pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 4);
	result =
		(pInfo->bytes[pInfo->length + 3] << 24) | 
		(pInfo->bytes[pInfo->length + 2] << 16) | 
		(pInfo->bytes[pInfo->length + 1] << 8) | 
		(pInfo->bytes[pInfo->length]);
	pInfo->length += 4;
	return result;
}

uint64_t Fetch8(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint64_t result = 0;
	pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 4);
	result =
		((uint64_t)pInfo->bytes[pInfo->length + 7] << 56) | 
		((uint64_t)pInfo->bytes[pInfo->length + 6] << 48) | 
		((uint64_t)pInfo->bytes[pInfo->length + 5] << 40) | 
		((uint64_t)pInfo->bytes[pInfo->length + 4] << 32) | 
		((uint64_t)pInfo->bytes[pInfo->length + 3] << 24) | 
		((uint64_t)pInfo->bytes[pInfo->length + 2] << 16) | 
		((uint64_t)pInfo->bytes[pInfo->length + 1] << 8) | 
		((uint64_t)pInfo->bytes[pInfo->length]);
	pInfo->length += 8;
	return result;
}

uint64_t Fetch(DisAsmContext * pContext, InstructionInfo * pInfo, uint8_t N)
{
	uint64_t result = 0;
	uint8_t i = 0;
	for (i = 0; i < N; ++i)
	{
		result = (result << 8) + Fetch1(pContext, pInfo);
	}
	pInfo->length += N;
	return result;
}

uint64_t FetchN(DisAsmContext * pContext, InstructionInfo * pInfo, uint8_t N)
{
	uint64_t result = 0;
	switch (N)
	{
	case 1: result = Fetch1(pContext, pInfo); break;
	case 2: result = Fetch2(pContext, pInfo); break;
	case 4: result = Fetch4(pContext, pInfo); break;
	case 8: result = Fetch8(pContext, pInfo); break;
	default: result = Fetch(pContext, pInfo, N); break;
	}
	return result;
}

OpCodeMapElement * ChooseOpCode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	OpCodeMapElement * element = NULL;

	uint8_t byte = Fetch1(pContext, pInfo);
	OpCode opcode = 0;

	if (8 == pContext->size)
	{
		/* REX prefix */
		switch (byte)
		{
		case 0x40: case 0x41: case 0x42: case 0x43:
		case 0x44: case 0x45: case 0x46: case 0x47:
		case 0x48: case 0x49: case 0x4A: case 0x4B:
		case 0x4C: case 0x4D: case 0x4E: case 0x4F:
			if (pInfo->hasREX)
			{
				return NULL;
			}
			pInfo->hasREX = 1;
			pInfo->REX.value = byte;
			return ChooseOpCode(pContext, pInfo);
		/* 2-byte VEX prefix */
		case 0xC5:
			if (pInfo->hasVEX2 || pInfo->hasVEX3)
			{
				return NULL;
			}
			pInfo->hasVEX2 = 1;
			pInfo->VEX2.value = Fetch1(pContext, pInfo);
			return ChooseOpCode(pContext, pInfo);
		/* 3-byte VEX prefix */
		case 0xC4:
			if (pInfo->hasVEX2 || pInfo->hasVEX3)
			{
				return NULL;
			}
			pInfo->hasVEX3 = 1;
			pInfo->VEX3.value = Fetch2(pContext, pInfo);
			return ChooseOpCode(pContext, pInfo);
		/* 3-byte XOP prefix */
		case 0x8F:
			if (pInfo->hasXOP) 
			{
				return NULL;
			}
			pInfo->hasXOP = 1;
			pInfo->XOP.value = Fetch2(pContext, pInfo);
			return ChooseOpCode(pContext, pInfo);
		default:
			break;
		}
 	}
	opcode = byte;

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
				uint32_t index = opcode & 0xFF;
				index = ((index >> 3) << 5) + (index & 0x07);
				element = &OpCodeMapTwoByte0F[index];
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
				return NULL;
			}
		default:
			break;
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
	pOperand->memory = 0;
	if (Reg == pOperand->type)
	{
		if (rRegister <= pOperand->value.reg && pOperand->value.reg <= rRegister + 7)
		{
			pOperand->value.reg = (pOperand->value.reg - rRegister);
            switch (pContext->currentSize)
            {
            case 2: pOperand->value.reg += Reg16; break;
            case 4: pOperand->value.reg += Reg32; break;
            case 8: pOperand->value.reg += Reg64; break;
            default: break;
            }
		}
		if (eRegister <= pOperand->value.reg && pOperand->value.reg <= eRegister + 7)
		{
			pOperand->value.reg = (pOperand->value.reg - eRegister);
            switch (pContext->currentSize)
            {
            case 2: pOperand->value.reg += Reg16; break;
            case 4: pOperand->value.reg += Reg32; break;
            case 8: pOperand->value.reg += Reg32; break;
            default: break;
            }
		}
	}
	if (Ap == pOperand->type)
	{
		pInfo->hasDisp = 1;
		pInfo->sizeDisp = 4;
		pInfo->hasSeg = 1;
	}
	switch (HiType)
	{
	case S:
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.Reg | RegSeg;
		break;
	case M:
	case R:
	case E:
		pOperand->type = Reg;
		pOperand->memory = pInfo->ModRM.fields.Mod != 3;
		pOperand->scale = pOperand->hasBase = pOperand->hasIndex = 0;
		if (pInfo->hasSIB)
		{
			pOperand->hasBase = 1;
			pOperand->hasIndex = 1;
			pOperand->scale = 1 << pInfo->SIB.fields.Scale;
			if (4 == (pOperand->index = pInfo->SIB.fields.Index))
			{
				pOperand->hasIndex = 0;
			}
			if (5 == (pOperand->value.reg = pInfo->SIB.fields.Base))
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
			pOperand->hasBase = 1;
			pOperand->hasIndex = 0;
			pOperand->value.reg = pInfo->ModRM.fields.RM;
			if (5 == pInfo->ModRM.fields.RM && 0 == pInfo->ModRM.fields.Mod)
			{
				pOperand->hasBase = 0;
			}
		}
		if (LoType == v)
		{
			pOperand->value.reg |= Reg32;
			pOperand->index |= Reg32;
		}
		else if (LoType == q)
		{
			pOperand->value.reg |= Reg32;
			pOperand->index |= Reg32;
		}
		else if (LoType == w)
		{
			pOperand->value.reg |= Reg16;
			pOperand->index |= Reg16;
		}
		else if (LoType == b)
		{
			pOperand->value.reg |= Reg8;
			pOperand->index |= Reg8;
		}
		else
		{
			pOperand->value.reg |= Reg32;
			pOperand->index |= Reg32;
		}
		break;
	case P:
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.Reg;
		switch (LoType)
		{
		case q:
			pOperand->value.reg |= RegMMX;
			break;
		default:
			break;
		}
		break;
	case Q:
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.RM;
		switch (LoType)
		{
		case q:
			pOperand->value.reg |= RegMMX;
			break;
		default:
			break;
		}
	case W:
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.RM;
		switch (LoType)
		{
		case ps:
		case ss:
		case pd:
		case sd:
		case o:
			pOperand->value.reg |= RegSSE;
			break;
		default:
			break;
		}
		break;
	case V:
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.Reg;
		switch (LoType)
		{
		case ps:
		case ss:
		case pd:
		case sd:
		case o:
			pOperand->value.reg |= RegSSE;
			break;
		default:
			break;
		}
		break;
	case C:
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.Reg;
		if (LoType == d)
		{
			pOperand->value.reg |= RegControl;
		}
		break;
	case D:
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.Reg;
		if (LoType == d)
		{
			pOperand->value.reg |= RegDebug;
		}
		break;
	case G:
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
            switch (pContext->currentSize)
            {
            case 2: pInfo->sizeImm = 2; break;
            case 4: pInfo->sizeImm = 4; break;
            case 8: pInfo->sizeImm = 4; break;
            default:
                break;
            }
		}
		if (LoType == v)
		{
            switch (pContext->currentSize)
            {
            case 2: pInfo->sizeImm = 2; break;
            case 4: pInfo->sizeImm = 4; break;
            case 8: 
				if (pInfo->hasREX && 1 == pInfo->REX.fields.W)
				{
					pInfo->sizeImm = 8;
				}
				else
				{
					pInfo->sizeImm = 4;
				}
				break;
            default:
                break;
            }
		}
		if (LoType == z)
		{
            switch (pContext->currentSize)
            {
            case 2: pInfo->sizeImm = 2; break;
            case 4: pInfo->sizeImm = 4; break;
            case 8: pInfo->sizeImm = 4; break;
            default:
                break;
            }
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

void CopyElementInfo(InstructionInfo * pInfo, OpCodeMapElement * pElement)
{
	pInfo->mnemonic = pElement->mnemonic;
	pInfo->nOperands = OPCOUNT(pElement->type);
	pInfo->operands[0].type = pElement->type[0];
	pInfo->operands[1].type = pElement->type[1];
	pInfo->operands[2].type = pElement->type[2];
	pInfo->operands[3].type = pElement->type[3];
	pInfo->operands[0].value.reg = pElement->reg[0];
	pInfo->operands[1].value.reg = pElement->reg[1];
	pInfo->operands[2].value.reg = pElement->reg[2];
	pInfo->operands[3].value.reg = pElement->reg[3];
}

void GroupDecode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	if (GROUP1 <= pInfo->mnemonic && pInfo->mnemonic <= GROUPP)
	{
		uint32_t index = (pInfo->mnemonic - GROUP1) * 8 + pInfo->ModRM.fields.Reg;
		OpCodeMapElement * pElement = &OpCodeMapGroup[index];
		/* GROUP3 TEST (/0 and /1) is tricky one */
		if (GROUP3 == pInfo->mnemonic && TEST == pElement->mnemonic)
		{
			pInfo->mnemonic = pElement->mnemonic;
			pInfo->mnemonic = TEST;
			pInfo->nOperands = 2;
			pInfo->operands[1].type = (0xF6 == pInfo->opcode) ? Ib : Iz;
		}
		else if (pElement->type[0])
		{
			CopyElementInfo(pInfo, pElement);
		}
		pInfo->mnemonic = pElement->mnemonic;
	}
}

void x87Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	OpCodeMapElement * pElement = NULL;
	if (ESCAPEX87 == pInfo->mnemonic)
	{
		uint32_t index = 0;
		if (pInfo->ModRM.fields.Mod == 3)
		{
			index = pInfo->ModRM.fields.RM + pInfo->ModRM.fields.Reg * 8 + (pInfo->opcode - 0xD7) * 64;
		}
		else
		{
			index = pInfo->ModRM.fields.Reg + (pInfo->opcode - 0xD8) * 8;
		}
		pElement = &OpCodeMapX87[index];
		CopyElementInfo(pInfo, pElement);
	}
}

uint32_t PrintOpCode(uint32_t OpCode)
{
	uint32_t length = 0;
	uint8_t i = 0;
	OpCodeMapElement * pElement = &OpCodeMapOneByte[OpCode];

	char * mnemonic = MnemonicToString(pElement->mnemonic);
	
	uint8_t nOperands = OPCOUNT(pElement->type);

	switch (pElement->mnemonic)
	{
	case PrefixCS: mnemonic = "CS"; break;
	case PrefixSS: mnemonic = "SS"; break;
	case PrefixDS: mnemonic = "DS"; break;
	case PrefixES: mnemonic = "ES"; break;
	case PrefixFS: mnemonic = "FS"; break;
	case PrefixGS: mnemonic = "GS"; break;
	/* FIXME */
	case _IN : mnemonic = "IN"; break;
	case _INT: mnemonic = "INT"; break;
	case _OUT: mnemonic = "OUT"; break;
	default: break;
	}
	length += strlen(mnemonic);

	printf("%s", mnemonic);

	for (i = 0; i < nOperands; ++i)
	{
		printf(i == 0 ? " " : ", ");
		length += i == 0 ? 1 : 2;
		if (Reg == pElement->type[i])
		{
			char * reg = RegisterToString(pElement->reg[i]);
			length += strlen(reg);
			printf("%s", reg);
		}
		else if (Imm == pElement->type[i])
		{
			printf("%d", pElement->reg[i]);
			++length;
		}
		else
		{
			OperandType hi = HITYPE(pElement->type[i]);
			OperandType lo = LOTYPE(pElement->type[i]);

			length += 2;

			switch (hi)
			{
			case E: printf("E"); break;
			case G: printf("G"); break;
			case I: printf("I"); break;
			case J: printf("J"); break;
			case M: printf("M"); break;
			case O: printf("O"); break;
			case X: printf("X"); break;
			case Y: printf("Y"); break;
			case F: printf("F"); break;
			case S: printf("S"); break;
			case R: printf("R"); break;
			case D: printf("D"); break;
			case C: printf("C"); break;
			case U: printf("U"); break;
			case V: printf("V"); break;
			case W: printf("W"); break;
			case P: printf("P"); break;
			case Q: printf("Q"); break;
			case A: printf("A"); break;
			default: --length; break;
			}
			switch (lo)
			{
			case b: printf("b"); break;
			case v: printf("v"); break;
			case z: printf("z"); break;
			case p: printf("p"); break;
			case w: printf("w"); break;
			case q: printf("q"); break;
			case d: printf("d"); break;
			case o: printf("o"); break;
			case ps: printf("ps"); ++length; break;
			case ss: printf("ss"); ++length; break;
			case pd: printf("pd"); ++length; break;
			case sd: printf("sd"); ++length; break;
			case a: printf("a"); break;
			default: --length; break;
			}
		}
	}
	return length;
}

void DisAsmPrintOpCodeMap(HDISASM hDisAsm)
{
	uint32_t width = 16;
	uint32_t i = 0;
	uint32_t j = 0;
	uint8_t k = 0;

	printf("  ");
	for (i = 0x00; i < 0x08; ++i)
	{
		printf("        %X       ", i);
	}
	printf("\n");
	for (i = 0x00; i < 0x10; ++i)
	{
		printf("%X ", i);
		for (j = 0x00; j < 0x08; ++j)
		{
			uint32_t padding = width - PrintOpCode((i << 4) | j);
			for (k = 0; k < padding; ++k) printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	printf("  ");
	for (i = 0x08; i < 0x10; ++i)
	{
		printf("        %X       ", i);
	}
	printf("\n");
	for (i = 0x00; i < 0x10; ++i)
	{
		printf("%X ", i);
		for (j = 0x08; j < 0x10; ++j)
		{
			uint32_t padding = width - PrintOpCode((i << 4) | j);
			for (k = 0; k < padding; ++k) printf(" ");
		}
		printf("\n");
	}
}

uint8_t DisAsmInstructionDecode(HDISASM hDisAsm, HREADER hReader, InstructionInfo * pInfo)
{
	DisAsmContext * pContext = (DisAsmContext*) hDisAsm;
	OpCodeMapElement * pElement = 0;
	uint8_t i = 0;

	pInfo->length = 0;
	pContext->error = 0;
	pContext->hReader = hReader;
	pContext->currentSize = pContext->size;

	pInfo->nPrefixes = 0;
	pInfo->hasREX = 0;

	pElement = ChooseOpCode(pContext, pInfo);
	if (NULL == pElement || DB == pElement->mnemonic || 1 == pContext->error)
	{
		return 0;
	}
	pInfo->hasModRM = 0;
	pInfo->set = GP;
	if (ESCAPEX87 == pElement->mnemonic)
	{
		pInfo->hasModRM = 1;
		pInfo->set = x87;
	}
	if (GROUP1 <= pElement->mnemonic && pElement->mnemonic <= GROUPP)
	{
		pInfo->hasModRM = 1;
	}
	pInfo->hasDisp = 0;
	pInfo->hasImm  = 0;

	CopyElementInfo(pInfo, pElement);
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
	pInfo->seg  = pInfo->hasSeg  ? Fetch2(pContext, pInfo) : 0;
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
