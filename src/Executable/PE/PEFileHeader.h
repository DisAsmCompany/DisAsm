/*
* Filename: PEFileHeader.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: File Header structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEFILEHEADER_H__
#define __PEFILEHEADER_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kPESignature = 0x00004550UL }; /* PE */

enum { PEFileHeaderMachine              = 0  };
enum { PEFileHeaderNumberOfSections     = 2  };
enum { PEFileHeaderPointerToSymbolTable = 8  };
enum { PEFileHeaderNumberOfSymbols      = 12 };
enum { PEFileHeaderSizeOfOptionalHeader = 16 };

static const SDFElement PEFileHeader[] =
{
	{"PE File Header"},
	{"Machine             ", kUnsigned, 2, 1, _PEMachine},
	{"NumberOfSections    ", kUnsigned, 2, 1},
	{"TimeDateStamp       ", kUTC, 4, 1},
	{"PointerToSymbolTable", kUnsigned, 4, 1},
	{"NumberOfSymbols     ", kUnsigned, 4, 1},
	{"SizeOfOptionalHeader", kUnsigned, 2, 1},
	{"Characteristics     ", kUnsigned, 2, 1, PECharacteristics},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEFILEHEADER_H__ */
