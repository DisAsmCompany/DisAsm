/*
 * Filename: MachOSegmentAttributes.h
 * Author:   DisAsmCompany
 * Date:     21/10/2013
 *
 * Description: Mach-O Segment Flags
 *
 *              
 *
 */

#pragma once
#ifndef __MACHOSEGMENTATTRIBUTES_H__
#define __MACHOSEGMENTATTRIBUTES_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum MachOSegmentAttributes[] =
{
	{"SG_HIGHVM",              0x00000001UL, 0x00000001UL},
	{"SG_FVMLIB",              0x00000002UL, 0x00000002UL},
	{"SG_NORELOC",             0x00000004UL, 0x00000004UL},
	{"SG_PROTECTED_VERSION_1", 0x00000008UL, 0x00000008UL},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSEGMENTATTRIBUTES_H__ */
