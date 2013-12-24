/*
 * Filename: MachOHeader64.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O header 64
 *
 *
 *
 */

#pragma once
#ifndef __MACHOHEADER64_H__036E3096_C573_46A5_B286_12AD8EEF3261__
#define __MACHOHEADER64_H__036E3096_C573_46A5_B286_12AD8EEF3261__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

SDFBegin(MachOHeader64, "Mach-O Header 64"),
{"Magic        ", kUnsigned, 4, 1, NULL},
{"CpuType      ", kUnsigned, 4, 1, _MachOCPUType},
{"CpuSubType   ", kUnsigned, 4, 1, NULL},
{"FileType     ", kUnsigned, 4, 1, MachOFileType},
{"CountCommands", kUnsigned, 4, 1, NULL},
{"SizeCommands ", kUnsigned, 4, 1, NULL},
{"Flags        ", kUnsigned, 4, 1, MachOHeaderFlags},
{"Reserved     ", kReserved, 4, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOHEADER64_H__036E3096_C573_46A5_B286_12AD8EEF3261__ */
