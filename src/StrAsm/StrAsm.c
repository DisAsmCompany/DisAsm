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
#define _STR_ENUM
#undef  __MNEMONIC_H__
#undef  __REGISTER_H__
#include "../DisAsm/DisAsm"
#include "StrAsm"

void PrintByte(uint32_t value)
{
	printf("%02X", value);
}

void InternalPrintString(const char * string, TextColor color)
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO info = {0};
	DWORD mode = 0;
	DWORD written = 0;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleMode(hStdOut, &mode))
	{
		WORD attributes;
		GetConsoleScreenBufferInfo(hStdOut, &info);
		attributes = info.wAttributes & ~(FOREGROUND_BLUE | FOREGROUND_GREEN |FOREGROUND_RED | FOREGROUND_INTENSITY);
		attributes |= (color & kRed)   ? FOREGROUND_RED   : 0;
		attributes |= (color & kGreen) ? FOREGROUND_GREEN : 0;
		attributes |= (color & kBlue)  ? FOREGROUND_BLUE  : 0;
		attributes |= FOREGROUND_INTENSITY;
		SetConsoleTextAttribute(hStdOut, attributes);
		WriteConsole(hStdOut, string, strlen(string), &written, NULL);
		SetConsoleTextAttribute(hStdOut, info.wAttributes);
	}
	else
	{
		WriteFile(hStdOut, string, strlen(string), &written, NULL);
	}
	FlushFileBuffers(hStdOut);
#else /* _WIN32 */
	printf("%s", string);
#endif /* _WIN32 */
}

void PrintError(const char * string)
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO info = {0};
	DWORD mode = 0;
	DWORD written = 0;
	HANDLE hStdOut = GetStdHandle(STD_ERROR_HANDLE);
	if (GetConsoleMode(hStdOut, &mode))
	{
		WORD attributes;
		GetConsoleScreenBufferInfo(hStdOut, &info);
		attributes = info.wAttributes & ~(FOREGROUND_BLUE | FOREGROUND_GREEN |FOREGROUND_RED | FOREGROUND_INTENSITY);
		attributes |= FOREGROUND_RED | FOREGROUND_INTENSITY;
		SetConsoleTextAttribute(hStdOut, attributes);
		WriteConsole(hStdOut, string, strlen(string), &written, NULL);
		SetConsoleTextAttribute(hStdOut, info.wAttributes);
	}
	else
	{
		WriteFile(hStdOut, string, strlen(string), &written, NULL);
	}
	FlushFileBuffers(hStdOut);
	OutputDebugStringA(string);
#else /* _WIN32 */
	fprintf(stderr, "%s", string);
#endif /* _WIN32 */
}

void PrintString(const char * string, TextColor color)
{
	InternalPrintString(string, color);
}

uint8_t IsNegative(uint32_t value, uint8_t size)
{
	return !!(value & (0x80 << 8 * (size - 1)));
}

uint32_t Inverse(uint32_t value, uint8_t size)
{
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
	printf("h");
}

void PrintSegment(InstructionInfo * pInfo)
{
	uint8_t i;
	for (i = 0; i < pInfo->nPrefixes; ++i)
	{
		switch (pInfo->prefixes[i].mnemonic)
		{
		case PrefixCS: printf("CS:"); break;
		case PrefixSS: printf("SS:"); break;
		case PrefixDS: printf("DS:"); break;
		case PrefixES: printf("ES:"); break;
		case PrefixFS: printf("FS:"); break;
		case PrefixGS: printf("GS:"); break;
		default:break;
		}
	}
}

void PrintOperand(InstructionInfo * pInfo, Operand * pOperand)
{
	if (pOperand->type == Reg)
	{
		char * reg = RegisterToString(pOperand->value.reg);
		if (pOperand->memory)
		{
			PrintSegment(pInfo);
			printf("[");

			if (pOperand->hasBase)
			{
				char * base = RegisterToString(pOperand->base);
				printf("%s", base);
			}
			if (pOperand->hasIndex)
			{
				if (pOperand->hasBase)
				{
					printf(" + ");
				}
				if (pOperand->scale > 1)
				{
					printf("%d * ", pOperand->scale);
				}
				printf("%s", RegisterToString(pOperand->index));
			}
			if (pInfo->hasDisp)
			{
				if (IsNegative(pInfo->disp, pInfo->sizeDisp))
				{
					if (pOperand->hasBase || pOperand->hasIndex)
					{
						printf(" - ");
					}
					else 
					{
						printf("-");
					}

					PrintValue(Inverse(pInfo->disp, pInfo->sizeDisp));
				}
				else
				{
					if (pOperand->hasBase || pOperand->hasIndex)
					{
						printf(" + ");
					}
					PrintValue(pInfo->disp);
				}
			}
			printf("]");
		}
		else 
		{
			printf("%s", reg);
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
		printf("[");
		PrintValue(pInfo->imm);
		printf("]");
	}
	if (HITYPE(pOperand->type) == I)
	{
		if (IsNegative(pInfo->imm, pInfo->sizeImm))
		{
			printf("-");
			PrintValue(Inverse(pInfo->imm, pInfo->sizeImm));
		}
		else
		{
			PrintValue(pInfo->imm);
		}
	}
	if (HITYPE(pOperand->type) == X)
	{
		printf("DS:[ESI]");
	}
	if (HITYPE(pOperand->type) == Y)
	{
		printf("ES:[EDI]");
	}
}

void StrAsmPrintInstruction(InstructionInfo * pInfo)
{
	char * mnemonic = NULL;
	uint8_t i;
	for (i = 0; i < pInfo->length; ++i)
	{
		PrintByte(pInfo->bytes[i]);
		printf(" ");
	}
	for (i = pInfo->length; i < 15; ++i)
	{
		printf("   ");
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
			mnemonic = MnemonicToString(pInfo->prefixes[i].mnemonic);
			printf("%s ", mnemonic);
			break;
		default:
			break;
		}
	}
	mnemonic = MnemonicToString(pInfo->mnemonic);
	if (mnemonic[0] == '_') ++mnemonic;
	PrintString(mnemonic, kBlue);

	for (i = 0; i < pInfo->nOperands; ++i)
	{
		printf(i > 0 ? ", " : " ");
		PrintOperand(pInfo, &pInfo->operands[i]);
	}
}
