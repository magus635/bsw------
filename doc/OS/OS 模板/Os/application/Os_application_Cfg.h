/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_application_Cfg.h
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
[!//
[!NOCODE!][!//
[!INCLUDE "Os_AppCommon.m"!][!//
[!ENDNOCODE!][!//
[!//
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
#ifndef OS_APPLICATION_CFG_H_
#define OS_APPLICATION_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* This brief the object,application,counter ID mask. */
#define OBJECTID_MASK                        (0x0000FFFFU)
#define APPLICATIONID_MASK                   (0x00FF0000U)
#define COUNTERID_MASK                       (0xFF000000U)
#define COREID_MASK                          (0xFF000000U)
/* This brief the os used application modes */
#define DONOTCARE                   ((AppModeType)0x00000000U)
#define OSDEFAULTAPPMODE            ((AppModeType)0x00000001U)
#define OSALLRUNNINGMODE            ((AppModeType)0xFFFFFFFFU)
#define APPLICATION_COUNTER_INVALID_ID_MASK      (0xFF000000U)


[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsAppMode/*,'@index')"!][!//
        [!VAR "CurrentAppModeMaske"="0"!][!//
        [!VAR "CurrentAppModeMaske"="bit:bitset($CurrentAppModeMaske,@index+1)"!][!//
#define [!"text:toupper(node:name(.))"!]         ((AppModeType)[!"num:inttohex($CurrentAppModeMaske,8)"!])
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//



[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
#define OS_APPLICATION_TOTAL_NUM                 ([!"num:i(count(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*))"!]U)
#define INVALID_OSAPPLICATION                    ([!"num:i(count(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*))"!]U)

    [!VAR "AllApplicationCountNumber"="0"!][!//
    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
#define APPLICATION[!"num:i(@index)"!]_OBJECT_START_NUMBER         ([!"num:i($AllApplicationCountNumber)"!]U)
        [!VAR "CurrentAppObjectCnt"="0"!][!//
        [!VAR "AppID"="num:i(./@index)"!][!//
        [!VAR "IocCbkObjectIDCount"="0"!][!//
        [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
        [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppCounterRef/*) + count(./OsAppScheduleTableRef/*) + num:i($IocCbkObjectIDCount))"!][!//
        [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                [!VAR "CurrentAppObjectCnt" = "$CurrentAppObjectCnt + 1"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                [!VAR "CurrentAppObjectCnt" = "$CurrentAppObjectCnt + 1"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                [!VAR "CurrentAppObjectCnt" = "$CurrentAppObjectCnt + 1"!][!//
            [!ENDIF!][!//
        [!ELSE!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                [!VAR "CurrentAppObjectCnt" = "$CurrentAppObjectCnt + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                [!VAR "CurrentAppObjectCnt" = "$CurrentAppObjectCnt + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                [!VAR "CurrentAppObjectCnt" = "$CurrentAppObjectCnt + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                [!VAR "CurrentAppObjectCnt" = "$CurrentAppObjectCnt + 1"!][!//
            [!ENDIF!][!//
            [!VAR "CurrentAppObjectCnt" = "$CurrentAppObjectCnt + 1"!][!//
        [!ENDIF!][!//
#define APPLICATION[!"num:i(@index)"!]_OBJECTCOUNT_NUMBER          ([!"num:i($CurrentAppObjectCnt)"!]U)
#define CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK                            ([!"num:inttohex(bit:shl(num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId),24),8)"!]U)
#define APPLICATION[!"num:i(@index)"!]_ID_MASK                     ([!"num:inttohex(bit:shl(num:i($AppID),16),8)"!]U)
#define APPLICATION[!"num:i(@index)"!]_ALARM_SCHEDULETABLE_NUMBER  ([!"num:i(count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*))"!]U)
        [!VAR "AllApplicationCountNumber" = "num:i($AllApplicationCountNumber + $CurrentAppObjectCnt)"!][!//


    [!ENDLOOP!][!//


#define TOTALNUM_OF_OBJECT                       ([!"num:i($AllApplicationCountNumber)"!]U)
#define INVAILD_OBJECT_NUMBER                    ([!"num:i($AllApplicationCountNumber)"!]U)
#define TOTALNUM_OF_TRUSTEDFUNC                  (2U)

    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
        #define [!"text:toupper(node:name(.))"!]                          ([!"num:i(@index)"!]U)
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//


[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsCounter/*,'@index')"!][!//
#define APPLICATION_COUNTER[!"num:i(@index)"!]_ID_MASK             ([!"num:inttohex(bit:shl(num:i(@index),24),8)"!]U)
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/


#endif /* OS_APPLICATION_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_application_Cfg.h                                                           **
****************************************************************************************************/

