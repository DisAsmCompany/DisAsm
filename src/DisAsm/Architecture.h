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
#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__

typedef enum Architecture_t
{
	x86 = 0x00000001UL,
	x64 = 0x00000002UL
}
Architecture;

#endif /* __ARCHITECTURE_H__ */
