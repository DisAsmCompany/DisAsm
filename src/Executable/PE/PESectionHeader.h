/*
* Filename: PESectionHeader.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Section Headers structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PESECTIONHEADER_H__
#define __PESECTIONHEADER_H__

enum { PESectionHeaderVirtualAddress   = 12 };
enum { PESectionHeaderSizeOfRawData    = 16 };
enum { PESectionHeaderPointerToRawData = 20 };

static const SDFElement PESectionHeader[] =
{
	{"PE Section Header"},
	{"Name                ", kStringASCII, 8, 1},
	{"PhysicalAddress     ", kUnsigned, 4, 1},
	{"VirtualAddress      ", kUnsigned, 4, 1},
	{"SizeOfRawData       ", kUnsigned, 4, 1},
	{"PointerToRawData    ", kUnsigned, 4, 1},
	{"PointerToRelocations", kUnsigned, 4, 1},
	{"PointerToLinenumbers", kUnsigned, 4, 1},
	{"NumberOfRelocations ", kUnsigned, 2, 1},
	{"NumberOfLinenumbers ", kUnsigned, 2, 1},
	{"Characteristics     ", kUnsigned, 4, 1, PESectionCharacteristics},
	{NULL}
};

#endif /* __PESECTIONHEADER_H__ */
