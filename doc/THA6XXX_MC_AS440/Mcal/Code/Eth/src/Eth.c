/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Eth.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Ethernet
 *
 *   brief                 : This file contains all functions of Ethernet Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 * 
 *   [SWS_Eth_00005] The Ethernet Driver module shall support pre-compile time, link time and post-build
 *   time configuration. (): Only Post-build support.
 *   [SWS_Eth_00012] The Ethernet Driver module shall provide an XML file that contains the data, which is
 *   required for the SW identification (it shall contain the vendor identification, module ID and software
 *   version information), configuration and integration process. This file should describe vendor specific
 *   configuration parameters as well as it should contain recommended configuration parameter values.:
 *   Eth_THA6206_LFBGA292.arxml is provided.
 *   [SWS_Eth_00125] The MCG shall read the ECU configuration description of the Ethernet Driver module(s).
 *   Ethernet Driver related configuration data is contained in the Ethernet Driver module configuration
 *   description.:EB and epc files.
 *   [SWS_Eth_00126] The MCG shall ensure the consistency of the generated configuration data.
 *   [SWS_Eth_00013 ]The configuration of the Ethernet Driver module shall be calculated at ECU
 *   configuration time. None of the communication parameters shall be calculated at runtime.

 ****************************************************************************************************/
/*
*#Violation Summary
*#Eth_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Eth_c_REF_4:MISRAC2012-Rule-11.4; 
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Eth_c_REF_5:MISRAC2012-Rule-18.4; 
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Eth_c_REF_6:MISRAC2012-Rule-20.10; 
* Justification: Use glue operator to construct the exclusive area function name.
*
*#Eth_c_REF_7:MISRAC2012-Rule-2.2; 
* Justification: This is necessary processing, as it is influenced by macro definitions.
*
*#Eth_c_REF_8:MISRAC2012-Rule-8.9; 
* Justification: The value should be placed in the const data sections to reduce code complexity and stack size.
*
*#Eth_c_REF_9:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Eth_c_REF_10:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*#Eth_c_REF_11:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Eth_c_REF_19:MISRAC2012-Rule-10.5; 
* Justification: Redundant cast is necessary to maintain the software structure and reduce the complexity.
*
*#Eth_c_REF_12:CertC-DCL00-C;
* Justification: Parameter declared refer to AUTOSAR specifications.
*
*#Eth_c_REF_13:CertC-DCL02-C;
* Justification: Company-specific naming conventions  are applied. Developers will not be confused.
*
*#Eth_c_REF_14:CertC-INT36-C;
* Justification: Cast a numeric value to a pointer type for accessing data at a specified 
* memory address.
*
*#Eth_c_REF_15:CertC-PRE00-C; 
* Justification: Function like macros are used to reduce code complexity.
*
*#Eth_c_REF_16:CWE-1071; 
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Eth_c_REF_17:CWE-1071; 
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Eth_c_REF_18:CWE-704; 
* Justification: Cast a numeric value to a pointer type for accessing data at a specified 
* memory address.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* \[SWS_Eth_00119]*/

#include "Eth.h"
/* \[SWS_Eth_00120] [SWS_Eth_00247] The Switch Driver management API's */
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
#include "EthSwt_Eth.h"
#endif /* (ETH_SWT_MANAGEMENT_SUPPORT \== STD_ON) */
#include "EthIf.h"
#include "SchM_Eth.h"
#if (ETH_ENA_MII_API == STD_ON)
#include "EthTrcv.h"
#endif /* (ETH_ENA_MII_API \== STD_ON) */
#if ((ETH_DEV_ERROR_DETECT == STD_ON)||(ETH_SAFETY_ENABLE == STD_ON))
/* [[SWS_Eth_00008] In case development error detection is enabled for the Ethernet Driver module: The
Ethernet Driver module shall check API parameters for validity and report detected errors to the DET*/
#include "Det.h"
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */

#include "Dem.h"


/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
/* \[SWS_Eth_00007] The Ethernet Driver module shall perform a consistency check between code files and
header files based on pre-process-checking the version numbers of related code files and header
files.*/
#if (ETH_VENDOR_ID != ETH_CFG_VENDOR_ID)
#error "Eth.c : Mismatch in Vendor ID"
#endif /* (ETH_VENDOR_ID !\= ETH_CFG_VENDOR_ID) */

#if (ETH_MODULE_ID != ETH_CFG_MODULE_ID)
#error "Eth.c : Mismatch in Module ID"
#endif /* \(ETH_MODULE_ID != ETH_CFG_MODULE_ID) */

#if (ETH_AR_RELEASE_MAJOR_VERSION != ETH_CFG_AR_RELEASE_MAJOR_VERSION)
#error "Eth.c : Mismatch in Release Major Version"
#endif /* (ETH_AR_RELEASE_MAJOR_VERSION !\= ETH_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (ETH_AR_RELEASE_MINOR_VERSION != ETH_CFG_AR_RELEASE_MINOR_VERSION)
#error "Eth.c : Mismatch in Release Minor Version"
#endif /* (ETH_AR_RELEASE_MINOR_VERSION !\= ETH_CFG_AR_RELEASE_MINOR_VERSION) */

#if (ETH_AR_RELEASE_REVISION_VERSION != ETH_CFG_AR_RELEASE_REVISION_VERSION)
#error "Eth.c : Mismatch in Release Revision Version"
#endif /* (ETH_AR_RELEASE_REVISION_VERSION !\= ETH_CFG_AR_RELEASE_REVISION_VERSION) */

#if (ETH_SW_MAJOR_VERSION != ETH_CFG_SW_MAJOR_VERSION)
#error "Eth.c : Mismatch in Software Major Version"
#endif /* (ETH_SW_MAJOR_VERSION !\= ETH_CFG_SW_MAJOR_VERSION) */

#if (ETH_SW_MINOR_VERSION != ETH_CFG_SW_MINOR_VERSION)
#error "Eth.c : Mismatch in Software Minor Version"
#endif /* (ETH_SW_MINOR_VERSION !\= ETH_CFG_SW_MINOR_VERSION) */

#if (ETH_SW_PATCH_VERSION != ETH_CFG_SW_PATCH_VERSION)
#error "Eth.c : Mismatch in Software Patch Version"
#endif /* \(ETH_SW_PATCH_VERSION != ETH_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define ETH_MAC_ADDR_LEN                  (6U) /* in bytes */
#define ETH_FRAMEHEADER_LENGTH            (14U)
#define ETH_FRAMECHKSUM_LENGTH            (4U)

/* #Violation: Eth_c_REF_11*/
#define ETH_DMA_CH_STAT_TI_SET            (0x00000001U)
/* #Violation: Eth_c_REF_11*/
#define ETH_DMA_CH_STAT_TI_RESET          (0x00000001U)
/* #Violation: Eth_c_REF_11*/
#define ETH_DMA_CH_STAT_RI_SET            (0x00000040U)
/* #Violation: Eth_c_REF_11*/
#define ETH_DMA_CH_STAT_RI_RESET          (0x00000040U)
/* #Violation: Eth_c_REF_11*/
#define ETH_DMA_CH_STAT_RBU_SET           (0x00000080U)
/* #Violation: Eth_c_REF_11*/
#define ETH_ERROR_ES_BIT                  (0x8000U)

/* #Violation: Eth_c_REF_11*/
#define ETH_DMA_CH_STAT_RBU_ERI_AIE_RESET (0x00004880U)
/* #Violation: Eth_c_REF_11*/
#define ETH_DMA_CH_STAT_NIS_RESET         (0x00008000U)
/* #Violation: Eth_c_REF_11*/
#define ETH_DMA_CH_STAT_CLR_ALL           (0x0000FFC7U)
#define ETH_BUFIDX_MASK                   (0x00001FFFU)
#if (ETH_OFFLOAD_CHECKSUM == STD_ON)
#define ETH_IPV4_ICMP_PROTOCOL (0x01U)
#define ETH_IPV4_FRAMETYPE     (0x0800U)
#define ETH_FRAME_ICMP_CRC_POS (36U)
#define ETH_FRAME_IPV4TYPE_POS (23U)
/* #Violation: Eth_c_REF_11*/
#define ETH_FIFOIDX_POS             (13U)

/* Maximum channels/ FIFOs supported in this device */
/* #Violation: Eth_c_REF_11*/
#define ETH_MAXCHLS_SUPPORTED         (4U)
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
/* Length of EtherType field */
#define ETH_ETHERTYPE_LEN             (2U)
#define ETH_FRAME_TYPE_MSB_POS        (12U)
#define ETH_DMA_TX_DESC_PAC_LEN_MASK (0x00007FFFU)

#endif
#endif /* (ETH_OFFLOAD_CHECKSUM \== STD_ON) */
/* #Violation: Eth_c_REF_6 */
/* #Violation: Eth_c_REF_15 */
#define ETH_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_##Exclusive_Area()
/* #Violation: Eth_c_REF_6 */
/* #Violation: Eth_c_REF_15 */
#define ETH_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_##Exclusive_Area()
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, BufIdx) \
    ((Eth_TxdescTxConfirmType)(Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]             \
         .ControllerStatePtr->Node.txDescrInfoPtr[DmaIdx][BufIdx]        \
         .txdescTxConfirm))
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_SET_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, BufIdx, Value) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]                        \
         .ControllerStatePtr->Node.txDescrInfoPtr[DmaIdx][(BufIdx)]                   \
         .txdescTxConfirm = ((uint32)(Value)))


#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)

#define ETH_BUF_IDX_SWT_DATA_PTR(CtrlIdx, CoreId, DmaIdx, BufIdx) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]             \
         .ControllerStatePtr->Node.txDescrInfoPtr[DmaIdx][BufIdx]        \
         .swtTxDataPtr)
#define ETH_BUF_IDX_SWT_TXLEN(CtrlIdx, CoreId, DmaIdx, BufIdx) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]             \
         .ControllerStatePtr->Node.txDescrInfoPtr[DmaIdx][BufIdx]        \
         .swtTxLength)


#define ETH_BUF_IDX_SWT_RXDATA_PTR(CtrlIdx, CoreId, DmaIdx, BufIdx) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]             \
         .ControllerStatePtr->Node.rxDescrInfoPtr[DmaIdx][BufIdx]        \
         .swtRxDataPtr)

#define ETH_BUF_IDX_SWT_RXLEN(CtrlIdx, CoreId, DmaIdx, BufIdx) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]             \
         .ControllerStatePtr->Node.rxDescrInfoPtr[DmaIdx][BufIdx]        \
         .swtRxLength)
#define ETH_BUF_IDX_SWT_MG_ONLY(CtrlIdx, CoreId, DmaIdx, BufIdx) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]             \
         .ControllerStatePtr->Node.rxDescrInfoPtr[DmaIdx][BufIdx]        \
         .swtMgmtFrameOnly)


#endif/*(ETH_SWT_MANAGEMENT_SUPPORT \== STD_ON)*/

/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_DRIVER_STATE(CtrlIdx, CoreId) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr->DriverState)
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_CONTROLLER_STATE(CtrlIdx, CoreId) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr->CntrlState)
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_NODE_ADDR(CtrlIdx, CoreId) \
    (&(Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr->Node))
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_NODE(CtrlIdx, CoreId) ((Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr->Node))
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_RX_INFO(CtrlIdx, CoreId, DmaIdx) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr->Node.rxChannelInfoPtr[DmaIdx].rxInfo)
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_TX_INFO(CtrlIdx, CoreId, DmaIdx) \
    (Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr->Node.txChannelInfoPtr[DmaIdx].txInfo)
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_RX_TMSTMP_DATAPTR(CtrlIdx, CoreId, DmaIdx) \
    ((Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr->RxTmStmpDataPtr[DmaIdx]))
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_RXIRQ_IS_ENABLED(CtrlIdx, CoreId) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthCtrlConfigPtr[CtrlIdx].EthSdkCtrlConfigPtr->rxIrqIsEnabled)
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_TXIRQ_IS_ENABLED(CtrlIdx, CoreId) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthCtrlConfigPtr[CtrlIdx].EthSdkCtrlConfigPtr->txIrqIsEnabled)
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_GET_CHID_FROM_FIFO(CtrlIdx, CoreId, FifoIdx) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthCtrlConfigPtr[CtrlIdx].EthTxFifoChnlMapPtr[FifoIdx])
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_GET_CHID_FROM_RXFIFO(CtrlIdx, CoreId, FifoIdx) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthCtrlConfigPtr[CtrlIdx].EthRxFifoChnlMapPtr[FifoIdx])

/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_GET_MAX_TXDMA_NUM(CtrlIdx, CoreId) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthCtrlConfigPtr[CtrlIdx].EthSdkCtrlConfigPtr->ethNumTxChnls)
/* #Violation: Eth_c_REF_9 */
/* #Violation: Eth_c_REF_15 */
#define ETH_GET_MAX_RXDMA_NUM(CtrlIdx, CoreId) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthCtrlConfigPtr[CtrlIdx].EthSdkCtrlConfigPtr->ethNumRxChnls)

/* #Violation: Eth_c_REF_9*/
/* #Violation: Eth_c_REF_15 */
#define ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, DmaIdx) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]             \
         ->EthCtrlConfigPtr[CtrlIdx]                     \
         .EthSdkCtrlConfigPtr->dma.txChannel[DmaIdx]   \
         .numOfTxBuffers)

/* #Violation: Eth_c_REF_9*/
/* #Violation: Eth_c_REF_15 */
#define ETH_GET_MAX_RX_DESC_NUM(CtrlIdx, CoreId, DmaIdx) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]             \
         ->EthCtrlConfigPtr[CtrlIdx]                     \
         .EthSdkCtrlConfigPtr->dma.rxChannel[DmaIdx]   \
         .numOfRxBuffers)

/* #Violation: Eth_c_REF_9*/
/* #Violation: Eth_c_REF_15 */
#define ETH_GET_CHID_FROM_PRIORITY(CtrlIdx, CoreId, Priority) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthCtrlConfigPtr[CtrlIdx].EthTxPrioFifoMapPtr[Priority])
/* #Violation: Eth_c_REF_15 */
/* #Violation: Eth_c_REF_11*/
/* #Violation: Eth_c_REF_9*/
#define ETH_DEM(CtrlIdx, CoreId) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthCtrlConfigPtr[CtrlIdx].EthDemPtr)
/* #Violation: Eth_c_REF_15 */
/* #Violation: Eth_c_REF_9*/
#define ETH_CTRL_NUM(CoreId) \
    (Eth_ConfigPtr->EthCoreConfigPtr[CoreId]->EthMaxControllers)


/****************************************************************************************************
**                          Private Type Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"

static P2CONST(Eth_ConfigType, AUTOMATIC, ETH_APPL_CONST) Eth_ConfigPtr;

/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/


/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

/* \[SWS_Eth_00218] */
/* The descriptor addresses must be aligned to configured bus width */


#if (ETH_FIFO0_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO0RxBuffer[ETH_FIFO0_CTRL0_RXBUF_SIZE];
ALIGNED(64)  uint8 Eth_FIFO0RxBuffer[ETH_FIFO0_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO1RxBuffer[ETH_FIFO1_CTRL0_RXBUF_SIZE];
ALIGNED(64)  uint8 Eth_FIFO1RxBuffer[ETH_FIFO1_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64) uint8 Eth_FIFO2RxBuffer[ETH_FIFO2_CTRL0_RXBUF_SIZE];
ALIGNED(64) uint8 Eth_FIFO2RxBuffer[ETH_FIFO2_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO3RxBuffer[ETH_FIFO3_CTRL0_RXBUF_SIZE];
ALIGNED(64)  uint8 Eth_FIFO3RxBuffer[ETH_FIFO3_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_SIZE \> 0)*/

#if (ETH_FIFO0_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO0TxBuffer[ETH_FIFO0_CTRL0_TXBUF_SIZE];
ALIGNED(64)  uint8 Eth_FIFO0TxBuffer[ETH_FIFO0_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_SIZE \> 0)*/
#if (ETH_FIFO1_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO1TxBuffer[ETH_FIFO1_CTRL0_TXBUF_SIZE];
ALIGNED(64)  uint8 Eth_FIFO1TxBuffer[ETH_FIFO1_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_SIZE \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO2TxBuffer[ETH_FIFO2_CTRL0_TXBUF_SIZE];
ALIGNED(64)  uint8 Eth_FIFO2TxBuffer[ETH_FIFO2_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_SIZE \> 0)*/
#if (ETH_FIFO3_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO3TxBuffer[ETH_FIFO3_CTRL0_TXBUF_SIZE];
ALIGNED(64)  uint8 Eth_FIFO3TxBuffer[ETH_FIFO3_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_SIZE \> 0)*/



#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx0descr[ETH_FIFO0_CTRL0_TXBUF_COUNT];
ALIGNED(64)  Eth_TxDescr Eth_Tx0descr[ETH_FIFO0_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx1descr[ETH_FIFO1_CTRL0_TXBUF_COUNT];
ALIGNED(64)  Eth_TxDescr Eth_Tx1descr[ETH_FIFO1_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx2descr[ETH_FIFO2_CTRL0_TXBUF_COUNT];
ALIGNED(64)  Eth_TxDescr Eth_Tx2descr[ETH_FIFO2_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx3descr[ETH_FIFO3_CTRL0_TXBUF_COUNT];
ALIGNED(64)  Eth_TxDescr Eth_Tx3descr[ETH_FIFO3_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx0descr[ETH_FIFO0_CTRL0_RXBUF_COUNT];
ALIGNED(64)  Eth_RxDescr Eth_Rx0descr[ETH_FIFO0_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx1descr[ETH_FIFO1_CTRL0_RXBUF_COUNT];
ALIGNED(64)  Eth_RxDescr Eth_Rx1descr[ETH_FIFO1_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx2descr[ETH_FIFO2_CTRL0_RXBUF_COUNT];
ALIGNED(64)  Eth_RxDescr Eth_Rx2descr[ETH_FIFO2_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx3descr[ETH_FIFO3_CTRL0_RXBUF_COUNT];
ALIGNED(64)  Eth_RxDescr Eth_Rx3descr[ETH_FIFO3_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/
/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"



/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
#if (ETH_MAX_CTRL_TO_CORE0 > 0)
static Eth_StatusType Eth_StatusCore0[ETH_MAX_CTRL_TO_CORE0];
static Eth_ControllerStateType Eth_ControllerStateCtrl0;

#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx0Ch[ETH_FIFO0_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/


#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx1Ch[ETH_FIFO1_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx2Ch[ETH_FIFO2_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx3Ch[ETH_FIFO3_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/


#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx0Ch[ETH_FIFO0_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx1Ch[ETH_FIFO1_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx2Ch[ETH_FIFO2_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx3Ch[ETH_FIFO3_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/
/* #Violation: Eth_c_REF_8*/
static Eth_RxChannelInfo    Eth_FifoRxInfo[ETH_CTRL0_RXFIFO_CFGD];
/* #Violation: Eth_c_REF_8*/
static Eth_TxChannelInfo    Eth_FifoTxInfo[ETH_CTRL0_TXFIFO_CFGD];



#endif /*(ETH_MAX_CTRL_TO_CORE0 \> 0)*/

/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"


/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

#if (ETH_MAX_CTRL_TO_CORE1 > 0)
static Eth_StatusType Eth_StatusCore1[ETH_MAX_CTRL_TO_CORE1];
static Eth_ControllerStateType Eth_ControllerStateCtrl0;

#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx0Ch[ETH_FIFO0_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/


#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx1Ch[ETH_FIFO1_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx2Ch[ETH_FIFO2_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx3Ch[ETH_FIFO3_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/


#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx0Ch[ETH_FIFO0_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx1Ch[ETH_FIFO1_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx2Ch[ETH_FIFO2_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx3Ch[ETH_FIFO3_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/

static Eth_RxChannelInfo    Eth_FifoRxInfo[ETH_CTRL0_RXFIFO_CFGD];

static Eth_TxChannelInfo    Eth_FifoTxInfo[ETH_CTRL0_TXFIFO_CFGD];
#endif /*(ETH_MAX_CTRL_TO_CORE1 \> 0)*/


/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"


/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
#if (ETH_MAX_CTRL_TO_CORE2 > 0)
static Eth_ControllerStateType Eth_ControllerStateCtrl0;
static Eth_StatusType Eth_StatusCore2[ETH_MAX_CTRL_TO_CORE2];

#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx0Ch[ETH_FIFO0_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/


#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx1Ch[ETH_FIFO1_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx2Ch[ETH_FIFO2_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx3Ch[ETH_FIFO3_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/


#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx0Ch[ETH_FIFO0_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx1Ch[ETH_FIFO1_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx2Ch[ETH_FIFO2_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx3Ch[ETH_FIFO3_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/

static Eth_RxChannelInfo    Eth_FifoRxInfo[ETH_CTRL0_RXFIFO_CFGD];

static Eth_TxChannelInfo    Eth_FifoTxInfo[ETH_CTRL0_TXFIFO_CFGD];
#endif /*(ETH_MAX_CTRL_TO_CORE2 \> 0)*/

/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
#if (ETH_MAX_CTRL_TO_CORE3 > 0)
static Eth_ControllerStateType Eth_ControllerStateCtrl0;
static Eth_StatusType Eth_StatusCore3[ETH_MAX_CTRL_TO_CORE3];

#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx0Ch[ETH_FIFO0_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/


#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx1Ch[ETH_FIFO1_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx2Ch[ETH_FIFO2_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
static Eth_TxDescrInfo Eth_Tx3Ch[ETH_FIFO3_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/


#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx0Ch[ETH_FIFO0_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx1Ch[ETH_FIFO1_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx2Ch[ETH_FIFO2_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
static Eth_RxDescrInfo Eth_Rx3Ch[ETH_FIFO3_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/

static Eth_RxChannelInfo    Eth_FifoRxInfo[ETH_CTRL0_RXFIFO_CFGD];

static Eth_TxChannelInfo    Eth_FifoTxInfo[ETH_CTRL0_TXFIFO_CFGD];
#endif /*(ETH_MAX_CTRL_TO_CORE3 \> 0)*/

/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"


/* Array contains pointers to Controller status of the core */
static Eth_StatusType *const Eth_CoreChannelStatusPtr[MCAL_NUMBER_OF_CORES] = 
{
#if (MCAL_NUMBER_OF_CORES > 0U)
#if (ETH_MAX_CTRL_TO_CORE0 > 0U)
    Eth_StatusCore0,
#else
    NULL_PTR,    
#endif /*(ETH_MAX_CTRL_TO_CORE0 \> 0U)*/
#endif /*(MCAL_NUMBER_OF_CORES \> 0U)*/

#if (MCAL_NUMBER_OF_CORES > 1U)

#if (ETH_MAX_CTRL_TO_CORE1 > 0U)
    Eth_StatusCore1,
#else
    NULL_PTR,        
#endif /*(ETH_MAX_CTRL_TO_CORE1 \> 0U)*/
#endif /*(MCAL_NUMBER_OF_CORES \> 1U)*/
#if (MCAL_NUMBER_OF_CORES > 2U)

#if (ETH_MAX_CTRL_TO_CORE2 > 0U)
    Eth_StatusCore2,
#else
    NULL_PTR,        
#endif /*(ETH_MAX_CTRL_TO_CORE2 \> 0U)*/
#endif /*(MCAL_NUMBER_OF_CORES \> 2U)*/
#if (MCAL_NUMBER_OF_CORES > 3U)

#if (ETH_MAX_CTRL_TO_CORE3 > 0U)
    Eth_StatusCore3,
#else
    NULL_PTR,        
#endif /*(ETH_MAX_CTRL_TO_CORE3 \> 0U)*/
#endif /*(MCAL_NUMBER_OF_CORES \> 3U)*/

};
/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"



#if (ETH_MAX_CTRL_TO_CORE0 > 0U)
/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
/* #Violation: Eth_c_REF_8*/
static  Eth_TxDescrInfo * Eth_TxChannelPtr[ETH_CTRL0_TXFIFO_CFGD] = 
{
#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx0Ch,
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx1Ch,
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx2Ch,
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx3Ch,
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/
};


/* #Violation: Eth_c_REF_8*/
static Eth_RxDescrInfo * Eth_RxChannelPtr[ETH_CTRL0_RXFIFO_CFGD] = 
{
#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx0Ch,
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx1Ch,
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx2Ch,
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx3Ch,
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/

};

/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
#endif /*(ETH_MAX_CTRL_TO_CORE0 \> 0)*/

#if (ETH_MAX_CTRL_TO_CORE1 > 0)
/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
#include "Eth_MemMap.h"

static  Eth_TxDescrInfo * Eth_TxChannelPtr[ETH_CTRL0_TXFIFO_CFGD] = 
{
#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx0Ch,
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx1Ch,
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx2Ch,
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx3Ch,
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/
};


static Eth_RxDescrInfo * Eth_RxChannelPtr[ETH_CTRL0_RXFIFO_CFGD] = 
{
#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx0Ch,
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx1Ch,
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx2Ch,
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx3Ch,
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/

};

/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
#endif /*(ETH_MAX_CTRL_TO_CORE1 \> 0)*/

#if (ETH_MAX_CTRL_TO_CORE2 > 0)
/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

static  Eth_TxDescrInfo * Eth_TxChannelPtr[ETH_CTRL0_TXFIFO_CFGD] = 
{
#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx0Ch,
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx1Ch,
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx2Ch,
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx3Ch,
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/
};


static Eth_RxDescrInfo * Eth_RxChannelPtr[ETH_CTRL0_RXFIFO_CFGD] = 
{
#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx0Ch,
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx1Ch,
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx2Ch,
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx3Ch,
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/

};

/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
#endif /*(ETH_MAX_CTRL_TO_CORE2 \> 0)*/

#if (ETH_MAX_CTRL_TO_CORE3 > 0)
/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

static  Eth_TxDescrInfo * Eth_TxChannelPtr[ETH_CTRL0_TXFIFO_CFGD] = 
{
#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx0Ch,
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx1Ch,
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx2Ch,
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
    Eth_Tx3Ch,
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/
};


static Eth_RxDescrInfo * Eth_RxChannelPtr[ETH_CTRL0_RXFIFO_CFGD] = 
{
#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx0Ch,
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx1Ch,
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx2Ch,
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
    Eth_Rx3Ch,
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/

};
/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
#endif /*(ETH_MAX_CTRL_TO_CORE3 \> 0)*/
/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

/* Variable to store starting address of Buffertable, Tx/Rx descriptors and
   Tx/Rx Buffers. (Controller0) */
/* #Violation: Eth_c_REF_7*/
/* #Violation: Eth_c_REF_8*/
static Eth_ControllerStateType *const Eth_ControllerStatePtr[ETH_MAX_CTRLS] = 
{
   &Eth_ControllerStateCtrl0,
};
/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/


#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
LOCAL_INLINE Std_ReturnType ETH_lChkSwtRxFrmParam(
            const uint16 RxActualLen, const uint16 RxModifiedLen,
            const uint8* const EthTypeAddrPtr, const uint8* const BufferPtr);

static BufReq_ReturnType ETH_lSwtAdaptPrepFrame(
                                             const uint8 CtrlIdx,
                                             const uint8 PrioMapIdx,
                                             Eth_BufIdxType* const BufIdxPtr,
                                             uint8** const BufPtr,
                                             uint16* const LenBytePtr,
                                            Mcal_CoreType  CoreId);
#endif /* (ETH_SWT_MANAGEMENT_SUPPORT \== STD_ON) */
#if (ETH_DEV_ERROR_DETECT == STD_ON)

static FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_CheckTransParam
(
    uint8           CtrlIdx, 
    uint8           PriorityId,
    Mcal_CoreType   CoreId,
    uint8           BufferIdx,
    /* #Violation: Eth_c_REF_12 */
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr
);
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON)*/
static FUNC(void, ETH_PRIVATE_CODE) Eth_HalfDuplexDemReportErr
(
    Mcal_CoreType CoreId, 
    uint8 CtrlIdx, 
    Eth_StatusType const *Eth_StatusPtr
);

static FUNC(void, ETH_PRIVATE_CODE) Eth_ControllerNotInitProcess(Mcal_CoreType CoreId, uint8 CtrlIdx);
static FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ControllerHadInitProcess(Mcal_CoreType CoreId, uint8 CtrlIdx, Eth_ModeType CtrlMode);

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#if (ETH_ENA_TX_INT == STD_ON)

extern FUNC(void, ETH_FAST_CODE) Eth_TX_ISRHandler(uint8 CtrlIdx, uint8 ChannelId);

#endif /* (ETH_ENA_TX_INT \== STD_ON) */
#if (ETH_ENA_RX_INT == STD_ON)

extern FUNC(void, ETH_FAST_CODE) Eth_RX_ISRHandler(uint8 CtrlIdx, uint8 ChannelId);

#endif /* (ETH_ENA_RX_INT \== STD_ON) */
/* #Violation: Eth_c_REF_11*/
#define ETH_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"
#if (ETH_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_DetCheck
(
    uint8 CtrlIdx, 
    uint8 Sid, 
    Mcal_CoreType CoreId
)
{
    Std_ReturnType  RetVal;
    Eth_StatusType const* Eth_StatusPtr;
    Eth_StatusPtr = Eth_CoreChannelStatusPtr[CoreId];
    RetVal = E_NOT_OK;
    if (NULL_PTR == Eth_StatusPtr)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, Sid, ETH_E_CORE_MISMATCH);
    }
    /*  ETH_E_INV_CTRL_IDX  \[SWS_Eth_00061] [SWS_Eth_00049] [SWS_Eth_00055] [SWS_Eth_00141]
    \[SWS_Eth_00165][SWS_Eth_00229][SWS_Eth_00236][SWS_Eth_00183][SWS_Eth_00188][SWS_Eth_00192]
    \[SWS_Eth_00197][SWS_Eth_00202][SWS_Eth_00202][SWS_Eth_00207][SWS_Eth_00082][SWS_Eth_00091]
    \[SWS_Eth_00098][SWS_Eth_00104]*/
    else if (CtrlIdx != MCAL_ZERO)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, Sid, ETH_E_INV_CTRL_IDX);
    }
    /*  ETH_E_UNINIT SWS_Eth_00060 \[SWS_Eth_00048 [SWS_Eth_00051][SWS_Eth_00054]
    \[SWS_Eth_00140][SWS_Eth_00143][SWS_Eth_00057][SWS_Eth_00164][SWS_Eth_00167][SWS_Eth_00228]
    \[SWS_Eth_00232][SWS_Eth_00235][SWS_Eth_00239][SWS_Eth_00185][SWS_Eth_00182][SWS_Eth_00187]
    \[SWS_Eth_00189][SWS_Eth_00191][SWS_Eth_00194][SWS_Eth_00196][SWS_Eth_00199][SWS_Eth_00201]
    \[SWS_Eth_00204][SWS_Eth_00201][SWS_Eth_00204][SWS_Eth_00206][SWS_Eth_00209][SWS_Eth_00081]
    \[SWS_Eth_00086][SWS_Eth_00090][SWS_Eth_00094][SWS_Eth_00099][SWS_Eth_00097][SWS_Eth_00103]
    \[SWS_Eth_00105] */
    else if (NULL_PTR == Eth_ConfigPtr)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, Sid, ETH_E_UNINIT);
    }
    /* \[SWS_Eth_00132] [SWS_Eth_00129] [SWS_Eth_00134] */
    /* #Violation: Eth_c_REF_9*/
    else if (ETH_CONTROLLER_STATE(CtrlIdx, CoreId) < ETH_CNTRL_INITIALIZED_ACTIVE)
    {
        if (ETH_SID_GETCONTROLLERMODE == Sid)
        {
            RetVal = E_OK;
        }
        else
        {
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, Sid, ETH_E_INV_MODE);
        }
    }
    else
    {
        RetVal = E_OK;
    }
    return RetVal;
}

#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Eth_ReciveProcess
 *
 *   Service ID              :
 *
 *   Description             : This function process recive .
 *
 *   Parameters in           :uint8 CtrlIdx : ctronler index
 *                            Mcal_CoreType CoreId : Core index
 *                            uint8  DmaIdx: Dma channel hw index.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : none.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
static Eth_RxStatusType Eth_ReciveProcess
(
    uint8 CtrlIdx, 
    Mcal_CoreType CoreId, 
    uint8 DmaIdx
)
{
    /* #Violation: Eth_c_REF_12 */
    uint8           *BufPtr;
    uint16           PackageLength;
    Eth_FrameType    FrameType;
    boolean          IsBroadcast;
    uint32           Index;
    uint32           PtrIndex;
    uint8  const    *BaseOff;
    uint8            ReceiveDescIndex;
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
    uint16 RxBufClrStrtIdx;
    Std_ReturnType RetVal;
#endif
    Eth_RxStatusType RxStatus;
    Eth_RxStatusType RetRxStatus;
    RetRxStatus = ETH_NOT_RECEIVED;
    RxStatus = ETH_RECEIVED;
    for (ReceiveDescIndex = MCAL_ZERO;
         /* #Violation: Eth_c_REF_9*/
         ((ReceiveDescIndex < ETH_GET_MAX_RX_DESC_NUM(CtrlIdx, CoreId, DmaIdx))&&(ETH_NOT_RECEIVED != RxStatus));
         ReceiveDescIndex++)
    {
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
        RxBufClrStrtIdx = ETH_NODE_ADDR(CtrlIdx, CoreId)->rxChannelInfoPtr[DmaIdx].descIndex;
#endif
        /* #Violation: Eth_c_REF_19*/
        RxStatus = Eth_Hal_Receive(
            /* #Violation: Eth_c_REF_9*/
            ETH_NODE_ADDR(CtrlIdx, CoreId),
            /* #Violation: Eth_c_REF_19*/
            (Eth_DmaChannel)DmaIdx,
            &BufPtr,
            &PackageLength,
            /* #Violation: Eth_c_REF_9*/
            &ETH_RX_INFO(CtrlIdx, CoreId, DmaIdx));

        if ((ETH_NOT_RECEIVED != RxStatus))
        {
            RetRxStatus = ETH_RECEIVED;
            /* Switch management support Enabled*/
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
            ETH_BUF_IDX_SWT_RXDATA_PTR(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx) =
                &(BufPtr[ETH_FRAME_TYPE_MSB_POS]);
            ETH_BUF_IDX_SWT_RXLEN(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx) = PackageLength;
            /* Call EthSwt_EthRxProcessFrame API to process Rx frame*/
            RetVal = EthSwt_EthRxProcessFrame(
                CtrlIdx,
                (((uint32)DmaIdx << ETH_FIFOIDX_POS) | RxBufClrStrtIdx),
                &ETH_BUF_IDX_SWT_RXDATA_PTR(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx),
                &ETH_BUF_IDX_SWT_RXLEN(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx),
                &ETH_BUF_IDX_SWT_MG_ONLY(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx));

            /* Is previous API call executed successfully?*/
            if (RetVal == E_OK)
            {
                /* Check the validity of the parameters modified by the EthSwt driver API*/
                RetVal = ETH_lChkSwtRxFrmParam(
                    PackageLength,
                    ETH_BUF_IDX_SWT_RXLEN(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx),
                    ETH_BUF_IDX_SWT_RXDATA_PTR(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx),
                    BufPtr);
            }

            /* Is any error occured due to previous check?*/
            if (RetVal == E_OK)
            {
                /* if the frame is for only Management purpose, do not invoke the
                    Rx indication function */
                /*  if the received frame is for only Management purpose*/
                if (ETH_BUF_IDX_SWT_MG_ONLY(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx) == FALSE)
#endif /* (ETH_SWT_MANAGEMENT_SUPPORT \== STD_ON) */
                {
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
                    /* Adjust the address offset with the management info length */
                    BufPtr =
                        (uint8
                             *)((uint32)BufPtr + (uint32)(PackageLength - ETH_BUF_IDX_SWT_RXLEN(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx)));

                    PackageLength = ETH_BUF_IDX_SWT_RXLEN(CtrlIdx, CoreId, DmaIdx, RxBufClrStrtIdx);
#endif /* (ETH_SWT_MANAGEMENT_SUPPORT \== STD_ON) */
                    Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                        .ControllerStatePtr->RxTmStmpDataPtr[DmaIdx] =
                        (Eth_DataType *)&BufPtr[ETH_FRAMEHEADER_LENGTH];
                    BaseOff = BufPtr;
                    PtrIndex = 0U;
                    IsBroadcast = (boolean)TRUE;
                    /* \[SWS_Eth_00153]When calling the callback function EthIf_RxIndication broadcast
                    frames shall be indicated to the Ethernet Interface (see [6])*/
                    for (Index = MCAL_ZERO; Index < ETH_MAC_ADDR_LEN; Index++)
                    {
                        if (0xFFU != BaseOff[PtrIndex])
                        {
                            IsBroadcast = (boolean)FALSE;
                        }
                        PtrIndex++;
                    }
                    PtrIndex += ETH_MAC_ADDR_LEN;
                    /* point to Frame Type */
                    FrameType =
                        (Eth_FrameType)(((uint32)BaseOff[PtrIndex] << 8U) | ((uint32)BaseOff[PtrIndex + 1U]));
                    /* exclude header and CRC */
                    PackageLength -= (ETH_FRAMEHEADER_LENGTH + ETH_FRAMECHKSUM_LENGTH);
                    /* point to pay load */
                    PtrIndex += 2U;
                    /* The function shall be callable on interrupt level */
                    /* \[SWS_Eth_00244] Ethernet SW Driver shall call EthIf_RxIndication to indicate a
                    successful reception either from the Interrupt routine (in interrupt mode) or from
                    the Eth_Receive routine in polling mode (please refer to SWC_ETH_0096)
                    [SWS_Eth_00096] The function shall read the next frame from the receive buffers.
                    The function passes the received frame to the Ethernet interface using the
                    callback function EthIf_RxIndication and indicates if there are more frames in the
                    receive buffers.*/
                    EthIf_RxIndication(
                        CtrlIdx,
                        FrameType,
                        IsBroadcast,
                        &(BaseOff[PtrIndex + ETH_MAC_ADDR_LEN]),
                        &(BaseOff[PtrIndex]),
                        PackageLength);

                    Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                        .ControllerStatePtr->RxTmStmpDataPtr[DmaIdx] = NULL_PTR;
                }
                /* Switch management support Enabled*/
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
                /* Invoke switch driver Rx indication API call */
                (void)EthSwt_EthRxFinishedIndication(
                    CtrlIdx, (((uint32)DmaIdx << ETH_FIFOIDX_POS) | RxBufClrStrtIdx));
            }
#endif
        }
        /* #Violation: Eth_c_REF_9*/
        if (NULL_PTR != ETH_RX_INFO(CtrlIdx, CoreId, DmaIdx).pCurDescr)
        {
            /* #Violation: Eth_c_REF_9*/
            Eth_Hal_FreeRxDescriptor(ETH_RX_INFO(CtrlIdx, CoreId, DmaIdx).pCurDescr);
        }
    }
    /* has valid frame in next descriptor */ 
    if(ETH_RECEIVED_MORE_DATA_AVAILABLE == RxStatus)
    {
        RetRxStatus = ETH_RECEIVED_MORE_DATA_AVAILABLE;
    }
    return RetRxStatus;
}


/****************************************************************************************************
 *   Function Name           : Eth_DemReportAllErrorPass
 *
 *   Service ID              :
 *
 *   Description             : This function report dem pass.
 *
 *   Parameters in           :

 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : none.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
static void Eth_DemReportAllErrorPass(uint8 CtrlIdx,Mcal_CoreType CoreId)
{
    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemFramesLost)
    {
        /* #Violation: Eth_c_REF_9*/
        Dem_SetEventStatus(ETH_DEM(CtrlIdx, CoreId)->EthDemFramesLost, DEM_EVENT_STATUS_PREPASSED);
    }

    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemCRC)
    {
        /* #Violation: Eth_c_REF_9*/
        Dem_SetEventStatus(ETH_DEM(CtrlIdx, CoreId)->EthDemCRC, DEM_EVENT_STATUS_PREPASSED);
    }
    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemUndersize)
    {
        /* #Violation: Eth_c_REF_9*/
        Dem_SetEventStatus(ETH_DEM(CtrlIdx, CoreId)->EthDemUndersize, DEM_EVENT_STATUS_PREPASSED);
    }

    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemOversize)
    {
        /* #Violation: Eth_c_REF_9*/
        Dem_SetEventStatus(ETH_DEM(CtrlIdx, CoreId)->EthDemOversize, DEM_EVENT_STATUS_PREPASSED);
    }

    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemAlignment)
    {
        /* #Violation: Eth_c_REF_9*/
        Dem_SetEventStatus(ETH_DEM(CtrlIdx, CoreId)->EthDemAlignment, DEM_EVENT_STATUS_PREPASSED);
    }

    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemSingleCollision)
    {
        /* #Violation: Eth_c_REF_9*/
        Dem_SetEventStatus(ETH_DEM(CtrlIdx, CoreId)->EthDemSingleCollision, DEM_EVENT_STATUS_PREPASSED);
    }

    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemMultipleCollision)
    {
        Dem_SetEventStatus(
            /* #Violation: Eth_c_REF_9*/
            ETH_DEM(CtrlIdx, CoreId)->EthDemMultipleCollision, DEM_EVENT_STATUS_PREPASSED);
    }
    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemLateCollision)
    {
        /* #Violation: Eth_c_REF_9*/
        Dem_SetEventStatus(ETH_DEM(CtrlIdx, CoreId)->EthDemLateCollision, DEM_EVENT_STATUS_PREPASSED);
    }
}

/****************************************************************************************************
 *   Function Name           : Eth_DemReportError
 *
 *   Service ID              :
 *
 *   Description             : This function report dem error (if new loss frame is detected).
 *
 *   Parameters in           :uint32 *RecordCnt, record count
 *                            uint32 CurrentCnt, crrent count read from register
 *                            Dem_EventIdType EventId
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : none.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
static void Eth_DemReportError(uint32 *RecordCnt,uint32 CurrentCnt,Dem_EventIdType EventId)
{
    if (*RecordCnt != CurrentCnt)
    {
        *RecordCnt = CurrentCnt;
        /* #Violation: Eth_c_REF_9*/
        Dem_SetEventStatus(EventId, DEM_EVENT_STATUS_PREFAILED);
    }
}
#if (ETH_OFFLOAD_CHECKSUM == STD_ON)
/****************************************************************************************************
 *   Function Name           : Eth_CheckForICMPV4Frame
 *
 *   Service ID              :
 *
 *   Description             : For ICMP-over-IPv4 packets, the Checksum field in the ICMP packet
 *                             must always be 16'h0000 in both modes, because pseudo-headers are
 *                             not defined for such packets. If it does not equal 16'h0000 , an
 *                             incorrect checksum may be inserted into the packet.
 *
 *   Parameters in           :FrameType- Ethernet frame type
 *                            EthLocalCoreStatusPtr- Pointer to Controller Status
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : void
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
static void Eth_CheckForICMPV4Frame
(
    const Eth_FrameType FrameType, 
    /* #Violation: Eth_c_REF_12 */
    volatile Eth_TxDescr const *CurDescrPtr
)
{
    uint8 *BufPtr;
    /* #Violation: Eth_c_REF_4*/
    /* #Violation: Eth_c_REF_14 */
    /* #Violation: Eth_c_REF_18 */
    BufPtr = (uint8 *)(CurDescrPtr->TDES0.U);
    /*IPV4 frame type*/
    if (ETH_IPV4_FRAMETYPE == FrameType)
    {
        if (BufPtr[ETH_FRAME_IPV4TYPE_POS] == ETH_IPV4_ICMP_PROTOCOL)
        {
            BufPtr[ETH_FRAME_ICMP_CRC_POS] = MCAL_ZERO;
            BufPtr[ETH_FRAME_ICMP_CRC_POS + 1U] = MCAL_ZERO;
        }
    }
}
#endif

/****************************************************************************************************
 *   Function Name           : Eth_ClearTxStatus
 *
 *   Service ID              :
 *
 *   Description             : This function set all Tx descriptor status to ETH_TX_DESC_NOUSE.
 *
 *   Parameters in           :uint8 CtrlIdx : ctronler index
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : void
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
static FUNC(void, ETH_PRIVATE_CODE) Eth_ClearTxStatus(Mcal_CoreType CoreId, uint8 CtrlIdx)
{
    uint8           Index;
    uint8           FifoIdx;

    /* #Violation: Eth_c_REF_9*/
    for (FifoIdx = MCAL_ZERO; FifoIdx < ETH_GET_MAX_TXDMA_NUM(CtrlIdx, CoreId); FifoIdx++)
    {
        /* #Violation: Eth_c_REF_9*/
        for (Index = MCAL_ZERO; Index < ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, FifoIdx); Index++)
        {
            /* #Violation: Eth_c_REF_9*/
            ETH_SET_BUF_IDX_STATE(CtrlIdx, CoreId, FifoIdx, Index, ETH_TX_DESC_NOUSE);
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Eth_InitPar
 *
 *   Service ID              :
 *
 *   Description             : This function set all parameters to default value.
 *
 *   Parameters in           :uint8 CtrlIdx : ctronler index
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : void
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
static FUNC(void, ETH_PRIVATE_CODE) Eth_InitPar(Mcal_CoreType CoreId, uint8 CtrlIdx)
{
    uint8           Index;
    uint8           FifoIdx;
    Eth_NodeHandle *NodePtr;
    /* #Violation: Eth_c_REF_9*/
    NodePtr = ETH_NODE_ADDR(CtrlIdx, CoreId);
    NodePtr->prevFreqCompensationValue = 0.0;
    NodePtr->pEthModule = Eth_ConfigPtr->EthCoreConfigPtr[CoreId]
                              ->EthCtrlConfigPtr[CtrlIdx]
                              .EthSdkCtrlConfigPtr->pEthModule;
    NodePtr->ethMiiCrValue = Eth_ConfigPtr->EthCoreConfigPtr[CoreId]
                                 ->EthCtrlConfigPtr[CtrlIdx]
                                 .EthSdkCtrlConfigPtr->ethMiiCrValue;
    NodePtr->numOfUsedTxCh = Eth_ConfigPtr->EthCoreConfigPtr[CoreId]
                                 ->EthCtrlConfigPtr[CtrlIdx]
                                 .EthSdkCtrlConfigPtr->ethNumTxChnls;

                                 
    NodePtr->txDescrInfoPtr = &Eth_TxChannelPtr[0];
    NodePtr->rxDescrInfoPtr = &Eth_RxChannelPtr[0];
    NodePtr->txChannelInfoPtr = &Eth_FifoTxInfo[0];
    NodePtr->rxChannelInfoPtr = &Eth_FifoRxInfo[0];
    /* #Violation: Eth_c_REF_9*/
    for (FifoIdx = MCAL_ZERO; FifoIdx < ETH_GET_MAX_TXDMA_NUM(CtrlIdx, CoreId); FifoIdx++)
    {
        NodePtr->txChannelInfoPtr[FifoIdx].channelId                       = ETH_DMA_CHANNEL0;
        NodePtr->txChannelInfoPtr[FifoIdx].numOfDescriptor                 = 0U;
        NodePtr->txChannelInfoPtr[FifoIdx].txBuffer1Size                   = 0U;
        NodePtr->txChannelInfoPtr[FifoIdx].txInfo.timeStamp.nanoseconds    = 0U;
        NodePtr->txChannelInfoPtr[FifoIdx].txInfo.timeStamp.seconds        = 0U;
        NodePtr->txChannelInfoPtr[FifoIdx].txInfo.timeStamp.secondsHi      = 0U;
        NodePtr->txChannelInfoPtr[FifoIdx].txInfo.errStatus                = 0U;
        NodePtr->txChannelInfoPtr[FifoIdx].txInfo.egressTimeStampAvailable = FALSE;
        NodePtr->txChannelInfoPtr[FifoIdx].pTxDescriptor                   = NULL_PTR;
        NodePtr->txChannelInfoPtr[FifoIdx].txChannelEnabled                = FALSE;
        NodePtr->txChannelInfoPtr[FifoIdx].descIndex                       = 0U;
        NodePtr->txChannelInfoPtr[FifoIdx].pTxBaseDescriptor               = NULL_PTR;
        /* #Violation: Eth_c_REF_9*/
        for (Index = MCAL_ZERO; Index < ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, FifoIdx); Index++)
        {
            /* #Violation: Eth_c_REF_19*/
            NodePtr->txDescrInfoPtr[FifoIdx][Index].txdescTxConfirm = (uint32)ETH_TX_DESC_NOUSE;
            NodePtr->txDescrInfoPtr[FifoIdx][Index].descrBufAddr    = 0U;
        }
    }
    /* #Violation: Eth_c_REF_9*/
    for (FifoIdx = MCAL_ZERO; FifoIdx < ETH_GET_MAX_RXDMA_NUM(CtrlIdx, CoreId); FifoIdx++)
    {
        NodePtr->rxChannelInfoPtr[FifoIdx].channelId                        = ETH_DMA_CHANNEL0;
        NodePtr->rxChannelInfoPtr[FifoIdx].numOfDescriptor                  = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxBuffer1Size                    = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.payloadType               = ETH_PAYLOAD_TYPE_UNKNOWN;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.timeStamp.nanoseconds     = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.timeStamp.seconds         = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.timeStamp.secondsHi       = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.errStatus                 = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.outerVlanTag              = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.innerVlanTag              = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.ipv6                      = FALSE;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.ipv4                      = FALSE;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.ipPayloadErr              = FALSE;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.ipHeaderErr               = FALSE;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.ingressTimeStampAvailable = FALSE;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxInfo.pCurDescr                 = NULL_PTR;
        NodePtr->rxChannelInfoPtr[FifoIdx].pRxDescriptor                    = NULL_PTR;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxChannelEnabled                 = FALSE;
        NodePtr->rxChannelInfoPtr[FifoIdx].descIndex                        = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].rxCount                          = 0U;
        NodePtr->rxChannelInfoPtr[FifoIdx].pRxBaseDescriptor                = NULL_PTR;
        /* #Violation: Eth_c_REF_9*/
        for (Index = MCAL_ZERO; Index < ETH_GET_MAX_RX_DESC_NUM(CtrlIdx, CoreId, FifoIdx); Index++)
        {
            /* #Violation: Eth_c_REF_9*/
            NodePtr->rxDescrInfoPtr[FifoIdx][Index].descrBufAddr = 0U;
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Eth_ControllerNotInitProcess
 *
 *   Service ID              :
 *
 *   Description             : This function initializes the controller when Ethernet has not been 
 *                             initialized before.
 *
 *   Parameters in           : uint8 CtrlIdx : Controller index
 *                            Mcal_CoreType CoreId : Core index
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : non-Reentrant.
 *
 *   Return value            : void.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/
 static FUNC(void, ETH_PRIVATE_CODE) Eth_ControllerNotInitProcess(Mcal_CoreType CoreId, uint8 CtrlIdx)
{
    Eth_Status     EthCtlStatus;
    /* \[SWS_Eth_00034] The function shall for all configured Ethernet controllers in the
    current EthConfigSet: Disable all controller Clear pending Ethernet interrupts Configure
    all controller configuration parameters (e.g. interrupts, frame length, frame filter, ...)
    Configure all transmit / receive resources (e.g. buffer initialization)
    implemented by geth reset.
    */
    ETH_ENTER_CRITICAL_SECTION(Eth_SetControllerMode);

    EthCtlStatus = Eth_Hal_Init(
        /* #Violation: Eth_c_REF_9*/
        ETH_NODE_ADDR(CtrlIdx, CoreId),
        Eth_ConfigPtr->EthCoreConfigPtr[CoreId]
            ->EthCtrlConfigPtr[CtrlIdx]
            .EthSdkCtrlConfigPtr);
    ETH_EXIT_CRITICAL_SECTION(Eth_SetControllerMode);

    if (ETH_STATUS_OK == EthCtlStatus)
    {
        /* #Violation: Eth_c_REF_9*/
        ETH_CONTROLLER_STATE(CtrlIdx, CoreId) = ETH_CNTRL_INITIALIZED;
        Eth_DemReportAllErrorPass(CtrlIdx, CoreId);
    }
    else
    {
        /* \[SWS_Eth_00173] [SWS_Eth_00168]The function shall check the access to the Ethernet
        controller. If the check fails, the function shall raise the production error
        ETH_E_ACCESS and return E_NOT_OK,otherwise pass the production error ETH_E_ACCESS
        and return E_OK. */
        /* #Violation: Eth_c_REF_9*/
        if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemAccess)
        {
            Dem_SetEventStatus(
                /* #Violation: Eth_c_REF_9*/
                ETH_DEM(CtrlIdx, CoreId)->EthDemAccess, DEM_EVENT_STATUS_PREFAILED);
        }
    }
}
/****************************************************************************************************
 *   Function Name           : Eth_ControllerHadInitProcess
 *
 *   Service ID              :
 *
 *   Description             : This function processes the controller mode change when Ethernet 
 *                              controller has been initialized.
 *
 *   Parameters in           : Mcal_CoreType CoreId : Core index
 *                            uint8 CtrlIdx : Controller index
 *                            Eth_ModeType CtrlMode : Desired controller mode
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Std_ReturnType
 *                            - E_OK: Controller mode changed successfully
 *                            - E_NOT_OK: Controller mode change failed
 *
 *   Preconditions           : Ethernet controller must be initialized.
 *
 *   AUTOSAR_Requirement     :  .
 ****************************************************************************************************/
static FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_ControllerHadInitProcess(Mcal_CoreType CoreId, uint8 CtrlIdx, Eth_ModeType CtrlMode)
{
    Std_ReturnType RetVal;
    Eth_ModeType   ModeStatus;
    Eth_Status     EthCtlStatus;
    RetVal = E_OK;
    /* #Violation: Eth_c_REF_9*/
    ModeStatus = Eth_Hal_GetControllerMode(ETH_NODE_ADDR(CtrlIdx, CoreId));
    /* \[SWS_Eth_00042] Put the controller in the specified mode given in the parameter*/
    if (ETH_MODE_ACTIVE == CtrlMode)
    {
        if (ETH_MODE_DOWN == ModeStatus)
        {
            /* down==>active */
            EthCtlStatus =
            /* #Violation: Eth_c_REF_9*/
                Eth_Hal_SetControllerMode(ETH_NODE_ADDR(CtrlIdx, CoreId), ETH_MODE_ACTIVE);
            if (ETH_STATUS_OK == EthCtlStatus)
            {
                /* #Violation: Eth_c_REF_9*/
                ETH_CONTROLLER_STATE(CtrlIdx, CoreId) = ETH_CNTRL_INITIALIZED_ACTIVE;
                /* SWS_Eth_00240  Calls EthIf_CtrlModeIndication when the controller
                mode changed. */
                EthIf_CtrlModeIndication(CtrlIdx, CtrlMode);
            }
            else
            {
                RetVal = E_NOT_OK;
            }
        }
    }
    /* down */
    else
    {
        if (ETH_MODE_ACTIVE == ModeStatus)
        {
            EthCtlStatus =
                /* #Violation: Eth_c_REF_9*/
                Eth_Hal_SetControllerMode(ETH_NODE_ADDR(CtrlIdx, CoreId), ETH_MODE_DOWN);
            /* active ==>down */
            if (ETH_STATUS_OK == EthCtlStatus)
            {
                /* \[SWS_Eth_00137] [SWS_Eth_00138]All locked transmit buffers shall be
                    * released delete all pending transmit and receive requests  */
                Eth_ClearTxStatus(CoreId, CtrlIdx);
                /* #Violation: Eth_c_REF_9*/
                ETH_CONTROLLER_STATE(CtrlIdx, CoreId) = ETH_CNTRL_INITIALIZED_DOWN;
                /* SWS_Eth_00240  Calls EthIf_CtrlModeIndication when the controller
                    * mode changed. */
                EthIf_CtrlModeIndication(CtrlIdx, CtrlMode);
            }
            else
            {
                RetVal = E_NOT_OK;
            }
        }
    }
    return RetVal;
}

#if (ETH_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
 *   Function Name           : Eth_CheckTransParam
 *
 *   Service ID              :
 *
 *   Description             : This function checks the parameters for Ethernet transmit operation.
 *
 *   Parameters in           : uint8 CtrlIdx : Controller index
 *                            uint8 PriorityId : Priority channel ID
 *                            Mcal_CoreType CoreId : Core index
 *                            uint8 BufferIdx : Transmit buffer index
 *                            P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr : Pointer to physical address
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Std_ReturnType
 *                            - E_OK: Parameters are valid
 *                            - E_NOT_OK: Parameters are invalid
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00092, SWS_Eth_00093.
 ****************************************************************************************************/

static FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_CheckTransParam
(
    uint8           CtrlIdx, 
    uint8           PriorityId,
    Mcal_CoreType   CoreId,
    uint8           BufferIdx,
    /* #Violation: Eth_c_REF_12 */
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr
)
{
    Std_ReturnType  RetVal;
    uint8           DmaIdx;
    RetVal = E_OK;
    /* #Violation: Eth_c_REF_9*/
    if (PriorityId >= ETH_GET_MAX_TXDMA_NUM(CtrlIdx, CoreId))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_INV_PARAM);
        RetVal = E_NOT_OK;
    }
    else
    {
        /* #Violation: Eth_c_REF_9*/
        DmaIdx = ETH_GET_CHID_FROM_FIFO(CtrlIdx, CoreId, PriorityId);

        /* \[SWS_Eth_00093] */
        if (NULL_PTR == PhysAddrPtr)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
        /* \[SWS_Eth_00092] If development error detection is enabled: the function shall check
        the parameter PhysAddrPtr for being valid. If the check fails, the function shall raise
        the development error ETH_E_PARAM_POINTER otherwise (if DET is disabled) return E_NOT_OK*/
        /* #Violation: Eth_c_REF_9*/
        else if (BufferIdx >= ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, DmaIdx))
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_INV_PARAM);
            RetVal = E_NOT_OK;
        }
        else
        /* #Violation: Eth_c_REF_17 */
        {
            /* DoNothing */
        }
    }
    return RetVal;
}
#endif /* End for ETH_DEV_ERROR_DETECT */
/****************************************************************************************************
 *   Function Name           : Eth_HalfDuplexDemReportErr
 *
 *   Service ID              :
 *
 *   Description             : This function reports half-duplex related errors to DEM module.
 *
 *   Parameters in           : Mcal_CoreType CoreId : Core index
 *                            uint8 CtrlIdx : Controller index
 *                            Eth_StatusType const *Eth_StatusPtr : Pointer to Ethernet status structure
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : void.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00224, SWS_Eth_00225.
 ****************************************************************************************************/

static FUNC(void, ETH_PRIVATE_CODE) Eth_HalfDuplexDemReportErr
(
    Mcal_CoreType CoreId, 
    uint8 CtrlIdx, 
    Eth_StatusType const *Eth_StatusPtr
)
{
    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemSingleCollision)
    {
        Eth_DemReportError(
            &(Eth_StatusPtr->ControllerStatePtr->DemErrorCnt.EthDemSingleCollisionCnt),
            /* #Violation: Eth_c_REF_9*/
            ETH_NODE(CtrlIdx, CoreId)
                .pEthModule->TX_SINGLE_COLLISION_GOOD_PACKETS.B.TXSNGLCOLG,
            /* #Violation: Eth_c_REF_9*/
            ETH_DEM(CtrlIdx, CoreId)->EthDemSingleCollision);
    }

    /* \[SWS_Eth_00224]*/

    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemMultipleCollision)
    {
        Eth_DemReportError(
            &(Eth_StatusPtr->ControllerStatePtr->DemErrorCnt.EthDemMultipleCollisionCnt),
            /* #Violation: Eth_c_REF_9*/
            ETH_NODE(CtrlIdx, CoreId)
                .pEthModule->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.TXMULTCOLG,
            /* #Violation: Eth_c_REF_9*/
            ETH_DEM(CtrlIdx, CoreId)->EthDemMultipleCollision);
    }

    /* \[SWS_Eth_00225]*/

    /* #Violation: Eth_c_REF_9*/
    if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemLateCollision)
    {
        Eth_DemReportError(
            &(Eth_StatusPtr->ControllerStatePtr->DemErrorCnt.EthDemLateCollisionCnt),
            /* #Violation: Eth_c_REF_9*/
            ETH_NODE(CtrlIdx, CoreId).pEthModule->TX_LATE_COLLISION_PACKETS.B.TXLATECOL,
            /* #Violation: Eth_c_REF_9*/
            ETH_DEM(CtrlIdx, CoreId)->EthDemLateCollision);
    }
}

/****************************************************************************************************
 *   Function Name           : Eth_Init
 *
 *   Service ID              : 0x01.
 *
 *   Description             : This function initializes the Ethernet Driver
 *
 *   Parameters in           : CfgPtr: Points to the implementation specific structure
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : void
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00027.[SWS_Eth_00003]
 * \[SWS_Eth_00014]The start address of post-build time configuration data shall be passed during
    module initialization.
    \[SWS_Eth_00031]Caveat: The API has to be called during initialization. 
    SWS_Eth_00034 is implement in Eth_Hal_Init of Eth_SetControllerMode.(HW)
    \[SWS_Eth_00039] 
    The function shall check the access to the Ethernet controller. If the check fails, the 
    function shall raise the production error ETH_E_ACCESS:

 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(void, ETH_PUBLIC_CODE) Eth_Init
(
    /* #Violation: Eth_c_REF_12 */
    P2CONST(Eth_ConfigType, AUTOMATIC, ETH_APPL_CONST) CfgPtr
)
{
    uint8        CtrlIdx;
    Mcal_CoreType CoreId;

    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    /* ETH_INV_POINTER */
    if (CfgPtr->EthCoreConfigPtr[CoreId] == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_INIT, ETH_E_INV_PARAM);
    }
    else
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* \[SWS_Eth_00028] Store the configuration data address in a global variable to enable
        subsequent API calls to access the configuration data. */
        Eth_ConfigPtr = CfgPtr;
        /* #Violation: Eth_c_REF_9*/
        for (CtrlIdx = MCAL_ZERO; CtrlIdx < ETH_CTRL_NUM(CoreId); CtrlIdx++)
        {
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr =
                Eth_ControllerStatePtr[CtrlIdx];
            Eth_ControllerStatePtr[CtrlIdx]->RxTmStmpDataPtr[0] = NULL_PTR;
            Eth_ControllerStatePtr[CtrlIdx]->RxTmStmpDataPtr[1] = NULL_PTR;
            Eth_ControllerStatePtr[CtrlIdx]->RxTmStmpDataPtr[2] = NULL_PTR;
            Eth_ControllerStatePtr[CtrlIdx]->RxTmStmpDataPtr[3] = NULL_PTR;

            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                .ControllerStatePtr->DemErrorCnt.EthDemAccessCnt = 0U;
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                .ControllerStatePtr->DemErrorCnt.EthDemFramesLostCnt = 0U;
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                .ControllerStatePtr->DemErrorCnt.EthDemAlignmentCnt = 0U;
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx].ControllerStatePtr->DemErrorCnt.EthDemCRCCnt =
                0U;
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                .ControllerStatePtr->DemErrorCnt.EthDemUndersizeCnt = 0U;
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                .ControllerStatePtr->DemErrorCnt.EthDemOversizeCnt = 0U;
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                .ControllerStatePtr->DemErrorCnt.EthDemSingleCollisionCnt = 0U;
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                .ControllerStatePtr->DemErrorCnt.EthDemMultipleCollisionCnt = 0U;
            Eth_CoreChannelStatusPtr[CoreId][CtrlIdx]
                .ControllerStatePtr->DemErrorCnt.EthDemLateCollisionCnt = 0U;
            Eth_InitPar(CoreId, CtrlIdx);
            /* #Violation: Eth_c_REF_9*/
            ETH_CONTROLLER_STATE(CtrlIdx, CoreId) = ETH_CNTRL_NOT_INITIALIZED;
                                                   
            /* \[SWS_Eth_00039] */
            /* #Violation: Eth_c_REF_9*/
            if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemAccess)
            {
                /* #Violation: Eth_c_REF_9*/
                Dem_SetEventStatus(ETH_DEM(CtrlIdx, CoreId)->EthDemAccess, DEM_EVENT_STATUS_PREPASSED);
            }
            /* \[SWS_Eth_00029] change the state of the driver from ETH_STATE_UNINIT to
             * ETH_STATE_INIT.*/
            /* #Violation: Eth_c_REF_9*/
            ETH_DRIVER_STATE(CtrlIdx, CoreId) = ETH_STATE_INIT;
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Eth_SetControllerMode
 *
 *   Service ID              : 0x03.
 *
 *   Description             : This function Enables / Disables the indexed controller
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet
 *                             Driver. 
 *                             CtrlMode: Controller Mode DOWN/ACTIVE
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.  : depend on hw.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: Successfully Initialized the controller.
 *                             E_NOT_OK: E_NOT_OK: controller mode could not be changed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00041.[SWS_Eth_00158][SWS_Eth_00034][SWS_Eth_00039]
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_SetControllerMode
(
    uint8 CtrlIdx, 
    /* #Violation: Eth_c_REF_13 */
    Eth_ModeType CtrlMode
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType  CoreId;
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Eth_StatusType const *Eth_StatusPtr;
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
    RetVal = E_NOT_OK;
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Eth_StatusPtr = Eth_CoreChannelStatusPtr[CoreId];
    /*  ETH_E_INV_CTRL_IDX  \[SWS_Eth_00044]  */
    if (CtrlIdx != MCAL_ZERO)
    {
        (void)Det_ReportError(
            ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SETCONTROLLERMODE, ETH_E_INV_CTRL_IDX);
    }
    /* \[SWS_Eth_00043] [SWS_Eth_00045]ETH_E_UNINIT */
    else if (NULL_PTR == Eth_ConfigPtr)
    {
        (void)Det_ReportError(
            ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SETCONTROLLERMODE, ETH_E_UNINIT);
    }
    else if (NULL_PTR == Eth_StatusPtr)
    {
        (void)Det_ReportError(
            ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SETCONTROLLERMODE, ETH_E_CORE_MISMATCH);
    }
    else if (ETH_MODE_ACTIVE < CtrlMode)
    {
        (void)Det_ReportError(
            ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SETCONTROLLERMODE, ETH_E_INV_MODE);
    }    
    else
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        if (ETH_CNTRL_NOT_INITIALIZED == ETH_CONTROLLER_STATE(CtrlIdx, CoreId))
        {
            Eth_ControllerNotInitProcess(CoreId, CtrlIdx);
        }
        /* 1. Disable the Transmit DMA (if applicable) by clearing Bit 0 (ST) of
         DMA_CH(#i)_TX_Control.
         2. Wait for any previous frame transmissions to complete. You can check this by
         reading the appropriate bits of MTL_TxQ0_Debug Register (TRCSTS is not 01 and
         TXQSTS=0).
         3. Disable the MAC transmitter and MAC receiver by clearing Bit (RE) and Bit 1(TE) .
         4. Disable the Receive DMA (if applicable), after making sure that the data in the Rx
         FIFO is transferred to the system memory (by reading the appropriate bits of
         MTL_TxQ0_Debug Register, PRXQ=0 and RXQSTS=00).
         5. Make sure that both Tx Queue and Rx Queue are empty (TXQSTS is 0 in MTL_TxQ0_Debug
         Register and RXQSTS is 0 in MTL_RxQ0_Debug Register).
         6. To restart the operation, first start the DMAs, and then enable the MAC
         Transmitter and Receiver */
        /* #Violation: Eth_c_REF_9*/
        if (ETH_CONTROLLER_STATE(CtrlIdx, CoreId) > ETH_CNTRL_NOT_INITIALIZED)
        {
            RetVal = Eth_ControllerHadInitProcess(CoreId, CtrlIdx, CtrlMode);
            if (E_OK == RetVal)
            {
                /* #Violation: Eth_c_REF_9*/
                if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemAccess)
                {
                    Dem_SetEventStatus(
                        /* #Violation: Eth_c_REF_9*/
                        ETH_DEM(CtrlIdx, CoreId)->EthDemAccess, DEM_EVENT_STATUS_PREPASSED);
                }
            }
        }
    }

    return RetVal;
}

/****************************************************************************************************
 *   Function Name           : Eth_GetControllerMode
 *
 *   Service ID              : 0x04.
 *
 *   Description             : This function Obtains the state of the indexed controller
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet
 *                                      Driver
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : CtrlModePtr: Controller Mode DOWN/ACTIVE
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant. depend on hw.
 *
 *   Return value            : E_OK: Successfully .
 *                             E_NOT_OK: controller mode could not be obtained.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00046.
 * [SWS_Eth_00047]:The function shall read the current controller mode
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetControllerMode
(
    uint8 CtrlIdx, 
    /* #Violation: Eth_c_REF_12 */
    P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType  CoreId;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    /* \[SWS_Eth_00048] If development error detection is enabled: the function shall check that the
    service Eth_Init was previously called. If the check fails, the function shall raise the
    development error ETH_E_UNINIT otherwise (if DET is disabled) return E_NOT_OK*/
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETCONTROLLERMODE, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00050] If development error detection is enabled: the function shall check the
        parameter CtrlModePtr for being valid. If the check fails, the function shall raise the
        development error ETH_E_PARAM_POINTER otherwise (if DET is disabled) return E_NOT_OK*/
        if (NULL_PTR == CtrlModePtr)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETCONTROLLERMODE, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        *CtrlModePtr = Eth_Hal_GetControllerMode(ETH_NODE_ADDR(CtrlIdx, CoreId));
        RetVal = E_OK;
    }
    return RetVal;
}

/****************************************************************************************************
 *   Function Name           : Eth_GetPhysAddr
 *
 *   Service ID              : 0x08.
 *
 *   Description             : This function Obtains the physical source address used by the indexed
 *controller
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet
 *Driver.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : PhysAddrPtr: Physical source address (MAC address) in network byte
 *order.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : Void
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00052.
 * [SWS_Eth_00053]The function shall read the source address used by the indexed controller.
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10 */
FUNC(void, ETH_PUBLIC_CODE) Eth_GetPhysAddr
(
    uint8 CtrlIdx, 
    /* #Violation: Eth_c_REF_12 */
    P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr
)
{
    Mcal_CoreType    CoreId;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetVal;
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETPHYADDRESS, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00056] */
        if (NULL_PTR == PhysAddrPtr)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETPHYADDRESS, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        Eth_Hal_GetMacAddress(ETH_NODE_ADDR(CtrlIdx, CoreId), PhysAddrPtr);
    }
}

/****************************************************************************************************
 *   Function Name           : Eth_SetPhysAddr
 *
 *   Service ID              : 0x13.
 *
 *   Description             : Sets the physical source address used by the indexed controller
 *
 *   Parameters in           : CtrlIdx: Index of the Ethernet controller within the context of the
 *Ethernet.
 *                             PhysAddrPtr: Pointer to memory containing the physical source address
(MAC address) in network byte order
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non Reentrant for the same CtrlIdx, reentrant for different
 *
 *   Return value            :
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00151.
 * [SWS_Eth_00139]The function shall update the source address used by the indexed controller
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(void, ETH_PUBLIC_CODE) Eth_SetPhysAddr
(
    uint8 CtrlIdx, 
    /* #Violation: Eth_c_REF_12 */
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr
)
{
    Mcal_CoreType CoreId;
    boolean       RegCheck;
    RegCheck = TRUE;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetVal;
    /*  ETH_E_INV_CTRL_IDX  \[SWS_Eth_00141]  */
    /*  ETH_E_UNINIT \[SWS_Eth_00140]*/
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_SETPHYSADDRESS, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00142]  ETH_E_PARAM_POINTER*/
        if (NULL_PTR == PhysAddrPtr)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SETPHYSADDRESS, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        RegCheck &= Eth_Hal_SetMacAddress(ETH_NODE_ADDR(CtrlIdx, CoreId), PhysAddrPtr);
#if (ETH_SAFETY_ENABLE == STD_ON)
        if (FALSE == RegCheck)
        {
            (void)Det_ReportRuntimeError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SETPHYSADDRESS, ETH_E_REG_CHECK_FAIL);
        }
#endif /* (ETH_SAFETY_ENABLE \== STD_ON)*/
    }
    /* #Violation: Eth_c_REF_9*/
    MCAL_UNUSED_VAR(RegCheck);
}

/****************************************************************************************************
 *   Function Name           : Eth_UpdatePhysAddrFilter
 *
 *   Service ID              : 0x12.
 *
 *   Description             : Update the physical source address to/from the indexed controller 
 *                            filter. If the Ethernet Controller is not capable to do the filtering, 
 *                            the software has to do this.
 *
 *   Parameters in           : CtrlIdx: Index of the Ethernet controller within the context of the 
 *                                      Ethernet Driver.
 *                             PhysAddrPtr: Pointer to memory containing the physical destination 
 *                                     address (MAC address) in network byte order. This is the 
 *                                     multicast destination address of the layer 2 Ethernet packet
 *                             Action: Add or remove the address from the Ethernet controllers filter.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non reentrant for same CtrlIdx, reentrant for different.
 *
 *   Return value            : Std_ReturnType .OK, NOT_OK
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : [SWS_Eth_00152]
 * [SWS_Eth_00150]The function shall update the physical address receive filter of the indexed 
 * controller.
 * [SWS_Eth_00163]
 * [SWS_Eth_00245]The Ethernet driver module will receive a frame when the destination 
 * Address match the PhyAddrPtr passed here. (e.g matching can be done via hash table or simple 
 * pattern matching
 * [SWS_Eth_00246]If the matching is positive, the upper layer shall be notified by calling 
 * RxIndication() callback.If the matching is negative, the frame shall be discarded
 * [SWS_Eth_00146] If this API is used and the hardware does not support filtering, promiscuous mode 
 * shall be enabled during initialization. :N.A  HW support.
 * 
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_UpdatePhysAddrFilter
(
    uint8 CtrlIdx, 
    /* #Violation: Eth_c_REF_12 */
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr, 
    /* #Violation: Eth_c_REF_13 */
    Eth_FilterActionType Action
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType  CoreId;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_UPDATEPHYSADDRFILTER, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00166] */
        if (NULL_PTR == PhysAddrPtr)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_UPDATEPHYSADDRFILTER, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* \[SWS_Eth_00144] If the physical source address (MAC address) is set to FF:FF:FF: FF:FF:FF,
        this shall completely open the filter.
        [SWS_Eth_00147] If the physical source address (MAC address) is set to 00:00:00: 00:00:00,
        this shall reduce the filter to the controllers unique ess and end promiscuous mode if it was
        turned on. */
        RetVal = (Std_ReturnType)Eth_Hal_UpdatePhysAddrFilter(
            /* #Violation: Eth_c_REF_9*/
            ETH_NODE_ADDR(CtrlIdx, CoreId), PhysAddrPtr, Action);
    }
    return RetVal;
}

/* \[SWS_Eth_00062] [SWS_Eth_00069]*/
#if (ETH_ENA_MII_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Eth_WriteMii
 *
 *   Service ID              : 0x05.
 *
 *   Description             : Configures a transceiver register or triggers a function offered by 
 *                             the receiver
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet Driver
 *                             TrcvIdx: Index of the transceiver on the MII
 *                             RegIdx: Index of the transceiver register on the MII
 *                             RegVal: Value to be written into the indexed register
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.: depend on hw.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: service accepted
 *                             E_NOT_OK: service denied
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00058.
 *  [SWS_Eth_00059] The function shall write the specified transceiver register through the MII of the 
indexed controller.
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_WriteMii
(
    uint8 CtrlIdx, 
    uint8 TrcvIdx, 
    uint8 RegIdx, 
    /* #Violation: Eth_c_REF_13 */
    uint16 RegVal
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType   CoreId;
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Eth_StatusType const *Eth_StatusPtr;
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */

    RetVal = E_NOT_OK;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Eth_StatusPtr = Eth_CoreChannelStatusPtr[CoreId];
    if (Eth_StatusPtr == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_WRITEMII, ETH_E_CORE_MISMATCH);
    }
    else if (CtrlIdx != MCAL_ZERO) /*  ETH_E_INV_CTRL_IDX  \[SWS_Eth_00061]  */
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_WRITEMII, ETH_E_INV_CTRL_IDX);
    }
    /*  ETH_E_UNINIT \[SWS_Eth_00060] If development error detection is enabled: the function
    shall check that the service Eth_Init was previously called. If the check fails, the function
    shall raise the development error ETH_E_UNINIT
    \[SWS_Eth_00063]*/
    else if (NULL_PTR == Eth_ConfigPtr)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_WRITEMII, ETH_E_UNINIT);
    }
    else
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        RetVal =
            /* #Violation: Eth_c_REF_9*/
            (Std_ReturnType)Eth_Hal_WriteMii(ETH_NODE_ADDR(CtrlIdx, CoreId), TrcvIdx, RegIdx, RegVal);
        if (E_OK == RetVal)
        {
            /* \[SWS_Eth_00241]The function shall call EthTrcv_WriteMiiIndication when the MII access
             * finished.*/
            EthTrcv_WriteMiiIndication(CtrlIdx, TrcvIdx, RegIdx);
        }
    }
    return RetVal;
}

/****************************************************************************************************
 *   Function Name           : Eth_ReadMii
 *
 *   Service ID              : 0x06.
 *
 *   Description             : This function reads a transceiver register
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet
 *                                      Driver.
 *                             TrcvIdx: Index of the transceiver on the MII (see [21] for details)
 *                             RegIdx: Index of the transceiver register on the MII (see [21] for
 *                                      details)
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : RegValPtr: Filled with the register content of the indexed register
 *                                       (see [21] for details)
 *
 *   Sync/Async              : Synchronous.: depend on hw.
 * 
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: service accepted
 *                             E_NOT_OK: service denied
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00064.
 * [SWS_Eth_00065]The function shall read the specified transceiver register through the MII of the 
 * indexed controller. 
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_ReadMii
(
    uint8 CtrlIdx, 
    uint8 TrcvIdx, 
    uint8 RegIdx, 
    /* #Violation: Eth_c_REF_12 */
    P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) RegValPtr
)
{
    Std_ReturnType RetVal;
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Eth_StatusType const *Eth_StatusPtr;
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    Mcal_CoreType   CoreId;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
    RetVal = E_NOT_OK;
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Eth_StatusPtr = Eth_CoreChannelStatusPtr[CoreId];
    if (Eth_StatusPtr == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_READMII, ETH_E_CORE_MISMATCH);
    }
    /*  ETH_E_INV_CTRL_IDX  \[SWS_Eth_00067]  */
    else if (CtrlIdx != MCAL_ZERO)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_READMII, ETH_E_INV_CTRL_IDX);
    }
    /*  ETH_E_UNINIT \[SWS_Eth_00066] [SWS_Eth_00070]*/
    else if (NULL_PTR == Eth_ConfigPtr)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_READMII, ETH_E_UNINIT);
    }
    else if (NULL_PTR == RegValPtr) /* \[SWS_Eth_00068]  ETH_E_PARAM_POINTER*/
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_READMII, ETH_E_PARAM_POINTER);
    }
    else
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        *RegValPtr = 0U;
        RetVal = (Std_ReturnType)Eth_Hal_ReadMii(
            /* #Violation: Eth_c_REF_9*/
            ETH_NODE_ADDR(CtrlIdx, CoreId), TrcvIdx, RegIdx, RegValPtr);
        /* \[SWS_Eth_00242]The function shall call EthTrcv_ReadMiiIndication when the MII access
         * finished*/
        if (E_OK == RetVal)
        {
            EthTrcv_ReadMiiIndication(CtrlIdx, TrcvIdx, RegIdx, *RegValPtr);
        }
        else
        {
            RetVal = E_NOT_OK;
        }
    }
    return RetVal;
}
#endif /* (ETH_ENA_MII_API \== STD_ON) */
/* \[SWS_Eth_00231]The function Eth_GetCounterValues shall be pre compile time configurable On/Off by 
the configuration parameter: EthGetCounterValuesApi.: this replaced with EthGetDropCountApi.
*/
#if (ETH_GET_DROP_COUNT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Eth_GetCounterValues
*
*   Service ID              : 0x14.
*
*   Description             : Reads a list with drop counter values of the corresponding controller.
*                             The meaning of these values is described at Eth_CounterType
*
*   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet
*                                      Driver.
*   Parameters inout        :

*
*   Parameters out          : CounterPtr: counter values according to IETF RFC 1757, RFC 1643 and 
*                                         RFC 2233.
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: success
*                             E_NOT_OK:  counter values read failure
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Eth_00226.
* [SWS_Eth_00227]The function shall read a list of values from the indexed controller
****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetCounterValues
(
    uint8 CtrlIdx, 
    /* #Violation: Eth_c_REF_12 */
    Eth_CounterType* CounterPtr
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType  CoreId;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)

    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETDROPCOUNT, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00230] ETH_E_PARAM_POINTER*/
        if (NULL_PTR == CounterPtr)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETDROPCOUNT, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        Eth_Hal_GetDropCounter(ETH_NODE_ADDR(CtrlIdx, CoreId), CounterPtr);
        RetVal = E_OK;
    }
    return RetVal;
}
#endif /* (ETH_GET_DROP_COUNT_API \== STD_ON) */
/* \[SWS_Eth_00238]The function Eth_GetRxStats shall be pre compile time configurable On/Off by the 
configuration parameter: EthGetRxStatsApi. :replaced EthGetRxStatsApi  with EthGetEtherStatsApi*/
#if (ETH_GET_ETHER_STATS_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Eth_GetRxStats
 *
 *   Service ID              : 0x15.
 *
 *   Description             : This function returns the list according to IETF RFC2819
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet 
 *                              Driver.
 *                             RxStats: List of values according to IETF RFC 2819 (Remote Network 
 *                              Monitoring Management Information Base)
 *   Parameters inout        : None
 *
 *   Parameters out          : EtherStats: list of values
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: success
 *                             E_NOT_OK: could not be obtained
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : [SWS_Eth_00233].
 * [SWS_Eth_00234] The function shall read a list of values from the indexed controller according 
 * to [22]
 * 
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetRxStats
(
    uint8 CtrlIdx, 
    /* #Violation: Eth_c_REF_12 */
    Eth_RxStatsType* RxStats
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType  CoreId;
/* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETETHERSTATS, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00237] ETH_E_PARAM_POINTER */
        if (NULL_PTR == RxStats)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETETHERSTATS, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        Eth_Hal_GetEtherStats(ETH_NODE_ADDR(CtrlIdx, CoreId), RxStats);
        RetVal = E_OK;
    }
    return RetVal;
}
#endif /* (ETH_GET_ETHER_STATS_API \== STD_ON) */


/* \[SWS_Eth_00251]The function Eth_GetTxStats shall be pre compile time configurable On/Off by the 
configuration parameter: EthGetTxStatsApi.*/
#if (ETH_GETTXSTATS_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Eth_GetTxStats
 *
 *   Service ID              : 0x1c.
 *
 *   Description             : Returns the list of Transmission Statistics out of IETF RFC1213 defined
 *                             with Eth_TxStatsType, where the maximal possible value shall denote an 
 *                             invalid value, e.g. this counter is not available.
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet 
 *                                      Driver.
 *                             
 *
 *   Parameters inout        :
 *
 *   Parameters out          : TxStats: List of values to read statistic values for transmission
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: successful
 *                             E_NOT_OK: Tx-statistics could not be obtained
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_91005.
 ****************************************************************************************************/
Std_ReturnType Eth_GetTxStats
(
    uint8 CtrlIdx,
    Eth_TxStatsType* TxStats
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType  CoreId;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    /* \[SWS_Eth_00248] ETH_E_UNINIT */
    /* \[SWS_Eth_00249] ETH_E_INV_CTRL_IDX */
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETTXSTATS, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00250] ETH_E_PARAM_POINTER */
        if (NULL_PTR == TxStats)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETTXSTATS, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        Eth_Hal_GetTxStats(ETH_NODE_ADDR(CtrlIdx, CoreId), TxStats);
        RetVal = E_OK;
    }
    return RetVal;
}
#endif  /* ETH_GETTXSTATS_API == STD_ON */

/* \[SWS_Eth_00255]The function Eth_GetTxErrorCounterValues shall be pre compile time configurable 
On/Off by the configuration parameter: EthGetTxErrorCounterValuesApi.*/
#if (ETH_GETTXERRCNTRVAL_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Eth_GetTxErrorCounterValues
 *
 *   Service ID              : 0x1d
 *
 *   Description             : Returns the list of Transmission Error Counters out of IETF RFC1213 and
 *                             RFC1643 defined with Eth_TxErrorCounterValuesType, where the maximal 
 *                             possible value shall denote an invalid value, e.g. this counter is not
 *                             available..
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet
 *                                      Driver.
 *
 *
 *   Parameters inout        :
 *
 *   Parameters out          : TxErrorCounterValues: List of values to read statistic error counter 
 *                                                   Values for transmission
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: successful
 *                             E_NOT_OK: could not be obtained
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_91006.
 ****************************************************************************************************/
Std_ReturnType Eth_GetTxErrorCounterValues
(
    uint8 CtrlIdx,
    Eth_TxErrorCounterValuesType* TxErrorCounterValues
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType  CoreId;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    /* \[SWS_Eth_00252] ETH_E_UNINIT */
    /* \[SWS_Eth_00253] ETH_E_INV_CTRL_IDX */
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETTXERRORCOUNTERVALUES, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00254] ETH_E_PARAM_POINTER */
        if (NULL_PTR == TxErrorCounterValues)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETTXERRORCOUNTERVALUES, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        Eth_Hal_GetTxErrorCounterValues(ETH_NODE_ADDR(CtrlIdx, CoreId), TxErrorCounterValues);

        RetVal = E_OK;
    }
    return RetVal;
}
#endif  /* ETH_GETTXERRCNTRVAL_API == STD_ON */

/* \[SWS_Eth_00210] [SWS_Eth_00211][SWS_Eth_00212][SWS_Eth_00213] [SWS_Eth_00214][SWS_Eth_00215]
 */
#if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Eth_GetCurrentTime
 *
 *   Service ID              : 0x16.
 *
 *   Description             : Returns a time value out of the HW registers according to the 
 *                             capability of the HW. Is the HW resolution is lower than the 
 *                             Eth_TimeStampType resolution resp. range, than an the remaining bits
 *                             will be filled with 0.Important Note: Eth_GetCurrentTime may be called
 *                             within an exclusive area
 *
 *   Parameters in           : CtrlIdx: Index of the addresses ETH controller.
 *
 *   Parameters inout        :
 *
 *   Parameters out          : timeQualPtr: quality of HW time stamp, e.g. based on current drift
 *                             timeStampPtr: current time stamp
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: successful
 *                             E_NOT_OK: failed
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00181.
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetCurrentTime
(
    uint8 CtrlIdx,
    /* #Violation: Eth_c_REF_12 */
    P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
    /* #Violation: Eth_c_REF_12 */
    P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr
)
{
    Std_ReturnType RetVal;
    Mcal_CoreType  CoreId;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
    if (NULL_PTR != timeQualPtr)
    {
        *timeQualPtr = ETH_INVALID;
    }

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETCURRENTTIME, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00184]
          If default error detection is enabled: the function shall check the parameter
          timeQualPtr and timeStampPtr for being valid. If the check fails, the function shall
          raise the default error ETH_E_PARAM_POINTER.*/
        if ((NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr))
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETCURRENTTIME, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        Eth_Hal_GetCurrentTime(ETH_NODE_ADDR(CtrlIdx, CoreId), timeStampPtr);
        RetVal = E_OK;
        *timeQualPtr = ETH_VALID;
    }
    return RetVal;
}

/****************************************************************************************************
 *   Function Name           : Eth_EnableEgressTimeStamp
 *
 *   Service ID              : 0x17.
 *
 *   Description             : Activates egress time stamping on a dedicated message object. 
 *                             Some HW does store once the egress time stamp marker and some HW needs 
 *                             it always before transmission. There will be no "disable" functionality,
 *                             due to the fact, that the message type is always "time stamped" by
 *                             network design.
 *   Parameters in           : CtrlIdx: Index of the addresses ETH controller.
 *                             BufId: Index of the message buffer, where Application expects egress 
 *                                    time stamping
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00186.
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(void, ETH_PUBLIC_CODE) Eth_EnableEgressTimeStamp
(
    uint8 CtrlIdx, 
    /* #Violation: Eth_c_REF_13 */
    Eth_BufIdxType BufIdx
)
{
    Eth_TxdescTxConfirmType TxdescTxConfirmState;
    Mcal_CoreType           CoreId;
    uint8                   PriorityId;
    uint8                   DmaIdx;
    uint8                   BufferIdx;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetVal;
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
    PriorityId = (uint8)((BufIdx & 0xFFFFE000U) >> 13U);
    BufferIdx = (uint8)(BufIdx & ETH_BUFIDX_MASK);
    /* called before tx, bufIdx is descriptor index */
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_ENABLEEGRESS, CoreId);
    if (E_OK == RetVal)
    {
        /* #Violation: Eth_c_REF_9*/
        if (PriorityId >= ETH_GET_MAX_TXDMA_NUM(CtrlIdx, CoreId))
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_ENABLEEGRESS, ETH_E_INV_PARAM);
            RetVal = E_NOT_OK;
        }
        else
        {
            /* #Violation: Eth_c_REF_9*/
            DmaIdx = ETH_GET_CHID_FROM_FIFO(CtrlIdx, CoreId, PriorityId);
            /* #Violation: Eth_c_REF_9*/
            if (BufferIdx >= ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, DmaIdx))
            {
                (void)Det_ReportError(
                    ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_ENABLEEGRESS, ETH_E_INV_PARAM);
                RetVal = E_NOT_OK;
            }            
        } 
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        DmaIdx = ETH_GET_CHID_FROM_FIFO(CtrlIdx, CoreId, PriorityId);
        /* #Violation: Eth_c_REF_9*/            
        /* #Violation: Eth_c_REF_19*/
        TxdescTxConfirmState = ETH_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, BufferIdx);
        if (TxdescTxConfirmState == ETH_TX_DESC_NOUSE)
        {
#if (ETH_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_ENABLEEGRESS, ETH_E_INV_PARAM);
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
        }
        else
        {
            /* #Violation: Eth_c_REF_9*/
            Eth_Hal_EnableEgressTimeStamp(    
                /* #Violation: Eth_c_REF_19*/
                ETH_NODE_ADDR(CtrlIdx, CoreId), (Eth_DmaChannel)DmaIdx, BufferIdx);
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Eth_GetEgressTimeStamp
 *
 *   Service ID              : 0x18.
 *
 *   Description             : Reads back the egress time stamp on a dedicated message object.
 *                             It must be called within the TxConfirmation() function.
 *
 *   Parameters in           : CtrlIdx: Index of the addresses ETH controller..
 *                             BufId:Index of the message buffer, where Application expects egress 
 *                                   time stamping
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : TimeQualPtr: quality of HW time stamp, based on current drift
 *                             TimeStampPtr: current time stamp
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : Std_ReturnType E_OK: success 
 *                                            E_NOT_OK: failed to read time stamp.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00190.
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
Std_ReturnType Eth_GetEgressTimeStamp
(
    uint8 CtrlIdx,
    /* #Violation: Eth_c_REF_13 */
    Eth_BufIdxType BufIdx,
    /* #Violation: Eth_c_REF_12 */
    Eth_TimeStampQualType* timeQualPtr,
    /* #Violation: Eth_c_REF_12 */
    Eth_TimeStampType* timeStampPtr
)
{
    Eth_TxdescTxConfirmType TxdescTxConfirmState;
    Mcal_CoreType       CoreId;
    uint8                   PriorityId;
    uint8                   DmaIdx;
    uint8                   BufferIdx;
    Std_ReturnType          RetVal;
    /* #Violation: Eth_c_REF_7*/
#if (ETH_DEV_ERROR_DETECT != STD_ON)
    RetVal = E_OK;
#endif /* (ETH_DEV_ERROR_DETECT !\= STD_ON) */
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
    PriorityId = (uint8)((BufIdx & 0xFFFFE000U) >> 13U);
    BufferIdx = (uint8)(BufIdx & ETH_BUFIDX_MASK);
    if (NULL_PTR != timeQualPtr)
    {
        *timeQualPtr = ETH_INVALID;
    }
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETEGRESSTIME, CoreId);
    if (E_OK == RetVal)
    {
        /* #Violation: Eth_c_REF_9*/
        if (PriorityId >= ETH_GET_MAX_TXDMA_NUM(CtrlIdx, CoreId))
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETEGRESSTIME, ETH_E_INV_PARAM);
            RetVal = E_NOT_OK;
        }
        else
        {
            /* #Violation: Eth_c_REF_9*/
            DmaIdx = ETH_GET_CHID_FROM_FIFO(CtrlIdx, CoreId, PriorityId);

            /* \[SWS_Eth_00193] If development error detection is enabled: the function shall check
            the parameter timeQualPtr and timeStampPtr for being valid. If the check fails, the
            function shall raise the development error ETH_E_PARAM_POINTER*/
            if ((NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr))
            {
                (void)Det_ReportError(
                    ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETEGRESSTIME, ETH_E_PARAM_POINTER);
                RetVal = E_NOT_OK;
            }
            /* #Violation: Eth_c_REF_9*/
            else if (BufferIdx >= ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, DmaIdx))
            {
                (void)Det_ReportError(
                    ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETEGRESSTIME, ETH_E_INV_PARAM);
                RetVal = E_NOT_OK;
            }
            else
            /* #Violation: Eth_c_REF_16 */
            /* #Violation: Eth_c_REF_17 */
            {
                /*DoNothing*/
            }
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        DmaIdx = ETH_GET_CHID_FROM_FIFO(CtrlIdx, CoreId, PriorityId);
        /* #Violation: Eth_c_REF_9*/
        /* #Violation: Eth_c_REF_19*/
        TxdescTxConfirmState = ETH_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, BufferIdx);
        if (ETH_TX_DESC_NOUSE == TxdescTxConfirmState)
        {
#if (ETH_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETEGRESSTIME, ETH_E_INV_PARAM);
            RetVal = E_NOT_OK;
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
        }
        else
        {
            ETH_ENTER_CRITICAL_SECTION(Eth_GetEgressTimeStamp);

            /* #Violation: Eth_c_REF_9*/
            if (TRUE == ETH_TX_INFO(CtrlIdx, CoreId, DmaIdx).egressTimeStampAvailable)
            {
                *timeQualPtr = ETH_VALID;
                /* #Violation: Eth_c_REF_9*/
                *timeStampPtr = ETH_RX_INFO(CtrlIdx, CoreId, DmaIdx).timeStamp;
                /* #Violation: Eth_c_REF_9*/
                ETH_TX_INFO(CtrlIdx, CoreId, DmaIdx).egressTimeStampAvailable = FALSE;
            }

            ETH_EXIT_CRITICAL_SECTION(Eth_GetEgressTimeStamp);
        }
    }
    return RetVal;
}

/****************************************************************************************************
 *   Function Name           : Eth_GetIngressTimeStamp
 *
 *   Service ID              : 0x19.
 *
 *   Description             : Reads back the ingress time stamp on a dedicated message object.
 *                                It must be called within the RxIndication() function.
 *
 *   Parameters in           : CtrlIdx: Index of the addresses ETH controller.
 *                             DataPtr: Pointer to the message buffer, where Application expects 
 *                                      ingress time stamping
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : TimeQualPtr: quality of HW time stamp, based on current drift
 *                             TimeStampPtr: current time stamp
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : Std_ReturnType E_OK: success 
 *                                            E_NOT_OK: failed to read time stamp.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00195.[SWS_Eth_00178]
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
Std_ReturnType Eth_GetIngressTimeStamp
(
    uint8 CtrlIdx,
    /* #Violation: Eth_c_REF_12 */
    const Eth_DataType* DataPtr,
    /* #Violation: Eth_c_REF_12 */
    Eth_TimeStampQualType* timeQualPtr,
    /* #Violation: Eth_c_REF_12 */
    Eth_TimeStampType* timeStampPtr
)
{
    Std_ReturnType RetVal;
    uint8          Index;
    uint8          DmaIdx;
    Mcal_CoreType  CoreId;
    boolean        DataPtrValid;
    DataPtrValid = FALSE;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
    /* #Violation: Eth_c_REF_7*/
#if (ETH_DEV_ERROR_DETECT != STD_ON)
    RetVal = E_OK;
#endif /* (ETH_DEV_ERROR_DETECT !\= STD_ON) */
    if (NULL_PTR != timeQualPtr)
    {
        *timeQualPtr = ETH_INVALID;
    }
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_GETINGRESSTIME, CoreId);
    if (E_OK == RetVal)
    {
        /* \[SWS_Eth_00198] If development error detection is enabled: the function shall check the
        parameter DataPtr, timeQualPtr and timeStampPtr for being valid. If the check fails, the
        function shall raise the development error ETH_E_PARAM_POINTER.*/
        if ((NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr) || (NULL_PTR == DataPtr))
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETINGRESSTIME, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* #Violation: Eth_c_REF_9*/
        for (Index = 0U; (Index < ETH_GET_MAX_RXDMA_NUM(CtrlIdx, CoreId)) && (FALSE == DataPtrValid); Index++)
        {
            /* #Violation: Eth_c_REF_9*/
            if (ETH_RX_TMSTMP_DATAPTR(CtrlIdx, CoreId, Index) == DataPtr)
            {
                DmaIdx = Index;
                ETH_ENTER_CRITICAL_SECTION(Eth_GetIngressTimeStamp);
                /* #Violation: Eth_c_REF_9*/
                if (TRUE == ETH_RX_INFO(CtrlIdx, CoreId, DmaIdx).ingressTimeStampAvailable)
                {
                    *timeQualPtr = ETH_VALID;
                    /* #Violation: Eth_c_REF_9*/
                    *timeStampPtr = ETH_RX_INFO(CtrlIdx, CoreId, DmaIdx).timeStamp;
                    /* #Violation: Eth_c_REF_9*/
                    ETH_RX_INFO(CtrlIdx, CoreId, DmaIdx).ingressTimeStampAvailable = FALSE;
                }
                ETH_EXIT_CRITICAL_SECTION(Eth_GetIngressTimeStamp);
                DataPtrValid = TRUE;
            }
        }
        /*check the parameter DataPtr is valid*/
        if ((FALSE == DataPtrValid) || (ETH_INVALID == *timeQualPtr))
        {
#if (ETH_DEV_ERROR_DETECT == STD_ON)

            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETINGRESSTIME, ETH_E_PARAM_POINTER);
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
            RetVal = E_NOT_OK;
        }
    }
    return RetVal;
}

#endif /* (ETH_GLOBAL_TIME_SUPPORT_API \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Eth_ProvideTxBuffer
 *
 *   Service ID              : 0x09.
 *
 *   Description             : Provides access to a transmit buffer of the FIFO related to the \
 *                             specified priority
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet
 *                                      Driver.
 *                             Priority:Frame priority for transmit buffer FIFO selection
 *
 *   Parameters inout        : LenBytePtr: In: desired length in bytes, out: granted length in bytes
 *
 *   Parameters out          : BufIdxPtr: Index to the granted buffer resource To be used for
 *                                        subsequent requests
 *                             BufPtr: Pointer to the granted buffer
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : BUFREQ_OK: Buffer request accomplished successful
 *                             BUFREQ_E_NOT_OK: Buffer request not successful. Buffer cannot be
 *                                             accessed
 *                             BUFREQ_E_BUSY: Temporarily no buffer available. It's up the
 *                                            requestor to retry request for a certain time
 *                             BUFREQ_E_OVFL:No Buffer of the required length can be provided
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00077.[SWS_Eth_00004]
 * [SWS_Eth_00078]The function shall provide a transmit buffer resource. The Ethernet Driver shall
lock the buffer until it receives a subsequent call of Eth_Transmit service with the buffer index
returned in the BufIdxPtr parameter.
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(BufReq_ReturnType, ETH_PUBLIC_CODE) Eth_ProvideTxBuffer
(
    uint8 CtrlIdx,
    uint8 Priority,    
    /* #Violation: Eth_c_REF_12 */
    P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_CONST) BufIdxPtr,
    /* #Violation: Eth_c_REF_12 */
    P2P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) BufPtr,
    /* #Violation: Eth_c_REF_12 */
    P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr
)
{
    BufReq_ReturnType BufferStatus;
    Mcal_CoreType     CoreId;
    uint32            FifoIdx;
    uint32            DmaIdx;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetVal;
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    BufferStatus = BUFREQ_E_NOT_OK;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();

#if (ETH_DEV_ERROR_DETECT == STD_ON)

    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_PROVIDETXBUFFER, CoreId);
    if (E_OK == RetVal)
    {
        /* SWS_Eth_00083/SWS_Eth_00084/SWS_Eth_00085 */
        if ((NULL_PTR == BufIdxPtr) || (NULL_PTR == LenBytePtr) || (NULL_PTR == BufPtr))
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDETXBUFFER, ETH_E_PARAM_POINTER);
        }
        else if (Priority > 7U)
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDETXBUFFER, ETH_E_INV_PARAM);
        }
        else

#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
        {
            /* #Violation: Eth_c_REF_9*/
            FifoIdx = ETH_GET_CHID_FROM_PRIORITY(CtrlIdx, CoreId, Priority);
#if (ETH_DEV_ERROR_DETECT == STD_ON)

            if (0xFFU == FifoIdx)
            {
                (void)Det_ReportError(
                    ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDETXBUFFER, ETH_E_INV_PARAM);
            }
            else
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
            {
                /* #Violation: Eth_c_REF_9*/
                DmaIdx = ETH_GET_CHID_FROM_FIFO(CtrlIdx, CoreId, FifoIdx);
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
                if ((*LenBytePtr) > ETH_NODE(CtrlIdx, CoreId).txChannelInfoPtr[DmaIdx].txBuffer1Size)
                {
                    /* If a buffer is requested with Eth_Hal_GetTxBuffer that is larger than the
                    available buffer length, then report an error and return available buffer length
                */
                    /* #Violation: Eth_c_REF_9*/
                    *LenBytePtr = ETH_NODE(CtrlIdx, CoreId).txChannelInfoPtr[DmaIdx].txBuffer1Size;
                    BufferStatus = BUFREQ_E_OVFL;
                }
                else
                {
                    /* Invoke and process the EthSwt APIs for management support*/
                    /*Switch driver frame preparation */
                    BufferStatus =
                        ETH_lSwtAdaptPrepFrame(CtrlIdx, DmaIdx, BufIdxPtr, BufPtr, LenBytePtr,CoreId);
                }
#else
                /* SWS_Eth_00079   larger than the available buffer length return the available length and
                * BUFREQ_E_OVFL*/
                /* \[SWS_Eth_00080]If all available buffers are in use the component shall return
                * BUFREQ_E_BUSY*/
                /* \[SWS_Eth_00004] A buffer index (BufIdx) indentifies an Ethernet buffer processed by
                Ethernet Driver API functions. Each controller buffers are identified by buffer
                indexes 0 to (n-1) where n is the number of buffers processed by the corresponding
                controller. Buffer indexes are valid within a tuple <CtrlIdx, BufIdx> only. A BufIdx
                uniquely identifies the buffer used for an Ethernet Driver.  */
                ETH_ENTER_CRITICAL_SECTION(Eth_ProvideTxBuffer);
                /* #Violation: Eth_c_REF_19*/
                BufferStatus = (BufReq_ReturnType)Eth_Hal_GetTxBuffer(
                    /* #Violation: Eth_c_REF_9*/
                    ETH_NODE_ADDR(CtrlIdx, CoreId),
                    /* #Violation: Eth_c_REF_19*/
                    (Eth_DmaChannel)DmaIdx,
                    BufIdxPtr,
                    BufPtr,
                    LenBytePtr);
                ETH_EXIT_CRITICAL_SECTION(Eth_ProvideTxBuffer);

                /* #Violation: Eth_c_REF_5*/
                *BufPtr += ETH_FRAMEHEADER_LENGTH;
                if (BUFREQ_OK == BufferStatus)
                {   /* #Violation: Eth_c_REF_9*/
                   /* #Violation: Eth_c_REF_19*/
                    if (ETH_TX_DESC_NOUSE != ETH_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, *BufIdxPtr))
                    {
                        BufferStatus = BUFREQ_E_BUSY;
                    }
                    else
                    {
                        /* #Violation: Eth_c_REF_9*/
                        ETH_SET_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, *BufIdxPtr, ETH_TX_DESC_ASSIGNED);
                    }
                }
#endif

                /* Provide Buffer index and buffer pointer to application
                Set buffer used, TimeStamp not enabled, store the length requested */
                *BufIdxPtr = ((uint32)FifoIdx << 13U) | (*BufIdxPtr);
            }

        }
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */

    return BufferStatus;
}

/****************************************************************************************************
 *   Function Name           : Eth_Transmit
 *
 *   Service ID              : 0x0a.
 *
 *   Description             : Triggers transmission of a previously filled transmit buffer. The 
 *                             function requires previous buffer request (Eth_ProvideTxBuffer).and 
 *                             must invoke Eth_TxConfirmation in ISR or mainfunction.
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet 
 *                                      Driver
 *                             BufIdx: Index of the buffer resource
 *                             FrameType: Ethernet frame type
 *                             TxConfirmation: Activates transmission confirmation
 *                             LenByte: Data length in byte.
 *                             PhysAddrPtr: Physical target address (MAC address) in network byte 
 *                                          order
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : ASynchronous. Depend on HW.
 *
 *   Reentrancy              : Reentrant for different buffer indexes and Ctrl indexes
 *
 *   Return value            : E_OK: success
 *                             E_NOT_OK: transmission failed
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00087.
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_Transmit
(
    uint8          CtrlIdx,
    /* #Violation: Eth_c_REF_13 */
    Eth_BufIdxType BufIdx,
    Eth_FrameType  FrameType,
    boolean        TxConfirmation,
    uint16         LenByte,
    /* #Violation: Eth_c_REF_12 */
    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr
)
{
    Std_ReturnType          RetVal;
    Mcal_CoreType           CoreId;
    uint32                  FrameLen;
    volatile uint8         *BufPtr;
    Eth_TxDescr const volatile    *pCurDescr;
    uint8                   Offset;
    uint32                  PtrIndex;
    uint8                   Macaddr[ETH_MAC_ADDR_LEN];
    Eth_TxdescTxConfirmType TxdescTxConfirmState;
    uint8                   PriorityId;
    uint8                   DmaIdx;
    uint8                   BufferIdx;
    boolean                 RegCheck;
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
    uint16 TxBufLengthConfig;
#endif
    PtrIndex = 0U;
    RegCheck = TRUE;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
    PriorityId = (uint8)((BufIdx & 0xFFFFE000U) >> 13U);
    BufferIdx = (uint8)(BufIdx & ETH_BUFIDX_MASK);

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_TRANSMIT, CoreId);
    if (E_OK == RetVal)
    {
        RetVal = Eth_CheckTransParam(CtrlIdx, PriorityId, CoreId, BufferIdx, PhysAddrPtr);
    }
    if (E_OK == RetVal)
#endif /* End for ETH_DEV_ERROR_DETECT */
    {
        /* #Violation: Eth_c_REF_9*/
        DmaIdx = ETH_GET_CHID_FROM_FIFO(CtrlIdx, CoreId, PriorityId);

        /* #Violation: Eth_c_REF_9*/
        /* #Violation: Eth_c_REF_19*/
        TxdescTxConfirmState = ETH_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, BufferIdx);
        if (ETH_TX_DESC_ASSIGNED != TxdescTxConfirmState)
        {
#if (ETH_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_INV_PARAM);
#endif /* End for ETH_DEV_ERROR_DETECT */
            RetVal = E_NOT_OK;
        }
        else
        {
            pCurDescr =
            /* #Violation: Eth_c_REF_9 */
            /* #Violation: Eth_c_REF_14 */
                &(ETH_NODE(CtrlIdx, CoreId).txChannelInfoPtr[DmaIdx].pTxBaseDescriptor[BufferIdx]);

            /* #Violation: Eth_c_REF_4*/
            /* #Violation: Eth_c_REF_18 */
            BufPtr = (uint8 *)(pCurDescr->TDES0.U);
            for (Offset = MCAL_ZERO; Offset < ETH_MAC_ADDR_LEN; Offset++)
            {
                BufPtr[PtrIndex] = PhysAddrPtr[Offset];
                PtrIndex += 1U;
            }
            /* Copy PHYs MAC address as source address in TX EthFrame */
            /* \[SWS_Eth_00088] The function shall build the Ethernet header with the given physical
            target address (MAC address) and trigger the transmission of a previously filled transmit
            buffer*/
            /* #Violation: Eth_c_REF_9*/
            Eth_Hal_GetMacAddress(ETH_NODE_ADDR(CtrlIdx, CoreId), Macaddr);
            for (Offset = MCAL_ZERO; Offset < ETH_MAC_ADDR_LEN; Offset++)
            {
                BufPtr[PtrIndex] = Macaddr[Offset];
                PtrIndex += 1U;
            }

#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)

            ETH_BUF_IDX_SWT_DATA_PTR(CtrlIdx, CoreId, DmaIdx, BufferIdx) = (uint8 *)&BufPtr[PtrIndex];
            ETH_BUF_IDX_SWT_TXLEN(CtrlIdx, CoreId, DmaIdx, BufferIdx) = LenByte;
            /* Invoke the switch driver API is to insert management information */
            RetVal = EthSwt_EthTxProcessFrame(
                CtrlIdx,
                BufferIdx,
                &ETH_BUF_IDX_SWT_DATA_PTR(CtrlIdx, CoreId, DmaIdx, BufferIdx),
                &ETH_BUF_IDX_SWT_TXLEN(CtrlIdx, CoreId, DmaIdx, BufferIdx));

            /* Management info inserted into the frame by the switch driver */
            /*Is E_OK returned by the EthSwt_EthTxProcessFrame API  */
            if (RetVal == E_OK)
            {
                /* Get the configured Tx buffer size */
                TxBufLengthConfig = ETH_NODE(CtrlIdx, CoreId).txChannelInfoPtr[DmaIdx].txBuffer1Size;

                /* If the modified length exceeds the configured buffer size or
                if the modified length is reduced from the actual requested length */
                if ((ETH_BUF_IDX_SWT_TXLEN(CtrlIdx, CoreId, DmaIdx, BufferIdx) >
                     (TxBufLengthConfig -
                      ((uint16)(ETH_FRAMEHEADER_LENGTH + ETH_FRAMECHKSUM_LENGTH)))) ||
                    ((ETH_BUF_IDX_SWT_TXLEN(CtrlIdx, CoreId, DmaIdx, BufferIdx) < LenByte)))
                {
                    /* Error - incorrect length modification by the switch driver */
                    RetVal = E_NOT_OK;
                }
                /* Is data pointer modified by the switch driver correct? */
                else if (
                    ETH_BUF_IDX_SWT_DATA_PTR(CtrlIdx, CoreId, DmaIdx, BufferIdx) !=
                    (uint8 *)(&BufPtr[PtrIndex+((ETH_BUF_IDX_SWT_TXLEN(CtrlIdx, CoreId, DmaIdx, BufferIdx) - LenByte))]))
                {
                    /* Error due to incorrect data pointer modification by the
                       switch driver */
                    RetVal = E_NOT_OK;
                }
                else
                {
                    /* Increment the buffer address by the number of bytes of
                       management information needed */
                    BufPtr =
                        (uint8 *)(&BufPtr
                                      [PtrIndex +
                                       ETH_BUF_IDX_SWT_TXLEN(CtrlIdx, CoreId, DmaIdx, BufferIdx) -
                                       LenByte]);
                }
            }

            /* Is return value E_OK ? */
            if (RetVal == E_OK)
#endif /* (ETH_SWT_MANAGEMENT_SUPPORT \== STD_ON) */
            {
                /* Fill the Frame Type in TX/Frame Buffer */
                BufPtr[PtrIndex] = (uint8)((FrameType >> 8U));
                PtrIndex++;
                BufPtr[PtrIndex] = (uint8)(FrameType & 0xFFU);
#if (ETH_OFFLOAD_CHECKSUM == STD_ON)
                Eth_CheckForICMPV4Frame(FrameType, pCurDescr);
#endif /* (ETH_OFFLOAD_CHECKSUM \== STD_ON) */

#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_OFF)
                FrameLen = (uint32)LenByte + ETH_FRAMEHEADER_LENGTH;

#else
                /*Buffer2 size would be zero, single buffer and single frame at the time.
                Here Header length(ETH_FRAMEHEADER_LENGTH) is added because
                provideTxbuffer API only provides the Payload buffer.*/
                FrameLen = ((ETH_BUF_IDX_SWT_TXLEN(CtrlIdx, CoreId, DmaIdx, BufferIdx) +
                   ETH_FRAMEHEADER_LENGTH) &
                  (uint32)ETH_DMA_TX_DESC_PAC_LEN_MASK);
#endif
                RegCheck &= Eth_Hal_Transmit(
                /* #Violation: Eth_c_REF_9*/
                    ETH_NODE_ADDR(CtrlIdx, CoreId),            
                    /* #Violation: Eth_c_REF_19*/
                    (Eth_DmaChannel)DmaIdx,
                    BufferIdx,
                    BufferIdx,
                    FrameLen);

                /* configure the first descriptor */
                if (TRUE == TxConfirmation)
                {
                    /* #Violation: Eth_c_REF_9*/
                    ETH_SET_BUF_IDX_STATE(
                        CtrlIdx, CoreId, DmaIdx, BufferIdx, ETH_TX_DESC_TRANSMIT_WITH_CONFIRM);
                }
                else
                {
                    /* SWS_Eth_00089 */
                    /* #Violation: Eth_c_REF_9*/
                    ETH_SET_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, BufferIdx, ETH_TX_DESC_NOUSE);
                }
                RetVal = E_OK;
#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)
                /* Tx finished indication to Switch*/
                RetVal = EthSwt_EthTxFinishedIndication(CtrlIdx, BufferIdx);
#endif
                if (FALSE == RegCheck)
                {
                    RetVal = E_NOT_OK;
#if (ETH_SAFETY_ENABLE == STD_ON)
                    (void)Det_ReportRuntimeError(
                        ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_REG_CHECK_FAIL);
#endif /* (ETH_SAFETY_ENABLE \== STD_ON)*/
                }
            }
        }
    }

    return RetVal;
}

#if (ETH_SWT_MANAGEMENT_SUPPORT == STD_ON)

/****************************************************************************************************
 *   Function Name           : ETH_lChkSwtRxFrmParam
 *
 *   Service ID              : None.
 *
 *   Description             : Checks the validity of modified parameters by the switch API
 *                             EthSwt_EthRxProcessFrame
  Parameters (in)            : RxActualLen - Actual length of the received frame        
 *                             RxModifiedLen - Length modified by                       
 *                                    EthSwt_EthRxProcessFrame API            
 *                             EthTypeAddrPtr - Pointer to the address of EthType field 
 *                             BufferPtr - Address of the receive buffer
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant
 *
 *   Return value            : E_OK: success
 *                             E_NOT_OK: transmission failed
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
LOCAL_INLINE Std_ReturnType ETH_lChkSwtRxFrmParam
(
    const uint16       RxActualLen,
    const uint16       RxModifiedLen,
    const uint8 *const EthTypeAddrPtr,
    const uint8 *const BufferPtr
)
{
    Std_ReturnType RetVal;

    /* if length is incremented from the actual received length or
     * length is modified below the minimum length */
    if ((RxModifiedLen > RxActualLen) || (RxModifiedLen < 18U))
    {
        RetVal = E_NOT_OK;
    }
    /* Address is not updated correctly by the EthSwt driver */
    else if (
        EthTypeAddrPtr !=
        (uint8
             *)((uint32) & (BufferPtr[ETH_FRAME_TYPE_MSB_POS]) + (uint32)(RxActualLen - RxModifiedLen)))
    {
        RetVal = E_NOT_OK;
    }
    else
    {
        RetVal = E_OK;
    }

    return RetVal;
}

/****************************************************************************************************
 *   Function Name           : ETH_lSwtAdaptPrepFrame
 *
 *   Service ID              : .
 *
 *   Description             : Function to provide the switch management support functionality in
                               ETH_ProvideTxBuffer API
*    Parameters (in)         : CtrlIdx - Index of the controller
                               PrioMapIdx - Internal FIFO reference index
     Parameters (inout)      : BufPtr - Pointer to the granted buffer. In case of invalid parameter
                               modification of EthSwt API, the existing value is restored. 
                               LenBytePtr- Pointer to the length in bytes. In case of invalid parameter 
                                 modification of EthSwt API, the existing value at the address is
    restored. Parameters (out): BufIdxPtr - Address where the granted buffer index is  stored
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Non Reentrant
 *
 *   Return value            : BUFREQ_OK       - Successfully granted buffer
**                             BUFREQ_E_NOT_OK - Error detected
**                             BUFREQ_E_OVFL - Requested additional size by EthSwt  driver too large
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : .
 ****************************************************************************************************/

static BufReq_ReturnType ETH_lSwtAdaptPrepFrame(
    const uint8           CtrlIdx,
    const uint8           PrioMapIdx,
    Eth_BufIdxType *const BufIdxPtr,
    uint8 **const         BufPtr,
    uint16 *const         LenBytePtr,
    Mcal_CoreType  CoreId)
{
    volatile uint8                      *TxBuffBasePtr;
    uint8                                     *EthBufPtr;
    uint8                                     *ModEthBufPtr;
    BufReq_ReturnType                          BufferStatus;
    Eth_BufIdxType                             EthBufIdx;
    uint16                                     TxBufLengthAligned;
    uint16                                     TxBufLengthConfig;
    uint16                                     CurrTxBufIdx;
    uint16                                     LenBytes;
    uint16                                     ModLenBytes;
    Std_ReturnType                             SwtRetVal;
    volatile Eth_TxDescr   *pCurDescr;
    /* Get controller status */
    /* Get configured buffer length */
    TxBufLengthConfig = ETH_NODE(CtrlIdx, CoreId).txChannelInfoPtr[PrioMapIdx].txBuffer1Size;

    LenBytes = *LenBytePtr;

    /* Invoke EthSwt_EthTxAdaptBufferLength API*/
    EthSwt_EthTxAdaptBufferLength(LenBytePtr);

    /* Make a copy and restore the requested length to LenBytePtr */
    ModLenBytes = *LenBytePtr;
    *LenBytePtr = LenBytes;

    /* If the modified length exceeds the configured buffer size */
    if (ModLenBytes >
        (TxBufLengthConfig - ((uint16)(ETH_FRAMEHEADER_LENGTH + ETH_FRAMECHKSUM_LENGTH))))
    {
        /* Fill output parameter 'LenBytePtr' as
           Allocated Tx Buffer Size - Frame Header and CRC) */
        *LenBytePtr = TxBufLengthConfig - ((uint16)(ETH_FRAMEHEADER_LENGTH + ETH_FRAMECHKSUM_LENGTH));

        /* BufferStatus - modified buffer size too large */
        BufferStatus = BUFREQ_E_OVFL;
    }
    /* if the modified length is reduced from the actual requested length*/
    else if (ModLenBytes < LenBytes)
    {
        /* BufferStatus - Error detected due to incorrect length
           modification by the switch driver */
        BufferStatus = BUFREQ_E_NOT_OK;
    }
    else
    {
        /* Read the buffer index from the queue (Queue front should not move here
         * as the validation of the modified parameters from Switch API is not
         * yet done */
        CurrTxBufIdx = ETH_NODE_ADDR(CtrlIdx, CoreId)->txChannelInfoPtr[PrioMapIdx].descIndex;
        pCurDescr = ETH_NODE_ADDR(CtrlIdx, CoreId)->txChannelInfoPtr[PrioMapIdx].pTxDescriptor;

        /* Provide Buffer index and buffer pointer to application
           Set buffer used, Transmission not yet requested, no confirmation. */
        EthBufIdx = ((uint32)PrioMapIdx << ETH_FIFOIDX_POS) | (CurrTxBufIdx);

        TxBuffBasePtr = (uint8 *)&pCurDescr->TDES0.U;

        TxBufLengthAligned = ETH_NODE_ADDR(CtrlIdx, CoreId)->txChannelInfoPtr[PrioMapIdx].txBuffer1Size;

        /* Make a copy of the existing address to restore in error scenario */
        EthBufPtr = *BufPtr;

        /*Store requested buffer length to check after invocation of Tx Prepare
        Frame API*/
        *BufPtr =
            (uint8
                 *)(((uint32)TxBuffBasePtr + ((uint32)CurrTxBufIdx * TxBufLengthAligned)) + (uint32)ETH_FRAME_TYPE_MSB_POS);

        /* [cover parentID={63394BF9-B5F5-41fe-B455-7AE5CF9D1A7E}]
        Invoke the EthSwt_EthTxPrepareFrame API for Tx frame preparation
        [/cover] */
        SwtRetVal = EthSwt_EthTxPrepareFrame(CtrlIdx, EthBufIdx, BufPtr, LenBytePtr);

        /* Make a copy and restore the requested length to LenBytePtr and
         * address to the initial value */
        ModLenBytes = *LenBytePtr;
        *LenBytePtr = LenBytes;
        ModEthBufPtr = *BufPtr;
        *BufPtr = EthBufPtr;

        /* Is Frame successfully prepared by the switch driver (return value - E_OK)*/
        if (SwtRetVal == E_OK)
        {
            /* If the modified length exceeds the configured buffer size*/
            if (ModLenBytes >
                (TxBufLengthConfig - ((uint16)(ETH_FRAMEHEADER_LENGTH + ETH_FRAMECHKSUM_LENGTH))))
            {
                /* Fill output parameter 'LenBytePtr' as
                   Allocated Tx Buffer Size - Frame Header and CRC) */
                *LenBytePtr =
                    TxBufLengthConfig - ((uint16)(ETH_FRAMEHEADER_LENGTH + ETH_FRAMECHKSUM_LENGTH));

                /* BufferStatus - modified buffer size too large */
                BufferStatus = BUFREQ_E_OVFL;
            }
            /* if the modified length is reduced from the actual requested length */
            else if (ModLenBytes < LenBytes)
            {
                /* BufferStatus - Error detected due to incorrect length
                   modification by the switch driver */
                BufferStatus = BUFREQ_E_NOT_OK;
            }
            /*Is Buffer pointer modified by the TxPrep frame API correct ?*/
            else if (
                ModEthBufPtr !=
                (uint8
                     *)(((uint32)TxBuffBasePtr + ((uint32)CurrTxBufIdx * TxBufLengthAligned) + (uint32)ETH_FRAME_TYPE_MSB_POS) + (uint32)(ModLenBytes - LenBytes)))
            {
                /* BufferStatus - Error detected due to incorrect data pointer
                   modification by the switch driver */
                BufferStatus = BUFREQ_E_NOT_OK;
            }
            else
            {

                /* #Violation: Eth_c_REF_9*/
                ETH_SET_BUF_IDX_STATE(CtrlIdx, CoreId, PrioMapIdx, *BufIdxPtr, ETH_TX_DESC_ASSIGNED);
                
                /* Provide the buffer index, address of the granted buffer as the
                output parameters */
                *BufIdxPtr = EthBufIdx;

                *BufPtr = (uint8 *)(&ModEthBufPtr[ETH_ETHERTYPE_LEN]);

                /* Update Buffer status as BUFREQ_OK*/
                BufferStatus = BUFREQ_OK;
            }
        }
        else
        {
            /* Frame preparation failed in the Swt driver */
            /* Update buffer status as BUFREQ_E_NOT_OK */
            BufferStatus = BUFREQ_E_NOT_OK;
        }
    }

    return BufferStatus;
}

#endif /* (ETH_SWT_MANAGEMENT_SUPPORT \== STD_ON) */







/****************************************************************************************************
 *   Function Name           : Eth_Receive
 *
 *   Service ID              : 0x0b.
 *
 *   Description             : Receive a frame from the related fifo.
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet 
 *                                      Driver 
 *                             FifoIdx: Specifies the related fifo
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : RxStatusPtr: Indicates whether a frame has been received and if so,
 *                                          whether more frames are available for the related fifo.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant for different FIFOs. Non Reentrant for the same FIFO.
 *
 *   Return value            : void
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00095.[SWS_Eth_00244]
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(void, ETH_PUBLIC_CODE) Eth_Receive
(
    uint8 CtrlIdx, 
    uint8 FifoIdx,
    /* #Violation: Eth_c_REF_12 */
    P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr
)
{
    Mcal_CoreType   CoreId;
    uint8            DmaIdx;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetVal;
#endif
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_RECEIVE, CoreId);
    if (E_OK == RetVal)
    {
        if ((NULL_PTR == RxStatusPtr)||(FifoIdx >= ETH_CTRL0_RXSCHEDULED_CFGD))
        {
            (void)Det_ReportError(
                ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_RECEIVE, ETH_E_PARAM_POINTER);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /* End for ETH_DEV_ERROR_DETECT */
    {
        *RxStatusPtr = ETH_NOT_RECEIVED;
        /* If Tx Isr is enabled then confirmation is done in ISR */
        /* #Violation: Eth_c_REF_9*/
        if (FALSE == ETH_RXIRQ_IS_ENABLED(CtrlIdx, CoreId))
        {
            /* #Violation: Eth_c_REF_9*/
            DmaIdx = ETH_GET_CHID_FROM_RXFIFO(CtrlIdx, CoreId, FifoIdx);

            *RxStatusPtr = Eth_ReciveProcess(CtrlIdx,CoreId,DmaIdx);
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Eth_TxConfirmation
 *
 *   Service ID              : 0x0C.
 *
 *   Description             : This function triggers frame transmission confirmation
 *
 *   Parameters in           : CtrlIdx: Index of the controller within the context of the Ethernet
 *Driver
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Eth_00100.
****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(void, ETH_PUBLIC_CODE) Eth_TxConfirmation(uint8 CtrlIdx)
{
    Mcal_CoreType CoreId;
    uint8         Index;
    uint8         DmaIdx;
    Eth_Status    EthCtlStatus;
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetVal;
#endif

    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_TXCONFIRMATION, CoreId);
    if (E_OK == RetVal)
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        /* If Tx Isr is enabled then confirmation is done in ISR */
        /* #Violation: Eth_c_REF_9*/
        if (FALSE == ETH_TXIRQ_IS_ENABLED(CtrlIdx, CoreId))
        {
            /* #Violation: Eth_c_REF_9*/
            for (DmaIdx = MCAL_ZERO; DmaIdx < ETH_GET_MAX_TXDMA_NUM(CtrlIdx, CoreId); DmaIdx++)
            {
                /* \[SWS_Eth_00101] all filled transmit buffers for successful transmission */
                /* #Violation: Eth_c_REF_9*/
                for (Index = MCAL_ZERO; Index < ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, DmaIdx);
                     Index++)
                {

                               
                    if (ETH_TX_DESC_TRANSMIT_WITH_CONFIRM ==
                        /* #Violation: Eth_c_REF_9*/
                        /* #Violation: Eth_c_REF_19*/
                        ETH_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, Index))
                    {
                        EthCtlStatus = Eth_Hal_GetTxStatus(
                        /* #Violation: Eth_c_REF_9*/
                            ETH_NODE_ADDR(CtrlIdx, CoreId),            
                            /* #Violation: Eth_c_REF_19*/
                            (Eth_DmaChannel)DmaIdx,
                            Index,
                            Index,
                            /* #Violation: Eth_c_REF_9*/
                            &ETH_TX_INFO(CtrlIdx, CoreId, DmaIdx));
                        /* \[SWS_Eth_00243].Ethernet SW Driver shall call EthIf_TxConfirmation with
                       Result set to E_OK to indicate a successful transmission; either from the
                       Interrupt routine (in interrupt mode) or from the Eth_TxConfirmation routine
                       in polling mode (if the notification has been enabled) */
                        /*release without error*/
                        if (ETH_STATUS_OK == EthCtlStatus)
                        {
                            EthIf_TxConfirmation(CtrlIdx, Index, E_OK);
                            /* \[SWS_Eth_00089] *[SWS_Eth_00102]
                            If transmission confirmation was enabled by a previous call to
                            Eth_Transmit function the function shall release the buffer resource*/
                            /* free */
                            /* #Violation: Eth_c_REF_9*/
                            ETH_SET_BUF_IDX_STATE(CtrlIdx, CoreId, DmaIdx, Index, ETH_TX_DESC_NOUSE);
                        }
                        /*release with error include busy.*/
                        else
                        {
                            if (ETH_STATUS_ERROR == EthCtlStatus)
                            {
                                /* \[SWS_Eth_00256]Ethernet SW Driver shall call EthIf_TxConfirmation
                                with Result set to E_NOT_OK if the transmission failed.*/
                                EthIf_TxConfirmation(CtrlIdx, Index, E_NOT_OK);
                                /* #Violation: Eth_c_REF_9*/
                                ETH_SET_BUF_IDX_STATE(
                                    CtrlIdx, CoreId, DmaIdx, Index, ETH_TX_DESC_NOUSE);
                            }
                        }
                    }
                }
            }
        }
    }
}

#if (ETH_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Eth_GetVersionInfo
 *
 *   Service ID              : 0x0D.
 *
 *   Description             : This function returns the version information
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : VersionInfoPtr: Version information of this module
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00106.
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(void, ETH_PUBLIC_CODE) Eth_GetVersionInfo
(
    /* #Violation: Eth_c_REF_12 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA) VersionInfoPtr
)
{
    /* SWS_Eth_00136 If development error detection is enabled: the function shall check the parameter
    VersionInfoPtr for being valid. If the check fails, the function shall raise the
    development error ETH_E_PARAM_POINTER*/
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == VersionInfoPtr)
    {
        (void)Det_ReportError(
            ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GETVERSIONINFO, ETH_E_PARAM_POINTER);
    }
    else
#endif /* (ETH_DEV_ERROR_DETECT \== STD_ON) */
    {
        VersionInfoPtr->vendorID = ETH_VENDOR_ID;
        VersionInfoPtr->moduleID = ETH_MODULE_ID;
        VersionInfoPtr->sw_major_version = ETH_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = ETH_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = ETH_SW_PATCH_VERSION;
    }
}
#endif

/****************************************************************************************************
 *   Function Name           : Eth_MainFunction
 *
 *   Service ID              : 0x20.
 *
 *   Description             : The function checks for controller errors and lost frames. Used for 
 *                             polling state changes. Calls EthIf_CtrlModeIndication when the 
 *                             controller mode changed.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : 
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Eth_00171.
 *   [SWS_Eth_00240] Since Mcu_SetMode is a synchronous interface, EthIf_CtrlModeIndication is called 
 *   in Mcu_SetMode.  
 ****************************************************************************************************/
/* #Violation: Eth_c_REF_10*/
FUNC(void, ETH_PUBLIC_CODE) Eth_MainFunction(void)
{
    uint8           CtrlIdx;
    Mcal_CoreType   CoreId;
    Eth_StatusType const *Eth_StatusPtr;
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
    /*EB guarantee Eth_StatusPtr is not NULL_PTR*/
    Eth_StatusPtr = Eth_CoreChannelStatusPtr[CoreId];

    if ((NULL_PTR != Eth_ConfigPtr) && (NULL_PTR != Eth_StatusPtr))
    {
        /* #Violation: Eth_c_REF_9*/
        /* #Violation: Eth_c_REF_17*/
        for (CtrlIdx = 0; CtrlIdx < ETH_CTRL_NUM(CoreId); CtrlIdx++)
        {
            /*SWS_Eth_00169 The function shall check for lost frames. If the check fails, the
                function shall raise the extended production error event ETH_E_RX_FRAMES_LOST
                SWS_Eth_00172 The function shall check for controller errors (e.g. CRC errors).
                If the check fails, the function shall raise the extended production error event
                as defined in section 7.2.2 Extended Production Errors (e.g. ETH_E_CRC)*/
            /* \[SWS_Eth_00219]*/
            /*SWS_Eth_00172 The function shall check for controller errors (e.g. CRC errors).
            If the check fails, the function shall raise the extended production error event
            as defined in section 7.2.2 Extended Production Errors (e.g. ETH_E_CRC)*/
            /* #Violation: Eth_c_REF_9*/
            if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemCRC)
            {
                Eth_DemReportError(
                    &(Eth_StatusPtr->ControllerStatePtr->DemErrorCnt.EthDemCRCCnt),
                    /* #Violation: Eth_c_REF_9*/
                    ETH_NODE(CtrlIdx, CoreId).pEthModule->RX_CRC_ERROR_PACKETS.B.RXCRCERR,
                    /* #Violation: Eth_c_REF_9*/
                    ETH_DEM(CtrlIdx, CoreId)->EthDemCRC);
            }

            /* \[SWS_Eth_00174]*/
            /*SWS_Eth_00169 The function shall check for lost frames. If the check fails, the
            unction shall raise the extended production error event ETH_E_RX_FRAMES_LOST */
            /* #Violation: Eth_c_REF_9*/
            if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemFramesLost)
            {
                Eth_DemReportError(
                    &(Eth_StatusPtr->ControllerStatePtr->DemErrorCnt.EthDemFramesLostCnt),
                    /* #Violation: Eth_c_REF_9*/
                    ETH_NODE(CtrlIdx, CoreId).pEthModule->RX_FIFO_OVERFLOW_PACKETS.B.RXFIFOOVFL,
                    /* #Violation: Eth_c_REF_9*/
                    ETH_DEM(CtrlIdx, CoreId)->EthDemFramesLost);
            }

            /* \[SWS_Eth_00220]*/
            /* #Violation: Eth_c_REF_9*/
            if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemUndersize)
            {
                Eth_DemReportError(
                    &(Eth_StatusPtr->ControllerStatePtr->DemErrorCnt.EthDemUndersizeCnt),
                    /* #Violation: Eth_c_REF_9*/
                    ETH_NODE(CtrlIdx, CoreId).pEthModule->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG,
                    /* #Violation: Eth_c_REF_9*/
                    ETH_DEM(CtrlIdx, CoreId)->EthDemUndersize);
            }
            /* \[SWS_Eth_00221]*/

            /* #Violation: Eth_c_REF_9*/
            if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemOversize)
            {
                Eth_DemReportError(
                    &(Eth_StatusPtr->ControllerStatePtr->DemErrorCnt.EthDemOversizeCnt),
                    /* #Violation: Eth_c_REF_9*/
                    ETH_NODE(CtrlIdx, CoreId).pEthModule->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG,
                    /* #Violation: Eth_c_REF_9*/
                    ETH_DEM(CtrlIdx, CoreId)->EthDemOversize);
            }

            /* \[SWS_Eth_00222] */

            /* #Violation: Eth_c_REF_9*/
            if (ETH_DISABLE_DEM_REPORT != ETH_DEM(CtrlIdx, CoreId)->EthDemAlignment)
            {
                Eth_DemReportError(
                    &(Eth_StatusPtr->ControllerStatePtr->DemErrorCnt.EthDemAlignmentCnt),
                    /* #Violation: Eth_c_REF_9*/
                    ETH_NODE(CtrlIdx, CoreId).pEthModule->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR,
                    /* #Violation: Eth_c_REF_9*/
                    ETH_DEM(CtrlIdx, CoreId)->EthDemAlignment);
            }

            if (ETH_HALFDUPLEX_MODE ==
                Eth_ConfigPtr->EthCoreConfigPtr[CoreId]
                    ->EthCtrlConfigPtr[CtrlIdx]
                    .EthSdkCtrlConfigPtr->mac.duplexMode)

            {
                /* \[SWS_Eth_00223]*/

                Eth_HalfDuplexDemReportErr(CoreId, CtrlIdx, Eth_StatusPtr);
            }
        }
    }
    
}

/****************************************************************************************************
 *   Function Name           : Eth_RX_ISRHandler
 *
 *   Service ID              : (0x41U)
 *
 *   Description             : This service routine invokes the required function
 *                             based on the channel configuration for further
 *                             calculations. It is called by ISR
 *
 *   Parameters in           : Channel:Eth channel ID
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :  [SWS_Eth_00244].
 ****************************************************************************************************/
#if (ETH_ENA_RX_INT == STD_ON)
FUNC(void, ETH_FAST_CODE) Eth_RX_ISRHandler
(
    uint8 CtrlIdx, 
    uint8 ChannelId
)
{
    uint32           Irq;
    Mcal_CoreType    CoreId;
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetVal;
#endif
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_RX_ISR, CoreId);
    if (E_OK == RetVal)
    {
        if(ChannelId > ETH_GET_MAX_RXDMA_NUM(CtrlIdx, CoreId))
        {
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_RX_ISR, ETH_E_INV_PARAM);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif /*(ETH_DEV_ERROR_DETECT \== STD_ON)*/
    {
        /* Get interrupt status */
        /* #Violation: Eth_c_REF_9*/
        Irq = Eth_Hal_GetDmaInterruptStatus(ETH_NODE_ADDR(CtrlIdx, CoreId), (Eth_DmaChannel)ChannelId);
        while ((Irq & (ETH_DMA_CH_STAT_RI_SET | ETH_DMA_CH_STAT_RBU_SET)) != MCAL_ZERO)
        {
            /* Clear interrupt status */
            /* #Violation: Eth_c_REF_9*/
            Eth_Hal_ClearDmaInterruptStatus(
                ETH_NODE_ADDR(CtrlIdx, CoreId),
                (Eth_DmaChannel)ChannelId,
                ETH_DMA_CH_STAT_RI_RESET | ETH_DMA_CH_STAT_NIS_RESET |
                    ETH_DMA_CH_STAT_RBU_ERI_AIE_RESET);

            Eth_ReciveProcess(CtrlIdx, CoreId, ChannelId);
            /* Is there a new frame come in */
            Irq = 0U; /* break */
        }
    }
}
#endif /* (ETH_ENA_RX_INT \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Eth_TX_ISRHandler
 *
 *   Service ID              : (0x40U)
 *
 *   Description             : This service routine invokes the required function
 *                             based on the channel configuration for further
 *                             calculations. It is called by ISR
 *
 *   Parameters in           : Channel:Eth channel ID
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     :
 ****************************************************************************************************/

#if (ETH_ENA_TX_INT == STD_ON)
FUNC(void, ETH_FAST_CODE) Eth_TX_ISRHandler
(
    uint8 CtrlIdx, 
    uint8 ChannelId
)
{
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Eth_StatusType *Eth_StatusPtr;
#endif
    Mcal_CoreType   CoreId;
    uint32          Index;
    uint32          Irq;
    uint32          Loop;
    Eth_Status      EthStatus;
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType RetVal;
#endif    
    /* #Violation: Eth_c_REF_9*/
    CoreId = Mcal_GetCoreId();
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    RetVal = Eth_DetCheck(CtrlIdx, ETH_SID_TX_ISR, CoreId);

    if (E_OK == RetVal)
    {
        if(ChannelId > ETH_GET_MAX_TXDMA_NUM(CtrlIdx, CoreId))
        {
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TX_ISR, ETH_E_INV_PARAM);
            RetVal = E_NOT_OK;
        }
    }
    if (E_OK == RetVal)
#endif
    {
        Loop = 0U;
        /* Get interrupt status */
        /* #Violation: Eth_c_REF_9*/
        Irq = Eth_Hal_GetDmaInterruptStatus(ETH_NODE_ADDR(CtrlIdx, CoreId), (Eth_DmaChannel)ChannelId);
        while (MCAL_ZERO != (ETH_DMA_CH_STAT_TI_SET & Irq))
        {
            /* Clear interrupt status */
            /* #Violation: Eth_c_REF_9*/
            Eth_Hal_ClearDmaInterruptStatus(
                ETH_NODE_ADDR(CtrlIdx, CoreId),
                (Eth_DmaChannel)ChannelId,
                ETH_DMA_CH_STAT_TI_RESET | ETH_DMA_CH_STAT_NIS_RESET);
            /* Loop all Tx descriptor */

            /* \[SWS_Eth_00101] all filled transmit buffers for successful transmission */
            /* #Violation: Eth_c_REF_9*/
            for (Index = MCAL_ZERO; Index < ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, ChannelId);
                 Index++)
            {
                /* #Violation: Eth_c_REF_9*/
                if (ETH_TX_DESC_TRANSMIT_WITH_CONFIRM ==
                    ETH_BUF_IDX_STATE(CtrlIdx, CoreId, ChannelId, Index))
                {
                    /* #Violation: Eth_c_REF_9*/
                    EthStatus = Eth_Hal_GetTxStatus(
                        ETH_NODE_ADDR(CtrlIdx, CoreId),
                        (Eth_DmaChannel)ChannelId,
                        Index,
                        Index,
                        &ETH_TX_INFO(CtrlIdx, CoreId, ChannelId));
                    /* \[SWS_Eth_00243].Ethernet SW Driver shall call EthIf_TxConfirmation with
                    Result set to E_OK to indicate a successful transmission; either from the
                    Interrupt routine (in interrupt mode) or from the Eth_TxConfirmation routine
                    in polling mode (if the notification has been enabled) */
                    /*release without error*/
                    if (ETH_STATUS_OK == EthStatus)
                    {
                        EthIf_TxConfirmation(CtrlIdx, Index, E_OK);
                        /* \[SWS_Eth_00089] */ /* free */
                        /* #Violation: Eth_c_REF_9*/
                        ETH_SET_BUF_IDX_STATE(CtrlIdx, CoreId, ChannelId, Index, ETH_TX_DESC_NOUSE);
                    }
                    else
                    {
                        if (ETH_STATUS_ERROR == EthStatus)
                        {
                            EthIf_TxConfirmation(CtrlIdx, Index, E_NOT_OK);
                            /* \[SWS_Eth_00089] */ /* free */
                            /* #Violation: Eth_c_REF_9*/
                            ETH_SET_BUF_IDX_STATE(
                                CtrlIdx, CoreId, ChannelId, Index, ETH_TX_DESC_NOUSE);
                        }
                    }
                }
            }

            /* Is there a new frame that be transmited */
            /* #Violation: Eth_c_REF_9*/
            Irq = Eth_Hal_GetDmaInterruptStatus(ETH_NODE_ADDR(CtrlIdx, CoreId), (Eth_DmaChannel)ChannelId);
            Loop++;
            /* #Violation: Eth_c_REF_9*/
            if (Loop > ETH_GET_MAX_TX_DESC_NUM(CtrlIdx, CoreId, ChannelId))
            {
                Irq = 0U; /* break */
            }
        }
    }
}
#endif /* (ETH_ENA_TX_INT \== STD_ON) */

/* End of Internal function Eth_TLLD_TimerIsr */
/* #Violation: Eth_c_REF_11*/
#define ETH_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Eth_c_REF_1*/
#include "Eth_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
