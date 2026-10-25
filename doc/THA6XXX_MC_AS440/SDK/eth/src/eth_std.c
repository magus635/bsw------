/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    eth_std.h
 * Author:      00930
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file implement the internal functions of ETH Driver
 *********************************************************************************************************************/

 /*
*#Violation Summary
*#eth_std_c_REF_1:CWE-704;
* Justification: Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
*#eth_std_c_REF_2:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
*#eth_std_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#eth_std_c_REF_4:MISRAC2012-Rule-11.4;
* Justification: The register must load the buffer's address.
*
*#eth_std_c_REF_5:CertC-INT36-C;
* Justification: Cast a numeric value to a pointer type for accessing data at a specified memory address.
*
*#eth_std_c_REF_6:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#eth_std_c_REF_7:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#eth_std_c_REF_8:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "eth_std.h"
#include "eth_register.h"
#include "Platform_Types.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* Define max packet size */
#define ETH_MAXPACKETSIZE_1518BYTES (1518U) /* 1518 Bytes */
#define ETH_MAXPACKETSIZE_2000BYTES (2000U) /* 2000 Bytes */
#define ETH_MAXPACKETSIZE_9018BYTES (9018U) /* 9018 Bytes */

#define ETH_MAC_WTO_16383BYTES (0x0EU)       /* watchdog timeout */
#define ETH_COUNT_MACADDRESS_REGISTERS (62U) /* Count of mac address register */
/* 50MHz represented in Hz*/
#define ETH_50MHZ (50000000U)
/* Value - (2^32) - 1 */
#define ETH_32BITMAX (0xFFFFFFFFU)
/* Number of microseconds increments per clock or overflow */
#define ETH_SUB_SEC_INCREMENT_VAL (20U)

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: eth_std_c_REF_6 */
#define ETH_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: eth_std_c_REF_7 */
#include "Eth_MemMap.h"
/**********************************************************************************************************************
 * Function:    Eth_Std_WaitTsupdtFree
 * Description: Wait until time-stamp can be updated
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthModule: Pointer to the ETH module registers
 *              timeOut: the max delay time
 * Inout:       None
 * Output:      None
 * Return:      Eth_ReturnState:
 *                ETH_RETURN_FALSE: Return failure state
 *                ETH_RETURN_TRUE: Return success state
 * Others:      None
 * History:
 *  Date        Author    Modified
 *  2023/06/19  00930      Create
 *********************************************************************************************************************/
static Eth_ReturnState Eth_Std_WaitTsupdtFree(const ETH_MODULE *const pEthModule, uint32 timeOut);

/**********************************************************************************************************************
 * Function:    Eth_Std_WaitTsaddreqFree
 * Description: Wait until Timestamp Addend register can be updated
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthModule: Pointer to the ETH module registers
 *              timeOut: the max delay time
 * Inout:       None
 * Output:      None
 * Return:      Eth_ReturnState:
 *                ETH_RETURN_FALSE: Return failure state
 *                ETH_RETURN_TRUE: Return success state
 * Others:      None
 * History:
 *  Date        Author    Modified
 *  2023/06/19  00930      Create
 *********************************************************************************************************************/
static Eth_ReturnState Eth_Std_WaitTsaddreqFree(const ETH_MODULE *const pEthModule, uint32 timeOut);
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static Eth_ReturnState Eth_Std_WaitTsupdtFree(const ETH_MODULE *const pEthModule, uint32 timeOut)
{
    volatile uint64 timeCount;
    Eth_ReturnState retState;

    timeCount = 0ULL;
    retState = ETH_RETURN_FALSE;
    /* wait for TSINIT = 0, time-stamp can be updated */
    do
    {
        if(ETH_BIT_DISABLE == pEthModule->MAC_TIMESTAMP_CONTROL.B.TSUPDT)
        {
            retState = ETH_RETURN_TRUE;
        }
        /* Counting and accumulation */
        timeCount++;
    } while((timeCount < (uint64)timeOut) && (ETH_RETURN_FALSE == retState));

    return retState;
}

static Eth_ReturnState Eth_Std_WaitTsaddreqFree(const ETH_MODULE *const pEthModule, uint32 timeOut)
{
    volatile uint64 timeCount;
    Eth_ReturnState retState;

    timeCount = 0ULL;
    retState = ETH_RETURN_FALSE;
    /* wait for TSADDREG = 0, time-stamp can be updated addend register */
    do
    {
        if(ETH_BIT_DISABLE == pEthModule->MAC_TIMESTAMP_CONTROL.B.TSADDREG)
        {
            retState = ETH_RETURN_TRUE;
        }
        /* Counting and accumulation */
        timeCount++;
    } while((timeCount < (uint64)timeOut) && (ETH_RETURN_FALSE == retState));

    return retState;
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
Eth_ReturnState Eth_Std_ResetModule(ETH_MODULE *const pEthModule)
{
    volatile uint64 timeCount;
    Eth_ReturnState retState;

    timeCount = 0ULL;
    /* ETH module software reset  */
    /* Reset the logic and all internal register of DMA, MTL & MAC */
    pEthModule->DMA_MODE.B.SWR = 1U;
    /* Poll */
    retState = ETH_RETURN_FALSE;

    /* wait for software is finished:DMA_MODE.B.SWR = 0  */
    do
    {
        if(ETH_BIT_DISABLE == pEthModule->DMA_MODE.B.SWR)
        {
            retState = ETH_RETURN_TRUE;
        }
        /* Counting and accumulation */
        timeCount++;
    } while((timeCount < (uint64)ETH_MAXTIMEOUT_COUNT) && (ETH_RETURN_FALSE == retState));

    return retState;
}

Eth_ReturnState Eth_Std_InitTime(ETH_MODULE *const pEthModule, const uint32 ethOpetnFreq,
                                 float64 *const pPrevFreqCompensationValue)
{
    /* #Violation: eth_std_c_REF_2 */
    ETH_MAC_TIMESTAMP_CONTROL regMacTimestampControl;
    float32 freqDivisionRatio;
    Eth_ReturnState ethState;
    boolean ret;

    ret = TRUE;
    regMacTimestampControl.U = pEthModule->MAC_TIMESTAMP_CONTROL.U;
    /* Time-stamp Enable */
    regMacTimestampControl.B.TSENA = ETH_BIT_ENABLE;
    /*Add time stamp for all frames */
    regMacTimestampControl.B.TSENALL = ETH_BIT_ENABLE;
    /* Enable PTP packet Processing for Version 2 Format */
    regMacTimestampControl.B.TSVER2ENA = ETH_BIT_ENABLE;
    /* Enable Processing of PTP over Ethernet Frames */
    regMacTimestampControl.B.TSIPENA = ETH_BIT_ENABLE;
    /* Disable Processing of PTP Frames Sent over IPv4-UDP.
     In default, it is enabled.*/
    regMacTimestampControl.B.TSIPV4ENA = ETH_BIT_DISABLE;
    /* Timestamp digital roll over control for 1 nanosecond accuracy
     That is, each value in nanosecond register represent 1ns*/
    regMacTimestampControl.B.TSCTRLSSR = ETH_BIT_ENABLE;
    pEthModule->MAC_TIMESTAMP_CONTROL.U = regMacTimestampControl.U;
    ret = Eth_Register_ReadBack_Check(ret, regMacTimestampControl.U, pEthModule->MAC_TIMESTAMP_CONTROL.U);

    /* Initiliaze system time higher word second with ZERO.*/
    pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = ETH_BIT_DISABLE;
    ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_DISABLE, pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR);
    /* Initiliaze system time(Second and Nanosecond part) with  ZERO.*/
    pEthModule->MAC_SYSTEM_TIME_SECONDS_UPDATE.U = ETH_BIT_DISABLE;
    ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_DISABLE, pEthModule->MAC_SYSTEM_TIME_SECONDS_UPDATE.U);
    pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.U = ETH_BIT_DISABLE;
    ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_DISABLE, pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.U);

    /*      ------------------------------------------------------------
     *                       TIME - COARSE UPDATE
     *      ------------------------------------------------------------
     *                (Not used currently in this function,
     *                described here just for information )
     *
     *   Cosnider for 50 Mhz Peripheral Bus frequency ,
     *                   ptp clock frequency = 50 Mhz.
     *
     *   Time period = 1/(50 * 10^6) seconds = (10^9)/(50 * 10^6) nanoseconds
     *   = (10^3)/50 nanoseconds = 1000/50 ns = 20 ns.
     *
     *   Value loaded  in GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC register is
     *   added to nano second on every ptp clock cycle.
     *
     *   Hence Min resolution = 20 ns. That is, 20 counts should be loaded in
     *   GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC register.
     *
     *   General formula for value to be
     *   loaded in GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC = 1000/ EthOpetnFreq,
     *   where EthOpetnFreq is Ethernet Peripheral operation frequency in MHz. ;
     *
     *     ------------------------------------------------------------
     *                        TIME - FINE UPDATE
     *     ------------------------------------------------------------
     *                   (Used currently in this function )
     *
     *   System Time Update logic requires a 50-MHz clock frequency to
     *   achieve 20-ns accuracy, 50MHz clock is internal to GETH-IP.
     *
     *   Here on every ptp clock cycle(which is Ethernet Peripheral
     *   Bus frequency) Accumulator register( which is internal to GETH IP) is
     *   added with the contents of MAC_TIMESTAMP_ADDEND register.
     *   The arithmetic carry(Due to overflow of Accumulator ) that the
     *   Accumulator generates is used as a pulse to increment the system time
     *   counter. Everytime pulse is generated, it represents 20 ns as per below
     *   calculated addend value ,so always value to  be initialised to
     *   GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC is 20
     *
     *   Value to be loaded to MAC_TIMESTAMP_ADDEND register =
     *                                              2^32/FreqDivisionRatio
     *
     *   where FreqDivisionRatio = PTP clock frequency/ 50 = EthOpetnFreq/50
     *
     * */

    freqDivisionRatio = ((float32)ethOpetnFreq / (float32)ETH_50MHZ);

    /* #Violation: eth_std_c_REF_8 */
    if(!IS_ZERO_FLT(freqDivisionRatio))
    {
        *pPrevFreqCompensationValue = ((float64)ETH_32BITMAX / (float64)freqDivisionRatio);
        /*Update ADDEND register */
        pEthModule->MAC_TIMESTAMP_ADDEND.U = (uint32)*pPrevFreqCompensationValue;
        ret = Eth_Register_ReadBack_Check(ret, (uint32)*pPrevFreqCompensationValue, pEthModule->MAC_TIMESTAMP_ADDEND.U);
    }
    /*Update SSINC value.*/
    pEthModule->MAC_SUB_SECOND_INCREMENT.B.SSINC = ETH_SUB_SEC_INCREMENT_VAL;
    ret = Eth_Register_ReadBack_Check(ret, ETH_SUB_SEC_INCREMENT_VAL, pEthModule->MAC_SUB_SECOND_INCREMENT.B.SSINC);
    /* Time stamp Fine update */
    pEthModule->MAC_TIMESTAMP_CONTROL.B.TSCFUPDT = ETH_BIT_ENABLE;
    ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MAC_TIMESTAMP_CONTROL.B.TSCFUPDT);
    /* Wait until Update Addend Register bit is Reset.*/
    ethState = Eth_Std_WaitTsaddreqFree(pEthModule, ETH_TIMERSET_TICKS);
    /* Check if timeout not happend. */
    if(ETH_RETURN_TRUE == ethState)
    {
        /* Set Update Addend Register bit to update content of the
         Timestamp Addend register.*/
        pEthModule->MAC_TIMESTAMP_CONTROL.B.TSADDREG = ETH_BIT_ENABLE;
        /* The Update Addend Register bit is cleared when the update is
         completed.Wait until Update Addend Register bit is cleared*/
        /* Wait until Update Addend Register bit is Reset.*/
        ethState = Eth_Std_WaitTsaddreqFree(pEthModule, ETH_TIMERSET_TICKS);
        /* Check if timeout not happend. */
        if(ETH_RETURN_TRUE == ethState)
        {
            /* Wait for TSINIT bit is Reset to start Timestamp Initialization*/
            ethState = Eth_Std_WaitTsinitFree(pEthModule, ETH_TIMERSET_TICKS);
            /* Check if timeout not happend. */
            if(ETH_RETURN_TRUE == ethState)
            {
                /* Initialize Time stamp.*/
                pEthModule->MAC_TIMESTAMP_CONTROL.B.TSINIT = ETH_BIT_ENABLE;
                /* The TSINIT Register bit is cleared when when the initialization is
                 completed. Wait until TSINIT Register bit is cleared */
                ethState = Eth_Std_WaitTsinitFree(pEthModule, ETH_TIMERSET_TICKS);
            }
        }
    }
    
    if(FALSE == ret)
    {
        ethState = ETH_RETURN_FALSE;
    }
    return ethState;
}

boolean Eth_Std_ClearDaFilter(ETH_MODULE *const pEthModule)
{
    /* register range from 0xe0008308 to 0xe00003fc */
     volatile uint32 pMacAddr;
    /* #Violation: eth_std_c_REF_2 */
    ETH_MAC_PACKET_FILTER regMacPacketFilter;
    uint32 count;
    boolean ret;

    ret = TRUE;
    regMacPacketFilter.U = pEthModule->MAC_PACKET_FILTER.U;
    /* Receive all is disabled */
    regMacPacketFilter.B.RA = ETH_BIT_DISABLE;
    /* disable Promiscuous mode */
    regMacPacketFilter.B.PR = ETH_BIT_DISABLE;
    /* disable multi-caste */
    regMacPacketFilter.B.PM = ETH_BIT_DISABLE;
    /* disable broad-caste */
    regMacPacketFilter.B.DBF = ETH_BIT_ENABLE;

    /* When this bit is reset, the MAC performs a perfect destination
    address filtering for unicast packets, that is,
    it compares the DA field with the values programmed in DA registers.*/
    /* Hash Unicast */
    regMacPacketFilter.B.HUC = ETH_BIT_DISABLE;
    regMacPacketFilter.B.HMC = ETH_BIT_DISABLE;
    pEthModule->MAC_PACKET_FILTER.U = regMacPacketFilter.U;
    ret = Eth_Register_ReadBack_Check(ret, regMacPacketFilter.U, pEthModule->MAC_PACKET_FILTER.U);

    /* The result of the SA or DA filtering is updated (pass or fail)  */
    /* #Violation: eth_std_c_REF_3 */
    pMacAddr = (uint32)&(pEthModule->MAC_ADDRESS_HIGH1);
    for(count = 0U; count < ETH_COUNT_MACADDRESS_REGISTERS; count++)
    {
        /* #Violation: eth_std_c_REF_4 */
        /* #Violation: eth_std_c_REF_5 */
        /* #Violation: eth_std_c_REF_1 */
        *(uint32 *)pMacAddr = 0U;
        /* #Violation: eth_std_c_REF_4 */
        /* #Violation: eth_std_c_REF_5 */
        /* #Violation: eth_std_c_REF_1 */
        ret = Eth_Register_ReadBack_Check(ret, 0U, *(uint32 *)pMacAddr);
        pMacAddr = pMacAddr + 4U;
    }

    return ret;
}

boolean Eth_Std_SetMacMaxPacketSize(ETH_MODULE *const pEthModule, uint16 maxPacketSize)
{
    /* #Violation: eth_std_c_REF_2 */
    ETH_MAC_CONFIGURATION macConfig;
    /* #Violation: eth_std_c_REF_2 */
    ETH_MAC_WATCHDOG_TIMEOUT macWDTimOut;
    boolean ret;

    ret = TRUE;
    macConfig.U = pEthModule->MAC_CONFIGURATION.U;
    if(ETH_MAXPACKETSIZE_1518BYTES == maxPacketSize)
    {
        macConfig.B.JE = ETH_BIT_DISABLE;
        macConfig.B.S2KP = ETH_BIT_DISABLE;
        macConfig.B.GPSLCE = ETH_BIT_DISABLE;
        macConfig.B.JD = ETH_BIT_DISABLE;
    }
    else if(ETH_MAXPACKETSIZE_2000BYTES == maxPacketSize)
    {
        macConfig.B.JE = ETH_BIT_DISABLE;
        /* 2k packet is enable (IEEE 802.3as support) */
        macConfig.B.S2KP = ETH_BIT_ENABLE;
        macConfig.B.GPSLCE = ETH_BIT_DISABLE;
        macConfig.B.JD = ETH_BIT_DISABLE;
    }
    else if(ETH_MAXPACKETSIZE_9018BYTES == maxPacketSize)
    {
        /* Jumbo packet Enable, allows 9018 bytes(9022 for VLAN tagged packets) */
        macConfig.B.JE = ETH_BIT_ENABLE;
        macConfig.B.GPSLCE = ETH_BIT_DISABLE;
        macConfig.B.JD = ETH_BIT_DISABLE;
    }
    else
    {
        macConfig.B.JE = ETH_BIT_DISABLE;
        macConfig.B.S2KP = ETH_BIT_DISABLE;
        /* Giant packet size limit control enable, GPSL in MAC_Ext_Configuration */
        macConfig.B.GPSLCE = ETH_BIT_ENABLE;
        /* Jabber is disabled, MAC can transfer up to 16383 bytes */
        macConfig.B.JD = ETH_BIT_ENABLE;
        pEthModule->MAC_EXT_CONFIGURATION.B.GPSL = maxPacketSize;
        ret = Eth_Register_ReadBack_Check(ret, maxPacketSize, pEthModule->MAC_EXT_CONFIGURATION.B.GPSL);

        macWDTimOut.U = pEthModule->MAC_WATCHDOG_TIMEOUT.U;
        /* programmable Watchdog enable, WTO field is used as watchdog timeout */
        macWDTimOut.B.PWE = ETH_BIT_ENABLE;
        /* packet size up to 16383 bytes */
        macWDTimOut.B.WTO = ETH_MAC_WTO_16383BYTES;
        pEthModule->MAC_WATCHDOG_TIMEOUT.U = macWDTimOut.U;
        ret = Eth_Register_ReadBack_Check(ret, macWDTimOut.U, pEthModule->MAC_WATCHDOG_TIMEOUT.U);
    }
    pEthModule->MAC_CONFIGURATION.U = macConfig.U;
    ret = Eth_Register_ReadBack_Check(ret, macConfig.U, pEthModule->MAC_CONFIGURATION.U);

    return ret;
}

boolean Eth_Std_SetMulticast(ETH_MODULE *const pEthModule, boolean enableMulticast)
{
    boolean ret;

    ret = TRUE;
    if(TRUE == enableMulticast)
    {
        pEthModule->MAC_PACKET_FILTER.B.PM = ETH_BIT_ENABLE;
        ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MAC_PACKET_FILTER.B.PM);
    }
    else
    {
        pEthModule->MAC_PACKET_FILTER.B.PM = ETH_BIT_DISABLE;
        ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_DISABLE, pEthModule->MAC_PACKET_FILTER.B.PM);
    }
    return ret;
}

boolean Eth_Std_SetPromiscuous(ETH_MODULE *const pEthModule, boolean enablePromiscuous)
{
    boolean ret;
    /* #Violation: eth_std_c_REF_2 */
    ETH_MAC_PACKET_FILTER macPacketFilt;

    ret = TRUE;
    if(TRUE == enablePromiscuous)
    {
        pEthModule->MAC_PACKET_FILTER.B.PR = ETH_BIT_ENABLE;
        ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MAC_PACKET_FILTER.B.PR);
    }
    else
    {
        macPacketFilt.U = pEthModule->MAC_PACKET_FILTER.U;
        macPacketFilt.B.PR = ETH_BIT_DISABLE;
        macPacketFilt.B.RA = ETH_BIT_DISABLE;
        pEthModule->MAC_PACKET_FILTER.U = macPacketFilt.U;
        ret = Eth_Register_ReadBack_Check(ret, macPacketFilt.U, pEthModule->MAC_PACKET_FILTER.U);
    }

    return ret;
}

Eth_ReturnState Eth_Std_AddDaFilter(ETH_MODULE *const pEthModule, uint32 addrHigh, uint32 addrLow)
{
    volatile uint32 *pMacAddrLow;
    volatile uint32 *pMacAddrHigh;
    uint32 macAddrHighValue;
    Eth_ReturnState retState;
    uint8 count;
    uint8 maxCount;
    boolean ret;

    ret = TRUE;
    retState = ETH_RETURN_FALSE;
    pMacAddrLow = (volatile uint32 *)&(pEthModule->MAC_ADDRESS_LOW1.U);
    pMacAddrHigh = (volatile uint32 *)&(pEthModule->MAC_ADDRESS_HIGH1.U);
    maxCount = (uint8)(ETH_COUNT_MACADDRESS_REGISTERS / 2U);

    /* Total 31 DA filters */
    count = 0U;
    while((count < maxCount) && ((0U != *pMacAddrLow) && (0U != (*pMacAddrHigh & 0xFFFFU))))
    {
        if((addrLow == *pMacAddrLow) && (addrHigh == (*pMacAddrHigh & 0xFFFFU)))
        {
            /*check if the address already exist,exit*/
            count = maxCount;
        }
        else
        {
            /* skip one high register */
            pMacAddrLow = &pMacAddrLow[2U];
            /* skip one low register */
            pMacAddrHigh = &pMacAddrHigh[2U];
            count++;
        }
    }

    if((0U == *pMacAddrLow) && (0U == (*pMacAddrHigh & 0xFFFFU)))
    {
        /* empty slot */
        macAddrHighValue = *pMacAddrHigh & 0xFFFF0000U;
        macAddrHighValue |= (addrHigh | 0x80000000U);
        *pMacAddrHigh = macAddrHighValue;
        ret = Eth_Register_ReadBack_Check(ret, macAddrHighValue, *pMacAddrHigh);
        *pMacAddrLow = addrLow;
        ret = Eth_Register_ReadBack_Check(ret, addrLow, *pMacAddrLow);

        retState = ETH_RETURN_TRUE;
    }

    if(FALSE == ret)
    {
        retState = ETH_RETURN_FALSE;
    }
    return retState;
}

Eth_ReturnState Eth_Std_RemoveDaFilter(ETH_MODULE *const pEthModule, uint32 addrHigh, uint32 addrLow)
{

    volatile uint32 *pMacAddrLow;
    volatile uint32 *pMacAddrHigh;
    Eth_ReturnState retState;
    uint8 count;
    uint8 maxCount;
    boolean ret;

    ret = TRUE;
    retState = ETH_RETURN_FALSE;
    pMacAddrLow = (volatile uint32 *)&(pEthModule->MAC_ADDRESS_LOW1.U);
    pMacAddrHigh = (volatile uint32 *)&(pEthModule->MAC_ADDRESS_HIGH1.U);
    maxCount = (uint8)(ETH_COUNT_MACADDRESS_REGISTERS / 2U);

    count = 0U;
    while((count < maxCount) && ((addrLow != *pMacAddrLow) && (addrHigh != (*pMacAddrHigh & 0xFFFFU))))
    {
        /* skip one high register */
        pMacAddrLow = &pMacAddrLow[2U];
        /* skip one low register */
        pMacAddrHigh = &pMacAddrHigh[2U];
        count++;
    }

    if((addrLow == *pMacAddrLow) && (addrHigh == (*pMacAddrHigh & 0xFFFFU)))
    {
        /* Match slot */
        *pMacAddrLow = 0U;
        ret = Eth_Register_ReadBack_Check(ret, 0U, *pMacAddrLow);
        *pMacAddrHigh = 0U;
        ret = Eth_Register_ReadBack_Check(ret, 0U, *pMacAddrHigh);
        retState = ETH_RETURN_TRUE;
    }

    if(FALSE == ret)
    {
        retState = ETH_RETURN_FALSE;
    }
    return retState;
}

Eth_ReturnState Eth_Std_SetCorrectTime(ETH_MODULE *const pEthModule, Eth_SysTimeCorrect correctType,
                                       uint16 secondsHiUpdate, uint32 secondsUpdate, uint32 nanoSecondsUpdate)
{
    Eth_ReturnState ethState;
    uint32 currentTimeSeconds;
    uint16 currentTimeHigSeconds;
    boolean ret;
    uint32 timesampHight;

    ret = TRUE;
    /* Wait until TSUPDT bit is zero, before starting system time update */
    ethState = Eth_Std_WaitTsupdtFree(pEthModule, ETH_TIMERSET_TICKS);
    /* Check if timeout not happend. */
    if(ETH_RETURN_TRUE == ethState)
    {
        if(ETH_SYSTIME_CORR_NEGATIVE == correctType)
        {
            pEthModule->MAC_SYSTEM_TIME_SECONDS_UPDATE.U = (uint32)(ETH_TWO_POW_32_VAL - secondsUpdate);
            ret = Eth_Register_ReadBack_Check(ret, (uint32)(ETH_TWO_POW_32_VAL - secondsUpdate), 
                pEthModule->MAC_SYSTEM_TIME_SECONDS_UPDATE.U);
            pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS =
                (uint32)(ETH_ONE_SEC_TO_NANOSEC - nanoSecondsUpdate);
            ret = Eth_Register_ReadBack_Check(ret, (uint32)(ETH_ONE_SEC_TO_NANOSEC - nanoSecondsUpdate), 
                pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS);
            /* Read current time (seconds)*/
            currentTimeSeconds = pEthModule->MAC_SYSTEM_TIME_SECONDS.U;
            /* Read current time (High word seconds)*/
            currentTimeHigSeconds = pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR;
            /* Check if current timer (seconds) is greater than requested seconds offset to be reduced from current
               seconds. If not, High seconds has to be reduced additionally 1. This is due to that, when updating
               seconds time, if seconds underflow happens, hardware will not automatically reduce High seconds.
               Hence it is taken care in ETH driver */
            if((secondsUpdate > currentTimeSeconds) && (currentTimeHigSeconds != (uint16)0U))
            {
                timesampHight = pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR;
                timesampHight -= (uint16)ETH_BIT_ENABLE;
                pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = timesampHight;
                ret = Eth_Register_ReadBack_Check(ret, timesampHight, pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR);
            }
            timesampHight = pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR;
            timesampHight -= secondsHiUpdate;
            pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = timesampHight;
            ret = Eth_Register_ReadBack_Check(ret, timesampHight, pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR);
            pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.ADDSUB = ETH_BIT_ENABLE;
            ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_ENABLE, pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.ADDSUB);
        }
        else
        {
            pEthModule->MAC_SYSTEM_TIME_SECONDS_UPDATE.U = secondsUpdate;
            ret = Eth_Register_ReadBack_Check(ret, secondsUpdate, pEthModule->MAC_SYSTEM_TIME_SECONDS_UPDATE.U);
            pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS = nanoSecondsUpdate;
            ret = Eth_Register_ReadBack_Check(ret, nanoSecondsUpdate, pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS);

            timesampHight = pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR;
            timesampHight += secondsHiUpdate;
            pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = timesampHight;
            ret = Eth_Register_ReadBack_Check(ret, timesampHight, pEthModule->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR);
            pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.ADDSUB = ETH_BIT_DISABLE;
            ret = Eth_Register_ReadBack_Check(ret, ETH_BIT_DISABLE, pEthModule->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.ADDSUB);
        }
        /* Set TSUPDT bit, Hence, Time update process starts. Setting 1, Self-cleared*/
        pEthModule->MAC_TIMESTAMP_CONTROL.B.TSUPDT = ETH_BIT_ENABLE;
        /*Wait until TSUPDT bit reset. It means time update is finished.*/
        ethState = Eth_Std_WaitTsupdtFree(pEthModule, ETH_TIMERSET_TICKS);
    }

    if(FALSE == ret)
    {
        ethState = ETH_RETURN_FALSE;
    }
    return ethState;
}

Eth_ReturnState Eth_Std_SetCorrectRateRatio(ETH_MODULE *const pEthModule, float64 freqCompensationValue)
{
    Eth_ReturnState ethState;
    boolean ret;

    ret = TRUE;
    if(freqCompensationValue < (float64)ETH_32BITMAX)
    {
        pEthModule->MAC_TIMESTAMP_ADDEND.U = (uint32)freqCompensationValue;
        ret = Eth_Register_ReadBack_Check(ret, (uint32)freqCompensationValue, pEthModule->MAC_TIMESTAMP_ADDEND.U);
    }
    else
    {
        pEthModule->MAC_TIMESTAMP_ADDEND.U = (uint32)(ETH_32BITMAX - 1U);
        ret = Eth_Register_ReadBack_Check(ret, (uint32)(ETH_32BITMAX - 1U),  pEthModule->MAC_TIMESTAMP_ADDEND.U);
    }
    /* Wait until Update Addend Register bit is Reset.*/
    ethState = Eth_Std_WaitTsaddreqFree(pEthModule, ETH_TIMERSET_TICKS);
    /* Check if timeout not happend. */
    if(ETH_RETURN_TRUE == ethState)
    {
        /* Set Update Addend Register bit to update content of the
         Timestamp Addend register.
         Info :When this bit is set, the content of the Timestamp Addend
         register is updated in the PTP block for fine correction*/
        pEthModule->MAC_TIMESTAMP_CONTROL.B.TSADDREG = ETH_BIT_ENABLE;
        /* The Update Addend Register bit bit is cleared when the update is
         completed.Wait until Addend Register bit bit is cleared*/
        ethState = Eth_Std_WaitTsaddreqFree(pEthModule, ETH_TIMERSET_TICKS);
    }

    if(FALSE == ret)
    {
        ethState = ETH_RETURN_FALSE;
    }
    return ethState;
}

Eth_ReturnState Eth_Std_WaitGmiiFree(const ETH_MODULE *const pEthModule, uint32 timeOut)
{
    volatile uint64 timeCount;
    Eth_ReturnState retState;

    timeCount = 0ULL;
    retState = ETH_RETURN_FALSE;
    /* wait for any previous MII read/write operation to complete */
    /* Poll */
    /* Get current time as start time */
    do
    {
        if(ETH_BIT_DISABLE == pEthModule->MAC_MDIO_ADDRESS.B.GB)
        {
            retState = ETH_RETURN_TRUE;
        }
        /* Counting and accumulation */
        timeCount++;
    } while((timeCount < (uint64)timeOut) && (ETH_RETURN_FALSE == retState));

    return retState;
}

Eth_ReturnState Eth_Std_WaitTsinitFree(const ETH_MODULE *const pEthModule, uint32 timeOut)
{
    volatile uint64 timeCount;
    Eth_ReturnState retState;

    timeCount = 0ULL;
    retState = ETH_RETURN_FALSE;
    /* wait for TSINIT = 0, time-stamp can be initialized */
    /* Get current time as start time */
    do
    {
        if(ETH_BIT_DISABLE == pEthModule->MAC_TIMESTAMP_CONTROL.B.TSINIT)
        {
            retState = ETH_RETURN_TRUE;
        }
        /* Counting and accumulation */
        timeCount++;
    } while((timeCount < (uint64)timeOut) && (ETH_RETURN_FALSE == retState));

    return retState;
}

/* #Violation: eth_std_c_REF_6 */
#define ETH_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: eth_std_c_REF_7 */
#include "Eth_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
