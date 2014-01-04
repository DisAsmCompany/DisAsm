/*
 * Filename: CPUID.h
 * Author:   DisAsmCompany
 * Date:     27/12/2013
 *
 * Description: CPU features identification
 *              
 *
 *
 */

#pragma once
#ifndef __CPUID_H__DE2FCA61_F4AB_430E_BB9A_4278D79DB9BE__
#define __CPUID_H__DE2FCA61_F4AB_430E_BB9A_4278D79DB9BE__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum EFLAGS_t
{
	kEFLAGS_CF  = 0,  /* Carry Flag */
	kEFLAGS_PF  = 2,  /* Parity Flag */
	kEFLAGS_AF  = 4,  /* Axillary Carry Flag, aka Adjust Flag */
	kEFLAGS_ZF  = 6,  /* Zero Flag */
	kEFLAGS_SF  = 7,  /* Sign Flag */
	kEFLAGS_TF  = 8,  /* Trap Flag */
	kEFLAGS_IF  = 9,  /* Interrupt Enable Flag */
	kEFLAGS_DF  = 10, /* Direction Flag */
	kEFLAGS_OF  = 11, /* Overflow Flag */
	kEFLAGS_NT  = 14, /* Nested Task Flag */
	kEFLAGS_RF  = 16, /* Resume Flag */
	kEFLAGS_VM  = 17, /* Virtual 8086 Mode */
	kEFLAGS_AC  = 18, /* Alignment Check */
	kEFLAGS_VIP = 19, /* Virtual Interrupt Flag */
	kEFLAGS_VIF = 20, /* Virtual Interrupt Pending */
	kEFLAGS_ID  = 21 /* ID Flag */
}
EFLAGS;

typedef enum XCR0_t
{
	kXCR0_EnabledMask = 0x06, /* XMM & YMM state are enabled by OS */
	kXCR0_OpMask      = 0xE0  /* ZMM state is enabled by OS */
}
XCR0;

typedef enum CPUIDFeature_t
{
	/* 00000001h EDX */
	kCPUIDFeature_X87            = 0,  /* x87 FPU, Floating Point Unit On-Board */
	kCPUIDFeature_VME            = 1,  /* Virtual 8086 */
	kCPUIDFeature_DE             = 2,  /* Debugging Extensions */
	kCPUIDFeature_PSE            = 3,  /* Page Size Extensions */
	kCPUIDFeature_TSC            = 4,  /* Time Stamp Counter */
	kCPUIDFeature_MSR            = 5,  /* Model Specific Registers and RDMSR/WRMSR Instructions */
	kCPUIDFeature_PAE            = 6,  /* Physical Address Extensions */
	kCPUIDFeature_MCE            = 7,  /* Machine Check Exception */
	kCPUIDFeature_CMPXCHG8B      = 8,  /* CMPXCHG8B Instruction, Compare and Exchange 8 Bytes */
	kCPUIDFeature_APIC           = 9,  /* APIC On-Board, Advanced Programmable Interrupt Controller */
	kCPUIDFeature_RESERVED10     = 10, /* Bit 10 is Reserved */
	kCPUIDFeature_SEP            = 11, /* SYSENTER and SYSEXIT instruction */
	kCPUIDFeature_MTRR           = 12, /* Memory Type Range Registers */
	kCPUIDFeature_PGE            = 13, /* Page Global Enable Bit */
	kCPUIDFeature_MCA            = 14, /* Machine Check Architecture */
	kCPUIDFeature_CMOV           = 15, /* CMOVcc, Conditional Move Instructions */
	kCPUIDFeature_PAT            = 16, /* Page Attribute Table */
	kCPUIDFeature_PSE36          = 17, /* 36-Bit Page Size Extension */
	kCPUIDFeature_PSN            = 18, /* Processor Serial Number */
	kCPUIDFeature_CLFLSH         = 19, /* CLFLUSH Instruction, Flush Cache Line */
	kCPUIDFeature_RESERVED20     = 20, /* Bit 20 is Reserved */
	kCPUIDFeature_DS             = 21, /* Debug Store */
	kCPUIDFeature_ACPI           = 22, /* Thermal Monitor and Software Controlled Clock Facilities for ACPI, Advanced Configuration and Power Interface */
	kCPUIDFeature_MMX            = 23, /* Intel MMX, Multi Media Extensions */
	kCPUIDFeature_FXSR           = 24, /* FXSAVE and FXSTOR Instructions */
	kCPUIDFeature_SSE            = 25, /* SSE, Streaming SIMD Extensions */
	kCPUIDFeature_SSE2           = 26, /* SSE2, Streaming SIMD Extensions */
	kCPUIDFeature_SS             = 27, /* Self Snoop */
	kCPUIDFeature_HTT            = 28, /* Intel Hyper Threading Technology */
	kCPUIDFeature_TM             = 29, /* Thermal Monitor */
	kCPUIDFeature_RESERVED30     = 30, /* Bit 30 is Reserved */
	kCPUIDFeature_PBE            = 31, /* Pending Break Enable */
	/* 00000001h ECX */
	kCPUIDFeature_SSE3           = 32 + 0,  /* SSE3, Streaming SIMD Extensions */
	kCPUIDFeature_PCLMULQDQ      = 32 + 1,  /* PCLMULQDQ Instruction, Carry-Less Multiplication Quad Word */
	kCPUIDFeature_DTES64         = 32 + 2,  /* 64-bit Debug Trace */
	kCPUIDFeature_MONITOR        = 32 + 3,  /* MONITOR/WAIT Instructions */
	kCPUIDFeature_DSCPL          = 32 + 4,  /* CPL-Qualified Debug Store */
	kCPUIDFeature_VMX            = 32 + 5,  /* VMX, Virtual Machine Extensions, aka Intel VT-x */
	kCPUIDFeature_SMX            = 32 + 6,  /* SMX, Safer Mode Extensions */
	kCPUIDFeature_EIST           = 32 + 7,  /* Enhanced Intel SpeedStep Technology */
	kCPUIDFeature_TM2            = 32 + 8,  /* Thermal Monitor 2 */
	kCPUIDFeature_SSSE3          = 32 + 9,  /* SSSE3, Supplemental Streaming SIMD Extensions */
	kCPUIDFeature_CNTXID         = 32 + 10, /* L1 Context ID */
	kCPUIDFeature_RESERVED11     = 32 + 11, /* Bit 11 is Reserved */
	kCPUIDFeature_FMA            = 32 + 12, /* Intel FMA, Fused Multiply-Add */
	kCPUIDFeature_CMPXCHG16B     = 32 + 13, /* CMPXCHG16B Instruction, Compare and Exchange 16 Bytes */
	kCPUIDFeature_XTPR           = 32 + 14, /* xTPR Update Control */
	kCPUIDFeature_PDCM           = 32 + 15, /* Performance Debug Capability MSR */
	kCPUIDFeature_RESERVED16     = 32 + 16, /* Bit 16 is Reserved */
	kCPUIDFeature_PCID           = 32 + 17, /* Process Context Identifier */
	kCPUIDFeature_DCA            = 32 + 18, /* Direct Cache Access */
	kCPUIDFeature_SSE41          = 32 + 19, /* SSE4.1, Streaming SIMD Extensions */
	kCPUIDFeature_SSE42          = 32 + 20, /* SSE4.2, Streaming SIMD Extensions */
	kCPUIDFeature_X2APIC         = 32 + 21, /* x2APIC */
	kCPUIDFeature_MOVBE          = 32 + 22, /* MOVBE Instruction, Move Data after Swapping Bytes */
	kCPUIDFeature_POPCNT         = 32 + 23, /* POPCNT Instruction, Populate the Count of Number of Bits Set to 1 */
	kCPUIDFeature_TSCD           = 32 + 24, /* TSC Dead Line */
	kCPUIDFeature_AESNI          = 32 + 25, /* Intel AES New Instructions, Advanced Encryption Standard */
	kCPUIDFeature_XSAVE          = 32 + 26, /* XSAVE */
	kCPUIDFeature_OSXSAVE        = 32 + 27, /* XSAVE Enabled by OS */
	kCPUIDFeature_AVX            = 32 + 28, /* AVX, Advanced Vector Extensions */
	kCPUIDFeature_F16C           = 32 + 29, /* CVT16, Half-Precision Floating Point */
	kCPUIDFeature_RDRAND         = 32 + 30, /* RDRAND Instruction */
	kCPUIDFeature_RESERVED31     = 32 + 31, /* Bit 31 is Reserved */
	/* 00000007h EBX */
	kCPUIDFeature_FSGSBASE       = 64 + 0,  /* FS/GS Base Read/Write */
	kCPUIDFeature_TSCADJUST      = 64 + 1,  /* IA32_TSC_ADJUST MSR */
	kCPUIDFeature_RESERVED2      = 64 + 2,  /* Bit 2 is Reserved */
	kCPUIDFeature_HLE            = 64 + 4,  /* HLE, Hardware Lock Elision : XAQUIRE, XRELEASE, XTEST Instructions */
	kCPUIDFeature_BMI1           = 64 + 3,  /* BMI1, Bit Manipulation Instructions */
	kCPUIDFeature_AVX2           = 64 + 5,  /* AVX2, Advanced Vector Extensions */
	kCPUIDFeature_RESERVEDEBX6   = 64 + 6,  /* Bit 6 is Reserved */
	kCPUIDFeature_SMEP           = 64 + 7,  /* SMPE, Supervisor Mode Execution Prevention */
	kCPUIDFeature_BMI2           = 64 + 8,  /* BMI1, Bit Manipulation Instructions */
	kCPUIDFeature_ERMS           = 64 + 9,  /* Enhanced REP MOVSB/STOSB */
	kCPUIDFeature_INVPCID        = 64 + 10, /* INVPCID Instruction, Invalidate Process Context Identifier */
	kCPUIDFeature_RTM            = 64 + 11, /* RTM, Restricted Transactional Memory : XBEGIN, XABORT, XEND Instructions */
	kCPUIDFeature_QM             = 64 + 12, /* Quality of Service Monitoring */
	kCPUIDFeature_DEPFPP         = 64 + 13, /* Deprecates FPU CS and FPU DS */
	kCPUIDFeature_MPX            = 64 + 14, /* Intel MPX, Memory Protection Extensions */
	kCPUIDFeature_RESERVEDEBX15  = 64 + 15, /* Bit 15 is Reserved */
	kCPUIDFeature_AVX512F        = 64 + 16, /* AVX512 Foundation */
	kCPUIDFeature_RESERVEDEBX17  = 64 + 17, /* Bit 17 is Reserved */
	kCPUIDFeature_RDSEED         = 64 + 18, /* RDSEED Instruction */
	kCPUIDFeature_ADX            = 64 + 19, /* ADCX/ADOX Instructions, Unsigned Integer Addition with Carry/Overflow Flag */
	kCPUIDFeature_SMAP           = 64 + 20, /* SMAP, Supervisor Mode Access Prevention */
	kCPUIDFeature_RESERVEDEBX21  = 64 + 21, /* Bit 21 is Reserved */
	kCPUIDFeature_RESERVEDEBX22  = 64 + 22, /* Bit 22 is Reserved */
	kCPUIDFeature_RESERVEDEBX23  = 64 + 23, /* Bit 23 is Reserved */
	kCPUIDFeature_RESERVEDEBX24  = 64 + 24, /* Bit 24 is Reserved */
	kCPUIDFeature_PT             = 64 + 25, /* PT, Processor Trace */
	kCPUIDFeature_AVX512PF       = 64 + 26, /* AVX512 Prefetch */
	kCPUIDFeature_AVX512ER       = 64 + 27, /* AVX512 Exponential and Reciprocal */
	kCPUIDFeature_AVX512CD       = 64 + 28, /* AVX512 Conflict Detection */
	kCPUIDFeature_SHA            = 64 + 29, /* Intel SHA Extensions - Secure Hash Algorithm */
	kCPUIDFeature_RESERVEDEBX30  = 64 + 30, /* Bit 30 is Reserved */
	kCPUIDFeature_RESERVEEBXD31  = 64 + 31, /* Bit 31 is Reserved */
	/* 80000001h EDX */
	/* on AMD, bits 80000001h EDX 0:17 are same as 00000001h EDX 0:17 */
	kCPUIDFeature_RESERVEDEDXE18 = 96 + 18, /* Bit 18 is Reserved */
	kCPUIDFeature_MP             = 96 + 19, /* MP, Multiprocessor Capable */
	kCPUIDFeature_NX             = 96 + 20, /* NX, No Execution Protection */
	kCPUIDFeature_RESERVEDEDXE21 = 96 + 21, /* Bit 21 is Reserved */
	kCPUIDFeature_MMXEXT         = 96 + 22, /* AMD Extensions to MMX Instructions */
	/* on AMD, bits 80000001h EDX 23:24 are same as 00000001h EDX 23:24 */
	kCPUIDFeature_FFXSR          = 96 + 25, /* FXSAVE/FXSTOR Optimizations */
	kCPUIDFeature_PAGE1GB        = 96 + 26, /* 1Gb Large Page Support */
	kCPUIDFeature_RDTSCP         = 96 + 27, /* RDTSCP Instruction */
	kCPUIDFeature_RESERVEDEDXE28 = 96 + 28, /* Bit 28 is Reserved */
	kCPUIDFeature_EM64T          = 96 + 29, /* EM64T, aka Intel 64, aka AMD64 */
	kCPUIDFeature_3DNOW          = 96 + 30, /* AMD 3DNow! */
	kCPUIDFeature_E3DNOW         = 96 + 31, /* AMD Enhanced 3DNow! */
	/* 800000001h ECX */
	kCPUIDFeature_LAHFSAHF       = 128 + 0,  /* LAHF and SAHF Instructions in 64-bit mode */
	kCPUIDFeature_SVM            = 128 + 2,  /* AMD SVM, Secure Virtual Machine, aka AMD-V (AMD Virtualization) */
	kCPUIDFeature_EAS            = 128 + 3,  /* Extended APIC Space */
	kCPUIDFeature_CR8            = 128 + 4,  /* LOCK MOV from/to CR0 = MOV from/to CR8 */
	kCPUIDFeature_LZCNT          = 128 + 5,  /* LZCNT Instruction, Count the Number of Leading Zeros */
	kCPUIDFeature_SSE4A          = 128 + 6,  /* SSE 4a, Streaming SIMD Extensions */
	kCPUIDFeature_MSSE           = 128 + 7,  /* Misaligned SSE */
	kCPUIDFeature_PREFETCHW      = 128 + 8,  /* 3DNow! PREFETCH and PREFETCHW */
	kCPUIDFeature_OSVW           = 128 + 9,  /* OS Visible Workaround */
	kCPUIDFeature_IBS            = 128 + 10, /* IBS, Instruction Based Sampling */
	kCPUIDFeature_XOP            = 128 + 11, /* AMD XOP, Extended Operation Support */
	kCPUIDFeature_SKINIT         = 128 + 12, /* SKINIT, Secure Init and Jump with Attestation */
	kCPUIDFeature_WDT            = 128 + 13, /* WDT, Watchdog Timer */
	kCPUIDFeature_RESERVEDECXE14 = 128 + 14, /* Bit 14 is Reserved */
	kCPUIDFeature_LWP            = 128 + 15, /* LWT, Light-Weight Profiling */
	kCPUIDFeature_FMA4           = 128 + 16, /* AMD FMA4, 4-Operands Fused Multiply-Add */
	kCPUIDFeature_TCE            = 128 + 17, /* TCE, Translation Cache Extension */
	kCPUIDFeature_RESERVEDECXE18 = 128 + 18, /* Bit 18 is Reserved */
	kCPUIDFeature_NODEID         = 128 + 19, /* Node ID */
	kCPUIDFeature_RESERVEDECXE20 = 128 + 20, /* Bit 20 is Reserved */
	kCPUIDFeature_TBM            = 128 + 21, /* TBM, Translation Bit Manipulation */
	kCPUIDFeature_TOPX           = 128 + 22  /* Topology Extensions */
	/* bits 23:31 are currently reserved and not yet defined */
}
CPUIDFeature;

typedef enum CacheLevel_t
{
	kCacheLevel_None = 0,
	kCacheLevel_TLBData,
	kCacheLevel_TLBCode,
	kCacheLevel_TLB4KData,
	kCacheLevel_TLB4KCode,
	kCacheLevel_TLB2M4MData,
	kCacheLevel_TLB2M4MCode,
	kCacheLevel_TLB0Data,
	kCacheLevel_TLB0Code,
	kCacheLevel_SharedTLB2,
	kCacheLevel_Trace,
	kCacheLevel_L1Data,
	kCacheLevel_L1Code,
	kCacheLevel_L2,
	kCacheLevel_L3,
	kCacheLevel_Max
}
CacheLevel;

typedef struct CacheInfo_t
{
	CacheLevel level;
	uint32_t size;
	uint32_t ways;
	uint32_t line;
	uint32_t sector;
}
CacheInfo;

typedef struct ModelInfo_t
{
	uint8_t stepping;
	uint8_t model;
	uint8_t family;
	uint8_t type;
	uint8_t emodel;
	uint8_t efamily;
}
ModelInfo;

uint8_t Check80286();
uint8_t Check80386();
uint8_t CheckCPUID();
uint8_t CheckCPUIDFeature(CPUIDFeature feature);
void CPUIDModelInfo(ModelInfo * pOutInfo);
void CPUIDCacheInfo(CacheInfo * pOutInfo);

#ifdef __cplusplus
}
#endif

#endif /* __CPUID_H__DE2FCA61_F4AB_430E_BB9A_4278D79DB9BE__ */
