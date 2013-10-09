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

#define PEDOSHeaderSignature 1
#define PEDOSHeaderAddressPE 2

static const SDFElement PEDOSHeader[] =
{
	/* DOS signature, either 'MZ' or 'ZM' */
	{"Signature        ", PEDOSHeaderSignature, kUnsigned, 2, 1},
	{"BytesInLastPage  ", 0, kUnsigned, 2, 1},
	{"Pages            ", 0, kUnsigned, 2, 1},
	{"Relocations      ", 0, kUnsigned, 2, 1},
	{"Paragraphs       ", 0, kUnsigned, 2, 1},
	{"ParagraphsMin    ", 0, kUnsigned, 2, 1},
	{"ParagraphsMax    ", 0, kUnsigned, 2, 1},
	/* initial value of SS register */
	{"InitialSS        ", 0, kUnsigned, 2, 1},
	/* initial value of SP register */
	{"InitialSP        ", 0, kUnsigned, 2, 1},
	{"CheckSum         ", 0, kUnsigned, 2, 1},
	/* initial value of IP register */
	{"InitialIP        ", 0, kUnsigned, 2, 1},
	/* initial value of CS register */
	{"InitialCS        ", 0, kUnsigned, 2, 1},
	{"AddressRelocation", 0, kUnsigned, 2, 1},
	{"OverlayNumber    ", 0, kUnsigned, 2, 1},
	{"Reserved         ", 0, kReserved, 2, 4},
	{"OEMID            ", 0, kUnsigned, 2, 1},
	{"OEMInfo          ", 0, kUnsigned, 2, 1},
	{"Reserved         ", 0, kReserved, 2, 10},
	{"AddressPE        ", PEDOSHeaderAddressPE, kUnsigned, 4, 1},
};
static const uint32_t PEDOSHeaderSize = sizeof(PEDOSHeader) / sizeof(PEDOSHeader[0]);

#endif /* __PEDOSHEADER_H__ */
