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
#ifndef __COFFSECTIONNUMBER_H__A1C70231_5408_4C3B_80BD_9E5A3CCB5A32__
#define __COFFSECTIONNUMBER_H__A1C70231_5408_4C3B_80BD_9E5A3CCB5A32__

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

#endif /* __COFFSECTIONNUMBER_H__A1C70231_5408_4C3B_80BD_9E5A3CCB5A32__ */
