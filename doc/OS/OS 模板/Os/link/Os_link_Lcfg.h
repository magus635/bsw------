/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_link_Lcfg.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Genaration Time       : [!"$datetime"!]
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_LINK_LCFG_H_
#define OS_LINK_LCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsResourceSubderivative) = 'Os_THA6206'"!][!//
#include "Compiler.h"
#include "Os_kernel_Cfg.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/*used for clone bss sections.*/
extern const Os_LinkBssMemGroupCfg Os_MemZeroInit_StageOne;
/*used for common bss sections.*/
extern const Os_LinkBssMemGroupCfg Os_MemZeroInit_StageTwo;
/*used for private bss sections.*/
extern const Os_LinkBssMemGroupCfg Os_MemZeroInit_StageThree;
/*used for unclear bss sections.*/
extern const Os_LinkBssMemGroupCfg Os_MemZeroInit_Unclear;
/*used for system stack setting.*/
extern const Os_LinkStackCfg Os_MemStackInit[2];
/*used for clone data/code sections.*/
extern const Os_LinkDataMemGroupCfg Os_MemDataInit_StageOne;
/*used for common data/code sections.*/
extern const Os_LinkDataMemGroupCfg Os_MemDataInit_StageTwo;
/*used for private data/code sections.*/
extern const Os_LinkDataMemGroupCfg Os_MemDataInit_StageThree;

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
[!ENDIF!][!//
#endif /* OS_LINK_LCFG_H_ */

/****************************************************************************************************
**     End of File: Os_link_Lcfg.h                                                                **
****************************************************************************************************/

