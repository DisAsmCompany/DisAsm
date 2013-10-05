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

typedef struct PEExportDirectory_t 
{
	uint32_t Characteristics;
	uint32_t TimeDateStamp;
	uint16_t MajorVersion;
	uint16_t MinorVersion;
	uint32_t Name;
	uint32_t Base;
	uint32_t NumberOfFunctions;
	uint32_t NumberOfNames;
	uint32_t AddressOfFunctions;     /* RVA from base of image */
	uint32_t AddressOfNames;         /* RVA from base of image */
	uint32_t AddressOfNameOrdinals;  /* RVA from base of image */
}
PEExportDirectory;

#endif /* __PEEXPORTDIRECTORY_H__ */
