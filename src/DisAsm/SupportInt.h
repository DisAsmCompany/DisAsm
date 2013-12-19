/*
* Filename: SupportInt.h
* Author:   SSE4
* Date:     22/09/2013
*
* Description: boolean int type support, defines types
*              such as int8_t, unit8_t, etc, or includes
*              stdint.h if compiler supports it
*
*/

#pragma once
#ifndef __SUPPORTINT_H__46E0AD0F_E016_4B9C_8358_9D525CD4347E__
#define __SUPPORTINT_H__46E0AD0F_E016_4B9C_8358_9D525CD4347E__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef __C99__
#define __C99__ 199901L
#endif /* __C99__ */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__)

#include <stdint.h>

#else /* defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__) */

#ifdef COMP_GNUC

#include <stdint.h>

#else /* COMP_GNUC */

typedef signed char        int8_t;
typedef unsigned char      uint8_t;
typedef signed short       int16_t;
typedef unsigned short     uint16_t;
typedef signed long        int32_t;
typedef unsigned long      uint32_t;

#ifdef COMP_BORLANDC

typedef __int64            int64_t;
typedef unsigned __int64   uint64_t;

#elif defined(COMP_MICROSOFTC) && COMP_VERSION <= COMP_MICROSOFTC6

typedef __int64            int64_t;
typedef unsigned __int64   uint64_t;

#else /* COMP_BORLANDC */

typedef signed long long   int64_t;
typedef unsigned long long uint64_t;

#endif /* COMP_BORLANDC */

#endif /* COMP_GNUC */

#endif /* defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__) */

typedef uint64_t address_t;
typedef uint64_t offset_t;

#ifdef COMP_BORLANDC

#define  I64(x) (x)
#define  U64(x) (x)

#elif defined(COMP_MICROSOFTC) && COMP_VERSION <= COMP_MICROSOFTC6

#define  I64(x) (x)
#define  U64(x) (x)

#else /*  COMP_BORLANDC */

#define  I64(x) (x##LL)
#define  U64(x) (x##ULL)

#endif /* COMP_BORLANDC */

#ifdef CPU_X86
enum { kBitnessNative = 32 };
typedef uint32_t native_t;
#endif /* CPU_X86 */
#ifdef CPU_X64
enum { kBitnessNative = 64 };
typedef uint64_t native_t;
#endif /* CPU_X64 */
#ifdef CPU_IA64
enum { kBitnessNative = 64 };
typedef uint64_t native_t;
#endif /* CPU_IA64 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SUPPORTINT_H__46E0AD0F_E016_4B9C_8358_9D525CD4347E__ */
