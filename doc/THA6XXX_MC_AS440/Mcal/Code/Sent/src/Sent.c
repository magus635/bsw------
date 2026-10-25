/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Sent.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SENT
*
*   brief                 : SENT Driver source file
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
*#Sent_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Sent_c_REF_2:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Sent_c_REF_3:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Sent_c_REF_4:CWE-1071-C;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Sent_c_REF_5:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#Sent_c_REF_6:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Sent_c_REF_7:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Sent_c_REF_8::MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Sent.h"
#include "SchM_Sent.h"
#include "Det.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (SENT_VENDOR_ID != SENT_CFG_VENDOR_ID)
  #error "Sent.c : Mismatch in Vendor ID"
#endif /* (SENT_VENDOR_ID \!= SENT_CFG_VENDOR_ID) */

#if (SENT_MODULE_ID != SENT_CFG_MODULE_ID)
  #error "Sent.c : Mismatch in Module ID"
#endif /* (SENT_MODULE_ID \!= SENT_CFG_MODULE_ID) */

#if (SENT_AR_RELEASE_MAJOR_VERSION != SENT_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Sent.c : Mismatch in Release Major Version"
#endif /* (SENT_AR_RELEASE_MAJOR_VERSION \!= SENT_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (SENT_AR_RELEASE_MINOR_VERSION != SENT_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Sent.c : Mismatch in Release Minor Version"
#endif /* (SENT_AR_RELEASE_MINOR_VERSION \!= SENT_CFG_AR_RELEASE_MINOR_VERSION) */

#if (SENT_AR_RELEASE_REVISION_VERSION != SENT_CFG_AR_RELEASE_PATCH_VERSION)
  #error "Sent.c : Mismatch in Release Revision Version"
#endif /* (SENT_AR_RELEASE_REVISION_VERSION \!= SENT_CFG_AR_RELEASE_REVISION_VERSION) */

#if (SENT_SW_MAJOR_VERSION != SENT_CFG_SW_MAJOR_VERSION)
  #error "Sent.c : Mismatch in Software Major Version"
#endif /* (SENT_SW_MAJOR_VERSION \!= SENT_CFG_SW_MAJOR_VERSION) */

#if (SENT_SW_MINOR_VERSION != SENT_CFG_SW_MINOR_VERSION)
  #error "Sent.c : Mismatch in Software Minor Version"
#endif /* (SENT_SW_MINOR_VERSION \!= SENT_CFG_SW_MINOR_VERSION) */

#if (SENT_SW_PATCH_VERSION != SENT_CFG_SW_PATCH_VERSION)
  #error "Sent.c : Mismatch in Software Patch Version"
#endif /* (SENT_SW_PATCH_VERSION \!= SENT_CFG_SW_PATCH_VERSION) */
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* Values used by the SENT module*/
#define SENT_ZERO_U                         (0x0U)
#define SENT_ONE_U                          (0x1U)

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/* #Violation: Sent_c_REF_6 */
/* #Violation: Sent_c_REF_7 */
#define SENT_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Sent_##Exclusive_Area() 
/* #Violation: Sent_c_REF_6 */
/* #Violation: Sent_c_REF_7 */
#define SENT_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Sent_##Exclusive_Area() 
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/* #Violation: Sent_c_REF_8 */
#define SENT_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
#include "Sent_MemMap.h" 

/* To store the Sent driver configuration pointer */
static const Sent_ConfigType *Sent_kConfigPtr;

/* #Violation: Sent_c_REF_8 */
#define SENT_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32 
/* #Violation: Sent_c_REF_1 */
#include "Sent_MemMap.h" 

/* #Violation: Sent_c_REF_8 */
#define SENT_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: Sent_c_REF_1 */
#include "Sent_MemMap.h" 

/* Indicate Address from SENT0 to SENT9 */
static SENT_MODULE *const Sent_BaseRegister[SENT_HW_MAX_CHANNELS] =
{
#if (SENT_HW_MAX_CHANNELS > 0U)
#if (SENT_INST0_CHAN0 == STD_ON)
    SENT0 
#else /* (SENT_INST0_CHAN0  \== STD_ON) */
    NULL_PTR
#endif /* (SENT_INST0_CHAN0  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 0U) */

#if (SENT_HW_MAX_CHANNELS > 1U)
#if (SENT_INST0_CHAN1 == STD_ON)
    ,SENT1 
#else /* (SENT_INST0_CHAN1  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN1  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 1U) */

#if (SENT_HW_MAX_CHANNELS > 2U)
#if (SENT_INST0_CHAN2 == STD_ON)
    /* #Violation: Sent_c_REF_2 */
    ,SENT2
#else /* (SENT_INST0_CHAN2  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN2  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 2U) */

#if (SENT_HW_MAX_CHANNELS > 3U)
#if (SENT_INST0_CHAN3 == STD_ON)
    /* #Violation: Sent_c_REF_2 */
    ,SENT3 
#else /* (SENT_INST0_CHAN3  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN3  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 3U) */

#if (SENT_HW_MAX_CHANNELS > 4U)
#if (SENT_INST0_CHAN4 == STD_ON)
    ,SENT4
#else /* (SENT_INST0_CHAN4  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN4  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 4U) */

#if (SENT_HW_MAX_CHANNELS > 5U)
#if (SENT_INST0_CHAN5 == STD_ON)
    /* #Violation: Sent_c_REF_2 */
    ,SENT5 
#else /* (SENT_INST0_CHAN5  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN5  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 5U) */

#if (SENT_HW_MAX_CHANNELS > 6U)
#if (SENT_INST0_CHAN6 == STD_ON)
    /* #Violation: Sent_c_REF_2 */
    ,SENT6 
#else /* (SENT_INST0_CHAN6  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN6  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 6U) */

#if (SENT_HW_MAX_CHANNELS > 7U)
#if (SENT_INST0_CHAN7 == STD_ON)
    /* #Violation: Sent_c_REF_2 */
    ,SENT7 
#else /* (SENT_INST0_CHAN7  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN7  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 7U) */

#if (SENT_HW_MAX_CHANNELS > 8U)
#if (SENT_INST0_CHAN8 == STD_ON)
    ,SENT8 
#else /* (SENT_INST0_CHAN8  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN8  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 8U) */

#if (SENT_HW_MAX_CHANNELS > 9U)
#if (SENT_INST0_CHAN9 == STD_ON)
    /* #Violation: Sent_c_REF_2 */
    ,SENT9 
#else /* (SENT_INST0_CHAN9  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN9  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 9U) */

#if (SENT_HW_MAX_CHANNELS > 10U)
#if (SENT_INST0_CHAN10 == STD_ON)
    ,SENT10 
#else /* (SENT_INST0_CHAN10  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN10  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 10U) */

#if (SENT_HW_MAX_CHANNELS > 11U)
#if (SENT_INST0_CHAN11 == STD_ON)
    ,SENT11 
#else /* (SENT_INST0_CHAN11  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN11  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 1U) */

#if (SENT_HW_MAX_CHANNELS > 12U)
#if (SENT_INST0_CHAN12 == STD_ON)
    ,SENT12 
#else /* (SENT_INST0_CHAN12  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN12  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 12U) */

#if (SENT_HW_MAX_CHANNELS > 13U)
#if (SENT_INST0_CHAN13 == STD_ON)
    ,SENT13 
#else /* (SENT_INST0_CHAN13  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN13  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 13U) */

#if (SENT_HW_MAX_CHANNELS > 14U)
#if (SENT_INST0_CHAN14 == STD_ON)
    ,SENT14 
#else /* (SENT_INST0_CHAN14  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN14  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 14U) */

#if (SENT_HW_MAX_CHANNELS > 15U)
#if (SENT_INST0_CHAN15 == STD_ON)
    ,SENT15 
#else /* (SENT_INST0_CHAN15  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN15  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 15U) */

#if (SENT_HW_MAX_CHANNELS > 16U)
#if (SENT_INST0_CHAN16 == STD_ON)
    ,SENT16 
#else /* (SENT_INST0_CHAN16  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN16  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 16U) */

#if (SENT_HW_MAX_CHANNELS > 17U)
#if (SENT_INST0_CHAN17 == STD_ON)
    ,SENT17 
#else /* (SENT_INST0_CHAN17  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN17  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 17U) */

#if (SENT_HW_MAX_CHANNELS > 18U)
#if (SENT_INST0_CHAN18 == STD_ON)
    ,SENT18 
#else /* (SENT_INST0_CHAN18  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN18  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 18U) */

#if (SENT_HW_MAX_CHANNELS > 19U)
#if (SENT_INST0_CHAN19 == STD_ON)
    ,SENT19 
#else /* (SENT_INST0_CHAN19  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN19  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 3U) */

#if (SENT_HW_MAX_CHANNELS > 20U)
#if (SENT_INST0_CHAN20 == STD_ON)
    ,SENT20 
#else /* (SENT_INST0_CHAN20  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN20  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 20U) */

#if (SENT_HW_MAX_CHANNELS > 21U)
#if (SENT_INST0_CHAN21 == STD_ON)
    ,SENT21 
#else /* (SENT_INST0_CHAN21  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN21  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 21U) */

#if (SENT_HW_MAX_CHANNELS > 22U)
#if (SENT_INST0_CHAN22 == STD_ON)
    ,SENT22 
#else /* (SENT_INST0_CHAN22  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN22  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 22U) */

#if (SENT_HW_MAX_CHANNELS > 23U)
#if (SENT_INST0_CHAN3 == STD_ON)
    /* #Violation: Sent_c_REF_2 */
    ,SENT23 
#else /* (SENT_INST0_CHAN23  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN23  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 23U) */

#if (SENT_HW_MAX_CHANNELS > 24U)
#if (SENT_INST0_CHAN24 == STD_ON)
    ,SENT24 
#else /* (SENT_INST0_CHAN24  \== STD_ON) */
    ,NULL_PTR
#endif /* (SENT_INST0_CHAN24  \== STD_ON) */
#endif /* (SENT_HW_MAX_CHANNELS \> 24U) */
};

/* #Violation: Sent_c_REF_8 */
#define SENT_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED 
/* #Violation: Sent_c_REF_1 */
#include "Sent_MemMap.h" 

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/* #Violation: Sent_c_REF_8 */
#define SENT_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8 
/* #Violation: Sent_c_REF_1 */
#include "Sent_MemMap.h" 

/* Variable to hold the pointers to variables holding core specific
   states */
#if (SENT_DEV_ERROR_DETECT == STD_ON)
static uint8 Sent_GblCoreState[MCAL_NUMBER_OF_CORES];
#endif

/* #Violation: Sent_c_REF_8 */
#define SENT_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8 
/* #Violation: Sent_c_REF_1 */
#include "Sent_MemMap.h" 

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#if (SENT_DEV_ERROR_DETECT == STD_ON)
/* function to verify DET check */
static Std_ReturnType Sent_lDetCheck (uint8 ServiceID, 
                              Sent_ChannelIdxType ChannelId);
/* Function for validate the requested configuration */
static Std_ReturnType Sent_lInitDetCheck(const Sent_ConfigType *const CfgPtr,
                                                  const Mcal_CoreType CoreId);
#endif

/* Function to initialize the Core specific SENT Module */
static void Sent_lCoreInit(const Mcal_CoreType CoreId, const Sent_ConfigType *const ConfigPtr);

static void Sent_ReadChStatus(const Sent_ChannelIdxType HwUnitId,
                              Sent_ChanStatusType *const StatePtr);

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/* Mapping the code */
/* #Violation: Sent_c_REF_8 */
#define SENT_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Sent_c_REF_1 */
#include "Sent_MemMap.h" 

/****************************************************************************************************
*   Function Name           : Sent_Init
*
*   Service ID              : 0x00.
*
*   Description             : This function:
*                             - Initializes the SENT Module, Baud Rate registers
*                             - Also configures the respective Channels registers
*                     
*   Parameters in           : ConfigPtr: Pointer to SENT driver configuration set.
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
/* #Violation: Sent_c_REF_5 */
void Sent_Init
(
    const Sent_ConfigType *const ConfigPtr
)
{
    Mcal_CoreType CoreId;
#if (SENT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrStatus;
#endif /* SENT_DEV_ERROR_DETECT == STD_ON */

    /* Get core id which is executing currently */
    /* #Violation: Sent_c_REF_3 */
    CoreId = Mcal_GetCoreId(); 

#if (SENT_DEV_ERROR_DETECT == STD_ON)
    /* Do the initialization DET checks */
    ErrStatus = Sent_lInitDetCheck(ConfigPtr, CoreId);
    /* Check all DET is passed */
    if(ErrStatus != E_NOT_OK)
#endif /* SENT_DEV_ERROR_DETECT == STD_ON */
    {
        /*Initialize master core variables*/
        Sent_lCoreInit(CoreId, ConfigPtr);

#if (SENT_DEV_ERROR_DETECT == STD_ON)
        /* Set Status to indicate that initialization is done */
        Sent_GblCoreState[CoreId]= SENT_INITIALIZED;
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */

        /* Take copy of passed global config pointer in master core */
        Sent_kConfigPtr = ConfigPtr;
    }
}

/****************************************************************************************************
*   Function Name           : Sent_SetChannel
*
*   Service ID              : 0x01
*
*   Description             : This function:
*                             - Enables/Disables the SENT Channel
*                     
*   Parameters in           : ChanId - SENT logical channel number
*                             Operation - SENT_ENABLE/SENT_DISABLE
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
/* #Violation: Sent_c_REF_5 */
void Sent_SetChannel
(
    const Sent_ChannelIdxType ChanId, 
    Sent_ChanOpType Operation
)
{
    boolean SentRet;

#if (SENT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrStatus;
    ErrStatus = Sent_lDetCheck(SENT_SID_SETCHANNEL, ChanId);
    if (E_OK == ErrStatus)
#endif
    {
        uint8 Channel;
        /*Extracting the physical channel ID*/
        Channel = Sent_kConfigPtr->Sent_PhysicalChanIdPtr[ChanId];
        if (Operation == SENT_ENABLE)
        {
            SentRet = Sent_Hal_Enable(Sent_BaseRegister[Channel]);
        }
        else
        {
            SentRet = Sent_Hal_Disable(Sent_BaseRegister[Channel]);
        }
        
#if (SENT_SAFETY_ENABLE == STD_ON)
        /* Check if the current register is securely written. */
        if (FALSE == SentRet)
        {
            (void)Det_ReportRuntimeError((uint16)SENT_MODULE_ID,
                                    SENT_MODULE_INSTANCE,
                                    SENT_SID_SETCHANNEL,
                                    SENT_E_INIT_FAILED);
        }
#else
        /* Just avoid MISRAC Rules */
        (void)SentRet;
#endif /* (SENT_SAFETY_ENABLE \== STD_ON) */ 
    }
}

/****************************************************************************************************
*   Function Name           : Sent_ReadData
*
*   Service ID              : 0x03
*
*   Description             : This function: 
*                             - reads the nibbles received in the Data register
*                     
*   Parameters in           : ChannelId - SENT Channel whose data has to be read
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Data that received.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Sent_c_REF_5 */
uint32 Sent_ReadData
(
    const Sent_ChannelIdxType ChannelId
)
{
    uint32 DataVal;
    Sent_ChannelIdxType Channel;
    Sent_Fast_Messagebuffer MessageBuffer;
    DataVal = SENT_ZERO_U;
#if (SENT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrStatus;

    ErrStatus = Sent_lDetCheck(SENT_SID_READDATA, ChannelId);
    if (E_OK == ErrStatus)
#endif
    {
        /*Extracting the physical channel ID*/
        Channel = Sent_kConfigPtr->Sent_PhysicalChanIdPtr[ChannelId];
        Sent_Hal_GetFastMessage(&MessageBuffer, Sent_BaseRegister[Channel]);
        DataVal = MessageBuffer.data;
    }
    
    return DataVal;
} 

/****************************************************************************************************
*   Function Name           : Sent_ReadSerialData
*
*   Service ID              : 0x04
*
*   Description             : This function:
*                             - reads the Serial data recieved and collected over
*                               several SENT frames
*                     
*   Parameters in           : ChannelId - SENT Channel's serial data has to be read
*
*   Parameters inout        : None.
*
*   Parameters out          : DataPtr -Data pointer pointing to the serial data read 
*                             from the SENT Channel.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Data that received.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None
****************************************************************************************************/
/* #Violation: Sent_c_REF_5 */
void Sent_ReadSerialData
(
    const Sent_ChannelIdxType ChannelId,
    Sent_RxSerialDataType *const DataPtr
)
{
    uint8 Channel;
    Sent_Slow_Messagebuffer MessageBuffer;
#if (SENT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrStatus;
#endif

#if (SENT_DEV_ERROR_DETECT == STD_ON)
    ErrStatus = Sent_lDetCheck(SENT_SID_READSERIALDATA, ChannelId);
    if (NULL_PTR == DataPtr)
    {
        /* Report to DET */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                        SENT_MODULE_INSTANCE,
                        SENT_SID_READSERIALDATA,
                        SENT_E_PARAM_POINTER);
    }
    else if (E_OK == ErrStatus)
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*Extracting the physical channel ID*/
        Channel = Sent_kConfigPtr->Sent_PhysicalChanIdPtr[ChannelId];
        Sent_Hal_GetSlowMessage(&MessageBuffer, Sent_BaseRegister[Channel]);
        DataPtr->Data = MessageBuffer.data;
        DataPtr->MsgId = MessageBuffer.messageID;
        DataPtr->Configuration = (uint8)MessageBuffer.slowType;
        DataPtr->Crc = MessageBuffer.crc;
    }
#if (SENT_DEV_ERROR_DETECT == STD_ON)
    else
    /* #Violation: Sent_c_REF_4 */
    {
        /* Do nothing */
    }
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
}

/****************************************************************************************************
*   Function Name           : Sent_ReadChannelStatus
*
*   Service ID              : 0x05
*
*   Description             : This function: 
*                             - reads the Channel status
*
*   Parameters in           : ChannelId - SENT Channel's status has to be read
*
*   Parameters inout        : None.
*
*   Parameters out          : StatPtr - Pointer pointing to the status of the SENT
*                             Channel.
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
/* #Violation: Sent_c_REF_5 */
void Sent_ReadChannelStatus
(
    const Sent_ChannelIdxType ChannelId,
    Sent_ChanStatusType *const StatPtr
)
{
    uint8 Channel;
#if (SENT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrStatus;

    ErrStatus = Sent_lDetCheck(SENT_SID_READCHANSTATUS, ChannelId);
    if (NULL_PTR == StatPtr)
    {
        /* Report to DET */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                        SENT_MODULE_INSTANCE,
                        SENT_SID_READCHANSTATUS,
                        SENT_E_PARAM_POINTER);
    }
    else if (E_OK == ErrStatus)
    {
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
        /*Extracting the physical channel ID*/
        Channel = Sent_kConfigPtr->Sent_PhysicalChanIdPtr[ChannelId];
        Sent_ReadChStatus(Channel, StatPtr);
#if (SENT_DEV_ERROR_DETECT == STD_ON)
    }
    else
    /* #Violation: Sent_c_REF_4 */
    {
        /* Do nothing */
    }
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
}

#if (SENT_SPC_USED == STD_ON)
/****************************************************************************************************
*   Function Name           : Sent_SpcGenPulse
*
*   Service ID              : 0x06
*
*   Description             : This function:
*                             - generates a Master pulse for SPC Sync transmission
*
*   Parameters in           : ChannelId - SENT Channel's status has to be read
*
*   Parameters inout        : None.
*
*   Parameters out          : None
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
/* #Violation: Sent_c_REF_5 */
void Sent_SpcGenPulse
(
    const Sent_ChannelIdxType ChanId
)
{
    /* check if Transaction is in progress, before proceeding !!! */
    uint8 Channel;
    uint8 ChanIdx;
    const Sent_ChannelCfgType * ChanPtr;
    MultiCoreID CoreId;
    boolean SentRet;
#if (SENT_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType ErrStatus;

    ErrStatus = Sent_lDetCheck(SENT_SID_SPCGENPULSE, ChanId);
    if (E_OK == ErrStatus)
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /*Extract the index of channel configuration and the channel configuration*/
        ChanIdx = Sent_kConfigPtr->Sent_ChannelLookUpTablePtr[ChanId].Sent_ChannelIndex;
        CoreId = Sent_kConfigPtr->Sent_ChannelLookUpTablePtr[ChanId].Sent_ChannelCore;

        ChanPtr = Sent_kConfigPtr->SentCorePtr[CoreId]->Sent_ChannelConfigPtr;
        /*Extracting the physical channel ID*/
        Channel = Sent_kConfigPtr->Sent_PhysicalChanIdPtr[ChanId];

        SentRet = Sent_Hal_EnableSpc(Sent_BaseRegister[Channel], ChanPtr[ChanIdx].SpcPlusWidth);

#if (SENT_SAFETY_ENABLE == STD_ON)
        /* Check if the current register is securely written. */
        if (FALSE == SentRet)
        {
            (void)Det_ReportRuntimeError((uint16)SENT_MODULE_ID,
                                    SENT_MODULE_INSTANCE,
                                    SENT_SID_SPCGENPULSE,
                                    SENT_E_INIT_FAILED);
        }
#else
        /* Just avoid MISRAC Rules */
        (void)SentRet;
#endif /* (SENT_SAFETY_ENABLE \== STD_ON) */ 
    } 
}
#endif /* (SENT_SPC_USED  \== STD_ON) */

#if (SENT_DEINIT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Sent_DeInit
*
*   Service ID              : 0x07
*
*   Description             : This function:
*                             - De-Initializes the SENT Module and it's registers,
*                             - also with respective Channels registers
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None
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
/* #Violation: Sent_c_REF_5 */
void Sent_DeInit
(
    void
)
{
    Std_ReturnType              RetStatus;
    Sent_ChannelIdxType         ChanIndex;
    Sent_ChannelIdxType         ChannelId;
    Sent_ChannelIdxType         Channels;
    Rcc_ModuleRst               rstModule;
    const Sent_ChannelCfgType*  lChannelConfigPtr;

    RetStatus = E_OK;
    /* Get core Id which is currently executing */
    /* #Violation: Sent_c_REF_3 */
    const MultiCoreID CoreId = Mcal_GetCoreId(); 

#if (SENT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the channel is in uninitialized state */
    if (SENT_INITIALIZED != (Sent_GblCoreState[CoreId]))
    {
        /* Report to DET */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                            SENT_MODULE_INSTANCE,
                            SENT_SID_DEINIT,
                            SENT_E_UNINIT);
    }
    else
#endif /* SENT_DEV_ERROR_DETECT == STD_ON */
    {
        /* Core specific configuration pointer */
        lChannelConfigPtr = Sent_kConfigPtr->SentCorePtr[CoreId]->Sent_ChannelConfigPtr;
        Channels = Sent_kConfigPtr->SentCorePtr[CoreId]->MaxChannels;
        for (ChanIndex = SENT_ZERO_U; (ChanIndex < Channels)&&(E_OK == RetStatus); ChanIndex++)
        {
            /*Physical channel ID of the channel */
            ChannelId = lChannelConfigPtr[ChanIndex].ChanId;

            /* Sent Kernel Reset to set registers to default value */
            /* #Violation: Sent_c_REF_3 */
            /* #Violation: Sent_c_REF_2 */
            rstModule = SENT_GET_RCC_RST_NUM(Sent_BaseRegister[ChannelId]);

            SENT_ENTER_CRITICAL_SECTION(DeInit);
            RetStatus = Mcal_GetLock(MCAL_LOCK_ID_RCC);
            if(E_OK == RetStatus)
            {
                (void)Rcc_Hal_TrigModuleRst(rstModule); 
                Mcal_ReleaseLock(MCAL_LOCK_ID_RCC);
            }
            SENT_EXIT_CRITICAL_SECTION(DeInit);
        }
#if(SENT_DEV_ERROR_DETECT == STD_ON)
        if(E_OK == RetStatus)
        {
            Sent_GblCoreState[CoreId]= SENT_UNINITIALIZED;
        }
        else
        {
            /* Report to DET */
            (void)Det_ReportError((uint16)SENT_MODULE_ID,
                                SENT_MODULE_INSTANCE,
                                SENT_SID_DEINIT,
                                SENT_E_DEINIT_FAILED);
        }
#endif /* SENT_DEV_ERROR_DETECT == STD_ON */
    }
}
#endif /* SENT_DEINIT_API == STD_ON */

#if (SENT_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Sent_GetVersionInfo
*
*   Service ID              : 0x08
*
*   Description             : This function returns the version information of this
*                             module.The version information include : Module ID,
*                             Vendor ID,Vendor specific version numbers
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None
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
/* #Violation: Sent_c_REF_5 */
void Sent_GetVersionInfo
(
    Std_VersionInfoType *const VersionInfo
)
{
#if (SENT_DEV_ERROR_DETECT == STD_ON )
    if ((VersionInfo) == NULL_PTR)
    {
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                        SENT_MODULE_INSTANCE,
                        SENT_SID_GETVERINFO,
                        SENT_E_PARAM_POINTER);
    }
    else
#endif /* (SENT_DEV_ERROR_DETECT \== STD_ON )  */
    {
        VersionInfo->moduleID = SENT_MODULE_ID;
        VersionInfo->vendorID = SENT_VENDOR_ID;
        VersionInfo->sw_major_version = (uint8)SENT_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = (uint8)SENT_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = (uint8)SENT_SW_PATCH_VERSION;
    }
}
#endif /*( (SENT_VERSION_INFO_API  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Sent_Receive_ISRHandler
*
*   Service ID              : 0x09
*
*   Description             : This function:
*                             - is the interrupt handler and collects the status
*                             of the relevant channels and inform the user
*
*   Parameters in           : IntrNode - Interrupt Node number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None
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
void Sent_Receive_ISRHandler
(
    uint8 IntrNode
)
{
    Sent_ChannelIdxType PhyChId;
    Sent_ChannelIdxType LogicChId;
    Sent_ChanStatusType ChanStatus;
    uint8 CoreId;
    uint8 CoreCh;
    const Sent_CoreConfigType *CorePtr;
    const Sent_ChannelCfgType * ChanPtr;

    PhyChId = IntrNode;
    /* #Violation: Sent_c_REF_3 */
    CoreId = (uint8)Mcal_GetCoreId(); 

#if (SENT_DEV_ERROR_DETECT == STD_ON)
    if((NULL_PTR != Sent_kConfigPtr) && (PhyChId < SENT_HW_MAX_CHANNELS))
    {
#endif /* (SENT_DEV_ERROR_DETECT \== STD_ON) */
        CorePtr = Sent_kConfigPtr->SentCorePtr[CoreId];

#if (SENT_DEV_ERROR_DETECT == STD_ON)
        if(CorePtr != NULL_PTR)
        {
#endif /* (SENT_DEV_ERROR_DETECT \== STD_ON) */

            ChanPtr = CorePtr->Sent_ChannelConfigPtr;
            /* get the SENT logic channel id */
            LogicChId = Sent_kConfigPtr->Sent_LogicalChanIdPtr[PhyChId];

#if (SENT_DEV_ERROR_DETECT == STD_ON)
            if((0xFFU != LogicChId) && (NULL_PTR != ChanPtr))
            {
                if(NULL_PTR != Sent_kConfigPtr->Sent_ChannelLookUpTablePtr)
                {
#endif /* (SENT_DEV_ERROR_DETECT \== STD_ON) */
                    CoreCh = Sent_kConfigPtr->Sent_ChannelLookUpTablePtr[LogicChId].Sent_ChannelIndex;

                    Sent_ReadChStatus(PhyChId, &ChanStatus);

                    /* Notify when event occur when function is configured*/
                    if(ChanPtr[CoreCh].CallbackFn != NULL_PTR)
                    {
                        ChanPtr[CoreCh].CallbackFn(LogicChId, &ChanStatus);
                    }
#if (SENT_DEV_ERROR_DETECT == STD_ON)
                }
            }
        }
    }
    else
    {
        /* Report to DET */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                            SENT_MODULE_INSTANCE,
                            SENT_SID_RECVISR,
                            SENT_E_INVALID_CHANNEL);
    }
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
}

/****************************************************************************************************
*   Function Name           : Sent_Error_ISRHandler
*
*   Service ID              : 0x0a
*
*   Description             : This function:
*                             - is the interrupt handler and collects the status
*                             of the relevant channels and inform the user
*
*   Parameters in           : IntrNode - Interrupt Node number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None
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
void Sent_Error_ISRHandler
(
    uint8 IntrNode
)
{
    Sent_ChannelIdxType PhyChId;
    Sent_ChannelIdxType LogicChId;
    Sent_ChanStatusType ChanStatus;
    uint8 CoreId;
    const Sent_CoreConfigType *CorePtr;
    const Sent_ChannelCfgType * ChanPtr;

    PhyChId = IntrNode;
    /* #Violation: Sent_c_REF_3 */
    CoreId = (uint8)Mcal_GetCoreId(); 

#if (SENT_DEV_ERROR_DETECT == STD_ON)
    if((NULL_PTR != Sent_kConfigPtr) && (PhyChId < SENT_HW_MAX_CHANNELS))
    {
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
        CorePtr = Sent_kConfigPtr->SentCorePtr[CoreId];
#if (SENT_DEV_ERROR_DETECT == STD_ON)
        if(CorePtr != NULL_PTR)
        {
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
            ChanPtr = CorePtr->Sent_ChannelConfigPtr;
            /* get the SENT logic channel id */
            LogicChId = Sent_kConfigPtr->Sent_LogicalChanIdPtr[PhyChId];
#if (SENT_DEV_ERROR_DETECT == STD_ON)
            if((0xFFU != LogicChId) && (NULL_PTR != ChanPtr))
            {
                if(NULL_PTR != Sent_kConfigPtr->Sent_ChannelLookUpTablePtr)
                {
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
                    const uint8 CoreCh = Sent_kConfigPtr->Sent_ChannelLookUpTablePtr[LogicChId].Sent_ChannelIndex;
                    Sent_ReadChStatus(PhyChId, &ChanStatus);
                    /* Notify the Application */
                    if(ChanPtr[CoreCh].CallbackErrFn != NULL_PTR)
                    {
                        ChanPtr[CoreCh].CallbackErrFn(LogicChId, &ChanStatus);
                    }
#if (SENT_DEV_ERROR_DETECT == STD_ON)
                }
            }
        }
    }
    else
    {
        /* Report to DET */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                            SENT_MODULE_INSTANCE,
                            SENT_SID_ERRISR,
                            SENT_E_INVALID_CHANNEL);
    }
#endif /* (SENT_DEV_ERROR_DETECT  \== STD_ON) */
}

/*******************************************************************************
**                      Local Function Definitions                            **
*******************************************************************************/

/****************************************************************************************************
*   Function Name           : Sent_lDetCheck
*
*   Service ID              : 0x20
*
*   Description             : This function:
*                             - checks whether SENT module is initialized or not
*                             - also verifies if the SENT channel has been       
*                               configured or not. Raising DET if error.          
*                             - also verifies if the OutPtr is not NULL        
*
*   Parameters in           : ServiceID - Informs Service ID of an API
*                             ChannelId - SENT logical channel number
*                             OutPtr    - The pointer that will be checked.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: No DET error occurred                             
*                             E_NOT_OK: DET error occurred                           
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
#if (SENT_DEV_ERROR_DETECT == STD_ON)
static Std_ReturnType Sent_lDetCheck
(
    uint8 ServiceID, 
    Sent_ChannelIdxType ChannelId
)
{
    Std_ReturnType RetVal;
    MultiCoreID CoreId;
    Sent_ChannelIdxType PhyChId;

#if(MCAL_NUMBER_OF_CORES > SENT_ONE_U)
    MultiCoreID CoreCh;
#endif /* (MCAL_NUMBER_OF_CORES \> SENT_ONE_U) */

    RetVal = E_OK;
    /* #Violation: Sent_c_REF_3 */
    CoreId = Mcal_GetCoreId();

    if ((Sent_GblCoreState[(uint8)CoreId]) == SENT_UNINITIALIZED)
    {
        /* Report to DET */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                        SENT_MODULE_INSTANCE,
                        ServiceID,
                        SENT_E_UNINIT);
        RetVal = E_NOT_OK;
    }
    else if(ChannelId >= SENT_HW_MAX_CHANNELS)
    {
        /* Report to DET */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                        SENT_MODULE_INSTANCE,
                        ServiceID,
                        SENT_E_INVALID_CHANNEL);
        RetVal = E_NOT_OK;
    }
    /*check if the channel is configuration is available*/
    else if(ChannelId >= SENT_MAX_CHANNELS_CONFIGURED)
    {
        /* Report to DET */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                        SENT_MODULE_INSTANCE,
                        ServiceID,
                        SENT_E_CHANNEL_NOT_CONFIGURED);
        RetVal = E_NOT_OK;
    }
    /*check for the channel status except for the set channel and
    read channel status APIs*/
    else if((ServiceID != SENT_SID_SETCHANNEL) &&
            (ServiceID != SENT_SID_READCHANSTATUS))
    {
        /*Extracting the physical channel ID*/
        PhyChId = Sent_kConfigPtr->Sent_PhysicalChanIdPtr[ChannelId];
        if(SENT_HW_MAX_CHANNELS > PhyChId)
        {
            if(SENT_MODULE_ENABLED != Sent_Hal_ChannelUsing(Sent_BaseRegister[PhyChId]))
            {
                /* Report to DET */
                (void)Det_ReportError((uint16)SENT_MODULE_ID,
                                SENT_MODULE_INSTANCE,
                                ServiceID,
                                SENT_E_CHANNEL_NOT_ENABLED);
                RetVal = E_NOT_OK;
            }
        }
        else
        {
            /* Report to DET */
            (void)Det_ReportError((uint16)SENT_MODULE_ID,
                            SENT_MODULE_INSTANCE,
                            ServiceID,
                            SENT_E_INVALID_CHANNEL);
            RetVal = E_NOT_OK;
        }
    }
    else
    /* #Violation: Sent_c_REF_4 */
    {
        /*Do nothing*/
    }
    /* Extract the channel assigned as per core */
#if(MCAL_NUMBER_OF_CORES > SENT_ONE_U)
    if (RetVal == E_OK)
    {
        /*Get the core ID assigend with the channel*/
        CoreCh = Sent_kConfigPtr->Sent_ChannelLookUpTablePtr[ChannelId].
            Sent_ChannelCore;
        /* Report to DET */
        /* Check if channel is assigned to core */
        if (CoreCh != CoreId)
        {
            (void)Det_ReportError((uint16)SENT_MODULE_ID,
                            SENT_MODULE_INSTANCE,
                            ServiceID,
                            SENT_E_CORE_CHANNEL_MISMATCH);
            RetVal = E_NOT_OK;
        }
    }
#endif /* (MCAL_NUMBER_OF_CORES \> SENT_ONE_U) */
    return RetVal;
}
#endif

/****************************************************************************************************
*   Function Name           : Sent_lCoreInit
*
*   Service ID              : 0x21
*
*   Description             : This function initialize all variables
*                             used by the SENT driver module to an initial state.
*                     
*   Parameters in           : ConfigPtr: Pointer to flash driver configuration set.
*                             CoreId : Core Number.
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
static void Sent_lCoreInit
(
    const Mcal_CoreType CoreId, const Sent_ConfigType *const ConfigPtr
)
{
    Sent_ChannelIdxType ChanIndex;
    Sent_ChannelIdxType PhyChannelId;
    const Sent_CoreConfigType *CorePtr;
    boolean SentRet;

    /* Core specific configuration pointer */
    CorePtr = ConfigPtr->SentCorePtr[CoreId];

    /* Initialize the core-x variables */
    /* Reset all core variables to "0" */
    /* Set the core status to IDLE */
    for (ChanIndex = SENT_ZERO_U; ChanIndex < CorePtr->MaxChannels; ChanIndex++)
    {
        /* Retrieve the SENT Physical channel id */
        PhyChannelId = CorePtr->Sent_ChannelConfigPtr[ChanIndex].ChanId;
        /* Consolidate the same Interrupt node for all interrupts specific to a
           channel */
        if (SENT_HW_MAX_CHANNELS > PhyChannelId)
        {
            SentRet = Sent_Hal_Init(&CorePtr->Sent_ChannelConfigPtr[ChanIndex].Config, Sent_BaseRegister[PhyChannelId]);

#if (SENT_SPC_USED == STD_ON)
            if((CorePtr->Sent_ChannelConfigPtr[ChanIndex].EnableSpc != 0U) && (TRUE == SentRet))
            {
                SentRet = Sent_Hal_InitSpc(CorePtr->Sent_ChannelConfigPtr[ChanIndex].SpcConfigPtr, Sent_BaseRegister[PhyChannelId]);
            }
#if (SENT_SAFETY_ENABLE == STD_ON)
            /* Check if the current register is securely written. */
            if (FALSE == SentRet)
            {
                (void)Det_ReportRuntimeError((uint16)SENT_MODULE_ID,
                                        SENT_MODULE_INSTANCE,
                                        SENT_SID_INIT,
                                        SENT_E_INIT_FAILED);
            }
#else
            /* Just avoid MISRAC Rules */
            (void)SentRet;
#endif /* (SENT_SAFETY_ENABLE \== STD_ON) */ 
                
#endif /* (SENT_SPC_USED  \== STD_ON) */
        }
    }
}

#if (SENT_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Sent_lInitDetCheck
*
*   Service ID              : 0x21
*
*   Description             : Local function :Service for DET check in Sent_Init() function.
*                     
*   Parameters in           : CfgPtr: Pointer to SENT driver configuration set.
*                             CoreId : Core Number.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : ErrorFlag (uint32).
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static Std_ReturnType Sent_lInitDetCheck
(
    const Sent_ConfigType *const CfgPtr,
    const Mcal_CoreType CoreId
)
{
    Std_ReturnType ErrStatus;
    /* Initialize the return variable */
    ErrStatus = E_OK;
    /* Check validity of configPtr */
    /* Det Check for NULL pointer  */
    if (NULL_PTR == CfgPtr)
    {
        /* Report to DET upon error, Init has been called with wrong
           parameter NULL Config Pointer */
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                        SENT_MODULE_INSTANCE,
                        SENT_SID_INIT,
                        SENT_E_INIT_FAILED);
        /* Report Error */
        ErrStatus = E_NOT_OK;
    }

    /* Check if current core is initialized */
    else if(SENT_UNINITIALIZED != Sent_GblCoreState[CoreId])
    {
        (void)Det_ReportError((uint16)SENT_MODULE_ID,
                        SENT_MODULE_INSTANCE,
                        SENT_SID_INIT,
                        SENT_E_ALREADY_INITIALIZED);
        /* Report Error */
        ErrStatus = E_NOT_OK;
    }
    else
    /* #Violation: Sent_c_REF_4 */
    {
        /* Do nothing */
    }

    return ErrStatus;
}
#endif

/****************************************************************************************************
*   Function Name           : Sent_ReadChStatus
*
*   Service ID              : 0x22
*
*   Description             : Local function :Service for read channel status.
*                     
*   Parameters in           : HwUnitId - SENT Channel's status has to be read
*
*   Parameters inout        : None.
*
*   Parameters out          : StatePtr - Pointer pointing to the status of the SENT
*                             Channel.
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
static void Sent_ReadChStatus
(
    const Sent_ChannelIdxType  HwUnitId,
    Sent_ChanStatusType *const StatePtr
)
{
    uint32 ChStatus;
    ChStatus = Sent_Hal_GetStatus(Sent_BaseRegister[HwUnitId]);

    if((SENT_FAST_CRC_ERROR & ChStatus) == 0U)
    {
        StatePtr->IsCRCErr = 0U;
    }
    else
    {
        StatePtr->IsCRCErr = 1U;
    }
    if((SENT_FAST_FORMAT_ERROR & ChStatus) == 0U)
    {
        StatePtr->IsFrameErr   = 0U;
    }
    else
    {
        StatePtr->IsFrameErr   = 1U;
    }
    if((SENT_SLOW_CRC_ERROR & ChStatus) == 0U)
    {
        StatePtr->IsSlowCRCErr   = 0U;
    }
    else
    {
        StatePtr->IsSlowCRCErr   = 1U;
    }
    if((SENT_SLOW_FORMAT_ERROR & ChStatus) == 0U)
    {
        StatePtr->IsSlowFrameErr = 0U;
    }
    else
    {
        StatePtr->IsSlowFrameErr =1U;
    }
    if((SENT_RECEIVE_SLOW_MESSAGE & ChStatus) == 0U)
    {
        StatePtr->IsSlowDone     = 0U;
    }
    else
    {
        StatePtr->IsSlowDone     = 1U;
    }
    if((SENT_RECEIVE_FAST_MESSAGE & ChStatus) == 0U)
    {
        StatePtr->IsDone     = 0U;
    }
    else
    {
        StatePtr->IsDone     = 1U;
    }
}

/* #Violation: Sent_c_REF_8 */
#define SENT_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Sent_c_REF_1 */
#include "Sent_MemMap.h" 
/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/

