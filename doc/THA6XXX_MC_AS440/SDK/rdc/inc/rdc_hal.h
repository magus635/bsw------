/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    rdc_hal.h
 * Author:      00915
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #rdc_hal_h_REF_1:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core, Boolean can only be represents as uint8.
*
* #rdc_hal_h_REF_2:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #rdc_hal_h_REF_3:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
* #rdc_hal_h_REF_4:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
#ifndef RDC_HAL_H_
#define RDC_HAL_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "rcc_hal.h"
#include "Platform_Types.h"
#include "rdc_register.h"
#include "rdc_std.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Extreme value select*/
typedef enum
{
    RDC_ExtremeValueSelect_MAX = 0U,    /* Max extreme value */
    RDC_ExtremeValueSelect_MIN          /* Min extreme value  */
} Rdc_ExtremeValueSelect;

/* RDC deinit selection */
typedef enum
{
    RDC_IdxSel_0 = 0U,    /* RDC0 */
#if defined(THA6_THA6412)
    RDC_IdxSel_1 = 1U,    /* RDC1(THA6412 support only) */
    RDC_IdxSel_All,       /* RDC0 and RDC1(THA6412 support only) */
#endif
} Rdc_IdxSel;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Group configuration structure */
typedef struct
{
    Rdc_SigType signalType;                          /* signal type: mix signal or baseband signal(THA6412 support only) */
    Rdc_ExcitationCarrierMode excitationCarrierMode; /* Excitation carrier out mode is soft or hardware.
                                                        In software mode, only SPWM mode is supported,
                                                        and the user needs to calculate the starting and
                                                        ending points of the carrier. In hardware mode,
                                                        PWM and SPWM modes are supported, and the
                                                        excitation frequency only supports 2kHz, 4kHz,
                                                        8kHz, 10kHz, and 20kHz */
    Rdc_WaveModeConfig waveMode;                     /* Excitation carrier out mode is Pwm or Spwm */
    Rdc_ExcitationCarrierFreq excitationCarrierFreq; /* The excitation carrier out frequency */
    Rdc_ExcitationCarrierEn excitationCarrierEn;     /* The excitation carrier out en */
    Rdc_DataSource i_dataSource;                     /* The data source is DSADC or SARADC */
    Rdc_DataSource q_dataSource;                     /* The data source is DSADC or SARADC */
    Rdc_TriggerSource triggerSource;                 /* Set the rdc trigger source is GTM or CPU*/
    Rdc_CompensationEn dcCompensationEn;             /* Set dc compensation On Or Off */
    sint16 dcOffsetI;                                /* Set The I-channel DC compensation value */
    sint16 dcOffsetQ;                                /* Set The Q-channel DC compensation value */
    Rdc_CompensationEn gainCompensationEn;           /* Set Gain compensation On Or Off */
    float32 gainOffset;                              /* Set The I-channel gain compensation value,
                                                        the value range of gainOffset is 0~2.0 */
    Rdc_CompensationEn highPassCompensationEn;       /* Set high-pass compensation On Or Off */
    Rdc_FilterCutoffFrequency filterCutoffFrequency; /* Set The high-pass compensation value */
    Rdc_SamplingRateConfig samplingRate;             /* Set sampling rate */
    Rdc_CarrierRecoverSource carrierRecoverSource;   /* Set carrier recovery data source */
#if defined(THA6_THA6412)
    boolean isEnableRefPhase;                        /* enable reference phase function (THA6412 support only) */
    sint32 refPhase;                                 /* reference phase with format s1.16 -pi ~ pi (THA6412 support only) */
#endif
    Rdc_CarrierPoints *points;                       /* Excitation carrier duty and cycle configuration */
    float32 dpllKp;                                  /* Solve the loop carrier recovery loop KP
                                                        Configuration, the value range of KP is 0~1.0 */
    float32 dpllKi;                                  /* Solve the loop carrier recovery loop KI
                                                        configuration, the value range of KI is 0~1.0 */
    float32 mainKp;                                  /* Solve the loop carrier main loop KP configuration,
                                                        the value range of KP is 0~1.0 */
    float32 mainKi;                                  /* Solve the loop carrier main loop KI configuration,
                                                        the value range of KI is 0~1.0*/
} Rdc_InitialConfig;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/

#define RDC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rdc_hal_h_REF_4 */
#include "Rdc_MemMap.h"

/**********************************************************************************************************************
 * Function:     Rdc_Hal_GetPhaseEstimation
 * Description:  Get RDC module phase estimates
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 * Inout:        None
 * Output:       None
 * Return:       uint32: Phase estimates
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Rdc_Hal_GetPhaseEstimation(const RDC_MODULE *pRdc);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_GetRealTimeSpeed
 * Description:  Get the speed value of the real-time solution
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 * Inout:        None
 * Output:       None
 * Return:       sint32: The real-time speed
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE sint32 Rdc_Hal_GetRealTimeSpeed(const RDC_MODULE *pRdc);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_GetTrigTimeSpeed
 * Description:  Get the speed value of the trigger time
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 * Inout:        None
 * Output:       pTimeStamp: Timestamp information
 * Return:       sint32: The trigger time speed
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE sint32 Rdc_Hal_GetTrigTimeSpeed(const RDC_MODULE *pRdc, uint32 *pTimeStamp);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_GetRealTimeAngle
 * Description:  Get the angle value of the real-time solution
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 * Inout:        None
 * Output:       None
 * Return:       sint32: The real-time speed,the data is defined as S1.22 type, which represents radians from -PI
 *               to PI with the fixed-point binary number format
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE sint32 Rdc_Hal_GetRealTimeAngle(const RDC_MODULE *pRdc);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_GetTrigTimeAngle
 * Description:  Get the angle value of the trigger time
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 * Inout:        None
 * Output:       pTimeStamp: Timestamp information
 * Return:       sint32: The trigger time angle,the data is defined as S1.22 type, which represents radians from
 *               -PI to PI with the fixed-point binary number format
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE sint32 Rdc_Hal_GetTrigTimeAngle(const RDC_MODULE *pRdc, uint32 *pTimeStamp);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_TriggerByCpu
 * Description:  CPU triggered reporting of angle and speed information
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different RDC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pRdc: Specifies the pointer to the RDC registers
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Rdc_Hal_TriggerByCpu(RDC_MODULE *pRdc);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_GetIExtremeValue
 * Description:  Get I max extreme value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               select:Extreme value select
 * Inout:        None
 * Output:       None
 * Return:       sint16: I path extreme value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE sint16 Rdc_Hal_GetIExtremeValue(const RDC_MODULE *pRdc , Rdc_ExtremeValueSelect select);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_GetQExtremeValue
 * Description:  Get Q max extreme value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 *               select:Extreme value select
 * Inout:        None
 * Output:       None
 * Return:       sint16: Q path extreme value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE sint16 Rdc_Hal_GetQExtremeValue(const RDC_MODULE *pRdc , Rdc_ExtremeValueSelect select);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_ClearExtremeValue
 * Description:  Clear extreme value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pRdc: Specifies the pointer to the RDC registers
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Rdc_Hal_ClearExtremeValue(RDC_MODULE *pRdc);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Rdc_Hal_GetPhaseEstimation(const RDC_MODULE *pRdc)
{
    uint32 phaseEstimation;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
#endif /* INPUT_ARG_DETECT */

    /* The phaseEstimation is defined as S0.18 type,which represents radians from 0 to 2PI with the fixed-point
       binary number forma */
    phaseEstimation = (uint32)(pRdc->CPE.B.PE);

    return phaseEstimation;
}

LOCAL_FORCEINLINE sint32 Rdc_Hal_GetRealTimeSpeed(const RDC_MODULE *pRdc)
{
    sint32 speed;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
#endif /* INPUT_ARG_DETECT */

    /* The speed is defined as S1.24 type */
    speed = (sint32)(pRdc->VEL.B.VELOCITY);

    return speed;
}

LOCAL_FORCEINLINE sint32 Rdc_Hal_GetTrigTimeSpeed(const RDC_MODULE *pRdc, uint32 *pTimeStamp)
{
    sint32 speed;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
    /* Check if the pTimeStamp is null pointer */
    /* #Violation: rdc_hal_h_REF_1 */
    Assert((boolean)(NULL_PTR != pTimeStamp));
#endif /* INPUT_ARG_DETECT */

    /* The speed is defined as S1.24 type */
    speed = (sint32)(pRdc->TRIVEL.B.TRIVEL);
    *pTimeStamp = (uint32)(pRdc->TRIGTSMP.B.TSCOUNT);

    return speed;
}

LOCAL_FORCEINLINE sint32 Rdc_Hal_GetRealTimeAngle(const RDC_MODULE *pRdc)
{
    sint32 angle;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
#endif /* INPUT_ARG_DETECT */

    /* The angle is defined as S1.22 type,which represents radians from -PI to PI with the fixed-point binary
       number forma */
    angle = (sint32)(pRdc->ANG.B.ANGEL);

    return angle;
}

LOCAL_FORCEINLINE sint32 Rdc_Hal_GetTrigTimeAngle(const RDC_MODULE *pRdc, uint32 *pTimeStamp)
{
    sint32 angle;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
    /* Check if the pTimeStamp is null pointer */
    /* #Violation: rdc_hal_h_REF_1 */
    Assert((boolean)(NULL_PTR != pTimeStamp));
#endif /* INPUT_ARG_DETECT */

    /* The angle is defined as S1.22 type,which represents radians from -PI to PI with the fixed-point binary
       number forma */
    angle = (sint32)(pRdc->TRIANG.B.TRIANG);
    *pTimeStamp = (uint32)(pRdc->TRIGTSMP.B.TSCOUNT);

    return angle;
}

LOCAL_FORCEINLINE boolean Rdc_Hal_TriggerByCpu(RDC_MODULE *pRdc)
{
    boolean ret = 1U;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
#endif /* INPUT_ARG_DETECT */

    pRdc->CPUTRI.B.CPUTRI = 1U;
    ret = Rdc_Register_ReadBack_Check(ret, 1U, pRdc->CPUTRI.B.CPUTRI);

    return ret;
}

LOCAL_FORCEINLINE sint16 Rdc_Hal_GetIExtremeValue(const RDC_MODULE *pRdc , Rdc_ExtremeValueSelect select)
{
    sint16 value;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
#endif /* INPUT_ARG_DETECT */
    if(RDC_ExtremeValueSelect_MAX == select)
    {
        value = (sint16)pRdc->IEXTREVALRPT.B.MAX;
    }
    else
    {
        value = (sint16)pRdc->IEXTREVALRPT.B.MIN;
    }
    return value;
}

LOCAL_FORCEINLINE sint16 Rdc_Hal_GetQExtremeValue(const RDC_MODULE *pRdc , Rdc_ExtremeValueSelect select)
{
    sint16 value;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
#endif /* INPUT_ARG_DETECT */

    if(RDC_ExtremeValueSelect_MAX == select)
    {
        value = (sint16)pRdc->QEXTREVALRPT.B.MAX;
    }
    else
    {
        value = (sint16)pRdc->QEXTREVALRPT.B.MIN;
    }
    return value;
}

LOCAL_FORCEINLINE void Rdc_Hal_ClearExtremeValue(RDC_MODULE *pRdc)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_h_REF_2 */
    /* #Violation: rdc_hal_h_REF_3 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
#endif /* INPUT_ARG_DETECT */
    pRdc->IQEXTREVALCLR.B.CLR = 1U;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function:     Rdc_Hal_Init
 * Description:  Initialize the RDC module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pModule: specifies the pointer to the RDC registers
 *               pConfig: The data structure of RDC configures
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern boolean Rdc_Hal_Init(RDC_MODULE *const pModule, const Rdc_InitialConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_DeInit
 * Description:  De-initialize the RDC module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        idxSel: specifies RDC selection
 * Inout:        None
 * Output:       None
 * Return:       Rcc_ErrorFlag: RDC module reset state
 * Others:       The usage restriction in THA6412: If RDC1 uses the excitation function,
 *               the function Input parameter can only be RDC_IdxSel_1 or RDC_IdxSel_All.
 * History:
 *  Date          Author    Modified
 *  2025/03/25    00976      Create
 *********************************************************************************************************************/
extern Rcc_ErrorFlag Rdc_Hal_DeInit(Rdc_IdxSel idxSel);

/**********************************************************************************************************************
 * Function:     Rdc_Hal_ConvertToSpeed
 * Description:  To convert S1.22 fixed-point data into actual speed in the range of -3125 to 3125
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        speed: speed of S1.22 data type
 *               fs: ADC sampling rate
 * Inout:        None
 * Output:       None
 * Return:       float32: Actual speed value,the range of -1 to 1
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern float32 Rdc_Hal_ConvertToSpeed(sint32 speed, float32 fs);

#if defined(THA6_THA6412)
/**********************************************************************************************************************
 * Function:     Rdc_Hal_SetReferencePhase
 * Description:  Set Reference Phase
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different RDC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pRdc specifies the pointer to the RDC registers
 *               enable: 0:disable 1:enable
 *               phaseEstimation: Reference phase Value
 * Inout:        None
 * Output:       None
 * Return:       boolean: The results of the inspection
 * Others:       THA6412 support only
 * History:
 *  Date          Author    Modified
 *  2023/06/05    00915      Create
 *********************************************************************************************************************/
extern boolean Rdc_Hal_SetReferencePhase(RDC_MODULE *const pRdc, boolean enable, sint32 phaseEstimation);
#endif


#define RDC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rdc_hal_h_REF_4 */
#include "Rdc_MemMap.h"

#endif /* RDC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
