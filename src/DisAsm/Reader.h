/*
* Filename: ReaderReader.h
* Author:   DisAsmCompany
* Date:     27/09/2013
*
* Description: abstract Reader API
*              (e.g. read from memory,
*              file, HTTP, FTP, etc)
*
*/

#pragma once
#ifndef __READER_H__
#define __READER_H__

typedef void * HREADER;

struct ReaderContext_t;

typedef int  (*pfnRead)(struct ReaderContext_t * hReader, void * buffer, uint32_t size);
typedef int  (*pfnSeek)(struct ReaderContext_t * hReader, uint32_t pos);
typedef void (*pfnDestroy)(struct ReaderContext_t * hReader);

typedef struct ReaderContext_t
{
	pfnRead    pRead;
	pfnSeek    pSeek;
	pfnDestroy pDestroy;
	void *     pPrivate;
}
ReaderContext;

int ReaderRead(HREADER hReader, void * buffer, uint32_t size);
int ReaderSeek(HREADER hReader, uint32_t pos);
void ReaderDestroy(HREADER hReader);

#endif // __READER_H__
