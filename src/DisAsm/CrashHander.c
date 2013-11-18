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

#ifdef _WIN32

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

LONG __stdcall CrashHandlerExceptionFilter(struct _EXCEPTION_POINTERS * pExceptionInfo)
{
	address_t callstack[MaxCallStack] = {0};
	uint32_t i = 0;
	Context context;

	ConsoleIOPrint("[ERROR] crash!\n");

	InfoOperationSystem();
	InfoEnvironment();

#ifdef _M_IX86
	context.InstructionPointer = pExceptionInfo->ContextRecord->Eip;
	context.StackBasePointer   = pExceptionInfo->ContextRecord->Ebp;
	context.StackFramePointer  = pExceptionInfo->ContextRecord->Esp;
#endif /* _M_IX86 */
#ifdef _M_X64
	context.InstructionPointer = pExceptionInfo->ContextRecord->Rip;
	context.StackBasePointer   = pExceptionInfo->ContextRecord->Rbp;
	context.StackFramePointer  = pExceptionInfo->ContextRecord->Rsp;
#endif /* _M_X64 */
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

BOOL __stdcall CrashHandlerRoutine(uint32_t CtrlType)
{
	address_t callstack[MaxCallStack] = {0};
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

#endif /* _WIN32 */
#ifdef __APPLE__

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
	address_t callstack[MaxCallStack] = {0};
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

#endif /* __APPLE__ */

void CrashHandlerInstall()
{
#ifdef _WIN32
	SetUnhandledExceptionFilter(CrashHandlerExceptionFilter);
	SetConsoleCtrlHandler(CrashHandlerRoutine, 1);
#endif /* _WIN32 */
#ifdef __APPLE__
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
#endif /* __APPLE__ */
}
