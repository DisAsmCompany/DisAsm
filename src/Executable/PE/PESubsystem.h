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
	{"IMAGE_SUBSYSTEM_UNKNOWN",                  0x0000},
	{"IMAGE_SUBSYSTEM_NATIVE",                   0x0001},
	{"IMAGE_SUBSYSTEM_WINDOWS_GUI",              0x0002},
	{"IMAGE_SUBSYSTEM_WINDOWS_CUI",              0x0003},
	{"IMAGE_SUBSYSTEM_OS2_CUI",                  0x0005},
	{"IMAGE_SUBSYSTEM_POSIX_CUI",                0x0007},
	{"IMAGE_SUBSYSTEM_NATIVE_WINDOWS",           0x0008},
	{"IMAGE_SUBSYSTEM_WINDOWS_CE_GUI",           0x0009},
	{"IMAGE_SUBSYSTEM_EFI_APPLICATION",          0x000A},
	{"IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER",  0x000B},
	{"IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER",       0x000C},
	{"IMAGE_SUBSYSTEM_EFI_ROM",                  0x000D},
	{"IMAGE_SUBSYSTEM_XBOX",                     0x000E},
	{"IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION", 0x0010},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PESUBSYSTEM_H__4B2BEA35_A4B5_4DEC_8C66_E5791FDD7381__ */
