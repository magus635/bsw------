/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Ocu.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : This file contains all API functions of Ocu Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Ocu_c_REF_1:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Ocu_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Ocu_c_REF_3:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Ocu_c_REF_4:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Ocu_c_REF_5:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Ocu_c_REF_6:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Ocu_c_REF_7:MISRAC2012-Rule-10.5; 
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*#Ocu_c_REF_8:CWE-1071; 
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Ocu_c_REF_9:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Ocu_c_REF_10:CertC-DCL00-C;
* Justification: Parameter declared refer to AUTOSAR specifications.
*
*#Ocu_c_REF_11:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*#Ocu_c_REF_12:MISRAC2012-Rule-2.2; 
* Justification: Platform-based design with configurable macros.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* SWS_Ocu_00006:
 * Ocu.c shall include Ocu.h*/
#include "Ocu.h"
#include "Ocu_GeneralTypes.h"
#include "Ocu_Version.h"
#include "Mcall.h"
#include "Det.h"
#include "SchM_Ocu.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (OCU_VENDOR_ID != OCU_CFG_VENDOR_ID)
  #error "Ocu.c : Mismatch in Vendor ID"
#endif /* (OCU_VENDOR_ID !\= OCU_CFG_VENDOR_ID) */

#if (OCU_MODULE_ID != OCU_CFG_MODULE_ID)
  #error "Ocu.c : Mismatch in Module ID"
#endif /* \(OCU_MODULE_ID != OCU_CFG_MODULE_ID) */

#if (OCU_AR_RELEASE_MAJOR_VERSION != OCU_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu.c : Mismatch in Release Major Version"
#endif /* (OCU_AR_RELEASE_MAJOR_VERSION !\= OCU_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (OCU_AR_RELEASE_MINOR_VERSION != OCU_CFG_AR_RELEASE_MINOR_VERSION)
  #error "OCU.c : Mismatch in Release Minor Version"
#endif /* (OCU_AR_RELEASE_MINOR_VERSION !\= OCU_CFG_AR_RELEASE_MINOR_VERSION) */

#if (OCU_AR_RELEASE_REVISION_VERSION != OCU_CFG_AR_RELEASE_REVISION_VERSION)
  #error "OCU.c : Mismatch in Release Revision Version"
#endif /* (OCU_AR_RELEASE_REVISION_VERSION !\= OCU_CFG_AR_RELEASE_REVISION_VERSION) */

#if (OCU_SW_MAJOR_VERSION != OCU_CFG_SW_MAJOR_VERSION)
  #error "OCU.c : Mismatch in Software Major Version"
#endif /* (OCU_SW_MAJOR_VERSION !\= OCU_CFG_SW_MAJOR_VERSION) */

#if (OCU_SW_MINOR_VERSION != OCU_CFG_SW_MINOR_VERSION)
  #error "OCU.c : Mismatch in Software Minor Version"
#endif /* (OCU_SW_MINOR_VERSION !\= OCU_CFG_SW_MINOR_VERSION) */

#if (OCU_SW_PATCH_VERSION != OCU_CFG_SW_PATCH_VERSION)
  #error "Ocu.c : Mismatch in Software Patch Version"
#endif /* \(OCU_SW_PATCH_VERSION != OCU_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
/* #Violation: Ocu_c_REF_2*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

#if (OCU_MAX_CHANNEL_TO_CORE0 != 0U)
/* Global variable to store channel status of core0 */
static VAR(Ocu_ChannelStatusType, OCU_VAR_FAST_CLEARED)
        Ocu_ChannelStatusCore0[OCU_MAX_CHANNEL_TO_CORE0];
/* Global variable to store driver status of core0 */
static VAR(Ocu_InitStateType, OCU_VAR_FAST_CLEARED) Ocu_DriverStatusCore0;
#endif /* OCU_MAX_CHANNEL_TO_CORE0 !\= 0U */

/* #Violation: Ocu_c_REF_2*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"


/* #Violation: Ocu_c_REF_2*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

#if defined(OCU_MAX_CHANNEL_TO_CORE1) && (OCU_MAX_CHANNEL_TO_CORE1 != 0U)
/* Global variable to store channel status of core1 */
static VAR(Ocu_ChannelStatusType, OCU_VAR_FAST_CLEARED)
        Ocu_ChannelStatusCore1[OCU_MAX_CHANNEL_TO_CORE1];
/* Global variable to store driver status of core1 */
static VAR(Ocu_InitStateType, OCU_VAR_FAST_CLEARED) Ocu_DriverStatusCore1;
#endif /* OCU_MAX_CHANNEL_TO_CORE1 !\= 0U */

/* #Violation: Ocu_c_REF_2*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

/* #Violation: Ocu_c_REF_2*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

#if defined(OCU_MAX_CHANNEL_TO_CORE2) && (OCU_MAX_CHANNEL_TO_CORE2 != 0U)
/* Global variable to store channel status of core2 */
static VAR(Ocu_ChannelStatusType, OCU_VAR_FAST_CLEARED)
        Ocu_ChannelStatusCore2[OCU_MAX_CHANNEL_TO_CORE2];
/* Global variable to store driver status of core1 */
static VAR(Ocu_InitStateType, OCU_VAR_FAST_CLEARED) Ocu_DriverStatusCore2;
#endif /* defined(OCU_MAX_CHANNEL_TO_CORE2) && (OCU_MAX_CHANNEL_TO_CORE2 !\= 0U) */

/* #Violation: Ocu_c_REF_2*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

/* #Violation: Ocu_c_REF_2*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

#if defined(OCU_MAX_CHANNEL_TO_CORE3) && (OCU_MAX_CHANNEL_TO_CORE3 != 0U)
/* Global variable to store channel status of core3 */
static VAR(Ocu_ChannelStatusType, OCU_VAR_FAST_CLEARED)
        Ocu_ChannelStatusCore3[OCU_MAX_CHANNEL_TO_CORE3];
/* Global variable to store driver status of core3 */
static VAR(Ocu_InitStateType, OCU_VAR_FAST_CLEARED) Ocu_DriverStatusCore3;
#endif /* defined(OCU_MAX_CHANNEL_TO_CORE3) && (OCU_MAX_CHANNEL_TO_CORE3 !\= 0U) */

/* #Violation: Ocu_c_REF_2*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"


/* #Violation: Ocu_c_REF_2*/
#define OCU_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

static CONSTP2VAR(Ocu_ChannelStatusType, OCU_CONFIG_DATA, OCU_APPL_DATA)
        Ocu_CoreChannelStatusPtr[MCAL_NUMBER_OF_CORES] =
{
        /* A pointer the channel global variable of core0 */
#if (OCU_MAX_CHANNEL_TO_CORE0 != 0U)
        &Ocu_ChannelStatusCore0[0],
#else
        NULL_PTR,
#endif /*(OCU_MAX_CHANNEL_TO_CORE0 !\= 0U)*/
#if (MCAL_NUMBER_OF_CORES >= 2U)
        /* A pointer the channel global variable of core1 */
#if (OCU_MAX_CHANNEL_TO_CORE1 != 0U)
       &Ocu_ChannelStatusCore1[0],
#else
        NULL_PTR,
#endif /*(OCU_MAX_CHANNEL_TO_CORE1 !\= 0U)*/
#endif /* (MCAL_NUMBER_OF_CORES >\= 2U) */
#if (MCAL_NUMBER_OF_CORES >= 3U)
        /* A pointer the channel global variable of core2 */
#if (OCU_MAX_CHANNEL_TO_CORE2 != 0U)
       &Ocu_ChannelStatusCore2[0],
#else
        NULL_PTR,
#endif /*(OCU_MAX_CHANNEL_TO_CORE2 !\= 0U)*/
#endif /* (MCAL_NUMBER_OF_CORES >\= 3U) */
#if (MCAL_NUMBER_OF_CORES >= 4U)
        /* A pointer the channel global variable of core3 */
#if (OCU_MAX_CHANNEL_TO_CORE3 != 0U)
       &Ocu_ChannelStatusCore3[0]
#else
        NULL_PTR
#endif /*(OCU_MAX_CHANNEL_TO_CORE3 !\= 0U)*/
#endif /* (MCAL_NUMBER_OF_CORES >\= 4U) */
};

static CONSTP2VAR(Ocu_InitStateType, OCU_CONFIG_DATA, OCU_APPL_DATA)
        Ocu_CoreDriverStatusPtr[MCAL_NUMBER_OF_CORES] =
{
#if (OCU_MAX_CHANNEL_TO_CORE0 != 0U)
        &Ocu_DriverStatusCore0,
#else
        NULL_PTR,
#endif /*(OCU_MAX_CHANNEL_TO_CORE0 !\= 0U)*/
#if (MCAL_NUMBER_OF_CORES >= 2U)
#if (OCU_MAX_CHANNEL_TO_CORE1 != 0U)
       &Ocu_DriverStatusCore1,
#else
        NULL_PTR,
#endif /*(OCU_MAX_CHANNEL_TO_CORE1 !\= 0U)*/
#endif /* (MCAL_NUMBER_OF_CORES >\= 2U) */
#if (MCAL_NUMBER_OF_CORES >= 3U)
#if (OCU_MAX_CHANNEL_TO_CORE2 != 0U)
       &Ocu_DriverStatusCore2,
#else
        NULL_PTR,
#endif /*(OCU_MAX_CHANNEL_TO_CORE2 !\= 0U)*/
#endif /* (MCAL_NUMBER_OF_CORES >\= 3U) */
#if (MCAL_NUMBER_OF_CORES >= 4U)
#if (OCU_MAX_CHANNEL_TO_CORE3 != 0U)
       &Ocu_DriverStatusCore3
#else
        NULL_PTR
#endif /*(OCU_MAX_CHANNEL_TO_CORE3 !\= 0U)*/
#endif /* (MCAL_NUMBER_OF_CORES >\= 4U) */
};
/* #Violation: Ocu_c_REF_2*/
#define OCU_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

/* #Violation: Ocu_c_REF_2*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

/* Global pointer that point to configuration data structure */
static P2CONST(Ocu_ConfigType,AUTOMATIC,OCU_APPL_CONST) Ocu_ConfigPtr;

/* #Violation: Ocu_c_REF_2*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

/****************************************************************************************************
**                          SchM Critical Section Protection Macros                                **
****************************************************************************************************/
/* Enter critical section macros */
/* #Violation: Ocu_c_REF_1*/
/* #Violation: Ocu_c_REF_9*/
#define OCU_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_##Exclusive_Area()
/* Exit critical section macros */
/* #Violation: Ocu_c_REF_1*/
/* #Violation: Ocu_c_REF_9*/
#define OCU_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_##Exclusive_Area()
/* Get channel global status pointer macros */
/* #Violation: Ocu_c_REF_9*/
#define OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex) \
        &((Ocu_CoreChannelStatusPtr[CoreId])[ChanInCoreIndex])
/* Get channel trigger event macros from const data structure */
/* #Violation: Ocu_c_REF_5*/
/* #Violation: Ocu_c_REF_9*/
#define OCU_GET_CHANNEL_EVENT(CoreId, ChanInCoreIndex) \
    (Ocu_ConfigPtr->CoreConfigPtr[CoreId]->Ocu_ChannelConfigPtr[ChanInCoreIndex].Event)
/* Get channel index in current core */
/* #Violation: Ocu_c_REF_5*/
/* #Violation: Ocu_c_REF_9*/
#define OCU_GET_CHANNEL_INDEX_IN_CORE(LogicChannelId) \
        (Ocu_ConfigPtr->OcuChannelIdxmapPtr[LogicChannelId].IndexInCore)
/* Get channel maximum compare value */
/* #Violation: Ocu_c_REF_5*/
/* #Violation: Ocu_c_REF_9*/
#define OCU_GET_CHANNEL_MAX_VALUE(CoreId, ChanInCoreIndex) \
        (Ocu_ConfigPtr->CoreConfigPtr[CoreId]->Ocu_ChannelConfigPtr[ChanInCoreIndex].MaxCounterValue)
/* Get channel notification callback function pointer */
/* #Violation: Ocu_c_REF_5*/
/* #Violation: Ocu_c_REF_9*/
#define OCU_GET_CHANNEL_NOTIFY_PTR(CoreId, ChanInCoreIndex) \
        (Ocu_ConfigPtr->CoreConfigPtr[CoreId]->Ocu_ChannelConfigPtr[ChanInCoreIndex].NotificationPtr)
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Ocu_c_REF_2*/
#define OCU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"

#if (OCU_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, OCU_PRIVATE_CODE) Ocu_CheckDetErrors
(
    Ocu_ChannelType Channel,
    uint8 ApiSid,
    Mcal_CoreType CoreId
);

static FUNC(Std_ReturnType, OCU_PRIVATE_CODE) Ocu_InitDetCheck
(
    const Ocu_ConfigType* const ConfigPtr, 
    Mcal_CoreType CoreId
);

#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
static Std_ReturnType Ocu_SetAbsoluteThresholdDetCheck
(
    Ocu_ChannelType ChannelNumber,
    Ocu_ValueType ReferenceValue,
    Ocu_ValueType AbsoluteValue
);
#endif /* (OCU_SET_ABSOLUTE_THRESHOLD_API \== STD_ON) */

#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
static Std_ReturnType Ocu_SetRelativeThresholdDetCheck
(
    Ocu_ChannelType ChannelNumber,
    Ocu_ValueType RelativeValue
);
#endif /* (OCU_SET_RELATIVE_THRESHOLD_API \== STD_ON) */

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
static Std_ReturnType Ocu_EnableNotificationDetCheck
(
    Ocu_ChannelType ChannelNumber
);
static Std_ReturnType Ocu_DisableNotificationDetCheck
(
    Ocu_ChannelType ChannelNumber
);
#endif /* (OCU_NOTIFICATION_SUPPORTED \== STD_ON) */

#endif /* (OCU_DEV_ERROR_DETECT \== STD_ON) */

static FUNC(boolean, OCU_PRIVATE_CODE) Ocu_SetCompare
(
    uint32 CompareValue,
    const Gtm_Output_Driver *HWchannelObjectPtr,
    Gtm_Tbu_Ch Timebase,
    Ocu_PinActionType OutputAction
);

static FUNC(boolean, OCU_PRIVATE_CODE) Ocu_StartChannelByAtom
(
  Ocu_ChannelStatusType* const LocalChannelStatusPtr,
  const Gtm_Output_Driver *HWchannelObjectPtr,
  Gtm_Tbu_Ch Timebase
);

/* #Violation: Ocu_c_REF_6*/
static const FUNC_P2VAR(Gtm_Output_Driver, OCU_CODE, OCU_APPL_DATA) Ocu_GetHardwareChannelObjectPtr
(
  Mcal_CoreType CoreId,
  uint8 ChInCoreIndex
);

#if (OCU_DE_INIT_API == STD_ON)
static FUNC(Std_ReturnType, OCU_PRIVATE_CODE) Ocu_DeInitCheck
(
    Mcal_CoreType CoreId
);
#endif /* (OCU_DE_INIT_API \== STD_ON) */

#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
static Ocu_ReturnType Ocu_GetReturnValue
(
    const uint32 PostValue,
    const uint32 StartVal,
    const uint32 CompareVal
);
#endif /* (OCU_SET_ABSOLUTE_THRESHOLD_API \== STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API \== STD_ON) */
/****************************************************************************************************
**                                      Private Function                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Ocu_GetTimebase
*
*   Service ID              : None.
*
*   Description             : Get tbu timebase for the given channel(Only for ATOM).
*
*   Parameters in           : GrpPtr: the group configuration pointer.
*                             DataPtr: pointer to ADC runtime.
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
LOCAL_INLINE FUNC(Gtm_Tbu_Ch, OCU_PRIVATE_CODE) Ocu_GetTimebase
(
  Mcal_CoreType CoreId,
  uint8 ChInCoreIndex
)
{
    uint8 ChannelId;
    uint32 HWConfigIndex;
    Gtm_Tbu_Ch Timebase;

    ChannelId = Ocu_ConfigPtr->CoreConfigPtr[CoreId]->Ocu_ChannelConfigPtr[ChInCoreIndex].ChannelId;
    HWConfigIndex = Ocu_ConfigPtr->OcuChannelIdxmapPtr[ChannelId].HWCfgIndex;
    if(HWConfigIndex < OCU_MAX_CHANNELS)
    {
        Timebase = Ocu_ConfigPtr->Ocu_HWGtmAtomConfigPtr[HWConfigIndex].TimeBase;
    }
    else
    {
/* #Violation: Ocu_c_REF_7*/
        Timebase = (Gtm_Tbu_Ch)0xFFU;
    }
    return Timebase;
}

#if (OCU_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Ocu_CheckDetErrors
*
*   Service ID              : None
*
*   Description             :This API returns the Det error.
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
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(Std_ReturnType, OCU_PRIVATE_CODE) Ocu_CheckDetErrors
(
    Ocu_ChannelType Channel,
    uint8 ApiSid,
    Mcal_CoreType CoreId
)
{
    uint32 CoreChIdx;
    const Ocu_ChConfigType *ChannelConfigPtr;
    Std_ReturnType ErrValue;
    ErrValue = E_NOT_OK;

    if (OCU_MAX_CHANNELS <= Channel)
    {
        /* Report to DET module */
        (void) Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, ApiSid,
                                OCU_E_PARAM_INVALID_CHANNEL);
    }
    else if (OCU_INITIALIZED != (*Ocu_CoreDriverStatusPtr[CoreId]))
    {
        (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                              ApiSid,
                              OCU_E_UNINIT);
    }
    else
    {
        CoreChIdx = Ocu_ConfigPtr->OcuChannelIdxmapPtr[Channel].IndexInCore;
        ChannelConfigPtr = &Ocu_ConfigPtr->CoreConfigPtr[CoreId]->
                                Ocu_ChannelConfigPtr[CoreChIdx];

        if(ChannelConfigPtr->ChannelId != Channel)
        {
            (void) Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, ApiSid,
                                   OCU_E_CORE_CHANNEL_MISMATCH);
        }
        else
        {
            ErrValue = E_OK;
        }
    }

    return ErrValue;
}

/****************************************************************************************************
*   Function Name           : Ocu_InitDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Ocu_Init.
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
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(Std_ReturnType, OCU_PRIVATE_CODE) Ocu_InitDetCheck
(
    const Ocu_ConfigType* const ConfigPtr, 
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;

    ErrValue = E_NOT_OK;

    if (NULL_PTR == ConfigPtr)
    {
        /* SWS_Ocu_00016 */
        (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                OCU_SID_INIT,
                                OCU_E_INIT_FAILED);
    }
    else if (NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId])
    {
        (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                OCU_SID_INIT,
                                OCU_E_CORE_NOT_CONFIGURED);
    }
    else if (OCU_UNINITIALIZED != (*Ocu_CoreDriverStatusPtr[CoreId]))
    {
        /* SWS_Ocu_00043 */
        (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                OCU_SID_INIT,
                                OCU_E_ALREADY_INITIALIZED);
    }
    else
    {
        ErrValue = E_OK;
    }
    return ErrValue;
}

#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Ocu_SetAbsoluteThresholdDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Ocu_SetAbsoluteThreshold.
*
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *                             ReferenceValue: Value given by the upper layer and used as a base to
 *                                  determine whether to call the notification before the function
 *                                  exits or not.
 *                             AbsoluteValue : Value to compare with the content of the counter. This
 *                                  value is in ticks
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
static Std_ReturnType Ocu_SetAbsoluteThresholdDetCheck
(
    Ocu_ChannelType ChannelNumber,
    Ocu_ValueType ReferenceValue,
    Ocu_ValueType AbsoluteValue
)
{
    Mcal_CoreType CoreId;
    Std_ReturnType ErrValue;
    uint8 ChanInCoreIndex;

/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_SETABSOLUTETHRESHOLD, CoreId);

    if(E_OK == ErrValue)
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        if(ReferenceValue > Ocu_ConfigPtr->CoreConfigPtr[CoreId]->
                            Ocu_ChannelConfigPtr[ChanInCoreIndex].MaxCounterValue)
        {
            (void) Det_ReportError (OCU_MODULE_ID,
                                    OCU_INSTANCE_ID,
                                    OCU_SID_SETABSOLUTETHRESHOLD,
                                    OCU_E_PARAM_REF_VALUE);
            ErrValue = E_NOT_OK;
        }
        else if(AbsoluteValue > Ocu_ConfigPtr->CoreConfigPtr[CoreId]->
                Ocu_ChannelConfigPtr[ChanInCoreIndex].MaxCounterValue)
        {
            (void) Det_ReportError (OCU_MODULE_ID,
                                    OCU_INSTANCE_ID,
                                    OCU_SID_SETABSOLUTETHRESHOLD,
                                    OCU_E_PARAM_COMPARE_VALUE);
            ErrValue = E_NOT_OK;
        }
/* #Violation: Ocu_c_REF_8*/
        else
        {
            /* Do nothing */
        }
    }

  return ErrValue;
}
#endif /* (OCU_SET_ABSOLUTE_THRESHOLD_API \== STD_ON) */

#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Ocu_SetRelativeThresholdDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Ocu_SetRelativeThreshold.
*
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *                             RelativeValue: Value to use for computing the new threshold.
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
static Std_ReturnType Ocu_SetRelativeThresholdDetCheck
(
    Ocu_ChannelType ChannelNumber,
    Ocu_ValueType RelativeValue
)
{
    Mcal_CoreType CoreId;
    Std_ReturnType ErrValue;
    uint8 ChanInCoreIndex;

/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_SETRELATIVETHRESHOLD, CoreId);

    if(E_OK == ErrValue)
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        if(RelativeValue > Ocu_ConfigPtr->CoreConfigPtr[CoreId]->
                Ocu_ChannelConfigPtr[ChanInCoreIndex].MaxCounterValue)
        {
            (void) Det_ReportError (OCU_MODULE_ID,
                                    OCU_INSTANCE_ID,
                                    OCU_SID_SETRELATIVETHRESHOLD,
                                    OCU_E_PARAM_COMPARE_VALUE);
            ErrValue = E_NOT_OK;
        }
    }

  return ErrValue;
}
#endif /* (OCU_SET_RELATIVE_THRESHOLD_API \== STD_ON) */

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/****************************************************************************************************
*   Function Name           : Ocu_DisableNotificationDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Ocu_EnableNotification.
*
*   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
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
static Std_ReturnType Ocu_EnableNotificationDetCheck
(
    Ocu_ChannelType ChannelNumber
)
{
    Mcal_CoreType CoreId;
    Std_ReturnType ErrValue;
    uint8 ChanInCoreIndex;

/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_ENABLENOTIFICATION, CoreId);

    if(E_OK == ErrValue)
    {

/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        /* SWS_Ocu_00114:
           Notification function is the NULL pointer */
/* #Violation: Ocu_c_REF_4*/
        if(NULL_PTR == OCU_GET_CHANNEL_NOTIFY_PTR(CoreId, ChanInCoreIndex))
        {
            (void)Det_ReportError(OCU_MODULE_ID,
                                  OCU_INSTANCE_ID,
                                  OCU_SID_ENABLENOTIFICATION,
                                  OCU_E_NO_VALID_NOTIF);
            ErrValue = E_NOT_OK;
        }
    }

  return ErrValue;
}
/****************************************************************************************************
*   Function Name           : Ocu_DisableNotificationDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Ocu_DisableNotification.
*
*   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
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
static Std_ReturnType Ocu_DisableNotificationDetCheck
(
    Ocu_ChannelType ChannelNumber
)
{
    Mcal_CoreType CoreId;
    Std_ReturnType ErrValue;
    uint8 ChanInCoreIndex;

/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_DISABLENOTIFICATION, CoreId);

    if(E_OK == ErrValue)
    {

/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        /* SWS_Ocu_00114:
           Notification function is the NULL pointer */
/* #Violation: Ocu_c_REF_4*/
        if(NULL_PTR == OCU_GET_CHANNEL_NOTIFY_PTR(CoreId, ChanInCoreIndex))
        {
            (void)Det_ReportError(OCU_MODULE_ID,
                                  OCU_INSTANCE_ID,
                                  OCU_SID_DISABLENOTIFICATION,
                                  OCU_E_NO_VALID_NOTIF);
            ErrValue = E_NOT_OK;
        }
    }

  return ErrValue;
}
#endif /* (OCU_NOTIFICATION_SUPPORTED \== STD_ON) */

#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

#if (OCU_DE_INIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Ocu_DeInitCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Ocu_DeInit.
*
*   Parameters in           :CoreId: Core ID.
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
static Std_ReturnType Ocu_DeInitCheck
(
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
    uint8 MaxChannel;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType const* LocalChannelStatusPtr;

    ErrValue = E_OK;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    if(OCU_INITIALIZED != (*Ocu_CoreDriverStatusPtr[CoreId]))
    {
        /* SWS_Ocu_00050 */
        (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                              OCU_SID_DEINIT,
                              OCU_E_UNINIT);
        ErrValue = E_NOT_OK;
    }
    else
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
        MaxChannel = Ocu_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels;

        for (ChanInCoreIndex = 0U;
             ((ChanInCoreIndex < MaxChannel) && (E_OK == ErrValue)); ChanInCoreIndex++)
        {
            /* Get the channel status variable pointer */
            LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);

            if(OCU_CHANNEL_RUNNING == LocalChannelStatusPtr->ChannelStatus)
            {
#if (OCU_DEV_ERROR_DETECT == STD_ON)
                /* SWS_Ocu_00137 */
                (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                       OCU_SID_DEINIT,
                                       OCU_E_PARAM_INVALID_STATE);
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
                ErrValue = E_NOT_OK;
            }
        }
    }
  return ErrValue;
}
#endif /* (OCU_DE_INIT_API \== STD_ON) */


#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_GetReturnValue
 *
 *   Service ID              : None
 *
 *   Description             :calculate the return value for SetAbsoluteThreshold and 
 *                                      SetRealativeThreshold
 *
 *   Parameters in           : PostValue : value to mark end of ref. interval
 *                             StartVal : counter value at the time of writing
 *                             CompareVal: value to mark start of ref. interval
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : Ocu_ReturnType.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant .
 *
 *   Return value            : uint32: compare value IN/OUT reference interval.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : .
 ****************************************************************************************************/
static Ocu_ReturnType Ocu_GetReturnValue
(
    const uint32 PostValue,
    const uint32 StartVal,
    const uint32 CompareVal
)
{
    Ocu_ReturnType RetVal;

    /* check if compare match will happen before counter roll-over */
    if (StartVal <= CompareVal)
    {
        /* counter is not expected to roll-over */
        /* check if post-update value is inside the compare match interval */
        if ((StartVal <= PostValue) && (PostValue < CompareVal))
        {
            RetVal = OCU_CM_IN_REF_INTERVAL;
        }
        else
        {
            RetVal = OCU_CM_OUT_REF_INTERVAL;
        }
    }
    else    /*counter has rolled-over*/
    {
        /* check if post-update value is outside the compare match interval */
        if ((PostValue < StartVal) && (PostValue > CompareVal))
        {
            RetVal = OCU_CM_OUT_REF_INTERVAL;
        }
        else
        {
            RetVal = OCU_CM_IN_REF_INTERVAL;
        }
    }
    return RetVal;
}
#endif /* (OCU_SET_ABSOLUTE_THRESHOLD_API \== STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Ocu_SetCompare
 *
 *   Service ID              : None
 *
 *   Description             :set compare value for atom channel
 *
 *   Parameters in           : CompareValue : value to mark end of ref. interval
 *                             HWchannelObjectPtr : Hardware channel object
 *                             ReferenceValue: value to mark start of ref. interval
 *                             Timebase : Tbu time base
 *                             OutputAction : Pinaction required on next compare match
 *   Parameters inout        : None.
 *
 *   Parameters out          : boolean.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channels .
 *
 *   Return value            : boolean: Whether write register success.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : .
 ****************************************************************************************************/
static FUNC(boolean, OCU_PRIVATE_CODE) Ocu_SetCompare
(
    uint32 CompareValue,
/* #Violation: Ocu_c_REF_10*/
    const Gtm_Output_Driver *HWchannelObjectPtr,
    Gtm_Tbu_Ch Timebase,
    Ocu_PinActionType OutputAction
)
{
    Gtm_Ocu_Output_Behavior BehaviorControl;
    Gtm_Ocu_Control CmpValue;
    boolean Ocu_RegRet;

    CmpValue.cm0 = 0U;
    CmpValue.cm1 = 0U;

    BehaviorControl.somcSignalLevelControl = (uint8)OutputAction;

    if(GTM_TBU_CH_TS0 == Timebase)
    {
        /* Set channel strategy is compare to ccu0 */
        BehaviorControl.somcCompareStrategy = GTM_SOMCCTRL_CCU0TS0;
        /* Set compare value */
        CmpValue.cm0 = CompareValue;
    }
    else
    {
        /* Set channel strategy is compare to ccu1 */
        BehaviorControl.somcCompareStrategy = GTM_SOMCCTRL_CCU1TS12;
        /* Set compare value */
        CmpValue.cm1 = CompareValue;
    }

    /* Call low level interface to set output behavior */
    Ocu_RegRet = Gtm_Ocu_Hal_SetOutputBehavior(HWchannelObjectPtr,
                                               &CmpValue,
                                               &BehaviorControl);
    return Ocu_RegRet;
}

/****************************************************************************************************
 *   Function Name           : Ocu_StartChannelByAtom.
 *
 *   Service ID              : None.
 *
 *   Description             :Start logic channel which is based on GTM-ATOM.
 *
 *   Parameters in           :HWchannelObjectPtr: Pointer to hwardware channel object.
 *                            Timebase: Tbu time base.
 *
 *   Parameters inout        : LocalChannelStatusPtr: Pointer to global channel variable.
 *
 *   Parameters out          : boolean.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channels .
 *
 *   Return value            : boolean: Init channel by ATOM success.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(boolean, OCU_PRIVATE_CODE) Ocu_StartChannelByAtom
(
  Ocu_ChannelStatusType* const LocalChannelStatusPtr,
/* #Violation: Ocu_c_REF_10*/
  const Gtm_Output_Driver *HWchannelObjectPtr,
  Gtm_Tbu_Ch Timebase
)
{
    uint32 CurrentCounter;
    uint32 AbsoluteValue;
    boolean Ocu_RegRet;

    Ocu_RegRet = TRUE;
    /* Clear interrupt status */
    Gtm_Ocu_Hal_ClearInterruptStatus(HWchannelObjectPtr, GTM_ATOM_IRQTYPE_ALL);
    /* Due to hardware limitations(GTM), it may need to set a temporary comparison value,
     * and interrupt must participate in this case to re-set actual compare value */
    if(GTM_TBU_CH_TS0 == Timebase)
    {
        /* Time base 0 is used to compare to CM0, so enable the interrupt of CM0 */
        Ocu_RegRet &= Gtm_Ocu_Hal_SetInterrupt(HWchannelObjectPtr, TRUE, FALSE);
    }
    else
    {
        /* Time base 0 or time base 1 is used to compare to CM1,
         * so enable the interrupt of CM1 */
        Ocu_RegRet &= Gtm_Ocu_Hal_SetInterrupt(HWchannelObjectPtr, FALSE, TRUE);
    }
    /* Get compare value from ram */
    AbsoluteValue = LocalChannelStatusPtr->CompareValue;
    /* Get current counter */
    CurrentCounter = Gtm_Ocu_Hal_GetCounterValue(Timebase);

    /* The new compare value must not be larger than the range of the
    * total time base value, because of hardware limitation */
    if(((CurrentCounter - AbsoluteValue) & (OCU_ATOM_COUNTER_RANGE_MASK))
        > OCU_TBU_BORDER_PAST_FUTURE)
    {
        /* The new compare value is in future for hardware */
        LocalChannelStatusPtr->AtomReProg = FALSE;
        Ocu_RegRet &= Ocu_SetCompare(AbsoluteValue,
                                    HWchannelObjectPtr,
                                    Timebase,
                                    LocalChannelStatusPtr->OutputAction);
    }
    else
    {
        /* The new compare value is in past for hardware,
        * need to reset compare value */
        LocalChannelStatusPtr->AtomReProg = TRUE;
        Ocu_RegRet &= Ocu_SetCompare((AbsoluteValue + OCU_TBU_BORDER_PAST_FUTURE)
                                    &(OCU_ATOM_COUNTER_RANGE_MASK),
                                    HWchannelObjectPtr,
                                    Timebase,
                                    OCU_DISABLE);
    }
    /* Enable the channel and output */
    Ocu_RegRet &= Gtm_Ocu_Hal_SetChannelOutput(HWchannelObjectPtr,
                                               TRUE,
                                               TRUE);
    return Ocu_RegRet;
}

/****************************************************************************************************
 *   Function Name           : Ocu_GetHardwareChannelObjectPtr.
 *
 *   Service ID              : None.
 *
 *   Description             :Get hardware channel object pointer.
 *
 *   Parameters in           :CoreId: Current core ID.
 *                            ChInCoreIndex: Index of the channel in the current core.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different channels .
 *
 *   Return value            : Pointer to hardware channel object.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_6*/
static const FUNC_P2VAR(Gtm_Output_Driver, OCU_CODE, OCU_APPL_DATA) Ocu_GetHardwareChannelObjectPtr
(
  Mcal_CoreType CoreId,
  uint8 ChInCoreIndex
)
{
    uint8 ChannelId;
    uint32 HWConfigIndex;
    const Gtm_Output_Driver *ChannelObjectPtr;

    ChannelId = Ocu_ConfigPtr->CoreConfigPtr[CoreId]->Ocu_ChannelConfigPtr[ChInCoreIndex].ChannelId;

    HWConfigIndex = Ocu_ConfigPtr->OcuChannelIdxmapPtr[ChannelId].HWCfgIndex;

    ChannelObjectPtr = &Ocu_ConfigPtr->Ocu_HWGtmAtomConfigPtr[HWConfigIndex].HWChannelIndex;
    return ChannelObjectPtr;
}
/****************************************************************************************************
 **                                    Global Function                                             **
 ****************************************************************************************************/
/* SWS_Ocu_00124 */
#if (OCU_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_GetVersionInfo
 *
 *   Service ID              : 0x09
 *
 *   Description             : This service returns the version information of this module.
 *
 *   Parameters in           : None
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : VersionInfoPtr: Pointer to where to store the version information of
 *                                 this module.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :SWS_Ocu_00122 SWS_Ocu_00123 SWS_Ocu_00124 SWS_Ocu_00125 SWS_Ocu_00126
 *
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_GetVersionInfo 
(
/* #Violation: Ocu_c_REF_6*/
/* #Violation: Ocu_c_REF_10*/
    P2VAR(Std_VersionInfoType, AUTOMATIC, OCU_APPL_DATA) VersionInfoPtr
)
{
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == VersionInfoPtr)
    {
        /* SWS_Ocu_00126 */
        (void) Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_GETVERSIONINFO,
                                OCU_E_PARAM_POINTER);
    }
    else
#endif /* (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* Update vendor ID, module ID, SW major, SW minor and SW patch version values
         in the pointer parameter. */
        /* Get OCU Vendor ID */
        VersionInfoPtr->vendorID = OCU_VENDOR_ID;
        /* Get OCU Module ID */
        VersionInfoPtr->moduleID = OCU_MODULE_ID;
        /* Get OCU module Software major version */
        VersionInfoPtr->sw_major_version = (uint8) OCU_SW_MAJOR_VERSION;
        /* Get OCU module Software minor version */
        VersionInfoPtr->sw_minor_version = (uint8) OCU_SW_MINOR_VERSION;
        /* Get OCU module Software patch version */
        VersionInfoPtr->sw_patch_version = (uint8) OCU_SW_PATCH_VERSION;
    }
}/* End of Ocu_GetVersionInfo*/
#endif /* (OCU_VERSION_INFO_API \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Ocu_Init
 *
 *   Service ID              : 0x00
 *
 *   Description             : Initialize all internals variables  and the used OCU structure
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
 *   AUTOSAR_Requirement     : SWS_Ocu_00036 SWS_Ocu_00095.
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_Init
(
/* #Violation: Ocu_c_REF_10*/
    P2CONST(Ocu_ConfigType, AUTOMATIC, OCU_APPL_CONST) ConfigPtr
)
{
    Mcal_CoreType CoreId;
    uint8 MaxChannel;
    uint8 ChanInCoreIndex;
    const Ocu_ChConfigType *ChannelConfigPtr;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    uint32 HWConfigIndex;
    uint8 ChannelId;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    boolean Ocu_RegRet;
    Std_ReturnType LockStatus;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

    Ocu_RegRet = TRUE;
/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* Check the errors of Ocu_Init */
    ErrValue = Ocu_InitDetCheck(ConfigPtr, CoreId);
    if (E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
        Ocu_ConfigPtr = ConfigPtr;

        MaxChannel = ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels;

        ChannelConfigPtr = ConfigPtr->CoreConfigPtr[CoreId]->Ocu_ChannelConfigPtr;

        /* Loop to initialize all hardware channels */
        for (ChanInCoreIndex = 0U; ChanInCoreIndex < MaxChannel; ChanInCoreIndex++)
        {
            /* Find the channel status variable */
            LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);
            /* Find logic channel index */
            ChannelId = ChannelConfigPtr[ChanInCoreIndex].ChannelId;
            /* Find the hardware configuration mapping index of logic channel */
            HWConfigIndex = ConfigPtr->OcuChannelIdxmapPtr[ChannelId].HWCfgIndex;

            /* #Violation: Ocu_c_REF_4*/
            if(OCU_COMPARE_EVENT_ADC == OCU_GET_CHANNEL_EVENT(CoreId, ChanInCoreIndex))
            {
                /* Set default compare match action to do nothing */
                LocalChannelStatusPtr->OutputAction = OCU_TOGGLE;
            }
            else
            {
                /* Set default compare match action to do nothing */
                LocalChannelStatusPtr->OutputAction = OCU_DISABLE;
            }

            HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_OCU);
            if(E_OK == LockStatus)
            {
                /* Initialize the GTM-ATOM channel */
                Ocu_RegRet &= Gtm_Ocu_Hal_InitChannel(HWchannelObjectPtr,
                                    &ConfigPtr->Ocu_HWGtmAtomConfigPtr[HWConfigIndex].HWChannelConfig);
                /* #Violation: Ocu_c_REF_4*/
                if(OCU_COMPARE_EVENT_PIN == OCU_GET_CHANNEL_EVENT(CoreId, ChanInCoreIndex))
                {
                    /* Disable channel and enable output for Ocu_SetPinState */
                    Ocu_RegRet &= Gtm_Ocu_Hal_SetChannelOutput(HWchannelObjectPtr,
                                                            FALSE,
                                                            TRUE);
                }
                Mcal_ReleaseLock(MCAL_LOCK_ID_OCU);
            }
            else
            {
                /* Get lock failed */
                Ocu_RegRet = FALSE;
                break;
            }
#if (STD_ON == OCU_SAFETY_ENABLE)
            if (TRUE == Ocu_RegRet)
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
            {
                /* Store the compareValue to global variable */
                LocalChannelStatusPtr->CompareValue = ChannelConfigPtr[ChanInCoreIndex].DefaultCompareValue;
                /* SWS_Ocu_00039:
                * Set channel status to stopped */
                LocalChannelStatusPtr->ChannelStatus = OCU_CHANNEL_STOPPED;
                /* SWS_Ocu_00040:
                * Disable all notifications */
                LocalChannelStatusPtr->NotifyEnabled = FALSE;
            }
        }
#if (STD_ON == OCU_SAFETY_ENABLE)
        if (TRUE != Ocu_RegRet)
        {
            (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_INIT, OCU_E_WRITE_REGISTER);
        }
        else
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
        {
            /* Set the driver status */
            (*Ocu_CoreDriverStatusPtr[CoreId]) = OCU_INITIALIZED;
        }
    }
/* #Violation: Ocu_c_REF_4*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
}

/* SWS_Ocu_00049 */
#if (OCU_DE_INIT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_DeInit
 *
 *   Service ID              : 0x01
 *
 *   Description             : This function de-initializes the OCU module.
 *
 *   Parameters in           : None
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
 *   AUTOSAR_Requirement     :SWS_Ocu_00045 SWS_Ocu_00046 SWS_Ocu_00047 SWS_Ocu_00048 SWS_Ocu_00049
 *                            SWS_Ocu_00050 SWS_Ocu_00136 SWS_Ocu_00137
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_DeInit
(
    void
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    boolean Ocu_RegRet;
    uint8 Ocu_ChInCore;
    Std_ReturnType ErrValue;

    Ocu_RegRet = TRUE;
/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    /* Check the errors of Ocu_Init */
    ErrValue = Ocu_DeInitCheck(CoreId);
    if (E_OK == ErrValue)
    {
    Ocu_ChInCore = Ocu_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannels;
        for (ChanInCoreIndex = 0U; ChanInCoreIndex < Ocu_ChInCore; ChanInCoreIndex++)
        {
            HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);

            /* Clear the interrupt status */
            Gtm_Ocu_Hal_ClearInterruptStatus(HWchannelObjectPtr,
                                            GTM_ATOM_IRQTYPE_ALL);
            /* SWS_Ocu_00047:
            * Disable the interrupt */
            Ocu_RegRet &= Gtm_Ocu_Hal_SetInterrupt(HWchannelObjectPtr, FALSE, FALSE);

            LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);
            /* Disable all notifications */
            LocalChannelStatusPtr->NotifyEnabled = FALSE;
        }

#if (STD_ON == OCU_SAFETY_ENABLE)
        if (TRUE != Ocu_RegRet)
        {
            (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_DEINIT, 
                                            OCU_E_WRITE_REGISTER);
        }
        else
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
        {
            /* Set the driver status */
            (*Ocu_CoreDriverStatusPtr[CoreId]) = OCU_UNINITIALIZED;
        }
    }
/* #Violation: Ocu_c_REF_5*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
}
#endif /* (OCU_DE_INIT_API \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Ocu_StartChannel
 *
 *   Service ID              : 0x02
 *
 *   Description             : Service to start an OCU channel.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *
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
 *   AUTOSAR_Requirement     : SWS_Ocu_00052 SWS_Ocu_00053 SWS_Ocu_00054 SWS_Ocu_00055 SWS_Ocu_00056
 *    SWS_Ocu_00057
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_StartChannel 
(
    Ocu_ChannelType ChannelNumber
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    Gtm_Tbu_Ch Timebase;
    boolean Ocu_RegRet;
    Std_ReturnType LockStatus;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

    Ocu_RegRet = TRUE;
/* #Violation: Ocu_c_REF_4*/
    CoreId     = Mcal_GetCoreId();
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00056:
     * Parameter ChannelNumber is invalid */
    /* SWS_Ocu_00057:
     * Driver is not initialized */
    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_STARTCHANNEL, CoreId);
    if(E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        /* Get the channel status variable pointer */
        LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);
        /* SWS_Ocu_00055:
        * Called on a channel in the state "RUNINNG" */
#if (OCU_DEV_ERROR_DETECT == STD_ON)
        if (OCU_CHANNEL_RUNNING == LocalChannelStatusPtr->ChannelStatus)
        {
            (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                         OCU_SID_STARTCHANNEL,
                                         OCU_E_BUSY);
        }
        else
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
        {
            HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);
            OCU_ENTER_CRITICAL_SECTION(Ocu_StartChannel);
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_OCU);
            if(E_OK == LockStatus)
            {
                Timebase = Ocu_GetTimebase(CoreId, ChanInCoreIndex);
                /* #Violation: Ocu_c_REF_12*/
                Ocu_RegRet &= Ocu_StartChannelByAtom(LocalChannelStatusPtr,
                                                    HWchannelObjectPtr, 
                                                    Timebase);
                Mcal_ReleaseLock(MCAL_LOCK_ID_OCU);
            }
            else
            {
                /* Get lock failed */
                Ocu_RegRet = FALSE;
            }
            if (TRUE == Ocu_RegRet)
            {
                /* SWS_Ocu_00054:
                * Set channel status to running state */
                LocalChannelStatusPtr->ChannelStatus = OCU_CHANNEL_RUNNING;
                OCU_EXIT_CRITICAL_SECTION(Ocu_StartChannel);
            }
            else
            {
                OCU_EXIT_CRITICAL_SECTION(Ocu_StartChannel);
#if (STD_ON == OCU_SAFETY_ENABLE)
                (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_STARTCHANNEL, 
                                            OCU_E_WRITE_REGISTER);
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
            }
        }
    }
/* #Violation: Ocu_c_REF_4*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
}

/****************************************************************************************************
 *   Function Name           : Ocu_StopChannel
 *
 *   Service ID              : 0x03
 *
 *   Description             : Service to stop an OCU channel.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *
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
 *   AUTOSAR_Requirement     : SWS_Ocu_00059 SWS_Ocu_00060 SWS_Ocu_00061 SWS_Ocu_00062 SWS_Ocu_00063
 *                             SWS_Ocu_00064 SWS_Ocu_00065
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_StopChannel 
(
    Ocu_ChannelType ChannelNumber
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    boolean Ocu_RegRet;
    Std_ReturnType LockStatus;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

    Ocu_RegRet = TRUE;
/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00064:
       ChannelNumber is invalid */
    /* SWS_Ocu_00065: 
       Driver is not initialized */
    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_STOPCHANNEL, CoreId);

    if(E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        /* Get the channel status variable pointer */
        LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);

        /* SWS_Ocu_00063:
         * In the state "STOPPED", then the function shall leave without any action */
        if(OCU_CHANNEL_RUNNING == LocalChannelStatusPtr->ChannelStatus)
        {
            HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);
            OCU_ENTER_CRITICAL_SECTION(Ocu_StopChannel);
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_OCU);
            if(E_OK == LockStatus)
            {
                /* Compare event is pin, Due to hardware characteristics, only the channel
                    * can be disabled, but the output must be enabled, Otherwise, the SL cannot
                    * control the output, and Ocu_SetPinState cannot set pin state correctly */
                /* #Violation: Ocu_c_REF_4*/
                if(OCU_COMPARE_EVENT_PIN == OCU_GET_CHANNEL_EVENT(CoreId, ChanInCoreIndex))
                {
                    /* Set pin event to hold the level */
                    Ocu_RegRet &= Gtm_Ocu_Hal_SetSignalLevelControl(HWchannelObjectPtr,
                                                        GTM_OCU_SLCTRL_NOCHANGE);
                    /* Disable channel and enable output for Ocu_SetPinState */
                    Ocu_RegRet &= Gtm_Ocu_Hal_SetChannelOutput(HWchannelObjectPtr,
                                                    FALSE,
                                                    TRUE);
                }
                else
                {
                    /* Disable channel and output */
                    Ocu_RegRet &= Gtm_Ocu_Hal_SetChannelOutput(HWchannelObjectPtr,
                                                    FALSE,
                                                    TRUE);
                }
                if(TRUE == Ocu_RegRet)
                {
                    /* Set channel pin action to stopped */
                    LocalChannelStatusPtr->OutputAction = OCU_DISABLE;
                    /* SWS_Ocu_00062:
                    * Set channel status to stopped */
                    LocalChannelStatusPtr->ChannelStatus = OCU_CHANNEL_STOPPED;
                    /* Set channel compare value to default compare value */
                    LocalChannelStatusPtr->CompareValue = Ocu_ConfigPtr->CoreConfigPtr[CoreId]->
                                                        Ocu_ChannelConfigPtr[ChanInCoreIndex].
                                                        DefaultCompareValue;
                }
                Mcal_ReleaseLock(MCAL_LOCK_ID_OCU);
            }
            else
            {
                /* Get lock failed */
                Ocu_RegRet = FALSE;
            }

            OCU_EXIT_CRITICAL_SECTION(Ocu_StopChannel);
#if (STD_ON == OCU_SAFETY_ENABLE)
            if (TRUE != Ocu_RegRet)
            {
                (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_STOPCHANNEL, 
                                             OCU_E_WRITE_REGISTER);
            }
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
        }
    }
/* #Violation: Ocu_c_REF_4*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
}

/* SWS_Ocu_00070 */
#if (OCU_SET_PIN_STATE_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_SetPinState
 *
 *   Service ID              : 0x04
 *
 *   Description             : Service to set immediately the level of the pin associated to an OCU
 *                               channel.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *                             PinState: OCU_LOW, OCU_HIGH
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
 *   AUTOSAR_Requirement     : SWS_Ocu_00067 SWS_Ocu_00068 SWS_Ocu_00069 SWS_Ocu_00070 SWS_Ocu_00071
 *    SWS_Ocu_00072 SWS_Ocu_00073 SWS_Ocu_00074 SWS_Ocu_00075
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_SetPinState 
(
    Ocu_ChannelType ChannelNumber,
    Ocu_PinStateType PinState
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType const* LocalChannelStatusPtr;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    boolean Ocu_RegRet;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

    Ocu_RegRet = TRUE;
/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00071: 
      Parameter ChannelNumber is invalid */
    /* SWS_Ocu_00074:
       Driver is not initialized*/
    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_SETPINSTATE, CoreId);

    if(E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* Get channel index in the core */
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        /* Get channel status variable pointer */
        LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);
#if (OCU_DEV_ERROR_DETECT == STD_ON)
        /* Only the channel compare event is configured as pin output,
         * this api can be called  */
/* #Violation: Ocu_c_REF_4*/
        if(OCU_COMPARE_EVENT_PIN != OCU_GET_CHANNEL_EVENT(CoreId, ChanInCoreIndex))
        {
            (void)Det_ReportError(OCU_MODULE_ID,
                                  OCU_INSTANCE_ID,
                                  OCU_SID_SETPINSTATE,
                                  OCU_E_PARAM_NO_PIN);
            ErrValue = E_NOT_OK;
        }
        /* Check the validation of pin output status */
        else if (OCU_HIGH < PinState)
        {
            /* SWS_Ocu_00073:
               Parameter PinState is invalid */
            (void)Det_ReportError(OCU_MODULE_ID,
                                  OCU_INSTANCE_ID,
                                  OCU_SID_SETPINSTATE,
                                  OCU_E_PARAM_INVALID_STATE);
            ErrValue = E_NOT_OK;
        }
/* #Violation: Ocu_c_REF_8*/
        else
        {
            /* Do nothing */
        }
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    }

#if (OCU_DEV_ERROR_DETECT == STD_ON)
    if(E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* SWS_Ocu_00069:
          * Used only if the channel is not in the RUNNING state */
        if(OCU_CHANNEL_STOPPED == LocalChannelStatusPtr->ChannelStatus)
        {
            HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);

            /* Control the output by SL(Channel has been disabled and Output has been enabled) */
            /* SWS_Ocu_00067:
                Set pin level */
            Ocu_RegRet &= Gtm_Ocu_Hal_SetSignalLevel(HWchannelObjectPtr, (Gtm_SignalState)PinState);
#if (STD_ON == OCU_SAFETY_ENABLE)
            if (TRUE != Ocu_RegRet)
            {
                (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_SETPINSTATE, 
                                             OCU_E_WRITE_REGISTER);
            }
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
        }
        else
        {
#if (OCU_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(OCU_MODULE_ID,
                                  OCU_INSTANCE_ID,
                                  OCU_SID_SETPINSTATE,
                                  OCU_E_PARAM_INVALID_STATE);
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
        }
    }
/* #Violation: Ocu_c_REF_4*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
}
#endif /* (OCU_SET_PIN_STATE_API \== STD_ON) */

/* SWS_Ocu_00079 */
#if (OCU_SET_PIN_ACTION_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_SetPinAction
 *
 *   Service ID              : 0x05
 *
 *   Description             : Service to indicate the driver what shall be done automatically by
 *                              hardware (if supported) upon compare match.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *                             Ocu_PinActionType: OCU_SET_LOW, OCU_SET_HIGH, OCU_TOGGLE, OCU_DISABLE
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
 *   AUTOSAR_Requirement     : SWS_Ocu_00077 SWS_Ocu_00078 SWS_Ocu_00079 SWS_Ocu_00080 SWS_Ocu_00081
 *    .SWS_Ocu_00082 SWS_Ocu_00083 SWS_Ocu_00084
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_SetPinAction
(
    Ocu_ChannelType ChannelNumber,
    Ocu_PinActionType OutputAction
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    boolean Ocu_RegRet;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

    Ocu_RegRet = TRUE;
/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00080:
       Parameter ChannelNumber is invalid */
    /* SWS_Ocu_00083:
       Driver is not initialized */
    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_SETPINACTION, CoreId);

    if (E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        /* Get channel status variable pointer */
        LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);
    }

#if (OCU_DEV_ERROR_DETECT == STD_ON)
    if (E_OK == ErrValue)
    {
/* #Violation: Ocu_c_REF_4*/
        if (OCU_COMPARE_EVENT_PIN != OCU_GET_CHANNEL_EVENT(CoreId, ChanInCoreIndex))
        {
            /* SWS_Ocu_00081:
               The pin is not associated with the channel */
            (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID,
                                  OCU_SID_SETPINACTION,
                                  OCU_E_PARAM_NO_PIN);
            ErrValue = E_NOT_OK;
        }
        else if (OutputAction > OCU_TOGGLE)
        {
            /* SWS_Ocu_00082:
               Parameter OutputAction is invalid */
            (void)Det_ReportError(OCU_MODULE_ID, OCU_INSTANCE_ID, 
                                  OCU_SID_SETPINACTION,
                                  OCU_E_PARAM_INVALID_ACTION);
            ErrValue = E_NOT_OK;
        }
/* #Violation: Ocu_c_REF_8*/
        else
        {
            /* Do nothing */
        }
    }

    if (E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
        HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);
        OCU_ENTER_CRITICAL_SECTION(Ocu_SetPinAction);
         /* SWS_Ocu_00077:
            Call low level interface to set pin action */

        Ocu_RegRet &= Gtm_Ocu_Hal_SetSignalLevelControl(HWchannelObjectPtr,
                                                       (uint8)OutputAction);
        if (TRUE == Ocu_RegRet)
        {
            /* Store the pin action */
            LocalChannelStatusPtr->OutputAction = OutputAction;
            OCU_EXIT_CRITICAL_SECTION(Ocu_SetPinAction);
        }
        else
        {
            OCU_EXIT_CRITICAL_SECTION(Ocu_SetPinAction);
#if (STD_ON == OCU_SAFETY_ENABLE)
            (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_SETPINACTION, 
                                         OCU_E_WRITE_REGISTER);
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
        }
    }
/* #Violation: Ocu_c_REF_4*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
}
#endif /* (OCU_SET_PIN_ACTION_API \== STD_ON) */

/* SWS_Ocu_00088 */
#if (OCU_GET_COUNTER_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_GetCounter
 *
 *   Service ID              : 0x06
 *
 *   Description             : Service to read the current value of the counter.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : Ocu_ValueType.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Ocu_ValueType CounterValue.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Ocu_00086 SWS_Ocu_00087 SWS_Ocu_00088 SWS_Ocu_00089 SWS_Ocu_00090
 *     SWS_Ocu_00085
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(Ocu_ValueType, OCU_PUBLIC_CODE) Ocu_GetCounter 
(
    Ocu_ChannelType ChannelNumber
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ValueType CounterValue; 
    Gtm_Tbu_Ch Timebase;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

    /* SWS_Ocu_00089 SWS_Ocu_00090 */
    CounterValue = 0U;
/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00089:
       Parameter ChannelNumber is invalid */
    /* SWS_Ocu_00090:
       Driver is not initialized */
    ErrValue = Ocu_CheckDetErrors(ChannelNumber, OCU_SID_GETCOUNTER, CoreId);
    if(E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        Timebase = Ocu_GetTimebase(CoreId, ChanInCoreIndex);

        /* Get current counter */
        CounterValue = Gtm_Ocu_Hal_GetCounterValue(Timebase);
    }
    /* SWS_Ocu_00086:
       Return the value of the counter of the channel */
    return CounterValue;
}
#endif /* (OCU_GET_COUNTER_API \== STD_ON) */

/* SWS_Ocu_00094 */
#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_SetAbsoluteThreshold
 *
 *   Service ID              : 0x07
 *
 *   Description             : Service to set the value of the channel threshold using an absolute
 *                              input data.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *                             ReferenceValue: Value given by the upper layer and used as a base to
 *                                  determine whether to call the notification before the function
 *                                  exits or not.
 *                             AbsoluteValue : Value to compare with the content of the counter. This
 *                                  value is in ticks
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
 *   AUTOSAR_Requirement     : SWS_Ocu_00091 SWS_Ocu_00092 SWS_Ocu_00093 SWS_Ocu_00094 SWS_Ocu_00095
 *     SWS_Ocu_00096 SWS_Ocu_00097 SWS_Ocu_00098
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(Ocu_ReturnType, OCU_PUBLIC_CODE) Ocu_SetAbsoluteThreshold
(
    Ocu_ChannelType ChannelNumber,
    Ocu_ValueType ReferenceValue,
    Ocu_ValueType AbsoluteValue
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    uint32 CurrentCounter;
    Ocu_ReturnType IntervalStatus;
    Gtm_Tbu_Ch Timebase;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    boolean Ocu_RegRet;

    IntervalStatus = OCU_CM_OUT_REF_INTERVAL;
    Ocu_RegRet = TRUE;
    /* #Violation: Ocu_c_REF_4*/
    CoreId     = Mcal_GetCoreId();
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00095 :
       Driver is not initialized */
    /* SWS_Ocu_00096:
       Parameter ChannelNumber is invalid */
    ErrValue = Ocu_SetAbsoluteThresholdDetCheck(ChannelNumber, ReferenceValue, AbsoluteValue);

    if(E_OK == ErrValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        /* Get channel status variable pointer */
        LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);
        Timebase = Ocu_GetTimebase(CoreId, ChanInCoreIndex);

        OCU_ENTER_CRITICAL_SECTION(Ocu_SetAbsoluteThreshold);
        /* Store the compare value to ram */
        LocalChannelStatusPtr->CompareValue = AbsoluteValue;
        /* Get counter before setting */
        CurrentCounter = Gtm_Ocu_Hal_GetCounterValue(Timebase);
        HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);
        /* If the new compare value is in the future */
        if(((CurrentCounter - AbsoluteValue) & (OCU_ATOM_COUNTER_RANGE_MASK))
            > OCU_TBU_BORDER_PAST_FUTURE)
        {
            /* The new compare value is in future for hardware */
            LocalChannelStatusPtr->AtomReProg = FALSE;
            /* SWS_Ocu_00092:
                Set the channel threshold */
            Ocu_RegRet &= Ocu_SetCompare(AbsoluteValue,
                            HWchannelObjectPtr,
                            Timebase,
                            LocalChannelStatusPtr->OutputAction);
        }
        else
        {
            /* The new compare value is in past for hardware,
                * need to reset compare value */
            LocalChannelStatusPtr->AtomReProg = TRUE;
            /* SWS_Ocu_00092:
                Set the channel threshold */
            Ocu_RegRet &= Ocu_SetCompare((AbsoluteValue + OCU_TBU_BORDER_PAST_FUTURE)
                            &(OCU_ATOM_COUNTER_RANGE_MASK),
                            HWchannelObjectPtr,
                            Timebase,
                            OCU_DISABLE);
        }
        if (TRUE == Ocu_RegRet)
        {
            /* Get counter after set */
            CurrentCounter = Gtm_Ocu_Hal_GetCounterValue(Timebase);
            /* Whether the compare match will occur (or has
                already occured) during the current Reference Interval, as a result
                of setting the new threshold value. */
            IntervalStatus = Ocu_GetReturnValue(CurrentCounter, 
                                                ReferenceValue,
                                                AbsoluteValue);
            OCU_EXIT_CRITICAL_SECTION(Ocu_SetAbsoluteThreshold);
        }
        else
        {
            IntervalStatus = OCU_CM_REF_ERROR;
            OCU_EXIT_CRITICAL_SECTION(Ocu_SetAbsoluteThreshold);
#if (STD_ON == OCU_SAFETY_ENABLE)
            (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_SETABSOLUTETHRESHOLD, 
                                         OCU_E_WRITE_REGISTER);
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
        }
    }
/* #Violation: Ocu_c_REF_4*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
    /* SWS_Ocu_00098:
       Return a status to indicate the caller whether the compare match will
       occur (or has already occured) during the current Reference Interval */
    return IntervalStatus;
}
#endif /* (OCU_SET_ABSOLUTE_THRESHOLD_API \== STD_ON) */

/* SWS_Ocu_00103 */
#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_SetRelativeThreshold
 *
 *   Service ID              : 0x08
 *
 *   Description             : Service to set the value of the channel threshold relative to the
 *                                      current value of the counter.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
 *                             RelativeValue: Value to use for computing the new threshold.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : Ocu_ReturnType.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Ocu_ReturnType OCU_CM_OUT_REF_INTERVAL OCU_CM_IN_REF_INTERVAL.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Ocu_00100 SWS_Ocu_00101 SWS_Ocu_00102 SWS_Ocu_00103 SWS_Ocu_00104
 *     SWS_Ocu_00105 SWS_Ocu_00106 SWS_Ocu_00107
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(Ocu_ReturnType, OCU_PUBLIC_CODE) Ocu_SetRelativeThreshold
(
    Ocu_ChannelType ChannelNumber,
    Ocu_ValueType RelativeValue
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    uint32 CompareValue;
    uint32 ReferenceValue;
    Ocu_ReturnType ErrValue;
    uint32 CounterValueRead0;
    Gtm_Tbu_Ch Timebase;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    boolean Ocu_RegRet;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType DetReturnValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

    /* Initialize return counter to 0 */
    ErrValue = OCU_CM_OUT_REF_INTERVAL;
    Ocu_RegRet = TRUE;
/* #Violation: Ocu_c_REF_4*/
    CoreId     = Mcal_GetCoreId();
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00104:
       Driver is not initialized */
    /* SWS_Ocu_00105: 
       Parameter ChannelNumber is invalid */
    DetReturnValue = Ocu_SetRelativeThresholdDetCheck(ChannelNumber, RelativeValue);

    if(E_OK == DetReturnValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);

        /* Get channel status variables pointer */
        LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);

        Timebase = Ocu_GetTimebase(CoreId, ChanInCoreIndex);

        OCU_ENTER_CRITICAL_SECTION(Ocu_SetRelativeThreshold);

        /* Get current counter */
        ReferenceValue = Gtm_Ocu_Hal_GetCounterValue(Timebase);

        /* SWS_Ocu_00101:
           Add RelativeValue to the value of the counter */
        CompareValue = ReferenceValue + RelativeValue;
/* #Violation: Ocu_c_REF_4*/
        if (CompareValue > OCU_GET_CHANNEL_MAX_VALUE(CoreId, ChanInCoreIndex))
        {
/* #Violation: Ocu_c_REF_4*/
            CompareValue = CompareValue - OCU_GET_CHANNEL_MAX_VALUE(CoreId, ChanInCoreIndex);
        }
        LocalChannelStatusPtr->CompareValue = CompareValue;

        HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);
        /* Get counter before setting */
        CounterValueRead0 = Gtm_Ocu_Hal_GetCounterValue(Timebase);

        /* If the new compare value is in the future */
        if (((CounterValueRead0 - CompareValue) & (OCU_ATOM_COUNTER_RANGE_MASK))
                > OCU_TBU_BORDER_PAST_FUTURE)
        {
            /* The new compare value is in future for hardware */
            LocalChannelStatusPtr->AtomReProg = FALSE;
            Ocu_RegRet &= Ocu_SetCompare(CompareValue,
                                        HWchannelObjectPtr,
                                        Timebase,
                                        LocalChannelStatusPtr->OutputAction);
        }
        else
        {
            /* The new compare value is in past for hardware,
                * need to reset compare value */
            LocalChannelStatusPtr->AtomReProg = TRUE;
            Ocu_RegRet &= Ocu_SetCompare((CompareValue + OCU_TBU_BORDER_PAST_FUTURE)
                                        &(OCU_ATOM_COUNTER_RANGE_MASK),
                                        HWchannelObjectPtr,
                                        Timebase,
                                        OCU_DISABLE);
        }
        if (TRUE == Ocu_RegRet)
        {
            /* Get counter after set */
            CounterValueRead0 = Gtm_Ocu_Hal_GetCounterValue(Timebase);
            /* Whether the compare match will occur (or has
            already occured) during the current Reference Interval, as a result
            of setting the new threshold value. */
            ErrValue = Ocu_GetReturnValue(CounterValueRead0, ReferenceValue,
                                        CompareValue);
            OCU_EXIT_CRITICAL_SECTION(Ocu_SetRelativeThreshold);
        }
        else
        {
            ErrValue = OCU_CM_REF_ERROR;
            OCU_EXIT_CRITICAL_SECTION(Ocu_SetRelativeThreshold);
#if (STD_ON == OCU_SAFETY_ENABLE)
            (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, OCU_SID_SETRELATIVETHRESHOLD, 
                                         OCU_E_WRITE_REGISTER);
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
        }
    }
/* #Violation: Ocu_c_REF_4*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
    /* SWS_Ocu_00106:
       Return a status to indicate the caller whether the compare match will
       occur (or has already occured) during the current Reference Interval */
    return ErrValue;
}
#endif /* (OCU_SET_RELATIVE_THRESHOLD_API \== STD_ON) */

/* SWS_Ocu_00111 */
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_DisableNotification
 *
 *   Service ID              : 0x0a
 *
 *   Description             : This service is used to disable notifications from an OCU channel.
 *
 *   Parameters in           : ChannelNumber: Numeric identifier of the OCU channel.
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
 *   AUTOSAR_Requirement     : SWS_Ocu_00109 SWS_Ocu_00110 SWS_Ocu_00111 SWS_Ocu_00112 SWS_Ocu_00113
 *    .SWS_Ocu_00114
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_DisableNotification
(
    Ocu_ChannelType ChannelNumber
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType DetReturnValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00112:
       Driver is not initialized */
    /* SWS_Ocu_00113: 
       Parameter ChannelNumber is invalid */
    DetReturnValue = Ocu_DisableNotificationDetCheck(ChannelNumber);

    if(E_OK == DetReturnValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);
        
        OCU_ENTER_CRITICAL_SECTION(Ocu_DisableNotification);
        /* SWS_Ocu_00109:
           Set notification status variables to FALSE,
           then notification is disabled */
        LocalChannelStatusPtr->NotifyEnabled = FALSE;
        OCU_EXIT_CRITICAL_SECTION(Ocu_DisableNotification);
    }
}
#endif

/* SWS_Ocu_00118 */
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/****************************************************************************************************
 *   Function Name           : Ocu_EnableNotification
 *
 *   Service ID              : 0x0b
 *
 *   Description             : This service is used to enable notifications from an OCU channel.
 *
 *   Parameters in           : Numeric identifier of the OCU channel.
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
 *   AUTOSAR_Requirement     : SWS_Ocu_00116 SWS_Ocu_00117 SWS_Ocu_00118 SWS_Ocu_00119 SWS_Ocu_00120
 *    .SWS_Ocu_00121
 ****************************************************************************************************/
/* #Violation: Ocu_c_REF_11*/
FUNC(void, OCU_PUBLIC_CODE) Ocu_EnableNotification
(
    Ocu_ChannelType ChannelNumber
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
#if (OCU_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType DetReturnValue;
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */

/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

#if (OCU_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Ocu_00119:
       Driver is not initialized */
    /* SWS_Ocu_00120: 
       Parameter ChannelNumber is invalid */
    DetReturnValue = Ocu_EnableNotificationDetCheck(ChannelNumber);

    if(E_OK == DetReturnValue)
#endif /* End of (OCU_DEV_ERROR_DETECT \== STD_ON) */
    {
/* #Violation: Ocu_c_REF_4*/
        ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(ChannelNumber);
        LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);

        OCU_ENTER_CRITICAL_SECTION(Ocu_EnableNotification);
        /* SWS_Ocu_00116:
           Enable the OCU compare match notification */
        LocalChannelStatusPtr->NotifyEnabled = TRUE;
        OCU_EXIT_CRITICAL_SECTION(Ocu_EnableNotification);
    }
}
#endif

/****************************************************************************************************
 *   Function Name           : Ocu_Gtm_Atom_CompareMatch_ISRHandler
 *
 *   Service ID              : 0xE0U
 *
 *   Description             : ISR handler.
 *
 *   Parameters in           : ModuleIndex: Hardware module index for Ocu channel.
 *                             Channel:     Hardware module channel for Ocu channel.
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
 *   AUTOSAR_Requirement     : 
 ****************************************************************************************************/
FUNC(void, OCU_PUBLIC_CODE) Ocu_Gtm_Atom_CompareMatch_ISRHandler
(
    uint8 ModuleIndex,  
    uint8 Channel
)
{
    Mcal_CoreType CoreId;
    uint8 ChanInCoreIndex;
    uint32 IntStatus;
    uint32 IntEnStatus;
    Ocu_ChannelStatusType *LocalChannelStatusPtr;
    uint32 AbsoluteValue;
    const Gtm_Output_Driver *HWchannelObjectPtr;
    Gtm_Tbu_Ch Timebase;
    boolean Ocu_RegRet;
    uint8 Offset;
    uint32 LogicChannel;

    Ocu_RegRet = TRUE;
/* #Violation: Ocu_c_REF_4*/
    CoreId = Mcal_GetCoreId();

    if(OCU_INITIALIZED == (*Ocu_CoreDriverStatusPtr[CoreId]))
    {
        Offset = (ModuleIndex * 8U) + Channel;
        /* Find logic from hardware and logic channel mapping table */
        LogicChannel = Ocu_ConfigPtr->OcuHwChannelMapPtr[Offset];
        if (0xFFU != LogicChannel)
        {
#if (OCU_DEV_ERROR_DETECT == STD_ON)
            if (CoreId != Ocu_ConfigPtr->OcuChannelIdxmapPtr[LogicChannel].Core)
            {
                (void)Det_ReportError(OCU_MODULE_ID,
                                      OCU_INSTANCE_ID,
                                      OCU_SID_GTM_ATOM_COMPAREMATCH_ISHANDLER,
                                      OCU_E_CORE_CHANNEL_MISMATCH);
            }
            else
#endif /* (OCU_DEV_ERROR_DETECT \== STD_ON) */
            {
/* #Violation: Ocu_c_REF_4*/
                ChanInCoreIndex = OCU_GET_CHANNEL_INDEX_IN_CORE(LogicChannel);
                LocalChannelStatusPtr = OCU_GET_CHANNEL_RAM_PTR(CoreId, ChanInCoreIndex);
                HWchannelObjectPtr = Ocu_GetHardwareChannelObjectPtr(CoreId, ChanInCoreIndex);
                /* Get channel interrupt enable status */
                IntEnStatus = Gtm_Ocu_Hal_GetInterruptEnableStatus(HWchannelObjectPtr,
                                                                GTM_ATOM_IRQTYPE_ALL);
                /* Get current channel hardware interrupt flag */
                IntStatus = Gtm_Ocu_Hal_GetInterruptStatus(HWchannelObjectPtr,
                                                        GTM_ATOM_IRQTYPE_ALL);
                /* If interrupt is belong to the current channel,
                * execute the last process of interrupt handle */
                if ((0U != IntEnStatus) && (IntEnStatus == (IntEnStatus & IntStatus)))
                {
                    /* Clear the interrupt status */
                    Gtm_Ocu_Hal_ClearInterruptStatus(HWchannelObjectPtr,
                                                    GTM_ATOM_IRQTYPE_ALL);
                    if ((OCU_CHANNEL_STOPPED != LocalChannelStatusPtr->ChannelStatus))
                    {
                        Timebase = Ocu_GetTimebase(CoreId, ChanInCoreIndex);
                        AbsoluteValue = LocalChannelStatusPtr->CompareValue;
                        /* If need to re-set the target compare value */
                        if (TRUE == LocalChannelStatusPtr->AtomReProg)
                        {
                            /* The interrupt is triggered next time which is the actual
                            * time point of compare event */
                            LocalChannelStatusPtr->AtomReProg = FALSE;
                            /* Re-set the compare value, and set compare event */
                            Ocu_RegRet &= Ocu_SetCompare(AbsoluteValue,
                                                         HWchannelObjectPtr,
                                                         Timebase,
                                                         LocalChannelStatusPtr->OutputAction);
                        }
                        else
                        {
                            LocalChannelStatusPtr->AtomReProg = TRUE;
/* #Violation: Ocu_c_REF_4*/
                            if (OCU_COMPARE_EVENT_PIN == OCU_GET_CHANNEL_EVENT(CoreId, ChanInCoreIndex))
                            {
                                /* After Ocu_SetOutputAction is called, it just do once operation */
                                LocalChannelStatusPtr->OutputAction = OCU_DISABLE;
                            }
                            /* Need re-set compare value, current do nothing */
                            Ocu_RegRet &= Ocu_SetCompare((AbsoluteValue + OCU_TBU_BORDER_PAST_FUTURE) &
                                                         (OCU_ATOM_COUNTER_RANGE_MASK),
                                                         HWchannelObjectPtr,
                                                         Timebase, OCU_DISABLE);
                            /* If notification is enabled and pin action is valid,
                            * call user's notification function */
                            if (TRUE == LocalChannelStatusPtr->NotifyEnabled)
                            {
                                Ocu_ConfigPtr->CoreConfigPtr[CoreId]->
                                Ocu_ChannelConfigPtr[ChanInCoreIndex].NotificationPtr();
                            }
                        }
#if (STD_ON == OCU_SAFETY_ENABLE)
                        if (TRUE != Ocu_RegRet)
                        {
                            (void)Det_ReportRuntimeError(OCU_MODULE_ID, OCU_INSTANCE_ID, 
                                OCU_SID_GTM_ATOM_COMPAREMATCH_ISHANDLER, OCU_E_WRITE_REGISTER);
                        }
#endif /* STD_ON \== OCU_SAFETY_ENABLE */
                    }
                }
            }
        }
    }
/* #Violation: Ocu_c_REF_4*/
    MCAL_UNUSED_VAR(Ocu_RegRet);
}

/* #Violation: Ocu_c_REF_2*/
#define OCU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Ocu_c_REF_3*/
#include "Ocu_MemMap.h"
/****************************************************************************************************
 **                          End of File                                                            **
 ****************************************************************************************************/


