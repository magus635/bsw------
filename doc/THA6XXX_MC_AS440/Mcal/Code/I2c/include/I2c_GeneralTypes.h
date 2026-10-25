/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : I2c_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : I2C
*
*   brief                 : This file contains all type definitions of I2c Driver
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
*#I2c_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#I2c_GeneralTypes_h_REF_2:CertC-DCL12-C.;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*/


/**************************************************************************************************/
#ifndef I2C_GENERAL_TYPES_H_
#define I2C_GENERAL_TYPES_H_
/***************************************************************************************************
*                               Includes
***************************************************************************************************/
#include "ComStack_Types.h"
#include "I2c_Cfg.h"
#include "Mcall.h"
#include "i2c_hal.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* I2c Initialization status in each core */
typedef uint8 I2c_InitType;

/* Channel ID */
typedef uint8 I2c_ChannelType;

/* I2c hardware unit ID */
typedef uint8 I2c_HwUnitType;

/* I2c transmit data type */
typedef uint8 I2c_DataType;

/* Size of I2c transmit data. */
typedef uint16 I2c_SizeType;

/* The destination address of the transmission */
typedef uint16 I2c_SlaveAddrType;

/* I2c initialization parameter structure remapping */
typedef I2C_InitParameter       I2c_InitConfigType;

/* I2c status parameter enumeration remapping */
typedef I2c_Status  I2c_ConfigStatusType;              

/* I2c transmition parameter enumeration remapping */
typedef I2C_DeviceInfo  I2c_DeviceInfoType;    
/****************************************************************************************************
**                          Global Enumeration Definitions                                         **
****************************************************************************************************/
/*
Type : I2c_ChannelStatusType
This type defines a range of specific status for I2C Driver.
It informs about the I2C Driver status and can be obtained
calling the API service I2c_GetStatus.
*/
typedef enum
{
    /* The I2C Driver is not initialized. */
    I2C_UNINIT = 0U,
    /* The I2C Driver is idle. */
    I2C_IDLE,
    /* The I2C Driver is performing busy. */
    I2C_BUSY
} I2c_ChannelStatusType;

typedef enum
{
    /* Bus error. */
    I2C_BUS_ERR = 0U,
    /* Overrun error. */
    I2C_OVERRUN,
    /* TxFIFO overflow. */
    I2C_TX_OVERFLOW,
    /* RxFIFO underflow. */
    I2C_RX_UNDERFLOW,
    /* No ack. */
    I2C_NO_ACK,
    /* Arbitration lost. */
    I2C_ARBITRATION_LOST,
    /* Time out error */
    I2C_TIMEOUT
} I2c_ChannelErrorType;


typedef enum
{
    I2C_NO_OPERATION = 0U,
    /* I2c write mode */
    I2C_WRITE,
    /* I2c read mode */
    I2C_READ
} I2c_OperationType;
/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* #Violation: I2c_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: I2c_GeneralTypes_h_REF_2 */ 
{
    /* Data buffer pointer */
    I2c_DataType        *DataPtr;
    /* TRUE enable 10bit hardware address, FALSE is 7bit hardware address*/
    boolean             AddressMode;
    /* The number of total bytes to be transferred */
    I2c_SizeType        Size;
    /* I2c Slave Address */
    I2c_SlaveAddrType   SlaveAddress;
    /* I2c Operation */
    I2c_OperationType   Diraction;
} I2c_TransDataInfoType;

/* This type is used to flag the I2C channel information */
/* #Violation: I2c_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: I2c_GeneralTypes_h_REF_2 */ 
{
    /* Channel Transmit state */
    I2c_ChannelStatusType HwState;
    /* I2c Operation */
    I2c_OperationType I2c_Operation;
    /* I2c device information */
    I2c_DeviceInfoType DevInfo;
} I2c_ChannelInfoType;

/* Type definition for the I2c channel information of current core */
typedef struct
{
    /* I2c channel status */
    I2c_ChannelInfoType     *ChannelStatusPtr;
    /* I2c driver initialization status in current core */
    uint8                   *CoreInitStatusPtr;
} I2c_CoreStatusType;

typedef struct
/* #Violation: I2c_GeneralTypes_h_REF_2 */ 
{
    /* Pointer to I2c configuration Parameter */
    const I2c_InitConfigType        *HwConfigPtr;
    /* transfer notification function */
    void (*I2c_NotifFunctionPtr)(I2c_ChannelErrorType ErrorId);
    /* I2C Hardware Channel */
    I2c_HwUnitType                  HwUnitId;
    /* I2C Channel ID */
    uint8                           ChannelId;
} I2c_ChannelConfigType;

typedef struct
/* #Violation: I2c_GeneralTypes_h_REF_2 */
{
    /* Pointer to I2c configuration Parameter */
    const I2c_ChannelConfigType           *ChannelConfigPtr;
    /* Max channel number of specific core */
    const uint8                     CoreMaxChannels;
} I2c_InitCoreConfigType;

typedef struct
/* #Violation: I2c_GeneralTypes_h_REF_2 */ 
{
    /* Pointer to I2c configuration Parameter for map core */
    const I2c_InitCoreConfigType    *CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* I2c channel assigned to the core channel */
    const uint8                     *ChannelIdToCoreChIdPtr;
    /* HwUnit assigned to the I2c channel */
    const uint8                     *HwUnitToChannelIdPtr;
} I2c_ConfigType;

#endif /* I2C_GENERAL_TYPES_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/
