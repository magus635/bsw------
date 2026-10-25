/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    espi_std.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: ESPI standard driver source file.
 *              This file contains implementations for ESPI standard driver.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#espi_std_c_REF_1:MISRAC2012-Rule-19.2;
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
*#espi_std_c_REF_2:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "espi_std.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

boolean Espi_Master_Std_InitClock(ESPI_MODULE *const pEspi, uint16 clockDivision)
{
    boolean ret;
    /* #Violation: espi_std_c_REF_1 */
    ESPI_GNRCON gnrcfg;

    ret = TRUE;
    gnrcfg.U = 0U;

    /* Set ESPI master mode */
    gnrcfg.B.MS = (uint32)ESPI_MODE_MASTER;
    /* Set module pre-division */
    gnrcfg.B.GTQ = (uint32)((uint32)clockDivision - 1U);
    /* Enable module clock */
    gnrcfg.B.CLKMUX = 1U;
    /* Start transition */
    gnrcfg.B.EN = 1U;

    pEspi->GNRCON.U = gnrcfg.U;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON.U, gnrcfg.U);

    return ret;
}

uint32 Espi_Master_Std_CalculateChannelConfiguration(const Espi_BaudRate baudRate, Espi_ClockPolarity clockPolarity,
                                                     Espi_ClockPhase clockPhase, boolean parityCheckEnable)
{
    /* #Violation: espi_std_c_REF_1 */
    ESPI_DCON dcfg;

    dcfg.U = 0;

    dcfg.B.TQ = (uint32)((uint32)baudRate.baudrateParameterQ - 1U);  /* Set time quantum   */
    dcfg.B.CSA = (uint32)((uint32)baudRate.baudrateParameterA - 1U); /* Set bit segment A  */
    dcfg.B.CSB = (uint32)baudRate.baudrateParameterB;                /* Set bit segment B  */
    dcfg.B.CSC = (uint32)baudRate.baudrateParameterC;                /* Set bit segment C  */
    dcfg.B.CPH = (uint32)clockPhase;                                 /* Set clock phase    */
    dcfg.B.CPOL = (uint32)clockPolarity;                             /* Set clock polarity */
    dcfg.B.PRTEN = (uint32)parityCheckEnable;                        /* Enable/Disable parity check */

    return dcfg.U;
}

boolean Espi_Master_Std_InitSlaveSlectConfiguration(ESPI_MODULE *const pEspi, Espi_Cs_ChannelId csChannel, Espi_ActiveOutputLevel slsoActiveLevel, boolean slsoEn)
{
    boolean ret;
    uint32 sscon;

    ret = TRUE;

    sscon = pEspi->SSCON.U;
    sscon &= ~(uint32)((1UL << ((uint32)csChannel + 16U)) + (1UL << (uint32)csChannel));
    sscon |= (((uint32)slsoEn << ((uint32)csChannel + 16U)) + (((uint32)slsoActiveLevel) << (uint32)csChannel));

    pEspi->SSCON.U = sscon;

    ret = Espi_Register_ReadBack_Check(ret, pEspi->SSCON.U, sscon);
    return ret;
}

boolean Espi_Slave_Std_InitClock(ESPI_MODULE *const pEspi, uint16 clockDivision)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: espi_std_c_REF_1 */
    ESPI_GNRCON gnrcfg;

    gnrcfg.U = 0U;

    /* Set ESPI module work mode as slave mode */
    gnrcfg.B.MS = (uint32)ESPI_MODE_SLAVE;
    /* Set module pre-division */
    gnrcfg.B.GTQ = (uint32)((uint32)clockDivision - 1U);
    /* Enable module clock*/
    gnrcfg.B.CLKMUX = 1U;
    /* Start transition */
    gnrcfg.B.EN = 1U;

    pEspi->GNRCON.U = gnrcfg.U;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON.U, gnrcfg.U);

    return ret;
}

uint32 Espi_Slave_Std_CalculateChannelConfiguration(boolean parityEn, const Espi_BaudRate baudRate)
{
    /* #Violation: espi_std_c_REF_1 */
    ESPI_DCON dcfg;

    dcfg.U = 0;
    dcfg.B.TQ = (uint32)((uint32)baudRate.baudrateParameterQ - 1U);
    dcfg.B.CSA = (uint32)((uint32)baudRate.baudrateParameterA - 1U);
    dcfg.B.CSB = (uint32)baudRate.baudrateParameterB;
    dcfg.B.CSC = (uint32)baudRate.baudrateParameterC;
    dcfg.B.CPH = (uint32)ESPI_CLOCKPHASE_SECONDSAMPLE;
    dcfg.B.CPOL = (uint32)ESPI_CLOCKPOLARITY_IDLE_LOW;
    dcfg.B.PRTEN = (uint32)parityEn;

    return dcfg.U;
}

boolean Espi_Std_SetDma(ESPI_MODULE *const pEspi, boolean dmaEn)
{
    /* #Violation: espi_std_c_REF_1 */
    ESPI_GNRCON1 gnrcfg1;
    boolean ret;

    ret = TRUE;
    gnrcfg1.U = pEspi->GNRCON1.U;
    gnrcfg1.B.TXDREN = (uint32)dmaEn; /* Enable/Disable DMA TX */
    gnrcfg1.B.RXDREN = (uint32)dmaEn; /* Enable/Disable DMA RX */
    pEspi->GNRCON1.U = gnrcfg1.U;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON1.U, gnrcfg1.U);
    
    return ret;
}

#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: espi_std_c_REF_2 */
#include "Spi_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
