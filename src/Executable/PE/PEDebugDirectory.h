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

static const SDFElement PEDebugDirectory[] =
{
	{"PE Debug Directory"},
	{"Characteristics ", kUnsigned, 4, 1},
	{"TimeDateStamp   ", kUTC, 4, 1},
	{"MajorVersion    ", kUnsigned, 2, 1},
	{"MinorVersion    ", kUnsigned, 2, 1},
	{"Type            ", kUnsigned, 4, 1, PEDebugType},
	{"SizeOfData      ", kUnsigned, 4, 1},
	{"AddressOfRawData", kUnsigned, 4, 1},
	{"PointerToRawData", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEDEBUGDIRECTORY_H__B9D454F1_BABD_43E0_A433_ED7B20513AA3__ */
