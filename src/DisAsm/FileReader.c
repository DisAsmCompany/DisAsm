/*
* Filename: FileReader.c
* Author:   DisAsmCompany
* Date:     27/09/2013
*
* Description: implementation of Reader API
*              for file system data source
*              
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "DisAsm"

typedef struct FileReaderContext_t
{
	FILE * f;
}
FileReaderContext;

#define AccessPrivateData(x) ((FileReaderContext*)(x->pPrivate))

int FileReaderRead(ReaderContext * pContext, void * buffer, uint32_t size)
{
	return (size == fread(buffer, 1, size, AccessPrivateData(pContext)->f));
}

int FileReaderSeek(ReaderContext * pContext, uint32_t pos)
{
	return (0 == fseek(AccessPrivateData(pContext)->f, pos, SEEK_SET));
}

void FileReaderDestroy(HREADER hReader)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	FileReaderContext * pPrivate = (FileReaderContext*) pContext->pPrivate;
	fclose(pPrivate->f);
	free(pContext);
	free(pPrivate);
}

HREADER FileReaderCreate(const char * path)
{
	FILE * f = fopen(path, "rb");
	ReaderContext * pContext = NULL;
	FileReaderContext * pPrivate = NULL;
	if (NULL == f)
	{
		char fullpath[32768];
		sprintf(fullpath, "%s\\%s", "C:\\Windows\\System32\\", path);
		f = fopen(fullpath, "rb");
		if (NULL == f)
		{
			return NULL;
		}
	}
	pContext = (ReaderContext*) malloc(sizeof(ReaderContext));
	pPrivate = (FileReaderContext*) malloc(sizeof(FileReaderContext));
	pPrivate->f = f;
	pContext->pRead    = FileReaderRead;
	pContext->pSeek    = FileReaderSeek;
	pContext->pDestroy = FileReaderDestroy;
	pContext->pPrivate = pPrivate;
	return (HREADER) pContext;
}
