/*
 * Filename: MachOFatHeader.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O fat header
 *              (universal "fat" binary
 *              that contains several
 *              binaries for multiple architectures)
 */

#pragma once
#ifndef __MACHOFATHEADER_H__
#define __MACHOFATHEADER_H__

typedef struct MachOFatHeader_t
{
	uint32_t CpuType;
	uint32_t CpuSubType;
	uint32_t Offset;
	uint32_t Size;
	uint32_t Align;
}
MachOFatHeader;

#endif /* __MACHOFATHEADER_H__ */
