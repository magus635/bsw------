/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Port.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GPIO
 *
 *   brief                 : This file contains all functions of Port Driver
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
*#Port_c_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Port_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Port_c_REF_3:CertC-DCL00-C; 
* Justification: Parameter declared refer to AUTOSAR specifications.

*#Port_c_REF_4:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Port_Cfg.h"
#include "Port_TLLD.h"
#include "Port_Version.h"
#include "Port_GeneralTypes.h"
/*  SWS_Port_00131:
    Port.c shall include Port.h, Port_MemMap.h, Det.h, SchM_Port.h.
    SWS_Port_00204:
    Port.c  shall optionally include Port_Cbk.h and Dem.h.
    Port.c has implicit access to the Port_Cfg.h file through the Port.h file.
*/
#include "Port.h"
#include "SchM_Port.h"
#if ((PORT_DEV_ERROR_DETECT == STD_ON) || (PORT_SAFETY_ENABLE == STD_ON))
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif /* ((PORT_DEV_ERROR_DETECT \== STD_ON) || (PORT_SAFETY_ENABLE \== STD_ON)) */
/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (PORT_VENDOR_ID != PORT_CFG_VENDOR_ID)
  #error "Port.c : Mismatch in Vendor ID"
#endif /* (PORT_VENDOR_ID \!= PORT_CFG_VENDOR_ID) */

#if (PORT_MODULE_ID != PORT_CFG_MODULE_ID)
  #error "Port.c : Mismatch in Module ID"
#endif /* \(PORT_MODULE_ID != PORT_CFG_MODULE_ID) */

#if (PORT_AR_RELEASE_MAJOR_VERSION != PORT_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Port.c : Mismatch in Release Major Version"
#endif /* (PORT_AR_RELEASE_MAJOR_VERSION \!= PORT_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (PORT_AR_RELEASE_MINOR_VERSION != PORT_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Port.c : Mismatch in Release Minor Version"
#endif /* (PORT_AR_RELEASE_MINOR_VERSION \!= PORT_CFG_AR_RELEASE_MINOR_VERSION) */

#if (PORT_AR_RELEASE_REVISION_VERSION != PORT_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Port.c : Mismatch in Release Revision Version"
#endif /* (PORT_AR_RELEASE_REVISION_VERSION \!= PORT_CFG_AR_RELEASE_REVISION_VERSION) */

#if (PORT_SW_MAJOR_VERSION != PORT_CFG_SW_MAJOR_VERSION)
  #error "Port.c : Mismatch in Software Major Version"
#endif /* (PORT_SW_MAJOR_VERSION \!= PORT_CFG_SW_MAJOR_VERSION) */

#if (PORT_SW_MINOR_VERSION != PORT_CFG_SW_MINOR_VERSION)
  #error "Port.c : Mismatch in Software Minor Version"
#endif /* (PORT_SW_MINOR_VERSION \!= PORT_CFG_SW_MINOR_VERSION) */

#if (PORT_SW_PATCH_VERSION != PORT_CFG_SW_PATCH_VERSION)
  #error "Port.c : Mismatch in Software Patch Version"
#endif /* \(PORT_SW_PATCH_VERSION != PORT_CFG_SW_PATCH_VERSION) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Mask: Take the lower four bits */
#define PORT_LOW4BIT_MASK                                (0x0FU)
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* #Violation: Port_c_REF_1 */
#define PORT_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Port_c_REF_2 */
#include "Port_MemMap.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
static Port_DriverStateType Port_InitStatus;
#endif /* (PORT_DEV_ERROR_DETECT  \== STD_ON) */

static P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) Port_ConfigPtr;

/* #Violation: Port_c_REF_1 */
#define PORT_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Port_c_REF_2 */
#include "Port_MemMap.h"
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
/* #Violation: Port_c_REF_1 */
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Port_c_REF_2 */
#include "Port_MemMap.h"

#if ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API == STD_ON))
static FUNC(boolean, PORT_PRIVATE_CODE) Port_IsPinAvailable
(
    uint8 PortNumber,
    uint8 PinNumber
);
#endif /* ((PORT_SET_PIN_DIRECTION_API \== STD_ON) || (PORT_SET_PIN_MODE_API \== STD_ON)) */

#if (PORT_SET_PIN_MODE_API == STD_ON)
static FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_CheckPinMode
(
    uint8 PinCTRCfg,
    uint8 PortNumber,
    uint8 PinNumber,
    Port_PinModeType Mode
);
#endif /* (PORT_SET_PIN_MODE_API \== STD_ON) */

/* #Violation: Port_c_REF_1 */
#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Port_c_REF_2 */
#include "Port_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Port_c_REF_1 */
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Port_c_REF_2 */
#include "Port_MemMap.h"

#if ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API == STD_ON))
/****************************************************************************************************
*   Function Name           : Port_IsPinAvailable
*
*   Service ID              : None.
*
*   Description             : This function shall check if the pin is available or not.
*
*   Parameters in           : Port: Port to be check.
*                             Pin: Pin to be check.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : TRUE: Pin is available.
*                             FALSE: Pin is unavailable.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, PORT_PRIVATE_CODE) Port_IsPinAvailable
(
    uint8 PortNumber,
    uint8 PinNumber
)
{
    boolean     RetVal;
    uint8       PortIndex;
    uint16      PortAvailable;

    /* Initialization function return value */
    RetVal = FALSE;
    /* Check whether the Port ID exceeds the maximum value of the chip */
    if(PORT_MAX_NUMBER > PortNumber)
    {
        /* Get the Port index of the real Port Number */
        PortIndex = Port_ConfigPtr->AvailablePortIndexPtr[PortNumber];
        /* Is the index corresponding to the port group valid */
        if(((uint8)PORT_NULL_MASK) != PortIndex)
        {
            /* Check whether the Pin is valid according to the Port group mask */
            PortAvailable = Port_ConfigPtr->AvailablePinsPtr[PortIndex] &
                                ((uint16)1U << (PinNumber & PORT_LOW4BIT_MASK));
            /* Check if the Port-Pin is valid */
            if(0U != PortAvailable)
            {
                /* Set the return value of the Port-Pin check */
                RetVal = TRUE;
            }
        }
    }

    return RetVal;
}
#endif /* ((PORT_SET_PIN_DIRECTION_API == STD_ON) || (PORT_SET_PIN_MODE_API \== STD_ON)) */

#if (PORT_SET_PIN_MODE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Port_CheckPinMode
*
*   Service ID              : None.
*
*   Description             : This function shall check pin Mode.
*
*   Parameters in           : PinCTRCfg:  CTR Register value.
*   Parameters in           : PortNumber: ID of Port.
*                             PinNumber:  ID of Pin.
*                             Mode:       Port pin mode to be set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK      : No error in the pin mode set.
*                             E_NOT_OK  : Error in the pin mode set.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_CheckPinMode
(
    uint8 PinCTRCfg,
    uint8 PortNumber,
    uint8 PinNumber,
    Port_PinModeType Mode
)
{
    Std_ReturnType  RetStatus;

    /* Check that the current Port-Pin is output and supports the current ALT mode */
    if (((uint8)PORT_PIN_OUT == (PinCTRCfg & ((uint8)PORT_REG_DIR_MASK))) &&
        (PORT_AVAILABEL_TOTAL_NUMBER > PortNumber) &&
        (0U != (Port_ConfigPtr->HwSupportedModesPtr[PortNumber].PortPin[PinNumber &
            PORT_LOW4BIT_MASK] & (1UL << (Mode & PORT_LOW4BIT_MASK)))))
    {
            RetStatus = E_OK;
    }
    /* Check if the current Port-Pin is input and the setting mode is GPIO */
    else if (((uint8)PORT_PIN_IN == (PinCTRCfg & ((uint8)PORT_REG_DIR_MASK))) &&
             ((uint8)PORT_OUTPUTALT_O0 == Mode))
    {
         RetStatus = E_OK;
    }
    else
    {
        RetStatus = E_NOT_OK;
    }

    return RetStatus;
}
#endif /* (PORT_SET_PIN_MODE_API \== STD_ON) */

/* #Violation: Port_c_REF_1 */
#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Port_c_REF_2 */
#include "Port_MemMap.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Port_c_REF_1 */
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Port_c_REF_2 */
#include "Port_MemMap.h"

/****************************************************************************************************
*   Function Name           : Port_Init
*
*   Service ID              : 0x00
*
*   Description             : This function shall initializes the Port Driver module.
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
*   Preconditions           : Port driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Port_00140 SWS_Port_00041 SWS_Port_00078 SWS_Port_00213
                              SWS_Port_00042 SWS_Port_00043 SWS_Port_00071 SWS_Port_00002
                              SWS_Port_00003 SWS_Port_00121
****************************************************************************************************/
/* #Violation: Port_c_REF_4 */
FUNC(void, PORT_PUBLIC_CODE) Port_Init
(
    /* #Violation: Port_c_REF_3 */
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr
)
{
#if ((PORT_DEV_ERROR_DETECT == STD_ON) || (PORT_SAFETY_ENABLE == STD_ON))
    boolean     RetStatus;
#endif /* ((PORT_DEV_ERROR_DETECT \== STD_ON) || (PORT_SAFETY_ENABLE \== STD_ON)) */

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == ConfigPtr)
    {
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_INIT, PORT_E_INIT_FAILED);
    }
    else
#endif /* (PORT_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Update global configuration pointer */
        Port_ConfigPtr = ConfigPtr;
#if ((PORT_DEV_ERROR_DETECT == STD_ON) || (PORT_SAFETY_ENABLE == STD_ON))
        /* Call the hardware initialization function */
        RetStatus = Port_TLLD_Init(Port_ConfigPtr);
#else
        (void)Port_TLLD_Init(Port_ConfigPtr);
#endif /* ((PORT_DEV_ERROR_DETECT \== STD_ON) || (PORT_SAFETY_ENABLE \== STD_ON)) */
        
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        if(TRUE == RetStatus)
        {
            /* Set Status to indicate that initialization is done */
            Port_InitStatus = PORT_INITIALIZED;
        }
#endif /* (PORT_DEV_ERROR_DETECT  \== STD_ON) */
#if (PORT_SAFETY_ENABLE == STD_ON)
        if(FALSE == RetStatus)
        {
            (void)Det_ReportRuntimeError(
                    PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_INIT, PORT_E_SAFETY_ERROR);
        }
#endif /* (PORT_SAFETY_ENABLE  \== STD_ON) */
    }
}


#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Port_SetPinDirection
*
*   Service ID              : 0x01
*
*   Description             : This function shall set the port pin direction.
*
*   Parameters in           : Pin: Port Pin ID number.
*                             Direction: Port Pin Direction.
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
*   Preconditions           : Port driver must be initialized.
*
*   AUTOSAR_Requirement     : SWS_Port_00141 SWS_Port_00063 SWS_Port_00054
****************************************************************************************************/
/* #Violation: Port_c_REF_4 */
FUNC(void, PORT_PUBLIC_CODE) Port_SetPinDirection
(
    Port_PinType Pin,
    Port_PinDirectionType Direction
)
{
    uint8               PortNumber;
    uint8               PinNumber;
    uint8               PinCTRCfg;
    Std_ReturnType      LockStatus;
    boolean             RetStatus;

    /* Get the Port ID from the Pin Symbolic ID */
    PortNumber = (uint8)((Pin >> 0x04U) & 0xFFU);
    /* Get the Pin ID from the Pin Symbolic ID */
    PinNumber  = (uint8)(Pin & 0x0FUL);

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Determine whether it has been initialized */
    if (PORT_UNINITIALIZED == Port_InitStatus)
    {
        RetStatus = FALSE;
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SETPINDIRECTION,
                              PORT_E_UNINIT);
    }
    else
    {
        /* Check if Port and Pin is valid */
        RetStatus = Port_IsPinAvailable(PortNumber, PinNumber);
        /* Determine the validity of the Pin */
        if (FALSE == RetStatus)
        {
            (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SETPINDIRECTION,
                                    PORT_E_PARAM_PIN);
        }
        /* Determine if the direction can be changed */
        else if ((uint8)PORT_PIN_DIR_NOT_CHANGEABLE == (Port_ConfigPtr->DirChangeCtrlPtr
            [Port_ConfigPtr->AvailablePortIndexPtr[PortNumber]].U & (1UL << PinNumber)))
        {
            RetStatus = FALSE;
            (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SETPINDIRECTION,
                                    PORT_E_DIRECTION_UNCHANGEABLE);
        }
        /*  SWS_Port_00137:
            For the port pins configured as changeable using the configuration tool, the PORT driver
            shall allow the user to change the direction of port pins during runtime.
            SWS_Port_00138:
            If the MCU port control hardware provides an output latch for setting the output level on
            a port pin, switching the port pin direction shall not alter the level set in this output latch.
        */
        else
        {
            RetStatus = TRUE;
        }
    }
    if(TRUE == RetStatus)
#endif /* (PORT_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Enter critical protection to avoid being interrupted by the current Core. */
        PORT_ENTER_CRITICAL_SECTION(SetPinDirection);
        /* Get the software lock to avoid operating this register with other Core colleagues */
        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_PORT);
        /* Spin lock acquired successfully */
        if(E_OK == LockStatus)
        {
            /* Get the CTR register control value of the corresponding Pin (uint8) */
            PinCTRCfg = Port_TLLD_GetPinCTRCfg(PortNumber, PinNumber, Port_ConfigPtr);
            /* Check whether the current pin direction is consistent with the expected */
            if((((uint8)PORT_REG_DIR_MASK) & PinCTRCfg) != (uint8)Direction)
            {
                RetStatus = Port_TLLD_SetPinDirection(PortNumber, PinNumber, Direction, Port_ConfigPtr);
            }
            else
            {
                RetStatus = TRUE;
            }
            /* Release the software lock to avoid other cores operating this register */
            Mcal_ReleaseLock(MCAL_LOCK_ID_PORT);
        }
        else
        {
            RetStatus = FALSE;
        }
        /* Exit critical protection to avoid affecting the current Core interrupt trigger */
        PORT_EXIT_CRITICAL_SECTION(SetPinDirection);

#if (PORT_SAFETY_ENABLE == STD_ON)
        if(FALSE == RetStatus)
        {
            (void)Det_ReportRuntimeError(
                PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SETPINDIRECTION, PORT_E_SAFETY_ERROR);
        }
#endif /* (PORT_SAFETY_ENABLE  \== STD_ON) */

#if ((PORT_SAFETY_ENABLE == STD_OFF) && (PORT_SAFETY_ENABLE == STD_OFF))
        MCAL_UNUSED_VAR(RetStatus);
#endif /* (PORT_SAFETY_ENABLE \== STD_OFF) && (PORT_SAFETY_ENABLE \== STD_OFF) */
    }
}

/****************************************************************************************************
*   Function Name           : Port_RefreshPortDirection
*
*   Service ID              : 0x02
*
*   Description             : This function shall refreshes port direction.
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
*   Preconditions           : Port driver must be initialized.
*
*   AUTOSAR_Requirement     : SWS_Port_00142 SWS_Port_00060
****************************************************************************************************/
/* #Violation: Port_c_REF_4 */
FUNC(void, PORT_PUBLIC_CODE) Port_RefreshPortDirection
(
    void
)
{
    boolean             RetStatus;
    boolean             CheckResult;
    uint8               PortNumber;
    uint8               PinNumber;
    uint8               PortIndex;
    uint8               PinCfgData;
    Std_ReturnType      LockStatus;

    /* Initialization function return value */
    RetStatus = TRUE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Determine whether it has been initialized */
    if (PORT_UNINITIALIZED == Port_InitStatus)
    {
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_REFRESHPORTDIR,
                              PORT_E_UNINIT);
    }
    else
#endif /* (PORT_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Loop Port to Maximum Port ID */
        for (PortNumber = 0U; ((TRUE == RetStatus) && (PortNumber < PORT_MAX_NUMBER)); PortNumber++)
        {
            /* Get the Port index of the real Port Number */
            PortIndex = Port_ConfigPtr->AvailablePortIndexPtr[PortNumber];
            /* Check PortIndex is available */
            if (((uint8)PORT_NULL_MASK) != PortIndex)
            {
                /* Loop Pin to Maximum Pin ID */
                for (PinNumber = 0U;
                    ((TRUE == RetStatus) && (PinNumber < PIN_MAX_NUMBER)); PinNumber++)
                {
                    /* Check if the Pin is available, Cannot use 'RetStatus' to store results */
                    CheckResult = Port_IsPinAvailable(PortNumber, PinNumber);
                    /* Check if the Pin is available */
                    if (TRUE == CheckResult)
                    {
                        /* Get Pinx's CTR control register configuration value (uint8) */
                        PinCfgData = Port_ConfigPtr->CTRxCfgPtr[PortIndex].B.PC[PinNumber];
                        /*  SWS_Port_00066:
                            For refreshing of the port on the microcontroller, the PORT driver shall
                            allow the user to refresh the direction of those port pins whose
                            direction is set by configuration and cannot be changed dynamically.
                            SWS_Port_00061:
                            The function Port_RefreshPortDirection shall exclude those port pins from
                            refreshing that are configured as pin direction changeable during runtime.
                        */
                        /* Port-Pin direction Not Changeable && Pin mode is PORT_OUTPUTALT_O0 (GPIO) */
                        if(((uint32)PORT_PIN_DIR_NOT_CHANGEABLE == (Port_ConfigPtr->DirChangeCtrlPtr
                            [PortIndex].U & (1UL << PinNumber))) &&
                            ((uint8)PORT_OUTPUTALT_O0 == (PinCfgData & ((uint8)PORT_REG_MODE_MASK))))
                        {
                            /* Enter critical protection to avoid
                                being interrupted by the current Core. */
                            PORT_ENTER_CRITICAL_SECTION(RefreshPortDirection);
                            /* Get the software lock to avoid
                                operating this register with other Core colleagues */
                            LockStatus = Mcal_GetLock(MCAL_LOCK_ID_PORT);
                            /* Spin lock acquired successfully */
                            if(E_OK == LockStatus)
                            {
                                /* Refresh Port-Pin to initialization state */
                                RetStatus = Port_TLLD_RefreshPortDirection(
                                        PortNumber, PinNumber, PinCfgData, Port_ConfigPtr);
                                /* Release the software lock to avoid
                                    other cores operating this register */
                                Mcal_ReleaseLock(MCAL_LOCK_ID_PORT);
                            }
                            else
                            {
                                RetStatus = FALSE;
                            }
                            /* Exit critical protection to avoid
                                affecting the current Core interrupt trigger */
                            PORT_EXIT_CRITICAL_SECTION(RefreshPortDirection);
                        }
#if (PORT_SAFETY_ENABLE == STD_ON)
                        if(FALSE == RetStatus)
                        {
                            (void)Det_ReportRuntimeError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                                                    PORT_SID_REFRESHPORTDIR, PORT_E_SAFETY_ERROR);
                        }
#endif /* (PORT_SAFETY_ENABLE  \== STD_ON) */
                    }
                }
            }
        }
    }
}
#endif /* (PORT_SET_PIN_DIRECTION_API  \== STD_ON) */

#if  (PORT_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Port_GetVersionInfo
*
*   Service ID              : 0x03
*
*   Description             : This function shall returns the version information of this module.
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
*   AUTOSAR_Requirement     : SWS_Port_00143
****************************************************************************************************/
/* #Violation: Port_c_REF_4 */
FUNC(void, PORT_PUBLIC_CODE) Port_GetVersionInfo
(
    /* #Violation: Port_c_REF_3 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) VersionInfoPtr
)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /*  SWS_Port_00225
        If Det is enabled, the parameter versioninfo shall bechecked for being NULL. The error
        PORT_E_PARAM_POINTER shall be reported in case the value is a NULL pointer.
    */
    /* Check whether the incoming parameter is a null pointer */
    if (NULL_PTR == VersionInfoPtr)
    {
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_GETVERSIONINFO,
                              PORT_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON \== PORT_DEV_ERROR_DETECT) */
    {
        /* Read version information into the structure pointer(VersionInfoPtr) */
        (VersionInfoPtr)->vendorID         = (uint16)PORT_VENDOR_ID;
        (VersionInfoPtr)->moduleID         = (uint16)PORT_MODULE_ID;
        (VersionInfoPtr)->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        (VersionInfoPtr)->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        (VersionInfoPtr)->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON \== PORT_VERSION_INFO_API) */

#if (PORT_SET_PIN_MODE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Port_SetPinMode
*
*   Service ID              : 0x04
*
*   Description             : This function shall set the Port-Pin ALT mode.
*
*   Parameters in           : Pin: Port Pin ID number.
*                             Mode: Alternative of pin mode
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
*   AUTOSAR_Requirement     : SWS_Port_00212 SWS_Port_00145 SWS_Port_00125 SWS_Port_00128
****************************************************************************************************/
/* #Violation: Port_c_REF_4 */
FUNC(void, PORT_PUBLIC_CODE) Port_SetPinMode
(
    Port_PinType Pin,
    Port_PinModeType Mode
)
{
    uint8               PortNumber;
    uint8               PinNumber;
    uint8               PinCTRCfg;
    Std_ReturnType      CheckResult;
    Std_ReturnType      LockStatus;
    uint8               PortIndex;
    boolean             RetStatus;

    /* Get the Port ID from the Pin Symbolic ID */
    PortNumber = (uint8)((Pin >> 0x04U) & 0xFFU);
    /* Get the Pin ID from the Pin Symbolic ID */
    PinNumber  = (uint8)(Pin & 0x0FUL);

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Determine whether it has been initialized */
    if (PORT_UNINITIALIZED == Port_InitStatus)
    {
        RetStatus = FALSE;
        (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SETPINMODE, PORT_E_UNINIT);
    }
    else
    {
        /* Check if the Pin is available */
        RetStatus = Port_IsPinAvailable(PortNumber, PinNumber);
        /* Determine the validity of the Pin */
        if (FALSE == RetStatus)
        {
            (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SETPINMODE,
                                    PORT_E_PARAM_PIN);
        }
        else
        {
            /* Get the Port index of the real Port Number */
            PortIndex = Port_ConfigPtr->AvailablePortIndexPtr[PortNumber];
            /*  SWS_Port_00223:
                If Det is enabled, the function Port_SetPinMode shall report PORT_E_MODE_UNCHANGEABLE
                error and return without any other action, if the parameter PortPinModeChangeable is
                set to FALSE.
            */
            if ((uint32)PORT_PIN_ALT_NOT_CHANGEABLE ==
                ((Port_ConfigPtr->ModeChangeCtrlPtr[PortIndex].U) & (1UL << PinNumber)))
            {
                RetStatus  = FALSE;
                (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SETPINMODE,
                                        PORT_E_MODE_UNCHANGEABLE);
            }
            else
            {
                RetStatus  = TRUE;
            }
        }
    }
    if(TRUE == RetStatus)
#endif /* (PORT_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Reset mode check value to avoid abnormal DET reporting after lock acquisition failure. */
        CheckResult = E_OK;
        /* Enter critical protection to avoid being interrupted by the current Core. */
        PORT_ENTER_CRITICAL_SECTION(SetPinMode);
        /* Get the software lock to avoid operating this register with other Core colleagues */
        LockStatus = Mcal_GetLock(MCAL_LOCK_ID_PORT);
        /* Spin lock acquired successfully */
        if(E_OK == LockStatus)
        {
            /* Get Pinx's CTR control register configuration value (uint8) */
            PinCTRCfg = Port_TLLD_GetPinCTRCfg(PortNumber, PinNumber, Port_ConfigPtr);
            /* Get the Port index of the real Port Number */
            PortIndex = Port_ConfigPtr->AvailablePortIndexPtr[PortNumber];
            /* Check whether the Port-Pin hardware supports the current mode */
            CheckResult = Port_CheckPinMode(PinCTRCfg, PortIndex, PinNumber, Mode);
            /* Check whether the current reuse function is consistent with the expected */
            if((E_OK == CheckResult) &&
               ((((uint8)PORT_REG_MODE_MASK) & PinCTRCfg) != Mode))
            {
                /* Set ALT mode of the current Port-Pin */
                RetStatus = Port_TLLD_SetPinMode(PortNumber, PinNumber, Mode, Port_ConfigPtr);
            }
            else
            {
                RetStatus = TRUE;
            }
            /* Release the software lock to avoid affecting other cores operating this register */
            Mcal_ReleaseLock(MCAL_LOCK_ID_PORT);
        }
        else
        {
            RetStatus = FALSE;
        }
        /* Exit critical protection to avoid affecting the current Core interrupt trigger */
        PORT_EXIT_CRITICAL_SECTION(SetPinMode);

#if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* Check whether the hardware supports the alternate */
        if (E_NOT_OK == CheckResult)
        {
            (void)Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                                    PORT_SID_SETPINMODE, PORT_E_PARAM_INVALID_MODE);
        }
#endif /* (PORT_DEV_ERROR_DETECT  \== STD_ON) */

#if (PORT_SAFETY_ENABLE == STD_ON)
       if(FALSE == RetStatus)
        {
            (void)Det_ReportRuntimeError(
                PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SID_SETPINMODE, PORT_E_SAFETY_ERROR);
        }
#endif /* (PORT_SAFETY_ENABLE  \== STD_ON) */

#if ((PORT_SAFETY_ENABLE == STD_OFF) && (PORT_SAFETY_ENABLE == STD_OFF))
        MCAL_UNUSED_VAR(RetStatus);
#endif /* (PORT_SAFETY_ENABLE \== STD_OFF) && (PORT_SAFETY_ENABLE \== STD_OFF) */
    }
}

#endif /* (PORT_SET_PIN_MODE_API  \== STD_ON) */

/* #Violation: Port_c_REF_1 */
#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Port_c_REF_2 */
#include "Port_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

