/*
* Filename: OpCodeMapTwoByte0F.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh)
*              
*              
*
*/

#ifndef __OPCODEMAPTWOBYTE0F_H__B448F901_0C8F_47E3_9D68_533F72EA7B3B__
#define __OPCODEMAPTWOBYTE0F_H__B448F901_0C8F_47E3_9D68_533F72EA7B3B__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh) */

/* 
       0 1 2 3 4 5 6 7   8 9 A B C D E F
NONE 0 X X X X X X X X 0 X X U X U X X + 0
0x66 0 X X X X X X X X 0 X X U X U X X + 0
0xF2 0 X X X X X X X X 0 X X U X U X X + 0
0xF3 0 X X X X X X X X 0 X X U X U X X + 0
NONE 1 X X X X X X X X 1 X X X X X X X X 1
0x66 1 X X X X X X X X 1 X X X X X X X X 1
0xF2 1 X X X U U U U U 1 X X X X X X X X 1
0xF3 1 X X X U U U X U 1 X X X X X X X X 1
NONE 2 X X X X U U U U 2 X X X X X X X X 2
0x66 2 X X X X U U U U 2 X X X X X X X X 2
0xF2 2 X X X X U U U U 2 U U X X X X U U 2
0xF3 2 X X X X U U U U 2 U U X X X X U U 2
NONE 3 X X X X X X U X 3 + U + U U U U U 3
0x66 3 X X X X X X U X 3 + U + U U U U U 3
0xF2 3 X X X X X X U X 3 + U + U U U U U 3
0xF3 3 X X X X X X U X 3 + U + U U U U U 3
NONE 4 X X X X X X X X 4 X X X X X X X X 4
0x66 4 X X X X X X X X 4 X X X X X X X X 4
0xF2 4 X X X X X X X X 4 X X X X X X X X 4
0xF3 4 X X X X X X X X 4 X X X X X X X X 4
NONE 5 X X X X X X X X 5 X X X X X X X X 5
0x66 5 X X U U X X X X 5 X X X X X X X X 5
0xF2 5 U X U U U U U U 5 X X X U X X X X 5
0xF3 5 U X X X U U U U 5 X X X X X X X X 5
NONE 6 X X X X X X X X 6 X X X X U U X X 6
0x66 6 X X X X X X X X 6 X X X X X X X X 6
0xF2 6 U U U U U U U U 6 U U U U U U U U 6
0xF3 6 U U U U U U U U 6 U U U U U U U X 6
NONE 7 X X X X X X X X 7 X X U U U U X X 7
0x66 7 X X X X X X X U 7 X X U U X X X X 7
0xF2 7 X X X X U U U U 7 X X U U X X U U 7
0xF3 7 X X X X U U U U 7 U U U U U U X X 7
       0 1 2 3 4 5 6 7   8 9 A B C D E F
NONE 8 X X X X X X X X 8 X X X X X X X X 8
0x66 8 X X X X X X X X 8 X X X X X X X X 8
0xF2 8 X X X X X X X X 8 X X X X X X X X 8
0xF3 8 X X X X X X X X 8 X X X X X X X X 8
NONE 9 X X X X X X X X 9 X X X X X X X X 9
0x66 9 X X X X X X X X 9 X X X X X X X X 9
0xF2 9 X X X X X X X X 9 X X X X X X X X 9
0xF3 9 X X X X X X X X 9 X X X X X X X X 9
NONE A X X X X X X U U A X X X X X X X X A
0x66 A X X X X X X U U A X X X X X X X X A
0xF2 A X X X X X X U U A X X X X X X X X A
0xF3 A X X X X X X U U A X X X X X X X X A
NONE B X X X X X X X X B X X X X X X X X B
0x66 B X X X X X X X X B U X X X U U X X B
0xF2 B X X X X X X X X B U X X X U U X X B
0xF3 B X X X X X X X X B X X X X X X X X B
NONE C X X X X X X X X C X X X X X X X X C
0x66 C X X X U X X X X C X X X X X X X X C
0xF2 C X X X U U U U X C X X X X X X X X C
0xF3 C X X X U U U U X C X X X X X X X X C
NONE D U X X X X X U X D X X X X X X X X D
0x66 D X X X X X X X X D X X X X X X X X D
0xF2 D X U U U U U X U D U U U U U U U U D
0xF3 D U U U U U U X U D U U U U U U U U D
NONE E X X X X X X U X E X X X X X X X X E
0x66 E X X X X X X X X E X X X X X X X X E
0xF2 E U U U U U U X U E U U U U U U U U E
0xF3 E U U U U U U X U E U U U U U U U U E
NONE F U X X X X X X X F X X X X X X X X F
0x66 F U X X X X X X X F X X X X X X X X F
0xF2 F X U U U U U U U F U U U U U U U X F
0xF3 F U U U U U U U U F U U U U U U U X F
       0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

/* each bit indicates does opcode has extensions for prefixes 0x66, 0xF2 or 0xF3 */
uint32_t OpCodeMapTwoByte0FExt[] =
{
	/* 0F00h - 0F1Fh */
	0x00FF0000UL,
	/* 0F20h - 0F3Fh */
	0x0000FF00UL,
	/* 0F40h - 0F5Fh */
	0xFFFF0000UL,
	/* 0F60h - 0F7Fh */
	0xFF79FFFFUL,
	/* 0F80h - 0F9Fh */
	0x00000000UL,
	/* 0FA0h - 0FBFh */
	0x39000000UL,
	/* 0FC0h - 0FDFh */
	0xFFFF0080UL,
	/* 0FE0h - 0FFFh */
	0xFFFFFFFFUL
};

OpCodeMapElement OpCodeMapTwoByte0F[] =
{
	/* 0F00h - 0F07h */
	{GROUP6}, {GROUP7}, {LAR, OP2(Gv, Ew)}, {LSL, OP2(Gv, Ew)}, {LOADALL}, {SYSCALL}, {CLTS}, {SYSRET},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F08h - 0F0Fh */
	{INVD}, {WBINVD}, {DB}, {UD2}, {DB}, {GROUPP, OP1(Mb)}, {FEMMS}, {ESCAPE3DNOW},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F10h - 0F17h */
	{MOVUPS, OP2(Vps, Wps)}, {MOVUPS, OP2(Wps, Vps)}, {MOVLPS, OP2(Vq, Mq)},     {MOVLPS, OP2(Mq, Vq)},  {UNPCKLPS, OP2(Wps, Vps)}, {UNPCKHPS, OP2(Wps, Vps)}, {MOVHPS, OP2(Voq, Mq)},    {MOVHPS, OP2(Mq, Voq)},
	{MOVUPD, OP2(Vpd, Wpd)}, {MOVUPD, OP2(Wss, Vss)}, {MOVLPD, OP2(Voq, Mq)},    {MOVLPD, OP2(Mq, Voq)}, {UNPCKLPS, OP2(Wpd, Vpd)}, {UNPCKHPS, OP2(Wpd, Vpd)}, {MOVHPD, OP2(Voq, Mq)},    {MOVHPD, OP2(Mq, Voq)},
	{MOVSD,  OP2(Vsd, Wsd)}, {MOVSD,  OP2(Wsd, Vsd)}, {MOVDDUP, OP2(Vo, Wsd)},   {DB},                   {DB},                      {DB},                      {DB},                      {DB},
	{MOVSS,  OP2(Vss, Wss)}, {MOVSS,  OP2(Wss, Vss)}, {MOVSLDUP, OP2(Vps, Wps)}, {DB},                   {DB},                      {DB},                      {MOVSHDUP, OP2(Vps, Wps)}, {DB},
	/* 0F18h - 0F1Fh */
	{GROUP16, OP1(Mb)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F20h - 0F27h */
	{MOV, OP2(Rd, Cd)}, {MOV, OP2(Rd, Dd)}, {MOV, OP2(Cd, Rd)}, {MOV, OP2(Dd, Rd)}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F28h - 0F2Fh */
	{MOVAPS, OP2(Vps, Wps)}, {MOVAPS, OP2(Wps, Vps)}, {CVTPI2PS, OP2(Vps, Qpi)}, {MOVNTPS, OP2(Mo, Vps)}, {CVTTPS2PI, OP2(Ppi, Wps)}, {CVTPS2PI, OP2(Ppi, Wps)}, {UCOMISS, OP2(Vss, Wss)}, {COMISS, OP2(Vss, Wss)},
	{MOVAPD, OP2(Vpd, Wpd)}, {MOVAPD, OP2(Wpd, Vpd)}, {CVTPI2PD, OP2(Vpd, Qpi)}, {MOVNTPD, OP2(Mo, Vpd)}, {CVTTPD2PI, OP2(Ppi, Wpd)}, {CVTPD2PI, OP2(Ppi, Wpd)}, {UCOMISD, OP2(Vsd, Wsd)}, {COMISD, OP2(Vsd, Wsd)},
	{DB},                    {DB},                    {CVTSI2SD, OP2(Vsd, Ey)},  {MOVNTSD, OP2(Mo, Vsd)}, {CVTTSD2SI, OP2(Ey, Wsd)},  {CVTSD2SI, OP2(Ey, Wsd)},  {DB}, {DB},
	{DB},                    {DB},                    {CVTSI2SS, OP2(Vss, Ey)},  {MOVNTSS, OP2(Mo, Vss)}, {CVTTSS2SI, OP2(Ey, Wss)},  {CVTSS2SI, OP2(Ey, Wss)},  {DB}, {DB},
	/* 0F30h - 0F37h */
	{WRMSR}, {RDTSC}, {RDMSR}, {RDPMC}, {SYSENTER}, {SYSEXIT}, {DB}, {GETSEC},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38h - 0F3Fh */
	{ESCAPE}, {DB}, {ESCAPE}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F40h - 0F47h */
	{CMOVO, OP2(Gv, Ev)}, {CMOVNO, OP2(Gv, Ev)}, {CMOVB, OP2(Gv, Ev)}, {CMOVAE, OP2(Gv, Ev)}, {CMOVE, OP2(Gv, Ev)}, {CMOVNE, OP2(Gv, Ev)}, {CMOVBE, OP2(Gv, Ev)}, {CMOVA, OP2(Gv, Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F48h - 0F4Fh */
	{CMOVS, OP2(Gv, Ev)}, {CMOVNS, OP2(Gv, Ev)}, {CMOVP, OP2(Gv, Ev)}, {CMOVNP, OP2(Gv, Ev)}, {CMOVL, OP2(Gv, Ev)}, {CMOVNL, OP2(Gv, Ev)}, {CMOVLE, OP2(Gv, Ev)}, {CMOVNLE, OP2(Gv, Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F50h - 0F57h */
	{MOVMSKPS, OP2(Gd, Ups)}, {SQRTPS, OP2(Vps, Wps)}, {RSQRTPS, OP2(Vps, Wps)}, {RCPPS, OP2(Vps, Wps)}, {ANDPS, OP2(Vps, Wps)}, {ANDNPS, OP2(Vps, Wps)}, {ORPS, OP2(Vps, Wps)}, {XORPS, OP2(Vps, Wps)},
	{MOVMSKPD, OP2(Gd, Upd)}, {SQRTPD, OP2(Vpd, Wpd)}, {DB},                     {DB},                   {ANDPD, OP2(Vpd, Wpd)}, {ANDNPD, OP2(Vpd, Wpd)}, {ORPD, OP2(Vpd, Wpd)}, {XORPD, OP2(Vpd, Wpd)},
	{DB},                     {SQRTSD, OP2(Vsd, Wsd)}, {DB},                     {DB},                   {DB},                   {DB},                    {DB},                  {DB},
	{DB},                     {SQRTSS, OP2(Vss, Wss)}, {RSQRTSS, OP2(Vss, Wss)}, {RCPSS, OP2(Vss, Wss)}, {DB},                   {DB},                    {DB},                  {DB},
	/* 0F58h - 0F5Fh */
	{ADDPS, OP2(Vps, Wps)}, {MULPS, OP2(Vps, Wps)}, {CVTPS2PD, OP2(Vpd, Wps)}, {CVTDQ2PS, OP2(Vps, Wo)},  {SUBPS, OP2(Vps, Wps)}, {MINPS, OP2(Vps, Wps)}, {DIVPS, OP2(Vps, Wps)}, {MAXPS, OP2(Vps, Wps)},
	{ADDPD, OP2(Vpd, Wpd)}, {MULPD, OP2(Vpd, Wpd)}, {CVTPD2PS, OP2(Vps, Wpd)}, {CVTPS2DQ, OP2(Vo, Wps)},  {SUBPD, OP2(Vpd, Wpd)}, {MINPD, OP2(Vpd, Wpd)}, {DIVPD, OP2(Vpd, Wpd)}, {MAXPD, OP2(Vpd, Wpd)},
	{ADDSD, OP2(Vsd, Wsd)}, {MULSD, OP2(Vsd, Wsd)}, {CVTSD2SS, OP2(Vss, Wsd)}, {DB},                      {SUBSD, OP2(Vsd, Wsd)}, {MINSD, OP2(Vsd, Wsd)}, {DIVSD, OP2(Vsd, Wsd)}, {MAXSD, OP2(Vsd, Wsd)},
	{ADDSS, OP2(Vss, Wss)}, {MULSS, OP2(Vss, Wss)}, {CVTSS2SD, OP2(Vsd, Wss)}, {CVTTPS2DQ, OP2(Vo, Wps)}, {SUBSS, OP2(Vss, Wss)}, {MINSS, OP2(Vss, Wss)}, {DIVSS, OP2(Vss, Wss)}, {MAXSS, OP2(Vss, Wss)},
	/* 0F60h - 0F67h */
	{PUNPCKLBW, OP2(Pq, Qd)},   {PUNPCKLWD, OP2(Pq, Qd)},   {PUNPCKLDQ, OP2(Pq, Qd)},   {PACKSSWB, OP2(Ppi, Qpi)}, {PCMPGTB, OP2(Ppk, Qpk)}, {PCMPGTW, OP2(Ppi, Qpi)}, {PCMPGTD, OP2(Ppj, Qpj)}, {PACKUSWB, OP2(Ppi, Qpi)},
	{PUNPCKLBW, OP2(Voq, Woq)}, {PUNPCKLWD, OP2(Voq, Woq)}, {PUNPCKLDQ, OP2(Voq, Woq)}, {PACKSSWB, OP2(Vpi, Wpi)}, {PCMPGTB, OP2(Vpk, Wpk)}, {PCMPGTW, OP2(Vpi, Wpi)}, {PCMPGTD, OP2(Vpj, Vpj)}, {PACKUSWB, OP2(Vpi, Wpi)},
	{DB},                       {DB},                       {DB},                       {DB},                      {DB},                     {DB},                     {DB},                     {DB},
	{DB},                       {DB},                       {DB},                       {DB},                      {DB},                     {DB},                     {DB},                     {DB},
	/* 0F68h - 0F6Fh */
	{PUNPCKHBW, OP2(Pq, Qd)}, {PUNPCKHWD, OP2(Pq, Qd)}, {PUNPCKHDQ, OP2(Pq, Qd)}, {PACKSSDW, OP2(Pq, Qq)}, {DB},                      {DB},                      {MOVD, OP2(Py, Ey)}, {MOVQ, OP2(Pq, Qq)},
	{PUNPCKHBW, OP2(Vo, Wq)}, {PUNPCKHWD, OP2(Vo, Wq)}, {PUNPCKHDQ, OP2(Vo, Wq)}, {PACKSSDW, OP2(Vo, Wo)}, {PUNPCKLQDQ, OP2(Vo, Wq)}, {PUNPCKHQDQ, OP2(Vo, Wq)}, {MOVD, OP2(Vy, Ey)}, {MOVDQA, OP2(Vo, Wo)},
	{DB},                     {DB},                     {DB},                     {DB},                    {DB},                      {DB},                      {DB},                {DB},
	{DB},                     {DB},                     {DB},                     {DB},                    {DB},                      {DB},                      {DB},                {MOVDQU, OP2(Vo, Wo)},
	/* 0F70h - 0F77h */
	{PSHUFW, OP3(Pq, Qq, Ib)},  {GROUP12},    {GROUP13},    {GROUP14},    {PCMPEQB, OP2(Ppk, Qpk)}, {PCMPEQW, OP2(Ppi, Qpi)}, {PCMPEQD, OP2(Ppj, Qpj)}, {EMMS},
	{PSHUFD, OP3(Vo, Wo, Ib)},  {GROUP12_66}, {GROUP13_66}, {GROUP14_66}, {PCMPEQB, OP2(Vpk, Wpk)}, {PCMPEQW, OP2(Vpk, Wpk)}, {PCMPEQD, OP2(Vpk, Wpk)}, {DB},
	{PSHUFLW, OP3(Vq, Wq, Ib)}, {DB},         {DB},         {DB},         {DB},                     {DB},                     {DB},                     {DB},
	{PSHUFHW, OP3(Vq, Wq, Ib)}, {DB},         {DB},         {DB},         {DB},                     {DB},                     {DB},                     {DB},
	/* 0F78h - 0F7Fh */
	{VMREAD, OP2(Ey, Gy)},            {VMWRITE, OP2(Gy, Ey)},   {DB}, {DB}, {DB},                    {DB},                    {MOVD, OP2(Ey, Py)}, {MOVQ, OP2(Qq, Pq)},
	{GROUP17},                        {EXTRQ, OP2(Voq, Uo)},    {DB}, {DB}, {HADDPD, OP2(Vpd, Wpd)}, {HSUBPD, OP2(Vpd, Wpd)}, {MOVD, OP2(Vy, Ey)}, {MOVDQA, OP2(Wo, Vo)},
	{INSERTQ, OP4(Voq, Uoq, Ib, Ib)}, {INSERTQ, OP2(Voq, Uoq)}, {DB}, {DB}, {HADDPS, OP2(Vps, Wps)}, {HSUBPS, OP2(Vps, Wps)}, {DB},                {DB},
	{DB},                             {DB},                     {DB}, {DB}, {DB},                    {DB},                    {MOVQ, OP2(Vq, Wq)}, {MOVDQU, OP2(Wo, Vo)},
	/* 0F80h - 0F87h */
	{JO, OP1(Jz)}, {JNO, OP1(Jz)}, {JB, OP1(Jz)}, {JAE, OP1(Jz)}, {JE, OP1(Jz)}, {JNE, OP1(Jz)}, {JBE, OP1(Jz)}, {JA, OP1(Jz)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F88h - 0F8Fh */
	{JS, OP1(Jz)}, {JNS, OP1(Jz)}, {JP, OP1(Jz)}, {JNP, OP1(Jz)}, {JL, OP1(Jz)}, {JNL, OP1(Jz)}, {JLE, OP1(Jz)}, {JNLE, OP1(Jz)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F90h - 0F97h */
	{SETO, OP1(Eb)}, {SETNO, OP1(Eb)}, {SETB, OP1(Eb)}, {SETAE, OP1(Eb)}, {SETE, OP1(Eb)}, {SETNE, OP1(Eb)}, {SETBE, OP1(Eb)}, {SETA, OP1(Eb)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F98h - 0F9Fh */
	{SETS, OP1(Eb)}, {SETNS, OP1(Eb)}, {SETP, OP1(Eb)}, {SETNP, OP1(Eb)}, {SETL, OP1(Eb)}, {SETNL, OP1(Eb)}, {SETLE, OP1(Eb)}, {SETNLE, OP1(Eb)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FA0h - 0FA7h */
	{PUSH, OP1(FS)}, {POP, OP1(FS)}, {CPUID}, {BT, OP2(Ev, Gv)}, {SHLD, OP3(Ev, Gv, Ib)}, {SHLD, OP3(Ev, Gv, CL)}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FA8h - 0FAFh */
	{PUSH, OP1(GS)}, {POP, OP1(GS)}, {RSM}, {BTS, OP2(Ev, Gv)}, {SHRD, OP3(Ev, Gv, Ib)}, {SHRD, OP3(Ev, Gv, CL)}, {GROUP15}, {IMUL, OP2(Gv, Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FB0h - 0FB7h */
	{CMPXCHG, OP2(Eb, Gb)}, {CMPXCHG, OP2(Ev, Gv)}, {LSS, OP2(Gv, Mp)}, {BTR, OP2(Ev, Gv)}, {LFS, OP2(Gv, Mp)}, {LGS, OP2(Gv, Mp)}, {MOVZX, OP2(Gv, Eb)}, {MOVZX, OP2(Gv, Ew)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FB8h - 0FBFh */
	{JMPE, OP1(Jz)},       {GROUP10}, {GROUP8, OP2(Ev, Ib)}, {BTC, OP2(Ev, Gv)}, {BSF, OP2(Gv, Ev)},   {BSR, OP2(Gv, Ev)},   {MOVSX, OP2(Gv, Eb)}, {MOVSX, OP2(Gv, Ev)},
	{DB},                  {DB},      {DB},                  {DB},               {DB},                 {DB},                 {DB},                 {DB},
	{DB},                  {DB},      {DB},                  {DB},               {DB},                 {DB},                 {DB},                 {DB},
	{POPCNT, OP2(Gv, Ev)}, {DB},      {DB},                  {DB},               {LZCNT, OP2(Gv, Ev)}, {LZCNT, OP2(Gv, Ev)}, {DB},                 {DB},
	/* 0FC0h - 0FC7h */
	{XADD, OP2(Eb, Gb)}, {XADD, OP2(Ev, Gv)}, {CMPPS, OP3(Vps, Wps, Ib)}, {MOVNTI, OP2(My, Gy)}, {PINSRW, OP3(Pq, Ew, Ib)}, {PEXTRW, OP3(Gd, Nq, Ib)}, {SHUFPS, OP3(Vps, Wps, Ib)}, {GROUP9},
	{DB},                {DB},                {CMPPD, OP3(Vpd, Wpd, Ib)}, {DB},                  {PINSRW, OP3(Vo, Ew, Ib)}, {PEXTRW, OP3(Gd, Uo, Ib)}, {SHUFPD, OP3(Vpd, Wpd, Ib)}, {DB},
	{DB},                {DB},                {CMPSD, OP3(Vsd, Wss, Ib)}, {DB},                  {DB},                      {DB},                      {DB},                        {DB},
	{DB},                {DB},                {CMPSS, OP3(Vss, Wss, Ib)}, {DB},                  {DB},                      {DB},                      {DB},                        {DB},
	/* 0FC8h - 0FCFh */
	{BSWAP, OP1(rAX)}, {BSWAP, OP1(rCX)}, {BSWAP, OP1(rDX)}, {BSWAP, OP1(rBX)}, {BSWAP, OP1(rSP)}, {BSWAP, OP1(rBP)}, {BSWAP, OP1(rBP)}, {BSWAP, OP1(rDI)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FD0h - 0FD7h */
	{DB},                      {PSRLW, OP2(Pq, Qq)}, {PSRLD, OP2(Pq, Qq)}, {PSRLQ, OP2(Pq, Qq)}, {PADDQ, OP2(Pq, Qq)}, {PMULLW, OP2(Pq, Qq)}, {DB},                   {PMOVMSKB, OP2(Gd, Nq)},
	{ADDSUBPD, OP2(Vpd, Wpd)}, {PSRLW, OP2(Vo, Wo)}, {PSRLD, OP2(Vo, Wo)}, {PSRLQ, OP2(Vo, Wo)}, {PADDQ, OP2(Vo, Wo)}, {PMULLW, OP2(Vo, Wo)}, {MOVQ, OP2(Wq, Vq)},    {PMOVMSKB, OP2(Gd, Uo)},
	{ADDSUBPS, OP2(Vps, Wps)}, {DB},                 {DB},                 {DB},                 {DB},                 {DB},                  {MOVDQ2Q, OP2(Pq, Uq)}, {DB},
	{DB},                      {DB},                 {DB},                 {DB},                 {DB},                 {DB},                  {MOVQ2DQ, OP2(Vo, Nq)}, {DB},
	/* 0FD8h - 0FDFh */
	{PSUBUSB, OP2(Pq, Qq)}, {PSUBUSW, OP2(Pq, Qq)}, {PMINUB, OP2(Pq, Qq)}, {PAND, OP2(Pq, Qq)}, {PADDUSB, OP2(Pq, Qq)}, {PADDUSW, OP2(Pq, Qq)}, {PMAXUB, OP2(Pq, Qq)}, {PANDN, OP2(Pq, Qq)},
	{PSUBUSB, OP2(Vo, Wo)}, {PSUBUSW, OP2(Vo, Wo)}, {PMINUB, OP2(Vo, Wo)}, {PAND, OP2(Vo, Wo)}, {PADDUSB, OP2(Vo, Wo)}, {PADDUSW, OP2(Vo, Wo)}, {PMAXUB, OP2(Vo, Wo)}, {PANDN, OP2(Vo, Wo)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FE0h - 0FE7h */
	{PAVGB, OP2(Pq, Qq)}, {PSRAW, OP2(Pq, Qq)}, {PSRAD, OP2(Pq, Qq)}, {PAVGW, OP2(Pq, Qq)}, {PMULHUW, OP2(Pq, Qq)}, {PMULHW, OP2(Pq, Qq)}, {DB},                       {MOVNTQ, OP2(Mq, Pq)},
	{PAVGB, OP2(Vo, Wo)}, {PSRAW, OP2(Vo, Wo)}, {PSRAD, OP2(Vo, Wo)}, {PAVGW, OP2(Vo, Wo)}, {PMULHUW, OP2(Vo, Wo)}, {PMULHW, OP2(Vo, Wo)}, {CVTTPD2DQ, OP2(Vpj, Wpd)}, {MOVNTDQ, OP2(Mo, Vo)},
	{DB},                 {DB},                 {DB},                 {DB},                 {DB},                   {DB},                  {CVTPD2DQ, OP2(Vpj, Wps)},  {DB},
	{DB},                 {DB},                 {DB},                 {DB},                 {DB},                   {DB},                  {CVTDQ2PD, OP2(Vpd, Wpj)},  {DB},
	/* 0FE8h - 0FEFh */
	{PSUBSB, OP2(Pq, Qq)}, {PSUBSW, OP2(Pq, Qq)}, {PMINSW, OP2(Pq, Qq)}, {POR, OP2(Pq, Qq)}, {PADDSB, OP2(Pq, Qq)}, {PADDSW, OP2(Pq, Qq)}, {PMAXSW, OP2(Pq, Qq)}, {PXOR, OP2(Pq, Qq)},
	{PSUBSB, OP2(Vo, Wo)}, {PSUBSW, OP2(Vo, Wo)}, {PMINSW, OP2(Vo, Wo)}, {POR, OP2(Vo, Wo)}, {PADDSB, OP2(Vo, Wo)}, {PADDSW, OP2(Vo, Wo)}, {PMAXSW, OP2(Vo, Wo)}, {PXOR, OP2(Vo, Wo)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FF0h - 0FF7h */
	{DB},                 {PSLLW, OP2(Pq, Qq)},   {PSLLD, OP2(Pq, Qq)},   {PSLLQ, OP2(Pq, Qq)},   {PMULUDQ, OP2(Pq, Qq)},   {PMADDWD, OP2(Pq, Qq)},   {PSADDBW, OP2(Pq, Qq)},   {MASKMOVQ, OP2(Pq, Qq)},
	{DB},                 {PSLLW, OP2(Vpq, Wpq)}, {PSLLD, OP2(Vpq, Wpq)}, {PSLLQ, OP2(Vpq, Wpq)}, {PMULUDQ, OP2(Vpj, Wpj)}, {PMADDWD, OP2(Vpi, Wpi)}, {PSADDBW, OP2(Vpk, Wpk)}, {MASKMOVDQU, OP2(Vpb, Wpb)},
	{LDDQU, OP2(Vo, Mo)}, {DB},                   {DB},                   {DB},                   {DB},                     {DB},                     {DB},                     {DB},
	{DB},                 {DB},                   {DB},                   {DB},                   {DB},                     {DB},                     {DB},                     {DB},
	/* 0FF8h - 0FFFh */
	{PSUBB, OP2(Pq, Qq)}, {PSUBW, OP2(Pq, Qq)}, {PSUBD, OP2(Pq, Qq)}, {PSUBQ, OP2(Pq, Qq)}, {PADDB, OP2(Pq, Qq)}, {PADDW, OP2(Pq, Qq)}, {PADDD, OP2(Pq, Qq)}, {UD0},
	{PSUBB, OP2(Vo, Wo)}, {PSUBW, OP2(Vo, Wo)}, {PSUBD, OP2(Vo, Wo)}, {PSUBQ, OP2(Vo, Wo)}, {PADDB, OP2(Vo, Wo)}, {PADDW, OP2(Vo, Wo)}, {PADDD, OP2(Vo, Wo)}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPCODEMAPTWOBYTE0F_H__B448F901_0C8F_47E3_9D68_533F72EA7B3B__ */
