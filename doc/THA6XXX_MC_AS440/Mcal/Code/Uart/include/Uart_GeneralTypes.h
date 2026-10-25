/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Uart_GeneralTypes.h
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
*#Uart_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification:Apply such struct/union definitons to simplify the code structure 
* and reduce the code complexity 
*
*#Uart_GeneralTypes_h_REF_2:CertC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and 
* reduce the code complexity;
*
*/

/**************************************************************************************************/
#ifndef UART_GENERALTYPES_H_
#define UART_GENERALTYPES_H_
/***************************************************************************************************
 *                               Includes
 ***************************************************************************************************/
#include "Std_Types.h"
#include "Mcall.h"
#include "asi_hal.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* Type definition for uart channel ID. */
typedef uint8               Uart_ChannelType;

/* Type defines the ASIx HwUnit ID used by UartChannel. */
typedef uint8               Uart_HwUnitType;

/* Type defines the buffer type used by UartChannel. */
typedef uint8               Uart_DataBufferType;

/* Type defines the data length of UartChannel. */
typedef uint16              Uart_DataLengthType;

/* Type defines the uart channel status value. */
typedef uint32              Uart_StatusType;

/* Type redefinition ASIx HwUnit initialization parameter structure. */
typedef Asi_Uart_Config     Uart_HwUnitConfigType;
/****************************************************************************************************
**                          Global Enumeration Definitions                                         **
****************************************************************************************************/
/* Enumeration type defines UART driver working status. */
typedef enum
{
    UART_UNINITIALIZED = 0U,
    UART_INITIALIZED
}Uart_DriverStateType;
/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* Type definition UartChannel configuration information structure */
/* #Violation: Uart_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Uart_GeneralTypes_h_REF_2 */
{
    /* Uart Channel ID */
    Uart_ChannelType                ChannelID;
    /* Uart Hardware Channel */
    Uart_HwUnitType                 HwUnitId;
    /* Uart channel transmission data width (byte) */
    uint8                           DataWidth;
    /* Receive Interrupt Handler function */
    void          (*UartRxNotification)(uint16 RxData);
    /* Transmit Interrupt Handler function */
    void          (*UartTxNotification)(void);
    /* Error  Interrupt Handler function */
    void          (*UartErrorNotification)(uint32 Value);
    /* Uart (ASI) register configuration information */
    const Uart_HwUnitConfigType     *HwUnitConfigPtr;
} Uart_ChannelConfigType;

/* Type definition UART driver configuration information structure in Corex */
/* #Violation: Uart_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Uart_GeneralTypes_h_REF_2 */
{
    /* Maximum number of the channels allocated to Corex */
    uint8                           MaxCoreChannel;
    /* Pointer to the UartChannel configuration information structure in Corex*/
    const Uart_ChannelConfigType    *ChannelConfigPtr;
} Uart_CoreConfigType;

/* Type definition UART driver configuration information structure */
typedef struct
/* #Violation: Uart_GeneralTypes_h_REF_2 */
{
    /* Corex configuration information structure pointer */
    const Uart_CoreConfigType       *CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* Pointer to UartChannel to Corex mapping table */
    const uint8                     *ChannelToCorePtr;
    /* Pointer to the ASIx to UartChannel mapping table */
    const uint8                     *HwUnitToChannelIdPtr;
    /* Uart available ASI hardware unit mapping table */
    ASI_MODULE * const              *HwUnitMapPtr;
} Uart_ConfigType;

/* This type is used to flag the Uart channel information */
typedef struct
{
    /* Uart driver initialization status in current core */
    Uart_DriverStateType                 *CoreInitStatusPtr;
} Uart_CoreStatusType;
#endif /* UART_GENERALTYPES_H_ */
/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/
