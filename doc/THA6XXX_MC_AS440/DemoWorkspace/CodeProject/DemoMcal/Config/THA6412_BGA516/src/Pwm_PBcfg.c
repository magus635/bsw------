/****************************************************************************************************
*   FileName              : Pwm_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : This file contains all post-build parameters in PWM Driver
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
*#Pwm_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Pwm_PBcfg_c_REF_2:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Pwm_PBcfg_c_REF_3:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
* 
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* SWS_Pwm_60075:
 *  Pwm_PBcfg.c shall include Pwm.h. */
#include "Pwm.h"
#include "Pwm_GeneralTypes.h"
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* Declare the notification functions */              
extern void Pwm_Notification_0(void);
extern void Pwm_Notification_1(void);
extern void Pwm_Notification_4(void);
extern void Pwm_Notification_5(void);


/****************************************************************************************************
**                                  Core0       configurations                                     **
****************************************************************************************************/
/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"



static const Pwm_ChConfigType Pwm_Core0ChannelConfig[PWM_MAX_CHANNEL_TO_CORE0] =
{
    {
        /* Channel Id*/
        0U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_FIXED_PERIOD,
        /* Period */
        2000U,
        /* Duty Cycle */
        1000U,
        /* Shift value */
        0U,
        /* Notification Function Pointer */
        Pwm_Notification_0,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_0,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_0
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                2000U,
                /* Actual Duty Cycle */
                1000U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONCM0,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_GENERATE,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        1U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_VARIABLE_PERIOD,
        /* Period */
        2000U,
        /* Duty Cycle */
        1000U,
        /* Shift value */
        0U,
        /* Notification Function Pointer */
        Pwm_Notification_1,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_0,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_1
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                2000U,
                /* Actual Duty Cycle */
                1000U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONCM0,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        2U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_FIXED_PERIOD_SHIFTED,
        /* Period */
        2000U,
        /* Duty Cycle */
        1000U,
        /* Shift value */
        200U,
        /* Notification Function Pointer */
        NULL_PTR,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_0,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_2
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                200U,
                /* Actual Duty Cycle */
                1200U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONTRIGGER,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        3U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_FIXED_PERIOD_CENTER_ALIGNED,
        /* Period */
        2000U,
        /* Duty Cycle */
        1000U,
        /* Shift value */
        500U,
        /* Notification Function Pointer */
        NULL_PTR,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_0,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_3
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                500U,
                /* Actual Duty Cycle */
                1500U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONTRIGGER,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        8U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_VARIABLE_PERIOD,
        /* Period */
        1000U,
        /* Duty Cycle */
        600U,
        /* Shift value */
        0U,
        /* Notification Function Pointer */
        NULL_PTR,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_TOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_1,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_1
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUFXCLK0,
                /* Actual Period */
                1000U,
                /* Actual Duty Cycle */
                600U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONCM0,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        9U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_VARIABLE_PERIOD,
        /* Period */
        0U,
        /* Duty Cycle */
        0U,
        /* Shift value */
        0U,
        /* Notification Function Pointer */
        NULL_PTR,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_TOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_1,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_6
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUFXCLK0,
                /* Actual Period */
                0U,
                /* Actual Duty Cycle */
                0U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONCM0,
                /* Signal Level */
                GTM_SIGNALSTATE_HIGH,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        10U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_VARIABLE_PERIOD,
        /* Period */
        0U,
        /* Duty Cycle */
        0U,
        /* Shift value */
        0U,
        /* Notification Function Pointer */
        NULL_PTR,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_TOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_1,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_7
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUFXCLK0,
                /* Actual Period */
                0U,
                /* Actual Duty Cycle */
                0U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONCM0,
                /* Signal Level */
                GTM_SIGNALSTATE_HIGH,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        11U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_VARIABLE_PERIOD,
        /* Period */
        1000U,
        /* Duty Cycle */
        500U,
        /* Shift value */
        0U,
        /* Notification Function Pointer */
        NULL_PTR,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_1,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_6
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                1000U,
                /* Actual Duty Cycle */
                500U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONCM0,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    }
};

/* PWM channels configuration of core0 */
static const Pwm_CoreConfigType Pwm_CoreConfigCore0 =
{
    /* Number of core0 maximum channels */
    8U,
    /*Channel configuration*/
    &Pwm_Core0ChannelConfig[0],
};

/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"
/****************************************************************************************************
**                                  Core1       configurations                                     **
****************************************************************************************************/
/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"



static const Pwm_ChConfigType Pwm_Core1ChannelConfig[PWM_MAX_CHANNEL_TO_CORE1] =
{
    {
        /* Channel Id*/
        4U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_FIXED_PERIOD,
        /* Period */
        2000U,
        /* Duty Cycle */
        1000U,
        /* Shift value */
        0U,
        /* Notification Function Pointer */
        Pwm_Notification_4,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_0,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_4
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                2000U,
                /* Actual Duty Cycle */
                1000U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONCM0,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_GENERATE,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        5U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_VARIABLE_PERIOD,
        /* Period */
        2000U,
        /* Duty Cycle */
        1000U,
        /* Shift value */
        0U,
        /* Notification Function Pointer */
        Pwm_Notification_5,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_0,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_5
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                2000U,
                /* Actual Duty Cycle */
                1000U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONCM0,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        6U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_FIXED_PERIOD_SHIFTED,
        /* Period */
        2000U,
        /* Duty Cycle */
        1000U,
        /* Shift value */
        200U,
        /* Notification Function Pointer */
        NULL_PTR,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_0,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_6
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                200U,
                /* Actual Duty Cycle */
                1200U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONTRIGGER,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    },
    {
        /* Channel Id*/
        7U,
        /* Idle State Level */
        GTM_SIGNALSTATE_HIGH,
        /* Channel Class */
        PWM_FIXED_PERIOD_CENTER_ALIGNED,
        /* Period */
        2000U,
        /* Duty Cycle */
        1000U,
        /* Shift value */
        500U,
        /* Notification Function Pointer */
        NULL_PTR,
        {
            {
                /* Hardware Channel Type */
                (uint8)GTM_OUTPUT_MODULE_ATOM,
                /* Hardware Timer Module Index */
                (uint8)GTM_PWM_MODULE_INDEX_0,
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)GTM_PWM_CH_INDEX_7
            },
            {
                /* Clock Source */
                GTM_PWM_CLOCK_CMUCLK1,
                /* Actual Period */
                500U,
                /* Actual Duty Cycle */
                1500U,
                /* Initial Counter Shift */
                0U,
                {
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                },
                /* Channel Counter Reset Source */
                GTM_PWM_RESETEVENT_ONTRIGGER,
                /* Signal Level */
                GTM_SIGNALSTATE_LOW,
                {
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                },
                /* Trigger Output Signal Select */
                GTM_PWM_TRIGOUT_FORWARD,
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                TRUE,
                /* Channel Control */
                TRUE,
                /* Channel Output Control */
                TRUE,
                /* Update Immediate Control */
                TRUE
            }   
        }
    }
};

/* PWM channels configuration of core1 */
static const Pwm_CoreConfigType Pwm_CoreConfigCore1 =
{
    /* Number of core1 maximum channels */
    4U,
    /*Channel configuration*/
    &Pwm_Core1ChannelConfig[0],
};

/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"


/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"
/* This array is used for mapping Pwm Channel to the Core. */
static const Pwm_MappingType Pwm_ChannelToCoreMap[PWM_MAX_CHANNELS] =
{
    /* PwmChannel_0 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel index */
        0U
    },
    /* PwmChannel_1 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel index */
        1U
    },
    /* PwmChannel_2 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel index */
        2U
    },
    /* PwmChannel_3 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel index */
        3U
    },
    /* PwmChannel_4 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE1, 
        /* Channel index */
        0U
    },
    /* PwmChannel_5 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE1, 
        /* Channel index */
        1U
    },
    /* PwmChannel_6 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE1, 
        /* Channel index */
        2U
    },
    /* PwmChannel_7 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE1, 
        /* Channel index */
        3U
    },
    /* ICU_DEMO */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel index */
        4U
    },
    /* PwmChannel_8 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel index */
        5U
    },
    /* PwmChannel_9 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel index */
        6U
    },
    /* PwmToDsadc */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel index */
        7U
    }
};

/* Mapping the hardware channel(GTM-TOM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Pwm_PBcfg_c_REF_2 */
static const uint8 Pwm_HwTomChannelMap[80U] =
{
    /* TOM0_CH0 */
    0xFFU,
    /* TOM0_CH1 */
    0xFFU,
    /* TOM0_CH2 */
    0xFFU,
    /* TOM0_CH3 */
    0xFFU,
    /* TOM0_CH4 */
    0xFFU,
    /* TOM0_CH5 */
    0xFFU,
    /* TOM0_CH6 */
    0xFFU,
    /* TOM0_CH7 */
    0xFFU,
    /* TOM0_CH8 */
    0xFFU,
    /* TOM0_CH9 */
    0xFFU,
    /* TOM0_CH10 */
    0xFFU,
    /* TOM0_CH11 */
    0xFFU,
    /* TOM0_CH12 */
    0xFFU,
    /* TOM0_CH13 */
    0xFFU,
    /* TOM0_CH14 */
    0xFFU,
    /* TOM0_CH15 */
    0xFFU,
    /* TOM1_CH0 */
    0xFFU,
    /* TOM1_CH1 */
    8U,
    /* TOM1_CH2 */
    0xFFU,
    /* TOM1_CH3 */
    0xFFU,
    /* TOM1_CH4 */
    0xFFU,
    /* TOM1_CH5 */
    0xFFU,
    /* TOM1_CH6 */
    9U,
    /* TOM1_CH7 */
    10U,
    /* TOM1_CH8 */
    0xFFU,
    /* TOM1_CH9 */
    0xFFU,
    /* TOM1_CH10 */
    0xFFU,
    /* TOM1_CH11 */
    0xFFU,
    /* TOM1_CH12 */
    0xFFU,
    /* TOM1_CH13 */
    0xFFU,
    /* TOM1_CH14 */
    0xFFU,
    /* TOM1_CH15 */
    0xFFU,
    /* TOM2_CH0 */
    0xFFU,
    /* TOM2_CH1 */
    0xFFU,
    /* TOM2_CH2 */
    0xFFU,
    /* TOM2_CH3 */
    0xFFU,
    /* TOM2_CH4 */
    0xFFU,
    /* TOM2_CH5 */
    0xFFU,
    /* TOM2_CH6 */
    0xFFU,
    /* TOM2_CH7 */
    0xFFU,
    /* TOM2_CH8 */
    0xFFU,
    /* TOM2_CH9 */
    0xFFU,
    /* TOM2_CH10 */
    0xFFU,
    /* TOM2_CH11 */
    0xFFU,
    /* TOM2_CH12 */
    0xFFU,
    /* TOM2_CH13 */
    0xFFU,
    /* TOM2_CH14 */
    0xFFU,
    /* TOM2_CH15 */
    0xFFU,
    /* TOM3_CH0 */
    0xFFU,
    /* TOM3_CH1 */
    0xFFU,
    /* TOM3_CH2 */
    0xFFU,
    /* TOM3_CH3 */
    0xFFU,
    /* TOM3_CH4 */
    0xFFU,
    /* TOM3_CH5 */
    0xFFU,
    /* TOM3_CH6 */
    0xFFU,
    /* TOM3_CH7 */
    0xFFU,
    /* TOM3_CH8 */
    0xFFU,
    /* TOM3_CH9 */
    0xFFU,
    /* TOM3_CH10 */
    0xFFU,
    /* TOM3_CH11 */
    0xFFU,
    /* TOM3_CH12 */
    0xFFU,
    /* TOM3_CH13 */
    0xFFU,
    /* TOM3_CH14 */
    0xFFU,
    /* TOM3_CH15 */
    0xFFU,
    /* TOM4_CH0 */
    0xFFU,
    /* TOM4_CH1 */
    0xFFU,
    /* TOM4_CH2 */
    0xFFU,
    /* TOM4_CH3 */
    0xFFU,
    /* TOM4_CH4 */
    0xFFU,
    /* TOM4_CH5 */
    0xFFU,
    /* TOM4_CH6 */
    0xFFU,
    /* TOM4_CH7 */
    0xFFU,
    /* TOM4_CH8 */
    0xFFU,
    /* TOM4_CH9 */
    0xFFU,
    /* TOM4_CH10 */
    0xFFU,
    /* TOM4_CH11 */
    0xFFU,
    /* TOM4_CH12 */
    0xFFU,
    /* TOM4_CH13 */
    0xFFU,
    /* TOM4_CH14 */
    0xFFU,
    /* TOM4_CH15 */
    0xFFU
};

/* Mapping the hardware channel(GTM-ATOM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Pwm_PBcfg_c_REF_2 */
static const uint8 Pwm_HwAtomChannelMap[64U] =
{
    /* ATOM0_CH0 */
    0U,
    /* ATOM0_CH1 */
    1U,
    /* ATOM0_CH2 */
    2U,
    /* ATOM0_CH3 */
    3U,
    /* ATOM0_CH4 */
    4U,
    /* ATOM0_CH5 */
    5U,
    /* ATOM0_CH6 */
    6U,
    /* ATOM0_CH7 */
    7U,
    /* ATOM1_CH0 */
    0xFFU,
    /* ATOM1_CH1 */
    0xFFU,
    /* ATOM1_CH2 */
    0xFFU,
    /* ATOM1_CH3 */
    0xFFU,
    /* ATOM1_CH4 */
    0xFFU,
    /* ATOM1_CH5 */
    0xFFU,
    /* ATOM1_CH6 */
    11U,
    /* ATOM1_CH7 */
    0xFFU,
    /* ATOM2_CH0 */
    0xFFU,
    /* ATOM2_CH1 */
    0xFFU,
    /* ATOM2_CH2 */
    0xFFU,
    /* ATOM2_CH3 */
    0xFFU,
    /* ATOM2_CH4 */
    0xFFU,
    /* ATOM2_CH5 */
    0xFFU,
    /* ATOM2_CH6 */
    0xFFU,
    /* ATOM2_CH7 */
    0xFFU,
    /* ATOM3_CH0 */
    0xFFU,
    /* ATOM3_CH1 */
    0xFFU,
    /* ATOM3_CH2 */
    0xFFU,
    /* ATOM3_CH3 */
    0xFFU,
    /* ATOM3_CH4 */
    0xFFU,
    /* ATOM3_CH5 */
    0xFFU,
    /* ATOM3_CH6 */
    0xFFU,
    /* ATOM3_CH7 */
    0xFFU,
    /* ATOM4_CH0 */
    0xFFU,
    /* ATOM4_CH1 */
    0xFFU,
    /* ATOM4_CH2 */
    0xFFU,
    /* ATOM4_CH3 */
    0xFFU,
    /* ATOM4_CH4 */
    0xFFU,
    /* ATOM4_CH5 */
    0xFFU,
    /* ATOM4_CH6 */
    0xFFU,
    /* ATOM4_CH7 */
    0xFFU,
    /* ATOM5_CH0 */
    0xFFU,
    /* ATOM5_CH1 */
    0xFFU,
    /* ATOM5_CH2 */
    0xFFU,
    /* ATOM5_CH3 */
    0xFFU,
    /* ATOM5_CH4 */
    0xFFU,
    /* ATOM5_CH5 */
    0xFFU,
    /* ATOM5_CH6 */
    0xFFU,
    /* ATOM5_CH7 */
    0xFFU,
    /* ATOM6_CH0 */
    0xFFU,
    /* ATOM6_CH1 */
    0xFFU,
    /* ATOM6_CH2 */
    0xFFU,
    /* ATOM6_CH3 */
    0xFFU,
    /* ATOM6_CH4 */
    0xFFU,
    /* ATOM6_CH5 */
    0xFFU,
    /* ATOM6_CH6 */
    0xFFU,
    /* ATOM6_CH7 */
    0xFFU,
    /* ATOM7_CH0 */
    0xFFU,
    /* ATOM7_CH1 */
    0xFFU,
    /* ATOM7_CH2 */
    0xFFU,
    /* ATOM7_CH3 */
    0xFFU,
    /* ATOM7_CH4 */
    0xFFU,
    /* ATOM7_CH5 */
    0xFFU,
    /* ATOM7_CH6 */
    0xFFU,
    /* ATOM7_CH7 */
    0xFFU
};

/* Configuration parameters */
const Pwm_ConfigType Pwm_ConfigSet[1U] =
{
    {
        {
            /* PWM channels configuration's pointer of core0 */
            &Pwm_CoreConfigCore0,
            /* PWM channels configuration's pointer of core1 */
            &Pwm_CoreConfigCore1,
            /* PWM channels configuration's pointer of core2 */
            NULL_PTR,
            /* PWM channels configuration's pointer of core3 */
            NULL_PTR
        },
        /* Table for relationship between channel ID in specified core and PWM channel ID */
        &Pwm_ChannelToCoreMap[0U],
        /* Pointer to hardware channel mapping with logic channel */
        {
            /* Pointer to GTM-TOM channel mapping with logic channel */
            &Pwm_HwTomChannelMap[0U],
            /* Pointer to GTM-ATOM channel mapping with logic channel */
            &Pwm_HwAtomChannelMap[0U]
        }
    }
};
/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

