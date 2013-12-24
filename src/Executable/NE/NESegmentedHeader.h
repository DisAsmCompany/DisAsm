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
#ifndef __NESEGMENTEDHEADER_H__9C9953A8_D82A_45E2_BAE5_4376AB937241__
#define __NESEGMENTEDHEADER_H__9C9953A8_D82A_45E2_BAE5_4376AB937241__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kNESignature = 0x454E }; /* NE */

enum { NESegmentedHeaderEntryTableOffset            = 0x02 };
enum { NESegmentedHeaderResidentNamesTableOffset    = 0x24 };
enum { NESegmentedHeaderNonResidentNamesTableOffset = 0x2A };

SDFBegin(NESegmentedHeader, "NE Segmented Header"),
{"Linker Version                 ", kUnsigned, 1, 1, NULL},
{"Linker Revision                ", kUnsigned, 1, 1, NULL},
{"Entry Table Offset             ", kUnsigned, 2, 1, NULL},
{"Entry Table Size               ", kUnsigned, 2, 1, NULL},
{"CRC                            ", kUnsigned, 4, 1, NULL},
{"Flags                          ", kUnsigned, 2, 1, NULL},
{"Segment Number                 ", kUnsigned, 2, 1, NULL},
{"Initial Heap Size              ", kUnsigned, 2, 1, NULL},
{"Initial Stack Size             ", kUnsigned, 2, 1, NULL},
{"CS:IP                          ", kUnsigned, 4, 1, NULL},
{"SS:SP                          ", kUnsigned, 4, 1, NULL},
{"Segment Table Count            ", kUnsigned, 2, 1, NULL},
{"Module Reference Table Count   ", kUnsigned, 2, 1, NULL},
{"Non-Resident Names Table Size  ", kUnsigned, 2, 1, NULL},
{"Segment Table Offset           ", kUnsigned, 2, 1, NULL},
{"Resource Table Offset          ", kUnsigned, 2, 1, NULL},
{"Resident Name Table Offset     ", kUnsigned, 2, 1, NULL},
{"Module Reference Table Offset  ", kUnsigned, 2, 1, NULL},
{"Imported Names Table Offset    ", kUnsigned, 2, 1, NULL},
{"Non-Resident Names Table Offset", kUnsigned, 4, 1, NULL},
{"Number Of Movable Entries      ", kUnsigned, 2, 1, NULL},
{"Logical Sector Alignment Shift ", kUnsigned, 2, 1, NULL},
{"Number Of Resource Entries     ", kUnsigned, 2, 1, NULL},
{"Executable Type                ", kUnsigned, 1, 1, NULL},
{"Reserved                       ", kReserved, 1, 9, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __NESEGMENTEDHEADER_H__9C9953A8_D82A_45E2_BAE5_4376AB937241__ */
