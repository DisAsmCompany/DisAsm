/*
 * Filename: MachOMagic.h
 * Author:   DisAsmCompany
 * Date:     14/10/2013
 *
 * Description: Mach-O Magic Numbers
 *)             (Signatures)
 *              
 *
 */

#pragma once
#ifndef __MACHOMAGIC_H__
#define __MACHOMAGIC_H__

static const uint32_t kMachOMagicLE    = 0xFEEDFACEUL;
static const uint32_t kMachOMagicBE    = 0xCEFAEDFEUL;
static const uint32_t kMachOFatMagicLE = 0xCAFEBABEUL;
static const uint32_t kMachOFatMagicBE = 0xBEBAFECAUL;

#endif /* __MACHOMAGIC_H__ */
