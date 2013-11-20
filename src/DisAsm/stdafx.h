/*
 * Filename: stdafx.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: all common include files
 *              are included to this all-in-one
 *              include files
 *
 */

#pragma once
#ifndef __STDAFX_H__7D97CBFD_DF43_4024_A628_1CA89E65AB83__
#define __STDAFX_H__7D97CBFD_DF43_4024_A628_1CA89E65AB83__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _WIN32
#define OS_WINDOWS

#ifdef _M_IX86
#define CPU_X86
enum { kBitnessNative = 32 };
#endif /* _M_IX86 */
#ifdef _M_X64
#define CPU_X64
enum { kBitnessNative = 64 };
#endif /* _M_X64 */
#ifdef _M_IA64
#define CPU_IA64
enum { kBitnessNative = 64 };
#endif /* _M_IA64 */

#endif /* _WIN32 */

#if defined(__unix__) || defined(__unix)
#define OS_UNIX

#if defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
#define CPU_X86
enum { kBitnessNative = 32 };
#endif /* defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) */

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#define CPU_X64
enum { kBitnessNative = 64 };
#endif /* defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) */

#if defined(__ia64__) || defined(_IA64) || defined(__IA64__)
#define CPU_IA64
enum { kBitnessNative = 64 };
#endif /* defined(__ia64__) || defined(_IA64) || defined(__IA64__) */

#endif /* defined(__unix__) || defined(__unix) */

#ifdef __APPLE__
#define OS_MACOSX
#endif /* __APPLE__ */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#ifdef OS_WINDOWS
#include <windows.h>
#else /* OS_WINDOWS */
#include <unistd.h>
#include <signal.h>
#include <dlfcn.h>
#ifdef OS_MACOSX
#include <mach-o/dyld.h>
#endif /* OS_MACOSX */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#endif /* OS_WINDOWS */

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif /* MIN */
#ifndef MAX 
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif /* MAX */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STDAFX_H__7D97CBFD_DF43_4024_A628_1CA89E65AB83__ */
