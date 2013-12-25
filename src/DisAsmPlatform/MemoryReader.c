/*
* Filename: MemoryReader.c
* Author:   DisAsmCompany
* Date:     27/09/2013
*
* Description: implementation of Reader API
*              for file system data source
*              
*
*/

#include "../DisAsm/DisAsm"
#include "DisAsmPlatform"

typedef struct MemoryReaderContext_t
{
	uint8_t * buffer;
	uint64_t size;
	uint64_t offset;
}
MemoryReaderContext;

#undef THIS
#define THIS ((MemoryReaderContext*)(pContext->pPrivate))

uint8_t MemoryReaderRead(ReaderContext * pContext, void * buffer, uint32_t size)
{
	if (THIS->offset + size <= THIS->size)
	{
		memcpy(buffer, THIS->buffer + THIS->offset, size);
		THIS->offset += size;
		return 1;
	}
	return 0;
}

uint8_t MemoryReaderSeek(ReaderContext * pContext, uint64_t pos)
{
	if (pos < THIS->size)
	{
		THIS->offset = pos;
		return 1;
	}
	return 0;
}

uint8_t MemoryReaderSkip(ReaderContext * pContext, int64_t count)
{
	if (THIS->offset + count < THIS->size)
	{
		THIS->offset += count;
		return 1;
	}
	return 0;
}

uint8_t MemoryReaderSize(ReaderContext * pContext, uint64_t * size)
{
	*size = THIS->size;
	return 1;
}

void MemoryReaderDestroy(ReaderContext * pContext)
{
	free(pContext->pPrivate);
	free(pContext);
}

HREADER MemoryReaderCreate(native_t buffer, uint32_t size)
{
	ReaderContext * pContext = NULL;
	MemoryReaderContext * pPrivate = NULL;
	if (0 == buffer)
	{
		return NULL;
	}
	pContext = (ReaderContext*) calloc(1, sizeof(ReaderContext));
	if (NULL == pContext)
	{
		return NULL;
	}
	pPrivate = (MemoryReaderContext*) calloc(1, sizeof(MemoryReaderContext));
	if (NULL == pPrivate)
	{
		free(pContext);
		return NULL;
	}
	pPrivate->buffer   = (uint8_t*) buffer;
	pPrivate->size     = size;
	pPrivate->offset   = 0;
	pContext->pRead    = MemoryReaderRead;
	pContext->pSeek    = MemoryReaderSeek;
	pContext->pSkip    = MemoryReaderSkip;
	pContext->pSize    = MemoryReaderSize;
	pContext->pDestroy = MemoryReaderDestroy;
	pContext->pPrivate = pPrivate;
	return (HREADER) pContext;
}
