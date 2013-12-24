/*
 * Filename: COFFSymbolClass.h
 * Author:   DisAsmCompany
 * Date:     25/10/2013
 *
 * Description: COFF Symbol Class
 *
 *
 *
 */

#pragma once
#ifndef __COFFSYMBOLCLASS_H__72DD5405_5B8A_4421_9D7E_34383FE76E21__
#define __COFFSYMBOLCLASS_H__72DD5405_5B8A_4421_9D7E_34383FE76E21__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum _COFFSymbolClass_t
{
	kCOFFSymbolClassExternal = 0x02,
    kCOFFSymbolClassStatic   = 0x03,
	kCOFFSymbolClassFile     = 0x67
}
COFFSymbolClass;

static const SDFEnum _COFFSymbolClass[] =
{
	{"IMAGE_SYM_CLASS_NULL",             0x00, 0},
	{"IMAGE_SYM_CLASS_AUTOMATIC",        0x01, 0},
	{"IMAGE_SYM_CLASS_EXTERNAL",         kCOFFSymbolClassExternal, 0},
	{"IMAGE_SYM_CLASS_STATIC",           kCOFFSymbolClassStatic, 0},
	{"IMAGE_SYM_CLASS_REGISTER",         0x04, 0},
	{"IMAGE_SYM_CLASS_EXTERNAL_DEF",     0x05, 0},
	{"IMAGE_SYM_CLASS_LABEL",            0x06, 0},
	{"IMAGE_SYM_CLASS_UNDEFINED_LABEL",  0x07, 0},
	{"IMAGE_SYM_CLASS_MEMBER_OF_STRUCT", 0x08, 0},
	{"IMAGE_SYM_CLASS_ARGUMENT",         0x09, 0},
	{"IMAGE_SYM_CLASS_STRUCT_TAG",       0x0A, 0},
	{"IMAGE_SYM_CLASS_MEMBER_OF_UNION",  0x0B, 0},
	{"IMAGE_SYM_CLASS_UNION_TAG",        0x0C, 0},
	{"IMAGE_SYM_CLASS_TYPE_DEFINITION",  0x0D, 0},
	{"IMAGE_SYM_CLASS_UNDEFINED_STATIC", 0x0E, 0},
	{"IMAGE_SYM_CLASS_ENUM_TAG",         0x0F, 0},
	{"IMAGE_SYM_CLASS_MEMBER_OF_ENUM",   0x10, 0},
	{"IMAGE_SYM_CLASS_REGISTER_PARAM",   0x11, 0},
	{"IMAGE_SYM_CLASS_BIT_FIELD",        0x12, 0},
	{"IMAGE_SYM_CLASS_FAR_EXTERNAL",     0x44, 0},
	{"IMAGE_SYM_CLASS_BLOCK",            0x64, 0},
	{"IMAGE_SYM_CLASS_FUNCTION",         0x65, 0},
	{"IMAGE_SYM_CLASS_END_OF_STRUCT",    0x66, 0},
	{"IMAGE_SYM_CLASS_FILE",             kCOFFSymbolClassFile, 0},
	{"IMAGE_SYM_CLASS_SECTION",          0x68, 0},
	{"IMAGE_SYM_CLASS_WEAK_EXTERNAL",    0x69, 0},
	{"IMAGE_SYM_CLASS_CLR_TOKEN",        0x6B, 0},
	{"IMAGE_SYM_CLASS_END_OF_FUNCTION",  0xFF, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COFFSYMBOLCLASS_H__72DD5405_5B8A_4421_9D7E_34383FE76E21__ */
