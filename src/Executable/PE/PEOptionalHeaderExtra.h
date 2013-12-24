/*
* Filename: PEOPtionalHeadersExtra.h
* Author:   DisAsmCompany
* Date:     22/10/2013
*
* Description: Optional Headers structure
*              of PE file (Portable Executable)
*              extra fields for PE32 (image only)
*
*/

#pragma once
#ifndef __PEOPTIONALHEADEREXTRA_H__933B7C9E_1E13_4422_A94B_6176B36C90F0__
#define __PEOPTIONALHEADEREXTRA_H__933B7C9E_1E13_4422_A94B_6176B36C90F0__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PEOptionalHeaderExtraImageBase           = 4  };
enum { PEOptionalHeaderExtraNumberOfRvaAndSizes = 68 };

SDFBegin(PEOptionalHeaderExtra, "PE Optional Header Extra"),
{"BaseOfData                 ", kUnsigned, 4, 1, NULL},
{"ImageBase                  ", kUnsigned, 4, 1, NULL},
{"SectionAlignment           ", kUnsigned, 4, 1, NULL},
{"FileAlignment              ", kUnsigned, 4, 1, NULL},
{"MajorOperatingSystemVersion", kUnsigned, 2, 1, NULL},
{"MinorOperatingSystemVersion", kUnsigned, 2, 1, NULL},
{"MajorImageVersion          ", kUnsigned, 2, 1, NULL},
{"MinorImageVersion          ", kUnsigned, 2, 1, NULL},
{"MajorSubsystemVersion      ", kUnsigned, 2, 1, NULL},
{"MinorSubsystemVersion      ", kUnsigned, 2, 1, NULL},
{"Win32VersionValue          ", kUnsigned, 4, 1, NULL},
{"SizeOfImage                ", kUnsigned, 4, 1, NULL},
{"SizeOfHeaders              ", kUnsigned, 4, 1, NULL},
{"CheckSum                   ", kUnsigned, 4, 1, NULL},
{"Subsystem                  ", kUnsigned, 2, 1, PESubsystem},
{"DllCharacteristics         ", kUnsigned, 2, 1, PEDllCharacteristics},
{"SizeOfStackReserve         ", kUnsigned, 4, 1, NULL},
{"SizeOfStackCommit          ", kUnsigned, 4, 1, NULL},
{"SizeOfHeapReserve          ", kUnsigned, 4, 1, NULL},
{"SizeOfHeapCommit           ", kUnsigned, 4, 1, NULL},
{"LoaderFlags                ", kUnsigned, 4, 1, NULL},
{"NumberOfRvaAndSizes        ", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEOPTIONALHEADEREXTRA_H__933B7C9E_1E13_4422_A94B_6176B36C90F0__ */
