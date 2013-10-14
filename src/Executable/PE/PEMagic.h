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
#ifndef __PEMAGIC_H__
#define __PEMAGIC_H__

typedef enum PEMagic_t
{
	kPEMagic32  = 0x010B,
	kPEMagic64  = 0x020B,
	kPEMagicROM = 0x0107,
}
PEMagic;

static const SDFEnum _PEMagic[] =
{
	{"IMAGE_NT_OPTIONAL_HDR32_MAGIC", kPEMagic32},
	{"IMAGE_NT_OPTIONAL_HDR64_MAGIC", kPEMagic64},
	{"IMAGE_ROM_OPTIONAL_HDR_MAGIC",  kPEMagicROM},
	{NULL}
};

#endif /* __PEMAGIC_H__ */
