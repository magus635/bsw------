/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    rdc_std.c
 * Author:      00915
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: RDC standard driver source file.
 *              This file contains implementations for RDC standard driver.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #rdc_std_c_REF_1:MISRAC2012-Rule-19.2;
* Justification:Define a union type to assign a one-time value to a register.
*
* #rdc_std_c_REF_2:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core, Boolean can only be represents as uint8.
*
* #rdc_std_c_REF_3:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #rdc_std_c_REF_4:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #rdc_std_c_REF_5:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
* #rdc_std_c_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "rdc_std.h"
#include "rdc_register.h"

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define RDC_18TH_POWER_OF2 (262143.0f)
#define RDC_14TH_POWER_OF2 (16384.0f)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/

#define RDC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rdc_std_c_REF_6 */
#include "Rdc_MemMap.h"

boolean Rdc_Std_SetSoftExcitationCarrierDuty(const Rdc_CarrierPoints *const points)
{
    boolean ret = TRUE;
    uint8 num;
    /* #Violation: rdc_std_c_REF_1 */
    RDC_CWDR cwdr_temp;
    /* #Violation: rdc_std_c_REF_1 */
    RDC_CWPOINTS cwpoints_temp;
    cwdr_temp.U = 0U;
    cwpoints_temp.U = 0U;

    for(num = 0U; num < RDC_MAX_EXCITATION_CARRIER_POINTS; num++)
    {
        cwdr_temp.B.CW_NEG = points->position[num].neg_position;
        cwdr_temp.B.CW_POS = points->position[num].pos_position;
        /* #Violation: rdc_std_c_REF_3 */
        RDC0->CWDRx[num].U = cwdr_temp.U;
        /* #Violation: rdc_std_c_REF_3 */
        ret = Rdc_Register_ReadBack_Check(ret, cwdr_temp.U, RDC0->CWDRx[num].U);
    }
    cwpoints_temp.B.CW_POINTS = points->carrier_points;
    cwpoints_temp.B.TOTAL_POINTS = points->total_points;
    /* #Violation: rdc_std_c_REF_3 */
    RDC0->CWPOINTS.U = cwpoints_temp.U;
    /* #Violation: rdc_std_c_REF_3 */
    ret = Rdc_Register_ReadBack_Check(ret, cwpoints_temp.U, RDC0->CWPOINTS.U);
    return ret;
}


boolean Rdc_Std_SetDpllPidConfig(RDC_MODULE *const pRdc, float32 kpData, float32 kiData)
{
    boolean ret = TRUE;
    float32 pid_temp;

    if((kpData >= 0.0f) && (kpData <= 1.0f))
    {
        pid_temp = kpData * RDC_18TH_POWER_OF2;
        pRdc->DPLLKP.B.KP = (uint32)(pid_temp);
        ret = Rdc_Register_ReadBack_Check(ret, (uint32)pid_temp, pRdc->DPLLKP.B.KP);
    }
    else
    {
        ret = FALSE;
    }

    if((kiData >= 0.0f) && (kiData <= 1.0f))
    {
        pid_temp = kiData * RDC_18TH_POWER_OF2;
        pRdc->DPLLKI.B.KI = (uint32)(pid_temp);
        ret = Rdc_Register_ReadBack_Check(ret, (uint32)pid_temp, pRdc->DPLLKI.B.KI);
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

boolean Rdc_Std_SetMainPidConfig(RDC_MODULE *const pRdc, float32 kpData, float32 kiData)
{
    boolean ret = TRUE;
    float32 pid_temp;

    if((kpData >= 0.0f) && (kpData <= 1.0f))
    {
        pid_temp = kpData * RDC_18TH_POWER_OF2;
        pRdc->MAINKP.B.KP = (uint32)(pid_temp);
        ret = Rdc_Register_ReadBack_Check(ret, (uint32)pid_temp, pRdc->MAINKP.B.KP);
    }
    else
    {
        ret = FALSE;
    }

    if((kiData >= 0.0f) && (kiData <= 1.0f))
    {
        pid_temp = kiData * RDC_18TH_POWER_OF2;
        pRdc->MAINKI.B.KI = (uint32)(pid_temp);
        ret = Rdc_Register_ReadBack_Check(ret, (uint32)pid_temp, pRdc->MAINKI.B.KI);
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: rdc_std_c_REF_1 */
boolean Rdc_Std_SetDcCompensation(RDC_MODULE *const pRdc, Rdc_CompensationEn enable, sint16 iOffset, sint16 qOffset)
{
    boolean ret = TRUE;
    /* #Violation: rdc_std_c_REF_1 */
    RDC_DCOFFSET dcoffValue;
    dcoffValue.U = 0U;

    if(RDC_COMPENSATIONEN_ENABLE == enable)
    {
        dcoffValue.B.DOCI = iOffset;
        dcoffValue.B.DOCQ = qOffset;
        pRdc->DCOFFSET.U = dcoffValue.U;
        ret = Rdc_Register_ReadBack_Check(ret, dcoffValue.U, pRdc->DCOFFSET.U);
    }
    pRdc->RECFG.B.DCBYPASS = (uint32)enable;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)enable, pRdc->RECFG.B.DCBYPASS);

    return ret;
}

boolean Rdc_Std_SetGainCompensation(RDC_MODULE *const pRdc, Rdc_CompensationEn enable, float32 gain)
{
    boolean ret = TRUE;
    float32 gain_temp;

    if(RDC_COMPENSATIONEN_ENABLE == enable)
    {   if((gain > 0.0f) && (gain < 2.0f))
        {
            gain_temp = gain * RDC_14TH_POWER_OF2;
            pRdc->GAINOFFSET.B.GCOFFSETI = (uint32)(gain_temp);
            ret = Rdc_Register_ReadBack_Check(ret, (uint32)(gain_temp), pRdc->GAINOFFSET.B.GCOFFSETI);
        }
        else
        {
            ret = FALSE;
        }
    }
    pRdc->RECFG.B.GCBYPASS = (uint32)enable;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)enable, pRdc->RECFG.B.GCBYPASS);

    return ret;
}

boolean Rdc_Std_SetHighPassCompensation(RDC_MODULE *const pRdc, Rdc_CompensationEn enable, Rdc_FilterCutoffFrequency freqLevel)
{
    boolean ret = TRUE;

    if(RDC_COMPENSATIONEN_ENABLE == enable)
    {
        pRdc->RECFG.B.HPFCFG = (uint32)freqLevel;
        ret = Rdc_Register_ReadBack_Check(ret, (uint32)(freqLevel), pRdc->RECFG.B.HPFCFG);
    }
    pRdc->RECFG.B.HPFBYPASS = (uint32)enable;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)enable, pRdc->RECFG.B.HPFBYPASS);

    return ret;
}

#define RDC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rdc_std_c_REF_6 */
#include "Rdc_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
