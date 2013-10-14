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

#include "MachOMagic.h"
#include "MachOCPUType.h"
#include "MachOLoadCommandType.h"
#include "MachOHeader.h"
#include "MachOHeader64.h"
#include "MachOFatHeader.h"
#include "MachOLoadCommand.h"
#include "MachOSegment.h"
#include "MachOSegment64.h"
#include "MachOSection.h"
#include "MachOSection64.h"
#include "MachODylib.h"
#include "MachOSymTab.h"

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
	if (kMachOFatMagicBE == magic || kMachOFatMagicLE == magic)
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
			SDFSetEndian(THIS->phFatHeaders[i], kMachOFatMagicBE == magic);
			SDFPrint(THIS->phFatHeaders[i]);
		}
		for (i = 0; i < THIS->nFatHeaders; ++i)
		{
			uint32_t offset = SDFReadUInt32(THIS->phFatHeaders[i], MachOFatHeaderOffset);
			uint32_t CpuType = SDFReadUInt32(THIS->phFatHeaders[i], MachOFatHeaderCpuType);
			
			if (0 == ReaderSeek(pContext->hReader, offset))
			{
				return 0;
			}
			if (CpuType & 0x01000000UL)
			{
				THIS->phMachHeaders[i] = SDFCreate(MachOHeader64, pContext->hReader);
			}
			else 
			{
				THIS->phMachHeaders[i] = SDFCreate(MachOHeader, pContext->hReader);
			}

			SDFPrint(THIS->phMachHeaders[i]);
			
			THIS->nCommands = SDFReadUInt32(THIS->phMachHeaders[i], MachOHeaderCountCommands);
			for (j = 0; j < THIS->nCommands; ++j)
			{
				uint32_t count, type;
				HSDF hCommand = SDFCreate(MachOLoadCommand, pContext->hReader);
				type = SDFReadUInt32(hCommand, MachOLoadCommandCommand);
				count = SDFReadUInt32(hCommand, MachOLoadCommandCommandSize) - SDFSizeInBytes(MachOLoadCommand);
				
				SDFPrint(hCommand);
				
				if (kMachOLoadCommandSegment32 == type)
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
				if (kMachOLoadCommandSegment64 == type)
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
				if (kMachOLoadCommandLoadDylib == type || kMachOLoadCommandIdDylib == type || kMachOLoadCommandReexportDylib == type)
				{
					HSDF hDylib = SDFCreate(MachODylib, pContext->hReader);
					SDFPrint(hDylib);
					SDFDestroy(hDylib);
					count -= SDFSizeInBytes(MachODylib);
					for (k = 0; k < count; ++k)
					{
						char c;
						ReaderRead(pContext->hReader, &c, 1);
						if (0 == c || '\n' == c || '\r' == c)
						{
							break;
						}
						printf("%c", c);
					}
					count -= k + 1;
					printf("\n");
				}
				if (kMachOLoadCommandSymTab == type)
				{
					HSDF hSymTab = SDFCreate(MachOSymTab, pContext->hReader);
					SDFPrint(hSymTab);
					SDFDestroy(hSymTab);
					count -= SDFSizeInBytes(MachOSymTab);
				}
				ReaderSkip(pContext->hReader, count);
				
				SDFDestroy(hCommand);
			}
		}
	}
	return 0;
}
