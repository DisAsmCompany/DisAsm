/*
 * Filename: MachOLoadCommand.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O load command
 *
 *
 *
 */

#pragma once
#ifndef __MACHOLOADCOMMAND_H__
#define __MACHOLOADCOMMAND_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { MachOLoadCommandCommand     = 0 };
enum { MachOLoadCommandCommandSize = 4 };

static const SDFElement MachOLoadCommand[] =
{
	{"Mach-O Load Command"},
	{"Command    ", kUnsigned, 4, 1, _MachOLoadCommandType},
	{"CommandSize", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOLOADCOMMAND_H__ */
