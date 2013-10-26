/*
* Filename: MZDOSHeader.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: MZ DOS Header structure
*
*              
*
*/

#pragma once
#ifndef __MZDOSHEADER_H__
#define __MZDOSHEADER_H__

static const uint32_t kMZDOSSignature = 0x5A4D; /* MZ */

static const uint32_t MZDOSHeaderSignature = 0;
static const uint32_t MZDOSHeaderAddressNew = 0x3C;

static const SDFElement MZDOSHeader[] =
{
	{"MZ DOS Header"},
	/* DOS signature, either 'MZ' or 'ZM' */
	{"Signature        ", kSignature, 2, 1},
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
	{"AddressNew       ", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __MZDOSHEADER_H__ */
