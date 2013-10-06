/*
* Filename: GroupDecode.c
* Author:   DisAsmCompany
* Date:     24/09/2013
*
* Description: Decoding of OpCode extensions
*              (GROUP1 - GROUPP)
*              
*
*/

#include "DisAsm"
#include "DisAsmContext.h"

void Group1Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = ADD; break;
	case 1: pInfo->mnemonic = OR;  break;
	case 2: pInfo->mnemonic = ADC; break;
	case 3: pInfo->mnemonic = SBB; break;
	case 4: pInfo->mnemonic = AND; break;
	case 5: pInfo->mnemonic = SUB; break;
	case 6: pInfo->mnemonic = XOR; break;
	case 7: pInfo->mnemonic = CMP; break;
	default: break;
	}
}

void Group1ADecode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = POP; break;
	case 1: break;
	case 2: break;
	case 3: break;
	case 4: break;
	case 5: break;
	case 6: break;
	case 7: break;
	default: break;
	}
}

void Group2Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = ROL; break;
	case 1: pInfo->mnemonic = ROR; break;
	case 2: pInfo->mnemonic = RCL; break;
	case 3: pInfo->mnemonic = RCR; break;
	case 4: pInfo->mnemonic = SHL; break;
	case 5: pInfo->mnemonic = SHR; break;
	case 6: pInfo->mnemonic = SAL; break;
	case 7: pInfo->mnemonic = SAR; break;
	default: break;
	}
}

void Group3Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0:
	case 1:
		pInfo->mnemonic = TEST;
		pInfo->nOperands = 2;
		pInfo->operands[1].type = (0xF6 == pInfo->opcode) ? Ib : Iz;
		break;
	case 2: pInfo->mnemonic = NOT;  break;
	case 3: pInfo->mnemonic = NEG;  break;
	case 4: pInfo->mnemonic = MUL;  break;
	case 5: pInfo->mnemonic = IMUL; break;
	case 6: pInfo->mnemonic = DIV;  break;
	case 7: pInfo->mnemonic = IDIV; break;
	default: break;
	}
}

void Group4Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	pInfo->nOperands = 1;
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = INC;  pInfo->operands[0].type = Eb; break;
	case 1: pInfo->mnemonic = DEC;  pInfo->operands[0].type = Eb; break;
	case 2: break;
	case 3: break;
	case 4: break;
	case 5: break;
	case 6: break;
	case 7: break;
	default: break;
	}
}

void Group5Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	pInfo->nOperands = 1;
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = INC;  pInfo->operands[0].type = Ev; break;
	case 1: pInfo->mnemonic = DEC;  pInfo->operands[0].type = Ev; break;
	case 2: pInfo->mnemonic = CALL; pInfo->operands[0].type = Ev; break;
	case 3: pInfo->mnemonic = CALL; pInfo->operands[0].type = Mp; break;
	case 4: pInfo->mnemonic = JMP;  pInfo->operands[0].type = Ev; break;
	case 5: pInfo->mnemonic = JMP;  pInfo->operands[0].type = Mp; break;
	case 6: pInfo->mnemonic = PUSH; pInfo->operands[0].type = Ev; break;
	case 7: break;
	default: break;
	}
}

void Group8Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: break;
	case 1: break;
	case 2: break;
	case 3: break;
	case 4: pInfo->mnemonic = BT;  break;
	case 5: pInfo->mnemonic = BTS; break;
	case 6: pInfo->mnemonic = BTR; break;
	case 7: pInfo->mnemonic = BTC; break;
	default: break;
	}
}

/*
according to AMD manual, all GROUP10 variants are defined as UD1, 
according to Intel, it is just unnamed undefined instructions
*/
void Group10Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = UD1; break;
	case 1: pInfo->mnemonic = UD1; break;
	case 2: pInfo->mnemonic = UD1; break;
	case 3: pInfo->mnemonic = UD1; break;
	case 4: pInfo->mnemonic = UD1; break;
	case 5: pInfo->mnemonic = UD1; break;
	case 6: pInfo->mnemonic = UD1; break;
	case 7: pInfo->mnemonic = UD1; break;
	default: break;
	}
}

void Group11Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = MOV; break;
	case 1: break;
	case 2: break;
	case 3: break;
	case 4: break;
	case 5: break;
	case 6: break;
	case 7: break;
	default: break;
	}
}

void Group15Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		default: break;
	}
}

/*
according to AMD manual, /4 - /7 forms are defines as valid instructions (NOPs)
for compatibility with future PREFETCH instructions
*/
void Group16Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = PREFETCHT0; break;
	case 1: pInfo->mnemonic = PREFETCHT1; break;
	case 2: pInfo->mnemonic = PREFETCHT2; break;
	case 3: pInfo->mnemonic = PREFETCHNTA; break;
	case 4: pInfo->mnemonic = NOP; break;
	case 5: pInfo->mnemonic = NOP; break;
	case 6: pInfo->mnemonic = NOP; break;
	case 7: pInfo->mnemonic = NOP; break;
	default: break;
	}
}

/*
Intel defines just /0 for PREFETCHW
AMD defines /0, /1 and /3, others are aliases to /0 for compatibility with future PREFETCH instructions
*/
void GroupPDecode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	switch (pInfo->ModRM.fields.Reg)
	{
	case 0: pInfo->mnemonic = PREFETCHW; break;
	case 1: pInfo->mnemonic = PREFETCHW; break;
	case 2: pInfo->mnemonic = PREFETCHW; break;
	case 3: pInfo->mnemonic = PREFETCHW; break;
	case 4: pInfo->mnemonic = PREFETCHW; break;
	case 5: pInfo->mnemonic = PREFETCHW; break;
	case 6: pInfo->mnemonic = PREFETCHW; break;
	case 7: pInfo->mnemonic = PREFETCHW; break;
	default: break;
	}
}

/*
      1  1A 2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 P 
GROUP XX XX XX XX XX XX             XX XX             XX    XX
*/

void GroupDecode(HDISASM hDisAsm, InstructionInfo * pInfo)
{
	DisAsmContext * pContext = (DisAsmContext*) hDisAsm;
	switch (pInfo->mnemonic)
	{
	case GROUP1 : Group1Decode (pContext, pInfo); break;
	case GROUP1A: Group1ADecode(pContext, pInfo); break;
	case GROUP2 : Group2Decode (pContext, pInfo); break;
	case GROUP3 : Group3Decode (pContext, pInfo); break;
	case GROUP4 : Group4Decode (pContext, pInfo); break;
	case GROUP5 : Group5Decode (pContext, pInfo); break;
	case GROUP8 : Group8Decode (pContext, pInfo); break;
	case GROUP10: Group10Decode(pContext, pInfo); break;
	case GROUP11: Group11Decode(pContext, pInfo); break;
	case GROUP15: Group15Decode(pContext, pInfo); break;
	case GROUP16: Group16Decode(pContext, pInfo); break;
	case GROUPP : GroupPDecode (pContext, pInfo); break;
	default: break;
	}
}
