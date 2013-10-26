/*
* Filename: main.c
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: main test file to run simple sample
*              in order to demonstrate library
*              usage and capabilities
*
*/

#include "../DisAsm/DisAsm"
#include "../StrAsm/StrAsm"
#include "../Executable/Executable"

typedef struct List_t
{
	uint32_t used;
	uint32_t size;
	uint32_t * memory;
}
List;

List * ListCreate()
{
	List * list = (List*) malloc(sizeof(List));
	list->used = 0;
	list->size = 16;
	list->memory = (uint32_t *) malloc(list->size * sizeof(uint32_t));
	return list;
}

void ListDestroy(List * list)
{
	free(list->memory);
	free(list);
}

uint32_t ListSize(List * list)
{
	return list->used;
}

void ListAdd(List * list, uint32_t value)
{
	uint32_t i = 0;
	for (i = 0; i < list->used; ++i)
	{
		if (list->memory[i] == value)
		{
			return;
		}
	}
	list->memory[list->used] = value;
	if (++list->used == list->size)
	{
		list->size *= 2;
		list->memory = realloc(list->memory, list->size * sizeof(uint32_t));
	}
}

uint32_t ListGet(List * list, uint32_t index)
{
	return list->memory[index];
}

void PrintAddress(uint32_t address)
{
	printf("%08X", address);
}

void DisAsmFunction(HDISASM hDisAsm, HREADER hReader, HBENCHMARK hBenchmark, uint32_t address, uint32_t base, List * list)
{
	InstructionInfo info = {0};
	uint8_t length = 0;
	uint8_t ret = 0;
	while (1)
	{
		BenchmarkSampleBegin(hBenchmark);
		length = DisAsmInstructionDecode(hDisAsm, hReader, &info);
		BenchmarkSampleEnd(hBenchmark);
		if (0 == length)
		{
			fprintf(stdout, "[ERROR] cannot decode opcode 0x%08X\n", info.opcode);
			fprintf(stderr, "[ERROR] cannot decode opcode 0x%08X\n", info.opcode);
			break;
		}
		{
			PrintAddress(address);
			printf(" ");
		}
		StrAsmPrintInstruction(&info);

		address += length;

		if (CALL == info.mnemonic && Jz == info.operands[0].type)
		{
			uint32_t offset = address + length + info.imm;
			printf("; call to ");
			PrintAddress(offset);
			ListAdd(list, offset);
		}
		if (JMP == info.mnemonic)
		{
			if (Reg == info.operands[0].type && !info.operands[0].hasBase && !info.operands[0].hasIndex)
			{
				printf("; jump to ");
				PrintAddress(address);
				break;
			}
			if (Jz == info.operands[0].type)
			{
				printf("; jump to ");
				PrintAddress(address);
				break;
			}
		}
		printf("\n");

		if (JO <= info.mnemonic && info.mnemonic <= JG)
		{
			/* conditional jump */
		}
		if (RET == info.mnemonic)
		{
			break;
		}
		/* detect sequence MOV EAX, 4C01h; INT 21h */
		if (ret && 2 == info.length && 0xCD == info.bytes[0] && 0x21 == info.bytes[1])
		{
			break;
		}
		ret = 0;
		if (3 == info.length && 0xB8 == info.bytes[0] && 0x01 == info.bytes[1] && 0x4C == info.bytes[2])
		{
			ret = 1;
		}
	}
}

int main(int argc, char * const argv[])
{
	uint32_t base = 0;
	HBENCHMARK hBenchmark = BenchmarkCreate();
	List * list = ListCreate();
	HREADER hReader = NULL;
	HEXECUTABLE hExecutable = NULL;
	HDISASM hDisAsm = NULL;
	Architecture architecture = 0;
	uint32_t count = 0;
	uint32_t i = 0;
	uint32_t entry = 0;
	uint8_t memory = 0;

	if (argc < 2)
	{
		fprintf(stderr, "[ERROR] usage : DisAsmSample <file>\n");
		return EXIT_FAILURE;
	}
	if (argc >= 3)
	{
		if (0 == strcmp(argv[2], "memory"))
		{
			memory = 1;
		}
	}
	if (memory)
	{
#ifdef _WIN32
		base = (uint32_t) LoadLibraryA(argv[1]);
		hReader = MemoryReaderCreate((void*)base, 0);
#endif /* _WIN32 */
	}
	else
	{
		hReader = FileReaderCreate(argv[1]);
	}
	if (NULL == hReader)
	{
		fprintf(stderr, "[ERROR] cannot open input file \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}
	hExecutable = ExecutableCreate(hReader, memory);
	if (NULL == hExecutable)
	{
		fprintf(stderr, "[ERROR] cannot open executable file \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}
	architecture = ExecutableGetArchitecture(hExecutable);
	if (ArchUnknown == architecture)
	{
		fprintf(stderr, "[ERROR] cannot open executable file (unknown/unsupported architecture) \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}
	if (ArchX86 == architecture)
	{
		hDisAsm = DisAsmCreate(32);
	}
	if (ArchX64 == architecture)
	{
		hDisAsm = DisAsmCreate(64);
	}
	if (NULL == hDisAsm)
	{
		fprintf(stderr, "[ERROR] cannot create disassembler\n");
		return EXIT_FAILURE;
	}
	entry = ExecutableGetEntryPoint(hExecutable);
	if (0 != entry)
	{
		printf("Entry Point :\n");
		ReaderSeek(hReader, entry);
		DisAsmFunction(hDisAsm, hReader, hBenchmark, entry, base, list);
		printf("\n");
	}
	entry = ExecutableGetStubEntryPoint(hExecutable);
	if (0 != entry)
	{
		HDISASM hDisAsmDOS = DisAsmCreate(16);
		printf("Stub Entry Point :\n");
		ReaderSeek(hReader, entry);
		DisAsmFunction(hDisAsmDOS, hReader, hBenchmark, entry, base, list);
		printf("\n");
		DisAsmDestroy(hDisAsmDOS);
	}
	count = ExecutableGetExportCount(hExecutable);
	for (i = 0; i < count; ++i)
	{
		char * name = ExecutableGetExportName(hExecutable, i);
		char * forwarder = ExecutableGetExportForwarderName(hExecutable, i);
		uint32_t address = ExecutableGetExportAddress(hExecutable, i);
		if (0 == address)
		{
			continue;
		}
		if (NULL != forwarder)
		{
			printf("[0x%02X] %s -> %s\n", i, name ? name : "(null)", forwarder);
		}
		else
		{
			printf("[0x%02X] %s\n", i, name ? name : "(null)");
			ReaderSeek(hReader, address);
			DisAsmFunction(hDisAsm, hReader, hBenchmark, address, base, list);
		}
		printf("\n");
		free(name);
		free(forwarder);
	}
	for (i = 0; i < ListSize(list); ++i)
	{
		uint32_t element = ListGet(list, i);
		ReaderSeek(hReader, element);
		printf("function %d %08X :\n", i, element);
		DisAsmFunction(hDisAsm, hReader, hBenchmark, element, base, list);
		printf("\n");
	}
	ListDestroy(list);
	DisAsmDestroy(hDisAsm);
	ExecutableDestroy(hExecutable);
	ReaderDestroy(hReader);
	BenchmarkPrintData(hBenchmark);
	BenchmarkDestroy(hBenchmark);
	return EXIT_SUCCESS;
}
