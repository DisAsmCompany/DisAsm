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

static const uint32_t kPENTSignature = 0x00004550; /* PE */

static const uint32_t PEFileHeaderSignature = 0;
static const uint32_t PEFileHeaderMachine = 4;
static const uint32_t PEFileHeaderNumberOfSections = 6;
static const uint32_t PEFileHeaderSizeOfOptionalHeader = 20;

static const SDFElement PEFileHeader[] =
{
	{"PE File Header"},
	{"Signature           ", kSignature, 4, 1},
	{"Machine             ", kUnsigned, 2, 1, PEMachine},
	{"NumberOfSections    ", kUnsigned, 2, 1},
	{"TimeDateStamp       ", kUTC, 4, 1},
	{"PointerToSymbolTable", kUnsigned, 4, 1},
	{"NumberOfSymbols     ", kUnsigned, 4, 1},
	{"SizeOfOptionalHeader", kUnsigned, 2, 1},
	{"Characteristics     ", kUnsigned, 2, 1, PECharacteristics},
	{NULL}
};

#endif /* __PEFILEHEADER_H__ */
