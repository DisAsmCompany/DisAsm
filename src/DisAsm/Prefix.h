/*
* Filename: Prefix.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: simple structure to describe
*              instruction prefixes
*              
*
*/

#ifndef __PREFIX_H__
#define __PREFIX_H__

#ifndef MAX_PREFIXES
#define MAX_PREFIXES 4
#endif // MAX_PREFIXES

typedef struct Prefix_t
{
	Mnemonic mnemonic;
	OpCode opcode;
}
Prefix;

#endif // __PREFIX_H__
