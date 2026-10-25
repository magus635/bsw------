/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Gpt.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all API functions of Gpt Driver
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
*#Gpt_c_REF_2:MISRAC2012-Rule-11.4; 
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Gpt_c_REF_3:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of 
* the driver must be placed.
*
*#Gpt_c_REF_4:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Gpt_c_REF_5:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Gpt_c_REF_6:CertC-DCL02-C;
* Justification: Company-specific naming conventions  are applied. Developers will not be confused.
*
*#Gpt_c_REF_7:CWE-1071; 
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Gpt_c_REF_8:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Gpt_c_REF_9:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Gpt_c_REF_10:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*#Gpt_c_REF_11:MISRAC2012-Rule-2.1; 
* Justification: Code review ensures the compliance with rule.
*
*#Gpt_c_REF_12:MISRAC2012-Rule-10.5; 
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* SWS_Gpt_00293 */
#include "Gpt.h"
#include "Gpt_Version.h"
#include "Mcall.h"
#include "Mcall_Cfg.h"
/* SWS_Gpt_00375 */
#include "Det.h"
/* Included for the declaration of the critical section protection functions */
#include "SchM_Gpt.h"


/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (GPT_VENDOR_ID != GPT_CFG_VENDOR_ID)
  #error "Gpt.c : Mismatch in Vendor ID"
#endif /* GPT_VENDOR_ID != GPT_CFG_VENDOR_ID */

#if (GPT_MODULE_ID != GPT_CFG_MODULE_ID)
  #error "Gpt.c : Mismatch in Module ID"
#endif /* \(GPT_MODULE_ID != GPT_CFG_MODULE_ID) */

#if (GPT_AR_RELEASE_MAJOR_VERSION != GPT_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt.c : Mismatch in Release Major Version"
#endif /* GPT_AR_RELEASE_MAJOR_VERSION != GPT_CFG_AR_RELEASE_MAJOR_VERSION */

#if (GPT_AR_RELEASE_MINOR_VERSION != GPT_CFG_AR_RELEASE_MINOR_VERSION)
  #error "GPT.c : Mismatch in Release Minor Version"
#endif /* GPT_AR_RELEASE_MINOR_VERSION != GPT_CFG_AR_RELEASE_MINOR_VERSION */

#if (GPT_AR_RELEASE_REVISION_VERSION != GPT_CFG_AR_RELEASE_REVISION_VERSION)
  #error "GPT.c : Mismatch in Release Revision Version"
#endif /* GPT_AR_RELEASE_REVISION_VERSION != GPT_CFG_AR_RELEASE_REVISION_VERSION */

#if (GPT_SW_MAJOR_VERSION != GPT_CFG_SW_MAJOR_VERSION)
  #error "GPT.c : Mismatch in Software Major Version"
#endif /* GPT_SW_MAJOR_VERSION != GPT_CFG_SW_MAJOR_VERSION */

#if (GPT_SW_MINOR_VERSION != GPT_CFG_SW_MINOR_VERSION)
  #error "GPT.c : Mismatch in Software Minor Version"
#endif /* GPT_SW_MINOR_VERSION != GPT_CFG_SW_MINOR_VERSION */

#if (GPT_SW_PATCH_VERSION != GPT_CFG_SW_PATCH_VERSION)
  #error "Gpt.c : Mismatch in Software Patch Version"
#endif /* \(GPT_SW_PATCH_VERSION != GPT_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                               Private Macros Definitions                                        **
****************************************************************************************************/
/* Enter critical section macros */
/* #Violation: Gpt_c_REF_4 */
#define GPT_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_##Exclusive_Area()
/* Exit critical section macros */
/* #Violation: Gpt_c_REF_4 */
#define GPT_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_##Exclusive_Area()
/* Get channel global status pointer macros */
/* #Violation: Gpt_c_REF_5 */
#define GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex) \
        &((Gpt_CoreChannelStatusPtr[CoreId])[ChInCoreIndex])
/* Get channel maximum counter value */
/* #Violation: Gpt_c_REF_5 */
#define GPT_GET_CHANNEL_MAX_VALUE(CoreId, ChanInCoreIndex) \
        (Gpt_ConfigPtr->CoreConfigPtr[CoreId]->Gpt_ChannelConfigPtr[ChanInCoreIndex].MaxTickValue)
/* Get hardware configuration index */
/* #Violation: Gpt_c_REF_5 */
#define GPT_GET_HWCONFIG_MAPINDEX(LogicChannelId) \
        (Gpt_ConfigPtr->GptChannelIdxmapPtr[LogicChannelId].HwCfgIndex)
/* Get GTM hardware channel object pointer */
/* #Violation: Gpt_c_REF_5 */        
#define GPT_GET_GTM_CHANNEL_OBJECT_PTR(HwCfgMapIndex) \
        (&(Gpt_ConfigPtr->GptHwGtmConfigPtr[HwCfgMapIndex].HwChannelIndex))        
/* Get basetimer hardware channel object pointer */
/* #Violation: Gpt_c_REF_5 */      
#define GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex) \
        (Gpt_ConfigPtr->GptHwBaseTimerConfigPtr[HwCfgMapIndex].HwChannelIndexPtr)
/* Get hardware channel class */
/* #Violation: Gpt_c_REF_5 */      
#define GPT_GET_HW_CLASS(CoreId, ChInCoreIndex) \
        (Gpt_ConfigPtr->CoreConfigPtr[CoreId]->Gpt_ChannelConfigPtr[ChInCoreIndex].HwClass)
/* Get channel index in core */
/* #Violation: Gpt_c_REF_5 */
#define GPT_GET_CHANNEL_INDEX_IN_CORE(LogicChannelId) \
        Gpt_ConfigPtr->GptChannelIdxmapPtr[LogicChannelId].Index
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/* Get wakeup enable configuration */
#define GPT_GET_WAKEUP_ENABLE_CONFIG(CoreId, ChInCoreIndex) \
        (Gpt_ConfigPtr->CoreConfigPtr[CoreId]->Gpt_ChannelConfigPtr[ChInCoreIndex].WakeupEnable)
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */
/* Report runtime error */
/* #Violation: Gpt_c_REF_5 */
#define GPT_DET_RUNTIME_ERROR_REPORT(ApiSid, ErrCode) \
        (void)Det_ReportRuntimeError(GPT_MODULE_ID, GPT_INSTANCE_ID, ApiSid, ErrCode)
/* Report error */
/* #Violation: Gpt_c_REF_5 */
#define GPT_DET_ERROR_REPORT(ApiSid, ErrCode) \
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, ApiSid, ErrCode)
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
/* Global variables of core0 */
/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */      
#include "Gpt_MemMap.h"

#if (GPT_MAX_CHANNEL_TO_CORE0 != 0U)
/* Global variables of all channels of core0 */
static VAR(Gpt_ChannelStatusType, GPT_VAR_FAST_CLEARED)
        Gpt_ChannelStatusCore0[GPT_MAX_CHANNEL_TO_CORE0];
/* Global variables of driver status of core0 */
static VAR(Gpt_DriverStateType, GPT_VAR_FAST_CLEARED) Gpt_DriverStatusCore0;
#endif /* GPT_MAX_CHANNEL_TO_CORE0 != 0U */

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */    
#include "Gpt_MemMap.h"  

/* Global variables of core1 */
/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */    
#include "Gpt_MemMap.h"  

#if defined(GPT_MAX_CHANNEL_TO_CORE1) && (GPT_MAX_CHANNEL_TO_CORE1 != 0U)
/* Global variables of all channels of core1 */
static VAR(Gpt_ChannelStatusType, GPT_VAR_FAST_CLEARED)
        Gpt_ChannelStatusCore1[GPT_MAX_CHANNEL_TO_CORE1];
/* Global variables of driver status of core1 */
static VAR(Gpt_DriverStateType, GPT_VAR_FAST_CLEARED) Gpt_DriverStatusCore1;
#endif /* defined(GPT_MAX_CHANNEL_TO_CORE1) \&& (GPT_MAX_CHANNEL_TO_CORE1 != 0U) */

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */      
#include "Gpt_MemMap.h"


/* Global variables of core2 */
/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */      
#include "Gpt_MemMap.h"    

#if defined(GPT_MAX_CHANNEL_TO_CORE2) && (GPT_MAX_CHANNEL_TO_CORE2 != 0U)
/* Global variables of all channels of core2 */
static VAR(Gpt_ChannelStatusType, GPT_VAR_FAST_CLEARED)
        Gpt_ChannelStatusCore2[GPT_MAX_CHANNEL_TO_CORE2];
/* Global variables of driver status of core2 */
static VAR(Gpt_DriverStateType, GPT_VAR_FAST_CLEARED) Gpt_DriverStatusCore2;
#endif /* defined(GPT_MAX_CHANNEL_TO_CORE2) \&& (GPT_MAX_CHANNEL_TO_CORE2 != 0U) */

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */      
#include "Gpt_MemMap.h"


/* Global variables of core3 */
/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */     
#include "Gpt_MemMap.h" 

#if defined(GPT_MAX_CHANNEL_TO_CORE3) && (GPT_MAX_CHANNEL_TO_CORE3 != 0U)
/* Global variables of all channels of core3 */
static VAR(Gpt_ChannelStatusType, GPT_VAR_FAST_CLEARED)
        Gpt_ChannelStatusCore3[GPT_MAX_CHANNEL_TO_CORE3];
/* Global variables of driver status of core3 */
static VAR(Gpt_DriverStateType, GPT_VAR_FAST_CLEARED) Gpt_DriverStatusCore3;
#endif /* defined(GPT_MAX_CHANNEL_TO_CORE3) \&& (GPT_MAX_CHANNEL_TO_CORE3 != 0U) */

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */     
#include "Gpt_MemMap.h" 


/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */     
#include "Gpt_MemMap.h" 

/* An array containing pointers to global variables of all channels of the core */
/* #Violation: Gpt_c_REF_8 */
static CONSTP2VAR(Gpt_ChannelStatusType, GPT_CONFIG_DATA, GPT_APPL_DATA)
        Gpt_CoreChannelStatusPtr[MCAL_NUMBER_OF_CORES] =
{
        /* A pointer the channel global variable of core0 */
#if (GPT_MAX_CHANNEL_TO_CORE0 != 0U)
        &Gpt_ChannelStatusCore0[0],
#else
        NULL_PTR,
#endif /*GPT_MAX_CHANNEL_TO_CORE0 != 0U */
#if (MCAL_NUMBER_OF_CORES >= 2U)
        /* A pointer the channel global variable of core1 */
#if (GPT_MAX_CHANNEL_TO_CORE1 != 0U)
       &Gpt_ChannelStatusCore1[0],
#else
        NULL_PTR,
#endif /* GPT_MAX_CHANNEL_TO_CORE1 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 2U */
#if (MCAL_NUMBER_OF_CORES >= 3U)
        /* A pointer the channel global variable of core2 */
#if (GPT_MAX_CHANNEL_TO_CORE2 != 0U)
       &Gpt_ChannelStatusCore2[0],
#else
        NULL_PTR,
#endif /* GPT_MAX_CHANNEL_TO_CORE2 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 3U */
#if (MCAL_NUMBER_OF_CORES >= 4U)
        /* A pointer the channel global variable of core3 */
#if (GPT_MAX_CHANNEL_TO_CORE3 != 0U)
       &Gpt_ChannelStatusCore3[0]
#else
        NULL_PTR
#endif /* GPT_MAX_CHANNEL_TO_CORE3 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 4U */
};

/* #Violation: Gpt_c_REF_8 */
static CONSTP2VAR(Gpt_DriverStateType, GPT_CONFIG_DATA, GPT_APPL_DATA)
        Gpt_CoreDriverStatusPtr[MCAL_NUMBER_OF_CORES] =
{
#if (GPT_MAX_CHANNEL_TO_CORE0 != 0U)
        &Gpt_DriverStatusCore0,
#else
        NULL_PTR,
#endif /*GPT_MAX_CHANNEL_TO_CORE0 != 0U */
#if (MCAL_NUMBER_OF_CORES >= 2U)
#if (GPT_MAX_CHANNEL_TO_CORE1 != 0U)
       &Gpt_DriverStatusCore1,
#else
        NULL_PTR,
#endif /* GPT_MAX_CHANNEL_TO_CORE1 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 2U */
#if (MCAL_NUMBER_OF_CORES >= 3U)
#if (GPT_MAX_CHANNEL_TO_CORE2 != 0U)
       &Gpt_DriverStatusCore2,
#else
        NULL_PTR,
#endif /* GPT_MAX_CHANNEL_TO_CORE2 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 3U */
#if (MCAL_NUMBER_OF_CORES >= 4U)
#if (GPT_MAX_CHANNEL_TO_CORE3 != 0U)
       &Gpt_DriverStatusCore3
#else
        NULL_PTR
#endif /* GPT_MAX_CHANNEL_TO_CORE3 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 4U */
};

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_c_REF_3 */     
#include "Gpt_MemMap.h"


#if (GPT_PREDEFTIMER_EN == STD_ON)
/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
/* #Violation: Gpt_c_REF_3 */     
#include "Gpt_MemMap.h"

/* Predef timer status and core status */
static uint32 Gpt_PredefTimerStatus;

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
/* #Violation: Gpt_c_REF_3 */     
#include "Gpt_MemMap.h"    
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Gpt_c_REF_3 */     
#include "Gpt_MemMap.h"

/* Global pointer that point to configuration data structure */
static P2CONST(Gpt_ConfigType, GPT_VAR, GPT_CONFIG_DATA) Gpt_ConfigPtr;

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Gpt_c_REF_3 */
#include "Gpt_MemMap.h"

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Gpt_c_REF_3 */
#include "Gpt_MemMap.h"
#if (GPT_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_CheckDetErrors
(
    Gpt_ChannelType LogicChannel,
    uint8 ApiSid
);

#if (GPT_PREDEFTIMER_EN == STD_ON)
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_PredefTimerDetCheck
(
    const Gpt_PredefTimerType PredefTimer,
    const uint32 *const TimeValuePtr
);
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_InitDetCheck
(
    const Gpt_ConfigType* const ConfigPtr,
    Mcal_CoreType CoreId
);
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */

#if (GPT_PREDEFTIMER_EN == STD_ON)
static FUNC(void,GPT_PRIVATE_CODE) Gpt_PreDefTimerInit
(
    void
);

static FUNC(void,GPT_PRIVATE_CODE) Gpt_PreDefTimerDeInit
(
    void
);
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

static FUNC(boolean, GPT_PRIVATE_CODE) Gpt_NormalTimerInit
(
    void
);

#if (GPT_DE_INIT_API == STD_ON)
static FUNC(void, GPT_PRIVATE_CODE) Gpt_NormalTimerDeInit
(
    void
);
#endif /* GPT_DE_INIT_API == STD_ON */

#if (GPT_DE_INIT_API == STD_ON)
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_DeInitCheck
(
    Mcal_CoreType CoreId
);
#endif/* End of API Gpt_DeInit() enable */

static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_StartTimerCheck
(
    Gpt_ChannelType LogicChannel,
    Gpt_ValueType TimerValue,
    Mcal_CoreType CoreId
);

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_EnableNotificationCheck
(
    Gpt_ChannelType LogicChannel,
    Mcal_CoreType CoreId
);

static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_DisableNotificationCheck
(
    Gpt_ChannelType LogicChannel,
    Mcal_CoreType CoreId
);
#endif/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_SetModeDetCheck
(
    Gpt_ModeType Mode,
    Mcal_CoreType CoreId
);

static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_DisableWakeupDetCheck
(
    Gpt_ChannelType Channel
);

static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_EnableWakeupDetCheck
(
    Gpt_ChannelType Channel
);
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */

static boolean Gpt_HWStopTimer
(
  uint32 HwCfgMapIndex, 
  Gpt_HWType HwClass
);

static boolean Gpt_HWSetTimerInterrupt
(
  uint32 HwCfgMapIndex, 
  Gpt_HWType HwClass,
  boolean EnableState
);

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Gpt_c_REF_3 */   
#include "Gpt_MemMap.h"   
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Gpt_c_REF_9 */
#define GPT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Gpt_c_REF_3 */   
#include "Gpt_MemMap.h"

#if (GPT_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_CheckDetErrors
*
*   Service ID              : None
*
*   Description             :This API is used to check common development errors.
*
*   Parameters in           : Channel: Gpt channel ID number;
*                             ApiSid: service ID
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
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_CheckDetErrors
(
    Gpt_ChannelType LogicChannel,
    uint8 ApiSid
)
{
    /* Declare the variable to store the DET return value */
    Std_ReturnType ErrValue;
    Mcal_CoreType    CoreId;
    uint32 ChInCoreIndex;
    const Gpt_ChConfigType* ChannelConfigPtr;

    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* Initialized return value to E_OK */
    ErrValue = E_NOT_OK;

    /* Check if the GPT Driver is initialized properly */
    if(GPT_INITIALIZED != (Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState))
    {
        /* Call API without GPT module initialized */
        GPT_DET_ERROR_REPORT(ApiSid, GPT_E_UNINIT);
    }
    else if(GPT_MAX_CHANNELS <= LogicChannel)
    {
        /* Call API with invalid channel ID */
        GPT_DET_ERROR_REPORT(ApiSid, GPT_E_PARAM_CHANNEL);
    }
    else
    {
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(LogicChannel);
        
        ChannelConfigPtr = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->Gpt_ChannelConfigPtr;

        if (ChannelConfigPtr[ChInCoreIndex].ChannelId != LogicChannel)
        {
            /* Call API in the wrong core */
            GPT_DET_ERROR_REPORT(ApiSid, GPT_E_CORE_CHANNEL_MISMATCH);
        }
        else
        {
            ErrValue = E_OK;
        }
    }
    return ErrValue;
} /* End of API Gpt_CheckDetErrors() */

#if (GPT_PREDEFTIMER_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_PredefTimerDetCheck
*
*   Service ID              : None
*
*   Description             :This API is used to check the development errors of the predef timer.
*
*   Parameters in           :PredefTimer: The type of Predef Timer.
*                            TimeValuePtr:The pointer of the return value.
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
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_PredefTimerDetCheck
(
    const Gpt_PredefTimerType PredefTimer,
    const uint32 *const TimeValuePtr
)
{

    Std_ReturnType ErrValue;
    Mcal_CoreType CoreId;

    ErrValue = E_OK;

    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    if(GPT_UNINITIALIZED == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState)
    {
        /* Call API without GPT module initialized */
        GPT_DET_ERROR_REPORT(GPT_SID_GET_PREDEFTIMERVALUE_SID, GPT_E_UNINIT);
        ErrValue = E_NOT_OK;
    }
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
    else if(GPT_MODE_SLEEP == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState)
    {
        /* Call API with invaild mode */
        GPT_DET_RUNTIME_ERROR_REPORT(GPT_SID_GET_PREDEFTIMERVALUE_SID, GPT_E_MODE);

        ErrValue = E_NOT_OK;
    }
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */
    else if(NULL_PTR == TimeValuePtr)
    {
        /* Call API with invaild pointer */
        GPT_DET_ERROR_REPORT(GPT_SID_GET_PREDEFTIMERVALUE_SID, GPT_E_PARAM_POINTER);

        ErrValue = E_NOT_OK;
    }
#if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_OFF)
    else if(PredefTimer == GPT_PREDEF_TIMER_100US_32BIT)
    {
        /* Call API with invaild predef timer type */
        GPT_DET_ERROR_REPORT(GPT_SID_GET_PREDEFTIMERVALUE_SID, GPT_E_PARAM_PREDEF_TIMER);

        ErrValue = E_NOT_OK;
    }
#endif /* GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON */
#if (GPT_PREDEFTIMER_1US_EN == STD_ON)
    else if((PredefTimer != GPT_PREDEF_TIMER_100US_32BIT) &&
            ((uint32)PredefTimer > (uint32)GPT_PREDEFTIMER_1US_TYPE))
    {
        /* Call API with invaild predef timer type */
        GPT_DET_ERROR_REPORT(GPT_SID_GET_PREDEFTIMERVALUE_SID, GPT_E_PARAM_PREDEF_TIMER);
        ErrValue = E_NOT_OK;
    }
#endif /* GPT_PREDEFTIMER_1US_EN == STD_ON */
    /* #Violation: Gpt_c_REF_7 */
    else
    {
        /* Do nothing */
    }

    return ErrValue;
} /* End of API Gpt_PredefTimerDetCheck() */
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

/****************************************************************************************************
*   Function Name           : Gpt_InitDetCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Gpt_Init.
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
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_InitDetCheck
(
    const Gpt_ConfigType* const ConfigPtr, 
    Mcal_CoreType CoreId
)
{
  Std_ReturnType ErrValue;

  ErrValue = E_NOT_OK;

  /* Check if config pointer is NULL pointer */
  if(NULL_PTR == ConfigPtr)
  {
      /* Call API with invaild parameter */
      GPT_DET_ERROR_REPORT(GPT_INIT_SID, GPT_E_PARAM_POINTER);
  }
  else if((NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId]) && 
          (NULL_PTR == ConfigPtr->GptPredefTimerPtr[0])  &&
          (NULL_PTR == ConfigPtr->GptPredefTimerPtr[1]))
  {
      /* Call API but the GPT is not configured in current core */
      GPT_DET_ERROR_REPORT(GPT_INIT_SID, GPT_E_CORE_NOT_CONFIGURED);
  }
  else if(GPT_UNINITIALIZED != (Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState))
  {
      /* SWS_Gpt_00307:
          Check if the GPT Driver is already Initialized */
      /* Call API with invaild parameter */
      GPT_DET_ERROR_REPORT(GPT_INIT_SID, GPT_E_ALREADY_INITIALIZED);
  } /* End of Gpt_DriverStatus == GPT_INITIALIZED */
  else
  {
      ErrValue = E_OK;
  }
  return ErrValue;
}
#endif /* GPT_DEV_ERROR_DETECT == STD_ON*/

#if (GPT_DE_INIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_DeInitCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Gpt_DeInit.
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
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_DeInitCheck
(
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
    uint8 ChannelInCoreIndex;
    const Gpt_ChannelStatusType* ChannelStatusPtr;

    ErrValue = E_OK;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00220:
       If the driver is not initialized, raise error*/
    if(GPT_INITIALIZED != (Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState))
    {
        /* Call API but the GPT is not configured in current core */
        GPT_DET_ERROR_REPORT(GPT_DEINIT_SID, GPT_E_UNINIT);
        ErrValue = E_NOT_OK;
    }
    else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        for (ChannelInCoreIndex = 0U; 
             (ChannelInCoreIndex < Gpt_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel) &&
             (E_OK == ErrValue); ChannelInCoreIndex++)
        {
            ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChannelInCoreIndex);
            /* SWS_Gpt_00234:
                 If any timer channel is in state "running" status, raise error.*/
            if (GPT_CH_RUNNING == ChannelStatusPtr->Status)
            {
                /* SWS_Gpt_00234 */
                /* Call API but there are channels running */
                GPT_DET_RUNTIME_ERROR_REPORT(GPT_DEINIT_SID, GPT_E_BUSY);
                ErrValue = E_NOT_OK;
            }
        }
    }
  return ErrValue;
}
#endif/* End of API Gpt_DeInit() enable */

/****************************************************************************************************
*   Function Name           : Gpt_StartTimerCheck
*
*   Service ID              : None
*
*   Description             : This API returns the Det error of Gpt_StartTimer.
*
*   Parameters in           : Channel: Numeric identifier of the GPT channel.
*                             Value: Target time in number of ticks.
*                             CoreId: Core ID.
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
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_StartTimerCheck
(
    Gpt_ChannelType LogicChannel,
    Gpt_ValueType TimerValue,
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
    const Gpt_ChannelStatusType* ChannelStatusPtr;
    uint8 ChInCoreIndex;
#if (GPT_DEV_ERROR_DETECT == STD_OFF)
    ErrValue = E_OK;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00212, SWS_Gpt_00224 */
    ErrValue = Gpt_CheckDetErrors(LogicChannel, GPT_START_TIMER_SID);
    /* Check if the Channel value is ZERO */
    if (E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(LogicChannel);

        if ((Gpt_ValueType) MCAL_ZERO == TimerValue)
        {
#if (GPT_DEV_ERROR_DETECT == STD_ON)
          /* Call API with invaild period value */
          GPT_DET_ERROR_REPORT(GPT_START_TIMER_SID, GPT_E_PARAM_VALUE);
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
            ErrValue = E_NOT_OK;
        }
        /* #Violation: Gpt_c_REF_5 */
        else if((MCAL_ONE == TimerValue) && (GPT_GET_HW_CLASS(CoreId, ChInCoreIndex) == GPT_HW_GTM))
        {
#if (GPT_DEV_ERROR_DETECT == STD_ON)
          /* Call API with invaild period value */
          GPT_DET_ERROR_REPORT(GPT_START_TIMER_SID, GPT_E_PARAM_VALUE);
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
            ErrValue = E_NOT_OK;
        }
        /* #Violation: Gpt_c_REF_5 */
        else if (GPT_GET_CHANNEL_MAX_VALUE(CoreId, ChInCoreIndex) < TimerValue)
        {
#if (GPT_DEV_ERROR_DETECT == STD_ON)
            /* Call API with invaild period value */
            GPT_DET_ERROR_REPORT(GPT_START_TIMER_SID, GPT_E_PARAM_VALUE);
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
            ErrValue = E_NOT_OK;
        }
        else
        {
            ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
            if (GPT_CH_RUNNING == ChannelStatusPtr->Status)
            {
                /* SWS_Gpt_00084 */
                /* Call API but the channel is already running */
                GPT_DET_RUNTIME_ERROR_REPORT(GPT_START_TIMER_SID, GPT_E_BUSY);
                ErrValue = E_NOT_OK;
            }
        }
    }
  return ErrValue;
}

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_EnableNotificationCheck
*
*   Service ID              : None
*
*   Description             :This API returns the Det error of Gpt_EnableNotification.
*
*   Parameters in           : Channel: Numeric identifier of the GPT channel
*                             CoreId: Core ID.
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
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_EnableNotificationCheck
(
    Gpt_ChannelType LogicChannel,
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
    uint8 ChInCoreIndex;
    const Gpt_ChannelStatusType* ChannelStatusPtr;

#if (GPT_DEV_ERROR_DETECT == STD_OFF)
    ErrValue = E_OK;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00226, SWS_Gpt_00214 */
    ErrValue = Gpt_CheckDetErrors(LogicChannel, GPT_ENABLE_NOTIFY_SID);
    /* Check if any DET error was reported */
    if (E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(LogicChannel);
#if (GPT_DEV_ERROR_DETECT == STD_ON)
        if (NULL_PTR == Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
                Gpt_ChannelConfigPtr[ChInCoreIndex].NotificationFuncPtr)
        {
            /* SWS_Gpt_00377:
               If no valid notification function is configured */
            /* Call API with invalid channel ID */
            GPT_DET_ERROR_REPORT(GPT_ENABLE_NOTIFY_SID, GPT_E_PARAM_CHANNEL);
            ErrValue = E_NOT_OK;
        }
        else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
        {
            ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);

            if (TRUE == ChannelStatusPtr->NotifyStatus)
            {
#if (GPT_DEV_ERROR_DETECT == STD_ON)
                /* Call API but the notification is already enabled */
                GPT_DET_ERROR_REPORT(GPT_ENABLE_NOTIFY_SID, GPT_E_ALREADY_ENABLED);
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
                ErrValue = E_NOT_OK;
            }
        }
    }

  return ErrValue;
}

/****************************************************************************************************
*   Function Name           : Gpt_DisableNotificationCheck
*
*   Service ID              : None.
*
*   Description             :This API returns the Det error of Gpt_EnableNotification.
*
*   Parameters in           : Channel: Numeric identifier of the GPT channel.
*                             CoreId: Core ID.
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
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_DisableNotificationCheck
(
    Gpt_ChannelType LogicChannel,
    Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrValue;
    uint8 ChInCoreIndex;
    const Gpt_ChannelStatusType* ChannelStatusPtr;

#if (GPT_DEV_ERROR_DETECT == STD_OFF)
    ErrValue = E_OK;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00226, SWS_Gpt_00214 */
    ErrValue = Gpt_CheckDetErrors(LogicChannel, GPT_DISABLE_NOTIFY_SID);
    /* Check if any DET error was reported */
    if (E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(LogicChannel);
#if (GPT_DEV_ERROR_DETECT == STD_ON)
        if (NULL_PTR == Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
                Gpt_ChannelConfigPtr[ChInCoreIndex].NotificationFuncPtr)
        {
            /* SWS_Gpt_00377:
               If no valid notification function is configured */
            /* Call API with invalid channel ID */
            GPT_DET_ERROR_REPORT(GPT_DISABLE_NOTIFY_SID, GPT_E_PARAM_CHANNEL);
            ErrValue = E_NOT_OK;
        }
        else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
        {
            ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);

            if (FALSE == ChannelStatusPtr->NotifyStatus)
            {
#if (GPT_DEV_ERROR_DETECT == STD_ON)
                /* Call API but the notification is already disabled */
                GPT_DET_ERROR_REPORT(GPT_DISABLE_NOTIFY_SID, GPT_E_ALREADY_DISABLED);
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
                    ErrValue = E_NOT_OK;
            }
        }
    }

  return ErrValue;
}

#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_SetModeDetCheck
*
*   Service ID              : None.
*
*   Description             :This API returns the Det error of Gpt_SetMode.
*
*   Parameters in           : Mode: See Gpt_ModeType.
*                             CoreId: Core ID.
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
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_SetModeDetCheck
(
    Gpt_ModeType Mode,
    Mcal_CoreType CoreId
)
{

    Std_ReturnType ErrValue;

    ErrValue = E_OK;

    /* /[SWS_Gpt_00228]  If development error detection is enabled for GPT module: 
       If the driver is not initialized, the function Gpt_SetMode shall raise the error 
       GPT_E_UNINIT. */
    if(GPT_UNINITIALIZED == (Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState))
    {
        /* Call API without GPT module initialized */
        GPT_DET_ERROR_REPORT(GPT_SET_MODE_SID, GPT_E_UNINIT);
        ErrValue = E_NOT_OK;
    }
    /* /[SWS_Gpt_00231]  If development error detection is enabled for GPT module: 
       The function Gpt_SetMode shall raise the error GPT_E_PARAM_MODE if the 
       parameter Mode is invalid. */
    else if (!((Mode == GPT_MODE_NORMAL) || (Mode == GPT_MODE_SLEEP)))
    {
        /* Call API with invalid mode value */
        GPT_DET_ERROR_REPORT(GPT_SET_MODE_SID, GPT_E_PARAM_MODE);
        ErrValue = E_NOT_OK;
    }
    else
    {
        /* Do nothing */
    }

    return ErrValue;
}

/****************************************************************************************************
*   Function Name           : Gpt_DisableWakeupDetCheck
*
*   Service ID              : None.
*
*   Description             :This API returns the Det error of Gpt_DisableWakeup.
*
*   Parameters in           : Channel:Numeric identifier of the GPT channel.
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
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_DisableWakeupDetCheck
(
    Gpt_ChannelType Channel
)
{

    Std_ReturnType ErrValue;
    Mcal_CoreType CoreId;
    uint8 ChInCoreIndex;

    /* /[SWS_Gpt_00215]  If development error detection is enabled for GPT module: 
       If the parameter Channel is invalid (not within the range specified by configuration) 
       or channel wakeup is not enabled by configuration (GptEnableWakeup), the function 
       Gpt_DisableWakeup shall raise the error GPT_E_PARAM_CHANNEL. */
    /* /[SWS_Gpt_00229]  If development error detection is enabled for GPT module: 
       If the driver is not initialized, the function Gpt_DisableWakeup shall raise the error 
       GPT_E_UNINIT. */
    ErrValue = Gpt_CheckDetErrors(Channel, GPT_DISABLE_WAKEUP_SID);

    if(E_OK == ErrValue)
    {
        CoreId = Mcal_GetCoreId();
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* /[SWS_Gpt_00215]  If development error detection is enabled for GPT module: 
           If the parameter Channel is invalid (not within the range specified by configuration) 
           or channel wakeup is not enabled by configuration (GptEnableWakeup), the function 
           Gpt_DisableWakeup shall raise the error GPT_E_PARAM_CHANNEL. */
        if(FALSE == GPT_GET_WAKEUP_ENABLE_CONFIG(CoreId, ChInCoreIndex))
        {
            /* /[SWS_Gpt_00215]  If development error detection is enabled for GPT module: 
              If the parameter Channel is invalid (not within the range specified by configuration) 
              or channel wakeup is not enabled by configuration (GptEnableWakeup), the function 
              Gpt_DisableWakeup shall raise the error GPT_E_PARAM_CHANNEL. */
            /* Call API with invalid channel ID */
            GPT_DET_ERROR_REPORT(GPT_DISABLE_WAKEUP_SID, GPT_E_PARAM_CHANNEL);
            ErrValue = E_NOT_OK;
        }
    }

    return ErrValue;
}

/****************************************************************************************************
*   Function Name           : Gpt_EnableWakeupDetCheck
*
*   Service ID              : None.
*
*   Description             :This API returns the Det error of Gpt_EnableWakeup.
*
*   Parameters in           : Channel:Numeric identifier of the GPT channel.
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
static FUNC(Std_ReturnType, GPT_PRIVATE_CODE) Gpt_EnableWakeupDetCheck
(
    Gpt_ChannelType Channel
)
{

    Std_ReturnType ErrValue;
    Mcal_CoreType CoreId;
    uint8 ChInCoreIndex;

    /* /[SWS_Gpt_00230]  If development error detection is enabled for GPT module: 
       If the driver is not initialized, the function Gpt_EnableWakeup shall raise the error 
       GPT_E_UNINIT. */
    /* /[SWS_Gpt_00216]  If development error detection is enabled for GPT module: 
       If the parameter Channel is invalid (not within the range specified by configuration) 
       or channel wakeup is not enabled by configuration (GptEnableWakeup), the function 
       Gpt_EnableWakeup shall raise the error GPT_E_PARAM_CHANNEL. */
    ErrValue = Gpt_CheckDetErrors(Channel, GPT_ENABLE_WAKEUP_SID);

    if(E_OK == ErrValue)
    {
        CoreId = Mcal_GetCoreId();
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* /[SWS_Gpt_00216]  If development error detection is enabled for GPT module: 
           If the parameter Channel is invalid (not within the range specified by configuration) 
           or channel wakeup is not enabled by configuration (GptEnableWakeup), the function 
           Gpt_EnableWakeup shall raise the error GPT_E_PARAM_CHANNEL. */
        if(FALSE == GPT_GET_WAKEUP_ENABLE_CONFIG(CoreId, ChInCoreIndex))
        {
            /* Call API with invalid channel ID */
            /* /[SWS_Gpt_00216]  If development error detection is enabled for GPT module: 
              If the parameter Channel is invalid (not within the range specified by configuration) 
              or channel wakeup is not enabled by configuration (GptEnableWakeup), the function 
              Gpt_EnableWakeup shall raise the error GPT_E_PARAM_CHANNEL. */
            GPT_DET_ERROR_REPORT(GPT_ENABLE_WAKEUP_SID, GPT_E_PARAM_CHANNEL);
            ErrValue = E_NOT_OK;
        }
    }

    return ErrValue;
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */

/****************************************************************************************************
*   Function Name           : Gpt_HWStopTimer
*
*   Service ID              : None.
*
*   Description             :This API stops the hardware timer.
*
*   Parameters in           : HwCfgMapIndex: Hardware configuration index.
*                             Gpt_HWType: Hardware class.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Safety check status.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static boolean Gpt_HWStopTimer
(
  uint32 HwCfgMapIndex, 
  Gpt_HWType HwClass
)
{
    boolean SafetyFlag;


    SafetyFlag = TRUE;

    if(GPT_HW_GTM == HwClass)
    {
        /* #Violation: Gpt_c_REF_5 */
        SafetyFlag = Gtm_Timer_Hal_StopChannel(GPT_GET_GTM_CHANNEL_OBJECT_PTR(HwCfgMapIndex));
    }
    else
    {
        /* #Violation: Gpt_c_REF_5 */
        Basetimer_Hal_StopTimer(GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex));
    }

    return SafetyFlag;
}

/****************************************************************************************************
*   Function Name           : Gpt_HWStopTimer
*
*   Service ID              : None.
*
*   Description             :This API set the interrupt of the hardware timer.
*
*   Parameters in           : HwCfgMapIndex: Hardware configuration index.
*                             Gpt_HWType: Hardware class.
*                             EnableState: Enable or disable the hardware interrupt.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Safety check status.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
static boolean Gpt_HWSetTimerInterrupt
(
  uint32 HwCfgMapIndex, 
  Gpt_HWType HwClass,
  boolean EnableState
)
{
    boolean SafetyFlag;

    SafetyFlag = TRUE;

    if(GPT_HW_GTM == HwClass)
    {
        /* #Violation: Gpt_c_REF_5 */
        SafetyFlag = Gtm_Timer_Hal_SetInterrupt(GPT_GET_GTM_CHANNEL_OBJECT_PTR(HwCfgMapIndex), 
                                                EnableState);
    }
    else
    {
        /* #Violation: Gpt_c_REF_5 */
        Basetimer_Hal_SetInterrupt(GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex), 
                                   EnableState);
    }

    return SafetyFlag;
}

#if (GPT_PREDEFTIMER_EN == STD_ON)
/****************************************************************************************************
 *   Function Name           : Gpt_PreDefTimerInit
 *
 *   Service ID              : None.
 *
 *   Description             :API to initialize the  Predef Timer.
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
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, GPT_PRIVATE_CODE) Gpt_PreDefTimerInit
(
    void
)
{
    Basetimer_InitConfig BaseTimerConfig;

    /* Range is fixed to 32bit */
    BaseTimerConfig.size = BASETIMER_SIZE_32BITS;
    /* Set target counter value to 32bit, a lower bit timer can be derived from a higher bit timer 
     * by a simple software mask operation*/
    BaseTimerConfig.load = 0xFFFFFFFFU;
    /* Set mode to free running */
    BaseTimerConfig.mode = BASETIMER_MODE_FREERUNNING;

#if (GPT_PREDEFTIMER_1US_EN == STD_ON)
    /* Start the 1us predefined timer */
    /* #Violation: Gpt_c_REF_2 */
    Basetimer_Hal_InitModule(Gpt_ConfigPtr->GptPredefTimerPtr[0U], &BaseTimerConfig);
    /* Start the timer */
    /* #Violation: Gpt_c_REF_2 */
    Basetimer_Hal_StartTimer(Gpt_ConfigPtr->GptPredefTimerPtr[0U]);
#endif /* GPT_PREDEFTIMER_1US_EN == STD_ON */

#if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
    /* Start the 100us predefined timer */
    /* #Violation: Gpt_c_REF_2 */
    Basetimer_Hal_InitModule(Gpt_ConfigPtr->GptPredefTimerPtr[1U], &BaseTimerConfig);
    /* Start the timer */
    /* #Violation: Gpt_c_REF_2 */
    Basetimer_Hal_StartTimer(Gpt_ConfigPtr->GptPredefTimerPtr[1U]);
#endif /* GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON */

} /* End of API Gpt_PreDefTimerInit() */
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

#if (GPT_DE_INIT_API == STD_ON)
#if (GPT_PREDEFTIMER_EN == STD_ON)
/****************************************************************************************************
 *   Function Name           : Gpt_PreDefTimerDeInit
 *
 *   Service ID              : None.
 *
 *   Description             :API to de-initialize the  Predef Timer.
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
 *   Return value            : Safety check status.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void,GPT_PRIVATE_CODE) Gpt_PreDefTimerDeInit
(
    void
)
{
#if (GPT_PREDEFTIMER_1US_EN == STD_ON)
    /* #Violation: Gpt_c_REF_2 */
    Basetimer_Hal_StopTimer(Gpt_ConfigPtr->GptPredefTimerPtr[0U]);
#endif /* GPT_PREDEFTIMER_1US_EN == STD_ON */

#if ((GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON))
    /* #Violation: Gpt_c_REF_2 */
    Basetimer_Hal_StopTimer(Gpt_ConfigPtr->GptPredefTimerPtr[1U]);
#endif /* GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON */

} /* End of API Gpt_PreDefTimerDeInit() */
#endif /* GPT_PREDEFTIMER_EN == STD_ON */
#endif /* GPT_DE_INIT_API == STD_ON */

/****************************************************************************************************
 *   Function Name           : Gpt_NormalTimerInit
 *
 *   Service ID              : None.
 *
 *   Description             :API to initialize the  normal Timer.
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
 *   Return value            : Safety check status.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(boolean, GPT_PRIVATE_CODE) Gpt_NormalTimerInit
(
    void
)
{
    uint32 MaxChannel;
    Mcal_CoreType CoreId;
    uint8 ChannelIndex;
    const Gpt_ChConfigType *ChannelConfigPtr;
    Gpt_ChannelStatusType *ChannelStatusPtr;
    uint32 ChannelId;
    const Gpt_GtmConfigType *GtmConfigPtr;
    const Gpt_BasetimerConfigType *BaseTimerConfigPtr;
    uint32 HwCfgIndex;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();
    
    MaxChannel = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel;

    ChannelConfigPtr = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
        Gpt_ChannelConfigPtr;
    for(ChannelIndex = 0U; ChannelIndex < MaxChannel; ChannelIndex++)
    {
        /* Get the logic channel id */
        ChannelId = ChannelConfigPtr[ChannelIndex].ChannelId;
        /* Find the hardware configuration index by logic id */
        HwCfgIndex = Gpt_ConfigPtr->GptChannelIdxmapPtr[ChannelId].HwCfgIndex;

        /* #Violation: Gpt_c_REF_5 */
        if(GPT_HW_GTM == GPT_GET_HW_CLASS(CoreId, ChannelIndex))
        {
            /* Find hardware configuration by hardware configuration index */
            GtmConfigPtr = &Gpt_ConfigPtr->GptHwGtmConfigPtr[HwCfgIndex];
            /* Initialize the hardware of this logic channel based on GTM */
            SafetyFlag &= Gtm_Timer_Hal_InitChannel(&GtmConfigPtr->HwChannelIndex, &GtmConfigPtr->HwChannelConfig);
        }
        else
        {
            /* Find hardware configuration by hardware configuration index */
            BaseTimerConfigPtr = &Gpt_ConfigPtr->GptHwBaseTimerConfigPtr[HwCfgIndex];
            /* Initialize the hardware of this logic channel based on BASETIMER */
            Basetimer_Hal_InitModule((BaseTimerConfigPtr->HwChannelIndexPtr),
                                     &BaseTimerConfigPtr->HwChannelConfig);
            /* Disable the interrupt, this is because the hardware enables interrupts by default */
            Basetimer_Hal_SetInterrupt(BaseTimerConfigPtr->HwChannelIndexPtr, FALSE);
        }

        if(TRUE != SafetyFlag)
        {
            break;
        }

        /* To get the channel status pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChannelIndex);
        /* Set the notification status to false(Initial status) */
        ChannelStatusPtr->NotifyStatus = FALSE;
        /* Set the channel status to not started (Initial status) */
        ChannelStatusPtr->Status = GPT_CH_NOTSTARTED;
        /* Set the channel wakeup status to not enabled (Initial status) */
        ChannelStatusPtr->WakeUpStatus = FALSE;
    }

    return SafetyFlag;
} /* End of API Gpt_NormalTimerInit() */

#if (GPT_DE_INIT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Gpt_NormalTimerDeInit
 *
 *   Service ID              : None.
 *
  *   Description             :API to de-initialize the  normal Timer.
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
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, GPT_PRIVATE_CODE) Gpt_NormalTimerDeInit
(
        void
)
{
    uint8 ChIndexInCore;
    uint8 MaxChannel;
    uint8 LogicId;
    uint32 HwCfgMapIndex;
    Mcal_CoreType CoreId;
    Gpt_ChannelStatusType* ChannelStatusPtr;

    /* Get current core id */
    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();
    /* Get maximum channel number of current core */
    MaxChannel = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel;
    /* Loop to de-initial all channel of current core */
    for(ChIndexInCore = 0U; ChIndexInCore < MaxChannel; ChIndexInCore++)
    {
      LogicId = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->Gpt_ChannelConfigPtr[ChIndexInCore].ChannelId;
      HwCfgMapIndex = Gpt_ConfigPtr->GptChannelIdxmapPtr[LogicId].HwCfgIndex;

      /* #Violation: Gpt_c_REF_5 */
      if(GPT_HW_GTM == GPT_GET_HW_CLASS(CoreId, ChIndexInCore))
      {
          /* De-Init the hardware channel(Due to hardware characteristics,
                 * critical section protection is not required)*/
          /* #Violation: Gpt_c_REF_5 */
          Gtm_Timer_Hal_DeinitChannel(GPT_GET_GTM_CHANNEL_OBJECT_PTR(HwCfgMapIndex));
      }
      else
      {
        /* Do nothing, because basetimer will be stopped by calling Gpt_StopChannel()
         * before calling this interface and there is no any other hardware features
         * need to be reset */
      }

        /* To get the channel status pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChIndexInCore);
        /* Set the notification status to default status  */
        ChannelStatusPtr->NotifyStatus = FALSE;
        /* Set the channel status to default status  */
        ChannelStatusPtr->Status = GPT_CH_NOTSTARTED;
        /* Set the channel wakeup status to not enabled (Initial status) */
        ChannelStatusPtr->WakeUpStatus = FALSE;
    }
} /* End of API Gpt_NormalTimerDeInit() */
#endif /* GPT_DE_INIT_API == STD_ON */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Gpt_SetSleepMode
 *
 *   Service ID              : None.
 *
  *   Description             :Set the GPT module to sleep mode.
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
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
void Gpt_SetSleepMode(void)
{
    uint32 MaxChannel;
    Mcal_CoreType CoreId;
    uint8 ChannelIndex;
    const Gpt_ChConfigType *ChannelConfigPtr;
    Gpt_ChannelStatusType *ChannelStatusPtr;
    uint32 HwCfgMapIndex;
    boolean IntEnStatus;
    boolean SafetyFlag;
    Std_ReturnType LockStatus;

    SafetyFlag = TRUE;
    LockStatus = E_OK;

    CoreId = Mcal_GetCoreId();

    MaxChannel = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel;

    ChannelConfigPtr = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
        Gpt_ChannelConfigPtr;

    GPT_ENTER_CRITICAL_SECTION(Gpt_SetMode);
    for(ChannelIndex = 0U; ChannelIndex < MaxChannel; ChannelIndex++)
    {
        /* To get the channel status pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChannelIndex);
        /* Get hardware configuration index by logic id */
        HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(ChannelConfigPtr[ChannelIndex].ChannelId);
        /* Check if the channel is configured the wakeup functionality */
        if(TRUE == GPT_GET_WAKEUP_ENABLE_CONFIG(CoreId, ChannelIndex))
        {
            /* /[SWS_Gpt_00153]  If the parameter Mode has the value GPT_MODE_SLEEP: 
            The function Gpt_SetMode shall enable the wakeup interrupts for all channels which 
            are configured for wakeup and the wakeup is enabled (stored attribute) via the 
            function Gpt_EnableWakeup prior. All other wakeup interrupts shall be disabled. */
            if(TRUE == ChannelStatusPtr->WakeUpStatus)
            {
                IntEnStatus =TRUE;  
            }
            /* The channel wakeup functionality is configured but not enabled by 
               Gpt_EnableWakeup API */
            else
            {
                LockStatus = Mcal_GetLock(MCAL_LOCK_ID_GPT);
                if(E_OK == LockStatus)
                {
                    /* /[SWS_Gpt_00164]  If the function Gpt_SetMode is called with parameter Mode 
                    has the value GPT_MODE_SLEEP: All timer channels in state "running" which are not 
                    configured for wakeup or not enabled for wakeup interruption (stored attribute) via 
                    Gpt_EnableWakeup shall be stopped and their state shall be changed to "stopped". */
                    SafetyFlag &= Gpt_HWStopTimer(HwCfgMapIndex, GPT_GET_HW_CLASS(CoreId, ChannelIndex));
                    Mcal_ReleaseLock(MCAL_LOCK_ID_GPT);
                }
                if((FALSE == SafetyFlag) || (E_OK != LockStatus))
                {
                    break;
                }

                ChannelStatusPtr->Status = GPT_CH_STOPPED;

                IntEnStatus = FALSE;
            }

            SafetyFlag &= Gpt_HWSetTimerInterrupt(HwCfgMapIndex, 
                                                  GPT_GET_HW_CLASS(CoreId, ChannelIndex), 
                                                  IntEnStatus);
            if(FALSE == SafetyFlag)
            {
                break;
            }            
        }
        /* Chanel is not configured for wakeup functionality */
        else
        {
            /* /[SWS_Gpt_00164]  If the function Gpt_SetMode is called with parameter Mode 
            has the value GPT_MODE_SLEEP: All timer channels in state "running" which are not 
            configured for wakeup or not enabled for wakeup interruption (stored attribute) via 
            Gpt_EnableWakeup shall be stopped and their state shall be changed to "stopped". */
            if(GPT_CH_RUNNING == ChannelStatusPtr->Status)
            {
                LockStatus = Mcal_GetLock(MCAL_LOCK_ID_GPT);
                if(E_OK == LockStatus)
                {
                    SafetyFlag &= Gpt_HWStopTimer(HwCfgMapIndex, GPT_GET_HW_CLASS(CoreId, ChannelIndex));
                    Mcal_ReleaseLock(MCAL_LOCK_ID_GPT);
                }
                if((FALSE == SafetyFlag) || (E_OK != LockStatus))
                {
                    break;
                }

                ChannelStatusPtr->Status = GPT_CH_STOPPED;
            }
        }
    }

    if((TRUE == SafetyFlag) && (E_OK == LockStatus))
    {
#if (GPT_PREDEFTIMER_EN == STD_ON)
        /* [SWS_Gpt_00393]  If the parameter Mode has the value GPT_MODE_SLEEP:
          The function Gpt_SetMode shall stop all enabled GPT Predef Timers. */
        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_GPT);
        if(E_OK == LockStatus)
        {
            /* Clear core status */
            Gpt_PredefTimerStatus = 
                (~(GPT_FLAG_SET << ((uint32)CoreId + GPT_CORESTATUS_POS))) & Gpt_PredefTimerStatus;
            /* Current core is the last core(Only the last core is responsible for stopping the 
              predef timer), so stop the predef timer */
            if((Gpt_PredefTimerStatus & GPT_CORE_STATUS_MASK) == 0U)
            {
                /* Clear predef timer status */
                Gpt_PredefTimerStatus = 0x0U;
                Gpt_PreDefTimerDeInit();
            }
            Mcal_ReleaseLock(MCAL_LOCK_ID_GPT);
        }

        if((TRUE == SafetyFlag) && (E_OK == LockStatus))
#endif /* GPT_PREDEFTIMER_EN == STD_ON */
        {
            Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState = GPT_MODE_SLEEP;
        }
    }
    GPT_EXIT_CRITICAL_SECTION(Gpt_SetMode);

#if (GPT_SAFETY_ENABLE == STD_ON)
    if(E_OK != LockStatus)
    {
        /* Get lock timeout */
        GPT_DET_RUNTIME_ERROR_REPORT(GPT_SET_MODE_SID, GPT_E_LOCK_TIMEOUT);
    }
    if(TRUE != SafetyFlag)
    {
        GPT_DET_RUNTIME_ERROR_REPORT(GPT_SET_MODE_SID, GPT_E_SAFETY_CHECK_FAILED);
    }
#endif /* GPT_SAFETY_ENABLE == STD_ON */
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Gpt_SetNormalMode
 *
 *   Service ID              : None.
 *
  *   Description             :Set the GPT module to normal mode.
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
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
void Gpt_SetNormalMode(void)
{
    uint32 MaxChannel;
    Mcal_CoreType CoreId;
    uint8 ChannelIndex;
    const Gpt_ChConfigType *ChannelConfigPtr;
    Gpt_ChannelStatusType *ChannelStatusPtr;
    uint32 HwCfgMapIndex;
    boolean IntEnStatus;
#if (GPT_PREDEFTIMER_EN == STD_ON)
    Std_ReturnType LockStatus;
#endif /* GPT_PREDEFTIMER_EN == STD_ON */
    boolean SafetyFlag;

#if (GPT_PREDEFTIMER_EN == STD_ON)
    LockStatus = E_OK;
#endif /* GPT_PREDEFTIMER_EN == STD_ON */
    SafetyFlag = TRUE;
    CoreId = Mcal_GetCoreId();

    MaxChannel = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel;

    ChannelConfigPtr = Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
        Gpt_ChannelConfigPtr;

    GPT_ENTER_CRITICAL_SECTION(Gpt_SetMode);
    for(ChannelIndex = 0U; ChannelIndex < MaxChannel; ChannelIndex++)
    {
        /* To get the channel status pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChannelIndex);
        /* Get hardware configuration index by logic id */
        HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(ChannelConfigPtr[ChannelIndex].ChannelId);
        /* [SWS_Gpt_00152]  If the parameter Mode has the value GPT_MODE_NORMAL:
          The function Gpt_SetMode shall enable the interrupt notification for all channels 
          which are configured for notification and the notification is enabled 
          (stored attribute) via the function Gpt_EnableNotification prior. All other 
          interrupt notifications shall be disabled. */
        if((NULL_PTR != ChannelConfigPtr[ChannelIndex].NotificationFuncPtr) &&
           (TRUE == ChannelStatusPtr->NotifyStatus))
        {
            IntEnStatus = TRUE;
        }
        else
        {
            IntEnStatus = FALSE;
        }

        SafetyFlag &= Gpt_HWSetTimerInterrupt(HwCfgMapIndex, GPT_GET_HW_CLASS(CoreId, ChannelIndex), 
                                             IntEnStatus);
        if(FALSE == SafetyFlag)
        {
            break;
        }
    }

    if(TRUE == SafetyFlag)
    {
#if (GPT_PREDEFTIMER_EN == STD_ON)
        /* [SWS_Gpt_00392]  If the parameter Mode has the value GPT_MODE_NORMAL:
            If the driver is in "sleep mode", the function Gpt_SetMode shall restart all enabled 
            GPT Predef Timers at value "0". */
        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_GPT);
        if(E_OK == LockStatus)
        {
            /* Set core status */
            Gpt_PredefTimerStatus |= ((1U << (uint32)CoreId) << GPT_CORESTATUS_POS);
            /* Current core is the first core to run, so start the predef timer */
            if(0U == (Gpt_PredefTimerStatus & GPT_PREDEFTIMER_STATUS_MASK))
            {
                /* Set predef timer status */
                Gpt_PredefTimerStatus |= GPT_FLAG_SET;
                Gpt_PreDefTimerInit();
            }
            Mcal_ReleaseLock(MCAL_LOCK_ID_GPT);
        }

        if(E_OK == LockStatus)
#endif /* GPT_PREDEFTIMER_EN == STD_ON */
        {
            Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState = GPT_MODE_NORMAL;
        }
    }
    GPT_EXIT_CRITICAL_SECTION(Gpt_SetMode);

#if (GPT_SAFETY_ENABLE == STD_ON)
#if (GPT_PREDEFTIMER_EN == STD_ON)
    if(E_OK != LockStatus)
    {
        /* Get lock timeout */
        GPT_DET_RUNTIME_ERROR_REPORT(GPT_SET_MODE_SID, GPT_E_LOCK_TIMEOUT);
    }
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

    if(TRUE != SafetyFlag)
    {
        GPT_DET_RUNTIME_ERROR_REPORT(GPT_SET_MODE_SID, GPT_E_SAFETY_CHECK_FAILED);
    }
#endif /* GPT_SAFETY_ENABLE == STD_ON */
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */

/* ECUC_Gpt_00319:
   Adds / removes the service Gpt_GetVersionInfo() from the code*/
#if (GPT_GET_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_GetVersionInfo
*
*   Service ID              : 0x00
*
*   Description             :Returns the version information of GPT module.
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
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     :  [SWS_Gpt_00279], [SWS_Gpt_00338].
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(void, GPT_PUBLIC_CODE) Gpt_GetVersionInfo
(
    /* #Violation: Gpt_c_REF_8 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA)VersionInfoPtr
)
{
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00338:
       Check If the parameter VersionInfoPtr is a null pointer */
    if(NULL_PTR == VersionInfoPtr)
    {
        /* Call API with invalid pointer */
        GPT_DET_ERROR_REPORT(GPT_GET_VERSION_INFO_SID, GPT_E_PARAM_POINTER);
    }
    else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        VersionInfoPtr->vendorID = GPT_VENDOR_ID;
        VersionInfoPtr->moduleID = GPT_MODULE_ID;
        VersionInfoPtr->sw_major_version = GPT_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = GPT_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = GPT_SW_PATCH_VERSION;
    }
} /* End of API Gpt_GetVersionInfo() */
#endif /* End of API Gpt_GetVersionInfo() enable */

/****************************************************************************************************
*   Function Name           : Gpt_Init
*
*   Service ID              : 0x01
*
*   Description             : Initializes the GPT driver.
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
*   Preconditions           : GPT Module must be uninitialized..
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00280], [SWS_Gpt_00006], [SWS_Gpt_00107], [SWS_Gpt_00068] ,
*                             [SWS_Gpt_00352], [SWS_Gpt_00353], [SWS_Gpt_00354], [SWS_Gpt_00355] ,
*                             [SWS_Gpt_00356], [SWS_Gpt_00307], [SWS_Gpt_00339], [SWS_Gpt_00309] ,
*                             [SWS_Gpt_00390].
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(void, GPT_PUBLIC_CODE) Gpt_Init
(
    P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST)ConfigPtr
)
{
    Mcal_CoreType CoreId;
#if (GPT_PREDEFTIMER_EN == STD_ON)
    Std_ReturnType LockStatus;
#endif /* GPT_PREDEFTIMER_EN == STD_ON */
#if (GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_PREDEFTIMER_EN == STD_ON)
    Std_ReturnType ErrValue;
#endif /* (GPT_DEV_ERROR_DETECT == STD_ON) \|| (GPT_PREDEFTIMER_EN == STD_ON) */
    boolean SafetyFlag;
    
    SafetyFlag = TRUE;
    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    ErrValue = Gpt_InitDetCheck(ConfigPtr, CoreId);

    if(E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        Gpt_ConfigPtr = ConfigPtr;

#if (GPT_PREDEFTIMER_EN == STD_ON)

        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_GPT);
        if(E_OK == LockStatus)
        {
            /* #Violation: Gpt_c_REF_5 */
            if(GPT_PREDEFTIMER_UNINITIALIZED == 
               (Gpt_PredefTimerStatus & (uint32)GPT_PREDEFTIMER_STATUS_MASK))
            {
                /* Set predefine timer status to initialized */
                Gpt_PredefTimerStatus = Gpt_PredefTimerStatus | GPT_FLAG_SET;
                /* SWS_Gpt_00390:
                   Enable predefine timer(s), and start from counter value "0".*/
                Gpt_PreDefTimerInit();
            }

            /* Record the core status */
            Gpt_PredefTimerStatus = 
                (GPT_FLAG_SET << ((uint32)CoreId + GPT_CORESTATUS_POS)) | Gpt_PredefTimerStatus;

            Mcal_ReleaseLock(MCAL_LOCK_ID_GPT);
#if (GPT_DEV_ERROR_DETECT == STD_OFF)
            ErrValue = E_OK;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
        }
        else
        {
            /* Get lock timeout */
            GPT_DET_RUNTIME_ERROR_REPORT(GPT_INIT_SID, GPT_E_LOCK_TIMEOUT);
            ErrValue = E_NOT_OK;
        }
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

        /* #Violation: Gpt_c_REF_11 */
        if(NULL_PTR != ConfigPtr->CoreConfigPtr[CoreId])
        {
#if (GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_PREDEFTIMER_EN == STD_ON)
            if (ErrValue == E_OK)
#endif /* (GPT_DEV_ERROR_DETECT == STD_ON) \|| (GPT_PREDEFTIMER_EN == STD_ON) */
            {
                /* SWS_Gpt_00006:
                  Initialize the hardware timer module of normal timer */
                /* SWS_Gpt_00107:
                    Disable all interrupt notifications */
                SafetyFlag &= Gpt_NormalTimerInit();

                /* Set the operation mode of the GPT driver to "GPT_INITIALIZED". */
                Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState = GPT_INITIALIZED;
                /* SWS_Gpt_00339:
                  Set the operation mode of the GPT mode to "normal mode". */
                Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState = GPT_MODE_NORMAL;
            }
        }
    }

#if (GPT_SAFETY_ENABLE == STD_ON)
    if(FALSE == SafetyFlag)
    {
        GPT_DET_RUNTIME_ERROR_REPORT(GPT_INIT_SID, GPT_E_SAFETY_CHECK_FAILED);
    }
#else
    {
        MCAL_UNUSED_VAR(SafetyFlag);
    }
#endif /* GPT_SAFETY_ENABLE == STD_ON */
} /* End of API Gpt_Init() */

/* SWS_Gpt_00194:
   Controled by the static configuration parameter */
#if (GPT_DE_INIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_DeInit
*
*   Service ID              : 0x02
*
*   Description             : Deinitializes the GPT driver.
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
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00281], [SWS_Gpt_00008], [SWS_Gpt_00162], [SWS_Gpt_00308],
*                             [SWS_Gpt_00194], [SWS_Gpt_00363], [SWS_Gpt_00234], [SWS_Gpt_00220],
*                             [SWS_Gpt_00391].
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(void, GPT_PUBLIC_CODE) Gpt_DeInit
(
    void
)
{
    Mcal_CoreType CoreId;

#if (GPT_PREDEFTIMER_EN == STD_ON)
    Std_ReturnType LockStatus;
#endif /* GPT_PREDEFTIMER_EN == STD_ON */
    Std_ReturnType ErrValue;

    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();
    
    ErrValue = Gpt_DeInitCheck(CoreId);

    if(E_OK == ErrValue)
    /* SWS_Gpt_00008:
       Deinitialize the hardware used */
    {
        /* SWS_Gpt_00105:
           Disable all interrupt notifications */
        /* SWS_Gpt_00363:
           Set the operation mode of the GPT driver to "uninitialized". */
        Gpt_NormalTimerDeInit();

#if (GPT_PREDEFTIMER_EN == STD_ON)
        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_GPT);
        if(E_OK == LockStatus)
        {
            /* Reset the core status */
            Gpt_PredefTimerStatus = 
                (~(GPT_FLAG_SET << ((uint32)CoreId + GPT_CORESTATUS_POS))) & Gpt_PredefTimerStatus;

            /* #Violation: Gpt_c_REF_5 */
            Mcal_ReleaseLock(MCAL_LOCK_ID_GPT);
            /* If current core is the last core */
            if (GPT_ALLCORE_UNITIALIZED == (Gpt_PredefTimerStatus & GPT_CORE_STATUS_MASK))
            {
                 /* SWS_Gpt_00391:
                    Stop all enabled GPT predefine timers */
                Gpt_PreDefTimerDeInit();
                /* Reset the status variable */
                Gpt_PredefTimerStatus = 0x0U;
            }
        }
        else
        {
            /* Get lock timeout */
            GPT_DET_RUNTIME_ERROR_REPORT(GPT_DEINIT_SID, GPT_E_LOCK_TIMEOUT);
            ErrValue = E_NOT_OK;
        }

#endif /* GPT_PREDEFTIMER_EN == STD_ON */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
        if(E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
        {
            /* Set the operation mode of the GPT driver to "uninitialized mode" */
            Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState = GPT_UNINITIALIZED;
            /* Set the operation mode to "normal mode" */
            Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState = GPT_MODE_NORMAL;  
        }
    }
} /* End of API Gpt_DeInit() */
#endif/* End of API Gpt_DeInit() enable */

/* SWS_Gpt_00195:
   Controled by the static configuration parameter */
#if (GPT_TIME_ELAPSED_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_GetTimeElapsed
*
*   Service ID              : 0x03
*
*   Description             : Returns the time already elapsed.
*
*   Parameters in           : Channel:Numeric identifier of the GPT channel.
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
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     :  [SWS_Gpt_00282], [SWS_Gpt_00010], [SWS_Gpt_00361], [SWS_Gpt_00295] ,
*                              [SWS_Gpt_00297], [SWS_Gpt_00299], [SWS_Gpt_00113], [SWS_Gpt_00195] ,
*                              [SWS_Gpt_00222], [SWS_Gpt_00210] .
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(Gpt_ValueType, GPT_PUBLIC_CODE) Gpt_GetTimeElapsed
(
    /* #Violation: Gpt_c_REF_6 */
    Gpt_ChannelType Channel
)
{
    uint32 HwCfgMapIndex;
    Gpt_ValueType TimeElapsed;
    Mcal_CoreType CoreId;
    uint8 ChInCoreIndex;
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */

    /* Initialize the return value as zero */
    TimeElapsed = (Gpt_ValueType)MCAL_ZERO;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00222, SWS_Gpt_00210 */
    ErrValue = Gpt_CheckDetErrors(Channel, GPT_GET_TIME_ELAPSED_SID);

    if(E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        /* #Violation: Gpt_c_REF_5 */
        CoreId = Mcal_GetCoreId();
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* Get hardware configuration mapping index */
        /* #Violation: Gpt_c_REF_5 */
        HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(Channel);

        /* #Violation: Gpt_c_REF_5 */
        switch(GPT_GET_HW_CLASS(CoreId, ChInCoreIndex))
        {
            case GPT_HW_GTM:
            {
                TimeElapsed = Gtm_Timer_Hal_GetChannelInfo(
                    /* #Violation: Gpt_c_REF_5 */
                    GPT_GET_GTM_CHANNEL_OBJECT_PTR(HwCfgMapIndex), GTM_TIMER_COUNT_USED);
                break;
            }
            case GPT_HW_BASETIMER:
            {
                TimeElapsed = Basetimer_Hal_GetElapsedCount
                                /* #Violation: Gpt_c_REF_5 */
                                (GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex));
                break;
            }
            default:
            {
                /* Do nothing */
                break;
            }
        }

    } /* End of ErrValue == E_NOT_OK */

        /* SWS_Gpt_00010:
           Return the Elapsed Time */
        /* SWS_Gpt_00361:
            Return the Elapsed Time depends on the timer mode. */
        /* SWS_Gpt_00295: 
            Return the value "0" if the channel is uninitialized. */
        /* SWS_Gpt_00297
            Return the time value at the moment of "stopped", if the channel status is "stopped." */
        /* SWS_Gpt_00299:
       Return the target time, if the channel status is stopping. */
    return TimeElapsed;
} /* End of API Gpt_GetTimeElapsed() */
#endif /* GPT_TIME_ELAPSED_API == STD_ON */

/* SWS_Gpt_00196 */
#if (GPT_TIME_REMAINING_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_GetTimeRemaining
*
*   Service ID              : 0x04
*
*   Description             : Returns the time remaining until the target time is reached.
*
*   Parameters in           : Channel:Numeric identifier of the GPT channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Remaining timer value (in number of ticks).
*
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00283], [SWS_Gpt_00083], [SWS_Gpt_00301], [SWS_Gpt_00303],
*                             [SWS_Gpt_00305], [SWS_Gpt_00114], [SWS_Gpt_00196], [SWS_Gpt_00223],
*                             [SWS_Gpt_00211] .
****************************************************************************************************/
/* #Violation: Gpt_c_REF_6 */
/* #Violation: Gpt_c_REF_10 */
FUNC(Gpt_ValueType, GPT_PUBLIC_CODE) Gpt_GetTimeRemaining
(
    Gpt_ChannelType Channel
)
{
    uint32 HwCfgMapIndex;
    Gpt_ValueType TimeRemaining;
    Mcal_CoreType CoreId;
    uint8 ChInCoreIndex;
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */

    /* Initialize the return value as zero */
    TimeRemaining = (Gpt_ValueType)MCAL_ZERO;

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00301,  SWS_Gpt_00223, SWS_Gpt_00211 */
    ErrValue = Gpt_CheckDetErrors(Channel, GPT_GET_TIME_REMAINING_SID);

    if(E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        /* #Violation: Gpt_c_REF_5 */
        CoreId = Mcal_GetCoreId();

        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* Get hardware configuration mapping index */
        /* #Violation: Gpt_c_REF_5 */
        HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(Channel);

        /* #Violation: Gpt_c_REF_5 */
        switch(GPT_GET_HW_CLASS(CoreId, ChInCoreIndex))
        {
            case GPT_HW_GTM:
            {
                TimeRemaining = Gtm_Timer_Hal_GetChannelInfo(
                    /* #Violation: Gpt_c_REF_5 */
                    GPT_GET_GTM_CHANNEL_OBJECT_PTR(HwCfgMapIndex), GTM_TIMER_COUNT_REMAIN);
                break;
            }
            case GPT_HW_BASETIMER:
            {
                TimeRemaining = Basetimer_Hal_GetRemainingCount(
                    /* #Violation: Gpt_c_REF_5 */
                    GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex));
                break;
            }
            default:
            {
                /* Do nothing */
                break;
            }
        }
    } /* End of ErrValue == E_NOT_OK */

    /* Return the Remaining Time:
       SWS_Gpt_00083, SWS_Gpt_00303, SWS_Gpt_00305 */
    return TimeRemaining;
} /* End of API Gpt_GetTimeRemaining() */
#endif /* GPT_TIME_REMAINING_API == STD_ON */

/****************************************************************************************************
*   Function Name           : Gpt_StartTimer
*
*   Service ID              : 0x05
*
*   Description             : Starts a timer channel.
*
*   Parameters in           : Channel: Numeric identifier of the GPT channel.
*                             Value: Target time in number of ticks.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant (but not for the same timer channel).
*
*   Return value            : None.
*
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00284],[SWS_Gpt_00274],[SWS_Gpt_00115],[SWS_Gpt_00364],
*                             [SWS_Gpt_00212],[SWS_Gpt_00218],[SWS_Gpt_00224],[SWS_Gpt_00084].
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(void, GPT_PUBLIC_CODE) Gpt_StartTimer
(
    /* #Violation: Gpt_c_REF_6 */
    Gpt_ChannelType Channel,
    /* #Violation: Gpt_c_REF_6 */
    Gpt_ValueType Value
)
{
    Mcal_CoreType CoreId;
    uint32 HwCfgMapIndex;
    Gpt_ChannelStatusType* ChannelStatusPtr;
    uint8 ChInCoreIndex;
    Std_ReturnType ErrValue;
    boolean SafetyFlag;
    Std_ReturnType LockStatus;

    SafetyFlag = TRUE;
    LockStatus = E_OK;
    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* SWS_Gpt_00212, SWS_Gpt_00224 */
    ErrValue = Gpt_StartTimerCheck(Channel, Value, CoreId);

    if (E_OK == ErrValue)
    {
        /* Get hardware configuration mapping index */
        /* #Violation: Gpt_c_REF_5 */
        HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(Channel);
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* Get the channel global variables pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);

        /* Enter Protected area */
        GPT_ENTER_CRITICAL_SECTION(Gpt_StartTimer);
        /* SWS_Gpt_00364 */
        ChannelStatusPtr->Status = GPT_CH_RUNNING;

        /* #Violation: Gpt_c_REF_5 */
        switch(GPT_GET_HW_CLASS(CoreId, ChInCoreIndex))
        {
            case GPT_HW_GTM:
            {
                /* Clear CN0 register to ensure the timer starts from zero */
                /* #Violation: Gpt_c_REF_5 */
                Gtm_Timer_Hal_SetCounterValue(GPT_GET_GTM_CHANNEL_OBJECT_PTR(HwCfgMapIndex), 
                                              MCAL_ZERO);
                LockStatus = Mcal_GetLock(MCAL_LOCK_ID_GPT);
                if(E_OK == LockStatus)
                {
                    /* SWS_Gpt_00274:
                       start the selected timer channel with a defined target time */
                    /* #Violation: Gpt_c_REF_5 */
                    SafetyFlag = Gtm_Timer_Hal_StartChannel(GPT_GET_GTM_CHANNEL_OBJECT_PTR(HwCfgMapIndex), Value);
                    Mcal_ReleaseLock(MCAL_LOCK_ID_GPT);
                }
                break;
            }
            case GPT_HW_BASETIMER:
            {
                /* Set target period value */
                /* #Violation: Gpt_c_REF_5 */
                Basetimer_Hal_SetLoad(GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex), Value);
                /* Clear the interrupt status */
                /* #Violation: Gpt_c_REF_5 */
                Basetimer_Hal_ClearFlag(GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex));
                /* Start the timer */
                /* #Violation: Gpt_c_REF_5 */
                Basetimer_Hal_StartTimer(GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex));
                break;
            }
            default:
            {
                /* Do nothing */
                break;
            }
        }
        /* Exit Protected area */
        GPT_EXIT_CRITICAL_SECTION(Gpt_StartTimer);

#if (GPT_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            GPT_DET_RUNTIME_ERROR_REPORT(GPT_START_TIMER_SID, GPT_E_SAFETY_CHECK_FAILED);
        }
        if(E_OK != LockStatus)
        {
            /* Get lock timeout */
            GPT_DET_RUNTIME_ERROR_REPORT(GPT_START_TIMER_SID, GPT_E_LOCK_TIMEOUT);
        }
#else
        MCAL_UNUSED_VAR(SafetyFlag);
#endif /* GPT_SAFETY_ENABLE == STD_ON */
    }
} /* End of API Gpt_StartTimer() */


/****************************************************************************************************
*   Function Name           : Gpt_StopTimer
*
*   Service ID              : 0x06
*
*   Description             : Stops a timer channel.
*
*   Parameters in           : Channel: Numeric identifier of the GPT channel
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant (but not for the same timer channel).
*
*   Return value            : None.
*
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00013], [SWS_Gpt_00343], [SWS_Gpt_00099], [SWS_Gpt_00344],
*                             [SWS_Gpt_00116], [SWS_Gpt_00213], [SWS_Gpt_00225].
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(void, GPT_PUBLIC_CODE) Gpt_StopTimer
(
    /* #Violation: Gpt_c_REF_6 */
    Gpt_ChannelType  Channel
)
{
    uint32 HwCfgMapIndex;
    Gpt_ChannelStatusType* ChannelStatusPtr;
    Mcal_CoreType CoreId;
    uint8 ChInCoreIndex;
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Declare the variable to store the DET return value */
    Std_ReturnType ErrValue;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    boolean SafetyFlag;
    Std_ReturnType LockStatus;
    
    SafetyFlag = TRUE;
    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00213, SWS_Gpt_00225 */
    ErrValue = Gpt_CheckDetErrors(Channel, GPT_STOP_TIMER_SID);

    if(E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* Get the channel global variables pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        /* Get hardware configuration mapping index */
        /* #Violation: Gpt_c_REF_5 */
        HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(Channel);
        /* SWS_Gpt_00344: 
           Channel in state "initialized", "stopped" or "expired", 
           the function leave without any action */
        if(GPT_CH_RUNNING == ChannelStatusPtr->Status)
        {
            /* Enter Protected area  */
            GPT_ENTER_CRITICAL_SECTION(Gpt_StopTimer);
            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_GPT);
            if(E_OK == LockStatus)
            {
                /* SWS_Gpt_00013:
                Stop the selected timer channel */
                /* #Violation: Gpt_c_REF_5 */
                SafetyFlag = Gpt_HWStopTimer(HwCfgMapIndex, GPT_GET_HW_CLASS(CoreId, ChInCoreIndex));
                /* SWS_Gpt_00343 */
                ChannelStatusPtr->Status = GPT_CH_STOPPED;
                Mcal_ReleaseLock(MCAL_LOCK_ID_GPT);
            }
            /* Exit Protected area */
            GPT_EXIT_CRITICAL_SECTION(Gpt_StopTimer);

#if (GPT_SAFETY_ENABLE == STD_ON)
            if(TRUE != SafetyFlag)
            {
                GPT_DET_RUNTIME_ERROR_REPORT(GPT_STOP_TIMER_SID, GPT_E_SAFETY_CHECK_FAILED);
            }
            if(E_OK != LockStatus)
            {
                /* Get lock timeout */
                GPT_DET_RUNTIME_ERROR_REPORT(GPT_STOP_TIMER_SID, GPT_E_LOCK_TIMEOUT);
            }
#else
            MCAL_UNUSED_VAR(SafetyFlag);
#endif /* GPT_SAFETY_ENABLE == STD_ON */
        }
    }
} /* End of API Gpt_StopTimer() */

#if (GPT_PREDEFTIMER_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_GetPredefTimerValue
*
*   Service ID              : 0x0d
*
*   Description             : Delivers the current value of the desired GPT Predef Timer.
*
*   Parameters in           : PredefTimer: GPT Predef Timer.
*
*   Parameters inout        : None.
*
*   Parameters out          : TimeValuePtr: Pointer to time value destination data in RAM.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Std_ReturnType.
*                             E_OK: no error has been detected
*                             E_NOT_OK: aborted due to errors
*
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00394], [SWS_Gpt_00395], [SWS_Gpt_00396], [SWS_Gpt_00397] ,
*                             [SWS_Gpt_00402], [SWS_Gpt_00398], [SWS_Gpt_00399], [SWS_Gpt_00400] ,
*                             [SWS_Gpt_00403] .
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(Std_ReturnType, GPT_PUBLIC_CODE)Gpt_GetPredefTimerValue
(
    Gpt_PredefTimerType PredefTimer,
    /* #Violation: Gpt_c_REF_8 */
    P2VAR(uint32, AUTOMATIC, GPT_APPL_DATA) TimeValuePtr
)
{
    Std_ReturnType ErrValue;
    Mcal_CoreType CoreId;
    uint32 CounterValue;

#if (GPT_DEV_ERROR_DETECT == STD_OFF)
    ErrValue = E_OK;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Gpt_00398, SWS_Gpt_00399, SWS_Gpt_00400, SWS_Gpt_00403 */
    ErrValue = Gpt_PredefTimerDetCheck(PredefTimer, TimeValuePtr);

    if (E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        /* #Violation: Gpt_c_REF_5 */
        CoreId = Mcal_GetCoreId();
        /* SWS_Gpt_00402:
         * If the GPT driver is not initialized, in sleep or the GPT
         * Predefine Timer is not enabled, the function Gpt_GetPredefTimerValue shall
         * return E_NOT_OK */
        if (GPT_INITIALIZED == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState)
        {
#if (GPT_PREDEFTIMER_1US_EN == STD_ON)
            /* Read the counter value of the 1us 32bit Predefine Timer */
            if(GPT_PREDEF_TIMER_100US_32BIT != PredefTimer)
            {
                /* #Violation: Gpt_c_REF_2 */
                CounterValue = Basetimer_Hal_GetElapsedCount(Gpt_ConfigPtr->GptPredefTimerPtr[0U]);
                /* A lower bit timer can be derived from a higher bit timer by a simple software 
                   mask operation */
                if(GPT_PREDEF_TIMER_1US_16BIT == PredefTimer)
                {
                    (*TimeValuePtr) = 0xFFFFU & CounterValue;
                }
                else if(GPT_PREDEF_TIMER_1US_24BIT == PredefTimer)
                {
                    (*TimeValuePtr) = 0xFFFFFFU & CounterValue;
                }
                /* #Violation: Gpt_c_REF_7 */
                else
                {
                    (*TimeValuePtr) = CounterValue;
                }
            }

#endif /* GPT_PREDEFTIMER_1US_EN == STD_ON */
#if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
            /* Read the counter value of the 100us 32bit Predefine Timer */
            if(GPT_PREDEF_TIMER_100US_32BIT == PredefTimer)
            {
                /* #Violation: Gpt_c_REF_5 */
                CounterValue = Basetimer_Hal_GetElapsedCount(Gpt_ConfigPtr->GptPredefTimerPtr[1U]);
                (*TimeValuePtr) = CounterValue;
            }
#endif /* GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON */
        }
        else
        {
            ErrValue = E_NOT_OK;
        }
    }
    /* SWS_Gpt_00402 */
    return ErrValue;
} /* End of API Gpt_GetPredefTimerValue() */
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

/* SWS_Gpt_00199: 
    Pre compile time configurable On/Off by the configuration parameter */
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_EnableNotification
*
*   Service ID              : 0x07
*
*   Description             : Enables the interrupt notification for a channel
*                             (relevant in normal mode).
*
*   Parameters in           : Channel: Numeric identifier of the GPT channel
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant (but not for the same timer channel)
*
*   Return value            : None.
*
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00286], [SWS_Gpt_00014], [SWS_Gpt_00117], [SWS_Gpt_00199],
*                             [SWS_Gpt_00226], [SWS_Gpt_00214], [SWS_Gpt_00377].
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(void, GPT_PUBLIC_CODE) Gpt_EnableNotification
(
    /* #Violation: Gpt_c_REF_6 */
    Gpt_ChannelType Channel
)
{
    uint32 HwCfgMapIndex;
    Mcal_CoreType CoreId;
    Gpt_ChannelStatusType* ChannelStatusPtr;
    uint8 ChInCoreIndex;
    Std_ReturnType ErrValue;
    boolean SafetyFlag;
    
    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    ErrValue = Gpt_EnableNotificationCheck(Channel, CoreId);

    /* SWS_Gpt_00226, SWS_Gpt_00214 */
    if(E_OK == ErrValue)
    {
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* Get the channel global variables pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        /* Get hardware configuration mapping index */
        /* #Violation: Gpt_c_REF_5 */
        HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(Channel);
        /* Enter Protected area  */
        GPT_ENTER_CRITICAL_SECTION(Gpt_EnableNotification);

        ChannelStatusPtr->NotifyStatus = TRUE;
        /* SWS_Gpt_00014 */
        SafetyFlag = Gpt_HWSetTimerInterrupt(HwCfgMapIndex, 
                                                /* #Violation: Gpt_c_REF_5 */
                                                GPT_GET_HW_CLASS(CoreId, ChInCoreIndex), TRUE);

        /* Exit Protected area */
        GPT_EXIT_CRITICAL_SECTION(Gpt_EnableNotification);

#if (GPT_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            GPT_DET_RUNTIME_ERROR_REPORT(GPT_ENABLE_NOTIFY_SID, GPT_E_SAFETY_CHECK_FAILED);
        }
#else
        MCAL_UNUSED_VAR(SafetyFlag);
#endif /* GPT_SAFETY_ENABLE == STD_ON */
    }
} /* End of API Gpt_EnableNotification() */
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */

/* SWS_Gpt_00200:
   Pre compile time configurable On/Off by the configuration parameter */
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_DisableNotification
*
*   Service ID              : 0x08
*
*   Description             : Disables the interrupt notification for a channel
*                             (relevant in normal mode).
*
*   Parameters in           : Channel: Numeric identifier of the GPT channel
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant (but not for the same timer channel)
*
*   Return value            : None.
*
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00287], [SWS_Gpt_00015], [SWS_Gpt_00118], [SWS_Gpt_00200] ,
*                             [SWS_Gpt_00227], [SWS_Gpt_00217], [SWS_Gpt_00379] .
****************************************************************************************************/
/* #Violation: Gpt_c_REF_10 */
FUNC(void, GPT_PUBLIC_CODE) Gpt_DisableNotification
(
    /* #Violation: Gpt_c_REF_6 */
    Gpt_ChannelType  Channel
)
{
    Mcal_CoreType CoreId;
    Gpt_ChannelStatusType* ChannelStatusPtr;
    uint32 HwCfgMapIndex;
    Std_ReturnType ErrValue;
    uint8 ChInCoreIndex;
    boolean SafetyFlag;

    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    /* SWS_Gpt_00217 */
    ErrValue = Gpt_DisableNotificationCheck(Channel, CoreId);

    if (E_OK == ErrValue)
    {
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* Get the channel global variables pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        /* Get hardware configuration mapping index */
        /* #Violation: Gpt_c_REF_5 */
        HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(Channel);

        /* Enter Protected area */
        GPT_ENTER_CRITICAL_SECTION(Gpt_DisableNotification);
        /* SWS_Gpt_00014 */
        /* Disable the interrupt of the channel */
        SafetyFlag = Gpt_HWSetTimerInterrupt(HwCfgMapIndex, 
                                             /* #Violation: Gpt_c_REF_5 */
                                             GPT_GET_HW_CLASS(CoreId, ChInCoreIndex), FALSE);

        ChannelStatusPtr->NotifyStatus = FALSE;
        /* Exit Protected area */
        GPT_EXIT_CRITICAL_SECTION(Gpt_DisableNotification);

#if (GPT_SAFETY_ENABLE == STD_ON)
        if(TRUE != SafetyFlag)
        {
            GPT_DET_RUNTIME_ERROR_REPORT(GPT_DISABLE_NOTIFY_SID, GPT_E_SAFETY_CHECK_FAILED);
        }
#else
        MCAL_UNUSED_VAR(SafetyFlag);
#endif /* GPT_SAFETY_ENABLE == STD_ON */
    }
} /* End of API Gpt_DisableNotification() */
#endif/*End of GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */

/* /[SWS_Gpt_00201]  The function Gpt_SetMode shall be pre compile time 
   configurable On/Off by the configuration parameter: 
   GptWakeupFunctionalityApi. */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_SetMode
*
*   Service ID              : 0x09
*
*   Description             : Sets the operation mode of the GPT.
*
*   Parameters in           : Mode: Numeric identifier of the GPT channel
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
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00288], [SWS_Gpt_00151], [SWS_Gpt_00255], [SWS_Gpt_00152]
*                             [SWS_Gpt_00153], [SWS_Gpt_00164], [SWS_Gpt_00165], [SWS_Gpt_00341]
*                             [SWS_Gpt_00228], [SWS_Gpt_00231], [SWS_Gpt_00201], [SWS_Gpt_00392]
*                             [SWS_Gpt_00393].
****************************************************************************************************/
FUNC(void, GPT_PUBLIC_CODE) Gpt_SetMode
(
    Gpt_ModeType  Mode
)
{
    Mcal_CoreType CoreId;
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */

    CoreId = Mcal_GetCoreId();
    /* #Violation: Gpt_c_REF_5 */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    ErrValue = Gpt_SetModeDetCheck(Mode, CoreId);

    if(E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        /* /[SWS_Gpt_00255]  The function Gpt_SetMode is only available if the configuration 
           parameter GptReportWakeupSource is enabled. */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        /* /[SWS_Gpt_00151]  The function Gpt_SetMode shall set the operation mode of the 
           GPT driver to the given mode parameter. */
        /* To sleep mode */
        if (GPT_MODE_SLEEP == Mode)
        {
            Gpt_SetSleepMode();
        }
        /* Switch from sleep mode to normal mode */
        else
        {
            Gpt_SetNormalMode();
        }
#endif /* GPT_REPORT_WAKEUP_SOURCE == STD_ON */
    }
} /* End of API Gpt_SetMode() */
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */

/* /[SWS_Gpt_00202]  The function Gpt_DisableWakeup shall be pre compile time 
   configurable On/Off by the configuration parameter: 
   GptWakeupFunctionalityApi. */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_DisableWakeup
*
*   Service ID              : 0x0a
*
*   Description             : Disables the wakeup interrupt of a channel (relevant in sleep mode).
*
*   Parameters in           : Mode: Numeric identifier of the GPT channel
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant (but not for the same timer channel).
*
*   Return value            : None.
*
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00289], [SWS_Gpt_00159], [SWS_Gpt_00157], [SWS_Gpt_00155]
*                             [SWS_Gpt_00202], [SWS_Gpt_00215], [SWS_Gpt_00229].
****************************************************************************************************/
FUNC(void, GPT_PUBLIC_CODE) Gpt_DisableWakeup
(
    Gpt_ChannelType Channel
)
{
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    Mcal_CoreType CoreId;
    uint8 ChInCoreIndex;
    Gpt_ChannelStatusType* ChannelStatusPtr;
#endif /* GPT_REPORT_WAKEUP_SOURCE == STD_ON */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    ErrValue = Gpt_DisableWakeupDetCheck(Channel);

    if(E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        /* /[SWS_Gpt_00157]  The function Gpt_DisableWakeup is only feasible, if 
           GptReportWakeupSource is statically configured available. */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        CoreId = Mcal_GetCoreId();
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* Get the channel global variables pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        /* /[SWS_Gpt_00159]  The function Gpt_DisableWakeup shall disable the wakeup 
           interrupt of the referenced channel configured for wakeup. The function shall save an 
           attribute like "wakeup disabled" of the channel. 
           Comment: This attribute affects the wakeup interrupt always when the driver is in 
           "sleep mode". In "normal mode" the attribute has no influence. */
        if(TRUE == ChannelStatusPtr->WakeUpStatus)
        {
            if(GPT_MODE_SLEEP == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState)
            {
                ChannelStatusPtr->WakeUpStatus = FALSE;
            }
        }
#endif /* GPT_REPORT_WAKEUP_SOURCE == STD_ON */
    }
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */

/* /[SWS_Gpt_00203]  The function Gpt_EnableWakeup shall be pre compile time 
   configurable On/Off by the configuration parameter: 
   GptWakeupFunctionalityApi. */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_EnableWakeup
*
*   Service ID              : 0x0b
*
*   Description             : Enables the wakeup interrupt of a channel (relevant in sleep mode).
*
*   Parameters in           : Mode: Numeric identifier of the GPT channel
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant (but not for the same timer channel).
*
*   Return value            : None.
*
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00290], [SWS_Gpt_00160], [SWS_Gpt_00158], [SWS_Gpt_00156]
*                             [SWS_Gpt_00203], [SWS_Gpt_00230], [SWS_Gpt_00216].
****************************************************************************************************/
FUNC(void, GPT_PUBLIC_CODE) Gpt_EnableWakeup
(
    Gpt_ChannelType Channel
)
{
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    Mcal_CoreType CoreId;
    uint8 ChInCoreIndex;
    Gpt_ChannelStatusType* ChannelStatusPtr;
#endif /* GPT_REPORT_WAKEUP_SOURCE == STD_ON */

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    ErrValue = Gpt_EnableWakeupDetCheck(Channel);

    if(E_OK == ErrValue)
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        /* /[SWS_Gpt_00158]  The function Gpt_DisableWakeup is only feasible, if 
           GptReportWakeupSource is statically configured available. */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        CoreId = Mcal_GetCoreId();
        /* /[SWS_Gpt_00157]  The function Gpt_DisableWakeup is only feasible, if 
           GptReportWakeupSource is statically configured available. */
        /* Get the channel index in current core */
        ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(Channel);
        /* Get the channel global variables pointer */
        ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        /* /[SWS_Gpt_00160]  The function Gpt_DisableWakeup shall disable the wakeup 
           interrupt of the referenced channel configured for wakeup. The function shall save an 
           attribute like "wakeup enabled" of the channel. 
           Comment: This attribute affects the wakeup interrupt always when the driver is in 
           "sleep mode". In "normal mode" the attribute has no influence. */
        if(GPT_MODE_NORMAL == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState)
        {
          if(TRUE == GPT_GET_WAKEUP_ENABLE_CONFIG(CoreId, ChInCoreIndex))
          {
              ChannelStatusPtr->WakeUpStatus = TRUE;
          }
        }
#endif /* GPT_REPORT_WAKEUP_SOURCE == STD_ON */
    }
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */

/* /[SWS_Gpt_00324]  The function Gpt_CheckWakeup shall be pre compile time 
   configurable On/Off by the configuration parameter: 
   GptWakeupFunctionalityApi. */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Gpt_CheckWakeup
*
*   Service ID              : 0x0c
*
*   Description             : Checks if a wakeup capable GPT channel is the source for a wakeup event and 
*                             calls the ECU state manager service EcuM_SetWakeupEvent in case of a valid 
*                             GPT channel wakeup event.
*
*   Parameters in           : WakeupSource: Information on wakeup source to be checked. The associated 
*                             GPT channel can be determined from configuration data
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
*   Preconditions           : GPT Module must be initialized.
*
*   AUTOSAR_Requirement     : [SWS_Gpt_00328], [SWS_Gpt_00321], [SWS_Gpt_00322], [SWS_Gpt_00323]
*                             [SWS_Gpt_00324], [SWS_Gpt_00325].
****************************************************************************************************/
FUNC(void, GPT_PUBLIC_CODE) Gpt_CheckWakeup
(
    EcuM_WakeupSourceType WakeupSource
)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* /[SWS_Gpt_00325]  If development error detection is enabled for GPT module: 
      If the driver is not initialized, the function Gpt_CheckWakeup shall raise the error 
      GPT_E_UNINIT. */
    /* Check if the GPT Driver is initialized properly */
    if(GPT_UNINITIALIZED == (Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState))
    {
        /* Call API without GPT initialization */
        GPT_DET_ERROR_REPORT(GPT_CHECK_WAKEUP_SID, GPT_E_UNINIT);
    }
    else
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
    {
        /* /[SWS_Gpt_00322]  The function Gpt_CheckWakeup is only feasible, if 
          GptReportWakeupSource is statically configured available. */
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
        /* /[SWS_Gpt_00321]  The function Gpt_CheckWakeup shall check if a wakeup 
           capable GPT channel is the source for a wakeup event and call 
           EcuM_SetWakeupEvent to indicate a valid timer wakeup event to the ECU State 
           Manager [8]. */
        if(WakeupSource == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_WakeupChannelInfo)
        {
            EcuM_SetWakeupEvent(WakeupSource);
        }
#endif /* GPT_REPORT_WAKEUP_SOURCE == STD_ON */
    }
}
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */

/****************************************************************************************************
 *   Function Name           : Gpt_Gtm_ISRHandler
 *
 *   Service ID              : 0x0F.
 *
 *   Description             : The interrupt handler.
 *
 *   Parameters in           : ModuleIndex: Hardware module index
 *                             Channel: Hardware channel index
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same timer channel).
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_c_REF_6 */
FUNC(void, GPT_PUBLIC_CODE)Gpt_Gtm_ISRHandler
(
    uint8 ModuleIndex, 
    uint8 Channel
)
{
    uint32 TimerPeriod;
    uint32 HwCfgMapIndex;
    Gpt_ChannelStatusType* ChannelStatusPtr;
    Mcal_CoreType CoreId;
    uint8 ChInCoreIndex;
    boolean IntStatus;  
    boolean IntEnStatus;
    boolean OneShotEnable;
    Gtm_Output_Driver HwChannelObject;
    uint8 Offset;
    uint8 LogicChannel;
    boolean SafetyFlag;

    SafetyFlag = TRUE;
    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    if(NULL_PTR != Gpt_ConfigPtr)
    {
        if(GPT_INITIALIZED == (Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState))
        {
            Offset = (ModuleIndex * 16U) + Channel;
            /* Find logic from hardware and logic channel mapping table */
            LogicChannel = Gpt_ConfigPtr->GptHwChannelMapPtr[0U][Offset];

            /* Except for the 0xFF, the logical channel ID is valid */
            if(0xFFU != LogicChannel)
            {
                /* #Violation: Gpt_c_REF_12 */
                if(CoreId == (Mcal_CoreType)Gpt_ConfigPtr->GptChannelIdxmapPtr[LogicChannel].Core)
                {
                    HwChannelObject.module = 0U;
                    HwChannelObject.moduleIndex = ModuleIndex;
                    HwChannelObject.channel = Channel;
                    ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(LogicChannel);
                    /* Get channel status variables pointer */
                    ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
                    /* #Violation: Gpt_c_REF_5 */
                    HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(LogicChannel);
                    /* Get channel interrupt enable status */
                    IntEnStatus = Gtm_Timer_Hal_GetInterruptEnableStatus((const Gtm_Output_Driver *)&HwChannelObject);
        
                    /* Get current interrupt flag */
                    IntStatus = Gtm_Timer_Hal_GetInterruptStatus((const Gtm_Output_Driver *)&HwChannelObject);
      
                    /* If interrupt enabled and interrupt generated, execute the interrupt handle */
                    if((TRUE == IntEnStatus) && (TRUE == IntStatus))
                    {
                        /* Clear current interrupt status */
                        Gtm_Timer_Hal_ClearInterruptStatus((const Gtm_Output_Driver *)&HwChannelObject);
                        /* Get one-shot enable status */
                        OneShotEnable = Gpt_ConfigPtr->GptHwGtmConfigPtr[HwCfgMapIndex].
                                        HwChannelConfig.isOneShotEnable;
        
                        /* If the channel mode is one-shot */
                        if(TRUE == OneShotEnable)
                        {
                            /* Set channel status to expired */
                            ChannelStatusPtr->Status = GPT_CH_EXPIRED;
                            /* Stop the selected timer channel */
                            SafetyFlag &= Gtm_Timer_Hal_StopChannel((const Gtm_Output_Driver *)&HwChannelObject);
                            /* Get period */
                            TimerPeriod = Gtm_Timer_Hal_GetCompareZero((const Gtm_Output_Driver *)&HwChannelObject);
                            /* Set CN0 to CM0 to support Gpt_GetTimeElapsed and
                            * Gpt_GetTimeRemain at time match situation */
                            Gtm_Timer_Hal_SetCounterValue((const Gtm_Output_Driver *)&HwChannelObject, TimerPeriod);
                        }
        
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
                        if((GPT_MODE_NORMAL == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState) && 
                          (TRUE == ChannelStatusPtr->NotifyStatus))
                        {
                            /* Invoke the user notification function */
                            Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
                                Gpt_ChannelConfigPtr[ChInCoreIndex].NotificationFuncPtr();
                        }
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */
    
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
                        if((GPT_MODE_SLEEP == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState) && 
                          (TRUE == ChannelStatusPtr->WakeUpStatus))
                        {
                            Gpt_CoreDriverStatusPtr[CoreId]->Gpt_WakeupChannelInfo = 
                            Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
                                  Gpt_ChannelConfigPtr[ChInCoreIndex].GptChannelWakeupInfo;
                            /* /[SWS_Gpt_00326] EcuM_CheckWakeup shall be called within the Interrupt 
                              Service Routine, servicing the GPT channel wakeup event on wakeup-capable 
                              channels. */
                            EcuM_CheckWakeup(Gpt_CoreDriverStatusPtr[CoreId]->Gpt_WakeupChannelInfo);
                        }
#endif /* GPT_REPORT_WAKEUP_SOURCE == STD_ON */
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */
                    }
                }
#if (GPT_DEV_ERROR_DETECT == STD_ON)
                else
                {
                    GPT_DET_ERROR_REPORT(GPT_SID_GTM_ISRHANDLER_SID, GPT_E_CORE_CHANNEL_MISMATCH);
                }
#endif /* (GPT_DEV_ERROR_DETECT \== STD_ON) */
            }
        }
    }

    if(TRUE != SafetyFlag)
    {
#if (GPT_SAFETY_ENABLE == STD_ON)
        GPT_DET_RUNTIME_ERROR_REPORT(GPT_SID_GTM_ISRHANDLER_SID, GPT_E_SAFETY_CHECK_FAILED);
#endif /* GPT_SAFETY_ENABLE == STD_ON */
    }
} /* End of API Gpt_Gtm_ISRHandler() */

/****************************************************************************************************
 *   Function Name           : Gpt_Basetimer_ISRHandler
 *
 *   Service ID              : 0xA0.
 *
 *   Description             : The interrupt handler.
 *
 *   Parameters in           : HwChannel: BASETIMER hardware index.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same timer channel).
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
FUNC(void, GPT_PUBLIC_CODE)Gpt_Basetimer_ISRHandler
(
    uint8 HwChannel
)
{
    Mcal_CoreType CoreId;
    uint32 HwCfgMapIndex;
    Gpt_ChannelStatusType* ChannelStatusPtr;
    Basetimer_Mode OneShotEnable;
    uint8 ChInCoreIndex;
    uint8 LogicChannel;
    
    /* #Violation: Gpt_c_REF_5 */
    CoreId = Mcal_GetCoreId();

    if(NULL_PTR != Gpt_ConfigPtr)
    {
        if((NULL_PTR != (Gpt_CoreDriverStatusPtr[CoreId])) && 
           (GPT_INITIALIZED == (Gpt_CoreDriverStatusPtr[CoreId]->Gpt_InitState)))
        {
            /* Find logic from hardware and logic channel mapping table */
            LogicChannel = Gpt_ConfigPtr->GptHwChannelMapPtr[1U][HwChannel];
            /* Except for the 0xFF, the logical channel ID is valid */
            if(0xFFU != LogicChannel)
            {
                /* #Violation: Gpt_c_REF_12 */
                if(CoreId == (Mcal_CoreType)Gpt_ConfigPtr->GptChannelIdxmapPtr[LogicChannel].Core)
                {
                    /* Get channel index in current core */
                    ChInCoreIndex = GPT_GET_CHANNEL_INDEX_IN_CORE(LogicChannel);
                    /* Get hardware configuration mapping index */
                    /* #Violation: Gpt_c_REF_5 */
                    HwCfgMapIndex = GPT_GET_HWCONFIG_MAPINDEX(LogicChannel);
                    /* [SWS_Gpt_00327]  The ISR's, providing the wakeup events, shall be responsible 
                      for resetting the interrupt flags (if needed by hardware). */
                    /* Clear the interrupt */
                    /* #Violation: Gpt_c_REF_5 */
                    Basetimer_Hal_ClearFlag(GPT_GET_BASETIMER_CHANNEL_OBJECT_PTR(HwCfgMapIndex));
                    
                    /* Get the channel mode */
                    OneShotEnable = Gpt_ConfigPtr->GptHwBaseTimerConfigPtr[HwCfgMapIndex].HwChannelConfig.mode;
                    /* Get channel status variables pointer */
                    ChannelStatusPtr = GPT_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
                    /* If the channel mode is one-shot */
                    if(BASETIMER_MODE_ONESHOT == OneShotEnable)
                    {
                        ChannelStatusPtr->Status = GPT_CH_EXPIRED;
                    }
        
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
                    if((GPT_MODE_NORMAL == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState) && 
                        (TRUE == ChannelStatusPtr->NotifyStatus))
                    {
                        /* Invoke the user notification function */
                        Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
                            Gpt_ChannelConfigPtr[ChInCoreIndex].NotificationFuncPtr();
                    }
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */
        
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
                    if((GPT_MODE_SLEEP == Gpt_CoreDriverStatusPtr[CoreId]->Gpt_ModeState) && 
                        (TRUE == ChannelStatusPtr->WakeUpStatus))
                    {
                        Gpt_CoreDriverStatusPtr[CoreId]->Gpt_WakeupChannelInfo = 
                        Gpt_ConfigPtr->CoreConfigPtr[CoreId]->
                              Gpt_ChannelConfigPtr[ChInCoreIndex].GptChannelWakeupInfo;
                        /* /[SWS_Gpt_00326] EcuM_CheckWakeup shall be called within the Interrupt 
                          Service Routine, servicing the GPT channel wakeup event on wakeup-capable 
                          channels. */
                        EcuM_CheckWakeup(Gpt_CoreDriverStatusPtr[CoreId]->Gpt_WakeupChannelInfo);
                    }
#endif /* GPT_REPORT_WAKEUP_SOURCE == STD_ON */
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */
                }
#if (GPT_DEV_ERROR_DETECT == STD_ON)
                else
                {
                    GPT_DET_ERROR_REPORT(GPT_SID_BASETIMER_ISRHANDLER_SID, 
                                         GPT_E_CORE_CHANNEL_MISMATCH);
                }
#endif /* (GPT_DEV_ERROR_DETECT \== STD_ON) */
            }
        }
    }
} /* End of API Gpt_Basetimer_ISRHandler() */

/* #Violation: Gpt_c_REF_9 */
#define GPT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Gpt_c_REF_3 */     
#include "Gpt_MemMap.h"
/****************************************************************************************************
 **                          End of File                                                            **
 ****************************************************************************************************/
