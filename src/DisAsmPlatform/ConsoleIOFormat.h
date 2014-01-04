/*
 * Filename: ConsoleIOFormat.h
 * Author:   DisAsmCompany
 * Date:     04/01/2014
 *
 * Description: console input-output
 *
 *
 *
 */

/* void ConsoleIOFormat(char * message, uint32_t size, const char * format, ...) */
{
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
			uint32_t width = 0;
			uint32_t precision = 0;
			uint8_t period = 0;
			uint8_t stop = 1;
			uint8_t large = 0;

			do
			{
				char specifier = format[i + 1];
				stop = 1;
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
				case 'c':
					{
						/* char is promoted to int */
						message[j] = (char) va_arg(args, int); ++i; ++j;
					}
					break;
				case 'd':
					{
						uint64_t value = large ? va_arg(args, uint64_t) : va_arg(args, uint32_t);
						++i;
						j += AppendDec(message + j, value, width);
					}
					break;
				case 'l':
				case 'L': stop = 0; large = 1; ++i; break;
				case 's':
					{
						const char * value = va_arg(args, const char *);
						xstrcat(message + j, size, value);
						j += xstrlen(value);
						++i;
					}
					break;
				case 'x':
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
		message[j] = 0;
	}
	va_end(args);
}
