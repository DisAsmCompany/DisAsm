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
#ifndef __READER_H__8BC98649_9F3A_4B24_B656_5B6E41194AC2__
#define __READER_H__8BC98649_9F3A_4B24_B656_5B6E41194AC2__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void * HREADER;

struct ReaderContext_t;

typedef int  (*pfnRead)(struct ReaderContext_t * hReader, void * buffer, uint32_t size);
typedef int  (*pfnSeek)(struct ReaderContext_t * hReader, uint64_t pos);
typedef int  (*pfnSkip)(struct ReaderContext_t * hReader, uint64_t count);
typedef void (*pfnDestroy)(struct ReaderContext_t * hReader);

typedef struct ReaderContext_t
{
	pfnRead    pRead;
	pfnSeek    pSeek;
	pfnSkip    pSkip;
	pfnDestroy pDestroy;
	void *     pPrivate;
}
ReaderContext;

int ReaderRead(HREADER hReader, void * buffer, uint32_t size);
int ReaderSeek(HREADER hReader, uint64_t pos);
int ReaderSkip(HREADER hReader, uint64_t count);
void ReaderDestroy(HREADER hReader);

typedef struct CallbackReader_t
{
	ReaderContext context;
	uint8_t * buffer;
	uint64_t offset;
	uint64_t length;
}
CallbackReader;

int CallbackRead(ReaderContext * pContext, void * buffer, uint32_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __READER_H__8BC98649_9F3A_4B24_B656_5B6E41194AC2__ */
