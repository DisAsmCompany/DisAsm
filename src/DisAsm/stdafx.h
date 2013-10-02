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
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#else /* _WIN32 */
#include <sys/time.h>
#endif /* _WIN32 */

#endif /* __STDAFX_H__ */
