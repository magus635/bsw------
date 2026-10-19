/****************************************************************************************************
*   FileName              : Os_Arti_Mock.c
*
*   BSW Module            : Os
*
*   brief                 : Storage of the strict ARTI hook mock (Os_Arti_Mock.h). Compiled to nothing
*                           unless OS_ARTI_USE_MOCK is defined. NOT production code.
****************************************************************************************************/
#if defined(OS_ARTI_USE_MOCK)
#include "Os_Arti_Mock.h"

volatile Os_ArtiMockRecordType Os_ArtiMockLog[OS_ARTI_MOCK_CORES][OS_ARTI_MOCK_DEPTH];
volatile unsigned long Os_ArtiMockCount[OS_ARTI_MOCK_CORES];
volatile unsigned long Os_ArtiMockBadCore;
#endif
