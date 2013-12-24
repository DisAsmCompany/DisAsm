/*
 * Filename: ELFMachine.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Machine (x86, PowerPC, etc)
 *
 *
 *
 */

#pragma once
#ifndef __ELFMACHINE_H__69A6BCF3_022C_49E3_BE36_731CE1DABCB6__
#define __ELFMACHINE_H__69A6BCF3_022C_49E3_BE36_731CE1DABCB6__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum ELFMachine_t
{
	kELFMachine386   = 0x0003,
	kELFMachine486   = 0x0006,
	kELFMachineX8664 = 0x003E
}
ELFMachine;

static const SDFEnum _ELFMachine[] =
{
	{"EM_NONE",        0x0000, 0},
	{"EM_M32",         0x0001, 0},
	{"EM_SPARC",       0x0002, 0},
	{"EM_386",         kELFMachine386, 0},
	{"EM_68K",         0x0004, 0},
	{"EM_88K",         0x0005, 0},
	{"EM_860",         0x0007, 0},
	{"EM_486",         kELFMachine486, 0},
	{"EM_MIPS",        0x0008, 0},
	{"EM_MIPS_RS4_BE", 0x000A, 0},
	{"EM_PARISC",      0x000F, 0},
	{"EM_SPARC32PLUS", 0x0012, 0},
	{"EM_PPC",         0x0014, 0},
	{"EM_PPC64",       0x0015, 0},
	{"EM_SH",          0x002A, 0},
	{"EM_SPARCV9",     0x002B, 0},
	{"EM_IA_64",       0x0032, 0},
	{"EM_X8664",       kELFMachineX8664, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFMACHINE_H__69A6BCF3_022C_49E3_BE36_731CE1DABCB6__ */
