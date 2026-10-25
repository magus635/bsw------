/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    rdc_std.h
 * Author:      00915
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #rdc_std_h_REF_1:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*
* #rdc_std_h_REF_2:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #rdc_std_h_REF_3:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be represents as uint8.
*
* #rdc_std_h_REF_4:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
* #rdc_std_h_REF_5:MISRAC2012-Dir-4.8;
* Justification:Apply such struct/union definitions to simplify the code structure and reduce the code
*               complexity.
*
* #rdc_std_h_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
#ifndef RDC_STD_H_
#define RDC_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "rdc_register.h"
#include "Platform_Types.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
#define RDC_MAX_EXCITATION_CARRIER_POINTS (20U)
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/* Excitation carrier position information structure */
typedef struct
{
    uint16 pos_position; /* Excitation carrier rising edge position */
    uint16 neg_position; /* Excitation carrier falling edge position */
} Rdc_CarrierPosition;

/* Excitation carrier configuration structure */
/* #Violation: rdc_std_h_REF_5 */
typedef struct
{
    Rdc_CarrierPosition position[20]; /* Excitation carrier position information */
    uint16 carrier_points;            /* How many triangular waves to describe a sine wave */
    uint16 total_points;              /* Total Count Points, total_points  must be equal to 20
                                         times carrier_points */
} Rdc_CarrierPoints;

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Excitation carrier output config */
typedef enum
{
    RDC_WAVEMODECONFIG_SPWM = 0U, /* SPWM mode  */
    RDC_WAVEMODECONFIG_PWM        /* PWM mode  */
} Rdc_WaveModeConfig;

/* Excitation carrier output mode */
typedef enum
{
    RDC_EXCITATIONCARRIERMODE_HARDWARE = 0U, /* The hardware sets the excitation carrier  */
    RDC_EXCITATIONCARRIERMODE_SOFTWARE       /* The software sets the excitation carrier  */
} Rdc_ExcitationCarrierMode;

/* Excitation carrier frequency */
typedef enum
{
    RDC_EXCITATIONCARRIERFREQ_2K = 1U, /* The excitation carrier frequency is 2K */
    RDC_EXCITATIONCARRIERFREQ_4K,      /* The excitation carrier frequency is 4K  */
    RDC_EXCITATIONCARRIERFREQ_8K,      /* The excitation carrier frequency is 8K  */
    RDC_EXCITATIONCARRIERFREQ_10K,     /* The excitation carrier frequency is 10K  */
    RDC_EXCITATIONCARRIERFREQ_20K      /* The excitation carrier frequency is 20K  */
} Rdc_ExcitationCarrierFreq;

/* Excitation carrier enable/disable */
typedef enum
{
    RDC_EXCITATIONCARRIEREN_DISABLE = 0U, /* Function is disabled */
    RDC_EXCITATIONCARRIEREN_ENABLE        /* Function is enabled */
} Rdc_ExcitationCarrierEn;

/* Data source is DSADC/SARADC */
typedef enum
{
    RDC_DATASOURCE_DSADC_0_4 = 0U,          /* The data source is DSADC0 in RDC0,DSADC4 in RDC1 */
    RDC_DATASOURCE_DSADC_1_5,               /* The data source is DSADC1 in RDC0,DSADC5 in RDC1*/
    RDC_DATASOURCE_DSADC_2_6,               /* The data source is DSADC2 in RDC0,DSADC6 in RDC1*/
    RDC_DATASOURCE_DSADC_3_7,               /* The data source is DSADC3 in RDC0,DSADC7 in RDC1*/
    RDC_DATASOURCE_SARADC_8_10 = 8,         /* The data source is SARADC8 in RDC0,SARADC10 in RDC1*/
    RDC_DATASOURCE_SARADC_9_11,             /* The data source is SARADC9 in RDC0,SARADC11 in RDC1*/
} Rdc_DataSource;

/* RDC data processing source selection */
typedef enum
{
    Rdc_DataProcessingSource_Q = 0U,     /* Input source is I-channel */
    Rdc_DataProcessingSource_I           /* Input source is Q-channel */
/* #Violation: rdc_std_h_REF_1 */
} Rdc_DataProcessingSource;

/* RDC SARADC data symbol conversion enable/bypass control*/
typedef enum
{
    Rdc_SaradcDataSymbolConversion_EN = 0U,         /* EN */
    Rdc_SaradcDataSymbolConversion_BYPASS           /* BYPASS */
/* #Violation: rdc_std_h_REF_1 */
} Rdc_SaradcDataSymbolConversion;

/* Trigger source is GTM/CPU */
typedef enum
{
    RDC_TRIGGERSOURCE_GTM = 0U, /* Input signal GTM  */
    RDC_TRIGGERSOURCE_CPU       /* Input signal CPU  */
} Rdc_TriggerSource;

/* signal type */
typedef enum
{
    RDC_SIGTYPE_MIX = 0U, /* Input signal type: mixed signal */
#if defined(THA6_THA6412)
    RDC_SIGTYPE_BASEBAND  /* Input signal type: baseband signal */
#endif
} Rdc_SigType;

/* Compensation function enable/disable */
typedef enum
{
    RDC_COMPENSATIONEN_ENABLE = 0U, /* Function is enabled */
    RDC_COMPENSATIONEN_DISABLE      /* Function is disabled */
} Rdc_CompensationEn;

/* Filter cutoff frequency */
typedef enum
{
    RDC_FILTERCUTOFFFREQUENCY_DISABLE = 0U, /* Function is disabled */
    RDC_FILTERCUTOFFFREQUENCY_1,            /* The filter cutoff frequency is 1*10^-5*fd */
    RDC_FILTERCUTOFFFREQUENCY_2,            /* The filter cutoff frequency is 4*10^-5*fd */
    RDC_FILTERCUTOFFFREQUENCY_3,            /* The filter cutoff frequency is 16*10^-5*fd */
    RDC_FILTERCUTOFFFREQUENCY_4,            /* The filter cutoff frequency is 62*10^-5*fd */
    RDC_FILTERCUTOFFFREQUENCY_5,            /* The filter cutoff frequency is 25*10^-4*fd */
    RDC_FILTERCUTOFFFREQUENCY_6,            /* The filter cutoff frequency is 1*10^-2*fd */
    RDC_FILTERCUTOFFFREQUENCY_7             /* The filter cutoff frequency is 4*10^-2*fd */
} Rdc_FilterCutoffFrequency;

/* Sampling rate configuration */
typedef enum
{
    RDC_SAMPLINGRATECONFIG_RESERVED = 0U,   /* Function is disabled */
    RDC_SAMPLINGRATECONFIG_8,               /* 8 excitation sampling rate */
    RDC_SAMPLINGRATECONFIG_16,              /* 16 excitation sampling rate */
    RDC_SAMPLINGRATECONFIG_32,              /* 32 excitation sampling rate */
} Rdc_SamplingRateConfig;

/* Carrier recovery selection */
typedef enum
{
    Rdc_CARRIERRECOVERSOURCE_Q = 0U,  /* Carrier recovery selection Q-channel data  */
    Rdc_CARRIERRECOVERSOURCE_I        /* Carrier recovery selection I-channel data  */
} Rdc_CarrierRecoverSource;


/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/

#define RDC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rdc_std_h_REF_5 */
#include "Rdc_MemMap.h"

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetWaveMode
 * Description:  Set excitation carrier mode is PWM or SPWM
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        waveMode: Excitation carrier output mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SetWaveMode(Rdc_WaveModeConfig waveMode);

/**********************************************************************************************************************
 * Function:     Rdc_Std_ExcitationCarrierMode
 * Description:  Set excitation carrier mode is hardware or software
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        mode: Excitation carrier output mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_ExcitationCarrierMode(Rdc_ExcitationCarrierMode mode);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetExcitationCarrierFreq
 * Description:  Set excitation carrier frequency, only valid in hardware mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        freq: Excitation carrier frequency
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SetExcitationCarrierFreq(Rdc_ExcitationCarrierFreq freq);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetExcitationCarrierEn
 * Description:  Excitation carrier output enable/disable control
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        en: Excitation carrier enable or disable
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SetExcitationCarrierEn(Rdc_ExcitationCarrierEn en);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetDataSource
 * Description:  Set the RDC data source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               i_source: i-channel RDC data source
 *               q_source: q-channel RDC data source
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SetDataSource(RDC_MODULE *pRdc, Rdc_DataSource i_source,Rdc_DataSource q_source);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetSamplingRate
 * Description:  Set the RDC sampling rate
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               samplingRate: The RDC sampling rate
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/13    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SetSamplingRate(RDC_MODULE *pRdc, Rdc_SamplingRateConfig samplingRate);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetTriggerSource
 * Description:  Set the RDC trigger source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               source: RDC trigger source
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SetTriggerSource(RDC_MODULE *pRdc, Rdc_TriggerSource source);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetCarrierRecoverSource
 * Description:  Set carrier recovery data source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               source: RDC carrier recovery data source
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/24    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SetCarrierRecoverSource(RDC_MODULE *pRdc, Rdc_CarrierRecoverSource source);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SelSignalType
 * Description:  Set the RDC input signal type
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               sigType: RDC input signal type
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/01/08    00976      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SelSignalType(RDC_MODULE *pRdc, Rdc_SigType sigType);

/**********************************************************************************************************************
 * Function:     Rdc_Register_ReadBack_Check
 * Description:  Check register readback values
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        state: initial state
 *               expect: Desired value
 *               value: readback value
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Std_SetWaveMode(Rdc_WaveModeConfig waveMode)
{
    boolean ret = 1U;
    /* SPWM mode or PWM mode*/
    /* #Violation: rdc_std_h_REF_2 */
    RDC0->CWCFG.B.WAVEMODE = (uint32)waveMode;
    /* #Violation: rdc_std_h_REF_2 */
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)waveMode, RDC0->CWCFG.B.WAVEMODE);

    return ret;
}

LOCAL_FORCEINLINE boolean Rdc_Std_ExcitationCarrierMode(Rdc_ExcitationCarrierMode mode)
{
    boolean ret = 1U;
    /* Hardware mode or Software mode*/
    /* #Violation: rdc_std_h_REF_2 */
    RDC0->CWCFG.B.SOFTCFGEN = (uint32)mode;
    /* #Violation: rdc_std_h_REF_2 */
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)mode, RDC0->CWCFG.B.SOFTCFGEN);

    return ret;
}

LOCAL_FORCEINLINE boolean Rdc_Std_SetExcitationCarrierFreq(Rdc_ExcitationCarrierFreq freq)
{
    boolean ret = 1U;
    /* Set excitation carrier frequency, only valid in hardware mode */
    /* #Violation: rdc_std_h_REF_2 */
    RDC0->CWCFG.B.STEPCFG = (uint32)freq;
    /* #Violation: rdc_std_h_REF_2 */
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)freq, RDC0->CWCFG.B.STEPCFG);

    return ret;
}

LOCAL_FORCEINLINE boolean Rdc_Std_SetExcitationCarrierEn(Rdc_ExcitationCarrierEn en)
{
    boolean ret = 1U;
    /* Excitation carrier output enable/disable control */
    /* #Violation: rdc_std_h_REF_2 */
    RDC0->CWCTRL.B.EXCRUN = (uint32)en;
    /* #Violation: rdc_std_h_REF_2 */
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)en, RDC0->CWCTRL.B.EXCRUN);

    return ret;
}

LOCAL_FORCEINLINE boolean Rdc_Std_SetDataSource(RDC_MODULE *pRdc, Rdc_DataSource i_source,Rdc_DataSource q_source)
{
    boolean ret = 1U;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_std_h_REF_2 */
    /* #Violation: rdc_std_h_REF_4 */
    Assert(((boolean)(CHECK_RDC_BASE(pRdc))));
#endif /* INPUT_ARG_DETECT */
    /* Set the RDC data source */
    pRdc->RECFG.B.IDATASEL = (uint32)i_source;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)i_source, pRdc->RECFG.B.IDATASEL);
    pRdc->RECFG.B.QDATASEL = (uint32)q_source;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)q_source, pRdc->RECFG.B.QDATASEL);

    if((i_source == RDC_DATASOURCE_SARADC_8_10) || (i_source == RDC_DATASOURCE_SARADC_9_11)
    || (q_source == RDC_DATASOURCE_SARADC_8_10) || (q_source == RDC_DATASOURCE_SARADC_9_11))
    {
        /* #Violation: rdc_std_h_REF_2 */
        RDC0->CWCFG.B.REQENFLAG = 1U;
        /* #Violation: rdc_std_h_REF_2 */
        ret = Rdc_Register_ReadBack_Check(ret, 1U, RDC0->CWCFG.B.REQENFLAG);
    }

    return ret;
}


LOCAL_FORCEINLINE boolean Rdc_Std_SetSamplingRate(RDC_MODULE *pRdc, Rdc_SamplingRateConfig samplingRate)
{
    boolean ret = 1U;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_std_h_REF_2 */
    /* #Violation: rdc_std_h_REF_4 */
    Assert(((boolean)(CHECK_RDC_BASE(pRdc))));
    /* Check if the samplingRate is invalid configuration*/
    /* #Violation: rdc_std_h_REF_3 */
    Assert((boolean)(RDC_SAMPLINGRATECONFIG_RESERVED != samplingRate));
#endif /* INPUT_ARG_DETECT */
    /* Set the RDC data source */
    pRdc->RECFG.B.SAMPCFG = (uint32)samplingRate;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)samplingRate, pRdc->RECFG.B.SAMPCFG);

    return ret;
}

LOCAL_FORCEINLINE boolean Rdc_Std_SetTriggerSource(RDC_MODULE *pRdc, Rdc_TriggerSource source)
{
    boolean ret = 1U;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_std_h_REF_2 */
    /* #Violation: rdc_std_h_REF_4 */
    Assert(((boolean)(CHECK_RDC_BASE(pRdc))));
#endif /* INPUT_ARG_DETECT */
    /* RDC trigger source is GTM/CPU */
    pRdc->RECFG.B.TRISEL = (uint32)source;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)source, pRdc->RECFG.B.TRISEL);

    return ret;
}

LOCAL_FORCEINLINE boolean Rdc_Std_SetCarrierRecoverSource(RDC_MODULE *pRdc, Rdc_CarrierRecoverSource source)
{
    boolean ret = 1U;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_std_h_REF_2 */
    /* #Violation: rdc_std_h_REF_4 */
    Assert(((boolean)(CHECK_RDC_BASE(pRdc))));
#endif /* INPUT_ARG_DETECT */
    pRdc->RECFG.B.VLDSEL = (uint32)source;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)source, pRdc->RECFG.B.VLDSEL);

    return ret;
}

LOCAL_FORCEINLINE boolean Rdc_Std_SelSignalType(RDC_MODULE *pRdc, Rdc_SigType sigType)
{
    boolean ret = 1U;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_std_h_REF_3 */
    Assert((boolean)(NULL_PTR != pRdc));
#endif /* INPUT_ARG_DETECT */
    pRdc->RECFG.B.SIGSEL = (uint32)sigType;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)sigType, pRdc->RECFG.B.SIGSEL);

    return ret;
}

#define RDC_REG_CHECK
#if defined(RDC_REG_CHECK)
LOCAL_FORCEINLINE boolean Rdc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
LOCAL_FORCEINLINE boolean Rdc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
 * Function:     Rdc_Std_SetSoftExcitationCarrierDuty
 * Description:  Set the excitation carrier period and duty cycle information
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        points: Period and duty cycle information
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern boolean Rdc_Std_SetSoftExcitationCarrierDuty(const Rdc_CarrierPoints *const points);


/**********************************************************************************************************************
 * Function:     Rdc_Std_SetDpllPidConfig
 * Description:  Set the digital phase-locked loop PID parameters
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               kpData: Digital phase-locked loop KP parameters,the value range of KP is 0~1.0
 *               kiData: Digital phase-locked loop KI parameters,the value range of KI is 0~1.0
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern boolean Rdc_Std_SetDpllPidConfig(RDC_MODULE *const pRdc, float32 kpData, float32 kiData);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetMainPidConfig
 * Description:  Set the main loop PID parameters
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               kpData: Main loop KP parameters,the value range of KP is 0~1.0
 *               kiData: Main loop KI parameters,the value range of KI is 0~1.0
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern boolean Rdc_Std_SetMainPidConfig(RDC_MODULE *const pRdc, float32 kpData, float32 kiData);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetDcCompensation
 * Description:  Set the RDC DC compensation parameters
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               enable: DC compensation enable/disable configuration
 *               iOffset: I-channel DC compensation value
 *               qOffset: Q-channel DC compensation value
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern boolean Rdc_Std_SetDcCompensation(RDC_MODULE *const pRdc, Rdc_CompensationEn enable, sint16 iOffset,
                                      sint16 qOffset);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetGainCompensation
 * Description:  Set the RDC gain compensation parameters
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               enable: Gain compensation enable/disable configuration
 *               gain: RDC gain compensation value,the value range of gainOffset is 0~2.0
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern boolean Rdc_Std_SetGainCompensation(RDC_MODULE *const pRdc, Rdc_CompensationEn enable, float32 gain);

/**********************************************************************************************************************
 * Function:     Rdc_Std_SetHighPassCompensation
 * Description:  Set the RDC High-pass filter parameters
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               enable: High-pass filter enable/disable configuration
 *               freqLevel: High-pass filter parameters
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern boolean Rdc_Std_SetHighPassCompensation(RDC_MODULE *const pRdc, Rdc_CompensationEn enable,
                                            Rdc_FilterCutoffFrequency freqLevel);

#define RDC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rdc_std_h_REF_5 */
#include "Rdc_MemMap.h"

#endif /* RDC_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
