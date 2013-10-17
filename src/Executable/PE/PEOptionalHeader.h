/*
* Filename: PEOPtionalHeaders.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Optional Headers structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEOPTIONALHEADER_H__
#define __PEOPTIONALHEADER_H__

static const uint32_t PEOptionalHeaderMagic               = 0;
static const uint32_t PEOptionalHeaderAddressOfEntryPoint = 16;
static const uint32_t PEOptionalHeaderNumberOfRvaAndSizes = 220;

static const SDFElement PEOptionalHeader[] =
{
	{"PE Optional Header"},
	/* Standard fields */
	{"Magic                      ", kUnsigned, 2, 1, _PEMagic},
	{"MajorLinkerVersion         ", kUnsigned, 1, 1},
	{"MinorLinkerVersion         ", kUnsigned, 1, 1},
	{"SizeOfCode                 ", kUnsigned, 4, 1},
	{"SizeOfInitializedData      ", kUnsigned, 4, 1},
	{"SizeOfUninitializedData    ", kUnsigned, 4, 1},
	{"AddressOfEntryPoint        ", kUnsigned, 4, 1},
	{"BaseOfCode                 ", kUnsigned, 4, 1},
	{"BaseOfData                 ", kUnsigned, 4, 1},
	/* NT additional fields */
	{"ImageBase                  ", kUnsigned, 4, 1},
	{"SectionAlignment           ", kUnsigned, 4, 1},
	{"FileAlignment              ", kUnsigned, 4, 1},
	{"MajorOperatingSystemVersion", kUnsigned, 2, 1},
	{"MinorOperatingSystemVersion", kUnsigned, 2, 1},
	{"MajorImageVersion          ", kUnsigned, 2, 1},
	{"MinorImageVersion          ", kUnsigned, 2, 1},
	{"MajorSubsystemVersion      ", kUnsigned, 2, 1},
	{"MinorSubsystemVersion      ", kUnsigned, 2, 1},
	{"Win32VersionValue          ", kUnsigned, 4, 1},
	{"SizeOfImage                ", kUnsigned, 4, 1},
	{"SizeOfHeaders              ", kUnsigned, 4, 1},
	{"CheckSum                   ", kUnsigned, 4, 1},
	{"Subsystem                  ", kUnsigned, 2, 1, PESubsystem},
	{"DllCharacteristics         ", kUnsigned, 2, 1, PEDllCharacteristics},
	{"SizeOfStackReserve         ", kUnsigned, 4, 1},
	{"SizeOfStackCommit          ", kUnsigned, 4, 1},
	{"MajorSubsystemVersion      ", kUnsigned, 4, 1},
	{"MinorSubsystemVersion      ", kUnsigned, 4, 1},
	{"LoaderFlags                ", kUnsigned, 4, 1},
	{"NumberOfRvaAndSizes        ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __PEOPTIONALHEADER_H__ */
