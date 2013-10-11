/*
 * Filename: MachOHeader64.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O header 64
 *
 *
 *
 */

#pragma once
#ifndef __MACHOHEADER64_H__
#define __MACHOHEADER64_H__

#define MachOHeader64CountCommands 1

static const SDFElement MachOHeader64[] =
{
	{"Mach-O Header"},
	{"Magic        ", 0, kUnsigned, 4, 1},
	{"CpuType      ", 0, kUnsigned, 4, 1},
	{"CpuSubType   ", 0, kUnsigned, 4, 1},
	{"FileType     ", 0, kUnsigned, 4, 1},
	{"CountCommands", MachOHeaderCountCommands, kUnsigned, 4, 1},
	{"SizeCommands ", 0, kUnsigned, 4, 1},
	{"Flags        ", 0, kUnsigned, 4, 1},
	{"Reserved     ", 0, kReserved, 4, 1},
};
static const uint32_t MachOHeader64Size = sizeof(MachOHeader64) / sizeof(MachOHeader64[0]);

#endif /* __MACHOHEADER64_H__ */
