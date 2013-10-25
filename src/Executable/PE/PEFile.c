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

#include "PEMachine.h"
#include "PESubsystem.h"
#include "PEMagic.h"
#include "PEDebugType.h"
#include "PECharacteristics.h"
#include "PEDllCharacteristics.h"
#include "PESectionCharacteristics.h"
#include "PEDOSHeader.h"
#include "PEFileHeader.h"
#include "PEDataDirectory.h"
#include "PEOptionalHeader.h"
#include "PEOptionalHeaderExtra.h"
#include "PEOptionalHeaderExtra64.h"
#include "PESectionHeader.h"
#include "PEExportDirectory.h"
#include "PEImportDescriptor.h"
#include "PEDebugDirectory.h"
#include "PELoadConfigDirectory.h"

#include "COFFSectionNumber.h"
#include "COFFSymbolType.h"
#include "COFFSymbolClass.h"
#include "COFFLibraryHeader.h"
#include "COFFSymbolTable.h"

typedef struct PEFileContext_t
{
	HSDF hDOSHeader;
	HSDF hFileHeader;
	HSDF hOptionalHeader;
    HSDF hOptionalHeaderExtra;
	uint32_t DataDirectoriesCount;
	PEDataDirectory * DataDirectories;
	HSDF * phSectionHeaders;
	HSDF hExportDirectory;
	HSDF hDebugDirectory;
	HSDF hLoadConfigDirectory;
	uint32_t NumberOfSections;
	uint32_t NumberOfFunctions;
    uint32_t NumberOfNames;
	uint32_t AddressOfEntryPoint;
	uint32_t OffsetExport;
	uint32_t SizeExport;
	uint32_t OffsetExportFunctions;
	uint32_t OffsetExportOrdinals;
	uint32_t OffsetExportNames;
	uint32_t AddressPE;
	uint32_t PointerToSymbolTable;
	uint32_t NumberOfSymbols;
	uint8_t PE64;
	uint8_t Object;
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
	if (pContext->memory || 1 == THIS->Object)
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

char * NameForOrdinal(ExecutableContext * pContext, uint32_t ordinal)
{
    char * name = NULL;
    uint16_t value  = 0;
    uint32_t address = 0;
    uint32_t i = 0;
    for (i = 0; i < THIS->NumberOfNames; ++i)
    {
        ReaderSeek(pContext->hReader, THIS->OffsetExportOrdinals + i * sizeof(uint16_t));
        ReaderRead(pContext->hReader, &value, sizeof(uint16_t));

        /* specification is wrong : we don't need to subtract Ordinal Base here */
        if (value == ordinal)
        {
            ReaderSeek(pContext->hReader, THIS->OffsetExportNames + i * sizeof(uint32_t));
            ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
            address = PERVAToOffset(pContext, address);
            if (0 != address)
            {
                name = FetchString(pContext, address);
            }
            break;
        }
    }
    return name;
}

int PEFileProcessDirectoryExport(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t i = 0;
	char * name = NULL;
	THIS->OffsetExport = PERVAToOffset(pContext, pDirectory->VirtualAddress);
	THIS->SizeExport = pDirectory->Size;
	if (pDirectory->Size < SDFSizeInBytes(PEExportDirectory))
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
	THIS->hExportDirectory = SDFCreate(PEExportDirectory, pContext->hReader);
	SDFPrint(THIS->hExportDirectory);
	THIS->NumberOfFunctions = SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryNumberOfFunctions);
    THIS->NumberOfNames    = SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryNumberOfFunctions);
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
        if (0 != address)
        {
            name = NameForOrdinal(pContext, i);
        }
		/* Forwarder RVA (within Export Directory) */
		if (THIS->OffsetExport <= address && address + sizeof(uint32_t) <= THIS->OffsetExport + THIS->SizeExport)
		{
			char * forwarder = FetchString(pContext, address);

            if (name)
            {
                printf("0x%04X 0x%08X %s -> %s\n", i, address, name, forwarder);
            }
            else
            {
                printf("0x%04X 0x%08X [0x%02X] -> %s\n", i, address, i, forwarder);
            }

			free(forwarder);
		}
		else
		{
            if (name)
            {
                printf("0x%04X 0x%08X %s\n", i, address, name);
            }
            else
            {
                printf("0x%04X 0x%08X [0x%02X]\n", i, address, i);
            }
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
	while (pos + SDFSizeInBytes(PEImportDescriptor) <= pDirectory->Size)
	{
		HSDF hImportDescriptor;
		char * name = NULL;
		uint32_t OriginalFirstThunk = 0;
		if (0 == ReaderSeek(pContext->hReader, offset + pos))
		{
			return 0;
		}
		hImportDescriptor = SDFCreate(PEImportDescriptor, pContext->hReader);
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
					if (0 != ptr)
                    {
                        ReaderSeek(pContext->hReader, ptr);
					    ReaderRead(pContext->hReader, &hint, sizeof(uint16_t));
					    name = FetchString(pContext, ptr + sizeof(uint16_t));
					    printf("0x%04X %s\n", hint, name);
					    free(name);
                    }
                    else
                    {
                        printf("0x%04X\n", hint);
                    }
				}
			}
			printf("\n");
		}
		SDFDestroy(hImportDescriptor);
		pos += SDFSizeInBytes(PEImportDescriptor);
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
	if (pDirectory->Size < SDFSizeInBytes(PEDebugDirectory))
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, offset))
	{
		return 0;
	}
	THIS->hDebugDirectory = SDFCreate(PEDebugDirectory, pContext->hReader);
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
	if (size < SDFSizeInBytes(PELoadConfigDirectory))
	{
		return 0;
	}
	THIS->hLoadConfigDirectory = SDFCreate(PELoadConfigDirectory, pContext->hReader);
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
	return THIS->Object ? 0 : PERVAToOffset(pContext, THIS->AddressOfEntryPoint);
}

uint32_t PEFileGetStubEntryPoint(ExecutableContext * pContext)
{
	return THIS->Object ? 0 : SDFSizeInBytes(PEDOSHeader);
}

uint32_t PEFileGetExportCount(ExecutableContext * pContext)
{
	return THIS->Object ? THIS->NumberOfSymbols : THIS->NumberOfFunctions;
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
	return NameForOrdinal(pContext, index);
}

char * PEFileGetExportForwarderName(ExecutableContext * pContext, uint32_t index)
{
	uint32_t address = 0;

	if (1 == THIS->Object)
	{
		return 0;
	}

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

Architecture PEFileGetArchitecture(ExecutableContext * pContext)
{
	Architecture arch = ArchUnknown;
	PEMachine machine = SDFReadUInt16(THIS->hFileHeader, PEFileHeaderMachine);
	switch (machine)
	{
	case kPEMachineX86: arch = ArchX86; break;
	case kPEMachineX64: arch = ArchX64; break;
	default: arch = ArchUnknown; break;
	}
	return arch;
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
	SDFDestroy(THIS->hFileHeader);
	SDFDestroy(THIS->hOptionalHeader);
    SDFDestroy(THIS->hOptionalHeaderExtra);
	SDFDestroy(THIS->hExportDirectory);
	SDFDestroy(THIS->hDebugDirectory);
	SDFDestroy(THIS->hLoadConfigDirectory);
	free(THIS->DataDirectories);
	free(THIS);
}

int PEFileOpen(ExecutableContext * pContext)
{
	uint32_t Signature;

	THIS->hDOSHeader = SDFCreate(PEDOSHeader, pContext->hReader);

	if (0 == ReaderSeek(pContext->hReader, 0))
	{
		return 0;
	}
	if (kPEDOSSignature != SDFReadUInt16(THIS->hDOSHeader, PEDOSHeaderSignature))
	{
		return 0;
	}
	SDFPrint(THIS->hDOSHeader);
	THIS->AddressPE = SDFReadUInt32(THIS->hDOSHeader, PEDOSHeaderAddressPE);
	if (0 == ReaderSeek(pContext->hReader, THIS->AddressPE))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &Signature, sizeof(uint32_t)))
	{
		return 0;
	}
	if (kPENTSignature != Signature)
	{
		return 0;
	}
	THIS->hFileHeader = SDFCreate(PEFileHeader, pContext->hReader);
	SDFPrint(THIS->hFileHeader);
	return 1;
}

int OBJFileOpen(ExecutableContext * pContext)
{
	uint16_t Arch = ArchUnknown;
	if (0 == ReaderSeek(pContext->hReader, 0))
	{
		return 0;
	}
	THIS->hFileHeader = SDFCreate(PEFileHeader, pContext->hReader);
	Arch = SDFReadUInt16(THIS->hFileHeader, PEFileHeaderMachine);
	if (kPEMachineX86 == Arch || kPEMachineX64 == Arch)
	{
		SDFPrint(THIS->hFileHeader);
		THIS->Object = 1;
		THIS->PointerToSymbolTable = SDFReadUInt32(THIS->hFileHeader, PEFileHeaderPointerToSymbolTable);
		THIS->NumberOfSymbols = SDFReadUInt32(THIS->hFileHeader, PEFileHeaderNumberOfSymbols);

		return 1;
	}
	return 0;
}

int OBJProcessSymbols(ExecutableContext * pContext)
{
	if (1 == THIS->Object)
	{
		uint32_t i = 0;
		uint32_t j = 0;
		char * buffer = 0;
		uint32_t size = 0;
		if (0 == ReaderSeek(pContext->hReader, THIS->PointerToSymbolTable))
		{
			return 0;
		}
		for (i = 0; i < THIS->NumberOfSymbols; ++i)
		{
			uint8_t Aux = 0;
			uint8_t Class = 0;
			HSDF hSymbols = SDFCreate(COFFSymbolTable, pContext->hReader);
			SDFPrint(hSymbols);

			Class = SDFReadUInt8(hSymbols, COFFSymbolTableStorageClass);
			
			Aux = SDFReadUInt8(hSymbols, COFFSymbolTableNumberOfAuxiliarySymbols);

			for (j = 0; j < Aux; ++j)
			{
				if (kCOFFSymbolClassFile == Class)
				{
					HSDF hAux = SDFCreate(COFFSymbolTableAuxiliaryFormatFiles, pContext->hReader);
					SDFPrint(hAux);
					SDFDestroy(hAux);
				}
				else
				{
					ReaderSkip(pContext->hReader, 18);
				}
			}
			i += Aux;
			
			SDFDestroy(hSymbols);
		}
		if (0 == ReaderSeek(pContext->hReader, THIS->PointerToSymbolTable + THIS->NumberOfSymbols * 18))
		{
			return 0;
		}
		if (0 == ReaderRead(pContext->hReader, &size, sizeof(uint32_t)))
		{
			return 0;
		}
		if (size < sizeof(uint32_t))
		{
			return 0;
		}
		size -= sizeof(uint32_t);
		if (NULL == (buffer = (char*) malloc(size)))
		{
			return 0;
		}
		if (0 == ReaderRead(pContext->hReader, buffer, size))
		{
			free(buffer);
			return 0;
		}
		for (i = 0; i < size; i += strlen(buffer + i) + 1)
		{
			printf("%s\n", buffer + i);
		}
		free(buffer);
	}
	return 1;
}

int PEFileInit(ExecutableContext * pContext)
{
	uint16_t Magic = 0;
	uint32_t OffsetSectionHeaders = 0;
	uint32_t SizeOfOptionalHeader = 0;
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t PEOptionalHeaderSize = SDFSizeInBytes(PEOptionalHeader);
	uint32_t ExtraSize = 0;
	SizeOfOptionalHeader = SDFReadUInt16(THIS->hFileHeader, PEFileHeaderSizeOfOptionalHeader);

	if (SizeOfOptionalHeader >= PEOptionalHeaderSize)
	{
		/* file has an optional header */
		const SDFElement * Extra = NULL;
		THIS->hOptionalHeader = SDFCreate(PEOptionalHeader, pContext->hReader);
		Magic = SDFReadUInt16(THIS->hOptionalHeader, PEOptionalHeaderMagic);
		if (kPEMagic32 != Magic && kPEMagic64 != Magic)
		{
			return 0;
		}
		THIS->AddressOfEntryPoint = SDFReadUInt32(THIS->hOptionalHeader, PEOptionalHeaderAddressOfEntryPoint);
		THIS->PE64 = kPEMagic64 == Magic;
		SDFPrint(THIS->hOptionalHeader);
		Extra = THIS->PE64 ? PEOptionalHeaderExtra64 : PEOptionalHeaderExtra;
		ExtraSize = SDFSizeInBytes(Extra);
		if (SizeOfOptionalHeader >= PEOptionalHeaderSize + ExtraSize)
		{
			THIS->hOptionalHeaderExtra = SDFCreate(Extra, pContext->hReader);
			SDFPrint(THIS->hOptionalHeaderExtra);
		}
		else if (0 == THIS->Object)
		{
			return 0;
		}
		THIS->DataDirectoriesCount = MIN(kPEDataDirectoryCount, (SizeOfOptionalHeader - PEOptionalHeaderSize - ExtraSize / sizeof(PEDataDirectory)));
		THIS->DataDirectoriesCount = MIN(SDFReadUInt32(THIS->hOptionalHeaderExtra, THIS->PE64 ? PEOptionalHeaderNumberOfRvaAndSizes64 : PEOptionalHeaderNumberOfRvaAndSizes), THIS->DataDirectoriesCount);
	}
	else if (0 == THIS->Object)
	{
		/* although optional header called optional, it is required for executable files */
		return 0;
	}
	OffsetSectionHeaders = SDFSizeInBytes(PEFileHeader) + SizeOfOptionalHeader;
	if (0 == THIS->Object)
	{
		OffsetSectionHeaders += THIS->AddressPE + sizeof(uint32_t);
	}
	if (THIS->DataDirectoriesCount > 0)
	{
		if (NULL == (THIS->DataDirectories = (PEDataDirectory*) malloc(sizeof(PEDataDirectory) * THIS->DataDirectoriesCount)))
		{
			return 0;
		}
		if (0 == ReaderRead(pContext->hReader, THIS->DataDirectories, sizeof(PEDataDirectory) * THIS->DataDirectoriesCount))
		{
			return 0;
		}
	}
	if (0 == (THIS->NumberOfSections = SDFReadUInt16(THIS->hFileHeader, PEFileHeaderNumberOfSections)))
	{
		return 0;
	}
	if (NULL == (THIS->phSectionHeaders = (HSDF*) malloc(sizeof(HSDF) * THIS->NumberOfSections)))
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, OffsetSectionHeaders))
	{
		return 0;
	}
	for (i = 0; i < THIS->NumberOfSections; ++i)
	{
		THIS->phSectionHeaders[i] = SDFCreate(PESectionHeader, pContext->hReader);
		SDFPrint(THIS->phSectionHeaders[i]);
	}
	for (i = 0; i < THIS->DataDirectoriesCount; ++i)
	{
		PEFileProcessDirectory(pContext, i);
	}
	OBJProcessSymbols(pContext);
	return 1;
}

int GetString(HREADER hReader)
{
	char c = 0;
	for (;;)
	{
		if (0 == ReaderRead(hReader, &c, sizeof(char)))
		{
			return 0;
		}
		if (0 == c)
		{
			break;
		}
		printf("%c", c);
	}
	printf("\n");
	return 1;
}

int LIBFileOpen(ExecutableContext * pContext)
{
	HSDF hHeader = NULL;
	uint32_t NumberOfMembers = 0;
	uint32_t NumberOfSymbols = 0;
	uint32_t i = 0;
	char Signature[8] = {0};
	if (0 == ReaderSeek(pContext->hReader, 0))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, Signature, kCOFFLibrarySignatureSize))
	{
		return 0;
	}
	if (0 != memcmp(Signature, kCOFFLibrarySignature, kCOFFLibrarySignatureSize))
	{
		return 0;
	}
	hHeader = SDFCreate(COFFLibraryHeader, pContext->hReader);
	SDFPrint(hHeader);
	/* first linker member */
	if (0 == ReaderRead(pContext->hReader, &NumberOfSymbols, sizeof(uint32_t)))
	{
		return 0;
	}
	NumberOfSymbols = LE2BE32(NumberOfSymbols);
	for (i = 0; i < NumberOfSymbols; ++i)
	{
		uint32_t Offset = 0;
		if (0 == ReaderRead(pContext->hReader, &Offset, sizeof(uint32_t)))
		{
			return 0;
		}
		printf("Offset : 0x%08X\n", Offset);
	}
	for (i = 0; i < NumberOfSymbols; ++i)
	{
		if (0 == GetString(pContext->hReader))
		{
			return 0;
		}
	}
	hHeader = SDFCreate(COFFLibraryHeader, pContext->hReader);
	SDFPrint(hHeader);
	/* second linker member */
	if (0 == ReaderRead(pContext->hReader, &NumberOfMembers, sizeof(uint32_t)))
	{
		return 0;
	}
	for (i = 0; i < NumberOfMembers; ++i)
	{
		uint32_t Offset = 0;
		if (0 == ReaderRead(pContext->hReader, &Offset, sizeof(uint32_t)))
		{
			return 0;
		}
		printf("Offset : 0x%08X\n", Offset);
	}
	if (0 == ReaderRead(pContext->hReader, &NumberOfSymbols, sizeof(uint32_t)))
	{
		return 0;
	}
	for (i = 0; i < NumberOfSymbols; ++i)
	{
		uint8_t Index1 = 0;
		uint8_t Index2 = 0;
		if (0 == ReaderRead(pContext->hReader, &Index1, sizeof(uint8_t)))
		{
			return 0;
		}
		if (0 == ReaderRead(pContext->hReader, &Index2, sizeof(uint8_t)))
		{
			return 0;
		}
		printf("0x%02X 0x%02X\n", Index1, Index2);
	}
	for (i = 0; i < NumberOfSymbols; ++i)
	{
		if (0 == GetString(pContext->hReader))
		{
			return 0;
		}
	}
	hHeader = SDFCreate(COFFLibraryHeader, pContext->hReader);
	SDFPrint(hHeader);
	/* long names member */
	for (i = 0; i < NumberOfMembers; ++i)
	{
		if (0 == GetString(pContext->hReader))
		{
			return 0;
		}
	}
	return 0;
}

int PEFileCreate(ExecutableContext * pContext)
{
	PEFileContext * pPEFileContext = (PEFileContext*) malloc(sizeof(PEFileContext));
	if (NULL == pPEFileContext)
	{
		return 0;
	}
	memset(pPEFileContext, 0, sizeof(PEFileContext));
	pContext->pPrivate = pPEFileContext;

	if (0 == PEFileOpen(pContext) && 0 == OBJFileOpen(pContext) && 0 == LIBFileOpen(pContext))
	{
		PEFileDestroy(pContext);
		return 0;
	}
	if (0 == PEFileInit(pContext))
	{
		PEFileDestroy(pContext);
		return 0;
	}

	pContext->pGetArchitecture        = PEFileGetArchitecture;
	pContext->pGetEntryPoint          = PEFileGetEntryPoint;
	pContext->pGetStubEntryPoint      = PEFileGetStubEntryPoint;
	pContext->pGetExportCount         = PEFileGetExportCount;
	pContext->pGetExportAddress       = PEFileGetExportAddress;
	pContext->pGetExportName          = PEFileGetExportName;
	pContext->pGetExportForwarderName = PEFileGetExportForwarderName;
	pContext->pDestroy                = PEFileDestroy;
	
	return 1;
}
