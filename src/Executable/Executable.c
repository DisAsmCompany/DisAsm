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
#include "../DisAsm/DisAsm"
#include "Executable"

typedef struct ExecutableContext_t
{
	uint8_t memory;
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

int ExecutableSeek(ExecutableContext * pContext, uint32_t pos)
{
	if (pContext->memory)
	{
		pContext->offset = pos;
		return 1;
	}
	else
	{
		return (0 == fseek(pContext->f, pos, SEEK_SET));
	}
}

int ExecutableRead(ExecutableContext * pContext, void * buffer, uint32_t size)
{
	if (pContext->memory)
	{
		memcpy(buffer, pContext->buffer + pContext->offset, size);
		pContext->offset += size;
		return 1;
	}
	else
	{
		return (size == fread(buffer, 1, size, pContext->f));
	}
}

int ExecutableInit(ExecutableContext * pContext)
{
	PEDataDirectory * ExportDataDirectory = NULL;
	uint32_t size = 0;

	pContext->index = 0;
	
	if (0 == ExecutableRead(pContext, &pContext->DOSHeader, sizeof(PEDOSHeader)))
	{
		return 0;
	}
	if (pContext->DOSHeader.magic != PEDOSSignature)
	{
		return 0;
	}
	if (0 == ExecutableSeek(pContext, pContext->DOSHeader.lfanew))
	{
		return 0;
	}
	if (0 == ExecutableRead(pContext, &pContext->NTHeaders, sizeof(PENTHeaders)))
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
	if (0 == ExecutableRead(pContext, pContext->SectionHeaders, size))
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
		if (0 == ExecutableSeek(pContext, offset))
		{
			return 0;
		}
		if (0 == ExecutableRead(pContext, &ExportDirectory, sizeof(PEExportDirectory)))
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

HEXECUTABLE ExecutableCreateFromFile(const char * name)
{
	ExecutableContext * pContext = (ExecutableContext*) malloc(sizeof(ExecutableContext));
	
	pContext->memory = 0;
	pContext->f = fopen(name, "rb");
	if (NULL == pContext->f)
	{
		return 0;
	}
	ExecutableInit(pContext);
	return (HEXECUTABLE) pContext;
}

HEXECUTABLE ExecutableCreateFromMemory(uint8_t * buffer)
{
	ExecutableContext * pContext = (ExecutableContext*) malloc(sizeof(ExecutableContext));

	pContext->memory = 1;
	pContext->buffer = buffer;
	pContext->offset = 0;
	if (NULL == pContext->f)
	{
		return 0;
	}
	ExecutableInit(pContext);
	return (HEXECUTABLE) pContext;
}

void ExecutableDestroy(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (!pContext->memory)
	{
		fclose(pContext->f);
	}
	free(hExecutable);
}

uint8_t * ExecutableGetNextFunction(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	uint8_t c;
	uint32_t ptr = 0;

	++pContext->index;

	if (pContext->index == pContext->count)
	{
		return NULL;
	}
	
	ExecutableSeek(pContext, pContext->offsetNames + pContext->index * 4);
	ExecutableRead(pContext, &ptr, sizeof(uint32_t));
	ptr = RVAToOffset(pContext, ptr);

	ExecutableSeek(pContext, ptr);
	for (;;)
	{
		ExecutableRead(pContext, &c, sizeof(uint8_t));
		if (0 == c)
		{
			printf("\n");
			break;
		}
		printf("%c", c);
	}

	ExecutableSeek(pContext, pContext->offsetFunctions + pContext->index * 4);
	ExecutableRead(pContext, &ptr, sizeof(uint32_t));
	ptr = RVAToOffset(pContext, ptr);
	if (pContext->memory)
	{
		ptr = ptr + pContext->buffer;
	}
	return ptr;
}
