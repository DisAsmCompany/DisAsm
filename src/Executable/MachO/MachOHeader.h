/*
 * Filename: MachOHeader.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O header
 *
 *
 *
 */

#pragma once
#ifndef __MACHOHEADER_H__
#define __MACHOHEADER_H__

typedef struct MachOHeader_t
{
	uint32_t Magic;
	uint32_t CpuType;
	uint32_t CpuSubType;
	uint32_t FileType;
	uint32_t CountCommands;
	uint32_t SizeCommands;
	uint32_t Flags;
}
MachOHeader;

#endif /* __MACHOHEADER_H__ */
