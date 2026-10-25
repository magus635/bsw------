/****************************************************************************************************
*   FileName              : Eth_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Ethernet
*
*   brief                 : This file contains all configuration declarations of Ethernet Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/


/*
*#Violation Summary
*#Eth_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers
*
*/
#ifndef ETH_CFG_H 
#define ETH_CFG_H 
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

#define ETH_CFG_VENDOR_ID                    (175U)
#define ETH_CFG_MODULE_ID                    (88U)

/* Autosar specification version */
#define ETH_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define ETH_CFG_AR_RELEASE_MINOR_VERSION     (4U)
#define ETH_CFG_AR_RELEASE_REVISION_VERSION  (0U)

/* Vendor specific implementation version information */
#define ETH_CFG_SW_MAJOR_VERSION             (1U)
#define ETH_CFG_SW_MINOR_VERSION             (2U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_CFG_SW_PATCH_VERSION             (0U)

/* Container : EthGeneralConfiguration */
#define ETH_DEV_ERROR_DETECT                 (STD_ON)
#define ETH_VERSION_INFO_API                 (STD_ON)
#define ETH_GET_DROP_COUNT_API               (STD_ON)
#define ETH_GET_ETHER_STATS_API              (STD_ON)
#define ETH_GLOBAL_TIME_SUPPORT_API          (STD_ON)
#define ETH_GETTXSTATS_API        (STD_OFF)
#define ETH_GETTXERRCNTRVAL_API        (STD_OFF)

/*
Configuration: ETH_SWT_MANAGEMENT_SUPPORT
- if STD_ON, Ethernet switch management support is enabled
- if STD_OFF, Ethernet switch management support is disabled
*/
#define ETH_SWT_MANAGEMENT_SUPPORT        (STD_OFF)


/* Rx buffer count and size for controller0 FIFO Index0 */
#define ETH_FIFO0_CTRL0_RXBUF_COUNT      (4U)
#define ETH_FIFO0_CTRL0_RXBUF_SIZE       (1024U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_FIFO0_CTRL0_RXBUF_PER_SIZE   (256U)

/* Rx buffer count and size for controller0 FIFO Index1 */
#define ETH_FIFO1_CTRL0_RXBUF_COUNT      (0U)
#define ETH_FIFO1_CTRL0_RXBUF_SIZE       (0U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_FIFO1_CTRL0_RXBUF_PER_SIZE   (0U)

/* Rx buffer count and size for controller0 FIFO Index2 */
#define ETH_FIFO2_CTRL0_RXBUF_COUNT      (0U)
#define ETH_FIFO2_CTRL0_RXBUF_SIZE       (0U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_FIFO2_CTRL0_RXBUF_PER_SIZE   (0U)

/* Rx buffer count and size for controller0 FIFO Index3 */
#define ETH_FIFO3_CTRL0_RXBUF_COUNT      (0U)
#define ETH_FIFO3_CTRL0_RXBUF_SIZE       (0U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_FIFO3_CTRL0_RXBUF_PER_SIZE   (0U)

/* Number of Receive FIFOs configured */
#define ETH_CTRL0_RXFIFO_CFGD       (1U)
#define ETH_CTRL0_RXSCHEDULED_CFGD       (1U)

/* Tx buffer count and size for controller0 FIFO Index0 */
#define ETH_FIFO0_CTRL0_TXBUF_COUNT      (4U)
#define ETH_FIFO0_CTRL0_TXBUF_SIZE       (1024U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_FIFO0_CTRL0_TXBUF_PER_SIZE   (256U)

/* Tx buffer count and size for controller0 FIFO Index1 */
#define ETH_FIFO1_CTRL0_TXBUF_COUNT      (5U)
#define ETH_FIFO1_CTRL0_TXBUF_SIZE       (1280U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_FIFO1_CTRL0_TXBUF_PER_SIZE   (256U)

/* Tx buffer count and size for controller0 FIFO Index2 */
#define ETH_FIFO2_CTRL0_TXBUF_COUNT      (0U)
#define ETH_FIFO2_CTRL0_TXBUF_SIZE       (0U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_FIFO2_CTRL0_TXBUF_PER_SIZE   (0U)

/* Tx buffer count and size for controller0 FIFO Index3 */
#define ETH_FIFO3_CTRL0_TXBUF_COUNT      (0U)
#define ETH_FIFO3_CTRL0_TXBUF_SIZE       (0U)
/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_FIFO3_CTRL0_TXBUF_PER_SIZE   (0U)

/* Number of Transmit FIFOs configured */
#define ETH_CTRL0_TXFIFO_CFGD       (2U)

/* \[SWS_Eth_00216] [SWS_Eth_00217]*/    
#define ETH_OFFLOAD_CHECKSUM_ICMP            (STD_ON)
#define ETH_OFFLOAD_CHECKSUM_IPV4            (STD_ON)
#define ETH_OFFLOAD_CHECKSUM_TCP             (STD_ON)
#define ETH_OFFLOAD_CHECKSUM_UDP             (STD_ON)
#define ETH_OFFLOAD_CHECKSUM                                                            \
(ETH_OFFLOAD_CHECKSUM_ICMP | ETH_OFFLOAD_CHECKSUM_IPV4 | ETH_OFFLOAD_CHECKSUM_TCP | \
ETH_OFFLOAD_CHECKSUM_UDP)

/* #Violation: Eth_Cfg_h_REF_1*/
#define ETH_MAIN_FUNCTION_PERIOD_IN_NANOSEC  (5U)
/* Configuration: ETH_MAX_CTRLS 
Limits the total number of supported controllers */
#define ETH_MAX_CTRLS                        (1U)
/* Configuration: ETH_INDEX 
Ethernet Driver Instance ID, used in DET_Report(.,.) Interface. */
#define ETH_INDEX                            (0U)


#define ETH_ENA_MII_API                      (STD_ON)
#define ETH_ENA_TX_INT                       (STD_OFF)
#define ETH_ENA_RX_INT                       (STD_OFF)
/* \[SWS_Eth_00003] The Ethernet Driver is using a zero-based index to abstract the access for upper
software layers. The parameter Eth_CtrlIdx within configuration corresponds to
parameter CtrlIdx used in the API.*/
#ifndef EthConf_EthCtrlConfig_EthCtrlConfig_0
#define EthConf_EthCtrlConfig_EthCtrlConfig_0 (0U)
#endif
/* ETH  mapped to Core0 */
#define ETH_MAX_CTRL_TO_CORE0             (1U)
/* ETH  mapped to Core1 */
#define ETH_MAX_CTRL_TO_CORE1             (0U)
/* ETH  mapped to Core2 */
#define ETH_MAX_CTRL_TO_CORE2             (0U)
/* ETH  mapped to Core3 */
#define ETH_MAX_CTRL_TO_CORE3             (0U)
#define ETH_SAFETY_ENABLE                 (STD_ON)

#endif /* ETH_CFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

