/*
 * Filename: Architecture.h
 * Author:   DisAsmCompany
 * Date:     14/11/2013
 *
 * Description: CPU architecture (x86, ARM, PowerPC, etc)
 *
 *
 *
 */

#pragma once
#ifndef __ARCHITECTURE_H__FFBB9EF6_2F39_4609_85F4_9662823E76C6__
#define __ARCHITECTURE_H__FFBB9EF6_2F39_4609_85F4_9662823E76C6__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum Architecture_t
{
	ArchUnknown = 0x00000000UL,
	ArchX86     = 0x00000001UL,
	ArchX64     = 0x00000002UL
}
Architecture;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ARCHITECTURE_H__FFBB9EF6_2F39_4609_85F4_9662823E76C6__ */
