/*
 * Filename: ELFType.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF type (executable, object, etc)
 *
 *
 *
 */

#pragma once
#ifndef __ELFTYPE_H__F626A937_9701_42EA_ADA2_61F31C7BF3C2__
#define __ELFTYPE_H__F626A937_9701_42EA_ADA2_61F31C7BF3C2__

static const SDFEnum ELFType[] =
{
	{"ET_NONE", 0x0000},
	{"ET_REL",  0x0001},
	{"ET_EXEC", 0x0002},
	{"ET_DYN",  0x0003},
	{"ET_CORE", 0x0004},
	{NULL}
};

#endif /* __ELFTYPE_H__F626A937_9701_42EA_ADA2_61F31C7BF3C2__ */
