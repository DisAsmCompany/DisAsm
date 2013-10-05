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

typedef struct PESectionHeader_t
{
	uint8_t  Name[8];
	/*union {
		uint32_t   PhysicalAddress;
		uint32_t   VirtualSize;
	} Misc;*/
	uint32_t PhysicalAddress;
	uint32_t VirtualAddress;
	uint32_t SizeOfRawData;
	uint32_t PointerToRawData;
	uint32_t PointerToRelocations;
	uint32_t PointerToLinenumbers;
	uint16_t NumberOfRelocations;
	uint16_t NumberOfLinenumbers;
	uint32_t Characteristics;
}
PESectionHeader;

#endif /* __PESECTIONHEADER_H__ */
