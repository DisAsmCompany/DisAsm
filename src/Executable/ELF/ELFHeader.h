/*
 * Filename: ELFHeader.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFHEADER_H__
#define __ELFHEADER_H__

static const uint32_t kELFMagic = 0x464C457FUL;

static const uint32_t ELFHeaderAddressOfEntryPoint = 24;
static const uint32_t ELFHeaderOffsetSections      = 32;
static const uint32_t ELFHeaderOffsetPrograms      = 28;
static const uint32_t ELFHeaderSizeOfProgram       = 42;
static const uint32_t ELFHeaderNumberOfPrograms    = 44;
static const uint32_t ELFHeaderSizeOfSection       = 46;
static const uint32_t ELFHeaderNumberOfSections    = 50;

static const SDFElement ELFHeader[] =
{
	{"ELF Header"},
	{"Magic                    ", kSignature, 4, 1},
	{"Class                    ", kUnsigned, 1, 1, ELFClass},
	{"Data                     ", kUnsigned, 1, 1, ELFData},
	{"Version                  ", kUnsigned, 1, 1, ELFVersion},
	{"Padding                  ", kReserved, 1, 9},
	{"Type                     ", kUnsigned, 2, 1, ELFType},
	{"Machine                  ", kUnsigned, 2, 1, ELFMachine},
	{"Version                  ", kUnsigned, 4, 1, ELFVersion},
	{"Address Of Entry Point   ", kUnsigned, 4, 1},
	{"Offset Program Header    ", kUnsigned, 4, 1},
	{"Offset Section Header    ", kUnsigned, 4, 1},
	{"Flags                    ", kUnsigned, 4, 1},
	{"ELF Header Size          ", kUnsigned, 2, 1},
	{"Program Header Size      ", kUnsigned, 2, 1},
	{"Number OF Program Headers", kUnsigned, 2, 1},
	{"Section Header Size      ", kUnsigned, 2, 1},
	{"Number OF Section Headers", kUnsigned, 2, 1},
	{"Section Header Index     ", kUnsigned, 2, 1},
	{NULL}
};

#endif /* __ELFHEADER_H__ */
