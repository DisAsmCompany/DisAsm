/*
 * Filename: ELFProgramFlags.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Program Flags
 *
 *
 *
 */

#pragma once
#ifndef __ELFPROGRAMFLAGS_H__1C9F97CA_B730_441B_9126_98DA5D11143B__
#define __ELFPROGRAMFLAGS_H__1C9F97CA_B730_441B_9126_98DA5D11143B__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFProgramFlags[] =
{
	{"PF_X", 0x0001, 0x0001},
	{"PF_W", 0x0002, 0x0002},
	{"PF_R", 0x0004, 0x0004},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFPROGRAMFLAGS_H__1C9F97CA_B730_441B_9126_98DA5D11143B__ */
