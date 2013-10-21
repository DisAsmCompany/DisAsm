/*
* Filename: PEDebugType.h
* Author:   DisAsmCompany
* Date:     14/10/2013
*
* Description: PE Debug Type (CodeView, Borland, etc)
*              
*              
*
*/

#pragma once
#ifndef __PEDEBUGTYPE_H__
#define __PEDEBUGTYPE_H__

static const SDFEnum PEDebugType[] =
{
	{"IMAGE_DEBUG_TYPE_UNKNOWN",       0x00000000UL},
	{"IMAGE_DEBUG_TYPE_COFF",          0x00000001UL},
	{"IMAGE_DEBUG_TYPE_CODEVIEW",      0x00000002UL},
	{"IMAGE_DEBUG_TYPE_FPO",           0x00000003UL},
	{"IMAGE_DEBUG_TYPE_MISC",          0x00000004UL},
	{"IMAGE_DEBUG_TYPE_EXCEPTION",     0x00000005UL},
	{"IMAGE_DEBUG_TYPE_FIXUP",         0x00000006UL},
	{"IMAGE_DEBUG_TYPE_OMAP_TO_SRC",   0x00000007UL},
	{"IMAGE_DEBUG_TYPE_OMAP_FROM_SRC", 0x00000008UL},
	{"IMAGE_DEBUG_TYPE_BORLAND",       0x00000009UL},
	{"IMAGE_DEBUG_TYPE_RESERVED10",    0x0000000AUL},
	{"IMAGE_DEBUG_TYPE_CLSID",         0x0000000BUL},
	{NULL}
};

#endif /* __PEDEBUGTYPE_H__ */