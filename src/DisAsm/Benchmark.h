/*
* Filename: Benchmark.h
* Author:   DisAsmCompany
* Date:     27/09/2013
*
* Description: simple benchmarking to
*              measure disassembler
*              performance
*
*/

#pragma once
#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

typedef void * HBENCHMARK;

HBENCHMARK BenchmarkCreate();
void BenchmarkSampleBegin(HBENCHMARK hBenchmark);
void BenchmarkSampleEnd(HBENCHMARK hBenchmark);
void BenchmarkPrintData(HBENCHMARK hBenchmark);
void BenchmarkDestroy(HBENCHMARK hBenchmark);

#endif /* __BENCHMARK_H__ */
