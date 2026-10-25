/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Icu_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TIM
*
*   brief                 : This file contains all post-build parameters in ICU Driver
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
*#Icu_PBcfg_c_REF_1:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Icu_PBcfg_c_REF_2:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
* 
*#Icu_PBcfg_c_REF_3:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* \[SWS_Icu_00247]*/
/* \[SWS_Icu_00254]*/
#include "Icu.h"

/* \[SWS_Icu_00214] [SWS_Icu_00348] [SWS_Icu_00044] [SWS_Icu_00215][SWS_Icu_00349]
 * Declare the notification functions */
extern void Icu_SignalNotification_1(void);
extern void Icu_TimestampNotification_3(void);
extern void Icu_SignalNotification_5(void);
extern void Icu_TimestampNotification_7(void);

/* Icu Channel(s) configuration informations which mapped to Core0 */
/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"
static const Gtm_Icu_Config Icu_ConfigCore0[]=
{
    /* IcuChannel_0 */
    {
        /* IcuMeasurementMode */
        (Gtm_Icu_Mode)ICU_MODE_SIGNAL_MEASUREMENT,
        /* Clock */
        GTM_CMU_CLK_1,
        /*input*/    
        GTM_TIM_INPUT_CURRENTCHANNEL,
        /*edge*/        
        GTM_TIM_EDGE_CAP_FALL,
        /*Filter*/
        NULL_PTR,
        /*ctrlMethodSetPtr*/
        NULL_PTR,
        /* Enables resetting of counter in certain modes */
        FALSE,
        /* Interrupt */
        {
            4U,/* Cnt OverFlow */
            GTM_IRQMODE_LEVEL
        },
        FALSE,
        /*AuxInConfig*/
        {
            /* IsChIndexBiggerThan7 */
            FALSE,
            FALSE,
            FALSE,
        },
    },
    
    /* IcuChannel_1 */
    {
        /* IcuMeasurementMode */
        (Gtm_Icu_Mode)ICU_MODE_SIGNAL_EDGE_DETECT,
        /* Clock */
        GTM_CMU_CLK_1,
        /*input*/    
        GTM_TIM_INPUT_CURRENTCHANNEL,
        /*edge*/        
        GTM_TIM_EDGE_CAP_RISE,
        /*Filter*/
        NULL_PTR,
        /*ctrlMethodSetPtr*/
        NULL_PTR,
        /* Enables resetting of counter in certain modes */
        FALSE,
        /* Interrupt */
        {
            1U,/* NewValue */
            GTM_IRQMODE_LEVEL
        },
        FALSE,
        /*AuxInConfig*/
        {
            /* IsChIndexBiggerThan7 */
            FALSE,
            FALSE,
            FALSE,
        },
    },
    
    /* IcuChannel_2 */
    {
        /* IcuMeasurementMode */
        (Gtm_Icu_Mode)ICU_MODE_EDGE_COUNTER,
        /* Clock */
        GTM_CMU_CLK_1,
        /*input*/    
        GTM_TIM_INPUT_CURRENTCHANNEL,
        /*edge*/        
        GTM_TIM_EDGE_CAP_BOTH,
        /*Filter*/
        NULL_PTR,
        /*ctrlMethodSetPtr*/
        NULL_PTR,
        /* Enables resetting of counter in certain modes */
        FALSE,
        /* Interrupt */
        {
            4U,/* Cnt OverFlow */
            GTM_IRQMODE_LEVEL
        },
        FALSE,
        /*AuxInConfig*/
        {
            /* IsChIndexBiggerThan7 */
            FALSE,
            FALSE,
            FALSE,
        },
    },
    
    /* IcuChannel_3 */
    {
        /* IcuMeasurementMode */
        (Gtm_Icu_Mode)ICU_MODE_TIMESTAMP,
        /* Clock */
        GTM_CMU_CLK_1,
        /*input*/    
        GTM_TIM_INPUT_CURRENTCHANNEL,
        /*edge*/        
        GTM_TIM_EDGE_CAP_FALL,
        /*Filter*/
        NULL_PTR,
        /*ctrlMethodSetPtr*/
        NULL_PTR,
        /* Enables resetting of counter in certain modes */
        FALSE,
        /* Interrupt */
        {
            1U,/* NewValue */
            GTM_IRQMODE_LEVEL
        },
        FALSE,
        /*AuxInConfig*/
        {
            /* IsChIndexBiggerThan7 */
            FALSE,
            FALSE,
            FALSE,
        },
    },
    
};

static const Icu_ChnConfigType Icu_ChannelConfigCore0[ICU_MAX_CHANNEL_TO_CORE0]=
{
    /* ICU Channel 0 */
    {
        0U,
        /* Notification function pointer */
        NULL_PTR,
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_0,
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_0,
        /* ChannelProperties */        
        ICU_MEASUREMENT_PRO_DUTY_CYCLE,
        /* Tim_ConfigPtr */
        &Icu_ConfigCore0[0],
        /* IsWakeupChannel */
        FALSE,
        /* WakeupSourceCfgInfo */
        0U,/*Not applicable*/
    },
    /* ICU Channel 1 */
    {
        1U,
        /* Notification function pointer */
        &Icu_SignalNotification_1,
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_2,
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_1,
        /* ChannelProperties */        
        0x00,
        /* Tim_ConfigPtr */
        &Icu_ConfigCore0[1],
        /* IsWakeupChannel */
        FALSE,
        /* WakeupSourceCfgInfo */
        0U,/*Not applicable*/
    },
    /* ICU Channel 2 */
    {
        2U,
        /* Notification function pointer */
        NULL_PTR,
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_0,
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_5,
        /* ChannelProperties */        
        0x00,
        /* Tim_ConfigPtr */
        &Icu_ConfigCore0[2],
        /* IsWakeupChannel */
        FALSE,
        /* WakeupSourceCfgInfo */
        0U,/*Not applicable*/
    },
    /* ICU Channel 3 */
    {
        3U,
        /* Notification function pointer */
        &Icu_TimestampNotification_3,
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_2,
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_0,
        /* ChannelProperties */        
        (uint8)ICU_CIRCULAR_BUFFER,
        /* Tim_ConfigPtr */
        &Icu_ConfigCore0[3],
        /* IsWakeupChannel */
        FALSE,
        /* WakeupSourceCfgInfo */
        0U,/*Not applicable*/
    },
};

static const Icu_ChannelConfigType Icu_ChannelConfigSetCore0[] =
{
    {
        /* Icu_ChnConfigType */
        &Icu_ChannelConfigCore0[0],
    }
};

/* Icu channel number and configuration information in Core0 */
static const Icu_CoreConfigType Icu_CoreConfigCore0 =
{
    /* Maximum number of the channels allocated to the core0 */
    ICU_MAX_CHANNEL_TO_CORE0,
    /* Icu configuration information of core0 */
    &Icu_ChannelConfigSetCore0[0]
};

/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"

/* Icu Channel(s) configuration informations which mapped to Core1 */
/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"
static const Gtm_Icu_Config Icu_ConfigCore1[]=
{
    /* IcuChannel_4 */
    {
        /* IcuMeasurementMode */
        (Gtm_Icu_Mode)ICU_MODE_SIGNAL_MEASUREMENT,
        /* Clock */
        GTM_CMU_CLK_1,
        /*input*/    
        GTM_TIM_INPUT_CURRENTCHANNEL,
        /*edge*/        
        GTM_TIM_EDGE_CAP_RISE,
        /*Filter*/
        NULL_PTR,
        /*ctrlMethodSetPtr*/
        NULL_PTR,
        /* Enables resetting of counter in certain modes */
        FALSE,
        /* Interrupt */
        {
            4U,/* Cnt OverFlow */
            GTM_IRQMODE_LEVEL
        },
        FALSE,
        /*AuxInConfig*/
        {
            /* IsChIndexBiggerThan7 */
            FALSE,
            FALSE,
            FALSE,
        },
    },
    
    /* IcuChannel_5 */
    {
        /* IcuMeasurementMode */
        (Gtm_Icu_Mode)ICU_MODE_SIGNAL_EDGE_DETECT,
        /* Clock */
        GTM_CMU_CLK_1,
        /*input*/    
        GTM_TIM_INPUT_CURRENTCHANNEL,
        /*edge*/        
        GTM_TIM_EDGE_CAP_FALL,
        /*Filter*/
        NULL_PTR,
        /*ctrlMethodSetPtr*/
        NULL_PTR,
        /* Enables resetting of counter in certain modes */
        FALSE,
        /* Interrupt */
        {
            1U,/* NewValue */
            GTM_IRQMODE_LEVEL
        },
        FALSE,
        /*AuxInConfig*/
        {
            /* IsChIndexBiggerThan7 */
            FALSE,
            FALSE,
            FALSE,
        },
    },
    
    /* IcuChannel_6 */
    {
        /* IcuMeasurementMode */
        (Gtm_Icu_Mode)ICU_MODE_EDGE_COUNTER,
        /* Clock */
        GTM_CMU_CLK_1,
        /*input*/    
        GTM_TIM_INPUT_CURRENTCHANNEL,
        /*edge*/        
        GTM_TIM_EDGE_CAP_RISE,
        /*Filter*/
        NULL_PTR,
        /*ctrlMethodSetPtr*/
        NULL_PTR,
        /* Enables resetting of counter in certain modes */
        FALSE,
        /* Interrupt */
        {
            4U,/* Cnt OverFlow */
            GTM_IRQMODE_LEVEL
        },
        FALSE,
        /*AuxInConfig*/
        {
            /* IsChIndexBiggerThan7 */
            FALSE,
            FALSE,
            FALSE,
        },
    },
    
    /* IcuChannel_7 */
    {
        /* IcuMeasurementMode */
        (Gtm_Icu_Mode)ICU_MODE_TIMESTAMP,
        /* Clock */
        GTM_CMU_CLK_1,
        /*input*/    
        GTM_TIM_INPUT_CURRENTCHANNEL,
        /*edge*/        
        GTM_TIM_EDGE_CAP_RISE,
        /*Filter*/
        NULL_PTR,
        /*ctrlMethodSetPtr*/
        NULL_PTR,
        /* Enables resetting of counter in certain modes */
        FALSE,
        /* Interrupt */
        {
            1U,/* NewValue */
            GTM_IRQMODE_LEVEL
        },
        FALSE,
        /*AuxInConfig*/
        {
            /* IsChIndexBiggerThan7 */
            FALSE,
            FALSE,
            FALSE,
        },
    },
    
};

static const Icu_ChnConfigType Icu_ChannelConfigCore1[ICU_MAX_CHANNEL_TO_CORE1]=
{
    /* ICU Channel 4 */
    {
        4U,
        /* Notification function pointer */
        NULL_PTR,
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_0,
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_1,
        /* ChannelProperties */        
        ICU_MEASUREMENT_PRO_DUTY_CYCLE,
        /* Tim_ConfigPtr */
        &Icu_ConfigCore1[0],
        /* IsWakeupChannel */
        FALSE,
        /* WakeupSourceCfgInfo */
        0U,/*Not applicable*/
    },
    /* ICU Channel 5 */
    {
        5U,
        /* Notification function pointer */
        &Icu_SignalNotification_5,
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_0,
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_2,
        /* ChannelProperties */        
        0x00,
        /* Tim_ConfigPtr */
        &Icu_ConfigCore1[1],
        /* IsWakeupChannel */
        FALSE,
        /* WakeupSourceCfgInfo */
        0U,/*Not applicable*/
    },
    /* ICU Channel 6 */
    {
        6U,
        /* Notification function pointer */
        NULL_PTR,
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_0,
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_3,
        /* ChannelProperties */        
        0x00,
        /* Tim_ConfigPtr */
        &Icu_ConfigCore1[2],
        /* IsWakeupChannel */
        FALSE,
        /* WakeupSourceCfgInfo */
        0U,/*Not applicable*/
    },
    /* ICU Channel 7 */
    {
        7U,
        /* Notification function pointer */
        &Icu_TimestampNotification_7,
        /* Index of HW GTM-TIM module */
        GTM_TIM_INDEX_0,
        /* Index of HW channel index inside the GTM-TIM module */
        GTM_TIM_CH_INDEX_4,
        /* ChannelProperties */        
        (uint8)ICU_CIRCULAR_BUFFER,
        /* Tim_ConfigPtr */
        &Icu_ConfigCore1[3],
        /* IsWakeupChannel */
        FALSE,
        /* WakeupSourceCfgInfo */
        0U,/*Not applicable*/
    },
};

static const Icu_ChannelConfigType Icu_ChannelConfigSetCore1[] =
{
    {
        /* Icu_ChnConfigType */
        &Icu_ChannelConfigCore1[0],
    }
};

/* Icu channel number and configuration information in Core1 */
static const Icu_CoreConfigType Icu_CoreConfigCore1 =
{
    /* Maximum number of the channels allocated to the core1 */
    ICU_MAX_CHANNEL_TO_CORE1,
    /* Icu configuration information of core1 */
    &Icu_ChannelConfigSetCore1[0]
};

/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"

/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"

/* 
This array is used for mapping Icu Channel to the Core. 
Array index is Icu channel -> array member is index of Icu_ChannelConfigSetCorex[x=0~4]
*/
static const Icu_MappingType Icu_ChannelToCoreMap[ICU_TOTAL_CHANNEL_NUMBER] =
{
/* Index, executionCore */
    /* IcuChannel_0 */
    {0U, MULTICOREID_CPU0},
    /* IcuChannel_1 */
    {1U, MULTICOREID_CPU0},
    /* IcuChannel_2 */
    {2U, MULTICOREID_CPU0},
    /* IcuChannel_3 */
    {3U, MULTICOREID_CPU0},
    /* IcuChannel_4 */
    {0U, MULTICOREID_CPU1},
    /* IcuChannel_5 */
    {1U, MULTICOREID_CPU1},
    /* IcuChannel_6 */
    {2U, MULTICOREID_CPU1},
    /* IcuChannel_7 */
    {3U, MULTICOREID_CPU1}
};

/* Mapping the hardware channel(GTM-TIM) index and logic channel index.
* Index of array is hardware index, the data of the index is logic channel id */
/* #Violation: Icu_PBcfg_c_REF_1 */
static const uint8 Icu_HwTimChannelMap[64U] =
{
    /* TIM0_CH0 */
    0U,
    /* TIM0_CH1 */
    4U,
    /* TIM0_CH2 */
    5U,
    /* TIM0_CH3 */
    6U,
    /* TIM0_CH4 */
    7U,
    /* TIM0_CH5 */
    2U,
    /* TIM0_CH6 */
    0xFFU,
    /* TIM0_CH7 */
    0xFFU,
    /* TIM1_CH0 */
    0xFFU,
    /* TIM1_CH1 */
    0xFFU,
    /* TIM1_CH2 */
    0xFFU,
    /* TIM1_CH3 */
    0xFFU,
    /* TIM1_CH4 */
    0xFFU,
    /* TIM1_CH5 */
    0xFFU,
    /* TIM1_CH6 */
    0xFFU,
    /* TIM1_CH7 */
    0xFFU,
    /* TIM2_CH0 */
    3U,
    /* TIM2_CH1 */
    1U,
    /* TIM2_CH2 */
    0xFFU,
    /* TIM2_CH3 */
    0xFFU,
    /* TIM2_CH4 */
    0xFFU,
    /* TIM2_CH5 */
    0xFFU,
    /* TIM2_CH6 */
    0xFFU,
    /* TIM2_CH7 */
    0xFFU,
    /* TIM3_CH0 */
    0xFFU,
    /* TIM3_CH1 */
    0xFFU,
    /* TIM3_CH2 */
    0xFFU,
    /* TIM3_CH3 */
    0xFFU,
    /* TIM3_CH4 */
    0xFFU,
    /* TIM3_CH5 */
    0xFFU,
    /* TIM3_CH6 */
    0xFFU,
    /* TIM3_CH7 */
    0xFFU,
    /* TIM4_CH0 */
    0xFFU,
    /* TIM4_CH1 */
    0xFFU,
    /* TIM4_CH2 */
    0xFFU,
    /* TIM4_CH3 */
    0xFFU,
    /* TIM4_CH4 */
    0xFFU,
    /* TIM4_CH5 */
    0xFFU,
    /* TIM4_CH6 */
    0xFFU,
    /* TIM4_CH7 */
    0xFFU,
    /* TIM5_CH0 */
    0xFFU,
    /* TIM5_CH1 */
    0xFFU,
    /* TIM5_CH2 */
    0xFFU,
    /* TIM5_CH3 */
    0xFFU,
    /* TIM5_CH4 */
    0xFFU,
    /* TIM5_CH5 */
    0xFFU,
    /* TIM5_CH6 */
    0xFFU,
    /* TIM5_CH7 */
    0xFFU,
    /* TIM6_CH0 */
    0xFFU,
    /* TIM6_CH1 */
    0xFFU,
    /* TIM6_CH2 */
    0xFFU,
    /* TIM6_CH3 */
    0xFFU,
    /* TIM6_CH4 */
    0xFFU,
    /* TIM6_CH5 */
    0xFFU,
    /* TIM6_CH6 */
    0xFFU,
    /* TIM6_CH7 */
    0xFFU,
    /* TIM7_CH0 */
    0xFFU,
    /* TIM7_CH1 */
    0xFFU,
    /* TIM7_CH2 */
    0xFFU,
    /* TIM7_CH3 */
    0xFFU,
    /* TIM7_CH4 */
    0xFFU,
    /* TIM7_CH5 */
    0xFFU,
    /* TIM7_CH6 */
    0xFFU,
    /* TIM7_CH7 */
    0xFFU
};

/* Configuration parameters */
/* #Violation: Icu_PBcfg_c_REF_2*/
const Icu_ConfigType Icu_ConfigSet[1U] =
{
    {
        {
            /* Pointer to Core Configuration structure */
            /* configuration information of core0 */
            &Icu_CoreConfigCore0,
            /* configuration information of core1 */
            &Icu_CoreConfigCore1
        },
        /* Table for relationship between channel ID in specified core and ICU channel ID */
        &Icu_ChannelToCoreMap[0U],
        /* Pointer to GTM-TIM channel mapping with logic channel */
        &Icu_HwTimChannelMap[0U]
    }
};
/* #Violation: Icu_PBcfg_c_REF_3 */
#define ICU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Icu_PBcfg_c_REF_2 */
#include "Icu_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
