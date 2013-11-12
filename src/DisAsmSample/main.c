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
	List * list = (List*) calloc(1, sizeof(List));
	list->used = 0;
	list->size = 16;
	list->memory = (uint32_t *) calloc(1, list->size * sizeof(uint32_t));
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

void DisAsmFunction(uint32_t bitness, HREADER hReader, HBENCHMARK hBenchmark, uint32_t address, uint32_t base, List * list)
{
	InstructionInfo info = {0};
	uint8_t length = 0;
	uint8_t ret = 0;
	/* store function start in order to analyze jumps */
	uint32_t start = address + base;
	while (1)
	{
		BenchmarkSampleBegin(hBenchmark);
		length = DisAsmInstructionDecode(bitness, hReader, &info);
		BenchmarkSampleEnd(hBenchmark);
		if (0 == length)
		{
			fprintf(stdout, "[ERROR] cannot decode opcode 0x%08X\n", info.opcode);
			fprintf(stderr, "[ERROR] cannot decode opcode 0x%08X\n", info.opcode);
			break;
		}
		PrintAddress(address);
		printf(" ");

		StrAsmPrintInstruction(&info);

		address += length;

		if (CALL == info.mnemonic && Jz == info.operands[0].type)
		{
			uint32_t offset = address + length + info.imm;
			printf("; call to ");
			PrintAddress(offset);
			ListAdd(list, offset);
		}
		/* non-conditional jump instructions (JMP) */
		if (JMP == info.mnemonic && 1 == info.nOperands)
		{
			uint32_t destination = 0;
			uint32_t rel = info.imm;
			/* explicit jump offset */
			if (J == HITYPE(info.operands[0].type))
			{
				destination = address;
				switch (info.sizeImm)
				{
				case 1:
					if (0x80UL & rel)
					{
						rel = 0xFFUL - rel + 1;
						destination = (destination > rel) ? (destination - rel) : 0;
					}
					else
					{
						destination += rel;
					}
					break;
				case 2:
					if (0x8000UL & rel)
					{
						rel = 0xFFUL - rel + 1;
						destination = (destination > rel) ? (destination - rel) : 0;
					}
					else
					{
						destination += rel;
					}
					break;
				case 4:
					if (0x80000000UL & rel)
					{
						rel = 0xFFUL - rel + 1;
						destination = (destination > rel) ? (destination - rel) : 0;
					}
					else
					{
						destination += rel;
					}
					break;
				case 8:
					break;
				default:
					break;
				}
				destination += base;
				printf("; jump to ");
			}
			/* special case - memory operand with no registers involved */
			else if (Reg == info.operands[0].type && !info.operands[0].hasBase && !info.operands[0].hasIndex)
			{
				destination = info.disp;
				printf("; jump to ");
			}
			/* jump uses registers, therefore cannot be calculated without emulation */
			else
			{
				/* abort disassembler */
				break;
			}
			PrintAddress(destination);

			/* branch somewhere into already disassembled part of function */
			if (start <= destination && destination < base + address)
			{
				break;
			}
			/* branch somewhere before function */
			if (destination < start)
			{
				break;
			}
			/* jump somewhere outside module */
			else if (0 == destination)
			{
				break;
			}
			else
			{
				address = destination - base;
				if (0 == ReaderSeek(hReader, address))
				{
					break;
				}
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

uint32_t ProcessExecutable(HREADER hReader, HEXECUTABLE hExecutable, uint32_t base)
{
    uint8_t bitness = 0;
	uint32_t entry = 0;
	uint32_t i = 0;
	uint32_t count = 0;
	HBENCHMARK hBenchmark = BenchmarkCreate();
	List * list = ListCreate();
	Architecture architecture = ExecutableGetArchitecture(hExecutable);
	if (ArchUnknown == architecture)
	{
		PrintError("[ERROR] cannot open executable file (unknown/unsupported architecture) \n");
		return 0;
	}
    switch (architecture)
    {
    case ArchX86: bitness = 32; break;
    case ArchX64: bitness = 64; break;
    default:
        PrintError("[ERROR] cannot open executable file (unsupported architecture) \n");
        break;
    }
	if (0 == base)
	{
		base = ExecutableGetBase(hExecutable);
	}	
	entry = ExecutableGetEntryPoint(hExecutable);
	if (0 != entry)
	{
		if (0 != ReaderSeek(hReader, entry))
		{
			PrintString("Entry Point :\n", kYellow);
			DisAsmFunction(bitness, hReader, hBenchmark, entry, base, list);
			PrintString("\n", kYellow);
		}
	}
	entry = ExecutableGetStubEntryPoint(hExecutable);
	if (0 != entry)
	{
		PrintString("Stub Entry Point :\n", kYellow);
		if (0 != ReaderSeek(hReader, entry))
		{
			DisAsmFunction(bitness, hReader, hBenchmark, entry, base, list);
			PrintString("\n", kYellow);
		}
	}
	count = ExecutableGetExportCount(hExecutable);
	for (i = 0; i < count; ++i)
	{
		char * name = ExecutableGetExportName(hExecutable, i);
		char * forwarder = ExecutableGetExportForwarderName(hExecutable, i);
		uint32_t address = ExecutableGetExportAddress(hExecutable, i);
		if (0 != address && 0 != ReaderSeek(hReader, address))
		{
			if (NULL != forwarder)
			{
				printf("[0x%02X] %s -> %s\n", i, name ? name : "(null)", forwarder);
			}
			else
			{
				printf("[0x%02X] %s\n", i, name ? name : "(null)");
				DisAsmFunction(bitness, hReader, hBenchmark, address, base, list);
			}
			printf("\n");
		}
		free(name);
		free(forwarder);
	}
	for (i = 0; i < ListSize(list); ++i)
	{
		uint32_t element = ListGet(list, i);
		if (0 != element && 0 != ReaderSeek(hReader, element))
		{
			printf("function %d %08X :\n", i, element);
			DisAsmFunction(bitness, hReader, hBenchmark, element, base, list);
			printf("\n");
		}
	}
	ListDestroy(list);
	BenchmarkPrintData(hBenchmark);
	BenchmarkDestroy(hBenchmark);
	return 1;
}

int main(int argc, char * const argv[])
{
	uint32_t base = 0;
	HREADER hReader = NULL;
	HEXECUTABLE hExecutable = NULL;
	uint32_t i = 0;
	uint32_t count = 0;
	uint8_t memory = 0;

	if (argc < 2)
	{
		PrintError("[ERROR] usage : DisAsmSample <file>\n");
		return EXIT_FAILURE;
	}
	if (0 == strcmp(argv[1], "map"))
	{
		DisAsmPrintOpCodeMap();
		return EXIT_SUCCESS;
	}
	if (argc >= 3)
	{
		if (0 == strcmp(argv[2], "memory"))
		{
			memory = 1;
		}
	}
	LeakTrackerInstall(1);
	if (memory)
	{
#ifdef _WIN32
		MODULEINFO info = {0};
		base = (uint32_t) LoadLibraryA(argv[1]);
		GetModuleInformation(GetCurrentProcess(), (HMODULE) base, &info, sizeof(MODULEINFO));
		hReader = MemoryReaderCreate((void*)base, info.SizeOfImage);
#endif /* _WIN32 */
	}
	else
	{
		hReader = FileReaderCreate(argv[1]);
	}
	if (NULL == hReader)
	{
		PrintError("[ERROR] cannot open input file \"");
		PrintError(argv[1]);
		PrintError("\"\n");
		return EXIT_FAILURE;
	}
	hExecutable = ExecutableCreate(hReader, memory);
	if (NULL == hExecutable)
	{
		PrintError("[ERROR] cannot open executable file \"");
		PrintError(argv[1]);
		PrintError("\"\n");
		return EXIT_FAILURE;
	}
	count = ExecutableGetObjectCount(hExecutable);
	for (i = 0; i < count; ++i)
	{
		ExecutableSetCurrentObject(hExecutable, i);
		ProcessExecutable(hReader, hExecutable, base);
	}
	ExecutableDestroy(hExecutable);
	ReaderDestroy(hReader);

	LeakTrackerInstall(0);
	
	return EXIT_SUCCESS;
}
