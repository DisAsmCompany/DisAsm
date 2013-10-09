/*
* Filename: PEExportDirectory.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Export Directory structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEEXPORTDIRECTORY_H__
#define __PEEXPORTDIRECTORY_H__

#define PEExportDirectoryNumberOfFunctions 1
#define PEExportDirectoryAddressOfFunctions 2
#define PEExportDirectoryAddressOfNames 3
#define PEExportDirectoryAddressOfNameOrdinals 4

static const SDFElement PEExportDirectory[] =
{
	{"PE Export Directory"},
	{"Characteristics      ", 0, kUnsigned, 4, 1},
	{"TimeDateStamp        ", 0, kUTC, 4, 1},
	{"MajorVersion         ", 0, kUnsigned, 2, 1},
	{"MinorVersion         ", 0, kUnsigned, 2, 1},
	{"Name                 ", 0, kUnsigned, 4, 1},
	{"Base                 ", 0, kUnsigned, 4, 1},
	{"NumberOfFunctions    ", PEExportDirectoryNumberOfFunctions, kUnsigned, 4, 1},
	{"NumberOfNames        ", 0, kUnsigned, 4, 1},
	{"AddressOfFunctions   ", PEExportDirectoryAddressOfFunctions, kUnsigned, 4, 1},
	{"AddressOfNames       ", PEExportDirectoryAddressOfNames, kUnsigned, 4, 1},
	{"AddressOfNameOrdinals", PEExportDirectoryAddressOfNameOrdinals, kUnsigned, 4, 1},
};
static const uint32_t PEExportDirectorySize = sizeof(PEExportDirectory) / sizeof(PEExportDirectory[0]);

#endif /* __PEEXPORTDIRECTORY_H__ */
