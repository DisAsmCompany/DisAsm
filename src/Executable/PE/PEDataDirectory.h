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

#ifndef kPEDataDirectoryCount
static const uint32_t kPEDataDirectoryCount = 0x10;
#endif /* PEDataDirectoryCount */

static const uint32_t kPEDataDirectoryExport         =  0; /* Export Directory                  */
static const uint32_t kPEDataDirectoryImport         =  1; /* Import Directory                  */
static const uint32_t kPEDataDirectoryResource       =  2; /* Resource Directory                */
static const uint32_t kPEDataDirectoryException      =  3; /* Exception Directory               */
static const uint32_t kPEDataDirectorySecurity       =  4; /* Security Directory                */
static const uint32_t kPEDataDirectoryFixup          =  5; /* Base Relocation Table             */
static const uint32_t kPEDataDirectoryDebug          =  6; /* Debug Directory                   */
static const uint32_t kPEDataDirectoryArchitecture   =  7; /* Architecture Specific Data        */
static const uint32_t kPEDataDirectoryGlobalPtr      =  8; /* RVA of GP                         */
static const uint32_t kPEDataDirectoryTLS            =  9; /* TLS Directory                     */
static const uint32_t kPEDataDirectoryLoadConfig     = 10; /* Load Configuration Directory      */
static const uint32_t kPEDataDirectoryBoundImport    = 11; /* Bound Import Directory in headers */
static const uint32_t kPEDataDirectoryIAT            = 12; /* Import Address Table              */
static const uint32_t kPEDataDirectoryDelayImport    = 13; /* Delay Load Import Descriptors     */
static const uint32_t kPEDataDirectoryCOM            = 14; /* COM Runtime descriptor            */

typedef struct PEDataDirectory_t
{
	uint32_t VirtualAddress;
	uint32_t Size;
}
PEDataDirectory;

#endif /* __PEDATADIRECTORY_H__ */
