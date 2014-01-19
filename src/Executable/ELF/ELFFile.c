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
#include "ELFIdent.h"
#include "ELFHeader32.h"
#include "ELFHeader64.h"
#include "ELFSectionType.h"
#include "ELFSectionFlags.h"
#include "ELFSectionHeader32.h"
#include "ELFSectionHeader64.h"
#include "ELFProgramType.h"
#include "ELFProgramFlags.h"
#include "ELFProgramHeader32.h"
#include "ELFProgramHeader64.h"
#include "ELFSymbolType.h"
#include "ELFSymbol32.h"
#include "ELFSymbol64.h"

typedef struct ELFFileContext_t
{
	HSDF hIdent;
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

int ELFProcessExport32(ExecutableContext * pContext)
{
	uint32_t i = 0;
	uint32_t count = (uint32_t) (THIS->ExportSize / SDFSizeInBytes(ELFSymbol32));

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
		CHECK_CALL(ReaderSeek(pContext->hReader, THIS->ExportAddress + i * SDFSizeInBytes(ELFSymbol32)));
		CHECK_CALL(hSymbol = SDFCreate(ELFSymbol32, pContext->hReader));

		if (0 != (address = SDFReadUInt32(hSymbol, ELFSymbol32Value)))
		{
			OBJ.pExports[i].Address = ExecutableRVAToOffset(pContext, address);
		}
		if (0 != (name = SDFReadUInt32(hSymbol, ELFSymbol32Name)))
		{
			OBJ.pExports[i].Name = THIS->NamesAddress + name;
		}
		SDFDebugPrint(hSymbol);
		SDFDestroy(hSymbol);
	}
	return 1;
}

int ELFProcessExport64(ExecutableContext * pContext)
{
	uint32_t i = 0;
	uint32_t count = (uint32_t) (THIS->ExportSize / SDFSizeInBytes(ELFSymbol32));

	if (0 == THIS->ExportAddress || 0 == THIS->ExportSize)
	{
		return 0;
	}
	CHECK_ALLOC(OBJ.pExports = calloc(1, sizeof(ExecutableSymbol) * count));
	OBJ.nExports = count;

	for (i = 0; i < count; ++i)
	{
		uint64_t address = 0;
		uint32_t name = 0;
		HSDF hSymbol = NULL;
		CHECK_CALL(ReaderSeek(pContext->hReader, THIS->ExportAddress + i * SDFSizeInBytes(ELFSymbol64)));
		CHECK_CALL(hSymbol = SDFCreate(ELFSymbol64, pContext->hReader));

		if (0 != (address = SDFReadUInt64(hSymbol, ELFSymbol64Value)))
		{
			OBJ.pExports[i].Address = ExecutableRVAToOffset(pContext, address);
		}
		if (0 != (name = SDFReadUInt32(hSymbol, ELFSymbol64Name)))
		{
			OBJ.pExports[i].Name = THIS->NamesAddress + name;
		}
		SDFDebugPrint(hSymbol);
		SDFDestroy(hSymbol);
	}
	return 1;
}

int ELFFileOpen32(ExecutableContext * pContext)
{
	uint16_t i = 0;
	uint32_t OffsetSections = 0;
	uint16_t SizeOfSection = 0;
	uint32_t OffsetPrograms = 0;
	uint16_t SizeOfProgram = 0;
	uint16_t Machine = 0;
	uint16_t IndexNames = 0;
	uint32_t OffsetNames = 0;

	CHECK_CALL(THIS->hHeader = SDFCreate(ELFHeader32, pContext->hReader));
	SDFDebugPrint(THIS->hHeader);

	Machine = SDFReadUInt16(THIS->hHeader, ELFHeader32Machine);
	switch (Machine)
	{
	case kELFMachine386:   OBJ.Arch = ArchX86; break;
	case kELFMachine486:   OBJ.Arch = ArchX86; break;
	case kELFMachineX8664: OBJ.Arch = ArchX64; break;
	default:               OBJ.Arch = ArchUnknown; break;
	}

	IndexNames = SDFReadUInt16(THIS->hHeader, ELFHeader32SectionHeaderIndex);
	OffsetSections   = SDFReadUInt32(THIS->hHeader, ELFHeader32OffsetSections);
	OBJ.nSections = SDFReadUInt16(THIS->hHeader, ELFHeader32NumberOfSections);
	SizeOfSection    = SDFReadUInt16(THIS->hHeader, ELFHeader32SizeOfSection);
	if (SizeOfSection < SDFSizeInBytes(ELFSectionHeader32))
	{
		return 0;
	}
	CHECK_ALLOC(OBJ.pSections = calloc(1, sizeof(ExecutableSection) * OBJ.nSections));

	/* first off, lookup section names */
	{
		HSDF hSectionHeader = NULL;
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * IndexNames));
		CHECK_CALL(hSectionHeader = SDFCreate(ELFSectionHeader32, pContext->hReader));
		OffsetNames = SDFReadUInt32(hSectionHeader, ELFSectionHeader32Offset);
		SDFDestroy(hSectionHeader);
	}
	for (i = 0; i < OBJ.nSections; ++i)
	{
		HSDF hSectionHeader = NULL;
		uint32_t type = 0;
		uint32_t Name = 0;

		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * i));
		CHECK_CALL(hSectionHeader = SDFCreate(ELFSectionHeader32, pContext->hReader));

		Name = SDFReadUInt32(hSectionHeader, ELFSectionHeader32Name);
		OBJ.pSections[i].VirtualAddress = SDFReadUInt32(hSectionHeader, ELFSectionHeader32Address);
		OBJ.pSections[i].FileAddress    = SDFReadUInt32(hSectionHeader, ELFSectionHeader32Offset);
		OBJ.pSections[i].FileSize       =
		OBJ.pSections[i].VirtualSize    = SDFReadUInt32(hSectionHeader, ELFSectionHeader32Size);

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

		type = SDFReadUInt32(hSectionHeader, ELFSectionHeader32Type);
		if (kELFSectionDynSym == type)
		{
			THIS->ExportAddress = OBJ.pSections[i].FileAddress;
			THIS->ExportSize = OBJ.pSections[i].FileSize;
		}
		SDFDebugPrint(hSectionHeader);
		SDFDestroy(hSectionHeader);
	}
	OffsetPrograms   = SDFReadUInt32(THIS->hHeader, ELFHeader32OffsetPrograms);
	THIS->NumberOfPrograms = SDFReadUInt16(THIS->hHeader, ELFHeader32NumberOfPrograms);
	SizeOfProgram    = SDFReadUInt16(THIS->hHeader, ELFHeader32SizeOfProgram);
	if (SizeOfProgram < SDFSizeInBytes(ELFProgramHeader32))
	{
		return 0;
	}
	CHECK_ALLOC(THIS->phProgramHeaders = calloc(1, SDFSizeInBytes(ELFProgramHeader32) * THIS->NumberOfPrograms));
	for (i = 0; i < THIS->NumberOfPrograms; ++i)
	{
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetPrograms + SizeOfProgram * i));
		CHECK_CALL(THIS->phProgramHeaders[i] = SDFCreate(ELFProgramHeader32, pContext->hReader));
		SDFDebugPrint(THIS->phProgramHeaders[i]);
	}
	OBJ.EntryPoint = ExecutableRVAToOffset(pContext, SDFReadUInt32(THIS->hHeader, ELFHeader32AddressOfEntryPoint));
	OBJ.StubEntryPoint = 0;

	ELFProcessExport32(pContext);
	return 1;
}

int ELFFileOpen64(ExecutableContext * pContext)
{
	uint16_t i = 0;
	uint64_t OffsetSections = 0;
	uint16_t SizeOfSection = 0;
	uint64_t OffsetPrograms = 0;
	uint16_t SizeOfProgram = 0;
	uint16_t Machine = 0;
	uint16_t IndexNames = 0;
	uint64_t OffsetNames = 0;

	CHECK_CALL(THIS->hHeader = SDFCreate(ELFHeader64, pContext->hReader));
	SDFDebugPrint(THIS->hHeader);

	Machine = SDFReadUInt16(THIS->hHeader, ELFHeader32Machine);
	switch (Machine)
	{
	case kELFMachine386:   OBJ.Arch = ArchX86; break;
	case kELFMachine486:   OBJ.Arch = ArchX86; break;
	case kELFMachineX8664: OBJ.Arch = ArchX64; break;
	default:               OBJ.Arch = ArchUnknown; break;
	}

	IndexNames = SDFReadUInt16(THIS->hHeader, ELFHeader64SectionHeaderIndex);
	OffsetSections   = SDFReadUInt64(THIS->hHeader, ELFHeader64OffsetSections);
	OBJ.nSections = SDFReadUInt16(THIS->hHeader, ELFHeader64NumberOfSections);
	SizeOfSection    = SDFReadUInt16(THIS->hHeader, ELFHeader64SizeOfSection);
	if (SizeOfSection < SDFSizeInBytes(ELFSectionHeader64))
	{
		return 0;
	}
	CHECK_ALLOC(OBJ.pSections = calloc(1, sizeof(ExecutableSection) * OBJ.nSections));

	/* first off, lookup section names */
	{
		HSDF hSectionHeader = NULL;
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * IndexNames));
		CHECK_CALL(hSectionHeader = SDFCreate(ELFSectionHeader64, pContext->hReader));
		OffsetNames = SDFReadUInt64(hSectionHeader, ELFSectionHeader64Offset);
		SDFDestroy(hSectionHeader);
	}
	for (i = 0; i < OBJ.nSections; ++i)
	{
		HSDF hSectionHeader = NULL;
		uint32_t type = 0;
		uint32_t Name = 0;

		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSections + SizeOfSection * i));
		CHECK_CALL(hSectionHeader = SDFCreate(ELFSectionHeader64, pContext->hReader));

		Name = SDFReadUInt32(hSectionHeader, ELFSectionHeader64Name);
		OBJ.pSections[i].VirtualAddress = SDFReadUInt32(hSectionHeader, ELFSectionHeader64Address);
		OBJ.pSections[i].FileAddress    = SDFReadUInt32(hSectionHeader, ELFSectionHeader64Offset);
		OBJ.pSections[i].FileSize       =
		OBJ.pSections[i].VirtualSize    = SDFReadUInt32(hSectionHeader, ELFSectionHeader64Size);

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

		type = SDFReadUInt32(hSectionHeader, ELFSectionHeader64Type);
		if (kELFSectionDynSym == type)
		{
			THIS->ExportAddress = OBJ.pSections[i].FileAddress;
			THIS->ExportSize = OBJ.pSections[i].FileSize;
		}
		SDFDebugPrint(hSectionHeader);
		SDFDestroy(hSectionHeader);
	}
	OffsetPrograms   = SDFReadUInt64(THIS->hHeader, ELFHeader64OffsetPrograms);
	THIS->NumberOfPrograms = SDFReadUInt16(THIS->hHeader, ELFHeader64NumberOfPrograms);
	SizeOfProgram    = SDFReadUInt16(THIS->hHeader, ELFHeader64SizeOfProgram);
	if (SizeOfProgram < SDFSizeInBytes(ELFProgramHeader64))
	{
		return 0;
	}
	CHECK_ALLOC(THIS->phProgramHeaders = calloc(1, SDFSizeInBytes(ELFProgramHeader64) * THIS->NumberOfPrograms));
	for (i = 0; i < THIS->NumberOfPrograms; ++i)
	{
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetPrograms + SizeOfProgram * i));
		CHECK_CALL(THIS->phProgramHeaders[i] = SDFCreate(ELFProgramHeader64, pContext->hReader));
		SDFDebugPrint(THIS->phProgramHeaders[i]);
	}
	OBJ.EntryPoint = ExecutableRVAToOffset(pContext, SDFReadUInt64(THIS->hHeader, ELFHeader64AddressOfEntryPoint));
	OBJ.StubEntryPoint = 0;

	ELFProcessExport64(pContext);
	return 1;
}

int ELFFileOpen(ExecutableContext * pContext)
{
	CHECK_ALLOC(pContext->pObjects = (ExecutableObject*) calloc(1, sizeof(ExecutableObject)));
	pContext->iObject = 0;
	pContext->nObjects = 1;
	CHECK_ALLOC(OBJ.pPrivate = calloc(1, sizeof(ELFFileContext)));

	CHECK_CALL(ReaderSeek(pContext->hReader, 0));
	CHECK_CALL(THIS->hIdent = SDFCreate(ELFIdent, pContext->hReader));
	if (kELFMagic != SDFReadUInt32(THIS->hIdent, ELFHeaderMagic))
	{
		return 0;
	}
	SDFDebugPrint(THIS->hIdent);

	switch (SDFReadUInt8(THIS->hIdent, ELFHeaderClass))
	{
	case kELFClass32:
		return ELFFileOpen32(pContext);
	case kELFClass64:
		return ELFFileOpen64(pContext);
	default:
		return 0;
	}
}

void ELFFileDestroy(ExecutableContext * pContext)
{
	for (pContext->iObject = 0; pContext->iObject < pContext->nObjects; ++pContext->iObject)
	{
		if (THIS)
		{
			uint16_t i = 0;
			for (i = 0; i < THIS->NumberOfPrograms; ++i)
			{
				SDFDestroy(THIS->phProgramHeaders[i]);
			}
			free(THIS->phProgramHeaders);
			SDFDestroy(THIS->hIdent);
			SDFDestroy(THIS->hHeader);
			free(THIS);
		}
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
