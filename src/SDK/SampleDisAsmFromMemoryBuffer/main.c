/*
* Filename: main.c
* Author:   DisAsmCompany
* Date:     23/11/2013
*
* Description: Sample DisAsm from Memory Buffer
*              
*              
*
*/

#include "../../DisAsm/DisAsm"
#include "../../StrAsm/StrAsm"

/* our buffer with RAW x86 machine code */
uint8_t buffer[] = 
{
	0x66, 0x81, 0xe4, 0xfc, 0xff, 0x31, 0xd2, 0x52, 0x68, 0x63, 0x61, 0x6c, 0x63, 0x89, 0xe6, 0x52,
	0x56, 0x64, 0x8b, 0x72, 0x30, 0x8b, 0x76, 0x0c, 0x8b, 0x76, 0x0c, 0xad, 0x8b, 0x30, 0x8b, 0x7e,
	0x18, 0x8b, 0x5f, 0x3c, 0x8b, 0x5c, 0x1f, 0x78, 0x8b, 0x74, 0x1f, 0x20, 0x01, 0xfe, 0x8b, 0x4c,
	0x1f, 0x24, 0x01, 0xf9, 0x0f, 0xb7, 0x2c, 0x51, 0x42, 0xad, 0x81, 0x3c, 0x07, 0x57, 0x69, 0x6e,
	0x45, 0x75, 0xf1, 0x8b, 0x74, 0x1f, 0x1c, 0x01, 0xfe, 0x03, 0x3c, 0xae, 0xff, 0xd7, 0xcc
};

int main()
{
	/* initialize callback reader */
	CallbackReader reader = {0};
	reader.context.pRead    = CallbackRead;
	reader.context.pPrivate = &reader;
	reader.buffer = (uint8_t*) buffer;
	reader.offset = 0;
	reader.length = sizeof(buffer);

	ConsoleIOInit();

	for (;;)
	{
		InstructionInfo info;
		uint8_t length = DisAsmInstructionDecode(32, &reader, &info);
		if (0 == length) break;
		StrAsmPrintInstruction(&info);
		ConsoleIOPrint("\n");
	}
	return 0;
}
