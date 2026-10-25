/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    i2c_std.c
 * Author:      01107
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of i2c module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*#i2c_std_c_REF_1:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers
*
*#i2c_std_c_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "i2c_std.h"
#include "tha6_cfg.h"
#include "compilertypes.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Structure Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: i2c_std_c_REF_2 */
#include "I2c_MemMap.h"

/**********************************************************************************************************************
 * Function:     I2c_Std_CheckBaudrateParameter
 * Description:  Check whether these I2C parameters, including baud rate, and duty cycle are correct.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        coreFrequency: The I2C peripheral frequency.
 *               busSpeed: I2C speed, e.g., 100Kbps is value-100000, 400Kbps value is value-400000
 *               dutyCycle: only for I2C fast or I2C fast + mode. This parameter can be one of the following values
 *               I2C_DutyCycle_2
 *               I2C_DutyCycle_16_9.
 *               pi2cType: pointer holding the I2C mode configuration
 * Inout:        None
 * Output:       None
 * Return:       I2c_Std_Status: detail see I2c_Std_Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/03    01358     Create
 *********************************************************************************************************************/
static I2c_Std_Status I2c_Std_CheckBaudrateParameter(uint32 coreFrequency, uint32 busSpeed, uint32 dutyCycle, uint32* const pi2cType);

/**********************************************************************************************************************
 * Function:     I2c_Std_SetBaudrate
 * Description:  Set I2C baud rate, duty cycle, F/S mode, TRISE.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pI2c: Pointer to the I2C module.
 *               coreFrequency: The I2C peripheral frequency.
 *               busSpeed: I2C speed, e.g., 100Kbps is value-100000, 400Kbps value is value-400000
 *               dutyCycle: only for I2C fast or I2C fast + mode. This parameter can be one of the following values
 *               I2C_DutyCycle_2
 *               I2C_DutyCycle_16_9.
 * Inout:        None
 * Output:       None
 * Return:       I2c_Std_Status: detail see I2c_Std_Status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/03/21    01107     Create
 *********************************************************************************************************************/
static I2c_Std_Status I2c_Std_SetBaudrate(I2C_MODULE *const pI2c, uint32 coreFrequency, uint32 busSpeed, uint32 dutyCycle);

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static I2c_Std_Status I2c_Std_CheckBaudrateParameter(uint32 coreFrequency, uint32 busSpeed, uint32 dutyCycle, uint32* const pi2cType)
{
    I2c_Std_Status status;

    status = I2C_STD_STATUS_OK;

    /* The output clock to be configured is within a valid range (122Hz~100KHz), and the AHB clock is greater than or equal to 2M */
    if((100000U >= busSpeed) && (122U < busSpeed) && (2000000U <= coreFrequency))
    {
        *pi2cType = I2C_STD_SPEED_MODE_STANDARD;
    }
    /* Fast mode(100 ~ 400Khz) with duty cycle is 2 at least 5Mhz */
    /* The output clock to be configured is within a valid range (100KHz~400KHz), the duty cycle mode is equal to I2C_STD_DUTYCYCLE_2, 
       and the AHB clock is greater than or equal to 5 MHz */
    else if((400000U >= busSpeed) && (100000U < busSpeed) && (I2C_STD_DUTYCYCLE_2 == dutyCycle) && (5000000U <= coreFrequency))
    {
        *pi2cType = I2C_STD_SPEED_MODE_FAST;
    }
    /* Fast mode(100 ~ 400Khz) with duty cycle is 16/9 at least 10Mhz */
    /* The output clock to be configured is within a valid range (100KHz~400KHz), the duty cycle mode is equal to I2C_STD_DUTYCYCLE_16_9, 
       and the AHB clock is greater than or equal to 10 MHz */
    else if ((400000U >= busSpeed) && (100000U < busSpeed) && (I2C_STD_DUTYCYCLE_16_9 == dutyCycle) && (10000000U <= coreFrequency))
    {
        *pi2cType = I2C_STD_SPEED_MODE_FAST;
    }
    /* Fast+(400 ~ 1Mhz) with duty cycle is 2 at least 12Mhz */
    /* The output clock to be configured is within a valid range (400KHz~1MHz), the duty cycle mode is equal to I2C_STD_DUTYCYCLE_2, 
       and the AHB clock is greater than or equal to 12 MHz */
    else if((1000000U >= busSpeed) && (400000U < busSpeed) && (I2C_STD_DUTYCYCLE_2 == dutyCycle) && (12000000U <= coreFrequency))
    {
        *pi2cType = I2C_STD_SPEED_MODE_FAST_PLUS;
    }
    /* Fast+(400 ~ 1Mhz) with duty cycle is 16/9 at least 25Mhz */
    /* The output clock to be configured is within a valid range (400KHz~1MHz), the duty cycle mode is equal to I2C_STD_DUTYCYCLE_16_9, 
       and the AHB clock is greater than or equal to 25 MHz */
    else if((1000000U >= busSpeed) && (400000U < busSpeed) && (I2C_STD_DUTYCYCLE_16_9 == dutyCycle) && (25000000U <= coreFrequency))
    {
        *pi2cType = I2C_STD_SPEED_MODE_FAST_PLUS;
    }
    /* High speed(1Mhz ~ 3.4Mhz) at least 40Mhz */
    /* The output clock to be configured is within a valid range (1MHz~3.4MHz), and the AHB clock is greater than or equal to 40M */
    else if((3400000U >= busSpeed) && (1000000U < busSpeed) && (40000000U <= coreFrequency))
    {    
        *pi2cType = I2C_STD_SPEED_MODE_HIGH;
    }
    else
    {
        status = I2C_STD_STATUS_PARAM_ERROR;
    }  

    return status;
}

static I2c_Std_Status I2c_Std_SetBaudrate(I2C_MODULE *const pI2c, uint32 coreFrequency, uint32 busSpeed, uint32 dutyCycle)
{
    I2c_Std_Status status;
    uint32 freqrange;
    uint32 ccrValue;
    uint32 i2cType;

    /* check if the baudrate parameter is in a valid range and get the check status */
    status = I2c_Std_CheckBaudrateParameter(coreFrequency, busSpeed, dutyCycle, &i2cType);
    /* status is equal to I2C_STD_STATUS_OK */
    if(I2C_STD_STATUS_OK == status)
    {
        /* I2C module is disabled */
        if((0U == pI2c->CR1.B.PE))
        {
            /* Calculate frequency range */
            freqrange = coreFrequency / 1000000U;

            /* frequency is in a valid range: 2 ~ 127 */
            if(128U > freqrange)
            {
                /* Write Frequency */
                pI2c->CR2.B.FREQ = freqrange;

                /* The mode to be enabled is standard mode */
                if(I2C_STD_SPEED_MODE_STANDARD == i2cType)
                {
                    /* Configure I2Cx: Speed */
                    pI2c->CCR.B.FS = 0U;

                    ccrValue = coreFrequency / (busSpeed * 2U);
                    pI2c->CCR.B.CCR = ccrValue;

                    /* Configure I2Cx: Rise Time */
                    pI2c->TRISE.B.TRISE = freqrange;
                }
                /* The mode to be enabled is fast mode or fast plus mode */
                else if((I2C_STD_SPEED_MODE_FAST == i2cType) || (I2C_STD_SPEED_MODE_FAST_PLUS == i2cType))
                {
                    pI2c->CCR.B.DUTY = dutyCycle;
                    pI2c->CCR.B.FS = 1U;

                    /* the duty cycle mode is equal to 0 */
                    if(0U == pI2c->CCR.B.DUTY)
                    {
                        ccrValue = coreFrequency / (busSpeed * 3U);
                        pI2c->CCR.B.CCR = ccrValue;
                    }
                    else
                    {
                        ccrValue = coreFrequency / (busSpeed * 25U);
                        pI2c->CCR.B.CCR = (ccrValue == 0U) ? 1U : ccrValue;
                    }

                    /* Configure I2Cx: Rise Time */
                    freqrange *= (I2C_STD_SPEED_MODE_FAST == i2cType) ? 300U : 120U;
                    pI2c->TRISE.B.TRISE = (freqrange / 1000U);
                }
                /* The mode to be enabled is high-speed mode */
                else /* i2cType is I2C_SPEED_MODE_HIGH */
                {
                    ccrValue = coreFrequency / (busSpeed * 3U);
                    pI2c->CCR1.B.MHS_CCR = ccrValue;

                    /* Configure I2Cx: Rise Time */
                    pI2c->TRISE.B.TRISE = (freqrange * 160U / 1000U);
                }
            }
            else
            {
                status = I2C_STD_STATUS_PARAM_ERROR;
            }
        }
        else
        {
            status = I2C_STD_STATUS_BUSY;
        }
    }

    return status;
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
I2c_Std_Status I2c_Std_Init(I2C_MODULE *const pI2c, const I2C_Std_InitParameter *const pInitParameter)
{
    I2c_Std_Status status;
    /* #Violation: i2c_std_c_REF_1 */
    I2C_CR3 tempCR3;

    /* Read the value of CR3 */
    tempCR3.U = pI2c->CR3.U;

    /* Disable I2C peripheral */
    pI2c->CR1.B.PE = 0U;

    /* Reset I2C peripheral */
    pI2c->CR1.B.SWRST = 1U;
    pI2c->CR1.B.SWRST = 0U;

    /* Calculate baud rate and get status */
    status = I2c_Std_SetBaudrate(pI2c, pInitParameter->coreFrequency, pInitParameter->busSpeed, pInitParameter->dutyCycle);

    /* status is equal to I2C_STD_STATUS_OK */
    if(I2C_STD_STATUS_OK == status)
    {
        /* FIFO enable */
        tempCR3.B.FIFOEN = pInitParameter->enFifo;
        /* FIFO Rx water mark */
        tempCR3.B.RF_ALFULL = pInitParameter->fifoRxWaterMark;
        /* FIFO Tx water mark */
        tempCR3.B.TF_ALEMPTY = pInitParameter->fifoTxWaterMark;
        /* FIFO align mode */
        tempCR3.B.ALIGN = pInitParameter->fifoAlignMode;
        /* I2C burst size */
        tempCR3.B.BS = pInitParameter->burstSize;
        /* I2C flow controller */
        tempCR3.B.FC = 1U;

        /* Write the register value to CR3 */
        pI2c->CR3.U = tempCR3.U;

        /* Enable I2C peripheral */
        pI2c->CR1.B.PE = 1U;
    }

    return status;
}

boolean I2c_Std_CheckFlag(const I2C_MODULE *const pI2c, uint32 flag, boolean setStatus)
{
    /* SR1\2\3\4 result */
    boolean result1;
    boolean result2;
    boolean result3;
    boolean result4;

    /* Expect status flags */
    uint32 parseExpectSr1;
    uint32 parseExpectSr2;
    uint32 parseExpectSr3;
    uint32 parseExpectSr4;

    /* Filter reserved value */
    parseExpectSr1 = flag & I2C_STD_SR1_MASK;
    parseExpectSr2 = (flag >> 16U) & (I2C_STD_SR2_MASK & 0xFFU);
    parseExpectSr3 = (flag >> 13U) & I2C_STD_SR3_MASK;
    parseExpectSr4 = (flag >> 28U) & I2C_STD_SR4_MASK;

    result2 = FALSE;

    /* the expected value of the bits are 1 */
    if(0U != setStatus)
    {
        /* Check SR1~4 bits set */
        result1 = (0U == parseExpectSr1) ? TRUE : ((parseExpectSr1 == (pI2c->SR1.U & parseExpectSr1)) ? TRUE : FALSE);

        /* both SR1 and SR2 need to be checked simultaneously */
        if((0U != parseExpectSr1) && (0U != parseExpectSr2))
        {
            /* Some bit fields of the SR1 register to be checked are set */
            if(TRUE == result1)
            {
                result2 = (parseExpectSr2 == (pI2c->SR2.U & parseExpectSr2)) ? TRUE : FALSE;
            }
        }
        else
        {
            result2 = (0U == parseExpectSr2) ? TRUE : ((parseExpectSr2 == (pI2c->SR2.U & parseExpectSr2)) ? TRUE : FALSE);
        }

        result3 = (0U == parseExpectSr3) ? TRUE : ((parseExpectSr3 == (pI2c->SR3.U & parseExpectSr3)) ? TRUE : FALSE);
        result4 = (0U == parseExpectSr4) ? TRUE : ((parseExpectSr4 == (pI2c->SR4.U & parseExpectSr4)) ? TRUE : FALSE);
    }
    else
    {
        /* Check SR1~4 bits clear */
        result1 = (0U == parseExpectSr1) ? TRUE : ((0U == (pI2c->SR1.U & parseExpectSr1)) ? TRUE : FALSE);
        result2 = (0U == parseExpectSr2) ? TRUE : ((0U == (pI2c->SR2.U & parseExpectSr2)) ? TRUE : FALSE);
        result3 = (0U == parseExpectSr3) ? TRUE : ((0U == (pI2c->SR3.U & parseExpectSr3)) ? TRUE : FALSE);
        result4 = (0U == parseExpectSr4) ? TRUE : ((0U == (pI2c->SR4.U & parseExpectSr4)) ? TRUE : FALSE);
    }

    /* Return result */
    return result1 & result2 & result3 & result4;
}

void I2c_Std_ClearFlag(I2C_MODULE *const pI2c, uint32 flag)
{
    /* The flag is within a valid range (I2C_STD_SR1_CLEARMASK) */
    if(0U != (I2C_STD_SR1_CLEARMASK & flag))
    {
        pI2c->SR1.U = ~flag; /* clear SR1 Bit5, Bit8~12 */
    }
    /* The flag is within a valid range (I2C_STD_SR4_CLEARMASK) */
    if(0U != (I2C_STD_SR4_CLEARMASK & flag))
    {
        pI2c->SR4.U = ~(flag >> 28U); /* clear SR4 Bit0, Bit3 */
        (void)pI2c->SR4.U; /* Write 0 first, and read register value to clear status */
    }
}

#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: i2c_std_c_REF_2 */
#include "I2c_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
