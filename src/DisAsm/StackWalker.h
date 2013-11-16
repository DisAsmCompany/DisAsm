/*
 * Filename: StackWalker.h
 * Author:   DisAsmCompany
 * Date:     16/11/2013
 *
 * Description: stack walker - used to capture callstack
 *              for example by crash handler or leak tracker
 *
 *
 */

#pragma once
#ifndef __STACKWALKER_H__
#define __STACKWALKER_H__

typedef struct Context_t
{
	address_t InstructionPointer;
	address_t StackBasePointer;
	address_t StackFramePointer;
}
Context;

enum {MaxCallStack = 32};

void StackWalkInit();
void StackWalkCleanup();
void StackWalk(address_t * callstack, Context * context);
void StackWalkSymbol(address_t address);

#endif /* __STACKWALKER_H__ */
