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

#define MachOFatHeaderCpuType    0
#define MachOFatHeaderOffset     8

static const SDFElement MachOFatHeader[] =
{
	{"Mach-O Fat Header"},
	{"CpuType   ", kUnsigned, 4, 1, MachOCPUType},
	{"CpuSubType", kUnsigned, 4, 1},
	{"Offset    ", kUnsigned, 4, 1},
	{"Size      ", kUnsigned, 4, 1},
	{"Align     ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __MACHOFATHEADER_H__ */
