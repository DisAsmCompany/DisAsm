/*
 * Filename: ELFHeader32.h
 * Author:   DisAsmCompany
 * Date:     19/01/2014
 *
 * Description: ELF32 Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFHEADER32_H__71667F2C_6E4E_4CAC_A20D_76117B5B02B0__
#define __ELFHEADER32_H__71667F2C_6E4E_4CAC_A20D_76117B5B02B0__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { ELFHeader32Machine             = 2 };
enum { ELFHeader32AddressOfEntryPoint = 8 };
enum { ELFHeader32OffsetPrograms      = 12 };
enum { ELFHeader32OffsetSections      = 16 };
enum { ELFHeader32SizeOfProgram       = 26 };
enum { ELFHeader32NumberOfPrograms    = 28 };
enum { ELFHeader32SizeOfSection       = 30 };
enum { ELFHeader32NumberOfSections    = 32 };
enum { ELFHeader32SectionHeaderIndex  = 34 };

SDFBegin(ELFHeader32, "ELF Header 32"),
{"Type                     ", kUnsigned, 2, 1, ELFType},
{"Machine                  ", kUnsigned, 2, 1, _ELFMachine},
{"Version                  ", kUnsigned, 4, 1, ELFVersion},
{"Address Of Entry Point   ", kUnsigned, 4, 1, NULL},
{"Offset Program Header    ", kUnsigned, 4, 1, NULL},
{"Offset Section Header    ", kUnsigned, 4, 1, NULL},
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

#endif /* __ELFHEADER32_H__71667F2C_6E4E_4CAC_A20D_76117B5B02B0__ */
