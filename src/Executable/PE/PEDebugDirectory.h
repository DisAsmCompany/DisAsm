/*
* Filename: PEDebugDirectory.h
* Author:   DisAsmCompany
* Date:     29/09/2013
*
* Description: Debug Directory structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEDEBUGDIRECTORY_H__
#define __PEDEBUGDIRECTORY_H__

static const SDFElement PEDebugDirectory[] =
{
	{"Characteristics ", 0, kUnsigned, 4, 1},
	{"TimeDateStamp   ", 0, kUTC, 4, 1},
	{"MajorVersion    ", 0, kUnsigned, 2, 1},
	{"MinorVersion    ", 0, kUnsigned, 2, 1},
	{"Type            ", 0, kUnsigned, 4, 1},
	{"SizeOfData      ", 0, kUnsigned, 4, 1},
	{"AddressOfRawData", 0, kUnsigned, 4, 1},
	{"PointerToRawData", 0, kUnsigned, 4, 1},
};
static const uint32_t PEDebugDirectorySize = sizeof(PEDebugDirectory) / sizeof(PEDebugDirectory[0]);

#endif /* __PEDEBUGDIRECTORY_H__ */
