/*
 * Filename: ELFABI.h
 * Author:   DisAsmCompany
 * Date:     25/10/2013
 *
 * Description: ELF ABI definition
 *              (Application Binary Interface)
 *
 *
 */

#pragma once
#ifndef __ELFABI_H__1CA347C4_28B8_4B0F_9BB5_2FFF713B76BA__
#define __ELFABI_H__1CA347C4_28B8_4B0F_9BB5_2FFF713B76BA__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static const SDFEnum ELFABI[] =
{
	{"ELFOSABI_SYSV",       0x00, 0},
	{"ELFOSABI_HPUX",       0x01, 0},
	{"ELFOSABI_NETBSD",     0x02, 0},
	{"ELFOSABI_LINUX",      0x03, 0},
	{"ELFOSABI_HURD",       0x04, 0},
	{"ELFOSABI_86OPEN",     0x05, 0},
	{"ELFOSABI_SOLARIS",    0x06, 0},
	{"ELFOSABI_AIX",        0x07, 0},
	{"ELFOSABI_IRIX",       0x08, 0},
	{"ELFOSABI_FREEBSD",    0x09, 0},
	{"ELFOSABI_TRU64",      0x0A, 0},
	{"ELFOSABI_MODESTO",    0x0B, 0},
	{"ELFOSABI_OPENBSD",    0x0C, 0},
	{"ELFOSABI_OPENVMS",    0x0D, 0},
	{"ELFOSABI_NSK",        0x0E, 0},
	{"ELFOSABI_AROS",       0x0F, 0},
	{"ELFOSABI_ARM_AEABI",  0x40, 0},
	{"ELFOSABI_ARM",        0x61, 0},
	{"ELFOSABI_STANDALONE", 0xFF, 0},
	{NULL, 0, 0}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ELFABI_H__1CA347C4_28B8_4B0F_9BB5_2FFF713B76BA__ */
