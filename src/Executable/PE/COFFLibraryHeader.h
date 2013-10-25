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
#ifndef __COFFLIBRARYHEADER_H__
#define __COFFLIBRARYHEADER_H__

static const char kCOFFLibrarySignatureSize = 8;
static const char kCOFFLibrarySignature[] = "!<arch>\n";

static const SDFElement COFFLibraryHeader[] =
{
	{"COFF Library Header"},
	{"Name         ", kStringASCII, 16, 1},
	{"Date         ", kStringASCII, 12, 1},
	{"User ID      ", kStringASCII, 6, 1},
	{"Group ID     ", kStringASCII, 6, 1},
	{"Mode         ", kStringASCII, 8, 1},
	{"Size         ", kStringASCII, 10, 1},
	{"End Of Header", kStringASCII, 2, 1},
	{NULL}
};

#endif /* __COFFLIBRARYHEADER_H__ */
