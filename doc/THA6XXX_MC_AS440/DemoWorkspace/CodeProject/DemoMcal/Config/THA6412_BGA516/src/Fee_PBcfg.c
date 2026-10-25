/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fee_Cfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all configurations of FEE module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Fee_PBcfg_c_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Fee_PBcfg_c_REF_2:MISRAC2012-Rule-8.9;
* Justification:The value should be placed in the const data sections to reduce code complexity 
* and stack size.
*
*#Fee_PBcfg_c_REF_3:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Fee.h"
#include "Fee_Cfg.h"

/****************************************************************************************************
*                         Function declaration                                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#if (0U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FEE_CORE_ALLOCATION) */
/* #Violation: Fee_PBcfg_c_REF_3 */
#include "Fee_MemMap.h"


static const Fee_BlockConfigType Fee_BlockConfig[FEE_MAX_BLOCK_COUNT] =
{
    {
        0U,     /* Block Cycle Count */
        8U,     /* Block number */
        32U,     /* Fee Block Size */
        FALSE,   /* normal */
    },
    {
        100U,     /* Block Cycle Count */
        9U,     /* Block number */
        64U,     /* Fee Block Size */
        TRUE,    /* immediate */
    }
};

/* #Violation: Fee_PBcfg_c_REF_2 */
const Fee_ConfigType Fee_ConfigSet[FEE_CONFIG_COUNT] =
{
    {
        /* The number of configuration block */
        2U,
        /* The block configuration */
        Fee_BlockConfig,
        /* Job End Notification */
        NvM_JobEndNotification,
        /* Job Error Notification */
        NvM_JobErrorNotification,
        /* Unavailable Failure Notification */
        NvM_UnavailableFailureNotification,
        /* Discover NonErasable Areas Notification */
        (Fee_NotificationPtrType)0,
        /* Not Found Management Info Notification */
        (Fee_NotificationPtrType)0,
    }
};

#if (0U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_PBcfg_c_REF_1 */
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FEE_CORE_ALLOCATION) */
/* #Violation: Fee_PBcfg_c_REF_3 */
#include "Fee_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

