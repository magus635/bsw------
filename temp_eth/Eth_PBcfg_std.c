
/****************************************************************************************************
*   FileName              : Eth_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Ethernet
*
*   brief                 : This file contains all configurations of Ethernet Driver
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
*#Eth_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Eth_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*#Eth_PBcfg_c_REF_3:MISRAC2012-Rule-10.5;
* Justification:Redundant cast is necessary to maintain the software structure and reduce the 
* complexity.
*
*#Eth_PBcfg_c_REF_4:MISRAC2012-Rule-11.4; 
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#Eth_PBcfg_c_REF_7:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* Include ETH Module File */
#include "Eth.h"



#if (ETH_FIFO0_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO0RxBuffer[ETH_FIFO0_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO1RxBuffer[ETH_FIFO1_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64) uint8 Eth_FIFO2RxBuffer[ETH_FIFO2_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_SIZE \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO3RxBuffer[ETH_FIFO3_CTRL0_RXBUF_SIZE];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_SIZE \> 0)*/

#if (ETH_FIFO0_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO0TxBuffer[ETH_FIFO0_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_SIZE \> 0)*/
#if (ETH_FIFO1_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO1TxBuffer[ETH_FIFO1_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_SIZE \> 0)*/

#if (ETH_FIFO2_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO2TxBuffer[ETH_FIFO2_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_SIZE \> 0)*/
#if (ETH_FIFO3_CTRL0_TXBUF_SIZE > 0)
extern ALIGNED(64)  uint8 Eth_FIFO3TxBuffer[ETH_FIFO3_CTRL0_TXBUF_SIZE];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_SIZE \> 0)*/



#if (ETH_FIFO0_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx0descr[ETH_FIFO0_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx1descr[ETH_FIFO1_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx2descr[ETH_FIFO2_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_TXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_TXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_TxDescr Eth_Tx3descr[ETH_FIFO3_CTRL0_TXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_TXBUF_COUNT \> 0)*/

#if (ETH_FIFO0_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx0descr[ETH_FIFO0_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO0_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO1_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx1descr[ETH_FIFO1_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO1_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO2_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx2descr[ETH_FIFO2_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO2_CTRL0_RXBUF_COUNT \> 0)*/
#if (ETH_FIFO3_CTRL0_RXBUF_COUNT > 0)
extern ALIGNED(64)  Eth_RxDescr Eth_Rx3descr[ETH_FIFO3_CTRL0_RXBUF_COUNT];
#endif /*(ETH_FIFO3_CTRL0_RXBUF_COUNT \> 0)*/



/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/* the source clock of Geth is AXI clock. config in MCU*/

/* Clock configuration for MDIO - between 1.0 MHz to 2.5 MHz frequency. */






/*Array to store index of the controller in the allocated core.*/
/* Eth configuration informations which mapped to Core0 */
/* #Violation: Eth_PBcfg_c_REF_2*/
#define ETH_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Eth_PBcfg_c_REF_1*/
#include "Eth_MemMap.h"
/* #Violation: Eth_PBcfg_c_REF_7 */
static const Eth_TxChannelConfig Eth_TxChannelCtrl0[2] =
{
  {
    ETH_DMA_BURSTLENGTH16,     /* Maximum burst length of the channel */
    &Eth_Tx0descr[0],              /* Pointer to TX descriptors RAM */
    (uint8 *)&Eth_FIFO0TxBuffer[0],              /* Ponter to Tx Buffer 1 */
    /* DMA channel Tx interrupt enable */
    {
      0,
    },
    TRUE,/* Enable/Disable Tx Channel */
    ETH_FIFO0_CTRL0_TXBUF_COUNT,/* Number of tx buffers.*/    
    ETH_FIFO0_CTRL0_TXBUF_PER_SIZE,/* Configured tx buffer size after align*/
    0U,/* DMA channel id*/
    0x0U,/* DMA channel Arbitration weight*/
  },
  {
    ETH_DMA_BURSTLENGTH16,     /* Maximum burst length of the channel */
    &Eth_Tx1descr[0],              /* Pointer to TX descriptors RAM */
    (uint8 *)&Eth_FIFO1TxBuffer[0],              /* Ponter to Tx Buffer 1 */
    /* DMA channel Tx interrupt enable */
    {
      0,
    },
    TRUE,/* Enable/Disable Tx Channel */
    ETH_FIFO1_CTRL0_TXBUF_COUNT,/* Number of tx buffers.*/    
    ETH_FIFO1_CTRL0_TXBUF_PER_SIZE,/* Configured tx buffer size after align*/
    1U,/* DMA channel id*/
    0x0U,/* DMA channel Arbitration weight*/
  },
};

/* #Violation: Eth_PBcfg_c_REF_7 */
static const Eth_TxQueueConfig Eth_TxFifoCtrl0[2] =
{
  {
    TRUE, /* Transmit store and forward enable/disable */
    ETH_TXQUEUE_SIZE_3072B, /* Tx Queue size */
    ETH_TXQUEUE_THRESHOLD_64B, /* Transmit Queue Threshold */
    FALSE, /* Enable/Disable Tx Queue Underflow Interrupt */
    TRUE, /*ENABLE QUEUE*/
    /* #Violation: Eth_PBcfg_c_REF_3*/
    (Eth_MtlTxqen)0x2U, /* MTL_TxQ_Operation_Mode*/ 
    (uint16)0x0U,  /* The Idle slope credit for Queue or Configured weight for WRR algorithm*/
    (uint32)0x0U, /* The high credit for qav Queue*/
    (uint32)0x0U,   /* The low credit for qav Queue*/
    (uint16)0x0U,  /* The send slope credit for qav Queue*/
    (uint16)0U, /* The queue id*/
  },
  {
    TRUE, /* Transmit store and forward enable/disable */
    ETH_TXQUEUE_SIZE_3072B, /* Tx Queue size */
    ETH_TXQUEUE_THRESHOLD_64B, /* Transmit Queue Threshold */
    FALSE, /* Enable/Disable Tx Queue Underflow Interrupt */
    TRUE, /*ENABLE QUEUE*/
    /* #Violation: Eth_PBcfg_c_REF_3*/
    (Eth_MtlTxqen)0x1U, /* MTL_TxQ_Operation_Mode*/ 
    (uint16)0x0U,  /* The Idle slope credit for Queue or Configured weight for WRR algorithm*/
    (uint32)0x0U, /* The high credit for qav Queue*/
    (uint32)0x0U,   /* The low credit for qav Queue*/
    (uint16)0x1000U,  /* The send slope credit for qav Queue*/
    (uint16)1U, /* The queue id*/
  },
};



/* Ingress FIFO configuration */
/* #Violation: Eth_PBcfg_c_REF_7 */
static const Eth_RxQueueConfig Eth_RxFifoCtrl0[1] =
{
  {
    TRUE,                       /* Receive Store and Forward Enable/Disable */
    ETH_RXQUEUE_SIZE_8192B,     /* Rx Queue size */
    ETH_RXFLOWCONTROL_THRESHOLD_2KB,/*Threshold for activating flow control*/
    ETH_RXFLOWCONTROL_THRESHOLD_1KB,/* RFD: Threshold for deactivating flow control */    
    ETH_RXQUEUE_THRESHOLD_64B, /* Receive Queue Threshold */
    ETH_DMA_CHANNEL0,          /* NOT USE! .Mapped DMA Channel of Rx Queue */
    255,                          /* tagged packets user priority, set 0 if single channel */
    FALSE,                      /* Error Packet Forwarding Enable/Disable */
    TRUE,                      /* Undersized Good Packet Forwarding Enable/Disable */
    FALSE,                      /* Enable/Disable Rx Queue Overflow Interrupt */
    TRUE,                      /* Enable/Disable Rx Queue */
    FALSE,                     /* Enable/Disable flow control signal operation */
  }
};

/* #Violation: Eth_PBcfg_c_REF_7 */
static const Eth_RxChannelConfig Eth_RxChannelCtrl0[1] =
{
  {
    ETH_DMA_BURSTLENGTH1,      /* Maximum burst length of the channel */
    &Eth_Rx0descr[0],              /* pointer to Rx descriptors RAM */
    (uint8 *)&Eth_FIFO0RxBuffer[0],               /* Ponter to Rx Buffer 1 */
    /* DMA channel Rx interrupt enable */
    {
      0,
    },
    TRUE,/* Enable/Disable rx Channel */
    /*Rx Ingress cfg */
    ETH_FIFO0_CTRL0_RXBUF_COUNT,/*NumOfRxBuffers*/
    ETH_FIFO0_CTRL0_RXBUF_PER_SIZE,/*RxBufferAlignSize*/
  }
};

static  const Eth_DemType EthDem[]=
{
    {
    /*DEM Id for Ethernet controller hardware test failure*/
    ETH_DISABLE_DEM_REPORT,
    /*DEM Id for Ethernet controller Frames Lost Error*/
    ETH_DISABLE_DEM_REPORT,
    /*DEM Id for Ethernet controller Frames Alignment Error*/
    ETH_DISABLE_DEM_REPORT,
    /*DEM Id for Ethernet controller Frames CRC Error*/
    ETH_DISABLE_DEM_REPORT,
    /*DEM Id for Ethernet controller  Undersize frame Error*/
    ETH_DISABLE_DEM_REPORT,
    /*DEM Id for Ethernet controller  Oversize frame Error*/
    ETH_DISABLE_DEM_REPORT,
    /*DEM Id for Ethernet controller Single collision Error*/
    ETH_DISABLE_DEM_REPORT,
    /*DEM Id for Ethernet controller Multiple collision Error*/
    ETH_DISABLE_DEM_REPORT,
    /*DEM Id for Ethernet controller Late collision Error*/
    ETH_DISABLE_DEM_REPORT,
    }

};





/* Priority to FIFO index mapping */
/* #Violation: Eth_PBcfg_c_REF_7 */
static const uint8 EthPrioToFifoMap0[8] =
{
  0x0U,
  0x0U,
  0x0U,
  0x0U,
  0x0U,
  0x0U,
  0x0U,
  0x1U
};

/* Fifo to Egress Queue Mapping   DMA FIFO to queue id. */
/* #Violation: Eth_PBcfg_c_REF_7 */
static const uint8 EthTxFifoToChMap0[2] =
{
  0U,
  1U
};








/* Fifo Ingress to Queue Mapping */
/* #Violation: Eth_PBcfg_c_REF_7 */
static const uint8 EthRxFifoToChMap0 [1] =
{
  0U
};

/* Container: EthConfigset */
static const EthSdkCtrlConfigType Eth_CtrlConfigCore0[ETH_MAX_CTRLS]=
{
    {
        /* Pointer to ETH register base address */
        /* #Violation: Eth_PBcfg_c_REF_4*/
        ETH,
        /* External Phy Interface RMII Mode */
        ETH_PHY_INTERFACE_RMII,
        
        /* Set the Tx clock delay in RGMII mode */
        ETH_CLKDELAY_CELL_0,
        /* Set the Rx clock delay in RGMII mode */
        ETH_CLKDELAY_CELL_0,
        /* pins N.A */
        {
        NULL_PTR,
        NULL_PTR,
        NULL_PTR
        },
        {
            /* Duplex Mode */
            ETH_FULLDUPLEX_MODE,
            /* Ethernet line speed */
            ETH_LINESPEED_100M,
            /* Loopback mode enable/disable */
            ETH_LOOPBACK_DISABLE,
            /* Maximum size of the ethernet packet */
            1518,
            /* MAC address for the ethernet */
            {
                /*MAC address (uint8 *)"00:DE:AD:00:00:02";*/
                (uint8)0x00U,
                (uint8)0xDEU,
                (uint8)0xADU,
                (uint8)0x00U,
                (uint8)0x00U,
                (uint8)0x02U
            },
            /* Enable/disable timestamp */
            TRUE,
            /* Set receive all packet */
            TRUE,
            /* Set destination address inverse Filter */
            FALSE,
            /* Set VLAN Tag Filter */
            FALSE,
            /* Set enablePromiscuous */
            TRUE,
            /* Set enableMulticast */
            TRUE,
            /* Set enableBroadcast */ 
            TRUE,
            /* Set checksum offload */
            (boolean)(ETH_OFFLOAD_CHECKSUM),
            FALSE, /* Set CRC stripping for Type packets */
            FALSE, /* Set pad stripping for Type or ethernet packets */
            FALSE, /* Set CRC Checking for Received Packets */
        },
        /* MTL */
        {
        
            /* Set ECC feature for MTL Tx FIFO memory */
            TRUE,
            /* Set ECC feature for MTL Rx FIFO memory */
            TRUE,
            /*not used*/
            {
            FALSE,                       /*Overriding MC-BC queue priority select,OMCBCQ */
            /* Broad And Multicast queue config */
            {
            ETH_MTL_QUEUE0,
            FALSE
            },   
            /* Unicast AVTP queue, AVCPQ */
            {
            ETH_MTL_QUEUE0,
            FALSE
            },
            /* #Violation: Eth_PBcfg_c_REF_3*/  
            (Eth_MtlQueue)0U,              /* Unicast PTP queue, PTPQ */
            /* #Violation: Eth_PBcfg_c_REF_3*/
            (Eth_MtlQueue)0U,              /* Remaining Unicast queue, UPQ */
            ETH_MTL_QUEUE0,                          /* All preemptable packet queue */
            },
            &Eth_TxFifoCtrl0[0],/* Tx queue configurations of selected queues */
            &Eth_RxFifoCtrl0[0],/* Rx queue configurations of selected queues */
        },
        /*DMA*/
        {
            TRUE,                   /* Enable/Disable Address Aligned Beats */
            ETH_DMA_INTERRUPT_MODE2, /* Interrupt mode */
            /*txchannel*/
            &Eth_TxChannelCtrl0[0],
            /* rx Channels configurations of selected Channels */
            &Eth_RxChannelCtrl0[0],
        },
        
        /* Number of Tx channels used in the controller */
        (uint8)2U,
        /* DMA transmit arbitration algorithm */
        (uint8)0U,
        /* MTL transmit scheduling algorithm */
        (uint8)3U,
        /* Number of Rx Channels used in the controller */
        (uint8)1U,
        /* Queue where the untagged Rx frames are routed */
        (uint8)0U,
        /* Transmit interrupt is enabled */
        ETH_ENA_TX_INT,
        /* Recive interrupt is enabled */        
        ETH_ENA_RX_INT,
        /*ETH frequency*/
        200000000U,
        /*CR value for MII*/
        /* #Violation: Eth_PBcfg_c_REF_3*/
        (Eth_CsrClockRange)4U,
    },
};


static const EthCtrlConfigType EthCtrlConfigCore0[]=
{
  {
    &Eth_CtrlConfigCore0[0],
    /* Pointer to the mapping of Tx FIFO to Channels */
    &EthTxFifoToChMap0[0],
    /* Pointer to the mapping of configured Priority to FifoIdx */
    &EthPrioToFifoMap0[0],
    
    /* Pointer to the mapping of Rx FIFO to Channels */
    &EthRxFifoToChMap0[0],
    /* Eth Controller Index */
    (uint8)0U,
    &EthDem[0],
  },

};

static const Eth_CoreConfigType Eth_CoreConfigCore0[]=
{
    {
        &EthCtrlConfigCore0[0],
        ETH_MAX_CTRL_TO_CORE0
    },
};

/* #Violation: Eth_PBcfg_c_REF_2*/
#define ETH_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Eth_PBcfg_c_REF_1*/
#include "Eth_MemMap.h"

/* #Violation: Eth_PBcfg_c_REF_2*/
#define ETH_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_PBcfg_c_REF_1*/
#include "Eth_MemMap.h"

/* 
This array is used for mapping Eth controller to the Core. 
Array index is Eth channel -> array member is index of Eth_ChannelConfigSetCorex[x=0~4]
*/
/* #Violation: Eth_PBcfg_c_REF_7 */
static const Eth_MappingType Eth_CtrlIdxToCoreMap[1] =
{
    /* Eth Ch0*/
    {0U, MULTICOREID_CPU0}
};

const Eth_ConfigType Eth_ConfigSet[ETH_MAX_CTRLS] =
{
    {
        {
            /* Pointer to Core Configuration structure */
            /* Eth configuration information of core0 */
            &Eth_CoreConfigCore0[0],
            /* No configuration information for core1 */
            NULL_PTR
        },
        &Eth_CtrlIdxToCoreMap[0]
    }
};

/* #Violation: Eth_PBcfg_c_REF_2*/
#define ETH_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_PBcfg_c_REF_1*/
#include "Eth_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


