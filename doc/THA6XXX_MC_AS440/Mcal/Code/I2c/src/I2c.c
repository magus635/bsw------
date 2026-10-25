/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : I2c.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : I2c.
*
*   brief                 : This file contains all functions of I2c Driver
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
*#I2c_c_REF_1:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#I2c_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#I2c_c_REF_3:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#I2c_c_REF_4:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#I2c_c_REF_5:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#I2c_c_REF_6:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#I2c_c_REF_7:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#I2c_c_REF_8:MISRAC2012-Rule-20.7;
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "I2c.h"
#include "I2c_GeneralTypes.h"
#include "SchM_I2c.h"
#include "I2c_Version.h"
/* Included for the declaration of Det_ReportError() */
#include "Det.h"



/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
/* Check if current file and I2C header file are of the same vendor */
#if (I2C_VENDOR_ID != I2C_CFG_VENDOR_ID)
  #error "I2c.c : Mismatch in Vendor ID"
#endif /* (I2C_VENDOR_ID \!= I2C_CFG_VENDOR_ID) */

#if (I2C_MODULE_ID != I2C_CFG_MODULE_ID)
  #error "I2c.c : Mismatch in Module ID"
#endif /* (I2C_MODULE_ID \!= I2C_CFG_MODULE_ID) */

#if (I2C_AR_RELEASE_MAJOR_VERSION != I2C_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "I2c.c : Mismatch in Release Major Version"
#endif /* (PORT_AR_RELEASE_MAJOR_VERSION \!= PORT_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (I2C_AR_RELEASE_MINOR_VERSION != I2C_CFG_AR_RELEASE_MINOR_VERSION)
  #error "I2c.c : Mismatch in Release Minor Version"
#endif /* (PORT_AR_RELEASE_MINOR_VERSION \!= PORT_CFG_AR_RELEASE_MINOR_VERSION) */

#if (I2C_AR_RELEASE_REVISION_VERSION != I2C_CFG_AR_RELEASE_REVISION_VERSION)
  #error "I2c.c : Mismatch in Release Revision Version"
#endif /* (PORT_AR_RELEASE_REVISION_VERSION \!= PORT_CFG_AR_RELEASE_REVISION_VERSION) */

#if (I2C_SW_MAJOR_VERSION != I2C_CFG_SW_MAJOR_VERSION)
  #error "I2c.c : Mismatch in Software Major Version"
#endif /* (PORT_SW_MAJOR_VERSION \!= PORT_CFG_SW_MAJOR_VERSION) */

#if (I2C_SW_MINOR_VERSION != I2C_CFG_SW_MINOR_VERSION)
  #error "I2c.c : Mismatch in Software Minor Version"
#endif /* (PORT_SW_MINOR_VERSION \!= PORT_CFG_SW_MINOR_VERSION) */

#if (I2C_SW_PATCH_VERSION != I2C_CFG_SW_PATCH_VERSION)
  #error "I2c.c : Mismatch in Software Patch Version"
#endif /* (I2C_SW_PATCH_VERSION \!= I2C_CFG_SW_PATCH_VERSION) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define I2C_INITIALIZED                    (1U)
#define I2C_UNINITIALIZED                  (0U)

/****************************************************************************************************
*                          SchM Critical Section Protection Macros                                 **
****************************************************************************************************/
/* #Violation: I2c_c_REF_1 */ 
/* #Violation: I2c_c_REF_6 */ 
#define I2C_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_I2c_##Exclusive_Area() 
/* #Violation: I2c_c_REF_1 */ 
/* #Violation: I2c_c_REF_6 */ 
#define I2C_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_I2c_##Exclusive_Area() 

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if (I2C_MAX_CHANNEL_TO_CORE0 > 0U)
/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

/* I2c channel internal status machine */
static I2c_ChannelInfoType I2c_ChannelStatusCore0[I2C_MAX_CHANNEL_TO_CORE0];

/* I2c initialization status in core0 */
static I2c_InitType I2c_InitStatusCore0;

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/* Holding core0 specific I2C channel status */
static const I2c_CoreStatusType I2c_StatusSetCore0 =
{
    &I2c_ChannelStatusCore0[0],
    &I2c_InitStatusCore0
};

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

#endif /* (I2C_MAX_CHANNEL_TO_CORE0 \> 0U) */

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (I2C_MAX_CHANNEL_TO_CORE1 > 0U)

/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

/* I2c channel internal status machine */
static I2c_ChannelInfoType I2c_ChannelStatusCore1[I2C_MAX_CHANNEL_TO_CORE1];

/* I2c initialization status in core1 */
static uint8 I2c_InitStatusCore1;

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

/* Holding core1 specific I2c channel status */
static const I2c_CoreStatusType I2c_StatusSetCore1 =
{
    &I2c_ChannelStatusCore1[0],
    &I2c_InitStatusCore1
};

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
 /* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"
#endif /* (I2C_MAX_CHANNEL_TO_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (I2C_MAX_CHANNEL_TO_CORE2 > 0U)

/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

/* I2c channel internal status machine */
static I2c_ChannelInfoType I2c_ChannelStatusCore2[I2C_MAX_CHANNEL_TO_CORE2];

/* I2c initialization status in core2 */
static uint8 I2c_InitStatusCore2;

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

/* Holding core2 specific I2c channel status */
static const I2c_CoreStatusType I2c_StatusSetCore2 =
{
    &I2c_ChannelStatusCore2[0],
    &I2c_InitStatusCore2
};

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"
#endif /* (I2C_MAX_CHANNEL_TO_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (I2C_MAX_CHANNEL_TO_CORE3 > 0U)

/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

/* I2c channel internal status machine */
static I2c_ChannelInfoType I2c_ChannelStatusCore3[I2C_MAX_CHANNEL_TO_CORE3];

/* I2c initialization status in core3 */
static uint8 I2c_InitStatusCore3;

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"

#define I2C_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
#include "I2c_MemMap.h"

/* Holding core3 specific I2c channel status */
static const I2c_CoreStatusType I2c_StatusSetCore3 =
{
    &I2c_ChannelStatusCore3[0],
    &I2c_InitStatusCore3
};

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h"
#endif /* (I2C_MAX_CHANNEL_TO_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/* Channel status information for all core */
static CONSTP2CONST(I2c_CoreStatusType, I2C_VAR, I2C_APPL_CONST)
                                      I2c_CoreStatusPtr[MCAL_NUMBER_OF_CORES] =
{
#if (I2C_MAX_CHANNEL_TO_CORE0 > 0U)
    &I2c_StatusSetCore0
#else
    NULL_PTR
#endif /* (I2C_MAX_CHANNEL_TO_CORE0 \> 0U) */

#if (MCAL_NUMBER_OF_CORES > 1U)
#if (I2C_MAX_CHANNEL_TO_CORE1 > 0U)
    ,&I2c_StatusSetCore1
#else
    ,NULL_PTR
#endif /* (I2C_MAX_CHANNEL_TO_CORE1 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 1U) */

#if (MCAL_NUMBER_OF_CORES > 2U)
#if (I2C_MAX_CHANNEL_TO_CORE2 > 0U)
    ,&I2c_StatusSetCore2
#else
    ,NULL_PTR
#endif /* (I2C_MAX_CHANNEL_TO_CORE2 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 2U) */

#if (MCAL_NUMBER_OF_CORES > 3U)
#if (I2C_MAX_CHANNEL_TO_CORE3 > 0U)
    ,&I2c_StatusSetCore3
#else
    ,NULL_PTR
#endif /* (I2C_MAX_CHANNEL_TO_CORE3 \> 0U) */
#endif /* (MCAL_NUMBER_OF_CORES \> 3U) */
};

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/* This pointer shall be store to copy field, not non-cache field */
static P2CONST(I2c_ConfigType, I2C_VAR, I2C_APPL_CONST) I2c_ConfigPtr;

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/* I2c module register base address packaging */
/* #Violation: I2c_c_REF_8 */ 
static CONSTP2VAR(I2C_MODULE, AUTOMATIC, SPI_APPL_CONST) I2c_BaseAddr[I2C_MAX_HWUNIT_COUNT] =
{
#if (I2C_MAX_HWUNIT_COUNT > 0U)
#if defined(I2C_HWUNIT_CHANNEL0)
    /* #Violation: I2c_c_REF_4 */ 
    I2C0 
#else /* \!defined(I2C_HWUNIT_CHANNEL0) */
    NULL_PTR
#endif /* defined(I2C_HWUNIT_CHANNEL0) */
#endif /* (I2C_MAX_HWUNIT_COUNT \> 0U) */

#if (I2C_MAX_HWUNIT_COUNT > 1U)
#if defined(I2C_HWUNIT_CHANNEL1)
    ,I2C1 
#else /* \!defined(I2C_HWUNIT_CHANNEL1) */
    ,NULL_PTR
#endif /* defined(I2C_HWUNIT_CHANNEL1) */
#endif /* (I2C_MAX_HWUNIT_COUNT \> 1U) */
};

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

#if (I2C_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, I2C_PRIVATE_CODE) I2c_TransmitDetCheck
(
    CONSTP2CONST(I2c_ChannelInfoType, AUTOMATIC, I2C_APPL_DATA)   ChannelInfoPtr,
    const uint8             ServiceId
);
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */

static FUNC(I2c_ChannelErrorType, I2C_PRIVATE_CODE) I2c_ErrorHandler
(
    I2c_HwUnitType          HwUnit
);

static FUNC(Std_ReturnType, I2C_PRIVATE_CODE) I2c_SyncTransmitInternal
(
    const I2c_ChannelType Channel,
    CONSTP2CONST(I2c_TransDataInfoType, AUTOMATIC, I2C_APPL_DATA) DataInfoPtr,
    Mcal_CoreType CoreId
);
/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 
#if (I2C_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : I2c_TransmitDetCheck
*
*   Service ID              : None.
*
*   Description             : DET check and return check RetStatus.
*
*   Parameters in           : CoreId: Current execution core ID
*                             Channel: I2c logical channel
*                             ServiceId: API service ID
*                             ChannelInfo: Information of I2c logical channel
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, I2C_PRIVATE_CODE) I2c_TransmitDetCheck
(
    CONSTP2CONST(I2c_ChannelInfoType, AUTOMATIC, I2C_APPL_DATA)   ChannelInfoPtr,
    const uint8             ServiceId
)
{
    Std_ReturnType      RetValue;

    RetValue = E_NOT_OK;
    if((0U == ChannelInfoPtr->DevInfo.dataSize) || 
       (I2C_MAX_SUPPORTED_SIZE < ChannelInfoPtr->DevInfo.dataSize))
    {
        /* Report to DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                      ServiceId, I2C_E_INVALID_SIZE);
    }
    else if(I2C_BUSY == ChannelInfoPtr->HwState)
    {
        /* Report to DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                      ServiceId, I2C_E_CHANNEL_BUSY);
    }
    else if(ChannelInfoPtr->DevInfo.devAddress > I2C_7_BIT_MAX_SLAVE_ADD)
    {
        /* Report to DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                       ServiceId, I2C_E_INVALID_SLAVE_ADDRESS);
    }
    else
    {
        RetValue = E_OK;
    }
    
    return RetValue;
}

/****************************************************************************************************
*   Function Name           : I2c_ChannelIDDetCheck
*
*   Service ID              : None.
*
*   Description             : Channel ID DET check and return check RetStatus.
*
*   Parameters in           : CoreId: Current execution core ID
*                             CoreChIdx: I2c channel on current core
*                             Channel: I2c logical channel
*                             ServiceId: API service ID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: No DET error
*                             E_NOT_OK: DET error.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, I2C_PRIVATE_CODE) I2c_ChannelIDDetCheck
(
    Mcal_CoreType           CoreId,
    uint8                   CoreChIdx,
    const I2c_ChannelType   Channel,
    const uint8             ServiceId
)
{
    Std_ReturnType                  RetValue;
    const I2c_InitCoreConfigType    *CorexConfigPtr;

    CorexConfigPtr = I2c_ConfigPtr->CoreConfigPtr[CoreId];

    RetValue = E_NOT_OK;
    if(NULL_PTR == CorexConfigPtr)
    {
         /* Channel is not configured in current core */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                              ServiceId, I2C_E_CORE_NOT_CONFIGURED);
    }
    else if (CoreChIdx >= I2c_ConfigPtr->CoreConfigPtr[CoreId]->CoreMaxChannels)
    {
        /* Channel number is greater than maximum configured of current core, 
        Logical channel is mismatch */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                              ServiceId, I2C_E_CORE_CHANNEL_MISMATCH);
    }
    else if(Channel != I2c_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].ChannelId)
    {
        /* Logical channel is mismatch */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                              ServiceId, I2C_E_CORE_CHANNEL_MISMATCH);
    }
    else if(I2C_MAX_HWUNIT_COUNT <= 
            I2c_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].HwUnitId)
    {
        /* Logical channel is mismatch */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                              ServiceId, I2C_E_CORE_CHANNEL_MISMATCH);
    }
    else if(NULL_PTR == I2c_BaseAddr[
            I2c_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx].HwUnitId])
    {
        /* Logical channel is mismatch */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                              ServiceId, I2C_E_CORE_CHANNEL_MISMATCH);
    }
    else
    {
        RetValue = E_OK;
    }
    
    return RetValue;
}
#endif  /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */
/****************************************************************************************************
*   Function Name           : I2c_ErrorHandler
*
*   Service ID              : None.
*
*   Description             : Judge the I2C channel status.
*
*   Parameters in           : CoreId: Current execution core ID
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : I2C_BUS_ERR: Bus error.
*                             I2C_OVERRUN: Overrun error.
*                             I2C_TX_OVERFLOW: TxFIFO overflow.
*                             I2C_RX_UNDERFLOW: RxFIFO underflow.
*                             I2C_NO_ACK: No ack.
*                             I2C_ARBITRATION_LOST: Arbitration lost.
*                             I2C_TIMEOUT: Time out error
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(I2c_ChannelErrorType, I2C_PRIVATE_CODE) I2c_ErrorHandler
(
    I2c_HwUnitType          HwUnit
)
{
    uint32                  ChannelStatus;
    I2c_ChannelErrorType    ErrorId;
    
    /* Check which status flag is set */
    ChannelStatus = I2c_Hal_GetFlag(I2c_BaseAddr[HwUnit]);
    /* Check if any transmit error occurred */
    if(0U != (ChannelStatus & I2C_SR1_BERR))
    {
        /* Set state machine to I2C_BUS_ERR */
        ErrorId = I2C_BUS_ERR;
    }
    else if(0U != (ChannelStatus & I2C_SR1_ARLO))
    {
        /* Set state machine to I2C_ARBITRATION_LOST */
        ErrorId = I2C_ARBITRATION_LOST;
    }
    else if(0U != (ChannelStatus & I2C_SR1_AF))
    {
        /* Set state machine to I2C_NO_ACK */
        ErrorId = I2C_NO_ACK;
    }
    else if(0U != (ChannelStatus & I2C_UNDERFLOW))
    {
        /* Set state machine to I2C_RX_UNDERFLOW */
        ErrorId = I2C_RX_UNDERFLOW;
    }
    else if(0U != (ChannelStatus & I2C_OVERFLOW))
    {
        /* Set state machine to I2C_TX_OVERFLOW */
        ErrorId = I2C_TX_OVERFLOW;
    }
    else if(0U != (ChannelStatus & I2C_SR1_OVR))
    {
        /* Set state machine to I2C_OVERRUN */
        ErrorId = I2C_OVERRUN;
    }
    else
    {
        /* Set state machine to I2C_TIMEOUT */
        ErrorId = I2C_TIMEOUT;
    }
    I2c_Hal_ClearFlag(I2c_BaseAddr[HwUnit], I2C_SR1_CLEARMASK | ((uint32)I2C_SR4_CLEARMASK << 28U));

    return ErrorId;
}

/****************************************************************************************************
*   Function Name           : I2c_SyncTransmitInternal
*
*   Service ID              : None
*
*   Description             : Internal function to perform synchronous I2C transmission.
*
*   Parameters in           : Channel: I2C channel identifier.
*                             DataInfoPtr: Pointer to transmission data information.
*                             CoreId: Current core ID.
*
*   Parameters inout        : None.
*
*   Parameters out          : Std_ReturnType: E_OK if successful, E_NOT_OK otherwise.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : Std_ReturnType: Transmission result.
*
*   Preconditions           : Parameters validated and module initialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, I2C_PRIVATE_CODE) I2c_SyncTransmitInternal
(
    const I2c_ChannelType Channel,
    CONSTP2CONST(I2c_TransDataInfoType, AUTOMATIC, I2C_APPL_DATA) DataInfoPtr,
    Mcal_CoreType CoreId
)
{
    uint8                       CoreChIdx;
    I2c_ConfigStatusType        RetStatus;
    const I2c_ChannelConfigType *ChannelConfigPtr;
    I2c_ChannelInfoType         *ChannelInfoPtr;
    I2c_ChannelErrorType        ErrorId;
    Std_ReturnType              RetValue;
#if (I2C_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType              DetRetStatus;
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */

    RetValue = E_NOT_OK;
    CoreChIdx = I2c_ConfigPtr->ChannelIdToCoreChIdPtr[Channel];
    
#if (I2C_DEV_ERROR_DETECT == STD_ON)
    DetRetStatus = I2c_ChannelIDDetCheck(CoreId, CoreChIdx, Channel, I2C_SID_SYNCTRANS);
    if(E_OK == DetRetStatus)
    {
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */

    /* Set the channel specific information */
        ChannelInfoPtr = &(I2c_CoreStatusPtr[CoreId]->ChannelStatusPtr[CoreChIdx]);
        /* Get channel config pointer */
        ChannelConfigPtr = &(I2c_ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[CoreChIdx]);

        /* Record the Channel information */
        ChannelInfoPtr->DevInfo.devAddress = DataInfoPtr->SlaveAddress;
        ChannelInfoPtr->DevInfo.pData = DataInfoPtr->DataPtr;
        ChannelInfoPtr->DevInfo.dataSize = DataInfoPtr->Size;
        ChannelInfoPtr->DevInfo.timeOut = I2C_TIMEOUT_DURATION;
        ChannelInfoPtr->I2c_Operation = DataInfoPtr->Diraction;

#if (I2C_DEV_ERROR_DETECT == STD_ON)
        DetRetStatus = I2c_TransmitDetCheck(ChannelInfoPtr, I2C_SID_SYNCTRANS);
    }
    if(E_OK == DetRetStatus)
#endif
    {
        I2C_ENTER_CRITICAL_SECTION(SyncTransmit);
        /* Set state machine to I2C_BUSY */
        ChannelInfoPtr->HwState = I2C_BUSY;
    
        if(I2C_WRITE == ChannelInfoPtr->I2c_Operation)
        {
            /* Set LSB of Slave address */
            ChannelInfoPtr->DevInfo.devAddress = ChannelInfoPtr->DevInfo.devAddress << 1U;
            /* Call write function to perform sending */
            RetStatus = I2c_Hal_MasterWrite(I2c_BaseAddr[ChannelConfigPtr->HwUnitId], &(ChannelInfoPtr->DevInfo));
        }
        else if(I2C_READ == ChannelInfoPtr->I2c_Operation)
        {
            /* Set LSB of Slave address */
            ChannelInfoPtr->DevInfo.devAddress = ((ChannelInfoPtr->DevInfo.devAddress << 1U) | 1U);
            /* Call read function to perform receiving */
            RetStatus = I2c_Hal_MasterRead(I2c_BaseAddr[ChannelConfigPtr->HwUnitId], &(ChannelInfoPtr->DevInfo));
        }
        else
        {
            RetStatus = I2C_STATUS_OK;
        }
    
        /* Transmit failed! */
        if(I2C_STATUS_OK != RetStatus)
        {
            ErrorId = I2c_ErrorHandler(ChannelConfigPtr->HwUnitId);
            /* Report errors */
            if(NULL_PTR != ChannelConfigPtr->I2c_NotifFunctionPtr)
            {
                (ChannelConfigPtr->I2c_NotifFunctionPtr)(ErrorId);
            }
        }
        else
        {
            RetValue = E_OK;
        }
    
        /* Set state machine to I2C_IDLE */
        ChannelInfoPtr->HwState = I2C_IDLE;
        I2C_EXIT_CRITICAL_SECTION(SyncTransmit);
    }
    return RetValue;
}

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: I2c_c_REF_2 */
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 

/****************************************************************************************************
*   Function Name           : I2c_Init
*
*   Service ID              : 0x00.
*
*   Description             : Initializes the I2C module.
*
*   Parameters in           : ConfigPtr: Pointer to LIN driver configuration set.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: I2c_c_REF_7 */
FUNC(void, I2C_PUBLIC_CODE) I2c_Init
(
    CONSTP2CONST(I2c_ConfigType, AUTOMATIC, I2C_APPL_CONST) ConfigPtr
)
{

    const I2c_ChannelConfigType     *ChannelConfigPtr;
    uint8                           CoreMaxChannel;
    uint8                           Channel;
    Mcal_CoreType                   CoreId;
    I2c_ChannelInfoType             *ChannelInfoPtr;
    I2c_Status                      RetStatus;

    /* Reset API execution status variables */
    RetStatus = I2C_STATUS_OK;
    /* Get core id which is executing currently */
    /* #Violation: I2c_c_REF_5 */ 
    CoreId = Mcal_GetCoreId(); 
    
#if (I2C_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == ConfigPtr)
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_INIT, I2C_E_PARAM_POINTER);
    }
    else if(NULL_PTR == I2c_CoreStatusPtr[CoreId])
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_INIT, I2C_E_CORE_NOT_CONFIGURED);
    }
    else if(I2C_INITIALIZED == *(I2c_CoreStatusPtr[CoreId]->CoreInitStatusPtr))
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_INIT, I2C_E_INITIALIZED);
    }
    else
#endif
    {
        /* Get the total channel number of current core */
        CoreMaxChannel = ConfigPtr->CoreConfigPtr[CoreId]->CoreMaxChannels;
    
        for(Channel = 0U; ((Channel < CoreMaxChannel) && (I2C_STATUS_OK == RetStatus)); Channel++)
        {
            /* Get I2c channel configuration in current core */
            ChannelConfigPtr = &(ConfigPtr->CoreConfigPtr[CoreId]->ChannelConfigPtr[Channel]);
            /* Initialize the configuration registers of the current Channel */
            RetStatus = I2c_Hal_Init(
                    I2c_BaseAddr[ChannelConfigPtr->HwUnitId], ChannelConfigPtr->HwConfigPtr);

            /* Reset global variables */
            ChannelInfoPtr = &(I2c_CoreStatusPtr[CoreId]->ChannelStatusPtr[Channel]);
            ChannelInfoPtr->HwState = I2C_IDLE;
            ChannelInfoPtr->I2c_Operation = I2C_NO_OPERATION;
            ChannelInfoPtr->DevInfo.devAddress = 0U;
            ChannelInfoPtr->DevInfo.pData = NULL_PTR;
            ChannelInfoPtr->DevInfo.dataSize = 0U;
            ChannelInfoPtr->DevInfo.timeOut = 0U;
            ChannelInfoPtr->DevInfo.masterCode = I2C_MASTERCODE;
        }
        if (I2C_STATUS_OK == RetStatus)
        {
            /* Set initialization RetStatus */
            *(I2c_CoreStatusPtr[CoreId]->CoreInitStatusPtr) = I2C_INITIALIZED;

            /* Update the global configuration parameter structure pointer */
            I2c_ConfigPtr = ConfigPtr;
        }
    }
}

#if (I2C_CFG_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : I2c_DeInit
*
*   Service ID              : 0x01.
*
*   Description             : This function reset all run-time variables and registers and set the I2c module to
*                             uninitialized status.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : I2C channel has been initialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: I2c_c_REF_7 */
FUNC(void, I2C_PUBLIC_CODE) I2c_DeInit
(
    void
)
{
    uint8                   Channel;
    uint8                   CoreMaxChannel;
    Mcal_CoreType           CoreId;
    I2c_ChannelInfoType     *ChannelInfoPtr;
    Std_ReturnType          RetStatus;
    I2c_Status              I2cStatus;

    RetStatus = E_OK;
    /* Get core id which is executing currently */
    /* #Violation: I2c_c_REF_5 */ 
    CoreId = Mcal_GetCoreId(); 
    
#if (I2C_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == I2c_CoreStatusPtr[CoreId])
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_DEINIT, I2C_E_CORE_NOT_CONFIGURED);
    }
    else if(I2C_UNINITIALIZED == *(I2c_CoreStatusPtr[CoreId]->CoreInitStatusPtr))
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_DEINIT, I2C_E_UNINIT);
    }
    else
#endif
    {
        /* Get the total channel number of current core */
        CoreMaxChannel = I2c_ConfigPtr->CoreConfigPtr[CoreId]->CoreMaxChannels;
            
        /* Reset all channel status */
        for(Channel = 0U; ((Channel < CoreMaxChannel) && (E_OK == RetStatus)); Channel++)
        {
            I2C_ENTER_CRITICAL_SECTION(DeInit);
            RetStatus = Mcal_GetLock(MCAL_LOCK_ID_RCC);
            if(E_OK == RetStatus)
            {
                /* Reset the clock */
                I2cStatus = I2c_Hal_DeInit(I2c_BaseAddr[I2c_ConfigPtr->
                            CoreConfigPtr[CoreId]->ChannelConfigPtr[Channel].HwUnitId]);
                if(I2C_STATUS_OK != I2cStatus)
                {
                    RetStatus = E_NOT_OK;
                }
                Mcal_ReleaseLock(MCAL_LOCK_ID_RCC);
            }
            I2C_EXIT_CRITICAL_SECTION(DeInit);
            /*Reset the channel information*/
            ChannelInfoPtr = &(I2c_CoreStatusPtr[CoreId]->ChannelStatusPtr[Channel]);
            ChannelInfoPtr->HwState = I2C_UNINIT;
            ChannelInfoPtr->I2c_Operation = I2C_NO_OPERATION;
            ChannelInfoPtr->DevInfo.devAddress = 0U;
            ChannelInfoPtr->DevInfo.pData = NULL_PTR;
            ChannelInfoPtr->DevInfo.dataSize = 0U;
            ChannelInfoPtr->DevInfo.timeOut = 0U;
        }
        if(E_OK == RetStatus)
        {
            /* Set initialization RetStatus */
            *(I2c_CoreStatusPtr[CoreId]->CoreInitStatusPtr) = I2C_UNINITIALIZED;
        }
        else
        {
            (void)Det_ReportRuntimeError((uint16)I2C_MODULE_ID, \
                                        (uint8)I2C_INSTANCE_ID, \
                                        (uint8)I2C_SID_DEINIT, \
                                        (uint8)I2C_E_DEINIT_FAILED);
        }
    }
}
#endif /* I2C_CFG_DEINIT_API == STD_ON */

/****************************************************************************************************
*   Function Name           : I2c_SyncTransmit
*
*   Service ID              : 0x02.
*
*   Description             : Sends/Receives I2C data. 
*
*   Parameters in           : Channel: I2C channel to be addressed.
*                             DataInfoPtr: Pointer to information packet containing the address mode, 
*                                          slave address,transmission direction, transmission size and 
*                                          data pointer.
*
*   Parameters inout        : None.
*
*   Parameters out          : If receive data, DataPtr: Pointer to a shadow buffer or memory mapped I2c
*                                         Hardware receive buffer.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: Transmission successfully.
*                             E_NOT_OK: Transmission failed.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: I2c_c_REF_7 */
FUNC(Std_ReturnType, I2C_PUBLIC_CODE) I2c_SyncTransmit
(
    const I2c_ChannelType Channel,
    CONSTP2CONST(I2c_TransDataInfoType, AUTOMATIC, I2C_APPL_DATA) DataInfoPtr
)
{
    Std_ReturnType              RetValue;
    Mcal_CoreType               CoreId;

    RetValue = E_NOT_OK;
    /* Get core id which is executing currently */
    /* #Violation: I2c_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 
    
#if (I2C_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == DataInfoPtr)
    {
        /* Report to DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                      I2C_SID_SYNCTRANS, I2C_E_PARAM_POINTER);
    }
    else if(NULL_PTR == I2c_CoreStatusPtr[CoreId])
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_SYNCTRANS, I2C_E_CORE_NOT_CONFIGURED);
    }
    else if(I2C_UNINITIALIZED == *(I2c_CoreStatusPtr[CoreId]->CoreInitStatusPtr))
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_SYNCTRANS, I2C_E_UNINIT);
    }
    else if(I2C_TOTAL_CFG_CHANNEL_NUM <= Channel)
    {
        /* Report to DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                      I2C_SID_SYNCTRANS, I2C_E_INVALID_CHANNEL);
    }
    else
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Find sub channel id in current core */
        RetValue = I2c_SyncTransmitInternal(Channel, DataInfoPtr, CoreId);
    }

    return RetValue;
}

/****************************************************************************************************
*   Function Name           : I2c_GetStatus
*
*   Service ID              : 0x03.
*
*   Description             : Gets the RetStatus of the I2C driver.
*
*   Parameters in           : Channel: I2c channel to be checked.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : I2C_UNINIT : The I2C Driver is not initialized.
*                             I2C_IDLE : The I2C Driver is idle.
*                             I2C_BUSY : The I2C Driver is performing busy.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: I2c_c_REF_7 */
FUNC(I2c_ChannelStatusType, I2C_PUBLIC_CODE) I2c_GetStatus
(
    const I2c_ChannelType Channel
)
{
    I2c_ChannelStatusType   ReturnStatus;
    Mcal_CoreType           CoreId;
    uint8                   CoreChIdx;
#if (I2C_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType              DetRetStatus;
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */

    /* Get core id which is executing currently */
    /* #Violation: I2c_c_REF_5 */
    CoreId = Mcal_GetCoreId(); 
    
#if (I2C_DEV_ERROR_DETECT == STD_ON)
    ReturnStatus = I2C_IDLE;
    
    if (I2C_TOTAL_CFG_CHANNEL_NUM <= Channel)
    {
        /* Report to DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, \
                        I2C_SID_GETSTATUS, I2C_E_INVALID_CHANNEL);
    }
    else if(NULL_PTR == I2c_CoreStatusPtr[CoreId])
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_GETSTATUS, I2C_E_CORE_NOT_CONFIGURED);
    }
    else if(I2C_UNINITIALIZED == *(I2c_CoreStatusPtr[CoreId]->CoreInitStatusPtr))
    {
        /* Report to  DET */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_GETSTATUS, I2C_E_UNINIT);
    }
    else
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Find sub channel id in current core */
        CoreChIdx = I2c_ConfigPtr->ChannelIdToCoreChIdPtr[Channel];
#if (I2C_DEV_ERROR_DETECT == STD_ON)
        DetRetStatus = I2c_ChannelIDDetCheck(CoreId, CoreChIdx, Channel, I2C_SID_GETSTATUS);
        if (E_OK == DetRetStatus)
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */
        {
            /* Get status */
            ReturnStatus = I2c_CoreStatusPtr[CoreId]->ChannelStatusPtr[CoreChIdx].HwState;
        }
    }
    return ReturnStatus;
}

#if (I2C_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : I2c_GetVersionInfo
*
*   Service ID              : 0x04.
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
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: I2c_c_REF_7 */
FUNC(void, I2C_PUBLIC_CODE) I2c_GetVersionInfo
(
    /* #Violation: I2c_c_REF_8 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, I2C_APPL_DATA) VersionInfoPtr
)
{
#if (I2C_DEV_ERROR_DETECT == STD_ON)
    if(NULL_PTR == VersionInfoPtr)
    {
        /* Invalid pointer */
        (void)Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_GETVERSIONINFO,
                              I2C_E_PARAM_POINTER);
    }
    else
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */
    {
        VersionInfoPtr->vendorID = (uint16)I2C_VENDOR_ID;
        VersionInfoPtr->moduleID = (uint16)I2C_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)I2C_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)I2C_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)I2C_SW_PATCH_VERSION;
    }
}
#endif /* I2C_VERSION_INFO_API == STD_ON */

/* #Violation: I2c_c_REF_2 */
#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: I2c_c_REF_3 */
#include "I2c_MemMap.h" 
/****************************************************************************************************
**                          End of File                                                            **
*****************************************************************************************************/
