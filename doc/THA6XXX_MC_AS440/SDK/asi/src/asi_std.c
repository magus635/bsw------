/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    asi_std.c
 * Author:      00101
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all internal functions of ASI Driver
 *********************************************************************************************************************/

/*
* #Violation Summary
*
* #asi_std_c_REF_1:MISRAC2012-Rule-19.2;
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*               code review.
*
* #asi_std_c_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #asi_std_c_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "asi_std.h"
#include "asi_register.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* ASI LIN Initiate Mode Request */
#define ASI_LINCR1_INIT_MODE_REQUEST  (0x01U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: asi_std_c_REF_3 */
#define ASI_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: asi_std_c_REF_2 */
#include "Asi_MemMap.h"

void Asi_Std_SetIntegerBaudRate(ASI_MODULE *const pAsi, uint32 baudRate)
{
    pAsi->LINIBRR.U = baudRate;
}

void Asi_Std_SetFractionalBaudRate(ASI_MODULE *const pAsi, uint32 baudRate)
{
    pAsi->LINFBRR.U = baudRate;
}

void Asi_Std_EnterInitMode(ASI_MODULE *const pAsi)
{
    /* #Violation: asi_std_c_REF_1 */
    ASI_LINCR1 lincr1Reg;

    lincr1Reg.U = pAsi->LINCR1.U;

    /* Exit Sleep Mode */
    if(ASI_LINCR1_SLEEP_MODE_REQUEST == (lincr1Reg.U & ASI_LINCR1_SLEEP_MODE_REQUEST))
    {
        lincr1Reg.B.SLEEP = 0U;
    }

    /* Enter INIT Mode */
    lincr1Reg.B.INITREQ = 1U;

    pAsi->LINCR1.U = lincr1Reg.U;
}

void Asi_Std_EnterNormalMode(ASI_MODULE *const pAsi)
{
    /* Exit NORMAL Mode */
    pAsi->LINCR1.U &= ~ASI_LINCR1_INIT_MODE_REQUEST; 
}

/* #Violation: asi_std_c_REF_3 */
#define ASI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: asi_std_c_REF_2 */
#include "Asi_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
