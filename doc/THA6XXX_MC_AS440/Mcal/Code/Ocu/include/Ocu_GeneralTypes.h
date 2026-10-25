/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Ocu_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : This file contains all type definitions of Ocu Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Ocu_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Ocu_GeneralTypes_h_REF_2:CertC-DCL12-C; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Ocu_GeneralTypes_h_REF_3:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef OCU_GENERALTYPES_H_
#define OCU_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Platform_Types.h"
#include "Mcall.h"
#include "gtm.h"
#include "Ocu_Cfg.h"

#include "gtm_ocu_hal.h"
/****************************************************************************************************
**                          Global Macros Definitions                                              **
****************************************************************************************************/

/* #Violation: Ocu_GeneralTypes_h_REF_3*/
#define     OCU_LOW                         GTM_SIGNALSTATE_LOW
#define     OCU_HIGH                        GTM_SIGNALSTATE_HIGH

/****************************************************************************************************
**                          Global basic type Definitions                                          **
****************************************************************************************************/
/* SWS_Ocu_00028:
   Numeric identifier of a OCU channel */
typedef uint32 Ocu_ChannelType;
/* SWS_Ocu_00029:
   Type for reading the counter and writing the threshold values  */
typedef uint32 Ocu_ValueType;
/* SWS_Ocu_00031:
   Output state of the pin linked to an OCU channel */
typedef Gtm_SignalState Ocu_PinStateType;

/****************************************************************************************************
**                          Global Enumration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    OCU_UNINITIALIZED = 0U,
    OCU_INITIALIZED
} Ocu_InitStateType;

typedef enum
{
    OCU_CHANNEL_STOPPED = 0U,
    OCU_CHANNEL_RUNNING
} Ocu_ChannelStateType;

/* SWS_Ocu_00032:
   Pin action to be performed on compare match */
typedef enum
{
    /* pin will remain at its current level */
    OCU_DISABLE = 0U,
    /* pin will be set HIGH */
    OCU_SET_HIGH = 1U,
    /* pin will be set LOW */
    OCU_SET_LOW = 2U,
    /* pin will be set to the opposite of its current level */
    OCU_TOGGLE = 3U
} Ocu_PinActionType;

/* SWS_Ocu_00138:
   Return information after setting a new threshold value. */
typedef enum
{
    /* compare match will occur Outside the current Reference Interval */
    OCU_CM_OUT_REF_INTERVAL = 0U,
    /* compare match will  occur Inside the current Reference Interval */
    OCU_CM_IN_REF_INTERVAL,
    /* compare match error */
    OCU_CM_REF_ERROR
} Ocu_ReturnType;

/* Compare match event class */
typedef enum
{
    /* compare match will operate pin level */
    OCU_COMPARE_EVENT_PIN = 0U,
    /* compare match will trigger adc */
    OCU_COMPARE_EVENT_ADC,
    /* compare match will trigger dma */
    OCU_COMPARE_EVENT_DMA
} Ocu_CompareEventType;

/* The hardware class of a logic ocu channel */
typedef enum
{
    OCU_HW_GTM_ATOM = 0U
} Ocu_HWType;


/****************************************************************************************************
**                          Global Structure Definitions                                          **
****************************************************************************************************/

/* Configuration type for hardware of GTM-ATOM */
/* #Violation: Ocu_GeneralTypes_h_REF_1*/
/* #Violation: Ocu_GeneralTypes_h_REF_2*/
typedef struct
{
    /* Channel Index structure */
    Gtm_Output_Driver        HWChannelIndex;
    /* Channel Configuration */
    Gtm_Ocu_Config           HWChannelConfig;
    /* Channel time base unit */
    Gtm_Tbu_Ch               TimeBase;
}Ocu_HWGtmAtomConfigType;

typedef struct
{
    /* Compare value for the channel */
    Ocu_ValueType           CompareValue;
    /* Interrupt status */
    boolean                 NotifyEnabled;
    /* Channel status */
    Ocu_ChannelStateType    ChannelStatus;
    /* Pin action */
    Ocu_PinActionType       OutputAction;
    /* Re-set compare value flag */
    boolean                 AtomReProg;
} Ocu_ChannelStatusType;

/* #Violation: Ocu_GeneralTypes_h_REF_1*/
/* #Violation: Ocu_GeneralTypes_h_REF_2*/
typedef struct
{
  /* Channel id */
  uint8                   ChannelId;
  /* Max counter value */
  uint32                  MaxCounterValue;
  /* Notification pointer */
  void                   (*NotificationPtr)(void);
  /* Output compare event class */
  Ocu_CompareEventType    Event;
  /* Default compare value */
  uint32                  DefaultCompareValue;
  /* Hardware class of a logic channel */
  Ocu_HWType              HWClass;
} Ocu_ChConfigType;

/* #Violation: Ocu_GeneralTypes_h_REF_1*/
/* #Violation: Ocu_GeneralTypes_h_REF_2*/
typedef struct
{
    /* Index of the core of the current channel */
    Mcal_CoreType               Core;
    /* Index of the channel of the current core */
    uint8                       IndexInCore;
    /* Hardware configuration mapping index */
    uint32                      HWCfgIndex;
} Ocu_MappingType;

/* #Violation: Ocu_GeneralTypes_h_REF_1*/
/* #Violation: Ocu_GeneralTypes_h_REF_2*/
typedef struct
{
  /* No of Gtm channels */
  uint8                         MaxChannels;
  /* Gpt Channel Configuration */
  const Ocu_ChConfigType*       Ocu_ChannelConfigPtr;
}Ocu_CoreConfigType;

/* SWS_Ocu_00033:
   The initialization data for the OCU driver */
/* #Violation: Ocu_GeneralTypes_h_REF_2*/
typedef struct
{
    /* The pointer to the core channel configuration */
    const Ocu_CoreConfigType*         CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* The pointer to the core channel mapping configuration */
    const Ocu_MappingType*            OcuChannelIdxmapPtr;
    /* Hardware channels configuration of all Ocu logic channel based on GTM-ATOM */
    const Ocu_HWGtmAtomConfigType*    Ocu_HWGtmAtomConfigPtr;
    /* Pointer to hardware channel mapping with logic channel */
    const uint8*                      OcuHwChannelMapPtr;
}Ocu_ConfigType;

#endif/*End of Ocu_GeneralTypes.h*/
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/



