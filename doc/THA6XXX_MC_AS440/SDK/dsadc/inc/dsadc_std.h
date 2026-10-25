/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dsadc_std.h
 * Author:      30037
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all stander data type definitions and function declarations.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #dsadc_std_h_REF_1:MISRAC2012-Dir-4.8
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #dsadc_std_h_REF_2:CERTC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #dsadc_std_h_REF_3:MISRAC2012-Rule-2.5;;
* Justification:The macros are reserved for upper layers
*
* #dsadc_std_h_REF_4:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
#ifndef DSADC_STD_H_
#define DSADC_STD_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "dsadc_register.h"
#include "Platform_Types.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* calculation macro define */
#define LOG2_ROUNDUPLIMIT (2U)
 /* #Violation: dsadc_std_h_REF_3 */
#define MOVE15BIT (15U)
/* #Violation: dsadc_std_h_REF_3 */
#define MOVE14BIT (14U)
/* #Violation: dsadc_std_h_REF_3 */
#define UINT32LIMIT (0x7FFFFFFFU)
/* #Violation: dsadc_std_h_REF_3 */
#define UINT8LIMIT (0xFFU)

/* dsadc register mask define */
#define MODCFG_CHKMSK   (0x001F717FU)
#define DSADC1_MODCFG_INSMSK   (0xF0000000U)
#define DEMICFG_CHKMSK  (0x000028FFU)
#define TSCNT_CHKMSK    (0x000F0000U)
/* #Violation: dsadc_std_h_REF_3 */
#define GAINCTR_CHKMSK  (0x000701FFU)
#define MFCFG_CHKMSK    (0xFFDFFFFFU)
#define INTERCON_CHKMSK (0x000003FFU)
#define AFCFG_CHKMSK    (0x000F7F3FU)
#define INTEN_CHKMSK    (0x00000FFFU)
/* #Violation: dsadc_std_h_REF_3 */
#define RFCON_CHKMSK    (0x00000003U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* DSADC Input multiplexer trigger mode config. */
typedef enum
{
    DSADC_INPUTMULTIPLEXERTRIGGERMODE_SOFTWARE = 0U,    /* Software control */
    DSADC_INPUTMULTIPLEXERTRIGGERMODE_RISING,           /* Rising control */
    DSADC_INPUTMULTIPLEXERTRIGGERMODE_FALLING,          /* Falling control */
    DSADC_INPUTMULTIPLEXERTRIGGERMODE_BOTH,             /* Both control */
} Dsadc_InputMultiplexerTriggerMode;

/* Trigger source select */
typedef enum
{
    DSADC_TRIGGERSOURCE_A = 0U,                         /* Trigger source A */
    DSADC_TRIGGERSOURCE_B,                              /* Trigger source B */
    DSADC_TRIGGERSOURCE_C,                              /* Trigger source C */
    DSADC_TRIGGERSOURCE_D,                              /* Trigger source D */
    DSADC_TRIGGERSOURCE_E,                              /* Trigger source E */
    DSADC_TRIGGERSOURCE_F,                              /* Trigger source F */
    DSADC_TRIGGERSOURCE_G,                              /* Trigger source G */
    DSADC_TRIGGERSOURCE_H,                              /* Trigger source H */            
    DSADC_TRIGGERSOURCE_I,                              /* Trigger source I */    
    DSADC_TRIGGERSOURCE_J,                              /* Trigger source J */
    DSADC_TRIGGERSOURCE_K,                              /* Trigger source K */        
    DSADC_TRIGGERSOURCE_L,                              /* Trigger source L */    
    DSADC_TRIGGERSOURCE_M,                              /* Trigger source M */
    DSADC_TRIGGERSOURCE_N,                              /* Trigger source N */        
    DSADC_TRIGGERSOURCE_O,                              /* Trigger source O */
    DSADC_TRIGGERSOURCE_P,                              /* Trigger source P */
} Dsadc_TriggerSource;

/* Dsadc Time-stamp trigger mode select. */
typedef enum
{   
    DSADC_TIMESTAMPTRIGGERMODE_NONE = 0U,               /* No Time-Stamp trigger */
    DSADC_TIMESTAMPTRIGGERMODE_RISING,                  /* Rising trigger */
    DSADC_TIMESTAMPTRIGGERMODE_FALLING,                 /* Falling trigger */
    DSADC_TIMESTAMPTRIGGERMODE_BOTH,                    /* Both trigger */
} Dsadc_TimeStampTriggerMode;

/* Dsadc CIC parallel select. */
typedef enum
{
    DSADC_CICPARALLELSELECTION_1 = 0U,                  /* CIC1 */
    DSADC_CICPARALLELSELECTION_2,                       /* CIC2 */
    DSADC_CICPARALLELSELECTION_3,                       /* CIC3 */
    DSADC_CICPARALLELSELECTION_4,                       /* CIC4 */                    
} Dsadc_CicParallelSelection;

/* Dsadc service request generate mode config. */
/*************************************************************************************************
 * Usage Note for Dsadc_ServiceRequest
 * There are differences in the functionality of enumeration Dsadc_ServiceRequest 
 * between the THA6206 version C and the THA6206 version D, as follows:
 * 1) DSADC_SERVICEREQUEST_HIGH function description
 *    - [SAME] DSADC_SERVICEREQUEST_HIGH common function is that the service request(for interrupt 
 *      or DMA) are triggered by the high-level trigger signal, timestamp, or main /auxiliary 
 *      channel result exceeding the upper/lower limit while user defined THA6_THA6206, 
 *      THA6_THA6206D and THA6_THA6412.
 *    - [DIFF] The chip not only supports the above DSADC_SERVICEREQUEST_HIGH common functions, 
 *      but also supports a new function: the service request can be triggered when the data exceeds 
 *      watermark value and the trigger signal is at a high level while defined THA6_THA6206D.
 * 
 * 2) DSADC_SERVICEREQUEST_LOW function description
 *    - [SAME] DSADC_SERVICEREQUEST_LOW common function is that the service request(for interrupt 
 *      or DMA) are triggered by the low-level trigger signal, timestamp, or main channel result 
 *      exceeding the upper/lower limit while user defined THA6_THA6206, THA6_THA6206D and THA6_THA6412.
 *    - [DIFF] The chip not only supports the above DSADC_SERVICEREQUEST_LOW common functions, 
 *      but also supports a new function: the service request can be triggered when the data exceeds 
 *      watermark value and the trigger signal is at a low level while defined THA6_THA6206D.
 * 
 * 
 * Additional note: 
 * DSADC_SERVICEREQUEST_NONE and DSADC_SERVICEREQUEST_FIFOTHRESHOLD function is same while 
 * user defined THA6_THA6206, THA6_THA6206D and THA6_THA6412. And DSADC_SERVICEREQUEST_FIFOTHRESHOLD 
 * function is that The service request are triggered by timestamp, main /auxiliary channel result 
 * exceeding the upper /lower limit, or result exceeding the watermark value. 
 *************************************************************************************************/
typedef enum
{
    DSADC_SERVICEREQUEST_NONE = 0U,                     /* No service request */
    DSADC_SERVICEREQUEST_HIGH,                          /* Refer to 1) DSADC_SERVICEREQUEST_HIGH function description */
    DSADC_SERVICEREQUEST_LOW,                           /* Refer to 2) DSADC_SERVICEREQUEST_LOW function description */    
    DSADC_SERVICEREQUEST_FIFOTHRESHOLD,                 /* Refer to Additional note */
} Dsadc_ServiceRequest;

/* Set dsadc main channel alarm condition. */
typedef enum
{
    DSADC_ALARMCONDITION_NEWRESULT = 0U,                /* New result generates alarm */
    DSADC_ALARMCONDITION_RESULTINRANGE,                 /* New result in range generates alarm */
    DSADC_ALARMCONDITION_RESULTOUTRANGE,                /* New result out range generates alarm */
} Dsadc_MainAlarmCondition;

/* Dsadc fir offset config. */
typedef enum
{
    DSADC_FILTEROUTPUTSHIFT_0 = 0U,                     /* Output shift 0 */
    DSADC_FILTEROUTPUTSHIFT_1,                          /* Output shift 1 */
    DSADC_FILTEROUTPUTSHIFT_2,                          /* Output shift 2 */
    DSADC_FILTEROUTPUTSHIFT_3,                          /* Output shift 3 */
} Dsadc_FirOffset;

/* Dsadc filter offset compensation config. */
typedef enum
{
    DSADC_FILTEROFFSETCOMPENSATION_0 = 0,               /* Offset compensation filter disable */
    DSADC_FILTEROFFSETCOMPENSATION_1,                   /* Offset compensation filter 1 */
    DSADC_FILTEROFFSETCOMPENSATION_2,                   /* Offset compensation filter 2 */
    DSADC_FILTEROFFSETCOMPENSATION_3,                   /* Offset compensation filter 3 */
    DSADC_FILTEROFFSETCOMPENSATION_4,                   /* Offset compensation filter 4 */
    DSADC_FILTEROFFSETCOMPENSATION_5,                   /* Offset compensation filter 5 */
    DSADC_FILTEROFFSETCOMPENSATION_6,                   /* Offset compensation filter 6 */
    DSADC_FILTEROFFSETCOMPENSATION_7,                   /* Offset compensation filter 7 */
} Dsadc_FilterOffsetCompensation;

/* Dsadc wave mode config. */
typedef enum
{
    DSADC_WAVESELECT_NONE = 0U,                         /* No wave */
    DSADC_WAVESELECT_SINE,                              /* Sin wave */
    DSADC_WAVESELECT_TRIANGULAR,                        /* Triangular wave */
    DSADC_WAVESELECT_SQUARE,                            /* Square wave */
} Dsadc_WaveMode;

/* Dsadc fifo threshold config. */
typedef enum
{
    DSADC_FIFOTHRESHOLD_1 = 0U,                         /* Fifo threshold is 1 */
    DSADC_FIFOTHRESHOLD_2,                              /* Fifo threshold is 2 */
    DSADC_FIFOTHRESHOLD_3,                              /* Fifo threshold is 3 */
    DSADC_FIFOTHRESHOLD_4,                              /* Fifo threshold is 4 */
} Dsadc_FifoThreshold;

/* Software control */
typedef enum
{
    DSADC_PGAGAIN_0DB = 0,                              /* PGA gain: 0 */
    DSADC_PGAGAIN_6DB,                                  /* PGA gain: 6 */
    DSADC_PGAGAIN_12DB,                                 /* PGA gain: 12 */
} Dsadc_PgaGain;

/* Software control */
typedef enum
{
    DSADC_TIMESTAMPCLOCKDIVIDER_1 = 0,                  /* Time stamp clock divider: 0 */
    DSADC_TIMESTAMPCLOCKDIVIDER_2,                      /* Time stamp clock divider: 1 */
    DSADC_TIMESTAMPCLOCKDIVIDER_4,                      /* Time stamp clock divider: 2 */
    DSADC_TIMESTAMPCLOCKDIVIDER_8 ,                     /* Time stamp clock divider: 3 */
} Dsadc_TimeStampClockDivider;

/* Mean shift length config */
typedef enum
{
    DSADC_MEANSHIFTLENGTH_2 = 0,                        /* 2 point mean calculation. */
    DSADC_MEANSHIFTLENGTH_4,                            /* 4 point mean calculation. */
    DSADC_MEANSHIFTLENGTH_8,                            /* 8 point mean calculation. */
    DSADC_MEANSHIFTLENGTH_16,                           /* 16 point mean calculation. */
    DSADC_MEANSHIFTLENGTH_32,                           /* 32 point mean calculation. */
    DSADC_MEANSHIFTLENGTH_64,                           /* 64 point mean calculation. */
} Dsadc_MeanShiftLength;
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Dsadc modualtor configuration */
/* #Violation: dsadc_std_h_REF_1 */
/* #Violation: dsadc_std_h_REF_2 */
typedef struct
{
    boolean positiveInputEnable;                    /* 0: Positive input disable 1: Positive input enable */
    boolean negativeInputEnable;                    /* 0: Negaitive input disable 1: Negative input enable */
    boolean positiveInputLine;                      /* 0: Select VREFX 1: Select input port */
    boolean negativeInputLine;                      /* 0: Select VREFX 1: Select input port */
    boolean inputPin;                               /* 0: Input B 1: Input A */
    boolean inputMultiplexerMode;                   /* 0: Prepattern mode 1: Single mode */
    boolean autoPowerControl;                       /* 0: Work after setting 1: Work after setting and triggering */
    Dsadc_PgaGain pgaGain;                          /* Pga gain select */
    Dsadc_InputMultiplexerTriggerMode inputMultiplexerTriggerMode;  /* Set input multiplexer trigger mode */
} Dsadc_ModulatorConfig;

/* Dsadc demodulator configuration */
/* #Violation: dsadc_std_h_REF_1 */
/* #Violation: dsadc_std_h_REF_2 */
typedef struct
{
    boolean resultDisplayMode;                      /* 0:Signed. Note: The struct member can only be configured as 0. */
    Dsadc_TriggerSource triggerSource;              /* Set DSADC trigger source */
} Dsadc_DemodulatorConfig;

/* Dsadc timestamp configuration */
/* #Violation: dsadc_std_h_REF_1 */
/* #Violation: dsadc_std_h_REF_2 */
typedef struct
{
    boolean start;                                  /* 0:Time-stamp stop 1:Time-stamp start */
    boolean multiplexerCopyEnable;                  /* 0:Not copy 1:Multiplexer sector copy enable */
    uint8 timeStampFrequency;                       /* Time-stamp frequency config */
    Dsadc_TimeStampClockDivider divider;            /* Time-stamp divider */
    Dsadc_TimeStampTriggerMode mode;                /* Set Time-stamp trigger mode. */
} Dsadc_TimeStampConfig;

/* Dsadc mean configuration */
/* #Violation: dsadc_std_h_REF_1 */
/* #Violation: dsadc_std_h_REF_2 */
typedef struct
{
    boolean meanMode;                               /* 0:Fixed single carrier mode 1:Mean points can be matched  */
    uint8 meanPoint;                                /* Mean point config */
    Dsadc_MeanShiftLength shiftLength;              /* Set mean shift length */
} Dsadc_MeanConfig;

/* Dsadc result threshold */
/* #Violation: dsadc_std_h_REF_1 */
/* #Violation: dsadc_std_h_REF_2 */
typedef struct
{
    uint16 thresholdLower;                          /* Set threshold lower limit */
    uint16 thresholdUpper;                          /* Set threshold upper limit */
} Dsadc_ThresholdConfig;

/* Dsadc main filter configuration */
/* #Violation: dsadc_std_h_REF_1 */
/* #Violation: dsadc_std_h_REF_2 */
typedef struct
{
    boolean cicFilterEnable;                        /* 0: Main channel CIC filter bypass 1:Main channel CIC filter enable */
    boolean decimationRate0;                        /* 0: FIR0 decimation rate is 2 1: FIR0 decimation rate is 1 */
    boolean decimationRate1;                        /* 0: FIR1 decimation rate is 2 1: FIR1 decimation rate is 1 */
    boolean fir0Enable;                             /* 0: FIR0 bypass 1: FIR0 enable */
    boolean fir1Enable;                             /* 0: FIR1 bypass 1: FIR1 enable */
    boolean firOffset0;                             /* 0: Output shift 0 1: Output shift 1 */
    uint8 cicFilterSampling;                        /* 0: Set Main channel CIC filter sampling factor */
    Dsadc_CicParallelSelection parallel;            /* Set Main channel CIC filter parallel */
    Dsadc_ServiceRequest request;                   /* Main channel service request config */
    Dsadc_MainAlarmCondition condition;             /* Set main channel alarm generation condition */
    Dsadc_FirOffset firOffset1;                     /* Set fir1 output shift */
    Dsadc_FilterOffsetCompensation offsetCompensation;  /* Set filter offset compensation */
} Dsadc_MainFilterConfig;

/* Dsadc auxiliary filter configuration */
/* #Violation: dsadc_std_h_REF_1 */
/* #Violation: dsadc_std_h_REF_2 */
typedef struct
{
    boolean request;                                /* 0: No Auxiliary channel service request 1: Generate Auxiliary channel service request */
    boolean cicFilterEnable;                        /* 0: Disable 1: Enable */
    uint8 auxiliaryCicFilterSampling;               /* Set Auxiliary channel CIC filter sampling factor */
    Dsadc_CicParallelSelection parallel;            /* Set Auxiliary channel CIC filter parallel */
} Dsadc_AuxiliaryFilterConfig;

/* Dsadc FIFO configuration */
/* #Violation: dsadc_std_h_REF_1 */
/* #Violation: dsadc_std_h_REF_2 */
typedef struct
{
    Dsadc_FifoThreshold fifoThreshold;              /* Set fifo threshold  */
} Dsadc_FifoConfig;
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dsadc_std_h_REF_4 */
#include "Dsadc_MemMap.h"
/**********************************************************************************************************************
 * Function:     Dsadc_Register_ReadBack_Check
 * Description:  Check register readback values
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        state: initial state
 *               expect: Desired value
 *               value: readback value
 * Inout:        None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Dsadc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define DSADC_REG_CHECK
#if defined(DSADC_REG_CHECK)
LOCAL_FORCEINLINE boolean Dsadc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Dsadc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     void Dsadc_Std_ConfigModulator
 * Description:  Config modulator function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig: pointer to modulator configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Std_ConfigModulator(DSADC_MODULE *const pDsadc, const Dsadc_ModulatorConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Void Dsadc_Std_ConfigDemodulator
 * Description:  Config demodulator function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig: pointer to demodulator configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Std_ConfigDemodulator(DSADC_MODULE *const pDsadc, const Dsadc_DemodulatorConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Void Dsadc_Std_ConfigTimeStamp
 * Description:  Config time-stamp function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig: pointer to time-stamp configuration structure
 * Inout:        None
 * Output:       Rcc_ErrorFlag:RCC error flag
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Std_ConfigTimeStamp(DSADC_MODULE *const pDsadc, const Dsadc_TimeStampConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Void Dsadc_Hal_ConfigMean
 * Description:  Config mean function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig: pointer to mean configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Std_ConfigMean(DSADC_MODULE *const pDsadc, const Dsadc_MeanConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     void Dsadc_Std_ConfigThreshold
 * Description:  Config threshold function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig: pointer to dsadc threshold configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Std_ConfigThreshold(DSADC_MODULE *const pDsadc, const Dsadc_ThresholdConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Void Dsadc_Std_ConfigMainFilter
 * Description:  Config main filter function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig: pointer to Main Filter configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Std_ConfigMainFilter(DSADC_MODULE *const pDsadc, const Dsadc_MainFilterConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Void Dsadc_Std_ConfigAuxFilter
 * Description:  Config Auxiliary filter function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig: pointer to Auxiliary Filter configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Std_ConfigAuxFilter(DSADC_MODULE *const pDsadc, const Dsadc_AuxiliaryFilterConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Void Dsadc_Std_ConfigFifo
 * Description:  Config FIFO function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDsadc:pointer to dsadc module 
 *               pConfig: pointer to FIFO configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *********************************************************************************************************************/
extern boolean Dsadc_Std_ConfigFifo(DSADC_MODULE *const pDsadc, const Dsadc_FifoConfig *const pConfig);

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dsadc_std_h_REF_4 */
#include "Dsadc_MemMap.h"

#endif /* EXTI_STD_H_ */
