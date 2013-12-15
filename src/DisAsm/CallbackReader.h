/*
* Filename: CallbackReader.h
* Author:   DisAsmCompany
* Date:     29/11/2013
*
* Description: simple callback reader API
*              
*              
*
*/

#pragma once
#ifndef __CALLBACKREADER_H__5D98E112_E391_4525_BB0E_87612A449F1F__
#define __CALLBACKREADER_H__5D98E112_E391_4525_BB0E_87612A449F1F__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct CallbackReader_t
{
	pfnRead    pRead;
	pfnSeek    pSeek;
	pfnSkip    pSkip;
	pfnSize    pSize;
	pfnDestroy pDestroy;
	void *     pPrivate;
	uint8_t * buffer;
	uint64_t offset;
	uint64_t length;
}
CallbackReader;

uint8_t CallbackRead(ReaderContext * pContext, void * buffer, uint32_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CALLBACKREADER_H__5D98E112_E391_4525_BB0E_87612A449F1F__ */
