/*
* Filename: Module.c
* Author:   DisAsmCompany
* Date:     23/11/2013
*
* Description: native module loader
*
*              
*
*/

#include "DisAsm"

#ifdef OS_WINDOWS

typedef struct _MODULEINFO
{
	LPVOID lpBaseOfDll;
	DWORD SizeOfImage;
	LPVOID EntryPoint;
}
MODULEINFO, *LPMODULEINFO;

typedef BOOL (__stdcall *pfnEnumProcessModules)(HANDLE hProcess, HMODULE *lphModule, DWORD cb, LPDWORD lpcbNeeded);
typedef BOOL (__stdcall *pfnGetModuleInformation)(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb);
pfnEnumProcessModules pEnumProcessModules = NULL;
pfnGetModuleInformation pGetModuleInformation = NULL;

#endif /* OS_WINDOWS */

address_t ModuleLoad(const char * name)
{
#ifdef OS_WINDOWS
	return (address_t) LoadLibraryA(name);
#endif /* OS_WINDOWS */
}

void ModuleUnload(address_t address)
{
#ifdef OS_WINDOWS
	FreeLibrary((HMODULE) address);
#endif /* OS_WINDOWS */
}

void ModuleGetInfo(address_t address, ModuleInfo * info)
{
	if (NULL != info)
	{
#ifdef OS_WINDOWS
		MODULEINFO mi = {0};
		HMODULE hPSAPI = LoadLibraryA("psapi.dll");
		if (NULL != hPSAPI)
		{
			pGetModuleInformation = (pfnGetModuleInformation) GetProcAddress(hPSAPI, "GetModuleInformation");
			if (NULL != pGetModuleInformation)
			{
				if (pGetModuleInformation(GetCurrentProcess(), (HMODULE) address, &mi, sizeof(MODULEINFO)))
				{
					info->address = (address_t) mi.lpBaseOfDll;
					info->size    = (uint32_t) mi.SizeOfImage;
					if (GetModuleFileNameA((HMODULE) address, info->path, NtfsMaxPath))
					{
						xstrcat(info->name, NtfsMaxPath, ShortName(info->path) + 1);
					}
				}
			}
			FreeLibrary(hPSAPI);
		}
#endif /* OS_WINDOWS */
	}
}

uint32_t ModuleEnum(ModuleInfo ** info)
{
	uint32_t count = 0;
	if (NULL != info)
	{
#ifdef OS_WINDOWS
		HMODULE hPSAPI = LoadLibraryA("psapi.dll");
		if (NULL != hPSAPI)
		{
			pEnumProcessModules = (pfnEnumProcessModules) GetProcAddress(hPSAPI, "EnumProcessModules");
			if (NULL != pEnumProcessModules)
			{
				uint32_t i;
				DWORD needed = 0;
				HMODULE * modules = NULL;
				ModuleInfo * array = NULL;
				pEnumProcessModules(GetCurrentProcess(), NULL, 0, &needed);
				count = needed / sizeof(DWORD);
				modules = (HMODULE *) calloc(1, count * sizeof(HMODULE));
				pEnumProcessModules(GetCurrentProcess(), modules, needed, &needed);
				array = (ModuleInfo*) calloc(1, count * sizeof(ModuleInfo));
				for (i = 0; i < count; ++i)
				{
					ModuleGetInfo((address_t) modules[i], &array[i]);
				}
				*info = array;
				free(modules);
			}
			FreeLibrary(hPSAPI);
		}
#endif /* OS_WINDOWS */
	}
	return count;
}
