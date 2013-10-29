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

static const SDFElement MachOHeader64[] =
{
	{"Mach-O Header 64"},
	{"Magic        ", kUnsigned, 4, 1},
	{"CpuType      ", kUnsigned, 4, 1, _MachOCPUType},
	{"CpuSubType   ", kUnsigned, 4, 1},
	{"FileType     ", kUnsigned, 4, 1, MachOFileType},
	{"CountCommands", kUnsigned, 4, 1},
	{"SizeCommands ", kUnsigned, 4, 1},
	{"Flags        ", kUnsigned, 4, 1, MachOHeaderFlags},
	{"Reserved     ", kReserved, 4, 1},
	{NULL}
};

#endif /* __MACHOHEADER64_H__ */
