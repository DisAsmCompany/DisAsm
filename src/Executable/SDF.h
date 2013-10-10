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

typedef struct SDFElement_t
{
	char * name;
	uint32_t id;
	SDFType type;
	uint32_t size;
	uint32_t count;
}
SDFElement;

typedef void * HSDF;

uint32_t SDFSizeInBytes(const SDFElement * definition, uint32_t size);
HSDF SDFCreate(const SDFElement * definition, uint32_t size, HREADER hReader);
void SDFPrint(HSDF hSDF);

uint16_t SDFReadUInt16(HSDF hSDF, uint32_t id);
uint32_t SDFReadUInt32(HSDF hSDF, uint32_t id);

void SDFDestroy(HSDF hSDF);

#endif /* __SDF_H__ */
