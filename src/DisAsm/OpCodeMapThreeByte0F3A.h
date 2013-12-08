/*
* Filename: OpCodeMapThreeByte0F3A.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh)
*              
*              
*
*/

#ifndef __OPCODEMAPTHREEBYTE0F3A_H__99B82404_53A0_44f7_8611_8C35670D6F0C__
#define __OPCODEMAPTHREEBYTE0F3A_H__99B82404_53A0_44f7_8611_8C35670D6F0C__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh) */

/* 
       0 1 2 3 4 5 6 7   8 9 A B C D E F
NONE 0                 0 U U U U U U U X 0
0x66 0                 0 X X X X X X X X 0
0xF2 0                 0 U U U U U U U U 0
0xF3 0                 0 U U U U U U U U 0
NONE 1                 1 U U U U U U U   1
0 66 1                 1 U U U U X X X   1
0xF2 1                 1 U U U U U U U   1
0xF3 1                 1 U U U U U U U   1
NONE 2 U U U U U U U U 2                 2
0 66 2 X X X U U U U U 2                 2
0xF2 2 U U U U U U U U 2                 2
0xF3 2 U U U U U U U U 2                 2
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
NONE 6 U U U U U U U U 6                 6
0 66 6 X X X X U U U U 6                 6
0xF2 6 U U U U U U U U 6                 6
0xF3 6 U U U U U U U U 6                 6
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
uint32_t OpCodeMapThreeByte0F3AExt[] =
{
	/* 0F3A00h - 0F3A1Fh */
	0x00FFFF00UL,
	/* 0F3A20h - 0F3A3Fh */
	0xFF000007UL,
	/* 0F3A40h - 0F3A5Fh */
	0x000000FFUL,
	/* 0F3A60h - 0F3A7Fh */
	0x0000000FUL,
	/* 0F3A80h - 0F3A9Fh */
	0x00000000UL,
	/* 0F3AA0h - 0F3ABFh */
	0x00000000UL,
	/* 0F3AC0h - 0F3ADFh */
	0x00000000UL,
	/* 0F3AE0h - 0F3AFFh */
	0x00000000UL
};

OpCodeMapElement OpCodeMapThreeByte0F3A[] =
{
	/* 0F3A00h - 0F3A07h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A08h - 0F3A0Fh */
	{DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {PALIGNR, OP3(Ppb, Qpb, Ib)},
	{ROUNDPS, OP3(Vps, Wps, Ib)}, {ROUNDPD, OP3(Vpd, Wpd, Ib)}, {ROUNDSS, OP3(Vss, Wss, Ib)}, {ROUNDSD, OP3(Vsd, Wsd, Ib)}, {BLENDPS, OP3(Vps, Wps, Ib)}, {BLENDPD, OP3(Vpd, Wpd, Ib)}, {PBLENDW, OP3(Vpw, Wpw, Ib)}, {PALIGNR, OP3(Vpb, Wpb, Ib)},
	{DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {DB},
	{DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {DB},                         {DB},
	/* 0F3A10h - 0F3A17h */
	{DB}, {DB}, {DB}, {DB}, {DB},                       {DB},                       {DB},                       {DB},
	{DB}, {DB}, {DB}, {DB}, {PEXTRB, OP3(Mb, Vpk, Ib)}, {PEXTRW, OP3(Mw, Vpw, Ib)}, {PEXTRD, OP3(Md, Vpj, Ib)}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB},                       {DB},                       {DB},                       {DB},
	{DB}, {DB}, {DB}, {DB}, {DB},                       {DB},                       {DB},                       {DB},
	/* 0F3A17h - 0F3A1Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A20h - 0F3A27h */
	{DB},                       {DB},                         {DB},                       {DB}, {DB}, {DB}, {DB}, {DB},
	{PINSRB, OP3(Vpk, Mb, Ib)}, {INSERTPS, OP3(Vps, Md, Ib)}, {PINSRD, OP3(Vpj, Ed, Ib)}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB},                       {DB},                         {DB},                       {DB}, {DB}, {DB}, {DB}, {DB},
	{DB},                       {DB},                         {DB},                       {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A28h - 0F3A2Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A30h - 0F3A37h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A38h - 0F3A3Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A40h - 0F3A47h */
	{DB},                      {DB},                      {DB},                         {DB}, {DB}, {DB}, {DB}, {DB},
	{DPPS, OP3(Vps, Wps, Ib)}, {DPPD, OP3(Vpd, Wpd, Ib)}, {MPSADBW, OP3(Vpk, Wpk, Ib)}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB},                      {DB},                      {DB},                         {DB}, {DB}, {DB}, {DB}, {DB},
	{DB},                      {DB},                      {DB},                         {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A48h - 0F3A4Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A50h - 0F3A57h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A57h - 0F3A5Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A60h - 0F3A67h */
	{DB},                         {DB},                         {DB},                         {DB},                         {DB}, {DB}, {DB}, {DB},
	{PCMPESTRM, OP3(Vo, Wo, Ib)}, {PCMPESTRI, OP3(Vo, Wo, Ib)}, {PCMPISTRM, OP3(Vo, Wo, Ib)}, {PCMPISTRI, OP3(Vo, Wo, Ib)}, {DB}, {DB}, {DB}, {DB},
	{DB},                         {DB},                         {DB},                         {DB},                         {DB}, {DB}, {DB}, {DB},
	{DB},                         {DB},                         {DB},                         {DB},                         {DB}, {DB}, {DB}, {DB},
	/* 0F3A68h - 0F3A6Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A70h - 0F3A77h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A78h - 0F3A7Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A80h - 0F3A87h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A88h - 0F3A8Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A90h - 0F3A97h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3A98h - 0F3A9Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AA0h - 0F3AA7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AA8h - 0F3AAFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AB0h - 0F3AB7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AB8h - 0F3ABFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AC0h - 0F3AC7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AC8h - 0F3ACFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AD0h - 0F3AD7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AD8h - 0F3ADFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AE0h - 0F3AE7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AE8h - 0F3AEFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AF0h - 0F3AF7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F3AF8h - 0F3AFFh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OPCODEMAPTHREEBYTE0F3A_H__99B82404_53A0_44f7_8611_8C35670D6F0C__ */
