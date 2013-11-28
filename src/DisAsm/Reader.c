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

uint8_t ReaderRead(HREADER hReader, void * buffer, uint32_t size)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	return pContext->pRead(hReader, buffer, size);
}

uint8_t ReaderSeek(HREADER hReader, uint64_t pos)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	return pContext->pSeek(hReader, pContext->base + pos);
}

uint8_t ReaderSkip(HREADER hReader, uint64_t count)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	return pContext->pSkip(hReader, count);
}

uint8_t ReaderSetBase(HREADER hReader, uint64_t base)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	pContext->base = base;
	return 1;
}

void ReaderDestroy(HREADER hReader)
{
	ReaderContext * pContext = (ReaderContext*) hReader;
	pContext->pDestroy(hReader);
}
