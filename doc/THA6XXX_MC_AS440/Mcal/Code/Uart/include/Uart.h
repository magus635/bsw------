/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Uart.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : ASI
 *
 *   brief                 : This file contains all type definitions of Uart Driver
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
*#Uart_h_REF_1:MISRAC2012-Rule-20.7;
* Justification:Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Uart_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*/

/**************************************************************************************************/
#ifndef UART_H_
#define UART_H_
/***************************************************************************************************
*                               Includes
***************************************************************************************************/
#include "Uart_Cfg.h"
#include "Uart_GeneralTypes.h"
#include "Uart_Version.h"
#include "Uart_PBcfg.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#if (UART_DEV_ERROR_DETECT == STD_ON)
/* Error Values */
/* API service used without module initialization. */
#define UART_E_UNINIT                           ((uint8)0x00U)
/* API service used module already initialization. */
#define UART_E_ALREADY_UNINIT                   ((uint8)0x01U)
/* API service used with an invalid or inactive channel parameter. */
#define UART_E_INVALID_CHANNEL                  ((uint8)0x02U)
/* API service called with invalid configuration pointer. */
#define UART_E_INVALID_POINTER                  ((uint8)0x03U)
/* API service called with a NULL pointer. */
#define UART_E_PARAM_POINTER                    ((uint8)0x05U)

/* Non-AUTOSAR */
/* Report DET UART module not configured for current Core */
#define UART_E_CORE_NOT_CONFIGURED              ((uint8)0xE0U)
/* UART channel is not allocated to current core */
#define UART_E_CORE_CHANNEL_MISMATCH            ((uint8)0xE1U)

/* Service IDs */
#define UART_SID_INIT                           ((uint8)0x00U)
#define UART_SID_DEINIT                         ((uint8)0x01U)
#define UART_SID_GETVERSIONINFO                 ((uint8)0x02U)
#define UART_SID_GETSTATUS                      ((uint8)0x03U)
#define UART_SID_WRITE                          ((uint8)0x04U)
#define UART_SID_READ                           ((uint8)0x05U)
#define UART_SID_GOTOSLEEP                      ((uint8)0x06U)
#define UART_SID_WAKEUP                         ((uint8)0x07U)

/* Non-AUTOSAR */
#ifdef UART_CFG_ERROR_INTERRUPT_ENABLE
/* SID for UART interrupt service function(error interrupt) */
/* #Violation: Uart_h_REF_2 */
#define UART_SID_ISR_ERROR                      ((uint8)0xE0U)
#endif /* UART_CFG_ERROR_INTERRUPT_ENABLE */

#ifdef UART_CFG_TX_INTERRUPT_ENABLE
/* SID for UART interrupt service function(receive interrupt) */
/* #Violation: Uart_h_REF_2 */
#define UART_SID_ISR_SEND                       ((uint8)0xE1U)
#endif /* UART_CFG_TX_INTERRUPT_ENABLE */

#ifdef UART_CFG_RX_INTERRUPT_ENABLE
/* SID for UART interrupt service function(send interrupt) */
/* #Violation: Uart_h_REF_2 */
#define UART_SID_ISR_RECV                       ((uint8)0xE2U)
#endif /* UART_CFG_RX_INTERRUPT_ENABLE */

#endif /* (UART_DEV_ERROR_DETECT  \== STD_ON) */
/****************************************************************************************************
**                          Global Macro Definitions -- Mask: Get Status                           **
****************************************************************************************************/
/* Mask: Noise detected in the received character */
/* #Violation: Uart_h_REF_2 */
#define UART_NOISE_FLAG                     ASI_UART_NOISE_FLAG
/* Mask: Data transfer completed */
#define UART_TX_COMPLETED_FLAG              ASI_UART_TX_COMPLETED_FLAG
/* Mask: There is data to be received */
#define UART_RX_COMPLETED_FLAG              ASI_UART_RX_COMPLETED_FLAG
/* Mask: Receive buffer overflow */
/* #Violation: Uart_h_REF_2 */
#define UART_FIFO_BUFFER_OVERRUN_FLAG       ASI_UART_FIFO_BUFFER_OVERRUN_FLAG
/* Mask: Hardware framing error */
/* #Violation: Uart_h_REF_2 */
#define UART_FRAMING_ERROR_FLAG             ASI_UART_FRAMING_ERROR_FLAG
/* Mask: Buffer data is ready to be read by software */
/* #Violation: Uart_h_REF_2 */
#define UART_BUFFER_DATA_READY_FLAG         ASI_UART_BUFFER_DATA_READY_FLAG
/* Mask: Parity Error */
/* #Violation: Uart_h_REF_2 */
#define UART_PARITY_ERROR_FLAG              ASI_UART_PARITY_ERROR_FLAG
/* Mask: Output compare error */
/* #Violation: Uart_h_REF_2 */
#define UART_OUTPUT_COMPARE_FLAG            ASI_UART_OUTPUT_COMPARE_FLAG
/* Mask: Sticky Zero Error */
/* #Violation: Uart_h_REF_2 */
#define UART_STACK_AT_ZERO_FLAG             ASI_UART_STACK_AT_ZERO_FLAG
/* Mask: Get all errors */
#define UART_ALL_FLAGS                      ASI_UART_ALL_FLAGS
/* Mask: Clear all errors */
#define UART_CLEAR_ALL_FLAGS                ASI_UART_CLEAR_ALL_FLAGS
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Uart_h_REF_2 */
#define UART_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Uart_h_REF_1 */
#include "Uart_MemMap.h"

extern FUNC(void, UART_PUBLIC_CODE) Uart_Init
(
    CONSTP2CONST(Uart_ConfigType, AUTOMATIC, UART_APPL_CONST) ConfigPtr
);

extern FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_DeInit
(
   void
);

#if (UART_VERSION_INFO_API == STD_ON)
extern FUNC(void, UART_PUBLIC_CODE) Uart_GetVersionInfo
(
    /* #Violation: Uart_h_REF_1 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, UART_APPL_DATA) VersionInfoPtr
);
#endif

extern FUNC(Uart_StatusType, UART_PUBLIC_CODE) Uart_GetStatus
(
    Uart_ChannelType Channel
);

extern FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_Write
(
    Uart_ChannelType                  Channel,
    CONSTP2CONST(Uart_DataBufferType, AUTOMATIC, UART_APPL_DATA) DataBufferPtr,
    Uart_DataLengthType               LengthToWrite
);

extern FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_Read
(
    Uart_ChannelType           Channel,
    CONSTP2VAR(Uart_DataBufferType, AUTOMATIC, UART_APPL_DATA) DataBufferPtr
);

extern FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_GoToSleep
(
    Uart_ChannelType    Channel
);

extern FUNC(Std_ReturnType, UART_PUBLIC_CODE) Uart_WakeUp
(
    Uart_ChannelType    Channel
);

#if (UART_CFG_RX_INTERRUPT_ENABLE == STD_ON)
extern FUNC(void, UART_PUBLIC_CODE) Uart_Rx_ISRHandler
(
    Uart_HwUnitType HwUnit
);
#endif /* \(UART_CFG_RX_INTERRUPT_ENABLE == STD_ON) */

#if (UART_CFG_TX_INTERRUPT_ENABLE == STD_ON)
extern FUNC(void, UART_PUBLIC_CODE) Uart_Tx_ISRHandler
(
    Uart_HwUnitType HwUnit
);
#endif /* \(UART_CFG_TX_INTERRUPT_ENABLE == STD_ON) */

#if (UART_CFG_ERROR_INTERRUPT_ENABLE == STD_ON)
extern FUNC(void, UART_PUBLIC_CODE) Uart_Error_ISRHandler
(
    Uart_HwUnitType HwUnit
);
#endif /* \(UART_CFG_ERROR_INTERRUPT_ENABLE == STD_ON) */
/* #Violation: Uart_h_REF_2 */
#define UART_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Uart_h_REF_1 */
#include "Uart_MemMap.h"

#endif /* UART_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/
