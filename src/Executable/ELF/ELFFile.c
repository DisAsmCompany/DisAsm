/*
 * Filename: ELFFile.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF (Executable and Linkable Format)
 *              file abstraction
 *
 *
 */

#include "../../DisAsm/DisAsm"
#include "../Executable"

#include "ELFClass.h"
#include "ELFData.h"
#include "ELFType.h"
#include "ELFMachine.h"
#include "ELFVersion.h"
#include "ELFABI.h"
#include "ELFHeader.h"
#include "ELFSectionType.h"
#include "ELFSectionFlags.h"
#include "ELFSectionHeader.h"
#include "ELFProgramType.h"
#include "ELFProgramFlags.h"
#include "ELFProgramHeader.h"

typedef struct ELFFileContext_t
{
	HSDF hHeader;
	HSDF * phSectionHeaders;
	HSDF * phProgramHeaders;
	uint16_t NumberOfSections;
	uint16_t NumberOfPrograms;
}
ELFFileContext;

#undef THIS
#define THIS ((ELFFileContext*)(pContext->pPrivate))

#define CHECK_CALL(x) do { if (0 == (x)) return 0; } while (0);
#define CHECK_ALLOC(x) do { if (NULL == (x)) return 0; } while (0);

uint32_t ELFRVAToOffset(ExecutableContext * pContext, uint32_t RVA)
{
	uint32_t offset = 0;
	uint16_t i = 0;
	for (i = 0; i < THIS->NumberOfSections; ++i)
	{
		uint32_t Address = SDFReadUInt32(THIS->phSectionHeaders[i], ELFSectionHeaderAddress);
		uint32_t Size    = SDFReadUInt32(THIS->phSectionHeaders[i], ELFSectionHeaderSize);
		uint32_t Data    = SDFReadUInt32(THIS->phSectionHeaders[i], ELFSectionHeaderOffset);
		if (Address <= RVA && RVA <= Address + Size)
		{
			offset = Data + RVA - Address;
			break;
		}
	}
	return offset;
}

int ELFFileOpen(ExecutableContext * pContext)
{
	uint16_t i = 0;
	uint32_t OffsetSections = 0;
	uint16_t SizeOfSection = 0;
	uint32_t OffsetPrograms = 0;
	uint16_t SizeOfProgram = 0;
	uint16_t Machine = 0;

	CHECK_CALL(ReaderSeek(pContext->hReader, 0));
	CHECK_CALL(THIS->hHeader = SDFCreate(ELFHeader, pContext->hReader));
	if (kELFMagic != SDFReadUInt32(THIS->hHeader, ELFHeaderMagic))
	{
		return 0;
	}
	SDFPrint(THIS->hHeader);

	Machine = SDFReadUInt16(THIS->hHeader, ELFHeaderMachine);
	switch (Machine)
	{
	case kELFMachine386:   pContext->Arch = ArchX86; break;
	case kELFMachine486:   pContext->Arch = ArchX86; break;
	case kELFMachineX8664: pContext->Arch = ArchX64; break;
	default:               pContext->Arch = ArchUnknown; break;
	}

	OffsetSections   = SDFReadUInt32(THIS->hHeader, ELFHeaderOffsetSections);
	THIS->NumberOfSections = SDFReadUInt16(THIS->hHeader, ELFHeaderNumberOfSections);
	SizeOfSection    = SDFReadUInt16(THIS->hHeader, ELFHeaderSizeOfSection);
	if (SizeOfSection < SDFSizeInBytes(ELFSectionHeader))
	{
		return 0;
	}
	CHECK_ALLOC(THIS->phSectionHeaders = malloc(SDFSizeInBytes(ELFSectionHeader) * THIS->NumberOfSections));
	for (i = 0; i < THIS->NumberOfSections; ++i)
	{
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * i));
		CHECK_CALL(THIS->phSectionHeaders[i] = SDFCreate(ELFSectionHeader, pContext->hReader));
		SDFPrint(THIS->phSectionHeaders[i]);
	}
	OffsetPrograms   = SDFReadUInt32(THIS->hHeader, ELFHeaderOffsetPrograms);
	THIS->NumberOfPrograms = SDFReadUInt16(THIS->hHeader, ELFHeaderNumberOfPrograms);
	SizeOfProgram    = SDFReadUInt16(THIS->hHeader, ELFHeaderSizeOfProgram);
	if (SizeOfProgram < SDFSizeInBytes(ELFProgramHeader))
	{
		return 0;
	}
	CHECK_ALLOC(THIS->phProgramHeaders = malloc(SDFSizeInBytes(ELFProgramHeader) * THIS->NumberOfPrograms));
	for (i = 0; i < THIS->NumberOfPrograms; ++i)
	{
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetPrograms + SizeOfProgram * i));
		CHECK_CALL(THIS->phProgramHeaders[i] = SDFCreate(ELFProgramHeader, pContext->hReader));
		SDFPrint(THIS->phProgramHeaders[i]);
	}
	pContext->EntryPoint = ELFRVAToOffset(pContext, SDFReadUInt32(THIS->hHeader, ELFHeaderAddressOfEntryPoint));
	return 1;
}

void ELFFileDestroy(ExecutableContext * pContext)
{
	uint16_t i = 0;
	for (i = 0; i < THIS->NumberOfSections; ++i)
	{
		SDFDestroy(THIS->phSectionHeaders[i]);
	}
	free(THIS->phSectionHeaders);
	for (i = 0; i < THIS->NumberOfPrograms; ++i)
	{
		SDFDestroy(THIS->phProgramHeaders[i]);
	}
	free(THIS->phProgramHeaders);
	SDFDestroy(THIS->hHeader);
	free(THIS);
}

int ELFFileCreate(ExecutableContext * pContext)
{
	ELFFileContext * pELFFileContext = (ELFFileContext*) malloc(sizeof(ELFFileContext));
	if (NULL == pELFFileContext)
	{
		return 0;
	}
	memset(pELFFileContext, 0, sizeof(ELFFileContext));
	pContext->pPrivate = pELFFileContext;
	if (0 == ELFFileOpen(pContext))
	{
		ELFFileDestroy(pContext);
		return 0;
	}
	pContext->pDestroy = ELFFileDestroy;

	return 1;
}
