/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Adc_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SARADC
*
*   brief                 : This file contains all type definitions of Adc Driver
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
*#Adc_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification:MCAL code is open-source without using opaque types.
*
*#Adc_GeneralTypes_h_REF_2:MISRAC2012-Rule-2.3;
* Justification:Reserved types are defined in AUTOSAR specifications.
*
*#Adc_GeneralTypes_h_REF_3:CertC-DCL06-C;
* Justification:The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Adc_GeneralTypes_h_REF_4:CertC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and 
* reduce the code complexity;
*
*/


#ifndef ADC_GENERALTYPES_H_
#define ADC_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Adc_Cfg.h"
#include "Mcall.h"
#include "saradc_hal.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* SWS_Adc_00506: Numeric ID of an ADC channel */
typedef uint8 Adc_ChannelType;

/* SWS_Adc_00507: Numeric ID of an ADC channel group */
/* For each Adc Kernel, maximum of 32 channel groups are supported */
typedef uint16 Adc_GroupType;

/* SWS_Adc_00508: Type for reading the converted values of a channel group (raw, without further
 * scaling, alignment according precompile switch ADC_RESULT_ALIGNMENT).
 */
typedef uint16 Adc_ValueGroupType;

/* SWS_Adc_00509: Type of clock prescaler factor */
/* Divider Factor for Analog Internal Clock (fADCI) */
/* #Violation: Adc_GeneralTypes_h_REF_2 */
typedef uint32 Adc_PrescaleType;

/* SWS_Adc_00510: Type of conversion time, i.e. the time during which the sampled analogue value is
 * converted into digital representation. */
/* #Violation: Adc_GeneralTypes_h_REF_2 */
typedef uint8 Adc_ConversionTimeType;

/* SWS_Adc_00511: Type of sampling time, i.e. the time during which the value is sampled,
 * (in clock cycles). */
/* #Violation: Adc_GeneralTypes_h_REF_2 */
typedef uint8 Adc_SamplingTimeType;

/* SWS_Adc_00516: Priority level of the channel, Lowest priority is 0. */
typedef uint8 Adc_GroupPriorityType;

/* SWS_Adc_00517: Type for assignment of channels to a channel group */
typedef Adc_ChannelType Adc_GroupDefType;

/* SWS_Adc_00518: Type for the number of samples of a streaming conversion buffer,
 * (in single access mode, parameter is 1) */
typedef uint8 Adc_StreamNumSampleType;

/* SWS_Adc_00521:Type for the reload value of the ADC module embedded timer
 * (only if supported by the ADC hardware). */
/* #Violation: Adc_GeneralTypes_h_REF_2 */
typedef uint16 Adc_HwTriggerTimerType;


/* SWS_Adc_00522: Type for configuring the prioritization mechanism. */
/* ADC_PRIORITY_NONE  = 0U : Priority mechanism is not available
 * ADC_PRIORITY_HW    = 1U : Hardware priority mechanism is available only
 * ADC_PRIORITY_HW_SW = 2U : Hardware and software priority mechanism is available
 * */
/* #Violation: Adc_GeneralTypes_h_REF_2 */
typedef uint8 Adc_PriorityImplementationType;


/* Numeric ID of an ADC Hw Unit */
typedef uint8 Adc_HwUnitType;

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/* SWS_Adc_00082 */
/* Type definition for ADC notification function pointer */
typedef void (*Adc_NotifFctPtrType)(void);
#endif /* (ADC_GRP_NOTIF_CAPABILITY  \== STD_ON) */

/****************************************************************************************************
**                          Global Enumeration Definitions                                         **
****************************************************************************************************/
/* SWS_Adc_00512: Type of channel resolution in number of bits. */

typedef enum
{
    ADC_BITS_12 = 0U,     /* 12bit */
    ADC_BITS_10,          /* 10bit */
    ADC_BITS_8            /* 8bit */
/* #Violation: Adc_GeneralTypes_h_REF_2 */
} Adc_ResolutionType;

/* SWS_Adc_00513: Current status of the conversion of the requested ADC Channel group. */
typedef enum
{
    /* The conversion of the specified group has not been started. */
    /* Group is in IDLE state, No result is available. */
    ADC_IDLE = 0U,
    /* The conversion of the specified group has been started and is still going on. */
    /* Group is in BUSY state, So far no result is available */
    ADC_BUSY,
    /* A conversion round (which is not the final one) of the specified group has been finished. */
    /* Group is in COMPLETED state, A result is available for all channels of the group. */
    ADC_COMPLETED,
    /* The result buffer is completely filled. */
    /* Group is in STREAM_COMPLETED state, For each channel of the selected group the number of
     * samples to be acquired is available*/
    ADC_STREAM_COMPLETED
} Adc_StatusType;

/* SWS_Adc_00514: Type for configuring the trigger source for an ADC Channel group. */
typedef enum
{
    /* Group is triggered by a software API call. */
    ADC_TRIGG_SRC_SW = 0U,
    /* Group is triggered by a hardware event. */
    ADC_TRIGG_SRC_HW
} Adc_TriggerSourceType;

/* SWS_Adc_00515: Type for configuring the conversion mode of an ADC Channel group. */
typedef enum
{
    /* Exactly one conversion of each channel in an ADC channel group is performed after the
     * configured trigger event. In case of 'group trigger source software', a started
     * One-Shot conversion can be stopped by a software API call. In case of 'group trigger
     * source hardware', a started One-Shot conversion can be stopped by disabling the
     * trigger event (if supported by hardware). */
    ADC_CONV_MODE_ONESHOT = 0U,
    /* Repeated conversions of each ADC channel in an ADC channel group are performed.
     * 'Continuous conversion mode' is only available for 'group trigger source software'.
     * A started 'Continuous conversion' can be stopped by a software API call. */
    ADC_CONV_MODE_CONTINUOUS
} Adc_GroupConvModeType;

/* SWS_Adc_00519: Type for configuring the streaming access mode buffer type. */
typedef enum
{
    /* The ADC Driver stops the conversion as soon as the stream buffer is full
     * (number of samples reached). */
    ADC_STREAM_BUFFER_LINEAR = 0U,
    /* The ADC Driver continues the conversion even if the stream buffer is full
     * (number of samples reached) by wrapping around the stream buffer itself. */
    ADC_STREAM_BUFFER_CIRCULAR
} Adc_StreamBufferModeType;

/* SWS_Adc_00528: Type for configuring the access mode to group conversion results. */
typedef enum
{
    /* Single access mode */
    ADC_ACCESS_MODE_SINGLE = 0U,
    /* Streaming access mode */
    ADC_ACCESS_MODE_STREAMING
} Adc_GroupAccessModeType;

/* SWS_Adc_00520: Type for configuring on which edge of the hardware trigger signal the driver
 *  should react, i.e. start the conversion (only if supported by the ADC hardware). */
typedef enum
{
    /* React on the falling edge of the hardware trigger signal
     * (only if supported by the ADC hardware). */
    ADC_HW_TRIG_FALLING_EDGE = 1U,
    /* React on the rising edge of the hardware trigger signal
     * (only if supported by the ADC hardware). */
    ADC_HW_TRIG_RISING_EDGE,
    /* React on both edges of the hardware trigger signal
     * (only if supported by the ADC hardware). */
    ADC_HW_TRIG_BOTH_EDGES
/* #Violation: Adc_GeneralTypes_h_REF_2 */
} Adc_HwTriggerSignalType;


/* SWS_Adc_00523: Replacement mechanism, which is used on ADC group level, if a group conversion
 * is interrupted by a group which has a higher priority. */
typedef enum
{
    /* Abort/Restart mechanism is used on group level, if a group is interrupted by a higher
     * priority group. The complete conversion round of the interrupted group (all group channels)
     * is restarted after the higher priority group conversion is finished. If the group is
     * configured in streaming access mode, only the results of the interrupted conversion round
     * are discarded. Results of previous conversion rounds which are already written to the
     * result buffer are not affected. */
    ADC_GROUP_REPL_ABORT_RESTART = 0U,
    /* Suspend/Resume mechanism is used on group level, if a group is interrupted by a higher
     * priority group. The conversion round of the interrupted group is completed after the
     * higher priority group conversion is finished. Results of previous conversion rounds
     * which are already written to the result buffer are not affected. */
    ADC_GROUP_REPL_SUSPEND_RESUME
/* #Violation: Adc_GeneralTypes_h_REF_2 */
}Adc_GroupReplacementType;


/* SWS_Adc_00524: In case of active limit checking: defines which conversion values are taken into
 * account related to the boardes defineed with AdcChannelLowLimit and AdcChannelHighLimit. */
typedef enum
{
    /* Never trigger */
    ADC_RANGE_NEVER = 0x0U,
    /* Range below low limit - low limit value included */
    ADC_RANGE_UNDER_LOW = 0xAU,
    /* Range between low limit and high limit - high limit value included */
    ADC_RANGE_BETWEEN = 0x1U,
    /* Range above high limit */
    ADC_RANGE_OVER_HIGH = 0x6U,
    /* Complete range - independent from channel limit settings */
    ADC_RANGE_ALWAYS = 0x3U,
    /* Range above low limit */
    ADC_RANGE_NOT_UNDER_LOW = 0x9U,
    /* Range above high limit or below low limit - low limit value included */
    ADC_RANGE_NOT_BETWEEN = 0x2U,
    /* Range below high limit - high limit value included */
    ADC_RANGE_NOT_OVER_HIGH = 0x5U
/* #Violation: Adc_GeneralTypes_h_REF_2 */
} Adc_ChannelRangeSelectType;


/* SWS_Adc_00525: Type for alignment of ADC raw results in ADC result buffer
 * (left/right alignment). */
typedef enum
{
    /* right alignment */
    ADC_ALIGN_RIGHT = 0U,
    /* left alignment */
    ADC_ALIGN_LEFT
/* #Violation: Adc_GeneralTypes_h_REF_2 */
} Adc_ResultAlignmentType;


#if (ADC_POWER_STATE_SUPPORTED == STD_ON)
/* SWS_Adc_00526: Power state currently active or set as target power state. */
typedef enum
{
    /* Adc full power mode. */
    ADC_FULL_POWER = 0U,
    /* Adc low power mode. */
    ADC_LOW_POWER,
    /* Adc no define power mode. */
    ADC_NODEFINE_POWER
} Adc_PowerStateType;

/* SWS_Adc_00527: Result of the requests related to power state transitions. */
typedef enum
{
    /* Power state change executed */
    ADC_SERVICE_ACCEPTED = 0U,
    /* ADC Module not initialized */
    ADC_NOT_INIT = 1U,
    /* Wrong API call sequence */
    ADC_SEQUENCE_ERROR = 2U,
    /* The HW module has a failure which prevents it to enter the required power state */
    ADC_HW_FAILURE = 3U,
    /* ADC Module does not support the requested power state */
    ADC_POWER_STATE_NOT_SUPP = 4U,
    /* ADC Module cannot transition directly from the current power state to the requested
     * power state */
    ADC_TRANS_NOT_POSSIBLE = 5U
} Adc_PowerStateRequestResultType;
#endif /* (ADC_POWER_STATE_SUPPORTED  \== STD_ON) */

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* Type definition for HW unit mapping relationship */
/* #Violation: Adc_GeneralTypes_h_REF_1 */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
    /* The index position of the HW unit in Core private configuration parameter structure */
    Adc_HwUnitType                     CoreHwUnitIdx;
    /* Core Id which the HW unit belong to */
    uint8                              HwMapCoreId;
} Adc_HWUnitCoreMapType;

/* Type definition for each ADC HW unit Trigger source data */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
    /* Group ID indicating the group requested in the particular HW Trigger source */
    Adc_GroupType                      GrpId;
    /* Priority level of the Group */
    Adc_GroupPriorityType              GrpPriority;
    /* Trigger source service request flag */
    uint8                              IsrServReqFlg;
} Adc_TriggSrcDataType;

/* Type definition for the Groups which are enabled in the ADC HW unit request source
    added for the optimization of ISR */
typedef struct
{
    /* Group channels in a sequence as configured. Maximum number of channels in a group can be 16 */
    /* #Violation: Adc_GeneralTypes_h_REF_3 */
    Adc_ChannelType                    GrpChannels[16];
    /* Total number of channels in group */
    uint8                              NoOfChannels;
} Adc_GroupDataType;

#if (ADC_ENABLE_QUEUING == STD_ON)
/* Type for store the previous channel group and next channel group ID in queue */
typedef struct
{
    /* This variable will give the Group ID which is previous in the Queue */
    Adc_GroupType                      PreviousGroup;
    /* This variable will give the Group ID which is Next in the Queue */
    Adc_GroupType                      NextGroup;
} Adc_QueueDataType;
#endif /* (ADC_ENABLE_QUEUING  \== STD_ON) */

/* Type definition for the global data information */
/* #Violation: Adc_GeneralTypes_h_REF_1 */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
    /* Array of Pointers which stores the Group Result buffer starting location on Adc_SetupResultBuffer */
    Adc_ValueGroupType                 **GroupResultBufferPtr;
    /* Variable to Hold Group Status */
    uint32                             GroupStatus;
    /* Variable to Hold Group Result Status */
    uint32                             GroupResultStatus;
    /* Variable which states the buffer is full with valid results for each group */
    uint32                             GrpBufferEndResultStatus;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Notification status for all the groups, maximum 32 groups */
    uint32                             GrpNotifStatus;
#endif /* (ADC_GRP_NOTIF_CAPABILITY  \== STD_ON) */
#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API == STD_ON))
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    /* Mask for all running internal channels */
    uint16                             AllRunningCh;
#endif /* (ADC_PRIORITY_IMPLEMENTATION \!= ADC_PRIORITY_NONE) */
#endif /* ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) || (ADC_HW_TRIGGER_API \== STD_ON)) */
    /* Request source related data */
    Adc_TriggSrcDataType               TriggSrcData[ADC_REQSRC_COUNT];
    /* Group data which is enabled in the RS */
    Adc_GroupDataType                  RsGroupData[ADC_REQSRC_COUNT];
#if (ADC_ENABLE_QUEUING == STD_ON)
    /* Array of Queue information */
    Adc_QueueDataType                  *QueueOfSwGroupPtr;
    /* Group Id which will be taken for conversion from Queue */
    Adc_GroupType                      PopGroupId;
    /* Group Id which is last in the Queue */
    Adc_GroupType                      PushGroupId;
#endif /* (ADC_ENABLE_QUEUING  \== STD_ON) */
    /* Number of conversion result set available for each ADC channel group */
    Adc_StreamNumSampleType            *NumValidConResPtr;
} Adc_GlobalDataType;

/* Type definition for global variables set */
typedef struct
{
#if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* Pointer to the initialize status */
    uint8                              *InitStatusPtr;
#endif /* (ADC_DEV_ERROR_DETECT  \== STD_ON) */
    /* Pointer to the global data buffer */
    Adc_GlobalDataType                 *GlobalDataSetPtr;
#if (ADC_ENABLE_QUEUING == STD_ON)
    /* Pointer to the Array of Queue information */
    Adc_QueueDataType                  *GrpQueueOfSwPtr;
#endif /* (ADC_ENABLE_QUEUING  \== STD_ON) */
    /* Pointer to the buffer array of Number of conversion result */
    Adc_StreamNumSampleType            *GroupNumValidConResPtr;
    /* Pointer to the buffer that save the data value(Group conversion data result buffer) */
    Adc_ValueGroupType                 **GrpRsltDataBfPtr;
} Adc_GlobalDataSetType;

/* Type definition for AdcGroupConfiguration */
/* #Violation: Adc_GeneralTypes_h_REF_1 */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
    /* When HW unit is master in sync group, Mark whether this group contains synchronous
     * request channels. */
    boolean                            IsSyncChExists;
#endif /* (ADC_HW_SYNC_CONV_GROUP_EN  \== STD_ON) */
    /* Number of ADC values to be acquired in streaming access mode */
    Adc_StreamNumSampleType            NumSamples;
    /* Internal channel mask from group definition - derived from the tool */
    uint16                             IntChMask;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* SWS_Adc_00104 */
    /* Notification function pointer */
    Adc_NotifFctPtrType                NotifFctPtr;
#endif /* (ADC_GRP_NOTIF_CAPABILITY  \== STD_ON) */
    /* Pointer to assignment of channels to a channel group */
    /* First element is the number of configured channels in the group */
    const Adc_GroupDefType             *GroupDefinitionPtr;
#if (ADC_DMA_MODE_ENABLE == STD_ON)
    /* Pointer to the array of result register configuration */
    const uint8                        *GroupResRegPtr;
#endif /* \(ADC_DMA_MODE_ENABLE == STD_ON) */
#if (ADC_HW_TRIGGER_API == STD_ON)
    /* Pointer to the HW trigger configuration parameters */
    const Saradc_GatingTriggerConfig   *HwTrigConfigPtr;
#endif /* (ADC_HW_TRIGGER_API  \== STD_ON) */
    /* Conversion result accumulation number */
    uint8                              ResultAccumNum;
    /* Group trigger source type : SW / HW */
    Adc_TriggerSourceType              TriggSrc;
    /* Group request source as in uC: RS0 - RS2 */
    Saradc_RequestSource               GrpRequestSrc;
    /* Group access mode */
    Adc_GroupAccessModeType            AccessMode;
    /* Group conversion mode */
    Adc_GroupConvModeType              ConvMode;
    /* Buffer mode type - Configure streaming buffer as "linear buffer" or "circular buffer" */
    Adc_StreamBufferModeType           StreamBufferMode;
    /* Switching of Priority mechanism */
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    /* Priority level of the group */
    Adc_GroupPriorityType              PriorityLevel;
#endif /* (ADC_PRIORITY_IMPLEMENTATION \== ADC_PRIORITY_HW_SW) */
} Adc_GroupCfgType;

#if (defined(ADC_ENABLE_LIMIT_CHECK) && (ADC_ENABLE_LIMIT_CHECK == STD_ON))
/* Type definition for limit checking configuration */
/* #Violation: Adc_GeneralTypes_h_REF_1 */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
    /* Channel limit checking boundary range */
    Saradc_BoundaryConfig              ChLimitChkConfigData;
    /* Limit checking interrupt method */
    Saradc_ChannelInterruptMode        ChLimitChkIntrMod;
} Adc_ChannelLimitCheckType;
#endif /* (defined(ADC_ENABLE_LIMIT_CHECK) && (ADC_ENABLE_LIMIT_CHECK \== STD_ON)) */

/* Type definition for channel configuration */
/* #Violation: Adc_GeneralTypes_h_REF_1 */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
#if (defined(ADC_ENABLE_LIMIT_CHECK) && (ADC_ENABLE_LIMIT_CHECK == STD_ON))
    /* Pointer to the limit checking configuration parameters */
    const Adc_ChannelLimitCheckType *ChLimitCheckingConfigPtr;
#endif /* (defined(ADC_ENABLE_LIMIT_CHECK) && (ADC_ENABLE_LIMIT_CHECK \== STD_ON)) */
    /* Physical channel configuration parameter */
    Saradc_ChannelConfig            ChConfigData;
    /* Dynamic configuration parameters of the channel */
    Saradc_DynaChannleConfig        ChRuntimeConfigData;
} Adc_ChannelCfgType;

/* ADC Kernel configuration structure */
/* #Violation: Adc_GeneralTypes_h_REF_1 */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
    /* ADC Hardware Unit */
    Adc_HwUnitType                     AdcHwUnit;
#if ((ADC_POLLING_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE == STD_ON))
    /* Result handling implementation */
    uint8                              RsltHldMthd;
#endif /* ((ADC_POLLING_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE \== STD_ON)) */
    /* Pointer to Adc Hw Unit configuration */
    const Saradc_ModuleConfig          *HwCfgPtr;
#if (ADC_HW_SYNC_CONV_GROUP_EN == STD_ON)
    /* When HW unit is master in sync group, this pointer to the HW unit set of slave */
    const Adc_HwUnitType               *SyncGrpSlaveHwPtr;
#endif /* (ADC_HW_SYNC_CONV_GROUP_EN  \== STD_ON) */
    /* Number of channels */
    uint8                              ChNum;
    /* Pointer to the array of channel configuration */
    const Adc_ChannelCfgType           *ChCfgPtr;
    /* Pointer to the array of group configuration */
    const Adc_GroupCfgType             *GrpCfgPtr;
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    /* Pointer to the array of Group mask for SW trigger sources */
    const uint32                       *TriggSrcGroupMaskPtr;
#endif /* (ADC_PRIORITY_IMPLEMENTATION \== ADC_PRIORITY_HW_SW) */
    /* Total number of configured groups - Maximum 32 groups for each ADC HW Unit */
    uint8                              TotCfgGrps;
    /* Index of group start position in different HW unit for each core, this is used to
     * get group data information in a buffer in each core */
    uint8                              IndexGrpsCore;
#if (ADC_DMA_MODE_ENABLE == STD_ON)
    /* ADC interrupt enable status in DMA mode */
    boolean                            IsIntEn;
#endif /* (ADC_DMA_MODE_ENABLE \== STD_ON) */
} Adc_KernelConfigType;

/* Type for HW unit configuration in core */
/* #Violation: Adc_GeneralTypes_h_REF_1 */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
    /* Maximum number of the ADC HW unit allocated to the core */
    uint8                              MaxCoreHwUnit;
    /* Pointer to ADC HW unit configuration */
    const Adc_KernelConfigType         *HwUnitConfigPtr;
} Adc_CoreConfigType;

/* SWS_Adc_00505: Data structure containing the set of configuration parameters required for
 * initializing the ADC Driver and ADC HW Unit(s). */
/* #Violation: Adc_GeneralTypes_h_REF_4 */
typedef struct
{
    /* Pointer to ADC HW unit configuration buffer address */
    const Adc_CoreConfigType           *CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* Map information that ADC HW unit allocated to the each core */
    const Adc_HWUnitCoreMapType        *HwUnitToCorePtr;
} Adc_ConfigType;

#endif /* ADC_GENERALTYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
