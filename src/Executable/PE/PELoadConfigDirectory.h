/*
* Filename: PELoadConfigDirectory.h
* Author:   DisAsmCompany
* Date:     29/09/2013
*
* Description: Load Config Directory structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PELOADCONFIGDIRECTORY_H__
#define __PELOADCONFIGDIRECTORY_H__

typedef struct PELoadConfigDirectory_t 
{
	uint32_t Size;
	uint32_t TimeDateStamp;
	uint16_t MajorVersion;
	uint16_t MinorVersion;
	uint32_t GlobalFlagsClear;
	uint32_t GlobalFlagsSet;
	uint32_t CriticalSectionDefaultTimeout;
	uint32_t DeCommitFreeBlockThreshold;
	uint32_t DeCommitTotalFreeThreshold;
	uint32_t LockPrefixTable;
	uint32_t MaximumAllocationSize;
	uint32_t VirtualMemoryThreshold;
	uint32_t ProcessHeapFlags;
	uint32_t ProcessAffinityMask;
	uint16_t CSDVersion;
	uint16_t Reserved;
	uint32_t EditList;
	uint32_t SecurityCookie;
	uint32_t SEHandlerTable;
	uint32_t SEHandlerCount;
}
PELoadConfigDirectory;

#endif /* __PELOADCONFIGDIRECTORY_H__ */
