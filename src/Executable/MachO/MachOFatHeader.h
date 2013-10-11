/*
 * Filename: MachOFatHeader.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O fat header
 *              (universal "fat" binary
 *              that contains several
 *              binaries for multiple architectures)
 */

#pragma once
#ifndef __MACHOFATHEADER_H__
#define __MACHOFATHEADER_H__

#define MachOFatHeaderCpuType    1
#define MachOFatHeaderOffset     2

static const SDFElement MachOFatHeader[] =
{
	{"Mach-O Fat Header"},
	{"CpuType   ", MachOFatHeaderCpuType, kUnsigned, 4, 1},
	{"CpuSubType", 0, kUnsigned, 4, 1},
	{"Offset    ", MachOFatHeaderOffset, kUnsigned, 4, 1},
	{"Size      ", 0, kUnsigned, 4, 1},
	{"Align     ", 0, kUnsigned, 4, 1},
};
static const uint32_t MachOFatHeaderSize = sizeof(MachOFatHeader) / sizeof(MachOFatHeader[0]);

#endif /* __MACHOFATHEADER_H__ */
