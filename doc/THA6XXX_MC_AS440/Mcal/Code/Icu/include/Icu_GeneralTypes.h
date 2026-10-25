/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Icu_GeneralTypes.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-TIM
 *
 *   brief                 : This file contains all functions of Icu Driver
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
*#Icu_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity 
*#Icu_GeneralTypes_h_REF_3:MISRAC2012-Rule-2.3;
* Justification: Reserved types are defined in AUTOSAR specifications.
*
*#Icu_GeneralTypes_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity;
*
*#Icu_GeneralTypes_h_REF_4:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for share buffer. Data integrity and correctness will be ensured
* by code review.
*
*/

#ifndef ICU_GENERALTYPES_H_
#define ICU_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* \[SWS_Icu_00276]  conflict with [SWS_BSW_00024]
We choose to follow the specifications of BSW, include Std_Types.h */
#include "Std_Types.h"
#include "Icu_Cfg.h"
#include "Mcall.h"
#include "gtm_icu_hal.h"
#if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
/* ICU implements a wake-up function, and according to the specification(SWS_Icu_00213), 
*  this header file needs to be include */
#include "EcuM.h"
/* ICU implements a wake-up function, and according to the specification(SWS_Icu_00213), 
*  this header file needs to be include */
#include "EcuM_Externals.h"
#endif/* (ICU_WAKEUP_FUNCTIONALITY_API \== STD_ON) */ 

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/

/* \[SWS_Icu_00278] Numeric identifier of an ICU Channel */
typedef uint8        Icu_ChannelType;

/* \[SWS_Icu_00290] Width of the buffer for storing time in terms of timer ticks  */
typedef uint32       Icu_ValueType;

/* \[SWS_Icu_00292] Type to abstract the return value of the service Icu_GetTimestampIndex() */
typedef uint16       Icu_IndexType;

/* \[SWS_Icu_00293] Type to abstract the return value of the service Icu_GetEdgeNumbers() */
typedef uint32       Icu_EdgeNumberType;

/* \[SWS_Icu_00294] Definition of the measurement mode type */
typedef Gtm_Icu_Mode Icu_MeasurementModeType;

/****************************************************************************************************
**                          Global Enumration Definitions                                          **
****************************************************************************************************/
/* \[SWS_Icu_00279] Input state of an ICU channel */
typedef enum
{
    ICU_IDLE = 0U,
    ICU_ACTIVE
} Icu_InputStateType;

/* \[SWS_Icu_00289] Definition of the type of activation edge of an ICU Channel */
typedef enum
{
    ICU_FALLING_EDGE = 0U,
    ICU_RISING_EDGE,
    ICU_BOTH_EDGES
} Icu_ActivationType;

/* \[SWS_Icu_00295] Definition of the signal measurement property type */
typedef enum
{
    ICU_LOW_TIME = 0U,
    ICU_HIGH_TIME,
    ICU_PERIOD_TIME,
    ICU_DUTY_CYCLE
/* #Violation: Icu_GeneralTypes_h_REF_3 */
} Icu_SignalMeasurementPropertyType;

/* \[SWS_Icu_00296] Definition of the timestamp measurement property type */
typedef enum
{
    ICU_LINEAR_BUFFER = 0U,
    ICU_CIRCULAR_BUFFER
} Icu_TimestampBufferType;

/*initialization state of driver*/
typedef enum
{
    ICU_UNINITIALIZED = 0U,
    ICU_INITIALIZED
} Icu_InitStateType;

/* \[SWS_Icu_00277] Allow enabling / disabling of all interrupts which are not 
required for the ECU wakeup. */
typedef enum
{
    ICU_MODE_NORMAL = 0U,
    ICU_MODE_SLEEP
/* #Violation: Icu_GeneralTypes_h_REF_1 */
} Icu_ModeType;


/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* #Violation: Icu_GeneralTypes_h_REF_2 */
/* #Violation: Icu_GeneralTypes_h_REF_1 */
typedef struct
{
    /* index of all channel */
    uint8 ChannelID;
    /* \[SWS_Icu_00283] [SWS_Icu_00378]*/
    /* Pointer to callback notification function */
    /* \[SWS_Icu_00018] The Icu notification functions shall be configurable as function
    pointers within the initialization data structure (Icu_ConfigType)
    [SWS_Icu_00187] The Icu module's notification functions shall have no parameters and no
    return value.*/
    void (*IcuNotificationPtr)(void);
    /* Index of HW GTM-TIM module */
    Gtm_Tim_Index             Index;
    /*channel index inside the module*/
    Gtm_Tim_Ch_Index          ChannelNumber;
    /* \[SWS_Icu_00284] [SWS_Icu_00285]*/
    /* Low time,high time, period time,circular,linear*/
    uint8                     ChannelProperties;
    /* \[SWS_Icu_00088] The module Icu shall allow the configuration per channel of thedefinition on
     * which edge the period starts. 
     [SWS_Icu_00286] default edge can be used by counter mode*/
    const Gtm_Icu_Config     *Gtm_Icu_ConfigPtr;
    boolean                   IsWakeupChannel; /*indicate the wakeup channel*/
    /* \[SWS_Icu_00288] If, in the definition for each Channel within the
    Icu_ConfigType, the channel is configured as wakeup capable then the value
    transmitted to the EcuM shall be configurable*/
    uint32                    WakeupSourceCfgInfo;
} Icu_ChnConfigType;

/* #Violation: Icu_GeneralTypes_h_REF_2 */
/* #Violation: Icu_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Pointer to ICU driver channel configuration */
    const Icu_ChnConfigType *Icu_ChnConfigPtr;
} Icu_ChannelConfigType;

/* \[SWS_Icu_00291] Type which contains the values needed for calculating duty cycles */
typedef Gtm_Icu_DutyCycleResult Icu_DutyCycleType;

/*Structure to store Edge Counting channel data into RAM  */
typedef volatile struct
{
    Icu_EdgeNumberType IcuEdgeCount;/*Record the valid Edge*/
    uint8   IrqType;/*indicate the Irq type of channel*/
} Icu_EdgeCountRamType;

/* Structure to store Timestamp channel data into RAM*/
typedef volatile struct
{
    uint32                 *BufferPtr;/*Store the Buffer point*/
    uint16                  BufferSize;/*Store the Buffer size*/
    /*indicate the timestamp index of the given channel, which is the next to be written */
    Icu_IndexType           TimestampIndex;
    uint16                  TimestampsCounter;/* count the isr number */
    /* the notification will be invoked after isr number is triggered NotifyInterval times */
    uint16                  NotifyInterval;
    Icu_TimestampBufferType BufferType; /* indicate the buffer type. circular or linear */
/* #Violation: Icu_GeneralTypes_h_REF_1 */
} Icu_TimestampRamType;

/* Structure to store Signal Measurement channel data into RAM*/
typedef volatile struct
{
    /* the threshold between the occurrence of overflow and the execution of interrupt */
    uint32  IsrOverflowThreshold;
    /* Low time,high time, period time,etc. */
    uint8   MeasureProperty;
    /* has valid result */
    boolean HasValidInput;
    /* overflow is detected */
    boolean IsOverFlowDetect;
    uint8   IrqType;/*indicate the Irq type of channel*/
} Icu_PwmMeasureRamType;

typedef union 
/* #Violation: Icu_GeneralTypes_h_REF_4 */
{
  Icu_EdgeCountRamType Icu_EdgeCountRam;
  Icu_TimestampRamType Icu_TimeStampRam;
  Icu_PwmMeasureRamType Icu_PwmMeasureRam;
} Icu_ChannelDataType;

/* Structure to channel data into RAM*/
/* #Violation: Icu_GeneralTypes_h_REF_2 */
/* #Violation: Icu_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Channel data for specific measurement mode */
    Icu_ChannelDataType            ChannelData;
    /* The start edge for ICU channel */
    Gtm_Tim_Edge_Cap               Edge;         
    /* Has vaild edge */ 
    volatile Icu_InputStateType    ChannelStatus;
    /* The measure mode for channel timestamp, edge counter, etc. */
    Icu_MeasurementModeType        MeasurementMode;
    volatile boolean               IsChannelRunning;
    boolean                        NotificationEnable;
    boolean                        WakeupIsEnabled;
    boolean                        WakeupSourceIsSet;

} Icu_ChannelRamDataType;

/* #Violation: Icu_GeneralTypes_h_REF_2 */
/* #Violation: Icu_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Num of Gtm channels */
    Icu_ChannelType              MaxChannels;
    /* Icu Channel Configuration */
    const Icu_ChannelConfigType *Icu_ChannelConfigPtr;
} Icu_CoreConfigType;

/* #Violation: Icu_GeneralTypes_h_REF_1 */
typedef struct
{
    /* index of Execution core */
    uint8         CoreChIdx;
    /* Execution core */
    Mcal_CoreType ExecutionCore;
} Icu_MappingType;

/* #Violation: Icu_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Icu Mode */
    Icu_ModeType      Mode;
    /* initialization state of driver */
    Icu_InitStateType Icu_InitState;
} Icu_CoreStateType;

/* \[SWS_Icu_00280] [SWS_Icu_00281] [SWS_Icu_00039]*/
/* Data Structure for Icu for Initializing the Icu Module */
typedef struct
{
    /* The pointer to the core channel configuration */
    const Icu_CoreConfigType *CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* The pointer to the core channel mapping configuration */
    const Icu_MappingType    *IcuChannelIdxmapPtr;
    /* Pointer to hardware channel mapping with logic channel */
    const uint8*             IcuHwChannelMapPtr;
} Icu_ConfigType;

#endif /* ICU_GENERALTYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
