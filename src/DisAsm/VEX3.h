/*
* Filename: VEX3.h
* Author:   DisAsmCompany
* Date:     04/11/2013
*
* Description: three-byte VEX prefix (used in x64)
*
*
*
*/

#pragma once
#ifndef __VEX3_H__C7EDFABA_5654_418E_AE41_C111C3A4CB60__
#define __VEX3_H__C7EDFABA_5654_418E_AE41_C111C3A4CB60__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define VEX3_R(VEX)      (((VEX)      ) & 0x01)
#define VEX3_X(VEX)      (((VEX) >>  1) & 0x01)
#define VEX3_B(VEX)      (((VEX) >>  2) & 0x01)
#define VEX3_mmmmmm(VEX) (((VEX) >>  3) & 0x1F)
#define VEX3_W(VEX)      (((VEX) >>  8) & 0x01)
#define VEX3_vvvv(VEX)   (((VEX) >>  9) & 0x0F)
#define VEX3_L(VEX)      (((VEX) >> 13) & 0x01)
#define VEX3_pp(VEX)     (((VEX) >> 14) & 0x03)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VEX3_H__C7EDFABA_5654_418E_AE41_C111C3A4CB60__ */
