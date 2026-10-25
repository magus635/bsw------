/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Pwm.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : This file contains all API functions of Pwm Driver
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
*#Pwm_c_REF_1:MISRAC2012-Rule-10.5;
* Justification: Redundant cast is necessary to maintain the software structure and reduce the complexity.
*
*#Pwm_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Pwm_c_REF_3:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Pwm_c_REF_4:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Pwm_c_REF_5:CertC-DCL02-C;
* Justification: Company-specific naming conventions  are applied. Developers will not be confused.
*
*#Pwm_c_REF_6:CWE-1071; 
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Pwm_c_REF_7:CertC-PRE00-C; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Pwm_c_REF_8:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Pwm_c_REF_9:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Pwm_c_REF_10:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Pwm_GeneralTypes.h"
#include "gtm_pwm_hal.h"
#include "gtm.h"
/* SWS_Pwm_50075:
 * Pwm.c shall include Pwm.h */
#include "Pwm.h"
#include "Pwm_Version.h"
#include "Pwm_Cfg.h"
#include "Mcall.h"
/* SWS_Pwm_50075:
 * Pwm.c shall include Det.h */
#include "Det.h"

/* SWS_Pwm_50075:
 * Pwm.c shall include SchM_Pwm.h */
#include "SchM_Pwm.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (PWM_VENDOR_ID != PWM_CFG_VENDOR_ID)
  #error "Pwm.c : Mismatch in Vendor ID"
#endif /* PWM_VENDOR_ID != PWM_CFG_VENDOR_ID */

#if (PWM_MODULE_ID != PWM_CFG_MODULE_ID)
  #error "Pwm.c : Mismatch in Module ID"
#endif /* \(PWM_MODULE_ID != PWM_CFG_MODULE_ID) */

#if (PWM_AR_RELEASE_MAJOR_VERSION != PWM_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm.c : Mismatch in Release Major Version"
#endif /* PWM_AR_RELEASE_MAJOR_VERSION != PWM_CFG_AR_RELEASE_MAJOR_VERSION */

#if (PWM_AR_RELEASE_MINOR_VERSION != PWM_CFG_AR_RELEASE_MINOR_VERSION)
  #error "PWM.c : Mismatch in Release Minor Version"
#endif /* PWM_AR_RELEASE_MINOR_VERSION != PWM_CFG_AR_RELEASE_MINOR_VERSION */

#if (PWM_AR_RELEASE_REVISION_VERSION != PWM_CFG_AR_RELEASE_REVISION_VERSION)
  #error "PWM.c : Mismatch in Release Revision Version"
#endif /* PWM_AR_RELEASE_REVISION_VERSION != PWM_CFG_AR_RELEASE_REVISION_VERSION */

#if (PWM_SW_MAJOR_VERSION != PWM_CFG_SW_MAJOR_VERSION)
  #error "PWM.c : Mismatch in Software Major Version"
#endif /* PWM_SW_MAJOR_VERSION != PWM_CFG_SW_MAJOR_VERSION */

#if (PWM_SW_MINOR_VERSION != PWM_CFG_SW_MINOR_VERSION)
  #error "PWM.c : Mismatch in Software Minor Version"
#endif /* PWM_SW_MINOR_VERSION != PWM_CFG_SW_MINOR_VERSION */

#if (PWM_SW_PATCH_VERSION != PWM_CFG_SW_PATCH_VERSION)
  #error "Pwm.c : Mismatch in Software Patch Version"
#endif /* \(PWM_SW_PATCH_VERSION != PWM_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
/* Global variables of all channels in core0 */
/* #Violation: Pwm_c_REF_9 */
#define PWM_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Pwm_MemMap.h"

#if (PWM_MAX_CHANNEL_TO_CORE0 != 0U)

static VAR(Pwm_ChannelStatusType, PWM_VAR_FAST_CLEARED)
        Pwm_ChannelStatusCore0[PWM_MAX_CHANNEL_TO_CORE0];

static VAR(Pwm_InitStateType, PWM_VAR_FAST_CLEARED) Pwm_DriverStatusCore0;

#endif /* PWM_MAX_CHANNEL_TO_CORE0 != 0U */

/* #Violation: Pwm_c_REF_9 */
#define PWM_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"


/* Global variables of all channels in core1 */
/* #Violation: Pwm_c_REF_9 */
#define PWM_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"

#if defined(PWM_MAX_CHANNEL_TO_CORE1) && (PWM_MAX_CHANNEL_TO_CORE1 != 0U)
static VAR(Pwm_ChannelStatusType, PWM_VAR_FAST_CLEARED)
        Pwm_ChannelStatusCore1[PWM_MAX_CHANNEL_TO_CORE1];

static VAR(Pwm_InitStateType, PWM_VAR_FAST_CLEARED) Pwm_DriverStatusCore1;

#endif /* defined(PWM_MAX_CHANNEL_TO_CORE1) \&& (PWM_MAX_CHANNEL_TO_CORE1 != 0U) */

/* #Violation: Pwm_c_REF_9 */
#define PWM_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"


/* Global variables of all channels in core2 */
/* #Violation: Pwm_c_REF_9 */
#define PWM_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"

#if defined(PWM_MAX_CHANNEL_TO_CORE2) && (PWM_MAX_CHANNEL_TO_CORE2 != 0U)
static VAR(Pwm_ChannelStatusType, PWM_VAR_FAST_CLEARED)
        Pwm_ChannelStatusCore2[PWM_MAX_CHANNEL_TO_CORE2];

static VAR(Pwm_InitStateType, PWM_VAR_FAST_CLEARED) Pwm_DriverStatusCore2;

#endif /* defined(PWM_MAX_CHANNEL_TO_CORE2) \&& (PWM_MAX_CHANNEL_TO_CORE2 != 0U) */

/* #Violation: Pwm_c_REF_9 */
#define PWM_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"


/* Global variables of all channels in core3 */
/* #Violation: Pwm_c_REF_9 */
#define PWM_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"

#if defined(PWM_MAX_CHANNEL_TO_CORE3) && (PWM_MAX_CHANNEL_TO_CORE3 != 0U)
static VAR(Pwm_ChannelStatusType, PWM_VAR_FAST_CLEARED)
        Pwm_ChannelStatusCore3[PWM_MAX_CHANNEL_TO_CORE3];

static VAR(Pwm_InitStateType, PWM_VAR_FAST_CLEARED) Pwm_DriverStatusCore3;

#endif /* defined(PWM_MAX_CHANNEL_TO_CORE3) \&& (PWM_MAX_CHANNEL_TO_CORE3 != 0U) */

/* #Violation: Pwm_c_REF_9 */
#define PWM_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"

/* An array containing pointers to global variables of all channels of the core */
/* #Violation: Pwm_c_REF_9 */
#define PWM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"

/* #Violation: Pwm_c_REF_8 */
static CONSTP2VAR(Pwm_ChannelStatusType, PWM_CONFIG_DATA, PWM_APPL_DATA)
        Pwm_CoreChannelStatusPtr[MCAL_NUMBER_OF_CORES] =
{
        /* A pointer the channel global variable of core0 */
#if (PWM_MAX_CHANNEL_TO_CORE0 != 0U)
        &Pwm_ChannelStatusCore0[0],
#else
        NULL_PTR,
#endif /* PWM_MAX_CHANNEL_TO_CORE0 != 0U */
#if (MCAL_NUMBER_OF_CORES >= 2U)
        /* A pointer the channel global variable of core1 */
#if (PWM_MAX_CHANNEL_TO_CORE1 != 0U)
       &Pwm_ChannelStatusCore1[0],
#else
        NULL_PTR,
#endif /* PWM_MAX_CHANNEL_TO_CORE1 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 2U */
#if (MCAL_NUMBER_OF_CORES >= 3U)
        /* A pointer the channel global variable of core2 */
#if (PWM_MAX_CHANNEL_TO_CORE2 != 0U)
       &Pwm_ChannelStatusCore2[0],
#else
        NULL_PTR,
#endif /* PWM_MAX_CHANNEL_TO_CORE2 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 3U */
#if (MCAL_NUMBER_OF_CORES >= 4U)
        /* A pointer the channel global variable of core3 */
#if (PWM_MAX_CHANNEL_TO_CORE3 != 0U)
       &Pwm_ChannelStatusCore3[0]
#else
        NULL_PTR
#endif /* PWM_MAX_CHANNEL_TO_CORE3 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 4U */
};

/* An array containing pointers to global variables of the core status */
/* #Violation: Pwm_c_REF_8 */
static CONSTP2VAR(Pwm_InitStateType, PWM_CONFIG_DATA, PWM_APPL_DATA)
        Pwm_CoreDriverStatusPtr[MCAL_NUMBER_OF_CORES] =
{
#if (PWM_MAX_CHANNEL_TO_CORE0 != 0U)
        &Pwm_DriverStatusCore0,
#else
        NULL_PTR,
#endif /* PWM_MAX_CHANNEL_TO_CORE0 != 0U */
#if (MCAL_NUMBER_OF_CORES >= 2U)
#if (PWM_MAX_CHANNEL_TO_CORE1 != 0U)
       &Pwm_DriverStatusCore1,
#else
        NULL_PTR,
#endif /* PWM_MAX_CHANNEL_TO_CORE1 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 2U */
#if (MCAL_NUMBER_OF_CORES >= 3U)
#if (PWM_MAX_CHANNEL_TO_CORE2 != 0U)
       &Pwm_DriverStatusCore2,
#else
        NULL_PTR,
#endif /* PWM_MAX_CHANNEL_TO_CORE2 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 3U */
#if (MCAL_NUMBER_OF_CORES >= 4U)
#if (PWM_MAX_CHANNEL_TO_CORE3 != 0U)
       &Pwm_DriverStatusCore3
#else
        NULL_PTR
#endif /* PWM_MAX_CHANNEL_TO_CORE3 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 4U */
};

/* #Violation: Pwm_c_REF_9 */
#define PWM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"

/* #Violation: Pwm_c_REF_9 */
#define PWM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"

/* Global pointer that point to configuration data structure */
static P2CONST(Pwm_ConfigType,AUTOMATIC, PWM_CONFIG_DATA) Pwm_ConfigPtr;

/* #Violation: Pwm_c_REF_9 */
#define PWM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"
/****************************************************************************************************
**                          SchM Critical Section Protection Macros                                **
****************************************************************************************************/
/* Enter critical section macros */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_3 */
#define PWM_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_##Exclusive_Area()
/* Exit critical section macros */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_3 */
#define PWM_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_##Exclusive_Area()
/* Get channel global status pointer macros */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_3 */
#define PWM_GET_CHANNEL_RAM_PTR(CoreId, ChIndexInCore) \
        &((Pwm_CoreChannelStatusPtr[CoreId])[ChIndexInCore])
/* Get hardware channel class */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_4 */
#define PWM_GET_HW_CLASS(CoreId, ChIndexInCore) \
        (Pwm_ConfigPtr->CoreConfigPtr[CoreId]->Pwm_ChannelConfigPtr[ChIndexInCore]. \
         PwmHwChannelConfig.HWChannelIndex.module)
/* Get hardware channel object */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_4 */
#define PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore) \
        (&Pwm_ConfigPtr->CoreConfigPtr[CoreId]->Pwm_ChannelConfigPtr[ChIndexInCore]. \
         PwmHwChannelConfig.HWChannelIndex)
/* Get channel index in core */
/* #Violation: Pwm_c_REF_7 */
#define PWM_GET_CHANNEL_INDEX_IN_CORE(LogicChannelId) \
        Pwm_ConfigPtr->PwmChannelIdxmapPtr[LogicChannelId].Index
/* Get channel update mechanism */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_4 */
#define PWM_GET_CHANNEL_UPDATE_MECHANISM(CoreId, ChIndexInCore) \
        (Pwm_ConfigPtr->CoreConfigPtr[CoreId]->Pwm_ChannelConfigPtr[ChIndexInCore]. \
         PwmHwChannelConfig.HWChannelConfig.isSyncUpdateEnabled)
/* Get channel mode */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_4 */
#define PWM_GET_CHANNEL_MODE(CoreId, ChIndexInCore) \
        (Pwm_ConfigPtr->CoreConfigPtr[CoreId]->Pwm_ChannelConfigPtr[ChIndexInCore]. \
         ChnPeriodClass)
/* Get channel idle level */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_4 */
#define PWM_GET_CHANNEL_IDLELEVEL(CoreId, ChIndexInCore) \
        (Pwm_ConfigPtr->CoreConfigPtr[CoreId]->Pwm_ChannelConfigPtr[ChIndexInCore]. \
         IdleLevel)
/* Get channel notify function pointer */
/* #Violation: Pwm_c_REF_7 */
/* #Violation: Pwm_c_REF_4 */
#define PWM_GET_CHANNEL_NOTIFY_PTR(CoreId, ChIndexInCore) \
        (Pwm_ConfigPtr->CoreConfigPtr[CoreId]->Pwm_ChannelConfigPtr[ChIndexInCore]. \
         NotificationFuncPtr)
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#if (PWM_DEV_ERROR_DETECT == STD_ON)
#if (PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
    (PWM_GET_OUTPUT_STATE_API == STD_ON) || (PWM_NOTIFICATION_SUPPORTED == STD_ON) || \
    (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_CheckDetErrors
(
    Pwm_ChannelType ChannelNumber,
    uint8 ApiSid,
    Mcal_CoreType CoreId
);
#endif /* PWM_DEV_ERROR_DETECT == STD_ON */
#endif /* (PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
    (PWM_GET_OUTPUT_STATE_API == STD_ON) || (PWM_NOTIFICATION_SUPPORTED == STD_ON) || \
    (PWM_SET_PERIOD_AND_DUTY_API \== STD_ON) */

#if ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API == STD_ON))
static FUNC(uint32, PWM_PRIVATE_CODE) Pwm_CalculateDuty
(
    Pwm_PeriodType AbsolutePeriod,
    Pwm_PeriodType RelativeDuty
);
#endif /* ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API \== STD_ON)) */

static FUNC(boolean, PWM_PRIVATE_CODE) Pwm_ChannelInit
(
    const Pwm_ChConfigType *const ChannelConfigPtr,
    uint8 CoreIndex,
    Mcal_CoreType CoreId
);

#if (PWM_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_InitDetCheck
(
    const Pwm_ConfigType* const ConfigPtr, 
    Mcal_CoreType CoreId
);

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_SetDutyCycleDetCheck
(
    Pwm_ChannelType ChannelNumber,
    Pwm_DutyCycleType DutyCycleValue,
    Mcal_CoreType CoreId
);
#endif /* PWM_SET_DUTY_CYCLE_API == STD_ON */

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_SetPeriodAndDutyDetCheck
(
    Pwm_ChannelType ChannelNumber,
    Pwm_PeriodType PeriodValue,
    Pwm_DutyCycleType DutyCycleValue,
    Mcal_CoreType CoreId
);
#endif /* PWM_SET_PERIOD_AND_DUTY_API == STD_ON */

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_EnDisableNotificationDetCheck
(
    Pwm_ChannelType ChannelNumber,
    uint8 ApiSid,
    Mcal_CoreType CoreId
);
#endif /* PWM_NOTIFICATION_SUPPORTED == STD_ON */

#endif /* PWM_DEV_ERROR_DETECT == STD_ON */

#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
static FUNC(uint8, PWM_PRIVATE_CODE) Pwm_Is0Or100IrqHandle
(
    const Pwm_ChannelStatusType* const ChannelStatusPtr,
    Pwm_PeriodType CurrentPeriod,
    Pwm_PeriodType AbsDutyCycle
);
#endif /* ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON)) */

/* #Violation: Pwm_c_REF_9 */
#define PWM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"
/****************************************************************************************************
**                          Private Function                                                       **
****************************************************************************************************/
#if (PWM_DEV_ERROR_DETECT == STD_ON)
#if (PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
    (PWM_GET_OUTPUT_STATE_API == STD_ON) || (PWM_NOTIFICATION_SUPPORTED == STD_ON) || \
    (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_CheckDetErrors
 *
 *   Service ID              : None
 *
 *   Description             :This API returns the Det error.
 *
 *   Parameters in           : Channel: Pwm channel ID number;
 *                             ApiSid: service ID
 *                             CoreId: Core id.
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
 *   AUTOSAR_Requirement     : None
 ****************************************************************************************************/
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_CheckDetErrors
(
    Pwm_ChannelType ChannelNumber,
    uint8 ApiSid,
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
    uint8 ChIndexInCore;

    ErrValue = E_NOT_OK;

    /* Check ChannelNumber is in the valid range */
    if(PWM_MAX_CHANNEL_ID_CONFIGURED < ChannelNumber)
    {
        /* SWS_Pwm_30002 */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, ApiSid,
                                PWM_E_PARAM_CHANNEL);
    }
    else if(PWM_INITIALIZED != (*Pwm_CoreDriverStatusPtr[CoreId]))
    {
        /* SWS_Pwm_20002 */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,ApiSid,
                              PWM_E_UNINIT);
    }
    else if(CoreId !=
            Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber].Core)
    {
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,ApiSid,
                              PWM_E_CORE_CHANNEL_MISMATCH);
    }
    else
    {
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        /* #Violation: Pwm_c_REF_4 */
        if ((uint8)GTM_OUTPUT_MODULE_ATOM < PWM_GET_HW_CLASS(CoreId, ChIndexInCore))
        {
            (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, ApiSid, PWM_E_PARAM_VALUE);
        }
        else
        {
            ErrValue = E_OK;
        }
    }

    return ErrValue;
}
#endif /* PWM_DEV_ERROR_DETECT == STD_ON */
#endif /* (PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
    (PWM_GET_OUTPUT_STATE_API == STD_ON) || (PWM_NOTIFICATION_SUPPORTED == STD_ON) || \
    (PWM_SET_PERIOD_AND_DUTY_API \== STD_ON) */

#if ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API == STD_ON))
/****************************************************************************************************
*   Function Name           : Pwm_CalculateDuty
*
*   Service ID              : None
*
*   Description             : This is PWM Driver Component support function.
**                            This function Calculates Absolute duty for the
**                            PWM channel
*
*   Parameters in           : AbsolutePeriod: user defined period
*                             RelativeDuty:user defined duty
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : uint32
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(uint32, PWM_PRIVATE_CODE) Pwm_CalculateDuty
(
    Pwm_PeriodType AbsolutePeriod,
    Pwm_PeriodType RelativeDuty
)
{
    Pwm_PeriodType AbsoluteDuty;
    if(0U == AbsolutePeriod)
    {
        AbsoluteDuty = 0U;
    }
    else
    {
#if (PWM_DUTY_SHIFT_IN_TICKS == STD_ON)
        /* Dutycycle is in absolute ticks, use this directly */
        AbsoluteDuty = RelativeDuty;
#else
        /* SWS_Pwm_00059: Dutycycle is in percentage */
        /* Covert the passed Relative value to absolute value as mentioned in SWS
         (AbsoluteDutyCycle=(((uint32)AbsolutePeriodTime *relativeDutyCycle)))>>15) */
        AbsoluteDuty = (((AbsolutePeriod >> 15U) * RelativeDuty) + \
                        (((AbsolutePeriod & 0x7FFFU) * RelativeDuty) >> 15U));

#endif /* PWM_DUTY_SHIFT_IN_TICKS == STD_ON */
        /* If period is less than scaled value */
        if(AbsolutePeriod <= AbsoluteDuty)
        {
            /* Make scaled value with full range of timer max */
            AbsoluteDuty = AbsolutePeriod;
        }
    }
    return AbsoluteDuty;
}
#endif /* ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API \== STD_ON)) */

/****************************************************************************************************
*   Function Name           : Pwm_ChannelInit
*
*   Service ID              : None
*
*   Description             : This API initialize the hardware channel of PWM.
*
*   Parameters in           : ChannelConfigPtr: Pointer to the channel configuration.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : No-Reentrant.
*
*   Return value            : Safety check status.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, PWM_PRIVATE_CODE) Pwm_ChannelInit
(
    const Pwm_ChConfigType *const ChannelConfigPtr,
    uint8 CoreIndex,
    Mcal_CoreType CoreId
)
{
    Pwm_ChannelStatusType* ChannelStatusPtr;
    boolean SafetyFlag;

    /* Init the hardware channel */
    SafetyFlag = Gtm_Pwm_Hal_InitChannel(&(ChannelConfigPtr->PwmHwChannelConfig.HWChannelIndex),
                            &(ChannelConfigPtr->PwmHwChannelConfig.HWChannelConfig));

    ChannelStatusPtr = PWM_GET_CHANNEL_RAM_PTR(CoreId, CoreIndex);

    /* Store the period to global variable */
    ChannelStatusPtr->CurrentPeriodVal = ChannelConfigPtr->Period;
#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
    if((0U == ChannelConfigPtr->DutyCycle) || 
       (0U == ChannelConfigPtr->Period) || 
       (ChannelConfigPtr->DutyCycle == ChannelConfigPtr->Period))
    {
        ChannelStatusPtr->DutyIs0Or100 = TRUE;
    }
#endif /* ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON)) */

    return SafetyFlag;
}

#if (PWM_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Pwm_InitDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Pwm_Init.
*
*   Parameters in           :ConfigPtr: Input configuration data structure pointer.
*                            CoreId: Core ID.   
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
*   AUTOSAR_Requirement     : SWS_Pwm_00201, SWS_Pwm_50002
****************************************************************************************************/
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_InitDetCheck
(
    const Pwm_ConfigType* const ConfigPtr, 
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;

    ErrValue = E_NOT_OK;

    if(NULL_PTR == ConfigPtr)
    {
        /* SWS_Pwm_00201 */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_INIT_SID,PWM_E_INIT_FAILED);
    }
    else if(NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId])
    {
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_INIT_SID,
                                PWM_E_CORE_NOT_CONFIGURED);
    }
    else if(PWM_UNINITIALIZED != (*Pwm_CoreDriverStatusPtr[CoreId]))
    {
        /* SWS_Pwm_50002 */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,PWM_INIT_SID,
                                PWM_E_ALREADY_INITIALIZED);
    }
    else
    {
        ErrValue = E_OK;
    }

    return ErrValue;
}

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Pwm_SetDutyCycleDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Pwm_SetDutyCycle.
*
*   Parameters in           : ChannelNumber: Numeric identifier of the PWM
*                             DutyCycle: Min = 0x0000
*                                        Max=0x8000(In Percent)
*                                        Max=0xFFFF(In ticks and hardware is GTM-TOM)
*                                        Max=0xFFFFFF(In ticks and hardware is GTM-ATOM)
*                             CoreId: Core of the current core
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
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_SetDutyCycleDetCheck
(
    Pwm_ChannelType ChannelNumber,
    Pwm_DutyCycleType DutyCycleValue,
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
#if (PWM_DUTY_SHIFT_IN_TICKS == STD_ON)
    uint8 ChIndexInCore;
#endif /* PWM_DUTY_SHIFT_IN_TICKS \== STD_ON */

    ErrValue = Pwm_CheckDetErrors(ChannelNumber, PWM_SET_DUTYCYCLE_SID, CoreId);

    if(E_OK == ErrValue)
    {
        /* In this macro, duty cycle is set by ticks */
#if (PWM_DUTY_SHIFT_IN_TICKS == STD_ON)
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        /* Pwm channel based on gtm-atom is 24 bits wide */
        /* #Violation: Pwm_c_REF_4 */
        if(((uint8)GTM_OUTPUT_MODULE_ATOM == PWM_GET_HW_CLASS(CoreId, ChIndexInCore)) && 
            (PWM_MAX_DUTYCYCLE_TICKS_ATOM < DutyCycleValue))
        {
            (void) Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                   PWM_SET_DUTYCYCLE_SID,
                                   PWM_E_PARAM_VALUE);
            ErrValue = E_NOT_OK;
        }
        /* #Violation: Pwm_c_REF_4 */
        else if(((uint8)GTM_OUTPUT_MODULE_TOM == PWM_GET_HW_CLASS(CoreId, ChIndexInCore)) &&
                (PWM_MAX_DUTYCYCLE_TICKS_TOM < DutyCycleValue))
        {
            (void) Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                    PWM_SET_DUTYCYCLE_SID,
                                    PWM_E_PARAM_VALUE);
            ErrValue = E_NOT_OK;
        }
#else
        if(PWM_MAX_DUTYCYCLE_PERCENT < DutyCycleValue)
        {
            /* SWS_Pwm_00058 */
            (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_DUTYCYCLE_SID,
                                    PWM_E_PARAM_VALUE);
            ErrValue = E_NOT_OK;
        }
#endif /* PWM_DUTY_SHIFT_IN_TICKS \== STD_ON */
        /* #Violation: Pwm_c_REF_6 */
        else
        {
            /* Do nothing */
        }
    }

    return ErrValue;
}
#endif /* PWM_SET_DUTY_CYCLE_API == STD_ON */

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Pwm_SetPeriodAndDutyDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Pwm_SetPeriodAndDuty.
*
*   Parameters in           : ChannelNumber: Numeric identifier of the PWM
*                             Period:    Min = 0x0000
*                                        Max=0x8000(In Percent)
*                                        Max=0xFFFF(In ticks and hardware is GTM-TOM)
*                                        Max=0xFFFFFF(In ticks and hardware is GTM-ATOM)
*                             DutyCycle: Min = 0x0000
*                                        Max=0x8000(In Percent)
*                                        Max=0xFFFF(In ticks and hardware is GTM-TOM)
*                                        Max=0xFFFFFF(In ticks and hardware is GTM-ATOM)
*                             CoreId: Core of the current core
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
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_SetPeriodAndDutyDetCheck
(
    Pwm_ChannelType ChannelNumber,
    Pwm_PeriodType PeriodValue,
    Pwm_DutyCycleType DutyCycleValue,
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
    uint8 ChIndexInCore;
    
    /* Check the validation of the common functions */
    ErrValue = Pwm_CheckDetErrors(ChannelNumber, PWM_SET_PERIODANDDUTY_SID, CoreId);

    if(E_OK == ErrValue)
    {
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        /* #Violation: Pwm_c_REF_4 */
        if (PWM_VARIABLE_PERIOD != PWM_GET_CHANNEL_MODE(CoreId, ChIndexInCore))
        {
            /* SWS_Pwm_40002, SWS_Pwm_00041 */
            (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                  PWM_SET_PERIODANDDUTY_SID,
                                  PWM_E_PERIOD_UNCHANGEABLE);
            ErrValue = E_NOT_OK;
        }
        /* #Violation: Pwm_c_REF_4 */
        else if((uint8)GTM_OUTPUT_MODULE_TOM == PWM_GET_HW_CLASS(CoreId, ChIndexInCore))
        {
            /* Pwm channel based on GTM-TOM is 16 bits wide */
            if(PWM_MAX_PERIOD_TICKS_TOM < PeriodValue)
            {
                (void) Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                        PWM_SET_PERIODANDDUTY_SID,
                                        PWM_E_PARAM_VALUE);
                ErrValue = E_NOT_OK;
            }
#if (PWM_DUTY_SHIFT_IN_TICKS == STD_ON)
            /* In percent, the duty cycle value should be less than 0x8000 */
            else if(DutyCycleValue > PWM_MAX_DUTYCYCLE_TICKS_TOM)
            {
                (void) Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                        PWM_SET_PERIODANDDUTY_SID,
                                        PWM_E_PARAM_VALUE);
                ErrValue = E_NOT_OK;
            }
#else 
            else if(DutyCycleValue > PWM_MAX_DUTYCYCLE_PERCENT)
            {
                (void) Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                        PWM_SET_PERIODANDDUTY_SID,
                                        PWM_E_PARAM_VALUE);
                ErrValue = E_NOT_OK;
            }
#endif /* PWM_DUTY_SHIFT_IN_TICKS \== STD_ON */
            /* #Violation: Pwm_c_REF_6 */
            else
            {
                /* Do nothing */
            }
        }
        /* #Violation: Pwm_c_REF_4 */
        else if((uint8)GTM_OUTPUT_MODULE_ATOM == PWM_GET_HW_CLASS(CoreId, ChIndexInCore))
        {
            /* Pwm channel based on GTM-TOM is 16 bits wide */
            if(PWM_MAX_PERIOD_TICKS_ATOM < PeriodValue)
            {
                (void) Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                        PWM_SET_PERIODANDDUTY_SID,
                                        PWM_E_PARAM_VALUE);
                ErrValue = E_NOT_OK;
            }
#if (PWM_DUTY_SHIFT_IN_TICKS == STD_ON)
            /* In percent, the duty cycle value should be less than 0x8000 */
            else if(DutyCycleValue > PWM_MAX_DUTYCYCLE_TICKS_ATOM)
            {
                (void) Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                        PWM_SET_PERIODANDDUTY_SID,
                                        PWM_E_PARAM_VALUE);
                ErrValue = E_NOT_OK;
            }
#else 
            else if(DutyCycleValue > PWM_MAX_DUTYCYCLE_PERCENT)
            {
                (void) Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                                        PWM_SET_PERIODANDDUTY_SID,
                                        PWM_E_PARAM_VALUE);
                ErrValue = E_NOT_OK;
            }
#endif /* PWM_DUTY_SHIFT_IN_TICKS \== STD_ON */
            /* #Violation: Pwm_c_REF_6 */
            else
            {
                /* Do nothing */
            }
        }
        /* #Violation: Pwm_c_REF_6 */
        else
        {
            /* Do nothing */
        }
    }
    return ErrValue;
}
#endif /* End of (PWM_SET_PERIOD_AND_DUTY_API \== STD_ON) */

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/****************************************************************************************************
*   Function Name           : Pwm_EnDisableNotificationDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Pwm_DisableNotification or 
*                            Pwm_EnableNotification.
*
*   Parameters in           : ChannelNumber: Numeric identifier of the PWM
*                             ApiSid: PWM_ENABLE_NOTIFICATION_SID or PWM_DISABLE_NOTIFICATION_SID
*                             CoreId: Core of the current core
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
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(Std_ReturnType, PWM_PRIVATE_CODE) Pwm_EnDisableNotificationDetCheck
(
    Pwm_ChannelType ChannelNumber,
    uint8 ApiSid,
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
    uint8 ChIndexInCore;

    /* Check the validation of the common functions */
    ErrValue = Pwm_CheckDetErrors(ChannelNumber, ApiSid, CoreId);

    ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

    if(E_OK == ErrValue)
    {
        /* #Violation: Pwm_c_REF_4 */
        if(NULL_PTR == PWM_GET_CHANNEL_NOTIFY_PTR(CoreId, ChIndexInCore))
        {
            (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, ApiSid,
                                  PWM_E_NOTIFY_NOTCONFIG);
            ErrValue = E_NOT_OK;
        }
        else
        {
            ErrValue = E_OK;
        }
    }

  return ErrValue;
}
#endif /* End of (PWM_NOTIFICATION_SUPPORTED \== STD_ON) */

#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */

#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
/****************************************************************************************************
*   Function Name           : Pwm_Is0Or100IrqHandle
*
*   Service ID              : None
*
*   Description             :This API gets the interrupt handle information for 0% or 100% duty cycle 
*                           condition.
*
*   Parameters in           : ChannelStatusPtr: Pointer to the logic channel global variables.
*                             CurrentPeriod: Current period of the channel.
*                             AbsDutyCycle: Absolute duty cycle of the channel(In ticks).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : No-Reentrant.
*
*   Return value            : uint8
*                             0: Do not need to handle interrupt
*                             1: Need to enter 0 or 100 interrupt handle
*                             2: Need to exit 0 or 100 interrupt handle
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(uint8, PWM_PRIVATE_CODE) Pwm_Is0Or100IrqHandle
(
    const Pwm_ChannelStatusType* const ChannelStatusPtr,
    Pwm_PeriodType CurrentPeriod,
    Pwm_PeriodType AbsDutyCycle
)
{
    uint8 HandleFlag;
    
      HandleFlag = 0U;

    /* Do the operation, only if the interrupt is enabled */
    if(GTM_PWM_IRQEDGE_NONE != ChannelStatusPtr->InterruptStatus)
    {
        /* If the old duty cycle is between 0% to 100% */
        if(FALSE == ChannelStatusPtr->DutyIs0Or100)
        {
            /* 0% or 100% duty cycle is set */
            if ((0U == AbsDutyCycle) || (AbsDutyCycle == CurrentPeriod) || (0U == CurrentPeriod))
            {
                HandleFlag = 1U;
            }
        }
        /* If the old duty cycle is 0% or 100% */
        else
        {
            /* New duty cycle between 0% to 100% is set */
            if ((0U != AbsDutyCycle) && (0U != CurrentPeriod) && (AbsDutyCycle != CurrentPeriod))
            {
                HandleFlag = 2U;
            }
        }
    }

    return HandleFlag;
}
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */

/****************************************************************************************************
*   Function Name           : PWM_CalculateCompareValues
*
*   Service ID              : None
*
*   Description             : This function Calculates Absolute duty for the compare values
*                             CM0 and CM1
*
*   Parameters in           : CoreId: core id.
*                             ChIndexInCore: channel index in current core.
*                             CurrentPeriod: current channel period.
*                             AbsDutyCycle: absolute duty cycle.
*                             ChannelConfigPtr: channel configuration pointer.
*                             HwCompareZero: Hardware compare value CM0.
*                             HwCompareOne: Hardware compare value CM1.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : void.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
LOCAL_INLINE FUNC(void, PWM_PRIVATE_CODE) PWM_CalculateCompareValues
(
    Mcal_CoreType           CoreId,
    uint8                   ChIndexInCore,
    Pwm_PeriodType          CurrentPeriod,
    Pwm_PeriodType          AbsDutyCycle,
    const Pwm_ChConfigType* ChannelConfigPtr,
    uint32*                 HwCompareZero,
    uint32*                 HwCompareOne
)
{
    uint32 MaxCounter;
    /* #Violation: Pwm_c_REF_4 */
    if((uint8)GTM_OUTPUT_MODULE_TOM == PWM_GET_HW_CLASS(CoreId, ChIndexInCore))
    {
        MaxCounter = PWM_MAX_DUTYCYCLE_TICKS_TOM;
    }
    else
    {
        MaxCounter = PWM_MAX_DUTYCYCLE_TICKS_ATOM;
    }

    /* Duty cycle is 0% */
    if(0U == AbsDutyCycle)
    {
        /* If the counter register TOM[i]_CH[x]_CN0.CN0 of channel x is reset
            * by the trigger signal coming from another channel,If TOM[i]_CH[x]_CM0.CM0
            * > MAX and TOM[i]_CH[x]_CM1.CM1=0, the output is !TOM[i]_CH[x]_CTRL.SL
            * (i.e. 0% duty cycle PWM signal). */
        *HwCompareZero = MaxCounter;
        *HwCompareOne = 0U;
    }
    /* Duty cycle is 100% */
    else if(AbsDutyCycle == CurrentPeriod)
    {
        /* If the counter register TOM[i]_CH[x]_CN0.CN0 of channel x is reset
            * by the trigger signal coming from another channel,If TOM[i]_CH[x]_CM0.CM0=0
            * and TOM[i]_CH[x]_CM1.CM1=MAX, the output is a pulse of TOM[i]_CH[x]_CTRL.SL
            * for the period MAX (i.e.100% duty cycle PWM signal). */
        *HwCompareZero = 0U;
        *HwCompareOne = MaxCounter;
    }
    /* Duty cycle is 0% ~ 100% */
    else
    {
        /* In this case, the duty cycle and period values are not directly equal the CM1 and 
            * CM0 registers of the hardware, respectively */
        if(PWM_FIXED_PERIOD_SHIFTED == ChannelConfigPtr->ChnPeriodClass)
        {
            /* After the phase shift, the output point of the initial polarity 
                * waveform is defined by the shift value(In ticks) */
            *HwCompareZero = ChannelConfigPtr->ShiftValue;
            /* The output point of the non-polarity waveform is also 
                * defined by the shift value */
            *HwCompareOne = ((ChannelConfigPtr->ShiftValue + AbsDutyCycle) % CurrentPeriod);
        }
        else
        {
            /* The PWM_FIXED_PERIOD_CENTER_ALIGNED mode can be understood as a special phase shift, 
                * and the phase shift value is just half of the non-duty cycle phase */
            *HwCompareZero = (CurrentPeriod - AbsDutyCycle) >> 1U;
            *HwCompareOne = CurrentPeriod - ((CurrentPeriod - AbsDutyCycle) >> 1U);
        }
    }
}

/****************************************************************************************************
 **                          Global Function Definitions                                            **
 ****************************************************************************************************/
/* SWS_Pwm_20069 */
#if (PWM_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_GetVersionInfo
 *
 *   Service ID              : 0x08
 *
 *   Description             :This API returns the version information of PWM
 *                            driver component.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : Pointer to where to store the version information of this module.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : PWM Module must be initialized..
 *
 *   AUTOSAR_Requirement     : SWS_Pwm_00103.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(void, PWM_PUBLIC_CODE) Pwm_GetVersionInfo
(
    /* #Violation: Pwm_c_REF_8 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA)VersionInfoPtr
)
{
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* Check if parameter passed is equal to Null pointer */
    if(NULL_PTR == VersionInfoPtr)
    {
        /* Report Error to DET */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,
                              PWM_GET_VERSION_INFO_SID, PWM_E_PARAM_POINTER);
    }
    else
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    {
        VersionInfoPtr->vendorID = PWM_VENDOR_ID;
        VersionInfoPtr->moduleID = PWM_MODULE_ID;
        VersionInfoPtr->sw_major_version = PWM_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = PWM_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = PWM_SW_PATCH_VERSION;
    }
}
#endif /* PWM_VERSION_INFO_API == STD_ON */
/****************************************************************************************************
 *   Function Name           : Pwm_Init
 *
 *   Service ID              : 0x00
 *
 *   Description             : Initialize all internals variables  and the used PWM structure
 *
 *   Parameters in           : ConfigPtr: The pointer to configuration set.
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
 *   AUTOSAR_Requirement     : SWS_Pwm_00095.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(void, PWM_PUBLIC_CODE) Pwm_Init
(
    P2CONST(Pwm_ConfigType, PWM_VAR, PWM_APPL_CONST) ConfigPtr
)
{
    Mcal_CoreType CoreId;
    const Pwm_ChConfigType *ChannelConfigPtr;
    uint8 ChIndexInCore;
    Std_ReturnType LockStatus;
#if (PWM_HANDLE_SHIFT_BY_OFFSET == STD_ON)
    uint8 OutputsNumber;
    const Pwm_ChannelsOutputCfgType *ChannelsOutputConfigPtr;
#endif /* PWM_HANDLE_SHIFT_BY_OFFSET \== STD_ON */
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* End of (PWM_DEV_ERROR_DETECT \== STD_ON) */
    boolean SafetyFlag;

    SafetyFlag = TRUE;

    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (PWM_DEV_ERROR_DETECT == STD_ON)

    ErrValue = Pwm_InitDetCheck(ConfigPtr,CoreId);

    if(E_OK == ErrValue)
#endif /* End of (PWM_DEV_ERROR_DETECT \== STD_ON) */
    {
        Pwm_ConfigPtr = ConfigPtr;

        ChannelConfigPtr = Pwm_ConfigPtr->CoreConfigPtr[CoreId]->Pwm_ChannelConfigPtr;
        /* Loop to set the attributes of Advance Timer channels */
        for (ChIndexInCore = 0U;
             ChIndexInCore < Pwm_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels; 
             ChIndexInCore++)
        {
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_PWM);
            if(E_OK == LockStatus)
            {  
                /* SWS_Pwm_00052: Disable all notifications */
                SafetyFlag &= Pwm_ChannelInit(&ChannelConfigPtr[ChIndexInCore], ChIndexInCore, CoreId);
                Mcal_ReleaseLock(MCAL_LOCK_ID_PWM);
            }
            else
            {
                /* Get lock failed */
                SafetyFlag = FALSE;
            }
            if(TRUE != SafetyFlag)
            {
                break;
            }
        } /* End of Advance Timer channels Settings 'for' loop */

#if (PWM_HANDLE_SHIFT_BY_OFFSET == STD_ON)
        ChannelsOutputConfigPtr = Pwm_ConfigPtr->CoreConfigPtr[CoreId]->
            ChannelsOutputConfig.ChannelSOutPtr;
        /* Enter Protected area */
        PWM_ENTER_CRITICAL_SECTION(Pwm_Init);
        for (OutputsNumber = 0U; OutputsNumber <Pwm_ConfigPtr->CoreConfigPtr[CoreId]->
             ChannelsOutputConfig.OutputChannelsNumber; OutputsNumber++)
        {
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_PWM);
            if(E_OK == LockStatus)
            {
                SafetyFlag &= Gtm_Pwm_Hal_SetChannelsOutput(ChannelsOutputConfigPtr[OutputsNumber].Module,
                                            ChannelsOutputConfigPtr[OutputsNumber].ModuleIndex,
                                            ChannelsOutputConfigPtr[OutputsNumber].
                                            OutputChannelsConfig,
                                            TRUE);
                Mcal_ReleaseLock(MCAL_LOCK_ID_PWM);
            }
            else
            {
                /* Get lock failed */
                SafetyFlag = FALSE;
            }
            if(TRUE != SafetyFlag)
            {
                break;
            }
        }
        /* Exit Protected area */
        PWM_EXIT_CRITICAL_SECTION(Pwm_Init);
#endif /* PWM_HANDLE_SHIFT_BY_OFFSET == STD_ON */

        if(TRUE == SafetyFlag)
        {
            (*Pwm_CoreDriverStatusPtr[CoreId]) = PWM_INITIALIZED;
        }
        else
        {
#if (PWM_SAFETY_ENABLE == STD_ON)
            (void)Det_ReportRuntimeError(PWM_MODULE_ID, 
                                        PWM_INSTANCE_ID, 
                                        PWM_INIT_SID, 
                                        PWM_E_SAFETY_CHECK_FAILED);
#endif /* PWM_SAFETY_ENABLE == STD_ON */
        }
    }
} /* End of API Pwm_Init() */

/* SWS_Pwm_10080, SWS_Pwm_20080 */
#if (PWM_DE_INIT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_DeInit
 *
 *   Service ID              : 0x01
 *
 *   Description             : de-initialize the PWM module.
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
 *   Preconditions           : PWM Module must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Pwm_00096.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(void, PWM_PUBLIC_CODE) Pwm_DeInit
(
    void
)
{
    Mcal_CoreType CoreId;
    uint8 ChIndexInCore;
    const Pwm_ChConfigType *ChannelConfigPtr;
    Gtm_SignalState IdleSignalLevel;
    Pwm_ChannelStatusType* ChannelStatusPtr;
    boolean SafetyFlag;
    Std_ReturnType LockStatus;

    SafetyFlag = TRUE;
    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (PWM_DEV_ERROR_DETECT == STD_ON)
    if(PWM_INITIALIZED != (*Pwm_CoreDriverStatusPtr[CoreId]))
    {
        /* SWS_Pwm_20002 */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_DEINIT_SID, PWM_E_UNINIT);
    }
    else
#endif /* PWM_DEV_ERROR_DETECT == STD_ON */
    {
        ChannelConfigPtr = Pwm_ConfigPtr->CoreConfigPtr[CoreId]->Pwm_ChannelConfigPtr;
        for (ChIndexInCore = 0U;
             ChIndexInCore < (uint8)Pwm_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels; 
             ChIndexInCore++)
        {
            ChannelStatusPtr = PWM_GET_CHANNEL_RAM_PTR(CoreId, ChIndexInCore);

            IdleSignalLevel = ChannelConfigPtr[ChIndexInCore].IdleLevel;

            PWM_ENTER_CRITICAL_SECTION(Pwm_DeInit);
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_PWM);
            if(E_OK == LockStatus)
            {
                /* SWS_Pwm_00011: set the state of the PWM output
                signals to the idle state */
                /* SWS_Pwm_00012: Disable PWM interrupts */
                SafetyFlag &= Gtm_Pwm_Hal_DeinitChannel(
                    /* #Violation: Pwm_c_REF_4 */
                    PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore), IdleSignalLevel);
                Mcal_ReleaseLock(MCAL_LOCK_ID_PWM);
            }
            else
            {
                /* Get lock failed */
                SafetyFlag = FALSE;
            }

            /* Set global notification status to no edge */
            ChannelStatusPtr->InterruptStatus = GTM_PWM_IRQEDGE_NONE;
            /* Set global period status to no edge */
            ChannelStatusPtr->CurrentPeriodVal = 0U;
#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
            /* Set global 0% or 100% status to false */
            ChannelStatusPtr->DutyIs0Or100 = FALSE;
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */
            /* Exit Protected area */
            PWM_EXIT_CRITICAL_SECTION(Pwm_DeInit);

            if(TRUE != SafetyFlag)
            {
                break;
            }
        }

        if(TRUE == SafetyFlag)
        {
            (*Pwm_CoreDriverStatusPtr[CoreId]) = PWM_UNINITIALIZED;
        }
#if (PWM_SAFETY_ENABLE == STD_ON)
        else
        {
            (void)Det_ReportRuntimeError(PWM_MODULE_ID, 
                                        PWM_INSTANCE_ID, 
                                        PWM_DEINIT_SID, 
                                        PWM_E_SAFETY_CHECK_FAILED);
        }
#endif /* PWM_SAFETY_ENABLE == STD_ON */
    }
}
#endif /* End of (PWM_DE_INIT_API \== STD_ON) */

/* SWS_Pwm_10082, SWS_Pwm_20082 */
#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_SetDutyCycle
 *
 *   Service ID              : 0x02
 *
 *   Description             :  set the duty cycle of the PWM channel.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the PWM
 *                             DutyCycle: Min = 0x0000
 *                                        Max=0x8000 in Percent
 *                                        Max=0xFFFF in ticks and hardware is GTM-TOM
 *                                        Max=0xFFFFFF in ticks and hardware is GTM-ATOM
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channel numbers.
 *
 *   Return value            : None.
 *
 *   Preconditions           : PWM Module must be initialized..
 *
 *   AUTOSAR_Requirement     : SWS_Pwm_00097.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(void, PWM_PUBLIC_CODE) Pwm_SetDutyCycle
(
    Pwm_ChannelType ChannelNumber,
    /* #Violation: Pwm_c_REF_5 */
    Pwm_DutyCycleType DutyCycle
)
{
    Pwm_PeriodType CurrentPeriod;
    Pwm_PeriodType AbsDutyCycle;
    uint8 ChIndexInCore;
    Pwm_ChannelStatusType* ChannelStatusPtr;
    Mcal_CoreType CoreId;
    const Pwm_ChConfigType* ChannelConfigPtr;
    uint32 HwCompareZero;
    uint32 HwCompareOne;
#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
    uint8 HandleInfo;
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON */
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    boolean SafetyFlag;

    SafetyFlag = TRUE;

    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Pwm_20002, SWS_Pwm_30002 */
    ErrValue = Pwm_SetDutyCycleDetCheck(ChannelNumber, DutyCycle, CoreId);

    if(E_OK == ErrValue)
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    {
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        
        ChannelStatusPtr = PWM_GET_CHANNEL_RAM_PTR(CoreId, ChIndexInCore);
        /* Get channel configuration pointer */
        ChannelConfigPtr = &(Pwm_ConfigPtr->CoreConfigPtr[CoreId]->
                           Pwm_ChannelConfigPtr[ChIndexInCore]);

        if(PWM_VARIABLE_PERIOD == ChannelConfigPtr->ChnPeriodClass)
        {
            /* The period value may be changed by user through API,
             * so get the period value from global variable */
            CurrentPeriod = ChannelStatusPtr->CurrentPeriodVal;
        }
        else
        {
            /* Except for the variable period mode, the period value of other modes 
             * is fixed at the configuration stage, so you can take it from the 
             * static configuration */
            CurrentPeriod = ChannelConfigPtr->Period;
        }
        /* Calculate the absolute duty cycle value(In ticks) */
        AbsDutyCycle = Pwm_CalculateDuty(CurrentPeriod, DutyCycle);

        /* SWS_Pwm_00013:  Set the duty cycle of the channel. */
        /* SWS_Pwm_00014 , SWS_Pwm_00016 */
        /* SWS_Pwm_00017: Update the duty cycle with configured PwmDutycycleUpdatedEndperiod */

        /* This condition represents all modes with 'PwmHandleShiftByOffset' enabled, 
         * as well as PWM_FIXED_PERIOD and PWM_VARIABLE_PERIOD with with 
         * 'PwmHandleShiftByOffset' disabled */
        if(GTM_PWM_RESETEVENT_ONCM0 == ChannelConfigPtr->
                                       PwmHwChannelConfig.HWChannelConfig.resetSource)
        {
            /* In this case, the duty cycle and period values correspond to the CM1 and 
             * CM0 registers of the hardware, respectively */
            HwCompareZero = CurrentPeriod;
            HwCompareOne = AbsDutyCycle;
        }
        /* This condition represents PWM_FIXED_PERIOD_SHIFTED and PWM_FIXED_PERIOD_CENTER_ALIGNED modes
         * with 'PwmHandleShiftByOffset' disabled */
        else
        {
            PWM_CalculateCompareValues(CoreId,
                                       ChIndexInCore,
                                       CurrentPeriod,
                                       AbsDutyCycle,
                                       ChannelConfigPtr,
                                       &HwCompareZero,
                                       &HwCompareOne);
            /* GTM errata 517 :MISS output signal when CM1<2 and CM0> CM1*/
            if ((2U > HwCompareOne) && (HwCompareZero > HwCompareOne))
            {
#if (PWM_SAFETY_ENABLE == STD_ON)
                (void)Det_ReportRuntimeError(
                    PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_DUTYCYCLE_SID, PWM_E_PARAM_VALUE);
#endif
            }
        }
        PWM_ENTER_CRITICAL_SECTION(Pwm_SetDutyCycle);

#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
        HandleInfo = Pwm_Is0Or100IrqHandle(ChannelStatusPtr,
                                           CurrentPeriod,
                                           AbsDutyCycle);
        /* From non 0% or non 100% enter to 0% or 100%, disable interrupt first 
           and then update compare value */
        if(1U == HandleInfo)
        {
            /* Disable interrupt */
            /* #Violation: Pwm_c_REF_4 */
            SafetyFlag &= Gtm_Pwm_Hal_SetInterrupt(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                                   GTM_PWM_IRQEDGE_ALL,
                                                   FALSE);
            ChannelStatusPtr->DutyIs0Or100 = TRUE;
        }
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */

        SafetyFlag &= Gtm_Pwm_Hal_SetPeriodDutyCycle(
                                        /* #Violation: Pwm_c_REF_4 */
                                        PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                        HwCompareZero,
                                        HwCompareOne,
                                        /* #Violation: Pwm_c_REF_4 */
                                        PWM_GET_CHANNEL_UPDATE_MECHANISM(CoreId, ChIndexInCore));

#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
        /* From 0% or 100% enter to non 0% or non 100%, update compare value first,
           and then enable interrupt */
        if(2U == HandleInfo)
        {
            /* Enable interrupt */
            /* #Violation: Pwm_c_REF_4 */
            SafetyFlag &= Gtm_Pwm_Hal_SetInterrupt(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                                   ChannelStatusPtr->InterruptStatus,
                                                   TRUE);
            ChannelStatusPtr->DutyIs0Or100 = FALSE;
        }
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */

        PWM_EXIT_CRITICAL_SECTION(Pwm_SetDutyCycle);

#if (PWM_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            (void)Det_ReportRuntimeError(PWM_MODULE_ID, 
                                         PWM_INSTANCE_ID, 
                                         PWM_SET_DUTYCYCLE_SID, 
                                         PWM_E_SAFETY_CHECK_FAILED);
        }
#else
        MCAL_UNUSED_VAR(SafetyFlag);
#endif /* PWM_SAFETY_ENABLE == STD_ON */

    }
}
#endif /* PWM_SET_DUTY_CYCLE_API == STD_ON */

/* SWS_Pwm_10083, SWS_Pwm_20083 */
#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_SetPeriodAndDuty
 *
 *   Service ID              : 0x03
 *
 *   Description             :  set the period and the duty cycle of a PWM channel.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the PWM
 *                             Period: Period of the PWM signal
 *                             DutyCycle: Min=0x0000 Max=0x8000
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channel numbers
 *
 *   Return value            : None.
 *
 *   Preconditions           : PWM Module must be initialized..
 *
 *   AUTOSAR_Requirement     : SWS_Pwm_00098.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(void, PWM_PUBLIC_CODE) Pwm_SetPeriodAndDuty
/* #Violation: Pwm_c_REF_5 */
(
    Pwm_ChannelType ChannelNumber,
    Pwm_PeriodType Period,
    /* #Violation: Pwm_c_REF_5 */
    Pwm_DutyCycleType DutyCycle
)
{
    Mcal_CoreType CoreId;
    uint32 AbsDutyCycle;
    uint8 ChIndexInCore;
    Pwm_ChannelStatusType* ChannelStatusPtr;
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ErrValue;
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
    uint8 HandleInfo;
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */
    boolean SafetyFlag;

    SafetyFlag = TRUE;
    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /*SWS_Pwm_30002 */
    ErrValue = Pwm_SetPeriodAndDutyDetCheck(ChannelNumber, Period, DutyCycle, CoreId);

    if (E_OK == ErrValue)
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    {
        /* Get the channel index in core */
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        /* Get channel status variables pointer */
        ChannelStatusPtr = PWM_GET_CHANNEL_RAM_PTR(CoreId, ChIndexInCore);

        PWM_ENTER_CRITICAL_SECTION(Pwm_SetPeriodAndDuty);
        /* Record the current period value for Pwm_SetDutyCycle() API to 
         * calculate the absolute duty cycle value */
        ChannelStatusPtr->CurrentPeriodVal = Period;
        /* Calculate the absolute duty cycle value(In ticks) */
        AbsDutyCycle = Pwm_CalculateDuty(Period, DutyCycle);

#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
        HandleInfo = Pwm_Is0Or100IrqHandle(ChannelStatusPtr,
                                           Period,
                                           AbsDutyCycle);
        /* From non 0% or non 100% enter to 0% or 100%, disable interrupt first 
           and then update compare value */
        if(1U == HandleInfo)
        {
            /* Disable interrupt */
            /* #Violation: Pwm_c_REF_4 */
            SafetyFlag &= Gtm_Pwm_Hal_SetInterrupt(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                                   GTM_PWM_IRQEDGE_ALL,
                                                   FALSE);
            ChannelStatusPtr->DutyIs0Or100 = TRUE;
        }
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */

        /* SWS_Pwm_00150 */
        /* SWS_Pwm_00019:  Set the period and the duty cycle */
        /* SWS_Pwm_00076: Update the period with configured PwmPeriodUpdatedEndperiod */
        /* #Violation: Pwm_c_REF_4 */
        SafetyFlag &= Gtm_Pwm_Hal_SetPeriodDutyCycle(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                        Period,
                                        AbsDutyCycle,
                                        /* #Violation: Pwm_c_REF_4 */
                                        PWM_GET_CHANNEL_UPDATE_MECHANISM(CoreId, ChIndexInCore));

#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
        /* From 0% or 100% enter to non 0% or non 100%, update compare value first,
           and then enable interrupt */
        if(2U == HandleInfo)
        {
            /* Enable interrupt */
            /* #Violation: Pwm_c_REF_4 */
            SafetyFlag &= Gtm_Pwm_Hal_SetInterrupt(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                                   ChannelStatusPtr->InterruptStatus,
                                                   TRUE);
            
            ChannelStatusPtr->DutyIs0Or100 = FALSE;
        }
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */

        PWM_EXIT_CRITICAL_SECTION(Pwm_SetPeriodAndDuty);

#if (PWM_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            (void)Det_ReportRuntimeError(PWM_MODULE_ID, 
                                         PWM_INSTANCE_ID, 
                                         PWM_SET_PERIODANDDUTY_SID, 
                                         PWM_E_SAFETY_CHECK_FAILED);
        }
#else
        MCAL_UNUSED_VAR(SafetyFlag);
#endif /* PWM_SAFETY_ENABLE == STD_ON */
    }
}
#endif /* End of (PWM_SET_PERIOD_AND_DUTY_API \== STD_ON) */

/* SWS_Pwm_10084, SWS_Pwm_20084 */
#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_SetOutputToIdle
 *
 *   Service ID              : 0x04
 *
 *   Description             :  Service sets the PWM output to the configured Idle state.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the PWM
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channel numbers
 *
 *   Return value            : None.
 *
 *   Preconditions           : PWM Module must be initialized..
 *
 *   AUTOSAR_Requirement     : SWS_Pwm_00099.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(void, PWM_PUBLIC_CODE) Pwm_SetOutputToIdle
(
    Pwm_ChannelType ChannelNumber
)
{
    Mcal_CoreType CoreId;
    uint8 ChIndexInCore;
#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
    Pwm_ChannelStatusType* ChannelStatusPtr;
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */

#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ErrValue;
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    boolean SafetyFlag;

    SafetyFlag = TRUE;
    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Pwm_20002, SWS_Pwm_30002 */
    ErrValue = Pwm_CheckDetErrors(ChannelNumber, PWM_SET_OUTPUTTOIDLE_SID, CoreId);

    if(E_OK == ErrValue)
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    {
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        PWM_ENTER_CRITICAL_SECTION(Pwm_SetOutputToIdle);
#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))

        ChannelStatusPtr = PWM_GET_CHANNEL_RAM_PTR(CoreId, ChIndexInCore);

        if(GTM_PWM_IRQEDGE_NONE != ChannelStatusPtr->InterruptStatus)
        {
            /* Disable interrupt */
            /* #Violation: Pwm_c_REF_4 */
            SafetyFlag &= Gtm_Pwm_Hal_SetInterrupt(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                                   GTM_PWM_IRQEDGE_ALL,
                                                   FALSE);
            
            /* Clear interrupt status */
            /* #Violation: Pwm_c_REF_4 */
            Gtm_Pwm_Hal_ClearInterruptStatus(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                             GTM_PWM_IRQEDGE_ALL);

            ChannelStatusPtr->DutyIs0Or100 = TRUE;
        }
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE \== STD_ON) */

        /* SWS_Pwm_00021: Set immediately the output to the configured idle state */
        /* #Violation: Pwm_c_REF_4 */
        SafetyFlag &= Gtm_Pwm_Hal_SetIdleLevel(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                               /* #Violation: Pwm_c_REF_4 */
                                               PWM_GET_CHANNEL_IDLELEVEL(CoreId, ChIndexInCore));
        PWM_EXIT_CRITICAL_SECTION(Pwm_SetOutputToIdle);

#if (PWM_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            (void)Det_ReportRuntimeError(PWM_MODULE_ID, 
                                         PWM_INSTANCE_ID, 
                                         PWM_SET_OUTPUTTOIDLE_SID, 
                                         PWM_E_SAFETY_CHECK_FAILED);
        }
#else
        MCAL_UNUSED_VAR(SafetyFlag);
#endif /* PWM_SAFETY_ENABLE == STD_ON */
    }
}
#endif /* End of (PWM_SET_OUTPUT_TO_IDLE_API \== STD_ON) */

/* SWS_Pwm_10085, SWS_Pwm_20085 */
#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_GetOutputState
 *
 *   Service ID              : 0x05
 *
 *   Description             : Service to read the internal state of the PWM output signal.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the PWM
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channel numbers
 *
 *   Return value            : PWM_HIGH The PWM output state is high
 *                             PWM_LOW The PWM output state is low
 *
 *   Preconditions           : PWM Module must be initialized..
 *
 *   AUTOSAR_Requirement     : SWS_Pwm_00100.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(Pwm_OutputStateType, PWM_PUBLIC_CODE) Pwm_GetOutputState
(
    Pwm_ChannelType ChannelNumber
)
{
    Pwm_OutputStateType  OutputLevel;
    uint8 ChIndexInCore;
    Mcal_CoreType CoreId;
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ErrValue;
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */

    OutputLevel = PWM_LOW;
    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Pwm_20002, SWS_Pwm_30002 */
    ErrValue = Pwm_CheckDetErrors(ChannelNumber, PWM_GET_OUTPUTSTATE_SID, CoreId);

    if(E_OK == ErrValue)
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    {
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        /* SWS_Pwm_00022: Read the internal state of the PWM output signal */
        /* #Violation: Pwm_c_REF_1 */
        OutputLevel = (Pwm_OutputStateType)Gtm_Pwm_Hal_GetOutputLevel(
                                                /* #Violation: Pwm_c_REF_4 */
                                                PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore));
    }
    return OutputLevel;
}
#endif /* End of (PWM_GET_OUTPUT_STATE_API \== STD_ON) */

/* SWS_Pwm_10112, SWS_Pwm_20112 */
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_DisableNotification
 *
 *   Service ID              : 0x06
 *
 *   Description             : Service to disable the PWM signal edge notification.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the PWM
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channel numbers
 *
 *   Return value            : None.
 *
 *   Preconditions           : PWM Module must be initialized..
 *
 *   AUTOSAR_Requirement     : SWS_Pwm_00101.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(void, PWM_PUBLIC_CODE) Pwm_DisableNotification
(
    Pwm_ChannelType ChannelNumber
)
{
    uint8 ChIndexInCore;
    Mcal_CoreType CoreId;
    Pwm_ChannelStatusType* ChannelStatusPtr;
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ErrValue;
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    boolean SafetyFlag;

    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Pwm_20002, SWS_Pwm_30002 */
    ErrValue = Pwm_EnDisableNotificationDetCheck(ChannelNumber, 
                                                 PWM_DISABLENOTIFICATION_SID, CoreId);

    if(E_OK == ErrValue)
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    {
        /* Get the channel index in core */
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        PWM_ENTER_CRITICAL_SECTION(Pwm_DisableNotification);
        /* SWS_Pwm_00023: Disable the signal edge notification*/
        /* Disable interrupt */
        /* #Violation: Pwm_c_REF_4 */
        SafetyFlag = Gtm_Pwm_Hal_SetInterrupt(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                              GTM_PWM_IRQEDGE_ALL,
                                              FALSE);
        
        /* Clear interrupt status */
        /* #Violation: Pwm_c_REF_4 */
        Gtm_Pwm_Hal_ClearInterruptStatus(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                         GTM_PWM_IRQEDGE_ALL);
        ChannelStatusPtr = PWM_GET_CHANNEL_RAM_PTR(CoreId, ChIndexInCore);
        ChannelStatusPtr->InterruptStatus = GTM_PWM_IRQEDGE_NONE;
        PWM_EXIT_CRITICAL_SECTION(Pwm_DisableNotification);

#if (PWM_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            (void)Det_ReportRuntimeError(PWM_MODULE_ID, 
                                         PWM_INSTANCE_ID, 
                                         PWM_DISABLENOTIFICATION_SID, 
                                         PWM_E_SAFETY_CHECK_FAILED);
        }
#else
        MCAL_UNUSED_VAR(SafetyFlag);
#endif /* PWM_SAFETY_ENABLE == STD_ON */
    }
}
#endif /* PWM_NOTIFICATION_SUPPORTED \== STD_ON */

/* SWS_Pwm_10113, SWS_Pwm_20113 */
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
/****************************************************************************************************
 *   Function Name           : Pwm_EnableNotification
 *
 *   Service ID              : 0x07
 *
 *   Description             : Enable the PWM signal edge notification.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the PWM
 *                             Notification: PWM_RISING_EDGE / PWM_FALLING_EDGE / PWM_BOTH_EDGES
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channel numbers
 *
 *   Return value            : None.
 *
 *   Preconditions           : PWM Module must be initialized.
 *
 *   AUTOSAR_Requirement     : SWS_Pwm_00102.
 ****************************************************************************************************/
/* #Violation: Pwm_c_REF_10 */
FUNC(void, PWM_PUBLIC_CODE) Pwm_EnableNotification
(
    Pwm_ChannelType ChannelNumber,
    Pwm_EdgeNotificationType Notification
)
{
    Mcal_CoreType CoreId;
    uint8 ChIndexInCore;
    Pwm_ChannelStatusType* ChannelStatusPtr;
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ErrValue;
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    boolean SafetyFlag;

    SafetyFlag = TRUE;
    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (PWM_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Pwm_20002, SWS_Pwm_30002 */
    ErrValue = Pwm_EnDisableNotificationDetCheck(ChannelNumber, 
                                                 PWM_ENABLENOTIFICATION_SID, CoreId);
    if(E_OK == ErrValue)
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
    {
        ChIndexInCore = PWM_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        ChannelStatusPtr = PWM_GET_CHANNEL_RAM_PTR(CoreId, ChIndexInCore);

        PWM_ENTER_CRITICAL_SECTION(Pwm_EnableNotification);
        /* SWS_Pwm_00081: Cancel pending interrupts */
        /* #Violation: Pwm_c_REF_4 */
        Gtm_Pwm_Hal_ClearInterruptStatus(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                         GTM_PWM_IRQEDGE_ALL);
        /* If the status of 0% or 100% duty cycle flag is set,
         * do not enable the hardware interrupt */
#if (PWM_0_100_INTERRUPT_HANDLE == STD_ON)
        if(FALSE == ChannelStatusPtr->DutyIs0Or100)
#endif /* PWM_INT_FOR_0_100_HANDLE \== STD_OFF */
        {
            /* SWS_Pwm_00024 */
            /* #Violation: Pwm_c_REF_4 */
            SafetyFlag &= Gtm_Pwm_Hal_SetInterrupt(PWM_GET_CHANNEL_OBJECT_PTR(CoreId, ChIndexInCore),
                                                  /* #Violation: Pwm_c_REF_1 */
                                                  (Gtm_Pwm_IrqEdge)Notification,
                                                  TRUE);
        }

        /* Store the edge type and enable the interrupt status variable */
        /* #Violation: Pwm_c_REF_1 */
        ChannelStatusPtr->InterruptStatus = (Gtm_Pwm_IrqEdge)Notification;
        PWM_EXIT_CRITICAL_SECTION(Pwm_EnableNotification);
        
#if (PWM_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            (void)Det_ReportRuntimeError(PWM_MODULE_ID, 
                                         PWM_INSTANCE_ID, 
                                         PWM_ENABLENOTIFICATION_SID, 
                                         PWM_E_SAFETY_CHECK_FAILED);
        }
#else
        MCAL_UNUSED_VAR(SafetyFlag);
#endif /* PWM_SAFETY_ENABLE == STD_ON */

    }
}
#endif /* PWM_NOTIFICATION_SUPPORTED \== STD_ON */

/****************************************************************************************************
*   Function Name           : Pwm_DutyPeriod_ISRHandler
*
*   Service ID              : 0x0F
*
*   Description             : ISR callback functions.It is called by ISR
*
*   Parameters in           : Module: Hardware type. 0: GTM-TOM 1: GTM-ATOM
*                             ModuleIndex: Hardware module index
*                             Channel: Hardware channel index
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant for different channel numbers
*
*   Return value            : None
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, PWM_PRIVATE_CODE) Pwm_DutyPeriod_ISRHandler
(
    uint8 Module, 
    uint8 ModuleIndex, 
    uint8 Channel
)
{
    Mcal_CoreType CoreId;
    uint8 ChIndexInCore;
    uint32 IntEnStatus;
    uint32 IntStatus;
    Gtm_Output_Driver HWChannelObject;
    uint32 LogicChannelIndex;
    uint8 Offset;

    /* #Violation: Pwm_c_REF_4 */
    CoreId = Mcal_GetCoreId();

    if(NULL_PTR != Pwm_ConfigPtr)
    {
        if((NULL_PTR != Pwm_CoreDriverStatusPtr[CoreId]) && 
           (PWM_INITIALIZED == (*Pwm_CoreDriverStatusPtr[CoreId])))
        {
            if(0U == Module)
            {
                Offset = (ModuleIndex * 16U) + Channel;
            }
            else
            {
                Offset = (ModuleIndex * 8U) + Channel;
            }
            
            /* Find logic from hardware and logic channel mapping table */
            LogicChannelIndex = Pwm_ConfigPtr->PwmHwChannelMapPtr[Module][Offset];

            if(0xFFU != LogicChannelIndex)
            {
                if(CoreId == Pwm_ConfigPtr->PwmChannelIdxmapPtr[LogicChannelIndex].Core)
                {
                    HWChannelObject.module = Module;
                    HWChannelObject.moduleIndex = ModuleIndex;
                    HWChannelObject.channel = Channel;
                    ChIndexInCore = Pwm_ConfigPtr->PwmChannelIdxmapPtr[LogicChannelIndex].Index;
    
                    /* Check whether the rsing edge interrupt is triggered */
                    IntEnStatus = Gtm_Pwm_Hal_GetInterruptEnableStatus((const Gtm_Output_Driver *)&HWChannelObject,
                                                                        GTM_PWM_IRQEDGE_RISE);
                    /* Get the edge interrupt status from register */
                    IntStatus = Gtm_Pwm_Hal_GetInterruptStatus((const Gtm_Output_Driver *)&HWChannelObject,
                                                                GTM_PWM_IRQEDGE_RISE);
        
                    /* Check whether the rsing edge interrupt is triggered */
                    if(0x01U == (IntEnStatus & IntStatus))
                    {
                        /* Clear the edge hardware interrupt flag */
                        Gtm_Pwm_Hal_ClearInterruptStatus((const Gtm_Output_Driver *)&HWChannelObject,
                                                        GTM_PWM_IRQEDGE_RISE);
                        /* Call user notification function */
                        Pwm_ConfigPtr->CoreConfigPtr[CoreId]->
                            Pwm_ChannelConfigPtr[ChIndexInCore].NotificationFuncPtr();
                    }
                    /* Check whether the falling edge interrupt is triggered */
                    else
                    {
                        /* Get the edge interrupt enable status from register */
                        IntEnStatus = Gtm_Pwm_Hal_GetInterruptEnableStatus((const Gtm_Output_Driver *)&HWChannelObject,
                                                                            GTM_PWM_IRQEDGE_FALL);
                        /* Get the edge interrupt status from register */
                        IntStatus = Gtm_Pwm_Hal_GetInterruptStatus((const Gtm_Output_Driver *)&HWChannelObject,
                                                                    GTM_PWM_IRQEDGE_FALL);
        
                        /* The interrupt soure of ATOM or TOM is shared, this is used to check whether the 
                        * interrupt is belong to the current channel */
                        if(0x01U == (IntEnStatus & IntStatus))
                        {
                            /* Clear the edge hardware interrupt flag */
                            Gtm_Pwm_Hal_ClearInterruptStatus((const Gtm_Output_Driver *)&HWChannelObject,
                                                            GTM_PWM_IRQEDGE_FALL);
                            /* Call user notification function */
                            Pwm_ConfigPtr->CoreConfigPtr[CoreId]->
                                Pwm_ChannelConfigPtr[ChIndexInCore].NotificationFuncPtr();
                        }
                    }
                }
#if (PWM_DEV_ERROR_DETECT == STD_ON)
                else
                {
                    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID,PWM_ISR_SID,
                                          PWM_E_CORE_CHANNEL_MISMATCH);
                }
#endif /* PWM_DEV_ERROR_DETECT \== STD_ON */
            }
        }
    }
} /* End of API Pwm_DutyPeriod_ISRHandler() */

/* #Violation: Pwm_c_REF_9 */
#define PWM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Pwm_c_REF_2 */
#include "Pwm_MemMap.h"
/****************************************************************************************************
 **                          End of File                                                           **
 ****************************************************************************************************/


