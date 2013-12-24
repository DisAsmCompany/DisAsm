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
	{"ET_NONE", 0x0000, 0},
	{"ET_REL",  0x0001, 0},
	{"ET_EXEC", 0x0002, 0},
	{"ET_DYN",  0x0003, 0},
	{"ET_CORE", 0x0004, 0},
	{NULL, 0, 0}
};

#endif /* __ELFTYPE_H__F626A937_9701_42EA_ADA2_61F31C7BF3C2__ */
