/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Msc.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Msc
 *
 *   brief                 : This file contains all API functions of Msc Driver
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
*#Msc_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Msc_c_REF_3:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Msc_c_REF_4:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Msc_c_REF_9:CertC-PRE00-C; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Msc_c_REF_11:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Msc_c_REF_12:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Msc_c_REF_13:MISRAC2012-Rule-11.4; 
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Msc_c_REF_14:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Msc_GeneralTypes.h"
#include "msc_hal.h"
#include "Msc.h"
#include "Msc_Version.h"
#include "Msc_Cfg.h"
#include "Mcall.h"
#include "SchM_Msc.h"
#include "Det.h"
#include "tha6_cfg.h"
/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (MSC_VENDOR_ID != MSC_CFG_VENDOR_ID)
#error "Msc.c : Mismatch in Vendor ID"
#endif /* MSC_VENDOR_ID != MSC_CFG_VENDOR_ID */

#if (MSC_MODULE_ID != MSC_CFG_MODULE_ID)
#error "Msc.c : Mismatch in Module ID"
#endif /* \(MSC_MODULE_ID != MSC_CFG_MODULE_ID) */

#if (MSC_AR_RELEASE_MAJOR_VERSION != MSC_CFG_AR_RELEASE_MAJOR_VERSION)
#error "Msc.c : Mismatch in Release Major Version"
#endif /* MSC_AR_RELEASE_MAJOR_VERSION != MSC_CFG_AR_RELEASE_MAJOR_VERSION */

#if (MSC_AR_RELEASE_MINOR_VERSION != MSC_CFG_AR_RELEASE_MINOR_VERSION)
#error "Msc.c : Mismatch in Release Minor Version"
#endif /* MSC_AR_RELEASE_MINOR_VERSION != MSC_CFG_AR_RELEASE_MINOR_VERSION */

#if (MSC_AR_RELEASE_REVISION_VERSION != MSC_CFG_AR_RELEASE_REVISION_VERSION)
#error "Msc.c : Mismatch in Release Revision Version"
#endif /* MSC_AR_RELEASE_REVISION_VERSION != MSC_CFG_AR_RELEASE_REVISION_VERSION */

#if (MSC_SW_MAJOR_VERSION != MSC_CFG_SW_MAJOR_VERSION)
#error "Msc.c : Mismatch in Software Major Version"
#endif /* MSC_SW_MAJOR_VERSION != MSC_CFG_SW_MAJOR_VERSION */

#if (MSC_SW_MINOR_VERSION != MSC_CFG_SW_MINOR_VERSION)
#error "Msc.c : Mismatch in Software Minor Version"
#endif /* MSC_SW_MINOR_VERSION != MSC_CFG_SW_MINOR_VERSION */

#if (MSC_SW_PATCH_VERSION != MSC_CFG_SW_PATCH_VERSION)
#error "Msc.c : Mismatch in Software Patch Version"
#endif /* \(MSC_SW_PATCH_VERSION != MSC_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Global Variable Definitions                                      **
****************************************************************************************************/
/* Global variables of all channels in core0 */
/* #Violation: Msc_c_REF_12 */
#define MSC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

#if (MSC_MAX_CHANNEL_TO_CORE0 != 0U)

#if (MSC_DEV_ERROR_DETECT == STD_ON)
static VAR(Msc_ChannelStatusType, MSC_VAR_FAST_CLEARED)
        Msc_ChannelStatusCore0[MSC_MAX_CHANNEL_TO_CORE0];
#endif /* MSC_DEV_ERROR_DETECT \== STD_ON */
static VAR(Msc_InitStateType, MSC_VAR_FAST_CLEARED) Msc_DriverStatusCore0;

#endif /* MSC_MAX_CHANNEL_TO_CORE0 != 0U */

/* #Violation: Msc_c_REF_12 */
#define MSC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

/* Global variables of all channels in core1 */
/* #Violation: Msc_c_REF_12 */
#define MSC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

#if defined(MSC_MAX_CHANNEL_TO_CORE1) && (MSC_MAX_CHANNEL_TO_CORE1 != 0U)
#if (MSC_DEV_ERROR_DETECT == STD_ON)
static VAR(Msc_ChannelStatusType, MSC_VAR_FAST_CLEARED)
        Msc_ChannelStatusCore1[MSC_MAX_CHANNEL_TO_CORE1];
#endif /* MSC_DEV_ERROR_DETECT \== STD_ON */
static VAR(Msc_InitStateType, MSC_VAR_FAST_CLEARED) Msc_DriverStatusCore1;

#endif /* defined(MSC_MAX_CHANNEL_TO_CORE1) \&& (MSC_MAX_CHANNEL_TO_CORE1 != 0U) */

/* #Violation: Msc_c_REF_12 */
#define MSC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

/* Global variables of all channels in core2 */
/* #Violation: Msc_c_REF_12 */
#define MSC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

#if defined(MSC_MAX_CHANNEL_TO_CORE2) && (MSC_MAX_CHANNEL_TO_CORE2 != 0U)
#if (MSC_DEV_ERROR_DETECT == STD_ON)
static VAR(Msc_ChannelStatusType, MSC_VAR_FAST_CLEARED)
        Msc_ChannelStatusCore2[MSC_MAX_CHANNEL_TO_CORE2];
#endif /* MSC_DEV_ERROR_DETECT\== STD_ON */
static VAR(Msc_InitStateType, MSC_VAR_FAST_CLEARED) Msc_DriverStatusCore2;

#endif /* defined(MSC_MAX_CHANNEL_TO_CORE2) \&& (MSC_MAX_CHANNEL_TO_CORE2 != 0U) */

/* #Violation: Msc_c_REF_12 */
#define MSC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

/* Global variables of all channels in core3 */
/* #Violation: Msc_c_REF_12 */
#define MSC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

#if defined(MSC_MAX_CHANNEL_TO_CORE3) && (MSC_MAX_CHANNEL_TO_CORE3 != 0U)
#if (MSC_DEV_ERROR_DETECT == STD_ON)
static VAR(Msc_ChannelStatusType, MSC_VAR_FAST_CLEARED)
        Msc_ChannelStatusCore3[MSC_MAX_CHANNEL_TO_CORE3];
#endif /* MSC_DEV_ERROR_DETECT \== STD_ON */
static VAR(Msc_InitStateType, MSC_VAR_FAST_CLEARED) Msc_DriverStatusCore3;

#endif /* defined(MSC_MAX_CHANNEL_TO_CORE3) \&& (MSC_MAX_CHANNEL_TO_CORE3 != 0U) */

/* #Violation: Msc_c_REF_12 */
#define MSC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"


/* #Violation: Msc_c_REF_12 */
#define MSC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

/* Global pointer that point to configuration data structure */
static P2CONST(Msc_ConfigType,AUTOMATIC, MSC_CONFIG_DATA) Msc_ConfigPtr;

/* #Violation: Msc_c_REF_12 */
#define MSC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"


/* An array containing pointers to global variables of all channels of the core */
/* #Violation: Msc_c_REF_12 */
#define MSC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

#if (MSC_DEV_ERROR_DETECT == STD_ON)
/* #Violation: Msc_c_REF_11 */
static CONSTP2VAR(Msc_ChannelStatusType, MSC_CONFIG_DATA, MSC_APPL_DATA)
        Msc_CoreChannelStatusPtr[MCAL_NUMBER_OF_CORES] =
{
        /* A pointer the channel global variable of core0 */
#if (MSC_MAX_CHANNEL_TO_CORE0 != 0U)
        &Msc_ChannelStatusCore0[0],
#else
        NULL_PTR,
#endif /* MSC_MAX_CHANNEL_TO_CORE0 != 0U */
#if (MCAL_NUMBER_OF_CORES >= 2U)
        /* A pointer the channel global variable of core1 */
#if (MSC_MAX_CHANNEL_TO_CORE1 != 0U)
       &Msc_ChannelStatusCore1[0],
#else
        NULL_PTR,
#endif /* MSC_MAX_CHANNEL_TO_CORE1 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 2U */
#if (MCAL_NUMBER_OF_CORES >= 3U)
        /* A pointer the channel global variable of core2 */
#if (MSC_MAX_CHANNEL_TO_CORE2 != 0U)
       &Msc_ChannelStatusCore2[0],
#else
        NULL_PTR,
#endif /* MSC_MAX_CHANNEL_TO_CORE2 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 3U */
#if (MCAL_NUMBER_OF_CORES >= 4U)
        /* A pointer the channel global variable of core3 */
#if (MSC_MAX_CHANNEL_TO_CORE3 != 0U)
       &Msc_ChannelStatusCore3[0]
#else
        NULL_PTR
#endif /* MSC_MAX_CHANNEL_TO_CORE3 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 4U */
};
#endif /* MSC_DEV_ERROR_DETECT \== STD_ON */

/* #Violation: Msc_c_REF_11 */
static CONSTP2VAR(Msc_InitStateType, MSC_CONFIG_DATA, MSC_APPL_DATA)
        Msc_CoreDriverStatusPtr[MCAL_NUMBER_OF_CORES] =
{
#if (MSC_MAX_CHANNEL_TO_CORE0 != 0U)
        &Msc_DriverStatusCore0,
#else
        NULL_PTR,
#endif /* MSC_MAX_CHANNEL_TO_CORE0 != 0U */
#if (MCAL_NUMBER_OF_CORES >= 2U)
#if (MSC_MAX_CHANNEL_TO_CORE1 != 0U)
       &Msc_DriverStatusCore1,
#else
        NULL_PTR,
#endif /* MSC_MAX_CHANNEL_TO_CORE1 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 2U */
#if (MCAL_NUMBER_OF_CORES >= 3U)
#if (MSC_MAX_CHANNEL_TO_CORE2 != 0U)
       &Msc_DriverStatusCore2,
#else
        NULL_PTR,
#endif /* MSC_MAX_CHANNEL_TO_CORE2 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 3U */
#if (MCAL_NUMBER_OF_CORES >= 4U)
#if (MSC_MAX_CHANNEL_TO_CORE3 != 0U)
       &Msc_DriverStatusCore3
#else
        NULL_PTR
#endif /* MSC_MAX_CHANNEL_TO_CORE3 != 0U */
#endif /* MCAL_NUMBER_OF_CORES >= 4U */
};


/* #Violation: Msc_c_REF_12 */
#define MSC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"

/****************************************************************************************************
**                          SchM Critical Section Protection Macros                                **
****************************************************************************************************/
/* Enter critical section macros */
/* #Violation: Msc_c_REF_9 */
/* #Violation: Msc_c_REF_3 */
#define MSC_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_##Exclusive_Area()

/* Exit critical section macros */
/* #Violation: Msc_c_REF_9 */
/* #Violation: Msc_c_REF_3 */
#define MSC_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_##Exclusive_Area()

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Get channel global status pointer macros */
/* #Violation: Msc_c_REF_9 */
#define MSC_GET_CHANNEL_RAM_PTR(CoreId, CoreChIndex) \
        &((Msc_CoreChannelStatusPtr[CoreId])[CoreChIndex])

/* Get channel index in core */
/* #Violation: Msc_c_REF_9 */
#define MSC_GET_CHANNEL_INDEX_IN_CORE(ModNum) \
        Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Index

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
static MSC_MODULE* Msc_GetHwChannelObject
(
    Mcal_CoreType CoreId,
    uint32 LogicChannelId
);

static Std_ReturnType Msc_HandleInterrupt
(
    MSC_MODULE* const HwObjectPtr, 
    uint8 ServiceNum, 
    Msc_IntrStsFlag IntEvent
);

static void Msc_PerformRxStateChange(
    Msc_ModuleType ModNum, 
    Msc_RxStateType UpstreamStatus
);

/* #Violation: Msc_c_REF_12 */
#define MSC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Msc_c_REF_2 */
#include "Msc_MemMap.h"
/****************************************************************************************************
**                          Private Function                                                       **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Msc_GetHwChannelObject
 *
 *   Service ID              : None.
 *
 *   Description             : Get hardware channel object by logic channel id.
 *
 *   Parameters in           : CoreId: Current core id.
 *                             LogicChannelId: Logic channel id.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : Pointer to hardware channel base address.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static MSC_MODULE* Msc_GetHwChannelObject(Mcal_CoreType CoreId, uint32 LogicChannelId)
{
    uint32 HwMapIndex;
    MSC_MODULE *HwObjectPtr;

    /* #Violation: Msc_c_REF_13 */
    HwObjectPtr = MSC0_HAL;

    if((NULL_PTR != Msc_ConfigPtr) && (LogicChannelId < MSC_TOTAL_CHANNEL_NUMBER))
    {
        HwMapIndex = Msc_ConfigPtr->MscCoreMappingPtr[LogicChannelId].Index;
        HwObjectPtr = Msc_ConfigPtr->CoreConfigPtr[CoreId]-> 
        Msc_ChannelConfigPtr[HwMapIndex].MscModulePtr;
    }

    return HwObjectPtr;
}

/****************************************************************************************************
 *   Function Name           : Msc_HandleInterrupt
 *
 *   Service ID              : None.
 *
 *   Description             : Handle the msc interrupt.
 *
 *   Parameters in           : HwObjectPtr: Hardware base address.
 *                             ServiceNum: Service number of interrupt.
 *                             IntEvent: Interrupt event type.
 *                             NotifyPtr: Notification function pointer.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : Pointer to hardware channel base address.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static Std_ReturnType Msc_HandleInterrupt
(
    MSC_MODULE* const HwObjectPtr, 
    uint8 ServiceNum, 
    Msc_IntrStsFlag IntEvent
)
{
    Msc_Status IntStatus;
    Msc_IntrEn IntEnStatus;
    uint8 Service;
    Std_ReturnType RetVal;

    RetVal = FALSE;

    Service = Msc_Hal_GetServiceNodeNumber(HwObjectPtr, IntEvent);
    /* Check if the receive data interrupt is happened */
    if(ServiceNum == Service)
    {
        IntStatus = Msc_Hal_GetIntrStatusFlag(HwObjectPtr, IntEvent);
        IntEnStatus = Msc_Hal_GetInterruptEnabledStatus(HwObjectPtr, IntEvent);

        /* If hardware flag is set and notification is enabled */
        if((MSC_STATUS_SET == IntStatus) && (MSC_INTREN_ENABLED == IntEnStatus))
        {
            /* Clear Interrupt Flag */
            Msc_Hal_ClearIntrStatusFlag(HwObjectPtr, IntEvent);
            RetVal = TRUE;
        } 
    }
    return RetVal;
}

/****************************************************************************************************
**                          Global Function                                                        **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Msc_Init
 *
 *   Service ID              : 0x00
 *
 *   Description             : Initialize all internals variables  and the used MSC structure
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
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_Init
(
    CONSTP2CONST(Msc_ConfigType, AUTOMATIC, MSC_APPL_CONST) ConfigPtr
)
{
    uint8 ChannelIndex;
    const Msc_ChConfigType *ChannelConfigPtr;
    Mcal_CoreType CoreId;
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    Msc_ChannelStatusType *ChannelStatusPtr;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    boolean Status;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == ConfigPtr)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, 
                              MSC_INSTANCE_ID, 
                              MSC_INIT_SID, 
                              MSC_E_PARAM_POINTER);
    }
    else if ((NULL_PTR == ConfigPtr->CoreConfigPtr[CoreId]) ||
             (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId]))
    /* #Violation: Msc_c_REF_9 */
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID,
                              MSC_INSTANCE_ID,
                              MSC_INIT_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    /* Check if the MSC Driver is already initialized */
    else if (MSC_UNINITIALIZED != (*Msc_CoreDriverStatusPtr[CoreId]))
    /* #Violation: Msc_c_REF_9 */
    {
        /* Report Error to DET */
        (void)Det_ReportError(MSC_MODULE_ID, 
                              MSC_INSTANCE_ID, 
                              MSC_INIT_SID,
                              MSC_E_ALREADY_INITIALIZED);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        /*Store the configuration pointer to global variable*/
        Msc_ConfigPtr = ConfigPtr;

        /* Initialize all channels in current core */
        for(ChannelIndex = 0U; ChannelIndex < 
            ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel; ChannelIndex++)
        {
            /* #Violation: Msc_c_REF_4 */
            ChannelConfigPtr = &Msc_ConfigPtr->CoreConfigPtr[CoreId]->
                Msc_ChannelConfigPtr[ChannelIndex];
            
            /* Initialize basic module */
            Status = Msc_Hal_InitModule((MSC_MODULE *)ChannelConfigPtr->MscModulePtr, 
                ChannelConfigPtr->ModuleConfigPtr);
            
            if(FALSE == Status)
            {
                /* Report Error to DET */
                (void)Det_ReportRuntimeError(MSC_MODULE_ID, 
                                             MSC_INSTANCE_ID, 
                                             MSC_INIT_SID,
                                             MSC_E_INIT_FAILED);
                break;
            }
        
            if(NULL_PTR != ChannelConfigPtr->InterruptConfigPtr)
            {
                /* Initialize interrupt */
                Msc_Hal_InitInterrupt((MSC_MODULE *)ChannelConfigPtr->MscModulePtr, 
                                      &ChannelConfigPtr->InterruptConfigPtr->IntConfig);
            }

#if (MSC_DEV_ERROR_DETECT == STD_ON)
            /* To get the channel status pointer */
            ChannelStatusPtr = MSC_GET_CHANNEL_RAM_PTR(CoreId, ChannelIndex);
        
            ChannelStatusPtr->NotifyStatus = FALSE;
            ChannelStatusPtr->UpstreamChannelStatus = MSC_RX_ON;
            ChannelStatusPtr->DownstreamChannelStatus = MSC_DOWNSTREAMEN_ENABLED;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
        }

        /* Set Msc Driver status to initialized */
        (*Msc_CoreDriverStatusPtr[CoreId]) = MSC_INITIALIZED;
    }
}

#if (MSC_DEINIT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_DeInit
 *
 *   Service ID              : 0x01
 *
 *   Description             : Deinitialize the MSC peripheral
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
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_DeInit
(
    void
)
{
    uint8 ChannelIndex;
    Mcal_CoreType    CoreId;
    MSC_MODULE const *HwObjectPtr;
    Rcc_ErrorFlag RetValue;
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    Msc_ChannelStatusType *ChannelStatusPtr;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    Std_ReturnType RetStatus;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == Msc_ConfigPtr)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, 
                              MSC_INSTANCE_ID, 
                              MSC_DEINIT_SID, 
                              MSC_E_UNINIT);
    }
    else if(NULL_PTR == Msc_ConfigPtr->CoreConfigPtr[CoreId])
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID,
                              MSC_INSTANCE_ID,
                              MSC_DEINIT_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        for(ChannelIndex = 0U; ChannelIndex < 
            Msc_ConfigPtr->CoreConfigPtr[CoreId]->MaxChannel; ChannelIndex++)
        /* #Violation: Msc_c_REF_9 */
        {
            HwObjectPtr = Msc_GetHwChannelObject(CoreId, ChannelIndex);

            MSC_ENTER_CRITICAL_SECTION(Msc_DeInit);

            RetStatus = Mcal_GetLock(MCAL_LOCK_ID_RCC);
            if(E_OK == RetStatus)
            {
                /* DeInitialize Msc module */
                /* #Violation: Msc_c_REF_7 */
                /* #Violation: Msc_c_REF_4 */
                RetValue = Msc_Hal_DeInitModule(HwObjectPtr);
                Mcal_ReleaseLock(MCAL_LOCK_ID_RCC);
                if(RCC_ERRORFLAG_SUCCESS != RetValue)
                {
                    RetStatus = E_NOT_OK;
                }
            }
            MSC_EXIT_CRITICAL_SECTION(Msc_DeInit);

            if(E_OK != RetStatus)
            {
                /* Report to DET */
                (void)Det_ReportRuntimeError(MSC_MODULE_ID, 
                                             MSC_INSTANCE_ID, 
                                             MSC_DEINIT_SID, 
                                             MSC_E_INIT_FAILED);
                break;
            }
#if (MSC_DEV_ERROR_DETECT == STD_ON)
            /* To get the channel status pointer */
            ChannelStatusPtr = MSC_GET_CHANNEL_RAM_PTR(CoreId, ChannelIndex);
            ChannelStatusPtr->NotifyStatus = FALSE;
            ChannelStatusPtr->UpstreamChannelStatus = MSC_RX_OFF;
            ChannelStatusPtr->DownstreamChannelStatus = MSC_DOWNSTREAMEN_DISABLED;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
        }
        /* Set Msc Driver status to initialized */
        (*Msc_CoreDriverStatusPtr[CoreId]) = MSC_UNINITIALIZED;
    }
}
#endif /* MSC_DEINIT_API \== STD_ON */

#if (MSC_CHANGE_TX_STATUS_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_ChangeTxState
 *
 *   Service ID              : 0x02
 *
 *   Description             : Activates/Deactivates the transmitter of the MSC module
 *
 *   Parameters in           : ModNum: Msc logic module number.
 *                             Mode: Transmitter enable or disable mode.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : void.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_ChangeTxState
(
    Msc_ModuleType ModNum,
    Msc_TxStateType DownstreamStatus
)
{
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    Msc_ChannelStatusType *ChannelStatusPtr;
    uint8 ChInCoreIndex;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    MSC_MODULE *HwObjectPtr;
    Mcal_CoreType    CoreId;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)

    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGETXSTATUS_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGETXSTATUS_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGETXSTATUS_SID,
                              MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGETXSTATUS_SID,
                              MSC_E_CORE_NOT_MATCH);
    }
    else if (MSC_DOWNSTREAMEN_ENABLED < DownstreamStatus)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGETXSTATUS_SID, MSC_E_INVALID_MODE);
    }
    else if ((NULL_PTR != Msc_CoreChannelStatusPtr[CoreId]) &&
             (DownstreamStatus == (*Msc_CoreChannelStatusPtr[CoreId]).DownstreamChannelStatus))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGETXSTATUS_SID, MSC_E_INVALID_MODE);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        /*Call Low Level Function to Change the Transmitter State */
        Msc_Hal_ControlDownstream(HwObjectPtr, DownstreamStatus);
#if (MSC_DEV_ERROR_DETECT == STD_ON)
        ChInCoreIndex = MSC_GET_CHANNEL_INDEX_IN_CORE(ModNum);
        /* To get the channel status pointer */
        ChannelStatusPtr = MSC_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        ChannelStatusPtr->DownstreamChannelStatus = DownstreamStatus;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    }
}
#endif /* MSC_CHANGE_TX_STATUS_API \== STD_ON */

#if (MSC_GET_TX_STATUS_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_GetTxStatus
 *
 *   Service ID              : 0x03
 * 
 *   Description             : ModNum: Msc logic module number.
 *                             Acquire the readiness of the Transmitter ReturnValue.
 *
 *   Parameters in           : FrameType: Frame Type.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Msc_TxStatusType.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(Msc_TxStatusType, MSC_PUBLIC_CODE)Msc_GetTxStatus
(
    Msc_ModuleType ModNum,
    Msc_FrameClassType TxFrameType
)
{
    Msc_TransmitStsFlag StatusFlag;
    Msc_TxStatusType ReturnStatus;
    Msc_Status LReturnStatus;
    Mcal_CoreType    CoreId;
    MSC_MODULE const *HwObjectPtr;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

    ReturnStatus = MSC_TX_NOT_OK;

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETTXSTATUS_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    /* #Violation: Msc_c_REF_9 */
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETTXSTATUS_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETTXSTATUS_SID, MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETTXSTATUS_SID, MSC_E_CORE_NOT_MATCH);
    }
    else if ((MSC_CMD_FRAME != TxFrameType) && (MSC_DATA_FRAME != TxFrameType))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETTXSTATUS_SID, MSC_E_INVALID_TXTYPE);
    }
    else
#endif /* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        if(MSC_CMD_FRAME == TxFrameType)
        {
            StatusFlag = MSC_TRANSMITSTSFLAG_COMP;
        }
        else
        {
            StatusFlag = MSC_TRANSMITSTSFLAG_DATP;
        }

        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        /* Call low level function to get the transmitter state */
        /* #Violation: Msc_c_REF_4 */
        LReturnStatus = 
            Msc_Hal_GetTransmitStatusFlag(HwObjectPtr, StatusFlag);

        /* Get command frame transmitter status */
        if(MSC_CMD_FRAME == TxFrameType)
        {
            if(MSC_STATUS_SET == LReturnStatus)
            {
                /* Command frame is pending */
                ReturnStatus = MSC_CMDFRMTX_NOTREADY;
            }
            else
            {
                /* Command transmitter is ready */
                ReturnStatus = MSC_CMDFRMTX_READY;
            }
        }
        /* Get data frame transmitter status */
        else
        {
            if(MSC_STATUS_SET == LReturnStatus)
            {
                /* Data frame is pending */
                ReturnStatus = MSC_DATAFRMTX_NOTREADY;
            }
            else
            {
                /* Data transmitter is ready */
                ReturnStatus = MSC_DATAFRMTX_READY;
            }
        }
    }

    return ReturnStatus;
}
#endif /* MSC_GET_TX_STATUS_API \== STD_ON */

/****************************************************************************************************
 *   Function Name           : Msc_TxCmdFrame
 *
 *   Service ID              : 0x04
 *
 *   Description             : Transmit Command Frame
 *
 *   Parameters in           : ModNum: Msc logic module number. 
 *                             Device: The device to transmit command.
                              Msc_Cmd:The command to transmit.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : void.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_TxCmdFrame
(
    Msc_ModuleType ModNum,
    Msc_TxDevSelectType Device,
    uint32 Cmd
)
{
    Mcal_CoreType    CoreId;
    MSC_MODULE *HwObjectPtr;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXCMDFRAME_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXCMDFRAME_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXCMDFRAME_SID, MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXCMDFRAME_SID, MSC_E_CORE_NOT_MATCH);
    }
    else if (MSC_TARGET_EN3 < Device)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXCMDFRAME_SID, MSC_E_INVALID_DEVICE);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        MSC_ENTER_CRITICAL_SECTION(Msc_TxCmdFrame);
        /* Select the command transmit device */
        /* #Violation: Msc_c_REF_7 */
        /* #Violation: Msc_c_REF_4 */
        Msc_Hal_SetCommandTarget(HwObjectPtr, Device);
        /* Send command */
        /* #Violation: Msc_c_REF_7 */
        /* #Violation: Msc_c_REF_4 */
        Msc_Hal_SendCommand(HwObjectPtr, Cmd);
        MSC_EXIT_CRITICAL_SECTION(Msc_TxCmdFrame);
    }
}

/****************************************************************************************************
 *   Function Name           : Msc_SyncTxCmdFrame
 *
 *   Service ID              : 0x10
 *
 *   Description             : Transmit Command Frame
 *
 *   Parameters in           : ModNum: Msc logic module number. 
 *                             Device: The device to transmit command.
 *                             Msc_Cmd:The command to transmit.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : void.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
#if defined(THA6_THA6206D)
FUNC(Std_ReturnType, MSC_PUBLIC_CODE)Msc_SyncTxCmdFrame
(
    Msc_ModuleType ModNum,
    Msc_TxDevSelectType Device,
    uint32 Cmd
)
{
    boolean          RetVal;
    Std_ReturnType   RetCode;
    Mcal_CoreType    CoreId;
    MSC_MODULE *HwObjectPtr;

    /* #Violation: Msc_c_REF_4 */
    RetCode = E_NOT_OK;
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SYNCTXCMDFRAME_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SYNCTXCMDFRAME_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SYNCTXCMDFRAME_SID, MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SYNCTXCMDFRAME_SID, MSC_E_CORE_NOT_MATCH);
    }
    else if (MSC_TARGET_EN3 < Device)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SYNCTXCMDFRAME_SID, MSC_E_INVALID_DEVICE);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        MSC_ENTER_CRITICAL_SECTION(Msc_TxCmdFrame);
        /* Select the command transmit device */
        /* #Violation: Msc_c_REF_7 */
        /* #Violation: Msc_c_REF_4 */
        Msc_Hal_SetCommandTarget(HwObjectPtr, Device);
        /* Send command */
        /* #Violation: Msc_c_REF_7 */
        /* #Violation: Msc_c_REF_4 */
        RetVal = Msc_Hal_SyncSendCommand(HwObjectPtr, Cmd);
        MSC_EXIT_CRITICAL_SECTION(Msc_TxCmdFrame);
        if (TRUE == RetVal)
        {
            RetCode = E_OK;
        }
    }

    return RetCode;
}
#endif

#if (MSC_TX_DATA_FRAME_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_TxDataFrame
 *
 *   Service ID              : 0x05
 *
 *   Description             : Transmit Data Frame
 *
 *   Parameters in           : ModNum: Msc logic module number.
 *                             DeviceHigh: The device to transmit SRH.
                              DeviceLow: The device to transmit SRL.
                              Msc_Data:The data to transmit.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : void.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_TxDataFrame
(
    Msc_ModuleType ModNum,
    Msc_TxDevSelectType DeviceHigh,
    Msc_TxDevSelectType DeviceLow,
    uint32 DataValue
)
{
    Mcal_CoreType    CoreId;
    MSC_MODULE *HwObjectPtr;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXDATAFRAME_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXDATAFRAME_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXDATAFRAME_SID, MSC_E_INVALID_CHANNEL);
    }
    else if ((Msc_ConfigPtr->MscCoreMappingPtr != NULL_PTR) &&
             ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXDATAFRAME_SID, MSC_E_CORE_NOT_MATCH);
    }
    else if (MSC_TARGET_EN3 < DeviceHigh)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXDATAFRAME_SID, MSC_E_INVALID_DEVICE);
    }
    else if (MSC_TARGET_EN3 < DeviceLow)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_TXDATAFRAME_SID, MSC_E_INVALID_DEVICE);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        MSC_ENTER_CRITICAL_SECTION(Msc_TxDataFrame);
        /* Select the device of data frame */
        /* #Violation: Msc_c_REF_7 */
        /* #Violation: Msc_c_REF_4 */
        Msc_Hal_SetDataTarget(HwObjectPtr, 
                              DeviceHigh, 
                              DeviceLow);
        /* Send data */
        /* #Violation: Msc_c_REF_7 */
        /* #Violation: Msc_c_REF_4 */
        Msc_Hal_SendData(HwObjectPtr, DataValue);
        MSC_EXIT_CRITICAL_SECTION(Msc_TxDataFrame);
    }
}
#endif /* MSC_TX_DATA_FRAME_API \== STD_ON */

/****************************************************************************************************
 *   Function Name           : Msc_SelectTxDevice
 *
 *   Service ID              : 0x0F
 *
 *   Description             : Select the transmit device of data frame
 *
 *   Parameters in           : ModNum: Msc logic module number.
 *                             DeviceHigh: The device to transmit SRH.
 *                             DeviceLow: The device to transmit SRL.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : void.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_SelectTxDevice
(
    Msc_ModuleType ModNum,
    Msc_TxDevSelectType DeviceHigh,
    Msc_TxDevSelectType DeviceLow
)
{
    Mcal_CoreType    CoreId;
    MSC_MODULE *HwObjectPtr;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELTXDEVICE_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELTXDEVICE_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELTXDEVICE_SID, MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELTXDEVICE_SID, MSC_E_CORE_NOT_MATCH);
    }
    else if (MSC_TARGET_EN3 < DeviceHigh)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELTXDEVICE_SID, MSC_E_INVALID_DEVICE);
    }
    else if (MSC_TARGET_EN3 < DeviceLow)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELTXDEVICE_SID, MSC_E_INVALID_DEVICE);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        /* Select the device of data frame */
        /* #Violation: Msc_c_REF_4 */
        /* #Violation: Msc_c_REF_7 */
        Msc_Hal_SetDataTarget(HwObjectPtr,
                              DeviceHigh, 
                              DeviceLow);
    }
}

#if (MSC_CHANGE_RX_STATUS_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Msc_ChangeRxState
*
*   Service ID              : 0x0B
*
*   Description             : Activates/Deactivates the receiver of the MSC module
*
*   Parameters in           : ModNum: Msc logic module number.
*                             UpstreamStatus: Mode: Receiver mode.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant (but not for the same ModNum).
*
*   Return value            : void.
*
*   Preconditions           : Msc module must be initialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */

/* -------------------------------------------------------------------------- */
/*  Static helper: Perform actual RX state change after all DET checks       */
/* -------------------------------------------------------------------------- */
static void Msc_PerformRxStateChange(Msc_ModuleType ModNum, Msc_RxStateType UpstreamStatus)
{
    Msc_UpDiv      UpstreamDiv = MSC_UPDIV_DISABLED;
    Mcal_CoreType  CoreId = Mcal_GetCoreId();
    uint32         ChInCoreIndex = MSC_GET_CHANNEL_INDEX_IN_CORE(ModNum);
    MSC_MODULE    *HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);

    if (MSC_RX_OFF == UpstreamStatus)
    {
        UpstreamDiv = MSC_UPDIV_DISABLED;
    }
    else
    {
        if (NULL_PTR != Msc_ConfigPtr->CoreConfigPtr[CoreId]->Msc_ChannelConfigPtr)
        {
            if (NULL_PTR != Msc_ConfigPtr->CoreConfigPtr[CoreId]->Msc_ChannelConfigPtr[ChInCoreIndex].ModuleConfigPtr)
            {
                UpstreamDiv = Msc_ConfigPtr->CoreConfigPtr[CoreId]->Msc_ChannelConfigPtr[ChInCoreIndex].ModuleConfigPtr->upstreamConfig.upDiv;
            }
        }
    }

    /* Call Low Level Function to Change the receiver State */
    /* #Violation: Msc_c_REF_4 */
    /* #Violation: Msc_c_REF_7 */
    Msc_Hal_ControlUpstream(HwObjectPtr, UpstreamDiv);

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    {
        Msc_ChannelStatusType *ChannelStatusPtr = MSC_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        if (NULL_PTR != ChannelStatusPtr)
        {
            ChannelStatusPtr->UpstreamChannelStatus = UpstreamStatus;
        }
    }
#endif /* MSC_DEV_ERROR_DETECT == STD_ON */
}

/* -------------------------------------------------------------------------- */
/*  Main function                                                            */
/* -------------------------------------------------------------------------- */
FUNC(void, MSC_PUBLIC_CODE) Msc_ChangeRxState
(
    Msc_ModuleType ModNum,
    Msc_RxStateType UpstreamStatus
)
{
    Mcal_CoreType CoreId;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGERXSTATUS_SID, MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGERXSTATUS_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGERXSTATUS_SID, MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGERXSTATUS_SID, MSC_E_CORE_NOT_MATCH);
    }
    else if ((MSC_RX_ON != UpstreamStatus) && (MSC_RX_OFF != UpstreamStatus))
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGERXSTATUS_SID, MSC_E_INVALID_MODE);
    }
    /* #Violation: Msc_c_REF_9 */
    else if (UpstreamStatus == (*Msc_CoreChannelStatusPtr[CoreId]).UpstreamChannelStatus)
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_CHANGERXSTATUS_SID, MSC_E_INVALID_MODE);
    }
    else
#endif /* MSC_DEV_ERROR_DETECT == STD_ON */
    {
        Msc_PerformRxStateChange(ModNum, UpstreamStatus);
    }
}
#endif /* MSC_CHANGE_RX_STATUS_API == STD_ON */

#if (MSC_GET_RX_DATA_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_GetRxData
 *
 *   Service ID              : 0x06
 *
 *   Description             : Acquire the upstream data
 *
 *   Parameters in           : ModNum: Msc logic module number.
 *                             Msc_RxRegister: Receiver register.
                              DataRead: Received data.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : DataRead: Data pointer.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 * 
 *   Return value            : MSC_RXSTATUS_PE: Received data parity error.
 *                             MSC_RXSTATUS_RECEIVED: Received right data.
 *                             MSC_RXSTATUS_NORESPONSE: No data received.
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(Msc_RxStatus, MSC_PUBLIC_CODE)Msc_GetRxData
(
    Msc_ModuleType ModNum,
    Msc_UpstreamRegType Msc_RxRegister,
    uint8 *const DataPtr
)
{
    Msc_RxStatus Status;
    Mcal_CoreType    CoreId;
    MSC_MODULE *HwObjectPtr;

    Status = MSC_RXSTATUS_NORESPONSE;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXDATA_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXDATA_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXDATA_SID, MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXDATA_SID, MSC_E_CORE_NOT_MATCH);
    }
    else if (MSC_UD3 < Msc_RxRegister)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXDATA_SID,
                              MSC_E_INVALID_RXREGISTER);
    }
    else if (NULL_PTR == DataPtr)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXDATA_SID, MSC_E_PARAM_POINTER);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        MSC_ENTER_CRITICAL_SECTION(Msc_GetRxData);
        /*Call Low Level Function to get the receiver State*/
        /* #Violation: Msc_c_REF_4 */
        Status = Msc_Hal_ReceiveData(HwObjectPtr, 
                                    Msc_RxRegister, DataPtr);
        MSC_EXIT_CRITICAL_SECTION(Msc_GetRxData);
    }
    return Status;
}
#endif /* MSC_GET_RX_DATA_API \== STD_ON */

#if (MSC_SELECT_RX_DEVICE_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_SelectRxDevice
 *
 *   Service ID              : 0x07
 *
 *   Description             : Select the receiver device.
 *
 *   Parameters in           : ModNum: logic module number.
 *                             Msc_Device: Receiver device.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : None.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_SelectRxDevice
(
    Msc_ModuleType ModNum,
    Msc_RxDevSelectType Msc_Device
)
{
    Mcal_CoreType    CoreId;
    MSC_MODULE *HwObjectPtr;
    
    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELRXDEVICE_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELRXDEVICE_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELRXDEVICE_SID, MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELRXDEVICE_SID, MSC_E_CORE_NOT_MATCH);
    }
    else if (MSC_SDI_3 < Msc_Device)
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_SELRXDEVICE_SID,
                              MSC_E_INVALID_RXDEVICE);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        /* Call Low Level Function to select the receiver device */
        /* #Violation: Msc_c_REF_4 */
        Msc_Hal_SelectReceivingDevice(HwObjectPtr, Msc_Device);
    }
}
#endif /* MSC_SELECT_RX_DEVICE_API \== STD_ON */

#if (MSC_START_RX_TIMEOUT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_StartRxTimeout
 *
 *   Service ID              : 0x08
 *
 *   Description             : Start upstream timeout mechanism.
 *
 *   Parameters in           : ModNum: logic module number.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : Std_ReturnType.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
FUNC(void, MSC_PUBLIC_CODE)Msc_StartRxTimeout
(
    Msc_ModuleType ModNum
)
{
    Mcal_CoreType    CoreId;
    uint8 ChInCoreIndex;
    const Msc_TimeoutConfigType* TimeoutConfigPtr;
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrValue;
#endif /* MSC_DEV_ERROR_DETECT \== STD_ON */
    Msc_IntrEn TimeoutEnStatus;
    MSC_MODULE *HwObjectPtr;

    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    ErrValue = E_OK;

    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_STARTRXTIMEOUT_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
        ErrValue = E_NOT_OK;
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_STARTRXTIMEOUT_SID, MSC_E_UNINIT);
        ErrValue = E_NOT_OK;
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_STARTRXTIMEOUT_SID,
                              MSC_E_INVALID_CHANNEL);
        ErrValue = E_NOT_OK;
    }
    else if (CoreId != (Mcal_CoreType)Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_STARTRXTIMEOUT_SID,
                              MSC_E_CORE_NOT_MATCH);
        ErrValue = E_NOT_OK;
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        ChInCoreIndex = MSC_GET_CHANNEL_INDEX_IN_CORE(ModNum);

        TimeoutConfigPtr = Msc_ConfigPtr->CoreConfigPtr[CoreId]->
                Msc_ChannelConfigPtr[ChInCoreIndex].TimeoutConfigPtr;
                
        if(NULL_PTR == TimeoutConfigPtr)
        {
#if (MSC_DEV_ERROR_DETECT == STD_ON)
            /* Report to DET */
            (void)Det_ReportError(MSC_MODULE_ID,
                                MSC_INSTANCE_ID,
                                MSC_STARTRXTIMEOUT_SID,
                                MSC_E_TIMEOUT_NOT_CONFIGURATED);
            ErrValue = E_NOT_OK;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
        }
    }

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    if(E_OK == ErrValue)
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
      if(NULL_PTR != TimeoutConfigPtr->UpTimeoutFrmNotifyPtr)
      {
          TimeoutEnStatus = MSC_INTREN_ENABLED;
      }
      else
      {
          TimeoutEnStatus = MSC_INTREN_DISABLED;
      }

      HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
      Msc_Hal_StartTimeoutDetection(HwObjectPtr, 
      &TimeoutConfigPtr->TimeoutConfig,
      TimeoutEnStatus);
    }
}
#endif /* MSC_START_RX_TIMEOUT_API \== STD_ON */

#if (MSC_GET_RX_TIMEOUT_STATUS_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_GetRxTimeoutStatus
 *
 *   Service ID              : 0x09
 *
 *   Description             : Get the receiver timeout status.
 *
 *   Parameters in           : ModNum: Msc logic module number.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Msc_RxTimeoutStatusType.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
FUNC(Msc_RxTimeoutStatusType, MSC_PUBLIC_CODE)Msc_GetRxTimeoutStatus
(
    Msc_ModuleType ModNum
)
{
    Msc_RxTimeoutStatusType TimeoutReturnValue;
    Msc_Status ReturnStatus;
    Mcal_CoreType    CoreId;
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    const Msc_TimeoutConfigType* TimeoutConfigPtr;
    Std_ReturnType ErrValue;
    uint8 ChInCoreIndex;
#endif /* MSC_DEV_ERROR_DETECT \== STD_ON */
    MSC_MODULE *HwObjectPtr;

    CoreId = Mcal_GetCoreId();
    TimeoutReturnValue = MSC_TIMEOUT_NOT_OK;

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    ErrValue = E_OK;

    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXTIMEOUT_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
        ErrValue = E_NOT_OK;
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXTIMEOUT_SID, MSC_E_UNINIT);
        ErrValue = E_NOT_OK;
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXTIMEOUT_SID,
                              MSC_E_INVALID_CHANNEL);
        ErrValue = E_NOT_OK;
    }
    else if (CoreId != (Mcal_CoreType)Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXTIMEOUT_SID, MSC_E_CORE_NOT_MATCH);
        ErrValue = E_NOT_OK;
    }
    else
    {
        ChInCoreIndex = MSC_GET_CHANNEL_INDEX_IN_CORE(ModNum);

        TimeoutConfigPtr =
            Msc_ConfigPtr->CoreConfigPtr[CoreId]->Msc_ChannelConfigPtr[ChInCoreIndex].TimeoutConfigPtr;

        if (NULL_PTR == TimeoutConfigPtr)
        {
            /* Report to DET */
            (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_GETRXTIMEOUT_SID,
                                  MSC_E_TIMEOUT_NOT_CONFIGURATED);
            ErrValue = E_NOT_OK;
        }
    }

    if(E_OK == ErrValue)
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        /*Call Low Level Function to get the receiver timeout status*/
        ReturnStatus = Msc_Hal_GetIntrStatusFlag(HwObjectPtr,
                                                MSC_INTRSTSFLAG_TO);

        if(MSC_STATUS_SET == ReturnStatus)
        {
            /* Clear timeout status */
            Msc_Hal_ClearIntrStatusFlag(HwObjectPtr,
                                        MSC_INTRSTSFLAG_TO);
            TimeoutReturnValue = MSC_UPSTREAM_TIMEOUT;
        }
        else
        {
            TimeoutReturnValue = MSC_UPSTREAM_NO_TIMEOUT;
        }
    }

    return TimeoutReturnValue;
}
#endif /* MSC_GET_RX_TIMEOUT_STATUS_API == STD_ON */

/****************************************************************************************************
 *   Function Name           : Msc_EnableNotfication
 *
 *   Service ID              : 0x0C
 *
 *   Description             : Enable the interrupt.
 *
 *   Parameters in           : ModNum: logic module number.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : None.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_EnableNotfication
(
    Msc_ModuleType ModNum
)
{
    Mcal_CoreType    CoreId;
    uint32 IntEnableState;
    uint8 ChInCoreIndex;
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    Msc_ChannelStatusType *ChannelStatusPtr;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    MSC_MODULE* HwObjectPtr;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_ENABLENOTFICATION_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_ENABLENOTFICATION_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_ENABLENOTFICATION_SID,
                              MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_ENABLENOTFICATION_SID,
                              MSC_E_CORE_NOT_MATCH);
    }
    else if ((Msc_CoreChannelStatusPtr[CoreId] != NULL_PTR) &&
             (TRUE == (*Msc_CoreChannelStatusPtr[CoreId]).NotifyStatus))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_ENABLENOTFICATION_SID,
                              MSC_E_ALREADY_ENABLED);
    }
    else
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        ChInCoreIndex = MSC_GET_CHANNEL_INDEX_IN_CORE(ModNum);

        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
    
        if(NULL_PTR != Msc_ConfigPtr->CoreConfigPtr[CoreId]->
            Msc_ChannelConfigPtr)
        {
            if(NULL_PTR != Msc_ConfigPtr->CoreConfigPtr[CoreId]->
                Msc_ChannelConfigPtr[ChInCoreIndex].InterruptConfigPtr)
            {
                IntEnableState = Msc_ConfigPtr->CoreConfigPtr[CoreId]->
                    Msc_ChannelConfigPtr[ChInCoreIndex].InterruptConfigPtr->IntEnablePara;
            }
            else
            {
                IntEnableState = 0U;
            }
        }
        else
        {
            IntEnableState = 0U;
        }

        /* Enable the hardware interrupt */
        /* #Violation: Msc_c_REF_4 */
        Msc_Hal_EnableInterrupt(HwObjectPtr, IntEnableState);
        
#if (MSC_DEV_ERROR_DETECT == STD_ON)
        ChannelStatusPtr = MSC_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        if(NULL_PTR != ChannelStatusPtr)
        {
            ChannelStatusPtr->NotifyStatus = TRUE;
        }
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    }
}

/****************************************************************************************************
 *   Function Name           : Msc_DisableNotfication
 *
 *   Service ID              : 0x0D
 *
 *   Description             : Disable the interrupt.
 *
 *   Parameters in           : ModNum: logic module number.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant (but not for the same ModNum).
 *
 *   Return value            : None.
 *
 *   Preconditions           : Msc module must be initialized.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE)Msc_DisableNotfication
(
    Msc_ModuleType ModNum
)
{
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    Msc_ChannelStatusType *ChannelStatusPtr;
    uint8 ChInCoreIndex;
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    Mcal_CoreType    CoreId;
    MSC_MODULE* HwObjectPtr;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* #Violation: Msc_c_REF_9 */
    if (NULL_PTR == Msc_CoreDriverStatusPtr[CoreId])
    {
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_DISABLENOTFICATION_SID,
                              MSC_E_CORE_NOT_CONFIGURATED);
    }
    else if (MSC_UNINITIALIZED == (*Msc_CoreDriverStatusPtr[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_DISABLENOTFICATION_SID, MSC_E_UNINIT);
    }
    else if (ModNum >= MSC_TOTAL_CHANNEL_NUMBER)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_DISABLENOTFICATION_SID,
                              MSC_E_INVALID_CHANNEL);
    }
    else if ((uint8)CoreId != Msc_ConfigPtr->MscCoreMappingPtr[ModNum].Core)
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_DISABLENOTFICATION_SID,
                              MSC_E_CORE_NOT_MATCH);
    }
    else if ((Msc_CoreChannelStatusPtr[CoreId] != NULL_PTR) &&
             (FALSE == (*Msc_CoreChannelStatusPtr[CoreId]).NotifyStatus))
    {
        /* Report to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_DISABLENOTFICATION_SID,
                              MSC_E_ALREADY_DISABLED);
    }
    else
#endif /* MSC_DEV_ERROR_DETECT \== STD_ON */
    {
        HwObjectPtr = Msc_GetHwChannelObject(CoreId, ModNum);
        /* Disable all interrupt */
        /* #Violation: Msc_c_REF_4 */
        Msc_Hal_DisableInterrupt(HwObjectPtr, 
                                MSC_INTR_ENABLE_FLAG_ALL);
      
#if (MSC_DEV_ERROR_DETECT == STD_ON)
        ChInCoreIndex = MSC_GET_CHANNEL_INDEX_IN_CORE(ModNum);
        ChannelStatusPtr = MSC_GET_CHANNEL_RAM_PTR(CoreId, ChInCoreIndex);
        if(NULL_PTR != ChannelStatusPtr)
        {
            ChannelStatusPtr->NotifyStatus = FALSE;
        }
#endif/* MSC_DEV_ERROR_DETECT \== STD_ON */
    }
}

#if (MSC_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Msc_GetVersionInfo
 *
 *   Service ID              : 0x0A
 *
 *   Description             :Get the version information.
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
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, Msc_PUBLIC_CODE)Msc_GetVersionInfo
(
    /* #Violation: Msc_c_REF_11 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, Msc_APPL_DATA) VersionInfoPtr
)
{
#if (MSC_DEV_ERROR_DETECT == STD_ON)
    /* Check if parameter passed is equal to Null pointer */
    if (NULL_PTR == VersionInfoPtr)
    {
        /* Report Error to DET */
        (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID,
                              MSC_GETVERSIONINFO_SID, MSC_E_PARAM_POINTER);
    }
    else
#endif /* Msc_DEV_ERROR_DETECT \== STD_ON */
    {
        VersionInfoPtr->vendorID = MSC_VENDOR_ID;
        VersionInfoPtr->moduleID = MSC_MODULE_ID;
        VersionInfoPtr->sw_major_version = MSC_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = MSC_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = MSC_SW_PATCH_VERSION;
    }
}
#endif /* Msc_VERSION_INFO_API \== STD_ON */

/****************************************************************************************************
 *   Function Name           : Msc_ISRHandler
 *
 *   Service ID              : 0x0E.
 *
 *   Description             : The interrupt handler.
 *
 *   Parameters in           : HwModNum: hardware module index.
 *
 *                             ServiceNum: The interrupt node
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
 *   Preconditions           : Msc module must be initialized and at least one interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_c_REF_14 */
FUNC(void, MSC_PUBLIC_CODE) Msc_ISRHandler
(
    uint8 HwModNum,
    uint8 ServiceNum
)
{
    Mcal_CoreType CoreId;
    uint32 ChInCoreIndex;
    const Msc_NotficationType *NotifyPtr;
    MSC_MODULE* HwObjectPtr;
    uint8 LogicChannel;
    Std_ReturnType RetVal;

    /* #Violation: Msc_c_REF_4 */
    CoreId = Mcal_GetCoreId();

    /* #Violation: Msc_c_REF_9 */
    if((Msc_CoreDriverStatusPtr[CoreId] != NULL_PTR) &&
       (MSC_UNINITIALIZED != (*Msc_CoreDriverStatusPtr[CoreId])))
    {
        LogicChannel = Msc_ConfigPtr->MscHwChannelMapPtr[HwModNum];

        if (0xFFU != LogicChannel)
        {
            if ((uint8)CoreId == Msc_ConfigPtr->MscCoreMappingPtr[LogicChannel].Core)
            {
                ChInCoreIndex = MSC_GET_CHANNEL_INDEX_IN_CORE(LogicChannel);
                HwObjectPtr = Msc_GetHwChannelObject(CoreId, LogicChannel);
                /* Get receive, command frame, time frame,
                   data frame notification callback function entry pointer*/
                NotifyPtr = &Msc_ConfigPtr->CoreConfigPtr[CoreId]
                                 ->Msc_ChannelConfigPtr[ChInCoreIndex]
                                 .InterruptConfigPtr->Notification;

                /* Handle the receive interrupt */
                RetVal = Msc_HandleInterrupt(HwObjectPtr, ServiceNum, MSC_INTRSTSFLAG_RX);
                if (TRUE == RetVal)
                {
                    NotifyPtr->RxFrmNotifyPtr();
                }
                /* Handle the command frame interrupt */
                RetVal = Msc_HandleInterrupt(HwObjectPtr, ServiceNum, MSC_INTRSTSFLAG_CF);
                if (TRUE == RetVal)
                {
                    NotifyPtr->CmdFrmNotifyPtr();
                }
                /* Handle the time frame interrupt */
                RetVal = Msc_HandleInterrupt(HwObjectPtr, ServiceNum, MSC_INTRSTSFLAG_TF);
                if (TRUE == RetVal)
                {
                    NotifyPtr->TimeFrmNotifyPtr();
                }

                /* Handle the data frame interrupt */
                RetVal = Msc_HandleInterrupt(HwObjectPtr, ServiceNum, MSC_INTRSTSFLAG_DF);
                if (TRUE == RetVal)
                {
                    NotifyPtr->DataFrmNotifyPtr();
                }

                /* Handle the timeout interrupt */
                RetVal = Msc_HandleInterrupt(HwObjectPtr, ServiceNum, MSC_INTRSTSFLAG_TO);
                if (TRUE == RetVal)
                {
                    Msc_ConfigPtr->CoreConfigPtr[CoreId]
                        ->Msc_ChannelConfigPtr[ChInCoreIndex]
                        .TimeoutConfigPtr->UpTimeoutFrmNotifyPtr();
                }
            }
#if (MSC_DEV_ERROR_DETECT == STD_ON)
            else
            {
                /* Report to DET */
                (void)Det_ReportError(MSC_MODULE_ID, MSC_INSTANCE_ID, MSC_ISRHANDLER_SID,
                                      MSC_E_CORE_NOT_MATCH);
            }
#endif /* Msc_DEV_ERROR_DETECT \== STD_ON */
        }
    }
}

/* #Violation: Msc_c_REF_12 */
#define MSC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"
/****************************************************************************************************
 **                          End of File                                                            **
 ****************************************************************************************************/
