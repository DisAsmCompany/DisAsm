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

#include "DisAsm"

typedef struct FileReaderContext_t
{
#ifdef OS_WINDOWS
	HANDLE hFile;
	uint64_t size;
	uint64_t offset;
#else /* OS_WINDOWS */
	FILE * f;
#endif /* OS_WINDOWS */
}
FileReaderContext;

#define AccessPrivateData(x) ((FileReaderContext*)(x->pPrivate))

int FileReaderRead(ReaderContext * pContext, void * buffer, uint32_t size)
{
#ifdef OS_WINDOWS
	uint32_t offset = 0;
	while (offset < size)
	{
		DWORD read = 0;
		if (!ReadFile(AccessPrivateData(pContext)->hFile, (uint8_t*)buffer + offset, size - offset, &read, NULL) || 0 == read)
		{
			return 0;
		}
		offset += read;
	}
	AccessPrivateData(pContext)->offset += size;
	return 1;
#else /* OS_WINDOWS */
	return (size == fread(buffer, 1, size, AccessPrivateData(pContext)->f));
#endif /* OS_WINDOWS */
}

int FileReaderSeek(ReaderContext * pContext, uint64_t pos)
{
#ifdef OS_WINDOWS
	if (pos < AccessPrivateData(pContext)->size)
	{
		LARGE_INTEGER from = {0}, to = {0};
		from.QuadPart = pos;
		if (SetFilePointerEx(AccessPrivateData(pContext)->hFile, from, &to, FILE_BEGIN))
		{
			AccessPrivateData(pContext)->offset = pos;
			return 1;
		}
	}
	return 0;
#else /* OS_WINDOWS */
	return (0 == fseek(AccessPrivateData(pContext)->f, pos, SEEK_SET));
#endif /* OS_WINDOWS */
}

int FileReaderSkip(ReaderContext * pContext, uint64_t count)
{
#ifdef OS_WINDOWS
	if (AccessPrivateData(pContext)->offset + count < AccessPrivateData(pContext)->size)
	{
		LARGE_INTEGER from = {0}, to = {0};
		from.QuadPart = count;
		if (SetFilePointerEx(AccessPrivateData(pContext)->hFile, from, &to, FILE_CURRENT))
		{
			AccessPrivateData(pContext)->offset += count;
			return 1;
		}
	}
	return 0;
#else /* OS_WINDOWS */
	return (0 == fseek(AccessPrivateData(pContext)->f, count, SEEK_CUR));
#endif /* OS_WINDOWS */
}

void FileReaderDestroy(ReaderContext * hReader)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	FileReaderContext * pPrivate = (FileReaderContext*) pContext->pPrivate;
#ifdef OS_WINDOWS
	CloseHandle(pPrivate->hFile);
#else /* OS_WINDOWS */
	fclose(pPrivate->f);
#endif /* OS_WINDOWS */
	free(pContext);
	free(pPrivate);
}

HREADER FileReaderCreate(const char * path)
{
#ifdef OS_WINDOWS
	LARGE_INTEGER li = {0};
	HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#else /* OS_WINDOWS */
	FILE * f = fopen(path, "rb");
#endif /* OS_WINDOWS */
	ReaderContext * pContext = NULL;
	FileReaderContext * pPrivate = NULL;
#ifdef OS_WINDOWS
	if (INVALID_HANDLE_VALUE == hFile)
#else /* OS_WINDOWS */
	if (NULL == f)
#endif /* OS_WINDOWS */
	{
		char fullpath[32768] = {0};
		xstrcat(fullpath, 32768, "C:\\Windows\\System32\\");
		xstrcat(fullpath, 32768, path);
#ifdef OS_WINDOWS
		hFile = CreateFileA(fullpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
#else /* OS_WINDOWS */
		f = fopen(fullpath, "rb");
		if (NULL == f)
#endif /* OS_WINDOWS */
		{
			return NULL;
		}
	}
	pContext = (ReaderContext*) calloc(1, sizeof(ReaderContext));
	pPrivate = (FileReaderContext*) calloc(1, sizeof(FileReaderContext));
#ifdef OS_WINDOWS
	pPrivate->hFile = hFile;
	GetFileSizeEx(hFile, &li);
	pPrivate->size = li.QuadPart;
	pPrivate->offset = 0;
#else /* OS_WINDOWS */
	pPrivate->f = f;
#endif /* OS_WINDOWS */
	pContext->pRead    = FileReaderRead;
	pContext->pSeek    = FileReaderSeek;
	pContext->pSkip    = FileReaderSkip;
	pContext->pDestroy = FileReaderDestroy;
	pContext->pPrivate = pPrivate;
	return (HREADER) pContext;
}
