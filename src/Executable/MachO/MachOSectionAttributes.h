/*
 * Filename: MachOSectionAttributes.h
 * Author:   DisAsmCompany
 * Date:     21/10/2013
 *
 * Description: Mach-O Section Types & Flags
 *
 *              
 *
 */

#pragma once
#ifndef __MACHOSECTIONATTRIBUTES_H__
#define __MACHOSECTIONATTRIBUTES_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum MachOSectionAttributes[] =
{
	/* types */
	{"S_REGULAR",                             0x00000000UL, 0x000000FFUL},
	{"S_ZEROFILL",                            0x00000001UL, 0x000000FFUL},
	{"S_CSTRING_LITERALS",                    0x00000002UL, 0x000000FFUL},
	{"S_4BYTE_LITERALS",                      0x00000003UL, 0x000000FFUL},
	{"S_8BYTE_LITERALS",                      0x00000004UL, 0x000000FFUL},
	{"S_LITERAL_POINTERS",                    0x00000005UL, 0x000000FFUL},
	{"S_NON_LAZY_SYMBOL_POINTERS",            0x00000006UL, 0x000000FFUL},
	{"S_LAZY_SYMBOL_POINTERS",                0x00000007UL, 0x000000FFUL},
	{"S_SYMBOL_STUBS",                        0x00000008UL, 0x000000FFUL},
	{"S_MOD_INIT_FUNC_POINTERS",              0x00000009UL, 0x000000FFUL},
	{"S_MOD_TERM_FUNC_POINTERS",              0x0000000AUL, 0x000000FFUL},
	{"S_COALESCED",                           0x0000000BUL, 0x000000FFUL},
	{"S_GB_ZEROFILL",                         0x0000000CUL, 0x000000FFUL},
	{"S_INTERPOSING",                         0x0000000DUL, 0x000000FFUL},
	{"S_16BYTE_LITERALS",                     0x0000000EUL, 0x000000FFUL},
	{"S_DTRACE_DOF",                          0x0000000FUL, 0x000000FFUL},
	{"S_LAZY_DYLIB_SYMBOL_POINTERS",          0x00000010UL, 0x000000FFUL},
	{"S_THREAD_LOCAL_REGULAR",                0x00000011UL, 0x000000FFUL},
	{"S_THREAD_LOCAL_ZEROFILL",               0x00000012UL, 0x000000FFUL},
	{"S_THREAD_LOCAL_VARIABLES",              0x00000013UL, 0x000000FFUL},
	{"S_THREAD_LOCAL_VARIABLE_POINTERS",      0x00000014UL, 0x000000FFUL},
	{"S_THREAD_LOCAL_INIT_FUNCTION_POINTERS", 0x00000015UL, 0x000000FFUL},
	/* system attributes */
	{"S_ATTR_LOC_RELOC",                      0x00000100UL, 0x00000100UL},
	{"S_ATTR_EXT_RELOC",                      0x00000200UL, 0x00000200UL},
	{"S_ATTR_SOME_INSTRUCTIONS",              0x00000400UL, 0x00000400UL},
	/* user attributes */
	{"S_ATTR_DEBUG",                          0x02000000UL, 0x02000000UL},
	{"S_ATTR_SELF_MODIFYING_CODE",            0x04000000UL, 0x04000000UL},
	{"S_ATTR_LIVE_SUPPORT",                   0x08000000UL, 0x08000000UL},
	{"S_ATTR_NO_DEAD_STRIP",                  0x10000000UL, 0x10000000UL},
	{"S_ATTR_STRIP_STATIC_SYMS",              0x20000000UL, 0x20000000UL},
	{"S_ATTR_NO_TOC",                         0x40000000UL, 0x40000000UL},
	{"S_ATTR_PURE_INSTRUCTIONS",              0x80000000UL, 0x80000000UL},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSECTIONATTRIBUTES_H__ */
