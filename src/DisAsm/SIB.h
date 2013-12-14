/*
* Filename: SIB.h
* Author:   DisAsmCompany
* Date:     24/09/2013
*
* Description: defines decoding of SIB byte
*              (Scale, Index, Base fields)
*              
*
*/

#pragma once
#ifndef __SIB_H__6D324994_5477_465F_9546_E1916E818D2F__
#define __SIB_H__6D324994_5477_465F_9546_E1916E818D2F__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SIB_BASE(SIB)  (((SIB)     ) & 0x07)
#define SIB_INDEX(SIB) (((SIB) >> 3) & 0x07)
#define SIB_SCALE(SIB) (((SIB) >> 6) & 0x03)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SIB_H__6D324994_5477_465F_9546_E1916E818D2F__ */
