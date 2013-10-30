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
	if (NULL != pContext && NULL != pContext->pDestroy)
	{
		pContext->pDestroy(hExecutable);
	}
	free(hExecutable);
}

Architecture ExecutableGetArchitecture(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->pObjects[pContext->iObject].Arch : ArchUnknown;
}

uint32_t ExecutableGetEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->pObjects[pContext->iObject].EntryPoint : 0;
}

uint32_t ExecutableGetStubEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->pObjects[pContext->iObject].StubEntryPoint : 0;
}

uint32_t ExecutableGetExportCount(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pGetExportCount)
	{
		return pContext->pGetExportCount(pContext);
	}
	return 0;
}

uint32_t ExecutableGetExportAddress(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pGetExportAddress)
	{
		return pContext->pGetExportAddress(pContext, index);
	}
	return 0;
}

char * ExecutableGetExportName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pGetExportName)
	{
		return pContext->pGetExportName(pContext, index);
	}
	return 0;
}

char * ExecutableGetExportForwarderName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	if (NULL != pContext && NULL != pContext->pGetExportForwarderName)
	{
		return pContext->pGetExportForwarderName(pContext, index);
	}
	return 0;
}
