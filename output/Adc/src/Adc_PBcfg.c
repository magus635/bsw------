/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Adc_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : SARADC
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Adc_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Adc_PBcfg_c_REF_2:MISRAC2012-Rule-10.5;
* Justification:Redundant cast is necessary to maintain the software structure and reduce the 
* complexity.
*
*#Adc_PBcfg_c_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Adc_PBcfg_c_REF_4:CertC-DLC06-C
* Justification:The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Adc_PBcfg_c_REF_5:CWE-547
* Justification:The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#include "Adc.h"


/****************************************************************************************************
**                          External Function Declarations                                         **
****************************************************************************************************/
/* HWTrigDemo/GroupHwTrig notification function declaration */
extern void AdcDemo_Adc0HwTrigNotif(void);
/* HWTrigDemo/GroupHwResultAccumulation notification function declaration */
extern void AdcDemo_Adc0HwTrigRsltAccumNotif(void);
/* SWTrigDemo/GroupContinuous notification function declaration */
extern void AdcDemo_Adc2ContinuousNotif(void);

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/* Configuration informations which mapped to Core0 */
/* #Violation: Adc_PBcfg_c_REF_3 */
#define ADC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Adc_PBcfg_c_REF_1 */
#include "Adc_MemMap.h"

/* ADC0 Group "HWTrigDemo" configuration */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit0GroupHwTrig[8] =
{
    /* Total number of channels assigned to the group 'GroupHwTrig' of HwUnit0 */
    7U,

    /* The channels assigned to the group 'GroupHwTrig' of HwUnit0 */
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit0GroupHwTrigStreaming[4] =
{
    /* Total number of channels assigned to the group 'GroupHwTrigStreaming' of HwUnit0 */
    3U,

    /* The channels assigned to the group 'GroupHwTrigStreaming' of HwUnit0 */
    2U,
    4U,
    6U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit0GroupHwResultAccumulation[8] =
{
    /* Total number of channels assigned to the group 'GroupHwResultAccumulation' of HwUnit0 */
    7U,

    /* The channels assigned to the group 'GroupHwResultAccumulation' of HwUnit0 */
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit0GroupSyncConv[2] =
{
    /* Total number of channels assigned to the group 'GroupSyncConv' of HwUnit0 */
    1U,

    /* The channels assigned to the group 'GroupSyncConv' of HwUnit0 */
    7U
};
/* ADC1 Group "DmaTransferDemo" configuration */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit1GroupSwTrig[5] =
{
    /* Total number of channels assigned to the group 'GroupSwTrig' of HwUnit1 */
    4U,

    /* The channels assigned to the group 'GroupSwTrig' of HwUnit1 */
    0U,
    1U,
    2U,
    3U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit1GroupSwTrig_DmaLinkedList[5] =
{
    /* Total number of channels assigned to the group 'GroupSwTrig_DmaLinkedList' of HwUnit1 */
    4U,

    /* The channels assigned to the group 'GroupSwTrig_DmaLinkedList' of HwUnit1 */
    4U,
    5U,
    6U,
    7U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit1GroupSwTrig_ResRegConf[7] =
{
    /* Total number of channels assigned to the group 'GroupSwTrig_ResRegConf' of HwUnit1 */
    6U,

    /* The channels assigned to the group 'GroupSwTrig_ResRegConf' of HwUnit1 */
    0U,
    1U,
    2U,
    3U,
    4U,
    5U
};
/* Result register configuration of the channels assigned to the group 'GroupSwTrig_ResRegConf' of HwUnit1 */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const uint8 Adc_ChResRegsInHwUnit1GroupSwTrig_ResRegConf[7] =
{
    15U,
    15U,
    15U,
    15U,
    15U,
    15U
};
/* ADC8 Group "PollingModeDemo" configuration */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit8GroupHwPolling[9] =
{
    /* Total number of channels assigned to the group 'GroupHwPolling' of HwUnit8 */
    8U,

    /* The channels assigned to the group 'GroupHwPolling' of HwUnit8 */
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit8GroupHwStreaming[6] =
{
    /* Total number of channels assigned to the group 'GroupHwStreaming' of HwUnit8 */
    5U,

    /* The channels assigned to the group 'GroupHwStreaming' of HwUnit8 */
    0U,
    2U,
    4U,
    6U,
    7U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit8GroupSwPolling[8] =
{
    /* Total number of channels assigned to the group 'GroupSwPolling' of HwUnit8 */
    7U,

    /* The channels assigned to the group 'GroupSwPolling' of HwUnit8 */
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit8GroupSwStreaming[4] =
{
    /* Total number of channels assigned to the group 'GroupSwStreaming' of HwUnit8 */
    3U,

    /* The channels assigned to the group 'GroupSwStreaming' of HwUnit8 */
    1U,
    3U,
    5U
};
/* ADC Groups are arranged in the order of their trigger type ( HW/SW ) and
request sources (RS0 .. RS2) starting from SW trigger RS0 to SW trigger
RS2 and then HW trigger RS0 to HW trigger RS2. */
/* HW trigger configuration parameters for GroupHwTrig: channel 0 */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Saradc_GatingTriggerConfig Adc_HwUnit0Group0HwTrigConfig =
{
    /* Gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER0,
    /* Trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER0,
    /* Start conversion after HW trigger request occurs */
    SARADC_GATINGMODE_ALWAYS,
    /* Trigger signal edge */
    /* #Violation: Adc_PBcfg_c_REF_2 */
    (Saradc_TriggerMode)ADC_HW_TRIG_RISING_EDGE,
    /* Not used timer trigger */
    {
        FALSE,
        0U,
        SARADC_TIMERMODE_STOP
    }
};
/* HW trigger configuration parameters for GroupHwTrigStreaming: channel 1 */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Saradc_GatingTriggerConfig Adc_HwUnit0Group1HwTrigConfig =
{
    /* Gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER0,
    /* Trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER0,
    /* Start conversion after HW trigger request occurs */
    SARADC_GATINGMODE_ALWAYS,
    /* Trigger signal edge */
    /* #Violation: Adc_PBcfg_c_REF_2 */
    (Saradc_TriggerMode)ADC_HW_TRIG_BOTH_EDGES,
    /* Not used timer trigger */
    {
        FALSE,
        0U,
        SARADC_TIMERMODE_STOP
    }
};
/* HW trigger configuration parameters for GroupHwResultAccumulation: channel 2 */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Saradc_GatingTriggerConfig Adc_HwUnit0Group2HwTrigConfig =
{
    /* Gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER0,
    /* Trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER0,
    /* Start conversion after HW trigger request occurs */
    SARADC_GATINGMODE_ALWAYS,
    /* Trigger signal edge */
    /* #Violation: Adc_PBcfg_c_REF_2 */
    (Saradc_TriggerMode)ADC_HW_TRIG_RISING_EDGE,
    /* Not used timer trigger */
    {
        FALSE,
        0U,
        SARADC_TIMERMODE_STOP
    }
};
/* HW trigger configuration parameters for GroupSyncConv: channel 3 */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Saradc_GatingTriggerConfig Adc_HwUnit0Group3HwTrigConfig =
{
    /* Gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER0,
    /* Trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER0,
    /* Start conversion after HW trigger request occurs */
    SARADC_GATINGMODE_ALWAYS,
    /* Trigger signal edge */
    /* #Violation: Adc_PBcfg_c_REF_2 */
    (Saradc_TriggerMode)ADC_HW_TRIG_RISING_EDGE,
    /* Not used timer trigger */
    {
        FALSE,
        0U,
        SARADC_TIMERMODE_STOP
    }
};
/* ADC HwUnit0 Group configuration */
static const Adc_GroupCfgType Adc_HwUnit0GrpCfg[ADC_CFG_GROUPS_HWUNIT_ADC0] =
{
    /* Group 'GroupHwTrig' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0x7f,
        /* Notification function pointer */
        AdcDemo_Adc0HwTrigNotif,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit0GroupHwTrig[0U],
        /* ADC0 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* Pointer to the HW trigger configuration parameters */
        &Adc_HwUnit0Group0HwTrigConfig,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_HW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_CIRCULAR
    },
    /* Group 'GroupHwTrigStreaming' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        5U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0x54,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit0GroupHwTrigStreaming[0U],
        /* ADC0 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* Pointer to the HW trigger configuration parameters */
        &Adc_HwUnit0Group1HwTrigConfig,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_HW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE1,
        /* Group access mode */
        ADC_ACCESS_MODE_STREAMING,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    },
    /* Group 'GroupHwResultAccumulation' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0x7f,
        /* Notification function pointer */
        AdcDemo_Adc0HwTrigRsltAccumNotif,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit0GroupHwResultAccumulation[0U],
        /* ADC0 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* Pointer to the HW trigger configuration parameters */
        &Adc_HwUnit0Group2HwTrigConfig,
        /* Enable result accumulation mode */
        15U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_HW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_CIRCULAR
    },
    /* Group 'GroupSyncConv' */
    {
        /* Exists at least a sync channel under this group */
        TRUE,
        /* Number of ADC values to be acquired in streaming access mode */
        5U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0x80,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit0GroupSyncConv[0U],
        /* ADC0 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* Pointer to the HW trigger configuration parameters */
        &Adc_HwUnit0Group3HwTrigConfig,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_HW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_STREAMING,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    }
};
/* ADC HwUnit1 Group configuration */
static const Adc_GroupCfgType Adc_HwUnit1GrpCfg[ADC_CFG_GROUPS_HWUNIT_ADC1] =
{
    /* Group 'GroupSwTrig' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0xf,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit1GroupSwTrig[0U],
        /* Manual allocation of the result register is not supported for this channel.
        (AdcResultRegisterManual = false). */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    },
    /* Group 'GroupSwTrig_DmaLinkedList' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0xf0,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit1GroupSwTrig_DmaLinkedList[0U],
        /* Manual allocation of the result register is not supported for this channel.
        (AdcResultRegisterManual = false). */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    },
    /* Group 'GroupSwTrig_ResRegConf' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0x3f,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit1GroupSwTrig_ResRegConf[0U],
        /* Result register configuration of the channels assigned to the group */
        &Adc_ChResRegsInHwUnit1GroupSwTrig_ResRegConf[0U],
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    }
};
/* HW trigger configuration parameters for GroupHwPolling: channel 256 */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Saradc_GatingTriggerConfig Adc_HwUnit8Group256HwTrigConfig =
{
    /* Gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER1,
    /* Trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER1,
    /* Start conversion after HW trigger request occurs */
    SARADC_GATINGMODE_ALWAYS,
    /* Trigger signal edge */
    /* #Violation: Adc_PBcfg_c_REF_2 */
    (Saradc_TriggerMode)ADC_HW_TRIG_FALLING_EDGE,
    /* Not used timer trigger */
    {
        FALSE,
        0U,
        SARADC_TIMERMODE_STOP
    }
};
/* HW trigger configuration parameters for GroupHwStreaming: channel 257 */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Saradc_GatingTriggerConfig Adc_HwUnit8Group257HwTrigConfig =
{
    /* Gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER1,
    /* Trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER1,
    /* Start conversion after HW trigger request occurs */
    SARADC_GATINGMODE_ALWAYS,
    /* Trigger signal edge */
    /* #Violation: Adc_PBcfg_c_REF_2 */
    (Saradc_TriggerMode)ADC_HW_TRIG_RISING_EDGE,
    /* Not used timer trigger */
    {
        FALSE,
        0U,
        SARADC_TIMERMODE_STOP
    }
};
/* ADC HwUnit8 Group configuration */
static const Adc_GroupCfgType Adc_HwUnit8GrpCfg[ADC_CFG_GROUPS_HWUNIT_ADC8] =
{
    /* Group 'GroupHwPolling' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0xff,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit8GroupHwPolling[0U],
        /* ADC8 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* Pointer to the HW trigger configuration parameters */
        &Adc_HwUnit8Group256HwTrigConfig,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_HW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_CIRCULAR
    },
    /* Group 'GroupHwStreaming' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        5U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0xad,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit8GroupHwStreaming[0U],
        /* ADC8 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* Pointer to the HW trigger configuration parameters */
        &Adc_HwUnit8Group257HwTrigConfig,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_HW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE1,
        /* Group access mode */
        ADC_ACCESS_MODE_STREAMING,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    },
    /* Group 'GroupSwPolling' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0xfb,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit8GroupSwPolling[0U],
        /* ADC8 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_CIRCULAR
    },
    /* Group 'GroupSwStreaming' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        5U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0x52,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit8GroupSwStreaming[0U],
        /* ADC8 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_STREAMING,
        /* Group conversion mode */
        ADC_CONV_MODE_CONTINUOUS,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    }
};

/* ADC 0 Channel configuration */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_ChannelCfgType Adc_HwUnit0ChCfg[8] =
{
    /* Channel "AN0": channel ID - 0 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel0 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT0,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel0 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT0,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN1": channel ID - 1 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel1 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT1,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel1 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT1,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN2": channel ID - 2 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel2 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT2,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel2 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT2,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN3": channel ID - 3 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel3 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT3,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel3 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT3,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN4": channel ID - 4 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel4 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT4,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel4 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT4,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN5": channel ID - 5 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel5 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT5,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel5 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT5,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN6": channel ID - 6 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel6 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT6,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel6 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT6,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN7": channel ID - 7 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel7 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT7,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is enabled */
            TRUE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel7 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT7,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is enabled */
            TRUE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    }
};

/* ADC 1 Channel configuration */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_ChannelCfgType Adc_HwUnit1ChCfg[8] =
{
    /* Channel "AN8": channel ID - 0 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel0 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT0,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is used */
            TRUE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel0 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT0,
            /* Dma is used */
            TRUE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN9": channel ID - 1 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel1 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT1,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is used */
            TRUE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel1 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT1,
            /* Dma is used */
            TRUE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN10": channel ID - 2 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel2 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT2,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is used */
            TRUE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel2 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT2,
            /* Dma is used */
            TRUE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN11": channel ID - 3 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel3 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT3,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is used */
            TRUE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel3 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT3,
            /* Dma is used */
            TRUE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN12": channel ID - 4 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel4 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT4,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is used */
            TRUE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel4 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT4,
            /* Dma is used */
            TRUE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN13": channel ID - 5 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel5 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT5,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is used */
            TRUE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel5 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT5,
            /* Dma is used */
            TRUE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN14": channel ID - 6 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel6 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT6,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is used */
            TRUE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel6 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT6,
            /* Dma is used */
            TRUE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN15": channel ID - 7 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel7 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT7,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is used */
            TRUE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel7 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT7,
            /* Dma is used */
            TRUE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    }
};

/* ADC 8 Channel configuration */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_ChannelCfgType Adc_HwUnit8ChCfg[8] =
{
    /* Channel "AN32": channel ID - 0 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel0 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT0,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel0 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT0,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN33": channel ID - 1 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel1 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT1,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel1 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT1,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN35": channel ID - 2 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel3 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT3,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel3 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT3,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN36": channel ID - 3 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel4 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT4,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel4 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT4,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN37": channel ID - 4 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel5 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT5,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel5 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT5,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN38": channel ID - 5 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel6 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT6,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel6 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT6,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN39": channel ID - 6 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel7 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT7,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel7 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT7,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN34": channel ID - 7 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel2 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT2,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel2 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT2,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    }
};
/* ADC 0 hardware unit configuration */
static const Saradc_ModuleConfig Adc_HwUnit0HwCfg =
{
    /* Clock prescale */
    6U,
    /* Sample time */
    10U,
    /* Conversion Resolution */
    SARADC_RESOLUTION_12BIT,
    /* Synchronous conversion source - master or standalone */
    SARADC_CONVERTER_MASTER,
    /* Request queue configuration */
    {
        /* Request queue 0 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE
        },
        /* Request queue 1 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE
        },
        /* Request queue 2 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE,
        }
    }
};

/* ADC 1 hardware unit configuration */
static const Saradc_ModuleConfig Adc_HwUnit1HwCfg =
{
    /* Clock prescale */
    6U,
    /* Sample time */
    2U,
    /* Conversion Resolution */
    SARADC_RESOLUTION_12BIT,
    /* Synchronous conversion source - slave */
    SARADC_CONVERTER_SLAVE1,
    /* Request queue configuration */
    {
        /* Request queue 0 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE
        },
        /* Request queue 1 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE
        },
        /* Request queue 2 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE,
        }
    }
};

/* ADC 8 hardware unit configuration */
static const Saradc_ModuleConfig Adc_HwUnit8HwCfg =
{
    /* Clock prescale */
    6U,
    /* Sample time */
    10U,
    /* Conversion Resolution */
    SARADC_RESOLUTION_12BIT,
    /* Synchronous conversion source - master or standalone */
    SARADC_CONVERTER_MASTER,
    /* Request queue configuration */
    {
        /* Request queue 0 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE
        },
        /* Request queue 1 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE
        },
        /* Request queue 2 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE,
        }
    }
};

/* Slave HW unit ID configuration when sync group is used */
/* #Violation: Adc_PBcfg_c_REF_4 */
/* #Violation: Adc_PBcfg_c_REF_5 */
static const Adc_HwUnitType Adc_SyncGroupSlaveHwUnitMasterAdc0Core0[2] =
{
    /* Total number of all slaves */
    1,

    /* Slave HW unit IDs */
    1U
};

/* ADC HwUnit configuration parameters of Core0 */
static const Adc_KernelConfigType Adc_HwUnitConfigSetCore0[ADC_MAX_HWUNIT_TO_CORE0] =
{
    /* ADC 0 configuration */
    {
        /* ADC HwUnit0 */
        ADC_HWUNIT_ADC0,
        /* Result handling method of the HW unit */
        ADC_RESULT_HANDLING_INTERRUPT_MODE,
        /* Pointer to Adc Hw Unit configuration */
        &Adc_HwUnit0HwCfg,
        /* Pointer to the slave Hw units of sync group */
        &Adc_SyncGroupSlaveHwUnitMasterAdc0Core0[0],
        /* 8 channels */
        8U,
        /* Pointer to the array of channel configuration */
        &Adc_HwUnit0ChCfg[0U],
        /* Pointer to the array of group configuration */
        &Adc_HwUnit0GrpCfg[0U],
        /* Total number of configured groups */
        ADC_CFG_GROUPS_HWUNIT_ADC0,
        /* Index of group start position in ADC HwUnit0 in Core0 */
        0U,
        /* Interrupt enable status*/
        /* Interrupt is always enabled when interrupt */
        TRUE
    },
    /* ADC 1 configuration */
    {
        /* ADC HwUnit1 */
        ADC_HWUNIT_ADC1,
        /* Result handling method of the HW unit */
        ADC_RESULT_HANDLING_DMA_MODE,
        /* Pointer to Adc Hw Unit configuration */
        &Adc_HwUnit1HwCfg,
        /* Sync group slave or standalone */
        NULL_PTR,
        /* 8 channels */
        8U,
        /* Pointer to the array of channel configuration */
        &Adc_HwUnit1ChCfg[0U],
        /* Pointer to the array of group configuration */
        &Adc_HwUnit1GrpCfg[0U],
        /* Total number of configured groups */
        ADC_CFG_GROUPS_HWUNIT_ADC1,
        /* Index of group start position in ADC HwUnit1 in Core0 */
        4U,
        /* Interrupt enable status*/
        /* Interrupt is disabled when in DMA mode */
        FALSE
    },
    /* ADC 8 configuration */
    {
        /* ADC HwUnit8 */
        ADC_HWUNIT_ADC8,
        /* Result handling method of the HW unit */
        ADC_RESULT_HANDLING_POLLING_MODE,
        /* Pointer to Adc Hw Unit configuration */
        &Adc_HwUnit8HwCfg,
        /* Sync group slave or standalone */
        NULL_PTR,
        /* 8 channels */
        8U,
        /* Pointer to the array of channel configuration */
        &Adc_HwUnit8ChCfg[0U],
        /* Pointer to the array of group configuration */
        &Adc_HwUnit8GrpCfg[0U],
        /* Total number of configured groups */
        ADC_CFG_GROUPS_HWUNIT_ADC8,
        /* Index of group start position in ADC HwUnit8 in Core0 */
        7U,
        /* Interrupt enable status*/
        /* Interrupt is always disabled when polling mode */
        FALSE
    }
};

/* Total ADC Hwunit number and configuration information in Core0 */
static const Adc_CoreConfigType Adc_ConfigSetCore0 =
{
    /* Maximum number of the ADC HwUnit allocated to the core0 */
    ADC_MAX_HWUNIT_TO_CORE0,
    /* ADC HwUnit configuration information of core0 */
    &Adc_HwUnitConfigSetCore0[0]
};
/* #Violation: Adc_PBcfg_c_REF_3 */
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Adc_PBcfg_c_REF_1 */
#include "Adc_MemMap.h"


/* Configuration informations which mapped to Core1 */
/* #Violation: Adc_PBcfg_c_REF_3 */
#define ADC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Adc_PBcfg_c_REF_1 */
#include "Adc_MemMap.h"

/* ADC2 Group "SWTrigDemo" configuration */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit2GroupContinuous[8] =
{
    /* Total number of channels assigned to the group 'GroupContinuous' of HwUnit2 */
    7U,

    /* The channels assigned to the group 'GroupContinuous' of HwUnit2 */
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit2GroupLimitCheck[2] =
{
    /* Total number of channels assigned to the group 'GroupLimitCheck' of HwUnit2 */
    1U,

    /* The channels assigned to the group 'GroupLimitCheck' of HwUnit2 */
    0U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit2GroupOneShot[8] =
{
    /* Total number of channels assigned to the group 'GroupOneShot' of HwUnit2 */
    7U,

    /* The channels assigned to the group 'GroupOneShot' of HwUnit2 */
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit2GroupStreaming[5] =
{
    /* Total number of channels assigned to the group 'GroupStreaming' of HwUnit2 */
    4U,

    /* The channels assigned to the group 'GroupStreaming' of HwUnit2 */
    4U,
    5U,
    6U,
    1U
};
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_GroupDefType Adc_ChsInHwUnit2GroupSwResultAccumulation[8] =
{
    /* Total number of channels assigned to the group 'GroupSwResultAccumulation' of HwUnit2 */
    7U,

    /* The channels assigned to the group 'GroupSwResultAccumulation' of HwUnit2 */
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U
};
/* ADC Groups are arranged in the order of their trigger type ( HW/SW ) and
request sources (RS0 .. RS2) starting from SW trigger RS0 to SW trigger
RS2 and then HW trigger RS0 to HW trigger RS2. */
/* ADC HwUnit2 Group configuration */
static const Adc_GroupCfgType Adc_HwUnit2GrpCfg[ADC_CFG_GROUPS_HWUNIT_ADC2] =
{
    /* Group 'GroupContinuous' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0xfe,
        /* Notification function pointer */
        AdcDemo_Adc2ContinuousNotif,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit2GroupContinuous[0U],
        /* ADC2 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_CONTINUOUS,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_CIRCULAR
    },
    /* Group 'GroupLimitCheck' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0x1,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit2GroupLimitCheck[0U],
        /* ADC2 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    },
    /* Group 'GroupOneShot' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0xfe,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit2GroupOneShot[0U],
        /* ADC2 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE1,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_CIRCULAR
    },
    /* Group 'GroupStreaming' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        5U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0x72,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit2GroupStreaming[0U],
        /* ADC2 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Disable result accumulation mode */
        0U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE2,
        /* Group access mode */
        ADC_ACCESS_MODE_STREAMING,
        /* Group conversion mode */
        ADC_CONV_MODE_CONTINUOUS,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    },
    /* Group 'GroupSwResultAccumulation' */
    {
        /* No sync channel enable under this group */
        FALSE,
        /* Number of ADC values to be acquired in streaming access mode */
        1U,
        /* Internal channel mask from group definition - derived from the tool */
        (uint16)0xfe,
        /* Notification function pointer */
        NULL_PTR,
        /* Assignment of channels to a channel group */
        /* First element is the number of configured channels in the group */
        /* From Second element will give the channel ID */
        &Adc_ChsInHwUnit2GroupSwResultAccumulation[0U],
        /* ADC2 not in DMA result handling mode, 
        and manual allocation of the result register is not supported. */
        NULL_PTR,
        /* SW trigger */
        NULL_PTR,
        /* Enable result accumulation mode */
        15U,
        /* Group trigger source: SW or HW */
        ADC_TRIGG_SRC_SW,
        /* Group request queue: RS0 - RS2 */
        SARADC_REQUESTSOURCE_QUEUE0,
        /* Group access mode */
        ADC_ACCESS_MODE_SINGLE,
        /* Group conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /* Buffer mode type - Configure streaming buffer as "linear buffer" or "ring buffer" */
        ADC_STREAM_BUFFER_LINEAR
    }
};
/* Limit checking configuration parameters for AN16: channel 0 */
static const Adc_ChannelLimitCheckType Adc_HwUnit2Channel0LimitCheckingConfig =
{
    /* Limit checking configuration */
    {
        /* Low boundary */
        1501U,
        /* high boundary */
        3000U
    },
    /* Channel interrupt type for limit checking */
    SARADC_CHANNELINTERRUPT_INBOUNDARY
};

/* ADC 2 Channel configuration */
/* #Violation: Adc_PBcfg_c_REF_5 */
/* #Violation: Adc_PBcfg_c_REF_4 */
static const Adc_ChannelCfgType Adc_HwUnit2ChCfg[8] =
{
    /* Channel "AN16": channel ID - 0 */
    {
        /* Pointer to the limit checking configuration parameters */
        &Adc_HwUnit2Channel0LimitCheckingConfig,
        /* Channel0 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT0,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is used for this channel */
            /* Limit checking range: Less than the upper limit, Greater than the lower limit */
            FALSE,
            /* Discard result out of range */
            FALSE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel0 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT0,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is used for this channel */
            /* Limit checking range: Less than the upper limit, Greater than the lower limit */
            FALSE,
            /* Discard result out of range */
            FALSE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN17": channel ID - 1 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel1 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT1,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel1 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT1,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN18": channel ID - 2 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel2 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT2,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel2 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT2,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN19": channel ID - 3 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel3 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT3,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel3 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT3,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN20": channel ID - 4 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel4 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT4,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel4 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT4,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN21": channel ID - 5 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel5 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT5,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel5 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT5,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN22": channel ID - 6 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel6 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT6,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel6 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT6,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    },
    /* Channel "AN23": channel ID - 7 */
    {
        /* Limit checking is not enabled for this channel */
        NULL_PTR,
        /* Channel7 configuration */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT7,
            /* Over-write always */
            SARADC_OVERWRITEMODE,
            /* Dma is unused */
            FALSE,
            /* Conversion result align method */
            (boolean)ADC_RESULT_ALIGNMENT,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        },
        /* Channel7 configuration for runtime */
        {
            /* Channel ID */
            SARADC_CHANNELRESULT7,
            /* Dma is unused */
            FALSE,
            /* Synchronize conversion is unused */
            FALSE,
            /* Limit checking is not used for this channel */
            /* Less than the upper boundary, greater than the lower boundary is
            the threshold range */
            FALSE,
            /* Retain result out of range */
            TRUE,
            /* HDI not used */
            SARADC_HDI_OFF
        }
    }
};
/* ADC 2 hardware unit configuration */
static const Saradc_ModuleConfig Adc_HwUnit2HwCfg =
{
    /* Clock prescale */
    6U,
    /* Sample time */
    10U,
    /* Conversion Resolution */
    SARADC_RESOLUTION_12BIT,
    /* Synchronous conversion source - master or standalone */
    SARADC_CONVERTER_MASTER,
    /* Request queue configuration */
    {
        /* Request queue 0 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE
        },
        /* Request queue 1 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE
        },
        /* Request queue 2 */
        {
            /* Priority */
            SARADC_QUEUEPRIORITY_LOWEST,
            /* Start mode */
            SARADC_STARTMODE_CANCELINJECTREPEAT,
            /* Arbitration queue is enable */
            TRUE,
        }
    }
};


/* ADC HwUnit configuration parameters of Core1 */
static const Adc_KernelConfigType Adc_HwUnitConfigSetCore1[ADC_MAX_HWUNIT_TO_CORE1] =
{
    /* ADC 2 configuration */
    {
        /* ADC HwUnit2 */
        ADC_HWUNIT_ADC2,
        /* Result handling method of the HW unit */
        ADC_RESULT_HANDLING_INTERRUPT_MODE,
        /* Pointer to Adc Hw Unit configuration */
        &Adc_HwUnit2HwCfg,
        /* Sync group slave or standalone */
        NULL_PTR,
        /* 8 channels */
        8U,
        /* Pointer to the array of channel configuration */
        &Adc_HwUnit2ChCfg[0U],
        /* Pointer to the array of group configuration */
        &Adc_HwUnit2GrpCfg[0U],
        /* Total number of configured groups */
        ADC_CFG_GROUPS_HWUNIT_ADC2,
        /* Index of group start position in ADC HwUnit2 in Core1 */
        0U,
        /* Interrupt enable status*/
        /* Interrupt is always enabled when interrupt */
        TRUE
    }
};

/* Total ADC Hwunit number and configuration information in Core1 */
static const Adc_CoreConfigType Adc_ConfigSetCore1 =
{
    /* Maximum number of the ADC HwUnit allocated to the core1 */
    ADC_MAX_HWUNIT_TO_CORE1,
    /* ADC HwUnit configuration information of core1 */
    &Adc_HwUnitConfigSetCore1[0]
};
/* #Violation: Adc_PBcfg_c_REF_3 */
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Adc_PBcfg_c_REF_1 */
#include "Adc_MemMap.h"

/* #Violation: Adc_PBcfg_c_REF_3 */
#define ADC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Adc_PBcfg_c_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/*
This array is used for mapping Adc hardware unit to the Core.
Array index is Adc hardware unit ->
First member in the array is index of Adc_HwUnitConfigSetCorex[x=0~4];
Second member in the array is Core ID that the HW unit is mapped to.
*/
static const Adc_HWUnitCoreMapType Adc_HwUnitToCoreMap[ADC_MAX_KERNELS] =
{
    /* ADC0 config info is assigned to Adc_HwUnitConfigSetCore0[0], and mapped to CORE0 */
    {0U, 0U},
    /* ADC1 config info is assigned to Adc_HwUnitConfigSetCore0[1], and mapped to CORE0 */
    {1U, 0U},
    /* ADC2 config info is assigned to Adc_HwUnitConfigSetCore1[0], and mapped to CORE1 */
    {0U, 1U},
    /* ADC3 is not used */
    {255U, 255U},
    /* ADC4 is not used */
    {255U, 255U},
    /* ADC5 is not used */
    {255U, 255U},
    /* ADC6 is not used */
    {255U, 255U},
    /* ADC7 is not used */
    {255U, 255U},
    /* ADC8 config info is assigned to Adc_HwUnitConfigSetCore0[2], and mapped to CORE0 */
    {2U, 0U},
    /* ADC9 is not used */
    {255U, 255U}
};
/*
ADC configuration data set
*/
const Adc_ConfigType Adc_ConfigSet[ADC_CONFIG_COUNT] =
{
    {
        {
            /* ADC configuration information of core0 */
            &Adc_ConfigSetCore0,
            /* ADC configuration information of core1 */
            &Adc_ConfigSetCore1

        },
        /* Pointer to Adc HwUnit mapped to core configuration */
        &Adc_HwUnitToCoreMap[0]
    }
};
/* #Violation: Adc_PBcfg_c_REF_3 */
#define ADC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Adc_PBcfg_c_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
