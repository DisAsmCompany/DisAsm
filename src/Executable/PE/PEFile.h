/*
 * Filename: PEFile.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: PE file abstraction
 *              (Portable Executable)
 *
 *
 */

#pragma once
#ifndef __PEFILE_H__
#define __PEFILE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int PEFileCreate(ExecutableContext * pContext);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEFILE_H__ */
