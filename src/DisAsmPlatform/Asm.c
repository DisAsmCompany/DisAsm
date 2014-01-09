/*
 * Filename: Asm.c
 * Author:   DisAsmCompany
 * Date:     26/12/2013
 *
 * Description: frequently used assembler functions
 *              like CPUID, RDTSC, etc
 *
 *
 */

#include "../DisAsm/DisAsm"
#include "DisAsmPlatform"

#if (defined(COMP_MICROSOFTC) && COMP_VERSION >= COMP_MICROSOFTC2005) || defined(COMP_INTELC)
#include <intrin.h>
#include <xmmintrin.h>
#endif /* (defined(COMP_MICROSOFTC) && COMP_VERSION >= COMP_MICROSOFTC2005) || defined(COMP_INTELC) */

#if defined(COMP_MICROSOFTC)

/* old Microsoft C versions have no __cpuid, __readeflags, __writeeflags available */

#if COMP_VERSION < COMP_MICROSOFTC2005

#define _MM_HINT_T0     1
#define _MM_HINT_T1     2
#define _MM_HINT_T2     3
#define _MM_HINT_NTA    0

void __cpuid(int CPUInfo[4], int InfoType)
{
	__asm
	{
		mov eax, InfoType;
		cpuid;
		mov CPUInfo[0], eax;
		mov CPUInfo[1], ebx;
		mov CPUInfo[2], ecx;
		mov CPUInfo[3], edx;
	}
}

int64_t __rdtsc()
{
	return 0;
}

#endif /* COMP_VERSION <= COMP_MICROSOFTC6 */

#if COMP_VERSION < COMP_MICROSOFTC2005

native_t __readeflags(void)
{
	native_t result;
	__asm
	{
		pushfd;
		pop eax;
		mov result, eax;
	}
	return result;
}

void __writeeflags(native_t value)
{
	__asm
	{
		mov eax, value;
		push eax;
		popfd;
	}
}

#endif /* COMP_VERSION < COMP_MICROSOFTC2005 */

#endif /* defined(COMP_MICROSOFTC) */

#if defined(COMP_WATCOMC)

void WatcomCallCPUID(uint32_t, uint32_t, uint32_t *, uint32_t *, uint32_t *, uint32_t *); 
#pragma aux WatcomCallCPUID = \
".586" \
"push eax" \
"push ebx" \
"push ecx" \
"push edx" \
"mov eax, esi" \
"mov ecx, edi" \
"cpuid" \
"mov esi, [esp]" \
"mov [esi], edx" \
"mov esi, [esp+4]" \
"mov [esi], ecx" \
"mov esi, [esp+8]" \
"mov [esi], ebx" \
"mov esi, [esp+12]" \
"mov [esi], eax" \
"add esp, 16" \
parm [esi] [edi] [eax] [ebx] [ecx] [edx] \
modify [esi edi eax ebx ecx edx];

#endif /* defined(COMP_WATCOMC) */

uint32_t CallCPUID(uint32_t level, uint32_t selector, uint32_t * outeax, uint32_t * outebx, uint32_t * outecx, uint32_t * outedx)
{
    uint32_t _eax = 0, _ebx = 0, _ecx = 0, _edx = 0;
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	/* use intrinsic because x64 doesn't allow inline assembly */
	int info[4] = {0};
	(void) selector;
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
		mov ecx, selector
		cpuid
		mov _eax, eax
		mov _ebx, ebx
		mov _ecx, ecx
		mov _edx, edx
	}
#endif /* defined(COMP_BORLANDC) */
#if defined(COMP_WATCOMC)
	WatcomCallCPUID(level, selector, &_eax, &_ebx, &_ecx, &_edx);
#endif /* defined(COMP_WATCOMC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__(
	"cpuid"
	: "=a" (_eax), "=b" (_ebx), "=c" (_ecx), "=d" (_edx)
	: "a" (level), "c" (selector)
	);
#endif /* defined(COMP_GNUC) */
    if (outeax) *outeax = _eax;
    if (outebx) *outebx = _ebx;
    if (outecx) *outecx = _ecx;
    if (outedx) *outedx = _edx;
    return _eax;
}

#if defined(COMP_WATCOMC)

native_t __readeflags();
void __writeeflags(native_t);

#pragma aux __readeflags = \
	".586" \
	"pushfd" \
	"pop eax" \
	modify [eax];

#pragma aux __writeeflags = \
	".586" \
	"push eax" \
	"popfd" \
	parm [eax] \
	modify [eax];

#endif /* defined(COMP_WATCOMC) */

#if defined(COMP_BORLANDC)

native_t __readeflags()
{
	native_t _eflags;
	__asm
	{
		pushfd
		pop eax
		mov _eflags, eax
	}
	return _eflags;
}

void __writeeflags(native_t _eflags)
{
	__asm
	{
		mov eax, _eflags
		push eax
		popfd
	}
}

#endif /* defined(COMP_BORLANDC) */

native_t ReadEFLAGS()
{
	native_t value = 0;
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) || defined(COMP_WATCOMC) || defined(COMP_BORLANDC)
	value = __readeflags();
#endif /* defined(COMP_MICROSOFTC) || defined(COMP_INTELC) || defined(COMP_WATCOMC) || defined(COMP_BORLANDC) */
#if defined(COMP_GNUC)
#if defined(CPU_X86)
	__asm__ __volatile__(
		"pushf\n"
		"popl %%eax"
		: "=a" (value)
		);
#endif /* defined(CPU_X86) */
#if defined(CPU_X64)
	__asm__ __volatile__(
		"pushf\n"
		"popq %%rax"
		: "=a" (value)
		);
#endif /* defined(CPU_X64) */
#endif /* defined(COMP_GNUC) */
	return value;
}

void WriteEFLAGS(native_t eflags)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) || defined(COMP_WATCOMC) || defined(COMP_BORLANDC)
	__writeeflags(eflags);
#endif /* defined(COMP_MICROSOFTC) || defined(COMP_INTELC) || defined(COMP_WATCOMC) || defined(COMP_BORLANDC) */
#if defined(COMP_GNUC)
#if defined(CPU_X86)
	__asm__ __volatile__(
		"pushl %%eax\n"
		"popf"
		:
		: "a" (eflags)
		);
#endif /* defined(CPU_X86) */
#if defined(CPU_X64)
	__asm__ __volatile__(
		"pushq %%rax\n"
		"popf"
		:
		: "a" (eflags)
		);
#endif /* defined(CPU_X64) */
#endif /* defined(COMP_GNUC) */
}

void CallPREFETCH(void * p)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_m_prefetch(p);
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("prefetch (%0)" :: "d"(p));
#endif /* defined(COMP_GNUC) */
}

void CallPREFETCHW(void * p)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_m_prefetchw(p);
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("prefetchw (%0)" :: "d"(p));
#endif /* defined(COMP_GNUC) */
}
void CallPREFETCHT0(void *p)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_prefetch(p, _MM_HINT_T0);
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("prefetcht0 (%0)" :: "d"(p));
#endif /* defined(COMP_GNUC) */
}

void CallPREFETCHT1(void *p)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_prefetch(p, _MM_HINT_T1);
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("prefetcht1 (%0)" :: "d"(p));
#endif /* defined(COMP_GNUC) */
}

void CallPREFETCHT2(void *p)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_prefetch(p, _MM_HINT_T2);
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("prefetcht1 (%0)" :: "d"(p));
#endif /* defined(COMP_GNUC) */
}

void CallPREFETCHNTA(void *p)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_prefetch(p, _MM_HINT_NTA);
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("prefetchnta (%0)" :: "d"(p));
#endif /* defined(COMP_GNUC) */
}

void CallCLFLUSH(void *p)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_clflush(p);
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("clflush (%0)" :: "d"(p));
#endif /* defined(COMP_GNUC) */
}

void CallLFENCE()
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_lfence();
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("lfence");
#endif /* defined(COMP_GNUC) */
}

void CallMFENCE()
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_mfence();
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("mfence");
#endif /* defined(COMP_GNUC) */
}

void CallSFENCE()
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_sfence();
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("sfence");
#endif /* defined(COMP_GNUC) */
}

void CallPAUSE()
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	_mm_pause();
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__("pause");
#endif /* defined(COMP_GNUC) */
}

int64_t CallRDTSC()
{
	int64_t result = 0;
	/* serialize unfinished instructions */
	CallCPUID(0, 0, NULL, NULL, NULL, NULL);
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	result = __rdtsc();
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
	return result;
}

native_t CallXGETBV()
{
	native_t result = 0;
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	/* we cannot use neither inline assembler, nor intrinsic,
	since XGETBV is pretty new instruction and not supported yet */
	typedef native_t (*code)();
	uint8_t raw[] = {0x33, 0xC9, 0x0F, 0x01, 0xD0, 0xC3}; /* XOR ECX, ECX; XGETBV; RET; */
	code p = (code)(native_t)raw;
	result = p();
#endif /* #if defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	uint32_t _eax, _edx;
	__asm__ __volatile__(
		"xor %%ecx, %%ecx\n"
		".byte 0x0f, 0x01, 0xd0"
		: "=a"(_eax), "=d"(_edx)
		);
	result = _edx;
	result <<= 32;
	result |= _eax;
#endif /* defined(COMP_GNUC) */
	return result;
}
