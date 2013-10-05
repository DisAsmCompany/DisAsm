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
	/* DOS signature, either 'MZ' or 'ZM' */
	uint16_t Signature;
	uint16_t BytesInLastPage;
	uint16_t Pages;
	uint16_t Relocations;
	uint16_t Paragraphs;
	uint16_t ParagraphsMin;
	uint16_t ParagraphsMax;
	/* initial value of SS register */
	uint16_t InitialSS;
	/* initial value of SP register */
	uint16_t InitialSP;
	uint16_t CheckSum;
	/* initial value of IP register */
	uint16_t InitialIP;
	/* initial value of CS register */
	uint16_t InitialCS;
	uint16_t AddressRelocation;
	uint16_t OverlayNumber;
	uint16_t Reserved1[4];
	uint16_t OEMID;
	uint16_t OEMInfo;
	uint16_t Reserved2[10];
	uint32_t AddressPE;
}
PEDOSHeader;

#endif /* __PEDOSHEADER_H__ */
