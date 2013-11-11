
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
#ifndef __MACHOTHREADSTTUSX64_H__
#define __MACHOTHREADSTTUSX64_H__

static const uint32_t MachOThreadStatusX64EIP = 128;

static const SDFElement MachOThreadStatusX64[] =
{
	{"Mach-O Thread Status X64"},
	{"RAX   ", kUnsigned, 8, 1},
	{"RBX   ", kUnsigned, 8, 1},
	{"RCX   ", kUnsigned, 8, 1},
	{"RDX   ", kUnsigned, 8, 1},
	{"RDI   ", kUnsigned, 8, 1},
	{"RSI   ", kUnsigned, 8, 1},
	{"RBP   ", kUnsigned, 8, 1},
	{"RSP   ", kUnsigned, 8, 1},
	{"R8    ", kUnsigned, 8, 1},
	{"R9    ", kUnsigned, 8, 1},
	{"R10   ", kUnsigned, 8, 1},
	{"R11   ", kUnsigned, 8, 1},
	{"R12   ", kUnsigned, 8, 1},
	{"R13   ", kUnsigned, 8, 1},
	{"R14   ", kUnsigned, 8, 1},
	{"R15   ", kUnsigned, 8, 1},
	{"RIP   ", kUnsigned, 8, 1},
	{"RFLAGS", kUnsigned, 8, 1},
	{"CS    ", kUnsigned, 8, 1},
	{"FS    ", kUnsigned, 8, 1},
	{"GS    ", kUnsigned, 8, 1},
	{NULL}
};

#endif /* __MACHOTHREADSTTUSX64_H__ */
