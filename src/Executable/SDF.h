/*
 * Filename: SDF.h
 * Author:   DisAsmCompany
 * Date:     09/10/2013
 *
 * Description: SDF (Structure Definition Format)
 *              API declaration.
 *
 *
 */

#pragma once
#ifndef __SDF_H__
#define __SDF_H__

typedef enum SDFType_t
{
	kUnsigned,
	kUTC,
	kStringASCII,
	kReserved,
}
SDFType;

typedef struct SDFEnum_t
{
	char * name;
	uint32_t value;
}
SDFEnum;

typedef struct SDFElement_t
{
	char * name;
	SDFType type;
	uint32_t size;
	uint32_t count;
	const SDFEnum * enumeration;
}
SDFElement;

typedef void * HSDF;

uint32_t SDFSizeInBytes(const SDFElement * definition);
HSDF SDFCreate(const SDFElement * definition, HREADER hReader);
void SDFPrint(HSDF hSDF);

uint16_t SDFReadUInt16(HSDF hSDF, uint32_t id);
uint32_t SDFReadUInt32(HSDF hSDF, uint32_t id);

void SDFDestroy(HSDF hSDF);

#endif /* __SDF_H__ */
