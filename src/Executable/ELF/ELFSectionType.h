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

static const SDFEnum ELFSectionType[] =
{
	{"SHT_NULL",           0x00000000UL},
	{"SHT_PROGBITS",       0x00000001UL},
	{"SHT_SYMTAB",         0x00000002UL},
	{"SHT_STRTAB",         0x00000003UL},
	{"SHT_RELA",           0x00000004UL},
	{"SHT_HASH",           0x00000005UL},
	{"SHT_DYNAMIC",        0x00000006UL},
	{"SHT_NOTE",           0x00000007UL},
	{"SHT_NOBITS",         0x00000008UL},
	{"SHT_REL",            0x00000009UL},
	{"SHT_SHLIB",          0x0000000AUL},
	{"SHT_DYNSYM",         0x0000000BUL},
	{"SHT_GNU_ATTRIBUTES", 0x6FFFFFF5UL},
	{"SHT_GNU_HASH",       0x6FFFFFF6UL},
	{"SHT_GNU_LIBLIST",    0x6FFFFFF7UL},
	{"SHT_GNU_VERDEF",     0x6FFFFFFDUL},
	{"SHT_GNU_VERNEED",    0x6FFFFFFEUL},
	{"SHT_GNU_VERSYM",     0x6FFFFFFFUL},
	{NULL}
};

#endif /* __ELFSECTIONTYPE_H__ */
