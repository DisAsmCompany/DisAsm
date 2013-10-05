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
	((value & 0x0000FF00) << 8) |
	((value & 0x00FF0000) >> 8) |
	((value & 0xFF000000) >> 24);
}

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
			MachOFatHeader *headers = malloc(sizeof(MachOFatHeader) * count);
			if (NULL == headers)
			{
				return 0;
			}
			if (0 == ReaderRead(pContext->hReader, headers, sizeof(MachOFatHeader) * count))
			{
				return 0;
			}
			for (i = 0; i < count; ++i)
			{
				printf("Mach-O Fat Header %d :\n", i);
				printf("CpuType    : 0x%08X\n", headers[i].CpuType);
				printf("CpuSubType : 0x%08X\n", headers[i].CpuSubType);
				printf("Offset     : 0x%08X\n", headers[i].Offset);
				printf("Size       : 0x%08X\n", headers[i].Size);
				printf("Align      : 0x%08X\n", headers[i].Align);
				printf("\n");
			}
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
