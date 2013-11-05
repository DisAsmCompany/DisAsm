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
	HSDF * phProgramHeaders;
	uint16_t NumberOfPrograms;
}
ELFFileContext;

#undef THIS
#define THIS ((ELFFileContext*)(pContext->pPrivate))

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

	CHECK_ALLOC(pContext->pObjects = (ExecutableObject*) malloc(sizeof(ExecutableObject)));
	pContext->iObject = 0;
	pContext->nObjects = 1;

	Machine = SDFReadUInt16(THIS->hHeader, ELFHeaderMachine);
	switch (Machine)
	{
	case kELFMachine386:   pContext->pObjects[pContext->iObject].Arch = ArchX86; break;
	case kELFMachine486:   pContext->pObjects[pContext->iObject].Arch = ArchX86; break;
	case kELFMachineX8664: pContext->pObjects[pContext->iObject].Arch = ArchX64; break;
	default:               pContext->pObjects[pContext->iObject].Arch = ArchUnknown; break;
	}

	OffsetSections   = SDFReadUInt32(THIS->hHeader, ELFHeaderOffsetSections);
	pContext->pObjects[pContext->iObject].nSections = SDFReadUInt16(THIS->hHeader, ELFHeaderNumberOfSections);
	SizeOfSection    = SDFReadUInt16(THIS->hHeader, ELFHeaderSizeOfSection);
	if (SizeOfSection < SDFSizeInBytes(ELFSectionHeader))
	{
		return 0;
	}
	CHECK_ALLOC(pContext->pObjects[pContext->iObject].pSections = malloc(sizeof(ExecutableSection) * pContext->pObjects[pContext->iObject].nSections));
	for (i = 0; i < pContext->pObjects[pContext->iObject].nSections; ++i)
	{
		HSDF hSectionHeader = NULL;
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * i));
		CHECK_CALL(hSectionHeader = SDFCreate(ELFSectionHeader, pContext->hReader));

		pContext->pObjects[pContext->iObject].pSections[i].VirtualAddress = SDFReadUInt32(hSectionHeader, ELFSectionHeaderAddress);
		pContext->pObjects[pContext->iObject].pSections[i].FileAddress    = SDFReadUInt32(hSectionHeader, ELFSectionHeaderOffset);
		pContext->pObjects[pContext->iObject].pSections[i].FileSize       =
		pContext->pObjects[pContext->iObject].pSections[i].VirtualSize    = SDFReadUInt32(hSectionHeader, ELFSectionHeaderSize);

		SDFPrint(hSectionHeader);
		SDFDestroy(hSectionHeader);
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
	pContext->pObjects[pContext->iObject].EntryPoint = ExecutableRVAToOffset(pContext, SDFReadUInt32(THIS->hHeader, ELFHeaderAddressOfEntryPoint));
	pContext->pObjects[pContext->iObject].StubEntryPoint = 0;
	return 1;
}

void ELFFileDestroy(ExecutableContext * pContext)
{
	uint16_t i = 0;
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
	CHECK_ALLOC(pContext->pPrivate = calloc(1, sizeof(ELFFileContext)));
	if (0 == ELFFileOpen(pContext))
	{
		ELFFileDestroy(pContext);
		return 0;
	}
	pContext->pDestroy = ELFFileDestroy;

	return 1;
}
