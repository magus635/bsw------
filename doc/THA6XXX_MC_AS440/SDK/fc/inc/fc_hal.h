/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    fc_hal.h
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
#ifndef FC_HAL_H_
#define FC_HAL_H_
/*
*#Violation Summary
*#fc_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#fc_hal_h_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "fc_register.h"
#include "rcc_hal.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                           Global Macro Definitions
 *********************************************************************************************************************/
/* ^Initial Time Out^ analog initialization time out */
#define ANALOG_INIT_TIMEOUT 0xFFFFFUL

#define FC_REG_CHECK
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/

/* Enumeration for reference value generate mode */
typedef enum
{
    FC_REFERENCEVALUEMODE_SOFTWARE = 0U, /* software mode */
    FC_REFERENCEVALUEMODE_ALTERNATE,     /* alternate mode */
    FC_REFERENCEVALUEMODE_RAMP,          /* ramp mode */
    FC_REFERENCEVALUEMODE_HDI            /* HDI mode */
} Fc_ReferenceValueMode;

/* Enumeration for select input channel of trigger */
typedef enum
{
    FC_TRIGGERINPUTSEL_ADCZ_TRIG0 = 8U,  /* trigger is ADCz trigger0 */
    FC_TRIGGERINPUTSEL_ADCZ_TRIG1,       /* trigger is ADCz trigger1 */
    FC_TRIGGERINPUTSEL_ADCZ_TRIG2,       /* trigger is ADCz trigger2 */
    FC_TRIGGERINPUTSEL_ADC8_TRIG3 = 11U, /* trigger is ADC8 trigger3 */
    FC_TRIGGERINPUTSEL_ADC9_TRIG3 = 11U, /* trigger is ADC9 trigger3 */
    FC_TRIGGERINPUTSEL_ADC8_TRIG4 = 12U, /* trigger is ADC8 trigger4 */
    FC_TRIGGERINPUTSEL_ADC9_TRIG4 = 12U, /* trigger is ADC9 trigger4 */
    FC_TRIGGERINPUTSEL_LOW = 0U          /* trigger is low level*/
} Fc_TriggerInputSel;

/* Enumeration for select trigger polarity */
typedef enum
{
    FC_TRIGGERPOLARITY_NO_INVERT = 0U, /* the trigger level is invert */
    FC_TRIGGERPOLARITY_INVERT          /* the trigger level is not invert */
} Fc_TriggerPolarity;

/* Enumeration for select polarity */
typedef enum
{
    FC_RAMPDIR_DOWN = 0U, /* ramp up */
    FC_RAMPDIR_UP         /* ramp down */
} Fc_RampDir;

/* Enumeration for run control mode of ramp */
typedef enum
{
    FC_RAMPRUNCTRL_STOP = 0U,                     /* trigger to stop ramp */
    FC_RAMPRUNCTRL_WTITESTARTVALUERUN,            /* write reference value to start ramp */
    FC_RAMPRUNCTRL_TRIGGERRAN,                    /* trigger to run ramp*/
    FC_RAMPRUNCTRL_WTITESTARTVALUERUN_TRIGGERSTOP /* write reference value to start ramp and trigger to stop ramp */
} Fc_RampRunCtrl;

/* Enumeration for trigger edge of control ramp */
typedef enum
{
    FC_RAMPTRIGGEREDGE_NONE = 0U, /* do not control */
    FC_RAMPTRIGGEREDGE_DOWN,      /* down edge */
    FC_RAMPTRIGGEREDGE_UP,        /* up edge */
    FC_RAMPTRIGGEREDGE_BOTH       /* both edge */
} Fc_RampTriggerEdge;

/* Enumeration for generate boundary flag mode */
typedef enum
{
    FC_BOUNDARYFLAGMODE_ABOVE = 0U, /* set boundary flag when the compare is above reference value */
    FC_BOUNDARYFLAGMODE_BELOW       /* set boundary flag when the compare is below reference value */
} Fc_BoundaryFlagMode;

/* Enumeration for boundary flag polarity */
typedef enum
{
    FC_BOUNDARYFLAGPOLARITY_NO_INVERT = 0U, /* do not invert boundary flag */
    FC_BOUNDARYFLAGPOLARITY_INVERT          /* invert boundary flag */
} Fc_BoundaryFlagPolarity;

/* Enumeration for common output */
typedef enum
{
    FC_COMMOMOUTPUTSEL_COM0 = 0U, /* common boundary flag output 0 */
    FC_COMMOMOUTPUTSEL_COM1,      /* common boundary flag output 1 */
    FC_COMMOMOUTPUTSEL_COM2,      /* common boundary flag output 2 */
    FC_COMMOMOUTPUTSEL_COM3,      /* common boundary flag output 3 */
    FC_COMMOMOUTPUTSEL_INT0,      /* common interrupt output 0 */
    FC_COMMOMOUTPUTSEL_INT1,      /* common interrupt output 1 */
    FC_COMMOMOUTPUTSEL_INT2,      /* common interrupt output 2 */
    FC_COMMOMOUTPUTSEL_INT3,      /* common interrupt output 3 */
    FC_COMMOMOUTPUTSEL_NONE       /* no common output */
} Fc_CommonOutputSel;

/* Enumeration for select boundary flag output */
typedef enum
{
    FC_BOUNDARYFLAGOUTPUTSEL_PROCESSED = 0U, /* output is processed */
    FC_BOUNDARYFLAGOUTPUTSEL_NO_PROCESSED    /* output is compare result */
} Fc_BoundaryFlagOutputSel;

/* Enumeration for fc analog clock divider factor */
typedef enum
{
    FC_CLOCKDIV_2 = 0U, /* fc clock divider is 2 */
    FC_CLOCKDIV_4,      /* fc clock divider is 4 */
    FC_CLOCKDIV_6,      /* fc clock divider is 6 */
    FC_CLOCKDIV_8,      /* fc clock divider is 8 */
    FC_CLOCKDIV_10,     /* fc clock divider is 10 */
    FC_CLOCKDIV_12,     /* fc clock divider is 12 */
    FC_CLOCKDIV_14,     /* fc clock divider is 14 */
    FC_CLOCKDIV_16,     /* fc clock divider is 16 */
} Fc_ClockDiv;

/* Enumeration for fc sample and compare time control */
typedef enum
{
    FC_CLOCKCONTROL_2 = 0U, /* fc clock control is 2 clock */
    FC_CLOCKCONTROL_4,      /* fc clock control is 4 clock */
    FC_CLOCKCONTROL_6,      /* fc clock control is 6 clock */
    FC_CLOCKCONTROL_8,      /* fc clock control is 8 clock */
} Fc_ClockControl;

/* Enumeration for fc input select */
typedef enum
{
    FC_INPUTSEL_NORMAL = 0U, /* fc input is normal */
    FC_INPUTSEL_TEST = 3U,   /* fc input is test source */
} Fc_InputSel;

/* Enumeration for interrupt generate mode */
typedef enum
{
    FC_INTERRUTMODE_NONE = 0U,        /* do not generate interrupt */
    FC_INTERRUTMODE_RAMP_OVER,        /* generate interrupt when ramp over */
    FC_INTERRUTMODE_UPDATE_REFERENCE, /* generate interrupt when reference update */
    FC_INTERRUTMODE_COMPARE_OVER,     /* generate interrupt when compare over */
} Fc_InterruptMode;

/* Enumeration for interrupt generate event when compare over */
typedef enum
{
    FC_INTERRUTEVENT_NONE = 0U, /* do not generate interrupt */
    FC_INTERRUTEVENT_ABOVE,     /* generate interrupt when compare result is above reference value */
    FC_INTERRUTEVENT_BELOW,     /* generate interrupt when compare result is below reference value */
    FC_INTERRUTEVENT_BOTH       /* generate interrupt when compare result is below or above reference value */
} Fc_InterruptEvent;

/* Enumeration for boundary flag control */
typedef enum
{
    FC_BOUNDARYFLAGCONTROL_HOLD = 0U, /* hold the boundary flag */
    FC_BOUNDARYFLAGCONTROL_CLEAR,     /* clear the boundary flag by software */
    FC_BOUNDARYFLAGCONTROL_SET,       /* set the boundary flag by software */
    FC_BOUNDARYFLAGCONTROL_INVERT,    /* invert the boundary flag by software */
    FC_BOUNDARYFLAGCONTROL_HARDWARE,  /* boundary flag control by hardware */
} Fc_BoundaryFlagControl;

/* Error indicating flag */
typedef enum
{
    FC_ERRORFLAG_SUCCESS = 0U, /* Execute successful */
    FC_ERRORFLAG_FAIL,         /* Code execute fail */
} Fc_ErrorFlag;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure for interrupt */
typedef struct
{
    Fc_InterruptMode mode;   /* mode of generate interrupt */
    Fc_InterruptEvent event; /* event of generate interrupt when compare over */
} Fc_Interrupt;

/* Structure for alternate value */
typedef struct
{
    uint32 value0; /* alternate value0 */
    uint32 value1; /* alternate value1*/
} Fc_AlternateValue;

/* Structure for trigger configuration */
typedef struct
{
    Fc_TriggerInputSel inputSel; /* input select of trigger */
    Fc_TriggerPolarity polarity; /* polarity of trigger */
} Fc_Trigger;

/*  Structure for ramp configuration of reference value generate is ramp mode */
typedef struct
{
    uint32 startValue;              /* start value of ramp */
    uint32 endValue;                /* end value of ramp */
    Fc_RampDir dir;                 /* direct of ramp */
    uint32 stepWide;                /* step wide of ramp */
    Fc_RampRunCtrl runCtrl;         /* run control mode of ramp */
    Fc_RampTriggerEdge triggerEdge; /* trigger edge of control ramp */
} Fc_RampConfig;

/* Structure for reference value configuration */
typedef struct
{
    Fc_ReferenceValueMode refMode;    /* reference value generate mode */
    Fc_Trigger trigger;               /* trigger configuration*/
    uint16 referenceValue;            /* reference value of reference value generate is software mode*/
    Fc_AlternateValue alternateValue; /* alternate value of reference value generate is alternate mode */
    Fc_RampConfig rampConfig;         /* ramp configuration of reference value generate is ramp mode */
    uint16 upDelta;                   /* up hysteresis of reference value */
    uint16 lowDelta;                  /* low hysteresis of reference value */
} Fc_ReferenceValueConfig;

/* Structure for boundary flag lock */
typedef struct
{
    boolean bfLockEnable; /* boundary flag lock enable */
    boolean bflockValue;  /* boundary flag lock value */
} Fc_BoundaryFlagLock;

/* Structure for fc output configuration */
typedef struct
{
    Fc_BoundaryFlagMode bfMode;           /* generate boundary flag mode */
    Fc_BoundaryFlagPolarity bfpolarity;   /* boundary flag polarity */
    Fc_CommonOutputSel commonOutputSel;   /* common output select */
    Fc_BoundaryFlagOutputSel bfOutputSel; /* boundary flag output select */
    Fc_BoundaryFlagLock bfLock;           /* boundary flag lock */
    Fc_BoundaryFlagControl ctrl;          /* boundary flag control */
} Fc_OutputConfig;

/* Structure for fc compare function configuration */
typedef struct
{
    Fc_ClockDiv clockDiv;        /* analog clock divider factor */
    Fc_ClockControl sampleTime;  /* fc sample time control */
    Fc_ClockControl compareTime; /* fc compare time control */
    uint8 compareInterval;       /* fc compare time interval, the interval is analog clock cycle */
    boolean dmaEnable;           /* fc DMA transfer enable */
    Fc_InputSel inputSel;        /* fc input select*/
} Fc_CompareConfig;

/* Structure for fc all configuration */
typedef struct
{
    Fc_ReferenceValueConfig reference; /* reference configuration */
    Fc_OutputConfig output;            /* output configuration */
    Fc_CompareConfig compareConfig;    /* compare configuration */
} Fc_Config;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: fc_hal_h_REF_1 */
#define FC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: fc_hal_h_REF_2 */
#include "Fc_MemMap.h"
/**********************************************************************************************************************
 * Function:     Fc_Register_ReadBack_Check
 * Description:  Register read back check
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        state: Original state
 *               expect: The value expected to be written
 *               value: The value actually written
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/05/29    01359     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Fc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(FC_REG_CHECK)
LOCAL_FORCEINLINE boolean Fc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
LOCAL_FORCEINLINE boolean Fc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
 * Function:     Fc_Hal_ResetModule
 * Description:  Reset one specific FC module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pFc: Pointer to FC module
 * Inout:        None
 * Output:       None
 * Return:       Rcc_ErrorFlag: the status of module reset, module reset failed, status may be timeout or null pointer
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern Rcc_ErrorFlag Fc_Hal_ResetModule(const FC_MODULE *const pFc);
/**********************************************************************************************************************
 * Function:     Fc_Hal_InitReferenceValue
 * Description:  Initial FC reference value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different FC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pFc: Pointer to FC module
 *               pConfig: Pointer to configuration of FC reference value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_InitReferenceValue(FC_MODULE *const pFc, const Fc_ReferenceValueConfig *const pConfig);
/**********************************************************************************************************************
 * Function:     Fc_Hal_InitOutput
 * Description:  Initial FC output.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different FC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pFc: Pointer to FC module
 *               pConfig: Pointer to configuration of FC output
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_InitOutput(FC_MODULE *const pFc, const Fc_OutputConfig *const pConfig);
/**********************************************************************************************************************
 * Function:     Fc_Hal_Init
 * Description:  Initial all configuration of FC module, include FC reference and output and clock etc.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pFc: Pointer to FC module
 *               pConfig: Pointer to configuration of FC module
 * Inout:        None
 * Output:       None
 * Return:       Fc_ErrorFlag:
 *                 FC_ERRORFLAG_SUCCESS: initialization success
 *                 FC_ERRORFLAG_FAIL: initialization fail
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern Fc_ErrorFlag Fc_Hal_Init(FC_MODULE *const pFc, const Fc_Config *const pConfig);
/**********************************************************************************************************************
 * Function:     Fc_Hal_StartCompare
 * Description:  Start or stop comparison.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pFc: Pointer to FC module
 *               enable: If true, start comparison; otherwise, stop comparison
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_StartCompare(FC_MODULE *const pFc, boolean enable);
/**********************************************************************************************************************
 * Function:     Fc_Hal_SetInterrupt
 * Description:  Set FC interrupt,including interrupt triggering mode and enable.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different FC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pFc: Pointer to FC module
 *               pConfig: Pointer to FC interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_SetInterrupt(FC_MODULE *const pFc, const Fc_Interrupt *const pConfig);
/**********************************************************************************************************************
 * Function:     Fc_Hal_GetInterruptStatus
 * Description:  Get interrupt status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pFc: Pointer to FC module
 * Inout:        None
 * Output:       None
 * Return:       boolean: Interrupt status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_GetInterruptStatus(const FC_MODULE *const pFc);
/**********************************************************************************************************************
 * Function:     Fc_Hal_ClearInterruptStatus
 * Description:  Clear interrupt status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pFc: Pointer to FC module
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern void Fc_Hal_ClearInterruptStatus(FC_MODULE *const pFc);
/**********************************************************************************************************************
 * Function:     Fc_Hal_SetBoundaryFlag
 * Description:  Set boundary flag by software or by hardware.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different FC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pFc: Pointer to FC module
 *               ctrl: boundary flag software control
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_SetBoundaryFlag(FC_MODULE *const pFc, Fc_BoundaryFlagControl ctrl);
/**********************************************************************************************************************
 * Function:     Fc_Hal_SetRampValue
 * Description:  Set reference value of ramp mode and alternation mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different FC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pFc: Pointer to FC module
 *               refVal0: reference value 0
 *               refVal1: reference value 1
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_SetRampValue(FC_MODULE *const pFc, uint16 refVal0, uint16 refVal1);
/**********************************************************************************************************************
 * Function:     Fc_Hal_SetReferenceValue
 * Description:  Set reference value of software set fix reference mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different FC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pFc: Pointer to FC module
 *               referVal: reference value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/01/16    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_SetReferenceValue(FC_MODULE *const pFc, uint16 referVal);
/**********************************************************************************************************************
 * Function:     Fc_Hal_GetCompareStatus
 * Description:  Get compare status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different FC modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pFc: Pointer to FC module
 * Inout:        None
 * Output:       None
 * Return:       boolean: status : 0:compare result is not update,1:compare result is update
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/04/26    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_GetCompareStatus(const FC_MODULE *const pFc);
/**********************************************************************************************************************
 * Function:     Fc_Hal_GetCompareResult
 * Description:  Get compare result.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pFc: Pointer to FC module
 * Inout:        None
 * Output:       None
 * Return:       boolean: value : 0:compare voltage is below reference,1:compare voltage is above reference
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/04/26    01254     Create
 *********************************************************************************************************************/
extern boolean Fc_Hal_GetCompareResult(const FC_MODULE *const pFc);

/* #Violation: fc_hal_h_REF_1 */
#define FC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: fc_hal_h_REF_2 */
#include "Fc_MemMap.h"
#endif /* FC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
