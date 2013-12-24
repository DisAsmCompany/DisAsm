/*
 * Filename: ELFHeader.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFHEADER_H__9B7AE5DE_8EA4_474F_9E5E_1E405118EE8B__
#define __ELFHEADER_H__9B7AE5DE_8EA4_474F_9E5E_1E405118EE8B__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kELFMagic = 0x464C457FUL };

enum { ELFHeaderMagic               = 0  };
enum { ELFHeaderMachine             = 18 };
enum { ELFHeaderAddressOfEntryPoint = 24 };
enum { ELFHeaderOffsetSections      = 32 };
enum { ELFHeaderOffsetPrograms      = 28 };
enum { ELFHeaderSizeOfProgram       = 42 };
enum { ELFHeaderNumberOfPrograms    = 44 };
enum { ELFHeaderSizeOfSection       = 46 };
enum { ELFHeaderNumberOfSections    = 48 };
enum { ELFHeaderSectionHeaderIndex  = 50 };

SDFBegin(ELFHeader, "ELF Header"),
{"Magic                    ", kSignature, 4, 1, NULL},
{"Class                    ", kUnsigned, 1, 1, ELFClass},
{"Data                     ", kUnsigned, 1, 1, ELFData},
{"Version                  ", kUnsigned, 1, 1, ELFVersion},
{"OS ABI                   ", kUnsigned, 1, 1, ELFABI},
{"OS ABI Version           ", kUnsigned, 1, 1, NULL},
{"Padding                  ", kReserved, 1, 7, NULL},
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

#endif /* __ELFHEADER_H__9B7AE5DE_8EA4_474F_9E5E_1E405118EE8B__ */
