/*
* Filename: NESegmentedHeader.h
* Author:   DisAsmCompany
* Date:     26/10/2013
*
* Description: NE Segmented Header
*
*              
*
*/

#pragma once
#ifndef __NESEGMENTEDHEADER_H__
#define __NESEGMENTEDHEADER_H__

enum { kNESignature = 0x454E }; /* NE */

enum { NESegmentedHeaderEntryTableOffset            = 0x02 };
enum { NESegmentedHeaderResidentNamesTableOffset    = 0x24 };
enum { NESegmentedHeaderNonResidentNamesTableOffset = 0x2A };

static const SDFElement NESegmentedHeader[] =
{
	{"NE Segmented Header"},
	{"Linker Version                 ", kUnsigned, 1, 1},
	{"Linker Revision                ", kUnsigned, 1, 1},
	{"Entry Table Offset             ", kUnsigned, 2, 1},
	{"Entry Table Size               ", kUnsigned, 2, 1},
	{"CRC                            ", kUnsigned, 4, 1},
	{"Flags                          ", kUnsigned, 2, 1},
	{"Segment Number                 ", kUnsigned, 2, 1},
	{"Initial Heap Size              ", kUnsigned, 2, 1},
	{"Initial Stack Size             ", kUnsigned, 2, 1},
	{"CS:IP                          ", kUnsigned, 4, 1},
	{"SS:SP                          ", kUnsigned, 4, 1},
	{"Segment Table Count            ", kUnsigned, 2, 1},
	{"Module Reference Table Count   ", kUnsigned, 2, 1},
	{"Non-Resident Names Table Size  ", kUnsigned, 2, 1},
	{"Segment Table Offset           ", kUnsigned, 2, 1},
	{"Resource Table Offset          ", kUnsigned, 2, 1},
	{"Resident Name Table Offset     ", kUnsigned, 2, 1},
	{"Module Reference Table Offset  ", kUnsigned, 2, 1},
	{"Imported Names Table Offset    ", kUnsigned, 2, 1},
	{"Non-Resident Names Table Offset", kUnsigned, 4, 1},
	{"Number Of Movable Entries      ", kUnsigned, 2, 1},
	{"Logical Sector Alignment Shift ", kUnsigned, 2, 1},
	{"Number Of Resource Entries     ", kUnsigned, 2, 1},
	{"Executable Type                ", kUnsigned, 1, 1},
	{"Reserved                       ", kReserved, 1, 9},
	{NULL}
};
#endif /* __NESEGMENTEDHEADER_H__ */
