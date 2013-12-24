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
#ifndef __PEDEBUGDIRECTORY_H__B9D454F1_BABD_43E0_A433_ED7B20513AA3__
#define __PEDEBUGDIRECTORY_H__B9D454F1_BABD_43E0_A433_ED7B20513AA3__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

SDFBegin(PEDebugDirectory, "PE Debug Directory"),
{"Characteristics ", kUnsigned, 4, 1, NULL},
{"TimeDateStamp   ", kUTC, 4, 1, NULL},
{"MajorVersion    ", kUnsigned, 2, 1, NULL},
{"MinorVersion    ", kUnsigned, 2, 1, NULL},
{"Type            ", kUnsigned, 4, 1, PEDebugType},
{"SizeOfData      ", kUnsigned, 4, 1, NULL},
{"AddressOfRawData", kUnsigned, 4, 1, NULL},
{"PointerToRawData", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEDEBUGDIRECTORY_H__B9D454F1_BABD_43E0_A433_ED7B20513AA3__ */
