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
