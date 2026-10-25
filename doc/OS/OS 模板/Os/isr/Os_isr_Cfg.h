/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_isr_Cfg.h
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
#ifndef OS_ISR_CFG_H_
#define OS_ISR_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
#define [!"text:toupper(OsResourceSubderivative)"!]
[!IF "node:value(./OsResourceSubderivative) != 'Os_SC300'"!][!//
#define GICv3(x)              ((GIC_MODULE*)(Os_IsrGICAddr[x]))
[!ENDIF!][!//
/* Trigger methods of interrupt */
#define OS_ISR_TRIGGERMETHOD_LEVEL (0U)
#define OS_ISR_TRIGGERMETHOD_EDGE  (1U)
/* Identification of two kinds of interrupt */
#define OS_ISR_INTERRUPTGROUP_FIQ  (0U)
#define OS_ISR_INTERRUPTGROUP_IRQ  (1U)

[!IF "node:value(./OsResourceSubderivative) = 'Os_SC300'"!][!//
#define OS_ISR_SPI_TOTAL_NUM            (73U)
#define OS_ISR_INTERNALINT_TOTAL_NUM    (16U)
[!ELSE!][!//
#define OS_ISR_SPI_TOTAL_NUM            (960U)
#define OS_ISR_INTERNALINT_TOTAL_NUM    (32U)
[!ENDIF!][!//

[!VAR "TpIsrName" = "','"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
    [!IF "node:exists(./OsTpCounterRef)"!][!//
        [!VAR "TpIsrName" = "concat($TpIsrName, ',', node:name(node:ref(node:ref(OsTpCounterRef)/OsTimerTypeIsrRef)))"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!LOOP "node:order(./OsIsr/*,'@index')"!][!//
    [!IF "OsIsrCategory = 'CATEGORY_2'"!][!//
        #define [!"text:toupper(node:name(.))"!]        (ISRType)([!"@index"!])
    [!ENDIF!][!//
[!ENDLOOP!][!//

#define OS_ISR_TOTAL_NUM    ([!"num:i(count(./OsIsr/*))"!]U)
#define INVALID_ISR  OS_ISR_TOTAL_NUM
/* ISR1 interrupt disable level, except tp interrupt */
#define OS_ISR_CAT1_DISABLE_LEVEL   ([!//
[!VAR "HighestPriority"="32"!][!//
[!LOOP "node:order(./OsIsr/*,'num:i(@index)')"!][!//
    [!IF "not(contains($TpIsrName, node:name(.)))"!][!//
        [!IF "OsIsrPriority < $HighestPriority"!][!//
            [!VAR "HighestPriority"="OsIsrPriority"!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!"num:i($HighestPriority)"!][!//
UL)
/* ISR2 interrupt disable level */
#define OS_ISR_CAT2_DISABLE_LEVEL   ([!//
[!VAR "HighestPriority"="32"!][!//
[!LOOP "node:order(./OsIsr/*,'num:i(@index)')"!][!//
    [!IF "(OsIsrCategory = 'CATEGORY_2') and not(contains($TpIsrName, node:name(.)))"!][!//
        [!IF "OsIsrPriority < $HighestPriority"!][!//
            [!VAR "HighestPriority"="OsIsrPriority"!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!"num:i($HighestPriority)"!][!//
UL)
/* ISR1 interrupt disable level, including tp interrupt */
#define OS_ISR_TP_DISABLE_LEVEL     ([!//
[!VAR "HighestPriority"="32"!][!//
[!LOOP "node:order(./OsIsr/*,'num:i(@index)')"!][!//
    [!IF "$TpIsrName = ','"!][!//
        [!IF "OsIsrPriority < $HighestPriority"!][!//
            [!VAR "HighestPriority"="OsIsrPriority"!][!//
        [!ENDIF!][!//
    [!ELSE!][!//
        [!IF "contains($TpIsrName, node:name(.))"!][!//
            [!IF "OsIsrPriority < $HighestPriority"!][!//
                [!VAR "HighestPriority"="OsIsrPriority"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!"num:i($HighestPriority)"!][!//
UL)
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




#endif /* OS_ISR_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_isr_Cfg.h                                                                 **
****************************************************************************************************/

