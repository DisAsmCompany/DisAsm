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
#include "MachOThreadStatus.h"
#include "MachOThreadStatusX86.h"
#include "MachOThreadStatusX64.h"

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
#define THIS ((MachOFileContext*)(OBJ.pPrivate))

uint32_t MachOProcessCommandSegment(ExecutableContext * pContext, uint8_t x64)
{
	uint32_t base = 0;
	uint32_t i = 0;
	uint32_t count = 0;
	const SDFElement * Segment = x64 ? MachOSegment64 : MachOSegment;
	const SDFElement * Section = x64 ? MachOSection64 : MachOSection;
	uint32_t NumberOfSections = 0;
	HSDF hSegment = NULL;
	
	CHECK_CALL(hSegment = SDFCreate(Segment, pContext->hReader));
	NumberOfSections = SDFReadUInt32(hSegment, x64 ? kMachOSegment64NumberOfSections : kMachOSegmentNumberOfSections);
	SDFDebugPrint(hSegment);
	SDFDestroy(hSegment);
	count += SDFSizeInBytes(Segment);
	
	base = OBJ.nSections;
	OBJ.nSections += NumberOfSections;
	CHECK_ALLOC(OBJ.pSections = 
				realloc(OBJ.pSections, sizeof(ExecutableSection) * OBJ.nSections));
	
	for (i = 0; i < NumberOfSections; ++i)
	{
		HSDF hSection = SDFCreate(Section, pContext->hReader);
		SDFDebugPrint(hSection);
		
		if (x64)
		{
			OBJ.pSections[base + i].VirtualAddress = SDFReadUInt64(hSection, MachOSection64Address);
			OBJ.pSections[base + i].VirtualSize    = SDFReadUInt64(hSection, MachOSection64Size);
			OBJ.pSections[base + i].FileAddress    = SDFReadUInt32(hSection, MachOSection64Offset);
			OBJ.pSections[base + i].FileSize       = SDFReadUInt64(hSection, MachOSection64Size);
		}
		else 
		{
			OBJ.pSections[base + i].VirtualAddress = SDFReadUInt32(hSection, MachOSectionAddress);
			OBJ.pSections[base + i].VirtualSize    = SDFReadUInt32(hSection, MachOSectionSize);
			OBJ.pSections[base + i].FileAddress    = SDFReadUInt32(hSection, MachOSectionOffset);
			OBJ.pSections[base + i].FileSize       = SDFReadUInt32(hSection, MachOSectionSize);
		}
		
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
	SDFDebugPrint(hDylib);
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
	}
	count += i + 1;
	return count;
}

uint32_t MachOProcessCommandUUID(ExecutableContext * pContext)
{
	unsigned char uuid[16];
	CHECK_CALL(ReaderRead(pContext->hReader, uuid, 16));
	return 16;
}

uint32_t MachOProcessCommandSymTab(ExecutableContext * pContext)
{
	HSDF hSymTab = SDFCreate(MachOSymTab, pContext->hReader);
	SDFDebugPrint(hSymTab);
	SDFDestroy(hSymTab);
	return SDFSizeInBytes(MachOSymTab);
}

uint32_t MachOProcessCommandThreadX86(ExecutableContext * pContext)
{
	HSDF hThread = SDFCreate(MachOThreadStatusX86, pContext->hReader);
	SDFDebugPrint(hThread);
	OBJ.EntryPoint = ExecutableRVAToOffset(pContext, SDFReadUInt32(hThread, MachOThreadStatusX86EIP));
	SDFDestroy(hThread);
	return SDFSizeInBytes(MachOThreadStatusX86);
}

uint32_t MachOProcessCommandThreadX64(ExecutableContext * pContext)
{
	HSDF hThread = SDFCreate(MachOThreadStatusX64, pContext->hReader);
	SDFDebugPrint(hThread);
	OBJ.EntryPoint = ExecutableRVAToOffset(pContext, SDFReadUInt64(hThread, MachOThreadStatusX64EIP));
	SDFDestroy(hThread);
	return SDFSizeInBytes(MachOThreadStatusX64);
}

uint32_t MachOProcessCommandThread(ExecutableContext * pContext)
{
	uint32_t result = 0;
	
	HSDF hThread = SDFCreate(MachOThreadStatus, pContext->hReader);
	SDFDebugPrint(hThread);
	SDFDestroy(hThread);
	result += SDFSizeInBytes(MachOThreadStatus);
	
	switch (OBJ.Arch)
	{
	case ArchX86: result += MachOProcessCommandThreadX86(pContext); break;
	case ArchX64: result += MachOProcessCommandThreadX64(pContext); break;
	default: break;
	}
	return result;
}

void MachOFileDestroy(ExecutableContext * pContext)
{
	for (pContext->iObject = 0; pContext->iObject < pContext->nObjects; ++pContext->iObject)
	{
		if (NULL != pContext->pObjects)
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
	}
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
	CHECK_ALLOC(pContext->pObjects = (ExecutableObject*) calloc(1, sizeof(ExecutableObject) * pContext->nObjects));
	pContext->iObject = 0;
	CHECK_ALLOC(OBJ.pPrivate = calloc(1, sizeof(MachOFileContext)));
	CHECK_ALLOC(THIS->phFatHeaders = (HSDF*) calloc(1, sizeof(HSDF) * pContext->nObjects));
	CHECK_ALLOC(THIS->phMachHeaders = (HSDF*) calloc(1, sizeof(HSDF) * pContext->nObjects));
	for (i = 0; i < pContext->nObjects; ++i)
	{
		CHECK_CALL(THIS->phFatHeaders[i] = SDFCreate(MachOFatHeader, pContext->hReader));
		SDFSetEndian(THIS->phFatHeaders[i], (kMachOFatMagicBE == magic) ? 1 : 0);
		SDFDebugPrint(THIS->phFatHeaders[i]);
	}
	for (i = 0; i < pContext->nObjects; ++i)
	{
		uint32_t CpuType = SDFReadUInt32(THIS->phFatHeaders[i], MachOFatHeaderCpuType);
		
		pContext->iObject = i;
		OBJ.Offset = SDFReadUInt32(THIS->phFatHeaders[i], MachOFatHeaderOffset);
		
		switch (CpuType)
		{
			case kMachOCPUTypeX86: OBJ.Arch = ArchX86; break;
			case kMachOCPUTypeX64: OBJ.Arch = ArchX64; break;
			default: break;
		}
		
		CHECK_CALL(ReaderSeek(pContext->hReader, OBJ.Offset));
		CHECK_CALL(THIS->phMachHeaders[i] = SDFCreate(CpuType & kMachOCPUType64 ? MachOHeader64 : MachOHeader, pContext->hReader));
		SDFDebugPrint(THIS->phMachHeaders[i]);
		
		THIS->nCommands = SDFReadUInt32(THIS->phMachHeaders[i], MachOHeaderCountCommands);
		for (j = 0; j < THIS->nCommands; ++j)
		{
			uint32_t count, type;
			HSDF hCommand = NULL;
			CHECK_CALL(hCommand = SDFCreate(MachOLoadCommand, pContext->hReader));
			type = SDFReadUInt32(hCommand, MachOLoadCommandCommand);
			count = SDFReadUInt32(hCommand, MachOLoadCommandCommandSize) - SDFSizeInBytes(MachOLoadCommand);
			SDFDebugPrint(hCommand);
			
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
	pContext->iObject = 0;
	return 1;
}

int MachOFileCreate(ExecutableContext * pContext)
{
	pContext->pDestroy = MachOFileDestroy;
	if (0 == MachOFileInit(pContext))
	{
		ExecutableFree(pContext);
		return 0;
	}
	return 1;
}
