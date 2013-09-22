/*
* Filename: InstructionInfo.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: information about instruction
*              (opcode, number and types of
*              operands, subset, etc)
*
*/

#pragma once
#ifndef __INSTRUCTIONINFO_H__
#define __INSTRUCTIONINFO_H__

typedef struct InstructionInfo_t
{
	int length;
	OpCode opcode;
	Mnemonic mnemonic;
	unsigned char hasModRM;
	unsigned char hasSIB;
	unsigned char hasDisp;
	unsigned char sizeDisp;
	unsigned char hasImm;
	unsigned char sizeImm;
	ModRMu ModRM;
	unsigned char SIB;
	unsigned char operands;
	Operand operand1;
	Operand operand2;
	Operand operand3;
	unsigned long disp;
	unsigned long imm;
	unsigned char nPrefixes;
	Prefix prefixes[MAX_PREFIXES];
}
InstructionInfo;

#endif // __INSTRUCTIONINFO_H__
