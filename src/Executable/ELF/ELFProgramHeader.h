/*
 * Filename: ELFProgramHeader.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Program Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFPROGRAMHEADER_H__
#define __ELFPROGRAMHEADER_H__

static const SDFElement ELFProgramHeader[] =
{
	{"ELF Program Header"},
	{"Type            ", kUnsigned, 4, 1, ELFProgramType},
	{"Offset          ", kUnsigned, 4, 1},
	{"Virtual Address ", kUnsigned, 4, 1},
	{"Physical Address", kUnsigned, 4, 1},
	{"Physical Size   ", kUnsigned, 4, 1},
	{"Virtual Size    ", kUnsigned, 4, 1},
	{"Flags           ", kUnsigned, 4, 1, ELFProgramFlags},
	{"Align           ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __ELFPROGRAMHEADER_H__ */
