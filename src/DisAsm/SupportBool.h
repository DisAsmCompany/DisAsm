/*
* Filename: SupportBool.h
* Author:   SSE4
* Date:     22/09/2013
*
* Description: boolean data type support, defines true, 
*              false, bool if necessary, or includes
*              stdbool.h if compiler supports it
*
*/

#pragma once
#ifndef __SUPPORTBOOL_H__
#define __SUPPORTBOOL_H__

#ifndef __C99__
#define __C99__ 199901L
#endif /* __C99__ */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__)

#include <stdbool.h>

#else /* defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__) */

#if defined(__BORLANDC__) || defined(_MSC_VER)
typedef int _Bool;
#endif /* defined(__BORLANDC__) || defined(_MSC_VER) */

#define true  1
#define false 0
#define bool  _Bool

#endif /* defined(__STDC_VERSION__) && (__STDC_VERSION__ >= __C99__) */

#endif /* __SUPPORTBOOL_H__ */
