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

#if defined(__GNUC__)

#include <stdint.h>

#else /* defined(__GNUC__) */

typedef signed char        int8_t;
typedef unsigned char      uint8_t;
typedef signed short       int16_t;
typedef unsigned short     uint16_t;
typedef signed long        int32_t;
typedef unsigned long      uint32_t;
typedef signed long long   int64_t;
typedef unsigned long long uint64_t;

#endif /* defined(__GNUC__) */

#endif /* defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__) */

typedef uint64_t address_t;
typedef uint64_t offset_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SUPPORTINT_H__46E0AD0F_E016_4B9C_8358_9D525CD4347E__ */
