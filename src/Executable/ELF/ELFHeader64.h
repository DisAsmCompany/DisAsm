/*
 * Filename: ELFHeader64.h
 * Author:   DisAsmCompany
 * Date:     19/01/2014
 *
 * Description: ELF64 Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFHEADER64_H__FB8CEABB_F6DF_469A_B062_CA2238D19340__
#define __ELFHEADER64_H__FB8CEABB_F6DF_469A_B062_CA2238D19340__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { ELFHeader64Machine             = 2 };
enum { ELFHeader64AddressOfEntryPoint = 8 };
enum { ELFHeader64OffsetPrograms      = 16 };
enum { ELFHeader64OffsetSections      = 24 };
enum { ELFHeader64SizeOfProgram       = 38 };
enum { ELFHeader64NumberOfPrograms    = 40 };
enum { ELFHeader64SizeOfSection       = 42 };
enum { ELFHeader64NumberOfSections    = 44 };
enum { ELFHeader64SectionHeaderIndex  = 46 };

SDFBegin(ELFHeader64, "ELF Header 64"),
{"Type                     ", kUnsigned, 2, 1, ELFType},
{"Machine                  ", kUnsigned, 2, 1, _ELFMachine},
{"Version                  ", kUnsigned, 4, 1, ELFVersion},
{"Address Of Entry Point   ", kUnsigned, 8, 1, NULL},
{"Offset Program Header    ", kUnsigned, 8, 1, NULL},
{"Offset Section Header    ", kUnsigned, 8, 1, NULL},
{"Flags                    ", kUnsigned, 4, 1, NULL},
{"ELF Header Size          ", kUnsigned, 2, 1, NULL},
{"Program Header Size      ", kUnsigned, 2, 1, NULL},
{"Number OF Program Headers", kUnsigned, 2, 1, NULL},
{"Section Header Size      ", kUnsigned, 2, 1, NULL},
{"Number OF Section Headers", kUnsigned, 2, 1, NULL},
{"Section Header Index     ", kUnsigned, 2, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFHEADER64_H__FB8CEABB_F6DF_469A_B062_CA2238D19340__ */
