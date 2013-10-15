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

typedef void * HEXECUTABLE;

struct ExecutableContext_t;

typedef Architecture (*pfnExecutableGetArchitecture)(struct ExecutableContext_t * hExecutable);
typedef uint32_t (*pfnExecutableGetEntryPoint)(struct ExecutableContext_t * hExecutable);
typedef uint32_t (*pfnExecutableGetStubEntryPoint)(struct ExecutableContext_t * hExecutable);
typedef uint32_t (*pfnExecutableGetExportCount)(struct ExecutableContext_t * hExecutable);
typedef uint32_t (*pfnExecutableGetExportAddress)(struct ExecutableContext_t * hExecutable, uint32_t index);
typedef char *   (*pfnExecutableGetExportName)(struct ExecutableContext_t * hExecutable, uint32_t index);
typedef char *   (*pfnExecutableGetExportForwarderName)(struct ExecutableContext_t * hExecutable, uint32_t index);
typedef void (*pfnExecutableDestroy)(struct ExecutableContext_t * hExecutable);

typedef struct ExecutableContext_t
{
	uint8_t memory;
	HREADER hReader;
	pfnExecutableGetArchitecture        pGetArchitecture;
	pfnExecutableGetEntryPoint          pGetEntryPoint;
	pfnExecutableGetStubEntryPoint      pGetStubEntryPoint;
	pfnExecutableGetExportCount         pGetExportCount;
	pfnExecutableGetExportAddress       pGetExportAddress;
	pfnExecutableGetExportName          pGetExportName;
	pfnExecutableGetExportForwarderName pGetExportForwarderName;
	pfnExecutableDestroy pDestroy;
	void * pPrivate;
}
ExecutableContext;

HEXECUTABLE ExecutableCreate(HREADER hReader, int memory);
void ExecutableDestroy(HEXECUTABLE hExecutable);
Architecture ExecutableGetArchitecture(HEXECUTABLE hExecutable);
uint32_t ExecutableGetEntryPoint(HEXECUTABLE hExecutable);
uint32_t ExecutableGetStubEntryPoint(HEXECUTABLE hExecutable);
uint32_t ExecutableGetExportCount(HEXECUTABLE hExecutable);
uint32_t ExecutableGetExportAddress(HEXECUTABLE hExecutable, uint32_t index);
char * ExecutableGetExportName(HEXECUTABLE hExecutable, uint32_t index);
char * ExecutableGetExportForwarderName(HEXECUTABLE hExecutable, uint32_t index);

#endif /* __EXECUTABLE_H__ */
