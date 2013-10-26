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
#define THIS ((NEFileContext*)(pContext->pPrivate))

#define CHECK_CALL(x) do { if (0 == (x)) return 0; } while (0);
#define CHECK_ALLOC(x) do { if (NULL == (x)) return 0; } while (0);

int NEFileOpen(ExecutableContext * pContext)
{
	uint16_t Signature;

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
	SDFPrint(THIS->hDOSHeader);
	SDFPrint(THIS->hSegmentedHeader);

	pContext->Arch = ArchX86;
	pContext->StubEntryPoint = SDFSizeInBytes(MZDOSHeader);
	return 1;
}

void NEFileDestroy(ExecutableContext * pContext)
{
	SDFDestroy(THIS->hDOSHeader);
	SDFDestroy(THIS->hSegmentedHeader);
	free(THIS);
}

int NEFileCreate(ExecutableContext * pContext)
{
	NEFileContext * pNEFileContext = (NEFileContext*) malloc(sizeof(NEFileContext));
	if (NULL == pNEFileContext)
	{
		return 0;
	}
	memset(pNEFileContext, 0, sizeof(NEFileContext));
	pContext->pPrivate = pNEFileContext;

	if (0 == NEFileOpen(pContext))
	{
		NEFileDestroy(pContext);
		return 0;
	}

	pContext->pDestroy                = NEFileDestroy;

	return 1;
}
