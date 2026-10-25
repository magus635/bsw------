/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    ovc_std.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of OVC module.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#ovc_std_c_REF_1:MISRAC2012-Dir-11.4;
 * Justification: Converting integers to object pointers to reduce register access complexity.
 *
 * #ovc_std_c_REF_2:MISRAC2012-Dir-4.9;
 * Justification: Function like macros are used to reduce code complexity.
 *
 * #ovc_std_c_REF_3:MISRAC2012-Rule-10.5;
 * Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
 * 
 * #ovc_std_c_REF_4:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #ovc_std_c_REF_5:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 *
 */

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "ovc_register.h"
#include "ovc_std.h"
#include "multicore.h"
#include "tha6_cfg.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /*INPUT_ARG_DETECT*/
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define OVC_STD_DISABLE_MASK (0x00000001U)
#define OVC_STD_ADDRALIG_MASK (0xFFFE0000U)
/* #Violation: ovc_std_c_REF_4 */
#define OVC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ovc_std_c_REF_5 */
#include "Ovc_MemMap.h"

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/

boolean Ovc_Std_FinishOverlayConfig(OVC_MODULE *const pOvc, uint32 coreId)
{
    boolean ret;
    ret = TRUE;
    uint32 ovcConf;

    /* Bit 29 Write Protection for OVCONF */
    pOvc->CTR.B.POVCONF = 1U;
    ret = Ovc_Register_ReadBack_Check(ret, (uint32)1U, pOvc->CTR.B.POVCONF);
    /* Bit 25 Overlay Configured 1, Bit 24 Overlay Configured 0*/
    ovcConf = (uint32)((uint32)1U << (coreId));
    pOvc->CTR.B.OVCONF = ovcConf;
    ret = Ovc_Register_ReadBack_Check(ret, ovcConf, pOvc->CTR.B.OVCONF);

    return ret;
}

boolean Ovc_Std_DisableOVSTARTandOVSTOP(OVC_MODULE *const pOvc, uint32 coreId)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    regVal = pOvc->CTR.U;
    regVal &= ~((uint32)OVC_STD_DISABLE_MASK << coreId);
    /* Value 0 for OVSTART and OVSTOP are un-applied to core0 or core 1*/
    pOvc->CTR.U = regVal;
    /* #Violation: ovc_std_c_REF_1 */
    ret = Ovc_Register_ReadBack_Check(ret, regVal, pOvc->CTR.U);

    return ret;
}


boolean Ovc_Std_AddrAligCheck(uint32 targetBaseAddress, uint32 redirectionBaseAddress, uint32 blockSize)
{
    boolean ret;
    uint32 mask;
    ret = FALSE;

    mask = OVC_STD_ADDRALIG_MASK | (blockSize << 5U);

    if(((targetBaseAddress | mask) == mask) && ((redirectionBaseAddress | mask) == mask))
    {
        ret = TRUE;
    }
    
    return ret;
}

/* #Violation: ovc_std_c_REF_4 */
#define OVC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ovc_std_c_REF_5 */
#include "Ovc_MemMap.h"
/**********************************************************************************************************************
**                                                    End of File                                                    **
**********************************************************************************************************************/
