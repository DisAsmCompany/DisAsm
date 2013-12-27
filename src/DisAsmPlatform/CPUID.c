/*
 * Filename: CPUID.c
 * Author:   DisAsmCompany
 * Date:     27/12/2013
 *
 * Description: CPU features identification
 *              
 *
 *
 */

#include "../DisAsm/DisAsm"
#include "DisAsmPlatform"

#define FEATURE_INDEX(x) ((x) >> 5)
#define FEATURE_SHIFT(x) (1 << ((x) & 0x1F))

uint8_t CheckCPUIDFeature(CPUIDFeature feature)
{
	/*
	unified array of CPUID features
	features[0] = 00000001h EDX
	features[1] = 00000001h ECX
	features[2] = 00000007h EBX
	features[3] = 80000001h EDX
	features[4] = 80000001h ECX
	*/
	static uint8_t checked;
	static uint32_t features[5];

	/* did we already check for features? */
	if (!checked)
	{
		if (CheckCPUID())
		{
			uint32_t MaxBasicLevel = CallCPUID(0x00000000UL, 0, NULL, NULL, NULL, NULL);
			uint32_t MaxExtendedLevel = CallCPUID(0x80000000UL, 0, NULL, NULL, NULL, NULL);

			if (MaxBasicLevel >= 0x00000001UL)
			{
				CallCPUID(0x00000001UL, 0, NULL, NULL, &features[1], &features[0]);
				
				if (MaxBasicLevel >= 0x00000007UL)
				{
					CallCPUID(0x00000007UL, 0, NULL, &features[2], NULL, NULL);
				}
			}
			if (MaxExtendedLevel >= 0x80000001UL)
			{
				CallCPUID(0x80000001UL, 0, NULL, NULL, &features[4], &features[3]);
			}
			/* for AVX, AVX2, AVX512 check the OS support
			http://software.intel.com/en-us/articles/how-to-detect-new-instruction-support-in-the-4th-generation-intel-core-processor-family
			*/
			{
				native_t xcr0 = 0;
				if (features[FEATURE_INDEX(kCPUIDFeature_OSXSAVE)] & FEATURE_SHIFT(kCPUIDFeature_OSXSAVE))
				{
					xcr0 = CallXGETBV();
				}
				if (!(xcr0 & kXCR0_EnabledMask))
				{
					features[FEATURE_INDEX(kCPUIDFeature_AVX)]  &= ~FEATURE_SHIFT(kCPUIDFeature_AVX);
					features[FEATURE_INDEX(kCPUIDFeature_AVX2)] &= ~FEATURE_SHIFT(kCPUIDFeature_AVX2);
				}
				if (!(xcr0 & (kXCR0_EnabledMask | kXCR0_OpMask)))
				{
					features[FEATURE_INDEX(kCPUIDFeature_AVX512F)]  &= ~FEATURE_SHIFT(kCPUIDFeature_AVX512F);
					features[FEATURE_INDEX(kCPUIDFeature_AVX512PF)] &= ~FEATURE_SHIFT(kCPUIDFeature_AVX512PF);
					features[FEATURE_INDEX(kCPUIDFeature_AVX512ER)] &= ~FEATURE_SHIFT(kCPUIDFeature_AVX512ER);
					features[FEATURE_INDEX(kCPUIDFeature_AVX512CD)] &= ~FEATURE_SHIFT(kCPUIDFeature_AVX512CD);
				}
			}
		}
		checked = 1;
	}
	return (features[FEATURE_INDEX(feature)] & FEATURE_SHIFT(feature)) ? 1 : 0;
}

uint8_t Check80286()
{
	/* Bits 12-15 are always set on the 8086 and always clear on 80386 and later */
	native_t kFlags8086 = (1 << 12) | (1 << 13) | (1 << 14) | (1 << 15);
	uint8_t supported = 0;
	/* clear bits 12-15 */
	native_t eflags = ReadEFLAGS();
	WriteEFLAGS(eflags & ~kFlags8086);
	supported = (0 == (ReadEFLAGS() & kFlags8086)) ? 1 : 0;
	WriteEFLAGS(eflags);
	return supported;
}

uint8_t Check80386()
{
	/* The AC flag (bit 18) is always set on 80386 and later */
	native_t kFlag80386 = 1 << kEFLAGS_AC;
	uint8_t supported = 0;
	native_t eflags = ReadEFLAGS();
	WriteEFLAGS(eflags ^ kFlag80386);
	supported = ((eflags & kFlag80386) != (ReadEFLAGS() & kFlag80386)) ? 1 : 0;
	WriteEFLAGS(eflags);
	return supported;
}

uint8_t CheckCPUID()
{
	/*
	The ID flag (bit 21) in the EFLAGS register indicates support for the CPUID instruction.
	If a software procedure can set and clear this flag, 
	the processor executing the procedure supports the CPUID instruction. 
	This instruction operates the same in non-64-bit modes and 64-bit mode.
	*/
    native_t kFlagCPUID = 1 << kEFLAGS_ID;
    uint8_t supported = 0;
    native_t eflags = ReadEFLAGS();
    WriteEFLAGS(eflags ^ kFlagCPUID);
	supported = ((eflags & kFlagCPUID) != (ReadEFLAGS() & kFlagCPUID)) ? 1 : 0;
    WriteEFLAGS(eflags);
    return supported;
}

void CPUIDModelInfo(ModelInfo * pOutInfo)
{
	if (CheckCPUID() && CallCPUID(0x00000000UL, 0, NULL, NULL, NULL, NULL) >= 0x00000001UL)
	{
		uint32_t info = CallCPUID(0x00000001UL, 0, NULL, NULL, NULL, NULL);
		pOutInfo->stepping = (uint8_t)(info & 0x0F);
		pOutInfo->model    = (uint8_t)((info >> 4) & 0x0F);
		pOutInfo->family   = (uint8_t)((info >> 8) & 0x0F);
		pOutInfo->type     = (uint8_t)((info >> 12) & 0x03);
		pOutInfo->emodel   = (uint8_t)((info >> 16) & 0x0F);
		pOutInfo->efamily  = (uint8_t)((info >> 20) & 0xFF);
	}
}

#define K4 4
#define M2 2048
#define M4 4096

static const CacheInfo IntelCacheDescriptors[] =
{
	{kCacheLevel_None,      0, 0, 0 , 0}, /* 01h : Null descriptor, this byte contains no information */
	{kCacheLevel_TLBCode,  K4, 4, 32, 0}, /* 01h : Instruction TLB: 4 KByte pages,4-way set associative, 32 entries */
	{kCacheLevel_TLBCode,  M4, 0, 2 , 0}, /* 02h : Instruction TLB: 4 MByte pages, fully associative, 2 entries */
	{kCacheLevel_TLBData,  K4, 4, 64, 0}, /* 03h : Data TLB: 4 KByte pages, 4-way set associative, 64 entries */
	{kCacheLevel_TLBData,  M4, 4, 8 , 0}, /* 04h : Data TLB: 4 MByte pages, 4-way set associative, 8 entries */
	{kCacheLevel_TLBData,  M4, 4, 32, 0}, /* 05h : Data TLB: 4 MByte pages, 4-way set associative, 32 entries */
	{kCacheLevel_L1Code,    8, 4, 32, 0}, /* 06h : 1st-level instruction cache: 8 KBytes, 4-way set associative, 32 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 07h */
	{kCacheLevel_L1Code,   16, 4, 32, 0}, /* 08h : 1st-level instruction cache: 16 KBytes, 4-way set associative, 32 byte line size */
	{kCacheLevel_L1Code,   32, 4, 64, 0}, /* 09h : 1st-level instruction cache: 32KBytes, 4-way set associative, 64 byte line size */
	{kCacheLevel_L1Data,    8, 2, 32, 0}, /* 0Ah : 1st-level data cache: 8 KBytes, 2-way set associative, 32 byte line size */
	{kCacheLevel_TLBCode,  M4, 4, 4 , 0}, /* 0Bh : Instruction TLB: 4 MByte pages,4-way set associative, 4 entries */
	{kCacheLevel_L1Data,   16, 4, 32, 0}, /* 0Ch : 1st-level data cache: 16 KBytes, 4-way set associative,32 byte line size */
	{kCacheLevel_L1Data,   16, 4, 64, 0}, /* 0Dh : 1st-level data cache: 16 KBytes, 4-way set associative,64 byte line size */
	{kCacheLevel_L1Data,   24, 6, 64, 0}, /* 0Eh : 1st-level data cache: 24 KBytes, 6-way set associative,64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 0Fh */

	{kCacheLevel_L1Data, 16, 4, 32, 0}, /* 10h : [IA-64] data L1 cache, 16 KB, 4 ways, 32 byte lines */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 11h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 12h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 13h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 14h */
	{kCacheLevel_L1Code, 16, 4, 32, 0}, /* 15h : [IA-64] code L1 cache, 16 KB, 4 ways, 32 byte lines */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 16h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 17h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 18h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 19h */
	{kCacheLevel_L2, 96, 6, 64, 0}, /* 1Ah : [IA-64] code and data L2 cache, 96 KB, 6 ways, 64 byte lines */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 1Bh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 1Ch */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 1Dh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 1Eh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 1Fh */

	{kCacheLevel_None, 0, 0, 0, 0}, /* 20h */
	{kCacheLevel_L2,  256,  8, 64, 0}, /* 21h : 2nd-level cache: 256 KBytes, 8-way set associative, 64 byte line size */
	{kCacheLevel_L3,  512,  4, 64, 2}, /* 22h : 3rd-level cache: 512 KBytes, 4-way set associative, 64 byte line size, 2 lines per sector */
	{kCacheLevel_L3, 1024,  8, 64, 2}, /* 23h : 3rd-level cache: 1 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector */
	{kCacheLevel_L2, 1024, 16, 64, 0}, /* 24h : 2nd-level cache: 1 MBytes, 16-way set associative, 64 byte line size */
	{kCacheLevel_L3, 2048,  8, 64, 2}, /* 25h : 3rd-level cache: 2 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 26h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 27h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 28h */
	{kCacheLevel_L3, 4096,  8, 64, 2}, /* 29h : 3rd-level cache: 4 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 2Ah */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 2Bh */
	{kCacheLevel_L1Data, 32, 8, 64, 0}, /* 2Ch : 1st-level data cache: 32 KBytes, 8-way set associative,64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 2Dh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 2Eh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 2Fh */

	{kCacheLevel_L1Code, 32, 8, 64, 0}, /* 30h : 1st-level instruction cache: 32 KBytes, 8-way set associative, 64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 31h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 32h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 33h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 34h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 35h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 36h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 37h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 38h */
	{kCacheLevel_L2, 128, 4, 64, 1}, /* 39h : [???] code and data L2 cache, 128 KB, 4 ways, 64 byte lines, sectored */
	{kCacheLevel_L2, 192, 6, 64, 1}, /* 3Ah : [???] code and data L2 cache, 192 KB, 6 ways, 64 byte lines, sectored */
	{kCacheLevel_L2, 128, 2, 64, 1}, /* 3Bh : [???] code and data L2 cache, 128 KB, 2 ways, 64 byte lines, sectored */
	{kCacheLevel_L2, 256, 4, 64, 1}, /* 3Ch : [???] code and data L2 cache, 256 KB, 4 ways, 64 byte lines, sectored */
	{kCacheLevel_L2, 384, 6, 64, 1}, /* 3Dh : [???] code and data L2 cache, 384 KB, 6 ways, 64 byte lines, sectored */
	{kCacheLevel_L2, 512, 4, 64, 1}, /* 3Eh : [???] code and data L2 cache, 512 KB, 4 ways, 64 byte lines, sectored */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 3Fh */

	{kCacheLevel_None,   0,  0,  0, 0}, /* 40h : No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache */
	{kCacheLevel_L2,   128,  4, 32, 0}, /* 41h : 2nd-level cache: 128 KBytes, 4-way set associative, 32 byte line size */
	{kCacheLevel_L2,   256,  4, 32, 0}, /* 42h : 2nd-level cache: 256 KBytes, 4-way set associative, 32 byte line size */
	{kCacheLevel_L2,   512,  4, 32, 0}, /* 43h : 2nd-level cache: 512 KBytes, 4-way set associative, 32 byte line size */
	{kCacheLevel_L2,  1024,  4, 32, 0}, /* 44h : 2nd-level cache: 1 MByte, 4-way set associative, 32 byte line size */
	{kCacheLevel_L2,  2048,  4, 32, 0}, /* 45h : 2nd-level cache: 2 MByte, 4-way set associative, 32 byte line size */
	{kCacheLevel_L3,  4096,  4, 64, 0}, /* 46h : 3rd-level cache: 4 MByte, 4-way set associative, 64 byte line size */
	{kCacheLevel_L3,  8192,  8, 64, 0}, /* 47h : 3rd-level cache: 8 MByte, 8-way set associative, 64 byte line size */
	{kCacheLevel_L2,  3072, 12, 64, 0}, /* 48h : 2nd-level cache: 3MByte, 12-way set associative, 64 byte line size */
	{kCacheLevel_L3,  4096, 16, 64, 0}, /* 49h : 3rd-level cache: 4MB, 16-way set associative, 64-byte line size (Intel Xeon processor MP, Family 0FH, Model 06H); */
	{kCacheLevel_L3,  6144, 12, 64, 0}, /* 4Ah : 3rd-level cache: 6MByte, 12-way set associative, 64 byte line size */
	{kCacheLevel_L3,  8192, 16, 64, 0}, /* 4Bh : 3rd-level cache: 8MByte, 16-way set associative, 64 byte line size */
	{kCacheLevel_L3, 12288, 12, 64, 0}, /* 4Ch : 3rd-level cache: 12MByte, 12-way set associative, 64 byte line size */
	{kCacheLevel_L3, 16384, 16, 64, 0}, /* 4Dh : 3rd-level cache: 16MByte, 16-way set associative, 64 byte line size */
	{kCacheLevel_L2,  6144, 24, 64, 0}, /* 4Eh : 2nd-level cache: 6MByte, 24-way set associative, 64 byte line size */
	{kCacheLevel_TLBCode , K4,           0, 32 , 0}, /* 4Fh : Instruction TLB: 4 KByte pages, 32 entries */

	{kCacheLevel_TLBCode , K4 | M2 | M4, 0, 64 , 0}, /* 50h : Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 64 entries */
	{kCacheLevel_TLBCode , K4 | M2 | M4, 0, 128, 0}, /* 51h : Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 128 entries */
	{kCacheLevel_TLBCode , K4 | M2 | M4, 0, 256, 0}, /* 52h : Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 256 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 53h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 54h */
	{kCacheLevel_TLBCode,  M2 | M4, 0, 7  , 0}, /* 55h : Instruction TLB: 2-MByte or 4-MByte pages, fully associative, 7 entries */
	{kCacheLevel_TLB0Data, K4,      4, 16 , 0}, /* 56h : Data TLB0: 4 MByte pages, 4-way set associative, 16 entries */
	{kCacheLevel_TLB0Data, K4,      4, 16 , 0}, /* 57h : Data TLB0: 4 KByte pages, 4-way associative, 16 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 58h */
	{kCacheLevel_TLB0Data, K4,      0, 16 , 0}, /* 59h : Data TLB0: 4 KByte pages, fully associative, 16 entries */
	{kCacheLevel_TLB0Data, M2 | M4, 4, 32 , 0}, /* 5Ah : Data TLB0: 2-MByte or 4 MByte pages, 4-way set associative, 32 entries */
	{kCacheLevel_TLBData,  K4 | M4, 0, 64 , 0}, /* 5Bh : Data TLB: 4 KByte and 4 MByte pages, 64 entries */
	{kCacheLevel_TLBData,  K4 | M4, 0, 128, 0}, /* 5Ch : Data TLB: 4 KByte and 4 MByte pages,128 entries */
	{kCacheLevel_TLBData,  K4 | M4, 0, 256, 0}, /* 5Dh : Data TLB: 4 KByte and 4 MByte pages,256 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 5Eh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 5Fh */

	{kCacheLevel_L1Data, 16, 8, 64, 0}, /* 60h : 1st-level data cache: 16 KByte, 8-way set associative,64 byte line size */
	{kCacheLevel_TLBCode, 4, 0, 48, 0}, /* 61h : Instruction TLB: 4 KByte pages, fully associative, 48 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 62h */
	{kCacheLevel_TLBData, 0x100000, 4, 4, 0}, /* 63h : Data TLB: 1 GByte pages, 4-way set associative, 4 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 64h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 65h */
	{kCacheLevel_L1Data, 8,  4, 64, 0}, /* 66h : 1st-level data cache: 8 KByte, 4-way set associative, 64 byte line size */
	{kCacheLevel_L1Data, 16, 4, 64, 0}, /* 67h : 1st-level data cache: 16 KByte, 4-way set associative,64 byte line size */
	{kCacheLevel_L1Data, 32, 4, 64, 0}, /* 68h : 1st-level data cache: 32 KByte, 4-way set associative,64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 69h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 6Ah */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 6Bh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 6Ch */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 6Dh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 6Eh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 6Fh */

	{kCacheLevel_Trace, 12, 8, 0, 0}, /* 70h : Trace cache: 12 mu-op, 8-way set associative */
	{kCacheLevel_Trace, 16, 8, 0, 0}, /* 71h : Trace cache: 16 mu-op, 8-way set associative */
	{kCacheLevel_Trace, 32, 8, 0, 0}, /* 72h : Trace cache: 32 mu-op, 8-way set associative */
	{kCacheLevel_Trace, 64, 8, 0, 0}, /* 72h : Trace cache: [???] 64 mu-op, 8-way set associative */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 74h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 75h */
	{kCacheLevel_TLBCode, M2 | M4, 0, 8, 0}, /* 76h : Instruction TLB: 2M/4M pages, fully associative, 8 entries */
	{kCacheLevel_L1Code, 16, 4, 64, 1}, /* 77h : [IA-64] : code L1 cache, 16 KB, 4 ways, 64 byte lines, sectored */
	{kCacheLevel_L2, 1024, 4,  64, 0}, /* 78h : 2nd-level cache: 1 MByte, 4-way set associative, 64byte line size */
	{kCacheLevel_L2,  128, 8,  64, 2}, /* 79h : 2nd-level cache: 128 KByte, 8-way set associative, 64 byte line size, 2 lines per sector */
	{kCacheLevel_L2,  256, 8,  64, 2}, /* 7Ah : 2nd-level cache: 256 KByte, 8-way set associative, 64 byte line size, 2 lines per sector */
	{kCacheLevel_L2,  512, 8,  64, 2}, /* 7Bh : 2nd-level cache: 512 KByte, 8-way set associative, 64 byte line size, 2 lines per sector */
	{kCacheLevel_L2, 1024, 8,  64, 2}, /* 7Ch : 2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size, 2 lines per sector */
	{kCacheLevel_L2, 2048, 8,  64, 0}, /* 7Dh : 2nd-level cache: 2 MByte, 8-way set associative, 64byte line size */
	{kCacheLevel_L2,  256, 8, 128, 1}, /* 7Eh : [IA-64] : code and data L2 cache, 256 KB, 8 ways, 128 byte lines, sectored */
	{kCacheLevel_L2,  512, 2,  64, 0}, /* 7Fh : 2nd-level cache: 512 KByte, 2-way set associative, 64-byte line size */

	{kCacheLevel_L2,  512, 8, 64, 0}, /* 80h : 2nd-level cache: 512 KByte, 8-way set associative, 64-byte line size */
	{kCacheLevel_L2,  128, 8, 32, 0}, /* 81h : [???] 2nd-level cache: 128 KByte, 8-way set associative, 32-byte line size */
	{kCacheLevel_L2,  256, 8, 32, 0}, /* 82h : 2nd-level cache: 256 KByte, 8-way set associative, 32 byte line size */
	{kCacheLevel_L2,  512, 8, 32, 0}, /* 83h : 2nd-level cache: 512 KByte, 8-way set associative, 32 byte line size */
	{kCacheLevel_L2, 1024, 8, 32, 0}, /* 84h : 2nd-level cache: 1 MByte, 8-way set associative, 32 byte line size */
	{kCacheLevel_L2, 2048, 8, 32, 0}, /* 85h : 2nd-level cache: 2 MByte, 8-way set associative, 32 byte line size */
	{kCacheLevel_L2,  512, 4, 64, 0}, /* 86h : 2nd-level cache: 512 KByte, 4-way set associative, 64 byte line size */
	{kCacheLevel_L2, 1024, 8, 64, 0}, /* 87h : 2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size */
	{kCacheLevel_L3, 2048, 4, 64, 0}, /* 88h : [IA-64] code and data L3 cache, 2048 KB, 4 ways, 64 byte lines */
	{kCacheLevel_L3, 4096, 4, 64, 0}, /* 89h : [IA-64] code and data L3 cache, 4096 KB, 4 ways, 64 byte lines */
	{kCacheLevel_L3, 8192, 4, 64, 0}, /* 8Ah : [IA-64] code and data L3 cache, 8192 KB, 4 ways, 64 byte lines */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 8Bh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 8Ch */
	{kCacheLevel_L3, 3072, 12, 128, 0}, /* 8Dh : [IA-64] code and data L3 cache, 3072 KB, 12 ways, 128 byte lines */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 8Eh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 8Fh */

	{kCacheLevel_TLBCode, K4 | M4, 0, 64, 0}, /* 90h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 91h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 92h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 93h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 94h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 95h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 96h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 97h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 98h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 99h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 9Ah */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 9Bh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 9Ch */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 9Dh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 9Eh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* 9Fh */

	{kCacheLevel_None, 0, 0, 0, 0}, /* A0h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A1h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A2h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A3h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A4h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A5h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A6h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A7h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A8h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* A9h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* AAh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* ABh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* ACh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* ADh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* AEh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* AFh */

	{kCacheLevel_TLBCode,  K4, 4, 128, 0}, /* B0h : Instruction TLB: 4 KByte pages, 4-way set associative, 128 entries */
	{kCacheLevel_TLBCode,  M2, 4,  64, 0}, /* B1h : Instruction TLB: 2M pages, 4-way, 8 entries or 4M pages, 4-way, 4 entries */
	{kCacheLevel_TLBCode,  K4, 4,  64, 0}, /* B2h : Instruction TLB: 4KByte pages,4-way set associative, 64 entries */
	{kCacheLevel_TLBData,  K4, 4, 128, 0}, /* B3h : Data TLB: 4 KByte pages, 4-way set associative, 128 entries */
	{kCacheLevel_TLBData,  K4, 4, 256, 0}, /* B4h : Data TLB: 4 KByte pages, 4-way associative, 256 entries */
	{kCacheLevel_TLBCode,  K4, 8,  64, 0}, /* B5h : Instruction TLB: 4KByte pages,8-way set associative, 64 entries */
	{kCacheLevel_TLBCode,  K4, 8, 128, 0}, /* B6h : Instruction TLB: 4KByte pages, 8-way set associative, 128 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* B7h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* B8h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* B9h */
	{kCacheLevel_TLBData,  K4, 4,  64, 0}, /* BAh : Data TLB: 4 KByte pages,4-way associative, 64 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* BBh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* BCh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* BDh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* BEh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* BFh */

	{kCacheLevel_TLBData,    K4 | M4, 4,    8, 0}, /* C0h : Data TLB: 4 KByte and 4 MByte pages, 4-way associative, 8 entries */
	{kCacheLevel_SharedTLB2, K4 | M4, 8, 1024, 0}, /* C1h : Shared 2nd-Level TLB: 4 KByte/2MByte pages, 8-way associative, 1024 entries */
	{kCacheLevel_TLBData,    M2 | M4, 4,   16, 0}, /* C2h : Data TLB: 2 MByte/4MByte pages,4-way associative, 16 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* C3h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* C4h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* C5h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* C6h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* C7h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* C8h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* C9h */
	{kCacheLevel_SharedTLB2, K4, 4, 512, 0}, /* CAh : Shared 2nd-Level TLB: 4 KByte pages, 4-way associative, 512 entries */
	{kCacheLevel_None, 0, 0, 0, 0}, /* CBh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* CCh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* CDh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* CEh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* CFh */

	{kCacheLevel_L3,  512,   4, 64, 0}, /* D0h : 3rd-level cache: 512 KByte, 4-way set associative, 64 byte line size */
	{kCacheLevel_L3, 1024,   4, 64, 0}, /* D1h : 3rd-level cache: 1 MByte, 4-way set associative, 64 byte line size */
	{kCacheLevel_L3, 2048,   4, 64, 0}, /* D2h : 3rd-level cache: 2 MByte, 4-way set associative, 64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* D3h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* D4h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* D5h */
	{kCacheLevel_L3, 1024,   8, 64, 0}, /* D6h : 3rd-level cache: 1 MByte, 8-way set associative, 64 byte line size */
	{kCacheLevel_L3, 2048,   8, 64, 0}, /* D7h : 3rd-level cache: 2 MByte, 8-way set associative, 64 byte line size */
	{kCacheLevel_L3, 4096,   8, 64, 0}, /* D8h : 3rd-level cache: 4 MByte, 8-way set associative, 64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* D9h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* DAh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* DBh */
	{kCacheLevel_L3, 1536,  12, 64, 0}, /* DCh : 3rd-level cache: 1.5 MByte, 12-way set associative, 64 byte line size */
	{kCacheLevel_L3, 3072,  12, 64, 0}, /* DDh : 3rd-level cache: 3 MByte, 12-way set associative, 64 byte line size */
	{kCacheLevel_L3, 6144,  12, 64, 0}, /* DEh : 3rd-level cache: 6 MByte, 12-way set associative, 64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* DFh */

	{kCacheLevel_None, 0, 0, 0, 0}, /* E0h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* E1h */
	{kCacheLevel_L3, 2048,  12, 64, 0}, /* E2h : 3rd-level cache: 2 MByte, 16-way set associative, 64 byte line size */
	{kCacheLevel_L3, 4096,  12, 64, 0}, /* E3h : 3rd-level cache: 4 MByte, 16-way set associative, 64 byte line size */
	{kCacheLevel_L3, 8192,  12, 64, 0}, /* E4h : 3rd-level cache: 8 MByte, 16-way set associative, 64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* E5h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* E6h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* E7h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* E8h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* E9h */
	{kCacheLevel_L3, 12288, 24, 64, 0}, /* EAh : 3rd-level cache: 12MByte, 24-way set associative, 64 byte line size */
	{kCacheLevel_L3, 18432, 24, 64, 0}, /* EBh : 3rd-level cache: 18MByte, 24-way set associative, 64 byte line size */
	{kCacheLevel_L3, 24576, 24, 64, 0}, /* ECh : 3rd-level cache: 24MByte, 24-way set associative, 64 byte line size */
	{kCacheLevel_None, 0, 0, 0, 0}, /* EDh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* EEh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* EFh */

	{kCacheLevel_Prefetching64,  0, 0, 0, 0}, /* F0h : 64-Byte prefetching */
	{kCacheLevel_Prefetching128, 0, 0, 0, 0}, /* F1h : 128-Byte prefetching */
	{kCacheLevel_None, 0, 0, 0, 0}, /* F2h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* F3h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* F4h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* F5h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* F6h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* F7h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* F8h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* F9h */
	{kCacheLevel_None, 0, 0, 0, 0}, /* FAh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* FBh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* FCh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* FDh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* FEh */
	{kCacheLevel_None, 0, 0, 0, 0}, /* FFh */
};

uint32_t AMDCacheWays(uint32_t field)
{
	uint8_t result = 0;
	switch (field)
	{
	case  1: result =   1; break;
	case  2: result =   2; break;
	case  4: result =   4; break;
	case  6: result =   8; break;
	case  8: result =  16; break;
	case 10: result =  32; break;
	case 11: result =  38; break;
	case 12: result =  64; break;
	case 13: result =  96; break;
	case 14: result = 128; break;
	case 15: result =   0; break;
	default: break;
	}
	return result;
}

void CPUIDCacheInfo(CacheInfo * pOutInfo)
{
	if (CheckCPUID())
	{
		CacheInfo info[kCacheLevel_Max];
		uint32_t MaxBasicLevel = CallCPUID(0x00000000UL, 0, NULL, NULL, NULL, NULL);
		uint32_t MaxExtendedLevel = CallCPUID(0x80000000UL, 0, NULL, NULL, NULL, NULL);
		uint8_t count = 1;
		uint8_t leaf4 = 0;

		if (MaxBasicLevel >= 0x00000002UL)
		{
			/* Intel Way (old) */
			uint8_t descriptors[16];
			uint8_t i;

			for (i = 0; i < count; ++i)
			{
				uint8_t j;
				CallCPUID(0x00000002UL, 0, (uint32_t*)descriptors, (uint32_t*)(descriptors + 4), (uint32_t*)(descriptors + 8), (uint32_t*)(descriptors + 12));
				count = (0 == i) ? descriptors[0] : count;

				for (j = 1; j < 16; ++j)
				{
					const CacheInfo * entry = &IntelCacheDescriptors[descriptors[j]];
					CacheLevel level = entry->level;

					if (0xFF == descriptors[j])
					{
						/* CPUID leaf 2 does not report cache descriptor information, use CPUID leaf 4 to query cache parameters */
						leaf4 = 1;
					}
					if (0x49 == descriptors[j])
					{
						/* 0x49 is tricky value, because it is different for different processors
						3rd-level cache: 4MB, 16-way set associative, 64-byte line size (Intel Xeon processor MP, Family 0FH, Model 06H)
						2nd-level cache: 4 MByte, 16-way set associative, 64byte line size
						*/
						ModelInfo model;
						CPUIDModelInfo(&model);
						if (0x0F == model.family && 0x06 == model.model)
						{
							level = kCacheLevel_L3;
						}
						else
						{
							level = kCacheLevel_L2;
						}
					}
					info[level].level       = level;
					info[level].size        = entry->size;
					info[level].line        = entry->line;
					info[level].ways        = entry->ways;
					info[level].sector      = entry->sector;
				}
			}
		}
		if (leaf4 && MaxBasicLevel >= 0x00000004UL)
		{
			/* Intel Way (new) */
			uint32_t selector = 0;
			uint32_t eax, ebx, ecx;
			for (;;)
			{
				CacheLevel level;
				uint32_t index, type, partitions, sets;
				CallCPUID(0x00000004UL, selector, &eax, &ebx, &ecx, NULL);
				type = eax & 0x1F;
				index = (eax >> 5) & 0x7;

				if (0 == type) break; /* No More Caches */

				switch (index)
				{
				case 1: level = (type == 1) ? kCacheLevel_L1Data : kCacheLevel_L1Code; break;
				case 2: level = kCacheLevel_L2; break;
				case 3: level = kCacheLevel_L3; break;
				default: break;
				}
				/*
				This Cache Size in Bytes
				= (Ways + 1) * (Partitions + 1) * (Line_Size + 1) * (Sets + 1)
				= (EBX[31:22] + 1) * (EBX[21:12] + 1) * (EBX[11:0] + 1) * (ECX + 1)
				*/
				info[level].level = level;
				info[level].ways  = (ebx >> 22) + 1;
				info[level].line  = (ebx & 0xFFF) + 1;
				partitions = ((ebx >> 12) & 0x3FF) + 1;
				sets = ecx + 1;
				info[level].size = (info[level].ways * info[level].line * partitions * sets) >> 10;
				++selector;
			}
		}
		/* AMD Way */
		if (0 == count && MaxExtendedLevel >= 0x80000005UL)
		{
			uint32_t TLB2M4M, TLB4K, L1Code, L1Data;
			CallCPUID(0x80000005UL, 0, &TLB2M4M, &TLB4K, &L1Data, &L1Code);

			info[kCacheLevel_TLB2M4MCode].size = TLB2M4M & 0xFF;
			info[kCacheLevel_TLB2M4MCode].ways = (TLB2M4M >> 8) & 0xFF;
			info[kCacheLevel_TLB2M4MData].size = (TLB2M4M >> 16) & 0xFF;
			info[kCacheLevel_TLB2M4MData].ways = TLB2M4M >> 24;

			info[kCacheLevel_TLB4KCode].size = TLB4K & 0xFF;
			info[kCacheLevel_TLB4KCode].ways = (TLB4K >> 8) & 0xFF;
			info[kCacheLevel_TLB4KData].size = (TLB4K >> 16) & 0xFF;
			info[kCacheLevel_TLB4KData].ways = TLB4K >> 24;

			info[kCacheLevel_L1Data].size = L1Data >> 24;
			info[kCacheLevel_L1Data].ways = (L1Data >> 8) & 0xFF;
			info[kCacheLevel_L1Data].line = L1Data & 0xFF;

			info[kCacheLevel_L1Code].size = L1Code >> 24;
			info[kCacheLevel_L1Code].ways = (L1Code >> 8) & 0xFF;
			info[kCacheLevel_L1Code].line = L1Code & 0xFF;

			if (MaxExtendedLevel >= 0x80000006UL)
			{
				uint32_t L2, L3;
				CallCPUID(0x80000006UL, 0, NULL, NULL, &L2, &L3);

				info[kCacheLevel_L2].size = L2 >> 16;
				info[kCacheLevel_L2].ways = AMDCacheWays((L2 >> 12) & 0x0F);
				info[kCacheLevel_L2].line = L2 & 0xFF;

				info[kCacheLevel_L3].size = 512 * (L3 >> 18);
				info[kCacheLevel_L3].ways = AMDCacheWays((L3 >> 12) & 0x0F);
				info[kCacheLevel_L3].line = L3 & 0xFF;
			}
		}
		if (NULL != pOutInfo)
		{
			pOutInfo->size   = info[pOutInfo->level].size;
			pOutInfo->line   = info[pOutInfo->level].line;
			pOutInfo->ways   = info[pOutInfo->level].ways;
			pOutInfo->sector = info[pOutInfo->level].sector;
		}
	}
}
