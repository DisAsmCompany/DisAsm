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

#include "../DisAsm/DisAsm"
#include "StrAsm"

uint8_t IsNegative(uint64_t value, uint8_t size)
{
	return !!(value & (0x80 << 8 * (size - 1)));
}

uint64_t Inverse(uint64_t value, uint8_t size)
{
	if (size == 8)
	{
		value = U64(0xFFFFFFFFFFFFFFFF) - value;
	}
	if (size == 4)
	{
		value = 0xFFFFFFFFUL - value;
	}
	if (size == 2)
	{
		value = 0xFFFFUL - value;
	}
	if (size == 1)
	{
		value = 0xFFUL - value;
	}
	return value + 1;
}

void PrintValue(uint64_t value)
{
	if (value > 0xFFFFUL)
	{
		PrintByte((value >> 24) & 0xFF);
		PrintByte((value >> 16) & 0xFF);
	}
	if (value > 0xFF)
	{
		PrintByte((value >> 8) & 0xFF);
	}
	PrintByte(value & 0xFF);
	ConsoleIOPrint("h");
}

void PrintSegment(InstructionInfo * pInfo)
{
	uint8_t i;
	for (i = 0; i < pInfo->nPrefixes; ++i)
	{
		switch (pInfo->prefixes[i].mnemonic)
		{
		case PrefixCS: ConsoleIOPrint("CS:"); break;
		case PrefixSS: ConsoleIOPrint("SS:"); break;
		case PrefixDS: ConsoleIOPrint("DS:"); break;
		case PrefixES: ConsoleIOPrint("ES:"); break;
		case PrefixFS: ConsoleIOPrint("FS:"); break;
		case PrefixGS: ConsoleIOPrint("GS:"); break;
		default:break;
		}
	}
}

void PrintOperand(InstructionInfo * pInfo, Operand * pOperand)
{
	if (pOperand->type == Reg)
	{
		if (pOperand->memory)
		{
			switch (pOperand->size)
			{
			case 1: ConsoleIOPrint("BYTE PTR "); break;
			case 2: ConsoleIOPrint("WORD PTR "); break;
			case 4: ConsoleIOPrint("DWORD PTR "); break;
			case 8: ConsoleIOPrint("QWORD PTR "); break;
			}
			PrintSegment(pInfo);
			ConsoleIOPrint("[");

			if (pOperand->hasBase)
			{
				ConsoleIOPrint(DisAsmRegisterToString(pOperand->value.reg));
			}
			if (pOperand->hasIndex)
			{
				if (pOperand->hasBase)
				{
					ConsoleIOPrint(" + ");
				}
				if (pOperand->scale > 1)
				{
					ConsoleIOPrintFormatted("%d * ", pOperand->scale);
				}
				ConsoleIOPrint(DisAsmRegisterToString(pOperand->index));
			}
			if (pInfo->hasDisp)
			{
				if (IsNegative(pInfo->disp, pInfo->sizeDisp))
				{
					if (pOperand->hasBase || pOperand->hasIndex)
					{
						ConsoleIOPrint(" - ");
					}
					else 
					{
						ConsoleIOPrint("-");
					}

					PrintValue(Inverse(pInfo->disp, pInfo->sizeDisp));
				}
				else
				{
					if (pOperand->hasBase || pOperand->hasIndex)
					{
						ConsoleIOPrint(" + ");
					}
					PrintValue(pInfo->disp);
				}
			}
			ConsoleIOPrint("]");
		}
		else 
		{
			ConsoleIOPrint(DisAsmRegisterToString(pOperand->value.reg));
		}

	}
	if (HITYPE(pOperand->type) == J)
	{
		PrintValue(pInfo->imm);
	}
	if (pOperand->type == Imm)
	{
		PrintValue(pOperand->value.imm);
	}
	if (HITYPE(pOperand->type) == O)
	{
		PrintSegment(pInfo);
		ConsoleIOPrint("[");
		PrintValue(pInfo->imm);
		ConsoleIOPrint("]");
	}
	if (HITYPE(pOperand->type) == I)
	{
		if (IsNegative(pInfo->imm, pInfo->sizeImm))
		{
			ConsoleIOPrint("-");
			PrintValue(Inverse(pInfo->imm, pInfo->sizeImm));
		}
		else
		{
			PrintValue(pInfo->imm);
		}
	}
	if (HITYPE(pOperand->type) == X)
	{
		ConsoleIOPrint("DS:[ESI]");
	}
	if (HITYPE(pOperand->type) == Y)
	{
		ConsoleIOPrint("ES:[EDI]");
	}
}

void StrAsmPrintInstruction(InstructionInfo * pInfo)
{
	char * mnemonic = NULL;
	uint8_t i;
	for (i = 0; i < pInfo->length; ++i)
	{
		ConsoleIOPrintFormatted("%02X ", pInfo->bytes[i]);
	}
	for (i = pInfo->length; i < 15; ++i)
	{
		ConsoleIOPrint("   ");
	}
	for (i = 0; i < pInfo->nPrefixes; ++i)
	{
		switch (pInfo->prefixes[i].mnemonic)
		{
		case LOCK:
		case REPNE:
		case REPNZ:
		case REP:
		case REPE:
		case REPZ:
			mnemonic = DisAsmMnemonicToString(pInfo->prefixes[i].mnemonic);
			PrintColoredString(mnemonic, kGreen);
			ConsoleIOPrint(" ");
			break;
		default:
			break;
		}
	}
	mnemonic = DisAsmMnemonicToString(pInfo->mnemonic);
	if (mnemonic[0] == '_') ++mnemonic;
	PrintColoredString(mnemonic, kBlue);

	for (i = 0; i < pInfo->nOperands; ++i)
	{
		ConsoleIOPrint(i > 0 ? ", " : " ");
		PrintOperand(pInfo, &pInfo->operands[i]);
	}
}
