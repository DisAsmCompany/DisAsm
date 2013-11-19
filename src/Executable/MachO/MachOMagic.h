/*
 * Filename: MachOMagic.h
 * Author:   DisAsmCompany
 * Date:     14/10/2013
 *
 * Description: Mach-O Magic Numbers
 *             (Signatures)
 *              
 *
 */

#pragma once
#ifndef __MACHOMAGIC_H__
#define __MACHOMAGIC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kMachOMagicLE    = 0xFEEDFACEUL };
enum { kMachOMagicBE    = 0xCEFAEDFEUL };
enum { kMachOFatMagicLE = 0xCAFEBABEUL };
enum { kMachOFatMagicBE = 0xBEBAFECAUL };

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOMAGIC_H__ */
