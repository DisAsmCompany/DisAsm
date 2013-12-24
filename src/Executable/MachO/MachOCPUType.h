/*
 * Filename: MachOCPUType.h
 * Author:   DisAsmCompany
 * Date:     14/10/2013
 *
 * Description: Mach-OCPU Type (x86, x64, PowerPC, etc)
 *
 *              
 *
 */

#pragma once
#ifndef __MACHOCPUTYPE_H__24F728A8_B1A2_4076_A123_02002AA955DF__
#define __MACHOCPUTYPE_H__24F728A8_B1A2_4076_A123_02002AA955DF__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum MachOCPUType_t
{
	kMachOCPUType64  = 0x01000000UL,
	kMachOCPUTypeX86 = 0x00000007UL,
	kMachOCPUTypeX64 = kMachOCPUTypeX86 | kMachOCPUType64
}
MachOCPUType;

static const SDFEnum _MachOCPUType[] =
{
	{"CPU_TYPE_MC680x0",   0x00000006UL, 0},
	{"CPU_TYPE_X86",       kMachOCPUTypeX86, 0},
	{"CPU_TYPE_X86_64",    kMachOCPUTypeX64, 0},
	{"CPU_TYPE_ARM",       0x0000000CUL, 0},
	{"CPU_TYPE_POWERPC",   0x00000012UL, 0},
	{"CPU_TYPE_POWERPC64", 0x01000012UL, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOCPUTYPE_H__24F728A8_B1A2_4076_A123_02002AA955DF__ */
