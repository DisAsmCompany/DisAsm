/*
 * Filename: ELFSectionFlags.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Section Flags
 *
 *
 *
 */

#pragma once
#ifndef __ELFSECTIONFLAGS_H__70636818_EE51_4C1C_9DE7_168DF75F38E7__
#define __ELFSECTIONFLAGS_H__70636818_EE51_4C1C_9DE7_168DF75F38E7__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFSectionFlags[] =
{
	{"SHF_WRITE",     0x00000001UL, 0x00000001UL},
	{"SHF_ALLOC",     0x00000002UL, 0x00000002UL},
	{"SHF_EXECINSTR", 0x00000004UL, 0x00000004UL},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFSECTIONFLAGS_H__70636818_EE51_4C1C_9DE7_168DF75F38E7__ */
