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

#define MODRM_RM(ModRM)  (((ModRM)     ) & 0x07)
#define MODRM_REG(ModRM) (((ModRM) >> 3) & 0x07)
#define MODRM_MOD(ModRM) (((ModRM) >> 6) & 0x03)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MODRM_H__68524C1D_613C_4C88_8910_3D1F65CD553E__ */
