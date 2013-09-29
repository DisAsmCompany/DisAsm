/*
* Filename: Executable.c
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Executable API implementation
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../DisAsm/DisAsm"
#include "Executable"

typedef struct ExecutableContext_t
{
	uint8_t memory;
	HREADER hReader;
	uint32_t index;
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

uint32_t RVAToOffset(ExecutableContext * pContext, uint32_t RVA)
{
	uint32_t offset = 0;
	uint16_t i = 0;
	if (pContext->memory)
	{
		return RVA;
	}
	for (i = 0; i < pContext->FileHeader.NumberOfSections; ++i)
	{
		if (pContext->SectionHeaders[i].VirtualAddress <= RVA && RVA <= pContext->SectionHeaders[i].VirtualAddress + pContext->SectionHeaders[i].SizeOfRawData)
		{
			offset = pContext->SectionHeaders[i].PointerToRawData + RVA - pContext->SectionHeaders[i].VirtualAddress;
			break;
		}
	}
	return offset;
}

void PrintSignature(uint32_t Signature, uint8_t size)
{
	uint8_t i = 0;
	if (size == 2) printf("0x%04X ", Signature);
	if (size == 4) printf("0x%08X ", Signature);
	printf("'");
	for (i = 0; i < size; ++i)
	{
		char byte = (Signature >> (i * 8)) & 0xFF;
		if (('A' <= byte && byte <= 'Z') || ('a' <= byte && byte <= 'z') || ('0' <= byte && byte <= '9'))
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

char * CharacteristicsToString(uint16_t Characteristics)
{
	char * result = malloc(1024);
	result[0] = 0;
	if (Characteristics & 0x0001) strcat(result, "IMAGE_FILE_RELOCS_STRIPPED ");
	if (Characteristics & 0x0002) strcat(result, "IMAGE_FILE_EXECUTABLE_IMAGE ");
	if (Characteristics & 0x0004) strcat(result, "IMAGE_FILE_LINE_NUMS_STRIPPED ");
	if (Characteristics & 0x0008) strcat(result, "IMAGE_FILE_LOCAL_SYMS_STRIPPED ");
	if (Characteristics & 0x0010) strcat(result, "IMAGE_FILE_AGGRESIVE_WS_TRIM ");
	if (Characteristics & 0x0020) strcat(result, "IMAGE_FILE_LARGE_ADDRESS_AWARE ");
	if (Characteristics & 0x0040) strcat(result, "IMAGE_FILE_40h ");
	if (Characteristics & 0x0080) strcat(result, "IMAGE_FILE_BYTES_REVERSED_LO ");
	if (Characteristics & 0x0100) strcat(result, "IMAGE_FILE_32BIT_MACHINE ");
	if (Characteristics & 0x0200) strcat(result, "IMAGE_FILE_DEBUG_STRIPPED ");
	if (Characteristics & 0x0400) strcat(result, "IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP ");
	if (Characteristics & 0x0800) strcat(result, "IMAGE_FILE_NET_RUN_FROM_SWAP ");
	if (Characteristics & 0x1000) strcat(result, "IMAGE_FILE_SYSTEM ");
	if (Characteristics & 0x2000) strcat(result, "IMAGE_FILE_DLL ");
	if (Characteristics & 0x4000) strcat(result, "IMAGE_FILE_UP_SYSTEM_ONLY ");
	if (Characteristics & 0x8000) strcat(result, "IMAGE_FILE_BYTES_REVERSED_HI ");
	return result;
}

char * SectionCharacteristicsToString(uint32_t Characteristics)
{
	char * result = malloc(1024);
	uint32_t align = Characteristics & 0x00F00000UL;
	result[0] = 0;
	if (Characteristics & 0x00000001UL) strcat(result, "IMAGE_SCN_TYPE_DSECT ");
	if (Characteristics & 0x00000002UL) strcat(result, "IMAGE_SCN_TYPE_NOLOAD ");
	if (Characteristics & 0x00000004UL) strcat(result, "IMAGE_SCN_TYPE_GROUP ");
	if (Characteristics & 0x00000008UL) strcat(result, "IMAGE_SCN_TYPE_NO_PAD ");
	if (Characteristics & 0x00000010UL) strcat(result, "IMAGE_SCN_TYPE_COPY ");
	if (Characteristics & 0x00000020UL) strcat(result, "IMAGE_SCN_CNT_CODE ");
	if (Characteristics & 0x00000040UL) strcat(result, "IMAGE_SCN_CNT_INITIALIZED_DATA ");
	if (Characteristics & 0x00000080UL) strcat(result, "IMAGE_SCN_CNT_UNINITIALIZED_DATA ");
	if (Characteristics & 0x00000100UL) strcat(result, "IMAGE_SCN_LNK_OTHER ");
	if (Characteristics & 0x00000200UL) strcat(result, "IMAGE_SCN_LNK_INFO ");
	if (Characteristics & 0x00000400UL) strcat(result, "IMAGE_SCN_TYPE_OVER ");
	if (Characteristics & 0x00000800UL) strcat(result, "IMAGE_SCN_LNK_REMOVE ");
	if (Characteristics & 0x00001000UL) strcat(result, "IMAGE_SCN_LNK_COMDAT ");
	if (Characteristics & 0x00002000UL) strcat(result, "IMAGE_SCN_LNK_2000h ");
	if (Characteristics & 0x00004000UL) strcat(result, "IMAGE_SCN_NO_DEFER_SPEC_EXC ");
	if (Characteristics & 0x00008000UL) strcat(result, "IMAGE_SCN_GPREL ");
	if (Characteristics & 0x00010000UL) strcat(result, "IMAGE_SCN_MEM_SYSHEAP ");
	if (Characteristics & 0x00020000UL) strcat(result, "IMAGE_SCN_MEM_PURGEABLE ");
	if (Characteristics & 0x00040000UL) strcat(result, "IMAGE_SCN_MEM_LOCKED ");
	if (Characteristics & 0x00080000UL) strcat(result, "IMAGE_SCN_MEM_PRELOAD ");
	if (align == 0x00100000UL) strcat(result, "IMAGE_SCN_ALIGN_1BYTES ");
	if (align == 0x00200000UL) strcat(result, "IMAGE_SCN_ALIGN_2BYTES ");
	if (align == 0x00300000UL) strcat(result, "IMAGE_SCN_ALIGN_4BYTES ");
	if (align == 0x00400000UL) strcat(result, "IMAGE_SCN_ALIGN_8BYTES ");
	if (align == 0x00500000UL) strcat(result, "IMAGE_SCN_ALIGN_16BYTES ");
	if (align == 0x00600000UL) strcat(result, "IMAGE_SCN_ALIGN_32BYTES ");
	if (align == 0x00700000UL) strcat(result, "IMAGE_SCN_ALIGN_64BYTES ");
	if (align == 0x00800000UL) strcat(result, "IMAGE_SCN_ALIGN_128BYTES ");
	if (align == 0x00900000UL) strcat(result, "IMAGE_SCN_ALIGN_256BYTES ");
	if (align == 0x00A00000UL) strcat(result, "IMAGE_SCN_ALIGN_512BYTES ");
	if (align == 0x00B00000UL) strcat(result, "IMAGE_SCN_ALIGN_1024BYTES ");
	if (align == 0x00C00000UL) strcat(result, "IMAGE_SCN_ALIGN_2048BYTES ");
	if (align == 0x00D00000UL) strcat(result, "IMAGE_SCN_ALIGN_4096BYTES ");
	if (align == 0x00E00000UL) strcat(result, "IMAGE_SCN_ALIGN_8192BYTES ");
	if (align == 0x00F00000UL) strcat(result, "IMAGE_SCN_ALIGN_16384BYTES ");
	if (Characteristics & 0x01000000UL) strcat(result, "IMAGE_SCN_LNK_NRELOC_OVFL ");
	if (Characteristics & 0x02000000UL) strcat(result, "IMAGE_SCN_MEM_DISCARDABLE ");
	if (Characteristics & 0x04000000UL) strcat(result, "IMAGE_SCN_MEM_NOT_CACHED ");
	if (Characteristics & 0x08000000UL) strcat(result, "IMAGE_SCN_MEM_NOT_PAGED ");
	if (Characteristics & 0x10000000UL) strcat(result, "IMAGE_SCN_MEM_SHARED ");
	if (Characteristics & 0x20000000UL) strcat(result, "IMAGE_SCN_MEM_EXECUTE ");
	if (Characteristics & 0x40000000UL) strcat(result, "IMAGE_SCN_MEM_READ ");
	if (Characteristics & 0x80000000UL) strcat(result, "IMAGE_SCN_MEM_WRITE ");
	return result;
}

char * SubsystemToString(uint16_t Subsystem)
{
	switch (Subsystem)
	{
	case 0x0000: return "IMAGE_SUBSYSTEM_UNKNOWN";
	case 0x0001: return "IMAGE_SUBSYSTEM_NATIVE";
	case 0x0002: return "IMAGE_SUBSYSTEM_WINDOWS_GUI";
	case 0x0003: return "IMAGE_SUBSYSTEM_WINDOWS_CUI";
	case 0x0005: return "IMAGE_SUBSYSTEM_OS2_CUI";
	case 0x0007: return "IMAGE_SUBSYSTEM_POSIX_CUI";
	case 0x0008: return "IMAGE_SUBSYSTEM_NATIVE_WINDOWS";
	case 0x0009: return "IMAGE_SUBSYSTEM_WINDOWS_CE_GUI";
	case 0x000A: return "IMAGE_SUBSYSTEM_EFI_APPLICATION";
	case 0x000B: return "IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER";
	case 0x000C: return "IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER";
	case 0x000D: return "IMAGE_SUBSYSTEM_EFI_ROM";
	case 0x000E: return "IMAGE_SUBSYSTEM_XBOX";
	case 0x0010: return "IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION";
	default: return "?";
	}
}

char * MachineToString(uint16_t Machine)
{
	switch(Machine)
	{
	case 0x014C: return "IMAGE_FILE_MACHINE_I386";
	case 0x0162: return "IMAGE_FILE_MACHINE_R3000";
	case 0x0166: return "IMAGE_FILE_MACHINE_R4000";
	case 0x0168: return "IMAGE_FILE_MACHINE_R10000";
	case 0x0169: return "IMAGE_FILE_MACHINE_WCEMIPSV2";
	case 0x0184: return "IMAGE_FILE_MACHINE_ALPHA";
	case 0x01A2: return "IMAGE_FILE_MACHINE_SH3";
	case 0x01A3: return "IMAGE_FILE_MACHINE_SH3DSP";
	case 0x01A4: return "IMAGE_FILE_MACHINE_SH3E";
	case 0x01A6: return "IMAGE_FILE_MACHINE_SH4";
	case 0x01A8: return "IMAGE_FILE_MACHINE_SH5";
	case 0x01C0: return "IMAGE_FILE_MACHINE_ARM";
	case 0x01C2: return "IMAGE_FILE_MACHINE_THUMB";
	case 0x01D3: return "IMAGE_FILE_MACHINE_AM33";
	case 0x01F0: return "IMAGE_FILE_MACHINE_POWERPC";
	case 0x01F1: return "IMAGE_FILE_MACHINE_POWERPCFP";
	case 0x0200: return "IMAGE_FILE_MACHINE_IA64";
	case 0x0266: return "IMAGE_FILE_MACHINE_MIPS16";
	case 0x0284: return "IMAGE_FILE_MACHINE_ALPHA64";
	case 0x0366: return "IMAGE_FILE_MACHINE_MIPSFPU";
	case 0x0466: return "IMAGE_FILE_MACHINE_MIPSFPU16";
	case 0x0520: return "IMAGE_FILE_MACHINE_TRICORE";
	case 0x0CEF: return "IMAGE_FILE_MACHINE_CEF";
	case 0x0EBC: return "IMAGE_FILE_MACHINE_EBC";
	case 0x8664: return "IMAGE_FILE_MACHINE_AMD64";
	case 0x9041: return "IMAGE_FILE_MACHINE_M32R";
	case 0xC0EE: return "IMAGE_FILE_MACHINE_CEE";
	default: return "?";
	}
}

char * MagicToString(uint16_t Magic)
{
	switch (Magic)
	{
	case 0x010B: return "IMAGE_NT_OPTIONAL_HDR32_MAGIC";
	case 0x020B: return "IMAGE_NT_OPTIONAL_HDR64_MAGIC";
	case 0x0107: return "IMAGE_ROM_OPTIONAL_HDR_MAGIC";
	default: return "?";
	}
}

char * DebugTypeToString(uint32_t Type)
{
	switch (Type)
	{
	case 0x00000000UL: return "IMAGE_DEBUG_TYPE_UNKNOWN";
	case 0x00000001UL: return "IMAGE_DEBUG_TYPE_COFF";
	case 0x00000002UL: return "IMAGE_DEBUG_TYPE_CODEVIEW";
	case 0x00000003UL: return "IMAGE_DEBUG_TYPE_FPO";
	case 0x00000004UL: return "IMAGE_DEBUG_TYPE_MISC";
	case 0x00000005UL: return "IMAGE_DEBUG_TYPE_EXCEPTION";
	case 0x00000006UL: return "IMAGE_DEBUG_TYPE_FIXUP";
	case 0x00000007UL: return "IMAGE_DEBUG_TYPE_OMAP_TO_SRC";
	case 0x00000008UL: return "IMAGE_DEBUG_TYPE_OMAP_FROM_SRC";
	case 0x00000009UL: return "IMAGE_DEBUG_TYPE_BORLAND";
	case 0x0000000AUL: return "IMAGE_DEBUG_TYPE_RESERVED10";
	case 0x0000000BUL: return "IMAGE_DEBUG_TYPE_CLSID";
	default: return "?";
	}
}

char * UTC(uint32_t TimeStamp)
{
	time_t time = TimeStamp;
	char * c = ctime(&time);
	c[strlen(c) - 1] = 0;
	return c;
}

char * FetchString(ExecutableContext * pContext, uint32_t address)
{
	char * buffer = NULL; 
	uint8_t i = 0;
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

int ProcessDirectoryExport(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t i = 0;
	char * name = "";
	pContext->OffsetExport = RVAToOffset(pContext, pDirectory->VirtualAddress);
	pContext->SizeExport = pDirectory->Size;
	if (pDirectory->Size < sizeof(PEExportDirectory))
	{
		return 0;
	}
	if (0 == pContext->OffsetExport)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, pContext->OffsetExport))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &pContext->ExportDirectory, sizeof(PEExportDirectory)))
	{
		return 0;
	}
	if (0 != pContext->ExportDirectory.Name)
	{
		uint32_t ptr = RVAToOffset(pContext, pContext->ExportDirectory.Name);
		if (0 != ptr)
		{
			name = FetchString(pContext, ptr);
		}
	}
	printf("Export Directory :\n");
	printf("Characteristics         : 0x%08X\n", pContext->ExportDirectory.Characteristics);
	printf("Time Date Stamp         : 0x%08X (%s)\n", pContext->ExportDirectory.TimeDateStamp, UTC(pContext->ExportDirectory.TimeDateStamp));
	printf("Major Version           : %d\n", pContext->ExportDirectory.MajorVersion);
	printf("Minor Version           : %d\n", pContext->ExportDirectory.MinorVersion);
	printf("Name                    : 0x%08X (%s)\n", pContext->ExportDirectory.Name, name);
	printf("Base                    : 0x%08X\n", pContext->ExportDirectory.Base);
	printf("Number Of Functions     : %d\n", pContext->ExportDirectory.NumberOfFunctions);
	printf("Number Of Names         : %d\n", pContext->ExportDirectory.NumberOfNames);
	printf("Address Of Functions    : 0x%08X\n", pContext->ExportDirectory.AddressOfFunctions);
	printf("Address Of Names        : 0x%08X\n", pContext->ExportDirectory.AddressOfNames);
	printf("Address Of NameOrdinals : 0x%08X\n", pContext->ExportDirectory.AddressOfNameOrdinals);

	pContext->OffsetExportFunctions = RVAToOffset(pContext, pContext->ExportDirectory.AddressOfFunctions);
	pContext->OffsetExportOrdinals = RVAToOffset(pContext, pContext->ExportDirectory.AddressOfNameOrdinals);
	pContext->OffsetExportNames = RVAToOffset(pContext, pContext->ExportDirectory.AddressOfNames);

	for (i = 0; i < pContext->ExportDirectory.NumberOfFunctions; ++i)
	{
		uint32_t address = 0;
		uint32_t ptr = 0;
		uint32_t j = 0;
		ReaderSeek(pContext->hReader, pContext->OffsetExportFunctions + i * 4);
		ReaderRead(pContext->hReader, &ptr, sizeof(uint32_t));
		address = RVAToOffset(pContext, ptr);

		ReaderSeek(pContext->hReader, pContext->OffsetExportNames + i * sizeof(uint32_t));
		ReaderRead(pContext->hReader, &ptr, sizeof(uint32_t));
		ptr = RVAToOffset(pContext, ptr);

		name = FetchString(pContext, ptr);

		// Forwarder RVA (within Export Directory)
		if (pContext->OffsetExport <= address && address <= pContext->OffsetExport + pContext->SizeExport)
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

int ProcessDirectoryImport(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t offset = RVAToOffset(pContext, pDirectory->VirtualAddress);
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
		address = RVAToOffset(pContext, ImportDescriptor.Name);
		name = FetchString(pContext, address);
		printf("Import Descriptor :\n");
		printf("Original First Thunk : 0x%08X\n", ImportDescriptor.OriginalFirstThunk);
		printf("Time Date Stamp      : 0x%08X (%s)\n", ImportDescriptor.TimeDateStamp, UTC(ImportDescriptor.TimeDateStamp));
		printf("Forwarder Chain      : 0x%08X\n", ImportDescriptor.ForwarderChain);
		printf("Name                 : 0x%08X (%s)\n", ImportDescriptor.Name, name);
		printf("First Thunk          : 0x%08X\n", ImportDescriptor.FirstThunk);
		free(name);

		address = RVAToOffset(pContext, ImportDescriptor.OriginalFirstThunk);
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
					printf("ordinal 0x%08X\n", element & ~0x80000000UL);
				}
				else
				{
					uint16_t hint = 0;
					uint32_t ptr = RVAToOffset(pContext, element);
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

int ProcessDirectoryDebug(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t offset = RVAToOffset(pContext, pDirectory->VirtualAddress);
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
	if (0 == ReaderRead(pContext->hReader, &pContext->DebugDirectory, sizeof(PEDebugDirectory)))
	{
		return 0;
	}
	printf("Debug Directory :\n");
	printf("Characteristics     : %d\n", pContext->DebugDirectory.Characteristics);
	printf("TimeDateStamp       : 0x%08X (%s)\n", pContext->DebugDirectory.TimeDateStamp, UTC(pContext->DebugDirectory.TimeDateStamp));
	printf("Major Version       : %d\n", pContext->DebugDirectory.MajorVersion);
	printf("Minor Version       : %d\n", pContext->DebugDirectory.MinorVersion);
	printf("Type                : 0x%08X (%s)\n", pContext->DebugDirectory.Type, DebugTypeToString(pContext->DebugDirectory.Type));
	printf("Size Of Data        : 0x%08X\n", pContext->DebugDirectory.SizeOfData);
	printf("Address Of Raw Data : 0x%08X\n", pContext->DebugDirectory.AddressOfRawData);
	printf("Pointer To Raw Data : 0x%08X\n", pContext->DebugDirectory.PointerToRawData);
	return 1;
}

int ProcessDirectoryLoadConfig(ExecutableContext * pContext, PEDataDirectory * pDirectory)
{
	uint32_t offset = RVAToOffset(pContext, pDirectory->VirtualAddress);

	if (0 == offset)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, offset))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &pContext->LoadConfigDirectory.Size, sizeof(uint32_t)))
	{
		return 0;
	}
	if (pContext->LoadConfigDirectory.Size < sizeof(PELoadConfigDirectory))
	{
		return 0;
	}
	pContext->LoadConfigDirectory.Size = sizeof(PELoadConfigDirectory);
	if (0 == ReaderRead(pContext->hReader, &pContext->LoadConfigDirectory.TimeDateStamp, pContext->LoadConfigDirectory.Size - sizeof(uint32_t)))
	{
		return 0;
	}
	printf("Load Config Directory :\n");
	printf("Size                             : %d\n", pContext->LoadConfigDirectory.Size);
	printf("Time Date Stamp                  : 0x%08X (%s)\n", pContext->LoadConfigDirectory.TimeDateStamp, UTC(pContext->LoadConfigDirectory.TimeDateStamp));
	printf("Major Version                    : %d\n", pContext->LoadConfigDirectory.MajorVersion);
	printf("Minor Version                    : %d\n", pContext->LoadConfigDirectory.MinorVersion);
	printf("Global Flags Clear               : 0x%08X\n", pContext->LoadConfigDirectory.GlobalFlagsClear);
	printf("Global Flags Set                 : 0x%08X\n", pContext->LoadConfigDirectory.GlobalFlagsSet);
	printf("Critical Section Default Timeout : %d\n", pContext->LoadConfigDirectory.CriticalSectionDefaultTimeout);
	printf("DeCommit Free Block Threshold    : %d\n", pContext->LoadConfigDirectory.DeCommitFreeBlockThreshold);
	printf("DeCommit Total Free Threshold    : %d\n", pContext->LoadConfigDirectory.DeCommitTotalFreeThreshold);
	printf("Lock Prefix Table                : 0x%08X\n", pContext->LoadConfigDirectory.LockPrefixTable);
	printf("Maximum Allocation Size          : %d\n", pContext->LoadConfigDirectory.MaximumAllocationSize);
	printf("Virtual Memory Threshold         : %d\n", pContext->LoadConfigDirectory.VirtualMemoryThreshold);
	printf("Process Heap Flags               : 0x%08X\n", pContext->LoadConfigDirectory.ProcessHeapFlags);
	printf("Process Affinity Mask            : 0x%08X\n", pContext->LoadConfigDirectory.ProcessAffinityMask);
	printf("CSD Version                      : %d\n", pContext->LoadConfigDirectory.CSDVersion);
	printf("Reserved                         : %d\n", pContext->LoadConfigDirectory.Reserved);
	printf("EditList                         : %d\n", pContext->LoadConfigDirectory.EditList);
	printf("Security Cookie                  : %d\n", pContext->LoadConfigDirectory.SecurityCookie);
	printf("SEHandler Table                  : 0x%08X\n", pContext->LoadConfigDirectory.SEHandlerTable);
	printf("SEHandler Count                  : %d\n", pContext->LoadConfigDirectory.SEHandlerCount);
	return 1;
}

void ProcessDirectory(ExecutableContext * pContext, uint32_t index)
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
	printf("Size    : 0x%08X\n" , pContext->DataDirectories[index].Size);
	printf("Address : 0x%08X\n" , pContext->DataDirectories[index].VirtualAddress);

	if (pContext->DataDirectories[index].Size > 0 && pContext->DataDirectories->VirtualAddress > 0)
	{
		switch (index)
		{
		case 0x00: ProcessDirectoryExport    (pContext, &pContext->DataDirectories[index]); break;
		case 0x01: ProcessDirectoryImport    (pContext, &pContext->DataDirectories[index]); break;
		case 0x06: ProcessDirectoryDebug     (pContext, &pContext->DataDirectories[index]); break;
		case 0x0A: ProcessDirectoryLoadConfig(pContext, &pContext->DataDirectories[index]); break;
		default: break;
		}
	}
	printf("\n");
}

int ExecutableInit(ExecutableContext * pContext)
{
	PEDataDirectory * ExportDataDirectory = NULL;
	uint32_t size = 0;
	uint32_t OffsetSectionHeaders = 0;

	pContext->index = 0;
	
	if (0 == ReaderRead(pContext->hReader, &pContext->DOSHeader, sizeof(PEDOSHeader)))
	{
		return 0;
	}
	if (pContext->DOSHeader.Signature != PEDOSSignature)
	{
		return 0;
	}
	{
		uint8_t i = 0;
		printf("MS DOS Header : \n");
		printf("Signature          : "); PrintSignature(pContext->DOSHeader.Signature, 2);
		printf("Bytes In Last Page : %d\n", pContext->DOSHeader.BytesInLastPage);
		printf("Pages              : %d\n", pContext->DOSHeader.Pages);
		printf("Relocations        : %d\n", pContext->DOSHeader.Relocations);
		printf("Paragraphs         : %d\n", pContext->DOSHeader.Paragraphs);
		printf("ParagraphsMin      : %d\n", pContext->DOSHeader.ParagraphsMin);
		printf("ParagraphsMax      : %d\n", pContext->DOSHeader.ParagraphsMax);
		printf("Initial SS         : 0x%04X\n", pContext->DOSHeader.InitialSS);
		printf("Initial SP         : 0x%04X\n", pContext->DOSHeader.InitialSP);
		printf("Check Sum          : 0x%04X\n", pContext->DOSHeader.CheckSum);
		printf("Initial IP         : 0x%04X\n", pContext->DOSHeader.InitialIP);
		printf("Initial CS         : 0x%04X\n", pContext->DOSHeader.InitialCS);
		printf("Address Relocation : 0x%04X\n", pContext->DOSHeader.AddressRelocation);
		printf("Overlay Number     : %d\n", pContext->DOSHeader.OverlayNumber);
		//for (i = 0; i < 4; ++i)
		//printf("Reserved[%d]        : %d\n", i, pContext->DOSHeader.Reserved1[i]);
		printf("OEM ID             : %d\n", pContext->DOSHeader.OEMID);
		printf("OEM Info           : %d\n", pContext->DOSHeader.OEMInfo);
		//for (i = 0; i < 10; ++i)
		//printf("Reserved[%d]        : %d\n", i, pContext->DOSHeader.Reserved2[i]);
		printf("Address PE         : 0x%08X\n", pContext->DOSHeader.AddressPE);
		printf("\n");
	}
	if (0 == ReaderSeek(pContext->hReader, pContext->DOSHeader.AddressPE))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &pContext->Signature, sizeof(uint32_t)))
	{
		return 0;
	}
	if (pContext->Signature != PENTSignature)
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &pContext->FileHeader, sizeof(PEFileHeader)))
	{
		return 0;
	}
	{
		uint8_t i = 0;
		char * Characteristics = CharacteristicsToString(pContext->FileHeader.Characteristics);
		printf("Signature : \n"); PrintSignature(pContext->Signature, 4);

		printf("PE File Header : \n");
		printf("Machine                 : 0x%04X (%s)\n", pContext->FileHeader.Machine, MachineToString(pContext->FileHeader.Machine));
		printf("Number Of Sections      : %d\n", pContext->FileHeader.NumberOfSections);
		printf("Time Date Stamp         : 0x%08X (%s)\n", pContext->FileHeader.TimeDateStamp, UTC(pContext->FileHeader.TimeDateStamp));
		printf("Pointer To Symbol Table : %d\n", pContext->FileHeader.PointerToSymbolTable);
		printf("Number Of Symbols       : %d\n", pContext->FileHeader.NumberOfSymbols);
		printf("Size Of Optional Header : 0x%04X\n", pContext->FileHeader.SizeOfOptionalHeader);
		printf("Characteristics         : 0x%04X (%s)\n", pContext->FileHeader.Characteristics, Characteristics);
		printf("\n");
		free(Characteristics);
	}
	if (pContext->FileHeader.SizeOfOptionalHeader < sizeof(PEOptionalHeader))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &pContext->OptionalHeader, sizeof(PEOptionalHeader)))
	{
		return 0;
	}
	{
		uint8_t i = 0;
		printf("PE Optional Header : \n");
		printf("Magic                          : 0x%04X (%s)\n", pContext->OptionalHeader.Magic, MagicToString(pContext->OptionalHeader.Magic));
		printf("Major Linker Version           : %d\n", pContext->OptionalHeader.MajorLinkerVersion);
		printf("Minor Linker Version           : %d\n", pContext->OptionalHeader.MinorLinkerVersion);
		printf("Size Of Code                   : 0x%08X\n", pContext->OptionalHeader.SizeOfCode);
		printf("Size Of Initialized Data       : 0x%08X\n", pContext->OptionalHeader.SizeOfInitializedData);
		printf("Size Of Uninitialized Data     : 0x%08X\n", pContext->OptionalHeader.SizeOfUninitializedData);
		printf("Address Of Entry Point         : 0x%08X\n", pContext->OptionalHeader.AddressOfEntryPoint);
		printf("Base Of Code                   : 0x%08X\n", pContext->OptionalHeader.BaseOfCode);
		printf("Base Of Data                   : 0x%08X\n", pContext->OptionalHeader.BaseOfData);
		printf("Image Base                     : 0x%08X\n", pContext->OptionalHeader.ImageBase);
		printf("Section Alignment              : 0x%08X\n", pContext->OptionalHeader.SectionAlignment);
		printf("File Alignment                 : 0x%08X\n", pContext->OptionalHeader.FileAlignment);
		printf("Major Operating System Version : %d\n", pContext->OptionalHeader.MajorOperatingSystemVersion);
		printf("Minor Operating System Version : %d\n", pContext->OptionalHeader.MinorOperatingSystemVersion);
		printf("Major Image Version            : %d\n", pContext->OptionalHeader.MajorImageVersion);
		printf("Minor Image Version            : %d\n", pContext->OptionalHeader.MinorImageVersion);
		printf("Major Subsystem Version        : %d\n", pContext->OptionalHeader.MajorSubsystemVersion);
		printf("Minor Subsystem Version        : %d\n", pContext->OptionalHeader.MinorSubsystemVersion);
		printf("Win32 Version Value            : %d\n", pContext->OptionalHeader.Win32VersionValue);
		printf("Size Of Image                  : 0x%08X\n", pContext->OptionalHeader.SizeOfImage);
		printf("Size Of Headers                : 0x%08X\n", pContext->OptionalHeader.SizeOfHeaders);
		printf("Check Sum                      : 0x%08X\n", pContext->OptionalHeader.CheckSum);
		printf("Subsystem                      : 0x%04X (%s)\n", pContext->OptionalHeader.Subsystem, SubsystemToString(pContext->OptionalHeader.Subsystem));
		printf("Dll Characteristics            : 0x%04X\n", pContext->OptionalHeader.DllCharacteristics);
		printf("Size Of Stack Reserve          : 0x%08X\n", pContext->OptionalHeader.SizeOfStackReserve);
		printf("Size Of Stack Commit           : 0x%08X\n", pContext->OptionalHeader.SizeOfStackCommit);
		printf("Size Of Heap Reserve           : 0x%08X\n", pContext->OptionalHeader.SizeOfHeapReserve);
		printf("Size Of Heap Commit            : 0x%08X\n", pContext->OptionalHeader.SizeOfHeapCommit);
		printf("Loader Flags                   : 0x%08X\n", pContext->OptionalHeader.LoaderFlags);
		printf("Number Of Rva And Sizes        : %d\n", pContext->OptionalHeader.NumberOfRvaAndSizes);
		printf("\n");
	}
	OffsetSectionHeaders = pContext->DOSHeader.AddressPE + sizeof(uint32_t) + sizeof(PEFileHeader) + pContext->FileHeader.SizeOfOptionalHeader;
	pContext->DataDirectoriesCount = min(PEDataDirectoryCount, (pContext->FileHeader.SizeOfOptionalHeader - sizeof(PEOptionalHeader)) / sizeof(PEDataDirectory));
	if (pContext->DataDirectoriesCount)
	{
		pContext->DataDirectories = (PEDataDirectory*) malloc(sizeof(PEDataDirectory) * pContext->DataDirectoriesCount);
		if (NULL == pContext->DataDirectories)
		{
			return 0;
		}
	}
	if (pContext->DataDirectoriesCount > 0)
	{
		if (0 == ReaderRead(pContext->hReader, pContext->DataDirectories, sizeof(PEDataDirectory) * pContext->DataDirectoriesCount))
		{
			return 0;
		}
	}
	if (pContext->FileHeader.NumberOfSections == 0)
	{
		return 0;
	}
	size = sizeof(PESectionHeader) * pContext->FileHeader.NumberOfSections;
	pContext->SectionHeaders = (PESectionHeader*) malloc(size);
	if (NULL == pContext->SectionHeaders)
	{
		return 0;
	}
	if (0 == ReaderSeek(pContext->hReader, OffsetSectionHeaders))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, pContext->SectionHeaders, size))
	{
		return 0;
	}
	{
		uint8_t i = 0;
		for (i = 0; i < pContext->FileHeader.NumberOfSections; ++i)
		{
			char * Characteristics = SectionCharacteristicsToString(pContext->SectionHeaders[i].Characteristics);
			char name[9] = {0};
			memcpy(name, pContext->SectionHeaders[i].Name, 8);
			printf("Section[%d] Header :\n", i);
			printf("Name                    : %s\n", name);
			printf("Physical Address        : 0x%08X\n", pContext->SectionHeaders[i].PhysicalAddress);
			printf("Virtual Address         : 0x%08X\n", pContext->SectionHeaders[i].VirtualAddress);
			printf("Size Of Raw Data        : 0x%08X\n", pContext->SectionHeaders[i].SizeOfRawData);
			printf("Pointer To Raw Data     : 0x%08X\n", pContext->SectionHeaders[i].PointerToRawData);
			printf("Pointer To Relocations  : 0x%08X\n", pContext->SectionHeaders[i].PointerToRelocations);
			printf("Pointer To Line Numbers : 0x%08X\n", pContext->SectionHeaders[i].PointerToLinenumbers);
			printf("Number Of Relocations   : %d\n", pContext->SectionHeaders[i].NumberOfRelocations);
			printf("Number Of Line Numbers  : %d\n", pContext->SectionHeaders[i].NumberOfLinenumbers);
			printf("Characteristics         : 0x%08X (%s)\n", pContext->SectionHeaders[i].Characteristics, Characteristics);
			printf("\n");
			free(Characteristics);
		}
	}
	{
		uint8_t i = 0;
		for (i = 0; i < pContext->DataDirectoriesCount; ++i)
		{
			ProcessDirectory(pContext, i);
		}
	}
	return 1;
}

HEXECUTABLE ExecutableCreate(HREADER hReader, int memory)
{
	ExecutableContext * pContext = NULL;

	if (NULL == hReader)
	{
		return NULL;
	}
	pContext = (ExecutableContext*) malloc(sizeof(ExecutableContext));
	if (NULL == pContext)
	{
		return NULL;
	}
	pContext->hReader = hReader;
	pContext->memory = memory;
	ExecutableInit(pContext);
	return (HEXECUTABLE) pContext;
}

void ExecutableDestroy(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	free(pContext->DataDirectories);
	free(pContext->SectionHeaders);
	free(hExecutable);
}

uint32_t ExecutableGetExportFunctionCount(HEXECUTABLE hExecutable)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	return pContext->ExportDirectory.NumberOfFunctions;
}

uint32_t ExecutableGetExportFunctionAddress(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	uint32_t address = 0;

	ReaderSeek(pContext->hReader, pContext->OffsetExportFunctions + index * sizeof(uint32_t));
	ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
	return RVAToOffset(pContext, address);
}

char * ExecutableGetExportFunctionName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	uint32_t address = 0;

	ReaderSeek(pContext->hReader, pContext->OffsetExportNames + index * sizeof(uint32_t));
	ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
	address = RVAToOffset(pContext, address);
	return FetchString(pContext, address);
}

char * ExecutableGetExportForwarderName(HEXECUTABLE hExecutable, uint32_t index)
{
	ExecutableContext * pContext = (ExecutableContext*) hExecutable;
	uint32_t address = 0;

	ReaderSeek(pContext->hReader, pContext->OffsetExportFunctions + index * sizeof(uint32_t));
	ReaderRead(pContext->hReader, &address, sizeof(uint32_t));
	address = RVAToOffset(pContext, address);
	if (pContext->OffsetExport <= address && address <= pContext->OffsetExport + pContext->SizeExport)
	{
		return FetchString(pContext, address);
	}
	return NULL;
}