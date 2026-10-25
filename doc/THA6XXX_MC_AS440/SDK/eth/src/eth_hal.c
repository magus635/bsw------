/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    eth_hal.c
 * Author:      00930
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file implement the functions of ETH module.
 *********************************************************************************************************************/

/*
* #Violation Summary
* #eth_hal_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
* #eth_hal_c_REF_2:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
* #eth_hal_c_REF_3:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
* #eth_hal_c_REF_4:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
* #eth_hal_c_REF_5:MISRAC2012-Rule-11.4;
* Justification: The register must load the buffer's address.
*
* #eth_hal_c_REF_6:MISRAC2012-Rule-10.5;
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
* #eth_hal_c_REF_7:MISRAC2012-Rule-2.2;
* Justification: Platform-based design with configurable macros.
*
* #eth_hal_c_REF_8:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
* #eth_hal_c_REF_9:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #eth_hal_c_REF_10:CertC-DCL02-C;
* Justification: Company-specific naming conventions are applied. Developers will not be confused.
*
* #eth_hal_c_REF_11:CertC-DCL15-C;
* Justification: Reserved API for user access
*
* #eth_hal_c_REF_12:CertC-INT36-C;
* Justification: Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
* #eth_hal_c_REF_13:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
* #eth_hal_c_REF_14:CWE-704;
* Justification: Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
* #eth_hal_c_REF_15:CertC-DCL19-C;
* Justification: Reserved API for user access
*
* #eth_hal_c_REF_16:CWE-1071;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block
*
* #eth_hal_c_REF_17:MISRAC2012-Rule-8.7;
* Justification: The function is used by other file.
*
* #eth_hal_c_REF_18:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #eth_hal_c_REF_19:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Eth_Cfg.h"
#include "eth_hal.h"
#include "stm_hal.h"
#include "eth_std.h"
#include "eth_register.h"
#include "Platform_Types.h"
#include "cpuwdt_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/

#define ETH_RDES0_IVT_MASK (0xFFFF0000U)
#define ETH_RDES0_IVT_SHIFT (16U)
#define ETH_RDES0_OVT_MASK (0x0000FFFFU)

#define ETH_MAC_ADDRESS_GROUP_MAXNUM (6U)

/* To indicate that drop count or Ether status is not available. */
#define ETH_COUNTER_NOT_AVAILABLE (0xFFFFFFFFU)
/* #Violation: eth_hal_c_REF_1 */
/* #Violation: eth_hal_c_REF_13 */
#define ETH_HAL_STONS_FLOAT64(Seconds) ((float64)((float64)(Seconds) * (float64)1000000000ULL))
/* Initiate a read or write access to the MDIO slave */
#define ETH_INITIATE_RDWR_MDIO (1U)
/* Enable ETH receiver queue type */
#define ETH_QUEUE_EN_DCB_GEN (2U)
/* Enable all DMA Tx/Rx interrupt */
#define ETH_ENABLE_ALL_DMA_INTERRUPT (0xFFC7U)
#if !(defined(ETH_SPLICING_ENABLE) && (ETH_SPLICING_ENABLE == TRUE))
/* RDES3 State, own by application, LD and FD are set */
#define ETH_RDES3_OWN_LD_FD (0x30000000U)
#endif
/* The context descriptor is valid */
#define ETH_CONTEXT_DESCR_VALID (0x40000000U)
/* The context descriptor mask */
#define ETH_CONTEXT_DESCR_MASK (0xD0000000U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: eth_hal_c_REF_18 */
#define ETH_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: eth_hal_c_REF_19 */
#include "Eth_MemMap.h"
/**********************************************************************************************************************
 * Function:     Eth_Hal_SetPhyInterfaceMode
 * Description:  Set the phy interface mode and set time-delay when the mode is RGMII mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               mode: External Phy Interface RMII Mode
 *               txClkDelay: The time-delay of transmission in RGMII mode
 *               rxClkDelay: The time-delay of reception in RGMII mode
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_SetPhyInterfaceMode(ETH_MODULE *const pEthModule, Eth_PhyInterfaceMode mode, 
                                        Eth_ClkDelay txClkDelay, Eth_ClkDelay rxClkDelay);

/**********************************************************************************************************************
 * Function:     Eth_Hal_InitTransmitDescriptors
 * Description:  Initialize the transmitting Descriptors
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTxChannelConfig: Pointer to structure for ETH DMA Tx channel configuration
 *               channelId: DMA channel Index
 * Inout:        None
 * Output:       pEthNode: Pointer to the Structure for ETH driver handle
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_InitTransmitDescriptors(const Eth_NodeHandle *const pEthNode, const Eth_TxChannelConfig *const pTxChannelConfig,
                                            Eth_DmaChannel channelId);

/**********************************************************************************************************************
 * Function:     Eth_Hal_InitReceiveDescriptors
 * Description:  Initialize the receiving Descriptors
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pRxChannelConfig: Pointer to structure for ETH DMA Rx channel configuration
 *               channelId: DMA channel Index
 * Inout:        None
 * Output:       pEthNode: Pointer to the Structure for ETH driver handle
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_InitReceiveDescriptors(const Eth_NodeHandle *const pEthNode, const Eth_RxChannelConfig *const pRxChannelConfig,
                                           Eth_DmaChannel channelId);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ResetTransmitDescriptors
 * Description:  Reset the transmitting Descriptors
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: DMA channel Index
 *               curBufIdx: Current descriptor index
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/12/11    00930      Create
 *********************************************************************************************************************/
static void Eth_Hal_ResetTransmitDescriptors(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId,
                                             uint32 curBufIdx);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ResetReceiveDescriptors
 * Description:  Reset the receiving Descriptors
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: DMA channel Index
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/12/11    00930      Create
 *********************************************************************************************************************/
static void Eth_Hal_ResetReceiveDescriptors(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ConfigureDma
 * Description:  Configure the operating mode of the DMA
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthConfig: Pointer to configuration structure for the DMA initialization
 * Inout:        None
 * Output:       pEthNode: Pointer to the Structure for ETH driver handle
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_ConfigureDma(const Eth_NodeHandle *const pEthNode, const Eth_Config *const pEthConfig);

/**********************************************************************************************************************
 * Function:     Eth_Hal_SetMtlRxqOperationMode
 * Description:  Set MTL_Rxq_Operation_MODE
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        regAddrMtlRxqOperationMode: Pointer to address of MTL_Rxq_Operation_MODE register
 *               queueId: Queue ID
 *               pMtlConfig: Pointer to configuration structure for the MTL initialization
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/27    00930      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_SetMtlRxqOperationMode(volatile uint32 *const regAddrMtlRxqOperationMode, Eth_MtlQueue queueId,
                                           const Eth_MtlConfig *const pMtlConfig);

/**********************************************************************************************************************
 * Function:     Eth_Hal_SetMtlRxQueue
 * Description:  Set MTL Receive queue
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               pMtlRxQueueConfig: Pointer to configuration structure for the MTL RxQueue
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/24    00930      Create
 *********************************************************************************************************************/
 static boolean Eth_Hal_SetMtlRxQueue(ETH_MODULE *const pEthModule, const Eth_MtlRxQueueConfig *const pMtlRxQueueConfig);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ClearMtlAllInterruptFlags
 * Description:  Clear MTL all interrupt flags
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               queueId: Queue ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/27    00930      Create
 *********************************************************************************************************************/
static void Eth_Hal_ClearMtlAllInterruptFlags(ETH_MODULE *const pEthModule, Eth_MtlQueue queueId);

/**********************************************************************************************************************
 * Function:     Eth_Hal_EnableMtlInterrupt
 * Description:  Enable MTL interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               queueId: Queue ID
 *               flag: MTL interrupt flag
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/27    00930      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_EnableMtlInterrupt(ETH_MODULE *const pEthModule, Eth_MtlQueue queueId,
                                       Eth_MtlInterruptFlagOrEnable flag);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ConfigureMtlTxQ
 * Description:  Configure the TxQ operating mode of the MTL
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               pEthConfig: Pointer to configuration structure for the MTL initialization
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/03    01359      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_ConfigureMtlTxQ(ETH_MODULE *const pEthModule, const Eth_Config *const pEthConfig);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ConfigureMtlRxQ
 * Description:  Configure the RxQ operating mode of the MTL
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               pEthConfig: Pointer to configuration structure for the MTL initialization
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/03    01359      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_ConfigureMtlRxQ(ETH_MODULE *const pEthModule, const Eth_Config *const pEthConfig);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ConfigureMtl
 * Description:  Configure the operating mode of the MTL
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               pEthConfig: Pointer to configuration structure for the MTL initialization
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_ConfigureMtl(ETH_MODULE *const pEthModule, const Eth_Config *const pEthConfig);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ConfigureMac
 * Description:  Configure the operating mode of the MAC
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               pMacConfig: Pointer to configuration structure for the MAC initialization
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static boolean Eth_Hal_ConfigureMac(const Eth_NodeHandle *const pEthNode, const Eth_MacConfig *const pMacConfig);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetIngressTimeStamp
 * Description:  Read ingress timestamp value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: The Rx DMA channel
 * Inout:        None
 * Output:       pRxInfo: Pointer to the receive information
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static void Eth_Hal_GetIngressTimeStamp(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, Eth_RxInfo *const pRxInfo);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetEgressTimestamp
 * Description:  Get Egress time-stamp value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthModule: Pointer to the ETH module registers
 *               pCurrDescr: Current descriptor which include timestamp
 *               pTxInfo: Pointer to the transmit information
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static void Eth_Hal_GetEgressTimestamp(const ETH_MODULE *const pEthModule, volatile const Eth_TxDescr *const pCurrDescr,
                                       Eth_TxInfo *const pTxInfo);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ShuffleTxDescriptor
 * Description:  Shuffle Transmit Descriptor
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: The Tx DMA channel
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/30    00930      Create
 *********************************************************************************************************************/
static void Eth_Hal_ShuffleTxDescriptor(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ShuffleRxDescriptor
 * Description:  Shuffle Receive Descriptor
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: The Rx DMA channel
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/30    00930      Create
 *********************************************************************************************************************/
static void Eth_Hal_ShuffleRxDescriptor(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ResetRxDescriptor
 * Description:  Release the received descriptors
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pCurDescr: Pointer to the current descriptor
 *               descrBufAddr: The current descriptor buffer1 address
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/30    00930      Create
 *********************************************************************************************************************/
static void Eth_Hal_ResetRxDescriptor(volatile Eth_RxDescr *const pCurDescr, uint32 descrBufAddr);

/**********************************************************************************************************************
 * Function:     Eth_Hal_StartDevice
 * Description:  Startup the controller(enable the DMA and MAC)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:       None
 * Return:       Eth_Status:
 *                 ETH_STATUS_OK: Successed to startup the controller and register read back check correct
 *                 ETH_STATUS_ERROR: Failed to startup the controller or register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static Eth_Status Eth_Hal_StartDevice(const Eth_NodeHandle *const pEthNode);

/**********************************************************************************************************************
 * Function:     Eth_Hal_CheckTxMTLEmpty
 * Description:  Check if Tx MTL queues are empty
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:       None
 * Return:       Eth_Status:
 *                 ETH_STATUS_OK: Success
 *                 ETH_STATUS_ERROR: Failure
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static Eth_Status Eth_Hal_CheckTxMTLEmpty(const Eth_NodeHandle *const pEthNode);

/**********************************************************************************************************************
 * Function:     Eth_Hal_StopDevice
 * Description:  Stop the controller(disable the DMA and MAC)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:       None
 * Return:       Eth_Status:
 *                 ETH_STATUS_OK: Successed to stop the controller and register read back check correct
 *                 ETH_STATUS_ERROR: Failed to stop the controller or register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
static Eth_Status Eth_Hal_StopDevice(const Eth_NodeHandle *const pEthNode);

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static boolean Eth_Hal_SetPhyInterfaceMode(ETH_MODULE *const pEthModule, Eth_PhyInterfaceMode mode,
                                        Eth_ClkDelay txClkDelay, Eth_ClkDelay rxClkDelay)
{
    /* #Violation: eth_hal_c_REF_4 */
    ETH_SKEWCTL regVal;
    boolean ret;

    ret = TRUE;
    regVal.U = 0U;
    /* Clear ENDINIT protection,the register protected by E can be written */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* Set PHY interface mode */
    pEthModule->GPCTL.B.PHYSEL = (uint32)mode;
    /* Set ENDINIT protection */
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Eth_Register_ReadBack_Check(ret, (uint32)mode, pEthModule->GPCTL.B.PHYSEL);

#if defined(THA6_THA6104)
    (void)regVal;
    (void)txClkDelay;
    (void)rxClkDelay;
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    /* If PHY interface mode is RGMII, then set Tx/Rx clock delay */
    if((ETH_PHY_INTERFACE_MII != mode) && (ETH_PHY_INTERFACE_RMII != mode))
    {
        /* Clear ENDINIT protection,the register protected by E can be written */
        DISABLE_ALL_INTERRUPTS();
        ret &= Cpuwdt_Hal_ClearEndinit();
        pEthModule->PTR.B.PHY_TXCTL_O = (uint32)ETH_TX_EN;
        regVal.B.SKEW_TX_CTRL = (uint32)txClkDelay;
        regVal.B.SKEW_RX_CTRL = (uint32)rxClkDelay;
        pEthModule->SKEWCTL.U = regVal.U;
        /* Set ENDINIT protection */
        ret &= Cpuwdt_Hal_SetEndinit();
        ENABLE_ALL_INTERRUPTS();
        ret = Eth_Register_ReadBack_Check(ret, (uint32)ETH_TX_EN, pEthModule->PTR.B.PHY_TXCTL_O);
        ret = Eth_Register_ReadBack_Check(ret, regVal.U, pEthModule->SKEWCTL.U);
    }
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
    return ret;
}

static boolean Eth_Hal_InitTransmitDescriptors(const Eth_NodeHandle *const pEthNode, const Eth_TxChannelConfig *const pTxChannelConfig,
                                               Eth_DmaChannel channelId)
{
    uint32 numberOfDes; /* Numbert of descriptor */
    uint32 buffer1StartAddress;
    volatile Eth_TxDescr *pBaseDescr;
    ETH_MODULE *pEthModule;
    boolean ret;

    ret = TRUE;
    pEthModule = pEthNode->pEthModule;
    /* #Violation: eth_hal_c_REF_5 */
    buffer1StartAddress = (uint32)pTxChannelConfig->pDescTxBuffer;
    pEthNode->txChannelInfoPtr[channelId].channelId = channelId;
    pEthNode->txChannelInfoPtr[channelId].txBuffer1Size = (uint16)pTxChannelConfig->txBufferAlignSize;
    pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor = pTxChannelConfig->pTxDescrList;
    /* Initialize descriptors in ring mode */
    for(numberOfDes = 0; numberOfDes < pTxChannelConfig->numOfTxBuffers; numberOfDes++)
    {
        /* Get descriptor list base address */
        pBaseDescr = &(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[numberOfDes]);
        /* TDES0,Set the transmit buffer address */
        pBaseDescr->TDES0.U = buffer1StartAddress + (uint32)(numberOfDes * pTxChannelConfig->txBufferAlignSize);
        pBaseDescr->TDES1.U = 0U; /* Buffer2 not used */
                                              /* TDES2 */
        pBaseDescr->TDES2.R.B1L = pTxChannelConfig->txBufferAlignSize;
        pBaseDescr->TDES2.R.VTIR = 0U;      /* Do not use VLAN tag */
        pBaseDescr->TDES2.R.B2L = 0U;       /* Buffer2 not used */
        pBaseDescr->TDES2.R.TTSE_TMWD = 0U; /* time-stamp not used */
        pBaseDescr->TDES2.R.IOC = 0U;       /* interrupt disabled */
        pEthNode->txDescrInfoPtr[channelId][numberOfDes].descrBufAddr = pBaseDescr->TDES0.U;

        /* TDES3 will be configured again while transmitting each packet */
        pBaseDescr->TDES3.U = (uint32)ETH_APPLICATION_OWN; /* owned by Application */
    }

    /* Program the Transmit Ring length registers,The ring length programmed must be at least 4. */
    pEthModule->DMA_CH[channelId].TXDESC_RING_LENGTH.U = (uint32)pTxChannelConfig->numOfTxBuffers - 1U;
    ret = Eth_Register_ReadBack_Check(ret, (uint32)pTxChannelConfig->numOfTxBuffers - 1U, pEthModule->DMA_CH[channelId].TXDESC_RING_LENGTH.U);

    /* Initialize transmit descriptor list address with the base address of the descriptor */
    /* #Violation: eth_hal_c_REF_5 */
    pEthModule->DMA_CH[channelId].TXDESC_LIST_ADDRESS.U = (uint32)&(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[0]);
    /* #Violation: eth_hal_c_REF_5 */
    ret = Eth_Register_ReadBack_Check(ret, (uint32)&(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[0]), 
        pEthModule->DMA_CH[channelId].TXDESC_LIST_ADDRESS.U);

    /* Program transmit tail pointer registers indicating to the DMA about the available descriptors */
    /* #Violation: eth_hal_c_REF_5 */
    pEthModule->DMA_CH[channelId].TXDESC_TAIL_POINTER.U = (uint32)&(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[pTxChannelConfig->numOfTxBuffers]);
    /* #Violation: eth_hal_c_REF_5 */
    ret = Eth_Register_ReadBack_Check(ret, (uint32)&(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[pTxChannelConfig->numOfTxBuffers]), 
        pEthModule->DMA_CH[channelId].TXDESC_TAIL_POINTER.U);

    /* Get current descriptor address */
    pEthNode->txChannelInfoPtr[channelId].pTxDescriptor = pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor;
    pEthNode->txChannelInfoPtr[channelId].descIndex = 0U;

    return ret;
}

static boolean Eth_Hal_InitReceiveDescriptors(const Eth_NodeHandle *const pEthNode, const Eth_RxChannelConfig *const pRxChannelConfig,
                                           Eth_DmaChannel channelId)
{
    uint32 numberOfDes; /* Number of descriptor */
    uint32 buffer1StartAddress;
    ETH_MODULE *pEthModule;
    volatile Eth_RxDescr *pBaseDescr;
    boolean ret;
    uint32 rxBufSizeHi;

    ret = TRUE;
    pEthModule = pEthNode->pEthModule;
    /* #Violation: eth_hal_c_REF_5 */
    buffer1StartAddress = (uint32)pRxChannelConfig->pDescRxBuffer;

    pEthNode->rxChannelInfoPtr[channelId].channelId = channelId;
    pEthNode->rxChannelInfoPtr[channelId].rxBuffer1Size = pRxChannelConfig->rxBufferAlignSize;
    pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor = pRxChannelConfig->pRxDescrList;

    /* Initialize descriptors in ring mode */
    for(numberOfDes = 0; numberOfDes < pRxChannelConfig->numOfRxBuffers; numberOfDes++)
    {
        /* Get descriptor list base address */
        pBaseDescr = &(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[numberOfDes]);
        pBaseDescr->RDES0.U = buffer1StartAddress + (uint32)(numberOfDes * pRxChannelConfig->rxBufferAlignSize);
        pBaseDescr->RDES2.U = 0U; /* buffer2 not used */
        pBaseDescr->RDES3.R.BUF1V = ETH_BIT_ENABLE;    /* buffer 1 valid */
        pBaseDescr->RDES3.R.BUF2V = ETH_BIT_DISABLE;   /* buffer 2 not valid */
        pBaseDescr->RDES3.R.IOC = ETH_BIT_ENABLE;      /* interrupt enabled */
        pBaseDescr->RDES3.R.OWN = (uint32)ETH_DMA_OWN; /* owned by DMA */
        pEthNode->rxDescrInfoPtr[channelId][numberOfDes].descrBufAddr = pBaseDescr->RDES0.U;
    }

    /* Program the Receive Ring length registers,The ring length programmed must be at least 4. */
    pEthModule->DMA_CH[channelId].RXDESC_RING_LENGTH.B.RDRL = pRxChannelConfig->numOfRxBuffers - 1U;
    ret = Eth_Register_ReadBack_Check(ret, (uint32)pRxChannelConfig->numOfRxBuffers - 1U, pEthModule->DMA_CH[channelId].RXDESC_RING_LENGTH.B.RDRL);

    /* Initialize receive descriptor list address with the base address of the descriptor */
    /* #Violation: eth_hal_c_REF_5 */
    pEthModule->DMA_CH[channelId].RXDESC_LIST_ADDRESS.U = (uint32)&(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[0]);
    /* #Violation: eth_hal_c_REF_5 */
    ret = Eth_Register_ReadBack_Check(ret, (uint32)&(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[0]), 
        pEthModule->DMA_CH[channelId].RXDESC_LIST_ADDRESS.U);

    /* Program receive tail pointer registers indicating to the DMA about the available descriptors */
    /* #Violation: eth_hal_c_REF_5 */
    pEthModule->DMA_CH[channelId].RXDESC_TAIL_POINTER.U = (uint32)&(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[pRxChannelConfig->numOfRxBuffers]);
    /* #Violation: eth_hal_c_REF_5 */
    ret = Eth_Register_ReadBack_Check(ret, (uint32)&(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[pRxChannelConfig->numOfRxBuffers]), 
        pEthModule->DMA_CH[channelId].RXDESC_TAIL_POINTER.U);

    /* Set the buffer size */
    rxBufSizeHi = ((uint32)((uint32)pRxChannelConfig->rxBufferAlignSize >> 3U) & 0xFFFU);
    pEthModule->DMA_CH[channelId].RX_CONTROL.B.RBSZ_13_Y = rxBufSizeHi;
    ret = Eth_Register_ReadBack_Check(ret, rxBufSizeHi, pEthModule->DMA_CH[channelId].RX_CONTROL.B.RBSZ_13_Y);

    /* Get current descriptor address */
    pEthNode->rxChannelInfoPtr[channelId].pRxDescriptor = (Eth_RxDescr *)&(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[0]);
    pEthNode->rxChannelInfoPtr[channelId].descIndex = 0;
    pEthNode->rxChannelInfoPtr[channelId].rxCount = 0;

    return ret;
}

static boolean Eth_Hal_ConfigureDma(const Eth_NodeHandle *const pEthNode, const Eth_Config *const pEthConfig)
{
    /* #Violation: eth_hal_c_REF_4 */
    ETH_DMA_SYSBUS_MODE regDmaSysbusMode;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_DMA_CH_INTERRUPT_ENABLE regDmaChInterruptEnable;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_DMA_CH_TX_CONTROL regDmaChTxControl;
    ETH_MODULE *pEthModule;
    uint8 channelIndex;
    uint8 dmaChId;
    const Eth_DmaConfig *pDmaConfig;
    boolean ret;

    ret = TRUE;
    pDmaConfig = &(pEthConfig->dma);
    pEthModule = pEthNode->pEthModule;

    /* Program the following fields to initialize the DMA_SysBus_Mode register:
         a. AAL: Address-Aligned Beats according to the configuration
         b. FB:  Fixed burst Length disable */
    regDmaSysbusMode.U = pEthModule->DMA_SYSBUS_MODE.U;
    regDmaSysbusMode.B.AAL = pDmaConfig->addrAlignedBeatsEnabled;
    regDmaSysbusMode.B.FB = ETH_BIT_ENABLE;
    pEthModule->DMA_SYSBUS_MODE.U = regDmaSysbusMode.U;
    ret = Eth_Register_ReadBack_Check(ret, regDmaSysbusMode.U, pEthModule->DMA_SYSBUS_MODE.U);

    /* Set DMA Interrupt Mode */
    pEthModule->DMA_MODE.B.INTM = (uint32)pDmaConfig->interruptMode;
    ret = Eth_Register_ReadBack_Check(ret, (uint32)pDmaConfig->interruptMode, pEthModule->DMA_MODE.B.INTM);
    /* Set Transmit Arbitration Algorithm */
    pEthModule->DMA_MODE.B.TAA = pEthConfig->ethDmaTxArbAlg;
    ret = Eth_Register_ReadBack_Check(ret, pEthConfig->ethDmaTxArbAlg, pEthModule->DMA_MODE.B.TAA);

    /* Tx channel configuration */
    for(channelIndex = 0; channelIndex < pEthConfig->ethNumTxChnls; channelIndex++)
    {
        if(TRUE == pDmaConfig->txChannel[channelIndex].txChannelEnabled)
        {
            dmaChId = pDmaConfig->txChannel[channelIndex].txChIdx;
            /* Program the settings of the maximum burst-length and weights for TX Channels(s) */
            regDmaChTxControl.U = pEthModule->DMA_CH[dmaChId].TX_CONTROL.U;
            regDmaChTxControl.B.OSF = ETH_BIT_ENABLE;
            regDmaChTxControl.B.TCW = pDmaConfig->txChannel[channelIndex].txDmaChnlWght;
            regDmaChTxControl.B.TXPBL =
                (uint32)pDmaConfig->txChannel[channelIndex].maxBurstLength;
            pEthModule->DMA_CH[dmaChId].TX_CONTROL.U = regDmaChTxControl.U;
            ret = Eth_Register_ReadBack_Check(ret, regDmaChTxControl.U, pEthModule->DMA_CH[dmaChId].TX_CONTROL.U);
                
            /* Configure descriptor for TX Channels(s) */
            /* #Violation: eth_hal_c_REF_6 */
            ret &= Eth_Hal_InitTransmitDescriptors(pEthNode, &pDmaConfig->txChannel[channelIndex], (Eth_DmaChannel)dmaChId);
            /* Set DMA interrupt */
            regDmaChInterruptEnable.U = pEthModule->DMA_CH[dmaChId].INTERRUPT_ENABLE.U;
            regDmaChInterruptEnable.U |= pDmaConfig->txChannel[channelIndex].txDmaChInterruptEnable.U;
            pEthModule->DMA_CH[channelIndex].INTERRUPT_ENABLE.U = regDmaChInterruptEnable.U;
            ret = Eth_Register_ReadBack_Check(ret, regDmaChInterruptEnable.U, pEthModule->DMA_CH[channelIndex].INTERRUPT_ENABLE.U);
        }
    }
    /* Rx channel configuration */
    for(channelIndex = 0; channelIndex < pEthConfig->ethNumRxChnls; channelIndex++)
    {
        if(TRUE == pDmaConfig->rxChannel[channelIndex].rxChannelEnabled)
        {
            /* Configure descriptor for RX Channels(s) */
            /* #Violation: eth_hal_c_REF_6 */
            ret &= Eth_Hal_InitReceiveDescriptors(pEthNode, &pDmaConfig->rxChannel[channelIndex], (Eth_DmaChannel)channelIndex);
            /* Program the settings of the maximum burst-length */
            pEthModule->DMA_CH[channelIndex].RX_CONTROL.B.RXPBL =
                (uint32)pDmaConfig->rxChannel[channelIndex].maxBurstLength;
            ret = Eth_Register_ReadBack_Check(ret, (uint32)pDmaConfig->rxChannel[channelIndex].maxBurstLength, 
                pEthModule->DMA_CH[channelIndex].RX_CONTROL.B.RXPBL);
            /* Set DMA interrupt */
            regDmaChInterruptEnable.U = pEthModule->DMA_CH[channelIndex].INTERRUPT_ENABLE.U;
            regDmaChInterruptEnable.U |= pDmaConfig->rxChannel[channelIndex].rxDmaChInterruptEnable.U;
            pEthModule->DMA_CH[channelIndex].INTERRUPT_ENABLE.U = regDmaChInterruptEnable.U;
            ret = Eth_Register_ReadBack_Check(ret, regDmaChInterruptEnable.U, pEthModule->DMA_CH[channelIndex].INTERRUPT_ENABLE.U);
        }
    }

    return ret;
}

static void Eth_Hal_ClearMtlAllInterruptFlags(ETH_MODULE *const pEthModule, Eth_MtlQueue queueId)
{
    uint32 regValue;

    /* clear MTL interrupt flag */
    regValue = (uint32)ETH_MTL_TXQUEUEUNDERFLOW_FLAG | (uint32)ETH_MTL_AVERAGEBITSPERSLOT_FLAG |
               (uint32)ETH_MTL_RXQUEUEOVERFLOW_FLAG;
    switch((uint32)queueId)
    {
        case(uint32)ETH_MTL_QUEUE0:
            pEthModule->MTL_Q0.INTERRUPT_CONTROL_STATUS.U |= regValue;
            break;
        case(uint32)ETH_MTL_QUEUE1:
            pEthModule->MTL_Q1.INTERRUPT_CONTROL_STATUS.U |= regValue;
            break;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        case(uint32)ETH_MTL_QUEUE2:
            pEthModule->MTL_Q2.INTERRUPT_CONTROL_STATUS.U |= regValue;
            break;
        case(uint32)ETH_MTL_QUEUE3:
            pEthModule->MTL_Q3.INTERRUPT_CONTROL_STATUS.U |= regValue;
            break;
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
        default:
            /* #Violation: eth_hal_c_REF_8 */
            /*do nothing*/
            break;
    }
}

static boolean Eth_Hal_EnableMtlInterrupt(ETH_MODULE *const pEthModule, Eth_MtlQueue queueId, Eth_MtlInterruptFlagOrEnable flag)
{
    boolean ret;
    uint32 enableStsVal;

    ret = TRUE;
    switch((uint32)queueId)
    {
        case(uint32)ETH_MTL_QUEUE0:
            enableStsVal = pEthModule->MTL_Q0.INTERRUPT_CONTROL_STATUS.U;
            enableStsVal |= (uint32)flag;
            pEthModule->MTL_Q0.INTERRUPT_CONTROL_STATUS.U = enableStsVal;
            ret = Eth_Register_ReadBack_Check(ret, enableStsVal, pEthModule->MTL_Q0.INTERRUPT_CONTROL_STATUS.U);
            break;
        case(uint32)ETH_MTL_QUEUE1:
            enableStsVal = pEthModule->MTL_Q1.INTERRUPT_CONTROL_STATUS.U;
            enableStsVal |= (uint32)flag;
            pEthModule->MTL_Q1.INTERRUPT_CONTROL_STATUS.U = enableStsVal;
            ret = Eth_Register_ReadBack_Check(ret, enableStsVal, pEthModule->MTL_Q1.INTERRUPT_CONTROL_STATUS.U);
            break;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        case(uint32)ETH_MTL_QUEUE2:
            enableStsVal = pEthModule->MTL_Q2.INTERRUPT_CONTROL_STATUS.U;
            enableStsVal |= (uint32)flag;
            pEthModule->MTL_Q2.INTERRUPT_CONTROL_STATUS.U = enableStsVal;
            ret = Eth_Register_ReadBack_Check(ret, enableStsVal, pEthModule->MTL_Q2.INTERRUPT_CONTROL_STATUS.U);
            break;
        case(uint32)ETH_MTL_QUEUE3:
            enableStsVal = pEthModule->MTL_Q3.INTERRUPT_CONTROL_STATUS.U;
            enableStsVal |= (uint32)flag;
            pEthModule->MTL_Q3.INTERRUPT_CONTROL_STATUS.U = enableStsVal;
            ret = Eth_Register_ReadBack_Check(ret, enableStsVal, pEthModule->MTL_Q3.INTERRUPT_CONTROL_STATUS.U);
            break;
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
        default:
            /* #Violation: eth_hal_c_REF_8 */
            /*do nothing*/
            break;
    }

    return ret;
}

static boolean Eth_Hal_SetMtlRxqOperationMode(volatile uint32 *const regAddrMtlRxqOperationMode, Eth_MtlQueue queueId,
                                              const Eth_MtlConfig *const pMtlConfig)
{
    boolean ret;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MTL_RXQ_OPERATION_MODE regMtlRxqOperationMode;

    ret = TRUE;
    regMtlRxqOperationMode.U = *regAddrMtlRxqOperationMode;

    /* Receive Store and Forward (RSF) or RTC in case of Threshold mode */
    regMtlRxqOperationMode.B.RSF = pMtlConfig->rxQueue[queueId].storeAndForward;
    /* The received packet is transferred to DMA when the packet size within the MTL Rx queue is larger than the
     * threshold.*/
    /* When Receive Store and Forward (RSF) is enable,This field is ignored */
    regMtlRxqOperationMode.B.RTC = (uint32)pMtlConfig->rxQueue[queueId].rxQueueThreshold;
    /* The flow control signal operation, based on the fill-level of Rx queue. */
    regMtlRxqOperationMode.B.EHFC = pMtlConfig->rxQueue[queueId].rxFlowCtlEnabled;
    /* The flow control signal to the MAC is asserted when the fill level of the Rx queue crosses the threshold
     * configured in RFA field */
    regMtlRxqOperationMode.B.RFA = (uint32)pMtlConfig->rxQueue[queueId].rxFlowControlThresholdsActive;
    /* This flow control signal is de-asserted when the fill-level of the queue is lower than the threshold configured
     * in the RFD field. */
    regMtlRxqOperationMode.B.RFD = (uint32)pMtlConfig->rxQueue[queueId].rxFlowControlThresholdsDeactive;
    /* Receive Queue Size  */
    regMtlRxqOperationMode.B.RQS = (uint32)pMtlConfig->rxQueue[queueId].rxQueueSize;
    /* Error Packet forwarding enable */
    regMtlRxqOperationMode.B.FEP = pMtlConfig->rxQueue[queueId].forwardErrorPacket;
    /* Under-sized good Packet forwarding enable */
    regMtlRxqOperationMode.B.FUP = pMtlConfig->rxQueue[queueId].forwardUndersizedGoodPacket;

    *regAddrMtlRxqOperationMode = regMtlRxqOperationMode.U;
    ret = Eth_Register_ReadBack_Check(ret, regMtlRxqOperationMode.U, *regAddrMtlRxqOperationMode);

    return ret;
}

static boolean Eth_Hal_SetMtlRxQueue(ETH_MODULE *const pEthModule, const Eth_MtlRxQueueConfig *const pMtlRxQueueConfig)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MAC_RXQ_CTRL1 regMacRxqCtrl1;

    regMacRxqCtrl1.U = 0U;
    /* Type field based Rx queue disable */
    regMacRxqCtrl1.B.TBRQE = ETH_BIT_DISABLE;
    /* Overriding MCBCQ priority select */
    if(TRUE == pMtlRxQueueConfig->overridingMcbcqPriEnable)
    {
        regMacRxqCtrl1.B.OMCBCQ = ETH_BIT_ENABLE;
    }
    /* Set multicast and broadcast queue */
    regMacRxqCtrl1.B.MCBCQ = (uint32)pMtlRxQueueConfig->bdAndMultiQueueConfig.bdAndMultiQueue;
    if(TRUE == pMtlRxQueueConfig->bdAndMultiQueueConfig.bdAndMultiQueueEnable)
    {
        regMacRxqCtrl1.B.MCBCQEN = ETH_BIT_ENABLE;
    }
    /* Set unicast AVTP queue */
    regMacRxqCtrl1.B.AVCPQ = (uint32)pMtlRxQueueConfig->unicastAVTPQueueConfig.unicastAVTPQueue;
    if(TRUE == pMtlRxQueueConfig->unicastAVTPQueueConfig.taggedAVQueueEnable)
    {
        regMacRxqCtrl1.B.TACPQE = ETH_BIT_ENABLE;
    }
    /* Set unicast PTP queue */
    regMacRxqCtrl1.B.PTPQ = (uint32)pMtlRxQueueConfig->unicastPTPQueue;
    /* Set TPQC to 0x01,PTP tagged packet are routed to RX queue specified by PTPQ field */
    regMacRxqCtrl1.B.TPQC = 0x01U;
    /* Set remaining unicast queue */
    regMacRxqCtrl1.B.UPQ = (uint32)pMtlRxQueueConfig->remainingUnicastQueue;
    /* Set preemptable packet queue */
    regMacRxqCtrl1.B.FPRQ = (uint32)pMtlRxQueueConfig->preemptableQueue;
    pEthModule->MAC_RXQ_CTRL1.U = regMacRxqCtrl1.U;
    ret = Eth_Register_ReadBack_Check(ret, regMacRxqCtrl1.U, pEthModule->MAC_RXQ_CTRL1.U);

    return ret;
}

static boolean Eth_Hal_ConfigureMtlTxQ(ETH_MODULE *const pEthModule, const Eth_Config *const pEthConfig)
{
    uint8                       txQueueIndex;
    const Eth_MtlConfig        *pMtlConfig;
    volatile uint32            *pRegAddr;
    uint32                       dmaId;
    ETH_MTL_TXQ_OPERATION_MODE *pTxQRegster;
    boolean ret;
    pMtlConfig = &(pEthConfig->mtl);
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MTL_TXQ0_OPERATION_MODE regMtlTxQ0OperMod;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MTL_TXQ_OPERATION_MODE regMtlTxQOperMod;

    ret = TRUE;
    /* TX Queue(s) configuration */
    /* Program the transmit scheduling */
    pEthModule->MTL_OPERATION_MODE.B.SCHALG = (uint32)pEthConfig->ethMtlTxSchAlg;
    ret = Eth_Register_ReadBack_Check(ret, (uint32)pEthConfig->ethMtlTxSchAlg, pEthModule->MTL_OPERATION_MODE.B.SCHALG);

    for (txQueueIndex = 0U; txQueueIndex < pEthConfig->ethNumTxChnls; txQueueIndex++)
    {
        if (TRUE == pMtlConfig->txQueue[txQueueIndex].txQueueEnabled)
        {
            dmaId = (uint32)pMtlConfig->txQueue[txQueueIndex].txChId;
            if (0U == dmaId)
            {
                regMtlTxQ0OperMod.U = pEthModule->MTL_TXQ0.OPERATION_MODE.U;
                regMtlTxQ0OperMod.B.TQS = (uint32)pMtlConfig->txQueue[txQueueIndex].txQueueSize; /* Transmit Queue Size */
                regMtlTxQ0OperMod.B.TSF = pMtlConfig->txQueue[txQueueIndex].storeAndForward;
                regMtlTxQ0OperMod.B.TTC = (uint32)pMtlConfig->txQueue[txQueueIndex].txQueueThreshold;
                regMtlTxQ0OperMod.B.TXQEN = (uint32)pMtlConfig->txQueue[txQueueIndex].txQueueMode;
                pEthModule->MTL_TXQ0.OPERATION_MODE.U = regMtlTxQ0OperMod.U;
                ret = Eth_Register_ReadBack_Check(ret, regMtlTxQ0OperMod.U, pEthModule->MTL_TXQ0.OPERATION_MODE.U);

                pEthModule->MTL_TXQ0.QUANTUM_WEIGHT.U = pMtlConfig->txQueue[txQueueIndex].idleSlopeCredit;
                ret = Eth_Register_ReadBack_Check(ret, pMtlConfig->txQueue[txQueueIndex].idleSlopeCredit,
                    pEthModule->MTL_TXQ0.QUANTUM_WEIGHT.U);
            }
            else
            {
                /* Set MTL_Txq_Operation_MODE: MTL_TXQ1~MTL_TXQ3 */
                /* #Violation: eth_hal_c_REF_5 */
                /* #Violation: eth_hal_c_REF_9 */
                /* #Violation: eth_hal_c_REF_12 */
                /* #Violation: eth_hal_c_REF_14 */
                pTxQRegster = (ETH_MTL_TXQ_OPERATION_MODE *)((uint32)&pEthModule->MTL_TXQ1.OPERATION_MODE.U + ((dmaId - 1U) * 0x40U));
                regMtlTxQOperMod.U = pTxQRegster->U;
                regMtlTxQOperMod.B.TQS = (uint32)pMtlConfig->txQueue[txQueueIndex].txQueueSize;
                regMtlTxQOperMod.B.TSF = pMtlConfig->txQueue[txQueueIndex].storeAndForward;
                regMtlTxQOperMod.B.TTC = (uint32)pMtlConfig->txQueue[txQueueIndex].txQueueThreshold;
                regMtlTxQOperMod.B.TXQEN = (uint32)pMtlConfig->txQueue[txQueueIndex].txQueueMode;
                pTxQRegster->U = regMtlTxQOperMod.U;
                ret = Eth_Register_ReadBack_Check(ret, regMtlTxQOperMod.U, pTxQRegster->U);

                /* #Violation: eth_hal_c_REF_5 */
                /* #Violation: eth_hal_c_REF_9 */
                /* #Violation: eth_hal_c_REF_12 */
                /* #Violation: eth_hal_c_REF_14 */
                pRegAddr = (volatile uint32 *)((uint32 )&pEthModule->MTL_TXQ1.QUANTUM_WEIGHT.U + ((dmaId - 1U) * 0x40U));

                *pRegAddr = pMtlConfig->txQueue[txQueueIndex].idleSlopeCredit;
                ret = Eth_Register_ReadBack_Check(ret, pMtlConfig->txQueue[txQueueIndex].idleSlopeCredit, *pRegAddr);

                /* Enable MTL txQueueUnderflow interrupt */
                if(TRUE == pMtlConfig->txQueue[(txQueueIndex)].txQueueUnderflowInterruptEnabled)
                {
                    /* #Violation: eth_hal_c_REF_6 */
                    ret &= Eth_Hal_EnableMtlInterrupt(pEthModule, (Eth_MtlQueue)(txQueueIndex),ETH_MTL_TXQUEUEUNDERFLOW_EN);
                }
                if (ETH_TXQUEUE_AV_ENABLE == pMtlConfig->txQueue[(txQueueIndex)].txQueueMode)
                { /* valaible for Queue 1~3 */
                    /* #Violation: eth_hal_c_REF_5 */
                    /* #Violation: eth_hal_c_REF_9 */
                    /* #Violation: eth_hal_c_REF_12 */
                    /* #Violation: eth_hal_c_REF_14 */
                    pRegAddr = (volatile uint32 *)((uint32)&pEthModule->MTL_TXQ1.ETS_CONTROL.U + ((dmaId - 1U) * 0x40U));
                    /*Enable CBS algorithm and credit not be reset to 0 when no packet to Tx*/
                    *pRegAddr = 0x0000000CU;
                    ret = Eth_Register_ReadBack_Check(ret, 0x0000000CU, *pRegAddr);
                    /* #Violation: eth_hal_c_REF_5 */
                    /* #Violation: eth_hal_c_REF_9 */
                    /* #Violation: eth_hal_c_REF_12 */
                    /* #Violation: eth_hal_c_REF_14 */
                    pRegAddr = (volatile uint32 *)((uint32)&pEthModule->MTL_TXQ1.SENDSLOPECREDIT.U + ((dmaId - 1U) * 0x40U));
                    *pRegAddr = pMtlConfig->txQueue[txQueueIndex].sendSlopeCredit;
                    ret = Eth_Register_ReadBack_Check(ret, pMtlConfig->txQueue[txQueueIndex].sendSlopeCredit, *pRegAddr);
                    /* #Violation: eth_hal_c_REF_5 */
                    /* #Violation: eth_hal_c_REF_9 */
                    /* #Violation: eth_hal_c_REF_12 */
                    /* #Violation: eth_hal_c_REF_14 */
                    pRegAddr = (volatile uint32 *)((uint32)&pEthModule->MTL_TXQ1.HICREDIT.U + ((dmaId - 1U) * 0x40U));
                    *pRegAddr = pMtlConfig->txQueue[txQueueIndex].hiCredit;
                    ret = Eth_Register_ReadBack_Check(ret, pMtlConfig->txQueue[txQueueIndex].hiCredit, *pRegAddr);
                    /* #Violation: eth_hal_c_REF_5 */
                    /* #Violation: eth_hal_c_REF_9 */
                    /* #Violation: eth_hal_c_REF_12 */
                    /* #Violation: eth_hal_c_REF_14 */
                    pRegAddr = (volatile uint32 *)((uint32)&pEthModule->MTL_TXQ1.LOCREDIT.U + ((dmaId - 1U) * 0x40U));
                    *pRegAddr = pMtlConfig->txQueue[txQueueIndex].loCredit;
                    ret = Eth_Register_ReadBack_Check(ret, pMtlConfig->txQueue[txQueueIndex].loCredit, *pRegAddr);
                }
            }
        }
    }

    return ret;
}

static boolean Eth_Hal_ConfigureMtlRxQ(ETH_MODULE *const pEthModule, const Eth_Config *const pEthConfig)
{
    uint32                      rxQueueIndex;
    uint32                      rxQueueIndexOffset;
    const Eth_MtlConfig        *pMtlConfig;
    boolean ret;
    uint32 tempVal;
    pMtlConfig = &(pEthConfig->mtl);

    ret = TRUE;
    /* RX Queue(s) configuration */
    /* Receive Arbitration Algorithm */
    pEthModule->MTL_OPERATION_MODE.B.RAA = (uint32)ETH_RX_ARBITRATION_ALG_SP;
    ret = Eth_Register_ReadBack_Check(ret, (uint32)ETH_RX_ARBITRATION_ALG_SP, pEthModule->MTL_OPERATION_MODE.B.RAA);

    /*Program MAC to the Receive Queue mapping for many channels */
    ret &= Eth_Hal_SetMtlRxQueue(pEthModule, &pMtlConfig->rxQueueConfig);

    for (rxQueueIndex = 0; rxQueueIndex < (uint32)pEthConfig->ethNumRxChnls; rxQueueIndex++)
    {
        if (TRUE == pMtlConfig->rxQueue[rxQueueIndex].rxQueueEnabled)
        {
            /* Program the Receive Queue to DMA mapping,only support static mapping now */
            rxQueueIndexOffset = (uint32)(rxQueueIndex * 8U);
            tempVal = pEthModule->MTL_RXQ_DMA_MAP0.U;
            tempVal |= (rxQueueIndex << rxQueueIndexOffset);
            pEthModule->MTL_RXQ_DMA_MAP0.U = tempVal;
            ret = Eth_Register_ReadBack_Check(ret, tempVal, pEthModule->MTL_RXQ_DMA_MAP0.U);
            /* Set MTL_Rxq_Operation_MODE:MTL_RXQ0~MTL_RXQ3 */
            ret &= Eth_Hal_SetMtlRxqOperationMode(
                /* #Violation: eth_hal_c_REF_5 */
                /* #Violation: eth_hal_c_REF_9 */
                /* #Violation: eth_hal_c_REF_12 */
                /* #Violation: eth_hal_c_REF_14 */
                ((volatile uint32 *)((uint32)&pEthModule->MTL_RXQ0.OPERATION_MODE.U + (rxQueueIndex * 0x40U))),
                /* #Violation: eth_hal_c_REF_6 */
                (Eth_MtlQueue)rxQueueIndex,
                pMtlConfig);
            /* Receive Queue Enable */
            tempVal = pEthModule->MAC_RXQ_CTRL0.U;
            tempVal |= (uint32)((uint32)ETH_RXQUEUE_ENABLE << (rxQueueIndex * ETH_QUEUE_EN_DCB_GEN));
            pEthModule->MAC_RXQ_CTRL0.U = tempVal;
            ret = Eth_Register_ReadBack_Check(ret, tempVal, pEthModule->MAC_RXQ_CTRL0.U);
            /* Set VLAN priority */
            tempVal = pEthModule->MAC_RXQ_CTRL2.U;
            tempVal |= (uint32)((uint32)pMtlConfig->rxQueue[rxQueueIndex].taggedUserpriority << (rxQueueIndex * 8U));
            pEthModule->MAC_RXQ_CTRL2.U = tempVal;
            ret = Eth_Register_ReadBack_Check(ret, tempVal, pEthModule->MAC_RXQ_CTRL2.U);
            /* Enable MTL rxQueueOverflow interrupt */
            if(TRUE == pMtlConfig->rxQueue[rxQueueIndex].rxQueueOverflowInterruptEnabled)
            {
                /* #Violation: eth_hal_c_REF_6 */
                ret &= Eth_Hal_EnableMtlInterrupt(pEthModule, (Eth_MtlQueue)rxQueueIndex, ETH_MTL_RXQUEUEOVERFLOW_EN);
            }
        }
    }

    return ret;
}

static boolean Eth_Hal_ConfigureMtl(ETH_MODULE *const pEthModule, const Eth_Config *const pEthConfig)
{
    uint8                       queueIndex;
    const Eth_MtlConfig        *pMtlConfig;
    boolean ret;
    pMtlConfig = &(pEthConfig->mtl);

    ret = TRUE;
    /* clear all flags for MTL interrupt */
    for (queueIndex = 0; queueIndex < pEthConfig->ethNumTxChnls; queueIndex++)
    {
        /* #Violation: eth_hal_c_REF_6 */
        Eth_Hal_ClearMtlAllInterruptFlags(pEthModule, (Eth_MtlQueue)queueIndex);
    }

    /* Enable the ECC control and interrupt */
    if (TRUE == pMtlConfig->rxFifoEccEnable)
    {
        /* MTL Rx FIFO ECC Enable */
        pEthModule->MTL_ECC_CTL.B.MRXEE = ETH_BIT_ENABLE;
        ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MTL_ECC_CTL.B.MRXEE);
        /* MTL ECC Rx memory Correctable Error Interrupt Enable */
        pEthModule->MTL_ECC_INTERRUPT_ENABLE.B.RXCEIE = ETH_BIT_ENABLE;
        ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MTL_ECC_INTERRUPT_ENABLE.B.RXCEIE);
    }
    if (TRUE == pMtlConfig->txFifoEccEnable)
    {
        /* MTL Tx FIFO ECC Enable */
        pEthModule->MTL_ECC_CTL.B.MTXEE = ETH_BIT_ENABLE;
        ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MTL_ECC_CTL.B.MTXEE);
        /* MTL ECC Tx memory Correctable Error Interrupt Enable */
        pEthModule->MTL_ECC_INTERRUPT_ENABLE.B.TXCEIE = ETH_BIT_ENABLE;
        ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MTL_ECC_INTERRUPT_ENABLE.B.TXCEIE);
    }

    /* TX Queue(s) configuration */
    ret &= Eth_Hal_ConfigureMtlTxQ(pEthModule, pEthConfig);

    /* RX Queue(s) configuration */
    ret &= Eth_Hal_ConfigureMtlRxQ(pEthModule, pEthConfig);

    return ret;
}

static boolean Eth_Hal_ConfigureMac(const Eth_NodeHandle *const pEthNode, const Eth_MacConfig *const pMacConfig)
{
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MAC_PACKET_FILTER regMacPacketFilter;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MAC_CONFIGURATION regMacConfiguration;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MAC_Q0_TX_FLOW_CTRL regMacQ0TxFlowCtrl;
    ETH_MODULE *pEthModule;
    boolean ret;

    ret = TRUE;
    pEthModule = pEthNode->pEthModule;
    /* set MAC Address */
    ret &= Eth_Hal_SetMacAddress(pEthNode, pMacConfig->macAddress);
    ret &= Eth_Std_ClearDaFilter(pEthModule);

    /* packet Filter Configuration */
    regMacPacketFilter.U = pEthModule->MAC_PACKET_FILTER.U;
    regMacPacketFilter.B.RA =
        (uint32)((TRUE == pMacConfig->allPacketPassing) ? ETH_BIT_ENABLE : ETH_BIT_DISABLE);
    regMacPacketFilter.B.DAIF = (uint32)((TRUE == pMacConfig->daAddrInversePassing) ? ETH_BIT_ENABLE : ETH_BIT_DISABLE);
    regMacPacketFilter.B.VTFE = (uint32)((TRUE == pMacConfig->vlanTagPassing) ? ETH_BIT_ENABLE : ETH_BIT_DISABLE);
    regMacPacketFilter.B.DBF = (uint32)((TRUE == pMacConfig->enableBroadcast) ? ETH_BIT_DISABLE : ETH_BIT_ENABLE);
    regMacPacketFilter.B.PR =
        (uint32)((TRUE == pMacConfig->enablePromiscuous) ? ETH_BIT_ENABLE : ETH_BIT_DISABLE); /* Close promiscuous mode */
    regMacPacketFilter.B.PM =
        (uint32)((TRUE == pMacConfig->enableMulticast) ? ETH_BIT_ENABLE
                                                     : ETH_BIT_DISABLE); /* Can't receive the multi-caste */
    pEthModule->MAC_PACKET_FILTER.U = regMacPacketFilter.U;
    ret = Eth_Register_ReadBack_Check(ret, regMacPacketFilter.U, pEthModule->MAC_PACKET_FILTER.U);

    /* MAC configuration */
    regMacConfiguration.U = pEthModule->MAC_CONFIGURATION.U;
    regMacConfiguration.B.DM = (uint32)pMacConfig->duplexMode;
    regMacConfiguration.B.PRELEN = (uint32)ETH_PREAMBLELENGTH_7BYTES;
    regMacConfiguration.B.IPC = pMacConfig->checksumOffload;
    regMacConfiguration.B.ACS =
        (uint32)((TRUE == pMacConfig->automaticPadOrCRCStripping) ? ETH_BIT_ENABLE : ETH_BIT_DISABLE);
    regMacConfiguration.B.CST = (uint32)((TRUE == pMacConfig->crcStrippingForEther) ? ETH_BIT_ENABLE : ETH_BIT_DISABLE);
    regMacConfiguration.B.LM = (uint32)pMacConfig->loopbackMode; /* Set Loop-back Mode */
    /* Set ethernet line speed*/
    switch((uint32)pMacConfig->lineSpeed)
    {
        case(uint32)ETH_LINESPEED_10M:
            regMacConfiguration.B.PS = ETH_BIT_ENABLE;
            regMacConfiguration.B.FES = ETH_BIT_DISABLE;
            break;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        case(uint32)ETH_LINESPEED_100M:
            regMacConfiguration.B.PS = ETH_BIT_ENABLE;
            regMacConfiguration.B.FES = ETH_BIT_ENABLE;
            break;
        case(uint32)ETH_LINESPEED_1000M:
            regMacConfiguration.B.PS = ETH_BIT_DISABLE;
            regMacConfiguration.B.FES = ETH_BIT_DISABLE;
            break;
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
        default:
            /* #Violation: eth_hal_c_REF_8 */
            /*do nothing*/
            break;
    }
    pEthModule->MAC_CONFIGURATION.U = regMacConfiguration.U;
    ret = Eth_Register_ReadBack_Check(ret, regMacConfiguration.U, pEthModule->MAC_CONFIGURATION.U);
    ret &= Eth_Std_SetMacMaxPacketSize(pEthModule, pMacConfig->maxPacketSize);

    /* Set CRC checking for received packets,pMacConfig->DisableCrcChecking = TRUE,then CRC checking is disable */
    pEthModule->MAC_EXT_CONFIGURATION.B.DCRCC =
        (uint32)((TRUE == pMacConfig->disableCrcChecking) ? ETH_BIT_ENABLE : ETH_BIT_DISABLE);
    ret = Eth_Register_ReadBack_Check(ret, (uint32)((TRUE == pMacConfig->disableCrcChecking) ? ETH_BIT_ENABLE : ETH_BIT_DISABLE),
        pEthModule->MAC_EXT_CONFIGURATION.B.DCRCC);
    /* Flow control for transmitting */
    /* Normal operation with automatic zeor-quanta pause packet generation is enabled */
    regMacQ0TxFlowCtrl.U = pEthModule->MAC_Q0_TX_FLOW_CTRL.U;
    regMacQ0TxFlowCtrl.B.DZPQ = ETH_BIT_DISABLE;
    regMacQ0TxFlowCtrl.B.PLT = 1U; /* Pause low threshold */
    regMacQ0TxFlowCtrl.B.PT = 256U; /* Pause time */
    regMacQ0TxFlowCtrl.B.TFE = ETH_BIT_ENABLE;/* Transmit flow control is enabled */
    pEthModule->MAC_Q0_TX_FLOW_CTRL.U = regMacQ0TxFlowCtrl.U;
    ret = Eth_Register_ReadBack_Check(ret, regMacQ0TxFlowCtrl.U, pEthModule->MAC_Q0_TX_FLOW_CTRL.U);
    /* Flow control for receiving, receive flow control only in the full-duplex mode */
    pEthModule->MAC_RX_FLOW_CTRL.B.RFE = ETH_BIT_ENABLE;/* Receive flow control is enabled */
    ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MAC_RX_FLOW_CTRL.B.RFE);

    return ret;
}

static void Eth_Hal_GetIngressTimeStamp(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, Eth_RxInfo *const pRxInfo)
{
    volatile Eth_RxDescr *pCurDescr;
    uint32 currTimeSec;
    uint32 descriptorSec;
    uint16 currTimeSecHi;

    uint32 curDescIndex;
    curDescIndex = pEthNode->rxChannelInfoPtr[channelId].descIndex;
    pCurDescr = &(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[curDescIndex]);

    if(ETH_BIT_ENABLE == pCurDescr->RDES1.W.TSA)
    {

        /* Get the buffer index */
        if((pEthNode->rxChannelInfoPtr[channelId].numOfDescriptor-1U)==curDescIndex)
        {
            curDescIndex = 0U;
        }
        else
        {
            curDescIndex++; /* Pointer to the receive context descriptor */
        }
        pCurDescr = &(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[curDescIndex]);

        if(ETH_CONTEXT_DESCR_VALID == (pCurDescr->RDES3.U & ETH_CONTEXT_DESCR_MASK)) /*OWN = 0, CTXT = 1, DE = 0*/
        {
            currTimeSec = pEthNode->pEthModule->MAC_SYSTEM_TIME_SECONDS.U;
            currTimeSecHi = (uint16)(pEthNode->pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.U & 0xFFFFU);
            descriptorSec = (uint32)(pCurDescr->RDES1.U);

            if(descriptorSec <= currTimeSec)
            {
                pRxInfo->timeStamp.secondsHi = currTimeSecHi;
            }
            else
            {
                pRxInfo->timeStamp.secondsHi = (uint16)(currTimeSecHi - 1U);
            }
            pRxInfo->timeStamp.seconds = descriptorSec;
            pRxInfo->timeStamp.nanoseconds = (uint32)(pCurDescr->RDES0.U);
            pRxInfo->ingressTimeStampAvailable = TRUE;
        }
        else
        {
            pRxInfo->ingressTimeStampAvailable = FALSE;
        }


        /* Free the receive descriptor, enabling it for the further reception */
        Eth_Hal_ResetRxDescriptor(pCurDescr, pEthNode->rxDescrInfoPtr[channelId][curDescIndex].descrBufAddr);
        Eth_Hal_FreeRxDescriptor(pCurDescr);
        /* Shuffle to next descriptor */
        Eth_Hal_ShuffleRxDescriptor(pEthNode, channelId);
    }
    else
    {
        pRxInfo->timeStamp.secondsHi = 0U;
        pRxInfo->timeStamp.seconds = 0U;
        pRxInfo->timeStamp.nanoseconds = 0U;
        pRxInfo->ingressTimeStampAvailable = FALSE;
    }
}

static void Eth_Hal_GetEgressTimestamp(const ETH_MODULE *const pEthModule, volatile const Eth_TxDescr *const pCurrDescr,
                                       Eth_TxInfo *const pTxInfo)
{
    uint32 currTimeSec;
    uint32 descriptorSec;
    Eth_TimeStampType *pTimeStamp;
    uint16 currTimeSecHi;

    pTimeStamp = &pTxInfo->timeStamp;
    if(pCurrDescr->TDES3.W.TTSS != 0U)
    {
        currTimeSec = (uint32)(pEthModule->MAC_SYSTEM_TIME_SECONDS.U);
        currTimeSecHi = (uint16)(pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.U & 0xFFFFU);
        descriptorSec = (uint32)(pCurrDescr->TDES1.U);
        if(descriptorSec <= currTimeSec)
        {
            pTimeStamp->secondsHi = currTimeSecHi;
        }
        else
        {
            pTimeStamp->secondsHi = (uint16)(currTimeSecHi - 1U);
        }
        pTimeStamp->seconds = descriptorSec;
        pTimeStamp->nanoseconds = (uint32)(pCurrDescr->TDES0.U);
        pTxInfo->egressTimeStampAvailable = TRUE;
    }
    else
    {
        pTimeStamp->secondsHi = 0U;
        pTimeStamp->seconds = 0U;
        pTimeStamp->nanoseconds = 0U;
        pTxInfo->egressTimeStampAvailable = FALSE;
    }
}

static void Eth_Hal_ShuffleTxDescriptor(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId)
{
    uint32 numDescr;
    uint32 curDescIndex;

    curDescIndex = pEthNode->txChannelInfoPtr[channelId].descIndex;
    numDescr = pEthNode->txChannelInfoPtr[channelId].numOfDescriptor;
    if ((numDescr-1U) == curDescIndex)
    {
        /* wrap around the descriptors */
        curDescIndex = 0U;
    }
    else
    {
        /* point to the next descriptor */
        curDescIndex++;
    }
    pEthNode->txChannelInfoPtr[channelId].pTxDescriptor = &(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[curDescIndex]);
    pEthNode->txChannelInfoPtr[channelId].descIndex = curDescIndex;
}

static void Eth_Hal_ShuffleRxDescriptor(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId)
{
    uint32 numDescr;
    uint32 curDescIndex;

    curDescIndex = pEthNode->rxChannelInfoPtr[channelId].descIndex;
    numDescr = pEthNode->rxChannelInfoPtr[channelId].numOfDescriptor;
    if((numDescr-1U) == curDescIndex)
    {
        /* wrap around the descriptors */
        curDescIndex = 0U;
    }
    else
    {
        /* point to the next descriptor */
        curDescIndex++;
    }
    pEthNode->rxChannelInfoPtr[channelId].descIndex = curDescIndex;
    pEthNode->rxChannelInfoPtr[channelId].pRxDescriptor = &(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[curDescIndex]);
    /* #Violation: eth_hal_c_REF_5 */
    pEthNode->pEthModule->DMA_CH[channelId].RXDESC_TAIL_POINTER.U = (uint32)&(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[numDescr]);
}

static void Eth_Hal_ResetRxDescriptor(volatile Eth_RxDescr *const pCurDescr, uint32 descrBufAddr)
{
    pCurDescr->RDES3.U = 0;
    pCurDescr->RDES3.R.BUF1V = ETH_BIT_ENABLE;  /* buffer 1 valid */
    pCurDescr->RDES3.R.BUF2V = ETH_BIT_DISABLE; /* buffer 2 not valid */
    pCurDescr->RDES3.R.IOC = ETH_BIT_ENABLE;    /* interrupt enabled */

    /* release the received descriptors */
    pCurDescr->RDES0.U = descrBufAddr;
    pCurDescr->RDES1.U = 0U; /* reserved */
    pCurDescr->RDES2.U = 0U; /* buffer2 not used */
}

static Eth_Status Eth_Hal_StartDevice(const Eth_NodeHandle *const pEthNode)
{
    Eth_Status ethSts;
    uint8 channelIndex;
    boolean ret;   
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MAC_CONFIGURATION regMacConfig;

    ret = TRUE; 
    ethSts = ETH_STATUS_OK;
    /* Start all configured TxDMA channels */
    for(channelIndex = 0U; channelIndex < pEthNode->numOfUsedTxCh; channelIndex++)
    {
        if(TRUE == pEthNode->txChannelInfoPtr[channelIndex].txChannelEnabled)
        {
            pEthNode->pEthModule->DMA_CH[channelIndex].TX_CONTROL.B.ST = ETH_BIT_ENABLE;
            ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthNode->pEthModule->DMA_CH[channelIndex].TX_CONTROL.B.ST);
        }
    }
    /* Start all configured RxDMA channels */
    /* #Violation: eth_hal_c_REF_1 */
    for(channelIndex = 0U; channelIndex < ETH_CTRL0_RXSCHEDULED_CFGD; channelIndex++)
    {
        if(TRUE == pEthNode->rxChannelInfoPtr[channelIndex].rxChannelEnabled)
        {
            pEthNode->pEthModule->DMA_CH[channelIndex].RX_CONTROL.B.SR = ETH_BIT_ENABLE;
            ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthNode->pEthModule->DMA_CH[channelIndex].RX_CONTROL.B.SR);
        }
    }
    /* Enable MAC Tx and Rx*/
    regMacConfig.U = pEthNode->pEthModule->MAC_CONFIGURATION.U;
    regMacConfig.B.TE = ETH_BIT_ENABLE;
    regMacConfig.B.RE = ETH_BIT_ENABLE;
    pEthNode->pEthModule->MAC_CONFIGURATION.U = regMacConfig.U;
    ret = Eth_Register_ReadBack_Check(ret, regMacConfig.U, pEthNode->pEthModule->MAC_CONFIGURATION.U);
    

    if(FALSE == ret)
    {
        ethSts = ETH_STATUS_ERROR;
    }
    return ethSts;
}

static Eth_Status Eth_Hal_CheckTxMTLEmpty(const Eth_NodeHandle *const pEthNode)
{
    uint64 startTime;
    uint64 curTime;
    uint32 queueEmpty;
    uint8 channelId;
    Eth_Status ethSts;
    const ETH_MODULE *pEthModule;

    pEthModule = pEthNode->pEthModule;
    ethSts = ETH_STATUS_OK;
    queueEmpty = 1U;
    for(channelId = 0U; ((channelId < pEthNode->numOfUsedTxCh) && (ETH_STATUS_OK == ethSts)); channelId++)
    {
        ethSts = ETH_STATUS_ERROR;
        /* Get the start time */
        startTime = Stm_Hal_GetValue();
        do
        {
            /* Check MTL queue is empty */
            /* Flush the corresponding MTL Tx Queue (Channels and queues are mapped 1:1) */
            switch(channelId)
            {
                case (uint8)ETH_MTL_QUEUE0:
                    queueEmpty =
                        pEthModule->MTL_TXQ0.MTL_TXQ_DEBUG.B.TXQSTS; /* When Tx queue is empty,then TXQSTS = 0*/
                    break;
                case (uint8)ETH_MTL_QUEUE1:
                    queueEmpty = pEthModule->MTL_TXQ1.MTL_TXQ_DEBUG.B.TXQSTS;
                    break;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
                case (uint8)ETH_MTL_QUEUE2:
                    queueEmpty = pEthModule->MTL_TXQ2.MTL_TXQ_DEBUG.B.TXQSTS;
                    break;
                case (uint8)ETH_MTL_QUEUE3:
                    queueEmpty = pEthModule->MTL_TXQ3.MTL_TXQ_DEBUG.B.TXQSTS;
                    break;
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
                default:
                    /* #Violation: eth_hal_c_REF_8 */
                    /*do nothing*/
                    break;
            }

            if(ETH_BIT_DISABLE == queueEmpty)
            {
                ethSts = ETH_STATUS_OK;
            }
            /* Get current time */
            curTime = Stm_Hal_GetValue();
        } while((ETH_STATUS_ERROR == ethSts) && (curTime < (startTime + (uint64)ETH_TIMERSET_TICKS1)));
    }

    return ethSts;
}

static Eth_Status Eth_Hal_StopDevice(const Eth_NodeHandle *const pEthNode)
{
    Eth_Status ethSts;
    uint8 channelId;
    ETH_MODULE *pEthModule;
    boolean ret;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MAC_CONFIGURATION regMacConfig;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_DMA_CH_RX_CONTROL regDmaChRxCtrl;

    ret = TRUE;
    pEthModule = pEthNode->pEthModule;
    /* Stop all configured TxDMA channels and flush the corresponding MTL queues */
    for(channelId = 0U; channelId < pEthNode->numOfUsedTxCh; channelId++)
    {
        /* Stop all the TxDMA channel (This will set flag DMA_CHi_Status[TPS]) */
        pEthModule->DMA_CH[channelId].TX_CONTROL.B.ST = ETH_BIT_DISABLE;
        ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_DISABLE, pEthModule->DMA_CH[channelId].TX_CONTROL.B.ST);

        /* Flush the corresponding MTL Tx Queue (Channels and queues are mapped 1:1) */
        switch(channelId)
        {
            case (uint8)ETH_MTL_QUEUE0:
                pEthModule->MTL_TXQ0.OPERATION_MODE.B.FTQ = ETH_BIT_ENABLE;
                break;
            case (uint8)ETH_MTL_QUEUE1:
                pEthModule->MTL_TXQ1.OPERATION_MODE.B.FTQ = ETH_BIT_ENABLE;
                break;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
            case (uint8)ETH_MTL_QUEUE2:
                pEthModule->MTL_TXQ2.OPERATION_MODE.B.FTQ = ETH_BIT_ENABLE;
                break;
            case (uint8)ETH_MTL_QUEUE3:
                pEthModule->MTL_TXQ3.OPERATION_MODE.B.FTQ = ETH_BIT_ENABLE;
                break;
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
            default:
                /* #Violation: eth_hal_c_REF_8 */
                /*do nothing*/
                break;
        }
    }
    /* Make sure all Tx MTL queues are now empty */
    ethSts = Eth_Hal_CheckTxMTLEmpty(pEthNode);

    if(ETH_STATUS_OK == ethSts)
    {
        /* Disable the MAC transmitter and receiver */
        regMacConfig.U = pEthModule->MAC_CONFIGURATION.U;
        regMacConfig.B.TE = ETH_BIT_DISABLE;
        regMacConfig.B.RE = ETH_BIT_DISABLE;
        pEthModule->MAC_CONFIGURATION.U = regMacConfig.U;
        ret = Eth_Register_ReadBack_Check(ret, regMacConfig.U, pEthModule->MAC_CONFIGURATION.U);

        /* Stop all configured RxDMA channels and flush the corresponding MTL queues */
        /* #Violation: eth_hal_c_REF_1 */
        for(channelId = 0U; channelId < ETH_CTRL0_RXSCHEDULED_CFGD; channelId++)
        {
            regDmaChRxCtrl.U = pEthModule->DMA_CH[channelId].RX_CONTROL.U;
            /* Stop the RxDMA channel (This will set flag DMA_CHi_Status[RPS]) */
            regDmaChRxCtrl.B.SR = ETH_BIT_DISABLE;
            /* Flush the corresponding MTL Rx Queue (Channels and queues are not necessarily mapped 1:1) */
            regDmaChRxCtrl.B.RPF = ETH_BIT_ENABLE;
            pEthModule->DMA_CH[channelId].RX_CONTROL.U = regDmaChRxCtrl.U;
            ret = Eth_Register_ReadBack_Check(ret, regDmaChRxCtrl.U, pEthModule->DMA_CH[channelId].RX_CONTROL.U);
        }
    }

    if(FALSE == ret)
    {
        ethSts = ETH_STATUS_ERROR;
    }
    return ethSts;
}

static void Eth_Hal_ResetTransmitDescriptors(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId,
                                            uint32 curBufIdx)
{
    volatile Eth_TxDescr *pCurrDescr;

    /* Get current Tx descriptor */
    pCurrDescr = &(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[curBufIdx]);
    /* Reinitialize descriptors */
    /* TDES0,Set the transmit buffer address */
    pCurrDescr->TDES0.U = pEthNode->txDescrInfoPtr[channelId][curBufIdx].descrBufAddr;
    pCurrDescr->TDES1.U = 0;
    /* TDES3 will be configured again while transmitting each packet */
    pCurrDescr->TDES3.U = (uint32)ETH_APPLICATION_OWN; /* owned by Application */
}

static void Eth_Hal_ResetReceiveDescriptors(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId)
{
    uint32 numberOfDes;
    volatile Eth_RxDescr *pBaseDescr;
    uint32 numDescr;

    numDescr = pEthNode->rxChannelInfoPtr[channelId].numOfDescriptor;
    /* Get descriptor list base address */
    /* Reinitialize descriptors in ring mode */
    for(numberOfDes = 0; numberOfDes < numDescr; numberOfDes++)
    {
        pBaseDescr = &(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[numberOfDes]);
        /* RDES0,Set the transmit buffer address */
        pBaseDescr->RDES0.U = pEthNode->rxDescrInfoPtr[channelId][numberOfDes].descrBufAddr;
        pBaseDescr->RDES1.U = 0U; /* reserved */
        pBaseDescr->RDES2.U = 0U; /* buffer2 not used */

        pBaseDescr->RDES3.U = 0;
        pBaseDescr->RDES3.R.BUF1V = ETH_BIT_ENABLE;  /* buffer 1 valid */
        pBaseDescr->RDES3.R.BUF2V = ETH_BIT_DISABLE; /* buffer 2 not valid */
        pBaseDescr->RDES3.R.IOC = ETH_BIT_ENABLE;    /* interrupt enabled */
        pBaseDescr->RDES3.R.OWN = ETH_BIT_ENABLE;    /* owned by DMA */
    }
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_Init(Eth_NodeHandle *pEthNode, const Eth_Config *const pEthConfig)
{
    Eth_Status retStatus;
    Eth_ReturnState ethState;
    uint8 index;
    uint32 dmaIndex;
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthNode->pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pEthConfig is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthConfig));
    /* Check if the pEthConfig->pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthConfig->pEthModule));
    /* Check ETH Support Mode */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_PHY_INTERFACE_MODE(pEthConfig->phyInterfaceMode)));
    /* Check the number of ETH Tx channels */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_NUMCH(pEthConfig->ethNumTxChnls)));
    /* Check the number of ETH Rx channels */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_NUMCH(pEthConfig->ethNumRxChnls)));
    /* Check if the pEthConfig->dma.txChannel is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthConfig->dma.txChannel));
    /* Check if the pEthConfig->mtl.txQueue is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthConfig->mtl.txQueue));
    /* Check if the pEthNode->txChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr));
    /* Check if the pEthNode->txDescrInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txDescrInfoPtr));
    for(index = 0; index < pEthConfig->ethNumTxChnls; index++)
    {
        dmaIndex = pEthConfig->dma.txChannel[index].txChIdx;
        /* Check ETH Tx DMA channel ID */
        /* #Violation: eth_hal_c_REF_1 */
        Assert((boolean)(CHECK_ETH_TX_DMACH_QUEUE_ID(dmaIndex)));
        /* Check if the pEthConfig->dma.txChannel->pTxDescrList is null pointer */
        /* #Violation: eth_hal_c_REF_3 */
        Assert((boolean)(NULL_PTR != pEthConfig->dma.txChannel[index].pTxDescrList));
        /* Check if the pEthConfig->dma.txChannel->pDescTxBuffer is null pointer */
        /* #Violation: eth_hal_c_REF_3 */
        Assert((boolean)(NULL_PTR != pEthConfig->dma.txChannel[index].pDescTxBuffer));
        /* Check ETH Tx Queue ID */
        /* #Violation: eth_hal_c_REF_1 */
        Assert((boolean)(CHECK_ETH_TX_DMACH_QUEUE_ID(pEthConfig->mtl.txQueue[index].txChId)));
    }
    /* Check if the pEthConfig->dma.rxChannel is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthConfig->dma.rxChannel));
    /* Check if the pEthNode->rxChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->rxChannelInfoPtr));
    /* Check if the pEthNode->rxDescrInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->rxDescrInfoPtr));
    for(index = 0; index < pEthConfig->ethNumRxChnls; index++)
    {
        /* Check if the pEthConfig->dma.rxChannel->pRxDescrList is null pointer */
        /* #Violation: eth_hal_c_REF_3 */
        Assert((boolean)(NULL_PTR != pEthConfig->dma.rxChannel[index].pRxDescrList));
        /* Check if the pEthConfig->dma.rxChannel->pDescRxBuffer is null pointer */
        /* #Violation: eth_hal_c_REF_3 */
        Assert((boolean)(NULL_PTR != pEthConfig->dma.rxChannel[index].pDescRxBuffer));
    }
    /* Check line speed */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_LINE_SPEED(pEthConfig->mac.lineSpeed)));
    /* Check if the ethFre equal zero */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(0U != pEthConfig->ethFre));

#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    retStatus = ETH_STATUS_ERROR;
    pEthNode->pEthModule = pEthConfig->pEthModule;
    pEthNode->ethMiiCrValue = pEthConfig->ethMiiCrValue;
    pEthNode->numOfUsedTxCh = pEthConfig->ethNumTxChnls;
    for(index = 0; index < pEthConfig->ethNumTxChnls; index++)
    {
        dmaIndex = pEthConfig->dma.txChannel[index].txChIdx;
        pEthNode->txChannelInfoPtr[dmaIndex].txChannelEnabled = pEthConfig->dma.txChannel[index].txChannelEnabled;
        pEthNode->txChannelInfoPtr[dmaIndex].numOfDescriptor = pEthConfig->dma.txChannel[index].numOfTxBuffers;
    }

    for(index = 0; index < pEthConfig->ethNumRxChnls; index++)
    {
        pEthNode->rxChannelInfoPtr[index].rxChannelEnabled = pEthConfig->dma.rxChannel[index].rxChannelEnabled;
        pEthNode->rxChannelInfoPtr[index].numOfDescriptor =  pEthConfig->dma.rxChannel[index].numOfRxBuffers;
    }

    /* Set the phy interface mode and set time-delay when the mode is RGMII mode */
    ret &= Eth_Hal_SetPhyInterfaceMode(
            pEthConfig->pEthModule,
            pEthConfig->phyInterfaceMode,
            pEthConfig->txClkDelay,
            pEthConfig->rxClkDelay);
    /* reset the Module */
    ethState = Eth_Std_ResetModule(pEthConfig->pEthModule);

    if(ETH_RETURN_TRUE == ethState)
    {

        /* Configure the operating mode of the DMA */
        ret &= Eth_Hal_ConfigureDma(pEthNode, pEthConfig);

        /* Configure the operating mode of the MTL */
        ret &= Eth_Hal_ConfigureMtl(pEthConfig->pEthModule, pEthConfig);

        /* Configure the operating mode of the MAC */
        ret &= Eth_Hal_ConfigureMac(pEthNode, &pEthConfig->mac);

        retStatus = ETH_STATUS_OK;
        if(TRUE == pEthConfig->mac.enableTimestamp)
        { /*Configure TimeStamp*/
            if(ETH_RETURN_TRUE ==
               Eth_Std_InitTime(pEthConfig->pEthModule, pEthConfig->ethFre, &pEthNode->prevFreqCompensationValue))
            {
                retStatus = ETH_STATUS_OK;
            }
            else
            {
                retStatus = ETH_STATUS_ERROR;
            }
        }
    }

    if(FALSE == ret)
    {
        retStatus = ETH_STATUS_ERROR;
    }
    return retStatus;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_ModeType Eth_Hal_GetControllerMode(const Eth_NodeHandle *const pEthNode)
{
    Eth_ModeType ethMode;
    /* #Violation: eth_hal_c_REF_4 */
    ETH_MAC_CONFIGURATION regMacConfiguration;
    uint8 channelIndex;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthNode->pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check the number of ETH Tx channels */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_NUMCH(pEthNode->numOfUsedTxCh)));
    /* Check if the pEthNode->txChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr));
    /* Check if the pEthNode->rxChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->rxChannelInfoPtr));
#endif /* INPUT_ARG_DETECT */

    regMacConfiguration.U = pEthNode->pEthModule->MAC_CONFIGURATION.U;

    /* MAC_CONFIGURATION.B.TE mac_enableTransmitter, bit1; MAC_CONFIGURATION.B.RE mac_enableReceiver, bit0 */
    if((ETH_BIT_ENABLE == regMacConfiguration.B.TE) && (ETH_BIT_ENABLE == regMacConfiguration.B.RE))
    {
        ethMode = ETH_MODE_ACTIVE;
        /* Start all configured TxDMA channels */
        for(channelIndex = 0U; (channelIndex < pEthNode->numOfUsedTxCh) && (ethMode == ETH_MODE_ACTIVE);
            channelIndex++)
        {
            if(TRUE == pEthNode->txChannelInfoPtr[channelIndex].txChannelEnabled)
            {
                if(pEthNode->pEthModule->DMA_CH[channelIndex].TX_CONTROL.B.ST == ETH_BIT_DISABLE)
                {
                    ethMode = ETH_MODE_DOWN;
                }
            }

            if(TRUE == pEthNode->rxChannelInfoPtr[channelIndex].rxChannelEnabled)
            {
                if(pEthNode->pEthModule->DMA_CH[channelIndex].RX_CONTROL.B.SR == ETH_BIT_DISABLE)
                {
                    ethMode = ETH_MODE_DOWN;
                }
            }
        }
    }
    else
    {
        ethMode = ETH_MODE_DOWN;
    }
    return ethMode;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_SetControllerMode(const Eth_NodeHandle *const pEthNode, Eth_ModeType ctrlMode)
{
    Eth_Status ethSts;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check the number of ETH Tx channels */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_NUMCH(pEthNode->numOfUsedTxCh)));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pEthNode->txChannelInfoPtr[channelId].pTxDescriptor is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr));
#endif /* INPUT_ARG_DETECT */

    if(ETH_MODE_ACTIVE == ctrlMode)
    {
        ethSts = Eth_Hal_StartDevice(pEthNode);
    }
    else
    {
        ethSts = Eth_Hal_StopDevice(pEthNode);
    }

    return ethSts;
}

/* #Violation: eth_hal_c_REF_11 */
/* #Violation: eth_hal_c_REF_10 */
/* #Violation: eth_hal_c_REF_17 */
void Eth_Hal_GetMacAddress(const Eth_NodeHandle *const pEthNode, uint8 *const pMacAddr)
{
    uint32 regVal;
    const ETH_MODULE *pEthModule;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pMacAddr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pMacAddr));
#endif /* INPUT_ARG_DETECT */

    pEthModule = pEthNode->pEthModule;
    regVal = (uint32)pEthModule->MAC_ADDRESS_HIGH0.U;
    pMacAddr[5U] = (uint8)((regVal >> 8U) & 0x00ffU);
    pMacAddr[4U] = (uint8)(regVal & 0x00ffU);

    regVal = (uint32)pEthModule->MAC_ADDRESS_LOW0.U;
    pMacAddr[3U] = (uint8)((regVal >> 24U));
    pMacAddr[2U] = (uint8)((regVal >> 16U) & 0x00ffU);
    pMacAddr[1U] = (uint8)((regVal >> 8U) & 0x00ffU);
    pMacAddr[0U] = (uint8)(regVal & 0x00ffU);
}

/* #Violation: eth_hal_c_REF_11 */
/* #Violation: eth_hal_c_REF_10 */
/* #Violation: eth_hal_c_REF_17 */
boolean Eth_Hal_SetMacAddress(const Eth_NodeHandle *const pEthNode, const uint8 *const pMacAddr)
{
    uint32 regVal;
    ETH_MODULE *pEthModule;
    boolean ret;
    uint32 macAddrLow0;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pMacAddr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pMacAddr));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    pEthModule = pEthNode->pEthModule;
    regVal = (uint32)(pEthModule->MAC_ADDRESS_HIGH0.U & 0xFFFF0000U);
    regVal |= (uint32)pMacAddr[4] + ((uint32)pMacAddr[5] << 8U) + 0x80000000U;
    pEthModule->MAC_ADDRESS_HIGH0.U = regVal;
    ret = Eth_Register_ReadBack_Check(ret, regVal, pEthModule->MAC_ADDRESS_HIGH0.U);

    macAddrLow0 = (uint32)pMacAddr[0] + ((uint32)pMacAddr[1] << 8U) + ((uint32)pMacAddr[2] << 16U) + ((uint32)pMacAddr[3] << 24U);
    pEthModule->MAC_ADDRESS_LOW0.U = macAddrLow0;
    ret = Eth_Register_ReadBack_Check(ret, macAddrLow0, pEthModule->MAC_ADDRESS_LOW0.U);
    
    return ret;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_UpdatePhysAddrFilter(const Eth_NodeHandle *const pEthNode, const uint8 *const pMacAddr,
                                        Eth_FilterActionType action)
{
    Eth_Status ethSts;
    uint32 addrLow;
    uint32 addrHigh;
    uint32 iCount;
    ETH_MODULE *pEthModule;
    uint8 localMacAddress[ETH_MAC_ADDRESS_GROUP_MAXNUM];
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pMacAddr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pMacAddr));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    ethSts = ETH_STATUS_ERROR;
    /* Get the local MAC address */
    Eth_Hal_GetMacAddress(pEthNode, localMacAddress);
    /*If the local MAC address is the filter MAC address, then return error status */
    for(iCount=0; ((iCount<ETH_MAC_ADDRESS_GROUP_MAXNUM)&&(ETH_STATUS_OK != ethSts)); iCount++)
    {
      if(localMacAddress[iCount] != pMacAddr[iCount])
      {
          ethSts = ETH_STATUS_OK;
      }
    }

    if(ETH_STATUS_OK == ethSts)
    {
        pEthModule = pEthNode->pEthModule;
        addrLow = (uint32)pMacAddr[0U];
        addrLow |= (((uint32)pMacAddr[1U]) << 8U);
        addrLow |= (((uint32)pMacAddr[2U]) << 16U);
        addrLow |= (((uint32)pMacAddr[3U]) << 24U);
        addrHigh = (uint32)pMacAddr[4U];
        addrHigh |= (((uint32)pMacAddr[5U]) << 8U);

        if(ETH_ADD_TO_FILTER == action)
        {
            if((0U == addrLow) && (0U == addrHigh))
            {
                /*If the physical source address (MAC address) is set to 00:00:00:00:00:00,
                 * this shall reduce the filter to the controllers unique unicast MAC
                 * address and end promiscuous  mode if it was turned on.*/
                ret &= Eth_Std_ClearDaFilter(pEthModule);
                ethSts = ETH_STATUS_OK;
            }
            else if((0xFFFFFFFFU == addrLow) && (0x0000FFFFU == addrHigh))
            {
                /* open the filter completely */
                ret &= Eth_Std_SetPromiscuous(pEthModule, TRUE);
                ret &= Eth_Std_SetMulticast(pEthModule, TRUE);
                ethSts = ETH_STATUS_OK;
            }
            else
            {
                ret &= Eth_Std_SetPromiscuous(pEthModule, FALSE);
                ret &= Eth_Std_SetMulticast(pEthModule, FALSE);
                ethSts = ((ETH_RETURN_TRUE == Eth_Std_AddDaFilter(pEthModule, addrHigh, addrLow)) ? ETH_STATUS_OK
                                                                                                 : ETH_STATUS_ERROR);
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
                pEthModule->MAC_PACKET_FILTER.B.HPF = ETH_BIT_ENABLE; /* Perfect filter */
                ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MAC_PACKET_FILTER.B.HPF);
#endif
            }
        }
        else
        {
            /* remove */
            if((0U == addrLow) && (0U == addrHigh))
            {
                ethSts = ETH_STATUS_ERROR;
            }
            else
            {
                ret &= Eth_Std_SetPromiscuous(pEthModule, FALSE);
                ret &= Eth_Std_SetMulticast(pEthModule, FALSE);
                ethSts = ((ETH_RETURN_TRUE == Eth_Std_RemoveDaFilter(pEthModule, addrHigh, addrLow)) ? ETH_STATUS_OK
                                                                                                    : ETH_STATUS_ERROR);
            }
        }
    }

    if(FALSE == ret)
    {
        ethSts = ETH_STATUS_ERROR;
    }
    return ethSts;
}

/* #Violation: eth_hal_c_REF_2 */
void Eth_Hal_GetDropCounter(const Eth_NodeHandle *const pEthNode, Eth_CounterType *const pDropCounter)
{
    uint32 totalErronInbPkts;
    const ETH_MODULE *pEthModule;
    uint32 txPacketCountGoodBadVal;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pDropCounter is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pDropCounter));
#endif /* INPUT_ARG_DETECT */

    pEthModule = pEthNode->pEthModule;
    pDropCounter->DropPktBufOverrun = (uint32)(pEthModule->RX_FIFO_OVERFLOW_PACKETS.B.RXFIFOOVFL);
    pDropCounter->DropPktCrc = (uint32)(pEthModule->RX_CRC_ERROR_PACKETS.B.RXCRCERR);
    pDropCounter->UndersizePkt = (uint32)(pEthModule->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG);
    pDropCounter->OversizePkt = (uint32)(pEthModule->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG);
    pDropCounter->AlgnmtErr = (uint32)(pEthModule->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR);
    /* SQE test error,this error counter is not available from Hardware*/
    pDropCounter->SqeTestErr = ETH_COUNTER_NOT_AVAILABLE;
    pDropCounter->DiscInbdPkt = (uint32)(pEthModule->RX_FIFO_OVERFLOW_PACKETS.B.RXFIFOOVFL);
    /* Total number of erroneous inbound packets.
       Info:This item is filled with counter that wihch is addition of all receive
       error counters available from hardware */
    totalErronInbPkts = (uint32)(pEthModule->RX_CRC_ERROR_PACKETS.B.RXCRCERR);
    totalErronInbPkts = (uint32)(totalErronInbPkts + pEthModule->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR);
    totalErronInbPkts = (uint32)(totalErronInbPkts + pEthModule->RX_RUNT_ERROR_PACKETS.B.RXRUNTERR);
    totalErronInbPkts = (uint32)(totalErronInbPkts + pEthModule->RX_JABBER_ERROR_PACKETS.B.RXJABERR);
    totalErronInbPkts = (uint32)(totalErronInbPkts + pEthModule->RX_LENGTH_ERROR_PACKETS.B.RXLENERR);
    totalErronInbPkts = (uint32)(totalErronInbPkts + pEthModule->RX_OUT_OF_RANGE_TYPE_PACKETS.B.RXOUTOFRNG);
    totalErronInbPkts = (uint32)(totalErronInbPkts + pEthModule->RX_RECEIVE_ERROR_PACKETS.B.RXRCVERR);
    pDropCounter->ErrInbdPkt = totalErronInbPkts;
    pDropCounter->DiscOtbdPkt = (uint32)(pEthModule->TX_UNDERFLOW_ERROR_PACKETS.B.TXUNDRFLW);
    txPacketCountGoodBadVal = (uint32)pEthModule->TX_PACKET_COUNT_GOOD_BAD.B.TXPKTGB;
    pDropCounter->ErrOtbdPkt =
        (uint32)(txPacketCountGoodBadVal - (uint32)pEthModule->TX_PACKET_COUNT_GOOD.B.TXPKTG);
    pDropCounter->SnglCollPkt = (uint32)(pEthModule->TX_SINGLE_COLLISION_GOOD_PACKETS.B.TXSNGLCOLG);
    pDropCounter->MultCollPkt = (uint32)(pEthModule->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.TXMULTCOLG);
    pDropCounter->DfrdPkt = (uint32)(pEthModule->TX_DEFERRED_PACKETS.B.TXDEFRD);
    pDropCounter->LatCollPkt = (uint32)(pEthModule->TX_LATE_COLLISION_PACKETS.B.TXLATECOL);
    pDropCounter->HwDepCtr0 = 0U;
    pDropCounter->HwDepCtr1 = 0U;
    pDropCounter->HwDepCtr2 = 0U;
    pDropCounter->HwDepCtr3 = 0U;
}

/* #Violation: eth_hal_c_REF_2 */
void Eth_Hal_GetEtherStats(const Eth_NodeHandle *const pEthNode, Eth_RxStatsType *const pEtherStats)
{
    const ETH_MODULE *pEthModule;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pEtherStats is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEtherStats));
#endif /* INPUT_ARG_DETECT */

    pEthModule = pEthNode->pEthModule;
    /* Maximal possible value shall denote an invalid value (e.g. counter not available) */
    pEtherStats->RxStatsDropEvents = (uint32)(pEthModule->RX_FIFO_OVERFLOW_PACKETS.B.RXFIFOOVFL);
    pEtherStats->RxStatsOctets = (uint32)(pEthModule->RX_OCTET_COUNT_GOOD_BAD.B.RXOCTGB);
    pEtherStats->RxStatsPkts = (uint32)(pEthModule->RX_PACKETS_COUNT_GOOD_BAD.B.RXPKTGB);
    pEtherStats->RxStatsBroadcastPkts = (uint32)(pEthModule->RX_BROADCAST_PACKETS_GOOD.B.RXBCASTG);
    pEtherStats->RxStatsMulticastPkts = (uint32)(pEthModule->RX_MULTICAST_PACKETS_GOOD.B.RXMCASTG);
    pEtherStats->RxStatsCrcAlignErrors = (uint32)(pEthModule->RX_CRC_ERROR_PACKETS.B.RXCRCERR);
    pEtherStats->RxStatsCrcAlignErrors += (uint32)(pEthModule->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR);
    pEtherStats->RxStatsUndersizePkts = (uint32)(pEthModule->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG);
    pEtherStats->RxStatsOversizePkts = (uint32)(pEthModule->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG);
    pEtherStats->RxStatsFragments = (uint32)(pEthModule->RX_RUNT_ERROR_PACKETS.B.RXRUNTERR);
    pEtherStats->RxStatsJabbers = (uint32)(pEthModule->RX_JABBER_ERROR_PACKETS.B.RXJABERR);
    /* etherStatsCollisions,this error counter is not available from Hardware */
    pEtherStats->RxStatsCollisions = ETH_COUNTER_NOT_AVAILABLE;
    pEtherStats->RxStatsPkts64Octets = (uint32)(pEthModule->RX_64OCTETS_PACKETS_GOOD_BAD.B.RX64OCTGB);
    pEtherStats->RxStatsPkts65to127Octets = (uint32)(pEthModule->RX_65TO127OCTETS_PACKETS_GOOD_BAD.B.RX65_127OCTGB);
    pEtherStats->RxStatsPkts128to255Octets =
        (uint32)(pEthModule->RX_128TO255OCTETS_PACKETS_GOOD_BAD.B.RX128_255OCTGB);
    pEtherStats->RxStatsPkts256to511Octets =
        (uint32)(pEthModule->RX_256TO511OCTETS_PACKETS_GOOD_BAD.B.RX256_511OCTGB);
    pEtherStats->RxStatsPkts512to1023Octets =
        (uint32)(pEthModule->RX_512TO1023OCTETS_PACKETS_GOOD_BAD.B.RX512_1023OCTGB);
    pEtherStats->RxStatsPkts1024to1518Octets =
        (uint32)(pEthModule->RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD.B.RX1024_MAXOCTGB);
}

/* #Violation: eth_hal_c_REF_2 */
void Eth_Hal_GetTxStats(const Eth_NodeHandle *const pEthNode, Eth_TxStatsType *const pTxStats)
{
    const ETH_MODULE *pEthModule;
    uint32 TxNUcastPktsCnt;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pEtherStats is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pTxStats));
#endif /* INPUT_ARG_DETECT */

    pEthModule = pEthNode->pEthModule;
    /* txNumberOfOctets - number of octets transmitted */
    pTxStats->TxNumberOfOctets = (uint32)(pEthModule->TX_OCTET_COUNT_GOOD_BAD.U);
    /* txNUcastPkts - Total number of non-unicast packets transmitted */
    TxNUcastPktsCnt = (uint32)(pEthModule->TX_MULTICAST_PACKETS_GOOD_BAD.U);
    pTxStats->TxNUcastPkts = (uint32)(TxNUcastPktsCnt + pEthModule->TX_BROADCAST_PACKETS_GOOD_BAD.U);
    /* txUniCastPkts - Total number of unicast packets transmitted */
    pTxStats->TxUniCastPkts = (uint32)(pEthModule->TX_UNICAST_PACKETS_GOOD_BAD.U);
}

/* #Violation: eth_hal_c_REF_2 */
void Eth_Hal_GetTxErrorCounterValues(const Eth_NodeHandle *const pEthNode, Eth_TxErrorCounterValuesType *const pTxErrorCounterValues)
{
    const ETH_MODULE *pEthModule;
    uint32 txDroppedErrPktsCnt;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pEtherStats is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pTxErrorCounterValues));
#endif /* INPUT_ARG_DETECT */

    pEthModule = pEthNode->pEthModule;
    /* txDroppedNoErrorPkts - Not supported */
    pTxErrorCounterValues->TxDroppedNoErrorPkts = (uint32)0xFFFFFFFFU; /* Not support */
    /* txDroppedErrorPkts - Total number of outbound packets that could not be transmitted because of errors */
    txDroppedErrPktsCnt = (uint32)(pEthModule->TX_UNDERFLOW_ERROR_PACKETS.U);
    txDroppedErrPktsCnt += (uint32)(pEthModule->TX_LATE_COLLISION_PACKETS.U);
    txDroppedErrPktsCnt += (uint32)(pEthModule->TX_EXCESSIVE_COLLISION_PACKETS.U);
    txDroppedErrPktsCnt += (uint32)(pEthModule->TX_CARRIER_ERROR_PACKETS.U);
    pTxErrorCounterValues->TxDroppedErrorPkts = (uint32)(txDroppedErrPktsCnt + pEthModule->TX_EXCESSIVE_DEFERRAL_ERROR.U);
    /* TxDeferredTrans - Count of frames for which the first Tx attempt is delayed because the medium is busy */
    pTxErrorCounterValues->TxDeferredTrans = (uint32)(pEthModule->TX_DEFERRED_PACKETS.U);
    /* TxSingleCollision - Count of frames for which Tx is inhibited by exactly one collision */
    pTxErrorCounterValues->TxSingleCollision =  (uint32)(pEthModule->TX_SINGLE_COLLISION_GOOD_PACKETS.U);
    /* TxMultipleCollision - Count of frames for which Tx is inhibited by more than one collision */
    pTxErrorCounterValues->TxMultipleCollision = (uint32)(pEthModule->TX_MULTIPLE_COLLISION_GOOD_PACKETS.U);
    /* TxLateCollision - Count of packets aborted because of late collision */
    pTxErrorCounterValues->TxLateCollision = (uint32)(pEthModule->TX_LATE_COLLISION_PACKETS.U);
    /* TxExcessiveCollsion - Count of packets aborted due of excessive collisions */
    pTxErrorCounterValues->TxExcessiveCollison = (uint32)(pEthModule->TX_EXCESSIVE_COLLISION_PACKETS.U);
}

/* #Violation: eth_hal_c_REF_2 */
Eth_RxStatusType Eth_Hal_Receive(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint8 **const pRxBuf, uint16 *const pReceiveLength,
                             Eth_RxInfo *const pRxInfo)
{
    Eth_RxDescr *pCurDescr;
    uint32 bufIdx;
    Eth_RxStatusType ethRxSts;
#if (defined(ETH_SPLICING_ENABLE) && (ETH_SPLICING_ENABLE == TRUE))
    uint16 packetLength;
#endif

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthNode->rxDescrInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->rxDescrInfoPtr));
    /* Check if the pEthNode->rxChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->rxChannelInfoPtr));
    /* Check ETH channel number */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_CHANNEL(channelId)));
    /* Check if the pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor));
    /* Check if the pEthNode->rxChannelInfoPtr[channelId].pRxDescriptor is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->rxChannelInfoPtr[channelId].pRxDescriptor));
    /* Check if the pRxBuf is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pRxBuf));
    /* Check if the pReceiveLength is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pReceiveLength));
    /* Check if the pRxInfo is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pRxInfo));
#endif /* INPUT_ARG_DETECT */

    uint32 curDescIndex;
    curDescIndex = pEthNode->rxChannelInfoPtr[channelId].descIndex;
    /* Get descriptor list base address */
    pCurDescr = &(pEthNode->rxChannelInfoPtr[channelId].pRxBaseDescriptor[curDescIndex]);
    pRxInfo->pCurDescr = NULL_PTR;
    /* own by application */
    if ((uint32)ETH_DMA_OWN == pCurDescr->RDES3.R.OWN)
    {
        ethRxSts = ETH_NOT_RECEIVED;
    }
    else
    {
        ethRxSts = ETH_RECEIVED;
        /* Get the buffer index */
        bufIdx = curDescIndex;

#if (defined(ETH_SPLICING_ENABLE) && (ETH_SPLICING_ENABLE == TRUE))
        /* The first segment of the packet and but not the last segment */
        if(((pCurDescr->RDES3.W.FD == 1U) && (pCurDescr->RDES3.W.LD != 1U)) ||
           ((pCurDescr->RDES3.W.FD != 1U) && (pCurDescr->RDES3.W.LD != 1U))) /* Intermediate segment of the packet */
        {
            /* Get the packet length,this is the accumulated number of bytess that have been received for the current
             * packet */
            packetLength = (uint16)(pCurDescr->RDES3.W.PL);
            *pReceiveLength = (uint16)packetLength - pEthNode->rxChannelInfoPtr[channelId].rxCount;
            /* Update pEthNode->rxChannel[channelId].rxCount to the accumulated number of bytes */
            pEthNode->rxChannelInfoPtr[channelId].rxCount = packetLength;
            /* #Violation: eth_hal_c_REF_9 */
            /* #Violation: eth_hal_c_REF_12 */
            /* #Violation: eth_hal_c_REF_14 */
            *pRxBuf = (uint8 *)pEthNode->rxDescrInfoPtr[channelId][curDescIndex].descrBufAddr;
        }
        /* Check if Last Descriptor bit (LD) is set, should be the last segment and the first segment of the packet*/
        else if(ETH_BIT_ENABLE == pCurDescr->RDES3.W.LD)
        {
            /* check whether it is good packet or bad packet */
            if(ETH_BIT_DISABLE == pCurDescr->RDES3.W.ERRSUM)
            {
                /* good package, get the packet length */
                *pReceiveLength = (uint16)(pCurDescr->RDES3.W.PL);
                pEthNode->rxChannelInfoPtr[channelId].rxCount = 0;
                /* #Violation: eth_hal_c_REF_9 */
                /* #Violation: eth_hal_c_REF_12 */
                /* #Violation: eth_hal_c_REF_14 */
                *pRxBuf = (uint8 *)pEthNode->rxDescrInfoPtr[channelId][curDescIndex].descrBufAddr;
                /* #Violation: eth_hal_c_REF_7 */
                pRxInfo->errStatus = pCurDescr->RDES3.U;

                if(ETH_BIT_ENABLE == pCurDescr->RDES3.W.RS1V)
                {
                    pRxInfo->ipHeaderErr = pCurDescr->RDES1.W.IPHE;
                    pRxInfo->ipPayloadErr = pCurDescr->RDES1.W.IPCE;
                    pRxInfo->ipv4 = pCurDescr->RDES1.W.IP4;
                    pRxInfo->ipv6 = pCurDescr->RDES1.W.IP6;
                    /* #Violation: eth_hal_c_REF_6 */
                    pRxInfo->payloadType = (Eth_PayloadType)pCurDescr->RDES1.W.PT;
                }

                if(ETH_BIT_ENABLE == pCurDescr->RDES3.W.RS0V)
                {
                    pRxInfo->outerVlanTag = (uint16)(pCurDescr->RDES0.U & ETH_RDES0_OVT_MASK);
                    pRxInfo->innerVlanTag = (uint16)((pCurDescr->RDES0.U & ETH_RDES0_IVT_MASK) >> ETH_RDES0_IVT_SHIFT);
                }
                else
                {
                    pRxInfo->outerVlanTag = 0U;
                    pRxInfo->innerVlanTag = 0U;
                }
                /* Get ingress time-stamp */
                Eth_Hal_GetIngressTimeStamp(pEthNode, channelId, pRxInfo);
            }
            else
            {
                /* #Violation: eth_hal_c_REF_7 */
                pRxInfo->errStatus = pCurDescr->RDES3.U;
                if(ETH_BIT_ENABLE == pCurDescr->RDES3.W.RS1V)
                {
                    pRxInfo->ipHeaderErr = pCurDescr->RDES1.W.IPHE;
                    pRxInfo->ipPayloadErr = pCurDescr->RDES1.W.IPCE;
                }
                *pReceiveLength = 0U;
                ethRxSts = ETH_NOT_RECEIVED;
                Eth_Hal_ResetReceiveDescriptors(pEthNode, channelId);
            }
        }
        else
        {
            *pReceiveLength = 0U;
            ethRxSts = ETH_NOT_RECEIVED;
        }
#else
        if((pCurDescr->RDES3.W.FD == 1U) && (pCurDescr->RDES3.W.LD == 1U))
        {
            /* check whether it is good packet or bad packet */
            if(ETH_BIT_DISABLE == pCurDescr->RDES3.W.ERRSUM)
            {
                /* good package, get the packet length */
                *pReceiveLength = (uint16)(pCurDescr->RDES3.W.PL);
                /* #Violation: eth_hal_c_REF_9 */
                /* #Violation: eth_hal_c_REF_12 */
                /* #Violation: eth_hal_c_REF_14 */
                *pRxBuf = (uint8 *)pEthNode->rxDescrInfoPtr[channelId][curDescIndex].descrBufAddr;
                /* #Violation: eth_hal_c_REF_7 */
                pRxInfo->errStatus = pCurDescr->RDES3.U;

                if(ETH_BIT_ENABLE == pCurDescr->RDES3.W.RS1V)
                {
                    pRxInfo->ipHeaderErr = pCurDescr->RDES1.W.IPHE;
                    pRxInfo->ipPayloadErr = pCurDescr->RDES1.W.IPCE;
                    pRxInfo->ipv4 = pCurDescr->RDES1.W.IP4;
                    pRxInfo->ipv6 = pCurDescr->RDES1.W.IP6;
                    /* #Violation: eth_hal_c_REF_6 */
                    pRxInfo->payloadType = (Eth_PayloadType)pCurDescr->RDES1.W.PT;
                }

                if(ETH_BIT_ENABLE == pCurDescr->RDES3.W.RS0V)
                {
                    pRxInfo->outerVlanTag = (uint16)(pCurDescr->RDES0.U & ETH_RDES0_OVT_MASK);
                    pRxInfo->innerVlanTag = (uint16)((pCurDescr->RDES0.U & ETH_RDES0_IVT_MASK) >> ETH_RDES0_IVT_SHIFT);
                }
                else
                {
                    pRxInfo->outerVlanTag = 0U;
                    pRxInfo->innerVlanTag = 0U;
                }
                /* Get ingress time-stamp */
                Eth_Hal_GetIngressTimeStamp(pEthNode, channelId, pRxInfo);
            }
            else
            {
                /* #Violation: eth_hal_c_REF_7 */
                pRxInfo->errStatus = pCurDescr->RDES3.U;
                if(ETH_BIT_ENABLE == pCurDescr->RDES3.W.RS1V)
                {
                    pRxInfo->ipHeaderErr = pCurDescr->RDES1.W.IPHE;
                    pRxInfo->ipPayloadErr = pCurDescr->RDES1.W.IPCE;
                }
                *pReceiveLength = 0U;
                ethRxSts = ETH_NOT_RECEIVED;
                Eth_Hal_ResetReceiveDescriptors(pEthNode, channelId);
            }
        }
        else
        {
            *pReceiveLength = 0U;
            ethRxSts = ETH_NOT_RECEIVED;
        }
#endif
        pRxInfo->pCurDescr = pCurDescr;
        /* Free the receive descriptor, enabling it for the further reception */
        Eth_Hal_ResetRxDescriptor(pCurDescr, pEthNode->rxDescrInfoPtr[channelId][bufIdx].descrBufAddr);
        /* Shuffle to next descriptor */
        Eth_Hal_ShuffleRxDescriptor(pEthNode, channelId);

        if (ETH_RECEIVED == ethRxSts)
        {
#if (defined(ETH_SPLICING_ENABLE) && (ETH_SPLICING_ENABLE == TRUE))
            /* own by application */
            if ((uint32)ETH_APPLICATION_OWN ==
                pEthNode->rxChannelInfoPtr[channelId].pRxDescriptor->RDES3.R.OWN)
            {
                ethRxSts = ETH_RECEIVED_MORE_DATA_AVAILABLE;
            }
#else
            /* own by application, LD,FD are set */
            if (ETH_RDES3_OWN_LD_FD == (pEthNode->rxChannelInfoPtr[channelId].pRxDescriptor->RDES3.U & ETH_RDES3_OWN_LD_FD))
            {
                ethRxSts = ETH_RECEIVED_MORE_DATA_AVAILABLE;
            }
#endif
        }
    }
    return ethRxSts;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_GetTxBuffer(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 *const pBufIdx, uint8 **const pTxBuf,
                               uint16 *const pLenByte)
{
    volatile const Eth_TxDescr *pCurDescr;
    uint32 curDescIndex;
    Eth_Status ethSts;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthNode->txChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr));
    /* Check ETH channel number */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_CHANNEL(channelId)));
    /* Check if the pEthNode->txChannelInfoPtr[channelId].pTxDescriptor is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr[channelId].pTxDescriptor));
    /* Check if the pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor));
    /* Check if the pBufIdx is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pBufIdx));
    /* Check if the pTxBuf is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pTxBuf));
    /* Check if the pLenByte is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pLenByte));
#endif /* INPUT_ARG_DETECT */

    /* Get descriptor list base address */

    /* Get the pointer to current TX descriptor */
    pCurDescr = pEthNode->txChannelInfoPtr[channelId].pTxDescriptor;

    /* check descriptor whether own by application */
    if((uint32)ETH_DMA_OWN == pCurDescr->TDES3.R.OWN)
    {
        ethSts = ETH_STATUS_BUSY;
    }
    else
    {
        if((*pLenByte) > pEthNode->txChannelInfoPtr[channelId].txBuffer1Size)
        {
            /* If a buffer is requested with Eth_Hal_GetTxBuffer that is larger than the available
            buffer length, then report an error and return available buffer length */
            *pLenByte = pEthNode->txChannelInfoPtr[channelId].txBuffer1Size;
            ethSts = ETH_STATUS_OVFL;
        }
        else
        {
            curDescIndex = pEthNode->txChannelInfoPtr[channelId].descIndex;
            Eth_Hal_ResetTransmitDescriptors(pEthNode, channelId, curDescIndex);
            /* #Violation: eth_hal_c_REF_9 */
            /* #Violation: eth_hal_c_REF_12 */
            /* #Violation: eth_hal_c_REF_14 */
            *pTxBuf = (uint8 *)pCurDescr->TDES0.U;
            /* Get the buffer index */
            *pBufIdx = curDescIndex;
            Eth_Hal_ShuffleTxDescriptor(pEthNode, channelId);
            ethSts = ETH_STATUS_OK;
        }
    }
    return ethSts;
}

 /* #Violation: eth_hal_c_REF_2 */
boolean Eth_Hal_Transmit(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 beginBufIdx, uint32 endBufIdx,
                      uint32 packetLength)
{
    uint32 curBufIdx;
    uint32 packetLengthVal;
    volatile Eth_TxDescr *pFirstDescr;
    volatile Eth_TxDescr *pCurrDescr;
    volatile const Eth_TxDescr *pLastDescr;
    boolean ret;
    uint32 numDescr;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthNode->txChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr));
    /* Check ETH channel number */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_CHANNEL(channelId)));
    /* Check if the pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor));
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(packetLength > 0U));
#endif /* INPUT_ARG_DETECT */
    numDescr = pEthNode->txChannelInfoPtr[channelId].numOfDescriptor;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)((beginBufIdx < numDescr) && (endBufIdx < numDescr)));
    if(endBufIdx > beginBufIdx)
    {
        /* #Violation: eth_hal_c_REF_3 */
         Assert((boolean)((endBufIdx-beginBufIdx)<numDescr));
    }
    else
    {
        /* #Violation: eth_hal_c_REF_3 */
        Assert((boolean)((beginBufIdx-endBufIdx)<numDescr));
    }
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    /* Get the pointer to current TX descriptor */
    pFirstDescr = &(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[beginBufIdx]);
    pCurrDescr = pFirstDescr;

    packetLengthVal = packetLength;
    /* configure the first descriptor */
    Eth_Hal_ResetTransmitDescriptors(pEthNode, channelId, beginBufIdx); /* Reset transmit descriptors */
    pFirstDescr->TDES3.R.FL_TPL = packetLengthVal; /* total length of the packet */
    pFirstDescr->TDES3.R.TSE = 0U;              /* TCP Segmentation Disable */
    /* IP Header checksum and payload checksum calculation and insertion are enabled */
    pFirstDescr->TDES3.R.CIC_TPL = 3U;
    pFirstDescr->TDES3.R.SAIC = 0U; /* Source Address insertion disabled */
    pFirstDescr->TDES3.R.CPC = 0U;  /* CRC and PAD insertion enabled */

    curBufIdx = beginBufIdx;
    /* configure every other descriptor including first descriptor for the frame transmission */
    while(curBufIdx != endBufIdx)
    {
        if(curBufIdx != beginBufIdx)
        {
            Eth_Hal_ResetTransmitDescriptors(pEthNode, channelId, curBufIdx); /* Reset transmit descriptors */
        }
        pCurrDescr->TDES3.R.FD = 0U;
        pCurrDescr->TDES3.R.LD = 0U;
        pCurrDescr->TDES2.R.IOC = 0U; /* Clear the IOC bits for intermeditate buffers */
        pCurrDescr->TDES2.R.B1L = pEthNode->txChannelInfoPtr[channelId].txBuffer1Size;
        packetLengthVal -= pEthNode->txChannelInfoPtr[channelId].txBuffer1Size;

        pCurrDescr->TDES3.R.OWN = (uint32)ETH_DMA_OWN; /* release to DMA */

        curBufIdx++;
        if(curBufIdx == numDescr)
        {
            curBufIdx = 0U;
        }
        pCurrDescr = &(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[curBufIdx]);
    }

    /* The last descriptor of the frame */
    pCurrDescr->TDES3.R.FD = 0U;
    pCurrDescr->TDES3.R.LD = 1U;  /* last descriptor of the frame */
    pCurrDescr->TDES2.R.IOC = 1U; /* last descriptor of the frame set IOC */
    if(packetLengthVal >= pEthNode->txChannelInfoPtr[channelId].txBuffer1Size)
    {
        pCurrDescr->TDES2.R.B1L = pEthNode->txChannelInfoPtr[channelId].txBuffer1Size;
    }
    else
    {
        pCurrDescr->TDES2.R.B1L = packetLengthVal;
    }
    pFirstDescr->TDES3.R.FD = 1U; /* first descriptor of the frame */

    pCurrDescr->TDES3.R.OWN = (uint32)ETH_DMA_OWN; /* release to DMA */

    pLastDescr = &(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[numDescr - 1U]);
    if (pCurrDescr == pLastDescr)
    {
        /* wrap around the descriptors */
        pEthNode->txChannelInfoPtr[channelId].descIndex = 0U;
    }
    else
    {
        /* point to the next descriptor */
        pEthNode->txChannelInfoPtr[channelId].descIndex = curBufIdx + 1U;
    }

    /* Program tail pointer registers, Start to transmitter */
    /* #Violation: eth_hal_c_REF_5 */
    pEthNode->pEthModule->DMA_CH[channelId].TXDESC_TAIL_POINTER.U = (uint32)&(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[numDescr]);
    /* #Violation: eth_hal_c_REF_5 */
    ret = Eth_Register_ReadBack_Check(ret, (uint32)&(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[numDescr]), 
        pEthNode->pEthModule->DMA_CH[channelId].TXDESC_TAIL_POINTER.U);
    
    return ret;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_GetTxStatus(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 beginBufIdx, uint32 endBufIdx,
                               Eth_TxInfo *const pTxInfo)
{
    volatile const Eth_TxDescr *pCurrDescr;
    uint32 curBufIdx;
    Eth_Status ethSts;
    uint32 numDescr;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthNode->pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pEthNode->txChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr));
    /* Check ETH channel number */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_CHANNEL(channelId)));
    /* Check if the pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor));
    /* Check if the pTxInfo is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pTxInfo));
#endif /* INPUT_ARG_DETECT */

    numDescr = pEthNode->txChannelInfoPtr[channelId].numOfDescriptor;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)((beginBufIdx < numDescr) && (endBufIdx < numDescr)));
    if(endBufIdx > beginBufIdx)
    {
        /* #Violation: eth_hal_c_REF_3 */
         Assert((boolean)((endBufIdx-beginBufIdx)<numDescr));
    }
    else
    {
        /* #Violation: eth_hal_c_REF_3 */
        Assert((boolean)((beginBufIdx-endBufIdx)<numDescr));
    }

#endif /* INPUT_ARG_DETECT */

    /* Get the pointer to current TX descriptor */
    pCurrDescr = &(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[beginBufIdx]);
    curBufIdx = beginBufIdx;
    pTxInfo->errStatus = 0U;
    ethSts = ETH_STATUS_OK;
    while((curBufIdx != endBufIdx) && (ETH_STATUS_OK == ethSts))
    {
         /* Check if transmission is finished */
        if((uint32)ETH_APPLICATION_OWN == pCurrDescr->TDES3.W.OWN)
        {
            curBufIdx++;
            if(curBufIdx == numDescr)
            {
                curBufIdx = 0U;
            }
            pCurrDescr = &(pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[curBufIdx]);
        }
        else
        {
            ethSts = ETH_STATUS_ERROR;
        }
    }

    /* The last descriptor of the frame */
    if ((curBufIdx == endBufIdx) && (ETH_STATUS_OK == ethSts))
    {
        /* Check if transmission is finished */
        if ((uint32)ETH_APPLICATION_OWN == pCurrDescr->TDES3.W.OWN)
        {
            if (ETH_BIT_ENABLE != pCurrDescr->TDES3.W.ERRSUM)
            {
                /* Check if it is the last descriptor */
                if (ETH_BIT_ENABLE == pCurrDescr->TDES3.W.LD)
                {
                    ethSts = ETH_STATUS_OK;
                    pTxInfo->errStatus = pCurrDescr->TDES3.U;
                    Eth_Hal_GetEgressTimestamp(pEthNode->pEthModule, pCurrDescr, pTxInfo);
                }
                else
                {
                    ethSts = ETH_STATUS_ERROR;
                }
            }
            else
            {
                ethSts = ETH_STATUS_ERROR;
            }
        }
        else
        {
            ethSts = ETH_STATUS_BUSY;
        }
    }

    return ethSts;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_SetCurrentTime(const Eth_NodeHandle *const pEthNode, const Eth_TimeStampType *const pTimeStamp)
{
    Eth_Status ethSts;
    Eth_ReturnState ethState;
    ETH_MODULE *pEthModule;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pTimeStamp is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pTimeStamp));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    pEthModule = pEthNode->pEthModule;
    ethSts = ETH_STATUS_ERROR;
    /* Wait for TSINIT bit is is read as zero to start Timestamp Initialization */
    ethState = Eth_Std_WaitTsinitFree(pEthModule, ETH_TIMERSET_TICKS);
    /* Check if timeout not happend. */
    if(ETH_RETURN_TRUE == ethState)
    {
        /* Update Second, Nanosecond and second higher word */
        pEthModule->MAC_SYSTEM_TIME_SECONDS_UPDATE.U = pTimeStamp->seconds;
        ret = Eth_Register_ReadBack_Check(ret, pTimeStamp->seconds, pEthModule->MAC_SYSTEM_TIME_SECONDS_UPDATE.U);
        pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS = pTimeStamp->nanoseconds;
        ret = Eth_Register_ReadBack_Check(ret, pTimeStamp->nanoseconds, pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS);
        pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = (uint16)pTimeStamp->secondsHi;
        ret = Eth_Register_ReadBack_Check(ret, pTimeStamp->secondsHi, pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR);
        /* Set TSINIT bit to start initializing timer values */
        pEthModule->MAC_TIMESTAMP_CONTROL.B.TSINIT = ETH_BIT_ENABLE;
        /* Wait until TSINIT bit is read as zero. So Initialization is finished */
        ethState = Eth_Std_WaitTsinitFree(pEthModule, ETH_TIMERSET_TICKS);
        /* Check if timeout not happend */
        if(ETH_RETURN_TRUE == ethState)
        {
            ethSts = ETH_STATUS_OK;
        }

        if(FALSE == ret)
        {
            ethSts = ETH_STATUS_ERROR;
        }
    }

    return ethSts;
}

/* #Violation: eth_hal_c_REF_2 */
void Eth_Hal_GetCurrentTime(const Eth_NodeHandle *const pEthNode, Eth_TimeStampType *const pTimeStamp)
{
    const ETH_MODULE *pEthModule;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pTimeStamp is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pTimeStamp));
#endif /* INPUT_ARG_DETECT */
    pEthModule = pEthNode->pEthModule;
    /* Return Higher word second, second and nano second value */
    pTimeStamp->seconds = pEthModule->MAC_SYSTEM_TIME_SECONDS.U;
    pTimeStamp->secondsHi = pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR;
    pTimeStamp->nanoseconds = pEthModule->MAC_SYSTEM_TIME_NANOSECONDS.B.TSSS;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_SetCorrectionTime(Eth_NodeHandle *const pEthNode, const Eth_TimeIntDiffType *const pTimeOffset,
                                     const Eth_RateRatioType *const pRateRatio)
{
    float64 ingressTimeStampDelta;
    float64 originTimeStampDelta;
    float64 freqCompensationValue;
    float64 freqScaleFactor;
    Eth_Status ethSts;
    Eth_ReturnState ethState;
    ETH_MODULE *pEthModule;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pTimeOffset is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pTimeOffset));
    /* Check if the pRateRatio is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pRateRatio));
#endif /* INPUT_ARG_DETECT */
    pEthModule = pEthNode->pEthModule;

    ethSts = ETH_STATUS_ERROR;
    ethState = Eth_Std_SetCorrectTime(
        pEthModule, ((pTimeOffset->sign == TRUE) ? ETH_SYSTIME_CORR_POSITIVE: ETH_SYSTIME_CORR_NEGATIVE),
        pTimeOffset->diff.secondsHi, pTimeOffset->diff.seconds, pTimeOffset->diff.nanoseconds);

    if(ETH_RETURN_TRUE == ethState)
    {
        /* #Violation: eth_hal_c_REF_8 */
        originTimeStampDelta =
            /* #Violation: eth_hal_c_REF_1 */
            (float64)ETH_HAL_STONS_FLOAT64(
                ((float64)pRateRatio->OriginTimeStampDelta.diff.secondsHi * (float64)ETH_TWO_POW_32_VAL) +
                (float64)pRateRatio->OriginTimeStampDelta.diff.seconds) +
            (float64)pRateRatio->OriginTimeStampDelta.diff.nanoseconds;

        /* #Violation: eth_hal_c_REF_8 */
        ingressTimeStampDelta =
            /* #Violation: eth_hal_c_REF_1 */
            (float64)ETH_HAL_STONS_FLOAT64(
                ((float64)pRateRatio->IngressTimeStampDelta.diff.secondsHi * (float64)ETH_TWO_POW_32_VAL) +
                (float64)pRateRatio->IngressTimeStampDelta.diff.seconds) +
            (float64)pRateRatio->IngressTimeStampDelta.diff.nanoseconds;

        /* #Violation: eth_hal_c_REF_1 */
        if(IS_ZERO_FLT(ingressTimeStampDelta))
        {
            freqScaleFactor = (float64)1.0;
        }
        else
        {
            freqScaleFactor = (((float64)2U * originTimeStampDelta) - ingressTimeStampDelta) / ingressTimeStampDelta;
            /* Check the correction factor is greater than zero.
               Zero or Negative value is not a valid correction factor */
            if(freqScaleFactor <= (float64)0.0)
            {
                freqScaleFactor = (float64)1.0;
            }
        }
        freqCompensationValue = pEthNode->prevFreqCompensationValue * freqScaleFactor;
        ethState = Eth_Std_SetCorrectRateRatio(pEthModule, freqCompensationValue);
        /* Check if timeout not happend */
        if(ETH_RETURN_TRUE == ethState)
        {
            pEthNode->prevFreqCompensationValue = freqCompensationValue;
            ethSts = ETH_STATUS_OK;
        }
    }

    return ethSts;
}

/* #Violation: eth_hal_c_REF_2 */
void Eth_Hal_EnableEgressTimeStamp(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 bufIdx)
{
#if(STD_ON == INPUT_ARG_DETECT)
    uint32 numDescr;
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthNode->txChannelInfoPtr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr));
    /* Check ETH channel number */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_CHANNEL(channelId)));
    /* Check if the pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor));

    numDescr = pEthNode->txChannelInfoPtr[channelId].numOfDescriptor;
    /* Check if the phyAddr < 32 */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(bufIdx < numDescr));
#endif /* INPUT_ARG_DETECT */

    /* Set the TTSE Bit of transmit descriptor */
    pEthNode->txChannelInfoPtr[channelId].pTxBaseDescriptor[bufIdx].TDES2.R.TTSE_TMWD = ETH_BIT_ENABLE;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_WriteMii(const Eth_NodeHandle *const pEthNode, uint32 phyAddr, uint32 regAddr, uint16 regVal)
{
    Eth_ReturnState retState;
    Eth_Status ethSts;
    ETH_MODULE *pEthModule;
    boolean ret;
    uint32 macMdioAddr;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the phyAddr < 32 */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(phyAddr < 32U));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    pEthModule = pEthNode->pEthModule;

    ethSts = ETH_STATUS_BUSY;
    retState = Eth_Std_WaitGmiiFree(pEthModule, ETH_MAXTIMEOUT_COUNT);
    if(ETH_RETURN_TRUE == retState)
    {
        /* write data */
        pEthModule->MAC_MDIO_DATA.B.GD = regVal;

        /* 5bit Physical Layer Address, 5bit GMII register or device address, 4bit csr-clock divider, Write, Busy */
        macMdioAddr = (uint32)((phyAddr << 21U) | (regAddr << 16U) | ((uint32)pEthNode->ethMiiCrValue << 8U) |
                      ((uint32)ETH_GOC_WRITE << 2U) | (ETH_INITIATE_RDWR_MDIO << 0U));
        pEthModule->MAC_MDIO_ADDRESS.U = macMdioAddr;
        ret = Eth_Register_ReadBack_Check(ret, macMdioAddr | (ETH_INITIATE_RDWR_MDIO << 0U), pEthModule->MAC_MDIO_ADDRESS.U);

        retState = Eth_Std_WaitGmiiFree(pEthModule, ETH_MAXTIMEOUT_COUNT);
        if(ETH_RETURN_TRUE == retState)
        {
            ethSts = ETH_STATUS_OK;
        }
    }

    if(FALSE == ret)
    {
        ethSts = ETH_STATUS_ERROR;
    }
    return ethSts;
}

/* #Violation: eth_hal_c_REF_2 */
Eth_Status Eth_Hal_ReadMii(const Eth_NodeHandle *const pEthNode, uint32 phyAddr, uint32 regAddr, uint16 *const pRegVal)
{
    Eth_ReturnState ethState;
    Eth_Status ethSts;
    ETH_MODULE *pEthModule;
    boolean ret;
    uint32 macMdioAddr;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check if the pRegVal is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pRegVal));
    /* Check if the phyAddr < 32 */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(phyAddr < 32U));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    pEthModule = pEthNode->pEthModule;

    ethSts = ETH_STATUS_BUSY;
    ethState = Eth_Std_WaitGmiiFree(pEthModule, ETH_MAXTIMEOUT_COUNT);
    if(ETH_RETURN_TRUE == ethState)
    {
        /* 5bit Physical Layer Address, 5bit GMII register or device address, 4bit csr-clock divider, Read, Busy */
        macMdioAddr = (uint32)((phyAddr << 21U) | (regAddr << 16U) | ((uint32)pEthNode->ethMiiCrValue << 8U) |
                      ((uint32)ETH_GOC_READ << 2U) | (ETH_INITIATE_RDWR_MDIO << 0U));
        pEthModule->MAC_MDIO_ADDRESS.U = macMdioAddr;
        ret = Eth_Register_ReadBack_Check(ret, macMdioAddr, pEthModule->MAC_MDIO_ADDRESS.U);
        /* Wait Phy device free, return the data */
        ethState = Eth_Std_WaitGmiiFree(pEthModule, ETH_MAXTIMEOUT_COUNT);
        if(ETH_RETURN_TRUE == ethState)
        {
            /* Get data */
            *pRegVal = (uint16)pEthModule->MAC_MDIO_DATA.B.GD;
            ethSts = ETH_STATUS_OK;
        }
    }

    if(FALSE == ret)
    {
        ethSts = ETH_STATUS_ERROR;
    }
    return ethSts;
}

/* #Violation: eth_hal_c_REF_2 */
boolean Eth_Hal_SetDmaInterrupt(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, const uint32 interruptEn)
{
    /* #Violation: eth_hal_c_REF_4 */
    ETH_DMA_CH_INTERRUPT_ENABLE regDmaChInterruptEnable;
    ETH_MODULE *pEthModule;
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check ETH channel number */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_CHANNEL(channelId)));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    pEthModule = pEthNode->pEthModule;

    /* Set DMA Interrupt */
    regDmaChInterruptEnable.U = pEthModule->DMA_CH[channelId].INTERRUPT_ENABLE.U;
    regDmaChInterruptEnable.U &= ~ETH_ENABLE_ALL_DMA_INTERRUPT;
    regDmaChInterruptEnable.U |= interruptEn;
    pEthModule->DMA_CH[channelId].INTERRUPT_ENABLE.U = regDmaChInterruptEnable.U;
    ret = Eth_Register_ReadBack_Check(ret, regDmaChInterruptEnable.U, pEthModule->DMA_CH[channelId].INTERRUPT_ENABLE.U);

    return ret;
}

/* #Violation: eth_hal_c_REF_2 */
uint32 Eth_Hal_GetDmaInterruptStatus(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId)
{
    uint32 dmaInterruptSts;
    const ETH_MODULE *pEthModule;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check ETH channel number */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_CHANNEL(channelId)));
#endif /* INPUT_ARG_DETECT */
    pEthModule = pEthNode->pEthModule;

    dmaInterruptSts = pEthModule->DMA_CH[channelId].STATUS.U & ETH_ENABLE_ALL_DMA_INTERRUPT;
    return dmaInterruptSts;
}

/* #Violation: eth_hal_c_REF_2 */
void Eth_Hal_ClearDmaInterruptStatus(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 clearMask)
{
    ETH_MODULE *pEthModule;
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pEthNode is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode));
    /* Check if the pEthModule is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEthNode->pEthModule));
    /* Check ETH channel number */
    /* #Violation: eth_hal_c_REF_1 */
    Assert((boolean)(CHECK_ETH_CHANNEL(channelId)));
#endif /* INPUT_ARG_DETECT */
    pEthModule = pEthNode->pEthModule;
    /* Clear all interrupt status */
    pEthModule->DMA_CH[channelId].STATUS.U = clearMask;
}

/* #Violation: eth_hal_c_REF_17 */
void Eth_Hal_FreeRxDescriptor(volatile Eth_RxDescr *const pCurDescr)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* Check if the pCurDescr is null pointer */
    /* #Violation: eth_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pCurDescr));
#endif /* INPUT_ARG_DETECT */
    pCurDescr->RDES3.R.OWN = ETH_BIT_ENABLE;    /* owned by DMA */
}

/* #Violation: eth_hal_c_REF_18 */
#define ETH_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: eth_hal_c_REF_19 */
#include "Eth_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
