/*
* Filename: PEExportDirectory.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Export Directory structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEEXPORTDIRECTORY_H__06AD55F0_A581_4FE9_8286_55EF04C81B5C__
#define __PEEXPORTDIRECTORY_H__06AD55F0_A581_4FE9_8286_55EF04C81B5C__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PEExportDirectoryNumberOfFunctions     = 20 };
enum { PEExportDirectoryNumberOfNames         = 24 };
enum { PEExportDirectoryAddressOfFunctions    = 28 };
enum { PEExportDirectoryAddressOfNames        = 32 };
enum { PEExportDirectoryAddressOfNameOrdinals = 36 };

SDFBegin(PEExportDirectory, "PE Export Directory"),
{"Characteristics      ", kUnsigned, 4, 1, NULL},
{"TimeDateStamp        ", kUTC, 4, 1, NULL},
{"MajorVersion         ", kUnsigned, 2, 1, NULL},
{"MinorVersion         ", kUnsigned, 2, 1, NULL},
{"Name                 ", kUnsigned, 4, 1, NULL},
{"OrdinalBase          ", kUnsigned, 4, 1, NULL},
{"NumberOfFunctions    ", kUnsigned, 4, 1, NULL},
{"NumberOfNames        ", kUnsigned, 4, 1, NULL},
{"AddressOfFunctions   ", kUnsigned, 4, 1, NULL},
{"AddressOfNames       ", kUnsigned, 4, 1, NULL},
{"AddressOfNameOrdinals", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEEXPORTDIRECTORY_H__06AD55F0_A581_4FE9_8286_55EF04C81B5C__ */
