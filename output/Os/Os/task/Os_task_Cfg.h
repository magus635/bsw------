/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_task_Cfg.h
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
*   Genaration Time       : 2026-03-05 20:16:16
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
#ifndef OS_TASK_CFG_H_
#define OS_TASK_CFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/


/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define OSEVENT_0               (1U)
#define OSEVENT_1               (2U)
#define OSEVENT_2               (4U)
#define OSEVENT_3               (8U)
#define OSEVENT_4               (16U)
#define IDLE_TASK_CORE0        (TaskType)(0U)
#define IDLE_TASK_CORE1        (TaskType)(1U)
#define TASK1        (TaskType)(2U)
#define TASK2        (TaskType)(3U)
#define TASK3        (TaskType)(4U)
#define TASK4        (TaskType)(5U)
#define TASK5        (TaskType)(6U)
#define TASK6        (TaskType)(7U)
#define TASK7        (TaskType)(8U)
#define DEFAULT_INIT_TASK        (TaskType)(9U)
#define DEFAULT_INIT_TASK_CORE1        (TaskType)(10U)
#define TASK0_CORE1        (TaskType)(11U)
#define TASK8        (TaskType)(12U)
#define TASK9_CORE1        (TaskType)(13U)
#define TASK10_CORE1        (TaskType)(14U)
#define TASK11_CORE1        (TaskType)(15U)
#define TASK12_CORE1        (TaskType)(16U)
#define TASK13_CORE1        (TaskType)(17U)
#define TASK14_CORE1        (TaskType)(18U)
#define TASK15_CORE1        (TaskType)(19U)
#define TASK16        (TaskType)(20U)
#define TASK17        (TaskType)(21U)
#define TASK18        (TaskType)(22U)
#define TASK19        (TaskType)(23U)
#define TASK20        (TaskType)(24U)
#define TOTAL_TASK_NUM      (TaskType)(25)
#define INVALID_TASK        TOTAL_TASK_NUM

#define PRIORITY0_CORE0_QUEUESIZE                           (2U)
#define PRIORITY1_CORE0_QUEUESIZE                           (6U)
#define PRIORITY2_CORE0_QUEUESIZE                           (2U)
#define PRIORITY3_CORE0_QUEUESIZE                           (102U)
#define PRIORITY4_CORE0_QUEUESIZE                           (5U)
#define PRIORITY5_CORE0_QUEUESIZE                           (2U)
#define PRIORITY6_CORE0_QUEUESIZE                           (2U)
#define PRIORITY7_CORE0_QUEUESIZE                           (2U)
#define PRIORITY8_CORE0_QUEUESIZE                           (2U)
#define TASK_CORE0_TOTAL_PRIORITY                           (9U)

#define PRIORITY0_CORE1_QUEUESIZE                           (2U)
#define PRIORITY1_CORE1_QUEUESIZE                           (3U)
#define PRIORITY2_CORE1_QUEUESIZE                           (3U)
#define PRIORITY3_CORE1_QUEUESIZE                           (3U)
#define PRIORITY4_CORE1_QUEUESIZE                           (2U)
#define PRIORITY5_CORE1_QUEUESIZE                           (3U)
#define PRIORITY6_CORE1_QUEUESIZE                           (2U)
#define TASK_CORE1_TOTAL_PRIORITY                           (7U)

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/




#endif /* OS_TASK_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_task_Cfg.h                                                                 **
****************************************************************************************************/

