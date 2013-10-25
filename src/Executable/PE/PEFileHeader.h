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

static const uint32_t PEFileHeaderMachine              = 0;
static const uint32_t PEFileHeaderNumberOfSections     = 2;
static const uint32_t PEFileHeaderPointerToSymbolTable = 8;
static const uint32_t PEFileHeaderNumberOfSymbols      = 12;
static const uint32_t PEFileHeaderSizeOfOptionalHeader = 16;

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

#endif /* __PEFILEHEADER_H__ */
