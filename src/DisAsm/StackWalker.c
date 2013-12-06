/*
 * Filename: StackWalker.c
 * Author:   DisAsmCompany
 * Date:     16/11/2013
 *
 * Description: stack walker - used to capture callstack
 *              for example by crash handler or leak tracker
 *
 *
 */

#include "DisAsm"

#ifdef OS_WINDOWS

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

ModuleInfo * g_Modules = NULL;
uint32_t g_nModules = 0;

void LoadModules(HANDLE hProcess)
{
	uint32_t i;
	char exe[NtfsMaxPath];

	GetModuleFileNameA(NULL, exe, NtfsMaxPath);
	g_nModules = ModuleEnum(&g_Modules);

	for (i = 0; i < g_nModules; ++i)
	{
		IMAGEHLP_MODULE64_V3 info3 = {0};
		info3.SizeOfStruct = sizeof(IMAGEHLP_MODULE64_V3);
		if (!pSymLoadModule64(hProcess, NULL, exe, g_Modules[i].path, g_Modules[i].address, g_Modules[i].size))
		{
			ConsoleIOPrintFormatted("SymLoadModule64 failed for \"%s\"\n", g_Modules[i].path);
		}
		if (!pSymGetModuleInfo64(hProcess, g_Modules[i].address, &info3))
		{
			info3.SizeOfStruct = sizeof(IMAGEHLP_MODULE64_V2);
			if (!pSymGetModuleInfo64(hProcess, g_Modules[i].address, &info3))
			{
				ConsoleIOPrintFormatted("SymGetModuleInfo64 failed for \"%s\"\n", g_Modules[i].path);
			}
		}
	}
}

HMODULE hDbgHelp = NULL;

void StackWalkInit()
{
	HANDLE hProcess = GetCurrentProcess();
	hDbgHelp = LoadLibraryA("dbghelp.dll");

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
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetModuleFileNameA(NULL, temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			ShortName(temp)[0] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetEnvironmentVariableA("_NT_SYMBOL_PATH", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetEnvironmentVariableA("_NT_ALTERNATE_SYMBOL_PATH", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetEnvironmentVariableA("SYSTEMROOT", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
			xstrcat(temp, NtfsMaxPath, "\\system32");
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, ";");
		}
		if (GetEnvironmentVariableA("TEMP", temp, NtfsMaxPath))
		{
			temp[NtfsMaxPath - 1] = 0;
			xstrcat(path, NtfsMaxPath, "SRV*");
			xstrcat(path, NtfsMaxPath, temp);
			xstrcat(path, NtfsMaxPath, "\\websymbols*http://msdl.microsoft.com/download/symbols;");
		}
		else
		{
			xstrcat(path, NtfsMaxPath, "SRC*C:\\temp\\websymbols*http://msdl.microsoft.com/download/symbols;");
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

void StackWalkSymbol(native_t address)
{
	DWORD i;
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
			ConsoleIOPrintFormatted("%s!", g_Modules[i].name);
			break;
		}
	}

	if (pSymGetSymFromAddr64(GetCurrentProcess(), address, &disp, pSymbol))
	{
		if (NULL != pSymbol->Name)
		{
			ConsoleIOPrintFormatted("%s", pSymbol->Name);
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

#ifndef GETCONTEXT
#ifdef CPU_X86
#ifdef COMP_MICROSOFTC
#define GETCONTEXT(c) \
do \
{ \
	__asm    call x \
	__asm x: pop eax \
	__asm    mov c.Eip, eax \
	__asm    mov c.Ebp, ebp \
	__asm    mov c.Esp, esp \
} \
while(0);
#else /* COMP_MICROSOFTC */
#define GETCONTEXT(c)
#endif /* COMP_MICROSOFTC */
#else /* CPU_X86 */
#define GETCONTEXT(c) do { RtlCaptureContext(&context); } while (0);
#endif /* CPU_X86 */
#endif /* GETCONTEXT */

void StackWalk(native_t * callstack, Context * pContext)
{
	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread  = GetCurrentThread();

	CONTEXT context = {0};
	STACKFRAME64 frame = {0};
	DWORD machine = 0;
	DWORD i = 0;
	if (NULL == pContext)
	{
		GETCONTEXT(context);
	}
	else
	{
#ifdef CPU_X86
		context.Eip = (uint32_t) pContext->InstructionPointer;
		context.Esp = (uint32_t) pContext->StackFramePointer;
		context.Ebp = (uint32_t) pContext->StackBasePointer;
#endif /* CPU_X86 */
#ifdef CPU_X64
		context.Rip = (uint32_t) pContext->InstructionPointer;
		context.Rsp = (uint32_t) pContext->StackFramePointer;
		context.Rbp = (uint32_t) pContext->StackBasePointer;
#endif /* CPU_X64 */
	}
	context.ContextFlags = CONTEXT_FULL;
#ifdef CPU_X86
	machine = IMAGE_FILE_MACHINE_I386;
	frame.AddrPC.Offset    = context.Eip;
	frame.AddrPC.Mode      = AddrModeFlat;
	frame.AddrFrame.Offset = context.Ebp;
	frame.AddrFrame.Mode   = AddrModeFlat;
	frame.AddrStack.Offset = context.Esp;
	frame.AddrStack.Mode   = AddrModeFlat;
#endif /* CPU_X86 */
#ifdef CPU_X64
	machine = IMAGE_FILE_MACHINE_AMD64;
	frame.AddrPC.Offset    = context.Rip;
	frame.AddrPC.Mode      = AddrModeFlat;
	frame.AddrFrame.Offset = context.Rbp;
	frame.AddrFrame.Mode   = AddrModeFlat;
	frame.AddrStack.Offset = context.Rsp;
	frame.AddrStack.Mode   = AddrModeFlat;
#endif /* CPU_X64 */
#ifdef CPU_IA64
	machine = IMAGE_FILE_MACHINE_IA64;
#endif /* CPU_IA64 */
	memset(callstack, 0, sizeof(native_t) * MaxCallStack);
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
			callstack[i] = (native_t) frame.AddrPC.Offset;
		}
	}
}

#else /* OS_WINDOWS */

void StackWalkInit() {}
void StackWalkCleanup() {}
void StackWalk(native_t * callstack, Context * context)
{
	void **frame = (void**) __builtin_frame_address(0);
	void **bp = (void**) (*frame);
	void *ip = frame[1];
	
	int i;
	for (i = 0; bp && ip && i < MaxCallStack; ++i)
	{
		callstack[i] = (native_t)ip;
		ip = bp[1];
		bp = (void**)(bp[0]);
	}
}

void StackWalkSymbol(native_t address)
{
/* cygwin doesn't have Dl_info and dladdr */
#ifndef OS_CYGWIN
	Dl_info info = {0};
	
	ConsoleIOPrintFormatted("%08X", address);
	if (0 != dladdr((void*)address, &info))
	{
		if (NULL != info.dli_sname)
		{
			const char * symbol = info.dli_sname;
			ConsoleIOPrintFormatted(" %s", symbol);
		}
	}
#endif /* OS_CYGWIN */
}

#endif /* OS_WINDOWS */
