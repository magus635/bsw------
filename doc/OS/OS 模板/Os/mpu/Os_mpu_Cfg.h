/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_mpu_Cfg.h
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
#ifndef OS_MPU_CFG_H_
#define OS_MPU_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
/*Max region count to limit the user setting the region number*/
#define MAX_REGION_COUNT   (23U)

#define STACK_REGION_COUNT  (3U)
#define USER_REGION_COUNT  (20U)

/*The Stack region number, which allocate the last three region for stack switch*/
#define OS_MPU_STACK_REGION_PROTECT_ONE      (21U)
#define OS_MPU_CURRENT_STACK_REGION          (22U)
#define OS_MPU_STACK_REGION_PROTECT_TWO      (MAX_REGION_COUNT)

[!INDENT "0"!][!//
[!VAR "TaskIsrMpNum" = "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsTask"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "count(./OsTaskMemoryProtection/*) != 0"!][!//
            [!VAR "TaskIsrMpNum" = "$TaskIsrMpNum + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIsr"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "count(./OsIsrMemoryProtection/*) != 0"!][!//
            [!IF "./OsIsrCategory = 'CATEGORY_2'"!][!//
                [!VAR "TaskIsrMpNum" = "$TaskIsrMpNum + 1"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
#define OS_MPU_COUNT       ([!"num:i($TaskIsrMpNum)"!]U)
[!VAR "TaskIsrAccessNum" = "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
    [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
        [!IF "count(node:ref(.)/OsTaskAccessCheck/*) != 0"!][!//
            [!VAR "TaskIsrAccessNum" = "$TaskIsrAccessNum + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
        [!IF "count(node:ref(.)/OsIsrAccessCheck/*) != 0"!][!//
        [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
            [!VAR "TaskIsrAccessNum" = "$TaskIsrAccessNum + 1"!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
#define OS_MPU_ACCESSCOUNT       ([!"num:i($TaskIsrAccessNum)"!]U)

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsPeripheralArea"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        #define [!"text:toupper(node:name(.))"!]       ([!"num:i(@index)"!]U)
    [!ENDLOOP!][!//
#define OS_PERIPHERALID_COUNT       ([!"num:i(count(./*))"!]U)
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/




#endif /* OS_MPU_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_mpu_Cfg.h                                                                 **
****************************************************************************************************/

