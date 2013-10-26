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

HEXECUTABLE ExecutableCreate(HREADER hReader, int memory)
{
	ExecutableContext * pContext = NULL;

	if (NULL == hReader)
	{
		return NULL;
	}
	pContext = (ExecutableContext*) malloc(sizeof(ExecutableContext));
	if (NULL == pContext)
	{
		return NULL;
	}
	memset(pContext, 0, sizeof(ExecutableContext));
	pContext->hReader = hReader;
	pContext->memory = memory;
	if (0 == PEFileCreate(pContext) && 
		0 == NEFileCreate(pContext) &&
		0 == LXFileCreate(pContext) &&
		0 == MachOFileCreate(pContext) && 
		0 == ELFFileCreate(pContext))
	{
		free(pContext);
		return 0;
	}
	return (HEXECUTABLE) pContext;
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
	return NULL != pContext ? pContext->Arch : ArchUnknown;
}

uint32_t ExecutableGetEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->EntryPoint : 0;
}

uint32_t ExecutableGetStubEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return NULL != pContext ? pContext->StubEntryPoint : 0;
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
