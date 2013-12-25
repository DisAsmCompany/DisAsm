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

enum
{
	kHasModRM = 0x00000001UL,
	kHasSIB   = 0x00000002UL,
	kHasSeg   = 0x00000004UL,
	kHasDisp  = 0x00000008UL,
	kHasImm   = 0x00000010UL,
	kHasVEX2  = 0x00000020UL,
	kHasVEX3  = 0x00000040UL,
	kHasXOP3  = 0x00000080UL,
};

typedef struct InstructionInfo_t
{
	/* instruction length, in bytes. currently, maximum allowed length is 15 bytes (kMaxInstruction) */
	uint8_t length;
	uint32_t opcode;
	Mnemonic mnemonic;
	uint8_t sizeDisp;
	uint8_t sizeImm;
	uint16_t seg;
	uint32_t flags;
	uint8_t ModRM;
	uint8_t SIB;
	uint8_t REX;
	uint8_t VEX2;
	uint16_t VEX3;
	uint16_t XOP3;
	uint8_t nOperands;
	Operand operands[kMaxOperands];
	uint64_t disp;
	uint64_t imm;
	uint8_t nPrefixes;
	Prefix prefixes[kMaxPrefixes];
	uint8_t bytes[kMaxInstruction];
	uint8_t LegacySSEPrefix;
	InstructionSet set;
}
InstructionInfo;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INSTRUCTIONINFO_H__A31D14F8_8717_4166_8F0A_0891FDE3DCD9__ */
