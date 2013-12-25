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
#ifndef __MEMORYREADER_H__57A88D90_D3FB_4E2A_A61D_A78215768A28__
#define __MEMORYREADER_H__57A88D90_D3FB_4E2A_A61D_A78215768A28__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

HREADER MemoryReaderCreate(native_t buffer, uint32_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MEMORYREADER_H__57A88D90_D3FB_4E2A_A61D_A78215768A28__ */
