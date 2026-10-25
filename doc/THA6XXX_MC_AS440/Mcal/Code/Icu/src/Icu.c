/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Icu.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-TIM
 *
 *   brief                 : This file contains all functions of Icu Driver,
 *                           [SWS_Icu_00131]it depends on MCU 4.4.0, PORT 4.4.0, Resource 4.4.0
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/
/*
*#Violation Summary
*#Icu_c_REF_1:MISRAC2012-Rule-10.5;
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety 
* of the casting.
*
*#Icu_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
* driver must be placed.
*
*#Icu_c_REF_3:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Icu_c_REF_4:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Icu_c_REF_5:MISRAC2012-Rule-8.9; 
* Justification: The value should be placed in the const data sections to reduce code 
* complexity and stack size.
*
*#Icu_c_REF_6:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Icu_c_REF_7:CertC-DCL00-C;
* Justification: Parameter declared refer to AUTOSAR specifications.
*
*#Icu_c_REF_8:CertC-DCL02-C;
* Justification: Company-specific naming conventions  are applied. Developers will not be confused.
*
*#Icu_c_REF_9:CertC-PRE00-C; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Icu_c_REF_10:CWE-1071; 
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Icu_c_REF_11:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Icu_c_REF_12:MISRAC2012-Rule-8.9; 
* Justification: Variables need to be allocated to designated areas.
*
*#Icu_c_REF_13:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*#Icu_c_REF_14:MISRAC2012-Rule-2.2;
* Justification:Platform-based design with configurable macros.
*/

/* [SWS_Icu_00149] N.A The Icu module's environment shall check the integrity if several 
   calls for the same ICU channel are used during runtime in different tasks or ISRs. 
   [SWS_Icu_00150] N.A The Icu module shall not check the integrity if several calls for 
   the same ICU channel are used during runtime in different tasks or ISRs 
   [SWS_Icu_91002][SWS_Icu_91003] N.A drfat Tags:atp.Status=draft */

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Icu.h"
/* [SWS_Icu_00251] shall include Det.h, SchM_Icu.h and Icu_MemMap.h */
/* [SWS_Icu_00213] Included for the declaration of Det_ReportError() */
#include "Det.h"
/* Included for the declaration of the critical section protection functions */
#include "SchM_Icu.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (ICU_VENDOR_ID != ICU_CFG_VENDOR_ID)
#error "Icu.c : Mismatch in Vendor ID"
#endif /* ICU_VENDOR_ID != ICU_CFG_VENDOR_ID */

#if (ICU_MODULE_ID != ICU_CFG_MODULE_ID)
#error "Icu.c : Mismatch in Module ID"
#endif /* \(ICU_MODULE_ID != ICU_CFG_MODULE_ID) */

#if (ICU_AR_RELEASE_MAJOR_VERSION != ICU_CFG_AR_RELEASE_MAJOR_VERSION)
#error "Icu.c : Mismatch in Release Major Version"
#endif /* ICU_AR_RELEASE_MAJOR_VERSION != ICU_CFG_AR_RELEASE_MAJOR_VERSION */

#if (ICU_AR_RELEASE_MINOR_VERSION != ICU_CFG_AR_RELEASE_MINOR_VERSION)
#error "Icu.c : Mismatch in Release Minor Version"
#endif /* ICU_AR_RELEASE_MINOR_VERSION != ICU_CFG_AR_RELEASE_MINOR_VERSION */

#if (ICU_AR_RELEASE_REVISION_VERSION != ICU_CFG_AR_RELEASE_REVISION_VERSION)
#error "Icu.c : Mismatch in Release Revision Version"
#endif /* ICU_AR_RELEASE_REVISION_VERSION != ICU_CFG_AR_RELEASE_REVISION_VERSION */

#if (ICU_SW_MAJOR_VERSION != ICU_CFG_SW_MAJOR_VERSION)
#error "Icu.c : Mismatch in Software Major Version"
#endif /* ICU_SW_MAJOR_VERSION != ICU_CFG_SW_MAJOR_VERSION */

#if (ICU_SW_MINOR_VERSION != ICU_CFG_SW_MINOR_VERSION)
#error "Icu.c : Mismatch in Software Minor Version"
#endif /* ICU_SW_MINOR_VERSION != ICU_CFG_SW_MINOR_VERSION */

#if (ICU_SW_PATCH_VERSION != ICU_CFG_SW_PATCH_VERSION)
#error "Icu.c : Mismatch in Software Patch Version"
#endif /* \(ICU_SW_PATCH_VERSION != ICU_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* #Violation: Icu_c_REF_3 */
/* #Violation: Icu_c_REF_9 */
#define ICU_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_##Exclusive_Area()
/* #Violation: Icu_c_REF_3 */
/* #Violation: Icu_c_REF_9 */
#define ICU_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_##Exclusive_Area()
#define ICU_MEASURE_IRQ_NEW_VALUE                  (1U)
#define ICU_MEASURE_IRQ_CNTOVFL                    (2U)
#define ICU_IRQ_NEW_VALUE_MASK                     (0x01U)
#define ICU_IRQ_CNTOVFL_MASK                       (0x04U)

/* Macros for timestamp channel */
#define ICU_BUFFERSIZE_MIN_VAL                     (0x00U)
#define ICU_NOTIFY_INTERVAL_MIN_VAL                (0x01U)
#define ICU_BUFFER_IDX_INIT_VAL                    (0x0000U)

/* #Violation: Icu_c_REF_4 */
/* #Violation: Icu_c_REF_9 */
#define ICU_GET_HW_INDEX(CoreId, CoreChIdx) \
    (Icu_ConfigPtr->CoreConfigPtr[CoreId]->Icu_ChannelConfigPtr->Icu_ChnConfigPtr[CoreChIdx].Index)
/* #Violation: Icu_c_REF_4 */
/* #Violation: Icu_c_REF_9 */
#define ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx)               \
    (Icu_ConfigPtr->CoreConfigPtr[CoreId]                    \
         ->Icu_ChannelConfigPtr->Icu_ChnConfigPtr[CoreChIdx] \
         .ChannelNumber)

/* #Violation: Icu_c_REF_4 */
/* #Violation: Icu_c_REF_9 */
#define ICU_GET_CORE_CH_IDX(Channel)    (Icu_ConfigPtr->IcuChannelIdxmapPtr[Channel].CoreChIdx)

/* #Violation: Icu_c_REF_4 */
/* #Violation: Icu_c_REF_9 */
#define ICU_GET_EXECUTION_CORE(Channel) (Icu_ConfigPtr->IcuChannelIdxmapPtr[Channel].ExecutionCore)

/* #Violation: Icu_c_REF_11 */
#define ICU_IS_WAKEUP_CH(CoreId, CoreChIdx)                  \
    (TRUE ==                                                 \
     Icu_ConfigPtr->CoreConfigPtr[CoreId]                    \
         ->Icu_ChannelConfigPtr->Icu_ChnConfigPtr[CoreChIdx] \
         .IsWakeupChannel)

/* #Violation: Icu_c_REF_11 */
#define ICU_WAKEUP_CFG_INFO(CoreId, CoreChIdx)               \
    (Icu_ConfigPtr->CoreConfigPtr[CoreId]                    \
         ->Icu_ChannelConfigPtr->Icu_ChnConfigPtr[CoreChIdx] \
         .WakeupSourceCfgInfo)

/* #Violation: Icu_c_REF_4 */
/* #Violation: Icu_c_REF_9 */
#define ICU_CURRENT_MODE(CoreId) (Icu_CoreStatusPtr[CoreId]->Mode)
/****************************************************************************************************
**                             Global Variable Definitions                                         **
****************************************************************************************************/
/* Global variables of core0 */
#if (ICU_MAX_CHANNEL_TO_CORE0 != 0U)
/* #Violation: Icu_c_REF_11 */
#define ICU_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Icu_MemMap.h"

/* Global variables of driver status of core0 */
static VAR(Icu_CoreStateType, ICU_VAR_FAST_CLEARED) Icu_CoreStatusCore0;
/* Global variables of all channels of core0 */
static VAR(Icu_ChannelRamDataType, ICU_VAR_FAST_CLEARED)
    Icu_ChannelRamDataCore0[ICU_MAX_CHANNEL_TO_CORE0];

    /* #Violation: Icu_c_REF_11 */
#define ICU_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"
#endif /* ICU_MAX_CHANNEL_TO_CORE0 != 0U */


/* Global variables of core1 */
#if (ICU_MAX_CHANNEL_TO_CORE1 != 0U)
/* #Violation: Icu_c_REF_11 */
#define ICU_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"

/* Global variables of driver status of core1 */
static VAR(Icu_CoreStateType, ICU_VAR_FAST_CLEARED) Icu_CoreStatusCore1;
/* Global variables of all channels of core1 */
static VAR(Icu_ChannelRamDataType, ICU_VAR_FAST_CLEARED)
    Icu_ChannelRamDataCore1[ICU_MAX_CHANNEL_TO_CORE1];

/* #Violation: Icu_c_REF_11 */
#define ICU_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"
#endif /* ICU_MAX_CHANNEL_TO_CORE1 != 0U */


/* Global variables of core2 */
#if (ICU_MAX_CHANNEL_TO_CORE2 != 0U)
/* #Violation: Icu_c_REF_11 */
#define ICU_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"

/* Global variables of driver status of core2 */
static VAR(Icu_CoreStateType, ICU_VAR_FAST_CLEARED) Icu_CoreStatusCore2;
/* Global variables of all channels of core2 */
static VAR(Icu_ChannelRamDataType, ICU_VAR_FAST_CLEARED)
    Icu_ChannelRamDataCore2[ICU_MAX_CHANNEL_TO_CORE2];

    /* #Violation: Icu_c_REF_11 */
#define ICU_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"
#endif /* ICU_MAX_CHANNEL_TO_CORE2 != 0U */


/* Global variables of core3 */
#if (ICU_MAX_CHANNEL_TO_CORE3 != 0U)
/* #Violation: Icu_c_REF_11 */
#define ICU_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"

/* Global variables of driver status of core3 */
static VAR(Icu_CoreStateType, ICU_VAR_FAST_CLEARED) Icu_CoreStatusCore3;
/* Global variables of all channels of core3 */
static VAR(Icu_ChannelRamDataType, ICU_VAR_FAST_CLEARED)
    Icu_ChannelRamDataCore3[ICU_MAX_CHANNEL_TO_CORE3];

/* #Violation: Icu_c_REF_11 */
#define ICU_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"
#endif /* ICU_MAX_CHANNEL_TO_CORE3 != 0U */

/* #Violation: Icu_c_REF_11 */
#define ICU_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"

/* Global array of pointers to store address of core status */
/* #Violation: Icu_c_REF_6 */
/* #Violation: Icu_c_REF_12 */
static CONSTP2VAR(Icu_ChannelRamDataType, ICU_CONFIG_DATA, ICU_APPL_DATA)
/* #Violation: Icu_c_REF_5 */
    Icu_ChannelRamData[MCAL_NUMBER_OF_CORES] = 
{
#if (ICU_MAX_CHANNEL_TO_CORE0 != 0U)
    (Icu_ChannelRamDataType *)&Icu_ChannelRamDataCore0[0],
#else
    NULL_PTR,
#endif /* ICU_MAX_CHANNEL_TO_CORE0 != 0U */
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (ICU_MAX_CHANNEL_TO_CORE1 != 0U)
    (Icu_ChannelRamDataType *)&Icu_ChannelRamDataCore1[0],
#else
    NULL_PTR,
#endif /* ICU_MAX_CHANNEL_TO_CORE1 != 0U */
#endif /* MCAL_NUMBER_OF_CORES > 1U */
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (ICU_MAX_CHANNEL_TO_CORE2 != 0U)
    (Icu_ChannelRamDataType *)&Icu_ChannelRamDataCore2[0],
#else
    NULL_PTR,
#endif /* ICU_MAX_CHANNEL_TO_CORE2 != 0U */
#endif /* MCAL_NUMBER_OF_CORES > 2U */
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (ICU_MAX_CHANNEL_TO_CORE3 != 0U)
    (Icu_ChannelRamDataType *)&Icu_ChannelRamDataCore3[0]
#else
    NULL_PTR
#endif /* ICU_MAX_CHANNEL_TO_CORE3 != 0U */
#endif /* MCAL_NUMBER_OF_CORES > 3U */
};

/* Global array of pointers to store address of core status */
/* #Violation: Icu_c_REF_6 */
static CONSTP2VAR(Icu_CoreStateType, ICU_CONFIG_DATA, ICU_APPL_DATA)
    Icu_CoreStatusPtr[MCAL_NUMBER_OF_CORES] = 
{
#if (ICU_MAX_CHANNEL_TO_CORE0 != 0U)
    (Icu_CoreStateType *)&Icu_CoreStatusCore0,
#else
    NULL_PTR,
#endif /* ICU_MAX_CHANNEL_TO_CORE0 != 0U */
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (ICU_MAX_CHANNEL_TO_CORE1 != 0U)
    (Icu_CoreStateType *)&Icu_CoreStatusCore1,
#else
    NULL_PTR,
#endif /* ICU_MAX_CHANNEL_TO_CORE1 != 0U */
#endif /* MCAL_NUMBER_OF_CORES > 1U */
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (ICU_MAX_CHANNEL_TO_CORE2 != 0U)
    (Icu_CoreStateType *)&Icu_CoreStatusCore2,
#else
    NULL_PTR,
#endif /* ICU_MAX_CHANNEL_TO_CORE2 != 0U */
#endif /* MCAL_NUMBER_OF_CORES > 2U */
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (ICU_MAX_CHANNEL_TO_CORE3 != 0U)
    (Icu_CoreStateType *)&Icu_CoreStatusCore3
#else
    NULL_PTR
#endif /* ICU_MAX_CHANNEL_TO_CORE3 != 0U */
#endif /* MCAL_NUMBER_OF_CORES > 3U */
};

/* #Violation: Icu_c_REF_11 */
#define ICU_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"

/* #Violation: Icu_c_REF_11 */
#define ICU_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"
/* Global pointer variable for channel configuration */
static P2CONST(Icu_ConfigType, ICU_VAR, ICU_CONFIG_DATA) Icu_ConfigPtr;

/* Variable is used to support to access the GTM_CFG common register of GTM
   | BIT31 - BIT5: Unused       
   | BIT3: Core3 initialization status
   | BIT2: Core2 initialization status
   | BIT1: Core1 initialization status
   | BIT0: Core0 initialization status*/
static uint32 Icu_AuxInSrcStatus;

/* #Violation: Icu_c_REF_11 */
#define ICU_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"

/* #Violation: Icu_c_REF_11 */
#define ICU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Icu_c_REF_6 */
static FUNC_P2VAR(Icu_ChannelRamDataType, ICU_CODE, ICU_APPL_DATA) Icu_GetChannelPar
(
    Mcal_CoreType CoreId, 
    uint8 CoreChIndex
);
#if (ICU_DEV_ERROR_DETECT == STD_ON)

static FUNC(Std_ReturnType, ICU_CODE) Icu_CheckDetErrors
(
    Icu_ChannelType ChannelNumber, 
    uint8 ApiSid
);
LOCAL_INLINE FUNC(Std_ReturnType, ICU_PRIVATE_CODE) Icu_DeInitDetCheck
(
    Mcal_CoreType CoreId
);

#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)

LOCAL_INLINE FUNC(boolean, ICU_PRIVATE_CODE) Icu_StartSignalCheck
(
    Gtm_SignalState CurrentLevel,
    uint8 MeasureProperty
);
#endif /* ICU_SIGNAL_MEASUREMENT_API == STD_ON */

/****************************************************************************************************
 *   Function Name           : Icu_GetChannelPar
 *
 *   Service ID              :
 *
 *   Description             : This API get CH Parameter.
 *
 *   Parameters in           : CoreId: Core index,
 *                             CoreChIdx: the ch index in COREx.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : reentrancy .
 *
 *   Return value            : Icu_ChannelRamDataType.
 *
 *   Preconditions           :  None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_6 */
static FUNC_P2VAR(Icu_ChannelRamDataType, ICU_CODE, ICU_APPL_DATA) Icu_GetChannelPar
(
    Mcal_CoreType CoreId, 
    uint8 CoreChIndex
)
{
/* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) RamDataPtr;
    /* Get the Parameter set of channel */
    RamDataPtr = Icu_ChannelRamData[CoreId];    
    RamDataPtr = &RamDataPtr[CoreChIndex];
    return RamDataPtr;
}

/****************************************************************************************************
 *   Function Name           : Icu_InitRamParameter
 *
 *   Service ID              :
 *
 *   Description             : This API init the parameter from config.
 *
 *   Parameters in           : RamDataPtr: Channel RAM parameter,
 *                             ChCfgPtr: config date of channel.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : No-Reentrant.
 *
 *   Return value            : none.
 *
 *   Preconditions           :  None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
LOCAL_INLINE FUNC(void, ICU_CODE) Icu_InitRamParameter
(
    /* #Violation: Icu_c_REF_6 */
    CONSTP2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) RamDataPtr,
    CONSTP2CONST(Icu_ChnConfigType, AUTOMATIC, ICU_CONFIG_DATA) ChCfgPtr
)
{
    /* [SWS_Icu_00040] Initialize each channel status as idle */
    RamDataPtr->ChannelStatus = ICU_IDLE;
    /* [SWS_Icu_00061] Disable notification for each channel */
    RamDataPtr->NotificationEnable = FALSE;
    RamDataPtr->IsChannelRunning = FALSE;
    /* [SWS_Icu_00121] The function Icu_Init shall disable the wakeup-capability of all
       channels*/
    RamDataPtr->WakeupIsEnabled = FALSE;
    /* store the config data */
    RamDataPtr->MeasurementMode = (Icu_MeasurementModeType)ChCfgPtr->Gtm_Icu_ConfigPtr->icuMode;
    RamDataPtr->Edge = ChCfgPtr->Gtm_Icu_ConfigPtr->edge;

    /* init parameter for special mode */
    switch (RamDataPtr->MeasurementMode)
    {
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
        case ICU_MODE_SIGNAL_MEASUREMENT:
        {
            /* Init parameter for Tim in ICU_MODE_SIGNAL_MEASUREMENT mode */
            RamDataPtr->ChannelData.Icu_PwmMeasureRam.MeasureProperty = ChCfgPtr->ChannelProperties;
            RamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput = FALSE;
            RamDataPtr->ChannelData.Icu_PwmMeasureRam.IsrOverflowThreshold = 1000U;
            RamDataPtr->ChannelData.Icu_PwmMeasureRam.IsOverFlowDetect = FALSE;
            RamDataPtr->ChannelData.Icu_PwmMeasureRam.IrqType = 0U;
            break;
        }
#endif /* ICU_SIGNAL_MEASUREMENT_API == STD_ON */
#if (ICU_TIMESTAMP_API == STD_ON)
        case ICU_MODE_TIMESTAMP:
        {
            /* Init parameter for Tim in ICU_MODE_TIMESTAMP mode */
            /* #Violation: Icu_c_REF_1 */
            RamDataPtr->ChannelData.Icu_TimeStampRam.BufferType = (Icu_TimestampBufferType)(ChCfgPtr->ChannelProperties);
            RamDataPtr->ChannelData.Icu_TimeStampRam.BufferPtr = NULL_PTR;
            break;
        }
#endif /* ICU_TIMESTAMP_API == STD_ON */ 
#if (ICU_EDGE_COUNT_API == STD_ON)
        case ICU_MODE_EDGE_COUNTER:
        {
            /* Init parameter for Tim in ICU_MODE_EDGE_COUNTER mode */
            RamDataPtr->ChannelData.Icu_EdgeCountRam.IcuEdgeCount = MCAL_ZERO;
            RamDataPtr->ChannelData.Icu_EdgeCountRam.IrqType = ICU_MEASURE_IRQ_CNTOVFL;
            break;
        }
#endif /* ICU_EDGE_COUNT_API == STD_ON */ 
        default:
        {
            /*DoNothing*/
            break;
        }
    }
}

#if (ICU_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_CheckDetErrors
 *
 *   Service ID              :
 *
 *   Description             : This API Check Parameter of APIS.
 *
 *   Parameters in           : ChannelNumber: Channel index,
 *                             ApiSid: API service id.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Std_ReturnType.
 *
 *   Preconditions           :  None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
static FUNC(Std_ReturnType, ICU_CODE) Icu_CheckDetErrors
(
    Icu_ChannelType ChannelNumber, 
    uint8 ApiSid
)
{
    Std_ReturnType ReturnValue;
    Mcal_CoreType  CoreId;

    /* #Violation: Icu_c_REF_4 */
    CoreId = Mcal_GetCoreId();
    ReturnValue = E_NOT_OK;

    /* [SWS_Icu_00159] [SWS_Icu_00160][SWS_Icu_00161]
     * [SWS_Icu_00162][SWS_Icu_00163][SWS_Icu_00164][SWS_Icu_00169] [SWS_Icu_00171]
     * [SWS_Icu_00172][SWS_Icu_00173] [SWS_Icu_00371][SWS_Icu_00376][SWS_Icu_00174] [SWS_Icu_00176]
     * [SWS_Icu_00177] [SWS_Icu_00178][SWS_Icu_00180] Check ChannelNumber is in the valid range */
    if (ICU_TOTAL_CHANNEL_NUMBER <= ChannelNumber)
    {
        /* Report to DET module */
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ApiSid, ICU_E_PARAM_CHANNEL);
    }
    else if (NULL_PTR == Icu_CoreStatusPtr[CoreId])
    {
        /* Report Error to DET */
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ApiSid, ICU_E_CORE_NOT_CONFIGURED);
    }
    /* Check if the ICU Driver is initialized properly*/
    else if (ICU_INITIALIZED != Icu_CoreStatusPtr[CoreId]->Icu_InitState)
    {
        /* [SWS_Icu_00022] Report to DET module */
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ApiSid, ICU_E_UNINIT);
    }
    /* #Violation: Icu_c_REF_4 */
    else if (CoreId != ICU_GET_EXECUTION_CORE(ChannelNumber))
    {
        /* Report Error to DET */
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ApiSid, ICU_E_CORE_CHANNEL_MISMATCH);
    }
    /* #Violation: Icu_c_REF_4 */
    else if((ICU_MODE_SLEEP == ICU_CURRENT_MODE(CoreId)) && 
            (ICU_GET_INPUT_STATE_SID != ApiSid))
    {
        (void)Det_ReportError(
          ICU_MODULE_ID, ICU_INSTANCE_ID, ApiSid, ICU_E_INVALID_MODE);
    }
    else
    {
        ReturnValue = E_OK;
    }

    return ReturnValue;
}
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */

#if (ICU_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_InitDetCheck
 *
 *   Service ID              : None.
 *
 *   Description             : This API is used to check the development error of Icu_Init API.
 *
 *   Parameters in           : ConfigPtr: Pointer to the configuration structure.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Std_ReturnType.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
static FUNC(Std_ReturnType, ICU_PRIVATE_CODE) Icu_InitDetCheck
(
    const Icu_ConfigType* const ConfigPtr
)
{
    Mcal_CoreType CoreId;
    Std_ReturnType ErrValue;

    ErrValue = E_NOT_OK;

    /* #Violation: Icu_c_REF_4 */
    CoreId = Mcal_GetCoreId();
    /* Initialize the DET return value */
    if (NULL_PTR == ConfigPtr)
    {
        /* Report Error to DET */
        (void)Det_ReportError(
            ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_INIT_FAILED);
    }
    else if (NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId])
    {
        /* Report Error to DET */
        (void)Det_ReportError(
            ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_CORE_NOT_CONFIGURED);

    }
#if (ICU_ALREADY_INIT_DET_CHECK == STD_ON)
    /* Check if the ICU Driver is already initialized */
    else if (ICU_INITIALIZED == Icu_CoreStatusPtr[CoreId]->Icu_InitState)
    {
        /* [SWS_Icu_00220] Report Error to DET [SWS_Icu_00054] */
        (void)Det_ReportError(
            ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_ALREADY_INITIALIZED);
    }
#endif /* End of (ICU_ALREADY_INIT_DET_CHECK \== STD_ON */
    else 
    {
        ErrValue = E_OK;
    }

    return ErrValue;
}
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */

#if (ICU_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_DeInitDetCheck
 *
 *   Service ID              : None.
 *
 *   Description             : This API returns the Det error of Icu_DeInit.
 *
 *   Parameters in           : CoreId: Core id.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : E_OK: DET check passed.
 *                             E_NOT_OK: DET check failed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, ICU_PRIVATE_CODE) Icu_DeInitDetCheck
(
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;

    ErrValue = E_NOT_OK;
    if (NULL_PTR == Icu_CoreStatusPtr[CoreId])
    {
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DEINIT_SID, ICU_E_CORE_NOT_CONFIGURED);
    }
    /* [SWS_Icu_00221] Check if the Icu Module is not initialized */
    else if (ICU_INITIALIZED != Icu_CoreStatusPtr[CoreId]->Icu_InitState)
    {
        /* Report Error to DET */
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DEINIT_SID, ICU_E_UNINIT);
    }
    else
    {
        ErrValue = E_OK;
    }

    return ErrValue;
}
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_StartSignalCheck
 *
 *   Service ID              : None.
 *
 *   Description             : This API returns the Measure action.
 *
 *   Parameters in           : CurrentLevel: Current input level.
 *                             MeasureProperty: Measure level property.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : TRUE: Measure immediate.
 *                             FALSE: Not measure immediate..
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
LOCAL_INLINE FUNC(boolean, ICU_PRIVATE_CODE) Icu_StartSignalCheck
(
    Gtm_SignalState CurrentLevel,
    uint8 MeasureProperty
)
{
    boolean            MeasureImmediate;
    MeasureImmediate   = FALSE;
    /* [SWS_Icu_00140] l start themeasurement of signals beginning with the configured
     * default start edge whichoccurs first after the call of this service.*/
    /* #Violation: Icu_c_REF_4 */
    if (ICU_MEASUREMENT_PRO_HIGH_TIME == MeasureProperty)
    {
        if (GTM_SIGNALSTATE_HIGH == CurrentLevel)
        {
            /* current is vaild level,do not start test immediatly, otherwise return
             * wrong result */
            MeasureImmediate = FALSE;
        }
        else
        {
            MeasureImmediate = TRUE;
        }
    }
    /* #Violation: Icu_c_REF_4 */
    else if (ICU_MEASUREMENT_PRO_LOW_TIME == MeasureProperty)
    {
        if (GTM_SIGNALSTATE_HIGH == CurrentLevel)
        {
            MeasureImmediate = TRUE;
        }
        else
        {
            /* current is vaild level,do not start test immediatly, otherwise return
             * wrong result */
            MeasureImmediate = FALSE;
        }
    }
    else
    /* #Violation: Icu_c_REF_10 */
    {
        /*Do nothing */
    }

    return MeasureImmediate;
}
#endif /* End of (ICU_SIGNAL_MEASUREMENT_API \== STD_ON) */

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
 *   Function Name           : Icu_Init
 *
 *   Service ID              : 0x00
 *
 *   Description             : This API performs the initialization of the Icu Driver Component.
 *
 *   Parameters in           : ConfigPtr: Pointer to a selected configuration structure.
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
 *   Preconditions           : [SWS_Icu_00131] None.
 *
 *   AUTOSAR_Requirement     : Sws_Icu_00191.[SWS_Icu_00297][SWS_Icu_00298][SWS_Icu_00051]
 *   [SWS_Icu_00052][SWS_Icu_00053][SWS_Icu_00128][SWS_Icu_00129]
 *   [SWS_Icu_00138] Pre-compile is NOT APPLICABLE.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_Init
(
    /* #Violation: Icu_c_REF_7 */
    P2CONST(Icu_ConfigType, AUTOMATIC, ICU_CONFIG_DATA) ConfigPtr
)
{
    /* Defining a pointer to the channel config parameters */
    P2CONST(Icu_ChnConfigType, AUTOMATIC, ICU_CONFIG_DATA) ChCfgPtr;
    P2CONST(Icu_ChnConfigType, AUTOMATIC, ICU_CONFIG_DATA) Icu_ChnCfgPtr;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) RamDataPtr;
    Mcal_CoreType   CoreId;
    Gtm_Icu_Driver  Icu_Driver;
    Icu_ChannelType CoreChIdx;
    /* Declare the variable to store return value */
    Std_ReturnType ReturnValue;
    Std_ReturnType LockStatus;
    boolean         SafetyFlag;
    /* #Violation: Icu_c_REF_14 */
    ReturnValue = E_OK;
    SafetyFlag = TRUE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_InitDetCheck(ConfigPtr);

    /* Check if any DET was reported */
    if (E_OK == ReturnValue)
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* SWS_Icu_00054 */
        Icu_ConfigPtr = ConfigPtr;

        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();

        /*Update the global pointer with the first channel's database address */
        Icu_ChnCfgPtr = ConfigPtr->CoreConfigPtr[CoreId]->Icu_ChannelConfigPtr->Icu_ChnConfigPtr;

        /* Initialize all the configured Icu Channels */
        for (CoreChIdx = MCAL_ZERO; (CoreChIdx < ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels) && (E_OK == ReturnValue);
             CoreChIdx++)
        {
            /* Load the channel data pointer */
            RamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
            ChCfgPtr = &Icu_ChnCfgPtr[CoreChIdx];

#if (ICU_DEV_RUNTIME_ERROR_DETECT == STD_ON)
            if (TRUE == RamDataPtr->IsChannelRunning)
            {
                /* [SWS_Icu_00054] The Icu module's environment shall not call Icu_Init during a
                 * running operation (e. g. timestamp measurement or edge counting*/
                if ((ICU_MODE_TIMESTAMP == RamDataPtr->MeasurementMode) ||
                    (ICU_MODE_EDGE_COUNTER == RamDataPtr->MeasurementMode))
                {
                    (void)Det_ReportRuntimeError(
                        ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_STARTED);
                }
            }
#endif /* End of #if (ICU_DEV_RUNTIME_ERROR_DETECT \== STD_ON */
            /*Store the parameter of CH into Ram*/
            Icu_InitRamParameter(RamDataPtr, ChCfgPtr);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);

            /* [SWS_Icu_00006] initialize all relevant registers*/
            SafetyFlag &= Gtm_Icu_Hal_InitChannel(&Icu_Driver, ChCfgPtr->Gtm_Icu_ConfigPtr);
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_ICU);
            if (E_OK == LockStatus)
            {
                /* Set internal signal rout */
                SafetyFlag &= Gtm_Icu_Hal_SetAuxInput(&Icu_Driver, ChCfgPtr->Gtm_Icu_ConfigPtr);
                Mcal_ReleaseLock(MCAL_LOCK_ID_ICU);
            }
            else
            {
#if (ICU_SAFETY_ENABLE == STD_ON)
                (void)Det_ReportError(
                    ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_GETLOCK_FAILED);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
                ReturnValue = E_NOT_OK;
            }

            if (TRUE != SafetyFlag)
            {
#if (ICU_SAFETY_ENABLE == STD_ON)
                (void)Det_ReportRuntimeError(
                    ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_SAFETY_CHECK_FAILED);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
                ReturnValue = E_NOT_OK;
            }
        }

        /* Recrod the input source selection for signal TIM[i]_AUX_IN set status */
        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_ICU);

        if(E_OK == LockStatus)
        {
            /* EB guarantees that this parameter is the same for all channels */
            if(FALSE == Icu_ChnCfgPtr[0U].Gtm_Icu_ConfigPtr->auxInCfg.isBigger8)
            {
                /* Only recrod the core status, because it has been set 
                   in Gtm_Icu_Hal_SetAuxInput before */
                Icu_AuxInSrcStatus = 
                    ((uint32)1U << (uint32)CoreId) | Icu_AuxInSrcStatus;
            }
            Mcal_ReleaseLock(MCAL_LOCK_ID_ICU);
        }
        else
        {
#if (ICU_SAFETY_ENABLE == STD_ON)
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_INIT_SID, ICU_E_GETLOCK_FAILED);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
            ReturnValue = E_NOT_OK;
        }
        if (E_OK == ReturnValue)
        {
            /* [SWS_Icu_00060] The function Icu_Init shall set the module mode to ICU_MODE_NORMAL*/
            Icu_CoreStatusPtr[CoreId]->Mode = ICU_MODE_NORMAL;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
            /* SWS_Icu_00022 */
            /* Set Icu Driver status as initialized */
            Icu_CoreStatusPtr[CoreId]->Icu_InitState = ICU_INITIALIZED;
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
        }
    }
} /* End of API Icu_Init */

/* SWS_Icu_00092, SWS_Icu_00301 */
#if (ICU_DE_INIT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_DeInit
 *
 *   Service ID              : 0x01
 *
 *   Description             : This API performs the De-initialization of the Icu Driver Component.
 *
 *   Parameters in           : None
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : Sws_Icu_00193.[SWS_Icu_00300][SWS_Icu_00299][SWS_Icu_00022]
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_DeInit
(
    void
)
{
    /* Defining a pointer to the CH Ram data */
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) RamDataPtr;
    P2CONST(Icu_ChnConfigType, AUTOMATIC, ICU_CONFIG_DATA) Icu_ChnCfgPtr;
    uint8              ChannelNo;
    uint8              CoreChIdx;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    Icu_ChannelType    MaxChannels;
    Std_ReturnType     ReturnValue;
    Gtm_TimAux_In      InputRount;
    boolean            SafetyFlag;
    Std_ReturnType LockStatus;

    SafetyFlag = TRUE;

    /* #Violation: Icu_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_DeInitDetCheck(CoreId);
    if(E_OK == ReturnValue)
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        MaxChannels = Icu_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels;
        for (ChannelNo = MCAL_ZERO; ChannelNo < MaxChannels;
             ChannelNo++)
        {
            CoreChIdx = ChannelNo;
            /* [SWS_Icu_00091] influence only the peripherals which are allocated by static
             * configuration and/or the runtime configuration set passed by the previous call of
             * Icu_Init() Load the channel data pointer */
            RamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);

#if (ICU_DEV_RUNTIME_ERROR_DETECT == STD_ON)
            if (TRUE == RamDataPtr->IsChannelRunning)
            {
                /* [SWS_Icu_00152] The Icu module environment shall not call Icu_DeInit during a
                 * running operation (e. g. timestamp measurement or edge counting)*/
                if ((ICU_MODE_TIMESTAMP == RamDataPtr->MeasurementMode) ||
                    (ICU_MODE_EDGE_COUNTER == RamDataPtr->MeasurementMode))
                {
                    (void)Det_ReportRuntimeError(
                        ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DEINIT_SID, ICU_E_STARTED);
                }
            }
#endif /* End of #if (ICU_DEV_RUNTIME_ERROR_DETECT \== STD_ON */

            /* [SWS_Icu_00036] set the state of the peripherals
             * used by configuration as the same after power on reset*/
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
            Gtm_Icu_Hal_DeinitChannel(&Icu_Driver);
            /* #Violation: Icu_c_REF_4 */
            InputRount.tim = Icu_Driver.tim;
            /* #Violation: Icu_c_REF_4 */
            InputRount.channel = Icu_Driver.channel;
            InputRount.selOutN = 0U;
            InputRount.src = 0U;
            /* De-Init the internal rout function */
            SafetyFlag &= Gtm_Icu_Hal_TimAuxIn((const Gtm_TimAux_In *)&InputRount);
            /* Initialize each channel status as idle */
            RamDataPtr->ChannelStatus = ICU_IDLE;
            RamDataPtr->IsChannelRunning = FALSE;
            /* [SWS_Icu_00037] Disable notification for each channel */
            RamDataPtr->NotificationEnable = FALSE;
            /*other parameter will be initialized by init() function */
        }

        /* Recrod the input source selection for signal TIM[i]_AUX_IN set status */
        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_ICU);

        if(E_OK == LockStatus)
        {
            Icu_ChnCfgPtr = Icu_ConfigPtr->CoreConfigPtr[CoreId]->Icu_ChannelConfigPtr->Icu_ChnConfigPtr;
            /* EB guarantees that this parameter is the same for all channels */
            if(FALSE == Icu_ChnCfgPtr->Gtm_Icu_ConfigPtr->auxInCfg.isBigger8)
            {
                /* Re-set core bit */
                Icu_AuxInSrcStatus = 
                  (~((uint32)1U << (uint32)CoreId)) & Icu_AuxInSrcStatus;

                if(0U == Icu_AuxInSrcStatus)
                {
                    /* The current core is the last core and is responsible 
                       for deinitializing the GTM TIM Aux in src */
                    SafetyFlag &= Gtm_Icu_Hal_SetTimSrcInMux(0U);
                }
            }
            Mcal_ReleaseLock(MCAL_LOCK_ID_ICU);
        }
        else
        {
#if (ICU_SAFETY_ENABLE == STD_ON)
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DEINIT_SID, ICU_E_GETLOCK_FAILED);
#endif /* ICU_SAFETY_ENABLE == STD_ON */       
            ReturnValue = E_NOT_OK;
        }

        if (TRUE != SafetyFlag)
        {
#if (ICU_SAFETY_ENABLE == STD_ON)
            (void)Det_ReportRuntimeError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DEINIT_SID, ICU_E_SAFETY_CHECK_FAILED);
#endif /* ICU_SAFETY_ENABLE == STD_ON */       
            ReturnValue = E_NOT_OK;
        }
    }

    if (E_OK == ReturnValue)
    {
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* Set Icu Driver status as un-initialized */
        Icu_CoreStatusPtr[CoreId]->Icu_InitState = ICU_UNINITIALIZED;
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    }

} /* End of API Icu_DeInit */

#endif /* End of (ICU_DE_INIT_API \== STD_ON */

/* SWS_Icu_00095, SWS_Icu_00303 */
#if (ICU_SET_MODE_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_SetMode
 *
 *   Service ID              : 0x02
 *
 *   Description             : This function sets the ICU mode
 *
 *   Parameters in           : Mode:
 *                             ICU_MODE_NORMAL: Normal operation, all used interrupts are enabled 
 *                                              according to the notification requests.
 *                             ICU_MODE_SLEEP: Reduced power mode. In sleep mode only those 
 *                                             notifications are available which are configured 
 *                                             as wakeup capable.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : [Sws_Icu_00194][SWS_Icu_00008][SWS_Icu_00302][SWS_Icu_00133]
 *                             [SWS_Icu_00258]
 ****************************************************************************************************/
void Icu_SetMode
(
    Icu_ModeType Mode
)
{
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType      CoreId;
    uint32             ChannelNo;

    CoreId = Mcal_GetCoreId();

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == Icu_CoreStatusPtr[CoreId])
    {
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_MODE_SID, ICU_E_CORE_NOT_CONFIGURED);
    }
    else if (ICU_INITIALIZED != Icu_CoreStatusPtr[CoreId]->Icu_InitState)
    {
        /* SWS_Icu_00022 Report to DET module */
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_MODE_SID, ICU_E_UNINIT);
    }
    /* [SWS_Icu_00125] ICU_E_PARAM_MODE */
    else if (ICU_MODE_SLEEP < Mode)
    {
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_MODE_SID, ICU_E_PARAM_MODE);
    }
    else
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    {
        if (Icu_CoreStatusPtr[CoreId]->Mode != Mode)
        {
            if (ICU_MODE_SLEEP == Mode)
            {
                /* are there any channel running */
                for (ChannelNo = MCAL_ZERO;
                     ((ChannelNo < Icu_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels));
                     ChannelNo++)
                {
                    /* Load the channel data pointer */
                    Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, ChannelNo);
                    /* SWS_Icu_00261: All channels are stopped except those channels
                       - which have been configured as wakeup capable and
                       - which were explicitly enabled by the call of Icu_EnableWakeup() */
                    if ((TRUE == Icu_ChannelRamDataPtr->IsChannelRunning) && 
                        (FALSE == Icu_ChannelRamDataPtr->WakeupIsEnabled))
                    {
                        (void)Det_ReportRuntimeError(
                            ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_MODE_SID, ICU_E_BUSY_OPERATION);
                        ChannelNo = Icu_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels;
                    }
                    /*
                    [SWS_Icu_00012] only those wakeup events are available which are
                    configured as wakeup capable, enabled via Icu_EnableWakeup() after
                    Icu_Init() and which are not disabled via service
                    Icu_DisableWakeup() */
                    /* If the wake-up function is enabled(i.e., the function is statically configured
                       and enabled by calling the Icu_EnableWakeup function).In this case, interrupts 
                       should be enabled, but interrupts are enabled when the Icu_EnableEdgeDetection 
                       function is called, and the Icu_EnableEdgeDetection function is called before 
                       this function is called, so no processing is required */

                    /* [SWS_Icu_00260] all other interrupts handled by this module are disabled 
                       and must not lead to an exit from the reduced power mode state (e.g. idle, 
                       halt) of the MCU if the event occurs. */
                    /* If the wake-up function is not configured for the channel, or if the wake-up
                       function is configured but not enabled, the interrupt should be disabled. 
                       However, this function will check the running status of these channels, and 
                       will only execute correctly when all of them are in a stopped state.When their 
                       channel is stopped, the interrupt has no effect, 
                       so nothing is done in this case */
                }
            }
            else
            {
                /* When entering NORMAL mode, the interrupt that was disabled when entering sleep 
                   mode should be resumed. But going into sleep mode is designed in such a way that 
                   it doesn't disable interrupts, so there's really no need to recover any 
                   interruptions */
            }
            Icu_CoreStatusPtr[CoreId]->Mode = Mode;
        }
    }
}
#endif /* ICU_SET_MODE_API \== STD_ON */ 

/* SWS_Icu_00306, SWS_Icu_00096 */
#if (ICU_DISABLE_WAKEUP_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_DisableWakeup
 *
 *   Service ID              : 0x03
 *
 *   Description             : This function disables the wakeup capability of a single ICU channel.
 *
 *   Parameters in           : channel:
 *                               Numeric identifier of the ICU channel
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
 *   AUTOSAR_Requirement     : Sws_Icu_00195.[SWS_Icu_00304][SWS_Icu_00305][SWS_Icu_00013]
 ****************************************************************************************************/
void Icu_DisableWakeup
(
    Icu_ChannelType Channel
)
{
    uint8          CoreChIdx;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType CoreId;
    CoreId = Mcal_GetCoreId();

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Icu_00024 */
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_DISABLE_WAKEUP_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    {
        /* SWS_Icu_00012 which are not disabled via service Icu_DisableWakeup() */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00305 */
        if (ICU_IS_WAKEUP_CH(CoreId, CoreChIdx))
        {
            Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
            Icu_ChannelRamDataPtr->WakeupIsEnabled = FALSE;
        }
        else
        {
#if (ICU_DEV_ERROR_DETECT == STD_ON)
            /* [SWS_Icu_00059] raise development error ICU_E_PARAM_CHANNEL */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_WAKEUP_SID, ICU_E_PARAM_CHANNEL);
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
        }
    
    }
}
#endif /* ICU_DISABLE_WAKEUP_API \== STD_ON */ 

/* SWS_Icu_00097, SWS_Icu_00308 */
#if (ICU_ENABLE_WAKEUP_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_EnableWakeup
 *
 *   Service ID              : 0x04
 *
 *   Description             : This function (re-)enables the wakeup capability of the given ICU 
 *                             channel.
 *
 *   Parameters in           : channel:
 *                               Numeric identifier of the ICU channel
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
 *   AUTOSAR_Requirement     : Sws_Icu_00196.[SWS_Icu_00307][SWS_Icu_00014]
 ****************************************************************************************************/
void Icu_EnableWakeup
(
    Icu_ChannelType Channel
)
{
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType  CoreId;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    uint8          CoreChIdx;

    CoreId = Mcal_GetCoreId();

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Icu_00155 */
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_ENABLE_WAKEUP_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    {
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        if (ICU_IS_WAKEUP_CH(CoreId, CoreChIdx))
        {
            Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
            Icu_ChannelRamDataPtr->WakeupIsEnabled = TRUE;
        }
        else
        {
#if (ICU_DEV_ERROR_DETECT == STD_ON)
            /* SWS_Icu_00156 */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_WAKEUP_SID, ICU_E_PARAM_CHANNEL);
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
        }
    }
}
#endif /* ICU_ENABLE_WAKEUP_API \== STD_ON */ 

/* SWS_Icu_00362, SWS_Icu_00360 */
#if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_CheckWakeup
 *
 *   Service ID              : 0x15
 *
 *   Description             : Checks if a wakeup capable ICU channel is the source for a wakeup 
 *                              event and calls the ECU state manager service EcuM_SetWakeupEvent 
 *                              in case of a valid ICU channel wakeup event..
 *
 *   Parameters in           : WakeupSource:
 *                               Informatin on wakeup source to be checked.The associated ICU channel 
 *                               can be determined from configuration data.
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
 *   AUTOSAR_Requirement     : [SWS_Icu_00358][SWS_Icu_00361]
 ****************************************************************************************************/
void Icu_CheckWakeup
(
    EcuM_WakeupSourceType WakeupSource
)
{
    Mcal_CoreType   CoreId;
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
    Icu_ChannelType ChannelNo;
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
#endif /* ICU_REPORT_WAKEUP_SOURCE == STD_ON */

    CoreId = Mcal_GetCoreId();
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == Icu_CoreStatusPtr[CoreId])
    {
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_CHECK_WAKEUP_SID, ICU_E_CORE_NOT_CONFIGURED);
    }
    else if (ICU_INITIALIZED != Icu_CoreStatusPtr[CoreId]->Icu_InitState)
    {
        /* [SWS_Icu_00363] Report to DET module */
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_CHECK_WAKEUP_SID, ICU_E_UNINIT);
    }
    else
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    {
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
        for (ChannelNo = MCAL_ZERO; ChannelNo < Icu_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels;
             ChannelNo++)
        {
            Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, ChannelNo);
            /* invoked EcuM_CheckWakeup before */
            if (TRUE == Icu_ChannelRamDataPtr->WakeupSourceIsSet)
            {
                /* SWS_Icu_00359 */
                if (WakeupSource == ICU_WAKEUP_CFG_INFO(CoreId, ChannelNo))
                {
                    /* [SWS_Icu_00359] call EcuM_SetWakeupEvent to indicate a valid timer
                    wakeup event to the ECU State Manager*/
                    EcuM_SetWakeupEvent(WakeupSource);
                    Icu_ChannelRamDataPtr->WakeupSourceIsSet = FALSE;
                    ChannelNo = Icu_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels; /*break*/
                }
            }
        }
#endif /* ICU_REPORT_WAKEUP_SOURCE == STD_ON */
    }
}
#endif /* ICU_WAKEUP_FUNCTIONALITY_API \== STD_ON */

/****************************************************************************************************
 *   Function Name           : Icu_SetActivationCondition
 *
 *   Service ID              : 0x05
 *
 *   Description             : This API service will set the activation edge
 *
 *   Parameters in           : Channel: Numeric identifier of the ICU channel.
 *                             Activation: Edge type to be set.
                                - ICU_RISING_EDGE
                                - ICU_FALLING_EDGE
                                - ICU_BOTH_EDGES
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
 *   AUTOSAR_Requirement     : Sws_Icu_00197.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_SetActivationCondition
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel, 
    Icu_ActivationType Activation
)
{
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    Mcal_CoreType   CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_SET_ACTIVATION_CONDITION_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00309 */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* SWS_Icu_00090 */
        if (ICU_MODE_SIGNAL_MEASUREMENT == Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID,
                ICU_INSTANCE_ID,
                ICU_SET_ACTIVATION_CONDITION_SID,
                ICU_E_PARAM_CHANNEL);
        }
        /* [SWS_Icu_00043] If development error detection is enabled the function 
           Icu_SetActivationCondition shall check the parameter Activation. The 
           function Icu_SetActivationCondition shall raise the error 
           ICU_E_PARAM_ACTIVATION if Activation is invalid but only for the requested ICU 
           channel. */
        else if (Activation > ICU_BOTH_EDGES)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID,
                ICU_INSTANCE_ID,
                ICU_SET_ACTIVATION_CONDITION_SID,
                ICU_E_PARAM_ACTIVATION);
        }
        /* Check if any DET was reported */
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON */
        {
            /* Set the activation edge value */
            /* #Violation: Icu_c_REF_1 */
            Icu_ChannelRamDataPtr->Edge = (Gtm_Tim_Edge_Cap)Activation;
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
            SafetyFlag &= Gtm_Icu_Hal_SetCaptureEdge(&Icu_Driver, Icu_ChannelRamDataPtr->Edge);

            /* [SWS_Icu_00139] Initialize channel status as idle */
            Icu_ChannelRamDataPtr->ChannelStatus = ICU_IDLE;
#if (ICU_SAFETY_ENABLE == STD_ON)
            if(TRUE != SafetyFlag)
            {
              (void)Det_ReportRuntimeError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SET_ACTIVATION_CONDITION_SID, ICU_E_SAFETY_CHECK_FAILED);
            }
#endif /* ICU_SAFETY_ENABLE == STD_ON */
        }
    }
} /* End of API Icu_SetActivationCondition */

/****************************************************************************************************
 *   Function Name           : Icu_DisableNotification
 *
 *   Service ID              : 0x06
 *
 *   Description             : This function disables the notification of a channel.
 *
 *   Parameters in           : Channel: Numeric identifier of the ICU channel
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : Sws_Icu_00198.[SWS_Icu_00042][SWS_Icu_00217]
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_DisableNotification
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;

#endif /*(ICU_DEV_ERROR_DETECT \== STD_ON */
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Icu_ChannelType CoreChIdx;
    Mcal_CoreType   CoreId;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_DISABLE_NOTIFICATION_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();

        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* [SWS_Icu_00050] [SWS_Icu_00310] Icu module functions for different channel numbers
         * shall be re-entrant*/
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* Check if the measurement mode is other than Time Stamp measurement */
        if ((ICU_MODE_SIGNAL_MEASUREMENT == Icu_ChannelRamDataPtr->MeasurementMode) ||
            (ICU_MODE_EDGE_COUNTER == Icu_ChannelRamDataPtr->MeasurementMode))
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_NOTIFICATION_SID, ICU_E_PARAM_CHANNEL);
        }
#if (ICU_ALREADY_ENABLEDISABLE_DET_CHECK == STD_ON)
        /* Check if the notification for the channel is already Disabled */
        else if (FALSE == Icu_ChannelRamDataPtr->NotificationEnable)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_NOTIFICATION_SID, ICU_E_ALREADY_DISABLED);
        }
#endif /* ICU_ALREADY_ENABLEDISABLE_DET_CHECK \== STD_ON */
        else
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
        {
            /* [SWS_Icu_00009] Store the disabled notification into RAM */
            Icu_ChannelRamDataPtr->NotificationEnable = FALSE;
        } /* End of (ReturnValue == E_OK */
    }
} /* End of API Icu_DisableNotification */

/****************************************************************************************************
 *   Function Name           : Icu_EnableNotification
 *
 *   Service ID              : 0x07
 *
 *   Description             : This API service will enable the Icu signal
 *                             notification of the requested channel.
 *
 *   Parameters in           : Channel: Numeric identifier of the ICU channel.
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : Sws_Icu_00199.[SWS_Icu_00021][SWS_Icu_00216]
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_EnableNotification
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;

#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType CoreId;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_ENABLE_NOTIFICATION_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00311 */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* Check if the measurement mode is other than Time Stamp measurement */
        if ((ICU_MODE_SIGNAL_MEASUREMENT == Icu_ChannelRamDataPtr->MeasurementMode) ||
            (ICU_MODE_EDGE_COUNTER == Icu_ChannelRamDataPtr->MeasurementMode))
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_NOTIFICATION_SID, ICU_E_PARAM_CHANNEL);
        }
#if (ICU_ALREADY_ENABLEDISABLE_DET_CHECK == STD_ON)
        /* NOTIFICATION ALREADY ENABLED */
        else if (TRUE == Icu_ChannelRamDataPtr->NotificationEnable)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_NOTIFICATION_SID, ICU_E_ALREADY_ENABLED);
        }
#endif /* ICU_ALREADY_ENABLEDISABLE_DET_CHECK \== STD_ON */
        /* Check if any DET was reported */
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON */
        {
            /* [SWS_Icu_00010] Store enabled notification into RAM */
            Icu_ChannelRamDataPtr->NotificationEnable = TRUE;
        }
    }
} /* End of API Icu_EnableNotification */

/* SWS_Icu_00122, SWS_Icu_00315 */
#if (ICU_GET_INPUT_STATE_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_GetInputState
 *
 *   Service ID              : 0x08
 *
 *   Description             : This function returns the status of the ICU input.
 *
 *   Parameters in           : Channel: Numeric identifier of the ICU channel.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Icu_InputStateType
 *                              ICU_ACTIVE: An activation edge has been detected
 *                              ICU_IDLE: No activation edge has been detected  *since the last call
 *                                 of Icu_GetInputState() or Icu_Init().
 *
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00200.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(Icu_InputStateType, ICU_CODE) Icu_GetInputState
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;

#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    /* Local variable to store the channel status */
    Icu_InputStateType ChannelState;
    Icu_ChannelType    CoreChIdx;
    uint32             NewValueFlg;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType  CoreId;
    Gtm_Icu_Driver Icu_Driver;
    /* [SWS_Icu_00049] Set the initial state to Idle
    [SWS_Icu_00313] Icu_GetInputState shall return Icu_InputStateType
    which will have value ICU_IDLE when no activation edge has been detected since
    the last call of Icu_GetInputState() or Icu_Init().*/
    ChannelState = ICU_IDLE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    ReturnValue = Icu_CheckDetErrors(Channel, ICU_GET_INPUT_STATE_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* [SWS_Icu_00312]  re-entrant.*/
        /* Get the Parameter set of channel */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00030]*/
        if((TRUE != Icu_ChannelRamDataPtr->WakeupIsEnabled) &&
           /* #Violation: Icu_c_REF_4 */
           (ICU_MODE_SLEEP == ICU_CURRENT_MODE(CoreId)))
        {
            (void)Det_ReportError(
              ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_STATE_SID, ICU_E_INVALID_MODE);
        }
        else if ((ICU_MODE_SIGNAL_EDGE_DETECT != Icu_ChannelRamDataPtr->MeasurementMode) &&
            (ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChannelRamDataPtr->MeasurementMode))
        {
            /* [SWS_Icu_00162] Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_INPUT_STATE_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else
#endif /* End of #if (ICU_DEV_ERROR_DETECT \== STD_ON */
        {
            /* [SWS_Icu_00031] If an activation edge has been detected the
             * functionIcu_GetInputState shall return ICU_ACTIVE for Edge Detection channels*/
            /* [SWS_Icu_00314]  For Signal Measurement a channel should be set to ICU_ACTIVE not
             * until this measurement has completed and the driver is able to  provide useful
             * information on the input signal*/
            ICU_ENTER_CRITICAL_SECTION(Icu_GetInputState);
            /* active edge has been detected in ohter API */
            if (ICU_ACTIVE == Icu_ChannelRamDataPtr->ChannelStatus)
            {
                ChannelState = ICU_ACTIVE;
            }
            else
            {
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
                /* Get interrupt flag */
                NewValueFlg = Gtm_Icu_Hal_GetInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_NEWVAL);
                if (1U == NewValueFlg)
                {
                    /* have active edge */
                    Gtm_Icu_Hal_ClearInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_NEWVAL);
                    ChannelState = ICU_ACTIVE;
                    /* #Violation: Icu_c_REF_4 */
                    Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput = TRUE;
                }
            }
            /* [SWS_Icu_00313] [SWS_Icu_00032] Store channel status as idle */
            Icu_ChannelRamDataPtr->ChannelStatus = ICU_IDLE;
            ICU_EXIT_CRITICAL_SECTION(Icu_GetInputState);
        } /* End of (ReturnValue \== E_OK) */
    }
    return ChannelState;
} /* End of API Icu_GetInputState */

#endif /* End of (ICU_GET_INPUT_STATE_API \== STD_ON) */
/* SWS_Icu_00098, SWS_Icu_00321 */
#if (ICU_TIMESTAMP_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_StartTimestamp
 *
 *   Service ID              : 0x09
 *
 *   Description             :This function starts the capturing of timer values on the edges.
 *
 *   Parameters in           : Channel: Numeric identifier of the ICU channel
 *                             BufferSize: Size of the external buffer (number of entries)
 *                             NotifyInterval: Notification interval (number of events). This
 *                                 parameter can not be checked in a reasonable way.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : BufferPtr: Pointer to the buffer-array where the timestamp values shall
 *                                 be placed.
 *
 *   Sync/Async              : ASynchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00201.[SWS_Icu_00063]
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_StartTimestamp
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel,
    /* #Violation: Icu_c_REF_6 */
    /* #Violation: Icu_c_REF_7 */
    P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr,
    uint16 BufferSize,
    uint16 NotifyInterval
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Set the DET return value */
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_START_TIMESTAMP_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* [SWS_Icu_00316] re-entrant.*/
        /* Get the Parameter set of channel */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00066]The function Icu_StartTimeStamp shall only be available in
        Measurement Mode ICU_MODE_TIMESTAMP */
        if (ICU_MODE_TIMESTAMP != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if pointer passed is Null */        
        else if (NULL_PTR == BufferPtr)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_POINTER);
        }
        /* [SWS_Icu_00108] Check if the channel buffer size is zero */        
        else if ((uint16)ICU_BUFFERSIZE_MIN_VAL == BufferSize)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_BUFFER_SIZE);
        }
        /* [SWS_Icu_00319] [SWS_Icu_00354]Check if the channel notifying interval less
         * than one */
        else if ((uint16)ICU_NOTIFY_INTERVAL_MIN_VAL > NotifyInterval)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_NOTIFY_INTERVAL);
        }
        /* wrong notifyInterval */
        else if ((NotifyInterval > BufferSize) && 
                 (ICU_LINEAR_BUFFER == Icu_ChannelRamDataPtr->ChannelData.Icu_TimeStampRam.BufferType))
        {
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_PARAM_NOTIFY_INTERVAL);
        }
        /* Check if any DET was reported */
        else
#endif /* End of #if (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            if (FALSE == Icu_ChannelRamDataPtr->IsChannelRunning)
            {
                /* Enter Critical Section */
                ICU_ENTER_CRITICAL_SECTION(Icu_StartTimestamp);
                /* [SWS_Icu_00317]shall start the capturing of timer values on the edges to
                 * an external buffer, at the beginning of the buffer.*/
                Icu_ChannelRamDataPtr->ChannelData.Icu_TimeStampRam.BufferPtr = BufferPtr;
                Icu_ChannelRamDataPtr->ChannelData.Icu_TimeStampRam.BufferSize = BufferSize;
                Icu_ChannelRamDataPtr->ChannelData.Icu_TimeStampRam.TimestampIndex = 
                    ICU_BUFFER_IDX_INIT_VAL;
                Icu_ChannelRamDataPtr->ChannelData.Icu_TimeStampRam.TimestampsCounter = 
                    (uint16)MCAL_ZERO;
                Icu_ChannelRamDataPtr->ChannelData.Icu_TimeStampRam.NotifyInterval = NotifyInterval;
                /* Initialize channel status as active */
                Icu_ChannelRamDataPtr->IsChannelRunning = TRUE;
                /* start timestamp */
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
                /* [SWS_Icu_00063] The function Icu_StartTimestamp shall start the capturing of
                  * timer values on the edges  activated by the service
                  * Icu_SetActivationCondition()*/
                SafetyFlag &= Gtm_Icu_Hal_StartCapture(
                    &Icu_Driver, (uint8)(GTM_TIM_IRQ_NEWVAL), Icu_ChannelRamDataPtr->Edge, FALSE);
                /* EXIT Critical Section */
                ICU_EXIT_CRITICAL_SECTION(Icu_StartTimestamp);
#if (ICU_SAFETY_ENABLE == STD_ON)
                if(TRUE != SafetyFlag)
                {
                  (void)Det_ReportRuntimeError(
                    ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_START_TIMESTAMP_SID, ICU_E_SAFETY_CHECK_FAILED);
                }
#endif /* ICU_SAFETY_ENABLE == STD_ON */
            }
        }
    }
#if (ICU_SAFETY_ENABLE == STD_OFF)
    /* #Violation: Icu_c_REF_4 */
    MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_OFF */
} /* End of API Icu_StartTimestamp */

#endif /* End of (ICU_TIMESTAMP_API \== STD_ON) */
/* SWS_Icu_00099, SWS_Icu_00323 */
#if (ICU_TIMESTAMP_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_StopTimestamp
 *
 *   Service ID              : 0x0A
 *
 *   Description             :This function stops the timestamp measurement of the given channel.
 *
 *   Parameters in           : Channel: Numeric identifier of the ICU channel
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00202.[SWS_Icu_00322]
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_StopTimestamp
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType     Channel
) 
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_STOP_TIMESTAMP_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00322 */
        /* Get the Parameter set of channel */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00165] Check if the channel is other than Time Stamp measurement */
        /* [SWS_Icu_00164] If development error detection is enabled the function
        Icu_StopTimestamp shall check the parameter Channel and shall raise
        development error ICU_E_PARAM_CHANNEL if Channel is invalid (invalid identifier or
        channel not configured for mode ICU_MODE_TIMESTAMP)*/
        if (ICU_MODE_TIMESTAMP != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            /* Check if the channel status is Idle */
            if (FALSE == Icu_ChannelRamDataPtr->IsChannelRunning)
            {
#if (ICU_DEV_ERROR_DETECT == STD_ON)
#if (ICU_DEV_RUNTIME_ERROR_DETECT == STD_ON)
                /* [SWS_Icu_00166] Set DET return value to E_NOT_OK */
                /* [SWS_Icu_00322] In production mode the function Icu_StopTimestamp shall not
                 * return an error when the Channel is not active (has not started or has already
                 * stopped*/
                /* Report Error to DET */
                (void)Det_ReportRuntimeError(
                    ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_NOT_STARTED);
#endif /* End of (ICU_DEV_RUNTIME_ERROR_DETECT \== STD_ON) */
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
            }
            else
            {
                /* Enter Critical Section */
                ICU_ENTER_CRITICAL_SECTION(Icu_StopTimestamp);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
                /* [SWS_Icu_00067] The function Icu_StopTimestamp shall stop the timestamp
                 * measurement of the given channel*/
                SafetyFlag &= Gtm_Icu_Hal_StopCapture(&Icu_Driver);
                SafetyFlag &= Gtm_Icu_Hal_SetInterrupt(&Icu_Driver, 0U); /* disable all */
                /* Initialize channel status as idle */
                Icu_ChannelRamDataPtr->IsChannelRunning = FALSE;
                /* Exit Critical Section */
                ICU_EXIT_CRITICAL_SECTION(Icu_StopTimestamp);

#if (ICU_SAFETY_ENABLE == STD_ON)
                if(TRUE != SafetyFlag)
                {
                    (void)Det_ReportRuntimeError(
                      ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_TIMESTAMP_SID, ICU_E_SAFETY_CHECK_FAILED);
                }
#else
                MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
            }
        } /* End of ReturnValue == E_OK */
    }
} /* End of API Icu_StopTimestamp */
#endif /* End of (ICU_TIMESTAMP_API \== STD_ON) */

/* SWS_Icu_00100, SWS_Icu_00325 */
#if (ICU_TIMESTAMP_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_GetTimestampIndex
 *
 *   Service ID              : 0x0B
 *
 *   Description             :This function reads the timestamp index of the given channel.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Icu_IndexType :Abstract return type to cover different microcontrollers
 *
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00203.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_IndexType   LusTimestampIndex;
    Icu_ChannelType CoreChIdx;
    Mcal_CoreType   CoreId;
    const Icu_ChannelRamDataType *Icu_ChannelRamDataPtr;
    /* SWS_Icu_00107 */
    LusTimestampIndex = ICU_BUFFER_IDX_INIT_VAL;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_GET_TIMESTAMP_INDEX_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00324 */
        /* Get the Parameter set of channel */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00170] Check if the measurement mode is other than Time Stamp measurement
        [SWS_Icu_00169] If development error detection is enabled the function
        Icu_GetTimestampIndex shall check the parameter Channel. If Channel is
        invalid (invalid identifier or channel not configured for mode
        ICU_MODE_TIMESTAMP), the function Icu_GetTimestampIndex shall raise
        development error ICU_E_PARAM_CHANNEL*/
        if (ICU_MODE_TIMESTAMP != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIMESTAMP_INDEX_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            ICU_ENTER_CRITICAL_SECTION(Icu_GetTimestampIndex);
            /* [SWS_Icu_00135] return 0 when channel is not started*/
            if (TRUE == Icu_ChannelRamDataPtr->IsChannelRunning)
            {
                /* [SWS_Icu_00071]
                 *  read the timestamp index of the given channel, which is the next to be
                 * written*/
                /* #Violation: Icu_c_REF_4 */
                LusTimestampIndex = 
                    Icu_ChannelRamDataPtr->ChannelData.Icu_TimeStampRam.TimestampIndex;
            }
            ICU_EXIT_CRITICAL_SECTION(Icu_GetTimestampIndex);

        }
    }
    return LusTimestampIndex;
} /* End of API Icu_GetTimestampIndex */
#endif /* End of (ICU_TIMESTAMP_API \== STD_ON) */

/* SWS_Icu_00101, SWS_Icu_00327 */
#if (ICU_EDGE_COUNT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_ResetEdgeCount
 *
 *   Service ID              : 0x0C
 *
 *   Description             :This function resets the value of the counted edges to zero.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00204.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_ResetEdgeCount
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelRamDataType *Icu_ChannelRamDataPtr;
    Icu_ChannelType    CoreChIdx;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Set the DET return value */
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_RESET_EDGE_COUNT_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);

        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00326]The function Icu_ResetEdgeCount shall be re-entrant*/
        /* Check if the measurement mode is other than Edge counting
        [SWS_Icu_00171] If development error detection is enabled the function
        Icu_ResetEdgeCount shall check the parameter Channel. If Channel is invalid
        (invalid identifier or channel not configured for mode ICU_MODE_EDGE_COUNTER),
        then Icu_ResetEdgeCount shall raise development error
        ICU_E_PARAM_CHANNEL*/
        if ((ICU_MODE_EDGE_COUNTER) != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_RESET_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else 
#endif /* End of #if (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            ICU_ENTER_CRITICAL_SECTION(Icu_ResetEdgeCount);
            /* [SWS_Icu_00072]  Invoke the Low Level Driver for resetting the edge count */
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
            SafetyFlag = Gtm_Icu_Hal_ResetEdgeCount(&Icu_Driver);
            Icu_ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IcuEdgeCount = 0U;
            ICU_EXIT_CRITICAL_SECTION(Icu_ResetEdgeCount);
#if (ICU_SAFETY_ENABLE == STD_ON)
            if(TRUE != SafetyFlag)
            {
                (void)Det_ReportRuntimeError(
                    ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_RESET_EDGE_COUNT_SID, ICU_E_SAFETY_CHECK_FAILED);
            }
#else
            MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
        } /* End of ReturnValue == E_OK */
    }
} /* End of API Icu_ResetEdgeCount */
#endif /* End of (ICU_EDGE_COUNT_API \== STD_ON) */

/* SWS_Icu_00102, SWS_Icu_00329 */
#if (ICU_EDGE_COUNT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_EnableEdgeCount
 *
 *   Service ID              : 0x0D
 *
 *   Description             :This function enables the counting of edges of the given channel.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00205.[SWS_Icu_00073]The function Icu_EnableEdgeCount shall
 *only count the configured1 edges (rising edge / falling edge / both edges
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_EnableEdgeCount
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_ENABLE_EDGE_COUNT_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00328 */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00074] be available for each ICU channel in Measurement Mode "EDGE COUNTER"
        [SWS_Icu_00172] If development error detection is enabled, the function
        Icu_EnableEdgeCount shall check the parameter Channel. If Channel is invalid
        (invalid identifier or channel not configured for mode ICU_MODE_EDGE_COUNTER),
        then the function Icu_EnableEdgeCount shall raise development error
        ICU_E_PARAM_CHANNEL*/
        if (ICU_MODE_EDGE_COUNTER != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else 
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            if (FALSE == Icu_ChannelRamDataPtr->IsChannelRunning)
            {
                /* [SWS_Icu_00078]  enable the counting of edges of the given channel.*/
                /* Enter Critical Section */
                ICU_ENTER_CRITICAL_SECTION(Icu_EnableEdgeCount);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
                SafetyFlag &= Gtm_Icu_Hal_StartCapture(
                    &Icu_Driver, (uint8)GTM_TIM_IRQ_CNTOVERFLOW, Icu_ChannelRamDataPtr->Edge, FALSE);

                /* Initialize channel status as active */
                Icu_ChannelRamDataPtr->IsChannelRunning = TRUE;
                /* EXIT Critical Section */
                ICU_EXIT_CRITICAL_SECTION(Icu_EnableEdgeCount);

#if (ICU_SAFETY_ENABLE == STD_ON)
                if(TRUE != SafetyFlag)
                {
                    (void)Det_ReportRuntimeError(
                      ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_COUNT_SID, ICU_E_SAFETY_CHECK_FAILED);
                }
#endif /* ICU_SAFETY_ENABLE == STD_ON */
            }      
        }
    }
} /* End of API Icu_EnableEdgeCount */
#endif /* End of (ICU_EDGE_COUNT_API \== STD_ON) */

/* SWS_Icu_00103, SWS_Icu_00331 */
#if (ICU_EDGE_COUNT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_DisableEdgeCount
 *
 *   Service ID              : 0x0E
 *
 *   Description             :This function disables the counting of edges of the given channel.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00206.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_DisableEdgeCount
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType     Channel
) 
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_DISABLE_EDGE_COUNT_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();

        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00330 */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        if (ICU_MODE_EDGE_COUNTER != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* [SWS_Icu_00173] If development error detection is enabled the function
            Icu_DisableEdgeCount shall check the parameter Channel. If Channel is
            invalid (invalid identifier or channel not configured for mode
            ICU_MODE_EDGE_COUNTER), the function Icu_DisableEdgeCount shall raise
            development error ICU_E_PARAM_CHANNEL. Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_COUNT_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else 
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            if (TRUE == Icu_ChannelRamDataPtr->IsChannelRunning)
            {
                /* Enter Critical Section */
                ICU_ENTER_CRITICAL_SECTION(Icu_DisableEdgeCount);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
                /* [SWS_Icu_00079] The function Icu_DisableEdgeCount shall disable the
                counting of edges of the given channel.*/
                SafetyFlag &= Gtm_Icu_Hal_StopCapture(&Icu_Driver);
                /* Initialize the channel status as idle */
                Icu_ChannelRamDataPtr->IsChannelRunning = FALSE;
                /* Exit Critical Section */
                ICU_EXIT_CRITICAL_SECTION(Icu_DisableEdgeCount);
#if (ICU_SAFETY_ENABLE == STD_ON)
                if(TRUE != SafetyFlag)
                {
                    (void)Det_ReportRuntimeError(
                      ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_COUNT_SID, ICU_E_SAFETY_CHECK_FAILED);
                }
#endif /* ICU_SAFETY_ENABLE == STD_ON */
            }
        }
    }
} /* End of API Icu_DisableEdgeCount */
#endif /* End of (ICU_EDGE_COUNT_API \== STD_ON) */

/* SWS_Icu_00369, SWS_Icu_00370 */
#if (ICU_EDGE_DETECT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_EnableEdgeDetection
 *
 *   Service ID              : 0x16
 *
 *   Description             :This function enables / re-enables the detection of edges of the given
 *channel.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00364.[SWS_Icu_00366]
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_EnableEdgeDetection
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_ENABLE_EDGE_DETECTION_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00368 */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00367] Check if the measurement mode is other than Edge Detection
        [SWS_Icu_00371] If development error detection is enabled; the function
        Icu_EnableEdgeDetection shall check the parameter Channel. If Channel is
        invalid (invalid identifier or channel not configured for mode
        ICU_MODE_SIGNAL_EDGE_DETECT), then the function
        Icu_EnableEdgeDetection shall raise development error
        ICU_E_PARAM_CHANNEL*/
        if (ICU_MODE_SIGNAL_EDGE_DETECT != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_ENABLE_EDGE_DETECTION_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else 
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            /* [SWS_Icu_00365]shall enable the detection of edges for the given channel*/
            /* Enter Critical Section */
            ICU_ENTER_CRITICAL_SECTION(Icu_EnableEdgeDetection);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
            SafetyFlag &= Gtm_Icu_Hal_StartEdgeDetect(
                &Icu_Driver, (uint8)(GTM_TIM_IRQ_NEWVAL), Icu_ChannelRamDataPtr->Edge, 1U);

            /* Initialize channel status as active */
            Icu_ChannelRamDataPtr->IsChannelRunning = TRUE;
            /* EXIT Critical Section */
            ICU_EXIT_CRITICAL_SECTION(Icu_EnableEdgeDetection);
#if (ICU_SAFETY_ENABLE == STD_ON)
            if(TRUE != SafetyFlag)
            {
                (void)Det_ReportRuntimeError(ICU_MODULE_ID, 
                                            ICU_INSTANCE_ID, 
                                            ICU_ENABLE_EDGE_DETECTION_SID, 
                                            ICU_E_SAFETY_CHECK_FAILED);
            }
#else
            MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
        }
    }
} /* End of API Icu_EnableEdgeDetection */

/****************************************************************************************************
 *   Function Name           : Icu_EnableMultiEdgeDetection
 *
 *   Service ID              : 0x31
 *
 *   Description             :This API service enables the detection of MultiEdges of the
 *                            requested channel.
 *
 *   Parameters in           : Channel: Numeric identifier of the ICU channel
 *                             EdgeCount: Number of edges to detect
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_EnableMultiEdgeDetection
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel, 
    uint32 EdgeCount
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType     CoreId;
    Gtm_Icu_Driver    Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_ENABLE_MULTI_EDGE_DETECTION_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        if (0U == EdgeCount)
        {
            (void)Det_ReportError(
                ICU_MODULE_ID,
                ICU_INSTANCE_ID,
                ICU_ENABLE_MULTI_EDGE_DETECTION_SID,
                ICU_E_ERROR_EDGE_NUMBER);
        }
        /* Check if the measurement mode is other than Edge Detection */
        else if (ICU_MODE_SIGNAL_EDGE_DETECT != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID,
                ICU_INSTANCE_ID,
                ICU_ENABLE_MULTI_EDGE_DETECTION_SID,
                ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {

            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId,CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId,CoreChIdx);
            /* Enter Critical Section */
            ICU_ENTER_CRITICAL_SECTION(Icu_EnableMultiEdgeDetection);
            /* Initialize channel status as active */
            Icu_ChannelRamDataPtr->IsChannelRunning = TRUE;

            SafetyFlag &= Gtm_Icu_Hal_StartEdgeDetect(
                &Icu_Driver, (uint8)(GTM_TIM_IRQ_NEWVAL), Icu_ChannelRamDataPtr->Edge, EdgeCount);
            /* EXIT Critical Section */
            ICU_EXIT_CRITICAL_SECTION(Icu_EnableMultiEdgeDetection);
#if (ICU_SAFETY_ENABLE == STD_ON)
            if(TRUE != SafetyFlag)
            {
                (void)Det_ReportRuntimeError(ICU_MODULE_ID, 
                                            ICU_INSTANCE_ID, 
                                            ICU_ENABLE_MULTI_EDGE_DETECTION_SID, 
                                            ICU_E_SAFETY_CHECK_FAILED);
            }
#else
            MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
        }
    }
}
#endif /* #if (ICU_EDGE_DETECT_API \== STD_ON) */

/* SWS_Icu_00374, SWS_Icu_00375 */
#if (ICU_EDGE_DETECT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_DisableEdgeDetection
 *
 *   Service ID              : 0x17
 *
 *   Description             :This function disables the detection of edges of the given channel.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00377.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_DisableEdgeDetection
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_4 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_DISABLE_EDGE_DETECTION_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00373 */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* Check if the measurement mode is other than Edge Detection
        [SWS_Icu_00376] If development error detection is enabled the function
        Icu_DisableEdgeDetection shall check the parameter Channel. If Channel is
        invalid (invalid identifier or channel not configured for mode
        ICU_MODE_SIGNAL_EDGE_DETECT), the function Icu_DisableEdgeDetection
        shall raise development error ICU_E_PARAM_CHANNEL*/
        if (ICU_MODE_SIGNAL_EDGE_DETECT != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_DISABLE_EDGE_DETECTION_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            if (TRUE == Icu_ChannelRamDataPtr->IsChannelRunning)
            {
                /* [SWS_Icu_00372]The function Icu_DisableEdgeDetection shall disable the
                detection of edges of the given channel*/
                /* Enter Critical Section */
                ICU_ENTER_CRITICAL_SECTION(Icu_DisableEdgeDetection);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
                SafetyFlag &= Gtm_Icu_Hal_StopCapture(&Icu_Driver);

                /* Initialize the channel status as idle */
                Icu_ChannelRamDataPtr->IsChannelRunning = FALSE;
                /* Exit Critical Section */
                ICU_EXIT_CRITICAL_SECTION(Icu_DisableEdgeDetection);
#if (ICU_SAFETY_ENABLE == STD_ON)
                if(TRUE != SafetyFlag)
                {
                    (void)Det_ReportRuntimeError(ICU_MODULE_ID, 
                                                ICU_INSTANCE_ID, 
                                                ICU_DISABLE_EDGE_DETECTION_SID, 
                                                ICU_E_SAFETY_CHECK_FAILED);
                }
#else
                MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
            }

        } /* End of (ReturnValue \== E_OK) */
    }
} /* End of API Icu_DisableEdgeDetection */
#endif /* #if (ICU_EDGE_DETECT_API \== STD_ON) */

/* SWS_Icu_00104, SWS_Icu_00333 */
#if (ICU_EDGE_COUNT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_GetEdgeNumbers
 *
 *   Service ID              : 0x0F
 *
 *   Description             :This function reads the number of counted edges.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Icu_EdgeNumberType :Abstract return type to cover different
 *microcontrollers.
 *
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00207.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    const Icu_ChannelRamDataType *Icu_ChannelRamDataPtr;
    Icu_ChannelType CoreChIdx;
    Mcal_CoreType      CoreId;
    uint32             OldEdgeNumsHighWords;
    uint32             NewEdgeNumsHighWords;
    uint32             EdgeNums;
    uint32             EdgeNumsLowWords;
    Gtm_Icu_Driver     Icu_Driver;
    /* [SWS_Icu_00175] return 0 if error is detected */
    EdgeNums = 0U;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_GET_EDGE_NUMBERS_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* Get the Parameter set of channel */        
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* SWS_Icu_00332 */
        /* Check if the measurement mode is other than Edge Detection
        [SWS_Icu_00174] If development error detection is enabled, the function
        Icu_GetEdgeNumbers shall check the parameter Channel. If Channel is invalid
        (invalid identifier or channel not configured for mode ICU_MODE_EDGE_COUNTER),
        the function Icu_GetEdgeNumbers shall raise development error
        ICU_E_PARAM_CHANNEL. */
        if (ICU_MODE_EDGE_COUNTER != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_EDGE_NUMBERS_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            OldEdgeNumsHighWords =
                Icu_ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IcuEdgeCount;
            EdgeNumsLowWords = Gtm_Icu_Hal_GetEdgeNums(&Icu_Driver);
            /* #Violation: Icu_c_REF_4 */
            NewEdgeNumsHighWords =
                Icu_ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IcuEdgeCount;
            /* changed by ISR */
            if (OldEdgeNumsHighWords != NewEdgeNumsHighWords)
            {
                EdgeNumsLowWords = Gtm_Icu_Hal_GetEdgeNums(&Icu_Driver);
            }
            EdgeNums = NewEdgeNumsHighWords + EdgeNumsLowWords;

        } /* End of (ReturnValue \== E_OK) */
    }
    /* [SWS_Icu_00080]read the number of counted edges after the last call of Icu_ResetEdgeCount(*/
    return EdgeNums;
} /* End of API Icu_GetEdgeNumbers */
#endif /* End of (ICU_EDGE_COUNT_API \== STD_ON) */

/* SWS_Icu_00142, SWS_Icu_00335 */
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_StartSignalMeasurement
 *
 *   Service ID              : 0x13
 *
 *   Description             :This function starts the measurement of signals.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : ASynchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None
 *
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00208.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_StartSignalMeasurement
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    Gtm_Tim_Edge_Cap   StartEdge;
    Gtm_SignalState    CurrentLevel;
    boolean            MeasureImmediate;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_START_SIGNAL_MEASUREMENT_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* [SWS_Icu_00334] shall be reentrant*/
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
        /* #Violation: Icu_c_REF_4 */
        Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId,CoreChIdx);
        /* #Violation: Icu_c_REF_4 */
        Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId,CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00176][SWS_Icu_00141] Check if the measurement mode is other than Signal
         * measurement */
        if (ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID,
                ICU_INSTANCE_ID,
                ICU_START_SIGNAL_MEASUREMENT_SID,
                ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            if (FALSE == Icu_ChannelRamDataPtr->IsChannelRunning)
            {
                /* Enter Critical Section */
                ICU_ENTER_CRITICAL_SECTION(Icu_StartSignalMeasurement);
                /* [SWS_Icu_00146] Initialize channel status as idle */
                Icu_ChannelRamDataPtr->ChannelStatus = ICU_IDLE;
                Icu_ChannelRamDataPtr->IsChannelRunning = TRUE;
                StartEdge = Icu_ChannelRamDataPtr->Edge;
                /* #Violation: Icu_c_REF_4 */
                Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput = FALSE;
                /* #Violation: Icu_c_REF_4 */
                Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.IrqType =
                    ICU_MEASURE_IRQ_CNTOVFL;
                /*get current level of ICU channel*/
                CurrentLevel = Gtm_Icu_Hal_GetSignalLevel(&Icu_Driver);
                MeasureImmediate = Icu_StartSignalCheck(CurrentLevel, 
                            Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.MeasureProperty);

                /* #Violation: Icu_c_REF_1 */
                if ((Gtm_Tim_Edge_Cap)ICU_BOTH_EDGES == StartEdge)
                {
                    /* Read the actual input signal value of the channel ,and start at next edge*/
                    if (GTM_SIGNALSTATE_HIGH == CurrentLevel)
                    {
                        /* #Violation: Icu_c_REF_1 */
                        StartEdge = (Gtm_Tim_Edge_Cap)ICU_FALLING_EDGE;
                    }
                    else
                    {
                        /* #Violation: Icu_c_REF_1 */
                        StartEdge = (Gtm_Tim_Edge_Cap)ICU_RISING_EDGE;
                    }
                }

                SafetyFlag &= Gtm_Icu_Hal_StartCapture(
                    &Icu_Driver, (uint8)GTM_TIM_IRQ_CNTOVERFLOW, StartEdge, MeasureImmediate);

                /* Exit Critical Section */
                ICU_EXIT_CRITICAL_SECTION(Icu_StartSignalMeasurement);
#if (ICU_SAFETY_ENABLE == STD_ON)
                if(TRUE != SafetyFlag)
                {
                    (void)Det_ReportRuntimeError(ICU_MODULE_ID, 
                                                ICU_INSTANCE_ID, 
                                                ICU_START_SIGNAL_MEASUREMENT_SID, 
                                                ICU_E_SAFETY_CHECK_FAILED);
                }
#endif /* ICU_SAFETY_ENABLE == STD_ON */
            }
        } /* End of (ReturnValue \== E_OK) */
    }
#if (ICU_SAFETY_ENABLE == STD_OFF)
    MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_OFF */
} /* End of API Icu_StartSignalMeasurement */
#endif /* End of (ICU_SIGNAL_MEASUREMENT_API \== STD_ON) */

/* SWS_Icu_00145, SWS_Icu_00337 */
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_StopSignalMeasurement
 *
 *   Service ID              : 0x14
 *
 *   Description             :This API stops the measurement of signals of the
 *                            given channel.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
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
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00209.
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_StopSignalMeasurement
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;

#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType      CoreId;
    Gtm_Icu_Driver     Icu_Driver;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    ReturnValue = Icu_CheckDetErrors(Channel, ICU_STOP_SIGNAL_MEASUREMENT_SID);
    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* [SWS_Icu_00336] Reentrant */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00177][SWS_Icu_00144] Check if the measurement mode is other than Signal
         * measurement */
        if (ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_STOP_SIGNAL_MEASUREMENT_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else 
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            if (TRUE == Icu_ChannelRamDataPtr->IsChannelRunning)
            {
                /* Enter Critical Section */
                ICU_ENTER_CRITICAL_SECTION(Icu_StopSignalMeasurement);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
                /* #Violation: Icu_c_REF_4 */
                Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
                /* [SWS_Icu_00143] stop the measurement of signals of the given channe */
                SafetyFlag &= Gtm_Icu_Hal_StopCapture(&Icu_Driver);
                /* Initialize the channel status as idle */
                Icu_ChannelRamDataPtr->IsChannelRunning = FALSE;
                /* Exit Critical Section */
                ICU_EXIT_CRITICAL_SECTION(Icu_StopSignalMeasurement);
#if (ICU_SAFETY_ENABLE == STD_ON)
                if(TRUE != SafetyFlag)
                {
                    (void)Det_ReportRuntimeError(ICU_MODULE_ID, 
                                                ICU_INSTANCE_ID, 
                                                ICU_STOP_SIGNAL_MEASUREMENT_SID, 
                                                ICU_E_SAFETY_CHECK_FAILED);
                }
#endif /* ICU_SAFETY_ENABLE == STD_ON */
            }
        } /* End of (ReturnValue \== E_OK) */
    }
#if (ICU_SAFETY_ENABLE == STD_OFF)
    MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_OFF */
} /* End of API Icu_StopSignalMeasurement */
#endif /* End of (ICU_SIGNAL_MEASUREMENT_API \== STD_ON) */

/* SWS_Icu_00105, SWS_Icu_00341 */
#if (ICU_GET_TIME_ELAPSED_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_GetTimeElapsed
 *
 *   Service ID              : 0x10
 *
 *   Description             :This function reads the elapsed Signal Low Time for the given channel.
 *
 *   Parameters in           : Numeric identifier of the ICU channel
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Icu_ValueType
 *
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Icu_00210.[SWS_Icu_00136] [SWS_Icu_00339][SWS_Icu_00340]
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;

    Icu_ValueType   SignalTime;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType  CoreId;
    Gtm_Icu_Driver Icu_Driver;
    uint32         NewValueFlg;
    /* SWS_Icu_00179 */
    SignalTime = MCAL_ZERO;
#if (ICU_DEV_ERROR_DETECT == STD_ON)

    ReturnValue = Icu_CheckDetErrors(Channel, ICU_GET_TIME_ELAPSED_SID);
    if (E_OK == ReturnValue)

#endif /* ICU_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();
        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00338 */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);

#if (ICU_DEV_ERROR_DETECT == STD_ON)

        /* Check if the measurement mode is other than Signal measurement 
           SWS_Icu_00178 */
        if (ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_TIME_ELAPSED_SID, ICU_E_PARAM_CHANNEL);
        }
        /* Check if any DET was reported */
        else 
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId, CoreChIdx);
            /* #Violation: Icu_c_REF_4 */
            Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId, CoreChIdx);
            /* [SWS_Icu_00081] The function Icu_GetTimeElapsed shall read the elapsed Signal Low
            Time for the given channel that is configured in Measurement Mode
            Measurement, Signal Low Time. The elapsed time is measured between a falling edge
            and the consecutive rising edge of the channel*/
            /* [SWS_Icu_00082] The function Icu_GetTimeElapsed shall read the elapsed Signal High
            Time for the given channel that is configured in Measurement Mode, Signal High Time.
            The elapsed time is measured between a rising edge
            and the consecutive falling edge of the channel.*/
            /* [SWS_Icu_00083] The function Icu_GetTimeElapsed shall read the elapsed
            Signal Period Time for the given channel that is configured in Measurement Mode
            ignal Measurement, Signal Period Time. The elapsed time is measured between
            consecutive rising (or falling) edges of the channel. The period start edge is
            configurable*/
            NewValueFlg = Gtm_Icu_Hal_GetInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_NEWVAL);

            if (1U == NewValueFlg)
            {
                /* new result has been detected */
                Gtm_Icu_Hal_ClearInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_NEWVAL);
                ICU_ENTER_CRITICAL_SECTION(Icu_GetTimeElapsed);
                Icu_ChannelRamDataPtr->ChannelStatus = ICU_ACTIVE;
                Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput = FALSE;
                ICU_EXIT_CRITICAL_SECTION(Icu_GetTimeElapsed);
                SignalTime = Gtm_Icu_Hal_GetTimeElapsed(&Icu_Driver);
            }
            /* new result has been detected by other API*/
            else if (TRUE == Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput)
            {
                ICU_ENTER_CRITICAL_SECTION(Icu_GetTimeElapsed);
                Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput = FALSE;
                Icu_ChannelRamDataPtr->ChannelStatus = ICU_ACTIVE;
                ICU_EXIT_CRITICAL_SECTION(Icu_GetTimeElapsed);
                SignalTime = Gtm_Icu_Hal_GetTimeElapsed(&Icu_Driver);
            }
            else
            /* #Violation: Icu_c_REF_10 */
            {
                /* Do nothing */
            }
        }
    }
    return SignalTime;

} /* End of API Icu_GetTimeElapsed */
#endif /* End of (ICU_GET_TIME_ELAPSED_API \== STD_ON) */

/* SWS_Icu_00106, SWS_Icu_00345 */
#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_GetDutyCycleValues
 *
 *   Service ID              : 0x11
 *
 *   Description             :This function reads the coherent active time and period time for the
                               given ICU Channel..
 *
 *   Parameters in           : Numeric identifier of the ICU channel
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : Icu_DutyCycleType: Pointer to a buffer where the results (high time and
                               period time) shall be placed..
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : void
 *
 *   Preconditions           : The Icu Driver must be initialized.
 *
 *   AUTOSAR_Requirement     : [SWS_Icu_00211].
 *
 * [SWS_Icu_00137][SWS_Icu_00343][SWS_Icu_00344]:There are differences:
 *  1 A complete cycle of waveform is required to complete the acquisition.
 *  2. A cycle is in the process of collection, and reading it will return the complete and collected
 *      data from the previous cycle.
 *
 *
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_GetDutyCycleValues
(
    /* #Violation: Icu_c_REF_8 */
    Icu_ChannelType Channel, 
    /* #Violation: Icu_c_REF_7 */
    P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_DATA) DutyCycleValues
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ReturnValue;
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    Icu_ChannelType CoreChIdx;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) Icu_ChannelRamDataPtr;
    Mcal_CoreType  CoreId;
    Gtm_Icu_Driver Icu_Driver;
    uint32         NewValueFlg;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* [SWS_Icu_00181]Check if pointer passed is Null */
    if (NULL_PTR == DutyCycleValues)
    {
        /* Report Error to DET */
        (void)Det_ReportError(
            ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_PARAM_POINTER);
        ReturnValue = E_NOT_OK;
    }
    else
    {
        ReturnValue = Icu_CheckDetErrors(Channel, ICU_GET_DUTY_CYCLE_VALUES_SID);
    }

    if (E_OK == ReturnValue)
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON) */
    {
        DutyCycleValues->ActiveTime = MCAL_ZERO;
        DutyCycleValues->PeriodTime = MCAL_ZERO;
        /* #Violation: Icu_c_REF_4 */
        CoreId = Mcal_GetCoreId();

        /* #Violation: Icu_c_REF_4 */
        CoreChIdx = ICU_GET_CORE_CH_IDX(Channel);
        /* SWS_Icu_00342 */
        Icu_ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
        /* #Violation: Icu_c_REF_4 */
        Icu_Driver.channel = ICU_GET_HW_CH_INDEX(CoreId,CoreChIdx);
        /* #Violation: Icu_c_REF_4 */
        Icu_Driver.tim = ICU_GET_HW_INDEX(CoreId,CoreChIdx);

#if (ICU_DEV_ERROR_DETECT == STD_ON)
        /* [SWS_Icu_00180] If development error detection is enabled: the function
        Icu_GetDutyCycleValues shall check the parameter Channel. If Channel is
        invalid (invalid identifier or channel not configured for mode
        ICU_MODE_SIGNAL_MEASUREMENT, Duty Cycle Values), the function
        Icu_GetDutyCycleValues shall raise development error
        ICU_E_PARAM_CHANNEL.*/
        if (ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChannelRamDataPtr->MeasurementMode)
        {
            /* Report Error to DET */
            (void)Det_ReportError(
                ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_DUTY_CYCLE_VALUES_SID, ICU_E_PARAM_CHANNEL);
        }
        else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */
        {
#if (ICU_DEV_ERROR_DETECT == STD_ON)
            if (ICU_MEASUREMENT_PRO_DUTY_CYCLE != 
                Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.MeasureProperty)
            {
                /* Report Error to DET */
                (void)Det_ReportError(
                    ICU_MODULE_ID,
                    ICU_INSTANCE_ID,
                    ICU_GET_DUTY_CYCLE_VALUES_SID,
                    ICU_E_PARAM_CHANNEL);
            }
            else
#endif /* End of (ICU_DEV_ERROR_DETECT \== STD_ON) */ 
            {
                /* [SWS_Icu_00084] The function Icu_GetDutyCycleValues shall read the coherent
                    * active time and period time for the given ICU Channel, if it is configured in
                    * Measurement Mode signal Measurement, Duty Cycle Value */
                NewValueFlg = Gtm_Icu_Hal_GetInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_NEWVAL);
                /* new result has been detected */
                if (1U == NewValueFlg)
                {
                    Gtm_Icu_Hal_ClearInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_NEWVAL);
                    ICU_ENTER_CRITICAL_SECTION(Icu_GetDutyCycleValues);
                    Icu_ChannelRamDataPtr->ChannelStatus = ICU_ACTIVE;
                    Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput = FALSE;
                    ICU_EXIT_CRITICAL_SECTION(Icu_GetDutyCycleValues);
                    Gtm_Icu_Hal_GetDutyCycleValues(&Icu_Driver, DutyCycleValues);
                }
                /* new result has been detected by other API */
                else if (TRUE == Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput)
                {
                    ICU_ENTER_CRITICAL_SECTION(Icu_GetDutyCycleValues);
                    Icu_ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam.HasValidInput = FALSE;
                    Icu_ChannelRamDataPtr->ChannelStatus = ICU_ACTIVE;
                    ICU_EXIT_CRITICAL_SECTION(Icu_GetDutyCycleValues);
                    Gtm_Icu_Hal_GetDutyCycleValues(&Icu_Driver, DutyCycleValues);
                }
                else
                /* #Violation: Icu_c_REF_10 */
                {
                    /*Do nothing */
                }
            }
        }
    }
} /* End of API Icu_GetDutyCycleValues */
#endif /* End of (ICU_GET_DUTY_CYCLE_VALUES_API \== STD_ON) */

#if (ICU_GET_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_GetVersionInfo
 *
 *   Service ID              : 0x12
 *
 *   Description             :This function returns the version information of this module.
 *
 *   Parameters in           : versioninfo:Pointer to where to store the version information of this
 *                             module.
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
 *   AUTOSAR_Requirement     : [SWS_Icu_00212].
 ****************************************************************************************************/
/* #Violation: Icu_c_REF_13 */
FUNC(void, ICU_CODE) Icu_GetVersionInfo
(
    /* #Violation: Icu_c_REF_7 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_APPL_DATA) versioninfo
)
{
#if (ICU_DEV_ERROR_DETECT == STD_ON)
    /* [SWS_Icu_00356] Check if parameter passed is equal to Null pointer */
    if (NULL_PTR == versioninfo)
    {
        /* Report Error to DET */
        (void)Det_ReportError(
            ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_GET_VERSION_INFO_SID, ICU_E_PARAM_VINFO);
    }
    else
#endif /* ICU_DEV_ERROR_DETECT \== STD_ON) */
    {
        versioninfo->vendorID = ICU_VENDOR_ID;
        versioninfo->moduleID = ICU_MODULE_ID;
        versioninfo->sw_major_version = ICU_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = ICU_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = ICU_SW_PATCH_VERSION;
    }
}
#endif /* ICU_GET_VERSION_INFO_API == STD_ON */

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : SignalMeasureOverflowProc
 *
 *   Service ID              : None
 *
 *   Description             : This function confirm that does overflow  happened in valid edge.
 *
 *   Parameters in           :Icu_DriverPtr: Index of timxchy.
 *                            ChannelRamDataPtr: Ram Parameter of ch
 *                            IntFlg: New Value Isr Flg
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
static void Icu_SignalMeasureOverflowProc
(
    const Gtm_Icu_Driver *const Icu_DriverPtr,
    /* #Violation: Icu_c_REF_6 */
    CONSTP2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) ChannelRamDataPtr,
    uint32 IntFlg
)
{
    uint32            OverFlowElapsedTime;
    uint32            ElapsedTime;
    Gtm_SignalState   ActiveLevel;
    Gtm_SignalState   HwActiveLevel;
    boolean           SafetyFlag;
    Icu_PwmMeasureRamType *ChannelDataPtr;

    /* Point to signal measurement data ram */
    ChannelDataPtr = &ChannelRamDataPtr->ChannelData.Icu_PwmMeasureRam;

    SafetyFlag = TRUE;
    if (TRUE == ChannelRamDataPtr->IsChannelRunning)
    {
        /* the Irq type is Cnt overflow */
        if (ICU_MEASURE_IRQ_CNTOVFL == ChannelDataPtr->IrqType)
        {   /* new result has been detected */
            if (0U != (IntFlg & ICU_IRQ_NEW_VALUE_MASK))
            {
                ChannelDataPtr->HasValidInput = TRUE;
            }

            if ((ICU_MEASUREMENT_PRO_LOW_TIME == ChannelDataPtr->MeasureProperty) ||
                (ICU_MEASUREMENT_PRO_HIGH_TIME == ChannelDataPtr->MeasureProperty))
            {
                OverFlowElapsedTime = Gtm_Icu_Hal_GetOverFlowElapsedTime(Icu_DriverPtr);
                /* Get the time from the edge to the current time*/
                ElapsedTime = Gtm_Icu_Hal_GetTimeElapsed(Icu_DriverPtr);
                if (ICU_MEASUREMENT_PRO_LOW_TIME == ChannelDataPtr->MeasureProperty)
                {
                    ActiveLevel = GTM_SIGNALSTATE_LOW;
                }
                else
                {
                    ActiveLevel = GTM_SIGNALSTATE_HIGH;
                }

                HwActiveLevel = Gtm_Icu_Hal_GetSignalLevel(Icu_DriverPtr);

                /* The current level is not the target level that needs to be tested */
                if (HwActiveLevel != ActiveLevel)
                {
                    if (ElapsedTime < ChannelDataPtr->IsrOverflowThreshold)
                    {
                        /* overflow ISR executing on active phase */
                        ChannelDataPtr->HasValidInput = FALSE;
                        ChannelRamDataPtr->ChannelStatus = ICU_IDLE;
                    }
                    else
                    /* #Violation: Icu_c_REF_10 */
                    {
                        /* overflow ISR executing on inactive phase */
                        /* Do Nothing */
                    }
                }
                /* The current level is the target level that needs to be tested */
                else
                {
                    /* overflow ISR executing on active phase */
                    if (OverFlowElapsedTime >= ChannelDataPtr->IsrOverflowThreshold)
                    {
                        /* Overflow is due to active phase. */
                        /* Set a flag to identify that the active phase is not valid */
                        ChannelDataPtr->IsOverFlowDetect = TRUE;
                    }
                    ChannelDataPtr->IrqType = ICU_MEASURE_IRQ_NEW_VALUE;
                    /* enable a new value interrupt to set the result as invalid */
                    SafetyFlag &= Gtm_Icu_Hal_SetInterrupt(Icu_DriverPtr, (uint8)(GTM_TIM_IRQ_NEWVAL));
                }
            }
            else
            {
                /* reset the counter overflow interrupt enable and set newval interrupt enable */
                 ChannelDataPtr->IrqType = ICU_MEASURE_IRQ_NEW_VALUE;
                SafetyFlag &= Gtm_Icu_Hal_SetInterrupt(Icu_DriverPtr, (uint8)GTM_TIM_IRQ_NEWVAL);
            }
        }
        else
        {
            if ((ICU_MEASUREMENT_PRO_LOW_TIME ==  ChannelDataPtr->MeasureProperty) ||
                (ICU_MEASUREMENT_PRO_HIGH_TIME ==  ChannelDataPtr->MeasureProperty))
            {
                /* Cnt overflow is occoured */
                if ((TRUE ==  ChannelDataPtr->IsOverFlowDetect) ||
                    (0U != (IntFlg & ICU_IRQ_CNTOVFL_MASK)))
                {
                     ChannelDataPtr->IsOverFlowDetect = FALSE;
                    ChannelRamDataPtr->ChannelStatus = ICU_IDLE;
                     ChannelDataPtr->HasValidInput = FALSE;
                }
            }
            else
            {
                ChannelRamDataPtr->ChannelStatus = ICU_IDLE;
                 ChannelDataPtr->HasValidInput = FALSE;
            }
             ChannelDataPtr->IrqType = ICU_MEASURE_IRQ_CNTOVFL;
            SafetyFlag &= Gtm_Icu_Hal_SetInterrupt(Icu_DriverPtr, (uint8)GTM_TIM_IRQ_CNTOVERFLOW);
        }
#if (ICU_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            (void)Det_ReportRuntimeError(ICU_MODULE_ID, 
                                        ICU_INSTANCE_ID, 
                                        ICU_SID_ISR, 
                                        ICU_E_SAFETY_CHECK_FAILED);
        }
#endif /* ICU_SAFETY_ENABLE == STD_ON */
    }
#if (ICU_SAFETY_ENABLE == STD_OFF)
    MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
}
#endif /* ICU_SIGNAL_MEASUREMENT_API \== STD_ON) */
/* [SWS_Icu_00218] The Icu module notification
 * Icu_TimestampNotification_<Channel> depends on pre-processor switch IcuTimestampApi*/

#if (ICU_TIMESTAMP_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Icu_TimeStampIsrProc
 *
 *   Service ID              : None
 *
 *   Description             : This function do time stamp process.
 *
 *   Parameters in           :Icu_DriverPtr: Index of timxchy.
                              ChannelRamDataPtr: Ram Parameter of ch
                              SingleChannelConfigPtr: Channel config variable
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
static void Icu_TimeStampIsrProc
(
    const Gtm_Icu_Driver *const Icu_DriverPtr,
    /* #Violation: Icu_c_REF_6 */
    CONSTP2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) ChannelRamDataPtr,
    CONSTP2CONST(Icu_ChnConfigType, AUTOMATIC, ICU_CONFIG_DATA) SingleChannelConfigPtr
)
{
    uint32 *BufferPtr;
    uint16  IndexOfTimeStamp;
    uint16 TimestampsCounter;
    boolean SafetyFlag;
    Icu_TimestampRamType *ChannelDataPtr;
    /* Point to timestamp data ram */
    ChannelDataPtr = &ChannelRamDataPtr->ChannelData.Icu_TimeStampRam;

    SafetyFlag = TRUE;
    /* Cannot call ICU API in higher priority context than ISR */
    if (TRUE == ChannelRamDataPtr->IsChannelRunning)
    {
        IndexOfTimeStamp = ChannelDataPtr->TimestampIndex;
        BufferPtr = ChannelDataPtr->BufferPtr;
        /* Check if timestamp capturing reached end of the buffer */
        if ((IndexOfTimeStamp) < (ChannelDataPtr->BufferSize))
        {
            /* Update the buffer pointer with current timestamp */
            BufferPtr[IndexOfTimeStamp] = Gtm_Icu_Hal_GetTimeStamp(Icu_DriverPtr);
            IndexOfTimeStamp++;
            /* Check whether the timestamp index has reached the end of buffer */
            if (IndexOfTimeStamp >= (ChannelDataPtr->BufferSize))
            {
                /*  Check if buffer is configured as circular */
                if (ICU_CIRCULAR_BUFFER == ChannelDataPtr->BufferType)
                {
                    /* [SWS_Icu_00064] Reset buffer pointer and index */
                    IndexOfTimeStamp = ICU_BUFFER_IDX_INIT_VAL;
                }
                /* [SWS_Icu_00065]  linear process */
                else
                {
                    SafetyFlag &= Gtm_Icu_Hal_StopCapture(Icu_DriverPtr);
                    SafetyFlag &= Gtm_Icu_Hal_SetInterrupt(Icu_DriverPtr, 0U);
                    ChannelRamDataPtr->IsChannelRunning = FALSE;
#if (ICU_SAFETY_ENABLE == STD_ON)
                    if(TRUE != SafetyFlag)
                    {
                        (void)Det_ReportRuntimeError(ICU_MODULE_ID, 
                                                    ICU_INSTANCE_ID, 
                                                    ICU_SID_ISR, 
                                                    ICU_E_SAFETY_CHECK_FAILED);
                    }
#endif /* ICU_SAFETY_ENABLE == STD_ON */
                }
            }

            /* [SWS_Icu_00318] The Icu module shall only call a notification function if the
            notification has been enabled by the call of Icu_EnableNotification() */
            if (TRUE == ChannelRamDataPtr->NotificationEnable)
            {
                TimestampsCounter = ChannelDataPtr->TimestampsCounter;
                TimestampsCounter++;
                /* SWS_Icu_00320 */
                if ((TimestampsCounter) == (ChannelDataPtr->NotifyInterval))
                {
                    /* [SWS_Icu_00134]The Icu module shall only call a notification function
                    if a notification function is configured. */
                    if (NULL_PTR != SingleChannelConfigPtr->IcuNotificationPtr)
                    {
                        (SingleChannelConfigPtr->IcuNotificationPtr)();
                    }
                    /* Reset the number of timestamp captured counter */
                    TimestampsCounter = MCAL_ZERO;
                }

                ChannelDataPtr->TimestampsCounter = TimestampsCounter;
            }
        }
        ChannelDataPtr->TimestampIndex = IndexOfTimeStamp;
    }
#if (ICU_SAFETY_ENABLE == STD_OFF)
    MCAL_UNUSED_VAR(SafetyFlag);
#endif /* ICU_SAFETY_ENABLE == STD_ON */
}
#endif /* ICU_SIGNAL_MEASUREMENT_API == STD_ON */

/****************************************************************************************************
 *   Function Name           : EdgeDetectionIsrProc
 *
 *   Service ID              : None
 *
 *   Description             : This function process Isr in Edge Detection mode.
 *
 *   Parameters in           :SingleChannelConfigPtr: configuration data for channel.
 *                            ChannelRamDataPtr: Ram Parameter of ch
 *                            IntFlg: New Value Isr Flg
 * 
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for diffrent channel.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static void EdgeDetectionIsrProc
(
    /* #Violation: Icu_c_REF_6 */
    CONSTP2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) ChannelRamDataPtr,
    CONSTP2CONST(Icu_ChnConfigType, AUTOMATIC, ICU_CONFIG_DATA) SingleChannelConfigPtr,
    uint32 IntFlg,
    Icu_ChannelType CoreChIdx
)
{
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
    Mcal_CoreType CoreId;
    /* #Violation: Icu_c_REF_4 */
    CoreId = Mcal_GetCoreId();
#endif /* ICU_REPORT_WAKEUP_SOURCE \== STD_ON */

    if (0U != (IntFlg & ICU_IRQ_NEW_VALUE_MASK))
    {
        ChannelRamDataPtr->ChannelStatus = ICU_ACTIVE;
        if (ICU_MODE_SIGNAL_EDGE_DETECT == ChannelRamDataPtr->MeasurementMode)
        {
            /* [SWS_Icu_00055] IcuReportWakeupSource is set to ON */
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)

            /* [SWS_Icu_00056] The module is in mode ICU_MODE_SLEEP */
            if (ICU_MODE_SLEEP == ICU_CURRENT_MODE(CoreId))
            {
                /* Is channel wakeup capable? */
                if (TRUE == ChannelRamDataPtr->WakeupIsEnabled)
                {
                    /* [SWS_Icu_00228] EcuM call back
                    [SWS_Icu_00057] A wakeup event occurs on a wakeup capable ICU channel*/
                    EcuM_CheckWakeup(ICU_WAKEUP_CFG_INFO(CoreId, CoreChIdx));
                    ChannelRamDataPtr->WakeupSourceIsSet = TRUE;
                }
            }
#else
           /* #Violation: Icu_c_REF_4 */
           MCAL_UNUSED_VAR(CoreChIdx);
#endif /* ICU_REPORT_WAKEUP_SOURCE \== STD_ON */
            /* signal edge detect mode process */
            if (TRUE == ChannelRamDataPtr->NotificationEnable)
            {
                if (NULL_PTR != SingleChannelConfigPtr->IcuNotificationPtr)
                {
                    (SingleChannelConfigPtr->IcuNotificationPtr)();
                }
            }
        }
    }
}
/****************************************************************************************************
 *   Function Name           : Icu_Tim_ISRHandler
 *
 *   Service ID              : 0x30
 *
 *   Description             : This service routine invokes the required function
 *                             based on the channel configuration for further
 *                             calculations. It is called by ISR
 *
 *   Parameters in           : ModuleIndex: Hardware module index.
 *                             Channel: Hardware channel index.
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
FUNC(void, ICU_FAST_CODE) Icu_Tim_ISRHandler
(
    uint8 ModuleIndex,  
    uint8 Channel
)
{
    Icu_ChannelType CoreChIdx;
    uint32 LogicChannel;
    /* Defining a pointer to point to the channel configuration parameters */
    P2CONST(Icu_ChnConfigType, AUTOMATIC, ICU_CONFIG_DATA) SingleChConfigPtr;
    P2CONST(Icu_ChnConfigType, AUTOMATIC, ICU_CONFIG_DATA) SingleChannelConfigPtr;
    /* #Violation: Icu_c_REF_6 */
    P2VAR(Icu_ChannelRamDataType, AUTOMATIC, ICU_APPL_DATA) ChannelRamDataPtr;
    Mcal_CoreType  CoreId;
    Gtm_Icu_Driver Icu_Driver;
    uint32         IntFlg;
    uint8 Offset;
    /* #Violation: Icu_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == Icu_CoreStatusPtr[CoreId])
    {
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SID_ISR, ICU_E_CORE_NOT_CONFIGURED);
    }
    else if (ICU_INITIALIZED != Icu_CoreStatusPtr[CoreId]->Icu_InitState)
    {
        (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SID_ISR, ICU_E_UNINIT);
    }
    else
#endif /* ICU_DEV_ERROR_DETECT == STD_ON */
    {
        Offset = (ModuleIndex * 8U) + Channel;
        /* Find logic from hardware and logic channel mapping table */
        LogicChannel = Icu_ConfigPtr->IcuHwChannelMapPtr[Offset];

        if(0xFFU != LogicChannel)
        {
            if(CoreId == Icu_ConfigPtr->IcuChannelIdxmapPtr[LogicChannel].ExecutionCore)
            {
                /* #Violation: Icu_c_REF_4 */
                CoreChIdx = ICU_GET_CORE_CH_IDX(LogicChannel);
                ChannelRamDataPtr = Icu_GetChannelPar(CoreId, CoreChIdx);
                /* #Violation: Icu_c_REF_1 */
                Icu_Driver.channel = (Gtm_Tim_Ch_Index)Channel;
                /* #Violation: Icu_c_REF_1 */
                Icu_Driver.tim = (Gtm_Tim_Index)ModuleIndex;
                /* Get interrupt flag */
                IntFlg = Gtm_Icu_Hal_GetInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_ALL);
                /* Clearing the interrupt flag for the TIM channel */
                /* [SWS_Icu_00229] The ISR's, providing the wakeup events, shall be responsible
                    for resetting the interrupt flags if required by hardware */
                /* [SWS_Icu_00119] The ISRs shall reset the interrupt flags (if needed by hardware) 
                    and call the corresponding notification functions. */
                Gtm_Icu_Hal_ClearInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_ALL);

                SingleChConfigPtr =
                    Icu_ConfigPtr->CoreConfigPtr[CoreId]->Icu_ChannelConfigPtr->Icu_ChnConfigPtr;
                SingleChannelConfigPtr = &SingleChConfigPtr[CoreChIdx];

                if (0U != IntFlg)
                {
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
                    /* signal measurement mode process */
                    if (ICU_MODE_SIGNAL_MEASUREMENT == ChannelRamDataPtr->MeasurementMode)
                    {
                        /* #Violation: Icu_c_REF_4 */
                        Icu_SignalMeasureOverflowProc(
                            &Icu_Driver,
                            ChannelRamDataPtr,
                            IntFlg);
                    }
#endif /* ICU_SIGNAL_MEASUREMENT_API \== STD_ON */
                    EdgeDetectionIsrProc(ChannelRamDataPtr,SingleChannelConfigPtr,IntFlg,CoreChIdx);
#if (ICU_TIMESTAMP_API == STD_ON)
                    /* Check whether the channel is configured for Timestamp */
                    if (ICU_MODE_TIMESTAMP == ChannelRamDataPtr->MeasurementMode)
                    {
                        Icu_TimeStampIsrProc(&Icu_Driver, ChannelRamDataPtr, SingleChannelConfigPtr);
                    }
#endif /* ICU_TIMESTAMP_API == STD_ON */

#if (ICU_EDGE_COUNT_API == STD_ON)
                    if ((ICU_MODE_EDGE_COUNTER == ChannelRamDataPtr->MeasurementMode))
                    {
                        /*CNT OVERFLOW is occoured*/
                        if(0U != (IntFlg & ICU_IRQ_CNTOVFL_MASK))
                        {
                            if(ICU_MEASURE_IRQ_CNTOVFL == ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IrqType)
                            {
                                /*Disable OVERFLOW INT ,enable new value for next vaild edge*/
                                ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IrqType = ICU_MEASURE_IRQ_NEW_VALUE;
                                /*enable a new value interrupt to set the result as invalid*/
                                (void)Gtm_Icu_Hal_SetInterrupt(&Icu_Driver, (uint8)(GTM_TIM_IRQ_NEWVAL));
                                Gtm_Icu_Hal_ClearInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_ALL);
                            }
                        }
                        /*Next vaild edge */
                        else if (0U != (IntFlg & ICU_IRQ_NEW_VALUE_MASK))
                        {
                            if(ICU_MEASURE_IRQ_NEW_VALUE == ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IrqType)
                            {
                                ICU_ENTER_CRITICAL_SECTION(Icu_Tim_ISRHandler);
                                ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IcuEdgeCount = 
                                ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IcuEdgeCount + ICU_CNTOFL_COUNTER;
                                ICU_EXIT_CRITICAL_SECTION(Icu_Tim_ISRHandler);

                                /*Enable OVERFLOW INT ,Disable new value */
                                ChannelRamDataPtr->ChannelData.Icu_EdgeCountRam.IrqType = ICU_MEASURE_IRQ_CNTOVFL;
                                /*enable a new value interrupt to set the result as invalid*/
                                (void)Gtm_Icu_Hal_SetInterrupt(&Icu_Driver, (uint8)(GTM_TIM_IRQ_CNTOVERFLOW));
                                Gtm_Icu_Hal_ClearInterruptStatus(&Icu_Driver, GTM_TIM_IRQTYPE_ALL);
                            }
                        }
                        else
                        {
                            /*do nothing*/
                        }
                      }
        #endif /* ICU_EDGE_COUNT_API == STD_ON */
                    }
            }
#if (ICU_DEV_ERROR_DETECT == STD_ON)
            else
            {
                (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, ICU_SID_ISR, ICU_E_CORE_CHANNEL_MISMATCH);
            }
#endif /* (ICU_DEV_ERROR_DETECT \== STD_ON) */
        }
    }
}
/* End of Internal function Icu_Tim_ISRHandler */

/* #Violation: Icu_c_REF_11 */
#define ICU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Icu_c_REF_2 */
#include "Icu_MemMap.h"
/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/
