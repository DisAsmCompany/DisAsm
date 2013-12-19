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
#ifndef __SDF_H__3C52F878_0BF8_4371_B9E3_E153B9F9487D__
#define __SDF_H__3C52F878_0BF8_4371_B9E3_E153B9F9487D__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum SDFType_t
{
	kUnsigned,
	kUTC,
	kVersion,
	kSignature,
	kStringASCII,
	kReserved
}
SDFType;

typedef struct SDFEnum_t
{
	char * name;
	uint32_t value;
	uint32_t mask;
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

uint64_t LE2BE64(uint64_t value);
uint32_t LE2BE32(uint32_t value);
uint16_t LE2BE16(uint16_t value);

uint32_t SDFSizeInBytes(const SDFElement * definition);
HSDF SDFCreate(const SDFElement * definition, HREADER hReader);
void SDFPrint(HSDF hSDF);

uint8_t SDFReadUInt8(HSDF hSDF, uint32_t offset);
uint16_t SDFReadUInt16(HSDF hSDF, uint32_t offset);
uint32_t SDFReadUInt32(HSDF hSDF, uint32_t offset);
uint64_t SDFReadUInt64(HSDF hSDF, uint64_t offset);
void SDFSetEndian(HSDF hSDF, uint8_t endian);

void SDFDestroy(HSDF hSDF);

#if defined(_DEBUG) || defined(DEBUG)
#define SDFDebugPrint SDFPrint
#else /* defined(_DEBUG) || defined(DEBUG) */
#define SDFDebugPrint (void)sizeof
#endif /* defined(_DEBUG) || defined(DEBUG) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SDF_H__3C52F878_0BF8_4371_B9E3_E153B9F9487D__ */
