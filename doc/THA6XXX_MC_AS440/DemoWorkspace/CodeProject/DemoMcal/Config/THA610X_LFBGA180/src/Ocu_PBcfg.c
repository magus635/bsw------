
/****************************************************************************************************
*   FileName              : Ocu_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : This file contains all post-build parameters in OCU Driver
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
*#Ocu_PBCfg_c_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Ocu_PBCfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Ocu_PBCfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Ocu_PBCfg_c_REF_4:CertC-DCL06-C; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* SWS_Ocu_00007:
 * Ocu_PBcfg.c shall include Ocu.h */
#include "Ocu.h"
#include "Ocu_GeneralTypes.h"
#include "Ocu_Cfg.h"
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
/* OcuChannel_0 notification */
extern void Ocu_Notification_Channel0(void);
/* OcuChannel_1 notification */
extern void Ocu_Notification_Channel1(void);


/****************************************************************************************************
**              Low level driver configurations of the channel based on GTM-ATOM                   **
****************************************************************************************************/
/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"

/* The hardware configuration of all logic channel based on GTM-ATOM */
/* #Violation: Ocu_PBCfg_c_REF_3 */
/* #Violation: Ocu_PBCfg_c_REF_4 */
static const Ocu_HWGtmAtomConfigType Ocu_HWGtmAtomChannelsConfig[2U] = 
{
    /* OcuChannel_0 configuration */
    {
        /* The low level interface index */
        {
            /* Hardware Channel Type */
            (uint8)GTM_OUTPUT_MODULE_ATOM,
            /* Hardware Timer Module Index */
            (uint8)GTM_ATOM_INDEX_0,
            /* Group index, only used for TIO module */
            0U,
            /* Hardware Channel Index */
            (uint8)GTM_ATOM_CH_INDEX_1
        },
        /* The low level configuration */
        {
            /* Clock source */
            GTM_ATOM_CH_CLKSRC_CMUCLK0,
            /* Timer base */
            GTM_ATOM_TIMEBASE_TS1,
            /* Signal level */
            GTM_SIGNALSTATE_LOW,
            {
                /* Somc sl control */
                GTM_OCU_SLCTRL_NOCHANGE,
                /* Somc control */
                GTM_SOMCCTRL_CCU0TS0
            },
            {
                /* CCU0 interrupt control */
                FALSE,
                /* CCU1 interrupt control */
                FALSE,
                /* Interrupt level mode */
                GTM_IRQMODE_LEVEL
            },
            /* Compare value0 */
            1000U,
            /* Compare value1 */
            0U
        },
        /* Abstract time base */
        GTM_TBU_CH_TS0
    },
    /* OcuChannel_1 configuration */
    {
        /* The low level interface index */
        {
            /* Hardware Channel Type */
            (uint8)GTM_OUTPUT_MODULE_ATOM,
            /* Hardware Timer Module Index */
            (uint8)GTM_ATOM_INDEX_0,
            /* Group index, only used for TIO module */
            0U,
            /* Hardware Channel Index */
            (uint8)GTM_ATOM_CH_INDEX_0
        },
        /* The low level configuration */
        {
            /* Clock source */
            GTM_ATOM_CH_CLKSRC_CMUCLK0,
            /* Timer base */
            GTM_ATOM_TIMEBASE_TS1,
            /* Signal level */
            GTM_SIGNALSTATE_LOW,
            {
                /* Somc sl control */
                GTM_OCU_SLCTRL_NOCHANGE,
                /* Somc control */
                GTM_SOMCCTRL_CCU0TS0
            },
            {
                /* CCU0 interrupt control */
                FALSE,
                /* CCU1 interrupt control */
                FALSE,
                /* Interrupt level mode */
                GTM_IRQMODE_LEVEL
            },
            /* Compare value0 */
            1000U,
            /* Compare value1 */
            0U
        },
        /* Abstract time base */
        GTM_TBU_CH_TS0
    }
};

/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"


/****************************************************************************************************
**                               MCAL driver configurations                                        **
****************************************************************************************************/
/****************************************************************************************************
**                                  Core0       configurations                                     **
****************************************************************************************************/
/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"
static const Ocu_ChConfigType Ocu_Core0ChannelConfig[OCU_MAX_CHANNEL_TO_CORE0] =
{
    /* OcuChannel_0 configuration */
    {
        /* Channel Id */
        0U,
        /* Channel Maximum Value  */
        16777215U,
        /* Notification pointer */
        Ocu_Notification_Channel0,
        /* Output event class */
        OCU_COMPARE_EVENT_PIN,
        /* Default compare value */
        1000U,
        /* The hardware class of the logic ocu channel */
        OCU_HW_GTM_ATOM
    },
    /* OcuChannel_1 configuration */
    {
        /* Channel Id */
        1U,
        /* Channel Maximum Value  */
        16777215U,
        /* Notification pointer */
        Ocu_Notification_Channel1,
        /* Output event class */
        OCU_COMPARE_EVENT_ADC,
        /* Default compare value */
        1000U,
        /* The hardware class of the logic ocu channel */
        OCU_HW_GTM_ATOM
    }
};

/* OCU channels configuration of core0 */
static const Ocu_CoreConfigType Ocu_CoreConfigCore0 =
{
    /* Number of core0 maximum channels */
    2U,
    /*Channel configuration*/
    &Ocu_Core0ChannelConfig[0]
};

/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"


/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"


/* This array is used for mapping Ocu Channel to the Core. */
static const Ocu_MappingType Ocu_ChannelToCoreMap[OCU_MAX_CHANNELS] =
{
    /* OcuChannel_0 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel Index */
        0U,
        /* Hardware configuration mapping index */
        0U
    },
    /* OcuChannel_1 */
    {
        /* Core number */
        (Mcal_CoreType)MCAL_CORE0, 
        /* Channel Index */
        1U,
        /* Hardware configuration mapping index */
        1U
    }
};

/* Mapping the hardware channel(GTM-ATOM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Ocu_PBCfg_c_REF_3 */
static const uint8 Ocu_HwAtomChannelMap[8U] =
{
    /* ATOM0_CH0 */
    1U,
    /* ATOM0_CH1 */
    0U,
    /* ATOM0_CH2 */
    0xFFU,
    /* ATOM0_CH3 */
    0xFFU,
    /* ATOM0_CH4 */
    0xFFU,
    /* ATOM0_CH5 */
    0xFFU,
    /* ATOM0_CH6 */
    0xFFU,
    /* ATOM0_CH7 */
    0xFFU
};

/* Configuration parameters */
/* #Violation: Ocu_PBCfg_c_REF_3 */
const Ocu_ConfigType Ocu_ConfigSet[1U] =
{
    {
        {
            /* OCU channels configuration's pointer of core0 */
            &Ocu_CoreConfigCore0,
            /* OCU channels configuration's pointer of core1 */
            NULL_PTR
        },
        /* Table for relationship between channel ID in specified core and OCU channel ID */
        &Ocu_ChannelToCoreMap[0U],
        /* Configuration for hardware channel which is GtmAtom */
        &Ocu_HWGtmAtomChannelsConfig[0U],
        /* Pointer to GTM-ATOM channel mapping with logic channel */
        &Ocu_HwAtomChannelMap[0U],
    }
};

/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
