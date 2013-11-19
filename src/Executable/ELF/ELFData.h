/*
 * Filename: ELFData.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF data (LSB, MSB)
 *
 *
 *
 */

#pragma once
#ifndef __ELFDATA_H__
#define __ELFDATA_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFData[] =
{
	{"ELFDATANONE", 0},
	{"ELFDATA2LSB", 1},
	{"ELFDATA2MSB", 2},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFDATA_H__ */
