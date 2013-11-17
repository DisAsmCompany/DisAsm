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

HEXECUTABLE ExecutableCreate(HREADER hReader, int memory)
{
	ExecutableContext * pContext = NULL;
	uint32_t i = 0;

	if (NULL == hReader)
	{
		return NULL;
	}
	CHECK_ALLOC(pContext = (ExecutableContext*) calloc(1, sizeof(ExecutableContext)));
	pContext->memory = memory;
	pContext->hReader = hReader;
	while (NULL != Registry[i])
	{
		if (0 != Registry[i](pContext))
		{
			return (HEXECUTABLE) pContext;
		}
		++i;
	}
	free(pContext);
	return 0;
}

void ExecutableDestroy(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext)
	{
        uint32_t i = 0;
        for (i = 0; i < pContext->nObjects; ++i)
        {
            free(pContext->pObjects[i].pSections);
            free(pContext->pObjects[i].pExports);
        }
        free(pContext->pObjects);
        if (NULL != pContext->pDestroy)
        {
            pContext->pDestroy(hExecutable);
        }
	}
	free(hExecutable);
}

Architecture ExecutableGetArchitecture(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->pObjects[pContext->iObject].Arch : ArchUnknown;
}

address_t ExecutableGetBase(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->pObjects[pContext->iObject].Base : 0;
}

address_t ExecutableGetEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->pObjects[pContext->iObject].EntryPoint : 0;
}

address_t ExecutableGetStubEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->pObjects[pContext->iObject].StubEntryPoint : 0;
}

uint32_t ExecutableGetExportCount(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->pObjects[pContext->iObject].nExports : 0;
}

address_t ExecutableGetExportAddress(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pObjects && index < pContext->pObjects[pContext->iObject].nExports)
	{
		return pContext->pObjects[pContext->iObject].pExports[index].Address;
	}
	return 0;
}

char * ExecutableGetExportName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pObjects && index < pContext->pObjects[pContext->iObject].nExports)
	{
		address_t address = pContext->pObjects[pContext->iObject].pExports[index].Name;
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
	if (NULL != pContext && NULL != pContext->pObjects && index < pContext->pObjects[pContext->iObject].nExports)
	{
		address_t address = pContext->pObjects[pContext->iObject].pExports[index].Forwarder;
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
	uint16_t i = 0;
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pObjects)
	{
		if (pContext->memory)
		{
			return RVA;
		}
		for (i = 0; i < pContext->pObjects[pContext->iObject].nSections; ++i)
		{
			address_t Address = pContext->pObjects[pContext->iObject].pSections[i].VirtualAddress;
			address_t Size    = pContext->pObjects[pContext->iObject].pSections[i].VirtualSize;
			address_t Data    = pContext->pObjects[pContext->iObject].pSections[i].FileAddress;
			if (Address <= RVA && RVA <= Address + Size)
			{
				offset = pContext->pObjects[pContext->iObject].Offset + Data + RVA - Address;
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
