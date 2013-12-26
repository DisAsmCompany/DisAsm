/*
 * Filename: Asm.h
 * Author:   DisAsmCompany
 * Date:     26/12/2013
 *
 * Description: frequently used assembler functions
 *              like CPUID, RDTSC, etc
 *
 *
 */

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

uint32_t CallCPUID(uint32_t level, uint32_t * outeax, uint32_t * outebx, uint32_t * outecx, uint32_t * outedx);
native_t ReadEFLAGS();
void WriteEFLAGS(native_t eflags);
uint8_t Check80286();
uint8_t Check80386();
uint8_t CheckCPUID();
