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
#ifndef __SIB_H__
#define __SIB_H__

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

#endif /* __SIB_H__ */
