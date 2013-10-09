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

#ifndef PENTSignature
#define PENTSignature 0x00004550 /* PE */
#endif /* PENTSignature */

#define PEFileHeaderNumberOfSections 1
#define PEFileHeaderSizeOfOptionalHeader 2

static const SDFElement PEFileHeader[] =
{
	{"PE File Header"},
	{"Machine             ", 0, kUnsigned, 2, 1},
	{"NumberOfSections    ", PEFileHeaderNumberOfSections, kUnsigned, 2, 1},
	{"TimeDateStamp       ", 0, kUTC, 4, 1},
	{"PointerToSymbolTable", 0, kUnsigned, 4, 1},
	{"NumberOfSymbols     ", 0, kUnsigned, 4, 1},
	{"SizeOfOptionalHeader", PEFileHeaderSizeOfOptionalHeader, kUnsigned, 2, 1},
	{"Characteristics     ", 0, kUnsigned, 2, 1},
};
static const uint32_t PEFileHeaderSize = sizeof(PEFileHeader) / sizeof(PEFileHeader[0]);

#endif /* __PEFILEHEADER_H__ */
