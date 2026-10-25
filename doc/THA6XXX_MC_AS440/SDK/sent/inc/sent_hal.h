/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    sent_hal.h
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
#ifndef SENT_HAL_H_
#define SENT_HAL_H_

/*
*#Violation Summary
*#sent_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: Reserved macros for upper layer application.

*#sent_hal_h_REF_2:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#sent_hal_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#sent_hal_h_REF_4:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#sent_hal_h_REF_5:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "sent_register.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^SENT_RFDATA_DATA_MASK^ Mask for data in RFDATA register */
#define SENT_RFDATA_DATA_MASK (0x0FFFFFF0U)
/* ^SENT_RFDATA_DATA_OFFSET^ Offset for data in RFDATA register */
#define SENT_RFDATA_DATA_OFFSET (4U)
/* ^SENT_SHORT_SERIAL_ID^ Short serial message identification in RX_SLOWST*/
/* #Violation: sent_hal_h_REF_1 */
#define SENT_SHORT_SERIAL_ID (17U)
/* ^SENT_ENHANCED_ID^ Enhanced message identification in RX_SLOWST*/
/* #Violation: sent_hal_h_REF_1 */
#define SENT_ENHANCED_ID (19U)
/* ^SENT_STATUS_MASK^ Sent Status Mask */
#define SENT_STATUS_MASK (0x60F0U)
/* ^Sent_Status^ Indicate the Sent Status */
/* #Violation: sent_hal_h_REF_1 */
#define SENT_FAST_CRC_ERROR (0x10U)
/* #Violation: sent_hal_h_REF_1 */
#define SENT_FAST_FORMAT_ERROR (0x20U)
/* #Violation: sent_hal_h_REF_1 */
#define SENT_SLOW_CRC_ERROR (0x40U)
/* #Violation: sent_hal_h_REF_1 */
#define SENT_SLOW_FORMAT_ERROR (0x80U)
/* #Violation: sent_hal_h_REF_1 */
#define SENT_RECEIVE_FAST_MESSAGE (0x4000U)
/* #Violation: sent_hal_h_REF_1 */
#define SENT_RECEIVE_SLOW_MESSAGE (0x2000U)
/* ^SENT_SYNCPULERRSTATUS_MASK^ Sent Status2 Mask */
/* #Violation: sent_hal_h_REF_1 */
#define SENT_SYNCPULERRSTATUS_MASK (0x3U)
/* ^Sent_SyncPulErrStatus^ Indicate the Sent Status2 */
/* #Violation: sent_hal_h_REF_1 */
#define SENT_SP25E (0x1U)
/* ^Sent Msel^ Indicate Sent mode */
#define SENT_MSEL_GTM_TRIGGER (0x1U)
#define SENT_MSEL_INTERNAL_TRIGGER (0x10000U)

#define SENT_REG_CHECK
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* SENT CRC type */
typedef enum
{
    SENT_CRC_TYPE_2010 = 0U, /* Recommended CRC (J2716 2010 or newer spec) */
    SENT_CRC_TYPE_2007       /* Original Legacy CRC (J2716 2007 spec) */
} Sent_CRC_Type;

/* Determine whether CRC calculation include status nibble. */
typedef enum
{
    SENT_CRC_WITH_OUT_STATUS = 0U, /* CRC checksum calculate data nibbles only */
    SENT_CRC_WITH_STATUS           /* CRC checksum calculate include status and data nibbles. */
} Sent_CRC_With;

/* Enable CRC check for SENT message */
typedef enum
{
    SENT_CRC_ENABLE_OFF = 0U, /* CRC check is turned off */
    SENT_CRC_ENABLE_ON        /* Low Polarity activation */
} Sent_CRC_Enable;

/* The number of nibbles in data valid from 1 to 6 */
typedef enum
{
    SENT_NIBBLES_NUM_1= 1U, /* Specifies received the number of data nibbles is 1 */
    SENT_NIBBLES_NUM_2,     /* Specifies received the number of data nibbles is 2 */
    SENT_NIBBLES_NUM_3,     /* Specifies received the number of data nibbles is 3 */
    SENT_NIBBLES_NUM_4,     /* Specifies received the number of data nibbles is 4 */
    SENT_NIBBLES_NUM_5,     /* Specifies received the number of data nibbles is 5 */
    SENT_NIBBLES_NUM_6      /* Specifies received the number of data nibbles is 6 */
} Sent_Nibble;

/* Enable/Disable expected pause after crc  */
typedef enum
{
    SENT_PAUSE_DISABLE = 0U, /* Pause is not expected after crc  */
    SENT_PAUSE_ENABLE        /* Pause is expected after crc */
} Sent_Pause;

/* The edge detection polarity */
typedef enum
{
    SENT_POLARITY_RISING = 0U, /* detect the rising edge in receiving data */
    SENT_POLARITY_FALLING      /* detect the falling edge in receiving data */
} Sent_Polarity;

/* Indicate type of message in slow channel */
typedef enum
{
    SENT_SLOW_TYPE_NO = 0U,    /* no message in slow channel */
    SENT_SLOW_TYPE_SHORT,      /* short serial message in slow channel */
    SENT_SLOW_TYPE_ENHANCED12, /* enhanced12 message in slow channel */
    SENT_SLOW_TYPE_ENHANCED16, /* enhanced16 message in slow channel */
    SENT_SLOW_TYPE_ALL         /* received message in slow channel, maybe short serial, enhanced12 or enhanced16 message */
} Sent_Slow_Type;

/* Indicate type of message in slow channel */
typedef enum
{
    SENT_TRIGGER_MODE_SPC = 0U, /* Spc trigger mode */
    SENT_TRIGGER_MODE_GTM       /* Gtm trigger mode */
} Sent_Trigger_Mode;

/* Gtm enable channel */
typedef enum
{
    SENT_GTM_CHANNEL_0 = 0U, /* Gtm Channel 0 */
    SENT_GTM_CHANNEL_1,      /* Gtm Channel 1 */
    SENT_GTM_CHANNEL_2,      /* Gtm Channel 2 */
    SENT_GTM_CHANNEL_3,      /* Gtm Channel 3 */
    SENT_GTM_CHANNEL_4,      /* Gtm Channel 4 */
    SENT_GTM_CHANNEL_5,      /* Gtm Channel 5 */
    SENT_GTM_CHANNEL_6,      /* Gtm Channel 6 */
    SENT_GTM_CHANNEL_7,      /* Gtm Channel 7 */
    SENT_GTM_CHANNEL_8,      /* Gtm Channel 8 */
    SENT_GTM_CHANNEL_9,      /* Gtm Channel 9 */
    SENT_GTM_CHANNEL_10,     /* Gtm Channel 10 */
    SENT_GTM_CHANNEL_11,     /* Gtm Channel 11 */
    SENT_GTM_CHANNEL_12,     /* Gtm Channel 12 */
    SENT_GTM_CHANNEL_13,     /* Gtm Channel 13 */
    SENT_GTM_CHANNEL_14,     /* Gtm Channel 14 */
}Sent_Gtm_Channel;

/* Sent enable status */
typedef enum
{
    SENT_MODULE_DISABLED = 0U, /* Module disable */
    SENT_MODULE_ENABLED        /* Module enable */
}Sent_Enable_Status;

/* Sent message reception status */
typedef enum
{
    SENT_MESSAGE_NONE = 0U, /* No message */
    SENT_MESSAGE_MISSED,   /* Message miss */
    SENT_MESSAGE_RECEIVED  /* Message received */
}Sent_Message_Status;

/* Determine whether data reception valid interrupt mask */
typedef enum
{
    SENT_VALIDINT_DISMASK = 0U, /* Dismask valid interrupt */
    SENT_VALIDINT_MASK          /* Mask valid interrupt */
}Sent_ValidInt;

/* Determine whether data reception error interrupt mask */
typedef enum
{
    SENT_ERRORINT_DISMASK = 0U, /* Dismask error interrupt */
    SENT_ERRORINT_MASK          /* Mask error interrupt */
}Sent_ErrorInt;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* fast channel message buffer. */
typedef struct
/* #Violation: sent_hal_h_REF_2 */
/* #Violation: sent_hal_h_REF_3 */
{
    uint8 status; /* received status value from fast channel */
    uint8 crc;    /* received crc value from fast channel */
    uint32 data;  /* contains the data value from fast channel */
} Sent_Fast_Messagebuffer;

/* slow channel message buffer. */
typedef struct
/* #Violation: sent_hal_h_REF_2 */
/* #Violation: sent_hal_h_REF_3 */
{
    uint8 messageID;         /* received messageID from slow channel */
    uint8 crc;               /* received crc value from slow channel */
    uint16 data;             /* contains the data value from slow channel */
    Sent_Slow_Type slowType; /* contains the type of slow message */
} Sent_Slow_Messagebuffer;

/* Crc Configuration structure */
typedef struct
{
    Sent_CRC_Type crcType;     /* CRC type used in SENT */
    Sent_CRC_With crcWith;     /* CRC include status nibble or not */
    Sent_CRC_Enable crcEnable; /* CRC check turn on or turn off  */
} Sent_CRC_Config;

/* SPC initialize Configuration */
typedef struct
/* #Violation: sent_hal_h_REF_2 */
/* #Violation: sent_hal_h_REF_3 */
{
    Sent_Trigger_Mode triggerMode; /* The trigger mode (SPC or GTM)  */
    uint16 tickTime;               /* per tick time in clock of SPC  */
    Sent_Gtm_Channel gtmChannel;   /* Gtm channel for triggering SPC */
    uint32 timeOut;                /* Time out time for Gtm trigger */
}Sent_Spc_Config;

/* Initial configuration structure for SENT */
typedef struct
/* #Violation: sent_hal_h_REF_3 */
{
    Sent_CRC_Config crcConfig; /* CRC configuration */
    Sent_Nibble nibbleNum;     /* Number of nibbles in the data */
    Sent_Pause pause;          /* Pause pulse will be expect after crc */
    Sent_Polarity polarity;    /* The idle polarity of receive data */
    uint16 rsynMax;            /* Maximum number of clocks in ticks  */
    uint16 rsynMin;            /* Minimum number of clocks in ticks */
    Sent_ValidInt validIntSta; /* Valid interrupt mask configuration, THA6104 is supported,
                                  but THA6206 and THA6412 are not supported */
    Sent_ErrorInt errorIntSta; /* Error interrupt mask configuration, THA6104 is supported,
                                  but THA6206 and THA6412 are not supported */
} Sent_Config;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: sent_hal_h_REF_4 */
#define SENT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: sent_hal_h_REF_5 */
#include "Sent_MemMap.h"

/**********************************************************************************************************************
 * Function:     Sent_Register_ReadBack_Check
 * Description:  Register read back check
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        state: Original state
 *               expect: The value expected to be written
 *               value: The value actually written
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/05/29    01359     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Sent_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(SENT_REG_CHECK)
LOCAL_FORCEINLINE boolean Sent_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Sent_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Sent_Hal_Init
 * Description:  Configure Sent module for one channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different SENT modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pSentConfig: SENT configuration structure array
 *               pSentModule: indicate Sent module channel
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/28    01321     Create
 *********************************************************************************************************************/
extern boolean Sent_Hal_Init(const Sent_Config *const pSentConfig, SENT_MODULE *const pSentModule);

/**********************************************************************************************************************
 * Function:     Sent_Hal_InitSpc
 * Description:  Configure Spc module for one channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different SENT modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pSpcConfig: SPC configuration structure array
 *               pSentModule: indicate Sent module channel
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/28    01321     Create
 *********************************************************************************************************************/
extern boolean Sent_Hal_InitSpc(const Sent_Spc_Config *const pSpcConfig, SENT_MODULE *const pSentModule);

/**********************************************************************************************************************
 * Function:     Sent_Hal_Enable
 * Description:  Enable Sent channel for receiving only for not using SPC
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different SENT modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pSentModule: indicate Sent module channel
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/28    01321     Create
 *********************************************************************************************************************/
extern boolean Sent_Hal_Enable(SENT_MODULE *const pSentModule);

/**********************************************************************************************************************
 * Function:     Sent_Hal_Disable
 * Description:  Disable Sent channel for receiving only for not using SPC
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different SENT modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pSentModule: indicate Sent module channel
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/28    01321     Create
 *********************************************************************************************************************/
extern boolean Sent_Hal_Disable(SENT_MODULE *const pSentModule);

/**********************************************************************************************************************
 * Function:     Sent_Hal_GetFastMessage
 * Description:  Return the message information that is received in the fast channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSentModule: indicate Sent module channel
 *               pFastMessage: Fast message buffer
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/28    01321     Create
 *********************************************************************************************************************/
extern void Sent_Hal_GetFastMessage(Sent_Fast_Messagebuffer *const pFastMessage, const SENT_MODULE *const pSentModule);

/**********************************************************************************************************************
 * Function:     Sent_Hal_GetSlowMessage
 * Description:  Return the message information that is received in the slow channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSentModule: indicate Sent module channel
 *               pSlowMessage: Slow message buffer
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/28    01321     Create
 *********************************************************************************************************************/
extern void Sent_Hal_GetSlowMessage(Sent_Slow_Messagebuffer *const pSlowMessage, const SENT_MODULE *const pSentModule);

/**********************************************************************************************************************
 * Function:     Sent_Hal_EnableSpc (uint16 tickNum)
 * Description:  trigger a spc pulse
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different SENT modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pSentModule: indicate Sent module channel
 *               tickPeriod: total tick time for SPC trigger
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/28    01321     Create
 *********************************************************************************************************************/
extern boolean Sent_Hal_EnableSpc(SENT_MODULE *const pSentModule, uint8 tickPeriod);

/**********************************************************************************************************************
 * Function:     Sent_Hal_GetStatus
 * Description:  Get the Status for a specific channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different SENT modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pSentModule: indicate Sent module channel
 * Inout:        None
 * Output:       None
 * Return:       uint32: sentStatus
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/28    01321     Create
 *********************************************************************************************************************/
extern uint32 Sent_Hal_GetStatus(const SENT_MODULE *const pSentModule);

/**********************************************************************************************************************
 * Function:     Sent_Hal_ChannelUsing
 * Description:  Get the Status of Channel is using.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSentModule: indicate Sent module channel
 * Inout:        None
 * Output:       None
 * Return:       Sent_Enable_Status: enableStatus
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/20    01321     Create
 *********************************************************************************************************************/
extern Sent_Enable_Status Sent_Hal_ChannelUsing(const SENT_MODULE *const pSentModule);

/**********************************************************************************************************************
 * Function:     Sent_Hal_GetGTMReceiveStatus
 * Description:  Get the Status of Channel whether it received message.(SPC triggered by GTM)
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSentModule: indicate Sent module channel
 * Inout:        None
 * Output:       None
 * Return:       Sent_Message_Status: message Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/20    01321     Create
 *********************************************************************************************************************/
extern Sent_Message_Status Sent_Hal_GetGTMReceiveStatus(const SENT_MODULE *const pSentModule);

#if defined(THA6_THA6104)
/**********************************************************************************************************************
 * Function:     Sent_Hal_GetSyncPulErrStatus
 * Description:  Get the Sync Pulse Error Status for a specific channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different SENT modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pSentModule: indicate Sent module channel
 * Inout:        None
 * Output:       None
 * Return:       uint32: Sync Pulse Error Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/18    01359     Create
 *********************************************************************************************************************/
extern uint32 Sent_Hal_GetSyncPulErrStatus(const SENT_MODULE *const pSentModule);
#endif

/* #Violation: sent_hal_h_REF_4 */
#define SENT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: sent_hal_h_REF_5 */
#include "Sent_MemMap.h"
#endif /* SENT_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/    
