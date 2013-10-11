/*
 * Filename: MachOSection64.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Section 64
 *)
 *              
 *
 */

#pragma once
#ifndef __MACHOSECTION64_H__
#define __MACHOSECTION64_H__

static const SDFElement MachOSection64[] =
{
	{"Mach-O Section 64"},
	{"SectionName     ", 0, kStringASCII, 16, 1},
	{"SegmentName     ", 0, kStringASCII, 16, 1},
	{"Address         ", 0, kUnsigned, 8, 1},
	{"Size            ", 0, kUnsigned, 8, 1},
	{"Offset          ", 0, kUnsigned, 4, 1},
	{"Align           ", 0, kUnsigned, 4, 1},
	{"RelocationOffset", 0, kUnsigned, 4, 1},
	{"RelocationCount ", 0, kUnsigned, 4, 1},
	{"Flags           ", 0, kUnsigned, 4, 1},
	{"Reserved        ", 0, kReserved, 4, 1},
	{"Reserved        ", 0, kReserved, 4, 1},
};
static const uint32_t MachOSection64Size = sizeof(MachOSection64) / sizeof(MachOSection64[0]);

#endif /* __MACHOSECTION64_H__ */
