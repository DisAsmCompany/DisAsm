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

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
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
	BenchmarkContext * pContext = (BenchmarkContext*) malloc(sizeof(BenchmarkContext));
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	pContext->frequency = li.QuadPart;
	pContext->count = 0;
	pContext->total = 0;
	pContext->_max = 0;
	pContext->_min = 0xFFFFFFFFFFFFFFFFULL;
	return (HBENCHMARK) pContext;
}

void BenchmarkSampleBegin(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	pContext->sample = li.QuadPart;
}

void BenchmarkSampleEnd(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	pContext->sample = li.QuadPart - pContext->sample;
	pContext->total += pContext->sample;
	++pContext->count;
	pContext->_max = (pContext->_max < pContext->sample) ? pContext->sample : pContext->_max;
	pContext->_min = (pContext->_min > pContext->sample) ? pContext->sample : pContext->_min;
}

void BenchmarkPrintData(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;

	printf("avg : %.4f\n", (float) pContext->total / (pContext->frequency * pContext->count));
	printf("min : %.4f\n", (float) pContext->_min / pContext->frequency);
	printf("max : %.4f\n", (float) pContext->_max / pContext->frequency);
}

void BenchmarkDestroy(HBENCHMARK hBenchmark)
{
	BenchmarkContext * pContext = (BenchmarkContext*) hBenchmark;
}
