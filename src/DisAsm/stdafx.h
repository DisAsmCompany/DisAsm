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
#ifndef __STDAFX_H__
#define __STDAFX_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")
#else /* _WIN32 */
#include <unistd.h>
#include <signal.h>
#include <dlfcn.h>
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif /* __APPLE__ */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#endif /* _WIN32 */

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif /* MIN */
#ifndef MAX 
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif /* MAX */

#endif /* __STDAFX_H__ */
