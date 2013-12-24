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

SDFBegin(LXObjectTable, "LX Object Table"),
{"Virtual Size           ", kUnsigned, 4, 1, NULL},
{"Relocation Base Address", kUnsigned, 4, 1, NULL},
{"Object Flags           ", kUnsigned, 4, 1, NULL},
{"Page Table Index       ", kUnsigned, 4, 1, NULL},
{"Page Table Count       ", kUnsigned, 4, 1, NULL},
{"Reserved               ", kReserved, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LXOBJECTABLE_H__82D953CB_353E_448F_AE3E_86972801B49E__ */


