/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    cpuwdt_std.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* *#cpuwdt_hal_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* *#cpuwdt_hal_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
 #ifndef CPUWDT_STD_H_
#define CPUWDT_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "multicore.h"
#include "cpuwdt_register.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
#define CPUWDT_REG_CHECK

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
/* #Violation: cpuwdt_hal_h_REF_2 */
#define CPUWDT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpuwdt_hal_h_REF_1 */
#include "Cpuwdt_MemMap.h"

/**********************************************************************************************************************
 * Function:    Cpuwdt_Register_ReadBack_Check
 * Description: Checks whether the register value written is equal to the value read back
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       expect: Read back the value of the register
 *              value: value written to register
 *              state: Wrong initial state
 * Inout:       None
 * Output:      None
 * Return:      boolean: Flag indicating whether the value written to register is the same as the value read back
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2025/03/10   01744     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Cpuwdt_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(CPUWDT_REG_CHECK)
LOCAL_FORCEINLINE boolean Cpuwdt_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
LOCAL_FORCEINLINE boolean Cpuwdt_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
 * Function:     Cpuwdt_Std_ClearPw0
 * Description:  This function clears PW0 write protection guarding initialization registers.
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
extern boolean Cpuwdt_Std_ClearPw0(MultiCoreID coreId);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Std_SetPw0
 * Description:  This function sets PW0 write protection guarding initialization registers.
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
extern boolean Cpuwdt_Std_SetPw0(MultiCoreID coreId);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Std_ClearPwwdt
 * Description:  This function clears PWWDT write protection guarding feeding dog registers.
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
extern boolean Cpuwdt_Std_ClearPwwdt(MultiCoreID coreId);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Std_SetPwwdt
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
extern boolean Cpuwdt_Std_SetPwwdt(MultiCoreID coreId);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Std_ClearPwce
 * Description:  This function clears PWCE write protection guarding ENDINIT control registers.
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
extern boolean Cpuwdt_Std_ClearPwce(MultiCoreID coreId);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Std_SetPwce
 * Description:  This function sets PWCE write protection guarding ENDINIT control registers.
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
extern boolean Cpuwdt_Std_SetPwce(MultiCoreID coreId);

/* #Violation: cpuwdt_hal_h_REF_2 */
#define CPUWDT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpuwdt_hal_h_REF_1 */
#include "Cpuwdt_MemMap.h"
#endif /* CPUWDT_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
