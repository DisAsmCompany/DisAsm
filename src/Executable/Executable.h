/*
* Filename: Executable.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: additional API to access functions
*              in executable files, such as PE
*              (Portable Executable)
*
*/

#pragma once
#ifndef __EXECUTABLE_H__
#define __EXECUTABLE_H__

#define CHECK_CALL(x) do { if (0 == (x)) return 0; } while (0);
#define CHECK_ALLOC(x) do { if (NULL == (x)) return 0; } while (0);

typedef void * HEXECUTABLE;

struct ExecutableContext_t;

typedef void (*pfnExecutableDestroy)(struct ExecutableContext_t * hExecutable);

typedef struct ExecutableSection_t
{
	uint32_t VirtualAddress;
	uint32_t VirtualSize;
	uint32_t VirtualAlignment;
	uint32_t FileAddress;
	uint32_t FileSize;
	uint32_t FileAlignment;
}
ExecutableSection;

typedef struct ExecutableSymbol_t
{
	uint32_t Name;
	uint32_t Ordinal;
	uint32_t Address;
	uint32_t Forwarder;
}
ExecutableSymbol;

typedef struct ExecutableObject_t
{
	Architecture Arch;
	uint32_t EntryPoint;
	uint32_t StubEntryPoint;
	uint32_t Base;

	uint32_t nSections;
	ExecutableSection * pSections;

	uint32_t nExports;
	ExecutableSymbol * pExports;
}
ExecutableObject;

typedef struct ExecutableContext_t
{
	uint8_t memory;
	HREADER hReader;
	pfnExecutableDestroy pDestroy;
	void * pPrivate;
	ExecutableObject * pObjects;
	uint32_t nObjects;
	uint32_t iObject;
}
ExecutableContext;

HEXECUTABLE ExecutableCreate(HREADER hReader, int memory);
void ExecutableDestroy(HEXECUTABLE hExecutable);
Architecture ExecutableGetArchitecture(HEXECUTABLE hExecutable);
uint32_t ExecutableGetBase(HEXECUTABLE hExecutable);
uint32_t ExecutableGetEntryPoint(HEXECUTABLE hExecutable);
uint32_t ExecutableGetStubEntryPoint(HEXECUTABLE hExecutable);
uint32_t ExecutableGetExportCount(HEXECUTABLE hExecutable);
uint32_t ExecutableGetExportAddress(HEXECUTABLE hExecutable, uint32_t index);
char * ExecutableGetExportName(HEXECUTABLE hExecutable, uint32_t index);
char * ExecutableGetExportForwarderName(HEXECUTABLE hExecutable, uint32_t index);

uint32_t ExecutableRVAToOffset(HEXECUTABLE hExecutable, uint32_t RVA);
char * FetchString(ExecutableContext * pContext, uint32_t address);

#endif /* __EXECUTABLE_H__ */
