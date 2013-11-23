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

void DisAsmFunction(uint8_t bitness, HREADER hReader, HBENCHMARK hBenchmark, address_t address, address_t base, DynamicArray * array)
{
	InstructionInfo info = {0};
	uint8_t ret = 0;
	/* store function start in order to analyze jumps */
	address_t start = address + base;
	for (;;)
	{
		uint8_t length;
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

		if (CALL == info.mnemonic && 1 == info.nOperands && J == HITYPE(info.operands[0].type))
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
			if (J == HITYPE(info.operands[0].type))
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
			ConsoleIOPrintFormatted("; jump to %08LX", destination);

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
	address_t entry;
	uint32_t i;
	uint32_t count;
	HBENCHMARK hBenchmark = BenchmarkCreate();
	DynamicArray * array;
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
	HEXECUTABLE hExecutable;
	uint32_t i;
	uint32_t count;
	uint8_t memory = 0;

#ifdef OS_WINDOWS
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
#endif /* OS_WINDOWS */
	StackWalkInit();
	CrashHandlerInstall();
	LeakTrackerInstall(1);
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
	if (memory)
	{
		ModuleInfo info = {0};
		native_t address = ModuleLoad(argv[1]);
		ModuleGetInfo(address, &info);
		hReader = MemoryReaderCreate(address, info.size);
		base = (uint32_t) address;
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
