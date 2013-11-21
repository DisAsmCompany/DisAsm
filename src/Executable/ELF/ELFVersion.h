/*
 * Filename: ELFVersion.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF version
 *
 *
 *
 */

#pragma once
#ifndef __ELFVERSION_H__1A9E211B_28A1_4CC3_8CDF_8967E216F51D__
#define __ELFVERSION_H__1A9E211B_28A1_4CC3_8CDF_8967E216F51D__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFVersion[] =
{
	{"EV_NONE",    0x0000},
	{"EV_CURRENT", 0x0001},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFVERSION_H__1A9E211B_28A1_4CC3_8CDF_8967E216F51D__ */
