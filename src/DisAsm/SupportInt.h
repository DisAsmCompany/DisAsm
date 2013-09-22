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
#ifndef __SUPPORTINT_H__
#define __SUPPORTINT_H__

#ifndef __C99__
#define __C99__ 199901L
#endif /* __C99__ */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__)

#include <stdint.h>

#else /* defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__) */

#if defined(__GNUC__)

#include <stdint.h>

#else /* defined(__GNUC__) */

typedef signed char     int8_t;
typedef unsigned char  uint8_t;
typedef signed short    int16_t;
typedef unsigned short uint16_t;
typedef signed long     int32_t;
typedef unsigned long  uint32_t;

#endif /* defined(__GNUC__) */

#endif /* defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__) */

#endif /* __SUPPORTINT_H__ */
