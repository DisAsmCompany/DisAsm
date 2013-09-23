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

typedef struct DisAsmContext_t
{
	uint8_t * buffer;
	uint8_t length;
	uint8_t size;
}
DisAsmContext;

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
				__asm int 3;
			}
			else if (1 == pInfo->nPrefixes && 0xF2 == pInfo->prefixes[0].opcode)
			{
				__asm int 3;
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
				__asm int 3;
			}
			else if (1 == pInfo->nPrefixes && 0xF2 == pInfo->prefixes[0].opcode)
			{
				__asm int 3;
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
				__asm int 3;
			}
			else if (1 == pInfo->nPrefixes && 0xF2 == pInfo->prefixes[0].opcode)
			{
				__asm int 3;
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
		case CS:
		case SS:
		case DS:
		case ES:
		case FS:
		case GS:
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

void GROUP1Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = ADD; break;
	case 1: pInfo->mnemonic = OR;  break;
	case 2: pInfo->mnemonic = ADC; break;
	case 3: pInfo->mnemonic = SBB; break;
	case 4: pInfo->mnemonic = AND; break;
	case 5: pInfo->mnemonic = SUB; break;
	case 6: pInfo->mnemonic = XOR; break;
	case 7: pInfo->mnemonic = CMP; break;
	default: break;
	}
}

void GROUP2Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = ROL; break;
	case 1: pInfo->mnemonic = ROR; break;
	case 2: pInfo->mnemonic = RCL; break;
	case 3: pInfo->mnemonic = RCR; break;
	case 4: pInfo->mnemonic = SHL; break;
	case 5: pInfo->mnemonic = SHR; break;
	case 6: pInfo->mnemonic = SAL; break;
	case 7: pInfo->mnemonic = SAR; break;
	default: break;
	}
}

void GROUP3Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0:
	case 1:
		pInfo->mnemonic = TEST;
		pInfo->nOperands = 2;
		pInfo->operands[1].type = (0xF6 == pInfo->opcode) ? Ib : Iz;
		break;
	case 2: pInfo->mnemonic = NOT;  break;
	case 3: pInfo->mnemonic = NEG;  break;
	case 4: pInfo->mnemonic = MUL;  break;
	case 5: pInfo->mnemonic = IMUL; break;
	case 6: pInfo->mnemonic = DIV;  break;
	case 7: pInfo->mnemonic = IDIV; break;
	default: break;
	}
}

void GROUP5Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	pInfo->nOperands = 1;
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = INC;  pInfo->operands[0].type = Ev; break;
	case 1: pInfo->mnemonic = DEC;  pInfo->operands[0].type = Ev; break;
	case 2: pInfo->mnemonic = CALL; pInfo->operands[0].type = Ev; break;
	case 3: pInfo->mnemonic = CALL; pInfo->operands[0].type = Mp; break;
	case 4: pInfo->mnemonic = JMP;  pInfo->operands[0].type = Ev; break;
	case 5: pInfo->mnemonic = JMP;  pInfo->operands[0].type = Mp; break;
	case 6: pInfo->mnemonic = PUSH; pInfo->operands[0].type = Ev; break;
	case 7: break;
	default: break;
	}
}

void GROUP11Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = MOV; break;
	case 1: break;
	case 2: break;
	case 3: break;
	case 4: break;
	case 5: break;
	case 6: break;
	case 7: break;
	default: break;
	}
}

void OperandDecode(DisAsmContext *pContext, InstructionInfo * pInfo, Operand * pOperand)
{
	OperandType HiType = HITYPE(pOperand->type);
	OperandType LoType = LOTYPE(pOperand->type);
	switch (HiType)
	{
	case Reg:
		if (pOperand->value.reg & rRegister)
		{
			pOperand->value.reg = (pOperand->value.reg & ~rRegister) | Reg32;
		}
		if (pOperand->value.reg & eRegister)
		{
			pOperand->value.reg = (pOperand->value.reg & ~eRegister) | Reg32;
		}
		break;
	case E:
		pOperand->type = Reg;
		pOperand->value.reg = pInfo->ModRM.fields.RM;
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
		__asm int 3;
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

		switch (pInfo->mnemonic)
		{
		case GROUP1 : GROUP1Decode (pContext, pInfo); break;
		case GROUP2 : GROUP2Decode (pContext, pInfo); break;
		case GROUP3 : GROUP3Decode (pContext, pInfo); break;
		case GROUP5 : GROUP5Decode (pContext, pInfo); break;
		case GROUP11: GROUP11Decode(pContext, pInfo); break;
		default: break;
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
			pInfo->SIB = Fetch1(pContext);
		}
	}
	for (i = 0; i < pInfo->nOperands; ++i)
	{
		OperandDecode(pContext, pInfo, &pInfo->operands[i]);
	}
	pInfo->disp = pInfo->hasDisp ? FetchN(pContext, pInfo->sizeDisp) : 0;
	pInfo->imm  = pInfo->hasImm  ? FetchN(pContext, pInfo->sizeImm)  : 0;
	pInfo->length = pContext->length;
	return pInfo->length;
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
