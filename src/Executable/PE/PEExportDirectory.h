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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PEExportDirectoryNumberOfFunctions     = 20 };
enum { PEExportDirectoryNumberOfNames         = 24 };
enum { PEExportDirectoryAddressOfFunctions    = 28 };
enum { PEExportDirectoryAddressOfNames        = 32 };
enum { PEExportDirectoryAddressOfNameOrdinals = 36 };

static const SDFElement PEExportDirectory[] =
{
	{"PE Export Directory"},
	{"Characteristics      ", kUnsigned, 4, 1},
	{"TimeDateStamp        ", kUTC, 4, 1},
	{"MajorVersion         ", kUnsigned, 2, 1},
	{"MinorVersion         ", kUnsigned, 2, 1},
	{"Name                 ", kUnsigned, 4, 1},
	{"OrdinalBase          ", kUnsigned, 4, 1},
	{"NumberOfFunctions    ", kUnsigned, 4, 1},
	{"NumberOfNames        ", kUnsigned, 4, 1},
	{"AddressOfFunctions   ", kUnsigned, 4, 1},
	{"AddressOfNames       ", kUnsigned, 4, 1},
	{"AddressOfNameOrdinals", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEEXPORTDIRECTORY_H__ */
