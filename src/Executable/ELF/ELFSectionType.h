/*
 * Filename: ELFSectionType.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Section Type
 *
 *
 *
 */

#pragma once
#ifndef __ELFSECTIONTYPE_H__
#define __ELFSECTIONTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum ELFSectionType_t
{
	kELFSectionSymTab = 0x00000002UL,
	kELFSectionStrTab = 0x00000003UL,
	kELFSectionDynSym = 0x0000000BUL
}
ELFSectionType;

static const SDFEnum _ELFSectionType[] =
{
	{"SHT_NULL",           0x00000000UL},
	{"SHT_PROGBITS",       0x00000001UL},
	{"SHT_SYMTAB",         kELFSectionSymTab},
	{"SHT_STRTAB",         kELFSectionStrTab},
	{"SHT_RELA",           0x00000004UL},
	{"SHT_HASH",           0x00000005UL},
	{"SHT_DYNAMIC",        0x00000006UL},
	{"SHT_NOTE",           0x00000007UL},
	{"SHT_NOBITS",         0x00000008UL},
	{"SHT_REL",            0x00000009UL},
	{"SHT_SHLIB",          0x0000000AUL},
	{"SHT_DYNSYM",         kELFSectionDynSym},
	{"SHT_GNU_ATTRIBUTES", 0x6FFFFFF5UL},
	{"SHT_GNU_HASH",       0x6FFFFFF6UL},
	{"SHT_GNU_LIBLIST",    0x6FFFFFF7UL},
	{"SHT_GNU_VERDEF",     0x6FFFFFFDUL},
	{"SHT_GNU_VERNEED",    0x6FFFFFFEUL},
	{"SHT_GNU_VERSYM",     0x6FFFFFFFUL},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFSECTIONTYPE_H__ */
