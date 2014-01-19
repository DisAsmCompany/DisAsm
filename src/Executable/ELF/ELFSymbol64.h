/*
 * Filename: ELFSymbol64.h
 * Author:   DisAsmCompany
 * Date:     19/01/2014
 *
 * Description: ELF64 Symbol (exported or debug)
 *              used in sections like .symtab or .dynsym
 *
 *
 */

#pragma once
#ifndef __ELFSYMBOL64_H__5313C415_ED7B_4BF8_A61D_9991D7DBD547__
#define __ELFSYMBOL64_H__5313C415_ED7B_4BF8_A61D_9991D7DBD547__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { ELFSymbol64Name  = 0 };
enum { ELFSymbol64Value = 8 };
enum { ELFSymbol64Index = 6 };

SDFBegin(ELFSymbol64, "ELF Symbol 64"),
{"Name ", kUnsigned, 4, 1, NULL},
{"Info ", kUnsigned, 1, 1, ELFSymbolType},
{"Other", kUnsigned, 1, 1, NULL},
{"Index", kUnsigned, 2, 1, NULL},
{"Value", kUnsigned, 8, 1, NULL},
{"Size ", kUnsigned, 8, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFSYMBOL64_H__5313C415_ED7B_4BF8_A61D_9991D7DBD547__ */
