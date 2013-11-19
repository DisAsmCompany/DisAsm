/*
 * Filename: COFFSymbolType.h
 * Author:   DisAsmCompany
 * Date:     25/10/2013
 *
 * Description: COFF Symbol Type
 *
 *
 *
 */

#pragma once
#ifndef __COFFSYMBOLTYPE_H__
#define __COFFSYMBOLTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum COFFSymbolType[] =
{
	{"IMAGE_SYM_TYPE_NULL",   0x0000},
	{"IMAGE_SYM_TYPE_VOID",   0x0001},
	{"IMAGE_SYM_TYPE_CHAR",   0x0002},
	{"IMAGE_SYM_TYPE_SHORT",  0x0003},
	{"IMAGE_SYM_TYPE_INT",    0x0004},
	{"IMAGE_SYM_TYPE_LONG",   0x0005},
	{"IMAGE_SYM_TYPE_FLOAT",  0x0006},
	{"IMAGE_SYM_TYPE_DOUBLE", 0x0007},
	{"IMAGE_SYM_TYPE_STRUCT", 0x0008},
	{"IMAGE_SYM_TYPE_UNION",  0x0009},
	{"IMAGE_SYM_TYPE_ENUM",   0x000A},
	{"IMAGE_SYM_TYPE_MOE",    0x000B},
	{"IMAGE_SYM_TYPE_BYTE",   0x000C},
	{"IMAGE_SYM_TYPE_WORD",   0x000D},
	{"IMAGE_SYM_TYPE_UINT",   0x000E},
	{"IMAGE_SYM_TYPE_DWORD",  0x000F},
	{"IMAGE_SYM_TYPE_FUNC",   0x0020},
	{"IMAGE_SYM_TYPE_PCODE",  0x8000},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COFFSYMBOLTYPE_H__ */
