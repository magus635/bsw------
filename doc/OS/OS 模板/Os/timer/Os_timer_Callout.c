/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timer_callout.c
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


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_GeneralTypes.h"
#include "Os_timer_types.h"
#include "Compiler.h"
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!IF "node:value(./OsResourceSubderivative) != 'Os_SC300'"!][!//
#include "basetimer_hal.h"
[!ENDIF!][!//
[!ENDSELECT!][!//
#include "Os_timer_Callout.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/


/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
#define OS_START_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!IF "node:value(./OsResourceSubderivative) = 'Os_SC300'"!][!//
[!LOOP "node:order(./OsCounter/*,'@index')"!][!//
[!IF "num:i(node:ref(./OsTimerTypeIsrRef)/OsIsrInterruptSource) = 15"!][!//
#define SYSTIMER_CTL_REG        ((volatile uint32*)0xE000E010)
#define SYSTIMER_RELOAD_REG     ((volatile uint32*)0xE000E014)
#define SYSTIMER_COUNTER_REG    ((volatile uint32*)0xE000E018)

FUNC(void, OS_CODE) OsTimer_Hal_[!"node:name(.)"!]Init(uint32 BasePerTick)
{
    [!INDENT "4"!][!//
    *SYSTIMER_RELOAD_REG = BasePerTick;
    //Enable SYSTIMER Interrupt(Bit0) and Decrease to 0 to produce INTC(Bit1).
    *SYSTIMER_CTL_REG = 0x3; /*use extern clk.*/
    [!ENDINDENT!][!//
}

/* Acknowledge Pit interrupt and reload interrupt period for next interrupt.*/
FUNC(void, OS_CODE) OsTimer_Hal_[!"node:name(.)"!]AckAndReloadInterrupt(void)
{
}
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCounter"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
    [!IF "node:value(./OsCounterType) = 'SOFTWARE' or 
    num:i(node:ref(./OsTimerTypeIsrRef)/OsIsrInterruptSource) = 27 or 
    num:i(node:ref(./OsTimerTypeIsrRef)/OsIsrInterruptSource) = 30 or 
    num:i(node:ref(./OsTimerTypeIsrRef)/OsIsrInterruptSource) = 15"!][!//
    [!ELSE!][!//
        FUNC(void, OS_CODE) OsTimer_Hal_[!"node:name(.)"!]Init(uint32 BasePerTick)
        {

        }

        /* Acknowledge Pit interrupt and reload interrupt period for next interrupt.*/
        FUNC(void, OS_CODE) OsTimer_Hal_[!"node:name(.)"!]AckAndReloadInterrupt(void)
        {

        }
    [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

#define OS_STOP_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
