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
	SDFElement * definition;
	uint32_t size;
	uint8_t * data;
}
SDFContext;

uint32_t SDFSizeInBytes(const SDFElement * definition, uint32_t size)
{
	uint32_t bytes = 0;
	uint32_t i = 0;
	for (i = 0; i < size; ++i)
	{
		bytes += definition[i].count * definition[i].size;
	}
	return bytes;
}

HSDF SDFCreate(const SDFElement * definition, uint32_t size, HREADER hReader)
{
	SDFContext * pContext = NULL;
	uint32_t bytes = SDFSizeInBytes(definition, size);
	uint32_t i = 0;
	uint32_t value = 0;
	pContext = (SDFContext*) malloc(sizeof(SDFContext));
	if (NULL == pContext)
	{
		return NULL;
	}
	pContext->definition = definition;
	pContext->size = size;
	pContext->data = malloc(bytes);
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

char * GetUTC(uint32_t TimeStamp)
{
	time_t time = TimeStamp;
	char * c = ctime(&time);
	c[strlen(c) - 1] = 0;
	return c;
}

void SDFPrint(HSDF hSDF)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint32_t i = 0, j = 0;
	uint32_t offset = 0;
	printf("%s\n", pContext->definition[0].name);
	for (i = 1; i <= pContext->size; ++i)
	{
		for (j = 0; j < pContext->definition[i].count; ++j)
		{
			if (kReserved != pContext->definition[i].type)
			{
				printf("%s", pContext->definition[i].name);
				if (pContext->definition[i].count > 1)
				{
					printf("[%d]", j);
				}
				if (1 == pContext->definition[i].size)
				{
					uint8_t * value = (uint8_t*) (pContext->data + offset);
					printf(" : 0x%02X", *value);
				}
				if (2 == pContext->definition[i].size)
				{
					uint16_t * value = (uint16_t*) (pContext->data + offset);
					printf(" : 0x%04X", *value);
				}
				if (4 == pContext->definition[i].size)
				{
					uint32_t * value = (uint32_t*) (pContext->data + offset);
					printf(" : 0x%08X", *value);
					if (kUTC == pContext->definition[i].type)
					{
						printf(" (%s)", GetUTC(*value));
					}
				}
				printf("\n");
			}
			offset += pContext->definition[i].size;
		}
	}
}

uint16_t SDFReadUInt16(HSDF hSDF, uint32_t id)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint16_t value = 0;
	uint32_t i = 0;
	uint32_t offset = 0;
	for (i = 1; i <= pContext->size; ++i)
	{
		if (pContext->definition[i].id == id)
		{
			value = * (uint16_t*) (pContext->data + offset);
			break;
		}
		offset += pContext->definition[i].count * pContext->definition[i].size;
	}
	return value;
}

uint32_t SDFReadUInt32(HSDF hSDF, uint32_t id)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint32_t value = 0;
	uint32_t i = 0;
	uint32_t offset = 0;
	for (i = 1; i <= pContext->size; ++i)
	{
		if (pContext->definition[i].id == id)
		{
			value = * (uint32_t*) (pContext->data + offset);
			break;
		}
		offset += pContext->definition[i].count * pContext->definition[i].size;
	}
	return value;
}

void SDFDestroy(HSDF hSDF)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	free(pContext->data);
	free(pContext);
}
