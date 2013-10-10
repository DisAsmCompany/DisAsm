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


#define PESectionHeaderVirtualAddress   1
#define PESectionHeaderSizeOfRawData    2
#define PESectionHeaderPointerToRawData 3

static const SDFElement PESectionHeader[] =
{
	{"PE Section Header"},
	{"Name                ", 0, kStringASCII, 8, 1},
	{"PhysicalAddress     ", 0, kUnsigned, 4, 1},
	{"VirtualAddress      ", PESectionHeaderVirtualAddress, kUnsigned, 4, 1},
	{"SizeOfRawData       ", PESectionHeaderSizeOfRawData, kUnsigned, 4, 1},
	{"PointerToRawData    ", PESectionHeaderPointerToRawData, kUnsigned, 4, 1},
	{"PointerToRelocations", 0, kUnsigned, 4, 1},
	{"PointerToLinenumbers", 0, kUnsigned, 4, 1},
	{"NumberOfRelocations ", 0, kUnsigned, 2, 1},
	{"NumberOfLinenumbers ", 0, kUnsigned, 2, 1},
	{"Characteristics     ", 0, kUnsigned, 4, 1},
};
static const uint32_t PESectionHeaderSize = sizeof(PESectionHeader) / sizeof(PESectionHeader[0]);

#endif /* __PESECTIONHEADER_H__ */
