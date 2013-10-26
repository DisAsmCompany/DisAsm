/*
 * Filename: LXFile.h
 * Author:   DisAsmCompany
 * Date:     26/10/2013
 *
 * Description: LX/LE file abstraction
 *              (Linear Executable)
 *
 *
 */

#include "../../DisAsm/DisAsm"
#include "../Executable"

#include "../MZ/MZDOSHeader.h"
#include "LXOrdering.h"
#include "LXCPUType.h"
#include "LXOSType.h"
#include "LXFileHeader.h"
#include "LXObjectTable.h"

typedef struct LXFileContext_t
{
	HSDF hDOSHeader;
	HSDF hFileHeader;
	HSDF * phObjectTable;
	uint32_t AddressLX;
	uint32_t NumberOfObjects;
}
LXFileContext;

#undef THIS
#define THIS ((LXFileContext*)(pContext->pPrivate))

int LXFileOpen(ExecutableContext * pContext)
{
	uint16_t Signature = 0;
	uint32_t Offset = 0;
	uint32_t Count  = 0;
	uint32_t EIP = 0;
	uint32_t EIPObject = 0;
	uint32_t i = 0;

	CHECK_CALL(ReaderSeek(pContext->hReader, 0));
	CHECK_CALL(THIS->hDOSHeader = SDFCreate(MZDOSHeader, pContext->hReader));
	if (kMZDOSSignature != SDFReadUInt16(THIS->hDOSHeader, MZDOSHeaderSignature))
	{
		return 0;
	}
	THIS->AddressLX = SDFReadUInt32(THIS->hDOSHeader, MZDOSHeaderAddressNew);
	CHECK_CALL(ReaderSeek(pContext->hReader, THIS->AddressLX));
	CHECK_CALL(ReaderRead(pContext->hReader, &Signature, sizeof(uint16_t)));
	if (kLXSignature != Signature && kLESignature != Signature)
	{
		return 0;
	}
	CHECK_CALL(THIS->hFileHeader = SDFCreate(LXFileHeader, pContext->hReader));
	SDFPrint(THIS->hDOSHeader);
	SDFPrint(THIS->hFileHeader);

	EIP       = SDFReadUInt32(THIS->hFileHeader, LXFileHeaderObjectEIP);
	EIPObject = SDFReadUInt32(THIS->hFileHeader, LXFileHeaderObjectEIPObject);
	Offset    = SDFReadUInt32(THIS->hFileHeader, LXFileHeaderObjectTableOffset);
	Count     = SDFReadUInt32(THIS->hFileHeader, LXFileHeaderObjectTableCount);

	if (0 == Count)
	{
		return 0;
	}
	THIS->NumberOfObjects = Count;

	CHECK_ALLOC(THIS->phObjectTable = (HSDF*) malloc(sizeof(HSDF) * THIS->NumberOfObjects));
	CHECK_CALL(ReaderSeek(pContext->hReader, THIS->AddressLX + Offset));
	for (i = 0; i < THIS->NumberOfObjects; ++i)
	{
		THIS->phObjectTable[i] = SDFCreate(LXObjectTable, pContext->hReader);

		SDFPrint(THIS->phObjectTable[i]);
	}
	pContext->Arch = ArchX86;
	return 1;
}

void LXFileDestroy(ExecutableContext * pContext)
{
	uint32_t i = 0;
	for (i = 0; i < THIS->NumberOfObjects; ++i)
	{
		SDFDestroy(THIS->phObjectTable[i]);
	}
	free(THIS->phObjectTable);
	SDFDestroy(THIS->hDOSHeader);
	SDFDestroy(THIS->hFileHeader);
	free(THIS);
}

int LXFileCreate(ExecutableContext * pContext)
{
	CHECK_ALLOC(pContext->pPrivate = calloc(1, sizeof(LXFileContext)));

	if (0 == LXFileOpen(pContext))
	{
		LXFileDestroy(pContext);
		return 0;
	}
	pContext->pDestroy = LXFileDestroy;

	return 1;
}
