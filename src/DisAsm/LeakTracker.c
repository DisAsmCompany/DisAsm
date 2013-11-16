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

enum {MaxCallStack = 16};

typedef struct Allocation_t
{
	void * address;
    void * heap;
	uint32_t size;
	uint8_t freed;
	address_t callstack[MaxCallStack];
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

typedef struct _IMAGEHLP_MODULE64_V2
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
}
IMAGEHLP_MODULE64_V2, *PIMAGEHLP_MODULE64_V2;

typedef struct _IMAGEHLP_MODULE64_V3
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
IMAGEHLP_MODULE64_V3, *PIMAGEHLP_MODULE64_V3;

#define SYMOPT_CASE_INSENSITIVE         0x00000001
#define SYMOPT_UNDNAME                  0x00000002
#define SYMOPT_DEFERRED_LOADS           0x00000004
#define SYMOPT_NO_CPP                   0x00000008
#define SYMOPT_LOAD_LINES               0x00000010
#define SYMOPT_OMAP_FIND_NEAREST        0x00000020
#define SYMOPT_LOAD_ANYTHING            0x00000040
#define SYMOPT_IGNORE_CVREC             0x00000080
#define SYMOPT_NO_UNQUALIFIED_LOADS     0x00000100
#define SYMOPT_FAIL_CRITICAL_ERRORS     0x00000200
#define SYMOPT_EXACT_SYMBOLS            0x00000400
#define SYMOPT_ALLOW_ABSOLUTE_SYMBOLS   0x00000800
#define SYMOPT_IGNORE_NT_SYMPATH        0x00001000
#define SYMOPT_INCLUDE_32BIT_MODULES    0x00002000
#define SYMOPT_PUBLICS_ONLY             0x00004000
#define SYMOPT_NO_PUBLICS               0x00008000
#define SYMOPT_AUTO_PUBLICS             0x00010000
#define SYMOPT_NO_IMAGE_SEARCH          0x00020000
#define SYMOPT_SECURE                   0x00040000
#define SYMOPT_NO_PROMPTS               0x00080000
#define SYMOPT_OVERWRITE                0x00100000
#define SYMOPT_IGNORE_IMAGEDIR          0x00200000
#define SYMOPT_FLAT_DIRECTORY           0x00400000
#define SYMOPT_FAVOR_COMPRESSED         0x00800000
#define SYMOPT_ALLOW_ZERO_ADDRESS       0x01000000

#define SYMOPT_DEBUG                    0x80000000

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
typedef BOOL (__stdcall *pfnSymGetModuleInfo64)(HANDLE hProcess, DWORD64 qwAddr, PIMAGEHLP_MODULE64_V3 ModuleInfo);
typedef DWORD64 (__stdcall *pfnSymLoadModule64)(HANDLE hProcess, HANDLE hFile, PCSTR ImageName, PCSTR ModuleName, DWORD64 BaseOfDll, DWORD SizeOfDll);

pfnSymInitialize            pSymInitialize            = NULL;
pfnSymCleanup               pSymCleanup               = NULL;
pfnSymGetOptions            pSymGetOptions            = NULL;
pfnSymSetOptions            pSymSetOptions            = NULL;
pfnStackWalk64              pStackWalk64              = NULL;
pfnSymGetSymFromAddr64      pSymGetSymFromAddr64      = NULL;
pfnSymFunctionTableAccess64 pSymFunctionTableAccess64 = NULL;
pfnSymGetModuleBase64       pSymGetModuleBase64       = NULL;
pfnSymGetModuleInfo64       pSymGetModuleInfo64       = NULL;
pfnSymLoadModule64          pSymLoadModule64          = NULL;

enum {NtfsMaxPath = 32768};

typedef struct ModuleInfo_t
{
	address_t address;
	uint32_t size;
	char path[NtfsMaxPath];
	char name[NtfsMaxPath];
}
ModuleInfo;

ModuleInfo * g_Modules = NULL;
uint32_t g_nModules = 0;

char * ShortName(char * name)
{
	char * p = name + strlen(name) - 1;
	for (; p != name; --p)
	{
		if (*p == '\\' || *p == '/' || *p == ':')
		{
			return p;
		}
	}
	return name;
}

void LoadModules(HANDLE hProcess)
{
	HMODULE * modules = NULL;
	DWORD needed = 0;
	DWORD i = 0;
	char exe[NtfsMaxPath];

	GetModuleFileNameA(NULL, exe, NtfsMaxPath);
	EnumProcessModules(hProcess, NULL, 0, &needed);
	g_nModules = needed / 4;
	g_Modules = (ModuleInfo*) malloc(g_nModules * sizeof(ModuleInfo));
	modules = (HMODULE*) malloc(g_nModules * sizeof(HMODULE));
	if (NULL != modules && NULL != g_Modules)
	{
		EnumProcessModules(hProcess, modules, needed, &needed);

		for (i = 0; i < g_nModules; ++i)
		{
			MODULEINFO info = {0};
			IMAGEHLP_MODULE64_V3 info3 = {0};
			info3.SizeOfStruct = sizeof(IMAGEHLP_MODULE64_V3);
			GetModuleInformation(hProcess, modules[i], &info, sizeof(MODULEINFO));
			GetModuleFileNameA(modules[i], g_Modules[i].path, NtfsMaxPath);
			if (!pSymLoadModule64(hProcess, NULL, exe, g_Modules[i].path, info.lpBaseOfDll, info.SizeOfImage))
			{
				fprintf(stderr, "SymLoadModule64 failed for \"%s\"\n", g_Modules[i].path);
			}
			if (!pSymGetModuleInfo64(hProcess, info.lpBaseOfDll, &info3))
			{
				info3.SizeOfStruct = sizeof(IMAGEHLP_MODULE64_V2);
				if (!pSymGetModuleInfo64(hProcess, info.lpBaseOfDll, &info3))
				{
					fprintf(stderr, "SymGetModuleInfo64 failed for \"%s\"\n", g_Modules[i].path);
				}
			}
			g_Modules[i].address = info.lpBaseOfDll;
			g_Modules[i].size = info.SizeOfImage;
			strcpy(g_Modules[i].name, ShortName(g_Modules[i].path) + 1);
		}
	}
	free(modules);
}

HMODULE hDbgHelp = NULL;

void StackWalkInit()
{
	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread  = GetCurrentThread();
	hDbgHelp = LoadLibrary(_T("dbghelp.dll"));
	
	if (NULL != hDbgHelp)
	{
		char path[NtfsMaxPath] = {0};
		char temp[NtfsMaxPath];
		pSymInitialize            = (pfnSymInitialize)            GetProcAddress(hDbgHelp, "SymInitialize");
		pSymCleanup               = (pfnSymCleanup)               GetProcAddress(hDbgHelp, "SymCleanup");
		pSymGetOptions            = (pfnSymGetOptions)            GetProcAddress(hDbgHelp, "SymGetOptions");
		pSymSetOptions            = (pfnSymSetOptions)            GetProcAddress(hDbgHelp, "SymSetOptions");
		pStackWalk64              = (pfnStackWalk64)              GetProcAddress(hDbgHelp, "StackWalk64");
		pSymGetSymFromAddr64      = (pfnSymGetSymFromAddr64)      GetProcAddress(hDbgHelp, "SymGetSymFromAddr64");
		pSymFunctionTableAccess64 = (pfnSymFunctionTableAccess64) GetProcAddress(hDbgHelp, "SymFunctionTableAccess64");
		pSymGetModuleBase64       = (pfnSymGetModuleBase64)       GetProcAddress(hDbgHelp, "SymGetModuleBase64");
		pSymGetModuleInfo64       = (pfnSymGetModuleInfo64)       GetProcAddress(hDbgHelp, "SymGetModuleInfo64");
		pSymLoadModule64          = (pfnSymLoadModule64)          GetProcAddress(hDbgHelp, "SymLoadModule64");

		if (GetCurrentDirectoryA(NtfsMaxPath, temp))
		{
			temp[NtfsMaxPath - 1] = 0;
			strcat(path, temp);
			strcat(path, ";");
		}
		if (GetModuleFileNameA(NULL, temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			ShortName(temp)[0] = 0;
			strcat(path, temp);
			strcat(path, ";");
		}
		if (GetEnvironmentVariableA("_NT_SYMBOL_PATH", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			strcat(path, temp);
			strcat(path, ";");
		}
		if (GetEnvironmentVariableA("_NT_ALTERNATE_SYMBOL_PATH", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			strcat(path, temp);
			strcat(path, ";");
		}
		if (GetEnvironmentVariableA("SYSTEMROOT", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			strcat(path, temp);
			strcat(path, ";");
			strcat(temp, "\\system32");
			strcat(path, temp);
			strcat(path, ";");
		}
		if (GetEnvironmentVariableA("TEMP", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			strcat(path, "SRV*");
			strcat(path, temp);
			strcat(path, "\\websymbols*http://msdl.microsoft.com/download/symbols;");
		}
		else
		{
			strcat(path, "SRC*C:\\temp\\websymbols*http://msdl.microsoft.com/download/symbols;");
		}

		if (pSymInitialize(hProcess, path, false))
		{
			DWORD options = pSymGetOptions();
			options |= SYMOPT_DEBUG;
			pSymSetOptions(options);

			LoadModules(hProcess);
		}
	}
}

void StackWalkSymbol(address_t address)
{
	DWORD i = 0;
	DWORD64 disp;
	enum { MaxNameLength = 1024 }; 
	char buffer[sizeof(IMAGEHLP_SYMBOL64) + MaxNameLength];
	IMAGEHLP_SYMBOL64 * pSymbol = (IMAGEHLP_SYMBOL64*) buffer;
	pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
	pSymbol->MaxNameLength = MaxNameLength;
	
	for (i = 0; i < g_nModules; ++i)
	{
		if (g_Modules[i].address <= address && address <= g_Modules[i].address + g_Modules[i].size)
		{
			printf("%s!", g_Modules[i].name);
			break;
		}
	}
	
	if (pSymGetSymFromAddr64(GetCurrentProcess(), address, &disp, pSymbol))
	{
		if (NULL != pSymbol->Name)
		{
			printf("%s", pSymbol->Name);
		}
	}
}

void StackWalkCleanup()
{
	if (NULL != pSymCleanup)
	{
		pSymCleanup(GetCurrentProcess());
	}
	FreeLibrary(hDbgHelp);
	hDbgHelp = NULL;
}

void StackWalk(address_t * callstack)
{
	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread  = GetCurrentThread();

	CONTEXT context = {0};
	STACKFRAME64 frame = {0};
	DWORD machine = 0;
	DWORD i = 0;
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

	memset(callstack, 0, sizeof(address_t) * MaxCallStack);
	for (i = 0; i < MaxCallStack; ++i)
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
			callstack[i] = frame.AddrPC.Offset;
		}
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
	    g_Allocations[g_nTotalAllocations - 1].freed   = freed;
		StackWalk(g_Allocations[g_nTotalAllocations - 1].callstack);
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
		StackWalkInit();

		g_Allocations = (Allocation*)HeapAlloc(GetProcessHeap(), 0, sizeof(Allocation));

		pOriginalHeapFree    = (pfnHeapFree)   (&xThunkHeapFree);
		pOriginalHeapAlloc   = (pfnHeapAlloc)  (&xThunkHeapAlloc);
		pOriginalHeapReAlloc = (pfnHeapReAlloc)(&xThunkHeapReAlloc);
		pOriginalRtlFreeHeap = (pfnHeapFree)   (&xThunkRtlFreeHeap);
		/* need to capture RtlFreeHeap, because sometimes memory allocated by HeapAlloc
		is being freed directly by this function instead of HeapFree
		but if RtlFreeHeap is the same function as HeapFree, no need to patch twice
		*/

		VirtualProtect(xThunkHeapAlloc,   PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
		VirtualProtect(xThunkHeapReAlloc, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
		VirtualProtect(xThunkHeapFree,    PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
		VirtualProtect(xThunkRtlFreeHeap, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);

		PatchFunction((uint8_t*)HeapReAlloc, (uint8_t*)xHeapReAlloc, xThunkHeapReAlloc);
		PatchFunction((uint8_t*)HeapAlloc,   (uint8_t*)xHeapAlloc,   xThunkHeapAlloc);
		PatchFunction((uint8_t*)HeapFree,    (uint8_t*)xHeapFree,    xThunkHeapFree);
		if (RtlFreeHeap != HeapFree)
		{
			PatchFunction((uint8_t*)RtlFreeHeap, (uint8_t*)xRtlFreeHeap, xThunkRtlFreeHeap);
		}
	}
	else
	{
		uint32_t i = 0;
		uint32_t j = 0;
		uint32_t total = 0;

		RestoreFunction((uint8_t*)HeapAlloc,   xThunkHeapAlloc);
		RestoreFunction((uint8_t*)HeapReAlloc, xThunkHeapReAlloc);
		RestoreFunction((uint8_t*)HeapFree,    xThunkHeapFree);
		if (RtlFreeHeap != HeapFree)
		{
			RestoreFunction((uint8_t*)RtlFreeHeap, xThunkRtlFreeHeap);
		}

		for (i = 0; i < g_nTotalAllocations; ++i)
		{
			if (0 == g_Allocations[i].freed)
			{
				total += g_Allocations[i].size;
				printf("memory leak 0x%08X of %d bytes\n", g_Allocations[i].address, g_Allocations[i].size);

				for (j = 0; j < MaxCallStack; ++j)
				{
					if (0 == g_Allocations[i].callstack[j])
					{
						break;
					}
					printf("0x%08X ", g_Allocations[i].callstack[j]);
					StackWalkSymbol(g_Allocations[i].callstack[j]);
					printf("\n");
				}
				printf("\n");
			}
		}
		printf("total leaked %d bytes\n", total);

		StackWalkCleanup();
	}
}
