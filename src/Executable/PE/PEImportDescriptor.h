/*
* Filename: PEImportDescriptor.h
* Author:   DisAsmCompany
* Date:     29/09/2013
*
* Description: Import Descriptor structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEIMPORTDESCRIPTOR_H__
#define __PEIMPORTDESCRIPTOR_H__

#define PEImportDescriptorOriginalFirstThunk 1
#define PEImportDescriptorName               2

static const SDFElement PEImportDescriptor[] =
{
	{"PE Import Descriptor"},
	{"OriginalFirstThunk", PEImportDescriptorOriginalFirstThunk, kUnsigned, 4, 1},
	{"TimeDateStamp     ", 0, kUTC, 4, 1},
	{"ForwarderChain    ", 0, kUnsigned, 4, 1},
	{"Name              ", PEImportDescriptorName, kUnsigned, 4, 1},
	{"FirstThunk        ", 0, kUnsigned, 4, 1},
};
static const uint32_t PEImportDescriptorSize = sizeof(PEImportDescriptor) / sizeof(PEImportDescriptor[0]);

#endif /* __PEIMPORTDESCRIPTOR_H__ */
