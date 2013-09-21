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
	unsigned char RM  : 3;
	unsigned char Reg : 3;
	unsigned char Mod : 2;
}
ModRMs;

typedef union ModRMu_t
{
	ModRMs fields;
	unsigned char value;
}
ModRMu;

#endif // __MODRM_H__
