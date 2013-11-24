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
#else /* OS_WINDOWS */
	int hFile;
#endif /* OS_WINDOWS */
	uint64_t size;
	uint64_t offset;
}
FileReaderContext;

#undef THIS
#define THIS ((FileReaderContext*)(pContext->pPrivate))

uint8_t FileReaderRead(ReaderContext * pContext, void * buffer, uint32_t size)
{
	uint32_t offset = 0;
	while (offset < size)
	{
#ifdef OS_WINDOWS
		DWORD count = 0;
		if (!ReadFile(THIS->hFile, (uint8_t*)buffer + offset, size - offset, &count, NULL) || 0 == count)
#else /* OS_WINDOWS */
		uint32_t count = 0;
		if (-1 == (count = read(THIS->hFile, (uint8_t*)buffer + offset, size - offset)))
#endif /* OS_WINDOWS */
		{
			return 0;
		}
		offset += count;
	}
	THIS->offset += size;
	return 1;
}

uint8_t FileReaderSeek(ReaderContext * pContext, uint64_t pos)
{
	if (pos < THIS->size)
	{
#ifdef OS_WINDOWS
		LARGE_INTEGER from = {0}, to = {0};
		from.QuadPart = pos;
		if (SetFilePointerEx(THIS->hFile, from, &to, FILE_BEGIN))
#else /* OS_WINDOWS */
		if (-1 != lseek(THIS->hFile, pos, SEEK_SET))
#endif /* OS_WINDOWS */
		{
			THIS->offset = pos;
			return 1;
		}
	}
	return 0;
}

uint8_t FileReaderSkip(ReaderContext * pContext, uint64_t count)
{
	if (THIS->offset + count < THIS->size)
	{
#ifdef OS_WINDOWS
		LARGE_INTEGER from = {0}, to = {0};
		from.QuadPart = count;
		if (SetFilePointerEx(THIS->hFile, from, &to, FILE_CURRENT))
#else /* OS_WINDOWS */
		if (-1 != lseek(THIS->hFile, count, SEEK_CUR))
#endif /* OS_WINDOWS */
		{
			THIS->offset += count;
			return 1;
		}
	}
	return 0;
}

void FileReaderDestroy(ReaderContext * pContext)
{
#ifdef OS_WINDOWS
	CloseHandle(THIS->hFile);
#else /* OS_WINDOWS */
	close(THIS->hFile);
#endif /* OS_WINDOWS */
	free(THIS);
	free(pContext);
}

HREADER FileReaderCreate(const char * path)
{
#ifdef OS_WINDOWS
	LARGE_INTEGER li = {0};
	HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#else /* OS_WINDOWS */
	int hFile = open(path, O_RDONLY);
#endif /* OS_WINDOWS */
	ReaderContext * pContext = NULL;
	FileReaderContext * pPrivate = NULL;
#ifdef OS_WINDOWS
	if (INVALID_HANDLE_VALUE == hFile)
#else /* OS_WINDOWS */
	if (-1 == hFile)
#endif /* OS_WINDOWS */
	{
		char fullpath[NtfsMaxPath] = {0};
		xstrcat(fullpath, NtfsMaxPath, "C:\\Windows\\System32\\");
		xstrcat(fullpath, NtfsMaxPath, path);
#ifdef OS_WINDOWS
		hFile = CreateFileA(fullpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
#else /* OS_WINDOWS */
		hFile = open(fullpath, O_RDONLY);
		if (-1 == hFile)
#endif /* OS_WINDOWS */
		{
			return NULL;
		}
	}
	pContext = (ReaderContext*) calloc(1, sizeof(ReaderContext));
	pPrivate = (FileReaderContext*) calloc(1, sizeof(FileReaderContext));

	pPrivate->hFile = hFile;
#ifdef OS_WINDOWS
	GetFileSizeEx(hFile, &li);
	pPrivate->size = li.QuadPart;
#else /* OS_WINDOWS */
	pPrivate->size = lseek(hFile, 0, SEEK_END);
	lseek(hFile, 0, SEEK_SET);
#endif /* OS_WINDOWS */
	pPrivate->offset = 0;

	pContext->pRead    = FileReaderRead;
	pContext->pSeek    = FileReaderSeek;
	pContext->pSkip    = FileReaderSkip;
	pContext->pDestroy = FileReaderDestroy;
	pContext->pPrivate = pPrivate;
	return (HREADER) pContext;
}
