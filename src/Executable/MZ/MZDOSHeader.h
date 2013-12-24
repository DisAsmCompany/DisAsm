/*
* Filename: MZDOSHeader.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: MZ DOS Header structure
*              used in PE/NE/LE/LX files
*              
*
*/

#pragma once
#ifndef __MZDOSHEADER_H__
#define __MZDOSHEADER_H__

enum { kMZDOSSignature = 0x5A4D }; /* MZ */
enum { kZMDOSSignature = 0x4D5A }; /* ZM */

enum { MZDOSHeaderSignature = 0 };
enum { MZDOSHeaderAddressNew = 0x3C };

SDFBegin(MZDOSHeader, "MZ DOS Header"),
/* DOS signature, either 'MZ' or 'ZM' */
{"Signature        ", kSignature, 2, 1, NULL},
{"BytesInLastPage  ", kUnsigned, 2, 1, NULL},
{"Pages            ", kUnsigned, 2, 1, NULL},
{"Relocations      ", kUnsigned, 2, 1, NULL},
{"Paragraphs       ", kUnsigned, 2, 1, NULL},
{"ParagraphsMin    ", kUnsigned, 2, 1, NULL},
{"ParagraphsMax    ", kUnsigned, 2, 1, NULL},
/* initial value of SS register */
{"InitialSS        ", kUnsigned, 2, 1, NULL},
/* initial value of SP register */
{"InitialSP        ", kUnsigned, 2, 1, NULL},
{"CheckSum         ", kUnsigned, 2, 1, NULL},
/* initial value of IP register */
{"InitialIP        ", kUnsigned, 2, 1, NULL},
/* initial value of CS register */
{"InitialCS        ", kUnsigned, 2, 1, NULL},
{"AddressRelocation", kUnsigned, 2, 1, NULL},
{"OverlayNumber    ", kUnsigned, 2, 1, NULL},
{"Reserved         ", kReserved, 2, 4, NULL},
{"OEMID            ", kUnsigned, 2, 1, NULL},
{"OEMInfo          ", kUnsigned, 2, 1, NULL},
{"Reserved         ", kReserved, 2, 10, NULL},
{"AddressNew       ", kUnsigned, 4, 1, NULL},
SDFEnd

#endif /* __MZDOSHEADER_H__ */
