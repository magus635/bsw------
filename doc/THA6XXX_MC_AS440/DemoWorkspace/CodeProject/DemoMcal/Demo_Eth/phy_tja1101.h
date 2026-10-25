/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    phy_tja1101.h
 * Author:      00930
 * Version:     v0.1
 * Date:        2023/06/19
 * Description: This file contains all data type definitions and function declarations of interfaces.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/17    00930     Create
 *********************************************************************************************************************/
#ifndef PHY_TJA1101_
#define PHY_TJA1101_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "port_hal.h"
#include "eth_hal.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
#define GETH_PHY_MDIO_CTRL                       0x00U
#define GETH_PHY_MDIO_STAT                       0x01U
#define GETH_PHY_MDIO_PHYID1                     0x02U
#define GETH_PHY_MDIO_PHYID2                     0x03U
#define GETH_PHY_MDIO_EXTENDEDSTAT               0x0FU
#define GETH_PHY_MDIO_PHYID3                     0x10U
#define GETH_PHY_MDIO_EXTENDEDCTRL               0x11U
#define GETH_PHY_MDIO_PHYCTL1                    0x12U
#define GETH_PHY_MDIO_PHYCTL2                    0x13U
#define GETH_PHY_MDIO_ERRCNT                     0x14U
#define GETH_PHY_MDIO_INTSRC                     0x15U
#define GETH_PHY_MDIO_INTEN                      0x16U
#define GETH_PHY_MDIO_COMMSTAT                   0x17U
#define GETH_PHY_MDIO_GENSTAT                    0x18U
#define GETH_PHY_MDIO_EXTERNALSTAT               0x19U
#define GETH_PHY_MDIO_LINKFAILCNT                0x1AU
#define GETH_PHY_MDIO_COMMCFG                    0x1BU
#define GETH_PHY_MDIO_PHYCTL3                    0x1CU

#define PHY_IRQ_SLEEP_ABORT                   0x0001U
#define PHY_IRQ_TEMP_ERR                      0x0002U
#define PHY_IRQ_UV_RECOVERY                   0x0004U
#define PHY_IRQ_UV_ERR                        0x0008U
#define PHY_IRQ_CONTROL_ERR                   0x0020U
#define PHY_IRQ_SQI_WARNING                   0x0040U
#define PHY_IRQ_TRAINING_FAILED               0x0080U
#define PHY_IRQ_SYM_ERR                       0x0100U
#define PHY_IRQ_LINK_STATUS_UP                0x0200U
#define PHY_IRQ_LINK_STATUS_FAIL              0x0400U
#define PHY_IRQ_PHY_INIT_FAIL                 0x0800U
#define PHY_IRQ_LPS_RECEIVED                  0x1000U
#define PHY_IRQ_WUR_RECEIVED                  0x2000U
#define PHY_IRQ_WAKEUP                        0x4000U
#define PHY_IRQ_PWON                          0x8000U

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/* P14.7 output configuration */
static Port_OutputConfig s_phyRst_OUT = {{PORT_MODULE_P14, PORT_PIN_7},
                                        PORT_OUTPUTSEL_O0,
                                        PORT_OUTPUTMODE_PUSHPULL,
                                        PORT_CONTROLLER_PORT,
                                        PORT_DRIVESTRENGTH_LOW};
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Phy_Modify(Eth_NodeHandle *pEthNode, uint32 layeraddr, uint32 registerAddr,
                                  uint32 value, uint32 mask)
{
    uint16 reg;

    /* Read */
    Eth_Hal_ReadMii(pEthNode, layeraddr, registerAddr, &reg);

    /* Modify */
    reg &= (uint32)~mask;           /* Clear masked bits */
    reg |= (uint32)(mask & value);  /* Set masked bits to value */

    /* Write */
    Eth_Hal_WriteMii(pEthNode, layeraddr, registerAddr, reg);
}

LOCAL_FORCEINLINE sint32 Eth_Phy_Tja1101_Init(Eth_NodeHandle *pEthNode, Eth_PhyInterfaceMode mode,Eth_LineSpeed speed)
{
    sint32 retValue   = 0;
    sint32 retrycount = 100000;
    uint32 PHYaddr = 0;
    uint16 value = 0;
    uint16 value1 = 0;
    volatile uint32 icount = 0;
    (void)speed;
    /* 0. Reset the Phy device via p14.7 */


    /* 1. Find out the device address and Chenck ID */
    for(PHYaddr = 0; PHYaddr < 32; PHYaddr++)
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYID1, &value);
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYID2, &value1);
        if((value == 0x180)&&(value1 == 0xdd01)) break;
    }
    if((value != 0x180)&&(value1!= 0xdd01)) return -1;

    /* 2. SoftWare reset and wait to finished */
    Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x8000);
    do
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr,GETH_PHY_MDIO_CTRL, &value);
    } while (value & 0x8000);

    /*
     * 3.Configuration register access enabled
     */
    Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, 0x0004U, 0x0004U);

    Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYCTL1, 0x0U, 0x8000U);  /* 18U,Set slave mode,bit15:1-master,0-slave */
    Eth_Hal_ReadMii(pEthNode ,PHYaddr, GETH_PHY_MDIO_PHYCTL1, &value);  /* 18U,bit15:1-master,0-slave */

    /*
     * 4.Requests the specified PHY device to enter normal mode.
     */

    /* if sleep mode BIT14:11=b1010. goto standby mode. */
    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, &value);
    if((value & 0x7800) == 0x5000)
    {
        Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, 0x6000U, 0x7800U);
    }/* when auto_op=1,will goto Normal mode, else (auto_op=0 managed_mode) goto standby mode */

    /* if standby mode BIT14:11=b1100,goto Normal mode */
    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, &value);
    if((value & 0x7800) == 0x6000)
    {
        Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, 0x1800U, 0x7800U);
    }

    /*
     * 4.Config to MII/RMII interface.
     * BIT9:8 = 2b00,MII mode enabled
     *        = 2b01,RMII mode enabled (50 MHz input on REF_CLK)
     *        = 2b10,RMII mode enabled (50 MHz output on REF_CLK)  select this
     *        = 2b11,Reverse
     */
    if(ETH_PHY_INTERFACE_MII == mode)
    {
        /* 18U,set slave mode,bit9:8:00-MII, 01-RMII(50MHz input on REF_CLK, 10-RMII(50MHz output on REF_CLK) */
        Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYCTL1, 0x0U, 0x0300U);
        Eth_Hal_ReadMii(pEthNode ,PHYaddr, GETH_PHY_MDIO_PHYCTL1, &value);
    }
    else    /* RMII mode*/
    {
        Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYCTL1, 0x200U, 0x300U);
    }
    /*
     * 5.Set work status (100M FUll_duplex,Auto negotiation not supported)
     * BIT8 = 1b1,DUPLEX_MODE,always 1;
     *+----+------+---------+
     *|BIT6| BIT13|  Speed  |
     *+----+------+---------+
     *|  0 |   0  | 10 Mbps |
     *+----+------+---------+
     *|  0 |   1  | 100Mbps |
     *+----+------+---------+
     *|  1 |   0  | 1000Mbps|
     *+----+------+---------+
     *|  1 |   0  | reserved|
     *+----+------+---------+
     */
    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, &value);
    Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, (value|(1<<13) | (1<<8)));

    /*
     * 6.Enable interrupt for phy
     */
    uint16 irqs = PHY_IRQ_LINK_STATUS_UP | PHY_IRQ_LINK_STATUS_FAIL | PHY_IRQ_WAKEUP | PHY_IRQ_PWON;

    Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_INTEN, irqs, irqs);

    /*
     * 7.Wait for valid link established.
     */

    do{
        Eth_Hal_ReadMii(pEthNode ,PHYaddr, GETH_PHY_MDIO_INTSRC, &value);

        /* PowerOn interrupt handling */
        if ((value & 0x8000U) != 0U)
        {
            /*  goto normal mode. */
            Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, 0x1800U, 0x7800U);
            /*link control enabled.  */ 
            Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, 0x8000U, 0x8000U);
        }
        /* WakeUp interrupt handling */
        if ((value & 0x4000U) != 0U)
        {
            /*  link control enabled.*/ 
            Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, 0x8000U, 0x8000U);
        }

        /* Link down interrupt handling */
        if ((value & 0x0400U) != 0U)
        {

        }
        /* Link up interrupt handling */
        if ((value & 0x0200U) != 0U)
        {
            break;
        }

        if (retrycount < 0)
        {
            retValue = -1;
            break;
        }
        else{
            retrycount--;
        }

    }while(1);

    icount = 100000;
    retrycount = 100000;
    do{
        Eth_Hal_ReadMii(pEthNode ,PHYaddr, GETH_PHY_MDIO_COMMSTAT, &value);  /* 23U,link status:0x9c00 */

        /* Valid link established. */
        if ((value&0x9c00) == 0x9c00){
            break;
        }
        else if (retrycount < 0)
        {
            retValue = -1;
            break;
        }
        else
        {
            Phy_Modify(pEthNode, PHYaddr, GETH_PHY_MDIO_EXTENDEDCTRL, 0x9800U, 0x9800U);  /* 17U, link control */
            retrycount--;
        }
        icount--;
    }while(icount>0);

    return retValue;
}

#endif /*  PHY_TJA1101_*/
