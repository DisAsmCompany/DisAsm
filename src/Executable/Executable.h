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

#define CHECK_CALL(x) for (;;) { if (0 == (x)) return 0; break; }
#define CHECK_ALLOC(x) for (;;) { if (NULL == (x)) return 0; break; }

typedef void * HEXECUTABLE;

struct ExecutableContext_t;

typedef void (*pfnExecutableDestroy)(struct ExecutableContext_t * hExecutable);

typedef struct ExecutableSection_t
{
	address_t VirtualAddress;
	uint64_t  VirtualSize;
	uint32_t  VirtualAlignment;
	address_t FileAddress;
	uint64_t  FileSize;
	uint32_t  FileAlignment;
}
ExecutableSection;

typedef struct ExecutableSymbol_t
{
	address_t Name;
	uint32_t  Ordinal;
	address_t Address;
	address_t Forwarder;
}
ExecutableSymbol;

typedef struct ExecutableObject_t
{
	Architecture Arch;
	address_t EntryPoint;
	address_t StubEntryPoint;
	address_t Base;
	address_t Offset;

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
address_t ExecutableGetBase(HEXECUTABLE hExecutable);
address_t ExecutableGetEntryPoint(HEXECUTABLE hExecutable);
address_t ExecutableGetStubEntryPoint(HEXECUTABLE hExecutable);
uint32_t  ExecutableGetExportCount(HEXECUTABLE hExecutable);
address_t ExecutableGetExportAddress(HEXECUTABLE hExecutable, uint32_t index);
char * ExecutableGetExportName(HEXECUTABLE hExecutable, uint32_t index);
char * ExecutableGetExportForwarderName(HEXECUTABLE hExecutable, uint32_t index);

/* FAT executable API */
uint32_t ExecutableGetObjectCount(HEXECUTABLE hExecutable);
uint32_t ExecutableGetCurrentObject(HEXECUTABLE hExecutable);
uint32_t ExecutableSetCurrentObject(HEXECUTABLE hExecutable, uint32_t index);

address_t ExecutableRVAToOffset(HEXECUTABLE hExecutable, address_t RVA);
char * FetchString(ExecutableContext * pContext, address_t address);

#endif /* __EXECUTABLE_H__ */
