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

typedef struct CacheInfo_t
{
	uint8_t level;
	uint8_t pages;
	uint8_t associative;
	uint8_t entries;
}
CacheInfo;

static const CacheInfo CacheTable[] =
{
	{0, 0, 0, 0}, /* 00h */
	{0, 0, 0, 0}, /* 01h */
	{0, 0, 0, 0}, /* 02h */
	{0, 0, 0, 0}, /* 03h */
	{0, 0, 0, 0}, /* 04h */
	{0, 0, 0, 0}, /* 05h */
	{0, 0, 0, 0}, /* 06h */
	{0, 0, 0, 0}, /* 07h */
	{0, 0, 0, 0}, /* 08h */
	{0, 0, 0, 0}, /* 09h */
	{0, 0, 0, 0}, /* 0Ah */
	{0, 0, 0, 0}, /* 0Bh */
	{0, 0, 0, 0}, /* 0Ch */
	{0, 0, 0, 0}, /* 0Dh */
	{0, 0, 0, 0}, /* 0Eh */
	{0, 0, 0, 0}, /* 0Fh */

	{0, 0, 0, 0}, /* 10h */
	{0, 0, 0, 0}, /* 11h */
	{0, 0, 0, 0}, /* 12h */
	{0, 0, 0, 0}, /* 13h */
	{0, 0, 0, 0}, /* 14h */
	{0, 0, 0, 0}, /* 15h */
	{0, 0, 0, 0}, /* 16h */
	{0, 0, 0, 0}, /* 17h */
	{0, 0, 0, 0}, /* 18h */
	{0, 0, 0, 0}, /* 19h */
	{0, 0, 0, 0}, /* 1Ah */
	{0, 0, 0, 0}, /* 1Bh */
	{0, 0, 0, 0}, /* 1Ch */
	{0, 0, 0, 0}, /* 1Dh */
	{0, 0, 0, 0}, /* 1Eh */
	{0, 0, 0, 0}, /* 1Fh */

	{0, 0, 0, 0}, /* 20h */
	{0, 0, 0, 0}, /* 21h */
	{0, 0, 0, 0}, /* 22h */
	{0, 0, 0, 0}, /* 23h */
	{0, 0, 0, 0}, /* 24h */
	{0, 0, 0, 0}, /* 25h */
	{0, 0, 0, 0}, /* 26h */
	{0, 0, 0, 0}, /* 27h */
	{0, 0, 0, 0}, /* 28h */
	{0, 0, 0, 0}, /* 29h */
	{0, 0, 0, 0}, /* 2Ah */
	{0, 0, 0, 0}, /* 2Bh */
	{0, 0, 0, 0}, /* 2Ch */
	{0, 0, 0, 0}, /* 2Dh */
	{0, 0, 0, 0}, /* 2Eh */
	{0, 0, 0, 0}, /* 2Fh */

	{0, 0, 0, 0}, /* 30h */
	{0, 0, 0, 0}, /* 31h */
	{0, 0, 0, 0}, /* 32h */
	{0, 0, 0, 0}, /* 33h */
	{0, 0, 0, 0}, /* 34h */
	{0, 0, 0, 0}, /* 35h */
	{0, 0, 0, 0}, /* 36h */
	{0, 0, 0, 0}, /* 37h */
	{0, 0, 0, 0}, /* 38h */
	{0, 0, 0, 0}, /* 39h */
	{0, 0, 0, 0}, /* 3Ah */
	{0, 0, 0, 0}, /* 3Bh */
	{0, 0, 0, 0}, /* 3Ch */
	{0, 0, 0, 0}, /* 3Dh */
	{0, 0, 0, 0}, /* 3Eh */
	{0, 0, 0, 0}, /* 3Fh */

	{0, 0, 0, 0}, /* 40h */
	{0, 0, 0, 0}, /* 41h */
	{0, 0, 0, 0}, /* 42h */
	{0, 0, 0, 0}, /* 43h */
	{0, 0, 0, 0}, /* 44h */
	{0, 0, 0, 0}, /* 45h */
	{0, 0, 0, 0}, /* 46h */
	{0, 0, 0, 0}, /* 47h */
	{0, 0, 0, 0}, /* 48h */
	{0, 0, 0, 0}, /* 49h */
	{0, 0, 0, 0}, /* 4Ah */
	{0, 0, 0, 0}, /* 4Bh */
	{0, 0, 0, 0}, /* 4Ch */
	{0, 0, 0, 0}, /* 4Dh */
	{0, 0, 0, 0}, /* 4Eh */
	{0, 0, 0, 0}, /* 4Fh */

	{0, 0, 0, 0}, /* 50h */
	{0, 0, 0, 0}, /* 51h */
	{0, 0, 0, 0}, /* 52h */
	{0, 0, 0, 0}, /* 53h */
	{0, 0, 0, 0}, /* 54h */
	{0, 0, 0, 0}, /* 55h */
	{0, 0, 0, 0}, /* 56h */
	{0, 0, 0, 0}, /* 57h */
	{0, 0, 0, 0}, /* 58h */
	{0, 0, 0, 0}, /* 59h */
	{0, 0, 0, 0}, /* 5Ah */
	{0, 0, 0, 0}, /* 5Bh */
	{0, 0, 0, 0}, /* 5Ch */
	{0, 0, 0, 0}, /* 5Dh */
	{0, 0, 0, 0}, /* 5Eh */
	{0, 0, 0, 0}, /* 5Fh */

	{0, 0, 0, 0}, /* 60h */
	{0, 0, 0, 0}, /* 61h */
	{0, 0, 0, 0}, /* 62h */
	{0, 0, 0, 0}, /* 63h */
	{0, 0, 0, 0}, /* 64h */
	{0, 0, 0, 0}, /* 65h */
	{0, 0, 0, 0}, /* 66h */
	{0, 0, 0, 0}, /* 67h */
	{0, 0, 0, 0}, /* 68h */
	{0, 0, 0, 0}, /* 69h */
	{0, 0, 0, 0}, /* 6Ah */
	{0, 0, 0, 0}, /* 6Bh */
	{0, 0, 0, 0}, /* 6Ch */
	{0, 0, 0, 0}, /* 6Dh */
	{0, 0, 0, 0}, /* 6Eh */
	{0, 0, 0, 0}, /* 6Fh */

	{0, 0, 0, 0}, /* 70h */
	{0, 0, 0, 0}, /* 71h */
	{0, 0, 0, 0}, /* 72h */
	{0, 0, 0, 0}, /* 73h */
	{0, 0, 0, 0}, /* 74h */
	{0, 0, 0, 0}, /* 75h */
	{0, 0, 0, 0}, /* 76h */
	{0, 0, 0, 0}, /* 77h */
	{0, 0, 0, 0}, /* 78h */
	{0, 0, 0, 0}, /* 79h */
	{0, 0, 0, 0}, /* 7Ah */
	{0, 0, 0, 0}, /* 7Bh */
	{0, 0, 0, 0}, /* 7Ch */
	{0, 0, 0, 0}, /* 7Dh */
	{0, 0, 0, 0}, /* 7Eh */
	{0, 0, 0, 0}, /* 7Fh */

	{0, 0, 0, 0}, /* 80h */
	{0, 0, 0, 0}, /* 81h */
	{0, 0, 0, 0}, /* 82h */
	{0, 0, 0, 0}, /* 83h */
	{0, 0, 0, 0}, /* 84h */
	{0, 0, 0, 0}, /* 85h */
	{0, 0, 0, 0}, /* 86h */
	{0, 0, 0, 0}, /* 87h */
	{0, 0, 0, 0}, /* 88h */
	{0, 0, 0, 0}, /* 89h */
	{0, 0, 0, 0}, /* 8Ah */
	{0, 0, 0, 0}, /* 8Bh */
	{0, 0, 0, 0}, /* 8Ch */
	{0, 0, 0, 0}, /* 8Dh */
	{0, 0, 0, 0}, /* 8Eh */
	{0, 0, 0, 0}, /* 8Fh */

	{0, 0, 0, 0}, /* 90h */
	{0, 0, 0, 0}, /* 91h */
	{0, 0, 0, 0}, /* 92h */
	{0, 0, 0, 0}, /* 93h */
	{0, 0, 0, 0}, /* 94h */
	{0, 0, 0, 0}, /* 95h */
	{0, 0, 0, 0}, /* 96h */
	{0, 0, 0, 0}, /* 97h */
	{0, 0, 0, 0}, /* 98h */
	{0, 0, 0, 0}, /* 99h */
	{0, 0, 0, 0}, /* 9Ah */
	{0, 0, 0, 0}, /* 9Bh */
	{0, 0, 0, 0}, /* 9Ch */
	{0, 0, 0, 0}, /* 9Dh */
	{0, 0, 0, 0}, /* 9Eh */
	{0, 0, 0, 0}, /* 9Fh */

	{0, 0, 0, 0}, /* A0h */
	{0, 0, 0, 0}, /* A1h */
	{0, 0, 0, 0}, /* A2h */
	{0, 0, 0, 0}, /* A3h */
	{0, 0, 0, 0}, /* A4h */
	{0, 0, 0, 0}, /* A5h */
	{0, 0, 0, 0}, /* A6h */
	{0, 0, 0, 0}, /* A7h */
	{0, 0, 0, 0}, /* A8h */
	{0, 0, 0, 0}, /* A9h */
	{0, 0, 0, 0}, /* AAh */
	{0, 0, 0, 0}, /* ABh */
	{0, 0, 0, 0}, /* ACh */
	{0, 0, 0, 0}, /* ADh */
	{0, 0, 0, 0}, /* AEh */
	{0, 0, 0, 0}, /* AFh */

	{0, 0, 0, 0}, /* B0h */
	{0, 0, 0, 0}, /* B1h */
	{0, 0, 0, 0}, /* B2h */
	{0, 0, 0, 0}, /* B3h */
	{0, 0, 0, 0}, /* B4h */
	{0, 0, 0, 0}, /* B5h */
	{0, 0, 0, 0}, /* B6h */
	{0, 0, 0, 0}, /* B7h */
	{0, 0, 0, 0}, /* B8h */
	{0, 0, 0, 0}, /* B9h */
	{0, 0, 0, 0}, /* BAh */
	{0, 0, 0, 0}, /* BBh */
	{0, 0, 0, 0}, /* BCh */
	{0, 0, 0, 0}, /* BDh */
	{0, 0, 0, 0}, /* BEh */
	{0, 0, 0, 0}, /* BFh */

	{0, 0, 0, 0}, /* C0h */
	{0, 0, 0, 0}, /* C1h */
	{0, 0, 0, 0}, /* C2h */
	{0, 0, 0, 0}, /* C3h */
	{0, 0, 0, 0}, /* C4h */
	{0, 0, 0, 0}, /* C5h */
	{0, 0, 0, 0}, /* C6h */
	{0, 0, 0, 0}, /* C7h */
	{0, 0, 0, 0}, /* C8h */
	{0, 0, 0, 0}, /* C9h */
	{0, 0, 0, 0}, /* CAh */
	{0, 0, 0, 0}, /* CBh */
	{0, 0, 0, 0}, /* CCh */
	{0, 0, 0, 0}, /* CDh */
	{0, 0, 0, 0}, /* CEh */
	{0, 0, 0, 0}, /* CFh */

	{0, 0, 0, 0}, /* D0h */
	{0, 0, 0, 0}, /* D1h */
	{0, 0, 0, 0}, /* D2h */
	{0, 0, 0, 0}, /* D3h */
	{0, 0, 0, 0}, /* D4h */
	{0, 0, 0, 0}, /* D5h */
	{0, 0, 0, 0}, /* D6h */
	{0, 0, 0, 0}, /* D7h */
	{0, 0, 0, 0}, /* D8h */
	{0, 0, 0, 0}, /* D9h */
	{0, 0, 0, 0}, /* DAh */
	{0, 0, 0, 0}, /* DBh */
	{0, 0, 0, 0}, /* DCh */
	{0, 0, 0, 0}, /* DDh */
	{0, 0, 0, 0}, /* DEh */
	{0, 0, 0, 0}, /* DFh */

	{0, 0, 0, 0}, /* E0h */
	{0, 0, 0, 0}, /* E1h */
	{0, 0, 0, 0}, /* E2h */
	{0, 0, 0, 0}, /* E3h */
	{0, 0, 0, 0}, /* E4h */
	{0, 0, 0, 0}, /* E5h */
	{0, 0, 0, 0}, /* E6h */
	{0, 0, 0, 0}, /* E7h */
	{0, 0, 0, 0}, /* E8h */
	{0, 0, 0, 0}, /* E9h */
	{0, 0, 0, 0}, /* EAh */
	{0, 0, 0, 0}, /* EBh */
	{0, 0, 0, 0}, /* ECh */
	{0, 0, 0, 0}, /* EDh */
	{0, 0, 0, 0}, /* EEh */
	{0, 0, 0, 0}, /* EFh */

	{0, 0, 0, 0}, /* F0h */
	{0, 0, 0, 0}, /* F1h */
	{0, 0, 0, 0}, /* F2h */
	{0, 0, 0, 0}, /* F3h */
	{0, 0, 0, 0}, /* F4h */
	{0, 0, 0, 0}, /* F5h */
	{0, 0, 0, 0}, /* F6h */
	{0, 0, 0, 0}, /* F7h */
	{0, 0, 0, 0}, /* F8h */
	{0, 0, 0, 0}, /* F9h */
	{0, 0, 0, 0}, /* FAh */
	{0, 0, 0, 0}, /* FBh */
	{0, 0, 0, 0}, /* FCh */
	{0, 0, 0, 0}, /* FDh */
	{0, 0, 0, 0}, /* FEh */
	{0, 0, 0, 0}, /* FFh */
};

void InfoCPUCache()
{
	uint8_t descriptors[16];
	uint8_t count = 1;
	uint8_t i;

	for (i = 0; i < count; ++i)
	{
		CallCPUID(0x00000002UL, (uint32_t*)descriptors, (uint32_t*)(descriptors + 4), (uint32_t*)(descriptors + 8), (uint32_t*)(descriptors + 12));
		count = descriptors[0];
	}
}

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

			if (MaxBasicLevel >= 0x00000002UL)
			{
				InfoCPUCache();

				if (MaxBasicLevel >= 0x00000003UL && (featuresEDX & kCPUIDFeature_PSN))
				{
					char PSN[17] = {0};
					CallCPUID(0x00000003UL, (uint32_t*)PSN, (uint32_t*)(PSN + 4), (uint32_t*)(PSN + 8), (uint32_t*)(PSN + 12));
					ConsoleIOPrintFormatted("PSN : %s\n", PSN);
				}
				if (MaxBasicLevel >= 0x00000007UL)
				{
					uint32_t featuresEBX = 0;
					CallCPUID(0x00000007UL, NULL, &featuresEBX, NULL, NULL);

					ConsoleIOPrintFormatted("AVX2    : %s\n", featuresEBX & kCPUIDFeature_AVX2  ? "YES" : "NO ");
				}
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
	InfoCPU();
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
		sigemptyset(&action.sa_mask);
		if (0 != sigaction(signals[i].signum, &action, NULL))
		{
			ConsoleIOPrintFormatted("[ERROR] cannot install signal handler for signal %s\n", signals[i].message);
		}
	}
#endif /* OS_UNIX */
}
