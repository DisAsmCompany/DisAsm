/*
* Filename: DisAsm.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: DisAsm API entry points :
*              public functions to be
*              called by users.
*
*/

#pragma once
#ifndef __DISASM_H__
#define __DISASM_H__

typedef void * HDISASM;

HDISASM DisAsmCreate(uint32_t bitness);
void DisAsmDestroy(HDISASM hDisAsm);

void DisAsmPrintOpCodeMap(HDISASM hDisAsm);
uint8_t DisAsmInstructionDecode(HDISASM hDisAsm, HREADER hReaders, InstructionInfo * pInfo);

/* for tests */

OpCode _ChooseOpCode(uint8_t * buffer);

#endif /* __DISASM_H__ */
