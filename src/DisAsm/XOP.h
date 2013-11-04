/*
* Filename: XOP.h
* Author:   DisAsmCompany
* Date:     04/11/2013
*
* Description: three-byte XOP prefix (used in x64)
*
*
*
*/

#pragma once
#ifndef __XOP_H__
#define __XOP_H__

typedef struct XOPs_t
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
XOPs;

typedef union XOPu_t
{
	XOPs fields;
	uint16_t value;
}
XOPu;

#endif /* __XOP_H__ */
