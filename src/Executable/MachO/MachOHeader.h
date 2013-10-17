/*
 * Filename: MachOHeader.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O header
 *
 *
 *
 */

#pragma once
#ifndef __MACHOHEADER_H__
#define __MACHOHEADER_H__

static const uint32_t MachOHeaderCountCommands = 16;

static const SDFElement MachOHeader[] =
{
	{"Mach-O Header"},
	{"Magic        ", kUnsigned, 4, 1},
	{"CpuType      ", kUnsigned, 4, 1, MachOCPUType},
	{"CpuSubType   ", kUnsigned, 4, 1},
	{"FileType     ", kUnsigned, 4, 1},
	{"CountCommands", kUnsigned, 4, 1},
	{"SizeCommands ", kUnsigned, 4, 1},
	{"Flags        ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __MACHOHEADER_H__ */
