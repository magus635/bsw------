/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_counter_Lcfg.c
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


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_counter_types.h"
#include "Os_timer_Lcfg.h"
#include "Os_counter_Cfg.h"
#include "Os_counter_Lcfg.h"
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

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_CounterRunningDataType    OsCounter_SoftwareRunningData;
static Os_CounterNodeQueueDataType  OsCounter_SoftwareNodeQueueData[OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE_OBJECTS + 1];
static Os_CounterNodeQueueType      OsCounter_SoftwareNodeQueue;
static Os_CounterFrtRunningDataType  OsCounter_SystemTickRunningData;
static Os_CounterNodeQueueDataType  OsCounter_SystemTickNodeQueueData[OS_CFG_COUNTER_NUM_OSCOUNTER_SYSTEMTICK_OBJECTS + 1];
static Os_CounterNodeQueueType      OsCounter_SystemTickNodeQueue;
static Os_CounterNodeQueueDataType  OsCounter_HrtNodeQueueData[OS_CFG_COUNTER_NUM_OSCOUNTER_HRT_OBJECTS + 1];
static Os_CounterNodeQueueType      OsCounter_HrtNodeQueue;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_CounterRunningDataType    OsCounter_Software2RunningData;
static Os_CounterNodeQueueDataType  OsCounter_Software2NodeQueueData[OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE2_OBJECTS + 1];
static Os_CounterNodeQueueType      OsCounter_Software2NodeQueue;
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_CounterRunningDataType  OsCounter_PitRunningData;
static Os_CounterNodeQueueDataType  OsCounter_PitNodeQueueData[OS_CFG_COUNTER_NUM_OSCOUNTER_PIT_OBJECTS + 1];
static Os_CounterNodeQueueType      OsCounter_PitNodeQueue;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_CounterFrtRunningDataType  OsCounter_SystemTick_Core1RunningData;
static Os_CounterNodeQueueDataType  OsCounter_SystemTick_Core1NodeQueueData[OS_CFG_COUNTER_NUM_OSCOUNTER_SYSTEMTICK_CORE1_OBJECTS + 1];
static Os_CounterNodeQueueType      OsCounter_SystemTick_Core1NodeQueue;
static Os_CounterNodeQueueDataType  OsCounter_Hrt_Core1NodeQueueData[OS_CFG_COUNTER_NUM_OSCOUNTER_HRT_CORE1_OBJECTS + 1];
static Os_CounterNodeQueueType      OsCounter_Hrt_Core1NodeQueue;
static Os_CounterRunningDataType    OsCounter_Software_Core1RunningData;
static Os_CounterNodeQueueDataType  OsCounter_Software_Core1NodeQueueData[OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE_CORE1_OBJECTS + 1];
static Os_CounterNodeQueueType      OsCounter_Software_Core1NodeQueue;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

const Os_CounterQueueMemConfigType OsCounter_SoftwareQueueMemCfg =
{
    OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE_OBJECTS + 1,             /* Size */
    &OsCounter_SoftwareNodeQueueData[0]                /* FreeQueueHead */ 
};

const Os_CounterConfigType Os_OsCounter_SoftwareConfigSet =
{
    {
        1000ul,           /* MaxAllowedCountValue */
        1000ul,            /* MaxDifferenceValue */
        1ul,           /* MinCyle */
        1ul,       /* TicksPerBase */
    },            /* CounterAttr */
    17ul,              /* ObjectID */
    COUNTER_DRIVER_SOFTERWARE,               /* DriverType */
    &OsCounter_SoftwareNodeQueue,            /* NodeQueue */
    &OsCounter_SoftwareRunningData,          /* RunningData */
    &OsCounter_SoftwareQueueMemCfg,          /* QueueMemCfg */
    NULL_PTR               /* HwCfg */
};

static const Os_CounterQueueMemConfigType OsCounter_SystemTickQueueMemCfg =
{
    OS_CFG_COUNTER_NUM_OSCOUNTER_SYSTEMTICK_OBJECTS + 1,
    &OsCounter_SystemTickNodeQueueData[0]
};

static const Os_CounterHwConfigType OsCounter_SystemTickHwCfg =
{
    TIMER_DRIVER_FRTTIMER,
    {
        .FrtCfg = &OsTimer_Hal_OsCounter_SystemTickHwCfg
    }
};

static const Os_CounterConfigType Os_OsCounter_SystemTickConfigSet =
{
    {
        1000ul,           /* MaxAllowedCountValue */
        1000ul,            /* MaxDifferenceValue */
        1ul,           /* MinCyle */
        25000ul        /* TicksPerBase */
    },            /* CounterAttr */
    18ul,               /* ObjectID */
    COUNTER_DRIVER_HARDWARE,               /* DriverType */
    &OsCounter_SystemTickNodeQueue,            /* NodeQueue */
    (Os_CounterRunningDataRefType)&OsCounter_SystemTickRunningData,          /* RunningData */
    &OsCounter_SystemTickQueueMemCfg,          /* QueueMemCfg */
    &OsCounter_SystemTickHwCfg               /* HwCfg */
};

const Os_CounterQueueMemConfigType OsCounter_HrtQueueMemCfg =
{
    OS_CFG_COUNTER_NUM_OSCOUNTER_HRT_OBJECTS + 1,
    &OsCounter_HrtNodeQueueData[0]
};

static const Os_CounterHwConfigType OsCounter_HrtHwCfg =
{
    TIMER_DRIVER_HRTTIMER,
    {
        .HrtCfg = &OsTimer_Hal_OsCounter_HrtHwCfg
    }
};

const Os_CounterConfigType Os_OsCounter_HrtConfigSet =
{
    {
        1073741823ul,           /* MaxAllowedCountValue */
        1073741823ul,            /* MaxDifferenceValue */
        1ul,           /* MinCyle */
        1ul       /* TicksPerBase */
    },            /* CounterAttr */
    19ul,             /* ObjectID */
    COUNTER_DRIVER_HARDWARE,               /* DriverType */
    &OsCounter_HrtNodeQueue,            /* NodeQueue */
    NULL_PTR ,          /* RunningData */
    &OsCounter_HrtQueueMemCfg,          /* QueueMemCfg */
    &OsCounter_HrtHwCfg               /* HwCfg */
};

const Os_CounterQueueMemConfigType OsCounter_Software2QueueMemCfg =
{
    OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE2_OBJECTS + 1,             /* Size */
    &OsCounter_Software2NodeQueueData[0]                /* FreeQueueHead */ 
};

const Os_CounterConfigType Os_OsCounter_Software2ConfigSet =
{
    {
        200ul,           /* MaxAllowedCountValue */
        200ul,            /* MaxDifferenceValue */
        1ul,           /* MinCyle */
        1ul,       /* TicksPerBase */
    },            /* CounterAttr */
    31ul,              /* ObjectID */
    COUNTER_DRIVER_SOFTERWARE,               /* DriverType */
    &OsCounter_Software2NodeQueue,            /* NodeQueue */
    &OsCounter_Software2RunningData,          /* RunningData */
    &OsCounter_Software2QueueMemCfg,          /* QueueMemCfg */
    NULL_PTR               /* HwCfg */
};

static const Os_CounterQueueMemConfigType OsCounter_PitQueueMemCfg =
{
    OS_CFG_COUNTER_NUM_OSCOUNTER_PIT_OBJECTS + 1,
    &OsCounter_PitNodeQueueData[0],
};

static const Os_CounterHwConfigType OsCounter_PitHwCfg =
{
    TIMER_DRIVER_PITTIMER,
    {
    .PitCfg = &OsTimer_Hal_OsCounter_PitHwCfg  
    }
};

static const Os_CounterConfigType Os_OsCounter_PitConfigSet =
{
    {
        1000ul,           /* MaxAllowedCountValue */
        1000ul,           /* MaxDifferenceValue */
        1ul,           /* MinCyle */
        100000ul,           /* TicksPerBase */
    },            /* CounterAttr */
    35ul,               /* ObjectID */
    COUNTER_DRIVER_HARDWARE,               /* DriverType */
    &OsCounter_PitNodeQueue,            /* NodeQueue */
    &OsCounter_PitRunningData,          /* RunningData */
    &OsCounter_PitQueueMemCfg,          /* QueueMemCfg */
    &OsCounter_PitHwCfg               /* HwCfg */
};        

static const Os_CounterQueueMemConfigType OsCounter_SystemTick_Core1QueueMemCfg =
{
    OS_CFG_COUNTER_NUM_OSCOUNTER_SYSTEMTICK_CORE1_OBJECTS + 1,
    &OsCounter_SystemTick_Core1NodeQueueData[0]
};

static const Os_CounterHwConfigType OsCounter_SystemTick_Core1HwCfg =
{
    TIMER_DRIVER_FRTTIMER,
    {
        .FrtCfg = &OsTimer_Hal_OsCounter_SystemTick_Core1HwCfg
    }
};

static const Os_CounterConfigType Os_OsCounter_SystemTick_Core1ConfigSet =
{
    {
        1000ul,           /* MaxAllowedCountValue */
        1000ul,            /* MaxDifferenceValue */
        1ul,           /* MinCyle */
        25000ul        /* TicksPerBase */
    },            /* CounterAttr */
    50ul,               /* ObjectID */
    COUNTER_DRIVER_HARDWARE,               /* DriverType */
    &OsCounter_SystemTick_Core1NodeQueue,            /* NodeQueue */
    (Os_CounterRunningDataRefType)&OsCounter_SystemTick_Core1RunningData,          /* RunningData */
    &OsCounter_SystemTick_Core1QueueMemCfg,          /* QueueMemCfg */
    &OsCounter_SystemTick_Core1HwCfg               /* HwCfg */
};

const Os_CounterQueueMemConfigType OsCounter_Hrt_Core1QueueMemCfg =
{
    OS_CFG_COUNTER_NUM_OSCOUNTER_HRT_CORE1_OBJECTS + 1,
    &OsCounter_Hrt_Core1NodeQueueData[0]
};

static const Os_CounterHwConfigType OsCounter_Hrt_Core1HwCfg =
{
    TIMER_DRIVER_HRTTIMER,
    {
        .HrtCfg = &OsTimer_Hal_OsCounter_Hrt_Core1HwCfg
    }
};

const Os_CounterConfigType Os_OsCounter_Hrt_Core1ConfigSet =
{
    {
        1073741823ul,           /* MaxAllowedCountValue */
        1073741823ul,            /* MaxDifferenceValue */
        1ul,           /* MinCyle */
        1ul       /* TicksPerBase */
    },            /* CounterAttr */
    51ul,             /* ObjectID */
    COUNTER_DRIVER_HARDWARE,               /* DriverType */
    &OsCounter_Hrt_Core1NodeQueue,            /* NodeQueue */
    NULL_PTR ,          /* RunningData */
    &OsCounter_Hrt_Core1QueueMemCfg,          /* QueueMemCfg */
    &OsCounter_Hrt_Core1HwCfg               /* HwCfg */
};

const Os_CounterQueueMemConfigType OsCounter_Software_Core1QueueMemCfg =
{
    OS_CFG_COUNTER_NUM_OSCOUNTER_SOFTWARE_CORE1_OBJECTS + 1,             /* Size */
    &OsCounter_Software_Core1NodeQueueData[0]                /* FreeQueueHead */ 
};

const Os_CounterConfigType Os_OsCounter_Software_Core1ConfigSet =
{
    {
        300ul,           /* MaxAllowedCountValue */
        300ul,            /* MaxDifferenceValue */
        1ul,           /* MinCyle */
        1ul,       /* TicksPerBase */
    },            /* CounterAttr */
    52ul,              /* ObjectID */
    COUNTER_DRIVER_SOFTERWARE,               /* DriverType */
    &OsCounter_Software_Core1NodeQueue,            /* NodeQueue */
    &OsCounter_Software_Core1RunningData,          /* RunningData */
    &OsCounter_Software_Core1QueueMemCfg,          /* QueueMemCfg */
    NULL_PTR               /* HwCfg */
};


/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

CONSTP2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) Os_CounterConfigSet[OS_COUNTER_TOTAL_NUM] =
{
    &Os_OsCounter_SoftwareConfigSet,
    &Os_OsCounter_SystemTickConfigSet,
    &Os_OsCounter_HrtConfigSet,
    &Os_OsCounter_PitConfigSet,
    &Os_OsCounter_Software2ConfigSet,
    &Os_OsCounter_SystemTick_Core1ConfigSet,
    &Os_OsCounter_Hrt_Core1ConfigSet,
    &Os_OsCounter_Software_Core1ConfigSet
};

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/





