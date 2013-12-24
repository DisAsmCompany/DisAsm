/*
* Filename: LXOrdering.h
* Author:   DisAsmCompany
* Date:     26/10/2013
*
* Description: LX Byte/Word Ordering
* 
*
*
*/

#pragma once
#ifndef __LXORDERING_H__02691875_16B9_4377_AF79_DF4FFCAFCC47__
#define __LXORDERING_H__02691875_16B9_4377_AF79_DF4FFCAFCC47__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum LXOrdering[] =
{
	{"Little Endian", 0x00, 0},
	{"Big Endian",    0x01, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LXORDERING_H__02691875_16B9_4377_AF79_DF4FFCAFCC47__ */
