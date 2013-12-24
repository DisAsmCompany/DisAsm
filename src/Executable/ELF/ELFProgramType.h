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
#ifndef __ELFPROGRAMTYPE_H__354C9025_C753_4747_9743_3EE88B4D7F38__
#define __ELFPROGRAMTYPE_H__354C9025_C753_4747_9743_3EE88B4D7F38__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFProgramType[] =
{
	{"PT_NULL",         0x00000000UL, 0},
	{"PT_LOAD",         0x00000001UL, 0},
	{"PT_DYNAMIC",      0x00000002UL, 0},
	{"PT_INTERP",       0x00000003UL, 0},
	{"PT_NOTE",         0x00000004UL, 0},
	{"PT_SHLIB",        0x00000005UL, 0},
	{"PT_PHDR",         0x00000006UL, 0},
	{"PT_GNU_EH_FRAME", 0x6474e550UL, 0},
	{"PT_GNU_STACK",    0x6474e551UL, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFPROGRAMTYPE_H__354C9025_C753_4747_9743_3EE88B4D7F38__ */
