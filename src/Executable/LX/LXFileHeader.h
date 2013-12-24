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
#ifndef __LXFILEHEADER_H__3887EC12_ECA8_4630_B46B_3585C839A510__
#define __LXFILEHEADER_H__3887EC12_ECA8_4630_B46B_3585C839A510__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kLESignature = 0x454C }; /* LE */
enum { kLXSignature = 0x584C }; /* LX */

enum { LXFileHeaderObjectEIP         = 0x16 };
enum { LXFileHeaderObjectEIPObject   = 0x1A };
enum { LXFileHeaderObjectTableOffset = 0x3E };
enum { LXFileHeaderObjectTableCount  = 0x42 };

SDFBegin(LXFileHeader, "LX File Header"),
{"Byte Ordering                     ", kUnsigned, 1, 1, LXOrdering},
{"Word Ordering                     ", kUnsigned, 1, 1, LXOrdering},
{"Format Level                      ", kUnsigned, 4, 1, NULL},
{"CPU Type                          ", kUnsigned, 2, 1, LXCPUType},
{"OS Type                           ", kUnsigned, 2, 1, LXOSType},
{"Module Version                    ", kUnsigned, 4, 1, NULL},
{"Module Flags                      ", kUnsigned, 4, 1, NULL},
{"Module Pages                      ", kUnsigned, 4, 1, NULL},
{"EIP Object                        ", kUnsigned, 4, 1, NULL},
{"EIP                               ", kUnsigned, 4, 1, NULL},
{"ESP Object                        ", kUnsigned, 4, 1, NULL},
{"ESP                               ", kUnsigned, 4, 1, NULL},
{"Page Size                         ", kUnsigned, 4, 1, NULL},
{"Page Offset Shift                 ", kUnsigned, 4, 1, NULL},
{"Fixup Section Size                ", kUnsigned, 4, 1, NULL},
{"Fixup Section Checksum            ", kUnsigned, 4, 1, NULL},
{"Loader Section Size               ", kUnsigned, 4, 1, NULL},
{"Loader Section Checksum           ", kUnsigned, 4, 1, NULL},
{"Object Table Offset               ", kUnsigned, 4, 1, NULL},
{"Object Table Count                ", kUnsigned, 4, 1, NULL},
{"Object Page Table Offset          ", kUnsigned, 4, 1, NULL},
{"Object Iterated Pages Offset      ", kUnsigned, 4, 1, NULL},
{"Resource Table Offset             ", kUnsigned, 4, 1, NULL},
{"Resource Table Count              ", kUnsigned, 4, 1, NULL},
{"Resident Name Table Offset        ", kUnsigned, 4, 1, NULL},
{"Entry Table Offset                ", kUnsigned, 4, 1, NULL},
{"Module Directives Offset          ", kUnsigned, 4, 1, NULL},
{"Module Directives Count           ", kUnsigned, 4, 1, NULL},
{"Fixup Page Table Offset           ", kUnsigned, 4, 1, NULL},
{"Fixup Record Table Offset         ", kUnsigned, 4, 1, NULL},
{"Import Module Table Offset        ", kUnsigned, 4, 1, NULL},
{"Import Module Table Count         ", kUnsigned, 4, 1, NULL},
{"Import Procedure Name Table Offset", kUnsigned, 4, 1, NULL},
{"Per-Page Checksum Offset          ", kUnsigned, 4, 1, NULL},
{"Data Pages Offset                 ", kUnsigned, 4, 1, NULL},
{"Preload Pages                     ", kUnsigned, 4, 1, NULL},
{"Non-Resident Name Table Offset    ", kUnsigned, 4, 1, NULL},
{"Non-Resident Name Table Length    ", kUnsigned, 4, 1, NULL},
{"Non-Resident Name Table Checksum  ", kUnsigned, 4, 1, NULL},
{"Auto Data Segment Object Number   ", kUnsigned, 4, 1, NULL},
{"Debug Info Offset                 ", kUnsigned, 4, 1, NULL},
{"Debug Info Length                 ", kUnsigned, 4, 1, NULL},
{"Instance Preload                  ", kUnsigned, 4, 1, NULL},
{"Instance Demand                   ", kUnsigned, 4, 1, NULL},
{"Heap Size                         ", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LXFILEHEADER_H__3887EC12_ECA8_4630_B46B_3585C839A510__ */
