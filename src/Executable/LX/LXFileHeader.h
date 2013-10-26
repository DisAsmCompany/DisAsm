/*
* Filename: LXFileHeader.h
* Author:   DisAsmCompany
* Date:     26/10/2013
*
* Description: LX/LE File Header
* 
*
*
*/

#pragma once
#ifndef __LXFILEHEADER_H__
#define __LXFILEHEADER_H__

static const uint16_t kLESignature = 0x454C; /* LE */
static const uint16_t kLXSignature = 0x584C; /* LX */

static const uint32_t LXFileHeaderObjectEIP         = 0x16;
static const uint32_t LXFileHeaderObjectEIPObject   = 0x1A;
static const uint32_t LXFileHeaderObjectTableOffset = 0x3E;
static const uint32_t LXFileHeaderObjectTableCount  = 0x42;

static const SDFElement LXFileHeader[] =
{
	{"LX File Header"},
	{"Byte Ordering                     ", kUnsigned, 1, 1, LXOrdering},
	{"Word Ordering                     ", kUnsigned, 1, 1, LXOrdering},
	{"Format Level                      ", kUnsigned, 4, 1},
	{"CPU Type                          ", kUnsigned, 2, 1, LXCPUType},
	{"OS Type                           ", kUnsigned, 2, 1, LXOSType},
	{"Module Version                    ", kUnsigned, 4, 1},
	{"Module Flags                      ", kUnsigned, 4, 1},
	{"Module Pages                      ", kUnsigned, 4, 1},
	{"EIP Object                        ", kUnsigned, 4, 1},
	{"EIP                               ", kUnsigned, 4, 1},
	{"ESP Object                        ", kUnsigned, 4, 1},
	{"ESP                               ", kUnsigned, 4, 1},
	{"Page Size                         ", kUnsigned, 4, 1},
	{"Page Offset Shift                 ", kUnsigned, 4, 1},
	{"Fixup Section Size                ", kUnsigned, 4, 1},
	{"Fixup Section Checksum            ", kUnsigned, 4, 1},
	{"Loader Section Size               ", kUnsigned, 4, 1},
	{"Loader Section Checksum           ", kUnsigned, 4, 1},
	{"Object Table Offset               ", kUnsigned, 4, 1},
	{"Object Table Count                ", kUnsigned, 4, 1},
	{"Object Page Table Offset          ", kUnsigned, 4, 1},
	{"Object Iterated Pages Offset      ", kUnsigned, 4, 1},
	{"Resource Table Offset             ", kUnsigned, 4, 1},
	{"Resource Table Count              ", kUnsigned, 4, 1},
	{"Resident Name Table Offset        ", kUnsigned, 4, 1},
	{"Entry Table Offset                ", kUnsigned, 4, 1},
	{"Module Directives Offset          ", kUnsigned, 4, 1},
	{"Module Directives Count           ", kUnsigned, 4, 1},
	{"Fixup Page Table Offset           ", kUnsigned, 4, 1},
	{"Fixup Record Table Offset         ", kUnsigned, 4, 1},
	{"Import Module Table Offset        ", kUnsigned, 4, 1},
	{"Import Module Table Count         ", kUnsigned, 4, 1},
	{"Import Procedure Name Table Offset", kUnsigned, 4, 1},
	{"Per-Page Checksum Offset          ", kUnsigned, 4, 1},
	{"Data Pages Offset                 ", kUnsigned, 4, 1},
	{"Preload Pages                     ", kUnsigned, 4, 1},
	{"Non-Resident Name Table Offset    ", kUnsigned, 4, 1},
	{"Non-Resident Name Table Length    ", kUnsigned, 4, 1},
	{"Non-Resident Name Table Checksum  ", kUnsigned, 4, 1},
	{"Auto Data Segment Object Number   ", kUnsigned, 4, 1},
	{"Debug Info Offset                 ", kUnsigned, 4, 1},
	{"Debug Info Length                 ", kUnsigned, 4, 1},
	{"Instance Preload                  ", kUnsigned, 4, 1},
	{"Instance Demand                   ", kUnsigned, 4, 1},
	{"Heap Size                         ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __LXFILEHEADER_H__ */
