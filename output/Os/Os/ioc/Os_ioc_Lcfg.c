/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc_Lcfg.c
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
*   Genaration Time       : 2026-03-01 08:11:30
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
#include "Os_ioc_Lcfg.h"
#include "Os_kernel_Cfg.h"
#include "common.h"
#include "Os_context_types.h"
#include "Os_spinlock_Cfg.h"
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
**                          Private Function Declarations                                          **
****************************************************************************************************/
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
#define OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"

Os_Hal_ServiceContextFrame Os_Ioc_Core0ToCore1ServiceCallBuffer[OS_IOC_CORE0_TO_CORE1_SERVICECALL_BUFFER_LENGTH];
Os_IocInterCoreServiceCallRunningDataType Os_Ioc_Core0ToCore1ServiceCallRunningData;
Os_IocInterCoreServiceCallParamOutType Os_Ioc_Core0ToCore1ParameterOut[OS_IOC_CORE0_TO_CORE1_SERVICECALL_BUFFER_LENGTH];

Os_Hal_ServiceContextFrame Os_Ioc_Core1ToCore0ServiceCallBuffer[OS_IOC_CORE1_TO_CORE0_SERVICECALL_BUFFER_LENGTH];
Os_IocInterCoreServiceCallRunningDataType Os_Ioc_Core1ToCore0ServiceCallRunningData;
Os_IocInterCoreServiceCallParamOutType Os_Ioc_Core1ToCore0ParameterOut[OS_IOC_CORE1_TO_CORE0_SERVICECALL_BUFFER_LENGTH];

#define OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
static const Os_IocInterCoreServiceChannelCfgType Os_Ioc_Core0ToCore1ServiceChannelCfg =
{
    Os_Ioc_Core0ToCore1ServiceCallBuffer,       /* ServiceContextBuffer */
    OS_IOC_CORE0_TO_CORE1_SERVICECALL_BUFFER_LENGTH,        /* BufferLength */
    &Os_Ioc_Core0ToCore1ServiceCallRunningData,       /* RunningData */
    0UL,                                         /* IntId */
    Os_Ioc_Core0ToCore1ParameterOut
};

static const Os_IocInterCoreServiceChannelCfgType Os_Ioc_Core1ToCore0ServiceChannelCfg =
{
    Os_Ioc_Core1ToCore0ServiceCallBuffer,       /* ServiceContextBuffer */
    OS_IOC_CORE1_TO_CORE0_SERVICECALL_BUFFER_LENGTH,        /* BufferLength */
    &Os_Ioc_Core1ToCore0ServiceCallRunningData,       /* RunningData */
    0UL,                                         /* IntId */
    Os_Ioc_Core1ToCore0ParameterOut
};

const Os_IocInterCoreServiceChannelCfgRefType Os_IocServiceChannelCfgRef[OS_KERNEL_MAX_CORE_NUM] =
{
    /* Physical core0 to other cores channels */
    {
        NULL_PTR,
        &Os_Ioc_Core0ToCore1ServiceChannelCfg
    },
    /* Physical core1 to other cores channels */
    {
        &Os_Ioc_Core1ToCore0ServiceChannelCfg,
        NULL_PTR
    },
};
CONSTP2CONST(Os_IocConfigType, AUTOMATIC, OS_CONST) Os_IocConfigSet[OS_IOC_TOTAL_NUM + 1U] = 
{
    NULL_PTR
};
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
