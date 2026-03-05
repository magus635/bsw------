/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_kernel_Cfg.h
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
*   Genaration Time       : 2026-03-05 20:05:05
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
#ifndef OS_KERNEL_CFG_H_
#define OS_KERNEL_CFG_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/


#define OS_CORE_ID_0                                ((CoreIdType)0)
#define OS_CORE_ID_1                                ((CoreIdType)1)
#define OS_KERNEL_CORE0_APPLICATION_COUNT_NUMBER                ((uint32)3)
#define OS_KERNEL_CORE0_APPLICATION_START_NUMBER                ((uint32)0)
#define OS_KERNEL_CORE0_CONTEXT_COUNT_NUMBER                    ((uint32)24)   
#define OS_KERNEL_CORE0_CONTEXT_START_NUMBER                    ((uint32)0)
#define OS_KERNEL_CORE0_TPOBJECT_COUNT_NUMBER                   ((uint32)5)
#define OS_KERNEL_CORE0_TPOBJECT_START_NUMBER                   ((uint32)0)
#define OS_KERNEL_CORE0_TPOBJECT_USED_COUNTERID                 ((uint32)2)
#define OS_KERNEL_CORE0_MPU_CORE_REGION_MAX_NUMBER              ((uint32)2) 
#define OS_KERNEL_CORE0_MPU_APP_REGION_MAX_NUMBER               ((uint32)2)  
#define OS_KERNEL_CORE0_MPU_OBJECT_REGION_MAX_NUMBER            ((uint32)1)
#define OS_KERNEL_CORE0_STARTOS_INITFUNCTION_OBJECT_NUMBER      ((uint32)29)
#define OS_KERNEL_CORE0_KERNEL_APPLICATION_NUMBER               ((uint32)0)
#define OS_KERNEL_CORE0_RESOURCE_COUNT_NUMBER                   ((uint32)3)
#define OS_KERNEL_CORE0_RESOURCE_START_NUMBER                   ((uint32)0)

#define OS_KERNEL_CORE1_APPLICATION_COUNT_NUMBER                ((uint32)1)
#define OS_KERNEL_CORE1_APPLICATION_START_NUMBER                ((uint32)3)
#define OS_KERNEL_CORE1_CONTEXT_COUNT_NUMBER                    ((uint32)17)   
#define OS_KERNEL_CORE1_CONTEXT_START_NUMBER                    ((uint32)24)
#define OS_KERNEL_CORE1_TPOBJECT_COUNT_NUMBER                   ((uint32)2)
#define OS_KERNEL_CORE1_TPOBJECT_START_NUMBER                   ((uint32)5)
#define OS_KERNEL_CORE1_TPOBJECT_USED_COUNTERID                 ((uint32)6)
#define OS_KERNEL_CORE1_MPU_CORE_REGION_MAX_NUMBER              ((uint32)1) 
#define OS_KERNEL_CORE1_MPU_APP_REGION_MAX_NUMBER               ((uint32)0)  
#define OS_KERNEL_CORE1_MPU_OBJECT_REGION_MAX_NUMBER            ((uint32)0)
#define OS_KERNEL_CORE1_STARTOS_INITFUNCTION_OBJECT_NUMBER      ((uint32)60)
#define OS_KERNEL_CORE1_KERNEL_APPLICATION_NUMBER               ((uint32)3)
#define OS_KERNEL_CORE1_RESOURCE_COUNT_NUMBER                   ((uint32)2)
#define OS_KERNEL_CORE1_RESOURCE_START_NUMBER                   ((uint32)3)


#define OS_CORE_ID_MASTER                     ()
#define OS_KERNEL_MAX_CORE_NUM                (U)
#define OS_KERNEL_TOTAL_USED_NUM              (0UL)
#define OS_CORE_ID_INVAILD_NUM                ((CoreIdType)0)
#define OS_KERNEL_COMBINE_COREID_MASK         ((uint32)0x00000003)

#define OS_KERNEL_SUPPORT_SC2
#define OS_KERNEL_SUPPORT_SC3
#define OS_STATUS_EXTENDED          (STD_ON)
#define OS_STATUS_USEARTI           (STD_OFF)
#define OS_SERVICE_PROTECTION          (STD_OFF)

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


#endif /* OS_KERNEL_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_kernel_Cfg.h                                                                 **
****************************************************************************************************/


