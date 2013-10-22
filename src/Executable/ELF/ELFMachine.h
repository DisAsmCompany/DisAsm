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
#ifndef __ELFMACHINE_H__
#define __ELFMACHINE_H__

static const SDFEnum ELFMachine[] =
{
	{"EM_NONE",        0x0000},
	{"EM_M32",         0x0001},
	{"EM_SPARC",       0x0002},
	{"EM_386",         0x0003},
	{"EM_68K",         0x0004},
	{"EM_88K",         0x0005},
	{"EM_860",         0x0007},
	{"EM_MIPS",        0x0008},
	{"EM_MIPS_RS4_BE", 0x000A},
	{NULL}
};

#endif /* __ELFMACHINE_H__ */
