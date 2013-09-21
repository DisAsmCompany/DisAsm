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

int main(int argc, char * const argv[])
{
	/* let's dissasemble GetVersionEx() API from kernel32.dll */
	unsigned char * buffer = (unsigned char*)GetVersionEx;
	InstructionInfo info = {0};
	int length = 0;
	while (1)
	{
		length = DisAsmInstructionDecode(buffer, &info);
		if (-1 == length)
		{
			break;
		}
		StrAsmPrintInstruction(&info);
		buffer += length;
	}
	return EXIT_SUCCESS;
}
