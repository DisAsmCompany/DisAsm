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
#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

typedef struct DynamicArray_t
{
	uint32_t used;
	uint32_t size;
	uint32_t * memory;
}
DynamicArray;

DynamicArray * DynamicArrayCreate();
void DynamicArrayDestroy(DynamicArray * array);
uint32_t DynamicArraySize(DynamicArray * array);
void DynamicArrayAdd(DynamicArray * array, uint32_t value);
uint32_t DynamicArrayGet(DynamicArray * array, uint32_t index);

#endif /* __DYNAMICARRAY_H__ */
