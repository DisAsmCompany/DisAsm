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

void PrintAddress(address_t address)
{
	ConsoleIOPrintFormatted("%08X", address);
}

void DisAsmFunction(uint8_t bitness, HREADER hReader, HBENCHMARK hBenchmark, address_t address, address_t base, DynamicArray * array)
{
	InstructionInfo info = {0};
	uint8_t length = 0;
	uint8_t ret = 0;
	/* store function start in order to analyze jumps */
	address_t start = address + base;
	for (;;)
	{
		BenchmarkSampleBegin(hBenchmark);
		length = DisAsmInstructionDecode(bitness, hReader, &info);
		BenchmarkSampleEnd(hBenchmark);
		if (0 == length)
		{
			ConsoleIOPrintFormatted("[ERROR] cannot decode opcode 0x%08X\n", info.opcode);
			break;
		}
		ConsoleIOPrintFormatted("%08X ", address);

		StrAsmPrintInstruction(&info);

		address += length;

		if (CALL == info.mnemonic && Jz == info.operands[0].type)
		{
			address_t offset = address + info.imm;
			ConsoleIOPrint("; call to ");
			PrintAddress(offset);
			DynamicArrayAdd(array, offset);
		}
		/* non-conditional jump instructions (JMP) */
		if (JMP == info.mnemonic && 1 == info.nOperands)
		{
			address_t destination = 0;
			address_t rel = info.imm;
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
				ConsoleIOPrint("; jump to ");
			}
			/* special case - memory operand with no registers involved */
			else if (Reg == info.operands[0].type && !info.operands[0].hasBase && !info.operands[0].hasIndex)
			{
				destination = info.disp;
				ConsoleIOPrint("; jump to ");
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
		ConsoleIOPrint("\n");

		if (JO <= info.mnemonic && info.mnemonic <= JG)
		{
			/* conditional jump */
		}
		if (RET == info.mnemonic)
		{
			break;
		}
		if (16 == bitness)
		{
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
}

uint8_t ProcessExecutable(HREADER hReader, HEXECUTABLE hExecutable, address_t base)
{
    uint8_t bitness = 0;
	address_t entry = 0;
	uint32_t i = 0;
	uint32_t count = 0;
	HBENCHMARK hBenchmark = BenchmarkCreate();
	DynamicArray * array = NULL;
	Architecture architecture = ExecutableGetArchitecture(hExecutable);
	if (ArchUnknown == architecture)
	{
		ConsoleIOPrint("[ERROR] cannot open executable file (unknown/unsupported architecture) \n");
		return 0;
	}
    switch (architecture)
    {
    case ArchX86: bitness = 32; break;
    case ArchX64: bitness = 64; break;
    default:
        ConsoleIOPrint("[ERROR] cannot open executable file (unsupported architecture) \n");
        break;
    }
	if (0 == base)
	{
		base = ExecutableGetBase(hExecutable);
	}
	array = DynamicArrayCreate();
	entry = ExecutableGetEntryPoint(hExecutable);
	if (0 != entry)
	{
		if (0 != ReaderSeek(hReader, entry))
		{
			ConsoleIOPrint("Entry Point :\n");
			DisAsmFunction(bitness, hReader, hBenchmark, entry, base, array);
			ConsoleIOPrint("\n");
		}
	}
	entry = ExecutableGetStubEntryPoint(hExecutable);
	if (0 != entry)
	{
		ConsoleIOPrint("Stub Entry Point :\n");
		if (0 != ReaderSeek(hReader, entry))
		{
			DisAsmFunction(16, hReader, hBenchmark, entry, base, array);
			ConsoleIOPrint("\n");
		}
	}
	count = ExecutableGetExportCount(hExecutable);
	for (i = 0; i < count; ++i)
	{
		char * name = ExecutableGetExportName(hExecutable, i);
		char * forwarder = ExecutableGetExportForwarderName(hExecutable, i);
		address_t address = ExecutableGetExportAddress(hExecutable, i);
		if (0 != address && 0 != ReaderSeek(hReader, address))
		{
			if (NULL != forwarder)
			{
				ConsoleIOPrintFormatted("[0x%02X] %s -> %s\n", i, name ? name : "(null)", forwarder);
			}
			else
			{
				ConsoleIOPrintFormatted("[0x%02X] %s\n", i, name ? name : "(null)");
				DisAsmFunction(bitness, hReader, hBenchmark, address, base, array);
			}
			ConsoleIOPrint("\n");
		}
		free(name);
		free(forwarder);
	}
	for (i = 0; i < DynamicArraySize(array); ++i)
	{
		address_t element = DynamicArrayGet(array, i);
		if (0 != element && 0 != ReaderSeek(hReader, element))
		{
			ConsoleIOPrintFormatted("function %d %08LX :\n", i, element);
			DisAsmFunction(bitness, hReader, hBenchmark, element, base, array);
			ConsoleIOPrint("\n");
		}
	}
	DynamicArrayDestroy(array);
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

	ConsoleIOInit();

	if (argc < 2)
	{
		ConsoleIOPrint("[ERROR] usage : DisAsmSample <file>\n");
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
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
	CrashHandlerInstall();
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
		ConsoleIOPrintFormatted("[ERROR] cannot open input file \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}
	hExecutable = ExecutableCreate(hReader, memory);
	if (NULL == hExecutable)
	{
		ConsoleIOPrintFormatted("[ERROR] cannot open executable file \"%s\"\n", argv[1]);
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
