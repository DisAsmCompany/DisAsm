/*
 * Filename: PEString.h
 * Author:   DisAsmCompany
 * Date:     02/10/2013
 *
 * Description: PE file structures 
 *              string representation
 *
 *
 */

#pragma once
#ifndef __PESTRING_H__
#define __PESTRING_H__

void PrintSignature(uint32_t Signature, uint8_t size);

char * PECharacteristicsToString(uint16_t Characteristics);
char * PEDllCharacteristicsToString(uint16_t Characteristics);
char * PESectionCharacteristicsToString(uint32_t Characteristics);

#endif /* __PESTRING_H__ */
