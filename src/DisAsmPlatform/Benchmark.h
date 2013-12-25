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

typedef void * HBENCHMARK;

HBENCHMARK BenchmarkCreate();
void BenchmarkSampleBegin(HBENCHMARK hBenchmark);
void BenchmarkSampleEnd(HBENCHMARK hBenchmark);
void BenchmarkPrintData(HBENCHMARK hBenchmark);
int64_t BenchmarkGetSample(HBENCHMARK hBenchmark);
int64_t BenchmarkGetFrequency(HBENCHMARK hBenchmark);
void BenchmarkDestroy(HBENCHMARK hBenchmark);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BENCHMARK_H__CD0D1B20_8A57_4C47_AAC6_6FC68CBEC1F5__ */
