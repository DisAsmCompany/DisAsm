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
#ifdef _WIN32
	HANDLE hFile;
	uint64_t size;
	uint64_t offset;
#else /* _WIN32 */
	FILE * f;
#endif /* _WIN32 */
}
FileReaderContext;

#define AccessPrivateData(x) ((FileReaderContext*)(x->pPrivate))

int FileReaderRead(ReaderContext * pContext, void * buffer, uint32_t size)
{
#ifdef _WIN32
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
#else /* _WIN32 */
	return (size == fread(buffer, 1, size, AccessPrivateData(pContext)->f));
#endif /* _WIN32 */
}

int FileReaderSeek(ReaderContext * pContext, uint64_t pos)
{
#ifdef _WIN32
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
#else /* _WIN32 */
	return (0 == fseek(AccessPrivateData(pContext)->f, pos, SEEK_SET));
#endif /* _WIN32 */
}

int FileReaderSkip(ReaderContext * pContext, uint64_t count)
{
#ifdef _WIN32
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
#else /* _WIN32 */
	return (0 == fseek(AccessPrivateData(pContext)->f, count, SEEK_CUR));
#endif /* _WIN32 */
}

void FileReaderDestroy(ReaderContext * hReader)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	FileReaderContext * pPrivate = (FileReaderContext*) pContext->pPrivate;
#ifdef _WIN32
	CloseHandle(pPrivate->hFile);
#else /* _WIN32 */
	fclose(pPrivate->f);
#endif /* _WIN32 */
	free(pContext);
	free(pPrivate);
}

HREADER FileReaderCreate(const char * path)
{
#ifdef _WIN32
	LARGE_INTEGER li = {0};
	HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#else /* _WIN32 */
	FILE * f = fopen(path, "rb");
#endif /* _WIN32 */
	ReaderContext * pContext = NULL;
	FileReaderContext * pPrivate = NULL;
#ifdef _WIN32
	if (INVALID_HANDLE_VALUE == hFile)
#else /* _WIN32 */
	if (NULL == f)
#endif /* _WIN32 */
	{
		char fullpath[32768] = {0};
		xstrcat(fullpath, 32768, "C:\\Windows\\System32\\");
		xstrcat(fullpath, 32768, path);
#ifdef _WIN32
		hFile = CreateFileA(fullpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
#else /* _WIN32 */
		f = fopen(fullpath, "rb");
		if (NULL == f)
#endif /* _WIN32 */
		{
			return NULL;
		}
	}
	pContext = (ReaderContext*) calloc(1, sizeof(ReaderContext));
	pPrivate = (FileReaderContext*) calloc(1, sizeof(FileReaderContext));
#ifdef _WIN32
	pPrivate->hFile = hFile;
	GetFileSizeEx(hFile, &li);
	pPrivate->size = li.QuadPart;
	pPrivate->offset = 0;
#else /* _WIN32 */
	pPrivate->f = f;
#endif /* _WIN32 */
	pContext->pRead    = FileReaderRead;
	pContext->pSeek    = FileReaderSeek;
	pContext->pSkip    = FileReaderSkip;
	pContext->pDestroy = FileReaderDestroy;
	pContext->pPrivate = pPrivate;
	return (HREADER) pContext;
}
