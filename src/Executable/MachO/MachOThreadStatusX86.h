
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

static const SDFElement MachOThreadStatusX86[] =
{
	{"Mach-O Thread Status X86"},
	{"EAX   ", kUnsigned, 4, 1},
	{"EBX   ", kUnsigned, 4, 1},
	{"ECX   ", kUnsigned, 4, 1},
	{"EDX   ", kUnsigned, 4, 1},
	{"EDI   ", kUnsigned, 4, 1},
	{"ESI   ", kUnsigned, 4, 1},
	{"EBP   ", kUnsigned, 4, 1},
	{"ESP   ", kUnsigned, 4, 1},
	{"SS    ", kUnsigned, 4, 1},
	{"EFLAGS", kUnsigned, 4, 1},
	{"EIP   ", kUnsigned, 4, 1},
	{"CS    ", kUnsigned, 4, 1},
	{"DS    ", kUnsigned, 4, 1},
	{"ES    ", kUnsigned, 4, 1},
	{"FS    ", kUnsigned, 4, 1},
	{"GS    ", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOTHREADSTTUSX86_H__8A3AF381_9432_4F12_BB99_52BB8AF92F9C__ */
