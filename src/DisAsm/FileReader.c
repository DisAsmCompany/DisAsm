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
	return 1;
#else /* _WIN32 */
	return (size == fread(buffer, 1, size, AccessPrivateData(pContext)->f));
#endif /* _WIN32 */
}

int FileReaderSeek(ReaderContext * pContext, uint32_t pos)
{
#ifdef _WIN32
	LARGE_INTEGER from = {0}, to = {0};
	from.QuadPart = pos;
	return !!SetFilePointerEx(AccessPrivateData(pContext)->hFile, from, &to, FILE_BEGIN);
#else /* _WIN32 */
	return (0 == fseek(AccessPrivateData(pContext)->f, pos, SEEK_SET));
#endif /* _WIN32 */
}

int FileReaderSkip(ReaderContext * pContext, uint32_t count)
{
#ifdef _WIN32
	LARGE_INTEGER from = {0}, to = {0};
	from.QuadPart = count;
	return !!SetFilePointerEx(AccessPrivateData(pContext)->hFile, from, &to, FILE_CURRENT);
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
		char fullpath[32768];
		sprintf(fullpath, "%s\\%s", "C:\\Windows\\System32", path);
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
