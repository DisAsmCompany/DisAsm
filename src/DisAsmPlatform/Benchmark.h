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
#ifndef __BENCHMARK_H__CD0D1B20_8A57_4C47_AAC6_6FC68CBEC1F5__
#define __BENCHMARK_H__CD0D1B20_8A57_4C47_AAC6_6FC68CBEC1F5__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct BenchmarkSample_t
{
	int64_t frequency;
	int64_t time;
	int64_t user;
	int64_t kernel;
	int64_t tick;
}
BenchmarkSample;

typedef void * HBENCHMARK;

HBENCHMARK BenchmarkCreate();
void BenchmarkSampleBegin(HBENCHMARK hBenchmark);
void BenchmarkSampleEnd(HBENCHMARK hBenchmark);
void BenchmarkGetSample(HBENCHMARK hBenchmark, BenchmarkSample * pSample);
void BenchmarkDestroy(HBENCHMARK hBenchmark);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BENCHMARK_H__CD0D1B20_8A57_4C47_AAC6_6FC68CBEC1F5__ */
