/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    phy_dp83867.h
 * Author:      00930
 * Version:     v0.1
 * Date:        2023/06/19
 * Description: This file contains all data type definitions and function declarations of interfaces.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/17    00930     Create
 *********************************************************************************************************************/
#ifndef PHY_DP83867_
#define PHY_DP83867_
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
#define GETH_PHY_MDIO_AN_ADV                     0x04U
#define GETH_PHY_MDIO_AN_LPA                     0x05U
#define GETH_PHY_MDIO_AN_EXP                     0x06U
#define GETH_PHY_MDIO_AN_NPTX                    0x07U
#define GETH_PHY_MDIO_AN_NPRX                    0x08U
#define GETH_PHY_MDIO_GCTRL                      0x09U
#define GETH_PHY_MDIO_GSTAT                      0x0AU
#define GETH_PHY_MDIO_RES11                      0x0BU
#define GETH_PHY_MDIO_RES12                      0x0CU
#define GETH_PHY_MDIO_MMDCTRL                    0x0DU
#define GETH_PHY_MDIO_MMDDATA                    0x0EU
#define GETH_PHY_MDIO_XSTAT                      0x0FU
#define GETH_PHY_MDIO_PHYPERF                    0x10U
#define GETH_PHY_MDIO_PHYSTAT1                   0x11U
#define GETH_PHY_MDIO_PHYSTAT2                   0x12U
#define GETH_PHY_MDIO_PHYCTL1                    0x13U
#define GETH_PHY_MDIO_PHYCTL2                    0x14U
#define GETH_PHY_MDIO_ERRCNT                     0x15U
#define GETH_PHY_MDIO_EECTRL                     0x16U
#define GETH_PHY_MDIO_MIICTRL                    0x17U
#define GETH_PHY_MDIO_MIISTAT                    0x18U
#define GETH_PHY_MDIO_IMASK                      0x19U
#define GETH_PHY_MDIO_ISTAT                      0x1AU
#define GETH_PHY_MDIO_LED                        0x1BU
#define GETH_PHY_MDIO_TPGCTRL                    0x1CU
#define GETH_PHY_MDIO_TPGDATA                    0x1DU
#define GETH_PHY_MDIO_FWV                        0x1EU
#define GETH_PHY_MDIO_RES1F                      0x1FU
#define PHY_MDIO_PHYID1                          0x02U
#define PHY_MDIO_PHYID2                          0x03U
#define GETH_PHY_MDIO_MMDCTRL_ACCESSTYPE_ADDR    0x00U
#define GETH_PHY_MDIO_MMDCTRL_ACCESSTYPE_DATA    0x4000U
#define GETH_PHY_MDIO_MMDCTRL_ACCESSTYPE_DATA_PI 0x8000U

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/* Phy reset:P14.10 output configuration */

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
LOCAL_FORCEINLINE sint32 Eth_Phy_Dp83867_Init(Eth_NodeHandle *pEthNode,Eth_PhyInterfaceMode mode,Eth_LineSpeed speed)
{
    sint32 retValue   = 0;
    sint32 retrycount = 100000;

    /* 1. Find out the device address */
    uint32 PHYaddr = 0;
    uint16 value = 0;
    uint16 value1 = 0;

    /* 0. Reset the Phy device via p14.10 */

    for(PHYaddr = 0; PHYaddr < 32; PHYaddr++)
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYID1, &value);
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYID2, &value1);
        if((value == 0x2000)&&(value1 == 0xA231)) break;
    }
    if((value != 0x2000)&&(value1!= 0xA231)) return -1;


    /* 2. SoftWare reset and wait to finished */
    Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x8000);
    do
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr,GETH_PHY_MDIO_CTRL, &value);
    } while (value & 0x8000);


    if(ETH_PHY_INTERFACE_RGMII == mode)
    {
        /*
         * 3.Auto-Negotiation Enabled
         *
         * When auto-negotiation is disabled:
         * 1).allows the port speed to be 1000 Mbps.
         * 2).allows the port as Duplex capability.
         */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x1140);

        /*
         * 4. 1000BASE-T Configuration
         *
         * 1)Advertise 1000Base-T Full Duplex ability.
         * 2)Advertise Multi-port device
         */
        Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_GCTRL, 0x300);

        /*
         * 5.Extended RGMII Control Register configuration
         *
         * 1).Enable RGMII transmit/receive clock is shifted relative to transmit data.
         * 2).Enable RGMII transmit/receive FIFO half full threshold.
         * 3).Enable RGMII interface.
         */
        /* Select access type as ADDR for MMD access and select the Device address */
        Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
        /* Select PHY register for write operation */
        Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0032);
        /* select the DATA operation and device address */
        Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
        /* Write the data */
        Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x00d3);

        /*
         * 6.Extended RGMII Delay Control Register configuration
         *
         * 1).RGMII Receive  Clock Delay: 0.75 ns
         * 2).RGMII Transmit Clock Delay: 0.75 ns
         */
        /* Select access type as ADDR for MMD access and select the Device address */
        Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
        /* Select PHY register for write operation */
        Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0086);
        /* select the DATA operation and device address */
        Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
        /* Write the data */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0000U);
    }
    else
    {
        /*
         *The RGMII Disable strap corresponds to the RGMII Enable (bit 7) in the RGMIICTL register (address 0x0032).
         *The When RGMII mode is disabled, the DP83867 operates in GMII/MII mode.
         *The RGMII ENABLE (Register 0x0032, bit 7)
         */

          /* Select access type as ADDR for MMD access and select the Device address */
          Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
          /* Select PHY register for write operation */
          Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0032);
          /* select the DATA operation and device address */
          Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
          /* Write the data */
          Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_MMDDATA, 0);


        /* MII Interface */
        if(speed < ETH_LINESPEED_1000M)
        {
            Eth_Hal_WriteMii(pEthNode,PHYaddr, 0x0018,0x6170);
            Eth_Hal_WriteMii(pEthNode,PHYaddr, 0x04, 0x061);
            Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_GCTRL,0);
        }
        /* GMII Interface */
        else
        {
            /*
             * 3.Auto-Negotiation Enabled
             *
             * When auto-negotiation is disabled:
             * 1).allows the port speed to be 1000 Mbps.
             * 2).allows the port as Duplex capability.
             */
            Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_CTRL, 0x1140);

            /*
             * 4. 1000BASE-T Configuration
             *
             * 1)Advertise 1000Base-T Full Duplex ability.
             * 2)Advertise Multi-port device
             */
            Eth_Hal_WriteMii(pEthNode,PHYaddr, GETH_PHY_MDIO_GCTRL, 0x300);
        }

    }

    /*
     * 6.Check for Auto-Negotiation configuration
     * 1).Restart Auto-Negotiation. reinitialize the Auto-Negotiation process. If Auto-Negotiation is disabled
     */

    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, &value);                        /* The correct value:0x1140 */
    Eth_Hal_WriteMii(pEthNode,PHYaddr,GETH_PHY_MDIO_CTRL, (value | (1<<9) | (1<<12)));    /* enable auto-negotiation, restart auto-negotiation */

    /*
     * 7.Wait for Auto-Negotiation process complete.
     */
    retrycount = 100000;
    do
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_STAT, &value);
        retrycount--;
    } while (((value & 0x20)==0)&&(retrycount != 0));

    /*
     * 8.Wait for valid link established.
     */
    retrycount = 100000;
    do{
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_STAT, &value);

        retValue = ((value & (1 << 2)) != 0) ? 0 : 1;

        /* Valid link established. */
        if (retValue == 0){
            break;
        }
        else if (retrycount < 0)
        {
            retValue = -1;
            break;
        }
        else{
            retrycount--;
        }

    }while(1);

    Eth_Hal_ReadMii(pEthNode,PHYaddr, GETH_PHY_MDIO_PHYSTAT1, &value);
    return retValue;
}

LOCAL_FORCEINLINE sint32 Eth_Phy_Dp83867_InitMiiLoop(Eth_NodeHandle *pEthNode, Eth_PhyInterfaceMode mode, Eth_LineSpeed speed)
{
    sint32 retValue = 0;
    sint32 retrycount = 100000;
    uint32 PHYaddr = 0;
    uint16 value = 0;
    uint16 value1 = 0;

    /* 0. Reset the Phy device via p14.10 */


    /* 1. Find out the device address */
    for(PHYaddr = 0; PHYaddr < 32; PHYaddr++)
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYID1, &value);
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYID2, &value1);
        if((value == 0x2000) && (value1 == 0xA231))
            break;
    }
    if((value != 0x2000) && (value1 != 0xA231))
        return -1;

    /* 2. SoftWare reset and wait to finished */
    Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x8000);
    do
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, &value);
    } while(value & 0x8000);

    if(ETH_PHY_INTERFACE_RGMII == mode)
    {
        /*
         * 3.Auto-Negotiation Enabled
         *
         * When auto-negotiation is disabled:
         * 1).allows the port speed to be 1000 Mbps.
         * 2).allows the port as Duplex capability.
         */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x1140);

        /*
         * 4. 1000BASE-T Configuration
         *
         * 1)Advertise 1000Base-T Full Duplex ability.
         * 2)Advertise Multi-port device
         */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, 0x300);

        /*
         * 5.Extended RGMII Control Register configuration
         *
         * 1).Enable RGMII transmit/receive clock is shifted relative to transmit data.
         * 2).Enable RGMII transmit/receive FIFO half full threshold.
         * 3).Enable RGMII interface.
         */
        /* Select access type as ADDR for MMD access and select the Device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
        /* Select PHY register for write operation */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0032);
        /* select the DATA operation and device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
        /* Write the data */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x00d3);

        /*
         * 6.Extended RGMII Delay Control Register configuration
         *
         * 1).RGMII Receive  Clock Delay: 0.75 ns
         * 2).RGMII Transmit Clock Delay: 0.75 ns
         */
        /* Select access type as ADDR for MMD access and select the Device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
        /* Select PHY register for write operation */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0086);
        /* select the DATA operation and device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
        /* Write the data */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0000U);
    }
    else
    {
        /*
         *The RGMII Disable strap corresponds to the RGMII Enable (bit 7) in the RGMIICTL register (address 0x0032).
         *The When RGMII mode is disabled, the DP83867 operates in GMII/MII mode.
         *The RGMII ENABLE (Register 0x0032, bit 7)
         */

        /* Select access type as ADDR for MMD access and select the Device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
        /* Select PHY register for write operation */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0032);
        /* select the DATA operation and device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
        /* Write the data */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0);

        /* MII Interface */
        if(speed < ETH_LINESPEED_1000M)
        {
            Eth_Hal_WriteMii(pEthNode, PHYaddr, 0x0018, 0x6170);
            Eth_Hal_WriteMii(pEthNode, PHYaddr, 0x04, 0x061);
            Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, 0);
        }
        /* GMII Interface */
        else
        {
            /*
             * 3.Auto-Negotiation Enabled
             *
             * When auto-negotiation is disabled:
             * 1).allows the port speed to be 1000 Mbps.
             * 2).allows the port as Duplex capability.
             */
            Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x1140);

            /*
             * 4. 1000BASE-T Configuration
             *
             * 1)Advertise 1000Base-T Full Duplex ability.
             * 2)Advertise Multi-port device
             */
            Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, 0x300);
        }
    }

    /*
     * 6.Check for Auto-Negotiation configuration
     * 1).Restart Auto-Negotiation. reinitialize the Auto-Negotiation process. If Auto-Negotiation is disabled
     */

    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, &value); 
    Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL,
                     (value | (1 << 9) | (1 << 12)|(1 << 14))); 
    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, &value);
    /*
     * 7.Wait for Auto-Negotiation process complete.
     */
    retrycount = 100000;
    do
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_STAT, &value);
        retrycount--;
    } while(((value & 0x20) == 0) && (retrycount != 0));

    /*
     * 8.Wait for valid link established.
     */
    retrycount = 100000;
    do
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_STAT, &value);

        retValue = ((value & (1 << 2)) != 0) ? 0 : 1;

        /* Valid link established. */
        if(retValue == 0)
        {
            break;
        }
        else if(retrycount < 0)
        {
            retValue = -1;
            break;
        }
        else
        {
            retrycount--;
        }

    } while(1);

    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYSTAT1, &value);

    return retValue;
}


LOCAL_FORCEINLINE sint32 Eth_Phy_Dp83867_HalfDuplexInit(Eth_NodeHandle *pEthNode, Eth_PhyInterfaceMode mode, Eth_LineSpeed speed)
{
    sint32 retValue = 0;
    sint32 retrycount = 100000;
    uint32 PHYaddr = 0;
    uint16 value = 0;
    uint16 value1 = 0;

    /* 0. Reset the Phy device via p14.10 */


    /* 1. Find out the device address */
    for(PHYaddr = 0; PHYaddr < 32; PHYaddr++)
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYID1, &value);
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYID2, &value1);
        if((value == 0x2000) && (value1 == 0xA231))
            break;
    }
    if((value != 0x2000) && (value1 != 0xA231))
        return -1;

    /* 2. SoftWare reset and wait to finished */
    Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x8000);
    do
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, &value);
    } while(value & 0x8000);

    if(ETH_PHY_INTERFACE_RGMII == mode)
    {
        /*
         * 3.Auto-Negotiation Enabled
         *
         * When auto-negotiation is disabled:
         * 1).allows the port speed to be 1000 Mbps.
         * 2).allows the port as Duplex capability.
         */

        if(ETH_LINESPEED_10M == speed)
        {
             /* Auto-negotiation is disabled, 10Mbps,full duplex  ok */
             Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x0100);
        }
        else
        {
#if 1
            /* Auto-negotiation is disabled, 100Mbps,full duplex  ok */
            Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x2100);
#endif

#if 0
             /* Auto-negotiation is disabled, 100Mbps,half duplex  ok */
             Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x2000);

#endif

#if 0
            /* Auto-negotiation is disabled, 100Mbps,full duplex  ok, PHY MII Loopback ok */
            Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, (0x2100|(1 << 14)));
            Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, &value);
#endif
        }

        /*
         * 4. 1000BASE-T Configuration
         *
         * 1)Advertise 1000Base-T Full Duplex ability.
         * 2)Advertise Multi-port device
         */

        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, &value);
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, (0x300|(1 << 12)|(1 << 11)));/* PHY is master */
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, &value);

        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_AN_ADV, &value);
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_AN_LPA, &value1);

        /*
         * 5.Extended RGMII Control Register configuration
         *
         * 1).Enable RGMII transmit/receive clock is shifted relative to transmit data.
         * 2).Enable RGMII transmit/receive FIFO half full threshold.
         * 3).Enable RGMII interface.
         */
        /* Select access type as ADDR for MMD access and select the Device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
        /* Select PHY register for write operation */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0032);
        /* select the DATA operation and device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
        /* Write the data */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x00d3);

        /*
         * 6.Extended RGMII Delay Control Register configuration
         *
         * 1).RGMII Receive  Clock Delay: 0.75 ns
         * 2).RGMII Transmit Clock Delay: 0.75 ns
         */
        /* Select access type as ADDR for MMD access and select the Device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
        /* Select PHY register for write operation */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0086);
        /* select the DATA operation and device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
        /* Write the data */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0000U);
    }
    else
    {
        /*
         *The RGMII Disable strap corresponds to the RGMII Enable (bit 7) in the RGMIICTL register (address 0x0032).
         *The When RGMII mode is disabled, the DP83867 operates in GMII/MII mode.
         *The RGMII ENABLE (Register 0x0032, bit 7)
         */

        /* Select access type as ADDR for MMD access and select the Device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x001f);
        /* Select PHY register for write operation */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0x0032);
        /* select the DATA operation and device address */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDCTRL, 0x401f);
        /* Write the data */
        Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_MMDDATA, 0);

        /* MII Interface */
        if(speed < ETH_LINESPEED_1000M)
        {
            Eth_Hal_WriteMii(pEthNode, PHYaddr, 0x0018, 0x6170);
            Eth_Hal_WriteMii(pEthNode, PHYaddr, 0x04, 0x061);
            Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, 0);

            if(ETH_LINESPEED_10M == speed)
            {

                 /* Auto-negotiation is disabled, 10Mbps,full duplex  ok */
                 Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x0100);

                 Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, &value);
                 Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, (1 << 12)|(1 << 11));/* PHY is master */
            }
            else
            {
                /* Auto-negotiation is disabled, 100Mbps,full duplex  ok */
                Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x2100);

                /* Auto-negotiation is disabled, 100Mbps,half duplex  ok */

            }

        }
        /* GMII Interface */
        else
        {
            /*
             * 3.Auto-Negotiation Enabled
             *
             * When auto-negotiation is disabled:
             * 1).allows the port speed to be 1000 Mbps.
             * 2).allows the port as Duplex capability.
             */
            Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, 0x1140);

            /*
             * 4. 1000BASE-T Configuration
             *
             * 1)Advertise 1000Base-T Full Duplex ability.
             * 2)Advertise Multi-port device
             */
            Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_GCTRL, 0x300);
        }
    }

    /*
     * 6.Check for Auto-Negotiation configuration
     * 1).Restart Auto-Negotiation. reinitialize the Auto-Negotiation process. If Auto-Negotiation is disabled
     */

    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_CTRL, &value); 


    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYPERF, &value);
    Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYPERF, (value|(1 << 10))); /* Force link Good */
    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYPERF, &value);
    /* If enable robust auto MDI/MDIX resolution, set CFG3 bit9=1, this doesn't affect link state */
    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_FWV, &value);
    Eth_Hal_WriteMii(pEthNode, PHYaddr, GETH_PHY_MDIO_FWV, (value|(1 << 9))); /* Enable robust auto MDI/MDIX resolution */
    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_FWV, &value);

    /*
     * 7.Wait for Auto-Negotiation process complete.
     */


    /*
     * 8.Wait for valid link established.
     */
    retrycount = 100000;
    do
    {
        Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_STAT, &value);

        retValue = ((value & (1 << 2)) != 0) ? 0 : 1;

        /* Valid link established. */
        if(retValue == 0)
        {
            break;
        }
        else if(retrycount < 0)
        {
            retValue = -1;
            break;
        }
        else
        {
            retrycount--;
        }

    } while(1);

    Eth_Hal_ReadMii(pEthNode, PHYaddr, GETH_PHY_MDIO_PHYSTAT1, &value);

    return retValue;
}




#endif
