/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : I2c.h
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
*#I2c_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#I2c_h_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for different configurations.
*
*#I2c_h_REF_3:MISRAC2012-Rule-20.7;
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*/

/**************************************************************************************************/
#ifndef I2C_H_
#define I2C_H_
/***************************************************************************************************
*                               Includes
***************************************************************************************************/
#include "I2c_GeneralTypes.h"
#include "I2c_Version.h"
#include "I2c_PBcfg.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#if (I2C_DEV_ERROR_DETECT == STD_ON)
/* Error Values */
/* I2C is not initialized */
#define I2C_E_UNINIT                    ((uint8)0x00U)
/* I2C is initialized */
#define I2C_E_INITIALIZED               ((uint8)0x01U)
/* Invalid channel ID */
#define I2C_E_INVALID_CHANNEL           ((uint8)0x02U)
/* Invalid slave address */
#define I2C_E_INVALID_SLAVE_ADDRESS     ((uint8)0x03U)
/* Invalid pointer */
#define I2C_E_PARAM_POINTER             ((uint8)0x04U)
/* Invalid date size */
#define I2C_E_INVALID_SIZE              ((uint8)0x05U)
/* Channel is busy */
#define I2C_E_CHANNEL_BUSY              ((uint8)0x06U)
/* Current core is not config */
#define I2C_E_CORE_NOT_CONFIGURED       ((uint8)0x07U)
/* I2C channel is not allocated to current core */
#define I2C_E_CORE_CHANNEL_MISMATCH     ((uint8)0x08U)

/* Service IDs */
#define I2C_SID_INIT                    ((uint8)0x00U)
#define I2C_SID_SYNCTRANS               ((uint8)0x02U)
#define I2C_SID_GETSTATUS               ((uint8)0x03U)
#define I2C_SID_GETVERSIONINFO          ((uint8)0x04U)
#endif /* (I2C_DEV_ERROR_DETECT  \== STD_ON) */

/* used for deinit API */
#if (I2C_CFG_DEINIT_API == STD_ON)
/* I2C deinit failed */
#define I2C_E_DEINIT_FAILED             ((uint8)0x09U)
#define I2C_SID_DEINIT                  ((uint8)0x01U)
#endif /* (I2C_CFG_DEINIT_API \= STD_ON) */

/* The maximum number of bits supported by I2c TxFIFO */
#define I2C_MAX_SUPPORTED_SIZE              ((uint16)0x3FFFU)
/* FIFO underflow */
#define I2C_UNDERFLOW                        ((uint32)0x20000U)
/* FIFO overflow */
#define I2C_OVERFLOW                        ((uint32)0x100000U)
/* Max value of 7 bit address */
#define I2C_7_BIT_MAX_SLAVE_ADD                ((uint8)0x7FU)
/* standard mode */
#define I2C_STANDARD_MODE                   ((uint32)0x186A0U)
/* fast mode: 400000Hz */
/* #Violation: I2c_h_REF_2 */ 
#define I2C_FAST_MODE                       ((uint32)0x61A80U)
/* fast plus mode: 1000000Hz */
/* #Violation: I2c_h_REF_2 */ 
#define I2C_FASTPLUS_MODE                   ((uint32)0xF4240U)
/* high speed mode: 3400000Hz */
/* #Violation: I2c_h_REF_2 */ 
#define I2C_HIGHSPEED_MODE                  ((uint32)0x33E140U)
/* master code */
#define I2C_MASTERCODE                      ((uint8)0x09U)
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
/* #Violation: I2c_h_REF_1 */ 
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL 
#include "I2c_MemMap.h" 

#if (I2C_VERSION_INFO_API == STD_ON)
extern FUNC(void, I2C_PUBLIC_CODE) I2c_GetVersionInfo
(
    /* #Violation: I2c_h_REF_3 */ 
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, I2C_APPL_DATA) VersionInfoPtr
);
#endif /* (I2C_VERSION_INFO_API  \== STD_ON) */

extern FUNC(void, I2C_PUBLIC_CODE) I2c_Init
(
    CONSTP2CONST(I2c_ConfigType, AUTOMATIC, I2C_APPL_CONST) ConfigPtr
);

#if (I2C_CFG_DEINIT_API == STD_ON)
extern FUNC(void, I2C_PUBLIC_CODE) I2c_DeInit
(
    void
);
#endif /* (I2C_CFG_DEINIT_API  \== STD_ON) */

extern FUNC(Std_ReturnType, I2C_PUBLIC_CODE) I2c_SyncTransmit
(
    const I2c_ChannelType Channel,
    CONSTP2CONST(I2c_TransDataInfoType, AUTOMATIC, I2C_APPL_DATA) DataInfoPtr
);

extern FUNC(I2c_ChannelStatusType, I2C_PUBLIC_CODE) I2c_GetStatus
(
    const I2c_ChannelType         Channel
);

/* #Violation: I2c_h_REF_1 */ 
#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL 
#include "I2c_MemMap.h" 

#endif /* I2C_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/
