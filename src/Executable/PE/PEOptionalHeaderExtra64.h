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
#ifndef __PEOPTIONALHEADEREXTRA64_H__
#define __PEOPTIONALHEADEREXTRA64_H__

enum { PEOptionalHeaderExtra64ImageBase           = 0  };
enum { PEOptionalHeaderExtra64NumberOfRvaAndSizes = 84 };

static const SDFElement PEOptionalHeaderExtra64[] =
{
    {"PE Optional Header Extra 64"},
    {"ImageBase                  ", kUnsigned, 8, 1},
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
    {"SizeOfStackReserve         ", kUnsigned, 8, 1},
    {"SizeOfStackCommit          ", kUnsigned, 8, 1},
    {"SizeOfHeapReserve          ", kUnsigned, 8, 1},
    {"SizeOfHeapCommit           ", kUnsigned, 8, 1},
    {"LoaderFlags                ", kUnsigned, 4, 1},
    {"NumberOfRvaAndSizes        ", kUnsigned, 4, 1},
    {NULL}
};

#endif /* __PEOPTIONALHEADEREXTRA64_H__ */
