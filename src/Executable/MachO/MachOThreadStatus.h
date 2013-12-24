
/*
 * Filename: MachOThreadStatus.h
 * Author:   DisAsmCompany
 * Date:     11/11/2013
 *
 * Description: Mach-O thread status
 *
 *
 *
 */

#pragma once
#ifndef __MACHOTHREADSTTUSX_H__53C00FD8_5E35_4869_AAC7_B7DCC437EF9D__
#define __MACHOTHREADSTTUSX_H__53C00FD8_5E35_4869_AAC7_B7DCC437EF9D__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

SDFBegin(MachOThreadStatus, "Mach-O Thread Status"),
{"Flavor", kUnsigned, 4, 1, NULL},
{"Count ", kUnsigned, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOTHREADSTTUSX_H__53C00FD8_5E35_4869_AAC7_B7DCC437EF9D__ */
