/*
* Filename: MVEX.h
* Author:   DisAsmCompany
* Date:     15/12/2013
*
* Description: MVEX prefix (used in x64)
*              defined by Intel for Larrabee instructions
*              (aka Intel MIC, Knights Ferry, Knights Corner, Xeon Phi, etc)
*              never shipped in real hardware
*/

#pragma once
#ifndef __MVEX_H__D0C7197D_279F_4981_B369_608EBE2F15F7__
#define __MVEX_H__D0C7197D_279F_4981_B369_608EBE2F15F7__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MVEX_R(MVEX)     (((MVEX)      ) & 0x01)
#define MVEX_X(MVEX)     (((MVEX) >>  1) & 0x01)
#define MVEX_B(MVEX)     (((MVEX) >>  2) & 0x01)
#define MVEX_Rh(MVEX)    (((MVEX) >>  3) & 0x01)
#define MVEX_mmmmm(MVEX) (((MVEX) >>  4) & 0x0F)
#define MVEX_W(MVEX)     (((MVEX) >>  8) & 0x01)
#define MVEX_vvvv(MVEX)  (((MVEX) >>  9) & 0x0F)
#define MVEX_pp(MVEX)    (((MVEX) >> 14) & 0x03)
#define MVEX_E(MVEX)     (((MVEX) >> 16) & 0x01)
#define MVEX_sss(MVEX)   (((MVEX) >> 17) & 0x07)
#define MVEX_vh(MVEX)    (((MVEX) >> 20) & 0x01)
#define MVEX_kkk(MVEX)   (((MVEX) >> 21) & 0x07)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MVEX_H__D0C7197D_279F_4981_B369_608EBE2F15F7__ */
