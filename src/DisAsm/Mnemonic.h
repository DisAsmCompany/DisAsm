/*
* Filename: Mnemonic.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: x86 mnemonics,
*              such as ADD, NOP,
*              INT, etc
*
*/

/* no "pragma once" - header is tricky and supposed to be included twice by design */
#ifndef __MNEMONIC_H__20CAFD53_E4D1_49A5_88DC_47A54ADFD022__
#define __MNEMONIC_H__20CAFD53_E4D1_49A5_88DC_47A54ADFD022__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

_ENUM_START(Mnemonic, 0)
_ENUM_ELEMENT(DB)     /* Data Binary (not decoded instruction) */
_ENUM_ELEMENT(ESCAPE) /* Escape to another OpCode Map */
_ENUM_ELEMENT(ESCAPEX87) /* Escape to CoProcessor Instruction Set */
_ENUM_ELEMENT(ESCAPE3DNOW) /* Escape to 3DNow! Instruction Set */
_ENUM_ELEMENT(DAA)    /* Decimal Adjust AL after Addition */
_ENUM_ELEMENT(AAA)    /* ASCII Adjust AL after Addition */
_ENUM_ELEMENT(DAS)    /* Decimal Adjust AL after Subtraction */
_ENUM_ELEMENT(AAS)    /* ASCII Adjust AL after Subtraction */
_ENUM_ELEMENT(AAM)    /* ASCII Adjust AX after Multiply */
_ENUM_ELEMENT(AAD)    /* ASCII Adjust AX before Division */
_ENUM_ELEMENT(HLT)    /* Halt */
_ENUM_ELEMENT(CMC)    /* Complement Carry Flag */
_ENUM_ELEMENT(NOP)    /* No Operation */
_ENUM_ELEMENT(PAUSE)  /* Pause Spin Loop Hint */
_ENUM_ELEMENT(CLC)    /* Clear Carry Flag */
_ENUM_ELEMENT(STC)    /* Set Carry Flag */
_ENUM_ELEMENT(CLI)    /* Clear Interrupt Flag */
_ENUM_ELEMENT(STI)    /* Set Interrupt Flag */
_ENUM_ELEMENT(CLD)    /* Clear Direction Flag */
_ENUM_ELEMENT(STD)    /* Set Direction Flag */
_ENUM_ELEMENT(MOV)    /* Move */
_ENUM_ELEMENT(MOVZX)  /* Move with Zero Extend */
_ENUM_ELEMENT(PUSH)   /* Push Onto the Stack */
_ENUM_ELEMENT(POP)    /* Pop  From the Stack */
_ENUM_ELEMENT(ADD)    /* Add */
_ENUM_ELEMENT(ADC)    /* Add with Carry */
_ENUM_ELEMENT(AND)    /* Logical And */
_ENUM_ELEMENT(XOR)    /* Logical Exclusive Or */
_ENUM_ELEMENT(OR)     /* Logical Inclusive Or */
_ENUM_ELEMENT(SBB)    /* Integer Subtraction with Borrow */
_ENUM_ELEMENT(SUB)    /* Subtract */
_ENUM_ELEMENT(CMP)    /* Compare Two Operands */
_ENUM_ELEMENT(INC)    /* Increment by One */
_ENUM_ELEMENT(DEC)    /* Decrement by One */
_ENUM_ELEMENT(JMP)    /* Jump */
_ENUM_ELEMENT(JMPE)   /* Reserved for emulator on IPF */
_ENUM_ELEMENT(CALL)   /* Call Procedure */
_ENUM_ELEMENT(TEST)   /* Logical Compare */
_ENUM_ELEMENT(XCHG)   /* Exchange Register/Memory with Register */
_ENUM_ELEMENT(CPUID)  /* CPU Identification */
_ENUM_ELEMENT(RET)    /* Return from Procedure */
_ENUM_ELEMENT(ENTER)  /* Make Stack Frame for Procedure Parameters */
_ENUM_ELEMENT(LEAVE)  /* High Level Procedure Exit */
_ENUM_ELEMENT(_INT)   /* Call to Interrupt Procedure */
_ENUM_ELEMENT(INTO)   /* Call to Interrupt Procedure */
_ENUM_ELEMENT(IRET)   /* Interrupt Return */
_ENUM_ELEMENT(IRETD)  /* Interrupt Return */
_ENUM_ELEMENT(LEA)    /* Load Effective Address */
_ENUM_ELEMENT(NOT)    /* One's Complement Negotiation */
_ENUM_ELEMENT(NEG)    /* Two's Complement Negotiation */
_ENUM_ELEMENT(MUL)    /* Unsigned Multiply */
_ENUM_ELEMENT(IMUL)   /* Signed Multiply */
_ENUM_ELEMENT(DIV)    /* Unsigned Divide */
_ENUM_ELEMENT(IDIV)   /* Signed Divide */
_ENUM_ELEMENT(PUSHA)  /* Push all General-Purpose Registers */
_ENUM_ELEMENT(PUSHAD) /* Push all General-Purpose Registers */
_ENUM_ELEMENT(PUSHF)  /* Push FLAHS Register onto Stack */
_ENUM_ELEMENT(PUSHFD) /* Push EFLAHS Register onto Stack */
_ENUM_ELEMENT(PUSHFQ) /* Push RFLAHS Register onto Stack */
_ENUM_ELEMENT(POPA)   /* Pop all General-Purpose Registers */
_ENUM_ELEMENT(POPAD)  /* Pop all General-Purpose Registers */
_ENUM_ELEMENT(POPF)   /* Pop Stack into FLAGS Register */
_ENUM_ELEMENT(POPFD)  /* Pop Stack into EFLAGS Register */
_ENUM_ELEMENT(POPFQ)  /* Pop Stack into RFLAGS Register */
_ENUM_ELEMENT(SAHF)   /* Store AL into Flags */
_ENUM_ELEMENT(LAHF)   /* Load Flags into AL */
_ENUM_ELEMENT(CBW)    /* Convert Byte to Word */
_ENUM_ELEMENT(CWDE)   /* Convert Word to Double Word */
_ENUM_ELEMENT(CDQE)   /* Convert Double Word to Quad Word */
_ENUM_ELEMENT(CWD)    /* Convert Word to Double Word */
_ENUM_ELEMENT(CDQ)    /* Convert Double Word to Quad Word */
_ENUM_ELEMENT(CQO)    /* Convert Double Word to Quad Word */
_ENUM_ELEMENT(WAIT)   /* Wait */
_ENUM_ELEMENT(FWAIT)  /* Wait */
_ENUM_ELEMENT(XADD)   /* Exchange and Add */
_ENUM_ELEMENT(CMPXCHG)/* Compare and Exchange */
_ENUM_ELEMENT(SACL)   /* [Undocumented] Set AL on Carry */
_ENUM_ELEMENT(XLAT)   /* Table Look-Up Translation */
_ENUM_ELEMENT(XLATB)  /* Table Look-Up Translation */
_ENUM_ELEMENT(MOVSX)  /* Move with Sign Extension */
_ENUM_ELEMENT(MOVSXD) /* Move with Sign Extension */
_ENUM_ELEMENT(SHRD)   /* Double-Precision Shift Right */
_ENUM_ELEMENT(SHLD)   /* Double-Precision Shift Left */
_ENUM_ELEMENT(LAR)    /* Load Access Right Byte */
_ENUM_ELEMENT(LSL)    /* Load Segment Limit */
_ENUM_ELEMENT(BSWAP)  /* Byte Swap */
_ENUM_ELEMENT(RSM)    /* Resume From System Management Mode */
_ENUM_ELEMENT(BT)     /* Bit Test */
_ENUM_ELEMENT(BTS)    /* Bit Test and Set */
_ENUM_ELEMENT(BTR)    /* Bit Test and Reset */
_ENUM_ELEMENT(BTC)    /* Bit Test and Complement */
_ENUM_ELEMENT(BSF)    /* Bit Scan Forward */
_ENUM_ELEMENT(BSR)    /* Bit Scan Reverse */
_ENUM_ELEMENT(LZCNT)  /* Count the Number of Leading Zero Bits */
_ENUM_ELEMENT(POPCNT) /* Return the Count of Bits Set to One */
_ENUM_ELEMENT(ARPL)   /* Adjust RPL Field of Segment Selector */
_ENUM_ELEMENT(BOUND)  /* Check Array Index Against Bounds */
_ENUM_ELEMENT(LOADALL)/* [Undocummented] Load All */
_ENUM_ELEMENT(LDS)    /* Load Far Pointer into segment DS */
_ENUM_ELEMENT(LES)    /* Load Far Pointer into segment ES */
_ENUM_ELEMENT(LFS)    /* Load Far Pointer into segment FS */
_ENUM_ELEMENT(LGS)    /* Load Far Pointer into segment GS */
_ENUM_ELEMENT(LSS)    /* Load Far Pointer into segment SS */
_ENUM_ELEMENT(MOVNTI) /* Store Double-Word using Non-Temporal Hint */
/* Undefined Instruction */
_ENUM_ELEMENT(UD0)    /* Undefined Instruction */
_ENUM_ELEMENT(UD1)    /* Undefined Instruction */
_ENUM_ELEMENT(UD2)    /* Undefined Instruction */
/* Prefetch */
_ENUM_ELEMENT(PREFETCHT0)  /* Prefetch Data Into Caches using T0 Hint */
_ENUM_ELEMENT(PREFETCHT1)  /* Prefetch Data Into Caches using T1 Hint */
_ENUM_ELEMENT(PREFETCHT2)  /* Prefetch Data Into Caches using T2 Hint */
_ENUM_ELEMENT(PREFETCHNTA) /* Prefetch Data Into Caches using NTA Hint */
_ENUM_ELEMENT(PREFETCHW)   /* Prefetch Data Into Caches in Anticipation of Write */
/* Port */
_ENUM_ELEMENT(_IN)    /* Input from Port */
_ENUM_ELEMENT(INS)    /* Input from Port to String */
_ENUM_ELEMENT(INSB)   /* Input from Port to String */
_ENUM_ELEMENT(INSW)   /* Input from Port to String */
_ENUM_ELEMENT(INSD)   /* Input from Port to String */
_ENUM_ELEMENT(_OUT)   /* Output to Port */
_ENUM_ELEMENT(OUTS)   /* Output String to Port */
_ENUM_ELEMENT(OUTSB)  /* Output String to Port */
_ENUM_ELEMENT(OUTSW)  /* Output String to Port */
_ENUM_ELEMENT(OUTSD)  /* Output String to Port */
/* System Call */
_ENUM_ELEMENT(SYSCALL)  /* Fast System Call */
_ENUM_ELEMENT(SYSRET)   /* Fast Return from Fast System Call */
_ENUM_ELEMENT(SYSENTER) /* Fast System Call */
_ENUM_ELEMENT(SYSEXIT)  /* Fast Return from Fast System Call */
_ENUM_ELEMENT(CLTS)     /* Clear Task-Switched Flag in CR0 */
_ENUM_ELEMENT(WRMSR)    /* Write to Model-Specific Register */
_ENUM_ELEMENT(RDMSR)    /* Read from Model-Specific Register */
_ENUM_ELEMENT(RDTSC)    /* Read Time-Stamp Counter */
_ENUM_ELEMENT(RDPMC)    /* Read Performance-Monitoring Counters */
/* Loop */
_ENUM_ELEMENT(LOOP)    /* Loop */
_ENUM_ELEMENT(LOOPE)   /* Loop if Equal */
_ENUM_ELEMENT(LOOPZ)   /* Loop if Zero (same as LOOPE) */
_ENUM_ELEMENT(LOOPNE)  /* Loop if not Equal */
_ENUM_ELEMENT(LOOPNZ)  /* Loop if not Zero (same as LOOPNE) */
/* Move String to String */
_ENUM_ELEMENT(MOVS)   /* Move String to String */
_ENUM_ELEMENT(MOVSB)  /* Move String to String */
_ENUM_ELEMENT(MOVSW)  /* Move String to String */
//_ENUM_ELEMENT(MOVSD)  /* Move String to String */
_ENUM_ELEMENT(MOVSQ)  /* Move String to String */
/* Compare String Operands */
_ENUM_ELEMENT(CMPS)   /* Compare String Operands */
_ENUM_ELEMENT(CMPSB)  /* Compare String Operands */
_ENUM_ELEMENT(CMPSW)  /* Compare String Operands */
/*_ENUM_ELEMENT(CMPSD)*/  /* Compare String Operands */
_ENUM_ELEMENT(CMPSQ)  /* Compare String Operands */
/* Store String */
_ENUM_ELEMENT(STOS)   /* Store String */
_ENUM_ELEMENT(STOSB)  /* Store String */
_ENUM_ELEMENT(STOSW)  /* Store String */
_ENUM_ELEMENT(STOSD)  /* Store String */
_ENUM_ELEMENT(STOSQ)  /* Store String */
/* Load String */
_ENUM_ELEMENT(LODS)   /* Load String */
_ENUM_ELEMENT(LODSB)  /* Load String */
_ENUM_ELEMENT(LODSW)  /* Load String */
_ENUM_ELEMENT(LODSD)  /* Load String */
_ENUM_ELEMENT(LODSQ)  /* Load String */
/* Scan String */
_ENUM_ELEMENT(SCAS)   /* Scan String */
_ENUM_ELEMENT(SCASB)  /* Scan String */
_ENUM_ELEMENT(SCASW)  /* Scan String */
_ENUM_ELEMENT(SCASD)  /* Scan String */
_ENUM_ELEMENT(SCASQ)  /* Scan String */
/* Rotate and Shift */
_ENUM_ELEMENT(ROL)    /* Rotate Left */
_ENUM_ELEMENT(ROR)    /* Rotate Right */
_ENUM_ELEMENT(RCL)    /* Rotate Left through Carry */
_ENUM_ELEMENT(RCR)    /* Rotate Right through Carry */
_ENUM_ELEMENT(SHL)    /* Shift Logical Left */
_ENUM_ELEMENT(SHR)    /* Shift Logical Right */
_ENUM_ELEMENT(SAL)    /* Shift Arithmetic Left */
_ENUM_ELEMENT(SAR)    /* Shift Arithmetic Right */
/* Jcc - Jump if Condition Met */
_ENUM_ELEMENT(JO)     /* Jump if Overflow */
_ENUM_ELEMENT(JNO)    /* Jump if Not Overflow */
_ENUM_ELEMENT(JB)     /* Jump if Below */
_ENUM_ELEMENT(JNAE)   /* Jump if not Above or Equal (same as JB) */
_ENUM_ELEMENT(JAE)    /* Jump if Above or Equal */
_ENUM_ELEMENT(JNB)    /* Jump if not Below (same as JAE) */
_ENUM_ELEMENT(JNC)    /* Jump if not Carry (same as JAE) */
_ENUM_ELEMENT(JE)     /* Jump if Equal */
_ENUM_ELEMENT(JZ)     /* Jump if Zero (same as JE) */
_ENUM_ELEMENT(JNE)    /* Jump if Not Equal */
_ENUM_ELEMENT(JNZ)    /* Jump if not Zero (same as JNE) */
_ENUM_ELEMENT(JBE)    /* Jump if Below or Equal */
_ENUM_ELEMENT(JNA)    /* Jump if not Above (same as JBE) */
_ENUM_ELEMENT(JA)     /* Jump if Above */
_ENUM_ELEMENT(JNBE)   /* Jump if not Below or Equal (same as JA) */
_ENUM_ELEMENT(JS)     /* Jump if Sign */
_ENUM_ELEMENT(JNS)    /* Jump if not Sign */
_ENUM_ELEMENT(JP)     /* Jump if Parity */
_ENUM_ELEMENT(JPE)    /* Jump if Parity Even (same as JP) */
_ENUM_ELEMENT(JNP)    /* Jump if not Parity */
_ENUM_ELEMENT(JPO)    /* Jump if Parity Odd (same as JNP) */
_ENUM_ELEMENT(JL)     /* Jump if Less */
_ENUM_ELEMENT(JNGE)   /* Jump if not Greater or Equal (same as JL) */
_ENUM_ELEMENT(JNL)    /* Jump if not Less */
_ENUM_ELEMENT(JGE)    /* Jump if Greater or Equal (same as JNL) */
_ENUM_ELEMENT(JLE)    /* Jump if Less or Equal */
_ENUM_ELEMENT(JNG)    /* Jump if not Greater (same as JLE) */
_ENUM_ELEMENT(JNLE)   /* Jump if not Less or Equal */
_ENUM_ELEMENT(JG)     /* Jump if Greater (same as JNLE) */
_ENUM_ELEMENT(JCXZ)   /* Jump if CX is 0 */
_ENUM_ELEMENT(JECXZ)  /* Jump if ECX is 0 */
_ENUM_ELEMENT(JRCXZ)  /* Jump if RCX is 0 */
/* SETcc - Set Byte On Condition */
_ENUM_ELEMENT(SETO)     /* Set if Overflow */
_ENUM_ELEMENT(SETNO)    /* Set if Not Overflow */
_ENUM_ELEMENT(SETB)     /* Set if Below */
_ENUM_ELEMENT(SETNAE)   /* Set if not Above or Equal (same as SETB) */
_ENUM_ELEMENT(SETAE)    /* Set if Above or Equal */
_ENUM_ELEMENT(SETNB)    /* Set if not Below (same as SETAE) */
_ENUM_ELEMENT(SETNC)    /* Set if not Carry (same as SETAE) */
_ENUM_ELEMENT(SETE)     /* Set if Equal */
_ENUM_ELEMENT(SETZ)     /* Set if Zero (same as SETE) */
_ENUM_ELEMENT(SETNE)    /* Set if Not Equal */
_ENUM_ELEMENT(SETNZ)    /* Set if not Zero (same as SETNE) */
_ENUM_ELEMENT(SETBE)    /* Set if Below or Equal */
_ENUM_ELEMENT(SETNA)    /* Set if not Above (same as SETBE) */
_ENUM_ELEMENT(SETA)     /* Set if Above */
_ENUM_ELEMENT(SETNBE)   /* Set if not Below or Equal (same as SETA) */
_ENUM_ELEMENT(SETS)     /* Set if Sign */
_ENUM_ELEMENT(SETNS)    /* Set if not Sign */
_ENUM_ELEMENT(SETP)     /* Set if Parity */
_ENUM_ELEMENT(SETPE)    /* Set if Parity Even (same as SETP) */
_ENUM_ELEMENT(SETNP)    /* Set if not Parity */
_ENUM_ELEMENT(SETPO)    /* Set if Parity Odd (same as SETNP) */
_ENUM_ELEMENT(SETL)     /* Set if Less */
_ENUM_ELEMENT(SETNGE)   /* Set if not Greater or Equal (same as SETL) */
_ENUM_ELEMENT(SETNL)    /* Set if not Less */
_ENUM_ELEMENT(SETGE)    /* Set if Greater or Equal (same as SETNL) */
_ENUM_ELEMENT(SETLE)    /* Set if Less or Equal */
_ENUM_ELEMENT(SETNG)    /* Set if not Greater (same as SETLE) */
_ENUM_ELEMENT(SETNLE)   /* Set if not Less or Equal */
_ENUM_ELEMENT(SETG)     /* Set if Greater (same as SETNLE) */
_ENUM_ELEMENT(INVD)     /* Invalidate Internal Caches */
_ENUM_ELEMENT(WBINVD)   /* Write Back and Invalidate Caches */
/* CMOVcc - Conditional Move */
_ENUM_ELEMENT(CMOVO)     /* Conditional Move if Overflow */
_ENUM_ELEMENT(CMOVNO)    /* Conditional Move if Not Overflow */
_ENUM_ELEMENT(CMOVB)     /* Conditional Move if Below */
_ENUM_ELEMENT(CMOVNAE)   /* Conditional Move if not Above or Equal (same as CMOVB) */
_ENUM_ELEMENT(CMOVAE)    /* Conditional Move if Above or Equal */
_ENUM_ELEMENT(CMOVNB)    /* Conditional Move if not Below (same as CMOVAE) */
_ENUM_ELEMENT(CMOVNC)    /* Conditional Move if not Carry (same as CMOVAE) */
_ENUM_ELEMENT(CMOVE)     /* Conditional Move if Equal */
_ENUM_ELEMENT(CMOVZ)     /* Conditional Move if Zero (same as CMOVE) */
_ENUM_ELEMENT(CMOVNE)    /* Conditional Move if Not Equal */
_ENUM_ELEMENT(CMOVNZ)    /* Conditional Move if not Zero (same as CMOVNE) */
_ENUM_ELEMENT(CMOVBE)    /* Conditional Move if Below or Equal */
_ENUM_ELEMENT(CMOVNA)    /* Conditional Move if not Above (same as CMOVBE) */
_ENUM_ELEMENT(CMOVA)     /* Conditional Move if Above */
_ENUM_ELEMENT(CMOVNBE)   /* Conditional Move if not Below or Equal (same as CMOVA) */
_ENUM_ELEMENT(CMOVS)     /* Conditional Move if Sign */
_ENUM_ELEMENT(CMOVNS)    /* Conditional Move if not Sign */
_ENUM_ELEMENT(CMOVP)     /* Conditional Move if Parity */
_ENUM_ELEMENT(CMOVPE)    /* Conditional Move if Parity Even (same as CMOVP) */
_ENUM_ELEMENT(CMOVNP)    /* Conditional Move if not Parity */
_ENUM_ELEMENT(CMOVPO)    /* Conditional Move if Parity Odd (same as CMOVNP) */
_ENUM_ELEMENT(CMOVL)     /* Conditional Move if Less */
_ENUM_ELEMENT(CMOVNGE)   /* Conditional Move if not Greater or Equal (same as CMOVL) */
_ENUM_ELEMENT(CMOVNL)    /* Conditional Move if not Less */
_ENUM_ELEMENT(CMOVGE)    /* Conditional Move if Greater or Equal (same as CMOVNL) */
_ENUM_ELEMENT(CMOVLE)    /* Conditional Move if Less or Equal */
_ENUM_ELEMENT(CMOVNG)    /* Conditional Move if not Greater (same as CMOVLE) */
_ENUM_ELEMENT(CMOVNLE)   /* Conditional Move if not Less or Equal */
_ENUM_ELEMENT(CMOVG)     /* Conditional Move if Greater (same as SETNLE) */
/* OpCode Extensions */
_ENUM_ELEMENT(GROUP1)
_ENUM_ELEMENT(GROUP1A)
_ENUM_ELEMENT(GROUP2)
_ENUM_ELEMENT(GROUP3_F6)
_ENUM_ELEMENT(GROUP3_F7)
_ENUM_ELEMENT(GROUP4)
_ENUM_ELEMENT(GROUP5)
_ENUM_ELEMENT(GROUP6)
_ENUM_ELEMENT(GROUP7)
_ENUM_ELEMENT(GROUP7_EXT2)
_ENUM_ELEMENT(GROUP8)
_ENUM_ELEMENT(GROUP9)
_ENUM_ELEMENT(GROUP10)
_ENUM_ELEMENT(GROUP11)
_ENUM_ELEMENT(GROUP12)
_ENUM_ELEMENT(GROUP12_66)
_ENUM_ELEMENT(GROUP13)
_ENUM_ELEMENT(GROUP13_66)
_ENUM_ELEMENT(GROUP14)
_ENUM_ELEMENT(GROUP14_66)
_ENUM_ELEMENT(GROUP15)
_ENUM_ELEMENT(GROUP16)
_ENUM_ELEMENT(GROUP17)
_ENUM_ELEMENT(GROUP12VEX)
_ENUM_ELEMENT(GROUP13VEX)
_ENUM_ELEMENT(GROUP14VEX)
_ENUM_ELEMENT(GROUP15VEX)
_ENUM_ELEMENT(GROUP16VEX)
_ENUM_ELEMENT(GROUP17VEX)
_ENUM_ELEMENT(GROUPP)
/* x87 FPU */
_ENUM_ELEMENT(FADD)     /* Add */
_ENUM_ELEMENT(FADDP)    /* Add */
_ENUM_ELEMENT(FIADD)    /* Add */
_ENUM_ELEMENT(FMUL)     /* Multiply */
_ENUM_ELEMENT(FMULP)    /* Multiply */
_ENUM_ELEMENT(FIMUL)    /* Multiply */
_ENUM_ELEMENT(FCOM)     /* Compare Floating Point Values */
_ENUM_ELEMENT(FCOM2)    /* Compare Floating Point Values */
_ENUM_ELEMENT(FICOM)    /* Compare Floating Point Values */
_ENUM_ELEMENT(FCOMP)    /* Compare Floating Point Values and Pop */
_ENUM_ELEMENT(FCOMP3)   /* Compare Floating Point Values and Pop */
_ENUM_ELEMENT(FCOMP5)   /* Compare Floating Point Values and Pop */
_ENUM_ELEMENT(FCOMPP)   /* Compare Floating Point Values and Pop Twice */
_ENUM_ELEMENT(FICOMP)   /* Compare Floating Point Values */
_ENUM_ELEMENT(FCOMI)    /* Compare Floating Point Values and Set EFLAGS */
_ENUM_ELEMENT(FCOMIP)   /* Compare Floating Point Values and Set EFLAGS */
_ENUM_ELEMENT(FUCOM)    /* Unordered Compare Floating Point Values */
_ENUM_ELEMENT(FUCOMP)   /* Unordered Compare Floating Point Values */
_ENUM_ELEMENT(FUCOMI)   /* Unordered Compare Floating Point Values */
_ENUM_ELEMENT(FUCOMPP)  /* Unordered Compare Floating Point Values */
_ENUM_ELEMENT(FUCOMIP)  /* Unordered Compare and Set EFLAGS */
_ENUM_ELEMENT(FSUB)     /* Subtract */
_ENUM_ELEMENT(FSUBP)    /* Subtract */
_ENUM_ELEMENT(FISUB)    /* Subtract */
_ENUM_ELEMENT(FSUBR)    /* Reverse Subtract */
_ENUM_ELEMENT(FSUBRP)   /* Reverse Subtract */
_ENUM_ELEMENT(FISUBR)   /* Reverse Subtract */
_ENUM_ELEMENT(FDIV)     /* Divide */
_ENUM_ELEMENT(FDIVP)    /* Divide */
_ENUM_ELEMENT(FIDIV)    /* Divide */
_ENUM_ELEMENT(FDIVR)    /* Reverse Divide */
_ENUM_ELEMENT(FDIVRP)   /* Reverse Divide */
_ENUM_ELEMENT(FIDIVR)   /* Reverse Divide */
_ENUM_ELEMENT(FLD)      /* Load Floating Point Value */
_ENUM_ELEMENT(FLDENV)   /* Load x87 FPU Environment */
_ENUM_ELEMENT(FLDCW)    /* Load x87 FPU Control Word */
_ENUM_ELEMENT(FILD)     /* Load Integer */
_ENUM_ELEMENT(FST)      /* Store Floating Point Value */
_ENUM_ELEMENT(FSTP)     /* Store Floating Point Value and Pop */
_ENUM_ELEMENT(FSTP1)    /* Store Floating Point Value and Pop */
_ENUM_ELEMENT(FSTP8)    /* Store Floating Point Value and Pop */
_ENUM_ELEMENT(FSTP9)    /* Store Floating Point Value and Pop */
_ENUM_ELEMENT(FSTENV)   /* Store x87 FPU Environment */
_ENUM_ELEMENT(FSTCW)    /* Store x87 FPU Control Word */
_ENUM_ELEMENT(FSTSW)    /* Store x87 FPU Status Word */
_ENUM_ELEMENT(FNSTSW)   /* Store x87 FPU Status Word */
_ENUM_ELEMENT(FISTTP)   /* Store Integer with Truncation */
_ENUM_ELEMENT(FIST)     /* Store Integer */
_ENUM_ELEMENT(FISTP)    /* Store Integer */
_ENUM_ELEMENT(FCMOVB)   /* Move if Below */
_ENUM_ELEMENT(FCMOVE)   /* Move if Equal */
_ENUM_ELEMENT(FCMOVBE)  /* Move if Below or Equal */
_ENUM_ELEMENT(FCMOVU)   /* Move if Unordered */
_ENUM_ELEMENT(FCMOVNB)  /* Move if Not Below */
_ENUM_ELEMENT(FCMOVNE)  /* Move if Not Equal */
_ENUM_ELEMENT(FCMOVNBE) /* Move if Not Below or Equal */
_ENUM_ELEMENT(FCMOVNU)  /* Move if Not Unordered */
_ENUM_ELEMENT(FXCH)     /* Exchange Register Contents */
_ENUM_ELEMENT(FXCH4)    /* Exchange Register Contents */
_ENUM_ELEMENT(FXCH7)    /* Exchange Register Contents */
_ENUM_ELEMENT(FLD1)     /* Load Constant (1.0) */
_ENUM_ELEMENT(FLDL2T)   /* Load Constant (log2 10) */
_ENUM_ELEMENT(FLDL2E)   /* Load Constant (log2 e) */
_ENUM_ELEMENT(FLDPI)    /* Load Constant (PI) */
_ENUM_ELEMENT(FLDLG2)   /* Load Constant (log10 2) */
_ENUM_ELEMENT(FLDLN2)   /* Load Constant (ln 2) */
_ENUM_ELEMENT(FLDZ)     /* Load Constant (0.0) */
_ENUM_ELEMENT(FNOP)     /* No Operation */
_ENUM_ELEMENT(FFREE)    /* Free Floating Point Register */
_ENUM_ELEMENT(FFREEP)   /* Free Floating Point Register and Pop Stack */
_ENUM_ELEMENT(FNCLEX)   /* Clear Exceptions */
_ENUM_ELEMENT(FNINIT)   /* Initialize Floating-Point Unit */
_ENUM_ELEMENT(FCHS)     /* Change Sign */
_ENUM_ELEMENT(FABS)     /* Absolute Value */
_ENUM_ELEMENT(FTST)     /* Test */
_ENUM_ELEMENT(FXAM)     /* Examine ModR/M */
_ENUM_ELEMENT(F2XM1)    /* Compute 2^X - 1 */
_ENUM_ELEMENT(FYL2X)    /* Compute Y * log2 X */
_ENUM_ELEMENT(FPTAN)    /* Partial Tangent */
_ENUM_ELEMENT(FPATAN)   /* Partial Arctangent */
_ENUM_ELEMENT(FXTRACT)  /* Extract Exponent and Significant */
_ENUM_ELEMENT(FPREM)    /* Partial Remainder */
_ENUM_ELEMENT(FPREM1)   /* Partial Remainder */
_ENUM_ELEMENT(FDECSTP)  /* Decrement Stack-Top Pointer */
_ENUM_ELEMENT(FINCSTP)  /* Increment Stack-Top Pointer */
_ENUM_ELEMENT(FYL2XP1)  /* Compute Y * log2 (X + 1) */
_ENUM_ELEMENT(FSQRT)    /* Square Root */
_ENUM_ELEMENT(FSINCOS)  /* Sine and Cosine */
_ENUM_ELEMENT(FSIN)     /* Sine */
_ENUM_ELEMENT(FCOS)     /* Cosine */
_ENUM_ELEMENT(FRNDINT)  /* Round to Integer */
_ENUM_ELEMENT(FSCALE)   /* Scale */
_ENUM_ELEMENT(FBLD)     /* Load Binary Coded Decimal */
_ENUM_ELEMENT(FBSTP)    /* Store Binary Coded Decimal and Pop */
_ENUM_ELEMENT(FRSTOR)   /* Restore x87 FPU State */
_ENUM_ELEMENT(FNSAVE)   /* Store x87 FPU State */
/* MMX */
_ENUM_ELEMENT(EMMS)     /* Empty MMX Technology State */
_ENUM_ELEMENT(PSUBUSB)  /* Subtract Packed Unsigned Integer with Unsigned Saturation */
_ENUM_ELEMENT(PSUBUSW)  /* Subtract Packed Unsigned Integer with Unsigned Saturation */
_ENUM_ELEMENT(PSUBSB)   /* Subtract Packed Unsigned Integer with Signed Saturation */
_ENUM_ELEMENT(PSUBSW)   /* Subtract Packed Unsigned Integer with Signed Saturation */
_ENUM_ELEMENT(PSUBB)    /* Subtract Packed Integer */
_ENUM_ELEMENT(PSUBW)    /* Subtract Packed Integer */
_ENUM_ELEMENT(PSUBD)    /* Subtract Packed Integer */
_ENUM_ELEMENT(PSUBQ)    /* Subtract Packed Integer */
_ENUM_ELEMENT(PADDUSB)  /* Add Packed Unsigned Integer with Unsigned Saturation */
_ENUM_ELEMENT(PADDUSW)  /* Add Packed Unsigned Integer with Unsigned Saturation */
_ENUM_ELEMENT(PADDSB)   /* Add Packed Unsigned Integer with Signed Saturation */
_ENUM_ELEMENT(PADDSW)   /* Add Packed Unsigned Integer with Signed Saturation */
_ENUM_ELEMENT(PADDB)    /* Add Packed Integer */
_ENUM_ELEMENT(PADDW)    /* Add Packed Integer */
_ENUM_ELEMENT(PADDD)    /* Add Packed Integer */
_ENUM_ELEMENT(PMINUB)   /* Minimum Packed Integer */
_ENUM_ELEMENT(PMINSW)   /* Minimum Packed Integer */
_ENUM_ELEMENT(PMAXUB)   /* Maximum Packed Integer */
_ENUM_ELEMENT(PMAXSW)   /* Maximum Packed Integer */
_ENUM_ELEMENT(PAND)     /* Bitwise Logical AND */
_ENUM_ELEMENT(PANDN)    /* Bitwise Logical AND-NOT */
_ENUM_ELEMENT(POR)      /* Bitwise Logical OR */
_ENUM_ELEMENT(PXOR)     /* Bitwise Logical XOR */
_ENUM_ELEMENT(PSLLW)    /* Shift Packed Data Left Logical */
_ENUM_ELEMENT(PSLLD)    /* Shift Packed Data Left Logical */
_ENUM_ELEMENT(PSLLQ)    /* Shift Packed Data Left Logical */
_ENUM_ELEMENT(PSLLDQ)   /* Shift Packed Data Left Logical */
_ENUM_ELEMENT(PSRLW)    /* Shift Packed Data Right Logical */
_ENUM_ELEMENT(PSRLD)    /* Shift Packed Data Right Logical */
_ENUM_ELEMENT(PSRLQ)    /* Shift Packed Data Right Logical */
_ENUM_ELEMENT(PSRLDQ)   /* Shift Packed Data Right Logical */
_ENUM_ELEMENT(PSRAW)    /* Shift Packed Data Right Arithmetic */
_ENUM_ELEMENT(PSRAD)    /* Shift Packed Data Right Arithmetic */
_ENUM_ELEMENT(PMULLW)   /* Multiply Packed Signed Integers and Store Low Result */
_ENUM_ELEMENT(PADDQ)    /* Add Packed Quad-Word Integers */
_ENUM_ELEMENT(PAVGB)    /* Average Packed Integers */
_ENUM_ELEMENT(PAVGW)    /* Average Packed Integers */
_ENUM_ELEMENT(PMULHW)   /* Multiply Packed Signed Integers and Store High Result */
_ENUM_ELEMENT(PMULHUW)  /* Multiply Packed Unsigned Integers and Store High Result */
_ENUM_ELEMENT(PMULUDQ)  /* Multiply Packed Unsigned Integers */
_ENUM_ELEMENT(PSADDBW)  /* Compute Sum of Absolute Differences */
_ENUM_ELEMENT(PMADDWD)  /* Multiply and Add Packed Integers */
_ENUM_ELEMENT(PSHUFW)   /* Shuffle Packed Words */
_ENUM_ELEMENT(PSHUFD)   /* Shuffle Packed Double-Words */
_ENUM_ELEMENT(PSHUFHW)  /* Shuffle Packed High Words */ 
_ENUM_ELEMENT(PSHUFLW)  /* Shuffle Packed Low Words */
_ENUM_ELEMENT(PUNPCKLBW)/* Unpack and Interleave Low-Order Bytes */
_ENUM_ELEMENT(PUNPCKLWD)/* Unpack and Interleave Low-Order Words */
_ENUM_ELEMENT(PUNPCKLDQ)/* Unpack and Interleave Low-Order Double-Words */
_ENUM_ELEMENT(PUNPCKLQDQ)/* Unpack and Interleave Low-Order Quad-Words */
_ENUM_ELEMENT(PUNPCKHBW)/* Unpack and Interleave High-Order Bytes */
_ENUM_ELEMENT(PUNPCKHWD)/* Unpack and Interleave High-Order Words */
_ENUM_ELEMENT(PUNPCKHDQ)/* Unpack and Interleave High-Order Double-Words */
_ENUM_ELEMENT(PUNPCKHQDQ)/* Unpack and Interleave High-Order Quad-Words */
_ENUM_ELEMENT(PCMPEQB)  /* Compare Packed Bytes */
_ENUM_ELEMENT(PCMPEQW)  /* Compare Packed Words */
_ENUM_ELEMENT(PCMPEQD)  /* Compare Packed Double-Words */
_ENUM_ELEMENT(PCMPGTB)  /* Compare Packed Bytes for Greater Than */
_ENUM_ELEMENT(PCMPGTW)  /* Compare Packed Words for Greater Than */
_ENUM_ELEMENT(PCMPGTD)  /* Compare Packed Double-Words for Greater Than */
_ENUM_ELEMENT(PACKSSWB) /* Pack with Signed Saturation */
_ENUM_ELEMENT(PACKUSWB) /* Pack with Unsigned Saturation */
_ENUM_ELEMENT(PACKSSDW) /* Pack with Signed Saturation */
_ENUM_ELEMENT(MOVQ)     /* Move Quad Word */
_ENUM_ELEMENT(MOVD)     /* Move Double Word */
_ENUM_ELEMENT(MOVDQA)   /* Move Aligned Double-Quadword */
_ENUM_ELEMENT(MOVDQU)   /* Move Unaligned Double-Quadword */
_ENUM_ELEMENT(MASKMOVQ) /* Store Selected Bytes of Quad-Word */
/* 3DNow! */
_ENUM_ELEMENT(FEMMS)
/* SSE */
_ENUM_ELEMENT(MOVUPS)   /* Move Unaligned Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(MOVAPS)   /* Move Aligned Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(MOVSS)    /* Move Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(MOVLPS)   /* Move Low Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(MOVHPS)   /* Move High Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(MOVNTPS)  /* Store Packed Single-Precision Floating Point Values Using Non-Temporal Hint */
_ENUM_ELEMENT(MOVMSKPS) /* Extract Packed Single-Precision Floating Point Sing-Mask */
_ENUM_ELEMENT(SQRTPS)   /* Square Root of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(SQRTSS)   /* Square Root of Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(RSQRTPS)  /* Reciprocal of Square Root of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(RSQRTSS)  /* Reciprocal of Square Root of Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(RCPPS)    /* Reciprocal of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(RCPSS)    /* Reciprocal of Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(ANDPS)    /* Bitwise Logical AND of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(ANDNPS)   /* Bitwise Logical AND-NOT of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(ORPS)     /* Bitwise Logical OR of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(XORPS)    /* Bitwise Logical XOR of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(ADDPS)    /* Add Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(ADDSS)    /* Add Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(MULPS)    /* Multiply Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(MULSS)    /* Multiply Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(SUBPS)    /* Subtract Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(SUBSS)    /* Subtract Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(MINPS)    /* Minimum Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(MINSS)    /* Minimum Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(DIVPS)    /* Divide Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(DIVSS)    /* Divide Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(MAXPS)    /* Maximum Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(MAXSS)    /* Maximum Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(COMISS)   /* Compare Scalar Ordered Single-Precision Floating Point Values */
_ENUM_ELEMENT(UCOMISS)  /* Compare Scalar Unordered Single-Precision Floating Point Values */
_ENUM_ELEMENT(CMPPS)    /* Compare Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(CMPSS)    /* Compare Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(SHUFPS)   /* Shuffle Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(UNPCKLPS) /* Unpack and Interleave Low Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(UNPCKHPS) /* Unpack and Interleave High Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(CVTPI2PS) /* Convert Packed Double Word Integers to Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(CVTPS2PI) /* Convert Packed Single-Precision Floating Point Values to Packed Double Word Integers */
_ENUM_ELEMENT(CVTTPS2PI)/* Convert with Truncation Packed Single-Precision Floating Point Values to Packed Double Word Integers */
_ENUM_ELEMENT(CVTSI2SS) /* Convert Scalar Double Word Integers to Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(CVTSS2SI) /* Convert Scalar Single-Precision Floating Point Values to Scalar Double Word Integers */
_ENUM_ELEMENT(CVTTSS2SI)/* Convert with Truncation Scalar Single-Precision Floating Point Values to Scalar Double Word Integers */
_ENUM_ELEMENT(PINSRW)   /* Insert Word */
_ENUM_ELEMENT(PEXTRW)   /* Extract Word */
_ENUM_ELEMENT(PMOVMSKB) /* Move Byte Mask */
_ENUM_ELEMENT(SFENCE)   /* Store Fence */
/* SSE2 */
_ENUM_ELEMENT(MOVUPD)   /* Move Unaligned Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(MOVAPD)   /* Move Aligned Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(MOVSD)    /* Move Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(MOVLPD)   /* Move Low Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(MOVHPD)   /* Move High Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(MOVNTPD)  /* Store Packed Double-Precision Floating Point Values Using Non-Temporal Hint */
_ENUM_ELEMENT(MOVMSKPD) /* Extract Packed Double-Precision Floating Point Sing-Mask */
_ENUM_ELEMENT(SQRTPD)   /* Square Root of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(SQRTSD)   /* Square Root of Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(RSQRTPD)  /* Reciprocal of Square Root of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(RCPPD)    /* Reciprocal of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(ANDPD)    /* Bitwise Logical AND of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(ANDNPD)   /* Bitwise Logical AND-NOT of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(ORPD)     /* Bitwise Logical OR of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(XORPD)    /* Bitwise Logical XOR of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(ADDPD)    /* Add Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(ADDSD)    /* Add Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(MULPD)    /* Multiply Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(MULSD)    /* Multiply Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(SUBPD)    /* Subtract Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(SUBSD)    /* Subtract Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(MINPD)    /* Minimum Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(MINSD)    /* Minimum Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(DIVPD)    /* Divide Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(DIVSD)    /* Divide Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(MAXPD)    /* Maximum Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(MAXSD)    /* Maximum Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(COMISD)   /* Compare Scalar Ordered Double-Precision Floating Point Values */
_ENUM_ELEMENT(UCOMISD)  /* Compare Scalar Unordered Double-Precision Floating Point Values */
_ENUM_ELEMENT(CMPPD)    /* Compare Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(CMPSD)    /* Compare Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(SHUFPD)   /* Shuffle Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(UNPCKLPD) /* Unpack and Interleave Low Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(UNPCKHPD) /* Unpack and Interleave High Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(LDMXCSR)  /* Load MXCSR Register */
_ENUM_ELEMENT(STMXCSR)  /* Store MXCSR Register */
_ENUM_ELEMENT(CVTPS2PD) /* Converter Packed Packed Single-Precision Floating Point Values to Double Precision Floating Point Values */
_ENUM_ELEMENT(CVTPD2PS) /* Converter Packed Packed Double-Precision Floating Point Values to Single Precision Floating Point Values */
_ENUM_ELEMENT(CVTSS2SD) /* Converter Packed Scalar Single-Precision Floating Point Values to Double Precision Floating Point Values */
_ENUM_ELEMENT(CVTSD2SS) /* Converter Packed Scalar Double-Precision Floating Point Values to Single Precision Floating Point Values */
_ENUM_ELEMENT(CVTPI2PD) /* Convert Packed Double Word Integers to Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(CVTPD2PI) /* Convert Packed Single-Precision Floating Point Values to Packed Double Word Integers */
_ENUM_ELEMENT(CVTTPD2PI)/* Convert with Truncation Packed Double-Precision Floating Point Values to Packed Double Word Integers */
_ENUM_ELEMENT(CVTSI2SD) /* Convert Scalar Double Word Integers to Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(CVTSD2SI) /* Convert Scalar Double-Precision Floating Point Values to Scalar Double Word Integers */
_ENUM_ELEMENT(CVTTSD2SI)/* Convert with Truncation Scalar Double-Precision Floating Point Values to Scalar Double Word Integers */
_ENUM_ELEMENT(CVTDQ2PD) /* Convert Packed Double-Precision Floating Point Values to Packed Double Word Integers */
_ENUM_ELEMENT(CVTPD2DQ) /* Convert Packed Double-Precision Floating Point Values to Packed Double Word Integers */
_ENUM_ELEMENT(CVTTPD2DQ)/* Convert with Truncation Packed Double-Precision Floating Point Values to Packed Double Word Integers */
_ENUM_ELEMENT(CVTDQ2PS) /* Convert Packed Double-Word Integer Values to Single-Precision Floating Point Values */
_ENUM_ELEMENT(CVTPS2DQ) /* Convert Single-Precision Floating Point Values to Packed Double-Word Integer Values */
_ENUM_ELEMENT(CVTTPS2DQ)/* Convert with Truncation Single-Precision Floating Point Values to Packed Double-Word Integer Values */
_ENUM_ELEMENT(MOVQ2DQ)  /* Move Quad-Word from XMM to MMX Register */
_ENUM_ELEMENT(MOVDQ2Q)  /* Move Quad-Word from MMX to XMM Register */
_ENUM_ELEMENT(MOVNTQ)   /* Store of Quad-Word using Non-Temporal Hint */
_ENUM_ELEMENT(MOVNTDQ)  /* Store of Double Quad-Word using Non-Temporal Hint */
_ENUM_ELEMENT(MFENCE)   /* Memory Fence */
_ENUM_ELEMENT(LFENCE)   /* Load Fence */
_ENUM_ELEMENT(MASKMOVDQU) /* Store Selected Bytes of Double-Quad-Word */
/* SSE3 */
_ENUM_ELEMENT(MOVSLDUP) /* Move Packed Single-Precision Floating Point Values Low and Duplicate */
_ENUM_ELEMENT(MOVSHDUP) /* Move Packed Single-Precision Floating Point Values High and Duplicate */
_ENUM_ELEMENT(MOVDDUP)  /* Move One Double-Precision Floating Point Value and Duplicate */
_ENUM_ELEMENT(ADDSUBPS) /* Packed Single-Precision Floating Point Values Add/Subtract */
_ENUM_ELEMENT(ADDSUBPD) /* Packed Double-Precision Floating Point Values Add/Subtract */
_ENUM_ELEMENT(HADDPS)   /* Horizontal Add Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(HADDPD)   /* Horizontal Add Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(HSUBPS)   /* Horizontal Subtract Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(HSUBPD)   /* Horizontal Subtract Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(LDDQU)    /* Load Unaligned Integer 128 bits */
/* SSSE3 */
_ENUM_ELEMENT(PSHUFB)    /* Packed Shuffle Bytes */
_ENUM_ELEMENT(PALIGNR)   /* Packed Align Right */
_ENUM_ELEMENT(PHADDW)    /* Packed Horizontal Add */
_ENUM_ELEMENT(PHADDD)    /* Packed Horizontal Add */
_ENUM_ELEMENT(PHADDSW)   /* Packed Horizontal Add and Saturate */
_ENUM_ELEMENT(PHSUBW)    /* Packed Horizontal Subtract */
_ENUM_ELEMENT(PHSUBD)    /* Packed Horizontal Subtract */
_ENUM_ELEMENT(PHSUBSW)   /* Packed Horizontal Subtract and Saturate */
_ENUM_ELEMENT(PABSB)     /* Packed Absolute Value */
_ENUM_ELEMENT(PABSW)     /* Packed Absolute Value */
_ENUM_ELEMENT(PABSD)     /* Packed Absolute Value */
_ENUM_ELEMENT(PMULHRSW)  /* Packed Multiply High with Round and Scale */
_ENUM_ELEMENT(PMADDUBSW) /* Multiply and Add Packed Signed and Unsigned Bytes */
_ENUM_ELEMENT(PSIGNB)    /* Packed Sign */
_ENUM_ELEMENT(PSIGNW)    /* Packed Sign */
_ENUM_ELEMENT(PSIGND)    /* Packed Sign */
/* SSE4.1 */
_ENUM_ELEMENT(PMOVSXBW) /* Sign Extend Packed Signed  8-bit Integers to Packed Signed 16-bit Integers */
_ENUM_ELEMENT(PMOVSXBD) /* Sign Extend Packed Signed  8-bit Integers to Packed Signed 32-bit Integers */
_ENUM_ELEMENT(PMOVSXBQ) /* Sign Extend Packed Signed  8-bit Integers to Packed Signed 64-bit Integers */
_ENUM_ELEMENT(PMOVSXWD) /* Sign Extend Packed Signed 16-bit Integers to Packed Signed 32-bit Integers */
_ENUM_ELEMENT(PMOVSXWQ) /* Sign Extend Packed Signed 16-bit Integers to Packed Signed 64-bit Integers */
_ENUM_ELEMENT(PMOVSXDQ) /* Sign Extend Packed Signed 32-bit Integers to Packed Signed 64-bit Integers */
_ENUM_ELEMENT(PMOVZXBW) /* Zero Extend Packed  8-bit Integers to Packed 16-bit Integers */
_ENUM_ELEMENT(PMOVZXBD) /* Zero Extend Packed  8-bit Integers to Packed 32-bit Integers */
_ENUM_ELEMENT(PMOVZXBQ) /* Zero Extend Packed  8-bit Integers to Packed 64-bit Integers */
_ENUM_ELEMENT(PMOVZXWD) /* Zero Extend Packed 16-bit Integers to Packed 32-bit Integers */
_ENUM_ELEMENT(PMOVZXWQ) /* Zero Extend Packed 16-bit Integers to Packed 64-bit Integers */
_ENUM_ELEMENT(PMOVZXDQ) /* Zero Extend Packed 32-bit Integers to Packed 64-bit Integers */
_ENUM_ELEMENT(BLENDPS)  /* Blend Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(BLENDPD)  /* Blend Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(PBLENDW)  /* Blend Packed Words */
_ENUM_ELEMENT(ROUNDPS)  /* Round Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(ROUNDPD)  /* Round Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(ROUNDSS)  /* Round Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(ROUNDSD)  /* Round Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(PINSRB)   /* Insert Byte */
_ENUM_ELEMENT(PINSRD)   /* Insert Double-Word */
_ENUM_ELEMENT(INSERTPS) /* Insert Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(PACKUSDW) /* Pack with Unsigned Saturation */
_ENUM_ELEMENT(MOVNTDQA) /* Load Double-Word Non-Temporal Aligned Hint */
_ENUM_ELEMENT(PMINSB)   /* Minimum of Packed Signed Byte Integers */
_ENUM_ELEMENT(PMINSD)   /* Minimum of Packed Signed Double-Word Integers */
_ENUM_ELEMENT(PMINUW)   /* Minimum of Packed Word Integers */
_ENUM_ELEMENT(PMINUD)   /* Minimum of Packed Double Word Integers */
_ENUM_ELEMENT(PMAXSB)   /* Maximum of Packed Signed Byte Integers */
_ENUM_ELEMENT(PMAXSD)   /* Maximum of Packed Signed Double-Word Integers */
_ENUM_ELEMENT(PMAXUW)   /* Maximum of Packed Word Integers */
_ENUM_ELEMENT(PMAXUD)   /* Maximum of Packed Double Word Integers */
_ENUM_ELEMENT(PEXTRB)   /* Extract Byte */
_ENUM_ELEMENT(PEXTRD)   /* Extract Double-Word */
_ENUM_ELEMENT(BLENDVPS) /* Variable Blend Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(BLENDVPD) /* Variable Blend Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(PBLENVB)  /* Variable Blend Packed Bytes */
_ENUM_ELEMENT(PTEST)    /* Logical Compare */
_ENUM_ELEMENT(PHMINPOSUW) /* Packed Horizontal Word Minimum */
_ENUM_ELEMENT(DPPS)     /* Dot Product of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(DPPD)     /* Dot Product of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(MPSADBW)  /* Compute Multiple Packed Sums of Absolute Differences */
_ENUM_ELEMENT(PMULLD)   /* Multiply Packed Signed Double-Word Integers and Store Low Result */
/* SSE4.2 */
_ENUM_ELEMENT(PCMPESTRM)/* Packed Compare Explicit Length Strings and Return Mask */
_ENUM_ELEMENT(PCMPESTRI)/* Packed Compare Explicit Length Strings and Return Index */
_ENUM_ELEMENT(PCMPISTRM)/* Packed Compare Implicit Length Strings and Return Mask */
_ENUM_ELEMENT(PCMPISTRI)/* Packed Compare Implicit Length Strings and Return Index */
/* SSE4A */
_ENUM_ELEMENT(MOVNTSS)  /* Store Scalar Single-Precision Floating Point Values Using Non-Temporal Hint */
_ENUM_ELEMENT(MOVNTSD)  /* Store Scalar Single-Precision Floating Point Values Using Non-Temporal Hint */
_ENUM_ELEMENT(EXTRQ)    /* Extract Field From Register */
_ENUM_ELEMENT(INSERTQ)  /* Insert Field */
/* AVX */
_ENUM_ELEMENT(VZEROUPPER) /* Zero Upper Bits of YMM Registers */
_ENUM_ELEMENT(VBROADCASTSS)/* Broadcast Floating-Point Data */
_ENUM_ELEMENT(VBROADCASTSD)/* Broadcast Floating-Point Data */
_ENUM_ELEMENT(VMOVUPS)    /* Move Unaligned Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVAPS)    /* Move Aligned Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVUPD)    /* Move Unaligned Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVAPD)    /* Move Aligned Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVSS)     /* Move Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVSD)     /* Move Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVD)      /* Move Double Word */
_ENUM_ELEMENT(VMOVQ)      /* Move Quad Word */
_ENUM_ELEMENT(VMOVDQA)    /* Move Aligned Double-Quadword */
_ENUM_ELEMENT(VMOVDQU)    /* Move Unaligned Double-Quadword */
_ENUM_ELEMENT(VSHUFPS)    /* Shuffle Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VSHUFPD)    /* Shuffle Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VANDPS)     /* Bitwise Logical AND of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VANDNPS)    /* Bitwise Logical AND-NOT of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VORPS)      /* Bitwise Logical OR of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VXORPS)     /* Bitwise Logical XOR of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VANDPD)     /* Bitwise Logical AND of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VANDNPD)    /* Bitwise Logical AND-NOT of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VORPD)      /* Bitwise Logical OR of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VXORPD)     /* Bitwise Logical XOR of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VADDPS)     /* Add Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VADDSS)     /* Add Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMULPS)     /* Multiply Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMULSS)     /* Multiply Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VSUBPS)     /* Subtract Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VSUBSS)     /* Subtract Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMINPS)     /* Minimum Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMINSS)     /* Minimum Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VDIVPS)     /* Divide Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VDIVSS)     /* Divide Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMAXPS)     /* Maximum Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMAXSS)     /* Maximum Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VADDPD)     /* Add Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VADDSD)     /* Add Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMULPD)     /* Multiply Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMULSD)     /* Multiply Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VSUBPD)     /* Subtract Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VSUBSD)     /* Subtract Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMINPD)     /* Minimum Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMINSD)     /* Minimum Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VDIVPD)     /* Divide Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VDIVSD)     /* Divide Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMAXPD)     /* Maximum Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMAXSD)     /* Maximum Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VCMPPS)     /* Compare Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VCMPSS)     /* Compare Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VCMPPD)     /* Compare Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VCMPSD)     /* Compare Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VSQRTPS)    /* Square Root of Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VSQRTSS)    /* Square Root of Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VSQRTPD)    /* Square Root of Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VSQRTSD)    /* Square Root of Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VPAND)      /* Bitwise Logical AND */
_ENUM_ELEMENT(VPANDN)     /* Bitwise Logical AND-NOT */
_ENUM_ELEMENT(VPOR)       /* Bitwise Logical OR */
_ENUM_ELEMENT(VPXOR)      /* Bitwise Logical XOR */
_ENUM_ELEMENT(VPERM2F128) /* Permute Floating Point Values */
_ENUM_ELEMENT(VINSERTF128)/* Insert Packed Floating-Point Values */
_ENUM_ELEMENT(VEXTRACTF128)/* Extract Packed Floating-Point Values */
_ENUM_ELEMENT(VBLENDPS)   /* Blend Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VBLENDPD)   /* Blend Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VCVTSI2SS)  /* Convert Scalar Double Word Integers to Scalar Single-Precision Floating Point Values */
_ENUM_ELEMENT(VCVTSI2SD)  /* Convert Scalar Double Word Integers to Scalar Double-Precision Floating Point Values */
_ENUM_ELEMENT(VCOMISS)    /* Compare Scalar Ordered Single-Precision Floating Point Values */
_ENUM_ELEMENT(VUCOMISS)   /* Compare Scalar Unordered Single-Precision Floating Point Values */
_ENUM_ELEMENT(VCOMISD)    /* Compare Scalar Ordered Double-Precision Floating Point Values */
_ENUM_ELEMENT(VUCOMISD)   /* Compare Scalar Unordered Double-Precision Floating Point Values */
_ENUM_ELEMENT(VCVTPS2PD)  /* Converter Packed Packed Single-Precision Floating Point Values to Double Precision Floating Point Values */
_ENUM_ELEMENT(VCVTPD2PS)  /* Converter Packed Packed Double-Precision Floating Point Values to Single Precision Floating Point Values */
_ENUM_ELEMENT(VCVTSS2SD)  /* Converter Packed Scalar Single-Precision Floating Point Values to Double Precision Floating Point Values */
_ENUM_ELEMENT(VCVTSD2SS)  /* Converter Packed Scalar Double-Precision Floating Point Values to Single Precision Floating Point Values */
_ENUM_ELEMENT(VUNPCKLPS)  /* Unpack and Interleave Low Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VUNPCKHPS)  /* Unpack and Interleave High Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VUNPCKLPD)  /* Unpack and Interleave Low Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VUNPCKHPD)  /* Unpack and Interleave High Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VPUNPCKLBW) /* Unpack and Interleave Low-Order Bytes */
_ENUM_ELEMENT(VPUNPCKLWD) /* Unpack and Interleave Low-Order Words */
_ENUM_ELEMENT(VPUNPCKLDQ) /* Unpack and Interleave Low-Order Double-Words */
_ENUM_ELEMENT(VPUNPCKLQDQ)/* Unpack and Interleave Low-Order Quad-Words */
_ENUM_ELEMENT(VPUNPCKHBW) /* Unpack and Interleave High-Order Bytes */
_ENUM_ELEMENT(VPUNPCKHWD) /* Unpack and Interleave High-Order Words */
_ENUM_ELEMENT(VPUNPCKHDQ) /* Unpack and Interleave High-Order Double-Words */
_ENUM_ELEMENT(VPUNPCKHQDQ)/* Unpack and Interleave High-Order Quad-Words */
_ENUM_ELEMENT(VHADDPS)    /* Horizontal Add Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VHADDPD)    /* Horizontal Add Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VHSUBPS)    /* Horizontal Subtract Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VHSUBPD)    /* Horizontal Subtract Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVLPS)    /* Move Low Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVHPS)    /* Move High Packed Single-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVLPD)    /* Move Low Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVHPD)    /* Move High Packed Double-Precision Floating Point Values */
_ENUM_ELEMENT(VMOVSLDUP)  /* Move Packed Single-Precision Floating Point Values Low and Duplicate */
_ENUM_ELEMENT(VMOVSHDUP)  /* Move Packed Single-Precision Floating Point Values High and Duplicate */
_ENUM_ELEMENT(VPMINUB)    /* Minimum Packed Integer */
_ENUM_ELEMENT(VPMINSW)    /* Minimum Packed Integer */
_ENUM_ELEMENT(VPMAXUB)    /* Maximum Packed Integer */
_ENUM_ELEMENT(VPMAXSW)    /* Maximum Packed Integer */
_ENUM_ELEMENT(VPSHUFW)    /* Shuffle Packed Words */
_ENUM_ELEMENT(VPSHUFD)    /* Shuffle Packed Double-Words */
_ENUM_ELEMENT(VPSHUFHW)   /* Shuffle Packed High Words */ 
_ENUM_ELEMENT(VPSHUFLW)   /* Shuffle Packed Low Words */
_ENUM_ELEMENT(VPSUBB)     /* Subtract Packed Integer */
_ENUM_ELEMENT(VPSUBW)     /* Subtract Packed Integer */
_ENUM_ELEMENT(VPSUBD)     /* Subtract Packed Integer */
_ENUM_ELEMENT(VPSUBQ)     /* Subtract Packed Integer */
_ENUM_ELEMENT(VPADDB)     /* Add Packed Integer */
_ENUM_ELEMENT(VPADDW)     /* Add Packed Integer */
_ENUM_ELEMENT(VPADDD)     /* Add Packed Integer */
_ENUM_ELEMENT(VPSLLW)     /* Shift Packed Data Left Logical */
_ENUM_ELEMENT(VPSLLD)     /* Shift Packed Data Left Logical */
_ENUM_ELEMENT(VPSLLQ)     /* Shift Packed Data Left Logical */
_ENUM_ELEMENT(VPSLLDQ)    /* Shift Packed Data Left Logical */
_ENUM_ELEMENT(VPSRLW)     /* Shift Packed Data Right Logical */
_ENUM_ELEMENT(VPSRLD)     /* Shift Packed Data Right Logical */
_ENUM_ELEMENT(VPSRLQ)     /* Shift Packed Data Right Logical */
_ENUM_ELEMENT(VPSRLDQ)    /* Shift Packed Data Right Logical */
_ENUM_ELEMENT(VPSRAW)     /* Shift Packed Data Right Arithmetic */
_ENUM_ELEMENT(VPSRAD)     /* Shift Packed Data Right Arithmetic */
_ENUM_ELEMENT(VPMULLW)    /* Multiply Packed Signed Integers and Store Low Result */
_ENUM_ELEMENT(VPINSRW)    /* Insert Word */
_ENUM_ELEMENT(VPEXTRW)    /* Extract Word */
_ENUM_ELEMENT(VPMADDWD)   /* Multiply and Add Packed Integers */
_ENUM_ELEMENT(VPMULHW)    /* Multiply Packed Signed Integers and Store High Result */
_ENUM_ELEMENT(VPACKSSWB)  /* Pack with Signed Saturation */
_ENUM_ELEMENT(VPACKUSWB)  /* Pack with Unsigned Saturation */
_ENUM_ELEMENT(VPACKSSDW)  /* Pack with Signed Saturation */

_ENUM_ELEMENT(MOVBE)    /* Move Data after Swapping Bytes */
_ENUM_ELEMENT(CRC32)    /* Accumulate CRC32 Value */
/* SMX */
_ENUM_ELEMENT(GETSEC)   /* Safer Mode Extensions */
/* VMX */
_ENUM_ELEMENT(VMREAD)   /* Read Field from Virtual Machine Control Structure */
_ENUM_ELEMENT(VMWRITE)  /* Write Field to Virtual Machine Control Structure */
/* XSAVE */
_ENUM_ELEMENT(FXSAVE)   /* Save x87 FPU, MMX and MXCSR State */
_ENUM_ELEMENT(FXRSTOR)  /* Restore x87 FPU, MMX and MXCSR State */ 
_ENUM_ELEMENT(XGETBV)   /* Get Value of Extended Control Register */
_ENUM_ELEMENT(XSETBV)   /* Set Value of Extended Control Register */
/* prefixes */
_ENUM_ELEMENT(LOCK)        /* Assert #LOCK Signal Prefix */
_ENUM_ELEMENT(REPNE)       /* Repeat String Operation Prefix */
_ENUM_ELEMENT(REPNZ)       /* Repeat String Operation Prefix (same as REPNE) */
_ENUM_ELEMENT(REP)         /* Repeat String Operation Prefix */
_ENUM_ELEMENT(REPE)        /* Repeat String Operation Prefix (same as REP) */
_ENUM_ELEMENT(REPZ)        /* Repeat String Operation Prefix (same as REPZ) */
_ENUM_ELEMENT(PrefixCS)    /* CS Segment Override Prefix */
_ENUM_ELEMENT(PrefixSS)    /* SS Segment Override Prefix */
_ENUM_ELEMENT(PrefixDS)    /* DS Segment Override Prefix */
_ENUM_ELEMENT(PrefixES)    /* ES Segment Override Prefix */
_ENUM_ELEMENT(PrefixFS)    /* FS Segment Override Prefix */
_ENUM_ELEMENT(PrefixGS)    /* GS Segment Override Prefix */
_ENUM_ELEMENT(OperandSize)
_ENUM_ELEMENT(AddressSize)
_ENUM_STOP(Mnemonic, 0)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MNEMONIC_H__20CAFD53_E4D1_49A5_88DC_47A54ADFD022__ */
