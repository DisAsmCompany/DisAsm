/*
* Filename: PEDataDirectory.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Data Directory structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEDATADIRECTORY_H__
#define __PEDATADIRECTORY_H__

#ifndef PEDataDirectoryCount
#define PEDataDirectoryCount 0x10
#endif /* PEDataDirectoryCount */

#define PEDataDirectoryExport          0   // Export Directory
#define PEDataDirectoryImport          1   // Import Directory
#define PEDataDirectoryResource        2   // Resource Directory
#define PEDataDirectoryException       3   // Exception Directory
#define PEDataDirectorySecurity        4   // Security Directory
#define PEDataDirectoryFixup           5   // Base Relocation Table
#define PEDataDirectoryDebug           6   // Debug Directory
#define PEDataDirectoryArchitecture    7   // Architecture Specific Data
#define PEDataDirectoryGlobalPtr       8   // RVA of GP
#define PEDataDirectoryTLS             9   // TLS Directory
#define PEDataDirectoryLoadConfig     10   // Load Configuration Directory
#define PEDataDirectoryBoundImport    11   // Bound Import Directory in headers
#define PEDataDirectoryIAT            12   // Import Address Table
#define PEDataDirectoryDelayImport    13   // Delay Load Import Descriptors
#define PEDataDirectoryCOM            14   // COM Runtime descriptor

typedef struct PEDataDirectory_t
{
	uint32_t VirtualAddress;
	uint32_t Size;
}
PEDataDirectory;

#endif /* __PEDATADIRECTORY_H__ */
