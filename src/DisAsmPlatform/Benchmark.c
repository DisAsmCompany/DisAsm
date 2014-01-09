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

#include "../DisAsm/DisAsm"
#include "DisAsmPlatform"

typedef struct BenchmarkContext_t
{
	BenchmarkSample sample;
	int64_t count;
	int64_t total;
	int64_t _min;
	int64_t _max;
#ifdef OS_WINDOWS
	DWORD affinity;
#endif /* OS_WINDOWS */
}
BenchmarkContext;

HBENCHMARK BenchmarkCreate()
{
	BenchmarkContext * pContext = (BenchmarkContext*) calloc(1, sizeof(BenchmarkContext));
#ifdef OS_WINDOWS
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	pContext->sample.frequency = li.QuadPart;
#else /* OS_WINDOWS */
	pContext->sample.frequency = 1000;
#endif /* OS_WINDOWS */
	pContext->count = 0;
	pContext->total = 0;
	pContext->_max = 0;
	pContext->_min = I64(0x7FFFFFFFFFFFFFFF);
	return (HBENCHMARK) pContext;
}

#ifdef OS_WINDOWS

static int64_t HighLow(uint32_t high, uint32_t low)
{
	int64_t value = high;
	value <<= 32;
	value += low;
	return value;
}

#endif /* OS_WINDOWS */

void BenchmarkSampleBegin(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
#ifdef OS_WINDOWS
	LARGE_INTEGER li;
	FILETIME CreationTime, ExitTime, KernelTime, UserTime;
	pContext->affinity = SetThreadAffinityMask(GetCurrentThread(), 1);
	GetThreadTimes(GetCurrentThread(), &CreationTime, &ExitTime, &KernelTime, &UserTime);
	QueryPerformanceCounter(&li);
	pContext->sample.tick = CallRDTSC();
	pContext->sample.time = li.QuadPart;
	pContext->sample.user = HighLow(UserTime.dwHighDateTime, UserTime.dwLowDateTime);
	pContext->sample.kernel = HighLow(KernelTime.dwHighDateTime, KernelTime.dwLowDateTime);
#else /* OS_WINDOWS */
	struct timeval t;
	gettimeofday(&t, NULL);
	pContext->sample.time = 1000000 * t.tv_sec + t.tv_usec;
#endif /* OS_WINDOWS */
}

void BenchmarkSampleEnd(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
#ifdef OS_WINDOWS
	LARGE_INTEGER li;
	FILETIME CreationTime, ExitTime, KernelTime, UserTime;
	pContext->sample.tick = CallRDTSC() - pContext->sample.tick;
	GetThreadTimes(GetCurrentThread(), &CreationTime, &ExitTime, &KernelTime, &UserTime);
	QueryPerformanceCounter(&li);
	pContext->sample.time = li.QuadPart - pContext->sample.time;
	pContext->sample.user = HighLow(UserTime.dwHighDateTime, UserTime.dwLowDateTime) - pContext->sample.user;
	pContext->sample.kernel = HighLow(KernelTime.dwHighDateTime, KernelTime.dwLowDateTime) - pContext->sample.kernel;
	SetThreadAffinityMask(GetCurrentThread(), pContext->affinity);
#else /* OS_WINDOWS */
	struct timeval t;
	gettimeofday(&t, NULL);
	pContext->sample.time = (1000000 * t.tv_sec + t.tv_usec) - pContext->sample.time;
#endif /* OS_WINDOWS */
	pContext->total += pContext->sample.time;
	++pContext->count;
	pContext->_max = (pContext->_max < pContext->sample.time) ? pContext->sample.time : pContext->_max;
	pContext->_min = (pContext->_min > pContext->sample.time) ? pContext->sample.time : pContext->_min;
}

void BenchmarkGetSample(HBENCHMARK hBenchmark, BenchmarkSample * pSample)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
	memcpy(pSample, &pContext->sample, sizeof(BenchmarkSample));
}

void BenchmarkDestroy(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
	free(pContext);
}
