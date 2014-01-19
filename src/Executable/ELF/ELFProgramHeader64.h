/*
 * Filename: ELFProgramHeader64.h
 * Author:   DisAsmCompany
 * Date:     19/01/2014
 *
 * Description: ELF64 Program Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFPROGRAMHEADER32_H__C599521F_C92F_43EF_A3FD_299EA4683FE3__
#define __ELFPROGRAMHEADER32_H__C599521F_C92F_43EF_A3FD_299EA4683FE3__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

SDFBegin(ELFProgramHeader64, "ELF Program Header 64"),
{"Type            ", kUnsigned, 4, 1, ELFProgramType},
{"Offset          ", kUnsigned, 4, 1, NULL},
{"Virtual Address ", kUnsigned, 8, 1, NULL},
{"Physical Address", kUnsigned, 8, 1, NULL},
{"Physical Size   ", kUnsigned, 8, 1, NULL},
{"Virtual Size    ", kUnsigned, 8, 1, NULL},
{"Flags           ", kUnsigned, 8, 1, ELFProgramFlags},
{"Align           ", kUnsigned, 8, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFPROGRAMHEADER32_H__C599521F_C92F_43EF_A3FD_299EA4683FE3__ */
