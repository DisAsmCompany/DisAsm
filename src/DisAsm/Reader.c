/*
* Filename: ReaderReader.c
* Author:   DisAsmCompany
* Date:     27/09/2013
*
* Description: abstract Reader API
*              (e.g. read from memory,
*              file, HTTP, FTP, etc)
*
*/

#include "DisAsm"

int ReaderRead(HREADER hReader, void * buffer, uint32_t size)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	return pContext->pRead(hReader, buffer, size);
}

int ReaderSeek(HREADER hReader, uint64_t pos)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	return pContext->pSeek(hReader, pos);
}

int ReaderSkip(HREADER hReader, uint64_t count)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	return pContext->pSkip(hReader, count);
}

void ReaderDestroy(HREADER hReader)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	pContext->pDestroy(hReader);
}
