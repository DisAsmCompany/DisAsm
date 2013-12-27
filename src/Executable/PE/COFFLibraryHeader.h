/*
 * Filename: COFFLibraryHeader.h
 * Author:   DisAsmCompany
 * Date:     25/10/2013
 *
 * Description: COFF Library Header
 *              used in Microsoft COFF
 *              Library (.lib) files
 *
 */

#pragma once
#ifndef __COFFLIBRARYHEADER_H__E5C823A1_444D_4E5C_BAE6_234E0070CBB5__
#define __COFFLIBRARYHEADER_H__E5C823A1_444D_4E5C_BAE6_234E0070CBB5__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kCOFFLibrarySignatureSize = 8 };

static const char kCOFFLibrarySignature[] = "!<arch>\n";

static const char kCOFFMemberLinker[]    = "/       ";

SDFBegin(COFFLibraryHeader, "COFF Library Header"),
{"Name         ", kStringASCII, 16, 1, NULL},
{"Date         ", kStringASCII, 12, 1, NULL},
{"User ID      ", kStringASCII, 6, 1, NULL},
{"Group ID     ", kStringASCII, 6, 1, NULL},
{"Mode         ", kStringASCII, 8, 1, NULL},
{"Size         ", kStringASCII, 10, 1, NULL},
{"End Of Header", kStringASCII, 2, 1, NULL},
SDFEnd

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __COFFLIBRARYHEADER_H__E5C823A1_444D_4E5C_BAE6_234E0070CBB5__ */
