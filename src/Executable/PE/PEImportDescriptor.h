/*
* Filename: PEImportDescriptor.h
* Author:   DisAsmCompany
* Date:     29/09/2013
*", k
* Description: Import Descriptor structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEIMPORTDESCRIPTOR_H__
#define __PEIMPORTDESCRIPTOR_H__

#define PEImportDescriptorOriginalFirstThunk 0
#define PEImportDescriptorName               12

static const SDFElement PEImportDescriptor[] =
{
	{"PE Import Descriptor"},
	{"OriginalFirstThunk", kUnsigned, 4, 1},
	{"TimeDateStamp     ", kUTC, 4, 1},
	{"ForwarderChain    ", kUnsigned, 4, 1},
	{"Name              ", kUnsigned, 4, 1},
	{"FirstThunk        ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __PEIMPORTDESCRIPTOR_H__ */
