/*
* Filename: EVEX.h
* Author:   DisAsmCompany
* Date:     15/12/2013
*
* Description: EVEX prefix (used in x64)
*              defined by Intel for AVX-512 instructions
*              not yet shipped in real hardware
*
*/

#pragma once
#ifndef __EVEX_H__92D8071C_3B52_4B4D_8557_3BD1EF70D7A3__
#define __EVEX_H__92D8071C_3B52_4B4D_8557_3BD1EF70D7A3__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define EVEX_R(EVEX)    (((EVEX)      ) & 0x01)
#define EVEX_X(EVEX)    (((EVEX) >>  1) & 0x01)
#define EVEX_B(EVEX)    (((EVEX) >>  2) & 0x01)
#define EVEX_Rh(EVEX)   (((EVEX) >>  3) & 0x01)
#define EVEX_mm(EVEX)   (((EVEX) >>  6) & 0x03)
#define EVEX_W(EVEX)    (((EVEX) >>  8) & 0x01)
#define EVEX_vvvv(EVEX) (((EVEX) >>  9) & 0x0F)
#define EVEX_pp(EVEX)   (((EVEX) >> 14) & 0x03)
#define EVEX_z(EVEX)    (((EVEX) >> 16) & 0x01)
#define EVEX_LL(EVEX)   (((EVEX) >> 17) & 0x03)
#define EVEX_b(EVEX)    (((EVEX) >> 19) & 0x01)
#define EVEX_vh(EVEX)   (((EVEX) >> 20) & 0x01)
#define EVEX_aaa(EVEX)  (((EVEX) >> 21) & 0x07)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EVEX_H__92D8071C_3B52_4B4D_8557_3BD1EF70D7A3__ */
