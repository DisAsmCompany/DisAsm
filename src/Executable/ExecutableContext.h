/*
 * Filename: ExecutableContext.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Executable Context
 *              (private data)
 *
 *
 */

#pragma once
#ifndef __EXECUTABLECONTEXT_H__
#define __EXECUTABLECONTEXT_H__

typedef struct ExecutableContext_t
{
	uint8_t memory;
	HREADER hReader;
	uint32_t Signature;
	PEDOSHeader DOSHeader;
	PEFileHeader FileHeader;
	PEOptionalHeader OptionalHeader;
	uint32_t DataDirectoriesCount;
	PEDataDirectory * DataDirectories;
	PESectionHeader * SectionHeaders;
	PEExportDirectory ExportDirectory;
	PEDebugDirectory DebugDirectory;
	PELoadConfigDirectory LoadConfigDirectory;
	uint32_t OffsetExport;
	uint32_t SizeExport;
	uint32_t OffsetExportFunctions;
	uint32_t OffsetExportOrdinals;
	uint32_t OffsetExportNames;
}
ExecutableContext;

#endif /* __EXECUTABLECONTEXT_H__ */
