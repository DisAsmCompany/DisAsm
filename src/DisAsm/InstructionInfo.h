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
#ifndef __INSTRUCTIONINFO_H__A31D14F8_8717_4166_8F0A_0891FDE3DCD9__
#define __INSTRUCTIONINFO_H__A31D14F8_8717_4166_8F0A_0891FDE3DCD9__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kMaxOperands = 4 };
enum { kMaxInstruction = 15 };
enum { kMaxPrefixes = 4 };

typedef struct InstructionInfo_t
{
	/* instruction length, in bytes. currently, maximum allowed length is 15 bytes (kMaxInstruction) */
	uint8_t length;
	uint32_t opcode;
	Mnemonic mnemonic;
	uint8_t hasModRM : 1;
	uint8_t hasSIB   : 1;
	uint8_t hasSeg   : 1;
	uint8_t hasDisp  : 1;
	uint8_t hasImm   : 1;
	uint8_t hasVEX2  : 1;
	uint8_t hasVEX3  : 1;
	uint8_t hasXOP   : 1;
	uint8_t sizeDisp;
	uint8_t sizeImm;
	uint16_t seg;
	ModRMu ModRM;
	SIBu SIB;
	REXu REX;
	VEX2u VEX2;
	VEX3u VEX3;
	XOPu XOP;
	uint8_t nOperands;
	Operand operands[kMaxOperands];
	uint64_t disp;
	uint64_t imm;
	uint8_t nPrefixes;
	Prefix prefixes[kMaxPrefixes];
	uint8_t bytes[kMaxInstruction];
	InstructionSet set;
}
InstructionInfo;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INSTRUCTIONINFO_H__A31D14F8_8717_4166_8F0A_0891FDE3DCD9__ */
