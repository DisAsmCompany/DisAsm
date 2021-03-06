/*
* Filename: main.c
* Author:   DisAsmCompany
* Date:     20/12/2013
*
* Description: benchmarking executable in order to test
*              and profile disassembler speed
*
*
*/

#include "../DisAsm/DisAsm"
#include "../DisAsmPlatform/DisAsmPlatform"

int main(int argc, char * const argv[])
{
	HBENCHMARK hBenchmark = BenchmarkCreate();
	HREADER hReader = NULL;
	BenchmarkSample sample;
	uint64_t size = 0;
	uint64_t offset = 0;
	uint64_t instructions = 0;
	uint8_t i;
	uint64_t speed = 0;
	InstructionInfo info;

	ConsoleIOInit();
	if (argc < 2)
	{
		ConsoleIOPrint("[ERROR] usage : DisAsmBenchmark <file>\n");
		return EXIT_FAILURE;
	}
	hReader = CachedFileReaderCreate(argv[1]);
	if (NULL == hReader)
	{
		ConsoleIOPrint("[ERROR] cannot open input file\n");
		return EXIT_FAILURE;
	}
	ReaderSize(hReader, &size);

	for (i = 0; i < 25; ++i)
	{
		ReaderSeek(hReader, 0);
		offset = 0;
		instructions = 0;

		BenchmarkSampleBegin(hBenchmark);
		while (offset < size)
		{
			if (0 == DisAsmInstructionDecode(32, hReader, &info))
			{
				break;
			}
			offset += info.length;
			++instructions;
		}
		BenchmarkSampleEnd(hBenchmark);
		BenchmarkGetSample(hBenchmark, &sample);

		speed = offset * sample.frequency / sample.time;
		ConsoleIOPrintFormatted("%Ld instructions per second\n", instructions * sample.frequency / sample.time);
		ConsoleIOPrintFormatted("%Ld bytes per second ", speed);
		if (speed > 1024 * 1024)
		{
			ConsoleIOPrintFormatted("(%Ld Mb per second)", speed / (1024 * 1024));
		}
		else if (speed > 1024)
		{
			ConsoleIOPrintFormatted("(%Ld Mb per second)", speed / 1024);
		}
		ConsoleIOPrint("\n");
	}
	ReaderDestroy(hReader);
	BenchmarkDestroy(hBenchmark);
	return EXIT_SUCCESS;
}
