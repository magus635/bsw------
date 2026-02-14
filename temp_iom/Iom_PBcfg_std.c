/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : This file contains all configurations of IOM Driver
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
*#Iom_PBCfg_c_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Iom_PBCfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Iom_PBCfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Iom_PBCfg_c_REF_4:MISRAC2012-Rule-10.5; 
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Iom.h"

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
/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Iom_MemMap.h"
/* #Violation: Iom_PBCfg_c_REF_3 */
static const Iom_LpuConfigType Iom_LPUConfiguration[1] =
{
    {
        /* LPU channel 0 */ 
        IOM_LPUID_0,
        /* LPU event source and edge triggering configuration */
        {
            IOM_LPUEVENTSOURCE_MON,
            IOM_LPUEVENTTRIGGER_FALLINGEDGE
        },
        /* LPU eventWindow configuration */
        {
            /* LPU eventWindow source */
            IOM_LPUEVENTWINDOWCONTROLSOURCE_MON,
            /* LPU eventWindow edge triggering */
            IOM_LPUEVENTWINDOWCLEAREVENT_RISINGEDGE,
            /* LPU eventWindow running mode */
            IOM_LPUEVENTWINDOWRUNCONTROL_FREERUNNING,
            /* Whether to invert the event window */
            TRUE,
            /* The time the event window lasts */
            0U,
        },
        {
        /* LPU Monitor input configuration */
            {
                /* Monitor signal prescaler counter threshold */
                1U,
                /* Monitor signal filter mode */
                (Iom_PpuFilterMode)BOTHEDGES_DD,
                /* Monitor signal filter time */
                1U,
                /* Reset timer or not with delay debounce mode */
                FALSE
            },
            /* LPU Monitor signal source */
            (Iom_MonInput)CHANNEL0_IOM_MONINPUT_GTMTOUT24,
            /* Whether the LPU Monitor signal inverted */
            FALSE
        },
        {
        /* LPU reference input configuration */
            {
                /* Reference signal prescaler counter threshold */
                1U,
                /* Reference signal filter mode */
                (Iom_PpuFilterMode)BOTHEDGES_DD,
                /* Reference signal filter time */
                1U,
                /* Reset timer or not with delay debounce mode */
                FALSE
            },
            /* LPU Reference signal source */
            (Iom_RefInput)CHANNEL0_IOM_REFINPUT_GTMTOUT3,
            /* XOR usage */
            0U,
            /* Whether the LPU Monitor signal inverted */
            FALSE
        },
        {
        /* EMU configuration */
            /* Which EMU counter is selected for the LPU channel */
            IOM_EVENTCOUNTERCHANNEL_NOCOUNTER,
            /* EMU counter threshold */
            IOM_EVENTCOUNTERTHRESHOLD_DISABLE
        }
    }
}; 

/* #Violation: Iom_PBCfg_c_REF_3 */
static const Iom_EmuCombinerType Iom_EMUCombinerCfg[1] =
{
    {
        /* #Violation: Iom_PBCfg_c_REF_4 */
        (Iom_EventCounterChannel)0xFF,
        IOM_LPUID_0,
        IOM_EVENTCOUNTERTHRESHOLD_DISABLE
    }
};
/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"

/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"
const Iom_ConfigType Iom_ConfigSet[1U] =
{
    {
        /* LPU channel configuration */
        &Iom_LPUConfiguration[0U],
        /* EMU combined channel logging */
        1U,
        /* EMU combined channel configuration */
        &Iom_EMUCombinerCfg[0U],
        /* Iom Clock divide factor */
        (1U)
    }
};

/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"
 
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
  
