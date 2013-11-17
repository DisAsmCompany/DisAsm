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

enum { kPEDataDirectoryCount = 0x10 };

enum { kPEDataDirectoryExport         =  0 }; /* Export Directory                  */
enum { kPEDataDirectoryImport         =  1 }; /* Import Directory                  */
enum { kPEDataDirectoryResource       =  2 }; /* Resource Directory                */
enum { kPEDataDirectoryException      =  3 }; /* Exception Directory               */
enum { kPEDataDirectorySecurity       =  4 }; /* Security Directory                */
enum { kPEDataDirectoryFixup          =  5 }; /* Base Relocation Table             */
enum { kPEDataDirectoryDebug          =  6 }; /* Debug Directory                   */
enum { kPEDataDirectoryArchitecture   =  7 }; /* Architecture Specific Data        */
enum { kPEDataDirectoryGlobalPtr      =  8 }; /* RVA of GP                         */
enum { kPEDataDirectoryTLS            =  9 }; /* TLS Directory                     */
enum { kPEDataDirectoryLoadConfig     = 10 }; /* Load Configuration Directory      */
enum { kPEDataDirectoryBoundImport    = 11 }; /* Bound Import Directory in headers */
enum { kPEDataDirectoryIAT            = 12 }; /* Import Address Table              */
enum { kPEDataDirectoryDelayImport    = 13 }; /* Delay Load Import Descriptors     */
enum { kPEDataDirectoryCOM            = 14 }; /* COM Runtime descriptor            */

typedef struct PEDataDirectory_t
{
	uint32_t VirtualAddress;
	uint32_t Size;
}
PEDataDirectory;

#endif /* __PEDATADIRECTORY_H__ */
