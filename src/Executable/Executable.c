/*
* Filename: Executable.c
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Executable API implementation
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../DisAsm/DisAsm"
#include "Executable"

typedef struct ExecutableContext_t
{
	uint8_t memory;
	HREADER hReader;
	uint8_t * buffer;
	uint32_t offset;
	uint32_t index;
	FILE * f;
	PEDOSHeader DOSHeader;
	PENTHeaders NTHeaders;
	PESectionHeader * SectionHeaders;

	uint32_t offsetFunctions;
	uint32_t offsetNameOrdinals;
	uint32_t offsetNames;
	uint32_t count;
}
ExecutableContext;

uint32_t RVAToOffset(ExecutableContext * pContext, uint32_t RVA)
{
	uint32_t offset = 0;
	uint16_t i = 0;
	if (pContext->memory)
	{
		return RVA;
	}
	for (i = 0; i < pContext->NTHeaders.FileHeader.NumberOfSections; ++i)
	{
		if (pContext->SectionHeaders[i].VirtualAddress <= RVA && RVA <= pContext->SectionHeaders[i].VirtualAddress + pContext->SectionHeaders[i].SizeOfRawData)
		{
			offset = pContext->SectionHeaders[i].PointerToRawData + RVA - pContext->SectionHeaders[i].VirtualAddress;
			break;
		}
	}
	return offset;
}

int ExecutableInit(ExecutableContext * pContext)
{
	PEDataDirectory * ExportDataDirectory = NULL;
	uint32_t size = 0;

	pContext->index = 0;
	
	if (0 == ReaderRead(pContext->hReader, &pContext->DOSHeader, sizeof(PEDOSHeader)))
	{
		return 0;
	}
	if (pContext->DOSHeader.magic != PEDOSSignature)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, pContext->DOSHeader.lfanew))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &pContext->NTHeaders, sizeof(PENTHeaders)))
	{
		return 0;
	}
	if (pContext->NTHeaders.Signature != PENTSignature)
	{
		return 0;
	}
	if (pContext->NTHeaders.FileHeader.NumberOfSections == 0)
	{
		return 0;
	}
	size = sizeof(PESectionHeader) * pContext->NTHeaders.FileHeader.NumberOfSections;
	pContext->SectionHeaders = (PESectionHeader*) malloc(size);
	if (NULL == pContext->SectionHeaders)
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, pContext->SectionHeaders, size))
	{
		return 0;
	}
	ExportDataDirectory = &pContext->NTHeaders.OptionalHeader.DataDirectory[PEDataDirectoryExport];
	if (0 != ExportDataDirectory->Size)
	{
		PEExportDirectory ExportDirectory = {0};
		uint32_t offset = RVAToOffset(pContext, ExportDataDirectory->VirtualAddress);
		if (0 == offset)
		{
			return 0;
		}
		if (0 == ReaderSeek(pContext->hReader, offset))
		{
			return 0;
		}
		if (0 == ReaderRead(pContext->hReader, &ExportDirectory, sizeof(PEExportDirectory)))
		{
			return 0;
		}
		pContext->offsetFunctions = RVAToOffset(pContext, ExportDirectory.AddressOfFunctions);
		pContext->offsetNameOrdinals = RVAToOffset(pContext, ExportDirectory.AddressOfNameOrdinals);
		pContext->offsetNames = RVAToOffset(pContext, ExportDirectory.AddressOfNames);
		pContext->count = ExportDirectory.NumberOfNames;
	}
	return 1;
}

HEXECUTABLE ExecutableCreate(HREADER hReader, int memory)
{
	ExecutableContext * pContext = (ExecutableContext*) malloc(sizeof(ExecutableContext));

	pContext->hReader = hReader;
	pContext->memory = memory;
	ExecutableInit(pContext);
	return (HEXECUTABLE) pContext;
}

void ExecutableDestroy(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	free(hExecutable);
}

uint32_t ExecutableGetNextFunction(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	uint8_t c;
	uint32_t ptr = 0;

	++pContext->index;

	if (pContext->index == pContext->count)
	{
		return 0;
	}
	
	ReaderSeek(pContext->hReader, pContext->offsetNames + pContext->index * 4);
	ReaderRead(pContext->hReader, &ptr, sizeof(uint32_t));
	ptr = RVAToOffset(pContext, ptr);

	ReaderSeek(pContext->hReader, ptr);
	for (;;)
	{
		ReaderRead(pContext->hReader, &c, sizeof(uint8_t));
		if (0 == c)
		{
			printf("\n");
			break;
		}
		printf("%c", c);
	}

	ReaderSeek(pContext->hReader, pContext->offsetFunctions + pContext->index * 4);
	ReaderRead(pContext->hReader, &ptr, sizeof(uint32_t));
	ptr = RVAToOffset(pContext, ptr);
	return ptr;
}
