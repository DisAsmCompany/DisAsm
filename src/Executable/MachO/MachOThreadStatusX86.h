
/*
 * Filename: MachOThreadStatusX86.h
 * Author:   DisAsmCompany
 * Date:     29/10/2013
 *
 * Description: Mach-O thread status (x86)
 *
 *
 *
 */

#pragma once
#ifndef __MACHOTHREADSTTUSX86_H__8A3AF381_9432_4F12_BB99_52BB8AF92F9C__
#define __MACHOTHREADSTTUSX86_H__8A3AF381_9432_4F12_BB99_52BB8AF92F9C__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { MachOThreadStatusX86EIP = 40 };

SDFBegin(MachOThreadStatusX86, "Mach-O Thread Status X86"),
{"EAX   ", kUnsigned, 4, 1, NULL},
{"EBX   ", kUnsigned, 4, 1, NULL},
{"ECX   ", kUnsigned, 4, 1, NULL},
{"EDX   ", kUnsigned, 4, 1, NULL},
{"EDI   ", kUnsigned, 4, 1, NULL},
{"ESI   ", kUnsigned, 4, 1, NULL},
{"EBP   ", kUnsigned, 4, 1, NULL},
{"ESP   ", kUnsigned, 4, 1, NULL},
{"SS    ", kUnsigned, 4, 1, NULL},
{"EFLAGS", kUnsigned, 4, 1, NULL},
{"EIP   ", kUnsigned, 4, 1, NULL},
{"CS    ", kUnsigned, 4, 1, NULL},
{"DS    ", kUnsigned, 4, 1, NULL},
{"ES    ", kUnsigned, 4, 1, NULL},
{"FS    ", kUnsigned, 4, 1, NULL},
{"GS    ", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOTHREADSTTUSX86_H__8A3AF381_9432_4F12_BB99_52BB8AF92F9C__ */
