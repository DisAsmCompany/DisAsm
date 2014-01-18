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
#include "../DisAsmPlatform/DisAsmPlatform"
#include "../StrAsm/StrAsm"
#include "../Executable/Executable"

uint8_t map = 0;
uint8_t leaks = 0;
uint8_t memory = 0;
uint8_t help = 0;
uint8_t preload = 0;
uint8_t quiet = 0;
uint8_t raw = 0;

char * bytes = NULL;

address_t AddressAdjust(address_t address, offset_t offset, uint8_t size)
{
	address_t destination = address;
    offset_t mask = 0;
    offset_t inverse = 0;
	switch (size)
	{
		case 1: mask = 0x80; inverse = 0xFF; break;
        case 2: mask = 0x8000; inverse = 0xFFFF; break;
        case 4: mask = 0x80000000UL; inverse = 0xFFFFFFFFUL; break;
        case 8: mask = U64(0x8000000000000000); inverse = U64(0xFFFFFFFFFFFFFFFF); break;
        default: break;
    }
	if (mask & offset)
	{
		offset = inverse - offset + 1;
		destination = (destination > offset) ? (destination - offset) : 0;
	}
	else
	{
		destination += offset;
	}
	return destination;
}

typedef enum DisAsmFlags_t
{
	kStopOnRET = 0x00000001UL
}
DisAsmFlags;

void DisAsmFunction(uint8_t bitness, HREADER hReader, HBENCHMARK hBenchmark, address_t address, address_t base, DynamicArray * array, uint32_t flags)
{
	InstructionInfo info;
	uint8_t ret = 0;
	/* store function start in order to analyze jumps */
	address_t start = address + base;

	(void)(hBenchmark);
	memset(&info, 0, sizeof(info));
	for (;;)
	{
		uint8_t length;
#if defined(PROFILE)
		BenchmarkSampleBegin(hBenchmark);
#endif /* defined(PROFILE) */
		length = DisAsmInstructionDecode(bitness, hReader, &info);
#if defined(PROFILE)
		BenchmarkSampleEnd(hBenchmark);
#endif /* defined(PROFILE) */
		if (0 == length)
		{
			uint8_t i;
			ConsoleIOError("[ERROR] cannot decode instruction ");
			for (i = 0; i < info.length; ++i)
			{
				ConsoleIOErrorFormatted("%02X", info.bytes[i]);
			}
			ConsoleIOError("\n");
			break;
		}
		if (!quiet)
		{
			ConsoleIOPrintFormatted("%08X ", address);
			StrAsmPrintInstruction(&info);
		}
		address += length;

		if (!quiet && CALL == info.mnemonic && 1 == info.nOperands && Imm == info.operands[0].type)
		{
			address_t offset = AddressAdjust(address, info.imm, info.sizeImm);
			ConsoleIOPrintFormatted("; call to %08LX", offset);
			DynamicArrayAdd(array, offset);
		}
		/* non-conditional jump instructions (JMP) */
		if (JMP == info.mnemonic && 1 == info.nOperands)
		{
			address_t destination;
			/* explicit jump offset */
			if (Imm == info.operands[0].type)
			{
				destination = AddressAdjust(address, info.imm, info.sizeImm);
				
				destination += base;
			}
			/* special case - memory operand with no registers involved */
			else if (Reg == info.operands[0].type && !info.operands[0].hasBase && !info.operands[0].hasIndex)
			{
				destination = info.disp;
			}
			/* jump uses registers, therefore cannot be calculated without emulation */
			else
			{
				/* abort disassembler */
				break;
			}
			if (!quiet)
			{
				ConsoleIOPrintFormatted("; jump to %08LX", destination);
			}

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
		if (!quiet)
		{
			ConsoleIOPrint("\n");
		}
		if (JO <= info.mnemonic && info.mnemonic <= JG)
		{
			/* conditional jump */
		}
		if (flags & kStopOnRET && RET == info.mnemonic)
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
	address_t entry;
	uint32_t i;
	uint32_t count;
	HBENCHMARK hBenchmark = BenchmarkCreate();
	DynamicArray * array;
	Architecture architecture = ExecutableGetArchitecture(hExecutable);
	if (ArchUnknown == architecture)
	{
		BenchmarkDestroy(hBenchmark);
		ConsoleIOPrint("[ERROR] cannot open executable file (unknown/unsupported architecture) \n");
		return 0;
	}
    switch (architecture)
    {
    case ArchX86: bitness = 32; break;
    case ArchX64: bitness = 64; break;
    default:
		BenchmarkDestroy(hBenchmark);
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
			DisAsmFunction(bitness, hReader, hBenchmark, entry, base, array, kStopOnRET);
			ConsoleIOPrint("\n");
		}
	}
	entry = ExecutableGetStubEntryPoint(hExecutable);
	if (0 != entry)
	{
		ConsoleIOPrint("Stub Entry Point :\n");
		if (0 != ReaderSeek(hReader, entry))
		{
			DisAsmFunction(16, hReader, hBenchmark, entry, base, array, kStopOnRET);
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
				DisAsmFunction(bitness, hReader, hBenchmark, address, base, array, kStopOnRET);
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
			DisAsmFunction(bitness, hReader, hBenchmark, element, base, array, kStopOnRET);
			ConsoleIOPrint("\n");
		}
	}
	DynamicArrayDestroy(array);
	BenchmarkDestroy(hBenchmark);
	return 1;
}

uint8_t CheckCommandLineOption(const char * arg, const char * longoption)
{
	uint8_t result = 0;
	if (xstrlen(longoption) > 3 && '-' == longoption[0] && '-' == longoption[1])
	{
		char shortoption[3] = {0};
		char c = longoption[2];

		result |= (0 == xstricmp(longoption, arg)) ? 1 : 0;

		/* -x */
		shortoption[0] = '-';
		shortoption[1] = c;
		result |= (0 == xstricmp(shortoption, arg)) ? 1 : 0;
		/* /x */
		shortoption[0] = '/';
		shortoption[1] = c;
		result |= (0 == xstricmp(shortoption, arg)) ? 1 : 0;
	}
	return result;
}

void ParseCommandLine(int argc, char * const argv[])
{
	int i;

	for (i = 1; i < argc; ++i)
	{
		leaks   |= CheckCommandLineOption(argv[i], "--leaks");
		map     |= CheckCommandLineOption(argv[i], "--opcodemap");
		memory  |= CheckCommandLineOption(argv[i], "--memory");
		help    |= CheckCommandLineOption(argv[i], "--help");
		preload |= CheckCommandLineOption(argv[i], "--preload");
		quiet   |= CheckCommandLineOption(argv[i], "--quiet");
		raw     |= CheckCommandLineOption(argv[i], "--raw");
		if (CheckCommandLineOption(argv[i], "--bytes"))
		{
			if (argc >= i + 1)
			{
				++i;
				bytes = argv[i];
			}
		}
	}
}

int main(int argc, char * const argv[])
{
	uint32_t base = 0;
	HREADER hReader = NULL;
	HEXECUTABLE hExecutable;
	uint32_t i;
	uint32_t count;
	
#ifdef OS_WINDOWS
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
#endif /* OS_WINDOWS */
	ConsoleIOInit();

	ParseCommandLine(argc, argv);
	if (help)
	{
		ConsoleIOPrint("usage : DisAsmSample <options> <file>\n");
		return EXIT_SUCCESS;
	}
	if (argc < 2)
	{
		ConsoleIOPrint("[ERROR] usage : DisAsmSample <file> <options>\n");
		return EXIT_FAILURE;
	}
	if (map)
	{
		DisAsmPrintOpCodeMap();
		return EXIT_SUCCESS;
	}
	StackWalkInit();
	CrashHandlerInstall();
	if (leaks)
	{
		LeakTrackerInstall(1);
	}
	if (preload)
	{
		hReader = CachedFileReaderCreate(argv[argc - 1]);
	}
	else if (memory)
	{
		ModuleInfo info;
		native_t address = ModuleLoad(argv[argc - 1]);
		memset(&info, 0, sizeof(info));
		ModuleGetInfo(address, &info);
		hReader = MemoryReaderCreate(address, info.size);
		base = (uint32_t) address;
		ConsoleIOPrint("[WARNING] : --memory option specified, will attempt to load executable file\n");
	}
	else if (NULL != bytes)
	{
		uint32_t length = xstrlen(bytes);
		uint8_t * buffer = (uint8_t*) malloc(length / 2);
		uint32_t i;
		for (i = 0; i < length; ++i)
		{
			char c = bytes[i];
			if (i % 2)
			{
				buffer[i / 2] <<= 4;
			}
			else
			{
				buffer[i / 2] = 0;
			}
			if ('0' <= c && c <= '9')
			{
				buffer[i / 2] += c - '0';
			}
			else if (('a' <= c && c <= 'f') || ('A' <= c && c <= 'F'))
			{
				buffer[i / 2] += (c & ~0x20) - 'A' + 10;
			}
		}
		hReader = MemoryReaderCreate((native_t)buffer, length / 2);
	}
	else
	{
		hReader = FileReaderCreate(argv[argc - 1]);
	}
	if (NULL == hReader)
	{
		ConsoleIOPrintFormatted("[ERROR] cannot open input file \"%s\"\n", argv[argc - 1]);
		return EXIT_FAILURE;
	}
	if (raw || NULL != bytes)
	{
		DisAsmFunction(32, hReader, NULL, 0, 0, 0, 0);
	}
	else
	{
		hExecutable = ExecutableCreate(hReader, memory);
		if (NULL == hExecutable)
		{
			ConsoleIOPrintFormatted("[ERROR] cannot open executable file \"%s\"\n", argv[argc - 1]);
			return EXIT_FAILURE;
		}
		count = ExecutableGetObjectCount(hExecutable);
		for (i = 0; i < count; ++i)
		{
			ExecutableSetCurrentObject(hExecutable, i);
			ProcessExecutable(hReader, hExecutable, base);
		}
		ExecutableDestroy(hExecutable);
	}
	ReaderDestroy(hReader);

	if (leaks)
	{
		LeakTrackerInstall(0);
	}
	return EXIT_SUCCESS;
}
