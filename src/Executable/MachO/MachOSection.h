/*
 * Filename: MachOSection.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Section
 *
 *              
 *
 */

#pragma once
#ifndef __MACHOSECTION_H__F2FBA0F3_3BC6_4868_8710_941CB5CB1238__
#define __MACHOSECTION_H__F2FBA0F3_3BC6_4868_8710_941CB5CB1238__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { MachOSectionAddress = 32 };
enum { MachOSectionSize    = 36 };
enum { MachOSectionOffset  = 40 };

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
	{"Flags           ", kUnsigned, 4, 1, MachOSectionAttributes},
	{"Reserved        ", kReserved, 4, 1},
	{"Reserved        ", kReserved, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSECTION_H__F2FBA0F3_3BC6_4868_8710_941CB5CB1238__ */
