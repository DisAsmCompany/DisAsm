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

#ifndef __PREFIX_H__1C4E9DF6_A838_4FF4_AD2C_390BD658E0E8__
#define __PREFIX_H__1C4E9DF6_A838_4FF4_AD2C_390BD658E0E8__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef MAX_PREFIXES
#define MAX_PREFIXES 4
#endif /* MAX_PREFIXES */

typedef struct Prefix_t
{
	Mnemonic mnemonic;
	uint32_t opcode;
}
Prefix;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PREFIX_H__1C4E9DF6_A838_4FF4_AD2C_390BD658E0E8__ */
