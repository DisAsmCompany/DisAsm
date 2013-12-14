/*
* Filename: XOP3.h
* Author:   DisAsmCompany
* Date:     04/11/2013
*
* Description: three-byte XOP prefix (used in x64)
*
*
*
*/

#pragma once
#ifndef __XOP3_H__5251957B_A29E_49BC_8FAF_1330D403A0FA__
#define __XOP3_H__5251957B_A29E_49BC_8FAF_1330D403A0FA__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define XOP3_R(XOP)      (((XOP)      ) & 0x01)
#define XOP3_X(XOP)      (((XOP) >>  1) & 0x01)
#define XOP3_B(XOP)      (((XOP) >>  2) & 0x01)
#define XOP3_mmmmmm(XOP) (((XOP) >>  3) & 0x1F)
#define XOP3_W(XOP)      (((XOP) >>  8) & 0x01)
#define XOP3_vvvv(XOP)   (((XOP) >>  9) & 0x0F)
#define XOP3_L(XOP)      (((XOP) >> 13) & 0x01)
#define XOP3_pp(XOP)     (((XOP) >> 14) & 0x03)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __XOP3_H__5251957B_A29E_49BC_8FAF_1330D403A0FA__ */
