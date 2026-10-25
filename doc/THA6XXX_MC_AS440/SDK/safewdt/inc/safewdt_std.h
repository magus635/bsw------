/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    safewdt_std.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/

/*
* #Violation Summary
*
* #safewdt_std_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #safewdt_std_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/

#ifndef SAFEWDT_STD_H_
#define SAFEWDT_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "safewdt_register.h"
#include "compilertypes.h"
#include "Platform_Types.h"
#include "regtypes.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
#define SAFEWDT_REG_CHECK

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
/* #Violation: safewdt_std_h_REF_2 */
#define SAFEWDT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: safewdt_std_h_REF_1 */
#include "Safewdt_MemMap.h"

/**********************************************************************************************************************
 * Function:    Safewdt_Register_ReadBack_Check
 * Description: Checks whether the register value written is equal to the value read back 
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       expect: Read back the value of the register
 *              value: value written to register
 *              state: Wrong initial state
 * Inout:        None
 * Output:      None
 * Return:      boolean: Flag indicating whether the value written to register is the same as the value read back
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2025/03/10   01744     create
 *********************************************************************************************************************/ 
LOCAL_FORCEINLINE boolean Safewdt_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(SAFEWDT_REG_CHECK)
LOCAL_FORCEINLINE boolean Safewdt_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
LOCAL_FORCEINLINE boolean Safewdt_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif
/**********************************************************************************************************************
 *                                           Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Safewdt_Std_ClearPw0
 * Description:  This function clears PW0 write protection guarding initialization registers.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Std_ClearPw0(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Std_SetPw0
 * Description:  This function sets PW0 write protection guarding initialization registers.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Std_SetPw0(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Std_ClearPwwdt
 * Description:  This function clears PWWDT write protection guarding feeding dog registers.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Std_ClearPwwdt(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Std_SetPwwdt
 * Description:  This function sets PWWDT write protection guarding feeding dog registers.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        coreId: Current core id
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Std_SetPwwdt(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Std_ClearPwse
 * Description:  This function clears PWSE write protection guarding Safety ENDINIT control registers.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Std_ClearPwse(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Std_SetPwse
 * Description:  This function sets PWSE write protection guarding Safety ENDINIT control registers.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        sePw: PWSE permission password
 *               coreId: Current core id
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Std_SetPwse(void);

/* #Violation: safewdt_std_h_REF_2 */
#define SAFEWDT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: safewdt_std_h_REF_1 */
#include "Safewdt_MemMap.h"
#endif /* SAFEWDT_STD_H_ */
/**********************************************************************************************************************
 *                                                    End of File
 *********************************************************************************************************************/
