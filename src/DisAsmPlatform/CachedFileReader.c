/*
* Filename: CachedMemoryReader.h
* Author:   DisAsmCompany
* Date:     20/12/2013
*
* Description: implementation of Reader API
*              for file system data source (cached)
*              
*
*/

#include "../DisAsm/DisAsm"
#include "DisAsmPlatform"

typedef struct CachedFileReaderContext_t
{
	HREADER hFileReader;
	HREADER hMemoryReader;
	uint8_t * bytes;
}
CachedFileReaderContext;

#undef THIS
#define THIS ((CachedFileReaderContext*)(pContext->pPrivate))

uint8_t CachedFileReaderRead(ReaderContext * pContext, void * buffer, uint32_t size)
{
	return ReaderRead(THIS->hMemoryReader, buffer, size);
}

uint8_t CachedFileReaderSeek(ReaderContext * pContext, uint64_t pos)
{
	return ReaderSeek(THIS->hMemoryReader, pos);
}

uint8_t CachedFileReaderSkip(ReaderContext * pContext, int64_t count)
{
	return ReaderSkip(THIS->hMemoryReader, count);
}

uint8_t CachedFileReaderSize(ReaderContext * pContext, uint64_t * size)
{
	return ReaderSize(THIS->hMemoryReader, size);
}

void CachedFileReaderDestroy(ReaderContext * pContext)
{
	ReaderDestroy(THIS->hFileReader);
	ReaderDestroy(THIS->hMemoryReader);
	free(THIS->bytes);
	free(THIS);
	free(pContext);
}

HREADER CachedFileReaderCreate(const char * path)
{
	uint32_t block = 0x10000;
	uint32_t offset = 0;
	uint64_t size64 = 0;
	uint32_t size = 0;
	uint8_t * bytes = NULL;
	ReaderContext * pContext = NULL;
	CachedFileReaderContext * pPrivate = NULL;

	HREADER hMemoryReader = NULL;
	HREADER hFileReader = FileReaderCreate(path);
	if (NULL == hFileReader)
	{
		return NULL;
	}
	ReaderSize(hFileReader, &size64);
	if (size64 > 0x80000000UL)
	{
		/* too big to cache in memory */
		ReaderDestroy(hFileReader);
		return NULL;
	}
	size = (uint32_t) size64;

	bytes = calloc(1, size);
	if (NULL == bytes)
	{
		ReaderDestroy(hFileReader);
		return NULL;
	}
	while (offset < size)
	{
		uint32_t count = (size - offset > block) ? block : (size - offset);
		if (0 == ReaderRead(hFileReader, bytes + offset, count))
		{
			free(bytes);
			ReaderDestroy(hFileReader);
			return NULL;
		}
		offset += count;
	}
	hMemoryReader = MemoryReaderCreate((native_t) bytes, size);
	if (NULL == hMemoryReader)
	{
		ReaderDestroy(hFileReader);
		free(bytes);
		return NULL;
	}
	if (NULL == (pContext = (ReaderContext*) calloc(1, sizeof(ReaderContext))))
	{
		ReaderDestroy(hMemoryReader);
		ReaderDestroy(hFileReader);
		free(bytes);
		return NULL;
	}
	if (NULL == (pPrivate = (CachedFileReaderContext*) calloc(1, sizeof(CachedFileReaderContext))))
	{
		ReaderDestroy(hMemoryReader);
		ReaderDestroy(hFileReader);
		free(pContext);
		free(bytes);
		return NULL;
	}
	pContext->pRead    = CachedFileReaderRead;
	pContext->pSeek    = CachedFileReaderSeek;
	pContext->pSkip    = CachedFileReaderSkip;
	pContext->pSize    = CachedFileReaderSize;
	pContext->pDestroy = CachedFileReaderDestroy;
	pContext->pPrivate = pPrivate;
	THIS->bytes = bytes;
	THIS->hFileReader = hFileReader;
	THIS->hMemoryReader = hMemoryReader;
	return (HREADER) pContext;
}
