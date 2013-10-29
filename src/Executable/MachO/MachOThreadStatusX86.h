
/*
 * Filename: MachOThreadStatusX86.h
 * Author:   DisAsmCompany
 * Date:     29/10/2013
 *
 * Description: Mach-O header
 *
 *
 *
 */

#pragma once
#ifndef __MACHOTHREADSTTUSX86_H__
#define __MACHOTHREADSTTUSX86_H__

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

#endif /* __MACHOTHREADSTTUSX86_H__ */
