/*
 * Filename: DynamicArray.h
 * Author:   DisAsmCompany
 * Date:     12/11/2013
 *
 * Description: dynamic array implementation
 *
 *
 *
 */

#pragma once
#ifndef __DYNAMICARRAY_H__32942D11_0BA1_4000_8CAA_C74E4149A978__
#define __DYNAMICARRAY_H__32942D11_0BA1_4000_8CAA_C74E4149A978__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct DynamicArray_t
{
	uint32_t used;
	uint32_t size;
	uint64_t * memory;
}
DynamicArray;

DynamicArray * DynamicArrayCreate();
void DynamicArrayDestroy(DynamicArray * array);
uint32_t DynamicArraySize(DynamicArray * array);
void DynamicArrayAdd(DynamicArray * array, uint64_t value);
uint64_t DynamicArrayGet(DynamicArray * array, uint64_t index);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DYNAMICARRAY_H__32942D11_0BA1_4000_8CAA_C74E4149A978__ */
