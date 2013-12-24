/*
* Filename: PESubsystem.h
* Author:   DisAsmCompany
* Date:     14/10/2013
*
* Description: PE Subsystem (Console, GUI, POSIX, etc)
*              
*              
*
*/

#pragma once
#ifndef __PESUBSYSTEM_H__4B2BEA35_A4B5_4DEC_8C66_E5791FDD7381__
#define __PESUBSYSTEM_H__4B2BEA35_A4B5_4DEC_8C66_E5791FDD7381__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum PESubsystem[] =
{
	{"IMAGE_SUBSYSTEM_UNKNOWN",                  0x0000, 0},
	{"IMAGE_SUBSYSTEM_NATIVE",                   0x0001, 0},
	{"IMAGE_SUBSYSTEM_WINDOWS_GUI",              0x0002, 0},
	{"IMAGE_SUBSYSTEM_WINDOWS_CUI",              0x0003, 0},
	{"IMAGE_SUBSYSTEM_OS2_CUI",                  0x0005, 0},
	{"IMAGE_SUBSYSTEM_POSIX_CUI",                0x0007, 0},
	{"IMAGE_SUBSYSTEM_NATIVE_WINDOWS",           0x0008, 0},
	{"IMAGE_SUBSYSTEM_WINDOWS_CE_GUI",           0x0009, 0},
	{"IMAGE_SUBSYSTEM_EFI_APPLICATION",          0x000A, 0},
	{"IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER",  0x000B, 0},
	{"IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER",       0x000C, 0},
	{"IMAGE_SUBSYSTEM_EFI_ROM",                  0x000D, 0},
	{"IMAGE_SUBSYSTEM_XBOX",                     0x000E, 0},
	{"IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION", 0x0010, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PESUBSYSTEM_H__4B2BEA35_A4B5_4DEC_8C66_E5791FDD7381__ */
