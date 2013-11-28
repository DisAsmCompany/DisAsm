/*
 * Filename: COFFSymbolTable.h
 * Author:   DisAsmCompany
 * Date:     25/10/2013
 *
 * Description: COFF Symbol Table
 *              used in Microsoft COFF
 *              Object (.obj) files
 *
 */

#pragma once
#ifndef __COFFSYMBOLTABLE_H__068A299D_B584_4CE6_AA3B_3BA630C39900__
#define __COFFSYMBOLTABLE_H__068A299D_B584_4CE6_AA3B_3BA630C39900__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { COFFSymbolTableValue                    = 0 };
enum { COFFSymbolTableSectionNumber            = 4 };
enum { COFFSymbolTableType                     = 6 };
enum { COFFSymbolTableStorageClass             = 8 };
enum { COFFSymbolTableNumberOfAuxiliarySymbols = 9 };

static const SDFElement COFFSymbolTable[] = 
{
	{"COFF Symbol Table"},
	{"Value                      ", kUnsigned, 4, 1},
	{"Section Number             ", kUnsigned, 2, 1, COFFSectionNumber},
	{"Type                       ", kUnsigned, 2, 1, _COFFSymbolType},
	{"Storage Class              ", kUnsigned, 1, 1, _COFFSymbolClass},
	{"Number Of Auxiliary Symbols", kUnsigned, 1, 1},
	{NULL}
};

static const SDFElement COFFSymbolTableAuxiliaryFormatFunction[] = 
{
	{"Auxiliary Format 1: Function Definitions"},
	{"Tag Index               ", kUnsigned, 4, 1},
	{"Total Size              ", kUnsigned, 4, 1},
	{"Pointer To Line Number  ", kUnsigned, 4, 1},
	{"Pointer To Next Function", kUnsigned, 4, 1},
	{"Unused                  ", kReserved, 2, 1},
	{NULL}
};

static const SDFElement COFFSymbolTableAuxiliaryFormatFiles[] = 
{
	{"Auxiliary Format 4 : Files"},
	{"File Name", kStringASCII, 18, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COFFSYMBOLTABLE_H__068A299D_B584_4CE6_AA3B_3BA630C39900__ */
