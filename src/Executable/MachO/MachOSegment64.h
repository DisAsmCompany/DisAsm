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
#ifndef __MACHOSEGMENT64_H__02ECB341_C0C8_4F77_9AE9_A35BBC4E51CB__
#define __MACHOSEGMENT64_H__02ECB341_C0C8_4F77_9AE9_A35BBC4E51CB__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kMachOSegment64NumberOfSections = 56 };

SDFBegin(MachOSegment64, "Mach-O Segment"),
{"Name            ", kStringASCII, 16, 1, NULL},
{"VirtualAddress  ", kUnsigned, 8, 1, NULL},
{"VirtualSize     ", kUnsigned, 8, 1, NULL},
{"FileOffset      ", kUnsigned, 8, 1, NULL},
{"FileSize        ", kUnsigned, 8, 1, NULL},
{"ProtectionMax   ", kUnsigned, 4, 1, MachOMemoryProtection},
{"ProtectionInit  ", kUnsigned, 4, 1, MachOMemoryProtection},
{"NumberOfSections", kUnsigned, 4, 1, NULL},
{"Flags           ", kUnsigned, 4, 1, MachOSegmentAttributes},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSEGMENT64_H__02ECB341_C0C8_4F77_9AE9_A35BBC4E51CB__ */
