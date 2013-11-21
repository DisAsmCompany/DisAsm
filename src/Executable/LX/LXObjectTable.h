/*
* Filename: LXObjectTable.h
* Author:   DisAsmCompany
* Date:     26/10/2013
*
* Description: LX Object Table
* 
*
*
*/

#pragma once
#ifndef __LXOBJECTABLE_H__82D953CB_353E_448F_AE3E_86972801B49E__
#define __LXOBJECTABLE_H__82D953CB_353E_448F_AE3E_86972801B49E__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFElement LXObjectTable[] =
{
	{"LX Object Table"},
	{"Virtual Size           ", kUnsigned, 4, 1},
	{"Relocation Base Address", kUnsigned, 4, 1},
	{"Object Flags           ", kUnsigned, 4, 1},
	{"Page Table Index       ", kUnsigned, 4, 1},
	{"Page Table Count       ", kUnsigned, 4, 1},
	{"Reserved               ", kReserved, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LXOBJECTABLE_H__82D953CB_353E_448F_AE3E_86972801B49E__ */


