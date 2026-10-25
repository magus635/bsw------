/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Pwm_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : This file contains all type definitions of Pwm Driver
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
*#Pwm_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity 
*
*/

#ifndef PWM_GENERALTYPES_H_
#define PWM_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Pwm_Cfg.h"
#include "Platform_Types.h"
#include "gtm_pwm_hal.h"
#include "Mcall.h"
#include "gtm.h"

/****************************************************************************************************
**                          Global Macros Definitions                                              **
****************************************************************************************************/



/****************************************************************************************************
**                          Global basic type Definitions                                          **
****************************************************************************************************/
/* \[SWS_Pwm_00106]: Numeric identifier of a PWM channel. */
typedef uint8  Pwm_ChannelType;
/* \[SWS_Pwm_00107]: Definition of the period of a PWM channel. */
typedef uint32 Pwm_PeriodType;
/* Tick as unit:
 * - ATOM channel range: 0x00~0xFFFFFFU
 * - TOM channel range: 0x00~0xFFFFU
 * Percent as unit: 0x00~0x8000U */
#if (PWM_DUTY_SHIFT_IN_TICKS == STD_ON)
typedef uint32 Pwm_DutyCycleType;
#else
typedef uint16 Pwm_DutyCycleType;
#endif /* (PWM_DUTY_SHIFT_IN_TICKS  \== STD_ON) */
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
/* \[SWS_Pwm_00108]: Type definition for Pwm_OutputStateType */
typedef enum
{
    PWM_LOW = 0U,
    PWM_HIGH
}Pwm_OutputStateType;

/* \[SWS_Pwm_00109]: Definition of the type of edge notification of a PWM channel. */
typedef enum
{
    PWM_RISING_EDGE  = 1U,
    PWM_FALLING_EDGE,
    PWM_BOTH_EDGES
}Pwm_EdgeNotificationType;

typedef enum
{
    PWM_UNINITIALIZED = 0U,
    PWM_INITIALIZED
}Pwm_InitStateType;

/* \[SWS_Pwm_00110]: Defines the class of a PWM channel */
typedef enum
{
    PWM_VARIABLE_PERIOD = 0U,
    PWM_FIXED_PERIOD,
    PWM_FIXED_PERIOD_SHIFTED,
    PWM_FIXED_PERIOD_CENTER_ALIGNED
}Pwm_ChnPeriodType;
/****************************************************************************************************
**                          Global Structure Definitions                                          **
****************************************************************************************************/
typedef struct
{
#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE == STD_ON))
    /* Indicate the duty cycle is 0% or 100% of the channel */
    boolean                DutyIs0Or100;
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) && (PWM_0_100_INTERRUPT_HANDLE  \== STD_ON) */
    /* Interrupt status */
    Gtm_Pwm_IrqEdge        InterruptStatus;
    /* Current period */
    Pwm_PeriodType         CurrentPeriodVal;
}Pwm_ChannelStatusType;

typedef struct
{
    /* Channel Index structure */
    Gtm_Output_Driver            HWChannelIndex;
    /* Channel Configuration */
    Gtm_Pwm_Config               HWChannelConfig;
} Pwm_HWConfigType;

#if (PWM_HANDLE_SHIFT_BY_OFFSET == STD_ON)
typedef struct
{
    /* Module number */
    uint8                        ModuleIndex;
    /* Channel Index */
    Gtm_Output_Module            Module;
    /* Channels output Configuration */
    uint32                       OutputChannelsConfig;
} Pwm_ChannelsOutputCfgType;

typedef struct
{
    /* Multiple channels output configuration */
    const Pwm_ChannelsOutputCfgType*    ChannelSOutPtr;
    /* The number of modules that need to be output at the same time */
    uint8                               OutputChannelsNumber;
} Pwm_ChannelsOutputType;
#endif /* (PWM_HANDLE_SHIFT_BY_OFFSET  \== STD_ON) */

/* #Violation: Pwm_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Channel id */
    uint8               ChannelId;
    /* Idle state signal level */
    Gtm_SignalState     IdleLevel;
    /* Channel class */
    Pwm_ChnPeriodType   ChnPeriodClass;
    /* Actual Period */
    uint32              Period;
    /* Actual Duty cycle */
    uint32              DutyCycle;
    /* Shift value */
    uint32              ShiftValue;
    /* Notification function pointer */
    void                (*NotificationFuncPtr)(void);
    /* Hardware channel configuration */
    Pwm_HWConfigType    PwmHwChannelConfig;
}Pwm_ChConfigType;

/* #Violation: Pwm_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Index of the core of the current channel */
    Mcal_CoreType        Core;
    /* Index of the channel of the current core */
    uint8                Index;
} Pwm_MappingType;

/* #Violation: Pwm_GeneralTypes_h_REF_1 */
typedef struct
{
  /* No of Gtm channels */
  uint8                         MaxChannels;
  /* Pwm Channel Configuration */
  const Pwm_ChConfigType*       Pwm_ChannelConfigPtr;
#if (PWM_HANDLE_SHIFT_BY_OFFSET == STD_ON)
  /* Multiple channels output configuration */
  Pwm_ChannelsOutputType ChannelsOutputConfig;
#endif /* (PWM_HANDLE_SHIFT_BY_OFFSET  \== STD_ON) */
}Pwm_CoreConfigType;

/* SWS_Pwm_00111, SWS_Pwm_00061:
   Data Structure for Pwm for Initializing the Pwm Module */
typedef struct
{
    /* Core configuration pointer */
    const Pwm_CoreConfigType*  CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* Core mapping configuration pointer */
    const Pwm_MappingType*     PwmChannelIdxmapPtr;
    /* Pointer to hardware channel mapping with logic channel */
    const uint8*               PwmHwChannelMapPtr[2U];
}Pwm_ConfigType;

#endif/* End of Pwm_GeneralTypes.h*/
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/



