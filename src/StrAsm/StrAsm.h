/*
* Filename: StrAsm.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: StrAsm API declaration :	
*              convert instruction to
*              string representation
*
*/

#pragma once
#ifndef __STRASM_H__
#define __STRASM_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void StrAsmPrintInstruction(InstructionInfo * info);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STRASM_H__ */
