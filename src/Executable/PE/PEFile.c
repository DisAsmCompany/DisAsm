/*
 * Filename: PEFile.c
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: PE file abstraction
 *
 *
 *
 */

#include "../../DisAsm/DisAsm"
#include "../Executable"
#include "PEString.h"

typedef struct PEFileContext_t
{
	HSDF hDOSHeader;
	HSDF hPEFileHeader;
	HSDF hOptionalHeader;
	uint32_t DataDirectoriesCount;
	PEDataDirectory * DataDirectories;
	HSDF * phSectionHeaders;
	HSDF hExportDirectory;
	HSDF hDebugDirectory;
	HSDF hLoadConfigDirectory;
	uint32_t NumberOfSections;
	uint32_t NumberOfFunctions;
	uint32_t AddressOfEntryPoint;
	uint32_t OffsetExport;
	uint32_t SizeExport;
	uint32_t OffsetExportFunctions;
	uint32_t OffsetExportOrdinals;
	uint32_t OffsetExportNames;
}
PEFileContext;

#undef THIS
#define THIS ((PEFileContext*)(pContext->pPrivate))

char * FetchString(ExecutableContext * pContext, uint32_t address)
{
	char * buffer = NULL; 
	uint32_t i = 0;
	if (0 == ReaderSeek(pContext->hReader, address))
	{
		return NULL;
	}
	if (NULL == (buffer = malloc(1024)))
	{
		return NULL;
	}
	for (i = 0; i < 1024; ++i)
	{
		if (0 == ReaderRead(pContext->hReader, &buffer[i], sizeof(uint8_t)))
		{
			break;
		}
		if (0 == buffer[i] || '\n' == buffer[i] || '\r' == buffer[i])
		{
			break;
		}
	}
	buffer[i] = 0;
	return buffer;
}

uint32_t PERVAToOffset(ExecutableContext * pContext, uint32_t RVA)
{
	uint32_t offset = 0;
	uint16_t i = 0;
	if (pContext->memory)
	{
		return RVA;
	}
	for (i = 0; i < THIS->NumberOfSections; ++i)
	{
		uint32_t Address = SDFReadUInt32(THIS->phSectionHeaders[i], PESectionHeaderVirtualAddress);
		uint32_t Size    = SDFReadUInt32(THIS->phSectionHeaders[i], PESectionHeaderSizeOfRawData);
		uint32_t Data    = SDFReadUInt32(THIS->phSectionHeaders[i], PESectionHeaderPointerToRawData);
		if (Address <= RVA && RVA <= Address + Size)
		{
			offset = Data + RVA - Address;
			break;
		}
	}
	return offset;
}

int PEFileProcessDirectoryExport(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t i = 0;
	char * name = NULL;
	THIS->OffsetExport = PERVAToOffset(pContext, pDirectory->VirtualAddress);
	THIS->SizeExport = pDirectory->Size;
	if (pDirectory->Size < SDFSizeInBytes(PEExportDirectory, PEExportDirectorySize))
	{
		return 0;
	}
	if (0 == THIS->OffsetExport)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, THIS->OffsetExport))
	{
		return 0;
	}
	THIS->hExportDirectory = SDFCreate(PEExportDirectory, PEExportDirectorySize, pContext->hReader);
	SDFPrint(THIS->hExportDirectory);
	THIS->NumberOfFunctions = SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryNumberOfFunctions);
	THIS->OffsetExportFunctions = PERVAToOffset(pContext, SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryAddressOfFunctions));
	THIS->OffsetExportOrdinals  = PERVAToOffset(pContext, SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryAddressOfNameOrdinals));
	THIS->OffsetExportNames     = PERVAToOffset(pContext, SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryAddressOfNames));

	for (i = 0; i < THIS->NumberOfFunctions; ++i)
	{
		uint32_t address = 0;
		uint32_t ptr = 0;
		ReaderSeek(pContext->hReader, THIS->OffsetExportFunctions + i * 4);
		ReaderRead(pContext->hReader, &ptr, sizeof(uint32_t));
		address = PERVAToOffset(pContext, ptr);

		ReaderSeek(pContext->hReader, THIS->OffsetExportNames + i * sizeof(uint32_t));
		ReaderRead(pContext->hReader, &ptr, sizeof(uint32_t));
		ptr = PERVAToOffset(pContext, ptr);

		name = FetchString(pContext, ptr);

		/* Forwarder RVA (within Export Directory) */
		if (THIS->OffsetExport <= address && address + sizeof(uint32_t) <= THIS->OffsetExport + THIS->SizeExport)
		{
			char * forwarder = FetchString(pContext, address);

			printf("0x%04X 0x%08X %s -> %s\n", i, address, name, forwarder);

			free(forwarder);
		}
		else
		{
			printf("0x%04X 0x%08X %s\n", i, address, name);
		}
		free(name);
		name = NULL;
	}
	return 1;
}

int PEFileProcessDirectoryImport(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t offset = PERVAToOffset(pContext, pDirectory->VirtualAddress);
	uint32_t address = 0;
	uint32_t pos = 0;
	if (0 == offset)
	{
		return 0;
	}
	while (pos + SDFSizeInBytes(PEImportDescriptor, PEImportDescriptorSize) <= pDirectory->Size)
	{
		HSDF hImportDescriptor;
		char * name = NULL;
		uint32_t OriginalFirstThunk = 0;
		if (0 == ReaderSeek(pContext->hReader, offset + pos))
		{
			return 0;
		}
		hImportDescriptor = SDFCreate(PEImportDescriptor, PEImportDescriptorSize, pContext->hReader);
		SDFPrint(hImportDescriptor);
		OriginalFirstThunk = SDFReadUInt32(hImportDescriptor, PEImportDescriptorOriginalFirstThunk);
		if (0 == OriginalFirstThunk)
		{
			break;
		}
		address = PERVAToOffset(pContext, SDFReadUInt32(hImportDescriptor, PEImportDescriptorName));
		name = FetchString(pContext, address);
		printf("Import %s\n", name ? name : "");
		free(name);
		address = PERVAToOffset(pContext, OriginalFirstThunk);
		if (0 != address)
		{
			uint32_t i = 0;
			for (i = 0; ; ++i)
			{
				uint32_t element = 0;
				ReaderSeek(pContext->hReader, address + i * sizeof(uint32_t));
				ReaderRead(pContext->hReader, &element, sizeof(uint32_t));
				if (0 == element) break;
				if (element & 0x80000000UL)
				{
					printf("ordinal 0x%08lX\n", element & ~0x80000000UL);
				}
				else
				{
					uint16_t hint = 0;
					uint32_t ptr = PERVAToOffset(pContext, element);
					ReaderSeek(pContext->hReader, ptr);
					ReaderRead(pContext->hReader, &hint, sizeof(uint16_t));
					name = FetchString(pContext, ptr + sizeof(uint16_t));
					printf("0x%04X %s\n", hint, name);
					free(name);
				}
			}
			printf("\n");
		}
		SDFDestroy(hImportDescriptor);
		pos += SDFSizeInBytes(PEImportDescriptor, PEImportDescriptorSize);
	}
	return 1;
}

int PEFileProcessDirectoryDebug(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t offset = PERVAToOffset(pContext, pDirectory->VirtualAddress);
	if (0 == offset)
	{
		return 0;
	}
	if (pDirectory->Size < SDFSizeInBytes(PEDebugDirectory, PEDebugDirectorySize))
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, offset))
	{
		return 0;
	}
	THIS->hDebugDirectory = SDFCreate(PEDebugDirectory, PEDebugDirectorySize, pContext->hReader);
	SDFPrint(THIS->hDebugDirectory);
	return 1;
}

int PEFileProcessDirectoryLoadConfig(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t size = 0;
	uint32_t offset = PERVAToOffset(pContext, pDirectory->VirtualAddress);

	if (0 == offset)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, offset))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &size, sizeof(uint32_t)))
	{
		return 0;
	}
	if (size < SDFSizeInBytes(PELoadConfigDirectory, PELoadConfigDirectorySize))
	{
		return 0;
	}
	THIS->hLoadConfigDirectory = SDFCreate(PELoadConfigDirectory, PELoadConfigDirectorySize, pContext->hReader);
	SDFPrint(THIS->hLoadConfigDirectory);
	return 1;
}

void PEFileProcessDirectory(ExecutableContext * pContext, uint32_t index)
{
	switch (index)
	{
	case 0x00: printf("IMAGE_DIRECTORY_ENTRY_EXPORT        \n"); break;
	case 0x01: printf("IMAGE_DIRECTORY_ENTRY_IMPORT        \n"); break;
	case 0x02: printf("IMAGE_DIRECTORY_ENTRY_RESOURCE      \n"); break;
	case 0x03: printf("IMAGE_DIRECTORY_ENTRY_EXCEPTION     \n"); break;
	case 0x04: printf("IMAGE_DIRECTORY_ENTRY_SECURITY      \n"); break;
	case 0x05: printf("IMAGE_DIRECTORY_ENTRY_BASERELOC     \n"); break;
	case 0x06: printf("IMAGE_DIRECTORY_ENTRY_DEBUG         \n"); break;
	case 0x07: printf("IMAGE_DIRECTORY_ENTRY_ARCHITECTURE  \n"); break;
	case 0x08: printf("IMAGE_DIRECTORY_ENTRY_GLOBALPTR     \n"); break;
	case 0x09: printf("IMAGE_DIRECTORY_ENTRY_TLS           \n"); break;
	case 0x0A: printf("IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG   \n"); break;
	case 0x0B: printf("IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT  \n"); break;
	case 0x0C: printf("IMAGE_DIRECTORY_ENTRY_IAT           \n"); break;
	case 0x0D: printf("IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT  \n"); break;
	case 0x0E: printf("IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR\n"); break;
	case 0x0F: printf("IMAGE_DIRECTORY_ENTRY_RESERVED      \n"); break;
	default: break;
	}
	printf("Size    : 0x%08X\n" , THIS->DataDirectories[index].Size);
	printf("Address : 0x%08X\n" , THIS->DataDirectories[index].VirtualAddress);

	if (THIS->DataDirectories[index].Size > 0 && THIS->DataDirectories[index].VirtualAddress > 0)
	{
		switch (index)
		{
		case 0x00: PEFileProcessDirectoryExport    (pContext, &THIS->DataDirectories[index]); break;
		case 0x01: PEFileProcessDirectoryImport    (pContext, &THIS->DataDirectories[index]); break;
		case 0x06: PEFileProcessDirectoryDebug     (pContext, &THIS->DataDirectories[index]); break;
		case 0x0A: PEFileProcessDirectoryLoadConfig(pContext, &THIS->DataDirectories[index]); break;
		default: break;
		}
	}
	printf("\n");
}

uint32_t PEFileGetEntryPoint(ExecutableContext * pContext)
{
	return PERVAToOffset(pContext, THIS->AddressOfEntryPoint);
}

uint32_t PEFileGetStubEntryPoint(ExecutableContext * pContext)
{
	return SDFSizeInBytes(PEDOSHeader, PEDOSHeaderSize);
}

uint32_t PEFileGetExportCount(ExecutableContext * pContext)
{
	return THIS->NumberOfFunctions;
}

uint32_t PEFileGetExportAddress(ExecutableContext * pContext, uint32_t index)
{
	uint32_t address = 0;

	if (index >= THIS->NumberOfFunctions)
	{
		return 0;
	}

	ReaderSeek(pContext->hReader, THIS->OffsetExportFunctions + index * sizeof(uint32_t));
	ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
	return PERVAToOffset(pContext, address);
}

char * PEFileGetExportName(ExecutableContext * pContext, uint32_t index)
{
	uint32_t address = 0;

	if (index >= THIS->NumberOfFunctions)
	{
		return 0;
	}

	ReaderSeek(pContext->hReader, THIS->OffsetExportNames + index * sizeof(uint32_t));
	ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
	address = PERVAToOffset(pContext, address);
	return FetchString(pContext, address);
}

char * PEFileGetExportForwarderName(ExecutableContext * pContext, uint32_t index)
{
	uint32_t address = 0;

	if (index >= THIS->NumberOfFunctions)
	{
		return 0;
	}

	ReaderSeek(pContext->hReader, THIS->OffsetExportFunctions + index * sizeof(uint32_t));
	ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
	address = PERVAToOffset(pContext, address);
	if (THIS->OffsetExport <= address && address <= THIS->OffsetExport + THIS->SizeExport)
	{
		return FetchString(pContext, address);
	}
	return NULL;
}

void PEFileDestroy(ExecutableContext * pContext)
{
	uint32_t i = 0;
	for (i = 0; i < THIS->NumberOfSections; ++i)
	{
		SDFDestroy(THIS->phSectionHeaders[i]);
	}
	free(THIS->phSectionHeaders);
	SDFDestroy(THIS->hDOSHeader);
	SDFDestroy(THIS->hPEFileHeader);
	SDFDestroy(THIS->hOptionalHeader);
	SDFDestroy(THIS->hExportDirectory);
	SDFDestroy(THIS->hDebugDirectory);
	SDFDestroy(THIS->hLoadConfigDirectory);
	free(THIS->DataDirectories);
}

int PEFileCreate(ExecutableContext * pContext)
{
	uint32_t size = 0;
	uint32_t Signature = 0;
	uint16_t Magic = 0;
	uint32_t OffsetSectionHeaders = 0;
	uint32_t SizeOfOptionalHeader = 0;

	PEFileContext * pPEFileContext = (PEFileContext*) malloc(sizeof(PEFileContext));
	if (NULL == pPEFileContext)
	{
		return 0;
	}
	memset(pPEFileContext, 0, sizeof(PEFileContext));
	pContext->pPrivate                = pPEFileContext;
	pContext->pGetEntryPoint          = PEFileGetEntryPoint;
	pContext->pGetStubEntryPoint      = PEFileGetStubEntryPoint;
	pContext->pGetExportCount         = PEFileGetExportCount;
	pContext->pGetExportAddress       = PEFileGetExportAddress;
	pContext->pGetExportName          = PEFileGetExportName;
	pContext->pGetExportForwarderName = PEFileGetExportForwarderName;
	pContext->pDestroy                = PEFileDestroy;

	THIS->hDOSHeader = SDFCreate(PEDOSHeader, PEDOSHeaderSize, pContext->hReader);
	SDFPrint(THIS->hDOSHeader);

	if (SDFReadUInt16(THIS->hDOSHeader, PEDOSHeaderSignature) != PEDOSSignature)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, SDFReadUInt32(THIS->hDOSHeader, PEDOSHeaderAddressPE)))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &Signature, sizeof(uint32_t)))
	{
		return 0;
	}
	if (PENTSignature != Signature)
	{
		return 0;
	}
	printf("Signature : \n"); PrintSignature(Signature, 4);
	THIS->hPEFileHeader = SDFCreate(PEFileHeader, PEFileHeaderSize, pContext->hReader);
	SDFPrint(THIS->hPEFileHeader);
	SizeOfOptionalHeader = SDFReadUInt16(THIS->hPEFileHeader, PEFileHeaderSizeOfOptionalHeader);
	if (SizeOfOptionalHeader < SDFSizeInBytes(PEOptionalHeader, PEOptionalHeaderSize))
	{
		return 0;
	}
	THIS->hOptionalHeader = SDFCreate(PEOptionalHeader, PEOptionalHeaderSize, pContext->hReader);
	Magic = SDFReadUInt16(THIS->hOptionalHeader, PEOptionalHeaderMagic);
	if (PE32Magic != Magic && PE64Magic != Magic)
	{
		return 0;
	}
	SDFPrint(THIS->hOptionalHeader);
	THIS->AddressOfEntryPoint = SDFReadUInt32(THIS->hOptionalHeader, PEOptionalHeaderAddressOfEntryPoint);
	OffsetSectionHeaders = SDFReadUInt32(THIS->hDOSHeader, PEDOSHeaderAddressPE) + sizeof(uint32_t) + SDFSizeInBytes(PEFileHeader, PEFileHeaderSize) + SizeOfOptionalHeader;
	THIS->DataDirectoriesCount = MIN(PEDataDirectoryCount, (SizeOfOptionalHeader - SDFSizeInBytes(PEOptionalHeader, PEOptionalHeaderSize)) / sizeof(PEDataDirectory));
	THIS->DataDirectoriesCount = MIN(SDFReadUInt32(THIS->hOptionalHeader, PEOptionalHeaderNumberOfRvaAndSizes), THIS->DataDirectoriesCount);
	if (THIS->DataDirectoriesCount > 0)
	{
		THIS->DataDirectories = (PEDataDirectory*) malloc(sizeof(PEDataDirectory) * THIS->DataDirectoriesCount);
		if (NULL == THIS->DataDirectories)
		{
			return 0;
		}
		if (0 == ReaderRead(pContext->hReader, THIS->DataDirectories, sizeof(PEDataDirectory) * THIS->DataDirectoriesCount))
		{
			return 0;
		}
	}
	THIS->NumberOfSections = SDFReadUInt16(THIS->hPEFileHeader, PEFileHeaderNumberOfSections);
	if (0 == THIS->NumberOfSections)
	{
		return 0;
	}
	THIS->phSectionHeaders = (HSDF*) malloc(sizeof(HSDF) * THIS->NumberOfSections);
	if (NULL == THIS->phSectionHeaders)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, OffsetSectionHeaders))
	{
		return 0;
	}
	{
		uint32_t i = 0;
		for (i = 0; i < THIS->NumberOfSections; ++i)
		{
			THIS->phSectionHeaders[i] = SDFCreate(PESectionHeader, PESectionHeaderSize, pContext->hReader);
			SDFPrint(THIS->phSectionHeaders[i]);
		}
	}
	{
		uint8_t i = 0;
		for (i = 0; i < THIS->DataDirectoriesCount; ++i)
		{
			PEFileProcessDirectory(pContext, i);
		}
	}
	return 1;
}
