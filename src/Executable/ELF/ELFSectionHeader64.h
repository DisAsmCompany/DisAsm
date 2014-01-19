/*
 * Filename: ELFSectionHeader64.h
 * Author:   DisAsmCompany
 * Date:     19/01/2014
 *
 * Description: ELF64 Section Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFSECTIONHEADER64_H__AF5A6593_F48C_4269_AAE8_A1E2785C94CC__
#define __ELFSECTIONHEADER64_H__AF5A6593_F48C_4269_AAE8_A1E2785C94CC__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { ELFSectionHeader64Name    = 0  };
enum { ELFSectionHeader64Type    = 4  };
enum { ELFSectionHeader64Address = 16 };
enum { ELFSectionHeader64Offset  = 24 };
enum { ELFSectionHeader64Size    = 32 };

SDFBegin(ELFSectionHeader64, "ELF Section Header 64"),
{"Name           ", kUnsigned, 4, 1, NULL},
{"Type           ", kUnsigned, 4, 1, _ELFSectionType},
{"Flags          ", kUnsigned, 8, 1, ELFSectionFlags},
{"Address        ", kUnsigned, 8, 1, NULL},
{"Offset         ", kUnsigned, 8, 1, NULL},
{"Size           ", kUnsigned, 8, 1, NULL},
{"Link           ", kUnsigned, 4, 1, NULL},
{"Info           ", kUnsigned, 4, 1, NULL},
{"Align          ", kUnsigned, 8, 1, NULL},
{"Size Of Entries", kUnsigned, 8, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFSECTIONHEADER64_H__AF5A6593_F48C_4269_AAE8_A1E2785C94CC__ */
