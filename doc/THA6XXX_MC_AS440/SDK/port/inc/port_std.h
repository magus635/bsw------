/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    port_std.h
 * Author:      01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all standard layer data type definitions and function declarations.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#port_std_c_REF_1:MISRAC2012-Rule-2.5;
* Justification:Compiler macro is defined and used followed AUTOSAR standard rule..
*
*/
#ifndef PORT_STD_H_
#define PORT_STD_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "port_register.h"
#include "compilertypes.h"
#include "Platform_Types.h"

/********************************************************************************************************************** \
 *                                             Global Macro Definitions                                                 \
 *********************************************************************************************************************/ \
/* The PORT Shift operation */
#define PORT_SHIFT_1 1U /* Port shift 1 */
#define PORT_SHIFT_2 2U /* Port shift 2 */
#define PORT_SHIFT_3 3U /* Port shift 3 */

/* The PORT operation */
/* #Violation: port_std_c_REF_1 */
#define PORT_MASK_BIT_013 0xBU        /* Port mask bit0, bit1, bit3 */
#define PORT_MASK_BIT_LOW_1 0x1U      /* Port mask bit0 */
#define PORT_MASK_BIT_LOW_2 0x3U      /* Port mask bit0~1 */
#define PORT_MASK_BIT_LOW_3 0x7U      /* Port mask bit0~2 */
#define PORT_MASK_BIT_LOW_4 0xFU      /* Port mask bit0~3 */
#define PORT_MASK_BIT_LOW_8 0xFFU     /* Port mask bit0~7 */
#define PORT_DSR_INPUTMODE_OFFSET 1U  /* Port DSR input mode offset */
#define PORT_DSR_SLEWRATE_OFFSET 2U   /* Port DSR slew rate offset */
#define PORT_DSR_LEVEL_OFFSET 3U      /* Port DSR level offset */
#define PORT_PINMODE_OPEN_INOUT 0x40U /* Port pin open input output mode */
/* #Violation: port_std_c_REF_1 */
#define PORT_PINMODE_OPEN_OUT 0xC0U   /* Port pin close input, open output mode */
/* #Violation: port_std_c_REF_1 */
#define PORT_PINMODE_OPEN_IN 0x00U    /* Port pin open input, close output mode */
/* #Violation: port_std_c_REF_1 */
#define PORT_PINMODE_OPEN_NONE 0x80U  /* Port pin close input, close output mode */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enum for port pin 0~15 */
typedef enum
{
    PORT_PIN_0 = 0U, /* Port pin 0 */
    PORT_PIN_1,      /* Port pin 1 */
    PORT_PIN_2,      /* Port pin 2 */
    PORT_PIN_3,      /* Port pin 3 */
    PORT_PIN_4,      /* Port pin 4 */
    PORT_PIN_5,      /* Port pin 5 */
    PORT_PIN_6,      /* Port pin 6 */
    PORT_PIN_7,      /* Port pin 7 */
    PORT_PIN_8,      /* Port pin 8 */
    PORT_PIN_9,      /* Port pin 9 */
    PORT_PIN_10,     /* Port pin 10 */
    PORT_PIN_11,     /* Port pin 11 */
    PORT_PIN_12,     /* Port pin 12 */
    PORT_PIN_13,     /* Port pin 13 */
    PORT_PIN_14,     /* Port pin 14 */
    PORT_PIN_15      /* Port pin 15 */
} Port_Pin;

/* Enum for port pin output multiplexer */
typedef enum
{
    PORT_OUTPUTSEL_O0 = 0U, /* Port multiplexer select 0 */
    PORT_OUTPUTSEL_O1,      /* Port multiplexer select 1 */
    PORT_OUTPUTSEL_O2,      /* Port multiplexer select 2 */
    PORT_OUTPUTSEL_O3,      /* Port multiplexer select 3 */
    PORT_OUTPUTSEL_O4,      /* Port multiplexer select 4 */
    PORT_OUTPUTSEL_O5,      /* Port multiplexer select 5 */
    PORT_OUTPUTSEL_O6,      /* Port multiplexer select 6 */
    PORT_OUTPUTSEL_O7,      /* Port multiplexer select 7 */
    PORT_OUTPUTSEL_O8,      /* Port multiplexer select 8 */
    PORT_OUTPUTSEL_O9,      /* Port multiplexer select 9 */
    PORT_OUTPUTSEL_O10,      /* Port multiplexer select 10 */
    PORT_OUTPUTSEL_O11,      /* Port multiplexer select 11 */
    PORT_OUTPUTSEL_O12,      /* Port multiplexer select 12 */
    PORT_OUTPUTSEL_O13,      /* Port multiplexer select 13 */
    PORT_OUTPUTSEL_O14,      /* Port multiplexer select 14 */
    PORT_OUTPUTSEL_O15       /* Port multiplexer select 15 */
} Port_OutputSel;

/* Enum for port pin output mode push-pull/open-drain */
typedef enum
{
    PORT_OUTPUTMODE_PUSHPULL = 0x0U,  /* Port pin output push-pull mode */
    PORT_OUTPUTMODE_OPENDRAIN = 0x20U /* Port pin output open-drain mode */
} Port_OutputMode;

/* Enum for port pin pull-up and pull-down */
typedef enum
{
    PORT_PULL_NONE = 0U, /* Port pin no pull */
    PORT_PULL_DOWN = 2U, /* Port pin pull-down */
    PORT_PULL_UP = 3U    /* Port pin pull-up */
} Port_Pull;

/* Enum for port pin output state */
typedef enum
{
    PORT_OUTPUTSTATE_UNCHANGED = 0x0U, /* Port pin state is left unchanged */
    PORT_OUTPUTSTATE_LOW = 0x1U,       /* Port pin state is set to low */
    PORT_OUTPUTSTATE_HIGH = 0x10000U,  /* Port pin state is set to high */
    PORT_OUTPUTSTATE_TOGGLE = 0x10001U /* Port pin state is toggled */
} Port_OutputState;

/* Enum for port pin input state */
typedef enum
{
    PORT_INPUTSTATE_LOW = 0U, /* Port pin input state is low */
    PORT_INPUTSTATE_HIGH      /* Port pin input state is high */
} Port_InputState;

/* Enum for port pin input mode schmidt/cmos */
typedef enum
{
    PORT_INPUTMODE_SCHMIDT = 0x0U, /* Port pin input schmidt mode */
    PORT_INPUTMODE_CMOS            /* Port pin input cmos mode */
} Port_InputMode;

/* Enum for port pin level AL/TTL */
typedef enum
{
    PORT_LEVEL_AL = 0U, /* Port pin set AL level */
    PORT_LEVEL_TTL      /* Port pin set TTL level */
} Port_Level;

/* Enum for port pin drive strength */
typedef enum
{
    PORT_DRIVESTRENGTH_LOW = 0U, /* Port pin drive strength is low  */
    PORT_DRIVESTRENGTH_HIGH      /* Port pin drive strength is high */
} Port_DriveStrength;
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Macro Declarations
 *********************************************************************************************************************/
#define PORT_REG_CHECK
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

/**********************************************************************************************************************
 * Function: Port_Std_SetPinInput
 * Description: Set port pin input.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pPort: Pointer to port module.
 *        pin: Port pin number.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Std_SetPinInput(PORT_MODULE *pPort, Port_Pin pin);

/**********************************************************************************************************************
 * Function: Port_Std_SetPinOutput
 * Description: Set port pin output.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pPort: Pointer to port module.
 *        pin: Port pin number.
 *        outputSel: Output multiplexer.
 *        outputMode: output mode push-pull/open-drain.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Std_SetPinOutput(PORT_MODULE *pPort, Port_Pin pin, Port_OutputSel outputSel, Port_OutputMode outputMode);

/**********************************************************************************************************************
 * Function: Port_Std_SetPinInputMode
 * Description: Set port pin input mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pPort: Pointer to port module.
 *        pin: Port pin number.
 *        mode: Input mode.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/08/17   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Std_SetPinInputMode(PORT_MODULE *pPort, Port_Pin pin, Port_InputMode mode);

/**********************************************************************************************************************
 * Function: Port_Std_SetPinPullMode
 * Description: Set port pin pull mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pPort: Pointer to port module.
 *        pin: Port pin number.
 *        pull: Port pin pull mode.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Std_SetPinPullMode(PORT_MODULE *pPort, Port_Pin pin, Port_Pull pull);

/**********************************************************************************************************************
 * Function: Port_Std_SetPinLevel
 * Description: Set port pin level.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: port: Pointer to port module.
 *        pin: Port pin number.
 *        level: Port pin level AL/TTL.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: Clear endinit before use.
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Std_SetPinLevel(PORT_MODULE *pPort, Port_Pin pin, Port_Level level);

/**********************************************************************************************************************
 * Function: Port_Std_SetPinDriveStrength
 * Description: Set port pin drive strength.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: port: Pointer to port module.
 *        pin: Port pin number.
 *        strength: Port pin drive strength low/high.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: Clear endinit before use.
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Std_SetPinDriveStrength(PORT_MODULE *pPort, Port_Pin pin, Port_DriveStrength strength);

/**********************************************************************************************************************
 * Function: Port_Register_ReadBack_Check
 * Description: port register write check
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: state: Original state.
 *        expect: The value expected to be written.
 *        value: The value actually written.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2023/05/29   01077     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#if defined(PORT_REG_CHECK)
LOCAL_FORCEINLINE boolean Port_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
LOCAL_FORCEINLINE boolean Port_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Std_SetPinInput(PORT_MODULE *pPort, Port_Pin pin)
{
    /* Value for configure CTRx */
    volatile PORT_CTR0 *pCtr; /* Pointer to CTR module */
    uint8 ctrIndex;
    uint8 ctrShift;
    boolean ret;
    uint32 ctr;

    ret = TRUE;
    /* Set input and output, configure CTRx */
    pCtr = &(pPort->CTR0); /* Point to CTR register */
    /* Calculate CTR register offset */
    ctrIndex = ((uint8)pin >> PORT_SHIFT_2);
    ctrShift = (((uint8)pin & PORT_MASK_BIT_LOW_2) << PORT_SHIFT_3);
    ctr = (pCtr[ctrIndex].U & ~((uint32)PORT_MASK_BIT_LOW_8 << ctrShift));
    pCtr[ctrIndex].U = ctr;

    ret = Port_Register_ReadBack_Check(ret, ctr, pCtr[ctrIndex].U);
    return ret;
}

LOCAL_FORCEINLINE boolean Port_Std_SetPinOutput(PORT_MODULE *pPort, Port_Pin pin, Port_OutputSel outputSel,
                                             Port_OutputMode outputMode)
{
    /* Set input and output, configure CTRx */
    volatile PORT_CTR0 *pCtr;
    uint32 ctr;
    uint8 ctrIndex;
    uint8 ctrShift;
    boolean ret;

    ret = TRUE;
    /* Write to CTR */
    pCtr = &(pPort->CTR0);
    /* Calculate CTR register offset */
    ctrIndex = ((uint8)pin >> PORT_SHIFT_2);
    ctrShift = (((uint8)pin & PORT_MASK_BIT_LOW_2) << PORT_SHIFT_3);
    ctr = pCtr[ctrIndex].U;
    ctr &= ~((uint32)PORT_MASK_BIT_LOW_8 << ctrShift); /* Clear CTR bit field */
    
    /* first write bit SELx within bit ENx is 0 */
    ctr |= (((uint32)outputSel | (uint32)outputMode | PORT_PINMODE_OPEN_IN) << ctrShift); 
    pCtr[ctrIndex].U = ctr; /* Write configure to CTR register*/
    ret = Port_Register_ReadBack_Check(ret, ctr, pCtr[ctrIndex].U);

    /* second write bit ENx */
    ctr |= (uint32)((uint32)PORT_PINMODE_OPEN_INOUT << (uint32)ctrShift); 
    pCtr[ctrIndex].U = ctr; /* Write configure to CTR register*/

    ret = Port_Register_ReadBack_Check(ret, ctr, pCtr[ctrIndex].U);
    return ret;
}
    
LOCAL_FORCEINLINE boolean Port_Std_SetPinInputMode(PORT_MODULE *pPort, Port_Pin pin, Port_InputMode mode)
{
    volatile PORT_DSR0 *pDsr;
    uint32 dsr;
    uint32 dsrIndex;
    uint32 shift;
    boolean ret;

    ret = TRUE;
    dsrIndex = (uint32)pin >> PORT_SHIFT_3; /* Calculate DSR index */
    shift = ((((uint32)pin & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2) + PORT_DSR_INPUTMODE_OFFSET); /* Calculate input mode bit field shift */
    pDsr = &(pPort->DSR0);               /* Point to DSR register */

    dsr = pDsr[dsrIndex].U;                         /* Read DSR register */
    dsr &= ~((uint32)PORT_MASK_BIT_LOW_1 << shift); /* Clear input mode bit field */
    dsr |= ((uint32)mode << shift);                 /* Write input mode to bit field */

    pDsr[dsrIndex].U = dsr; /* Write DSR register */

    ret = Port_Register_ReadBack_Check(ret, dsr, pDsr[dsrIndex].U);
    return ret;
}

LOCAL_FORCEINLINE boolean Port_Std_SetPinPullMode(PORT_MODULE *pPort, Port_Pin pin, Port_Pull pull)
{
    uint32 psr;
    boolean ret;

    ret = TRUE;
    psr = pPort->PSR.U;

    psr &= (~((uint32)PORT_MASK_BIT_LOW_2 << ((uint8)pin << PORT_SHIFT_1))); /* Clear pull bit field */
    psr |= ((uint32)pull << ((uint8)pin << PORT_SHIFT_1));                   /* Set pull mode */
    pPort->PSR.U = psr;                                                      /* Write PSR register */

    ret = Port_Register_ReadBack_Check(ret, psr, pPort->PSR.U);
    return ret;
}

LOCAL_FORCEINLINE boolean Port_Std_SetPinLevel(PORT_MODULE *pPort, Port_Pin pin, Port_Level level)
{
    /* Value for configure DSRx */
    volatile PORT_DSR0 *pDsr; /* Pointer to DSR module */
    uint8 dsrIndex;
    uint8 dsrShift;
    uint32 dsr;
    boolean ret;

    ret = TRUE;
    pDsr = &(pPort->DSR0);                   /* Point to DSR register */
    dsrIndex = ((uint8)pin >> PORT_SHIFT_3); /* Calculate DSR register offset */
    /* Calculate level bit field offset */
    dsrShift = ((((uint8)pin & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2) + PORT_DSR_LEVEL_OFFSET);

    if(PORT_LEVEL_TTL == level)
    {
        dsr = pDsr[dsrIndex].U | ((uint32)PORT_MASK_BIT_LOW_1 << dsrShift); /* Set TTL level */
    }
    else
    {
        dsr = pDsr[dsrIndex].U & ~((uint32)PORT_MASK_BIT_LOW_1 << dsrShift); /* Set AL level */
    }
    pDsr[dsrIndex].U = dsr; 

    ret = Port_Register_ReadBack_Check(ret, dsr, pDsr[dsrIndex].U);
    return ret;
}

LOCAL_FORCEINLINE boolean Port_Std_SetPinDriveStrength(PORT_MODULE *pPort, Port_Pin pin, Port_DriveStrength strength)
{
    volatile PORT_DSR0 *pDsr;
    uint32 dsr;
    uint32 dsrIndex;
    uint32 shift;
    boolean ret;

    ret = TRUE;
    dsrIndex = (uint32)pin >> PORT_SHIFT_3;                      /* Calculate DSR index */
    shift = ((uint32)pin & PORT_MASK_BIT_LOW_3) << PORT_SHIFT_2; /* Calculate drive strength bit field shift */
    pDsr = &(pPort->DSR0);                                       /* Point to DSR register */

    dsr = pDsr[dsrIndex].U;                         /* Read DSR register */
    dsr &= ~((uint32)PORT_MASK_BIT_LOW_1 << shift); /* Clear drive strength bit field */
    dsr |= ((uint32)strength << shift);             /* Write drive strength to bit field */

    pDsr[dsrIndex].U = dsr; /* Write DSR register */
    ret = Port_Register_ReadBack_Check(ret, dsr, pDsr[dsrIndex].U);
    return ret;
}

#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/

#endif /* PORT_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
