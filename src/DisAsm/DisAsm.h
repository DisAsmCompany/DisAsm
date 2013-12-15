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
#ifndef __DISASM_H__38936F9A_D7E6_4F01_B769_C319321BE325__
#define __DISASM_H__38936F9A_D7E6_4F01_B769_C319321BE325__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void DisAsmPrintOpCodeMap();
uint8_t DisAsmInstructionDecode(uint8_t size, HREADER hReader, InstructionInfo * pInfo);

char * DisAsmMnemonicToString(Mnemonic mnemonic);
char * DisAsmRegisterToString(Register reg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DISASM_H__38936F9A_D7E6_4F01_B769_C319321BE325__ */
