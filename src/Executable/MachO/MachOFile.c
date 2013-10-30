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
#include "MachOHeaderFlags.h"
#include "MachOFileType.h"
#include "MachOHeader.h"
#include "MachOHeader64.h"
#include "MachOFatHeader.h"
#include "MachOLoadCommand.h"
#include "MachOMemoryProtection.h"
#include "MachOSegmentAttributes.h"
#include "MachOSegment.h"
#include "MachOSegment64.h"
#include "MachOSectionAttributes.h"
#include "MachOSection.h"
#include "MachOSection64.h"
#include "MachODylib.h"
#include "MachOSymTab.h"
#include "MachOThreadStatusX86.h"

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
	HSDF * phFatHeaders;
	HSDF * phMachHeaders;
	uint32_t nCommands;
}
MachOFileContext;

#undef THIS
#define THIS ((MachOFileContext*)(pContext->pPrivate))

uint32_t MachOProcessCommandSegment(ExecutableContext * pContext, uint8_t x64)
{
	uint32_t i = 0;
	uint32_t count = 0;
	const SDFElement * Segment = x64 ? MachOSegment64 : MachOSegment;
	const SDFElement * Section = x64 ? MachOSection64 : MachOSection;
	uint32_t NumberOfSections = 0;
	HSDF hSegment = NULL;
	
	CHECK_CALL(hSegment = SDFCreate(Segment, pContext->hReader));
	NumberOfSections = SDFReadUInt32(hSegment, x64 ? kMachOSegment64NumberOfSections : kMachOSegmentNumberOfSections);
	SDFPrint(hSegment);
	SDFDestroy(hSegment);
	count += SDFSizeInBytes(Segment);
	
	for (i = 0; i < NumberOfSections; ++i)
	{
		HSDF hSection = SDFCreate(Section, pContext->hReader);
		SDFPrint(hSection);
		SDFDestroy(hSection);
		count += SDFSizeInBytes(Section);
	}
	return count;
}

uint32_t MachOProcessCommandDylib(ExecutableContext * pContext)
{
	uint32_t count = 0;
	uint32_t i = 0;
	HSDF hDylib = SDFCreate(MachODylib, pContext->hReader);
	SDFPrint(hDylib);
	SDFDestroy(hDylib);
	count += SDFSizeInBytes(MachODylib);
	for (i = 0; i < count; ++i)
	{
		char c;
		ReaderRead(pContext->hReader, &c, 1);
		if (0 == c || '\n' == c || '\r' == c)
		{
			break;
		}
		printf("%c", c);
	}
	count += i + 1;
	printf("\n");
	return count;
}

uint32_t MachOProcessCommandUUID(ExecutableContext * pContext)
{
	unsigned char uuid[16];
	CHECK_CALL(ReaderRead(pContext->hReader, uuid, 16));
	printf("UUID : %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\n", 
		   uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7], uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
	return 16;
}

uint32_t MachOProcessCommandSymTab(ExecutableContext * pContext)
{
	HSDF hSymTab = SDFCreate(MachOSymTab, pContext->hReader);
	SDFPrint(hSymTab);
	SDFDestroy(hSymTab);
	return SDFSizeInBytes(MachOSymTab);
}

uint32_t MachOProcessCommandThread(ExecutableContext * pContext)
{
	
	return 0;
}

void MachOFileDestroy(ExecutableContext * pContext)
{
	uint32_t i = 0;
	for (i = 0; i < pContext->nObjects; ++i)
	{
		SDFDestroy(THIS->phFatHeaders[i]);
		SDFDestroy(THIS->phMachHeaders[i]);
	}
	free(THIS->phFatHeaders);
	free(THIS->phMachHeaders);
	free(THIS);
}

int MachOFileInit(ExecutableContext * pContext)
{
	uint32_t magic = 0;
	uint32_t i = 0, j = 0;
	
	CHECK_CALL(ReaderSeek(pContext->hReader, 0));
	CHECK_CALL(ReaderRead(pContext->hReader, &magic, sizeof(uint32_t)));
	if (kMachOFatMagicBE != magic && kMachOFatMagicLE != magic)
	{
		return 0;
	}
	CHECK_CALL(ReaderRead(pContext->hReader, &pContext->nObjects, sizeof(uint32_t)));
	if (0 == (pContext->nObjects = LEtoBE(pContext->nObjects)))
	{
		return 0;
	}
	CHECK_ALLOC(pContext->pObjects = (ExecutableObject*) malloc(sizeof(ExecutableObject) * pContext->nObjects));
	CHECK_ALLOC(THIS->phFatHeaders = (HSDF*) malloc(sizeof(HSDF) * pContext->nObjects));
	CHECK_ALLOC(THIS->phMachHeaders = (HSDF*) malloc(sizeof(HSDF) * pContext->nObjects));
	for (i = 0; i < pContext->nObjects; ++i)
	{
		CHECK_CALL(THIS->phFatHeaders[i] = SDFCreate(MachOFatHeader, pContext->hReader));
		SDFSetEndian(THIS->phFatHeaders[i], kMachOFatMagicBE == magic);
		SDFPrint(THIS->phFatHeaders[i]);
	}
	for (i = 0; i < pContext->nObjects; ++i)
	{
		uint32_t Offset = SDFReadUInt32(THIS->phFatHeaders[i], MachOFatHeaderOffset);
		uint32_t CpuType = SDFReadUInt32(THIS->phFatHeaders[i], MachOFatHeaderCpuType);
		
		CHECK_CALL(ReaderSeek(pContext->hReader, Offset));
		CHECK_CALL(THIS->phMachHeaders[i] = SDFCreate(CpuType & kMachOCPUType64 ? MachOHeader64 : MachOHeader, pContext->hReader));
		SDFPrint(THIS->phMachHeaders[i]);
		
		THIS->nCommands = SDFReadUInt32(THIS->phMachHeaders[i], MachOHeaderCountCommands);
		for (j = 0; j < THIS->nCommands; ++j)
		{
			uint32_t count, type;
			HSDF hCommand = NULL;
			CHECK_CALL(hCommand = SDFCreate(MachOLoadCommand, pContext->hReader));
			type = SDFReadUInt32(hCommand, MachOLoadCommandCommand);
			count = SDFReadUInt32(hCommand, MachOLoadCommandCommandSize) - SDFSizeInBytes(MachOLoadCommand);
			SDFPrint(hCommand);
			
			switch (type)
			{
				case kMachOLoadCommandSegment32:
					count -= MachOProcessCommandSegment(pContext, 0);
					break;
				case kMachOLoadCommandSegment64:
					count -= MachOProcessCommandSegment(pContext, 1);
					break;
				case kMachOLoadCommandLoadDylib:
				case kMachOLoadCommandIdDylib:
				case kMachOLoadCommandReexportDylib:
					/*count -= MachOProcessCommandDylib(pContext);*/
					break;
				case kMachOLoadCommandUUID:
					count -= MachOProcessCommandUUID(pContext);
					break;
				case kMachOLoadCommandSymTab:
					count -= MachOProcessCommandSymTab(pContext);
					break;
				case kMachOLoadCommandUnixThread:
				case kMachOLoadCommandThread:
					count -= MachOProcessCommandThread(pContext);
					break;
				default :
					break;
			}
			ReaderSkip(pContext->hReader, count);
			SDFDestroy(hCommand);
		}
	}
	return 0;
}

int MachOFileCreate(ExecutableContext * pContext)
{
	CHECK_ALLOC(pContext->pPrivate = calloc(1, sizeof(MachOFileContext)));
	if (0 == MachOFileInit(pContext))
	{
		MachOFileDestroy(pContext);
		return 0;
	}
	pContext->pDestroy = MachOFileDestroy;
	return 1;
}
