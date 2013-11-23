/*
* Filename: Module.h
* Author:   DisAsmCompany
* Date:     23/11/2013
*
* Description: native module loader
*
*              
*
*/

#pragma once
#ifndef __MODULE_H__FC1DF83A_147B_443F_B1BE_A3B7D20123E9__
#define __MODULE_H__FC1DF83A_147B_443F_B1BE_A3B7D20123E9__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum {NtfsMaxPath = 32768};

typedef struct ModuleInfo_t
{
	address_t address;
	uint32_t size;
	char path[NtfsMaxPath];
	char name[NtfsMaxPath];
}
ModuleInfo;

address_t ModuleLoad(const char * name);
void ModuleUnload(address_t address);
void ModuleGetInfo(address_t address, ModuleInfo * info);
uint32_t ModuleEnum(ModuleInfo ** info);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MODULE_H__FC1DF83A_147B_443F_B1BE_A3B7D20123E9__ */
