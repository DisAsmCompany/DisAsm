/*
 * Filename: MachOSegment64.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Segment 64 (Load Command)
 *
 *              
 *
 */

#pragma once
#ifndef __MACHOSEGMENT64_H__
#define __MACHOSEGMENT64_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kMachOSegment64NumberOfSections = 56 };

static const SDFElement MachOSegment64[] =
{
	{"Mach-O Segment"},
	{"Name            ", kStringASCII, 16, 1},
	{"VirtualAddress  ", kUnsigned, 8, 1},
	{"VirtualSize     ", kUnsigned, 8, 1},
	{"FileOffset      ", kUnsigned, 8, 1},
	{"FileSize        ", kUnsigned, 8, 1},
	{"ProtectionMax   ", kUnsigned, 4, 1, MachOMemoryProtection},
	{"ProtectionInit  ", kUnsigned, 4, 1, MachOMemoryProtection},
	{"NumberOfSections", kUnsigned, 4, 1},
	{"Flags           ", kUnsigned, 4, 1, MachOSegmentAttributes},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSEGMENT64_H__ */
