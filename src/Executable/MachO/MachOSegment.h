/*
 * Filename: MachOSegment.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Segment (Load Command)
 *)
 *              
 *
 */

#pragma once
#ifndef __MACHOSEGMENT_H__
#define __MACHOSEGMENT_H__

#define MachOSegmentNumberOfSections 1

static const SDFElement MachOSegment[] =
{
	{"Mach-O Segment"},
	{"Name            ", 0, kStringASCII, 16, 1},
	{"VirtualAddress  ", 0, kUnsigned, 4, 1},
	{"VirtualSize     ", 0, kUnsigned, 4, 1},
	{"FileOffset      ", 0, kUnsigned, 4, 1},
	{"FileSize        ", 0, kUnsigned, 4, 1},
	{"ProtectionMax   ", 0, kUnsigned, 4, 1},
	{"ProtectionInit  ", 0, kUnsigned, 4, 1},
	{"NumberOfSections", MachOSegmentNumberOfSections, kUnsigned, 4, 1},
	{"Flags           ", 0, kUnsigned, 4, 1},
};
static const uint32_t MachOSegmentSize = sizeof(MachOSegment) / sizeof(MachOSegment[0]);

#endif /* __MACHOSEGMENT_H__ */
