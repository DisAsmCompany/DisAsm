/*
* Filename: VEX2.h
* Author:   DisAsmCompany
* Date:     04/11/2013
*
* Description: two-byte VEX prefix (used in x64)
*
*
*
*/

#pragma once
#ifndef __VEX2_H__B64E0451_CAB7_4243_9DDC_BEC99A6C7EC6__
#define __VEX2_H__B64E0451_CAB7_4243_9DDC_BEC99A6C7EC6__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define VEX2_R(VEX)    ((((VEX) >> 7) & 0x01) ^ 0x01)
#define VEX2_vvvv(VEX) (0x10 - (((VEX) >> 3) & 0x0F))
#define VEX2_L(VEX)    (((VEX) >> 2) & 0x01)
#define VEX2_pp(VEX)   (((VEX)     ) & 0x03)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VEX2_H__B64E0451_CAB7_4243_9DDC_BEC99A6C7EC6__ */
