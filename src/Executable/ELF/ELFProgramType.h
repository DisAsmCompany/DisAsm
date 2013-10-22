/*
 * Filename: ELFProgramType.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Program Type
 *
 *
 *
 */

#pragma once
#ifndef __ELFPROGRAMTYPE_H__
#define __ELFPROGRAMTYPE_H__

static const SDFEnum ELFProgramType[] =
{
	{"PT_NULL",    0x0000},
	{"PT_LOAD",    0x0001},
	{"PT_DYNAMIC", 0x0002},
	{"PT_INTERP",  0x0003},
	{"PT_NOTE",    0x0004},
	{"PT_SHLIB",   0x0005},
	{"PT_PHDR",    0x0006},
	{NULL}
};

#endif /* __ELFPROGRAMTYPE_H__ */
