/*
 * Filename: PEString.c
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: PE file structures 
 *              string representation
 *
 *
 */

#include "../../DisAsm/DisAsm"
#include "../Executable"
#include "PEString.h"

char * UTC(uint32_t TimeStamp)
{
	time_t time = TimeStamp;
	char * c = ctime(&time);
	c[strlen(c) - 1] = 0;
	return c;
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

char * PECharacteristicsToString(uint16_t Characteristics)
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

char * PEDllCharacteristicsToString(uint16_t Characteristics)
{
	char * result = malloc(1024);
	result[0] = 0;
	if (Characteristics & 0x0001) strcat(result, "IMAGE_LIBRARY_PROCESS_INIT ");
	if (Characteristics & 0x0002) strcat(result, "IMAGE_LIBRARY_PROCESS_TERM ");
	if (Characteristics & 0x0004) strcat(result, "IMAGE_LIBRARY_THREAD_INIT ");
	if (Characteristics & 0x0008) strcat(result, "IMAGE_LIBRARY_THREAD_TERM ");
	if (Characteristics & 0x0010) strcat(result, "IMAGE_DLLCHARACTERISTICS_10h ");
	if (Characteristics & 0x0020) strcat(result, "IMAGE_DLLCHARACTERISTICS_20h ");
	if (Characteristics & 0x0040) strcat(result, "IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE ");
	if (Characteristics & 0x0080) strcat(result, "IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY ");
	if (Characteristics & 0x0100) strcat(result, "IMAGE_DLLCHARACTERISTICS_NX_COMPAT ");
	if (Characteristics & 0x0200) strcat(result, "IMAGE_DLLCHARACTERISTICS_NO_ISOLATION ");
	if (Characteristics & 0x0400) strcat(result, "IMAGE_DLLCHARACTERISTICS_NO_SEH ");
	if (Characteristics & 0x0800) strcat(result, "IMAGE_DLLCHARACTERISTICS_NO_BIND ");
	if (Characteristics & 0x1000) strcat(result, "IMAGE_DLLCHARACTERISTICS_1000h ");
	if (Characteristics & 0x2000) strcat(result, "IMAGE_DLLCHARACTERISTICS_WDM_DRIVER ");
	if (Characteristics & 0x4000) strcat(result, "IMAGE_DLLCHARACTERISTICS_4000h ");
	if (Characteristics & 0x8000) strcat(result, "IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE ");
	return result;
}

char * PESectionCharacteristicsToString(uint32_t Characteristics)
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

char * PESubsystemToString(uint16_t Subsystem)
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

char * PEMachineToString(uint16_t Machine)
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

char * PEMagicToString(uint16_t Magic)
{
	switch (Magic)
	{
	case 0x010B: return "IMAGE_NT_OPTIONAL_HDR32_MAGIC";
	case 0x020B: return "IMAGE_NT_OPTIONAL_HDR64_MAGIC";
	case 0x0107: return "IMAGE_ROM_OPTIONAL_HDR_MAGIC";
	default: return "?";
	}
}

char * PEDebugTypeToString(uint32_t Type)
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

void PEPrintDebugDirectory(PEDebugDirectory * pDebugDirectory)
{
	printf("Debug Directory :\n");
	printf("Characteristics     : %d\n",          pDebugDirectory->Characteristics);
	printf("TimeDateStamp       : 0x%08X (%s)\n", pDebugDirectory->TimeDateStamp, UTC(pDebugDirectory->TimeDateStamp));
	printf("Major Version       : %d\n",          pDebugDirectory->MajorVersion);
	printf("Minor Version       : %d\n",          pDebugDirectory->MinorVersion);
	printf("Type                : 0x%08X (%s)\n", pDebugDirectory->Type, PEDebugTypeToString(pDebugDirectory->Type));
	printf("Size Of Data        : 0x%08X\n",      pDebugDirectory->SizeOfData);
	printf("Address Of Raw Data : 0x%08X\n",      pDebugDirectory->AddressOfRawData);
	printf("Pointer To Raw Data : 0x%08X\n",      pDebugDirectory->PointerToRawData);
}

void PEPrintLoadConfigDirectory(PELoadConfigDirectory * pLoadConfigDirectory)
{
	printf("Load Config Directory :\n");
	printf("Size                             : %d\n",          pLoadConfigDirectory->Size);
	printf("Time Date Stamp                  : 0x%08X (%s)\n", pLoadConfigDirectory->TimeDateStamp, UTC(pLoadConfigDirectory->TimeDateStamp));
	printf("Major Version                    : %d\n",          pLoadConfigDirectory->MajorVersion);
	printf("Minor Version                    : %d\n",          pLoadConfigDirectory->MinorVersion);
	printf("Global Flags Clear               : 0x%08X\n",      pLoadConfigDirectory->GlobalFlagsClear);
	printf("Global Flags Set                 : 0x%08X\n",      pLoadConfigDirectory->GlobalFlagsSet);
	printf("Critical Section Default Timeout : %d\n",          pLoadConfigDirectory->CriticalSectionDefaultTimeout);
	printf("DeCommit Free Block Threshold    : %d\n",          pLoadConfigDirectory->DeCommitFreeBlockThreshold);
	printf("DeCommit Total Free Threshold    : %d\n",          pLoadConfigDirectory->DeCommitTotalFreeThreshold);
	printf("Lock Prefix Table                : 0x%08X\n",      pLoadConfigDirectory->LockPrefixTable);
	printf("Maximum Allocation Size          : %d\n",          pLoadConfigDirectory->MaximumAllocationSize);
	printf("Virtual Memory Threshold         : %d\n",          pLoadConfigDirectory->VirtualMemoryThreshold);
	printf("Process Heap Flags               : 0x%08X\n",      pLoadConfigDirectory->ProcessHeapFlags);
	printf("Process Affinity Mask            : 0x%08X\n",      pLoadConfigDirectory->ProcessAffinityMask);
	printf("CSD Version                      : %d\n",          pLoadConfigDirectory->CSDVersion);
	printf("Reserved                         : %d\n",          pLoadConfigDirectory->Reserved);
	printf("EditList                         : %d\n",          pLoadConfigDirectory->EditList);
	printf("Security Cookie                  : 0x%08X\n",      pLoadConfigDirectory->SecurityCookie);
	printf("SEHandler Table                  : 0x%08X\n",      pLoadConfigDirectory->SEHandlerTable);
	printf("SEHandler Count                  : %d\n",          pLoadConfigDirectory->SEHandlerCount);
	printf("\n");
}

void PEPrintExportDirectory(PEExportDirectory * pExportDirectory)
{
	printf("Export Directory :\n");
	printf("Characteristics         : 0x%08X\n",      pExportDirectory->Characteristics);
	printf("Time Date Stamp         : 0x%08X (%s)\n", pExportDirectory->TimeDateStamp, UTC(pExportDirectory->TimeDateStamp));
	printf("Major Version           : %d\n",          pExportDirectory->MajorVersion);
	printf("Minor Version           : %d\n",          pExportDirectory->MinorVersion);
	printf("Name                    : 0x%08X\n",      pExportDirectory->Name);
	printf("Base                    : 0x%08X\n",      pExportDirectory->Base);
	printf("Number Of Functions     : %d\n",          pExportDirectory->NumberOfFunctions);
	printf("Number Of Names         : %d\n",          pExportDirectory->NumberOfNames);
	printf("Address Of Functions    : 0x%08X\n",      pExportDirectory->AddressOfFunctions);
	printf("Address Of Names        : 0x%08X\n",      pExportDirectory->AddressOfNames);
	printf("Address Of NameOrdinals : 0x%08X\n",      pExportDirectory->AddressOfNameOrdinals);
	printf("\n");
}

void PEPrintDOSHeader(PEDOSHeader * pDOSHeader)
{
	printf("MS DOS Header : \n");
	printf("Signature          : ");        PrintSignature(pDOSHeader->Signature, 2);
	printf("Bytes In Last Page : %d\n",     pDOSHeader->BytesInLastPage);
	printf("Pages              : %d\n",     pDOSHeader->Pages);
	printf("Relocations        : %d\n",     pDOSHeader->Relocations);
	printf("Paragraphs         : %d\n",     pDOSHeader->Paragraphs);
	printf("ParagraphsMin      : %d\n",     pDOSHeader->ParagraphsMin);
	printf("ParagraphsMax      : %d\n",     pDOSHeader->ParagraphsMax);
	printf("Initial SS         : 0x%04X\n", pDOSHeader->InitialSS);
	printf("Initial SP         : 0x%04X\n", pDOSHeader->InitialSP);
	printf("Check Sum          : 0x%04X\n", pDOSHeader->CheckSum);
	printf("Initial IP         : 0x%04X\n", pDOSHeader->InitialIP);
	printf("Initial CS         : 0x%04X\n", pDOSHeader->InitialCS);
	printf("Address Relocation : 0x%04X\n", pDOSHeader->AddressRelocation);
	printf("Overlay Number     : %d\n",     pDOSHeader->OverlayNumber);
	printf("OEM ID             : %d\n",     pDOSHeader->OEMID);
	printf("OEM Info           : %d\n",     pDOSHeader->OEMInfo);
	printf("Address PE         : 0x%08X\n", pDOSHeader->AddressPE);
	printf("\n");
}

void PEPrintSectionHeader(PESectionHeader * pSectionHeader)
{
	char * Characteristics = PESectionCharacteristicsToString(pSectionHeader->Characteristics);
	char name[9] = {0};
	memcpy(name, pSectionHeader->Name, 8);
	printf("Section Header :\n");
	printf("Name                    : %s\n",          name);
	printf("Physical Address        : 0x%08X\n",      pSectionHeader->PhysicalAddress);
	printf("Virtual Address         : 0x%08X\n",      pSectionHeader->VirtualAddress);
	printf("Size Of Raw Data        : 0x%08X\n",      pSectionHeader->SizeOfRawData);
	printf("Pointer To Raw Data     : 0x%08X\n",      pSectionHeader->PointerToRawData);
	printf("Pointer To Relocations  : 0x%08X\n",      pSectionHeader->PointerToRelocations);
	printf("Pointer To Line Numbers : 0x%08X\n",      pSectionHeader->PointerToLinenumbers);
	printf("Number Of Relocations   : %d\n",          pSectionHeader->NumberOfRelocations);
	printf("Number Of Line Numbers  : %d\n",          pSectionHeader->NumberOfLinenumbers);
	printf("Characteristics         : 0x%08X (%s)\n", pSectionHeader->Characteristics, Characteristics);
	printf("\n");
	free(Characteristics);
}

void PEPrintOptionalHeader(PEOptionalHeader * pOptionalHeader)
{
	char * Characteristics = PEDllCharacteristicsToString(pOptionalHeader->DllCharacteristics);
	printf("PE Optional Header : \n");
	printf("Magic                          : 0x%04X (%s)\n", pOptionalHeader->Magic, PEMagicToString(pOptionalHeader->Magic));
	printf("Major Linker Version           : %d\n",          pOptionalHeader->MajorLinkerVersion);
	printf("Minor Linker Version           : %d\n",          pOptionalHeader->MinorLinkerVersion);
	printf("Size Of Code                   : 0x%08X\n",      pOptionalHeader->SizeOfCode);
	printf("Size Of Initialized Data       : 0x%08X\n",      pOptionalHeader->SizeOfInitializedData);
	printf("Size Of Uninitialized Data     : 0x%08X\n",      pOptionalHeader->SizeOfUninitializedData);
	printf("Address Of Entry Point         : 0x%08X\n",      pOptionalHeader->AddressOfEntryPoint);
	printf("Base Of Code                   : 0x%08X\n",      pOptionalHeader->BaseOfCode);
	printf("Base Of Data                   : 0x%08X\n",      pOptionalHeader->BaseOfData);
	printf("Image Base                     : 0x%08X\n",      pOptionalHeader->ImageBase);
	printf("Section Alignment              : 0x%08X\n",      pOptionalHeader->SectionAlignment);
	printf("File Alignment                 : 0x%08X\n",      pOptionalHeader->FileAlignment);
	printf("Major Operating System Version : %d\n",          pOptionalHeader->MajorOperatingSystemVersion);
	printf("Minor Operating System Version : %d\n",          pOptionalHeader->MinorOperatingSystemVersion);
	printf("Major Image Version            : %d\n",          pOptionalHeader->MajorImageVersion);
	printf("Minor Image Version            : %d\n",          pOptionalHeader->MinorImageVersion);
	printf("Major Subsystem Version        : %d\n",          pOptionalHeader->MajorSubsystemVersion);
	printf("Minor Subsystem Version        : %d\n",          pOptionalHeader->MinorSubsystemVersion);
	printf("Win32 Version Value            : %d\n",          pOptionalHeader->Win32VersionValue);
	printf("Size Of Image                  : 0x%08X\n",      pOptionalHeader->SizeOfImage);
	printf("Size Of Headers                : 0x%08X\n",      pOptionalHeader->SizeOfHeaders);
	printf("Check Sum                      : 0x%08X\n",      pOptionalHeader->CheckSum);
	printf("Subsystem                      : 0x%04X (%s)\n", pOptionalHeader->Subsystem, PESubsystemToString(pOptionalHeader->Subsystem));
	printf("Dll Characteristics            : 0x%04X (%s)\n", pOptionalHeader->DllCharacteristics, Characteristics);
	printf("Size Of Stack Reserve          : 0x%08X\n",      pOptionalHeader->SizeOfStackReserve);
	printf("Size Of Stack Commit           : 0x%08X\n",      pOptionalHeader->SizeOfStackCommit);
	printf("Size Of Heap Reserve           : 0x%08X\n",      pOptionalHeader->SizeOfHeapReserve);
	printf("Size Of Heap Commit            : 0x%08X\n",      pOptionalHeader->SizeOfHeapCommit);
	printf("Loader Flags                   : 0x%08X\n",      pOptionalHeader->LoaderFlags);
	printf("Number Of Rva And Sizes        : %d\n",          pOptionalHeader->NumberOfRvaAndSizes);
	printf("\n");
	free(Characteristics);
}

void PEPrintFileHeader(PEFileHeader * pFileHeader)
{
	char * Characteristics = PECharacteristicsToString(pFileHeader->Characteristics);
	printf("PE File Header : \n");
	printf("Machine                 : 0x%04X (%s)\n", pFileHeader->Machine, PEMachineToString(pFileHeader->Machine));
	printf("Number Of Sections      : %d\n",          pFileHeader->NumberOfSections);
	printf("Time Date Stamp         : 0x%08X (%s)\n", pFileHeader->TimeDateStamp, UTC(pFileHeader->TimeDateStamp));
	printf("Pointer To Symbol Table : %d\n",          pFileHeader->PointerToSymbolTable);
	printf("Number Of Symbols       : %d\n",          pFileHeader->NumberOfSymbols);
	printf("Size Of Optional Header : 0x%04X\n",      pFileHeader->SizeOfOptionalHeader);
	printf("Characteristics         : 0x%04X (%s)\n", pFileHeader->Characteristics, Characteristics);
	printf("\n");
	free(Characteristics);
}

void PEPrintImportDescriptor(PEImportDescriptor * pImportDescriptor)
{
	printf("Import Descriptor :\n");
	printf("Original First Thunk : 0x%08X\n",      pImportDescriptor->OriginalFirstThunk);
	printf("Time Date Stamp      : 0x%08X (%s)\n", pImportDescriptor->TimeDateStamp, UTC(pImportDescriptor->TimeDateStamp));
	printf("Forwarder Chain      : 0x%08X\n",      pImportDescriptor->ForwarderChain);
	printf("Name                 : 0x%08X\n",      pImportDescriptor->Name);
	printf("First Thunk          : 0x%08X\n",      pImportDescriptor->FirstThunk);
	printf("\n");
}