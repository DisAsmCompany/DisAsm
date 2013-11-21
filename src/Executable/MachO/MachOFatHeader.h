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
#ifndef __MACHOFATHEADER_H__40AFB9CC_4CC1_4A18_9FCA_1093D5AE0027__
#define __MACHOFATHEADER_H__40AFB9CC_4CC1_4A18_9FCA_1093D5AE0027__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { MachOFatHeaderCpuType = 0 };
enum { MachOFatHeaderOffset  = 8 };

static const SDFElement MachOFatHeader[] =
{
	{"Mach-O Fat Header"},
	{"CpuType   ", kUnsigned, 4, 1, _MachOCPUType},
	{"CpuSubType", kUnsigned, 4, 1},
	{"Offset    ", kUnsigned, 4, 1},
	{"Size      ", kUnsigned, 4, 1},
	{"Align     ", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOFATHEADER_H__40AFB9CC_4CC1_4A18_9FCA_1093D5AE0027__ */
