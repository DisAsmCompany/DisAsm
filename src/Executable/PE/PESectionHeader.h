/*
* Filename: PESectionHeader.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Section Headers structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PESECTIONHEADER_H__D327031D_4668_43CE_8A7B_31DE64A3F176__
#define __PESECTIONHEADER_H__D327031D_4668_43CE_8A7B_31DE64A3F176__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PESectionHeaderVirtualAddress   = 12 };
enum { PESectionHeaderSizeOfRawData    = 16 };
enum { PESectionHeaderPointerToRawData = 20 };

SDFBegin(PESectionHeader, "PE Section Header"),
{"Name                ", kStringASCII, 8, 1, NULL},
{"PhysicalAddress     ", kUnsigned, 4, 1, NULL},
{"VirtualAddress      ", kUnsigned, 4, 1, NULL},
{"SizeOfRawData       ", kUnsigned, 4, 1, NULL},
{"PointerToRawData    ", kUnsigned, 4, 1, NULL},
{"PointerToRelocations", kUnsigned, 4, 1, NULL},
{"PointerToLinenumbers", kUnsigned, 4, 1, NULL},
{"NumberOfRelocations ", kUnsigned, 2, 1, NULL},
{"NumberOfLinenumbers ", kUnsigned, 2, 1, NULL},
{"Characteristics     ", kUnsigned, 4, 1, PESectionCharacteristics},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PESECTIONHEADER_H__D327031D_4668_43CE_8A7B_31DE64A3F176__ */
