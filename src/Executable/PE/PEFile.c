/*
 * Filename: PEFile.c
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: PE file abstraction
 *              (Portable Executable)
 *
 *
 */

#include "../../DisAsm/DisAsm"
#include "../Executable"

#include "../MZ/MZDOSHeader.h"
#include "PEMachine.h"
#include "PESubsystem.h"
#include "PEMagic.h"
#include "PEDebugType.h"
#include "PECharacteristics.h"
#include "PEDllCharacteristics.h"
#include "PESectionCharacteristics.h"
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
	HSDF hExportDirectory;
	HSDF hDebugDirectory;
	HSDF hLoadConfigDirectory;
	uint32_t NumberOfFunctions;
    uint32_t NumberOfNames;
	uint32_t OffsetExport;
	uint32_t SizeExport;
	uint32_t AddressPE;
	uint32_t PointerToSymbolTable;
	uint32_t NumberOfSymbols;
	uint8_t PE64;
	uint8_t Object;
	uint32_t * ExportFunctions;
	uint32_t * ExportNames;
	uint16_t * ExportOrdinals;
}
PEFileContext;

#undef THIS
#define THIS ((PEFileContext*)(pContext->pPrivate))

uint32_t NameForOrdinal(ExecutableContext * pContext, uint32_t ordinal)
{
    uint32_t address = 0;
    uint32_t i = 0;
	if (NULL != THIS->ExportOrdinals && NULL != THIS->ExportNames)
	{
		for (i = 0; i < THIS->NumberOfNames; ++i)
		{
			/* specification is wrong : we don't need to subtract Ordinal Base here */
			if (ordinal == THIS->ExportOrdinals[i])
			{
				address = ExecutableRVAToOffset(pContext, THIS->ExportNames[i]);
				break;
			}
		}
	}
    return address;
}

int PEFileProcessDirectoryExport(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t OffsetExportFunctions, OffsetExportOrdinals, OffsetExportNames;
	uint32_t i = 0;
	uint32_t size = 0;
	char * name = NULL;
	THIS->OffsetExport = ExecutableRVAToOffset(pContext, pDirectory->VirtualAddress);
	THIS->SizeExport = pDirectory->Size;
	if (pDirectory->Size < SDFSizeInBytes(PEExportDirectory))
	{
		return 0;
	}
	if (0 == THIS->OffsetExport)
	{
		return 0;
	}
	CHECK_CALL(ReaderSeek(pContext->hReader, THIS->OffsetExport));
	CHECK_CALL(THIS->hExportDirectory = SDFCreate(PEExportDirectory, pContext->hReader));
	SDFPrint(THIS->hExportDirectory);
	THIS->NumberOfFunctions = SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryNumberOfFunctions);
    THIS->NumberOfNames     = SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryNumberOfFunctions);
	OffsetExportFunctions = ExecutableRVAToOffset(pContext, SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryAddressOfFunctions));
	OffsetExportOrdinals  = ExecutableRVAToOffset(pContext, SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryAddressOfNameOrdinals));
	OffsetExportNames     = ExecutableRVAToOffset(pContext, SDFReadUInt32(THIS->hExportDirectory, PEExportDirectoryAddressOfNames));

	if (0 != OffsetExportFunctions)
	{
		size = sizeof(uint32_t) * THIS->NumberOfFunctions;
		CHECK_ALLOC(THIS->ExportFunctions = (uint32_t*) calloc(1, size));
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetExportFunctions));
		CHECK_CALL(ReaderRead(pContext->hReader, THIS->ExportFunctions, size));
	}
	if (0 != OffsetExportNames)
	{
		size = sizeof(uint32_t) * THIS->NumberOfNames;
		CHECK_ALLOC(THIS->ExportNames = (uint32_t*) calloc(1, size));
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetExportNames));
		CHECK_CALL(ReaderRead(pContext->hReader, THIS->ExportNames, size));
	}
	if (0 != OffsetExportOrdinals)
	{
		size = sizeof(uint16_t) * THIS->NumberOfNames;
		CHECK_ALLOC(THIS->ExportOrdinals = (uint16_t*) calloc(1, size));
		CHECK_CALL(ReaderSeek(pContext->hReader, OffsetExportOrdinals));
		CHECK_CALL(ReaderRead(pContext->hReader, THIS->ExportOrdinals, size));
	}
	CHECK_ALLOC(pContext->pObjects[pContext->iObject].pExports = calloc(1, sizeof(ExecutableSymbol) * THIS->NumberOfFunctions));
	pContext->pObjects[pContext->iObject].nExports = THIS->NumberOfFunctions;

	for (i = 0; i < THIS->NumberOfFunctions; ++i)
	{
		uint32_t address = ExecutableRVAToOffset(pContext, THIS->ExportFunctions[i]);
        if (0 != address)
        {
			uint32_t Name = NameForOrdinal(pContext, i);
			if (0 != Name)
			{
				name = FetchString(pContext, Name);
				pContext->pObjects[pContext->iObject].pExports[i].Name = Name;
			}
        }

		pContext->pObjects[pContext->iObject].pExports[i].Address = address;
		pContext->pObjects[pContext->iObject].pExports[i].Ordinal = i;

		/* Forwarder RVA (within Export Directory) */
		if (THIS->OffsetExport <= address && address + sizeof(uint32_t) <= THIS->OffsetExport + THIS->SizeExport)
		{
			char * forwarder = FetchString(pContext, address);
            ConsoleIOPrintFormatted("[0x%04X] 0x%08X \"%s\" -> \"%s\"\n", i, address, name ? name : "(null)", forwarder);
			free(forwarder);

			pContext->pObjects[pContext->iObject].pExports[i].Forwarder = address;
		}
		else
		{
            ConsoleIOPrintFormatted("[0x%04X] 0x%08X \"%s\"\n", i, address, name ? name : "(null)");
		}
		free(name);
		name = NULL;
	}
	return 1;
}

int PEFileProcessDirectoryImport(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t offset = ExecutableRVAToOffset(pContext, pDirectory->VirtualAddress);
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
		CHECK_CALL(ReaderSeek(pContext->hReader, offset + pos));
		hImportDescriptor = SDFCreate(PEImportDescriptor, pContext->hReader);
		OriginalFirstThunk = SDFReadUInt32(hImportDescriptor, PEImportDescriptorOriginalFirstThunk);
		if (0 == OriginalFirstThunk)
		{
            SDFDestroy(hImportDescriptor);
			break;
		}
		SDFPrint(hImportDescriptor);
		address = ExecutableRVAToOffset(pContext, SDFReadUInt32(hImportDescriptor, PEImportDescriptorName));
		name = FetchString(pContext, address);
		ConsoleIOPrintFormatted("Import %s\n", name ? name : "");
		free(name);
		address = ExecutableRVAToOffset(pContext, OriginalFirstThunk);
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
					ConsoleIOPrintFormatted("ordinal 0x%08lX\n", element & ~0x80000000UL);
				}
				else
				{
					uint16_t hint = 0;
					uint32_t ptr = ExecutableRVAToOffset(pContext, element);
					if (0 != ptr)
                    {
                        ReaderSeek(pContext->hReader, ptr);
					    ReaderRead(pContext->hReader, &hint, sizeof(uint16_t));
					    name = FetchString(pContext, ptr + sizeof(uint16_t));
					    ConsoleIOPrintFormatted("0x%04X %s\n", hint, name);
					    free(name);
                    }
                    else
                    {
                        ConsoleIOPrintFormatted("0x%04X\n", hint);
                    }
				}
			}
			ConsoleIOPrint("\n");
		}
		SDFDestroy(hImportDescriptor);
		pos += SDFSizeInBytes(PEImportDescriptor);
	}
	return 1;
}

int PEFileProcessDirectoryDebug(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t offset = ExecutableRVAToOffset(pContext, pDirectory->VirtualAddress);
	if (0 == offset)
	{
		return 0;
	}
	if (pDirectory->Size < SDFSizeInBytes(PEDebugDirectory))
	{
		return 0;
	}
	CHECK_CALL(ReaderSeek(pContext->hReader, offset));
	CHECK_CALL(THIS->hDebugDirectory = SDFCreate(PEDebugDirectory, pContext->hReader));
	SDFPrint(THIS->hDebugDirectory);
	return 1;
}

int PEFileProcessDirectoryLoadConfig(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t size = 0;
	uint32_t offset = ExecutableRVAToOffset(pContext, pDirectory->VirtualAddress);
	if (0 == offset)
	{
		return 0;
	}
	CHECK_CALL(ReaderSeek(pContext->hReader, offset));
	CHECK_CALL(ReaderRead(pContext->hReader, &size, sizeof(uint32_t)));
	if (size < SDFSizeInBytes(PELoadConfigDirectory))
	{
		return 0;
	}
	CHECK_CALL(THIS->hLoadConfigDirectory = SDFCreate(PELoadConfigDirectory, pContext->hReader));
	SDFPrint(THIS->hLoadConfigDirectory);
	return 1;
}

void PEFileProcessDirectory(ExecutableContext * pContext, uint32_t index)
{
	switch (index)
	{
	case 0x00: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_EXPORT        \n"); break;
	case 0x01: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_IMPORT        \n"); break;
	case 0x02: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_RESOURCE      \n"); break;
	case 0x03: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_EXCEPTION     \n"); break;
	case 0x04: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_SECURITY      \n"); break;
	case 0x05: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_BASERELOC     \n"); break;
	case 0x06: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_DEBUG         \n"); break;
	case 0x07: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_ARCHITECTURE  \n"); break;
	case 0x08: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_GLOBALPTR     \n"); break;
	case 0x09: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_TLS           \n"); break;
	case 0x0A: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG   \n"); break;
	case 0x0B: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT  \n"); break;
	case 0x0C: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_IAT           \n"); break;
	case 0x0D: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT  \n"); break;
	case 0x0E: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR\n"); break;
	case 0x0F: ConsoleIOPrint("IMAGE_DIRECTORY_ENTRY_RESERVED      \n"); break;
	default: break;
	}
	ConsoleIOPrintFormatted("Size    : 0x%08X\n" , THIS->DataDirectories[index].Size);
	ConsoleIOPrintFormatted("Address : 0x%08X\n" , THIS->DataDirectories[index].VirtualAddress);

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
	ConsoleIOPrint("\n");
}

void PEFileDestroy(ExecutableContext * pContext)
{
	SDFDestroy(THIS->hDOSHeader);
	SDFDestroy(THIS->hFileHeader);
	SDFDestroy(THIS->hOptionalHeader);
    SDFDestroy(THIS->hOptionalHeaderExtra);
	SDFDestroy(THIS->hExportDirectory);
	SDFDestroy(THIS->hDebugDirectory);
	SDFDestroy(THIS->hLoadConfigDirectory);
	free(THIS->ExportFunctions);
	free(THIS->ExportNames);
	free(THIS->ExportOrdinals);
	free(THIS->DataDirectories);
	free(THIS);
}

int PEFileOpen(ExecutableContext * pContext)
{
	uint32_t Signature;
	uint16_t Machine;

	CHECK_CALL(ReaderSeek(pContext->hReader, 0));
	CHECK_CALL(THIS->hDOSHeader = SDFCreate(MZDOSHeader, pContext->hReader));
	if (kMZDOSSignature != SDFReadUInt16(THIS->hDOSHeader, MZDOSHeaderSignature))
	{
		return 0;
	}
	THIS->AddressPE = SDFReadUInt32(THIS->hDOSHeader, MZDOSHeaderAddressNew);
	CHECK_CALL(ReaderSeek(pContext->hReader, THIS->AddressPE));
	CHECK_CALL(ReaderRead(pContext->hReader, &Signature, sizeof(uint32_t)));
	if (kPESignature != Signature)
	{
		return 0;
	}
	CHECK_CALL(THIS->hFileHeader = SDFCreate(PEFileHeader, pContext->hReader));
	SDFPrint(THIS->hDOSHeader);
	SDFPrint(THIS->hFileHeader);
	
	CHECK_ALLOC(pContext->pObjects = (ExecutableObject*) calloc(1, sizeof(ExecutableObject)));
	pContext->iObject = 0;
	pContext->nObjects = 1;

	Machine = SDFReadUInt16(THIS->hFileHeader, PEFileHeaderMachine);
	switch (Machine)
	{
	case kPEMachineX86: pContext->pObjects[pContext->iObject].Arch = ArchX86; break;
	case kPEMachineX64: pContext->pObjects[pContext->iObject].Arch = ArchX64; break;
	default: pContext->pObjects[pContext->iObject].Arch = ArchUnknown; break;
	}
	pContext->pObjects[pContext->iObject].StubEntryPoint = SDFSizeInBytes(MZDOSHeader);
	return 1;
}

int OBJFileOpen(ExecutableContext * pContext)
{
	uint16_t Machine = ArchUnknown;
	if (0 == ReaderSeek(pContext->hReader, 0))
	{
		return 0;
	}
	CHECK_CALL(THIS->hFileHeader = SDFCreate(PEFileHeader, pContext->hReader));
	Machine = SDFReadUInt16(THIS->hFileHeader, PEFileHeaderMachine);
	if (kPEMachineX86 == Machine || kPEMachineX64 == Machine)
	{
		SDFPrint(THIS->hFileHeader);
		CHECK_ALLOC(pContext->pObjects = (ExecutableObject*) calloc(1, sizeof(ExecutableObject)));
		pContext->iObject = 0;
		pContext->nObjects = 1;
		THIS->PointerToSymbolTable = SDFReadUInt32(THIS->hFileHeader, PEFileHeaderPointerToSymbolTable);
		THIS->NumberOfSymbols = SDFReadUInt32(THIS->hFileHeader, PEFileHeaderNumberOfSymbols);
		switch (Machine)
		{
		case kPEMachineX86: pContext->pObjects[pContext->iObject].Arch = ArchX86; break;
		case kPEMachineX64: pContext->pObjects[pContext->iObject].Arch = ArchX64; break;
		default: pContext->pObjects[pContext->iObject].Arch = ArchUnknown; break;
		}
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
		char * buffer = NULL;
		uint32_t size = 0;
		CHECK_CALL(ReaderSeek(pContext->hReader, THIS->PointerToSymbolTable + THIS->NumberOfSymbols * 18));
		CHECK_CALL(ReaderRead(pContext->hReader, &size, sizeof(uint32_t)));
		if (size < sizeof(uint32_t))
		{
			return 0;
		}
		size -= sizeof(uint32_t);
		if (NULL == (buffer = (char*) calloc(1, size)))
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
			ConsoleIOPrintFormatted("%s\n", buffer + i);
		}
		if (0 == ReaderSeek(pContext->hReader, THIS->PointerToSymbolTable))
		{
			free(buffer);
			return 0;
		}
		for (i = 0; i < THIS->NumberOfSymbols; ++i)
		{
			uint8_t Aux = 0;
			uint8_t Class = 0;
			uint32_t Symbol[2] = {0};
			HSDF hSymbols = NULL;

			ReaderRead(pContext->hReader, &Symbol, 8);
			if (0 == Symbol[0])
			{
				ConsoleIOPrintFormatted("%s\n", buffer + Symbol[1] - 4);
			}
			else
			{
				char name[9] = {0};
				memcpy(name, &Symbol, 8);
				ConsoleIOPrintFormatted("%s\n", name);
			}
			
			hSymbols = SDFCreate(COFFSymbolTable, pContext->hReader);
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
	uint32_t PEOptionalHeaderSize = SDFSizeInBytes(PEOptionalHeader);
	uint32_t ExtraSize = 0;
	SizeOfOptionalHeader = SDFReadUInt16(THIS->hFileHeader, PEFileHeaderSizeOfOptionalHeader);

	if (SizeOfOptionalHeader >= PEOptionalHeaderSize)
	{
		/* file has an optional header */
		const SDFElement * Extra = NULL;
		CHECK_CALL(THIS->hOptionalHeader = SDFCreate(PEOptionalHeader, pContext->hReader));
		Magic = SDFReadUInt16(THIS->hOptionalHeader, PEOptionalHeaderMagic);
		if (kPEMagic32 != Magic && kPEMagic64 != Magic)
		{
			return 0;
		}
		THIS->PE64 = kPEMagic64 == Magic;
		SDFPrint(THIS->hOptionalHeader);
		Extra = THIS->PE64 ? PEOptionalHeaderExtra64 : PEOptionalHeaderExtra;
		ExtraSize = SDFSizeInBytes(Extra);
		if (SizeOfOptionalHeader >= PEOptionalHeaderSize + ExtraSize)
		{
			CHECK_CALL(THIS->hOptionalHeaderExtra = SDFCreate(Extra, pContext->hReader));
			SDFPrint(THIS->hOptionalHeaderExtra);
			
			THIS->DataDirectoriesCount = MIN(kPEDataDirectoryCount, (SizeOfOptionalHeader - PEOptionalHeaderSize - ExtraSize / sizeof(PEDataDirectory)));
			THIS->DataDirectoriesCount = MIN(SDFReadUInt32(THIS->hOptionalHeaderExtra, THIS->PE64 ? PEOptionalHeaderExtra64NumberOfRvaAndSizes : PEOptionalHeaderExtraNumberOfRvaAndSizes), THIS->DataDirectoriesCount);

			pContext->pObjects[pContext->iObject].Base = SDFReadUInt32(THIS->hOptionalHeaderExtra, THIS->PE64 ? PEOptionalHeaderExtra64ImageBase : PEOptionalHeaderExtraImageBase);
		}
		else if (0 == THIS->Object)
		{
			return 0;
		}
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
		CHECK_ALLOC(THIS->DataDirectories = (PEDataDirectory*) calloc(1, sizeof(PEDataDirectory) * THIS->DataDirectoriesCount));
		CHECK_CALL(ReaderRead(pContext->hReader, THIS->DataDirectories, sizeof(PEDataDirectory) * THIS->DataDirectoriesCount));
	}
	if (0 == (pContext->pObjects[pContext->iObject].nSections = SDFReadUInt16(THIS->hFileHeader, PEFileHeaderNumberOfSections)))
	{
		return 0;
	}
	CHECK_ALLOC(pContext->pObjects[pContext->iObject].pSections = calloc(1, sizeof(ExecutableSection) * pContext->pObjects[pContext->iObject].nSections));
	CHECK_CALL(ReaderSeek(pContext->hReader, OffsetSectionHeaders));
	for (i = 0; i < pContext->pObjects[pContext->iObject].nSections; ++i)
	{
		HSDF hSectionHeader = NULL;
		CHECK_CALL(hSectionHeader = SDFCreate(PESectionHeader, pContext->hReader));

		pContext->pObjects[pContext->iObject].pSections[i].VirtualAddress = SDFReadUInt32(hSectionHeader, PESectionHeaderVirtualAddress);
		pContext->pObjects[pContext->iObject].pSections[i].FileAddress    = SDFReadUInt32(hSectionHeader, PESectionHeaderPointerToRawData);
		pContext->pObjects[pContext->iObject].pSections[i].FileSize       =
		pContext->pObjects[pContext->iObject].pSections[i].VirtualSize    = SDFReadUInt32(hSectionHeader, PESectionHeaderSizeOfRawData);

		SDFPrint(hSectionHeader);
		SDFDestroy(hSectionHeader);
	}
	for (i = 0; i < THIS->DataDirectoriesCount; ++i)
	{
		PEFileProcessDirectory(pContext, i);
	}
	if (0 == THIS->Object)
	{
		pContext->pObjects[pContext->iObject].EntryPoint = ExecutableRVAToOffset(pContext, SDFReadUInt32(THIS->hOptionalHeader, PEOptionalHeaderAddressOfEntryPoint));
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
		ConsoleIOPrintFormatted("%c", c);
	}
	ConsoleIOPrint("\n");
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
		ConsoleIOPrintFormatted("Offset : 0x%08X\n", Offset);
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
		ConsoleIOPrintFormatted("Offset : 0x%08X\n", Offset);
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
		ConsoleIOPrintFormatted("0x%02X 0x%02X\n", Index1, Index2);
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
	CHECK_ALLOC(pContext->pPrivate = calloc(1, sizeof(PEFileContext)));

	if (0 == PEFileOpen(pContext) && 0 == OBJFileOpen(pContext) && 0 == LIBFileOpen(pContext))
	{
		PEFileDestroy(pContext);
		return 0;
	}
	if (0 == PEFileInit(pContext))
	{
		PEFileDestroy(pContext);
		return 0;
	};
	pContext->pDestroy = PEFileDestroy;
	
	return 1;
}
