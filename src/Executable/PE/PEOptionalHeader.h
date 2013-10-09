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

#define PE32Magic  0x010B
#define PE64Magic  0x020B
#define PEROMMagic 0x0107

#define PEOptionalHeaderMagic               1
#define PEOptionalHeaderAddressOfEntryPoint 2
#define PEOptionalHeaderNumberOfRvaAndSizes 3

static const SDFElement PEOptionalHeader[] =
{
	{"PE Optional Header"},
	/* Standard fields */
	{"Magic                      ", PEOptionalHeaderMagic, kUnsigned, 2, 1},
	{"MajorLinkerVersion         ", 0, kUnsigned, 1, 1},
	{"MinorLinkerVersion         ", 0, kUnsigned, 1, 1},
	{"SizeOfCode                 ", 0, kUnsigned, 4, 1},
	{"SizeOfInitializedData      ", 0, kUnsigned, 4, 1},
	{"SizeOfUninitializedData    ", 0, kUnsigned, 4, 1},
	{"AddressOfEntryPoint        ", PEOptionalHeaderAddressOfEntryPoint, kUnsigned, 4, 1},
	{"BaseOfCode                 ", 0, kUnsigned, 4, 1},
	{"BaseOfData                 ", 0, kUnsigned, 4, 1},
	/* NT additional fields */
	{"ImageBase                  ", 0, kUnsigned, 4, 1},
	{"SectionAlignment           ", 0, kUnsigned, 4, 1},
	{"FileAlignment              ", 0, kUnsigned, 4, 1},
	{"MajorOperatingSystemVersion", 0, kUnsigned, 2, 1},
	{"MinorOperatingSystemVersion", 0, kUnsigned, 2, 1},
	{"MajorImageVersion          ", 0, kUnsigned, 2, 1},
	{"MinorImageVersion          ", 0, kUnsigned, 2, 1},
	{"MajorSubsystemVersion      ", 0, kUnsigned, 2, 1},
	{"MinorSubsystemVersion      ", 0, kUnsigned, 2, 1},
	{"Win32VersionValue          ", 0, kUnsigned, 4, 1},
	{"SizeOfImage                ", 0, kUnsigned, 4, 1},
	{"SizeOfHeaders              ", 0, kUnsigned, 4, 1},
	{"CheckSum                   ", 0, kUnsigned, 4, 1},
	{"Subsystem                  ", 0, kUnsigned, 2, 1},
	{"DllCharacteristics         ", 0, kUnsigned, 2, 1},
	{"SizeOfStackReserve         ", 0, kUnsigned, 4, 1},
	{"SizeOfStackCommit          ", 0, kUnsigned, 4, 1},
	{"MajorSubsystemVersion      ", 0, kUnsigned, 4, 1},
	{"MinorSubsystemVersion      ", 0, kUnsigned, 4, 1},
	{"LoaderFlags                ", 0, kUnsigned, 4, 1},
	{"NumberOfRvaAndSizes        ", PEOptionalHeaderNumberOfRvaAndSizes, kUnsigned, 4, 1},
};
static const uint32_t PEOptionalHeaderSize = sizeof(PEOptionalHeader) / sizeof(PEOptionalHeader[0]);

#endif /* __PEOPTIONALHEADER_H__ */
