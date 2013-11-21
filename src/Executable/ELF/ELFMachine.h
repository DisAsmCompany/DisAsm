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
	{"EM_NONE",        0x0000},
	{"EM_M32",         0x0001},
	{"EM_SPARC",       0x0002},
	{"EM_386",         kELFMachine386},
	{"EM_68K",         0x0004},
	{"EM_88K",         0x0005},
	{"EM_860",         0x0007},
	{"EM_486",         kELFMachine486},
	{"EM_MIPS",        0x0008},
	{"EM_MIPS_RS4_BE", 0x000A},
	{"EM_PARISC",      0x000F},
	{"EM_SPARC32PLUS", 0x0012},
	{"EM_PPC",         0x0014},
	{"EM_PPC64",       0x0015},
	{"EM_SH",          0x002A},
	{"EM_SPARCV9",     0x002B},
	{"EM_IA_64",       0x0032},
	{"EM_X8664",       kELFMachineX8664},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFMACHINE_H__69A6BCF3_022C_49E3_BE36_731CE1DABCB6__ */
