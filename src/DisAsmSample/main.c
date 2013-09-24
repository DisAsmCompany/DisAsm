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

void DisAsmFunction(uint8_t * buffer)
{
	HDISASM hDisAsm = DisAsmCreate();
	InstructionInfo info = {0};
	uint8_t length = 0;
	while (1)
	{
		length = DisAsmInstructionDecode(hDisAsm, buffer, &info);
		if (0 == length)
		{
			break;
		}
		{
			uint8_t i;
			uint32_t address = (uint32_t) buffer;
			for (i = 0; i < 4; ++i)
			{
				uint8_t value = (address >> (3 - i) * 8) & 0xFF;
				printf("%X%X", value >> 4, value & 0x0F);
			}
			printf(" ");
		}
		{
			uint8_t i;
			for (i = 0; i < length; ++i)
			{
				printf("%X%X ", buffer[i] >> 4, buffer[i] & 0x0F);
			}
			for (i = length; i < 15; ++i)
			{
				printf("   ");
			}
		}
		StrAsmPrintInstruction(&info);
		buffer += length;

		if (RET == info.mnemonic)
		{
			break;
		}
	}
	DisAsmDestroy(hDisAsm);
}

int main(int argc, char * const argv[])
{
	/* let's dissasemble GetVersionEx() API from kernel32.dll */
	
	{
		//HEXECUTABLE hExecutable = ExecutableCreateFromFile("C:\\Windows\\System32\\kernel32.dll");
		HMODULE hModule = LoadLibraryA("gdi32.dll");
		HEXECUTABLE hExecutable = ExecutableCreateFromMemory((uint8_t*)hModule);
		uint8_t * ptr = NULL;
		if (!hExecutable)
		{
			return EXIT_FAILURE;
		}
		for (;;)
		{
			ptr = ExecutableGetNextFunction(hExecutable);
			if (NULL == ptr)
			{
				break;
			}
			DisAsmFunction(ptr);
		}

		ExecutableDestroy(hExecutable);
		FreeLibrary(hModule);
	}
	
	return EXIT_SUCCESS;
}
