/*
* Filename: PENTHeaders.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: NT Headers structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PENTHEADERS_H__
#define __PENTHEADERS_H__

#ifndef PENTSignature
#define PENTSignature 0x00004550 /* PE */
#endif /* PENTSignature */

typedef struct PENTHeaders_t
{
	uint32_t Signature;
	PEFileHeader FileHeader;
	PEOptionalHeader OptionalHeader;
}
PENTHeaders;

#endif /* __PENTHEADERS_H__ */
