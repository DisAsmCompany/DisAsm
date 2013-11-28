/*
* Filename: CallbackReader.c
* Author:   DisAsmCompany
* Date:     29/11/2013
*
* Description: simple callback reader API
*              
*              
*
*/

#include "DisAsm"

uint8_t CallbackRead(ReaderContext * pContext, void * buffer, uint32_t size)
{
	CallbackReader * pData = (CallbackReader*) pContext->pPrivate;
	if ((pData->offset + size <= pData->length) || 0 == pData->length)
	{
		memcpy(buffer, pData->buffer + pData->offset, size);
		pData->offset += size;
		return 1;
	}
	return 0;
}
