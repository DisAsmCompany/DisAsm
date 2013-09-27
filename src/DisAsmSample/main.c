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
	HREADER hReader = FileReaderCreate("C:\\Windows\\System32\\kernel32.dll");
	//uint32_t module = LoadLibraryA("kernel32.dll");
	//HREADER hReader = MemoryReaderCreate(module, 0);
	HEXECUTABLE hExecutable = ExecutableCreate(hReader, 1);
	uint32_t address = 0;
	if (!hExecutable)
	{
		return EXIT_FAILURE;
	}
	for (;;)
	{
		address = ExecutableGetNextFunction(hExecutable);
		if (0 == address)
		{
			break;
		}
		ReaderSeek(hReader, address);
		DisAsmFunction(hReader, hBenchmark, address + base);
	}
	ExecutableDestroy(hExecutable);
	ReaderDestroy(hReader);
	BenchmarkPrintData(hBenchmark);
	BenchmarkDestroy(hBenchmark);
	return EXIT_SUCCESS;
}
