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
	uint32_t AddressOfEntryPoint;
}
ELFFileContext;

#undef THIS
#define THIS ((ELFFileContext*)(pContext->pPrivate))

int ELFFileCreate(ExecutableContext * pContext)
{
	uint16_t i = 0;
	uint32_t OffsetSections = 0;
	uint16_t NumberOfSections = 0;
	uint16_t SizeOfSection = 0;
	uint32_t OffsetPrograms = 0;
	uint16_t NumberOfPrograms = 0;
	uint16_t SizeOfProgram = 0;
	ELFFileContext * pELFFileContext = (ELFFileContext*) malloc(sizeof(ELFFileContext));
	if (NULL == pELFFileContext)
	{
		return 0;
	}
	memset(pELFFileContext, 0, sizeof(ELFFileContext));
	pContext->pPrivate = pELFFileContext;
	if (0 == ReaderSeek(pContext->hReader, 0))
	{
		return 0;
	}
	THIS->hHeader = SDFCreate(ELFHeader, pContext->hReader);
	if (kELFMagic != SDFReadUInt32(THIS->hHeader, ELFHeaderMagic))
	{
		return 0;
	}
	SDFPrint(THIS->hHeader);

	THIS->AddressOfEntryPoint = SDFReadUInt32(THIS->hHeader, ELFHeaderAddressOfEntryPoint);
	OffsetSections   = SDFReadUInt32(THIS->hHeader, ELFHeaderOffsetSections);
	NumberOfSections = SDFReadUInt16(THIS->hHeader, ELFHeaderNumberOfSections);
	SizeOfSection    = SDFReadUInt16(THIS->hHeader, ELFHeaderSizeOfSection);
	for (i = 0; i < NumberOfSections; ++i)
	{
		HSDF hSection = NULL;
		ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * i);

		hSection = SDFCreate(ELFSectionHeader, pContext->hReader);
		SDFPrint(hSection);
		SDFDestroy(hSection);
	}
	OffsetPrograms   = SDFReadUInt32(THIS->hHeader, ELFHeaderOffsetPrograms);
	NumberOfPrograms = SDFReadUInt16(THIS->hHeader, ELFHeaderNumberOfPrograms);
	SizeOfProgram   = SDFReadUInt16(THIS->hHeader, ELFHeaderSizeOfProgram);
	for (i = 0; i < NumberOfPrograms; ++i)
	{
		HSDF hProgram = NULL;
		ReaderSeek(pContext->hReader, OffsetPrograms + SizeOfProgram * i);

		hProgram = SDFCreate(ELFProgramHeader, pContext->hReader);
		SDFPrint(hProgram);
		SDFDestroy(hProgram);
	}
	return 0;
}
