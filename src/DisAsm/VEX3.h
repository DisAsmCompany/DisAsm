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
#ifndef __VEX3_H__
#define __VEX3_H__

typedef struct VEX3s_t
{
	uint16_t R      : 1;
	uint16_t X      : 1;
	uint16_t B      : 1;
	uint16_t mmmmmm : 5;
	uint16_t W      : 1;
	uint16_t vvvv   : 4;
	uint16_t L      : 1;
	uint16_t pp     : 2;
}
VEX3s;

typedef union VEX3u_t
{
	VEX3s fields;
	uint16_t value;
}
VEX3u;

#endif /* __VEX3_H__ */
