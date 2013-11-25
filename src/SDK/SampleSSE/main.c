/*
* Filename: main.c
* Author:   DisAsmCompany
* Date:     24/11/2013
*
* Description: the Sample demonstrates how
*              to disassemble code with SSE
*              (Streaming SIMD Extensions)
*              instructions
*/

#include "../../DisAsm/DisAsm"
#include "../../StrAsm/StrAsm"

/* our buffer with RAW x86 machine code (with SSE instructions) */
uint8_t buffer[] = 
{
	/* movaps xmm0, X; */
	0x0F, 0x28, 0x45, 0xC0,
	/* movaps xmm1, Y; */
	0x0F, 0x28, 0x4D, 0x80,
	/* addps xmm0, xmm1; */
	0x0F, 0x58, 0xC1,
	/* addss xmm0, xmm1; */
	0xF3, 0x0F, 0x58, 0xC1,
	/* movaps Z, xmm0; */
	0x0F, 0x29, 0x85, 0x40, 0xFF, 0xFF, 0xFF,

	/* movapd xmm0, X; */
	0x66, 0x0F, 0x28, 0x85, 0x00, 0xFF, 0xFF, 0xFF,
	/* movapd xmm1, Y; */
	0x66, 0x0F, 0x28, 0x8D, 0xC0, 0xFE, 0xFF, 0xFF,
	/* addpd  xmm0, xmm1; */
	0x66, 0x0F, 0x58, 0xC1,
	/* addsd  xmm0, xmm1; */
	0xF2, 0x0F, 0x58, 0xC1,
	/* movapd Z, xmm0; */
	0x66, 0x0F, 0x29, 0x85, 0x80, 0xFE, 0xFF, 0xFF
};

int main()
{
	/* initialize callback reader */
	CallbackReader reader = {0};
	reader.pRead    = CallbackRead;
	reader.pPrivate = &reader;
	reader.buffer = (uint8_t*) buffer;
	reader.offset = 0;
	reader.length = sizeof(buffer);

	ConsoleIOInit();

	for (;;)
	{
		InstructionInfo info;
		if (0 == DisAsmInstructionDecode(32, &reader, &info)) break;
		StrAsmPrintInstruction(&info);
		ConsoleIOPrint("\n");
	}
	return 0;
}
