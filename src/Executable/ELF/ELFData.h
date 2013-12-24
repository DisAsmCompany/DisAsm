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
#ifndef __ELFDATA_H__1D362BF8_5FCF_48F9_A087_0B94E3DE0C4E__
#define __ELFDATA_H__1D362BF8_5FCF_48F9_A087_0B94E3DE0C4E__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFData[] =
{
	{"ELFDATANONE", 0, 0},
	{"ELFDATA2LSB", 1, 0},
	{"ELFDATA2MSB", 2, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFDATA_H__1D362BF8_5FCF_48F9_A087_0B94E3DE0C4E__ */
