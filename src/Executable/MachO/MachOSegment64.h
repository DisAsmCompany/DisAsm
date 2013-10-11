/*
 * Filename: MachOSegment64.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Segment 64 (Load Command)
 *)
 *              
 *
 */

#pragma once
#ifndef __MACHOSEGMENT64_H__
#define __MACHOSEGMENT64_H__

#define MachOSegment64NumberOfSections 1

static const SDFElement MachOSegment64[] =
{
	{"Mach-O Segment"},
	{"Name            ", 0, kStringASCII, 16, 1},
	{"VirtualAddress  ", 0, kUnsigned, 8, 1},
	{"VirtualSize     ", 0, kUnsigned, 8, 1},
	{"FileOffset      ", 0, kUnsigned, 8, 1},
	{"FileSize        ", 0, kUnsigned, 8, 1},
	{"ProtectionMax   ", 0, kUnsigned, 4, 1},
	{"ProtectionInit  ", 0, kUnsigned, 4, 1},
	{"NumberOfSections", MachOSegment64NumberOfSections, kUnsigned, 4, 1},
	{"Flags           ", 0, kUnsigned, 4, 1},
};
static const uint32_t MachOSegment64Size = sizeof(MachOSegment64) / sizeof(MachOSegment64[0]);

#endif /* __MACHOSEGMENT64_H__ */
