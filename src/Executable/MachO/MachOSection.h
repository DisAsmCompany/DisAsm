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

SDFBegin(MachOSection, "Mach-O Section"),
{"SectionName     ", kStringASCII, 16, 1, NULL},
{"SegmentName     ", kStringASCII, 16, 1, NULL},
{"Address         ", kUnsigned, 4, 1, NULL},
{"Size            ", kUnsigned, 4, 1, NULL},
{"Offset          ", kUnsigned, 4, 1, NULL},
{"Align           ", kUnsigned, 4, 1, NULL},
{"RelocationOffset", kUnsigned, 4, 1, NULL},
{"RelocationCount ", kUnsigned, 4, 1, NULL},
{"Flags           ", kUnsigned, 4, 1, MachOSectionAttributes},
{"Reserved        ", kReserved, 4, 1, NULL},
{"Reserved        ", kReserved, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSECTION_H__F2FBA0F3_3BC6_4868_8710_941CB5CB1238__ */
