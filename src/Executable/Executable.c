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
	pContext->hReader = hReader;
	pContext->memory = memory;
	if (0 == PEFileCreate(pContext) && 0 == MachOFileCreate(pContext) && 0 == ELFFileCreate(pContext))
	{
		free(pContext);
		return 0;
	}
	return (HEXECUTABLE) pContext;
}

void ExecutableDestroy(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	pContext->pDestroy(hExecutable);
	free(hExecutable);
}

Architecture ExecutableGetArchitecture(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return pContext->pGetArchitecture(pContext);
}

uint32_t ExecutableGetEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return pContext->pGetEntryPoint(pContext);
}

uint32_t ExecutableGetStubEntryPoint(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return pContext->pGetStubEntryPoint(pContext);
}

uint32_t ExecutableGetExportCount(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return pContext->pGetExportCount(pContext);
}

uint32_t ExecutableGetExportAddress(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return pContext->pGetExportAddress(pContext, index);
}

char * ExecutableGetExportName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return pContext->pGetExportName(pContext, index);
}

char * ExecutableGetExportForwarderName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return pContext->pGetExportForwarderName(pContext, index);
}
