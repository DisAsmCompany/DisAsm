/*
* Filename: Executable.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: additional API to access functions
*              in executable files, such as PE
*              (Portable Executable)
*
*/

#pragma once
#ifndef __EXECUTABLE_H__
#define __EXECUTABLE_H__

typedef void * HEXECUTABLE;

HEXECUTABLE ExecutableCreate(HREADER hReader, int memory);
void ExecutableDestroy(HEXECUTABLE hExecutable);
uint32_t ExecutableGetNextFunction(HEXECUTABLE hExecutable);

#endif /* __EXECUTABLE_H__ */
