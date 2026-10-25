/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Gpt_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all type definitions of Gpt Driver
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
*#Gpt_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity 
*
*#Gpt_GeneralTypes_h_REF_2:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Gpt_GeneralTypes_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity;
*/

#ifndef GPT_GENERALTYPES_H_
#define GPT_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Gpt_Cfg.h"
#include "gtm_timer_hal.h"
#include "Mcall.h"
#include "basetimer_hal.h"
/* GPT implements a wake-up function, and according to the specification(SWS_Gpt_00406), 
*  this header file needs to be include */
#include "EcuM.h"
/* GPT implements a wake-up function, and according to the specification(SWS_Gpt_00406), 
*  this header file needs to be include */
#include "EcuM_Externals.h"
/****************************************************************************************************
**                          Global Macros Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Global basic type Definitions                                          **
****************************************************************************************************/
/* SWS_Gpt_00358:
 * Type describing the channel ID */
typedef uint8 Gpt_ChannelType;
/* SWS_Gpt_00359:
 * Type describing the channel value */
typedef uint32 Gpt_ValueType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    GPT_UNINITIALIZED = 0U,
    GPT_INITIALIZED
}Gpt_InitStateType;

/* SWS_Gpt_00360 */
typedef enum
{
    /* Normal operation mode of the GPT */
    GPT_MODE_NORMAL = 0x00U,
    /* Operation for reduced power operation mode. In sleep 
       mode only wakeup capable channels are available. */
    GPT_MODE_SLEEP  = 0x01U
} Gpt_ModeType;

/* Channel Status Type */
typedef enum
{
    GPT_CH_NOTSTARTED = 0x00U,
    GPT_CH_RUNNING,
    GPT_CH_STOPPED,
    GPT_CH_EXPIRED
} Gpt_ChannelStateType;

/* SWS_Gpt_00389: Predefine Timer Type */
typedef enum
{
    GPT_PREDEF_TIMER_1US_16BIT = 0x00U,
    GPT_PREDEF_TIMER_1US_24BIT,
    GPT_PREDEF_TIMER_1US_32BIT,
    GPT_PREDEF_TIMER_100US_32BIT
} Gpt_PredefTimerType;

/* Gpt_HWType */
typedef enum
{
    GPT_HW_GTM = 0x00U,
    GPT_HW_BASETIMER
} Gpt_HWType;

/****************************************************************************************************
**                          Global Structure Definitions                                          **
****************************************************************************************************/
typedef struct
{
  /* Gpt driver state of current core */
  Gpt_InitStateType      Gpt_InitState;
  /* Gpt mode state of current core */
  Gpt_ModeType           Gpt_ModeState;
  /* Variable to store the channel wakeup info due to which GPT woke up */
  EcuM_WakeupSourceType  Gpt_WakeupChannelInfo;
}Gpt_DriverStateType;

/* Channel Status Type */
typedef  struct
{
    /* Notification status */
    boolean                      NotifyStatus;
    /* Wakeup status */
    boolean                      WakeUpStatus;
    /* Channel status */
    Gpt_ChannelStateType         Status;
}Gpt_ChannelStatusType;

/* Channel Configuration Type for GTM hardware */
/* #Violation: Gpt_GeneralTypes_h_REF_1 */
/* #Violation: Gpt_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Channel Index */
    Gtm_Output_Driver           HwChannelIndex;
    /* Channel Configuration */
    Gtm_Timer_Config            HwChannelConfig;
}Gpt_GtmConfigType;

/* Channel configuration type for basetimer hardware */
/* #Violation: Gpt_GeneralTypes_h_REF_1 */
/* #Violation: Gpt_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Channel Index pointer */
    BASETIMER_MODULE* const       HwChannelIndexPtr;
    /* Channel Configuration */
    Basetimer_InitConfig          HwChannelConfig;
}Gpt_BasetimerConfigType;

/* Channel Configuration Type */
/* #Violation: Gpt_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Channel Id */
    uint8                       ChannelId;
    /* Wakeup enable flag */
    uint8                       WakeupEnable;
    /* Channel Max Ticks  */
    uint32                      MaxTickValue;
    /* Notification function pointer */
    void                        (*NotificationFuncPtr)(void);
    /* Wakeup information to EcuM_SetWakeupEvent */
    EcuM_WakeupSourceType       GptChannelWakeupInfo;
    /* Hardware class of logic channel */
    Gpt_HWType                  HwClass;
}Gpt_ChConfigType;

/* Channel Mapping Type */
/* #Violation: Gpt_GeneralTypes_h_REF_1 */
/* #Violation: Gpt_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Index of the core of the current channel */
    uint8                       Core;
    /* index of the channel of the current core */
    uint8                       Index;
    /* Hardware configuration mapping index */
    uint32                      HwCfgIndex;
} Gpt_MappingType;

/* Core Configuration Type */
/* #Violation: Gpt_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Number of GPT channel of current core */
    Gpt_ChannelType                MaxChannel;
    /* Gpt Channel Configuration */
    const Gpt_ChConfigType*        Gpt_ChannelConfigPtr;
}Gpt_CoreConfigType;

/* SWS_Gpt_00357: The GPT Static Configuration Type */
/* #Violation: Gpt_GeneralTypes_h_REF_2 */
typedef struct
{
    /* The pointer to the core channel configuration */
    const Gpt_CoreConfigType*                    CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* The pointer to the core channel mapping configuration */
    const Gpt_MappingType*                       GptChannelIdxmapPtr;
    /* Hardware configuration for channel based on GTM */
    const Gpt_GtmConfigType*                     GptHwGtmConfigPtr;
    /* Hardware configuration for channel based on base timer */
    const Gpt_BasetimerConfigType*               GptHwBaseTimerConfigPtr;
    /* Pointer to hardware channel mapping with logic channel */
    /* #Violation: Gpt_GeneralTypes_h_REF_2 */
    const uint8*                                 GptHwChannelMapPtr[2U];
    /* Base address of the hardware of the predefined timer */
    /* #Violation: Gpt_GeneralTypes_h_REF_2 */
    BASETIMER_MODULE* const                      GptPredefTimerPtr[2U];
}Gpt_ConfigType;

#endif/*End of Gpt_GeneralTypes.h*/
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/



