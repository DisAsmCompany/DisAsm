/*
 * Filename: ELFSymbol.h
 * Author:   DisAsmCompany
 * Date:     06/11/2013
 *
 * Description: ELF Symbol (exported or debug)
 *              used in sections like .symtab or .dynsym
 *
 *
 */

#pragma once
#ifndef __ELFSYMBOL_H__
#define __ELFSYMBOL_H__

static const uint32_t ELFSymbolName  = 0;
static const uint32_t ELFSymbolValue = 4;
static const uint32_t ELFSymbolIndex = 14;

static const SDFElement ELFSymbol[] =
{
	{"ELF Symbol"},
	{"Name ", kUnsigned, 4, 1},
	{"Value", kUnsigned, 4, 1},
	{"Size ", kUnsigned, 4, 1},
	{"Info ", kUnsigned, 1, 1, ELFSymbolType},
	{"Other", kUnsigned, 1, 1},
	{"Index", kUnsigned, 2, 1},
	{NULL}
};

#endif /* __ELFSYMBOL_H__ */
