/*
 * Filename: MachOFile.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O file abstraction
 *
 *
 *
 */

#pragma once
#ifndef __MACHOFILE_H__
#define __MACHOFILE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int MachOFileCreate(ExecutableContext * pContext);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOFILE_H__ */
