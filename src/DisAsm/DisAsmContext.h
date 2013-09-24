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
	uint8_t * buffer;
	uint8_t length;
	uint8_t size;
}
DisAsmContext;

#endif // __DISASMCONTEXT_H__
