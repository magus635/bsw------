/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    can_std.c
 * Author:      00949
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all implementations of requirements of CAN module.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#can_std_c_REF_1:CERTC-INT36-C;
* Justification:Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
*#can_std_c_REF_2:CERTC-EXP36-C;
* Justification:Necessary type casting for memory and/or register accessing.
*
*#can_std_c_REF_3:MISRAC2012-Dir-1.1;
* Justification:Necessary type casting for memory and/or register accessing.
*
*#can_std_c_REF_4:MISRAC2012-Rule-11.4;
* Justification:The register must load the buffer's address.
*
*#can_std_c_REF_5:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#can_std_c_REF_6:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#can_std_c_REF_7:CWE-1701;
* Justification:MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#can_std_c_REF_8:CWE-704;
* Justification:Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
*#can_std_c_REF_9:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "can_register.h"
#include "can_std.h"
#include "tha6_cfg.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Variables Definition
 *********************************************************************************************************************/
#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: can_std_c_REF_9 */
#include "Can_MemMap.h"
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Can_Std_SetITRouter1Line
 * Description:  Set the selected group1 interrupt to the selected interrupt line
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: Type of Interrupt, see #arg CAN_STD_IT_RouterFlags
 *               itLine: Interrupt line number(0 ~ 15)
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/05/08    00976      Create
 *********************************************************************************************************************/
static boolean Can_Std_SetITRouter1Line(CAN_NODE *const pNode, uint32 it, uint32 itLine);

/**********************************************************************************************************************
 * Function:     Can_Std_SetITRouter2Line
 * Description:  Set the selected group2 interrupt to the selected interrupt line
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specify a pointer to the CAN node register
 *               it: Type of Interrupt, see #arg CAN_STD_IT_RouterFlags
 *               itLine: Interrupt line number(0 ~ 15)
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/05/08    00976      Create
 *********************************************************************************************************************/
static boolean Can_Std_SetITRouter2Line(CAN_NODE *const pNode, uint32 it, uint32 itLine);

/**********************************************************************************************************************
 * Function:     Can_Std_GetRxBuffMessage
 * Description:  Get an CAN frame from the Rx Buffer zone into the message RAM.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               rxLocation: dedicated RX buffer number of #arg CAN_STD_RxLocation
 *               pHeader: Specifies the pointer to receive header
 *               pData: pointer to a buffer where the pay-load of the RX frame will be stored
 * Inout:        None
 * Output:       pHeader: Specifies the pointer to receive header
 * Return:       None
 * Others:
 * History:
 *  Date         Author    Modified
 *  2025/05/08    00976      Create
 *********************************************************************************************************************/
static void Can_Std_GetRxBuffMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RXMSG *const pHeader, uint8* const pData);

/**********************************************************************************************************************
 * Function:     Can_Std_GetRxFifoMessage
 * Description:  Get an CAN frame from the Rx FIFO zone into the message RAM.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pNode: Specifies the pointer to the CAN node registers
 *               rxLocation: FIFO 0 or FIFO 1 of #arg CAN_STD_RxLocation
 *               pHeader: Specifies the pointer to receive header
 *               pData: pointer to a buffer where the pay-load of the RX frame will be stored
 * Inout:        None
 * Output:       pHeader: Specifies the pointer to receive header
 * Return:       None
 * Others:
 * History:
 *  Date         Author    Modified
 *  2023/09/03   01107     Create
 *********************************************************************************************************************/
static void Can_Std_GetRxFifoMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RXMSG *const pHeader, uint8* const pData);
 /**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static boolean Can_Std_SetITRouter1Line(CAN_NODE *const pNode, uint32 it, uint32 itLine)
{
    boolean ret;
    uint32 itMsk;
    
    ret = TRUE;
    itMsk = (it & CAN_STD_IT_MASK);

    /* 08. TE FIFO, total 2 interrupt request  */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_TEFIFO))
    {
        pNode->GRINT1.B.TEFIFO = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT1.B.TEFIFO, itLine);
        pNode->ISREG_EN.B.TEFIFOE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.TEFIFOE, TRUE);
    }

    /* 09. HPE  */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_HPE))
    {
        pNode->GRINT1.B.HPE = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT1.B.HPE, itLine);
        pNode->ISREG_EN.B.HPEE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.HPEE, TRUE);
    }

    /* 10. Wait, total 3 interrupt request */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_WAIT))
    {
        pNode->GRINT1.B.WATI = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT1.B.WATI, itLine);
        pNode->ISREG_EN.B.WATIE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.WATIE, TRUE);
    }

    /* 11. Alert, total 8 interrupt request */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_ALERT))
    {
        pNode->GRINT1.B.ALRT = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT1.B.ALRT, itLine);
        pNode->ISREG_EN.B.ALRTE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.ALRTE, TRUE);
    }

    /* 12. More, total 2 interrupt request */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_MORE))
    {
        pNode->GRINT1.B.MOER = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT1.B.MOER, itLine);
        pNode->ISREG_EN.B.MOERE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.MOERE, TRUE);
    }

    /* 13. Safe */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_SAFE))
    {
        pNode->GRINT1.B.SAFE = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT1.B.SAFE, itLine);
        pNode->ISREG_EN.B.SAFEE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.SAFEE, TRUE);
    }

    /* 14. Bus off */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_BUSOFF))
    {
        pNode->GRINT1.B.BOFF = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT1.B.BOFF, itLine);
        pNode->ISREG_EN.B.BOFFE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.BOFFE, TRUE);
    }

    /* 15. LOI, total 2 interrupt request */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_LOI))
    {
        pNode->GRINT1.B.LOI = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT1.B.LOI, itLine);
        pNode->ISREG_EN.B.LOIE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.LOIE, TRUE);
    }

    return ret;
}

static boolean Can_Std_SetITRouter2Line(CAN_NODE *const pNode, uint32 it, uint32 itLine)
{
    boolean ret = TRUE;
    uint32 itMsk;

    itMsk = (it & CAN_STD_IT_MASK);

    /* 00. REINT */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_REINT))
    {
        pNode->GRINT2.B.REINT = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT2.B.REINT, itLine);
        pNode->ISREG_EN.B.REINTEE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.REINTEE, TRUE);
    }

    /* 01. RXF1F */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_RXF1F))
    {
        pNode->GRINT2.B.RXF1F = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT2.B.RXF1F, itLine);
        pNode->ISREG_EN.B.RxF1FE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.RxF1FE, TRUE);
    }

    /* 02. RXF0F */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_RXF0F))
    {
        pNode->GRINT2.B.RXF0F = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT2.B.RXF0F, itLine);
        pNode->ISREG_EN.B.RxF0FE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.RxF0FE, TRUE);
    }

    /* 03. RXF1N */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_RXF1N))
    {
        pNode->GRINT2.B.RXF1N = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT2.B.RXF1N, itLine);
        pNode->ISREG_EN.B.RxF1NE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.RxF1NE, TRUE);
    }

    /* 04. RXF0N */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_RXF0N))
    {
        pNode->GRINT2.B.RXF0N = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT2.B.RXF0N, itLine);
        pNode->ISREG_EN.B.RxF0NE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.RxF0NE, TRUE);
    }

     /* 05. RETI */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_RETI))
    {
        pNode->GRINT2.B.RETI = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT2.B.RETI, itLine);
        pNode->ISREG_EN.B.RETIE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.RETIE, TRUE);
    }

    /* 06. TRAQ */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_TRAQ))
    {
        pNode->GRINT2.B.TRAQ = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT2.B.TRAQ, itLine);
        pNode->ISREG_EN.B.TRAQE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.TRAQE, TRUE);
    }

    /* 07. TRACO, total 2 interrupt request  */
    if (0U != (itMsk & CAN_STD_IT_ROUTER_TRACO))
    {
        pNode->GRINT2.B.TRACO = itLine;
        ret = Can_Register_ReadBack_Check(ret, pNode->GRINT2.B.TRACO, itLine);
        pNode->ISREG_EN.B.TRACOE = TRUE;
        ret = Can_Register_ReadBack_Check(ret, pNode->ISREG_EN.B.TRACOE, TRUE);
    }

    return ret;
}


static void Can_Std_GetRxBuffMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RXMSG *const pHeader, uint8* const pData)
{
    uint32 loopCount;

    uint32 rxAddress;

    CAN_RXMSG const volatile *pRxMsg;

    uint8 const volatile *pAddr8Bit;

    uint32 rxLocationTmp;

    rxLocationTmp = rxLocation;

    rxAddress = Can_Std_GetModuleBase(pNode);

    if (0U != rxAddress)
    {
        rxAddress += ((uint32)pNode->RX.BC.B.RBSA << 2U) + (Can_Std_ElementSzieToBytes(pNode->RX.ESC.B.RBDS) * rxLocationTmp);

        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        pRxMsg = (CAN_RXMSG *)rxAddress;

        pHeader->R0.U = pRxMsg->R0.U;

        pHeader->R1.U = pRxMsg->R1.U;

        pAddr8Bit = (uint8 const volatile*)pRxMsg->DB;

        for(loopCount = 0; loopCount < Can_Std_DlcToBytes(pHeader->R1.B.DLC); loopCount++)
        {
            pData[loopCount] = pAddr8Bit[loopCount];
        }

        if (rxLocationTmp < CAN_STD_RXLOCATION_BUFFER_32)
        {
            pNode->NDAT1.U = ((uint32)1U << rxLocationTmp);
        }
        else
        {
            rxLocationTmp -= 32U;
            pNode->NDAT2.U = ((uint32)1U << rxLocationTmp);
        }
    }
}


static void Can_Std_GetRxFifoMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RXMSG *const pHeader, uint8* const pData)
{
    uint32 loopCount;

    uint32 loopCountMax;

    uint32 loopCntWord;

    uint32 loopCntReByte;

    uint32 const volatile*pAddr32Bit;

    uint8 const volatile*pAddr8Bit;

    uint32 *pData32Bit;

    uint8 *pData8Bit;

    uint32 tempData;

    uint32 rxLocationTmp;

    uint32 rxAddress;

    rxAddress = Can_Std_GetModuleBase(pNode);

    if (rxLocation == CAN_STD_RXLOCATION_FIFO0)
    {
            /* Check that the Rx FIFO 0 is full & overwrite mode is on*/
        if ((0U != pNode->RX.F0S.B.F0F) && (0U != pNode->RX.F0C.B.F0OM))
        {
            /* When overwrite status is on discard first message in FIFO */
            pNode->RX.F0A.B.F0AI = pNode->RX.F0S.B.F0GI;
        }

        rxLocationTmp = pNode->RX.F0S.B.F0GI;

        rxAddress += ((uint32)pNode->RX.F0C.B.F0SA << 2U) + (Can_Std_ElementSzieToBytes(pNode->RX.ESC.B.F0DS) * rxLocationTmp);
    }
    else
    {
        /* Check that the Rx FIFO 1 is full and overwrite mode is on*/
        if ((0U != pNode->RX.F1S.B.F1F) && (0U != pNode->RX.F1C.B.F1OM))
        {
            /* When overwrite status is on discard first message in FIFO */
            pNode->RX.F1A.B.F1AI = pNode->RX.F1S.B.F1GI;
        }

        rxLocationTmp = pNode->RX.F1S.B.F1GI;

        rxAddress += ((uint32)pNode->RX.F1C.B.F1SA << 2U) + (Can_Std_ElementSzieToBytes(pNode->RX.ESC.B.F1DS) * rxLocationTmp);
    }

    /* #Violation: can_std_c_REF_1 */
    /* #Violation: can_std_c_REF_5 */
    /* #Violation: can_std_c_REF_8 */
    /* #Violation: can_hal_c_REF_12 */
    pAddr32Bit = (uint32 *)rxAddress;

    pHeader->R0.U = pAddr32Bit[0];
    pHeader->R1.U = pAddr32Bit[1];

    /* #Violation: can_std_c_REF_1 */
    /* #Violation: can_std_c_REF_5 */
    /* #Violation: can_std_c_REF_8 */
    /* #Violation: can_hal_c_REF_12 */
    pAddr32Bit = (uint32 *)(rxAddress + 8U);

    loopCountMax = Can_Std_DlcToBytes(pHeader->R1.B.DLC);

    loopCntWord = loopCountMax / 4U;
    loopCntReByte = loopCountMax % 4U;

    /* #Violation: can_std_c_REF_2 */
    /* #Violation: can_std_c_REF_3 */
    if (0U == ((uint32)pData & 0x3U))
    {
        /* word align */
        /* word copy */
        /* #Violation: can_std_c_REF_3 */
        pData32Bit = (void *)pData;
        for (loopCount = 0U; loopCount < loopCntWord; loopCount++)
        {
            pData32Bit[loopCount] = pAddr32Bit[loopCount];
        }

        /* byte copy for reset data less than 1 word */
        /* #Violation: can_std_c_REF_3 */
        pData8Bit = (void *)(&pData32Bit[loopCntWord]);
    }
    else
    {
        /* byte align */
        /* #Violation: can_std_c_REF_3 */
        pData8Bit = (void *)pData;
        for (loopCount = 0U; loopCount < loopCntWord; loopCount++)
        {
            tempData = pAddr32Bit[loopCount];

            pData8Bit[(4U*loopCount)]        = (uint8)tempData;
            pData8Bit[(4U*loopCount) + 1U]   = (uint8)(tempData >> 8U);
            pData8Bit[(4U*loopCount) + 2U]   = (uint8)(tempData >> 16U);
            pData8Bit[(4U*loopCount) + 3U]   = (uint8)(tempData >> 24U);
        }

        /* #Violation: can_std_c_REF_3 */
        pData8Bit = (void *)(&pData8Bit[4U*loopCntWord]);
    }

    /* byte copy for reset data less than 1 word */
    if (loopCntReByte != 0U)
    {
        tempData = pAddr32Bit[loopCntWord];
        /* #Violation: can_std_c_REF_3 */
        pAddr8Bit = (void *)(&tempData);
        for (loopCount = 0U; loopCount < loopCntReByte; loopCount++)
        {
            pData8Bit[loopCount] = pAddr8Bit[loopCount];
        }
    }

    /* ACK */
    if (rxLocation == CAN_STD_RXLOCATION_FIFO0)
    {
        pNode->RX.F0A.B.F0AI = rxLocationTmp;
    }
    else
    {
        pNode->RX.F1A.B.F1AI = rxLocationTmp;
    }

}



/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
uint32 Can_Std_GetModuleBase(const CAN_NODE *const pNode)
{
    uint32 moduleBaseAddress;

    uint32 nodeIndex;

    /* #Violation: can_std_c_REF_5 */
    /* #Violation: can_std_c_REF_6 */
    nodeIndex = CAN_NODE_INDEX(pNode);

    if (CAN_NODE_MAX_IN_MODULE > nodeIndex)
    {
        /* #Violation: can_std_c_REF_5 */
        moduleBaseAddress = (uint32)pNode - (sizeof(CAN_NODE) * nodeIndex);
    }
    else
    {
        moduleBaseAddress = 0;
    }

    return moduleBaseAddress;
}

uint32 Can_Std_GetModuleRAMStartAddr(const CAN_NODE *const pNode)
{
    uint32 moduleBaseAddress;

    uint32 msgStartAddress;

    uint32 nodeIndex;

    /* #Violation: can_std_c_REF_3 */
    /* #Violation: can_std_c_REF_4 */
    /* #Violation: can_std_c_REF_6 */
    nodeIndex = CAN_NODE_INDEX(pNode);

    if (CAN_NODE_MAX_IN_MODULE > nodeIndex)
    {
        /* #Violation: can_std_c_REF_3 */
        /* #Violation: can_std_c_REF_4 */
        /* #Violation: can_std_c_REF_10 */
        moduleBaseAddress = (uint32)pNode - (sizeof(CAN_NODE) * nodeIndex);
        /* #Violation: can_std_c_REF_3 */
        /* #Violation: can_std_c_REF_4 */
        /* #Violation: can_std_c_REF_10 */
        msgStartAddress = (uint32)((CAN_MODULE *)moduleBaseAddress)->RAM;
    }
    else
    {
        msgStartAddress = 0U;
    }

    return msgStartAddress;
}

uint32 Can_Std_GetModuleRAMEndAddr(const CAN_NODE *const pNode)
{
    uint32 moduleAddress;

    CAN_MODULE const volatile *pModule;

    uint32 msgEndAddress;

    uint32 nodeIndex;

    /* #Violation: can_std_c_REF_3 */
    /* #Violation: can_std_c_REF_4 */
    /* #Violation: can_std_c_REF_6 */
    nodeIndex = CAN_NODE_INDEX(pNode);

    if (CAN_NODE_MAX_IN_MODULE > nodeIndex)
    {
        /* #Violation: can_std_c_REF_3 */
        /* #Violation: can_std_c_REF_4 */
        moduleAddress =  (uint32)pNode - (sizeof(CAN_NODE) * nodeIndex);
        /* #Violation: can_std_c_REF_3 */
        /* #Violation: can_std_c_REF_5 */
        pModule =  (CAN_MODULE*)moduleAddress;

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        /* #Violation: can_std_c_REF_3 */
        /* #Violation: can_std_c_REF_10 */
        /* #Violation: can_std_c_REF_10 */
        msgEndAddress = (uint32)&pModule->RAM[CAN_STD_MODULE_RAM_SIZE] - 4U;
#endif

#if defined(THA6_THA6104) 
        /* #Violation: can_std_c_REF_5 */
        if (CAN0 == pModule)
        {
            /* #Violation: can_std_c_REF_3 */
            /* #Violation: can_std_c_REF_4 */
            msgEndAddress = (uint32)&pModule->RAM[CAN_STD_MODULE_RAM_SIZE] - 4U;
        }
        else
        {
            /* message ram size in CAN1 module is half of ram size in CAN0 module */
            /* #Violation: can_std_c_REF_3 */
            /* #Violation: can_std_c_REF_4 */
            msgEndAddress = (uint32)&pModule->RAM[CAN_STD_MODULE_RAM_SIZE/2U] - 4U;
        }
#endif        
    }
    else
    {
        msgEndAddress = 0UL;
    }

    return msgEndAddress;
}

boolean Can_Std_ActivateNotification(CAN_NODE *const pNode, uint32 activeITs, uint32 bufferIndexes)
{
    boolean ret;

    ret = TRUE;

    if (0U == (pNode->ILS.U & activeITs))
    {
        /* Enable Interrupt line 0 */
        pNode->ILE.B.EINT0 = 1U;
        ret = Can_Register_ReadBack_Check(ret, pNode->ILE.B.EINT0, 1U);
    }
    else if ((pNode->ILS.U & activeITs) == activeITs)
    {
        /* Enable Interrupt line 1 */
        pNode->ILE.B.EINT1 = 1U;
        ret = Can_Register_ReadBack_Check(ret, pNode->ILE.B.EINT1, 1U);
    }
    else
    {
        /* Enable Interrupt lines 0 and 1 */
        pNode->ILE.B.EINT0 = 1U;
        pNode->ILE.B.EINT1 = 1U;
        ret = Can_Register_ReadBack_Check(ret, pNode->ILE.U, 3U);
    }

    if (0U != (activeITs & CAN_STD_IT_TXCOMPLETED))
    {
         /* Enable Tx Buffer Transmission Interrupt to set TC flag in IR register,
         but interrupt will only occur if TC is enabled in IE register */
        pNode->TX.BTIE.U |= bufferIndexes;
        ret = Can_Register_ReadBack_Check(ret, (pNode->TX.BTIE.U&bufferIndexes), bufferIndexes);
    }

    if (0U != (activeITs & CAN_STD_IT_TXCANCELLATIONFIN))
    {
         /* Enable Tx Buffer Cancellation Finished Interrupt to set TCF flag in IR register,
         but interrupt will only occur if TCF is enabled in IE register */
        pNode->TX.BCIE.U |= bufferIndexes;
        ret = Can_Register_ReadBack_Check(ret, (pNode->TX.BCIE.U&bufferIndexes), bufferIndexes);
    }

    pNode->IE.U |= activeITs;
    ret = Can_Register_ReadBack_Check(ret, (pNode->IE.U&activeITs), activeITs);

    return ret;
}

boolean Can_Std_DeactivateNotification(CAN_NODE *const pNode, uint32 inactiveITs)
{
    boolean ret;
    uint32 itLineSelection;
    
    ret = TRUE;

    pNode->IE.U &= ~inactiveITs;

    ret = Can_Register_ReadBack_Check(ret, (pNode->IE.U&inactiveITs), 0U);

    if (0U != (inactiveITs & CAN_STD_IT_TXCOMPLETED))
    {
        /* Disable Tx Buffer Transmission Interrupts */
        pNode->TX.BTIE.U = 0U;
        ret = Can_Register_ReadBack_Check(ret, pNode->TX.BTIE.U, 0U);
    }

    if (0U != (inactiveITs & CAN_STD_IT_TXCANCELLATIONFIN))
    {
        /* Disable Tx Buffer Cancellation Finished Interrupt */
        pNode->TX.BCIE.U = 0U;
        ret = Can_Register_ReadBack_Check(ret, pNode->TX.BCIE.U, 0U);
    }

    itLineSelection = pNode->ILS.U;

    if ((pNode->IE.U | itLineSelection) == itLineSelection)
    {
        /* Disable Interrupt line 0 */
        pNode->ILE.B.EINT0 = 0U;
        ret = Can_Register_ReadBack_Check(ret, pNode->ILE.B.EINT0, 0U);
    }

    if (0U == (pNode->IE.U & itLineSelection))
    {
        /* Disable Interrupt line 1 */
        pNode->ILE.B.EINT1 = 0U;
        ret = Can_Register_ReadBack_Check(ret, pNode->ILE.B.EINT1, 0U);
    }

    return ret;
}


void Can_Std_AddMessageToTxBuffer(CAN_NODE *const pNode, uint32 txLocation,
                                    const CAN_TXMSG *const pTxHeaderSrc, uint32 immediatelySend,
                                    const uint8 *const pTxData)
{
    boolean pending;

    uint32 loopCount;

    uint32 txAddress;

    volatile uint32 *pAddr;

    CAN_TXMSG *pTxHeader;

    uint32 putIndex;

    pending = FALSE;

    txAddress = Can_Std_GetModuleBase(pNode);
    txAddress += ((uint32)pNode->TX.BC.B.TBSA << 2U);

    if (txLocation < CAN_STD_TXLOCATION_FIFO_QUEUE)
    {
        putIndex = txLocation;
        txAddress += Can_Std_ElementSzieToBytes(pNode->TX.ESC.B.TBDS) * putIndex;
    }
    else /* txLocation == CAN_STD_TXLOCATION_FIFO_QUEUE */
    {
        putIndex = pNode->TX.FQS.B.TFQPI;
        txAddress += Can_Std_ElementSzieToBytes(pNode->TX.ESC.B.TBDS) * putIndex; 
    }

    if (0U != (pNode->TX.BRP.U & ((uint32)1U << putIndex)))
    {
        pending = TRUE;
    }

    if (FALSE == pending)
    {
        /* #Violation: can_std_c_REF_1 */
        /* #Violation: can_std_c_REF_5 */
        /* #Violation: can_std_c_REF_8 */
        pTxHeader = (CAN_TXMSG *)txAddress;

        pTxHeader->T0 = pTxHeaderSrc->T0;

        pTxHeader->T1 = pTxHeaderSrc->T1;

        pAddr = pTxHeader->DB;

        /* write data into the data section of Tx Buffer element  */
        for(loopCount = 0U; loopCount < Can_Std_DlcToBytes(pTxHeaderSrc->T1.B.DLC); loopCount += 4U)
        {
            *pAddr = (((uint32)pTxData[loopCount + 3U] << 24U) |
                    ((uint32)pTxData[loopCount + 2U] << 16U) |
                    ((uint32)pTxData[loopCount + 1U] << 8U)  |
                    ((uint32)pTxData[loopCount]));
            pAddr++;
        }

        if (txLocation < CAN_STD_TXLOCATION_FIFO_QUEUE)
        {
            if (0U != immediatelySend)
            {
                /* TXBAR bits are set only for those Tx Buffers configured via TXBC. When no Tx scan is running, 
                the bits are reset immediately, else the bits remain set until the Tx scan process has completed. */
                pNode->TX.BAR.U = ((uint32)1U << putIndex);
            }   
        }
        else /* txLocation == CAN_STD_TXLOCATION_FIFO_QUEUE */
        {
            /* TXBAR bits are set only for those Tx fifo configured via TXBC. */
            pNode->TX.BAR.U = ((uint32)1U << putIndex);
        }
    }
}

void Can_Std_GetRxMessage(CAN_NODE *const pNode, uint32 rxLocation, CAN_RXMSG *const pHeader, uint8* const pData)
{
    if (rxLocation <= CAN_STD_RXLOCATION_BUFFER_63)
    {
        Can_Std_GetRxBuffMessage(pNode, rxLocation, pHeader, pData);
    }
    else if (rxLocation <= CAN_STD_RXLOCATION_FIFO1)
    {
        Can_Std_GetRxFifoMessage(pNode, rxLocation, pHeader, pData);
    }
    /* #Violation: can_std_c_REF_7 */
    else
    {
        /* N.A */
    }
}

void Can_Std_GetTxEvent(CAN_NODE *const pNode, CAN_TXEVENT* const pHeader)
{
    uint32 evAddress;
    uint32 evGetIdx;
    uint32 const volatile *pAddr32Bit;
    
    evGetIdx = (uint32)pNode->TX.EFS.B.EFGI;
    evAddress = Can_Std_GetModuleBase(pNode);
    evAddress += (uint32)pNode->TX.EFC.B.EFSA << 2U;
    evAddress += 8U*evGetIdx;

    /* #Violation: can_std_c_REF_1 */
    /* #Violation: can_std_c_REF_5 */
    /* #Violation: can_std_c_REF_8 */
    pAddr32Bit = (uint32*)evAddress;

    pHeader->E0.U = pAddr32Bit[0];

    pHeader->E1.U = pAddr32Bit[1];

    pNode->TX.EFA.B.EFAI = evGetIdx;
}


boolean Can_Std_SetITRouterLine(CAN_NODE *const pNode, uint32 it, uint32 itLine)
{
    boolean ret = TRUE;

    ret &= Can_Std_SetITRouter1Line(pNode, it, itLine);
    ret &= Can_Std_SetITRouter2Line(pNode, it, itLine);

    return ret;
}

#define CAN_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: can_std_c_REF_9 */
#include "Can_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
