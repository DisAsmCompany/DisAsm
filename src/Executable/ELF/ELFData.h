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

static const SDFEnum ELFData[] =
{
	{"ELFDATANONE", 0},
	{"ELFDATA2LSB", 1},
	{"ELFDATA2MSB", 2},
	{NULL}
};

#endif /* __ELFDATA_H__ */
