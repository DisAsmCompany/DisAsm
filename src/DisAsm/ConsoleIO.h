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
#ifndef __CONSOLEIO_H__0C1DF73B_6BBE_4CDA_8966_C6E31B0A8A8B__
#define __CONSOLEIO_H__0C1DF73B_6BBE_4CDA_8966_C6E31B0A8A8B__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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
	kBackGroundWhite   = kWhite << 8,

	kDefaultColor = kWhite | kBackGroundWhite
}
TextColor;

uint32_t xstrlen(const char * str);
void xstrcat(char * dst, uint32_t size, const char * src);

void ConsoleIOInit();
void ConsoleIOPrint(const char * string);
void PrintColoredString(const char * string, TextColor color);
void PrintByte(uint64_t value);
void ConsoleIOPrintFormatted(const char * format, ...);

#ifdef __cplusplus
extern }
#endif /* __cplusplus */

#endif /* __CONSOLEIO_H__0C1DF73B_6BBE_4CDA_8966_C6E31B0A8A8B__ */
