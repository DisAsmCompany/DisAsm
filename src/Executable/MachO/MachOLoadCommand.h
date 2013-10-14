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

#define MachOLoadCommandCommand     0
#define MachOLoadCommandCommandSize 4

static const SDFElement MachOLoadCommand[] =
{
	{"Mach-O Load Command"},
	{"Command    ", kUnsigned, 4, 1},
	{"CommandSize", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __MACHOLOADCOMMAND_H__ */
