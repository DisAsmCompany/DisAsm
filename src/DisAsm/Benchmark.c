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
	uint64_t frequency;
	uint64_t sample;
	uint64_t count;
	uint64_t total;
	uint64_t _min;
	uint64_t _max;
}
BenchmarkContext;

HBENCHMARK BenchmarkCreate()
{
	BenchmarkContext * pContext = (BenchmarkContext*) calloc(1, sizeof(BenchmarkContext));
#ifdef _WIN32
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	pContext->frequency = li.QuadPart;
#else /* _WIN32 */
	pContext->frequency = 1000;
#endif /* _WIN32 */
	pContext->count = 0;
	pContext->total = 0;
	pContext->_max = 0;
	pContext->_min = 0xFFFFFFFFFFFFFFFFULL;
	return (HBENCHMARK) pContext;
}

void BenchmarkSampleBegin(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
#ifdef _WIN32
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	pContext->sample = li.QuadPart;
#else /* _WIN32 */
	struct timeval t;
	gettimeofday(&t, NULL);
	pContext->sample = 1000000 * t.tv_sec + t.tv_usec;
#endif /* _WIN32 */
}

void BenchmarkSampleEnd(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
#ifdef _WIN32
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	pContext->sample = li.QuadPart - pContext->sample;
#else /* _WIN32 */
	struct timeval t;
	gettimeofday(&t, NULL);
	pContext->sample = (1000000 * t.tv_sec + t.tv_usec) - pContext->sample;
#endif /* _WIN32 */
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
		printf("avg : %.4f\n", (float) pContext->total / (pContext->frequency * pContext->count));
		printf("min : %.4f\n", (float) pContext->_min / pContext->frequency);
		printf("max : %.4f\n", (float) pContext->_max / pContext->frequency);
	}
}

void BenchmarkDestroy(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
	free(pContext);
}
