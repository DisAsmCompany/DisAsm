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
}
DisAsmContext;

HDISASM DisAsmCreate()
{
	DisAsmContext * pContext = malloc(sizeof(DisAsmContext));
	pContext->buffer = NULL;
	pContext->length = 0;
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

void GROUP5Decode(DisAsmContext * pContext, InstructionInfo * pInfo, OpCodeMapElement * pElement)
{
	pElement->operands = 1;
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pElement->mnemonic = INC;  pElement->operand1type = Ev; break;
	case 1: pElement->mnemonic = DEC;  pElement->operand1type = Ev; break;
	case 2: pElement->mnemonic = CALL; pElement->operand1type = Ev; break;
	case 3: pElement->mnemonic = CALL; pElement->operand1type = Mp; break;
	case 4: pElement->mnemonic = JMP;  pElement->operand1type = Ev; break;
	case 5: pElement->mnemonic = JMP;  pElement->operand1type = Mp; break;
	case 6: pElement->mnemonic = PUSH; pElement->operand1type = Ev; break;
	case 7: break;
	default: break;
	}
}

uint8_t DisAsmInstructionDecode(HDISASM hDisAsm, uint8_t * buffer, InstructionInfo * pInfo)
{
	DisAsmContext * pContext = (DisAsmContext*) hDisAsm;
	OpCodeMapElement * element = 0;

	pContext->buffer = buffer;
	pContext->length = 0;

	pInfo->nPrefixes = 0;

	element = ChooseOpCode(pContext, pInfo);
	if (NULL == element || DB == element->mnemonic)
	{
		__asm int 3;
		return 0;
	}

	pInfo->hasModRM = 0;
	if (GROUP1 <= element->mnemonic && element->mnemonic <= GROUPP)
	{
		pInfo->hasModRM = 1;
	}
	pInfo->hasDisp = 0;
	pInfo->hasImm  = 0;

	if (element->operands > 0)
	{
		pInfo->hasModRM = 0 != (element->operand1type & MaskModRM);
		if (element->operand1type & MaskImmediate)
		{
			pInfo->hasImm = 1;
			if (Jb == (element->operand1type & Jb))
			{
				pInfo->sizeImm = 1;
			}
			if (Ob == (element->operand1type & Ob))
			{
				pInfo->sizeImm = 4;
			}
			if (element->operand1type & v)
			{
				pInfo->sizeImm = 4;
			}
			if (element->operand1type & z)
			{
				pInfo->sizeImm = 4;
			}
			if (element->operand1type & w)
			{
				pInfo->sizeImm = 2;
			}
		}
		pInfo->operand1.type = element->operand1type;
		if (element->operand1type == Reg)
		{
			pInfo->operand1.value.reg = element->reg1;
		}

		if (element->operands > 1)
		{
			pInfo->hasModRM = 0 != (element->operand2type & MaskModRM);
			if (element->operand2type & MaskImmediate)
			{
				pInfo->hasImm = 1;
				if (Jb == (element->operand2type & Jb))
				{
					pInfo->sizeImm = 1;
				}
				if (Ob == (element->operand2type & Ob))
				{
					pInfo->sizeImm = 4;
				}
				if (element->operand2type & v)
				{
					pInfo->sizeImm = 4;
				}
				if (element->operand2type & z)
				{
					pInfo->sizeImm = 4;
				}
			}
			pInfo->operand2.type = element->operand2type;
			if (element->operand2type == Reg)
			{
				pInfo->operand2.value.reg = element->reg2;
			}

			if (element->operands > 2)
			{
				pInfo->hasModRM = 0 != (element->operand3type & MaskModRM);
				if (element->operand3type & I)
				{
					pInfo->hasImm = 1;
					if (element->operand3type & v)
					{
						pInfo->sizeImm = 4;
					}
				}
				if (element->operand3type == Reg)
				{
					pInfo->operand3.value.reg = element->reg3;
				}
			}
		}
	}
	if (pInfo->hasModRM)
	{
		pInfo->ModRM.value = Fetch1(pContext);
		pInfo->hasSIB = (pInfo->ModRM.fields.Mod != 3) && (pInfo->ModRM.fields.RM == 4);

		switch (element->mnemonic)
		{
		case GROUP5: GROUP5Decode(pContext, pInfo, element); break;
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
		if (element->operands > 0)
		{
			if (element->operand1type & E)
			{
				pInfo->operand1.type = Reg;
				pInfo->operand1.value.reg = pInfo->ModRM.fields.RM;
				if (element->operand1type & v)
				{
					pInfo->operand1.value.reg |= Reg32;
				}
			}
			if (element->operand1type & G)
			{
				pInfo->operand1.type = Reg;
				pInfo->operand1.value.reg = pInfo->ModRM.fields.Reg;
				if (element->operand1type & v)
				{
					pInfo->operand1.value.reg |= Reg32;
				}
			}
			if (element->operands > 1)
			{
				if (element->operand2type & E)
				{
					pInfo->operand2.type = Reg;
					pInfo->operand2.value.reg = pInfo->ModRM.fields.RM;
					if (element->operand2type & v)
					{
						pInfo->operand2.value.reg |= Reg32;
					}
				}
				if (element->operand2type & G)
				{
					pInfo->operand2.type = Reg;
					pInfo->operand2.value.reg = pInfo->ModRM.fields.Reg;
					if (element->operand2type & v)
					{
						pInfo->operand2.value.reg |= Reg32;
					}
				}
			}
		}
	}
	pInfo->operands = element->operands;
	pInfo->disp = pInfo->hasDisp ? FetchN(pContext, pInfo->sizeDisp) : 0;
	pInfo->imm  = pInfo->hasImm  ? FetchN(pContext, pInfo->sizeImm)  : 0;
	pInfo->length = pContext->length;
	pInfo->mnemonic = element->mnemonic;
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
