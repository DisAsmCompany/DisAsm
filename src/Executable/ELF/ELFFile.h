/*
 * Filename: ELFFile.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF (Executable and Linkable Format)
 *              file abstraction
 *
 *
 */

#pragma once
#ifndef __ELFFILE_H__
#define __ELFFILE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int ELFFileCreate(ExecutableContext * pContext);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFFILE_H__ */
