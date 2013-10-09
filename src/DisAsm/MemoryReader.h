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
#ifndef __MEMORYREADER_H__
#define __MEMORYREADER_H__

HREADER MemoryReaderCreate(void * buffer, uint32_t size);

#endif /* __MEMORYREADER_H__ */
