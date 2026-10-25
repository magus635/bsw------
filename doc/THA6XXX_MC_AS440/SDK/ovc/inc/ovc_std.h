/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    ovc_std.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#ovc_std_h_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #ovc_std_h_REF_2:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 */

#ifndef OVC_INC_OVC_STD_H_
#define OVC_INC_OVC_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "ovc_register.h"
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
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* #Violation: ovc_std_h_REF_1 */
#define OVC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ovc_std_h_REF_2 */
#include "Ovc_MemMap.h"


/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function:     Ovc_Std_FinishOverlayConfig
 * Description:  This function set the overlay of core0 or core1 has been configured
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pOvc: pointer to the OVC module
 *               coreId: Core ID
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern boolean Ovc_Std_FinishOverlayConfig(OVC_MODULE *const pOvc, uint32 coreId);

/**********************************************************************************************************************
 * Function:     Ovc_Std_DisableOVSTARTandOVSTOP
 * Description:  This function disables the core for OVSTART and OVSTOP
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pOvc: pointer to the OVC module
 *               coreId: Core ID
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/01    01208     Create
 *********************************************************************************************************************/
extern boolean Ovc_Std_DisableOVSTARTandOVSTOP(OVC_MODULE *const pOvc, uint32 coreId);

/**********************************************************************************************************************
 * Function:     Ovc_Std_AddrAligCheck
 * Description:  This function check targetBaseAddress and redirectionBaseAddress alignment
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        targetBaseAddress: target base address
 *               redirectionBaseAddress: redirection base address
 *               blockSize: block size mask value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  targetBaseAddress and redirectionBaseAddress alignment
 *                   FALSE: targetBaseAddress and redirectionBaseAddress not alignment
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/09/13    01361     Create
 *********************************************************************************************************************/
extern boolean Ovc_Std_AddrAligCheck(uint32 targetBaseAddress, uint32 redirectionBaseAddress, uint32 blockSize);


#define OVC_REG_CHECK
#if defined(OVC_REG_CHECK)
LOCAL_FORCEINLINE boolean Ovc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
LOCAL_FORCEINLINE boolean Ovc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/* #Violation: ovc_std_h_REF_1 */
#define OVC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ovc_std_h_REF_2 */
#include "Ovc_MemMap.h"
#endif /* OVC_INC_OVC_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
