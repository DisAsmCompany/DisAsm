/*
* Filename: InstructionSet.h
* Author:   DisAsmCompany
* Date:     06/10/2013
*
* Description: information about instruction
*              (opcode, number and types of
*              operands, subset, etc)
*
*/

/* no "pragma once" - header is tricky and supposed to be included twice by design */
#ifndef __INSTRUCTIONSET_H__00822A17_6A19_422B_B627_D10602DAEB62__
#define __INSTRUCTIONSET_H__00822A17_6A19_422B_B627_D10602DAEB62__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

_ENUM_START(InstructionSet, 0)
_ENUM_ELEMENT(GP)         /* General-Purpose */
_ENUM_ELEMENT(x87)        /* x87 FPU */
_ENUM_ELEMENT(MMX)        /* Multi-Media eXtension, Multiple-Math eXtension, Matrix-Math eXtension */
_ENUM_ELEMENT(_3DNow)     /* AMD 3DNow! */
_ENUM_ELEMENT(_3DNowPlus) /* AMD 3DNow!+ aka Extended 3DNow! aka Enhanced 3DNow! */
_ENUM_ELEMENT(SSE)        /* Streaming SIMD Extensions */
_ENUM_ELEMENT(SSE2)       /* Streaming SIMD Extensions 2 */
_ENUM_ELEMENT(SSE3)       /* Streaming SIMD Extensions 3 */
_ENUM_ELEMENT(SSSE3)      /* Supplemental Streaming SIMD Extensions 3 */
_ENUM_ELEMENT(SSE41)      /* Streaming SIMD Extensions 4.1 */
_ENUM_ELEMENT(SSE42)      /* Streaming SIMD Extensions 4.2 */
_ENUM_ELEMENT(SSE4a)      /* Streaming SIMD Extensions 4.a */
_ENUM_ELEMENT(SSE5)       /* Streaming SIMD Extensions 5 */
_ENUM_ELEMENT(AES)        /* Advanced Encryption Standard Instruction Set */
_ENUM_ELEMENT(AVX)        /* Advanced Vector Extensions */    
_ENUM_ELEMENT(AVX2)       /* Advanced Vector Extensions 2 */
_ENUM_ELEMENT(AVX512)     /* Advanced Vector Extensions 512 */
_ENUM_ELEMENT(CVT16)
_ENUM_ELEMENT(XOP)        /* eXtended Operations */
_ENUM_ELEMENT(FMA3)       /* Fused Multiply-Add 3 */
_ENUM_ELEMENT(FMA4)       /* Fused Multiply-Add 4 */
_ENUM_ELEMENT(SHA)        /* Secure Hash Algorithm */
_ENUM_ELEMENT(MPX)        /* Memory-Protection eXtensions */
_ENUM_STOP(InstructionSet, 0)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INSTRUCTIONSET_H__00822A17_6A19_422B_B627_D10602DAEB62__ */
