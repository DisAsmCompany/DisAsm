/*
 * Filename: MachOSymTab.h
 * Author:   DisAsmCompany
 * Date:     14/10/2013
 *
 * Description: Mach-O SymTab Structure
 *              (symbol table)
 *              
 *
 */

#pragma once
#ifndef __MACHOSYMTAB_H__6697381C_3637_4901_BAAC_66A2D9C9A85C__
#define __MACHOSYMTAB_H__6697381C_3637_4901_BAAC_66A2D9C9A85C__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFElement MachOSymTab[] =
{
	{"Mach-O Sym Tab"},
	{"SymbolTableOffset", kUnsigned, 4, 1},
	{"NumberOfSymbols  ", kUnsigned, 4, 1},
	{"StringTableOffset", kUnsigned, 4, 1},
	{"StringTableSize  ", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSYMTAB_H__6697381C_3637_4901_BAAC_66A2D9C9A85C__ */
