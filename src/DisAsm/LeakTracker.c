/*
 * Filename: LeakTracker.h
 * Author:   DisAsmCompany
 * Date:     11/11/2013
 *
 * Description: memory leaks tracker
 *
 *
 *
 */

#include "DisAsm"

/* OpCode for NOP (No Operation - instruction that does nothing) */
static const uint8_t nop = 0x90;
/* OpCode for JMP (Jump) */
static const uint8_t jmp = 0xE9;

typedef void * (__stdcall * pfnHeapAlloc)(void * hHeap, uint32_t flags, uint32_t size);
typedef void * (__stdcall * pfnHeapReAlloc)(void * hHeap, uint32_t flags, void * memory, uint32_t size);
typedef int (__stdcall * pfnHeapFree)(void * hHeap, uint32_t flags, LPVOID lpMem);

static pfnHeapFree pOriginalRtlFreeHeap = NULL;
static pfnHeapAlloc pOriginalHeapAlloc = NULL;
static pfnHeapReAlloc pOriginalHeapReAlloc = NULL;
static pfnHeapFree pOriginalHeapFree = NULL;

#define PAGE_SIZE 4096
#define THUNK_SIZE 20
uint8_t xThunkHeapAlloc[2 * THUNK_SIZE], xThunkHeapReAlloc[2 * THUNK_SIZE], xThunkHeapFree[2 * THUNK_SIZE], xThunkRtlFreeHeap[2 * THUNK_SIZE];

typedef struct Allocation_t
{
	void * address;
    void * heap;
	uint32_t size;
	uint8_t freed;
}
Allocation;

static size_t g_nActiveAllocations = 0;
static size_t g_nTotalAllocations = 0;
static size_t g_nCapacity = 0;

Allocation * g_Allocations = NULL;

static bool xHeapCalled = false;

typedef enum
{
	AddrMode1616,
	AddrMode1632,
	AddrModeReal,
	AddrModeFlat
}
ADDRESS_MODE;

typedef struct _tagADDRESS64
{
	DWORD64       Offset;
	WORD          Segment;
	ADDRESS_MODE  Mode;
}
ADDRESS64, *LPADDRESS64;

typedef struct _KDHELP64
{
	DWORD64   Thread;
	DWORD   ThCallbackStack;
	DWORD   ThCallbackBStore;
	DWORD   NextCallback;
	DWORD   FramePointer;
	DWORD64   KiCallUserMode;
	DWORD64   KeUserCallbackDispatcher;
	DWORD64   SystemRangeStart;
	DWORD64   KiUserExceptionDispatcher;
	DWORD64   StackBase;
	DWORD64   StackLimit;
	DWORD64   Reserved[5];
}
KDHELP64, *PKDHELP64;

typedef struct _tagSTACKFRAME64
{
	ADDRESS64   AddrPC;
	ADDRESS64   AddrReturn;
	ADDRESS64   AddrFrame;
	ADDRESS64   AddrStack;
	ADDRESS64   AddrBStore;
	PVOID       FuncTableEntry;
	DWORD64     Params[4];
	BOOL        Far;
	BOOL        Virtual;
	DWORD64     Reserved[3];
	KDHELP64    KdHelp;
}
STACKFRAME64, *LPSTACKFRAME64;

typedef struct _IMAGEHLP_SYMBOL64
{
	DWORD   SizeOfStruct;
	DWORD64 Address;
	DWORD   Size; 
	DWORD   Flags;
	DWORD   MaxNameLength;
	CHAR    Name[1];
}
IMAGEHLP_SYMBOL64, *PIMAGEHLP_SYMBOL64;

typedef enum
{
	SymNone = 0,
	SymCoff,
	SymCv,
	SymPdb,
	SymExport,
	SymDeferred,
	SymSym,
	SymDia,
	SymVirtual,
	NumSymTypes
}
SYM_TYPE;

typedef struct _IMAGEHLP_MODULE64
{
	DWORD    SizeOfStruct;
	DWORD64  BaseOfImage;
	DWORD    ImageSize;
	DWORD    TimeDateStamp;
	DWORD    CheckSum;
	DWORD    NumSyms;
	SYM_TYPE SymType;
	CHAR     ModuleName[32];
	CHAR     ImageName[256];
	CHAR     LoadedImageName[256];
	CHAR     LoadedPdbName[256];
	DWORD    CVSig;
	CHAR     CVData[MAX_PATH * 3];
	DWORD    PdbSig;
	GUID     PdbSig70;
	DWORD    PdbAge;
	BOOL     PdbUnmatched;
	BOOL     DbgUnmatched;
	BOOL     LineNumbers;
	BOOL     GlobalSymbols;
	BOOL     TypeInfo;
	BOOL     SourceIndexed;
	BOOL     Publics;
}
IMAGEHLP_MODULE64, *PIMAGEHLP_MODULE64;

typedef BOOL (__stdcall *PREAD_PROCESS_MEMORY_ROUTINE64)(HANDLE hProcess, DWORD64 qwBaseAddress, 
														 PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);
typedef PVOID (__stdcall *PFUNCTION_TABLE_ACCESS_ROUTINE64)(HANDLE ahProcess, DWORD64 AddrBase);
typedef DWORD64 (__stdcall *PGET_MODULE_BASE_ROUTINE64)(HANDLE hProcess, DWORD64 Address);
typedef DWORD64 (__stdcall *PTRANSLATE_ADDRESS_ROUTINE64)(HANDLE hProcess, HANDLE hThread, LPADDRESS64 lpaddr);

typedef BOOL  (__stdcall *pfnSymInitialize)(HANDLE hProcess, PCSTR UserSearchPath, BOOL fInvadeProcess);
typedef BOOL  (__stdcall *pfnSymCleanup)(HANDLE hProcess);
typedef DWORD (__stdcall *pfnSymSetOptions)(DWORD SymOptions);
typedef DWORD (__stdcall *pfnSymGetOptions)();
typedef BOOL  (__stdcall *pfnStackWalk64)(DWORD MachineType, HANDLE hProcess, HANDLE hThread,
										  LPSTACKFRAME64 StackFrame, PVOID ContextRecord,
										  PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
										  PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
										  PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine,
										  PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress);
typedef BOOL  (__stdcall *pfnSymGetSymFromAddr64)(HANDLE hProcess, DWORD64 qwAddr, PDWORD64 pdwDisplacement, PIMAGEHLP_SYMBOL64 Symbol);
typedef PVOID (__stdcall *pfnSymFunctionTableAccess64)(HANDLE hProcess, DWORD64 AddrBase);
typedef DWORD64 (__stdcall *pfnSymGetModuleBase64)(HANDLE hProcess, DWORD64 qwAddr);
typedef BOOL (__stdcall *pfnSymGetModuleInfo64)(HANDLE hProcess, DWORD64 qwAddr, PIMAGEHLP_MODULE64 ModuleInfo);

pfnSymInitialize            pSymInitialize            = NULL;
pfnSymCleanup               pSymCleanup               = NULL;
pfnSymGetOptions            pSymGetOptions            = NULL;
pfnSymSetOptions            pSymSetOptions            = NULL;
pfnStackWalk64              pStackWalk64              = NULL;
pfnSymGetSymFromAddr64      pSymGetSymFromAddr64      = NULL;
pfnSymFunctionTableAccess64 pSymFunctionTableAccess64 = NULL;
pfnSymGetModuleBase64       pSymGetModuleBase64       = NULL;
pfnSymGetModuleInfo64       pSymGetModuleInfo64       = NULL;

void StackWalk()
{
	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread  = GetCurrentThread();
	HMODULE hModule = LoadLibrary(_T("dbghelp.dll"));
	if (NULL != hModule)
	{
		pSymInitialize            = (pfnSymInitialize)            GetProcAddress(hModule, "SymInitialize");
		pSymCleanup               = (pfnSymCleanup)               GetProcAddress(hModule, "SymCleanup");
		pSymGetOptions            = (pfnSymGetOptions)            GetProcAddress(hModule, "SymGetOptions");
		pSymSetOptions            = (pfnSymSetOptions)            GetProcAddress(hModule, "SymSetOptions");
		pStackWalk64              = (pfnStackWalk64)              GetProcAddress(hModule, "StackWalk64");
		pSymGetSymFromAddr64      = (pfnSymGetSymFromAddr64)      GetProcAddress(hModule, "SymGetSymFromAddr64");
		pSymFunctionTableAccess64 = (pfnSymFunctionTableAccess64) GetProcAddress(hModule, "SymFunctionTableAccess64");
		pSymGetModuleBase64       = (pfnSymGetModuleBase64)       GetProcAddress(hModule, "SymGetModuleBase64");
		pSymGetModuleInfo64       = (pfnSymGetModuleInfo64)       GetProcAddress(hModule, "SymGetModuleInfo64");

		if (pSymInitialize(hProcess, NULL, false))
		{
			DWORD i = 0;
			DWORD * modules = NULL;
			DWORD needed = 0;
			CONTEXT context = {0};
			STACKFRAME64 frame = {0};
			DWORD machine = 0;
			enum { MaxNameLength = 1024 }; 
			IMAGEHLP_SYMBOL64 * pSymbol = (IMAGEHLP_SYMBOL64*) malloc(sizeof(IMAGEHLP_SYMBOL64) + MaxNameLength);
			pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
			pSymbol->MaxNameLength = MaxNameLength;
			RtlCaptureContext(&context);
#ifdef _M_IX86
			machine = IMAGE_FILE_MACHINE_I386;
			frame.AddrPC.Offset    = context.Eip;
			frame.AddrPC.Mode      = AddrModeFlat;
			frame.AddrFrame.Offset = context.Ebp;
			frame.AddrFrame.Mode   = AddrModeFlat;
			frame.AddrStack.Offset = context.Esp;
			frame.AddrStack.Mode   = AddrModeFlat;
#endif /* _M_IX86 */
#ifdef _M_X64
			machine = IMAGE_FILE_MACHINE_AMD64;
#endif /* _M_IA64 */
#ifdef _M_X64
			machine = IMAGE_FILE_MACHINE_IA64;
#endif /* _M_IA64 */

			EnumProcessModules(hProcess, NULL, 0, &needed);
			modules = (DWORD*) malloc(needed / 4);
			EnumProcessModules(hProcess, (HMODULE*)modules, needed, &needed);
			for (i = 0; i < needed / 4; ++i)
			{
				IMAGEHLP_MODULE64 info;
				info.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
				if (!pSymGetModuleInfo64(hProcess, modules[i], &info))
				{
					int x = 0;
				}
				else
				{
					int x = 0;
				}
			}

			for (;;)
			{
				if (!pStackWalk64(machine, hProcess, hThread, &frame, &context, NULL, pSymFunctionTableAccess64, pSymGetModuleBase64, NULL))
				{
					break;
				}
				if (0 == frame.AddrReturn.Offset)
				{
					break;
				}
				if (0 != frame.AddrPC.Offset)
				{
					DWORD64 disp;
					if (pSymGetSymFromAddr64(hProcess, frame.AddrPC.Offset, &disp, pSymbol))
					{
						int x = 0;
					}
				}
				printf("0x%08X\n", frame.AddrPC.Offset);
			}

			pSymCleanup(hProcess);
		}
		FreeLibrary(hModule);
	}
}

uint32_t xFindAllocation(void * address, void * heap)
{
	uint32_t i = 0;
	for (i = 0; i < g_nTotalAllocations; ++i)
	{
		if (g_Allocations[i].address == address && g_Allocations[i].heap == heap)
		{
			return i;
		}
	}
	return 0xFFFFFFFFUL;
}

void xUpdateAllocation(void * address, void * heap, uint32_t size, uint8_t freed);

void xAddAllocation(void * address, void * heap, uint32_t size, uint8_t freed)
{
    size_t index = xFindAllocation(address, heap);
    if (0xFFFFFFFFUL != index)
    {
		/* already has entry for allocation, so just update it */
        xUpdateAllocation(address, heap, size, freed);
    }
    else
    {
        ++g_nActiveAllocations;
        ++g_nTotalAllocations;
	    if (g_nTotalAllocations >= g_nCapacity)
	    {
		    g_nCapacity += 1024; /* linear grow */
			if (!g_Allocations)
			{
				g_Allocations = (Allocation*) pOriginalHeapAlloc(GetProcessHeap(), 0, g_nCapacity * sizeof(Allocation));
			}
			else
			{
				g_Allocations = (Allocation*) pOriginalHeapReAlloc(GetProcessHeap(), 0, g_Allocations, g_nCapacity * sizeof(Allocation));
				if (!g_Allocations)
				{
					/* if realloc fails, then try to do new alloc, then copy data */
					Allocation * allocations = (Allocation*) pOriginalHeapAlloc(GetProcessHeap(), 0, g_nCapacity * sizeof(Allocation));
					if (allocations)
					{
						memcpy(allocations, g_Allocations, (g_nCapacity - 1024) * sizeof(Allocation));
						pOriginalHeapFree(GetProcessHeap(), 0, g_Allocations);
						g_Allocations = allocations;
					}
				}
			}
			if (!g_Allocations)
		    {
			    DebugBreak();
		    }
	    }
	    g_Allocations[g_nTotalAllocations - 1].address = address;
	    g_Allocations[g_nTotalAllocations - 1].heap    = heap;
        g_Allocations[g_nTotalAllocations - 1].size    = size;
	    g_Allocations[g_nTotalAllocations - 1].freed   = false;
    }
}

void xUpdateAllocation(void * address, void * heap, uint32_t size, uint8_t freed)
{
	size_t index = xFindAllocation(address, heap);
	if (0xFFFFFFFFUL != index)
	{
		g_Allocations[index].address = address;
        g_Allocations[index].heap    = heap;
		g_Allocations[index].size    = freed ? g_Allocations[index].size : size;
		g_Allocations[index].freed   = freed;
	}
	else
	{
		xAddAllocation(address, heap, size, freed);
		if (freed) --g_nActiveAllocations;
	}
}

void * __stdcall xHeapAlloc(void * heap, uint32_t flags, uint32_t size)
{
	void * result = NULL;
	if (xHeapCalled)
	{
		return pOriginalHeapAlloc(heap, flags, size);
	}
	xHeapCalled = true;
	result = pOriginalHeapAlloc(heap, flags, size);
	if (NULL != result)
	{
		xAddAllocation(result, heap, size, false);
	}
	xHeapCalled = false;
	return result;
}

void * __stdcall xHeapReAlloc(void * heap, uint32_t flags, void * memory, uint32_t size)
{
	void * result = NULL;
	if (xHeapCalled)
	{
		return pOriginalHeapReAlloc(heap, flags, memory, size);
	}
	xHeapCalled = true;
	result = pOriginalHeapReAlloc(heap, flags, memory, size);
	if (NULL != result)
	{
		if (result == memory) 
		{
			/* same address, just update it */
			xUpdateAllocation(result, heap, size, false);
		}
		else
		{
			/* new address : mark old as freed and add entry for new */
			xUpdateAllocation(memory, heap, 0, true);
			xAddAllocation(result, heap, size, false);
		}
	}
	xHeapCalled = false;
	return result;
}

int __stdcall xHeapFree(void * heap, uint32_t flags, void * memory)
{
	int result = 0;
	if (xHeapCalled)
	{
		return pOriginalHeapFree(heap, flags, memory);
	}
	xHeapCalled = true;
	result = pOriginalHeapFree(heap, flags, memory);
	if (result && NULL != memory)
	{
		xUpdateAllocation(memory, heap, 0, true);
	}
	xHeapCalled = false;
	return result;
}

int __stdcall xRtlFreeHeap(void * heap, uint32_t flags, void * memory)
{
    int result = 0;
    if (xHeapCalled)
    {
        return pOriginalRtlFreeHeap(heap, flags, memory);
    }
    xHeapCalled = true;
    result = pOriginalRtlFreeHeap(heap, flags, memory);
    if (result && NULL != memory)
    {
        xUpdateAllocation(memory, heap, 0, true);
    }
    xHeapCalled = false;
    return result;
}

address_t CalculateOffsetForJMP(address_t from, address_t to)
{
	/* 5 is size of JMP instruction itself */
	return to - from - 5;
}

typedef struct CallbackData_t
{
    uint8_t * pBuffer;
    uint32_t offset;
}
CallbackData;

int CallbackRead(ReaderContext * pContext, void * buffer, uint32_t size)
{
    CallbackData * pData = (CallbackData*) pContext->pPrivate;
    memcpy(buffer, pData->pBuffer + pData->offset, size);
    pData->offset += size;
    return 1;
}

int CallbackSeek(ReaderContext * pContext, uint32_t pos)
{
    CallbackData * pData = (CallbackData*) pContext->pPrivate;
    pData->offset = pos;
    return 1;
}

int CallbackSkip(ReaderContext * pContext, uint32_t count)
{
    CallbackData * pData = (CallbackData*) pContext->pPrivate;
    pData->offset += count;
    return 1;
}

uint32_t PatchLength(uint8_t * pData, uint8_t * pOut, uint32_t required)
{
    uint32_t total = 0;
    CallbackData data;
    ReaderContext reader;
    reader.pRead    = CallbackRead;
    reader.pSkip    = CallbackSkip;
    reader.pSeek    = CallbackSeek;
    reader.pPrivate = &data;
    reader.pDestroy = NULL;

    data.pBuffer = pData;
    data.offset = 0;
	
	while (total < required)
	{
#ifdef _M_X64
        uint32_t length = DisAsmInstructionDecode(64, &reader, NULL);
#else /* _M_X64 */
        uint32_t length = DisAsmInstructionDecode(32, &reader, NULL);
#endif /* _M_X64 */
		if (0 == length)
		{
			return 0;
		}
		if (jmp == pData[total])
		{
			uint32_t offset = 0;
			/* we're unlucky enough - patched function starts from relative jump (JMP) that need to be corrected */
			memcpy(&offset, pData + total + 1, 4);
			/* math is simple :
			old offset = destination - original
			destination = old offset + original
			new offset = destination - thunk = old offset + original - thunk
			*/
			offset = offset + pData - pOut;
			memcpy(pOut + total + 1, &offset, 4);
			pOut[total] = jmp;
		}
		else
		{
			memcpy(pOut + total, pData + total, length);
		}
		total += length;
	}
	return total;
}

void PatchFunction(uint8_t * pOriginal, uint8_t * pHook, uint8_t * pThunk)
{
	uint32_t protect = 0;
	uint32_t length = 0;
	address_t offset = CalculateOffsetForJMP((address_t)pOriginal, (address_t)pHook);

	memset(pThunk, nop, 2 * THUNK_SIZE);

    if (0 == (length = PatchLength(pOriginal, pThunk, 5)))
    {
        return;
    }
	
	VirtualProtect(pOriginal, PAGE_SIZE, PAGE_READWRITE, &protect);
	pOriginal[0] = jmp;
	memcpy(pOriginal + 1, &offset, 4);
	memset(pOriginal + 5, nop, length - 5);
	VirtualProtect(pOriginal, PAGE_SIZE, protect, &protect);

	offset = CalculateOffsetForJMP((address_t)(pThunk + THUNK_SIZE), (address_t)(pOriginal + length));
	pThunk[THUNK_SIZE] = jmp;
	memcpy(pThunk + THUNK_SIZE + 1, &offset, 4);
}

void RestoreFunction(uint8_t * pOriginal, uint8_t * pThunk)
{
	uint32_t protect = 0;

	VirtualProtect(pOriginal, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
	PatchLength(pThunk, pOriginal, 5);
	VirtualProtect(pOriginal, PAGE_SIZE, protect, &protect);
}

void LeakTrackerInstall(uint8_t install)
{
	uint32_t protect = 0;

    HMODULE hModule = GetModuleHandleA("ntdll.dll");
    void * RtlFreeHeap = GetProcAddress(hModule, "RtlFreeHeap");

	if (install)
	{
		g_Allocations = (Allocation*)HeapAlloc(GetProcessHeap(), 0, sizeof(Allocation));

		/* need to capture RtlFreeHeap, because sometimes memory allocated by HeapAlloc
		is being freed directly by this function instead of HeapFree */
        pOriginalRtlFreeHeap = (pfnHeapFree)   (&xThunkRtlFreeHeap);
		pOriginalHeapAlloc   = (pfnHeapAlloc)  (&xThunkHeapAlloc);
		pOriginalHeapReAlloc = (pfnHeapReAlloc)(&xThunkHeapReAlloc);
		pOriginalHeapFree    = (pfnHeapFree)   (&xThunkHeapFree);

		VirtualProtect(xThunkHeapAlloc,   PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
		VirtualProtect(xThunkHeapReAlloc, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
		VirtualProtect(xThunkHeapFree,    PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);

		PatchFunction((uint8_t*)HeapReAlloc, (uint8_t*)xHeapReAlloc, xThunkHeapReAlloc);
		PatchFunction((uint8_t*)HeapAlloc,   (uint8_t*)xHeapAlloc,   xThunkHeapAlloc);
		PatchFunction((uint8_t*)HeapFree,    (uint8_t*)xHeapFree,    xThunkHeapFree);
        PatchFunction((uint8_t*)RtlFreeHeap, (uint8_t*)xRtlFreeHeap, xThunkRtlFreeHeap);
	}
	else
	{
		uint32_t i = 0;
		uint32_t total = 0;

		RestoreFunction((uint8_t*)HeapAlloc,   xThunkHeapAlloc);
		RestoreFunction((uint8_t*)HeapReAlloc, xThunkHeapReAlloc);
		RestoreFunction((uint8_t*)HeapFree,    xThunkHeapFree);
        RestoreFunction((uint8_t*)RtlFreeHeap, xThunkRtlFreeHeap);

		for (i = 0; i < g_nTotalAllocations; ++i)
		{
			if (0 == g_Allocations[i].freed)
			{
				total += g_Allocations[i].size;
				printf("memory leak 0x%08X of %d bytes\n", g_Allocations[i].address, g_Allocations[i].size);
			}
		}
		printf("total leaked %d bytes\n", total);
	}
}
