/*
 * Filename: DynamicArray.c
 * Author:   DisAsmCompany
 * Date:     12/11/2013
 *
 * Description: dynamic array implementation
 *
 *
 *
 */

#include "DisAsm"

DynamicArray * DynamicArrayCreate()
{
	DynamicArray * array = (DynamicArray*) calloc(1, sizeof(DynamicArray));
	array->used = 0;
	array->size = 16;
	array->memory = (uint32_t *) calloc(1, array->size * sizeof(uint32_t));
	return array;
}

void DynamicArrayDestroy(DynamicArray * array)
{
	free(array->memory);
	free(array);
}

uint32_t DynamicArraySize(DynamicArray * array)
{
	return array->used;
}

void DynamicArrayAdd(DynamicArray * array, uint32_t value)
{
	uint32_t i = 0;
	for (i = 0; i < array->used; ++i)
	{
		if (array->memory[i] == value)
		{
			return;
		}
	}
	array->memory[array->used] = value;
	if (++array->used == array->size)
	{
		array->size *= 2;
		array->memory = realloc(array->memory, array->size * sizeof(uint32_t));
	}
}

uint32_t DynamicArrayGet(DynamicArray * array, uint32_t index)
{
	return array->memory[index];
}
