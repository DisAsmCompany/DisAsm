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
#endif /* _M_IX86 */
#ifdef _M_X64
#define CPU_X64
#endif /* _M_X64 */
#ifdef _M_IA64
#define CPU_IA64
#endif /* _M_IA64 */

#endif /* _WIN32 */

#if defined(__unix__) || defined(__unix)
#define OS_UNIX
#endif /* defined(__unix__) || defined(__unix) */

#if defined(__APPLE__)
#define OS_UNIX
#define OS_MACOSX
#endif /* defined(__APPLE__) */

#if defined(__CYGWIN__)
#define OS_CYGWIN
#endif /* defined(__CYGWIN__) */

#ifdef OS_UNIX
#if defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
#define CPU_X86
#endif /* defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) */

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#define CPU_X64
#endif /* defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) */

#if defined(__ia64__) || defined(_IA64) || defined(__IA64__)
#define CPU_IA64
#endif /* defined(__ia64__) || defined(_IA64) || defined(__IA64__) */
#endif /* OS_UNIX */

#if defined(_MSC_VER)
#define COMP_MICOROSOFTC
#endif /* defined(_MSC_VER) */

#if defined(__BORLANDC__) || defined(__CODEGEARC__)
#define COMP_BORLANDC
#endif /* defined(__BORLANDC__) || defined(__CODEGEARC__) */

#if defined(__GNUC__)
#define COMP_GNUC
#endif /* defined(__GNUC__) */

#if defined(__clang__)
#define COMP_CLANG
#endif /* defined(__clang__) */

#if defined(__WATCOMC__)
#define COMP_WATCOMC
#endif /* defined(__WATCOMC__) */

#if defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ECL) || defined(__ICL)
#define COMP_INTELC
#endif /* defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ECL) || defined(__ICL) */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#ifdef OS_WINDOWS
#include <windows.h>
#else /* OS_WINDOWS */
#include <unistd.h>
#include <signal.h>
#include <dlfcn.h>
#include <fcntl.h>
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
