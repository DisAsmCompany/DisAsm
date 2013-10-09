/*
 * Filename: MachOFile.c
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O file abstraction
 *
 *
 *
 */

#include "../../DisAsm/DisAsm"
#include "../Executable"

uint32_t LEtoBE(uint32_t value)
{
	return 
	((value & 0x000000FF) << 24) |
	((value & 0x0000FF00) << 8)  |
	((value & 0x00FF0000) >> 8)  |
	((value & 0xFF000000) >> 24);
}

typedef struct SDFElement_t
{
	char * name;
	uint32_t id;
}
SDFElement;

typedef void * HSDF;

typedef struct SDFContext_t
{
	SDFElement * definition;
	uint32_t size;
	uint8_t * data;
}
SDFContext;

#define MachOFatHeader_CpuType    0
#define MachOFatHeader_CpuSubType 1
#define MachOFatHeader_Offset     2
#define MachOFatHeader_Size       3
#define MachOFatHeader_Align      4

SDFElement _MachOFatHeader[] =
{
	{"CpuType   ", MachOFatHeader_CpuType},
	{"CpuSubType", MachOFatHeader_CpuSubType},
	{"Offset    ", MachOFatHeader_Offset},
	{"Size      ", MachOFatHeader_Size},
	{"Align     ", MachOFatHeader_Align},
};

uint32_t SDFSizeInBytes(SDFElement * definition, uint32_t size)
{
	return size * sizeof(uint32_t);
}

HSDF SDFCreate(SDFElement * definition, uint32_t size, HREADER hReader)
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

	for (i = 0; i < size; ++i)
	{
		if (0 == ReaderRead(hReader, &value, sizeof(uint32_t)))
		{
			free(pContext);
			return NULL;
		}
		value = LEtoBE(value);
		memcpy(pContext->data + i * sizeof(uint32_t), &value, sizeof(uint32_t));
	}
	return (HSDF)pContext;
}

void SDFPrint(SDFElement * definition, uint32_t size, HSDF hSDF)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	uint32_t i = 0;
	for (i = 0; i < size; ++i)
	{
		uint32_t * data = (uint32_t*) (pContext->data + i * sizeof(uint32_t));
		printf("%s : 0x%08X\n", pContext->definition[i].name, *data);
	}
}

void SDFDestroy(HSDF hSDF)
{
	SDFContext * pContext = (SDFContext*) hSDF;
	free(pContext->data);
	free(pContext);
}

uint32_t MachOFatHeaderSize = sizeof(_MachOFatHeader) / sizeof(_MachOFatHeader[0]);

int MachOExecutableProcess(ExecutableContext * pContext)
{
	return 0;
}

int MachOFileCreate(ExecutableContext * pContext)
{
	uint32_t magic = 0;
	uint32_t count = 0;
	uint32_t i = 0;
	if (0 == ReaderSeek(pContext->hReader, 0))
	{
		return 0;
	}
	if (0 == ReaderRead(pContext->hReader, &magic, sizeof(uint32_t)))
	{
		return 0;
	}
	magic = LEtoBE(magic);
	if (0xCAFEBABEUL == magic)
	{
		if (0 == ReaderRead(pContext->hReader, &count, sizeof(uint32_t)))
		{
			return 0;
		}
		count = LEtoBE(count);
		if (count > 0)
		{
			for (i = 0; i < count; ++i)
			{
				printf("header %d :\n", i);
				HSDF header = SDFCreate(_MachOFatHeader, MachOFatHeaderSize, pContext->hReader);
				
				SDFPrint(_MachOFatHeader, MachOFatHeaderSize, header);
				
				SDFDestroy(header);
			}
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
