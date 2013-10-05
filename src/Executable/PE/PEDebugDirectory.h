/*
* Filename: PEDebugDirectory.h
* Author:   DisAsmCompany
* Date:     29/09/2013
*
* Description: Debug Directory structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEDEBUGDIRECTORY_H__
#define __PEDEBUGDIRECTORY_H__

typedef struct PEDebugDirectory_t 
{
	uint32_t Characteristics;
	uint32_t TimeDateStamp;
	uint16_t MajorVersion;
	uint16_t MinorVersion;
	uint32_t Type;
	uint32_t SizeOfData;
	uint32_t AddressOfRawData;
	uint32_t PointerToRawData;
}
PEDebugDirectory;

#endif /* __PEDEBUGDIRECTORY_H__ */
