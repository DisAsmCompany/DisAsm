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
#ifndef __PEIMPORTDESCRIPTOR_H__F01E52DB_CE66_4963_9442_414DB5549FA5__
#define __PEIMPORTDESCRIPTOR_H__F01E52DB_CE66_4963_9442_414DB5549FA5__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PEImportDescriptorOriginalFirstThunk = 0  };
enum { PEImportDescriptorName               = 12 };

SDFBegin(PEImportDescriptor, "PE Import Descriptor"),
{"OriginalFirstThunk", kUnsigned, 4, 1, NULL},
{"TimeDateStamp     ", kUTC, 4, 1, NULL},
{"ForwarderChain    ", kUnsigned, 4, 1, NULL},
{"Name              ", kUnsigned, 4, 1, NULL},
{"FirstThunk        ", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEIMPORTDESCRIPTOR_H__F01E52DB_CE66_4963_9442_414DB5549FA5__ */
