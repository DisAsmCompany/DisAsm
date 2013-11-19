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

typedef struct SIBs_t
{
	uint8_t Base  : 3;
	uint8_t Index : 3;
	uint8_t Scale : 2;
}
SIBs;

typedef union SIBu_t
{
	SIBs fields;
	uint8_t value;
}
SIBu;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SIB_H__6D324994_5477_465F_9546_E1916E818D2F__ */
