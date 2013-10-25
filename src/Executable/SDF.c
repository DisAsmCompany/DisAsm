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
        ((value & 0x00000000000000FFULL) << 56) |
        ((value & 0x000000000000FF00ULL) << 40) |
        ((value & 0x0000000000FF0000ULL) >> 24) |
        ((value & 0x00000000FF000000ULL) >> 8)  |
        ((value & 0x000000FF00000000ULL) << 8)  |
        ((value & 0x0000FF0000000000ULL) << 24) |
        ((value & 0x00FF000000000000ULL) >> 40) |
        ((value & 0xFF00000000000000ULL) >> 56);
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
	uint32_t i = 0;
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
	SDFContext * pContext = NULL;
	uint32_t bytes = SDFSizeInBytes(definition);
	pContext = (SDFContext*) malloc(sizeof(SDFContext));
	if (NULL == pContext)
	{
		return NULL;
	}
	pContext->definition = definition;
	pContext->data = malloc(bytes);
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

char * UTC(uint64_t TimeStamp)
{
	time_t time = TimeStamp;
	char * c = ctime(&time);
	c[strlen(c) - 1] = 0;
	return c;
}

void SDFPrintSignature(uint64_t Signature, uint32_t size)
{
    uint32_t i = 0;
    printf(" ('");
    for (i = 0; i < size; ++i)
    {
        char byte = (Signature >> (i * 8)) & 0xFF;
        if (isalnum(byte))
        {
            printf("%c", byte);
        }
        else
        {
            printf("[%02X]", byte);
        }
    }
    printf("')");
}


void SDFPrintEnum(const SDFEnum * enumeration, uint64_t value)
{
    uint8_t first = 1;
	if (NULL != enumeration)
	{
        printf(" (");
		while (NULL != enumeration->name)
		{
            uint32_t mask = enumeration->mask;
            if (0 == mask) mask = 0xFFFFFFFFUL;
			if (enumeration->value == (value & mask))
			{
                printf(first ? "%s" : " | %s", enumeration->name);
                first = 0;
			}
			++enumeration;
		}
        printf(")");
	}
}

void SDFPrint(HSDF hSDF)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint32_t i = 0, j = 0, k = 0;
	uint32_t offset = 0;
	printf("%s\n", pContext->definition[0].name);
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
				printf("%s", pContext->definition[i].name);
				if (pContext->definition[i].count > 1)
				{
					printf("[%d]", j);
				}
				if (kStringASCII == pContext->definition[i].type)
				{
					char * value = (char*) (pContext->data + offset);
					printf(" : '");
					for (k = 0; k < pContext->definition[i].size; ++k)
					{
						if (value[k] == 0) break;
						printf("%c", value[k]);
					}
					printf("'");
				}
                else
                {
                    uint64_t value;
                    if (1 == pContext->definition[i].size)
                    {
                        uint8_t value8 = *(uint8_t*) (pContext->data + offset);
                        printf(" : 0x%02X", value8);
                        value = value8;
                    }
                    if (2 == pContext->definition[i].size)
                    {
                        uint16_t value16 = *(uint16_t*) (pContext->data + offset);
                        value16 = pContext->endian ? LE2BE16(value16) : value16;
                        printf(" : 0x%04X", value16);
                        value = value16;
                    }
                    if (4 == pContext->definition[i].size)
                    {
                        uint32_t value32 = *(uint32_t*) (pContext->data + offset);
                        value32 = pContext->endian ? LE2BE32(value32) : value32;
                        printf(" : 0x%08X", value32);
                        value = value32;
                    }
                    if (8 == pContext->definition[i].size)
                    {
                        uint64_t value64 = *(uint64_t*) (pContext->data + offset);
                        value = pContext->endian ? LE2BE64(value64) : value64;
                        printf(" : 0x%016LX", value64);
                        value = value64;
                    }
                    if (kUTC == pContext->definition[i].type)
                    {
                        printf(" (%s)", UTC(value));
                    }
                    if (kVersion == pContext->definition[i].type)
                    {
                        printf(" (%Ld.%Ld.%Ld)", (value >> 16) & 0xFF, (value >> 8) & 0xFF, value & 0xFF);
                    }
                    if (kSignature == pContext->definition[i].type)
                    {
                        SDFPrintSignature(value, pContext->definition[i].size);
                    }
                    SDFPrintEnum(pContext->definition[i].enumeration, value);
                }
				printf("\n");
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
