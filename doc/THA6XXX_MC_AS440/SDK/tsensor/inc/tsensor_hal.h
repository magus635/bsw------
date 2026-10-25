/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    tsensor_hal.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of TSENSOR module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#tsensor_hal_h_REF_1:MISRAC2012-Rule-2.3;
* Justification:reason 1535 The members of the type are used in configuration-generated code.
*
*#tsensor_hal_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:reason 1534 The macros are reserved for upper layers
*
*#tsensor_hal_h_REF_3:MISRAC2012-Rule-11.4;
* Justification:reason 0303 Converting integers to object pointers to reduce register access complexity.
*
*#tsensor_hal_h_REF_4:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*/
#ifndef TSENSOR_HAL_H_
#define TSENSOR_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "tsensor_register.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^TSENSOR_INTERRUPT^ TSENSOR interrupt function enable/disable */
/* #Violation: tsensor_hal_h_REF_2 */
#define TSENSOR_INTERRUPT_ENABLE (0x1U)  /* Set TSENSOR interrupt function enable */
/* #Violation: tsensor_hal_h_REF_2 */
#define TSENSOR_INTERRUPT_DISABLE (0x0U) /* Set TSENSOR interrupt function disable */

/* ^TSENSOR_ALARM_MASK^ TSENSOR alarm mask enable/disable */
#define TSENSOR_ALARM_UNMASK (0x0U) /* Set TSENSOR alarm mask enable */
/* #Violation: tsensor_hal_h_REF_2 */
#define TSENSOR_ALARM_MASK (0x3U)   /* Set TSENSOR alarm mask disable */

/* ^TSENSOR_INTR_STATUS^ TSENSOR interrupt status */
/* #Violation: tsensor_hal_h_REF_2 */
#define TSENSOR_INTR_STATUS_COMPLETE (0x04U) /* TSENSOR sample completion interrupt status */

/* ^TSENSOR_ALARM_STATUS^ TSENSOR alarm status */
/* #Violation: tsensor_hal_h_REF_2 */
#define TSENSOR_ALARM_STATUS_UOF (0x02U) /* TSENSOR upper limit overflow status */
/* #Violation: tsensor_hal_h_REF_2 */
#define TSENSOR_ALARM_STATUS_LLU (0x08U) /* TSENSOR lower limit underflow status */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enumeration for Average times of TSENSOR sample results */
typedef enum
{
    TSENSOR_AVRTIMES_1 = 0U, /* Average times of TSENSOR sample results is 1  */
    TSENSOR_AVRTIMES_2,      /* Average times of TSENSOR sample results is 2  */
    TSENSOR_AVRTIMES_4,      /* Average times of TSENSOR sample results is 4  */
    TSENSOR_AVRTIMES_8,      /* Average times of TSENSOR sample results is 8  */
    TSENSOR_AVRTIMES_16      /* Average times of TSENSOR sample results is 16 */
} Tsensor_AvrTimes;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* TSENSOR configuration structure */
typedef struct
{
    Tsensor_AvrTimes avrTimes; /* TSENSOR temperature average times */
    boolean intEn;              /* Interrupt enable/disable, can be a value of TSENSOR_INTERRUPT */
    uint32 alarmMask;          /* Alarm mask enable/disable, can be a value of TSENSOR_ALARM_MASK */
    uint32 interval;           /* TSENSOR sample interval, with range (2ms-1.1h), unit is us, default 1s */
    float32 highLimit;         /* High temperature limit, default 145 */
    float32 lowLimit;          /* Low temperature limit, default -35 */
} Tsensor_Config;

#define TSENSOR_START_SEC_CODE_ASIL_D_GLOBAL
#include "Tsensor_MemMap.h"
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function :    Tsensor_Hal_Init
 * Description:  Initializing the TSENSOR module based on the configurations contained in the structure.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: Pointer to TSENSOR module configuration.
 *               pTsensor: Pointer to TSENSORx(x=0,1).
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the check for register value passes
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2024/03/27    01208     create
 *********************************************************************************************************************/
extern boolean Tsensor_Hal_Init(TSENSOR_MODULE *const pTsensor, const Tsensor_Config *const pConfig);

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Tsensor_Hal_GetResult
 * Description:  Get temperature result.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTsensor: Pointer to TSENSORx(x=0,1).
 * Inout:        None
 * Output:       pTemperature: Pointer to temperature value, TSENSOR actual Celsius degree temperature.
 * Return:       None
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2024/03/27    01208     create
 *********************************************************************************************************************/
extern void Tsensor_Hal_GetResult(const TSENSOR_MODULE *const pTsensor, float32 *const pTemperature);


/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function:     Tsensor_Hal_GetStatus
 * Description:  Get selected Tsensor status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTsensor : Pointer to TSENSORx(x=0,1).
 *               status: Select status to be read.
 * Inout:        None
 * Output:       None
 * Return:       uint32: TSENSOR flag status
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2024/03/27    01208     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Tsensor_Hal_GetStatus(const TSENSOR_MODULE *const pTsensor, uint32 status);

/**********************************************************************************************************************
 * Function   :  Tsensor_Hal_ClearStatus
 * Description:  Clear selected Tsensor status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTsensor: Pointer to TSENSORx(x=0,1).
 *               status: Select status to be cleared.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2024/03/27    01208     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Tsensor_Hal_ClearStatus(TSENSOR_MODULE *const pTsensor, uint32 status);

/**********************************************************************************************************************
 * Function:    Tsensor_Register_ReadBack_Check
 * Description: Checks whether the register value written is equal to the value read back 
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       expect: Read back the value of the registe
 *              value: value written to register
 *              state: Wrong initial state
 * Inout:       None
 * Output:      None
 * Return:      boolean: Flag indicating whether the value written to register is the same as the value read back
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2025/03/10   01368     create
 *********************************************************************************************************************/ 
LOCAL_FORCEINLINE boolean Tsensor_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define SARADC_REG_CHECK
#if defined(SARADC_REG_CHECK)
LOCAL_FORCEINLINE boolean Tsensor_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
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
LOCAL_FORCEINLINE boolean Tsensor_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/* #Violation: tsensor_hal_h_REF_1 */
LOCAL_FORCEINLINE uint32 Tsensor_Hal_GetStatus(const TSENSOR_MODULE *const pTsensor, uint32 status)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: tsensor_hal_h_REF_3 */
    /* #Violation: tsensor_hal_h_REF_4 */
    Assert((boolean)(CHECK_TSENSOR_BASE(pTsensor)));
#endif

    /* Read status */
    return pTsensor->STAT.U & status;
}

/* #Violation: tsensor_hal_h_REF_1 */
LOCAL_FORCEINLINE void Tsensor_Hal_ClearStatus(TSENSOR_MODULE *const pTsensor, uint32 status)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: tsensor_hal_h_REF_3 */
    /* #Violation: tsensor_hal_h_REF_4 */
    Assert((boolean)(CHECK_TSENSOR_BASE(pTsensor)));
#endif

    /* Clear status */
    pTsensor->CLEAR.U = status;
}

#define TSENSOR_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Tsensor_MemMap.h"

#endif /* TSENSOR_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
