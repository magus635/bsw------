/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all configurations of FLS module
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
*#Fls_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Fls_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*#Fls_PBcfg_c_REF_3:CertC-DL06-C;
* Justification:The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Fls_PBcfg_c_REF_4:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Fls.h"
#include "Fls_Cfg.h"

/***************************************************************************************************
*                         Function declaration
***************************************************************************************************/
/* Function declaration of Fls Job End Notification */
extern void Fee_JobEndNotification(void);

/* Function declaration of Fls Job Error Notifications */
extern void Fee_JobErrorNotification(void);

/***************************************************************************************************
*                               Local Constants
****************************************************************************************************/

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_PBcfg_c_REF_1 */
#include "Fls_MemMap.h"
/* #Violation: Fls_PBcfg_c_REF_3 */
/* #Violation: Fls_PBcfg_c_REF_4 */
static const Fls_SectorConfigType Fls_SectorList[2U] = 
{
    /* configuration of (FlsSector_0) */
    {
        /* Start address of the this FlsSector */
        0U,
        /* Size of the sector */
        8192U,
        /* Size of flash page size */
        16U,
        /* End address of the this FlsSector */
        262143U
    },/* configuration of (FlsSector_1) */
    {
        /* Start address of the this FlsSector */
        268435456U,
        /* Size of the sector */
        16384U,
        /* Size of flash page size */
        32U,
        /* End address of the this FlsSector */
        268959743U
    }};

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_PBcfg_c_REF_1 */
#include "Fls_MemMap.h"

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_PBcfg_c_REF_1 */
#include "Fls_MemMap.h"
/* Fls Configuration structure */
/* The job processing callback notifications shall be configurable as function pointers
   within the initialization data structure (Fls_ConfigType). [SWS_Fls_00109] */
const Fls_ConfigType Fls_ConfigSet[FLS_CONFIG_COUNT] =
{
    {
        /* Fast Mode : Maximum number of bytes to Read in one cycle */
        256U,
        /* Slow Mode : Maximum number of bytes to Read in one cycle */
        128U,
        /* Fast Mode : Maximum number of bytes to Write in one cycle */
        128U,
        /* Slow Mode : Maximum number of bytes to Write in one cycle */
        128U,
        /* Job End Notification */
        Fee_JobEndNotification,
        /* Job Error Notification */
        Fee_JobErrorNotification,
        /* FlsCallCycle for timeout monitoring, convert to us by multiplying by 1000 * 1000 */
        10000U,        /* Default mode of FLS driver */
        MEMIF_MODE_FAST,
        /* Pointer of FlsSector configuration */
        &Fls_SectorList[0U],
        /* Number of FlsSector */
        2U
    }
};

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_PBcfg_c_REF_2 */
#define FLS_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_PBcfg_c_REF_1 */
#include "Fls_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
