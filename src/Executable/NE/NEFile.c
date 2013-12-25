/*
 * Filename: NEFile.h
 * Author:   DisAsmCompany
 * Date:     26/10/2013
 *
 * Description: NE file abstraction
 *              (New Executable)
 *
 *
 */

#include "../../DisAsm/DisAsm"
#include "../Executable"

#include "../MZ/MZDOSHeader.h"
#include "NESegmentedHeader.h"

typedef struct NEFileContext_t
{
	HSDF hDOSHeader;
	HSDF hSegmentedHeader;
	uint32_t AddressNE;
}
NEFileContext;

#undef THIS
#define THIS ((NEFileContext*)(OBJ.pPrivate))

int NEReadStringTable(ExecutableContext * pContext)
{
	uint8_t length = 0;
	char * buffer = NULL;
	uint16_t ordinal = 0;

	for (;;)
	{
		CHECK_CALL(ReaderRead(pContext->hReader, &length, sizeof(uint8_t)));
		if (0 == length)
		{
			break;
		}
		CHECK_ALLOC(buffer = (char*) calloc(1, length + 1));
		CHECK_CALL(ReaderRead(pContext->hReader, buffer, length));
		CHECK_CALL(ReaderRead(pContext->hReader, &ordinal, sizeof(uint16_t)));
		buffer[length] = 0;

		free(buffer);
	}
	return 1;
}

int NEFileOpen(ExecutableContext * pContext)
{
	uint16_t Signature;
	uint32_t Offset;

	CHECK_ALLOC(pContext->pObjects = (ExecutableObject*) calloc(1, sizeof(ExecutableObject)));
	pContext->iObject  = 0;
	pContext->nObjects = 1;
	CHECK_ALLOC(OBJ.pPrivate = calloc(1, sizeof(NEFileContext)));

	CHECK_CALL(ReaderSeek(pContext->hReader, 0));
	CHECK_CALL(THIS->hDOSHeader = SDFCreate(MZDOSHeader, pContext->hReader));
	if (kMZDOSSignature != SDFReadUInt16(THIS->hDOSHeader, MZDOSHeaderSignature))
	{
		return 0;
	}
	THIS->AddressNE = SDFReadUInt32(THIS->hDOSHeader, MZDOSHeaderAddressNew);
	CHECK_CALL(ReaderSeek(pContext->hReader, THIS->AddressNE));
	CHECK_CALL(ReaderRead(pContext->hReader, &Signature, sizeof(uint16_t)));
	if (kNESignature != Signature)
	{
		return 0;
	}
	CHECK_CALL(THIS->hSegmentedHeader = SDFCreate(NESegmentedHeader, pContext->hReader));
	SDFDebugPrint(THIS->hDOSHeader);
	SDFDebugPrint(THIS->hSegmentedHeader);

	Offset = SDFReadUInt16(THIS->hSegmentedHeader, NESegmentedHeaderResidentNamesTableOffset);
	if (0 != Offset)
	{
		CHECK_CALL(ReaderSeek(pContext->hReader, THIS->AddressNE + Offset));
		CHECK_CALL(NEReadStringTable(pContext));
	}
	Offset = SDFReadUInt32(THIS->hSegmentedHeader, NESegmentedHeaderNonResidentNamesTableOffset);
	if (0 != Offset)
	{
		CHECK_CALL(ReaderSeek(pContext->hReader, Offset));
		CHECK_CALL(NEReadStringTable(pContext));
	}
	OBJ.Arch = ArchX86;
	OBJ.StubEntryPoint = SDFSizeInBytes(MZDOSHeader);
	return 1;
}

void NEFileDestroy(ExecutableContext * pContext)
{
	for (pContext->iObject = 0; pContext->iObject < pContext->nObjects; ++pContext->iObject)
	{
		SDFDestroy(THIS->hDOSHeader);
		SDFDestroy(THIS->hSegmentedHeader);
		free(THIS);
	}
}

int NEFileCreate(ExecutableContext * pContext)
{
	pContext->pDestroy = NEFileDestroy;

	if (0 == NEFileOpen(pContext))
	{
		ExecutableFree(pContext);
		return 0;
	}
	return 1;
}
