/*
 * Filename: ConsoleIO.h
 * Author:   DisAsmCompany
 * Date:     16/11/2013
 *
 * Description: console input-output
 *
 *
 *
 */

#pragma once
#ifndef __CONSOLEIO_H__
#define __CONSOLEIO_H__

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

	kBackGroundBlack   = kBlack << 8,
	kBackGroundRed     = kRed << 8,
	kBackGroundGreen   = kGreen << 8,
	kBackGroundBlue    = kBlue << 8,
	kBackGroundYellow  = kYellow << 8,
	kBackGroundMagenta = kMagenta << 8,
	kBackGroundCyan    = kCyan << 8,
	kBackGroundWhite   = kWhite << 8
}
TextColor;

void ConsoleIOInit();
void ConsoleIOPrint(const char * string);
void PrintColoredString(const char * string, TextColor color);
void PrintByte(uint32_t value);
void ConsoleIOPrintFormatted(const char * format, ...);

#endif /* __CONSOLEIO_H__ */
