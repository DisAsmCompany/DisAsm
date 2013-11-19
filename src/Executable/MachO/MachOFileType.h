/*
 * Filename: MachOFileType.h
 * Author:   DisAsmCompany
 * Date:     21/10/2013
 *
 * Description: Mach-O File Type
 *              (bundle, dylib, executable)
 *              
 *
 */

#pragma once
#ifndef __MACHOFILETYPE_H__
#define __MACHOFILETYPE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum MachOFileType[] =
{
	{"MH_OBJECT",      0x00000001UL},
	{"MH_EXECUTE",     0x00000002UL},
	{"MH_FVMLIB",      0x00000003UL},
	{"MH_CORE",        0x00000004UL},
	{"MH_PRELOAD",     0x00000005UL},
	{"MH_DYLIB",       0x00000006UL},
	{"MH_DYLINKER",    0x00000007UL},
	{"MH_BUNDLE",      0x00000008UL},
	{"MH_DYLIB_STUB",  0x00000009UL},
	{"MH_DSYM",        0x0000000AUL},
	{"MH_KEXT_BUNDLE", 0x0000000BUL},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOFILETYPE_H__ */
