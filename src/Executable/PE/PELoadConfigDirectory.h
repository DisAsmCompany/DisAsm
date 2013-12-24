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
#ifndef __PELOADCONFIGDIRECTORY_H__20900772_8DCF_4D0D_8760_3D5B89ADB466__
#define __PELOADCONFIGDIRECTORY_H__20900772_8DCF_4D0D_8760_3D5B89ADB466__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

SDFBegin(PELoadConfigDirectory, "PE Load Config Directory"),
{"TimeDateStamp                ", kUTC, 4, 1, NULL},
{"MajorVersion                 ", kUnsigned, 2, 1, NULL},
{"MinorVersion                 ", kUnsigned, 2, 1, NULL},
{"GlobalFlagsClear             ", kUnsigned, 4, 1, NULL},
{"GlobalFlagsSet               ", kUnsigned, 4, 1, NULL},
{"CriticalSectionDefaultTimeout", kUnsigned, 4, 1, NULL},
{"DeCommitFreeBlockThreshold   ", kUnsigned, 4, 1, NULL},
{"DeCommitTotalFreeThreshold   ", kUnsigned, 4, 1, NULL},
{"LockPrefixTable              ", kUnsigned, 4, 1, NULL},
{"MaximumAllocationSize        ", kUnsigned, 4, 1, NULL},
{"VirtualMemoryThreshold       ", kUnsigned, 4, 1, NULL},
{"ProcessHeapFlags             ", kUnsigned, 4, 1, NULL},
{"ProcessAffinityMask          ", kUnsigned, 4, 1, NULL},
{"CSDVersion                   ", kUnsigned, 2, 1, NULL},
{"Reserved                     ", kReserved, 2, 1, NULL},
{"EditList                     ", kUnsigned, 4, 1, NULL},
{"SecurityCookie               ", kUnsigned, 4, 1, NULL},
{"SEHandlerTable               ", kUnsigned, 4, 1, NULL},
{"SEHandlerCount               ", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PELOADCONFIGDIRECTORY_H__20900772_8DCF_4D0D_8760_3D5B89ADB466__ */
