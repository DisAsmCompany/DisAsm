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

#pragma once
#ifndef __ASM_H__39FAE327_E4C6_495E_9858_0712114A0257__
#define __ASM_H__39FAE327_E4C6_495E_9858_0712114A0257__

#ifdef __cplusplus
extern "C" {
#endif

native_t ReadEFLAGS();
void WriteEFLAGS(native_t eflags);

uint32_t CallCPUID(uint32_t level, uint32_t selector, uint32_t * outeax, uint32_t * outebx, uint32_t * outecx, uint32_t * outedx);

void CallPREFETCH(void * p);
void CallPREFETCHW(void * p);
void CallPREFETCHT0(void *p);
void CallPREFETCHT1(void *p);
void CallPREFETCHT2(void *p);
void CallPREFETCHNTA(void *p);
void CallCLFLUSH(void *p);

void CallLFENCE();
void CallMFENCE();
void CallSFENCE();

void __cpuidex(int * CPUInfo, int InfoType, int ECXValue);

int64_t CallRDTSC();

native_t CallXGETBV();

#ifdef __cplusplus
}
#endif

#endif /* __ASM_H__39FAE327_E4C6_495E_9858_0712114A0257__ */
