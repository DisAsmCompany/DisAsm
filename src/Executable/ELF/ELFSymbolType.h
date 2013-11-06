/*
 * Filename: ELFSymbolType.h
 * Author:   DisAsmCompany
 * Date:     06/11/2013
 *
 * Description: ELF Symbol Type, the most
 *              interesting is function
 *
 *
 */

#pragma once
#ifndef __ELFSYMBOLTYPE_H__
#define __ELFSYMBOLTYPE_H__

static const SDFEnum ELFSymbolType[] =
{
	{"STT_NOTYPE",  0x00, 0x0F},
	{"STT_OBJECT",  0x01, 0x0F},
	{"STT_FUNC",    0x02, 0x0F},
	{"STT_SECTION", 0x03, 0x0F},
	{"STT_FILE",    0x04, 0x0F},
	{"STB_LOCAL",   0x00, 0xF0},
	{"STB_GLOBAL",  0x10, 0xF0},
	{"STB_WEAK",    0x20, 0xF0},
	{NULL}
};

#endif /* __ELFSYMBOLTYPE_H__ */
