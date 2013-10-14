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
