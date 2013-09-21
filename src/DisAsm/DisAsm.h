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

int DisAsmInstructionDecode(unsigned char * buffer, InstructionInfo * info);

#endif // __DISASM_H__
