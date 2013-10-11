/*
 * Filename: MachOSection.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Section
 *)
 *              
 *
 */

#pragma once
#ifndef __MACHOSECTION_H__
#define __MACHOSECTION_H__

static const SDFElement MachOSection[] =
{
	{"Mach-O Section"},
	{"SectionName     ", 0, kStringASCII, 16, 1},
	{"SegmentName     ", 0, kStringASCII, 16, 1},
	{"Address         ", 0, kUnsigned, 4, 1},
	{"Size            ", 0, kUnsigned, 4, 1},
	{"Offset          ", 0, kUnsigned, 4, 1},
	{"Align           ", 0, kUnsigned, 4, 1},
	{"RelocationOffset", 0, kUnsigned, 4, 1},
	{"RelocationCount ", 0, kUnsigned, 4, 1},
	{"Flags           ", 0, kUnsigned, 4, 1},
	{"Reserved        ", 0, kReserved, 4, 1},
	{"Reserved        ", 0, kReserved, 4, 1},
};
static const uint32_t MachOSectionSize = sizeof(MachOSection) / sizeof(MachOSection[0]);

#endif /* __MACHOSECTION_H__ */
