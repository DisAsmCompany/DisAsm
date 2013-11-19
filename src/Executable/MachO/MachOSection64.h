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
#ifndef __MACHOSECTION64_H__
#define __MACHOSECTION64_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { MachOSection64Address = 32 };
enum { MachOSection64Size    = 40 };
enum { MachOSection64Offset  = 48 };

static const SDFElement MachOSection64[] =
{
	{"Mach-O Section 64"},
	{"SectionName     ", kStringASCII, 16, 1},
	{"SegmentName     ", kStringASCII, 16, 1},
	{"Address         ", kUnsigned, 8, 1},
	{"Size            ", kUnsigned, 8, 1},
	{"Offset          ", kUnsigned, 4, 1},
	{"Align           ", kUnsigned, 4, 1},
	{"RelocationOffset", kUnsigned, 4, 1},
	{"RelocationCount ", kUnsigned, 4, 1},
	{"Flags           ", kUnsigned, 4, 1, MachOSectionAttributes},
	{"Reserved        ", kReserved, 4, 1},
	{"Reserved        ", kReserved, 4, 1},
	{"Reserved        ", kReserved, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSECTION64_H__ */
