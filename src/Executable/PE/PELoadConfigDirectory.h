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
	{"TimeDateStamp                ", kUTC, 4, 1},
	{"MajorVersion                 ", kUnsigned, 2, 1},
	{"MinorVersion                 ", kUnsigned, 2, 1},
	{"GlobalFlagsClear             ", kUnsigned, 4, 1},
	{"GlobalFlagsSet               ", kUnsigned, 4, 1},
	{"CriticalSectionDefaultTimeout", kUnsigned, 4, 1},
	{"DeCommitFreeBlockThreshold   ", kUnsigned, 4, 1},
	{"DeCommitTotalFreeThreshold   ", kUnsigned, 4, 1},
	{"LockPrefixTable              ", kUnsigned, 4, 1},
	{"MaximumAllocationSize        ", kUnsigned, 4, 1},
	{"VirtualMemoryThreshold       ", kUnsigned, 4, 1},
	{"ProcessHeapFlags             ", kUnsigned, 4, 1},
	{"ProcessAffinityMask          ", kUnsigned, 4, 1},
	{"CSDVersion                   ", kUnsigned, 2, 1},
	{"Reserved                     ", kReserved, 2, 1},
	{"EditList                     ", kUnsigned, 4, 1},
	{"SecurityCookie               ", kUnsigned, 4, 1},
	{"SEHandlerTable               ", kUnsigned, 4, 1},
	{"SEHandlerCount               ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __PELOADCONFIGDIRECTORY_H__ */
