/*
* Filename: DisAsmContext.h
* Author:   DisAsmCompany
* Date:     24/09/2013
*
* Description: disassembler state
*              (aka private data)
*              
*
*/

#pragma once
#ifndef __DISASMCONTEXT_H__
#define __DISASMCONTEXT_H__

typedef struct DisAsmContext_t
{
	HREADER hReader;
	uint8_t size;
	uint8_t currentSize;
	uint8_t error;
}
DisAsmContext;

#endif /* __DISASMCONTEXT_H__ */
