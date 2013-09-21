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

#include <stdio.h>
#include <stdlib.h>

#include "../DisAsm/DisAsm"
#include "../StrAsm/StrAsm"

void TestAssert(int expression)
{
	if (!expression)
	{
		abort();
	}
}

void VerifyInstruction(OpCode opcode, Mnemonic mnemonic)
{
	InstructionInfo info = {0};
	unsigned char * buffer = (unsigned char*) &opcode;
	int length = DisAsmInstructionDecode(buffer, &info);
	TestAssert(1 == length);
	TestAssert(1 == info.length);
	TestAssert(mnemonic == info.mnemonic);
}

void VerifyInstructionWithModRM(OpCode opcode, Mnemonic mnemonic)
{
	unsigned char ModRM = 0x00;
	do
	{
		InstructionInfo info = {0};
		unsigned char hasSIB = 0x18 == (ModRM & 0x1C);
		unsigned char buffer[3];
		unsigned char SIB = 0;
		int length = 0;
		int expected = hasSIB ? 3 : 2;
		buffer[0] = (unsigned char)opcode;
		buffer[1] = ModRM;
		buffer[2] = SIB;
		length = DisAsmInstructionDecode(buffer, &info);
		TestAssert(expected == length);
		TestAssert(expected == info.length);
		TestAssert(mnemonic == info.mnemonic);
		TestAssert(1 == info.hasModRM);
		TestAssert(ModRM == info.ModRM.value);
		TestAssert(hasSIB == info.hasSIB);
		TestAssert(SIB == info.SIB);
		++ModRM;
	}
	while (ModRM != 0);
}

/* very simple test to decode famous x86 NOP instruction - opcode 90h */
void TestNOP()
{
	VerifyInstruction(0x90, NOP);
}

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

int main(int argc, char * const argv[])
{
	TestNOP();
	TestPrimaryOpCodeTable();
	return EXIT_SUCCESS;
}
