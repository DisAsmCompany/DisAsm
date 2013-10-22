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
	{"SHT_NULL",     0x0000},
	{"SHT_PROGBITS", 0x0001},
	{"SHT_SYMTAB",   0x0002},
	{"SHT_STRTAB",   0x0003},
	{"SHT_RELA",     0x0004},
	{"SHT_HASH",     0x0005},
	{"SHT_DYNAMIC",  0x0006},
	{"SHT_NOTE",     0x0007},
	{"SHT_NOBITS",   0x0008},
	{"SHT_REL",      0x0009},
	{"SHT_SHLIB",    0x000A},
	{"SHT_DYNSYM",   0x000B},
	{NULL}
};

#endif /* __ELFSECTIONTYPE_H__ */
