/*
 * Filename: ELFSectionHeader32.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Section Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFSECTIONHEADER32_H__FD58648C_3640_4AA5_AEC7_ADFB57A35C97__
#define __ELFSECTIONHEADER32_H__FD58648C_3640_4AA5_AEC7_ADFB57A35C97__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { ELFSectionHeader32Name    = 0  };
enum { ELFSectionHeader32Type    = 4  };
enum { ELFSectionHeader32Address = 12 };
enum { ELFSectionHeader32Offset  = 16 };
enum { ELFSectionHeader32Size    = 20 };

SDFBegin(ELFSectionHeader32, "ELF Section Header 32"),
{"Name           ", kUnsigned, 4, 1, NULL},
{"Type           ", kUnsigned, 4, 1, _ELFSectionType},
{"Flags          ", kUnsigned, 4, 1, ELFSectionFlags},
{"Address        ", kUnsigned, 4, 1, NULL},
{"Offset         ", kUnsigned, 4, 1, NULL},
{"Size           ", kUnsigned, 4, 1, NULL},
{"Link           ", kUnsigned, 4, 1, NULL},
{"Info           ", kUnsigned, 4, 1, NULL},
{"Align          ", kUnsigned, 4, 1, NULL},
{"Size Of Entries", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFSECTIONHEADER32_H__FD58648C_3640_4AA5_AEC7_ADFB57A35C97__ */
