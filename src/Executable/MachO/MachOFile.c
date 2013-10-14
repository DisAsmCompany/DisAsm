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

#include "MachOCPUType.h"
#include "MachOHeader.h"
#include "MachOHeader64.h"
#include "MachOFatHeader.h"
#include "MachOLoadCommand.h"
#include "MachOSegment.h"
#include "MachOSegment64.h"
#include "MachOSection.h"
#include "MachOSection64.h"

uint32_t LEtoBE(uint32_t value)
{
	return 
	((value & 0x000000FF) << 24) |
	((value & 0x0000FF00) << 8)  |
	((value & 0x00FF0000) >> 8)  |
	((value & 0xFF000000) >> 24);
}

typedef struct MachOFileContext_t
{
	uint32_t nFatHeaders;
	HSDF * phFatHeaders;
	HSDF * phMachHeaders;
	uint32_t nCommands;
}
MachOFileContext;

#undef THIS
#define THIS ((MachOFileContext*)(pContext->pPrivate))

int MachOExecutableProcess(ExecutableContext * pContext)
{
	return 0;
}

int MachOFileCreate(ExecutableContext * pContext)
{
	uint32_t magic = 0;
	uint32_t i = 0, j = 0, k = 0;
	
	MachOFileContext * pMachOFileContext = (MachOFileContext*) malloc(sizeof(MachOFileContext));
	if (NULL == pMachOFileContext)
	{
		return 0;
	}
	memset(pMachOFileContext, 0, sizeof(MachOFileContext));
	pContext->pPrivate = pMachOFileContext;
	
	if (0 == ReaderSeek(pContext->hReader, 0))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &magic, sizeof(uint32_t)))
	{
		return 0;
	}
	if (0xCAFEBABEUL == LEtoBE(magic))
	{
		if (0 == ReaderRead(pContext->hReader, &THIS->nFatHeaders, sizeof(uint32_t)))
		{
			return 0;
		}
		THIS->nFatHeaders = LEtoBE(THIS->nFatHeaders);
		if (0 == THIS->nFatHeaders)
		{
			return 0;
		}
		THIS->phFatHeaders = (HSDF*) malloc(sizeof(HSDF) * THIS->nFatHeaders);
		THIS->phMachHeaders = (HSDF*) malloc(sizeof(HSDF) * THIS->nFatHeaders);
		for (i = 0; i < THIS->nFatHeaders; ++i)
		{
			THIS->phFatHeaders[i] = SDFCreate(MachOFatHeader, pContext->hReader);
			SDFPrint(THIS->phFatHeaders[i]);
		}
		for (i = 0; i < THIS->nFatHeaders; ++i)
		{
			uint32_t offset = LEtoBE(SDFReadUInt32(THIS->phFatHeaders[i], MachOFatHeaderOffset));
			uint32_t CpuType = LEtoBE(SDFReadUInt32(THIS->phFatHeaders[i], MachOFatHeaderCpuType));
			
			if (0 == ReaderSeek(pContext->hReader, offset))
			{
				return 0;
			}
			if (CpuType == 0x07)
			{
				THIS->phMachHeaders[i] = SDFCreate(MachOHeader, pContext->hReader);
			}
			else 
			{
				THIS->phMachHeaders[i] = SDFCreate(MachOHeader64, pContext->hReader);
			}

			SDFPrint(THIS->phMachHeaders[i]);
			
			THIS->nCommands = SDFReadUInt32(THIS->phMachHeaders[i], MachOHeaderCountCommands);
			for (j = 0; j < THIS->nCommands; ++j)
			{
				uint32_t count, type;
				HSDF hCommand = SDFCreate(MachOLoadCommand, pContext->hReader);
				type = SDFReadUInt32(hCommand, MachOLoadCommandCommand);
				count = SDFReadUInt32(hCommand, MachOLoadCommandCommandSize) - SDFSizeInBytes(MachOLoadCommand);
				
				switch (type)
				{
					case 0x00000001UL: printf("Segment32\n"); break;
					case 0x00000019UL: printf("Segment64\n"); break;
					case 0x0000000CUL: printf("LoadDylib\n"); break;
					default : break;
				}
				
				SDFPrint(hCommand);
				
				if (0x00000001UL == type)
				{
					HSDF hSegment = SDFCreate(MachOSegment, pContext->hReader);
					uint32_t NumberOfSections = SDFReadUInt32(hSegment, MachOSegmentNumberOfSections);
					SDFPrint(hSegment);
					SDFDestroy(hSegment);
					count -= SDFSizeInBytes(MachOSegment);
					
					for (k = 0; k < NumberOfSections; ++k)
					{
						HSDF hSection = SDFCreate(MachOSection, pContext->hReader);
						SDFPrint(hSection);
						SDFDestroy(hSection);
						count -= SDFSizeInBytes(MachOSection);
					}
				}
				if (0x00000019UL == type)
				{
					HSDF hSegment = SDFCreate(MachOSegment64, pContext->hReader);
					uint32_t NumberOfSections = SDFReadUInt32(hSegment, MachOSegment64NumberOfSections);
					SDFPrint(hSegment);
					SDFDestroy(hSegment);
					count -= SDFSizeInBytes(MachOSegment64);
					
					for (k = 0; k < NumberOfSections; ++k)
					{
						HSDF hSection = SDFCreate(MachOSection64, pContext->hReader);
						SDFPrint(hSection);
						SDFDestroy(hSection);
						count -= SDFSizeInBytes(MachOSection64);
					}
				}
				ReaderSkip(pContext->hReader, count);
				
				SDFDestroy(hCommand);
			}
		}
	}
	return 0;
}
