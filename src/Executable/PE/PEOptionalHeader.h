/*
* Filename: PEOPtionalHeaders.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Optional Headers structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEOPTIONALHEADER_H__3EE5214B_CF69_4498_95E4_B3EE80EE7680__
#define __PEOPTIONALHEADER_H__3EE5214B_CF69_4498_95E4_B3EE80EE7680__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PEOptionalHeaderMagic               = 0  };
enum { PEOptionalHeaderAddressOfEntryPoint = 16 };

SDFBegin(PEOptionalHeader, "PE Optional Header"),
{"Magic                      ", kUnsigned, 2, 1, _PEMagic},
{"MajorLinkerVersion         ", kUnsigned, 1, 1, NULL},
{"MinorLinkerVersion         ", kUnsigned, 1, 1, NULL},
{"SizeOfCode                 ", kUnsigned, 4, 1, NULL},
{"SizeOfInitializedData      ", kUnsigned, 4, 1, NULL},
{"SizeOfUninitializedData    ", kUnsigned, 4, 1, NULL},
{"AddressOfEntryPoint        ", kUnsigned, 4, 1, NULL},
{"BaseOfCode                 ", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEOPTIONALHEADER_H__3EE5214B_CF69_4498_95E4_B3EE80EE7680__ */
