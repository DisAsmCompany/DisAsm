/*
 * Filename: ELFClass.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF class (32 or 64)
 *
 *
 *
 */

#pragma once
#ifndef __ELFCLASS_H__7187089F_C443_4017_BA6C_05E0B86B32EA__
#define __ELFCLASS_H__7187089F_C443_4017_BA6C_05E0B86B32EA__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFClass[] =
{
	{"ELFCLASSNONE", 0, 0},
	{"ELFCLASS32",   1, 0},
	{"ELFCLASS64",   2, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFCLASS_H__7187089F_C443_4017_BA6C_05E0B86B32EA__ */
