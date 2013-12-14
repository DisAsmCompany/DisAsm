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

#include "../DisAsm/DisAsm"
#include "Executable"

typedef int (*pfnCreate)(struct ExecutableContext_t * hExecutable);

static const pfnCreate Registry[] =
{
	PEFileCreate,
	NEFileCreate,
	LXFileCreate,
	MachOFileCreate,
	ELFFileCreate,
	NULL
};

HEXECUTABLE ExecutableCreate(HREADER hReader, uint8_t memory)
{
	ExecutableContext * pContext = NULL;
	uint32_t i = 0;

	if (NULL == hReader)
	{
		return NULL;
	}
	while (NULL != Registry[i])
	{
		CHECK_ALLOC(pContext = (ExecutableContext*) calloc(1, sizeof(ExecutableContext)));
		pContext->memory = memory;
		pContext->hReader = hReader;
		if (0 != Registry[i](pContext))
		{
			return (HEXECUTABLE) pContext;
		}
		else
		{
			ExecutableDestroy(pContext);
		}
		++i;
	}
	return 0;
}

void ExecutableDestroy(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext)
	{
		if (NULL != pContext->pObjects)
		{
			uint32_t i;
			for (i = 0; i < pContext->nObjects; ++i)
			{
				free(pContext->pObjects[i].pSections);
				free(pContext->pObjects[i].pExports);
			}
		}
        free(pContext->pObjects);
        if (NULL != pContext->pDestroy)
        {
            pContext->pDestroy(hExecutable);
        }
		pContext->nObjects = 0;
	}
	free(hExecutable);
}

Architecture ExecutableGetArchitecture(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return (NULL != pContext && NULL != pContext->pObjects) ? OBJ.Arch : ArchUnknown;
}

address_t ExecutableGetBase(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return (NULL != pContext && NULL != pContext->pObjects) ? OBJ.Base : 0;
}

address_t ExecutableGetEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return (NULL != pContext && NULL != pContext->pObjects) ? OBJ.EntryPoint : 0;
}

address_t ExecutableGetStubEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return (NULL != pContext && NULL != pContext->pObjects) ? OBJ.StubEntryPoint : 0;
}

uint32_t ExecutableGetExportCount(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return (NULL != pContext && NULL != pContext->pObjects) ? OBJ.nExports : 0;
}

address_t ExecutableGetExportAddress(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pObjects && index < OBJ.nExports)
	{
		return OBJ.pExports[index].Address;
	}
	return 0;
}

char * ExecutableGetExportName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pObjects && index < OBJ.nExports)
	{
		address_t address = OBJ.pExports[index].Name;
		if (0 != address)
		{
			return FetchString(pContext, address);
		}
	}
	return NULL;
}

char * ExecutableGetExportForwarderName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pObjects && index < OBJ.nExports)
	{
		address_t address = OBJ.pExports[index].Forwarder;
		if (0 != address)
		{
			return FetchString(pContext, address);
		}
	}
	return NULL;
}

uint32_t ExecutableGetObjectCount(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext)
	{
		return pContext->nObjects;
	}
	return 0;
}

uint32_t ExecutableGetCurrentObject(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext)
	{
		return pContext->iObject;
	}
	return 0;
}

uint32_t ExecutableSetCurrentObject(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && index < pContext->nObjects)
	{
		return pContext->iObject = index;
	}
	return 0;
}

address_t ExecutableRVAToOffset(HEXECUTABLE hExecutable, address_t RVA)
{
	address_t offset = 0;
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pObjects)
	{
		uint16_t i = 0;
		if (pContext->memory || OBJ.Object)
		{
			return RVA;
		}
		for (i = 0; i < OBJ.nSections; ++i)
		{
			address_t Address = OBJ.pSections[i].VirtualAddress;
			address_t Size    = OBJ.pSections[i].VirtualSize;
			address_t Data    = OBJ.pSections[i].FileAddress;
			if (Address <= RVA && RVA <= Address + Size)
			{
				offset = OBJ.Offset + Data + RVA - Address;
				break;
			}
		}
	}
	return offset;
}

char * FetchString(ExecutableContext * pContext, address_t address)
{
	char * buffer = NULL; 
	uint32_t i = 0;
	CHECK_CALL(ReaderSeek(pContext->hReader, address));
	CHECK_ALLOC(buffer = calloc(1, 1024));
	for (i = 0; i < 1024; ++i)
	{
		if (0 == ReaderRead(pContext->hReader, &buffer[i], sizeof(uint8_t)))
		{
			break;
		}
		if (0 == buffer[i] || '\n' == buffer[i] || '\r' == buffer[i])
		{
			break;
		}
	}
	buffer[i] = 0;
	return buffer;
}
