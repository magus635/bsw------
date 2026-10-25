/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    saradc_hal.h
 * Author:      30037
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/

/*
*#Violation Summary
*#saradc_hal_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity. 
*
*#saradc_hal_h_REF_2:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to registers.
*
*#saradc_hal_h_REF_3:MISRAC2012-Rule-2.5; 
*Justification: The macros are reserved for upper layers.
*
*#saradc_hal_h_REF_4:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#saradc_hal_h_REF_5:MISRAC2012-Rule-11.4;
* Justification: Casting a pointer to an integral type to obtain its address.
*/

#ifndef SARADC_HAL_H_
#define SARADC_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "saradc_std.h"
#include "saradc_register.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Flush SARADC queue */
/* #Violation: saradc_hal_h_REF_3 */
#define SARADC_QUEUE_MODE_CLEAR 0x1000U

/* Reset the QTRICTRL register, including disable external trigger signal  */
/* #Violation: saradc_hal_h_REF_3 */
#define SARADC_QUEUE_CTRL_CLEAR 0U

/* Disable internal timer */
#define SARADC_QUEUE_TIME_CLEAR 0U

/* Define the number of calibration counts */
#define SARADC_CALC_COUNTER 100U

/* #Violation: saradc_hal_h_REF_3 */
/* The valid bit position of the result in the result register  */
#define SARADC_RESULT_VALID 0x1000000U
/* Mask all source interrupt */
#define SARADC_SOURCE_MASK 0xC0000000U
/* Mask all channel interrupt */
#define SARADC_CHANNEL_MASK 0xC0000000U
/* Mask all result interrupt */
#define SARADC_RESULT_MASK 0xC0000000U
/* Unmask all source interrupt */
#define SARADC_SOURCE_UNMASK 0x3FFFFFFFU
/* Unmask all channel interrupt */
#define SARADC_CHANNEL_UNMASK 0x3FFFFFFFU
/* UnMask all result interrupt */
#define SARADC_RESULT_UNMASK 0x3FFFFFFFU
/* SARADC request queues number */
#define SARADC_QUEUE_NUM 3U
/* SARADC result reguster number */
#define SARADC_RESULT_REG_NUM 16U

/** \brief  Queue config*/
/* Enable Refill function. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_QUEUEOPTION_REFILL  ((uint32)1U << 5)
/* Enable external trigger */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_QUEUEOPTION_EXTERNALTRIGGER  ((uint32)1U << 7)
/* Enable source interrupt */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_QUEUEOPTION_SOURCEINTERRUPT  ((uint32)1U << 8)
/* Enable pull down diagnostics. 
   Note:THA6206 version C, the function only available for SARADCx channel_2. 
        THA6412/THA6104 and THA6206 version D, all SARADCx can use the function.
*/
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_DIAG_PULLDOWN  ((uint32)1U << 9)
/* Enable multiplexer pull down diagnostics.
   Note:THA6206 version C, the function only available for SARADCx channel_1. 
        THA6412/THA6104 and THA6206 version D, all SARADCx can use the function.
*/
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_DIAG_MULTIPLEXER_PULLDOWN  ((uint32)1U << 10)
/* Enable multiplexer pull up diagnostics.
   Note:THA6206 version C, the function only available for SARADCx channel_0.
        THA6412/THA6104 and THA6206 version D, all SARADCx can use the function.
*/
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_DIAG_MULTIPLEXER_PULLUP  ((uint32)1U << 11)
/* AVDD as converter diagnostics select */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_CONVERTERSELECTVDDM  (uint32)((1U << 12) | (0U << 13))
/* AGND as converter diagnostics select */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_CONVERTERSELECTAGND  (uint32)((1U << 12) | (1U << 13))
/* AVDD/2 as converter diagnostics Select */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_CONVERTERSELECTHALFVDDM  (uint32)((1U << 12) | (2U << 13))
/* AVDD*2/3 as converter diagnostics Select */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_CONVERTERSELECTTWOTHIRDSVDDM  (uint32)((1U << 12) | (3U << 13))

/** \brief  Interrupt status */
/* Interrupt 0 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT0_GENERATION  ((uint32)1U << 0)
/* Interrupt 1 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT1_GENERATION  ((uint32)1U << 1)
/* Interrupt 2 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT2_GENERATION  ((uint32)1U << 2)
/* Interrupt 3 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT3_GENERATION  ((uint32)1U << 3)
/* Interrupt 4 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT4_GENERATION  ((uint32)1U << 4)
/* Interrupt 5 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT5_GENERATION  ((uint32)1U << 5)
/* Interrupt 6 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT6_GENERATION  ((uint32)1U << 6)
/* Interrupt 7 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT7_GENERATION  ((uint32)1U << 7)
/* Interrupt 8 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT8_GENERATION  ((uint32)1U << 8)
/* Interrupt 9 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT9_GENERATION  ((uint32)1U << 9)
/* Interrupt 10 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT10_GENERATION  ((uint32)1U << 10)
/* Interrupt 11 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT11_GENERATION  ((uint32)1U << 11)
/* Interrupt 12 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT12_GENERATION  ((uint32)1U << 12)
/* Interrupt 13 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT13_GENERATION  ((uint32)1U << 13)
/* Interrupt 14 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT14_GENERATION  ((uint32)1U << 14)
/* Interrupt 15 generatation. */
/* #Violation: saradc_hal_h_REF_3 */
#define    SARADC_INTERRUPT15_GENERATION  ((uint32)1U << 15)

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Interrupt source select. */
typedef enum
{
    SARADC_INTERRUPTSOURCE_QUEUE = 0U, /* Request queue source interrupt. */
    SARADC_INTERRUPTSOURCE_CHANNEL,    /* Channel interrupt. */
    SARADC_INTERRUPTSOURCE_RESULT      /* Result interrupt. */
} Saradc_InterruptSource;

/* Set channel interrupt mode. */
typedef enum
{
    SARADC_CHANNELINTERRUPT_DISABLE = 0U, /* Set interrupt disable. */
    SARADC_CHANNELINTERRUPT_INBOUNDARY,   /* Conversion in boundary generate interrupt. */
    SARADC_CHANNELINTERRUPT_OUTBOUNDARY,  /* Conversion out of boundary generate interrupt. */
    SARADC_CHANNELINTERRUPT_ENABLE        /* Set interrupt enable (Ignore boundary). */
} Saradc_ChannelInterruptMode;

/* Map events to interrupts. */
typedef enum
{
    SARADC_MAPPING_INTERRUPT0 = 0U,  /* Mapping to group interrupt0. */
    SARADC_MAPPING_INTERRUPT1,       /* Mapping to group interrupt1. */
    SARADC_MAPPING_INTERRUPT2,       /* Mapping to group interrupt2. */
    SARADC_MAPPING_INTERRUPT3,       /* Mapping to group interrupt3. */
    SARADC_MAPPING_SHARE_INTERRUPT0, /* Mapping to share interrupt0. */
    SARADC_MAPPING_SHARE_INTERRUPT1, /* Mapping to share interrupt1. */
    SARADC_MAPPING_SHARE_INTERRUPT2, /* Mapping to share interrupt2. */
    SARADC_MAPPING_SHARE_INTERRUPT3  /* Mapping to share interrupt3. */
} Saradc_InterruptMapping;

/* Saradc gating mode select. */
typedef enum
{
    SARADC_GATINGMODE_DISABLED = 0U, /* Gating is disabled, no conversion request are issued */
    SARADC_GATINGMODE_ALWAYS,        /* Conversion request is issued if conversion request is generate */
    SARADC_GATINGMODE_GATINGHIGH,    /* Conversion request is issued if conversion request is generate and the gating
                                        signal is high */
    SARADC_GATINGMODE_GATINGLOW /* Conversion request is issued if conversion request is generate and the gating signal
                                   is low */
} Saradc_GatingMode;

/* Saradc trigger mode select. */
typedef enum
{
    SARADC_TRIGGERMODE_NOEXTERNALTRIGGER = 0U, /* No external trigger */
    SARADC_TRIGGERMODE_FALLINGEDGE,            /* Trigger event upon a falling edge */
    SARADC_TRIGGERMODE_RISINGEDGE,             /* Trigger event upon a rising edge */
    SARADC_TRIGGERMODE_ANYEDGE                 /* Trigger event upon any edge */
} Saradc_TriggerMode;

/* Saradc gating source select. */
typedef enum
{
    SARADC_GATINGSOURCE_GTM_TRIGGER0 = 0U,  /* GTM trigger0 gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER1,       /* GTM trigger1 gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER4 = 6U,  /* GTM trigger4 gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER2 = 10U, /* GTM trigger2 gating source */
    SARADC_GATINGSOURCE_GTM_TRIGGER3,       /* GTM trigger3 gating source */
    SARADC_GATINGSOURCE_EXTI_TRIGGER,       /* EXTI gating source  */
    SARADC_GATINGSOURCE_QUEUE_TRIGGER = 15U /* Q0/Q1 internal gating source */
} Saradc_GatingSource;

/* Saradc trigger source select. */
typedef enum
{
    SARADC_TRIGGERSOURCE_RDC_TRIGGER = 3U,         /* RDC trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER4 = 6U,        /* GTM trigger4 trigger source */
    SARADC_TRIGGERSOURCE_EXTI_TRIGGER,             /* EXTI trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER0,             /* GTM trigger0 trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER1,             /* GTM trigger1 trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER2,             /* GTM trigger2 trigger source */
    SARADC_TRIGGERSOURCE_GTM_TRIGGER3,             /* GTM trigger3 trigger source */
    SARADC_TRIGGERSOURCE_INTERRUPT_TRIGGER,        /* Interrupt trigger source */
    SARADC_TRIGGERSOURCE_COMMON0INTERRUPT_TRIGGER, /* Common0 interrupt trigger source */
    SARADC_TRIGGERSOURCE_COMMON1INTERRUPT_TRIGGER, /* Common1 interrupt trigger source */
    SARADC_TRIGGERSOURCE_QUEUE_TRIGGER             /* Q0/Q1 internal trigger source */
} Saradc_TriggerSource;

/* Data reduction mode setting. */
typedef enum
{
    SARADC_DATAREDUCTIONMODE_0 = 0U, /* Data reduction disabled. */
    SARADC_DATAREDUCTIONMODE_1,      /* Accumulate 2 result values */
    SARADC_DATAREDUCTIONMODE_2,      /* Accumulate 3 result values */
    SARADC_DATAREDUCTIONMODE_3,      /* Accumulate 4 result values */
    SARADC_DATAREDUCTIONMODE_4,      /* Accumulate 5 result values */
    SARADC_DATAREDUCTIONMODE_5,      /* Accumulate 6 result values */
    SARADC_DATAREDUCTIONMODE_6,      /* Accumulate 7 result values */
    SARADC_DATAREDUCTIONMODE_7,      /* Accumulate 8 result values */
    SARADC_DATAREDUCTIONMODE_8,      /* Accumulate 9 result values */
    SARADC_DATAREDUCTIONMODE_9,      /* Accumulate 10 result values */
    SARADC_DATAREDUCTIONMODE_10,     /* Accumulate 11 result values */
    SARADC_DATAREDUCTIONMODE_11,     /* Accumulate 12 result values */
    SARADC_DATAREDUCTIONMODE_12,     /* Accumulate 13 result values */
    SARADC_DATAREDUCTIONMODE_13,     /* Accumulate 14 result values */
    SARADC_DATAREDUCTIONMODE_14,     /* Accumulate 15 result values */
    SARADC_DATAREDUCTIONMODE_15      /* Accumulate 16 result values. */
} Saradc_DataReductionMode;
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Set queue trigger and gating source/mode. */
/* #Violation: saradc_hal_h_REF_1 */
typedef struct
{
    Saradc_GatingSource gatingSource;        /* Set queue gating source. */
    Saradc_TriggerSource triggerSource;      /* Set queue trigger source. */
    Saradc_GatingMode gatingMode;            /* Set queue gating mode. */
    Saradc_TriggerMode triggerMode;          /* Set queue trigger mode. */
    Saradc_TriggerByTimerConfig timerConfig; /* Timer trigger queue mode config. */
} Saradc_GatingTriggerConfig;

/* Saradc boundary value setting. */
typedef struct
{
    uint16 lowBoundary;  /* Specifies lower boundary voltage*/
    uint16 highBoundary; /* Specifies high boundary voltage*/
} Saradc_BoundaryConfig;

/* Saradc interrupt setting. */
typedef struct
{
    boolean interruptEnable;                  /* 0: Set interrupt disable.1: Set interrupt enable */
    Saradc_InterruptMapping interruptMapping; /* Set interrupt mapping. */
} Saradc_InterruptConfig;

/* Saradc channel interrupt setting. */
typedef struct
{
    Saradc_ChannelInterruptMode channelInterruptEnable; /* Set channel interrupt mode. */
    Saradc_InterruptMapping interruptMapping;           /* Set interrupt mapping. */
} Saradc_ChannelInterruptConfig;

/* Saradc channel config. */
typedef struct
{
    Saradc_ChannelResult channelResult;           /* Channel result select */
    Saradc_StorageMode storageMode;               /* Specifies conversion result will not be overwrite if enabled. */
    boolean enableDma;                            /* Enable DMA processing channel conversion result. */
    boolean rightAlignedStorage;    /* 0: Specified result is right aligned.1: Specified result is left aligned. */
    boolean enableSynchronize;      /* 0: Specifies channel synchronized conversion disable.1: Specifies channel synchronized
                                    conversion enable. */
    boolean boundaryRange;      /* 0: Less than the upper boundary, greater than the lower boundary is the threshold range.
                                1: Greater than the upper boundary, greater than the lower boundary is the threshold range. */
    boolean boundaryResultControl;   /* 0: Discard result out of range.1: Retain result out of range */
    Saradc_Hdi hdiIfEn;             /* HDI interface enable select */
} Saradc_ChannelConfig;

/* Saradc dynamic channel config. */
typedef struct
{
    Saradc_ChannelResult channelResult; /* Channel result select */
    boolean enableDma;                  /* Enable DMA processing channel conversion result. */
    boolean enableSynchronize;          /* 0: Specifies channel synchronized conversion disable.1: Specifies channel synchronized
                                           conversion enable. */
    boolean boundaryRange;              /* 0: Less than the upper boundary, greater than the lower boundary is the threshold range.
                                           1: Greater than the upper boundary, greater than the lower boundary is the threshold range. */
    boolean boundaryResultControl;      /* 0: Discard result out of range.1: Retain result out of range */
    Saradc_Hdi hdiIfEn;                 /* HDI interface enable select */
} Saradc_DynaChannleConfig;

/* Saradc Module config. */
/* #Violation: saradc_hal_h_REF_1 */
typedef struct
{
    uint8 divider;                            /* Saradc converter divider. */
    uint8 sampleTime;                         /* Saradc sample time. */
    Saradc_Resolution resolution;             /* Saradc converter resolution. */
    Saradc_ConverterSource converterSource;   /* Saradc synchronous converter source. */
    Saradc_QueueCommonConfig requestQueueConfig[3]; /* Request queue config. */
} Saradc_ModuleConfig;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Saradc_Hal_InitModule
 * Description:  Initialize the specified saradc module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               pConfig: pointer to saradc configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_InitModule(SARADC_MODULE *const pSaradc, const Saradc_ModuleConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_DeInitModule
 * Description:  De-initialize the saradc module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc:pointer to saradc module
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_DeInitModule(SARADC_MODULE *const pSaradc);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_OpenCalibration
 * Description:  Open saradc calibration function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc:pointer to saradc module 
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       This function can only be used after polling and receiving a TRUE value from the Saradc_Hal_GetAnalogReadyFlg 
 *               function. 
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_OpenCalibration(SARADC_MODULE *const pSaradc);

/**********************************************************************************************************************
 * Function:     uint32 Saradc_Hal_GetInterruptStatus
 * Description:  Get saradc interrupt status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               interruptSource:interrupt source.
 * Inout:        None
 * Output:       None
 * Return:       uint32:Interrupt status:
 *               1<<0    interrupt0 generate
 *               1<<1    interrupt1 generate
 *               1<<2    interrupt2 generate
 *               1<<3    interrupt3 generate
 *               1<<4    interrupt4 generate
 *               1<<5    interrupt5 generate
 *               1<<6    interrupt6 generate
 *               1<<7    interrupt7 generate
 *               1<<8    interrupt8 generate
 *               1<<9    interrupt9 generate
 *               1<<10    interrupt10 generate
 *               1<<11    interrupt11 generate
 *               1<<12    interrupt12 generate
 *               1<<13    interrupt13 generate
 *               1<<14    interrupt14 generate
 *               1<<15    interrupt15 generate
 *               Multiple interrupts can be generated simultaneously!!
 *
 *               Queue source (less than(1<<3))
 *               Channel source (less than (1<<12))
 *               Result source (less than (1<<16))
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern uint32 Saradc_Hal_GetInterruptStatus(const SARADC_MODULE *const pSaradc, Saradc_InterruptSource interruptSource);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_ClearInterruptStatus
 * Description:  Clear saradc interrupt status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               interruptSource:interrupt source.
 *               interruptID:
 *               1<<0    interrupt0 generate
 *               1<<1    interrupt1 generate
 *               1<<2    interrupt2 generate
 *               1<<3    interrupt3 generate
 *               1<<4    interrupt4 generate
 *               1<<5    interrupt5 generate
 *               1<<6    interrupt6 generate
 *               1<<7    interrupt7 generate
 *               1<<8    interrupt8 generate
 *               1<<9    interrupt9 generate
 *               1<<10    interrupt10 generate
 *               1<<11    interrupt11 generate
 *               1<<12    interrupt12 generate
 *               1<<13    interrupt13 generate
 *               1<<14    interrupt14 generate
 *               1<<15    interrupt15 generate
 *               Multiple interrupts can be cleared simultaneously!!
 *
 *               Queue source (less than(1<<3))
 *               Channel source (less than (1<<12))
 *               Result source (less than (1<<16))
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern void Saradc_Hal_ClearInterruptStatus(SARADC_MODULE *const pSaradc, Saradc_InterruptSource interruptSource, uint32 interruptID);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_InitChannel
 * Description:  Initializes the specified channel of the specified saradc.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelID:channel ID.
 *               pchannelConfig: channel config structure.
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_InitChannel(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, const Saradc_ChannelConfig *const pchannelConfig);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_DynamicChannelConfig
 * Description:  Configurate the specified channel function of the specified saradc dynamically.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelID:channel ID.
 *               pchannelConfig: channel config structure.
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/08/22    001368     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_DynamicChannelConfig(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                            const Saradc_DynaChannleConfig *const pChannelConfig);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_FillQueue
 * Description:  Add channel to queue and set diagnostic function.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When operate different Queue hardwares, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               channelID:channel ID.
 *               requestSource: request source selection
 *               option:queue config
 *               queue config option:
 *               1<<5    Enable Refill
 *               1<<7    Enable external trigger
 *               1<<8    Enable source interrupt
 *               1<<9    Enable Pull down diagnostics
 *               1<<10    Enable multiplexer Pull Down diagnostics
 *               1<<11    Enable multiplexer Pull Up Diagnostics
 *               (1U << 12) | (0U << 13)    VDDM as Converter Diagnostics select
 *               (1U << 12) | (1U << 13)    AGND as Converter Diagnostics select
 *               (1U << 12) | (2U << 13)    VDD/2 as Converter Diagnostics Select
 *               (1U << 12) | (3U << 13)    VDD*2/3 as Converter Diagnostics Select
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error
 *                        TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_FillQueue(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, Saradc_RequestSource requestSource, uint32 option);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_FlushQueue
 * Description:  Clear the channel and request information in a specific queue.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When operate different Queue hardwares, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               requestSource: request source selection
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_FlushQueue(SARADC_MODULE *const pSaradc, Saradc_RequestSource requestSource);


/**********************************************************************************************************************
 * Function:     Saradc_Hal_GetResult
 * Description:  Get conversion result.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               resultRegisterID: result register ID
 * Inout:        None
 * Output:       None
 * Return:       uint16: Conversion result
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern uint16 Saradc_Hal_GetResult(const SARADC_MODULE *const pSaradc, Saradc_ChannelResult resultRegisterID);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_GetResultValid
 * Description:  Get conversion result valid flag.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               resultRegisterID: result register ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE:invalid, TRUE:valid
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_GetResultValid(const SARADC_MODULE *const pSaradc, Saradc_ChannelResult resultRegisterID);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_SetBoundary
 * Description:  Boundary value config.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               pBoundaryConfig: boundary value config.
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_SetBoundary(SARADC_MODULE *const pSaradc, const Saradc_BoundaryConfig *const pBoundaryConfig);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_SetTriggerGating
 * Description:  Config specified queue trigger and gatting source/mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When operate different Queue hardwares, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               ptriggerConfig: Config queue trigger and gating source/mode
 *               requestsource: request source queue
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_SetTriggerGating(SARADC_MODULE *const pSaradc, const Saradc_GatingTriggerConfig *const pTriggerConfig, Saradc_RequestSource requestSource);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_SetResultInterrupt
 * Description:  Result interrupt enable/disable and mapping.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelResult:result register ID.
 *               pResultInterruptConfig: result interrupt config pointer
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_SetResultInterrupt(SARADC_MODULE *const pSaradc, Saradc_ChannelResult channelResult, const Saradc_InterruptConfig *const pResultInterruptConfig);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_MaskSourceInterrupt
 * Description:  Enable/Disable masking the specified queue Interrupt and mapping
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               mask: whether mask source interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_MaskSourceInterrupt(SARADC_MODULE *const pSaradc, boolean mask);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_MaskResultInterrupt
 * Description:  Enable/Disable masking the specified result register Interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               mask: whether mask result interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_MaskResultInterrupt(SARADC_MODULE *const pSaradc, boolean mask);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_MaskChannelInterrupt
 * Description:  Enable/Disable masking the specified Channel Interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               mask: whether mask channel interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_MaskChannelInterrupt(SARADC_MODULE *const pSaradc, boolean mask);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_SetSourceInterrupt
 * Description:  Config specified queue Interrupt and mapping.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               sourceInterruptMapping: Interrupt  mapping.
 *               requestsource: request source queue
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_SetSourceInterrupt(SARADC_MODULE *const pSaradc, Saradc_InterruptMapping sourceInterruptMapping, Saradc_RequestSource requestSource);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_SetChannelInterrupt
 * Description:  Channel interrupt mode select and mapping.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSaradc: pointer to saradc module
 *               channelID:channel ID.
 *               pChannelInterruptConfig: channel interrupt config pointer
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_SetChannelInterrupt(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, const Saradc_ChannelInterruptConfig *const pChannelInterruptConfig);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_SetQueueStartMode
 * Description:  Set the saradc working mode of Queues,
 *               (Wait-for-start / Cancel-inject-repeat mode).
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When set different SARADC modules, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               startMode:queue start mode 
 *               requestSource:request source queue
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_SetQueueStartMode(SARADC_MODULE *const pSaradc,Saradc_StartMode startMode, Saradc_RequestSource requestSource);     


#if defined (THA6_THA6206D)
/**********************************************************************************************************************
 * Function:     Saradc_Hal_Ch2StrongPullDownSet
 * Description:  Enable/Disable channel strong pull-down diagnostic function. 
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant 
 * Input:        pSaradc: pointer to saradc module
 *               enDisCfg: TRUE: Enable CH2 strong pull-down function
 *                         FALSE: Disable CH2 strong pull-down function
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2026/01/28    01368     Create
 *********************************************************************************************************************/
extern boolean Saradc_Hal_Ch2StrongPullDownSet(SARADC_MODULE *const pSaradc, boolean enDisCfg);
#endif

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Saradc_Hal_TriggerBySoftware
 * Description:  Software trigger queue to convert.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When operate different Queue hardwares, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               requestsource:request source selection
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Saradc_Hal_TriggerBySoftware(SARADC_MODULE *const pSaradc, Saradc_RequestSource requestSource);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_TrigTimerBySoftware
 * Description:  Software starts the timer to trigger the queue for conversion.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When operate different Queue hardwares, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               requestsource:request source selection
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Saradc_Hal_TrigTimerBySoftware(SARADC_MODULE *const pSaradc, Saradc_RequestSource requestSource);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_EnableBrokenWireDiagnostics
 * Description:  Enable/disable broken wire diagnostics.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When operate different channle hardwares, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               channelID:channel ID.
 *               0:disable broken wire diagnostics.
 *               1:enable broken wire diagnostics.
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Saradc_Hal_EnableBrokenWireDiagnostics(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, boolean enable);

/**********************************************************************************************************************
 * Function:     Saradc_Hal_SetAlwaysGatingMode
 * Description:  Setting saradc gating mode is always gating mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When operate different Queue hardwares, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               requestSource:request source queue
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Saradc_Hal_SetAlwaysGatingMode(SARADC_MODULE *const pSaradc, Saradc_RequestSource requestSource);                             

/**********************************************************************************************************************
 * Function:     Saradc_Hal_SetDataReduction
 * Description:  Channel data reduction number config.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When operate different channel hardwares, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pSaradc: pointer to saradc module
 *               channelID: channel ID
 *               dataReductionMode: Set data reduction number
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/18    30037     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Saradc_Hal_SetDataReduction(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, Saradc_DataReductionMode dataReductionMode);
                                    
/**********************************************************************************************************************
 * Function:     Saradc_Hal_GetAnalogReadyFlg
 * Description:  Get whether SARADC analog part has been initialized.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pSaradc: pointer to saradc module
 * Inout:        None
 * Output:       None
 * Return:       boolean: 0:initialization not complete, 1:initialization complete
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/01/07    01368     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Saradc_Hal_GetAnalogReadyFlg(const SARADC_MODULE *const pSaradc);           

/**********************************************************************************************************************
 *                                       Global  Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Saradc_Hal_TriggerBySoftware(SARADC_MODULE *const pSaradc, Saradc_RequestSource requestSource)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_h_REF_4 */
    /* #Violation: saradc_hal_h_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif

    /* Software trigger queue */
    pSaradc->QMODE[requestSource].B.STRIGEN = 1U;
}

LOCAL_FORCEINLINE void Saradc_Hal_TrigTimerBySoftware(SARADC_MODULE *const pSaradc, Saradc_RequestSource requestSource)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_h_REF_4 */
    /* #Violation: saradc_hal_h_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Software trigger timer enable*/
    pSaradc->QREQTM[requestSource].B.STRITEN = 1U;
}


LOCAL_FORCEINLINE boolean Saradc_Hal_EnableBrokenWireDiagnostics(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, boolean enable)
{
    boolean retSts;
    retSts = TRUE;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_h_REF_4 */
    /* #Violation: saradc_hal_h_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Enable channel 0 BrokenWireDiagnostics */
    pSaradc->CHCTRL[channelID].B.BWDETEN = enable;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts,  pSaradc->CHCTRL[channelID].B.BWDETEN, enable);
    return retSts;
}

LOCAL_FORCEINLINE boolean Saradc_Hal_SetAlwaysGatingMode(SARADC_MODULE *const pSaradc, Saradc_RequestSource requestSource)
{
    /* #Violation: saradc_hal_h_REF_2 */
    SARADC_QMODE QMODE;
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_h_REF_4 */
    /* #Violation: saradc_hal_h_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    retSts = TRUE;
    QMODE.U = pSaradc->QMODE[requestSource].U;
    /* Set gating mode */
    QMODE.B.GATEEN = (uint32)1U;

    pSaradc->QMODE[requestSource].U = QMODE.U;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QMODE[requestSource].U, QMODE.U);
    return retSts;
}

LOCAL_FORCEINLINE boolean Saradc_Hal_SetDataReduction(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                                 Saradc_DataReductionMode dataReductionMode)
{
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_h_REF_4 */
    /* #Violation: saradc_hal_h_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif

    retSts = TRUE;
    /* Set data reduction mode */
    pSaradc->CHCTRL[channelID].B.DREDCTRL = (uint32)dataReductionMode;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.DREDCTRL, (uint32)dataReductionMode);
    return retSts;
}

LOCAL_FORCEINLINE boolean Saradc_Hal_GetAnalogReadyFlg(const SARADC_MODULE *const pSaradc)
{  
    /***********************************************************************************
     * Usage Restrictions
     * -THA6206 version C chip, this API can only accurately reflect the completion flag
     * of ADC analog IP initialization. If the ADC analog IP is disabled, the return value
     * of this API will not be reset to zero.
     * THA6412, THA6104 and THA6206 version D chip this API can accurately reflect the 
     * initialization status.  
    *************************************************************************************/
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_h_REF_4 */
    /* #Violation: saradc_hal_h_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Get whether SARADC analog part is ready */
    return ((boolean)pSaradc->ANACFG.B.ANAFLG);
}

#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"
#endif /* SARADC_HAL_H_*/


/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
