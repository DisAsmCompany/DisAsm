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

char * PECharacteristicsToString(uint16_t Characteristics);
char * PEDllCharacteristicsToString(uint16_t Characteristics);
char * PESectionCharacteristicsToString(uint32_t Characteristics);
char * PESubsystemToString(uint16_t Subsystem);
char * PEMachineToString(uint16_t Machine);
char * PEMagicToString(uint16_t Magic);
char * PEDebugTypeToString(uint32_t Type);

void PEPrintDebugDirectory(PEDebugDirectory * pDebugDirectory);
void PEPrintLoadConfigDirectory(PELoadConfigDirectory * pLoadConfigDirectory);
void PEPrintExportDirectory(PEExportDirectory * pExportDirectory);
void PEPrintDOSHeader(PEDOSHeader * pDOSHeader);
void PEPrintSectionHeader(PESectionHeader * pSectionHeader);
void PEPrintOptionalHeader(PEOptionalHeader * pOptionalHeader);
void PEPrintFileHeader(PEFileHeader * pFileHeader);
void PEPrintImportDescriptor(PEImportDescriptor * pImportDescriptor);


#endif /* __PESTRING_H__ */