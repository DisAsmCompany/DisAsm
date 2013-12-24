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
#ifndef __MACHOFILETYPE_H__A374D1F4_CFEA_460D_8189_00DC6CC32E40__
#define __MACHOFILETYPE_H__A374D1F4_CFEA_460D_8189_00DC6CC32E40__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum MachOFileType[] =
{
	{"MH_OBJECT",      0x00000001UL, 0},
	{"MH_EXECUTE",     0x00000002UL, 0},
	{"MH_FVMLIB",      0x00000003UL, 0},
	{"MH_CORE",        0x00000004UL, 0},
	{"MH_PRELOAD",     0x00000005UL, 0},
	{"MH_DYLIB",       0x00000006UL, 0},
	{"MH_DYLINKER",    0x00000007UL, 0},
	{"MH_BUNDLE",      0x00000008UL, 0},
	{"MH_DYLIB_STUB",  0x00000009UL, 0},
	{"MH_DSYM",        0x0000000AUL, 0},
	{"MH_KEXT_BUNDLE", 0x0000000BUL, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOFILETYPE_H__A374D1F4_CFEA_460D_8189_00DC6CC32E40__ */
