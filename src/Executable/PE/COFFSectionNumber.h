/*
 * Filename: COFFSectionNumber.h
 * Author:   DisAsmCompany
 * Date:     25/10/2013
 *
 * Description: COFF Section Number
 *
 *
 *
 */

#pragma once
#ifndef __COFFSECTIONNUMBER_H__
#define __COFFSECTIONNUMBER_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum COFFSectionNumber[] =
{
	{"IMAGE_SYM_UNDEFINED", 0x0000},
	{"IMAGE_SYM_ABSOLUTE",  0xFFFF},
	{"IMAGE_SYM_DEBUG",     0xFFFE},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COFFSECTIONNUMBER_H__ */
