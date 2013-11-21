/*
 * Filename: ELFProgramHeader.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Program Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFPROGRAMHEADER_H__B4C72014_DF53_4AB5_88C0_F5E02D7DD9C7__
#define __ELFPROGRAMHEADER_H__B4C72014_DF53_4AB5_88C0_F5E02D7DD9C7__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFElement ELFProgramHeader[] =
{
	{"ELF Program Header"},
	{"Type            ", kUnsigned, 4, 1, ELFProgramType},
	{"Offset          ", kUnsigned, 4, 1},
	{"Virtual Address ", kUnsigned, 4, 1},
	{"Physical Address", kUnsigned, 4, 1},
	{"Physical Size   ", kUnsigned, 4, 1},
	{"Virtual Size    ", kUnsigned, 4, 1},
	{"Flags           ", kUnsigned, 4, 1, ELFProgramFlags},
	{"Align           ", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFPROGRAMHEADER_H__B4C72014_DF53_4AB5_88C0_F5E02D7DD9C7__ */
