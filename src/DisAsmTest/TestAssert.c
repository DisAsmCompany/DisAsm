/*
* Filename: TestAssert.c
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: test assert declaration
*              
*              
*
*/

#include "TestAssert.h"

void TestAssert(int expression)
{
	if (!expression)
	{
		abort();
	}
}
