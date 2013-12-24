
/*
 * Filename: MachOThreadStatusX64.h
 * Author:   DisAsmCompany
 * Date:     11/11/2013
 *
 * Description: Mach-O thread status (x64)
 *
 *
 *
 */

#pragma once
#ifndef __MACHOTHREADSTTUSX64_H__3B766B44_D3F2_400A_9DA4_AD67E0D0291A__
#define __MACHOTHREADSTTUSX64_H__3B766B44_D3F2_400A_9DA4_AD67E0D0291A__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { MachOThreadStatusX64EIP = 128 };

SDFBegin(MachOThreadStatusX64, "Mach-O Thread Status X64"),
{"RAX   ", kUnsigned, 8, 1, NULL},
{"RBX   ", kUnsigned, 8, 1, NULL},
{"RCX   ", kUnsigned, 8, 1, NULL},
{"RDX   ", kUnsigned, 8, 1, NULL},
{"RDI   ", kUnsigned, 8, 1, NULL},
{"RSI   ", kUnsigned, 8, 1, NULL},
{"RBP   ", kUnsigned, 8, 1, NULL},
{"RSP   ", kUnsigned, 8, 1, NULL},
{"R8    ", kUnsigned, 8, 1, NULL},
{"R9    ", kUnsigned, 8, 1, NULL},
{"R10   ", kUnsigned, 8, 1, NULL},
{"R11   ", kUnsigned, 8, 1, NULL},
{"R12   ", kUnsigned, 8, 1, NULL},
{"R13   ", kUnsigned, 8, 1, NULL},
{"R14   ", kUnsigned, 8, 1, NULL},
{"R15   ", kUnsigned, 8, 1, NULL},
{"RIP   ", kUnsigned, 8, 1, NULL},
{"RFLAGS", kUnsigned, 8, 1, NULL},
{"CS    ", kUnsigned, 8, 1, NULL},
{"FS    ", kUnsigned, 8, 1, NULL},
{"GS    ", kUnsigned, 8, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOTHREADSTTUSX64_H__3B766B44_D3F2_400A_9DA4_AD67E0D0291A__ */
