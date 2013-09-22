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
#ifndef __MODRM_H__
#define __MODRM_H__

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

#endif /* __MODRM_H__ */
