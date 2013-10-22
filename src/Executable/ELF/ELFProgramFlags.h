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
#ifndef __ELFPROGRAMFLAGS_H__
#define __ELFPROGRAMFLAGS_H__

static const SDFEnum ELFProgramFlags[] =
{
	{"PF_X", 0x0001, 0x0001},
	{"PF_W", 0x0002, 0x0002},
	{"PF_R", 0x0004, 0x0004},
	{NULL}
};

#endif /* __ELFPROGRAMFLAGS_H__ */
