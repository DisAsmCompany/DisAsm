/*
 * Filename: MachODylib.h
 * Author:   DisAsmCompany
 * Date:     14/10/2013
 *
 * Description: Mach-O Dylib Structure
 *              (used in several load commands)
 *              
 *
 */

#pragma once
#ifndef __MACHODYLIB_H__0AD2B98B_C18B_4A25_B1EB_9D2BD7C01E1E__
#define __MACHODYLIB_H__0AD2B98B_C18B_4A25_B1EB_9D2BD7C01E1E__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

SDFBegin(MachODylib, "Mach-O Dylib"),
{"OffsetString        ", kUnsigned, 4, 1, NULL},
{"TimeStamp           ", kUTC, 4, 1, NULL},
{"CurrentVersion      ", kVersion, 4, 1, NULL},
{"CompatibilityVersion", kVersion, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHODYLIB_H__0AD2B98B_C18B_4A25_B1EB_9D2BD7C01E1E__ */
