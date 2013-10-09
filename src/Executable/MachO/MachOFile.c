/*
 * Filename: MachOFile.c
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O file abstraction
 *
 *
 *
 */

#include "../../DisAsm/DisAsm"
#include "../Executable"

uint32_t LEtoBE(uint32_t value)
{
	return 
	((value & 0x000000FF) << 24) |
	((value & 0x0000FF00) << 8)  |
	((value & 0x00FF0000) >> 8)  |
	((value & 0xFF000000) >> 24);
}

#define MachOFatHeader_CpuType    0
#define MachOFatHeader_CpuSubType 1
#define MachOFatHeader_Offset     2
#define MachOFatHeader_Size       3
#define MachOFatHeader_Align      4

SDFElement _MachOFatHeader[] =
{
	{"Mach-O Fat Header"},
	{"CpuType   ", MachOFatHeader_CpuType},
	{"CpuSubType", MachOFatHeader_CpuSubType},
	{"Offset    ", MachOFatHeader_Offset},
	{"Size      ", MachOFatHeader_Size},
	{"Align     ", MachOFatHeader_Align},
};

uint32_t MachOFatHeaderSize = sizeof(_MachOFatHeader) / sizeof(_MachOFatHeader[0]);

int MachOExecutableProcess(ExecutableContext * pContext)
{
	return 0;
}

int MachOFileCreate(ExecutableContext * pContext)
{
	uint32_t magic = 0;
	uint32_t count = 0;
	uint32_t i = 0;
	if (0 == ReaderSeek(pContext->hReader, 0))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &magic, sizeof(uint32_t)))
	{
		return 0;
	}
	magic = LEtoBE(magic);
	if (0xCAFEBABEUL == magic)
	{
		if (0 == ReaderRead(pContext->hReader, &count, sizeof(uint32_t)))
		{
			return 0;
		}
		count = LEtoBE(count);
		if (count > 0)
		{
			for (i = 0; i < count; ++i)
			{
				HSDF header = SDFCreate(_MachOFatHeader, MachOFatHeaderSize, pContext->hReader);
				printf("header %d :\n", i);
				SDFPrint(header);
				
				SDFDestroy(header);
			}
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
