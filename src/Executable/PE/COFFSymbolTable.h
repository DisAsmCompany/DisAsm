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
#ifndef __COFFSYMBOLTABLE_H__
#define __COFFSYMBOLTABLE_H__

static const uint32_t COFFSymbolTableSectionNumber            = 12;
static const uint32_t COFFSymbolTableType                     = 14;
static const uint32_t COFFSymbolTableStorageClass             = 16;
static const uint32_t COFFSymbolTableNumberOfAuxiliarySymbols = 17;

static const SDFElement COFFSymbolTable[] = 
{
	{"COFF Symbol Table"},
	{"Name                       ", kStringASCII, 8, 1},
	{"Value                      ", kUnsigned, 4, 1},
	{"Section Number             ", kUnsigned, 2, 1, COFFSectionNumber},
	{"Type                       ", kUnsigned, 2, 1, COFFSymbolType},
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

#endif /* __COFFSYMBOLTABLE_H__ */
