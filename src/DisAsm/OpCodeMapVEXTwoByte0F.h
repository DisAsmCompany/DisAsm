/*
* Filename: OpCodeMapTwoByte0F.h
* Author:   DisAsmCompany
* Date:     04/01/2014
*
* Description: VEX OpCode Map (OpCodes 0F00h - 0FFFh)
*              
*              
*
*/

#ifndef __OPCODEMAPTVEXTWOBYTE0F_CF032DE1_90B1_44E7_81FC_B08D10AE845F__
#define __OPCODEMAPTVEXTWOBYTE0F_CF032DE1_90B1_44E7_81FC_B08D10AE845F__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* VEX OpCode Map (OpCodes 0F00h - 0FFFh) */

/* 
       0 1 2 3 4 5 6 7   8 9 A B C D E F
NONE 0                 0                 0
0x66 0                 0                 0
0xF2 0                 0                 0
0xF3 0                 0                 0
NONE 1                 1                 1
0 66 1                 1                 1
0xF2 1                 1                 1
0xF3 1                 1                 1
NONE 2                 2                 2
0 66 2                 2                 2
0xF2 2                 2                 2
0xF3 2                 2                 2
NONE 3                 3                 3
0 66 3                 3                 3
0xF2 3                 3                 3
0xF3 3                 3                 3
NONE 4                 4                 4
0 66 4                 4                 4
0xF2 4                 4                 4
0xF3 4                 4                 4
NONE 5                 5                 5
0 66 5                 5                 5
0xF2 5                 5                 5
0xF3 5                 5                 5
NONE 6                 6                 6
0 66 6                 6                 6
0xF2 6                 6                 6
0xF3 6                 6                 6
NONE 7                 7                 7
0 66 7                 7                 7
0xF2 7                 7                 7
0xF3 7                 7                 7
       0 1 2 3 4 5 6 7   8 9 A B C D E F
NONE 8                 8                 8
0 66 8                 8                 8
0xF2 8                 8                 8
0xF3 8                 8                 8
NONE 9                 9                 9
0 66 9                 9                 9
0xF2 9                 9                 9
0xF3 9                 9                 9
NONE A                 A                 A
0 66 A                 A                 A
0xF2 A                 A                 A
0xF3 A                 A                 A
NONE B                 B                 B
0 66 B                 B                 B
0xF2 B                 B                 B
0xF3 B                 B                 B
NONE C                 C                 C
0 66 C                 C                 C
0xF2 C                 C                 C
0xF3 C                 C                 C
NONE D                 D                 D
0 66 D                 D                 D
0xF2 D                 D                 D
0xF3 D                 D                 D
NONE E                 E                 E
0 66 E                 E                 E
0xF2 E                 E                 E
0xF3 E                 E                 E
NONE F                 F                 F
0 66 F                 F                 F
0xF2 F                 F                 F
0xF3 F                 F                 F
       0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

/* each bit indicates does opcode has extensions for prefixes 0x66, 0xF2 or 0xF3 */
uint32_t OpCodeMapVEXTwoByte0FExt[] =
{
	/* 0F00h - 0F1Fh */
	0x00FFFF00UL,
	/* 0F20h - 0F3Fh */
	0xFF000007UL,
	/* 0F40h - 0F5Fh */
	0xFF0000FFUL,
	/* 0F60h - 0F7Fh */
	0xFF00000FUL,
	/* 0F80h - 0F9Fh */
	0x00000000UL,
	/* 0FA0h - 0FBFh */
	0x00000000UL,
	/* 0FC0h - 0FDFh */
	0x00000000UL,
	/* 0FE0h - 0FFFh */
	0x00000000UL
};

OpCodeMapElement OpCodeMapVEXTwoByte0F[] =
{
	/* 0F00h - 0F07h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F08h - 0F0Fh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F10h - 0F17h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F17h - 0F1Fh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F20h - 0F27h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F28h - 0F2Fh */
	{VMOVAPS, OP2(Vps, Wps)}, {VMOVAPS, OP2(Wps, Vps)}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{VMOVAPD, OP2(Vpd, Wpd)}, {VMOVAPD, OP2(Wpd, Vpd)}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0},                {DB, OP0},                {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0},                {DB, OP0},                {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F30h - 0F37h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F38h - 0F3Fh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F40h - 0F47h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F48h - 0F4Fh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F50h - 0F57h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {VANDPS, OP3(Vps, Hps, Wps)}, {VANDNPS, OP3(Vps, Hps, Wps)}, {VORPS, OP3(Vps, Hps, Wps)}, {VXORPS, OP3(Vps, Hps, Wps)},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {VANDPD, OP3(Vpd, Hpd, Wpd)}, {VANDNPD, OP3(Vpd, Hpd, Wpd)}, {VORPD, OP3(Vpd, Hpd, Wpd)}, {VXORPD, OP3(Vpd, Hpd, Wpd)},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},                    {DB, OP0},                     {DB, OP0},                   {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},                    {DB, OP0},                     {DB, OP0},                   {DB, OP0},
	/* 0F58h - 0F5Fh */
	{VADDPS, OP3(Vps, Hps, Wps)}, {VMULPS, OP3(Vps, Hps, Wps)}, {DB, OP0}, {DB, OP0}, {VSUBPS, OP3(Vps, Hps, Wps)}, {VMINPS, OP3(Vps, Hps, Wps)}, {VDIVPS, OP3(Vps, Hps, Wps)}, {VMAXPS, OP3(Vps, Hps, Wps)},
	{VADDPD, OP3(Vpd, Hpd, Wpd)}, {VMULPD, OP3(Vpd, Hpd, Wpd)}, {DB, OP0}, {DB, OP0}, {VSUBPD, OP3(Vpd, Hpd, Wpd)}, {VMINPD, OP3(Vpd, Hpd, Wpd)}, {VDIVPD, OP3(Vpd, Hpd, Wpd)}, {VMAXPD, OP3(Vpd, Hpd, Wpd)},
	{VADDSD, OP3(Vsd, Hsd, Wsd)}, {VMULSD, OP3(Vsd, Hsd, Wsd)}, {DB, OP0}, {DB, OP0}, {VSUBSD, OP3(Vsd, Hsd, Wsd)}, {VMINSD, OP3(Vsd, Hsd, Wsd)}, {VDIVSD, OP3(Vsd, Hsd, Wsd)}, {VMAXSD, OP3(Vsd, Hsd, Wsd)},
	{VADDSS, OP3(Vss, Hss, Wss)}, {VMULSS, OP3(Vss, Hss, Wss)}, {DB, OP0}, {DB, OP0}, {VSUBSS, OP3(Vss, Hss, Wss)}, {VMINSS, OP3(Vss, Hss, Wss)}, {VDIVSS, OP3(Vss, Hss, Wss)}, {VMAXSS, OP3(Vss, Hss, Wss)},
	/* 0F60h - 0F67h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F68h - 0F6Fh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F70h - 0F77h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {VZEROUPPER, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F78h - 0F7Fh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {VMOVDQA, OP2(Wx, Vx)},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {VMOVDQU, OP2(Wx, Vx)},
	/* 0F80h - 0F87h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F88h - 0F8Fh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F90h - 0F97h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0F98h - 0F9Fh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FA0h - 0FA7h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FA8h - 0FAFh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FB0h - 0FB7h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FB8h - 0FBFh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FC0h - 0FC7h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {VSHUFPS, OP4(Vps, Hps, Wps, Ib)}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {VSHUFPD, OP4(Vpd, Hpd, Wpd, Ib)}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},                         {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},                         {DB, OP0},
	/* 0FC8h - 0FCFh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FD0h - 0FD7h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FD8h - 0FDFh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FE0h - 0FE7h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FE8h - 0FEFh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FF0h - 0FF7h */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	/* 0FF8h - 0FFFh */
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
	{DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0}, {DB, OP0},
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPCODEMAPTVEXTWOBYTE0F_CF032DE1_90B1_44E7_81FC_B08D10AE845F__ */
