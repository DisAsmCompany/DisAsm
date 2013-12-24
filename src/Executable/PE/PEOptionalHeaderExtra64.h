/*
* Filename: PEOPtionalHeadersExtra64.h
* Author:   DisAsmCompany
* Date:     22/10/2013
*
* Description: Optional Headers structure
*              of PE file (Portable Executable)
*              extra fields for PE32+ aka PE64 (image only)
*
*/

#pragma once
#ifndef __PEOPTIONALHEADEREXTRA64_H__CD002B9F_B295_4EB8_BE08_8CDCB6CAAE4F__
#define __PEOPTIONALHEADEREXTRA64_H__CD002B9F_B295_4EB8_BE08_8CDCB6CAAE4F__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PEOptionalHeaderExtra64ImageBase           = 0  };
enum { PEOptionalHeaderExtra64NumberOfRvaAndSizes = 84 };

SDFBegin(PEOptionalHeaderExtra64, "PE Optional Header Extra 64"),
{"ImageBase                  ", kUnsigned, 8, 1, NULL},
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
{"SizeOfStackReserve         ", kUnsigned, 8, 1, NULL},
{"SizeOfStackCommit          ", kUnsigned, 8, 1, NULL},
{"SizeOfHeapReserve          ", kUnsigned, 8, 1, NULL},
{"SizeOfHeapCommit           ", kUnsigned, 8, 1, NULL},
{"LoaderFlags                ", kUnsigned, 4, 1, NULL},
{"NumberOfRvaAndSizes        ", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEOPTIONALHEADEREXTRA64_H__CD002B9F_B295_4EB8_BE08_8CDCB6CAAE4F__ */
