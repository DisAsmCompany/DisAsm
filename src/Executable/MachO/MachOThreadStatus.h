
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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFElement MachOThreadStatus[] =
{
	{"Mach-O Thread Status"},
	{"Flavor", kUnsigned, 4, 1},
	{"Count ", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOTHREADSTTUSX_H__ */
