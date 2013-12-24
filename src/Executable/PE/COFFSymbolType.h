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
#ifndef __COFFSYMBOLTYPE_H__A3EEDC95_C3D6_4DBA_8262_7E4AEAED62E8__
#define __COFFSYMBOLTYPE_H__A3EEDC95_C3D6_4DBA_8262_7E4AEAED62E8__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum COFFSymbolType_t
{
    kCOFFSymbolTypeFunction = 0x0020
}
COFFSymbolType;

static const SDFEnum _COFFSymbolType[] =
{
	{"IMAGE_SYM_TYPE_NULL",   0x0000, 0},
	{"IMAGE_SYM_TYPE_VOID",   0x0001, 0},
	{"IMAGE_SYM_TYPE_CHAR",   0x0002, 0},
	{"IMAGE_SYM_TYPE_SHORT",  0x0003, 0},
	{"IMAGE_SYM_TYPE_INT",    0x0004, 0},
	{"IMAGE_SYM_TYPE_LONG",   0x0005, 0},
	{"IMAGE_SYM_TYPE_FLOAT",  0x0006, 0},
	{"IMAGE_SYM_TYPE_DOUBLE", 0x0007, 0},
	{"IMAGE_SYM_TYPE_STRUCT", 0x0008, 0},
	{"IMAGE_SYM_TYPE_UNION",  0x0009, 0},
	{"IMAGE_SYM_TYPE_ENUM",   0x000A, 0},
	{"IMAGE_SYM_TYPE_MOE",    0x000B, 0},
	{"IMAGE_SYM_TYPE_BYTE",   0x000C, 0},
	{"IMAGE_SYM_TYPE_WORD",   0x000D, 0},
	{"IMAGE_SYM_TYPE_UINT",   0x000E, 0},
	{"IMAGE_SYM_TYPE_DWORD",  0x000F, 0},
	{"IMAGE_SYM_TYPE_FUNC",   kCOFFSymbolTypeFunction, 0},
	{"IMAGE_SYM_TYPE_PCODE",  0x8000, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COFFSYMBOLTYPE_H__A3EEDC95_C3D6_4DBA_8262_7E4AEAED62E8__ */
