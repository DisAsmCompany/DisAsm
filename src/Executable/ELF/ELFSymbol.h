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
#ifndef __ELFSYMBOL_H__DFEC7F1E_9027_43D9_9393_A4074A350AB6__
#define __ELFSYMBOL_H__DFEC7F1E_9027_43D9_9393_A4074A350AB6__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { ELFSymbolName  = 0 };
enum { ELFSymbolValue = 4 };
enum { ELFSymbolIndex = 14 };

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFSYMBOL_H__DFEC7F1E_9027_43D9_9393_A4074A350AB6__ */
