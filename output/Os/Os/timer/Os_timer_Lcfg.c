/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timer_Lcfg.c
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
*   Genaration Time       : 2026-03-05 20:16:18
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
#include "Os_timer_Lcfg.h"
#include "Os_timer_hal.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Type Definitions                                                **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Structure Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_TimerHrtRunningDataType OsTimer_Hal_OsCounter_HrtRunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_TimerHrtRunningDataType OsTimer_Hal_OsCounter_Hrt_Core1RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_TimerHrtRunningDataType OsTimer_Hal_OsCounter_HrtRunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_TimerHrtRunningDataType OsTimer_Hal_OsCounter_Hrt_Core1RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
const Os_TimerFrtHwConfigType OsTimer_Hal_OsCounter_SystemTickHwCfg =
{
    OsTimer_Hal_EL1PhyTimerInit,                   /* Init */
    OsTimer_Hal_EL1PhyTimerAckInterrupt,           /* AckInterrupt */
    OsTimer_Hal_EL1PhyTimerGetCounterRegValue,     /* GetCounterRegValue  */
    OsTimer_Hal_EL1PhyTimerGetCompareRegValue,     /* GetCompareRegValue  */ 
    OsTimer_Hal_EL1PhyTimerSetCompareRegValue,     /* SetCompareRegValue  */
    30ul,                                          /* IsrID */
    25000ul,                                       /* Period */
    0x7FFFFFFFFFFFFFFFul,                          /* MaxCounterRegisterValue */
    0x7FFFFFFFul                                   /* MaxDifferenceValue */
};
const Os_TimerHrtHwConfigType OsTimer_Hal_OsCounter_HrtHwCfg =
{
    OsTimer_Hal_EL1VirtTimerInit,                   /* Init */
    OsTimer_Hal_EL1VirtTimerAckInterrupt,           /* AckInterrupt */
    OsTimer_Hal_EL1VirtTimerGetCounterRegValue,     /* GetCounterRegValue  */
    OsTimer_Hal_EL1VirtTimerGetCompareRegValue,     /* GetCompareRegValue  */ 
    OsTimer_Hal_EL1VirtTimerSetCompareRegValue,     /* SetCompareRegValue  */
    27ul,                                           /* IsrID */
    0x7FFFFFFFFFFFFFFFul,                           /* MaxCounterRegisterValue */
    0x7FFFFFFFul,                                   /* MaxDifferenceValue */
    &OsTimer_Hal_OsCounter_HrtRunningData      /* RunningData */
};
const Os_TimerPitHwConfigType OsTimer_Hal_OsCounter_PitHwCfg =
{
    OsTimer_Hal_OsCounter_PitInit,                       /* Init */
    OsTimer_Hal_OsCounter_PitAckAndReloadInterrupt,  /* PitAckAndReloadInterrupt  */ 
    246ul,                            /* IsrID */
    100000ul                       /* Period */
};        
const Os_TimerFrtHwConfigType OsTimer_Hal_OsCounter_SystemTick_Core1HwCfg =
{
    OsTimer_Hal_EL1PhyTimerInit,                   /* Init */
    OsTimer_Hal_EL1PhyTimerAckInterrupt,           /* AckInterrupt */
    OsTimer_Hal_EL1PhyTimerGetCounterRegValue,     /* GetCounterRegValue  */
    OsTimer_Hal_EL1PhyTimerGetCompareRegValue,     /* GetCompareRegValue  */ 
    OsTimer_Hal_EL1PhyTimerSetCompareRegValue,     /* SetCompareRegValue  */
    30ul,                                          /* IsrID */
    25000ul,                                       /* Period */
    0x7FFFFFFFFFFFFFFFul,                          /* MaxCounterRegisterValue */
    0x7FFFFFFFul                                   /* MaxDifferenceValue */
};
const Os_TimerHrtHwConfigType OsTimer_Hal_OsCounter_Hrt_Core1HwCfg =
{
    OsTimer_Hal_EL1VirtTimerInit,                   /* Init */
    OsTimer_Hal_EL1VirtTimerAckInterrupt,           /* AckInterrupt */
    OsTimer_Hal_EL1VirtTimerGetCounterRegValue,     /* GetCounterRegValue  */
    OsTimer_Hal_EL1VirtTimerGetCompareRegValue,     /* GetCompareRegValue  */ 
    OsTimer_Hal_EL1VirtTimerSetCompareRegValue,     /* SetCompareRegValue  */
    27ul,                                           /* IsrID */
    0x7FFFFFFFFFFFFFFFul,                           /* MaxCounterRegisterValue */
    0x7FFFFFFFul,                                   /* MaxDifferenceValue */
    &OsTimer_Hal_OsCounter_Hrt_Core1RunningData      /* RunningData */
};
/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/





