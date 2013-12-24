/*
* Filename: PEMagic.h
* Author:   DisAsmCompany
* Date:     14/10/2013
*
* Description: PE Magic (PE32, PE32+, etc)
*              
*              
*
*/

#pragma once
#ifndef __PEMAGIC_H__7374E7D6_DD90_44D6_ACDE_159E3B9946CB__
#define __PEMAGIC_H__7374E7D6_DD90_44D6_ACDE_159E3B9946CB__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum PEMagic_t
{
	kPEMagic32  = 0x010B,
	kPEMagic64  = 0x020B,
	kPEMagicROM = 0x0107,
}
PEMagic;

static const SDFEnum _PEMagic[] =
{
	{"IMAGE_NT_OPTIONAL_HDR32_MAGIC", kPEMagic32, 0},
	{"IMAGE_NT_OPTIONAL_HDR64_MAGIC", kPEMagic64, 0},
	{"IMAGE_ROM_OPTIONAL_HDR_MAGIC",  kPEMagicROM, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEMAGIC_H__7374E7D6_DD90_44D6_ACDE_159E3B9946CB__ */
