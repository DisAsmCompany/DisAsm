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
	{"SectionName     ", kStringASCII, 16, 1},
	{"SegmentName     ", kStringASCII, 16, 1},
	{"Address         ", kUnsigned, 4, 1},
	{"Size            ", kUnsigned, 4, 1},
	{"Offset          ", kUnsigned, 4, 1},
	{"Align           ", kUnsigned, 4, 1},
	{"RelocationOffset", kUnsigned, 4, 1},
	{"RelocationCount ", kUnsigned, 4, 1},
	{"Flags           ", kUnsigned, 4, 1},
	{"Reserved        ", kReserved, 4, 1},
	{"Reserved        ", kReserved, 4, 1},
	{NULL}
};

#endif /* __MACHOSECTION_H__ */
