/*
* Filename: OpCodeMapThreeByte0F38.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh)
*              
*              
*
*/

#ifndef __OPCODEMAPTHREEBYTE0F38_H__7F439552_B615_4319_8D18_685E1201A3B8__
#define __OPCODEMAPTHREEBYTE0F38_H__7F439552_B615_4319_8D18_685E1201A3B8__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh) */

/* 
       0 1 2 3 4 5 6 7   8 9 A B C D E F
NONE 0 X X X X         0                 0
0x66 0 X X X X         0                 0
0xF2 0 U U U U         0                 0
0xF3 0 U U U U         0                 0
NONE 1                 1 U U U U X X X U 1
0 66 1                 1 U U U U X X X U 1
0xF2 1                 1 U U U U U U U U 1
0xF3 1                 1 U U U U U U U U 1
NONE 2 U U U U U U U U 2                 2
0 66 2 X X X X X X U U 2                 2
0xF2 2 U U U U U U U U 2                 2
0xF3 2 U U U U U U U U 2                 2
NONE 3 U U U U U U U   3 U U U U U U U U 3
0 66 3 X X X X X X U   3 X X X X X X X X 3
0xF2 3 U U U U U U U   3 U U U U U U U U 3
0xF3 3 U U U U U U U   3 U U U U U U U U 3
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
NONE F X X             F                 F
0 66 F X X             F                 F
0xF2 F X X             F                 F
0xF3 F U U             F                 F
       0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

/* each bit indicates does opcode has extensions for prefixes 0x66, 0xF2 or 0xF3 */
uint32_t OpCodeMapThreeByte0F38Ext[] =
{
	/* 0F3800h - 0F381Fh */
	0x70FFFFFFUL,
	/* 0F3820h - 0F383Fh */
	0xFFFFFF3FUL,
	/* 0F3840h - 0F385Fh */
	0x000000FFUL,
	/* 0F3860h - 0F387Fh */
	0x00000000UL,
	/* 0F3880h - 0F389Fh */
	0x00000000UL,
	/* 0F38A0h - 0F38BFh */
	0x00000000UL,
	/* 0F38C0h - 0F38DFh */
	0x00000000UL,
	/* 0F38E0h - 0F38FFh */
	0x00FF0000UL
};

OpCodeMapElement OpCodeMapThreeByte0F38[] =
{
	/* 0F3800h - 0F3807h */
	{PSHUFB, OP2(Ppb, Qpb)}, {PHADDW, OP2(Ppi, Qpi)}, {PHADDD, OP2(Ppj, Qpj)}, {PHADDSW, OP2(Ppi, Qpi)}, {PMADDUBSW, OP2(Ppk, Qpk)}, {PHSUBW, OP2(Ppi, Qpi)}, {PHSUBD, OP2(Ppj, Qpj)}, {PHSUBSW, OP2(Ppi, Qpi)},
	{PSHUFB, OP2(Vpb, Wpb)}, {PHADDW, OP2(Vpi, Wpi)}, {PHADDD, OP2(Vpj, Wpj)}, {PHADDSW, OP2(Vpi, Wpi)}, {PMADDUBSW, OP2(Vpk, Wpk)}, {PHSUBW, OP2(Vpi, Wpi)}, {PHSUBD, OP2(Vpj, Wpj)}, {PHSUBSW, OP2(Vpi, Wpi)},
	{DB},                    {DB},                    {DB},                    {DB},                     {DB},                       {DB},                    {DB},                    {DB},
	{DB},                    {DB},                    {DB},                    {DB},                     {DB},                       {DB},                    {DB},                    {DB},
	/* 0F3808h - 0F380Fh */
	{PSIGNB, OP2(Qpk, Ppk)}, {PSIGNW, OP2(Ppi, Qpi)}, {PSIGND, OP2(Ppj, Qpk)}, {PMULHRSW, OP2(Ppi, Qpi)}, {DB}, {DB}, {DB}, {DB},
	{PSIGNB, OP2(Vpk, Wpk)}, {PSIGNW, OP2(Vpi, Wpi)}, {PSIGND, OP2(Vpj, Wpk)}, {PMULHRSW, OP2(Vpi, Qpi)}, {DB}, {DB}, {DB}, {DB},
	{DB},                    {DB},                    {DB},                    {DB},                      {DB}, {DB}, {DB}, {DB},
	{DB},                    {DB},                    {DB},                    {DB},                      {DB}, {DB}, {DB}, {DB},
	/* 0F3810h - 0F3817h */
	{DB},                     {DB}, {DB}, {DB}, {DB},                     {DB},                     {DB}, {DB},
	{PBLENVB, OP2(Vpb, Wpb)}, {DB}, {DB}, {DB}, {BLENDPS, OP2(Vps, Wps)}, {BLENDPD, OP2(Vpd, Wpd)}, {DB}, {PTEST, OP2(Vo, Wo)},
	{DB},                     {DB}, {DB}, {DB}, {DB},                     {DB},                     {DB}, {DB},
	{DB},                     {DB}, {DB}, {DB}, {DB},                     {DB},                     {DB}, {DB},
	/* 0F3817h - 0F381Fh */
	{DB}, {DB}, {DB}, {DB}, {PABSB, OP2(Ppk, Qpk)}, {PABSW, OP2(Ppi, Qpi)}, {PABSD, OP2(Ppj, Qpj)}, {DB},
	{DB}, {DB}, {DB}, {DB}, {PABSB, OP2(Vpk, Wpk)}, {PABSW, OP2(Vpi, Wpi)}, {PABSD, OP2(Vpj, Wpj)}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB},                   {DB},                   {DB},                   {DB},
	{DB}, {DB}, {DB}, {DB}, {DB},                   {DB},                   {DB},                   {DB},
	/* 0F3820h - 0F3827h */
	{DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB}, {DB},
	{PMOVSXBW, OP2(Vpi, Wpk)}, {PMOVSXBD, OP2(Vpj, Wpk)}, {PMOVSXBQ, OP2(Vpq, Wpk)}, {PMOVSXWD, OP2(Vpj, Wpi)}, {PMOVSXWQ, OP2(Vpq, Wpi)}, {PMOVSXDQ, OP2(Vpq, Wpj)}, {DB}, {DB},
	{DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB}, {DB},
	{DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB}, {DB},
	/* 0F3828h - 0F382Fh */
	{DB}, {DB}, {DB},                    {DB},                      {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {MOVNTDQA, OP2(Vo, Mo)}, {PACKUSDW, OP2(Vpi, Wpj)}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB},                    {DB},                      {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB},                    {DB},                      {DB}, {DB}, {DB}, {DB},
	/* 0F3830h - 0F3837h */
	{DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB}, {DB},
	{PMOVZXBW, OP2(Vpi, Wpk)}, {PMOVZXBD, OP2(Vpj, Wpk)}, {PMOVZXBQ, OP2(Vpq, Wpk)}, {PMOVZXWD, OP2(Vpj, Wpi)}, {PMOVZXWQ, OP2(Vpq, Wpi)}, {PMOVZXDQ, OP2(Vpq, Wpj)}, {DB}, {DB},
	{DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB}, {DB},
	{DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB},                      {DB}, {DB},
	/* 0F3838h - 0F383Fh */
	{DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},
	{PMINSB, OP2(Vpk, Wpk)}, {PMINSD, OP2(Vpj, Wpj)}, {PMINUW, OP2(Vpi, Wpi)}, {PMINUD, OP2(Vpj, Wpj)}, {PMAXSB, OP2(Vpk, Wpk)}, {PMAXSD, OP2(Vpj, Wpj)}, {PMAXUW, OP2(Vpi, Wpi)}, {PMAXUD, OP2(Vpj, Wpj)},
	{DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},
	{DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},                    {DB},
	/* 0F3840h - 0F3847h */
	{DB}, {DB},                        {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {PHMINPOSUW, OP2(Vpi, Wpi)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB},                        {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB},                        {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3848h - 0F384Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3850h - 0F3857h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3857h - 0F385Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3860h - 0F3867h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3868h - 0F386Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3870h - 0F3877h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3878h - 0F387Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3880h - 0F3887h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3888h - 0F388Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3890h - 0F3897h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3898h - 0F389Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38A0h - 0F38A7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38A8h - 0F38AFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38B0h - 0F38B7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38B8h - 0F38BFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38C0h - 0F38C7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38C8h - 0F38CFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38D0h - 0F38D7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38D8h - 0F38DFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38E0h - 0F38E7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38E8h - 0F38EFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38F0h - 0F38F7h */
	{MOVBE, OP2(Gv, Mv)}, {MOVBE, OP2(Mv, Gv)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{MOVBE, OP2(Gw, Mw)}, {MOVBE, OP2(Mw, Gw)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{CRC32, OP2(Gd, Eb)}, {CRC32, OP2(Gd, Ev)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB},                 {DB},                 {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38F8h - 0F38FFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPCODEMAPTHREEBYTE0F38_H__7F439552_B615_4319_8D18_685E1201A3B8__ */
