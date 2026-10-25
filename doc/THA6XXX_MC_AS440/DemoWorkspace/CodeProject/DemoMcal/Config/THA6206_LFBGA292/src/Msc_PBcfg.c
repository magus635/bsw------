/****************************************************************************************************
*   FileName              : Msc_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains all post-build parameters in Msc Driver
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
*#Msc_PBcfg_c_REF_1:MISRAC2012-Rule-11.4; 
* Justification: Casting a pointer to an integral type to obtain its address.
*
*#Msc_PBcfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
*
*#Msc_PBcfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*#Msc_PBcfg_c_REF_4:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Msc.h"
#include "Msc_Cfg.h"
#include "Msc_GeneralTypes.h"
#include "Mcall.h"
#include "msc_hal.h"
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
/* MscModuleConfiguration_0 Data frame notification function extern */
extern void Msc0_DataFrameNotification(void);
/* MscModuleConfiguration_0 Command frame notification function extern */
extern void Msc0_CmdFrameNotification(void);
/* MscModuleConfiguration_0 Receive data notification function extern */
extern void Msc0_RxNotification(void);



/****************************************************************************************************
**                          Configurations                                                         **
****************************************************************************************************/
/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */

/* Module configuration: 
* Including clock, upstream, downstream and interrupt */
/* #Violation: Msc_PBcfg_c_REF_3 */
static const Msc_ModuleConfig Msc_ModuleConfiguration[1U] = 
{
    /* MscModuleConfiguration_0 configuration */
    {
        /* Clock configuration */
        {
            /* Baud rate */
            2500000U,
            /* Clock divider mode */
            MSC_DIVMODE_FRACTIONAL
        },
        /* Upstream configuration */
        {
            /* Upstream channel division */
            MSC_UPDIV_32,
            /* Upstream channel frame type */
            MSC_FRAMETYPE_16BIT,
            /* Parity mode */
            MSC_PARITY_EVEN,
            /* Service request delay */
            MSC_REQDELAY_NODELAY,
            /* SDI polarity */
            MSC_SIGNALPOLARITY_NONINVERTED
        },
        /* Downstream configuration */
        {
            /* Transmission mode */
            MSC_TRANSMODE_TRIGGERED,
            /* Command frames length */
            MSC_CFLENGTH_15,
            /* Data frames srl length */
            MSC_DFLENGTH_16,
            /* Data frames srh length */
            MSC_DFLENGTH_15,
            /* Passive phase length of data frames */
            MSC_DFPPL_4,
            /* SRL active phase selection bit */
            MSC_SELBIT_LOWLEVEL,
            /* SRH active phase selection bit */
            MSC_SELBIT_NONE,
            /* Clock active phase */
            MSC_FCLVALID_ALWAYS,
            /* CSLP polarity */
            MSC_SIGNALPOLARITY_INVERTED,
            /* Number of passive time frames in data repetition mode */
            MSC_PTFCOUNT_0,
            /* Command-data-command in data repetition mode */
            MSC_CDCMODE_DISABLED,
            /* Data source configuration */
            {
                /* SRL data source selection */
                0x0U,
                /* SRH data source selection */
                0x0U,
                /* Emergency stop enable bits */
                0x0U,
                /* Injection enable pin 0 */
                MSC_INJEN_DISABLED,
                /* Injection position pin 0 */
                MSC_INJPOS_0,
                /* Injection enable pin 1 */
                MSC_INJEN_DISABLED,
                /* Injection position pin 1 */
                MSC_INJPOS_0
            },
            /* Downstream channel enable control */
            MSC_DOWNSTREAMEN_ENABLED
        }
    }};

/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */



/****************************************************************************************************
**                                  Core0       configurations                                     **
****************************************************************************************************/
/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#include "Msc_MemMap.h"
    /* Interrupt configuration of core0 */
/* #Violation: Msc_PBcfg_c_REF_3 */
static const Msc_IntConfigType Msc_Core0InterruptConfig[1U] =
{
    /* MscModuleConfiguration_0 interrupt configuration */
    {
        {
            /* Receive data interrupt type */
            MSC_RDITYPE_RECEIVEINUD3,
            /* Receive data interrupt service */
            MSC_INTRNODE_SR2,
            /* Time frame interrupt service */
            MSC_INTRNODE_SR0,
            /* Command frame interrupt service */
            MSC_INTRNODE_SR0,
            /* Data frame interrupt service */
            MSC_INTRNODE_SR2,
            /* Data frame interrupt type */
            MSC_DFINTERRUPT_LASTBIT
        },
        /* Interrupt notification function configuration */
        {
            /* Data frame notification function pointer */
            Msc0_DataFrameNotification,
            /* Command frame notification function pointer */
            Msc0_CmdFrameNotification,
            /* Time frame notification function pointer */
            NULL_PTR,
            /* Receive data notification function pointer */
            Msc0_RxNotification
        },
        /* Interrupt enable parameter */
        (uint32)(MSC_INTR_ENABLE_FLAG_RX|MSC_INTR_ENABLE_FLAG_CF|MSC_INTR_ENABLE_FLAG_DF)
    }
};



/* Channel configuration of core0 */
static const Msc_ChConfigType Msc_Core0ChannelConfig[MSC_MAX_CHANNEL_TO_CORE0] =
{
    /* MscModuleConfiguration_0 channel configuration */
    {
        /* Hardware module pointer */
        /* #Violation: Msc_PBcfg_c_REF_1 */
        MSC0_HAL,
        /* #Violation: Msc_PBcfg_c_REF_1 */
        /* Module configuration pointer */
        &Msc_ModuleConfiguration[0U],
        /* Interrupt configuration pointer */
        &Msc_Core0InterruptConfig[0U],
        /* Timeout configuration pointer */
        NULL_PTR
    }
};

/* MSC channels configuration of core0 */
static const Msc_CoreConfigType Msc_CoreConfigCore0 =
{
    /* Number of core0 maximum channels */
    1U,
    /* Channel configuration*/
    &Msc_Core0ChannelConfig[0U]
};

#define MSC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */

/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */

/* This array is used for mapping Msc Channel to the Core */
static const Msc_MappingType Msc_ChannelToCoreMap[MSC_TOTAL_CHANNEL_NUMBER] =
{

    /* MscModuleConfiguration_0: No.0 channel of MCAL_CORE0 */
    {
        /* Core number */
        (uint8)MCAL_CORE0, 
        /* Channel index in specific core */
        0U
    }
};

/* Mapping the hardware channel index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Msc_PBcfg_c_REF_3 */
static const uint8 Msc_HwChannelMap[1U] =
{
  /* Msc_0 */
  0U
};

/* Configuration parameters for driver to initialize */
const Msc_ConfigType Msc_ConfigSet[1U] =
{
    {
        {
            /* MSC channels configuration's pointer of core0 */
            &Msc_CoreConfigCore0,
            /* MSC channels configuration's pointer of core1 */
            NULL_PTR
        },
        /* Table for relationship between channel ID in specified core and MSC channel ID */
        &Msc_ChannelToCoreMap[0U],
        /* Pointer to MSC hardware channel mapping with logic channel */
        &Msc_HwChannelMap[0U]
    
    }
};

/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
