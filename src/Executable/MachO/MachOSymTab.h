/*
 * Filename: MachOSymTab.h
 * Author:   DisAsmCompany
 * Date:     14/10/2013
 *
 * Description: Mach-O SymTab Structure
 *)             (symbol table)
 *              
 *
 */

#pragma once
#ifndef __MACHOSYMTAB_H__
#define __MACHOSYMTAB_H__

static const SDFElement MachOSymTab[] =
{
	{"Mach-O Sym Tab"},
	{"SymbolTableOffset", kUnsigned, 4, 1},
	{"NumberOfSymbols  ", kUnsigned, 4, 1},
	{"StringTableOffset", kUnsigned, 4, 1},
	{"StringTableSize  ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __MACHOSYMTAB_H__ */
