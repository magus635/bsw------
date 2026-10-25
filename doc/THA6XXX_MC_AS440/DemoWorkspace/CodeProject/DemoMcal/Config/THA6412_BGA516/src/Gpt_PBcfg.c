/****************************************************************************************************
*   FileName              : Gpt_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all post-build parameters in GPT Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*           
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
****************************************************************************************************/
/*
*#Violation Summary
*
*#Gpt_PBcfg_c_REF_1:MISRAC2012-Rule-11.4; 
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Gpt_PBcfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
*
*#Gpt_PBcfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Gpt_PBcfg_c_REF_4:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Gpt.h"
#include "Gpt_Cfg.h"

/****************************************************************************************************
**                          GLOBAL VARIABLES                                                       **
****************************************************************************************************/

/****************************************************************************************************
**                          Configurations                                                         **
****************************************************************************************************/

/* Notification Function Declarations */
extern void Gpt_Notification_0(void);
extern void Gpt_Notification_1(void);
extern void Gpt_Notification_2(void);
extern void Gpt_Notification_3(void);
extern void Gpt_Notification_UartPrintf(void);
extern void Gpt_Notification_5(void);
extern void Gpt_Notification_6(void);
extern void Gpt_Notification_7(void);
extern void Gpt_Notification_8(void);
extern void Gpt_Notification_9(void);

/****************************************************************************************************
********                    Low level driver configurations                                  ********
****************************************************************************************************/

/****************************************************************************************************
**              Low level driver configurations of the channel based on GTM                        **
****************************************************************************************************/
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"

/* #Violation: Gpt_PBcfg_c_REF_3 */
static const Gpt_GtmConfigType Gpt_GtmChannelConfig[6U] =
{
    /* GptChannelConfiguration_0 low level driver configuration */
    {
        /* Channel Hardware index */
        {
            /* GTM Submodule Id */
            (uint8)GTM_OUTPUT_MODULE_TOM,
            /* Low level timer module Id */
            (uint8)GTM_TOM_INDEX_0,
            /* Group index, only used for TIO module */
            0U,
            /* Low level timer channel Id */
            (uint8)GTM_TOM_CH_INDEX_0
        },
        /* Channel Hardware Configuration */
        {
            /* Channel Clock Source, the current frequency is 1000000.0Hz */
            GTM_TOM_CH_CLKSRC_CMUFXCLK0,
            /* Channel Interrupt Signal Level */
            GTM_IRQMODE_LEVEL,
            /* Channel Output Trigger Signal */
            GTM_TOM_CH_TRIGOUT_FORWARD,
            /*Channel Timer One-Shot Mode */
            FALSE,    
            /*Channel Interrupt Control */
            FALSE
        }
    },
    /* GptChannelConfiguration_1 low level driver configuration */
    {
        /* Channel Hardware index */
        {
            /* GTM Submodule Id */
            (uint8)GTM_OUTPUT_MODULE_TOM,
            /* Low level timer module Id */
            (uint8)GTM_TOM_INDEX_0,
            /* Group index, only used for TIO module */
            0U,
            /* Low level timer channel Id */
            (uint8)GTM_TOM_CH_INDEX_1
        },
        /* Channel Hardware Configuration */
        {
            /* Channel Clock Source, the current frequency is 1000000.0Hz */
            GTM_TOM_CH_CLKSRC_CMUFXCLK0,
            /* Channel Interrupt Signal Level */
            GTM_IRQMODE_LEVEL,
            /* Channel Output Trigger Signal */
            GTM_TOM_CH_TRIGOUT_FORWARD,
            /*Channel Timer One-Shot Mode */
            TRUE,    
            /*Channel Interrupt Control */
            FALSE
        }
    },
    /* GptChannelConfiguration_2 low level driver configuration */
    {
        /* Channel Hardware index */
        {
            /* GTM Submodule Id */
            (uint8)GTM_OUTPUT_MODULE_TOM,
            /* Low level timer module Id */
            (uint8)GTM_TOM_INDEX_0,
            /* Group index, only used for TIO module */
            0U,
            /* Low level timer channel Id */
            (uint8)GTM_TOM_CH_INDEX_2
        },
        /* Channel Hardware Configuration */
        {
            /* Channel Clock Source, the current frequency is 1000000.0Hz */
            GTM_TOM_CH_CLKSRC_CMUFXCLK0,
            /* Channel Interrupt Signal Level */
            GTM_IRQMODE_LEVEL,
            /* Channel Output Trigger Signal */
            GTM_TOM_CH_TRIGOUT_FORWARD,
            /*Channel Timer One-Shot Mode */
            FALSE,    
            /*Channel Interrupt Control */
            FALSE
        }
    },
    /* GptChannelConfiguration_3 low level driver configuration */
    {
        /* Channel Hardware index */
        {
            /* GTM Submodule Id */
            (uint8)GTM_OUTPUT_MODULE_TOM,
            /* Low level timer module Id */
            (uint8)GTM_TOM_INDEX_0,
            /* Group index, only used for TIO module */
            0U,
            /* Low level timer channel Id */
            (uint8)GTM_TOM_CH_INDEX_3
        },
        /* Channel Hardware Configuration */
        {
            /* Channel Clock Source, the current frequency is 1000000.0Hz */
            GTM_TOM_CH_CLKSRC_CMUFXCLK0,
            /* Channel Interrupt Signal Level */
            GTM_IRQMODE_LEVEL,
            /* Channel Output Trigger Signal */
            GTM_TOM_CH_TRIGOUT_FORWARD,
            /*Channel Timer One-Shot Mode */
            TRUE,    
            /*Channel Interrupt Control */
            FALSE
        }
    },
    /* GptChannelConfiguration_6 low level driver configuration */
    {
        /* Channel Hardware index */
        {
            /* GTM Submodule Id */
            (uint8)GTM_OUTPUT_MODULE_TOM,
            /* Low level timer module Id */
            (uint8)GTM_TOM_INDEX_0,
            /* Group index, only used for TIO module */
            0U,
            /* Low level timer channel Id */
            (uint8)GTM_TOM_CH_INDEX_10
        },
        /* Channel Hardware Configuration */
        {
            /* Channel Clock Source, the current frequency is 1000000.0Hz */
            GTM_TOM_CH_CLKSRC_CMUFXCLK0,
            /* Channel Interrupt Signal Level */
            GTM_IRQMODE_LEVEL,
            /* Channel Output Trigger Signal */
            GTM_TOM_CH_TRIGOUT_FORWARD,
            /*Channel Timer One-Shot Mode */
            FALSE,    
            /*Channel Interrupt Control */
            FALSE
        }
    },
    /* GptForMcu_SetMode low level driver configuration */
    {
        /* Channel Hardware index */
        {
            /* GTM Submodule Id */
            (uint8)GTM_OUTPUT_MODULE_TOM,
            /* Low level timer module Id */
            (uint8)GTM_TOM_INDEX_1,
            /* Group index, only used for TIO module */
            0U,
            /* Low level timer channel Id */
            (uint8)GTM_TOM_CH_INDEX_8
        },
        /* Channel Hardware Configuration */
        {
            /* Channel Clock Source, the current frequency is 1000000.0Hz */
            GTM_TOM_CH_CLKSRC_CMUFXCLK0,
            /* Channel Interrupt Signal Level */
            GTM_IRQMODE_LEVEL,
            /* Channel Output Trigger Signal */
            GTM_TOM_CH_TRIGOUT_FORWARD,
            /*Channel Timer One-Shot Mode */
            TRUE,    
            /*Channel Interrupt Control */
            FALSE
        }
    }
};

/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"

/****************************************************************************************************
**              Low level driver configurations of the channel based on Base Timer                 **
****************************************************************************************************/
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"

/* #Violation: Gpt_PBcfg_c_REF_3 */
static const Gpt_BasetimerConfigType Gpt_BasetimerChannelConfig[4U] =
{
    /* GptChannelConfiguration_7 */
    {
        /* Base timer object */
        /* #Violation: Gpt_PBcfg_c_REF_1 */
        BASETIMER0,
        /* Channel Configuration */
        {
            /* Specifies the counter size */
            BASETIMER_SIZE_32BITS,
            /* Specifies the initial counter value */
            0U,
            /* Specifies the counter mode */
            BASETIMER_MODE_PERIODIC
        }
    },
    /* GptChannelConfiguration_8 */
    {
        /* Base timer object */
        /* #Violation: Gpt_PBcfg_c_REF_1 */
        BASETIMER1,
        /* Channel Configuration */
        {
            /* Specifies the counter size */
            BASETIMER_SIZE_32BITS,
            /* Specifies the initial counter value */
            0U,
            /* Specifies the counter mode */
            BASETIMER_MODE_PERIODIC
        }
    },
    /* GptChannelConfiguration_9 */
    {
        /* Base timer object */
        /* #Violation: Gpt_PBcfg_c_REF_1 */
        BASETIMER2,
        /* Channel Configuration */
        {
            /* Specifies the counter size */
            BASETIMER_SIZE_32BITS,
            /* Specifies the initial counter value */
            0U,
            /* Specifies the counter mode */
            BASETIMER_MODE_ONESHOT
        }
    },
    /* GptChannelConfiguration_10 */
    {
        /* Base timer object */
        /* #Violation: Gpt_PBcfg_c_REF_1 */
        BASETIMER3,
        /* Channel Configuration */
        {
            /* Specifies the counter size */
            BASETIMER_SIZE_32BITS,
            /* Specifies the initial counter value */
            0U,
            /* Specifies the counter mode */
            BASETIMER_MODE_ONESHOT
        }
    }
};

/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"

/****************************************************************************************************
**                               MCAL driver configurations                                        **
****************************************************************************************************/
/****************************************************************************************************
**                                  Core0       configurations                                     **
****************************************************************************************************/
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
static const Gpt_ChConfigType Gpt_Core0ChannelConfig[GPT_MAX_CHANNEL_TO_CORE0] =
{
    /* GptChannelConfiguration_0 */
    {
        /* Channel Id */
        0U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffU,
        /* Notification function pointer */
        Gpt_Notification_0,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_GTM
    },
    /* GptChannelConfiguration_1 */
    {
        /* Channel Id */
        1U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffU,
        /* Notification function pointer */
        Gpt_Notification_1,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_GTM
    },
    /* GptChannelConfiguration_6 */
    {
        /* Channel Id */
        4U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffU,
        /* Notification function pointer */
        Gpt_Notification_UartPrintf,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_GTM
    },
    /* GptChannelConfiguration_7 */
    {
        /* Channel Id */
        5U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffffffU,
        /* Notification function pointer */
        Gpt_Notification_5,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_BASETIMER
    },
    /* GptChannelConfiguration_9 */
    {
        /* Channel Id */
        7U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffffffU,
        /* Notification function pointer */
        Gpt_Notification_7,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_BASETIMER
    },
    /* GptForMcu_SetMode */
    {
        /* Channel Id */
        9U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffU,
        /* Notification function pointer */
        Gpt_Notification_9,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_GTM
    }
};

/* GPT channels configuration of core0 */
static const Gpt_CoreConfigType Gpt_CoreConfigCore0 =
{
    /* Number of core0 maximum channels */
    6U,
    /*Channel configuration*/
    &Gpt_Core0ChannelConfig[0]
};
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
/****************************************************************************************************
**                                  Core1       configurations                                     **
****************************************************************************************************/
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
static const Gpt_ChConfigType Gpt_Core1ChannelConfig[GPT_MAX_CHANNEL_TO_CORE1] =
{
    /* GptChannelConfiguration_2 */
    {
        /* Channel Id */
        2U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffU,
        /* Notification function pointer */
        Gpt_Notification_2,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_GTM
    },
    /* GptChannelConfiguration_3 */
    {
        /* Channel Id */
        3U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffU,
        /* Notification function pointer */
        Gpt_Notification_3,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_GTM
    },
    /* GptChannelConfiguration_8 */
    {
        /* Channel Id */
        6U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffffffU,
        /* Notification function pointer */
        Gpt_Notification_6,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_BASETIMER
    },
    /* GptChannelConfiguration_10 */
    {
        /* Channel Id */
        8U,
        /* Wakeup enable state */
        FALSE,
        /* Maximum tick */
        0xffffffffU,
        /* Notification function pointer */
        Gpt_Notification_8,
        /* Wakeup information to EcuM_SetWakeupEvent */
        0,
        /* Hardware class of logic channel */
        GPT_HW_BASETIMER
    }
};

/* GPT channels configuration of core1 */
static const Gpt_CoreConfigType Gpt_CoreConfigCore1 =
{
    /* Number of core1 maximum channels */
    4U,
    /*Channel configuration*/
    &Gpt_Core1ChannelConfig[0]
};
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"

    /* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
/* This array is used for mapping Gpt Channel to the Core 
 * and mapping the hardware configuration to logic channel */
static const Gpt_MappingType Gpt_ChannelToCoreMap[GPT_MAX_CHANNELS] =
{
    /* GptChannelConfiguration_0 */
    {
        /* Core number */
        (uint8)MCAL_CORE0, 
        /* Channel index in specific core */
        0U,
        /* Hardware configuration mapping index */
        0U
    },
    /* GptChannelConfiguration_1 */
    {
        /* Core number */
        (uint8)MCAL_CORE0, 
        /* Channel index in specific core */
        1U,
        /* Hardware configuration mapping index */
        1U
    },
    /* GptChannelConfiguration_2 */
    {
        /* Core number */
        (uint8)MCAL_CORE1, 
        /* Channel index in specific core */
        0U,
        /* Hardware configuration mapping index */
        2U
    },
    /* GptChannelConfiguration_3 */
    {
        /* Core number */
        (uint8)MCAL_CORE1, 
        /* Channel index in specific core */
        1U,
        /* Hardware configuration mapping index */
        3U
    },
    /* GptChannelConfiguration_6 */
    {
        /* Core number */
        (uint8)MCAL_CORE0, 
        /* Channel index in specific core */
        2U,
        /* Hardware configuration mapping index */
        4U
    },
    /* GptChannelConfiguration_7 */
    {
        /* Core number */
        (uint8)MCAL_CORE0, 
        /* Channel index in specific core */
        3U,
        /* Hardware configuration mapping index */
        0U
    },
    /* GptChannelConfiguration_8 */
    {
        /* Core number */
        (uint8)MCAL_CORE1, 
        /* Channel index in specific core */
        2U,
        /* Hardware configuration mapping index */
        1U
    },
    /* GptChannelConfiguration_9 */
    {
        /* Core number */
        (uint8)MCAL_CORE0, 
        /* Channel index in specific core */
        4U,
        /* Hardware configuration mapping index */
        2U
    },
    /* GptChannelConfiguration_10 */
    {
        /* Core number */
        (uint8)MCAL_CORE1, 
        /* Channel index in specific core */
        3U,
        /* Hardware configuration mapping index */
        3U
    },
    /* GptForMcu_SetMode */
    {
        /* Core number */
        (uint8)MCAL_CORE0, 
        /* Channel index in specific core */
        5U,
        /* Hardware configuration mapping index */
        5U
    }
};
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"

/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
  
/* Mapping the hardware channel(GTM-TOM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Gpt_PBcfg_c_REF_3 */
static const uint8 Gpt_HwTomChannelMap[80U] =
{
      /* TOM0_CH0 */
      0U,
      /* TOM0_CH1 */
      1U,
      /* TOM0_CH2 */
      2U,
      /* TOM0_CH3 */
      3U,
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
      4U,
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
      0xFFU,
      /* TOM1_CH2 */
      0xFFU,
      /* TOM1_CH3 */
      0xFFU,
      /* TOM1_CH4 */
      0xFFU,
      /* TOM1_CH5 */
      0xFFU,
      /* TOM1_CH6 */
      0xFFU,
      /* TOM1_CH7 */
      0xFFU,
      /* TOM1_CH8 */
      9U,
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

/* Mapping the hardware channel(BASETIMER) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Gpt_PBcfg_c_REF_3 */
static const uint8 Gpt_HwBasetimerChannelMap[6U] =
{
  /* BASETIMER0 */
  5U,
  /* BASETIMER1 */
  6U,
  /* BASETIMER2 */
  7U,
  /* BASETIMER3 */
  8U,
  /* BASETIMER4 */
  0xFFU,
  /* BASETIMER5 */
  0xFFU
};


/* Configuration parameters */
const Gpt_ConfigType Gpt_ConfigSet[1U] =
{
    {
        {
            /* GPT channels configuration's pointer of core0 */
            &Gpt_CoreConfigCore0,
            /* GPT channels configuration's pointer of core1 */
            &Gpt_CoreConfigCore1,
            /* GPT channels configuration's pointer of core2 */
            NULL_PTR,
            /* GPT channels configuration's pointer of core3 */
            NULL_PTR
        },
        /* Table for relationship between channel ID in specified core and GPT channel ID */
        &Gpt_ChannelToCoreMap[0U],
        /* Hardware configuration for channel based on GTM */
        &Gpt_GtmChannelConfig[0U],
        /* Hardware configuration for channel based on base timer */
        &Gpt_BasetimerChannelConfig[0U],
        {
            /* Pointer to GTM-TOM channel mapping with logic channel */
            &Gpt_HwTomChannelMap[0U],
            /* Pointer to BASETIMER channel mapping with logic channel */
            &Gpt_HwBasetimerChannelMap[0U]
        },
        {
            /* Pointer to 1us predef timer base address */
            /* #Violation: Gpt_PBcfg_c_REF_1 */
            BASETIMER4,
            /* Pointer to 100us predef timer base address */
            /* #Violation: Gpt_PBcfg_c_REF_1 */
            BASETIMER5
        }
    }
};

/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
