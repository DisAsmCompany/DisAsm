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
#ifndef __ELFCLASS_H__
#define __ELFCLASS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFClass[] =
{
	{"ELFCLASSNONE", 0},
	{"ELFCLASS32",   1},
	{"ELFCLASS64",   2},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFCLASS_H__ */
