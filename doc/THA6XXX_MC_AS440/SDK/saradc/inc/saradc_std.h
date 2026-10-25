/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    saradc_std.h
 * Author:      30037
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of internal functions.
 *********************************************************************************************************************/
#ifndef SARADC_STD_H_
#define SARADC_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "saradc_register.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/

/* SARADC converter resolution. */
typedef enum
{
    SARADC_RESOLUTION_12BIT = 0U, /* 12bit converter resolution. */
    SARADC_RESOLUTION_10BIT,      /* 10bit converter resolution. */
    SARADC_RESOLUTION_8BIT        /* 8bit converter resolution. */
} Saradc_Resolution;

/* When using synchronous conversion,take synchronous  group0(saradc0/saradc1/ saradc2/saradc3) as an example:
If saradc0 is master, saradc1 saradc2 and saradc3 are slave1 slave2 and slave3,respectively;
If saradc1 is master, saradc0  saradc2 and saradc3 are slave1 slave2 and slave3,respectively;
If saradc2 is master, saradc0 saradc1 and saradc3 are slave1 slave2 and slave3,respectively;
If saradc3 is master, saradc0 saradc1 and saradc2 are slave1 slave2 and slave3,respectively;
When using normal conversion, configure with SARADC_CONVERTER_MASTER */
typedef enum
{
    SARADC_CONVERTER_MASTER = 0U, /* Synchronous converter master / Normal converter. */
    SARADC_CONVERTER_SLAVE1,      /* Synchronous converter slave1. */
    SARADC_CONVERTER_SLAVE2,      /* Synchronous converter slave2. */
    SARADC_CONVERTER_SLAVE3       /* Synchronous converter slave3. */
} Saradc_ConverterSource;


/* Configure the timer triggering conversion mode. */
typedef enum
{
    SARADC_TIMERMODE_STOP = 0U,   /* Deactivate internal timer. */
    SARADC_TIMERMODE_FOLLOWTIMER, /* When the timer reaches a certain period, a conversion request is initiated. */
    SARADC_TIMERMODE_FOLLOWTIMER_ONLYONCE /* Only the first conversion is triggered by the timer, and then the
                                             conversion request is issued immediately after the queue is not empty */
} Saradc_TimerMode;

/* Saradc queue priority set. */
typedef enum
{
    SARADC_QUEUEPRIORITY_LOWEST = 0U, /* Lowest priority */
    SARADC_QUEUEPRIORITY_LOW,         /* Low priority */
    SARADC_QUEUEPRIORITY_HIGH,        /* High priority */
    SARADC_QUEUEPRIORITY_HIGHEST      /* Highest priority */
} Saradc_ArbiterPriority;

/* Saradc Conversion start mode set. */
typedef enum
{
    SARADC_STARTMODE_WAITFORSTART = 0U, /* Wait for start mode */
    SARADC_STARTMODE_CANCELINJECTREPEAT /* Cancel-Inject-Repeat mode */
} Saradc_StartMode;

/* Channel result register selection. */
typedef enum
{
    SARADC_CHANNELRESULT0 = 0U, /* Use Channel result register 0. */
    SARADC_CHANNELRESULT1,      /* Use Channel result register 1. */
    SARADC_CHANNELRESULT2,      /* Use Channel result register 2. */
    SARADC_CHANNELRESULT3,      /* Use Channel result register 3. */
    SARADC_CHANNELRESULT4,      /* Use Channel result register 4. */
    SARADC_CHANNELRESULT5,      /* Use Channel result register 5. */
    SARADC_CHANNELRESULT6,      /* Use Channel result register 6. */
    SARADC_CHANNELRESULT7,      /* Use Channel result register 7. */
    SARADC_CHANNELRESULT8,      /* Use Channel result register 8. */
    SARADC_CHANNELRESULT9,      /* Use Channel result register 9. */
    SARADC_CHANNELRESULT10,     /* Use Channel result register 10. */
    SARADC_CHANNELRESULT11,     /* Use Channel result register 11. */
    SARADC_CHANNELRESULT12,     /* Use Channel result register 12  */
    SARADC_CHANNELRESULT13,     /* Use Channel result register 13. */
    SARADC_CHANNELRESULT14,     /* Use Channel result register 14. */
    SARADC_CHANNELRESULT15      /* Use Channel result register 15. */
} Saradc_ChannelResult;


/* Saradc channel result storage mode setting. */
typedef enum
{
    SARADC_OVERWRITEMODE = 0U, /* Saradc over-write mode. */
    SARADC_WAITFORREADMODE     /* Saradc wait-for-read mode. */
} Saradc_StorageMode;


/* Request source queue select. */
typedef enum
{
    SARADC_REQUESTSOURCE_QUEUE0 = 0U, /* Select REQUEST SOURCE QUEUE0 . */
    SARADC_REQUESTSOURCE_QUEUE1,      /* Select REQUEST SOURCE QUEUE1. */
    SARADC_REQUESTSOURCE_QUEUE2       /* Select REQUEST SOURCE QUEUE2. */
} Saradc_RequestSource;

/* Channel select. */
typedef enum
{
    SARADC_CHANNELID_0 = 0U, /* Select Channel 0 to A/D convert. */
    SARADC_CHANNELID_1,      /* Select Channel 1 to A/D convert.. */
    SARADC_CHANNELID_2,      /* Select Channel 2 to A/D convert. */
    SARADC_CHANNELID_3,      /* Select Channel 3 to A/D convert. */
    SARADC_CHANNELID_4,      /* Select Channel 4 to A/D convert. */
    SARADC_CHANNELID_5,      /* Select Channel 5 to A/D convert. */
    SARADC_CHANNELID_6,      /* Select Channel 6 to A/D convert. */
    SARADC_CHANNELID_7,      /* Select Channel 7 to A/D convert. */
    SARADC_CHANNELID_8,      /* Select Channel 8 to A/D convert. */
    SARADC_CHANNELID_9,      /* Select Channel 9 to A/D convert. */
    SARADC_CHANNELID_10,     /* Select Channel 10 to A/D convert. */
    SARADC_CHANNELID_11,     /* Select Channel 11 to A/D convert. */
#if defined(THA6_THA6104)
    SARADC_CHANNELID_12,     /* Select Channel 12 to A/D convert. Active in THA6104, Reserved THA6206 and THA6412 */
    SARADC_CHANNELID_13,     /* Select Channel 13 to A/D convert. Active in THA6104, Reserved THA6206 and THA6412 */
    SARADC_CHANNELID_14,     /* Select Channel 14 to A/D convert. Active in THA6104, Reserved THA6206 and THA6412 */
    SARADC_CHANNELID_15      /* Select Channel 15 to A/D convert. Active in THA6104, Reserved THA6206 and THA6412 */
#endif /* end THA6_THA6104 */
} Saradc_ChannelID;

/* HDI */
typedef enum
{
    SARADC_HDI_OFF = 0U,/* HDI OFF */
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    SARADC_HDI_FC,      /* Enable FC HDI. */
#endif
    SARADC_HDI_GTM,     /* Enable GRM HDI. */
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    SARADC_HDI_RDC      /* Enable RDC HDI. */
#endif
} Saradc_Hdi;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Timer trigger queue mode config. */
typedef struct
{
    boolean enable;             /* 0:External trigger timer disable.1:External trigger timer enable. */
    uint8 sequence;             /* Set sequence timer value . */
    Saradc_TimerMode timermode; /* Set sequence timer mode . */
} Saradc_TriggerByTimerConfig;

/* Saradc queue config. */
typedef struct
{
    Saradc_ArbiterPriority priority;              /* Set arbiter priority. */
    Saradc_StartMode startMode;                   /* Set queue start mode. */
    boolean enable;                               /* 0: Arbitration queue disable 1: Arbitration queue enable */
} Saradc_QueueCommonConfig;



 #define ADC_START_SEC_CODE_ASIL_D_GLOBAL
 #include "Adc_MemMap.h"
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define SARADC_REG_CHECK
#if defined(SARADC_REG_CHECK)
LOCAL_FORCEINLINE boolean Saradc_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
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
LOCAL_FORCEINLINE boolean Saradc_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:    Saradc_Register_ReadBack_Check
 * Description: Checks whether the register value written is equal to the value read back
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       expect: Read back the value of the registe
 *              value: value written to register
 *              state: Wrong initial state
 * Inout:       None
 * Output:      None
 * Return:      boolean: Flag indicating whether the value written to register is the same as the value read back
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2025/03/10   01368     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Saradc_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect);

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Saradc_Std_AnalogConvertControl
 * Description:  Open/close the specified saradc Module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               enable: 0:close saradc, 1:open saradc
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_AnalogConvertControl(SARADC_MODULE *const pSaradc, boolean enable);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetSampleTime
 * Description:  Set sample time.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               sampleTime: sample time
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetSampleTime(SARADC_MODULE *const pSaradc, uint8 sampleTime);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetConverterSource
 * Description:  Set saradc synchronous converter source.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               converterSource: synchronous converter source
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetConverterSource(SARADC_MODULE *const pSaradc, Saradc_ConverterSource converterSource);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetQueueCommonConfig
 * Description:  Config specified queue arbiter priority tartmodeefill  queue enable/disable and diagnostic option.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               queueConfig: Config request queue.
 *               requestsource: request source queue
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetQueueCommonConfig(SARADC_MODULE *const pSaradc, const Saradc_QueueCommonConfig *const pCommonConfig, Saradc_RequestSource requestSource);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetStoreResult
 * Description:  Channel result register select.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module.
 *               channelID: channelID ID.
 *               channelResult: channel result register.
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetStoreResult(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, Saradc_ChannelResult channelResult);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetStorageMode
 * Description:  Channel storage mode config.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelResult:channel result.
 *               storageMode: storage mode config.
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetStorageMode(SARADC_MODULE *const pSaradc, Saradc_ChannelResult channelResult, Saradc_StorageMode storageMode);

/**********************************************************************************************************************
 * Function:     Saradc_Std_EnableDma
 * Description:  Channel result register dma enable control.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelResult:channel result.
 *               enableDma: Dma enable selection.
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_EnableDma(SARADC_MODULE *const pSaradc, Saradc_ChannelResult channelResult, boolean enableDma);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetAlign
 * Description:  Set the channel conversion result left/right alignment.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelResult:channel result.
 *               rightAlignedStorage: right/left alignment setting.
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetAlign(SARADC_MODULE *const pSaradc, Saradc_ChannelResult channelResult, boolean rightAlignedStorage);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetBoundaryRange
 * Description:  Select boundary range.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelResult:channel result.
 *               boundaryRange: 0:Less than the upper threshold, greater than the lower threshold.
 *                              1:Greater than the upper threshold, less than the lower threshold
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetBoundaryRange(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, boolean boundaryRange);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetBoundaryResultCtrl
 * Description:  Set boundary result control.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelResult:channel result.
 *               boundaryResultControl: 0:Data is discarded outside the threshold
 *                                      1:Data retention outside the threshold
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetBoundaryResultCtrl(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, boolean boundaryResultControl);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetSynchronizeRequest
 * Description:  Set the Synchronize conversion channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelID:channel ID
 *               enableSynchronize: Synchronize conversion channel enable
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetSynchronizeRequest(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, boolean enableSynchronize);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetHdiIf
 * Description:  Set the Synchronize conversion channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelID:channel ID
 *               hdiIfEn: HDI FC/RDC/GTM enable
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetHdiIf(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, Saradc_Hdi hdiIfEn);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetResolution
 * Description:  Select saradc converter resolution.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               resolution: converter resolution
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetResolution(SARADC_MODULE *const pSaradc, Saradc_Resolution resolution);

/**********************************************************************************************************************
 * Function:     Saradc_Std_SetDivider
 * Description:  Select saradc converter resolution.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               divider: converter divider
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Std_SetDivider(SARADC_MODULE *const pSaradc, uint8 divider);

#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"

#endif /* SARADC_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
