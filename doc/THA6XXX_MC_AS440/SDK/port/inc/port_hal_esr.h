/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    port_hal_esr.h
 * Author:      01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all hardware abstract layer data type definitions and function declarations.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#port_hal_esr_h_1:MISRAC2012-Rule-2.5;
* Justification:Compiler macro is defined and used followed AUTOSAR standard rule.
*
*#port_hal_esr_h_2:MISRAC2012-Rule-11.4; 
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#port_hal_esr_h_3:MISRAC2012-Rule-10.5
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*/
#ifndef PORT_HAL_ESR_H_
#define PORT_HAL_ESR_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "port_register.h"
#include "port_std.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "tha6_cfg.h"
#include "compilertypes.h"
#if (STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* PORT_ESR_PIN_DEFINE */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_PIN_0 (uint8)(0x00U) /* ESR Pin 0 */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_PIN_1 (uint8)(0x01U) /* ESR Pin 1 */

/* PORT_ESR_OUTPUTSEL_DEFINE */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_OUTPUTSEL_GPOUT    (uint8)(0x00U) /* General-purpose output */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_OUTPUTSEL_SYSRESET (uint8)(0x01U) /* System reset output, only for ESR0 */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_OUTPUTSEL_APPRESET (uint8)(0x02U) /* Application reset output */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_OUTPUTSEL_CLOSE    (uint8)(0x03U) /* Close output */

/* PORT_ESR_OUTPUTMODE_DEFINE */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_OUTPUTMODE_PUSHPULL  (uint8)(0x00U) /* Port pin output push-pull mode */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_OUTPUTMODE_OPENDRAIN (uint8)(0x01U) /* Port pin output open-drain mode */

/* PORT_ESR_LEVEL_DEFINE */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_LEVEL_AL  (uint8)(0x00U) /* Port pin set AL level */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_LEVEL_TTL (uint8)(0x01U) /* Port pin set TTL level */

/* PORT_ESR_DRIVESTRENGTH_DEFINE */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_DRIVESTRENGTH_LOW  (uint8)(0x00U) /* Port pin drive strength is low  */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_DRIVESTRENGTH_HIGH (uint8)(0x01U) /* Port pin drive strength is high */

/* PORT_ESR_SLEWRATE_DEFINE */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_SLEWRATE_OFF (uint8)(0x00U) /* Slew-rate mode off */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_SLEWRATE_ON  (uint8)(0x01U) /* Slew-rate mode on, only for PORT_ESR_DRIVESTRENGTH_HIGH */

/* PORT_ESR_INPUTMODE_DEFINE */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_INPUTMODE_SCHTRIG  (uint8)(0x00U) /* Schmidt trigger */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_INPUTMODE_CMOS     (uint8)(0x01U) /* CMOS */

/* PORT_ESR_PULL_DEFINE */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_PULL_UP   (uint8)(0x03U) /* Pull up */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_PULL_DOWN (uint8)(0x02U) /* Pull down */
/* #Violation: port_hal_esr_h_1 */
#define PORT_ESR_PULL_NO   (uint8)(0x00U) /* No pull */
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* ESR pad driver configuration structure */
typedef struct
{
    uint8 inputMode;     /* Input mode selection */
    uint8 level;         /* Select AL/TTL level */
    uint8 driveStrength; /* Select drive strength */
    uint8 slewRate;      /* Slew-rate mode */
} Port_EsrPadDriverConfig;

/* ESR configuration structure */
typedef struct
{
    uint8   pin;         /* Port pin, should be PORT_ESR_PIN_0 or PORT_ESR_PIN_1 */
    boolean outputEn;    /* Output Enable: 1U enable, 0U disable */
    uint8   outputSel;   /* Output multiplexer, should be a value of PORT_ESR_OUTPUTSEL_DEFINE */
    uint8   outputMode;  /* Select push-pull/open-drain, should be a value of PORT_ESR_OUTPUTMODE_DEFINE */
    boolean inputDis;    /* 1U disable input channel, internal level is always low.
                            0U enable input channel */

    uint8 pullResistor;  /* Pull Up/down resistor, should be a value of PORT_ESR_PULL_DEFINE */
    Port_EsrPadDriverConfig *pPadDriverCfg; /* Pad driver configuration */
} Port_EsrConfig;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

/**********************************************************************************************************************
 * Function: Port_Hal_Esr_SetPinHigh
 * Description: Set port pin output high.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pin: Port pin, should be PORT_ESR_PIN_0 or PORT_ESR_PIN_1.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2023/08/28    01077    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_Esr_SetPinHigh(uint8 pin);

/**********************************************************************************************************************
 * Function: Port_Hal_Esr_SetPinLow
 * Description: Set port pin output low.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pin: Port pin, should be PORT_ESR_PIN_0 or PORT_ESR_PIN_1.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2023/08/28    01077    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_Esr_SetPinLow(uint8 pin);

/**********************************************************************************************************************
 * Function: Port_Hal_Esr_SetPinToggle
 * Description: Set port pin output toggle.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESR pins, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input: pin: Port pin, should be PORT_ESR_PIN_0 or PORT_ESR_PIN_1.
 * Inout:  None
 * Output: None
 * Return: None
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2023/08/28    01077    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_Esr_SetPinToggle(uint8 pin);

/**********************************************************************************************************************
 * Function: Port_Hal_Esr_GetPinInputState
 * Description: Get port pin input state.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: pin: Port pin.
 * Inout:  None
 * Output: None
 * Return: Port_InputState: PORT_INPUTSTATE_HIGH: Pin level is high.
 *                          PORT_INPUTSTATE_LOW: Pin level is low.
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2023/08/28    01077    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE Port_InputState Port_Hal_Esr_GetPinInputState(uint8 pin);

/**********************************************************************************************************************
 * Function: Port_Hal_Esr_GetApplicationResetIndicator
 * Description: Get application reset indicator.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: None
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Application reset occured. FASLE: Application reset don't occured.
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2023/10/18    01077    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Port_Hal_Esr_GetApplicationResetIndicator(void);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Port_Hal_Esr_SetPinHigh(uint8 pin)
{
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_esr_h_3 */
    Assert((boolean)((PORT_ESR_PIN_0 == pin) || (PORT_ESR_PIN_1 == pin)));
#endif

    /* output data bit set */
    /* #Violation: port_hal_esr_h_2 */
    PORT_PESR->BSRR.U = ((uint32)PORT_OUTPUTSTATE_HIGH << pin);
}

LOCAL_FORCEINLINE void Port_Hal_Esr_SetPinLow(uint8 pin)
{
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_esr_h_3 */
    Assert((boolean)((PORT_ESR_PIN_0 == pin) || (PORT_ESR_PIN_1 == pin)));
#endif
    /* output data bit reset */
    /* #Violation: port_hal_esr_h_2 */
    PORT_PESR->BSRR.U = ((uint32)PORT_OUTPUTSTATE_LOW << pin);
}

LOCAL_FORCEINLINE void Port_Hal_Esr_SetPinToggle(uint8 pin)
{
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_esr_h_3 */
    Assert((boolean)((PORT_ESR_PIN_0 == pin) || (PORT_ESR_PIN_1 == pin)));
#endif
    /* Set port pin output toggle */
    /* #Violation: port_hal_esr_h_2 */
    PORT_PESR->BSRR.U = ((uint32)PORT_OUTPUTSTATE_TOGGLE << pin);
}

LOCAL_FORCEINLINE Port_InputState Port_Hal_Esr_GetPinInputState(uint8 pin)
{
    Port_InputState inputState;
    
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_esr_h_3 */
    Assert((boolean)((PORT_ESR_PIN_0 == pin) || (PORT_ESR_PIN_1 == pin)));
#endif

    /* Read port pin input state */
    /* #Violation: port_hal_esr_h_2 */
    if (0U != (PORT_PESR->IDR.U & ((uint32)1U << pin)))
    {
        inputState = PORT_INPUTSTATE_HIGH;
    }
    else
    {
        inputState = PORT_INPUTSTATE_LOW;
    }

    return inputState;
}

LOCAL_FORCEINLINE boolean Port_Hal_Esr_GetApplicationResetIndicator(void)
{
    /* #Violation: port_hal_esr_h_2 */
    return (boolean)PORT_PESR->OCFG.B.ARI;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function: Port_Hal_Esr_ClearApplicationResetIndicator
 * Description: Clear application reset indicator.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: None
 * Inout:  None
 * Output: None
 * Return: uint8: 0 - successful; 1 - failed
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2023/10/18    01077    create
 *********************************************************************************************************************/
extern uint8 Port_Hal_Esr_ClearAppResetIndicator(void);

/**********************************************************************************************************************
 * Function: Port_Hal_Esr_Init
 * Description: ESR pin initialization.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: pConfig: Pointer to port pin and controller configuration.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date          Author   Modified
 * 2023/05/29    01077    create
 *********************************************************************************************************************/
extern boolean Port_Hal_Esr_Init(const Port_EsrConfig *const pConfig);

#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

#endif /* PORT_HAL_ESR_H_ */

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
