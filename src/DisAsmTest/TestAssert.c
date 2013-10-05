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

#include "../DisAsm/DisAsm"
#include "../StrAsm/StrAsm"
#include "../Executable/Executable"

#include "TestAssert.h"

void TestAssert(int expression)
{
	if (!expression)
	{
		abort();
	}
}
