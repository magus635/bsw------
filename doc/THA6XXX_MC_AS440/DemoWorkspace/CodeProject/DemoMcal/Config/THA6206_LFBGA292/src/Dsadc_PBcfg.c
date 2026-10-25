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
*
*#Dsadc_PBcfg_c_REF_1:MISRAC2012-Rule-10.5;
* Justification: Redundant cast is necessary to maintain the software structure and reduce the 
*   complexity.
*
*#Dsadc_PBcfg_c_REF_2:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain
*   parts of the driver must be placed.
*
*#Dsadc_PBcfg_c_REF_3:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
*   substitution.
*
*#Dsadc_PBcfg_c_REF_4:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
*   substitution.
*
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#include "Dsadc.h"
#include "Mcall.h"


/****************************************************************************************************
**                          External Function Declarations                                         **
****************************************************************************************************/
/* Buffer full notification declaration - StreamingCircular: Channel2 */
extern void DsadcDemo_CircularBufferFull(void);

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

#define DSADC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dsadc_PBcfg_c_REF_2 */
#include "Dsadc_MemMap.h"

/* Modulator configuration parameters of channel0 */
static const Dsadc_ModulatorConfig Dsadc_ModulatorConfigChannel0 = 
{
    /* PINEN: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* NINEN: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* PINSET: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* NINSET: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* Initialize input pin of multiplexer */
    TRUE,
    /* Not Change or change to another input pin by a trigger event */
    FALSE,
    /* Auto power control disabled */
    FALSE,
    /* Input pin gain */
    DSADC_INPUT_GAIN_0dB,
    /* Control condition for a trigger event to control the input multiplexer */
    (Dsadc_InputMultiplexerTriggerMode)DSADC_INPUTMUX_CTRL_SW
};

/* Demodulator configuration parameters of channel0 */
static const Dsadc_DemodulatorConfig Dsadc_DemodulatorConfigChannel0 = 
{
    /* Result display mode: unsigned or signed */
    FALSE,
    /* Trigger source: 0_GTM_DSADC_TRIGGER0 */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_TriggerSource)0U
};

/* Timestamp configuration parameters of channel0 */
static const Dsadc_TimeStampConfig Dsadc_TimestampConfigChannel0 = 
{
    /* Enable the timestamp counter */
    TRUE,
    /* Not copy multiplexer */
    FALSE,
    /* Timestamp clock frequency */
    15U,
    /* Timestamp counter clock */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    DSADC_TIMESTAMPCLOCKDIVIDER_8,
    /* Timestamp trigger mode is equal to trigger mode of external trigger source */
    (Dsadc_TimeStampTriggerMode)DSADC_TIMESTAMP_TRIG_RISING_EDGE
};
/* Limit checking configuration parameters of channel0 */
static const Dsadc_ThresholdConfig Dsadc_LimitCheckingConfigChannel0 = 
{
    /* Low boundary value of limit checking */
    (uint16)0, 
    /* high boundary value of limit checking */
    (uint16)0
};


/* Main filter configuration parameters of channel0 */
static const Dsadc_MainFilterConfig Dsadc_MainFilterConfigChannel0 = 
{
    /* CIC filter is enabled */
    TRUE,
    /* FIR0 decimation rate is 2 */
    FALSE,
    /* FIR1 decimation rate is 2 */
    FALSE,
    /* FIR0 filter is enabled */
    TRUE,
    /* FIR1 filter is enabled */
    TRUE,
    /* FIR0 offset */
    (boolean)0,
    /* CIC filter sampling factor */
    127U,
    /* CIC filter type */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_CicParallelSelection)3U,
    /* Service request */
    (Dsadc_ServiceRequest)DSADC_GATE_HIGH_LEVEL,
    /* Alarm generate config */
    DSADC_ALARMCONDITION_NEWRESULT,
    /* FIR1 offset */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_FirOffset)0,
    /* Offset compensation filter config. */
    (Dsadc_FilterOffsetCompensation)DSADC_OFFSET_COMP_FILTER_DISABLE
};

/* Auxiliary filter configuration parameters of channel0 */
static const Dsadc_AuxiliaryFilterConfig Dsadc_AuxFilterConfigChannel0 = 
{
    /* Enable the auxiliary filter service request */
    TRUE,
    /* Enable the auxiliary CIC filter */
    TRUE,
    /* Auxiliary channel CIC filter sampling factor */
    31U,
    /* Auxiliary filter type */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_CicParallelSelection)3U
};

/* HW unit configuration parameters of channel0 */
static const Dsadc_ModuleConfig Dsadc_HWUnitConfigChannel0 = 
{
    /* Point to the modulator parameters configuration */
    &Dsadc_ModulatorConfigChannel0,
    /* Point to the demodulator parameters configuration */
    &Dsadc_DemodulatorConfigChannel0,
    /* Point to the timestamp parameters configuration */
    &Dsadc_TimestampConfigChannel0,
    /* Point to the limit checking parameters configuration */
    &Dsadc_LimitCheckingConfigChannel0,
    /* Point to the main filter parameter configuration */
    &Dsadc_MainFilterConfigChannel0,
    /* Point to the auxiliary filter parameter configuration */
    &Dsadc_AuxFilterConfigChannel0,
    /* Integrator is disabled */
    NULL_PTR,
    /* FIFO not used, external trigger */
    NULL_PTR
};
/* Modulator configuration parameters of channel1 */
static const Dsadc_ModulatorConfig Dsadc_ModulatorConfigChannel1 = 
{
    /* PINEN: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* NINEN: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* PINSET: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* NINSET: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* Initialize input pin of multiplexer */
    TRUE,
    /* Not Change or change to another input pin by a trigger event */
    FALSE,
    /* Auto power control disabled */
    FALSE,
    /* Input pin gain */
    DSADC_INPUT_GAIN_0dB,
    /* Control condition for a trigger event to control the input multiplexer */
    (Dsadc_InputMultiplexerTriggerMode)DSADC_INPUTMUX_CTRL_SW
};

/* Demodulator configuration parameters of channel1 */
static const Dsadc_DemodulatorConfig Dsadc_DemodulatorConfigChannel1 = 
{
    /* Result display mode: unsigned or signed */
    FALSE,
    /* External trigger is not used, default is 0 */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_TriggerSource)0U
};

/* Default Limit checking configuration parameters of channel1,
Used for AVOID SAC ALARM */
static const Dsadc_ThresholdConfig Dsadc_LimitCheckingConfigChannel1 = 
{
    /* Low boundary value of limit checking: -32768, unsigned value is 32768 */
    (uint16)32768, 
    /* high boundary value of limit checking: 32767 */
    (uint16)32767
};

/* Main filter configuration parameters of channel1 */
static const Dsadc_MainFilterConfig Dsadc_MainFilterConfigChannel1 = 
{
    /* CIC filter is enabled */
    TRUE,
    /* FIR0 decimation rate is 2 */
    FALSE,
    /* FIR1 decimation rate is 2 */
    FALSE,
    /* FIR0 filter is enabled */
    TRUE,
    /* FIR1 filter is enabled */
    TRUE,
    /* FIR0 offset */
    (boolean)0,
    /* CIC filter sampling factor */
    63U,
    /* CIC filter type */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_CicParallelSelection)3U,
    /* Service request */
    (Dsadc_ServiceRequest)DSADC_DATA_FIFO_THRESHOLD,
    /* Alarm generate config */
    DSADC_ALARMCONDITION_NEWRESULT,
    /* FIR1 offset */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_FirOffset)0,
    /* Offset compensation filter config. */
    (Dsadc_FilterOffsetCompensation)DSADC_OFFSET_COMP_FILTER_DISABLE
};

/* Auxiliary filter configuration parameters of channel1 */
static const Dsadc_AuxiliaryFilterConfig Dsadc_AuxFilterConfigChannel1 = 
{
    /* Disable the auxiliary filter service request */
    FALSE,
    /* Disable the auxiliary CIC filter */
    FALSE,
    /* Auxiliary channel CIC filter sampling factor */
    3U,
    /* Auxiliary filter type */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_CicParallelSelection)0U
};

/* FIFO configuration parameters of channel1 */
static const Dsadc_FifoConfig Dsadc_FifoConfigChannel1 = 
{
    /* FIFO threshold */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_FifoThreshold)0U
};

/* HW unit configuration parameters of channel1 */
static const Dsadc_ModuleConfig Dsadc_HWUnitConfigChannel1 = 
{
    /* Point to the modulator parameters configuration */
    &Dsadc_ModulatorConfigChannel1,
    /* Point to the demodulator parameters configuration */
    &Dsadc_DemodulatorConfigChannel1,
    /* Timestamp is not enabled for this channel */
    NULL_PTR,
    /* Point to the limit checking parameters configuration */
    &Dsadc_LimitCheckingConfigChannel1,
    /* Point to the main filter parameter configuration */
    &Dsadc_MainFilterConfigChannel1,
    /* Point to the auxiliary filter parameter configuration */
    &Dsadc_AuxFilterConfigChannel1,
    /* Integrator is disabled */
    NULL_PTR,
    /* Point to the FIFO parameters configuration */
    &Dsadc_FifoConfigChannel1
};
/* Modulator configuration parameters of channel2 */
static const Dsadc_ModulatorConfig Dsadc_ModulatorConfigChannel2 = 
{
    /* PINEN: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* NINEN: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* PINSET: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* NINSET: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* Initialize input pin of multiplexer */
    TRUE,
    /* Not Change or change to another input pin by a trigger event */
    FALSE,
    /* Auto power control disabled */
    FALSE,
    /* Input pin gain */
    DSADC_INPUT_GAIN_0dB,
    /* Control condition for a trigger event to control the input multiplexer */
    (Dsadc_InputMultiplexerTriggerMode)DSADC_INPUTMUX_CTRL_SW
};

/* Demodulator configuration parameters of channel2 */
static const Dsadc_DemodulatorConfig Dsadc_DemodulatorConfigChannel2 = 
{
    /* Result display mode: unsigned or signed */
    FALSE,
    /* External trigger is not used, default is 0 */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_TriggerSource)0U
};

/* Default Limit checking configuration parameters of channel2,
Used for AVOID SAC ALARM */
static const Dsadc_ThresholdConfig Dsadc_LimitCheckingConfigChannel2 = 
{
    /* Low boundary value of limit checking: -32768, unsigned value is 32768 */
    (uint16)32768, 
    /* high boundary value of limit checking: 32767 */
    (uint16)32767
};

/* Main filter configuration parameters of channel2 */
static const Dsadc_MainFilterConfig Dsadc_MainFilterConfigChannel2 = 
{
    /* CIC filter is enabled */
    TRUE,
    /* FIR0 decimation rate is 2 */
    FALSE,
    /* FIR1 decimation rate is 2 */
    FALSE,
    /* FIR0 filter is enabled */
    TRUE,
    /* FIR1 filter is enabled */
    TRUE,
    /* FIR0 offset */
    (boolean)0,
    /* CIC filter sampling factor */
    63U,
    /* CIC filter type */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_CicParallelSelection)3U,
    /* Service request */
    (Dsadc_ServiceRequest)DSADC_DATA_FIFO_THRESHOLD,
    /* Alarm generate config */
    DSADC_ALARMCONDITION_NEWRESULT,
    /* FIR1 offset */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_FirOffset)0,
    /* Offset compensation filter config. */
    (Dsadc_FilterOffsetCompensation)DSADC_OFFSET_COMP_FILTER_DISABLE
};

/* FIFO configuration parameters of channel2 */
static const Dsadc_FifoConfig Dsadc_FifoConfigChannel2 = 
{
    /* FIFO threshold */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_FifoThreshold)0U
};

/* HW unit configuration parameters of channel2 */
static const Dsadc_ModuleConfig Dsadc_HWUnitConfigChannel2 = 
{
    /* Point to the modulator parameters configuration */
    &Dsadc_ModulatorConfigChannel2,
    /* Point to the demodulator parameters configuration */
    &Dsadc_DemodulatorConfigChannel2,
    /* Timestamp is not enabled for this channel */
    NULL_PTR,
    /* Point to the limit checking parameters configuration */
    &Dsadc_LimitCheckingConfigChannel2,
    /* Point to the main filter parameter configuration */
    &Dsadc_MainFilterConfigChannel2,
    /* No auxiliary filter chain configuration */
    NULL_PTR,
    /* Integrator is disabled */
    NULL_PTR,
    /* Point to the FIFO parameters configuration */
    &Dsadc_FifoConfigChannel2
};
/* Modulator configuration parameters of channel3 */
static const Dsadc_ModulatorConfig Dsadc_ModulatorConfigChannel3 = 
{
    /* PINEN: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* NINEN: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* PINSET: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* NINSET: enabled(TRUE) or disabled(FALSE) */
    TRUE,
    /* Initialize input pin of multiplexer */
    TRUE,
    /* Not Change or change to another input pin by a trigger event */
    FALSE,
    /* Auto power control disabled */
    FALSE,
    /* Input pin gain */
    DSADC_INPUT_GAIN_0dB,
    /* Control condition for a trigger event to control the input multiplexer */
    (Dsadc_InputMultiplexerTriggerMode)DSADC_INPUTMUX_CTRL_SW
};

/* Demodulator configuration parameters of channel3 */
static const Dsadc_DemodulatorConfig Dsadc_DemodulatorConfigChannel3 = 
{
    /* Result display mode: unsigned or signed */
    FALSE,
    /* External trigger is not used, default is 0 */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_TriggerSource)0U
};

/* Default Limit checking configuration parameters of channel3,
Used for AVOID SAC ALARM */
static const Dsadc_ThresholdConfig Dsadc_LimitCheckingConfigChannel3 = 
{
    /* Low boundary value of limit checking: -32768, unsigned value is 32768 */
    (uint16)32768, 
    /* high boundary value of limit checking: 32767 */
    (uint16)32767
};

/* Main filter configuration parameters of channel3 */
static const Dsadc_MainFilterConfig Dsadc_MainFilterConfigChannel3 = 
{
    /* CIC filter is enabled */
    TRUE,
    /* FIR0 decimation rate is 2 */
    FALSE,
    /* FIR1 decimation rate is 2 */
    FALSE,
    /* FIR0 filter is enabled */
    TRUE,
    /* FIR1 filter is enabled */
    TRUE,
    /* FIR0 offset */
    (boolean)0,
    /* CIC filter sampling factor */
    63U,
    /* CIC filter type */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_CicParallelSelection)3U,
    /* Service request */
    (Dsadc_ServiceRequest)DSADC_DATA_FIFO_THRESHOLD,
    /* Alarm generate config */
    DSADC_ALARMCONDITION_NEWRESULT,
    /* FIR1 offset */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_FirOffset)0,
    /* Offset compensation filter config. */
    (Dsadc_FilterOffsetCompensation)DSADC_OFFSET_COMP_FILTER_DISABLE
};

/* FIFO configuration parameters of channel3 */
static const Dsadc_FifoConfig Dsadc_FifoConfigChannel3 = 
{
    /* FIFO threshold */
    /* #Violation: Dsadc_PBcfg_c_REF_1 */
    (Dsadc_FifoThreshold)0U
};

/* HW unit configuration parameters of channel3 */
static const Dsadc_ModuleConfig Dsadc_HWUnitConfigChannel3 = 
{
    /* Point to the modulator parameters configuration */
    &Dsadc_ModulatorConfigChannel3,
    /* Point to the demodulator parameters configuration */
    &Dsadc_DemodulatorConfigChannel3,
    /* Timestamp is not enabled for this channel */
    NULL_PTR,
    /* Point to the limit checking parameters configuration */
    &Dsadc_LimitCheckingConfigChannel3,
    /* Point to the main filter parameter configuration */
    &Dsadc_MainFilterConfigChannel3,
    /* No auxiliary filter chain configuration */
    NULL_PTR,
    /* Integrator is disabled */
    NULL_PTR,
    /* Point to the FIFO parameters configuration */
    &Dsadc_FifoConfigChannel3
};

/* Channel configuration parameters in 0 */
/* #Violation: Dsadc_PBcfg_c_REF_3 */
/* #Violation: Dsadc_PBcfg_c_REF_4 */
static const Dsadc_ChannelConfigType Dsadc_ChannelConfigCore0[4] = 
{
    {
        /* HW Unit ID */
        0U,
        /* Logical channel ID */
        0U,
        /* Disable the modulator dithering */
        FALSE,
        /* Common mode voltage is used */
        TRUE,
        /* Common mode voltage connect to DSADC_BIASVOLTAGE_3 */
        DSADC_BIASVOLTAGE_3,
        /* Enable auxiliary conversion channel result acquisition functionality */
        TRUE,
        /* Timestamp enabled */
        TRUE,
        /* Result handling mode */
        DSADC_RESULT_HANDLING_INTERRUPT_MODE,
        /* Number of values to be acquired in streaming access mode */
        1U,
        /* Conversion result access mode */
        DSADC_ACCESS_MODE_SINGLE,
        /* Buffer mode type */
        DSADC_STREAM_BUFFER_LEANER,
        /* No new result conversion generated notification function */
        NULL_PTR,
        /* No buffer full notification function */
        NULL_PTR,
        /* No limit checking notification function */
        NULL_PTR,
        /* Limit checking interrupt events */
        DSADC_LIMITCHECKING_BELOW_LOWER,
        /* No compensation configuration parameter */
        NULL_PTR,
        /* Point to the HW unit configuration of this channel(0) */
        &Dsadc_HWUnitConfigChannel0
    },
    {
        /* HW Unit ID */
        1U,
        /* Logical channel ID */
        1U,
        /* Disable the modulator dithering */
        FALSE,
        /* Common mode voltage is used */
        TRUE,
        /* Common mode voltage connect to DSADC_BIASVOLTAGE_0 */
        DSADC_BIASVOLTAGE_0,
        /* Disable auxiliary conversion channel result acquisition functionality */
        FALSE,
        /* Timestamp disabled */
        FALSE,
        /* Result handling mode */
        DSADC_RESULT_HANDLING_INTERRUPT_MODE,
        /* Number of values to be acquired in streaming access mode */
        5U,
        /* Conversion result access mode */
        DSADC_ACCESS_MODE_STREAMING,
        /* Buffer mode type */
        DSADC_STREAM_BUFFER_LEANER,
        /* No new result conversion generated notification function */
        NULL_PTR,
        /* No buffer full notification function */
        NULL_PTR,
        /* No limit checking notification function */
        NULL_PTR,
        /* Limit checking interrupt events */
        0U,
        /* No compensation configuration parameter */
        NULL_PTR,
        /* Point to the HW unit configuration of this channel(1) */
        &Dsadc_HWUnitConfigChannel1
    },
    {
        /* HW Unit ID */
        2U,
        /* Logical channel ID */
        2U,
        /* Disable the modulator dithering */
        FALSE,
        /* Common mode voltage is used */
        TRUE,
        /* Common mode voltage connect to DSADC_BIASVOLTAGE_0 */
        DSADC_BIASVOLTAGE_0,
        /* Disable auxiliary conversion channel result acquisition functionality */
        FALSE,
        /* Timestamp disabled */
        FALSE,
        /* Result handling mode */
        DSADC_RESULT_HANDLING_INTERRUPT_MODE,
        /* Number of values to be acquired in streaming access mode */
        10U,
        /* Conversion result access mode */
        DSADC_ACCESS_MODE_STREAMING,
        /* Buffer mode type */
        DSADC_STREAM_BUFFER_CIRCULAR,
        /* No new result conversion generated notification function */
        NULL_PTR,
        /* Pointer to the buffer full notification function 'DsadcDemo_CircularBufferFull' and 
        this function shall be implemented by the user */
        DsadcDemo_CircularBufferFull,
        /* No limit checking notification function */
        NULL_PTR,
        /* Limit checking interrupt events */
        0U,
        /* No compensation configuration parameter */
        NULL_PTR,
        /* Point to the HW unit configuration of this channel(2) */
        &Dsadc_HWUnitConfigChannel2
    },
    {
        /* HW Unit ID */
        3U,
        /* Logical channel ID */
        3U,
        /* Disable the modulator dithering */
        FALSE,
        /* Common mode voltage is not used */
        FALSE,
        /* Default set to DSADC_COMM_MODE_VOLT_0 */
        DSADC_BIASVOLTAGE_0,
        /* Disable auxiliary conversion channel result acquisition functionality */
        FALSE,
        /* Timestamp disabled */
        FALSE,
        /* Result handling mode */
        DSADC_RESULT_HANDLING_DMA_MODE,
        /* Number of values to be acquired in streaming access mode */
        1U,
        /* Conversion result access mode */
        DSADC_ACCESS_MODE_SINGLE,
        /* Buffer mode type */
        DSADC_STREAM_BUFFER_CIRCULAR,
        /* No new result conversion generated notification function */
        NULL_PTR,
        /* No buffer full notification function */
        NULL_PTR,
        /* No limit checking notification function */
        NULL_PTR,
        /* Limit checking interrupt events */
        0U,
        /* No compensation configuration parameter */
        NULL_PTR,
        /* Point to the HW unit configuration of this channel(3) */
        &Dsadc_HWUnitConfigChannel3
    }
};

/* Core0 configuration set */
static const Dsadc_CoreConfigType Dsadc_ConfigSetCore0 = 
{
    /* Maximum number of the channels in core0 */
    4U,
    /* Pointer to the channel configuration set */
    &Dsadc_ChannelConfigCore0[0]
};

/* Configuration informations which mapped to Core0 */
#define DSADC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dsadc_PBcfg_c_REF_2 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#define DSADC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dsadc_PBcfg_c_REF_2 */
#include "Dsadc_MemMap.h"


/* Configuration for logical channel ID mapping information.
Sub channel index in core, HW unit ID, Core ID.
*/
/* #Violation: Dsadc_PBcfg_c_REF_3 */
/* #Violation: Dsadc_PBcfg_c_REF_4 */
static const Dsadc_ChannelCoreMapType Dsadc_ChannelMapConfig[4] = 
{
    {0U, 0U, 0U},
    {1U, 1U, 0U},
    {2U, 2U, 0U},
    {3U, 3U, 0U}
};

/* Configuration for HW unit to logical channel */
/* #Violation: Dsadc_PBcfg_c_REF_3 */
/* #Violation: Dsadc_PBcfg_c_REF_4 */
static const Dsadc_ChannelType Dsadc_HWUnit2ChConfig[4] = 
{
    /* Logical channel0 mapped to DSADC0 */
    0U,
    /* Logical channel1 mapped to DSADC1 */
    1U,
    /* Logical channel2 mapped to DSADC2 */
    2U,
    /* Logical channel3 mapped to DSADC3 */
    3U
};

/* Global configuration parameters */
static const Dsadc_GlobalConfigType Dsadc_GlobalConfig = 
{
    /* HW unit enable status */
    0x0000000fU,
    /* Auxiliary filter enable status */
    0x00000300U,
    /* No carrier configuration parameters */
    NULL_PTR,
};

/* Dsadc configuration set parameters */
const Dsadc_ConfigType Dsadc_ConfigSet[DSADC_CONFIGSET_CNT] =
{
    {
        {
            /* Configuration set for core0 */
            &Dsadc_ConfigSetCore0,
            /* Not configuration set for core1 */
            NULL_PTR
        },
        /* Point to the global configuration parameters */
        &Dsadc_GlobalConfig,
        /* Point to the logical channel mapping buffer */
        &Dsadc_ChannelMapConfig[0],
        /* Point to the buffer that HW unit mapped to logical channel */
        &Dsadc_HWUnit2ChConfig[0]
    }
};

#define DSADC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dsadc_PBcfg_c_REF_2 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
