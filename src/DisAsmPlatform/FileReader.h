/*
* Filename: MemoryReader.h
* Author:   DisAsmCompany
* Date:     27/09/2013
*
* Description: implementation of Reader API
*              for file system data source
*              
*
*/

#pragma once
#ifndef __FILEREADER_H__7700367B_788D_478B_AA69_2FA6E8851CA5__
#define __FILEREADER_H__7700367B_788D_478B_AA69_2FA6E8851CA5__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

HREADER FileReaderCreate(const char * path);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FILEREADER_H__7700367B_788D_478B_AA69_2FA6E8851CA5__ */
