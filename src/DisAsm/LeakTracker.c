/*
 * Filename: LeakTracker.h
 * Author:   DisAsmCompany
 * Date:     11/11/2013
 *
 * Description: memory leaks tracker
 *
 *
 *
 */

#include "DisAsm"

typedef void * (__stdcall * pfnHeapAlloc)(void * hHeap, uint32_t flags, uint32_t size);
typedef void * (__stdcall * pfnHeapReAlloc)(void * hHeap, uint32_t flags, void * memory, uint32_t size);
typedef int (__stdcall * pfnHeapFree)(void * hHeap, uint32_t flags, LPVOID lpMem);

static pfnHeapAlloc pOriginalHeapAlloc = NULL;
static pfnHeapReAlloc pOriginalHeapReAlloc = NULL;
static pfnHeapFree pOriginalHeapFree = NULL;

#define PAGE_SIZE 4096
#define THUNK_SIZE 20
uint8_t xThunkHeapAlloc[2 * THUNK_SIZE], xThunkHeapReAlloc[2 * THUNK_SIZE], xThunkHeapFree[2 * THUNK_SIZE];

typedef struct Allocation_t
{
	void * address;
	uint32_t size;
	uint8_t freed;
}
Allocation;

static size_t g_nActiveAllocations = 0;
static size_t g_nTotalAllocations = 0;
static size_t g_nCapacity = 0;

Allocation * g_Allocations = NULL;

static bool xHeapCalled = false;

uint32_t xFindAllocation(void * address)
{
	uint32_t i = 0;
	for (i = 0; i < g_nTotalAllocations; ++i)
	{
		if (g_Allocations[i].address == address)
		{
			return i;
		}
	}
	return 0xFFFFFFFFUL;
}

void xAddAllocation(void * address, uint32_t size, uint8_t freed)
{
	++g_nActiveAllocations;
	++g_nTotalAllocations;
	if (g_nTotalAllocations >= g_nCapacity)
	{
		g_nCapacity += 1024; /* linear grow */
		g_Allocations = (Allocation*) pOriginalHeapReAlloc(GetProcessHeap(), 0, g_Allocations, g_nCapacity * sizeof(Allocation));
		if (!g_Allocations)
		{
			__asm int 3;
		}
	}
	g_Allocations[g_nTotalAllocations - 1].address = address;
	g_Allocations[g_nTotalAllocations - 1].size    = size;
	g_Allocations[g_nTotalAllocations - 1].freed   = false;
}

void xUpdateAllocation(void * address, uint32_t size, uint8_t freed)
{
	size_t index = xFindAllocation(address);
	if (0xFFFFFFFFUL != index)
	{
		g_Allocations[index].address = address;
		g_Allocations[index].size    = freed ? g_Allocations[index].size : size;
		g_Allocations[index].freed   = freed;
	}
	else
	{
		xAddAllocation(address, size, freed);
		if (freed) --g_nActiveAllocations;
	}
}

void * __stdcall xHeapAlloc(void * hHeap, uint32_t flags, uint32_t size)
{
	void * result = NULL;
	if (xHeapCalled)
	{
		return pOriginalHeapAlloc(hHeap, flags, size);
	}
	xHeapCalled = true;
	result = pOriginalHeapAlloc(hHeap, flags, size);
	if (NULL != result)
	{
		xAddAllocation(result, size, false);
	}
	xHeapCalled = false;
	return result;
}

void * __stdcall xHeapReAlloc(void * hHeap, uint32_t flags, void * memory, uint32_t size)
{
	void * result = NULL;
	if (xHeapCalled)
	{
		return pOriginalHeapReAlloc(hHeap, flags, memory, size);
	}
	xHeapCalled = true;
	result = pOriginalHeapReAlloc(hHeap, flags, memory, size);
	if (NULL != result)
	{
		if (result == memory) 
		{
			/* same address, just update it */
			xUpdateAllocation(result, size, false);
		}
		else
		{
			xUpdateAllocation(memory, 0, true);
			xAddAllocation(result, size, false);
		}
	}
	xHeapCalled = false;
	return result;
}

int __stdcall xHeapFree(void * hHeap, uint32_t flags, void * memory)
{
	int result = 0;
	if (xHeapCalled)
	{
		return pOriginalHeapFree(hHeap, flags, memory);
	}
	xHeapCalled = true;
	result = pOriginalHeapFree(hHeap, flags, memory);
	if (result)
	{
		xUpdateAllocation(memory, 0, true);
	}
	xHeapCalled = false;
	return result;
}

uint32_t CalculateOffsetForJMP(uint32_t from, uint32_t to)
{
	/* 5 is size of JMP instruction itself */
	return to - from - 5;
}

uint32_t PatchLength(uint32_t * pData)
{
	HDISASM hDisAsm = DisAsmCreate(32);
	HREADER hReader = MemoryReaderCreate(pData, PAGE_SIZE);
	uint32_t total = 0;
	while (total < 5)
	{
		uint32_t length = DisAsmInstructionDecode(hDisAsm, hReader, NULL);
		if (0 == length)
		{
			return 0;
		}
		total += length;
	}
	DisAsmDestroy(hDisAsm);
	ReaderDestroy(hReader);
	return total;
}

void PatchFunction(uint8_t * pOriginal, uint8_t * pHook, uint8_t * pThunk)
{
	/* OpCode for NOP (No Operation - instruction that does nothing) */
	uint8_t NOP = 0x90;
	/* OpCode for JMP (Jump) */
	uint8_t JMP = 0xE9;
	uint32_t protect = 0;
	uint32_t offset = CalculateOffsetForJMP((uint32_t)pOriginal, (uint32_t)pHook);

	uint32_t length = PatchLength(pOriginal);
	
	memset(pThunk, NOP, 2 * THUNK_SIZE);
	memcpy(pThunk, pOriginal, length);

	VirtualProtect(pOriginal, PAGE_SIZE, PAGE_READWRITE, &protect);
	pOriginal[0] = JMP;
	memcpy(pOriginal + 1, &offset, 4);
	memset(pOriginal + 5, NOP, length - 5);
	VirtualProtect(pOriginal, PAGE_SIZE, protect, &protect);

	offset = CalculateOffsetForJMP(pThunk + THUNK_SIZE, pOriginal + length);
	pThunk[THUNK_SIZE] = JMP;
	memcpy(pThunk + THUNK_SIZE + 1, &offset, 4);

	
}

void RestoreFunction(uint8_t * pOriginal, uint8_t * pThunk)
{
	uint32_t protect = 0;
	uint32_t length = PatchLength(pThunk);

	VirtualProtect(pOriginal, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
	memcpy(pOriginal, pThunk, length);
	VirtualProtect(pOriginal, PAGE_SIZE, protect, &protect);
}

void LeakTrackerInstall(uint8_t install)
{
	uint32_t protect = 0;

	if (install)
	{
		g_Allocations = (Allocation*)HeapAlloc(GetProcessHeap(), 0, sizeof(Allocation));

		pOriginalHeapAlloc   = (pfnHeapAlloc)  (&xThunkHeapAlloc);
		pOriginalHeapReAlloc = (pfnHeapReAlloc)(&xThunkHeapReAlloc);
		pOriginalHeapFree    = (pfnHeapFree)   (&xThunkHeapFree);

		VirtualProtect(xThunkHeapAlloc,   PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
		VirtualProtect(xThunkHeapReAlloc, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);
		VirtualProtect(xThunkHeapFree,    PAGE_SIZE, PAGE_EXECUTE_READWRITE, &protect);

		PatchFunction((uint8_t*)HeapReAlloc, (uint8_t*)xHeapReAlloc, xThunkHeapReAlloc);
		PatchFunction((uint8_t*)HeapAlloc,   (uint8_t*)xHeapAlloc,   xThunkHeapAlloc);
		PatchFunction((uint8_t*)HeapFree,    (uint8_t*)xHeapFree,    xThunkHeapFree);
	}
	else
	{
		uint32_t i = 0;
		uint32_t total = 0;

		RestoreFunction((uint8_t*)HeapAlloc,   xThunkHeapAlloc);
		RestoreFunction((uint8_t*)HeapReAlloc, xThunkHeapReAlloc);
		RestoreFunction((uint8_t*)HeapFree,    xThunkHeapFree);

		for (i = 0; i < g_nTotalAllocations; ++i)
		{
			if (0 == g_Allocations[i].freed)
			{
				total += g_Allocations[i].size;
				printf("memory leak 0x%04X of %d bytes\n", g_Allocations[i].address, g_Allocations[i].size);
			}
		}
		printf("total leaked %d bytes\n", total);
	}
}
