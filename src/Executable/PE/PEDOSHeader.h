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

#define PEDOSHeaderSignature 0
#define PEDOSHeaderAddressPE 0x3C

static const SDFElement PEDOSHeader[] =
{
	{"PE DOS Header"},
	/* DOS signature, either 'MZ' or 'ZM' */
	{"Signature        ", kUnsigned, 2, 1},
	{"BytesInLastPage  ", kUnsigned, 2, 1},
	{"Pages            ", kUnsigned, 2, 1},
	{"Relocations      ", kUnsigned, 2, 1},
	{"Paragraphs       ", kUnsigned, 2, 1},
	{"ParagraphsMin    ", kUnsigned, 2, 1},
	{"ParagraphsMax    ", kUnsigned, 2, 1},
	/* initial value of SS register */
	{"InitialSS        ", kUnsigned, 2, 1},
	/* initial value of SP register */
	{"InitialSP        ", kUnsigned, 2, 1},
	{"CheckSum         ", kUnsigned, 2, 1},
	/* initial value of IP register */
	{"InitialIP        ", kUnsigned, 2, 1},
	/* initial value of CS register */
	{"InitialCS        ", kUnsigned, 2, 1},
	{"AddressRelocation", kUnsigned, 2, 1},
	{"OverlayNumber    ", kUnsigned, 2, 1},
	{"Reserved         ", kReserved, 2, 4},
	{"OEMID            ", kUnsigned, 2, 1},
	{"OEMInfo          ", kUnsigned, 2, 1},
	{"Reserved         ", kReserved, 2, 10},
	{"AddressPE        ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __PEDOSHEADER_H__ */
