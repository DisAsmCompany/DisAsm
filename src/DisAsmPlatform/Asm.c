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

#if defined(COMP_WATCOMC)

#pragma aux WatcomCallCPUID = \
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

#endif /* defined(COMP_WATCOMC) */

uint32_t CallCPUID(uint32_t level, uint32_t * outeax, uint32_t * outebx, uint32_t * outecx, uint32_t * outedx)
{
    uint32_t _eax = 0, _ebx = 0, _ecx = 0, _edx = 0;
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
#if defined(COMP_WATCOMC)
	WatcomCallCPUID(level, &_eax, &_ebx, &_ecx, &_edx);
#endif /* defined(COMP_WATCOMC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__(
	"cpuid"
	: "=a" (_eax), "=b" (_ebx), "=c" (_ecx), "=d" (_edx)
	: "a" (level)
	);
#endif /* defined(COMP_GNUC) */
    if (outeax) *outeax = _eax;
    if (outebx) *outebx = _ebx;
    if (outecx) *outecx = _ecx;
    if (outedx) *outedx = _edx;
    return _eax;
}

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
	native_t value = 0;
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	value = __readeflags();
#endif /* defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__(
		"pushf\n"
		"pop %%eax"
		: "=a" (value)
		);
#endif /* defined(COMP_GNUC) */
	return value;
}

void WriteEFLAGS(native_t eflags)
{
#if defined(COMP_MICROSOFTC) || defined(COMP_INTELC)
	__writeeflags(eflags);
#endif /* defined(COMP_MICROSOFTC) || defined(COMP_INTELC) */
#if defined(COMP_GNUC)
	__asm__ __volatile__(
		"push %%eax\n"
		"popf"
		:
		: "a" (eflags)
		);
#endif /* defined(COMP_GNUC) */
}

#endif /* defined(COMP_WATCOMC) */

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
	native_t kFlag80386 = 1 << 18;
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
    native_t kFlagCPUID = 1 << 21;
    uint8_t supported = 0;
    native_t eflags = ReadEFLAGS();
    WriteEFLAGS(eflags ^ kFlagCPUID);
	supported = ((eflags & kFlagCPUID) != (ReadEFLAGS() & kFlagCPUID)) ? 1 : 0;
    WriteEFLAGS(eflags);
    return supported;
}
