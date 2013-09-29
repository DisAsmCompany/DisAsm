/*
* Filename: main.c
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: main test file to run simple sample
*              in order to demonstrate library
*              usage and capabilities
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "../DisAsm/DisAsm"
#include "../StrAsm/StrAsm"
#include "../Executable/Executable"

void DisAsmFunction(HREADER hReader, HBENCHMARK hBenchmark, uint32_t address)
{
	HDISASM hDisAsm = DisAsmCreate();
	InstructionInfo info = {0};
	uint8_t length = 0;
	while (1)
	{
		BenchmarkSampleBegin(hBenchmark);
		length = DisAsmInstructionDecode(hDisAsm, hReader, &info);
		BenchmarkSampleEnd(hBenchmark);
		if (0 == length)
		{
			printf("[ERROR] cannot decode opcode 0x%08X\n", info.opcode);
			break;
		}
		{
			uint8_t i;
			for (i = 0; i < 4; ++i)
			{
				uint8_t value = (address >> (3 - i) * 8) & 0xFF;
				printf("%X%X", value >> 4, value & 0x0F);
			}
			printf(" ");
		}
		StrAsmPrintInstruction(&info);

		address += length;

		if (JO <= info.mnemonic && info.mnemonic <= JG)
		{
			// conditional jump
			//break;
		}
		if (JMP == info.mnemonic)
		{
			// non-conditional jump
			//break;
		}
		if (RET == info.mnemonic)
		{
			break;
		}
	}
	DisAsmDestroy(hDisAsm);
}

int main(int argc, char * const argv[])
{
	uint32_t base = 0;
	HBENCHMARK hBenchmark = BenchmarkCreate();
	HREADER hReader = NULL;
	HEXECUTABLE hExecutable = NULL;
	uint32_t count = 0;
	uint32_t i = 0;
	uint8_t memory = 0;

	if (argc < 2)
	{
		fprintf(stderr, "[ERROR] usage : DisAsmSample <file>\n");
		return EXIT_FAILURE;
	}
	if (argc >= 3)
	{
		if (0 == strcmp(argv[2], "memory"))
		{
			memory = 1;
		}
	}
	if (memory)
	{
		base = LoadLibraryA(argv[1]);
		hReader = MemoryReaderCreate(base, 0);
	}
	else
	{
		hReader = FileReaderCreate(argv[1]);
	}
	if (NULL == hReader)
	{
		fprintf(stderr, "[ERROR] cannot open input file \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}
	hExecutable = ExecutableCreate(hReader, memory);
	if (NULL == hExecutable)
	{
		fprintf(stderr, "[ERROR] cannot open executable file \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}
	count = ExecutableGetExportFunctionCount(hExecutable);
	for (i = 0; i < count; ++i)
	{
		char * name = ExecutableGetExportFunctionName(hExecutable, i);
		char * forwarder = ExecutableGetExportForwarderName(hExecutable, i);
		uint32_t address = ExecutableGetExportFunctionAddress(hExecutable, i);
		if (NULL != forwarder)
		{
			printf("%s -> %s\n", name, forwarder);
		}
		else
		{
			printf("%s\n", name);
			ReaderSeek(hReader, address);
			DisAsmFunction(hReader, hBenchmark, address + base);
		}
		printf("\n");
		free(name);
		free(forwarder);
	}
	ExecutableDestroy(hExecutable);
	ReaderDestroy(hReader);
	BenchmarkPrintData(hBenchmark);
	BenchmarkDestroy(hBenchmark);
	return EXIT_SUCCESS;
}
