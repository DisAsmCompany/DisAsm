/*
* Filename: CachedMemoryReader.h
* Author:   DisAsmCompany
* Date:     20/12/2013
*
* Description: implementation of Reader API
*              for file system data source (cached)
*              
*
*/

#pragma once
#ifndef __CACHEDFILEREADER_H__C71A5374_082E_46BC_B54C_320277B5BB9A__
#define __CACHEDFILEREADER_H__C71A5374_082E_46BC_B54C_320277B5BB9A__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	HREADER CachedFileReaderCreate(const char * path);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CACHEDFILEREADER_H__C71A5374_082E_46BC_B54C_320277B5BB9A__ */
