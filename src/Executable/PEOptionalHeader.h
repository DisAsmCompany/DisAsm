/*
* Filename: PEOPtionalHeaders.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Optional Headers structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEOPTIONALHEADER_H__
#define __PEOPTIONALHEADER_H__

typedef struct PEOptionalHeader_t
{
	/* Standard fields */
	uint16_t Magic;
	uint8_t  MajorLinkerVersion;
	uint8_t  MinorLinkerVersion;
	uint32_t SizeOfCode;
	uint32_t SizeOfInitializedData;
	uint32_t SizeOfUninitializedData;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode;
	uint32_t BaseOfData;
	/* NT additional fields */
	uint32_t ImageBase;
	uint32_t SectionAlignment;
	uint32_t FileAlignment;
	uint16_t MajorOperatingSystemVersion;
	uint16_t MinorOperatingSystemVersion;
	uint16_t MajorImageVersion;
	uint16_t MinorImageVersion;
	uint16_t MajorSubsystemVersion;
	uint16_t MinorSubsystemVersion;
	uint32_t Win32VersionValue;
	uint32_t SizeOfImage;
	uint32_t SizeOfHeaders;
	uint32_t CheckSum;
	uint16_t Subsystem;
	uint16_t DllCharacteristics;
	uint32_t SizeOfStackReserve;
	uint32_t SizeOfStackCommit;
	uint32_t SizeOfHeapReserve;
	uint32_t SizeOfHeapCommit;
	uint32_t LoaderFlags;
	uint32_t NumberOfRvaAndSizes;
	PEDataDirectory DataDirectory[PEDataDirectoryCount];
}
PEOptionalHeader;

#endif /* __PEOPTIONALHEADER_H__ */
