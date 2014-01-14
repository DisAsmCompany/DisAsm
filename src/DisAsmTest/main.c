/*
* Filename: main.c
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: main test file to run unit tests
*              for the DisAsm library
*              
*
*/

#include "TestAssert.h"
#include "TestChooseOpCode.h"

#include "../DisAsm/DisAsm"
#include "../DisAsmPlatform/DisAsmPlatform"
#include "../StrAsm/StrAsm"
#include "../Executable/Executable"

void VerifyInstruction(uint8_t * bytes, uint8_t size, Mnemonic mnemonic)
{
	InstructionInfo info;
	CallbackReader reader;
	uint8_t length;
	uint8_t i;

	memset(&info, 0, sizeof(info));
	memset(&reader, 0, sizeof(reader));

	ConsoleIOPrint("Verify Instruction ");
	for (i = 0; i < size; ++i)
	{
		ConsoleIOPrintFormatted("0x%02X ", bytes[i]);
	}
	ConsoleIOPrintFormatted("%s\n", DisAsmMnemonicToString(mnemonic));

	reader.pRead    = CallbackRead;
	reader.pPrivate = &reader;
	reader.buffer = bytes;
	reader.length = size;
	reader.offset = 0;

	length = DisAsmInstructionDecode(32, &reader, &info);
	TestAssert(size == length);
	TestAssert(size == info.length);
	TestAssert(mnemonic == info.mnemonic);
}

void VerifyInstructionWithModRM(uint8_t * bytes, uint8_t size, Mnemonic mnemonic)
{
	uint8_t i = 0x00;

	ConsoleIOPrint("Verify Instruction with ModRM ");
	for (i = 0; i < size; ++i)
	{
		ConsoleIOPrintFormatted("0x%02X ", bytes[i]);
	}
	ConsoleIOPrintFormatted("%s\n", DisAsmMnemonicToString(mnemonic));

	do
	{
		CallbackReader reader;
		InstructionInfo info;
		uint8_t ModRM;
		uint8_t hasSIB;
		uint8_t * buffer = malloc(size + 6);
		uint8_t SIB = 0;
		uint8_t hasDisp = 0;
		uint8_t sizeDisp = 0;
		uint8_t length = 0;
		uint32_t expected = size + 1;

		memset(&info, 0, sizeof(info));
		memset(&reader, 0, sizeof(reader));
		memcpy(buffer, bytes, size);

		reader.pRead    = CallbackRead;
		reader.pPrivate = &reader;
		reader.buffer = (uint8_t*) buffer;
		reader.offset = 0;
		reader.length = size + 6;

		ModRM = i;
		hasSIB = (3 != MODRM_MOD(ModRM)) && (4 == MODRM_RM(ModRM));
		if (hasSIB)
		{
			++expected;
		}
		if (0 == MODRM_MOD(ModRM) && 5 == MODRM_RM(ModRM))
		{
			hasDisp = 1;
			sizeDisp = 4;
		}
		if (1 == MODRM_MOD(ModRM))
		{
			hasDisp = 1;
			sizeDisp = 1;
		}
		if (2 == MODRM_MOD(ModRM))
		{
			hasDisp = 1;
			sizeDisp = 4;
		}
		expected += sizeDisp;
		buffer[size] = ModRM;
		buffer[size + 1] = SIB;
		length = DisAsmInstructionDecode(32, &reader, &info);
		TestAssert(expected == length);
		TestAssert(expected == info.length);
		TestAssert(mnemonic == info.mnemonic);
		TestAssert(info.flags & kHasModRM);
		TestAssert(i == info.ModRM);
		TestAssert(hasSIB == (!!(info.flags & kHasSIB)));
		TestAssert(SIB == info.SIB);
		TestAssert(hasDisp == (!!(info.flags & kHasDisp)));
		TestAssert(sizeDisp == info.sizeDisp);
		++i;
	}
	while (i != 0);
}

/* very simple test to decode famous x86 NOP instruction - opcode 90h */
void TestNOP()
{
	uint8_t bytes[] = {0x90};
	VerifyInstruction(bytes, sizeof(bytes), NOP);
}

/* Primary Opcode Table (OpCodes 00h - FFh) */

/* 
  0 1 2 3 4 5 6 7   8 9 A B C D E F
0                 0                 0
1                 1                 1
2               X 2               X 2
3               X 3               X 3
4                 4                 4
5                 5                 5
6                 6                 6
7                 7                 7
  0 1 2 3 4 5 6 7   8 9 A B C D E F
8                 8 X X X X         8
9 X               9                 9
A                 A                 A
B                 B                 B
C                 C                 C
D                 D                 D
E                 E                 E
F         X X     F X X X X X X     F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

void TestPrimaryOpCodeTable()
{
	{
		uint8_t bytes[] = {0x27};
		VerifyInstruction(bytes, sizeof(bytes), DAA);
	}
	{
		uint8_t bytes[] = {0x37};
		VerifyInstruction(bytes, sizeof(bytes), AAA);
	}
	{
		uint8_t bytes[] = {0x2F};
		VerifyInstruction(bytes, sizeof(bytes), DAS);
	}
	{
		uint8_t bytes[] = {0x3F};
		VerifyInstruction(bytes, sizeof(bytes), AAS);
	}

	{
		uint8_t bytes[] = {0x88};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MOV);
	}
	{
		uint8_t bytes[] = {0x89};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MOV);
	}
	{
		uint8_t bytes[] = {0x8A};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MOV);
	}
	{
		uint8_t bytes[] = {0x8B};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MOV);
	}

	{
		uint8_t bytes[] = {0x90};
		VerifyInstruction(bytes, sizeof(bytes), NOP);
	}
	{
		uint8_t bytes[] = {0xF4};
		VerifyInstruction(bytes, sizeof(bytes), HLT);
	}
	{
		uint8_t bytes[] = {0xF5};
		VerifyInstruction(bytes, sizeof(bytes), CMC);
	}

	{
		uint8_t bytes[] = {0xF8};
		VerifyInstruction(bytes, sizeof(bytes), CLC);
	}
	{
		uint8_t bytes[] = {0xF9};
		VerifyInstruction(bytes, sizeof(bytes), STC);
	}
	{
		uint8_t bytes[] = {0xFA};
		VerifyInstruction(bytes, sizeof(bytes), CLI);
	}
	{
		uint8_t bytes[] = {0xFB};
		VerifyInstruction(bytes, sizeof(bytes), STI);
	}
	{
		uint8_t bytes[] = {0xFC};
		VerifyInstruction(bytes, sizeof(bytes), CLD);
	}
	{
		uint8_t bytes[] = {0xFD};
		VerifyInstruction(bytes, sizeof(bytes), STD);
	}
}

/* Secondary Opcode Table (OpCodes 0F00h - 0FFFh) */

/* 
  0 1 2 3 4 5 6 7   8 9 A B C D E F
0                 0                 0
1                 1                 1
2                 2                 2
3                 3                 3
4                 4                 4
5                 5                 5
6                 6                 6
7                 7                 7
  0 1 2 3 4 5 6 7   8 9 A B C D E F
8                 8                 8
9                 9                 9
A     X           A                 A
B                 B                 B
C                 C                 C
D                 D                 D
E                 E                 E
F                 F                 F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

void TestSecondaryOpCodeTable()
{
	{
		uint8_t bytes[] = {0x0F, 0xA2};
		VerifyInstruction(bytes, sizeof(bytes), CPUID);
	}
}

void TestSSE()
{
	{
		/* no prefixes - MULPS */
		uint8_t bytes[] = {0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULPS);
	}
	{
		/* prefix 0x66 - MULPD */
		uint8_t bytes[] = {0x66, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULPD);
	}
	{
		/* prefix 0xF2 - MULSD */
		uint8_t bytes[] = {0xF2, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSD);
	}
	{
		/* prefix 0xF3 - MULSS */
		uint8_t bytes[] = {0xF3, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSS);
	}
	/* same prefixes used twice */
	{
		/* prefix 0x66 0x66 - still MULPD */
		uint8_t bytes[] = {0x66, 0x66, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULPD);
	}
	{
		/* 0xF2 0xF2 - still MULSD */
		uint8_t bytes[] = {0xF2, 0xF2, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSD);
	}
	{
		/* 0xF3 0xF3 - still MULSS */
		uint8_t bytes[] = {0xF3, 0xF3, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSS);
	}
	/* two different prefixes */
	{
		/* 0x66 0xF2 - 0xF2 wins, so MULSD */
		uint8_t bytes[] = {0x66, 0xF2, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSD);
	}
	{
		/* 0xF2 0x66 - 0xF2 wins, so MULSD */
		uint8_t bytes[] = {0xF2, 0x66, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSD);
	}
	{
		/* 0x66 0xF3 - 0xF3 wins, so MULSS */
		uint8_t bytes[] = {0x66, 0xF3, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSS);
	}
	{
		/* 0xF3 0x66 - 0xF3 wins, so MULSS */
		uint8_t bytes[] = {0xF3, 0x66, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSS);
	}
	{
		/* 0xF2 0xF3 - 0xF3 wins, so MULSS */
		uint8_t bytes[] = {0xF2, 0xF3, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSS);
	}
	{
		/* 0xF3 0xF2 - 0xF2 wins, so MULSD */
		uint8_t bytes[] = {0xF3, 0xF2, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSD);
	}
	/* three different prefixes */
	{
		/* 0x66 0xF2 0xF3 - 0xF3 wins, so MULSS */
		uint8_t bytes[] = {0x66, 0xF2, 0xF3, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSS);
	}
	{
		/* 0x66 0xF3 0xF2 - 0xF2 wins, so MULSD */
		uint8_t bytes[] = {0x66, 0xF3, 0xF2, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSD);
	}
	{
		/* 0xF2 0x66 0xF3 - 0xF3 wins, so MULSS */
		uint8_t bytes[] = {0xF2, 0x66, 0xF3, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSS);
	}
	{
		/* 0xF2 0xF3 0x66 - 0xF3 wins, so MULSS */
		uint8_t bytes[] = {0xF2, 0xF3, 0x66, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSS);
	}
	{
		/* 0xF3 0x66 0xF2 - 0xF2 wins, so MULSD */
		uint8_t bytes[] = {0xF3, 0x66, 0xF2, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSD);
	}
	{
		/* 0xF3 0xF2 0x66 - 0xF2 wins, so MULSD */
		uint8_t bytes[] = {0xF3, 0xF2, 0x66, 0x0F, 0x59};
		VerifyInstructionWithModRM(bytes, sizeof(bytes), MULSD);
	}
	{
		uint8_t bytes[] = {0xC3};
	        VerifyInstruction(bytes, sizeof(bytes), RET);
	}
	{
                uint8_t bytes[] = {0xCB};
                VerifyInstruction(bytes, sizeof(bytes), RET);
        }
	{
                uint8_t bytes[] = {0xCE};
                VerifyInstruction(bytes, sizeof(bytes), INTO);
        }
	{
                uint8_t bytes[] = {0x60};
                VerifyInstruction(bytes, sizeof(bytes), PUSHA);
        }
	{
                uint8_t bytes[] = {0x61};
                VerifyInstruction(bytes, sizeof(bytes), POPA);
        }
        {
                uint8_t bytes[] = {0xD7};
                VerifyInstruction(bytes, sizeof(bytes), XLAT);
        }
        {
                uint8_t bytes[] = {0x98};
                VerifyInstruction(bytes, sizeof(bytes), CBW);
        }
        {
                uint8_t bytes[] = {0x99};
                VerifyInstruction(bytes, sizeof(bytes), CWD);
        }
        {
                uint8_t bytes[] = {0x9B};
                VerifyInstruction(bytes, sizeof(bytes), WAIT);
        }
        {
                uint8_t bytes[] = {0x9E};
                VerifyInstruction(bytes, sizeof(bytes), SAHF);
        }
        {
                uint8_t bytes[] = {0x9F};
                VerifyInstruction(bytes, sizeof(bytes), LAHF);
        }
        {
                uint8_t bytes[] = {0xC9};
                VerifyInstruction(bytes, sizeof(bytes), LEAVE);
        }
        {
                uint8_t bytes[] = {0xCF};
                VerifyInstruction(bytes, sizeof(bytes), IRET);
        }
        {
                uint8_t bytes[] = {0x00};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), ADD);
        }
        {
                uint8_t bytes[] = {0x01};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), ADD);
        }
        {
                uint8_t bytes[] = {0x02};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), ADD);
        }
        {
                uint8_t bytes[] = {0x03};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), ADD);
        }
        {
                uint8_t bytes[] = {0x10};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), ADC);
        }
        {
                uint8_t bytes[] = {0x11};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), ADC);
        }
        {
                uint8_t bytes[] = {0x12};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), ADC);
        }
        {
                uint8_t bytes[] = {0x13};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), ADC);
        }
        {
                uint8_t bytes[] = {0x20};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), AND);
        }
        {
                uint8_t bytes[] = {0x21};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), AND);
        }
        {
                uint8_t bytes[] = {0x22};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), AND);
        }
        {
                uint8_t bytes[] = {0x23};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), AND);
        }
        {
                uint8_t bytes[] = {0x30};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), XOR);
        }
        {
                uint8_t bytes[] = {0x31};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), XOR);
        }
        {
                uint8_t bytes[] = {0x32};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), XOR);
        }
        {
                uint8_t bytes[] = {0x33};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), XOR);
        }
        {
                uint8_t bytes[] = {0x08};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), OR);
        }
        {
                uint8_t bytes[] = {0x09};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), OR);
        }
        {
                uint8_t bytes[] = {0x0A};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), OR);
        }
        {
                uint8_t bytes[] = {0x0B};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), OR);
        }
        {
                uint8_t bytes[] = {0x18};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), SBB);
        }
        {
                uint8_t bytes[] = {0x19};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), SBB);
        }
        {
                uint8_t bytes[] = {0x1A};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), SBB);
        }
        {
                uint8_t bytes[] = {0x1B};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), SBB);
        }
        {
                uint8_t bytes[] = {0x28};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), SUB);
        }
        {
                uint8_t bytes[] = {0x29};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), SUB);
        }
        {
                uint8_t bytes[] = {0x2A};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), SUB);
        }
        {
                uint8_t bytes[] = {0x2B};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), SUB);
        }
        {
                uint8_t bytes[] = {0x38};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), CMP);
        }
        {
                uint8_t bytes[] = {0x39};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), CMP);
        }
        {
                uint8_t bytes[] = {0x3B};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), CMP);
        }
        {
                uint8_t bytes[] = {0x3A};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), CMP);
        }
        {
                uint8_t bytes[] = {0x3C};
                VerifyInstructionWithModRM(bytes, sizeof(bytes), CMP);
        }


}

int main()
{
	ConsoleIOInit();
	CrashHandlerInstall();

	TestChooseOpCode();
	TestNOP();
	TestPrimaryOpCodeTable();
	TestSecondaryOpCodeTable();
	TestSSE();
	return EXIT_SUCCESS;
}
