/*
 * Filename: MachOMemoryProtection.h
 * Author:   DisAsmCompany
 * Date:     21/10/2013
 *
 * Description: Mach-O Memory Protection Flags
 *              from mach/vm_prot.h
 *              
 *
 */

#pragma once
#ifndef __MACHOMEMORYPROTECTION_H__
#define __MACHOMEMORYPROTECTION_H__

static const SDFEnum MachOMemoryProtection[] =
{
	{"VM_PROT_NONE",      0x00000000UL, 0x00000007UL},
	{"VM_PROT_READ",      0x00000001UL, 0x00000001UL},
	{"VM_PROT_WRITE",     0x00000002UL, 0x00000002UL},
	{"VM_PROT_EXECUTE",   0x00000004UL, 0x00000004UL},
	{"VM_PROT_NO_CHANGE", 0x00000008UL, 0x00000008UL},
	{"VM_PROT_COPY",      0x00000010UL, 0x00000010UL},
	{"VM_PROT_TRUSTED",   0x00000020UL, 0x00000020UL},
	{NULL}
};

#endif /* __MACHOMEMORYPROTECTION_H__ */
