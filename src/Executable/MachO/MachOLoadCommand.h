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

#define MachOLoadCommandCommand     2
#define MachOLoadCommandCommandSize 1

static const SDFElement MachOLoadCommand[] =
{
	{"Mach-O Load Command"},
	{"Command    ", MachOLoadCommandCommand, kUnsigned, 4, 1},
	{"CommandSize", MachOLoadCommandCommandSize, kUnsigned, 4, 1},
};
static const uint32_t MachOLoadCommandSize = sizeof(MachOLoadCommand) / sizeof(MachOLoadCommand[0]);

#endif /* __MACHOLOADCOMMAND_H__ */
