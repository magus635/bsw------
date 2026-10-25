/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dma.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DMA
*
*   brief                 : This file contains all functions of DMA Driver
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
*#Dma_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Dma_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Redundant cast is necessary to maintain the software structure and reduce the 
* complexity.
*
*#Dma_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Dma_c_REF_4:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
*   driver must be placed.
*
*#Dma_c_REF_5:MISRAC2012-Rule-20.7;
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Dma_c_REF_6:MISRAC2012-Rule-20.10;
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Dma_c_REF_7:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#Dma_c_REF_8:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Dma_c_REF_9:CWE-1071;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Dma_c_REF_10:MISRAC2012-Dir-4.1;
* Justification: Number of loops is set by different configurations.
*
*#Dma_c_REF_11:MISRAC2012-Rule-2.2;
* Justification: Code review ensures the compliance with rule.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dma.h"
#include "Dma_Cfg.h"
#include "Dma_Version.h"
#include "SchM_Dma.h"
#include "Mcall.h"
#if ((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON))
#include "Det.h"
#endif /* \((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON)) */
/* Included the dma driver of HAL layer */
#include "tha6_cfg.h"
#include "dma_hal.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (DMA_VENDOR_ID != DMA_CFG_VENDOR_ID)
  #error "Dma.c : Mismatch in Vendor ID"
#endif /* \(DMA_VENDOR_ID != DMA_CFG_VENDOR_ID) */

#if (DMA_MODULE_ID != DMA_CFG_MODULE_ID)
  #error "Dma.c : Mismatch in Module ID"
#endif /* \(DMA_MODULE_ID != DMA_CFG_MODULE_ID) */

#if (DMA_AR_RELEASE_MAJOR_VERSION != DMA_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Dma.c : Mismatch in Release Major Version"
#endif /* \(DMA_AR_RELEASE_MAJOR_VERSION != DMA_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (DMA_AR_RELEASE_MINOR_VERSION != DMA_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Dma.c : Mismatch in Release Minor Version"
#endif /* \(DMA_AR_RELEASE_MINOR_VERSION != DMA_CFG_AR_RELEASE_MINOR_VERSION) */

#if (DMA_AR_RELEASE_REVISION_VERSION != DMA_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Dma.c : Mismatch in Release Revision Version"
#endif /* \(DMA_AR_RELEASE_REVISION_VERSION != DMA_CFG_AR_RELEASE_REVISION_VERSION) */

#if (DMA_SW_MAJOR_VERSION != DMA_CFG_SW_MAJOR_VERSION)
  #error "Dma.c : Mismatch in Software Major Version"
#endif /* \(DMA_SW_MAJOR_VERSION != DMA_CFG_SW_MAJOR_VERSION) */

#if (DMA_SW_MINOR_VERSION != DMA_CFG_SW_MINOR_VERSION)
  #error "Dma.c : Mismatch in Software Minor Version"
#endif /* \(DMA_SW_MINOR_VERSION != DMA_CFG_SW_MINOR_VERSION) */

#if (DMA_SW_PATCH_VERSION != DMA_CFG_SW_PATCH_VERSION)
  #error "Dma.c : Mismatch in Software Patch Version"
#endif /* \(DMA_SW_PATCH_VERSION != DMA_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Invalid Logical channel ID */
#define DMA_INVALID_CHANNEL                        (0xFFU)
/* Linked list not valid in shadowing operation */
#define DMA_INVALID_IDX                            (0xFFU)

/* Daisy chain is suspended */
#define DMA_DAISYCHAIN_SUSPENEDED                  (2U)
/* Daisy chain is transferring */
#define DMA_DAISYCHAIN_TRANSFERRING                (1U)
/* Daisy chain is idle */
#define DMA_DAISYCHAIN_IDLE                        (0U)

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
/* Maximum transfer size in bytes */
#define DMA_MAX_TRANSFER_SIZE                      (4095U)
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

#if (DMA_DEV_ERROR_DETECT == STD_ON)
/* Macro for report the DMA DET error */
/* #Violation: Dma_c_REF_8 */
#define Dma_ReportError(ServiceId, ErrCode)        \
                     (void)Det_ReportError(DMA_MODULE_ID, DMA_INSTANCE_ID, ServiceId, ErrCode)
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_SAFETY_ENABLE == STD_ON)
/* Macro for report the DMA runtime error */
/* #Violation: Dma_c_REF_8 */
#define Dma_ReportRuntimeError(ServiceId)        \
                     (void)Det_ReportRuntimeError(DMA_MODULE_ID, DMA_INSTANCE_ID, \
                                                  ServiceId, DMA_E_SAFETY_CHECK_FAILED)
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */

/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* Macro for enter critical section */
/* #Violation: Dma_c_REF_6 */
/* #Violation: Dma_c_REF_8 */
#define DMA_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Dma_##Exclusive_Area()
/* Macro for exit critical section */
/* #Violation: Dma_c_REF_6 */
/* #Violation: Dma_c_REF_8 */
#define DMA_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Dma_##Exclusive_Area()

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/**                         Private Variable Definitions - Core0                                  **/
#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Dma_MemMap.h"

#if (DMA_DEV_ERROR_DETECT == STD_ON)
/* Dma initialization status for Core0 */
static Dma_InitType Dma_InitStatusCore0;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#if (DMA_CFG_MAX_CHANNELS_CORE0 > 0U)

#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#if (DMA_CFG_MULTI_TRANSFER_NUM_CORE0 != 0U)
/* Current transfer configuration in core0 */
static Dma_TransferType Dma_CurrTransferCore0[DMA_CFG_MULTI_TRANSFER_NUM_CORE0];
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM_CORE0 != 0U) */

#if (DMA_CFG_MULTI_SHADOWING_NUM_CORE0 != 0U)
/* Current pattern match configuration in core0 */
static Dma_ShadowingType Dma_CurrShadowingCore0[DMA_CFG_MULTI_SHADOWING_NUM_CORE0];
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM_CORE0 != 0U) */

#if (DMA_CFG_DAISY_CHAIN_NUM_CORE0 != 0U)
/* Daisy chain status */
static uint8 Dma_DaisyChainStatusCore0[DMA_CFG_DAISY_CHAIN_NUM_CORE0];
#endif /* \(DMA_CFG_DAISY_CHAIN_NUM_CORE0 != 0U) */

/* Dma channel status for core0 */
static Dma_ChStatusType Dma_ChStatusCore0[DMA_CFG_MAX_CHANNELS_CORE0];

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
static Dma_ChannelTransferType *Dma_ChTransManualCore0[DMA_CFG_MAX_CHANNELS_CORE0];
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#endif /* \(DMA_MAX_HWUNIT_TO_CORE0 > 0U) */

/**                         Private Variable Definitions - Core1                                  **/
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (DMA_CFG_MAX_CHANNELS_CORE1 > 0U)

#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#if (DMA_DEV_ERROR_DETECT == STD_ON)
/* Dma initialization status for Core1 */
static Dma_InitType Dma_InitStatusCore1;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_CFG_MULTI_TRANSFER_NUM_CORE1 != 0U)
/* Current transfer configuration in core1 */
static Dma_TransferType Dma_CurrTransferCore1[DMA_CFG_MULTI_TRANSFER_NUM_CORE1];
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM_CORE1 != 0U) */

#if (DMA_CFG_MULTI_SHADOWING_NUM_CORE1 != 0U)
/* Current pattern match configuration in core1 */
static Dma_ShadowingType Dma_CurrShadowingCore1[DMA_CFG_MULTI_SHADOWING_NUM_CORE1];
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM_CORE1 != 0U) */

#if (DMA_CFG_DAISY_CHAIN_NUM_CORE1 != 0U)
/* Daisy chain status */
static uint8 Dma_DaisyChainStatusCore1[DMA_CFG_DAISY_CHAIN_NUM_CORE1];
#endif /* \(DMA_CFG_DAISY_CHAIN_NUM_CORE1 != 0U) */

/* Dma channel status for core1 */
static Dma_ChStatusType Dma_ChStatusCore1[DMA_CFG_MAX_CHANNELS_CORE1];

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
static Dma_ChannelTransferType *Dma_ChTransManualCore1[DMA_CFG_MAX_CHANNELS_CORE1];
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */#include "Dma_MemMap.h"

#endif /* \(DMA_CFG_MAX_CHANNELS_CORE1 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */

/**                         Private Variable Definitions - Core2                                  **/
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (DMA_CFG_MAX_CHANNELS_CORE2 > 0U)

#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#if (DMA_DEV_ERROR_DETECT == STD_ON)
/* Dma initialization status for Core1 */
static Dma_InitType Dma_InitStatusCore2;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_CFG_MULTI_TRANSFER_NUM_CORE2 != 0U)
/* Current transfer configuration in core2 */
static Dma_TransferType Dma_CurrTransferCore2[DMA_CFG_MULTI_TRANSFER_NUM_CORE2];
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM_CORE2 != 0U) */

#if (DMA_CFG_MULTI_SHADOWING_NUM_CORE2 != 0U)
/* Current pattern match configuration in core2 */
static Dma_ShadowingType Dma_CurrShadowingCore2[DMA_CFG_MULTI_SHADOWING_NUM_CORE2];
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM_CORE2 != 0U) */

#if (DMA_CFG_DAISY_CHAIN_NUM_CORE2 != 0U)
/* Daisy chain status */
static uint8 Dma_DaisyChainStatusCore2[DMA_CFG_DAISY_CHAIN_NUM_CORE2];
#endif /* \(DMA_CFG_DAISY_CHAIN_NUM_CORE2 != 0U) */

/* Dma channel status for core2 */
static Dma_ChStatusType Dma_ChStatusCore2[DMA_CFG_MAX_CHANNELS_CORE2];

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
static Dma_ChannelTransferType *Dma_ChTransManualCore2[DMA_CFG_MAX_CHANNELS_CORE2];
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#endif /* \(DMA_CFG_MAX_CHANNELS_CORE2 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */

/**                         Private Variable Definitions - Core3                                  **/
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (DMA_CFG_MAX_CHANNELS_CORE3 > 0U)

#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#if (DMA_DEV_ERROR_DETECT == STD_ON)
/* Dma initialization status for Core3 */
static Dma_InitType Dma_InitStatusCore3;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_CFG_MULTI_TRANSFER_NUM_CORE3 != 0U)
/* Current transfer configuration in core3 */
static Dma_TransferType Dma_CurrTransferCore3[DMA_CFG_MULTI_TRANSFER_NUM_CORE3];
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM_CORE3 != 0U) */

#if (DMA_CFG_MULTI_SHADOWING_NUM_CORE3 != 0U)
/* Current pattern match configuration in core3 */
static Dma_ShadowingType Dma_CurrShadowingCore1[DMA_CFG_MULTI_SHADOWING_NUM_CORE3];
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM_CORE3 != 0U) */

#if (DMA_CFG_DAISY_CHAIN_NUM_CORE3 != 0U)
/* Daisy chain status */
static uint8 Dma_DaisyChainStatusCore3[DMA_CFG_DAISY_CHAIN_NUM_CORE3];
#endif /* \(DMA_CFG_DAISY_CHAIN_NUM_CORE3 != 0U) */

/* Dma channel status for core3 */
static Dma_ChStatusType Dma_ChStatusCore3[DMA_CFG_MAX_CHANNELS_CORE3];

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
static Dma_ChannelTransferType *Dma_ChTransManualCore3[DMA_CFG_MAX_CHANNELS_CORE3];
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#endif /* \(DMA_CFG_MAX_CHANNELS_CORE3 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */

#define DMA_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

/* To store the Dma driver configuration pointer */
static P2CONST(Dma_ConfigType, AUTOMATIC, DMA_APPL_DATA) Dma_ConfigPtr;

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/**                         Private Constant Definitions - Core0                                  **/
#if (DMA_CFG_MAX_CHANNELS_CORE0 > 0U)

#define DMA_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

static const Dma_GlobalDataSetType Dma_DataSetCore0 =
{
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
#if (DMA_CFG_MULTI_TRANSFER_NUM_CORE0 != 0U)
    &Dma_CurrTransferCore0[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM_CORE0 != 0U) */
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
#if (DMA_CFG_MULTI_SHADOWING_NUM_CORE0 != 0U)
    &Dma_CurrShadowingCore0[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM_CORE0 != 0U) */
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if (DMA_CFG_DAISY_CHAIN_NUM_CORE0 != 0U)
    &Dma_DaisyChainStatusCore0[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_DAISY_CHAIN_NUM_CORE0 != 0U) */
#endif /* \(DMA_CFG_DAISYCHAIN_EN != 0U) */
#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
    Dma_ChTransManualCore0,
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */
    &Dma_ChStatusCore0[0]
};

#define DMA_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#endif /* \(DMA_CFG_MAX_CHANNELS_CORE0 > 0U) */

/**                         Private Constant Definitions - Core1                                  **/
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (DMA_CFG_MAX_CHANNELS_CORE1 > 0U)

#define DMA_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

static const Dma_GlobalDataSetType Dma_DataSetCore1 =
{
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
#if (DMA_CFG_MULTI_TRANSFER_NUM_CORE1 != 0U)
    &Dma_CurrTransferCore1[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM_CORE1 != 0U) */
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
#if (DMA_CFG_MULTI_SHADOWING_NUM_CORE1 != 0U)
    &Dma_CurrShadowingCore1[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM_CORE1 != 0U) */
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if (DMA_CFG_DAISY_CHAIN_NUM_CORE1 != 0U)
    &Dma_DaisyChainStatusCore1[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_DAISY_CHAIN_NUM_CORE1 != 0U) */
#endif /* \(DMA_CFG_DAISYCHAIN_EN != 0U) */
#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
    Dma_ChTransManualCore1,
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */
    &Dma_ChStatusCore1[0]
};

#define DMA_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#endif /* \(DMA_CFG_MAX_CHANNELS_CORE1 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */

/**                         Private Constant Definitions - Core2                                  **/
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (DMA_CFG_MAX_CHANNELS_CORE2 > 0U)

#define DMA_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

static const Dma_GlobalDataSetType Dma_DataSetCore2 =
{
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
#if (DMA_CFG_MULTI_TRANSFER_NUM_CORE2 != 0U)
    &Dma_CurrTransferCore2[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM_CORE2 != 0U) */
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
#if (DMA_CFG_MULTI_SHADOWING_NUM_CORE2 != 0U)
    &Dma_CurrShadowingCore2[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM_CORE2 != 0U) */
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if (DMA_CFG_DAISY_CHAIN_NUM_CORE2 != 0U)
    &Dma_DaisyChainStatusCore1[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_DAISY_CHAIN_NUM_CORE2 != 0U) */
#endif /* \(DMA_CFG_DAISYCHAIN_EN != 0U) */
#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
    Dma_ChTransManualCore2,
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */
    &Dma_ChStatusCore2[0]
};

#define DMA_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#endif /* \(DMA_CFG_MAX_CHANNELS_CORE2 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */

/**                         Private Constant Definitions - Core3                                  **/
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (DMA_CFG_MAX_CHANNELS_CORE3 > 0U)

#define DMA_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

static const Dma_GlobalDataSetType Dma_DataSetCore3 =
{
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
#if (DMA_CFG_MULTI_TRANSFER_NUM_CORE3 != 0U)
    &Dma_CurrTransferCore3[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM_CORE3 != 0U) */
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
#if (DMA_CFG_MULTI_SHADOWING_NUM_CORE3 != 0U)
    &Dma_CurrShadowingCore3[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM_CORE3 != 0U) */
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if (DMA_CFG_DAISY_CHAIN_NUM_CORE3 != 0U)
    &Dma_DaisyChainStatusCore3[0],
#else
    NULL_PTR,
#endif /* \(DMA_CFG_DAISY_CHAIN_NUM_CORE3 != 0U) */
#endif /* \(DMA_CFG_DAISYCHAIN_EN != 0U) */
#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
    Dma_ChTransManualCore3,
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */
    &Dma_ChStatusCore3[0]
};

#define DMA_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#endif /* \(DMA_CFG_MAX_CHANNELS_CORE3 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */

#define DMA_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#if (DMA_DEV_ERROR_DETECT == STD_ON)
/* Pointer to the DMA Initialization status */
/* #Violation: Dma_c_REF_5 */
static CONSTP2VAR(Dma_InitType, DMA_VAR, DMA_APPL_CONST)
                                       Dma_CoreInitStatusSetPtr[MCAL_NUMBER_OF_CORES] =
{
    &Dma_InitStatusCore0

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (DMA_CFG_MAX_CHANNELS_CORE1 > 0U)
    ,&Dma_InitStatusCore1
#else
    ,NULL_PTR
#endif /* \(DMA_CFG_MAX_CHANNELS_CORE1 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (DMA_CFG_MAX_CHANNELS_CORE2 > 0U)
    ,&Dma_InitStatusCore2
#else
    ,NULL_PTR
#endif /* \(DMA_CFG_MAX_CHANNELS_CORE2 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (DMA_CFG_MAX_CHANNELS_CORE3 > 0U)
    ,&Dma_InitStatusCore3
#else
    ,NULL_PTR
#endif /* \(DMA_CFG_MAX_CHANNELS_CORE3 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */
};
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/* Pointer to the DMA HW unit data structure set for each core */
static CONSTP2CONST(Dma_GlobalDataSetType, DMA_VAR, DMA_APPL_CONST)
                                       Dma_StatusDataSetPtr[MCAL_NUMBER_OF_CORES] =
{
#if (DMA_CFG_MAX_CHANNELS_CORE0 > 0U)
    &Dma_DataSetCore0
#else
    NULL_PTR
#endif /* \(DMA_CFG_MAX_CHANNELS_CORE0 > 0U) */

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (DMA_CFG_MAX_CHANNELS_CORE1 > 0U)
    ,&Dma_DataSetCore1
#else
    ,NULL_PTR
#endif /* \(DMA_CFG_MAX_CHANNELS_CORE1 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (DMA_CFG_MAX_CHANNELS_CORE2 > 0U)
    ,&Dma_DataSetCore2
#else
    ,NULL_PTR
#endif /* \(DMA_CFG_MAX_CHANNELS_CORE2 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (DMA_CFG_MAX_CHANNELS_CORE3 > 0U)
    ,&Dma_DataSetCore3
#else
    ,NULL_PTR
#endif /* \(DMA_CFG_MAX_CHANNELS_CORE3 > 0U) */
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */
};

/* Pointer to the address of each DMA HW unit */
/* #Violation: Dma_c_REF_5 */
static CONSTP2VAR(DMA_MODULE, AUTOMATIC, DMA_APPL_CONST) Dma_BaseAddrs[DMA_MAX_HWUNIT_COUNT] =
{
#if ((defined(DMA_HWUNIT_DMA0)) && (DMA_HWUNIT_DMA0 == 0U))
    /* #Violation: Dma_c_REF_3 */
    DMA0
#else /* \!defined(DMA_HWUNIT_DMA0) */
    NULL_PTR
#endif /* \((defined(DMA_HWUNIT_DMA0)) && (DMA_HWUNIT_DMA0 == 0U)) */

#if (DMA_MAX_HWUNIT_COUNT > 1U)
#if ((defined(DMA_HWUNIT_DMA1)) && (DMA_HWUNIT_DMA1 == 1U))
    /* #Violation: Dma_c_REF_3 */
    ,DMA1
#else /* \!defined(DMA_HWUNIT_DMA1) */
    ,NULL_PTR
#endif /* \((defined(DMA_HWUNIT_DMA1)) && (DMA_HWUNIT_DMA1 == 1U)) */
#endif /* \(DMA_MAX_HWUNIT_COUNT > 1U) */

#if (DMA_MAX_HWUNIT_COUNT > 2U)
#if ((defined(DMA_HWUNIT_DMA2)) && (DMA_HWUNIT_DMA2 == 2U))
    /* #Violation: Dma_c_REF_3 */
    ,DMA2
#else /* \!defined(DMA_HWUNIT_DMA2) */
    ,NULL_PTR
#endif /* \((defined(DMA_HWUNIT_DMA2)) && (DMA_HWUNIT_DMA2 == 2U)) */
#endif /* \(DMA_MAX_HWUNIT_COUNT > 2U) */

#if (DMA_MAX_HWUNIT_COUNT > 3U)
#if ((defined(DMA_HWUNIT_DMA3)) && (DMA_HWUNIT_DMA3 == 3U))
    /* #Violation: Dma_c_REF_3 */
    ,DMA3
#else /* \!defined(DMA_HWUNIT_DMA3) */
    ,NULL_PTR
#endif /* \((defined(DMA_HWUNIT_DMA3)) && (DMA_HWUNIT_DMA3 == 3U)) */
#endif /* \(DMA_MAX_HWUNIT_COUNT > 3U) */
};

#define DMA_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#if (DMA_DEV_ERROR_DETECT == STD_ON)

static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_CheckInitParam
(
    CONSTP2CONST(Dma_ConfigType, AUTOMATIC, DMA_APPL_CONST) ConfigPtr
);

static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_CheckInit
(
    uint8 ServiceId
);

#if (DMA_CFG_DEINIT_API == STD_ON)
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_CheckDeInit
(
    Mcal_CoreType CoreId
);
#endif /* \(DMA_CFG_DEINIT_API == STD_ON) */

static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_ChCommCheck
(
    uint8 ServiceId,
    Dma_ChannelType Channel
);

#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_StartDaisyChainErrCheck
(
    Dma_ChannelType Channel
);

#if ((DMA_CFG_CHANNEL_CANCEL_API == STD_ON) || (DMA_CFG_CHANNEL_PAUSE_API == STD_ON))
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_DaisyChainErrCheck
(
    Dma_ChannelType Channel
);
#endif /* \((DMA_CFG_CHANNEL_CANCEL_API == STD_ON) || (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)) */
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */

#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
static FUNC(Dma_TransferType, DMA_PRIVATE_CODE) Dma_GetTransferId
(
    Dma_ChannelType Channel
);
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */

#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
static FUNC(void, DMA_PRIVATE_CODE) Dma_LliConfigChange
(
    Dma_ChannelType Channel,
    Dma_LinkedListType LliId,
    CONSTP2CONST(Dma_ChConfigType, AUTOMATIC, DMA_APPL_CONST) ChConfigPtr
);
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */

#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ShadowingConfigChange
(
    Dma_ChannelType Channel,
    Dma_ShadowingType ShadowingId,
    CONSTP2CONST(Dma_ChConfigType, AUTOMATIC, DMA_APPL_CONST) ChConfigPtr
);
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */

static FUNC(uint32, DMA_PRIVATE_CODE) Dma_TerminalCountRefreshStatus
(
    Dma_HwUnitType  HwUnitId,
    uint8           PhyChannelId,
    Dma_ChannelType Channel
);

static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ResetChannelConfig
(
    Dma_ChannelType Channel,
    Dma_HwUnitType  PhyHwUnitId,
    uint8           PhyChannelId,
    CONSTP2CONST(Dma_ChConfigType, AUTOMATIC, DMA_APPL_CONST) ChConfigPtr
);

static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ChannelStartPrepare
(
    Dma_ChannelType Channel,
    boolean         DaisyChainEnFlg
);

#if (DMA_CFG_CHANNEL_CANCEL_API == STD_ON)
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ChannelCancelPrepare
(
    Dma_ChannelType  Channel,
    Dma_ChCancelType CancelMethod,
    boolean          DaisyChainEnFlg
);
#endif /* \(DMA_CFG_CHANNEL_CANCEL_API == STD_ON) */

#if (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292)
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ChannelSuspendPrepare
(
    Dma_ChannelType  Channel
);

static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ChannelResumePrepare
(
    Dma_ChannelType  Channel
);
#endif /* \(MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292) */
#endif /* \(DMA_CFG_CHANNEL_PAUSE_API == STD_ON) */

#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
static FUNC(void, DMA_PRIVATE_CODE) Dma_ChannelClrDblFrznStatus
(
    Dma_HwUnitType  PhyHwUnitId,
    uint8           PhyChannelId,
    Dma_DoubleBufferFrozenStatus FrznStatus
);
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_RefreshDaisyChainStatus
(
    Dma_ChannelType DcFirstCh
);
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */

static FUNC(boolean, DMA_PRIVATE_CODE) Dma_InitSingleChannel
(
    CONSTP2CONST(Dma_ConfigType, AUTOMATIC, DMA_APPL_CONST) ConfigPtr,
    Mcal_CoreType CoreId,
    uint8 ChannelCnt
);

static FUNC(boolean, DMA_PRIVATE_CODE) Dma_GetChannelEvent
(
    Dma_ChannelType Channel,
    P2VAR(uint32, AUTOMATIC, DMA_APPL_DATA) ChStatusPtr
);

#if (DMA_CFG_DEINIT_API == STD_ON)
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_DeInitAllChannels
(
    Mcal_CoreType CoreId,
    uint8         MaxChannel,
    P2VAR(boolean, AUTOMATIC, DMA_APPL_DATA) SafetyErrPtr
);

static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ResetHwUnits
(
    void
);
#endif /* \(DMA_CFG_DEINIT_API == STD_ON) */

#if (DMA_CFG_CHANNEL_CANCEL_API == STD_ON)
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_CancelDaisyChainMembers
(
    Dma_ChannelType             Channel,                          
    Dma_ChCancelType            CancelMethod,               
    Mcal_CoreType               CoreId
);
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
#endif /* \(DMA_CFG_CHANNEL_CANCEL_API == STD_ON) */

#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

#if (DMA_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_CheckInitParam
*
*   Service ID              : None.
*
*   Description             : Check the DET during DMA initialization.
*
*   Parameters in           : ConfigPtr: pointer to the DMA configuration parameters entry.
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
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_CheckInitParam
(
    CONSTP2CONST(Dma_ConfigType, AUTOMATIC, DMA_APPL_CONST) ConfigPtr
)
{
    Mcal_CoreType      CoreId;
    Std_ReturnType     RetErr;

    RetErr = E_NOT_OK;

    /* Get core id which core is currently executing */
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    if ((MCAL_MASTER_CORE != CoreId) && (NULL_PTR == Dma_CoreInitStatusSetPtr[CoreId]))
    {
        /* No HW UNIT are configured for specified core "CoreId" */
        /* Master must be initialized */
        Dma_ReportError(DMA_SID_INIT, DMA_E_CORE_NOT_CONFIGURED);
    }
    else if ((MCAL_MASTER_CORE != CoreId) &&
            (DMA_UNINITIALIZE == *(Dma_CoreInitStatusSetPtr[MCAL_MASTER_CORE])))
    {
        /* Master core is not initialized */
        Dma_ReportError(DMA_SID_INIT, DMA_E_MASTER_CORE_UNINITIALIZE);
    }
    else if (DMA_INITIALIZED == *(Dma_CoreInitStatusSetPtr[CoreId]))
    {
        /* Dma Driver initialization is called twice before De-init */
        Dma_ReportError(DMA_SID_INIT, DMA_E_ALREADY_INITIALIZED);
    }
    else if (NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is NULL_PTR, report DET error for variant PB */
        Dma_ReportError(DMA_SID_INIT, DMA_E_PARAM_CONFIG);
    }
    else
    {
        RetErr = E_OK;
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Dma_CheckInit
*
*   Service ID              : None.
*
*   Description             : Check the initialization status.
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
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_CheckInit
(
    uint8 ServiceId
)
{
    Std_ReturnType RetErr;
    Mcal_CoreType  CoreId;

    RetErr = E_NOT_OK;

    /* Get core id which core is currently executing */
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    if ((MCAL_MASTER_CORE != CoreId) && (NULL_PTR == Dma_CoreInitStatusSetPtr[CoreId]))
    {
        /* Report the no configuration parameters in current core */
        Dma_ReportError(ServiceId, DMA_E_CORE_NOT_CONFIGURED);
    }
    else if (DMA_INITIALIZED != *(Dma_CoreInitStatusSetPtr[CoreId]))
    {
        /* Reporting of error DMA_E_UNINIT */
        Dma_ReportError(ServiceId, DMA_E_UNINIT);
    }
    else if ((ServiceId != DMA_SID_DEINIT) && (NULL_PTR == Dma_ConfigPtr->CoreConfigPtr[CoreId]))
    {
        /* Not configuration data excluding the de-initialization API */
        Dma_ReportError(ServiceId, DMA_E_CORE_NOT_CONFIGURED);
    }
    else
    {
        RetErr = E_OK;
    }

    return RetErr;
}

#if (DMA_CFG_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_CheckDeInit
*
*   Service ID              : None.
*
*   Description             : Check the initialization status.
*
*   Parameters in           :
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
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_CheckDeInit
(
    Mcal_CoreType CoreId
)
{
    Std_ReturnType  Err;
    uint8 CoreCnt;

    Err = Dma_CheckInit(DMA_SID_DEINIT);
    if (E_OK == Err)
    {
        if (MCAL_MASTER_CORE == CoreId)
        {
            /* Check if all slave cores have been de-initialized  */
            for (CoreCnt = (uint8)MCAL_CORE1;
                    /* #Violation: Dma_c_REF_10 */
                    (CoreCnt < MCAL_NUMBER_OF_CORES) && (E_OK == Err); CoreCnt++)
            {
                if ((NULL_PTR != Dma_CoreInitStatusSetPtr[CoreCnt]) &&
                    (DMA_INITIALIZED == *Dma_CoreInitStatusSetPtr[CoreCnt]))
                {
                    /* Channel is not in IDLE status */
                    Dma_ReportError(DMA_SID_DEINIT, DMA_E_SLAVE_CORE_INITIALIZED);
                    Err = E_NOT_OK;
                }
            }
        }
    }

    return Err;
}
#endif /* \(DMA_CFG_DEINIT_API == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dma_ChCommCheck
*
*   Service ID              : None.
*
*   Description             : Common DET check with Channel
*
*   Parameters in           : ServiceId: Service id of calling API.
*                             Channel: Logical Channel ID and generated by EB tresos tool.
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
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_ChCommCheck
(
    uint8 ServiceId,
    Dma_ChannelType Channel
)
{
    Std_ReturnType           RetErr;
    uint8                    CoreChIdx;
    Mcal_CoreType            CoreId;

    RetErr = E_NOT_OK;
    /* Get core id which core is currently executing */
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    if (Channel >= DMA_CFG_MAX_CHANNELS)
    {
        /* Parameter 'Channel' is greater than maximum configured channel number */
        Dma_ReportError(ServiceId, DMA_E_PARAM_CHANNEL);
    }
    else
    {
        /* Get channel index in current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
        if (Dma_ConfigPtr->ChannelMapInfoPtr[Channel].ChMapCoreId != CoreId)
        {
            /* The logical channel is not mapped in current core */
            Dma_ReportError(ServiceId, DMA_E_CORE_CHANNEL_MISMATCH);
        }
        else if (CoreChIdx > Dma_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel)
        {
            /* Index in core is wrong */
            Dma_ReportError(ServiceId, DMA_E_CORE_CHANNEL_MISMATCH);
        }
        else
        {
            RetErr = E_OK;
        }
    }

    return RetErr;
}

#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_StartDaisyChainErrCheck
*
*   Service ID              : None.
*
*   Description             : DET checking for daisy chain start
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
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
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_StartDaisyChainErrCheck
(
    Dma_ChannelType Channel
)
{
    uint8                       DcMemberCnt;
    uint8                       DcIdx;
    Std_ReturnType              Err;
    Dma_ChStatusType            ChStatus;
    Mcal_CoreType               CoreId;
    const Dma_DaisyChainMapType *DcMapPtr;

    Err = E_OK;
    /* Checking if the channel is in daisy chain */
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    /* Get the logical daisy chain index */
    DcIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcIdx;
    if (DMA_INVALID_IDX != DcIdx)
    {
        /* Get the daisy chain configuration parameters */
        DcMapPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->DaisyChainListPtr[DcIdx];
        /* Judge if the channel is the member not the first in daisy chain */
        for (DcMemberCnt = 1U; (DcMemberCnt < DcMapPtr->DcMaxNum) && (E_OK == Err); DcMemberCnt++)
        {
            /* Get the channel status */
            ChStatus = Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[DcMapPtr->DcToChannelPtr[DcMemberCnt]];
            /* Judge if the channel is in transferring status */
            if ((DMA_CH_NONE != ChStatus) && (DMA_CH_TRANSFER_COMPLETE != ChStatus))
            {
                /* Daisy chain member is in transferring or suspend status, can not
                 * start the daisy chain */
                Err = E_NOT_OK;
            }
        }
    }

    return Err;
}

#if ((DMA_CFG_CHANNEL_CANCEL_API == STD_ON) || (DMA_CFG_CHANNEL_PAUSE_API == STD_ON))
/****************************************************************************************************
*   Function Name           : Dma_DaisyChainErrCheck
*
*   Service ID              : None.
*
*   Description             : DET checking for daisy chain
*
*   Parameters in           : ServiceId: Service id of calling API.
*                             Channel: Logical Channel ID and generated by EB tresos tool.
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
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_DaisyChainErrCheck
(
    Dma_ChannelType Channel
)
{
    uint8                       DcCnt;
    uint8                       DcMemberCnt;
    Std_ReturnType              Err;
    Mcal_CoreType               CoreId;
    const Dma_DaisyChainMapType *DcMapPtr;

    Err = E_OK;
    /* Checking if the channel is in daisy chain */

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    /* Loop all daisy chain */
    for (DcCnt = 0U;
        (DcCnt < Dma_ConfigPtr->CoreConfigPtr[CoreId]->MaxDaisyChain) && (E_OK == Err); DcCnt++)
    {
        /* Get the daisy chain configuration parameters */
        DcMapPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->DaisyChainListPtr[DcCnt];
        if (DMA_DAISYCHAIN_IDLE != Dma_StatusDataSetPtr[CoreId]->DcStatusPtr[DcCnt])
        {
            /* Daisy chain is in transferring or suspend status, can not
             * cancel/suspend/resume this channel separately */
            /* Judge if the channel is the member in the daisy chain */
            for (DcMemberCnt = 1U; (DcMemberCnt < DcMapPtr->DcMaxNum) && (E_OK == Err);
                                                                                 DcMemberCnt++)
            {
                /* Judge if the channel is the member in daisy chain */
                if (DcMapPtr->DcToChannelPtr[DcMemberCnt] == Channel)
                {
                    Err = E_NOT_OK;
                }
            }
        }
    }

    return Err;
}
#endif /* \((DMA_CFG_CHANNEL_CANCEL_API == STD_ON) || (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)) */
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */

#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
/****************************************************************************************************
*   Function Name           : Dma_GetTransferId
*
*   Service ID              : None.
*
*   Description             : Get current transfer ID of the logical channel
*
*   Parameters in           : Channel : Logical Channel ID and generated by EB tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Dma_TransferType: Current Logical transfer ID of the channel.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Dma_TransferType, DMA_PRIVATE_CODE) Dma_GetTransferId
(
    Dma_ChannelType Channel
)
{
    Dma_TransferType CurrTransferId;
    Dma_TransferType CoreTransferIdx;
    Mcal_CoreType    CoreId;

#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    /* Get the index position of transfer in current core */
    CoreTransferIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].ChTransferIdx;
    if (DMA_INVALID_IDX != CoreTransferIdx)
    {
        /* Get the transfer id of channel */
        CurrTransferId = Dma_StatusDataSetPtr[CoreId]->ChCurrTransferPtr[CoreTransferIdx];
    }
    else
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
    {
        /* If multiple configurations do not exists in channel, return 0 */
        CurrTransferId = 0U;
    }

    return CurrTransferId;
}
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */

#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_LliConfigChange
*
*   Service ID              : None.
*
*   Description             : Switch the linked list configuration of a logical channel.
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*                             LliId : Logical linked list ID and generated by EB tresos tool.
*                             ChConfigPtr: Channel configuration parameters.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, DMA_PRIVATE_CODE) Dma_LliConfigChange
(
    Dma_ChannelType Channel,
    Dma_LinkedListType LliId,
    CONSTP2CONST(Dma_ChConfigType, AUTOMATIC, DMA_APPL_CONST) ChConfigPtr
)
{
    Dma_HwUnitType                   PhyHwUnitId;
    uint8                            PhyChannelId;
    Dma_LinkedListType               LinkedListCnt;
    Dma_TransferType                 TransferId;
    const Dma_ChLinkedListConfigType *ChLliConfigPtr;
    Dma_LliCfgType                   LliConfig;
    const Dma_ChannelTransferConfig  *TransferConfigPtr;

    /* Get the HW unit ID and physical channel ID from logical channel ID */
    PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
    PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;

    ChLliConfigPtr = ChConfigPtr->ChLliConfigPtr;

    /* Initialize the linked list of current channel */
    for (LinkedListCnt = 0U;
            (LinkedListCnt < ChLliConfigPtr->LliMapInfoPtr[LliId].LliMaxNum); LinkedListCnt++)
    {
        TransferId =
            ChLliConfigPtr->LliMapInfoPtr[LliId].LliToTransferIdPtr[LinkedListCnt];
        TransferConfigPtr = &ChConfigPtr->ChTransferConfigPtr[TransferId].ChTransferConfig;
        LliConfig.source = TransferConfigPtr->source;
        LliConfig.destination = TransferConfigPtr->destination;
        LliConfig.transferWidth = TransferConfigPtr->transferWidth;
        LliConfig.transferSize = TransferConfigPtr->transferSize;

        if ((ChLliConfigPtr->LliMapInfoPtr[LliId].LliMaxNum - 1U) == LinkedListCnt)
        {
            /* Last member in linked list */
            LliConfig.linkedListItemAddress = (uint32)0U;
            /* TC interrupt enabled (include polling mode) */
            LliConfig.terminaCountInterEn = TRUE;
        }
        else
        {
            /* Point to the next member in linked list */
            /* #Violation: Dma_c_REF_3 */
            LliConfig.linkedListItemAddress = (uint32)(&ChLliConfigPtr->LliBufPtr[LinkedListCnt + 1U]);
            /* TC interrupt disabled */
            LliConfig.terminaCountInterEn = FALSE;
        }
        /* Write the linked list configuration information into linked list array */
        Dma_Hal_WriteLinkedListItem(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                    &ChLliConfigPtr->LliBufPtr[LinkedListCnt],
                                    &LliConfig);
    }
}
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */

#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ShadowingConfigChange
*
*   Service ID              : None.
*
*   Description             : Switch the shadowing operation configuration of a logical channel.
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*                             ShadowingId: Shadowing ID and generated by EB tresos tool.
*                             ChConfigPtr: Channel configuration parameters.
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ShadowingConfigChange
(
    Dma_ChannelType Channel,
    Dma_ShadowingType ShadowingId,
    CONSTP2CONST(Dma_ChConfigType, AUTOMATIC, DMA_APPL_CONST) ChConfigPtr
)
{
    boolean                          SafetyErr;
    Dma_HwUnitType                   PhyHwUnitId;
    uint8                            PhyChannelId;
    Dma_ShadowOperationConfig        ShadowingConfig;
    Dma_TransferType                 TransferId;
    const Dma_ChannelTransferConfig  *TransferConfigPtr;

    /* Get the HW unit ID and physical channel ID from logical channel ID */
    PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
    PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;

    TransferId = ChConfigPtr->ChShadowMapInfoPtr[ShadowingId].ShadowToTransferId;
    TransferConfigPtr = &ChConfigPtr->ChTransferConfigPtr[TransferId].ChTransferConfig;
    ShadowingConfig.source = TransferConfigPtr->source;
    ShadowingConfig.destination = TransferConfigPtr->destination;
    ShadowingConfig.transferWidth = TransferConfigPtr->transferWidth;
    ShadowingConfig.transferSize = TransferConfigPtr->transferSize;
#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
    if (DMA_INVALID_IDX != ChConfigPtr->ChShadowMapInfoPtr[ShadowingId].ShadowToLliId)
    {
        /* Linked list is enabled */
        /* Loading the configuration parameter into register */
        Dma_LliConfigChange(Channel,
                            ChConfigPtr->ChShadowMapInfoPtr[ShadowingId].ShadowToLliId,
                            ChConfigPtr);
        /* Linked list is valid in shadowing operation */
        ShadowingConfig.linkedListItemAddress =
                /* #Violation: Dma_c_REF_3 */
                (uint32)(&ChConfigPtr->ChLliConfigPtr->LliBufPtr[1]);
    }
    else
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */
    {
        /* Default linked list is unused for shadowing */
        ShadowingConfig.linkedListItemAddress = (uint32)0U;
    }
    /* Initialize the shadow channel configuration */
    SafetyErr = Dma_Hal_InitShadowOperation(Dma_BaseAddrs[PhyHwUnitId],
                                             PhyChannelId,
                                             &ShadowingConfig);

    return SafetyErr;
}
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dma_TerminalCountRefreshStatus
*
*   Service ID              : None.
*
*   Description             : Refresh the channel status after the channel terminal count event
*                             triggered.
*
*   Parameters in           : HwUnitId : DMA HW unit number
*                             PhyChannelId: Physical channel identification of a DMA.
*                             Channel: Logical channel ID and generated by tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : uint32: Channel status
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(uint32, DMA_PRIVATE_CODE) Dma_TerminalCountRefreshStatus
(
    Dma_HwUnitType  HwUnitId,
    uint8           PhyChannelId,
    Dma_ChannelType Channel
)
{
    uint8                        CoreChIdx;
#if ((DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) || (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) || \
     (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON))
    const Dma_ChConfigType       *ChConfigPtr;
#endif /* \((DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) || (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) || \
           (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)) */
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
    boolean                      ChEnStatus;
    Dma_TransferType             CurrTransferId;
    Dma_DoubleBufferFrozenStatus DblFrozenStatus;
    uint8                        DblBufId;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
    Mcal_CoreType                CoreId;
    uint32                       RetStatus;

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    /* Get the channel index in the current core */
    CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
    /* Get the status from status machine */
    RetStatus = (uint32)Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx];

#if ((DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) || (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) || \
     (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON))
    ChConfigPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx];
#endif /* \((DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) || (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) || \
           (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)) */

#if (DMA_CFG_CONTINUOUS_MODE_EN == STD_ON)
    if (TRUE == ChConfigPtr->ChContinuousMode)
    {
        /* Do not update the status machine, because the continuous mode will not stopped */
        RetStatus |= (uint32)DMA_CH_TRANSFER_COMPLETE;
    }
    else
#endif /* \(DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) */
#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
    if (NULL_PTR != ChConfigPtr->ChShadowMapInfoPtr)
    {
        /* Do not update the status machine, because the shadowing operation will not stopped */
        RetStatus |= (uint32)DMA_CH_TRANSFER_COMPLETE;
    }
    else
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */
    {
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_OFF)
        MCAL_UNUSED_VAR(HwUnitId);
        MCAL_UNUSED_VAR(PhyChannelId);
#else /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
        CurrTransferId = Dma_GetTransferId(Channel);
#else
        CurrTransferId = 0U;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
        /* Get index of double buffer configuration */
        DblBufId = ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChDoubleBufferId;
        if (DMA_INVALID_IDX != DblBufId)
        {
            /* Do not update the status machine, because the double buffer mode will not stop */
            /* Double buffer working in refill(continuous) mode */
            ChEnStatus = Dma_Hal_GetChannelEnableStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId);
            if (FALSE == ChEnStatus)
            {
                /* Channel is disabled by hardware automatically */
                /* Channel disabled due to software switch was not called in
                 * time after the transfer completed */
                RetStatus = (uint32)DMA_CH_NONE;
                Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_TRANSFER_COMPLETE;
            }
            else
            {
                /* Double Buffer frozen status */
                /* Get the double buffer status */
                DblFrozenStatus = Dma_Hal_GetDoubleBufferFrozenStatus(Dma_BaseAddrs[HwUnitId],
                                                                      PhyChannelId);
                if ((DMA_DOUBLEBUFFERFROZENSTATUS_NO_FROZEN != DblFrozenStatus) &&
                    (NULL_PTR !=
                       Dma_ConfigPtr->CommConfigPtr->DblBufConfigPtr[DblBufId].
                       DmaDblFrznNotificationPtr))
                {
                    Dma_ConfigPtr->CommConfigPtr->DblBufConfigPtr[DblBufId].
                    /* #Violation: Dma_c_REF_2 */
                        DmaDblFrznNotificationPtr(Channel, (Dma_DblFrznStatusType)DblFrozenStatus);
                    /* Refresh the status avoid user call other API to changed */
                    RetStatus = (uint32)Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx];
                }
                Dma_ChannelClrDblFrznStatus(HwUnitId, PhyChannelId, DblFrozenStatus);
            }
        }
        else
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
        {
            /* Complete transfer */
            RetStatus = (uint32)DMA_CH_TRANSFER_COMPLETE;
            Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_TRANSFER_COMPLETE;
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Dma_ResetChannelConfig
*
*   Service ID              : None.
*
*   Description             : Re-load the channel configuration parameters to register.
*
*   Parameters in           : Channel: Logical channel ID.
*                             PhyHwUnitId: HW unit number.
*                             PhyChannelId: Physical channel ID of a HW unit.
*                             ChConfigPtr: Channel configuration parameter.
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ResetChannelConfig
(
    Dma_ChannelType Channel,
    Dma_HwUnitType  PhyHwUnitId,
    uint8           PhyChannelId,
    CONSTP2CONST(Dma_ChConfigType, AUTOMATIC, DMA_APPL_CONST) ChConfigPtr
)
{
    boolean                   SafetyErr;
    Dma_TransferType          CurrTransferId;
#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
    Dma_ShadowingType         CoreShadowId;
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
    Dma_ShadowingType         CurrShadowId;
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
    Dma_DoubleBufferType      DblBufId;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
    Dma_ChannelTransferConfig TransferConfig;
    const Dma_ChannelTransferType *TransferPtr;
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API) */
#if (((DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) && (DMA_CFG_MULTI_SHADOWING_NUM != 0U)) ||\
     (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON))
    Mcal_CoreType             CoreId;
#endif /* \(((DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) && (DMA_CFG_MULTI_SHADOWING_NUM != 0U)) ||\
     (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)) */

    SafetyErr = TRUE;

#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
    CurrTransferId = Dma_GetTransferId(Channel);
#else
    CurrTransferId = 0U;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */

#if (((DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) && (DMA_CFG_MULTI_SHADOWING_NUM != 0U)) ||\
     (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON))
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
#endif /* \(((DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) && (DMA_CFG_MULTI_SHADOWING_NUM != 0U)) ||\
     (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)) */

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
    /* Get the transfer configuration of current transfer */
    TransferConfig = ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChTransferConfig;
    /* Pointer to the manual transfer configuration */
    TransferPtr = Dma_StatusDataSetPtr[CoreId]->ChTransManualPtr[
                     Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx];
    if (NULL_PTR != TransferPtr)
    {
        /* Update user manual configuration data */
        TransferConfig.source = TransferPtr->Source;
        TransferConfig.destination = TransferPtr->Destination;
        TransferConfig.transferWidth = TransferPtr->TransferWidth;
        TransferConfig.transferSize = TransferPtr->TransferSize;
    }

    /* Initialize the basic configuration of channel */
    SafetyErr &= Dma_Hal_InitChannelTransfer(Dma_BaseAddrs[PhyHwUnitId],
                                PhyChannelId,
                                &TransferConfig);
#else /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_OFF) */
    /* Initialize the basic configuration of channel */
    SafetyErr &= Dma_Hal_InitChannelTransfer(Dma_BaseAddrs[PhyHwUnitId],
                                PhyChannelId,
                                &ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChTransferConfig);
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API) */



#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
    /* Check if the linked list is enabled of current transfer in channel */
    if (DMA_INVALID_IDX != ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChLinkedListId)
    {
        /* Linked list is enabled */
        /* Loading the configuration parameter into register */
        Dma_LliConfigChange(Channel,
                            ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChLinkedListId,
                            ChConfigPtr);
        /* Initialize the linked list channel configuration */
        SafetyErr &= Dma_Hal_InitLinkedListItem(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                                &ChConfigPtr->ChLliConfigPtr->LliBufPtr[0]);
    }
#endif /* \(DMA_CFG_LINKEDLIST_EN  \== STD_OFF) */

#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
    /* Check if the shadowing operation is enabled */
    if (NULL_PTR != ChConfigPtr->ChShadowMapInfoPtr)
    {
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
        /* Find the shadowing index in current core */
        CoreShadowId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].ChShadowingIdx;
        if (DMA_INVALID_IDX != CoreShadowId)
        {
            /* Get the shadowing operation configuration ID of channel */
            CurrShadowId = Dma_StatusDataSetPtr[CoreId]->ChCurrShadowingPtr[CoreShadowId];
        }
        else
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
        {
            CurrShadowId = 0U;
        }
        /* Index 0 of configuration parameter is default to be used */
        SafetyErr &= Dma_ShadowingConfigChange(Channel, CurrShadowId, ChConfigPtr);
    }
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */

#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
    /* Get the double buffering ID that current transfer assigned */
    DblBufId = ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChDoubleBufferId;
    /* Check if the double buffering is enabled */
    if (DMA_INVALID_IDX != DblBufId)
    {
        /* Clear frozen flag before start */
        Dma_Hal_ClearDoubleBufferFrozenStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                              DMA_DOUBLEBUFFERSTATUSSELECT_BOTHBUFFER);
    }
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
    if (0U != ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChRemainCount)
    {
        /* Initialize the remaining transfer count value */
        SafetyErr &= Dma_Hal_SetTransferSizeThreshold(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                     ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChRemainCount);
    }
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN == STD_ON) */

#if ((DMA_CFG_MULTI_TRANSFER_NUM == 0U) && (DMA_CFG_LINKEDLIST_EN == STD_OFF) && \
        (DMA_CFG_SHADOWING_OPERATION_EN == STD_OFF))
    MCAL_UNUSED_VAR(Channel);
#endif /* \((DMA_CFG_MULTI_TRANSFER_NUM == 0U) && (DMA_CFG_LINKEDLIST_EN == STD_OFF) && \
        (DMA_CFG_SHADOWING_OPERATION_EN == STD_OFF)) */

    return SafetyErr;
}

/****************************************************************************************************
*   Function Name           : Dma_ChannelStartPrepare
*
*   Service ID              : None.
*
*   Description             : Prepare to start a channel
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*                             DaisyChainEnFlg: Daisy chain enable status.
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ChannelStartPrepare
(
    Dma_ChannelType Channel,
    boolean         DaisyChainEnFlg
)
{
    boolean                SafetyErr;
    uint8                  CoreChIdx;
    Dma_HwUnitType         PhyHwUnitId;
    uint8                  PhyChannelId;
    Mcal_CoreType          CoreId;
    const Dma_ChConfigType *ChConfigPtr;

    SafetyErr = TRUE;

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    /* Get the channel index in the current core */
    CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;

    /* Get the HW unit from Channel */
    PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
    /* Get the physical channel ID from Channel */
    PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
    /* Get the channel configuration parameters */
    ChConfigPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx];

#if (DMA_CFG_CHANNEL_NO_TRANSFER_EN == STD_ON)
    if (ChConfigPtr->IsTransCfgExists == TRUE)
#endif /* \(DMA_CFG_CHANNEL_NO_TRANSFER_EN == STD_ON) */
    {
        /* Reset the configuration parameters */
        SafetyErr &= Dma_ResetChannelConfig(Channel, PhyHwUnitId, PhyChannelId, ChConfigPtr);
    }

#if (DMA_CFG_INTERRUPT_EN == STD_ON)
    /* Clear the interrupt status first */
    Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                 ChConfigPtr->ChInterruptEnBits);
    /* Enable interrupts */
    SafetyErr &= Dma_Hal_EnableInterrupt(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                         ChConfigPtr->ChInterruptEnBits);
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    if (TRUE == DaisyChainEnFlg)
    {
        /* Enable the daisy chain function */
        (void)Dma_Hal_EnableDaisyChain(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
    }
    else
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    {
        /* Enable the channel */
        (void)Dma_Hal_EnableChannel(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
    }
#if (DMA_CFG_DAISYCHAIN_EN == STD_OFF)
    MCAL_UNUSED_VAR(DaisyChainEnFlg);
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */

    if (TRUE == SafetyErr)
    {
        /* Change the channel status to transferring status */
        Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_TRANSFERRING;
    }

    return SafetyErr;
}

#if (DMA_CFG_CHANNEL_CANCEL_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ChannelCancelPrepare
*
*   Service ID              : None.
*
*   Description             : Prepare to cancel a channel.
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*                             CancelMethod: Cancel channel method.
*                             DaisyChainEnFlg: Daisy chain enable status
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ChannelCancelPrepare
(
    Dma_ChannelType  Channel,
    Dma_ChCancelType CancelMethod,
    boolean          DaisyChainEnFlg
)
{
    boolean                SafetyErr;
    Dma_HwUnitType         PhyHwUnitId;
    uint8                  PhyChannelId;
    uint8                  CoreChIdx;
    Mcal_CoreType          CoreId;
#if (DMA_CFG_INTERRUPT_EN == STD_ON)
    const Dma_ChConfigType *ChConfigPtr;
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

    SafetyErr = TRUE;

    /* Get the HW unit from Channel */
    PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
    /* Get the physical channel ID from Channel */
    PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;

    /* Get the channel index in the current core */
    CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    if (DMA_CH_CANCEL_DIRECT == CancelMethod)
    {
        /* Cancel the channel */
        Dma_Hal_DisableChannel(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
    }
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292)
    else
    {
        /* Cancel the channel */
        SafetyErr &= Dma_Hal_SafeDisableChannel(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
    }
#endif /* \(MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292) */

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    if (TRUE == DaisyChainEnFlg)
    {
        SafetyErr &= Dma_Hal_DisableDaisyChain(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
    }
#else
    MCAL_UNUSED_VAR(DaisyChainEnFlg);
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */

    /* Clear status flags */
    Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                          DMA_CHANNELSTATUS_TC | DMA_CHANNELSTATUS_BUSERROR |
                          DMA_CHANNELSTATUS_SCB | DMA_CHANNELSTATUS_DCB |
                          DMA_CHANNELSTATUS_PAT | DMA_CHANNELSTATUS_THR);
#if (DMA_CFG_INTERRUPT_EN == STD_ON)
    /* Get the channel configuration parameters */
    ChConfigPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx];
    /* Clear the interrupt status first */
    Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                 ChConfigPtr->ChInterruptEnBits);
    /* Enable interrupts */
    SafetyErr &= Dma_Hal_DisableInterrupt(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                            ChConfigPtr->ChInterruptEnBits);
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

    if (TRUE == SafetyErr)
    {
        /* Reset the channel status */
        Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_NONE;
    }

    return SafetyErr;
}
#endif /* \(DMA_CFG_CHANNEL_CANCEL_API == STD_ON) */

#if (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292)
/****************************************************************************************************
*   Function Name           : Dma_ChannelSuspendPrepare
*
*   Service ID              : None.
*
*   Description             : Prepare to suspend a channel
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ChannelSuspendPrepare
(
    Dma_ChannelType  Channel
)
{
    boolean                SafetyErr;
    Dma_HwUnitType         PhyHwUnitId;
    uint8                  PhyChannelId;
    uint8                  CoreChIdx;
    Mcal_CoreType          CoreId;
#if (DMA_CFG_INTERRUPT_EN == STD_ON)
    const Dma_ChConfigType *ChConfigPtr;
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;

    /* Get the HW unit from Channel */
    PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
    /* Get the physical channel ID from Channel */
    PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
    /* Pause the channel from the busy status */
    SafetyErr = Dma_Hal_SuspendChannel(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);

#if (DMA_CFG_INTERRUPT_EN == STD_ON)
    /* Get the channel configuration parameters */
    ChConfigPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx];
    /* Disable the interrupts(Suspend the interrupt handler) */
    SafetyErr &= Dma_Hal_DisableInterrupt(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                            ChConfigPtr->ChInterruptEnBits);
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

    if (TRUE == SafetyErr)
    {
        /* Change the channel status to suspend status */
        Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_SUSPENDED;
    }

    return SafetyErr;
}

/****************************************************************************************************
*   Function Name           : Dma_ChannelResumePrepare
*
*   Service ID              : None.
*
*   Description             : Prepare to resume a channel.
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ChannelResumePrepare
(
    Dma_ChannelType  Channel
)
{
    boolean        SafetyErr;
    Dma_HwUnitType PhyHwUnitId;
    uint8          PhyChannelId;
    uint8          CoreChIdx;
    Mcal_CoreType  CoreId;
#if (DMA_CFG_INTERRUPT_EN == STD_ON)
    const Dma_ChConfigType *ChConfigPtr;
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;

    /* Get the HW unit from Channel */
    PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
    /* Get the physical channel ID from Channel */
    PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
    /* Resume the channel from the paused status */
    SafetyErr = Dma_Hal_ResumeChannel(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);

#if (DMA_CFG_INTERRUPT_EN == STD_ON)
    /* Get the channel configuration parameters */
    ChConfigPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx];
    /* Enable the interrupts(Resume the interrupt handler) */
    SafetyErr &= Dma_Hal_EnableInterrupt(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                        ChConfigPtr->ChInterruptEnBits);
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

    if (TRUE == SafetyErr)
    {
        /* Change channel status to transferring status */
        Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_TRANSFERRING;
    }

    return SafetyErr;
}
#endif /* \(MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292) */
#endif /* \(DMA_CFG_CHANNEL_PAUSE_API == STD_ON) */

#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ChannelClrDblFrznStatus
*
*   Service ID              : None.
*
*   Description             : Clear the frozen status of a channel.
*
*   Parameters in           : PhyHwUnitId: HW unit number.
*                             PhyChannelId: Physical channel number.
*                             FrznStatus: channel frozen status.
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
static FUNC(void, DMA_PRIVATE_CODE) Dma_ChannelClrDblFrznStatus
(
    Dma_HwUnitType  PhyHwUnitId,
    uint8           PhyChannelId,
    Dma_DoubleBufferFrozenStatus FrznStatus
)
{
    if (DMA_DOUBLEBUFFERFROZENSTATUS_BUFFER0_FROZEN == FrznStatus)
    {
        Dma_Hal_ClearDoubleBufferFrozenStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                              DMA_DOUBLEBUFFERSTATUSSELECT_BUFFER0);
    }
    else if (DMA_DOUBLEBUFFERFROZENSTATUS_BUFFER1_FROZEN == FrznStatus)
    {
        Dma_Hal_ClearDoubleBufferFrozenStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                              DMA_DOUBLEBUFFERSTATUSSELECT_BUFFER1);
    }
    else if ((DMA_DOUBLEBUFFERFROZENSTATUS_BOTH_FROZEN_BUFFER0FIRST == FrznStatus) ||
             (DMA_DOUBLEBUFFERFROZENSTATUS_BOTH_FROZEN_BUFFER1FIRST == FrznStatus))
    {
        Dma_Hal_ClearDoubleBufferFrozenStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                              DMA_DOUBLEBUFFERSTATUSSELECT_BOTHBUFFER);
    }
    else
    /* #Violation: Dma_c_REF_9 */
    {
        /* Do Nothing */
    }
}
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_RefreshDaisyChainStatus
*
*   Service ID              : None.
*
*   Description             : Refresh the status of all channels in the daisy chain.
*
*   Parameters in           : DcFirstCh: The logical ID of the first channel in the daisy chain.
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_RefreshDaisyChainStatus
(
    Dma_ChannelType DcFirstCh
)
{
    boolean                      SafetyErr;
    Dma_HwUnitType               PhyHwUnitId;
    uint8                        PhyChannelId;
#if (DMA_CFG_CONTINUOUS_MODE_EN == STD_ON)
    uint8                        CoreChIdx;
    boolean                      IsContinuoursMode;
#endif /* \(DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) */
    uint8                        DcIdx;
    uint8                        DcCnt;
    Dma_ChannelType              DcChannel;
    const Dma_DaisyChainMapType  *DcPtr;
    Mcal_CoreType                CoreId;

    SafetyErr = TRUE;

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

    /* This channel is the head of the daisy chain */
    /* Get the logical daisy chain ID through the first channel of the daisy chain */
    DcIdx = Dma_ConfigPtr->ChannelMapInfoPtr[DcFirstCh].CoreDcIdx;
    if (DMA_DAISYCHAIN_TRANSFERRING == Dma_StatusDataSetPtr[CoreId]->DcStatusPtr[DcIdx])
    {
        /* The daisy chain is in transferring status */
#if (DMA_CFG_CONTINUOUS_MODE_EN == STD_ON)
        /* Get the index of the first channel in daisy in current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[DcFirstCh].CoreChIdx;
        /* Get the refill mode enable status */
        IsContinuoursMode = Dma_ConfigPtr->CoreConfigPtr[CoreId]->
                                       ChannelConfigPtr[CoreChIdx].ChContinuousMode;
#endif /* \(DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) */
        /* Load daisy chain configuration parameters */
        DcPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->DaisyChainListPtr[DcIdx];
        /* Do not loop last channel  */
        for (DcCnt = 0U; ((DcCnt < DcPtr->DcMaxNum) && (TRUE == SafetyErr)); DcCnt++)
        {
            /* Get the channel that daisy chain member assigned */
            DcChannel = DcPtr->DcToChannelPtr[DcCnt];
            /* Get the HW unit from Channel */
            PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[DcChannel].HwUnitId;
            /* Get the physical channel ID from Channel */
            PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[DcChannel].PhyChannelId;
            /* Update the status machine */
            (void)Dma_TerminalCountRefreshStatus(PhyHwUnitId, PhyChannelId, DcChannel);
#if (DMA_CFG_CONTINUOUS_MODE_EN == STD_ON)
            if ((DcCnt != 0U) && (FALSE == IsContinuoursMode))
#endif /* \(DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) */
            {
                /* Disable the daisy chain when head channel is not working in continuous mode */
                SafetyErr &= Dma_Hal_DisableDaisyChain(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
            }
            /* Clear channel transfer completed status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                DMA_CHANNELSTATUS_TC);
        }
#if (DMA_CFG_CONTINUOUS_MODE_EN == STD_ON)
        if (FALSE == IsContinuoursMode)
#endif /* \(DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) */
        {
            /* If continuous mode is not enabled in head channel, set the daisy chain to
             * IDLE status */
            Dma_StatusDataSetPtr[CoreId]->DcStatusPtr[DcIdx] = DMA_DAISYCHAIN_IDLE;
        }
    }

    return SafetyErr;
}

#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dma_InitSingleChannel
*
*   Service ID              : None.
*
*   Description             : Initialize a channel.
*
*   Parameters in           : ConfigPtr: Pointer to the configuration parameter entry
*                             CoreId: Core ID
*                             ChannelCnt: Channel index in current core.
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_InitSingleChannel
(
    CONSTP2CONST(Dma_ConfigType, AUTOMATIC, DMA_APPL_CONST) ConfigPtr,
    Mcal_CoreType CoreId,
    uint8 ChannelCnt
)
{
    boolean                SafetyErr;
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
    Dma_DoubleBufferType   DblBufId;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
    Dma_CircularBufferType CircBufId;
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */
#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
    Dma_PatternType        PatternId;
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
    Dma_TransferType       TransferId;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
    Dma_TransferType       ShadowingId;
#endif  /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    uint8                  DcId;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    Dma_HwUnitType         PhyHwUnitId;
    uint8                  PhyChannelId;
    const Dma_ChConfigType *ChConfigPtr;

    SafetyErr = TRUE;

    /* Get the channel configuration information */
    ChConfigPtr = &(ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelCnt]);

#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
    TransferId = ConfigPtr->ChannelMapInfoPtr[ChConfigPtr->ChannelId].ChTransferIdx;
    if (DMA_INVALID_IDX != TransferId)
    {
        Dma_StatusDataSetPtr[CoreId]->ChCurrTransferPtr[TransferId] = 0U;
    }
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */

#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
    ShadowingId = ConfigPtr->ChannelMapInfoPtr[ChConfigPtr->ChannelId].ChShadowingIdx;
    if (DMA_INVALID_IDX != ShadowingId)
    {
        Dma_StatusDataSetPtr[CoreId]->ChCurrShadowingPtr[ShadowingId] = 0U;
    }
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */

    /* Reset the default status */
    Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[ChannelCnt] = DMA_CH_NONE;
#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
    /* Clear channel transfer pointer */
    Dma_StatusDataSetPtr[CoreId]->ChTransManualPtr[ChannelCnt] = NULL_PTR;
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    DcId = ConfigPtr->ChannelMapInfoPtr[ChConfigPtr->ChannelId].CoreDcIdx;
    if (DMA_INVALID_IDX != DcId)
    {
        Dma_StatusDataSetPtr[CoreId]->DcStatusPtr[DcId] = DMA_DAISYCHAIN_TRANSFERRING;
    }
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */

    PhyChannelId = ConfigPtr->ChannelMapInfoPtr[ChConfigPtr->ChannelId].PhyChannelId;
    PhyHwUnitId  = ConfigPtr->ChannelMapInfoPtr[ChConfigPtr->ChannelId].HwUnitId;

    /* Enable DMA privileged access mode default */
    SafetyErr &= Dma_Hal_SetChannelAccessMode(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                              DMA_ACCESSMODE_PRIVILEGED);

#if (DMA_CFG_CHANNEL_NO_TRANSFER_EN == STD_ON)
    if (ChConfigPtr->IsTransCfgExists == FALSE)
    {
        /* Initialize channel transfer configuration */
        SafetyErr &= Dma_Hal_InitChannelTransfer(Dma_BaseAddrs[PhyHwUnitId],
                                    PhyChannelId,
                                    &ChConfigPtr->ChTransferConfigPtr[0U].ChTransferConfig);
    }
#endif /* \(DMA_CFG_CHANNEL_NO_TRANSFER_EN == STD_ON) */

#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
    DblBufId = ChConfigPtr->ChTransferConfigPtr[0U].ChDoubleBufferId;
    if (DMA_INVALID_IDX != DblBufId)
    {
        /* Initialize double buffer feature */
        SafetyErr &= Dma_Hal_InitDoubleBuffer(Dma_BaseAddrs[PhyHwUnitId],
                                 PhyChannelId,
                                 &ConfigPtr->CommConfigPtr->DblBufConfigPtr[DblBufId].DblBufConfig);
        Dma_Hal_ClearDoubleBufferFrozenStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                              DMA_DOUBLEBUFFERSTATUSSELECT_BOTHBUFFER);
    }
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */

#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
    CircBufId = ChConfigPtr->ChTransferConfigPtr[0U].ChCircularBufferId;
    if (DMA_INVALID_IDX != CircBufId)
    {
        /* Initialize circular buffer feature */
        SafetyErr &= Dma_Hal_InitCircularBuffer(Dma_BaseAddrs[PhyHwUnitId],
                                   PhyChannelId,
                                   &ConfigPtr->CommConfigPtr->CircBufConfigPtr[CircBufId]);
    }
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */

#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
    PatternId = ChConfigPtr->ChTransferConfigPtr[0U].ChPatternId;
    if (DMA_INVALID_IDX != PatternId)
    {
        /* Initialize match pattern feature */
        SafetyErr &= Dma_Hal_InitMatchPattern(Dma_BaseAddrs[PhyHwUnitId],
                                 PhyChannelId,
                                 &ConfigPtr->CommConfigPtr->PatternConfigPtr[PatternId]);
    }
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */

#if (DMA_CFG_CONTINUOUS_MODE_EN == STD_ON)
    if (TRUE == ChConfigPtr->ChContinuousMode)
    {
        /* Enable continuous mode */
        SafetyErr &= Dma_Hal_EnableContinuousMode(Dma_BaseAddrs[PhyHwUnitId],
                                               PhyChannelId);
    }
#endif /* \(DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) */

    return SafetyErr;
}

/****************************************************************************************************
*   Function Name           : Dma_GetChannelEvent
*
*   Service ID              : None.
*
*   Description             : Get channel event status.
*
*   Parameters in           : Channel: Logical channel ID and generated by EB tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : ChStatusPtr: Pointer to the channel event status.
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
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_GetChannelEvent
(
    Dma_ChannelType Channel,
    P2VAR(uint32, AUTOMATIC, DMA_APPL_DATA) ChStatusPtr
)
{
    boolean                      SafetyErr;
    Dma_HwUnitType               PhyHwUnitId;
    uint8                        PhyChannelId;
    uint8                        CoreChIdx;
#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
    Dma_PatternType              CurrPatternIdx;
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */
#if ((DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) || (DMA_CFG_PATTERN_MATCH_EN == STD_ON))
    Dma_TransferType             CurrTransferId;
#endif /* \((DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) || (DMA_CFG_PATTERN_MATCH_EN == STD_ON)) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    Dma_ChannelType              DcFirstCh;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    uint32                       ChEvent;
    Mcal_CoreType                CoreId;
#if (((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_TC_INTERRUPT_EN == STD_ON)) ||  \
     ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)) || \
     (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) ||                                     \
     (DMA_CFG_PATTERN_MATCH_EN == STD_ON))
    const Dma_ChConfigType       *ChConfigPtr;
#endif /* \(((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_TC_INTERRUPT_EN == STD_ON)) ||  \
     ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)) || \
     (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) ||                                     \
     (DMA_CFG_PATTERN_MATCH_EN == STD_ON)) */

    SafetyErr = TRUE;
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();
    /* Get the HW unit from Channel */
    PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
    /* Get the physical channel ID from Channel */
    PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
    /* Get the channel index in current core */
    CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
#if (((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_TC_INTERRUPT_EN == STD_ON)) ||  \
 ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)) || \
 (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) ||                                     \
 (DMA_CFG_PATTERN_MATCH_EN == STD_ON))
    ChConfigPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx];
#endif /* \(((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_TC_INTERRUPT_EN == STD_ON)) ||  \
 ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)) || \
 (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) ||                                     \
 (DMA_CFG_PATTERN_MATCH_EN == STD_ON)) */

#if ((DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) || (DMA_CFG_PATTERN_MATCH_EN == STD_ON))
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
    CurrTransferId = Dma_GetTransferId(Channel);
#else /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
    CurrTransferId = 0U;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
#endif /* \((DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) || (DMA_CFG_PATTERN_MATCH_EN == STD_ON)) */

    DMA_ENTER_CRITICAL_SECTION(GetChannelStatus);

    /* Get status from status machine */
    *ChStatusPtr = (uint32)Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx];

#if ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_TC_INTERRUPT_EN == STD_ON))
    if (0U == ((uint8)DMA_CH_INT_TC & ChConfigPtr->ChInterruptEnBits))
#endif /* \((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_TC_INTERRUPT_EN == STD_ON)) */
    {
        /* Terminal count interrupt is not enabled in current channel,
         * When interrupt enabled, the status will be updated by interrupt handler */
        /* Get channel transfer completed status */
        ChEvent =
           Dma_Hal_GetStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId, DMA_CHANNELSTATUS_TC);
        if (DMA_CHANNELSTATUS_TC == ChEvent)
        {
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
            /* Get the first logical channel ID in daisy chain */
            DcFirstCh = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcFirstCh;
            if (DcFirstCh != DMA_INVALID_IDX)
            {
                SafetyErr &= Dma_RefreshDaisyChainStatus(DcFirstCh);
            }
            else
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
            {
                /* Update the status machine */
                *ChStatusPtr =
                        Dma_TerminalCountRefreshStatus(PhyHwUnitId, PhyChannelId, Channel);
                /* Clear channel transfer completed status */
                Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                     DMA_CHANNELSTATUS_TC);
            }
        }
    }

#if ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_ERR_INTERRUPT_EN == STD_ON))
    if (0U == ((uint8)DMA_CH_INT_ERROR & ChConfigPtr->ChInterruptEnBits))
#endif /* \((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)) */
    {
        /* Error interrupt is not enabled in current channel,
         * When interrupt enabled, the status will be updated by interrupt handler */
        /* Get error event status */
        ChEvent =
                Dma_Hal_GetStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                  DMA_CHANNELSTATUS_BUSERROR);
        if (DMA_CHANNELSTATUS_BUSERROR == ChEvent)
        {
            *ChStatusPtr |= (uint32)DMA_CH_ERROR;
            /* Status machine shall be reset */
            Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_NONE;
            /* Cancel the channel */
            Dma_Hal_DisableChannel(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
            /* Clear error event status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                DMA_CHANNELSTATUS_BUSERROR);

            DMA_EXIT_CRITICAL_SECTION(GetChannelStatus);

#if (DMA_DEV_ERROR_DETECT == STD_ON)
            /* Bus error occurred while data transferring or linked list item loading */
            Dma_ReportError(DMA_SID_GETCHANNELSTATUS, DMA_E_BUSERROR);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

            DMA_ENTER_CRITICAL_SECTION(GetChannelStatus);
        }
    }

#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
    /* Circular buffer used in current channel */
    if (DMA_INVALID_IDX !=
            ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChCircularBufferId)
    {
#if ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON))
        if (0U == ((uint8)DMA_CH_INT_SCB & Dma_ConfigPtr->
                CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].ChInterruptEnBits))
#endif /* \((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)) */
        {
            /* Source circular buffer rollback is not enabled in current channel */
            /* Get source circular buffer rollback event */
            ChEvent = Dma_Hal_GetStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                                      DMA_CHANNELSTATUS_SCB);
            if (DMA_CHANNELSTATUS_SCB == ChEvent)
            {
                *ChStatusPtr |= (uint32)DMA_CH_SCB;
                /* Clear source circular buffer rollback event status */
                Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                                             DMA_CHANNELSTATUS_SCB);
            }
        }

#if ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON))
        if (0U == ((uint8)DMA_CH_INT_DCB & Dma_ConfigPtr->
            CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].ChInterruptEnBits))
#endif /* \((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)) */
        {
            /* Get destination circular buffer rollback event */
            ChEvent = Dma_Hal_GetStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                                             DMA_CHANNELSTATUS_DCB);
            if (DMA_CHANNELSTATUS_DCB == ChEvent)
            {
                *ChStatusPtr |= (uint32)DMA_CH_DCB;
                /* Clear destination circular buffer rollback event status */
                Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                                             DMA_CHANNELSTATUS_DCB);
            }
        }
    }
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */

#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
    if (DMA_INVALID_IDX != ChConfigPtr->ChTransferConfigPtr[CurrTransferId].ChPatternId)
    {
#if ((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON))
        if (0U == ((uint8)DMA_CH_INT_PATTERN & Dma_ConfigPtr->
                CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].ChInterruptEnBits))
#endif /* \((DMA_CFG_INTERRUPT_EN == STD_ON) && (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)) */
        {
            /* Get data pattern matched event status */
            ChEvent =
                Dma_Hal_GetStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                                             DMA_CHANNELSTATUS_PAT);
            if (DMA_CHANNELSTATUS_PAT == ChEvent)
            {
                CurrPatternIdx = Dma_ConfigPtr->CoreConfigPtr[CoreId]->
                        ChannelConfigPtr[CoreChIdx].ChTransferConfigPtr[CurrTransferId].
                                                                        ChPatternId;
                if (TRUE == Dma_ConfigPtr->CommConfigPtr->PatternConfigPtr[CurrPatternIdx].
                                                                        patternMatchedStop)
                {
                    /* Stop after data matched function is enabled */
                    /* Change the channel transfer status to none */
                    Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_NONE;
                }
                *ChStatusPtr |= (uint32)DMA_CH_PATTERN_MATCHED;
                /* Clear data pattern matched event status */
                Dma_Hal_ClearStatus(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                                                DMA_CHANNELSTATUS_PAT);
            }
        }
    }
#endif /* \(DMA_CFG_PATTERN_MATCH_EN) */

    DMA_EXIT_CRITICAL_SECTION(GetChannelStatus);

    return SafetyErr;
}

#if (DMA_CFG_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_DeInitAllChannels
*
*   Service ID              : None.
*
*   Description             : De-initialize the all channels.
*
*   Parameters in           : CoreId: Core ID
*                             MaxChannel: Maximum channel number in current core.
*
*   Parameters inout        : SafetyErrPtr: Pointer to store the safety error status.
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
static FUNC(Std_ReturnType, DMA_PRIVATE_CODE) Dma_DeInitAllChannels
(
    Mcal_CoreType  CoreId,
    uint8          MaxChannel,
    P2VAR(boolean, AUTOMATIC, DMA_APPL_DATA) SafetyErrPtr
)
{
    uint8           ChannelCnt;
    Dma_ChannelType Channel;
    Std_ReturnType  RetErr;

    RetErr = E_OK;

    for (ChannelCnt = 0U;
         (ChannelCnt < MaxChannel) && (E_OK == RetErr);
         ChannelCnt++)
    {
        if ((DMA_CH_TRANSFERRING == Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[ChannelCnt]) ||
            (DMA_CH_SUSPENDED   == Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[ChannelCnt]))
        {
#if (DMA_DEV_ERROR_DETECT == STD_ON)
            Dma_ReportError(DMA_SID_DEINIT, DMA_E_CHANNEL_TRANSFERING);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
            RetErr = E_NOT_OK;
        }
        else
        {
            /* Get channel ID in core */
            Channel =
                Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelCnt].ChannelId;

            /* De-initialize the specified channel */
            *SafetyErrPtr &= Dma_Hal_DeInitChannel(
                            Dma_BaseAddrs[Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId],
                            Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId);

            if (TRUE == *SafetyErrPtr)
            {
                /* Reset the status */
                Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[ChannelCnt] = DMA_CH_NONE;
            }
            else
            {
                /* Regisrer write error */
                RetErr = E_NOT_OK;
            }
        }
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Dma_ResetHwUnits
*
*   Service ID              : None.
*
*   Description             : Reset the all DMA hardware units.
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
*   Return value            : TRUE: No safety error.
*                             FALSE: Safety error detected.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_ResetHwUnits
(
    void
)
{
    uint8           HWUnitCnt;
    Dma_HwUnitType  PhyHwUnitId;
    boolean         SafetyErr;
    Std_ReturnType  LockStatus;

    SafetyErr = TRUE;

    for (HWUnitCnt = 0U;
         (HWUnitCnt < Dma_ConfigPtr->HwUnitConfigPtr->MaxHwUnitNum) && (TRUE == SafetyErr);
         HWUnitCnt++)
    {
        PhyHwUnitId = Dma_ConfigPtr->HwUnitConfigPtr->HwUnitListPtr[HWUnitCnt];

        DMA_ENTER_CRITICAL_SECTION(DeInit);

        /* Get RCC lock to avoid reset register conflict */
        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_RCC);
        if (E_OK == LockStatus)
        {
            /* Reset the DMA hardware unit */
            SafetyErr &= Dma_Hal_ResetDma(Dma_BaseAddrs[PhyHwUnitId]);

            /* Release the lock after completing register settings. */
            Mcal_ReleaseLock(MCAL_LOCK_ID_RCC);
        }
        else
        {
            /* Get lock failed */
            SafetyErr = FALSE;
        }

        DMA_EXIT_CRITICAL_SECTION(DeInit);

        /* Disable the DMA hardware unit */
        SafetyErr &= Dma_Hal_DisableDma(Dma_BaseAddrs[PhyHwUnitId]);
    }

    return SafetyErr;
}
#endif /* \(DMA_CFG_DEINIT_API == STD_ON) */

#if (DMA_CFG_CHANNEL_CANCEL_API == STD_ON)
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_CancelDaisyChainMembers
*
*   Service ID              : None.
*
*   Description             : Cacel the daisy chain in channel.
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*                             CancelMethod: Cancel channel method.
*                             CoreId: Core ID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : None.
*
*   Return value            : TRUE: No safety error.
*                             FALSE: Safety error detected.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, DMA_PRIVATE_CODE) Dma_CancelDaisyChainMembers
(
    Dma_ChannelType             Channel,                          
    Dma_ChCancelType            CancelMethod,               
    Mcal_CoreType               CoreId
)
{
    boolean                     SafetyErr;
    uint8                       DcCnt;
    uint8                       DcIdx;
    Dma_ChannelType             DcChannel;
    const Dma_DaisyChainMapType *DcPtr;

    SafetyErr = TRUE;

    /* Get daisy chain ID in current core */
    DcIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcIdx;
    if (DMA_INVALID_IDX != DcIdx)
    {
        /* Set the daisy chain status to idle */
        Dma_StatusDataSetPtr[CoreId]->DcStatusPtr[DcIdx] = DMA_DAISYCHAIN_IDLE;
        /* Get daisy chain configuration parameters */
        DcPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->DaisyChainListPtr[DcIdx];
        /* Loop to cancel all members in daisy chain */
        for (DcCnt = 1U; ((DcCnt < DcPtr->DcMaxNum) && (TRUE == SafetyErr)); DcCnt++)
        {
            DcChannel = DcPtr->DcToChannelPtr[DcCnt];
            /* Cancel the daisy chain member */
            SafetyErr = Dma_ChannelCancelPrepare(DcChannel, CancelMethod, TRUE);
        }
    }

    return SafetyErr;
}
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
#endif /* \(DMA_CFG_CHANNEL_CANCEL_API == STD_ON) */

#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

/****************************************************************************************************
*   Function Name           : Dma_Init
*
*   Service ID              : 0x00
*
*   Description             : Initializes the Dma hardware units and driver.
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
*   Preconditions           : Dma driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_Init
(
    CONSTP2CONST(Dma_ConfigType, AUTOMATIC, DMA_APPL_CONST) ConfigPtr
)
{
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType         Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    boolean                SafetyErr;
    uint8                  HWUnitCnt;
    uint8                  ChannelCnt;
    Mcal_CoreType          CoreId;

    SafetyErr = TRUE;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Err = Dma_CheckInitParam(ConfigPtr);
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get core id which core is currently executing */
        /* #Violation: Dma_c_REF_1 */
        CoreId = Mcal_GetCoreId();

        if (NULL_PTR != ConfigPtr->CoreConfigPtr[CoreId])
        {
            for (ChannelCnt = 0U;
                    ChannelCnt < ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel;
                    ChannelCnt++)
            {
                SafetyErr &= Dma_InitSingleChannel(ConfigPtr, CoreId, ChannelCnt);
            }
        }

        if (MCAL_MASTER_CORE == CoreId)
        {
            /* Initialize the all HW units */
            for (HWUnitCnt = 0U;
                    ((HWUnitCnt < ConfigPtr->HwUnitConfigPtr->MaxHwUnitNum) &&
                            (TRUE == SafetyErr)); HWUnitCnt++)
            {
                /* Enable DMA HW units */
                SafetyErr &= Dma_Hal_EnableDma(
                        Dma_BaseAddrs[ConfigPtr->HwUnitConfigPtr->HwUnitListPtr[HWUnitCnt]]);
            }

#if (DMA_SAFETY_ENABLE == STD_ON)
            if (TRUE == SafetyErr)
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
            {
                /* Store ConfigPtr to use for other APIs when 'Dma_ConfigPtr' is not NULL */
                Dma_ConfigPtr = ConfigPtr;
            }
        }

#if (DMA_DEV_ERROR_DETECT == STD_ON)
#if (DMA_SAFETY_ENABLE == STD_ON)
        if (TRUE == SafetyErr)
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
        {
            *(Dma_CoreInitStatusSetPtr[CoreId]) = DMA_INITIALIZED;
        }
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    }

#if (DMA_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dma_ReportRuntimeError(DMA_SID_INIT);
    }
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
}

#if (DMA_CFG_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_DeInit
*
*   Service ID              : 0x01
*
*   Description             : Reset all run-time variables and registers and set the Dma module to
*                             uninitialized status.
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
*   Preconditions           : Dma driver must have been initialized before.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_DeInit
(
    void
)
{
    Std_ReturnType  Err;
    boolean         SafetyErr;
    Mcal_CoreType   CoreId;

    SafetyErr = TRUE;
    /* Get core id which core is currently executing */
    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Err = Dma_CheckDeInit(CoreId);
    if (E_OK == Err)
#else
    Err = E_OK;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        if (NULL_PTR != Dma_ConfigPtr->CoreConfigPtr[CoreId])
        {
            /* De-initialize the all channels */
            Err = Dma_DeInitAllChannels(CoreId,
                                        Dma_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel,
                                        &SafetyErr);
        }

        if (E_OK == Err)
        {
            if (MCAL_MASTER_CORE == CoreId)
            {
                /* De-initialize the all HW units */
                /* #Violation: Dma_c_REF_11 */
                SafetyErr &= Dma_ResetHwUnits();

                if (TRUE == SafetyErr)
                {
                    Dma_ConfigPtr = NULL_PTR;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
                    /* Change the core init status to uninitialized */
                    *(Dma_CoreInitStatusSetPtr[CoreId]) = DMA_UNINITIALIZE;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
                }
            }
            else
            {
#if (DMA_DEV_ERROR_DETECT == STD_ON)
                /* Change the core init status to uninitialized */
                *(Dma_CoreInitStatusSetPtr[CoreId]) = DMA_UNINITIALIZE;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
            }
        }

#if (DMA_SAFETY_ENABLE == STD_ON)
        if (FALSE == SafetyErr)
        {
            Dma_ReportRuntimeError(DMA_SID_DEINIT);
        }
#else
        MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
    }
}
#endif /* \(DMA_CFG_DEINIT_API == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dma_ChannelStart
*
*   Service ID              : 0x02
*
*   Description             : Start a channel data transfer
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : None.
*
*   Preconditions           : Dma driver must have been initialized before and the channel must in
*                             transferring or suspended status.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelStart
(
    Dma_ChannelType Channel
)
{
#if ((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_CFG_DAISYCHAIN_EN == STD_ON))
    Std_ReturnType              Err;
#endif /* \((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_CFG_DAISYCHAIN_EN == STD_ON)) */
    boolean                     SafetyErr;
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    uint8                       DcCnt;
    uint8                       DcIdx;
    Dma_ChannelType             DcChannel;
    const Dma_DaisyChainMapType *DcPtr;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    uint8                       CoreChIdx;
    Mcal_CoreType               CoreId;

    SafetyErr = TRUE;

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_CHANNELSTART);
    if (E_OK == Err)
    {
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_CHANNELSTART, Channel);
    }
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get the channel index in the current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;

        DMA_ENTER_CRITICAL_SECTION(ChannelStart);

        if ((DMA_CH_NONE == Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]) ||
            (DMA_CH_TRANSFER_COMPLETE == Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]))
        {
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
            Err = Dma_StartDaisyChainErrCheck(Channel);
            if (E_OK == Err)
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
            {
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
                DcIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcIdx;
                if (DMA_INVALID_IDX != DcIdx)
                {
                    /* Daisy chain is enabled */
                    /* Change the status to busy with daisy chain */
                    Dma_StatusDataSetPtr[CoreId]->DcStatusPtr[DcIdx] = DMA_DAISYCHAIN_TRANSFERRING;
                    /* Get the daisy chain configuration information  */
                    DcPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->DaisyChainListPtr[DcIdx];
                    for (DcCnt = 1U; ((DcCnt < DcPtr->DcMaxNum) && (TRUE == SafetyErr)); DcCnt++)
                    {
                        /* Get the channel that daisy chain member assigned */
                        DcChannel = DcPtr->DcToChannelPtr[DcCnt];
                        /* Load other channels as daisy chain mode */
                        SafetyErr = Dma_ChannelStartPrepare(DcChannel, TRUE);
                    }
                }
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
                /* Start the channel */
                SafetyErr &= Dma_ChannelStartPrepare(Channel, FALSE);
            }
            DMA_EXIT_CRITICAL_SECTION(ChannelStart);

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if (DMA_DEV_ERROR_DETECT == STD_ON)
            if (E_NOT_OK == Err)
            {
                /* The channel is not the first member in daisy chain */
                Dma_ReportError(DMA_SID_CHANNELSTART, DMA_E_DAISYCHAIN_START_FAILED);
            }
#endif /* DMA_DEV_ERROR_DETECT == STD_ON */
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
        }
        else
        {
            DMA_EXIT_CRITICAL_SECTION(ChannelStart);

#if (DMA_DEV_ERROR_DETECT == STD_ON)
            Dma_ReportError(DMA_SID_CHANNELSTART, DMA_E_CHANNEL_TRANSFERING);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        }
    }

#if (DMA_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dma_ReportRuntimeError(DMA_SID_CHANNELSTART);
    }
#else
    MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
}

#if (DMA_CFG_CHANNEL_CANCEL_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ChannelCancel
*
*   Service ID              : 0x03
*
*   Description             : Stop data transfer for a DMA channel by software.
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*                             CancelMethod: Cancel channel method.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : None.
*
*   Preconditions           : Dma driver must have been initialized before.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelCancel
(
    Dma_ChannelType Channel,
    Dma_ChCancelType CancelMethod
)
{
#if ((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_CFG_DAISYCHAIN_EN == STD_ON))
    Std_ReturnType              Err;
#endif /* \((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_CFG_DAISYCHAIN_EN == STD_ON)) */
    boolean                     SafetyErr;
    uint8                       CoreChIdx;
    Mcal_CoreType               CoreId;

    SafetyErr = TRUE;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_CHANNELCANCEL);
    if (E_OK == Err)
    {
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_CHANNELCANCEL, Channel);
        if (E_OK == Err)
        {
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292)
            if ((DMA_CH_CANCEL_DIRECT != CancelMethod) && (DMA_CH_CANCEL_SAFE != CancelMethod))
#else /* \(MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) */
            if (DMA_CH_CANCEL_DIRECT != CancelMethod)
#endif /* \(MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292) */
            {
                Err = E_NOT_OK;
                /* The channel cancellation method is not supported */
                Dma_ReportError(DMA_SID_CHANNELCANCEL, DMA_E_CANCEL_METHOD);
            }
        }
    }
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* #Violation: Dma_c_REF_1 */
        CoreId = Mcal_GetCoreId();
        /* Get the channel index in the current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;

        DMA_ENTER_CRITICAL_SECTION(ChannelCancel);

        if (DMA_CH_NONE != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx])
        {
            /* Channel is not in IDLE status */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
            Err = Dma_DaisyChainErrCheck(Channel);
            if (E_OK == Err)
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
            {
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
                if (DMA_INVALID_IDX != Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcIdx)
                {
                    SafetyErr = Dma_CancelDaisyChainMembers(Channel, CancelMethod, CoreId);
                }
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
                /* Cancel the channel */
                SafetyErr &= Dma_ChannelCancelPrepare(Channel, CancelMethod, FALSE);
            }
            DMA_EXIT_CRITICAL_SECTION(ChannelCancel);

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if (DMA_DEV_ERROR_DETECT == STD_ON)
            if (E_NOT_OK == Err)
            {
                /* The channel is not the first member in daisy chain */
                Dma_ReportError(DMA_SID_CHANNELCANCEL, DMA_E_CHANNEL_DAISYCHAIN);
            }
#endif /* DMA_DEV_ERROR_DETECT == STD_ON */
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
        }
        else
        {
            DMA_EXIT_CRITICAL_SECTION(ChannelCancel);
#if (DMA_DEV_ERROR_DETECT == STD_ON)
            /* Cancel is not allowed when channel is IDLE */
            Dma_ReportError(DMA_SID_CHANNELCANCEL, DMA_E_CHANNEL_IDLE);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        }
    }

#if (DMA_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dma_ReportRuntimeError(DMA_SID_CHANNELCANCEL);
    }
#else
    MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
}
#endif /* \(DMA_CFG_CHANNEL_CANCEL_API == STD_ON) */

#if (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ChannelSuspend
*
*   Service ID              : 0x04
*
*   Description             : Suspend a transferring channel
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : None.
*
*   Preconditions           : Dma driver must have been initialized before and the channel must in
*                             transferring status.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelSuspend
(
    Dma_ChannelType Channel
)
{
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292)
#if ((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_CFG_DAISYCHAIN_EN == STD_ON))
    Std_ReturnType              Err;
#endif /* \((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_CFG_DAISYCHAIN_EN == STD_ON)) */
    boolean                     SafetyErr;
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    uint8                       DcCnt;
    uint8                       DcIdx;
    Dma_ChannelType             DcChannel;
    const Dma_DaisyChainMapType *DcPtr;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    uint8                       CoreChIdx;
    Mcal_CoreType               CoreId;

    SafetyErr = TRUE;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_CHANNELSUSPEND);
    if (E_OK == Err)
    {
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_CHANNELSUSPEND, Channel);
    }
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get the channel index in the current core */
        /* #Violation: Dma_c_REF_1 */
        CoreId = Mcal_GetCoreId();

        /* Get the channel index in the current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;

        DMA_ENTER_CRITICAL_SECTION(ChannelSuspend);

        if (DMA_CH_TRANSFERRING == Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx])
        {
            /* The channel is in transferring status */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
            Err = Dma_DaisyChainErrCheck(Channel);
            if (E_OK == Err)
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
            {
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
                DcIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcIdx;
                if (DMA_INVALID_IDX != Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcIdx)
                {
                    /* Change the daisy chain status to suspended */
                    Dma_StatusDataSetPtr[CoreId]->DcStatusPtr[DcIdx] = DMA_DAISYCHAIN_SUSPENEDED;
                    /* Load daisy chain configuration parameters */
                    DcPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->DaisyChainListPtr[DcIdx];
                    /* Loop all channel in daisy chain */
                    for (DcCnt = 1U; ((DcCnt < DcPtr->DcMaxNum) && (TRUE == SafetyErr)); DcCnt++)
                    {
                        /* Get the channel that daisy chain member assigned */
                        DcChannel = DcPtr->DcToChannelPtr[DcCnt];
                        SafetyErr &= Dma_ChannelSuspendPrepare(DcChannel);
                    }
                }
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
                /* Suspend the channel */
                SafetyErr &= Dma_ChannelSuspendPrepare(Channel);
            }
            DMA_EXIT_CRITICAL_SECTION(ChannelSuspend);

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if (DMA_DEV_ERROR_DETECT == STD_ON)
            if (E_NOT_OK == Err)
            {
                /* The channel is not the first member in daisy chain */
                Dma_ReportError(DMA_SID_CHANNELSUSPEND, DMA_E_CHANNEL_DAISYCHAIN);
            }
#endif /* DMA_DEV_ERROR_DETECT == STD_ON */
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
        }
        else
        {
            DMA_EXIT_CRITICAL_SECTION(ChannelSuspend);
#if (DMA_DEV_ERROR_DETECT == STD_ON)
            /* Report DET when the channel is not in transferring status */
            Dma_ReportError(DMA_SID_CHANNELSUSPEND, DMA_E_CHANNEL_IDLE);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        }
    }

#if (DMA_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dma_ReportRuntimeError(DMA_SID_CHANNELSUSPEND);
    }
#else
    MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
#else /* \(MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) */
    (void)Channel;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Report DET when suspending the channel is not supported on the THA6206 platform */
    Dma_ReportError(DMA_SID_CHANNELSUSPEND, DMA_E_FEATURE_NOT_SUPPORTED);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
#endif /* \(MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292) */
}

/****************************************************************************************************
*   Function Name           : Dma_ChannelResume
*
*   Service ID              : 0x05
*
*   Description             : Resume a suspended channel
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : None.
*
*   Preconditions           : Dma driver must have been initialized before and the channel must in
*                             suspended status.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelResume
(
    Dma_ChannelType Channel
)
{
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292)
#if ((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_CFG_DAISYCHAIN_EN == STD_ON))
    Std_ReturnType              Err;
#endif /* \((DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_CFG_DAISYCHAIN_EN == STD_ON)) */
    boolean                     SafetyErr;
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    uint8                       DcCnt;
    uint8                       DcIdx;
    Dma_ChannelType             DcChannel;
    const Dma_DaisyChainMapType *DcPtr;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    uint8                       CoreChIdx;
    Mcal_CoreType               CoreId;

    SafetyErr = TRUE;

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_CHANNELRESUME);
    if (E_OK == Err)
    {
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_CHANNELRESUME, Channel);
    }
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get the channel index in the current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;

        DMA_ENTER_CRITICAL_SECTION(ChannelResume);

        if (DMA_CH_SUSPENDED == Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx])
        {
            /* Channel is in suspended status */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
            Err = Dma_DaisyChainErrCheck(Channel);
            if (E_OK == Err)
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
            {
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
                DcIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcIdx;
                if (DMA_INVALID_IDX != Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcIdx)
                {
                    /* Change the daisy chain status to transferring */
                    Dma_StatusDataSetPtr[CoreId]->DcStatusPtr[DcIdx] = DMA_DAISYCHAIN_TRANSFERRING;
                    /* Load daisy chain configuration parameters */
                    DcPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->DaisyChainListPtr[DcIdx];
                    /* Loop all channel in daisy chain */
                    for (DcCnt = 1U; ((DcCnt < DcPtr->DcMaxNum) && (TRUE == SafetyErr)); DcCnt++)
                    {
                        /* Get the channel that daisy chain member assigned */
                        DcChannel = DcPtr->DcToChannelPtr[DcCnt];
                        SafetyErr &= Dma_ChannelResumePrepare(DcChannel);
                    }
                }
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
                /* Resume the channel */
                SafetyErr &= Dma_ChannelResumePrepare(Channel);
            }
            DMA_EXIT_CRITICAL_SECTION(ChannelResume);

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if (DMA_DEV_ERROR_DETECT == STD_ON)
            if (E_NOT_OK == Err)
            {
                /* The channel is not the first member in daisy chain */
                Dma_ReportError(DMA_SID_CHANNELRESUME, DMA_E_CHANNEL_DAISYCHAIN);
            }
#endif /* DMA_DEV_ERROR_DETECT == STD_ON */
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
        }
        else
        {
            DMA_EXIT_CRITICAL_SECTION(ChannelResume);
#if (DMA_DEV_ERROR_DETECT == STD_ON)
            /* Not in suspend mode */
            Dma_ReportError(DMA_SID_CHANNELRESUME, DMA_E_CHANNEL_NOT_SUSPEND);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        }
    }

#if (DMA_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dma_ReportRuntimeError(DMA_SID_CHANNELRESUME);
    }
#else
    MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
#else /* \(MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) */
    (void)Channel;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Report DET when resuming the channel is not supported on the THA6206 platform */
    Dma_ReportError(DMA_SID_CHANNELRESUME, DMA_E_FEATURE_NOT_SUPPORTED);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
#endif /* \(MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA6206_LFBGA292) */
}
#endif /* \(DMA_CFG_CHANNEL_PAUSE_API == STD_ON) */

#if (DMA_CFG_TRANSFER_UPDATE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ChannelUpdate
*
*   Service ID              : 0x06
*
*   Description             : Switch a transfer configuration for a DMA channel
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*                             TransferId: Logical transfer ID of the channel, Must multiple set of
*                             transfer configuration in this channel
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : None.
*
*   Preconditions           : Dma driver must have been initialized before and the channel must
*                             in IDLE status.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelUpdate
(
    Dma_ChannelType Channel,
    Dma_TransferType TransferId
)
{
    boolean                SafetyErr;
    Dma_HwUnitType         PhyHwUnitId;
    uint8                  PhyChannelId;
    uint8                  CoreChIdx;
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
    Dma_DoubleBufferType   DblBufId;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
    Dma_CircularBufferType CircBufId;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
    Dma_PatternType        PatternId;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType         Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
    Dma_TransferType       CoreTransferIdx;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
    Mcal_CoreType          CoreId;
    const Dma_ChConfigType *ChConfigPtr;

    SafetyErr = TRUE;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_CHANNELUPDATE);
    if (E_OK == Err)
    {
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_CHANNELUPDATE, Channel);
    }
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* #Violation: Dma_c_REF_1 */
        CoreId = Mcal_GetCoreId();
        /* Get the channel index in the current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
        /* Get channel configuration */
        ChConfigPtr = &Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx];
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
        /* Get transfer ID flag */
        CoreTransferIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].ChTransferIdx;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */

#if (DMA_DEV_ERROR_DETECT == STD_ON)
        if (TransferId >= ChConfigPtr->ChTransferTotalNum)
        {
            /* Parameter "TransferId" is out of range */
            Dma_ReportError(DMA_SID_CHANNELUPDATE, DMA_E_PARAM_WRONG_ID);
            Err = E_NOT_OK;
        }
        else
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
        if (DMA_INVALID_IDX == CoreTransferIdx)
        {
            /* Multiple configuration is unsupported for current channel */
            Dma_ReportError(DMA_SID_CHANNELUPDATE, DMA_E_CHANNEL_MULTI_CONFIG);
            Err = E_NOT_OK;
        }
        else if (TransferId == Dma_StatusDataSetPtr[CoreId]->ChCurrTransferPtr[CoreTransferIdx])
        {
            /* Switch transfer is equal to current transfer */
            Dma_ReportError(DMA_SID_CHANNELUPDATE, DMA_E_UPDATE_SAME_ID);
            Err = E_NOT_OK;
        }
        else
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
        /* #Violation: Dma_c_REF_9 */
        {
            /* Do Nothing */
        }
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    }

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        DMA_ENTER_CRITICAL_SECTION(ChannelUpdate);

        if ((DMA_CH_TRANSFERRING != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]) &&
                 (DMA_CH_SUSPENDED != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]))
        {
            /* The channel is not in transferring or suspended status */

            /* Get the HW unit from Channel */
            PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
            /* Get the physical channel ID from Channel */
            PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
            /* Update the channel configuration */
            SafetyErr &= Dma_Hal_InitChannelTransfer(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                     &ChConfigPtr->ChTransferConfigPtr[TransferId].ChTransferConfig);

#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
            CoreTransferIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].ChTransferIdx;
            /* Record the configuration ID */
            Dma_StatusDataSetPtr[CoreId]->ChCurrTransferPtr[CoreTransferIdx] = TransferId;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */

#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
            /* Get the double buffering ID that current transfer assigned */
            DblBufId = ChConfigPtr->ChTransferConfigPtr[TransferId].ChDoubleBufferId;
            /* Check if the double buffering is enabled */
            if (DMA_INVALID_IDX != DblBufId)
            {
                /* Initialize the double buffer */
                SafetyErr &= Dma_Hal_InitDoubleBuffer(Dma_BaseAddrs[PhyHwUnitId],
                                         PhyChannelId,
                             &Dma_ConfigPtr->CommConfigPtr->DblBufConfigPtr[DblBufId].DblBufConfig);
            }
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */

#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
            /* Get the circular buffering ID that current transfer assigned */
            CircBufId = ChConfigPtr->ChTransferConfigPtr[TransferId].ChCircularBufferId;
            /* Check if the circular buffering is enabled */
            if (DMA_INVALID_IDX != CircBufId)
            {
                /* Initialize the circular buffer configuration */
                /* Index 0 of configuration parameter is default to be used */
                SafetyErr &= Dma_Hal_InitCircularBuffer(Dma_BaseAddrs[PhyHwUnitId],
                                           PhyChannelId,
                                         &Dma_ConfigPtr->CommConfigPtr->CircBufConfigPtr[CircBufId]);
            }
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */

#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
            /* Get the pattern ID that current transfer assigned */
            PatternId = ChConfigPtr->ChTransferConfigPtr[TransferId].ChPatternId;
            /* Check if the pattern is enabled */
            if (DMA_INVALID_IDX != PatternId)
            {
                /* Initialize the pattern match configuration of channel */
                /* Index 0 of configuration parameter is default to be used */
                SafetyErr &= Dma_Hal_InitMatchPattern(Dma_BaseAddrs[PhyHwUnitId],
                                         PhyChannelId,
                                         &Dma_ConfigPtr->CommConfigPtr->PatternConfigPtr[PatternId]);
            }
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
                /* Clear the manual channel transfer pointer; the currently switched 
                    configuration will be used for data transfer. */
                Dma_StatusDataSetPtr[CoreId]->ChTransManualPtr[CoreChIdx] = NULL_PTR;
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

            DMA_EXIT_CRITICAL_SECTION(ChannelUpdate);
        }
        else
        {
            DMA_EXIT_CRITICAL_SECTION(ChannelUpdate);

#if ((DMA_DEV_ERROR_DETECT == STD_ON))
            /* Channel can update only when channel is in none status or completed status */
            Dma_ReportError(DMA_SID_CHANNELUPDATE, DMA_E_CHANNEL_TRANSFERING);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        }
    }

#if (DMA_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dma_ReportRuntimeError(DMA_SID_CHANNELUPDATE);
    }
#else
    MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
}
#endif /* \(DMA_CFG_TRANSFER_UPDATE_API == STD_ON) */

#if (DMA_CFG_SHADOWING_UPDATE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ChannelShadowingUpdate
*
*   Service ID              : 0x07
*
*   Description             : Switch the shadow operation configuration for a Dma channel
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*                             ShadowingId: Logical shadowing operation ID of the channel, Must
*                             multiple set of shadowing configuration in this channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : None.
*
*   Preconditions           : Dma driver must have been initialized before.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelShadowingUpdate
(
    Dma_ChannelType Channel,
    Dma_ShadowingType ShadowingId
)
{
    boolean                         SafetyErr;
    uint8                           CoreChIdx;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType                  Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
    Dma_ShadowingType               CoreShadowId;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
    const Dma_ChConfigType          *ChConfigPtr;
    Mcal_CoreType                   CoreId;

    SafetyErr = TRUE;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_CHANNELSHADOWUPDATE);
    if (E_OK == Err)
    {
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_CHANNELSHADOWUPDATE, Channel);
    }

    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get the channel index in the current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
        /* #Violation: Dma_c_REF_1 */
        CoreId = Mcal_GetCoreId();
        ChConfigPtr =
                &Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx];
#if (DMA_DEV_ERROR_DETECT == STD_ON)
        if (NULL_PTR == ChConfigPtr->ChShadowMapInfoPtr)
        {
            /* Specified channel is not a shadowing configuration */
            Dma_ReportError(DMA_SID_CHANNELSHADOWUPDATE, DMA_E_SHADOWING);
            Err = E_NOT_OK;
        }
        else if (ShadowingId >= ChConfigPtr->ChShadowTotalNum)
        {
            /* Parameter "ShadowingId" is out of range */
            Dma_ReportError(DMA_SID_CHANNELSHADOWUPDATE, DMA_E_PARAM_WRONG_ID);
            Err = E_NOT_OK;
        }
        else
        {
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
            /* Get the index position  */
            CoreShadowId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].ChShadowingIdx;
            if (DMA_INVALID_IDX == (uint8)CoreShadowId)
            {
                /* Parameter "ShadowingId" is out of range */
                Dma_ReportError(DMA_SID_CHANNELSHADOWUPDATE, DMA_E_CHANNEL_MULTI_CONFIG);
                Err = E_NOT_OK;
            }
            else if (Dma_StatusDataSetPtr[CoreId]->ChCurrShadowingPtr[CoreShadowId] == ShadowingId)
            {
                /* Switch shadowing is equal to current shadowing */
                Dma_ReportError(DMA_SID_CHANNELSHADOWUPDATE, DMA_E_UPDATE_SAME_ID);
                Err = E_NOT_OK;
            }
            else
            /* #Violation: Dma_c_REF_9 */
            {
                /* Do Nothing */
            }
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */
        }

        if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        {
#if (DMA_CFG_MULTI_SHADOWING_NUM != 0U)
            /* Get the index position  */
            CoreShadowId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].ChShadowingIdx;
            /* Record the configuration set */
            Dma_StatusDataSetPtr[CoreId]->ChCurrShadowingPtr[CoreShadowId] =
                                                                (Dma_ShadowingType)ShadowingId;
#endif /* \(DMA_CFG_MULTI_SHADOWING_NUM != 0U) */

            DMA_ENTER_CRITICAL_SECTION(ChannelShadowingUpdate);
            
            if ((DMA_CH_TRANSFERRING == Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]) ||
                     (DMA_CH_SUSPENDED == Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]))
            {
                /* Update the shadowing configuration */
                SafetyErr = Dma_ShadowingConfigChange(Channel, ShadowingId, ChConfigPtr);
            }

            DMA_EXIT_CRITICAL_SECTION(ChannelShadowingUpdate);
        }
    }

#if (DMA_SAFETY_ENABLE == STD_ON)
    if (FALSE == SafetyErr)
    {
        /* Report the safety check error */
        Dma_ReportRuntimeError(DMA_SID_CHANNELSHADOWUPDATE);
    }
#else
    MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
}
#endif /* \(DMA_CFG_SHADOWING_UPDATE_API == STD_ON) */

#if (DMA_CFG_DOUBLE_BUFFER_SWITCH_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ChannelDoubleBufferSwitch
*
*   Service ID              : 0x08
*
*   Description             : In double buffer mode, software switch the buffer to the other buffer
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : None.
*
*   Preconditions           : Dma driver must have been initialized before.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelDoubleBufferSwitch
(
    Dma_ChannelType Channel
)
{
    Dma_HwUnitType   PhyHwUnitId;
    uint8            PhyChannelId;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Dma_TransferType CurrTransferId;
    uint8            CoreChIdx;
    Std_ReturnType   Err;
    Mcal_CoreType    CoreId;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_CHANNELDOUBLEBUFFERSWITCH);
    if (E_OK == Err)
    {
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_CHANNELDOUBLEBUFFERSWITCH, Channel);
    }
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
#if (DMA_DEV_ERROR_DETECT == STD_ON)
        /* Get the channel index in the current core */
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
        CoreId = Mcal_GetCoreId();
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
        CurrTransferId = Dma_GetTransferId(Channel);
#else
        CurrTransferId = 0U;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */

        if (NULL_PTR == Dma_ConfigPtr->CoreConfigPtr[CoreId]->
                ChannelConfigPtr[CoreChIdx].ChTransferConfigPtr)
        {
            /* No transfer configuration for this channel */
            Dma_ReportError(DMA_SID_CHANNELDOUBLEBUFFERSWITCH, DMA_E_CHANNEL_NO_TRANS_CONFIG);
        }
        else if (DMA_INVALID_IDX == Dma_ConfigPtr->CoreConfigPtr[CoreId]->
            ChannelConfigPtr[CoreChIdx].ChTransferConfigPtr[CurrTransferId].ChDoubleBufferId)
        {
            /* Specified transfer of channel is without a double buffer */
            Dma_ReportError(DMA_SID_CHANNELDOUBLEBUFFERSWITCH, DMA_E_DOUBLE_BUFFER);
        }
        else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        {
            /* Get the HW unit from Channel */
            PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
            /* Get the physical channel ID from Channel */
            PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
            /* Cancel the channel */
            Dma_Hal_SoftwareSwitchDoubleBuffer(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
        }
    }
}

#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */

#if (DMA_CFG_CHANNEL_REMAINING_TRANSFER_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_GetChannelRemainTransfer
*
*   Service ID              : 0x09
*
*   Description             : Get the remaining amount of data to be transferred.
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : uint16: Remaining transfer count.
*
*   Preconditions           : Dma driver must have been initialized before.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(uint16, DMA_PUBLIC_CODE) Dma_GetChannelRemainTransfer
(
    Dma_ChannelType Channel
)
{
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType      Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    Dma_HwUnitType      PhyHwUnitId;
    uint8               PhyChannelId;
    uint16              RemTransfNum;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_GETCHANNELREMAINTRANSFER);
    if (E_OK == Err)
    {
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_GETCHANNELREMAINTRANSFER, Channel);
    }
    if (E_NOT_OK == Err)
    {
        RemTransfNum = 0U;
    }
    else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Get the HW unit from Channel */
        PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
        /* Get the physical channel ID from Channel */
        PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;
        /* Get remaining count from register */
        RemTransfNum = Dma_Hal_GetRemainderTransferNum(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId);
    }

    return RemTransfNum;
}
#endif /* \(DMA_CFG_CHANNEL_REMAINING_TRANSFER_API == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dma_GetChannelStatus
*
*   Service ID              : 0x10
*
*   Description             : Get the event status.
*
*   Parameters in           : Channel: Logical Channel ID and generated by EB tresos tool.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : uint32: Channel transfer event status.
*                               Each bit represents the status of an event.
*                               Refer to "Dma_ChStatusType" for detail event status description.
*
*   Preconditions           : Dma driver must have been initialized before.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(uint32, DMA_PUBLIC_CODE) Dma_GetChannelStatus
(
    Dma_ChannelType Channel
)
{
    boolean                      SafetyErr;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType               Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    uint32                       ChStatus;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    ChStatus = (uint32)DMA_CH_ERROR;
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_GETCHANNELSTATUS);
    if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
#if (DMA_DEV_ERROR_DETECT == STD_ON)
        /* Common DET checking */
        Err = Dma_ChCommCheck(DMA_SID_GETCHANNELSTATUS, Channel);
        if (E_OK == Err)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        {
            SafetyErr = Dma_GetChannelEvent(Channel, &ChStatus);
#if (DMA_SAFETY_ENABLE == STD_ON)
            if (FALSE == SafetyErr)
            {
                /* Report the safety check error */
                Dma_ReportRuntimeError(DMA_SID_GETCHANNELSTATUS);
            }
#else
            MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
        }
    }

    return ChStatus;
}

#if (DMA_CFG_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_GetVersionInfo
*
*   Service ID              : 0x11
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
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_GetVersionInfo
(
    /* #Violation: Dma_c_REF_5 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, DMA_APPL_DATA) VersionInfoPtr
)
{
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == VersionInfoPtr)
    {
        Dma_ReportError(DMA_SID_GETVERSIONINFO, DMA_E_PARAM_POINTER);
    }
    else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        VersionInfoPtr->vendorID         = (uint16)DMA_VENDOR_ID;
        VersionInfoPtr->moduleID         = (uint16)DMA_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)DMA_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)DMA_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)DMA_SW_PATCH_VERSION;
    }
}
#endif /* \(DMA_CFG_VERSION_INFO_API == STD_ON) */

/****************************************************************************************************
*   Function Name           : Dma_LliMemberInsertManual
*
*   Service ID              : 0x12
*
*   Description             : Insert a linked list member configuration into a linked list
*                             buffer.
*
*   Parameters in           : Channel: Logical channel ID
*                             LliCfgPtr: Pointer to the linked list member configuration parameters
*
*   Parameters inout        : LliBufPtr: Pointer to the linked list buffer and used to save the
*                               linked list member configuration information
*
*   Parameters out          : None
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : E_OK: Insert linked list member success.
*                             E_NOT_OK: Insert linked list member failed.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(Std_ReturnType, DMA_PUBLIC_CODE) Dma_LliMemberInsertManual
(
    Dma_ChannelType Channel,
    /* #Violation: Dma_c_REF_5 */
    CONSTP2VAR(Dma_LliBufType, AUTOMATIC, DMA_APPL_DATA) LliBufPtr,
    CONSTP2CONST(Dma_LliCfgType, AUTOMATIC, DMA_APPL_DATA) LliCfgPtr
)
{
    Dma_HwUnitType PhyHwUnitId;
    uint8          PhyChannelId;
    Std_ReturnType RetErr;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    uint8          CoreChIdx;
    Mcal_CoreType  CoreId;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    RetErr = Dma_CheckInit(DMA_SID_LLIMEMBERINSERTMANUAL);
    if (E_OK == RetErr)
    {
        /* Common DET checking */
        RetErr = Dma_ChCommCheck(DMA_SID_LLIMEMBERINSERTMANUAL, Channel);
        if (E_OK == RetErr)
        {
            if ((NULL_PTR == LliBufPtr) || (NULL_PTR == LliCfgPtr))
            {
                Dma_ReportError(DMA_SID_LLIMEMBERINSERTMANUAL, DMA_E_PARAM_POINTER);
                RetErr = E_NOT_OK;
            }
        }
    }

    if (E_OK == RetErr)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
#if (DMA_DEV_ERROR_DETECT == STD_ON)
        /* #Violation: Dma_c_REF_1 */
        CoreId = Mcal_GetCoreId();
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
        if ((DMA_CH_NONE != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]) &&
            (DMA_CH_TRANSFER_COMPLETE != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]))
        {
            Dma_ReportError(DMA_SID_LLIMEMBERINSERTMANUAL, DMA_E_CHANNEL_TRANSFERING);
            RetErr = E_NOT_OK;
        }
        else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        {
            RetErr = E_OK;

            /* Get the HW unit from Channel */
            PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
            /* Get the physical channel ID from Channel */
            PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;

            /* Write the linked list configuration information into linked list array */
            Dma_Hal_WriteLinkedListItem(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                        LliBufPtr,
                                        LliCfgPtr);
        }
    }

    return RetErr;
}

/****************************************************************************************************
*   Function Name           : Dma_LliInsertCompleteManual
*
*   Service ID              : 0x13
*
*   Description             : When all linked list member configuration parameters are completed
*                             and insert to the linked list buffers, call this function to initialize
*                             the linked list and prepare to first linked list member.
*                             Then call Dma_ChannelStart() to start the DMA channel.
*
*   Parameters in           : Channel: Logical channel ID
*                             LliBufHeadAddrPtr: Pointer to the head address of the linked list
*                               buffer.
*
*   Parameters inout        : None.
*
*   Parameters out          : None
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : E_OK: Insert operation is completed.
*                             E_NOT_OK: Insert operation can not be completed.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(Std_ReturnType, DMA_PUBLIC_CODE) Dma_LliInsertCompleteManual
(
    Dma_ChannelType Channel,
    CONSTP2CONST(Dma_LliBufType, AUTOMATIC, DMA_APPL_DATA) LliBufHeadAddrPtr
)
{
    boolean        SafetyErr;
    Dma_HwUnitType PhyHwUnitId;
    uint8          PhyChannelId;
    Std_ReturnType RetErr;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    uint8          CoreChIdx;
    Mcal_CoreType  CoreId;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    RetErr = Dma_CheckInit(DMA_SID_LLIINSERTCOMPLETEMANUAL);
    if (E_OK == RetErr)
    {
        /* Common DET checking */
        RetErr = Dma_ChCommCheck(DMA_SID_LLIINSERTCOMPLETEMANUAL, Channel);
        if (E_OK == RetErr)
        {
            if (NULL_PTR == LliBufHeadAddrPtr)
            {
                Dma_ReportError(DMA_SID_LLIINSERTCOMPLETEMANUAL, DMA_E_PARAM_POINTER);
                RetErr = E_NOT_OK;
            }
        }
    }

    if (E_OK == RetErr)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
#if (DMA_DEV_ERROR_DETECT == STD_ON)
        /* #Violation: Dma_c_REF_1 */
        CoreId = Mcal_GetCoreId();
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
        if ((DMA_CH_NONE != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]) &&
            (DMA_CH_TRANSFER_COMPLETE != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]))
        {
            Dma_ReportError(DMA_SID_LLIINSERTCOMPLETEMANUAL, DMA_E_CHANNEL_TRANSFERING);
            RetErr = E_NOT_OK;
        }
        else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        {
            RetErr = E_OK;
            /* Get the HW unit from Channel */
            PhyHwUnitId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].HwUnitId;
            /* Get the physical channel ID from Channel */
            PhyChannelId = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].PhyChannelId;

            /* Initialize the linked list channel configuration */
            SafetyErr = Dma_Hal_InitLinkedListItem(Dma_BaseAddrs[PhyHwUnitId], PhyChannelId,
                                                   LliBufHeadAddrPtr);

#if (DMA_SAFETY_ENABLE == STD_ON)
            if (FALSE == SafetyErr)
            {
                /* Report the safety check error */
                Dma_ReportRuntimeError(DMA_SID_LLIINSERTCOMPLETEMANUAL);
            }
#else
            MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
        }
    }

    return RetErr;
}

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_ChannelUpdateManual
*
*   Service ID              : 0x14
*
*   Description             : Update the channel transfer configuration parameters manually.
*
*   Parameters in           : Channel: Logical channel ID
*                             ChannelTransferPtr: Pointer to the channel transfer configuration 
*                               parameters
*
*   Parameters inout        : None.
*
*   Parameters out          : None
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : This API is re-entrant for different channels.
*
*   Return value            : E_OK: Insert operation is completed.
*                             E_NOT_OK: Insert operation can not be completed.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Dma_c_REF_7 */
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelUpdateManual
(
    Dma_ChannelType Channel,
    CONSTP2VAR(Dma_ChannelTransferType, AUTOMATIC, DMA_APPL_DATA) ChannelTransferPtr
)
{
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetErr;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    uint8          CoreChIdx;
    Mcal_CoreType  CoreId;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    RetErr = Dma_CheckInit(DMA_SID_CHANNELUPDATEMANUAL);
    if (E_OK == RetErr)
    {
        /* Common DET checking */
        RetErr = Dma_ChCommCheck(DMA_SID_CHANNELUPDATEMANUAL, Channel);
        if (E_OK == RetErr)
        {
            if (NULL_PTR == ChannelTransferPtr)
            {
                /* ChannelTransferPtr is NULL pointer */
                Dma_ReportError(DMA_SID_CHANNELUPDATEMANUAL, DMA_E_PARAM_POINTER);
                RetErr = E_NOT_OK;
            }
            else if (ChannelTransferPtr->TransferSize > DMA_MAX_TRANSFER_SIZE)
            {
                /* Transfer size out of range */
                Dma_ReportError(DMA_SID_CHANNELUPDATEMANUAL, DMA_E_TRANSFER_SIZE_OUT_OF_RANGE);
                RetErr = E_NOT_OK;
            }
            else
            {
                /* Do Nothing */
            }
        }
    }

    if (E_OK == RetErr)
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* #Violation: Dma_c_REF_1 */
        CoreId = Mcal_GetCoreId();
        CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;

        DMA_ENTER_CRITICAL_SECTION(ChannelUpdate);

        if ((DMA_CH_TRANSFERRING != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]) &&
                 (DMA_CH_SUSPENDED != Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx]))
        {
            /* Pointer to the channel transfer configuration from ChannelTransferPtr */
            Dma_StatusDataSetPtr[CoreId]->ChTransManualPtr[CoreChIdx] = ChannelTransferPtr;

            DMA_EXIT_CRITICAL_SECTION(ChannelUpdate);
        }
        else
        {
            DMA_EXIT_CRITICAL_SECTION(ChannelUpdate);
            
#if ((DMA_DEV_ERROR_DETECT == STD_ON))
            /* Channel can update only when channel is in none status or completed status */
            Dma_ReportError(DMA_SID_CHANNELUPDATEMANUAL, DMA_E_CHANNEL_TRANSFERING);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        }
    }
}
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

/****************************************************************************************************
**                          Interrupt Service Function Definitions                                 **
****************************************************************************************************/

#if (DMA_CFG_INTERRUPT_EN == STD_ON)
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_TerminalCount_ISRHandler
*
*   Service ID              : 0xE0.
*
*   Description             : Terminal count interrupt, Transfer completed interrupt handler.
*
*   Parameters in           : HwUnitId: HW unit ID of DMA.
*                             ChannelId: Channel ID of DMA.
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
*   Preconditions           : 1. Dma driver must have been initialized before.
*                             2. Terminal interrupt must enabled by Tresos
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DMA_PUBLIC_CODE) Dma_TerminalCount_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
)
{
    Dma_ChannelType              Channel;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType               Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    uint8                        IntStatus;
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    boolean                      SafetyErr;
    Dma_ChannelType              DcFirstCh;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    uint8                        CoreChIdx;
    Mcal_CoreType                CoreId;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_TERMINALCOUNT_ISR);
    if (E_OK == Err)
    {
        /* Get the logical channel via HW unit and physical channel */
        Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];
        if (DMA_INVALID_CHANNEL == Channel)
        {
            /* Calculated channel id is invalid */
            Dma_ReportError(DMA_SID_TERMINALCOUNT_ISR, DMA_E_PARAM_CHANNEL);
            Err = E_NOT_OK;
        }
        else
        {
            Err = Dma_ChCommCheck(DMA_SID_TERMINALCOUNT_ISR, Channel);
        }
    }

    if (E_NOT_OK == Err)
    {
        /* Transfer completed interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_TC);
        if (0U != IntStatus)
        {
            /* Clear the interrupt status first */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                         (uint8)DMA_CH_INT_TC);
        }
    }
    else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Transfer completed interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_TC);
        if (0U != IntStatus)
        {
            /* Clear the interrupt status first */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                         (uint8)DMA_CH_INT_TC);

            /* Get the logical channel via HW unit and physical channel */
            Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
            /* Get the first logical channel ID in daisy chain */
            DcFirstCh = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreDcFirstCh;
            if (DcFirstCh != DMA_INVALID_IDX)
            {
                SafetyErr = Dma_RefreshDaisyChainStatus(DcFirstCh);

#if (DMA_SAFETY_ENABLE == STD_ON)
                if (FALSE == SafetyErr)
                {
                    /* Report the safety check error */
                    Dma_ReportRuntimeError(DMA_SID_TERMINALCOUNT_ISR);
                }
#else
                MCAL_UNUSED_VAR(SafetyErr);
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */
            }
            else
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
            {
                /* Update the status machine */
                (void)Dma_TerminalCountRefreshStatus(HwUnitId, PhyChannelId, Channel);
            }

            /* #Violation: Dma_c_REF_1 */
            CoreId = Mcal_GetCoreId();
            /* Get the sub index in core */
            CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
            if (NULL_PTR != Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                    DmaChannelNotificationPtr)
            {
                /* Call notification function */
                Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                                                 DmaChannelNotificationPtr(Channel, DMA_CH_INT_TC);
            }
        }
    }
}
#endif /* \(DMA_CFG_TC_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_RemainingCount_ISRHandler
*
*   Service ID              : 0xE1.
*
*   Description             : Remaining count threshold interrupt handler.
*
*   Parameters in           : HwUnitId: HW unit ID of DMA.
*                             ChannelId: Channel ID of DMA.
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
*   Preconditions           : 1. Dma driver must have been initialized before.
*                             2. Terminal interrupt must enabled by Tresos
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DMA_PUBLIC_CODE) Dma_RemainingCount_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
)
{
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType  Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    uint8           IntStatus;
    Mcal_CoreType   CoreId;
    uint8           CoreChIdx;
    Dma_ChannelType Channel;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_REMAININGCOUNT_ISR);
    if (E_OK == Err)
    {
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

        /* Get the logical channel via HW unit and physical channel */
        Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];

#if ( (DMA_DEV_ERROR_DETECT == STD_ON))
        if (DMA_INVALID_CHANNEL == Channel)
        {
            /* Calculated channel id is invalid */
            Dma_ReportError(DMA_SID_REMAININGCOUNT_ISR, DMA_E_PARAM_CHANNEL);
            Err = E_NOT_OK;
        }
        else
        {
            Err = Dma_ChCommCheck(DMA_SID_REMAININGCOUNT_ISR, Channel);
        }
    }

    if (E_NOT_OK == Err)
    {
        /* Transfer completed interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_REMAINING_COUNT);
        if (0U != IntStatus)
        {
            /* Clear the interrupt status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                         (uint8)DMA_CH_INT_REMAINING_COUNT);
        }
    }
    else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Transfer completed interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_REMAINING_COUNT);
        if (0U != IntStatus)
        {
            /* Clear the interrupt status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                         (uint8)DMA_CH_INT_REMAINING_COUNT);

            CoreId = Mcal_GetCoreId();
            CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
            /* Call notification function */
            if (NULL_PTR != Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                    DmaChannelNotificationPtr)
            {
                Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                                 DmaChannelNotificationPtr(Channel, DMA_CH_INT_REMAINING_COUNT);
            }
        }
    }
}
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_Error_ISRHandler
*
*   Service ID              : 0xE2.
*
*   Description             : Error interrupt handler.
*
*   Parameters in           : HwUnitId: HW unit ID of DMA.
*                             ChannelId: Physical channel ID of DMA.
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
*   Preconditions           : 1. Dma driver must have been initialized before.
*                             2. Terminal interrupt must enabled by Tresos
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DMA_PUBLIC_CODE) Dma_Error_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
)
{
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType  Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    Dma_ChannelType Channel;
    uint8           CoreChIdx;
    uint8           IntStatus;
    Mcal_CoreType   CoreId;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_ERROR_ISR);
    if (E_OK == Err)
    {
        /* Get the logical channel via HW unit and physical channel */
        Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];
        if (DMA_INVALID_CHANNEL == Channel)
        {
            /* Calculated channel id is invalid */
            Dma_ReportError(DMA_SID_ERROR_ISR, DMA_E_PARAM_CHANNEL);
            Err = E_NOT_OK;
        }
        else
        {
            Err = Dma_ChCommCheck(DMA_SID_ERROR_ISR, Channel);
        }
    }

    if (E_NOT_OK == Err)
    {
        /* Error interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_ERROR);
        if (0U != IntStatus)
        {
            /* Clear the error status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                         (uint8)DMA_CH_INT_ERROR);
        }
    }
    else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Error interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_ERROR);
        if (0U != IntStatus)
        {
            /* Clear the error status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                         (uint8)DMA_CH_INT_ERROR);

#if (DMA_DEV_ERROR_DETECT == STD_ON)
            /* Bus error occurred while data transferring or linked list item loading */
            Dma_ReportError(DMA_SID_ERROR_ISR, DMA_E_BUSERROR);
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

            /* #Violation: Dma_c_REF_1 */
            CoreId = Mcal_GetCoreId();
            /* Get the logical channel via HW unit and physical channel */
            Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];
            CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
            /* Error occurred then change the channel transfer to none */
            Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_NONE;

            /* Cancel the channel */
            Dma_Hal_DisableChannel(Dma_BaseAddrs[HwUnitId], PhyChannelId);

            if (NULL_PTR != Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                    DmaChannelNotificationPtr)
            {
                /* Call notification function */
                Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                                            DmaChannelNotificationPtr(Channel, DMA_CH_INT_ERROR);
            }
        }
    }
}
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_SrcCircBufRb_ISRHandler
*
*   Service ID              : 0xE3.
*
*   Description             : Source circular buffer rollback interrupt handler.
*
*   Parameters in           : HwUnitId: HW unit ID of DMA.
*                             ChannelId: Channel ID of DMA.
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
*   Preconditions           : 1. Dma driver must have been initialized before.
*                             2. Terminal interrupt must enabled by Tresos
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DMA_PUBLIC_CODE) Dma_SrcCircBufRb_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
)
{
    uint8           IntStatus;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType  Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    Dma_ChannelType Channel;
    uint8           CoreChIdx;
    Mcal_CoreType   CoreId;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_SRCCIRCBUF_ISR);
    if (E_OK == Err)
    {
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        /* Get the logical channel via HW unit and physical channel */
        Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];

#if (DMA_DEV_ERROR_DETECT == STD_ON)
        if (DMA_INVALID_CHANNEL == Channel)
        {
            /* Calculated channel id is invalid */
            Dma_ReportError(DMA_SID_SRCCIRCBUF_ISR, DMA_E_PARAM_CHANNEL);
            Err = E_NOT_OK;
        }
        else
        {
            Err = Dma_ChCommCheck(DMA_SID_SRCCIRCBUF_ISR, Channel);
        }
    }

    if (E_NOT_OK == Err)
    {
        /* Source circular buffer interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_SCB);
        if (0U != IntStatus)
        {
            /* Clear the source circular buffer interrupt status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_SCB);
        }
    }
    else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Source circular buffer interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_SCB);
        if (0U != IntStatus)
        {
            /* Clear the source circular buffer interrupt status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_SCB);

            CoreId = Mcal_GetCoreId();
            /* Get the logical channel via HW unit and physical channel */
            Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];
            CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
            if (NULL_PTR != Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                    DmaChannelNotificationPtr)
            {
                /* Call notification function */
                Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                                            DmaChannelNotificationPtr(Channel, DMA_CH_INT_SCB);
            }
        }
    }
}
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_DestCircBufRb_ISRHandler
*
*   Service ID              : 0xE4.
*
*   Description             : Destination circular buffer rollback interrupt handler.
*
*   Parameters in           : HwUnitId: HW unit ID of DMA.
*                             ChannelId: Channel ID of DMA.
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
*   Preconditions           : 1. Dma driver must have been initialized before.
*                             2. Terminal interrupt must enabled by Tresos
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DMA_PUBLIC_CODE) Dma_DestCircBufRb_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
)
{
    uint8           IntStatus;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType  Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    Dma_ChannelType Channel;
    uint8           CoreChIdx;
    Mcal_CoreType   CoreId;

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_DESTCIRCBUF_ISR);
    if (E_OK == Err)
    {
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
        /* Get the logical channel via HW unit and physical channel */
        Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];

#if (DMA_DEV_ERROR_DETECT == STD_ON)
        if (DMA_INVALID_CHANNEL == Channel)
        {
            /* Calculated channel id is invalid */
            Dma_ReportError(DMA_SID_DESTCIRCBUF_ISR, DMA_E_PARAM_CHANNEL);
            Err = E_NOT_OK;
        }
        else
        {
            Err = Dma_ChCommCheck(DMA_SID_DESTCIRCBUF_ISR, Channel);
        }
    }

    if (E_NOT_OK == Err)
    {
        /* Destination circular buffer interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_DCB);
        if (0U != IntStatus)
        {
            /* Clear the destination circular status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_DCB);
        }
    }
    else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Destination circular buffer interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_DCB);
        if (0U != IntStatus)
        {
            /* Clear the destination circular status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_DCB);

            CoreId = Mcal_GetCoreId();
            /* Get the logical channel via HW unit and physical channel */
            Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];
            CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
            if (NULL_PTR != Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                    DmaChannelNotificationPtr)
            {
                /* Call notification function */
                Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                                            DmaChannelNotificationPtr(Channel, DMA_CH_INT_DCB);
            }
        }
    }
}
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON) */
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_PatternMatch_ISRHandler
*
*   Service ID              : 0xE5.
*
*   Description             : Data pattern matched interrupt handler.
*
*   Parameters in           : HwUnitId: HW unit ID of DMA.
*                             ChannelId: Channel ID of DMA.
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
*   Preconditions           : 1. Dma driver must have been initialized before.
*                             2. Terminal interrupt must enabled by Tresos
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, DMA_PUBLIC_CODE) Dma_PatternMatch_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
)
{
    Mcal_CoreType    CoreId;
    uint8            IntStatus;
    Dma_ChannelType  CoreChIdx;
    Dma_ChannelType  Channel;
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType   Err;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    Dma_PatternType  CurrPatternIdx;
    Dma_TransferType CurrTransferId;

    /* #Violation: Dma_c_REF_1 */
    CoreId = Mcal_GetCoreId();

#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Check whether the DMA module initialized */
    Err = Dma_CheckInit(DMA_SID_TERMINALCOUNT_ISR);
    if (E_OK == Err)
    {
        /* Get the logical channel via HW unit and physical channel */
        Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];
        if (DMA_INVALID_CHANNEL == Channel)
        {
            /* Calculated channel id is invalid */
            Dma_ReportError(DMA_SID_PATTERNMATCH_ISR, DMA_E_PARAM_CHANNEL);
            Err = E_NOT_OK;
        }
        else
        {
            Err = Dma_ChCommCheck(DMA_SID_PATTERNMATCH_ISR, Channel);
        }
    }

    if (E_NOT_OK == Err)
    {
        /* Pattern match and the data matched interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_PATTERN);
        if (0U != IntStatus)
        {
            /* Clear the pattern match status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_PATTERN);
        }
    }
    else
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Pattern match and the data matched interrupt */
        IntStatus = Dma_Hal_GetInterruptStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_PATTERN);
        if (0U != IntStatus)
        {
            /* Clear the pattern match status */
            Dma_Hal_ClearStatus(Dma_BaseAddrs[HwUnitId], PhyChannelId,
                                               (uint8)DMA_CH_INT_PATTERN);

            Channel = Dma_ConfigPtr->HwUnitConfigPtr->HwToChannelPtr[HwUnitId][PhyChannelId];
            CoreChIdx = Dma_ConfigPtr->ChannelMapInfoPtr[Channel].CoreChIdx;
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
            CurrTransferId = Dma_GetTransferId(Channel);
#else /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
            CurrTransferId = 0U;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
            CurrPatternIdx = Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                                                     ChTransferConfigPtr[CurrTransferId].ChPatternId;

            if (TRUE ==
                Dma_ConfigPtr->CommConfigPtr->PatternConfigPtr[CurrPatternIdx].patternMatchedStop)
            {
                /* Stop after data matched function is enabled */
                /* Change the channel transfer status to none */
                Dma_StatusDataSetPtr[CoreId]->ChStatusPtr[CoreChIdx] = DMA_CH_NONE;
            }

            if (NULL_PTR != Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                    DmaChannelNotificationPtr)
            {
                /* Call notification function */
                Dma_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].
                                            DmaChannelNotificationPtr(Channel, DMA_CH_INT_PATTERN);
            }
        }
    }
}
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dma_c_REF_4 */
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
