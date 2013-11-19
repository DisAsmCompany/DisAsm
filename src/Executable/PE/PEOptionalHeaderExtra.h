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
#ifndef __PEOPTIONALHEADEREXTRA_H__
#define __PEOPTIONALHEADEREXTRA_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PEOptionalHeaderExtraImageBase           = 4  };
enum { PEOptionalHeaderExtraNumberOfRvaAndSizes = 68 };

static const SDFElement PEOptionalHeaderExtra[] =
{
    {"PE Optional Header Extra"},
    {"BaseOfData                 ", kUnsigned, 4, 1},
    {"ImageBase                  ", kUnsigned, 4, 1},
    {"SectionAlignment           ", kUnsigned, 4, 1},
    {"FileAlignment              ", kUnsigned, 4, 1},
    {"MajorOperatingSystemVersion", kUnsigned, 2, 1},
    {"MinorOperatingSystemVersion", kUnsigned, 2, 1},
    {"MajorImageVersion          ", kUnsigned, 2, 1},
    {"MinorImageVersion          ", kUnsigned, 2, 1},
    {"MajorSubsystemVersion      ", kUnsigned, 2, 1},
    {"MinorSubsystemVersion      ", kUnsigned, 2, 1},
    {"Win32VersionValue          ", kUnsigned, 4, 1},
    {"SizeOfImage                ", kUnsigned, 4, 1},
    {"SizeOfHeaders              ", kUnsigned, 4, 1},
    {"CheckSum                   ", kUnsigned, 4, 1},
    {"Subsystem                  ", kUnsigned, 2, 1, PESubsystem},
    {"DllCharacteristics         ", kUnsigned, 2, 1, PEDllCharacteristics},
    {"SizeOfStackReserve         ", kUnsigned, 4, 1},
    {"SizeOfStackCommit          ", kUnsigned, 4, 1},
    {"SizeOfHeapReserve          ", kUnsigned, 4, 1},
    {"SizeOfHeapCommit           ", kUnsigned, 4, 1},
    {"LoaderFlags                ", kUnsigned, 4, 1},
    {"NumberOfRvaAndSizes        ", kUnsigned, 4, 1},
    {NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEOPTIONALHEADEREXTRA_H__ */
