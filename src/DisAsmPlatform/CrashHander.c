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

#include "../DisAsm/DisAsm"
#include "DisAsmPlatform"

void InfoCache(CacheLevel level)
{
	CacheInfo info;
	info.level = level;
	CPUIDCacheInfo(&info);
	if (level == info.level)
	{
		switch (level)
		{
		case kCacheLevel_L1Code:
			ConsoleIOPrint("L1 (Code) : ");
			break;
		case kCacheLevel_L1Data:
			ConsoleIOPrint("L1 (Data) : ");
			break;
		case kCacheLevel_L2:
			ConsoleIOPrint("L2 : ");
			break;
		case kCacheLevel_L3:
			ConsoleIOPrint("L3 : ");
			break;
		default:
			break;
		}
		if (info.size >= 1024 && 0 == (info.size % 1024))
		{
			ConsoleIOPrintFormatted("%dMb size", info.size / 1024);
		}
		else
		{
			ConsoleIOPrintFormatted("%dKb size", info.size);
		}
		if (0 == info.ways)
		{
			ConsoleIOPrint(", fully associative");
		}
		else
		{
			ConsoleIOPrintFormatted(", %d-way set associative", info.ways);	
		}
		ConsoleIOPrintFormatted(", %d line size\n", info.line);
	}
}

void InfoCPU()
{
	if (CheckCPUID())
	{
		char name[13] = {0};
		uint32_t MaxBasicLevel = CallCPUID(0x00000000UL, 0, NULL, (uint32_t*)name, (uint32_t*)(name + 8), (uint32_t*)(name + 4));
		uint32_t MaxExtendedLevel = CallCPUID(0x80000000UL, 0, NULL, NULL, NULL, NULL);

		ConsoleIOPrint("CPU :\n");
		ConsoleIOPrintFormatted("CPU name : %s\n", name);

		ConsoleIOPrintFormatted("X87      : %s\n", CheckCPUIDFeature(kCPUIDFeature_X87)   ? "YES" : "NO ");
		ConsoleIOPrintFormatted("MMX      : %s\n", CheckCPUIDFeature(kCPUIDFeature_MMX)   ? "YES" : "NO ");
		ConsoleIOPrintFormatted("SSE      : %s\n", CheckCPUIDFeature(kCPUIDFeature_SSE)   ? "YES" : "NO ");
		ConsoleIOPrintFormatted("SSE2     : %s\n", CheckCPUIDFeature(kCPUIDFeature_SSE2)  ? "YES" : "NO ");

		ConsoleIOPrintFormatted("SSE3     : %s\n", CheckCPUIDFeature(kCPUIDFeature_SSE3)  ? "YES" : "NO ");
		ConsoleIOPrintFormatted("VMX      : %s\n", CheckCPUIDFeature(kCPUIDFeature_VMX)   ? "YES" : "NO ");
		ConsoleIOPrintFormatted("SMX      : %s\n", CheckCPUIDFeature(kCPUIDFeature_SMX)   ? "YES" : "NO ");
		ConsoleIOPrintFormatted("SSSE3    : %s\n", CheckCPUIDFeature(kCPUIDFeature_SSSE3) ? "YES" : "NO ");
		ConsoleIOPrintFormatted("SSE4.1   : %s\n", CheckCPUIDFeature(kCPUIDFeature_SSE41) ? "YES" : "NO ");
		ConsoleIOPrintFormatted("SSE4.2   : %s\n", CheckCPUIDFeature(kCPUIDFeature_SSE42) ? "YES" : "NO ");
		ConsoleIOPrintFormatted("AESNI    : %s\n", CheckCPUIDFeature(kCPUIDFeature_AESNI) ? "YES" : "NO ");
		ConsoleIOPrintFormatted("AVX      : %s\n", CheckCPUIDFeature(kCPUIDFeature_AVX)   ? "YES" : "NO ");

		ConsoleIOPrintFormatted("AVX2     : %s\n", CheckCPUIDFeature(kCPUIDFeature_AVX2)     ? "YES" : "NO ");
		ConsoleIOPrintFormatted("AVX512F  : %s\n", CheckCPUIDFeature(kCPUIDFeature_AVX512F)  ? "YES" : "NO ");
		ConsoleIOPrintFormatted("AVX512PF : %s\n", CheckCPUIDFeature(kCPUIDFeature_AVX512PF) ? "YES" : "NO ");
		ConsoleIOPrintFormatted("AVX512ER : %s\n", CheckCPUIDFeature(kCPUIDFeature_AVX512ER) ? "YES" : "NO ");
		ConsoleIOPrintFormatted("AVX512CD : %s\n", CheckCPUIDFeature(kCPUIDFeature_AVX512CD) ? "YES" : "NO ");
		ConsoleIOPrintFormatted("SHA      : %s\n", CheckCPUIDFeature(kCPUIDFeature_SHA)      ? "YES" : "NO ");

		ConsoleIOPrintFormatted("EM64T    : %s\n", CheckCPUIDFeature(kCPUIDFeature_EM64T)  ? "YES" : "NO ");
		ConsoleIOPrintFormatted("3DNow!   : %s\n", CheckCPUIDFeature(kCPUIDFeature_3DNOW)  ? "YES" : "NO ");
		ConsoleIOPrintFormatted("3DNow!+  : %s\n", CheckCPUIDFeature(kCPUIDFeature_E3DNOW) ? "YES" : "NO ");

		ConsoleIOPrintFormatted("SSE4.a   : %s\n", CheckCPUIDFeature(kCPUIDFeature_SSE4A)  ? "YES" : "NO ");
		ConsoleIOPrintFormatted("XOP      : %s\n", CheckCPUIDFeature(kCPUIDFeature_XOP)    ? "YES" : "NO ");
		ConsoleIOPrintFormatted("FMA4     : %s\n", CheckCPUIDFeature(kCPUIDFeature_FMA4)   ? "YES" : "NO ");

		InfoCache(kCacheLevel_L1Code);
		InfoCache(kCacheLevel_L1Data);
		InfoCache(kCacheLevel_L2);
		InfoCache(kCacheLevel_L3);

		if (MaxBasicLevel >= 0x00000003UL && CheckCPUIDFeature(kCPUIDFeature_PSN))
		{
			char PSN[17] = {0};
			CallCPUID(0x00000003UL, 0, (uint32_t*)PSN, (uint32_t*)(PSN + 4), (uint32_t*)(PSN + 8), (uint32_t*)(PSN + 12));
			ConsoleIOPrintFormatted("PSN : %s\n", PSN);
		}
		if (MaxExtendedLevel >= 0x80000001UL)
		{
			uint32_t featuresECX = 0, featuresEDX = 0;
			CallCPUID(0x80000001UL, 0, NULL, NULL, &featuresECX, &featuresEDX);

			if (MaxExtendedLevel >= 0x80000004UL)
			{
				char brand[49] = {0};
				CallCPUID(0x80000002UL, 0, (uint32_t*)(brand + 0x00), (uint32_t*)(brand + 0x04), (uint32_t*)(brand + 0x08), (uint32_t*)(brand + 0x0C));
				CallCPUID(0x80000003UL, 0, (uint32_t*)(brand + 0x10), (uint32_t*)(brand + 0x14), (uint32_t*)(brand + 0x18), (uint32_t*)(brand + 0x1C));
				CallCPUID(0x80000004UL, 0, (uint32_t*)(brand + 0x20), (uint32_t*)(brand + 0x24), (uint32_t*)(brand + 0x28), (uint32_t*)(brand + 0x2C));
				ConsoleIOPrintFormatted("CPU brand : %s\n", brand);
			}
		}
		ConsoleIOPrint("\n");
	}
	else
	{
		if (Check80286())
		{
			if (Check80386())
			{
				ConsoleIOPrint("CPU : Intel 80386\n");
			}
			else
			{
				ConsoleIOPrint("CPU : Intel 80286\n");
			}
		}
		else
		{
			ConsoleIOPrint("CPU : Intel 8086\n");
		}
	}
}

#ifdef OS_WINDOWS

#ifndef VER_PLATFORM_WIN32s
#define VER_PLATFORM_WIN32s             0
#endif /* VER_PLATFORM_WIN32s */

#ifndef VER_PLATFORM_WIN32_WINDOWS
#define VER_PLATFORM_WIN32_WINDOWS      1
#endif /* VER_PLATFORM_WIN32_WINDOWS */

#ifndef VER_PLATFORM_WIN32_NT
#define VER_PLATFORM_WIN32_NT           2
#endif /* VER_PLATFORM_WIN32_NT */

#ifndef VER_NT_WORKSTATION
#define VER_NT_WORKSTATION              0x0000001
#endif /* VER_NT_WORKSTATION */

#ifndef VER_NT_DOMAIN_CONTROLLER
#define VER_NT_DOMAIN_CONTROLLER        0x0000002
#endif /* VER_NT_DOMAIN_CONTROLLER */

#ifndef VER_NT_SERVER
#define VER_NT_SERVER                   0x0000003
#endif /* VER_NT_SERVER */

#ifndef VER_SUITE_SMALLBUSINESS
#define VER_SUITE_SMALLBUSINESS 0x00000001
#endif /* VER_SUITE_SMALLBUSINESS */

#ifndef VER_SUITE_ENTERPRISE
#define VER_SUITE_ENTERPRISE 0x00000002
#endif /* VER_SUITE_ENTERPRISE */

#ifndef VER_SUITE_BACKOFFICE
#define VER_SUITE_BACKOFFICE 0x00000004
#endif /* VER_SUITE_BACKOFFICE */

#ifndef VER_SUITE_COMMUNICATIONS
#define VER_SUITE_COMMUNICATIONS 0x00000008
#endif /* VER_SUITE_COMMUNICATIONS */

#ifndef VER_SUITE_TERMINAL
#define VER_SUITE_TERMINAL 0x00000010
#endif /* VER_SUITE_TERMINAL */

#ifndef VER_SUITE_SMALLBUSINESS_RESTRICTED
#define VER_SUITE_SMALLBUSINESS_RESTRICTED 0x00000020
#endif /* VER_SUITE_SMALLBUSINESS_RESTRICTED */

#ifndef VER_SUITE_EMBEDDEDNT
#define VER_SUITE_EMBEDDEDNT 0x00000040
#endif /* VER_SUITE_EMBEDDEDNT */

#ifndef VER_SUITE_DATACENTER
#define VER_SUITE_DATACENTER 0x00000080
#endif /* VER_SUITE_DATACENTER */

#ifndef VER_SUITE_SINGLEUSERTS
#define VER_SUITE_SINGLEUSERTS 0x00000100
#endif /* VER_SUITE_SINGLEUSERTS */

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
#if defined(COMP_MICROSOFTC) && COMP_VERSION <= COMP_MICROSOFTC6
		WORD wSuiteMask   = osvi.wReserved[0];
		WORD wProductType = osvi.wReserved[1]; 
#else /* defined(COMP_MICROSOFTC) && COMP_VERSION <= COMP_MICROSOFTC6 */
		WORD wSuiteMask   = osvi.wSuiteMask;
		WORD wProductType = osvi.wProductType; 
#endif /* defined(COMP_MICROSOFTC) && COMP_VERSION <= COMP_MICROSOFTC6 */
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

		if (0 != (wSuiteMask & VER_SUITE_SMALLBUSINESS))            ConsoleIOPrint(" VER_SUITE_SMALLBUSINESS");
		if (0 != (wSuiteMask & VER_SUITE_ENTERPRISE))               ConsoleIOPrint(" VER_SUITE_ENTERPRISE");
		if (0 != (wSuiteMask & VER_SUITE_BACKOFFICE))               ConsoleIOPrint(" VER_SUITE_BACKOFFICE");
		if (0 != (wSuiteMask & VER_SUITE_COMMUNICATIONS))           ConsoleIOPrint(" VER_SUITE_COMMUNICATIONS");
		if (0 != (wSuiteMask & VER_SUITE_TERMINAL))                 ConsoleIOPrint(" VER_SUITE_TERMINAL");
		if (0 != (wSuiteMask & VER_SUITE_SMALLBUSINESS_RESTRICTED)) ConsoleIOPrint(" VER_SUITE_SMALLBUSINESS_RESTRICTED");
		if (0 != (wSuiteMask & VER_SUITE_EMBEDDEDNT))               ConsoleIOPrint(" VER_SUITE_EMBEDDEDNT");
		if (0 != (wSuiteMask & VER_SUITE_DATACENTER))               ConsoleIOPrint(" VER_SUITE_DATACENTER");
		if (0 != (wSuiteMask & VER_SUITE_SINGLEUSERTS))             ConsoleIOPrint(" VER_SUITE_SINGLEUSERTS");
		if (0 != (wSuiteMask & VER_SUITE_PERSONAL))                 ConsoleIOPrint(" VER_SUITE_PERSONAL");
		if (0 != (wSuiteMask & VER_SUITE_BLADE))                    ConsoleIOPrint(" VER_SUITE_BLADE");
		if (0 != (wSuiteMask & VER_SUITE_EMBEDDED_RESTRICTED))      ConsoleIOPrint(" VER_SUITE_EMBEDDED_RESTRICTED");
		if (0 != (wSuiteMask & VER_SUITE_SECURITY_APPLIANCE))       ConsoleIOPrint(" VER_SUITE_SECURITY_APPLIANCE");
		if (0 != (wSuiteMask & VER_SUITE_STORAGE_SERVER))           ConsoleIOPrint(" VER_SUITE_STORAGE_SERVER");
		if (0 != (wSuiteMask & VER_SUITE_COMPUTE_SERVER))           ConsoleIOPrint(" VER_SUITE_COMPUTE_SERVER");
		if (0 != (wSuiteMask & VER_SUITE_WH_SERVER))                ConsoleIOPrint(" VER_SUITE_WH_SERVER");

		switch (wProductType)
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

typedef BOOL (__stdcall *pfnEnumDeviceDrivers)(LPVOID *lpImageBase, DWORD cb, LPDWORD lpcbNeeded);
typedef DWORD (__stdcall *pfnGetDeviceDriverNameA)(LPVOID ImageBase, LPCSTR lpBaseName, DWORD nSize);

typedef BOOL (__stdcall *pfnGetFileVersionInfoA)(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
typedef DWORD (__stdcall *pfnGetFileVersionInfoSizeA)(LPCSTR lptstrFilename, LPDWORD lpdwHandle); 
typedef BOOL (__stdcall *pfnVerQueryValueA)(const LPVOID pBlock, LPSTR lpSubBlock, LPVOID * lplpBuffer, PUINT puLen);

enum { kMaxVersionString = 256 };

typedef struct VersionInfo_t
{
	char Comments[kMaxVersionString];
	char CompanyName[kMaxVersionString];
	char FileDescription[kMaxVersionString];
	char FileVersion[kMaxVersionString];
	char InternalName[kMaxVersionString];
	char LegalCopyright[kMaxVersionString];
	char LegalTrademarks[kMaxVersionString];
	char OriginalFilename[kMaxVersionString];
	char ProductName[kMaxVersionString];
	char ProductVersion[kMaxVersionString];
	char PrivateBuild[kMaxVersionString];
	char SpecialBuild[kMaxVersionString];
}
VersionInfo;

void GetVersionInfo(const char * name, VersionInfo * pInfo)
{
	HMODULE hVersion = LoadLibraryA("version.dll");
	memset(pInfo, 0, sizeof(VersionInfo));
	if (NULL != hVersion)
	{
		pfnGetFileVersionInfoA GetFileVersionInfoA = (pfnGetFileVersionInfoA) GetProcAddress(hVersion, "GetFileVersionInfoA");
		pfnGetFileVersionInfoSizeA GetFileVersionInfoSizeA = (pfnGetFileVersionInfoSizeA) GetProcAddress(hVersion, "GetFileVersionInfoSizeA");
		pfnVerQueryValueA VerQueryValueA = (pfnVerQueryValueA) GetProcAddress(hVersion, "VerQueryValueA");
		if (NULL != GetFileVersionInfoA && NULL != GetFileVersionInfoSizeA && NULL != VerQueryValueA)
		{
			DWORD dummy = 0;
			DWORD size = GetFileVersionInfoSize(name, &dummy);
			if (size > 0 && size <= 8192)
			{
				char block[8192];
				if (GetFileVersionInfo(name, dummy, size, block))
				{
					struct LANGANDCODEPAGE
					{
						WORD language;
						WORD codepage;
					}
					* pTranslate;
					UINT blocksize;
					if (VerQueryValueA(block, "\\VarFileInfo\\Translation", (LPVOID*)&pTranslate, &blocksize))
					{
						uint32_t i;
						for (i = 0; i < blocksize / sizeof(struct LANGANDCODEPAGE); ++i)
						{
							UINT dummy;
							char * value = NULL;
							char subblock[50];
							char * tokens[] =
							{
								"Comments",
								"CompanyName",
								"FileDescription",
								"FileVersion",
								"InternalName",
								"LegalCopyright",
								"LegalTrademarks",
								"OriginalFilename",
								"ProductName",
								"ProductVersion",
								"PrivateBuild",
								"SpecialBuild"
							};
							size_t j;
							for (j = 0; j < sizeof(tokens) / sizeof(tokens[0]); ++j)
							{
								ConsoleIOFormat(subblock, 50, "\\StringFileInfo\\%04x%04x\\%s", pTranslate[i].language, pTranslate[i].codepage, tokens[j]);
								if (VerQueryValueA(block, subblock, &value, &dummy))
								{
									xstrcat((char*)pInfo + kMaxVersionString * j, kMaxVersionString, value);
								}
							}
						}
					}
				}
			}
		}
		FreeLibrary(hVersion);
	}
}

void InfoModules()
{
	ModuleInfo * modules = NULL;
	uint32_t count = ModuleEnum(&modules);
	uint32_t i;
	ConsoleIOPrint("Modules : \n");
	for (i = 0; i < count; ++i)
	{
		VersionInfo info;
		GetVersionInfo(modules[i].path, &info);
		ConsoleIOPrintFormatted("%s, %s, %s, %s\n", modules[i].path, info.FileDescription, info.CompanyName, info.ProductVersion);
	}
	free(modules);
}

void InfoDrivers()
{
	HMODULE hPSAPI = LoadLibraryA("psapi.dll");
	if (NULL != hPSAPI)
	{
		pfnEnumDeviceDrivers EnumDeviceDrivers = (pfnEnumDeviceDrivers) GetProcAddress(hPSAPI, "EnumDeviceDrivers");
		pfnGetDeviceDriverNameA GetDeviceDriverBaseNameA = (pfnGetDeviceDriverNameA) GetProcAddress(hPSAPI, "GetDeviceDriverBaseNameA");
		pfnGetDeviceDriverNameA GetDeviceDriverFileNameA = (pfnGetDeviceDriverNameA) GetProcAddress(hPSAPI, "GetDeviceDriverFileNameA");
		if (NULL != EnumDeviceDrivers && NULL != GetDeviceDriverBaseNameA && NULL != GetDeviceDriverFileNameA)
		{
			LPVOID * drivers = NULL;
			DWORD needed = 0;
			EnumDeviceDrivers(NULL, 0, &needed);
			drivers = (LPVOID*) malloc(needed);

			if (EnumDeviceDrivers(drivers, needed, &needed))
			{
				DWORD i;
				char windir[NtfsMaxPath] = {0};
				if (!GetWindowsDirectoryA(windir, NtfsMaxPath))
				{
					xstrcat(windir, NtfsMaxPath, "C:\\Windows");
				}
				ConsoleIOPrint("Drivers : \n");
				for (i = 0; i < needed / sizeof(LPVOID); ++i)
				{
					char name[NtfsMaxPath] = {0};
					
					if (GetDeviceDriverFileNameA(drivers[i], name, NtfsMaxPath) || GetDeviceDriverBaseNameA(drivers[i], name, NtfsMaxPath))
					{
						VersionInfo info;
						char full[NtfsMaxPath] = {0};
						char * path = name;
						if (0 == memcmp(path, "\\??\\", 4))
						{
							path += 4;
						}
						if (0 == memcmp(path, "\\SystemRoot\\", xstrlen("\\SystemRoot\\")))
						{
							xstrcat(full, NtfsMaxPath, windir);
							xstrcat(full, NtfsMaxPath, path + xstrlen("\\SystemRoot\\") - 1);
						}
						else if (0 == memcmp(path, "\\WINDOWS\\", xstrlen("\\WINDOWS\\")) ||
							0 == memcmp(path, "\\Windows\\", xstrlen("\\Windows\\")))
						{
							xstrcat(full, NtfsMaxPath, windir);
							xstrcat(full, NtfsMaxPath, path + xstrlen("\\WINDOWS\\") - 1);
						}
						else
						{
							if (NULL == xstrchr(path, '\\'))
							{
								xstrcat(full, NtfsMaxPath, windir);
								xstrcat(full, NtfsMaxPath, "\\system32\\drivers\\");
								xstrcat(full, NtfsMaxPath, path);
							}
							else
							{
								xstrcat(full, NtfsMaxPath, path);
							}
						}
						GetVersionInfo(full, &info);
						ConsoleIOPrintFormatted("%s, %s, %s, %s\n", full, info.FileDescription, info.CompanyName, info.ProductVersion);
					}
				}
			}
		}
		FreeLibrary(hPSAPI);
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
	return 0;
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
	
	ConsoleIOPrintFormatted("[ERROR] crash! received signal %s\n", signals[signum]);
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
	InfoCPU();
#ifdef OS_WINDOWS
	InfoModules();
	InfoDrivers();
	InfoOperationSystem();

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
		sigemptyset(&action.sa_mask);
		if (0 != sigaction(signals[i].signum, &action, NULL))
		{
			ConsoleIOPrintFormatted("[ERROR] cannot install signal handler for signal %s\n", signals[i].message);
		}
	}
#endif /* OS_UNIX */
}
