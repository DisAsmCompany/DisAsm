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
#ifndef __VEX2_H__
#define __VEX2_H__

typedef struct VEX2s_t
{
	uint8_t R    : 1;
	uint8_t vvvv : 4;
	uint8_t L    : 1;
	uint8_t pp   : 2;
}
VEX2s;

typedef union VEX2u_t
{
	VEX2s fields;
	uint8_t value;
}
VEX2u;

#endif /* __VEX2_H__ */
