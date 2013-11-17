/*
 * Filename: ConsoleIO.c
 * Author:   DisAsmCompany
 * Date:     16/11/2013
 *
 * Description: console input-output
 *
 *
 *
 */

#include "DisAsm"

uint8_t g_isConsoleStdOut = 0;
uint8_t g_isConsoleStdErr = 0;

HANDLE g_hStdOut = NULL;
HANDLE g_hStdErr = NULL;

uint32_t xstrlen(const char * str)
{
	uint32_t length = 0;
	if (NULL != str)
	{
		for (; 0 != *str; ++str, ++length);
	}
	return length;
}

void xstrcat(char * dst, uint32_t size, const char * src)
{
	uint32_t sizedst = xstrlen(dst);
	uint32_t sizesrc = xstrlen(src);
	uint32_t remain = sizedst < size ? size - sizedst : 0;
	uint32_t copy = sizesrc > remain ? remain : sizesrc;

	memcpy(dst + sizedst, src, copy);
}

void ConsoleIOInit()
{
	DWORD mode = 0;

	g_isConsoleStdOut = 0 != GetConsoleMode(g_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE), &mode);
	g_isConsoleStdErr = 0 != GetConsoleMode(g_hStdErr = GetStdHandle(STD_ERROR_HANDLE), &mode);
}

enum { DefaultColor = kWhite | kBackGroundWhite };

void ConsoleIOPrintInternal(const char * str, uint32_t length, TextColor color, uint8_t error)
{
	DWORD written = 0;
	HANDLE hConsole = error ? g_hStdErr : g_hStdOut;
	/* check, do we have actual console or redirection to file buffer? */
	if (error ? g_isConsoleStdErr : g_isConsoleStdOut)
	{
		CONSOLE_SCREEN_BUFFER_INFO info = {0};
		WORD attributes = 0;
		/* set custom text color, if necessary */
		if (DefaultColor != color)
		{
			GetConsoleScreenBufferInfo(hConsole, &info);
			attributes |= (color & kRed)   ? FOREGROUND_RED   : 0;
			attributes |= (color & kGreen) ? FOREGROUND_GREEN : 0;
			attributes |= (color & kBlue)  ? FOREGROUND_BLUE  : 0;
			attributes |= FOREGROUND_INTENSITY;
			attributes |= (color & kBackGroundRed)  ? BACKGROUND_RED   : 0;
			attributes |= (color & kBackGroundRed)  ? BACKGROUND_GREEN : 0;
			attributes |= (color & kBackGroundBlue) ? BACKGROUND_BLUE  : 0;
			SetConsoleTextAttribute(hConsole, attributes);
		}
		WriteConsole(hConsole, str, length, &written, NULL);
		/* restore color */
		if (DefaultColor != color)
		{
			SetConsoleTextAttribute(hConsole, info.wAttributes);
		}
	}
	else
	{
		WriteFile(hConsole, str, length, &written, NULL);
	}
}

void ConsoleIOPrint(const char * str)
{
	uint32_t length = xstrlen(str);
	if (length >= 7 && 0 == memcmp(str, "[ERROR]", 7))
	{
		ConsoleIOPrintInternal(str, xstrlen(str), kRed, 1);
		OutputDebugString(str);
	}
	ConsoleIOPrintInternal(str, length, DefaultColor, 0);
}

void PrintColoredString(const char * str, TextColor color)
{
	ConsoleIOPrintInternal(str, xstrlen(str), color, 0);
}

void PrintByte(uint64_t value)
{
	ConsoleIOPrintFormatted("%02LX", value);
}

uint32_t AppendDec(char * buffer, uint64_t value, uint32_t width)
{
	uint32_t length = 0;
	uint32_t i = 0;
	uint32_t divider = 1;
	if (0 == value)
	{
		buffer[0] = '0';
		return 1;
	}
	while (0 != value / divider)
	{
		++length;
		divider *= 10;
	}
	width = width < length ? length : width;
	for (i = length; i < width; ++i)
	{
		buffer[i - length] = '0';
	}
	for (i = 0; i < length; ++i)
	{
		uint32_t divider10 = divider / 10;
		buffer[width - length + i] = (char)((value % divider) / divider10 + '0');
		divider = divider10;
	}
	return width;
}

uint32_t AppendHex(char * buffer, uint64_t value, uint32_t width)
{
	char digits[] = "0123456789ABCDEF";
	uint32_t i = 0;
	uint32_t shift = 0;
	width = 0 == width ? 8 : width;
	shift = (width - 1) * 4;
	for (i = 0; i < width; ++i)
	{
		buffer[i] = digits[(value >> shift) & 0x0F];
		shift -= 4;
	}
	return width;
}

void ConsoleIOPrintFormatted(const char * format, ...)
{
	enum {MaxLength = 4096};
	char message[MaxLength] = {0};
	uint32_t length = xstrlen(format);
	uint32_t i = 0;
	uint32_t j = 0;
	va_list args;

	va_start(args, format);
	for (i = 0; i < length; ++i)
	{
		/* seems like format specifier */
		if (format[i] == '%')
		{
			char specifier = 0;
			uint32_t width = 0;
			uint32_t precision = 0;
			uint8_t period = 0;
			uint8_t stop = 1;
			uint8_t large = 0;

			do
			{
				stop = 1;
				specifier = format[i + 1];
				switch (specifier)
				{
				case '0': case '1': case '2': case '3': case '4':
				case '5': case '6': case '7': case '8': case '9':
					if (period)
					{
						precision = precision * 10 + specifier - '0';
					}
					else
					{
						width = width * 10 + specifier - '0';
					}
					stop = 0;
					++i;
					break;
				case '.': period = 1; ++i; stop = 0; break;
				case '%': message[j] = '%'; ++i; ++j; break;
				case 'c': message[j] = va_arg(args, char); ++i; ++j; break;
				case 'd':
					{
						uint64_t value = large ? va_arg(args, uint64_t) : va_arg(args, uint32_t);
						++i;
						j += AppendDec(message + j, value, width);
					}
					break;
				case 'f':
					{
						/*float value = va_arg(args, float);*/
					}
				case 'l':
				case 'L': stop = 0; large = 1; ++i; break;
				case 's':
					{
						const char * value = va_arg(args, const char *);
						xstrcat(message + j, MaxLength, value);
						j += strlen(value);
						++i;
					}
					break;
				case 'X':
					{
						uint64_t value = large ? va_arg(args, uint64_t) : va_arg(args, uint32_t);
						++i;
						j += AppendHex(message + j, value, width);
					}
					break;
				default: break;
				}
			}
			while (!stop);
		}
		else
		{
			message[j] = format[i];
			++j;
		}
	}
	va_end(args);
	ConsoleIOPrint(message);
}
