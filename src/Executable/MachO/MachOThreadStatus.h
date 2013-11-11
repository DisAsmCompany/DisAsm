
/*
 * Filename: MachOThreadStatus.h
 * Author:   DisAsmCompany
 * Date:     11/11/2013
 *
 * Description: Mach-O thread status
 *
 *
 *
 */

#pragma once
#ifndef __MACHOTHREADSTTUSX_H__
#define __MACHOTHREADSTTUSX_H__

static const SDFElement MachOThreadStatus[] =
{
	{"Mach-O Thread Status"},
	{"Flavor", kUnsigned, 4, 1},
	{"Count ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __MACHOTHREADSTTUSX_H__ */
