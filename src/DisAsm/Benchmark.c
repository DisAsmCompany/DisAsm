/*
* Filename: Benchmark.c
* Author:   DisAsmCompany
* Date:     27/09/2013
*
* Description: simple benchmarking to
*              measure disassembler
*              performance
*
*/

#include "DisAsm"

typedef struct BenchmarkContext_t
{
	int64_t frequency;
	int64_t sample;
	int64_t count;
	int64_t total;
	int64_t _min;
	int64_t _max;
}
BenchmarkContext;

HBENCHMARK BenchmarkCreate()
{
	BenchmarkContext * pContext = (BenchmarkContext*) calloc(1, sizeof(BenchmarkContext));
#ifdef OS_WINDOWS
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	pContext->frequency = li.QuadPart;
#else /* OS_WINDOWS */
	pContext->frequency = 1000;
#endif /* OS_WINDOWS */
	pContext->count = 0;
	pContext->total = 0;
	pContext->_max = 0;
	pContext->_min = I64(0x7FFFFFFFFFFFFFFF);
	return (HBENCHMARK) pContext;
}

void BenchmarkSampleBegin(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
#ifdef OS_WINDOWS
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	pContext->sample = li.QuadPart;
#else /* OS_WINDOWS */
	struct timeval t;
	gettimeofday(&t, NULL);
	pContext->sample = 1000000 * t.tv_sec + t.tv_usec;
#endif /* OS_WINDOWS */
}

void BenchmarkSampleEnd(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
#ifdef OS_WINDOWS
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	pContext->sample = li.QuadPart - pContext->sample;
#else /* OS_WINDOWS */
	struct timeval t;
	gettimeofday(&t, NULL);
	pContext->sample = (1000000 * t.tv_sec + t.tv_usec) - pContext->sample;
#endif /* OS_WINDOWS */
	pContext->total += pContext->sample;
	++pContext->count;
	pContext->_max = (pContext->_max < pContext->sample) ? pContext->sample : pContext->_max;
	pContext->_min = (pContext->_min > pContext->sample) ? pContext->sample : pContext->_min;
}

void BenchmarkPrintData(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;

	if (pContext->count > 0)
	{
		ConsoleIOPrintFormatted("avg : %.4f\n", (float) pContext->total / (pContext->frequency * pContext->count));
		ConsoleIOPrintFormatted("min : %.4f\n", (float) pContext->_min / pContext->frequency);
		ConsoleIOPrintFormatted("max : %.4f\n", (float) pContext->_max / pContext->frequency);
	}
}

void BenchmarkDestroy(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
	free(pContext);
}
