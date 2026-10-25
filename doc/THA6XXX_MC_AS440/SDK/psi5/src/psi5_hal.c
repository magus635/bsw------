/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    psi5_hal.c
 * Author:      01849
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: PSI5 hardware abstraction layer source file.
 *              This file contains implementations for PSI5 hardware abstraction layer.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #psi5_hal_c_REF_1:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be represents as uint8.
*
* #psi5_hal_c_REF_2:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #psi5_hal_c_REF_3:MISRAC2012-Rule-19.2;
* Justification:Define a union type to assign a one-time value to a register.
*
* #psi5_hal_c_REF_4:MISRAC2012-Rule-10.5;
* Justification:Necessary type casting to reduce code complexity; Code review ensure the safety of the
*               casting.
*
* #psi5_hal_c_REF_5:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #psi5_hal_c_REF_6:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "psi5_hal.h"
#include "rcc_hal.h"
#include "tha6_cfg.h"

#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
#if(INPUT_ARG_DETECT == STD_ON)
/**********************************************************************************************************************
 * Function:     Psi5_Hal_AssertSendChannelData
 * Description:  Check whether the data type of the transmission channel meets the requirements.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               frametype: pointer to the psi5 module transmit frame type.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
static void Psi5_Hal_AssertSendChannelData(const PSI5_MODULE *pPsi5, Psi5_ChannelId channelId,
                                           Psi5_FrameType frametype);
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
#if(INPUT_ARG_DETECT == STD_ON)
static void Psi5_Hal_AssertSendChannelData(const PSI5_MODULE *pPsi5, Psi5_ChannelId channelId,
                                           Psi5_FrameType frametype)
{
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));

    boolean checkresult;
    checkresult = FALSE;
    /* Check if the DMA base address and channel ID is out of range */
    if(pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_ENH_PROT == (uint32)PSI5_ENHPROT_PWM4)
    {
        if((uint32)frametype >= PSI5_ASSERTSEND_RANGEJUDGE)
        {
            checkresult = TRUE;
        }
    }
    else
    {
        if((uint32)frametype < PSI5_ASSERTSEND_RANGEJUDGE)
        {
            checkresult = TRUE;
        }
    }
    Assert((boolean)(checkresult));
}
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: psi5_hal_c_REF_5 */
#define PSI5_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: psi5_hal_c_REF_6 */
#include "Psi5_MemMap.h"

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_InitModule(PSI5_MODULE *const pPsi5, const Psi5_ModuleConfig *const pConfig)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(pConfig->timestampPrescaler >= PSI5_TS_PRESCALER_LIMIT));
#endif

    /* Configure prescale for timestamp counter */
    Psi5_Std_TimestampPrescaler(pPsi5, pConfig->timestampPrescaler);

    /* Configure the glitch filter config */
    Psi5_Std_GlitchFilter(pPsi5, pConfig->glitchFilter);

    /* Configure DMA handling */
    Psi5_Std_SetDma(pPsi5, pConfig->dmaEn);
}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_InitChannel(const Psi5_ChannelInitConfig *const pConfig)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pConfig->module));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(PSI5_TXFIFO_DEPTH >= pConfig->sendControl.fifoThresholdLevel));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(PSI5_RXFIFO_DEPTH >= pConfig->receiveControl.fifoThresholdLevel));
#endif

    uint32 tempProt;
    uint32 tempControl;
    uint32 tempRxControl;
    PSI5_MODULE *pPsi5;
    Psi5_ChannelId channelId;
    tempProt = (uint32)pConfig->sendControl.responseProt;
    tempRxControl = 0U;
    pPsi5 = pConfig->module;
    channelId = pConfig->channelId;

    /* #Violation: psi5_hal_c_REF_3 */
    PSI5_CH_TXRX_CONTROL tempTXRXCONTROL;
    /* #Violation: psi5_hal_c_REF_3 */
    PSI5_CH_FIFO_THRESHOLD tempCHFIFOTHRESHOLD;
    /* #Violation: psi5_hal_c_REF_3 */
    PSI5_CH_TX_CONTROL tempTXCONTROL;

    tempTXRXCONTROL.U = 0U;
    tempCHFIFOTHRESHOLD.U = 0U;
    tempTXCONTROL.U = 0U;

    /* CH_PRESCALER */
    pPsi5->CH[channelId].CH_PRESCALER.U = pConfig->channelPrescaler;


    /* CONTROL */
    tempControl = pPsi5->CONTROL.U;
    tempControl |= ((uint32) 1U) << ((uint32)channelId);
    tempControl |= ((uint32)pConfig->decFree << PSI5_DEC_FREE_OFFSET);

    if(tempProt == (uint32)PSI5_PROT_PARITY)
    {
        tempControl &= (~((uint32) 1U << ((uint32)channelId + PSI5_RSP_PROT_OFFSET)));
    }
    else
    {
        tempControl |= ((uint32) 1U << ((uint32)channelId + PSI5_RSP_PROT_OFFSET));
    }
    pPsi5->CONTROL.U = tempControl;

    /* RX_SET */
    /* TXRX_CONTROL */
    tempTXRXCONTROL.B.CTRL_COM_MODE = ((uint32)pConfig->receiveControl.asynchronousModeSelected);
    tempTXRXCONTROL.B.CTRL_AVBS = ((uint32)pConfig->receiveControl.avbsEnable);
    pPsi5->CH[channelId].CH_TXRX_CONTROL.U = tempTXRXCONTROL.U;

    /* RX_CONTROL */
    for (uint8 i = 0; i < PSI5_NUM_SLOTS; i++)
    {
        tempRxControl |= (((uint32)pConfig->receiveControl.receiveControlSlot[i].U) << (i * 4U));
    }
    pPsi5->CH[channelId].CH_RX_CONTROL.U = tempRxControl;

    /* FIFO_THRESHOLD */
    tempCHFIFOTHRESHOLD.B.TX_FIFO_THRESHOLD = pConfig->sendControl.fifoThresholdLevel;
    tempCHFIFOTHRESHOLD.B.RX_FIFO_THRESHOLD = pConfig->receiveControl.fifoThresholdLevel;
    pPsi5->CH[channelId].CH_FIFO_THRESHOLD.U = tempCHFIFOTHRESHOLD.U;

    /* TX_SET */
    /* TX_CONTROL */
    tempTXCONTROL.B.TX_TSYNC_EN = ((uint32)pConfig->sendControl.tsyncEnabled);
    tempTXCONTROL.B.TX_TSYNC_MODE = ((uint32)pConfig->sendControl.tsyncMode);
    tempTXCONTROL.B.TX_START_PAT = ((uint32)pConfig->sendControl.startpatSelected);
    tempTXCONTROL.B.TX_ENH_PROT = ((uint32)pConfig->sendControl.enhancedProtocolSelected);
    tempTXCONTROL.B.TX_START_CTRL = ((uint32)pConfig->sendControl.startSequenceGenerationEnabled);
    tempTXCONTROL.B.TX_BIT_STUFF = ((uint32)pConfig->sendControl.bitStuffingEnabled);
    tempTXCONTROL.B.TX_CRC_MODE = ((uint32)pConfig->sendControl.crcGenerationEnabled);

    pPsi5->CH[channelId].CH_TX_CONTROL.U = tempTXCONTROL.U;

}

/* #Violation: psi5_hal_c_REF_2 */
Rcc_ErrorFlag Psi5_Hal_ResetModule(void)
{

    Rcc_ErrorFlag resetResult;

    resetResult = Rcc_Hal_TrigModuleRst(RCC_MODULERST_PSI5);

    return resetResult;
}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_ReadChannelData(const PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                              Psi5_ReceiveFrame *const pFrame)
{
    /* #Violation: psi5_hal_c_REF_3 */
    PSI5_CH_RX_FIFO rxFifoRegister;
    Psi5_RxType type;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif

    rxFifoRegister = Psi5_Std_ReadReceiveChFifoData(pPsi5, channelId);

    if(rxFifoRegister.B1.RX_TYPE < (uint32)(PSI5_RXTYPE_ILLEGAL))
    {
        /* #Violation: psi5_hal_c_REF_4 */
        pFrame->dataType = (Psi5_RxType)rxFifoRegister.B1.RX_TYPE;
    }

    type = pFrame->dataType;

    if(type == PSI5_RXTYPE_CTRLDATA)
    {
        pFrame->rxTIE = (uint8)rxFifoRegister.B1.RX_TIE;
        pFrame->rxNBI = (uint8)rxFifoRegister.B1.RX_NBI;
        pFrame->rxMEI = (uint8)rxFifoRegister.B1.RX_MEI;
        pFrame->rxNFI = (uint8)rxFifoRegister.B1.RX_NFI;
        pFrame->frameLength = (uint8)rxFifoRegister.B1.RX_LEN;

        if(rxFifoRegister.B1.RX_SLOT < (uint32)(PSI5_SLOT_MAX))
        {
            /* #Violation: psi5_hal_c_REF_4 */
            pFrame->slotId = (Psi5_Slot)rxFifoRegister.B1.RX_SLOT;
        }

        pFrame->msgBit = (uint8)rxFifoRegister.B1.RX_MSG;
    }
    else if(type == PSI5_RXTYPE_TIMESTAMP)
    {
        pFrame->timestamp = rxFifoRegister.B2.RX_TIMESTAMP;
    }
    else
    {
        pFrame->payload = rxFifoRegister.B3.RX_PAYLOAD;
    }
}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_SendChannelData(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                              const Psi5_TransmitFrame *const pFrame)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
    /* #Violation: psi5_hal_c_REF_1 */
    Psi5_Hal_AssertSendChannelData(pPsi5, channelId, pFrame->frameType);
#endif


    Psi5_Std_ProtectSync(pPsi5, channelId);

    /* Frame4 */
    if(pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_ENH_PROT == (uint32)PSI5_ENHPROT_PWM4)
    {
        Psi5_Std_SendChannelDataFrame4(pPsi5, channelId, pFrame);
    }
    /* Frame1-Frame3 */
    else
    {
        Psi5_Std_SendChannelDataFrame13(pPsi5, channelId, pFrame);
    }
}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_TxCommand_Config(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                               const Psi5_TxCommand_Config *const config)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_ENH_PROT <= PSI5_ENH_PROT_LIMIT));
#endif

    if(pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_ENH_PROT == (uint32)PSI5_ENHPROT_TOOTHGAP)
    {
        /* The sync width in internal clock */
        Psi5_Std_SetTransmitChTsycnPeriod(pPsi5, channelId, config->txCommandChTsycnPeriod);
    }
    else
    {
        /* Controls PWM width */
        Psi5_Std_SetTransmitChTsycnPeriod(pPsi5, channelId, config->txCommandChTsycnPeriod);
        Psi5_Std_SetTransmitChPWM_Add(pPsi5, channelId, config->txCommandChPwmAdd);
    }
    /* Controls gap between two Sync pulse for ECU to Sensor communication */
    Psi5_Std_SetTransmitChToothgap_SyncGap(pPsi5, channelId, config->txCommandChSyncGap);

    /* Transmit Slot Control Register for Channel */
    Psi5_Std_SetTransmitChSync_SlotGap(pPsi5, channelId, config->txCommandChSync_SlotGap);
    Psi5_Std_SetTransmitChSlot_Post(pPsi5, channelId, config->txCommandChSlot_Post);
    Psi5_Std_SetTransmitChSlot_Gap(pPsi5, channelId, config->txCommandChSlot_Gap);

    /* Controls the width of slot in number of bits from Start bits to Parity/CRC bits */
    Psi5_Std_SetReceiveChSlot_Width(pPsi5, channelId, &(config->chSlot_Width));

}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_TxSync_Config(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId, const Psi5_TxSync_Config *const config)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif

    /* Controls the sync width in internal clock */
    Psi5_Std_SetTransmitChTsycnPeriod(pPsi5, channelId, config->txSyncChTsycnPeriod);

    /* Transmit slot control register for Channel */
    Psi5_Std_SetTransmitChSync_SlotGap(pPsi5, channelId, config->txSyncChSync_SlotGap);
    Psi5_Std_SetTransmitChSlot_Post(pPsi5, channelId, config->txSyncChSlot_Post);
    Psi5_Std_SetTransmitChSlot_Gap(pPsi5, channelId, config->txSyncChSlot_Gap);

    /* Controls the width of slot in number of bits from start bits to parity/CRC bits */
    Psi5_Std_SetReceiveChSlot_Width(pPsi5, channelId, &(config->chSlot_Width));
}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_RxAsync_Config(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId, const Psi5_ChSlot_Width *const config)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif

    /* Controls the width of slot in number of bits from start bits to parity/CRC bits */
    Psi5_Std_SetReceiveChSlot_Width(pPsi5, channelId, config);
}


/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_EnableTsyncPulse(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                               const Psi5_ReceiveControl *const receiveControl)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(96U >= receiveControl->fifoThresholdLevel));
#endif

    Psi5_Std_SetChSlot_Prot(pPsi5, channelId, receiveControl);
    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_TSYNC_EN = (uint32)SYNCENABLE;

}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_DisableTsyncPulse(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif

    pPsi5->CH[channelId].CH_TX_CONTROL.B.TX_TSYNC_EN = (uint32)SYNCDISABLE;

}

/* #Violation: psi5_hal_c_REF_2 */
uint32 Psi5_Hal_GetInterruptStatus(const PSI5_MODULE *const pPsi5)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif
    uint32 interruptStatus;

    interruptStatus = pPsi5->IRQ_STATUS.U;

    return interruptStatus;
}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_ClearInterrupt(PSI5_MODULE *const pPsi5, uint32 interrupt)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif

    pPsi5->IRQ_STATUS.U = interrupt;

}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_SetChannelInterrupt(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId, Psi5_IrqRequest enable,
                                  uint32 interrupt)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(interrupt <= PSI5_INTERRUPTCHANNEL_MAX));
#endif

    if(enable == PSI5_IRQREQUEST_DISABLED)
    {
        /* Clear interrupt source */
        pPsi5->CH[channelId].CH_IRQ_ENABLE.U &= (~interrupt);
    }
    else
    {
        /* Set interrupt source */
        pPsi5->CH[channelId].CH_IRQ_ENABLE.U |= interrupt;
    }
}


/* #Violation: psi5_hal_c_REF_2 */
Psi5_InterruptFlag Psi5_Hal_GetChannelInterruptFlag(const PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                                    Psi5_ChIrqSource interrupt)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif

    uint32 temp;
    Psi5_InterruptFlag flag;
    flag = PSI5_INTERRUPFLAG_NOTSETUP;

    temp = pPsi5->CH[channelId].CH_IRQ_STATUS.U & ((uint32)interrupt);
    if(temp > 0U)
    {
        flag = PSI5_INTERRUPFLAG_SETUP;
    }
    return flag;
}


/* #Violation: psi5_hal_c_REF_2 */
uint32 Psi5_Hal_GetChannelInterruptStatus(const PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif
    uint32 interruptStatus;

    interruptStatus = pPsi5->CH[channelId].CH_IRQ_STATUS.U;

    return interruptStatus;
}

/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_ClearChannelInterrupt(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId, uint32 interrupt)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(interrupt <= PSI5_INTERRUPTCHANNEL_MAX));
#endif

    pPsi5->CH[channelId].CH_IRQ_STATUS.U = interrupt;

}


/* #Violation: psi5_hal_c_REF_2 */
void Psi5_Hal_FlushFifo(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId, uint32 fifoFlush)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: psi5_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPsi5));
#endif

    pPsi5->CH[channelId].CH_FIFO_FLUSH.U |= fifoFlush;
    pPsi5->CH[channelId].CH_FIFO_FLUSH.U &= (~fifoFlush);

}

/* #Violation: psi5_hal_c_REF_5 */
#define PSI5_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: psi5_hal_c_REF_6 */
#include "Psi5_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
