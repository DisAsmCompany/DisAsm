/*
* Filename: StrAsm.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: StrAsm API declaration :	
*              convert instruction to
*              string representation
*
*/

typedef enum TextColor_t
{
	kBlack   = 0x00,
	kRed     = 0x01,
	kGreen   = 0x02,
	kBlue    = 0x04,
	kYellow  = kRed | kGreen,
	kMagenta = kRed | kBlue,
	kCyan    = kGreen | kBlue,
	kWhite   = kRed | kGreen | kBlue,
}
TextColor;

void PrintError(const char * string);
void PrintString(const char * string, TextColor color);
void StrAsmPrintInstruction(InstructionInfo * info);
