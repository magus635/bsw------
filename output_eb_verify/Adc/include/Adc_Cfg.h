#ifndef ADC_CFG_H
#define ADC_CFG_H

/* Enumerations from Definition */

/* AdcHwUnitId */
typedef enum {
    
    SARADC0,
    
    SARADC1,
    
    SARADC2,
    
    SARADC3,
    
    SARADC8,
    
    SARADC9
    
} AdcHwUnitIdType;


/* AdcClockSource */
typedef enum {
    
    undefined
    
} AdcClockSourceType;


/* AdcRequestSource0Prio */
typedef enum {
    
    LOWEST,
    
    LOW,
    
    HIGH,
    
    HIGHEST
    
} AdcRequestSource0PrioType;


/* AdcRequestSource1Prio */
typedef enum {
    
    LOWEST,
    
    LOW,
    
    HIGH,
    
    HIGHEST
    
} AdcRequestSource1PrioType;


/* AdcRequestSource2Prio */
typedef enum {
    
    LOWEST,
    
    LOW,
    
    HIGH,
    
    HIGHEST
    
} AdcRequestSource2PrioType;


/* AdcResolution */
typedef enum {
    
    BITS_12,
    
    BITS_10,
    
    BITS_8
    
} AdcResolutionType;


/* AdcRefVoltsrcHigh */
typedef enum {
    
    REF_VOLTAGE_VAREF,
    
    REF_VOLTAGE_CH0
    
} AdcRefVoltsrcHighType;


/* AdcRefVoltsrcLow */
typedef enum {
    
    REF_VOLTAGE_GND
    
} AdcRefVoltsrcLowType;


/* AdcResultHandlingImplementation */
typedef enum {
    
    INTERRUPT_MODE,
    
    POLLING_MODE,
    
    DMA_MODE
    
} AdcResultHandlingImplementationType;


/* AdcSyncConvMode */
typedef enum {
    
    ADC_STANDALONE,
    
    ADC_SYNC_CONV_MASTER,
    
    ADC_SYNC_CONV_SLAVE
    
} AdcSyncConvModeType;


/* AdcAnChannelNum */
typedef enum {
    
    AN0,
    
    AN1,
    
    AN2,
    
    AN3,
    
    AN4,
    
    AN5,
    
    AN6,
    
    AN7,
    
    AN43,
    
    AN8,
    
    AN9,
    
    AN10,
    
    AN11,
    
    AN12,
    
    AN13,
    
    AN14,
    
    AN15,
    
    AN47,
    
    AN16,
    
    AN17,
    
    AN18,
    
    AN19,
    
    AN20,
    
    AN21,
    
    AN22,
    
    AN23,
    
    P00_1,
    
    AN24_P40_0,
    
    AN25_P40_1,
    
    AN26_P40_2,
    
    AN27_P40_3,
    
    AN28,
    
    AN29,
    
    AN30,
    
    AN31,
    
    AN40,
    
    AN41,
    
    AN42,
    
    AN32_P40_4,
    
    AN33_P40_5,
    
    AN34,
    
    AN35,
    
    AN36_P40_6,
    
    AN37_P40_7,
    
    AN38_P40_8,
    
    AN39_P40_9,
    
    AN44,
    
    AN45,
    
    AN46,
    
    P00_12,
    
    P00_11,
    
    P00_10,
    
    P00_9,
    
    P00_8,
    
    P00_7,
    
    P00_6,
    
    P00_5,
    
    P00_4,
    
    P00_3,
    
    P00_2
    
} AdcAnChannelNumType;


/* AdcChannelRangeSelect */
typedef enum {
    
    ADC_RANGE_ALWAYS,
    
    ADC_RANGE_BETWEEN,
    
    ADC_RANGE_NOT_BETWEEN,
    
    ADC_RANGE_NOT_OVER_HIGH,
    
    ADC_RANGE_NOT_UNDER_LOW,
    
    ADC_RANGE_OVER_HIGH,
    
    ADC_RANGE_UNDER_LOW
    
} AdcChannelRangeSelectType;


/* AdcChannelRefVoltsrcHigh */
typedef enum {
    
    REF_VOLTAGE_VAREF
    
} AdcChannelRefVoltsrcHighType;


/* AdcChannelRefVoltsrcLow */
typedef enum {
    
    undefined
    
} AdcChannelRefVoltsrcLowType;


/* AdcGroupAccessMode */
typedef enum {
    
    ADC_ACCESS_MODE_SINGLE,
    
    ADC_ACCESS_MODE_STREAMING
    
} AdcGroupAccessModeType;


/* AdcGroupConversionMode */
typedef enum {
    
    ADC_CONV_MODE_CONTINUOUS,
    
    ADC_CONV_MODE_ONESHOT
    
} AdcGroupConversionModeType;


/* AdcGroupReplacement */
typedef enum {
    
    ADC_GROUP_REPL_ABORT_RESTART,
    
    ADC_GROUP_REPL_SUSPEND_RESUME
    
} AdcGroupReplacementType;


/* AdcGroupTriggSrc */
typedef enum {
    
    ADC_TRIGG_SRC_HW,
    
    ADC_TRIGG_SRC_SW
    
} AdcGroupTriggSrcType;


/* AdcGroupRequestSource */
typedef enum {
    
    REQUESTSOURCE_QUEUE0,
    
    REQUESTSOURCE_QUEUE1,
    
    REQUESTSOURCE_QUEUE2
    
} AdcGroupRequestSourceType;


/* AdcHwGatePin */
typedef enum {
    
    undefined
    
} AdcHwGatePinType;


/* AdcHwGateSignal */
typedef enum {
    
    ADC_GATE_SIGNAL_HIGH,
    
    ADC_GATE_SIGNAL_LOW,
    
    ADC_GATE_SIGNAL_NONE
    
} AdcHwGateSignalType;


/* AdcHwTrigSignal */
typedef enum {
    
    ADC_HW_TRIG_BOTH_EDGES,
    
    ADC_HW_TRIG_FALLING_EDGE,
    
    ADC_HW_TRIG_RISING_EDGE
    
} AdcHwTrigSignalType;


/* AdcStreamingBufferMode */
typedef enum {
    
    ADC_STREAM_BUFFER_CIRCULAR,
    
    ADC_STREAM_BUFFER_LINEAR
    
} AdcStreamingBufferModeType;


/* AdcPriorityImplementation */
typedef enum {
    
    ADC_PRIORITY_HW,
    
    ADC_PRIORITY_HW_SW,
    
    ADC_PRIORITY_NONE
    
} AdcPriorityImplementationType;


/* AdcResultAlignment */
typedef enum {
    
    ADC_ALIGN_LEFT,
    
    ADC_ALIGN_RIGHT
    
} AdcResultAlignmentType;



/* Pre-compile Parameters */


#endif /* ADC_CFG_H */
