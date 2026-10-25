/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all functions of Dio Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright /(c)
*   All Rights Reserved.
*
****************************************************************************************************/


/*
*#Violation Summary
*#Dio_c_REF_1:MISRAC2012-Rule-20.7;
* Justification:Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Dio_c_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Dio_c_REF_3:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*#Dio_c_REF_4:CertC-DCL00-C; 
* Justification:Parameter declared refer to AUTOSAR specifications.
*
*#Dio_c_REF_5:CertC-PRE00-C; 
* Justification:Function like macros are used to reduce code complexity.
*
*#Dio_c_REF_6:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dio.h"
#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
#include "Dio_Cfg.h"
#include "Dio_TLLD.h"
#include "Dio_GeneralTypes.h"
#include "Dio_Version.h"
/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (DIO_VENDOR_ID != DIO_CFG_VENDOR_ID)
  #error "Dio.c : Mismatch in Vendor ID"
#endif /* (DIO_VENDOR_ID \!= DIO_CFG_VENDOR_ID) */

#if (DIO_MODULE_ID != DIO_CFG_MODULE_ID)
  #error "Dio.c : Mismatch in Module ID"
#endif /* (DIO_MODULE_ID \!= DIO_CFG_MODULE_ID) */

#if (DIO_AR_RELEASE_MAJOR_VERSION != DIO_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Dio.c : Mismatch in Release Major Version"
#endif /* (DIO_AR_RELEASE_MAJOR_VERSION \!= DIO_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (DIO_AR_RELEASE_MINOR_VERSION != DIO_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Dio.c : Mismatch in Release Minor Version"
#endif /* (DIO_AR_RELEASE_MINOR_VERSION \!= DIO_CFG_AR_RELEASE_MINOR_VERSION) */

#if (DIO_AR_RELEASE_REVISION_VERSION != DIO_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Dio.c : Mismatch in Release Revision Version"
#endif /* (DIO_AR_RELEASE_REVISION_VERSION \!= DIO_CFG_AR_RELEASE_REVISION_VERSION) */

#if (DIO_SW_MAJOR_VERSION != DIO_CFG_SW_MAJOR_VERSION)
  #error "Dio.c : Mismatch in Software Major Version"
#endif /* (DIO_SW_MAJOR_VERSION \!= DIO_CFG_SW_MAJOR_VERSION) */

#if (DIO_SW_MINOR_VERSION != DIO_CFG_SW_MINOR_VERSION)
  #error "Dio.c : Mismatch in Software Minor Version"
#endif /* (DIO_SW_MINOR_VERSION \!= DIO_CFG_SW_MINOR_VERSION) */

#if (DIO_SW_PATCH_VERSION != DIO_CFG_SW_PATCH_VERSION)
  #error "Dio.c : Mismatch in Software Patch Version"
#endif /* (DIO_SW_PATCH_VERSION \!= DIO_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define DIO_PORTS_READ_ONLY_MASK            (0x20U)
/* offset value where the port number is present */
#define DIO_GROUP_OFFSET0                   (0x00U)
/* offset value where the port number is present */
#define DIO_PORTNUMBER_OFFSET               (0x04U)
/* lower 4-bit mask value in hex to get the pin number of a port */
#define DIO_CHANNEL_LOW4_MASK               (0x0FU)
/* lower 8-bit mask value in hex to get the port number */
#define DIO_CHANNEL_LOW8_MASK               (0xFFU)
/* #Violation: Dio_c_REF_5 */
#define GET_DIOPORTNUMBER(DioChannelId)\
                (Dio_PortType)(((DioChannelId) >> DIO_PORTNUMBER_OFFSET) & DIO_CHANNEL_LOW8_MASK)
/* #Violation: Dio_c_REF_5 */
#define GET_DIOPINNUMBER(DioChannelId)     (uint8)((DioChannelId) & DIO_CHANNEL_LOW4_MASK)
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

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
/* #Violation: Dio_c_REF_3 */
#define DIO_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dio_MemMap.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, DIO_PRIVATE_CODE) Dio_ChannelIdCheck
(
    Dio_ChannelType ChannelId,
    Dio_PortType PortNumber,
    uint8 PinNumber
);

static FUNC(Std_ReturnType, DIO_PRIVATE_CODE) Dio_PortIdCheck
(
    Dio_PortType PortId
);

static FUNC(Std_ReturnType, DIO_PRIVATE_CODE) Dio_GroupIdCheck
(
    CONSTP2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_DATA) ChannelGroupIdPtr
);

static FUNC(boolean, DIO_PRIVATE_CODE) Dio_ReadOnlyPortCheck
(
    Dio_PortType PortNumber
);
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
/* #Violation: Dio_c_REF_3 */
#define DIO_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dio_c_REF_2 */
#include "Dio_MemMap.h"

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Dio_c_REF_3 */
#define DIO_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dio_c_REF_2 */
#include "Dio_MemMap.h"


#if (DIO_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Dio_ChannelIdCheck
*
*   Service ID              : None.
*
*   Description             : This function shall check if the ChannelId is available or not.
*
*   Parameters in           : ChannelId: ID of DIO channel.
*                             PortNumber:  Port number of DIO channel.
*                             PinNumber: Pin number of DIO channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: The ChannelId is available.
*                             E_NOT_OK: The ChannelId is not available.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, DIO_PRIVATE_CODE) Dio_ChannelIdCheck
(
    Dio_ChannelType ChannelId,
    Dio_PortType PortNumber,
    uint8 PinNumber
)
{
    uint8       PortIndex;
    Std_ReturnType ErrorStatus;

    ErrorStatus = E_NOT_OK;

    if(ChannelId <= (Dio_ChannelType)DIO_MAX_AVAILABEL_PORT_PIN_ID)
    {
        PortIndex = Dio_ConfigSet.Dio_AvailablePortIndexPtr[PortNumber];
        if((DIO_INVALID_PORT_INDEX != PortIndex) && (DIO_PORT_CONFIGURED ==
           (Dio_Port_ConfigType)Dio_ConfigSet.Dio_ChCfgDataPtr[PortIndex].Dio_PortConfig))
        {
            if(((Dio_ConfigSet.Dio_ChCfgDataPtr[PortIndex].Dio_ChannelConfig) &
                 ((uint16)(1UL << PinNumber))) != DIO_CHANNEL_NOT_CONFIG)
            {
                ErrorStatus = E_OK;
            }
        }
    }

    return ErrorStatus;
}

/****************************************************************************************************
*   Function Name           : Dio_PortIdCheck
*
*   Service ID              : None.
*
*   Description             : This function shall check if the PortId is available or not.
*
*   Parameters in           : PortId: ID of DIO Port.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: The PortId is available.
*                             E_NOT_OK: The PortId is not available.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, DIO_PRIVATE_CODE) Dio_PortIdCheck
(
    Dio_PortType PortId
)
{
    uint8           PortIndex;
    Std_ReturnType  ErrorStatus;

    ErrorStatus = E_NOT_OK;

    if (PortId < DIO_MAX_PORT_NUMBER)
    {
        PortIndex = Dio_ConfigSet.Dio_AvailablePortIndexPtr[PortId];
        if ((DIO_INVALID_PORT_INDEX != PortIndex) && (DIO_PORT_CONFIGURED ==
            (Dio_Port_ConfigType)Dio_ConfigSet.Dio_ChCfgDataPtr[PortIndex].Dio_PortConfig))
        {
            ErrorStatus = E_OK;
        }

    }

    return ErrorStatus;
}

/****************************************************************************************************
*   Function Name           : Dio_GroupIdCheck
*
*   Service ID              : None.
*
*   Description             : This function shall check if the GroupId is available or not.
*
*   Parameters in           : ChannelGroupIdPtr: Pointer to ChannelGroup.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : E_OK: The ChannelGroup is available.
*                             E_NOT_OK: The ChannelGroup is not available.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, DIO_PRIVATE_CODE) Dio_GroupIdCheck
(
    CONSTP2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_DATA) ChannelGroupIdPtr
)
{
    Std_ReturnType ErrorStatus;

    ErrorStatus = E_NOT_OK;

    if((ChannelGroupIdPtr->port < DIO_MAX_PORT_NUMBER) &&
       (ChannelGroupIdPtr->mask >= DIO_GROUP_MIN_MASK) &&
       (ChannelGroupIdPtr->offset < DIO_PIN_MAX_NUMBER))
    {
        ErrorStatus = E_OK;
    }

    return ErrorStatus;
}

/****************************************************************************************************
*   Function Name           : Dio_ReadOnlyPortCheck
*
*   Service ID              : None.
*
*   Description             : This function shall check if the port is read only or it is writable.
*
*   Parameters in           : Port: ID of DIO port.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : TRUE: The port is read only.
*                             FALSE: The port is writable.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, DIO_PRIVATE_CODE) Dio_ReadOnlyPortCheck
(
    Dio_PortType PortNumber
)
{
    uint32 PortReadOnly;
    boolean RetVal;

    RetVal = FALSE;

    if (PortNumber < DIO_PORTS_READ_ONLY_MASK)
    {
        PortReadOnly = ((1UL << (PortNumber)) & ((uint32)DIO_PORTS_READONLY_00_31));
    }
    else
    {
        PortReadOnly = ((1UL << (PortNumber - DIO_PORTS_READ_ONLY_MASK)) & DIO_PORTS_READONLY_32_63);
    }

    if (0UL != PortReadOnly)
    {
        RetVal = TRUE;
    }

    return RetVal;
}

#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
/* #Violation: Dio_c_REF_3 */
#define DIO_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dio_c_REF_2 */
#include "Dio_MemMap.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Dio_c_REF_3 */
#define DIO_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dio_c_REF_2 */
#include "Dio_MemMap.h"


/****************************************************************************************************
*   Function Name           : Dio_ReadChannel
*
*   Service ID              : 0x00
*
*   Description             : This function shall return the value of the specified DIO channel.
*
*   Parameters in           : ChannelId: ID of DIO channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
*                             STD_LOW: The physical level of the corresponding Pin is STD_LOW.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Dio_00133
****************************************************************************************************/
/* #Violation: Dio_c_REF_6 */
FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_ReadChannel
(
    Dio_ChannelType ChannelId
)
{
    uint8          PinNumber;
    Dio_LevelType  RetVal;
    Dio_PortType   PortNumber;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetStatus;
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

    PortNumber = GET_DIOPORTNUMBER(ChannelId);
    PinNumber = GET_DIOPINNUMBER(ChannelId);
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    RetVal = (Dio_LevelType)STD_LOW;
    RetStatus = Dio_ChannelIdCheck(ChannelId, PortNumber, PinNumber);
    if(E_NOT_OK == RetStatus)
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_READCHANNEL,
                              DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
    {
        RetVal = Dio_TLLD_GetPinLevel(PortNumber, PinNumber);
    }

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Dio_WriteChannel
*
*   Service ID              : 0x01
*
*   Description             : This function shall set a level of a channel.
*
*   Parameters in           : ChannelId: ID of DIO channel.
*                             Level: Value to be written.
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
*   AUTOSAR_Requirement     : SWS_Dio_00134
****************************************************************************************************/
FUNC(void, DIO_PUBLIC_CODE) Dio_WriteChannel
(
    Dio_ChannelType ChannelId,
    Dio_LevelType Level
)
{

    Dio_PortType PortNumber;
    uint8 PinNumber;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    boolean PortReadOnly;
    Std_ReturnType RetStatus;
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

    PortNumber = GET_DIOPORTNUMBER(ChannelId);
    PinNumber = GET_DIOPINNUMBER(ChannelId);

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    RetStatus = Dio_ChannelIdCheck(ChannelId, PortNumber, PinNumber);
    if(E_NOT_OK == RetStatus)
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_WRITECHANNEL,
                              DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
    {
        PortReadOnly = Dio_ReadOnlyPortCheck(PortNumber);
        if(TRUE == PortReadOnly)
        {
            (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_WRITECHANNEL,
                                  DIO_E_PARAM_INVALID_CHANNEL_ID);
        }
        else
        {
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
            Dio_TLLD_SetPinLevel(PortNumber, PinNumber, Level);
#if (DIO_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

}

/****************************************************************************************************
*   Function Name           : Dio_ReadPort
*
*   Service ID              : 0x02
*
*   Description             : This function shall return the level of all channels of that port.
*
*   Parameters in           : PortId: ID of DIO Port.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Level of all channels of that port.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Dio_00135
****************************************************************************************************/
/* #Violation: Dio_c_REF_6 */
FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE) Dio_ReadPort
(
    Dio_PortType PortId
)
{
    Dio_PortLevelType RetVal;
    Dio_PortLevelType PinAvaPinsMask;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetStatus;
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

    RetVal = (Dio_PortLevelType)STD_LOW;
    PinAvaPinsMask = 0x0000U;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    RetStatus = Dio_PortIdCheck(PortId);
    if (E_NOT_OK == RetStatus)
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_READPORT,
                              DIO_E_PARAM_INVALID_PORT_ID);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
    {
        RetVal = Dio_TLLD_GetGroupLevel(PortId, DIO_GROUP_OFFSET0, DIO_GROUP_MASKALL);
        PinAvaPinsMask = Dio_ConfigSet.Dio_AvailablePortPinsPtr
                            [Dio_ConfigSet.Dio_AvailablePortIndexPtr[PortId]];
    }
    RetVal &= PinAvaPinsMask;
    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Dio_WritePort
*
*   Service ID              : 0x03
*
*   Description             : This function shall set a value of the port.
*
*   Parameters in           : PortId: ID of DIO channel.
*                             Level: Value to be written.
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
*   AUTOSAR_Requirement     : SWS_Dio_00136
****************************************************************************************************/
/* #Violation: Dio_c_REF_6 */
FUNC(void, DIO_PUBLIC_CODE) Dio_WritePort
(
    Dio_PortType PortId,
    Dio_PortLevelType Level
)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    boolean PortReadOnly;
    Std_ReturnType RetStatus;

    RetStatus = Dio_PortIdCheck(PortId);
    PortReadOnly = Dio_ReadOnlyPortCheck(PortId);
    if((E_NOT_OK == RetStatus) || (TRUE == PortReadOnly))
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_WRITEPORT,
                              DIO_E_PARAM_INVALID_PORT_ID);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
    {
        Dio_TLLD_SetGroupLevel(PortId, DIO_GROUP_OFFSET0, DIO_GROUP_MASKALL, Level);
    }
}

/****************************************************************************************************
*   Function Name           : Dio_ReadChannelGroup
*
*   Service ID              : 0x04
*
*   Description             : This function reads a subset of the adjoining bits of a port.
*
*   Parameters in           : ChannelGroupIdPtr: Pointer to ChannelGroup.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Level of a subset of the adjoining bits of a port.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : [SWS_Dio_00137],[SWS_Dio_00008],[SWS_Dio_00056],[SRS_Dio_12004]
****************************************************************************************************/
/* #Violation: Dio_c_REF_6 */
FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE) Dio_ReadChannelGroup
(
    /* #Violation: Dio_c_REF_4 */
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_CONFIG_CONST) ChannelGroupIdPtr
)
{
    Dio_PortLevelType RetVal;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetStatus;
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    RetVal = (Dio_PortLevelType)STD_LOW;

    if (ChannelGroupIdPtr == NULL_PTR)
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_READGROUP,
                              DIO_E_PARAM_POINTER);
    }
    else
    {
        RetStatus = Dio_GroupIdCheck(ChannelGroupIdPtr);
        if(E_NOT_OK == RetStatus)
        {
            (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_READGROUP,
                                  DIO_E_PARAM_INVALID_GROUP);
        }
        else
        {
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
            RetVal = Dio_TLLD_GetGroupLevel(ChannelGroupIdPtr->port, ChannelGroupIdPtr->offset,
                                            ChannelGroupIdPtr->mask);
#if (DIO_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Dio_WriteChannelGroup
*
*   Service ID              : 0x05
*
*   Description             : This function shall set a subset of the adjoining bits of a port
*                             to a specified level.
*
*   Parameters in           : ChannelGroupIdPtr: Pointer to ChannelGroup.
*                             Level: Value to be written.
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
*   AUTOSAR_Requirement     : [SWS_Dio_00138],[SWS_Dio_00008],[SWS_Dio_00056],[SRS_Dio_12004]
****************************************************************************************************/
/* #Violation: Dio_c_REF_6 */
FUNC(void, DIO_PUBLIC_CODE) Dio_WriteChannelGroup
(
    /* #Violation: Dio_c_REF_4 */
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_CONFIG_CONST) ChannelGroupIdPtr,
    Dio_PortLevelType Level
)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    boolean PortReadOnly;
    Std_ReturnType RetStatus;
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

#if (DIO_DEV_ERROR_DETECT == STD_ON)

    if (ChannelGroupIdPtr == NULL_PTR)
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_WRITEGROUP,
                              DIO_E_PARAM_POINTER);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
    {
#if (DIO_DEV_ERROR_DETECT == STD_ON)
        PortReadOnly = Dio_ReadOnlyPortCheck(ChannelGroupIdPtr->port);
        if(TRUE == PortReadOnly)
        {
            (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_WRITEGROUP,
                                  DIO_E_PARAM_INVALID_GROUP);
        }
        else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
        {
#if (DIO_DEV_ERROR_DETECT == STD_ON)
            RetStatus = Dio_GroupIdCheck(ChannelGroupIdPtr);
            if(E_NOT_OK == RetStatus)
            {
                (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_WRITEGROUP,
                                      DIO_E_PARAM_INVALID_GROUP);
            }
            else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
            {
                Dio_TLLD_SetGroupLevel(ChannelGroupIdPtr->port, ChannelGroupIdPtr->offset,
                                       ChannelGroupIdPtr->mask, Level);
            }
        }

    }
}

#if (DIO_FLIP_CHANNEL_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Dio_FlipChannel
*
*   Service ID              : 0x11
*
*   Description             : This function shall flip (change from 1 to 0 or from 0 to 1) the level
*                             of a channel and return the level of the channel after flip.
*
*   Parameters in           : ChannelId: ID of DIO channel.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
*                             STD_LOW: The physical level of the corresponding Pin is STD_LOW.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Dio_00190
****************************************************************************************************/
FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_FlipChannel
(
    Dio_ChannelType ChannelId
)
{
    Dio_PortType PortNumber;
    uint8 PinNumber;
    Dio_LevelType RetVal;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    boolean PortReadOnly;
    Std_ReturnType RetStatus;
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

    PortNumber = GET_DIOPORTNUMBER(ChannelId);
    PinNumber = GET_DIOPINNUMBER(ChannelId);

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    RetVal = (Dio_LevelType)STD_LOW;
    RetStatus = Dio_ChannelIdCheck(ChannelId, PortNumber, PinNumber);
    if(E_NOT_OK == RetStatus)
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_FLIPCHANNEL,
                              DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
    {
#if (DIO_DEV_ERROR_DETECT == STD_ON)
        PortReadOnly = Dio_ReadOnlyPortCheck(PortNumber);
        if(TRUE == PortReadOnly)
        {
            (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_FLIPCHANNEL,
                                  DIO_E_PARAM_INVALID_CHANNEL_ID);
        }
        else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
        {
            {
                RetVal = Dio_TLLD_TogglePin(PortNumber, PinNumber);
            }
        }
    }
    return RetVal;
}
#endif /* (DIO_FLIP_CHANNEL_API  \== STD_ON) */

#if (STD_ON == DIO_VERSION_INFO_API)
/****************************************************************************************************
*   Function Name           : Dio_GetVersionInfo
*
*   Service ID              : 0x12
*
*   Description             : This function shall get the version information of this module.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : VersionInfoPtr: Pointer to where to store the version information
*                                             of this module.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Dio_00139
****************************************************************************************************/
/* #Violation: Dio_c_REF_6 */
FUNC(void, DIO_PUBLIC_CODE) Dio_GetVersionInfo
(
    /* #Violation: Dio_c_REF_4 */
    /* #Violation: Dio_c_REF_1 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) VersionInfoPtr
)
{
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_GETVERSIO, DIO_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON \== DIO_DEV_ERROR_DETECT) */
    {
        VersionInfoPtr->vendorID         = (uint16)DIO_VENDOR_ID;
        VersionInfoPtr->moduleID         = (uint16)DIO_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON \== DIO_VERSION_INFO_API) */

#if (STD_ON== DIO_MASKED_WRITE_PORT_API)
/****************************************************************************************************
*   Function Name           : Dio_MaskedWritePort
*
*   Service ID              : 0x13
*
*   Description             : service to set the value of a given port with required mask.
*
*   Parameters in           : PortId: ID of DIO Port.
*                             Level : Value to be written.
*                             Mask  : Channels to be masked in the port.
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
*   AUTOSAR_Requirement     : SWS_Dio_00190
****************************************************************************************************/
void Dio_MaskedWritePort
(
    const Dio_PortType PortId,
    const Dio_PortLevelType Level,
    const Dio_PortLevelType Mask
)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    boolean PortReadOnly;
    Std_ReturnType RetStatus;

    RetStatus = Dio_PortIdCheck(PortId);
    PortReadOnly = Dio_ReadOnlyPortCheck(PortId);
    if((E_NOT_OK == RetStatus) || (TRUE == PortReadOnly))
    {
        (void)Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_SID_WRITEPORT,
                              DIO_E_PARAM_INVALID_PORT_ID);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */
    {
        Dio_TLLD_SetGroupLevel(PortId, DIO_GROUP_OFFSET0, Mask, Level);
    }
}
#endif /* (STD_ON \== DIO_MASKED_WRITE_PORT_API) */
/* #Violation: Dio_c_REF_3 */
#define DIO_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dio_c_REF_2 */
#include "Dio_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


/****************************************************************************************************
**                          Stub Function Definitions Start                                        **
****************************************************************************************************/


/*******************************************************************************
**                          Check Init                                       **
*******************************************************************************/

/****************************************************************************************************
**                          Stub Function Definitions End                                          **
****************************************************************************************************/
