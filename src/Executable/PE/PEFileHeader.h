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

#define PEFileHeaderNumberOfSections 2
#define PEFileHeaderSizeOfOptionalHeader 16

static const SDFElement PEFileHeader[] =
{
	{"PE File Header"},
	{"Machine             ", kUnsigned, 2, 1, PEMachine},
	{"NumberOfSections    ", kUnsigned, 2, 1},
	{"TimeDateStamp       ", kUTC, 4, 1},
	{"PointerToSymbolTable", kUnsigned, 4, 1},
	{"NumberOfSymbols     ", kUnsigned, 4, 1},
	{"SizeOfOptionalHeader", kUnsigned, 2, 1},
	{"Characteristics     ", kUnsigned, 2, 1},
	{NULL}
};

#endif /* __PEFILEHEADER_H__ */
