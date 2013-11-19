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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFProgramType[] =
{
	{"PT_NULL",         0x00000000UL},
	{"PT_LOAD",         0x00000001UL},
	{"PT_DYNAMIC",      0x00000002UL},
	{"PT_INTERP",       0x00000003UL},
	{"PT_NOTE",         0x00000004UL},
	{"PT_SHLIB",        0x00000005UL},
	{"PT_PHDR",         0x00000006UL},
	{"PT_GNU_EH_FRAME", 0x6474e550UL},
	{"PT_GNU_STACK",    0x6474e551UL},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFPROGRAMTYPE_H__ */
