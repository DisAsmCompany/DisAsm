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

	kDefaultColor = kWhite
}
TextColor;

uint32_t xstrlen(const char * str);
void xstrcat(char * dst, uint32_t size, const char * src);
uint8_t xisalnum(char c);
uint8_t xstrcmp(const char * str1, const char * str2);
uint8_t xstricmp(const char * str1, const char * str2);
const char * xstrchr(const char * str, char c);

char * ShortName(char * name);

void ConsoleIOInit();
void ConsoleIOPrint(const char * string);
void ConsoleIOPrintFormatted(const char * format, ...);
void ConsoleIOFormat(char * message, uint32_t size, const char * format, ...);
void PrintColoredString(const char * string, TextColor color, TextColor background);
void PrintByte(uint64_t value);

void ConsoleIOPrint(const char * string);
void ConsoleIOPrintFormatted(const char * format, ...);

#if defined(_DEBUG) || defined(DEBUG)
#define DebugPrint ConsoleIOPrint
#define DebugPrintFormatted ConsoleIOPrintFormatted
#else /* defined(_DEBUG) || defined(DEBUG) */
void DebugPrint(const char * string);
void DebugPrintFormatted(const char * format, ...);
#endif /* defined(_DEBUG) || defined(DEBUG) */

#ifdef __cplusplus
extern }
#endif /* __cplusplus */

#endif /* __CONSOLEIO_H__0C1DF73B_6BBE_4CDA_8966_C6E31B0A8A8B__ */
