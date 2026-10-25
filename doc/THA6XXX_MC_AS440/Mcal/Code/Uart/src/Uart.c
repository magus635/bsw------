/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Uart.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : ASI
 *
 *   brief                 : This file contains all functions of Uart Driver
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
*#Uart_c_REF_1:MISRAC2012-Rule-20.10;
* Justification:Use glue operator to construct the exclusive area function name.
*
*#Uart_c_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Uart_c_REF_3:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*#Uart_c_REF_4:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#Uart_c_REF_5:CertC-PRE00-C;
* Justification: Use simple macros to reduce code complexity.
*
*#Uart_c_REF_6:MISRAC2012-Rule-20.7;
* Justification:Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Uart_c_REF_7:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*#Uart_c_REF_8:CertC-PRE00; 
* Justification:Function like macros are used to reduce code complexity.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Uart.h"
#include "Mcall.h"
#include "Mcall_GeneralTypes.h"
#include "asi_hal.h"
#include "SchM_Uart.h"
#include "Uart_Version.h"
#if (UART_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
/* Check if current file and INTC header file are of the same vendor */
#if (UART_VENDOR_ID != UART_CFG_VENDOR_ID)
  #error "Uart.c : Mismatch in Vendor ID"
#endif /* (UART_VENDOR_ID \!= UART_CFG_VENDOR_ID) */

#if (UART_MODULE_ID != UART_CFG_MODULE_ID)
  #error "Uart.c : Mismatch in Module ID"
#endif /* (UART_MODULE_ID \!= UART_CFG_MODULE_ID) */

#if (UART_AR_RELEASE_MAJOR_VERSION != UART_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Uart.c : Mismatch in Release Major Version"
#endif /* (UART_AR_RELEASE_MAJOR_VERSION \!= UART_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (UART_AR_RELEASE_MINOR_VERSION != UART_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Uart.c : Mismatch in Release Minor Version"
#endif /* (UART_AR_RELEASE_MINOR_VERSION \!= UART_CFG_AR_RELEASE_MINOR_VERSION) */

#if (UART_AR_RELEASE_REVISION_VERSION != UART_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Uart.c : Mismatch in Release Revision Version"
#endif /* (UART_AR_RELEASE_REVISION_VERSION \!= UART_CFG_AR_RELEASE_REVISION_VERSION) */

#if (UART_SW_MAJOR_VERSION != UART_CFG_SW_MAJOR_VERSION)
  #error "Uart.c : Mismatch in Software Major Version"
#endif /* (UART_SW_MAJOR_VERSION \!= UART_CFG_SW_MAJOR_VERSION) */

#if (UART_SW_MINOR_VERSION != UART_CFG_SW_MINOR_VERSION)
  #error "Uart.c : Mismatch in Software Minor Version"
#endif /* (UART_SW_MINOR_VERSION \!= UART_CFG_SW_MINOR_VERSION) */

#if (UART_SW_PATCH_VERSION != UART_CFG_SW_PATCH_VERSION)
  #error "Uart.c : Mismatch in Software Patch Version"
#endif /* (UART_SW_PATCH_VERSION \!= UART_CFG_SW_PATCH_VERSION) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: Uart_c_REF_8 */
/* #Violation: Uart_c_REF_1 */
#define UART_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Uart_##Exclusive_Area()
/* #Violation: Uart_c_REF_8 */
/* #Violation: Uart_c_REF_1 */
#define UART_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Uart_##Exclusive_Area()
 
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if (UART_DEV_ERROR_DETECT == STD_ON)

/* Define the channel state structure on multi-Core0 */
#if (UART_MAX_CHANNEL_TO_CORE0 > 0U)
/* #Violation: Uart_c_REF_7 */
#define UART_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Uart_MemMap.h"

/* Uart initialization status in core0 */
static Uart_DriverStateType Uart_InitStatusCore0;
/* #Violation: Uart_c_REF_7 */
#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Uart_c_REF_2 */
#include "Uart_MemMap.h"
/* #Violation: Uart_c_REF_7 */
#define UART_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"

/* Holding core0 specific UART channel status */
static const Uart_CoreStatusType Uart_StatusSetCore0 =
{
    &Uart_InitStatusCore0
};
/* #Violation: Uart_c_REF_7 */
#define UART_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Uart_c_REF_2 */
#include "Uart_MemMap.h"
#endif /* (UART_MAX_CHANNEL_TO_CORE0 \> 0U) */

/* Define the channel state structure on multi-Core1 */
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (UART_MAX_CHANNEL_TO_CORE1 > 0U)

#define UART_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Uart_MemMap.h"

/* Uart initialization status in core1 */
static Uart_DriverStateType Uart_InitStatusCore1;

#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
#include "Uart_MemMap.h"

/* Holding core1 specific UART channel status */
static const Uart_CoreStatusType Uart_StatusSetCore1 =
{
    &Uart_InitStatusCore1
};

#define UART_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
#include "Uart_MemMap.h"

#endif /* (UART_MAX_CHANNEL_TO_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

/* Define the channel state structure on multi-Core2 */
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (UART_MAX_CHANNEL_TO_CORE2 > 0U)

#define UART_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#include "Uart_MemMap.h"

/* Uart initialization status in core1 */
static Uart_DriverStateType Uart_InitStatusCore2;

#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
#include "Uart_MemMap.h"

/* Holding core1 specific UART channel status */
static const Uart_CoreStatusType Uart_StatusSetCore2 =
{
    &Uart_InitStatusCore2
};

#define UART_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
#include "Uart_MemMap.h"

#endif /* (UART_MAX_CHANNEL_TO_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

/* Define the channel state structure on multi-Core3 */
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (UART_MAX_CHANNEL_TO_CORE3 > 0U)

#define UART_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#include "Uart_MemMap.h"

/* Uart initialization status in core1 */
static Uart_DriverStateType Uart_InitStatusCore3;

#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
#include "Uart_MemMap.h"

/* Holding core1 specific UART channel status */
static const Uart_CoreStatusType Uart_StatusSetCore3 =
{
    &Uart_InitStatusCore3
};

#define UART_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
#include "Uart_MemMap.h"

#endif /* (UART_MAX_CHANNEL_TO_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */
/* #Violation: Uart_c_REF_7 */
#define UART_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"

/* Channel status information for all core */
static CONSTP2CONST(Uart_CoreStatusType, UART_VAR, UART_APPL_CONST)
                                      Uart_CoreStatus[MCAL_NUMBER_OF_CORES] =
{
/* Define the channel state structure on multi-Core0 */
#if (UART_MAX_CHANNEL_TO_CORE0 > 0U)
    &Uart_StatusSetCore0
#else
    NULL_PTR
#endif /* (UART_MAX_CHANNEL_TO_CORE0 \> 0U) */

/* Define the channel state structure on multi-Core1 */
#if (MCAL_NUMBER_OF_CORES > 1U)
#if (UART_MAX_CHANNEL_TO_CORE1 > 0U)
    ,&Uart_StatusSetCore1
#else
    ,NULL_PTR
#endif /* (UART_MAX_CHANNEL_TO_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

/* Define the channel state structure on multi-Core2 */
#if (MCAL_NUMBER_OF_CORES > 2U)
#if (UART_MAX_CHANNEL_TO_CORE2 > 0U)
    ,&Uart_StatusSetCore2
#else
    ,NULL_PTR
#endif /* (UART_MAX_CHANNEL_TO_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

/* Define the channel state structure on multi-Core3 */
#if (MCAL_NUMBER_OF_CORES > 3U)
#if (UART_MAX_CHANNEL_TO_CORE3 > 0U)
    ,&Uart_StatusSetCore3
#else
    ,NULL_PTR
#endif /* (UART_MAX_CHANNEL_TO_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */
};
/* #Violation: Uart_c_REF_7 */
#define UART_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"
#endif /* \(UART_DEV_ERROR_DETECT == STD_ON) */
/* #Violation: Uart_c_REF_7 */
#define UART_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"

/* This pointer shall be store to copy field, not non-cache field */
static P2CONST(Uart_ConfigType, UART_VAR, UART_APPL_CONST) Uart_ConfigPtr;
/* #Violation: Uart_c_REF_7 */
#define UART_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: Uart_c_REF_7 */
#define UART_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"

#if (UART_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, UART_PRIVATE_CODE) Uart_GetDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           Channel,
    uint8           ServiceId
);
#endif /* ((UAR_DEV_ERROR_DETECT  \== STD_ON) */
/* #Violation: Uart_c_REF_7 */
#define UART_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Uart_c_REF_7 */
#define UART_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"
#if (UART_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Uart_GetDetStatus
*
*   Service ID              : None.
*
*   Description             : DET check and return check result.
*
*   Parameters in           : CoreId: Execution Core ID
*                             Channel: Uart logical channel, If there is no logical channe, it is
*                                       marked with 0xFF
*                             ServiceId: API service ID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: No DET error.
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_GetDetStatus
(
    Mcal_CoreType   CoreId,
    uint8           Channel,
    uint8           ServiceId
)
{
    Std_ReturnType              RetStatus;

    /* Initialize API execution result status variables */
    RetStatus = E_NOT_OK;

    if(NULL_PTR == Uart_ConfigPtr)
    {
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, ServiceId,
                                UART_E_UNINIT);
    }
    /* Configuration information in current Corex is NULL */
    else if (NULL_PTR == Uart_ConfigPtr->CoreConfigPtr[CoreId])
    {
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, ServiceId,
                            UART_E_CORE_NOT_CONFIGURED);
    }
    /* Not Uart driver Status information storage variable in current core 
       or Not Uart driver init Status information storage variable in current core */
    else if((NULL_PTR == Uart_CoreStatus[CoreId]) || 
            (NULL_PTR == Uart_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, ServiceId,
                                UART_E_CORE_NOT_CONFIGURED);
    }
    /* API service used without module initialization */
    else if(UART_UNINITIALIZED == *(Uart_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, ServiceId,
                        UART_E_UNINIT);
    }
    /* API service used with an invalid or inactive channel parameter */
    else if (Channel >= UART_TOTAL_CFG_CHANNEL_NUM)
    {
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, ServiceId,
                            UART_E_INVALID_CHANNEL);
    }
    /* Channel number is greater than maximum configured of current core */
    else if (Uart_ConfigPtr->ChannelToCorePtr[Channel] >=
             Uart_ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreChannel)
    {
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, ServiceId,
                            UART_E_CORE_CHANNEL_MISMATCH);
    }
    /* Logical channel is mismatch */
    else if (Channel != Uart_ConfigPtr->CoreConfigPtr[CoreId]->
             ChannelConfigPtr[Uart_ConfigPtr->ChannelToCorePtr[Channel]].ChannelID)
    {
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, ServiceId,
                            UART_E_CORE_CHANNEL_MISMATCH);
    }
    else
    {
        RetStatus = E_OK;
    }

    return RetStatus;
}
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
/* #Violation: Uart_c_REF_7 */
#define UART_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Uart_c_REF_7 */
#define UART_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"

/****************************************************************************************************
*   Function Name           : Uart_Init
*
*   Service ID              : 0x00.
*
*   Description             : This function shall initializes the Uart Driver module.
*
*   Parameters in           : ConfigPtr: Pointer to UART driver configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Uart_c_REF_3 */
FUNC(void, UART_PUBLIC_CODE) Uart_Init
(
    CONSTP2CONST(Uart_ConfigType, AUTOMATIC, UART_APPL_CONST) ConfigPtr
)
{
    uint8                           CoreMaxChannel;
    uint8                           ChannelCounter;
    Std_ReturnType                  RetStatus;
    Mcal_CoreType                   CoreId;
    const Uart_ChannelConfigType    *ChannelConfigPtr;


    /* Get core id which is executing currently */
    /* #Violation: Uart_c_REF_4 */
    CoreId = Mcal_GetCoreId();
#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* The input parameter ConfigPtr is NULL_PTR */
    if(NULL_PTR == ConfigPtr)
    {
        RetStatus = E_NOT_OK;
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, UART_SID_INIT,
                                UART_E_INVALID_POINTER);
    }
    /* Not Uart driver Status information storage variable in current core */
    else if(NULL_PTR == Uart_CoreStatus[CoreId])
    {
        RetStatus = E_NOT_OK;
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, UART_SID_INIT,
                                UART_E_CORE_NOT_CONFIGURED);
    }
    /* API service used without module initialization */
    else if(UART_INITIALIZED == *(Uart_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        RetStatus = E_NOT_OK;
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, UART_SID_INIT,
                                UART_E_ALREADY_UNINIT);
    }
    else
    {
        RetStatus = E_OK;
    }
    
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        
        /* Ensure the value of RetStatus is 0U when DET detection is closed. */
        RetStatus = E_OK;
        /* Get the total channel number of current core */
        CoreMaxChannel = ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreChannel;
        /* Initialize all channels in current core */
        for (ChannelCounter = 0U;
            (ChannelCounter < CoreMaxChannel)&&(E_OK == RetStatus); ChannelCounter++)
        {
            /* Get the configuration information structure pointer of the current channel */
            ChannelConfigPtr = &(ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelCounter]);
            /* Enter critical protection to prevent interruption */
            UART_ENTER_CRITICAL_SECTION(Init);
            /* Get the results of hardware initialization operations */
            RetStatus = Asi_Uart_Hal_InitModule(ConfigPtr->HwUnitMapPtr[ChannelConfigPtr->
                HwUnitId], ChannelConfigPtr->HwUnitConfigPtr, UART_TIMEOUT_DURATION);
            /* Exit critical protection */
            UART_EXIT_CRITICAL_SECTION(Init);
        }
        /* Check whether all UART Channels are initialized successfully */
        if (E_OK == RetStatus)
        {
#if (UART_DEV_ERROR_DETECT == STD_ON)
            /* Initialization successful: Update Uart initialization status to 'UART_INITIALIZED' */
            *(Uart_CoreStatus[CoreId]->CoreInitStatusPtr) = UART_INITIALIZED;
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
            /* Update Uart configuration information to 'Uart_ConfigPtr' */
            if(Uart_ConfigPtr != ConfigPtr)
            {
                Uart_ConfigPtr = ConfigPtr;
            }
        }
#if (UART_DEV_ERROR_DETECT == STD_ON)
        else
        {
            /* Initialization fail: Update Uart initialization status to 'UART_UNINITIALIZED' */
            *(Uart_CoreStatus[CoreId]->CoreInitStatusPtr) = UART_UNINITIALIZED;
        }
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    }
}
/****************************************************************************************************
*   Function Name           : Uart_DeInit
*
*   Service ID              : 0x01
*
*   Description             : Service for Uart de-initialization.
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
*   Return value            : E_OK: de-initialisation command has been accepted.
*                             E_NOT_OK: de-initialisation command has not been accepted.
*
*   Preconditions           : Uart driver must be initialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Uart_c_REF_3 */
FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_DeInit
(
   void
)
{
    uint8                           CoreMaxChannel;
    uint8                           ChannelCounter;
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    const Uart_ChannelConfigType    *CoreChannelConfigPtr;
    Uart_HwUnitType                 CoreChannelHwUnitId;
    Std_ReturnType                  LockStatus;


    /* Get core id which is executing currently */
    /*#Violation: Uart_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* Not Uart driver Status information storage variable in current core */
    if(NULL_PTR == Uart_CoreStatus[CoreId])
    {
        RetStatus = E_NOT_OK;
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, UART_SID_DEINIT,
                                UART_E_CORE_NOT_CONFIGURED);
    }
    /* API service used without module initialization */
    else if (UART_UNINITIALIZED == *(Uart_CoreStatus[CoreId]->CoreInitStatusPtr))
    {
        RetStatus = E_NOT_OK;
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, UART_SID_DEINIT,
                    UART_E_UNINIT);
    }
    else
    {
        RetStatus = E_OK;
    }


    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        if (NULL_PTR != Uart_ConfigPtr)
        {
            /* Set API return state initial value */
            RetStatus = E_OK;
            /* Get the total channel number of current core */
            CoreMaxChannel = Uart_ConfigPtr->CoreConfigPtr[CoreId]->MaxCoreChannel;
            /* Get current core Uart channel config */
            CoreChannelConfigPtr = Uart_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr;
            /* DeInitialize all channels in current core */
            for (ChannelCounter = 0U; ChannelCounter < CoreMaxChannel; ChannelCounter++)
            {
                /* Enter critical protection to prevent interruption */
                UART_ENTER_CRITICAL_SECTION(DeInit);
                /* Lock for disable interrupts */
                LockStatus = Mcal_GetLock(MCAL_LOCK_ID_RCC);
                /* Spin lock acquisition success */
                if (E_OK == LockStatus)
                {
                    /* Get current current channel related Uart HwUnitId */
                    CoreChannelHwUnitId = CoreChannelConfigPtr[ChannelCounter].HwUnitId;
                    /* Get the results of hardware de-initialization operations */
                    RetStatus |= Asi_Hal_ResetModule( Uart_ConfigPtr->HwUnitMapPtr[CoreChannelHwUnitId]);
                     /* Release software lock for UART */
                    Mcal_ReleaseLock(MCAL_LOCK_ID_RCC);
                }
                else
                {
                    RetStatus |= E_NOT_OK;
                }
                /* Exit critical protection */
                UART_EXIT_CRITICAL_SECTION(DeInit);
            }
            /* Check whether all Uart channel de-initialization is completed */
            if(E_OK == RetStatus)
            {
#if (UART_DEV_ERROR_DETECT == STD_ON)
                /* De-init successful: Update Uart initialization status to 'UART_UNINITIALIZED' */
                *(Uart_CoreStatus[CoreId]->CoreInitStatusPtr) = UART_UNINITIALIZED;
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
            }
        }
        else
        {
            RetStatus = E_NOT_OK;
        }
    }

   return RetStatus;
}
#if (UART_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Uart_GetVersionInfo
*
*   Service ID              : 0x02.
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
/* #Violation: Uart_c_REF_3 */
FUNC(void, UART_PUBLIC_CODE) Uart_GetVersionInfo
(
    /* #Violation: Uart_c_REF_6 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, UART_APPL_DATA) VersionInfoPtr
)
{
#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* Get DET check result */
    if(NULL_PTR == VersionInfoPtr)
    {
        /* Invalid pointer */
        (void)Det_ReportError(UART_MODULE_ID, UART_INSTANCE_ID, UART_SID_GETVERSIONINFO,
                              UART_E_PARAM_POINTER);
    }
    else
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        VersionInfoPtr->vendorID = (uint16)UART_VENDOR_ID;
        VersionInfoPtr->moduleID = (uint16)UART_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)UART_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)UART_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)UART_SW_PATCH_VERSION;
    }
}
#endif /* UART_VERSION_INFO_API == STD_ON */
/****************************************************************************************************
*   Function Name           : Uart_GetStatus
*
*   Service ID              : 0x03.
*
*   Description             : Gets the status of the UART driver.
*
*   Parameters in           : Channel: Numeric identifier of the UART channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrantt.
*
*   Return value            : Uart_HWUnitStateType: UART HwUnit Status.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
/* #Violation: Uart_c_REF_3 */
FUNC(Uart_StatusType, UART_PUBLIC_CODE) Uart_GetStatus
(
    Uart_ChannelType Channel
)
{
    uint8                   ChannelIdx;
    Mcal_CoreType           CoreId;
    Uart_HwUnitType         PhyHwUnitId;
    Uart_StatusType         UartStatus;

#if (UART_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType              RetStatus;
#endif /* UART_DEV_ERROR_DETECT == STD_ON */

    /* Initialize Uart driver state variables */
    UartStatus = 0U;
    /* Get core id which is executing currently */
    /*#Violation: Uart_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* Get DET check results */
    RetStatus = Uart_GetDetStatus(CoreId, Channel, UART_SID_GETSTATUS);
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the channel index in current core */
        ChannelIdx = Uart_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get the ASI hardware unit mapped by UartChannel */
        PhyHwUnitId = Uart_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelIdx].HwUnitId;
        /* Enter critical protection to prevent interruption */
        UART_ENTER_CRITICAL_SECTION(GetStatus);
        /* Get the all status flag */
        UartStatus = Asi_Uart_Hal_GetFlagStatus(
            Uart_ConfigPtr->HwUnitMapPtr[PhyHwUnitId], UART_ALL_FLAGS);
        /* Clear the all status flag */
        Asi_Uart_Hal_ClearFlagStatus(
            Uart_ConfigPtr->HwUnitMapPtr[PhyHwUnitId], UART_CLEAR_ALL_FLAGS);
        /* Exit critical protection */
        UART_EXIT_CRITICAL_SECTION(GetStatus);
    }

    return UartStatus;
}
/****************************************************************************************************
*   Function Name           : Uart_Write
*
*   Service ID              : 0x04.
*
*   Description             : Serves the sending of UART data.
*
*   Parameters in           : Channel: UART channel to be addressed.
*                             DataBufferPtr: Data sending buffer.
*                             Length: The length of data sent
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Send command has been accepted.
*                             E_NOT_OK: Send command has not been accepted.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
/* #Violation: Uart_c_REF_3 */
FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_Write
(
    Uart_ChannelType            Channel,
    const Uart_DataBufferType * const DataBufferPtr,
    Uart_DataLengthType         LengthToWrite
)
{
    uint8                           ChannelIdx;
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    uint32                          TxStatus;
    uint32                          LoopCount;
    uint32                          DelayCount;
    const Uart_ChannelConfigType    *ChannelConfigPtr;
    const Uart_DataBufferType       *DataToTransimtPtr;
    boolean                         IsClearTxCompeletFlag;

#if (UART_CFG_TX_INTERRUPT_ENABLE == STD_ON)
    LoopCount = 0U;
#endif /* \(UART_CFG_TX_INTERRUPT_ENABLE == STD_ON) */

    /* Get core id which is executing currently */
    /*#Violation: Uart_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* Get DET check results */
    RetStatus = Uart_GetDetStatus(CoreId, Channel, UART_SID_WRITE);
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Initialize API execution result status variables */
        RetStatus = E_OK;
        /* Get the channel index in current core */
        ChannelIdx = Uart_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get the configuration information structure pointer of the current channel */
        ChannelConfigPtr = &(Uart_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelIdx]);
        /* Get the data buffer address to be sent */
        DataToTransimtPtr = DataBufferPtr;
        /* Start send data (data pack) */
        for(LoopCount = 0U; (LoopCount < LengthToWrite) && (E_OK == RetStatus); LoopCount++)
        {
            /* Enter critical protection to prevent interruption */
            UART_ENTER_CRITICAL_SECTION(Write);
            /* ASI hardware unit sends data frame */
            Asi_Uart_Hal_SendData(
                    Uart_ConfigPtr->HwUnitMapPtr[ChannelConfigPtr->HwUnitId], DataToTransimtPtr);
            /* Calculate send data buffer address offset */
            DataToTransimtPtr = &DataToTransimtPtr[ChannelConfigPtr->DataWidth];
            /* Wait for data sending to complete */
            DelayCount = UART_TIMEOUT_DURATION;
            do
            {
                /* Get the sending status flag */
                TxStatus = Asi_Uart_Hal_GetFlagStatus(Uart_ConfigPtr->HwUnitMapPtr
                                    [ChannelConfigPtr->HwUnitId], UART_TX_COMPLETED_FLAG);
                DelayCount--;
            } while ((UART_TX_COMPLETED_FLAG != TxStatus) && (0U < DelayCount));

            /* Check whether the send is completed and has not timed out */
            if (UART_TX_COMPLETED_FLAG == TxStatus)
            {
                IsClearTxCompeletFlag  = TRUE;
#if (UART_CFG_TX_INTERRUPT_ENABLE == STD_ON)
                if ((ChannelConfigPtr->UartTxNotification != NULL_PTR) && 
                    (LoopCount >= (LengthToWrite - 1U)))
                {
                    IsClearTxCompeletFlag = FALSE;
                }
#endif /* \(UART_CFG_TX_INTERRUPT_ENABLE == STD_ON) */
            }
            else 
            {
                IsClearTxCompeletFlag = FALSE;
                RetStatus = E_NOT_OK;
            }
            if (IsClearTxCompeletFlag == TRUE)
            {
                /* Clear the send completion flag */
                Asi_Uart_Hal_ClearFlagStatus(Uart_ConfigPtr->HwUnitMapPtr[ChannelConfigPtr->HwUnitId],
                        UART_TX_COMPLETED_FLAG);
            }
            /* Exit critical protection */
            UART_EXIT_CRITICAL_SECTION(Write);
        }
    }
#if (UART_CFG_TX_INTERRUPT_ENABLE == STD_ON)
    if ((LoopCount == LengthToWrite) && (UART_TX_COMPLETED_FLAG == TxStatus))
    {
        RetStatus = E_OK;
    }
#endif /* \(UART_CFG_TX_INTERRUPT_ENABLE == STD_ON) */
    return RetStatus;
}
/****************************************************************************************************
*   Function Name           : Uart_Read
*
*   Service ID              : 0x05.
*
*   Description             : Serves the reception of UART data.
*
*   Parameters in           : Channel: Numeric identifier of the UART channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : DataBufferPtr: Pointer to Storage address of data.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Send command has been accepted.
*                             E_NOT_OK: Send command has not been accepted.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Uart_c_REF_3 */
FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_Read
(
    Uart_ChannelType           Channel,
    Uart_DataBufferType        * const DataBufferPtr
)
{
    uint8                           ChannelIdx;
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    uint32                          RxStatus;
    const Uart_ChannelConfigType    *ChannelConfigPtr;


    /* Get core id which is executing currently */
    /*#Violation: Uart_c_REF_4 */
    CoreId = Mcal_GetCoreId();


#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* Get DET check results */
    RetStatus = Uart_GetDetStatus(CoreId, Channel, UART_SID_READ);
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Initialize API execution result status variables */
        RetStatus = E_NOT_OK;
        /* Get the channel index in current core */
        ChannelIdx = Uart_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get the configuration information structure pointer of the current channel */
        ChannelConfigPtr = &(Uart_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelIdx]);
        /* Enter critical protection to prevent interruption */
        UART_ENTER_CRITICAL_SECTION(Read);
        /* Get the receive status flag */
        RxStatus = Asi_Uart_Hal_GetFlagStatus(
            Uart_ConfigPtr->HwUnitMapPtr[ChannelConfigPtr->HwUnitId], UART_RX_COMPLETED_FLAG);
        /* Check if the receive flag is set */
        if (UART_RX_COMPLETED_FLAG == RxStatus)
        {
            /* ASI hardware unit receive data frame */
            Asi_Uart_Hal_ReceiveData(
                    Uart_ConfigPtr->HwUnitMapPtr[ChannelConfigPtr->HwUnitId], DataBufferPtr);
            /* Clear receive completion status flag */
            Asi_Uart_Hal_ClearFlagStatus(Uart_ConfigPtr->HwUnitMapPtr[ChannelConfigPtr->HwUnitId],
                UART_RX_COMPLETED_FLAG | ASI_UART_BUFFER_DATA_READY_FLAG);
            /* Update API execution results to 'E_OK' */
            RetStatus = E_OK;
        }
        /* Exit critical protection */
        UART_EXIT_CRITICAL_SECTION(Read);
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Uart_GoToSleep
*
*   Service ID              : 0x06.
*
*   Description             : Serve sleep specified UartChannel.
*
*   Parameters in           : Channel: UART channel to be addressed.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Send command has been accepted.
*                             E_NOT_OK: Send command has not been accepted.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
/* #Violation: Uart_c_REF_3 */
FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_GoToSleep
(
    Uart_ChannelType        Channel
)
{
    uint8                           ChannelIdx;
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    const Uart_ChannelConfigType    *ChannelConfigPtr;

    /* Get core id which is executing currently */
    /*#Violation: Uart_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* Get DET check results */
    RetStatus = Uart_GetDetStatus(CoreId, Channel, UART_SID_GOTOSLEEP);
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Update API execution results to 'E_OK' */
        RetStatus = E_OK;
        /* Get the index of Channel in the current Core */
        ChannelIdx = Uart_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get the current channel configuration information structure pointer */
        ChannelConfigPtr = &(Uart_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelIdx]);
        /* ASI hardware unit enters low power mode */
        Asi_Hal_EnterSleepMode(Uart_ConfigPtr->HwUnitMapPtr[ChannelConfigPtr->HwUnitId]);
    }

    return RetStatus;
}
/****************************************************************************************************
*   Function Name           : Uart_WakeUp
*
*   Service ID              : 0x07.
*
*   Description             : Serve wake up specified UartChannel.
*
*   Parameters in           : Channel: UART channel to be addressed.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: Send command has been accepted.
*                             E_NOT_OK: Send command has not been accepted.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
/* #Violation: Uart_c_REF_3 */
FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_WakeUp
(
    Uart_ChannelType        Channel
)
{
    uint8                           ChannelIdx;
    Mcal_CoreType                   CoreId;
    Std_ReturnType                  RetStatus;
    const Uart_ChannelConfigType    *ChannelConfigPtr;

    /* Get core id which is executing currently */
    /*#Violation: Uart_c_REF_4 */
    CoreId = Mcal_GetCoreId();

#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* Get DET check results */
    RetStatus = Uart_GetDetStatus(CoreId, Channel, UART_SID_WAKEUP);
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Update API execution results to 'E_OK' */
        RetStatus = E_OK;
        /* Get the index of Channel in the current Core */
        ChannelIdx = Uart_ConfigPtr->ChannelToCorePtr[Channel];
        /* Get the current channel configuration information structure pointer */
        ChannelConfigPtr = &(Uart_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[ChannelIdx]);
        /*  ASI hardware unit exits low power mode */
        (void)Asi_Hal_ExitSleepMode(Uart_ConfigPtr->HwUnitMapPtr[ChannelConfigPtr->HwUnitId]);
    }

    return RetStatus;
}
#if (UART_CFG_RX_INTERRUPT_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Uart_Rx_ISRHandler
*
*   Service ID              : 0xE2.
*
*   Description             : Uart receive interrupt service function.
*
*   Parameters in           : HwUnit: Hardware unit physical ID.
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
FUNC(void, UART_PUBLIC_CODE) Uart_Rx_ISRHandler
(
    Uart_HwUnitType HwUnit
)
{
    uint8                   ChannelIdx;
    uint16                  DataBuffer;
    Mcal_CoreType           CoreId;
    Uart_ChannelType        Channel;

#if (UART_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType           RetStatus;
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    /* Get core id which is executing currently */
    CoreId = Mcal_GetCoreId();
    /* Get the UartChannel ID mapped by the ASI hardware unit */
    Channel = Uart_ConfigPtr->HwUnitToChannelIdPtr[HwUnit];

#if (UART_DEV_ERROR_DETECT == STD_ON)
    RetStatus = Uart_GetDetStatus(CoreId, Channel, UART_SID_ISR_RECV);
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Init DataBuffer */
        DataBuffer = 0U;
        /* ASI hardware unit receive data frame */
        Asi_Uart_Hal_ReceiveData(Uart_ConfigPtr->HwUnitMapPtr[HwUnit], (uint8*)&DataBuffer);
        /* Clear receive completion status flag */
        Asi_Uart_Hal_ClearFlagStatus(Uart_ConfigPtr->HwUnitMapPtr[HwUnit],
                        ASI_UART_RX_COMPLETED_FLAG | ASI_UART_BUFFER_DATA_READY_FLAG);
        /* Get the index number of Channel in the current Core */
        ChannelIdx = Uart_ConfigPtr->ChannelToCorePtr[Channel];
        /* Check if EndNotification exists */
        if (NULL_PTR != Uart_ConfigPtr->CoreConfigPtr[CoreId]->\
                        ChannelConfigPtr[ChannelIdx].UartRxNotification)
        {
            /* Handle EndNotification tasks */
            Uart_ConfigPtr->CoreConfigPtr[CoreId]->\
                    ChannelConfigPtr[ChannelIdx].UartRxNotification(DataBuffer);
        }
    }
}
#endif /* \(UART_CFG_RX_INTERRUPT_ENABLE == STD_ON) */

#if (UART_CFG_TX_INTERRUPT_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Uart_Tx_ISRHandler
*
*   Service ID              : 0xE1.
*
*   Description             : Uart sends interrupt service function.
*
*   Parameters in           : HwUnit: Hardware unit physical ID.
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
FUNC(void, UART_PUBLIC_CODE) Uart_Tx_ISRHandler
(
    Uart_HwUnitType HwUnit
)
{

    Uart_ChannelType        Channel;
    uint8                   ChannelIdx;
    Mcal_CoreType           CoreId;

#if (UART_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType           RetStatus;
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */

    /* Get core id which is executing currently */
    CoreId = Mcal_GetCoreId();
    /* Get the UartChannel ID mapped by the ASI hardware unit */
    Channel = Uart_ConfigPtr->HwUnitToChannelIdPtr[HwUnit];

#if (UART_DEV_ERROR_DETECT == STD_ON)
    RetStatus = Uart_GetDetStatus(CoreId, Channel, UART_SID_ISR_SEND);
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Clear receive completion status flag */
        Asi_Uart_Hal_ClearFlagStatus(
                Uart_ConfigPtr->HwUnitMapPtr[HwUnit], ASI_UART_TX_COMPLETED_FLAG);
        /* Get the index number of Channel in the current Core */
        ChannelIdx = Uart_ConfigPtr->ChannelToCorePtr[Channel];
        /* Check if EndNotification exists */
        if (NULL_PTR != Uart_ConfigPtr->CoreConfigPtr[CoreId]->\
                        ChannelConfigPtr[ChannelIdx].UartTxNotification)
        {
            /* Handle EndNotification tasks */
            Uart_ConfigPtr->CoreConfigPtr[CoreId]->\
                    ChannelConfigPtr[ChannelIdx].UartTxNotification();
        }
    }
}
#endif /* \(UART_CFG_TX_INTERRUPT_ENABLE == STD_ON) */

#if (UART_CFG_ERROR_INTERRUPT_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Uart_Error_ISRHandler
*
*   Service ID              : 0xE0.
*
*   Description             : Uart error interrupt service function.
*
*   Parameters in           : HwUnit: Hardware unit physical ID.
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
FUNC(void, UART_PUBLIC_CODE) Uart_Error_ISRHandler
(
    Uart_HwUnitType HwUnit
)
{
    uint8                       Channel;
    uint8                       ChannelIdx;
    Mcal_CoreType               CoreId;
    Uart_StatusType             StatusValue;

#if (UART_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType           RetStatus;
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */

    /* Get core id which is executing currently */
    CoreId = Mcal_GetCoreId();
    /* Get the UartChannel ID mapped by the ASI hardware unit */
    Channel = Uart_ConfigPtr->HwUnitToChannelIdPtr[HwUnit];

#if (UART_DEV_ERROR_DETECT == STD_ON)
    /* Get DET check results */
    RetStatus = Uart_GetDetStatus(CoreId, Channel, UART_SID_ISR_ERROR);
    if(E_OK == RetStatus)
#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Get the all status flag */
        StatusValue = Asi_Uart_Hal_GetFlagStatus(
            Uart_ConfigPtr->HwUnitMapPtr[HwUnit], UART_ALL_FLAGS);
        /* Clear receive completion status flag */
        Asi_Uart_Hal_ClearFlagStatus(
                Uart_ConfigPtr->HwUnitMapPtr[HwUnit], ASI_UART_ALL_ERROR_INTS);
        /* Get the index number of Channel in the current Core */
        ChannelIdx = Uart_ConfigPtr->ChannelToCorePtr[Channel];
        /* Check if EndNotification exists */
        if (NULL_PTR != Uart_ConfigPtr->CoreConfigPtr[CoreId]->\
                        ChannelConfigPtr[ChannelIdx].UartErrorNotification)
        {
            /* Handle EndNotification tasks */
            Uart_ConfigPtr->CoreConfigPtr[CoreId]->\
                    ChannelConfigPtr[ChannelIdx].UartErrorNotification(StatusValue);
        }
    }
}
#endif /* \(UART_CFG_ERROR_INTERRUPT_ENABLE == STD_ON) */
/* #Violation: Uart_c_REF_7 */
#define UART_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Uart_c_REF_2 */ 
#include "Uart_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
*****************************************************************************************************/

