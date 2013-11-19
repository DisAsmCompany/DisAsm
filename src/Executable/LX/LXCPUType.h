/*
* Filename: LXCPUType.h
* Author:   DisAsmCompany
* Date:     26/10/2013
*
* Description: LX CPU Type
* 
*
*
*/

#pragma once
#ifndef __LXCPUTYPE_H__
#define __LXCPUTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum LXCPUType[] =
{
	{"80286", 0x00},
	{"80386", 0x01},
	{"80486", 0x02},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LXCPUTYPE_H__ */
