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
#ifndef __ELFVERSION_H__
#define __ELFVERSION_H__

static const SDFEnum ELFVersion[] =
{
	{"EV_NONE",    0x0000},
	{"EV_CURRENT", 0x0001},
	{NULL}
};

#endif /* __ELFVERSION_H__ */
