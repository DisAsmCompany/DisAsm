/*
* Filename: REX.h
* Author:   DisAsmCompany
* Date:     14/10/2013
*
* Description: REX prefix (used in x64)
*
*
*
*/

#pragma once
#ifndef __REX_H__1779C43F_B028_48CA_BAA7_5AF9807DCFA9__
#define __REX_H__1779C43F_B028_48CA_BAA7_5AF9807DCFA9__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define REX_B(REX) (((REX)     ) & 0x01)
#define REX_X(REX) (((REX) >> 1) & 0x01)
#define REX_R(REX) (((REX) >> 2) & 0x01)
#define REX_W(REX) (((REX) >> 3) & 0x01)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __REX_H__1779C43F_B028_48CA_BAA7_5AF9807DCFA9__ */
