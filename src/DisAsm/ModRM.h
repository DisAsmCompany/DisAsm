/*
* Filename: ModRM.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: defines decoding of ModR/M byte
*              (Mod, R/M, Reg fields)
*              
*
*/

#pragma once
#ifndef __MODRM_H__68524C1D_613C_4C88_8910_3D1F65CD553E__
#define __MODRM_H__68524C1D_613C_4C88_8910_3D1F65CD553E__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct ModRMs_t
{
	uint8_t RM  : 3;
	uint8_t Reg : 3;
	uint8_t Mod : 2;
}
ModRMs;

typedef union ModRMu_t
{
	ModRMs fields;
	uint8_t value;
}
ModRMu;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MODRM_H__68524C1D_613C_4C88_8910_3D1F65CD553E__ */
