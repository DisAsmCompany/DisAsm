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
PEFileContext;

#undef THIS
#define THIS ((PEFileContext*)(pContext->pPrivate))

void PrintSignature(uint32_t Signature, uint8_t size)
{
	uint8_t i = 0;
	if (size == 2) printf("0x%04X ", Signature);
	if (size == 4) printf("0x%08X ", Signature);
	printf("'");
	for (i = 0; i < size; ++i)
	{
		char byte = (Signature >> (i * 8)) & 0xFF;
		if (isalnum(byte))
		{
			printf("%c", byte);
		}
		else
		{
			printf("[%02X]", byte);
		}
	}
	printf("'");
	printf("\n");
}

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
	for (i = 0; i < THIS->FileHeader.NumberOfSections; ++i)
	{
		if (THIS->SectionHeaders[i].VirtualAddress <= RVA && 
			RVA <= THIS->SectionHeaders[i].VirtualAddress + THIS->SectionHeaders[i].SizeOfRawData)
		{
			offset = THIS->SectionHeaders[i].PointerToRawData + RVA - THIS->SectionHeaders[i].VirtualAddress;
			break;
		}
	}
	return offset;
}

int PEFileProcessDirectoryExport(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t i = 0;
	char * name = "";
	THIS->OffsetExport = PERVAToOffset(pContext, pDirectory->VirtualAddress);
	THIS->SizeExport = pDirectory->Size;
	if (pDirectory->Size < sizeof(PEExportDirectory))
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
	if (0 == ReaderRead(pContext->hReader, &THIS->ExportDirectory, sizeof(PEExportDirectory)))
	{
		return 0;
	}
	PEPrintExportDirectory(&THIS->ExportDirectory);
	THIS->OffsetExportFunctions = PERVAToOffset(pContext, THIS->ExportDirectory.AddressOfFunctions);
	THIS->OffsetExportOrdinals = PERVAToOffset(pContext, THIS->ExportDirectory.AddressOfNameOrdinals);
	THIS->OffsetExportNames = PERVAToOffset(pContext, THIS->ExportDirectory.AddressOfNames);

	for (i = 0; i < THIS->ExportDirectory.NumberOfFunctions; ++i)
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

		// Forwarder RVA (within Export Directory)
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
	while (pos + sizeof(PEImportDescriptor) <= pDirectory->Size)
	{
		PEImportDescriptor ImportDescriptor;
		char * name = NULL;
		if (0 == ReaderSeek(pContext->hReader, offset + pos))
		{
			return 0;
		}
		if (0 == ReaderRead(pContext->hReader, &ImportDescriptor, sizeof(PEImportDescriptor)))
		{
			return 0;
		}
		if (0 == ImportDescriptor.OriginalFirstThunk)
		{
			break;
		}
		address = PERVAToOffset(pContext, ImportDescriptor.Name);
		PEPrintImportDescriptor(&ImportDescriptor);
		address = PERVAToOffset(pContext, ImportDescriptor.OriginalFirstThunk);
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
		}
		pos += sizeof(PEImportDescriptor);
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
	if (pDirectory->Size < sizeof(PEDebugDirectory))
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, offset))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &THIS->DebugDirectory, sizeof(PEDebugDirectory)))
	{
		return 0;
	}
	PEPrintDebugDirectory(&THIS->DebugDirectory);
	return 1;
}

int PEFileProcessDirectoryLoadConfig(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t offset = PERVAToOffset(pContext, pDirectory->VirtualAddress);

	if (0 == offset)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, offset))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &THIS->LoadConfigDirectory.Size, sizeof(uint32_t)))
	{
		return 0;
	}
	if (THIS->LoadConfigDirectory.Size < sizeof(PELoadConfigDirectory))
	{
		return 0;
	}
	THIS->LoadConfigDirectory.Size = sizeof(PELoadConfigDirectory);
	if (0 == ReaderRead(pContext->hReader, &THIS->LoadConfigDirectory.TimeDateStamp, THIS->LoadConfigDirectory.Size - sizeof(uint32_t)))
	{
		return 0;
	}
	PEPrintLoadConfigDirectory(&THIS->LoadConfigDirectory);
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
	return PERVAToOffset(pContext, THIS->OptionalHeader.AddressOfEntryPoint);
}

uint32_t PEFileGetStubEntryPoint(ExecutableContext * pContext)
{
	return sizeof(PEDOSHeader);
}

uint32_t PEFileGetExportCount(ExecutableContext * pContext)
{
	return THIS->ExportDirectory.NumberOfFunctions;
}

uint32_t PEFileGetExportAddress(ExecutableContext * pContext, uint32_t index)
{
	uint32_t address = 0;

	ReaderSeek(pContext->hReader, THIS->OffsetExportFunctions + index * sizeof(uint32_t));
	ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
	return PERVAToOffset(pContext, address);
}

char * PEFileGetExportName(ExecutableContext * pContext, uint32_t index)
{
	uint32_t address = 0;

	ReaderSeek(pContext->hReader, THIS->OffsetExportNames + index * sizeof(uint32_t));
	ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
	address = PERVAToOffset(pContext, address);
	return FetchString(pContext, address);
}

char * PEFileGetExportForwarderName(ExecutableContext * pContext, uint32_t index)
{
	uint32_t address = 0;

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
	free(THIS->SectionHeaders);
	free(THIS->DataDirectories);
}

int PEFileCreate(ExecutableContext * pContext)
{
	uint32_t size = 0;
	uint32_t OffsetSectionHeaders = 0;

	PEFileContext * pPEFileContext = (PEFileContext*) malloc(sizeof(PEFileContext));
	if (NULL == pPEFileContext)
	{
		return 0;
	}
	pContext->pPrivate                = pPEFileContext;
	pContext->pGetEntryPoint          = PEFileGetEntryPoint;
	pContext->pGetStubEntryPoint      = PEFileGetStubEntryPoint;
	pContext->pGetExportCount         = PEFileGetExportCount;
	pContext->pGetExportAddress       = PEFileGetExportAddress;
	pContext->pGetExportName          = PEFileGetExportName;
	pContext->pGetExportForwarderName = PEFileGetExportForwarderName;
	pContext->pDestroy                = PEFileDestroy;

	if (0 == ReaderRead(pContext->hReader, &THIS->DOSHeader, sizeof(PEDOSHeader)))
	{
		return 0;
	}
	if (THIS->DOSHeader.Signature != PEDOSSignature)
	{
		return 0;
	}
	PEPrintDOSHeader(&THIS->DOSHeader);
	if (0 == ReaderSeek(pContext->hReader, THIS->DOSHeader.AddressPE))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &THIS->Signature, sizeof(uint32_t)))
	{
		return 0;
	}
	if (THIS->Signature != PENTSignature)
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &THIS->FileHeader, sizeof(PEFileHeader)))
	{
		return 0;
	}
	printf("Signature : \n"); PrintSignature(THIS->Signature, 4);
	PEPrintFileHeader(&THIS->FileHeader);
	if (THIS->FileHeader.SizeOfOptionalHeader < sizeof(PEOptionalHeader))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &THIS->OptionalHeader, sizeof(PEOptionalHeader)))
	{
		return 0;
	}
	PEPrintOptionalHeader(&THIS->OptionalHeader);
	OffsetSectionHeaders = THIS->DOSHeader.AddressPE + sizeof(uint32_t) + sizeof(PEFileHeader) + THIS->FileHeader.SizeOfOptionalHeader;
	THIS->DataDirectoriesCount = MIN(PEDataDirectoryCount, (THIS->FileHeader.SizeOfOptionalHeader - sizeof(PEOptionalHeader)) / sizeof(PEDataDirectory));
	THIS->DataDirectoriesCount = MIN(THIS->OptionalHeader.NumberOfRvaAndSizes, THIS->DataDirectoriesCount);
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
	if (THIS->FileHeader.NumberOfSections == 0)
	{
		return 0;
	}
	size = sizeof(PESectionHeader) * THIS->FileHeader.NumberOfSections;
	THIS->SectionHeaders = (PESectionHeader*) malloc(size);
	if (NULL == THIS->SectionHeaders)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, OffsetSectionHeaders))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, THIS->SectionHeaders, size))
	{
		return 0;
	}
	{
		uint8_t i = 0;
		for (i = 0; i < THIS->FileHeader.NumberOfSections; ++i)
		{
			PEPrintSectionHeader(&THIS->SectionHeaders[i]);
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
