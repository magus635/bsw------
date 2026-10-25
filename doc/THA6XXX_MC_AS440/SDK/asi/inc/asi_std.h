/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    asi_std.h
 * Author:      00101
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of internal functions.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #asi_std_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
* #asi_hal_h_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

#ifndef ASI_STD_H_
#define ASI_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "asi_register.h"
#include "compilertypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ASI Run State */
#define ASI_LINCR1_SLEEP_MODE_REQUEST   (0x02U)
#define ASI_SHORT_MASK                  (0xFFFFU)
#define ASI_FLAG_RESET                  (0x0U)
#define ASI_FLAG_SET                    (0x1U)

/* ASI Parameter Setting */
/* #Violation: asi_std_h_REF_1 */
#define ASI_INTEGER_BAUDRATE_MAX        (0xFFFFFU)
/* #Violation: asi_std_h_REF_1 */
#define ASI_FRACTIONAL_BAUDRATE_MAX     (0xFU)
/* #Violation: asi_std_h_REF_1 */
#define ASI_HEADER_FRAME_TIMEOUT_MAX    (0x7FU)
/* #Violation: asi_std_h_REF_1 */
#define ASI_RESPONSE_FRAME_TIMEOUT_MAX  (0x0FU)
#define ASI_LIN_IS_ERR_FLAG             (0x80000000U)
#define ASI_REG_BDRLM_BYTE_SHIFT_OFFSET (0x03U)
#define ASI_UART_WORDLENGTH_IS_7_8_BITS (0x0U)
#define ASI_UART_IS_MODE_FLAG           (0x80000000U)

/* ENABLE UART MODE: UARTCR.UART */
#define ASI_UART_ENABLE_UART_MODE       (0x01U)

/* ENABLE LIN MODE: UARTCR.UART */
#define ASI_LIN_ENABLE_LIN_MODE         (0x00U)
#define ASI_FUNCTION_ENABLE             (0x01U)
#define ASI_FUNCTION_DISABLE            (0x00U)
#define ASI_LIN_DFL_DEVIATION           (0x01U)
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
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: asi_std_h_REF_1 */
#define ASI_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: asi_std_h_REF_2 */
#include "Asi_MemMap.h"
/**********************************************************************************************************************
 * Function:     void Asi_Std_SetInterupt
 * Description:  Enable or disable LIN/UART interrupt(s).
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAsi: pointer to ASI module
 *               interrupt: specified interrupt(s)
 *               isEnabled: specified interrupt is enabled or disabled
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Asi_Std_SetInterupt(ASI_MODULE *const pAsi, uint32 interrupt, boolean isEnabled);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Asi_Std_SetInterupt(ASI_MODULE *const pAsi, uint32 interrupt, boolean isEnabled)
{
    if(TRUE == isEnabled)
    {
        pAsi->LINIER.U |= interrupt; /* enable interrupt */
    }
    else
    {
        pAsi->LINIER.U &= (uint32)~interrupt; /* disable interrupt */
    }
}
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     void Asi_Std_SetIntegerBaudRate 
 * Description:  Set LIN/UART integer baud rate.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAsi: pointer to ASI module
 *               baudRate: integer baud rate
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Std_SetIntegerBaudRate (ASI_MODULE *const pAsi, uint32 baudRate);

/**********************************************************************************************************************
 * Function:     void Asi_Std_SetFractionalBaudRate 
 * Description:  Set LIN/UART fractional baud rate.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAsi: pointer to ASI module
 *               baudRate: fractional baud rate
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Std_SetFractionalBaudRate (ASI_MODULE *const pAsi, uint32 baudRate);

/**********************************************************************************************************************
 * Function:     void Asi_Std_EnterInitMode
 * Description:  The module will enter INIT mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAsi: pointer to ASI module
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Std_EnterInitMode(ASI_MODULE *const pAsi);

/**********************************************************************************************************************
 * Function:     void Asi_Std_EnterNormalMode 
 * Description:  The module will enter NORMAL mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAsi: pointer to ASI module
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Std_EnterNormalMode (ASI_MODULE *const pAsi);

/* #Violation: asi_std_h_REF_1 */
#define ASI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: asi_std_h_REF_2 */
#include "Asi_MemMap.h"

#endif /* ASI_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/    
