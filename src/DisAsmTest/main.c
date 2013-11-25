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
#include "../StrAsm/StrAsm"
#include "../Executable/Executable"

void VerifyInstruction(uint32_t opcode, Mnemonic mnemonic)
{
	InstructionInfo info = {0};
	CallbackReader reader = {0};
	uint8_t length;

	reader.pRead    = CallbackRead;
	reader.pPrivate = &reader;
	reader.buffer = (uint8_t*) &opcode;
	reader.offset = 0;
	
	length = DisAsmInstructionDecode(32, &reader, &info);
	TestAssert(1 == length);
	TestAssert(1 == info.length);
	TestAssert(mnemonic == info.mnemonic);
}

void VerifyInstructionWithModRM(uint32_t opcode, Mnemonic mnemonic)
{
	uint8_t i = 0x00;
	do
	{
		CallbackReader reader = {0};
		InstructionInfo info = {0};
		ModRMu ModRM;
		uint8_t hasSIB;
		uint8_t buffer[7];
		uint8_t SIB = 0;
		uint8_t hasDisp = 0;
		uint8_t sizeDisp = 0;
		uint8_t length = 0;
		uint8_t expected = 2;

		reader.pRead    = CallbackRead;
		reader.pPrivate = &reader;
		reader.buffer = (uint8_t*) buffer;
		reader.offset = 0;

		ModRM.value = i;
		hasSIB = (3 != ModRM.fields.Mod) && (4 == ModRM.fields.RM);
		if (hasSIB)
		{
			++expected;
		}
		if (0 == ModRM.fields.Mod && 5 == ModRM.fields.RM)
		{
			hasDisp = 1;
			sizeDisp = 4;
		}
		if (1 == ModRM.fields.Mod)
		{
			hasDisp = 1;
			sizeDisp = 1;
		}
		if (2 == ModRM.fields.Mod)
		{
			hasDisp = 1;
			sizeDisp = 4;
		}
		expected += sizeDisp;
		buffer[0] = (uint8_t) opcode;
		buffer[1] = ModRM.value;
		buffer[2] = SIB;
		length = DisAsmInstructionDecode(32, &reader, &info);
		TestAssert(expected == length);
		TestAssert(expected == info.length);
		TestAssert(mnemonic == info.mnemonic);
		TestAssert(1 == info.hasModRM);
		TestAssert(i == info.ModRM.value);
		TestAssert(hasSIB == info.hasSIB);
		TestAssert(SIB == info.SIB.value);
		TestAssert(hasDisp == info.hasDisp);
		TestAssert(sizeDisp == info.sizeDisp);
		++i;
	}
	while (i != 0);
}

/* very simple test to decode famous x86 NOP instruction - opcode 90h */
void TestNOP()
{
	VerifyInstruction(0x90, NOP);
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
	VerifyInstruction(0x27, DAA);
	VerifyInstruction(0x37, AAA);
	VerifyInstruction(0x2F, DAS);
	VerifyInstruction(0x3F, AAS);

	VerifyInstructionWithModRM(0x88, MOV);
	VerifyInstructionWithModRM(0x89, MOV);
	VerifyInstructionWithModRM(0x8A, MOV);
	VerifyInstructionWithModRM(0x8B, MOV);

	VerifyInstruction(0x90, NOP);

	VerifyInstruction(0xF4, HLT);
	VerifyInstruction(0xF5, CMC);

	VerifyInstruction(0xF8, CLC);
	VerifyInstruction(0xF9, STC);
	VerifyInstruction(0xFA, CLI);
	VerifyInstruction(0xFB, STI);
	VerifyInstruction(0xFC, CLD);
	VerifyInstruction(0xFD, STD);
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
9 X               9                 9
A                 A                 A
B                 B                 B
C                 C                 C
D                 D                 D
E                 E                 E
F                 F                 F
  0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

void TestSecondaryOpCodeTable()
{

}

int main(int argc, char * const argv[])
{
	TestChooseOpCode();
	TestNOP();
	TestPrimaryOpCodeTable();
	TestSecondaryOpCodeTable();
	return EXIT_SUCCESS;
}
