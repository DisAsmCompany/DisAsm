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

void DisAsmPrintOpCodeMap();
uint8_t DisAsmInstructionDecode(uint8_t size, HREADER hReaders, InstructionInfo * pInfo);

char * DisAsmMnemonicToString(Mnemonic mnemonic);
char * DisAsmRegisterToString(Register reg);

/* for tests */

OpCode _ChooseOpCode(uint8_t * buffer);

#endif /* __DISASM_H__ */
