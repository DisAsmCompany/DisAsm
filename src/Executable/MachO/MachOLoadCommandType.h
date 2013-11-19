/*
 * Filename: MachOLoadCommandType.h
 * Author:   DisAsmCompany
 * Date:     14/10/2013
 *
 * Description: Mach-O Load Command types
 *             (Segment, Dyld, etc)
 *              
 *
 */

#pragma once
#ifndef __MACHOLOADCOMMANDTYPE_H__
#define __MACHOLOADCOMMANDTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum MachOLoadCommandType_t
{
	kMachOLoadCommandSegment32     = 0x00000001UL,
	kMachOLoadCommandSegment64     = 0x00000019UL,
	kMachOLoadCommandThread        = 0x00000004UL,
	kMachOLoadCommandUnixThread    = 0x00000005UL,
	kMachOLoadCommandSymTab        = 0x00000002UL,
	kMachOLoadCommandLoadDylib     = 0x0000000CUL,
	kMachOLoadCommandIdDylib       = 0x0000000DUL,
	kMachOLoadCommandReexportDylib = 0x8000001FUL,
	kMachOLoadCommandUUID          = 0x0000001BUL,
}
MachOLoadCommandType;

static const SDFEnum _MachOLoadCommandType[] =
{
	{"LC_SEGMENT",        kMachOLoadCommandSegment32},
	{"LC_SEGMENT_64",     kMachOLoadCommandSegment64},
	{"LC_THREAD",         kMachOLoadCommandThread},
	{"LC_UNIXTHREAD",     kMachOLoadCommandUnixThread},
	{"LC_SYMTAB",         kMachOLoadCommandSymTab},
	{"LC_LOAD_DYLIB",     kMachOLoadCommandLoadDylib},
	{"LC_ID_DYLIB",       kMachOLoadCommandIdDylib},
	{"LC_REEXPORT_DYLIB", kMachOLoadCommandReexportDylib},
	{"LC_UUID",           kMachOLoadCommandUUID},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOLOADCOMMANDTYPE_H__ */
