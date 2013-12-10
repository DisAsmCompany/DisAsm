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
#define _STR_ENUM
#undef  __MNEMONIC_H__20CAFD53_E4D1_49A5_88DC_47A54ADFD022__
#undef  __REGISTER_H__8C8FA516_AFA4_402d_B1A2_8040D9312A78__
#include "DisAsm"

typedef struct DisAsmContext_t
{
    HREADER hReader;
    uint8_t size;
    uint8_t currentSize;
    uint8_t error;
}
DisAsmContext;

char * DisAsmMnemonicToString(Mnemonic mnemonic)
{
	return MnemonicToString(mnemonic);
}

char * DisAsmRegisterToString(Register reg)
{
	return RegisterToString(reg);
}

uint8_t Fetch1(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint8_t result = 0;
	if (pInfo->length + 1 <= kMaxInstruction)
	{
		pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 1);
		result = pInfo->bytes[pInfo->length];
		++pInfo->length;
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

uint16_t Fetch2(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint16_t result = 0;
	if (pInfo->length + 2 <= kMaxInstruction)
	{
		pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 2);
		result = 
			(pInfo->bytes[pInfo->length + 1] << 8) | 
			(pInfo->bytes[pInfo->length]);
		pInfo->length += 2;
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

uint32_t Fetch4(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint32_t result = 0;
	if (pInfo->length + 4 <= kMaxInstruction)
	{
		pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 4);
		result =
			(pInfo->bytes[pInfo->length + 3] << 24) | 
			(pInfo->bytes[pInfo->length + 2] << 16) | 
			(pInfo->bytes[pInfo->length + 1] << 8) | 
			(pInfo->bytes[pInfo->length]);
		pInfo->length += 4;
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

uint64_t Fetch8(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint64_t result = 0;
	if (pInfo->length +  8 <= kMaxInstruction)
	{
		pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 8);
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
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

uint64_t Fetch(DisAsmContext * pContext, InstructionInfo * pInfo, uint8_t N)
{
	uint64_t result = 0;
	if (pInfo->length + N <= kMaxInstruction)
	{
		uint8_t i;
		for (i = 0; i < N; ++i)
		{
			result = (result << 8) + Fetch1(pContext, pInfo);
		}
		pInfo->length += N;
	}
	else
	{
		pContext->error = 1;
	}
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

OpCodeMapElement * ChooseOpCodeExt(DisAsmContext * pContext, InstructionInfo * pInfo, uint32_t * opcode, OpCodeMapElement * map, uint32_t * ext)
{
	uint32_t index = *opcode & 0xFF;
	uint32_t offset = 0;
	/* check, if opcode has extensions for prefixes 0x66, 0xF2, 0xF3 */
	if (1 == pInfo->nPrefixes)
	{
		uint32_t mask = ext[index >> 5];
		if (mask & (1 << (index & 0x1F)))
		{
			uint32_t prefix = pInfo->prefixes[0].opcode;
			switch (prefix)
			{
			case 0x66: offset =  8; break;
			case 0xF2: offset = 16; break;
			case 0xF3: offset = 24; break;
			default: break;
			}
			if (offset > 0)
			{
				/* in that case, prefix is not a prefix actually, but part of unique opcode */
				*opcode |= (*opcode & 0x00FF0000UL) ? (prefix << 24) : (prefix << 16);
				--pInfo->nPrefixes;
			}
			pContext->currentSize = pContext->size;
		}
	}
	index = offset + ((index >> 3) << 5) + (index & 0x07);
	return &map[index];
}

OpCodeMapElement * ChooseOpCode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	OpCodeMapElement * element = NULL;

	uint8_t byte = Fetch1(pContext, pInfo);
	uint32_t opcode = 0;

	if (8 == pContext->size)
	{
		/* REX prefix */
		switch (byte)
		{
		case 0x40: case 0x41: case 0x42: case 0x43:
		case 0x44: case 0x45: case 0x46: case 0x47:
		case 0x48: case 0x49: case 0x4A: case 0x4B:
		case 0x4C: case 0x4D: case 0x4E: case 0x4F:
			if (pInfo->REX.value)
			{
				return NULL;
			}
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
		/* MVEX */
		case 0x62:
			return ChooseOpCode(pContext, pInfo);
		/* L1OM */
		case 0xD6:
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
			/* Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh) */
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapThreeByte0F38, OpCodeMapThreeByte0F38Ext);
			break;
		case 0x0F3A:
			opcode = (opcode << 8) | Fetch1(pContext, pInfo);
			/* Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh) */
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapThreeByte0F3A, OpCodeMapThreeByte0F3AExt);
			break;
		default:
			/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh) */
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapTwoByte0F, OpCodeMapTwoByte0FExt);
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
			if (pInfo->nPrefixes < kMaxPrefixes)
			{
				if (OperandSize == element->mnemonic)
				{
					pContext->currentSize = pContext->size / 2;
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

uint8_t SizeForType(DisAsmContext *pContext, OperandType type)
{
	uint8_t result = 0;
	switch (LOTYPE(type))
	{
	/* byte, regardless of operand size attribute */
	case b: result = 1; break;
	/* word, regardless of operand size attribute */
	case w: result = 2; break;
	/* double-word (4 bytes), regardless of operand size attribute */
	case d: result = 4; break;
	/* quad-word, regardless of operand size attribute */
	case q:
	case oq: result = 8; break;
	/* oct-word, regardless of operand size attribute */
	case o: 
	case pb: case pk: case pi: case pj: case pq: case pw:
	case ps: case ss: case pd: case sd:
		result = 16; break;
	/* word for 16-bit operand size, or double-word for 32-bit and 64-bit operand size */
	case z:
		switch (pContext->currentSize)
		{
		case 2: result = 2; break;
		case 4:
		case 8: result = 4; break;
		default: break;
		}
		break;
	/* word, double-word or quad-word (in 64-bit mode), depending on operand size attribute */
	case v:
		switch (pContext->currentSize)
		{
		case 2: result = 2; break;
		case 4: result = 4; break;
		case 8: result = 8; break;
		default: break;
		}
		break;
    /* double-word or quad-word, depending on operand size attribute */
    case y: result = 8; break;
	default: break;
	}
	return result;
}

Register registers[][5] =
{
	/* E */ {Reg8, Reg16, Reg32, Reg64, 0},
	/* G */ {Reg8, Reg16, Reg32, Reg64, 0},
	/* M */ {Reg8, Reg16, Reg32, Reg64, 0},
	/* S */ {0, RegSeg, 0, 0, 0},
	/* R */ {Reg8, Reg16, Reg32, Reg64, 0},
	/* D */ {0, RegDebug, RegDebug, RegDebug, 0},
	/* C */ {0, RegControl, RegControl, RegControl, 0},
	/* U */ {RegSSE, RegSSE, RegSSE, RegSSE, RegSSE},
	/* V */ {RegSSE, RegSSE, RegSSE, RegSSE, RegSSE},
	/* W */ {RegSSE, RegSSE, RegSSE, RegSSE, RegSSE},
	/* P */ {RegMMX, RegMMX, RegMMX, RegMMX, RegMMX},
	/* Q */ {RegMMX, RegMMX, RegMMX, RegMMX, RegMMX},
	/* N */ {RegMMX, RegMMX, RegMMX, RegMMX, RegMMX},
};

Register RegForType(DisAsmContext * pContext, OperandType type)
{
	Register reg = 0;
	OperandType HiType = (HITYPE(type) - E) >> 8;

	switch (SizeForType(pContext, type))
	{
	case 1 : reg = registers[HiType][0]; break;
	case 2 : reg = registers[HiType][1]; break;
	case 4 : reg = registers[HiType][2]; break;
	case 8 : reg = registers[HiType][3]; break;
	case 16: reg = registers[HiType][4]; break;
	default: reg = registers[HiType][2]; break;
	}
	return reg;
}

void OperandDecode(DisAsmContext *pContext, InstructionInfo * pInfo, Operand * pOperand)
{
	OperandType type = pOperand->type;
	OperandType HiType = HITYPE(type);
	if (Imm == pOperand->type)
	{
		pInfo->imm = pOperand->reg;
		pInfo->sizeImm = 1;
		return;
	}
	else if (Reg == pOperand->type)
	{
		if (rRegister <= pOperand->reg && pOperand->reg <= rRegister + 7)
		{
			pOperand->reg = (pOperand->reg - rRegister);
            switch (pContext->currentSize)
            {
            case 2: pOperand->reg += Reg16; break;
            case 4: pOperand->reg += Reg32; break;
            case 8: pOperand->reg += Reg64; break;
            default: break;
            }
		}
		if (eRegister <= pOperand->reg && pOperand->reg <= eRegister + 7)
		{
			pOperand->reg = (pOperand->reg - eRegister);
            switch (pContext->currentSize)
            {
            case 2: pOperand->reg += Reg16; break;
            case 4: pOperand->reg += Reg32; break;
            case 8: pOperand->reg += Reg32; break;
            default: break;
            }
		}
		return;
	}
	else if (Ap == pOperand->type)
	{
		pInfo->hasDisp = 1;
		pInfo->sizeDisp = 4;
		pInfo->hasSeg = 1;
        return;
	}
	switch (HiType)
	{
	case M: case R: case E:
	case Q: case W:
		pOperand->type = (pInfo->ModRM.fields.Mod != 3) ? Mem : Reg;
		pOperand->scale = pOperand->hasBase = pOperand->hasIndex = 0;
		pOperand->size = SizeForType(pContext, type);
		if (pInfo->hasSIB)
		{
			pOperand->hasBase = 1;
			pOperand->hasIndex = 1;
			pOperand->scale = 1 << pInfo->SIB.fields.Scale;
			if (4 == (pOperand->index = pInfo->SIB.fields.Index))
			{
				pOperand->hasIndex = 0;
			}
			if (5 == (pOperand->reg = pInfo->SIB.fields.Base) && 0 == pInfo->ModRM.fields.Mod)
			{
				pOperand->hasBase = 0;
			}
		}
		else
		{
			pOperand->hasIndex = 0;
			pOperand->reg = pInfo->ModRM.fields.RM;
            pOperand->reg |= pInfo->REX.fields.B ? 8 : 0;
			pOperand->hasBase = !(5 == pInfo->ModRM.fields.RM && 0 == pInfo->ModRM.fields.Mod);
		}
		if (Mem == pOperand->type)
		{
            switch (pContext->currentSize)
            {
            case 2:
                pOperand->reg |= Reg16;
                pOperand->index |= Reg16;
                break;
            case 4:
                pOperand->reg |= Reg32;
			    pOperand->index |= Reg32;
                break;
            case 8:
                pOperand->reg |= Reg64;
                pOperand->index |= Reg64;
                break;
            default:
                pOperand->reg |= Reg32;
                pOperand->index |= Reg32;
                break;
            }
		}
		else
		{
			pOperand->reg |= RegForType(pContext, type);
		}
		break;
	case P: case S: case V:
	case C: case D: case G:
	case N:
		pOperand->type = Reg;
		pOperand->reg = pInfo->ModRM.fields.Reg;
        pOperand->reg |= pInfo->REX.fields.R ? 8 : 0;
		pOperand->reg |= RegForType(pContext, type);
		break;
	case I: case J:
		pOperand->type = Imm;
		pInfo->hasImm = 1;
		pInfo->sizeImm = SizeForType(pContext, type);
		break;
	case O:
		pInfo->hasDisp = 1;
		pOperand->type = Mem;
		pOperand->hasBase = pOperand->hasIndex = 0;
		pOperand->size = SizeForType(pContext, type);
		switch (pContext->currentSize)
        {
		case 1: pInfo->sizeDisp = 1; break;
        case 2: pInfo->sizeDisp = 2; break;
        case 4: pInfo->sizeDisp = 4; break;
        case 8: pInfo->sizeDisp = 4; break;
        default:
            break;
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
	pInfo->operands[0].reg = pElement->reg[0];
	pInfo->operands[1].reg = pElement->reg[1];
	pInfo->operands[2].reg = pElement->reg[2];
	pInfo->operands[3].reg = pElement->reg[3];
}

void GroupDecode(InstructionInfo * pInfo)
{
	if (GROUP1 <= pInfo->mnemonic && pInfo->mnemonic <= GROUPP)
	{
		uint32_t index = (pInfo->mnemonic - GROUP1) * 8 + pInfo->ModRM.fields.Reg;
		OpCodeMapElement * pElement = &OpCodeMapGroup[index];
		if (pElement->type[0])
		{
			CopyElementInfo(pInfo, pElement);
		}
		pInfo->mnemonic = pElement->mnemonic;
		if (pElement->mnemonic == GROUP7_EXT2)
		{
			index = (pInfo->mnemonic - GROUP1) * 8 + pInfo->ModRM.fields.RM;
			pElement = &OpCodeMapGroup[index];
			pInfo->mnemonic = pElement->mnemonic;
		}
	}
}

void x87Decode(InstructionInfo * pInfo)
{
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
		CopyElementInfo(pInfo, &OpCodeMapX87[index]);
	}
}

uint32_t PrintOpCode(uint32_t OpCode)
{
	uint32_t length = 0;
	uint8_t i = 0;
	OpCodeMapElement * pElement = &OpCodeMapOneByte[OpCode];

	char * mnemonic = (char*)MnemonicToString(pElement->mnemonic);
	
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
	length += xstrlen(mnemonic);

	ConsoleIOPrint(mnemonic);

	for (i = 0; i < nOperands; ++i)
	{
		ConsoleIOPrint(i == 0 ? " " : ", ");
		length += i == 0 ? 1 : 2;
		if (Reg == pElement->type[i])
		{
			char * reg = (char*)RegisterToString(pElement->reg[i]);
			length += xstrlen(reg);
			ConsoleIOPrint(reg);
		}
		else if (Imm == pElement->type[i])
		{
			ConsoleIOPrintFormatted("%d", pElement->reg[i]);
			++length;
		}
		else
		{
			OperandType hi = HITYPE(pElement->type[i]);
			OperandType lo = LOTYPE(pElement->type[i]);

			length += 2;

			switch (hi)
			{
			case E: ConsoleIOPrint("E"); break;
			case G: ConsoleIOPrint("G"); break;
			case I: ConsoleIOPrint("I"); break;
			case J: ConsoleIOPrint("J"); break;
			case M: ConsoleIOPrint("M"); break;
			case O: ConsoleIOPrint("O"); break;
			case X: ConsoleIOPrint("X"); break;
			case Y: ConsoleIOPrint("Y"); break;
			case F: ConsoleIOPrint("F"); break;
			case S: ConsoleIOPrint("S"); break;
			case R: ConsoleIOPrint("R"); break;
			case D: ConsoleIOPrint("D"); break;
			case C: ConsoleIOPrint("C"); break;
			case U: ConsoleIOPrint("U"); break;
			case V: ConsoleIOPrint("V"); break;
			case W: ConsoleIOPrint("W"); break;
			case P: ConsoleIOPrint("P"); break;
			case Q: ConsoleIOPrint("Q"); break;
			case A: ConsoleIOPrint("A"); break;
			default: --length; break;
			}
			switch (lo)
			{
			case b:  ConsoleIOPrint("b"); break;
			case v:  ConsoleIOPrint("v"); break;
			case z:  ConsoleIOPrint("z"); break;
			case p:  ConsoleIOPrint("p"); break;
			case w:  ConsoleIOPrint("w"); break;
			case q:  ConsoleIOPrint("q"); break;
			case d:  ConsoleIOPrint("d"); break;
			case o:  ConsoleIOPrint("o"); break;
			case ps: ConsoleIOPrint("ps"); ++length; break;
			case ss: ConsoleIOPrint("ss"); ++length; break;
			case pd: ConsoleIOPrint("pd"); ++length; break;
			case sd: ConsoleIOPrint("sd"); ++length; break;
			case a:  ConsoleIOPrint("a"); break;
			default: --length; break;
			}
		}
	}
	return length;
}

void DisAsmPrintOpCodeMap()
{
	uint32_t width = 16;
	uint32_t i = 0;
	uint32_t j = 0;
	uint8_t k = 0;

	ConsoleIOPrint("  ");
	for (i = 0x00; i < 0x08; ++i)
	{
		ConsoleIOPrintFormatted("        %X       ", i);
	}
	ConsoleIOPrint("\n");
	for (i = 0x00; i < 0x10; ++i)
	{
		ConsoleIOPrintFormatted("%X ", i);
		for (j = 0x00; j < 0x08; ++j)
		{
			uint32_t padding = width - PrintOpCode((i << 4) | j);
			for (k = 0; k < padding; ++k) ConsoleIOPrint(" ");
		}
		ConsoleIOPrint("\n");
	}
	ConsoleIOPrint("\n");
	ConsoleIOPrint("  ");
	for (i = 0x08; i < 0x10; ++i)
	{
		ConsoleIOPrintFormatted("        %X       ", i);
	}
	ConsoleIOPrint("\n");
	for (i = 0x00; i < 0x10; ++i)
	{
		ConsoleIOPrintFormatted("%X ", i);
		for (j = 0x08; j < 0x10; ++j)
		{
			uint32_t padding = width - PrintOpCode((i << 4) | j);
			for (k = 0; k < padding; ++k) ConsoleIOPrint(" ");
		}
		ConsoleIOPrint("\n");
	}
}

uint8_t DisAsmInstructionDecode(uint8_t bitness, HREADER hReader, InstructionInfo * pInfo)
{
	InstructionInfo info;
	DisAsmContext context;
	OpCodeMapElement * pElement = 0;
	uint8_t i = 0;

	pInfo = pInfo ? pInfo : &info;
	pInfo->length = 0;
	pInfo->nPrefixes = 0;
	pInfo->REX.value = 0;
	pInfo->mnemonic = DB;

	context.error = 0;
	context.hReader = hReader;
	context.currentSize = context.size = bitness >> 3;

	pElement = ChooseOpCode(&context, pInfo);
	if (NULL == pElement || DB == pElement->mnemonic || 1 == context.error)
	{
		return 0;
	}
    if (8 == context.currentSize)
    {
        context.currentSize = pInfo->REX.fields.W ? 8 : 4;
    }
	pInfo->hasSeg = 0;
	pInfo->hasModRM = 0;
	pInfo->set = GP;
	if (ESCAPEX87 == pElement->mnemonic || (GROUP1 <= pElement->mnemonic && pElement->mnemonic <= GROUPP))
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
		pInfo->ModRM.value = Fetch1(&context, pInfo);
		pInfo->hasSIB = (pInfo->ModRM.fields.Mod != 3) && (pInfo->ModRM.fields.RM == 4);

		GroupDecode(pInfo);
		x87Decode(pInfo);
		if (ESCAPEX87 == pInfo->mnemonic || DB == pInfo->mnemonic || (GROUP1 <= pInfo->mnemonic && pInfo->mnemonic <= GROUPP))
		{
			return 0;
		}
		pInfo->SIB.value = pInfo->hasSIB ? Fetch1(&context, pInfo) : 0;
		switch (pInfo->ModRM.fields.Mod)
		{
		case 0:
			if (5 == pInfo->ModRM.fields.RM || (pInfo->hasSIB && 5 == pInfo->SIB.fields.Base))
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
	}
	for (i = 0; i < pInfo->nOperands; ++i) OperandDecode(&context, pInfo, &pInfo->operands[i]);
	pInfo->disp = pInfo->hasDisp ? FetchN(&context, pInfo, pInfo->sizeDisp) : 0;
	pInfo->seg  = pInfo->hasSeg  ? Fetch2(&context, pInfo) : 0;
	pInfo->imm  = pInfo->hasImm  ? FetchN(&context, pInfo, pInfo->sizeImm)  : 0;
	return pInfo->length;
}
