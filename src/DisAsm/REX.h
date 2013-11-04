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
#ifndef __REX_H__
#define __REX_H__

typedef struct REXs_t
{
	uint8_t B : 1;
	uint8_t X : 1;
	uint8_t R : 1;
	uint8_t W : 1;
	uint8_t _ : 4;
}
REXs;

typedef union REXu_t
{
	REXs fields;
	uint8_t value;
}
REXu;

#endif /* __REX_H__ */
