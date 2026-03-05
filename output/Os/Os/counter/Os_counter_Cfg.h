/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_counter_Cfg.h
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
*   Genaration Time       : 2026-03-05 20:04:59
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
#ifndef OS_COUNTER_CFG_H_
#define OS_COUNTER_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "common.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define   OS_CFG_COUNTER_SOFTWARE_USED           (STD_ON)
#define   OS_CFG_COUNTER_HRTTIMER_USED           (STD_ON)
#define   OS_CFG_COUNTER_FRTTIMER_USED           (STD_ON)
#define   OS_CFG_COUNTER_PITTIMER_USED           (STD_ON)
#define   OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE_OBJECTS    (1u)
#define   OS_CFG_COUNTER_NUM_OSCOUNTER_SYSTEMTICK_OBJECTS    (3u)
#define   OS_CFG_COUNTER_NUM_OSCOUNTER_HRT_OBJECTS    (0u)
#define   OS_CFG_COUNTER_NUM_OSCOUNTER_PIT_OBJECTS    (1u)
#define   OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE2_OBJECTS    (3u)
#define   OS_CFG_COUNTER_NUM_OSCOUNTER_SYSTEMTICK_CORE1_OBJECTS    (2u)
#define   OS_CFG_COUNTER_NUM_OSCOUNTER_HRT_CORE1_OBJECTS    (0u)
#define   OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE_CORE1_OBJECTS    (2u)
#define   OSCOUNTER_SOFTWARE                            (0u)
#define   OSCOUNTER_SYSTEMTICK                            (1u)
#define   OSCOUNTER_HRT                            (2u)
#define   OSCOUNTER_PIT                            (3u)
#define   OSCOUNTER_SOFTWARE2                            (4u)
#define   OSCOUNTER_SYSTEMTICK_CORE1                            (5u)
#define   OSCOUNTER_HRT_CORE1                            (6u)
#define   OSCOUNTER_SOFTWARE_CORE1                            (7u)
#define   OS_COUNTER_TOTAL_NUM                   (8u)
#define   INVALID_COUNTER                        OS_COUNTER_TOTAL_NUM

#define   OS_COUNTER_MAX_OBJECT_EXECS_PER_LOCK   (4u)

#define OS_TICKS2NS_OsCounter_SystemTick(x)   ((uint32)(((((uint32)(x)) * 1000000) + 0) / 1))
#define OS_TICKS2US_OsCounter_SystemTick(x)   ((uint32)(((((uint32)(x)) * 1000) + 0) / 1))
#define OS_TICKS2MS_OsCounter_SystemTick(x)   ((uint32)(((((uint32)(x)) * 1) + 0) / 1))
#define OS_TICKS2SEC_OsCounter_SystemTick(x)   ((uint32)(((((uint32)(x)) * 1) + 500) / 1000))

#define OS_TICKS2NS_OsCounter_Hrt(x)   ((uint32)(((((uint32)(x)) * 40) + 0) / 1))
#define OS_TICKS2US_OsCounter_Hrt(x)   ((uint32)(((((uint32)(x)) * 4) + 50) / 100))
#define OS_TICKS2MS_OsCounter_Hrt(x)   ((uint32)(((((uint32)(x)) * 4) + 50000) / 100000))
#define OS_TICKS2SEC_OsCounter_Hrt(x)   ((uint32)(((((uint32)(x)) * 0) + 500000) / 1000000))

#define OS_TICKS2NS_OsCounter_Pit(x)   ((uint32)(((((uint32)(x)) * 1000000) + 0) / 1))
#define OS_TICKS2US_OsCounter_Pit(x)   ((uint32)(((((uint32)(x)) * 1000) + 0) / 1))
#define OS_TICKS2MS_OsCounter_Pit(x)   ((uint32)(((((uint32)(x)) * 1) + 0) / 1))
#define OS_TICKS2SEC_OsCounter_Pit(x)   ((uint32)(((((uint32)(x)) * 1) + 500) / 1000))

#define OS_TICKS2NS_OsCounter_SystemTick_Core1(x)   ((uint32)(((((uint32)(x)) * 1000000) + 0) / 1))
#define OS_TICKS2US_OsCounter_SystemTick_Core1(x)   ((uint32)(((((uint32)(x)) * 1000) + 0) / 1))
#define OS_TICKS2MS_OsCounter_SystemTick_Core1(x)   ((uint32)(((((uint32)(x)) * 1) + 0) / 1))
#define OS_TICKS2SEC_OsCounter_SystemTick_Core1(x)   ((uint32)(((((uint32)(x)) * 1) + 500) / 1000))

#define OS_TICKS2NS_OsCounter_Hrt_Core1(x)   ((uint32)(((((uint32)(x)) * 40) + 0) / 1))
#define OS_TICKS2US_OsCounter_Hrt_Core1(x)   ((uint32)(((((uint32)(x)) * 4) + 50) / 100))
#define OS_TICKS2MS_OsCounter_Hrt_Core1(x)   ((uint32)(((((uint32)(x)) * 4) + 50000) / 100000))
#define OS_TICKS2SEC_OsCounter_Hrt_Core1(x)   ((uint32)(((((uint32)(x)) * 0) + 500000) / 1000000))


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




#endif /* OS_COUNTER_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_counter_Cfg.h                                                               **
****************************************************************************************************/

