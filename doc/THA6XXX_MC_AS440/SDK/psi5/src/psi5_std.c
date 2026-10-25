/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    psi5_std.c
 * Author:      01849
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: PSI5 standard driver source file.
 *              This file contains implementations for PSI5 standard driver.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #psi5_std_c_REF_1:MISRAC2012-Rule-19.2;
* Justification:Define a union type to assign a one-time value to a register.
*
* #psi5_std_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #psi5_std_c_REF_3:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "psi5_std.h"
#include "psi5_hal.h"
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
/* #Violation: psi5_std_c_REF_2 */
#define PSI5_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: psi5_std_c_REF_3 */
#include "Psi5_MemMap.h"

void Psi5_Std_SetReceiveChSlot_Width(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                     const Psi5_ChSlot_Width *const width)
{
    /* #Violation: psi5_std_c_REF_1 */
    PSI5_CH_RX_SLOT_CTRL0 tempSLOTCTRL0;
    /* #Violation: psi5_std_c_REF_1 */
    PSI5_CH_RX_SLOT_CTRL1 tempSLOTCTRL1;

    tempSLOTCTRL0.U = 0U;
    tempSLOTCTRL1.U = 0U;

    tempSLOTCTRL0.B.RX_SLOT0_WIDTH = width->chSlot_Width0;
    tempSLOTCTRL0.B.RX_SLOT1_WIDTH = width->chSlot_Width1;
    tempSLOTCTRL0.B.RX_SLOT2_WIDTH = width->chSlot_Width2;
    tempSLOTCTRL0.B.RX_SLOT3_WIDTH = width->chSlot_Width3;
    tempSLOTCTRL1.B.RX_SLOT4_WIDTH = width->chSlot_Width4;
    tempSLOTCTRL1.B.RX_SLOT5_WIDTH = width->chSlot_Width5;

    pPsi5->CH[channelId].CH_RX_SLOT_CTRL0.U = tempSLOTCTRL0.U;
    pPsi5->CH[channelId].CH_RX_SLOT_CTRL1.U = tempSLOTCTRL1.U;
}

void Psi5_Std_SetChSlot_Prot(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                             const Psi5_ReceiveControl *const receiveControl)
{
    uint32 tempRxControl;
    tempRxControl = 0U;

    for (uint8 i = 0; i < PSI5_NUM_SLOTS; i++)
    {
        tempRxControl |= (((uint32)receiveControl->receiveControlSlot[i].U) << (i * 4U));
    }
    pPsi5->CH[channelId].CH_RX_CONTROL.U = tempRxControl;

}

void Psi5_Std_ProtectSync(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId)
{
    boolean tempRspProt;
    tempRspProt = (boolean)(((pPsi5->CONTROL.U)>>((uint32)channelId + PSI5_RSP_PROT_OFFSET)) & (uint32)1U);

    for(uint8 i = 0; i < PSI5_NUM_SLOTS; i++)
    {
        if(tempRspProt == (uint32)PSI5_PROT_PARITY)
        {
            (pPsi5->CH[channelId].CH_RX_CONTROL.U) &= (~((uint32) 1U << ((i * 4U) + PSI5_PROT_OFFSET)));
        }
        else
        {
            (pPsi5->CH[channelId].CH_RX_CONTROL.U) |= ((uint32) 1U << ((i * 4U) + PSI5_PROT_OFFSET));
        }
    }
}


void Psi5_Std_SendChannelDataFrame4(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                    const Psi5_TransmitFrame *const pFrame)
{
    uint32 payLoadTemp;
    uint32 raddTemp;
    uint32 payloadValue;
    /* #Violation: psi5_std_c_REF_1 */
    PSI5_CH_TX_FIFO txFifoRegister;

    txFifoRegister.U = 0U;

    /* Composition control data frame */
    txFifoRegister.B1.TX_TYPE = (uint32)PSI5_TXTYPE_CTRLDATA;
    txFifoRegister.B1.TX_SADDR = (uint32)(pFrame->sAddr);
    txFifoRegister.B1.TX_CFG = 1U;
    txFifoRegister.B1.TX_FC = (uint32)(pFrame->functionCode);
    txFifoRegister.B1.TX_BLEN = PSI5_XXLONG_BLEN;
    if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_XXLONG_ANY)
    {
        txFifoRegister.B1.TX_CFG = 0U;
    }
    pPsi5->CH[channelId].CH_TX_FIFO.U = txFifoRegister.U;

    /* Composition payload data frame */
    if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_XXLONG_SHORT)
    {
        payloadValue = (uint32)(pFrame->functionCode);
    }
    else if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_XXLONG_LONG1)
    {
        payLoadTemp = (pFrame->payLoadData) << PSI5_XXLONG_LONG1_PAYLOADOFFSET;
        raddTemp = (uint32)(pFrame->rAddr) << PSI5_XXLONG_LONG1_RADDROFFSET;
        payloadValue = payLoadTemp | raddTemp | (uint32)(pFrame->functionCode);

    }
    else if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_XXLONG_LONG2)
    {
        payLoadTemp = (pFrame->payLoadData) << PSI5_XXLONG_LONG2_PAYLOADOFFSET;
        raddTemp = ((uint32)(pFrame->rAddr)) << PSI5_XXLONG_LONG2_RADDROFFSET;
        payloadValue = payLoadTemp | raddTemp | (uint32)(pFrame->functionCode);
    }
    else if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_XXLONG_XLONG)
    {
        payLoadTemp = (pFrame->payLoadData) << PSI5_XXLONG_XLONG_PAYLOADOFFSET;
        raddTemp = ((uint32)(pFrame->rAddr)) << PSI5_XXLONG_XLONG_RADDROFFSET;
        payloadValue = payLoadTemp | raddTemp | (uint32)(pFrame->functionCode);
    }
    else
    {
        payloadValue = (pFrame->payLoadData);
    }
    txFifoRegister.B2.TX_TYPE = (uint32)PSI5_TXTYPE_PAYLOADDATA;
    txFifoRegister.B2.TX_PAYLOAD = payloadValue;
    pPsi5->CH[channelId].CH_TX_FIFO.U = txFifoRegister.U;

}


void Psi5_Std_SendChannelDataFrame13(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                     const Psi5_TransmitFrame *const pFrame)
{
    uint32 payLoadTemp;
    uint32 payloadValue;
    /* #Violation: psi5_std_c_REF_1 */
    PSI5_CH_TX_FIFO txFifoRegister;

    txFifoRegister.U = 0U;

    /* Composition control data frame */
    txFifoRegister.B1.TX_TYPE = (uint32)PSI5_TXTYPE_CTRLDATA;
    txFifoRegister.B1.TX_SADDR = (uint32)(pFrame->sAddr);
    txFifoRegister.B1.TX_CFG = 0U;
    txFifoRegister.B1.TX_FC = (uint32)(pFrame->functionCode);

    if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_SHORT)
    {
        txFifoRegister.B1.TX_BLEN = PSI5_SHORT_BLEN;
    }
    else if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_XLONG)
    {
        txFifoRegister.B1.TX_BLEN = PSI5_XLONG_BLEN;
    }
    else
    {
        txFifoRegister.B1.TX_BLEN = PSI5_LONG_BLEN;
    }
    pPsi5->CH[channelId].CH_TX_FIFO.U = txFifoRegister.U;

    /* Composition payload data frame */
    if((uint32)(pFrame->frameType) != (uint32)PSI5_FRAMETYPE_SHORT)
    {
        if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_LONG1)
        {
            payLoadTemp = (uint32)(pFrame->payLoadData) << PSI5_LONG1_PAYLOADOFFSET;
            payloadValue = payLoadTemp | ((uint32)(pFrame->rAddr));
        }
        else if((uint32)(pFrame->frameType) == (uint32)PSI5_FRAMETYPE_LONG2)
        {
            payLoadTemp = (uint32)(pFrame->payLoadData) << PSI5_LONG2_PAYLOADOFFSET;
            payloadValue = payLoadTemp | (uint32)(pFrame->rAddr);
        }
        else
        {
            payLoadTemp = (uint32)(pFrame->payLoadData) << PSI5_XLONG_PAYLOADOFFSET;
            payloadValue = payLoadTemp | (uint32)(pFrame->rAddr);
        }
        txFifoRegister.B2.TX_TYPE = (uint32)PSI5_TXTYPE_PAYLOADDATA;
        txFifoRegister.B2.TX_PAYLOAD = payloadValue;
        pPsi5->CH[channelId].CH_TX_FIFO.U = txFifoRegister.U;
    }

}

/* #Violation: psi5_std_c_REF_2 */
#define PSI5_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: psi5_std_c_REF_3 */
#include "Psi5_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
