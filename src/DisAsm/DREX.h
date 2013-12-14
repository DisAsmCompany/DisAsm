/*
* Filename: DREX.h
* Author:   DisAsmCompany
* Date:     15/12/2013
*
* Description: DREX prefix (used in x64)
*              defined by AMD for 128-bit SSE instructions
*              never shipped in real hardware
*
*/

#pragma once
#ifndef __DREX_H__F4F1B954_4609_4081_9770_D7860593DD51__
#define __DREX_H__F4F1B954_4609_4081_9770_D7860593DD51__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DREX_B(DREX)    (((DREX)     ) & 0x01)
#define DREX_X(DREX)    (((DREX) >> 1) & 0x01)
#define DREX_R(DREX)    (((DREX) >> 2) & 0x01)
#define DREX_OC0(DREX)  (((DREX) >> 3) & 0x01)
#define DREX_dest(DREX) (((DREX) >> 4) & 0x0F)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DREX_H__F4F1B954_4609_4081_9770_D7860593DD51__ */
