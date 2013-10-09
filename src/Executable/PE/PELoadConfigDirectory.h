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

static const SDFElement PELoadConfigDirectory[] =
{
	{"PE Load Config Directory"},
	/* Standard fields */
	{"TimeDateStamp                ", 0, kUTC, 4, 1},
	{"MajorVersion                 ", 0, kUnsigned, 2, 1},
	{"MinorVersion                 ", 0, kUnsigned, 2, 1},
	{"GlobalFlagsClear             ", 0, kUnsigned, 4, 1},
	{"GlobalFlagsSet               ", 0, kUnsigned, 4, 1},
	{"CriticalSectionDefaultTimeout", 0, kUnsigned, 4, 1},
	{"DeCommitFreeBlockThreshold   ", 0, kUnsigned, 4, 1},
	{"DeCommitTotalFreeThreshold   ", 0, kUnsigned, 4, 1},
	{"LockPrefixTable              ", 0, kUnsigned, 4, 1},
	{"MaximumAllocationSize        ", 0, kUnsigned, 4, 1},
	{"VirtualMemoryThreshold       ", 0, kUnsigned, 4, 1},
	{"ProcessHeapFlags             ", 0, kUnsigned, 4, 1},
	{"ProcessAffinityMask          ", 0, kUnsigned, 4, 1},
	{"CSDVersion                   ", 0, kUnsigned, 2, 1},
	{"Reserved                     ", 0, kReserved, 2, 1},
	{"EditList                     ", 0, kUnsigned, 4, 1},
	{"SecurityCookie               ", 0, kUnsigned, 4, 1},
	{"SEHandlerTable               ", 0, kUnsigned, 4, 1},
	{"SEHandlerCount               ", 0, kUnsigned, 4, 1},
};
static const uint32_t PELoadConfigDirectorySize = sizeof(PELoadConfigDirectory) / sizeof(PELoadConfigDirectory[0]);

#endif /* __PELOADCONFIGDIRECTORY_H__ */
