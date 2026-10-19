/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_spinlock_Cfg.h
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
#ifndef OS_SPINLOCK_CFG_H_
#define OS_SPINLOCK_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsSpinlock/*,'num:i(@index)')"!][!//
    #define [!"text:toupper(node:name(.))"!]        (SpinlockIdType)([!"@index"!])
[!ENDLOOP!][!//
[!VAR "UserSpinlockNum" = "num:i(count(./OsSpinlock/*))"!][!//
[!VAR "IocSpinlockNum" = "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
    [!VAR "CurrentIocName" = "node:name(.)"!][!//
    [!VAR "IocSpinlockIsNeeded" = "'false'"!][!//
    [!VAR "SenderCoreId" = "0"!][!//
    [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
        [!IF "@index = 0"!][!//
            [!VAR "SenderCoreId" = "node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
        [!ELSE!][!//
            [!IF "$SenderCoreId != node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!VAR "IocSpinlockNum" = "$IocSpinlockNum + 1"!][!//
                [!VAR "IocSpinlockIsNeeded" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$IocSpinlockIsNeeded = 'false'"!][!//
        [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
            [!IF "$SenderCoreId != node:ref(node:ref(OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!VAR "IocSpinlockNum" = "$IocSpinlockNum + 1"!][!//
                [!VAR "IocSpinlockIsNeeded" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
    [!IF "$IocSpinlockIsNeeded = 'true'"!][!//
#define [!"text:toupper($CurrentIocName)"!]_SPINLOCK         ([!"num:i($UserSpinlockNum + $IocSpinlockNum - 1)"!]UL)
    [!ENDIF!][!//
[!ENDLOOP!][!//
#define STARTUP_SYN_SPINLOCK            ([!"num:i($UserSpinlockNum + $IocSpinlockNum)"!]UL)
#define SHUTDOWN_SYN_SPINLOCK           ([!"num:i($UserSpinlockNum + $IocSpinlockNum + 1)"!]UL)

#define OS_SPINLOCK_USER_CFG_NUM        ([!"num:i($UserSpinlockNum)"!]UL)
#define Os_INTERNAL_SPINLOCK_CFG_NUM    ([!"num:i($IocSpinlockNum + 2)"!]UL)
#define OS_SPINLOCK_TOTAL_NUM           (OS_SPINLOCK_USER_CFG_NUM + Os_INTERNAL_SPINLOCK_CFG_NUM)
#define OS_INVALID_SPINLOCK             (OS_SPINLOCK_TOTAL_NUM)
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




#endif /* OS_SPINLOCK_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_spinlock_Cfg.h                                                              **
****************************************************************************************************/

