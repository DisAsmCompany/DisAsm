/*
 * Filename: ELFIdent.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Identification
 *
 *
 *
 */

#pragma once
#ifndef __ELFIDENT_H__9B7AE5DE_8EA4_474F_9E5E_1E405118EE8B__
#define __ELFIDENT_H__9B7AE5DE_8EA4_474F_9E5E_1E405118EE8B__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kELFMagic = 0x464C457FUL };

enum { ELFHeaderMagic               = 0 };
enum { ELFHeaderClass               = 4 };

SDFBegin(ELFIdent, "ELF Ident"),
{"Magic                    ", kSignature, 4, 1, NULL},
{"Class                    ", kUnsigned, 1, 1, _ELFClass},
{"Data                     ", kUnsigned, 1, 1, ELFData},
{"Version                  ", kUnsigned, 1, 1, ELFVersion},
{"OS ABI                   ", kUnsigned, 1, 1, ELFABI},
{"OS ABI Version           ", kUnsigned, 1, 1, NULL},
{"Padding                  ", kReserved, 1, 7, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFIDENT_H__9B7AE5DE_8EA4_474F_9E5E_1E405118EE8B__ */
