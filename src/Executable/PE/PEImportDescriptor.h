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

typedef struct PEImportDescriptor_t 
{
	uint32_t OriginalFirstThunk;
	uint32_t TimeDateStamp;
	uint32_t ForwarderChain;
	uint32_t Name;
	uint32_t FirstThunk;
}
PEImportDescriptor;

#endif /* __PEIMPORTDESCRIPTOR_H__ */
