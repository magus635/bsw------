/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : This file contains all functions of IOM module
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
*#Iom_c_REF_1:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Iom_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Iom_c_REF_3:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Iom_c_REF_4:MISRAC2012-Dir-4.1; 
* Justification: This loop will never be executed more than once.
*
*#Iom_c_REF_5:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Iom_c_REF_6:MISRAC2012-Rule-2.2; 
* Justification: Code review ensures the compliance with rule.
*
*#Iom_c_REF_7:MISRAC2012-Rule-2.2; 
* Justification: Code review ensures the compliance with rule.
*
*#Iom_c_REF_8:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*#Iom_c_REF_9:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Iom_c_REF_10:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Iom_c_REF_11:CertC-DCL02-C;
* Justification: Company-specific naming conventions  are applied. Developers will not be confused.
*
*#Iom_c_REF_12:CertC-DCL00-C;
* Justification: Parameter declared refer to AUTOSAR specifications.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Iom.h"
#include "Mcall.h"
#include "iom_hal.h"
#include "Iom_GeneralTypes.h"
#include "Iom_Cfg.h"
#include "SchM_Iom.h"
#include "Iom_Version.h"
#include "Det.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (IOM_VENDOR_ID != IOM_CFG_VENDOR_ID)
  #error "Iom.c : Mismatch in Vendor ID"
#endif /* (IOM_VENDOR_ID !\= IOM_CFG_VENDOR_ID) */

#if (IOM_MODULE_ID != IOM_CFG_MODULE_ID)
  #error "Iom.c : Mismatch in Module ID"
#endif /* \(IOM_MODULE_ID != IOM_CFG_MODULE_ID) */

#if (IOM_AR_RELEASE_MAJOR_VERSION != IOM_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Iom.c : Mismatch in Release Major Version"
#endif /* (IOM_AR_RELEASE_MAJOR_VERSION !\= IOM_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (IOM_AR_RELEASE_MINOR_VERSION != IOM_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Iom.c : Mismatch in Release Minor Version"
#endif /* (IOM_AR_RELEASE_MINOR_VERSION !\= IOM_CFG_AR_RELEASE_MINOR_VERSION) */

#if (IOM_AR_RELEASE_REVISION_VERSION != IOM_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Iom.c : Mismatch in Release Revision Version"
#endif /* (IOM_AR_RELEASE_REVISION_VERSION !\= IOM_CFG_AR_RELEASE_REVISION_VERSION) */

#if (IOM_SW_MAJOR_VERSION != IOM_CFG_SW_MAJOR_VERSION)
  #error "Iom.c : Mismatch in Software Major Version"
#endif /* (IOM_SW_MAJOR_VERSION !\= IOM_CFG_SW_MAJOR_VERSION) */

#if (IOM_SW_MINOR_VERSION != IOM_CFG_SW_MINOR_VERSION)
  #error "Iom.c : Mismatch in Software Minor Version"
#endif /* (IOM_SW_MINOR_VERSION !\= IOM_CFG_SW_MINOR_VERSION) */

#if (IOM_SW_PATCH_VERSION != IOM_CFG_SW_PATCH_VERSION)
  #error "Iom.c : Mismatch in Software Patch Version"
#endif /* \(IOM_SW_PATCH_VERSION != IOM_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: Iom_c_REF_1*/
/* #Violation: Iom_c_REF_10*/
#define IOM_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Iom_##Exclusive_Area()
/* #Violation: Iom_c_REF_1*/
/* #Violation: Iom_c_REF_10*/
#define IOM_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Iom_##Exclusive_Area()

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if (0U == IOM_CORE_ALLOCATION)
/* #Violation: Iom_c_REF_2*/
#define IOM_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == IOM_CORE_ALLOCATION)
#define IOM_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == IOM_CORE_ALLOCATION)
#define IOM_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == IOM_CORE_ALLOCATION)
#define IOM_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#endif
#include "Iom_MemMap.h"

#if (STD_ON == IOM_DEV_ERROR_DETECT)
/* To store the initialization state of the Iom driver */
static Iom_InitType Iom_InitStatus;
#endif /* (STD_ON \== IOM_DEV_ERROR_DETECT) */

/* To store the Iom driver configuration pointer */
static P2CONST(Iom_ConfigType, AUTOMATIC, IOM_PRIVATE_DATA) Iom_ConfigPtr;

#if (0U == IOM_CORE_ALLOCATION)
/* #Violation: Iom_c_REF_2*/
#define IOM_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == IOM_CORE_ALLOCATION)
#define IOM_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == IOM_CORE_ALLOCATION)
#define IOM_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == IOM_CORE_ALLOCATION)
#define IOM_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#endif
/* #Violation: Iom_c_REF_3*/
#include "Iom_MemMap.h"

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
/* #Violation: Iom_c_REF_2*/
#define IOM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Iom_c_REF_3*/
#include "Iom_MemMap.h"

#if (IOM_DEV_ERROR_DETECT == STD_ON)

static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Iom_IsPpuChannelAvailable
(
    Iom_PpuChannelType PpuChannelNumber
);

#if (STD_ON == IOM_PPU_PRESCALER_API)
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Iom_IsPpuChannelPrescalerMode
(
    uint8 ServiceId,
    Iom_PpuChannelType PpuChannelNumber
);
#endif /* (IOM_PPU_PRESCALER_API  \== STD_ON) */

#if (STD_ON == IOM_PPU_FILTER_API)
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Iom_IsPpuChannelFilterMode
(
    uint8 ServiceId,
    Iom_PpuChannelType PpuChannelNumber
);
#endif /* (IOM_PPU_FILTER_API  \== STD_ON) */

static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Iom_IsLpuChannelAvailable
(
    Iom_LpuChannelIdType LpuChannelNumber
);

#endif /* (IOM_DEV_ERROR_DETECT  \== STD_ON) */

/* #Violation: Iom_c_REF_2*/
#define IOM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Iom_c_REF_3*/
#include "Iom_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Iom_c_REF_2*/
#define IOM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Iom_c_REF_3*/
#include "Iom_MemMap.h"

#if (IOM_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Iom_IsPpuChannelAvailable
*
*   Service ID              : None.
*
*   Description             : DET check for Ppu channel number.
*
*   Parameters in           : PpuChannelNumber: Ppu channel number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : Std_ReturnType: Return the DET check status
*                             - E_OK: No error
*                             - E_NOT_OK: Error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Iom_IsPpuChannelAvailable
(
    Iom_PpuChannelType PpuChannelNumber
)
{
    Std_ReturnType ReturnValue;
    uint8 ChannelNumber;

    ChannelNumber = 0U;
    ReturnValue = E_NOT_OK;
    /*Check Ppu channel MAX */
    if (IOM_PPU_CHANNEL_MAX >= (uint8)PpuChannelNumber)
    {
        /* Check each of the signals */
/* #Violation: Iom_c_REF_4*/
        while ((ChannelNumber < IOM_CHANNEL_USED_NUMBER) && (ReturnValue == E_NOT_OK))
        {
            /* Check both monitor signals and reference signals */
            if (((((uint16)Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].monitor.input & IOM_PPU_CHANNEL_MASK) ==
                (uint16)PpuChannelNumber) ||
                (((uint16)Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].reference.input & IOM_PPU_CHANNEL_MASK) ==
                (uint16)PpuChannelNumber)))
            {
                ReturnValue = E_OK;
            }
            ChannelNumber++;
        }
    }
    return ReturnValue;
}

#if (STD_ON == IOM_PPU_PRESCALER_API)
#if defined(THA6_THA6412) || defined(THA6_THA6104)
/****************************************************************************************************
*   Function Name           : Iom_IsPpuChannelPrescalerMode
*
*   Service ID              : None.
*
*   Description             : DET check for Ppu prescaler mode.
*
*   Parameters in           : ServiceId: Service id of calling API.
*                             PpuChannelNumber: Ppu channel number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : Std_ReturnType: Return the DET check status
*                             - E_OK: No error
*                             - E_NOT_OK: Error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Iom_IsPpuChannelPrescalerMode
(
    uint8 ServiceId,
    Iom_PpuChannelType PpuChannelNumber
)
{
    uint8 ChannelNumber;
    uint8 ChannelRecord;
    Std_ReturnType ReturnValue;

    ChannelRecord = 0U;
    ChannelNumber = 0U;
    ReturnValue = E_OK;
/* #Violation: Iom_c_REF_4*/
    while ((IOM_CHANNEL_USED_NUMBER > ChannelNumber) && (E_OK == ReturnValue))
    {
        /* Check each of the signals */
        if (((uint16)Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].monitor.input & IOM_PPU_CHANNEL_MASK) ==
            (uint16)PpuChannelNumber)
        {
            /* Recoed the channel that has already been set */
            ChannelRecord = 1U;
            /* Check if Ppu filter mode is correct */
            if ((IOM_PPUFILTERMODE_PRESCALERONRISINGEDGE !=
                 Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].monitor.filter.mode) &&
                 (IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE !=
                 Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].monitor.filter.mode))
            {
                (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, ServiceId,
                                      IOM_E_PARAM_PPUPRESCALER_MODE);
                ReturnValue = E_NOT_OK;
            }

        }
        /* Check each of the reference signals */
        if (((uint16)Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].reference.input & IOM_PPU_CHANNEL_MASK) ==
            (uint16)PpuChannelNumber)
        {
            /* Recoed the channel that has already been set */
            ChannelRecord = 1U;
            /* Check if Ppu filter mode is correct */
            if ((IOM_PPUFILTERMODE_PRESCALERONRISINGEDGE !=
                 Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].reference.filter.mode) &&
                 (IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE !=
                 Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].reference.filter.mode))
            {
                if (E_OK == ReturnValue) 
                {
                    (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, ServiceId,
                                          IOM_E_PARAM_PPUPRESCALER_MODE);
                    ReturnValue = E_NOT_OK;
                }
            }
        }
        ChannelNumber++;
    }
    /* Check if Ppu channel id is available */
    if (0U == ChannelRecord)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, ServiceId,
                              IOM_E_PARAM_PPUNO);
        ReturnValue = E_NOT_OK;
    }

    return ReturnValue;
}
#endif
#endif /* (IOM_PPU_PRESCALER_API  \== STD_ON) */

#if (STD_ON == IOM_PPU_FILTER_API)
/****************************************************************************************************
*   Function Name           : Iom_IsPpuChannelFilterMode
*
*   Service ID              : None.
*
*   Description             : DET check for Ppu filter mode.
*
*   Parameters in           : ServiceId:Service id of calling API.
*                             PpuChannelNumber: Ppu channel number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : Std_ReturnType: Return the DET check status
*                             - E_OK: No error
*                             - E_NOT_OK: Error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Iom_IsPpuChannelFilterMode
(
    uint8 ServiceId,
    Iom_PpuChannelType PpuChannelNumber
)
{
    uint8 ChannelNumber;
    uint8 ChannelRecord;
    Std_ReturnType ReturnValue;

    ChannelRecord = 0U;
    ChannelNumber = 0U;
    ReturnValue = E_OK;
/* #Violation: Iom_c_REF_4*/
    while ((IOM_CHANNEL_USED_NUMBER > ChannelNumber) && (E_OK == ReturnValue))
    {
        /* Check each of the signals */
        if (((uint16)Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].monitor.input & IOM_PPU_CHANNEL_MASK) ==
            (uint16)PpuChannelNumber)
        {
            /* Recoed the channel that has already been set */
            ChannelRecord = 1U;
            /* Check if Ppu filter mode is correct */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
            if (
                (IOM_PPUFILTERMODE_PRESCALERONRISINGEDGE ==
                Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].monitor.filter.mode) ||
                (IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE ==
                Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].monitor.filter.mode) ||
                (IOM_PPUFILTERMODE_NOFILTER ==
                Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].monitor.filter.mode)
            )

            {
                (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, ServiceId,
                                      IOM_E_PARAM_PPUFILTER_MODE);
                ReturnValue = E_NOT_OK;
            }
#endif
        }
        /* Check each of the reference signals */
        if (((uint16)Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].reference.input & IOM_PPU_CHANNEL_MASK) ==
            (uint16)PpuChannelNumber)
        {
            /* Recored the channel that has already been set */
            ChannelRecord = 1U;
            /* Check if Ppu filter mode is correct */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
            if (
                (IOM_PPUFILTERMODE_PRESCALERONRISINGEDGE ==
                Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].reference.filter.mode) ||
                (IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE ==
                Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].reference.filter.mode) ||
                (IOM_PPUFILTERMODE_NOFILTER ==
                Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].reference.filter.mode))
            {
                if (E_OK == ReturnValue)
                {
                    (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, ServiceId,
                                          IOM_E_PARAM_PPUFILTER_MODE);
                    ReturnValue = E_NOT_OK;
                }
            }
#endif
        }
        ChannelNumber++;
    }
    /* Check if Ppu channel id is available */
    if (0U == ChannelRecord)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, ServiceId,
                              IOM_E_PARAM_PPUNO);
        ReturnValue = E_NOT_OK;
    }

    return ReturnValue;
}
#endif /* (IOM_PPU_FILTER_API  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Iom_IsLpuChannelAvailable
*
*   Service ID              : None.
*
*   Description             : DET check for LPU channel number.
*
*   Parameters in           : LpuChannelNumber: Lpu channel number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : Std_ReturnType: Return the DET check status
*                             - E_OK: No error
*                             - E_NOT_OK: Error exists
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, INTC_PRIVATE_CODE) Iom_IsLpuChannelAvailable
(
    Iom_LpuChannelIdType LpuChannelNumber
)
{
    Std_ReturnType ReturnValue;
    uint8 ChannelNumber;

    ChannelNumber = 0U;
    ReturnValue = E_NOT_OK;
    /*Check Lpu channel MAX */
    if (IOM_LPU_CHANNEL_MAX >= (uint8)LpuChannelNumber)
    {
        /* Check each of the signals */
/* #Violation: Iom_c_REF_4*/
        while ((ChannelNumber < IOM_CHANNEL_USED_NUMBER) && (ReturnValue == E_NOT_OK))
        {
            /* Check both monitor signals and reference signals */
            if (((Iom_ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber].channel) == LpuChannelNumber))
            {
                ReturnValue = E_OK;
            }
            ChannelNumber++;
        }
    }
    return ReturnValue;
}

#endif /* (IOM_DEV_ERROR_DETECT  \== STD_ON) */

/* #Violation: Iom_c_REF_2*/
#define IOM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Iom_c_REF_3*/
#include "Iom_MemMap.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Iom_c_REF_2*/
#define IOM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Iom_c_REF_3*/
#include "Iom_MemMap.h"

/****************************************************************************************************
*   Function Name           : Iom_Init
*
*   Service ID              : 0x00.
*
*   Description             : This function shall will initialize all relevant registers
*                             of Iom hardware .
*
*   Parameters in           : ConfigPtr - Pointer to configuration set
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None
*
*   Preconditions           : IOM module must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(void, IOM_PUBLIC_CODE) Iom_Init
(
/* #Violation: Iom_c_REF_12*/
    P2CONST(Iom_ConfigType, AUTOMATIC, IOM_APPL_CONST) ConfigPtr
)
{
    Iom_LpuChannelType Iom_LpuConfigRecord;
    uint8 ChannelNumber;
    boolean Iom_RegRet;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    uint8 SafetyStatus;
    Mcal_CoreType CoreId;
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */

    Iom_RegRet = TRUE;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_INIT, IOM_E_CORE_NOT_CONFIGURED);
    }
    /* Check if ConfigPtr is a null pointer */
    else if (NULL_PTR == ConfigPtr)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_INIT, IOM_E_PARAM_INVALID);
    }
    /* Check if the IOM status is INITIALIZED */
    else if (IOM_INITIALIZED == Iom_InitStatus)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_INIT, IOM_E_INIT);
    }
    else
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */
    {
        /* Assign global configuration pointer */
        Iom_ConfigPtr = ConfigPtr;

        IOM_ENTER_CRITICAL_SECTION(Init);
        /* Set the Prescaler factor */
        Iom_RegRet &= Iom_Hal_SetClock(Iom_ConfigPtr->Iom_Clock_Div);
        IOM_EXIT_CRITICAL_SECTION(Init);

        /* Initialize each configured channel */
/* #Violation: Iom_c_REF_4*/
        for (ChannelNumber = 0U; ChannelNumber < IOM_CHANNEL_USED_NUMBER; ChannelNumber++)
        {
            /* Initialize the configured LPU channel */
            Iom_RegRet &= Iom_Hal_InitLpu(&Iom_LpuConfigRecord, 
                        &(ConfigPtr->Iom_LpuChannelConfigPtr[ChannelNumber]));
        }
#if (STD_ON == IOM_SAFETY_ENABLE)
        if (TRUE != Iom_RegRet)
        {
            (void)Det_ReportRuntimeError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_INIT, IOM_E_WRITE_REGISTER);
        }
        else
#endif /* STD_ON \== IOM_SAFETY_ENABLE */
        {
#if (STD_ON == IOM_DEV_ERROR_DETECT)
            /* Check if the register written is triggered E/SE protect */
            SafetyStatus = Iom_Hal_GetSafetyStatus();
            /* Check if the register is written correctly */
            if (0U != SafetyStatus)
            {
                (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_INIT, 
                                      IOM_E_REGISTER_WRITTEN_FALSE);
            }
            else
            {
                /* Set IOM status to IOM_INITIALIZED */
                Iom_InitStatus = IOM_INITIALIZED;
            }
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */
        }
    }
/* #Violation: Iom_c_REF_5*/
    MCAL_UNUSED_VAR(Iom_RegRet);
}

#if (STD_ON == IOM_GET_PPUGLITCH_API)
/****************************************************************************************************
*   Function Name           : Iom_GetPpuGlitch
*
*   Service ID              : 0x01.
*
*   Description             : Service for getting glitch information for the input signal, and 
*                             automatically delete the information after getting it.
*
*   Parameters in           : PpuChannelNumber: Number of the PPU channel
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : EdgeStatus : input signal edge glitch status.
*                             IOM_PPUGLITCHFLAG_NONE: Neither edge glitch flag
*                             IOM_PPUGLITCHFLAG_RISINGEDGE: Positive edge glitch flag
*                             IOM_PPUGLITCHFLAG_FALLINGEDGE: Negative edge glitch flag
*                             IOM_PPUGLITCHFLAG_ANYEDGE: Either edge glitch flag
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(Iom_PpuGlitchFlagType, IOM_PUBLIC_CODE) Iom_GetPpuGlitch
(
    Iom_PpuChannelType PpuChannelNumber
)
{
    Iom_PpuGlitchFlagType EdgeStatus;

#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Std_ReturnType ReturnValue;
    Mcal_CoreType CoreId;

    /* DET reported, Invalid value is returned */
    EdgeStatus = IOM_PPUGLITCHFLAG_NONE;

    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETGLITCH, 
                              IOM_E_CORE_NOT_CONFIGURED);
    }
    /* Check IOM state */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETGLITCH,
                              IOM_E_UNINIT);
    }
    else
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */ 
    {
#if (STD_ON == IOM_DEV_ERROR_DETECT)
        /* Check if Ppu channel id is available */
        ReturnValue = Iom_IsPpuChannelAvailable(PpuChannelNumber);
        if (E_NOT_OK == ReturnValue)
        {
            /* Report DET IOM_E_PARAM_PPUNO */
            (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETGLITCH,
                          IOM_E_PARAM_PPUNO);
        }
        else
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */
        {
            IOM_ENTER_CRITICAL_SECTION(GetGlitch);
            /* Get PPU GPIO input signal edge glitch status */
            EdgeStatus = Iom_Hal_GetGlitch(PpuChannelNumber);
            /* Clear PPU GPIO input signal edge glitch status */
            Iom_Hal_ClearGlitch(PpuChannelNumber, EdgeStatus);
            IOM_EXIT_CRITICAL_SECTION(GetGlitch);
        }
    }
    return EdgeStatus;
}
#endif /* (IOM_GET_PPUGLITCH_API  \== STD_ON) */

#if (STD_ON == IOM_PPU_PRESCALER_API)
/****************************************************************************************************
*   Function Name           : Iom_SetPpuPrecalerThreshold
*
*   Service ID              : 0x02.
*
*   Description             : Service for setting the specific Ppu Precaler factor.
*
*   Parameters in           : PpuChannelNumber: Ppu channel number.
*                             Threshold: the specific Ppu Precaler factor.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(void, IOM_PUBLIC_CODE) Iom_SetPpuPrecalerThreshold
(
    Iom_PpuChannelType PpuChannelNumber,
    Iom_PpuPrescalerThresholdType Threshold
)
{
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Std_ReturnType DetErr;
    Mcal_CoreType CoreId;
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */
    boolean Iom_RegRet;

    Iom_RegRet = TRUE;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETPPUPRECALER, 
                              IOM_E_CORE_NOT_CONFIGURED);
        DetErr = E_NOT_OK;
    }
    /* Check IOM state */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETPPUPRECALER,
                              IOM_E_UNINIT);
        DetErr = E_NOT_OK;
    }
    /* Check if Ppu channel number is greater than IOM_PPU_CHANNEL_MAX */
    else if (IOM_PPU_CHANNEL_MAX < (uint8)PpuChannelNumber)
    {
        /* Report DET IOM_E_PARAM_PPUNO */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID,
                              IOM_SID_SETPPUPRECALER, IOM_E_PARAM_PPUNO);
        DetErr = E_NOT_OK;
    }
    /* Check if Ppu Threshold is greater than IOM_PPU_THRES_MAX */
/* #Violation: Iom_c_REF_6*/
    else if (IOM_PPU_THRES_MAX < Threshold)
    {
        /* Report DET IOM_E_PARAM_PPUNO */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID,
                              IOM_SID_SETPPUPRECALER, IOM_E_PARAM_THRESHOLD);
        DetErr = E_NOT_OK;
    }
    else
    {
        DetErr = Iom_IsPpuChannelPrescalerMode(IOM_SID_SETPPUPRECALER, PpuChannelNumber);
    }
    if (E_OK == DetErr)
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */
    {
        IOM_ENTER_CRITICAL_SECTION(SetPPUPrecaler);
        /* Set Prescaler factor Threshold */
        Iom_RegRet &= Iom_Hal_SetPpuThreshold(PpuChannelNumber, (uint16)Threshold);
        IOM_EXIT_CRITICAL_SECTION(SetPPUPrecaler);
#if (STD_ON == IOM_SAFETY_ENABLE)
        if (TRUE != Iom_RegRet)
        {
            (void)Det_ReportRuntimeError(IOM_MODULE_ID, IOM_INSTANCE_ID,
                                         IOM_SID_SETPPUPRECALER, IOM_E_WRITE_REGISTER);
        }
#endif /* STD_ON \== IOM_SAFETY_ENABLE */
    }
/* #Violation: Iom_c_REF_5*/
    MCAL_UNUSED_VAR(Iom_RegRet);
}

/****************************************************************************************************
*   Function Name           : Iom_GetPpuPrecalerThreshold
*
*   Service ID              : 0x03.
*
*   Description             : Service for getting the specific Ppu Precaler factor.
*
*   Parameters in           : PpuChannelNumber: PPU channel number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Threshold : the specific Ppu Precaler factor.
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(Iom_PpuPrescalerThresholdType, IOM_PUBLIC_CODE) Iom_GetPpuPrecalerThreshold
(
    Iom_PpuChannelType PpuChannelNumber
)
{
    Iom_PpuPrescalerThresholdType Threshold;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Std_ReturnType DetErr;
    Mcal_CoreType CoreId;

    /* DET reported, Invalid value is returned */
    Threshold = IOM_THRESHOLD_FALSE;
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETPPUPRECALER, 
                              IOM_E_CORE_NOT_CONFIGURED);
        DetErr = E_NOT_OK;
    }
    /* Check IOM state */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETPPUPRECALER,
                              IOM_E_UNINIT);
        DetErr = E_NOT_OK;
    }
    /* Check if Ppu channel number is greater than IOM_PPU_CHANNEL_MAX */
    else if (IOM_PPU_CHANNEL_MAX < (uint8)PpuChannelNumber)
    {
        /* Report DET IOM_E_PARAM_PPUNO */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID,
                              IOM_SID_GETPPUPRECALER, IOM_E_PARAM_PPUNO);
        DetErr = E_NOT_OK;
    }
    else
    {
        /* Check if Ppu channel id is available and if Ppu channel is prescaler mode */
        DetErr = Iom_IsPpuChannelPrescalerMode(IOM_SID_GETPPUPRECALER, PpuChannelNumber);
    }
    if (E_OK == DetErr)
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
    {
        /* Get PPU Threshold */
        Threshold = Iom_Hal_GetPpuThreshold(PpuChannelNumber);
    }
    return Threshold;
}
#endif /* (IOM_PPU_PRESCALER_API  \== STD_ON) */

#if (STD_ON == IOM_PPU_FILTER_API)
/****************************************************************************************************
*   Function Name           : Iom_SetPpuFilterTimeThreshold
*
*   Service ID              : 0x04.
*
*   Description             : Service for setting the specific Ppu channel filter time.
*
*   Parameters in           : PpuChannelNumber: Ppu channel number.
*                             FilterTime: filter time of the specific Ppu channel, the unit
*                             of filter time is 10 nanoseconds.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(void, IOM_PUBLIC_CODE) Iom_SetPpuFilterTimeThreshold
(
    Iom_PpuChannelType PpuChannelNumber,
/* #Violation: Iom_c_REF_11*/
    Iom_PpuFilterTimeType FilterTime
)
{

#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Std_ReturnType DetErr;
    Mcal_CoreType CoreId;
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */
    boolean Iom_RegRet;

    Iom_RegRet = TRUE;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETPPUFILTERTIME, 
                              IOM_E_CORE_NOT_CONFIGURED);
        DetErr = E_NOT_OK;
    }
    /* Check IOM initial state */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETPPUFILTERTIME,
                              IOM_E_UNINIT);
        DetErr = E_NOT_OK;
    }
    /* determine whether the threshold exceeds the maximun value or 
    *  dose not match the minimum precision */
/* #Violation: Iom_c_REF_6*/
    else if (IOM_PPU_THRES_MAX < FilterTime)
    {
        /* Report DET IOM_E_PARAM_THRESHOLD for invalid argument */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETPPUFILTERTIME,
                              IOM_E_PARAM_THRESHOLD);
        DetErr = E_NOT_OK;
    }
    /* Check if Ppu channel id greater than IOM_PPU_CHANNEL_MAX */
    else if (IOM_PPU_CHANNEL_MAX < (uint16)PpuChannelNumber)
    {
        /* Report DET IOM_E_PARAM_PPUNO */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID,
                              IOM_SID_SETPPUFILTERTIME, IOM_E_PARAM_PPUNO);
        DetErr = E_NOT_OK;
    }
    else
    {
        /* Check if Ppu channel id is available and if Ppu channel is filter mode */
        DetErr = Iom_IsPpuChannelFilterMode(IOM_SID_SETPPUFILTERTIME, PpuChannelNumber);
    }
    if (E_OK == DetErr)
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
    {
        IOM_ENTER_CRITICAL_SECTION(SetFilterTime);
        /* Set filter time */
        Iom_RegRet = Iom_Hal_SetPpuThreshold(PpuChannelNumber, (uint16)FilterTime);
        IOM_EXIT_CRITICAL_SECTION(SetFilterTime);
#if (STD_ON == IOM_SAFETY_ENABLE)
        if (TRUE != Iom_RegRet)
        {
            (void)Det_ReportRuntimeError(IOM_MODULE_ID, IOM_INSTANCE_ID,
                                         IOM_SID_SETPPUFILTERTIME, IOM_E_WRITE_REGISTER);
        }
#endif /* STD_ON \== IOM_SAFETY_ENABLE */
    }
/* #Violation: Iom_c_REF_5*/
    MCAL_UNUSED_VAR(Iom_RegRet);
}


/****************************************************************************************************
*   Function Name           : Iom_GetPpuFilterTimeThreshold
*
*   Service ID              : 0x05.
*
*   Description             : Service for getting the specific Ppu filter time.
*
*   Parameters in           : PpuChannelNumber: Ppu channel number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Threshold : Ppu filter time, the unit
*                             of filter time is 10 nanoseconds.
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(Iom_PpuFilterTimeType, IOM_PUBLIC_CODE) Iom_GetPpuFilterTimeThreshold
(
    Iom_PpuChannelType PpuChannelNumber
)
{
/* #Violation: Iom_c_REF_11*/
    Iom_PpuFilterTimeType Threshold;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Std_ReturnType DetErr;
    Mcal_CoreType CoreId;
    
    /* DET reported, Invalid value is returned */
    Threshold = IOM_THRESHOLD_FALSE;
    
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETPPUFILTERTIME, 
                              IOM_E_CORE_NOT_CONFIGURED);
        DetErr = E_NOT_OK;
    }
    /* Check IOM init state */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETPPUFILTERTIME,
                              IOM_E_UNINIT);
        DetErr = E_NOT_OK;
    }
    /* Check if Ppu channel id greater than IOM_PPU_CHANNEL_MAX */
    else if (IOM_PPU_CHANNEL_MAX < (uint16)PpuChannelNumber)
    {
        /* Report DET IOM_E_PARAM_PPUNO */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID,
                              IOM_SID_GETPPUFILTERTIME, IOM_E_PARAM_PPUNO);
        DetErr = E_NOT_OK;
    }
    else
    {
        /* Check if Ppu channel id is available and if Ppu channel is filter mode */
        DetErr = Iom_IsPpuChannelFilterMode(IOM_SID_GETPPUFILTERTIME, PpuChannelNumber);
    }
    if (E_OK == DetErr)
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */
    {
        /* Get Ppu counter Threshold */
        Threshold = (Iom_PpuFilterTimeType)Iom_Hal_GetPpuThreshold(PpuChannelNumber);
    }
    return Threshold;
}
#endif /* (IOM_PPU_FILTER_API  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Iom_SetLpuEventWindowTimeThreshold
*
*   Service ID              : 0x06.
*
*   Description             : Service for setting Lpu event window time threshold.
*
*   Parameters in           : LpuChannelNumber : Lpu channel number.
*                             EventWindowTimeThreshold : event window time, the unit
*                             of event window time is 10 nanoseconds.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(void, IOM_PUBLIC_CODE) Iom_SetLpuEventWindowTimeThreshold
(
    Iom_LpuChannelIdType LpuChannelNumber,
    Iom_EventWinTimeThresType EventWindowTimeThreshold
)
{
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Std_ReturnType ReturnValue;
    Mcal_CoreType CoreId;
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */
    boolean Iom_RegRet;

    Iom_RegRet = TRUE;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETLPUEVENTWINTHRESHOLD, 
                              IOM_E_CORE_NOT_CONFIGURED);
    }
    /* Check IOM state */
    else if (IOM_INITIALIZED != Iom_InitStatus) 
    {
        /* Report DET IOM_E_PARAM_LPUNO */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETLPUEVENTWINTHRESHOLD,
                              IOM_E_UNINIT);
    }
    else
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
    {
#if (STD_ON == IOM_DEV_ERROR_DETECT)
        /* Check if Lpu channel id is available */
        ReturnValue = Iom_IsLpuChannelAvailable(LpuChannelNumber);
        /* Lpu channel id is unavailable */
        if (E_NOT_OK == ReturnValue)
        {
            /* Report DET IOM_E_UNINIT */
            (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETLPUEVENTWINTHRESHOLD,
                                  IOM_E_PARAM_LPUNO);
        }
        /* Check LPU threshold value */
/* #Violation: Iom_c_REF_6*/
        else if (IOM_LPU_THRES_MAX < EventWindowTimeThreshold)
        {
            /* Report DET IOM_E_PARAM_THRESHOLD for invalid argument */
            (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_SETLPUEVENTWINTHRESHOLD,
                                  IOM_E_PARAM_THRESHOLD);
        }
        else
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
        {
            IOM_ENTER_CRITICAL_SECTION(SetEventWindow);
            /* Set LPU event window count threshold. */
            Iom_RegRet &= Iom_Hal_SetEventWindowThreshold(LpuChannelNumber, EventWindowTimeThreshold);
            IOM_EXIT_CRITICAL_SECTION(SetEventWindow);
#if (STD_ON == IOM_SAFETY_ENABLE)
            if (TRUE != Iom_RegRet)
            {
                (void)Det_ReportRuntimeError(IOM_MODULE_ID, IOM_INSTANCE_ID,
                                             IOM_SID_SETLPUEVENTWINTHRESHOLD, IOM_E_WRITE_REGISTER);
            }
#endif /* STD_ON \== IOM_SAFETY_ENABLE */
        }
    }
/* #Violation: Iom_c_REF_5*/
    MCAL_UNUSED_VAR(Iom_RegRet);
}

/****************************************************************************************************
*   Function Name           : Iom_GetLpuEventWindowTimeThreshold
*
*   Service ID              : 0x07.
*
*   Description             : Service for getting Lpu event window time.
*
*   Parameters in           : LpuChannelNumber : Lpu channel number
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : ThresVal: Lpu event window time, the unit
*                             of Lpu event window time is 10 nanoseconds.
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(Iom_EventWinTimeThresType, IOM_PUBLIC_CODE) Iom_GetLpuEventWindowTimeThreshold
(
    Iom_LpuChannelIdType LpuChannelNumber
)
{
/* #Violation: Iom_c_REF_11*/
    Iom_EventWinTimeThresType Threshold;

#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Std_ReturnType ReturnValue;
    Mcal_CoreType CoreId;
    
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    /* DET reported, Invalid value is returned */
    Threshold = IOM_THRESHOLD_FALSE;

    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETLPUEVENTWINTHRESHOLD, 
                              IOM_E_CORE_NOT_CONFIGURED);
    }
    /* Check IOM state */
    else if (IOM_INITIALIZED != Iom_InitStatus) 
    {
        /* Report DET IOM_E_PARAM_LPUNO */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETLPUEVENTWINTHRESHOLD,
                              IOM_E_UNINIT);
    }
    /* LPU channel id is unavailable */
    else
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
    {
#if (STD_ON == IOM_DEV_ERROR_DETECT)
        /* Check if Lpu channel id is available */
        ReturnValue = Iom_IsLpuChannelAvailable(LpuChannelNumber);
        if (E_NOT_OK == ReturnValue)
        {
            /* Report DET IOM_E_UNINIT */
            (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETLPUEVENTWINTHRESHOLD,
                                  IOM_E_PARAM_LPUNO);
        }
        else
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
        {
            /* Get Lpu event window count threshold */
            Threshold = Iom_Hal_GetEventWindowThreshold(LpuChannelNumber);
        }
    }
    return Threshold;
}

/****************************************************************************************************
*   Function Name           : Iom_GetLpuChannelTrigHistory
*
*   Service ID              : 0x8.
*
*   Description             : This service supports checking the history of Lpu single channel 
*                             triggering events.
*
*   Parameters in           : LpuChannelNumber: Lpu channel id.
*
*   Parameters inout        : None. 
*   
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Std_ReturnType: Return Lpu channel trigger history.
*                             - E_OK: This channel has a triggering history.
*                             - E_NOT_OK: This channel has no triggering history.
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(Std_ReturnType, IOM_PUBLIC_CODE) Iom_GetLpuChannelTrigHistory
(
    Iom_LpuChannelIdType LpuChannelNumber
)
{
    uint16 EventHistory0;
    uint16 EventHistory1;
    uint16 EventHistory2;
    uint16 EventHistory3;
    Std_ReturnType ReturnValue;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
    ReturnValue = E_NOT_OK;
    
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, 
                              IOM_SID_GETLPUHISTORY, IOM_E_CORE_NOT_CONFIGURED);
    }
    /* Check IOM state */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETLPUHISTORY,
                              IOM_E_UNINIT);
    }
    else
#endif /* IOM_DEV_ERROR_DETECT == STD_ON */ 
    {
#if (STD_ON == IOM_DEV_ERROR_DETECT)
        /* Check if Lpu channel id is available */
        ReturnValue = Iom_IsLpuChannelAvailable(LpuChannelNumber);
        if (E_NOT_OK == ReturnValue)
        {
            /* Report DET IOM_E_PARAM_LPUNO */
            (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETLPUHISTORY,
                                  IOM_E_PARAM_LPUNO);
        }
        else
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
        {
            /* Get all the event trigger history */
            Iom_Hal_GetAllHistory(&EventHistory0, &EventHistory1, &EventHistory2, &EventHistory3);

            /* Get the trigger history of the specified channel */
            EventHistory0 &= (uint16)((uint16)1U << (uint16)LpuChannelNumber);
            EventHistory1 &= (uint16)((uint16)1U << (uint16)LpuChannelNumber);
            EventHistory2 &= (uint16)((uint16)1U << (uint16)LpuChannelNumber);
            EventHistory3 &= (uint16)((uint16)1U << (uint16)LpuChannelNumber);

            /* Determine whether the trigger event is empty */
            if (0U != (EventHistory0 | EventHistory1 | EventHistory2 | EventHistory3))
            {
                /* This channel has a triggering history */
                ReturnValue = E_OK;
            }
            else
            {
                /* This channel has no triggering history */
                ReturnValue = E_NOT_OK;
            }
        }
    }
    return ReturnValue;
}

/****************************************************************************************************
*   Function Name           : Iom_ClrEmuEventTriggerHistory
*
*   Service ID              : 0x9.
*
*   Description             : This service resets the Emu event trigger status history.
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
*   Return value            : None.
*
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(void, IOM_PUBLIC_CODE) Iom_ClrEmuEventTriggerHistory
(
    void
)
{
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();

    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, 
                              IOM_SID_CLRLPUHISTORY, IOM_E_CORE_NOT_CONFIGURED);
    }
    /* Check IOM state */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_CLRLPUHISTORY,
                              IOM_E_UNINIT);
    }
    else
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
    {
        /* Clear all the event trigger history */
        Iom_Hal_ClearAllHistory();
    }
}

/****************************************************************************************************
*   Function Name           : Iom_EnableEmuCounter
*
*   Service ID              : 0x10.
*
*   Description             : This service enable alarm output.
*
*   Parameters in           : None.
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
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(void, IOM_PUBLIC_CODE) Iom_EnableEmuCounter
(
    void
)
{
    uint8 ChannelNumber;
    boolean Iom_RegRet;

#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */

    Iom_RegRet = TRUE;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, 
                              IOM_SID_ENABLEEMUCOUNTER, IOM_E_CORE_NOT_CONFIGURED);
    }
    /* Check IOM Status */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_ENABLEEMUCOUNTER,
                              IOM_E_UNINIT);
    }
    else
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
    {
        IOM_ENTER_CRITICAL_SECTION(EnableEMUCounter);
        /* Enable Counter channel event selection function. */
        Iom_RegRet = Iom_Hal_SetEmuGlobalEventSel(Iom_ConfigPtr->Iom_EmuSelection);
/* #Violation: Iom_c_REF_4*/
        for (ChannelNumber = 0U; ChannelNumber < IOM_CHANNEL_USED_NUMBER; ChannelNumber++)
        {
            if (IOM_EMUCONFIG_MAX_INDEX != (uint32)Iom_ConfigPtr->Iom_EmuCombinerPtr[ChannelNumber].EmuCounterIndex)
            {
                Iom_RegRet &= Iom_Hal_SetCombiner((Iom_EventCounterChannelType)Iom_ConfigPtr->\
                                    Iom_EmuCombinerPtr[ChannelNumber].EmuCounterIndex, 
                                    Iom_ConfigPtr->Iom_EmuCombinerPtr[ChannelNumber].Channel,
                                    Iom_ConfigPtr->Iom_EmuCombinerPtr[ChannelNumber].Iom_EmuCounterThreshold);
            }
        }
        IOM_EXIT_CRITICAL_SECTION(EnableEMUCounter);
    }
#if (STD_ON == IOM_SAFETY_ENABLE)
    if (TRUE != Iom_RegRet)
    {
        (void)Det_ReportRuntimeError(IOM_MODULE_ID, IOM_INSTANCE_ID, \
                                        IOM_SID_ENABLEEMUCOUNTER, IOM_E_WRITE_REGISTER);
    }
#endif /* STD_ON \== IOM_SAFETY_ENABLE */
/* #Violation: Iom_c_REF_5*/
    MCAL_UNUSED_VAR(Iom_RegRet);
}

/****************************************************************************************************
*   Function Name           : Iom_DisableEmuCounter
*
*   Service ID              : 0x11.
*
*   Description             : This service disable alarm output.
*
*   Parameters in           : None.
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
*   Preconditions           : None
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(void, IOM_PUBLIC_CODE) Iom_DisableEmuCounter
(
    void
)
{
    boolean Iom_RegRet;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;
    /* Get core id which is executing currently */
/* #Violation: Iom_c_REF_5*/
    CoreId = Mcal_GetCoreId();
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */

    Iom_RegRet = TRUE;
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    /* Check if the current core id is correct */
    if (IOM_CORE_ALLOCATION != (uint32)CoreId)
    {
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_DISBLEEMUCOUNTER, IOM_E_CORE_NOT_CONFIGURED);
    }
    /* Check IOM Status */
    else if (IOM_INITIALIZED != Iom_InitStatus)
    {
        /* Report DET IOM_E_UNINIT */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_DISBLEEMUCOUNTER,
                              IOM_E_UNINIT);
    }
    else
#endif /* IOM_DEV_ERROR_DETECT \== STD_ON */
    {
        /* Disable Counter channel event selection function. */
        Iom_RegRet &= Iom_Hal_SetEmuGlobalEventSel(0U);
#if (STD_ON == IOM_SAFETY_ENABLE)
        if (TRUE != Iom_RegRet)
        {
            (void)Det_ReportRuntimeError(IOM_MODULE_ID, IOM_INSTANCE_ID, \
                                        IOM_SID_DISBLEEMUCOUNTER, IOM_E_WRITE_REGISTER);
        }
#endif /* STD_ON \== IOM_SAFETY_ENABLE */
    }
/* #Violation: Iom_c_REF_5*/
    MCAL_UNUSED_VAR(Iom_RegRet);
}

#if (STD_ON == IOM_VERSION_INFO_API)
/****************************************************************************************************
*   Function Name           : Iom_GetVersionInfo
*
*   Service ID              : 0x12.
*
*   Description             : returns the version information of this module
*                             The version information include:Module ID, Vendor ID,
*                             Vendor specific version numbers.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : VersionInfoPtr : Pointer to store the version
*                                           information of this module.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : IOM_VERSION_INFO_API = STD_ON
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Iom_c_REF_8*/
FUNC(void, IOM_PUBLIC_CODE) Iom_GetVersionInfo
(
/* #Violation: Iom_c_REF_9*/
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, IOM_APPL_DATA) VersionInfoPtr
)
{
#if (STD_ON == IOM_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        /* Report IOM_E_PARAM_POINTER DET */
        (void)Det_ReportError(IOM_MODULE_ID, IOM_INSTANCE_ID, IOM_SID_GETVERINFO,
                              IOM_E_PARAM_INVALID);
    }
    else
#endif /* (STD_ON \== IOM_DEV_ERROR_DETECT) */
    {
        VersionInfoPtr->vendorID         = IOM_VENDOR_ID;
        VersionInfoPtr->moduleID         = IOM_MODULE_ID;
        VersionInfoPtr->sw_major_version = IOM_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = IOM_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = IOM_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON \== IOM_VERSION_INFO_API) */

/* #Violation: Iom_c_REF_2*/
#define IOM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Iom_c_REF_3*/
#include "Iom_MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
