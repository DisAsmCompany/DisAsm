/*
 * Filename: CrashHandler.c
 * Author:   DisAsmCompany
 * Date:     16/11/2013
 *
 * Description: crash (exception) handler
 *
 *
 *
 */

#include "DisAsm"

#ifdef OS_WINDOWS

#ifndef VER_SUITE_PERSONAL
#define VER_SUITE_PERSONAL 0x00000200
#endif /* VER_SUITE_PERSONAL */

#ifndef VER_SUITE_BLADE
#define VER_SUITE_BLADE 0x00000400
#endif /* VER_SUITE_BLADE */

#ifndef VER_SUITE_EMBEDDED_RESTRICTED
#define VER_SUITE_EMBEDDED_RESTRICTED 0x00000800
#endif /* VER_SUITE_EMBEDDED_RESTRICTED */

#ifndef VER_SUITE_SECURITY_APPLIANCE
#define VER_SUITE_SECURITY_APPLIANCE 0x00001000
#endif /* VER_SUITE_SECURITY_APPLIANCE */

#ifndef VER_SUITE_STORAGE_SERVER
#define VER_SUITE_STORAGE_SERVER 0x00002000
#endif /* VER_SUITE_STORAGE_SERVER */

#ifndef VER_SUITE_COMPUTE_SERVER
#define VER_SUITE_COMPUTE_SERVER 0x00004000
#endif /* VER_SUITE_COMPUTE_SERVER */

#ifndef VER_SUITE_WH_SERVER
#define VER_SUITE_WH_SERVER 0x00008000
#endif /* VER_SUITE_WH_SERVER */

#ifndef SM_TABLETPC
#define SM_TABLETPC    86
#endif /* SM_TABLETPC */

#ifndef SM_MEDIACENTER
#define SM_MEDIACENTER 87
#endif /* SM_MEDIACENTER */

#ifndef SM_STARTER
#define SM_STARTER     88
#endif /* SM_STARTER */

#ifndef SM_SERVERR2
#define SM_SERVERR2    89
#endif /* SM_SERVERR2 */

void InfoOperationSystem()
{
	OSVERSIONINFOEX osvi = {0};
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if (GetVersionEx((OSVERSIONINFO*)&osvi))
	{
		ConsoleIOPrint("Operation System :\n");
		ConsoleIOPrintFormatted("%d.%d.%d (Service Pack %d.%d)", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber,
			osvi.wServicePackMajor, osvi.wServicePackMinor);

		switch (osvi.dwPlatformId)
		{
		case VER_PLATFORM_WIN32s:        ConsoleIOPrint(" VER_PLATFORM_WIN32s"); break;
		case VER_PLATFORM_WIN32_WINDOWS: ConsoleIOPrint(" VER_PLATFORM_WIN32_WINDOWS"); break;
		case VER_PLATFORM_WIN32_NT:      ConsoleIOPrint(" VER_PLATFORM_WIN32_NT"); break;
		default: break;
		}

		if (0 != (osvi.wSuiteMask & VER_SUITE_SMALLBUSINESS))            ConsoleIOPrint(" VER_SUITE_SMALLBUSINESS");
		if (0 != (osvi.wSuiteMask & VER_SUITE_ENTERPRISE))               ConsoleIOPrint(" VER_SUITE_ENTERPRISE");
		if (0 != (osvi.wSuiteMask & VER_SUITE_BACKOFFICE))               ConsoleIOPrint(" VER_SUITE_BACKOFFICE");
		if (0 != (osvi.wSuiteMask & VER_SUITE_COMMUNICATIONS))           ConsoleIOPrint(" VER_SUITE_COMMUNICATIONS");
		if (0 != (osvi.wSuiteMask & VER_SUITE_TERMINAL))                 ConsoleIOPrint(" VER_SUITE_TERMINAL");
		if (0 != (osvi.wSuiteMask & VER_SUITE_SMALLBUSINESS_RESTRICTED)) ConsoleIOPrint(" VER_SUITE_SMALLBUSINESS_RESTRICTED");
		if (0 != (osvi.wSuiteMask & VER_SUITE_EMBEDDEDNT))               ConsoleIOPrint(" VER_SUITE_EMBEDDEDNT");
		if (0 != (osvi.wSuiteMask & VER_SUITE_DATACENTER))               ConsoleIOPrint(" VER_SUITE_DATACENTER");
		if (0 != (osvi.wSuiteMask & VER_SUITE_SINGLEUSERTS))             ConsoleIOPrint(" VER_SUITE_SINGLEUSERTS");
		if (0 != (osvi.wSuiteMask & VER_SUITE_PERSONAL))                 ConsoleIOPrint(" VER_SUITE_PERSONAL");
		if (0 != (osvi.wSuiteMask & VER_SUITE_BLADE))                    ConsoleIOPrint(" VER_SUITE_BLADE");
		if (0 != (osvi.wSuiteMask & VER_SUITE_EMBEDDED_RESTRICTED))      ConsoleIOPrint(" VER_SUITE_EMBEDDED_RESTRICTED");
		if (0 != (osvi.wSuiteMask & VER_SUITE_SECURITY_APPLIANCE))       ConsoleIOPrint(" VER_SUITE_SECURITY_APPLIANCE");
		if (0 != (osvi.wSuiteMask & VER_SUITE_STORAGE_SERVER))           ConsoleIOPrint(" VER_SUITE_STORAGE_SERVER");
		if (0 != (osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER))           ConsoleIOPrint(" VER_SUITE_COMPUTE_SERVER");
		if (0 != (osvi.wSuiteMask & VER_SUITE_WH_SERVER))                ConsoleIOPrint(" VER_SUITE_WH_SERVER");

		switch (osvi.wProductType)
		{
		case VER_NT_WORKSTATION:       ConsoleIOPrint(" VER_NT_WORKSTATION"); break;
		case VER_NT_DOMAIN_CONTROLLER: ConsoleIOPrint(" VER_NT_DOMAIN_CONTROLLER"); break;
		case VER_NT_SERVER:            ConsoleIOPrint(" VER_NT_SERVER"); break;
		default: break;
		}

		ConsoleIOPrint("\n");

		ConsoleIOPrintFormatted("SM_SERVERR2    : %s\n", (0 != GetSystemMetrics(SM_SERVERR2))    ? "YES" : "NO");
		ConsoleIOPrintFormatted("SM_MEDIACENTER : %s\n", (0 != GetSystemMetrics(SM_MEDIACENTER)) ? "YES" : "NO");
		ConsoleIOPrintFormatted("SM_STARTER     : %s\n", (0 != GetSystemMetrics(SM_STARTER))     ? "YES" : "NO");
		ConsoleIOPrintFormatted("SM_TABLETPC    : %s\n", (0 != GetSystemMetrics(SM_TABLETPC))    ? "YES" : "NO");
		ConsoleIOPrint("\n");
	}
}

void InfoEnvironment()
{
	char * env = NULL;
	if (NULL != (env = GetEnvironmentStringsA()))
	{
		uint32_t length = 0;
		ConsoleIOPrint("Environment :\n");

		do
		{
			ConsoleIOPrintFormatted("%s\n", env);
			env += (length = xstrlen(env)) + 1;
		}
		while (length > 0);
	}
}

uint32_t CallCPUID(uint32_t level, uint32_t * outeax, uint32_t * outebx, uint32_t * outecx, uint32_t * outedx);

#if defined(COMP_WATCOMC)

#pragma aux CallCPUID = \
".586" \
"push eax" \
"push ebx" \
"push ecx" \
"push edx" \
"mov eax, esi" \
"cpuid" \
"mov esi, [esp]" \
"test esi, esi" \
"jmp skip_edx" \
"mov [esi], edx" \
"skip_edx: nop" \
"mov esi, [esp + 4]" \
"test esi, esi" \
"jmp skip_ecx" \
"mov [esi], ecx" \
"skip_ecx: nop" \
"mov esi, [esp + 8]" \
"test esi, esi" \
"jmp skip_ebx" \
"mov [esi], ebx" \
"skip_ebx: nop" \
"mov esi, [esp + 12]" \
"test esi, esi" \
"jmp skip_eax" \
"mov [esi], eax" \
"skip_eax: nop" \
"add esp, 16" \
parm [esi][eax][ebx][ecx][edx] \
modify [esi eax ebx ecx edx];

#else /* defined(COMP_WATCOMC) */

uint32_t CallCPUID(uint32_t level, uint32_t * outeax, uint32_t * outebx, uint32_t * outecx, uint32_t * outedx)
{
    uint32_t _eax, _ebx, _ecx, _edx;
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
    int info[4];
    __cpuid(info, level);
    _eax = info[0];
    _ebx = info[1];
    _ecx = info[2];
    _edx = info[3];
#endif /* defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_BORLANDC)
	__asm
	{
		mov eax, level
		cpuid
		mov _eax, eax
		mov _ebx, ebx
		mov _ecx, ecx
		mov _edx, edx
	}
#endif /* defined(COMP_BORLANDC) */
    if (outeax) *outeax = _eax;
    if (outebx) *outebx = _ebx;
    if (outecx) *outecx = _ecx;
    if (outedx) *outedx = _edx;
    return _eax;
}

#endif /* defined(COMP_WATCOMC) */

native_t ReadEFLAGS();
void WriteEFLAGS(native_t eflags);

#if defined(COMP_WATCOMC)

#pragma aux ReadEFLAGS = \
	".586" \
	"pushfd" \
	"pop eax" \
	modify [eax];

#pragma aux WriteEFLAGS = \
	".586" \
	"push eax" \
	"popfd" \
	parm [eax] \
	modify [eax];

#else /* defined(COMP_WATCOMC) */

native_t ReadEFLAGS()
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	return __readeflags();
#endif /* defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
}

void WriteEFLAGS(native_t eflags)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	__writeeflags(eflags);
#endif /* defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
}

#endif /* defined(COMP_WATCOMC) */

uint8_t CheckCPUID()
{
	/*
	The ID flag (bit 21) in the EFLAGS register indicates support for the CPUID instruction.
	If a software procedure can set and clear this flag, 
	the processor executing the procedure supports the CPUID instruction. 
	This instruction operates the same in non-64-bit modes and 64-bit mode.
	*/
    native_t kFlagCPUID = 1 << 21;
    uint8_t supported = 0;
    native_t eflags = ReadEFLAGS();
    WriteEFLAGS(eflags ^ kFlagCPUID);
    supported = (eflags & kFlagCPUID) != (ReadEFLAGS() & kFlagCPUID);
    WriteEFLAGS(eflags);
    return supported;
}

typedef enum CPUIDFeaturesECX_t
{
    kCPUIDFeature_SSE3       = 1 << 0,
    kCPUIDFeature_PCLMULDQ   = 1 << 1,
    kCPUIDFeature_DTES64     = 1 << 2,
    kCPUIDFeature_MONITOR    = 1 << 3,
    kCPUIDFeature_DSCPL      = 1 << 4,
    kCPUIDFeature_VMX        = 1 << 5,
    kCPUIDFeature_SMX        = 1 << 6,
    kCPUIDFeature_EIST       = 1 << 7,
    kCPUIDFeature_TM2        = 1 << 8,
    kCPUIDFeature_SSSE3      = 1 << 9,
    kCPUIDFeature_CNTXID     = 1 << 10,
    kCPUIDFeature_RESERVED11 = 1 << 11,
    kCPUIDFeature_FMA        = 1 << 12,
    kCPUIDFeature_CMPXCHG16B = 1 << 13,
    kCPUIDFeature_XTPR       = 1 << 14,
    kCPUIDFeature_PDCM       = 1 << 15,
    kCPUIDFeature_RESERVED16 = 1 << 16,
    kCPUIDFeature_PCID       = 1 << 17,
    kCPUIDFeature_DCA        = 1 << 18,
    kCPUIDFeature_SSE41      = 1 << 19,
    kCPUIDFeature_SSE42      = 1 << 20,
    kCPUIDFeature_X2APIC     = 1 << 21,
    kCPUIDFeature_MOVBE      = 1 << 22,
    kCPUIDFeature_POPCNT     = 1 << 23,
    kCPUIDFeature_TSCD       = 1 << 24,
    kCPUIDFeature_AESNI      = 1 << 25,
    kCPUIDFeature_XSAVE      = 1 << 26,
    kCPUIDFeature_OSXSAVE    = 1 << 27,
    kCPUIDFeature_AVX        = 1 << 28,
    kCPUIDFeature_F16C       = 1 << 29,
    kCPUIDFeature_RDRAND     = 1 << 30,
    kCPUIDFeature_RESERVED31 = 1 << 31,
}
CPUIDFeaturesECX;

typedef enum CPUIDFeaturesEDX_t
{
    kCPUIDFeature_X87        = 1 << 0,
    kCPUIDFeature_VME        = 1 << 1,
    kCPUIDFeature_DE         = 1 << 2,
    kCPUIDFeature_PSE        = 1 << 3,
    kCPUIDFeature_TSC        = 1 << 4,
    kCPUIDFeature_MSR        = 1 << 5,
    kCPUIDFeature_PAE        = 1 << 6,
    kCPUIDFeature_MCE        = 1 << 7,
    kCPUIDFeature_CMPXCHG8B  = 1 << 8,
    kCPUIDFeature_APIC       = 1 << 9,
    kCPUIDFeature_RESERVED10 = 1 << 10,
    kCPUIDFeature_SEP        = 1 << 11,
    kCPUIDFeature_MTRR       = 1 << 12,
    kCPUIDFeature_PGE        = 1 << 13,
    kCPUIDFeature_MCA        = 1 << 14,
    kCPUIDFeature_CMOV       = 1 << 15,
    kCPUIDFeature_PAT        = 1 << 16,
    kCPUIDFeature_PSE36      = 1 << 17,
    kCPUIDFeature_PSN        = 1 << 18,
    kCPUIDFeature_CLFLSH     = 1 << 19,
    kCPUIDFeature_RESERVED20 = 1 << 20,
    kCPUIDFeature_DS         = 1 << 21,
    kCPUIDFeature_ACPI       = 1 << 22,
    kCPUIDFeature_MMX        = 1 << 23,
    kCPUIDFeature_FXSR       = 1 << 24,
    kCPUIDFeature_SSE        = 1 << 25,
    kCPUIDFeature_SSE2       = 1 << 26,
    kCPUIDFeature_SS         = 1 << 27,
    kCPUIDFeature_HTT        = 1 << 28,
    kCPUIDFeature_TM         = 1 << 29,
    kCPUIDFeature_RESERVED30 = 1 << 30,
    kCPUIDFeature_PBE        = 1 << 31,
}
CPUIDFeaturesEDX;

typedef enum CPUIDFeaturesEBX_t
{
    kCPUIDFeature_AVX2       = 1 << 5,
}
CPUIDFeaturesEBX;

typedef enum CPUIDFeaturesExtendedECX_t
{
    kCPUIDFeature_LZCNT      = 1 << 5,
    kCPUIDFeature_SSE4A      = 1 << 6,
    kCPUIDFeature_MSSE       = 1 << 7,
    kCPUIDFeature_PREFETCHW  = 1 << 8,
    kCPUIDFeature_XOP        = 1 << 11,
    kCPUIDFeature_FMA4       = 1 << 16,
}
CPUIDFeaturesExtendedECX;

typedef enum CPUIDFeaturesExtendedEDX_t
{
    kCPUIDFeature_EM64T      = 1 << 29,
    kCPUIDFeature_3DNOW      = 1 << 30,
    kCPUIDFeature_E3DNOW     = 1 << 31,
}
CPUIDFeaturesExtendedEDX;

void InfoCPU()
{
    if (CheckCPUID())
    {
        char name[13] = {0};
        uint32_t MaxBasicLevel = CallCPUID(0x00000000UL, NULL, (uint32_t*)name, (uint32_t*)(name + 8), (uint32_t*)(name + 4));
        uint32_t MaxExtendedLevel = CallCPUID(0x80000000UL, NULL, NULL, NULL, NULL);

        ConsoleIOPrint("CPU :\n");
        ConsoleIOPrintFormatted("CPU name : %s\n", name);

        if (MaxBasicLevel >= 0x00000001UL)
        {
            uint32_t featuresECX = 0, featuresEDX = 0;
            CallCPUID(0x00000001UL, NULL, NULL, &featuresECX, &featuresEDX);

            ConsoleIOPrintFormatted("X87     : %s\n", featuresEDX & kCPUIDFeature_X87   ? "YES" : "NO ");
            ConsoleIOPrintFormatted("MMX     : %s\n", featuresEDX & kCPUIDFeature_MMX   ? "YES" : "NO ");
            ConsoleIOPrintFormatted("SSE     : %s\n", featuresEDX & kCPUIDFeature_SSE   ? "YES" : "NO ");
            ConsoleIOPrintFormatted("SSE2    : %s\n", featuresEDX & kCPUIDFeature_SSE2  ? "YES" : "NO ");

            ConsoleIOPrintFormatted("SSE3    : %s\n", featuresECX & kCPUIDFeature_SSE3  ? "YES" : "NO ");
            ConsoleIOPrintFormatted("VMX     : %s\n", featuresECX & kCPUIDFeature_VMX   ? "YES" : "NO ");
            ConsoleIOPrintFormatted("SMX     : %s\n", featuresECX & kCPUIDFeature_SMX   ? "YES" : "NO ");
            ConsoleIOPrintFormatted("SSSE3   : %s\n", featuresECX & kCPUIDFeature_SSSE3 ? "YES" : "NO ");
            ConsoleIOPrintFormatted("SSE4.1  : %s\n", featuresECX & kCPUIDFeature_SSE41 ? "YES" : "NO ");
            ConsoleIOPrintFormatted("SSE4.2  : %s\n", featuresECX & kCPUIDFeature_SSE42 ? "YES" : "NO ");
            ConsoleIOPrintFormatted("AESNI   : %s\n", featuresECX & kCPUIDFeature_AESNI ? "YES" : "NO ");
            ConsoleIOPrintFormatted("AVX     : %s\n", featuresECX & kCPUIDFeature_AVX   ? "YES" : "NO ");

            if (MaxBasicLevel >= 0x00000007UL)
            {
                uint32_t featuresEBX = 0;
                CallCPUID(0x00000007UL, NULL, &featuresEBX, NULL, NULL);

                ConsoleIOPrintFormatted("AVX2    : %s\n", featuresEBX & kCPUIDFeature_AVX2  ? "YES" : "NO ");
            }
        }
        if (MaxExtendedLevel >= 0x80000001UL)
        {
            uint32_t featuresECX = 0, featuresEDX = 0;
            CallCPUID(0x80000001UL, NULL, NULL, &featuresECX, &featuresEDX);

            ConsoleIOPrintFormatted("EM64T   : %s\n", featuresEDX & kCPUIDFeature_EM64T  ? "YES" : "NO ");
            ConsoleIOPrintFormatted("3DNow!  : %s\n", featuresEDX & kCPUIDFeature_3DNOW  ? "YES" : "NO ");
            ConsoleIOPrintFormatted("3DNow!+ : %s\n", featuresEDX & kCPUIDFeature_E3DNOW ? "YES" : "NO ");

            ConsoleIOPrintFormatted("SSE4.a  : %s\n", featuresEDX & kCPUIDFeature_SSE4A  ? "YES" : "NO ");
            ConsoleIOPrintFormatted("XOP     : %s\n", featuresEDX & kCPUIDFeature_XOP    ? "YES" : "NO ");
            ConsoleIOPrintFormatted("FMA4    : %s\n", featuresEDX & kCPUIDFeature_FMA4   ? "YES" : "NO ");

            if (MaxExtendedLevel >= 0x80000004UL)
            {
                char brand[49] = {0};
                CallCPUID(0x80000002UL, (uint32_t*)(brand + 0x00), (uint32_t*)(brand + 0x04), (uint32_t*)(brand + 0x08), (uint32_t*)(brand + 0x0C));
                CallCPUID(0x80000003UL, (uint32_t*)(brand + 0x10), (uint32_t*)(brand + 0x14), (uint32_t*)(brand + 0x18), (uint32_t*)(brand + 0x1C));
                CallCPUID(0x80000004UL, (uint32_t*)(brand + 0x20), (uint32_t*)(brand + 0x24), (uint32_t*)(brand + 0x28), (uint32_t*)(brand + 0x2C));
                ConsoleIOPrintFormatted("CPU brand : %s\n", brand);
            }
        }
        ConsoleIOPrint("\n");
    }
}

LONG __stdcall CrashHandlerExceptionFilter(struct _EXCEPTION_POINTERS * pExceptionInfo)
{
	native_t callstack[MaxCallStack] = {0};
	uint32_t i = 0;
	Context context;

	ConsoleIOPrint("[ERROR] crash!\n");

	InfoOperationSystem();
	InfoEnvironment();
    InfoCPU();

#ifdef CPU_X86
	context.InstructionPointer = pExceptionInfo->ContextRecord->Eip;
	context.StackBasePointer   = pExceptionInfo->ContextRecord->Ebp;
	context.StackFramePointer  = pExceptionInfo->ContextRecord->Esp;
#endif /* CPU_X86 */
#ifdef CPU_X64
	context.InstructionPointer = pExceptionInfo->ContextRecord->Rip;
	context.StackBasePointer   = pExceptionInfo->ContextRecord->Rbp;
	context.StackFramePointer  = pExceptionInfo->ContextRecord->Rsp;
#endif /* CPU_X64 */
	StackWalk(callstack, &context);
	for (i = 0; i < MaxCallStack; ++i)
	{
		if (0 == callstack[i])
		{
			break;
		}
		StackWalkSymbol(callstack[i]);
		ConsoleIOPrint("\n");
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

BOOL __stdcall CrashHandlerRoutine(DWORD CtrlType)
{
	native_t callstack[MaxCallStack] = {0};
	uint32_t i = 0;

	switch (CtrlType)
	{
	case CTRL_C_EVENT:        ConsoleIOPrint("CTRL_C_EVENT\n"); break;
	case CTRL_BREAK_EVENT:    ConsoleIOPrint("CTRL_BREAK_EVENT\n"); break;
	case CTRL_CLOSE_EVENT:    ConsoleIOPrint("CTRL_CLOSE_EVENT\n"); break;
	case CTRL_LOGOFF_EVENT:   ConsoleIOPrint("CTRL_LOGOFF_EVENT\n"); break;
	case CTRL_SHUTDOWN_EVENT: ConsoleIOPrint("CTRL_SHUTDOWN_EVENT\n"); break;
	default: break;
	}
	StackWalk(callstack, NULL);
	for (i = 0; i < MaxCallStack; ++i)
	{
		if (0 == callstack[i])
		{
			break;
		}
		StackWalkSymbol(callstack[i]);
		ConsoleIOPrint("\n");
	}
	ExitProcess(1);
	return true;
}

#endif /* OS_WINDOWS */
#ifdef OS_UNIX

typedef struct SignalRecord_t
{
	int signum;
	char * message;
}
SignalRecord;

static const SignalRecord signals[] =
{
	{SIGHUP,  "SIGHUP (hangup)"},
    {SIGINT,  "SIGINT (Ctrl-C)"},
    {SIGQUIT, "SIGQUIT (quit program)"},
    {SIGTRAP, "SIGTRAP (trace trap)"},
    {SIGABRT, "SIGABRT (abnormal termination)"},
    {SIGEMT,  "SIGEMT (emulation trap)"},
    {SIGBUS,  "SIGBUS (bus error)"},
    {SIGSYS,  "SIGSYS (invalid argument)"},
    {SIGILL,  "SIGILL (illegal instruction)"},
    {SIGPIPE, "SIGPIPE (pipe error)"},
    {SIGALRM, "SIGALRM (alarm clock)"},
    {SIGFPE,  "SIGFPE (floating-point exception)"},
    {SIGSEGV, "SIGSEGV (segmentation fault)"},
    {SIGTERM, "SIGTERM (termination request)"},
    {SIGTSTP, "SIGTSTP (terminal stop)"},
    //{SIGCONT, "SIGCONT (continue after stop)"},
    {SIGURG,  "SIGURG (urgent condition)"},
    {SIGABRT, "SIGABRT (abort)"},
    //{SIGCHLD, "SIGCHLD (child terminated)"},
    //{SIGTTIN, "SIGTTIN (tty input)"},
    //{SIGTTOU, "SIGTTOU (tty output)"},
    //{SIGIO, "SIGIO (pollable event)"},
    {SIGXCPU,   "SIGXCPU (CPU time limit exceeded)"},
    {SIGXFSZ,   "SIGXFSZ (file size limit exceeded)"},
    {SIGVTALRM, "SIGVTALRM (virtual timer alarm)"},
    {SIGPROF,   "SIGPROF (profiler timer alarm)"},
    //{SIGWINCH, "SIGWINCH (size changed)"},
    //{SIGINFO, "SIGINFO (status request)"},
    {SIGUSR1,   "SIGUSR1 (user defined signal 1)"},
    {SIGUSR2,   "SIGUSR2 (user defined signal 2)"},
};

void CrashHandler(int signum, siginfo_t * info, void * ucontext)
{
	native_t callstack[MaxCallStack] = {0};
	uint32_t i = 0;
	
	ConsoleIOPrint("[ERROR] crash!\n");
	StackWalk(callstack, NULL);
	for (i = 0; i < MaxCallStack; ++i)
	{
		if (0 == callstack[i])
		{
			break;
		}
		StackWalkSymbol(callstack[i]);
		ConsoleIOPrint("\n");
	}	
	_exit(EXIT_FAILURE);
}

#endif /* OS_UNIX */

void CrashHandlerInstall()
{
#ifdef OS_WINDOWS
	SetUnhandledExceptionFilter(CrashHandlerExceptionFilter);
	SetConsoleCtrlHandler(CrashHandlerRoutine, 1);
#endif /* OS_WINDOWS */
#ifdef OS_UNIX
	size_t i;
	for (i = 0; i < sizeof(signals) / sizeof(signals[0]); ++i)
	{
		struct sigaction action;
		action.sa_sigaction = CrashHandler;
		action.sa_flags = SA_RESTART | SA_SIGINFO;
		if (0 != sigaction(signals[i].signum, &action, NULL))
		{
			ConsoleIOPrintFormatted("[ERROR] cannot install signal handler for signal %s\n", signals[i].message);
		}
	}
#endif /* OS_UNIX */
}
