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
#include "ELFSymbolType.h"
#include "ELFSymbol.h"

typedef struct ELFFileContext_t
{
	HSDF hHeader;
	HSDF * phProgramHeaders;
	uint16_t  NumberOfPrograms;
	address_t ExportAddress;
	uint64_t  ExportSize;
	address_t NamesAddress;
}
ELFFileContext;

#undef THIS
#define THIS ((ELFFileContext*)(OBJ.pPrivate))

int ELFProcessExport(ExecutableContext * pContext)
{
	uint32_t i = 0;
	uint32_t count = (uint32_t) (THIS->ExportSize / SDFSizeInBytes(ELFSymbol));

	if (0 == THIS->ExportAddress || 0 == THIS->ExportSize)
	{
		return 0;
	}
	CHECK_ALLOC(OBJ.pExports = calloc(1, sizeof(ExecutableSymbol) * count));
	OBJ.nExports = count;

	for (i = 0; i < count; ++i)
	{
		uint32_t address = 0;
		uint32_t name = 0;
		HSDF hSymbol = NULL;
		CHECK_CALL(ReaderSeek(pContext->hReader, THIS->ExportAddress + i * SDFSizeInBytes(ELFSymbol)));
		CHECK_CALL(hSymbol = SDFCreate(ELFSymbol, pContext->hReader));

		if (0 != (address = SDFReadUInt32(hSymbol, ELFSymbolValue)))
		{
			OBJ.pExports[i].Address = ExecutableRVAToOffset(pContext, address);
		}
		if (0 != (name = SDFReadUInt32(hSymbol, ELFSymbolName)))
		{
			OBJ.pExports[i].Name = THIS->NamesAddress + name;
		}
		SDFDebugPrint(hSymbol);
		SDFDestroy(hSymbol);
	}
	return 1;
}

int ELFFileOpen(ExecutableContext * pContext)
{
	uint16_t i = 0;
	uint32_t OffsetSections = 0;
	uint16_t SizeOfSection = 0;
	uint32_t OffsetPrograms = 0;
	uint16_t SizeOfProgram = 0;
	uint16_t Machine = 0;
	uint16_t IndexNames = 0;
	uint32_t OffsetNames = 0;

	CHECK_ALLOC(pContext->pObjects = (ExecutableObject*) calloc(1, sizeof(ExecutableObject)));
	pContext->iObject = 0;
	pContext->nObjects = 1;
	CHECK_ALLOC(OBJ.pPrivate = calloc(1, sizeof(ELFFileContext)));

	CHECK_CALL(ReaderSeek(pContext->hReader, 0));
	CHECK_CALL(THIS->hHeader = SDFCreate(ELFHeader, pContext->hReader));
	if (kELFMagic != SDFReadUInt32(THIS->hHeader, ELFHeaderMagic))
	{
		return 0;
	}
	SDFDebugPrint(THIS->hHeader);

	Machine = SDFReadUInt16(THIS->hHeader, ELFHeaderMachine);
	switch (Machine)
	{
	case kELFMachine386:   OBJ.Arch = ArchX86; break;
	case kELFMachine486:   OBJ.Arch = ArchX86; break;
	case kELFMachineX8664: OBJ.Arch = ArchX64; break;
	default:               OBJ.Arch = ArchUnknown; break;
	}

	IndexNames = SDFReadUInt16(THIS->hHeader, ELFHeaderSectionHeaderIndex);
	OffsetSections   = SDFReadUInt32(THIS->hHeader, ELFHeaderOffsetSections);
	OBJ.nSections = SDFReadUInt16(THIS->hHeader, ELFHeaderNumberOfSections);
	SizeOfSection    = SDFReadUInt16(THIS->hHeader, ELFHeaderSizeOfSection);
	if (SizeOfSection < SDFSizeInBytes(ELFSectionHeader))
	{
		return 0;
	}
	CHECK_ALLOC(OBJ.pSections = calloc(1, sizeof(ExecutableSection) * OBJ.nSections));

	/* first off, lookup section names */
	{
		HSDF hSectionHeader = NULL;
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * IndexNames));
		CHECK_CALL(hSectionHeader = SDFCreate(ELFSectionHeader, pContext->hReader));
		OffsetNames = SDFReadUInt32(hSectionHeader, ELFSectionHeaderOffset);
		SDFDestroy(hSectionHeader);
	}
	for (i = 0; i < OBJ.nSections; ++i)
	{
		HSDF hSectionHeader = NULL;
		uint32_t type = 0;
		uint32_t Name = 0;

		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * i));
		CHECK_CALL(hSectionHeader = SDFCreate(ELFSectionHeader, pContext->hReader));

		Name = SDFReadUInt32(hSectionHeader, ELFSectionHeaderName);
		OBJ.pSections[i].VirtualAddress = SDFReadUInt32(hSectionHeader, ELFSectionHeaderAddress);
		OBJ.pSections[i].FileAddress    = SDFReadUInt32(hSectionHeader, ELFSectionHeaderOffset);
		OBJ.pSections[i].FileSize       =
		OBJ.pSections[i].VirtualSize    = SDFReadUInt32(hSectionHeader, ELFSectionHeaderSize);

		if (0 != Name)
		{
			char * value = FetchString(pContext, OffsetNames + Name);
			if (NULL != value)
			{
				if (0 == strcmp(value, ".dynstr"))
				{
					THIS->NamesAddress = OBJ.pSections[i].FileAddress;
				}
			}
            free(value);
		}

		type = SDFReadUInt32(hSectionHeader, ELFSectionHeaderType);
		if (kELFSectionDynSym == type)
		{
			THIS->ExportAddress = OBJ.pSections[i].FileAddress;
			THIS->ExportSize = OBJ.pSections[i].FileSize;
		}
		SDFDebugPrint(hSectionHeader);
		SDFDestroy(hSectionHeader);
	}
	OffsetPrograms   = SDFReadUInt32(THIS->hHeader, ELFHeaderOffsetPrograms);
	THIS->NumberOfPrograms = SDFReadUInt16(THIS->hHeader, ELFHeaderNumberOfPrograms);
	SizeOfProgram    = SDFReadUInt16(THIS->hHeader, ELFHeaderSizeOfProgram);
	if (SizeOfProgram < SDFSizeInBytes(ELFProgramHeader))
	{
		return 0;
	}
	CHECK_ALLOC(THIS->phProgramHeaders = calloc(1, SDFSizeInBytes(ELFProgramHeader) * THIS->NumberOfPrograms));
	for (i = 0; i < THIS->NumberOfPrograms; ++i)
	{
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetPrograms + SizeOfProgram * i));
		CHECK_CALL(THIS->phProgramHeaders[i] = SDFCreate(ELFProgramHeader, pContext->hReader));
		SDFDebugPrint(THIS->phProgramHeaders[i]);
	}
	OBJ.EntryPoint = ExecutableRVAToOffset(pContext, SDFReadUInt32(THIS->hHeader, ELFHeaderAddressOfEntryPoint));
	OBJ.StubEntryPoint = 0;

	ELFProcessExport(pContext);
	return 1;
}

void ELFFileDestroy(ExecutableContext * pContext)
{
	for (pContext->iObject = 0; pContext->iObject < pContext->nObjects; ++pContext->iObject)
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
}

int ELFFileCreate(ExecutableContext * pContext)
{
	pContext->pDestroy = ELFFileDestroy;

	if (0 == ELFFileOpen(pContext))
	{
		ExecutableFree(pContext);
		return 0;
	}
	return 1;
}
