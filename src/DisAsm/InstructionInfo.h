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
	uint8_t length;
	OpCode opcode;
	Mnemonic mnemonic;
	uint8_t hasModRM;
	uint8_t hasSIB;
	uint8_t hasDisp;
	uint8_t sizeDisp;
	uint8_t hasImm;
	uint8_t sizeImm;
	ModRMu ModRM;
	SIBu SIB;
	uint8_t nOperands;
	Operand operands[4];
	uint32_t disp;
	uint32_t imm;
	uint8_t nPrefixes;
	Prefix prefixes[MAX_PREFIXES];
	uint8_t bytes[16];
	InstructionSet set;
}
InstructionInfo;

#endif /* __INSTRUCTIONINFO_H__ */
