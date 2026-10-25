/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    espi_hal.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: ESPI hardware abstraction layer source file.
 *              This file contains implementations for ESPI hardware abstraction layer.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#espi_hal_c_REF_1:MISRAC2012-Dir-1.1;
* Justification:Inline assembly functions
*
*#espi_hal_c_REF_2:MISRAC2012-Dir-1.1;
* Justification:Necessary type casting for memory and/or register accessing.
*
*#espi_hal_c_REF_3:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
*#espi_hal_c_REF_4:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*#espi_hal_c_REF_5:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#espi_hal_c_REF_6:MISRAC2012-Rule-11.5;
* Justification:Cast from a pointer to void to a pointer to object type.
*
*#espi_hal_c_REF_7:MISRAC2012-Rule-19.2;
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
*#espi_hal_c_REF_8:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8;.
*
*#espi_hal_c_REF_9:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#espi_hal_c_REF_10:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#espi_hal_c_REF_11:MISRAC2012-Rule-8.7;
* Justification:This function may be used in other module.
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "espi_hal.h"
#include "espi_std.h"
#include "espi_register.h"
#include "compilertypes.h"
#include "rcc_hal.h"
#include "tha6_cfg.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
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

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Master_Hal_InitModule(ESPI_MODULE *const pEspi, const Espi_Master_ModuleInitConfig *const pConfig)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(pConfig->clockDivision >= 1U));
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif
    ret = TRUE;

    /* Configure divided clock in Master Mode*/
    ret &= Espi_Master_Std_InitClock(pEspi, pConfig->clockDivision);

    /* Configure EXPECT phase timeout threshold in Master Mode */
    ret &= Espi_Std_InitExpectTimeoutThreshold(pEspi, pConfig->expectTimeoutThreshold);

    /* Configure TX FIFO */
    ret &= Espi_Std_InitTxFifo(pEspi, pConfig->txFifoMode, pConfig->txFifoThreshold);

    /* Configure RX FIFO */
    ret &= Espi_Std_InitRxFifo(pEspi, pConfig->rxFifoMode, pConfig->rxFifoThreshold);

    /* Configure Move Counter Mode */
    ret &= Espi_Std_EnableMoveCounterMode(pEspi, pConfig->moveCounterEn);

    /* Configure DMA handling */
    if(TRUE == pConfig->dmaEn)
    {
        ret &= Espi_Std_SetDma(pEspi, pConfig->dmaEn);
    }

    /* Configure interrupt requests */
    if(0U != pConfig->interruptEn)
    {
        ret &= Espi_Hal_SetInterrupt(pEspi, pConfig->interruptEn, TRUE);
    }

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Master_Hal_InitChannel(ESPI_MODULE *const pEspi, const Espi_Master_ChannelInitConfig *const pConfig)
{
    boolean ret;
    uint8 channelMid;
    uint32 channelConfigVal;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(pConfig->baudRate.baudrateParameterQ >= 1U));
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    ret = TRUE;
    channelMid = ESPI_CS_CHANNEL_MAX >> 1U;
    channelConfigVal = Espi_Master_Std_CalculateChannelConfiguration(pConfig->baudRate, pConfig->clockPolarity,
                                                                     pConfig->clockPhase, pConfig->parityCheckEnable);

    if((uint8)pConfig->csChannel < channelMid)
    {
        pEspi->DCON[(uint8)pConfig->csChannel].U = channelConfigVal;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->DCON[(uint8)pConfig->csChannel].U, channelConfigVal);
    }
    else
    {
        pEspi->DCONEG[((uint8)pConfig->csChannel - channelMid)].U = channelConfigVal;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->DCONEG[((uint8)pConfig->csChannel - channelMid)].U, channelConfigVal);
    }

    /* Configure SLSO output */
    ret &= Espi_Master_Std_InitSlaveSlectConfiguration(pEspi, pConfig->csChannel, pConfig->slsoActiveLevel, pConfig->slsoEn);

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Slave_Hal_EnableCsChannel(ESPI_MODULE *const pEspi, boolean enable) 
{
    boolean ret;
    ret = TRUE;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif
    pEspi->SISW.B.SMISS = (uint32)enable;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->SISW.B.SMISS, (uint32)enable);

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */ 
boolean Espi_Slave_Hal_InitModule(ESPI_MODULE *const pEspi, const Espi_Slave_ModuleInitConfig *const pConfig)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(pConfig->clockDivision >= 1U));
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    ret = TRUE;

    /* Configure divided clock in Slave Mode */
    ret &= Espi_Slave_Std_InitClock(pEspi, pConfig->clockDivision);

    /* Configure EXPECT phase timeout threshold in Master Mode */
    ret &= Espi_Std_InitExpectTimeoutThreshold(pEspi, pConfig->expectTimeoutThreshold);

    /* Configure TX FIFO in Slave Mode */
    ret &= Espi_Std_InitTxFifo(pEspi, pConfig->txFifoMode, pConfig->txFifoThreshold);

    /* Configure RX FIFO */
    ret &= Espi_Std_InitRxFifo(pEspi, pConfig->rxFifoMode, pConfig->rxFifoThreshold);

    /* Configure DMA handling */
    if(TRUE == pConfig->dmaEn)
    {
        ret &= Espi_Std_SetDma(pEspi, pConfig->dmaEn);
    }

    /* Configure interrupt requests */
    if(0U != pConfig->interruptEn)
    {
        ret &= Espi_Hal_SetInterrupt(pEspi, pConfig->interruptEn, TRUE);
    }

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */ 
boolean Espi_Slave_Hal_InitChannel(ESPI_MODULE *const pEspi, const Espi_Slave_ChannelInitConfig *const pConfig)
{
    boolean ret;
    uint8 channelMid;
    uint32 dcfg;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(pConfig->baudRate.baudrateParameterQ >= 1U));
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    ret = TRUE;
    channelMid = ESPI_CS_CHANNEL_MAX >> 1U;

    if((uint8)pConfig->csChannel < channelMid)
    {
        dcfg = Espi_Slave_Std_CalculateChannelConfiguration(pConfig->parityCheckEnable, pConfig->baudRate);
        pEspi->DCON[(uint8)pConfig->csChannel].U = dcfg;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->DCON[(uint8)pConfig->csChannel].U, dcfg);
    }
    else
    {
        dcfg = Espi_Slave_Std_CalculateChannelConfiguration(pConfig->parityCheckEnable, pConfig->baudRate);
        pEspi->DCONEG[(uint8)pConfig->csChannel - channelMid].U = dcfg;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->DCONEG[(uint8)pConfig->csChannel - channelMid].U, dcfg);    
    }

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */
uint32 Espi_Hal_CalculateChannelDynamicConfiguration(Espi_Cs_ChannelId channelId, const Espi_ChannelDynamicConfig *const pConfig)
{
    /* #Violation: espi_hal_c_REF_7 */
    ESPI_EMCON emcfg;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    emcfg.U = 0U;

    emcfg.B.IPSC = (uint32)pConfig->delayTime.idleDelayTime.delayTimePrescalercoEfficient;
    emcfg.B.IDL = (uint32)pConfig->delayTime.idleDelayTime.delayTimePrescalerUnit;
    emcfg.B.LPSC = (uint32)pConfig->delayTime.leadingDelayTime.delayTimePrescalercoEfficient;
    emcfg.B.LDL = (uint32)pConfig->delayTime.leadingDelayTime.delayTimePrescalerUnit;
    emcfg.B.TPSC = (uint32)pConfig->delayTime.trailDelayTime.delayTimePrescalercoEfficient;
    emcfg.B.TDL = (uint32)pConfig->delayTime.trailDelayTime.delayTimePrescalerUnit;
    emcfg.B.PARTYP = (uint32)pConfig->parityMode;
    emcfg.B.UIOT1 = 0U;
    emcfg.B.MSB = (uint32)pConfig->bitOrder;
    emcfg.B.DL = (uint32)pConfig->dataWidth;
    emcfg.B.SCM = (uint32)channelId;

    switch(pConfig->dataMode)
    {
        case ESPI_MASTER_MODE_SINGLESHORT:
        {
            emcfg.B.DLU = (uint32)ESPI_DATAWIDTH_UNIT_BIT;
            emcfg.B.LDB = (uint32)ESPI_LASTWORD;
            break;
        }

        case ESPI_MASTER_MODE_SINGLELONG:
        {
            emcfg.B.DLU = (uint32)ESPI_DATAWIDTH_UNIT_BYTE;
            emcfg.B.LDB = (uint32)ESPI_LASTWORD;
            break;
        }

        case ESPI_MASTER_MODE_CONTINUOUSSHORT:
        {
            emcfg.B.DLU = (uint32)ESPI_DATAWIDTH_UNIT_BIT;
            emcfg.B.LDB = (uint32)ESPI_NOTLASTWORD;
            break;
        }

        case ESPI_MASTER_MODE_CONTINUOUSLONG:
        {
            emcfg.B.DLU = (uint32)ESPI_DATAWIDTH_UNIT_BYTE;
            emcfg.B.LDB = (uint32)ESPI_NOTLASTWORD;
            break;
        }

        case ESPI_MASTER_MODE_XXL:
        {
            emcfg.B.DLU = (uint32)ESPI_DATAWIDTH_UNIT_BYTE;
            emcfg.B.LDB = (uint32)ESPI_NOTLASTWORD;
            emcfg.B.DL = 0U;
            break;
        }

        case ESPI_MASTER_MODE_MOVECOUNTER:
        {
            emcfg.B.DLU = (uint32)ESPI_DATAWIDTH_UNIT_BIT;
            emcfg.B.LDB = (uint32)ESPI_NOTLASTWORD;
            break;
        }

        default:
        {
            /* Do nothing */
            break;
        }
    }

    return emcfg.U;
}

/* #Violation: espi_hal_c_REF_4 */
void Espi_Hal_WriteConfiguration(ESPI_MODULE *const pEspi, uint32 baconVal, boolean lastWord)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif
    /* Write baconVal to EMCONENTRY to end/start data stream */
    if (lastWord == TRUE)
    {
        pEspi->EMCONENTRY.U = baconVal | 1UL;
    }
    else
    {
        pEspi->EMCONENTRY.U = baconVal & 0xFFFFFFFEUL; 
    }
}

/* #Violation: espi_hal_c_REF_4 */
uint8 Espi_Hal_SendData(ESPI_MODULE *const pEspi, const uint8 *const txBuffer, const Espi_DataBufferWidth bufferWidth)
{
    uint32 data;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(NULL_PTR != txBuffer));
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    if(ESPI_DATABUFFER_32BITS == bufferWidth)
    {
        /* #Violation: espi_hal_c_REF_2 */ 
        data = *((const uint32 *)(const void *)txBuffer);
    }
    else if(ESPI_DATABUFFER_16BITS == bufferWidth)
    {
        /* #Violation: espi_hal_c_REF_2 */ 
        data = *((const uint16 *)(const void *)txBuffer);
    }
    else
    {
        data = *((const uint8 *)txBuffer);
    }

    Espi_Std_WriteTransferFifo(pEspi, data);

    return (uint8)bufferWidth;
}

/* #Violation: espi_hal_c_REF_4 */
uint8 Espi_Hal_ReceiveData(const ESPI_MODULE *const pEspi, uint8 *const rxBuffer, Espi_DataBufferWidth bufferWidth)
{
    uint32 rxData;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(NULL_PTR != rxBuffer));
#endif

    rxData = Espi_Std_ReadReceiveFifo(pEspi);

    if(ESPI_DATABUFFER_32BITS == bufferWidth)
    {
        /* #Violation: espi_hal_c_REF_2 */
        *((uint32 *)(void *)rxBuffer) = rxData;
    }
    else if(ESPI_DATABUFFER_16BITS == bufferWidth)
    {
        /* #Violation: espi_hal_c_REF_2 */
        *((uint16 *)(void *)rxBuffer) = (uint16)rxData;
    }
    else
    {
        *(rxBuffer) = (uint8)rxData;
    }

    return (uint8)bufferWidth;
}

/* #Violation: espi_hal_c_REF_11 */
boolean Espi_Hal_SetInterrupt(ESPI_MODULE *const pEspi, uint32 interrupt, boolean enable)
{
    boolean ret;
    uint32 regValue;
        
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(interrupt <= ESPI_INTC_ALL_FLAGS));
#endif
    
    ret = TRUE;
    regValue = pEspi->GNRCON1.U;

    if(TRUE == enable)
    {
        regValue |= interrupt;
        pEspi->GNRCON1.U = regValue;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON1.U, regValue);
    }
    else if(ESPI_INTC_FLAG_NO_ERROR == interrupt)
    {
        pEspi->GNRCON1.B.ERRIENS = interrupt;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON1.B.ERRIENS, interrupt);
    }
    else
    {
        regValue &= (~interrupt);
        pEspi->GNRCON1.U = regValue;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON1.U, regValue);
    }

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Hal_SetExtraLargeDataLength(ESPI_MODULE *const pEspi, uint16 byteCount)
{
    boolean ret;
    uint32 dataLength;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(byteCount >= 2U));
#endif

    ret = TRUE;
    dataLength = (uint32)byteCount - 1U;

    pEspi->LTCON.B.DLT = dataLength;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->LTCON.B.DLT, dataLength);

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Hal_SetFifoLevel(ESPI_MODULE *const pEspi, uint8 txLvl, uint8 rxLvl)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif
    ret = TRUE;
    
    pEspi->FIFOTHRESHOLD.B.TXTHRESHOLD = (uint32)txLvl;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->FIFOTHRESHOLD.B.TXTHRESHOLD, (uint32)txLvl);
    pEspi->FIFOTHRESHOLD.B.RXTHRESHOLD = (uint32)rxLvl;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->FIFOTHRESHOLD.B.RXTHRESHOLD, (uint32)rxLvl);

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */
uint32 Espi_Hal_GetRxFifoLevel(const ESPI_MODULE *const pEspi)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif
    return pEspi->FIFOLEVEL.B.RXLEVEL;
}

/* #Violation: espi_hal_c_REF_4 */
uint32 Espi_Hal_GetTxFifoLevel(const ESPI_MODULE *const pEspi)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif
    return pEspi->FIFOLEVEL.B.TXLEVEL;
}

/* #Violation: espi_hal_c_REF_4 */
uint32 Espi_Hal_GetFlagStatus(const ESPI_MODULE *const pEspi, uint32 flag)
{
    uint32 flagStatus;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    flagStatus = (pEspi->STS.U & ESPI_ALL_FLAGS_STATES & flag);

    return flagStatus;
}

/* #Violation: espi_hal_c_REF_4 */
void Espi_Hal_ClearFlagStatus(ESPI_MODULE *const pEspi, uint32 flag)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    if(ESPI_SRSTB_SET == (flag & ESPI_SRSTB_SET))
    {
        /* If the AFIF and BFIF bit are set, 
           the AFIF and BFIF bits must be cleared first before generating the reset */
        if(pEspi->MCCON.B.BFIF == 1U)
        {
            pEspi->MCCON.B.BFIC = 1U;
            pEspi->MCCON.B.AFIC = 1U;
        }
        /* GNRCON.SRSTB is self clearing. Writing it back to 0 is a second read modify write of
           GNRCON which can only truncate the reset pulse, a barrier is used instead */
        pEspi->GNRCON.B.SRSTB = 1U;
        /* #Violation: espi_hal_c_REF_1 */
        DSB();
    }

    /* ESPI_SRSTB_SET is not a STSC bit: only write the defined clear bits [19:0], reserved bits keep 0 */
    pEspi->STSC.U = (flag & (ESPI_INTC_ALL_FLAGS | ESPI_ALARM_ALL_FLAGS));
}

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Hal_FlushRxFifo(ESPI_MODULE *const pEspi)
{
    boolean ret;
    uint32 regValue;
    uint32 toggleValue;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    ret = TRUE;

    /* If the AFIF and BFIF bit are set,
       the AFIF and BFIF bits must be cleared first before generating the reset */
    if(pEspi->MCCON.B.BFIF == 1U)
    {
        pEspi->MCCON.B.BFIC = 1U;
        pEspi->MCCON.B.AFIC = 1U;
    }
    /* GNRCON.SRSTB (bits 31:30) clears the FIFO pointers and resets the FSM and the counters.
       The bit is self clearing, it is written as a whole register and it is not read back */
    regValue = pEspi->GNRCON.U;
    pEspi->GNRCON.U = (regValue & 0x3FFFFFFFU) | (1UL << 30U);
    /* #Violation: espi_hal_c_REF_1 */
    DSB();
    /* Toggling the RXFIFO move mode GNRCON1.RXFM (bits 29:28) re-arms the RXFIFO move logic, the
       same sequence as in Espi_Hal_TriggerDmaRequest. The configured mode is restored unchanged */
    regValue = pEspi->GNRCON1.U;
    if((((uint32)ESPI_FIFOMODE_BATCH) << 28U) == (regValue & 0x30000000U))
    {
        toggleValue = (regValue & 0xCFFFFFFFU) | (((uint32)ESPI_FIFOMODE_SINGLE) << 28U);
    }
    else
    {
        toggleValue = (regValue & 0xCFFFFFFFU) | (((uint32)ESPI_FIFOMODE_BATCH) << 28U);
    }
    pEspi->GNRCON1.U = toggleValue;
    /* #Violation: espi_hal_c_REF_1 */
    DSB();
    pEspi->GNRCON1.U = regValue;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON1.U, regValue);

    return ret;
}

/* #Violation: espi_hal_c_REF_3 */
/* #Violation: espi_hal_c_REF_4 */
Rcc_ErrorFlag Espi_Hal_ResetModule(ESPI_MODULE *const pEspi)
{
    /* #Violation: espi_hal_c_REF_7 */
    ESPI_GNRCON1 gnrcon1Reg;
    /* #Violation: espi_hal_c_REF_7 */
    ESPI_ESTS estsReg;
    Rcc_ModuleRst moduleEspiSel;
    Rcc_ErrorFlag resetResult;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    ret = TRUE;
    resetResult = RCC_ERRORFLAG_FAIL;

    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    moduleEspiSel = ESPI_GET_RCC_RST_NUM(pEspi);

    if (moduleEspiSel != RCC_MODULERST_MAX)
    {
        /* in master mode, must ensure STS.FS == 0b0 */
        if ((pEspi->GNRCON.B.MS == 0U) && (pEspi->STS.B.FS == 0U))
        {
            resetResult = RCC_ERRORFLAG_SUCCESS;
        }
        /* in slave mode, must ensure STS.SEF = 0b1 */
        else if (((pEspi->GNRCON.B.MS == 2U) || (pEspi->GNRCON.B.MS == 3U)) && (pEspi->STS.B.SEF == 1U))
        {
            resetResult = RCC_ERRORFLAG_SUCCESS;
        }
        else
        {
           /* Do nothing*/
        }
    }

    if (RCC_ERRORFLAG_SUCCESS == resetResult)
    {
        gnrcon1Reg.U = pEspi->GNRCON1.U;

        gnrcon1Reg.B.ERRIENS = 0U;
        gnrcon1Reg.B.TXFIEN = 0U;
        gnrcon1Reg.B.RXFIEN = 0U;
        gnrcon1Reg.B.TSE1EN = 0U;
        gnrcon1Reg.B.TSE2EN = 0U;
        gnrcon1Reg.B.DAIGEN = 0U;
        gnrcon1Reg.B.SEFEN = 0U;
        gnrcon1Reg.B.UEIEN = 0U;
        gnrcon1Reg.B.LTEIEN = 0U;
        gnrcon1Reg.B.TXDREN = 0U;
        gnrcon1Reg.B.RXDREN = 0U;

        pEspi->GNRCON1.U = gnrcon1Reg.U;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON1.U, gnrcon1Reg.U);
        pEspi->FIFOTHRESHOLD.B.STOEN = 0U;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->FIFOTHRESHOLD.B.STOEN, 0U);
        estsReg.U = pEspi->ESTS.U;
        estsReg.U &= (uint32)(~(uint32)(7UL << 29U));
        pEspi->ESTS.U = estsReg.U;
        ret = Espi_Register_ReadBack_Check(ret, pEspi->ESTS.B.CSDEN, 0U);

        /* #Violation: espi_hal_c_REF_1 */
        DSB();
        
        if (ret != TRUE)
        {
            resetResult = RCC_ERRORFLAG_FAIL;
        }
        else
        {
            resetResult = Rcc_Hal_TrigModuleRst(moduleEspiSel);
        }
    }

    return resetResult;
}

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Hal_EnableLoopBack(ESPI_MODULE *const pEspi, boolean enable)
{
    /* #Violation: espi_hal_c_REF_7 */
    ESPI_GNRCON gnrcfg;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif
    
    ret = TRUE;
    gnrcfg.U = pEspi->GNRCON.U;
    gnrcfg.B.OLBC = (uint32)enable;
    pEspi->GNRCON.U = gnrcfg.U;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->GNRCON.U, gnrcfg.U);

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Hal_SetMoveCounterDataLength(ESPI_MODULE *const pEspi, uint16 moveStep)
{
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
    /* #Violation: espi_hal_c_REF_8 */
    Assert((boolean)(moveStep == (moveStep & ESPI_MOVE_STEP_MASK)));
#endif
    
    ret = TRUE;

    if(pEspi->MCCON.B.BFIF == 1U)
    {
        pEspi->MCCON.B.BFIC = 1U;
        pEspi->MCCON.B.AFIC = 1U;
#if defined(THA6_THA6412)
        /* GNRCON.SRSTB is self clearing: it reads back as 0 and shall not be checked */
        pEspi->GNRCON.B.SRSTB = 1U;
        /* #Violation: espi_hal_c_REF_1 */
        DSB();
#endif
    }

    pEspi->MC.B.TOMS = moveStep;
    ret = Espi_Register_ReadBack_Check(ret, pEspi->MC.B.TOMS, moveStep);

    return ret;
}

/* #Violation: espi_hal_c_REF_4 */
boolean Espi_Hal_SetDma(ESPI_MODULE *const pEspi, boolean dmaEn)
{
    boolean ret;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_c_REF_5 */
    /* #Violation: espi_hal_c_REF_9 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

    ret = Espi_Std_SetDma(pEspi, dmaEn);
    return ret;
}

#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: espi_hal_c_REF_10 */
#include "Spi_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
