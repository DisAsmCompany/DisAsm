/*
* Filename: PEFileHeader.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: File Header structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEFILEHEADER_H__01113985_FC76_4F04_BA9E_979FCDA182E0__
#define __PEFILEHEADER_H__01113985_FC76_4F04_BA9E_979FCDA182E0__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kPESignature = 0x00004550UL }; /* PE */

enum { PEFileHeaderMachine              = 0  };
enum { PEFileHeaderNumberOfSections     = 2  };
enum { PEFileHeaderPointerToSymbolTable = 8  };
enum { PEFileHeaderNumberOfSymbols      = 12 };
enum { PEFileHeaderSizeOfOptionalHeader = 16 };

SDFBegin(PEFileHeader, "PE File Header"),
{"Machine             ", kUnsigned, 2, 1, _PEMachine},
{"NumberOfSections    ", kUnsigned, 2, 1, NULL},
{"TimeDateStamp       ", kUTC, 4, 1, NULL},
{"PointerToSymbolTable", kUnsigned, 4, 1, NULL},
{"NumberOfSymbols     ", kUnsigned, 4, 1, NULL},
{"SizeOfOptionalHeader", kUnsigned, 2, 1, NULL},
{"Characteristics     ", kUnsigned, 2, 1, PECharacteristics},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEFILEHEADER_H__01113985_FC76_4F04_BA9E_979FCDA182E0__ */
