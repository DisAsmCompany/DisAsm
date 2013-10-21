/*
 * Filename: MachOSegment.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Segment (Load Command)
 *
 *              
 *
 */

#pragma once
#ifndef __MACHOSEGMENT_H__
#define __MACHOSEGMENT_H__

static const uint32_t kMachOSegmentNumberOfSections = 40;

static const SDFElement MachOSegment[] =
{
	{"Mach-O Segment"},
	{"Name            ", kStringASCII, 16, 1},
	{"VirtualAddress  ", kUnsigned, 4, 1},
	{"VirtualSize     ", kUnsigned, 4, 1},
	{"FileOffset      ", kUnsigned, 4, 1},
	{"FileSize        ", kUnsigned, 4, 1},
	{"ProtectionMax   ", kUnsigned, 4, 1, MachOMemoryProtection},
	{"ProtectionInit  ", kUnsigned, 4, 1, MachOMemoryProtection},
	{"NumberOfSections", kUnsigned, 4, 1},
	{"Flags           ", kUnsigned, 4, 1, MachOSegmentAttributes},
	{NULL}
};

#endif /* __MACHOSEGMENT_H__ */
