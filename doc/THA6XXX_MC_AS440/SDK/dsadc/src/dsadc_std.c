/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dsadc_std.c
 * Author:      30037
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all stander implementations of requirements of DSADC module.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #dsadc_std_c_REF_1:MISRAC2012-Rule-19.2
* Justification:Define a union type to assign a one-time value to a register.
*
* #dsadc_std_c_REF_2:MSC12-C;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
* #dsadc_std_c_REF_3:CWE-561;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block
*
* #dsadc_std_c_REF_4:CWE-570;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block
*
* #dsadc_std_c_REF_5:CWE-571;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
* #dsadc_std_c_REF_6:CWE-1071;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
* #dsadc_std_c_REF_7:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #dsadc_std_c_REF_8:MISRAC2012-Rule-8.9;
* Justification:Static global variables are placed in non-cached RAM regions to ensure accessibility by multiple cores.
*
* #dsadc_std_c_REF_9:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #dsadc_std_c_REF_10:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #dsadc_std_c_REF_11:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #dsadc_std_c_REF_12:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "dsadc_register.h"
#include "dsadc_std.h"
#include "tha6_cfg.h"
#if (STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif

#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dsadc_std_c_REF_11 */
#include "Dsadc_MemMap.h"

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function:     Dsadc_Std_log2_roundUp
 * Description:  log2 and round up
 * Input:        roundUpValue: variant
 * Inout:        None
 * Output:       None
 * Return:       uint32: result
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *  2024/12/12    00976     Modify: extern to static
 *********************************************************************************************************************/
static uint32 Dsadc_Std_log2_roundUp(uint32 roundUpValue);

/**********************************************************************************************************************
 * Function:     Dsadc_Std_power
 * Description:  Dsadc_Std_power function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        base: base variant
 *               exponent: exponent variant
 * Inout:        None
 * Output:       None
 * Return:       uint32: result
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/08    30037     Create
 *  2024/12/12    00976     Modify: extern to static
 *********************************************************************************************************************/
static uint32 Dsadc_Std_power(uint32 base, uint32 exponent);


/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static uint32 Dsadc_Std_log2_roundUp(uint32 roundUpValue)
{
    uint32 exponent = 0U;
    uint32 roundUp = 0U;
    uint32 roundUpValueTemp = roundUpValue;

    while (roundUpValueTemp >= LOG2_ROUNDUPLIMIT)
    {
        if((roundUpValueTemp % 2U) != 0U)
        {
            roundUp = roundUp + 1U;
        }
        else
        {
            /* Do nothing */
        } 
        roundUpValueTemp /= 2U;
        exponent++;
    }

    if(0U != roundUp)
    {
        roundUp = 1U;
    }

    return exponent + roundUp;
}



static uint32 Dsadc_Std_power(uint32 base, uint32 exponent) 
{
    uint32 i;
    uint32 result = 1;
    
    for (i = 0U; i < exponent; i++) {
        result *= base;
    }
    
    return result;
}
/**********************************************************************************************************************
 *                                            Global Variable Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
boolean Dsadc_Std_ConfigModulator(DSADC_MODULE *const pDsadc, const Dsadc_ModulatorConfig *const pConfig)
{
    boolean ret = TRUE;

/* for search Dsadc_CalibUCBAddr */
    uint32 dsadcIdx;
    uint32 pinmodeIdx;
    uint32 calSum1, calSum2;
    uint32 calibUCBAddr;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_COMP comp;

    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_MODCFG modCfgValue;
    modCfgValue.U = pDsadc->MODCFG.U;

    /* Set Positive input  */
    modCfgValue.B.PINEN = pConfig->positiveInputEnable;
    /* Set Negative input */
    modCfgValue.B.NINEN = pConfig->negativeInputEnable;
    /* Set positive input line */
    modCfgValue.B.PINSET = pConfig->positiveInputLine;
    /* Set negative input line */
    modCfgValue.B.NINSET = pConfig->negativeInputLine;
    /* Input pin selection */
    modCfgValue.B.INPSEL = pConfig->inputPin;
    /* Set input multiplexer control pattern */
    modCfgValue.B.INMCP = (uint32)pConfig->inputMultiplexerTriggerMode;
    /* Set input multiplexer changing control */
    modCfgValue.B.INMCC = pConfig->inputMultiplexerMode;
    /* Set automatic power control */
    modCfgValue.B.APC = pConfig->autoPowerControl;
    /* Gain select of analog input path */
    modCfgValue.B.PGAGSEL = (uint32)pConfig->pgaGain;

    /* Write enable */
    pDsadc->MODCFG.U |= (1UL<<21U) | (1UL<<15U);
    pDsadc->MODCFG.U = modCfgValue.U;
    ret = Dsadc_Register_ReadBack_Check(ret, (modCfgValue.U & MODCFG_CHKMSK), (pDsadc->MODCFG.U & MODCFG_CHKMSK));
    pDsadc->MODCFG.B.INPWP = 0U;
    pDsadc->MODCFG.B.MPSWP = 0U;

    /* #Violation: dsadc_std_c_REF_3 */
    #if defined(THA6_THA6206) || defined(THA6_THA6206D)
    volatile uint32 Dsadc_CalibUCBAddr[6][4] =
    {
           /* DSADC0     DSADC1      DSADC2      DSADC3  */
        {0x94405F00U, 0x94405F10U, 0x94405F20U, 0x94405F30U},    /* Single Negative B */
        {0x94405E40U, 0x94405E50U, 0x94405E60U, 0x94405E70U},    /* Single Negative A */
        {0x94405D80U, 0x94405D90U, 0x94405DA0U, 0x94405DB0U},    /* Single Positive B */
        {0x94405A00U, 0x94405A10U, 0x94405A20U, 0x94405A30U},    /* Single Positive A */
        {0x94405B00U, 0x94405B10U, 0x94405B20U, 0x94405B30U},    /* Differential B    */
        {0x94405900U, 0x94405910U, 0x94405920U, 0x94405930U},    /* Differential A    */
    };
    #endif /* THA6_THA6206 & THA6_THA6206D */

    /* #Violation: dsadc_std_c_REF_3 */
    #if defined(THA6_THA6412)
    volatile uint32 Dsadc_CalibUCBAddr[6][10] =
    {
           /* DSADC0     DSADC1      DSADC2      DSADC3        DSADC4       DSADC5        DSADC6      DSADC7       DSADC8       DSADC9     */
        {0x94405D80U, 0x94405D90U, 0x94405DA0U, 0x94405DB0U, 0x94405DC0U, 0x94405DD0U, 0x94405DE0U, 0x94405DF0U, 0x94405E00U, 0x94405E10U},    /* Single Negative B */
        {0x94405D80U, 0x94405D90U, 0x94405DA0U, 0x94405DB0U, 0x94405DC0U, 0x94405DD0U, 0x94405DE0U, 0x94405DF0U, 0x94405E00U, 0x94405E10U},    /* Single Negative A */
        {0x94405D80U, 0x94405D90U, 0x94405DA0U, 0x94405DB0U, 0x94405DC0U, 0x94405DD0U, 0x94405DE0U, 0x94405DF0U, 0x94405E00U, 0x94405E10U},    /* Single Positive B */
        {0x94405D80U, 0x94405D90U, 0x94405DA0U, 0x94405DB0U, 0x94405DC0U, 0x94405DD0U, 0x94405DE0U, 0x94405DF0U, 0x94405E00U, 0x94405E10U},    /* Single Positive A */
        {0x94405900U, 0x94405910U, 0x94405920U, 0x94405930U, 0x944059C0U, 0x944059D0U, 0x944059E0U, 0x944059F0U, 0x94405A80U, 0x94405A90U},    /* Differential B    */
        {0x94405900U, 0x94405910U, 0x94405920U, 0x94405930U, 0x944059C0U, 0x944059D0U, 0x944059E0U, 0x944059F0U, 0x94405A80U, 0x94405A90U},    /* Differential A    */
    };
    #endif /* THA6_THA6412 */
    /* set calibration scheme according to pin mode selection */
    /*
                        DSADC Input Channel Configuration
        Mode                PINEN   NINEN   PINSET  NINSET  INPSEL  | SUM | pinmodeIdx
        Single Negative B   0       1       0       1       0       | 2   | 0 (2-2)
        Single Negative A   0       1       0       1       1       | 3   | 1 (3-2)
        Single Positive B   1       0       1       0       0       | 2   | 2
        Single Positive A   1       0       1       0       1       | 3   | 3
        Differential B      1       1       1       1       0       | 4   | 4
        Differential A      1       1       1       1       1       | 5   | 5
    */
   calSum1 = (uint32)modCfgValue.B.PINEN + (uint32)modCfgValue.B.NINEN + (uint32)modCfgValue.B.PINSET + (uint32)modCfgValue.B.NINSET + (uint32)modCfgValue.B.INPSEL;
   calSum2 = (uint32)modCfgValue.B.PINEN + (uint32)modCfgValue.B.NINEN + (uint32)modCfgValue.B.PINSET;

   if (((2U == calSum1) || (3U == calSum1)) && (1U == calSum2))
   {
        /* Single Negative B(calSum1 = 2) or Single Negative A(calSum1 = 3) */
        pinmodeIdx = calSum1 - 2UL;
   }
   else
   {
        pinmodeIdx = calSum1;
   }

    /* #Violation: dsadc_std_c_REF_5 */
    /* #Violation: dsadc_std_c_REF_7 */
    /* #Violation: dsadc_std_c_REF_12 */
   dsadcIdx = GET_DSADC_MODULE_NUM(pDsadc);

   calibUCBAddr = Dsadc_CalibUCBAddr[pinmodeIdx][dsadcIdx];

   /* #Violation: dsadc_std_c_REF_7 */
   comp.U = *(uint32*)calibUCBAddr;

   comp.B.GCOFFSET = comp.B.GCOFFSET >> 1UL;

   pDsadc->COMP.U = comp.U;
   
   ret = Dsadc_Register_ReadBack_Check(ret, (comp.U), (pDsadc->COMP.U));
    return ret;
}

boolean Dsadc_Std_ConfigDemodulator(DSADC_MODULE *const pDsadc, const Dsadc_DemodulatorConfig *const pConfig)
{
    /******************************************************
     * Usage Restrictions
     * - Conversion result display(RDP bit) can only be 
     *   configured as 0(signed mode) in THA6206 and THA6412, 
     *   please refer to errata.
     *******************************************************/
    boolean ret = TRUE;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_DEMICFG demcfg;
    demcfg.U = pDsadc->DEMICFG.U;

    /* Trigger select  */
    demcfg.B.TRGSEL = (uint32)pConfig->triggerSource;
    /* Set conversion result display pattern */
    demcfg.B.RDP = pConfig->resultDisplayMode;
    
    /* signed mode */
    if (0U == pConfig->resultDisplayMode)
    {
        /* Write enable */
        pDsadc->DEMICFG.B.MSWP = 1U;
        pDsadc->DEMICFG.U = demcfg.U;
        pDsadc->DEMICFG.B.MSWP = 0U;
        ret = Dsadc_Register_ReadBack_Check(ret, (demcfg.U & DEMICFG_CHKMSK), (pDsadc->DEMICFG.U & DEMICFG_CHKMSK));
    }
    else
    {
        /* unsigned mode is not supported */
        ret = FALSE;
    }

    return ret;
}

boolean Dsadc_Std_ConfigTimeStamp(DSADC_MODULE *const pDsadc, const Dsadc_TimeStampConfig *const pConfig)
{
    boolean ret = TRUE;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_DEMICFG demcfg;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_TSCNT tsCntValue;
    demcfg.U = pDsadc->DEMICFG.U;
    tsCntValue.U = pDsadc->TSCNT.U;

    /* Set Timestamp pattern  */
    demcfg.B.TSP = 1U;
    /* Set Timestamp trigger pattern */
    demcfg.B.TSTRP = (uint32)pConfig->mode;

    /* Write enable */
    pDsadc->DEMICFG.B.MSWP = 1U;
    pDsadc->DEMICFG.U = demcfg.U;
    pDsadc->DEMICFG.B.MSWP = 0U;
    ret = Dsadc_Register_ReadBack_Check(ret, (demcfg.U & DEMICFG_CHKMSK), (pDsadc->DEMICFG.U & DEMICFG_CHKMSK));

    /* Write enable */
    pDsadc->MODCFG.B.MPSWP = 1U;
    /* Set Frequency divider cofficient */
    pDsadc->MODCFG.B.FDIVC = pConfig->timeStampFrequency;
    pDsadc->MODCFG.B.MPSWP = 0U;
    ret = Dsadc_Register_ReadBack_Check(ret, (pConfig->timeStampFrequency & MODCFG_CHKMSK),
                                         (pDsadc->MODCFG.B.FDIVC & MODCFG_CHKMSK));

    /* Timestamp counter clock selection  */
    tsCntValue.B.TSCCS = (uint32)pConfig->divider;
    /* Analog multiple sector copy enable  */
    tsCntValue.B.AMSCEN = pConfig->multiplexerCopyEnable;
    /* Set Timestamp counter start control */
    tsCntValue.B.TSCSC = pConfig->start;

    pDsadc->TSCNT.U = tsCntValue.U;
    ret = Dsadc_Register_ReadBack_Check(ret, (tsCntValue.U & TSCNT_CHKMSK), (pDsadc->TSCNT.U & TSCNT_CHKMSK));

    return ret;
}

boolean Dsadc_Std_ConfigThreshold(DSADC_MODULE *const pDsadc, const Dsadc_ThresholdConfig *const pConfig)
{
    boolean ret = TRUE;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_THRESLM threslmValue;
    threslmValue.U = pDsadc->THRESLM.U;

    /* Set Threshold check lower limit  */
    threslmValue.B.TCLL = pConfig->thresholdLower;
    /* Set Threshold check upper limit */
    threslmValue.B.TCUL = pConfig->thresholdUpper;

    pDsadc->THRESLM.U = threslmValue.U;
    ret = Dsadc_Register_ReadBack_Check(ret, (threslmValue.U), (pDsadc->THRESLM.U));

    return ret;

}

boolean Dsadc_Std_ConfigMainFilter(DSADC_MODULE *const pDsadc, const Dsadc_MainFilterConfig *const pConfig)
{
    boolean ret = TRUE;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_MFCFG mfCfgValue;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_GAINCTR gainCtrValue;
    uint32 cicgain;
    uint32 calVar0;
    float32 calVar1;

    mfCfgValue.U = pDsadc->MFCFG.U;
    gainCtrValue.U = pDsadc->GAINCTR.U;

    if(1U == pConfig->cicFilterEnable)
    {
        /* Main CIC filter enable  */
        mfCfgValue.B.MCFEN = 1U;
        /* Set Main CIC filter sampling factor */
        mfCfgValue.B.MCFSF = pConfig->cicFilterSampling;
        /* Main CIC parallel series selection */
        mfCfgValue.B.MCPS = (uint32)pConfig->parallel;
        
        cicgain = Dsadc_Std_power(mfCfgValue.B.MCFSF + (uint32)1U , mfCfgValue.B.MCPS + (uint32)1U);

        mfCfgValue.B.MCGSL = Dsadc_Std_log2_roundUp(cicgain);

        /* Fine gain offset enable  */
        gainCtrValue.B.GAINOFFEN = 1U;
        /* Fine gain offset config  */
        calVar0 = Dsadc_Std_power(2U,((uint32)mfCfgValue.B.MCGSL));
        calVar1 = (float32)calVar0/(float32)cicgain;

        calVar0 = Dsadc_Std_power(2U,((uint32)7U));
        calVar1 = (calVar1*(float32)calVar0) + 0.5f;

        gainCtrValue.B.GAINOFF = (uint32)(calVar1);

        pDsadc->GAINCTR.U = gainCtrValue.U;
        ret = Dsadc_Register_ReadBack_Check(ret, (gainCtrValue.U & GAINCTR_CHKMSK),
                                             (pDsadc->GAINCTR.U & GAINCTR_CHKMSK));



    }
    else
    {
        /* Main CIC filter disable  */
        mfCfgValue.B.MCFEN = 0U;
    }

    /* Main generation service request configuration */
    mfCfgValue.B.MGSRC = (uint32)pConfig->request;
    /* Main alarm generation condition selection */
    mfCfgValue.B.MAGCS = (uint32)pConfig->condition;

    if(1U == pConfig->fir0Enable)
    {
        /* Set FIR0 output enable */
        mfCfgValue.B.FIR0FEN = 1U;
        /* Set FIR0 output shift */
        mfCfgValue.B.FIR0OSF = pConfig->firOffset0;
        /* Set FIR0 filter decimation rate */
        mfCfgValue.B.FIR0DEC = pConfig->decimationRate0;
    }
    else
    {
         /* Set FIR0 output disable */
        mfCfgValue.B.FIR0FEN = 0U;
    }

    if(1U == pConfig->fir1Enable)
    {
        /* Set FIR1 output enable */
        mfCfgValue.B.FIR1FEN = 1U;
        /* Set FIR1 output shift */
        mfCfgValue.B.FIR1OSF = (uint32)pConfig->firOffset1;
        /* Set FIR1 filter decimation rate */
        mfCfgValue.B.FIR1DEC = pConfig->decimationRate1;
    }
    else
    {
        /* Set FIR1 output disable */
        mfCfgValue.B.FIR1FEN = 0U;
    }

    /* Offset compensation filter configuration */
    mfCfgValue.B.OCENCFG = (uint32)pConfig->offsetCompensation;

    pDsadc->MFCFG.U = mfCfgValue.U;
    ret = Dsadc_Register_ReadBack_Check(ret, (mfCfgValue.U & MFCFG_CHKMSK), (pDsadc->MFCFG.U & MFCFG_CHKMSK));

    return ret;

}

boolean Dsadc_Std_ConfigMean(DSADC_MODULE *const pDsadc, const Dsadc_MeanConfig *const pConfig)
{
    boolean ret = TRUE;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_INTERCON interValue;
    interValue.U = pDsadc->INTERCON.U;

    /* Set MEAN bypass */
    pDsadc->MFCFG.B.INTERBYPASS = 0U;
    ret = Dsadc_Register_ReadBack_Check(ret, 0U, pDsadc->MFCFG.B.INTERBYPASS);

    /* Set Shift length control */
    interValue.B.SFL = (uint32)pConfig->shiftLength;
    /* Set Mean mode */
    interValue.B.MODE = pConfig->meanMode;
    /* Set Mean Points */
    interValue.B.LEN = pConfig->meanPoint;

    pDsadc->INTERCON.U = interValue.U;
    ret = Dsadc_Register_ReadBack_Check(ret, (interValue.U & INTERCON_CHKMSK), (pDsadc->INTERCON.U & INTERCON_CHKMSK));

    return ret;
}

boolean Dsadc_Std_ConfigAuxFilter(DSADC_MODULE *const pDsadc, const Dsadc_AuxiliaryFilterConfig *const pConfig)
{
    boolean ret = TRUE;
    /* #Violation: dsadc_std_c_REF_1 */
    DSADC_AFCFG afCfgValue;
    uint32 cicgain;
    afCfgValue.U = pDsadc->AFCFG.U;

    /* Auxiliary alarm generation condition selection  */
    afCfgValue.B.AAGCS = pDsadc->MFCFG.B.MAGCS;
    /* Auxiliary channel service request config */
    afCfgValue.B.AGSRC = pConfig->request;
    /*  Set Auxiliary channel CIC filter parallel */
    afCfgValue.B.ACPS = (uint32)pConfig->parallel;
    /* Set Auxiliary channel CIC filter sampling factor */
    afCfgValue.B.ACFDF = pConfig->auxiliaryCicFilterSampling;

    cicgain = Dsadc_Std_power(afCfgValue.B.ACFDF + (uint32)1U , afCfgValue.B.ACPS + (uint32)1U);

    /* Set Auxiliary CIC gain shift length */
    afCfgValue.B.ACGSL = Dsadc_Std_log2_roundUp(cicgain);
    /* Set Auxiliary cic Filter Enable */
    afCfgValue.B.ACFEN = pConfig->cicFilterEnable;

    pDsadc->AFCFG.U = afCfgValue.U;
    ret = Dsadc_Register_ReadBack_Check(ret, (afCfgValue.U & AFCFG_CHKMSK), (pDsadc->AFCFG.U & AFCFG_CHKMSK));

    return ret;
}

boolean Dsadc_Std_ConfigFifo(DSADC_MODULE *const pDsadc, const Dsadc_FifoConfig *const pConfig)
{
    boolean ret = TRUE;

    /* Set Fifo Enable */
    pDsadc->DEMICFG.B.FIFOBYPASS = 0U;
    ret = Dsadc_Register_ReadBack_Check(ret, 0U, pDsadc->DEMICFG.B.FIFOBYPASS);
    /* Set Service request FIFO value */
    pDsadc->RFCON.B.SRLVAL = (uint32)pConfig->fifoThreshold;
    ret = Dsadc_Register_ReadBack_Check(ret, (uint32)pConfig->fifoThreshold, pDsadc->RFCON.B.SRLVAL);

    return ret;
}

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dsadc_std_c_REF_11 */
#include "Dsadc_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
