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

#ifndef __MNEMONIC_H__
#define __MNEMONIC_H__

_ENUM_START(Mnemonic)
_ENUM_ELEMENT(DB)     /* Data Binary (not decoded instruction) */
_ENUM_ELEMENT(DAA)    /* Decimal Adjust AL after Addition */
_ENUM_ELEMENT(AAA)    /* ASCII Adjust AL after Addition */
_ENUM_ELEMENT(DAS)    /* Decimal Adjust AL after Subtraction */
_ENUM_ELEMENT(AAS)    /* ASCII Adjust AL after Subtraction */
_ENUM_ELEMENT(HLT)    /* Halt */
_ENUM_ELEMENT(CMC)    /* Complement Carry Flag */
_ENUM_ELEMENT(NOP)    /* No Operation */
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
_ENUM_ELEMENT(CALL)   /* Call Procedure */
_ENUM_ELEMENT(TEST)   /* Logical Compare */
_ENUM_ELEMENT(XCHG)   /* Exchange Register/Memory with Register */
_ENUM_ELEMENT(CPUID)  /* CPU Identification */
_ENUM_ELEMENT(UD2)    /* Undefined Instruction */
_ENUM_ELEMENT(RET)    /* Return from Procedure */
_ENUM_ELEMENT(LEAVE)  /* High Level Procedure Exit */
_ENUM_ELEMENT(LEA)    /* Load Effective Address */
_ENUM_ELEMENT(NOT)    /* One's Complement Negotiation */
_ENUM_ELEMENT(NEG)    /* Two's Complement Negotiation */
_ENUM_ELEMENT(MUL)    /* Unsigned Multiply */
_ENUM_ELEMENT(IMUL)   /* Signed Multiply */
_ENUM_ELEMENT(DIV)    /* Unsigned Divide */
_ENUM_ELEMENT(IDIV)   /* Signed Divide */
/* Move String to String */
_ENUM_ELEMENT(MOVS)   /* Move String to String */
_ENUM_ELEMENT(MOVSB)  /* Move String to String */
_ENUM_ELEMENT(MOVSW)  /* Move String to String */
_ENUM_ELEMENT(MOVSD)  /* Move String to String */
_ENUM_ELEMENT(MOVSQ)  /* Move String to String */
/* Compare String Operands */
_ENUM_ELEMENT(CMPS)   /* Compare String Operands */
_ENUM_ELEMENT(CMPSB)  /* Compare String Operands */
_ENUM_ELEMENT(CMPSW)  /* Compare String Operands */
_ENUM_ELEMENT(CMPSD)  /* Compare String Operands */
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
_ENUM_ELEMENT(GROUP3)
_ENUM_ELEMENT(GROUP4)
_ENUM_ELEMENT(GROUP5)
_ENUM_ELEMENT(GROUP6)
_ENUM_ELEMENT(GROUP7)
_ENUM_ELEMENT(GROUP8)
_ENUM_ELEMENT(GROUP9)
_ENUM_ELEMENT(GROUP10)
_ENUM_ELEMENT(GROUP11)
_ENUM_ELEMENT(GROUP12)
_ENUM_ELEMENT(GROUP13)
_ENUM_ELEMENT(GROUP14)
_ENUM_ELEMENT(GROUP15)
_ENUM_ELEMENT(GROUP16)
_ENUM_ELEMENT(GROUP17)
_ENUM_ELEMENT(GROUPP)
/* prefixes */
_ENUM_ELEMENT(LOCK)    /* Assert #LOCK Signal Prefix */
_ENUM_ELEMENT(REPNE)   /* Repeat String Operation Prefix */
_ENUM_ELEMENT(REPNZ)   /* Repeat String Operation Prefix (same as REPNE) */
_ENUM_ELEMENT(REP)     /* Repeat String Operation Prefix */
_ENUM_ELEMENT(REPE)    /* Repeat String Operation Prefix (same as REP) */
_ENUM_ELEMENT(REPZ)    /* Repeat String Operation Prefix (same as REPZ) */
_ENUM_ELEMENT(CS)      /* CS Segment Override Prefix */
_ENUM_ELEMENT(SS)      /* SS Segment Override Prefix */
_ENUM_ELEMENT(DS)      /* DS Segment Override Prefix */
_ENUM_ELEMENT(ES)      /* ES Segment Override Prefix */
_ENUM_ELEMENT(FS)      /* FS Segment Override Prefix */
_ENUM_ELEMENT(GS)      /* GS Segment Override Prefix */
_ENUM_ELEMENT(OperandSize)
_ENUM_ELEMENT(AddressSize)
_ENUM_STOP(Mnemonic)

#endif /* __MNEMONIC_H__ */
