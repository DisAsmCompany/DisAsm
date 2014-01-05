/*
 * Filename: SDF.c
 * Author:   DisAsmCompany
 * Date:     09/10/2013
 *
 * Description: SDF (Structure Definition Format)
 *              API declaration.
 *
 *
 */

#include "../DisAsm/DisAsm"
#include "../DisAsmPlatform/DisAsmPlatform"
#include "../StrAsm/StrAsm"
#include "Executable"

typedef struct SDFContext_t
{
	const SDFElement * definition;
	uint8_t * data;
	uint8_t endian;
}
SDFContext;

uint64_t LE2BE64(uint64_t value)
{
    return 
        ((value & U64(0x00000000000000FF)) << 56) |
        ((value & U64(0x000000000000FF00)) << 40) |
        ((value & U64(0x0000000000FF0000)) >> 24) |
        ((value & U64(0x00000000FF000000)) >> 8)  |
        ((value & U64(0x000000FF00000000)) << 8)  |
        ((value & U64(0x0000FF0000000000)) << 24) |
        ((value & U64(0x00FF000000000000)) >> 40) |
        ((value & U64(0xFF00000000000000)) >> 56);
}

uint32_t LE2BE32(uint32_t value)
{
	return 
	((value & 0x000000FFUL) << 24) |
	((value & 0x0000FF00UL) << 8)  |
	((value & 0x00FF0000UL) >> 8)  |
	((value & 0xFF000000UL) >> 24);
}

uint16_t LE2BE16(uint16_t value)
{
	return 
	((value & 0x00FF) << 8)  |
	((value & 0xFF00) >> 8);
}

uint32_t SDFSizeInBytes(const SDFElement * definition)
{
	uint32_t bytes = 0;
	uint32_t i;
	for (i = 0; ; ++i)
	{
		if (NULL == definition[i].name)
		{
			break;
		}
		bytes += definition[i].count * definition[i].size;
	}
	return bytes;
}

HSDF SDFCreate(const SDFElement * definition, HREADER hReader)
{
	SDFContext * pContext = (SDFContext*) calloc(1, sizeof(SDFContext));
	uint32_t bytes = SDFSizeInBytes(definition);
	if (NULL == pContext)
	{
		return NULL;
	}
	pContext->definition = definition;
	pContext->data = calloc(1, bytes);
	pContext->endian = 0;
	if (NULL == pContext->data)
	{
		free(pContext);
		return NULL;
	}
	if (0 == ReaderRead(hReader, pContext->data, bytes))
	{
		free(pContext->data);
		free(pContext);
		return NULL;
	}
	return (HSDF)pContext;
}

#define LEAPYEAR(year) (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define YEARSIZE(year) (LEAPYEAR(year) ? U64(366) : U64(365))

static const uint8_t MonthSizes[2][12] = 
{
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static const char * Days[] = 
{
	"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

static const char * Months[] = 
{
	"January", "February", "March",	"April", "May", "June",	"July", "August", "September",	"October", "November", "December"
};

enum { SecondsInDay = U64(24) * U64(60) * U64(60) };

void UTC(uint64_t TimeStamp)
{
	uint64_t clock = TimeStamp % SecondsInDay;
	uint64_t day = TimeStamp / SecondsInDay;
	uint64_t seconds = clock % 60;
	uint64_t minutes = (clock % 3600) / 60;
	uint64_t hours = clock / 3600;
	uint64_t dayofweek = (day + 4) % 7; /* day 0 of 1970 was a Thursday */
	uint64_t year = 1970;
	uint64_t month = 0;

	while (day >= YEARSIZE(year))
	{
		day -= YEARSIZE(year);
		++year;
	}
	while (day >= MonthSizes[LEAPYEAR(year)][month])
	{
		day -= MonthSizes[LEAPYEAR(year)][month];
		++month;
	}
	++day;

	ConsoleIOPrintFormatted(" (%s %s %ld %02ld:%02ld:%02ld %ld)", Days[dayofweek], Months[month], day, hours, minutes, seconds, year);
}

void SDFPrintSignature(uint64_t Signature, uint32_t size)
{
    uint32_t i = 0;
    ConsoleIOPrint(" ('");
    for (i = 0; i < size; ++i)
    {
        char byte = (char)((Signature >> (i * 8)) & 0xFF);
        if (xisalnum(byte))
        {
            ConsoleIOPrintFormatted("%c", byte);
        }
        else
        {
            ConsoleIOPrintFormatted("[%02X]", byte);
        }
    }
    ConsoleIOPrint("')");
}

void SDFPrintEnum(const SDFEnum * enumeration, uint64_t value)
{
	if (NULL != enumeration)
	{
		uint8_t first = 1;
        ConsoleIOPrint(" (");
		while (NULL != enumeration->name)
		{
            uint32_t mask = enumeration->mask;
            if (0 == mask) mask = 0xFFFFFFFFUL;
			if (enumeration->value == (value & mask))
			{
				if (!first) ConsoleIOPrint(" | ");
				ConsoleIOPrint(enumeration->name);
                first = 0;
			}
			++enumeration;
		}
        ConsoleIOPrint(")");
	}
}

void SDFPrint(HSDF hSDF)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint32_t i = 0, j = 0, k = 0;
	uint32_t offset = 0;
	if (NULL == pContext)
	{
		return;
	}
	PrintColoredString(pContext->definition[0].name, kYellow, kDefaultColor);
	ConsoleIOPrint("\n");
	for (i = 1; ; ++i)
	{
		if (NULL == pContext->definition[i].name)
		{
			break;
		}
		for (j = 0; j < pContext->definition[i].count; ++j)
		{
			if (kReserved != pContext->definition[i].type)
			{
				ConsoleIOPrintFormatted("%s", pContext->definition[i].name);
				if (pContext->definition[i].count > 1)
				{
					ConsoleIOPrintFormatted("[%d]", j);
				}
				if (kStringASCII == pContext->definition[i].type)
				{
					char * value = (char*) (pContext->data + offset);
					ConsoleIOPrint(" : '");
					for (k = 0; k < pContext->definition[i].size; ++k)
					{
						if (value[k] == 0) break;
						ConsoleIOPrintFormatted("%c", value[k]);
					}
					ConsoleIOPrint("'");
				}
                else
                {
                    uint64_t value = 0;
                    if (1 == pContext->definition[i].size)
                    {
                        uint8_t value8 = *(uint8_t*) (pContext->data + offset);
                        ConsoleIOPrintFormatted(" : 0x%02X", value8);
                        value = value8;
                    }
                    if (2 == pContext->definition[i].size)
                    {
                        uint16_t value16 = *(uint16_t*) (pContext->data + offset);
                        value16 = pContext->endian ? LE2BE16(value16) : value16;
                        ConsoleIOPrintFormatted(" : 0x%04X", value16);
                        value = value16;
                    }
                    if (4 == pContext->definition[i].size)
                    {
                        uint32_t value32 = *(uint32_t*) (pContext->data + offset);
                        value32 = pContext->endian ? LE2BE32(value32) : value32;
                        ConsoleIOPrintFormatted(" : 0x%08X", value32);
                        value = value32;
                    }
                    if (8 == pContext->definition[i].size)
                    {
                        uint64_t value64 = *(uint64_t*) (pContext->data + offset);
                        value64 = pContext->endian ? LE2BE64(value64) : value64;
                        ConsoleIOPrintFormatted(" : 0x%016LX", value64);
                        value = value64;
                    }
                    if (kUTC == pContext->definition[i].type)
                    {
						UTC(value);
                    }
                    if (kVersion == pContext->definition[i].type)
                    {
                        ConsoleIOPrintFormatted(" (%Ld.%Ld.%Ld)", (value >> 16) & 0xFF, (value >> 8) & 0xFF, value & 0xFF);
                    }
                    if (kSignature == pContext->definition[i].type)
                    {
                        SDFPrintSignature(value, pContext->definition[i].size);
                    }
                    SDFPrintEnum(pContext->definition[i].enumeration, value);
                }
				ConsoleIOPrint("\n");
			}
			offset += pContext->definition[i].size;
		}
	}
}

uint8_t SDFReadUInt8(HSDF hSDF, uint32_t offset)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint8_t value = 0;
	value = * (uint8_t*) (pContext->data + offset);
	return value;
}

uint16_t SDFReadUInt16(HSDF hSDF, uint32_t offset)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint16_t value = 0;
	value = * (uint16_t*) (pContext->data + offset);
	value = pContext->endian ? LE2BE16(value) : value;
	return value;
}

uint32_t SDFReadUInt32(HSDF hSDF, uint32_t offset)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint32_t value = 0;
	value = * (uint32_t*) (pContext->data + offset);
	value = pContext->endian ? LE2BE32(value) : value;
	return value;
}

uint64_t SDFReadUInt64(HSDF hSDF, uint64_t offset)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint64_t value = 0;
	value = * (uint64_t*) (pContext->data + offset);
	value = pContext->endian ? LE2BE64(value) : value;
	return value;
}

void SDFSetEndian(HSDF hSDF, uint8_t endian)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	pContext->endian = endian;
}

void SDFDestroy(HSDF hSDF)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	if (NULL != pContext)
	{
		free(pContext->data);
	}
	free(pContext);
}
