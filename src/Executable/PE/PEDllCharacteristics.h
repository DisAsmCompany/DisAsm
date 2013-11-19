/*
* Filename: PEDllCharacteristics.h
* Author:   DisAsmCompany
* Date:     17/10/2013
*
* Description: PE Dll Characteristics
*              
*              
*
*/

#pragma once
#ifndef __PEDLLCHARACTERISTICS_H__
#define __PEDLLCHARACTERISTICS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum PEDllCharacteristics[] =
{
    {"IMAGE_LIBRARY_PROCESS_INIT",                     0x0001, 0x0001},
    {"IMAGE_LIBRARY_PROCESS_TERM",                     0x0002, 0x0002},
    {"IMAGE_LIBRARY_THREAD_INIT",                      0x0004, 0x0004},
    {"IMAGE_LIBRARY_THREAD_TERM",                      0x0008, 0x0008},
    {"IMAGE_DLLCHARACTERISTICS_10h",                   0x0010, 0x0010},
    {"IMAGE_DLLCHARACTERISTICS_20h",                   0x0020, 0x0020},
    {"IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE",          0x0040, 0x0040},
    {"IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY",       0x0080, 0x0080},
    {"IMAGE_DLLCHARACTERISTICS_NX_COMPAT",             0x0100, 0x0100},
    {"IMAGE_DLLCHARACTERISTICS_NO_ISOLATION",          0x0200, 0x0200},
    {"IMAGE_DLLCHARACTERISTICS_NO_SEH",                0x0400, 0x0400},
    {"IMAGE_DLLCHARACTERISTICS_NO_BIND",               0x0800, 0x0800},
    {"IMAGE_DLLCHARACTERISTICS_1000h",                 0x1000, 0x1000},
    {"IMAGE_DLLCHARACTERISTICS_WDM_DRIVER",            0x2000, 0x2000},
    {"IMAGE_DLLCHARACTERISTICS_4000h",                 0x4000, 0x4000},
    {"IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE", 0x8000, 0x8000},
    {NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEDLLCHARACTERISTICS_H__ */
