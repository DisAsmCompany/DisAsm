/*
 * Filename: MachOHeader.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: Mach-O header
 *
 *
 *
 */

#pragma once
#ifndef __MACHOHEADER_H__83FABB59_D17C_4DFA_AFCC_3005BD6B0A25__
#define __MACHOHEADER_H__83FABB59_D17C_4DFA_AFCC_3005BD6B0A25__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { MachOHeaderCountCommands = 16 };

SDFBegin(MachOHeader, "Mach-O Header"),
{"Magic        ", kUnsigned, 4, 1, NULL},
{"CpuType      ", kUnsigned, 4, 1, _MachOCPUType},
{"CpuSubType   ", kUnsigned, 4, 1, NULL},
{"FileType     ", kUnsigned, 4, 1, MachOFileType},
{"CountCommands", kUnsigned, 4, 1, NULL},
{"SizeCommands ", kUnsigned, 4, 1, NULL},
{"Flags        ", kUnsigned, 4, 1, MachOHeaderFlags},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOHEADER_H__83FABB59_D17C_4DFA_AFCC_3005BD6B0A25__ */
