/*
 * Filename: MachOSection64.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Section 64
 *
 *              
 *
 */

#pragma once
#ifndef __MACHOSECTION64_H__042B1D9B_071F_4B43_A792_4B7B205501F3__
#define __MACHOSECTION64_H__042B1D9B_071F_4B43_A792_4B7B205501F3__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { MachOSection64Address = 32 };
enum { MachOSection64Size    = 40 };
enum { MachOSection64Offset  = 48 };

SDFBegin(MachOSection64, "Mach-O Section 64"),
{"SectionName     ", kStringASCII, 16, 1, NULL},
{"SegmentName     ", kStringASCII, 16, 1, NULL},
{"Address         ", kUnsigned, 8, 1, NULL},
{"Size            ", kUnsigned, 8, 1, NULL},
{"Offset          ", kUnsigned, 4, 1, NULL},
{"Align           ", kUnsigned, 4, 1, NULL},
{"RelocationOffset", kUnsigned, 4, 1, NULL},
{"RelocationCount ", kUnsigned, 4, 1, NULL},
{"Flags           ", kUnsigned, 4, 1, MachOSectionAttributes},
{"Reserved        ", kReserved, 4, 1, NULL},
{"Reserved        ", kReserved, 4, 1, NULL},
{"Reserved        ", kReserved, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSECTION64_H__042B1D9B_071F_4B43_A792_4B7B205501F3__ */
