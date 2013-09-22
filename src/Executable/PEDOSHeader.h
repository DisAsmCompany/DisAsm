/*
* Filename: PEDOSHeader.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: DOS Header structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEDOSHEADER_H__
#define __PEDOSHEADER_H__

#ifndef PEDOSSignature
#define PEDOSSignature 0x5A4D /* MZ */
#endif /* PEDOSSignature */

typedef struct PEDOSHeader_t 
{
	uint16_t magic;
	uint16_t cblp;
	uint16_t cp;
	uint16_t crlc;
	uint16_t cparhdr;
	uint16_t minalloc;
	uint16_t maxalloc;
	uint16_t ss;
	uint16_t sp;
	uint16_t csum;
	uint16_t ip;
	uint16_t cs;
	uint16_t lfarlc;
	uint16_t ovno;
	uint16_t res[4];
	uint16_t oemid;
	uint16_t oeminfo;
	uint16_t res2[10];
	uint32_t lfanew;
}
PEDOSHeader;

#endif /* __PEDOSHEADER_H__ */
