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
#ifndef __ELFSECTIONTYPE_H__FA1A44DE_BD8E_4A1A_AFDA_7906771011E3__
#define __ELFSECTIONTYPE_H__FA1A44DE_BD8E_4A1A_AFDA_7906771011E3__

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
	{"SHT_NULL",           0x00000000UL, 0},
	{"SHT_PROGBITS",       0x00000001UL, 0},
	{"SHT_SYMTAB",         kELFSectionSymTab, 0},
	{"SHT_STRTAB",         kELFSectionStrTab, 0},
	{"SHT_RELA",           0x00000004UL, 0},
	{"SHT_HASH",           0x00000005UL, 0},
	{"SHT_DYNAMIC",        0x00000006UL, 0},
	{"SHT_NOTE",           0x00000007UL, 0},
	{"SHT_NOBITS",         0x00000008UL, 0},
	{"SHT_REL",            0x00000009UL, 0},
	{"SHT_SHLIB",          0x0000000AUL, 0},
	{"SHT_DYNSYM",         kELFSectionDynSym, 0},
	{"SHT_GNU_ATTRIBUTES", 0x6FFFFFF5UL, 0},
	{"SHT_GNU_HASH",       0x6FFFFFF6UL, 0},
	{"SHT_GNU_LIBLIST",    0x6FFFFFF7UL, 0},
	{"SHT_GNU_VERDEF",     0x6FFFFFFDUL, 0},
	{"SHT_GNU_VERNEED",    0x6FFFFFFEUL, 0},
	{"SHT_GNU_VERSYM",     0x6FFFFFFFUL, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFSECTIONTYPE_H__FA1A44DE_BD8E_4A1A_AFDA_7906771011E3__ */
