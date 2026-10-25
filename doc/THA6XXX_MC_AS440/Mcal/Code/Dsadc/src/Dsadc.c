/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dsadc.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DSADC
*
*   brief                 : This file contains all functions of Dsadc Driver
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
*#Dsadc_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Dsadc_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Redundant cast is necessary to maintain the software structure and reduce the 
*   complexity.
*
*#Dsadc_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Dsadc_c_REF_4:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain
*   parts of the driver must be placed.
*
*#Dsadc_c_REF_5:MISRAC2012-Rule-20.10;
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Dsadc_c_REF_6:MISRAC2012-Rule-20.7;
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Dsadc_c_REF_7:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#Dsadc_c_REF_8:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Dsadc_c_REF_9:CWE-1071;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Dsadc_c_REF_10:MISRAC2012-Dir-4.1;
* Justification: Number of loops is set by different configurations.
*
*#Dsadc_c_REF_11:MISRAC2012-Rule-2.2;
* Justification: Code review ensures the compliance with rule.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
#include "Dsadc.h"
#include "Dsadc_Version.h"
#include "SchM_Dsadc.h"
#if ((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON))
/* Included the declaration of Dsadc_ReportError() */
#include "Det.h"
#endif /* \((DSADC_DEV_ERROR_DETECT == STD_ON) || (DSADC_SAFETY_ENABLE == STD_ON)) */
#if (DSADC_DEM_ERROR_REPORT_STATUS == STD_ON)
/* Included for the declaration of Dem_SetEventStatus() */
#include "Dem.h"
#endif /* \(LIN_DEM_ERROR_REPORT_STATUS == STD_ON) */
/* Included the Dsadc driver of HAL layer */
#include "tha6_cfg.h"
#include "dsadc_hal.h"


/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
/* Check if current file and INTC header file are of the same vendor */
#if (DSADC_VENDOR_ID != DSADC_CFG_VENDOR_ID)
  #error "Dsadc.c : Mismatch in Vendor ID"
#endif /* \(DSADC_VENDOR_ID != DSADC_CFG_VENDOR_ID) */

#if (DSADC_MODULE_ID != DSADC_CFG_MODULE_ID)
  #error "Dsadc.c : Mismatch in Module ID"
#endif /* \(DSADC_MODULE_ID != DSADC_CFG_MODULE_ID) */

#if (DSADC_AR_RELEASE_MAJOR_VERSION != DSADC_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Dsadc.c : Mismatch in Release Major Version"
#endif /* \(DSADC_AR_RELEASE_MAJOR_VERSION != DSADC_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (DSADC_AR_RELEASE_MINOR_VERSION != DSADC_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Dsadc.c : Mismatch in Release Minor Version"
#endif /* \(DSADC_AR_RELEASE_MINOR_VERSION != DSADC_CFG_AR_RELEASE_MINOR_VERSION) */

#if (DSADC_AR_RELEASE_REVISION_VERSION != DSADC_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Dsadc.c : Mismatch in Release Revision Version"
#endif /* \(DSADC_AR_RELEASE_REVISION_VERSION != DSADC_CFG_AR_RELEASE_REVISION_VERSION) */

#if (DSADC_SW_MAJOR_VERSION != DSADC_CFG_SW_MAJOR_VERSION)
  #error "Dsadc.c : Mismatch in Software Major Version"
#endif /* \(DSADC_SW_MAJOR_VERSION != DSADC_CFG_SW_MAJOR_VERSION) */

#if (DSADC_SW_MINOR_VERSION != DSADC_CFG_SW_MINOR_VERSION)
  #error "Dsadc.c : Mismatch in Software Minor Version"
#endif /* \(DSADC_SW_MINOR_VERSION != DSADC_CFG_SW_MINOR_VERSION) */

#if (DSADC_SW_PATCH_VERSION != DSADC_CFG_SW_PATCH_VERSION)
  #error "Dsadc.c : Mismatch in Software Patch Version"
#endif /* \(DSADC_SW_PATCH_VERSION != DSADC_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/* Macro for get the channel configuration of given core.
 * Core: Core identifier
 * ChannelIdx: Channel index in the core, not logical channel
 *  */
/* #Violation: Dsadc_c_REF_1 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_GET_CHCFG(Core, ChannelIdx)    \
                              (&Dsadc_ConfigPtr->CoreConfigPtr[Core]->ChannelConfigPtr[ChannelIdx])
/* Macro for get channel index in the core using Channel identifier.
 * Channel: Logical channel identifier
 *  */
/* #Violation: Dsadc_c_REF_1 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_GET_CORECHIDX(Channel)       \
                              (Dsadc_ConfigPtr->ChannelMapPtr[Channel].CoreChannelIdx)
/* Macro for get maximum channel in the core.
 * Core: Core identifier
 *  */
/* #Violation: Dsadc_c_REF_1 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_GET_COREMAXCH(Core)          \
                              (Dsadc_ConfigPtr->CoreConfigPtr[Core]->MaxCoreChannel)
/* Macro for get the HW unit identifier.
 * HwUnitId: HW unit identifier.
 *  */
/* #Violation: Dsadc_c_REF_1 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_GET_CHOFHW(HwUnitId)         \
                              (Dsadc_ConfigPtr->HwUnitToChannelIdPtr[HwUnitId])
/* Macro for get HW unit identifier.
 * Channel: Logical channel identifier.
 *  */
/* #Violation: Dsadc_c_REF_1 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_GET_HWOFCH(Channel)          \
                              (Dsadc_ConfigPtr->ChannelMapPtr[Channel].HwUnitId)
/* Macro for get the main conversion channel status.
 * Core: Core identifier
 * ChannelIdx: Channel index in the core, not logical channel
 *  */
/* #Violation: Dsadc_c_REF_1 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_CHSTA(Core, ChannelIdx)     \
                              (Dsadc_CoreDataSetPtr[Core][ChannelIdx].ChStatus)

/* Macro for get the auxiliary conversion channel status */
/* #Violation: Dsadc_c_REF_1 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_CHAUXSTA(Core, ChannelIdx)  \
                              (Dsadc_CoreDataSetPtr[Core][ChannelIdx].ChAuxStatus)

/* Macro for get the channel interrupt config. */
/* #Violation: Dsadc_c_REF_1 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_CHINTBITS(Core, ChannelIdx) \
                              (Dsadc_CoreDataSetPtr[Core][ChannelIdx].IntEnBits)

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* Macro for report the DSADC DET error */
/* #Violation: Dsadc_c_REF_8 */
#define Dsadc_ReportError(ServiceId, ErrCode)        \
                              (void)Det_ReportError(DSADC_MODULE_ID, DSADC_INSTANCE_ID, \
                                                    ServiceId, ErrCode)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

#if (DSADC_SAFETY_ENABLE == STD_ON)
/* Macro for report the DSADC runtime error */
/* #Violation: Dma_c_REF_8 */
#define Dsadc_ReportRuntimeError(ServiceId)        \
                     (void)Det_ReportRuntimeError(DSADC_MODULE_ID, DSADC_INSTANCE_ID, \
                                                  ServiceId, DSADC_E_SAFETY_CHECK_FAILED)
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* Carrier is stopped */
#define DSADC_CARRIER_SIGNAL_STOP                       (STD_OFF)
/* Carrier is started */
#define DSADC_CARRIER_SIGNAL_START                      (STD_ON)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/* Mask for the low 8bits of the DSADC hardware unit enable status.  */
#define DSADC_HWUNIT_EN_LOW_BITS_MASK                   (0xFFU)
/* Shift amount for the high 2bits of the DSADC hardware unit enable status. */
#define DSADC_HWUNIT_EN_HIGH_BITS_SHIFT                 (8U)
/* Mask for the high 2bits of the DSADC hardware unit enable status. */
#define DSADC_HWUNIT_EN_HIGH_BITS_MASK                  (0x30000U)

#if (DSADC_CFG_SET_CARRIER_SYNC_PARAM_API == STD_ON)
/* Invalid ID */
#define DSADC_INVALID_ID                                (255U)
#endif /* \(DSADC_CFG_SET_CARRIER_SYNC_PARAM_API == STD_ON) */

/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_5 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Dsadc_##Exclusive_Area()
/* #Violation: Dsadc_c_REF_5 */
/* #Violation: Dsadc_c_REF_8 */
#define DSADC_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Dsadc_##Exclusive_Area()

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/**                         Private Variable Definitions - Core0                                  **/
#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Dsadc_MemMap.h"

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* Driver initialization status flag for Core0 */
/* Since the main core must be initialized, this variable must exist */
static Dsadc_InitType Dsadc_InitFlgCore0;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#if (DSADC_MAX_CHANNEL_TO_CORE0 > 0U)

#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

/* Dsadc Runtime data variable of core0  */
static Dsadc_GlobalDataType Dsadc_DataCore0[DSADC_MAX_CHANNEL_TO_CORE0];

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#endif /* \(DSADC_MAX_CHANNEL_TO_CORE0 > 0U) */

/**                         Private Variable Definitions - Core1                                  **/
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (DSADC_MAX_CHANNEL_TO_CORE1 > 0U)

#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* Dsadc installed flag for Core 1 */
static Dsadc_InitType Dsadc_InitFlgCore1;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/* Dsadc Runtime data variable of core1 */
static Dsadc_GlobalDataType Dsadc_DataCore1[DSADC_MAX_CHANNEL_TO_CORE1];

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#endif /* \(DSADC_MAX_CHANNEL_TO_CORE1 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */

/**                         Private Variable Definitions - Core2                                  **/
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (DSADC_MAX_CHANNEL_TO_CORE2 > 0U)

#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* Dsadc installed flag for Core 2 */
static Dsadc_InitType Dsadc_InitFlgCore2;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/* Dsadc Runtime data variable of core2 */
static Dsadc_GlobalDataType Dsadc_DataCore2[DSADC_MAX_CHANNEL_TO_CORE2];

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#endif /* \(DSADC_MAX_CHANNEL_TO_CORE2 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */

/**                         Private Variable Definitions - Core3                                  **/
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (DSADC_MAX_CHANNEL_TO_CORE3 > 0U)

#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* Dsadc installed flag for Core 3 */
static Dsadc_InitType Dsadc_InitFlgCore3;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/* Dsadc Runtime data variable of core3 */
static Dsadc_GlobalDataType Dsadc_DataCore3[DSADC_MAX_CHANNEL_TO_CORE3];

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#endif /* \(DSADC_MAX_CHANNEL_TO_CORE3 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */

#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* Carrier signal status */
static uint8 Dsadc_CarrierStatus;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/* To store the Dsadc driver configuration pointer */
static P2CONST(Dsadc_ConfigType, AUTOMATIC, DSDSADC_APPL_DATA) Dsadc_ConfigPtr;

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
#define DSADC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* Pointer to the DSADC Initialization status */
/* #Violation: Dsadc_c_REF_6 */
static CONSTP2VAR(Dsadc_InitType, DSADC_VAR, DSADC_APPL_CONST)
                                       Dsadc_CoreInitStatusSetPtr[MCAL_NUMBER_OF_CORES] =
{
    &Dsadc_InitFlgCore0

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (DSADC_MAX_CHANNEL_TO_CORE1 > 0U)
    ,&Dsadc_InitFlgCore1
#else
    ,NULL_PTR
#endif /* \(DSADC_MAX_CHANNEL_TO_CORE1 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (DSADC_MAX_CHANNEL_TO_CORE2 > 0U)
    ,&Dsadc_InitFlgCore2
#else
    ,NULL_PTR
#endif /* \(DSADC_MAX_CHANNEL_TO_CORE2 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (DSADC_MAX_CHANNEL_TO_CORE3 > 0U)
    ,&Dsadc_InitFlgCore3
#else
    ,NULL_PTR
#endif /* \(DSADC_MAX_CHANNEL_TO_CORE3 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */
};
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/* Pointer to the ADC HW unit data structure set for each core */
/* #Violation: Dsadc_c_REF_6 */
static CONSTP2VAR(Dsadc_GlobalDataType, DSADC_VAR, DSADC_APPL_CONST)
                                       Dsadc_CoreDataSetPtr[MCAL_NUMBER_OF_CORES] =
{
#if (DSADC_MAX_CHANNEL_TO_CORE0 > 0U)
    &Dsadc_DataCore0[0]
#else
    NULL_PTR
#endif /* \(DSADC_MAX_CHANNEL_TO_CORE0 > 0U) */

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (DSADC_MAX_CHANNEL_TO_CORE1 > 0U)
    ,&Dsadc_DataCore1[0]
#else
    ,NULL_PTR
#endif /* \(DSADC_MAX_CHANNEL_TO_CORE1 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (DSADC_MAX_CHANNEL_TO_CORE2 > 0U)
    ,&Dsadc_DataCore2[0]
#else
    ,NULL_PTR
#endif /* \(DSADC_MAX_CHANNEL_TO_CORE2 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (DSADC_MAX_CHANNEL_TO_CORE3 > 0U)
    ,&Dsadc_DataCore3[0]
#else
    ,NULL_PTR
#endif /* \(DSADC_MAX_CHANNEL_TO_CORE3 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */
};

/* Pointer to the address of each DSADC HW unit */
/* #Violation: Dsadc_c_REF_6 */
static CONSTP2VAR(DSADC_MODULE, DSADC_VAR, DSADC_APPL_CONST) Dsadc_BaseAddrs[DSADC_TOTAL_HWUNIT] =
{
#if ((defined(DSADC_HWUNIT_DSADC0)) && (DSADC_HWUNIT_DSADC0 == 0U))
    /* #Violation: Dsadc_c_REF_3 */
    DSADC0
#else /* \!defined(DSADC_HWUNIT_DSADC0) */
    NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC0)) && (DSADC_HWUNIT_DSADC0 == 0U)) */

#if (DSADC_TOTAL_HWUNIT > 1U)
#if ((defined(DSADC_HWUNIT_DSADC1)) && (DSADC_HWUNIT_DSADC1 == 1U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC1
#else /* \!defined(DSADC_HWUNIT_DSADC1) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC1)) && (DSADC_HWUNIT_DSADC1 == 1U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 1U) */

#if (DSADC_TOTAL_HWUNIT > 2U)
#if ((defined(DSADC_HWUNIT_DSADC2)) && (DSADC_HWUNIT_DSADC2 == 2U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC2
#else /* \!defined(DSADC_HWUNIT_DSADC2) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC2)) && (DSADC_HWUNIT_DSADC2 == 2U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 2U) */

#if (DSADC_TOTAL_HWUNIT > 3U)
#if ((defined(DSADC_HWUNIT_DSADC3)) && (DSADC_HWUNIT_DSADC3 == 3U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC3
#else /* \!defined(DSADC_HWUNIT_DSADC3) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC3)) && (DSADC_HWUNIT_DSADC3 == 3U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 3U) */

#if (DSADC_TOTAL_HWUNIT > 4U)
#if ((defined(DSADC_HWUNIT_DSADC4)) && (DSADC_HWUNIT_DSADC4 == 4U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC4
#else /* \!defined(DSADC_HWUNIT_DSADC4) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC4)) && (DSADC_HWUNIT_DSADC4 == 4U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 4U) */

#if (DSADC_TOTAL_HWUNIT > 5U)
#if ((defined(DSADC_HWUNIT_DSADC5)) && (DSADC_HWUNIT_DSADC5 == 5U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC5
#else /* \!defined(DSADC_HWUNIT_DSADC5) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC5)) && (DSADC_HWUNIT_DSADC5 == 5U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 5U) */

#if (DSADC_TOTAL_HWUNIT > 6U)
#if ((defined(DSADC_HWUNIT_DSADC6)) && (DSADC_HWUNIT_DSADC6 == 6U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC6
#else /* \!defined(DSADC_HWUNIT_DSADC6) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC6)) && (DSADC_HWUNIT_DSADC6 == 6U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 6U) */

#if (DSADC_TOTAL_HWUNIT > 7U)
#if ((defined(DSADC_HWUNIT_DSADC7)) && (DSADC_HWUNIT_DSADC7 == 7U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC7
#else /* \!defined(DSADC_HWUNIT_DSADC7) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC7)) && (DSADC_HWUNIT_DSADC7 == 7U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 7U) */

#if (DSADC_TOTAL_HWUNIT > 8U)
#if ((defined(DSADC_HWUNIT_DSADC8)) && (DSADC_HWUNIT_DSADC8 == 8U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC8
#else /* \!defined(DSADC_HWUNIT_DSADC8) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC8)) && (DSADC_HWUNIT_DSADC8 == 8U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 8U) */

#if (DSADC_TOTAL_HWUNIT > 9U)
#if ((defined(DSADC_HWUNIT_DSADC9)) && (DSADC_HWUNIT_DSADC9 == 9U))
    /* #Violation: Dsadc_c_REF_3 */
    ,DSADC9
#else /* \!defined(DSADC_HWUNIT_DSADC9) */
    ,NULL_PTR
#endif /* \((defined(DSADC_HWUNIT_DSADC9)) && (DSADC_HWUNIT_DSADC9 == 9U)) */
#endif /* \(DSADC_TOTAL_HWUNIT > 9U) */
};

#define DSADC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#if (DSADC_DEV_ERROR_DETECT == STD_ON)

static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckInitParam
(
    CONSTP2CONST(Dsadc_ConfigType, AUTOMATIC, DSADC_APPL_CONST) ConfigPtr
);

static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckInit
(
    uint8 ServiceId,
    Mcal_CoreType CoreId
);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckDeInit
(
    Mcal_CoreType CoreId
);
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckMulticoreAllocateError
(
    uint8 ServiceId,
    Dsadc_ChannelType ChannelId
);

#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_InitChannel
(
    CONSTP2CONST(Dsadc_ConfigType, AUTOMATIC, DSADC_APPL_CONST) ConfigPtr,
    Mcal_CoreType CoreId,
    Dsadc_ChannelType ChIdx
);

static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_InitMasterCore
(
    CONSTP2CONST(Dsadc_ConfigType, AUTOMATIC, DSADC_APPL_CONST) ConfigPtr
);

#if (DSADC_CFG_DEINIT_API == STD_ON)
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckAllChannelStatus
(
    void
);

static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_DeInitChannel
(
    Dsadc_HWUnitType HwUnitId
);
#endif /* \(DSADC_CFG_DEINIT_API == STD_ON) */

#if ((DSADC_CFG_GETSTREAMLASTPOINTER_API == STD_ON) && (DSADC_DEV_ERROR_DETECT == STD_ON))
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_GetStreamLastPointerErrCheck
(
    Mcal_CoreType CoreId,
    Dsadc_ChannelType CoreChIdx
);
#endif /* \((DSADC_CFG_GETSTREAMLASTPOINTER_API == STD_ON) && (DSADC_DEV_ERROR_DETECT == STD_ON)) */

#if ((DSADC_CFG_DMA_MODE == STD_ON) || (DSADC_CFG_INTERRUPT_MODE == STD_ON))
static FUNC(void, DSADC_PRIVATE_CODE) Dsadc_SetInterruptEnStatus
(
    /* #Violation: Dsadc_c_REF_6 */
    CONSTP2VAR(Dsadc_GlobalDataType, AUTOMATIC, DSADC_APPL_DATA) DataPtr,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr
);
#endif /* \((DSADC_CFG_DMA_MODE == STD_ON) || (DSADC_CFG_INTERRUPT_MODE == STD_ON)) */

#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
static FUNC(void, DSADC_PRIVATE_CODE) Dsadc_AuxIsrEventEntry
(
    Dsadc_HWUnitType HwUnitId,
    Dsadc_ChannelType Channel,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr
);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE == STD_ON) */

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_IsrEventEntry
(
    Dsadc_HWUnitType HwUnitId,
    Dsadc_ChannelType Channel,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr
);
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_FifoOrExternalTriggerIsr
(
    Dsadc_HWUnitType HwUnitId,
    Dsadc_ChannelType Channel,
    boolean TrigMthdFlg,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr,
    Dsadc_ResultType RecentRslt
);
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
#if (DSADC_CFG_TIMESTAMP_ENABLE == STD_ON)
static FUNC(void, DSADC_PRIVATE_CODE) Dsadc_TimestampIsr
(
    Dsadc_HWUnitType HwUnitId,
    Dsadc_ChannelType Channel,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr
);
#endif /* \(DSADC_CFG_TIMESTAMP_ENABLE == STD_ON) */
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_CheckInitParam
*
*   Service ID              : None.
*
*   Description             : Check initialization status for DET
*
*   Parameters in           : ConfigPtr: Pointer to the DSADC configuration parameters.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : No DET error
*                             E_NOT_OK : DET error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckInitParam
(
    CONSTP2CONST(Dsadc_ConfigType, AUTOMATIC, DSADC_APPL_CONST) ConfigPtr
)
{
    Std_ReturnType RetErr;
    Mcal_CoreType  CoreId;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    RetErr = E_NOT_OK;
    if ((MCAL_MASTER_CORE != CoreId) &&
            (DSADC_UNINITIALIZE == *(Dsadc_CoreInitStatusSetPtr[MCAL_MASTER_CORE])))
    {
        /* Master core is not initialized */
        Dsadc_ReportError(DSADC_SID_INIT, DSADC_E_MASTER_CORE_UNINITIALIZE);
    }
    else if ((MCAL_MASTER_CORE != CoreId) && (NULL_PTR == Dsadc_CoreInitStatusSetPtr[CoreId]))
    {
        /* No HW UNIT are configured for specified core "CoreId" */
        Dsadc_ReportError(DSADC_SID_INIT, DSADC_E_CORE_NOT_CONFIGURED);
    }
    else if (DSADC_INITIALIZED == *(Dsadc_CoreInitStatusSetPtr[CoreId]))
    {
        /* SWS_Adc_00107: DET for ADC_E_ALREADY_INITIALIZED */
        /* ADC Driver initialization is called twice before De-init */
        Dsadc_ReportError(DSADC_SID_INIT, DSADC_E_ALREADY_INITIALIZED);
    }
    else if (NULL_PTR == ConfigPtr)
    {
        /* SWS_Adc_00343: DET for ADC_E_PARAM_CONFIG */
        /* ConfigPtr is NULL_PTR, report DET error for variant PB */
        Dsadc_ReportError(DSADC_SID_INIT, DSADC_E_PARAM_CONFIG);
    }
    else
    {
        RetErr = E_OK;
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Dsadc_CheckInit
*
*   Service ID              : None.
*
*   Description             : Check module initialization status
*
*   Parameters in           : ServiceId: Service id of calling API.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : No DET error
*                             E_NOT_OK : DET error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckInit
(
    uint8 ServiceId,
    Mcal_CoreType CoreId
)
{
    Std_ReturnType RetErr;

    RetErr = E_NOT_OK;

    if ((MCAL_MASTER_CORE != CoreId) && (NULL_PTR == Dsadc_CoreInitStatusSetPtr[CoreId]))
    {
        /* No HW UNIT are configured for specified core "CoreId" */
        Dsadc_ReportError(ServiceId, DSADC_E_CORE_NOT_CONFIGURED);
    }
    else if (DSADC_INITIALIZED != *(Dsadc_CoreInitStatusSetPtr[CoreId]))
    {
        /* Reporting of error DSADC_E_UNINIT */
        Dsadc_ReportError(ServiceId, DSADC_E_UNINIT);
    }
    else if ((ServiceId != DSADC_SID_DEINIT) && (NULL_PTR == Dsadc_ConfigPtr->CoreConfigPtr[CoreId]))
    {
        /* Not configuration data excluding the de-initialization API */
        Dsadc_ReportError(ServiceId, DSADC_E_CORE_NOT_CONFIGURED);
    }
    else
    {
        RetErr = E_OK;
    }

    return RetErr;
}

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_CheckDeInit
*
*   Service ID              : None.
*
*   Description             : Check module initialization status
*
*   Parameters in           : ServiceId: Service id of calling API.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : No DET error
*                             E_NOT_OK : DET error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckDeInit
(
    Mcal_CoreType CoreId
)
{
    Std_ReturnType Err;
    uint8 CoreCnt;

    Err = Dsadc_CheckInit(DSADC_SID_DEINIT, CoreId);
    if (E_OK == Err)
    {
        if (MCAL_MASTER_CORE == CoreId)
        {
            /* Check if all slave cores have been de-initialized  */
            for (CoreCnt = (uint8)MCAL_CORE1;
                    /* #Violation: Dsadc_c_REF_10 */
                    (CoreCnt < MCAL_NUMBER_OF_CORES) && (E_OK == Err); CoreCnt++)
            {
                if ((NULL_PTR != Dsadc_CoreInitStatusSetPtr[CoreCnt]) &&
                    (DSADC_INITIALIZED == *Dsadc_CoreInitStatusSetPtr[CoreCnt]))
                {
                    /* Some slave core has not been de-initialized */
                    Dsadc_ReportError(DSADC_SID_DEINIT, DSADC_E_SLAVE_CORE_INITIALIZED);
                    Err = E_NOT_OK;
                }
            }
        }
    }

    return Err;
}
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dsadc_CheckMulticoreAllocateError
*
*   Service ID              : None.
*
*   Description             : This function shall check multi-core allocation error.
*
*   Parameters in           : ServiceId: Service API ID;
*                             ChannelId: Numeric ID of requested logical channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : No DET error
*                             E_NOT_OK : DET error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckMulticoreAllocateError
(
    uint8 ServiceId,
    Dsadc_ChannelType ChannelId
)
{
    Std_ReturnType                RetErr;
    Mcal_CoreType                 CoreId;
    uint8                         CoreChIdx;
    const Dsadc_ChannelConfigType *CfgPtr;

    RetErr = E_NOT_OK;

    if (ChannelId >= DSADC_CFG_TOTAL_CHANNELS)
    {
        /* Wrong channel */
        Dsadc_ReportError(ServiceId, DSADC_E_PARAM_CHANNEL);
    }
    else
    {
        /* Get core id which core is currently executing */
        /* #Violation: Dsadc_c_REF_1 */
        CoreId = Mcal_GetCoreId();
        /* Find the sub-index according to the channel */
        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(ChannelId);
        /* #Violation: Dsadc_c_REF_1 */
        if (CoreChIdx >= DSADC_GET_COREMAXCH(CoreId))
        {
            /* Parameter of channel is out of range */
            Dsadc_ReportError(ServiceId, DSADC_E_CORE_HWUNIT_MISMATCH);
        }
        else
        {
            /* #Violation: Dsadc_c_REF_1 */
            CfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);
            if (ChannelId != CfgPtr->LgcChId)
            {
                /* Parameter of  is not equal to the actual assigned logic channel
                 * for specified core */
                Dsadc_ReportError(ServiceId, DSADC_E_CORE_HWUNIT_MISMATCH);
            }
            else
            {
                RetErr = E_OK;
            }
        }
    }

    return RetErr;
}

#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

#if (DSADC_CFG_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_CheckAllChannelStatus
*
*   Service ID              : None.
*
*   Description             : Check all DSADC channels are busy or not.
*
*   Parameters in           : None
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK : No DET error
*                             E_NOT_OK : DET error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_CheckAllChannelStatus
(
    void
)
{
    Std_ReturnType                RetErr;
    uint8                         CoreChdx;
    Dsadc_StatusType              ChStatus;
    Mcal_CoreType                 CoreId;

    RetErr = E_OK;

    /* Get core id which core is currently executing */
    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    /* Configuration is exists */
    if (NULL_PTR != Dsadc_ConfigPtr->CoreConfigPtr[CoreId])
    {
        CoreChdx = 0U;
        /* Loop all HW unit of specified cores */
        /* #Violation: Dsadc_c_REF_1 */
        while ((CoreChdx < DSADC_GET_COREMAXCH(CoreId)) &&
            /* Exit loop when any one group is not in 'ADC_E_DET_NO_ERR' status */
            (E_OK == RetErr))
        {
            /* Get the current ADC HW Unit Group status */
            /* #Violation: Dsadc_c_REF_1 */
            ChStatus = DSADC_CHSTA(CoreId, CoreChdx);
            if (DSADC_BUSY == ChStatus)
            {
                RetErr = E_NOT_OK;
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
                /* Channel is not in IDLE status */
                Dsadc_ReportError(DSADC_SID_DEINIT, DSADC_E_BUSY);
#endif /* \(DSADC_CFG_CARRIER_ENABLE == STD_ON) */
            }

            CoreChdx++;
        }
    }

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    if (E_OK == RetErr)
    {
        /* Judge whether carrier generator is running */
        if (DSADC_CARRIER_SIGNAL_START == Dsadc_CarrierStatus)
        {
            RetErr = E_NOT_OK;
            /* Carrier generator is running */
            Dsadc_ReportError(DSADC_SID_DEINIT, DSADC_E_CARRIER_ALREADY_OPENDED);
        }
    }
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

    return RetErr;
}

/****************************************************************************************************
 *   Function Name           : Dsadc_DeInitChannel
 *
 *   Service ID              : None.
 *
 *   Description             : De-initialize the a DSADC channel.
 *
 *   Parameters in           : HwUnitId: HWunit ID.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : TRUE: Dsadc channel de-init success.
 *                             FALSE: Dsadc channel de-init failed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_DeInitChannel
(
    Dsadc_HWUnitType HwUnitId
)
{
    boolean SafetyErr;
    Std_ReturnType LockStatus;
    SafetyErr = TRUE;

    DSADC_ENTER_CRITICAL_SECTION(DeInit);

    /* Lock for disable interrupts */
    LockStatus = Mcal_GetLock(MCAL_LOCK_ID_RCC);
    if (E_OK == LockStatus)
    {
        /* Some common registers in DSADC0 should be de-initialized by
            * CORE0 */
        /* De-initialize the DSADC module, reset all registers by RCC */
        SafetyErr &= Dsadc_Hal_DeInitModule(Dsadc_BaseAddrs[HwUnitId]);

        /* Release software lock for INTC */
        Mcal_ReleaseLock(MCAL_LOCK_ID_RCC);
    }
    else
    {
        /* Get lock failed */
        SafetyErr = FALSE;
    }

    DSADC_EXIT_CRITICAL_SECTION(DeInit);

    return SafetyErr;
}

#endif /* \(DSADC_CFG_DEINIT_API == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dsadc_SetInterruptEnStatus
*
*   Service ID              : None.
*
*   Description             : Set interrupt enable status.
*                             Only valid when result handling mode is INTERRUPT or DMA.
*
*   Parameters in           : ChCfgPtr: Pointer to the configuration information of logical
*                               channel.
*
*   Parameters inout        : DataPtr: Pointer to the global dataset.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, DSADC_PRIVATE_CODE) Dsadc_SetInterruptEnStatus
(
    /* #Violation: Dsadc_c_REF_6 */
    CONSTP2VAR(Dsadc_GlobalDataType, AUTOMATIC, DSADC_APPL_DATA) DataPtr,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr
)
{
#if (DSADC_CFG_DMA_MODE == STD_ON)
    /* DMA mode enabled with DSADC channel */
    if (DSADC_RESULT_HANDLING_DMA_MODE == ChCfgPtr->RsltHldMthd)
    {
        /* Conversion result is handled by DMA */
        if (DSADC_SERVICEREQUEST_FIFOTHRESHOLD == ChCfgPtr->HwCfgPtr->pMainFilterConfig->request)
        {
            /* Software trigger, setting the DMA FIFO request */
            DataPtr->IntEnBits = (uint16)DSADC_DMA_FIFO_INTERRUPT;
        }
        else
        {
            /* External signal trigger, setting the DMA service request */
            DataPtr->IntEnBits = (uint16)DSADC_DMA_EXTERNAL_TRIGGER_INTERRUPT;
        }
    }
    else
#endif /* \(DSADC_CFG_DMA_MODE == STD_ON) */
#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
    /* Interrupt mode enabled with DSADC channel */
    {
        /* Conversion result is handled by interrupt */
        if (DSADC_SERVICEREQUEST_FIFOTHRESHOLD == ChCfgPtr->HwCfgPtr->pMainFilterConfig->request)
        {
            if (DSADC_RESULT_HANDLING_INTERRUPT_MODE == ChCfgPtr->RsltHldMthd)
            {
                /* Software trigger, setting the FIFO request interrupt */
                DataPtr->IntEnBits = (uint16)DSADC_FIFO_INTERRUPT;
            }
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
            if (TRUE == ChCfgPtr->IsAuxChRsltAcqEn)
            {
                /* Auxiliary conversion channel completed interrupt */
                /* Enable the auxiliary channel conversion completed interrupt */
                DataPtr->IntEnBits |= (uint16)DSADC_AUXILIARY_COMPLETED_INTERRUPT;
            }
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
        }
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
        else if (DSADC_SERVICEREQUEST_NONE ==
                ChCfgPtr->HwCfgPtr->pMainFilterConfig->request)
        {
            if (TRUE == ChCfgPtr->IsAuxChRsltAcqEn)
            {
                /* Auxiliary conversion channel completed interrupt */
                /* Enable the auxiliary channel conversion completed interrupt */
                DataPtr->IntEnBits |= (uint16)DSADC_AUXILIARY_COMPLETED_INTERRUPT;
            }
        }
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
        else
        {
            /* External signal trigger, setting the service request interrupt */
            DataPtr->IntEnBits = (uint16)DSADC_EXTERNAL_TRIGGER_INTERRUPT;
#if (DSADC_CFG_TIMESTAMP_ENABLE == STD_ON)
            if (TRUE == ChCfgPtr->TimestampEn)
            {
                /* Enable the timestamp interrupt when external trigger is used */
                DataPtr->IntEnBits |= (uint16)DSADC_TIMESTAMP_INTERRUPT;
            }
#endif /* \(DSADC_CFG_TIMESTAMP_ENABLE == STD_ON) */
        }

#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
#if (DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_ON)
        if (NULL_PTR != ChCfgPtr->HwCfgPtr->pThresholdConfig)
        {
            /* Limit checking function enabled */
            /* Limit checking function is only valid when auxiliary filter chain enabled */
            /* Enable the limit checking interrupt */
            DataPtr->IntEnBits |= (uint16)(ChCfgPtr->LimitCheckEvtBits);
        }
#endif /* \(DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_ON) */
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
    }
#else
    {
        /* Do Nothing */
    }
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */
}

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_AuxIsrEventEntry
*
*   Service ID              : None.
*
*   Description             : Process the auxiliary channel event interrupt of specified HW unit.
*
*   Parameters in           : HwUnitId: HW unit identifier.
*                             Channel: Logical channel
*                             ChCfgPtr: Pointer to the configuration information of logical
*                               channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, DSADC_PRIVATE_CODE) Dsadc_AuxIsrEventEntry
(
    Dsadc_HWUnitType HwUnitId,
    Dsadc_ChannelType Channel,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr
)
{
    uint32                        IntStatus;
    Dsadc_ChannelType             CoreChIdx;
    Mcal_CoreType                 CoreId;
#if (DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_ON)
#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
    Dsadc_ResultType              AuxResult;
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */
#endif /* \(DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_ON) */

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_OFF)
    MCAL_UNUSED_VAR(ChCfgPtr);
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_OFF) */

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    /* #Violation: Dsadc_c_REF_1 */
    CoreChIdx = DSADC_GET_CORECHIDX(Channel);

    /* Get interrupt status */
    IntStatus = Dsadc_Hal_GetInterruptStatus(Dsadc_BaseAddrs[HwUnitId]);

    /* Conversion is completed */
    if (DSADC_AUXILIARY_COMPLETED_INTERRUPT == (IntStatus & DSADC_AUXILIARY_COMPLETED_INTERRUPT))
    {
        /* If the auxiliary conversion channel completed is triggered */
        /* Clear interrupt flag */
        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId],
                                              DSADC_AUXILIARY_COMPLETED_INTERRUPT);

        DSADC_ENTER_CRITICAL_SECTION(ResultHandling);

        /* Direct read conversion result from register */
        Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChRsltBufPtr[1U] =
                                             (Dsadc_ResultType)Dsadc_Hal_GetConversionResult(
                                             Dsadc_BaseAddrs[HwUnitId],
                                             /* #Violation: Dsadc_c_REF_2 */
                                             (Dsadc_ChannelSelect)DSADC_CONV_CHANNEL_AUX);

        /* #Violation: Dsadc_c_REF_1 */
        DSADC_CHAUXSTA(CoreId, CoreChIdx) = DSADC_STREAM_COMPLETED;

        DSADC_EXIT_CRITICAL_SECTION(ResultHandling);

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
        if ((NULL_PTR != ChCfgPtr->NewRsltNotifFuncPtr) &&
            (TRUE == Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus))
        {
            /* Call result result conversion completed notification */
            ChCfgPtr->NewRsltNotifFuncPtr(DSADC_CONV_CHANNEL_AUX);
        }
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */
    }

#if (DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_ON)
    /* Conversion result above the upper limit event */
    if (DSADC_AUXILIARY_SAUL_INTERRUPT == (IntStatus & DSADC_AUXILIARY_SAUL_INTERRUPT))
    {
        /* If the FIFO interrupt is triggered */
        /* Clear interrupt flag */
        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId],
                                             DSADC_AUXILIARY_SAUL_INTERRUPT);

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
        if ((NULL_PTR != ChCfgPtr->LimitChkNotifFuncPtr) &&
            (TRUE == Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus))
        {
            /* Direct read conversion result from register */
            AuxResult =  (Dsadc_ResultType)Dsadc_Hal_GetConversionResult(
                                                 Dsadc_BaseAddrs[HwUnitId],
                                                 /* #Violation: Dsadc_c_REF_2 */
                                                 (Dsadc_ChannelSelect)DSADC_CONV_CHANNEL_AUX);
            /* Call limit checking notification */
            ChCfgPtr->LimitChkNotifFuncPtr(DSADC_RESULT_ABOVE_UPPER_LIMIT, AuxResult);
        }
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */
    }
    /* Conversion result below the lower limit event */
    else if((DSADC_AUXILIARY_SBUL_INTERRUPT == (IntStatus & DSADC_AUXILIARY_SBUL_INTERRUPT)))
    {
        /* If the FIFO interrupt is triggered */
        /* Clear interrupt flag */
        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId],
                                            DSADC_AUXILIARY_SBUL_INTERRUPT);

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
        if ((NULL_PTR != ChCfgPtr->LimitChkNotifFuncPtr) &&
            (TRUE == Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus))
        {
            /* Direct read conversion result from register */
            AuxResult =  (Dsadc_ResultType)Dsadc_Hal_GetConversionResult(
                                                 Dsadc_BaseAddrs[HwUnitId],
                                                 /* #Violation: Dsadc_c_REF_2 */
                                                 (Dsadc_ChannelSelect)DSADC_CONV_CHANNEL_AUX);
            /* Call limit checking notification */
            ChCfgPtr->LimitChkNotifFuncPtr(DSADC_RESULT_BELOW_LOWER_LIMIT, AuxResult);
        }
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */
    }
    else
    {
        /* Do Nothing */
    }
#endif /* \(DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_ON) */
}
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
/****************************************************************************************************
*   Function Name           : Dsadc_IsrEventEntry
*
*   Service ID              : None.
*
*   Description             : Process the event interrupt of specified HW unit.
*
*   Parameters in           : HwUnitId: HW unit identifier.
*                             Channel: Logical channel
*                             ChCfgPtr: Pointer to the configuration information of logical
*                               channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : TRUE: No safety error.
*                             FALSE: Safety error detected.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_IsrEventEntry
(
    Dsadc_HWUnitType HwUnitId,
    Dsadc_ChannelType Channel,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr
)
{
    boolean             SafetyErr;
    uint32              IntStatus;
    Dsadc_ResultType    RecentRslt;

    SafetyErr = TRUE;


    /* Get interrupt status */
    IntStatus = Dsadc_Hal_GetInterruptStatus(Dsadc_BaseAddrs[HwUnitId]);
    if (DSADC_EXTERNAL_TRIGGER_INTERRUPT == (IntStatus & DSADC_EXTERNAL_TRIGGER_INTERRUPT))
    {
        /* If the external interrupt is triggered */
        /* Get result then clear interrupt flag */
        RecentRslt = (Dsadc_ResultType)Dsadc_Hal_GetConversionResult(
                                                    Dsadc_BaseAddrs[HwUnitId],
                                                    /* #Violation: Dsadc_c_REF_2 */
                                                    (Dsadc_ChannelSelect)DSADC_CONV_CHANNEL_MAIN);
        /* Clear interrupt flag */
        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId], DSADC_EXTERNAL_TRIGGER_INTERRUPT);
        /* Process the main conversion channel FIFO event */
        SafetyErr = Dsadc_FifoOrExternalTriggerIsr(HwUnitId, Channel, TRUE, ChCfgPtr, RecentRslt);
    }
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    else if (DSADC_FIFO_INTERRUPT == (IntStatus & DSADC_FIFO_INTERRUPT))
    {
        /* If the FIFO interrupt is triggered */
        /* Get result then clear interrupt flag.
         * This is necessary when FIFO is used, because the interrupt flag cannot be cleared
         * successfully unless the result is read from the FIFO. */
        RecentRslt = (Dsadc_ResultType)Dsadc_Hal_GetConversionResult(
                                        Dsadc_BaseAddrs[HwUnitId],
                                        /* #Violation: Dsadc_c_REF_2 */
                                        (Dsadc_ChannelSelect)DSADC_CONV_CHANNEL_MAIN);

        /* Clear interrupt flag */
        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId], DSADC_FIFO_INTERRUPT);

        /* Process the main conversion channel FIFO event */
        SafetyErr = Dsadc_FifoOrExternalTriggerIsr(HwUnitId, Channel, FALSE, ChCfgPtr, RecentRslt);
    }
    else
    /* #Violation: Dsadc_c_REF_9 */
    {
        /* Do Nothing */
    }
#endif /* \(DSADC_CFG_INTERRUPT_MODE == STD_ON) */

#if (DSADC_CFG_TIMESTAMP_ENABLE == STD_ON)
    if (DSADC_TIMESTAMP_INTERRUPT == (IntStatus & DSADC_TIMESTAMP_INTERRUPT))
    {
        /* If the timestamp interrupt is triggered */
        /* Clear interrupt flag */
        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId], DSADC_TIMESTAMP_INTERRUPT);
        /* Process the main conversion channel timestamp event */
        Dsadc_TimestampIsr(HwUnitId, Channel, ChCfgPtr);
    }
#endif /* \(DSADC_CFG_TIMESTAMP_ENABLE == STD_ON) */

    return SafetyErr;
}
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
/****************************************************************************************************
*   Function Name           : Dsadc_FifoOrExternalTriggerIsr
*
*   Service ID              : None.
*
*   Description             : Main conversion channel FIFO interrupt processing code.
*
*   Parameters in           : HwUnitId: HW unit identifier.
*                             Channel: Logical channel.
*                             TrigMthdFlg: Interrupt trigger method. true-external event trigger;
*                                                                    false-FIFO threshold trigger.
*                             ChCfgPtr: Pointer to the configuration information of logical
*                               channel.
*                             RecentRslt: Recent result of main filter.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : TRUE: No safety error.
*                             FALSE: Safety error detected.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_FifoOrExternalTriggerIsr
(
    Dsadc_HWUnitType HwUnitId,
    Dsadc_ChannelType Channel,
    boolean TrigMthdFlg,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr,
    Dsadc_ResultType RecentRslt
)
{
    boolean                       SafetyErr;
    Dsadc_ChannelType             CoreChIdx;
    Dsadc_NumSampleType           CurrBufPos;
    Dsadc_FifoErrorStatus         FifoErr;
    Mcal_CoreType                 CoreId;

    SafetyErr = TRUE;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    /* #Violation: Dsadc_c_REF_1 */
    CoreChIdx = DSADC_GET_CORECHIDX(Channel);

    if (NULL_PTR != ChCfgPtr->HwCfgPtr->pFifoConfig)
    {
        /* Get FIFO error status */
        FifoErr = Dsadc_Hal_GetFifoErrorFlag(Dsadc_BaseAddrs[HwUnitId]);
    }
    else
    {
        FifoErr = DSADC_NOERRORFLAG;
    }

    if ((uint8)((uint8)FifoErr & (uint8)DSADC_READERROR) != (uint8)DSADC_READERROR)
    {
        if (DSADC_ACCESS_MODE_SINGLE == ChCfgPtr->RsltAccessMod)
        {
            DSADC_ENTER_CRITICAL_SECTION(ResultHandling);

#if (DSADC_CFG_TIMESTAMP_ENABLE == STD_ON)
            if ((TRUE == ChCfgPtr->TimestampEn) &&
                (DSADC_TIMESTAMPTRIGGERMODE_NONE == ChCfgPtr->HwCfgPtr->pTimeStampConfig->mode))
            {
                /* Direct read timestamp from register and save it to buffer */
                Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].Timestamp =
                        (Dsadc_TimestampType)Dsadc_Hal_GetTimeStamp(Dsadc_BaseAddrs[HwUnitId]);
            }
#endif /* \(DSADC_CFG_TIMESTAMP_ENABLE == STD_ON) */

            /* Direct read conversion result from register */
            Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChRsltBufPtr[0U] = RecentRslt;
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
            /* Auxiliary filter is enabled and External event trigger */
            if ((TRUE == ChCfgPtr->IsAuxChRsltAcqEn) && (TRUE == TrigMthdFlg))
            {
                /* Auxiliary filter result acquisition functionality */
                /* Direct read conversion result from register */
                Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChRsltBufPtr[1U] =
                                            (Dsadc_ResultType)Dsadc_Hal_GetConversionResult(
                                            Dsadc_BaseAddrs[HwUnitId],
                                            /* #Violation: Dsadc_c_REF_2 */
                                            (Dsadc_ChannelSelect)DSADC_CONV_CHANNEL_AUX);

                /* #Violation: Dsadc_c_REF_1 */
                DSADC_CHAUXSTA(CoreId, CoreChIdx) = DSADC_STREAM_COMPLETED;
            }
#else
            MCAL_UNUSED_VAR(TrigMthdFlg);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */

            /* #Violation: Dsadc_c_REF_1 */
            DSADC_CHSTA(CoreId, CoreChIdx) = DSADC_STREAM_COMPLETED;

            DSADC_EXIT_CRITICAL_SECTION(ResultHandling);
        }
        else
        {
            DSADC_ENTER_CRITICAL_SECTION(ResultHandling);

            /* Get the number of valid conversion result to find the write location to buffer */
            CurrBufPos = Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChValidRsltNum;
            if (CurrBufPos == ChCfgPtr->NumSamples)
            {
                /* Only for circular buffering */
                /* Reset index to base address */
                CurrBufPos = 0U;
            }

            /* Read Conversion result and fill the data into user buffer */
            Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChRsltBufPtr[CurrBufPos] = RecentRslt;

            /* Increment the no. of valid conversion result */
            CurrBufPos++;
            /* Update the Number of conversion result */
            Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChValidRsltNum = CurrBufPos;

            if (CurrBufPos == ChCfgPtr->NumSamples)
            {
                /* Change the status to DSADC_STREAM_COMPLETED when streaming buffer full
                 * completely */
                /* #Violation: Dsadc_c_REF_1 */
                DSADC_CHSTA(CoreId, CoreChIdx) = DSADC_STREAM_COMPLETED;

                DSADC_EXIT_CRITICAL_SECTION(ResultHandling);

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
                /* notification function is enabled and Buffer full notification is configured */
                if ((NULL_PTR != ChCfgPtr->BufFullNotifFuncPtr) &&
                    (TRUE == Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus))
                {
                    /* Call user buffer full notification */
                    ChCfgPtr->BufFullNotifFuncPtr();
                }
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */

                /* Streaming buffer with linear */
                if (DSADC_STREAM_BUFFER_LEANER == ChCfgPtr->StreamBufMod)
                {
                    DSADC_ENTER_CRITICAL_SECTION(ResultHandling);

                    /* Stop in linear buffer */
                    /* Disable all interrupts */
                    SafetyErr = Dsadc_Hal_DisableInterrupt(Dsadc_BaseAddrs[HwUnitId],
                                                               /* #Violation: Dsadc_c_REF_1 */
                                                               DSADC_CHINTBITS(CoreId, CoreChIdx));

                    if (TRUE == SafetyErr)
                    {
                        /* Clear the interrupt event flags */
                        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId],
                                                           /* #Violation: Dsadc_c_REF_1 */
                                                           DSADC_CHINTBITS(CoreId, CoreChIdx));
#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
                        /* Disable the group notification */
                        Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus = FALSE;
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */
                    }
                    DSADC_EXIT_CRITICAL_SECTION(ResultHandling);
                }
            }
            else
            {
                /* #Violation: Dsadc_c_REF_1 */
                if (DSADC_STREAM_COMPLETED != DSADC_CHSTA(CoreId, CoreChIdx))
                {
                    /* At least one conversion result generated */
                    /* #Violation: Dsadc_c_REF_1 */
                    DSADC_CHSTA(CoreId, CoreChIdx) = DSADC_COMPLETED;
                }

                DSADC_EXIT_CRITICAL_SECTION(ResultHandling);
            }
        }

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
        /* Notification function is enabled and new result notification is configured */
        if ((NULL_PTR != ChCfgPtr->NewRsltNotifFuncPtr) &&
            (TRUE == Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus))
        {
            /* Call new conversion result generated notification */
            ChCfgPtr->NewRsltNotifFuncPtr(DSADC_CONV_CHANNEL_MAIN);
        }
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */

        Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].FifoErrFlag = DSADC_NOERRORFLAG;

#if (DSADC_DEM_ERROR_REPORT_STATUS == STD_ON)
        Dem_SetEventStatus(DSADC_E_FIFO_FAILURE, DEM_EVENT_STATUS_PASSED);
#endif /* \(DSADC_DEM_ERROR_REPORT_STATUS == STD_ON) */
    }
    else
    {
        Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].FifoErrFlag = DSADC_READERROR;
#if (DSADC_DEM_ERROR_REPORT_STATUS == STD_ON)
        Dem_SetEventStatus(DSADC_E_FIFO_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif /* \(DSADC_DEM_ERROR_REPORT_STATUS == STD_ON) */
    }

    if (DSADC_NOERRORFLAG != FifoErr)
    {
        /* Clear FIFO when error occurs */
        SafetyErr &= Dsadc_Hal_ClearFifo(Dsadc_BaseAddrs[HwUnitId]);
    }

    return SafetyErr;
}
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
#if (DSADC_CFG_TIMESTAMP_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_TimestampIsr
*
*   Service ID              : None.
*
*   Description             : Main conversion channel timestamp interrupt processing code.
*
*   Parameters in           : HwUnitId: HW unit identifier.
*                             Channel: Logical channel
*                             ChCfgPtr: Pointer to the configuration information of logical
*                               channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, DSADC_PRIVATE_CODE) Dsadc_TimestampIsr
(
    Dsadc_HWUnitType HwUnitId,
    Dsadc_ChannelType Channel,
    CONSTP2CONST(Dsadc_ChannelConfigType, AUTOMATIC, DSADC_APPL_CONST) ChCfgPtr
)
{
    Dsadc_ChannelType             CoreChIdx;
    Mcal_CoreType                 CoreId;

    if (DSADC_ACCESS_MODE_SINGLE == ChCfgPtr->RsltAccessMod)
    {
        if ((TRUE == ChCfgPtr->TimestampEn) &&
                (DSADC_TIMESTAMPTRIGGERMODE_NONE != ChCfgPtr->HwCfgPtr->pTimeStampConfig->mode))
        {
            /* #Violation: Dsadc_c_REF_1 */
            CoreId = Mcal_GetCoreId();
            /* #Violation: Dsadc_c_REF_1 */
            CoreChIdx = DSADC_GET_CORECHIDX(Channel);
            /* Direct read timestamp from register and save it to buffer */
            Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].Timestamp =
                    Dsadc_Hal_GetTriggerTimeStamp(Dsadc_BaseAddrs[HwUnitId]);
        }
    }
}
#endif /* \(DSADC_CFG_TIMESTAMP_ENABLE == STD_ON) */
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */

/****************************************************************************************************
 *   Function Name           : Dsadc_InitChannel
 *
 *   Service ID              : None.
 *
 *   Description             : Initialize the a DSADC channel.
 *
 *   Parameters in           : ConfigPtr: Pointer to configuration set in Variant PB.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : TRUE: No safety error.
 *                             FALSE: Safety error detected.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_InitChannel
(
    CONSTP2CONST(Dsadc_ConfigType, AUTOMATIC, DSADC_APPL_CONST) ConfigPtr,
    Mcal_CoreType CoreId,
    Dsadc_ChannelType ChIdx
)
{
    boolean                       SafetyErr;
    const Dsadc_ChannelConfigType *ChCfgPtr;
    Dsadc_GlobalDataType          *DataPtr;

    /* #Violation: Dsadc_c_REF_1 */
    ChCfgPtr = &ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChIdx];
    /* Initialize the DSADC driver */
    SafetyErr =
        Dsadc_Hal_InitModule(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId], ChCfgPtr->HwCfgPtr);

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
    /* Only for THA6412 */
    SafetyErr &=
    /* #Violation: Dsadc_c_REF_2 */
        Dsadc_Hal_ConfigDsadc1InPort((Dsadc_InputPortSelect)ConfigPtr->Dsadc1InputPin);
#endif /* \(MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
    /* setting the dithering */
    SafetyErr &= Dsadc_Hal_EnableDithering(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId],
                                                        ChCfgPtr->IsMdlDitheringEn);

    /* Enable the DC compensation */
    SafetyErr &= Dsadc_Hal_BypassDcCompensation(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId], 0U);
    /* Enable the gain compensation */
    SafetyErr &=
            Dsadc_Hal_BypassGainCompensation(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId], 0U);

    if (NULL_PTR != ChCfgPtr->CalibCompConfigPtr)
    {
        /* When auto calibration is not used, set the compensation parameters */
        SafetyErr &= Dsadc_Hal_ConfigCompensation(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId],
                                                        ChCfgPtr->CalibCompConfigPtr);
    }

    if (TRUE == ChCfgPtr->IsCommonModeVoltEn)
    {
        /* Configure the common mode voltage */
        SafetyErr &= Dsadc_Hal_ConfigBiasVoltage(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId],
                                    ChCfgPtr->CommonModeVoltLevel,
                                    TRUE);
    }

    /* Close DSADC reset */
    SafetyErr &= Dsadc_Hal_CloseLoop(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId]);

    /* Initialize the global variables */
    DataPtr = &Dsadc_CoreDataSetPtr[CoreId][ChIdx];
    /* Result result buffer */
    DataPtr->ChRsltBufPtr = NULL_PTR;
    DataPtr->ChValidRsltNum = 0U;
    DataPtr->FifoErrFlag = DSADC_NOERRORFLAG;
    DataPtr->ChStatus = DSADC_IDLE;
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    DataPtr->ChAuxStatus = DSADC_IDLE;
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
    DataPtr->ChNotifStatus = FALSE;
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */
    DataPtr->IntEnBits = 0U;

    /* Only set the interrupt flag when interrupt or DMA result handling mode */
    Dsadc_SetInterruptEnStatus(DataPtr, ChCfgPtr);

    return SafetyErr;
}

/****************************************************************************************************
 *   Function Name           : Dsadc_InitMasterCore
 *
 *   Service ID              : None.
 *
 *   Description             : Initialize the global resources in master core.
 *
 *   Parameters in           : ConfigPtr: Pointer to configuration set in Variant PB.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : TRUE: No safety error.
 *                             FALSE: Safety error detected.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(boolean, DSADC_PRIVATE_CODE) Dsadc_InitMasterCore
(
    CONSTP2CONST(Dsadc_ConfigType, AUTOMATIC, DSADC_APPL_CONST) ConfigPtr
)
{
    boolean SafetyErr;
    uint16  HwUnitEnBits;

    /* global configuration can only be enabled in master core */
    /* Enable or disable the clock sync mode for all DSADC */
    SafetyErr = Dsadc_Hal_SetSyncMode(DSADC_CFG_CLOCKSYNC_ENABLE);
    /* Enable or disable the integrator functionality */
    SafetyErr &= Dsadc_Hal_SetIntegratorState(DSADC_CFG_INTEGRATOR_ENABLE);

    /* Enable the modulator and demodulator */
    HwUnitEnBits = (uint16)((ConfigPtr->GlobalCfgPtr->HWUnitEnBits &
                            DSADC_HWUNIT_EN_HIGH_BITS_MASK) >>
                            DSADC_HWUNIT_EN_HIGH_BITS_SHIFT);
    HwUnitEnBits |= (uint16)ConfigPtr->GlobalCfgPtr->HWUnitEnBits &
                            DSADC_HWUNIT_EN_LOW_BITS_MASK;
    SafetyErr &= Dsadc_Hal_EnableModuleSync(HwUnitEnBits);

#if (DSADC_CFG_INIT_SYNC_ENABLE_HWUNIT == STD_ON)
    /* Enable main filter chain for each HW units */
    SafetyErr &= Dsadc_Hal_EnableMainChannelSync(ConfigPtr->GlobalCfgPtr->HWUnitEnBits);
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    /* Enable auxiliary filter chain for each HW units */
    SafetyErr &=
            Dsadc_Hal_EnableAuxChannelSync(ConfigPtr->GlobalCfgPtr->AuxFltrHwUnitEnBits);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
#endif /* \(DSADC_CFG_INIT_SYNC_ENABLE_HWUNIT == STD_ON) */

    if (NULL_PTR != ConfigPtr->GlobalCfgPtr->CarrierCfgPtr)
    {
        /* Configure the carrier generator */
        SafetyErr &= Dsadc_Hal_ConfigCarrierWave(ConfigPtr->GlobalCfgPtr->CarrierCfgPtr);
    }

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    /* Carrier signal status */
    Dsadc_CarrierStatus = DSADC_CARRIER_SIGNAL_STOP;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

#if (DSADC_SAFETY_ENABLE == STD_ON)
    if (TRUE == SafetyErr)
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */
    {
        /* Store ConfigPtr to use for other APIs when 'Dsadc_ConfigPtr' is not NULL */
        Dsadc_ConfigPtr = ConfigPtr;
    }

    return SafetyErr;
}

#if ((DSADC_CFG_GETSTREAMLASTPOINTER_API == STD_ON) && (DSADC_DEV_ERROR_DETECT == STD_ON))
/****************************************************************************************************
 *   Function Name           : Dsadc_GetStreamLastPointerErrCheck
 *
 *   Service ID              : None.
 *
 *   Description             : Check the error status of API Dsadc_GetStreamLastPointer.
 *
 *   Parameters in           : CoreId: Core ID.
 *                             CoreChIdx: Channel index in Core.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : E_OK: No DET check error.
 *                             E_NOT_OK: DET check error exists.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Std_ReturnType, DSADC_PRIVATE_CODE) Dsadc_GetStreamLastPointerErrCheck
(
    Mcal_CoreType CoreId,
    Dsadc_ChannelType CoreChIdx
)
{
    boolean                       RetErr;
    const Dsadc_ChannelConfigType *ChCfgPtr;

    /* Get the configuration information of logical channel */
    /* #Violation: Dsadc_c_REF_1 */
    ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);

#if (DSADC_CFG_DMA_MODE == STD_ON)
    if (DSADC_RESULT_HANDLING_DMA_MODE == ChCfgPtr->RsltHldMthd)
    {
        /* This API is not allowed in DMA mode */
        Dsadc_ReportError(DSADC_SID_GETSTREAMLASTPOINTER, DSADC_E_DMA_ENABLED);
        RetErr = E_NOT_OK;
    }
    else
#endif /* \(DSADC_CFG_DMA_MODE == STD_ON) */
    if (DSADC_ACCESS_MODE_SINGLE == ChCfgPtr->RsltAccessMod)
    {
        /* The pointer to store the conversion result is  NULL */
        Dsadc_ReportError(DSADC_SID_GETSTREAMLASTPOINTER, DSADC_E_SINGLE_ENABLED);
        RetErr = E_NOT_OK;
    }
    else if (NULL_PTR == Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChRsltBufPtr)
    {
        /* The pointer to store the conversion result is  NULL */
        Dsadc_ReportError(DSADC_SID_GETSTREAMLASTPOINTER, DSADC_E_BUFFER_UNINIT);
        RetErr = E_NOT_OK;
    }
    else
    /* #Violation: Dsadc_c_REF_9 */
    {
        RetErr = E_OK;
    }

    return RetErr;
}
#endif /* \((DSADC_CFG_GETSTREAMLASTPOINTER_API == STD_ON) && (DSADC_DEV_ERROR_DETECT == STD_ON)) */

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
*   Function Name           : Dsadc_Init
*
*   Service ID              : 0x00
*
*   Description             : Initializes the DSADC hardware units and driver.
*
*   Parameters in           : ConfigPtr: Pointer to configuration set in Variant PB.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Dsadc driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_Init
(
    CONSTP2CONST(Dsadc_ConfigType, AUTOMATIC, DSADC_APPL_CONST) ConfigPtr
)
{
    boolean                       SafetyErr;
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                Err;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    Dsadc_ChannelType             ChIdx;
    Mcal_CoreType                 CoreId;
    
    SafetyErr = TRUE;

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Err = Dsadc_CheckInitParam(ConfigPtr);
    if (E_OK == Err)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get core id which core is currently executing */
        /* #Violation: Dsadc_c_REF_1 */
        CoreId = Mcal_GetCoreId();

        /* Determine whether the main core has configuration data */
        if (NULL_PTR != ConfigPtr->CoreConfigPtr[CoreId])
        {
            /* Initialize the configured resources */
            for (ChIdx = 0U; ((ChIdx < ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreChannel) &&
                    (TRUE == SafetyErr)); ChIdx++)
            {
                SafetyErr &= Dsadc_InitChannel(ConfigPtr, CoreId, ChIdx);
            }
        }

        if (MCAL_MASTER_CORE == CoreId)
        {
            SafetyErr &= Dsadc_InitMasterCore(ConfigPtr);
        }

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
#if (DSADC_SAFETY_ENABLE == STD_ON)
        if (TRUE == SafetyErr)
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */
        {
            *(Dsadc_CoreInitStatusSetPtr[CoreId]) = DSADC_INITIALIZED;
        }
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    }

#if (DSADC_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dsadc_ReportRuntimeError(DSADC_SID_INIT);
    }
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */
}

#if (DSADC_CFG_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_DeInit
*
*   Service ID              : 0x01
*
*   Description             : Returns all DSADC HW Units to a state comparable to their power
*                             on reset state.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Dsadc driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DeInit
(
    void
)
{
    boolean                       SafetyErr;
    Std_ReturnType                Err;
    Dsadc_ChannelType             ChIdx;
    const Dsadc_ChannelConfigType *ChCfgPtr;
    Mcal_CoreType                 CoreId;

    SafetyErr = TRUE;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Err = Dsadc_CheckDeInit(CoreId);
    if (E_OK == Err)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Running status judge */
        Err = Dsadc_CheckAllChannelStatus();
        if (E_OK == Err)
        {
            /* Determine whether the main core has configuration data */
            if (NULL_PTR != Dsadc_ConfigPtr->CoreConfigPtr[CoreId])
            {
                for (ChIdx = 0U;
                        /* #Violation: Dsadc_c_REF_1 */
                        ((ChIdx < DSADC_GET_COREMAXCH(CoreId)) && (TRUE == SafetyErr)); ChIdx++)
                {
                    /* Get configuration of current channel */
                    /* #Violation: Dsadc_c_REF_1 */
                    ChCfgPtr = DSADC_GET_CHCFG(CoreId, ChIdx);
                    if (0U != ChCfgPtr->HwUnitId)
                    {
                        /* #Violation: Dsadc_c_REF_11 */
                        SafetyErr &= Dsadc_DeInitChannel(ChCfgPtr->HwUnitId);
                    }
                    /* Reset channel status */
                    /* #Violation: Dsadc_c_REF_1 */
                    DSADC_CHSTA(CoreId, ChIdx) = DSADC_IDLE;
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
                    /* #Violation: Dsadc_c_REF_1 */
                    DSADC_CHAUXSTA(CoreId, ChIdx) = DSADC_IDLE;
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
                }
            }

            if (MCAL_MASTER_CORE == CoreId)
            {
                SafetyErr &= Dsadc_DeInitChannel(0U);

#if (DSADC_SAFETY_ENABLE == STD_ON)
                if (TRUE == SafetyErr)
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */
                {
                    /* De-initialize the global variables */
                    Dsadc_ConfigPtr = NULL_PTR;
                }
            }

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
#if (DSADC_SAFETY_ENABLE == STD_ON)
            if (TRUE == SafetyErr)
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */
            {
                *(Dsadc_CoreInitStatusSetPtr[CoreId]) = DSADC_UNINITIALIZE;
            }
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
        }
    }

#if (DSADC_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dsadc_ReportRuntimeError(DSADC_SID_DEINIT);
    }
#else
    MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */
}
#endif /* \(ADC_DEINIT_API == STD_ON) */

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
/****************************************************************************************************
*   Function Name           : Dsadc_SetupResultBuffer
*
*   Service ID              : 0x02
*
*   Description             : Initializes DSADC driver with the channel specific result buffer start
*                             address where the conversion results will be stored. The application
*                             has to ensure that the application buffer, where DataBufferPtr points
*                             to, can hold all the conversion results of the specified group. The
*                             initialization with Dsadc_SetupResultBuffer is required after reset,
*                             before a modulation can be started.
*
*   Parameters in           : Channel: Numeric ID of requested logical channel.
*                             DataBufferPtr: Pointer to result data buffer.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK:  result buffer pointer initialized correctly
*                             E_NOT_OK: operation failed or development error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00419.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_SetupResultBuffer
(
    Dsadc_ChannelType Channel,
    /* #Violation: Dsadc_c_REF_6 */
    CONSTP2VAR(Dsadc_ResultType, AUTOMATIC, DSADC_APPL_DATA) DataBufferPtr
)
{
    Std_ReturnType                 RetErr;
    Dsadc_ChannelType              CoreChIdx;
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
#if (DSADC_CFG_DMA_MODE == STD_ON)
    const Dsadc_ChannelConfigType *ChCfgPtr;
#endif /* \(DSADC_CFG_DMA_MODE == STD_ON) */
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    Mcal_CoreType                  CoreId;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    RetErr = Dsadc_CheckInit(DSADC_SID_SETUPRESULTBUFFER, CoreId);
    if (E_OK == RetErr)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

        /* Get channel index in current core */
        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(Channel);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        if (NULL_PTR == DataBufferPtr)
        {
            /* User data buffer is NULL */
            Dsadc_ReportError(DSADC_SID_SETUPRESULTBUFFER, DSADC_E_PARAM_POINTER);
            RetErr = E_NOT_OK;
        }
        else
        {
            RetErr = Dsadc_CheckMulticoreAllocateError(DSADC_SID_SETUPRESULTBUFFER, Channel);
            if (E_OK == RetErr)
            {
#if (DSADC_CFG_DMA_MODE == STD_ON)
                /* Get channel configuration information */
                /* #Violation: Dsadc_c_REF_1 */
                ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);
                if (DSADC_RESULT_HANDLING_DMA_MODE == ChCfgPtr->RsltHldMthd)
                {
                    /* Call to this function is not allowed in DMA mode */
                    Dsadc_ReportError(DSADC_SID_SETUPRESULTBUFFER, DSADC_E_DMA_ENABLED);

                    RetErr = E_NOT_OK;
                }
#endif /* \(DSADC_CFG_DMA_MODE == STD_ON) */
            }
        }
    }

    if (E_OK == RetErr)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* #Violation: Dsadc_c_REF_1 */
        if ((DSADC_IDLE == DSADC_CHSTA(CoreId, CoreChIdx))
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
            /* #Violation: Dsadc_c_REF_1 */
            && (DSADC_IDLE == DSADC_CHAUXSTA(CoreId, CoreChIdx))
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
        )
        {
            /* Clear the valid conversion result number */
            Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChValidRsltNum = 0U;
            /* Pointer to the user data buffer */
            Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChRsltBufPtr = DataBufferPtr;

            RetErr = E_OK;
        }
        else
        {
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
            /* Setup buffer must in IDLE status */
            Dsadc_ReportError(DSADC_SID_SETUPRESULTBUFFER, DSADC_E_BUSY);
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
            RetErr = E_NOT_OK;
        }
    }

    return RetErr;
}
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON)) */

/****************************************************************************************************
*   Function Name           : Dsadc_StartConversion
*
*   Service ID              : 0x03
*
*   Description             : Starts the conversion of requested channels.
*
*   Parameters in           : Channel: Numeric ID of requested logical channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Reentrant for different channel, Non-reentrant for same channel.
*
*   Return value            : E_OK:  result buffer pointer initialized correctly
*                             E_NOT_OK: operation failed or development error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_StartConversion
(
    Dsadc_ChannelType Channel
)
{
    boolean                        SafetyErr;
    Std_ReturnType                 RetErr;
    Dsadc_ChannelType              CoreChIdx;
    const Dsadc_ChannelConfigType *ChCfgPtr;
    Mcal_CoreType                  CoreId;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    RetErr = Dsadc_CheckInit(DSADC_SID_STARTCONVERSION, CoreId);
    if (E_OK == RetErr)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(Channel);
        /* Get the configuration information of logical channel */
        /* #Violation: Dsadc_c_REF_1 */
        ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        RetErr = Dsadc_CheckMulticoreAllocateError(DSADC_SID_STARTCONVERSION, Channel);
        if (E_OK == RetErr)
        {
#if (DSADC_CFG_DMA_MODE == STD_ON)
            if (DSADC_RESULT_HANDLING_DMA_MODE != ChCfgPtr->RsltHldMthd)
#endif /* \(DSADC_CFG_DMA_MODE == STD_ON) */
            {
                /* Not in DMA mode */
                if (NULL_PTR == Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChRsltBufPtr)
                {
                    /* The pointer to store the conversion result is  NULL */
                    Dsadc_ReportError(DSADC_SID_STARTCONVERSION, DSADC_E_BUFFER_UNINIT);
                    RetErr = E_NOT_OK;
                }
            }
        }
    }

    if (E_OK == RetErr)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Enter Critical section */
        DSADC_ENTER_CRITICAL_SECTION(StartConversion);

        /* #Violation: Dsadc_c_REF_1 */
        if (((DSADC_IDLE == DSADC_CHSTA(CoreId, CoreChIdx)) ||
                /* #Violation: Dsadc_c_REF_1 */
                (DSADC_STREAM_COMPLETED == DSADC_CHSTA(CoreId, CoreChIdx)))
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
            /* #Violation: Dsadc_c_REF_1 */
            && ((DSADC_IDLE == DSADC_CHAUXSTA(CoreId, CoreChIdx)) ||
                    /* #Violation: Dsadc_c_REF_1 */
                    (DSADC_STREAM_COMPLETED == DSADC_CHAUXSTA(CoreId, CoreChIdx)))
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
        )
        {
            /* Reset valid sample number */
            Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChValidRsltNum = 0U;

#if (DSADC_CFG_DMA_MODE == STD_ON)
            /* Do nothing in DMA mode */
            if (DSADC_RESULT_HANDLING_DMA_MODE != ChCfgPtr->RsltHldMthd)
#endif /* \(DSADC_CFG_DMA_MODE == STD_ON) */
            {
                Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].FifoErrFlag = DSADC_NOERRORFLAG;
                /* Clear the interrupt event flags */
                Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId],
                                               /* #Violation: Dsadc_c_REF_1 */
                                               DSADC_CHINTBITS(CoreId, CoreChIdx));
            }

            /* Check and clear the FIFO error status */
            SafetyErr = Dsadc_Hal_ClearFifo(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId]);

            /* Enable the interrupt or DMA */
            /* #Violation: Dsadc_c_REF_1 */
            SafetyErr &= Dsadc_Hal_EnableInterrupt(Dsadc_BaseAddrs[ChCfgPtr->HwUnitId],
                                                   /* #Violation: Dsadc_c_REF_1 */
                                                   DSADC_CHINTBITS(CoreId, CoreChIdx));

            if (TRUE == SafetyErr)
            {
                /* Set the main conversion channel status to busy */
                /* #Violation: Dsadc_c_REF_1 */
                DSADC_CHSTA(CoreId, CoreChIdx) = DSADC_BUSY;

#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
                if (DSADC_ACCESS_MODE_SINGLE == ChCfgPtr->RsltAccessMod)
                {
                    /* Set the auxiliary conversion channel status to busy */
                    /* #Violation: Dsadc_c_REF_1 */
                    DSADC_CHAUXSTA(CoreId, CoreChIdx) = DSADC_BUSY;
                }
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */

                /* Exit Critical section */
                DSADC_EXIT_CRITICAL_SECTION(StartConversion);

                RetErr = E_OK;
            }
            else
            {
                /* Exit Critical section */
                DSADC_EXIT_CRITICAL_SECTION(StartConversion);

#if (DSADC_SAFETY_ENABLE == STD_ON)
                /* Report the safety check error */
                Dsadc_ReportRuntimeError(DSADC_SID_STARTCONVERSION);
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */

                RetErr = E_NOT_OK;
            }
        }
        else
        {
            /* Exit Critical section */
            DSADC_EXIT_CRITICAL_SECTION(StartConversion);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
            /* The given channel is in BUSY status */
            Dsadc_ReportError(DSADC_SID_STARTCONVERSION, DSADC_E_BUSY);
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

            RetErr = E_NOT_OK;
        }
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Dsadc_StopConversion
*
*   Service ID              : 0x04
*
*   Description             : Stop the conversion of requested channel.
*
*   Parameters in           : Channel: Numeric ID of requested logical channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant for different channel, Non-reentrant for same channel.
*
*   Return value            : E_OK:  result buffer pointer initialized correctly
*                             E_NOT_OK: operation failed or development error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00419.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_StopConversion
(
    Dsadc_ChannelType Channel
)
{
    boolean                        SafetyErr;
    Std_ReturnType                 RetErr;
    Dsadc_ChannelType              CoreChIdx;
    Mcal_CoreType                  CoreId;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    RetErr = Dsadc_CheckInit(DSADC_SID_STOPCONVERSION, CoreId);
    if (E_OK == RetErr)
    {
        RetErr = Dsadc_CheckMulticoreAllocateError(DSADC_SID_STOPCONVERSION, Channel);
    }

    if (E_OK == RetErr)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(Channel);

        /* Enter Critical section */
        DSADC_ENTER_CRITICAL_SECTION(StopConversion);

        /* #Violation: Dsadc_c_REF_1 */
        if ((DSADC_IDLE != DSADC_CHSTA(CoreId, CoreChIdx))
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
            /* #Violation: Dsadc_c_REF_1 */
            || (DSADC_IDLE != DSADC_CHAUXSTA(CoreId, CoreChIdx))
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
            )
        {
            /* Disable all interrupts */
            /* #Violation: Dsadc_c_REF_1 */
            SafetyErr = Dsadc_Hal_DisableInterrupt(Dsadc_BaseAddrs[DSADC_GET_HWOFCH(Channel)],
                                                   /* #Violation: Dsadc_c_REF_1 */
                                                   DSADC_CHINTBITS(CoreId, CoreChIdx));

            if (TRUE == SafetyErr)
            {
                /* Clear the interrupt event flags */
                /* #Violation: Dsadc_c_REF_1 */
                Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[DSADC_GET_HWOFCH(Channel)],
                                                   /* #Violation: Dsadc_c_REF_1 */
                                                   DSADC_CHINTBITS(CoreId, CoreChIdx));

                /* Reset the main channel status */
                /* #Violation: Dsadc_c_REF_1 */
                DSADC_CHSTA(CoreId, CoreChIdx) = DSADC_IDLE;

#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
                /* result the auxiliary conversion channel status */
                /* #Violation: Dsadc_c_REF_1 */
                DSADC_CHAUXSTA(CoreId, CoreChIdx) = DSADC_IDLE;
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
                /* Disable the group notification */
                Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus = FALSE;
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */

                /* Enter Critical section */
                DSADC_EXIT_CRITICAL_SECTION(StopConversion);

                RetErr = E_OK;
            }
            else
            {
                /* Enter Critical section */
                DSADC_EXIT_CRITICAL_SECTION(StopConversion);

#if (DSADC_SAFETY_ENABLE == STD_ON)
                /* Report the safety check error */
                Dsadc_ReportRuntimeError(DSADC_SID_STOPCONVERSION);
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */

                 RetErr = E_NOT_OK;
            }
        }
        else
        {
            /* Enter Critical section */
            DSADC_EXIT_CRITICAL_SECTION(StopConversion);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
            /* The given channel is in BUSY status */
            Dsadc_ReportError(DSADC_SID_STOPCONVERSION, DSADC_E_IDLE);
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

            RetErr = E_NOT_OK;
        }
    }

    return RetErr;
}

#if (DSADC_CFG_GETSTREAMLASTPOINTER_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_GetStreamLastPointer
*
*   Service ID              : 0x05
*
*   Description             : Returns the number of valid samples per channel, stored in the result
*                             buffer. Reads a pointer, pointing to a position in the channel result
*                             buffer. With the pointer position, the results of all channels
*                             of the last completed conversion round can be accessed.
*                             With the pointer and the return value, all valid group conversion
*                             results can be accessed (the user has to take the layout of the result
*                             buffer into account).
*
*   Parameters in           : Channel: Numeric ID of requested logical channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : PtrToSamplePtr: Pointer to result buffer pointer.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Number of valid samples.
*
*   Preconditions           : Channel is working in streaming access mode.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(Dsadc_NumSampleType, DSADC_PUBLIC_CODE) Dsadc_GetStreamLastPointer
(
    Dsadc_ChannelType Channel,
    /* #Violation: Dsadc_c_REF_6 */
    P2P2VAR(Dsadc_ResultType, AUTOMATIC, DSADC_APPL_DATA) const PtrToSamplePtr
)
{
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                 RetErr;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    Dsadc_ChannelType              CoreChIdx;
    Dsadc_StatusType               ChStatus;
    Dsadc_NumSampleType            ValidNum;
    Dsadc_FifoErrorStatus          FifoErr;
    Mcal_CoreType                  CoreId;
    const Dsadc_ChannelConfigType  *ChCfgPtr;

    ValidNum = 0U;
#if (DSADC_DEM_ERROR_REPORT_STATUS == STD_ON)
    FifoErr = DSADC_NOERRORFLAG;
#endif /* \(DSADC_DEM_ERROR_REPORT_STATUS == STD_ON) */

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    RetErr = Dsadc_CheckInit(DSADC_SID_GETSTREAMLASTPOINTER, CoreId);
    if (E_OK == RetErr)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

        /* Get the index of the channel in current core */
        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(Channel);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        if (NULL_PTR == PtrToSamplePtr)
        {
            /* User buffer is NULL */
            Dsadc_ReportError(DSADC_SID_GETSTREAMLASTPOINTER, DSADC_E_PARAM_POINTER);
            RetErr = E_NOT_OK;
        }
        else
        {
            RetErr = Dsadc_CheckMulticoreAllocateError(DSADC_SID_GETSTREAMLASTPOINTER, Channel);
            if (E_OK == RetErr)
            {
                RetErr = Dsadc_GetStreamLastPointerErrCheck(CoreId, CoreChIdx);
            }
        }
    }

    if (E_OK == RetErr)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Default pointer to the BULL_PTR */
        *PtrToSamplePtr = (Dsadc_ResultType*)NULL_PTR;
        /* Get the configuration information of logical channel */
        /* #Violation: Dsadc_c_REF_1 */
        ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);

        DSADC_ENTER_CRITICAL_SECTION(GetStreamLastPointer);

        /* Get the channel status */
        /* #Violation: Dsadc_c_REF_1 */
        ChStatus = DSADC_CHSTA(CoreId, CoreChIdx);
        if ((DSADC_COMPLETED == ChStatus) || (DSADC_STREAM_COMPLETED == ChStatus))
        {
            /* Get FIFO error status */
            FifoErr = Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].FifoErrFlag;
            if (DSADC_NOERRORFLAG == FifoErr)
            {
                /* Get valid number of request main conversion channel */
                ValidNum = Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChValidRsltNum;
                /* Pointer the latest conversion result to User buffer */
                *PtrToSamplePtr = &Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].
                                       ChRsltBufPtr[ValidNum - 1U];

                /* Change the channel status to BUSY */
                /* #Violation: Dsadc_c_REF_1 */
                DSADC_CHSTA(CoreId, CoreChIdx) = DSADC_BUSY;

                if (DSADC_STREAM_COMPLETED == ChStatus)
                {
                    /* Buffer full */
                    ValidNum = ChCfgPtr->NumSamples;
                    if (DSADC_STREAM_BUFFER_LEANER == ChCfgPtr->StreamBufMod)
                    {
                        /* Change the channel status to IDLE */
                        /* #Violation: Dsadc_c_REF_1 */
                        DSADC_CHSTA(CoreId, CoreChIdx) = DSADC_IDLE;
                    }
                }
            }
        }

        DSADC_EXIT_CRITICAL_SECTION(GetStreamLastPointer);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        if (DSADC_IDLE == ChStatus)
        {
            /* API Dsadc_StartConversion not called */
            Dsadc_ReportError(DSADC_SID_GETSTREAMLASTPOINTER, DSADC_E_IDLE);
        }
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    }

#if (DSADC_DEM_ERROR_REPORT_STATUS == STD_ON)
    /* DEM is enabled */
    if (DSADC_NOERRORFLAG == FifoErr)
    {
        /* No FIFO error exists or the error restored */
        Dem_SetEventStatus(DSADC_E_FIFO_FAILURE, DEM_EVENT_STATUS_PASSED);
    }
    else
    {
        /* FIFO error exists to report DEM error */
        Dem_SetEventStatus(DSADC_E_FIFO_FAILURE, DEM_EVENT_STATUS_FAILED);
    }
#endif /* \(DSADC_DEM_ERROR_REPORT_STATUS == STD_ON) */

    return ValidNum;
}
#endif /* \(DSADC_CFG_GETSTREAMLASTPOINTER_API == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dsadc_GetChannelStatus
*
*   Service ID              : 0x06
*
*   Description             : Get the current status of specified channel.
*
*   Parameters in           : Channel: Numeric ID of requested logical channel.
*                             ConvChannel: Main channel or auxiliary channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Conversion status for the requested channel.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(Dsadc_StatusType, DSADC_PUBLIC_CODE) Dsadc_GetChannelStatus
(
    Dsadc_ChannelType Channel,
    Dsadc_ConvChannelType ConvChannel
)
{
#if (DSADC_CFG_POLLING_MODE == STD_ON)
    boolean                        SafetyErr;
    Dsadc_ResultStatus             RsltStatus;
    Dsadc_ResultType               RecentRslt;
#endif /* \#if (DSADC_CFG_POLLING_MODE == STD_ON) */
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                 Err;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    Dsadc_ChannelType              CoreChIdx;
    Dsadc_StatusType               RetStatus;
    Mcal_CoreType                  CoreId;
    const Dsadc_ChannelConfigType  *ChCfgPtr;

#if (DSADC_CFG_POLLING_MODE == STD_ON)
    SafetyErr = TRUE;
#endif /* \(DSADC_CFG_POLLING_MODE == STD_ON) */

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    RetStatus = DSADC_IDLE;

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Err = Dsadc_CheckInit(DSADC_SID_GETSTATUS, CoreId);
    if (E_OK == Err)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */    

        /* Get the index of the channel in current core */
        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(Channel);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        Err = Dsadc_CheckMulticoreAllocateError(DSADC_SID_GETSTATUS, Channel);
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
        if (E_OK == Err)
        {
            if (DSADC_CONV_CHANNEL_AUX == ConvChannel)
            {
                /* Get the configuration information of logical channel */
                /* #Violation: Dsadc_c_REF_1 */
                ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);
                if (NULL_PTR == ChCfgPtr->HwCfgPtr->pAuxiliaryFilterConfig)
                {
                    /* Auxiliary filter is not configured */
                    Dsadc_ReportError(DSADC_SID_GETSTATUS, DSADC_E_AUX_FILTER_DISABLED);
                    Err = E_NOT_OK;
                }
#if (DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_OFF)
                else if (FALSE == ChCfgPtr->IsAuxChRsltAcqEn)
                {
                    /* The auxiliary filter value acquisition function is not enabled and
                     * the threshold detection function is not enabled */
                    Dsadc_ReportError(DSADC_SID_GETSTATUS, DSADC_E_AUX_RESULT_DISABLED);
                    Err = E_NOT_OK;
                }
                else
                /* #Violation: Dsadc_c_REF_9 */
                {
                    /* Do Nothing */
                }
#endif /* \(DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_OFF) */
            }
        }
#else /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
        MCAL_UNUSED_VAR(ConvChannel);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
    }

    if (E_OK == Err)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get the configuration information of logical channel */
        /* #Violation: Dsadc_c_REF_1 */
        ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);

#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
        if (DSADC_CONV_CHANNEL_AUX == ConvChannel)
        {
#if (DSADC_CFG_POLLING_MODE == STD_ON)
            if (DSADC_RESULT_HANDLING_POLLING_MODE == ChCfgPtr->RsltHldMthd)
            {
                /* Used for loop the auxiliary filter chain result or limit checking event,
                 * and refresh the auxiliary filter chain status */
                Dsadc_AuxIsrEventEntry(DSADC_GET_HWOFCH(Channel), Channel, ChCfgPtr);
            }
#endif /* \(DSADC_CFG_POLLING_MODE == STD_ON) */

            DSADC_ENTER_CRITICAL_SECTION(GetChannelStatus);
            /* Read and return current status of auxiliary conversion channel
             * of given logic channel */
            /* #Violation: Dsadc_c_REF_1 */
            RetStatus = DSADC_CHAUXSTA(CoreId, CoreChIdx);
        }
        else
#else /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
        MCAL_UNUSED_VAR(ConvChannel);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
        {
#if (DSADC_CFG_POLLING_MODE == STD_ON)
            if (DSADC_RESULT_HANDLING_POLLING_MODE == ChCfgPtr->RsltHldMthd)
            {
                if (DSADC_SERVICEREQUEST_NONE == ChCfgPtr->HwCfgPtr->pMainFilterConfig->request)
                {
                    RetStatus = DSADC_CHSTA(CoreId, CoreChIdx);
                    if (DSADC_IDLE != RetStatus)
                    {
                        if (!((DSADC_STREAM_COMPLETED == RetStatus) &&
                            (DSADC_STREAM_BUFFER_LEANER == ChCfgPtr->StreamBufMod)))
                        {
                            /* If no request, indicate that both FIFO and external
                             * trigger are not used */
                            RsltStatus = Dsadc_Hal_GetMainResultStatus(
                                                        Dsadc_BaseAddrs[DSADC_GET_HWOFCH(Channel)]);
                            if (DSADC_RESULTVALID == RsltStatus)
                            {
                                RecentRslt = (Dsadc_ResultType)Dsadc_Hal_GetConversionResult(
                                                       Dsadc_BaseAddrs[DSADC_GET_HWOFCH(Channel)],
                                                       /* #Violation: Dsadc_c_REF_2 */
                                                       (Dsadc_ChannelSelect)DSADC_CONV_CHANNEL_MAIN);
                                /* Process the main conversion channel FIFO event */
                                SafetyErr = Dsadc_FifoOrExternalTriggerIsr(DSADC_GET_HWOFCH(Channel),
                                                               Channel, FALSE, ChCfgPtr, RecentRslt);
                            }
                        }
                    }
                }
                else
                {
                    /* Used for loop the main filter chain result or timestamp value,
                     * and refresh the main filter chain status */
                    SafetyErr = Dsadc_IsrEventEntry(DSADC_GET_HWOFCH(Channel), Channel, ChCfgPtr);
                }
            }
#endif /* \(DSADC_CFG_POLLING_MODE == STD_ON) */

            DSADC_ENTER_CRITICAL_SECTION(GetChannelStatus);
            /* Read and return current status of main conversion channel
             * of given logic channel */
            /* #Violation: Dsadc_c_REF_1 */
            RetStatus = DSADC_CHSTA(CoreId, CoreChIdx);
        }

#if (DSADC_CFG_POLLING_MODE == STD_ON)
        if (FALSE == SafetyErr)
        {
            DSADC_EXIT_CRITICAL_SECTION(GetChannelStatus);

#if (DSADC_SAFETY_ENABLE == STD_ON)
            /* Report the safety check error */
            Dsadc_ReportRuntimeError(DSADC_SID_GETSTATUS);
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */
        }
        else
#endif /* \(DSADC_CFG_POLLING_MODE == STD_ON) */
        {
            if (DSADC_ACCESS_MODE_SINGLE == ChCfgPtr->RsltAccessMod)
            {
                if ((DSADC_COMPLETED == RetStatus) || (DSADC_STREAM_COMPLETED == RetStatus))
                {
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
                    if (DSADC_CONV_CHANNEL_AUX == ConvChannel)
                    {
                        /* Change the channel status to BUSY */
                        /* #Violation: Dsadc_c_REF_1 */
                        DSADC_CHAUXSTA(CoreId, CoreChIdx) = DSADC_BUSY;
                    }
                    else
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
                    {
                        /* Change the channel status to BUSY */
                        /* #Violation: Dsadc_c_REF_1 */
                        DSADC_CHSTA(CoreId, CoreChIdx) = DSADC_BUSY;
                    }
                }
            }

            DSADC_EXIT_CRITICAL_SECTION(GetChannelStatus);
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Dsadc_StartCarrierSignal
*
*   Service ID              : 0x09
*
*   Description             : Start the generation of the carrier signal from the carrier generator
*                             based on the configured waveform properties for exciting the resolver
*                             coils.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK:  result buffer pointer initialized correctly
*                             E_NOT_OK: operation failed or development error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00419.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_StartCarrierSignal
(
    void
)
{
    Std_ReturnType                 RetErr;

    RetErr = E_NOT_OK;

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    if (DSADC_INITIALIZED != *(Dsadc_CoreInitStatusSetPtr[MCAL_MASTER_CORE]))
    {
        /* Reporting of error ADC_E_UNINIT */
        Dsadc_ReportError(DSADC_SID_STARTCARRIERSIGNAL, DSADC_E_UNINIT);
    }
    else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        if (Dsadc_ConfigPtr->GlobalCfgPtr->CarrierCfgPtr == NULL_PTR)
        {
            /* Carrier generator is disabled */
            Dsadc_ReportError(DSADC_SID_STARTCARRIERSIGNAL,
                                           DSADC_E_CARRIER_DISABLED);
        }
        else if (DSADC_CARRIER_SIGNAL_START == Dsadc_CarrierStatus)
        {
            /* Carrier signal is already opened */
            Dsadc_ReportError(DSADC_SID_STARTCARRIERSIGNAL,
                                    DSADC_E_CARRIER_ALREADY_OPENDED);
        }
        else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
        {
            /* Start the carrier generator */
            (void)Dsadc_Hal_EnableCarrierWave(TRUE);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
            /* Update carrier status machine to BUSY */
            Dsadc_CarrierStatus = DSADC_CARRIER_SIGNAL_START;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

            RetErr = E_OK;
        }
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Dsadc_StopCarrierSignal
*
*   Service ID              : 0x0A
*
*   Description             : Stop the generation of the carrier signal from the carrier generator.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK:  result buffer pointer initialized correctly
*                             E_NOT_OK: operation failed or development error occurred
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00419.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_StopCarrierSignal
(
    void
)
{
    Std_ReturnType                 RetErr;

    RetErr = E_NOT_OK;

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    if (DSADC_INITIALIZED != *(Dsadc_CoreInitStatusSetPtr[MCAL_MASTER_CORE]))
    {
        /* Reporting of error ADC_E_UNINIT */
        Dsadc_ReportError(DSADC_SID_STOPCARRIERSIGNAL, DSADC_E_UNINIT);
    }
    else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        if (DSADC_CARRIER_SIGNAL_STOP == Dsadc_CarrierStatus)
        {
            /* Carrier signal is already closed */
            Dsadc_ReportError(DSADC_SID_STOPCARRIERSIGNAL,
                                    DSADC_E_CARRIER_ALREADY_CLOSED);
        }
        else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
        {
            /* Stop the carrier generator */
            (void)Dsadc_Hal_EnableCarrierWave(FALSE);
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
            /* Update carrier status machine to STOP */
            Dsadc_CarrierStatus = DSADC_CARRIER_SIGNAL_STOP;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

            RetErr = E_OK;
        }
    }

    return RetErr;
}

#if (DSADC_CFG_SET_CARRIER_SYNC_PARAM_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_SetCarrierSyncParam
*
*   Service ID              : 0x10
*
*   Description             : Configure the carrier sync start and end parameters.
*
*   Parameters in           : CarrierSyncParamPtr: Pointer to the carrier sync configuration
*                               parameters.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_SetCarrierSyncParam
(
    P2CONST(Dsadc_CarrierSyncConfigType, AUTOMATIC, DSADC_APPL_CONST) CarrierSyncParamPtr
)
{
    uint8   HwUnitCnt;

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    if (DSADC_INITIALIZED != *(Dsadc_CoreInitStatusSetPtr[MCAL_MASTER_CORE]))
    {
        /* Reporting of error ADC_E_UNINIT */
        Dsadc_ReportError(DSADC_SID_SETCARRIERSYNCPARAM, DSADC_E_UNINIT);
    }
    else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        for (HwUnitCnt = 0U; HwUnitCnt < DSADC_TOTAL_HWUNIT; HwUnitCnt++)
        {
            if (DSADC_INVALID_ID != Dsadc_ConfigPtr->HwUnitToChannelIdPtr[HwUnitCnt])
            {
                /* HW is configured in project */
                /* Configure the carrier sync parameters */
                (void)Dsadc_Hal_ConfigCarrierWaveSync(Dsadc_BaseAddrs[HwUnitCnt], CarrierSyncParamPtr);
            }
        }
    }
}
#endif /* \(DSADC_CFG_SET_CARRIER_SYNC_PARAM_API == STD_ON) */

#if (DSADC_CFG_GET_CARRIER_SYNC_DELAY_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_GetCarrierDelayValue
*
*   Service ID              : 0x11
*
*   Description             : Read carrier signal delay value and return it. The carrier delay value
*                             is used to determine the start and stop parameter of carrier
*                             synchronization.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : uint8: Return the carrier delay value.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(uint8, DSADC_PUBLIC_CODE) Dsadc_GetCarrierDelayValue
(
    void
)
{
    uint8 CarrierDlyVal;

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    if (DSADC_INITIALIZED != *(Dsadc_CoreInitStatusSetPtr[MCAL_MASTER_CORE]))
    {
        CarrierDlyVal = 0U;
        /* Reporting of error ADC_E_UNINIT */
        Dsadc_ReportError(DSADC_SID_GETCARRIERDELAYVALUE, DSADC_E_UNINIT);
    }
    else if (DSADC_CARRIER_SIGNAL_STOP == Dsadc_CarrierStatus)
    {
        CarrierDlyVal = 0U;
        /* Carrier generator is stopped */
        Dsadc_ReportError(DSADC_SID_GETCARRIERDELAYVALUE,
                                DSADC_E_CARRIER_ALREADY_CLOSED);
    }
    else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Read carrier signal delay value */
        CarrierDlyVal = Dsadc_Hal_GetCarrierWaveSyncDelay();
    }

    return CarrierDlyVal;
}
#endif /* \(DSADC_CFG_GET_CARRIER_SYNC_DELAY_API == STD_ON) */

#if (DSADC_CFG_TIMESTAMP_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_GetTimestamp
*
*   Service ID              : 0x0B
*
*   Description             : Get the timestamp count value for the read result event.
*                             This timestamp count is the time from the HW result event untill the
*                             ReadResult API reads the result value from the HW Result register.
*
*   Parameters in           : Channel: Numeric ID of requested logical channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Dsadc_TimestampType: time-stamp value.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Adc_00419.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(Dsadc_TimestampType, DSADC_PUBLIC_CODE) Dsadc_GetTimestamp
(
    Dsadc_ChannelType Channel
)
{
    Dsadc_ChannelType             CoreChIdx;
    Dsadc_TimestampType           CurrTimestamp;
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                Err;
    const Dsadc_ChannelConfigType *ChCfgPtr;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    Mcal_CoreType                 CoreId;

    CurrTimestamp = 0U;
    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Err = Dsadc_CheckInit(DSADC_SID_GETTIMESTAMP, CoreId);
    if (E_OK == Err)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

        /* Find the channel index through given logic channel */
        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(Channel);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        Err = Dsadc_CheckMulticoreAllocateError(DSADC_SID_GETTIMESTAMP, Channel);
        if (E_OK == Err)
        {
            /* Get the configuration information of logical channel */
            /* #Violation: Dsadc_c_REF_1 */
            ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);

#if (DSADC_CFG_DMA_MODE == STD_ON)
            if (DSADC_RESULT_HANDLING_DMA_MODE == ChCfgPtr->RsltHldMthd)
            {
                /* This APi is not allowed in DMA mode */
                Dsadc_ReportError(DSADC_SID_GETTIMESTAMP, DSADC_E_DMA_ENABLED);
                Err = E_NOT_OK;
            }
            else
#endif /* \(DSADC_CFG_DMA_MODE == STD_ON) */
            if (DSADC_ACCESS_MODE_STREAMING == ChCfgPtr->RsltAccessMod)
            {
                /* Call to this function is not allowed when access mode is
                 * DSADC_ACCESS_MODE_STREAMING */
                Dsadc_ReportError(DSADC_SID_GETTIMESTAMP, DSADC_E_TIMESTAMP_NOT_SUPPORTED);
                Err = E_NOT_OK;
            }
            else if (FALSE == ChCfgPtr->TimestampEn)
            {
                /* Timestamp is disabled in requested channel */
                Dsadc_ReportError(DSADC_SID_GETTIMESTAMP, DSADC_E_TIMESTAMP_NOT_SUPPORTED);
                Err = E_NOT_OK;
            }
            else
            /* #Violation: Dsadc_c_REF_9 */
            {
                /* Do Nothing */
            }
        }
    }

    if (E_OK == Err)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get timestamp value */
        CurrTimestamp = Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].Timestamp;
    }

    return CurrTimestamp;
}
#endif /* \(DSADC_CFG_TIMESTAMP_ENABLE == STD_ON) */

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_EnableNotification
*
*   Service ID              : 0x0C
*
*   Description             : Enables the notification mechanism for the requested DSADC Channel.
*
*   Parameters in           : Channel: Numeric ID of requested logical channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_EnableNotification
(
    Dsadc_ChannelType Channel
)
{
    Dsadc_ChannelType              CoreChIdx;
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                 Err;
    const Dsadc_ChannelConfigType  *ChCfgPtr;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    Mcal_CoreType                  CoreId;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Err = Dsadc_CheckInit(DSADC_SID_ENABLENOTIFICATION, CoreId);
    if (E_OK == Err)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

        /* Find the channel index through given logic channel */
        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(Channel);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        Err = Dsadc_CheckMulticoreAllocateError(DSADC_SID_ENABLENOTIFICATION, Channel);
        if (E_OK == Err)
        {
            /* #Violation: Dsadc_c_REF_1 */
            ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);
            /* Check whether notification function is NULL */
            if ((NULL_PTR == ChCfgPtr->NewRsltNotifFuncPtr) &&
                (NULL_PTR == ChCfgPtr->BufFullNotifFuncPtr) &&
                (NULL_PTR == ChCfgPtr->LimitChkNotifFuncPtr))
            {
                /* Notification function points to NULL */
                Dsadc_ReportError( DSADC_SID_ENABLENOTIFICATION, DSADC_E_NOTIF_CAPABILITY);
                Err = E_NOT_OK;
            }
        }
    }

    if (E_OK == Err)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Enable the status of the notification */
        Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus = TRUE;
    }
}

/****************************************************************************************************
*   Function Name           : Dsadc_DisableNotification
*
*   Service ID              : 0x0D
*
*   Description             : Disables the notification mechanism for the requested DSADC Channel.
*
*   Parameters in           : Channel: Numeric ID of requested logical channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DisableNotification
(
    Dsadc_ChannelType Channel
)
{
    Dsadc_ChannelType              CoreChIdx;
    Mcal_CoreType                  CoreId;
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                 Err;
    const Dsadc_ChannelConfigType  *ChCfgPtr;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Err = Dsadc_CheckInit(DSADC_SID_DISABLENOTIFICATION, CoreId);
    if (E_OK == Err)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

        /* Find the channel index through given logic channel */
        /* #Violation: Dsadc_c_REF_1 */
        CoreChIdx = DSADC_GET_CORECHIDX(Channel);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        Err = Dsadc_CheckMulticoreAllocateError(DSADC_SID_DISABLENOTIFICATION, Channel);
        if (E_OK == Err)
        {
            /* #Violation: Dsadc_c_REF_1 */
            ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);
            /* Check whether notification function is NULL */
            if ((NULL_PTR == ChCfgPtr->NewRsltNotifFuncPtr) &&
                (NULL_PTR == ChCfgPtr->BufFullNotifFuncPtr) &&
                (NULL_PTR == ChCfgPtr->LimitChkNotifFuncPtr))
            {
                /* Notification function points to NULL */
                Dsadc_ReportError(DSADC_SID_DISABLENOTIFICATION, DSADC_E_NOTIF_CAPABILITY);
                Err = E_NOT_OK;
            }
        }
    }

    if (E_OK == Err)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Clear the status of the notification */
        Dsadc_CoreDataSetPtr[CoreId][CoreChIdx].ChNotifStatus = FALSE;
    }
}

#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */

#if (DSADC_CFG_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_GetVersionInfo
*
*   Service ID              : 0x0E
*
*   Description             : This service returns the version information of this module.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : VersionInfoPtr: Pointer to where to store the version information of 
*                             this module.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dsadc_c_REF_7 */
FUNC(void, DSDSADC_PUBLIC_CODE) Dsadc_GetVersionInfo
(
    /* #Violation: Dsadc_c_REF_6 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, DSADC_APPL_DATA) VersionInfoPtr
)
{
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == VersionInfoPtr)
    {
        Dsadc_ReportError(DSADC_SID_GETVERSIONINFO, DSADC_E_PARAM_POINTER);
    }
    else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        VersionInfoPtr->vendorID         = (uint16)DSADC_VENDOR_ID;
        VersionInfoPtr->moduleID         = (uint16)DSADC_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)DSADC_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)DSADC_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)DSADC_SW_PATCH_VERSION;
    }
}
#endif /* \(DSADC_VERSION_INFO_API == STD_ON) */

#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_AuxiliaryChannel_ISRHandler
*
*   Service ID              : 0xE0.
*
*   Description             : Interrupt handler of auxiliary channel.
*                             Interrupt as follows:
*                               - REAST: Auxiliary Transition Completes Interrupt Status.
*                               - SBAST: Auxiliary Result Below Lower Limit Interrupt Status.
*                               - SAAST: Auxiliary Result Above Upper Limit Interrupt Status.
*
*   Parameters in           : HwUnitId: the DSADC number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant for different interrupt in IP..
*
*   Return value            : None.
*
*   Preconditions           : Related interrupt enabled.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_AuxiliaryChannel_ISRHandler
(
    Dsadc_HWUnitType HwUnitId
)
{
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                Err;
    Dsadc_StatusType              ChStatus;
    uint32                        IntStatus;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    Dsadc_ChannelType             Channel;
    Dsadc_ChannelType             CoreChIdx;
    Mcal_CoreType                 CoreId;
    const Dsadc_ChannelConfigType *ChCfgPtr;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Err = Dsadc_CheckInit(DSADC_SID_AUXCHANNEL_ISR, CoreId);
    if (E_OK == Err)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

        /* Get logical channel ID from HW unit ID */
        /* #Violation: Dsadc_c_REF_1 */
        Channel = DSADC_GET_CHOFHW(HwUnitId);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        Err = Dsadc_CheckMulticoreAllocateError(DSADC_SID_AUXCHANNEL_ISR, Channel);
        if (E_OK == Err)
        {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

            /* Find the channel index through given logic channel */
            /* #Violation: Dsadc_c_REF_1 */
            CoreChIdx = DSADC_GET_CORECHIDX(Channel);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
            /* #Violation: Dsadc_c_REF_1 */
            ChStatus = DSADC_CHAUXSTA(CoreId, CoreChIdx);
            if (DSADC_IDLE == ChStatus)
            {
                /* Channel is in IDLE or CALIBRATING status */
                Dsadc_ReportError(DSADC_SID_AUXCHANNEL_ISR, DSADC_E_IDLE);
                Err = E_NOT_OK;
            }
        }
    }

    if (E_NOT_OK == Err)
    {
        /* Get interrupt status */
        IntStatus = Dsadc_Hal_GetInterruptStatus(Dsadc_BaseAddrs[HwUnitId]);
        /* If the auxiliary conversion channel completed is triggered */
        /* Clear interrupt flag */
        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId], IntStatus);
    }
    else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get the channel configuration */
        /* #Violation: Dsadc_c_REF_1 */
        ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);
        /* Auxiliary filter interrupt process */
        Dsadc_AuxIsrEventEntry(HwUnitId, Channel, ChCfgPtr);
    }
}
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE == STD_ON) */

#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
/****************************************************************************************************
*   Function Name           : Dsadc_MainChannel_ISRHandler
*
*   Service ID              : 0xE1.
*
*   Description             : Interrupt handler of main channel.
*                             Interrupt as follows:
*                               - TSTMPST: Timestamp Interrupt Status.
*                               - SBMST: Main Result Below Lower Limit Interrupt Status.
*                               - SAMST: Main Result Above Upper Limit Interrupt Status.
*                               - FIFOFILLST: FIFO Data Reaches Threshold Interrupt Status.
*                               - TRIGST: External Trigger Interrupt Status.
*
*   Parameters in           : HwUnitId: the SDADC number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant for different interrupt in IP.
*
*   Return value            : None.
*
*   Preconditions           : Related interrupt enabled.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_MainChannel_ISRHandler
(
    Dsadc_HWUnitType HwUnitId
)
{
    boolean                       SafetyErr;
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                Err;
    Dsadc_StatusType              ChStatus;
    uint32                        IntStatus;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    Dsadc_ChannelType             Channel;
    Dsadc_ChannelType             CoreChIdx;
    Mcal_CoreType                 CoreId;
    const Dsadc_ChannelConfigType *ChCfgPtr;

    /* #Violation: Dsadc_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
    Err = Dsadc_CheckInit(DSADC_SID_MAINCHANNEL_ISR, CoreId);
    if (E_OK == Err)
    {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

        /* Get logical channel ID from HW unit ID */
        /* #Violation: Dsadc_c_REF_1 */
        Channel = DSADC_GET_CHOFHW(HwUnitId);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
        Err = Dsadc_CheckMulticoreAllocateError(DSADC_SID_MAINCHANNEL_ISR, Channel);
        if (E_OK == Err)
        {
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

            /* Find the channel index through given logic channel */
            /* #Violation: Dsadc_c_REF_1 */
            CoreChIdx = DSADC_GET_CORECHIDX(Channel);

#if (DSADC_DEV_ERROR_DETECT == STD_ON)
            /* #Violation: Dsadc_c_REF_1 */
            ChStatus = DSADC_CHSTA(CoreId, CoreChIdx);
            if (DSADC_IDLE == ChStatus)
            {
                /* Channel is in IDLE or CALIBRATING status */
                Dsadc_ReportError(DSADC_SID_MAINCHANNEL_ISR, DSADC_E_IDLE);
                Err = E_NOT_OK;
            }
        }
    }

    if (E_NOT_OK == Err)
    {
        /* Get interrupt status */
        IntStatus = Dsadc_Hal_GetInterruptStatus(Dsadc_BaseAddrs[HwUnitId]);
        /* If the auxiliary conversion channel completed is triggered */
        /* Clear interrupt flag */
        Dsadc_Hal_ClearInterruptStatus(Dsadc_BaseAddrs[HwUnitId], IntStatus);
    }
    else
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get the channel configuration */
        /* #Violation: Dsadc_c_REF_1 */
        ChCfgPtr = DSADC_GET_CHCFG(CoreId, CoreChIdx);
        /* Main filter chain interrupt process */
        SafetyErr = Dsadc_IsrEventEntry(HwUnitId, Channel, ChCfgPtr);

#if (DSADC_SAFETY_ENABLE == STD_ON)
        if (FALSE == SafetyErr)
        {
            /* Report the safety check error */
            Dsadc_ReportRuntimeError(DSADC_SID_MAINCHANNEL_ISR);
        }
#else
        MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */
    }
}
#endif /* \(DSADC_CFG_INTERRUPT_MODE == STD_ON) */

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dsadc_c_REF_4 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                                  End of File                                                    **
****************************************************************************************************/
